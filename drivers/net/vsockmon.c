<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <net/rtnetlink.h>
#समावेश <net/sock.h>
#समावेश <net/af_vsock.h>
#समावेश <uapi/linux/vsockmon.h>
#समावेश <linux/virtio_vsock.h>

/* Virtio transport max packet size plus header */
#घोषणा DEFAULT_MTU (VIRTIO_VSOCK_MAX_PKT_BUF_SIZE + \
		     माप(काष्ठा af_vsockmon_hdr))

अटल पूर्णांक vsockmon_dev_init(काष्ठा net_device *dev)
अणु
	dev->lstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_lstats);
	अगर (!dev->lstats)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम vsockmon_dev_uninit(काष्ठा net_device *dev)
अणु
	मुक्त_percpu(dev->lstats);
पूर्ण

काष्ठा vsockmon अणु
	काष्ठा vsock_tap vt;
पूर्ण;

अटल पूर्णांक vsockmon_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा vsockmon *vsockmon = netdev_priv(dev);

	vsockmon->vt.dev = dev;
	vsockmon->vt.module = THIS_MODULE;
	वापस vsock_add_tap(&vsockmon->vt);
पूर्ण

अटल पूर्णांक vsockmon_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा vsockmon *vsockmon = netdev_priv(dev);

	वापस vsock_हटाओ_tap(&vsockmon->vt);
पूर्ण

अटल netdev_tx_t vsockmon_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	dev_lstats_add(dev, skb->len);

	dev_kमुक्त_skb(skb);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम
vsockmon_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	dev_lstats_पढ़ो(dev, &stats->rx_packets, &stats->rx_bytes);

	stats->tx_packets = 0;
	stats->tx_bytes = 0;
पूर्ण

अटल पूर्णांक vsockmon_is_valid_mtu(पूर्णांक new_mtu)
अणु
	वापस new_mtu >= (पूर्णांक)माप(काष्ठा af_vsockmon_hdr);
पूर्ण

अटल पूर्णांक vsockmon_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	अगर (!vsockmon_is_valid_mtu(new_mtu))
		वापस -EINVAL;

	dev->mtu = new_mtu;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops vsockmon_ops = अणु
	.nकरो_init = vsockmon_dev_init,
	.nकरो_uninit = vsockmon_dev_uninit,
	.nकरो_खोलो = vsockmon_खोलो,
	.nकरो_stop = vsockmon_बंद,
	.nकरो_start_xmit = vsockmon_xmit,
	.nकरो_get_stats64 = vsockmon_get_stats64,
	.nकरो_change_mtu = vsockmon_change_mtu,
पूर्ण;

अटल u32 always_on(काष्ठा net_device *dev)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vsockmon_ethtool_ops = अणु
	.get_link = always_on,
पूर्ण;

अटल व्योम vsockmon_setup(काष्ठा net_device *dev)
अणु
	dev->type = ARPHRD_VSOCKMON;
	dev->priv_flags |= IFF_NO_QUEUE;

	dev->netdev_ops	= &vsockmon_ops;
	dev->ethtool_ops = &vsockmon_ethtool_ops;
	dev->needs_मुक्त_netdev = true;

	dev->features = NETIF_F_SG | NETIF_F_FRAGLIST |
			NETIF_F_HIGHDMA | NETIF_F_LLTX;

	dev->flags = IFF_NOARP;

	dev->mtu = DEFAULT_MTU;
पूर्ण

अटल काष्ठा rtnl_link_ops vsockmon_link_ops __पढ़ो_mostly = अणु
	.kind			= "vsockmon",
	.priv_size		= माप(काष्ठा vsockmon),
	.setup			= vsockmon_setup,
पूर्ण;

अटल __init पूर्णांक vsockmon_रेजिस्टर(व्योम)
अणु
	वापस rtnl_link_रेजिस्टर(&vsockmon_link_ops);
पूर्ण

अटल __निकास व्योम vsockmon_unरेजिस्टर(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&vsockmon_link_ops);
पूर्ण

module_init(vsockmon_रेजिस्टर);
module_निकास(vsockmon_unरेजिस्टर);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Gerard Garcia <ggarcia@deic.uab.cat>");
MODULE_DESCRIPTION("Vsock monitoring device. Based on nlmon device.");
MODULE_ALIAS_RTNL_LINK("vsockmon");
