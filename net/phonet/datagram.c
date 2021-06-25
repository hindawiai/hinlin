<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: datagram.c
 *
 * Datagram (ISI) Phonet sockets
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Authors: Sakari Ailus <sakari.ailus@nokia.com>
 *          Rथऊmi Denis-Courmont
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <यंत्र/ioctls.h>
#समावेश <net/sock.h>

#समावेश <linux/phonet.h>
#समावेश <linux/export.h>
#समावेश <net/phonet/phonet.h>

अटल पूर्णांक pn_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb);

/* associated socket ceases to exist */
अटल व्योम pn_sock_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	sk_common_release(sk);
पूर्ण

अटल पूर्णांक pn_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक answ;

	चयन (cmd) अणु
	हाल SIOCINQ:
		lock_sock(sk);
		skb = skb_peek(&sk->sk_receive_queue);
		answ = skb ? skb->len : 0;
		release_sock(sk);
		वापस put_user(answ, (पूर्णांक __user *)arg);

	हाल SIOCPNADDRESOURCE:
	हाल SIOCPNDELRESOURCE: अणु
			u32 res;
			अगर (get_user(res, (u32 __user *)arg))
				वापस -EFAULT;
			अगर (res >= 256)
				वापस -EINVAL;
			अगर (cmd == SIOCPNADDRESOURCE)
				वापस pn_sock_bind_res(sk, res);
			अन्यथा
				वापस pn_sock_unbind_res(sk, res);
		पूर्ण
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

/* Destroy socket. All references are gone. */
अटल व्योम pn_deकाष्ठा(काष्ठा sock *sk)
अणु
	skb_queue_purge(&sk->sk_receive_queue);
पूर्ण

अटल पूर्णांक pn_init(काष्ठा sock *sk)
अणु
	sk->sk_deकाष्ठा = pn_deकाष्ठा;
	वापस 0;
पूर्ण

अटल पूर्णांक pn_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	DECLARE_SOCKADDR(काष्ठा sockaddr_pn *, target, msg->msg_name);
	काष्ठा sk_buff *skb;
	पूर्णांक err;

	अगर (msg->msg_flags & ~(MSG_DONTWAIT|MSG_EOR|MSG_NOSIGNAL|
				MSG_CMSG_COMPAT))
		वापस -EOPNOTSUPP;

	अगर (target == शून्य)
		वापस -EDESTADDRREQ;

	अगर (msg->msg_namelen < माप(काष्ठा sockaddr_pn))
		वापस -EINVAL;

	अगर (target->spn_family != AF_PHONET)
		वापस -EAFNOSUPPORT;

	skb = sock_alloc_send_skb(sk, MAX_PHONET_HEADER + len,
					msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (skb == शून्य)
		वापस err;
	skb_reserve(skb, MAX_PHONET_HEADER);

	err = स_नकल_from_msg((व्योम *)skb_put(skb, len), msg, len);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस err;
	पूर्ण

	/*
	 * Fill in the Phonet header and
	 * finally pass the packet क्रमwards.
	 */
	err = pn_skb_send(sk, skb, target);

	/* If ok, वापस len. */
	वापस (err >= 0) ? len : err;
पूर्ण

अटल पूर्णांक pn_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		      पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा sockaddr_pn sa;
	पूर्णांक rval = -EOPNOTSUPP;
	पूर्णांक copylen;

	अगर (flags & ~(MSG_PEEK|MSG_TRUNC|MSG_DONTWAIT|MSG_NOSIGNAL|
			MSG_CMSG_COMPAT))
		जाओ out_noमुक्त;

	skb = skb_recv_datagram(sk, flags, noblock, &rval);
	अगर (skb == शून्य)
		जाओ out_noमुक्त;

	pn_skb_get_src_sockaddr(skb, &sa);

	copylen = skb->len;
	अगर (len < copylen) अणु
		msg->msg_flags |= MSG_TRUNC;
		copylen = len;
	पूर्ण

	rval = skb_copy_datagram_msg(skb, 0, msg, copylen);
	अगर (rval) अणु
		rval = -EFAULT;
		जाओ out;
	पूर्ण

	rval = (flags & MSG_TRUNC) ? skb->len : copylen;

	अगर (msg->msg_name != शून्य) अणु
		__sockaddr_check_size(माप(sa));
		स_नकल(msg->msg_name, &sa, माप(sa));
		*addr_len = माप(sa);
	पूर्ण

out:
	skb_मुक्त_datagram(sk, skb);

out_noमुक्त:
	वापस rval;
पूर्ण

/* Queue an skb क्रम a sock. */
अटल पूर्णांक pn_backlog_rcv(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err = sock_queue_rcv_skb(sk, skb);

	अगर (err < 0)
		kमुक्त_skb(skb);
	वापस err ? NET_RX_DROP : NET_RX_SUCCESS;
पूर्ण

/* Module registration */
अटल काष्ठा proto pn_proto = अणु
	.बंद		= pn_sock_बंद,
	.ioctl		= pn_ioctl,
	.init		= pn_init,
	.sendmsg	= pn_sendmsg,
	.recvmsg	= pn_recvmsg,
	.backlog_rcv	= pn_backlog_rcv,
	.hash		= pn_sock_hash,
	.unhash		= pn_sock_unhash,
	.get_port	= pn_sock_get_port,
	.obj_size	= माप(काष्ठा pn_sock),
	.owner		= THIS_MODULE,
	.name		= "PHONET",
पूर्ण;

अटल स्थिर काष्ठा phonet_protocol pn_dgram_proto = अणु
	.ops		= &phonet_dgram_ops,
	.prot		= &pn_proto,
	.sock_type	= SOCK_DGRAM,
पूर्ण;

पूर्णांक __init isi_रेजिस्टर(व्योम)
अणु
	वापस phonet_proto_रेजिस्टर(PN_PROTO_PHONET, &pn_dgram_proto);
पूर्ण

व्योम __निकास isi_unरेजिस्टर(व्योम)
अणु
	phonet_proto_unरेजिस्टर(PN_PROTO_PHONET, &pn_dgram_proto);
पूर्ण
