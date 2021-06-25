<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* L2TPv3 ethernet pseuकरोwire driver
 *
 * Copyright (c) 2008,2009,2010 Katalix Systems Ltd
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/socket.h>
#समावेश <linux/hash.h>
#समावेश <linux/l2tp.h>
#समावेश <linux/in.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/spinlock.h>
#समावेश <net/sock.h>
#समावेश <net/ip.h>
#समावेश <net/icmp.h>
#समावेश <net/udp.h>
#समावेश <net/inet_common.h>
#समावेश <net/inet_hashtables.h>
#समावेश <net/tcp_states.h>
#समावेश <net/protocol.h>
#समावेश <net/xfrm.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/udp.h>

#समावेश "l2tp_core.h"

/* Default device name. May be overridden by name specअगरied by user */
#घोषणा L2TP_ETH_DEV_NAME	"l2tpeth%d"

/* via netdev_priv() */
काष्ठा l2tp_eth अणु
	काष्ठा l2tp_session	*session;
	atomic_दीर्घ_t		tx_bytes;
	atomic_दीर्घ_t		tx_packets;
	atomic_दीर्घ_t		tx_dropped;
	atomic_दीर्घ_t		rx_bytes;
	atomic_दीर्घ_t		rx_packets;
	atomic_दीर्घ_t		rx_errors;
पूर्ण;

/* via l2tp_session_priv() */
काष्ठा l2tp_eth_sess अणु
	काष्ठा net_device __rcu *dev;
पूर्ण;

अटल पूर्णांक l2tp_eth_dev_init(काष्ठा net_device *dev)
अणु
	eth_hw_addr_अक्रमom(dev);
	eth_broadcast_addr(dev->broadcast);
	netdev_lockdep_set_classes(dev);

	वापस 0;
पूर्ण

अटल व्योम l2tp_eth_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा l2tp_eth *priv = netdev_priv(dev);
	काष्ठा l2tp_eth_sess *spriv;

	spriv = l2tp_session_priv(priv->session);
	RCU_INIT_POINTER(spriv->dev, शून्य);
	/* No need क्रम synchronize_net() here. We're called by
	 * unरेजिस्टर_netdev*(), which करोes the synchronisation क्रम us.
	 */
पूर्ण

अटल netdev_tx_t l2tp_eth_dev_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा l2tp_eth *priv = netdev_priv(dev);
	काष्ठा l2tp_session *session = priv->session;
	अचिन्हित पूर्णांक len = skb->len;
	पूर्णांक ret = l2tp_xmit_skb(session, skb);

	अगर (likely(ret == NET_XMIT_SUCCESS)) अणु
		atomic_दीर्घ_add(len, &priv->tx_bytes);
		atomic_दीर्घ_inc(&priv->tx_packets);
	पूर्ण अन्यथा अणु
		atomic_दीर्घ_inc(&priv->tx_dropped);
	पूर्ण
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम l2tp_eth_get_stats64(काष्ठा net_device *dev,
				 काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा l2tp_eth *priv = netdev_priv(dev);

	stats->tx_bytes   = (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&priv->tx_bytes);
	stats->tx_packets = (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&priv->tx_packets);
	stats->tx_dropped = (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&priv->tx_dropped);
	stats->rx_bytes   = (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&priv->rx_bytes);
	stats->rx_packets = (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&priv->rx_packets);
	stats->rx_errors  = (अचिन्हित दीर्घ)atomic_दीर्घ_पढ़ो(&priv->rx_errors);
पूर्ण

अटल स्थिर काष्ठा net_device_ops l2tp_eth_netdev_ops = अणु
	.nकरो_init		= l2tp_eth_dev_init,
	.nकरो_uninit		= l2tp_eth_dev_uninit,
	.nकरो_start_xmit		= l2tp_eth_dev_xmit,
	.nकरो_get_stats64	= l2tp_eth_get_stats64,
	.nकरो_set_mac_address	= eth_mac_addr,
पूर्ण;

अटल काष्ठा device_type l2tpeth_type = अणु
	.name = "l2tpeth",
पूर्ण;

अटल व्योम l2tp_eth_dev_setup(काष्ठा net_device *dev)
अणु
	SET_NETDEV_DEVTYPE(dev, &l2tpeth_type);
	ether_setup(dev);
	dev->priv_flags		&= ~IFF_TX_SKB_SHARING;
	dev->features		|= NETIF_F_LLTX;
	dev->netdev_ops		= &l2tp_eth_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
पूर्ण

अटल व्योम l2tp_eth_dev_recv(काष्ठा l2tp_session *session, काष्ठा sk_buff *skb, पूर्णांक data_len)
अणु
	काष्ठा l2tp_eth_sess *spriv = l2tp_session_priv(session);
	काष्ठा net_device *dev;
	काष्ठा l2tp_eth *priv;

	अगर (!pskb_may_pull(skb, ETH_HLEN))
		जाओ error;

	secpath_reset(skb);

	/* checksums verअगरied by L2TP */
	skb->ip_summed = CHECKSUM_NONE;

	skb_dst_drop(skb);
	nf_reset_ct(skb);

	rcu_पढ़ो_lock();
	dev = rcu_dereference(spriv->dev);
	अगर (!dev)
		जाओ error_rcu;

	priv = netdev_priv(dev);
	अगर (dev_क्रमward_skb(dev, skb) == NET_RX_SUCCESS) अणु
		atomic_दीर्घ_inc(&priv->rx_packets);
		atomic_दीर्घ_add(data_len, &priv->rx_bytes);
	पूर्ण अन्यथा अणु
		atomic_दीर्घ_inc(&priv->rx_errors);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस;

error_rcu:
	rcu_पढ़ो_unlock();
error:
	kमुक्त_skb(skb);
पूर्ण

अटल व्योम l2tp_eth_delete(काष्ठा l2tp_session *session)
अणु
	काष्ठा l2tp_eth_sess *spriv;
	काष्ठा net_device *dev;

	अगर (session) अणु
		spriv = l2tp_session_priv(session);

		rtnl_lock();
		dev = rtnl_dereference(spriv->dev);
		अगर (dev) अणु
			unरेजिस्टर_netdevice(dev);
			rtnl_unlock();
			module_put(THIS_MODULE);
		पूर्ण अन्यथा अणु
			rtnl_unlock();
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम l2tp_eth_show(काष्ठा seq_file *m, व्योम *arg)
अणु
	काष्ठा l2tp_session *session = arg;
	काष्ठा l2tp_eth_sess *spriv = l2tp_session_priv(session);
	काष्ठा net_device *dev;

	rcu_पढ़ो_lock();
	dev = rcu_dereference(spriv->dev);
	अगर (!dev) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	dev_hold(dev);
	rcu_पढ़ो_unlock();

	seq_म_लिखो(m, "   interface %s\n", dev->name);

	dev_put(dev);
पूर्ण

अटल व्योम l2tp_eth_adjust_mtu(काष्ठा l2tp_tunnel *tunnel,
				काष्ठा l2tp_session *session,
				काष्ठा net_device *dev)
अणु
	अचिन्हित पूर्णांक overhead = 0;
	u32 l3_overhead = 0;
	u32 mtu;

	/* अगर the encap is UDP, account क्रम UDP header size */
	अगर (tunnel->encap == L2TP_ENCAPTYPE_UDP) अणु
		overhead += माप(काष्ठा udphdr);
		dev->needed_headroom += माप(काष्ठा udphdr);
	पूर्ण

	lock_sock(tunnel->sock);
	l3_overhead = kernel_sock_ip_overhead(tunnel->sock);
	release_sock(tunnel->sock);

	अगर (l3_overhead == 0) अणु
		/* L3 Overhead couldn't be identअगरied, this could be
		 * because tunnel->sock was शून्य or the socket's
		 * address family was not IPv4 or IPv6,
		 * dev mtu stays at 1500.
		 */
		वापस;
	पूर्ण
	/* Adjust MTU, factor overhead - underlay L3, overlay L2 hdr
	 * UDP overhead, अगर any, was alपढ़ोy factored in above.
	 */
	overhead += session->hdr_len + ETH_HLEN + l3_overhead;

	mtu = l2tp_tunnel_dst_mtu(tunnel) - overhead;
	अगर (mtu < dev->min_mtu || mtu > dev->max_mtu)
		dev->mtu = ETH_DATA_LEN - overhead;
	अन्यथा
		dev->mtu = mtu;

	dev->needed_headroom += session->hdr_len;
पूर्ण

अटल पूर्णांक l2tp_eth_create(काष्ठा net *net, काष्ठा l2tp_tunnel *tunnel,
			   u32 session_id, u32 peer_session_id,
			   काष्ठा l2tp_session_cfg *cfg)
अणु
	अचिन्हित अक्षर name_assign_type;
	काष्ठा net_device *dev;
	अक्षर name[IFNAMSIZ];
	काष्ठा l2tp_session *session;
	काष्ठा l2tp_eth *priv;
	काष्ठा l2tp_eth_sess *spriv;
	पूर्णांक rc;

	अगर (cfg->अगरname) अणु
		strlcpy(name, cfg->अगरname, IFNAMSIZ);
		name_assign_type = NET_NAME_USER;
	पूर्ण अन्यथा अणु
		म_नकल(name, L2TP_ETH_DEV_NAME);
		name_assign_type = NET_NAME_ENUM;
	पूर्ण

	session = l2tp_session_create(माप(*spriv), tunnel, session_id,
				      peer_session_id, cfg);
	अगर (IS_ERR(session)) अणु
		rc = PTR_ERR(session);
		जाओ err;
	पूर्ण

	dev = alloc_netdev(माप(*priv), name, name_assign_type,
			   l2tp_eth_dev_setup);
	अगर (!dev) अणु
		rc = -ENOMEM;
		जाओ err_sess;
	पूर्ण

	dev_net_set(dev, net);
	dev->min_mtu = 0;
	dev->max_mtu = ETH_MAX_MTU;
	l2tp_eth_adjust_mtu(tunnel, session, dev);

	priv = netdev_priv(dev);
	priv->session = session;

	session->recv_skb = l2tp_eth_dev_recv;
	session->session_बंद = l2tp_eth_delete;
	अगर (IS_ENABLED(CONFIG_L2TP_DEBUGFS))
		session->show = l2tp_eth_show;

	spriv = l2tp_session_priv(session);

	l2tp_session_inc_refcount(session);

	rtnl_lock();

	/* Register both device and session जबतक holding the rtnl lock. This
	 * ensures that l2tp_eth_delete() will see that there's a device to
	 * unरेजिस्टर, even अगर it happened to run beक्रमe we assign spriv->dev.
	 */
	rc = l2tp_session_रेजिस्टर(session, tunnel);
	अगर (rc < 0) अणु
		rtnl_unlock();
		जाओ err_sess_dev;
	पूर्ण

	rc = रेजिस्टर_netdevice(dev);
	अगर (rc < 0) अणु
		rtnl_unlock();
		l2tp_session_delete(session);
		l2tp_session_dec_refcount(session);
		मुक्त_netdev(dev);

		वापस rc;
	पूर्ण

	strlcpy(session->अगरname, dev->name, IFNAMSIZ);
	rcu_assign_poपूर्णांकer(spriv->dev, dev);

	rtnl_unlock();

	l2tp_session_dec_refcount(session);

	__module_get(THIS_MODULE);

	वापस 0;

err_sess_dev:
	l2tp_session_dec_refcount(session);
	मुक्त_netdev(dev);
err_sess:
	kमुक्त(session);
err:
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा l2tp_nl_cmd_ops l2tp_eth_nl_cmd_ops = अणु
	.session_create	= l2tp_eth_create,
	.session_delete	= l2tp_session_delete,
पूर्ण;

अटल पूर्णांक __init l2tp_eth_init(व्योम)
अणु
	पूर्णांक err = 0;

	err = l2tp_nl_रेजिस्टर_ops(L2TP_PWTYPE_ETH, &l2tp_eth_nl_cmd_ops);
	अगर (err)
		जाओ err;

	pr_info("L2TP ethernet pseudowire support (L2TPv3)\n");

	वापस 0;

err:
	वापस err;
पूर्ण

अटल व्योम __निकास l2tp_eth_निकास(व्योम)
अणु
	l2tp_nl_unरेजिस्टर_ops(L2TP_PWTYPE_ETH);
पूर्ण

module_init(l2tp_eth_init);
module_निकास(l2tp_eth_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("James Chapman <jchapman@katalix.com>");
MODULE_DESCRIPTION("L2TP ethernet pseudowire driver");
MODULE_VERSION("1.0");
MODULE_ALIAS_L2TP_PWTYPE(5);
