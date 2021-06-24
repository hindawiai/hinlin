<शैली गुरु>
/******************************************************************************
 * xenbus_comms.c
 *
 * Low level code to talks to Xen Store: ringbuffer and event channel.
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

#समावेश <linux/रुको.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <xen/xenbus.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <xen/events.h>
#समावेश <xen/page.h>
#समावेश "xenbus.h"

/* A list of replies. Currently only one will ever be outstanding. */
LIST_HEAD(xs_reply_list);

/* A list of ग_लिखो requests. */
LIST_HEAD(xb_ग_लिखो_list);
DECLARE_WAIT_QUEUE_HEAD(xb_रुकोq);
DEFINE_MUTEX(xb_ग_लिखो_mutex);

/* Protect xenbus पढ़ोer thपढ़ो against save/restore. */
DEFINE_MUTEX(xs_response_mutex);

अटल पूर्णांक xenbus_irq;
अटल काष्ठा task_काष्ठा *xenbus_task;

अटल irqवापस_t wake_रुकोing(पूर्णांक irq, व्योम *unused)
अणु
	wake_up(&xb_रुकोq);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक check_indexes(XENSTORE_RING_IDX cons, XENSTORE_RING_IDX prod)
अणु
	वापस ((prod - cons) <= XENSTORE_RING_SIZE);
पूर्ण

अटल व्योम *get_output_chunk(XENSTORE_RING_IDX cons,
			      XENSTORE_RING_IDX prod,
			      अक्षर *buf, uपूर्णांक32_t *len)
अणु
	*len = XENSTORE_RING_SIZE - MASK_XENSTORE_IDX(prod);
	अगर ((XENSTORE_RING_SIZE - (prod - cons)) < *len)
		*len = XENSTORE_RING_SIZE - (prod - cons);
	वापस buf + MASK_XENSTORE_IDX(prod);
पूर्ण

अटल स्थिर व्योम *get_input_chunk(XENSTORE_RING_IDX cons,
				   XENSTORE_RING_IDX prod,
				   स्थिर अक्षर *buf, uपूर्णांक32_t *len)
अणु
	*len = XENSTORE_RING_SIZE - MASK_XENSTORE_IDX(cons);
	अगर ((prod - cons) < *len)
		*len = prod - cons;
	वापस buf + MASK_XENSTORE_IDX(cons);
पूर्ण

अटल पूर्णांक xb_data_to_ग_लिखो(व्योम)
अणु
	काष्ठा xenstore_करोमुख्य_पूर्णांकerface *पूर्णांकf = xen_store_पूर्णांकerface;

	वापस (पूर्णांकf->req_prod - पूर्णांकf->req_cons) != XENSTORE_RING_SIZE &&
		!list_empty(&xb_ग_लिखो_list);
पूर्ण

/**
 * xb_ग_लिखो - low level ग_लिखो
 * @data: buffer to send
 * @len: length of buffer
 *
 * Returns number of bytes written or -err.
 */
अटल पूर्णांक xb_ग_लिखो(स्थिर व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xenstore_करोमुख्य_पूर्णांकerface *पूर्णांकf = xen_store_पूर्णांकerface;
	XENSTORE_RING_IDX cons, prod;
	अचिन्हित पूर्णांक bytes = 0;

	जबतक (len != 0) अणु
		व्योम *dst;
		अचिन्हित पूर्णांक avail;

		/* Read indexes, then verअगरy. */
		cons = पूर्णांकf->req_cons;
		prod = पूर्णांकf->req_prod;
		अगर (!check_indexes(cons, prod)) अणु
			पूर्णांकf->req_cons = पूर्णांकf->req_prod = 0;
			वापस -EIO;
		पूर्ण
		अगर (!xb_data_to_ग_लिखो())
			वापस bytes;

		/* Must ग_लिखो data /after/ पढ़ोing the consumer index. */
		virt_mb();

		dst = get_output_chunk(cons, prod, पूर्णांकf->req, &avail);
		अगर (avail == 0)
			जारी;
		अगर (avail > len)
			avail = len;

		स_नकल(dst, data, avail);
		data += avail;
		len -= avail;
		bytes += avail;

		/* Other side must not see new producer until data is there. */
		virt_wmb();
		पूर्णांकf->req_prod += avail;

		/* Implies mb(): other side will see the updated producer. */
		अगर (prod <= पूर्णांकf->req_cons)
			notअगरy_remote_via_evtchn(xen_store_evtchn);
	पूर्ण

	वापस bytes;
पूर्ण

अटल पूर्णांक xb_data_to_पढ़ो(व्योम)
अणु
	काष्ठा xenstore_करोमुख्य_पूर्णांकerface *पूर्णांकf = xen_store_पूर्णांकerface;
	वापस (पूर्णांकf->rsp_cons != पूर्णांकf->rsp_prod);
पूर्ण

अटल पूर्णांक xb_पढ़ो(व्योम *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा xenstore_करोमुख्य_पूर्णांकerface *पूर्णांकf = xen_store_पूर्णांकerface;
	XENSTORE_RING_IDX cons, prod;
	अचिन्हित पूर्णांक bytes = 0;

	जबतक (len != 0) अणु
		अचिन्हित पूर्णांक avail;
		स्थिर अक्षर *src;

		/* Read indexes, then verअगरy. */
		cons = पूर्णांकf->rsp_cons;
		prod = पूर्णांकf->rsp_prod;
		अगर (cons == prod)
			वापस bytes;

		अगर (!check_indexes(cons, prod)) अणु
			पूर्णांकf->rsp_cons = पूर्णांकf->rsp_prod = 0;
			वापस -EIO;
		पूर्ण

		src = get_input_chunk(cons, prod, पूर्णांकf->rsp, &avail);
		अगर (avail == 0)
			जारी;
		अगर (avail > len)
			avail = len;

		/* Must पढ़ो data /after/ पढ़ोing the producer index. */
		virt_rmb();

		स_नकल(data, src, avail);
		data += avail;
		len -= avail;
		bytes += avail;

		/* Other side must not see मुक्त space until we've copied out */
		virt_mb();
		पूर्णांकf->rsp_cons += avail;

		/* Implies mb(): other side will see the updated consumer. */
		अगर (पूर्णांकf->rsp_prod - cons >= XENSTORE_RING_SIZE)
			notअगरy_remote_via_evtchn(xen_store_evtchn);
	पूर्ण

	वापस bytes;
पूर्ण

अटल पूर्णांक process_msg(व्योम)
अणु
	अटल काष्ठा अणु
		काष्ठा xsd_sockmsg msg;
		अक्षर *body;
		जोड़ अणु
			व्योम *alloc;
			काष्ठा xs_watch_event *watch;
		पूर्ण;
		bool in_msg;
		bool in_hdr;
		अचिन्हित पूर्णांक पढ़ो;
	पूर्ण state;
	काष्ठा xb_req_data *req;
	पूर्णांक err;
	अचिन्हित पूर्णांक len;

	अगर (!state.in_msg) अणु
		state.in_msg = true;
		state.in_hdr = true;
		state.पढ़ो = 0;

		/*
		 * We must disallow save/restore जबतक पढ़ोing a message.
		 * A partial पढ़ो across s/r leaves us out of sync with
		 * xenstored.
		 * xs_response_mutex is locked as दीर्घ as we are processing one
		 * message. state.in_msg will be true as दीर्घ as we are holding
		 * the lock here.
		 */
		mutex_lock(&xs_response_mutex);

		अगर (!xb_data_to_पढ़ो()) अणु
			/* We raced with save/restore: pending data 'gone'. */
			mutex_unlock(&xs_response_mutex);
			state.in_msg = false;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (state.in_hdr) अणु
		अगर (state.पढ़ो != माप(state.msg)) अणु
			err = xb_पढ़ो((व्योम *)&state.msg + state.पढ़ो,
				      माप(state.msg) - state.पढ़ो);
			अगर (err < 0)
				जाओ out;
			state.पढ़ो += err;
			अगर (state.पढ़ो != माप(state.msg))
				वापस 0;
			अगर (state.msg.len > XENSTORE_PAYLOAD_MAX) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण

		len = state.msg.len + 1;
		अगर (state.msg.type == XS_WATCH_EVENT)
			len += माप(*state.watch);

		state.alloc = kदो_स्मृति(len, GFP_NOIO | __GFP_HIGH);
		अगर (!state.alloc)
			वापस -ENOMEM;

		अगर (state.msg.type == XS_WATCH_EVENT)
			state.body = state.watch->body;
		अन्यथा
			state.body = state.alloc;
		state.in_hdr = false;
		state.पढ़ो = 0;
	पूर्ण

	err = xb_पढ़ो(state.body + state.पढ़ो, state.msg.len - state.पढ़ो);
	अगर (err < 0)
		जाओ out;

	state.पढ़ो += err;
	अगर (state.पढ़ो != state.msg.len)
		वापस 0;

	state.body[state.msg.len] = '\0';

	अगर (state.msg.type == XS_WATCH_EVENT) अणु
		state.watch->len = state.msg.len;
		err = xs_watch_msg(state.watch);
	पूर्ण अन्यथा अणु
		err = -ENOENT;
		mutex_lock(&xb_ग_लिखो_mutex);
		list_क्रम_each_entry(req, &xs_reply_list, list) अणु
			अगर (req->msg.req_id == state.msg.req_id) अणु
				list_del(&req->list);
				err = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		mutex_unlock(&xb_ग_लिखो_mutex);
		अगर (err)
			जाओ out;

		अगर (req->state == xb_req_state_रुको_reply) अणु
			req->msg.req_id = req->caller_req_id;
			req->msg.type = state.msg.type;
			req->msg.len = state.msg.len;
			req->body = state.body;
			/* ग_लिखो body, then update state */
			virt_wmb();
			req->state = xb_req_state_got_reply;
			req->cb(req);
		पूर्ण अन्यथा
			kमुक्त(req);
	पूर्ण

	mutex_unlock(&xs_response_mutex);

	state.in_msg = false;
	state.alloc = शून्य;
	वापस err;

 out:
	mutex_unlock(&xs_response_mutex);
	state.in_msg = false;
	kमुक्त(state.alloc);
	state.alloc = शून्य;
	वापस err;
पूर्ण

अटल पूर्णांक process_ग_लिखोs(व्योम)
अणु
	अटल काष्ठा अणु
		काष्ठा xb_req_data *req;
		पूर्णांक idx;
		अचिन्हित पूर्णांक written;
	पूर्ण state;
	व्योम *base;
	अचिन्हित पूर्णांक len;
	पूर्णांक err = 0;

	अगर (!xb_data_to_ग_लिखो())
		वापस 0;

	mutex_lock(&xb_ग_लिखो_mutex);

	अगर (!state.req) अणु
		state.req = list_first_entry(&xb_ग_लिखो_list,
					     काष्ठा xb_req_data, list);
		state.idx = -1;
		state.written = 0;
	पूर्ण

	अगर (state.req->state == xb_req_state_पातed)
		जाओ out_err;

	जबतक (state.idx < state.req->num_vecs) अणु
		अगर (state.idx < 0) अणु
			base = &state.req->msg;
			len = माप(state.req->msg);
		पूर्ण अन्यथा अणु
			base = state.req->vec[state.idx].iov_base;
			len = state.req->vec[state.idx].iov_len;
		पूर्ण
		err = xb_ग_लिखो(base + state.written, len - state.written);
		अगर (err < 0)
			जाओ out_err;
		state.written += err;
		अगर (state.written != len)
			जाओ out;

		state.idx++;
		state.written = 0;
	पूर्ण

	list_del(&state.req->list);
	state.req->state = xb_req_state_रुको_reply;
	list_add_tail(&state.req->list, &xs_reply_list);
	state.req = शून्य;

 out:
	mutex_unlock(&xb_ग_लिखो_mutex);

	वापस 0;

 out_err:
	state.req->msg.type = XS_ERROR;
	state.req->err = err;
	list_del(&state.req->list);
	अगर (state.req->state == xb_req_state_पातed)
		kमुक्त(state.req);
	अन्यथा अणु
		/* ग_लिखो err, then update state */
		virt_wmb();
		state.req->state = xb_req_state_got_reply;
		wake_up(&state.req->wq);
	पूर्ण

	mutex_unlock(&xb_ग_लिखो_mutex);

	state.req = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक xb_thपढ़ो_work(व्योम)
अणु
	वापस xb_data_to_पढ़ो() || xb_data_to_ग_लिखो();
पूर्ण

अटल पूर्णांक xenbus_thपढ़ो(व्योम *unused)
अणु
	पूर्णांक err;

	जबतक (!kthपढ़ो_should_stop()) अणु
		अगर (रुको_event_पूर्णांकerruptible(xb_रुकोq, xb_thपढ़ो_work()))
			जारी;

		err = process_msg();
		अगर (err == -ENOMEM)
			schedule();
		अन्यथा अगर (err)
			pr_warn_ratelimited("error %d while reading message\n",
					    err);

		err = process_ग_लिखोs();
		अगर (err)
			pr_warn_ratelimited("error %d while writing message\n",
					    err);
	पूर्ण

	xenbus_task = शून्य;
	वापस 0;
पूर्ण

/**
 * xb_init_comms - Set up पूर्णांकerrupt handler off store event channel.
 */
पूर्णांक xb_init_comms(व्योम)
अणु
	काष्ठा xenstore_करोमुख्य_पूर्णांकerface *पूर्णांकf = xen_store_पूर्णांकerface;

	अगर (पूर्णांकf->req_prod != पूर्णांकf->req_cons)
		pr_err("request ring is not quiescent (%08x:%08x)!\n",
		       पूर्णांकf->req_cons, पूर्णांकf->req_prod);

	अगर (पूर्णांकf->rsp_prod != पूर्णांकf->rsp_cons) अणु
		pr_warn("response ring is not quiescent (%08x:%08x): fixing up\n",
			पूर्णांकf->rsp_cons, पूर्णांकf->rsp_prod);
		/* अवरोधs kdump */
		अगर (!reset_devices)
			पूर्णांकf->rsp_cons = पूर्णांकf->rsp_prod;
	पूर्ण

	अगर (xenbus_irq) अणु
		/* Alपढ़ोy have an irq; assume we're resuming */
		rebind_evtchn_irq(xen_store_evtchn, xenbus_irq);
	पूर्ण अन्यथा अणु
		पूर्णांक err;

		err = bind_evtchn_to_irqhandler(xen_store_evtchn, wake_रुकोing,
						0, "xenbus", &xb_रुकोq);
		अगर (err < 0) अणु
			pr_err("request irq failed %i\n", err);
			वापस err;
		पूर्ण

		xenbus_irq = err;

		अगर (!xenbus_task) अणु
			xenbus_task = kthपढ़ो_run(xenbus_thपढ़ो, शून्य,
						  "xenbus");
			अगर (IS_ERR(xenbus_task))
				वापस PTR_ERR(xenbus_task);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम xb_deinit_comms(व्योम)
अणु
	unbind_from_irqhandler(xenbus_irq, &xb_रुकोq);
	xenbus_irq = 0;
पूर्ण
