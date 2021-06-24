<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * File: pep-gprs.c
 *
 * GPRS over Phonet pipe end poपूर्णांक socket
 *
 * Copyright (C) 2008 Nokia Corporation.
 *
 * Author: Rथऊmi Denis-Courmont
 */

#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/sock.h>

#समावेश <linux/अगर_phonet.h>
#समावेश <net/tcp_states.h>
#समावेश <net/phonet/gprs.h>

#घोषणा GPRS_DEFAULT_MTU 1400

काष्ठा gprs_dev अणु
	काष्ठा sock		*sk;
	व्योम			(*old_state_change)(काष्ठा sock *);
	व्योम			(*old_data_पढ़ोy)(काष्ठा sock *);
	व्योम			(*old_ग_लिखो_space)(काष्ठा sock *);

	काष्ठा net_device	*dev;
पूर्ण;

अटल __be16 gprs_type_trans(काष्ठा sk_buff *skb)
अणु
	स्थिर u8 *pvfc;
	u8 buf;

	pvfc = skb_header_poपूर्णांकer(skb, 0, 1, &buf);
	अगर (!pvfc)
		वापस htons(0);
	/* Look at IP version field */
	चयन (*pvfc >> 4) अणु
	हाल 4:
		वापस htons(ETH_P_IP);
	हाल 6:
		वापस htons(ETH_P_IPV6);
	पूर्ण
	वापस htons(0);
पूर्ण

अटल व्योम gprs_ग_लिखोable(काष्ठा gprs_dev *gp)
अणु
	काष्ठा net_device *dev = gp->dev;

	अगर (pep_ग_लिखोable(gp->sk))
		netअगर_wake_queue(dev);
पूर्ण

/*
 * Socket callbacks
 */

अटल व्योम gprs_state_change(काष्ठा sock *sk)
अणु
	काष्ठा gprs_dev *gp = sk->sk_user_data;

	अगर (sk->sk_state == TCP_CLOSE_WAIT) अणु
		काष्ठा net_device *dev = gp->dev;

		netअगर_stop_queue(dev);
		netअगर_carrier_off(dev);
	पूर्ण
पूर्ण

अटल पूर्णांक gprs_recv(काष्ठा gprs_dev *gp, काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = gp->dev;
	पूर्णांक err = 0;
	__be16 protocol = gprs_type_trans(skb);

	अगर (!protocol) अणु
		err = -EINVAL;
		जाओ drop;
	पूर्ण

	अगर (skb_headroom(skb) & 3) अणु
		काष्ठा sk_buff *rskb, *fs;
		पूर्णांक flen = 0;

		/* Phonet Pipe data header may be misaligned (3 bytes),
		 * so wrap the IP packet as a single fragment of an head-less
		 * socket buffer. The network stack will pull what it needs,
		 * but at least, the whole IP payload is not स_नकल'd. */
		rskb = netdev_alloc_skb(dev, 0);
		अगर (!rskb) अणु
			err = -ENOBUFS;
			जाओ drop;
		पूर्ण
		skb_shinfo(rskb)->frag_list = skb;
		rskb->len += skb->len;
		rskb->data_len += rskb->len;
		rskb->truesize += rskb->len;

		/* Aव्योम nested fragments */
		skb_walk_frags(skb, fs)
			flen += fs->len;
		skb->next = skb_shinfo(skb)->frag_list;
		skb_frag_list_init(skb);
		skb->len -= flen;
		skb->data_len -= flen;
		skb->truesize -= flen;

		skb = rskb;
	पूर्ण

	skb->protocol = protocol;
	skb_reset_mac_header(skb);
	skb->dev = dev;

	अगर (likely(dev->flags & IFF_UP)) अणु
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
		netअगर_rx(skb);
		skb = शून्य;
	पूर्ण अन्यथा
		err = -ENODEV;

drop:
	अगर (skb) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.rx_dropped++;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम gprs_data_पढ़ोy(काष्ठा sock *sk)
अणु
	काष्ठा gprs_dev *gp = sk->sk_user_data;
	काष्ठा sk_buff *skb;

	जबतक ((skb = pep_पढ़ो(sk)) != शून्य) अणु
		skb_orphan(skb);
		gprs_recv(gp, skb);
	पूर्ण
पूर्ण

अटल व्योम gprs_ग_लिखो_space(काष्ठा sock *sk)
अणु
	काष्ठा gprs_dev *gp = sk->sk_user_data;

	अगर (netअगर_running(gp->dev))
		gprs_ग_लिखोable(gp);
पूर्ण

/*
 * Network device callbacks
 */

अटल पूर्णांक gprs_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा gprs_dev *gp = netdev_priv(dev);

	gprs_ग_लिखोable(gp);
	वापस 0;
पूर्ण

अटल पूर्णांक gprs_बंद(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

अटल netdev_tx_t gprs_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा gprs_dev *gp = netdev_priv(dev);
	काष्ठा sock *sk = gp->sk;
	पूर्णांक len, err;

	चयन (skb->protocol) अणु
	हाल  htons(ETH_P_IP):
	हाल  htons(ETH_P_IPV6):
		अवरोध;
	शेष:
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	skb_orphan(skb);
	skb_set_owner_w(skb, sk);
	len = skb->len;
	err = pep_ग_लिखो(sk, skb);
	अगर (err) अणु
		net_dbg_ratelimited("%s: TX error (%d)\n", dev->name, err);
		dev->stats.tx_पातed_errors++;
		dev->stats.tx_errors++;
	पूर्ण अन्यथा अणु
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += len;
	पूर्ण

	netअगर_stop_queue(dev);
	अगर (pep_ग_लिखोable(sk))
		netअगर_wake_queue(dev);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops gprs_netdev_ops = अणु
	.nकरो_खोलो	= gprs_खोलो,
	.nकरो_stop	= gprs_बंद,
	.nकरो_start_xmit	= gprs_xmit,
पूर्ण;

अटल व्योम gprs_setup(काष्ठा net_device *dev)
अणु
	dev->features		= NETIF_F_FRAGLIST;
	dev->type		= ARPHRD_PHONET_PIPE;
	dev->flags		= IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu		= GPRS_DEFAULT_MTU;
	dev->min_mtu		= 576;
	dev->max_mtu		= (PHONET_MAX_MTU - 11);
	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 10;

	dev->netdev_ops		= &gprs_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
पूर्ण

/*
 * External पूर्णांकerface
 */

/*
 * Attach a GPRS पूर्णांकerface to a datagram socket.
 * Returns the पूर्णांकerface index on success, negative error code on error.
 */
पूर्णांक gprs_attach(काष्ठा sock *sk)
अणु
	अटल स्थिर अक्षर अगरname[] = "gprs%d";
	काष्ठा gprs_dev *gp;
	काष्ठा net_device *dev;
	पूर्णांक err;

	अगर (unlikely(sk->sk_type == SOCK_STREAM))
		वापस -EINVAL; /* need packet boundaries */

	/* Create net device */
	dev = alloc_netdev(माप(*gp), अगरname, NET_NAME_UNKNOWN, gprs_setup);
	अगर (!dev)
		वापस -ENOMEM;
	gp = netdev_priv(dev);
	gp->sk = sk;
	gp->dev = dev;

	netअगर_stop_queue(dev);
	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		मुक्त_netdev(dev);
		वापस err;
	पूर्ण

	lock_sock(sk);
	अगर (unlikely(sk->sk_user_data)) अणु
		err = -EBUSY;
		जाओ out_rel;
	पूर्ण
	अगर (unlikely((1 << sk->sk_state & (TCPF_CLOSE|TCPF_LISTEN)) ||
			sock_flag(sk, SOCK_DEAD))) अणु
		err = -EINVAL;
		जाओ out_rel;
	पूर्ण
	sk->sk_user_data	= gp;
	gp->old_state_change	= sk->sk_state_change;
	gp->old_data_पढ़ोy	= sk->sk_data_पढ़ोy;
	gp->old_ग_लिखो_space	= sk->sk_ग_लिखो_space;
	sk->sk_state_change	= gprs_state_change;
	sk->sk_data_पढ़ोy	= gprs_data_पढ़ोy;
	sk->sk_ग_लिखो_space	= gprs_ग_लिखो_space;
	release_sock(sk);
	sock_hold(sk);

	prपूर्णांकk(KERN_DEBUG"%s: attached\n", dev->name);
	वापस dev->अगरindex;

out_rel:
	release_sock(sk);
	unरेजिस्टर_netdev(dev);
	वापस err;
पूर्ण

व्योम gprs_detach(काष्ठा sock *sk)
अणु
	काष्ठा gprs_dev *gp = sk->sk_user_data;
	काष्ठा net_device *dev = gp->dev;

	lock_sock(sk);
	sk->sk_user_data	= शून्य;
	sk->sk_state_change	= gp->old_state_change;
	sk->sk_data_पढ़ोy	= gp->old_data_पढ़ोy;
	sk->sk_ग_लिखो_space	= gp->old_ग_लिखो_space;
	release_sock(sk);

	prपूर्णांकk(KERN_DEBUG"%s: detached\n", dev->name);
	unरेजिस्टर_netdev(dev);
	sock_put(sk);
पूर्ण
