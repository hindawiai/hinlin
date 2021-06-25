<शैली गुरु>
/******************************************************************************
 * xenbus_xs.c
 *
 * This is the kernel equivalent of the "xs" library.  We करोn't need everything
 * and we use xenbus_comms क्रम communication.
 *
 * Copyright (C) 2005 Rusty Russell, IBM Corporation
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
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/unistd.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/uपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/reboot.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/xenbus.h>
#समावेश <xen/xen.h>
#समावेश "xenbus.h"

/*
 * Framework to protect suspend/resume handling against normal Xenstore
 * message handling:
 * During suspend/resume there must be no खोलो transaction and no pending
 * Xenstore request.
 * New watch events happening in this समय can be ignored by firing all watches
 * after resume.
 */

/* Lock protecting enter/निकास critical region. */
अटल DEFINE_SPINLOCK(xs_state_lock);
/* Number of users in critical region (रक्षित by xs_state_lock). */
अटल अचिन्हित पूर्णांक xs_state_users;
/* Suspend handler रुकोing or alपढ़ोy active (रक्षित by xs_state_lock)? */
अटल पूर्णांक xs_suspend_active;
/* Unique Xenstore request id (रक्षित by xs_state_lock). */
अटल uपूर्णांक32_t xs_request_id;

/* Wait queue क्रम all callers रुकोing क्रम critical region to become usable. */
अटल DECLARE_WAIT_QUEUE_HEAD(xs_state_enter_wq);
/* Wait queue क्रम suspend handling रुकोing क्रम critical region being empty. */
अटल DECLARE_WAIT_QUEUE_HEAD(xs_state_निकास_wq);

/* List of रेजिस्टरed watches, and a lock to protect it. */
अटल LIST_HEAD(watches);
अटल DEFINE_SPINLOCK(watches_lock);

/* List of pending watch callback events, and a lock to protect it. */
अटल LIST_HEAD(watch_events);
अटल DEFINE_SPINLOCK(watch_events_lock);

/* Protect watch (de)रेजिस्टर against save/restore. */
अटल DECLARE_RWSEM(xs_watch_rwsem);

/*
 * Details of the xenwatch callback kernel thपढ़ो. The thपढ़ो रुकोs on the
 * watch_events_रुकोq क्रम work to करो (queued on watch_events list). When it
 * wakes up it acquires the xenwatch_mutex beक्रमe पढ़ोing the list and
 * carrying out work.
 */
अटल pid_t xenwatch_pid;
अटल DEFINE_MUTEX(xenwatch_mutex);
अटल DECLARE_WAIT_QUEUE_HEAD(watch_events_रुकोq);

अटल व्योम xs_suspend_enter(व्योम)
अणु
	spin_lock(&xs_state_lock);
	xs_suspend_active++;
	spin_unlock(&xs_state_lock);
	रुको_event(xs_state_निकास_wq, xs_state_users == 0);
पूर्ण

अटल व्योम xs_suspend_निकास(व्योम)
अणु
	xb_dev_generation_id++;
	spin_lock(&xs_state_lock);
	xs_suspend_active--;
	spin_unlock(&xs_state_lock);
	wake_up_all(&xs_state_enter_wq);
पूर्ण

अटल uपूर्णांक32_t xs_request_enter(काष्ठा xb_req_data *req)
अणु
	uपूर्णांक32_t rq_id;

	req->type = req->msg.type;

	spin_lock(&xs_state_lock);

	जबतक (!xs_state_users && xs_suspend_active) अणु
		spin_unlock(&xs_state_lock);
		रुको_event(xs_state_enter_wq, xs_suspend_active == 0);
		spin_lock(&xs_state_lock);
	पूर्ण

	अगर (req->type == XS_TRANSACTION_START && !req->user_req)
		xs_state_users++;
	xs_state_users++;
	rq_id = xs_request_id++;

	spin_unlock(&xs_state_lock);

	वापस rq_id;
पूर्ण

व्योम xs_request_निकास(काष्ठा xb_req_data *req)
अणु
	spin_lock(&xs_state_lock);
	xs_state_users--;
	अगर ((req->type == XS_TRANSACTION_START && req->msg.type == XS_ERROR) ||
	    (req->type == XS_TRANSACTION_END && !req->user_req &&
	     !WARN_ON_ONCE(req->msg.type == XS_ERROR &&
			   !म_भेद(req->body, "ENOENT"))))
		xs_state_users--;
	spin_unlock(&xs_state_lock);

	अगर (xs_suspend_active && !xs_state_users)
		wake_up(&xs_state_निकास_wq);
पूर्ण

अटल पूर्णांक get_error(स्थिर अक्षर *errorstring)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; म_भेद(errorstring, xsd_errors[i].errstring) != 0; i++) अणु
		अगर (i == ARRAY_SIZE(xsd_errors) - 1) अणु
			pr_warn("xen store gave: unknown error %s\n",
				errorstring);
			वापस EINVAL;
		पूर्ण
	पूर्ण
	वापस xsd_errors[i].errnum;
पूर्ण

अटल bool xenbus_ok(व्योम)
अणु
	चयन (xen_store_करोमुख्य_type) अणु
	हाल XS_LOCAL:
		चयन (प्रणाली_state) अणु
		हाल SYSTEM_POWER_OFF:
		हाल SYSTEM_RESTART:
		हाल SYSTEM_HALT:
			वापस false;
		शेष:
			अवरोध;
		पूर्ण
		वापस true;
	हाल XS_PV:
	हाल XS_HVM:
		/* FIXME: Could check that the remote करोमुख्य is alive,
		 * but it is normally initial करोमुख्य. */
		वापस true;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

अटल bool test_reply(काष्ठा xb_req_data *req)
अणु
	अगर (req->state == xb_req_state_got_reply || !xenbus_ok()) अणु
		/* पढ़ो req->state beक्रमe all other fields */
		virt_rmb();
		वापस true;
	पूर्ण

	/* Make sure to reपढ़ो req->state each समय. */
	barrier();

	वापस false;
पूर्ण

अटल व्योम *पढ़ो_reply(काष्ठा xb_req_data *req)
अणु
	करो अणु
		रुको_event(req->wq, test_reply(req));

		अगर (!xenbus_ok())
			/*
			 * If we are in the process of being shut-करोwn there is
			 * no poपूर्णांक of trying to contact XenBus - it is either
			 * समाप्तed (xenstored application) or the other करोमुख्य
			 * has been समाप्तed or is unreachable.
			 */
			वापस ERR_PTR(-EIO);
		अगर (req->err)
			वापस ERR_PTR(req->err);

	पूर्ण जबतक (req->state != xb_req_state_got_reply);

	वापस req->body;
पूर्ण

अटल व्योम xs_send(काष्ठा xb_req_data *req, काष्ठा xsd_sockmsg *msg)
अणु
	bool notअगरy;

	req->msg = *msg;
	req->err = 0;
	req->state = xb_req_state_queued;
	init_रुकोqueue_head(&req->wq);

	/* Save the caller req_id and restore it later in the reply */
	req->caller_req_id = req->msg.req_id;
	req->msg.req_id = xs_request_enter(req);

	mutex_lock(&xb_ग_लिखो_mutex);
	list_add_tail(&req->list, &xb_ग_लिखो_list);
	notअगरy = list_is_singular(&xb_ग_लिखो_list);
	mutex_unlock(&xb_ग_लिखो_mutex);

	अगर (notअगरy)
		wake_up(&xb_रुकोq);
पूर्ण

अटल व्योम *xs_रुको_क्रम_reply(काष्ठा xb_req_data *req, काष्ठा xsd_sockmsg *msg)
अणु
	व्योम *ret;

	ret = पढ़ो_reply(req);

	xs_request_निकास(req);

	msg->type = req->msg.type;
	msg->len = req->msg.len;

	mutex_lock(&xb_ग_लिखो_mutex);
	अगर (req->state == xb_req_state_queued ||
	    req->state == xb_req_state_रुको_reply)
		req->state = xb_req_state_पातed;
	अन्यथा
		kमुक्त(req);
	mutex_unlock(&xb_ग_लिखो_mutex);

	वापस ret;
पूर्ण

अटल व्योम xs_wake_up(काष्ठा xb_req_data *req)
अणु
	wake_up(&req->wq);
पूर्ण

पूर्णांक xenbus_dev_request_and_reply(काष्ठा xsd_sockmsg *msg, व्योम *par)
अणु
	काष्ठा xb_req_data *req;
	काष्ठा kvec *vec;

	req = kदो_स्मृति(माप(*req) + माप(*vec), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	vec = (काष्ठा kvec *)(req + 1);
	vec->iov_len = msg->len;
	vec->iov_base = msg + 1;

	req->vec = vec;
	req->num_vecs = 1;
	req->cb = xenbus_dev_queue_reply;
	req->par = par;
	req->user_req = true;

	xs_send(req, msg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xenbus_dev_request_and_reply);

/* Send message to xs, get kदो_स्मृति'ed reply.  ERR_PTR() on error. */
अटल व्योम *xs_talkv(काष्ठा xenbus_transaction t,
		      क्रमागत xsd_sockmsg_type type,
		      स्थिर काष्ठा kvec *iovec,
		      अचिन्हित पूर्णांक num_vecs,
		      अचिन्हित पूर्णांक *len)
अणु
	काष्ठा xb_req_data *req;
	काष्ठा xsd_sockmsg msg;
	व्योम *ret = शून्य;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	req = kदो_स्मृति(माप(*req), GFP_NOIO | __GFP_HIGH);
	अगर (!req)
		वापस ERR_PTR(-ENOMEM);

	req->vec = iovec;
	req->num_vecs = num_vecs;
	req->cb = xs_wake_up;
	req->user_req = false;

	msg.req_id = 0;
	msg.tx_id = t.id;
	msg.type = type;
	msg.len = 0;
	क्रम (i = 0; i < num_vecs; i++)
		msg.len += iovec[i].iov_len;

	xs_send(req, &msg);

	ret = xs_रुको_क्रम_reply(req, &msg);
	अगर (len)
		*len = msg.len;

	अगर (IS_ERR(ret))
		वापस ret;

	अगर (msg.type == XS_ERROR) अणु
		err = get_error(ret);
		kमुक्त(ret);
		वापस ERR_PTR(-err);
	पूर्ण

	अगर (msg.type != type) अणु
		pr_warn_ratelimited("unexpected type [%d], expected [%d]\n",
				    msg.type, type);
		kमुक्त(ret);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	वापस ret;
पूर्ण

/* Simplअगरied version of xs_talkv: single message. */
अटल व्योम *xs_single(काष्ठा xenbus_transaction t,
		       क्रमागत xsd_sockmsg_type type,
		       स्थिर अक्षर *string,
		       अचिन्हित पूर्णांक *len)
अणु
	काष्ठा kvec iovec;

	iovec.iov_base = (व्योम *)string;
	iovec.iov_len = म_माप(string) + 1;
	वापस xs_talkv(t, type, &iovec, 1, len);
पूर्ण

/* Many commands only need an ack, करोn't care what it says. */
अटल पूर्णांक xs_error(अक्षर *reply)
अणु
	अगर (IS_ERR(reply))
		वापस PTR_ERR(reply);
	kमुक्त(reply);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक count_strings(स्थिर अक्षर *strings, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक num;
	स्थिर अक्षर *p;

	क्रम (p = strings, num = 0; p < strings + len; p += म_माप(p) + 1)
		num++;

	वापस num;
पूर्ण

/* Return the path to dir with /name appended. Buffer must be kमुक्त()'ed. */
अटल अक्षर *join(स्थिर अक्षर *dir, स्थिर अक्षर *name)
अणु
	अक्षर *buffer;

	अगर (म_माप(name) == 0)
		buffer = kaप्र_लिखो(GFP_NOIO | __GFP_HIGH, "%s", dir);
	अन्यथा
		buffer = kaप्र_लिखो(GFP_NOIO | __GFP_HIGH, "%s/%s", dir, name);
	वापस (!buffer) ? ERR_PTR(-ENOMEM) : buffer;
पूर्ण

अटल अक्षर **split(अक्षर *strings, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक *num)
अणु
	अक्षर *p, **ret;

	/* Count the strings. */
	*num = count_strings(strings, len);

	/* Transfer to one big alloc क्रम easy मुक्तing. */
	ret = kदो_स्मृति(*num * माप(अक्षर *) + len, GFP_NOIO | __GFP_HIGH);
	अगर (!ret) अणु
		kमुक्त(strings);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	स_नकल(&ret[*num], strings, len);
	kमुक्त(strings);

	strings = (अक्षर *)&ret[*num];
	क्रम (p = strings, *num = 0; p < strings + len; p += म_माप(p) + 1)
		ret[(*num)++] = p;

	वापस ret;
पूर्ण

अक्षर **xenbus_directory(काष्ठा xenbus_transaction t,
			स्थिर अक्षर *dir, स्थिर अक्षर *node, अचिन्हित पूर्णांक *num)
अणु
	अक्षर *strings, *path;
	अचिन्हित पूर्णांक len;

	path = join(dir, node);
	अगर (IS_ERR(path))
		वापस (अक्षर **)path;

	strings = xs_single(t, XS_सूचीECTORY, path, &len);
	kमुक्त(path);
	अगर (IS_ERR(strings))
		वापस (अक्षर **)strings;

	वापस split(strings, len, num);
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_directory);

/* Check अगर a path exists. Return 1 अगर it करोes. */
पूर्णांक xenbus_exists(काष्ठा xenbus_transaction t,
		  स्थिर अक्षर *dir, स्थिर अक्षर *node)
अणु
	अक्षर **d;
	पूर्णांक dir_n;

	d = xenbus_directory(t, dir, node, &dir_n);
	अगर (IS_ERR(d))
		वापस 0;
	kमुक्त(d);
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_exists);

/* Get the value of a single file.
 * Returns a kदो_स्मृतिed value: call मुक्त() on it after use.
 * len indicates length in bytes.
 */
व्योम *xenbus_पढ़ो(काष्ठा xenbus_transaction t,
		  स्थिर अक्षर *dir, स्थिर अक्षर *node, अचिन्हित पूर्णांक *len)
अणु
	अक्षर *path;
	व्योम *ret;

	path = join(dir, node);
	अगर (IS_ERR(path))
		वापस (व्योम *)path;

	ret = xs_single(t, XS_READ, path, len);
	kमुक्त(path);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_पढ़ो);

/* Write the value of a single file.
 * Returns -err on failure.
 */
पूर्णांक xenbus_ग_लिखो(काष्ठा xenbus_transaction t,
		 स्थिर अक्षर *dir, स्थिर अक्षर *node, स्थिर अक्षर *string)
अणु
	स्थिर अक्षर *path;
	काष्ठा kvec iovec[2];
	पूर्णांक ret;

	path = join(dir, node);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	iovec[0].iov_base = (व्योम *)path;
	iovec[0].iov_len = म_माप(path) + 1;
	iovec[1].iov_base = (व्योम *)string;
	iovec[1].iov_len = म_माप(string);

	ret = xs_error(xs_talkv(t, XS_WRITE, iovec, ARRAY_SIZE(iovec), शून्य));
	kमुक्त(path);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_ग_लिखो);

/* Create a new directory. */
पूर्णांक xenbus_सूची_गढ़ो(काष्ठा xenbus_transaction t,
		 स्थिर अक्षर *dir, स्थिर अक्षर *node)
अणु
	अक्षर *path;
	पूर्णांक ret;

	path = join(dir, node);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	ret = xs_error(xs_single(t, XS_MKसूची, path, शून्य));
	kमुक्त(path);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_सूची_गढ़ो);

/* Destroy a file or directory (directories must be empty). */
पूर्णांक xenbus_rm(काष्ठा xenbus_transaction t, स्थिर अक्षर *dir, स्थिर अक्षर *node)
अणु
	अक्षर *path;
	पूर्णांक ret;

	path = join(dir, node);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	ret = xs_error(xs_single(t, XS_RM, path, शून्य));
	kमुक्त(path);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_rm);

/* Start a transaction: changes by others will not be seen during this
 * transaction, and changes will not be visible to others until end.
 */
पूर्णांक xenbus_transaction_start(काष्ठा xenbus_transaction *t)
अणु
	अक्षर *id_str;

	id_str = xs_single(XBT_NIL, XS_TRANSACTION_START, "", शून्य);
	अगर (IS_ERR(id_str))
		वापस PTR_ERR(id_str);

	t->id = simple_म_से_अदीर्घ(id_str, शून्य, 0);
	kमुक्त(id_str);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_transaction_start);

/* End a transaction.
 * If abanकरोn is true, transaction is discarded instead of committed.
 */
पूर्णांक xenbus_transaction_end(काष्ठा xenbus_transaction t, पूर्णांक पात)
अणु
	अक्षर पातstr[2];

	अगर (पात)
		म_नकल(पातstr, "F");
	अन्यथा
		म_नकल(पातstr, "T");

	वापस xs_error(xs_single(t, XS_TRANSACTION_END, पातstr, शून्य));
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_transaction_end);

/* Single पढ़ो and म_पूछो: वापसs -त्रुटि_सं or num scanned. */
पूर्णांक xenbus_म_पूछो(काष्ठा xenbus_transaction t,
		 स्थिर अक्षर *dir, स्थिर अक्षर *node, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;
	अक्षर *val;

	val = xenbus_पढ़ो(t, dir, node, शून्य);
	अगर (IS_ERR(val))
		वापस PTR_ERR(val);

	बहु_शुरू(ap, fmt);
	ret = vमाला_पूछो(val, fmt, ap);
	बहु_पूर्ण(ap);
	kमुक्त(val);
	/* Distinctive त्रुटि_सं. */
	अगर (ret == 0)
		वापस -दुस्फल;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_म_पूछो);

/* Read an (optional) अचिन्हित value. */
अचिन्हित पूर्णांक xenbus_पढ़ो_अचिन्हित(स्थिर अक्षर *dir, स्थिर अक्षर *node,
				  अचिन्हित पूर्णांक शेष_val)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = xenbus_म_पूछो(XBT_NIL, dir, node, "%u", &val);
	अगर (ret <= 0)
		val = शेष_val;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_पढ़ो_अचिन्हित);

/* Single म_लिखो and ग_लिखो: वापसs -त्रुटि_सं or 0. */
पूर्णांक xenbus_म_लिखो(काष्ठा xenbus_transaction t,
		  स्थिर अक्षर *dir, स्थिर अक्षर *node, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;
	अक्षर *buf;

	बहु_शुरू(ap, fmt);
	buf = kvaप्र_लिखो(GFP_NOIO | __GFP_HIGH, fmt, ap);
	बहु_पूर्ण(ap);

	अगर (!buf)
		वापस -ENOMEM;

	ret = xenbus_ग_लिखो(t, dir, node, buf);

	kमुक्त(buf);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_म_लिखो);

/* Takes tuples of names, म_पूछो-style args, and व्योम **, शून्य terminated. */
पूर्णांक xenbus_gather(काष्ठा xenbus_transaction t, स्थिर अक्षर *dir, ...)
अणु
	बहु_सूची ap;
	स्थिर अक्षर *name;
	पूर्णांक ret = 0;

	बहु_शुरू(ap, dir);
	जबतक (ret == 0 && (name = बहु_तर्क(ap, अक्षर *)) != शून्य) अणु
		स्थिर अक्षर *fmt = बहु_तर्क(ap, अक्षर *);
		व्योम *result = बहु_तर्क(ap, व्योम *);
		अक्षर *p;

		p = xenbus_पढ़ो(t, dir, name, शून्य);
		अगर (IS_ERR(p)) अणु
			ret = PTR_ERR(p);
			अवरोध;
		पूर्ण
		अगर (fmt) अणु
			अगर (माला_पूछो(p, fmt, result) == 0)
				ret = -EINVAL;
			kमुक्त(p);
		पूर्ण अन्यथा
			*(अक्षर **)result = p;
	पूर्ण
	बहु_पूर्ण(ap);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(xenbus_gather);

अटल पूर्णांक xs_watch(स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	काष्ठा kvec iov[2];

	iov[0].iov_base = (व्योम *)path;
	iov[0].iov_len = म_माप(path) + 1;
	iov[1].iov_base = (व्योम *)token;
	iov[1].iov_len = म_माप(token) + 1;

	वापस xs_error(xs_talkv(XBT_NIL, XS_WATCH, iov,
				 ARRAY_SIZE(iov), शून्य));
पूर्ण

अटल पूर्णांक xs_unwatch(स्थिर अक्षर *path, स्थिर अक्षर *token)
अणु
	काष्ठा kvec iov[2];

	iov[0].iov_base = (अक्षर *)path;
	iov[0].iov_len = म_माप(path) + 1;
	iov[1].iov_base = (अक्षर *)token;
	iov[1].iov_len = म_माप(token) + 1;

	वापस xs_error(xs_talkv(XBT_NIL, XS_UNWATCH, iov,
				 ARRAY_SIZE(iov), शून्य));
पूर्ण

अटल काष्ठा xenbus_watch *find_watch(स्थिर अक्षर *token)
अणु
	काष्ठा xenbus_watch *i, *cmp;

	cmp = (व्योम *)simple_म_से_अदीर्घ(token, शून्य, 16);

	list_क्रम_each_entry(i, &watches, list)
		अगर (i == cmp)
			वापस i;

	वापस शून्य;
पूर्ण

पूर्णांक xs_watch_msg(काष्ठा xs_watch_event *event)
अणु
	अगर (count_strings(event->body, event->len) != 2) अणु
		kमुक्त(event);
		वापस -EINVAL;
	पूर्ण
	event->path = (स्थिर अक्षर *)event->body;
	event->token = (स्थिर अक्षर *)म_अक्षर(event->body, '\0') + 1;

	spin_lock(&watches_lock);
	event->handle = find_watch(event->token);
	अगर (event->handle != शून्य &&
			(!event->handle->will_handle ||
			 event->handle->will_handle(event->handle,
				 event->path, event->token))) अणु
		spin_lock(&watch_events_lock);
		list_add_tail(&event->list, &watch_events);
		event->handle->nr_pending++;
		wake_up(&watch_events_रुकोq);
		spin_unlock(&watch_events_lock);
	पूर्ण अन्यथा
		kमुक्त(event);
	spin_unlock(&watches_lock);

	वापस 0;
पूर्ण

/*
 * Certain older XenBus toolstack cannot handle पढ़ोing values that are
 * not populated. Some Xen 3.4 installation are incapable of करोing this
 * so अगर we are running on anything older than 4 करो not attempt to पढ़ो
 * control/platक्रमm-feature-xs_reset_watches.
 */
अटल bool xen_strict_xenbus_quirk(व्योम)
अणु
#अगर_घोषित CONFIG_X86
	uपूर्णांक32_t eax, ebx, ecx, edx, base;

	base = xen_cpuid_base();
	cpuid(base + 1, &eax, &ebx, &ecx, &edx);

	अगर ((eax >> 16) < 4)
		वापस true;
#पूर्ण_अगर
	वापस false;

पूर्ण
अटल व्योम xs_reset_watches(व्योम)
अणु
	पूर्णांक err;

	अगर (!xen_hvm_करोमुख्य() || xen_initial_करोमुख्य())
		वापस;

	अगर (xen_strict_xenbus_quirk())
		वापस;

	अगर (!xenbus_पढ़ो_अचिन्हित("control",
				  "platform-feature-xs_reset_watches", 0))
		वापस;

	err = xs_error(xs_single(XBT_NIL, XS_RESET_WATCHES, "", शून्य));
	अगर (err && err != -EEXIST)
		pr_warn("xs_reset_watches failed: %d\n", err);
पूर्ण

/* Register callback to watch this node. */
पूर्णांक रेजिस्टर_xenbus_watch(काष्ठा xenbus_watch *watch)
अणु
	/* Poपूर्णांकer in ascii is the token. */
	अक्षर token[माप(watch) * 2 + 1];
	पूर्णांक err;

	प्र_लिखो(token, "%lX", (दीर्घ)watch);

	watch->nr_pending = 0;

	करोwn_पढ़ो(&xs_watch_rwsem);

	spin_lock(&watches_lock);
	BUG_ON(find_watch(token));
	list_add(&watch->list, &watches);
	spin_unlock(&watches_lock);

	err = xs_watch(watch->node, token);

	अगर (err) अणु
		spin_lock(&watches_lock);
		list_del(&watch->list);
		spin_unlock(&watches_lock);
	पूर्ण

	up_पढ़ो(&xs_watch_rwsem);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_xenbus_watch);

व्योम unरेजिस्टर_xenbus_watch(काष्ठा xenbus_watch *watch)
अणु
	काष्ठा xs_watch_event *event, *पंचांगp;
	अक्षर token[माप(watch) * 2 + 1];
	पूर्णांक err;

	प्र_लिखो(token, "%lX", (दीर्घ)watch);

	करोwn_पढ़ो(&xs_watch_rwsem);

	spin_lock(&watches_lock);
	BUG_ON(!find_watch(token));
	list_del(&watch->list);
	spin_unlock(&watches_lock);

	err = xs_unwatch(watch->node, token);
	अगर (err)
		pr_warn("Failed to release watch %s: %i\n", watch->node, err);

	up_पढ़ो(&xs_watch_rwsem);

	/* Make sure there are no callbacks running currently (unless
	   its us) */
	अगर (current->pid != xenwatch_pid)
		mutex_lock(&xenwatch_mutex);

	/* Cancel pending watch events. */
	spin_lock(&watch_events_lock);
	अगर (watch->nr_pending) अणु
		list_क्रम_each_entry_safe(event, पंचांगp, &watch_events, list) अणु
			अगर (event->handle != watch)
				जारी;
			list_del(&event->list);
			kमुक्त(event);
		पूर्ण
		watch->nr_pending = 0;
	पूर्ण
	spin_unlock(&watch_events_lock);

	अगर (current->pid != xenwatch_pid)
		mutex_unlock(&xenwatch_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_xenbus_watch);

व्योम xs_suspend(व्योम)
अणु
	xs_suspend_enter();

	करोwn_ग_लिखो(&xs_watch_rwsem);
	mutex_lock(&xs_response_mutex);
पूर्ण

व्योम xs_resume(व्योम)
अणु
	काष्ठा xenbus_watch *watch;
	अक्षर token[माप(watch) * 2 + 1];

	xb_init_comms();

	mutex_unlock(&xs_response_mutex);

	xs_suspend_निकास();

	/* No need क्रम watches_lock: the xs_watch_rwsem is sufficient. */
	list_क्रम_each_entry(watch, &watches, list) अणु
		प्र_लिखो(token, "%lX", (दीर्घ)watch);
		xs_watch(watch->node, token);
	पूर्ण

	up_ग_लिखो(&xs_watch_rwsem);
पूर्ण

व्योम xs_suspend_cancel(व्योम)
अणु
	mutex_unlock(&xs_response_mutex);
	up_ग_लिखो(&xs_watch_rwsem);

	xs_suspend_निकास();
पूर्ण

अटल पूर्णांक xenwatch_thपढ़ो(व्योम *unused)
अणु
	काष्ठा xs_watch_event *event;

	xenwatch_pid = current->pid;

	क्रम (;;) अणु
		रुको_event_पूर्णांकerruptible(watch_events_रुकोq,
					 !list_empty(&watch_events));

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		mutex_lock(&xenwatch_mutex);

		spin_lock(&watch_events_lock);
		event = list_first_entry_or_null(&watch_events,
				काष्ठा xs_watch_event, list);
		अगर (event) अणु
			list_del(&event->list);
			event->handle->nr_pending--;
		पूर्ण
		spin_unlock(&watch_events_lock);

		अगर (event) अणु
			event->handle->callback(event->handle, event->path,
						event->token);
			kमुक्त(event);
		पूर्ण

		mutex_unlock(&xenwatch_mutex);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wake up all thपढ़ोs रुकोing क्रम a xenstore reply. In हाल of shutकरोwn all
 * pending replies will be marked as "aborted" in order to let the रुकोers
 * वापस in spite of xenstore possibly no दीर्घer being able to reply. This
 * will aव्योम blocking shutकरोwn by a thपढ़ो रुकोing क्रम xenstore but being
 * necessary क्रम shutकरोwn processing to proceed.
 */
अटल पूर्णांक xs_reboot_notअगरy(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ code, व्योम *unused)
अणु
	काष्ठा xb_req_data *req;

	mutex_lock(&xb_ग_लिखो_mutex);
	list_क्रम_each_entry(req, &xs_reply_list, list)
		wake_up(&req->wq);
	list_क्रम_each_entry(req, &xb_ग_लिखो_list, list)
		wake_up(&req->wq);
	mutex_unlock(&xb_ग_लिखो_mutex);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block xs_reboot_nb = अणु
	.notअगरier_call = xs_reboot_notअगरy,
पूर्ण;

पूर्णांक xs_init(व्योम)
अणु
	पूर्णांक err;
	काष्ठा task_काष्ठा *task;

	रेजिस्टर_reboot_notअगरier(&xs_reboot_nb);

	/* Initialize the shared memory rings to talk to xenstored */
	err = xb_init_comms();
	अगर (err)
		वापस err;

	task = kthपढ़ो_run(xenwatch_thपढ़ो, शून्य, "xenwatch");
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);

	/* shutकरोwn watches क्रम kexec boot */
	xs_reset_watches();

	वापस 0;
पूर्ण
