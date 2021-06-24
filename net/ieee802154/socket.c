<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IEEE802154.4 socket पूर्णांकerface
 *
 * Copyright 2007, 2008 Siemens AG
 *
 * Written by:
 * Sergey Lapin <slapin@ossfans.org>
 * Maxim Gorbachyov <maxim.gorbachev@siemens.com>
 */

#समावेश <linux/net.h>
#समावेश <linux/capability.h>
#समावेश <linux/module.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर.h>
#समावेश <linux/termios.h>	/* For TIOCOUTQ/INQ */
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <net/datalink.h>
#समावेश <net/psnap.h>
#समावेश <net/sock.h>
#समावेश <net/tcp_states.h>
#समावेश <net/route.h>

#समावेश <net/af_ieee802154.h>
#समावेश <net/ieee802154_netdev.h>

/* Utility function क्रम families */
अटल काष्ठा net_device*
ieee802154_get_dev(काष्ठा net *net, स्थिर काष्ठा ieee802154_addr *addr)
अणु
	काष्ठा net_device *dev = शून्य;
	काष्ठा net_device *पंचांगp;
	__le16 pan_id, लघु_addr;
	u8 hwaddr[IEEE802154_ADDR_LEN];

	चयन (addr->mode) अणु
	हाल IEEE802154_ADDR_LONG:
		ieee802154_devaddr_to_raw(hwaddr, addr->extended_addr);
		rcu_पढ़ो_lock();
		dev = dev_getbyhwaddr_rcu(net, ARPHRD_IEEE802154, hwaddr);
		अगर (dev)
			dev_hold(dev);
		rcu_पढ़ो_unlock();
		अवरोध;
	हाल IEEE802154_ADDR_SHORT:
		अगर (addr->pan_id == cpu_to_le16(IEEE802154_PANID_BROADCAST) ||
		    addr->लघु_addr == cpu_to_le16(IEEE802154_ADDR_UNDEF) ||
		    addr->लघु_addr == cpu_to_le16(IEEE802154_ADDR_BROADCAST))
			अवरोध;

		rtnl_lock();

		क्रम_each_netdev(net, पंचांगp) अणु
			अगर (पंचांगp->type != ARPHRD_IEEE802154)
				जारी;

			pan_id = पंचांगp->ieee802154_ptr->pan_id;
			लघु_addr = पंचांगp->ieee802154_ptr->लघु_addr;
			अगर (pan_id == addr->pan_id &&
			    लघु_addr == addr->लघु_addr) अणु
				dev = पंचांगp;
				dev_hold(dev);
				अवरोध;
			पूर्ण
		पूर्ण

		rtnl_unlock();
		अवरोध;
	शेष:
		pr_warn("Unsupported ieee802154 address type: %d\n",
			addr->mode);
		अवरोध;
	पूर्ण

	वापस dev;
पूर्ण

अटल पूर्णांक ieee802154_sock_release(काष्ठा socket *sock)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk) अणु
		sock->sk = शून्य;
		sk->sk_prot->बंद(sk, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ieee802154_sock_sendmsg(काष्ठा socket *sock, काष्ठा msghdr *msg,
				   माप_प्रकार len)
अणु
	काष्ठा sock *sk = sock->sk;

	वापस sk->sk_prot->sendmsg(sk, msg, len);
पूर्ण

अटल पूर्णांक ieee802154_sock_bind(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
				पूर्णांक addr_len)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (sk->sk_prot->bind)
		वापस sk->sk_prot->bind(sk, uaddr, addr_len);

	वापस sock_no_bind(sock, uaddr, addr_len);
पूर्ण

अटल पूर्णांक ieee802154_sock_connect(काष्ठा socket *sock, काष्ठा sockaddr *uaddr,
				   पूर्णांक addr_len, पूर्णांक flags)
अणु
	काष्ठा sock *sk = sock->sk;

	अगर (addr_len < माप(uaddr->sa_family))
		वापस -EINVAL;

	अगर (uaddr->sa_family == AF_UNSPEC)
		वापस sk->sk_prot->disconnect(sk, flags);

	वापस sk->sk_prot->connect(sk, uaddr, addr_len);
पूर्ण

अटल पूर्णांक ieee802154_dev_ioctl(काष्ठा sock *sk, काष्ठा अगरreq __user *arg,
				अचिन्हित पूर्णांक cmd)
अणु
	काष्ठा अगरreq अगरr;
	पूर्णांक ret = -ENOIOCTLCMD;
	काष्ठा net_device *dev;

	अगर (copy_from_user(&अगरr, arg, माप(काष्ठा अगरreq)))
		वापस -EFAULT;

	अगरr.अगरr_name[IFNAMSIZ-1] = 0;

	dev_load(sock_net(sk), अगरr.अगरr_name);
	dev = dev_get_by_name(sock_net(sk), अगरr.अगरr_name);

	अगर (!dev)
		वापस -ENODEV;

	अगर (dev->type == ARPHRD_IEEE802154 && dev->netdev_ops->nकरो_करो_ioctl)
		ret = dev->netdev_ops->nकरो_करो_ioctl(dev, &अगरr, cmd);

	अगर (!ret && copy_to_user(arg, &अगरr, माप(काष्ठा अगरreq)))
		ret = -EFAULT;
	dev_put(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee802154_sock_ioctl(काष्ठा socket *sock, अचिन्हित पूर्णांक cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा sock *sk = sock->sk;

	चयन (cmd) अणु
	हाल SIOCGIFADDR:
	हाल SIOCSIFADDR:
		वापस ieee802154_dev_ioctl(sk, (काष्ठा अगरreq __user *)arg,
				cmd);
	शेष:
		अगर (!sk->sk_prot->ioctl)
			वापस -ENOIOCTLCMD;
		वापस sk->sk_prot->ioctl(sk, cmd, arg);
	पूर्ण
पूर्ण

/* RAW Sockets (802.15.4 created in userspace) */
अटल HLIST_HEAD(raw_head);
अटल DEFINE_RWLOCK(raw_lock);

अटल पूर्णांक raw_hash(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&raw_lock);
	sk_add_node(sk, &raw_head);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	ग_लिखो_unlock_bh(&raw_lock);

	वापस 0;
पूर्ण

अटल व्योम raw_unhash(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&raw_lock);
	अगर (sk_del_node_init(sk))
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	ग_लिखो_unlock_bh(&raw_lock);
पूर्ण

अटल व्योम raw_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	sk_common_release(sk);
पूर्ण

अटल पूर्णांक raw_bind(काष्ठा sock *sk, काष्ठा sockaddr *_uaddr, पूर्णांक len)
अणु
	काष्ठा ieee802154_addr addr;
	काष्ठा sockaddr_ieee802154 *uaddr = (काष्ठा sockaddr_ieee802154 *)_uaddr;
	पूर्णांक err = 0;
	काष्ठा net_device *dev = शून्य;

	अगर (len < माप(*uaddr))
		वापस -EINVAL;

	uaddr = (काष्ठा sockaddr_ieee802154 *)_uaddr;
	अगर (uaddr->family != AF_IEEE802154)
		वापस -EINVAL;

	lock_sock(sk);

	ieee802154_addr_from_sa(&addr, &uaddr->addr);
	dev = ieee802154_get_dev(sock_net(sk), &addr);
	अगर (!dev) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	sk->sk_bound_dev_अगर = dev->अगरindex;
	sk_dst_reset(sk);

	dev_put(dev);
out:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक raw_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
		       पूर्णांक addr_len)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक raw_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक raw_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक mtu;
	काष्ठा sk_buff *skb;
	पूर्णांक hlen, tlen;
	पूर्णांक err;

	अगर (msg->msg_flags & MSG_OOB) अणु
		pr_debug("msg->msg_flags = 0x%x\n", msg->msg_flags);
		वापस -EOPNOTSUPP;
	पूर्ण

	lock_sock(sk);
	अगर (!sk->sk_bound_dev_अगर)
		dev = dev_getfirstbyhwtype(sock_net(sk), ARPHRD_IEEE802154);
	अन्यथा
		dev = dev_get_by_index(sock_net(sk), sk->sk_bound_dev_अगर);
	release_sock(sk);

	अगर (!dev) अणु
		pr_debug("no dev\n");
		err = -ENXIO;
		जाओ out;
	पूर्ण

	mtu = IEEE802154_MTU;
	pr_debug("name = %s, mtu = %u\n", dev->name, mtu);

	अगर (size > mtu) अणु
		pr_debug("size = %zu, mtu = %u\n", size, mtu);
		err = -EMSGSIZE;
		जाओ out_dev;
	पूर्ण

	hlen = LL_RESERVED_SPACE(dev);
	tlen = dev->needed_tailroom;
	skb = sock_alloc_send_skb(sk, hlen + tlen + size,
				  msg->msg_flags & MSG_DONTWAIT, &err);
	अगर (!skb)
		जाओ out_dev;

	skb_reserve(skb, hlen);

	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);

	err = स_नकल_from_msg(skb_put(skb, size), msg, size);
	अगर (err < 0)
		जाओ out_skb;

	skb->dev = dev;
	skb->protocol = htons(ETH_P_IEEE802154);

	err = dev_queue_xmit(skb);
	अगर (err > 0)
		err = net_xmit_त्रुटि_सं(err);

	dev_put(dev);

	वापस err ?: size;

out_skb:
	kमुक्त_skb(skb);
out_dev:
	dev_put(dev);
out:
	वापस err;
पूर्ण

अटल पूर्णांक raw_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
		       पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	माप_प्रकार copied = 0;
	पूर्णांक err = -EOPNOTSUPP;
	काष्ठा sk_buff *skb;

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ करोne;

	sock_recv_ts_and_drops(msg, sk, skb);

	अगर (flags & MSG_TRUNC)
		copied = skb->len;
करोne:
	skb_मुक्त_datagram(sk, skb);
out:
	अगर (err)
		वापस err;
	वापस copied;
पूर्ण

अटल पूर्णांक raw_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_RX_DROP;

	अगर (sock_queue_rcv_skb(sk, skb) < 0) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	वापस NET_RX_SUCCESS;
पूर्ण

अटल व्योम ieee802154_raw_deliver(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk;

	पढ़ो_lock(&raw_lock);
	sk_क्रम_each(sk, &raw_head) अणु
		bh_lock_sock(sk);
		अगर (!sk->sk_bound_dev_अगर ||
		    sk->sk_bound_dev_अगर == dev->अगरindex) अणु
			काष्ठा sk_buff *clone;

			clone = skb_clone(skb, GFP_ATOMIC);
			अगर (clone)
				raw_rcv_skb(sk, clone);
		पूर्ण
		bh_unlock_sock(sk);
	पूर्ण
	पढ़ो_unlock(&raw_lock);
पूर्ण

अटल पूर्णांक raw_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक raw_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			  sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल काष्ठा proto ieee802154_raw_prot = अणु
	.name		= "IEEE-802.15.4-RAW",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा sock),
	.बंद		= raw_बंद,
	.bind		= raw_bind,
	.sendmsg	= raw_sendmsg,
	.recvmsg	= raw_recvmsg,
	.hash		= raw_hash,
	.unhash		= raw_unhash,
	.connect	= raw_connect,
	.disconnect	= raw_disconnect,
	.माला_लोockopt	= raw_माला_लोockopt,
	.setsockopt	= raw_setsockopt,
पूर्ण;

अटल स्थिर काष्ठा proto_ops ieee802154_raw_ops = अणु
	.family		   = PF_IEEE802154,
	.owner		   = THIS_MODULE,
	.release	   = ieee802154_sock_release,
	.bind		   = ieee802154_sock_bind,
	.connect	   = ieee802154_sock_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = sock_no_accept,
	.getname	   = sock_no_getname,
	.poll		   = datagram_poll,
	.ioctl		   = ieee802154_sock_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,
	.shutकरोwn	   = sock_no_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = ieee802154_sock_sendmsg,
	.recvmsg	   = sock_common_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
पूर्ण;

/* DGRAM Sockets (802.15.4 dataframes) */
अटल HLIST_HEAD(dgram_head);
अटल DEFINE_RWLOCK(dgram_lock);

काष्ठा dgram_sock अणु
	काष्ठा sock sk;

	काष्ठा ieee802154_addr src_addr;
	काष्ठा ieee802154_addr dst_addr;

	अचिन्हित पूर्णांक bound:1;
	अचिन्हित पूर्णांक connected:1;
	अचिन्हित पूर्णांक want_ack:1;
	अचिन्हित पूर्णांक want_lqi:1;
	अचिन्हित पूर्णांक secen:1;
	अचिन्हित पूर्णांक secen_override:1;
	अचिन्हित पूर्णांक seclevel:3;
	अचिन्हित पूर्णांक seclevel_override:1;
पूर्ण;

अटल अंतरभूत काष्ठा dgram_sock *dgram_sk(स्थिर काष्ठा sock *sk)
अणु
	वापस container_of(sk, काष्ठा dgram_sock, sk);
पूर्ण

अटल पूर्णांक dgram_hash(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&dgram_lock);
	sk_add_node(sk, &dgram_head);
	sock_prot_inuse_add(sock_net(sk), sk->sk_prot, 1);
	ग_लिखो_unlock_bh(&dgram_lock);

	वापस 0;
पूर्ण

अटल व्योम dgram_unhash(काष्ठा sock *sk)
अणु
	ग_लिखो_lock_bh(&dgram_lock);
	अगर (sk_del_node_init(sk))
		sock_prot_inuse_add(sock_net(sk), sk->sk_prot, -1);
	ग_लिखो_unlock_bh(&dgram_lock);
पूर्ण

अटल पूर्णांक dgram_init(काष्ठा sock *sk)
अणु
	काष्ठा dgram_sock *ro = dgram_sk(sk);

	ro->want_ack = 1;
	ro->want_lqi = 0;
	वापस 0;
पूर्ण

अटल व्योम dgram_बंद(काष्ठा sock *sk, दीर्घ समयout)
अणु
	sk_common_release(sk);
पूर्ण

अटल पूर्णांक dgram_bind(काष्ठा sock *sk, काष्ठा sockaddr *uaddr, पूर्णांक len)
अणु
	काष्ठा sockaddr_ieee802154 *addr = (काष्ठा sockaddr_ieee802154 *)uaddr;
	काष्ठा ieee802154_addr haddr;
	काष्ठा dgram_sock *ro = dgram_sk(sk);
	पूर्णांक err = -EINVAL;
	काष्ठा net_device *dev;

	lock_sock(sk);

	ro->bound = 0;

	अगर (len < माप(*addr))
		जाओ out;

	अगर (addr->family != AF_IEEE802154)
		जाओ out;

	ieee802154_addr_from_sa(&haddr, &addr->addr);
	dev = ieee802154_get_dev(sock_net(sk), &haddr);
	अगर (!dev) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (dev->type != ARPHRD_IEEE802154) अणु
		err = -ENODEV;
		जाओ out_put;
	पूर्ण

	ro->src_addr = haddr;

	ro->bound = 1;
	err = 0;
out_put:
	dev_put(dev);
out:
	release_sock(sk);

	वापस err;
पूर्ण

अटल पूर्णांक dgram_ioctl(काष्ठा sock *sk, पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	चयन (cmd) अणु
	हाल SIOCOUTQ:
	अणु
		पूर्णांक amount = sk_wmem_alloc_get(sk);

		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण

	हाल SIOCINQ:
	अणु
		काष्ठा sk_buff *skb;
		अचिन्हित दीर्घ amount;

		amount = 0;
		spin_lock_bh(&sk->sk_receive_queue.lock);
		skb = skb_peek(&sk->sk_receive_queue);
		अगर (skb) अणु
			/* We will only वापस the amount
			 * of this packet since that is all
			 * that will be पढ़ो.
			 */
			amount = skb->len - ieee802154_hdr_length(skb);
		पूर्ण
		spin_unlock_bh(&sk->sk_receive_queue.lock);
		वापस put_user(amount, (पूर्णांक __user *)arg);
	पूर्ण
	पूर्ण

	वापस -ENOIOCTLCMD;
पूर्ण

/* FIXME: स्वतःbind */
अटल पूर्णांक dgram_connect(काष्ठा sock *sk, काष्ठा sockaddr *uaddr,
			 पूर्णांक len)
अणु
	काष्ठा sockaddr_ieee802154 *addr = (काष्ठा sockaddr_ieee802154 *)uaddr;
	काष्ठा dgram_sock *ro = dgram_sk(sk);
	पूर्णांक err = 0;

	अगर (len < माप(*addr))
		वापस -EINVAL;

	अगर (addr->family != AF_IEEE802154)
		वापस -EINVAL;

	lock_sock(sk);

	अगर (!ro->bound) अणु
		err = -ENETUNREACH;
		जाओ out;
	पूर्ण

	ieee802154_addr_from_sa(&ro->dst_addr, &addr->addr);
	ro->connected = 1;

out:
	release_sock(sk);
	वापस err;
पूर्ण

अटल पूर्णांक dgram_disconnect(काष्ठा sock *sk, पूर्णांक flags)
अणु
	काष्ठा dgram_sock *ro = dgram_sk(sk);

	lock_sock(sk);
	ro->connected = 0;
	release_sock(sk);

	वापस 0;
पूर्ण

अटल पूर्णांक dgram_sendmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार size)
अणु
	काष्ठा net_device *dev;
	अचिन्हित पूर्णांक mtu;
	काष्ठा sk_buff *skb;
	काष्ठा ieee802154_mac_cb *cb;
	काष्ठा dgram_sock *ro = dgram_sk(sk);
	काष्ठा ieee802154_addr dst_addr;
	पूर्णांक hlen, tlen;
	पूर्णांक err;

	अगर (msg->msg_flags & MSG_OOB) अणु
		pr_debug("msg->msg_flags = 0x%x\n", msg->msg_flags);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!ro->connected && !msg->msg_name)
		वापस -EDESTADDRREQ;
	अन्यथा अगर (ro->connected && msg->msg_name)
		वापस -EISCONN;

	अगर (!ro->bound)
		dev = dev_getfirstbyhwtype(sock_net(sk), ARPHRD_IEEE802154);
	अन्यथा
		dev = ieee802154_get_dev(sock_net(sk), &ro->src_addr);

	अगर (!dev) अणु
		pr_debug("no dev\n");
		err = -ENXIO;
		जाओ out;
	पूर्ण
	mtu = IEEE802154_MTU;
	pr_debug("name = %s, mtu = %u\n", dev->name, mtu);

	अगर (size > mtu) अणु
		pr_debug("size = %zu, mtu = %u\n", size, mtu);
		err = -EMSGSIZE;
		जाओ out_dev;
	पूर्ण

	hlen = LL_RESERVED_SPACE(dev);
	tlen = dev->needed_tailroom;
	skb = sock_alloc_send_skb(sk, hlen + tlen + size,
				  msg->msg_flags & MSG_DONTWAIT,
				  &err);
	अगर (!skb)
		जाओ out_dev;

	skb_reserve(skb, hlen);

	skb_reset_network_header(skb);

	cb = mac_cb_init(skb);
	cb->type = IEEE802154_FC_TYPE_DATA;
	cb->ackreq = ro->want_ack;

	अगर (msg->msg_name) अणु
		DECLARE_SOCKADDR(काष्ठा sockaddr_ieee802154*,
				 daddr, msg->msg_name);

		ieee802154_addr_from_sa(&dst_addr, &daddr->addr);
	पूर्ण अन्यथा अणु
		dst_addr = ro->dst_addr;
	पूर्ण

	cb->secen = ro->secen;
	cb->secen_override = ro->secen_override;
	cb->seclevel = ro->seclevel;
	cb->seclevel_override = ro->seclevel_override;

	err = wpan_dev_hard_header(skb, dev, &dst_addr,
				   ro->bound ? &ro->src_addr : शून्य, size);
	अगर (err < 0)
		जाओ out_skb;

	err = स_नकल_from_msg(skb_put(skb, size), msg, size);
	अगर (err < 0)
		जाओ out_skb;

	skb->dev = dev;
	skb->protocol = htons(ETH_P_IEEE802154);

	err = dev_queue_xmit(skb);
	अगर (err > 0)
		err = net_xmit_त्रुटि_सं(err);

	dev_put(dev);

	वापस err ?: size;

out_skb:
	kमुक्त_skb(skb);
out_dev:
	dev_put(dev);
out:
	वापस err;
पूर्ण

अटल पूर्णांक dgram_recvmsg(काष्ठा sock *sk, काष्ठा msghdr *msg, माप_प्रकार len,
			 पूर्णांक noblock, पूर्णांक flags, पूर्णांक *addr_len)
अणु
	माप_प्रकार copied = 0;
	पूर्णांक err = -EOPNOTSUPP;
	काष्ठा sk_buff *skb;
	काष्ठा dgram_sock *ro = dgram_sk(sk);
	DECLARE_SOCKADDR(काष्ठा sockaddr_ieee802154 *, saddr, msg->msg_name);

	skb = skb_recv_datagram(sk, flags, noblock, &err);
	अगर (!skb)
		जाओ out;

	copied = skb->len;
	अगर (len < copied) अणु
		msg->msg_flags |= MSG_TRUNC;
		copied = len;
	पूर्ण

	/* FIXME: skip headers अगर necessary ?! */
	err = skb_copy_datagram_msg(skb, 0, msg, copied);
	अगर (err)
		जाओ करोne;

	sock_recv_ts_and_drops(msg, sk, skb);

	अगर (saddr) अणु
		/* Clear the implicit padding in काष्ठा sockaddr_ieee802154
		 * (16 bits between 'family' and 'addr') and in काष्ठा
		 * ieee802154_addr_sa (16 bits at the end of the काष्ठाure).
		 */
		स_रखो(saddr, 0, माप(*saddr));

		saddr->family = AF_IEEE802154;
		ieee802154_addr_to_sa(&saddr->addr, &mac_cb(skb)->source);
		*addr_len = माप(*saddr);
	पूर्ण

	अगर (ro->want_lqi) अणु
		err = put_cmsg(msg, SOL_IEEE802154, WPAN_WANTLQI,
			       माप(uपूर्णांक8_t), &(mac_cb(skb)->lqi));
		अगर (err)
			जाओ करोne;
	पूर्ण

	अगर (flags & MSG_TRUNC)
		copied = skb->len;
करोne:
	skb_मुक्त_datagram(sk, skb);
out:
	अगर (err)
		वापस err;
	वापस copied;
पूर्ण

अटल पूर्णांक dgram_rcv_skb(काष्ठा sock *sk, काष्ठा sk_buff *skb)
अणु
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_RX_DROP;

	अगर (sock_queue_rcv_skb(sk, skb) < 0) अणु
		kमुक्त_skb(skb);
		वापस NET_RX_DROP;
	पूर्ण

	वापस NET_RX_SUCCESS;
पूर्ण

अटल अंतरभूत bool
ieee802154_match_sock(__le64 hw_addr, __le16 pan_id, __le16 लघु_addr,
		      काष्ठा dgram_sock *ro)
अणु
	अगर (!ro->bound)
		वापस true;

	अगर (ro->src_addr.mode == IEEE802154_ADDR_LONG &&
	    hw_addr == ro->src_addr.extended_addr)
		वापस true;

	अगर (ro->src_addr.mode == IEEE802154_ADDR_SHORT &&
	    pan_id == ro->src_addr.pan_id &&
	    लघु_addr == ro->src_addr.लघु_addr)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक ieee802154_dgram_deliver(काष्ठा net_device *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा sock *sk, *prev = शून्य;
	पूर्णांक ret = NET_RX_SUCCESS;
	__le16 pan_id, लघु_addr;
	__le64 hw_addr;

	/* Data frame processing */
	BUG_ON(dev->type != ARPHRD_IEEE802154);

	pan_id = dev->ieee802154_ptr->pan_id;
	लघु_addr = dev->ieee802154_ptr->लघु_addr;
	hw_addr = dev->ieee802154_ptr->extended_addr;

	पढ़ो_lock(&dgram_lock);
	sk_क्रम_each(sk, &dgram_head) अणु
		अगर (ieee802154_match_sock(hw_addr, pan_id, लघु_addr,
					  dgram_sk(sk))) अणु
			अगर (prev) अणु
				काष्ठा sk_buff *clone;

				clone = skb_clone(skb, GFP_ATOMIC);
				अगर (clone)
					dgram_rcv_skb(prev, clone);
			पूर्ण

			prev = sk;
		पूर्ण
	पूर्ण

	अगर (prev) अणु
		dgram_rcv_skb(prev, skb);
	पूर्ण अन्यथा अणु
		kमुक्त_skb(skb);
		ret = NET_RX_DROP;
	पूर्ण
	पढ़ो_unlock(&dgram_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक dgram_माला_लोockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			    अक्षर __user *optval, पूर्णांक __user *optlen)
अणु
	काष्ठा dgram_sock *ro = dgram_sk(sk);

	पूर्णांक val, len;

	अगर (level != SOL_IEEE802154)
		वापस -EOPNOTSUPP;

	अगर (get_user(len, optlen))
		वापस -EFAULT;

	len = min_t(अचिन्हित पूर्णांक, len, माप(पूर्णांक));

	चयन (optname) अणु
	हाल WPAN_WANTACK:
		val = ro->want_ack;
		अवरोध;
	हाल WPAN_WANTLQI:
		val = ro->want_lqi;
		अवरोध;
	हाल WPAN_SECURITY:
		अगर (!ro->secen_override)
			val = WPAN_SECURITY_DEFAULT;
		अन्यथा अगर (ro->secen)
			val = WPAN_SECURITY_ON;
		अन्यथा
			val = WPAN_SECURITY_OFF;
		अवरोध;
	हाल WPAN_SECURITY_LEVEL:
		अगर (!ro->seclevel_override)
			val = WPAN_SECURITY_LEVEL_DEFAULT;
		अन्यथा
			val = ro->seclevel;
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

अटल पूर्णांक dgram_setsockopt(काष्ठा sock *sk, पूर्णांक level, पूर्णांक optname,
			    sockptr_t optval, अचिन्हित पूर्णांक optlen)
अणु
	काष्ठा dgram_sock *ro = dgram_sk(sk);
	काष्ठा net *net = sock_net(sk);
	पूर्णांक val;
	पूर्णांक err = 0;

	अगर (optlen < माप(पूर्णांक))
		वापस -EINVAL;

	अगर (copy_from_sockptr(&val, optval, माप(पूर्णांक)))
		वापस -EFAULT;

	lock_sock(sk);

	चयन (optname) अणु
	हाल WPAN_WANTACK:
		ro->want_ack = !!val;
		अवरोध;
	हाल WPAN_WANTLQI:
		ro->want_lqi = !!val;
		अवरोध;
	हाल WPAN_SECURITY:
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN) &&
		    !ns_capable(net->user_ns, CAP_NET_RAW)) अणु
			err = -EPERM;
			अवरोध;
		पूर्ण

		चयन (val) अणु
		हाल WPAN_SECURITY_DEFAULT:
			ro->secen_override = 0;
			अवरोध;
		हाल WPAN_SECURITY_ON:
			ro->secen_override = 1;
			ro->secen = 1;
			अवरोध;
		हाल WPAN_SECURITY_OFF:
			ro->secen_override = 1;
			ro->secen = 0;
			अवरोध;
		शेष:
			err = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल WPAN_SECURITY_LEVEL:
		अगर (!ns_capable(net->user_ns, CAP_NET_ADMIN) &&
		    !ns_capable(net->user_ns, CAP_NET_RAW)) अणु
			err = -EPERM;
			अवरोध;
		पूर्ण

		अगर (val < WPAN_SECURITY_LEVEL_DEFAULT ||
		    val > IEEE802154_SCF_SECLEVEL_ENC_MIC128) अणु
			err = -EINVAL;
		पूर्ण अन्यथा अगर (val == WPAN_SECURITY_LEVEL_DEFAULT) अणु
			ro->seclevel_override = 0;
		पूर्ण अन्यथा अणु
			ro->seclevel_override = 1;
			ro->seclevel = val;
		पूर्ण
		अवरोध;
	शेष:
		err = -ENOPROTOOPT;
		अवरोध;
	पूर्ण

	release_sock(sk);
	वापस err;
पूर्ण

अटल काष्ठा proto ieee802154_dgram_prot = अणु
	.name		= "IEEE-802.15.4-MAC",
	.owner		= THIS_MODULE,
	.obj_size	= माप(काष्ठा dgram_sock),
	.init		= dgram_init,
	.बंद		= dgram_बंद,
	.bind		= dgram_bind,
	.sendmsg	= dgram_sendmsg,
	.recvmsg	= dgram_recvmsg,
	.hash		= dgram_hash,
	.unhash		= dgram_unhash,
	.connect	= dgram_connect,
	.disconnect	= dgram_disconnect,
	.ioctl		= dgram_ioctl,
	.माला_लोockopt	= dgram_माला_लोockopt,
	.setsockopt	= dgram_setsockopt,
पूर्ण;

अटल स्थिर काष्ठा proto_ops ieee802154_dgram_ops = अणु
	.family		   = PF_IEEE802154,
	.owner		   = THIS_MODULE,
	.release	   = ieee802154_sock_release,
	.bind		   = ieee802154_sock_bind,
	.connect	   = ieee802154_sock_connect,
	.socketpair	   = sock_no_socketpair,
	.accept		   = sock_no_accept,
	.getname	   = sock_no_getname,
	.poll		   = datagram_poll,
	.ioctl		   = ieee802154_sock_ioctl,
	.gettstamp	   = sock_gettstamp,
	.listen		   = sock_no_listen,
	.shutकरोwn	   = sock_no_shutकरोwn,
	.setsockopt	   = sock_common_setsockopt,
	.माला_लोockopt	   = sock_common_माला_लोockopt,
	.sendmsg	   = ieee802154_sock_sendmsg,
	.recvmsg	   = sock_common_recvmsg,
	.mmap		   = sock_no_mmap,
	.sendpage	   = sock_no_sendpage,
पूर्ण;

/* Create a socket. Initialise the socket, blank the addresses
 * set the state.
 */
अटल पूर्णांक ieee802154_create(काष्ठा net *net, काष्ठा socket *sock,
			     पूर्णांक protocol, पूर्णांक kern)
अणु
	काष्ठा sock *sk;
	पूर्णांक rc;
	काष्ठा proto *proto;
	स्थिर काष्ठा proto_ops *ops;

	अगर (!net_eq(net, &init_net))
		वापस -EAFNOSUPPORT;

	चयन (sock->type) अणु
	हाल SOCK_RAW:
		rc = -EPERM;
		अगर (!capable(CAP_NET_RAW))
			जाओ out;
		proto = &ieee802154_raw_prot;
		ops = &ieee802154_raw_ops;
		अवरोध;
	हाल SOCK_DGRAM:
		proto = &ieee802154_dgram_prot;
		ops = &ieee802154_dgram_ops;
		अवरोध;
	शेष:
		rc = -ESOCKTNOSUPPORT;
		जाओ out;
	पूर्ण

	rc = -ENOMEM;
	sk = sk_alloc(net, PF_IEEE802154, GFP_KERNEL, proto, kern);
	अगर (!sk)
		जाओ out;
	rc = 0;

	sock->ops = ops;

	sock_init_data(sock, sk);
	/* FIXME: sk->sk_deकाष्ठा */
	sk->sk_family = PF_IEEE802154;

	/* Checksums on by शेष */
	sock_set_flag(sk, SOCK_ZAPPED);

	अगर (sk->sk_prot->hash) अणु
		rc = sk->sk_prot->hash(sk);
		अगर (rc) अणु
			sk_common_release(sk);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (sk->sk_prot->init) अणु
		rc = sk->sk_prot->init(sk);
		अगर (rc)
			sk_common_release(sk);
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा net_proto_family ieee802154_family_ops = अणु
	.family		= PF_IEEE802154,
	.create		= ieee802154_create,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक ieee802154_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			  काष्ठा packet_type *pt, काष्ठा net_device *orig_dev)
अणु
	अगर (!netअगर_running(dev))
		जाओ drop;
	pr_debug("got frame, type %d, dev %p\n", dev->type, dev);
#अगर_घोषित DEBUG
	prपूर्णांक_hex_dump_bytes("ieee802154_rcv ",
			     DUMP_PREFIX_NONE, skb->data, skb->len);
#पूर्ण_अगर

	अगर (!net_eq(dev_net(dev), &init_net))
		जाओ drop;

	ieee802154_raw_deliver(dev, skb);

	अगर (dev->type != ARPHRD_IEEE802154)
		जाओ drop;

	अगर (skb->pkt_type != PACKET_OTHERHOST)
		वापस ieee802154_dgram_deliver(dev, skb);

drop:
	kमुक्त_skb(skb);
	वापस NET_RX_DROP;
पूर्ण

अटल काष्ठा packet_type ieee802154_packet_type = अणु
	.type = htons(ETH_P_IEEE802154),
	.func = ieee802154_rcv,
पूर्ण;

अटल पूर्णांक __init af_ieee802154_init(व्योम)
अणु
	पूर्णांक rc;

	rc = proto_रेजिस्टर(&ieee802154_raw_prot, 1);
	अगर (rc)
		जाओ out;

	rc = proto_रेजिस्टर(&ieee802154_dgram_prot, 1);
	अगर (rc)
		जाओ err_dgram;

	/* Tell SOCKET that we are alive */
	rc = sock_रेजिस्टर(&ieee802154_family_ops);
	अगर (rc)
		जाओ err_sock;
	dev_add_pack(&ieee802154_packet_type);

	rc = 0;
	जाओ out;

err_sock:
	proto_unरेजिस्टर(&ieee802154_dgram_prot);
err_dgram:
	proto_unरेजिस्टर(&ieee802154_raw_prot);
out:
	वापस rc;
पूर्ण

अटल व्योम __निकास af_ieee802154_हटाओ(व्योम)
अणु
	dev_हटाओ_pack(&ieee802154_packet_type);
	sock_unरेजिस्टर(PF_IEEE802154);
	proto_unरेजिस्टर(&ieee802154_dgram_prot);
	proto_unरेजिस्टर(&ieee802154_raw_prot);
पूर्ण

module_init(af_ieee802154_init);
module_निकास(af_ieee802154_हटाओ);

MODULE_LICENSE("GPL");
MODULE_ALIAS_NETPROTO(PF_IEEE802154);
