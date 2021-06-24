<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IF_MACVLAN_H
#घोषणा _LINUX_IF_MACVLAN_H

#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <net/netlink.h>
#समावेश <linux/u64_stats_sync.h>

काष्ठा macvlan_port;

#घोषणा MACVLAN_MC_FILTER_BITS	8
#घोषणा MACVLAN_MC_FILTER_SZ	(1 << MACVLAN_MC_FILTER_BITS)

काष्ठा macvlan_dev अणु
	काष्ठा net_device	*dev;
	काष्ठा list_head	list;
	काष्ठा hlist_node	hlist;
	काष्ठा macvlan_port	*port;
	काष्ठा net_device	*lowerdev;
	व्योम			*accel_priv;
	काष्ठा vlan_pcpu_stats __percpu *pcpu_stats;

	DECLARE_BITMAP(mc_filter, MACVLAN_MC_FILTER_SZ);

	netdev_features_t	set_features;
	क्रमागत macvlan_mode	mode;
	u16			flags;
	अचिन्हित पूर्णांक		macaddr_count;
	u32			bc_queue_len_req;
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	काष्ठा netpoll		*netpoll;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत व्योम macvlan_count_rx(स्थिर काष्ठा macvlan_dev *vlan,
				    अचिन्हित पूर्णांक len, bool success,
				    bool multicast)
अणु
	अगर (likely(success)) अणु
		काष्ठा vlan_pcpu_stats *pcpu_stats;

		pcpu_stats = get_cpu_ptr(vlan->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->rx_packets++;
		pcpu_stats->rx_bytes += len;
		अगर (multicast)
			pcpu_stats->rx_multicast++;
		u64_stats_update_end(&pcpu_stats->syncp);
		put_cpu_ptr(vlan->pcpu_stats);
	पूर्ण अन्यथा अणु
		this_cpu_inc(vlan->pcpu_stats->rx_errors);
	पूर्ण
पूर्ण

बाह्य व्योम macvlan_common_setup(काष्ठा net_device *dev);

बाह्य पूर्णांक macvlan_common_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
				  काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				  काष्ठा netlink_ext_ack *extack);

बाह्य व्योम macvlan_dellink(काष्ठा net_device *dev, काष्ठा list_head *head);

बाह्य पूर्णांक macvlan_link_रेजिस्टर(काष्ठा rtnl_link_ops *ops);

#अगर IS_ENABLED(CONFIG_MACVLAN)
अटल अंतरभूत काष्ठा net_device *
macvlan_dev_real_dev(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *macvlan = netdev_priv(dev);

	वापस macvlan->lowerdev;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा net_device *
macvlan_dev_real_dev(स्थिर काष्ठा net_device *dev)
अणु
	BUG();
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम *macvlan_accel_priv(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *macvlan = netdev_priv(dev);

	वापस macvlan->accel_priv;
पूर्ण

अटल अंतरभूत bool macvlan_supports_dest_filter(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *macvlan = netdev_priv(dev);

	वापस macvlan->mode == MACVLAN_MODE_PRIVATE ||
	       macvlan->mode == MACVLAN_MODE_VEPA ||
	       macvlan->mode == MACVLAN_MODE_BRIDGE;
पूर्ण

अटल अंतरभूत पूर्णांक macvlan_release_l2fw_offload(काष्ठा net_device *dev)
अणु
	काष्ठा macvlan_dev *macvlan = netdev_priv(dev);

	macvlan->accel_priv = शून्य;
	वापस dev_uc_add(macvlan->lowerdev, dev->dev_addr);
पूर्ण
#पूर्ण_अगर /* _LINUX_IF_MACVLAN_H */
