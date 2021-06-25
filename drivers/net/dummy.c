<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* dummy.c: a dummy net driver

	The purpose of this driver is to provide a device to poपूर्णांक a
	route through, but not to actually transmit packets.

	Why?  If you have a machine whose only connection is an occasional
	PPP/SLIP/PLIP link, you can only connect to your own hostname
	when the link is up.  Otherwise you have to use localhost.
	This isn't very consistent.

	One solution is to set up a dummy link using PPP/SLIP/PLIP,
	but this seems (to me) too much overhead क्रम too little gain.
	This driver provides a small alternative. Thus you can करो

	[when not running slip]
		अगरconfig dummy slip.addr.ess.here up
	[to go to slip]
		अगरconfig dummy करोwn
		dip whatever

	This was written by looking at Donald Becker's skeleton driver
	and the loopback driver.  I then threw away anything that didn't
	apply!	Thanks to Alan Cox क्रम the key clue on what to करो with
	misguided packets.

			Nick Holloway, 27th May 1994
	[I tweaked this explanation a little but that's all]
			Alan Cox, 30th May 1994
*/

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/net_tstamp.h>
#समावेश <net/rtnetlink.h>
#समावेश <linux/u64_stats_sync.h>

#घोषणा DRV_NAME	"dummy"

अटल पूर्णांक numdummies = 1;

/* fake multicast ability */
अटल व्योम set_multicast_list(काष्ठा net_device *dev)
अणु
पूर्ण

अटल व्योम dummy_get_stats64(काष्ठा net_device *dev,
			      काष्ठा rtnl_link_stats64 *stats)
अणु
	dev_lstats_पढ़ो(dev, &stats->tx_packets, &stats->tx_bytes);
पूर्ण

अटल netdev_tx_t dummy_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	dev_lstats_add(dev, skb->len);

	skb_tx_बारtamp(skb);
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक dummy_dev_init(काष्ठा net_device *dev)
अणु
	dev->lstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_lstats);
	अगर (!dev->lstats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम dummy_dev_uninit(काष्ठा net_device *dev)
अणु
	मुक्त_percpu(dev->lstats);
पूर्ण

अटल पूर्णांक dummy_change_carrier(काष्ठा net_device *dev, bool new_carrier)
अणु
	अगर (new_carrier)
		netअगर_carrier_on(dev);
	अन्यथा
		netअगर_carrier_off(dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops dummy_netdev_ops = अणु
	.nकरो_init		= dummy_dev_init,
	.nकरो_uninit		= dummy_dev_uninit,
	.nकरो_start_xmit		= dummy_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_rx_mode	= set_multicast_list,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_get_stats64	= dummy_get_stats64,
	.nकरो_change_carrier	= dummy_change_carrier,
पूर्ण;

अटल व्योम dummy_get_drvinfo(काष्ठा net_device *dev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, DRV_NAME, माप(info->driver));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops dummy_ethtool_ops = अणु
	.get_drvinfo            = dummy_get_drvinfo,
	.get_ts_info		= ethtool_op_get_ts_info,
पूर्ण;

अटल व्योम dummy_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	/* Initialize the device काष्ठाure. */
	dev->netdev_ops = &dummy_netdev_ops;
	dev->ethtool_ops = &dummy_ethtool_ops;
	dev->needs_मुक्त_netdev = true;

	/* Fill in device काष्ठाure with ethernet-generic values. */
	dev->flags |= IFF_NOARP;
	dev->flags &= ~IFF_MULTICAST;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE | IFF_NO_QUEUE;
	dev->features	|= NETIF_F_SG | NETIF_F_FRAGLIST;
	dev->features	|= NETIF_F_GSO_SOFTWARE;
	dev->features	|= NETIF_F_HW_CSUM | NETIF_F_HIGHDMA | NETIF_F_LLTX;
	dev->features	|= NETIF_F_GSO_ENCAP_ALL;
	dev->hw_features |= dev->features;
	dev->hw_enc_features |= dev->features;
	eth_hw_addr_अक्रमom(dev);

	dev->min_mtu = 0;
	dev->max_mtu = 0;
पूर्ण

अटल पूर्णांक dummy_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			  काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा rtnl_link_ops dummy_link_ops __पढ़ो_mostly = अणु
	.kind		= DRV_NAME,
	.setup		= dummy_setup,
	.validate	= dummy_validate,
पूर्ण;

/* Number of dummy devices to be set up by this module. */
module_param(numdummies, पूर्णांक, 0);
MODULE_PARM_DESC(numdummies, "Number of dummy pseudo devices");

अटल पूर्णांक __init dummy_init_one(व्योम)
अणु
	काष्ठा net_device *dev_dummy;
	पूर्णांक err;

	dev_dummy = alloc_netdev(0, "dummy%d", NET_NAME_ENUM, dummy_setup);
	अगर (!dev_dummy)
		वापस -ENOMEM;

	dev_dummy->rtnl_link_ops = &dummy_link_ops;
	err = रेजिस्टर_netdevice(dev_dummy);
	अगर (err < 0)
		जाओ err;
	वापस 0;

err:
	मुक्त_netdev(dev_dummy);
	वापस err;
पूर्ण

अटल पूर्णांक __init dummy_init_module(व्योम)
अणु
	पूर्णांक i, err = 0;

	करोwn_ग_लिखो(&pernet_ops_rwsem);
	rtnl_lock();
	err = __rtnl_link_रेजिस्टर(&dummy_link_ops);
	अगर (err < 0)
		जाओ out;

	क्रम (i = 0; i < numdummies && !err; i++) अणु
		err = dummy_init_one();
		cond_resched();
	पूर्ण
	अगर (err < 0)
		__rtnl_link_unरेजिस्टर(&dummy_link_ops);

out:
	rtnl_unlock();
	up_ग_लिखो(&pernet_ops_rwsem);

	वापस err;
पूर्ण

अटल व्योम __निकास dummy_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&dummy_link_ops);
पूर्ण

module_init(dummy_init_module);
module_निकास(dummy_cleanup_module);
MODULE_LICENSE("GPL");
MODULE_ALIAS_RTNL_LINK(DRV_NAME);
