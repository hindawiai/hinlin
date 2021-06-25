<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <net/tcp.h>
#समावेश <net/strparser.h>
#समावेश <net/xfrm.h>
#समावेश <net/esp.h>
#समावेश <net/espपूर्णांकcp.h>
#समावेश <linux/skmsg.h>
#समावेश <net/inet_common.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <net/ipv6_stubs.h>
#पूर्ण_अगर

अटल व्योम handle_nonesp(काष्ठा espपूर्णांकcp_ctx *ctx, काष्ठा sk_buff *skb,
			  काष्ठा sock *sk)
अणु
	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) >= sk->sk_rcvbuf ||
	    !sk_rmem_schedule(sk, skb, skb->truesize)) अणु
		XFRM_INC_STATS(sock_net(sk), LINUX_MIB_XFRMINERROR);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	skb_set_owner_r(skb, sk);

	स_रखो(skb->cb, 0, माप(skb->cb));
	skb_queue_tail(&ctx->ike_queue, skb);
	ctx->saved_data_पढ़ोy(sk);
पूर्ण

अटल व्योम handle_esp(काष्ठा sk_buff *skb, काष्ठा sock *sk)
अणु
	काष्ठा tcp_skb_cb *tcp_cb = (काष्ठा tcp_skb_cb *)skb->cb;

	skb_reset_transport_header(skb);

	/* restore IP CB, we need at least IP6CB->nhoff */
	स_हटाओ(skb->cb, &tcp_cb->header, माप(tcp_cb->header));

	rcu_पढ़ो_lock();
	skb->dev = dev_get_by_index_rcu(sock_net(sk), skb->skb_iअगर);
	local_bh_disable();
#अगर IS_ENABLED(CONFIG_IPV6)
	अगर (sk->sk_family == AF_INET6)
		ipv6_stub->xfrm6_rcv_encap(skb, IPPROTO_ESP, 0, TCP_ENCAP_ESPINTCP);
	अन्यथा
#पूर्ण_अगर
		xfrm4_rcv_encap(skb, IPPROTO_ESP, 0, TCP_ENCAP_ESPINTCP);
	local_bh_enable();
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम espपूर्णांकcp_rcv(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = container_of(strp, काष्ठा espपूर्णांकcp_ctx,
						strp);
	काष्ठा strp_msg *rxm = strp_msg(skb);
	पूर्णांक len = rxm->full_len - 2;
	u32 nonesp_marker;
	पूर्णांक err;

	/* keepalive packet? */
	अगर (unlikely(len == 1)) अणु
		u8 data;

		err = skb_copy_bits(skb, rxm->offset + 2, &data, 1);
		अगर (err < 0) अणु
			XFRM_INC_STATS(sock_net(strp->sk), LINUX_MIB_XFRMINHDRERROR);
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		अगर (data == 0xff) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण

	/* drop other लघु messages */
	अगर (unlikely(len <= माप(nonesp_marker))) अणु
		XFRM_INC_STATS(sock_net(strp->sk), LINUX_MIB_XFRMINHDRERROR);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	err = skb_copy_bits(skb, rxm->offset + 2, &nonesp_marker,
			    माप(nonesp_marker));
	अगर (err < 0) अणु
		XFRM_INC_STATS(sock_net(strp->sk), LINUX_MIB_XFRMINHDRERROR);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* हटाओ header, leave non-ESP marker/SPI */
	अगर (!__pskb_pull(skb, rxm->offset + 2)) अणु
		XFRM_INC_STATS(sock_net(strp->sk), LINUX_MIB_XFRMINERROR);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (pskb_trim(skb, rxm->full_len - 2) != 0) अणु
		XFRM_INC_STATS(sock_net(strp->sk), LINUX_MIB_XFRMINERROR);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (nonesp_marker == 0)
		handle_nonesp(ctx, skb, strp->sk);
	अन्यथा
		handle_esp(skb, strp->sk);
पूर्ण

अटल पूर्णांक espपूर्णांकcp_parse(काष्ठा strparser *strp, काष्ठा sk_buff *skb)
अणु
	काष्ठा strp_msg *rxm = strp_msg(skb);
	__be16 blen;
	u16 len;
	पूर्णांक err;

	अगर (skb->len < rxm->offset + 2)
		वापस 0;

	err = skb_copy_bits(skb, rxm->offset, &blen, माप(blen));
	अगर (err < 0)
		वापस err;

	len = be16_to_cpu(blen);
	अगर (len < 2)
		वापस -EINVAL;

	वापस len;
पूर्ण

अटल पूर्णांक espपूर्णांकcp_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			    पूर्णांक nonblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);
	काष्ठा sk_buff *skb;
	पूर्णांक err = 0;
	पूर्णांक copied;
	पूर्णांक off = 0;

	flags |= nonblock ? MSG_DONTWAIT : 0;

	skb = __skb_recv_datagram(sk, &ctx->ike_queue, flags, &off, &err);
	अगर (!skb) अणु
		अगर (err == -EAGAIN && sk->sk_shutकरोwn & RCV_SHUTDOWN)
			वापस 0;
		वापस err;
	पूर्ण

	copied = len;
	अगर (copied > skb->len)
		copied = skb->len;
	अन्यथा अगर (copied < skb->len)
		msg->msg_flags |= MSG_TRUNC;

	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (unlikely(err)) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	अगर (flags & MSG_TRUNC)
		copied = skb->len;
	kमुक्त_skb(skb);
	वापस copied;
पूर्ण

पूर्णांक espपूर्णांकcp_queue_out(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);

	अगर (skb_queue_len(&ctx->out_queue) >= netdev_max_backlog)
		वापस -ENOBUFS;

	__skb_queue_tail(&ctx->out_queue, skb);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(espपूर्णांकcp_queue_out);

/* espपूर्णांकcp length field is 2B and length includes the length field's size */
#घोषणा MAX_ESPINTCP_MSG (((1 << 16) - 1) - 2)

अटल पूर्णांक espपूर्णांकcp_sendskb_locked(काष्ठा sock *sk, काष्ठा espपूर्णांकcp_msg *emsg,
				   पूर्णांक flags)
अणु
	करो अणु
		पूर्णांक ret;

		ret = skb_send_sock_locked(sk, emsg->skb,
					   emsg->offset, emsg->len);
		अगर (ret < 0)
			वापस ret;

		emsg->len -= ret;
		emsg->offset += ret;
	पूर्ण जबतक (emsg->len > 0);

	kमुक्त_skb(emsg->skb);
	स_रखो(emsg, 0, माप(*emsg));

	वापस 0;
पूर्ण

अटल पूर्णांक espपूर्णांकcp_sendskmsg_locked(काष्ठा sock *sk,
				     काष्ठा espपूर्णांकcp_msg *emsg, पूर्णांक flags)
अणु
	काष्ठा sk_msg *skmsg = &emsg->skmsg;
	काष्ठा scatterlist *sg;
	पूर्णांक करोne = 0;
	पूर्णांक ret;

	flags |= MSG_SENDPAGE_NOTLAST;
	sg = &skmsg->sg.data[skmsg->sg.start];
	करो अणु
		माप_प्रकार size = sg->length - emsg->offset;
		पूर्णांक offset = sg->offset + emsg->offset;
		काष्ठा page *p;

		emsg->offset = 0;

		अगर (sg_is_last(sg))
			flags &= ~MSG_SENDPAGE_NOTLAST;

		p = sg_page(sg);
retry:
		ret = करो_tcp_sendpages(sk, p, offset, size, flags);
		अगर (ret < 0) अणु
			emsg->offset = offset - sg->offset;
			skmsg->sg.start += करोne;
			वापस ret;
		पूर्ण

		अगर (ret != size) अणु
			offset += ret;
			size -= ret;
			जाओ retry;
		पूर्ण

		करोne++;
		put_page(p);
		sk_mem_unअक्षरge(sk, sg->length);
		sg = sg_next(sg);
	पूर्ण जबतक (sg);

	स_रखो(emsg, 0, माप(*emsg));

	वापस 0;
पूर्ण

अटल पूर्णांक espपूर्णांकcp_push_msgs(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);
	काष्ठा espपूर्णांकcp_msg *emsg = &ctx->partial;
	पूर्णांक err;

	अगर (!emsg->len)
		वापस 0;

	अगर (ctx->tx_running)
		वापस -EAGAIN;
	ctx->tx_running = 1;

	अगर (emsg->skb)
		err = espपूर्णांकcp_sendskb_locked(sk, emsg, flags);
	अन्यथा
		err = espपूर्णांकcp_sendskmsg_locked(sk, emsg, flags);
	अगर (err == -EAGAIN) अणु
		ctx->tx_running = 0;
		वापस flags & MSG_DONTWAIT ? -EAGAIN : 0;
	पूर्ण
	अगर (!err)
		स_रखो(emsg, 0, माप(*emsg));

	ctx->tx_running = 0;

	वापस err;
पूर्ण

पूर्णांक espपूर्णांकcp_push_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);
	काष्ठा espपूर्णांकcp_msg *emsg = &ctx->partial;
	अचिन्हित पूर्णांक len;
	पूर्णांक offset;

	अगर (sk->sk_state != TCP_ESTABLISHED) अणु
		kमुक्त_skb(skb);
		वापस -ECONNRESET;
	पूर्ण

	offset = skb_transport_offset(skb);
	len = skb->len - offset;

	espपूर्णांकcp_push_msgs(sk, 0);

	अगर (emsg->len) अणु
		kमुक्त_skb(skb);
		वापस -ENOBUFS;
	पूर्ण

	skb_set_owner_w(skb, sk);

	emsg->offset = offset;
	emsg->len = len;
	emsg->skb = skb;

	espपूर्णांकcp_push_msgs(sk, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(espपूर्णांकcp_push_skb);

अटल पूर्णांक espपूर्णांकcp_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	दीर्घ समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);
	काष्ठा espपूर्णांकcp_msg *emsg = &ctx->partial;
	काष्ठा iov_iter pfx_iter;
	काष्ठा kvec pfx_iov = अणुपूर्ण;
	माप_प्रकार msglen = size + 2;
	अक्षर buf[2] = अणु0पूर्ण;
	पूर्णांक err, end;

	अगर (msg->msg_flags & ~MSG_DONTWAIT)
		वापस -EOPNOTSUPP;

	अगर (size > MAX_ESPINTCP_MSG)
		वापस -EMSGSIZE;

	अगर (msg->msg_controllen)
		वापस -EOPNOTSUPP;

	lock_sock(sk);

	err = espपूर्णांकcp_push_msgs(sk, msg->msg_flags & MSG_DONTWAIT);
	अगर (err < 0) अणु
		अगर (err != -EAGAIN || !(msg->msg_flags & MSG_DONTWAIT))
			err = -ENOBUFS;
		जाओ unlock;
	पूर्ण

	sk_msg_init(&emsg->skmsg);
	जबतक (1) अणु
		/* only -ENOMEM is possible since we करोn't coalesce */
		err = sk_msg_alloc(sk, &emsg->skmsg, msglen, 0);
		अगर (!err)
			अवरोध;

		err = sk_stream_रुको_memory(sk, &समयo);
		अगर (err)
			जाओ fail;
	पूर्ण

	*((__be16 *)buf) = cpu_to_be16(msglen);
	pfx_iov.iov_base = buf;
	pfx_iov.iov_len = माप(buf);
	iov_iter_kvec(&pfx_iter, WRITE, &pfx_iov, 1, pfx_iov.iov_len);

	err = sk_msg_memcopy_from_iter(sk, &pfx_iter, &emsg->skmsg,
				       pfx_iov.iov_len);
	अगर (err < 0)
		जाओ fail;

	err = sk_msg_memcopy_from_iter(sk, &msg->msg_iter, &emsg->skmsg, size);
	अगर (err < 0)
		जाओ fail;

	end = emsg->skmsg.sg.end;
	emsg->len = size;
	sk_msg_iter_var_prev(end);
	sg_mark_end(sk_msg_elem(&emsg->skmsg, end));

	tcp_rate_check_app_limited(sk);

	err = espपूर्णांकcp_push_msgs(sk, msg->msg_flags & MSG_DONTWAIT);
	/* this message could be partially sent, keep it */

	release_sock(sk);

	वापस size;

fail:
	sk_msg_मुक्त(sk, &emsg->skmsg);
	स_रखो(emsg, 0, माप(*emsg));
unlock:
	release_sock(sk);
	वापस err;
पूर्ण

अटल काष्ठा proto espपूर्णांकcp_prot __ro_after_init;
अटल काष्ठा proto_ops espपूर्णांकcp_ops __ro_after_init;
अटल काष्ठा proto espपूर्णांकcp6_prot;
अटल काष्ठा proto_ops espपूर्णांकcp6_ops;
अटल DEFINE_MUTEX(tcpv6_prot_mutex);

अटल व्योम espपूर्णांकcp_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);

	strp_data_पढ़ोy(&ctx->strp);
पूर्ण

अटल व्योम espपूर्णांकcp_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = container_of(work,
						काष्ठा espपूर्णांकcp_ctx, work);
	काष्ठा sock *sk = ctx->strp.sk;

	lock_sock(sk);
	अगर (!ctx->tx_running)
		espपूर्णांकcp_push_msgs(sk, 0);
	release_sock(sk);
पूर्ण

अटल व्योम espपूर्णांकcp_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);

	schedule_work(&ctx->work);
	ctx->saved_ग_लिखो_space(sk);
पूर्ण

अटल व्योम espपूर्णांकcp_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);

	ctx->saved_deकाष्ठा(sk);
	kमुक्त(ctx);
पूर्ण

bool tcp_is_ulp_esp(काष्ठा sock *sk)
अणु
	वापस sk->sk_prot == &espपूर्णांकcp_prot || sk->sk_prot == &espपूर्णांकcp6_prot;
पूर्ण
EXPORT_SYMBOL_GPL(tcp_is_ulp_esp);

अटल व्योम build_protos(काष्ठा proto *espपूर्णांकcp_prot,
			 काष्ठा proto_ops *espपूर्णांकcp_ops,
			 स्थिर काष्ठा proto *orig_prot,
			 स्थिर काष्ठा proto_ops *orig_ops);
अटल पूर्णांक espपूर्णांकcp_init_sk(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा strp_callbacks cb = अणु
		.rcv_msg = espपूर्णांकcp_rcv,
		.parse_msg = espपूर्णांकcp_parse,
	पूर्ण;
	काष्ठा espपूर्णांकcp_ctx *ctx;
	पूर्णांक err;

	/* sockmap is not compatible with espपूर्णांकcp */
	अगर (sk->sk_user_data)
		वापस -EBUSY;

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	err = strp_init(&ctx->strp, sk, &cb);
	अगर (err)
		जाओ मुक्त;

	__sk_dst_reset(sk);

	strp_check_rcv(&ctx->strp);
	skb_queue_head_init(&ctx->ike_queue);
	skb_queue_head_init(&ctx->out_queue);

	अगर (sk->sk_family == AF_INET) अणु
		sk->sk_prot = &espपूर्णांकcp_prot;
		sk->sk_socket->ops = &espपूर्णांकcp_ops;
	पूर्ण अन्यथा अणु
		mutex_lock(&tcpv6_prot_mutex);
		अगर (!espपूर्णांकcp6_prot.recvmsg)
			build_protos(&espपूर्णांकcp6_prot, &espपूर्णांकcp6_ops, sk->sk_prot, sk->sk_socket->ops);
		mutex_unlock(&tcpv6_prot_mutex);

		sk->sk_prot = &espपूर्णांकcp6_prot;
		sk->sk_socket->ops = &espपूर्णांकcp6_ops;
	पूर्ण
	ctx->saved_data_पढ़ोy = sk->sk_data_पढ़ोy;
	ctx->saved_ग_लिखो_space = sk->sk_ग_लिखो_space;
	ctx->saved_deकाष्ठा = sk->sk_deकाष्ठा;
	sk->sk_data_पढ़ोy = espपूर्णांकcp_data_पढ़ोy;
	sk->sk_ग_लिखो_space = espपूर्णांकcp_ग_लिखो_space;
	sk->sk_deकाष्ठा = espपूर्णांकcp_deकाष्ठा;
	rcu_assign_poपूर्णांकer(icsk->icsk_ulp_data, ctx);
	INIT_WORK(&ctx->work, espपूर्णांकcp_tx_work);

	/* aव्योम using task_frag */
	sk->sk_allocation = GFP_ATOMIC;

	वापस 0;

मुक्त:
	kमुक्त(ctx);
	वापस err;
पूर्ण

अटल व्योम espपूर्णांकcp_release(काष्ठा sock *sk)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);
	काष्ठा sk_buff_head queue;
	काष्ठा sk_buff *skb;

	__skb_queue_head_init(&queue);
	skb_queue_splice_init(&ctx->out_queue, &queue);

	जबतक ((skb = __skb_dequeue(&queue)))
		espपूर्णांकcp_push_skb(sk, skb);

	tcp_release_cb(sk);
पूर्ण

अटल व्योम espपूर्णांकcp_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);
	काष्ठा espपूर्णांकcp_msg *emsg = &ctx->partial;

	strp_stop(&ctx->strp);

	sk->sk_prot = &tcp_prot;
	barrier();

	cancel_work_sync(&ctx->work);
	strp_करोne(&ctx->strp);

	skb_queue_purge(&ctx->out_queue);
	skb_queue_purge(&ctx->ike_queue);

	अगर (emsg->len) अणु
		अगर (emsg->skb)
			kमुक्त_skb(emsg->skb);
		अन्यथा
			sk_msg_मुक्त(sk, &emsg->skmsg);
	पूर्ण

	tcp_बंद(sk, समयout);
पूर्ण

अटल __poll_t espपूर्णांकcp_poll(काष्ठा file *file, काष्ठा socket *sock,
			      poll_table *रुको)
अणु
	__poll_t mask = datagram_poll(file, sock, रुको);
	काष्ठा sock *sk = sock->sk;
	काष्ठा espपूर्णांकcp_ctx *ctx = espपूर्णांकcp_अ_लोtx(sk);

	अगर (!skb_queue_empty(&ctx->ike_queue))
		mask |= EPOLLIN | EPOLLRDNORM;

	वापस mask;
पूर्ण

अटल व्योम build_protos(काष्ठा proto *espपूर्णांकcp_prot,
			 काष्ठा proto_ops *espपूर्णांकcp_ops,
			 स्थिर काष्ठा proto *orig_prot,
			 स्थिर काष्ठा proto_ops *orig_ops)
अणु
	स_नकल(espपूर्णांकcp_prot, orig_prot, माप(काष्ठा proto));
	स_नकल(espपूर्णांकcp_ops, orig_ops, माप(काष्ठा proto_ops));
	espपूर्णांकcp_prot->sendmsg = espपूर्णांकcp_sendmsg;
	espपूर्णांकcp_prot->recvmsg = espपूर्णांकcp_recvmsg;
	espपूर्णांकcp_prot->बंद = espपूर्णांकcp_बंद;
	espपूर्णांकcp_prot->release_cb = espपूर्णांकcp_release;
	espपूर्णांकcp_ops->poll = espपूर्णांकcp_poll;
पूर्ण

अटल काष्ठा tcp_ulp_ops espपूर्णांकcp_ulp __पढ़ो_mostly = अणु
	.name = "espintcp",
	.owner = THIS_MODULE,
	.init = espपूर्णांकcp_init_sk,
पूर्ण;

व्योम __init espपूर्णांकcp_init(व्योम)
अणु
	build_protos(&espपूर्णांकcp_prot, &espपूर्णांकcp_ops, &tcp_prot, &inet_stream_ops);

	tcp_रेजिस्टर_ulp(&espपूर्णांकcp_ulp);
पूर्ण
