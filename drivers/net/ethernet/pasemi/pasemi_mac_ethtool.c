<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2008 PA Semi, Inc
 *
 * Ethtool hooks क्रम the PA Semi PWRficient onchip 1G/10G Ethernet MACs
 */


#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/pasemi_dma.h>
#समावेश "pasemi_mac.h"

अटल काष्ठा अणु
	स्थिर अक्षर str[ETH_GSTRING_LEN];
पूर्ण ethtool_stats_keys[] = अणु
	अणु "rx-drops" पूर्ण,
	अणु "rx-bytes" पूर्ण,
	अणु "rx-packets" पूर्ण,
	अणु "rx-broadcast-packets" पूर्ण,
	अणु "rx-multicast-packets" पूर्ण,
	अणु "rx-crc-errors" पूर्ण,
	अणु "rx-undersize-errors" पूर्ण,
	अणु "rx-oversize-errors" पूर्ण,
	अणु "rx-short-fragment-errors" पूर्ण,
	अणु "rx-jabber-errors" पूर्ण,
	अणु "rx-64-byte-packets" पूर्ण,
	अणु "rx-65-127-byte-packets" पूर्ण,
	अणु "rx-128-255-byte-packets" पूर्ण,
	अणु "rx-256-511-byte-packets" पूर्ण,
	अणु "rx-512-1023-byte-packets" पूर्ण,
	अणु "rx-1024-1518-byte-packets" पूर्ण,
	अणु "rx-pause-frames" पूर्ण,
	अणु "tx-bytes" पूर्ण,
	अणु "tx-packets" पूर्ण,
	अणु "tx-broadcast-packets" पूर्ण,
	अणु "tx-multicast-packets" पूर्ण,
	अणु "tx-collisions" पूर्ण,
	अणु "tx-late-collisions" पूर्ण,
	अणु "tx-excessive-collisions" पूर्ण,
	अणु "tx-crc-errors" पूर्ण,
	अणु "tx-undersize-errors" पूर्ण,
	अणु "tx-oversize-errors" पूर्ण,
	अणु "tx-64-byte-packets" पूर्ण,
	अणु "tx-65-127-byte-packets" पूर्ण,
	अणु "tx-128-255-byte-packets" पूर्ण,
	अणु "tx-256-511-byte-packets" पूर्ण,
	अणु "tx-512-1023-byte-packets" पूर्ण,
	अणु "tx-1024-1518-byte-packets" पूर्ण,
पूर्ण;

अटल u32
pasemi_mac_ethtool_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(netdev);
	वापस mac->msg_enable;
पूर्ण

अटल व्योम
pasemi_mac_ethtool_set_msglevel(काष्ठा net_device *netdev,
				u32 level)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(netdev);
	mac->msg_enable = level;
पूर्ण


अटल व्योम
pasemi_mac_ethtool_get_ringparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(netdev);

	ering->tx_max_pending = TX_RING_SIZE/2;
	ering->tx_pending = RING_USED(mac->tx)/2;
	ering->rx_max_pending = RX_RING_SIZE/4;
	ering->rx_pending = RING_USED(mac->rx)/4;
पूर्ण

अटल पूर्णांक pasemi_mac_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ethtool_stats_keys);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम pasemi_mac_get_ethtool_stats(काष्ठा net_device *netdev,
		काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा pasemi_mac *mac = netdev_priv(netdev);
	पूर्णांक i;

	data[0] = pasemi_पढ़ो_dma_reg(PAS_DMA_RXINT_RCMDSTA(mac->dma_अगर))
			>> PAS_DMA_RXINT_RCMDSTA_DROPS_S;
	क्रम (i = 0; i < 32; i++)
		data[1+i] = pasemi_पढ़ो_mac_reg(mac->dma_अगर, PAS_MAC_RMON(i));
पूर्ण

अटल व्योम pasemi_mac_get_strings(काष्ठा net_device *netdev, u32 stringset,
				   u8 *data)
अणु
	स_नकल(data, ethtool_stats_keys, माप(ethtool_stats_keys));
पूर्ण

स्थिर काष्ठा ethtool_ops pasemi_mac_ethtool_ops = अणु
	.get_msglevel		= pasemi_mac_ethtool_get_msglevel,
	.set_msglevel		= pasemi_mac_ethtool_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.get_ringparam          = pasemi_mac_ethtool_get_ringparam,
	.get_strings		= pasemi_mac_get_strings,
	.get_sset_count		= pasemi_mac_get_sset_count,
	.get_ethtool_stats	= pasemi_mac_get_ethtool_stats,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
पूर्ण;

