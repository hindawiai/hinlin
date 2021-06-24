<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017 - 2018 Covalent IO, Inc. http://covalent.io */

#समावेश <linux/skmsg.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/scatterlist.h>

#समावेश <net/sock.h>
#समावेश <net/tcp.h>
#समावेश <net/tls.h>

अटल bool sk_msg_try_coalesce_ok(काष्ठा sk_msg *msg, पूर्णांक elem_first_coalesce)
अणु
	अगर (msg->sg.end > msg->sg.start &&
	    elem_first_coalesce < msg->sg.end)
		वापस true;

	अगर (msg->sg.end < msg->sg.start &&
	    (elem_first_coalesce > msg->sg.start ||
	     elem_first_coalesce < msg->sg.end))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक sk_msg_alloc(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक len,
		 पूर्णांक elem_first_coalesce)
अणु
	काष्ठा page_frag *pfrag = sk_page_frag(sk);
	पूर्णांक ret = 0;

	len -= msg->sg.size;
	जबतक (len > 0) अणु
		काष्ठा scatterlist *sge;
		u32 orig_offset;
		पूर्णांक use, i;

		अगर (!sk_page_frag_refill(sk, pfrag))
			वापस -ENOMEM;

		orig_offset = pfrag->offset;
		use = min_t(पूर्णांक, len, pfrag->size - orig_offset);
		अगर (!sk_wmem_schedule(sk, use))
			वापस -ENOMEM;

		i = msg->sg.end;
		sk_msg_iter_var_prev(i);
		sge = &msg->sg.data[i];

		अगर (sk_msg_try_coalesce_ok(msg, elem_first_coalesce) &&
		    sg_page(sge) == pfrag->page &&
		    sge->offset + sge->length == orig_offset) अणु
			sge->length += use;
		पूर्ण अन्यथा अणु
			अगर (sk_msg_full(msg)) अणु
				ret = -ENOSPC;
				अवरोध;
			पूर्ण

			sge = &msg->sg.data[msg->sg.end];
			sg_unmark_end(sge);
			sg_set_page(sge, pfrag->page, use, orig_offset);
			get_page(pfrag->page);
			sk_msg_iter_next(msg, end);
		पूर्ण

		sk_mem_अक्षरge(sk, use);
		msg->sg.size += use;
		pfrag->offset += use;
		len -= use;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_alloc);

पूर्णांक sk_msg_clone(काष्ठा sock *sk, काष्ठा sk_msg *dst, काष्ठा sk_msg *src,
		 u32 off, u32 len)
अणु
	पूर्णांक i = src->sg.start;
	काष्ठा scatterlist *sge = sk_msg_elem(src, i);
	काष्ठा scatterlist *sgd = शून्य;
	u32 sge_len, sge_off;

	जबतक (off) अणु
		अगर (sge->length > off)
			अवरोध;
		off -= sge->length;
		sk_msg_iter_var_next(i);
		अगर (i == src->sg.end && off)
			वापस -ENOSPC;
		sge = sk_msg_elem(src, i);
	पूर्ण

	जबतक (len) अणु
		sge_len = sge->length - off;
		अगर (sge_len > len)
			sge_len = len;

		अगर (dst->sg.end)
			sgd = sk_msg_elem(dst, dst->sg.end - 1);

		अगर (sgd &&
		    (sg_page(sge) == sg_page(sgd)) &&
		    (sg_virt(sge) + off == sg_virt(sgd) + sgd->length)) अणु
			sgd->length += sge_len;
			dst->sg.size += sge_len;
		पूर्ण अन्यथा अगर (!sk_msg_full(dst)) अणु
			sge_off = sge->offset + off;
			sk_msg_page_add(dst, sg_page(sge), sge_len, sge_off);
		पूर्ण अन्यथा अणु
			वापस -ENOSPC;
		पूर्ण

		off = 0;
		len -= sge_len;
		sk_mem_अक्षरge(sk, sge_len);
		sk_msg_iter_var_next(i);
		अगर (i == src->sg.end && len)
			वापस -ENOSPC;
		sge = sk_msg_elem(src, i);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_clone);

व्योम sk_msg_वापस_zero(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक bytes)
अणु
	पूर्णांक i = msg->sg.start;

	करो अणु
		काष्ठा scatterlist *sge = sk_msg_elem(msg, i);

		अगर (bytes < sge->length) अणु
			sge->length -= bytes;
			sge->offset += bytes;
			sk_mem_unअक्षरge(sk, bytes);
			अवरोध;
		पूर्ण

		sk_mem_unअक्षरge(sk, sge->length);
		bytes -= sge->length;
		sge->length = 0;
		sge->offset = 0;
		sk_msg_iter_var_next(i);
	पूर्ण जबतक (bytes && i != msg->sg.end);
	msg->sg.start = i;
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_वापस_zero);

व्योम sk_msg_वापस(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक bytes)
अणु
	पूर्णांक i = msg->sg.start;

	करो अणु
		काष्ठा scatterlist *sge = &msg->sg.data[i];
		पूर्णांक unअक्षरge = (bytes < sge->length) ? bytes : sge->length;

		sk_mem_unअक्षरge(sk, unअक्षरge);
		bytes -= unअक्षरge;
		sk_msg_iter_var_next(i);
	पूर्ण जबतक (i != msg->sg.end);
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_वापस);

अटल पूर्णांक sk_msg_मुक्त_elem(काष्ठा sock *sk, काष्ठा sk_msg *msg, u32 i,
			    bool अक्षरge)
अणु
	काष्ठा scatterlist *sge = sk_msg_elem(msg, i);
	u32 len = sge->length;

	/* When the skb owns the memory we मुक्त it from consume_skb path. */
	अगर (!msg->skb) अणु
		अगर (अक्षरge)
			sk_mem_unअक्षरge(sk, len);
		put_page(sg_page(sge));
	पूर्ण
	स_रखो(sge, 0, माप(*sge));
	वापस len;
पूर्ण

अटल पूर्णांक __sk_msg_मुक्त(काष्ठा sock *sk, काष्ठा sk_msg *msg, u32 i,
			 bool अक्षरge)
अणु
	काष्ठा scatterlist *sge = sk_msg_elem(msg, i);
	पूर्णांक मुक्तd = 0;

	जबतक (msg->sg.size) अणु
		msg->sg.size -= sge->length;
		मुक्तd += sk_msg_मुक्त_elem(sk, msg, i, अक्षरge);
		sk_msg_iter_var_next(i);
		sk_msg_check_to_मुक्त(msg, i, msg->sg.size);
		sge = sk_msg_elem(msg, i);
	पूर्ण
	consume_skb(msg->skb);
	sk_msg_init(msg);
	वापस मुक्तd;
पूर्ण

पूर्णांक sk_msg_मुक्त_noअक्षरge(काष्ठा sock *sk, काष्ठा sk_msg *msg)
अणु
	वापस __sk_msg_मुक्त(sk, msg, msg->sg.start, false);
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_मुक्त_noअक्षरge);

पूर्णांक sk_msg_मुक्त(काष्ठा sock *sk, काष्ठा sk_msg *msg)
अणु
	वापस __sk_msg_मुक्त(sk, msg, msg->sg.start, true);
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_मुक्त);

अटल व्योम __sk_msg_मुक्त_partial(काष्ठा sock *sk, काष्ठा sk_msg *msg,
				  u32 bytes, bool अक्षरge)
अणु
	काष्ठा scatterlist *sge;
	u32 i = msg->sg.start;

	जबतक (bytes) अणु
		sge = sk_msg_elem(msg, i);
		अगर (!sge->length)
			अवरोध;
		अगर (bytes < sge->length) अणु
			अगर (अक्षरge)
				sk_mem_unअक्षरge(sk, bytes);
			sge->length -= bytes;
			sge->offset += bytes;
			msg->sg.size -= bytes;
			अवरोध;
		पूर्ण

		msg->sg.size -= sge->length;
		bytes -= sge->length;
		sk_msg_मुक्त_elem(sk, msg, i, अक्षरge);
		sk_msg_iter_var_next(i);
		sk_msg_check_to_मुक्त(msg, i, bytes);
	पूर्ण
	msg->sg.start = i;
पूर्ण

व्योम sk_msg_मुक्त_partial(काष्ठा sock *sk, काष्ठा sk_msg *msg, u32 bytes)
अणु
	__sk_msg_मुक्त_partial(sk, msg, bytes, true);
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_मुक्त_partial);

व्योम sk_msg_मुक्त_partial_noअक्षरge(काष्ठा sock *sk, काष्ठा sk_msg *msg,
				  u32 bytes)
अणु
	__sk_msg_मुक्त_partial(sk, msg, bytes, false);
पूर्ण

व्योम sk_msg_trim(काष्ठा sock *sk, काष्ठा sk_msg *msg, पूर्णांक len)
अणु
	पूर्णांक trim = msg->sg.size - len;
	u32 i = msg->sg.end;

	अगर (trim <= 0) अणु
		WARN_ON(trim < 0);
		वापस;
	पूर्ण

	sk_msg_iter_var_prev(i);
	msg->sg.size = len;
	जबतक (msg->sg.data[i].length &&
	       trim >= msg->sg.data[i].length) अणु
		trim -= msg->sg.data[i].length;
		sk_msg_मुक्त_elem(sk, msg, i, true);
		sk_msg_iter_var_prev(i);
		अगर (!trim)
			जाओ out;
	पूर्ण

	msg->sg.data[i].length -= trim;
	sk_mem_unअक्षरge(sk, trim);
	/* Adjust copyअवरोध अगर it falls पूर्णांकo the trimmed part of last buf */
	अगर (msg->sg.curr == i && msg->sg.copyअवरोध > msg->sg.data[i].length)
		msg->sg.copyअवरोध = msg->sg.data[i].length;
out:
	sk_msg_iter_var_next(i);
	msg->sg.end = i;

	/* If we trim data a full sg elem beक्रमe curr poपूर्णांकer update
	 * copyअवरोध and current so that any future copy operations
	 * start at new copy location.
	 * However trimed data that has not yet been used in a copy op
	 * करोes not require an update.
	 */
	अगर (!msg->sg.size) अणु
		msg->sg.curr = msg->sg.start;
		msg->sg.copyअवरोध = 0;
	पूर्ण अन्यथा अगर (sk_msg_iter_dist(msg->sg.start, msg->sg.curr) >=
		   sk_msg_iter_dist(msg->sg.start, msg->sg.end)) अणु
		sk_msg_iter_var_prev(i);
		msg->sg.curr = i;
		msg->sg.copyअवरोध = msg->sg.data[i].length;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_trim);

पूर्णांक sk_msg_zerocopy_from_iter(काष्ठा sock *sk, काष्ठा iov_iter *from,
			      काष्ठा sk_msg *msg, u32 bytes)
अणु
	पूर्णांक i, maxpages, ret = 0, num_elems = sk_msg_elem_used(msg);
	स्थिर पूर्णांक to_max_pages = MAX_MSG_FRAGS;
	काष्ठा page *pages[MAX_MSG_FRAGS];
	sमाप_प्रकार orig, copied, use, offset;

	orig = msg->sg.size;
	जबतक (bytes > 0) अणु
		i = 0;
		maxpages = to_max_pages - num_elems;
		अगर (maxpages == 0) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		copied = iov_iter_get_pages(from, pages, bytes, maxpages,
					    &offset);
		अगर (copied <= 0) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण

		iov_iter_advance(from, copied);
		bytes -= copied;
		msg->sg.size += copied;

		जबतक (copied) अणु
			use = min_t(पूर्णांक, copied, PAGE_SIZE - offset);
			sg_set_page(&msg->sg.data[msg->sg.end],
				    pages[i], use, offset);
			sg_unmark_end(&msg->sg.data[msg->sg.end]);
			sk_mem_अक्षरge(sk, use);

			offset = 0;
			copied -= use;
			sk_msg_iter_next(msg, end);
			num_elems++;
			i++;
		पूर्ण
		/* When zerocopy is mixed with sk_msg_*copy* operations we
		 * may have a copyअवरोध set in this हाल clear and prefer
		 * zerocopy reमुख्यder when possible.
		 */
		msg->sg.copyअवरोध = 0;
		msg->sg.curr = msg->sg.end;
	पूर्ण
out:
	/* Revert iov_iter updates, msg will need to use 'trim' later अगर it
	 * also needs to be cleared.
	 */
	अगर (ret)
		iov_iter_revert(from, msg->sg.size - orig);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_zerocopy_from_iter);

पूर्णांक sk_msg_memcopy_from_iter(काष्ठा sock *sk, काष्ठा iov_iter *from,
			     काष्ठा sk_msg *msg, u32 bytes)
अणु
	पूर्णांक ret = -ENOSPC, i = msg->sg.curr;
	काष्ठा scatterlist *sge;
	u32 copy, buf_size;
	व्योम *to;

	करो अणु
		sge = sk_msg_elem(msg, i);
		/* This is possible अगर a trim operation shrunk the buffer */
		अगर (msg->sg.copyअवरोध >= sge->length) अणु
			msg->sg.copyअवरोध = 0;
			sk_msg_iter_var_next(i);
			अगर (i == msg->sg.end)
				अवरोध;
			sge = sk_msg_elem(msg, i);
		पूर्ण

		buf_size = sge->length - msg->sg.copyअवरोध;
		copy = (buf_size > bytes) ? bytes : buf_size;
		to = sg_virt(sge) + msg->sg.copyअवरोध;
		msg->sg.copyअवरोध += copy;
		अगर (sk->sk_route_caps & NETIF_F_NOCACHE_COPY)
			ret = copy_from_iter_nocache(to, copy, from);
		अन्यथा
			ret = copy_from_iter(to, copy, from);
		अगर (ret != copy) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
		bytes -= copy;
		अगर (!bytes)
			अवरोध;
		msg->sg.copyअवरोध = 0;
		sk_msg_iter_var_next(i);
	पूर्ण जबतक (i != msg->sg.end);
out:
	msg->sg.curr = i;
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_memcopy_from_iter);

पूर्णांक sk_msg_रुको_data(काष्ठा sock *sk, काष्ठा sk_psock *psock, पूर्णांक flags,
		     दीर्घ समयo, पूर्णांक *err)
अणु
	DEFINE_WAIT_FUNC(रुको, woken_wake_function);
	पूर्णांक ret = 0;

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		वापस 1;

	अगर (!समयo)
		वापस ret;

	add_रुको_queue(sk_sleep(sk), &रुको);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	ret = sk_रुको_event(sk, &समयo,
			    !list_empty(&psock->ingress_msg) ||
			    !skb_queue_empty(&sk->sk_receive_queue), &रुको);
	sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_रुको_data);

/* Receive sk_msg from psock->ingress_msg to @msg. */
पूर्णांक sk_msg_recvmsg(काष्ठा sock *sk, काष्ठा sk_psock *psock, काष्ठा msghdr *msg,
		   पूर्णांक len, पूर्णांक flags)
अणु
	काष्ठा iov_iter *iter = &msg->msg_iter;
	पूर्णांक peek = flags & MSG_PEEK;
	काष्ठा sk_msg *msg_rx;
	पूर्णांक i, copied = 0;

	msg_rx = sk_psock_peek_msg(psock);
	जबतक (copied != len) अणु
		काष्ठा scatterlist *sge;

		अगर (unlikely(!msg_rx))
			अवरोध;

		i = msg_rx->sg.start;
		करो अणु
			काष्ठा page *page;
			पूर्णांक copy;

			sge = sk_msg_elem(msg_rx, i);
			copy = sge->length;
			page = sg_page(sge);
			अगर (copied + copy > len)
				copy = len - copied;
			copy = copy_page_to_iter(page, sge->offset, copy, iter);
			अगर (!copy)
				वापस copied ? copied : -EFAULT;

			copied += copy;
			अगर (likely(!peek)) अणु
				sge->offset += copy;
				sge->length -= copy;
				अगर (!msg_rx->skb)
					sk_mem_unअक्षरge(sk, copy);
				msg_rx->sg.size -= copy;

				अगर (!sge->length) अणु
					sk_msg_iter_var_next(i);
					अगर (!msg_rx->skb)
						put_page(page);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* Lets not optimize peek हाल अगर copy_page_to_iter
				 * didn't copy the entire length lets just अवरोध.
				 */
				अगर (copy != sge->length)
					वापस copied;
				sk_msg_iter_var_next(i);
			पूर्ण

			अगर (copied == len)
				अवरोध;
		पूर्ण जबतक (i != msg_rx->sg.end);

		अगर (unlikely(peek)) अणु
			msg_rx = sk_psock_next_msg(psock, msg_rx);
			अगर (!msg_rx)
				अवरोध;
			जारी;
		पूर्ण

		msg_rx->sg.start = i;
		अगर (!sge->length && msg_rx->sg.start == msg_rx->sg.end) अणु
			msg_rx = sk_psock_dequeue_msg(psock);
			kमुक्त_sk_msg(msg_rx);
		पूर्ण
		msg_rx = sk_psock_peek_msg(psock);
	पूर्ण

	वापस copied;
पूर्ण
EXPORT_SYMBOL_GPL(sk_msg_recvmsg);

अटल काष्ठा sk_msg *sk_psock_create_ingress_msg(काष्ठा sock *sk,
						  काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_msg *msg;

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) > sk->sk_rcvbuf)
		वापस शून्य;

	अगर (!sk_rmem_schedule(sk, skb, skb->truesize))
		वापस शून्य;

	msg = kzalloc(माप(*msg), __GFP_NOWARN | GFP_KERNEL);
	अगर (unlikely(!msg))
		वापस शून्य;

	sk_msg_init(msg);
	वापस msg;
पूर्ण

अटल पूर्णांक sk_psock_skb_ingress_enqueue(काष्ठा sk_buff *skb,
					काष्ठा sk_psock *psock,
					काष्ठा sock *sk,
					काष्ठा sk_msg *msg)
अणु
	पूर्णांक num_sge, copied;

	/* skb linearize may fail with ENOMEM, but lets simply try again
	 * later अगर this happens. Under memory pressure we करोn't want to
	 * drop the skb. We need to linearize the skb so that the mapping
	 * in skb_to_sgvec can not error.
	 */
	अगर (skb_linearize(skb))
		वापस -EAGAIN;
	num_sge = skb_to_sgvec(skb, msg->sg.data, 0, skb->len);
	अगर (unlikely(num_sge < 0)) अणु
		kमुक्त(msg);
		वापस num_sge;
	पूर्ण

	copied = skb->len;
	msg->sg.start = 0;
	msg->sg.size = copied;
	msg->sg.end = num_sge;
	msg->skb = skb;

	sk_psock_queue_msg(psock, msg);
	sk_psock_data_पढ़ोy(sk, psock);
	वापस copied;
पूर्ण

अटल पूर्णांक sk_psock_skb_ingress_self(काष्ठा sk_psock *psock, काष्ठा sk_buff *skb);

अटल पूर्णांक sk_psock_skb_ingress(काष्ठा sk_psock *psock, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk = psock->sk;
	काष्ठा sk_msg *msg;

	/* If we are receiving on the same sock skb->sk is alपढ़ोy asचिन्हित,
	 * skip memory accounting and owner transition seeing it alपढ़ोy set
	 * correctly.
	 */
	अगर (unlikely(skb->sk == sk))
		वापस sk_psock_skb_ingress_self(psock, skb);
	msg = sk_psock_create_ingress_msg(sk, skb);
	अगर (!msg)
		वापस -EAGAIN;

	/* This will transition ownership of the data from the socket where
	 * the BPF program was run initiating the redirect to the socket
	 * we will eventually receive this data on. The data will be released
	 * from skb_consume found in __tcp_bpf_recvmsg() after its been copied
	 * पूर्णांकo user buffers.
	 */
	skb_set_owner_r(skb, sk);
	वापस sk_psock_skb_ingress_enqueue(skb, psock, sk, msg);
पूर्ण

/* Puts an skb on the ingress queue of the socket alपढ़ोy asचिन्हित to the
 * skb. In this हाल we करो not need to check memory limits or skb_set_owner_r
 * because the skb is alपढ़ोy accounted क्रम here.
 */
अटल पूर्णांक sk_psock_skb_ingress_self(काष्ठा sk_psock *psock, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_msg *msg = kzalloc(माप(*msg), __GFP_NOWARN | GFP_ATOMIC);
	काष्ठा sock *sk = psock->sk;

	अगर (unlikely(!msg))
		वापस -EAGAIN;
	sk_msg_init(msg);
	skb_set_owner_r(skb, sk);
	वापस sk_psock_skb_ingress_enqueue(skb, psock, sk, msg);
पूर्ण

अटल पूर्णांक sk_psock_handle_skb(काष्ठा sk_psock *psock, काष्ठा sk_buff *skb,
			       u32 off, u32 len, bool ingress)
अणु
	अगर (!ingress) अणु
		अगर (!sock_ग_लिखोable(psock->sk))
			वापस -EAGAIN;
		वापस skb_send_sock(psock->sk, skb, off, len);
	पूर्ण
	वापस sk_psock_skb_ingress(psock, skb);
पूर्ण

अटल व्योम sk_psock_backlog(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_psock *psock = container_of(work, काष्ठा sk_psock, work);
	काष्ठा sk_psock_work_state *state = &psock->work_state;
	काष्ठा sk_buff *skb;
	bool ingress;
	u32 len, off;
	पूर्णांक ret;

	mutex_lock(&psock->work_mutex);
	अगर (state->skb) अणु
		skb = state->skb;
		len = state->len;
		off = state->off;
		state->skb = शून्य;
		जाओ start;
	पूर्ण

	जबतक ((skb = skb_dequeue(&psock->ingress_skb))) अणु
		len = skb->len;
		off = 0;
start:
		ingress = skb_bpf_ingress(skb);
		skb_bpf_redirect_clear(skb);
		करो अणु
			ret = -EIO;
			अगर (!sock_flag(psock->sk, SOCK_DEAD))
				ret = sk_psock_handle_skb(psock, skb, off,
							  len, ingress);
			अगर (ret <= 0) अणु
				अगर (ret == -EAGAIN) अणु
					state->skb = skb;
					state->len = len;
					state->off = off;
					जाओ end;
				पूर्ण
				/* Hard errors अवरोध pipe and stop xmit. */
				sk_psock_report_error(psock, ret ? -ret : EPIPE);
				sk_psock_clear_state(psock, SK_PSOCK_TX_ENABLED);
				kमुक्त_skb(skb);
				जाओ end;
			पूर्ण
			off += ret;
			len -= ret;
		पूर्ण जबतक (len);

		अगर (!ingress)
			kमुक्त_skb(skb);
	पूर्ण
end:
	mutex_unlock(&psock->work_mutex);
पूर्ण

काष्ठा sk_psock *sk_psock_init(काष्ठा sock *sk, पूर्णांक node)
अणु
	काष्ठा sk_psock *psock;
	काष्ठा proto *prot;

	ग_लिखो_lock_bh(&sk->sk_callback_lock);

	अगर (sk->sk_user_data) अणु
		psock = ERR_PTR(-EBUSY);
		जाओ out;
	पूर्ण

	psock = kzalloc_node(माप(*psock), GFP_ATOMIC | __GFP_NOWARN, node);
	अगर (!psock) अणु
		psock = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	prot = READ_ONCE(sk->sk_prot);
	psock->sk = sk;
	psock->eval = __SK_NONE;
	psock->sk_proto = prot;
	psock->saved_unhash = prot->unhash;
	psock->saved_बंद = prot->बंद;
	psock->saved_ग_लिखो_space = sk->sk_ग_लिखो_space;

	INIT_LIST_HEAD(&psock->link);
	spin_lock_init(&psock->link_lock);

	INIT_WORK(&psock->work, sk_psock_backlog);
	mutex_init(&psock->work_mutex);
	INIT_LIST_HEAD(&psock->ingress_msg);
	spin_lock_init(&psock->ingress_lock);
	skb_queue_head_init(&psock->ingress_skb);

	sk_psock_set_state(psock, SK_PSOCK_TX_ENABLED);
	refcount_set(&psock->refcnt, 1);

	rcu_assign_sk_user_data_nocopy(sk, psock);
	sock_hold(sk);

out:
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);
	वापस psock;
पूर्ण
EXPORT_SYMBOL_GPL(sk_psock_init);

काष्ठा sk_psock_link *sk_psock_link_pop(काष्ठा sk_psock *psock)
अणु
	काष्ठा sk_psock_link *link;

	spin_lock_bh(&psock->link_lock);
	link = list_first_entry_or_null(&psock->link, काष्ठा sk_psock_link,
					list);
	अगर (link)
		list_del(&link->list);
	spin_unlock_bh(&psock->link_lock);
	वापस link;
पूर्ण

अटल व्योम __sk_psock_purge_ingress_msg(काष्ठा sk_psock *psock)
अणु
	काष्ठा sk_msg *msg, *पंचांगp;

	list_क्रम_each_entry_safe(msg, पंचांगp, &psock->ingress_msg, list) अणु
		list_del(&msg->list);
		sk_msg_मुक्त(psock->sk, msg);
		kमुक्त(msg);
	पूर्ण
पूर्ण

अटल व्योम __sk_psock_zap_ingress(काष्ठा sk_psock *psock)
अणु
	काष्ठा sk_buff *skb;

	जबतक ((skb = skb_dequeue(&psock->ingress_skb)) != शून्य) अणु
		skb_bpf_redirect_clear(skb);
		kमुक्त_skb(skb);
	पूर्ण
	__sk_psock_purge_ingress_msg(psock);
पूर्ण

अटल व्योम sk_psock_link_destroy(काष्ठा sk_psock *psock)
अणु
	काष्ठा sk_psock_link *link, *पंचांगp;

	list_क्रम_each_entry_safe(link, पंचांगp, &psock->link, list) अणु
		list_del(&link->list);
		sk_psock_मुक्त_link(link);
	पूर्ण
पूर्ण

व्योम sk_psock_stop(काष्ठा sk_psock *psock, bool रुको)
अणु
	spin_lock_bh(&psock->ingress_lock);
	sk_psock_clear_state(psock, SK_PSOCK_TX_ENABLED);
	sk_psock_cork_मुक्त(psock);
	__sk_psock_zap_ingress(psock);
	spin_unlock_bh(&psock->ingress_lock);

	अगर (रुको)
		cancel_work_sync(&psock->work);
पूर्ण

अटल व्योम sk_psock_करोne_strp(काष्ठा sk_psock *psock);

अटल व्योम sk_psock_destroy(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sk_psock *psock = container_of(to_rcu_work(work),
					      काष्ठा sk_psock, rwork);
	/* No sk_callback_lock since alपढ़ोy detached. */

	sk_psock_करोne_strp(psock);

	cancel_work_sync(&psock->work);
	mutex_destroy(&psock->work_mutex);

	psock_progs_drop(&psock->progs);

	sk_psock_link_destroy(psock);
	sk_psock_cork_मुक्त(psock);

	अगर (psock->sk_redir)
		sock_put(psock->sk_redir);
	sock_put(psock->sk);
	kमुक्त(psock);
पूर्ण

व्योम sk_psock_drop(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	sk_psock_stop(psock, false);

	ग_लिखो_lock_bh(&sk->sk_callback_lock);
	sk_psock_restore_proto(sk, psock);
	rcu_assign_sk_user_data(sk, शून्य);
	अगर (psock->progs.stream_parser)
		sk_psock_stop_strp(sk, psock);
	अन्यथा अगर (psock->progs.stream_verdict || psock->progs.skb_verdict)
		sk_psock_stop_verdict(sk, psock);
	ग_लिखो_unlock_bh(&sk->sk_callback_lock);

	INIT_RCU_WORK(&psock->rwork, sk_psock_destroy);
	queue_rcu_work(प्रणाली_wq, &psock->rwork);
पूर्ण
EXPORT_SYMBOL_GPL(sk_psock_drop);

अटल पूर्णांक sk_psock_map_verd(पूर्णांक verdict, bool redir)
अणु
	चयन (verdict) अणु
	हाल SK_PASS:
		वापस redir ? __SK_REसूचीECT : __SK_PASS;
	हाल SK_DROP:
	शेष:
		अवरोध;
	पूर्ण

	वापस __SK_DROP;
पूर्ण

पूर्णांक sk_psock_msg_verdict(काष्ठा sock *sk, काष्ठा sk_psock *psock,
			 काष्ठा sk_msg *msg)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक ret;

	rcu_पढ़ो_lock();
	prog = READ_ONCE(psock->progs.msg_parser);
	अगर (unlikely(!prog)) अणु
		ret = __SK_PASS;
		जाओ out;
	पूर्ण

	sk_msg_compute_data_poपूर्णांकers(msg);
	msg->sk = sk;
	ret = bpf_prog_run_pin_on_cpu(prog, msg);
	ret = sk_psock_map_verd(ret, msg->sk_redir);
	psock->apply_bytes = msg->apply_bytes;
	अगर (ret == __SK_REसूचीECT) अणु
		अगर (psock->sk_redir)
			sock_put(psock->sk_redir);
		psock->sk_redir = msg->sk_redir;
		अगर (!psock->sk_redir) अणु
			ret = __SK_DROP;
			जाओ out;
		पूर्ण
		sock_hold(psock->sk_redir);
	पूर्ण
out:
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sk_psock_msg_verdict);

अटल व्योम sk_psock_skb_redirect(काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_psock *psock_other;
	काष्ठा sock *sk_other;

	sk_other = skb_bpf_redirect_fetch(skb);
	/* This error is a buggy BPF program, it वापसed a redirect
	 * वापस code, but then didn't set a redirect पूर्णांकerface.
	 */
	अगर (unlikely(!sk_other)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	psock_other = sk_psock(sk_other);
	/* This error indicates the socket is being torn करोwn or had another
	 * error that caused the pipe to अवरोध. We can't send a packet on
	 * a socket that is in this state so we drop the skb.
	 */
	अगर (!psock_other || sock_flag(sk_other, SOCK_DEAD)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	spin_lock_bh(&psock_other->ingress_lock);
	अगर (!sk_psock_test_state(psock_other, SK_PSOCK_TX_ENABLED)) अणु
		spin_unlock_bh(&psock_other->ingress_lock);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_queue_tail(&psock_other->ingress_skb, skb);
	schedule_work(&psock_other->work);
	spin_unlock_bh(&psock_other->ingress_lock);
पूर्ण

अटल व्योम sk_psock_tls_verdict_apply(काष्ठा sk_buff *skb, काष्ठा sock *sk, पूर्णांक verdict)
अणु
	चयन (verdict) अणु
	हाल __SK_REसूचीECT:
		sk_psock_skb_redirect(skb);
		अवरोध;
	हाल __SK_PASS:
	हाल __SK_DROP:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक sk_psock_tls_strp_पढ़ो(काष्ठा sk_psock *psock, काष्ठा sk_buff *skb)
अणु
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = __SK_PASS;

	rcu_पढ़ो_lock();
	prog = READ_ONCE(psock->progs.stream_verdict);
	अगर (likely(prog)) अणु
		skb->sk = psock->sk;
		skb_dst_drop(skb);
		skb_bpf_redirect_clear(skb);
		ret = bpf_prog_run_pin_on_cpu(prog, skb);
		ret = sk_psock_map_verd(ret, skb_bpf_redirect_fetch(skb));
		skb->sk = शून्य;
	पूर्ण
	sk_psock_tls_verdict_apply(skb, psock->sk, ret);
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sk_psock_tls_strp_पढ़ो);

अटल व्योम sk_psock_verdict_apply(काष्ठा sk_psock *psock,
				   काष्ठा sk_buff *skb, पूर्णांक verdict)
अणु
	काष्ठा sock *sk_other;
	पूर्णांक err = -EIO;

	चयन (verdict) अणु
	हाल __SK_PASS:
		sk_other = psock->sk;
		अगर (sock_flag(sk_other, SOCK_DEAD) ||
		    !sk_psock_test_state(psock, SK_PSOCK_TX_ENABLED)) अणु
			जाओ out_मुक्त;
		पूर्ण

		skb_bpf_set_ingress(skb);

		/* If the queue is empty then we can submit directly
		 * पूर्णांकo the msg queue. If its not empty we have to
		 * queue work otherwise we may get OOO data. Otherwise,
		 * अगर sk_psock_skb_ingress errors will be handled by
		 * retrying later from workqueue.
		 */
		अगर (skb_queue_empty(&psock->ingress_skb)) अणु
			err = sk_psock_skb_ingress_self(psock, skb);
		पूर्ण
		अगर (err < 0) अणु
			spin_lock_bh(&psock->ingress_lock);
			अगर (sk_psock_test_state(psock, SK_PSOCK_TX_ENABLED)) अणु
				skb_queue_tail(&psock->ingress_skb, skb);
				schedule_work(&psock->work);
			पूर्ण
			spin_unlock_bh(&psock->ingress_lock);
		पूर्ण
		अवरोध;
	हाल __SK_REसूचीECT:
		sk_psock_skb_redirect(skb);
		अवरोध;
	हाल __SK_DROP:
	शेष:
out_मुक्त:
		kमुक्त_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम sk_psock_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा sk_psock *psock;
	व्योम (*ग_लिखो_space)(काष्ठा sock *sk) = शून्य;

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (likely(psock)) अणु
		अगर (sk_psock_test_state(psock, SK_PSOCK_TX_ENABLED))
			schedule_work(&psock->work);
		ग_लिखो_space = psock->saved_ग_लिखो_space;
	पूर्ण
	rcu_पढ़ो_unlock();
	अगर (ग_लिखो_space)
		ग_लिखो_space(sk);
पूर्ण

#अगर IS_ENABLED(CONFIG_BPF_STREAM_PARSER)
अटल व्योम sk_psock_strp_पढ़ो(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_psock *psock;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = __SK_DROP;
	काष्ठा sock *sk;

	rcu_पढ़ो_lock();
	sk = strp->sk;
	psock = sk_psock(sk);
	अगर (unlikely(!psock)) अणु
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण
	prog = READ_ONCE(psock->progs.stream_verdict);
	अगर (likely(prog)) अणु
		skb->sk = sk;
		skb_dst_drop(skb);
		skb_bpf_redirect_clear(skb);
		ret = bpf_prog_run_pin_on_cpu(prog, skb);
		ret = sk_psock_map_verd(ret, skb_bpf_redirect_fetch(skb));
		skb->sk = शून्य;
	पूर्ण
	sk_psock_verdict_apply(psock, skb, ret);
out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक sk_psock_strp_पढ़ो_करोne(काष्ठा strparser *strp, पूर्णांक err)
अणु
	वापस err;
पूर्ण

अटल पूर्णांक sk_psock_strp_parse(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_psock *psock = container_of(strp, काष्ठा sk_psock, strp);
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = skb->len;

	rcu_पढ़ो_lock();
	prog = READ_ONCE(psock->progs.stream_parser);
	अगर (likely(prog)) अणु
		skb->sk = psock->sk;
		ret = bpf_prog_run_pin_on_cpu(prog, skb);
		skb->sk = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/* Called with socket lock held. */
अटल व्योम sk_psock_strp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा sk_psock *psock;

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (likely(psock)) अणु
		अगर (tls_sw_has_ctx_rx(sk)) अणु
			psock->saved_data_पढ़ोy(sk);
		पूर्ण अन्यथा अणु
			ग_लिखो_lock_bh(&sk->sk_callback_lock);
			strp_data_पढ़ोy(&psock->strp);
			ग_लिखो_unlock_bh(&sk->sk_callback_lock);
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक sk_psock_init_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अटल स्थिर काष्ठा strp_callbacks cb = अणु
		.rcv_msg	= sk_psock_strp_पढ़ो,
		.पढ़ो_sock_करोne	= sk_psock_strp_पढ़ो_करोne,
		.parse_msg	= sk_psock_strp_parse,
	पूर्ण;

	वापस strp_init(&psock->strp, sk, &cb);
पूर्ण

व्योम sk_psock_start_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अगर (psock->saved_data_पढ़ोy)
		वापस;

	psock->saved_data_पढ़ोy = sk->sk_data_पढ़ोy;
	sk->sk_data_पढ़ोy = sk_psock_strp_data_पढ़ोy;
	sk->sk_ग_लिखो_space = sk_psock_ग_लिखो_space;
पूर्ण

व्योम sk_psock_stop_strp(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अगर (!psock->saved_data_पढ़ोy)
		वापस;

	sk->sk_data_पढ़ोy = psock->saved_data_पढ़ोy;
	psock->saved_data_पढ़ोy = शून्य;
	strp_stop(&psock->strp);
पूर्ण

अटल व्योम sk_psock_करोne_strp(काष्ठा sk_psock *psock)
अणु
	/* Parser has been stopped */
	अगर (psock->progs.stream_parser)
		strp_करोne(&psock->strp);
पूर्ण
#अन्यथा
अटल व्योम sk_psock_करोne_strp(काष्ठा sk_psock *psock)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_STREAM_PARSER */

अटल पूर्णांक sk_psock_verdict_recv(पढ़ो_descriptor_t *desc, काष्ठा sk_buff *skb,
				 अचिन्हित पूर्णांक offset, माप_प्रकार orig_len)
अणु
	काष्ठा sock *sk = (काष्ठा sock *)desc->arg.data;
	काष्ठा sk_psock *psock;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = __SK_DROP;
	पूर्णांक len = skb->len;

	/* clone here so sk_eat_skb() in tcp_पढ़ो_sock करोes not drop our data */
	skb = skb_clone(skb, GFP_ATOMIC);
	अगर (!skb) अणु
		desc->error = -ENOMEM;
		वापस 0;
	पूर्ण

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (unlikely(!psock)) अणु
		len = 0;
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण
	prog = READ_ONCE(psock->progs.stream_verdict);
	अगर (!prog)
		prog = READ_ONCE(psock->progs.skb_verdict);
	अगर (likely(prog)) अणु
		skb->sk = sk;
		skb_dst_drop(skb);
		skb_bpf_redirect_clear(skb);
		ret = bpf_prog_run_pin_on_cpu(prog, skb);
		ret = sk_psock_map_verd(ret, skb_bpf_redirect_fetch(skb));
		skb->sk = शून्य;
	पूर्ण
	sk_psock_verdict_apply(psock, skb, ret);
out:
	rcu_पढ़ो_unlock();
	वापस len;
पूर्ण

अटल व्योम sk_psock_verdict_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा socket *sock = sk->sk_socket;
	पढ़ो_descriptor_t desc;

	अगर (unlikely(!sock || !sock->ops || !sock->ops->पढ़ो_sock))
		वापस;

	desc.arg.data = sk;
	desc.error = 0;
	desc.count = 1;

	sock->ops->पढ़ो_sock(sk, &desc, sk_psock_verdict_recv);
पूर्ण

व्योम sk_psock_start_verdict(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अगर (psock->saved_data_पढ़ोy)
		वापस;

	psock->saved_data_पढ़ोy = sk->sk_data_पढ़ोy;
	sk->sk_data_पढ़ोy = sk_psock_verdict_data_पढ़ोy;
	sk->sk_ग_लिखो_space = sk_psock_ग_लिखो_space;
पूर्ण

व्योम sk_psock_stop_verdict(काष्ठा sock *sk, काष्ठा sk_psock *psock)
अणु
	अगर (!psock->saved_data_पढ़ोy)
		वापस;

	sk->sk_data_पढ़ोy = psock->saved_data_पढ़ोy;
	psock->saved_data_पढ़ोy = शून्य;
पूर्ण
