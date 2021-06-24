<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2017 - 2018 Covalent IO, Inc. http://covalent.io */

#समावेश <linux/skmsg.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/init.h>
#समावेश <linux/रुको.h>

#समावेश <net/inet_common.h>
#समावेश <net/tls.h>

अटल पूर्णांक bpf_tcp_ingress(काष्ठा sock *sk, काष्ठा sk_psock *psock,
			   काष्ठा sk_msg *msg, u32 apply_bytes, पूर्णांक flags)
अणु
	bool apply = apply_bytes;
	काष्ठा scatterlist *sge;
	u32 size, copied = 0;
	काष्ठा sk_msg *पंचांगp;
	पूर्णांक i, ret = 0;

	पंचांगp = kzalloc(माप(*पंचांगp), __GFP_NOWARN | GFP_KERNEL);
	अगर (unlikely(!पंचांगp))
		वापस -ENOMEM;

	lock_sock(sk);
	पंचांगp->sg.start = msg->sg.start;
	i = msg->sg.start;
	करो अणु
		sge = sk_msg_elem(msg, i);
		size = (apply && apply_bytes < sge->length) ?
			apply_bytes : sge->length;
		अगर (!sk_wmem_schedule(sk, size)) अणु
			अगर (!copied)
				ret = -ENOMEM;
			अवरोध;
		पूर्ण

		sk_mem_अक्षरge(sk, size);
		sk_msg_xfer(पंचांगp, msg, i, size);
		copied += size;
		अगर (sge->length)
			get_page(sk_msg_page(पंचांगp, i));
		sk_msg_iter_var_next(i);
		पंचांगp->sg.end = i;
		अगर (apply) अणु
			apply_bytes -= size;
			अगर (!apply_bytes)
				अवरोध;
		पूर्ण
	पूर्ण जबतक (i != msg->sg.end);

	अगर (!ret) अणु
		msg->sg.start = i;
		sk_psock_queue_msg(psock, पंचांगp);
		sk_psock_data_पढ़ोy(sk, psock);
	पूर्ण अन्यथा अणु
		sk_msg_मुक्त(sk, पंचांगp);
		kमुक्त(पंचांगp);
	पूर्ण

	release_sock(sk);
	वापस ret;
पूर्ण

अटल पूर्णांक tcp_bpf_push(काष्ठा sock *sk, काष्ठा sk_msg *msg, u32 apply_bytes,
			पूर्णांक flags, bool unअक्षरge)
अणु
	bool apply = apply_bytes;
	काष्ठा scatterlist *sge;
	काष्ठा page *page;
	पूर्णांक size, ret = 0;
	u32 off;

	जबतक (1) अणु
		bool has_tx_ulp;

		sge = sk_msg_elem(msg, msg->sg.start);
		size = (apply && apply_bytes < sge->length) ?
			apply_bytes : sge->length;
		off  = sge->offset;
		page = sg_page(sge);

		tcp_rate_check_app_limited(sk);
retry:
		has_tx_ulp = tls_sw_has_ctx_tx(sk);
		अगर (has_tx_ulp) अणु
			flags |= MSG_SENDPAGE_NOPOLICY;
			ret = kernel_sendpage_locked(sk,
						     page, off, size, flags);
		पूर्ण अन्यथा अणु
			ret = करो_tcp_sendpages(sk, page, off, size, flags);
		पूर्ण

		अगर (ret <= 0)
			वापस ret;
		अगर (apply)
			apply_bytes -= ret;
		msg->sg.size -= ret;
		sge->offset += ret;
		sge->length -= ret;
		अगर (unअक्षरge)
			sk_mem_unअक्षरge(sk, ret);
		अगर (ret != size) अणु
			size -= ret;
			off  += ret;
			जाओ retry;
		पूर्ण
		अगर (!sge->length) अणु
			put_page(page);
			sk_msg_iter_next(msg, start);
			sg_init_table(sge, 1);
			अगर (msg->sg.start == msg->sg.end)
				अवरोध;
		पूर्ण
		अगर (apply && !apply_bytes)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tcp_bpf_push_locked(काष्ठा sock *sk, काष्ठा sk_msg *msg,
			       u32 apply_bytes, पूर्णांक flags, bool unअक्षरge)
अणु
	पूर्णांक ret;

	lock_sock(sk);
	ret = tcp_bpf_push(sk, msg, apply_bytes, flags, unअक्षरge);
	release_sock(sk);
	वापस ret;
पूर्ण

पूर्णांक tcp_bpf_sendmsg_redir(काष्ठा sock *sk, काष्ठा sk_msg *msg,
			  u32 bytes, पूर्णांक flags)
अणु
	bool ingress = sk_msg_to_ingress(msg);
	काष्ठा sk_psock *psock = sk_psock_get(sk);
	पूर्णांक ret;

	अगर (unlikely(!psock)) अणु
		sk_msg_मुक्त(sk, msg);
		वापस 0;
	पूर्ण
	ret = ingress ? bpf_tcp_ingress(sk, psock, msg, bytes, flags) :
			tcp_bpf_push_locked(sk, msg, bytes, flags, false);
	sk_psock_put(sk, psock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_bpf_sendmsg_redir);

#अगर_घोषित CONFIG_BPF_SYSCALL
अटल bool tcp_bpf_stream_पढ़ो(स्थिर काष्ठा sock *sk)
अणु
	काष्ठा sk_psock *psock;
	bool empty = true;

	rcu_पढ़ो_lock();
	psock = sk_psock(sk);
	अगर (likely(psock))
		empty = list_empty(&psock->ingress_msg);
	rcu_पढ़ो_unlock();
	वापस !empty;
पूर्ण

अटल पूर्णांक tcp_bpf_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		    पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा sk_psock *psock;
	पूर्णांक copied, ret;

	अगर (unlikely(flags & MSG_ERRQUEUE))
		वापस inet_recv_error(sk, msg, len, addr_len);

	psock = sk_psock_get(sk);
	अगर (unlikely(!psock))
		वापस tcp_recvmsg(sk, msg, len, nonblock, flags, addr_len);
	अगर (!skb_queue_empty(&sk->sk_receive_queue) &&
	    sk_psock_queue_empty(psock)) अणु
		sk_psock_put(sk, psock);
		वापस tcp_recvmsg(sk, msg, len, nonblock, flags, addr_len);
	पूर्ण
	lock_sock(sk);
msg_bytes_पढ़ोy:
	copied = sk_msg_recvmsg(sk, psock, msg, len, flags);
	अगर (!copied) अणु
		पूर्णांक data, err = 0;
		दीर्घ समयo;

		समयo = sock_rcvसमयo(sk, nonblock);
		data = sk_msg_रुको_data(sk, psock, flags, समयo, &err);
		अगर (data) अणु
			अगर (!sk_psock_queue_empty(psock))
				जाओ msg_bytes_पढ़ोy;
			release_sock(sk);
			sk_psock_put(sk, psock);
			वापस tcp_recvmsg(sk, msg, len, nonblock, flags, addr_len);
		पूर्ण
		अगर (err) अणु
			ret = err;
			जाओ out;
		पूर्ण
		copied = -EAGAIN;
	पूर्ण
	ret = copied;
out:
	release_sock(sk);
	sk_psock_put(sk, psock);
	वापस ret;
पूर्ण

अटल पूर्णांक tcp_bpf_send_verdict(काष्ठा sock *sk, काष्ठा sk_psock *psock,
				काष्ठा sk_msg *msg, पूर्णांक *copied, पूर्णांक flags)
अणु
	bool cork = false, enospc = sk_msg_full(msg);
	काष्ठा sock *sk_redir;
	u32 tosend, delta = 0;
	पूर्णांक ret;

more_data:
	अगर (psock->eval == __SK_NONE) अणु
		/* Track delta in msg size to add/subtract it on SK_DROP from
		 * वापसed to user copied size. This ensures user करोesn't
		 * get a positive वापस code with msg_cut_data and SK_DROP
		 * verdict.
		 */
		delta = msg->sg.size;
		psock->eval = sk_psock_msg_verdict(sk, psock, msg);
		delta -= msg->sg.size;
	पूर्ण

	अगर (msg->cork_bytes &&
	    msg->cork_bytes > msg->sg.size && !enospc) अणु
		psock->cork_bytes = msg->cork_bytes - msg->sg.size;
		अगर (!psock->cork) अणु
			psock->cork = kzalloc(माप(*psock->cork),
					      GFP_ATOMIC | __GFP_NOWARN);
			अगर (!psock->cork)
				वापस -ENOMEM;
		पूर्ण
		स_नकल(psock->cork, msg, माप(*msg));
		वापस 0;
	पूर्ण

	tosend = msg->sg.size;
	अगर (psock->apply_bytes && psock->apply_bytes < tosend)
		tosend = psock->apply_bytes;

	चयन (psock->eval) अणु
	हाल __SK_PASS:
		ret = tcp_bpf_push(sk, msg, tosend, flags, true);
		अगर (unlikely(ret)) अणु
			*copied -= sk_msg_मुक्त(sk, msg);
			अवरोध;
		पूर्ण
		sk_msg_apply_bytes(psock, tosend);
		अवरोध;
	हाल __SK_REसूचीECT:
		sk_redir = psock->sk_redir;
		sk_msg_apply_bytes(psock, tosend);
		अगर (psock->cork) अणु
			cork = true;
			psock->cork = शून्य;
		पूर्ण
		sk_msg_वापस(sk, msg, tosend);
		release_sock(sk);
		ret = tcp_bpf_sendmsg_redir(sk_redir, msg, tosend, flags);
		lock_sock(sk);
		अगर (unlikely(ret < 0)) अणु
			पूर्णांक मुक्त = sk_msg_मुक्त_noअक्षरge(sk, msg);

			अगर (!cork)
				*copied -= मुक्त;
		पूर्ण
		अगर (cork) अणु
			sk_msg_मुक्त(sk, msg);
			kमुक्त(msg);
			msg = शून्य;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल __SK_DROP:
	शेष:
		sk_msg_मुक्त_partial(sk, msg, tosend);
		sk_msg_apply_bytes(psock, tosend);
		*copied -= (tosend + delta);
		वापस -EACCES;
	पूर्ण

	अगर (likely(!ret)) अणु
		अगर (!psock->apply_bytes) अणु
			psock->eval =  __SK_NONE;
			अगर (psock->sk_redir) अणु
				sock_put(psock->sk_redir);
				psock->sk_redir = शून्य;
			पूर्ण
		पूर्ण
		अगर (msg &&
		    msg->sg.data[msg->sg.start].page_link &&
		    msg->sg.data[msg->sg.start].length)
			जाओ more_data;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक tcp_bpf_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा sk_msg पंचांगp, *msg_tx = शून्य;
	पूर्णांक copied = 0, err = 0;
	काष्ठा sk_psock *psock;
	दीर्घ समयo;
	पूर्णांक flags;

	/* Don't let पूर्णांकernal करो_tcp_sendpages() flags through */
	flags = (msg->msg_flags & ~MSG_SENDPAGE_DECRYPTED);
	flags |= MSG_NO_SHARED_FRAGS;

	psock = sk_psock_get(sk);
	अगर (unlikely(!psock))
		वापस tcp_sendmsg(sk, msg, size);

	lock_sock(sk);
	समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);
	जबतक (msg_data_left(msg)) अणु
		bool enospc = false;
		u32 copy, osize;

		अगर (sk->sk_err) अणु
			err = -sk->sk_err;
			जाओ out_err;
		पूर्ण

		copy = msg_data_left(msg);
		अगर (!sk_stream_memory_मुक्त(sk))
			जाओ रुको_क्रम_sndbuf;
		अगर (psock->cork) अणु
			msg_tx = psock->cork;
		पूर्ण अन्यथा अणु
			msg_tx = &पंचांगp;
			sk_msg_init(msg_tx);
		पूर्ण

		osize = msg_tx->sg.size;
		err = sk_msg_alloc(sk, msg_tx, msg_tx->sg.size + copy, msg_tx->sg.end - 1);
		अगर (err) अणु
			अगर (err != -ENOSPC)
				जाओ रुको_क्रम_memory;
			enospc = true;
			copy = msg_tx->sg.size - osize;
		पूर्ण

		err = sk_msg_memcopy_from_iter(sk, &msg->msg_iter, msg_tx,
					       copy);
		अगर (err < 0) अणु
			sk_msg_trim(sk, msg_tx, osize);
			जाओ out_err;
		पूर्ण

		copied += copy;
		अगर (psock->cork_bytes) अणु
			अगर (size > psock->cork_bytes)
				psock->cork_bytes = 0;
			अन्यथा
				psock->cork_bytes -= size;
			अगर (psock->cork_bytes && !enospc)
				जाओ out_err;
			/* All cork bytes are accounted, rerun the prog. */
			psock->eval = __SK_NONE;
			psock->cork_bytes = 0;
		पूर्ण

		err = tcp_bpf_send_verdict(sk, psock, msg_tx, &copied, flags);
		अगर (unlikely(err < 0))
			जाओ out_err;
		जारी;
रुको_क्रम_sndbuf:
		set_bit(SOCK_NOSPACE, &sk->sk_socket->flags);
रुको_क्रम_memory:
		err = sk_stream_रुको_memory(sk, &समयo);
		अगर (err) अणु
			अगर (msg_tx && msg_tx != psock->cork)
				sk_msg_मुक्त(sk, msg_tx);
			जाओ out_err;
		पूर्ण
	पूर्ण
out_err:
	अगर (err < 0)
		err = sk_stream_error(sk, msg->msg_flags, err);
	release_sock(sk);
	sk_psock_put(sk, psock);
	वापस copied ? copied : err;
पूर्ण

अटल पूर्णांक tcp_bpf_sendpage(काष्ठा sock *sk, काष्ठा page *page, पूर्णांक offset,
			    माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sk_msg पंचांगp, *msg = शून्य;
	पूर्णांक err = 0, copied = 0;
	काष्ठा sk_psock *psock;
	bool enospc = false;

	psock = sk_psock_get(sk);
	अगर (unlikely(!psock))
		वापस tcp_sendpage(sk, page, offset, size, flags);

	lock_sock(sk);
	अगर (psock->cork) अणु
		msg = psock->cork;
	पूर्ण अन्यथा अणु
		msg = &पंचांगp;
		sk_msg_init(msg);
	पूर्ण

	/* Catch हाल where ring is full and sendpage is stalled. */
	अगर (unlikely(sk_msg_full(msg)))
		जाओ out_err;

	sk_msg_page_add(msg, page, size, offset);
	sk_mem_अक्षरge(sk, size);
	copied = size;
	अगर (sk_msg_full(msg))
		enospc = true;
	अगर (psock->cork_bytes) अणु
		अगर (size > psock->cork_bytes)
			psock->cork_bytes = 0;
		अन्यथा
			psock->cork_bytes -= size;
		अगर (psock->cork_bytes && !enospc)
			जाओ out_err;
		/* All cork bytes are accounted, rerun the prog. */
		psock->eval = __SK_NONE;
		psock->cork_bytes = 0;
	पूर्ण

	err = tcp_bpf_send_verdict(sk, psock, msg, &copied, flags);
out_err:
	release_sock(sk);
	sk_psock_put(sk, psock);
	वापस copied ? copied : err;
पूर्ण

क्रमागत अणु
	TCP_BPF_IPV4,
	TCP_BPF_IPV6,
	TCP_BPF_NUM_PROTS,
पूर्ण;

क्रमागत अणु
	TCP_BPF_BASE,
	TCP_BPF_TX,
	TCP_BPF_NUM_CFGS,
पूर्ण;

अटल काष्ठा proto *tcpv6_prot_saved __पढ़ो_mostly;
अटल DEFINE_SPINLOCK(tcpv6_prot_lock);
अटल काष्ठा proto tcp_bpf_prots[TCP_BPF_NUM_PROTS][TCP_BPF_NUM_CFGS];

अटल व्योम tcp_bpf_rebuild_protos(काष्ठा proto prot[TCP_BPF_NUM_CFGS],
				   काष्ठा proto *base)
अणु
	prot[TCP_BPF_BASE]			= *base;
	prot[TCP_BPF_BASE].unhash		= sock_map_unhash;
	prot[TCP_BPF_BASE].बंद		= sock_map_बंद;
	prot[TCP_BPF_BASE].recvmsg		= tcp_bpf_recvmsg;
	prot[TCP_BPF_BASE].stream_memory_पढ़ो	= tcp_bpf_stream_पढ़ो;

	prot[TCP_BPF_TX]			= prot[TCP_BPF_BASE];
	prot[TCP_BPF_TX].sendmsg		= tcp_bpf_sendmsg;
	prot[TCP_BPF_TX].sendpage		= tcp_bpf_sendpage;
पूर्ण

अटल व्योम tcp_bpf_check_v6_needs_rebuild(काष्ठा proto *ops)
अणु
	अगर (unlikely(ops != smp_load_acquire(&tcpv6_prot_saved))) अणु
		spin_lock_bh(&tcpv6_prot_lock);
		अगर (likely(ops != tcpv6_prot_saved)) अणु
			tcp_bpf_rebuild_protos(tcp_bpf_prots[TCP_BPF_IPV6], ops);
			smp_store_release(&tcpv6_prot_saved, ops);
		पूर्ण
		spin_unlock_bh(&tcpv6_prot_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक __init tcp_bpf_v4_build_proto(व्योम)
अणु
	tcp_bpf_rebuild_protos(tcp_bpf_prots[TCP_BPF_IPV4], &tcp_prot);
	वापस 0;
पूर्ण
core_initcall(tcp_bpf_v4_build_proto);

अटल पूर्णांक tcp_bpf_निश्चित_proto_ops(काष्ठा proto *ops)
अणु
	/* In order to aव्योम retpoline, we make assumptions when we call
	 * पूर्णांकo ops अगर e.g. a psock is not present. Make sure they are
	 * indeed valid assumptions.
	 */
	वापस ops->recvmsg  == tcp_recvmsg &&
	       ops->sendmsg  == tcp_sendmsg &&
	       ops->sendpage == tcp_sendpage ? 0 : -ENOTSUPP;
पूर्ण

पूर्णांक tcp_bpf_update_proto(काष्ठा sock *sk, काष्ठा sk_psock *psock, bool restore)
अणु
	पूर्णांक family = sk->sk_family == AF_INET6 ? TCP_BPF_IPV6 : TCP_BPF_IPV4;
	पूर्णांक config = psock->progs.msg_parser   ? TCP_BPF_TX   : TCP_BPF_BASE;

	अगर (restore) अणु
		अगर (inet_csk_has_ulp(sk)) अणु
			/* TLS करोes not have an unhash proto in SW हालs,
			 * but we need to ensure we stop using the sock_map
			 * unhash routine because the associated psock is being
			 * हटाओd. So use the original unhash handler.
			 */
			WRITE_ONCE(sk->sk_prot->unhash, psock->saved_unhash);
			tcp_update_ulp(sk, psock->sk_proto, psock->saved_ग_लिखो_space);
		पूर्ण अन्यथा अणु
			sk->sk_ग_लिखो_space = psock->saved_ग_लिखो_space;
			/* Pairs with lockless पढ़ो in sk_clone_lock() */
			WRITE_ONCE(sk->sk_prot, psock->sk_proto);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (inet_csk_has_ulp(sk))
		वापस -EINVAL;

	अगर (sk->sk_family == AF_INET6) अणु
		अगर (tcp_bpf_निश्चित_proto_ops(psock->sk_proto))
			वापस -EINVAL;

		tcp_bpf_check_v6_needs_rebuild(psock->sk_proto);
	पूर्ण

	/* Pairs with lockless पढ़ो in sk_clone_lock() */
	WRITE_ONCE(sk->sk_prot, &tcp_bpf_prots[family][config]);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_bpf_update_proto);

/* If a child got cloned from a listening socket that had tcp_bpf
 * protocol callbacks installed, we need to restore the callbacks to
 * the शेष ones because the child करोes not inherit the psock state
 * that tcp_bpf callbacks expect.
 */
व्योम tcp_bpf_clone(स्थिर काष्ठा sock *sk, काष्ठा sock *newsk)
अणु
	पूर्णांक family = sk->sk_family == AF_INET6 ? TCP_BPF_IPV6 : TCP_BPF_IPV4;
	काष्ठा proto *prot = newsk->sk_prot;

	अगर (prot == &tcp_bpf_prots[family][TCP_BPF_BASE])
		newsk->sk_prot = sk->sk_prot_creator;
पूर्ण
#पूर्ण_अगर /* CONFIG_BPF_SYSCALL */
