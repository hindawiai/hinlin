<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*******************************************************************************
  STMMAC Ethtool support

  Copyright (C) 2007-2009  STMicroelectronics Ltd


  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>
*******************************************************************************/

#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mii.h>
#समावेश <linux/phylink.h>
#समावेश <linux/net_tstamp.h>
#समावेश <यंत्र/पन.स>

#समावेश "stmmac.h"
#समावेश "dwmac_dma.h"
#समावेश "dwxgmac2.h"

#घोषणा REG_SPACE_SIZE	0x1060
#घोषणा MAC100_ETHTOOL_NAME	"st_mac100"
#घोषणा GMAC_ETHTOOL_NAME	"st_gmac"
#घोषणा XGMAC_ETHTOOL_NAME	"st_xgmac"

#घोषणा ETHTOOL_DMA_OFFSET	55

काष्ठा sपंचांगmac_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा STMMAC_STAT(m)	\
	अणु #m, माप_field(काष्ठा sपंचांगmac_extra_stats, m),	\
	दुरत्व(काष्ठा sपंचांगmac_priv, xstats.m)पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_stats sपंचांगmac_gstrings_stats[] = अणु
	/* Transmit errors */
	STMMAC_STAT(tx_underflow),
	STMMAC_STAT(tx_carrier),
	STMMAC_STAT(tx_losscarrier),
	STMMAC_STAT(vlan_tag),
	STMMAC_STAT(tx_deferred),
	STMMAC_STAT(tx_vlan),
	STMMAC_STAT(tx_jabber),
	STMMAC_STAT(tx_frame_flushed),
	STMMAC_STAT(tx_payload_error),
	STMMAC_STAT(tx_ip_header_error),
	/* Receive errors */
	STMMAC_STAT(rx_desc),
	STMMAC_STAT(sa_filter_fail),
	STMMAC_STAT(overflow_error),
	STMMAC_STAT(ipc_csum_error),
	STMMAC_STAT(rx_collision),
	STMMAC_STAT(rx_crc_errors),
	STMMAC_STAT(dribbling_bit),
	STMMAC_STAT(rx_length),
	STMMAC_STAT(rx_mii),
	STMMAC_STAT(rx_multicast),
	STMMAC_STAT(rx_gmac_overflow),
	STMMAC_STAT(rx_watchकरोg),
	STMMAC_STAT(da_rx_filter_fail),
	STMMAC_STAT(sa_rx_filter_fail),
	STMMAC_STAT(rx_missed_cntr),
	STMMAC_STAT(rx_overflow_cntr),
	STMMAC_STAT(rx_vlan),
	STMMAC_STAT(rx_split_hdr_pkt_n),
	/* Tx/Rx IRQ error info */
	STMMAC_STAT(tx_undeflow_irq),
	STMMAC_STAT(tx_process_stopped_irq),
	STMMAC_STAT(tx_jabber_irq),
	STMMAC_STAT(rx_overflow_irq),
	STMMAC_STAT(rx_buf_unav_irq),
	STMMAC_STAT(rx_process_stopped_irq),
	STMMAC_STAT(rx_watchकरोg_irq),
	STMMAC_STAT(tx_early_irq),
	STMMAC_STAT(fatal_bus_error_irq),
	/* Tx/Rx IRQ Events */
	STMMAC_STAT(rx_early_irq),
	STMMAC_STAT(threshold),
	STMMAC_STAT(tx_pkt_n),
	STMMAC_STAT(rx_pkt_n),
	STMMAC_STAT(normal_irq_n),
	STMMAC_STAT(rx_normal_irq_n),
	STMMAC_STAT(napi_poll),
	STMMAC_STAT(tx_normal_irq_n),
	STMMAC_STAT(tx_clean),
	STMMAC_STAT(tx_set_ic_bit),
	STMMAC_STAT(irq_receive_pmt_irq_n),
	/* MMC info */
	STMMAC_STAT(mmc_tx_irq_n),
	STMMAC_STAT(mmc_rx_irq_n),
	STMMAC_STAT(mmc_rx_csum_offload_irq_n),
	/* EEE */
	STMMAC_STAT(irq_tx_path_in_lpi_mode_n),
	STMMAC_STAT(irq_tx_path_निकास_lpi_mode_n),
	STMMAC_STAT(irq_rx_path_in_lpi_mode_n),
	STMMAC_STAT(irq_rx_path_निकास_lpi_mode_n),
	STMMAC_STAT(phy_eee_wakeup_error_n),
	/* Extended RDES status */
	STMMAC_STAT(ip_hdr_err),
	STMMAC_STAT(ip_payload_err),
	STMMAC_STAT(ip_csum_bypassed),
	STMMAC_STAT(ipv4_pkt_rcvd),
	STMMAC_STAT(ipv6_pkt_rcvd),
	STMMAC_STAT(no_ptp_rx_msg_type_ext),
	STMMAC_STAT(ptp_rx_msg_type_sync),
	STMMAC_STAT(ptp_rx_msg_type_follow_up),
	STMMAC_STAT(ptp_rx_msg_type_delay_req),
	STMMAC_STAT(ptp_rx_msg_type_delay_resp),
	STMMAC_STAT(ptp_rx_msg_type_pdelay_req),
	STMMAC_STAT(ptp_rx_msg_type_pdelay_resp),
	STMMAC_STAT(ptp_rx_msg_type_pdelay_follow_up),
	STMMAC_STAT(ptp_rx_msg_type_announce),
	STMMAC_STAT(ptp_rx_msg_type_management),
	STMMAC_STAT(ptp_rx_msg_pkt_reserved_type),
	STMMAC_STAT(ptp_frame_type),
	STMMAC_STAT(ptp_ver),
	STMMAC_STAT(बारtamp_dropped),
	STMMAC_STAT(av_pkt_rcvd),
	STMMAC_STAT(av_tagged_pkt_rcvd),
	STMMAC_STAT(vlan_tag_priority_val),
	STMMAC_STAT(l3_filter_match),
	STMMAC_STAT(l4_filter_match),
	STMMAC_STAT(l3_l4_filter_no_match),
	/* PCS */
	STMMAC_STAT(irq_pcs_ane_n),
	STMMAC_STAT(irq_pcs_link_n),
	STMMAC_STAT(irq_rgmii_n),
	/* DEBUG */
	STMMAC_STAT(mtl_tx_status_fअगरo_full),
	STMMAC_STAT(mtl_tx_fअगरo_not_empty),
	STMMAC_STAT(mmtl_fअगरo_ctrl),
	STMMAC_STAT(mtl_tx_fअगरo_पढ़ो_ctrl_ग_लिखो),
	STMMAC_STAT(mtl_tx_fअगरo_पढ़ो_ctrl_रुको),
	STMMAC_STAT(mtl_tx_fअगरo_पढ़ो_ctrl_पढ़ो),
	STMMAC_STAT(mtl_tx_fअगरo_पढ़ो_ctrl_idle),
	STMMAC_STAT(mac_tx_in_छोड़ो),
	STMMAC_STAT(mac_tx_frame_ctrl_xfer),
	STMMAC_STAT(mac_tx_frame_ctrl_idle),
	STMMAC_STAT(mac_tx_frame_ctrl_रुको),
	STMMAC_STAT(mac_tx_frame_ctrl_छोड़ो),
	STMMAC_STAT(mac_gmii_tx_proto_engine),
	STMMAC_STAT(mtl_rx_fअगरo_fill_level_full),
	STMMAC_STAT(mtl_rx_fअगरo_fill_above_thresh),
	STMMAC_STAT(mtl_rx_fअगरo_fill_below_thresh),
	STMMAC_STAT(mtl_rx_fअगरo_fill_level_empty),
	STMMAC_STAT(mtl_rx_fअगरo_पढ़ो_ctrl_flush),
	STMMAC_STAT(mtl_rx_fअगरo_पढ़ो_ctrl_पढ़ो_data),
	STMMAC_STAT(mtl_rx_fअगरo_पढ़ो_ctrl_status),
	STMMAC_STAT(mtl_rx_fअगरo_पढ़ो_ctrl_idle),
	STMMAC_STAT(mtl_rx_fअगरo_ctrl_active),
	STMMAC_STAT(mac_rx_frame_ctrl_fअगरo),
	STMMAC_STAT(mac_gmii_rx_proto_engine),
	/* TSO */
	STMMAC_STAT(tx_tso_frames),
	STMMAC_STAT(tx_tso_nfrags),
	/* EST */
	STMMAC_STAT(mtl_est_cgce),
	STMMAC_STAT(mtl_est_hlbs),
	STMMAC_STAT(mtl_est_hlbf),
	STMMAC_STAT(mtl_est_btre),
	STMMAC_STAT(mtl_est_btrlm),
पूर्ण;
#घोषणा STMMAC_STATS_LEN ARRAY_SIZE(sपंचांगmac_gstrings_stats)

/* HW MAC Management counters (अगर supported) */
#घोषणा STMMAC_MMC_STAT(m)	\
	अणु #m, माप_field(काष्ठा sपंचांगmac_counters, m),	\
	दुरत्व(काष्ठा sपंचांगmac_priv, mmc.m)पूर्ण

अटल स्थिर काष्ठा sपंचांगmac_stats sपंचांगmac_mmc[] = अणु
	STMMAC_MMC_STAT(mmc_tx_octetcount_gb),
	STMMAC_MMC_STAT(mmc_tx_framecount_gb),
	STMMAC_MMC_STAT(mmc_tx_broadcastframe_g),
	STMMAC_MMC_STAT(mmc_tx_multicastframe_g),
	STMMAC_MMC_STAT(mmc_tx_64_octets_gb),
	STMMAC_MMC_STAT(mmc_tx_65_to_127_octets_gb),
	STMMAC_MMC_STAT(mmc_tx_128_to_255_octets_gb),
	STMMAC_MMC_STAT(mmc_tx_256_to_511_octets_gb),
	STMMAC_MMC_STAT(mmc_tx_512_to_1023_octets_gb),
	STMMAC_MMC_STAT(mmc_tx_1024_to_max_octets_gb),
	STMMAC_MMC_STAT(mmc_tx_unicast_gb),
	STMMAC_MMC_STAT(mmc_tx_multicast_gb),
	STMMAC_MMC_STAT(mmc_tx_broadcast_gb),
	STMMAC_MMC_STAT(mmc_tx_underflow_error),
	STMMAC_MMC_STAT(mmc_tx_singlecol_g),
	STMMAC_MMC_STAT(mmc_tx_multicol_g),
	STMMAC_MMC_STAT(mmc_tx_deferred),
	STMMAC_MMC_STAT(mmc_tx_latecol),
	STMMAC_MMC_STAT(mmc_tx_exesscol),
	STMMAC_MMC_STAT(mmc_tx_carrier_error),
	STMMAC_MMC_STAT(mmc_tx_octetcount_g),
	STMMAC_MMC_STAT(mmc_tx_framecount_g),
	STMMAC_MMC_STAT(mmc_tx_excessdef),
	STMMAC_MMC_STAT(mmc_tx_छोड़ो_frame),
	STMMAC_MMC_STAT(mmc_tx_vlan_frame_g),
	STMMAC_MMC_STAT(mmc_rx_framecount_gb),
	STMMAC_MMC_STAT(mmc_rx_octetcount_gb),
	STMMAC_MMC_STAT(mmc_rx_octetcount_g),
	STMMAC_MMC_STAT(mmc_rx_broadcastframe_g),
	STMMAC_MMC_STAT(mmc_rx_multicastframe_g),
	STMMAC_MMC_STAT(mmc_rx_crc_error),
	STMMAC_MMC_STAT(mmc_rx_align_error),
	STMMAC_MMC_STAT(mmc_rx_run_error),
	STMMAC_MMC_STAT(mmc_rx_jabber_error),
	STMMAC_MMC_STAT(mmc_rx_undersize_g),
	STMMAC_MMC_STAT(mmc_rx_oversize_g),
	STMMAC_MMC_STAT(mmc_rx_64_octets_gb),
	STMMAC_MMC_STAT(mmc_rx_65_to_127_octets_gb),
	STMMAC_MMC_STAT(mmc_rx_128_to_255_octets_gb),
	STMMAC_MMC_STAT(mmc_rx_256_to_511_octets_gb),
	STMMAC_MMC_STAT(mmc_rx_512_to_1023_octets_gb),
	STMMAC_MMC_STAT(mmc_rx_1024_to_max_octets_gb),
	STMMAC_MMC_STAT(mmc_rx_unicast_g),
	STMMAC_MMC_STAT(mmc_rx_length_error),
	STMMAC_MMC_STAT(mmc_rx_स्वतःfrangetype),
	STMMAC_MMC_STAT(mmc_rx_छोड़ो_frames),
	STMMAC_MMC_STAT(mmc_rx_fअगरo_overflow),
	STMMAC_MMC_STAT(mmc_rx_vlan_frames_gb),
	STMMAC_MMC_STAT(mmc_rx_watchकरोg_error),
	STMMAC_MMC_STAT(mmc_rx_ipc_पूर्णांकr_mask),
	STMMAC_MMC_STAT(mmc_rx_ipc_पूर्णांकr),
	STMMAC_MMC_STAT(mmc_rx_ipv4_gd),
	STMMAC_MMC_STAT(mmc_rx_ipv4_hderr),
	STMMAC_MMC_STAT(mmc_rx_ipv4_nopay),
	STMMAC_MMC_STAT(mmc_rx_ipv4_frag),
	STMMAC_MMC_STAT(mmc_rx_ipv4_udsbl),
	STMMAC_MMC_STAT(mmc_rx_ipv4_gd_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv4_hderr_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv4_nopay_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv4_frag_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv4_udsbl_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv6_gd_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv6_hderr_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv6_nopay_octets),
	STMMAC_MMC_STAT(mmc_rx_ipv6_gd),
	STMMAC_MMC_STAT(mmc_rx_ipv6_hderr),
	STMMAC_MMC_STAT(mmc_rx_ipv6_nopay),
	STMMAC_MMC_STAT(mmc_rx_udp_gd),
	STMMAC_MMC_STAT(mmc_rx_udp_err),
	STMMAC_MMC_STAT(mmc_rx_tcp_gd),
	STMMAC_MMC_STAT(mmc_rx_tcp_err),
	STMMAC_MMC_STAT(mmc_rx_icmp_gd),
	STMMAC_MMC_STAT(mmc_rx_icmp_err),
	STMMAC_MMC_STAT(mmc_rx_udp_gd_octets),
	STMMAC_MMC_STAT(mmc_rx_udp_err_octets),
	STMMAC_MMC_STAT(mmc_rx_tcp_gd_octets),
	STMMAC_MMC_STAT(mmc_rx_tcp_err_octets),
	STMMAC_MMC_STAT(mmc_rx_icmp_gd_octets),
	STMMAC_MMC_STAT(mmc_rx_icmp_err_octets),
	STMMAC_MMC_STAT(mmc_tx_fpe_fragment_cntr),
	STMMAC_MMC_STAT(mmc_tx_hold_req_cntr),
	STMMAC_MMC_STAT(mmc_rx_packet_assembly_err_cntr),
	STMMAC_MMC_STAT(mmc_rx_packet_smd_err_cntr),
	STMMAC_MMC_STAT(mmc_rx_packet_assembly_ok_cntr),
	STMMAC_MMC_STAT(mmc_rx_fpe_fragment_cntr),
पूर्ण;
#घोषणा STMMAC_MMC_STATS_LEN ARRAY_SIZE(sपंचांगmac_mmc)

अटल व्योम sपंचांगmac_ethtool_getdrvinfo(काष्ठा net_device *dev,
				      काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (priv->plat->has_gmac || priv->plat->has_gmac4)
		strlcpy(info->driver, GMAC_ETHTOOL_NAME, माप(info->driver));
	अन्यथा अगर (priv->plat->has_xgmac)
		strlcpy(info->driver, XGMAC_ETHTOOL_NAME, माप(info->driver));
	अन्यथा
		strlcpy(info->driver, MAC100_ETHTOOL_NAME,
			माप(info->driver));

	अगर (priv->plat->pdev) अणु
		strlcpy(info->bus_info, pci_name(priv->plat->pdev),
			माप(info->bus_info));
	पूर्ण
	strlcpy(info->version, DRV_MODULE_VERSION, माप(info->version));
पूर्ण

अटल पूर्णांक sपंचांगmac_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (priv->hw->pcs & STMMAC_PCS_RGMII ||
	    priv->hw->pcs & STMMAC_PCS_SGMII) अणु
		काष्ठा rgmii_adv adv;
		u32 supported, advertising, lp_advertising;

		अगर (!priv->xstats.pcs_link) अणु
			cmd->base.speed = SPEED_UNKNOWN;
			cmd->base.duplex = DUPLEX_UNKNOWN;
			वापस 0;
		पूर्ण
		cmd->base.duplex = priv->xstats.pcs_duplex;

		cmd->base.speed = priv->xstats.pcs_speed;

		/* Get and convert ADV/LP_ADV from the HW AN रेजिस्टरs */
		अगर (sपंचांगmac_pcs_get_adv_lp(priv, priv->ioaddr, &adv))
			वापस -EOPNOTSUPP;	/* should never happen indeed */

		/* Encoding of PSE bits is defined in 802.3z, 37.2.1.4 */

		ethtool_convert_link_mode_to_legacy_u32(
			&supported, cmd->link_modes.supported);
		ethtool_convert_link_mode_to_legacy_u32(
			&advertising, cmd->link_modes.advertising);
		ethtool_convert_link_mode_to_legacy_u32(
			&lp_advertising, cmd->link_modes.lp_advertising);

		अगर (adv.छोड़ो & STMMAC_PCS_PAUSE)
			advertising |= ADVERTISED_Pause;
		अगर (adv.छोड़ो & STMMAC_PCS_ASYM_PAUSE)
			advertising |= ADVERTISED_Asym_Pause;
		अगर (adv.lp_छोड़ो & STMMAC_PCS_PAUSE)
			lp_advertising |= ADVERTISED_Pause;
		अगर (adv.lp_छोड़ो & STMMAC_PCS_ASYM_PAUSE)
			lp_advertising |= ADVERTISED_Asym_Pause;

		/* Reg49[3] always set because ANE is always supported */
		cmd->base.स्वतःneg = ADVERTISED_Autoneg;
		supported |= SUPPORTED_Autoneg;
		advertising |= ADVERTISED_Autoneg;
		lp_advertising |= ADVERTISED_Autoneg;

		अगर (adv.duplex) अणु
			supported |= (SUPPORTED_1000baseT_Full |
				      SUPPORTED_100baseT_Full |
				      SUPPORTED_10baseT_Full);
			advertising |= (ADVERTISED_1000baseT_Full |
					ADVERTISED_100baseT_Full |
					ADVERTISED_10baseT_Full);
		पूर्ण अन्यथा अणु
			supported |= (SUPPORTED_1000baseT_Half |
				      SUPPORTED_100baseT_Half |
				      SUPPORTED_10baseT_Half);
			advertising |= (ADVERTISED_1000baseT_Half |
					ADVERTISED_100baseT_Half |
					ADVERTISED_10baseT_Half);
		पूर्ण
		अगर (adv.lp_duplex)
			lp_advertising |= (ADVERTISED_1000baseT_Full |
					   ADVERTISED_100baseT_Full |
					   ADVERTISED_10baseT_Full);
		अन्यथा
			lp_advertising |= (ADVERTISED_1000baseT_Half |
					   ADVERTISED_100baseT_Half |
					   ADVERTISED_10baseT_Half);
		cmd->base.port = PORT_OTHER;

		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising, advertising);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.lp_advertising, lp_advertising);

		वापस 0;
	पूर्ण

	वापस phylink_ethtool_ksettings_get(priv->phylink, cmd);
पूर्ण

अटल पूर्णांक
sपंचांगmac_ethtool_set_link_ksettings(काष्ठा net_device *dev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (priv->hw->pcs & STMMAC_PCS_RGMII ||
	    priv->hw->pcs & STMMAC_PCS_SGMII) अणु
		u32 mask = ADVERTISED_Autoneg | ADVERTISED_Pause;

		/* Only support ANE */
		अगर (cmd->base.स्वतःneg != AUTONEG_ENABLE)
			वापस -EINVAL;

		mask &= (ADVERTISED_1000baseT_Half |
			ADVERTISED_1000baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full |
			ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full);

		mutex_lock(&priv->lock);
		sपंचांगmac_pcs_ctrl_ane(priv, priv->ioaddr, 1, priv->hw->ps, 0);
		mutex_unlock(&priv->lock);

		वापस 0;
	पूर्ण

	वापस phylink_ethtool_ksettings_set(priv->phylink, cmd);
पूर्ण

अटल u32 sपंचांगmac_ethtool_geपंचांगsglevel(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	वापस priv->msg_enable;
पूर्ण

अटल व्योम sपंचांगmac_ethtool_seपंचांगsglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	priv->msg_enable = level;

पूर्ण

अटल पूर्णांक sपंचांगmac_check_अगर_running(काष्ठा net_device *dev)
अणु
	अगर (!netअगर_running(dev))
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_ethtool_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (priv->plat->has_xgmac)
		वापस XGMAC_REGSIZE * 4;
	वापस REG_SPACE_SIZE;
पूर्ण

अटल व्योम sपंचांगmac_ethtool_gregs(काष्ठा net_device *dev,
			  काष्ठा ethtool_regs *regs, व्योम *space)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 *reg_space = (u32 *) space;

	sपंचांगmac_dump_mac_regs(priv, priv->hw, reg_space);
	sपंचांगmac_dump_dma_regs(priv, priv->ioaddr, reg_space);

	अगर (!priv->plat->has_xgmac) अणु
		/* Copy DMA रेजिस्टरs to where ethtool expects them */
		स_नकल(&reg_space[ETHTOOL_DMA_OFFSET],
		       &reg_space[DMA_BUS_MODE / 4],
		       NUM_DWMAC1000_DMA_REGS * 4);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	वापस phylink_ethtool_nway_reset(priv->phylink);
पूर्ण

अटल व्योम sपंचांगmac_get_ringparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(netdev);

	ring->rx_max_pending = DMA_MAX_RX_SIZE;
	ring->tx_max_pending = DMA_MAX_TX_SIZE;
	ring->rx_pending = priv->dma_rx_size;
	ring->tx_pending = priv->dma_tx_size;
पूर्ण

अटल पूर्णांक sपंचांगmac_set_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending ||
	    ring->rx_pending < DMA_MIN_RX_SIZE ||
	    ring->rx_pending > DMA_MAX_RX_SIZE ||
	    !is_घातer_of_2(ring->rx_pending) ||
	    ring->tx_pending < DMA_MIN_TX_SIZE ||
	    ring->tx_pending > DMA_MAX_TX_SIZE ||
	    !is_घातer_of_2(ring->tx_pending))
		वापस -EINVAL;

	वापस sपंचांगmac_reinit_ringparam(netdev, ring->rx_pending,
				       ring->tx_pending);
पूर्ण

अटल व्योम
sपंचांगmac_get_छोड़ोparam(काष्ठा net_device *netdev,
		      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(netdev);
	काष्ठा rgmii_adv adv_lp;

	अगर (priv->hw->pcs && !sपंचांगmac_pcs_get_adv_lp(priv, priv->ioaddr, &adv_lp)) अणु
		छोड़ो->स्वतःneg = 1;
		अगर (!adv_lp.छोड़ो)
			वापस;
	पूर्ण अन्यथा अणु
		phylink_ethtool_get_छोड़ोparam(priv->phylink, छोड़ो);
	पूर्ण
पूर्ण

अटल पूर्णांक
sपंचांगmac_set_छोड़ोparam(काष्ठा net_device *netdev,
		      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(netdev);
	काष्ठा rgmii_adv adv_lp;

	अगर (priv->hw->pcs && !sपंचांगmac_pcs_get_adv_lp(priv, priv->ioaddr, &adv_lp)) अणु
		छोड़ो->स्वतःneg = 1;
		अगर (!adv_lp.छोड़ो)
			वापस -EOPNOTSUPP;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस phylink_ethtool_set_छोड़ोparam(priv->phylink, छोड़ो);
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_get_ethtool_stats(काष्ठा net_device *dev,
				 काष्ठा ethtool_stats *dummy, u64 *data)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 rx_queues_count = priv->plat->rx_queues_to_use;
	u32 tx_queues_count = priv->plat->tx_queues_to_use;
	अचिन्हित दीर्घ count;
	पूर्णांक i, j = 0, ret;

	अगर (priv->dma_cap.asp) अणु
		क्रम (i = 0; i < STMMAC_SAFETY_FEAT_SIZE; i++) अणु
			अगर (!sपंचांगmac_safety_feat_dump(priv, &priv->sstats, i,
						&count, शून्य))
				data[j++] = count;
		पूर्ण
	पूर्ण

	/* Update the DMA HW counters क्रम dwmac10/100 */
	ret = sपंचांगmac_dma_diagnostic_fr(priv, &dev->stats, (व्योम *) &priv->xstats,
			priv->ioaddr);
	अगर (ret) अणु
		/* If supported, क्रम new GMAC chips expose the MMC counters */
		अगर (priv->dma_cap.rmon) अणु
			sपंचांगmac_mmc_पढ़ो(priv, priv->mmcaddr, &priv->mmc);

			क्रम (i = 0; i < STMMAC_MMC_STATS_LEN; i++) अणु
				अक्षर *p;
				p = (अक्षर *)priv + sपंचांगmac_mmc[i].stat_offset;

				data[j++] = (sपंचांगmac_mmc[i].माप_stat ==
					     माप(u64)) ? (*(u64 *)p) :
					     (*(u32 *)p);
			पूर्ण
		पूर्ण
		अगर (priv->eee_enabled) अणु
			पूर्णांक val = phylink_get_eee_err(priv->phylink);
			अगर (val)
				priv->xstats.phy_eee_wakeup_error_n = val;
		पूर्ण

		अगर (priv->synopsys_id >= DWMAC_CORE_3_50)
			sपंचांगmac_mac_debug(priv, priv->ioaddr,
					(व्योम *)&priv->xstats,
					rx_queues_count, tx_queues_count);
	पूर्ण
	क्रम (i = 0; i < STMMAC_STATS_LEN; i++) अणु
		अक्षर *p = (अक्षर *)priv + sपंचांगmac_gstrings_stats[i].stat_offset;
		data[j++] = (sपंचांगmac_gstrings_stats[i].माप_stat ==
			     माप(u64)) ? (*(u64 *)p) : (*(u32 *)p);
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांगmac_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(netdev);
	पूर्णांक i, len, safety_len = 0;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		len = STMMAC_STATS_LEN;

		अगर (priv->dma_cap.rmon)
			len += STMMAC_MMC_STATS_LEN;
		अगर (priv->dma_cap.asp) अणु
			क्रम (i = 0; i < STMMAC_SAFETY_FEAT_SIZE; i++) अणु
				अगर (!sपंचांगmac_safety_feat_dump(priv,
							&priv->sstats, i,
							शून्य, शून्य))
					safety_len++;
			पूर्ण

			len += safety_len;
		पूर्ण

		वापस len;
	हाल ETH_SS_TEST:
		वापस sपंचांगmac_selftest_get_count(priv);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम sपंचांगmac_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;
	u8 *p = data;
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		अगर (priv->dma_cap.asp) अणु
			क्रम (i = 0; i < STMMAC_SAFETY_FEAT_SIZE; i++) अणु
				स्थिर अक्षर *desc;
				अगर (!sपंचांगmac_safety_feat_dump(priv,
							&priv->sstats, i,
							शून्य, &desc)) अणु
					स_नकल(p, desc, ETH_GSTRING_LEN);
					p += ETH_GSTRING_LEN;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (priv->dma_cap.rmon)
			क्रम (i = 0; i < STMMAC_MMC_STATS_LEN; i++) अणु
				स_नकल(p, sपंचांगmac_mmc[i].stat_string,
				       ETH_GSTRING_LEN);
				p += ETH_GSTRING_LEN;
			पूर्ण
		क्रम (i = 0; i < STMMAC_STATS_LEN; i++) अणु
			स_नकल(p, sपंचांगmac_gstrings_stats[i].stat_string,
				ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	हाल ETH_SS_TEST:
		sपंचांगmac_selftest_get_strings(priv, p);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण

/* Currently only support WOL through Magic packet. */
अटल व्योम sपंचांगmac_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (!priv->plat->pmt)
		वापस phylink_ethtool_get_wol(priv->phylink, wol);

	mutex_lock(&priv->lock);
	अगर (device_can_wakeup(priv->device)) अणु
		wol->supported = WAKE_MAGIC | WAKE_UCAST;
		अगर (priv->hw_cap_support && !priv->dma_cap.pmt_magic_frame)
			wol->supported &= ~WAKE_MAGIC;
		wol->wolopts = priv->wolopts;
	पूर्ण
	mutex_unlock(&priv->lock);
पूर्ण

अटल पूर्णांक sपंचांगmac_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 support = WAKE_MAGIC | WAKE_UCAST;

	अगर (!device_can_wakeup(priv->device))
		वापस -EOPNOTSUPP;

	अगर (!priv->plat->pmt) अणु
		पूर्णांक ret = phylink_ethtool_set_wol(priv->phylink, wol);

		अगर (!ret)
			device_set_wakeup_enable(priv->device, !!wol->wolopts);
		वापस ret;
	पूर्ण

	/* By शेष almost all GMAC devices support the WoL via
	 * magic frame but we can disable it अगर the HW capability
	 * रेजिस्टर shows no support क्रम pmt_magic_frame. */
	अगर ((priv->hw_cap_support) && (!priv->dma_cap.pmt_magic_frame))
		wol->wolopts &= ~WAKE_MAGIC;

	अगर (wol->wolopts & ~support)
		वापस -EINVAL;

	अगर (wol->wolopts) अणु
		pr_info("stmmac: wakeup enable\n");
		device_set_wakeup_enable(priv->device, 1);
		enable_irq_wake(priv->wol_irq);
	पूर्ण अन्यथा अणु
		device_set_wakeup_enable(priv->device, 0);
		disable_irq_wake(priv->wol_irq);
	पूर्ण

	mutex_lock(&priv->lock);
	priv->wolopts = wol->wolopts;
	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_ethtool_op_get_eee(काष्ठा net_device *dev,
				     काष्ठा ethtool_eee *edata)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (!priv->dma_cap.eee)
		वापस -EOPNOTSUPP;

	edata->eee_enabled = priv->eee_enabled;
	edata->eee_active = priv->eee_active;
	edata->tx_lpi_समयr = priv->tx_lpi_समयr;
	edata->tx_lpi_enabled = priv->tx_lpi_enabled;

	वापस phylink_ethtool_get_eee(priv->phylink, edata);
पूर्ण

अटल पूर्णांक sपंचांगmac_ethtool_op_set_eee(काष्ठा net_device *dev,
				     काष्ठा ethtool_eee *edata)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret;

	अगर (!priv->dma_cap.eee)
		वापस -EOPNOTSUPP;

	अगर (priv->tx_lpi_enabled != edata->tx_lpi_enabled)
		netdev_warn(priv->dev,
			    "Setting EEE tx-lpi is not supported\n");

	अगर (!edata->eee_enabled)
		sपंचांगmac_disable_eee_mode(priv);

	ret = phylink_ethtool_set_eee(priv->phylink, edata);
	अगर (ret)
		वापस ret;

	अगर (edata->eee_enabled &&
	    priv->tx_lpi_समयr != edata->tx_lpi_समयr) अणु
		priv->tx_lpi_समयr = edata->tx_lpi_समयr;
		sपंचांगmac_eee_init(priv);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 sपंचांगmac_usec2riwt(u32 usec, काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित दीर्घ clk = clk_get_rate(priv->plat->sपंचांगmac_clk);

	अगर (!clk) अणु
		clk = priv->plat->clk_ref_rate;
		अगर (!clk)
			वापस 0;
	पूर्ण

	वापस (usec * (clk / 1000000)) / 256;
पूर्ण

अटल u32 sपंचांगmac_riwt2usec(u32 riwt, काष्ठा sपंचांगmac_priv *priv)
अणु
	अचिन्हित दीर्घ clk = clk_get_rate(priv->plat->sपंचांगmac_clk);

	अगर (!clk) अणु
		clk = priv->plat->clk_ref_rate;
		अगर (!clk)
			वापस 0;
	पूर्ण

	वापस (riwt * 256) / (clk / 1000000);
पूर्ण

अटल पूर्णांक __sपंचांगmac_get_coalesce(काष्ठा net_device *dev,
				 काष्ठा ethtool_coalesce *ec,
				 पूर्णांक queue)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	u32 max_cnt;
	u32 rx_cnt;
	u32 tx_cnt;

	rx_cnt = priv->plat->rx_queues_to_use;
	tx_cnt = priv->plat->tx_queues_to_use;
	max_cnt = max(rx_cnt, tx_cnt);

	अगर (queue < 0)
		queue = 0;
	अन्यथा अगर (queue >= max_cnt)
		वापस -EINVAL;

	अगर (queue < tx_cnt) अणु
		ec->tx_coalesce_usecs = priv->tx_coal_समयr[queue];
		ec->tx_max_coalesced_frames = priv->tx_coal_frames[queue];
	पूर्ण अन्यथा अणु
		ec->tx_coalesce_usecs = 0;
		ec->tx_max_coalesced_frames = 0;
	पूर्ण

	अगर (priv->use_riwt && queue < rx_cnt) अणु
		ec->rx_max_coalesced_frames = priv->rx_coal_frames[queue];
		ec->rx_coalesce_usecs = sपंचांगmac_riwt2usec(priv->rx_riwt[queue],
							 priv);
	पूर्ण अन्यथा अणु
		ec->rx_max_coalesced_frames = 0;
		ec->rx_coalesce_usecs = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_get_coalesce(काष्ठा net_device *dev,
			       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __sपंचांगmac_get_coalesce(dev, ec, -1);
पूर्ण

अटल पूर्णांक sपंचांगmac_get_per_queue_coalesce(काष्ठा net_device *dev, u32 queue,
					 काष्ठा ethtool_coalesce *ec)
अणु
	वापस __sपंचांगmac_get_coalesce(dev, ec, queue);
पूर्ण

अटल पूर्णांक __sपंचांगmac_set_coalesce(काष्ठा net_device *dev,
				 काष्ठा ethtool_coalesce *ec,
				 पूर्णांक queue)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	bool all_queues = false;
	अचिन्हित पूर्णांक rx_riwt;
	u32 max_cnt;
	u32 rx_cnt;
	u32 tx_cnt;

	rx_cnt = priv->plat->rx_queues_to_use;
	tx_cnt = priv->plat->tx_queues_to_use;
	max_cnt = max(rx_cnt, tx_cnt);

	अगर (queue < 0)
		all_queues = true;
	अन्यथा अगर (queue >= max_cnt)
		वापस -EINVAL;

	अगर (priv->use_riwt && (ec->rx_coalesce_usecs > 0)) अणु
		rx_riwt = sपंचांगmac_usec2riwt(ec->rx_coalesce_usecs, priv);

		अगर ((rx_riwt > MAX_DMA_RIWT) || (rx_riwt < MIN_DMA_RIWT))
			वापस -EINVAL;

		अगर (all_queues) अणु
			पूर्णांक i;

			क्रम (i = 0; i < rx_cnt; i++) अणु
				priv->rx_riwt[i] = rx_riwt;
				sपंचांगmac_rx_watchकरोg(priv, priv->ioaddr,
						   rx_riwt, i);
				priv->rx_coal_frames[i] =
					ec->rx_max_coalesced_frames;
			पूर्ण
		पूर्ण अन्यथा अगर (queue < rx_cnt) अणु
			priv->rx_riwt[queue] = rx_riwt;
			sपंचांगmac_rx_watchकरोg(priv, priv->ioaddr,
					   rx_riwt, queue);
			priv->rx_coal_frames[queue] =
				ec->rx_max_coalesced_frames;
		पूर्ण
	पूर्ण

	अगर ((ec->tx_coalesce_usecs == 0) &&
	    (ec->tx_max_coalesced_frames == 0))
		वापस -EINVAL;

	अगर ((ec->tx_coalesce_usecs > STMMAC_MAX_COAL_TX_TICK) ||
	    (ec->tx_max_coalesced_frames > STMMAC_TX_MAX_FRAMES))
		वापस -EINVAL;

	अगर (all_queues) अणु
		पूर्णांक i;

		क्रम (i = 0; i < tx_cnt; i++) अणु
			priv->tx_coal_frames[i] =
				ec->tx_max_coalesced_frames;
			priv->tx_coal_समयr[i] =
				ec->tx_coalesce_usecs;
		पूर्ण
	पूर्ण अन्यथा अगर (queue < tx_cnt) अणु
		priv->tx_coal_frames[queue] =
			ec->tx_max_coalesced_frames;
		priv->tx_coal_समयr[queue] =
			ec->tx_coalesce_usecs;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_set_coalesce(काष्ठा net_device *dev,
			       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __sपंचांगmac_set_coalesce(dev, ec, -1);
पूर्ण

अटल पूर्णांक sपंचांगmac_set_per_queue_coalesce(काष्ठा net_device *dev, u32 queue,
					 काष्ठा ethtool_coalesce *ec)
अणु
	वापस __sपंचांगmac_set_coalesce(dev, ec, queue);
पूर्ण

अटल पूर्णांक sपंचांगmac_get_rxnfc(काष्ठा net_device *dev,
			    काष्ठा ethtool_rxnfc *rxnfc, u32 *rule_locs)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	चयन (rxnfc->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		rxnfc->data = priv->plat->rx_queues_to_use;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 sपंचांगmac_get_rxfh_key_size(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	वापस माप(priv->rss.key);
पूर्ण

अटल u32 sपंचांगmac_get_rxfh_indir_size(काष्ठा net_device *dev)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	वापस ARRAY_SIZE(priv->rss.table);
पूर्ण

अटल पूर्णांक sपंचांगmac_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key,
			   u8 *hfunc)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	अगर (indir) अणु
		क्रम (i = 0; i < ARRAY_SIZE(priv->rss.table); i++)
			indir[i] = priv->rss.table[i];
	पूर्ण

	अगर (key)
		स_नकल(key, priv->rss.key, माप(priv->rss.key));
	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगmac_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
			   स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक i;

	अगर ((hfunc != ETH_RSS_HASH_NO_CHANGE) && (hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;

	अगर (indir) अणु
		क्रम (i = 0; i < ARRAY_SIZE(priv->rss.table); i++)
			priv->rss.table[i] = indir[i];
	पूर्ण

	अगर (key)
		स_नकल(priv->rss.key, key, माप(priv->rss.key));

	वापस sपंचांगmac_rss_configure(priv, priv->hw, &priv->rss,
				    priv->plat->rx_queues_to_use);
पूर्ण

अटल व्योम sपंचांगmac_get_channels(काष्ठा net_device *dev,
				काष्ठा ethtool_channels *chan)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	chan->rx_count = priv->plat->rx_queues_to_use;
	chan->tx_count = priv->plat->tx_queues_to_use;
	chan->max_rx = priv->dma_cap.number_rx_queues;
	chan->max_tx = priv->dma_cap.number_tx_queues;
पूर्ण

अटल पूर्णांक sपंचांगmac_set_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *chan)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर (chan->rx_count > priv->dma_cap.number_rx_queues ||
	    chan->tx_count > priv->dma_cap.number_tx_queues ||
	    !chan->rx_count || !chan->tx_count)
		वापस -EINVAL;

	वापस sपंचांगmac_reinit_queues(dev, chan->rx_count, chan->tx_count);
पूर्ण

अटल पूर्णांक sपंचांगmac_get_ts_info(काष्ठा net_device *dev,
			      काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);

	अगर ((priv->dma_cap.समय_stamp || priv->dma_cap.aसमय_stamp)) अणु

		info->so_बारtamping = SOF_TIMESTAMPING_TX_SOFTWARE |
					SOF_TIMESTAMPING_TX_HARDWARE |
					SOF_TIMESTAMPING_RX_SOFTWARE |
					SOF_TIMESTAMPING_RX_HARDWARE |
					SOF_TIMESTAMPING_SOFTWARE |
					SOF_TIMESTAMPING_RAW_HARDWARE;

		अगर (priv->ptp_घड़ी)
			info->phc_index = ptp_घड़ी_index(priv->ptp_घड़ी);

		info->tx_types = (1 << HWTSTAMP_TX_OFF) | (1 << HWTSTAMP_TX_ON);

		info->rx_filters = ((1 << HWTSTAMP_FILTER_NONE) |
				    (1 << HWTSTAMP_FILTER_PTP_V1_L4_EVENT) |
				    (1 << HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
				    (1 << HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
				    (1 << HWTSTAMP_FILTER_PTP_V2_L4_EVENT) |
				    (1 << HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
				    (1 << HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
				    (1 << HWTSTAMP_FILTER_PTP_V2_EVENT) |
				    (1 << HWTSTAMP_FILTER_PTP_V2_SYNC) |
				    (1 << HWTSTAMP_FILTER_PTP_V2_DELAY_REQ) |
				    (1 << HWTSTAMP_FILTER_ALL));
		वापस 0;
	पूर्ण अन्यथा
		वापस ethtool_op_get_ts_info(dev, info);
पूर्ण

अटल पूर्णांक sपंचांगmac_get_tunable(काष्ठा net_device *dev,
			      स्थिर काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		*(u32 *)data = priv->rx_copyअवरोध;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांगmac_set_tunable(काष्ठा net_device *dev,
			      स्थिर काष्ठा ethtool_tunable *tuna,
			      स्थिर व्योम *data)
अणु
	काष्ठा sपंचांगmac_priv *priv = netdev_priv(dev);
	पूर्णांक ret = 0;

	चयन (tuna->id) अणु
	हाल ETHTOOL_RX_COPYBREAK:
		priv->rx_copyअवरोध = *(u32 *)data;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops sपंचांगmac_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.begin = sपंचांगmac_check_अगर_running,
	.get_drvinfo = sपंचांगmac_ethtool_getdrvinfo,
	.get_msglevel = sपंचांगmac_ethtool_geपंचांगsglevel,
	.set_msglevel = sपंचांगmac_ethtool_seपंचांगsglevel,
	.get_regs = sपंचांगmac_ethtool_gregs,
	.get_regs_len = sपंचांगmac_ethtool_get_regs_len,
	.get_link = ethtool_op_get_link,
	.nway_reset = sपंचांगmac_nway_reset,
	.get_ringparam = sपंचांगmac_get_ringparam,
	.set_ringparam = sपंचांगmac_set_ringparam,
	.get_छोड़ोparam = sपंचांगmac_get_छोड़ोparam,
	.set_छोड़ोparam = sपंचांगmac_set_छोड़ोparam,
	.self_test = sपंचांगmac_selftest_run,
	.get_ethtool_stats = sपंचांगmac_get_ethtool_stats,
	.get_strings = sपंचांगmac_get_strings,
	.get_wol = sपंचांगmac_get_wol,
	.set_wol = sपंचांगmac_set_wol,
	.get_eee = sपंचांगmac_ethtool_op_get_eee,
	.set_eee = sपंचांगmac_ethtool_op_set_eee,
	.get_sset_count	= sपंचांगmac_get_sset_count,
	.get_rxnfc = sपंचांगmac_get_rxnfc,
	.get_rxfh_key_size = sपंचांगmac_get_rxfh_key_size,
	.get_rxfh_indir_size = sपंचांगmac_get_rxfh_indir_size,
	.get_rxfh = sपंचांगmac_get_rxfh,
	.set_rxfh = sपंचांगmac_set_rxfh,
	.get_ts_info = sपंचांगmac_get_ts_info,
	.get_coalesce = sपंचांगmac_get_coalesce,
	.set_coalesce = sपंचांगmac_set_coalesce,
	.get_per_queue_coalesce = sपंचांगmac_get_per_queue_coalesce,
	.set_per_queue_coalesce = sपंचांगmac_set_per_queue_coalesce,
	.get_channels = sपंचांगmac_get_channels,
	.set_channels = sपंचांगmac_set_channels,
	.get_tunable = sपंचांगmac_get_tunable,
	.set_tunable = sपंचांगmac_set_tunable,
	.get_link_ksettings = sपंचांगmac_ethtool_get_link_ksettings,
	.set_link_ksettings = sपंचांगmac_ethtool_set_link_ksettings,
पूर्ण;

व्योम sपंचांगmac_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &sपंचांगmac_ethtool_ops;
पूर्ण
