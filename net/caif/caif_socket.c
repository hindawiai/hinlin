<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ":%s(): " fmt, __func__

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/poll.h>
#समावेश <linux/tcp.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/caअगर/caअगर_socket.h>
#समावेश <linux/pkt_sched.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/caअगर_dev.h>
#समावेश <net/caअगर/cfpkt.h>

MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(AF_CAIF);

/*
 * CAIF state is re-using the TCP socket states.
 * caअगर_states stored in sk_state reflect the state as reported by
 * the CAIF stack, जबतक sk_socket->state is the state of the socket.
 */
क्रमागत caअगर_states अणु
	CAIF_CONNECTED		= TCP_ESTABLISHED,
	CAIF_CONNECTING	= TCP_SYN_SENT,
	CAIF_DISCONNECTED	= TCP_CLOSE
पूर्ण;

#घोषणा TX_FLOW_ON_BIT	1
#घोषणा RX_FLOW_ON_BIT	2

काष्ठा caअगरsock अणु
	काष्ठा sock sk; /* must be first member */
	काष्ठा cflayer layer;
	u32 flow_state;
	काष्ठा caअगर_connect_request conn_req;
	काष्ठा mutex पढ़ोlock;
	काष्ठा dentry *debugfs_socket_dir;
	पूर्णांक headroom, tailroom, maxframe;
पूर्ण;

अटल पूर्णांक rx_flow_is_on(काष्ठा caअगरsock *cf_sk)
अणु
	वापस test_bit(RX_FLOW_ON_BIT,
			(व्योम *) &cf_sk->flow_state);
पूर्ण

अटल पूर्णांक tx_flow_is_on(काष्ठा caअगरsock *cf_sk)
अणु
	वापस test_bit(TX_FLOW_ON_BIT,
			(व्योम *) &cf_sk->flow_state);
पूर्ण

अटल व्योम set_rx_flow_off(काष्ठा caअगरsock *cf_sk)
अणु
	 clear_bit(RX_FLOW_ON_BIT,
		 (व्योम *) &cf_sk->flow_state);
पूर्ण

अटल व्योम set_rx_flow_on(काष्ठा caअगरsock *cf_sk)
अणु
	 set_bit(RX_FLOW_ON_BIT,
			(व्योम *) &cf_sk->flow_state);
पूर्ण

अटल व्योम set_tx_flow_off(काष्ठा caअगरsock *cf_sk)
अणु
	 clear_bit(TX_FLOW_ON_BIT,
		(व्योम *) &cf_sk->flow_state);
पूर्ण

अटल व्योम set_tx_flow_on(काष्ठा caअगरsock *cf_sk)
अणु
	 set_bit(TX_FLOW_ON_BIT,
		(व्योम *) &cf_sk->flow_state);
पूर्ण

अटल व्योम caअगर_पढ़ो_lock(काष्ठा sock *sk)
अणु
	काष्ठा caअगरsock *cf_sk;
	cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	mutex_lock(&cf_sk->पढ़ोlock);
पूर्ण

अटल व्योम caअगर_पढ़ो_unlock(काष्ठा sock *sk)
अणु
	काष्ठा caअगरsock *cf_sk;
	cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	mutex_unlock(&cf_sk->पढ़ोlock);
पूर्ण

अटल पूर्णांक sk_rcvbuf_lowwater(काष्ठा caअगरsock *cf_sk)
अणु
	/* A quarter of full buffer is used a low water mark */
	वापस cf_sk->sk.sk_rcvbuf / 4;
पूर्ण

अटल व्योम caअगर_flow_ctrl(काष्ठा sock *sk, पूर्णांक mode)
अणु
	काष्ठा caअगरsock *cf_sk;
	cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	अगर (cf_sk->layer.dn && cf_sk->layer.dn->modemcmd)
		cf_sk->layer.dn->modemcmd(cf_sk->layer.dn, mode);
पूर्ण

/*
 * Copied from sock.c:sock_queue_rcv_skb(), but changed so packets are
 * not dropped, but CAIF is sending flow off instead.
 */
अटल व्योम caअगर_queue_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff_head *list = &sk->sk_receive_queue;
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	bool queued = false;

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) + skb->truesize >=
		(अचिन्हित पूर्णांक)sk->sk_rcvbuf && rx_flow_is_on(cf_sk)) अणु
		net_dbg_ratelimited("sending flow OFF (queue len = %d %d)\n",
				    atomic_पढ़ो(&cf_sk->sk.sk_rmem_alloc),
				    sk_rcvbuf_lowwater(cf_sk));
		set_rx_flow_off(cf_sk);
		caअगर_flow_ctrl(sk, CAIF_MODEMCMD_FLOW_OFF_REQ);
	पूर्ण

	err = sk_filter(sk, skb);
	अगर (err)
		जाओ out;

	अगर (!sk_rmem_schedule(sk, skb, skb->truesize) && rx_flow_is_on(cf_sk)) अणु
		set_rx_flow_off(cf_sk);
		net_dbg_ratelimited("sending flow OFF due to rmem_schedule\n");
		caअगर_flow_ctrl(sk, CAIF_MODEMCMD_FLOW_OFF_REQ);
	पूर्ण
	skb->dev = शून्य;
	skb_set_owner_r(skb, sk);
	spin_lock_irqsave(&list->lock, flags);
	queued = !sock_flag(sk, SOCK_DEAD);
	अगर (queued)
		__skb_queue_tail(list, skb);
	spin_unlock_irqrestore(&list->lock, flags);
out:
	अगर (queued)
		sk->sk_data_पढ़ोy(sk);
	अन्यथा
		kमुक्त_skb(skb);
पूर्ण

/* Packet Receive Callback function called from CAIF Stack */
अटल पूर्णांक caअगर_sktrecv_cb(काष्ठा cflayer *layr, काष्ठा cfpkt *pkt)
अणु
	काष्ठा caअगरsock *cf_sk;
	काष्ठा sk_buff *skb;

	cf_sk = container_of(layr, काष्ठा caअगरsock, layer);
	skb = cfpkt_tonative(pkt);

	अगर (unlikely(cf_sk->sk.sk_state != CAIF_CONNECTED)) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण
	caअगर_queue_rcv_skb(&cf_sk->sk, skb);
	वापस 0;
पूर्ण

अटल व्योम cfsk_hold(काष्ठा cflayer *layr)
अणु
	काष्ठा caअगरsock *cf_sk = container_of(layr, काष्ठा caअगरsock, layer);
	sock_hold(&cf_sk->sk);
पूर्ण

अटल व्योम cfsk_put(काष्ठा cflayer *layr)
अणु
	काष्ठा caअगरsock *cf_sk = container_of(layr, काष्ठा caअगरsock, layer);
	sock_put(&cf_sk->sk);
पूर्ण

/* Packet Control Callback function called from CAIF */
अटल व्योम caअगर_ctrl_cb(काष्ठा cflayer *layr,
			 क्रमागत caअगर_ctrlcmd flow,
			 पूर्णांक phyid)
अणु
	काष्ठा caअगरsock *cf_sk = container_of(layr, काष्ठा caअगरsock, layer);
	चयन (flow) अणु
	हाल CAIF_CTRLCMD_FLOW_ON_IND:
		/* OK from modem to start sending again */
		set_tx_flow_on(cf_sk);
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		अवरोध;

	हाल CAIF_CTRLCMD_FLOW_OFF_IND:
		/* Modem asks us to shut up */
		set_tx_flow_off(cf_sk);
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		अवरोध;

	हाल CAIF_CTRLCMD_INIT_RSP:
		/* We're now connected */
		caअगर_client_रेजिस्टर_refcnt(&cf_sk->layer,
						cfsk_hold, cfsk_put);
		cf_sk->sk.sk_state = CAIF_CONNECTED;
		set_tx_flow_on(cf_sk);
		cf_sk->sk.sk_shutकरोwn = 0;
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		अवरोध;

	हाल CAIF_CTRLCMD_DEINIT_RSP:
		/* We're now disconnected */
		cf_sk->sk.sk_state = CAIF_DISCONNECTED;
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		अवरोध;

	हाल CAIF_CTRLCMD_INIT_FAIL_RSP:
		/* Connect request failed */
		cf_sk->sk.sk_err = ECONNREFUSED;
		cf_sk->sk.sk_state = CAIF_DISCONNECTED;
		cf_sk->sk.sk_shutकरोwn = SHUTDOWN_MASK;
		/*
		 * Socket "standards" seems to require POLLOUT to
		 * be set at connect failure.
		 */
		set_tx_flow_on(cf_sk);
		cf_sk->sk.sk_state_change(&cf_sk->sk);
		अवरोध;

	हाल CAIF_CTRLCMD_REMOTE_SHUTDOWN_IND:
		/* Modem has बंदd this connection, or device is करोwn. */
		cf_sk->sk.sk_shutकरोwn = SHUTDOWN_MASK;
		cf_sk->sk.sk_err = ECONNRESET;
		set_rx_flow_on(cf_sk);
		cf_sk->sk.sk_error_report(&cf_sk->sk);
		अवरोध;

	शेष:
		pr_debug("Unexpected flow command %d\n", flow);
	पूर्ण
पूर्ण

अटल व्योम caअगर_check_flow_release(काष्ठा sock *sk)
अणु
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);

	अगर (rx_flow_is_on(cf_sk))
		वापस;

	अगर (atomic_पढ़ो(&sk->sk_rmem_alloc) <= sk_rcvbuf_lowwater(cf_sk)) अणु
			set_rx_flow_on(cf_sk);
			caअगर_flow_ctrl(sk, CAIF_MODEMCMD_FLOW_ON_REQ);
	पूर्ण
पूर्ण

/*
 * Copied from unix_dgram_recvmsg, but हटाओd credit checks,
 * changed locking, address handling and added MSG_TRUNC.
 */
अटल पूर्णांक caअगर_seqpkt_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *m,
			       माप_प्रकार len, पूर्णांक flags)

अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक ret;
	पूर्णांक copylen;

	ret = -EOPNOTSUPP;
	अगर (flags & MSG_OOB)
		जाओ पढ़ो_error;

	skb = skb_recv_datagram(sk, flags, 0 , &ret);
	अगर (!skb)
		जाओ पढ़ो_error;
	copylen = skb->len;
	अगर (len < copylen) अणु
		m->msg_flags |= MSG_TRUNC;
		copylen = len;
	पूर्ण

	ret = skb_copy_datagram_msg(skb, 0, m, copylen);
	अगर (ret)
		जाओ out_मुक्त;

	ret = (flags & MSG_TRUNC) ? skb->len : copylen;
out_मुक्त:
	skb_मुक्त_datagram(sk, skb);
	caअगर_check_flow_release(sk);
	वापस ret;

पढ़ो_error:
	वापस ret;
पूर्ण


/* Copied from unix_stream_रुको_data, identical except क्रम lock call. */
अटल दीर्घ caअगर_stream_data_रुको(काष्ठा sock *sk, दीर्घ समयo)
अणु
	DEFINE_WAIT(रुको);
	lock_sock(sk);

	क्रम (;;) अणु
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);

		अगर (!skb_queue_empty(&sk->sk_receive_queue) ||
			sk->sk_err ||
			sk->sk_state != CAIF_CONNECTED ||
			sock_flag(sk, SOCK_DEAD) ||
			(sk->sk_shutकरोwn & RCV_SHUTDOWN) ||
			संकेत_pending(current) ||
			!समयo)
			अवरोध;

		sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
		release_sock(sk);
		समयo = schedule_समयout(समयo);
		lock_sock(sk);

		अगर (sock_flag(sk, SOCK_DEAD))
			अवरोध;

		sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	पूर्ण

	finish_रुको(sk_sleep(sk), &रुको);
	release_sock(sk);
	वापस समयo;
पूर्ण


/*
 * Copied from unix_stream_recvmsg, but हटाओd credit checks,
 * changed locking calls, changed address handling.
 */
अटल पूर्णांक caअगर_stream_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक copied = 0;
	पूर्णांक target;
	पूर्णांक err = 0;
	दीर्घ समयo;

	err = -EOPNOTSUPP;
	अगर (flags&MSG_OOB)
		जाओ out;

	/*
	 * Lock the socket to prevent queue disordering
	 * जबतक sleeps in स_नकल_tomsg
	 */
	err = -EAGAIN;
	अगर (sk->sk_state == CAIF_CONNECTING)
		जाओ out;

	caअगर_पढ़ो_lock(sk);
	target = sock_rcvlowat(sk, flags&MSG_WAITALL, size);
	समयo = sock_rcvसमयo(sk, flags&MSG_DONTWAIT);

	करो अणु
		पूर्णांक chunk;
		काष्ठा sk_buff *skb;

		lock_sock(sk);
		अगर (sock_flag(sk, SOCK_DEAD)) अणु
			err = -ECONNRESET;
			जाओ unlock;
		पूर्ण
		skb = skb_dequeue(&sk->sk_receive_queue);
		caअगर_check_flow_release(sk);

		अगर (skb == शून्य) अणु
			अगर (copied >= target)
				जाओ unlock;
			/*
			 *	POSIX 1003.1g mandates this order.
			 */
			err = sock_error(sk);
			अगर (err)
				जाओ unlock;
			err = -ECONNRESET;
			अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
				जाओ unlock;

			err = -EPIPE;
			अगर (sk->sk_state != CAIF_CONNECTED)
				जाओ unlock;
			अगर (sock_flag(sk, SOCK_DEAD))
				जाओ unlock;

			release_sock(sk);

			err = -EAGAIN;
			अगर (!समयo)
				अवरोध;

			caअगर_पढ़ो_unlock(sk);

			समयo = caअगर_stream_data_रुको(sk, समयo);

			अगर (संकेत_pending(current)) अणु
				err = sock_पूर्णांकr_त्रुटि_सं(समयo);
				जाओ out;
			पूर्ण
			caअगर_पढ़ो_lock(sk);
			जारी;
unlock:
			release_sock(sk);
			अवरोध;
		पूर्ण
		release_sock(sk);
		chunk = min_t(अचिन्हित पूर्णांक, skb->len, size);
		अगर (स_नकल_to_msg(msg, skb->data, chunk)) अणु
			skb_queue_head(&sk->sk_receive_queue, skb);
			अगर (copied == 0)
				copied = -EFAULT;
			अवरोध;
		पूर्ण
		copied += chunk;
		size -= chunk;

		/* Mark पढ़ो part of skb as used */
		अगर (!(flags & MSG_PEEK)) अणु
			skb_pull(skb, chunk);

			/* put the skb back अगर we didn't use it up. */
			अगर (skb->len) अणु
				skb_queue_head(&sk->sk_receive_queue, skb);
				अवरोध;
			पूर्ण
			kमुक्त_skb(skb);

		पूर्ण अन्यथा अणु
			/*
			 * It is questionable, see note in unix_dgram_recvmsg.
			 */
			/* put message back and वापस */
			skb_queue_head(&sk->sk_receive_queue, skb);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (size);
	caअगर_पढ़ो_unlock(sk);

out:
	वापस copied ? : err;
पूर्ण

/*
 * Copied from sock.c:sock_रुको_क्रम_wmem, but change to रुको क्रम
 * CAIF flow-on and sock_writable.
 */
अटल दीर्घ caअगर_रुको_क्रम_flow_on(काष्ठा caअगरsock *cf_sk,
				  पूर्णांक रुको_ग_लिखोable, दीर्घ समयo, पूर्णांक *err)
अणु
	काष्ठा sock *sk = &cf_sk->sk;
	DEFINE_WAIT(रुको);
	क्रम (;;) अणु
		*err = 0;
		अगर (tx_flow_is_on(cf_sk) &&
			(!रुको_ग_लिखोable || sock_ग_लिखोable(&cf_sk->sk)))
			अवरोध;
		*err = -ETIMEDOUT;
		अगर (!समयo)
			अवरोध;
		*err = -ERESTARTSYS;
		अगर (संकेत_pending(current))
			अवरोध;
		prepare_to_रुको(sk_sleep(sk), &रुको, TASK_INTERRUPTIBLE);
		*err = -ECONNRESET;
		अगर (sk->sk_shutकरोwn & SHUTDOWN_MASK)
			अवरोध;
		*err = -sk->sk_err;
		अगर (sk->sk_err)
			अवरोध;
		*err = -EPIPE;
		अगर (cf_sk->sk.sk_state != CAIF_CONNECTED)
			अवरोध;
		समयo = schedule_समयout(समयo);
	पूर्ण
	finish_रुको(sk_sleep(sk), &रुको);
	वापस समयo;
पूर्ण

/*
 * Transmit a SKB. The device may temporarily request re-transmission
 * by वापसing EAGAIN.
 */
अटल पूर्णांक transmit_skb(काष्ठा sk_buff *skb, काष्ठा caअगरsock *cf_sk,
			पूर्णांक noblock, दीर्घ समयo)
अणु
	काष्ठा cfpkt *pkt;

	pkt = cfpkt_fromnative(CAIF_सूची_OUT, skb);
	स_रखो(skb->cb, 0, माप(काष्ठा caअगर_payload_info));
	cfpkt_set_prio(pkt, cf_sk->sk.sk_priority);

	अगर (cf_sk->layer.dn == शून्य) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	वापस cf_sk->layer.dn->transmit(cf_sk->layer.dn, pkt);
पूर्ण

/* Copied from af_unix:unix_dgram_sendmsg, and adapted to CAIF */
अटल पूर्णांक caअगर_seqpkt_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	पूर्णांक buffer_size;
	पूर्णांक ret = 0;
	काष्ठा sk_buff *skb = शून्य;
	पूर्णांक noblock;
	दीर्घ समयo;
	caअगर_निश्चित(cf_sk);
	ret = sock_error(sk);
	अगर (ret)
		जाओ err;

	ret = -EOPNOTSUPP;
	अगर (msg->msg_flags&MSG_OOB)
		जाओ err;

	ret = -EOPNOTSUPP;
	अगर (msg->msg_namelen)
		जाओ err;

	ret = -EINVAL;
	अगर (unlikely(msg->msg_iter.iov->iov_base == शून्य))
		जाओ err;
	noblock = msg->msg_flags & MSG_DONTWAIT;

	समयo = sock_sndसमयo(sk, noblock);
	समयo = caअगर_रुको_क्रम_flow_on(container_of(sk, काष्ठा caअगरsock, sk),
				1, समयo, &ret);

	अगर (ret)
		जाओ err;
	ret = -EPIPE;
	अगर (cf_sk->sk.sk_state != CAIF_CONNECTED ||
		sock_flag(sk, SOCK_DEAD) ||
		(sk->sk_shutकरोwn & RCV_SHUTDOWN))
		जाओ err;

	/* Error अगर trying to ग_लिखो more than maximum frame size. */
	ret = -EMSGSIZE;
	अगर (len > cf_sk->maxframe && cf_sk->sk.sk_protocol != CAIFPROTO_RFM)
		जाओ err;

	buffer_size = len + cf_sk->headroom + cf_sk->tailroom;

	ret = -ENOMEM;
	skb = sock_alloc_send_skb(sk, buffer_size, noblock, &ret);

	अगर (!skb || skb_tailroom(skb) < buffer_size)
		जाओ err;

	skb_reserve(skb, cf_sk->headroom);

	ret = स_नकल_from_msg(skb_put(skb, len), msg, len);

	अगर (ret)
		जाओ err;
	ret = transmit_skb(skb, cf_sk, noblock, समयo);
	अगर (ret < 0)
		/* skb is alपढ़ोy मुक्तd */
		वापस ret;

	वापस len;
err:
	kमुक्त_skb(skb);
	वापस ret;
पूर्ण

/*
 * Copied from unix_stream_sendmsg and adapted to CAIF:
 * Changed हटाओd permission handling and added रुकोing क्रम flow on
 * and other minor adaptations.
 */
अटल पूर्णांक caअगर_stream_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			       माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	पूर्णांक err, size;
	काष्ठा sk_buff *skb;
	पूर्णांक sent = 0;
	दीर्घ समयo;

	err = -EOPNOTSUPP;
	अगर (unlikely(msg->msg_flags&MSG_OOB))
		जाओ out_err;

	अगर (unlikely(msg->msg_namelen))
		जाओ out_err;

	समयo = sock_sndसमयo(sk, msg->msg_flags & MSG_DONTWAIT);
	समयo = caअगर_रुको_क्रम_flow_on(cf_sk, 1, समयo, &err);

	अगर (unlikely(sk->sk_shutकरोwn & SEND_SHUTDOWN))
		जाओ pipe_err;

	जबतक (sent < len) अणु

		size = len-sent;

		अगर (size > cf_sk->maxframe)
			size = cf_sk->maxframe;

		/* If size is more than half of sndbuf, chop up message */
		अगर (size > ((sk->sk_sndbuf >> 1) - 64))
			size = (sk->sk_sndbuf >> 1) - 64;

		अगर (size > SKB_MAX_ALLOC)
			size = SKB_MAX_ALLOC;

		skb = sock_alloc_send_skb(sk,
					size + cf_sk->headroom +
					cf_sk->tailroom,
					msg->msg_flags&MSG_DONTWAIT,
					&err);
		अगर (skb == शून्य)
			जाओ out_err;

		skb_reserve(skb, cf_sk->headroom);
		/*
		 *	If you pass two values to the sock_alloc_send_skb
		 *	it tries to grab the large buffer with GFP_NOFS
		 *	(which can fail easily), and अगर it fails grab the
		 *	fallback size buffer which is under a page and will
		 *	succeed. [Alan]
		 */
		size = min_t(पूर्णांक, size, skb_tailroom(skb));

		err = स_नकल_from_msg(skb_put(skb, size), msg, size);
		अगर (err) अणु
			kमुक्त_skb(skb);
			जाओ out_err;
		पूर्ण
		err = transmit_skb(skb, cf_sk,
				msg->msg_flags&MSG_DONTWAIT, समयo);
		अगर (err < 0)
			/* skb is alपढ़ोy मुक्तd */
			जाओ pipe_err;

		sent += size;
	पूर्ण

	वापस sent;

pipe_err:
	अगर (sent == 0 && !(msg->msg_flags&MSG_NOSIGNAL))
		send_sig(SIGPIPE, current, 0);
	err = -EPIPE;
out_err:
	वापस sent ? : err;
पूर्ण

अटल पूर्णांक setsockopt(काष्ठा socket *sock, पूर्णांक lvl, पूर्णांक opt, sockptr_t ov,
		अचिन्हित पूर्णांक ol)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	पूर्णांक linksel;

	अगर (cf_sk->sk.sk_socket->state != SS_UNCONNECTED)
		वापस -ENOPROTOOPT;

	चयन (opt) अणु
	हाल CAIFSO_LINK_SELECT:
		अगर (ol < माप(पूर्णांक))
			वापस -EINVAL;
		अगर (lvl != SOL_CAIF)
			जाओ bad_sol;
		अगर (copy_from_sockptr(&linksel, ov, माप(पूर्णांक)))
			वापस -EINVAL;
		lock_sock(&(cf_sk->sk));
		cf_sk->conn_req.link_selector = linksel;
		release_sock(&cf_sk->sk);
		वापस 0;

	हाल CAIFSO_REQ_PARAM:
		अगर (lvl != SOL_CAIF)
			जाओ bad_sol;
		अगर (cf_sk->sk.sk_protocol != CAIFPROTO_UTIL)
			वापस -ENOPROTOOPT;
		lock_sock(&(cf_sk->sk));
		अगर (ol > माप(cf_sk->conn_req.param.data) ||
		    copy_from_sockptr(&cf_sk->conn_req.param.data, ov, ol)) अणु
			release_sock(&cf_sk->sk);
			वापस -EINVAL;
		पूर्ण
		cf_sk->conn_req.param.size = ol;
		release_sock(&cf_sk->sk);
		वापस 0;

	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	वापस 0;
bad_sol:
	वापस -ENOPROTOOPT;

पूर्ण

/*
 * caअगर_connect() - Connect a CAIF Socket
 * Copied and modअगरied af_irda.c:irda_connect().
 *
 * Note : by consulting "errno", the user space caller may learn the cause
 * of the failure. Most of them are visible in the function, others may come
 * from subroutines called and are listed here :
 *  o -EAFNOSUPPORT: bad socket family or type.
 *  o -ESOCKTNOSUPPORT: bad socket type or protocol
 *  o -EINVAL: bad socket address, or CAIF link type
 *  o -ECONNREFUSED: remote end refused the connection.
 *  o -EINPROGRESS: connect request sent but समयd out (or non-blocking)
 *  o -EISCONN: alपढ़ोy connected.
 *  o -ETIMEDOUT: Connection समयd out (send समयout)
 *  o -ENODEV: No link layer to send request
 *  o -ECONNRESET: Received Shutकरोwn indication or lost link layer
 *  o -ENOMEM: Out of memory
 *
 *  State Strategy:
 *  o sk_state: holds the CAIF_* protocol state, it's updated by
 *	caअगर_ctrl_cb.
 *  o sock->state: holds the SS_* socket state and is updated by connect and
 *	disconnect.
 */
अटल पूर्णांक caअगर_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
			पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	दीर्घ समयo;
	पूर्णांक err;
	पूर्णांक अगरindex, headroom, tailroom;
	अचिन्हित पूर्णांक mtu;
	काष्ठा net_device *dev;

	lock_sock(sk);

	err = -EINVAL;
	अगर (addr_len < दुरत्वend(काष्ठा sockaddr, sa_family))
		जाओ out;

	err = -EAFNOSUPPORT;
	अगर (uaddr->sa_family != AF_CAIF)
		जाओ out;

	चयन (sock->state) अणु
	हाल SS_UNCONNECTED:
		/* Normal हाल, a fresh connect */
		caअगर_निश्चित(sk->sk_state == CAIF_DISCONNECTED);
		अवरोध;
	हाल SS_CONNECTING:
		चयन (sk->sk_state) अणु
		हाल CAIF_CONNECTED:
			sock->state = SS_CONNECTED;
			err = -EISCONN;
			जाओ out;
		हाल CAIF_DISCONNECTED:
			/* Reconnect allowed */
			अवरोध;
		हाल CAIF_CONNECTING:
			err = -EALREADY;
			अगर (flags & O_NONBLOCK)
				जाओ out;
			जाओ रुको_connect;
		पूर्ण
		अवरोध;
	हाल SS_CONNECTED:
		caअगर_निश्चित(sk->sk_state == CAIF_CONNECTED ||
				sk->sk_state == CAIF_DISCONNECTED);
		अगर (sk->sk_shutकरोwn & SHUTDOWN_MASK) अणु
			/* Allow re-connect after SHUTDOWN_IND */
			caअगर_disconnect_client(sock_net(sk), &cf_sk->layer);
			caअगर_मुक्त_client(&cf_sk->layer);
			अवरोध;
		पूर्ण
		/* No reconnect on a seqpacket socket */
		err = -EISCONN;
		जाओ out;
	हाल SS_DISCONNECTING:
	हाल SS_FREE:
		caअगर_निश्चित(1); /*Should never happen */
		अवरोध;
	पूर्ण
	sk->sk_state = CAIF_DISCONNECTED;
	sock->state = SS_UNCONNECTED;
	sk_stream_समाप्त_queues(&cf_sk->sk);

	err = -EINVAL;
	अगर (addr_len != माप(काष्ठा sockaddr_caअगर))
		जाओ out;

	स_नकल(&cf_sk->conn_req.sockaddr, uaddr,
		माप(काष्ठा sockaddr_caअगर));

	/* Move to connecting socket, start sending Connect Requests */
	sock->state = SS_CONNECTING;
	sk->sk_state = CAIF_CONNECTING;

	/* Check priority value comming from socket */
	/* अगर priority value is out of range it will be ajusted */
	अगर (cf_sk->sk.sk_priority > CAIF_PRIO_MAX)
		cf_sk->conn_req.priority = CAIF_PRIO_MAX;
	अन्यथा अगर (cf_sk->sk.sk_priority < CAIF_PRIO_MIN)
		cf_sk->conn_req.priority = CAIF_PRIO_MIN;
	अन्यथा
		cf_sk->conn_req.priority = cf_sk->sk.sk_priority;

	/*अगरindex = id of the पूर्णांकerface.*/
	cf_sk->conn_req.अगरindex = cf_sk->sk.sk_bound_dev_अगर;

	cf_sk->layer.receive = caअगर_sktrecv_cb;

	err = caअगर_connect_client(sock_net(sk), &cf_sk->conn_req,
				&cf_sk->layer, &अगरindex, &headroom, &tailroom);

	अगर (err < 0) अणु
		cf_sk->sk.sk_socket->state = SS_UNCONNECTED;
		cf_sk->sk.sk_state = CAIF_DISCONNECTED;
		जाओ out;
	पूर्ण

	err = -ENODEV;
	rcu_पढ़ो_lock();
	dev = dev_get_by_index_rcu(sock_net(sk), अगरindex);
	अगर (!dev) अणु
		rcu_पढ़ो_unlock();
		जाओ out;
	पूर्ण
	cf_sk->headroom = LL_RESERVED_SPACE_EXTRA(dev, headroom);
	mtu = dev->mtu;
	rcu_पढ़ो_unlock();

	cf_sk->tailroom = tailroom;
	cf_sk->maxframe = mtu - (headroom + tailroom);
	अगर (cf_sk->maxframe < 1) अणु
		pr_warn("CAIF Interface MTU too small (%d)\n", dev->mtu);
		err = -ENODEV;
		जाओ out;
	पूर्ण

	err = -EINPROGRESS;
रुको_connect:

	अगर (sk->sk_state != CAIF_CONNECTED && (flags & O_NONBLOCK))
		जाओ out;

	समयo = sock_sndसमयo(sk, flags & O_NONBLOCK);

	release_sock(sk);
	err = -ERESTARTSYS;
	समयo = रुको_event_पूर्णांकerruptible_समयout(*sk_sleep(sk),
			sk->sk_state != CAIF_CONNECTING,
			समयo);
	lock_sock(sk);
	अगर (समयo < 0)
		जाओ out; /* -ERESTARTSYS */

	err = -ETIMEDOUT;
	अगर (समयo == 0 && sk->sk_state != CAIF_CONNECTED)
		जाओ out;
	अगर (sk->sk_state != CAIF_CONNECTED) अणु
		sock->state = SS_UNCONNECTED;
		err = sock_error(sk);
		अगर (!err)
			err = -ECONNREFUSED;
		जाओ out;
	पूर्ण
	sock->state = SS_CONNECTED;
	err = 0;
out:
	release_sock(sk);
	वापस err;
पूर्ण

/*
 * caअगर_release() - Disconnect a CAIF Socket
 * Copied and modअगरied af_irda.c:irda_release().
 */
अटल पूर्णांक caअगर_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);

	अगर (!sk)
		वापस 0;

	set_tx_flow_off(cf_sk);

	/*
	 * Ensure that packets are not queued after this poपूर्णांक in समय.
	 * caअगर_queue_rcv_skb checks SOCK_DEAD holding the queue lock,
	 * this ensures no packets when sock is dead.
	 */
	spin_lock_bh(&sk->sk_receive_queue.lock);
	sock_set_flag(sk, SOCK_DEAD);
	spin_unlock_bh(&sk->sk_receive_queue.lock);
	sock->sk = शून्य;

	WARN_ON(IS_ERR(cf_sk->debugfs_socket_dir));
	debugfs_हटाओ_recursive(cf_sk->debugfs_socket_dir);

	lock_sock(&(cf_sk->sk));
	sk->sk_state = CAIF_DISCONNECTED;
	sk->sk_shutकरोwn = SHUTDOWN_MASK;

	caअगर_disconnect_client(sock_net(sk), &cf_sk->layer);
	cf_sk->sk.sk_socket->state = SS_DISCONNECTING;
	wake_up_पूर्णांकerruptible_poll(sk_sleep(sk), EPOLLERR|EPOLLHUP);

	sock_orphan(sk);
	sk_stream_समाप्त_queues(&cf_sk->sk);
	release_sock(sk);
	sock_put(sk);
	वापस 0;
पूर्ण

/* Copied from af_unix.c:unix_poll(), added CAIF tx_flow handling */
अटल __poll_t caअगर_poll(काष्ठा file *file,
			      काष्ठा socket *sock, poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	__poll_t mask;
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);

	sock_poll_रुको(file, sock, रुको);
	mask = 0;

	/* exceptional events? */
	अगर (sk->sk_err)
		mask |= EPOLLERR;
	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;
	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP;

	/* पढ़ोable? */
	अगर (!skb_queue_empty_lockless(&sk->sk_receive_queue) ||
		(sk->sk_shutकरोwn & RCV_SHUTDOWN))
		mask |= EPOLLIN | EPOLLRDNORM;

	/*
	 * we set writable also when the other side has shut करोwn the
	 * connection. This prevents stuck sockets.
	 */
	अगर (sock_ग_लिखोable(sk) && tx_flow_is_on(cf_sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;

	वापस mask;
पूर्ण

अटल स्थिर काष्ठा proto_ops caअगर_seqpacket_ops = अणु
	.family = PF_CAIF,
	.owner = THIS_MODULE,
	.release = caअगर_release,
	.bind = sock_no_bind,
	.connect = caअगर_connect,
	.socketpair = sock_no_socketpair,
	.accept = sock_no_accept,
	.getname = sock_no_getname,
	.poll = caअगर_poll,
	.ioctl = sock_no_ioctl,
	.listen = sock_no_listen,
	.shutकरोwn = sock_no_shutकरोwn,
	.setsockopt = setsockopt,
	.sendmsg = caअगर_seqpkt_sendmsg,
	.recvmsg = caअगर_seqpkt_recvmsg,
	.mmap = sock_no_mmap,
	.sendpage = sock_no_sendpage,
पूर्ण;

अटल स्थिर काष्ठा proto_ops caअगर_stream_ops = अणु
	.family = PF_CAIF,
	.owner = THIS_MODULE,
	.release = caअगर_release,
	.bind = sock_no_bind,
	.connect = caअगर_connect,
	.socketpair = sock_no_socketpair,
	.accept = sock_no_accept,
	.getname = sock_no_getname,
	.poll = caअगर_poll,
	.ioctl = sock_no_ioctl,
	.listen = sock_no_listen,
	.shutकरोwn = sock_no_shutकरोwn,
	.setsockopt = setsockopt,
	.sendmsg = caअगर_stream_sendmsg,
	.recvmsg = caअगर_stream_recvmsg,
	.mmap = sock_no_mmap,
	.sendpage = sock_no_sendpage,
पूर्ण;

/* This function is called when a socket is finally destroyed. */
अटल व्योम caअगर_sock_deकाष्ठाor(काष्ठा sock *sk)
अणु
	काष्ठा caअगरsock *cf_sk = container_of(sk, काष्ठा caअगरsock, sk);
	caअगर_निश्चित(!refcount_पढ़ो(&sk->sk_wmem_alloc));
	caअगर_निश्चित(sk_unhashed(sk));
	caअगर_निश्चित(!sk->sk_socket);
	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_debug("Attempt to release alive CAIF socket: %p\n", sk);
		वापस;
	पूर्ण
	sk_stream_समाप्त_queues(&cf_sk->sk);
	caअगर_मुक्त_client(&cf_sk->layer);
पूर्ण

अटल पूर्णांक caअगर_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
		       पूर्णांक kern)
अणु
	काष्ठा sock *sk = शून्य;
	काष्ठा caअगरsock *cf_sk = शून्य;
	अटल काष्ठा proto prot = अणु.name = "PF_CAIF",
		.owner = THIS_MODULE,
		.obj_size = माप(काष्ठा caअगरsock),
		.useroffset = दुरत्व(काष्ठा caअगरsock, conn_req.param),
		.usersize = माप_field(काष्ठा caअगरsock, conn_req.param)
	पूर्ण;

	अगर (!capable(CAP_SYS_ADMIN) && !capable(CAP_NET_ADMIN))
		वापस -EPERM;
	/*
	 * The sock->type specअगरies the socket type to use.
	 * The CAIF socket is a packet stream in the sense
	 * that it is packet based. CAIF trusts the reliability
	 * of the link, no resending is implemented.
	 */
	अगर (sock->type == SOCK_SEQPACKET)
		sock->ops = &caअगर_seqpacket_ops;
	अन्यथा अगर (sock->type == SOCK_STREAM)
		sock->ops = &caअगर_stream_ops;
	अन्यथा
		वापस -ESOCKTNOSUPPORT;

	अगर (protocol < 0 || protocol >= CAIFPROTO_MAX)
		वापस -EPROTONOSUPPORT;
	/*
	 * Set the socket state to unconnected.	 The socket state
	 * is really not used at all in the net/core or socket.c but the
	 * initialization makes sure that sock->state is not uninitialized.
	 */
	sk = sk_alloc(net, PF_CAIF, GFP_KERNEL, &prot, kern);
	अगर (!sk)
		वापस -ENOMEM;

	cf_sk = container_of(sk, काष्ठा caअगरsock, sk);

	/* Store the protocol */
	sk->sk_protocol = (अचिन्हित अक्षर) protocol;

	/* Initialize शेष priority क्रम well-known हालs */
	चयन (protocol) अणु
	हाल CAIFPROTO_AT:
		sk->sk_priority = TC_PRIO_CONTROL;
		अवरोध;
	हाल CAIFPROTO_RFM:
		sk->sk_priority = TC_PRIO_INTERACTIVE_BULK;
		अवरोध;
	शेष:
		sk->sk_priority = TC_PRIO_BESTEFFORT;
	पूर्ण

	/*
	 * Lock in order to try to stop someone from खोलोing the socket
	 * too early.
	 */
	lock_sock(&(cf_sk->sk));

	/* Initialize the nozero शेष sock काष्ठाure data. */
	sock_init_data(sock, sk);
	sk->sk_deकाष्ठा = caअगर_sock_deकाष्ठाor;

	mutex_init(&cf_sk->पढ़ोlock); /* single task पढ़ोing lock */
	cf_sk->layer.ctrlcmd = caअगर_ctrl_cb;
	cf_sk->sk.sk_socket->state = SS_UNCONNECTED;
	cf_sk->sk.sk_state = CAIF_DISCONNECTED;

	set_tx_flow_off(cf_sk);
	set_rx_flow_on(cf_sk);

	/* Set शेष options on configuration */
	cf_sk->conn_req.link_selector = CAIF_LINK_LOW_LATENCY;
	cf_sk->conn_req.protocol = protocol;
	release_sock(&cf_sk->sk);
	वापस 0;
पूर्ण


अटल स्थिर काष्ठा net_proto_family caअगर_family_ops = अणु
	.family = PF_CAIF,
	.create = caअगर_create,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init caअगर_sktinit_module(व्योम)
अणु
	वापस sock_रेजिस्टर(&caअगर_family_ops);
पूर्ण

अटल व्योम __निकास caअगर_sktनिकास_module(व्योम)
अणु
	sock_unरेजिस्टर(PF_CAIF);
पूर्ण
module_init(caअगर_sktinit_module);
module_निकास(caअगर_sktनिकास_module);
