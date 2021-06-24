<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/rtnetlink.h>

अटल netdev_tx_t nlmon_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	dev_lstats_add(dev, skb->len);

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक nlmon_dev_init(काष्ठा net_device *dev)
अणु
	dev->lstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_lstats);
	वापस dev->lstats == शून्य ? -ENOMEM : 0;
पूर्ण

अटल व्योम nlmon_dev_uninit(काष्ठा net_device *dev)
अणु
	मुक्त_percpu(dev->lstats);
पूर्ण

काष्ठा nlmon अणु
	काष्ठा netlink_tap nt;
पूर्ण;

अटल पूर्णांक nlmon_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा nlmon *nlmon = netdev_priv(dev);

	nlmon->nt.dev = dev;
	nlmon->nt.module = THIS_MODULE;
	वापस netlink_add_tap(&nlmon->nt);
पूर्ण

अटल पूर्णांक nlmon_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा nlmon *nlmon = netdev_priv(dev);

	वापस netlink_हटाओ_tap(&nlmon->nt);
पूर्ण

अटल व्योम
nlmon_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	u64 packets, bytes;

	dev_lstats_पढ़ो(dev, &packets, &bytes);

	stats->rx_packets = packets;
	stats->tx_packets = 0;

	stats->rx_bytes = bytes;
	stats->tx_bytes = 0;
पूर्ण

अटल u32 always_on(काष्ठा net_device *dev)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops nlmon_ethtool_ops = अणु
	.get_link = always_on,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops nlmon_ops = अणु
	.nकरो_init = nlmon_dev_init,
	.nकरो_uninit = nlmon_dev_uninit,
	.nकरो_खोलो = nlmon_खोलो,
	.nकरो_stop = nlmon_बंद,
	.nकरो_start_xmit = nlmon_xmit,
	.nकरो_get_stats64 = nlmon_get_stats64,
पूर्ण;

अटल व्योम nlmon_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_NETLINK;
	dev->priv_flags |= IFF_NO_QUEUE;

	dev->netdev_ops	= &nlmon_ops;
	dev->ethtool_ops = &nlmon_ethtool_ops;
	dev->needs_मुक्त_netdev = true;

	dev->features = NETIF_F_SG | NETIF_F_FRAGLIST |
			NETIF_F_HIGHDMA | NETIF_F_LLTX;
	dev->flags = IFF_NOARP;

	/* That's rather a softlimit here, which, of course,
	 * can be altered. Not a real MTU, but what is to be
	 * expected in most हालs.
	 */
	dev->mtu = NLMSG_GOODSIZE;
	dev->min_mtu = माप(काष्ठा nlmsghdr);
पूर्ण

अटल पूर्णांक nlmon_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS])
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा rtnl_link_ops nlmon_link_ops __पढ़ो_mostly = अणु
	.kind			= "nlmon",
	.priv_size		= माप(काष्ठा nlmon),
	.setup			= nlmon_setup,
	.validate		= nlmon_validate,
पूर्ण;

अटल __init पूर्णांक nlmon_रेजिस्टर(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&nlmon_link_ops);
पूर्ण

अटल __निकास व्योम nlmon_unरेजिस्टर(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&nlmon_link_ops);
पूर्ण

module_init(nlmon_रेजिस्टर);
module_निकास(nlmon_unरेजिस्टर);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Daniel Borkmann <dborkman@redhat.com>");
MODULE_AUTHOR("Mathieu Geli <geli@enseirb.fr>");
MODULE_DESCRIPTION("Netlink monitoring device");
MODULE_ALIAS_RTNL_LINK("nlmon");
