<शैली गुरु>
/*
 * Driver giving user-space access to the kernel's xenbus connection
 * to xenstore.
 *
 * Copyright (c) 2005, Christian Limpach
 * Copyright (c) 2005, Rusty Russell, IBM Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Changes:
 * 2008-10-07  Alex Zeffertt    Replaced /proc/xen/xenbus with xenfs fileप्रणाली
 *                              and /proc/xen compatibility mount poपूर्णांक.
 *                              Turned xenfs पूर्णांकo a loadable module.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/uपन.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/रुको.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/init.h>
#समावेश <linux/namei.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/workqueue.h>

#समावेश <xen/xenbus.h>
#समावेश <xen/xen.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश "xenbus.h"

अचिन्हित पूर्णांक xb_dev_generation_id;

/*
 * An element of a list of outstanding transactions, क्रम which we're
 * still रुकोing a reply.
 */
काष्ठा xenbus_transaction_holder अणु
	काष्ठा list_head list;
	काष्ठा xenbus_transaction handle;
	अचिन्हित पूर्णांक generation_id;
पूर्ण;

/*
 * A buffer of data on the queue.
 */
काष्ठा पढ़ो_buffer अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक cons;
	अचिन्हित पूर्णांक len;
	अक्षर msg[];
पूर्ण;

काष्ठा xenbus_file_priv अणु
	/*
	 * msgbuffer_mutex is held जबतक partial requests are built up
	 * and complete requests are acted on.  It thereक्रमe protects
	 * the "transactions" and "watches" lists, and the partial
	 * request length and buffer.
	 *
	 * reply_mutex protects the reply being built up to वापस to
	 * usermode.  It nests inside msgbuffer_mutex but may be held
	 * alone during a watch callback.
	 */
	काष्ठा mutex msgbuffer_mutex;

	/* In-progress transactions */
	काष्ठा list_head transactions;

	/* Active watches. */
	काष्ठा list_head watches;

	/* Partial request. */
	अचिन्हित पूर्णांक len;
	जोड़ अणु
		काष्ठा xsd_sockmsg msg;
		अक्षर buffer[XENSTORE_PAYLOAD_MAX];
	पूर्ण u;

	/* Response queue. */
	काष्ठा mutex reply_mutex;
	काष्ठा list_head पढ़ो_buffers;
	रुको_queue_head_t पढ़ो_रुकोq;

	काष्ठा kref kref;

	काष्ठा work_काष्ठा wq;
पूर्ण;

/* Read out any raw xenbus messages queued up. */
अटल sमाप_प्रकार xenbus_file_पढ़ो(काष्ठा file *filp,
			       अक्षर __user *ubuf,
			       माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा xenbus_file_priv *u = filp->निजी_data;
	काष्ठा पढ़ो_buffer *rb;
	अचिन्हित i;
	पूर्णांक ret;

	mutex_lock(&u->reply_mutex);
again:
	जबतक (list_empty(&u->पढ़ो_buffers)) अणु
		mutex_unlock(&u->reply_mutex);
		अगर (filp->f_flags & O_NONBLOCK)
			वापस -EAGAIN;

		ret = रुको_event_पूर्णांकerruptible(u->पढ़ो_रुकोq,
					       !list_empty(&u->पढ़ो_buffers));
		अगर (ret)
			वापस ret;
		mutex_lock(&u->reply_mutex);
	पूर्ण

	rb = list_entry(u->पढ़ो_buffers.next, काष्ठा पढ़ो_buffer, list);
	i = 0;
	जबतक (i < len) अणु
		अचिन्हित sz = min((अचिन्हित)len - i, rb->len - rb->cons);

		ret = copy_to_user(ubuf + i, &rb->msg[rb->cons], sz);

		i += sz - ret;
		rb->cons += sz - ret;

		अगर (ret != 0) अणु
			अगर (i == 0)
				i = -EFAULT;
			जाओ out;
		पूर्ण

		/* Clear out buffer अगर it has been consumed */
		अगर (rb->cons == rb->len) अणु
			list_del(&rb->list);
			kमुक्त(rb);
			अगर (list_empty(&u->पढ़ो_buffers))
				अवरोध;
			rb = list_entry(u->पढ़ो_buffers.next,
					काष्ठा पढ़ो_buffer, list);
		पूर्ण
	पूर्ण
	अगर (i == 0)
		जाओ again;

out:
	mutex_unlock(&u->reply_mutex);
	वापस i;
पूर्ण

/*
 * Add a buffer to the queue.  Caller must hold the appropriate lock
 * अगर the queue is not local.  (Commonly the caller will build up
 * multiple queued buffers on a temporary local list, and then add it
 * to the appropriate list under lock once all the buffers have een
 * successfully allocated.)
 */
अटल पूर्णांक queue_reply(काष्ठा list_head *queue, स्थिर व्योम *data, माप_प्रकार len)
अणु
	काष्ठा पढ़ो_buffer *rb;

	अगर (len == 0)
		वापस 0;
	अगर (len > XENSTORE_PAYLOAD_MAX)
		वापस -EINVAL;

	rb = kदो_स्मृति(माप(*rb) + len, GFP_KERNEL);
	अगर (rb == शून्य)
		वापस -ENOMEM;

	rb->cons = 0;
	rb->len = len;

	स_नकल(rb->msg, data, len);

	list_add_tail(&rb->list, queue);
	वापस 0;
पूर्ण

/*
 * Free all the पढ़ो_buffer s on a list.
 * Caller must have sole reference to list.
 */
अटल व्योम queue_cleanup(काष्ठा list_head *list)
अणु
	काष्ठा पढ़ो_buffer *rb;

	जबतक (!list_empty(list)) अणु
		rb = list_entry(list->next, काष्ठा पढ़ो_buffer, list);
		list_del(list->next);
		kमुक्त(rb);
	पूर्ण
पूर्ण

काष्ठा watch_adapter अणु
	काष्ठा list_head list;
	काष्ठा xenbus_watch watch;
	काष्ठा xenbus_file_priv *dev_data;
	अक्षर *token;
पूर्ण;

अटल व्योम मुक्त_watch_adapter(काष्ठा watch_adapter *watch)
अणु
	kमुक्त(watch->watch.node);
	kमुक्त(watch->token);
	kमुक्त(watch);
पूर्ण

अटल काष्ठा watch_adapter *alloc_watch_adapter(स्थिर अक्षर *path,
						 स्थिर अक्षर *token)
अणु
	काष्ठा watch_adapter *watch;

	watch = kzalloc(माप(*watch), GFP_KERNEL);
	अगर (watch == शून्य)
		जाओ out_fail;

	watch->watch.node = kstrdup(path, GFP_KERNEL);
	अगर (watch->watch.node == शून्य)
		जाओ out_मुक्त;

	watch->token = kstrdup(token, GFP_KERNEL);
	अगर (watch->token == शून्य)
		जाओ out_मुक्त;

	वापस watch;

out_मुक्त:
	मुक्त_watch_adapter(watch);

out_fail:
	वापस शून्य;
पूर्ण

अटल व्योम watch_fired(काष्ठा xenbus_watch *watch,
			स्थिर अक्षर *path,
			स्थिर अक्षर *token)
अणु
	काष्ठा watch_adapter *adap;
	काष्ठा xsd_sockmsg hdr;
	स्थिर अक्षर *token_caller;
	पूर्णांक path_len, tok_len, body_len;
	पूर्णांक ret;
	LIST_HEAD(staging_q);

	adap = container_of(watch, काष्ठा watch_adapter, watch);

	token_caller = adap->token;

	path_len = म_माप(path) + 1;
	tok_len = म_माप(token_caller) + 1;
	body_len = path_len + tok_len;

	hdr.type = XS_WATCH_EVENT;
	hdr.len = body_len;

	mutex_lock(&adap->dev_data->reply_mutex);

	ret = queue_reply(&staging_q, &hdr, माप(hdr));
	अगर (!ret)
		ret = queue_reply(&staging_q, path, path_len);
	अगर (!ret)
		ret = queue_reply(&staging_q, token_caller, tok_len);

	अगर (!ret) अणु
		/* success: pass reply list onto watcher */
		list_splice_tail(&staging_q, &adap->dev_data->पढ़ो_buffers);
		wake_up(&adap->dev_data->पढ़ो_रुकोq);
	पूर्ण अन्यथा
		queue_cleanup(&staging_q);

	mutex_unlock(&adap->dev_data->reply_mutex);
पूर्ण

अटल व्योम xenbus_worker(काष्ठा work_काष्ठा *wq)
अणु
	काष्ठा xenbus_file_priv *u;
	काष्ठा xenbus_transaction_holder *trans, *पंचांगp;
	काष्ठा watch_adapter *watch, *पंचांगp_watch;
	काष्ठा पढ़ो_buffer *rb, *पंचांगp_rb;

	u = container_of(wq, काष्ठा xenbus_file_priv, wq);

	/*
	 * No need क्रम locking here because there are no other users,
	 * by definition.
	 */

	list_क्रम_each_entry_safe(trans, पंचांगp, &u->transactions, list) अणु
		xenbus_transaction_end(trans->handle, 1);
		list_del(&trans->list);
		kमुक्त(trans);
	पूर्ण

	list_क्रम_each_entry_safe(watch, पंचांगp_watch, &u->watches, list) अणु
		unरेजिस्टर_xenbus_watch(&watch->watch);
		list_del(&watch->list);
		मुक्त_watch_adapter(watch);
	पूर्ण

	list_क्रम_each_entry_safe(rb, पंचांगp_rb, &u->पढ़ो_buffers, list) अणु
		list_del(&rb->list);
		kमुक्त(rb);
	पूर्ण
	kमुक्त(u);
पूर्ण

अटल व्योम xenbus_file_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा xenbus_file_priv *u;

	/*
	 * We might be called in xenbus_thपढ़ो().
	 * Use workqueue to aव्योम deadlock.
	 */
	u = container_of(kref, काष्ठा xenbus_file_priv, kref);
	schedule_work(&u->wq);
पूर्ण

अटल काष्ठा xenbus_transaction_holder *xenbus_get_transaction(
	काष्ठा xenbus_file_priv *u, uपूर्णांक32_t tx_id)
अणु
	काष्ठा xenbus_transaction_holder *trans;

	list_क्रम_each_entry(trans, &u->transactions, list)
		अगर (trans->handle.id == tx_id)
			वापस trans;

	वापस शून्य;
पूर्ण

व्योम xenbus_dev_queue_reply(काष्ठा xb_req_data *req)
अणु
	काष्ठा xenbus_file_priv *u = req->par;
	काष्ठा xenbus_transaction_holder *trans = शून्य;
	पूर्णांक rc;
	LIST_HEAD(staging_q);

	xs_request_निकास(req);

	mutex_lock(&u->msgbuffer_mutex);

	अगर (req->type == XS_TRANSACTION_START) अणु
		trans = xenbus_get_transaction(u, 0);
		अगर (WARN_ON(!trans))
			जाओ out;
		अगर (req->msg.type == XS_ERROR) अणु
			list_del(&trans->list);
			kमुक्त(trans);
		पूर्ण अन्यथा अणु
			rc = kstrtou32(req->body, 10, &trans->handle.id);
			अगर (WARN_ON(rc))
				जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (req->type == XS_TRANSACTION_END) अणु
		trans = xenbus_get_transaction(u, req->msg.tx_id);
		अगर (WARN_ON(!trans))
			जाओ out;
		list_del(&trans->list);
		kमुक्त(trans);
	पूर्ण

	mutex_unlock(&u->msgbuffer_mutex);

	mutex_lock(&u->reply_mutex);
	rc = queue_reply(&staging_q, &req->msg, माप(req->msg));
	अगर (!rc)
		rc = queue_reply(&staging_q, req->body, req->msg.len);
	अगर (!rc) अणु
		list_splice_tail(&staging_q, &u->पढ़ो_buffers);
		wake_up(&u->पढ़ो_रुकोq);
	पूर्ण अन्यथा अणु
		queue_cleanup(&staging_q);
	पूर्ण
	mutex_unlock(&u->reply_mutex);

	kमुक्त(req->body);
	kमुक्त(req);

	kref_put(&u->kref, xenbus_file_मुक्त);

	वापस;

 out:
	mutex_unlock(&u->msgbuffer_mutex);
पूर्ण

अटल पूर्णांक xenbus_command_reply(काष्ठा xenbus_file_priv *u,
				अचिन्हित पूर्णांक msg_type, स्थिर अक्षर *reply)
अणु
	काष्ठा अणु
		काष्ठा xsd_sockmsg hdr;
		अक्षर body[16];
	पूर्ण msg;
	पूर्णांक rc;

	msg.hdr = u->u.msg;
	msg.hdr.type = msg_type;
	msg.hdr.len = म_माप(reply) + 1;
	अगर (msg.hdr.len > माप(msg.body))
		वापस -E2BIG;
	स_नकल(&msg.body, reply, msg.hdr.len);

	mutex_lock(&u->reply_mutex);
	rc = queue_reply(&u->पढ़ो_buffers, &msg, माप(msg.hdr) + msg.hdr.len);
	wake_up(&u->पढ़ो_रुकोq);
	mutex_unlock(&u->reply_mutex);

	अगर (!rc)
		kref_put(&u->kref, xenbus_file_मुक्त);

	वापस rc;
पूर्ण

अटल पूर्णांक xenbus_ग_लिखो_transaction(अचिन्हित msg_type,
				    काष्ठा xenbus_file_priv *u)
अणु
	पूर्णांक rc;
	काष्ठा xenbus_transaction_holder *trans = शून्य;
	काष्ठा अणु
		काष्ठा xsd_sockmsg hdr;
		अक्षर body[];
	पूर्ण *msg = (व्योम *)u->u.buffer;

	अगर (msg_type == XS_TRANSACTION_START) अणु
		trans = kzalloc(माप(*trans), GFP_KERNEL);
		अगर (!trans) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण
		trans->generation_id = xb_dev_generation_id;
		list_add(&trans->list, &u->transactions);
	पूर्ण अन्यथा अगर (msg->hdr.tx_id != 0 &&
		   !xenbus_get_transaction(u, msg->hdr.tx_id))
		वापस xenbus_command_reply(u, XS_ERROR, "ENOENT");
	अन्यथा अगर (msg_type == XS_TRANSACTION_END &&
		 !(msg->hdr.len == 2 &&
		   (!म_भेद(msg->body, "T") || !म_भेद(msg->body, "F"))))
		वापस xenbus_command_reply(u, XS_ERROR, "EINVAL");
	अन्यथा अगर (msg_type == XS_TRANSACTION_END) अणु
		trans = xenbus_get_transaction(u, msg->hdr.tx_id);
		अगर (trans && trans->generation_id != xb_dev_generation_id) अणु
			list_del(&trans->list);
			kमुक्त(trans);
			अगर (!म_भेद(msg->body, "T"))
				वापस xenbus_command_reply(u, XS_ERROR,
							    "EAGAIN");
			अन्यथा
				वापस xenbus_command_reply(u,
							    XS_TRANSACTION_END,
							    "OK");
		पूर्ण
	पूर्ण

	rc = xenbus_dev_request_and_reply(&msg->hdr, u);
	अगर (rc && trans) अणु
		list_del(&trans->list);
		kमुक्त(trans);
	पूर्ण

out:
	वापस rc;
पूर्ण

अटल पूर्णांक xenbus_ग_लिखो_watch(अचिन्हित msg_type, काष्ठा xenbus_file_priv *u)
अणु
	काष्ठा watch_adapter *watch;
	अक्षर *path, *token;
	पूर्णांक err, rc;

	path = u->u.buffer + माप(u->u.msg);
	token = स_प्रथम(path, 0, u->u.msg.len);
	अगर (token == शून्य) अणु
		rc = xenbus_command_reply(u, XS_ERROR, "EINVAL");
		जाओ out;
	पूर्ण
	token++;
	अगर (स_प्रथम(token, 0, u->u.msg.len - (token - path)) == शून्य) अणु
		rc = xenbus_command_reply(u, XS_ERROR, "EINVAL");
		जाओ out;
	पूर्ण

	अगर (msg_type == XS_WATCH) अणु
		watch = alloc_watch_adapter(path, token);
		अगर (watch == शून्य) अणु
			rc = -ENOMEM;
			जाओ out;
		पूर्ण

		watch->watch.callback = watch_fired;
		watch->dev_data = u;

		err = रेजिस्टर_xenbus_watch(&watch->watch);
		अगर (err) अणु
			मुक्त_watch_adapter(watch);
			rc = err;
			जाओ out;
		पूर्ण
		list_add(&watch->list, &u->watches);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(watch, &u->watches, list) अणु
			अगर (!म_भेद(watch->token, token) &&
			    !म_भेद(watch->watch.node, path)) अणु
				unरेजिस्टर_xenbus_watch(&watch->watch);
				list_del(&watch->list);
				मुक्त_watch_adapter(watch);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Success.  Synthesize a reply to say all is OK. */
	rc = xenbus_command_reply(u, msg_type, "OK");

out:
	वापस rc;
पूर्ण

अटल sमाप_प्रकार xenbus_file_ग_लिखो(काष्ठा file *filp,
				स्थिर अक्षर __user *ubuf,
				माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा xenbus_file_priv *u = filp->निजी_data;
	uपूर्णांक32_t msg_type;
	पूर्णांक rc = len;
	पूर्णांक ret;

	/*
	 * We're expecting usermode to be writing properly क्रमmed
	 * xenbus messages.  If they ग_लिखो an incomplete message we
	 * buffer it up.  Once it is complete, we act on it.
	 */

	/*
	 * Make sure concurrent ग_लिखोrs can't stomp all over each
	 * other's messages and make a mess of our partial message
	 * buffer.  We करोn't make any attemppt to stop multiple
	 * ग_लिखोrs from making a mess of each other's incomplete
	 * messages; we're just trying to guarantee our own पूर्णांकernal
	 * consistency and make sure that single ग_लिखोs are handled
	 * atomically.
	 */
	mutex_lock(&u->msgbuffer_mutex);

	/* Get this out of the way early to aव्योम confusion */
	अगर (len == 0)
		जाओ out;

	/* Can't ग_लिखो a xenbus message larger we can buffer */
	अगर (len > माप(u->u.buffer) - u->len) अणु
		/* On error, dump existing buffer */
		u->len = 0;
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	ret = copy_from_user(u->u.buffer + u->len, ubuf, len);

	अगर (ret != 0) अणु
		rc = -EFAULT;
		जाओ out;
	पूर्ण

	/* Deal with a partial copy. */
	len -= ret;
	rc = len;

	u->len += len;

	/* Return अगर we haven't got a full message yet */
	अगर (u->len < माप(u->u.msg))
		जाओ out;	/* not even the header yet */

	/* If we're expecting a message that's larger than we can
	   possibly send, dump what we have and वापस an error. */
	अगर ((माप(u->u.msg) + u->u.msg.len) > माप(u->u.buffer)) अणु
		rc = -E2BIG;
		u->len = 0;
		जाओ out;
	पूर्ण

	अगर (u->len < (माप(u->u.msg) + u->u.msg.len))
		जाओ out;	/* incomplete data portion */

	/*
	 * OK, now we have a complete message.  Do something with it.
	 */

	kref_get(&u->kref);

	msg_type = u->u.msg.type;

	चयन (msg_type) अणु
	हाल XS_WATCH:
	हाल XS_UNWATCH:
		/* (Un)Ask क्रम some path to be watched क्रम changes */
		ret = xenbus_ग_लिखो_watch(msg_type, u);
		अवरोध;

	शेष:
		/* Send out a transaction */
		ret = xenbus_ग_लिखो_transaction(msg_type, u);
		अवरोध;
	पूर्ण
	अगर (ret != 0) अणु
		rc = ret;
		kref_put(&u->kref, xenbus_file_मुक्त);
	पूर्ण

	/* Buffered message consumed */
	u->len = 0;

 out:
	mutex_unlock(&u->msgbuffer_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक xenbus_file_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा xenbus_file_priv *u;

	अगर (xen_store_evtchn == 0)
		वापस -ENOENT;

	stream_खोलो(inode, filp);

	u = kzalloc(माप(*u), GFP_KERNEL);
	अगर (u == शून्य)
		वापस -ENOMEM;

	kref_init(&u->kref);

	INIT_LIST_HEAD(&u->transactions);
	INIT_LIST_HEAD(&u->watches);
	INIT_LIST_HEAD(&u->पढ़ो_buffers);
	init_रुकोqueue_head(&u->पढ़ो_रुकोq);
	INIT_WORK(&u->wq, xenbus_worker);

	mutex_init(&u->reply_mutex);
	mutex_init(&u->msgbuffer_mutex);

	filp->निजी_data = u;

	वापस 0;
पूर्ण

अटल पूर्णांक xenbus_file_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा xenbus_file_priv *u = filp->निजी_data;

	kref_put(&u->kref, xenbus_file_मुक्त);

	वापस 0;
पूर्ण

अटल __poll_t xenbus_file_poll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा xenbus_file_priv *u = file->निजी_data;

	poll_रुको(file, &u->पढ़ो_रुकोq, रुको);
	अगर (!list_empty(&u->पढ़ो_buffers))
		वापस EPOLLIN | EPOLLRDNORM;
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations xen_xenbus_fops = अणु
	.पढ़ो = xenbus_file_पढ़ो,
	.ग_लिखो = xenbus_file_ग_लिखो,
	.खोलो = xenbus_file_खोलो,
	.release = xenbus_file_release,
	.poll = xenbus_file_poll,
	.llseek = no_llseek,
पूर्ण;
EXPORT_SYMBOL_GPL(xen_xenbus_fops);

अटल काष्ठा miscdevice xenbus_dev = अणु
	.minor = MISC_DYNAMIC_MINOR,
	.name = "xen/xenbus",
	.fops = &xen_xenbus_fops,
पूर्ण;

अटल पूर्णांक __init xenbus_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_करोमुख्य())
		वापस -ENODEV;

	err = misc_रेजिस्टर(&xenbus_dev);
	अगर (err)
		pr_err("Could not register xenbus frontend device\n");
	वापस err;
पूर्ण
device_initcall(xenbus_init);
