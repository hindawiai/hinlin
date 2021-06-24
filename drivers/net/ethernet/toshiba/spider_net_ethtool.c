<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Network device driver क्रम Cell Processor-Based Blade
 *
 * (C) Copyright IBM Corp. 2005
 *
 * Authors : Utz Bacher <utz.bacher@de.ibm.com>
 *           Jens Osterkamp <Jens.Osterkamp@de.ibm.com>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>

#समावेश "spider_net.h"


अटल काष्ठा अणु
	स्थिर अक्षर str[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "tx_packets" पूर्ण,
	अणु "tx_bytes" पूर्ण,
	अणु "rx_packets" पूर्ण,
	अणु "rx_bytes" पूर्ण,
	अणु "tx_errors" पूर्ण,
	अणु "tx_dropped" पूर्ण,
	अणु "rx_dropped" पूर्ण,
	अणु "rx_descriptor_error" पूर्ण,
	अणु "tx_timeouts" पूर्ण,
	अणु "alloc_rx_skb_error" पूर्ण,
	अणु "rx_iommu_map_error" पूर्ण,
	अणु "tx_iommu_map_error" पूर्ण,
	अणु "rx_desc_unk_state" पूर्ण,
पूर्ण;

अटल पूर्णांक
spider_net_ethtool_get_link_ksettings(काष्ठा net_device *netdev,
				      काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा spider_net_card *card;
	card = netdev_priv(netdev);

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 1000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);

	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, 1000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);

	cmd->base.port = PORT_FIBRE;
	cmd->base.speed = card->phy.speed;
	cmd->base.duplex = DUPLEX_FULL;

	वापस 0;
पूर्ण

अटल व्योम
spider_net_ethtool_get_drvinfo(काष्ठा net_device *netdev,
			       काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा spider_net_card *card;
	card = netdev_priv(netdev);

	/* clear and fill out info */
	strlcpy(drvinfo->driver, spider_net_driver_name,
		माप(drvinfo->driver));
	strlcpy(drvinfo->version, VERSION, माप(drvinfo->version));
	strlcpy(drvinfo->fw_version, "no information",
		माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(card->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम
spider_net_ethtool_get_wol(काष्ठा net_device *netdev,
			   काष्ठा ethtool_wolinfo *wolinfo)
अणु
	/* no support क्रम wol */
	wolinfo->supported = 0;
	wolinfo->wolopts = 0;
पूर्ण

अटल u32
spider_net_ethtool_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा spider_net_card *card;
	card = netdev_priv(netdev);
	वापस card->msg_enable;
पूर्ण

अटल व्योम
spider_net_ethtool_set_msglevel(काष्ठा net_device *netdev,
				u32 level)
अणु
	काष्ठा spider_net_card *card;
	card = netdev_priv(netdev);
	card->msg_enable = level;
पूर्ण

अटल पूर्णांक
spider_net_ethtool_nway_reset(काष्ठा net_device *netdev)
अणु
	अगर (netअगर_running(netdev)) अणु
		spider_net_stop(netdev);
		spider_net_खोलो(netdev);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
spider_net_ethtool_get_ringparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा spider_net_card *card = netdev_priv(netdev);

	ering->tx_max_pending = SPIDER_NET_TX_DESCRIPTORS_MAX;
	ering->tx_pending = card->tx_chain.num_desc;
	ering->rx_max_pending = SPIDER_NET_RX_DESCRIPTORS_MAX;
	ering->rx_pending = card->rx_chain.num_desc;
पूर्ण

अटल पूर्णांक spider_net_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ethtool_stats_keys);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम spider_net_get_ethtool_stats(काष्ठा net_device *netdev,
		काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा spider_net_card *card = netdev_priv(netdev);

	data[0] = netdev->stats.tx_packets;
	data[1] = netdev->stats.tx_bytes;
	data[2] = netdev->stats.rx_packets;
	data[3] = netdev->stats.rx_bytes;
	data[4] = netdev->stats.tx_errors;
	data[5] = netdev->stats.tx_dropped;
	data[6] = netdev->stats.rx_dropped;
	data[7] = card->spider_stats.rx_desc_error;
	data[8] = card->spider_stats.tx_समयouts;
	data[9] = card->spider_stats.alloc_rx_skb_error;
	data[10] = card->spider_stats.rx_iommu_map_error;
	data[11] = card->spider_stats.tx_iommu_map_error;
	data[12] = card->spider_stats.rx_desc_unk_state;
पूर्ण

अटल व्योम spider_net_get_strings(काष्ठा net_device *netdev, u32 stringset,
				   u8 *data)
अणु
	स_नकल(data, ethtool_stats_keys, माप(ethtool_stats_keys));
पूर्ण

स्थिर काष्ठा ethtool_ops spider_net_ethtool_ops = अणु
	.get_drvinfo		= spider_net_ethtool_get_drvinfo,
	.get_wol		= spider_net_ethtool_get_wol,
	.get_msglevel		= spider_net_ethtool_get_msglevel,
	.set_msglevel		= spider_net_ethtool_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.nway_reset		= spider_net_ethtool_nway_reset,
	.get_ringparam          = spider_net_ethtool_get_ringparam,
	.get_strings		= spider_net_get_strings,
	.get_sset_count		= spider_net_get_sset_count,
	.get_ethtool_stats	= spider_net_get_ethtool_stats,
	.get_link_ksettings	= spider_net_ethtool_get_link_ksettings,
पूर्ण;

