<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  IUCV protocol stack क्रम Linux on zSeries
 *
 *  Copyright IBM Corp. 2006, 2009
 *
 *  Author(s):	Jennअगरer Hunt <jenhunt@us.ibm.com>
 *		Hendrik Brueckner <brueckner@linux.vnet.ibm.com>
 *  PM functions:
 *		Ursula Braun <ursula.braun@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "af_iucv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/init.h>
#समावेश <linux/poll.h>
#समावेश <linux/security.h>
#समावेश <net/sock.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/cpcmd.h>
#समावेश <linux/kmod.h>

#समावेश <net/iucv/af_iucv.h>

#घोषणा VERSION "1.2"

अटल अक्षर iucv_userid[80];

अटल काष्ठा proto iucv_proto = अणु
	.name		= "AF_IUCV",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा iucv_sock),
पूर्ण;

अटल काष्ठा iucv_पूर्णांकerface *pr_iucv;

/* special AF_IUCV IPRM messages */
अटल स्थिर u8 iprm_shutकरोwn[8] =
	अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण;

#घोषणा TRGCLS_SIZE	माप_field(काष्ठा iucv_message, class)

#घोषणा __iucv_sock_रुको(sk, condition, समयo, ret)			\
करो अणु									\
	DEFINE_WAIT(__रुको);						\
	दीर्घ __समयo = समयo;						\
	ret = 0;							\
	prepare_to_रुको(sk_sleep(sk), &__रुको, TASK_INTERRUPTIBLE);	\
	जबतक (!(condition)) अणु						\
		अगर (!__समयo) अणु						\
			ret = -EAGAIN;					\
			अवरोध;						\
		पूर्ण							\
		अगर (संकेत_pending(current)) अणु				\
			ret = sock_पूर्णांकr_त्रुटि_सं(__समयo);			\
			अवरोध;						\
		पूर्ण							\
		release_sock(sk);					\
		__समयo = schedule_समयout(__समयo);			\
		lock_sock(sk);						\
		ret = sock_error(sk);					\
		अगर (ret)						\
			अवरोध;						\
	पूर्ण								\
	finish_रुको(sk_sleep(sk), &__रुको);				\
पूर्ण जबतक (0)

#घोषणा iucv_sock_रुको(sk, condition, समयo)				\
(अणु									\
	पूर्णांक __ret = 0;							\
	अगर (!(condition))						\
		__iucv_sock_रुको(sk, condition, समयo, __ret);		\
	__ret;								\
पूर्ण)

अटल काष्ठा sock *iucv_accept_dequeue(काष्ठा sock *parent,
					काष्ठा socket *newsock);
अटल व्योम iucv_sock_समाप्त(काष्ठा sock *sk);
अटल व्योम iucv_sock_बंद(काष्ठा sock *sk);

अटल व्योम afiucv_hs_callback_txnotअगरy(काष्ठा sock *sk, क्रमागत iucv_tx_notअगरy);

/* Call Back functions */
अटल व्योम iucv_callback_rx(काष्ठा iucv_path *, काष्ठा iucv_message *);
अटल व्योम iucv_callback_txकरोne(काष्ठा iucv_path *, काष्ठा iucv_message *);
अटल व्योम iucv_callback_connack(काष्ठा iucv_path *, u8 *);
अटल पूर्णांक iucv_callback_connreq(काष्ठा iucv_path *, u8 *, u8 *);
अटल व्योम iucv_callback_connrej(काष्ठा iucv_path *, u8 *);
अटल व्योम iucv_callback_shutकरोwn(काष्ठा iucv_path *, u8 *);

अटल काष्ठा iucv_sock_list iucv_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(iucv_sk_list.lock),
	.स्वतःbind_name = ATOMIC_INIT(0)
पूर्ण;

अटल काष्ठा iucv_handler af_iucv_handler = अणु
	.path_pending	  = iucv_callback_connreq,
	.path_complete	  = iucv_callback_connack,
	.path_severed	  = iucv_callback_connrej,
	.message_pending  = iucv_callback_rx,
	.message_complete = iucv_callback_txकरोne,
	.path_quiesced	  = iucv_callback_shutकरोwn,
पूर्ण;

अटल अंतरभूत व्योम high_nmcpy(अचिन्हित अक्षर *dst, अक्षर *src)
अणु
       स_नकल(dst, src, 8);
पूर्ण

अटल अंतरभूत व्योम low_nmcpy(अचिन्हित अक्षर *dst, अक्षर *src)
अणु
       स_नकल(&dst[8], src, 8);
पूर्ण

/**
 * iucv_msg_length() - Returns the length of an iucv message.
 * @msg:	Poपूर्णांकer to काष्ठा iucv_message, MUST NOT be शून्य
 *
 * The function वापसs the length of the specअगरied iucv message @msg of data
 * stored in a buffer and of data stored in the parameter list (PRMDATA).
 *
 * For IUCV_IPRMDATA, AF_IUCV uses the following convention to transport socket
 * data:
 *	PRMDATA[0..6]	socket data (max 7 bytes);
 *	PRMDATA[7]	socket data length value (len is 0xff - PRMDATA[7])
 *
 * The socket data length is computed by subtracting the socket data length
 * value from 0xFF.
 * If the socket data len is greater 7, then PRMDATA can be used क्रम special
 * notअगरications (see iucv_sock_shutकरोwn); and further,
 * अगर the socket data len is > 7, the function वापसs 8.
 *
 * Use this function to allocate socket buffers to store iucv message data.
 */
अटल अंतरभूत माप_प्रकार iucv_msg_length(काष्ठा iucv_message *msg)
अणु
	माप_प्रकार datalen;

	अगर (msg->flags & IUCV_IPRMDATA) अणु
		datalen = 0xff - msg->rmmsg[7];
		वापस (datalen < 8) ? datalen : 8;
	पूर्ण
	वापस msg->length;
पूर्ण

/**
 * iucv_sock_in_state() - check क्रम specअगरic states
 * @sk:		sock काष्ठाure
 * @state:	first iucv sk state
 * @state:	second iucv sk state
 *
 * Returns true अगर the socket in either in the first or second state.
 */
अटल पूर्णांक iucv_sock_in_state(काष्ठा sock *sk, पूर्णांक state, पूर्णांक state2)
अणु
	वापस (sk->sk_state == state || sk->sk_state == state2);
पूर्ण

/**
 * iucv_below_msglim() - function to check अगर messages can be sent
 * @sk:		sock काष्ठाure
 *
 * Returns true अगर the send queue length is lower than the message limit.
 * Always वापसs true अगर the socket is not connected (no iucv path क्रम
 * checking the message limit).
 */
अटल अंतरभूत पूर्णांक iucv_below_msglim(काष्ठा sock *sk)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	अगर (sk->sk_state != IUCV_CONNECTED)
		वापस 1;
	अगर (iucv->transport == AF_IUCV_TRANS_IUCV)
		वापस (atomic_पढ़ो(&iucv->skbs_in_xmit) < iucv->path->msglim);
	अन्यथा
		वापस ((atomic_पढ़ो(&iucv->msg_sent) < iucv->msglimit_peer) &&
			(atomic_पढ़ो(&iucv->pendings) <= 0));
पूर्ण

/**
 * iucv_sock_wake_msglim() - Wake up thपढ़ो रुकोing on msg limit
 */
अटल व्योम iucv_sock_wake_msglim(काष्ठा sock *sk)
अणु
	काष्ठा socket_wq *wq;

	rcu_पढ़ो_lock();
	wq = rcu_dereference(sk->sk_wq);
	अगर (skwq_has_sleeper(wq))
		wake_up_पूर्णांकerruptible_all(&wq->रुको);
	sk_wake_async(sk, SOCK_WAKE_SPACE, POLL_OUT);
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * afiucv_hs_send() - send a message through HiperSockets transport
 */
अटल पूर्णांक afiucv_hs_send(काष्ठा iucv_message *imsg, काष्ठा sock *sock,
		   काष्ठा sk_buff *skb, u8 flags)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sock);
	काष्ठा af_iucv_trans_hdr *phs_hdr;
	पूर्णांक err, confirm_recv = 0;

	phs_hdr = skb_push(skb, माप(*phs_hdr));
	स_रखो(phs_hdr, 0, माप(*phs_hdr));
	skb_reset_network_header(skb);

	phs_hdr->magic = ETH_P_AF_IUCV;
	phs_hdr->version = 1;
	phs_hdr->flags = flags;
	अगर (flags == AF_IUCV_FLAG_SYN)
		phs_hdr->winकरोw = iucv->msglimit;
	अन्यथा अगर ((flags == AF_IUCV_FLAG_WIN) || !flags) अणु
		confirm_recv = atomic_पढ़ो(&iucv->msg_recv);
		phs_hdr->winकरोw = confirm_recv;
		अगर (confirm_recv)
			phs_hdr->flags = phs_hdr->flags | AF_IUCV_FLAG_WIN;
	पूर्ण
	स_नकल(phs_hdr->destUserID, iucv->dst_user_id, 8);
	स_नकल(phs_hdr->destAppName, iucv->dst_name, 8);
	स_नकल(phs_hdr->srcUserID, iucv->src_user_id, 8);
	स_नकल(phs_hdr->srcAppName, iucv->src_name, 8);
	ASCEBC(phs_hdr->destUserID, माप(phs_hdr->destUserID));
	ASCEBC(phs_hdr->destAppName, माप(phs_hdr->destAppName));
	ASCEBC(phs_hdr->srcUserID, माप(phs_hdr->srcUserID));
	ASCEBC(phs_hdr->srcAppName, माप(phs_hdr->srcAppName));
	अगर (imsg)
		स_नकल(&phs_hdr->iucv_hdr, imsg, माप(काष्ठा iucv_message));

	skb->dev = iucv->hs_dev;
	अगर (!skb->dev) अणु
		err = -ENODEV;
		जाओ err_मुक्त;
	पूर्ण

	dev_hard_header(skb, skb->dev, ETH_P_AF_IUCV, शून्य, शून्य, skb->len);

	अगर (!(skb->dev->flags & IFF_UP) || !netअगर_carrier_ok(skb->dev)) अणु
		err = -ENETDOWN;
		जाओ err_मुक्त;
	पूर्ण
	अगर (skb->len > skb->dev->mtu) अणु
		अगर (sock->sk_type == SOCK_SEQPACKET) अणु
			err = -EMSGSIZE;
			जाओ err_मुक्त;
		पूर्ण
		err = pskb_trim(skb, skb->dev->mtu);
		अगर (err)
			जाओ err_मुक्त;
	पूर्ण
	skb->protocol = cpu_to_be16(ETH_P_AF_IUCV);

	atomic_inc(&iucv->skbs_in_xmit);
	err = dev_queue_xmit(skb);
	अगर (net_xmit_eval(err)) अणु
		atomic_dec(&iucv->skbs_in_xmit);
	पूर्ण अन्यथा अणु
		atomic_sub(confirm_recv, &iucv->msg_recv);
		WARN_ON(atomic_पढ़ो(&iucv->msg_recv) < 0);
	पूर्ण
	वापस net_xmit_eval(err);

err_मुक्त:
	kमुक्त_skb(skb);
	वापस err;
पूर्ण

अटल काष्ठा sock *__iucv_get_sock_by_name(अक्षर *nm)
अणु
	काष्ठा sock *sk;

	sk_क्रम_each(sk, &iucv_sk_list.head)
		अगर (!स_भेद(&iucv_sk(sk)->src_name, nm, 8))
			वापस sk;

	वापस शून्य;
पूर्ण

अटल व्योम iucv_sock_deकाष्ठा(काष्ठा sock *sk)
अणु
	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_error_queue);

	sk_mem_reclaim(sk);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_err("Attempt to release alive iucv socket %p\n", sk);
		वापस;
	पूर्ण

	WARN_ON(atomic_पढ़ो(&sk->sk_rmem_alloc));
	WARN_ON(refcount_पढ़ो(&sk->sk_wmem_alloc));
	WARN_ON(sk->sk_wmem_queued);
	WARN_ON(sk->sk_क्रमward_alloc);
पूर्ण

/* Cleanup Listen */
अटल व्योम iucv_sock_cleanup_listen(काष्ठा sock *parent)
अणु
	काष्ठा sock *sk;

	/* Close non-accepted connections */
	जबतक ((sk = iucv_accept_dequeue(parent, शून्य))) अणु
		iucv_sock_बंद(sk);
		iucv_sock_समाप्त(sk);
	पूर्ण

	parent->sk_state = IUCV_CLOSED;
पूर्ण

अटल व्योम iucv_sock_link(काष्ठा iucv_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&l->lock);
	sk_add_node(sk, &l->head);
	ग_लिखो_unlock_bh(&l->lock);
पूर्ण

अटल व्योम iucv_sock_unlink(काष्ठा iucv_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&l->lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l->lock);
पूर्ण

/* Kill socket (only अगर zapped and orphaned) */
अटल व्योम iucv_sock_समाप्त(काष्ठा sock *sk)
अणु
	अगर (!sock_flag(sk, SOCK_ZAPPED) || sk->sk_socket)
		वापस;

	iucv_sock_unlink(&iucv_sk_list, sk);
	sock_set_flag(sk, SOCK_DEAD);
	sock_put(sk);
पूर्ण

/* Terminate an IUCV path */
अटल व्योम iucv_sever_path(काष्ठा sock *sk, पूर्णांक with_user_data)
अणु
	अचिन्हित अक्षर user_data[16];
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	काष्ठा iucv_path *path = iucv->path;

	अगर (iucv->path) अणु
		iucv->path = शून्य;
		अगर (with_user_data) अणु
			low_nmcpy(user_data, iucv->src_name);
			high_nmcpy(user_data, iucv->dst_name);
			ASCEBC(user_data, माप(user_data));
			pr_iucv->path_sever(path, user_data);
		पूर्ण अन्यथा
			pr_iucv->path_sever(path, शून्य);
		iucv_path_मुक्त(path);
	पूर्ण
पूर्ण

/* Send controlling flags through an IUCV socket क्रम HIPER transport */
अटल पूर्णांक iucv_send_ctrl(काष्ठा sock *sk, u8 flags)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	पूर्णांक err = 0;
	पूर्णांक blen;
	काष्ठा sk_buff *skb;
	u8 shutकरोwn = 0;

	blen = माप(काष्ठा af_iucv_trans_hdr) +
	       LL_RESERVED_SPACE(iucv->hs_dev);
	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		/* controlling flags should be sent anyway */
		shutकरोwn = sk->sk_shutकरोwn;
		sk->sk_shutकरोwn &= RCV_SHUTDOWN;
	पूर्ण
	skb = sock_alloc_send_skb(sk, blen, 1, &err);
	अगर (skb) अणु
		skb_reserve(skb, blen);
		err = afiucv_hs_send(शून्य, sk, skb, flags);
	पूर्ण
	अगर (shutकरोwn)
		sk->sk_shutकरोwn = shutकरोwn;
	वापस err;
पूर्ण

/* Close an IUCV socket */
अटल व्योम iucv_sock_बंद(काष्ठा sock *sk)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	अचिन्हित दीर्घ समयo;
	पूर्णांक err = 0;

	lock_sock(sk);

	चयन (sk->sk_state) अणु
	हाल IUCV_LISTEN:
		iucv_sock_cleanup_listen(sk);
		अवरोध;

	हाल IUCV_CONNECTED:
		अगर (iucv->transport == AF_IUCV_TRANS_HIPER) अणु
			err = iucv_send_ctrl(sk, AF_IUCV_FLAG_FIN);
			sk->sk_state = IUCV_DISCONN;
			sk->sk_state_change(sk);
		पूर्ण
		fallthrough;

	हाल IUCV_DISCONN:
		sk->sk_state = IUCV_CLOSING;
		sk->sk_state_change(sk);

		अगर (!err && atomic_पढ़ो(&iucv->skbs_in_xmit) > 0) अणु
			अगर (sock_flag(sk, SOCK_LINGER) && sk->sk_lingerसमय)
				समयo = sk->sk_lingerसमय;
			अन्यथा
				समयo = IUCV_DISCONN_TIMEOUT;
			iucv_sock_रुको(sk,
					iucv_sock_in_state(sk, IUCV_CLOSED, 0),
					समयo);
		पूर्ण
		fallthrough;

	हाल IUCV_CLOSING:
		sk->sk_state = IUCV_CLOSED;
		sk->sk_state_change(sk);

		sk->sk_err = ECONNRESET;
		sk->sk_state_change(sk);

		skb_queue_purge(&iucv->send_skb_q);
		skb_queue_purge(&iucv->backlog_skb_q);
		fallthrough;

	शेष:
		iucv_sever_path(sk, 1);
	पूर्ण

	अगर (iucv->hs_dev) अणु
		dev_put(iucv->hs_dev);
		iucv->hs_dev = शून्य;
		sk->sk_bound_dev_अगर = 0;
	पूर्ण

	/* mark socket क्रम deletion by iucv_sock_समाप्त() */
	sock_set_flag(sk, SOCK_ZAPPED);

	release_sock(sk);
पूर्ण

अटल व्योम iucv_sock_init(काष्ठा sock *sk, काष्ठा sock *parent)
अणु
	अगर (parent) अणु
		sk->sk_type = parent->sk_type;
		security_sk_clone(parent, sk);
	पूर्ण
पूर्ण

अटल काष्ठा sock *iucv_sock_alloc(काष्ठा socket *sock, पूर्णांक proto, gfp_t prio, पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	काष्ठा iucv_sock *iucv;

	sk = sk_alloc(&init_net, PF_IUCV, prio, &iucv_proto, kern);
	अगर (!sk)
		वापस शून्य;
	iucv = iucv_sk(sk);

	sock_init_data(sock, sk);
	INIT_LIST_HEAD(&iucv->accept_q);
	spin_lock_init(&iucv->accept_q_lock);
	skb_queue_head_init(&iucv->send_skb_q);
	INIT_LIST_HEAD(&iucv->message_q.list);
	spin_lock_init(&iucv->message_q.lock);
	skb_queue_head_init(&iucv->backlog_skb_q);
	iucv->send_tag = 0;
	atomic_set(&iucv->pendings, 0);
	iucv->flags = 0;
	iucv->msglimit = 0;
	atomic_set(&iucv->skbs_in_xmit, 0);
	atomic_set(&iucv->msg_sent, 0);
	atomic_set(&iucv->msg_recv, 0);
	iucv->path = शून्य;
	iucv->sk_txnotअगरy = afiucv_hs_callback_txnotअगरy;
	स_रखो(&iucv->src_user_id , 0, 32);
	अगर (pr_iucv)
		iucv->transport = AF_IUCV_TRANS_IUCV;
	अन्यथा
		iucv->transport = AF_IUCV_TRANS_HIPER;

	sk->sk_deकाष्ठा = iucv_sock_deकाष्ठा;
	sk->sk_sndसमयo = IUCV_CONN_TIMEOUT;

	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = proto;
	sk->sk_state	= IUCV_OPEN;

	iucv_sock_link(&iucv_sk_list, sk);
	वापस sk;
पूर्ण

अटल व्योम iucv_accept_enqueue(काष्ठा sock *parent, काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iucv_sock *par = iucv_sk(parent);

	sock_hold(sk);
	spin_lock_irqsave(&par->accept_q_lock, flags);
	list_add_tail(&iucv_sk(sk)->accept_q, &par->accept_q);
	spin_unlock_irqrestore(&par->accept_q_lock, flags);
	iucv_sk(sk)->parent = parent;
	sk_acceptq_added(parent);
पूर्ण

अटल व्योम iucv_accept_unlink(काष्ठा sock *sk)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा iucv_sock *par = iucv_sk(iucv_sk(sk)->parent);

	spin_lock_irqsave(&par->accept_q_lock, flags);
	list_del_init(&iucv_sk(sk)->accept_q);
	spin_unlock_irqrestore(&par->accept_q_lock, flags);
	sk_acceptq_हटाओd(iucv_sk(sk)->parent);
	iucv_sk(sk)->parent = शून्य;
	sock_put(sk);
पूर्ण

अटल काष्ठा sock *iucv_accept_dequeue(काष्ठा sock *parent,
					काष्ठा socket *newsock)
अणु
	काष्ठा iucv_sock *isk, *n;
	काष्ठा sock *sk;

	list_क्रम_each_entry_safe(isk, n, &iucv_sk(parent)->accept_q, accept_q) अणु
		sk = (काष्ठा sock *) isk;
		lock_sock(sk);

		अगर (sk->sk_state == IUCV_CLOSED) अणु
			iucv_accept_unlink(sk);
			release_sock(sk);
			जारी;
		पूर्ण

		अगर (sk->sk_state == IUCV_CONNECTED ||
		    sk->sk_state == IUCV_DISCONN ||
		    !newsock) अणु
			iucv_accept_unlink(sk);
			अगर (newsock)
				sock_graft(sk, newsock);

			release_sock(sk);
			वापस sk;
		पूर्ण

		release_sock(sk);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम __iucv_स्वतः_name(काष्ठा iucv_sock *iucv)
अणु
	अक्षर name[12];

	प्र_लिखो(name, "%08x", atomic_inc_वापस(&iucv_sk_list.स्वतःbind_name));
	जबतक (__iucv_get_sock_by_name(name)) अणु
		प्र_लिखो(name, "%08x",
			atomic_inc_वापस(&iucv_sk_list.स्वतःbind_name));
	पूर्ण
	स_नकल(iucv->src_name, name, 8);
पूर्ण

/* Bind an unbound socket */
अटल पूर्णांक iucv_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			  पूर्णांक addr_len)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_iucv *, sa, addr);
	अक्षर uid[माप(sa->siucv_user_id)];
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv;
	पूर्णांक err = 0;
	काष्ठा net_device *dev;

	/* Verअगरy the input sockaddr */
	अगर (addr_len < माप(काष्ठा sockaddr_iucv) ||
	    addr->sa_family != AF_IUCV)
		वापस -EINVAL;

	lock_sock(sk);
	अगर (sk->sk_state != IUCV_OPEN) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	ग_लिखो_lock_bh(&iucv_sk_list.lock);

	iucv = iucv_sk(sk);
	अगर (__iucv_get_sock_by_name(sa->siucv_name)) अणु
		err = -EADDRINUSE;
		जाओ करोne_unlock;
	पूर्ण
	अगर (iucv->path)
		जाओ करोne_unlock;

	/* Bind the socket */
	अगर (pr_iucv)
		अगर (!स_भेद(sa->siucv_user_id, iucv_userid, 8))
			जाओ vm_bind; /* VM IUCV transport */

	/* try hiper transport */
	स_नकल(uid, sa->siucv_user_id, माप(uid));
	ASCEBC(uid, 8);
	rcu_पढ़ो_lock();
	क्रम_each_netdev_rcu(&init_net, dev) अणु
		अगर (!स_भेद(dev->perm_addr, uid, 8)) अणु
			स_नकल(iucv->src_user_id, sa->siucv_user_id, 8);
			/* Check क्रम uninitialized siucv_name */
			अगर (म_भेदन(sa->siucv_name, "        ", 8) == 0)
				__iucv_स्वतः_name(iucv);
			अन्यथा
				स_नकल(iucv->src_name, sa->siucv_name, 8);
			sk->sk_bound_dev_अगर = dev->अगरindex;
			iucv->hs_dev = dev;
			dev_hold(dev);
			sk->sk_state = IUCV_BOUND;
			iucv->transport = AF_IUCV_TRANS_HIPER;
			अगर (!iucv->msglimit)
				iucv->msglimit = IUCV_HIPER_MSGLIM_DEFAULT;
			rcu_पढ़ो_unlock();
			जाओ करोne_unlock;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
vm_bind:
	अगर (pr_iucv) अणु
		/* use local userid क्रम backward compat */
		स_नकल(iucv->src_name, sa->siucv_name, 8);
		स_नकल(iucv->src_user_id, iucv_userid, 8);
		sk->sk_state = IUCV_BOUND;
		iucv->transport = AF_IUCV_TRANS_IUCV;
		sk->sk_allocation |= GFP_DMA;
		अगर (!iucv->msglimit)
			iucv->msglimit = IUCV_QUEUELEN_DEFAULT;
		जाओ करोne_unlock;
	पूर्ण
	/* found no dev to bind */
	err = -ENODEV;
करोne_unlock:
	/* Release the socket list lock */
	ग_लिखो_unlock_bh(&iucv_sk_list.lock);
करोne:
	release_sock(sk);
	वापस err;
पूर्ण

/* Automatically bind an unbound socket */
अटल पूर्णांक iucv_sock_स्वतःbind(काष्ठा sock *sk)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	पूर्णांक err = 0;

	अगर (unlikely(!pr_iucv))
		वापस -EPROTO;

	स_नकल(iucv->src_user_id, iucv_userid, 8);
	iucv->transport = AF_IUCV_TRANS_IUCV;
	sk->sk_allocation |= GFP_DMA;

	ग_लिखो_lock_bh(&iucv_sk_list.lock);
	__iucv_स्वतः_name(iucv);
	ग_लिखो_unlock_bh(&iucv_sk_list.lock);

	अगर (!iucv->msglimit)
		iucv->msglimit = IUCV_QUEUELEN_DEFAULT;

	वापस err;
पूर्ण

अटल पूर्णांक afiucv_path_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_iucv *, sa, addr);
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	अचिन्हित अक्षर user_data[16];
	पूर्णांक err;

	high_nmcpy(user_data, sa->siucv_name);
	low_nmcpy(user_data, iucv->src_name);
	ASCEBC(user_data, माप(user_data));

	/* Create path. */
	iucv->path = iucv_path_alloc(iucv->msglimit,
				     IUCV_IPRMDATA, GFP_KERNEL);
	अगर (!iucv->path) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण
	err = pr_iucv->path_connect(iucv->path, &af_iucv_handler,
				    sa->siucv_user_id, शून्य, user_data,
				    sk);
	अगर (err) अणु
		iucv_path_मुक्त(iucv->path);
		iucv->path = शून्य;
		चयन (err) अणु
		हाल 0x0b:	/* Target communicator is not logged on */
			err = -ENETUNREACH;
			अवरोध;
		हाल 0x0d:	/* Max connections क्रम this guest exceeded */
		हाल 0x0e:	/* Max connections क्रम target guest exceeded */
			err = -EAGAIN;
			अवरोध;
		हाल 0x0f:	/* Missing IUCV authorization */
			err = -EACCES;
			अवरोध;
		शेष:
			err = -ECONNREFUSED;
			अवरोध;
		पूर्ण
	पूर्ण
करोne:
	वापस err;
पूर्ण

/* Connect an unconnected socket */
अटल पूर्णांक iucv_sock_connect(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			     पूर्णांक alen, पूर्णांक flags)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_iucv *, sa, addr);
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	पूर्णांक err;

	अगर (alen < माप(काष्ठा sockaddr_iucv) || addr->sa_family != AF_IUCV)
		वापस -EINVAL;

	अगर (sk->sk_state != IUCV_OPEN && sk->sk_state != IUCV_BOUND)
		वापस -EBADFD;

	अगर (sk->sk_state == IUCV_OPEN &&
	    iucv->transport == AF_IUCV_TRANS_HIPER)
		वापस -EBADFD; /* explicit bind required */

	अगर (sk->sk_type != SOCK_STREAM && sk->sk_type != SOCK_SEQPACKET)
		वापस -EINVAL;

	अगर (sk->sk_state == IUCV_OPEN) अणु
		err = iucv_sock_स्वतःbind(sk);
		अगर (unlikely(err))
			वापस err;
	पूर्ण

	lock_sock(sk);

	/* Set the destination inक्रमmation */
	स_नकल(iucv->dst_user_id, sa->siucv_user_id, 8);
	स_नकल(iucv->dst_name, sa->siucv_name, 8);

	अगर (iucv->transport == AF_IUCV_TRANS_HIPER)
		err = iucv_send_ctrl(sock->sk, AF_IUCV_FLAG_SYN);
	अन्यथा
		err = afiucv_path_connect(sock, addr);
	अगर (err)
		जाओ करोne;

	अगर (sk->sk_state != IUCV_CONNECTED)
		err = iucv_sock_रुको(sk, iucv_sock_in_state(sk, IUCV_CONNECTED,
							    IUCV_DISCONN),
				     sock_sndसमयo(sk, flags & O_NONBLOCK));

	अगर (sk->sk_state == IUCV_DISCONN || sk->sk_state == IUCV_CLOSED)
		err = -ECONNREFUSED;

	अगर (err && iucv->transport == AF_IUCV_TRANS_IUCV)
		iucv_sever_path(sk, 0);

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

/* Move a socket पूर्णांकo listening state. */
अटल पूर्णांक iucv_sock_listen(काष्ठा socket *sock, पूर्णांक backlog)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err;

	lock_sock(sk);

	err = -EINVAL;
	अगर (sk->sk_state != IUCV_BOUND)
		जाओ करोne;

	अगर (sock->type != SOCK_STREAM && sock->type != SOCK_SEQPACKET)
		जाओ करोne;

	sk->sk_max_ack_backlog = backlog;
	sk->sk_ack_backlog = 0;
	sk->sk_state = IUCV_LISTEN;
	err = 0;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

/* Accept a pending connection */
अटल पूर्णांक iucv_sock_accept(काष्ठा socket *sock, काष्ठा socket *newsock,
			    पूर्णांक flags, bool kern)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा sock *sk = sock->sk, *nsk;
	दीर्घ समयo;
	पूर्णांक err = 0;

	lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

	अगर (sk->sk_state != IUCV_LISTEN) अणु
		err = -EBADFD;
		जाओ करोne;
	पूर्ण

	समयo = sock_rcvसमयo(sk, flags & O_NONBLOCK);

	/* Wait क्रम an incoming connection */
	add_रुको_queue_exclusive(sk_sleep(sk), &रुको);
	जबतक (!(nsk = iucv_accept_dequeue(sk, newsock))) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (!समयo) अणु
			err = -EAGAIN;
			अवरोध;
		पूर्ण

		release_sock(sk);
		समयo = schedule_समयout(समयo);
		lock_sock_nested(sk, SINGLE_DEPTH_NESTING);

		अगर (sk->sk_state != IUCV_LISTEN) अणु
			err = -EBADFD;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			err = sock_पूर्णांकr_त्रुटि_सं(समयo);
			अवरोध;
		पूर्ण
	पूर्ण

	set_current_state(TASK_RUNNING);
	हटाओ_रुको_queue(sk_sleep(sk), &रुको);

	अगर (err)
		जाओ करोne;

	newsock->state = SS_CONNECTED;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक iucv_sock_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
			     पूर्णांक peer)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_iucv *, siucv, addr);
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	addr->sa_family = AF_IUCV;

	अगर (peer) अणु
		स_नकल(siucv->siucv_user_id, iucv->dst_user_id, 8);
		स_नकल(siucv->siucv_name, iucv->dst_name, 8);
	पूर्ण अन्यथा अणु
		स_नकल(siucv->siucv_user_id, iucv->src_user_id, 8);
		स_नकल(siucv->siucv_name, iucv->src_name, 8);
	पूर्ण
	स_रखो(&siucv->siucv_port, 0, माप(siucv->siucv_port));
	स_रखो(&siucv->siucv_addr, 0, माप(siucv->siucv_addr));
	स_रखो(&siucv->siucv_nodeid, 0, माप(siucv->siucv_nodeid));

	वापस माप(काष्ठा sockaddr_iucv);
पूर्ण

/**
 * iucv_send_iprm() - Send socket data in parameter list of an iucv message.
 * @path:	IUCV path
 * @msg:	Poपूर्णांकer to a काष्ठा iucv_message
 * @skb:	The socket data to send, skb->len MUST BE <= 7
 *
 * Send the socket data in the parameter list in the iucv message
 * (IUCV_IPRMDATA). The socket data is stored at index 0 to 6 in the parameter
 * list and the socket data len at index 7 (last byte).
 * See also iucv_msg_length().
 *
 * Returns the error code from the iucv_message_send() call.
 */
अटल पूर्णांक iucv_send_iprm(काष्ठा iucv_path *path, काष्ठा iucv_message *msg,
			  काष्ठा sk_buff *skb)
अणु
	u8 prmdata[8];

	स_नकल(prmdata, (व्योम *) skb->data, skb->len);
	prmdata[7] = 0xff - (u8) skb->len;
	वापस pr_iucv->message_send(path, msg, IUCV_IPRMDATA, 0,
				 (व्योम *) prmdata, 8);
पूर्ण

अटल पूर्णांक iucv_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			     माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	माप_प्रकार headroom = 0;
	माप_प्रकार linear;
	काष्ठा sk_buff *skb;
	काष्ठा iucv_message txmsg = अणु0पूर्ण;
	काष्ठा cmsghdr *cmsg;
	पूर्णांक cmsg_करोne;
	दीर्घ समयo;
	अक्षर user_id[9];
	अक्षर appl_id[9];
	पूर्णांक err;
	पूर्णांक noblock = msg->msg_flags & MSG_DONTWAIT;

	err = sock_error(sk);
	अगर (err)
		वापस err;

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	/* SOCK_SEQPACKET: we करो not support segmented records */
	अगर (sk->sk_type == SOCK_SEQPACKET && !(msg->msg_flags & MSG_EOR))
		वापस -EOPNOTSUPP;

	lock_sock(sk);

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		err = -EPIPE;
		जाओ out;
	पूर्ण

	/* Return अगर the socket is not in connected state */
	अगर (sk->sk_state != IUCV_CONNECTED) अणु
		err = -ENOTCONN;
		जाओ out;
	पूर्ण

	/* initialize शेषs */
	cmsg_करोne   = 0;	/* check क्रम duplicate headers */

	/* iterate over control messages */
	क्रम_each_cmsghdr(cmsg, msg) अणु
		अगर (!CMSG_OK(msg, cmsg)) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (cmsg->cmsg_level != SOL_IUCV)
			जारी;

		अगर (cmsg->cmsg_type & cmsg_करोne) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		cmsg_करोne |= cmsg->cmsg_type;

		चयन (cmsg->cmsg_type) अणु
		हाल SCM_IUCV_TRGCLS:
			अगर (cmsg->cmsg_len != CMSG_LEN(TRGCLS_SIZE)) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			/* set iucv message target class */
			स_नकल(&txmsg.class,
				(व्योम *) CMSG_DATA(cmsg), TRGCLS_SIZE);

			अवरोध;

		शेष:
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* allocate one skb क्रम each iucv message:
	 * this is fine क्रम SOCK_SEQPACKET (unless we want to support
	 * segmented records using the MSG_EOR flag), but
	 * क्रम SOCK_STREAM we might want to improve it in future */
	अगर (iucv->transport == AF_IUCV_TRANS_HIPER) अणु
		headroom = माप(काष्ठा af_iucv_trans_hdr) +
			   LL_RESERVED_SPACE(iucv->hs_dev);
		linear = min(len, PAGE_SIZE - headroom);
	पूर्ण अन्यथा अणु
		अगर (len < PAGE_SIZE) अणु
			linear = len;
		पूर्ण अन्यथा अणु
			/* In nonlinear "classic" iucv skb,
			 * reserve space क्रम iucv_array
			 */
			headroom = माप(काष्ठा iucv_array) *
				   (MAX_SKB_FRAGS + 1);
			linear = PAGE_SIZE - headroom;
		पूर्ण
	पूर्ण
	skb = sock_alloc_send_pskb(sk, headroom + linear, len - linear,
				   noblock, &err, 0);
	अगर (!skb)
		जाओ out;
	अगर (headroom)
		skb_reserve(skb, headroom);
	skb_put(skb, linear);
	skb->len = len;
	skb->data_len = len - linear;
	err = skb_copy_datagram_from_iter(skb, 0, &msg->msg_iter, len);
	अगर (err)
		जाओ fail;

	/* रुको अगर outstanding messages क्रम iucv path has reached */
	समयo = sock_sndसमयo(sk, noblock);
	err = iucv_sock_रुको(sk, iucv_below_msglim(sk), समयo);
	अगर (err)
		जाओ fail;

	/* वापस -ECONNRESET अगर the socket is no दीर्घer connected */
	अगर (sk->sk_state != IUCV_CONNECTED) अणु
		err = -ECONNRESET;
		जाओ fail;
	पूर्ण

	/* increment and save iucv message tag क्रम msg_completion cbk */
	txmsg.tag = iucv->send_tag++;
	IUCV_SKB_CB(skb)->tag = txmsg.tag;

	अगर (iucv->transport == AF_IUCV_TRANS_HIPER) अणु
		atomic_inc(&iucv->msg_sent);
		err = afiucv_hs_send(&txmsg, sk, skb, 0);
		अगर (err) अणु
			atomic_dec(&iucv->msg_sent);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु /* Classic VM IUCV transport */
		skb_queue_tail(&iucv->send_skb_q, skb);
		atomic_inc(&iucv->skbs_in_xmit);

		अगर (((iucv->path->flags & IUCV_IPRMDATA) & iucv->flags) &&
		    skb->len <= 7) अणु
			err = iucv_send_iprm(iucv->path, &txmsg, skb);

			/* on success: there is no message_complete callback */
			/* क्रम an IPRMDATA msg; हटाओ skb from send queue   */
			अगर (err == 0) अणु
				atomic_dec(&iucv->skbs_in_xmit);
				skb_unlink(skb, &iucv->send_skb_q);
				kमुक्त_skb(skb);
			पूर्ण

			/* this error should never happen since the	*/
			/* IUCV_IPRMDATA path flag is set... sever path */
			अगर (err == 0x15) अणु
				pr_iucv->path_sever(iucv->path, शून्य);
				atomic_dec(&iucv->skbs_in_xmit);
				skb_unlink(skb, &iucv->send_skb_q);
				err = -EPIPE;
				जाओ fail;
			पूर्ण
		पूर्ण अन्यथा अगर (skb_is_nonlinear(skb)) अणु
			काष्ठा iucv_array *iba = (काष्ठा iucv_array *)skb->head;
			पूर्णांक i;

			/* skip iucv_array lying in the headroom */
			iba[0].address = (u32)(addr_t)skb->data;
			iba[0].length = (u32)skb_headlen(skb);
			क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
				skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

				iba[i + 1].address =
					(u32)(addr_t)skb_frag_address(frag);
				iba[i + 1].length = (u32)skb_frag_size(frag);
			पूर्ण
			err = pr_iucv->message_send(iucv->path, &txmsg,
						    IUCV_IPBUFLST, 0,
						    (व्योम *)iba, skb->len);
		पूर्ण अन्यथा अणु /* non-IPRM Linear skb */
			err = pr_iucv->message_send(iucv->path, &txmsg,
					0, 0, (व्योम *)skb->data, skb->len);
		पूर्ण
		अगर (err) अणु
			अगर (err == 3) अणु
				user_id[8] = 0;
				स_नकल(user_id, iucv->dst_user_id, 8);
				appl_id[8] = 0;
				स_नकल(appl_id, iucv->dst_name, 8);
				pr_err(
		"Application %s on z/VM guest %s exceeds message limit\n",
					appl_id, user_id);
				err = -EAGAIN;
			पूर्ण अन्यथा अणु
				err = -EPIPE;
			पूर्ण

			atomic_dec(&iucv->skbs_in_xmit);
			skb_unlink(skb, &iucv->send_skb_q);
			जाओ fail;
		पूर्ण
	पूर्ण

	release_sock(sk);
	वापस len;

fail:
	kमुक्त_skb(skb);
out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल काष्ठा sk_buff *alloc_iucv_recv_skb(अचिन्हित दीर्घ len)
अणु
	माप_प्रकार headroom, linear;
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (len < PAGE_SIZE) अणु
		headroom = 0;
		linear = len;
	पूर्ण अन्यथा अणु
		headroom = माप(काष्ठा iucv_array) * (MAX_SKB_FRAGS + 1);
		linear = PAGE_SIZE - headroom;
	पूर्ण
	skb = alloc_skb_with_frags(headroom + linear, len - linear,
				   0, &err, GFP_ATOMIC | GFP_DMA);
	WARN_ONCE(!skb,
		  "alloc of recv iucv skb len=%lu failed with errcode=%d\n",
		  len, err);
	अगर (skb) अणु
		अगर (headroom)
			skb_reserve(skb, headroom);
		skb_put(skb, linear);
		skb->len = len;
		skb->data_len = len - linear;
	पूर्ण
	वापस skb;
पूर्ण

/* iucv_process_message() - Receive a single outstanding IUCV message
 *
 * Locking: must be called with message_q.lock held
 */
अटल व्योम iucv_process_message(काष्ठा sock *sk, काष्ठा sk_buff *skb,
				 काष्ठा iucv_path *path,
				 काष्ठा iucv_message *msg)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक len;

	len = iucv_msg_length(msg);

	/* store msg target class in the second 4 bytes of skb ctrl buffer */
	/* Note: the first 4 bytes are reserved क्रम msg tag */
	IUCV_SKB_CB(skb)->class = msg->class;

	/* check क्रम special IPRM messages (e.g. iucv_sock_shutकरोwn) */
	अगर ((msg->flags & IUCV_IPRMDATA) && len > 7) अणु
		अगर (स_भेद(msg->rmmsg, iprm_shutकरोwn, 8) == 0) अणु
			skb->data = शून्य;
			skb->len = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (skb_is_nonlinear(skb)) अणु
			काष्ठा iucv_array *iba = (काष्ठा iucv_array *)skb->head;
			पूर्णांक i;

			iba[0].address = (u32)(addr_t)skb->data;
			iba[0].length = (u32)skb_headlen(skb);
			क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
				skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

				iba[i + 1].address =
					(u32)(addr_t)skb_frag_address(frag);
				iba[i + 1].length = (u32)skb_frag_size(frag);
			पूर्ण
			rc = pr_iucv->message_receive(path, msg,
					      IUCV_IPBUFLST,
					      (व्योम *)iba, len, शून्य);
		पूर्ण अन्यथा अणु
			rc = pr_iucv->message_receive(path, msg,
					      msg->flags & IUCV_IPRMDATA,
					      skb->data, len, शून्य);
		पूर्ण
		अगर (rc) अणु
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
		WARN_ON_ONCE(skb->len != len);
	पूर्ण

	IUCV_SKB_CB(skb)->offset = 0;
	अगर (sk_filter(sk, skb)) अणु
		atomic_inc(&sk->sk_drops);	/* skb rejected by filter */
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	अगर (__sock_queue_rcv_skb(sk, skb))	/* handle rcv queue full */
		skb_queue_tail(&iucv_sk(sk)->backlog_skb_q, skb);
पूर्ण

/* iucv_process_message_q() - Process outstanding IUCV messages
 *
 * Locking: must be called with message_q.lock held
 */
अटल व्योम iucv_process_message_q(काष्ठा sock *sk)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा sock_msg_q *p, *n;

	list_क्रम_each_entry_safe(p, n, &iucv->message_q.list, list) अणु
		skb = alloc_iucv_recv_skb(iucv_msg_length(&p->msg));
		अगर (!skb)
			अवरोध;
		iucv_process_message(sk, skb, p->path, &p->msg);
		list_del(&p->list);
		kमुक्त(p);
		अगर (!skb_queue_empty(&iucv->backlog_skb_q))
			अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक iucv_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
			     माप_प्रकार len, पूर्णांक flags)
अणु
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	अचिन्हित पूर्णांक copied, rlen;
	काष्ठा sk_buff *skb, *rskb, *cskb;
	पूर्णांक err = 0;
	u32 offset;

	अगर ((sk->sk_state == IUCV_DISCONN) &&
	    skb_queue_empty(&iucv->backlog_skb_q) &&
	    skb_queue_empty(&sk->sk_receive_queue) &&
	    list_empty(&iucv->message_q.list))
		वापस 0;

	अगर (flags & (MSG_OOB))
		वापस -EOPNOTSUPP;

	/* receive/dequeue next skb:
	 * the function understands MSG_PEEK and, thus, करोes not dequeue skb */
	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb) अणु
		अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
			वापस 0;
		वापस err;
	पूर्ण

	offset = IUCV_SKB_CB(skb)->offset;
	rlen   = skb->len - offset;		/* real length of skb */
	copied = min_t(अचिन्हित पूर्णांक, rlen, len);
	अगर (!rlen)
		sk->sk_shutकरोwn = sk->sk_shutकरोwn | RCV_SHUTDOWN;

	cskb = skb;
	अगर (skb_copy_datagram_msg(cskb, offset, msg, copied)) अणु
		अगर (!(flags & MSG_PEEK))
			skb_queue_head(&sk->sk_receive_queue, skb);
		वापस -EFAULT;
	पूर्ण

	/* SOCK_SEQPACKET: set MSG_TRUNC अगर recv buf size is too small */
	अगर (sk->sk_type == SOCK_SEQPACKET) अणु
		अगर (copied < rlen)
			msg->msg_flags |= MSG_TRUNC;
		/* each iucv message contains a complete record */
		msg->msg_flags |= MSG_EOR;
	पूर्ण

	/* create control message to store iucv msg target class:
	 * get the trgcls from the control buffer of the skb due to
	 * fragmentation of original iucv message. */
	err = put_cmsg(msg, SOL_IUCV, SCM_IUCV_TRGCLS,
		       माप(IUCV_SKB_CB(skb)->class),
		       (व्योम *)&IUCV_SKB_CB(skb)->class);
	अगर (err) अणु
		अगर (!(flags & MSG_PEEK))
			skb_queue_head(&sk->sk_receive_queue, skb);
		वापस err;
	पूर्ण

	/* Mark पढ़ो part of skb as used */
	अगर (!(flags & MSG_PEEK)) अणु

		/* SOCK_STREAM: re-queue skb अगर it contains unreceived data */
		अगर (sk->sk_type == SOCK_STREAM) अणु
			अगर (copied < rlen) अणु
				IUCV_SKB_CB(skb)->offset = offset + copied;
				skb_queue_head(&sk->sk_receive_queue, skb);
				जाओ करोne;
			पूर्ण
		पूर्ण

		kमुक्त_skb(skb);
		अगर (iucv->transport == AF_IUCV_TRANS_HIPER) अणु
			atomic_inc(&iucv->msg_recv);
			अगर (atomic_पढ़ो(&iucv->msg_recv) > iucv->msglimit) अणु
				WARN_ON(1);
				iucv_sock_बंद(sk);
				वापस -EFAULT;
			पूर्ण
		पूर्ण

		/* Queue backlog skbs */
		spin_lock_bh(&iucv->message_q.lock);
		rskb = skb_dequeue(&iucv->backlog_skb_q);
		जबतक (rskb) अणु
			IUCV_SKB_CB(rskb)->offset = 0;
			अगर (__sock_queue_rcv_skb(sk, rskb)) अणु
				/* handle rcv queue full */
				skb_queue_head(&iucv->backlog_skb_q,
						rskb);
				अवरोध;
			पूर्ण
			rskb = skb_dequeue(&iucv->backlog_skb_q);
		पूर्ण
		अगर (skb_queue_empty(&iucv->backlog_skb_q)) अणु
			अगर (!list_empty(&iucv->message_q.list))
				iucv_process_message_q(sk);
			अगर (atomic_पढ़ो(&iucv->msg_recv) >=
							iucv->msglimit / 2) अणु
				err = iucv_send_ctrl(sk, AF_IUCV_FLAG_WIN);
				अगर (err) अणु
					sk->sk_state = IUCV_DISCONN;
					sk->sk_state_change(sk);
				पूर्ण
			पूर्ण
		पूर्ण
		spin_unlock_bh(&iucv->message_q.lock);
	पूर्ण

करोne:
	/* SOCK_SEQPACKET: वापस real length अगर MSG_TRUNC is set */
	अगर (sk->sk_type == SOCK_SEQPACKET && (flags & MSG_TRUNC))
		copied = rlen;

	वापस copied;
पूर्ण

अटल अंतरभूत __poll_t iucv_accept_poll(काष्ठा sock *parent)
अणु
	काष्ठा iucv_sock *isk, *n;
	काष्ठा sock *sk;

	list_क्रम_each_entry_safe(isk, n, &iucv_sk(parent)->accept_q, accept_q) अणु
		sk = (काष्ठा sock *) isk;

		अगर (sk->sk_state == IUCV_CONNECTED)
			वापस EPOLLIN | EPOLLRDNORM;
	पूर्ण

	वापस 0;
पूर्ण

अटल __poll_t iucv_sock_poll(काष्ठा file *file, काष्ठा socket *sock,
			       poll_table *रुको)
अणु
	काष्ठा sock *sk = sock->sk;
	__poll_t mask = 0;

	sock_poll_रुको(file, sock, रुको);

	अगर (sk->sk_state == IUCV_LISTEN)
		वापस iucv_accept_poll(sk);

	अगर (sk->sk_err || !skb_queue_empty(&sk->sk_error_queue))
		mask |= EPOLLERR |
			(sock_flag(sk, SOCK_SELECT_ERR_QUEUE) ? EPOLLPRI : 0);

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN)
		mask |= EPOLLRDHUP;

	अगर (sk->sk_shutकरोwn == SHUTDOWN_MASK)
		mask |= EPOLLHUP;

	अगर (!skb_queue_empty(&sk->sk_receive_queue) ||
	    (sk->sk_shutकरोwn & RCV_SHUTDOWN))
		mask |= EPOLLIN | EPOLLRDNORM;

	अगर (sk->sk_state == IUCV_CLOSED)
		mask |= EPOLLHUP;

	अगर (sk->sk_state == IUCV_DISCONN)
		mask |= EPOLLIN;

	अगर (sock_ग_लिखोable(sk) && iucv_below_msglim(sk))
		mask |= EPOLLOUT | EPOLLWRNORM | EPOLLWRBAND;
	अन्यथा
		sk_set_bit(SOCKWQ_ASYNC_NOSPACE, sk);

	वापस mask;
पूर्ण

अटल पूर्णांक iucv_sock_shutकरोwn(काष्ठा socket *sock, पूर्णांक how)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	काष्ठा iucv_message txmsg;
	पूर्णांक err = 0;

	how++;

	अगर ((how & ~SHUTDOWN_MASK) || !how)
		वापस -EINVAL;

	lock_sock(sk);
	चयन (sk->sk_state) अणु
	हाल IUCV_LISTEN:
	हाल IUCV_DISCONN:
	हाल IUCV_CLOSING:
	हाल IUCV_CLOSED:
		err = -ENOTCONN;
		जाओ fail;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((how == SEND_SHUTDOWN || how == SHUTDOWN_MASK) &&
	    sk->sk_state == IUCV_CONNECTED) अणु
		अगर (iucv->transport == AF_IUCV_TRANS_IUCV) अणु
			txmsg.class = 0;
			txmsg.tag = 0;
			err = pr_iucv->message_send(iucv->path, &txmsg,
				IUCV_IPRMDATA, 0, (व्योम *) iprm_shutकरोwn, 8);
			अगर (err) अणु
				चयन (err) अणु
				हाल 1:
					err = -ENOTCONN;
					अवरोध;
				हाल 2:
					err = -ECONNRESET;
					अवरोध;
				शेष:
					err = -ENOTCONN;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			iucv_send_ctrl(sk, AF_IUCV_FLAG_SHT);
	पूर्ण

	sk->sk_shutकरोwn |= how;
	अगर (how == RCV_SHUTDOWN || how == SHUTDOWN_MASK) अणु
		अगर ((iucv->transport == AF_IUCV_TRANS_IUCV) &&
		    iucv->path) अणु
			err = pr_iucv->path_quiesce(iucv->path, शून्य);
			अगर (err)
				err = -ENOTCONN;
/*			skb_queue_purge(&sk->sk_receive_queue); */
		पूर्ण
		skb_queue_purge(&sk->sk_receive_queue);
	पूर्ण

	/* Wake up anyone sleeping in poll */
	sk->sk_state_change(sk);

fail:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक iucv_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	अगर (!sk)
		वापस 0;

	iucv_sock_बंद(sk);

	sock_orphan(sk);
	iucv_sock_समाप्त(sk);
	वापस err;
पूर्ण

/* माला_लोockopt and setsockopt */
अटल पूर्णांक iucv_sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
				sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	पूर्णांक val;
	पूर्णांक rc;

	अगर (level != SOL_IUCV)
		वापस -ENOPROTOOPT;

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	rc = 0;

	lock_sock(sk);
	चयन (optname) अणु
	हाल SO_IPRMDATA_MSG:
		अगर (val)
			iucv->flags |= IUCV_IPRMDATA;
		अन्यथा
			iucv->flags &= ~IUCV_IPRMDATA;
		अवरोध;
	हाल SO_MSGLIMIT:
		चयन (sk->sk_state) अणु
		हाल IUCV_OPEN:
		हाल IUCV_BOUND:
			अगर (val < 1 || val > U16_MAX)
				rc = -EINVAL;
			अन्यथा
				iucv->msglimit = val;
			अवरोध;
		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		rc = -ENOPROTOOPT;
		अवरोध;
	पूर्ण
	release_sock(sk);

	वापस rc;
पूर्ण

अटल पूर्णांक iucv_sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
				अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	अचिन्हित पूर्णांक val;
	पूर्णांक len;

	अगर (level != SOL_IUCV)
		वापस -ENOPROTOOPT;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (len < 0)
		वापस -EINVAL;

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	चयन (optname) अणु
	हाल SO_IPRMDATA_MSG:
		val = (iucv->flags & IUCV_IPRMDATA) ? 1 : 0;
		अवरोध;
	हाल SO_MSGLIMIT:
		lock_sock(sk);
		val = (iucv->path != शून्य) ? iucv->path->msglim	/* connected */
					   : iucv->msglimit;	/* शेष */
		release_sock(sk);
		अवरोध;
	हाल SO_MSGSIZE:
		अगर (sk->sk_state == IUCV_OPEN)
			वापस -EBADFD;
		val = (iucv->hs_dev) ? iucv->hs_dev->mtu -
				माप(काष्ठा af_iucv_trans_hdr) - ETH_HLEN :
				0x7fffffff;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	अगर (put_user(len, optlen))
		वापस -EFAULT;
	अगर (copy_to_user(optval, &val, len))
		वापस -EFAULT;

	वापस 0;
पूर्ण


/* Callback wrappers - called from iucv base support */
अटल पूर्णांक iucv_callback_connreq(काष्ठा iucv_path *path,
				 u8 ipvmid[8], u8 ipuser[16])
अणु
	अचिन्हित अक्षर user_data[16];
	अचिन्हित अक्षर nuser_data[16];
	अचिन्हित अक्षर src_name[8];
	काष्ठा sock *sk, *nsk;
	काष्ठा iucv_sock *iucv, *niucv;
	पूर्णांक err;

	स_नकल(src_name, ipuser, 8);
	EBCASC(src_name, 8);
	/* Find out अगर this path beदीर्घs to af_iucv. */
	पढ़ो_lock(&iucv_sk_list.lock);
	iucv = शून्य;
	sk = शून्य;
	sk_क्रम_each(sk, &iucv_sk_list.head)
		अगर (sk->sk_state == IUCV_LISTEN &&
		    !स_भेद(&iucv_sk(sk)->src_name, src_name, 8)) अणु
			/*
			 * Found a listening socket with
			 * src_name == ipuser[0-7].
			 */
			iucv = iucv_sk(sk);
			अवरोध;
		पूर्ण
	पढ़ो_unlock(&iucv_sk_list.lock);
	अगर (!iucv)
		/* No socket found, not one of our paths. */
		वापस -EINVAL;

	bh_lock_sock(sk);

	/* Check अगर parent socket is listening */
	low_nmcpy(user_data, iucv->src_name);
	high_nmcpy(user_data, iucv->dst_name);
	ASCEBC(user_data, माप(user_data));
	अगर (sk->sk_state != IUCV_LISTEN) अणु
		err = pr_iucv->path_sever(path, user_data);
		iucv_path_मुक्त(path);
		जाओ fail;
	पूर्ण

	/* Check क्रम backlog size */
	अगर (sk_acceptq_is_full(sk)) अणु
		err = pr_iucv->path_sever(path, user_data);
		iucv_path_मुक्त(path);
		जाओ fail;
	पूर्ण

	/* Create the new socket */
	nsk = iucv_sock_alloc(शून्य, sk->sk_protocol, GFP_ATOMIC, 0);
	अगर (!nsk) अणु
		err = pr_iucv->path_sever(path, user_data);
		iucv_path_मुक्त(path);
		जाओ fail;
	पूर्ण

	niucv = iucv_sk(nsk);
	iucv_sock_init(nsk, sk);
	niucv->transport = AF_IUCV_TRANS_IUCV;
	nsk->sk_allocation |= GFP_DMA;

	/* Set the new iucv_sock */
	स_नकल(niucv->dst_name, ipuser + 8, 8);
	EBCASC(niucv->dst_name, 8);
	स_नकल(niucv->dst_user_id, ipvmid, 8);
	स_नकल(niucv->src_name, iucv->src_name, 8);
	स_नकल(niucv->src_user_id, iucv->src_user_id, 8);
	niucv->path = path;

	/* Call iucv_accept */
	high_nmcpy(nuser_data, ipuser + 8);
	स_नकल(nuser_data + 8, niucv->src_name, 8);
	ASCEBC(nuser_data + 8, 8);

	/* set message limit क्रम path based on msglimit of accepting socket */
	niucv->msglimit = iucv->msglimit;
	path->msglim = iucv->msglimit;
	err = pr_iucv->path_accept(path, &af_iucv_handler, nuser_data, nsk);
	अगर (err) अणु
		iucv_sever_path(nsk, 1);
		iucv_sock_समाप्त(nsk);
		जाओ fail;
	पूर्ण

	iucv_accept_enqueue(sk, nsk);

	/* Wake up accept */
	nsk->sk_state = IUCV_CONNECTED;
	sk->sk_data_पढ़ोy(sk);
	err = 0;
fail:
	bh_unlock_sock(sk);
	वापस 0;
पूर्ण

अटल व्योम iucv_callback_connack(काष्ठा iucv_path *path, u8 ipuser[16])
अणु
	काष्ठा sock *sk = path->निजी;

	sk->sk_state = IUCV_CONNECTED;
	sk->sk_state_change(sk);
पूर्ण

अटल व्योम iucv_callback_rx(काष्ठा iucv_path *path, काष्ठा iucv_message *msg)
अणु
	काष्ठा sock *sk = path->निजी;
	काष्ठा iucv_sock *iucv = iucv_sk(sk);
	काष्ठा sk_buff *skb;
	काष्ठा sock_msg_q *save_msg;
	पूर्णांक len;

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
		pr_iucv->message_reject(path, msg);
		वापस;
	पूर्ण

	spin_lock(&iucv->message_q.lock);

	अगर (!list_empty(&iucv->message_q.list) ||
	    !skb_queue_empty(&iucv->backlog_skb_q))
		जाओ save_message;

	len = atomic_पढ़ो(&sk->sk_rmem_alloc);
	len += SKB_TRUESIZE(iucv_msg_length(msg));
	अगर (len > sk->sk_rcvbuf)
		जाओ save_message;

	skb = alloc_iucv_recv_skb(iucv_msg_length(msg));
	अगर (!skb)
		जाओ save_message;

	iucv_process_message(sk, skb, path, msg);
	जाओ out_unlock;

save_message:
	save_msg = kzalloc(माप(काष्ठा sock_msg_q), GFP_ATOMIC | GFP_DMA);
	अगर (!save_msg)
		जाओ out_unlock;
	save_msg->path = path;
	save_msg->msg = *msg;

	list_add_tail(&save_msg->list, &iucv->message_q.list);

out_unlock:
	spin_unlock(&iucv->message_q.lock);
पूर्ण

अटल व्योम iucv_callback_txकरोne(काष्ठा iucv_path *path,
				 काष्ठा iucv_message *msg)
अणु
	काष्ठा sock *sk = path->निजी;
	काष्ठा sk_buff *this = शून्य;
	काष्ठा sk_buff_head *list;
	काष्ठा sk_buff *list_skb;
	काष्ठा iucv_sock *iucv;
	अचिन्हित दीर्घ flags;

	iucv = iucv_sk(sk);
	list = &iucv->send_skb_q;

	bh_lock_sock(sk);

	spin_lock_irqsave(&list->lock, flags);
	skb_queue_walk(list, list_skb) अणु
		अगर (msg->tag == IUCV_SKB_CB(list_skb)->tag) अणु
			this = list_skb;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (this) अणु
		atomic_dec(&iucv->skbs_in_xmit);
		__skb_unlink(this, list);
	पूर्ण

	spin_unlock_irqrestore(&list->lock, flags);

	अगर (this) अणु
		kमुक्त_skb(this);
		/* wake up any process रुकोing क्रम sending */
		iucv_sock_wake_msglim(sk);
	पूर्ण

	अगर (sk->sk_state == IUCV_CLOSING) अणु
		अगर (atomic_पढ़ो(&iucv->skbs_in_xmit) == 0) अणु
			sk->sk_state = IUCV_CLOSED;
			sk->sk_state_change(sk);
		पूर्ण
	पूर्ण
	bh_unlock_sock(sk);

पूर्ण

अटल व्योम iucv_callback_connrej(काष्ठा iucv_path *path, u8 ipuser[16])
अणु
	काष्ठा sock *sk = path->निजी;

	अगर (sk->sk_state == IUCV_CLOSED)
		वापस;

	bh_lock_sock(sk);
	iucv_sever_path(sk, 1);
	sk->sk_state = IUCV_DISCONN;

	sk->sk_state_change(sk);
	bh_unlock_sock(sk);
पूर्ण

/* called अगर the other communication side shuts करोwn its RECV direction;
 * in turn, the callback sets SEND_SHUTDOWN to disable sending of data.
 */
अटल व्योम iucv_callback_shutकरोwn(काष्ठा iucv_path *path, u8 ipuser[16])
अणु
	काष्ठा sock *sk = path->निजी;

	bh_lock_sock(sk);
	अगर (sk->sk_state != IUCV_CLOSED) अणु
		sk->sk_shutकरोwn |= SEND_SHUTDOWN;
		sk->sk_state_change(sk);
	पूर्ण
	bh_unlock_sock(sk);
पूर्ण

/***************** HiperSockets transport callbacks ********************/
अटल व्योम afiucv_swap_src_dest(काष्ठा sk_buff *skb)
अणु
	काष्ठा af_iucv_trans_hdr *trans_hdr = iucv_trans_hdr(skb);
	अक्षर पंचांगpID[8];
	अक्षर पंचांगpName[8];

	ASCEBC(trans_hdr->destUserID, माप(trans_hdr->destUserID));
	ASCEBC(trans_hdr->destAppName, माप(trans_hdr->destAppName));
	ASCEBC(trans_hdr->srcUserID, माप(trans_hdr->srcUserID));
	ASCEBC(trans_hdr->srcAppName, माप(trans_hdr->srcAppName));
	स_नकल(पंचांगpID, trans_hdr->srcUserID, 8);
	स_नकल(पंचांगpName, trans_hdr->srcAppName, 8);
	स_नकल(trans_hdr->srcUserID, trans_hdr->destUserID, 8);
	स_नकल(trans_hdr->srcAppName, trans_hdr->destAppName, 8);
	स_नकल(trans_hdr->destUserID, पंचांगpID, 8);
	स_नकल(trans_hdr->destAppName, पंचांगpName, 8);
	skb_push(skb, ETH_HLEN);
	स_रखो(skb->data, 0, ETH_HLEN);
पूर्ण

/**
 * afiucv_hs_callback_syn - react on received SYN
 **/
अटल पूर्णांक afiucv_hs_callback_syn(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा af_iucv_trans_hdr *trans_hdr = iucv_trans_hdr(skb);
	काष्ठा sock *nsk;
	काष्ठा iucv_sock *iucv, *niucv;
	पूर्णांक err;

	iucv = iucv_sk(sk);
	अगर (!iucv) अणु
		/* no sock - connection refused */
		afiucv_swap_src_dest(skb);
		trans_hdr->flags = AF_IUCV_FLAG_SYN | AF_IUCV_FLAG_FIN;
		err = dev_queue_xmit(skb);
		जाओ out;
	पूर्ण

	nsk = iucv_sock_alloc(शून्य, sk->sk_protocol, GFP_ATOMIC, 0);
	bh_lock_sock(sk);
	अगर ((sk->sk_state != IUCV_LISTEN) ||
	    sk_acceptq_is_full(sk) ||
	    !nsk) अणु
		/* error on server socket - connection refused */
		afiucv_swap_src_dest(skb);
		trans_hdr->flags = AF_IUCV_FLAG_SYN | AF_IUCV_FLAG_FIN;
		err = dev_queue_xmit(skb);
		iucv_sock_समाप्त(nsk);
		bh_unlock_sock(sk);
		जाओ out;
	पूर्ण

	niucv = iucv_sk(nsk);
	iucv_sock_init(nsk, sk);
	niucv->transport = AF_IUCV_TRANS_HIPER;
	niucv->msglimit = iucv->msglimit;
	अगर (!trans_hdr->winकरोw)
		niucv->msglimit_peer = IUCV_HIPER_MSGLIM_DEFAULT;
	अन्यथा
		niucv->msglimit_peer = trans_hdr->winकरोw;
	स_नकल(niucv->dst_name, trans_hdr->srcAppName, 8);
	स_नकल(niucv->dst_user_id, trans_hdr->srcUserID, 8);
	स_नकल(niucv->src_name, iucv->src_name, 8);
	स_नकल(niucv->src_user_id, iucv->src_user_id, 8);
	nsk->sk_bound_dev_अगर = sk->sk_bound_dev_अगर;
	niucv->hs_dev = iucv->hs_dev;
	dev_hold(niucv->hs_dev);
	afiucv_swap_src_dest(skb);
	trans_hdr->flags = AF_IUCV_FLAG_SYN | AF_IUCV_FLAG_ACK;
	trans_hdr->winकरोw = niucv->msglimit;
	/* अगर receiver acks the xmit connection is established */
	err = dev_queue_xmit(skb);
	अगर (!err) अणु
		iucv_accept_enqueue(sk, nsk);
		nsk->sk_state = IUCV_CONNECTED;
		sk->sk_data_पढ़ोy(sk);
	पूर्ण अन्यथा
		iucv_sock_समाप्त(nsk);
	bh_unlock_sock(sk);

out:
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * afiucv_hs_callback_synack() - react on received SYN-ACK
 **/
अटल पूर्णांक afiucv_hs_callback_synack(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	अगर (!iucv)
		जाओ out;
	अगर (sk->sk_state != IUCV_BOUND)
		जाओ out;
	bh_lock_sock(sk);
	iucv->msglimit_peer = iucv_trans_hdr(skb)->winकरोw;
	sk->sk_state = IUCV_CONNECTED;
	sk->sk_state_change(sk);
	bh_unlock_sock(sk);
out:
	kमुक्त_skb(skb);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * afiucv_hs_callback_synfin() - react on received SYN_FIN
 **/
अटल पूर्णांक afiucv_hs_callback_synfin(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	अगर (!iucv)
		जाओ out;
	अगर (sk->sk_state != IUCV_BOUND)
		जाओ out;
	bh_lock_sock(sk);
	sk->sk_state = IUCV_DISCONN;
	sk->sk_state_change(sk);
	bh_unlock_sock(sk);
out:
	kमुक्त_skb(skb);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * afiucv_hs_callback_fin() - react on received FIN
 **/
अटल पूर्णांक afiucv_hs_callback_fin(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	/* other end of connection बंदd */
	अगर (!iucv)
		जाओ out;
	bh_lock_sock(sk);
	अगर (sk->sk_state == IUCV_CONNECTED) अणु
		sk->sk_state = IUCV_DISCONN;
		sk->sk_state_change(sk);
	पूर्ण
	bh_unlock_sock(sk);
out:
	kमुक्त_skb(skb);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * afiucv_hs_callback_win() - react on received WIN
 **/
अटल पूर्णांक afiucv_hs_callback_win(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	अगर (!iucv)
		वापस NET_RX_SUCCESS;

	अगर (sk->sk_state != IUCV_CONNECTED)
		वापस NET_RX_SUCCESS;

	atomic_sub(iucv_trans_hdr(skb)->winकरोw, &iucv->msg_sent);
	iucv_sock_wake_msglim(sk);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * afiucv_hs_callback_rx() - react on received data
 **/
अटल पूर्णांक afiucv_hs_callback_rx(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	अगर (!iucv) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	अगर (sk->sk_state != IUCV_CONNECTED) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	अगर (sk->sk_shutकरोwn & RCV_SHUTDOWN) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	/* ग_लिखो stuff from iucv_msg to skb cb */
	skb_pull(skb, माप(काष्ठा af_iucv_trans_hdr));
	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);
	IUCV_SKB_CB(skb)->offset = 0;
	अगर (sk_filter(sk, skb)) अणु
		atomic_inc(&sk->sk_drops);	/* skb rejected by filter */
		kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	spin_lock(&iucv->message_q.lock);
	अगर (skb_queue_empty(&iucv->backlog_skb_q)) अणु
		अगर (__sock_queue_rcv_skb(sk, skb))
			/* handle rcv queue full */
			skb_queue_tail(&iucv->backlog_skb_q, skb);
	पूर्ण अन्यथा
		skb_queue_tail(&iucv_sk(sk)->backlog_skb_q, skb);
	spin_unlock(&iucv->message_q.lock);
	वापस NET_RX_SUCCESS;
पूर्ण

/**
 * afiucv_hs_rcv() - base function क्रम arriving data through HiperSockets
 *                   transport
 *                   called from netअगर RX softirq
 **/
अटल पूर्णांक afiucv_hs_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
	काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	काष्ठा sock *sk;
	काष्ठा iucv_sock *iucv;
	काष्ठा af_iucv_trans_hdr *trans_hdr;
	पूर्णांक err = NET_RX_SUCCESS;
	अक्षर nullstring[8];

	अगर (!pskb_may_pull(skb, माप(*trans_hdr))) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_SUCCESS;
	पूर्ण

	trans_hdr = iucv_trans_hdr(skb);
	EBCASC(trans_hdr->destAppName, माप(trans_hdr->destAppName));
	EBCASC(trans_hdr->destUserID, माप(trans_hdr->destUserID));
	EBCASC(trans_hdr->srcAppName, माप(trans_hdr->srcAppName));
	EBCASC(trans_hdr->srcUserID, माप(trans_hdr->srcUserID));
	स_रखो(nullstring, 0, माप(nullstring));
	iucv = शून्य;
	sk = शून्य;
	पढ़ो_lock(&iucv_sk_list.lock);
	sk_क्रम_each(sk, &iucv_sk_list.head) अणु
		अगर (trans_hdr->flags == AF_IUCV_FLAG_SYN) अणु
			अगर ((!स_भेद(&iucv_sk(sk)->src_name,
				     trans_hdr->destAppName, 8)) &&
			    (!स_भेद(&iucv_sk(sk)->src_user_id,
				     trans_hdr->destUserID, 8)) &&
			    (!स_भेद(&iucv_sk(sk)->dst_name, nullstring, 8)) &&
			    (!स_भेद(&iucv_sk(sk)->dst_user_id,
				     nullstring, 8))) अणु
				iucv = iucv_sk(sk);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((!स_भेद(&iucv_sk(sk)->src_name,
				     trans_hdr->destAppName, 8)) &&
			    (!स_भेद(&iucv_sk(sk)->src_user_id,
				     trans_hdr->destUserID, 8)) &&
			    (!स_भेद(&iucv_sk(sk)->dst_name,
				     trans_hdr->srcAppName, 8)) &&
			    (!स_भेद(&iucv_sk(sk)->dst_user_id,
				     trans_hdr->srcUserID, 8))) अणु
				iucv = iucv_sk(sk);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	पढ़ो_unlock(&iucv_sk_list.lock);
	अगर (!iucv)
		sk = शून्य;

	/* no sock
	how should we send with no sock
	1) send without sock no send rc checking?
	2) पूर्णांकroduce शेष sock to handle this हालs

	 SYN -> send SYN|ACK in good हाल, send SYN|FIN in bad हाल
	 data -> send FIN
	 SYN|ACK, SYN|FIN, FIN -> no action? */

	चयन (trans_hdr->flags) अणु
	हाल AF_IUCV_FLAG_SYN:
		/* connect request */
		err = afiucv_hs_callback_syn(sk, skb);
		अवरोध;
	हाल (AF_IUCV_FLAG_SYN | AF_IUCV_FLAG_ACK):
		/* connect request confirmed */
		err = afiucv_hs_callback_synack(sk, skb);
		अवरोध;
	हाल (AF_IUCV_FLAG_SYN | AF_IUCV_FLAG_FIN):
		/* connect request refused */
		err = afiucv_hs_callback_synfin(sk, skb);
		अवरोध;
	हाल (AF_IUCV_FLAG_FIN):
		/* बंद request */
		err = afiucv_hs_callback_fin(sk, skb);
		अवरोध;
	हाल (AF_IUCV_FLAG_WIN):
		err = afiucv_hs_callback_win(sk, skb);
		अगर (skb->len == माप(काष्ठा af_iucv_trans_hdr)) अणु
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण
		fallthrough;	/* and receive non-zero length data */
	हाल (AF_IUCV_FLAG_SHT):
		/* shutकरोwn request */
		fallthrough;	/* and receive zero length data */
	हाल 0:
		/* plain data frame */
		IUCV_SKB_CB(skb)->class = trans_hdr->iucv_hdr.class;
		err = afiucv_hs_callback_rx(sk, skb);
		अवरोध;
	शेष:
		kमुक्त_skb(skb);
	पूर्ण

	वापस err;
पूर्ण

/**
 * afiucv_hs_callback_txnotअगरy() - handle send notअगरications from HiperSockets
 *                                 transport
 **/
अटल व्योम afiucv_hs_callback_txnotअगरy(काष्ठा sock *sk, क्रमागत iucv_tx_notअगरy n)
अणु
	काष्ठा iucv_sock *iucv = iucv_sk(sk);

	अगर (sock_flag(sk, SOCK_ZAPPED))
		वापस;

	चयन (n) अणु
	हाल TX_NOTIFY_OK:
		atomic_dec(&iucv->skbs_in_xmit);
		iucv_sock_wake_msglim(sk);
		अवरोध;
	हाल TX_NOTIFY_PENDING:
		atomic_inc(&iucv->pendings);
		अवरोध;
	हाल TX_NOTIFY_DELAYED_OK:
		atomic_dec(&iucv->skbs_in_xmit);
		अगर (atomic_dec_वापस(&iucv->pendings) <= 0)
			iucv_sock_wake_msglim(sk);
		अवरोध;
	शेष:
		atomic_dec(&iucv->skbs_in_xmit);
		अगर (sk->sk_state == IUCV_CONNECTED) अणु
			sk->sk_state = IUCV_DISCONN;
			sk->sk_state_change(sk);
		पूर्ण
	पूर्ण

	अगर (sk->sk_state == IUCV_CLOSING) अणु
		अगर (atomic_पढ़ो(&iucv->skbs_in_xmit) == 0) अणु
			sk->sk_state = IUCV_CLOSED;
			sk->sk_state_change(sk);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * afiucv_netdev_event: handle netdev notअगरier chain events
 */
अटल पूर्णांक afiucv_netdev_event(काष्ठा notअगरier_block *this,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *event_dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा sock *sk;
	काष्ठा iucv_sock *iucv;

	चयन (event) अणु
	हाल NETDEV_REBOOT:
	हाल NETDEV_GOING_DOWN:
		sk_क्रम_each(sk, &iucv_sk_list.head) अणु
			iucv = iucv_sk(sk);
			अगर ((iucv->hs_dev == event_dev) &&
			    (sk->sk_state == IUCV_CONNECTED)) अणु
				अगर (event == NETDEV_GOING_DOWN)
					iucv_send_ctrl(sk, AF_IUCV_FLAG_FIN);
				sk->sk_state = IUCV_DISCONN;
				sk->sk_state_change(sk);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल NETDEV_DOWN:
	हाल NETDEV_UNREGISTER:
	शेष:
		अवरोध;
	पूर्ण
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block afiucv_netdev_notअगरier = अणु
	.notअगरier_call = afiucv_netdev_event,
पूर्ण;

अटल स्थिर काष्ठा proto_ops iucv_sock_ops = अणु
	.family		= PF_IUCV,
	.owner		= THIS_MODULE,
	.release	= iucv_sock_release,
	.bind		= iucv_sock_bind,
	.connect	= iucv_sock_connect,
	.listen		= iucv_sock_listen,
	.accept		= iucv_sock_accept,
	.getname	= iucv_sock_getname,
	.sendmsg	= iucv_sock_sendmsg,
	.recvmsg	= iucv_sock_recvmsg,
	.poll		= iucv_sock_poll,
	.ioctl		= sock_no_ioctl,
	.mmap		= sock_no_mmap,
	.socketpair	= sock_no_socketpair,
	.shutकरोwn	= iucv_sock_shutकरोwn,
	.setsockopt	= iucv_sock_setsockopt,
	.माला_लोockopt	= iucv_sock_माला_लोockopt,
पूर्ण;

अटल पूर्णांक iucv_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol,
			    पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	अगर (protocol && protocol != PF_IUCV)
		वापस -EPROTONOSUPPORT;

	sock->state = SS_UNCONNECTED;

	चयन (sock->type) अणु
	हाल SOCK_STREAM:
	हाल SOCK_SEQPACKET:
		/* currently, proto ops can handle both sk types */
		sock->ops = &iucv_sock_ops;
		अवरोध;
	शेष:
		वापस -ESOCKTNOSUPPORT;
	पूर्ण

	sk = iucv_sock_alloc(sock, protocol, GFP_KERNEL, kern);
	अगर (!sk)
		वापस -ENOMEM;

	iucv_sock_init(sk, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_proto_family iucv_sock_family_ops = अणु
	.family	= AF_IUCV,
	.owner	= THIS_MODULE,
	.create	= iucv_sock_create,
पूर्ण;

अटल काष्ठा packet_type iucv_packet_type = अणु
	.type = cpu_to_be16(ETH_P_AF_IUCV),
	.func = afiucv_hs_rcv,
पूर्ण;

अटल पूर्णांक afiucv_iucv_init(व्योम)
अणु
	वापस pr_iucv->iucv_रेजिस्टर(&af_iucv_handler, 0);
पूर्ण

अटल व्योम afiucv_iucv_निकास(व्योम)
अणु
	pr_iucv->iucv_unरेजिस्टर(&af_iucv_handler, 0);
पूर्ण

अटल पूर्णांक __init afiucv_init(व्योम)
अणु
	पूर्णांक err;

	अगर (MACHINE_IS_VM) अणु
		cpcmd("QUERY USERID", iucv_userid, माप(iucv_userid), &err);
		अगर (unlikely(err)) अणु
			WARN_ON(err);
			err = -EPROTONOSUPPORT;
			जाओ out;
		पूर्ण

		pr_iucv = try_then_request_module(symbol_get(iucv_अगर), "iucv");
		अगर (!pr_iucv) अणु
			prपूर्णांकk(KERN_WARNING "iucv_if lookup failed\n");
			स_रखो(&iucv_userid, 0, माप(iucv_userid));
		पूर्ण
	पूर्ण अन्यथा अणु
		स_रखो(&iucv_userid, 0, माप(iucv_userid));
		pr_iucv = शून्य;
	पूर्ण

	err = proto_रेजिस्टर(&iucv_proto, 0);
	अगर (err)
		जाओ out;
	err = sock_रेजिस्टर(&iucv_sock_family_ops);
	अगर (err)
		जाओ out_proto;

	अगर (pr_iucv) अणु
		err = afiucv_iucv_init();
		अगर (err)
			जाओ out_sock;
	पूर्ण

	err = रेजिस्टर_netdevice_notअगरier(&afiucv_netdev_notअगरier);
	अगर (err)
		जाओ out_notअगरier;

	dev_add_pack(&iucv_packet_type);
	वापस 0;

out_notअगरier:
	अगर (pr_iucv)
		afiucv_iucv_निकास();
out_sock:
	sock_unरेजिस्टर(PF_IUCV);
out_proto:
	proto_unरेजिस्टर(&iucv_proto);
out:
	अगर (pr_iucv)
		symbol_put(iucv_अगर);
	वापस err;
पूर्ण

अटल व्योम __निकास afiucv_निकास(व्योम)
अणु
	अगर (pr_iucv) अणु
		afiucv_iucv_निकास();
		symbol_put(iucv_अगर);
	पूर्ण

	unरेजिस्टर_netdevice_notअगरier(&afiucv_netdev_notअगरier);
	dev_हटाओ_pack(&iucv_packet_type);
	sock_unरेजिस्टर(PF_IUCV);
	proto_unरेजिस्टर(&iucv_proto);
पूर्ण

module_init(afiucv_init);
module_निकास(afiucv_निकास);

MODULE_AUTHOR("Jennifer Hunt <jenhunt@us.ibm.com>");
MODULE_DESCRIPTION("IUCV Sockets ver " VERSION);
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_IUCV);
