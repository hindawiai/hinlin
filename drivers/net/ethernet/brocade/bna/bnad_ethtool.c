<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

#समावेश "cna.h"

#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/rtnetlink.h>

#समावेश "bna.h"

#समावेश "bnad.h"

#घोषणा BNAD_NUM_TXF_COUNTERS 12
#घोषणा BNAD_NUM_RXF_COUNTERS 10
#घोषणा BNAD_NUM_CQ_COUNTERS (3 + 5)
#घोषणा BNAD_NUM_RXQ_COUNTERS 7
#घोषणा BNAD_NUM_TXQ_COUNTERS 5

अटल स्थिर अक्षर *bnad_net_stats_strings[] = अणु
	"rx_packets",
	"tx_packets",
	"rx_bytes",
	"tx_bytes",
	"rx_errors",
	"tx_errors",
	"rx_dropped",
	"tx_dropped",
	"multicast",
	"collisions",
	"rx_length_errors",
	"rx_crc_errors",
	"rx_frame_errors",
	"tx_fifo_errors",

	"netif_queue_stop",
	"netif_queue_wakeup",
	"netif_queue_stopped",
	"tso4",
	"tso6",
	"tso_err",
	"tcpcsum_offload",
	"udpcsum_offload",
	"csum_help",
	"tx_skb_too_short",
	"tx_skb_stopping",
	"tx_skb_max_vectors",
	"tx_skb_mss_too_long",
	"tx_skb_tso_too_short",
	"tx_skb_tso_prepare",
	"tx_skb_non_tso_too_long",
	"tx_skb_tcp_hdr",
	"tx_skb_udp_hdr",
	"tx_skb_csum_err",
	"tx_skb_headlen_too_long",
	"tx_skb_headlen_zero",
	"tx_skb_frag_zero",
	"tx_skb_len_mismatch",
	"tx_skb_map_failed",
	"hw_stats_updates",
	"netif_rx_dropped",

	"link_toggle",
	"cee_toggle",

	"rxp_info_alloc_failed",
	"mbox_intr_disabled",
	"mbox_intr_enabled",
	"tx_unmap_q_alloc_failed",
	"rx_unmap_q_alloc_failed",
	"rxbuf_alloc_failed",
	"rxbuf_map_failed",

	"mac_stats_clr_cnt",
	"mac_frame_64",
	"mac_frame_65_127",
	"mac_frame_128_255",
	"mac_frame_256_511",
	"mac_frame_512_1023",
	"mac_frame_1024_1518",
	"mac_frame_1518_1522",
	"mac_rx_bytes",
	"mac_rx_packets",
	"mac_rx_fcs_error",
	"mac_rx_multicast",
	"mac_rx_broadcast",
	"mac_rx_control_frames",
	"mac_rx_pause",
	"mac_rx_unknown_opcode",
	"mac_rx_alignment_error",
	"mac_rx_frame_length_error",
	"mac_rx_code_error",
	"mac_rx_carrier_sense_error",
	"mac_rx_undersize",
	"mac_rx_oversize",
	"mac_rx_fragments",
	"mac_rx_jabber",
	"mac_rx_drop",

	"mac_tx_bytes",
	"mac_tx_packets",
	"mac_tx_multicast",
	"mac_tx_broadcast",
	"mac_tx_pause",
	"mac_tx_deferral",
	"mac_tx_excessive_deferral",
	"mac_tx_single_collision",
	"mac_tx_muliple_collision",
	"mac_tx_late_collision",
	"mac_tx_excessive_collision",
	"mac_tx_total_collision",
	"mac_tx_pause_honored",
	"mac_tx_drop",
	"mac_tx_jabber",
	"mac_tx_fcs_error",
	"mac_tx_control_frame",
	"mac_tx_oversize",
	"mac_tx_undersize",
	"mac_tx_fragments",

	"bpc_tx_pause_0",
	"bpc_tx_pause_1",
	"bpc_tx_pause_2",
	"bpc_tx_pause_3",
	"bpc_tx_pause_4",
	"bpc_tx_pause_5",
	"bpc_tx_pause_6",
	"bpc_tx_pause_7",
	"bpc_tx_zero_pause_0",
	"bpc_tx_zero_pause_1",
	"bpc_tx_zero_pause_2",
	"bpc_tx_zero_pause_3",
	"bpc_tx_zero_pause_4",
	"bpc_tx_zero_pause_5",
	"bpc_tx_zero_pause_6",
	"bpc_tx_zero_pause_7",
	"bpc_tx_first_pause_0",
	"bpc_tx_first_pause_1",
	"bpc_tx_first_pause_2",
	"bpc_tx_first_pause_3",
	"bpc_tx_first_pause_4",
	"bpc_tx_first_pause_5",
	"bpc_tx_first_pause_6",
	"bpc_tx_first_pause_7",

	"bpc_rx_pause_0",
	"bpc_rx_pause_1",
	"bpc_rx_pause_2",
	"bpc_rx_pause_3",
	"bpc_rx_pause_4",
	"bpc_rx_pause_5",
	"bpc_rx_pause_6",
	"bpc_rx_pause_7",
	"bpc_rx_zero_pause_0",
	"bpc_rx_zero_pause_1",
	"bpc_rx_zero_pause_2",
	"bpc_rx_zero_pause_3",
	"bpc_rx_zero_pause_4",
	"bpc_rx_zero_pause_5",
	"bpc_rx_zero_pause_6",
	"bpc_rx_zero_pause_7",
	"bpc_rx_first_pause_0",
	"bpc_rx_first_pause_1",
	"bpc_rx_first_pause_2",
	"bpc_rx_first_pause_3",
	"bpc_rx_first_pause_4",
	"bpc_rx_first_pause_5",
	"bpc_rx_first_pause_6",
	"bpc_rx_first_pause_7",

	"rad_rx_frames",
	"rad_rx_octets",
	"rad_rx_vlan_frames",
	"rad_rx_ucast",
	"rad_rx_ucast_octets",
	"rad_rx_ucast_vlan",
	"rad_rx_mcast",
	"rad_rx_mcast_octets",
	"rad_rx_mcast_vlan",
	"rad_rx_bcast",
	"rad_rx_bcast_octets",
	"rad_rx_bcast_vlan",
	"rad_rx_drops",

	"rlb_rad_rx_frames",
	"rlb_rad_rx_octets",
	"rlb_rad_rx_vlan_frames",
	"rlb_rad_rx_ucast",
	"rlb_rad_rx_ucast_octets",
	"rlb_rad_rx_ucast_vlan",
	"rlb_rad_rx_mcast",
	"rlb_rad_rx_mcast_octets",
	"rlb_rad_rx_mcast_vlan",
	"rlb_rad_rx_bcast",
	"rlb_rad_rx_bcast_octets",
	"rlb_rad_rx_bcast_vlan",
	"rlb_rad_rx_drops",

	"fc_rx_ucast_octets",
	"fc_rx_ucast",
	"fc_rx_ucast_vlan",
	"fc_rx_mcast_octets",
	"fc_rx_mcast",
	"fc_rx_mcast_vlan",
	"fc_rx_bcast_octets",
	"fc_rx_bcast",
	"fc_rx_bcast_vlan",

	"fc_tx_ucast_octets",
	"fc_tx_ucast",
	"fc_tx_ucast_vlan",
	"fc_tx_mcast_octets",
	"fc_tx_mcast",
	"fc_tx_mcast_vlan",
	"fc_tx_bcast_octets",
	"fc_tx_bcast",
	"fc_tx_bcast_vlan",
	"fc_tx_parity_errors",
	"fc_tx_timeout",
	"fc_tx_fid_parity_errors",
पूर्ण;

#घोषणा BNAD_ETHTOOL_STATS_NUM	ARRAY_SIZE(bnad_net_stats_strings)

अटल पूर्णांक
bnad_get_link_ksettings(काष्ठा net_device *netdev,
			काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 supported, advertising;

	supported = SUPPORTED_10000baseT_Full;
	advertising = ADVERTISED_10000baseT_Full;
	cmd->base.स्वतःneg = AUTONEG_DISABLE;
	supported |= SUPPORTED_FIBRE;
	advertising |= ADVERTISED_FIBRE;
	cmd->base.port = PORT_FIBRE;
	cmd->base.phy_address = 0;

	अगर (netअगर_carrier_ok(netdev)) अणु
		cmd->base.speed = SPEED_10000;
		cmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnad_set_link_ksettings(काष्ठा net_device *netdev,
			स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	/* 10G full duplex setting supported only */
	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE)
		वापस -EOPNOTSUPP;

	अगर ((cmd->base.speed == SPEED_10000) &&
	    (cmd->base.duplex == DUPLEX_FULL))
		वापस 0;

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम
bnad_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा bfa_ioc_attr *ioc_attr;
	अचिन्हित दीर्घ flags;

	strlcpy(drvinfo->driver, BNAD_NAME, माप(drvinfo->driver));

	ioc_attr = kzalloc(माप(*ioc_attr), GFP_KERNEL);
	अगर (ioc_attr) अणु
		spin_lock_irqsave(&bnad->bna_lock, flags);
		bfa_nw_ioc_get_attr(&bnad->bna.ioceth.ioc, ioc_attr);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);

		strlcpy(drvinfo->fw_version, ioc_attr->adapter_attr.fw_ver,
			माप(drvinfo->fw_version));
		kमुक्त(ioc_attr);
	पूर्ण

	strlcpy(drvinfo->bus_info, pci_name(bnad->pcidev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम
bnad_get_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wolinfo)
अणु
	wolinfo->supported = 0;
	wolinfo->wolopts = 0;
पूर्ण

अटल पूर्णांक
bnad_get_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	/* Lock rqd. to access bnad->bna_lock */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	coalesce->use_adaptive_rx_coalesce =
		(bnad->cfg_flags & BNAD_CF_DIM_ENABLED) ? true : false;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	coalesce->rx_coalesce_usecs = bnad->rx_coalescing_समयo *
					BFI_COALESCING_TIMER_UNIT;
	coalesce->tx_coalesce_usecs = bnad->tx_coalescing_समयo *
					BFI_COALESCING_TIMER_UNIT;
	coalesce->tx_max_coalesced_frames = BFI_TX_INTERPKT_COUNT;

	वापस 0;
पूर्ण

अटल पूर्णांक
bnad_set_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *coalesce)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	पूर्णांक to_del = 0;

	अगर (coalesce->rx_coalesce_usecs == 0 ||
	    coalesce->rx_coalesce_usecs >
	    BFI_MAX_COALESCING_TIMEO * BFI_COALESCING_TIMER_UNIT)
		वापस -EINVAL;

	अगर (coalesce->tx_coalesce_usecs == 0 ||
	    coalesce->tx_coalesce_usecs >
	    BFI_MAX_COALESCING_TIMEO * BFI_COALESCING_TIMER_UNIT)
		वापस -EINVAL;

	mutex_lock(&bnad->conf_mutex);
	/*
	 * Do not need to store rx_coalesce_usecs here
	 * Every समय DIM is disabled, we can get it from the
	 * stack.
	 */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (coalesce->use_adaptive_rx_coalesce) अणु
		अगर (!(bnad->cfg_flags & BNAD_CF_DIM_ENABLED)) अणु
			bnad->cfg_flags |= BNAD_CF_DIM_ENABLED;
			bnad_dim_समयr_start(bnad);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bnad->cfg_flags & BNAD_CF_DIM_ENABLED) अणु
			bnad->cfg_flags &= ~BNAD_CF_DIM_ENABLED;
			अगर (bnad->cfg_flags & BNAD_CF_DIM_ENABLED &&
			    test_bit(BNAD_RF_DIM_TIMER_RUNNING,
			    &bnad->run_flags)) अणु
				clear_bit(BNAD_RF_DIM_TIMER_RUNNING,
							&bnad->run_flags);
				to_del = 1;
			पूर्ण
			spin_unlock_irqrestore(&bnad->bna_lock, flags);
			अगर (to_del)
				del_समयr_sync(&bnad->dim_समयr);
			spin_lock_irqsave(&bnad->bna_lock, flags);
			bnad_rx_coalescing_समयo_set(bnad);
		पूर्ण
	पूर्ण
	अगर (bnad->tx_coalescing_समयo != coalesce->tx_coalesce_usecs /
					BFI_COALESCING_TIMER_UNIT) अणु
		bnad->tx_coalescing_समयo = coalesce->tx_coalesce_usecs /
						BFI_COALESCING_TIMER_UNIT;
		bnad_tx_coalescing_समयo_set(bnad);
	पूर्ण

	अगर (bnad->rx_coalescing_समयo != coalesce->rx_coalesce_usecs /
					BFI_COALESCING_TIMER_UNIT) अणु
		bnad->rx_coalescing_समयo = coalesce->rx_coalesce_usecs /
						BFI_COALESCING_TIMER_UNIT;

		अगर (!(bnad->cfg_flags & BNAD_CF_DIM_ENABLED))
			bnad_rx_coalescing_समयo_set(bnad);

	पूर्ण

	/* Add Tx Inter-pkt DMA count?  */

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	mutex_unlock(&bnad->conf_mutex);
	वापस 0;
पूर्ण

अटल व्योम
bnad_get_ringparam(काष्ठा net_device *netdev,
		   काष्ठा ethtool_ringparam *ringparam)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);

	ringparam->rx_max_pending = BNAD_MAX_RXQ_DEPTH;
	ringparam->tx_max_pending = BNAD_MAX_TXQ_DEPTH;

	ringparam->rx_pending = bnad->rxq_depth;
	ringparam->tx_pending = bnad->txq_depth;
पूर्ण

अटल पूर्णांक
bnad_set_ringparam(काष्ठा net_device *netdev,
		   काष्ठा ethtool_ringparam *ringparam)
अणु
	पूर्णांक i, current_err, err = 0;
	काष्ठा bnad *bnad = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	mutex_lock(&bnad->conf_mutex);
	अगर (ringparam->rx_pending == bnad->rxq_depth &&
	    ringparam->tx_pending == bnad->txq_depth) अणु
		mutex_unlock(&bnad->conf_mutex);
		वापस 0;
	पूर्ण

	अगर (ringparam->rx_pending < BNAD_MIN_Q_DEPTH ||
	    ringparam->rx_pending > BNAD_MAX_RXQ_DEPTH ||
	    !is_घातer_of_2(ringparam->rx_pending)) अणु
		mutex_unlock(&bnad->conf_mutex);
		वापस -EINVAL;
	पूर्ण
	अगर (ringparam->tx_pending < BNAD_MIN_Q_DEPTH ||
	    ringparam->tx_pending > BNAD_MAX_TXQ_DEPTH ||
	    !is_घातer_of_2(ringparam->tx_pending)) अणु
		mutex_unlock(&bnad->conf_mutex);
		वापस -EINVAL;
	पूर्ण

	अगर (ringparam->rx_pending != bnad->rxq_depth) अणु
		bnad->rxq_depth = ringparam->rx_pending;
		अगर (!netअगर_running(netdev)) अणु
			mutex_unlock(&bnad->conf_mutex);
			वापस 0;
		पूर्ण

		क्रम (i = 0; i < bnad->num_rx; i++) अणु
			अगर (!bnad->rx_info[i].rx)
				जारी;
			bnad_destroy_rx(bnad, i);
			current_err = bnad_setup_rx(bnad, i);
			अगर (current_err && !err)
				err = current_err;
		पूर्ण

		अगर (!err && bnad->rx_info[0].rx) अणु
			/* restore rx configuration */
			bnad_restore_vlans(bnad, 0);
			bnad_enable_शेष_bcast(bnad);
			spin_lock_irqsave(&bnad->bna_lock, flags);
			bnad_mac_addr_set_locked(bnad, netdev->dev_addr);
			spin_unlock_irqrestore(&bnad->bna_lock, flags);
			bnad->cfg_flags &= ~(BNAD_CF_ALLMULTI |
					     BNAD_CF_PROMISC);
			bnad_set_rx_mode(netdev);
		पूर्ण
	पूर्ण
	अगर (ringparam->tx_pending != bnad->txq_depth) अणु
		bnad->txq_depth = ringparam->tx_pending;
		अगर (!netअगर_running(netdev)) अणु
			mutex_unlock(&bnad->conf_mutex);
			वापस 0;
		पूर्ण

		क्रम (i = 0; i < bnad->num_tx; i++) अणु
			अगर (!bnad->tx_info[i].tx)
				जारी;
			bnad_destroy_tx(bnad, i);
			current_err = bnad_setup_tx(bnad, i);
			अगर (current_err && !err)
				err = current_err;
		पूर्ण
	पूर्ण

	mutex_unlock(&bnad->conf_mutex);
	वापस err;
पूर्ण

अटल व्योम
bnad_get_छोड़ोparam(काष्ठा net_device *netdev,
		    काष्ठा ethtool_छोड़ोparam *छोड़ोparam)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);

	छोड़ोparam->स्वतःneg = 0;
	छोड़ोparam->rx_छोड़ो = bnad->bna.enet.छोड़ो_config.rx_छोड़ो;
	छोड़ोparam->tx_छोड़ो = bnad->bna.enet.छोड़ो_config.tx_छोड़ो;
पूर्ण

अटल पूर्णांक
bnad_set_छोड़ोparam(काष्ठा net_device *netdev,
		    काष्ठा ethtool_छोड़ोparam *छोड़ोparam)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा bna_छोड़ो_config छोड़ो_config;
	अचिन्हित दीर्घ flags;

	अगर (छोड़ोparam->स्वतःneg == AUTONEG_ENABLE)
		वापस -EINVAL;

	mutex_lock(&bnad->conf_mutex);
	अगर (छोड़ोparam->rx_छोड़ो != bnad->bna.enet.छोड़ो_config.rx_छोड़ो ||
	    छोड़ोparam->tx_छोड़ो != bnad->bna.enet.छोड़ो_config.tx_छोड़ो) अणु
		छोड़ो_config.rx_छोड़ो = छोड़ोparam->rx_छोड़ो;
		छोड़ो_config.tx_छोड़ो = छोड़ोparam->tx_छोड़ो;
		spin_lock_irqsave(&bnad->bna_lock, flags);
		bna_enet_छोड़ो_config(&bnad->bna.enet, &छोड़ो_config);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
	पूर्ण
	mutex_unlock(&bnad->conf_mutex);
	वापस 0;
पूर्ण

अटल व्योम bnad_get_txf_strings(u8 **string, पूर्णांक f_num)
अणु
	ethtool_प्र_लिखो(string, "txf%d_ucast_octets", f_num);
	ethtool_प्र_लिखो(string, "txf%d_ucast", f_num);
	ethtool_प्र_लिखो(string, "txf%d_ucast_vlan", f_num);
	ethtool_प्र_लिखो(string, "txf%d_mcast_octets", f_num);
	ethtool_प्र_लिखो(string, "txf%d_mcast", f_num);
	ethtool_प्र_लिखो(string, "txf%d_mcast_vlan", f_num);
	ethtool_प्र_लिखो(string, "txf%d_bcast_octets", f_num);
	ethtool_प्र_लिखो(string, "txf%d_bcast", f_num);
	ethtool_प्र_लिखो(string, "txf%d_bcast_vlan", f_num);
	ethtool_प्र_लिखो(string, "txf%d_errors", f_num);
	ethtool_प्र_लिखो(string, "txf%d_filter_vlan", f_num);
	ethtool_प्र_लिखो(string, "txf%d_filter_mac_sa", f_num);
पूर्ण

अटल व्योम bnad_get_rxf_strings(u8 **string, पूर्णांक f_num)
अणु
	ethtool_प्र_लिखो(string, "rxf%d_ucast_octets", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_ucast", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_ucast_vlan", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_mcast_octets", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_mcast", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_mcast_vlan", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_bcast_octets", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_bcast", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_bcast_vlan", f_num);
	ethtool_प्र_लिखो(string, "rxf%d_frame_drops", f_num);
पूर्ण

अटल व्योम bnad_get_cq_strings(u8 **string, पूर्णांक q_num)
अणु
	ethtool_प्र_लिखो(string, "cq%d_producer_index", q_num);
	ethtool_प्र_लिखो(string, "cq%d_consumer_index", q_num);
	ethtool_प्र_लिखो(string, "cq%d_hw_producer_index", q_num);
	ethtool_प्र_लिखो(string, "cq%d_intr", q_num);
	ethtool_प्र_लिखो(string, "cq%d_poll", q_num);
	ethtool_प्र_लिखो(string, "cq%d_schedule", q_num);
	ethtool_प्र_लिखो(string, "cq%d_keep_poll", q_num);
	ethtool_प्र_लिखो(string, "cq%d_complete", q_num);
पूर्ण

अटल व्योम bnad_get_rxq_strings(u8 **string, पूर्णांक q_num)
अणु
	ethtool_प्र_लिखो(string, "rxq%d_packets", q_num);
	ethtool_प्र_लिखो(string, "rxq%d_bytes", q_num);
	ethtool_प्र_लिखो(string, "rxq%d_packets_with_error", q_num);
	ethtool_प्र_लिखो(string, "rxq%d_allocbuf_failed", q_num);
	ethtool_प्र_लिखो(string, "rxq%d_mapbuf_failed", q_num);
	ethtool_प्र_लिखो(string, "rxq%d_producer_index", q_num);
	ethtool_प्र_लिखो(string, "rxq%d_consumer_index", q_num);
पूर्ण

अटल व्योम bnad_get_txq_strings(u8 **string, पूर्णांक q_num)
अणु
	ethtool_प्र_लिखो(string, "txq%d_packets", q_num);
	ethtool_प्र_लिखो(string, "txq%d_bytes", q_num);
	ethtool_प्र_लिखो(string, "txq%d_producer_index", q_num);
	ethtool_प्र_लिखो(string, "txq%d_consumer_index", q_num);
	ethtool_प्र_लिखो(string, "txq%d_hw_consumer_index", q_num);
पूर्ण

अटल व्योम
bnad_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *string)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	पूर्णांक i, j, q_num;
	u32 bmap;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	mutex_lock(&bnad->conf_mutex);

	क्रम (i = 0; i < BNAD_ETHTOOL_STATS_NUM; i++) अणु
		BUG_ON(!(म_माप(bnad_net_stats_strings[i]) < ETH_GSTRING_LEN));
		ethtool_प्र_लिखो(&string, bnad_net_stats_strings[i]);
	पूर्ण

	bmap = bna_tx_rid_mask(&bnad->bna);
	क्रम (i = 0; bmap; i++) अणु
		अगर (bmap & 1)
			bnad_get_txf_strings(&string, i);
		bmap >>= 1;
	पूर्ण

	bmap = bna_rx_rid_mask(&bnad->bna);
	क्रम (i = 0; bmap; i++, bmap >>= 1) अणु
		अगर (bmap & 1)
			bnad_get_rxf_strings(&string, i);
		bmap >>= 1;
	पूर्ण

	q_num = 0;
	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		अगर (!bnad->rx_info[i].rx)
			जारी;
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++)
			bnad_get_cq_strings(&string, q_num++);
	पूर्ण

	q_num = 0;
	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		अगर (!bnad->rx_info[i].rx)
			जारी;
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++) अणु
			bnad_get_rxq_strings(&string, q_num++);
			अगर (bnad->rx_info[i].rx_ctrl[j].ccb &&
			    bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1] &&
			    bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1]->rxq)
				bnad_get_rxq_strings(&string, q_num++);
		पूर्ण
	पूर्ण

	q_num = 0;
	क्रम (i = 0; i < bnad->num_tx; i++) अणु
		अगर (!bnad->tx_info[i].tx)
			जारी;
		क्रम (j = 0; j < bnad->num_txq_per_tx; j++)
			bnad_get_txq_strings(&string, q_num++);
	पूर्ण

	mutex_unlock(&bnad->conf_mutex);
पूर्ण

अटल पूर्णांक
bnad_get_stats_count_locked(काष्ठा net_device *netdev)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	पूर्णांक i, j, count = 0, rxf_active_num = 0, txf_active_num = 0;
	u32 bmap;

	bmap = bna_tx_rid_mask(&bnad->bna);
	क्रम (i = 0; bmap; i++) अणु
		अगर (bmap & 1)
			txf_active_num++;
		bmap >>= 1;
	पूर्ण
	bmap = bna_rx_rid_mask(&bnad->bna);
	क्रम (i = 0; bmap; i++) अणु
		अगर (bmap & 1)
			rxf_active_num++;
		bmap >>= 1;
	पूर्ण
	count = BNAD_ETHTOOL_STATS_NUM +
		txf_active_num * BNAD_NUM_TXF_COUNTERS +
		rxf_active_num * BNAD_NUM_RXF_COUNTERS;

	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		अगर (!bnad->rx_info[i].rx)
			जारी;
		count += bnad->num_rxp_per_rx * BNAD_NUM_CQ_COUNTERS;
		count += bnad->num_rxp_per_rx * BNAD_NUM_RXQ_COUNTERS;
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++)
			अगर (bnad->rx_info[i].rx_ctrl[j].ccb &&
				bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1] &&
				bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1]->rxq)
				count +=  BNAD_NUM_RXQ_COUNTERS;
	पूर्ण

	क्रम (i = 0; i < bnad->num_tx; i++) अणु
		अगर (!bnad->tx_info[i].tx)
			जारी;
		count += bnad->num_txq_per_tx * BNAD_NUM_TXQ_COUNTERS;
	पूर्ण
	वापस count;
पूर्ण

अटल पूर्णांक
bnad_per_q_stats_fill(काष्ठा bnad *bnad, u64 *buf, पूर्णांक bi)
अणु
	पूर्णांक i, j;
	काष्ठा bna_rcb *rcb = शून्य;
	काष्ठा bna_tcb *tcb = शून्य;

	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		अगर (!bnad->rx_info[i].rx)
			जारी;
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++)
			अगर (bnad->rx_info[i].rx_ctrl[j].ccb &&
				bnad->rx_info[i].rx_ctrl[j].ccb->rcb[0] &&
				bnad->rx_info[i].rx_ctrl[j].ccb->rcb[0]->rxq) अणु
				buf[bi++] = bnad->rx_info[i].rx_ctrl[j].
						ccb->producer_index;
				buf[bi++] = 0; /* ccb->consumer_index */
				buf[bi++] = *(bnad->rx_info[i].rx_ctrl[j].
						ccb->hw_producer_index);

				buf[bi++] = bnad->rx_info[i].
						rx_ctrl[j].rx_पूर्णांकr_ctr;
				buf[bi++] = bnad->rx_info[i].
						rx_ctrl[j].rx_poll_ctr;
				buf[bi++] = bnad->rx_info[i].
						rx_ctrl[j].rx_schedule;
				buf[bi++] = bnad->rx_info[i].
						rx_ctrl[j].rx_keep_poll;
				buf[bi++] = bnad->rx_info[i].
						rx_ctrl[j].rx_complete;
			पूर्ण
	पूर्ण
	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		अगर (!bnad->rx_info[i].rx)
			जारी;
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++)
			अगर (bnad->rx_info[i].rx_ctrl[j].ccb) अणु
				अगर (bnad->rx_info[i].rx_ctrl[j].ccb->rcb[0] &&
					bnad->rx_info[i].rx_ctrl[j].ccb->
					rcb[0]->rxq) अणु
					rcb = bnad->rx_info[i].rx_ctrl[j].
							ccb->rcb[0];
					buf[bi++] = rcb->rxq->rx_packets;
					buf[bi++] = rcb->rxq->rx_bytes;
					buf[bi++] = rcb->rxq->
							rx_packets_with_error;
					buf[bi++] = rcb->rxq->
							rxbuf_alloc_failed;
					buf[bi++] = rcb->rxq->rxbuf_map_failed;
					buf[bi++] = rcb->producer_index;
					buf[bi++] = rcb->consumer_index;
				पूर्ण
				अगर (bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1] &&
					bnad->rx_info[i].rx_ctrl[j].ccb->
					rcb[1]->rxq) अणु
					rcb = bnad->rx_info[i].rx_ctrl[j].
								ccb->rcb[1];
					buf[bi++] = rcb->rxq->rx_packets;
					buf[bi++] = rcb->rxq->rx_bytes;
					buf[bi++] = rcb->rxq->
							rx_packets_with_error;
					buf[bi++] = rcb->rxq->
							rxbuf_alloc_failed;
					buf[bi++] = rcb->rxq->rxbuf_map_failed;
					buf[bi++] = rcb->producer_index;
					buf[bi++] = rcb->consumer_index;
				पूर्ण
			पूर्ण
	पूर्ण

	क्रम (i = 0; i < bnad->num_tx; i++) अणु
		अगर (!bnad->tx_info[i].tx)
			जारी;
		क्रम (j = 0; j < bnad->num_txq_per_tx; j++)
			अगर (bnad->tx_info[i].tcb[j] &&
				bnad->tx_info[i].tcb[j]->txq) अणु
				tcb = bnad->tx_info[i].tcb[j];
				buf[bi++] = tcb->txq->tx_packets;
				buf[bi++] = tcb->txq->tx_bytes;
				buf[bi++] = tcb->producer_index;
				buf[bi++] = tcb->consumer_index;
				buf[bi++] = *(tcb->hw_consumer_index);
			पूर्ण
	पूर्ण

	वापस bi;
पूर्ण

अटल व्योम
bnad_get_ethtool_stats(काष्ठा net_device *netdev, काष्ठा ethtool_stats *stats,
		       u64 *buf)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	पूर्णांक i, j, bi = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा rtnl_link_stats64 net_stats64;
	u64 *stats64;
	u32 bmap;

	mutex_lock(&bnad->conf_mutex);
	अगर (bnad_get_stats_count_locked(netdev) != stats->n_stats) अणु
		mutex_unlock(&bnad->conf_mutex);
		वापस;
	पूर्ण

	/*
	 * Used bna_lock to sync पढ़ोs from bna_stats, which is written
	 * under the same lock
	 */
	spin_lock_irqsave(&bnad->bna_lock, flags);

	स_रखो(&net_stats64, 0, माप(net_stats64));
	bnad_netdev_qstats_fill(bnad, &net_stats64);
	bnad_netdev_hwstats_fill(bnad, &net_stats64);

	buf[bi++] = net_stats64.rx_packets;
	buf[bi++] = net_stats64.tx_packets;
	buf[bi++] = net_stats64.rx_bytes;
	buf[bi++] = net_stats64.tx_bytes;
	buf[bi++] = net_stats64.rx_errors;
	buf[bi++] = net_stats64.tx_errors;
	buf[bi++] = net_stats64.rx_dropped;
	buf[bi++] = net_stats64.tx_dropped;
	buf[bi++] = net_stats64.multicast;
	buf[bi++] = net_stats64.collisions;
	buf[bi++] = net_stats64.rx_length_errors;
	buf[bi++] = net_stats64.rx_crc_errors;
	buf[bi++] = net_stats64.rx_frame_errors;
	buf[bi++] = net_stats64.tx_fअगरo_errors;

	/* Get netअगर_queue_stopped from stack */
	bnad->stats.drv_stats.netअगर_queue_stopped = netअगर_queue_stopped(netdev);

	/* Fill driver stats पूर्णांकo ethtool buffers */
	stats64 = (u64 *)&bnad->stats.drv_stats;
	क्रम (i = 0; i < माप(काष्ठा bnad_drv_stats) / माप(u64); i++)
		buf[bi++] = stats64[i];

	/* Fill hardware stats excluding the rxf/txf पूर्णांकo ethtool bufs */
	stats64 = (u64 *) &bnad->stats.bna_stats->hw_stats;
	क्रम (i = 0;
	     i < दुरत्व(काष्ठा bfi_enet_stats, rxf_stats[0]) /
		माप(u64);
	     i++)
		buf[bi++] = stats64[i];

	/* Fill txf stats पूर्णांकo ethtool buffers */
	bmap = bna_tx_rid_mask(&bnad->bna);
	क्रम (i = 0; bmap; i++) अणु
		अगर (bmap & 1) अणु
			stats64 = (u64 *)&bnad->stats.bna_stats->
						hw_stats.txf_stats[i];
			क्रम (j = 0; j < माप(काष्ठा bfi_enet_stats_txf) /
					माप(u64); j++)
				buf[bi++] = stats64[j];
		पूर्ण
		bmap >>= 1;
	पूर्ण

	/*  Fill rxf stats पूर्णांकo ethtool buffers */
	bmap = bna_rx_rid_mask(&bnad->bna);
	क्रम (i = 0; bmap; i++) अणु
		अगर (bmap & 1) अणु
			stats64 = (u64 *)&bnad->stats.bna_stats->
						hw_stats.rxf_stats[i];
			क्रम (j = 0; j < माप(काष्ठा bfi_enet_stats_rxf) /
					माप(u64); j++)
				buf[bi++] = stats64[j];
		पूर्ण
		bmap >>= 1;
	पूर्ण

	/* Fill per Q stats पूर्णांकo ethtool buffers */
	bi = bnad_per_q_stats_fill(bnad, buf, bi);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	mutex_unlock(&bnad->conf_mutex);
पूर्ण

अटल पूर्णांक
bnad_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस bnad_get_stats_count_locked(netdev);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32
bnad_get_flash_partition_by_offset(काष्ठा bnad *bnad, u32 offset,
				u32 *base_offset)
अणु
	काष्ठा bfa_flash_attr *flash_attr;
	काष्ठा bnad_iocmd_comp fcomp;
	u32 i, flash_part = 0, ret;
	अचिन्हित दीर्घ flags = 0;

	flash_attr = kzalloc(माप(काष्ठा bfa_flash_attr), GFP_KERNEL);
	अगर (!flash_attr)
		वापस 0;

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_flash_get_attr(&bnad->bna.flash, flash_attr,
				bnad_cb_completion, &fcomp);
	अगर (ret != BFA_STATUS_OK) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		kमुक्त(flash_attr);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	रुको_क्रम_completion(&fcomp.comp);
	ret = fcomp.comp_status;

	/* Check क्रम the flash type & base offset value */
	अगर (ret == BFA_STATUS_OK) अणु
		क्रम (i = 0; i < flash_attr->npart; i++) अणु
			अगर (offset >= flash_attr->part[i].part_off &&
			    offset < (flash_attr->part[i].part_off +
				      flash_attr->part[i].part_size)) अणु
				flash_part = flash_attr->part[i].part_type;
				*base_offset = flash_attr->part[i].part_off;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	kमुक्त(flash_attr);
	वापस flash_part;
पूर्ण

अटल पूर्णांक
bnad_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	वापस BFA_TOTAL_FLASH_SIZE;
पूर्ण

अटल पूर्णांक
bnad_get_eeprom(काष्ठा net_device *netdev, काष्ठा ethtool_eeprom *eeprom,
		u8 *bytes)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा bnad_iocmd_comp fcomp;
	u32 flash_part = 0, base_offset = 0;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;

	/* Fill the magic value */
	eeprom->magic = bnad->pcidev->venकरोr | (bnad->pcidev->device << 16);

	/* Query the flash partition based on the offset */
	flash_part = bnad_get_flash_partition_by_offset(bnad,
				eeprom->offset, &base_offset);
	अगर (flash_part == 0)
		वापस -EFAULT;

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_flash_पढ़ो_part(&bnad->bna.flash, flash_part,
				bnad->id, bytes, eeprom->len,
				eeprom->offset - base_offset,
				bnad_cb_completion, &fcomp);
	अगर (ret != BFA_STATUS_OK) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		जाओ करोne;
	पूर्ण

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	रुको_क्रम_completion(&fcomp.comp);
	ret = fcomp.comp_status;
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक
bnad_set_eeprom(काष्ठा net_device *netdev, काष्ठा ethtool_eeprom *eeprom,
		u8 *bytes)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा bnad_iocmd_comp fcomp;
	u32 flash_part = 0, base_offset = 0;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret = 0;

	/* Check अगर the flash update request is valid */
	अगर (eeprom->magic != (bnad->pcidev->venकरोr |
			     (bnad->pcidev->device << 16)))
		वापस -EINVAL;

	/* Query the flash partition based on the offset */
	flash_part = bnad_get_flash_partition_by_offset(bnad,
				eeprom->offset, &base_offset);
	अगर (flash_part == 0)
		वापस -EFAULT;

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bfa_nw_flash_update_part(&bnad->bna.flash, flash_part,
				bnad->id, bytes, eeprom->len,
				eeprom->offset - base_offset,
				bnad_cb_completion, &fcomp);
	अगर (ret != BFA_STATUS_OK) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		जाओ करोne;
	पूर्ण

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	रुको_क्रम_completion(&fcomp.comp);
	ret = fcomp.comp_status;
करोne:
	वापस ret;
पूर्ण

अटल पूर्णांक
bnad_flash_device(काष्ठा net_device *netdev, काष्ठा ethtool_flash *eflash)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा bnad_iocmd_comp fcomp;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = 0;

	ret = request_firmware(&fw, eflash->data, &bnad->pcidev->dev);
	अगर (ret) अणु
		netdev_err(netdev, "can't load firmware %s\n", eflash->data);
		जाओ out;
	पूर्ण

	fcomp.bnad = bnad;
	fcomp.comp_status = 0;

	init_completion(&fcomp.comp);
	spin_lock_irq(&bnad->bna_lock);
	ret = bfa_nw_flash_update_part(&bnad->bna.flash, BFA_FLASH_PART_FWIMG,
				bnad->id, (u8 *)fw->data, fw->size, 0,
				bnad_cb_completion, &fcomp);
	अगर (ret != BFA_STATUS_OK) अणु
		netdev_warn(netdev, "flash update failed with err=%d\n", ret);
		ret = -EIO;
		spin_unlock_irq(&bnad->bna_lock);
		जाओ out;
	पूर्ण

	spin_unlock_irq(&bnad->bna_lock);
	रुको_क्रम_completion(&fcomp.comp);
	अगर (fcomp.comp_status != BFA_STATUS_OK) अणु
		ret = -EIO;
		netdev_warn(netdev,
			    "firmware image update failed with err=%d\n",
			    fcomp.comp_status);
	पूर्ण
out:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bnad_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_TX_MAX_FRAMES |
				     ETHTOOL_COALESCE_USE_ADAPTIVE_RX,
	.get_drvinfo = bnad_get_drvinfo,
	.get_wol = bnad_get_wol,
	.get_link = ethtool_op_get_link,
	.get_coalesce = bnad_get_coalesce,
	.set_coalesce = bnad_set_coalesce,
	.get_ringparam = bnad_get_ringparam,
	.set_ringparam = bnad_set_ringparam,
	.get_छोड़ोparam = bnad_get_छोड़ोparam,
	.set_छोड़ोparam = bnad_set_छोड़ोparam,
	.get_strings = bnad_get_strings,
	.get_ethtool_stats = bnad_get_ethtool_stats,
	.get_sset_count = bnad_get_sset_count,
	.get_eeprom_len = bnad_get_eeprom_len,
	.get_eeprom = bnad_get_eeprom,
	.set_eeprom = bnad_set_eeprom,
	.flash_device = bnad_flash_device,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = bnad_get_link_ksettings,
	.set_link_ksettings = bnad_set_link_ksettings,
पूर्ण;

व्योम
bnad_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &bnad_ethtool_ops;
पूर्ण
