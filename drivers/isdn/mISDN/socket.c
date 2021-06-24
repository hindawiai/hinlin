<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Author	Karsten Keil <kkeil@novell.com>
 *
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/mISDNअगर.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश "core.h"

अटल u_पूर्णांक	*debug;

अटल काष्ठा proto mISDN_proto = अणु
	.name		= "misdn",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा mISDN_sock)
पूर्ण;

#घोषणा _pms(sk)	((काष्ठा mISDN_sock *)sk)

अटल काष्ठा mISDN_sock_list	data_sockets = अणु
	.lock = __RW_LOCK_UNLOCKED(data_sockets.lock)
पूर्ण;

अटल काष्ठा mISDN_sock_list	base_sockets = अणु
	.lock = __RW_LOCK_UNLOCKED(base_sockets.lock)
पूर्ण;

#घोषणा L2_HEADER_LEN	4

अटल अंतरभूत काष्ठा sk_buff *
_l2_alloc_skb(अचिन्हित पूर्णांक len, gfp_t gfp_mask)
अणु
	काष्ठा sk_buff  *skb;

	skb = alloc_skb(len + L2_HEADER_LEN, gfp_mask);
	अगर (likely(skb))
		skb_reserve(skb, L2_HEADER_LEN);
	वापस skb;
पूर्ण

अटल व्योम
mISDN_sock_link(काष्ठा mISDN_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&l->lock);
	sk_add_node(sk, &l->head);
	ग_लिखो_unlock_bh(&l->lock);
पूर्ण

अटल व्योम mISDN_sock_unlink(काष्ठा mISDN_sock_list *l, काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&l->lock);
	sk_del_node_init(sk);
	ग_लिखो_unlock_bh(&l->lock);
पूर्ण

अटल पूर्णांक
mISDN_send(काष्ठा mISDNchannel *ch, काष्ठा sk_buff *skb)
अणु
	काष्ठा mISDN_sock *msk;
	पूर्णांक	err;

	msk = container_of(ch, काष्ठा mISDN_sock, ch);
	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s len %d %p\n", __func__, skb->len, skb);
	अगर (msk->sk.sk_state == MISDN_CLOSED)
		वापस -EUNATCH;
	__net_बारtamp(skb);
	err = sock_queue_rcv_skb(&msk->sk, skb);
	अगर (err)
		prपूर्णांकk(KERN_WARNING "%s: error %d\n", __func__, err);
	वापस err;
पूर्ण

अटल पूर्णांक
mISDN_ctrl(काष्ठा mISDNchannel *ch, u_पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा mISDN_sock *msk;

	msk = container_of(ch, काष्ठा mISDN_sock, ch);
	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s(%p, %x, %p)\n", __func__, ch, cmd, arg);
	चयन (cmd) अणु
	हाल CLOSE_CHANNEL:
		msk->sk.sk_state = MISDN_CLOSED;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
mISDN_sock_cmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, काष्ठा sk_buff *skb)
अणु
	काष्ठा __kernel_old_समयval	tv;

	अगर (_pms(sk)->cmask & MISDN_TIME_STAMP) अणु
		skb_get_बारtamp(skb, &tv);
		put_cmsg(msg, SOL_MISDN, MISDN_TIME_STAMP, माप(tv), &tv);
	पूर्ण
पूर्ण

अटल पूर्णांक
mISDN_sock_recvmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len,
		   पूर्णांक flags)
अणु
	काष्ठा sk_buff		*skb;
	काष्ठा sock		*sk = sock->sk;

	पूर्णांक		copied, err;

	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s: len %d, flags %x ch.nr %d, proto %x\n",
		       __func__, (पूर्णांक)len, flags, _pms(sk)->ch.nr,
		       sk->sk_protocol);
	अगर (flags & (MSG_OOB))
		वापस -EOPNOTSUPP;

	अगर (sk->sk_state == MISDN_CLOSED)
		वापस 0;

	skb = skb_recv_datagram(sk, flags, flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		वापस err;

	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_mISDN *, maddr, msg->msg_name);

		maddr->family = AF_ISDN;
		maddr->dev = _pms(sk)->dev->id;
		अगर ((sk->sk_protocol == ISDN_P_LAPD_TE) ||
		    (sk->sk_protocol == ISDN_P_LAPD_NT)) अणु
			maddr->channel = (mISDN_HEAD_ID(skb) >> 16) & 0xff;
			maddr->tei =  (mISDN_HEAD_ID(skb) >> 8) & 0xff;
			maddr->sapi = mISDN_HEAD_ID(skb) & 0xff;
		पूर्ण अन्यथा अणु
			maddr->channel = _pms(sk)->ch.nr;
			maddr->sapi = _pms(sk)->ch.addr & 0xFF;
			maddr->tei =  (_pms(sk)->ch.addr >> 8) & 0xFF;
		पूर्ण
		msg->msg_namelen = माप(*maddr);
	पूर्ण

	copied = skb->len + MISDN_HEADER_LEN;
	अगर (len < copied) अणु
		अगर (flags & MSG_PEEK)
			refcount_dec(&skb->users);
		अन्यथा
			skb_queue_head(&sk->sk_receive_queue, skb);
		वापस -ENOSPC;
	पूर्ण
	स_नकल(skb_push(skb, MISDN_HEADER_LEN), mISDN_HEAD_P(skb),
	       MISDN_HEADER_LEN);

	err = skb_copy_datagram_msg(skb, 0, msg, copied);

	mISDN_sock_cmsg(sk, msg, skb);

	skb_मुक्त_datagram(sk, skb);

	वापस err ? : copied;
पूर्ण

अटल पूर्णांक
mISDN_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg, माप_प्रकार len)
अणु
	काष्ठा sock		*sk = sock->sk;
	काष्ठा sk_buff		*skb;
	पूर्णांक			err = -ENOMEM;

	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s: len %d flags %x ch %d proto %x\n",
		       __func__, (पूर्णांक)len, msg->msg_flags, _pms(sk)->ch.nr,
		       sk->sk_protocol);

	अगर (msg->msg_flags & MSG_OOB)
		वापस -EOPNOTSUPP;

	अगर (msg->msg_flags & ~(MSG_DONTWAIT | MSG_NOSIGNAL | MSG_ERRQUEUE))
		वापस -EINVAL;

	अगर (len < MISDN_HEADER_LEN)
		वापस -EINVAL;

	अगर (sk->sk_state != MISDN_BOUND)
		वापस -EBADFD;

	lock_sock(sk);

	skb = _l2_alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		जाओ करोne;

	अगर (स_नकल_from_msg(skb_put(skb, len), msg, len)) अणु
		err = -EFAULT;
		जाओ करोne;
	पूर्ण

	स_नकल(mISDN_HEAD_P(skb), skb->data, MISDN_HEADER_LEN);
	skb_pull(skb, MISDN_HEADER_LEN);

	अगर (msg->msg_namelen >= माप(काष्ठा sockaddr_mISDN)) अणु
		/* अगर we have a address, we use it */
		DECLARE_SOCKADDR(काष्ठा sockaddr_mISDN *, maddr, msg->msg_name);
		mISDN_HEAD_ID(skb) = maddr->channel;
	पूर्ण अन्यथा अणु /* use शेष क्रम L2 messages */
		अगर ((sk->sk_protocol == ISDN_P_LAPD_TE) ||
		    (sk->sk_protocol == ISDN_P_LAPD_NT))
			mISDN_HEAD_ID(skb) = _pms(sk)->ch.nr;
	पूर्ण

	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s: ID:%x\n",
		       __func__, mISDN_HEAD_ID(skb));

	err = -ENODEV;
	अगर (!_pms(sk)->ch.peer)
		जाओ करोne;
	err = _pms(sk)->ch.recv(_pms(sk)->ch.peer, skb);
	अगर (err)
		जाओ करोne;
	अन्यथा अणु
		skb = शून्य;
		err = len;
	पूर्ण

करोne:
	kमुक्त_skb(skb);
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक
data_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s(%p) sk=%p\n", __func__, sock, sk);
	अगर (!sk)
		वापस 0;
	चयन (sk->sk_protocol) अणु
	हाल ISDN_P_TE_S0:
	हाल ISDN_P_NT_S0:
	हाल ISDN_P_TE_E1:
	हाल ISDN_P_NT_E1:
		अगर (sk->sk_state == MISDN_BOUND)
			delete_channel(&_pms(sk)->ch);
		अन्यथा
			mISDN_sock_unlink(&data_sockets, sk);
		अवरोध;
	हाल ISDN_P_LAPD_TE:
	हाल ISDN_P_LAPD_NT:
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_HDLC:
	हाल ISDN_P_B_X75SLP:
	हाल ISDN_P_B_L2DTMF:
	हाल ISDN_P_B_L2DSP:
	हाल ISDN_P_B_L2DSPHDLC:
		delete_channel(&_pms(sk)->ch);
		mISDN_sock_unlink(&data_sockets, sk);
		अवरोध;
	पूर्ण

	lock_sock(sk);

	sock_orphan(sk);
	skb_queue_purge(&sk->sk_receive_queue);

	release_sock(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक
data_sock_ioctl_bound(काष्ठा sock *sk, अचिन्हित पूर्णांक cmd, व्योम __user *p)
अणु
	काष्ठा mISDN_ctrl_req	cq;
	पूर्णांक			err = -EINVAL, val[2];
	काष्ठा mISDNchannel	*bchan, *next;

	lock_sock(sk);
	अगर (!_pms(sk)->dev) अणु
		err = -ENODEV;
		जाओ करोne;
	पूर्ण
	चयन (cmd) अणु
	हाल IMCTRLREQ:
		अगर (copy_from_user(&cq, p, माप(cq))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर ((sk->sk_protocol & ~ISDN_P_B_MASK) == ISDN_P_B_START) अणु
			list_क्रम_each_entry_safe(bchan, next,
						 &_pms(sk)->dev->bchannels, list) अणु
				अगर (bchan->nr == cq.channel) अणु
					err = bchan->ctrl(bchan,
							  CONTROL_CHANNEL, &cq);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			err = _pms(sk)->dev->D.ctrl(&_pms(sk)->dev->D,
						    CONTROL_CHANNEL, &cq);
		अगर (err)
			अवरोध;
		अगर (copy_to_user(p, &cq, माप(cq)))
			err = -EFAULT;
		अवरोध;
	हाल IMCLEAR_L2:
		अगर (sk->sk_protocol != ISDN_P_LAPD_NT) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		val[0] = cmd;
		अगर (get_user(val[1], (पूर्णांक __user *)p)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		err = _pms(sk)->dev->teimgr->ctrl(_pms(sk)->dev->teimgr,
						  CONTROL_CHANNEL, val);
		अवरोध;
	हाल IMHOLD_L1:
		अगर (sk->sk_protocol != ISDN_P_LAPD_NT
		    && sk->sk_protocol != ISDN_P_LAPD_TE) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		val[0] = cmd;
		अगर (get_user(val[1], (पूर्णांक __user *)p)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		err = _pms(sk)->dev->teimgr->ctrl(_pms(sk)->dev->teimgr,
						  CONTROL_CHANNEL, val);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक
data_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक			err = 0, id;
	काष्ठा sock		*sk = sock->sk;
	काष्ठा mISDNdevice	*dev;
	काष्ठा mISDNversion	ver;

	चयन (cmd) अणु
	हाल IMGETVERSION:
		ver.major = MISDN_MAJOR_VERSION;
		ver.minor = MISDN_MINOR_VERSION;
		ver.release = MISDN_RELEASE;
		अगर (copy_to_user((व्योम __user *)arg, &ver, माप(ver)))
			err = -EFAULT;
		अवरोध;
	हाल IMGETCOUNT:
		id = get_mdevice_count();
		अगर (put_user(id, (पूर्णांक __user *)arg))
			err = -EFAULT;
		अवरोध;
	हाल IMGETDEVINFO:
		अगर (get_user(id, (पूर्णांक __user *)arg)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		dev = get_mdevice(id);
		अगर (dev) अणु
			काष्ठा mISDN_devinfo di;

			स_रखो(&di, 0, माप(di));
			di.id = dev->id;
			di.Dprotocols = dev->Dprotocols;
			di.Bprotocols = dev->Bprotocols | get_all_Bprotocols();
			di.protocol = dev->D.protocol;
			स_नकल(di.channelmap, dev->channelmap,
			       माप(di.channelmap));
			di.nrbchan = dev->nrbchan;
			strscpy(di.name, dev_name(&dev->dev), माप(di.name));
			अगर (copy_to_user((व्योम __user *)arg, &di, माप(di)))
				err = -EFAULT;
		पूर्ण अन्यथा
			err = -ENODEV;
		अवरोध;
	शेष:
		अगर (sk->sk_state == MISDN_BOUND)
			err = data_sock_ioctl_bound(sk, cmd,
						    (व्योम __user *)arg);
		अन्यथा
			err = -ENOTCONN;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक data_sock_setsockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
				sockptr_t optval, अचिन्हित पूर्णांक len)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0, opt = 0;

	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s(%p, %d, %x, optval, %d)\n", __func__, sock,
		       level, optname, len);

	lock_sock(sk);

	चयन (optname) अणु
	हाल MISDN_TIME_STAMP:
		अगर (copy_from_sockptr(&opt, optval, माप(पूर्णांक))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (opt)
			_pms(sk)->cmask |= MISDN_TIME_STAMP;
		अन्यथा
			_pms(sk)->cmask &= ~MISDN_TIME_STAMP;
		अवरोध;
	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक data_sock_माला_लोockopt(काष्ठा socket *sock, पूर्णांक level, पूर्णांक optname,
				अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा sock *sk = sock->sk;
	पूर्णांक len, opt;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	अगर (len != माप(अक्षर))
		वापस -EINVAL;

	चयन (optname) अणु
	हाल MISDN_TIME_STAMP:
		अगर (_pms(sk)->cmask & MISDN_TIME_STAMP)
			opt = 1;
		अन्यथा
			opt = 0;

		अगर (put_user(opt, optval))
			वापस -EFAULT;
		अवरोध;
	शेष:
		वापस -ENOPROTOOPT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
data_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_mISDN *maddr = (काष्ठा sockaddr_mISDN *) addr;
	काष्ठा sock *sk = sock->sk;
	काष्ठा sock *csk;
	पूर्णांक err = 0;

	अगर (*debug & DEBUG_SOCKET)
		prपूर्णांकk(KERN_DEBUG "%s(%p) sk=%p\n", __func__, sock, sk);
	अगर (addr_len != माप(काष्ठा sockaddr_mISDN))
		वापस -EINVAL;
	अगर (!maddr || maddr->family != AF_ISDN)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (_pms(sk)->dev) अणु
		err = -EALREADY;
		जाओ करोne;
	पूर्ण
	_pms(sk)->dev = get_mdevice(maddr->dev);
	अगर (!_pms(sk)->dev) अणु
		err = -ENODEV;
		जाओ करोne;
	पूर्ण

	अगर (sk->sk_protocol < ISDN_P_B_START) अणु
		पढ़ो_lock_bh(&data_sockets.lock);
		sk_क्रम_each(csk, &data_sockets.head) अणु
			अगर (sk == csk)
				जारी;
			अगर (_pms(csk)->dev != _pms(sk)->dev)
				जारी;
			अगर (csk->sk_protocol >= ISDN_P_B_START)
				जारी;
			अगर (IS_ISDN_P_TE(csk->sk_protocol)
			    == IS_ISDN_P_TE(sk->sk_protocol))
				जारी;
			पढ़ो_unlock_bh(&data_sockets.lock);
			err = -EBUSY;
			जाओ करोne;
		पूर्ण
		पढ़ो_unlock_bh(&data_sockets.lock);
	पूर्ण

	_pms(sk)->ch.send = mISDN_send;
	_pms(sk)->ch.ctrl = mISDN_ctrl;

	चयन (sk->sk_protocol) अणु
	हाल ISDN_P_TE_S0:
	हाल ISDN_P_NT_S0:
	हाल ISDN_P_TE_E1:
	हाल ISDN_P_NT_E1:
		mISDN_sock_unlink(&data_sockets, sk);
		err = connect_layer1(_pms(sk)->dev, &_pms(sk)->ch,
				     sk->sk_protocol, maddr);
		अगर (err)
			mISDN_sock_link(&data_sockets, sk);
		अवरोध;
	हाल ISDN_P_LAPD_TE:
	हाल ISDN_P_LAPD_NT:
		err = create_l2entity(_pms(sk)->dev, &_pms(sk)->ch,
				      sk->sk_protocol, maddr);
		अवरोध;
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_HDLC:
	हाल ISDN_P_B_X75SLP:
	हाल ISDN_P_B_L2DTMF:
	हाल ISDN_P_B_L2DSP:
	हाल ISDN_P_B_L2DSPHDLC:
		err = connect_Bstack(_pms(sk)->dev, &_pms(sk)->ch,
				     sk->sk_protocol, maddr);
		अवरोध;
	शेष:
		err = -EPROTONOSUPPORT;
	पूर्ण
	अगर (err)
		जाओ करोne;
	sk->sk_state = MISDN_BOUND;
	_pms(sk)->ch.protocol = sk->sk_protocol;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक
data_sock_getname(काष्ठा socket *sock, काष्ठा sockaddr *addr,
		  पूर्णांक peer)
अणु
	काष्ठा sockaddr_mISDN	*maddr = (काष्ठा sockaddr_mISDN *) addr;
	काष्ठा sock		*sk = sock->sk;

	अगर (!_pms(sk)->dev)
		वापस -EBADFD;

	lock_sock(sk);

	maddr->family = AF_ISDN;
	maddr->dev = _pms(sk)->dev->id;
	maddr->channel = _pms(sk)->ch.nr;
	maddr->sapi = _pms(sk)->ch.addr & 0xff;
	maddr->tei = (_pms(sk)->ch.addr >> 8) & 0xff;
	release_sock(sk);
	वापस माप(*maddr);
पूर्ण

अटल स्थिर काष्ठा proto_ops data_sock_ops = अणु
	.family		= PF_ISDN,
	.owner		= THIS_MODULE,
	.release	= data_sock_release,
	.ioctl		= data_sock_ioctl,
	.bind		= data_sock_bind,
	.getname	= data_sock_getname,
	.sendmsg	= mISDN_sock_sendmsg,
	.recvmsg	= mISDN_sock_recvmsg,
	.poll		= datagram_poll,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.setsockopt	= data_sock_setsockopt,
	.माला_लोockopt	= data_sock_माला_लोockopt,
	.connect	= sock_no_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.mmap		= sock_no_mmap
पूर्ण;

अटल पूर्णांक
data_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	अगर (sock->type != SOCK_DGRAM)
		वापस -ESOCKTNOSUPPORT;

	sk = sk_alloc(net, PF_ISDN, GFP_KERNEL, &mISDN_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);

	sock->ops = &data_sock_ops;
	sock->state = SS_UNCONNECTED;
	sock_reset_flag(sk, SOCK_ZAPPED);

	sk->sk_protocol = protocol;
	sk->sk_state    = MISDN_OPEN;
	mISDN_sock_link(&data_sockets, sk);

	वापस 0;
पूर्ण

अटल पूर्णांक
base_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	prपूर्णांकk(KERN_DEBUG "%s(%p) sk=%p\n", __func__, sock, sk);
	अगर (!sk)
		वापस 0;

	mISDN_sock_unlink(&base_sockets, sk);
	sock_orphan(sk);
	sock_put(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक
base_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक			err = 0, id;
	काष्ठा mISDNdevice	*dev;
	काष्ठा mISDNversion	ver;

	चयन (cmd) अणु
	हाल IMGETVERSION:
		ver.major = MISDN_MAJOR_VERSION;
		ver.minor = MISDN_MINOR_VERSION;
		ver.release = MISDN_RELEASE;
		अगर (copy_to_user((व्योम __user *)arg, &ver, माप(ver)))
			err = -EFAULT;
		अवरोध;
	हाल IMGETCOUNT:
		id = get_mdevice_count();
		अगर (put_user(id, (पूर्णांक __user *)arg))
			err = -EFAULT;
		अवरोध;
	हाल IMGETDEVINFO:
		अगर (get_user(id, (पूर्णांक __user *)arg)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		dev = get_mdevice(id);
		अगर (dev) अणु
			काष्ठा mISDN_devinfo di;

			स_रखो(&di, 0, माप(di));
			di.id = dev->id;
			di.Dprotocols = dev->Dprotocols;
			di.Bprotocols = dev->Bprotocols | get_all_Bprotocols();
			di.protocol = dev->D.protocol;
			स_नकल(di.channelmap, dev->channelmap,
			       माप(di.channelmap));
			di.nrbchan = dev->nrbchan;
			strscpy(di.name, dev_name(&dev->dev), माप(di.name));
			अगर (copy_to_user((व्योम __user *)arg, &di, माप(di)))
				err = -EFAULT;
		पूर्ण अन्यथा
			err = -ENODEV;
		अवरोध;
	हाल IMSETDEVNAME:
	अणु
		काष्ठा mISDN_devनाम dn;
		अगर (copy_from_user(&dn, (व्योम __user *)arg,
				   माप(dn))) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		dn.name[माप(dn.name) - 1] = '\0';
		dev = get_mdevice(dn.id);
		अगर (dev)
			err = device_नाम(&dev->dev, dn.name);
		अन्यथा
			err = -ENODEV;
	पूर्ण
	अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक
base_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *addr, पूर्णांक addr_len)
अणु
	काष्ठा sockaddr_mISDN *maddr = (काष्ठा sockaddr_mISDN *) addr;
	काष्ठा sock *sk = sock->sk;
	पूर्णांक err = 0;

	अगर (addr_len < माप(काष्ठा sockaddr_mISDN))
		वापस -EINVAL;

	अगर (!maddr || maddr->family != AF_ISDN)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (_pms(sk)->dev) अणु
		err = -EALREADY;
		जाओ करोne;
	पूर्ण

	_pms(sk)->dev = get_mdevice(maddr->dev);
	अगर (!_pms(sk)->dev) अणु
		err = -ENODEV;
		जाओ करोne;
	पूर्ण
	sk->sk_state = MISDN_BOUND;

करोne:
	release_sock(sk);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा proto_ops base_sock_ops = अणु
	.family		= PF_ISDN,
	.owner		= THIS_MODULE,
	.release	= base_sock_release,
	.ioctl		= base_sock_ioctl,
	.bind		= base_sock_bind,
	.getname	= sock_no_getname,
	.sendmsg	= sock_no_sendmsg,
	.recvmsg	= sock_no_recvmsg,
	.listen		= sock_no_listen,
	.shutकरोwn	= sock_no_shutकरोwn,
	.connect	= sock_no_connect,
	.socketpair	= sock_no_socketpair,
	.accept		= sock_no_accept,
	.mmap		= sock_no_mmap
पूर्ण;


अटल पूर्णांक
base_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा sock *sk;

	अगर (sock->type != SOCK_RAW)
		वापस -ESOCKTNOSUPPORT;
	अगर (!capable(CAP_NET_RAW))
		वापस -EPERM;

	sk = sk_alloc(net, PF_ISDN, GFP_KERNEL, &mISDN_proto, kern);
	अगर (!sk)
		वापस -ENOMEM;

	sock_init_data(sock, sk);
	sock->ops = &base_sock_ops;
	sock->state = SS_UNCONNECTED;
	sock_reset_flag(sk, SOCK_ZAPPED);
	sk->sk_protocol = protocol;
	sk->sk_state    = MISDN_OPEN;
	mISDN_sock_link(&base_sockets, sk);

	वापस 0;
पूर्ण

अटल पूर्णांक
mISDN_sock_create(काष्ठा net *net, काष्ठा socket *sock, पूर्णांक proto, पूर्णांक kern)
अणु
	पूर्णांक err = -EPROTONOSUPPORT;

	चयन (proto) अणु
	हाल ISDN_P_BASE:
		err = base_sock_create(net, sock, proto, kern);
		अवरोध;
	हाल ISDN_P_TE_S0:
	हाल ISDN_P_NT_S0:
	हाल ISDN_P_TE_E1:
	हाल ISDN_P_NT_E1:
	हाल ISDN_P_LAPD_TE:
	हाल ISDN_P_LAPD_NT:
	हाल ISDN_P_B_RAW:
	हाल ISDN_P_B_HDLC:
	हाल ISDN_P_B_X75SLP:
	हाल ISDN_P_B_L2DTMF:
	हाल ISDN_P_B_L2DSP:
	हाल ISDN_P_B_L2DSPHDLC:
		err = data_sock_create(net, sock, proto, kern);
		अवरोध;
	शेष:
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_proto_family mISDN_sock_family_ops = अणु
	.owner  = THIS_MODULE,
	.family = PF_ISDN,
	.create = mISDN_sock_create,
पूर्ण;

पूर्णांक
misdn_sock_init(u_पूर्णांक *deb)
अणु
	पूर्णांक err;

	debug = deb;
	err = sock_रेजिस्टर(&mISDN_sock_family_ops);
	अगर (err)
		prपूर्णांकk(KERN_ERR "%s: error(%d)\n", __func__, err);
	वापस err;
पूर्ण

व्योम
misdn_sock_cleanup(व्योम)
अणु
	sock_unरेजिस्टर(PF_ISDN);
पूर्ण
