<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Instituto Nokia de Tecnologia
 *
 * Authors:
 *    Aloisio Almeida Jr <aloisio.almeida@खोलोbossa.org>
 *    Lauro Ramos Venancio <lauro.venancio@खोलोbossa.org>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": %s: " fmt, __func__

#समावेश <net/tcp_states.h>
#समावेश <linux/nfc.h>
#समावेश <linux/export.h>

#समावेश "nfc.h"

अटल काष्ठा nfc_sock_list raw_sk_list = अणु
	.lock = __RW_LOCK_UNLOCKED(raw_sk_list.lock)
पूर्ण;

अटल व्योम nfc_sock_link(काष्ठा nfc_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock(&l->lock);
	sk_add_node(sk, &l->head);
	ग_लिखो_unlock(&l->lock);
पूर्ण

अटल व्योम nfc_sock_unlink(काष्ठा nfc_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock(&l->lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock(&l->lock);
पूर्ण

अटल व्योम rawsock_ग_लिखो_queue_purge(काष्ठा sock *sk)
अणु
	pr_debug("sk=%p\n", sk);

	spin_lock_bh(&sk->sk_ग_लिखो_queue.lock);
	__skb_queue_purge(&sk->sk_ग_लिखो_queue);
	nfc_rawsock(sk)->tx_work_scheduled = false;
	spin_unlock_bh(&sk->sk_ग_लिखो_queue.lock);
पूर्ण

अटल व्योम rawsock_report_error(काष्ठा sock *sk, पूर्णांक err)
अणु
	pr_debug("sk=%p err=%d\n", sk, err);

	sk->sk_shutकरोwn = SHUTDOWN_MASK;
	sk->sk_err = -err;
	sk->sk_error_report(sk);

	rawsock_ग_लिखो_queue_purge(sk);
पूर्ण

अटल पूर्णांक rawsock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	pr_debug("sock=%p sk=%p\n", sock, sk);

	अगर (!sk)
		वापस 0;

	अगर (sock->type == SOCK_RAW)
		nfc_sock_unlink(&raw_sk_list, sk);

	sock_orphan(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक rawsock_connect(काष्ठा socket *sock, काष्ठा sockaddr *_addr,
			   पूर्णांक len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा sockaddr_nfc *addr = (काष्ठा sockaddr_nfc *)_addr;
	काष्ठा nfc_dev *dev;
	पूर्णांक rc = 0;

	pr_debug("sock=%p sk=%p flags=%d\n", sock, sk, flags);

	अगर (!addr || len < माप(काष्ठा sockaddr_nfc) ||
	    addr->sa_family != AF_NFC)
		वापस -EINVAL;

	pr_debug("addr dev_idx=%u target_idx=%u protocol=%u\n",
		 addr->dev_idx, addr->target_idx, addr->nfc_protocol);

	lock_sock(sk);

	अगर (sock->state == SS_CONNECTED) अणु
		rc = -EISCONN;
		जाओ error;
	पूर्ण

	dev = nfc_get_device(addr->dev_idx);
	अगर (!dev) अणु
		rc = -ENODEV;
		जाओ error;
	पूर्ण

	अगर (addr->target_idx > dev->target_next_idx - 1 ||
	    addr->target_idx < dev->target_next_idx - dev->n_tarमाला_लो) अणु
		rc = -EINVAL;
		जाओ put_dev;
	पूर्ण

	rc = nfc_activate_target(dev, addr->target_idx, addr->nfc_protocol);
	अगर (rc)
		जाओ put_dev;

	nfc_rawsock(sk)->dev = dev;
	nfc_rawsock(sk)->target_idx = addr->target_idx;
	sock->state = SS_CONNECTED;
	sk->sk_state = TCP_ESTABLISHED;
	sk->sk_state_change(sk);

	release_sock(sk);
	वापस 0;

put_dev:
	nfc_put_device(dev);
error:
	release_sock(sk);
	वापस rc;
पूर्ण

अटल पूर्णांक rawsock_add_header(काष्ठा sk_buff *skb)
अणु
	*(u8 *)skb_push(skb, NFC_HEADER_SIZE) = 0;

	वापस 0;
पूर्ण

अटल व्योम rawsock_data_exchange_complete(व्योम *context, काष्ठा sk_buff *skb,
					   पूर्णांक err)
अणु
	काष्ठा sock *sk = (काष्ठा sock *) context;

	BUG_ON(in_irq());

	pr_debug("sk=%p err=%d\n", sk, err);

	अगर (err)
		जाओ error;

	err = rawsock_add_header(skb);
	अगर (err)
		जाओ error_skb;

	err = sock_queue_rcv_skb(sk, skb);
	अगर (err)
		जाओ error_skb;

	spin_lock_bh(&sk->sk_ग_लिखो_queue.lock);
	अगर (!skb_queue_empty(&sk->sk_ग_लिखो_queue))
		schedule_work(&nfc_rawsock(sk)->tx_work);
	अन्यथा
		nfc_rawsock(sk)->tx_work_scheduled = false;
	spin_unlock_bh(&sk->sk_ग_लिखो_queue.lock);

	sock_put(sk);
	वापस;

error_skb:
	kमुक्त_skb(skb);

error:
	rawsock_report_error(sk, err);
	sock_put(sk);
पूर्ण

अटल व्योम rawsock_tx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sock *sk = to_rawsock_sk(work);
	काष्ठा nfc_dev *dev = nfc_rawsock(sk)->dev;
	u32 target_idx = nfc_rawsock(sk)->target_idx;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	pr_debug("sk=%p target_idx=%u\n", sk, target_idx);

	अगर (sk->sk_shutकरोwn & SEND_SHUTDOWN) अणु
		rawsock_ग_लिखो_queue_purge(sk);
		वापस;
	पूर्ण

	skb = skb_dequeue(&sk->sk_ग_लिखो_queue);

	sock_hold(sk);
	rc = nfc_data_exchange(dev, target_idx, skb,
			       rawsock_data_exchange_complete, sk);
	अगर (rc) अणु
		rawsock_report_error(sk, rc);
		sock_put(sk);
	पूर्ण
पूर्ण

अटल पूर्णांक rawsock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;
	काष्ठा nfc_dev *dev = nfc_rawsock(sk)->dev;
	काष्ठा sk_buff *skb;
	पूर्णांक rc;

	pr_debug("sock=%p sk=%p len=%zu\n", sock, sk, len);

	अगर (msg->msg_namelen)
		वापस -EOPNOTSUPP;

	अगर (sock->state != SS_CONNECTED)
		वापस -ENOTCONN;

	skb = nfc_alloc_send_skb(dev, sk, msg->msg_flags, len, &rc);
	अगर (skb == शून्य)
		वापस rc;

	rc = स_नकल_from_msg(skb_put(skb, len), msg, len);
	अगर (rc < 0) अणु
		kमुक्त_skb(skb);
		वापस rc;
	पूर्ण

	spin_lock_bh(&sk->sk_ग_लिखो_queue.lock);
	__skb_queue_tail(&sk->sk_ग_लिखो_queue, skb);
	अगर (!nfc_rawsock(sk)->tx_work_scheduled) अणु
		schedule_work(&nfc_rawsock(sk)->tx_work);
		nfc_rawsock(sk)->tx_work_scheduled = true;
	पूर्ण
	spin_unlock_bh(&sk->sk_ग_लिखो_queue.lock);

	वापस len;
पूर्ण

अटल पूर्णांक rawsock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
			   पूर्णांक flags)
अणु
	पूर्णांक noblock = flags & MSG_DONTWAIT;
	काष्ठा sock *sk = sock->sk;
	काष्ठा sk_buff *skb;
	पूर्णांक copied;
	पूर्णांक rc;

	pr_debug("sock=%p sk=%p len=%zu flags=%d\n", sock, sk, len, flags);

	skb = skb_recv_datagram(sk, flags, noblock, &rc);
	अगर (!skb)
		वापस rc;

	copied = skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	rc = skb_copy_datagram_msg(skb, 0, msg, copied);

	skb_मुक्त_datagram(sk, skb);

	वापस rc ? : copied;
पूर्ण

अटल स्थिर काष्ठा proto_ops rawsock_ops = अणु
	.family         = PF_NFC,
	.owner          = THIS_MODULE,
	.release        = rawsock_release,
	.bind           = sock_no_bind,
	.connect        = rawsock_connect,
	.socketpair     = sock_no_socketpair,
	.accept         = sock_no_accept,
	.getname        = sock_no_getname,
	.poll           = datagram_poll,
	.ioctl          = sock_no_ioctl,
	.listen         = sock_no_listen,
	.shutकरोwn       = sock_no_shutकरोwn,
	.sendmsg        = rawsock_sendmsg,
	.recvmsg        = rawsock_recvmsg,
	.mmap           = sock_no_mmap,
पूर्ण;

अटल स्थिर काष्ठा proto_ops rawsock_raw_ops = अणु
	.family         = PF_NFC,
	.owner          = THIS_MODULE,
	.release        = rawsock_release,
	.bind           = sock_no_bind,
	.connect        = sock_no_connect,
	.socketpair     = sock_no_socketpair,
	.accept         = sock_no_accept,
	.getname        = sock_no_getname,
	.poll           = datagram_poll,
	.ioctl          = sock_no_ioctl,
	.listen         = sock_no_listen,
	.shutकरोwn       = sock_no_shutकरोwn,
	.sendmsg        = sock_no_sendmsg,
	.recvmsg        = rawsock_recvmsg,
	.mmap           = sock_no_mmap,
पूर्ण;

अटल व्योम rawsock_deकाष्ठा(काष्ठा sock *sk)
अणु
	pr_debug("sk=%p\n", sk);

	अगर (sk->sk_state == TCP_ESTABLISHED) अणु
		nfc_deactivate_target(nfc_rawsock(sk)->dev,
				      nfc_rawsock(sk)->target_idx,
				      NFC_TARGET_MODE_IDLE);
		nfc_put_device(nfc_rawsock(sk)->dev);
	पूर्ण

	skb_queue_purge(&sk->sk_receive_queue);

	अगर (!sock_flag(sk, SOCK_DEAD)) अणु
		pr_err("Freeing alive NFC raw socket %p\n", sk);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक rawsock_create(काष्ठा net *net, काष्ठा socket *sock,
			  स्थिर काष्ठा nfc_protocol *nfc_proto, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	pr_debug("sock=%p\n", sock);

	अगर ((sock->type != SOCK_SEQPACKET) && (sock->type != SOCK_RAW))
		वापस -ESOCKTNOSUPPORT;

	अगर (sock->type == SOCK_RAW) अणु
		अगर (!ns_capable(net->user_ns, CAP_NET_RAW))
			वापस -EPERM;
		sock->ops = &rawsock_raw_ops;
	पूर्ण अन्यथा अणु
		sock->ops = &rawsock_ops;
	पूर्ण

	sk = sk_alloc(net, PF_NFC, GFP_ATOMIC, nfc_proto->proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);
	sk->sk_protocol = nfc_proto->id;
	sk->sk_deकाष्ठा = rawsock_deकाष्ठा;
	sock->state = SS_UNCONNECTED;
	अगर (sock->type == SOCK_RAW)
		nfc_sock_link(&raw_sk_list, sk);
	अन्यथा अणु
		INIT_WORK(&nfc_rawsock(sk)->tx_work, rawsock_tx_work);
		nfc_rawsock(sk)->tx_work_scheduled = false;
	पूर्ण

	वापस 0;
पूर्ण

व्योम nfc_send_to_raw_sock(काष्ठा nfc_dev *dev, काष्ठा sk_buff *skb,
			  u8 payload_type, u8 direction)
अणु
	काष्ठा sk_buff *skb_copy = शून्य, *nskb;
	काष्ठा sock *sk;
	u8 *data;

	पढ़ो_lock(&raw_sk_list.lock);

	sk_क्रम_each(sk, &raw_sk_list.head) अणु
		अगर (!skb_copy) अणु
			skb_copy = __pskb_copy_fclone(skb, NFC_RAW_HEADER_SIZE,
						      GFP_ATOMIC, true);
			अगर (!skb_copy)
				जारी;

			data = skb_push(skb_copy, NFC_RAW_HEADER_SIZE);

			data[0] = dev ? dev->idx : 0xFF;
			data[1] = direction & 0x01;
			data[1] |= (payload_type << 1);
		पूर्ण

		nskb = skb_clone(skb_copy, GFP_ATOMIC);
		अगर (!nskb)
			जारी;

		अगर (sock_queue_rcv_skb(sk, nskb))
			kमुक्त_skb(nskb);
	पूर्ण

	पढ़ो_unlock(&raw_sk_list.lock);

	kमुक्त_skb(skb_copy);
पूर्ण
EXPORT_SYMBOL(nfc_send_to_raw_sock);

अटल काष्ठा proto rawsock_proto = अणु
	.name     = "NFC_RAW",
	.owner    = THIS_MODULE,
	.obj_size = माप(काष्ठा nfc_rawsock),
पूर्ण;

अटल स्थिर काष्ठा nfc_protocol rawsock_nfc_proto = अणु
	.id	  = NFC_SOCKPROTO_RAW,
	.proto    = &rawsock_proto,
	.owner    = THIS_MODULE,
	.create   = rawsock_create
पूर्ण;

पूर्णांक __init rawsock_init(व्योम)
अणु
	पूर्णांक rc;

	rc = nfc_proto_रेजिस्टर(&rawsock_nfc_proto);

	वापस rc;
पूर्ण

व्योम rawsock_निकास(व्योम)
अणु
	nfc_proto_unरेजिस्टर(&rawsock_nfc_proto);
पूर्ण
