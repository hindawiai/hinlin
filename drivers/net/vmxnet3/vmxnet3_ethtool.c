<शैली गुरु>
/*
 * Linux driver क्रम VMware's vmxnet3 ethernet NIC.
 *
 * Copyright (C) 2008-2020, VMware, Inc. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Maपूर्णांकained by: pv-drivers@vmware.com
 *
 */


#समावेश "vmxnet3_int.h"

काष्ठा vmxnet3_stat_desc अणु
	अक्षर desc[ETH_GSTRING_LEN];
	पूर्णांक  offset;
पूर्ण;


/* per tq stats मुख्यtained by the device */
अटल स्थिर काष्ठा vmxnet3_stat_desc
vmxnet3_tq_dev_stats[] = अणु
	/* description,         offset */
	अणु "Tx Queue#",        0 पूर्ण,
	अणु "  TSO pkts tx",	दुरत्व(काष्ठा UPT1_TxStats, TSOPktsTxOK) पूर्ण,
	अणु "  TSO bytes tx",	दुरत्व(काष्ठा UPT1_TxStats, TSOBytesTxOK) पूर्ण,
	अणु "  ucast pkts tx",	दुरत्व(काष्ठा UPT1_TxStats, ucastPktsTxOK) पूर्ण,
	अणु "  ucast bytes tx",	दुरत्व(काष्ठा UPT1_TxStats, ucastBytesTxOK) पूर्ण,
	अणु "  mcast pkts tx",	दुरत्व(काष्ठा UPT1_TxStats, mcastPktsTxOK) पूर्ण,
	अणु "  mcast bytes tx",	दुरत्व(काष्ठा UPT1_TxStats, mcastBytesTxOK) पूर्ण,
	अणु "  bcast pkts tx",	दुरत्व(काष्ठा UPT1_TxStats, bcastPktsTxOK) पूर्ण,
	अणु "  bcast bytes tx",	दुरत्व(काष्ठा UPT1_TxStats, bcastBytesTxOK) पूर्ण,
	अणु "  pkts tx err",	दुरत्व(काष्ठा UPT1_TxStats, pktsTxError) पूर्ण,
	अणु "  pkts tx discard",	दुरत्व(काष्ठा UPT1_TxStats, pktsTxDiscard) पूर्ण,
पूर्ण;

/* per tq stats मुख्यtained by the driver */
अटल स्थिर काष्ठा vmxnet3_stat_desc
vmxnet3_tq_driver_stats[] = अणु
	/* description,         offset */
	अणु"  drv dropped tx total",	दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
						 drop_total) पूर्ण,
	अणु "     too many frags", दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					  drop_too_many_frags) पूर्ण,
	अणु "     giant hdr",	दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					 drop_oversized_hdr) पूर्ण,
	अणु "     hdr err",	दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					 drop_hdr_inspect_err) पूर्ण,
	अणु "     tso",		दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					 drop_tso) पूर्ण,
	अणु "  ring full",	दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					 tx_ring_full) पूर्ण,
	अणु "  pkts linearized",	दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					 linearized) पूर्ण,
	अणु "  hdr cloned",	दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					 copy_skb_header) पूर्ण,
	अणु "  giant hdr",	दुरत्व(काष्ठा vmxnet3_tq_driver_stats,
					 oversized_hdr) पूर्ण,
पूर्ण;

/* per rq stats मुख्यtained by the device */
अटल स्थिर काष्ठा vmxnet3_stat_desc
vmxnet3_rq_dev_stats[] = अणु
	अणु "Rx Queue#",        0 पूर्ण,
	अणु "  LRO pkts rx",	दुरत्व(काष्ठा UPT1_RxStats, LROPktsRxOK) पूर्ण,
	अणु "  LRO byte rx",	दुरत्व(काष्ठा UPT1_RxStats, LROBytesRxOK) पूर्ण,
	अणु "  ucast pkts rx",	दुरत्व(काष्ठा UPT1_RxStats, ucastPktsRxOK) पूर्ण,
	अणु "  ucast bytes rx",	दुरत्व(काष्ठा UPT1_RxStats, ucastBytesRxOK) पूर्ण,
	अणु "  mcast pkts rx",	दुरत्व(काष्ठा UPT1_RxStats, mcastPktsRxOK) पूर्ण,
	अणु "  mcast bytes rx",	दुरत्व(काष्ठा UPT1_RxStats, mcastBytesRxOK) पूर्ण,
	अणु "  bcast pkts rx",	दुरत्व(काष्ठा UPT1_RxStats, bcastPktsRxOK) पूर्ण,
	अणु "  bcast bytes rx",	दुरत्व(काष्ठा UPT1_RxStats, bcastBytesRxOK) पूर्ण,
	अणु "  pkts rx OOB",	दुरत्व(काष्ठा UPT1_RxStats, pktsRxOutOfBuf) पूर्ण,
	अणु "  pkts rx err",	दुरत्व(काष्ठा UPT1_RxStats, pktsRxError) पूर्ण,
पूर्ण;

/* per rq stats मुख्यtained by the driver */
अटल स्थिर काष्ठा vmxnet3_stat_desc
vmxnet3_rq_driver_stats[] = अणु
	/* description,         offset */
	अणु "  drv dropped rx total", दुरत्व(काष्ठा vmxnet3_rq_driver_stats,
					     drop_total) पूर्ण,
	अणु "     err",		दुरत्व(काष्ठा vmxnet3_rq_driver_stats,
					 drop_err) पूर्ण,
	अणु "     fcs",		दुरत्व(काष्ठा vmxnet3_rq_driver_stats,
					 drop_fcs) पूर्ण,
	अणु "  rx buf alloc fail", दुरत्व(काष्ठा vmxnet3_rq_driver_stats,
					  rx_buf_alloc_failure) पूर्ण,
पूर्ण;

/* global stats मुख्यtained by the driver */
अटल स्थिर काष्ठा vmxnet3_stat_desc
vmxnet3_global_stats[] = अणु
	/* description,         offset */
	अणु "tx timeout count",	दुरत्व(काष्ठा vmxnet3_adapter,
					 tx_समयout_count) पूर्ण
पूर्ण;


व्योम
vmxnet3_get_stats64(काष्ठा net_device *netdev,
		   काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा vmxnet3_adapter *adapter;
	काष्ठा vmxnet3_tq_driver_stats *drvTxStats;
	काष्ठा vmxnet3_rq_driver_stats *drvRxStats;
	काष्ठा UPT1_TxStats *devTxStats;
	काष्ठा UPT1_RxStats *devRxStats;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	adapter = netdev_priv(netdev);

	/* Collect the dev stats पूर्णांकo the shared area */
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD, VMXNET3_CMD_GET_STATS);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		devTxStats = &adapter->tqd_start[i].stats;
		drvTxStats = &adapter->tx_queue[i].stats;
		stats->tx_packets += devTxStats->ucastPktsTxOK +
				     devTxStats->mcastPktsTxOK +
				     devTxStats->bcastPktsTxOK;
		stats->tx_bytes += devTxStats->ucastBytesTxOK +
				   devTxStats->mcastBytesTxOK +
				   devTxStats->bcastBytesTxOK;
		stats->tx_errors += devTxStats->pktsTxError;
		stats->tx_dropped += drvTxStats->drop_total;
	पूर्ण

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		devRxStats = &adapter->rqd_start[i].stats;
		drvRxStats = &adapter->rx_queue[i].stats;
		stats->rx_packets += devRxStats->ucastPktsRxOK +
				     devRxStats->mcastPktsRxOK +
				     devRxStats->bcastPktsRxOK;

		stats->rx_bytes += devRxStats->ucastBytesRxOK +
				   devRxStats->mcastBytesRxOK +
				   devRxStats->bcastBytesRxOK;

		stats->rx_errors += devRxStats->pktsRxError;
		stats->rx_dropped += drvRxStats->drop_total;
		stats->multicast +=  devRxStats->mcastPktsRxOK;
	पूर्ण
पूर्ण

अटल पूर्णांक
vmxnet3_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस (ARRAY_SIZE(vmxnet3_tq_dev_stats) +
			ARRAY_SIZE(vmxnet3_tq_driver_stats)) *
		       adapter->num_tx_queues +
		       (ARRAY_SIZE(vmxnet3_rq_dev_stats) +
			ARRAY_SIZE(vmxnet3_rq_driver_stats)) *
		       adapter->num_rx_queues +
			ARRAY_SIZE(vmxnet3_global_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण


/* This is a version 2 of the vmxnet3 ethtool_regs which goes hand in hand with
 * the version 2 of the vmxnet3 support क्रम ethtool(8) --रेजिस्टर-dump.
 * Thereक्रमe, अगर any रेजिस्टरs are added, हटाओd or modअगरied, then a version
 * bump and a corresponding change in the vmxnet3 support क्रम ethtool(8)
 * --रेजिस्टर-dump would be required.
 */
अटल पूर्णांक
vmxnet3_get_regs_len(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	वापस ((9 /* BAR1 रेजिस्टरs */ +
		(1 + adapter->पूर्णांकr.num_पूर्णांकrs) +
		(1 + adapter->num_tx_queues * 17 /* Tx queue रेजिस्टरs */) +
		(1 + adapter->num_rx_queues * 23 /* Rx queue रेजिस्टरs */)) *
		माप(u32));
पूर्ण


अटल व्योम
vmxnet3_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, vmxnet3_driver_name, माप(drvinfo->driver));

	strlcpy(drvinfo->version, VMXNET3_DRIVER_VERSION_REPORT,
		माप(drvinfo->version));

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण


अटल व्योम
vmxnet3_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *buf)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i, j;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	क्रम (j = 0; j < adapter->num_tx_queues; j++) अणु
		क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_tq_dev_stats); i++)
			ethtool_प्र_लिखो(&buf, vmxnet3_tq_dev_stats[i].desc);
		क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_tq_driver_stats); i++)
			ethtool_प्र_लिखो(&buf, vmxnet3_tq_driver_stats[i].desc);
	पूर्ण

	क्रम (j = 0; j < adapter->num_rx_queues; j++) अणु
		क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_rq_dev_stats); i++)
			ethtool_प्र_लिखो(&buf, vmxnet3_rq_dev_stats[i].desc);
		क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_rq_driver_stats); i++)
			ethtool_प्र_लिखो(&buf, vmxnet3_rq_driver_stats[i].desc);
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_global_stats); i++)
		ethtool_प्र_लिखो(&buf, vmxnet3_global_stats[i].desc);
पूर्ण

netdev_features_t vmxnet3_fix_features(काष्ठा net_device *netdev,
				       netdev_features_t features)
अणु
	/* If Rx checksum is disabled, then LRO should also be disabled */
	अगर (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_LRO;

	वापस features;
पूर्ण

netdev_features_t vmxnet3_features_check(काष्ठा sk_buff *skb,
					 काष्ठा net_device *netdev,
					 netdev_features_t features)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	/* Validate अगर the tunneled packet is being offloaded by the device */
	अगर (VMXNET3_VERSION_GE_4(adapter) &&
	    skb->encapsulation && skb->ip_summed == CHECKSUM_PARTIAL) अणु
		u8 l4_proto = 0;

		चयन (vlan_get_protocol(skb)) अणु
		हाल htons(ETH_P_IP):
			l4_proto = ip_hdr(skb)->protocol;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			l4_proto = ipv6_hdr(skb)->nexthdr;
			अवरोध;
		शेष:
			वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
		पूर्ण

		अगर (l4_proto != IPPROTO_UDP)
			वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	पूर्ण
	वापस features;
पूर्ण

अटल व्योम vmxnet3_enable_encap_offloads(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	अगर (VMXNET3_VERSION_GE_4(adapter)) अणु
		netdev->hw_enc_features |= NETIF_F_SG | NETIF_F_RXCSUM |
			NETIF_F_HW_CSUM | NETIF_F_HW_VLAN_CTAG_TX |
			NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_TSO | NETIF_F_TSO6 |
			NETIF_F_LRO | NETIF_F_GSO_UDP_TUNNEL |
			NETIF_F_GSO_UDP_TUNNEL_CSUM;
	पूर्ण
पूर्ण

अटल व्योम vmxnet3_disable_encap_offloads(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	अगर (VMXNET3_VERSION_GE_4(adapter)) अणु
		netdev->hw_enc_features &= ~(NETIF_F_SG | NETIF_F_RXCSUM |
			NETIF_F_HW_CSUM | NETIF_F_HW_VLAN_CTAG_TX |
			NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_TSO | NETIF_F_TSO6 |
			NETIF_F_LRO | NETIF_F_GSO_UDP_TUNNEL |
			NETIF_F_GSO_UDP_TUNNEL_CSUM);
	पूर्ण
पूर्ण

पूर्णांक vmxnet3_set_features(काष्ठा net_device *netdev, netdev_features_t features)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	netdev_features_t changed = features ^ netdev->features;
	netdev_features_t tun_offload_mask = NETIF_F_GSO_UDP_TUNNEL |
					     NETIF_F_GSO_UDP_TUNNEL_CSUM;
	u8 udp_tun_enabled = (netdev->features & tun_offload_mask) != 0;

	अगर (changed & (NETIF_F_RXCSUM | NETIF_F_LRO |
		       NETIF_F_HW_VLAN_CTAG_RX | tun_offload_mask)) अणु
		अगर (features & NETIF_F_RXCSUM)
			adapter->shared->devRead.misc.uptFeatures |=
			UPT1_F_RXCSUM;
		अन्यथा
			adapter->shared->devRead.misc.uptFeatures &=
			~UPT1_F_RXCSUM;

		/* update hardware LRO capability accordingly */
		अगर (features & NETIF_F_LRO)
			adapter->shared->devRead.misc.uptFeatures |=
							UPT1_F_LRO;
		अन्यथा
			adapter->shared->devRead.misc.uptFeatures &=
							~UPT1_F_LRO;

		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			adapter->shared->devRead.misc.uptFeatures |=
			UPT1_F_RXVLAN;
		अन्यथा
			adapter->shared->devRead.misc.uptFeatures &=
			~UPT1_F_RXVLAN;

		अगर ((features & tun_offload_mask) != 0 && !udp_tun_enabled) अणु
			vmxnet3_enable_encap_offloads(netdev);
			adapter->shared->devRead.misc.uptFeatures |=
			UPT1_F_RXINNEROFLD;
		पूर्ण अन्यथा अगर ((features & tun_offload_mask) == 0 &&
			   udp_tun_enabled) अणु
			vmxnet3_disable_encap_offloads(netdev);
			adapter->shared->devRead.misc.uptFeatures &=
			~UPT1_F_RXINNEROFLD;
		पूर्ण

		spin_lock_irqsave(&adapter->cmd_lock, flags);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_UPDATE_FEATURE);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
vmxnet3_get_ethtool_stats(काष्ठा net_device *netdev,
			  काष्ठा ethtool_stats *stats, u64  *buf)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	u8 *base;
	पूर्णांक i;
	पूर्णांक j = 0;

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD, VMXNET3_CMD_GET_STATS);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	/* this करोes assume each counter is 64-bit wide */
	क्रम (j = 0; j < adapter->num_tx_queues; j++) अणु
		base = (u8 *)&adapter->tqd_start[j].stats;
		*buf++ = (u64)j;
		क्रम (i = 1; i < ARRAY_SIZE(vmxnet3_tq_dev_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_tq_dev_stats[i].offset);

		base = (u8 *)&adapter->tx_queue[j].stats;
		क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_tq_driver_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_tq_driver_stats[i].offset);
	पूर्ण

	क्रम (j = 0; j < adapter->num_rx_queues; j++) अणु
		base = (u8 *)&adapter->rqd_start[j].stats;
		*buf++ = (u64) j;
		क्रम (i = 1; i < ARRAY_SIZE(vmxnet3_rq_dev_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_rq_dev_stats[i].offset);

		base = (u8 *)&adapter->rx_queue[j].stats;
		क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_rq_driver_stats); i++)
			*buf++ = *(u64 *)(base +
					  vmxnet3_rq_driver_stats[i].offset);
	पूर्ण

	base = (u8 *)adapter;
	क्रम (i = 0; i < ARRAY_SIZE(vmxnet3_global_stats); i++)
		*buf++ = *(u64 *)(base + vmxnet3_global_stats[i].offset);
पूर्ण


/* This is a version 2 of the vmxnet3 ethtool_regs which goes hand in hand with
 * the version 2 of the vmxnet3 support क्रम ethtool(8) --रेजिस्टर-dump.
 * Thereक्रमe, अगर any रेजिस्टरs are added, हटाओd or modअगरied, then a version
 * bump and a corresponding change in the vmxnet3 support क्रम ethtool(8)
 * --रेजिस्टर-dump would be required.
 */
अटल व्योम
vmxnet3_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	u32 *buf = p;
	पूर्णांक i = 0, j = 0;

	स_रखो(p, 0, vmxnet3_get_regs_len(netdev));

	regs->version = 2;

	/* Update vmxnet3_get_regs_len अगर we want to dump more रेजिस्टरs */

	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_VRRS);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_UVRS);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_DSAL);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_DSAH);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_MACL);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_MACH);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_ICR);
	buf[j++] = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_ECR);

	buf[j++] = adapter->पूर्णांकr.num_पूर्णांकrs;
	क्रम (i = 0; i < adapter->पूर्णांकr.num_पूर्णांकrs; i++) अणु
		buf[j++] = VMXNET3_READ_BAR0_REG(adapter, VMXNET3_REG_IMR
						 + i * VMXNET3_REG_ALIGN);
	पूर्ण

	buf[j++] = adapter->num_tx_queues;
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा vmxnet3_tx_queue *tq = &adapter->tx_queue[i];

		buf[j++] = VMXNET3_READ_BAR0_REG(adapter, VMXNET3_REG_TXPROD +
						 i * VMXNET3_REG_ALIGN);

		buf[j++] = VMXNET3_GET_ADDR_LO(tq->tx_ring.basePA);
		buf[j++] = VMXNET3_GET_ADDR_HI(tq->tx_ring.basePA);
		buf[j++] = tq->tx_ring.size;
		buf[j++] = tq->tx_ring.next2fill;
		buf[j++] = tq->tx_ring.next2comp;
		buf[j++] = tq->tx_ring.gen;

		buf[j++] = VMXNET3_GET_ADDR_LO(tq->data_ring.basePA);
		buf[j++] = VMXNET3_GET_ADDR_HI(tq->data_ring.basePA);
		buf[j++] = tq->data_ring.size;
		buf[j++] = tq->txdata_desc_size;

		buf[j++] = VMXNET3_GET_ADDR_LO(tq->comp_ring.basePA);
		buf[j++] = VMXNET3_GET_ADDR_HI(tq->comp_ring.basePA);
		buf[j++] = tq->comp_ring.size;
		buf[j++] = tq->comp_ring.next2proc;
		buf[j++] = tq->comp_ring.gen;

		buf[j++] = tq->stopped;
	पूर्ण

	buf[j++] = adapter->num_rx_queues;
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा vmxnet3_rx_queue *rq = &adapter->rx_queue[i];

		buf[j++] =  VMXNET3_READ_BAR0_REG(adapter, VMXNET3_REG_RXPROD +
						  i * VMXNET3_REG_ALIGN);
		buf[j++] =  VMXNET3_READ_BAR0_REG(adapter, VMXNET3_REG_RXPROD2 +
						  i * VMXNET3_REG_ALIGN);

		buf[j++] = VMXNET3_GET_ADDR_LO(rq->rx_ring[0].basePA);
		buf[j++] = VMXNET3_GET_ADDR_HI(rq->rx_ring[0].basePA);
		buf[j++] = rq->rx_ring[0].size;
		buf[j++] = rq->rx_ring[0].next2fill;
		buf[j++] = rq->rx_ring[0].next2comp;
		buf[j++] = rq->rx_ring[0].gen;

		buf[j++] = VMXNET3_GET_ADDR_LO(rq->rx_ring[1].basePA);
		buf[j++] = VMXNET3_GET_ADDR_HI(rq->rx_ring[1].basePA);
		buf[j++] = rq->rx_ring[1].size;
		buf[j++] = rq->rx_ring[1].next2fill;
		buf[j++] = rq->rx_ring[1].next2comp;
		buf[j++] = rq->rx_ring[1].gen;

		buf[j++] = VMXNET3_GET_ADDR_LO(rq->data_ring.basePA);
		buf[j++] = VMXNET3_GET_ADDR_HI(rq->data_ring.basePA);
		buf[j++] = rq->rx_ring[0].size;
		buf[j++] = rq->data_ring.desc_size;

		buf[j++] = VMXNET3_GET_ADDR_LO(rq->comp_ring.basePA);
		buf[j++] = VMXNET3_GET_ADDR_HI(rq->comp_ring.basePA);
		buf[j++] = rq->comp_ring.size;
		buf[j++] = rq->comp_ring.next2proc;
		buf[j++] = rq->comp_ring.gen;
	पूर्ण
पूर्ण


अटल व्योम
vmxnet3_get_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_UCAST | WAKE_ARP | WAKE_MAGIC;
	wol->wolopts = adapter->wol;
पूर्ण


अटल पूर्णांक
vmxnet3_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_PHY | WAKE_MCAST | WAKE_BCAST |
			    WAKE_MAGICSECURE)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	adapter->wol = wol->wolopts;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	वापस 0;
पूर्ण


अटल पूर्णांक
vmxnet3_get_link_ksettings(काष्ठा net_device *netdev,
			   काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	ethtool_link_ksettings_zero_link_mode(ecmd, supported);
	ethtool_link_ksettings_add_link_mode(ecmd, supported, 10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(ecmd, supported, 1000baseT_Full);
	ethtool_link_ksettings_add_link_mode(ecmd, supported, TP);
	ethtool_link_ksettings_zero_link_mode(ecmd, advertising);
	ethtool_link_ksettings_add_link_mode(ecmd, advertising, TP);
	ecmd->base.port = PORT_TP;

	अगर (adapter->link_speed) अणु
		ecmd->base.speed = adapter->link_speed;
		ecmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		ecmd->base.speed = SPEED_UNKNOWN;
		ecmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	वापस 0;
पूर्ण


अटल व्योम
vmxnet3_get_ringparam(काष्ठा net_device *netdev,
		      काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	param->rx_max_pending = VMXNET3_RX_RING_MAX_SIZE;
	param->tx_max_pending = VMXNET3_TX_RING_MAX_SIZE;
	param->rx_mini_max_pending = VMXNET3_VERSION_GE_3(adapter) ?
		VMXNET3_RXDATA_DESC_MAX_SIZE : 0;
	param->rx_jumbo_max_pending = VMXNET3_RX_RING2_MAX_SIZE;

	param->rx_pending = adapter->rx_ring_size;
	param->tx_pending = adapter->tx_ring_size;
	param->rx_mini_pending = VMXNET3_VERSION_GE_3(adapter) ?
		adapter->rxdata_desc_size : 0;
	param->rx_jumbo_pending = adapter->rx_ring2_size;
पूर्ण


अटल पूर्णांक
vmxnet3_set_ringparam(काष्ठा net_device *netdev,
		      काष्ठा ethtool_ringparam *param)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	u32 new_tx_ring_size, new_rx_ring_size, new_rx_ring2_size;
	u16 new_rxdata_desc_size;
	u32 sz;
	पूर्णांक err = 0;

	अगर (param->tx_pending == 0 || param->tx_pending >
						VMXNET3_TX_RING_MAX_SIZE)
		वापस -EINVAL;

	अगर (param->rx_pending == 0 || param->rx_pending >
						VMXNET3_RX_RING_MAX_SIZE)
		वापस -EINVAL;

	अगर (param->rx_jumbo_pending == 0 ||
	    param->rx_jumbo_pending > VMXNET3_RX_RING2_MAX_SIZE)
		वापस -EINVAL;

	/* अगर adapter not yet initialized, करो nothing */
	अगर (adapter->rx_buf_per_pkt == 0) अणु
		netdev_err(netdev, "adapter not completely initialized, "
			   "ring size cannot be changed yet\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (VMXNET3_VERSION_GE_3(adapter)) अणु
		अगर (param->rx_mini_pending > VMXNET3_RXDATA_DESC_MAX_SIZE)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (param->rx_mini_pending != 0) अणु
		वापस -EINVAL;
	पूर्ण

	/* round it up to a multiple of VMXNET3_RING_SIZE_ALIGN */
	new_tx_ring_size = (param->tx_pending + VMXNET3_RING_SIZE_MASK) &
							~VMXNET3_RING_SIZE_MASK;
	new_tx_ring_size = min_t(u32, new_tx_ring_size,
				 VMXNET3_TX_RING_MAX_SIZE);
	अगर (new_tx_ring_size > VMXNET3_TX_RING_MAX_SIZE || (new_tx_ring_size %
						VMXNET3_RING_SIZE_ALIGN) != 0)
		वापस -EINVAL;

	/* ring0 has to be a multiple of
	 * rx_buf_per_pkt * VMXNET3_RING_SIZE_ALIGN
	 */
	sz = adapter->rx_buf_per_pkt * VMXNET3_RING_SIZE_ALIGN;
	new_rx_ring_size = (param->rx_pending + sz - 1) / sz * sz;
	new_rx_ring_size = min_t(u32, new_rx_ring_size,
				 VMXNET3_RX_RING_MAX_SIZE / sz * sz);
	अगर (new_rx_ring_size > VMXNET3_RX_RING_MAX_SIZE || (new_rx_ring_size %
							   sz) != 0)
		वापस -EINVAL;

	/* ring2 has to be a multiple of VMXNET3_RING_SIZE_ALIGN */
	new_rx_ring2_size = (param->rx_jumbo_pending + VMXNET3_RING_SIZE_MASK) &
				~VMXNET3_RING_SIZE_MASK;
	new_rx_ring2_size = min_t(u32, new_rx_ring2_size,
				  VMXNET3_RX_RING2_MAX_SIZE);

	/* rx data ring buffer size has to be a multiple of
	 * VMXNET3_RXDATA_DESC_SIZE_ALIGN
	 */
	new_rxdata_desc_size =
		(param->rx_mini_pending + VMXNET3_RXDATA_DESC_SIZE_MASK) &
		~VMXNET3_RXDATA_DESC_SIZE_MASK;
	new_rxdata_desc_size = min_t(u16, new_rxdata_desc_size,
				     VMXNET3_RXDATA_DESC_MAX_SIZE);

	अगर (new_tx_ring_size == adapter->tx_ring_size &&
	    new_rx_ring_size == adapter->rx_ring_size &&
	    new_rx_ring2_size == adapter->rx_ring2_size &&
	    new_rxdata_desc_size == adapter->rxdata_desc_size) अणु
		वापस 0;
	पूर्ण

	/*
	 * Reset_work may be in the middle of resetting the device, रुको क्रम its
	 * completion.
	 */
	जबतक (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (netअगर_running(netdev)) अणु
		vmxnet3_quiesce_dev(adapter);
		vmxnet3_reset_dev(adapter);

		/* recreate the rx queue and the tx queue based on the
		 * new sizes */
		vmxnet3_tq_destroy_all(adapter);
		vmxnet3_rq_destroy_all(adapter);

		err = vmxnet3_create_queues(adapter, new_tx_ring_size,
					    new_rx_ring_size, new_rx_ring2_size,
					    adapter->txdata_desc_size,
					    new_rxdata_desc_size);
		अगर (err) अणु
			/* failed, most likely because of OOM, try शेष
			 * size */
			netdev_err(netdev, "failed to apply new sizes, "
				   "try the default ones\n");
			new_rx_ring_size = VMXNET3_DEF_RX_RING_SIZE;
			new_rx_ring2_size = VMXNET3_DEF_RX_RING2_SIZE;
			new_tx_ring_size = VMXNET3_DEF_TX_RING_SIZE;
			new_rxdata_desc_size = VMXNET3_VERSION_GE_3(adapter) ?
				VMXNET3_DEF_RXDATA_DESC_SIZE : 0;

			err = vmxnet3_create_queues(adapter,
						    new_tx_ring_size,
						    new_rx_ring_size,
						    new_rx_ring2_size,
						    adapter->txdata_desc_size,
						    new_rxdata_desc_size);
			अगर (err) अणु
				netdev_err(netdev, "failed to create queues "
					   "with default sizes. Closing it\n");
				जाओ out;
			पूर्ण
		पूर्ण

		err = vmxnet3_activate_dev(adapter);
		अगर (err)
			netdev_err(netdev, "failed to re-activate, error %d."
				   " Closing it\n", err);
	पूर्ण
	adapter->tx_ring_size = new_tx_ring_size;
	adapter->rx_ring_size = new_rx_ring_size;
	adapter->rx_ring2_size = new_rx_ring2_size;
	adapter->rxdata_desc_size = new_rxdata_desc_size;

out:
	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
	अगर (err)
		vmxnet3_क्रमce_बंद(adapter);

	वापस err;
पूर्ण

अटल पूर्णांक
vmxnet3_get_rss_hash_opts(काष्ठा vmxnet3_adapter *adapter,
			  काष्ठा ethtool_rxnfc *info)
अणु
	क्रमागत Vmxnet3_RSSField rss_fields;

	अगर (netअगर_running(adapter->netdev)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&adapter->cmd_lock, flags);

		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_GET_RSS_FIELDS);
		rss_fields = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	पूर्ण अन्यथा अणु
		rss_fields = adapter->rss_fields;
	पूर्ण

	info->data = 0;

	/* Report शेष options क्रम RSS on vmxnet3 */
	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3 |
			      RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (rss_fields & VMXNET3_RSS_FIELDS_UDPIP4)
			info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		info->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
		अगर (rss_fields & VMXNET3_RSS_FIELDS_ESPIP4)
			info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V4_FLOW:
	हाल IPV4_FLOW:
		info->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (rss_fields & VMXNET3_RSS_FIELDS_UDPIP6)
			info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		info->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल SCTP_V6_FLOW:
	हाल IPV6_FLOW:
		info->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vmxnet3_set_rss_hash_opt(काष्ठा net_device *netdev,
			 काष्ठा vmxnet3_adapter *adapter,
			 काष्ठा ethtool_rxnfc *nfc)
अणु
	क्रमागत Vmxnet3_RSSField rss_fields = adapter->rss_fields;

	/* RSS करोes not support anything other than hashing
	 * to queues on src and dst IPs and ports
	 */
	अगर (nfc->data & ~(RXH_IP_SRC | RXH_IP_DST |
			  RXH_L4_B_0_1 | RXH_L4_B_2_3))
		वापस -EINVAL;

	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST) ||
		    !(nfc->data & RXH_L4_B_0_1) ||
		    !(nfc->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST))
			वापस -EINVAL;
		चयन (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			rss_fields &= ~VMXNET3_RSS_FIELDS_UDPIP4;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_fields |= VMXNET3_RSS_FIELDS_UDPIP4;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST))
			वापस -EINVAL;
		चयन (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			rss_fields &= ~VMXNET3_RSS_FIELDS_UDPIP6;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_fields |= VMXNET3_RSS_FIELDS_UDPIP6;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST))
			वापस -EINVAL;
		चयन (nfc->data & (RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		हाल 0:
			rss_fields &= ~VMXNET3_RSS_FIELDS_ESPIP4;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			rss_fields |= VMXNET3_RSS_FIELDS_ESPIP4;
		अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल SCTP_V4_FLOW:
	हाल SCTP_V6_FLOW:
		अगर (!(nfc->data & RXH_IP_SRC) ||
		    !(nfc->data & RXH_IP_DST) ||
		    (nfc->data & RXH_L4_B_0_1) ||
		    (nfc->data & RXH_L4_B_2_3))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* अगर we changed something we need to update flags */
	अगर (rss_fields != adapter->rss_fields) अणु
		adapter->शेष_rss_fields = false;
		अगर (netअगर_running(netdev)) अणु
			काष्ठा Vmxnet3_DriverShared *shared = adapter->shared;
			जोड़ Vmxnet3_CmdInfo *cmdInfo = &shared->cu.cmdInfo;
			अचिन्हित दीर्घ flags;

			spin_lock_irqsave(&adapter->cmd_lock, flags);
			cmdInfo->setRssFields = rss_fields;
			VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
					       VMXNET3_CMD_SET_RSS_FIELDS);

			/* Not all requested RSS may get applied, so get and
			 * cache what was actually applied.
			 */
			VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
					       VMXNET3_CMD_GET_RSS_FIELDS);
			adapter->rss_fields =
				VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
			spin_unlock_irqrestore(&adapter->cmd_lock, flags);
		पूर्ण अन्यथा अणु
			/* When the device is activated, we will try to apply
			 * these rules and cache the applied value later.
			 */
			adapter->rss_fields = rss_fields;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
vmxnet3_get_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *info,
		  u32 *rules)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = adapter->num_rx_queues;
		अवरोध;
	हाल ETHTOOL_GRXFH:
		अगर (!VMXNET3_VERSION_GE_4(adapter)) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
#अगर_घोषित VMXNET3_RSS
		अगर (!adapter->rss) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		err = vmxnet3_get_rss_hash_opts(adapter, info);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
vmxnet3_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (!VMXNET3_VERSION_GE_4(adapter)) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण
#अगर_घोषित VMXNET3_RSS
	अगर (!adapter->rss) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण
#पूर्ण_अगर

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXFH:
		err = vmxnet3_set_rss_hash_opt(netdev, adapter, info);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

करोne:
	वापस err;
पूर्ण

#अगर_घोषित VMXNET3_RSS
अटल u32
vmxnet3_get_rss_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	काष्ठा UPT1_RSSConf *rssConf = adapter->rss_conf;

	वापस rssConf->indTableSize;
पूर्ण

अटल पूर्णांक
vmxnet3_get_rss(काष्ठा net_device *netdev, u32 *p, u8 *key, u8 *hfunc)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	काष्ठा UPT1_RSSConf *rssConf = adapter->rss_conf;
	अचिन्हित पूर्णांक n = rssConf->indTableSize;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (!p)
		वापस 0;
	अगर (n > UPT1_RSS_MAX_IND_TABLE_SIZE)
		वापस 0;
	जबतक (n--)
		p[n] = rssConf->indTable[n];
	वापस 0;

पूर्ण

अटल पूर्णांक
vmxnet3_set_rss(काष्ठा net_device *netdev, स्थिर u32 *p, स्थिर u8 *key,
		स्थिर u8 hfunc)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ flags;
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	काष्ठा UPT1_RSSConf *rssConf = adapter->rss_conf;

	/* We करो not allow change in unsupported parameters */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;
	अगर (!p)
		वापस 0;
	क्रम (i = 0; i < rssConf->indTableSize; i++)
		rssConf->indTable[i] = p[i];

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_UPDATE_RSSIDT);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	वापस 0;

पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
vmxnet3_get_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	अगर (!VMXNET3_VERSION_GE_3(adapter))
		वापस -EOPNOTSUPP;

	चयन (adapter->coal_conf->coalMode) अणु
	हाल VMXNET3_COALESCE_DISABLED:
		/* काष्ठा ethtool_coalesce is alपढ़ोy initialized to 0 */
		अवरोध;
	हाल VMXNET3_COALESCE_ADAPT:
		ec->use_adaptive_rx_coalesce = true;
		अवरोध;
	हाल VMXNET3_COALESCE_STATIC:
		ec->tx_max_coalesced_frames =
			adapter->coal_conf->coalPara.coalStatic.tx_comp_depth;
		ec->rx_max_coalesced_frames =
			adapter->coal_conf->coalPara.coalStatic.rx_depth;
		अवरोध;
	हाल VMXNET3_COALESCE_RBC: अणु
		u32 rbc_rate;

		rbc_rate = adapter->coal_conf->coalPara.coalRbc.rbc_rate;
		ec->rx_coalesce_usecs = VMXNET3_COAL_RBC_USECS(rbc_rate);
	पूर्ण
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
vmxnet3_set_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	काष्ठा Vmxnet3_DriverShared *shared = adapter->shared;
	जोड़ Vmxnet3_CmdInfo *cmdInfo = &shared->cu.cmdInfo;
	अचिन्हित दीर्घ flags;

	अगर (!VMXNET3_VERSION_GE_3(adapter))
		वापस -EOPNOTSUPP;

	अगर ((ec->rx_coalesce_usecs == 0) &&
	    (ec->use_adaptive_rx_coalesce == 0) &&
	    (ec->tx_max_coalesced_frames == 0) &&
	    (ec->rx_max_coalesced_frames == 0)) अणु
		स_रखो(adapter->coal_conf, 0, माप(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_DISABLED;
		जाओ करोne;
	पूर्ण

	अगर (ec->rx_coalesce_usecs != 0) अणु
		u32 rbc_rate;

		अगर ((ec->use_adaptive_rx_coalesce != 0) ||
		    (ec->tx_max_coalesced_frames != 0) ||
		    (ec->rx_max_coalesced_frames != 0)) अणु
			वापस -EINVAL;
		पूर्ण

		rbc_rate = VMXNET3_COAL_RBC_RATE(ec->rx_coalesce_usecs);
		अगर (rbc_rate < VMXNET3_COAL_RBC_MIN_RATE ||
		    rbc_rate > VMXNET3_COAL_RBC_MAX_RATE) अणु
			वापस -EINVAL;
		पूर्ण

		स_रखो(adapter->coal_conf, 0, माप(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_RBC;
		adapter->coal_conf->coalPara.coalRbc.rbc_rate = rbc_rate;
		जाओ करोne;
	पूर्ण

	अगर (ec->use_adaptive_rx_coalesce != 0) अणु
		अगर ((ec->rx_coalesce_usecs != 0) ||
		    (ec->tx_max_coalesced_frames != 0) ||
		    (ec->rx_max_coalesced_frames != 0)) अणु
			वापस -EINVAL;
		पूर्ण
		स_रखो(adapter->coal_conf, 0, माप(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_ADAPT;
		जाओ करोne;
	पूर्ण

	अगर ((ec->tx_max_coalesced_frames != 0) ||
	    (ec->rx_max_coalesced_frames != 0)) अणु
		अगर ((ec->rx_coalesce_usecs != 0) ||
		    (ec->use_adaptive_rx_coalesce != 0)) अणु
			वापस -EINVAL;
		पूर्ण

		अगर ((ec->tx_max_coalesced_frames >
		    VMXNET3_COAL_STATIC_MAX_DEPTH) ||
		    (ec->rx_max_coalesced_frames >
		     VMXNET3_COAL_STATIC_MAX_DEPTH)) अणु
			वापस -EINVAL;
		पूर्ण

		स_रखो(adapter->coal_conf, 0, माप(*adapter->coal_conf));
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_STATIC;

		adapter->coal_conf->coalPara.coalStatic.tx_comp_depth =
			(ec->tx_max_coalesced_frames ?
			 ec->tx_max_coalesced_frames :
			 VMXNET3_COAL_STATIC_DEFAULT_DEPTH);

		adapter->coal_conf->coalPara.coalStatic.rx_depth =
			(ec->rx_max_coalesced_frames ?
			 ec->rx_max_coalesced_frames :
			 VMXNET3_COAL_STATIC_DEFAULT_DEPTH);

		adapter->coal_conf->coalPara.coalStatic.tx_depth =
			 VMXNET3_COAL_STATIC_DEFAULT_DEPTH;
		जाओ करोne;
	पूर्ण

करोne:
	adapter->शेष_coal_mode = false;
	अगर (netअगर_running(netdev)) अणु
		spin_lock_irqsave(&adapter->cmd_lock, flags);
		cmdInfo->varConf.confVer = 1;
		cmdInfo->varConf.confLen =
			cpu_to_le32(माप(*adapter->coal_conf));
		cmdInfo->varConf.confPA  = cpu_to_le64(adapter->coal_conf_pa);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_SET_COALESCE);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vmxnet3_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_drvinfo       = vmxnet3_get_drvinfo,
	.get_regs_len      = vmxnet3_get_regs_len,
	.get_regs          = vmxnet3_get_regs,
	.get_wol           = vmxnet3_get_wol,
	.set_wol           = vmxnet3_set_wol,
	.get_link          = ethtool_op_get_link,
	.get_coalesce      = vmxnet3_get_coalesce,
	.set_coalesce      = vmxnet3_set_coalesce,
	.get_strings       = vmxnet3_get_strings,
	.get_sset_count	   = vmxnet3_get_sset_count,
	.get_ethtool_stats = vmxnet3_get_ethtool_stats,
	.get_ringparam     = vmxnet3_get_ringparam,
	.set_ringparam     = vmxnet3_set_ringparam,
	.get_rxnfc         = vmxnet3_get_rxnfc,
	.set_rxnfc         = vmxnet3_set_rxnfc,
#अगर_घोषित VMXNET3_RSS
	.get_rxfh_indir_size = vmxnet3_get_rss_indir_size,
	.get_rxfh          = vmxnet3_get_rss,
	.set_rxfh          = vmxnet3_set_rss,
#पूर्ण_अगर
	.get_link_ksettings = vmxnet3_get_link_ksettings,
पूर्ण;

व्योम vmxnet3_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &vmxnet3_ethtool_ops;
पूर्ण
