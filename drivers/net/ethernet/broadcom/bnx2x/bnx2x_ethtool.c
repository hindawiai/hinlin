<शैली गुरु>
/* bnx2x_ethtool.c: QLogic Everest network driver.
 *
 * Copyright (c) 2007-2013 Broadcom Corporation
 * Copyright (c) 2014 QLogic Corporation
 * All rights reserved
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Maपूर्णांकained by: Ariel Elior <ariel.elior@qlogic.com>
 * Written by: Eliezer Tamir
 * Based on code from Michael Chan's bnx2 driver
 * UDP CSUM errata workaround by Arik Gendelman
 * Slowpath and fastpath rework by Vladislav Zolotarov
 * Statistics and Link management by Yitchak Gertner
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/ethtool.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/crc32.h>
#समावेश "bnx2x.h"
#समावेश "bnx2x_cmn.h"
#समावेश "bnx2x_dump.h"
#समावेश "bnx2x_init.h"

/* Note: in the क्रमmat strings below %s is replaced by the queue-name which is
 * either its index or 'fcoe' क्रम the fcoe queue. Make sure the क्रमmat string
 * length करोes not exceed ETH_GSTRING_LEN - MAX_QUEUE_NAME_LEN + 2
 */
#घोषणा MAX_QUEUE_NAME_LEN	4
अटल स्थिर काष्ठा अणु
	दीर्घ offset;
	पूर्णांक size;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnx2x_q_stats_arr[] = अणु
/* 1 */	अणु Q_STATS_OFFSET32(total_bytes_received_hi), 8, "[%s]: rx_bytes" पूर्ण,
	अणु Q_STATS_OFFSET32(total_unicast_packets_received_hi),
						8, "[%s]: rx_ucast_packets" पूर्ण,
	अणु Q_STATS_OFFSET32(total_multicast_packets_received_hi),
						8, "[%s]: rx_mcast_packets" पूर्ण,
	अणु Q_STATS_OFFSET32(total_broadcast_packets_received_hi),
						8, "[%s]: rx_bcast_packets" पूर्ण,
	अणु Q_STATS_OFFSET32(no_buff_discard_hi),	8, "[%s]: rx_discards" पूर्ण,
	अणु Q_STATS_OFFSET32(rx_err_discard_pkt),
					 4, "[%s]: rx_phy_ip_err_discards"पूर्ण,
	अणु Q_STATS_OFFSET32(rx_skb_alloc_failed),
					 4, "[%s]: rx_skb_alloc_discard" पूर्ण,
	अणु Q_STATS_OFFSET32(hw_csum_err), 4, "[%s]: rx_csum_offload_errors" पूर्ण,
	अणु Q_STATS_OFFSET32(driver_xoff), 4, "[%s]: tx_exhaustion_events" पूर्ण,
	अणु Q_STATS_OFFSET32(total_bytes_transmitted_hi),	8, "[%s]: tx_bytes" पूर्ण,
/* 10 */अणु Q_STATS_OFFSET32(total_unicast_packets_transmitted_hi),
						8, "[%s]: tx_ucast_packets" पूर्ण,
	अणु Q_STATS_OFFSET32(total_multicast_packets_transmitted_hi),
						8, "[%s]: tx_mcast_packets" पूर्ण,
	अणु Q_STATS_OFFSET32(total_broadcast_packets_transmitted_hi),
						8, "[%s]: tx_bcast_packets" पूर्ण,
	अणु Q_STATS_OFFSET32(total_tpa_aggregations_hi),
						8, "[%s]: tpa_aggregations" पूर्ण,
	अणु Q_STATS_OFFSET32(total_tpa_aggregated_frames_hi),
					8, "[%s]: tpa_aggregated_frames"पूर्ण,
	अणु Q_STATS_OFFSET32(total_tpa_bytes_hi),	8, "[%s]: tpa_bytes"पूर्ण,
	अणु Q_STATS_OFFSET32(driver_filtered_tx_pkt),
					4, "[%s]: driver_filtered_tx_pkt" पूर्ण
पूर्ण;

#घोषणा BNX2X_NUM_Q_STATS ARRAY_SIZE(bnx2x_q_stats_arr)

अटल स्थिर काष्ठा अणु
	दीर्घ offset;
	पूर्णांक size;
	bool is_port_stat;
	अक्षर string[ETH_GSTRING_LEN];
पूर्ण bnx2x_stats_arr[] = अणु
/* 1 */	अणु STATS_OFFSET32(total_bytes_received_hi),
				8, false, "rx_bytes" पूर्ण,
	अणु STATS_OFFSET32(error_bytes_received_hi),
				8, false, "rx_error_bytes" पूर्ण,
	अणु STATS_OFFSET32(total_unicast_packets_received_hi),
				8, false, "rx_ucast_packets" पूर्ण,
	अणु STATS_OFFSET32(total_multicast_packets_received_hi),
				8, false, "rx_mcast_packets" पूर्ण,
	अणु STATS_OFFSET32(total_broadcast_packets_received_hi),
				8, false, "rx_bcast_packets" पूर्ण,
	अणु STATS_OFFSET32(rx_stat_करोt3statsfcserrors_hi),
				8, true, "rx_crc_errors" पूर्ण,
	अणु STATS_OFFSET32(rx_stat_करोt3statsalignmenterrors_hi),
				8, true, "rx_align_errors" पूर्ण,
	अणु STATS_OFFSET32(rx_stat_etherstatsundersizepkts_hi),
				8, true, "rx_undersize_packets" पूर्ण,
	अणु STATS_OFFSET32(etherstatsoverrsizepkts_hi),
				8, true, "rx_oversize_packets" पूर्ण,
/* 10 */अणु STATS_OFFSET32(rx_stat_etherstatsfragments_hi),
				8, true, "rx_fragments" पूर्ण,
	अणु STATS_OFFSET32(rx_stat_etherstatsjabbers_hi),
				8, true, "rx_jabbers" पूर्ण,
	अणु STATS_OFFSET32(no_buff_discard_hi),
				8, false, "rx_discards" पूर्ण,
	अणु STATS_OFFSET32(mac_filter_discard),
				4, true, "rx_filtered_packets" पूर्ण,
	अणु STATS_OFFSET32(mf_tag_discard),
				4, true, "rx_mf_tag_discard" पूर्ण,
	अणु STATS_OFFSET32(pfc_frames_received_hi),
				8, true, "pfc_frames_received" पूर्ण,
	अणु STATS_OFFSET32(pfc_frames_sent_hi),
				8, true, "pfc_frames_sent" पूर्ण,
	अणु STATS_OFFSET32(brb_drop_hi),
				8, true, "rx_brb_discard" पूर्ण,
	अणु STATS_OFFSET32(brb_truncate_hi),
				8, true, "rx_brb_truncate" पूर्ण,
	अणु STATS_OFFSET32(छोड़ो_frames_received_hi),
				8, true, "rx_pause_frames" पूर्ण,
	अणु STATS_OFFSET32(rx_stat_maccontrolframesreceived_hi),
				8, true, "rx_mac_ctrl_frames" पूर्ण,
	अणु STATS_OFFSET32(nig_समयr_max),
				4, true, "rx_constant_pause_events" पूर्ण,
/* 20 */अणु STATS_OFFSET32(rx_err_discard_pkt),
				4, false, "rx_phy_ip_err_discards"पूर्ण,
	अणु STATS_OFFSET32(rx_skb_alloc_failed),
				4, false, "rx_skb_alloc_discard" पूर्ण,
	अणु STATS_OFFSET32(hw_csum_err),
				4, false, "rx_csum_offload_errors" पूर्ण,
	अणु STATS_OFFSET32(driver_xoff),
				4, false, "tx_exhaustion_events" पूर्ण,
	अणु STATS_OFFSET32(total_bytes_transmitted_hi),
				8, false, "tx_bytes" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_अगरhcoutbaकरोctets_hi),
				8, true, "tx_error_bytes" पूर्ण,
	अणु STATS_OFFSET32(total_unicast_packets_transmitted_hi),
				8, false, "tx_ucast_packets" पूर्ण,
	अणु STATS_OFFSET32(total_multicast_packets_transmitted_hi),
				8, false, "tx_mcast_packets" पूर्ण,
	अणु STATS_OFFSET32(total_broadcast_packets_transmitted_hi),
				8, false, "tx_bcast_packets" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_करोt3statsपूर्णांकernalmactransmiterrors_hi),
				8, true, "tx_mac_errors" पूर्ण,
	अणु STATS_OFFSET32(rx_stat_करोt3statscarriersenseerrors_hi),
				8, true, "tx_carrier_errors" पूर्ण,
/* 30 */अणु STATS_OFFSET32(tx_stat_करोt3statssinglecollisionframes_hi),
				8, true, "tx_single_collisions" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_करोt3statsmultiplecollisionframes_hi),
				8, true, "tx_multi_collisions" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_करोt3statsdeferredtransmissions_hi),
				8, true, "tx_deferred" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_करोt3statsexcessivecollisions_hi),
				8, true, "tx_excess_collisions" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_करोt3statslatecollisions_hi),
				8, true, "tx_late_collisions" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_etherstatscollisions_hi),
				8, true, "tx_total_collisions" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_etherstatspkts64octets_hi),
				8, true, "tx_64_byte_packets" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_etherstatspkts65octetsto127octets_hi),
				8, true, "tx_65_to_127_byte_packets" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_etherstatspkts128octetsto255octets_hi),
				8, true, "tx_128_to_255_byte_packets" पूर्ण,
	अणु STATS_OFFSET32(tx_stat_etherstatspkts256octetsto511octets_hi),
				8, true, "tx_256_to_511_byte_packets" पूर्ण,
/* 40 */अणु STATS_OFFSET32(tx_stat_etherstatspkts512octetsto1023octets_hi),
				8, true, "tx_512_to_1023_byte_packets" पूर्ण,
	अणु STATS_OFFSET32(etherstatspkts1024octetsto1522octets_hi),
				8, true, "tx_1024_to_1522_byte_packets" पूर्ण,
	अणु STATS_OFFSET32(etherstatspktsover1522octets_hi),
				8, true, "tx_1523_to_9022_byte_packets" पूर्ण,
	अणु STATS_OFFSET32(छोड़ो_frames_sent_hi),
				8, true, "tx_pause_frames" पूर्ण,
	अणु STATS_OFFSET32(total_tpa_aggregations_hi),
				8, false, "tpa_aggregations" पूर्ण,
	अणु STATS_OFFSET32(total_tpa_aggregated_frames_hi),
				8, false, "tpa_aggregated_frames"पूर्ण,
	अणु STATS_OFFSET32(total_tpa_bytes_hi),
				8, false, "tpa_bytes"पूर्ण,
	अणु STATS_OFFSET32(recoverable_error),
				4, false, "recoverable_errors" पूर्ण,
	अणु STATS_OFFSET32(unrecoverable_error),
				4, false, "unrecoverable_errors" पूर्ण,
	अणु STATS_OFFSET32(driver_filtered_tx_pkt),
				4, false, "driver_filtered_tx_pkt" पूर्ण,
	अणु STATS_OFFSET32(eee_tx_lpi),
				4, true, "Tx LPI entry count"पूर्ण,
	अणु STATS_OFFSET32(ptp_skip_tx_ts),
				4, false, "ptp_skipped_tx_tstamp" पूर्ण,
पूर्ण;

#घोषणा BNX2X_NUM_STATS		ARRAY_SIZE(bnx2x_stats_arr)

अटल पूर्णांक bnx2x_get_port_type(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port_type;
	u32 phy_idx = bnx2x_get_cur_phy_idx(bp);
	चयन (bp->link_params.phy[phy_idx].media_type) अणु
	हाल ETH_PHY_SFPP_10G_FIBER:
	हाल ETH_PHY_SFP_1G_FIBER:
	हाल ETH_PHY_XFP_FIBER:
	हाल ETH_PHY_KR:
	हाल ETH_PHY_CX4:
		port_type = PORT_FIBRE;
		अवरोध;
	हाल ETH_PHY_DA_TWINAX:
		port_type = PORT_DA;
		अवरोध;
	हाल ETH_PHY_BASE_T:
		port_type = PORT_TP;
		अवरोध;
	हाल ETH_PHY_NOT_PRESENT:
		port_type = PORT_NONE;
		अवरोध;
	हाल ETH_PHY_UNSPECIFIED:
	शेष:
		port_type = PORT_OTHER;
		अवरोध;
	पूर्ण
	वापस port_type;
पूर्ण

अटल पूर्णांक bnx2x_get_vf_link_ksettings(काष्ठा net_device *dev,
				       काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u32 supported, advertising;

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (bp->state == BNX2X_STATE_OPEN) अणु
		अगर (test_bit(BNX2X_LINK_REPORT_FD,
			     &bp->vf_link_vars.link_report_flags))
			cmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			cmd->base.duplex = DUPLEX_HALF;

		cmd->base.speed = bp->vf_link_vars.line_speed;
	पूर्ण अन्यथा अणु
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.speed = SPEED_UNKNOWN;
	पूर्ण

	cmd->base.port		= PORT_OTHER;
	cmd->base.phy_address	= 0;
	cmd->base.स्वतःneg	= AUTONEG_DISABLE;

	DP(BNX2X_MSG_ETHTOOL, "ethtool_cmd: cmd %d\n"
	   "  supported 0x%x  advertising 0x%x  speed %u\n"
	   "  duplex %d  port %d  phy_address %d\n"
	   "  autoneg %d\n",
	   cmd->base.cmd, supported, advertising,
	   cmd->base.speed,
	   cmd->base.duplex, cmd->base.port, cmd->base.phy_address,
	   cmd->base.स्वतःneg);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_get_link_ksettings(काष्ठा net_device *dev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक cfg_idx = bnx2x_get_link_cfg_idx(bp);
	u32 media_type;
	u32 supported, advertising, lp_advertising;

	ethtool_convert_link_mode_to_legacy_u32(&lp_advertising,
						cmd->link_modes.lp_advertising);

	/* Dual Media boards present all available port types */
	supported = bp->port.supported[cfg_idx] |
		(bp->port.supported[cfg_idx ^ 1] &
		 (SUPPORTED_TP | SUPPORTED_FIBRE));
	advertising = bp->port.advertising[cfg_idx];
	media_type = bp->link_params.phy[bnx2x_get_cur_phy_idx(bp)].media_type;
	अगर (media_type == ETH_PHY_SFP_1G_FIBER) अणु
		supported &= ~(SUPPORTED_10000baseT_Full);
		advertising &= ~(ADVERTISED_10000baseT_Full);
	पूर्ण

	अगर ((bp->state == BNX2X_STATE_OPEN) && bp->link_vars.link_up &&
	    !(bp->flags & MF_FUNC_DIS)) अणु
		cmd->base.duplex = bp->link_vars.duplex;

		अगर (IS_MF(bp) && !BP_NOMCP(bp))
			cmd->base.speed = bnx2x_get_mf_speed(bp);
		अन्यथा
			cmd->base.speed = bp->link_vars.line_speed;
	पूर्ण अन्यथा अणु
		cmd->base.duplex = DUPLEX_UNKNOWN;
		cmd->base.speed = SPEED_UNKNOWN;
	पूर्ण

	cmd->base.port = bnx2x_get_port_type(bp);

	cmd->base.phy_address = bp->mdio.prtad;

	अगर (bp->link_params.req_line_speed[cfg_idx] == SPEED_AUTO_NEG)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	/* Publish LP advertised speeds and FC */
	अगर (bp->link_vars.link_status & LINK_STATUS_AUTO_NEGOTIATE_COMPLETE) अणु
		u32 status = bp->link_vars.link_status;

		lp_advertising |= ADVERTISED_Autoneg;
		अगर (status & LINK_STATUS_LINK_PARTNER_SYMMETRIC_PAUSE)
			lp_advertising |= ADVERTISED_Pause;
		अगर (status & LINK_STATUS_LINK_PARTNER_ASYMMETRIC_PAUSE)
			lp_advertising |= ADVERTISED_Asym_Pause;

		अगर (status & LINK_STATUS_LINK_PARTNER_10THD_CAPABLE)
			lp_advertising |= ADVERTISED_10baseT_Half;
		अगर (status & LINK_STATUS_LINK_PARTNER_10TFD_CAPABLE)
			lp_advertising |= ADVERTISED_10baseT_Full;
		अगर (status & LINK_STATUS_LINK_PARTNER_100TXHD_CAPABLE)
			lp_advertising |= ADVERTISED_100baseT_Half;
		अगर (status & LINK_STATUS_LINK_PARTNER_100TXFD_CAPABLE)
			lp_advertising |= ADVERTISED_100baseT_Full;
		अगर (status & LINK_STATUS_LINK_PARTNER_1000THD_CAPABLE)
			lp_advertising |= ADVERTISED_1000baseT_Half;
		अगर (status & LINK_STATUS_LINK_PARTNER_1000TFD_CAPABLE) अणु
			अगर (media_type == ETH_PHY_KR) अणु
				lp_advertising |=
					ADVERTISED_1000baseKX_Full;
			पूर्ण अन्यथा अणु
				lp_advertising |=
					ADVERTISED_1000baseT_Full;
			पूर्ण
		पूर्ण
		अगर (status & LINK_STATUS_LINK_PARTNER_2500XFD_CAPABLE)
			lp_advertising |= ADVERTISED_2500baseX_Full;
		अगर (status & LINK_STATUS_LINK_PARTNER_10GXFD_CAPABLE) अणु
			अगर (media_type == ETH_PHY_KR) अणु
				lp_advertising |=
					ADVERTISED_10000baseKR_Full;
			पूर्ण अन्यथा अणु
				lp_advertising |=
					ADVERTISED_10000baseT_Full;
			पूर्ण
		पूर्ण
		अगर (status & LINK_STATUS_LINK_PARTNER_20GXFD_CAPABLE)
			lp_advertising |= ADVERTISED_20000baseKR2_Full;
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.lp_advertising,
						lp_advertising);

	DP(BNX2X_MSG_ETHTOOL, "ethtool_cmd: cmd %d\n"
	   "  supported 0x%x  advertising 0x%x  speed %u\n"
	   "  duplex %d  port %d  phy_address %d\n"
	   "  autoneg %d\n",
	   cmd->base.cmd, supported, advertising,
	   cmd->base.speed,
	   cmd->base.duplex, cmd->base.port, cmd->base.phy_address,
	   cmd->base.स्वतःneg);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_set_link_ksettings(काष्ठा net_device *dev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u32 advertising, cfg_idx, old_multi_phy_config, new_multi_phy_config;
	u32 speed, phy_idx;
	u32 supported;
	u8 duplex = cmd->base.duplex;

	ethtool_convert_link_mode_to_legacy_u32(&supported,
						cmd->link_modes.supported);
	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (IS_MF_SD(bp))
		वापस 0;

	DP(BNX2X_MSG_ETHTOOL, "ethtool_cmd: cmd %d\n"
	   "  supported 0x%x  advertising 0x%x  speed %u\n"
	   "  duplex %d  port %d  phy_address %d\n"
	   "  autoneg %d\n",
	   cmd->base.cmd, supported, advertising,
	   cmd->base.speed,
	   cmd->base.duplex, cmd->base.port, cmd->base.phy_address,
	   cmd->base.स्वतःneg);

	speed = cmd->base.speed;

	/* If received a request क्रम an unknown duplex, assume full*/
	अगर (duplex == DUPLEX_UNKNOWN)
		duplex = DUPLEX_FULL;

	अगर (IS_MF_SI(bp)) अणु
		u32 part;
		u32 line_speed = bp->link_vars.line_speed;

		/* use 10G अगर no link detected */
		अगर (!line_speed)
			line_speed = 10000;

		अगर (bp->common.bc_ver < REQ_BC_VER_4_SET_MF_BW) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "To set speed BC %X or higher is required, please upgrade BC\n",
			   REQ_BC_VER_4_SET_MF_BW);
			वापस -EINVAL;
		पूर्ण

		part = (speed * 100) / line_speed;

		अगर (line_speed < speed || !part) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "Speed setting should be in a range from 1%% to 100%% of actual line speed\n");
			वापस -EINVAL;
		पूर्ण

		अगर (bp->state != BNX2X_STATE_OPEN)
			/* store value क्रम following "load" */
			bp->pending_max = part;
		अन्यथा
			bnx2x_update_max_mf_config(bp, part);

		वापस 0;
	पूर्ण

	cfg_idx = bnx2x_get_link_cfg_idx(bp);
	old_multi_phy_config = bp->link_params.multi_phy_config;
	अगर (cmd->base.port != bnx2x_get_port_type(bp)) अणु
		चयन (cmd->base.port) अणु
		हाल PORT_TP:
			अगर (!(bp->port.supported[0] & SUPPORTED_TP ||
			      bp->port.supported[1] & SUPPORTED_TP)) अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "Unsupported port type\n");
				वापस -EINVAL;
			पूर्ण
			bp->link_params.multi_phy_config &=
				~PORT_HW_CFG_PHY_SELECTION_MASK;
			अगर (bp->link_params.multi_phy_config &
			    PORT_HW_CFG_PHY_SWAPPED_ENABLED)
				bp->link_params.multi_phy_config |=
				PORT_HW_CFG_PHY_SELECTION_SECOND_PHY;
			अन्यथा
				bp->link_params.multi_phy_config |=
				PORT_HW_CFG_PHY_SELECTION_FIRST_PHY;
			अवरोध;
		हाल PORT_FIBRE:
		हाल PORT_DA:
		हाल PORT_NONE:
			अगर (!(bp->port.supported[0] & SUPPORTED_FIBRE ||
			      bp->port.supported[1] & SUPPORTED_FIBRE)) अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "Unsupported port type\n");
				वापस -EINVAL;
			पूर्ण
			bp->link_params.multi_phy_config &=
				~PORT_HW_CFG_PHY_SELECTION_MASK;
			अगर (bp->link_params.multi_phy_config &
			    PORT_HW_CFG_PHY_SWAPPED_ENABLED)
				bp->link_params.multi_phy_config |=
				PORT_HW_CFG_PHY_SELECTION_FIRST_PHY;
			अन्यथा
				bp->link_params.multi_phy_config |=
				PORT_HW_CFG_PHY_SELECTION_SECOND_PHY;
			अवरोध;
		शेष:
			DP(BNX2X_MSG_ETHTOOL, "Unsupported port type\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Save new config in हाल command complete successfully */
	new_multi_phy_config = bp->link_params.multi_phy_config;
	/* Get the new cfg_idx */
	cfg_idx = bnx2x_get_link_cfg_idx(bp);
	/* Restore old config in हाल command failed */
	bp->link_params.multi_phy_config = old_multi_phy_config;
	DP(BNX2X_MSG_ETHTOOL, "cfg_idx = %x\n", cfg_idx);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		u32 an_supported_speed = bp->port.supported[cfg_idx];
		अगर (bp->link_params.phy[EXT_PHY1].type ==
		    PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM84833)
			an_supported_speed |= (SUPPORTED_100baseT_Half |
					       SUPPORTED_100baseT_Full);
		अगर (!(bp->port.supported[cfg_idx] & SUPPORTED_Autoneg)) अणु
			DP(BNX2X_MSG_ETHTOOL, "Autoneg not supported\n");
			वापस -EINVAL;
		पूर्ण

		/* advertise the requested speed and duplex अगर supported */
		अगर (advertising & ~an_supported_speed) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "Advertisement parameters are not supported\n");
			वापस -EINVAL;
		पूर्ण

		bp->link_params.req_line_speed[cfg_idx] = SPEED_AUTO_NEG;
		bp->link_params.req_duplex[cfg_idx] = duplex;
		bp->port.advertising[cfg_idx] = (ADVERTISED_Autoneg |
					 advertising);
		अगर (advertising) अणु

			bp->link_params.speed_cap_mask[cfg_idx] = 0;
			अगर (advertising & ADVERTISED_10baseT_Half) अणु
				bp->link_params.speed_cap_mask[cfg_idx] |=
				PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_HALF;
			पूर्ण
			अगर (advertising & ADVERTISED_10baseT_Full)
				bp->link_params.speed_cap_mask[cfg_idx] |=
				PORT_HW_CFG_SPEED_CAPABILITY_D0_10M_FULL;

			अगर (advertising & ADVERTISED_100baseT_Full)
				bp->link_params.speed_cap_mask[cfg_idx] |=
				PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_FULL;

			अगर (advertising & ADVERTISED_100baseT_Half) अणु
				bp->link_params.speed_cap_mask[cfg_idx] |=
				     PORT_HW_CFG_SPEED_CAPABILITY_D0_100M_HALF;
			पूर्ण
			अगर (advertising & ADVERTISED_1000baseT_Half) अणु
				bp->link_params.speed_cap_mask[cfg_idx] |=
					PORT_HW_CFG_SPEED_CAPABILITY_D0_1G;
			पूर्ण
			अगर (advertising & (ADVERTISED_1000baseT_Full |
						ADVERTISED_1000baseKX_Full))
				bp->link_params.speed_cap_mask[cfg_idx] |=
					PORT_HW_CFG_SPEED_CAPABILITY_D0_1G;

			अगर (advertising & (ADVERTISED_10000baseT_Full |
						ADVERTISED_10000baseKX4_Full |
						ADVERTISED_10000baseKR_Full))
				bp->link_params.speed_cap_mask[cfg_idx] |=
					PORT_HW_CFG_SPEED_CAPABILITY_D0_10G;

			अगर (advertising & ADVERTISED_20000baseKR2_Full)
				bp->link_params.speed_cap_mask[cfg_idx] |=
					PORT_HW_CFG_SPEED_CAPABILITY_D0_20G;
		पूर्ण
	पूर्ण अन्यथा अणु /* क्रमced speed */
		/* advertise the requested speed and duplex अगर supported */
		चयन (speed) अणु
		हाल SPEED_10:
			अगर (duplex == DUPLEX_FULL) अणु
				अगर (!(bp->port.supported[cfg_idx] &
				      SUPPORTED_10baseT_Full)) अणु
					DP(BNX2X_MSG_ETHTOOL,
					   "10M full not supported\n");
					वापस -EINVAL;
				पूर्ण

				advertising = (ADVERTISED_10baseT_Full |
					       ADVERTISED_TP);
			पूर्ण अन्यथा अणु
				अगर (!(bp->port.supported[cfg_idx] &
				      SUPPORTED_10baseT_Half)) अणु
					DP(BNX2X_MSG_ETHTOOL,
					   "10M half not supported\n");
					वापस -EINVAL;
				पूर्ण

				advertising = (ADVERTISED_10baseT_Half |
					       ADVERTISED_TP);
			पूर्ण
			अवरोध;

		हाल SPEED_100:
			अगर (duplex == DUPLEX_FULL) अणु
				अगर (!(bp->port.supported[cfg_idx] &
						SUPPORTED_100baseT_Full)) अणु
					DP(BNX2X_MSG_ETHTOOL,
					   "100M full not supported\n");
					वापस -EINVAL;
				पूर्ण

				advertising = (ADVERTISED_100baseT_Full |
					       ADVERTISED_TP);
			पूर्ण अन्यथा अणु
				अगर (!(bp->port.supported[cfg_idx] &
						SUPPORTED_100baseT_Half)) अणु
					DP(BNX2X_MSG_ETHTOOL,
					   "100M half not supported\n");
					वापस -EINVAL;
				पूर्ण

				advertising = (ADVERTISED_100baseT_Half |
					       ADVERTISED_TP);
			पूर्ण
			अवरोध;

		हाल SPEED_1000:
			अगर (duplex != DUPLEX_FULL) अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "1G half not supported\n");
				वापस -EINVAL;
			पूर्ण

			अगर (bp->port.supported[cfg_idx] &
			     SUPPORTED_1000baseT_Full) अणु
				advertising = (ADVERTISED_1000baseT_Full |
					       ADVERTISED_TP);

			पूर्ण अन्यथा अगर (bp->port.supported[cfg_idx] &
				   SUPPORTED_1000baseKX_Full) अणु
				advertising = ADVERTISED_1000baseKX_Full;
			पूर्ण अन्यथा अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "1G full not supported\n");
				वापस -EINVAL;
			पूर्ण

			अवरोध;

		हाल SPEED_2500:
			अगर (duplex != DUPLEX_FULL) अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "2.5G half not supported\n");
				वापस -EINVAL;
			पूर्ण

			अगर (!(bp->port.supported[cfg_idx]
			      & SUPPORTED_2500baseX_Full)) अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "2.5G full not supported\n");
				वापस -EINVAL;
			पूर्ण

			advertising = (ADVERTISED_2500baseX_Full |
				       ADVERTISED_TP);
			अवरोध;

		हाल SPEED_10000:
			अगर (duplex != DUPLEX_FULL) अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "10G half not supported\n");
				वापस -EINVAL;
			पूर्ण
			phy_idx = bnx2x_get_cur_phy_idx(bp);
			अगर ((bp->port.supported[cfg_idx] &
			     SUPPORTED_10000baseT_Full) &&
			    (bp->link_params.phy[phy_idx].media_type !=
			     ETH_PHY_SFP_1G_FIBER)) अणु
				advertising = (ADVERTISED_10000baseT_Full |
					       ADVERTISED_FIBRE);
			पूर्ण अन्यथा अगर (bp->port.supported[cfg_idx] &
			       SUPPORTED_10000baseKR_Full) अणु
				advertising = (ADVERTISED_10000baseKR_Full |
					       ADVERTISED_FIBRE);
			पूर्ण अन्यथा अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "10G full not supported\n");
				वापस -EINVAL;
			पूर्ण

			अवरोध;

		शेष:
			DP(BNX2X_MSG_ETHTOOL, "Unsupported speed %u\n", speed);
			वापस -EINVAL;
		पूर्ण

		bp->link_params.req_line_speed[cfg_idx] = speed;
		bp->link_params.req_duplex[cfg_idx] = duplex;
		bp->port.advertising[cfg_idx] = advertising;
	पूर्ण

	DP(BNX2X_MSG_ETHTOOL, "req_line_speed %d\n"
	   "  req_duplex %d  advertising 0x%x\n",
	   bp->link_params.req_line_speed[cfg_idx],
	   bp->link_params.req_duplex[cfg_idx],
	   bp->port.advertising[cfg_idx]);

	/* Set new config */
	bp->link_params.multi_phy_config = new_multi_phy_config;
	अगर (netअगर_running(dev)) अणु
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);
		bnx2x_क्रमce_link_reset(bp);
		bnx2x_link_set(bp);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DUMP_ALL_PRESETS		0x1FFF
#घोषणा DUMP_MAX_PRESETS		13

अटल पूर्णांक __bnx2x_get_preset_regs_len(काष्ठा bnx2x *bp, u32 preset)
अणु
	अगर (CHIP_IS_E1(bp))
		वापस dump_num_रेजिस्टरs[0][preset-1];
	अन्यथा अगर (CHIP_IS_E1H(bp))
		वापस dump_num_रेजिस्टरs[1][preset-1];
	अन्यथा अगर (CHIP_IS_E2(bp))
		वापस dump_num_रेजिस्टरs[2][preset-1];
	अन्यथा अगर (CHIP_IS_E3A0(bp))
		वापस dump_num_रेजिस्टरs[3][preset-1];
	अन्यथा अगर (CHIP_IS_E3B0(bp))
		वापस dump_num_रेजिस्टरs[4][preset-1];
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक __bnx2x_get_regs_len(काष्ठा bnx2x *bp)
अणु
	u32 preset_idx;
	पूर्णांक regdump_len = 0;

	/* Calculate the total preset regs length */
	क्रम (preset_idx = 1; preset_idx <= DUMP_MAX_PRESETS; preset_idx++)
		regdump_len += __bnx2x_get_preset_regs_len(bp, preset_idx);

	वापस regdump_len;
पूर्ण

अटल पूर्णांक bnx2x_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक regdump_len = 0;

	अगर (IS_VF(bp))
		वापस 0;

	regdump_len = __bnx2x_get_regs_len(bp);
	regdump_len *= 4;
	regdump_len += माप(काष्ठा dump_header);

	वापस regdump_len;
पूर्ण

#घोषणा IS_E1_REG(chips)	((chips & DUMP_CHIP_E1) == DUMP_CHIP_E1)
#घोषणा IS_E1H_REG(chips)	((chips & DUMP_CHIP_E1H) == DUMP_CHIP_E1H)
#घोषणा IS_E2_REG(chips)	((chips & DUMP_CHIP_E2) == DUMP_CHIP_E2)
#घोषणा IS_E3A0_REG(chips)	((chips & DUMP_CHIP_E3A0) == DUMP_CHIP_E3A0)
#घोषणा IS_E3B0_REG(chips)	((chips & DUMP_CHIP_E3B0) == DUMP_CHIP_E3B0)

#घोषणा IS_REG_IN_PRESET(presets, idx)  \
		((presets & (1 << (idx-1))) == (1 << (idx-1)))

/******* Paged रेजिस्टरs info selectors ********/
अटल स्थिर u32 *__bnx2x_get_page_addr_ar(काष्ठा bnx2x *bp)
अणु
	अगर (CHIP_IS_E2(bp))
		वापस page_vals_e2;
	अन्यथा अगर (CHIP_IS_E3(bp))
		वापस page_vals_e3;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल u32 __bnx2x_get_page_reg_num(काष्ठा bnx2x *bp)
अणु
	अगर (CHIP_IS_E2(bp))
		वापस PAGE_MODE_VALUES_E2;
	अन्यथा अगर (CHIP_IS_E3(bp))
		वापस PAGE_MODE_VALUES_E3;
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर u32 *__bnx2x_get_page_ग_लिखो_ar(काष्ठा bnx2x *bp)
अणु
	अगर (CHIP_IS_E2(bp))
		वापस page_ग_लिखो_regs_e2;
	अन्यथा अगर (CHIP_IS_E3(bp))
		वापस page_ग_लिखो_regs_e3;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल u32 __bnx2x_get_page_ग_लिखो_num(काष्ठा bnx2x *bp)
अणु
	अगर (CHIP_IS_E2(bp))
		वापस PAGE_WRITE_REGS_E2;
	अन्यथा अगर (CHIP_IS_E3(bp))
		वापस PAGE_WRITE_REGS_E3;
	अन्यथा
		वापस 0;
पूर्ण

अटल स्थिर काष्ठा reg_addr *__bnx2x_get_page_पढ़ो_ar(काष्ठा bnx2x *bp)
अणु
	अगर (CHIP_IS_E2(bp))
		वापस page_पढ़ो_regs_e2;
	अन्यथा अगर (CHIP_IS_E3(bp))
		वापस page_पढ़ो_regs_e3;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल u32 __bnx2x_get_page_पढ़ो_num(काष्ठा bnx2x *bp)
अणु
	अगर (CHIP_IS_E2(bp))
		वापस PAGE_READ_REGS_E2;
	अन्यथा अगर (CHIP_IS_E3(bp))
		वापस PAGE_READ_REGS_E3;
	अन्यथा
		वापस 0;
पूर्ण

अटल bool bnx2x_is_reg_in_chip(काष्ठा bnx2x *bp,
				       स्थिर काष्ठा reg_addr *reg_info)
अणु
	अगर (CHIP_IS_E1(bp))
		वापस IS_E1_REG(reg_info->chips);
	अन्यथा अगर (CHIP_IS_E1H(bp))
		वापस IS_E1H_REG(reg_info->chips);
	अन्यथा अगर (CHIP_IS_E2(bp))
		वापस IS_E2_REG(reg_info->chips);
	अन्यथा अगर (CHIP_IS_E3A0(bp))
		वापस IS_E3A0_REG(reg_info->chips);
	अन्यथा अगर (CHIP_IS_E3B0(bp))
		वापस IS_E3B0_REG(reg_info->chips);
	अन्यथा
		वापस false;
पूर्ण

अटल bool bnx2x_is_wreg_in_chip(काष्ठा bnx2x *bp,
	स्थिर काष्ठा wreg_addr *wreg_info)
अणु
	अगर (CHIP_IS_E1(bp))
		वापस IS_E1_REG(wreg_info->chips);
	अन्यथा अगर (CHIP_IS_E1H(bp))
		वापस IS_E1H_REG(wreg_info->chips);
	अन्यथा अगर (CHIP_IS_E2(bp))
		वापस IS_E2_REG(wreg_info->chips);
	अन्यथा अगर (CHIP_IS_E3A0(bp))
		वापस IS_E3A0_REG(wreg_info->chips);
	अन्यथा अगर (CHIP_IS_E3B0(bp))
		वापस IS_E3B0_REG(wreg_info->chips);
	अन्यथा
		वापस false;
पूर्ण

/**
 * bnx2x_पढ़ो_pages_regs - पढ़ो "paged" रेजिस्टरs
 *
 * @bp:		device handle
 * @p:		output buffer
 * @preset:	the preset value
 *
 * Reads "paged" memories: memories that may only be पढ़ो by first writing to a
 * specअगरic address ("write address") and then पढ़ोing from a specअगरic address
 * ("read address"). There may be more than one ग_लिखो address per "page" and
 * more than one पढ़ो address per ग_लिखो address.
 */
अटल व्योम bnx2x_पढ़ो_pages_regs(काष्ठा bnx2x *bp, u32 *p, u32 preset)
अणु
	u32 i, j, k, n;

	/* addresses of the paged रेजिस्टरs */
	स्थिर u32 *page_addr = __bnx2x_get_page_addr_ar(bp);
	/* number of paged रेजिस्टरs */
	पूर्णांक num_pages = __bnx2x_get_page_reg_num(bp);
	/* ग_लिखो addresses */
	स्थिर u32 *ग_लिखो_addr = __bnx2x_get_page_ग_लिखो_ar(bp);
	/* number of ग_लिखो addresses */
	पूर्णांक ग_लिखो_num = __bnx2x_get_page_ग_लिखो_num(bp);
	/* पढ़ो addresses info */
	स्थिर काष्ठा reg_addr *पढ़ो_addr = __bnx2x_get_page_पढ़ो_ar(bp);
	/* number of पढ़ो addresses */
	पूर्णांक पढ़ो_num = __bnx2x_get_page_पढ़ो_num(bp);
	u32 addr, size;

	क्रम (i = 0; i < num_pages; i++) अणु
		क्रम (j = 0; j < ग_लिखो_num; j++) अणु
			REG_WR(bp, ग_लिखो_addr[j], page_addr[i]);

			क्रम (k = 0; k < पढ़ो_num; k++) अणु
				अगर (IS_REG_IN_PRESET(पढ़ो_addr[k].presets,
						     preset)) अणु
					size = पढ़ो_addr[k].size;
					क्रम (n = 0; n < size; n++) अणु
						addr = पढ़ो_addr[k].addr + n*4;
						*p++ = REG_RD(bp, addr);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __bnx2x_get_preset_regs(काष्ठा bnx2x *bp, u32 *p, u32 preset)
अणु
	u32 i, j, addr;
	स्थिर काष्ठा wreg_addr *wreg_addr_p = शून्य;

	अगर (CHIP_IS_E1(bp))
		wreg_addr_p = &wreg_addr_e1;
	अन्यथा अगर (CHIP_IS_E1H(bp))
		wreg_addr_p = &wreg_addr_e1h;
	अन्यथा अगर (CHIP_IS_E2(bp))
		wreg_addr_p = &wreg_addr_e2;
	अन्यथा अगर (CHIP_IS_E3A0(bp))
		wreg_addr_p = &wreg_addr_e3;
	अन्यथा अगर (CHIP_IS_E3B0(bp))
		wreg_addr_p = &wreg_addr_e3b0;

	/* Read the idle_chk रेजिस्टरs */
	क्रम (i = 0; i < IDLE_REGS_COUNT; i++) अणु
		अगर (bnx2x_is_reg_in_chip(bp, &idle_reg_addrs[i]) &&
		    IS_REG_IN_PRESET(idle_reg_addrs[i].presets, preset)) अणु
			क्रम (j = 0; j < idle_reg_addrs[i].size; j++)
				*p++ = REG_RD(bp, idle_reg_addrs[i].addr + j*4);
		पूर्ण
	पूर्ण

	/* Read the regular रेजिस्टरs */
	क्रम (i = 0; i < REGS_COUNT; i++) अणु
		अगर (bnx2x_is_reg_in_chip(bp, &reg_addrs[i]) &&
		    IS_REG_IN_PRESET(reg_addrs[i].presets, preset)) अणु
			क्रम (j = 0; j < reg_addrs[i].size; j++)
				*p++ = REG_RD(bp, reg_addrs[i].addr + j*4);
		पूर्ण
	पूर्ण

	/* Read the CAM रेजिस्टरs */
	अगर (bnx2x_is_wreg_in_chip(bp, wreg_addr_p) &&
	    IS_REG_IN_PRESET(wreg_addr_p->presets, preset)) अणु
		क्रम (i = 0; i < wreg_addr_p->size; i++) अणु
			*p++ = REG_RD(bp, wreg_addr_p->addr + i*4);

			/* In हाल of wreg_addr रेजिस्टर, पढ़ो additional
			   रेजिस्टरs from पढ़ो_regs array
			*/
			क्रम (j = 0; j < wreg_addr_p->पढ़ो_regs_count; j++) अणु
				addr = *(wreg_addr_p->पढ़ो_regs);
				*p++ = REG_RD(bp, addr + j*4);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Paged रेजिस्टरs are supported in E2 & E3 only */
	अगर (CHIP_IS_E2(bp) || CHIP_IS_E3(bp)) अणु
		/* Read "paged" रेजिस्टरs */
		bnx2x_पढ़ो_pages_regs(bp, p, preset);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __bnx2x_get_regs(काष्ठा bnx2x *bp, u32 *p)
अणु
	u32 preset_idx;

	/* Read all रेजिस्टरs, by पढ़ोing all preset रेजिस्टरs */
	क्रम (preset_idx = 1; preset_idx <= DUMP_MAX_PRESETS; preset_idx++) अणु
		/* Skip presets with IOR */
		अगर ((preset_idx == 2) ||
		    (preset_idx == 5) ||
		    (preset_idx == 8) ||
		    (preset_idx == 11))
			जारी;
		__bnx2x_get_preset_regs(bp, p, preset_idx);
		p += __bnx2x_get_preset_regs_len(bp, preset_idx);
	पूर्ण
पूर्ण

अटल व्योम bnx2x_get_regs(काष्ठा net_device *dev,
			   काष्ठा ethtool_regs *regs, व्योम *_p)
अणु
	u32 *p = _p;
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा dump_header dump_hdr = अणु0पूर्ण;

	regs->version = 2;
	स_रखो(p, 0, regs->len);

	अगर (!netअगर_running(bp->dev))
		वापस;

	/* Disable parity attentions as दीर्घ as following dump may
	 * cause false alarms by पढ़ोing never written रेजिस्टरs. We
	 * will re-enable parity attentions right after the dump.
	 */

	bnx2x_disable_blocks_parity(bp);

	dump_hdr.header_size = (माप(काष्ठा dump_header) / 4) - 1;
	dump_hdr.preset = DUMP_ALL_PRESETS;
	dump_hdr.version = BNX2X_DUMP_VERSION;

	/* dump_meta_data presents OR of CHIP and PATH. */
	अगर (CHIP_IS_E1(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E1;
	पूर्ण अन्यथा अगर (CHIP_IS_E1H(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E1H;
	पूर्ण अन्यथा अगर (CHIP_IS_E2(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E2 |
		(BP_PATH(bp) ? DUMP_PATH_1 : DUMP_PATH_0);
	पूर्ण अन्यथा अगर (CHIP_IS_E3A0(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E3A0 |
		(BP_PATH(bp) ? DUMP_PATH_1 : DUMP_PATH_0);
	पूर्ण अन्यथा अगर (CHIP_IS_E3B0(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E3B0 |
		(BP_PATH(bp) ? DUMP_PATH_1 : DUMP_PATH_0);
	पूर्ण

	स_नकल(p, &dump_hdr, माप(काष्ठा dump_header));
	p += dump_hdr.header_size + 1;

	/* This isn't really an error, but since attention handling is going
	 * to prपूर्णांक the GRC समयouts using this macro, we use the same.
	 */
	BNX2X_ERR("Generating register dump. Might trigger harmless GRC timeouts\n");

	/* Actually पढ़ो the रेजिस्टरs */
	__bnx2x_get_regs(bp, p);

	/* Re-enable parity attentions */
	bnx2x_clear_blocks_parity(bp);
	bnx2x_enable_blocks_parity(bp);
पूर्ण

अटल पूर्णांक bnx2x_get_preset_regs_len(काष्ठा net_device *dev, u32 preset)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक regdump_len = 0;

	regdump_len = __bnx2x_get_preset_regs_len(bp, preset);
	regdump_len *= 4;
	regdump_len += माप(काष्ठा dump_header);

	वापस regdump_len;
पूर्ण

अटल पूर्णांक bnx2x_set_dump(काष्ठा net_device *dev, काष्ठा ethtool_dump *val)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	/* Use the ethtool_dump "flag" field as the dump preset index */
	अगर (val->flag < 1 || val->flag > DUMP_MAX_PRESETS)
		वापस -EINVAL;

	bp->dump_preset_idx = val->flag;
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_get_dump_flag(काष्ठा net_device *dev,
			       काष्ठा ethtool_dump *dump)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	dump->version = BNX2X_DUMP_VERSION;
	dump->flag = bp->dump_preset_idx;
	/* Calculate the requested preset idx length */
	dump->len = bnx2x_get_preset_regs_len(dev, bp->dump_preset_idx);
	DP(BNX2X_MSG_ETHTOOL, "Get dump preset %d length=%d\n",
	   bp->dump_preset_idx, dump->len);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_get_dump_data(काष्ठा net_device *dev,
			       काष्ठा ethtool_dump *dump,
			       व्योम *buffer)
अणु
	u32 *p = buffer;
	काष्ठा bnx2x *bp = netdev_priv(dev);
	काष्ठा dump_header dump_hdr = अणु0पूर्ण;

	/* Disable parity attentions as दीर्घ as following dump may
	 * cause false alarms by पढ़ोing never written रेजिस्टरs. We
	 * will re-enable parity attentions right after the dump.
	 */

	bnx2x_disable_blocks_parity(bp);

	dump_hdr.header_size = (माप(काष्ठा dump_header) / 4) - 1;
	dump_hdr.preset = bp->dump_preset_idx;
	dump_hdr.version = BNX2X_DUMP_VERSION;

	DP(BNX2X_MSG_ETHTOOL, "Get dump data of preset %d\n", dump_hdr.preset);

	/* dump_meta_data presents OR of CHIP and PATH. */
	अगर (CHIP_IS_E1(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E1;
	पूर्ण अन्यथा अगर (CHIP_IS_E1H(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E1H;
	पूर्ण अन्यथा अगर (CHIP_IS_E2(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E2 |
		(BP_PATH(bp) ? DUMP_PATH_1 : DUMP_PATH_0);
	पूर्ण अन्यथा अगर (CHIP_IS_E3A0(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E3A0 |
		(BP_PATH(bp) ? DUMP_PATH_1 : DUMP_PATH_0);
	पूर्ण अन्यथा अगर (CHIP_IS_E3B0(bp)) अणु
		dump_hdr.dump_meta_data = DUMP_CHIP_E3B0 |
		(BP_PATH(bp) ? DUMP_PATH_1 : DUMP_PATH_0);
	पूर्ण

	स_नकल(p, &dump_hdr, माप(काष्ठा dump_header));
	p += dump_hdr.header_size + 1;

	/* Actually पढ़ो the रेजिस्टरs */
	__bnx2x_get_preset_regs(bp, p, dump_hdr.preset);

	/* Re-enable parity attentions */
	bnx2x_clear_blocks_parity(bp);
	bnx2x_enable_blocks_parity(bp);

	वापस 0;
पूर्ण

अटल व्योम bnx2x_get_drvinfo(काष्ठा net_device *dev,
			      काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	अक्षर version[ETHTOOL_FWVERS_LEN];
	पूर्णांक ext_dev_info_offset;
	u32 mbi;

	strlcpy(info->driver, DRV_MODULE_NAME, माप(info->driver));

	अगर (SHMEM2_HAS(bp, extended_dev_info_shared_addr)) अणु
		ext_dev_info_offset = SHMEM2_RD(bp,
						extended_dev_info_shared_addr);
		mbi = REG_RD(bp, ext_dev_info_offset +
			     दुरत्व(काष्ठा extended_dev_info_shared_cfg,
				      mbi_version));
		अगर (mbi) अणु
			स_रखो(version, 0, माप(version));
			snम_लिखो(version, ETHTOOL_FWVERS_LEN, "mbi %d.%d.%d ",
				 (mbi & 0xff000000) >> 24,
				 (mbi & 0x00ff0000) >> 16,
				 (mbi & 0x0000ff00) >> 8);
			strlcpy(info->fw_version, version,
				माप(info->fw_version));
		पूर्ण
	पूर्ण

	स_रखो(version, 0, माप(version));
	bnx2x_fill_fw_str(bp, version, ETHTOOL_FWVERS_LEN);
	strlcat(info->fw_version, version, माप(info->fw_version));

	strlcpy(info->bus_info, pci_name(bp->pdev), माप(info->bus_info));
पूर्ण

अटल व्योम bnx2x_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (bp->flags & NO_WOL_FLAG) अणु
		wol->supported = 0;
		wol->wolopts = 0;
	पूर्ण अन्यथा अणु
		wol->supported = WAKE_MAGIC;
		अगर (bp->wol)
			wol->wolopts = WAKE_MAGIC;
		अन्यथा
			wol->wolopts = 0;
	पूर्ण
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक bnx2x_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (wol->wolopts & ~WAKE_MAGIC) अणु
		DP(BNX2X_MSG_ETHTOOL, "WOL not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (wol->wolopts & WAKE_MAGIC) अणु
		अगर (bp->flags & NO_WOL_FLAG) अणु
			DP(BNX2X_MSG_ETHTOOL, "WOL not supported\n");
			वापस -EINVAL;
		पूर्ण
		bp->wol = 1;
	पूर्ण अन्यथा
		bp->wol = 0;

	अगर (SHMEM2_HAS(bp, curr_cfg))
		SHMEM2_WR(bp, curr_cfg, CURR_CFG_MET_OS);

	वापस 0;
पूर्ण

अटल u32 bnx2x_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	वापस bp->msg_enable;
पूर्ण

अटल व्योम bnx2x_set_msglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (capable(CAP_NET_ADMIN)) अणु
		/* dump MCP trace */
		अगर (IS_PF(bp) && (level & BNX2X_MSG_MCP))
			bnx2x_fw_dump_lvl(bp, KERN_INFO);
		bp->msg_enable = level;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (!bp->port.pmf)
		वापस 0;

	अगर (netअगर_running(dev)) अणु
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);
		bnx2x_क्रमce_link_reset(bp);
		bnx2x_link_set(bp);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 bnx2x_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (bp->flags & MF_FUNC_DIS || (bp->state != BNX2X_STATE_OPEN))
		वापस 0;

	अगर (IS_VF(bp))
		वापस !test_bit(BNX2X_LINK_REPORT_LINK_DOWN,
				 &bp->vf_link_vars.link_report_flags);

	वापस bp->link_vars.link_up;
पूर्ण

अटल पूर्णांक bnx2x_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	वापस bp->common.flash_size;
पूर्ण

/* Per pf misc lock must be acquired beक्रमe the per port mcp lock. Otherwise,
 * had we करोne things the other way around, अगर two pfs from the same port would
 * attempt to access nvram at the same समय, we could run पूर्णांकo a scenario such
 * as:
 * pf A takes the port lock.
 * pf B succeeds in taking the same lock since they are from the same port.
 * pf A takes the per pf misc lock. Perक्रमms eeprom access.
 * pf A finishes. Unlocks the per pf misc lock.
 * Pf B takes the lock and proceeds to perक्रमm it's own access.
 * pf A unlocks the per port lock, जबतक pf B is still working (!).
 * mcp takes the per port lock and corrupts pf B's access (and/or has it's own
 * access corrupted by pf B)
 */
अटल पूर्णांक bnx2x_acquire_nvram_lock(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक count, i;
	u32 val;

	/* acquire HW lock: protect against other PFs in PF Direct Assignment */
	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_NVRAM);

	/* adjust समयout क्रम emulation/FPGA */
	count = BNX2X_NVRAM_TIMEOUT_COUNT;
	अगर (CHIP_REV_IS_SLOW(bp))
		count *= 100;

	/* request access to nvram पूर्णांकerface */
	REG_WR(bp, MCP_REG_MCPR_NVM_SW_ARB,
	       (MCPR_NVM_SW_ARB_ARB_REQ_SET1 << port));

	क्रम (i = 0; i < count*10; i++) अणु
		val = REG_RD(bp, MCP_REG_MCPR_NVM_SW_ARB);
		अगर (val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port))
			अवरोध;

		udelay(5);
	पूर्ण

	अगर (!(val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port))) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot get access to nvram interface\n");
		bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_NVRAM);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_release_nvram_lock(काष्ठा bnx2x *bp)
अणु
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक count, i;
	u32 val;

	/* adjust समयout क्रम emulation/FPGA */
	count = BNX2X_NVRAM_TIMEOUT_COUNT;
	अगर (CHIP_REV_IS_SLOW(bp))
		count *= 100;

	/* relinquish nvram पूर्णांकerface */
	REG_WR(bp, MCP_REG_MCPR_NVM_SW_ARB,
	       (MCPR_NVM_SW_ARB_ARB_REQ_CLR1 << port));

	क्रम (i = 0; i < count*10; i++) अणु
		val = REG_RD(bp, MCP_REG_MCPR_NVM_SW_ARB);
		अगर (!(val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port)))
			अवरोध;

		udelay(5);
	पूर्ण

	अगर (val & (MCPR_NVM_SW_ARB_ARB_ARB1 << port)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot free access to nvram interface\n");
		वापस -EBUSY;
	पूर्ण

	/* release HW lock: protect against other PFs in PF Direct Assignment */
	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_NVRAM);
	वापस 0;
पूर्ण

अटल व्योम bnx2x_enable_nvram_access(काष्ठा bnx2x *bp)
अणु
	u32 val;

	val = REG_RD(bp, MCP_REG_MCPR_NVM_ACCESS_ENABLE);

	/* enable both bits, even on पढ़ो */
	REG_WR(bp, MCP_REG_MCPR_NVM_ACCESS_ENABLE,
	       (val | MCPR_NVM_ACCESS_ENABLE_EN |
		      MCPR_NVM_ACCESS_ENABLE_WR_EN));
पूर्ण

अटल व्योम bnx2x_disable_nvram_access(काष्ठा bnx2x *bp)
अणु
	u32 val;

	val = REG_RD(bp, MCP_REG_MCPR_NVM_ACCESS_ENABLE);

	/* disable both bits, even after पढ़ो */
	REG_WR(bp, MCP_REG_MCPR_NVM_ACCESS_ENABLE,
	       (val & ~(MCPR_NVM_ACCESS_ENABLE_EN |
			MCPR_NVM_ACCESS_ENABLE_WR_EN)));
पूर्ण

अटल पूर्णांक bnx2x_nvram_पढ़ो_dword(काष्ठा bnx2x *bp, u32 offset, __be32 *ret_val,
				  u32 cmd_flags)
अणु
	पूर्णांक count, i, rc;
	u32 val;

	/* build the command word */
	cmd_flags |= MCPR_NVM_COMMAND_DOIT;

	/* need to clear DONE bit separately */
	REG_WR(bp, MCP_REG_MCPR_NVM_COMMAND, MCPR_NVM_COMMAND_DONE);

	/* address of the NVRAM to पढ़ो from */
	REG_WR(bp, MCP_REG_MCPR_NVM_ADDR,
	       (offset & MCPR_NVM_ADDR_NVM_ADDR_VALUE));

	/* issue a पढ़ो command */
	REG_WR(bp, MCP_REG_MCPR_NVM_COMMAND, cmd_flags);

	/* adjust समयout क्रम emulation/FPGA */
	count = BNX2X_NVRAM_TIMEOUT_COUNT;
	अगर (CHIP_REV_IS_SLOW(bp))
		count *= 100;

	/* रुको क्रम completion */
	*ret_val = 0;
	rc = -EBUSY;
	क्रम (i = 0; i < count; i++) अणु
		udelay(5);
		val = REG_RD(bp, MCP_REG_MCPR_NVM_COMMAND);

		अगर (val & MCPR_NVM_COMMAND_DONE) अणु
			val = REG_RD(bp, MCP_REG_MCPR_NVM_READ);
			/* we पढ़ो nvram data in cpu order
			 * but ethtool sees it as an array of bytes
			 * converting to big-endian will करो the work
			 */
			*ret_val = cpu_to_be32(val);
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (rc == -EBUSY)
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "nvram read timeout expired\n");
	वापस rc;
पूर्ण

पूर्णांक bnx2x_nvram_पढ़ो(काष्ठा bnx2x *bp, u32 offset, u8 *ret_buf,
		     पूर्णांक buf_size)
अणु
	पूर्णांक rc;
	u32 cmd_flags;
	__be32 val;

	अगर ((offset & 0x03) || (buf_size & 0x03) || (buf_size == 0)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "Invalid parameter: offset 0x%x  buf_size 0x%x\n",
		   offset, buf_size);
		वापस -EINVAL;
	पूर्ण

	अगर (offset + buf_size > bp->common.flash_size) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "Invalid parameter: offset (0x%x) + buf_size (0x%x) > flash_size (0x%x)\n",
		   offset, buf_size, bp->common.flash_size);
		वापस -EINVAL;
	पूर्ण

	/* request access to nvram पूर्णांकerface */
	rc = bnx2x_acquire_nvram_lock(bp);
	अगर (rc)
		वापस rc;

	/* enable access to nvram पूर्णांकerface */
	bnx2x_enable_nvram_access(bp);

	/* पढ़ो the first word(s) */
	cmd_flags = MCPR_NVM_COMMAND_FIRST;
	जबतक ((buf_size > माप(u32)) && (rc == 0)) अणु
		rc = bnx2x_nvram_पढ़ो_dword(bp, offset, &val, cmd_flags);
		स_नकल(ret_buf, &val, 4);

		/* advance to the next dword */
		offset += माप(u32);
		ret_buf += माप(u32);
		buf_size -= माप(u32);
		cmd_flags = 0;
	पूर्ण

	अगर (rc == 0) अणु
		cmd_flags |= MCPR_NVM_COMMAND_LAST;
		rc = bnx2x_nvram_पढ़ो_dword(bp, offset, &val, cmd_flags);
		स_नकल(ret_buf, &val, 4);
	पूर्ण

	/* disable access to nvram पूर्णांकerface */
	bnx2x_disable_nvram_access(bp);
	bnx2x_release_nvram_lock(bp);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_nvram_पढ़ो32(काष्ठा bnx2x *bp, u32 offset, u32 *buf,
			      पूर्णांक buf_size)
अणु
	पूर्णांक rc;

	rc = bnx2x_nvram_पढ़ो(bp, offset, (u8 *)buf, buf_size);

	अगर (!rc) अणु
		__be32 *be = (__be32 *)buf;

		जबतक ((buf_size -= 4) >= 0)
			*buf++ = be32_to_cpu(*be++);
	पूर्ण

	वापस rc;
पूर्ण

अटल bool bnx2x_is_nvm_accessible(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc = 1;
	u16 pm = 0;
	काष्ठा net_device *dev = pci_get_drvdata(bp->pdev);

	अगर (bp->pdev->pm_cap)
		rc = pci_पढ़ो_config_word(bp->pdev,
					  bp->pdev->pm_cap + PCI_PM_CTRL, &pm);

	अगर ((rc && !netअगर_running(dev)) ||
	    (!rc && ((pm & PCI_PM_CTRL_STATE_MASK) != (__क्रमce u16)PCI_D0)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक bnx2x_get_eeprom(काष्ठा net_device *dev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *eebuf)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (!bnx2x_is_nvm_accessible(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL  | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस -EAGAIN;
	पूर्ण

	DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "ethtool_eeprom: cmd %d\n"
	   "  magic 0x%x  offset 0x%x (%d)  len 0x%x (%d)\n",
	   eeprom->cmd, eeprom->magic, eeprom->offset, eeprom->offset,
	   eeprom->len, eeprom->len);

	/* parameters alपढ़ोy validated in ethtool_get_eeprom */

	वापस bnx2x_nvram_पढ़ो(bp, eeprom->offset, eebuf, eeprom->len);
पूर्ण

अटल पूर्णांक bnx2x_get_module_eeprom(काष्ठा net_device *dev,
				   काष्ठा ethtool_eeprom *ee,
				   u8 *data)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक rc = -EINVAL, phy_idx;
	u8 *user_data = data;
	अचिन्हित पूर्णांक start_addr = ee->offset, xfer_size = 0;

	अगर (!bnx2x_is_nvm_accessible(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस -EAGAIN;
	पूर्ण

	phy_idx = bnx2x_get_cur_phy_idx(bp);

	/* Read A0 section */
	अगर (start_addr < ETH_MODULE_SFF_8079_LEN) अणु
		/* Limit transfer size to the A0 section boundary */
		अगर (start_addr + ee->len > ETH_MODULE_SFF_8079_LEN)
			xfer_size = ETH_MODULE_SFF_8079_LEN - start_addr;
		अन्यथा
			xfer_size = ee->len;
		bnx2x_acquire_phy_lock(bp);
		rc = bnx2x_पढ़ो_sfp_module_eeprom(&bp->link_params.phy[phy_idx],
						  &bp->link_params,
						  I2C_DEV_ADDR_A0,
						  start_addr,
						  xfer_size,
						  user_data);
		bnx2x_release_phy_lock(bp);
		अगर (rc) अणु
			DP(BNX2X_MSG_ETHTOOL, "Failed reading A0 section\n");

			वापस -EINVAL;
		पूर्ण
		user_data += xfer_size;
		start_addr += xfer_size;
	पूर्ण

	/* Read A2 section */
	अगर ((start_addr >= ETH_MODULE_SFF_8079_LEN) &&
	    (start_addr < ETH_MODULE_SFF_8472_LEN)) अणु
		xfer_size = ee->len - xfer_size;
		/* Limit transfer size to the A2 section boundary */
		अगर (start_addr + xfer_size > ETH_MODULE_SFF_8472_LEN)
			xfer_size = ETH_MODULE_SFF_8472_LEN - start_addr;
		start_addr -= ETH_MODULE_SFF_8079_LEN;
		bnx2x_acquire_phy_lock(bp);
		rc = bnx2x_पढ़ो_sfp_module_eeprom(&bp->link_params.phy[phy_idx],
						  &bp->link_params,
						  I2C_DEV_ADDR_A2,
						  start_addr,
						  xfer_size,
						  user_data);
		bnx2x_release_phy_lock(bp);
		अगर (rc) अणु
			DP(BNX2X_MSG_ETHTOOL, "Failed reading A2 section\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_get_module_info(काष्ठा net_device *dev,
				 काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक phy_idx, rc;
	u8 sff8472_comp, diag_type;

	अगर (!bnx2x_is_nvm_accessible(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस -EAGAIN;
	पूर्ण
	phy_idx = bnx2x_get_cur_phy_idx(bp);
	bnx2x_acquire_phy_lock(bp);
	rc = bnx2x_पढ़ो_sfp_module_eeprom(&bp->link_params.phy[phy_idx],
					  &bp->link_params,
					  I2C_DEV_ADDR_A0,
					  SFP_EEPROM_SFF_8472_COMP_ADDR,
					  SFP_EEPROM_SFF_8472_COMP_SIZE,
					  &sff8472_comp);
	bnx2x_release_phy_lock(bp);
	अगर (rc) अणु
		DP(BNX2X_MSG_ETHTOOL, "Failed reading SFF-8472 comp field\n");
		वापस -EINVAL;
	पूर्ण

	bnx2x_acquire_phy_lock(bp);
	rc = bnx2x_पढ़ो_sfp_module_eeprom(&bp->link_params.phy[phy_idx],
					  &bp->link_params,
					  I2C_DEV_ADDR_A0,
					  SFP_EEPROM_DIAG_TYPE_ADDR,
					  SFP_EEPROM_DIAG_TYPE_SIZE,
					  &diag_type);
	bnx2x_release_phy_lock(bp);
	अगर (rc) अणु
		DP(BNX2X_MSG_ETHTOOL, "Failed reading Diag Type field\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!sff8472_comp ||
	    (diag_type & SFP_EEPROM_DIAG_ADDR_CHANGE_REQ) ||
	    !(diag_type & SFP_EEPROM_DDM_IMPLEMENTED)) अणु
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	पूर्ण अन्यथा अणु
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_nvram_ग_लिखो_dword(काष्ठा bnx2x *bp, u32 offset, u32 val,
				   u32 cmd_flags)
अणु
	पूर्णांक count, i, rc;

	/* build the command word */
	cmd_flags |= MCPR_NVM_COMMAND_DOIT | MCPR_NVM_COMMAND_WR;

	/* need to clear DONE bit separately */
	REG_WR(bp, MCP_REG_MCPR_NVM_COMMAND, MCPR_NVM_COMMAND_DONE);

	/* ग_लिखो the data */
	REG_WR(bp, MCP_REG_MCPR_NVM_WRITE, val);

	/* address of the NVRAM to ग_लिखो to */
	REG_WR(bp, MCP_REG_MCPR_NVM_ADDR,
	       (offset & MCPR_NVM_ADDR_NVM_ADDR_VALUE));

	/* issue the ग_लिखो command */
	REG_WR(bp, MCP_REG_MCPR_NVM_COMMAND, cmd_flags);

	/* adjust समयout क्रम emulation/FPGA */
	count = BNX2X_NVRAM_TIMEOUT_COUNT;
	अगर (CHIP_REV_IS_SLOW(bp))
		count *= 100;

	/* रुको क्रम completion */
	rc = -EBUSY;
	क्रम (i = 0; i < count; i++) अणु
		udelay(5);
		val = REG_RD(bp, MCP_REG_MCPR_NVM_COMMAND);
		अगर (val & MCPR_NVM_COMMAND_DONE) अणु
			rc = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (rc == -EBUSY)
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "nvram write timeout expired\n");
	वापस rc;
पूर्ण

#घोषणा BYTE_OFFSET(offset)		(8 * (offset & 0x03))

अटल पूर्णांक bnx2x_nvram_ग_लिखो1(काष्ठा bnx2x *bp, u32 offset, u8 *data_buf,
			      पूर्णांक buf_size)
अणु
	पूर्णांक rc;
	u32 cmd_flags, align_offset, val;
	__be32 val_be;

	अगर (offset + buf_size > bp->common.flash_size) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "Invalid parameter: offset (0x%x) + buf_size (0x%x) > flash_size (0x%x)\n",
		   offset, buf_size, bp->common.flash_size);
		वापस -EINVAL;
	पूर्ण

	/* request access to nvram पूर्णांकerface */
	rc = bnx2x_acquire_nvram_lock(bp);
	अगर (rc)
		वापस rc;

	/* enable access to nvram पूर्णांकerface */
	bnx2x_enable_nvram_access(bp);

	cmd_flags = (MCPR_NVM_COMMAND_FIRST | MCPR_NVM_COMMAND_LAST);
	align_offset = (offset & ~0x03);
	rc = bnx2x_nvram_पढ़ो_dword(bp, align_offset, &val_be, cmd_flags);

	अगर (rc == 0) अणु
		/* nvram data is वापसed as an array of bytes
		 * convert it back to cpu order
		 */
		val = be32_to_cpu(val_be);

		val &= ~le32_to_cpu((__क्रमce __le32)
				    (0xff << BYTE_OFFSET(offset)));
		val |= le32_to_cpu((__क्रमce __le32)
				   (*data_buf << BYTE_OFFSET(offset)));

		rc = bnx2x_nvram_ग_लिखो_dword(bp, align_offset, val,
					     cmd_flags);
	पूर्ण

	/* disable access to nvram पूर्णांकerface */
	bnx2x_disable_nvram_access(bp);
	bnx2x_release_nvram_lock(bp);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_nvram_ग_लिखो(काष्ठा bnx2x *bp, u32 offset, u8 *data_buf,
			     पूर्णांक buf_size)
अणु
	पूर्णांक rc;
	u32 cmd_flags;
	u32 val;
	u32 written_so_far;

	अगर (buf_size == 1)	/* ethtool */
		वापस bnx2x_nvram_ग_लिखो1(bp, offset, data_buf, buf_size);

	अगर ((offset & 0x03) || (buf_size & 0x03) || (buf_size == 0)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "Invalid parameter: offset 0x%x  buf_size 0x%x\n",
		   offset, buf_size);
		वापस -EINVAL;
	पूर्ण

	अगर (offset + buf_size > bp->common.flash_size) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "Invalid parameter: offset (0x%x) + buf_size (0x%x) > flash_size (0x%x)\n",
		   offset, buf_size, bp->common.flash_size);
		वापस -EINVAL;
	पूर्ण

	/* request access to nvram पूर्णांकerface */
	rc = bnx2x_acquire_nvram_lock(bp);
	अगर (rc)
		वापस rc;

	/* enable access to nvram पूर्णांकerface */
	bnx2x_enable_nvram_access(bp);

	written_so_far = 0;
	cmd_flags = MCPR_NVM_COMMAND_FIRST;
	जबतक ((written_so_far < buf_size) && (rc == 0)) अणु
		अगर (written_so_far == (buf_size - माप(u32)))
			cmd_flags |= MCPR_NVM_COMMAND_LAST;
		अन्यथा अगर (((offset + 4) % BNX2X_NVRAM_PAGE_SIZE) == 0)
			cmd_flags |= MCPR_NVM_COMMAND_LAST;
		अन्यथा अगर ((offset % BNX2X_NVRAM_PAGE_SIZE) == 0)
			cmd_flags |= MCPR_NVM_COMMAND_FIRST;

		स_नकल(&val, data_buf, 4);

		/* Notice unlike bnx2x_nvram_पढ़ो_dword() this will not
		 * change val using be32_to_cpu(), which causes data to flip
		 * अगर the eeprom is पढ़ो and then written back. This is due
		 * to tools utilizing this functionality that would अवरोध
		 * अगर this would be resolved.
		 */
		rc = bnx2x_nvram_ग_लिखो_dword(bp, offset, val, cmd_flags);

		/* advance to the next dword */
		offset += माप(u32);
		data_buf += माप(u32);
		written_so_far += माप(u32);

		/* At end of each 4Kb page, release nvram lock to allow MFW
		 * chance to take it क्रम its own use.
		 */
		अगर ((cmd_flags & MCPR_NVM_COMMAND_LAST) &&
		    (written_so_far < buf_size)) अणु
			DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
			   "Releasing NVM lock after offset 0x%x\n",
			   (u32)(offset - माप(u32)));
			bnx2x_release_nvram_lock(bp);
			usleep_range(1000, 2000);
			rc = bnx2x_acquire_nvram_lock(bp);
			अगर (rc)
				वापस rc;
		पूर्ण

		cmd_flags = 0;
	पूर्ण

	/* disable access to nvram पूर्णांकerface */
	bnx2x_disable_nvram_access(bp);
	bnx2x_release_nvram_lock(bp);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_set_eeprom(काष्ठा net_device *dev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *eebuf)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक port = BP_PORT(bp);
	पूर्णांक rc = 0;
	u32 ext_phy_config;

	अगर (!bnx2x_is_nvm_accessible(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस -EAGAIN;
	पूर्ण

	DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "ethtool_eeprom: cmd %d\n"
	   "  magic 0x%x  offset 0x%x (%d)  len 0x%x (%d)\n",
	   eeprom->cmd, eeprom->magic, eeprom->offset, eeprom->offset,
	   eeprom->len, eeprom->len);

	/* parameters alपढ़ोy validated in ethtool_set_eeprom */

	/* PHY eeprom can be accessed only by the PMF */
	अगर ((eeprom->magic >= 0x50485900) && (eeprom->magic <= 0x504859FF) &&
	    !bp->port.pmf) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "wrong magic or interface is not pmf\n");
		वापस -EINVAL;
	पूर्ण

	ext_phy_config =
		SHMEM_RD(bp,
			 dev_info.port_hw_config[port].बाह्यal_phy_config);

	अगर (eeprom->magic == 0x50485950) अणु
		/* 'PHYP' (0x50485950): prepare phy क्रम FW upgrade */
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);

		bnx2x_acquire_phy_lock(bp);
		rc |= bnx2x_link_reset(&bp->link_params,
				       &bp->link_vars, 0);
		अगर (XGXS_EXT_PHY_TYPE(ext_phy_config) ==
					PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101)
			bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_0,
				       MISC_REGISTERS_GPIO_HIGH, port);
		bnx2x_release_phy_lock(bp);
		bnx2x_link_report(bp);

	पूर्ण अन्यथा अगर (eeprom->magic == 0x50485952) अणु
		/* 'PHYR' (0x50485952): re-init link after FW upgrade */
		अगर (bp->state == BNX2X_STATE_OPEN) अणु
			bnx2x_acquire_phy_lock(bp);
			rc |= bnx2x_link_reset(&bp->link_params,
					       &bp->link_vars, 1);

			rc |= bnx2x_phy_init(&bp->link_params,
					     &bp->link_vars);
			bnx2x_release_phy_lock(bp);
			bnx2x_calc_fc_adv(bp);
		पूर्ण
	पूर्ण अन्यथा अगर (eeprom->magic == 0x53985943) अणु
		/* 'PHYC' (0x53985943): PHY FW upgrade completed */
		अगर (XGXS_EXT_PHY_TYPE(ext_phy_config) ==
				       PORT_HW_CFG_XGXS_EXT_PHY_TYPE_SFX7101) अणु

			/* DSP Remove Download Mode */
			bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_0,
				       MISC_REGISTERS_GPIO_LOW, port);

			bnx2x_acquire_phy_lock(bp);

			bnx2x_sfx7101_sp_sw_reset(bp,
						&bp->link_params.phy[EXT_PHY1]);

			/* रुको 0.5 sec to allow it to run */
			msleep(500);
			bnx2x_ext_phy_hw_reset(bp, port);
			msleep(500);
			bnx2x_release_phy_lock(bp);
		पूर्ण
	पूर्ण अन्यथा
		rc = bnx2x_nvram_ग_लिखो(bp, eeprom->offset, eebuf, eeprom->len);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_get_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	स_रखो(coal, 0, माप(काष्ठा ethtool_coalesce));

	coal->rx_coalesce_usecs = bp->rx_ticks;
	coal->tx_coalesce_usecs = bp->tx_ticks;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_set_coalesce(काष्ठा net_device *dev,
			      काष्ठा ethtool_coalesce *coal)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	bp->rx_ticks = (u16)coal->rx_coalesce_usecs;
	अगर (bp->rx_ticks > BNX2X_MAX_COALESCE_TOUT)
		bp->rx_ticks = BNX2X_MAX_COALESCE_TOUT;

	bp->tx_ticks = (u16)coal->tx_coalesce_usecs;
	अगर (bp->tx_ticks > BNX2X_MAX_COALESCE_TOUT)
		bp->tx_ticks = BNX2X_MAX_COALESCE_TOUT;

	अगर (netअगर_running(dev))
		bnx2x_update_coalesce(bp);

	वापस 0;
पूर्ण

अटल व्योम bnx2x_get_ringparam(काष्ठा net_device *dev,
				काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	ering->rx_max_pending = MAX_RX_AVAIL;

	/* If size isn't alपढ़ोy set, we give an estimation of the number
	 * of buffers we'll have. We're neglecting some possible conditions
	 * [we couldn't know क्रम certain at this poपूर्णांक अगर number of queues
	 * might shrink] but the number would be correct क्रम the likely
	 * scenario.
	 */
	अगर (bp->rx_ring_size)
		ering->rx_pending = bp->rx_ring_size;
	अन्यथा अगर (BNX2X_NUM_RX_QUEUES(bp))
		ering->rx_pending = MAX_RX_AVAIL / BNX2X_NUM_RX_QUEUES(bp);
	अन्यथा
		ering->rx_pending = MAX_RX_AVAIL;

	ering->tx_max_pending = IS_MF_FCOE_AFEX(bp) ? 0 : MAX_TX_AVAIL;
	ering->tx_pending = bp->tx_ring_size;
पूर्ण

अटल पूर्णांक bnx2x_set_ringparam(काष्ठा net_device *dev,
			       काष्ठा ethtool_ringparam *ering)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	DP(BNX2X_MSG_ETHTOOL,
	   "set ring params command parameters: rx_pending = %d, tx_pending = %d\n",
	   ering->rx_pending, ering->tx_pending);

	अगर (pci_num_vf(bp->pdev)) अणु
		DP(BNX2X_MSG_IOV,
		   "VFs are enabled, can not change ring parameters\n");
		वापस -EPERM;
	पूर्ण

	अगर (bp->recovery_state != BNX2X_RECOVERY_DONE) अणु
		DP(BNX2X_MSG_ETHTOOL,
		   "Handling parity error recovery. Try again later\n");
		वापस -EAGAIN;
	पूर्ण

	अगर ((ering->rx_pending > MAX_RX_AVAIL) ||
	    (ering->rx_pending < (bp->disable_tpa ? MIN_RX_SIZE_NONTPA :
						    MIN_RX_SIZE_TPA)) ||
	    (ering->tx_pending > (IS_MF_STORAGE_ONLY(bp) ? 0 : MAX_TX_AVAIL)) ||
	    (ering->tx_pending <= MAX_SKB_FRAGS + 4)) अणु
		DP(BNX2X_MSG_ETHTOOL, "Command parameters not supported\n");
		वापस -EINVAL;
	पूर्ण

	bp->rx_ring_size = ering->rx_pending;
	bp->tx_ring_size = ering->tx_pending;

	वापस bnx2x_reload_अगर_running(dev);
पूर्ण

अटल व्योम bnx2x_get_छोड़ोparam(काष्ठा net_device *dev,
				 काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक cfg_idx = bnx2x_get_link_cfg_idx(bp);
	पूर्णांक cfg_reg;

	eछोड़ो->स्वतःneg = (bp->link_params.req_flow_ctrl[cfg_idx] ==
			   BNX2X_FLOW_CTRL_AUTO);

	अगर (!eछोड़ो->स्वतःneg)
		cfg_reg = bp->link_params.req_flow_ctrl[cfg_idx];
	अन्यथा
		cfg_reg = bp->link_params.req_fc_स्वतः_adv;

	eछोड़ो->rx_छोड़ो = ((cfg_reg & BNX2X_FLOW_CTRL_RX) ==
			    BNX2X_FLOW_CTRL_RX);
	eछोड़ो->tx_छोड़ो = ((cfg_reg & BNX2X_FLOW_CTRL_TX) ==
			    BNX2X_FLOW_CTRL_TX);

	DP(BNX2X_MSG_ETHTOOL, "ethtool_pauseparam: cmd %d\n"
	   "  autoneg %d  rx_pause %d  tx_pause %d\n",
	   eछोड़ो->cmd, eछोड़ो->स्वतःneg, eछोड़ो->rx_छोड़ो, eछोड़ो->tx_छोड़ो);
पूर्ण

अटल पूर्णांक bnx2x_set_छोड़ोparam(काष्ठा net_device *dev,
				काष्ठा ethtool_छोड़ोparam *eछोड़ो)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u32 cfg_idx = bnx2x_get_link_cfg_idx(bp);
	अगर (IS_MF(bp))
		वापस 0;

	DP(BNX2X_MSG_ETHTOOL, "ethtool_pauseparam: cmd %d\n"
	   "  autoneg %d  rx_pause %d  tx_pause %d\n",
	   eछोड़ो->cmd, eछोड़ो->स्वतःneg, eछोड़ो->rx_छोड़ो, eछोड़ो->tx_छोड़ो);

	bp->link_params.req_flow_ctrl[cfg_idx] = BNX2X_FLOW_CTRL_AUTO;

	अगर (eछोड़ो->rx_छोड़ो)
		bp->link_params.req_flow_ctrl[cfg_idx] |= BNX2X_FLOW_CTRL_RX;

	अगर (eछोड़ो->tx_छोड़ो)
		bp->link_params.req_flow_ctrl[cfg_idx] |= BNX2X_FLOW_CTRL_TX;

	अगर (bp->link_params.req_flow_ctrl[cfg_idx] == BNX2X_FLOW_CTRL_AUTO)
		bp->link_params.req_flow_ctrl[cfg_idx] = BNX2X_FLOW_CTRL_NONE;

	अगर (eछोड़ो->स्वतःneg) अणु
		अगर (!(bp->port.supported[cfg_idx] & SUPPORTED_Autoneg)) अणु
			DP(BNX2X_MSG_ETHTOOL, "autoneg not supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (bp->link_params.req_line_speed[cfg_idx] == SPEED_AUTO_NEG) अणु
			bp->link_params.req_flow_ctrl[cfg_idx] =
				BNX2X_FLOW_CTRL_AUTO;
		पूर्ण
		bp->link_params.req_fc_स्वतः_adv = 0;
		अगर (eछोड़ो->rx_छोड़ो)
			bp->link_params.req_fc_स्वतः_adv |= BNX2X_FLOW_CTRL_RX;

		अगर (eछोड़ो->tx_छोड़ो)
			bp->link_params.req_fc_स्वतः_adv |= BNX2X_FLOW_CTRL_TX;

		अगर (!bp->link_params.req_fc_स्वतः_adv)
			bp->link_params.req_fc_स्वतः_adv |= BNX2X_FLOW_CTRL_NONE;
	पूर्ण

	DP(BNX2X_MSG_ETHTOOL,
	   "req_flow_ctrl 0x%x\n", bp->link_params.req_flow_ctrl[cfg_idx]);

	अगर (netअगर_running(dev)) अणु
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);
		bnx2x_क्रमce_link_reset(bp);
		bnx2x_link_set(bp);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर bnx2x_tests_str_arr[BNX2X_NUM_TESTS_SF][ETH_GSTRING_LEN] = अणु
	"register_test (offline)    ",
	"memory_test (offline)      ",
	"int_loopback_test (offline)",
	"ext_loopback_test (offline)",
	"nvram_test (online)        ",
	"interrupt_test (online)    ",
	"link_test (online)         "
पूर्ण;

क्रमागत अणु
	BNX2X_PRI_FLAG_ISCSI,
	BNX2X_PRI_FLAG_FCOE,
	BNX2X_PRI_FLAG_STORAGE,
	BNX2X_PRI_FLAG_LEN,
पूर्ण;

अटल स्थिर अक्षर bnx2x_निजी_arr[BNX2X_PRI_FLAG_LEN][ETH_GSTRING_LEN] = अणु
	"iSCSI offload support",
	"FCoE offload support",
	"Storage only interface"
पूर्ण;

अटल u32 bnx2x_eee_to_adv(u32 eee_adv)
अणु
	u32 modes = 0;

	अगर (eee_adv & SHMEM_EEE_100M_ADV)
		modes |= ADVERTISED_100baseT_Full;
	अगर (eee_adv & SHMEM_EEE_1G_ADV)
		modes |= ADVERTISED_1000baseT_Full;
	अगर (eee_adv & SHMEM_EEE_10G_ADV)
		modes |= ADVERTISED_10000baseT_Full;

	वापस modes;
पूर्ण

अटल u32 bnx2x_adv_to_eee(u32 modes, u32 shअगरt)
अणु
	u32 eee_adv = 0;
	अगर (modes & ADVERTISED_100baseT_Full)
		eee_adv |= SHMEM_EEE_100M_ADV;
	अगर (modes & ADVERTISED_1000baseT_Full)
		eee_adv |= SHMEM_EEE_1G_ADV;
	अगर (modes & ADVERTISED_10000baseT_Full)
		eee_adv |= SHMEM_EEE_10G_ADV;

	वापस eee_adv << shअगरt;
पूर्ण

अटल पूर्णांक bnx2x_get_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u32 eee_cfg;

	अगर (!SHMEM2_HAS(bp, eee_status[BP_PORT(bp)])) अणु
		DP(BNX2X_MSG_ETHTOOL, "BC Version does not support EEE\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	eee_cfg = bp->link_vars.eee_status;

	edata->supported =
		bnx2x_eee_to_adv((eee_cfg & SHMEM_EEE_SUPPORTED_MASK) >>
				 SHMEM_EEE_SUPPORTED_SHIFT);

	edata->advertised =
		bnx2x_eee_to_adv((eee_cfg & SHMEM_EEE_ADV_STATUS_MASK) >>
				 SHMEM_EEE_ADV_STATUS_SHIFT);
	edata->lp_advertised =
		bnx2x_eee_to_adv((eee_cfg & SHMEM_EEE_LP_ADV_STATUS_MASK) >>
				 SHMEM_EEE_LP_ADV_STATUS_SHIFT);

	/* SHMEM value is in 16u units --> Convert to 1u units. */
	edata->tx_lpi_समयr = (eee_cfg & SHMEM_EEE_TIMER_MASK) << 4;

	edata->eee_enabled    = (eee_cfg & SHMEM_EEE_REQUESTED_BIT)	? 1 : 0;
	edata->eee_active     = (eee_cfg & SHMEM_EEE_ACTIVE_BIT)	? 1 : 0;
	edata->tx_lpi_enabled = (eee_cfg & SHMEM_EEE_LPI_REQUESTED_BIT) ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_set_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u32 eee_cfg;
	u32 advertised;

	अगर (IS_MF(bp))
		वापस 0;

	अगर (!SHMEM2_HAS(bp, eee_status[BP_PORT(bp)])) अणु
		DP(BNX2X_MSG_ETHTOOL, "BC Version does not support EEE\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	eee_cfg = bp->link_vars.eee_status;

	अगर (!(eee_cfg & SHMEM_EEE_SUPPORTED_MASK)) अणु
		DP(BNX2X_MSG_ETHTOOL, "Board does not support EEE!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	advertised = bnx2x_adv_to_eee(edata->advertised,
				      SHMEM_EEE_ADV_STATUS_SHIFT);
	अगर ((advertised != (eee_cfg & SHMEM_EEE_ADV_STATUS_MASK))) अणु
		DP(BNX2X_MSG_ETHTOOL,
		   "Direct manipulation of EEE advertisement is not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (edata->tx_lpi_समयr > EEE_MODE_TIMER_MASK) अणु
		DP(BNX2X_MSG_ETHTOOL,
		   "Maximal Tx Lpi timer supported is %x(u)\n",
		   EEE_MODE_TIMER_MASK);
		वापस -EINVAL;
	पूर्ण
	अगर (edata->tx_lpi_enabled &&
	    (edata->tx_lpi_समयr < EEE_MODE_NVRAM_AGGRESSIVE_TIME)) अणु
		DP(BNX2X_MSG_ETHTOOL,
		   "Minimal Tx Lpi timer supported is %d(u)\n",
		   EEE_MODE_NVRAM_AGGRESSIVE_TIME);
		वापस -EINVAL;
	पूर्ण

	/* All is well; Apply changes*/
	अगर (edata->eee_enabled)
		bp->link_params.eee_mode |= EEE_MODE_ADV_LPI;
	अन्यथा
		bp->link_params.eee_mode &= ~EEE_MODE_ADV_LPI;

	अगर (edata->tx_lpi_enabled)
		bp->link_params.eee_mode |= EEE_MODE_ENABLE_LPI;
	अन्यथा
		bp->link_params.eee_mode &= ~EEE_MODE_ENABLE_LPI;

	bp->link_params.eee_mode &= ~EEE_MODE_TIMER_MASK;
	bp->link_params.eee_mode |= (edata->tx_lpi_समयr &
				    EEE_MODE_TIMER_MASK) |
				    EEE_MODE_OVERRIDE_NVRAM |
				    EEE_MODE_OUTPUT_TIME;

	/* Restart link to propagate changes */
	अगर (netअगर_running(dev)) अणु
		bnx2x_stats_handle(bp, STATS_EVENT_STOP);
		bnx2x_क्रमce_link_reset(bp);
		bnx2x_link_set(bp);
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत अणु
	BNX2X_CHIP_E1_OFST = 0,
	BNX2X_CHIP_E1H_OFST,
	BNX2X_CHIP_E2_OFST,
	BNX2X_CHIP_E3_OFST,
	BNX2X_CHIP_E3B0_OFST,
	BNX2X_CHIP_MAX_OFST
पूर्ण;

#घोषणा BNX2X_CHIP_MASK_E1	(1 << BNX2X_CHIP_E1_OFST)
#घोषणा BNX2X_CHIP_MASK_E1H	(1 << BNX2X_CHIP_E1H_OFST)
#घोषणा BNX2X_CHIP_MASK_E2	(1 << BNX2X_CHIP_E2_OFST)
#घोषणा BNX2X_CHIP_MASK_E3	(1 << BNX2X_CHIP_E3_OFST)
#घोषणा BNX2X_CHIP_MASK_E3B0	(1 << BNX2X_CHIP_E3B0_OFST)

#घोषणा BNX2X_CHIP_MASK_ALL	((1 << BNX2X_CHIP_MAX_OFST) - 1)
#घोषणा BNX2X_CHIP_MASK_E1X	(BNX2X_CHIP_MASK_E1 | BNX2X_CHIP_MASK_E1H)

अटल पूर्णांक bnx2x_test_रेजिस्टरs(काष्ठा bnx2x *bp)
अणु
	पूर्णांक idx, i, rc = -ENODEV;
	u32 wr_val = 0, hw;
	पूर्णांक port = BP_PORT(bp);
	अटल स्थिर काष्ठा अणु
		u32 hw;
		u32 offset0;
		u32 offset1;
		u32 mask;
	पूर्ण reg_tbl[] = अणु
/* 0 */		अणु BNX2X_CHIP_MASK_ALL,
			BRB1_REG_PAUSE_LOW_THRESHOLD_0,	4, 0x000003ff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			DORQ_REG_DB_ADDR0,		4, 0xffffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_E1X,
			HC_REG_AGG_INT_0,		4, 0x000003ff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			PBF_REG_MAC_IF0_ENABLE,		4, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2 | BNX2X_CHIP_MASK_E3,
			PBF_REG_P0_INIT_CRD,		4, 0x000007ff पूर्ण,
		अणु BNX2X_CHIP_MASK_E3B0,
			PBF_REG_INIT_CRD_Q0,		4, 0x000007ff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			PRS_REG_CID_PORT_0,		4, 0x00ffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			PXP2_REG_PSWRQ_CDU0_L2P,	4, 0x000fffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			PXP2_REG_RQ_CDU0_EFIRST_MEM_ADDR, 8, 0x0003ffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			PXP2_REG_PSWRQ_TM0_L2P,		4, 0x000fffff पूर्ण,
/* 10 */	अणु BNX2X_CHIP_MASK_ALL,
			PXP2_REG_RQ_USDM0_EFIRST_MEM_ADDR, 8, 0x0003ffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			PXP2_REG_PSWRQ_TSDM0_L2P,	4, 0x000fffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			QM_REG_CONNNUM_0,		4, 0x000fffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			TM_REG_LIN0_MAX_ACTIVE_CID,	4, 0x0003ffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			SRC_REG_KEYRSS0_0,		40, 0xffffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			SRC_REG_KEYRSS0_7,		40, 0xffffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			XCM_REG_WU_DA_SET_TMR_CNT_FLG_CMD00, 4, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			XCM_REG_WU_DA_CNT_CMD00,	4, 0x00000003 पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			XCM_REG_GLB_DEL_ACK_MAX_CNT_0,	4, 0x000000ff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_T_BIT,		4, 0x00000001 पूर्ण,
/* 20 */	अणु BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_EMAC0_IN_EN,		4, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_BMAC0_IN_EN,		4, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_XCM0_OUT_EN,		4, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_BRB0_OUT_EN,		4, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_XCM_MASK,		4, 0x00000007 पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_ACPI_PAT_6_LEN,	68, 0x000000ff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_ACPI_PAT_0_CRC,	68, 0xffffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_MAC_0_0,	160, 0xffffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_IP_0_1,	160, 0xffffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_IPV4_IPV6_0,	160, 0x00000001 पूर्ण,
/* 30 */	अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_UDP_0,	160, 0x0000ffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_DEST_TCP_0,	160, 0x0000ffff पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LLH0_VLAN_ID_0,	160, 0x00000fff पूर्ण,
		अणु BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_XGXS_SERDES0_MODE_SEL,	4, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_LED_CONTROL_OVERRIDE_TRAFFIC_P0, 4, 0x00000001पूर्ण,
		अणु BNX2X_CHIP_MASK_ALL,
			NIG_REG_STATUS_INTERRUPT_PORT0,	4, 0x07ffffff पूर्ण,
		अणु BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_XGXS0_CTRL_EXTREMOTEMDIOST, 24, 0x00000001 पूर्ण,
		अणु BNX2X_CHIP_MASK_E1X | BNX2X_CHIP_MASK_E2,
			NIG_REG_SERDES0_CTRL_PHY_ADDR,	16, 0x0000001f पूर्ण,

		अणु BNX2X_CHIP_MASK_ALL, 0xffffffff, 0, 0x00000000 पूर्ण
	पूर्ण;

	अगर (!bnx2x_is_nvm_accessible(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस rc;
	पूर्ण

	अगर (CHIP_IS_E1(bp))
		hw = BNX2X_CHIP_MASK_E1;
	अन्यथा अगर (CHIP_IS_E1H(bp))
		hw = BNX2X_CHIP_MASK_E1H;
	अन्यथा अगर (CHIP_IS_E2(bp))
		hw = BNX2X_CHIP_MASK_E2;
	अन्यथा अगर (CHIP_IS_E3B0(bp))
		hw = BNX2X_CHIP_MASK_E3B0;
	अन्यथा /* e3 A0 */
		hw = BNX2X_CHIP_MASK_E3;

	/* Repeat the test twice:
	 * First by writing 0x00000000, second by writing 0xffffffff
	 */
	क्रम (idx = 0; idx < 2; idx++) अणु

		चयन (idx) अणु
		हाल 0:
			wr_val = 0;
			अवरोध;
		हाल 1:
			wr_val = 0xffffffff;
			अवरोध;
		पूर्ण

		क्रम (i = 0; reg_tbl[i].offset0 != 0xffffffff; i++) अणु
			u32 offset, mask, save_val, val;
			अगर (!(hw & reg_tbl[i].hw))
				जारी;

			offset = reg_tbl[i].offset0 + port*reg_tbl[i].offset1;
			mask = reg_tbl[i].mask;

			save_val = REG_RD(bp, offset);

			REG_WR(bp, offset, wr_val & mask);

			val = REG_RD(bp, offset);

			/* Restore the original रेजिस्टर's value */
			REG_WR(bp, offset, save_val);

			/* verअगरy value is as expected */
			अगर ((val & mask) != (wr_val & mask)) अणु
				DP(BNX2X_MSG_ETHTOOL,
				   "offset 0x%x: val 0x%x != 0x%x mask 0x%x\n",
				   offset, val, wr_val, mask);
				जाओ test_reg_निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	rc = 0;

test_reg_निकास:
	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_test_memory(काष्ठा bnx2x *bp)
अणु
	पूर्णांक i, j, rc = -ENODEV;
	u32 val, index;
	अटल स्थिर काष्ठा अणु
		u32 offset;
		पूर्णांक size;
	पूर्ण mem_tbl[] = अणु
		अणु CCM_REG_XX_DESCR_TABLE,   CCM_REG_XX_DESCR_TABLE_SIZE पूर्ण,
		अणु CFC_REG_ACTIVITY_COUNTER, CFC_REG_ACTIVITY_COUNTER_SIZE पूर्ण,
		अणु CFC_REG_LINK_LIST,        CFC_REG_LINK_LIST_SIZE पूर्ण,
		अणु DMAE_REG_CMD_MEM,         DMAE_REG_CMD_MEM_SIZE पूर्ण,
		अणु TCM_REG_XX_DESCR_TABLE,   TCM_REG_XX_DESCR_TABLE_SIZE पूर्ण,
		अणु UCM_REG_XX_DESCR_TABLE,   UCM_REG_XX_DESCR_TABLE_SIZE पूर्ण,
		अणु XCM_REG_XX_DESCR_TABLE,   XCM_REG_XX_DESCR_TABLE_SIZE पूर्ण,

		अणु 0xffffffff, 0 पूर्ण
	पूर्ण;

	अटल स्थिर काष्ठा अणु
		अक्षर *name;
		u32 offset;
		u32 hw_mask[BNX2X_CHIP_MAX_OFST];
	पूर्ण prty_tbl[] = अणु
		अणु "CCM_PRTY_STS",  CCM_REG_CCM_PRTY_STS,
			अणु0x3ffc0, 0,   0, 0पूर्ण पूर्ण,
		अणु "CFC_PRTY_STS",  CFC_REG_CFC_PRTY_STS,
			अणु0x2,     0x2, 0, 0पूर्ण पूर्ण,
		अणु "DMAE_PRTY_STS", DMAE_REG_DMAE_PRTY_STS,
			अणु0,       0,   0, 0पूर्ण पूर्ण,
		अणु "TCM_PRTY_STS",  TCM_REG_TCM_PRTY_STS,
			अणु0x3ffc0, 0,   0, 0पूर्ण पूर्ण,
		अणु "UCM_PRTY_STS",  UCM_REG_UCM_PRTY_STS,
			अणु0x3ffc0, 0,   0, 0पूर्ण पूर्ण,
		अणु "XCM_PRTY_STS",  XCM_REG_XCM_PRTY_STS,
			अणु0x3ffc1, 0,   0, 0पूर्ण पूर्ण,

		अणु शून्य, 0xffffffff, अणु0, 0, 0, 0पूर्ण पूर्ण
	पूर्ण;

	अगर (!bnx2x_is_nvm_accessible(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस rc;
	पूर्ण

	अगर (CHIP_IS_E1(bp))
		index = BNX2X_CHIP_E1_OFST;
	अन्यथा अगर (CHIP_IS_E1H(bp))
		index = BNX2X_CHIP_E1H_OFST;
	अन्यथा अगर (CHIP_IS_E2(bp))
		index = BNX2X_CHIP_E2_OFST;
	अन्यथा /* e3 */
		index = BNX2X_CHIP_E3_OFST;

	/* pre-Check the parity status */
	क्रम (i = 0; prty_tbl[i].offset != 0xffffffff; i++) अणु
		val = REG_RD(bp, prty_tbl[i].offset);
		अगर (val & ~(prty_tbl[i].hw_mask[index])) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "%s is 0x%x\n", prty_tbl[i].name, val);
			जाओ test_mem_निकास;
		पूर्ण
	पूर्ण

	/* Go through all the memories */
	क्रम (i = 0; mem_tbl[i].offset != 0xffffffff; i++)
		क्रम (j = 0; j < mem_tbl[i].size; j++)
			REG_RD(bp, mem_tbl[i].offset + j*4);

	/* Check the parity status */
	क्रम (i = 0; prty_tbl[i].offset != 0xffffffff; i++) अणु
		val = REG_RD(bp, prty_tbl[i].offset);
		अगर (val & ~(prty_tbl[i].hw_mask[index])) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "%s is 0x%x\n", prty_tbl[i].name, val);
			जाओ test_mem_निकास;
		पूर्ण
	पूर्ण

	rc = 0;

test_mem_निकास:
	वापस rc;
पूर्ण

अटल व्योम bnx2x_रुको_क्रम_link(काष्ठा bnx2x *bp, u8 link_up, u8 is_serdes)
अणु
	पूर्णांक cnt = 1400;

	अगर (link_up) अणु
		जबतक (bnx2x_link_test(bp, is_serdes) && cnt--)
			msleep(20);

		अगर (cnt <= 0 && bnx2x_link_test(bp, is_serdes))
			DP(BNX2X_MSG_ETHTOOL, "Timeout waiting for link up\n");

		cnt = 1400;
		जबतक (!bp->link_vars.link_up && cnt--)
			msleep(20);

		अगर (cnt <= 0 && !bp->link_vars.link_up)
			DP(BNX2X_MSG_ETHTOOL,
			   "Timeout waiting for link init\n");
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_run_loopback(काष्ठा bnx2x *bp, पूर्णांक loopback_mode)
अणु
	अचिन्हित पूर्णांक pkt_size, num_pkts, i;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *packet;
	काष्ठा bnx2x_fastpath *fp_rx = &bp->fp[0];
	काष्ठा bnx2x_fastpath *fp_tx = &bp->fp[0];
	काष्ठा bnx2x_fp_txdata *txdata = fp_tx->txdata_ptr[0];
	u16 tx_start_idx, tx_idx;
	u16 rx_start_idx, rx_idx;
	u16 pkt_prod, bd_prod;
	काष्ठा sw_tx_bd *tx_buf;
	काष्ठा eth_tx_start_bd *tx_start_bd;
	dma_addr_t mapping;
	जोड़ eth_rx_cqe *cqe;
	u8 cqe_fp_flags, cqe_fp_type;
	काष्ठा sw_rx_bd *rx_buf;
	u16 len;
	पूर्णांक rc = -ENODEV;
	u8 *data;
	काष्ठा netdev_queue *txq = netdev_get_tx_queue(bp->dev,
						       txdata->txq_index);

	/* check the loopback mode */
	चयन (loopback_mode) अणु
	हाल BNX2X_PHY_LOOPBACK:
		अगर (bp->link_params.loopback_mode != LOOPBACK_XGXS) अणु
			DP(BNX2X_MSG_ETHTOOL, "PHY loopback not supported\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल BNX2X_MAC_LOOPBACK:
		अगर (CHIP_IS_E3(bp)) अणु
			पूर्णांक cfg_idx = bnx2x_get_link_cfg_idx(bp);
			अगर (bp->port.supported[cfg_idx] &
			    (SUPPORTED_10000baseT_Full |
			     SUPPORTED_20000baseMLD2_Full |
			     SUPPORTED_20000baseKR2_Full))
				bp->link_params.loopback_mode = LOOPBACK_XMAC;
			अन्यथा
				bp->link_params.loopback_mode = LOOPBACK_UMAC;
		पूर्ण अन्यथा
			bp->link_params.loopback_mode = LOOPBACK_BMAC;

		bnx2x_phy_init(&bp->link_params, &bp->link_vars);
		अवरोध;
	हाल BNX2X_EXT_LOOPBACK:
		अगर (bp->link_params.loopback_mode != LOOPBACK_EXT) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "Can't configure external loopback\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		DP(BNX2X_MSG_ETHTOOL, "Command parameters not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* prepare the loopback packet */
	pkt_size = (((bp->dev->mtu < ETH_MAX_PACKET_SIZE) ?
		     bp->dev->mtu : ETH_MAX_PACKET_SIZE) + ETH_HLEN);
	skb = netdev_alloc_skb(bp->dev, fp_rx->rx_buf_size);
	अगर (!skb) अणु
		DP(BNX2X_MSG_ETHTOOL, "Can't allocate skb\n");
		rc = -ENOMEM;
		जाओ test_loopback_निकास;
	पूर्ण
	packet = skb_put(skb, pkt_size);
	स_नकल(packet, bp->dev->dev_addr, ETH_ALEN);
	eth_zero_addr(packet + ETH_ALEN);
	स_रखो(packet + 2*ETH_ALEN, 0x77, (ETH_HLEN - 2*ETH_ALEN));
	क्रम (i = ETH_HLEN; i < pkt_size; i++)
		packet[i] = (अचिन्हित अक्षर) (i & 0xff);
	mapping = dma_map_single(&bp->pdev->dev, skb->data,
				 skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(&bp->pdev->dev, mapping))) अणु
		rc = -ENOMEM;
		dev_kमुक्त_skb(skb);
		DP(BNX2X_MSG_ETHTOOL, "Unable to map SKB\n");
		जाओ test_loopback_निकास;
	पूर्ण

	/* send the loopback packet */
	num_pkts = 0;
	tx_start_idx = le16_to_cpu(*txdata->tx_cons_sb);
	rx_start_idx = le16_to_cpu(*fp_rx->rx_cons_sb);

	netdev_tx_sent_queue(txq, skb->len);

	pkt_prod = txdata->tx_pkt_prod++;
	tx_buf = &txdata->tx_buf_ring[TX_BD(pkt_prod)];
	tx_buf->first_bd = txdata->tx_bd_prod;
	tx_buf->skb = skb;
	tx_buf->flags = 0;

	bd_prod = TX_BD(txdata->tx_bd_prod);
	tx_start_bd = &txdata->tx_desc_ring[bd_prod].start_bd;
	tx_start_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
	tx_start_bd->addr_lo = cpu_to_le32(U64_LO(mapping));
	tx_start_bd->nbd = cpu_to_le16(2); /* start + pbd */
	tx_start_bd->nbytes = cpu_to_le16(skb_headlen(skb));
	tx_start_bd->vlan_or_ethertype = cpu_to_le16(pkt_prod);
	tx_start_bd->bd_flags.as_bitfield = ETH_TX_BD_FLAGS_START_BD;
	SET_FLAG(tx_start_bd->general_data,
		 ETH_TX_START_BD_HDR_NBDS,
		 1);
	SET_FLAG(tx_start_bd->general_data,
		 ETH_TX_START_BD_PARSE_NBDS,
		 0);

	/* turn on parsing and get a BD */
	bd_prod = TX_BD(NEXT_TX_IDX(bd_prod));

	अगर (CHIP_IS_E1x(bp)) अणु
		u16 global_data = 0;
		काष्ठा eth_tx_parse_bd_e1x  *pbd_e1x =
			&txdata->tx_desc_ring[bd_prod].parse_bd_e1x;
		स_रखो(pbd_e1x, 0, माप(काष्ठा eth_tx_parse_bd_e1x));
		SET_FLAG(global_data,
			 ETH_TX_PARSE_BD_E1X_ETH_ADDR_TYPE, UNICAST_ADDRESS);
		pbd_e1x->global_data = cpu_to_le16(global_data);
	पूर्ण अन्यथा अणु
		u32 parsing_data = 0;
		काष्ठा eth_tx_parse_bd_e2  *pbd_e2 =
			&txdata->tx_desc_ring[bd_prod].parse_bd_e2;
		स_रखो(pbd_e2, 0, माप(काष्ठा eth_tx_parse_bd_e2));
		SET_FLAG(parsing_data,
			 ETH_TX_PARSE_BD_E2_ETH_ADDR_TYPE, UNICAST_ADDRESS);
		pbd_e2->parsing_data = cpu_to_le32(parsing_data);
	पूर्ण
	wmb();

	txdata->tx_db.data.prod += 2;
	/* make sure descriptor update is observed by the HW */
	wmb();
	DOORBELL_RELAXED(bp, txdata->cid, txdata->tx_db.raw);

	barrier();

	num_pkts++;
	txdata->tx_bd_prod += 2; /* start + pbd */

	udelay(100);

	tx_idx = le16_to_cpu(*txdata->tx_cons_sb);
	अगर (tx_idx != tx_start_idx + num_pkts)
		जाओ test_loopback_निकास;

	/* Unlike HC IGU won't generate an पूर्णांकerrupt क्रम status block
	 * updates that have been perक्रमmed जबतक पूर्णांकerrupts were
	 * disabled.
	 */
	अगर (bp->common.पूर्णांक_block == INT_BLOCK_IGU) अणु
		/* Disable local BHes to prevent a dead-lock situation between
		 * sch_direct_xmit() and bnx2x_run_loopback() (calling
		 * bnx2x_tx_पूर्णांक()), as both are taking netअगर_tx_lock().
		 */
		local_bh_disable();
		bnx2x_tx_पूर्णांक(bp, txdata);
		local_bh_enable();
	पूर्ण

	rx_idx = le16_to_cpu(*fp_rx->rx_cons_sb);
	अगर (rx_idx != rx_start_idx + num_pkts)
		जाओ test_loopback_निकास;

	cqe = &fp_rx->rx_comp_ring[RCQ_BD(fp_rx->rx_comp_cons)];
	cqe_fp_flags = cqe->fast_path_cqe.type_error_flags;
	cqe_fp_type = cqe_fp_flags & ETH_FAST_PATH_RX_CQE_TYPE;
	अगर (!CQE_TYPE_FAST(cqe_fp_type) || (cqe_fp_flags & ETH_RX_ERROR_FALGS))
		जाओ test_loopback_rx_निकास;

	len = le16_to_cpu(cqe->fast_path_cqe.pkt_len_or_gro_seg_len);
	अगर (len != pkt_size)
		जाओ test_loopback_rx_निकास;

	rx_buf = &fp_rx->rx_buf_ring[RX_BD(fp_rx->rx_bd_cons)];
	dma_sync_single_क्रम_cpu(&bp->pdev->dev,
				   dma_unmap_addr(rx_buf, mapping),
				   fp_rx->rx_buf_size, DMA_FROM_DEVICE);
	data = rx_buf->data + NET_SKB_PAD + cqe->fast_path_cqe.placement_offset;
	क्रम (i = ETH_HLEN; i < pkt_size; i++)
		अगर (*(data + i) != (अचिन्हित अक्षर) (i & 0xff))
			जाओ test_loopback_rx_निकास;

	rc = 0;

test_loopback_rx_निकास:

	fp_rx->rx_bd_cons = NEXT_RX_IDX(fp_rx->rx_bd_cons);
	fp_rx->rx_bd_prod = NEXT_RX_IDX(fp_rx->rx_bd_prod);
	fp_rx->rx_comp_cons = NEXT_RCQ_IDX(fp_rx->rx_comp_cons);
	fp_rx->rx_comp_prod = NEXT_RCQ_IDX(fp_rx->rx_comp_prod);

	/* Update producers */
	bnx2x_update_rx_prod(bp, fp_rx, fp_rx->rx_bd_prod, fp_rx->rx_comp_prod,
			     fp_rx->rx_sge_prod);

test_loopback_निकास:
	bp->link_params.loopback_mode = LOOPBACK_NONE;

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_test_loopback(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc = 0, res;

	अगर (BP_NOMCP(bp))
		वापस rc;

	अगर (!netअगर_running(bp->dev))
		वापस BNX2X_LOOPBACK_FAILED;

	bnx2x_netअगर_stop(bp, 1);
	bnx2x_acquire_phy_lock(bp);

	res = bnx2x_run_loopback(bp, BNX2X_PHY_LOOPBACK);
	अगर (res) अणु
		DP(BNX2X_MSG_ETHTOOL, "  PHY loopback failed  (res %d)\n", res);
		rc |= BNX2X_PHY_LOOPBACK_FAILED;
	पूर्ण

	res = bnx2x_run_loopback(bp, BNX2X_MAC_LOOPBACK);
	अगर (res) अणु
		DP(BNX2X_MSG_ETHTOOL, "  MAC loopback failed  (res %d)\n", res);
		rc |= BNX2X_MAC_LOOPBACK_FAILED;
	पूर्ण

	bnx2x_release_phy_lock(bp);
	bnx2x_netअगर_start(bp);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_test_ext_loopback(काष्ठा bnx2x *bp)
अणु
	पूर्णांक rc;
	u8 is_serdes =
		(bp->link_vars.link_status & LINK_STATUS_SERDES_LINK) > 0;

	अगर (BP_NOMCP(bp))
		वापस -ENODEV;

	अगर (!netअगर_running(bp->dev))
		वापस BNX2X_EXT_LOOPBACK_FAILED;

	bnx2x_nic_unload(bp, UNLOAD_NORMAL, false);
	rc = bnx2x_nic_load(bp, LOAD_LOOPBACK_EXT);
	अगर (rc) अणु
		DP(BNX2X_MSG_ETHTOOL,
		   "Can't perform self-test, nic_load (for external lb) failed\n");
		वापस -ENODEV;
	पूर्ण
	bnx2x_रुको_क्रम_link(bp, 1, is_serdes);

	bnx2x_netअगर_stop(bp, 1);

	rc = bnx2x_run_loopback(bp, BNX2X_EXT_LOOPBACK);
	अगर (rc)
		DP(BNX2X_MSG_ETHTOOL, "EXT loopback failed  (res %d)\n", rc);

	bnx2x_netअगर_start(bp);

	वापस rc;
पूर्ण

काष्ठा code_entry अणु
	u32 sram_start_addr;
	u32 code_attribute;
#घोषणा CODE_IMAGE_TYPE_MASK			0xf0800003
#घोषणा CODE_IMAGE_VNTAG_PROखाताS_DATA		0xd0000003
#घोषणा CODE_IMAGE_LENGTH_MASK			0x007ffffc
#घोषणा CODE_IMAGE_TYPE_EXTENDED_सूची		0xe0000000
	u32 nvm_start_addr;
पूर्ण;

#घोषणा CODE_ENTRY_MAX			16
#घोषणा CODE_ENTRY_EXTENDED_सूची_IDX	15
#घोषणा MAX_IMAGES_IN_EXTENDED_सूची	64
#घोषणा NVRAM_सूची_OFFSET		0x14

#घोषणा EXTENDED_सूची_EXISTS(code)					  \
	((code & CODE_IMAGE_TYPE_MASK) == CODE_IMAGE_TYPE_EXTENDED_सूची && \
	 (code & CODE_IMAGE_LENGTH_MASK) != 0)

#घोषणा CRC32_RESIDUAL			0xdebb20e3
#घोषणा CRC_BUFF_SIZE			256

अटल पूर्णांक bnx2x_nvram_crc(काष्ठा bnx2x *bp,
			   पूर्णांक offset,
			   पूर्णांक size,
			   u8 *buff)
अणु
	u32 crc = ~0;
	पूर्णांक rc = 0, करोne = 0;

	DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
	   "NVRAM CRC from 0x%08x to 0x%08x\n", offset, offset + size);

	जबतक (करोne < size) अणु
		पूर्णांक count = min_t(पूर्णांक, size - करोne, CRC_BUFF_SIZE);

		rc = bnx2x_nvram_पढ़ो(bp, offset + करोne, buff, count);

		अगर (rc)
			वापस rc;

		crc = crc32_le(crc, buff, count);
		करोne += count;
	पूर्ण

	अगर (crc != CRC32_RESIDUAL)
		rc = -EINVAL;

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_test_nvram_dir(काष्ठा bnx2x *bp,
				काष्ठा code_entry *entry,
				u8 *buff)
अणु
	माप_प्रकार size = entry->code_attribute & CODE_IMAGE_LENGTH_MASK;
	u32 type = entry->code_attribute & CODE_IMAGE_TYPE_MASK;
	पूर्णांक rc;

	/* Zero-length images and AFEX profiles करो not have CRC */
	अगर (size == 0 || type == CODE_IMAGE_VNTAG_PROखाताS_DATA)
		वापस 0;

	rc = bnx2x_nvram_crc(bp, entry->nvm_start_addr, size, buff);
	अगर (rc)
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "image %x has failed crc test (rc %d)\n", type, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक bnx2x_test_dir_entry(काष्ठा bnx2x *bp, u32 addr, u8 *buff)
अणु
	पूर्णांक rc;
	काष्ठा code_entry entry;

	rc = bnx2x_nvram_पढ़ो32(bp, addr, (u32 *)&entry, माप(entry));
	अगर (rc)
		वापस rc;

	वापस bnx2x_test_nvram_dir(bp, &entry, buff);
पूर्ण

अटल पूर्णांक bnx2x_test_nvram_ext_dirs(काष्ठा bnx2x *bp, u8 *buff)
अणु
	u32 rc, cnt, dir_offset = NVRAM_सूची_OFFSET;
	काष्ठा code_entry entry;
	पूर्णांक i;

	rc = bnx2x_nvram_पढ़ो32(bp,
				dir_offset +
				माप(entry) * CODE_ENTRY_EXTENDED_सूची_IDX,
				(u32 *)&entry, माप(entry));
	अगर (rc)
		वापस rc;

	अगर (!EXTENDED_सूची_EXISTS(entry.code_attribute))
		वापस 0;

	rc = bnx2x_nvram_पढ़ो32(bp, entry.nvm_start_addr,
				&cnt, माप(u32));
	अगर (rc)
		वापस rc;

	dir_offset = entry.nvm_start_addr + 8;

	क्रम (i = 0; i < cnt && i < MAX_IMAGES_IN_EXTENDED_सूची; i++) अणु
		rc = bnx2x_test_dir_entry(bp, dir_offset +
					      माप(काष्ठा code_entry) * i,
					  buff);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_test_nvram_dirs(काष्ठा bnx2x *bp, u8 *buff)
अणु
	u32 rc, dir_offset = NVRAM_सूची_OFFSET;
	पूर्णांक i;

	DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "NVRAM DIRS CRC test-set\n");

	क्रम (i = 0; i < CODE_ENTRY_EXTENDED_सूची_IDX; i++) अणु
		rc = bnx2x_test_dir_entry(bp, dir_offset +
					      माप(काष्ठा code_entry) * i,
					  buff);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस bnx2x_test_nvram_ext_dirs(bp, buff);
पूर्ण

काष्ठा crc_pair अणु
	पूर्णांक offset;
	पूर्णांक size;
पूर्ण;

अटल पूर्णांक bnx2x_test_nvram_tbl(काष्ठा bnx2x *bp,
				स्थिर काष्ठा crc_pair *nvram_tbl, u8 *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; nvram_tbl[i].size; i++) अणु
		पूर्णांक rc = bnx2x_nvram_crc(bp, nvram_tbl[i].offset,
					 nvram_tbl[i].size, buf);
		अगर (rc) अणु
			DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
			   "nvram_tbl[%d] has failed crc test (rc %d)\n",
			   i, rc);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_test_nvram(काष्ठा bnx2x *bp)
अणु
	अटल स्थिर काष्ठा crc_pair nvram_tbl[] = अणु
		अणु     0,  0x14 पूर्ण, /* bootstrap */
		अणु  0x14,  0xec पूर्ण, /* dir */
		अणु 0x100, 0x350 पूर्ण, /* manuf_info */
		अणु 0x450,  0xf0 पूर्ण, /* feature_info */
		अणु 0x640,  0x64 पूर्ण, /* upgrade_key_info */
		अणु 0x708,  0x70 पूर्ण, /* manuf_key_info */
		अणु     0,     0 पूर्ण
	पूर्ण;
	अटल स्थिर काष्ठा crc_pair nvram_tbl2[] = अणु
		अणु 0x7e8, 0x350 पूर्ण, /* manuf_info2 */
		अणु 0xb38,  0xf0 पूर्ण, /* feature_info */
		अणु     0,     0 पूर्ण
	पूर्ण;

	u8 *buf;
	पूर्णांक rc;
	u32 magic;

	अगर (BP_NOMCP(bp))
		वापस 0;

	buf = kदो_स्मृति(CRC_BUFF_SIZE, GFP_KERNEL);
	अगर (!buf) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "kmalloc failed\n");
		rc = -ENOMEM;
		जाओ test_nvram_निकास;
	पूर्ण

	rc = bnx2x_nvram_पढ़ो32(bp, 0, &magic, माप(magic));
	अगर (rc) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "magic value read (rc %d)\n", rc);
		जाओ test_nvram_निकास;
	पूर्ण

	अगर (magic != 0x669955aa) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "wrong magic value (0x%08x)\n", magic);
		rc = -ENODEV;
		जाओ test_nvram_निकास;
	पूर्ण

	DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM, "Port 0 CRC test-set\n");
	rc = bnx2x_test_nvram_tbl(bp, nvram_tbl, buf);
	अगर (rc)
		जाओ test_nvram_निकास;

	अगर (!CHIP_IS_E1x(bp) && !CHIP_IS_57811xx(bp)) अणु
		u32 hide = SHMEM_RD(bp, dev_info.shared_hw_config.config2) &
			   SHARED_HW_CFG_HIDE_PORT1;

		अगर (!hide) अणु
			DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
			   "Port 1 CRC test-set\n");
			rc = bnx2x_test_nvram_tbl(bp, nvram_tbl2, buf);
			अगर (rc)
				जाओ test_nvram_निकास;
		पूर्ण
	पूर्ण

	rc = bnx2x_test_nvram_dirs(bp, buf);

test_nvram_निकास:
	kमुक्त(buf);
	वापस rc;
पूर्ण

/* Send an EMPTY ramrod on the first queue */
अटल पूर्णांक bnx2x_test_पूर्णांकr(काष्ठा bnx2x *bp)
अणु
	काष्ठा bnx2x_queue_state_params params = अणुशून्यपूर्ण;

	अगर (!netअगर_running(bp->dev)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस -ENODEV;
	पूर्ण

	params.q_obj = &bp->sp_objs->q_obj;
	params.cmd = BNX2X_Q_CMD_EMPTY;

	__set_bit(RAMROD_COMP_WAIT, &params.ramrod_flags);

	वापस bnx2x_queue_state_change(bp, &params);
पूर्ण

अटल व्योम bnx2x_self_test(काष्ठा net_device *dev,
			    काष्ठा ethtool_test *etest, u64 *buf)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u8 is_serdes, link_up;
	पूर्णांक rc, cnt = 0;

	अगर (pci_num_vf(bp->pdev)) अणु
		DP(BNX2X_MSG_IOV,
		   "VFs are enabled, can not perform self test\n");
		वापस;
	पूर्ण

	अगर (bp->recovery_state != BNX2X_RECOVERY_DONE) अणु
		netdev_err(bp->dev,
			   "Handling parity error recovery. Try again later\n");
		etest->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण

	DP(BNX2X_MSG_ETHTOOL,
	   "Self-test command parameters: offline = %d, external_lb = %d\n",
	   (etest->flags & ETH_TEST_FL_OFFLINE),
	   (etest->flags & ETH_TEST_FL_EXTERNAL_LB)>>2);

	स_रखो(buf, 0, माप(u64) * BNX2X_NUM_TESTS(bp));

	अगर (bnx2x_test_nvram(bp) != 0) अणु
		अगर (!IS_MF(bp))
			buf[4] = 1;
		अन्यथा
			buf[0] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	अगर (!netअगर_running(dev)) अणु
		DP(BNX2X_MSG_ETHTOOL, "Interface is down\n");
		वापस;
	पूर्ण

	is_serdes = (bp->link_vars.link_status & LINK_STATUS_SERDES_LINK) > 0;
	link_up = bp->link_vars.link_up;
	/* offline tests are not supported in MF mode */
	अगर ((etest->flags & ETH_TEST_FL_OFFLINE) && !IS_MF(bp)) अणु
		पूर्णांक port = BP_PORT(bp);
		u32 val;

		/* save current value of input enable क्रम TX port IF */
		val = REG_RD(bp, NIG_REG_EGRESS_UMP0_IN_EN + port*4);
		/* disable input क्रम TX port IF */
		REG_WR(bp, NIG_REG_EGRESS_UMP0_IN_EN + port*4, 0);

		bnx2x_nic_unload(bp, UNLOAD_NORMAL, false);
		rc = bnx2x_nic_load(bp, LOAD_DIAG);
		अगर (rc) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			DP(BNX2X_MSG_ETHTOOL,
			   "Can't perform self-test, nic_load (for offline) failed\n");
			वापस;
		पूर्ण

		/* रुको until link state is restored */
		bnx2x_रुको_क्रम_link(bp, 1, is_serdes);

		अगर (bnx2x_test_रेजिस्टरs(bp) != 0) अणु
			buf[0] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		पूर्ण
		अगर (bnx2x_test_memory(bp) != 0) अणु
			buf[1] = 1;
			etest->flags |= ETH_TEST_FL_FAILED;
		पूर्ण

		buf[2] = bnx2x_test_loopback(bp); /* पूर्णांकernal LB */
		अगर (buf[2] != 0)
			etest->flags |= ETH_TEST_FL_FAILED;

		अगर (etest->flags & ETH_TEST_FL_EXTERNAL_LB) अणु
			buf[3] = bnx2x_test_ext_loopback(bp); /* बाह्यal LB */
			अगर (buf[3] != 0)
				etest->flags |= ETH_TEST_FL_FAILED;
			etest->flags |= ETH_TEST_FL_EXTERNAL_LB_DONE;
		पूर्ण

		bnx2x_nic_unload(bp, UNLOAD_NORMAL, false);

		/* restore input क्रम TX port IF */
		REG_WR(bp, NIG_REG_EGRESS_UMP0_IN_EN + port*4, val);
		rc = bnx2x_nic_load(bp, LOAD_NORMAL);
		अगर (rc) अणु
			etest->flags |= ETH_TEST_FL_FAILED;
			DP(BNX2X_MSG_ETHTOOL,
			   "Can't perform self-test, nic_load (for online) failed\n");
			वापस;
		पूर्ण
		/* रुको until link state is restored */
		bnx2x_रुको_क्रम_link(bp, link_up, is_serdes);
	पूर्ण

	अगर (bnx2x_test_पूर्णांकr(bp) != 0) अणु
		अगर (!IS_MF(bp))
			buf[5] = 1;
		अन्यथा
			buf[1] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	अगर (link_up) अणु
		cnt = 100;
		जबतक (bnx2x_link_test(bp, is_serdes) && --cnt)
			msleep(20);
	पूर्ण

	अगर (!cnt) अणु
		अगर (!IS_MF(bp))
			buf[6] = 1;
		अन्यथा
			buf[2] = 1;
		etest->flags |= ETH_TEST_FL_FAILED;
	पूर्ण
पूर्ण

#घोषणा IS_PORT_STAT(i)		(bnx2x_stats_arr[i].is_port_stat)
#घोषणा HIDE_PORT_STAT(bp)	IS_VF(bp)

/* ethtool statistics are displayed क्रम all regular ethernet queues and the
 * fcoe L2 queue अगर not disabled
 */
अटल पूर्णांक bnx2x_num_stat_queues(काष्ठा bnx2x *bp)
अणु
	वापस BNX2X_NUM_ETH_QUEUES(bp);
पूर्ण

अटल पूर्णांक bnx2x_get_sset_count(काष्ठा net_device *dev, पूर्णांक stringset)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक i, num_strings = 0;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		अगर (is_multi(bp)) अणु
			num_strings = bnx2x_num_stat_queues(bp) *
				      BNX2X_NUM_Q_STATS;
		पूर्ण अन्यथा
			num_strings = 0;
		अगर (HIDE_PORT_STAT(bp)) अणु
			क्रम (i = 0; i < BNX2X_NUM_STATS; i++)
				अगर (!IS_PORT_STAT(i))
					num_strings++;
		पूर्ण अन्यथा
			num_strings += BNX2X_NUM_STATS;

		वापस num_strings;

	हाल ETH_SS_TEST:
		वापस BNX2X_NUM_TESTS(bp);

	हाल ETH_SS_PRIV_FLAGS:
		वापस BNX2X_PRI_FLAG_LEN;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल u32 bnx2x_get_निजी_flags(काष्ठा net_device *dev)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u32 flags = 0;

	flags |= (!(bp->flags & NO_ISCSI_FLAG) ? 1 : 0) << BNX2X_PRI_FLAG_ISCSI;
	flags |= (!(bp->flags & NO_FCOE_FLAG)  ? 1 : 0) << BNX2X_PRI_FLAG_FCOE;
	flags |= (!!IS_MF_STORAGE_ONLY(bp)) << BNX2X_PRI_FLAG_STORAGE;

	वापस flags;
पूर्ण

अटल व्योम bnx2x_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *buf)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	पूर्णांक i, j, k, start;
	अक्षर queue_name[MAX_QUEUE_NAME_LEN+1];

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		k = 0;
		अगर (is_multi(bp)) अणु
			क्रम_each_eth_queue(bp, i) अणु
				स_रखो(queue_name, 0, माप(queue_name));
				snम_लिखो(queue_name, माप(queue_name),
					 "%d", i);
				क्रम (j = 0; j < BNX2X_NUM_Q_STATS; j++)
					snम_लिखो(buf + (k + j)*ETH_GSTRING_LEN,
						ETH_GSTRING_LEN,
						bnx2x_q_stats_arr[j].string,
						queue_name);
				k += BNX2X_NUM_Q_STATS;
			पूर्ण
		पूर्ण

		क्रम (i = 0, j = 0; i < BNX2X_NUM_STATS; i++) अणु
			अगर (HIDE_PORT_STAT(bp) && IS_PORT_STAT(i))
				जारी;
			म_नकल(buf + (k + j)*ETH_GSTRING_LEN,
				   bnx2x_stats_arr[i].string);
			j++;
		पूर्ण

		अवरोध;

	हाल ETH_SS_TEST:
		/* First 4 tests cannot be करोne in MF mode */
		अगर (!IS_MF(bp))
			start = 0;
		अन्यथा
			start = 4;
		स_नकल(buf, bnx2x_tests_str_arr + start,
		       ETH_GSTRING_LEN * BNX2X_NUM_TESTS(bp));
		अवरोध;

	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(buf, bnx2x_निजी_arr,
		       ETH_GSTRING_LEN * BNX2X_PRI_FLAG_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bnx2x_get_ethtool_stats(काष्ठा net_device *dev,
				    काष्ठा ethtool_stats *stats, u64 *buf)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u32 *hw_stats, *offset;
	पूर्णांक i, j, k = 0;

	अगर (is_multi(bp)) अणु
		क्रम_each_eth_queue(bp, i) अणु
			hw_stats = (u32 *)&bp->fp_stats[i].eth_q_stats;
			क्रम (j = 0; j < BNX2X_NUM_Q_STATS; j++) अणु
				अगर (bnx2x_q_stats_arr[j].size == 0) अणु
					/* skip this counter */
					buf[k + j] = 0;
					जारी;
				पूर्ण
				offset = (hw_stats +
					  bnx2x_q_stats_arr[j].offset);
				अगर (bnx2x_q_stats_arr[j].size == 4) अणु
					/* 4-byte counter */
					buf[k + j] = (u64) *offset;
					जारी;
				पूर्ण
				/* 8-byte counter */
				buf[k + j] = HILO_U64(*offset, *(offset + 1));
			पूर्ण
			k += BNX2X_NUM_Q_STATS;
		पूर्ण
	पूर्ण

	hw_stats = (u32 *)&bp->eth_stats;
	क्रम (i = 0, j = 0; i < BNX2X_NUM_STATS; i++) अणु
		अगर (HIDE_PORT_STAT(bp) && IS_PORT_STAT(i))
			जारी;
		अगर (bnx2x_stats_arr[i].size == 0) अणु
			/* skip this counter */
			buf[k + j] = 0;
			j++;
			जारी;
		पूर्ण
		offset = (hw_stats + bnx2x_stats_arr[i].offset);
		अगर (bnx2x_stats_arr[i].size == 4) अणु
			/* 4-byte counter */
			buf[k + j] = (u64) *offset;
			j++;
			जारी;
		पूर्ण
		/* 8-byte counter */
		buf[k + j] = HILO_U64(*offset, *(offset + 1));
		j++;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_set_phys_id(काष्ठा net_device *dev,
			     क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (!bnx2x_is_nvm_accessible(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		वापस -EAGAIN;
	पूर्ण

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 1;	/* cycle on/off once per second */

	हाल ETHTOOL_ID_ON:
		bnx2x_acquire_phy_lock(bp);
		bnx2x_set_led(&bp->link_params, &bp->link_vars,
			      LED_MODE_ON, SPEED_1000);
		bnx2x_release_phy_lock(bp);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		bnx2x_acquire_phy_lock(bp);
		bnx2x_set_led(&bp->link_params, &bp->link_vars,
			      LED_MODE_FRONT_PANEL_OFF, 0);
		bnx2x_release_phy_lock(bp);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		bnx2x_acquire_phy_lock(bp);
		bnx2x_set_led(&bp->link_params, &bp->link_vars,
			      LED_MODE_OPER,
			      bp->link_vars.line_speed);
		bnx2x_release_phy_lock(bp);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_get_rss_flags(काष्ठा bnx2x *bp, काष्ठा ethtool_rxnfc *info)
अणु
	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		info->data = RXH_IP_SRC | RXH_IP_DST |
			     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अवरोध;
	हाल UDP_V4_FLOW:
		अगर (bp->rss_conf_obj.udp_rss_v4)
			info->data = RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अन्यथा
			info->data = RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल UDP_V6_FLOW:
		अगर (bp->rss_conf_obj.udp_rss_v6)
			info->data = RXH_IP_SRC | RXH_IP_DST |
				     RXH_L4_B_0_1 | RXH_L4_B_2_3;
		अन्यथा
			info->data = RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		info->data = RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		info->data = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
			   u32 *rules __always_unused)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = BNX2X_NUM_ETH_QUEUES(bp);
		वापस 0;
	हाल ETHTOOL_GRXFH:
		वापस bnx2x_get_rss_flags(bp, info);
	शेष:
		DP(BNX2X_MSG_ETHTOOL, "Command parameters not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_set_rss_flags(काष्ठा bnx2x *bp, काष्ठा ethtool_rxnfc *info)
अणु
	पूर्णांक udp_rss_requested;

	DP(BNX2X_MSG_ETHTOOL,
	   "Set rss flags command parameters: flow type = %d, data = %llu\n",
	   info->flow_type, info->data);

	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
	हाल TCP_V6_FLOW:
		/* For TCP only 4-tupple hash is supported */
		अगर (info->data ^ (RXH_IP_SRC | RXH_IP_DST |
				  RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "Command parameters not supported\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	हाल UDP_V4_FLOW:
	हाल UDP_V6_FLOW:
		/* For UDP either 2-tupple hash or 4-tupple hash is supported */
		अगर (info->data == (RXH_IP_SRC | RXH_IP_DST |
				   RXH_L4_B_0_1 | RXH_L4_B_2_3))
			udp_rss_requested = 1;
		अन्यथा अगर (info->data == (RXH_IP_SRC | RXH_IP_DST))
			udp_rss_requested = 0;
		अन्यथा
			वापस -EINVAL;

		अगर (CHIP_IS_E1x(bp) && udp_rss_requested) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "57710, 57711 boards don't support RSS according to UDP 4-tuple\n");
			वापस -EINVAL;
		पूर्ण

		अगर ((info->flow_type == UDP_V4_FLOW) &&
		    (bp->rss_conf_obj.udp_rss_v4 != udp_rss_requested)) अणु
			bp->rss_conf_obj.udp_rss_v4 = udp_rss_requested;
			DP(BNX2X_MSG_ETHTOOL,
			   "rss re-configured, UDP 4-tupple %s\n",
			   udp_rss_requested ? "enabled" : "disabled");
			अगर (bp->state == BNX2X_STATE_OPEN)
				वापस bnx2x_rss(bp, &bp->rss_conf_obj, false,
						 true);
		पूर्ण अन्यथा अगर ((info->flow_type == UDP_V6_FLOW) &&
			   (bp->rss_conf_obj.udp_rss_v6 != udp_rss_requested)) अणु
			bp->rss_conf_obj.udp_rss_v6 = udp_rss_requested;
			DP(BNX2X_MSG_ETHTOOL,
			   "rss re-configured, UDP 4-tupple %s\n",
			   udp_rss_requested ? "enabled" : "disabled");
			अगर (bp->state == BNX2X_STATE_OPEN)
				वापस bnx2x_rss(bp, &bp->rss_conf_obj, false,
						 true);
		पूर्ण
		वापस 0;

	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		/* For IP only 2-tupple hash is supported */
		अगर (info->data ^ (RXH_IP_SRC | RXH_IP_DST)) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "Command parameters not supported\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IP_USER_FLOW:
	हाल ETHER_FLOW:
		/* RSS is not supported क्रम these protocols */
		अगर (info->data) अणु
			DP(BNX2X_MSG_ETHTOOL,
			   "Command parameters not supported\n");
			वापस -EINVAL;
		पूर्ण
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2x_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	चयन (info->cmd) अणु
	हाल ETHTOOL_SRXFH:
		वापस bnx2x_set_rss_flags(bp, info);
	शेष:
		DP(BNX2X_MSG_ETHTOOL, "Command parameters not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 bnx2x_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	वापस T_ETH_INसूचीECTION_TABLE_SIZE;
पूर्ण

अटल पूर्णांक bnx2x_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key,
			  u8 *hfunc)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	u8 ind_table[T_ETH_INसूचीECTION_TABLE_SIZE] = अणु0पूर्ण;
	माप_प्रकार i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (!indir)
		वापस 0;

	/* Get the current configuration of the RSS indirection table */
	bnx2x_get_rss_ind_table(&bp->rss_conf_obj, ind_table);

	/*
	 * We can't use a स_नकल() as an पूर्णांकernal storage of an
	 * indirection table is a u8 array जबतक indir->ring_index
	 * poपूर्णांकs to an array of u32.
	 *
	 * Indirection table contains the FW Client IDs, so we need to
	 * align the वापसed table to the Client ID of the leading RSS
	 * queue.
	 */
	क्रम (i = 0; i < T_ETH_INसूचीECTION_TABLE_SIZE; i++)
		indir[i] = ind_table[i] - bp->fp->cl_id;

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2x_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
			  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);
	माप_प्रकार i;

	/* We require at least one supported parameter to be changed and no
	 * change in any of the unsupported parameters
	 */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;

	अगर (!indir)
		वापस 0;

	क्रम (i = 0; i < T_ETH_INसूचीECTION_TABLE_SIZE; i++) अणु
		/*
		 * The same as in bnx2x_get_rxfh: we can't use a स_नकल()
		 * as an पूर्णांकernal storage of an indirection table is a u8 array
		 * जबतक indir->ring_index poपूर्णांकs to an array of u32.
		 *
		 * Indirection table contains the FW Client IDs, so we need to
		 * align the received table to the Client ID of the leading RSS
		 * queue
		 */
		bp->rss_conf_obj.ind_table[i] = indir[i] + bp->fp->cl_id;
	पूर्ण

	अगर (bp->state == BNX2X_STATE_OPEN)
		वापस bnx2x_config_rss_eth(bp, false);

	वापस 0;
पूर्ण

/**
 * bnx2x_get_channels - माला_लो the number of RSS queues.
 *
 * @dev:		net device
 * @channels:		वापसs the number of max / current queues
 */
अटल व्योम bnx2x_get_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *channels)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	channels->max_combined = BNX2X_MAX_RSS_COUNT(bp);
	channels->combined_count = BNX2X_NUM_ETH_QUEUES(bp);
पूर्ण

/**
 * bnx2x_change_num_queues - change the number of RSS queues.
 *
 * @bp:			bnx2x निजी काष्ठाure
 * @num_rss:		rss count
 *
 * Re-configure पूर्णांकerrupt mode to get the new number of MSI-X
 * vectors and re-add NAPI objects.
 */
अटल व्योम bnx2x_change_num_queues(काष्ठा bnx2x *bp, पूर्णांक num_rss)
अणु
	bnx2x_disable_msi(bp);
	bp->num_ethernet_queues = num_rss;
	bp->num_queues = bp->num_ethernet_queues + bp->num_cnic_queues;
	BNX2X_DEV_INFO("set number of queues to %d\n", bp->num_queues);
	bnx2x_set_पूर्णांक_mode(bp);
पूर्ण

/**
 * bnx2x_set_channels - sets the number of RSS queues.
 *
 * @dev:		net device
 * @channels:		includes the number of queues requested
 */
अटल पूर्णांक bnx2x_set_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *channels)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	DP(BNX2X_MSG_ETHTOOL,
	   "set-channels command parameters: rx = %d, tx = %d, other = %d, combined = %d\n",
	   channels->rx_count, channels->tx_count, channels->other_count,
	   channels->combined_count);

	अगर (pci_num_vf(bp->pdev)) अणु
		DP(BNX2X_MSG_IOV, "VFs are enabled, can not set channels\n");
		वापस -EPERM;
	पूर्ण

	/* We करोn't support separate rx / tx channels.
	 * We करोn't allow setting 'other' channels.
	 */
	अगर (channels->rx_count || channels->tx_count || channels->other_count
	    || (channels->combined_count == 0) ||
	    (channels->combined_count > BNX2X_MAX_RSS_COUNT(bp))) अणु
		DP(BNX2X_MSG_ETHTOOL, "command parameters not supported\n");
		वापस -EINVAL;
	पूर्ण

	/* Check अगर there was a change in the active parameters */
	अगर (channels->combined_count == BNX2X_NUM_ETH_QUEUES(bp)) अणु
		DP(BNX2X_MSG_ETHTOOL, "No change in active parameters\n");
		वापस 0;
	पूर्ण

	/* Set the requested number of queues in bp context.
	 * Note that the actual number of queues created during load may be
	 * less than requested अगर memory is low.
	 */
	अगर (unlikely(!netअगर_running(dev))) अणु
		bnx2x_change_num_queues(bp, channels->combined_count);
		वापस 0;
	पूर्ण
	bnx2x_nic_unload(bp, UNLOAD_NORMAL, true);
	bnx2x_change_num_queues(bp, channels->combined_count);
	वापस bnx2x_nic_load(bp, LOAD_NORMAL);
पूर्ण

अटल पूर्णांक bnx2x_get_ts_info(काष्ठा net_device *dev,
			     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा bnx2x *bp = netdev_priv(dev);

	अगर (bp->flags & PTP_SUPPORTED) अणु
		info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
					SOF_TIMESTAMPING_RX_SOFTWARE |
					SOF_TIMESTAMPING_SOFTWARE |
					SOF_TIMESTAMPING_TX_HARDWARE |
					SOF_TIMESTAMPING_RX_HARDWARE |
					SOF_TIMESTAMPING_RAW_HARDWARE;

		अगर (bp->ptp_घड़ी)
			info->phc_index = ptp_घड़ी_index(bp->ptp_घड़ी);
		अन्यथा
			info->phc_index = -1;

		info->rx_filters = (1 << HWTSTAMP_FILTER_NONE) |
				   (1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
				   (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
				   (1 << HWTSTAMP_FILTER_PTP_V2_EVENT);

		info->tx_types = (1 << HWTSTAMP_TX_OFF)|(1 << HWTSTAMP_TX_ON);

		वापस 0;
	पूर्ण

	वापस ethtool_op_get_ts_info(dev, info);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops bnx2x_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo		= bnx2x_get_drvinfo,
	.get_regs_len		= bnx2x_get_regs_len,
	.get_regs		= bnx2x_get_regs,
	.get_dump_flag		= bnx2x_get_dump_flag,
	.get_dump_data		= bnx2x_get_dump_data,
	.set_dump		= bnx2x_set_dump,
	.get_wol		= bnx2x_get_wol,
	.set_wol		= bnx2x_set_wol,
	.get_msglevel		= bnx2x_get_msglevel,
	.set_msglevel		= bnx2x_set_msglevel,
	.nway_reset		= bnx2x_nway_reset,
	.get_link		= bnx2x_get_link,
	.get_eeprom_len		= bnx2x_get_eeprom_len,
	.get_eeprom		= bnx2x_get_eeprom,
	.set_eeprom		= bnx2x_set_eeprom,
	.get_coalesce		= bnx2x_get_coalesce,
	.set_coalesce		= bnx2x_set_coalesce,
	.get_ringparam		= bnx2x_get_ringparam,
	.set_ringparam		= bnx2x_set_ringparam,
	.get_छोड़ोparam		= bnx2x_get_छोड़ोparam,
	.set_छोड़ोparam		= bnx2x_set_छोड़ोparam,
	.self_test		= bnx2x_self_test,
	.get_sset_count		= bnx2x_get_sset_count,
	.get_priv_flags		= bnx2x_get_निजी_flags,
	.get_strings		= bnx2x_get_strings,
	.set_phys_id		= bnx2x_set_phys_id,
	.get_ethtool_stats	= bnx2x_get_ethtool_stats,
	.get_rxnfc		= bnx2x_get_rxnfc,
	.set_rxnfc		= bnx2x_set_rxnfc,
	.get_rxfh_indir_size	= bnx2x_get_rxfh_indir_size,
	.get_rxfh		= bnx2x_get_rxfh,
	.set_rxfh		= bnx2x_set_rxfh,
	.get_channels		= bnx2x_get_channels,
	.set_channels		= bnx2x_set_channels,
	.get_module_info	= bnx2x_get_module_info,
	.get_module_eeprom	= bnx2x_get_module_eeprom,
	.get_eee		= bnx2x_get_eee,
	.set_eee		= bnx2x_set_eee,
	.get_ts_info		= bnx2x_get_ts_info,
	.get_link_ksettings	= bnx2x_get_link_ksettings,
	.set_link_ksettings	= bnx2x_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops bnx2x_vf_ethtool_ops = अणु
	.get_drvinfo		= bnx2x_get_drvinfo,
	.get_msglevel		= bnx2x_get_msglevel,
	.set_msglevel		= bnx2x_set_msglevel,
	.get_link		= bnx2x_get_link,
	.get_coalesce		= bnx2x_get_coalesce,
	.get_ringparam		= bnx2x_get_ringparam,
	.set_ringparam		= bnx2x_set_ringparam,
	.get_sset_count		= bnx2x_get_sset_count,
	.get_strings		= bnx2x_get_strings,
	.get_ethtool_stats	= bnx2x_get_ethtool_stats,
	.get_rxnfc		= bnx2x_get_rxnfc,
	.set_rxnfc		= bnx2x_set_rxnfc,
	.get_rxfh_indir_size	= bnx2x_get_rxfh_indir_size,
	.get_rxfh		= bnx2x_get_rxfh,
	.set_rxfh		= bnx2x_set_rxfh,
	.get_channels		= bnx2x_get_channels,
	.set_channels		= bnx2x_set_channels,
	.get_link_ksettings	= bnx2x_get_vf_link_ksettings,
पूर्ण;

व्योम bnx2x_set_ethtool_ops(काष्ठा bnx2x *bp, काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = (IS_PF(bp)) ?
		&bnx2x_ethtool_ops : &bnx2x_vf_ethtool_ops;
पूर्ण
