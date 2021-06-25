<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>

#समावेश "qlcnic.h"

काष्ठा qlcnic_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा QLC_SIZखातापूर्ण(m) माप_field(काष्ठा qlcnic_adapter, m)
#घोषणा QLC_OFF(m) दुरत्व(काष्ठा qlcnic_adapter, m)
अटल स्थिर u32 qlcnic_fw_dump_level[] = अणु
	0x3, 0x7, 0xf, 0x1f, 0x3f, 0x7f, 0xff
पूर्ण;

अटल स्थिर काष्ठा qlcnic_stats qlcnic_gstrings_stats[] = अणु
	अणु"xmit_on", QLC_SIZखातापूर्ण(stats.xmit_on), QLC_OFF(stats.xmit_on)पूर्ण,
	अणु"xmit_off", QLC_SIZखातापूर्ण(stats.xmit_off), QLC_OFF(stats.xmit_off)पूर्ण,
	अणु"xmit_called", QLC_SIZखातापूर्ण(stats.xmitcalled),
	 QLC_OFF(stats.xmitcalled)पूर्ण,
	अणु"xmit_finished", QLC_SIZखातापूर्ण(stats.xmitfinished),
	 QLC_OFF(stats.xmitfinished)पूर्ण,
	अणु"tx dma map error", QLC_SIZखातापूर्ण(stats.tx_dma_map_error),
	 QLC_OFF(stats.tx_dma_map_error)पूर्ण,
	अणु"tx_bytes", QLC_SIZखातापूर्ण(stats.txbytes), QLC_OFF(stats.txbytes)पूर्ण,
	अणु"tx_dropped", QLC_SIZखातापूर्ण(stats.txdropped), QLC_OFF(stats.txdropped)पूर्ण,
	अणु"rx dma map error", QLC_SIZखातापूर्ण(stats.rx_dma_map_error),
	 QLC_OFF(stats.rx_dma_map_error)पूर्ण,
	अणु"rx_pkts", QLC_SIZखातापूर्ण(stats.rx_pkts), QLC_OFF(stats.rx_pkts)पूर्ण,
	अणु"rx_bytes", QLC_SIZखातापूर्ण(stats.rxbytes), QLC_OFF(stats.rxbytes)पूर्ण,
	अणु"rx_dropped", QLC_SIZखातापूर्ण(stats.rxdropped), QLC_OFF(stats.rxdropped)पूर्ण,
	अणु"null rxbuf", QLC_SIZखातापूर्ण(stats.null_rxbuf), QLC_OFF(stats.null_rxbuf)पूर्ण,
	अणु"csummed", QLC_SIZखातापूर्ण(stats.csummed), QLC_OFF(stats.csummed)पूर्ण,
	अणु"lro_pkts", QLC_SIZखातापूर्ण(stats.lro_pkts), QLC_OFF(stats.lro_pkts)पूर्ण,
	अणु"lrobytes", QLC_SIZखातापूर्ण(stats.lrobytes), QLC_OFF(stats.lrobytes)पूर्ण,
	अणु"lso_frames", QLC_SIZखातापूर्ण(stats.lso_frames), QLC_OFF(stats.lso_frames)पूर्ण,
	अणु"encap_lso_frames", QLC_SIZखातापूर्ण(stats.encap_lso_frames),
	 QLC_OFF(stats.encap_lso_frames)पूर्ण,
	अणु"encap_tx_csummed", QLC_SIZखातापूर्ण(stats.encap_tx_csummed),
	 QLC_OFF(stats.encap_tx_csummed)पूर्ण,
	अणु"encap_rx_csummed", QLC_SIZखातापूर्ण(stats.encap_rx_csummed),
	 QLC_OFF(stats.encap_rx_csummed)पूर्ण,
	अणु"skb_alloc_failure", QLC_SIZखातापूर्ण(stats.skb_alloc_failure),
	 QLC_OFF(stats.skb_alloc_failure)पूर्ण,
	अणु"mac_filter_limit_overrun", QLC_SIZखातापूर्ण(stats.mac_filter_limit_overrun),
	 QLC_OFF(stats.mac_filter_limit_overrun)पूर्ण,
	अणु"spurious intr", QLC_SIZखातापूर्ण(stats.spurious_पूर्णांकr),
	 QLC_OFF(stats.spurious_पूर्णांकr)पूर्ण,
	अणु"mbx spurious intr", QLC_SIZखातापूर्ण(stats.mbx_spurious_पूर्णांकr),
	 QLC_OFF(stats.mbx_spurious_पूर्णांकr)पूर्ण,
पूर्ण;

अटल स्थिर अक्षर qlcnic_device_gstrings_stats[][ETH_GSTRING_LEN] = अणु
	"tx unicast frames",
	"tx multicast frames",
	"tx broadcast frames",
	"tx dropped frames",
	"tx errors",
	"tx local frames",
	"tx numbytes",
	"rx unicast frames",
	"rx multicast frames",
	"rx broadcast frames",
	"rx dropped frames",
	"rx errors",
	"rx local frames",
	"rx numbytes",
पूर्ण;

अटल स्थिर अक्षर qlcnic_83xx_tx_stats_strings[][ETH_GSTRING_LEN] = अणु
	"ctx_tx_bytes",
	"ctx_tx_pkts",
	"ctx_tx_errors",
	"ctx_tx_dropped_pkts",
	"ctx_tx_num_buffers",
पूर्ण;

अटल स्थिर अक्षर qlcnic_83xx_mac_stats_strings[][ETH_GSTRING_LEN] = अणु
	"mac_tx_frames",
	"mac_tx_bytes",
	"mac_tx_mcast_pkts",
	"mac_tx_bcast_pkts",
	"mac_tx_pause_cnt",
	"mac_tx_ctrl_pkt",
	"mac_tx_lt_64b_pkts",
	"mac_tx_lt_127b_pkts",
	"mac_tx_lt_255b_pkts",
	"mac_tx_lt_511b_pkts",
	"mac_tx_lt_1023b_pkts",
	"mac_tx_lt_1518b_pkts",
	"mac_tx_gt_1518b_pkts",
	"mac_rx_frames",
	"mac_rx_bytes",
	"mac_rx_mcast_pkts",
	"mac_rx_bcast_pkts",
	"mac_rx_pause_cnt",
	"mac_rx_ctrl_pkt",
	"mac_rx_lt_64b_pkts",
	"mac_rx_lt_127b_pkts",
	"mac_rx_lt_255b_pkts",
	"mac_rx_lt_511b_pkts",
	"mac_rx_lt_1023b_pkts",
	"mac_rx_lt_1518b_pkts",
	"mac_rx_gt_1518b_pkts",
	"mac_rx_length_error",
	"mac_rx_length_small",
	"mac_rx_length_large",
	"mac_rx_jabber",
	"mac_rx_dropped",
	"mac_crc_error",
	"mac_align_error",
	"eswitch_frames",
	"eswitch_bytes",
	"eswitch_multicast_frames",
	"eswitch_broadcast_frames",
	"eswitch_unicast_frames",
	"eswitch_error_free_frames",
	"eswitch_error_free_bytes",
पूर्ण;

#घोषणा QLCNIC_STATS_LEN	ARRAY_SIZE(qlcnic_gstrings_stats)

अटल स्थिर अक्षर qlcnic_tx_queue_stats_strings[][ETH_GSTRING_LEN] = अणु
	"xmit_on",
	"xmit_off",
	"xmit_called",
	"xmit_finished",
	"tx_bytes",
पूर्ण;

#घोषणा QLCNIC_TX_STATS_LEN	ARRAY_SIZE(qlcnic_tx_queue_stats_strings)

अटल स्थिर अक्षर qlcnic_83xx_rx_stats_strings[][ETH_GSTRING_LEN] = अणु
	"ctx_rx_bytes",
	"ctx_rx_pkts",
	"ctx_lro_pkt_cnt",
	"ctx_ip_csum_error",
	"ctx_rx_pkts_wo_ctx",
	"ctx_rx_pkts_drop_wo_sds_on_card",
	"ctx_rx_pkts_drop_wo_sds_on_host",
	"ctx_rx_osized_pkts",
	"ctx_rx_pkts_dropped_wo_rds",
	"ctx_rx_unexpected_mcast_pkts",
	"ctx_invalid_mac_address",
	"ctx_rx_rds_ring_prim_attempted",
	"ctx_rx_rds_ring_prim_success",
	"ctx_num_lro_flows_added",
	"ctx_num_lro_flows_removed",
	"ctx_num_lro_flows_active",
	"ctx_pkts_dropped_unknown",
पूर्ण;

अटल स्थिर अक्षर qlcnic_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register_Test_on_offline",
	"Link_Test_on_offline",
	"Interrupt_Test_offline",
	"Internal_Loopback_offline",
	"External_Loopback_offline",
	"EEPROM_Test_offline"
पूर्ण;

#घोषणा QLCNIC_TEST_LEN	ARRAY_SIZE(qlcnic_gstrings_test)

अटल अंतरभूत पूर्णांक qlcnic_82xx_statistics(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस ARRAY_SIZE(qlcnic_gstrings_stats) +
	       ARRAY_SIZE(qlcnic_83xx_mac_stats_strings) +
	       QLCNIC_TX_STATS_LEN * adapter->drv_tx_rings;
पूर्ण

अटल अंतरभूत पूर्णांक qlcnic_83xx_statistics(काष्ठा qlcnic_adapter *adapter)
अणु
	वापस ARRAY_SIZE(qlcnic_gstrings_stats) +
	       ARRAY_SIZE(qlcnic_83xx_tx_stats_strings) +
	       ARRAY_SIZE(qlcnic_83xx_mac_stats_strings) +
	       ARRAY_SIZE(qlcnic_83xx_rx_stats_strings) +
	       QLCNIC_TX_STATS_LEN * adapter->drv_tx_rings;
पूर्ण

अटल पूर्णांक qlcnic_dev_statistics_len(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक len = -1;

	अगर (qlcnic_82xx_check(adapter)) अणु
		len = qlcnic_82xx_statistics(adapter);
		अगर (adapter->flags & QLCNIC_ESWITCH_ENABLED)
			len += ARRAY_SIZE(qlcnic_device_gstrings_stats);
	पूर्ण अन्यथा अगर (qlcnic_83xx_check(adapter)) अणु
		len = qlcnic_83xx_statistics(adapter);
	पूर्ण

	वापस len;
पूर्ण

#घोषणा	QLCNIC_TX_INTR_NOT_CONFIGURED	0X78563412

#घोषणा QLCNIC_MAX_EEPROM_LEN   1024

अटल स्थिर u32 diag_रेजिस्टरs[] = अणु
	QLCNIC_CMDPEG_STATE,
	QLCNIC_RCVPEG_STATE,
	QLCNIC_FW_CAPABILITIES,
	QLCNIC_CRB_DRV_ACTIVE,
	QLCNIC_CRB_DEV_STATE,
	QLCNIC_CRB_DRV_STATE,
	QLCNIC_CRB_DRV_SCRATCH,
	QLCNIC_CRB_DEV_PARTITION_INFO,
	QLCNIC_CRB_DRV_IDC_VER,
	QLCNIC_PEG_ALIVE_COUNTER,
	QLCNIC_PEG_HALT_STATUS1,
	QLCNIC_PEG_HALT_STATUS2,
	-1
पूर्ण;


अटल स्थिर u32 ext_diag_रेजिस्टरs[] = अणु
	CRB_XG_STATE_P3P,
	ISR_INT_STATE_REG,
	QLCNIC_CRB_PEG_NET_0+0x3c,
	QLCNIC_CRB_PEG_NET_1+0x3c,
	QLCNIC_CRB_PEG_NET_2+0x3c,
	QLCNIC_CRB_PEG_NET_4+0x3c,
	-1
पूर्ण;

#घोषणा QLCNIC_MGMT_API_VERSION	3
#घोषणा QLCNIC_ETHTOOL_REGS_VER	4

अटल अंतरभूत पूर्णांक qlcnic_get_ring_regs_len(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक ring_regs_cnt = (adapter->drv_tx_rings * 5) +
			    (adapter->max_rds_rings * 2) +
			    (adapter->drv_sds_rings * 3) + 5;
	वापस ring_regs_cnt * माप(u32);
पूर्ण

अटल पूर्णांक qlcnic_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	u32 len;

	अगर (qlcnic_83xx_check(adapter))
		len = qlcnic_83xx_get_regs_len(adapter);
	अन्यथा
		len = माप(ext_diag_रेजिस्टरs) + माप(diag_रेजिस्टरs);

	len += ((QLCNIC_DEV_INFO_SIZE + 2) * माप(u32));
	len += qlcnic_get_ring_regs_len(adapter);
	वापस len;
पूर्ण

अटल पूर्णांक qlcnic_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस QLCNIC_FLASH_TOTAL_SIZE;
पूर्ण

अटल व्योम
qlcnic_get_drvinfo(काष्ठा net_device *dev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	u32 fw_major, fw_minor, fw_build;
	fw_major = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MAJOR);
	fw_minor = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MINOR);
	fw_build = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_SUB);
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		"%d.%d.%d", fw_major, fw_minor, fw_build);

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
	strlcpy(drvinfo->driver, qlcnic_driver_name, माप(drvinfo->driver));
	strlcpy(drvinfo->version, QLCNIC_LINUX_VERSIONID,
		माप(drvinfo->version));
पूर्ण

अटल पूर्णांक qlcnic_82xx_get_link_ksettings(काष्ठा qlcnic_adapter *adapter,
					  काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	u32 speed, reg;
	पूर्णांक check_sfp_module = 0, err = 0;
	u16 pcअगरn = ahw->pci_func;
	u32 supported, advertising;

	/* पढ़ो which mode */
	अगर (adapter->ahw->port_type == QLCNIC_GBE) अणु
		supported = (SUPPORTED_10baseT_Half |
				   SUPPORTED_10baseT_Full |
				   SUPPORTED_100baseT_Half |
				   SUPPORTED_100baseT_Full |
				   SUPPORTED_1000baseT_Half |
				   SUPPORTED_1000baseT_Full);

		advertising = (ADVERTISED_100baseT_Half |
				     ADVERTISED_100baseT_Full |
				     ADVERTISED_1000baseT_Half |
				     ADVERTISED_1000baseT_Full);

		ecmd->base.speed = adapter->ahw->link_speed;
		ecmd->base.duplex = adapter->ahw->link_duplex;
		ecmd->base.स्वतःneg = adapter->ahw->link_स्वतःneg;

	पूर्ण अन्यथा अगर (adapter->ahw->port_type == QLCNIC_XGBE) अणु
		u32 val = 0;
		val = QLCRD32(adapter, QLCNIC_PORT_MODE_ADDR, &err);

		अगर (val == QLCNIC_PORT_MODE_802_3_AP) अणु
			supported = SUPPORTED_1000baseT_Full;
			advertising = ADVERTISED_1000baseT_Full;
		पूर्ण अन्यथा अणु
			supported = SUPPORTED_10000baseT_Full;
			advertising = ADVERTISED_10000baseT_Full;
		पूर्ण

		अगर (netअगर_running(adapter->netdev) && ahw->has_link_events) अणु
			अगर (ahw->linkup) अणु
				reg = QLCRD32(adapter,
					      P3P_LINK_SPEED_REG(pcअगरn), &err);
				speed = P3P_LINK_SPEED_VAL(pcअगरn, reg);
				ahw->link_speed = speed * P3P_LINK_SPEED_MHZ;
			पूर्ण

			ecmd->base.speed = ahw->link_speed;
			ecmd->base.स्वतःneg = ahw->link_स्वतःneg;
			ecmd->base.duplex = ahw->link_duplex;
			जाओ skip;
		पूर्ण

		ecmd->base.speed = SPEED_UNKNOWN;
		ecmd->base.duplex = DUPLEX_UNKNOWN;
		ecmd->base.स्वतःneg = AUTONEG_DISABLE;
	पूर्ण अन्यथा
		वापस -EIO;

skip:
	ecmd->base.phy_address = adapter->ahw->physical_port;

	चयन (adapter->ahw->board_type) अणु
	हाल QLCNIC_BRDTYPE_P3P_REF_QG:
	हाल QLCNIC_BRDTYPE_P3P_4_GB:
	हाल QLCNIC_BRDTYPE_P3P_4_GB_MM:
		supported |= SUPPORTED_Autoneg;
		advertising |= ADVERTISED_Autoneg;
		fallthrough;
	हाल QLCNIC_BRDTYPE_P3P_10G_CX4:
	हाल QLCNIC_BRDTYPE_P3P_10G_CX4_LP:
	हाल QLCNIC_BRDTYPE_P3P_10000_BASE_T:
		supported |= SUPPORTED_TP;
		advertising |= ADVERTISED_TP;
		ecmd->base.port = PORT_TP;
		ecmd->base.स्वतःneg =  adapter->ahw->link_स्वतःneg;
		अवरोध;
	हाल QLCNIC_BRDTYPE_P3P_IMEZ:
	हाल QLCNIC_BRDTYPE_P3P_XG_LOM:
	हाल QLCNIC_BRDTYPE_P3P_HMEZ:
		supported |= SUPPORTED_MII;
		advertising |= ADVERTISED_MII;
		ecmd->base.port = PORT_MII;
		ecmd->base.स्वतःneg = AUTONEG_DISABLE;
		अवरोध;
	हाल QLCNIC_BRDTYPE_P3P_10G_SFP_PLUS:
	हाल QLCNIC_BRDTYPE_P3P_10G_SFP_CT:
	हाल QLCNIC_BRDTYPE_P3P_10G_SFP_QT:
		advertising |= ADVERTISED_TP;
		supported |= SUPPORTED_TP;
		check_sfp_module = netअगर_running(adapter->netdev) &&
				   ahw->has_link_events;
		fallthrough;
	हाल QLCNIC_BRDTYPE_P3P_10G_XFP:
		supported |= SUPPORTED_FIBRE;
		advertising |= ADVERTISED_FIBRE;
		ecmd->base.port = PORT_FIBRE;
		ecmd->base.स्वतःneg = AUTONEG_DISABLE;
		अवरोध;
	हाल QLCNIC_BRDTYPE_P3P_10G_TP:
		अगर (adapter->ahw->port_type == QLCNIC_XGBE) अणु
			ecmd->base.स्वतःneg = AUTONEG_DISABLE;
			supported |= (SUPPORTED_FIBRE | SUPPORTED_TP);
			advertising |=
				(ADVERTISED_FIBRE | ADVERTISED_TP);
			ecmd->base.port = PORT_FIBRE;
			check_sfp_module = netअगर_running(adapter->netdev) &&
					   ahw->has_link_events;
		पूर्ण अन्यथा अणु
			ecmd->base.स्वतःneg = AUTONEG_ENABLE;
			supported |= (SUPPORTED_TP | SUPPORTED_Autoneg);
			advertising |=
				(ADVERTISED_TP | ADVERTISED_Autoneg);
			ecmd->base.port = PORT_TP;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(&adapter->pdev->dev, "Unsupported board model %d\n",
			adapter->ahw->board_type);
		वापस -EIO;
	पूर्ण

	अगर (check_sfp_module) अणु
		चयन (adapter->ahw->module_type) अणु
		हाल LINKEVENT_MODULE_OPTICAL_UNKNOWN:
		हाल LINKEVENT_MODULE_OPTICAL_SRLR:
		हाल LINKEVENT_MODULE_OPTICAL_LRM:
		हाल LINKEVENT_MODULE_OPTICAL_SFP_1G:
			ecmd->base.port = PORT_FIBRE;
			अवरोध;
		हाल LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLE:
		हाल LINKEVENT_MODULE_TWINAX_UNSUPPORTED_CABLELEN:
		हाल LINKEVENT_MODULE_TWINAX:
			ecmd->base.port = PORT_TP;
			अवरोध;
		शेष:
			ecmd->base.port = PORT_OTHER;
		पूर्ण
	पूर्ण

	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(ecmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *ecmd)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);

	अगर (qlcnic_82xx_check(adapter))
		वापस qlcnic_82xx_get_link_ksettings(adapter, ecmd);
	अन्यथा अगर (qlcnic_83xx_check(adapter))
		वापस qlcnic_83xx_get_link_ksettings(adapter, ecmd);

	वापस -EIO;
पूर्ण


अटल पूर्णांक qlcnic_set_port_config(काष्ठा qlcnic_adapter *adapter,
				  स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	u32 ret = 0, config = 0;
	/* पढ़ो which mode */
	अगर (ecmd->base.duplex)
		config |= 0x1;

	अगर (ecmd->base.स्वतःneg)
		config |= 0x2;

	चयन (ecmd->base.speed) अणु
	हाल SPEED_10:
		config |= (0 << 8);
		अवरोध;
	हाल SPEED_100:
		config |= (1 << 8);
		अवरोध;
	हाल SPEED_1000:
		config |= (10 << 8);
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	ret = qlcnic_fw_cmd_set_port(adapter, config);

	अगर (ret == QLCNIC_RCODE_NOT_SUPPORTED)
		वापस -EOPNOTSUPP;
	अन्यथा अगर (ret)
		वापस -EIO;
	वापस ret;
पूर्ण

अटल पूर्णांक qlcnic_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *ecmd)
अणु
	u32 ret = 0;
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);

	अगर (qlcnic_83xx_check(adapter))
		qlcnic_83xx_get_port_type(adapter);

	अगर (adapter->ahw->port_type != QLCNIC_GBE)
		वापस -EOPNOTSUPP;

	अगर (qlcnic_83xx_check(adapter))
		ret = qlcnic_83xx_set_link_ksettings(adapter, ecmd);
	अन्यथा
		ret = qlcnic_set_port_config(adapter, ecmd);

	अगर (!ret)
		वापस ret;

	adapter->ahw->link_speed = ecmd->base.speed;
	adapter->ahw->link_duplex = ecmd->base.duplex;
	adapter->ahw->link_स्वतःneg = ecmd->base.स्वतःneg;

	अगर (!netअगर_running(dev))
		वापस 0;

	dev->netdev_ops->nकरो_stop(dev);
	वापस dev->netdev_ops->nकरो_खोलो(dev);
पूर्ण

अटल पूर्णांक qlcnic_82xx_get_रेजिस्टरs(काष्ठा qlcnic_adapter *adapter,
				     u32 *regs_buff)
अणु
	पूर्णांक i, j = 0, err = 0;

	क्रम (i = QLCNIC_DEV_INFO_SIZE + 1; diag_रेजिस्टरs[j] != -1; j++, i++)
		regs_buff[i] = QLC_SHARED_REG_RD32(adapter, diag_रेजिस्टरs[j]);
	j = 0;
	जबतक (ext_diag_रेजिस्टरs[j] != -1)
		regs_buff[i++] = QLCRD32(adapter, ext_diag_रेजिस्टरs[j++],
					 &err);
	वापस i;
पूर्ण

अटल व्योम
qlcnic_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_host_rds_ring *rds_rings;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	u32 *regs_buff = p;
	पूर्णांक ring, i = 0;

	स_रखो(p, 0, qlcnic_get_regs_len(dev));

	regs->version = (QLCNIC_ETHTOOL_REGS_VER << 24) |
		(adapter->ahw->revision_id << 16) | (adapter->pdev)->device;

	regs_buff[0] = (0xcafe0000 | (QLCNIC_DEV_INFO_SIZE & 0xffff));
	regs_buff[1] = QLCNIC_MGMT_API_VERSION;

	अगर (adapter->ahw->capabilities & QLC_83XX_ESWITCH_CAPABILITY)
		regs_buff[2] = adapter->ahw->max_vnic_func;

	अगर (qlcnic_82xx_check(adapter))
		i = qlcnic_82xx_get_रेजिस्टरs(adapter, regs_buff);
	अन्यथा
		i = qlcnic_83xx_get_रेजिस्टरs(adapter, regs_buff);

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		वापस;

	/* Marker btw regs and TX ring count */
	regs_buff[i++] = 0xFFEFCDAB;

	regs_buff[i++] = adapter->drv_tx_rings; /* No. of TX ring */
	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
		tx_ring = &adapter->tx_ring[ring];
		regs_buff[i++] = le32_to_cpu(*(tx_ring->hw_consumer));
		regs_buff[i++] = tx_ring->sw_consumer;
		regs_buff[i++] = पढ़ोl(tx_ring->crb_cmd_producer);
		regs_buff[i++] = tx_ring->producer;
		अगर (tx_ring->crb_पूर्णांकr_mask)
			regs_buff[i++] = पढ़ोl(tx_ring->crb_पूर्णांकr_mask);
		अन्यथा
			regs_buff[i++] = QLCNIC_TX_INTR_NOT_CONFIGURED;
	पूर्ण

	regs_buff[i++] = adapter->max_rds_rings; /* No. of RX ring */
	क्रम (ring = 0; ring < adapter->max_rds_rings; ring++) अणु
		rds_rings = &recv_ctx->rds_rings[ring];
		regs_buff[i++] = पढ़ोl(rds_rings->crb_rcv_producer);
		regs_buff[i++] = rds_rings->producer;
	पूर्ण

	regs_buff[i++] = adapter->drv_sds_rings; /* No. of SDS ring */
	क्रम (ring = 0; ring < adapter->drv_sds_rings; ring++) अणु
		sds_ring = &(recv_ctx->sds_rings[ring]);
		regs_buff[i++] = पढ़ोl(sds_ring->crb_sts_consumer);
		regs_buff[i++] = sds_ring->consumer;
		regs_buff[i++] = पढ़ोl(sds_ring->crb_पूर्णांकr_mask);
	पूर्ण
पूर्ण

अटल u32 qlcnic_test_link(काष्ठा net_device *dev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	पूर्णांक err = 0;
	u32 val;

	अगर (qlcnic_83xx_check(adapter)) अणु
		val = qlcnic_83xx_test_link(adapter);
		वापस (val & 1) ? 0 : 1;
	पूर्ण
	val = QLCRD32(adapter, CRB_XG_STATE_P3P, &err);
	अगर (err == -EIO)
		वापस err;
	val = XG_LINK_STATE_P3P(adapter->ahw->pci_func, val);
	वापस (val == XG_LINK_UP_P3P) ? 0 : 1;
पूर्ण

अटल पूर्णांक
qlcnic_get_eeprom(काष्ठा net_device *dev, काष्ठा ethtool_eeprom *eeprom,
		      u8 *bytes)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	पूर्णांक offset;
	पूर्णांक ret = -1;

	अगर (qlcnic_83xx_check(adapter))
		वापस 0;
	अगर (eeprom->len == 0)
		वापस -EINVAL;

	eeprom->magic = (adapter->pdev)->venकरोr |
			((adapter->pdev)->device << 16);
	offset = eeprom->offset;

	अगर (qlcnic_82xx_check(adapter))
		ret = qlcnic_rom_fast_पढ़ो_words(adapter, offset, bytes,
						 eeprom->len);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम
qlcnic_get_ringparam(काष्ठा net_device *dev,
		काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);

	ring->rx_pending = adapter->num_rxd;
	ring->rx_jumbo_pending = adapter->num_jumbo_rxd;
	ring->tx_pending = adapter->num_txd;

	ring->rx_max_pending = adapter->max_rxd;
	ring->rx_jumbo_max_pending = adapter->max_jumbo_rxd;
	ring->tx_max_pending = MAX_CMD_DESCRIPTORS;
पूर्ण

अटल u32
qlcnic_validate_ringparam(u32 val, u32 min, u32 max, अक्षर *r_name)
अणु
	u32 num_desc;
	num_desc = max(val, min);
	num_desc = min(num_desc, max);
	num_desc = roundup_घात_of_two(num_desc);

	अगर (val != num_desc) अणु
		prपूर्णांकk(KERN_INFO "%s: setting %s ring size %d instead of %d\n",
		       qlcnic_driver_name, r_name, num_desc, val);
	पूर्ण

	वापस num_desc;
पूर्ण

अटल पूर्णांक
qlcnic_set_ringparam(काष्ठा net_device *dev,
		काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	u16 num_rxd, num_jumbo_rxd, num_txd;

	अगर (ring->rx_mini_pending)
		वापस -EOPNOTSUPP;

	num_rxd = qlcnic_validate_ringparam(ring->rx_pending,
			MIN_RCV_DESCRIPTORS, adapter->max_rxd, "rx");

	num_jumbo_rxd = qlcnic_validate_ringparam(ring->rx_jumbo_pending,
			MIN_JUMBO_DESCRIPTORS, adapter->max_jumbo_rxd,
						"rx jumbo");

	num_txd = qlcnic_validate_ringparam(ring->tx_pending,
			MIN_CMD_DESCRIPTORS, MAX_CMD_DESCRIPTORS, "tx");

	अगर (num_rxd == adapter->num_rxd && num_txd == adapter->num_txd &&
			num_jumbo_rxd == adapter->num_jumbo_rxd)
		वापस 0;

	adapter->num_rxd = num_rxd;
	adapter->num_jumbo_rxd = num_jumbo_rxd;
	adapter->num_txd = num_txd;

	वापस qlcnic_reset_context(adapter);
पूर्ण

अटल पूर्णांक qlcnic_validate_ring_count(काष्ठा qlcnic_adapter *adapter,
				      u8 rx_ring, u8 tx_ring)
अणु
	अगर (rx_ring == 0 || tx_ring == 0)
		वापस -EINVAL;

	अगर (rx_ring != 0) अणु
		अगर (rx_ring > adapter->max_sds_rings) अणु
			netdev_err(adapter->netdev,
				   "Invalid ring count, SDS ring count %d should not be greater than max %d driver sds rings.\n",
				   rx_ring, adapter->max_sds_rings);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	 अगर (tx_ring != 0) अणु
		अगर (tx_ring > adapter->max_tx_rings) अणु
			netdev_err(adapter->netdev,
				   "Invalid ring count, Tx ring count %d should not be greater than max %d driver Tx rings.\n",
				   tx_ring, adapter->max_tx_rings);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qlcnic_get_channels(काष्ठा net_device *dev,
		काष्ठा ethtool_channels *channel)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);

	channel->max_rx = adapter->max_sds_rings;
	channel->max_tx = adapter->max_tx_rings;
	channel->rx_count = adapter->drv_sds_rings;
	channel->tx_count = adapter->drv_tx_rings;
पूर्ण

अटल पूर्णांक qlcnic_set_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *channel)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	पूर्णांक err;

	अगर (!(adapter->flags & QLCNIC_MSIX_ENABLED)) अणु
		netdev_err(dev, "No RSS/TSS support in non MSI-X mode\n");
		वापस -EINVAL;
	पूर्ण

	अगर (channel->other_count || channel->combined_count)
		वापस -EINVAL;

	err = qlcnic_validate_ring_count(adapter, channel->rx_count,
					 channel->tx_count);
	अगर (err)
		वापस err;

	अगर (adapter->drv_sds_rings != channel->rx_count) अणु
		err = qlcnic_validate_rings(adapter, channel->rx_count,
					    QLCNIC_RX_QUEUE);
		अगर (err) अणु
			netdev_err(dev, "Unable to configure %u SDS rings\n",
				   channel->rx_count);
			वापस err;
		पूर्ण
		adapter->drv_rss_rings = channel->rx_count;
	पूर्ण

	अगर (adapter->drv_tx_rings != channel->tx_count) अणु
		err = qlcnic_validate_rings(adapter, channel->tx_count,
					    QLCNIC_TX_QUEUE);
		अगर (err) अणु
			netdev_err(dev, "Unable to configure %u Tx rings\n",
				   channel->tx_count);
			वापस err;
		पूर्ण
		adapter->drv_tss_rings = channel->tx_count;
	पूर्ण

	adapter->flags |= QLCNIC_TSS_RSS;

	err = qlcnic_setup_rings(adapter);
	netdev_info(dev, "Allocated %d SDS rings and %d Tx rings\n",
		    adapter->drv_sds_rings, adapter->drv_tx_rings);

	वापस err;
पूर्ण

अटल व्योम
qlcnic_get_छोड़ोparam(काष्ठा net_device *netdev,
			  काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक port = adapter->ahw->physical_port;
	पूर्णांक err = 0;
	__u32 val;

	अगर (qlcnic_83xx_check(adapter)) अणु
		qlcnic_83xx_get_छोड़ोparam(adapter, छोड़ो);
		वापस;
	पूर्ण
	अगर (adapter->ahw->port_type == QLCNIC_GBE) अणु
		अगर ((port < 0) || (port > QLCNIC_NIU_MAX_GBE_PORTS))
			वापस;
		/* get flow control settings */
		val = QLCRD32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port), &err);
		अगर (err == -EIO)
			वापस;
		छोड़ो->rx_छोड़ो = qlcnic_gb_get_rx_flowctl(val);
		val = QLCRD32(adapter, QLCNIC_NIU_GB_PAUSE_CTL, &err);
		अगर (err == -EIO)
			वापस;
		चयन (port) अणु
		हाल 0:
			छोड़ो->tx_छोड़ो = !(qlcnic_gb_get_gb0_mask(val));
			अवरोध;
		हाल 1:
			छोड़ो->tx_छोड़ो = !(qlcnic_gb_get_gb1_mask(val));
			अवरोध;
		हाल 2:
			छोड़ो->tx_छोड़ो = !(qlcnic_gb_get_gb2_mask(val));
			अवरोध;
		हाल 3:
		शेष:
			छोड़ो->tx_छोड़ो = !(qlcnic_gb_get_gb3_mask(val));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (adapter->ahw->port_type == QLCNIC_XGBE) अणु
		अगर ((port < 0) || (port > QLCNIC_NIU_MAX_XG_PORTS))
			वापस;
		छोड़ो->rx_छोड़ो = 1;
		val = QLCRD32(adapter, QLCNIC_NIU_XG_PAUSE_CTL, &err);
		अगर (err == -EIO)
			वापस;
		अगर (port == 0)
			छोड़ो->tx_छोड़ो = !(qlcnic_xg_get_xg0_mask(val));
		अन्यथा
			छोड़ो->tx_छोड़ो = !(qlcnic_xg_get_xg1_mask(val));
	पूर्ण अन्यथा अणु
		dev_err(&netdev->dev, "Unknown board type: %x\n",
					adapter->ahw->port_type);
	पूर्ण
पूर्ण

अटल पूर्णांक
qlcnic_set_छोड़ोparam(काष्ठा net_device *netdev,
			  काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक port = adapter->ahw->physical_port;
	पूर्णांक err = 0;
	__u32 val;

	अगर (qlcnic_83xx_check(adapter))
		वापस qlcnic_83xx_set_छोड़ोparam(adapter, छोड़ो);

	/* पढ़ो mode */
	अगर (adapter->ahw->port_type == QLCNIC_GBE) अणु
		अगर ((port < 0) || (port > QLCNIC_NIU_MAX_GBE_PORTS))
			वापस -EIO;
		/* set flow control */
		val = QLCRD32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port), &err);
		अगर (err == -EIO)
			वापस err;

		अगर (छोड़ो->rx_छोड़ो)
			qlcnic_gb_rx_flowctl(val);
		अन्यथा
			qlcnic_gb_unset_rx_flowctl(val);

		QLCWR32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port),
				val);
		QLCWR32(adapter, QLCNIC_NIU_GB_MAC_CONFIG_0(port), val);
		/* set स्वतःneg */
		val = QLCRD32(adapter, QLCNIC_NIU_GB_PAUSE_CTL, &err);
		अगर (err == -EIO)
			वापस err;
		चयन (port) अणु
		हाल 0:
			अगर (छोड़ो->tx_छोड़ो)
				qlcnic_gb_unset_gb0_mask(val);
			अन्यथा
				qlcnic_gb_set_gb0_mask(val);
			अवरोध;
		हाल 1:
			अगर (छोड़ो->tx_छोड़ो)
				qlcnic_gb_unset_gb1_mask(val);
			अन्यथा
				qlcnic_gb_set_gb1_mask(val);
			अवरोध;
		हाल 2:
			अगर (छोड़ो->tx_छोड़ो)
				qlcnic_gb_unset_gb2_mask(val);
			अन्यथा
				qlcnic_gb_set_gb2_mask(val);
			अवरोध;
		हाल 3:
		शेष:
			अगर (छोड़ो->tx_छोड़ो)
				qlcnic_gb_unset_gb3_mask(val);
			अन्यथा
				qlcnic_gb_set_gb3_mask(val);
			अवरोध;
		पूर्ण
		QLCWR32(adapter, QLCNIC_NIU_GB_PAUSE_CTL, val);
	पूर्ण अन्यथा अगर (adapter->ahw->port_type == QLCNIC_XGBE) अणु
		अगर (!छोड़ो->rx_छोड़ो || छोड़ो->स्वतःneg)
			वापस -EOPNOTSUPP;

		अगर ((port < 0) || (port > QLCNIC_NIU_MAX_XG_PORTS))
			वापस -EIO;

		val = QLCRD32(adapter, QLCNIC_NIU_XG_PAUSE_CTL, &err);
		अगर (err == -EIO)
			वापस err;
		अगर (port == 0) अणु
			अगर (छोड़ो->tx_छोड़ो)
				qlcnic_xg_unset_xg0_mask(val);
			अन्यथा
				qlcnic_xg_set_xg0_mask(val);
		पूर्ण अन्यथा अणु
			अगर (छोड़ो->tx_छोड़ो)
				qlcnic_xg_unset_xg1_mask(val);
			अन्यथा
				qlcnic_xg_set_xg1_mask(val);
		पूर्ण
		QLCWR32(adapter, QLCNIC_NIU_XG_PAUSE_CTL, val);
	पूर्ण अन्यथा अणु
		dev_err(&netdev->dev, "Unknown board type: %x\n",
				adapter->ahw->port_type);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_reg_test(काष्ठा net_device *dev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	u32 data_पढ़ो;
	पूर्णांक err = 0;

	अगर (qlcnic_83xx_check(adapter))
		वापस qlcnic_83xx_reg_test(adapter);

	data_पढ़ो = QLCRD32(adapter, QLCNIC_PCIX_PH_REG(0), &err);
	अगर (err == -EIO)
		वापस err;
	अगर ((data_पढ़ो & 0xffff) != adapter->pdev->venकरोr)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_eeprom_test(काष्ठा net_device *dev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);

	अगर (qlcnic_82xx_check(adapter))
		वापस 0;

	वापस qlcnic_83xx_flash_test(adapter);
पूर्ण

अटल पूर्णांक qlcnic_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु

	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस QLCNIC_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस qlcnic_dev_statistics_len(adapter);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक qlcnic_irq_test(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_cmd_args cmd;
	पूर्णांक ret, drv_sds_rings = adapter->drv_sds_rings;
	पूर्णांक drv_tx_rings = adapter->drv_tx_rings;

	अगर (qlcnic_83xx_check(adapter))
		वापस qlcnic_83xx_पूर्णांकerrupt_test(netdev);

	अगर (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EIO;

	ret = qlcnic_diag_alloc_res(netdev, QLCNIC_INTERRUPT_TEST);
	अगर (ret)
		जाओ clear_diag_irq;

	ahw->diag_cnt = 0;
	ret = qlcnic_alloc_mbx_args(&cmd, adapter, QLCNIC_CMD_INTRPT_TEST);
	अगर (ret)
		जाओ मुक्त_diag_res;

	cmd.req.arg[1] = ahw->pci_func;
	ret = qlcnic_issue_cmd(adapter, &cmd);
	अगर (ret)
		जाओ करोne;

	usleep_range(1000, 12000);
	ret = !ahw->diag_cnt;

करोne:
	qlcnic_मुक्त_mbx_args(&cmd);

मुक्त_diag_res:
	qlcnic_diag_मुक्त_res(netdev, drv_sds_rings);

clear_diag_irq:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	clear_bit(__QLCNIC_RESETTING, &adapter->state);

	वापस ret;
पूर्ण

#घोषणा QLCNIC_ILB_PKT_SIZE		64
#घोषणा QLCNIC_NUM_ILB_PKT		16
#घोषणा QLCNIC_ILB_MAX_RCV_LOOP		10
#घोषणा QLCNIC_LB_PKT_POLL_DELAY_MSEC	1
#घोषणा QLCNIC_LB_PKT_POLL_COUNT	20

अटल व्योम qlcnic_create_loopback_buff(अचिन्हित अक्षर *data, u8 mac[])
अणु
	अचिन्हित अक्षर अक्रमom_data[] = अणु0xa8, 0x06, 0x45, 0x00पूर्ण;

	स_रखो(data, 0x4e, QLCNIC_ILB_PKT_SIZE);

	स_नकल(data, mac, ETH_ALEN);
	स_नकल(data + ETH_ALEN, mac, ETH_ALEN);

	स_नकल(data + 2 * ETH_ALEN, अक्रमom_data, माप(अक्रमom_data));
पूर्ण

पूर्णांक qlcnic_check_loopback_buff(अचिन्हित अक्षर *data, u8 mac[])
अणु
	अचिन्हित अक्षर buff[QLCNIC_ILB_PKT_SIZE];
	qlcnic_create_loopback_buff(buff, mac);
	वापस स_भेद(data, buff, QLCNIC_ILB_PKT_SIZE);
पूर्ण

पूर्णांक qlcnic_करो_lb_test(काष्ठा qlcnic_adapter *adapter, u8 mode)
अणु
	काष्ठा qlcnic_recv_context *recv_ctx = adapter->recv_ctx;
	काष्ठा qlcnic_host_sds_ring *sds_ring = &recv_ctx->sds_rings[0];
	काष्ठा sk_buff *skb;
	पूर्णांक i, loop, cnt = 0;

	क्रम (i = 0; i < QLCNIC_NUM_ILB_PKT; i++) अणु
		skb = netdev_alloc_skb(adapter->netdev, QLCNIC_ILB_PKT_SIZE);
		अगर (!skb)
			जाओ error;
		qlcnic_create_loopback_buff(skb->data, adapter->mac_addr);
		skb_put(skb, QLCNIC_ILB_PKT_SIZE);
		adapter->ahw->diag_cnt = 0;
		qlcnic_xmit_frame(skb, adapter->netdev);
		loop = 0;

		करो अणु
			msleep(QLCNIC_LB_PKT_POLL_DELAY_MSEC);
			qlcnic_process_rcv_ring_diag(sds_ring);
			अगर (loop++ > QLCNIC_LB_PKT_POLL_COUNT)
				अवरोध;
		पूर्ण जबतक (!adapter->ahw->diag_cnt);

		dev_kमुक्त_skb_any(skb);

		अगर (!adapter->ahw->diag_cnt)
			dev_warn(&adapter->pdev->dev,
				 "LB Test: packet #%d was not received\n",
				 i + 1);
		अन्यथा
			cnt++;
	पूर्ण
	अगर (cnt != i) अणु
error:
		dev_err(&adapter->pdev->dev,
			"LB Test: failed, TX[%d], RX[%d]\n", i, cnt);
		अगर (mode != QLCNIC_ILB_MODE)
			dev_warn(&adapter->pdev->dev,
				 "WARNING: Please check loopback cable\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_loopback_test(काष्ठा net_device *netdev, u8 mode)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक drv_tx_rings = adapter->drv_tx_rings;
	पूर्णांक drv_sds_rings = adapter->drv_sds_rings;
	काष्ठा qlcnic_host_sds_ring *sds_ring;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक loop = 0;
	पूर्णांक ret;

	अगर (qlcnic_83xx_check(adapter))
		वापस qlcnic_83xx_loopback_test(netdev, mode);

	अगर (!(ahw->capabilities & QLCNIC_FW_CAPABILITY_MULTI_LOOPBACK)) अणु
		dev_info(&adapter->pdev->dev,
			 "Firmware do not support loopback test\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	dev_warn(&adapter->pdev->dev, "%s loopback test in progress\n",
		 mode == QLCNIC_ILB_MODE ? "internal" : "external");
	अगर (ahw->op_mode == QLCNIC_NON_PRIV_FUNC) अणु
		dev_warn(&adapter->pdev->dev,
			 "Loopback test not supported in nonprivileged mode\n");
		वापस 0;
	पूर्ण

	अगर (test_and_set_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EBUSY;

	ret = qlcnic_diag_alloc_res(netdev, QLCNIC_LOOPBACK_TEST);
	अगर (ret)
		जाओ clear_it;

	sds_ring = &adapter->recv_ctx->sds_rings[0];
	ret = qlcnic_set_lb_mode(adapter, mode);
	अगर (ret)
		जाओ मुक्त_res;

	ahw->diag_cnt = 0;
	करो अणु
		msleep(500);
		qlcnic_process_rcv_ring_diag(sds_ring);
		अगर (loop++ > QLCNIC_ILB_MAX_RCV_LOOP) अणु
			netdev_info(netdev,
				    "Firmware didn't sent link up event to loopback request\n");
			ret = -ETIMEDOUT;
			जाओ मुक्त_res;
		पूर्ण अन्यथा अगर (adapter->ahw->diag_cnt) अणु
			ret = adapter->ahw->diag_cnt;
			जाओ मुक्त_res;
		पूर्ण
	पूर्ण जबतक (!QLCNIC_IS_LB_CONFIGURED(ahw->loopback_state));

	ret = qlcnic_करो_lb_test(adapter, mode);

	qlcnic_clear_lb_mode(adapter, mode);

 मुक्त_res:
	qlcnic_diag_मुक्त_res(netdev, drv_sds_rings);

 clear_it:
	adapter->drv_sds_rings = drv_sds_rings;
	adapter->drv_tx_rings = drv_tx_rings;
	clear_bit(__QLCNIC_RESETTING, &adapter->state);
	वापस ret;
पूर्ण

अटल व्योम
qlcnic_diag_test(काष्ठा net_device *dev, काष्ठा ethtool_test *eth_test,
		     u64 *data)
अणु
	स_रखो(data, 0, माप(u64) * QLCNIC_TEST_LEN);

	data[0] = qlcnic_reg_test(dev);
	अगर (data[0])
		eth_test->flags |= ETH_TEST_FL_FAILED;

	data[1] = (u64) qlcnic_test_link(dev);
	अगर (data[1])
		eth_test->flags |= ETH_TEST_FL_FAILED;

	अगर (eth_test->flags & ETH_TEST_FL_OFFLINE) अणु
		data[2] = qlcnic_irq_test(dev);
		अगर (data[2])
			eth_test->flags |= ETH_TEST_FL_FAILED;

		data[3] = qlcnic_loopback_test(dev, QLCNIC_ILB_MODE);
		अगर (data[3])
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (eth_test->flags & ETH_TEST_FL_EXTERNAL_LB) अणु
			data[4] = qlcnic_loopback_test(dev, QLCNIC_ELB_MODE);
			अगर (data[4])
				eth_test->flags |= ETH_TEST_FL_FAILED;
			eth_test->flags |= ETH_TEST_FL_EXTERNAL_LB_DONE;
		पूर्ण

		data[5] = qlcnic_eeprom_test(dev);
		अगर (data[5])
			eth_test->flags |= ETH_TEST_FL_FAILED;
	पूर्ण
पूर्ण

अटल व्योम
qlcnic_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	पूर्णांक index, i, num_stats;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *qlcnic_gstrings_test,
		       QLCNIC_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		num_stats = ARRAY_SIZE(qlcnic_tx_queue_stats_strings);
		क्रम (i = 0; i < adapter->drv_tx_rings; i++) अणु
			क्रम (index = 0; index < num_stats; index++) अणु
				प्र_लिखो(data, "tx_queue_%d %s", i,
					qlcnic_tx_queue_stats_strings[index]);
				data += ETH_GSTRING_LEN;
			पूर्ण
		पूर्ण

		क्रम (index = 0; index < QLCNIC_STATS_LEN; index++) अणु
			स_नकल(data + index * ETH_GSTRING_LEN,
			       qlcnic_gstrings_stats[index].stat_string,
			       ETH_GSTRING_LEN);
		पूर्ण

		अगर (qlcnic_83xx_check(adapter)) अणु
			num_stats = ARRAY_SIZE(qlcnic_83xx_tx_stats_strings);
			क्रम (i = 0; i < num_stats; i++, index++)
				स_नकल(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_tx_stats_strings[i],
				       ETH_GSTRING_LEN);
			num_stats = ARRAY_SIZE(qlcnic_83xx_mac_stats_strings);
			क्रम (i = 0; i < num_stats; i++, index++)
				स_नकल(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_mac_stats_strings[i],
				       ETH_GSTRING_LEN);
			num_stats = ARRAY_SIZE(qlcnic_83xx_rx_stats_strings);
			क्रम (i = 0; i < num_stats; i++, index++)
				स_नकल(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_rx_stats_strings[i],
				       ETH_GSTRING_LEN);
			वापस;
		पूर्ण अन्यथा अणु
			num_stats = ARRAY_SIZE(qlcnic_83xx_mac_stats_strings);
			क्रम (i = 0; i < num_stats; i++, index++)
				स_नकल(data + index * ETH_GSTRING_LEN,
				       qlcnic_83xx_mac_stats_strings[i],
				       ETH_GSTRING_LEN);
		पूर्ण
		अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
			वापस;
		num_stats = ARRAY_SIZE(qlcnic_device_gstrings_stats);
		क्रम (i = 0; i < num_stats; index++, i++) अणु
			स_नकल(data + index * ETH_GSTRING_LEN,
			       qlcnic_device_gstrings_stats[i],
			       ETH_GSTRING_LEN);
		पूर्ण
	पूर्ण
पूर्ण

अटल u64 *qlcnic_fill_stats(u64 *data, व्योम *stats, पूर्णांक type)
अणु
	अगर (type == QLCNIC_MAC_STATS) अणु
		काष्ठा qlcnic_mac_statistics *mac_stats =
					(काष्ठा qlcnic_mac_statistics *)stats;
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_frames);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_bytes);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_mcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_bcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_छोड़ो_cnt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_ctrl_pkt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_64b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_127b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_255b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_511b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_1023b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_lt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_tx_gt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_frames);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_bytes);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_mcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_bcast_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_छोड़ो_cnt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_ctrl_pkt);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_64b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_127b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_255b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_511b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_1023b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_lt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_gt_1518b_pkts);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_length_error);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_length_small);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_length_large);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_jabber);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_dropped);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_rx_crc_error);
		*data++ = QLCNIC_FILL_STATS(mac_stats->mac_align_error);
	पूर्ण अन्यथा अगर (type == QLCNIC_ESW_STATS) अणु
		काष्ठा __qlcnic_esw_statistics *esw_stats =
				(काष्ठा __qlcnic_esw_statistics *)stats;
		*data++ = QLCNIC_FILL_STATS(esw_stats->unicast_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->multicast_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->broadcast_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->dropped_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->errors);
		*data++ = QLCNIC_FILL_STATS(esw_stats->local_frames);
		*data++ = QLCNIC_FILL_STATS(esw_stats->numbytes);
	पूर्ण
	वापस data;
पूर्ण

व्योम qlcnic_update_stats(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_tx_queue_stats tx_stats;
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	पूर्णांक ring;

	स_रखो(&tx_stats, 0, माप(tx_stats));
	क्रम (ring = 0; ring < adapter->drv_tx_rings; ring++) अणु
		tx_ring = &adapter->tx_ring[ring];
		tx_stats.xmit_on += tx_ring->tx_stats.xmit_on;
		tx_stats.xmit_off += tx_ring->tx_stats.xmit_off;
		tx_stats.xmit_called += tx_ring->tx_stats.xmit_called;
		tx_stats.xmit_finished += tx_ring->tx_stats.xmit_finished;
		tx_stats.tx_bytes += tx_ring->tx_stats.tx_bytes;
	पूर्ण

	adapter->stats.xmit_on = tx_stats.xmit_on;
	adapter->stats.xmit_off = tx_stats.xmit_off;
	adapter->stats.xmitcalled = tx_stats.xmit_called;
	adapter->stats.xmitfinished = tx_stats.xmit_finished;
	adapter->stats.txbytes = tx_stats.tx_bytes;
पूर्ण

अटल u64 *qlcnic_fill_tx_queue_stats(u64 *data, व्योम *stats)
अणु
	काष्ठा qlcnic_host_tx_ring *tx_ring;

	tx_ring = (काष्ठा qlcnic_host_tx_ring *)stats;

	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_on);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_off);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_called);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.xmit_finished);
	*data++ = QLCNIC_FILL_STATS(tx_ring->tx_stats.tx_bytes);

	वापस data;
पूर्ण

अटल व्योम qlcnic_get_ethtool_stats(काष्ठा net_device *dev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	काष्ठा qlcnic_host_tx_ring *tx_ring;
	काष्ठा qlcnic_esw_statistics port_stats;
	काष्ठा qlcnic_mac_statistics mac_stats;
	पूर्णांक index, ret, length, size, ring;
	अक्षर *p;

	स_रखो(data, 0, stats->n_stats * माप(u64));

	क्रम (ring = 0, index = 0; ring < adapter->drv_tx_rings; ring++) अणु
		अगर (adapter->is_up == QLCNIC_ADAPTER_UP_MAGIC) अणु
			tx_ring = &adapter->tx_ring[ring];
			data = qlcnic_fill_tx_queue_stats(data, tx_ring);
			qlcnic_update_stats(adapter);
		पूर्ण अन्यथा अणु
			data += QLCNIC_TX_STATS_LEN;
		पूर्ण
	पूर्ण

	length = QLCNIC_STATS_LEN;
	क्रम (index = 0; index < length; index++) अणु
		p = (अक्षर *)adapter + qlcnic_gstrings_stats[index].stat_offset;
		size = qlcnic_gstrings_stats[index].माप_stat;
		*data++ = (size == माप(u64)) ? (*(u64 *)p) : ((*(u32 *)p));
	पूर्ण

	अगर (qlcnic_83xx_check(adapter)) अणु
		अगर (adapter->ahw->linkup)
			qlcnic_83xx_get_stats(adapter, data);
		वापस;
	पूर्ण अन्यथा अणु
		/* Retrieve MAC statistics from firmware */
		स_रखो(&mac_stats, 0, माप(काष्ठा qlcnic_mac_statistics));
		qlcnic_get_mac_stats(adapter, &mac_stats);
		data = qlcnic_fill_stats(data, &mac_stats, QLCNIC_MAC_STATS);
	पूर्ण

	अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
		वापस;

	स_रखो(&port_stats, 0, माप(काष्ठा qlcnic_esw_statistics));
	ret = qlcnic_get_port_stats(adapter, adapter->ahw->pci_func,
			QLCNIC_QUERY_RX_COUNTER, &port_stats.rx);
	अगर (ret)
		वापस;

	data = qlcnic_fill_stats(data, &port_stats.rx, QLCNIC_ESW_STATS);
	ret = qlcnic_get_port_stats(adapter, adapter->ahw->pci_func,
			QLCNIC_QUERY_TX_COUNTER, &port_stats.tx);
	अगर (ret)
		वापस;

	qlcnic_fill_stats(data, &port_stats.tx, QLCNIC_ESW_STATS);
पूर्ण

अटल पूर्णांक qlcnic_set_led(काष्ठा net_device *dev,
			  क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	पूर्णांक drv_sds_rings = adapter->drv_sds_rings;
	पूर्णांक err = -EIO, active = 1;

	अगर (qlcnic_83xx_check(adapter))
		वापस qlcnic_83xx_set_led(dev, state);

	अगर (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC) अणु
		netdev_warn(dev, "LED test not supported for non "
				"privilege function\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		अगर (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state))
			वापस -EBUSY;

		अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
			अवरोध;

		अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
			अगर (qlcnic_diag_alloc_res(dev, QLCNIC_LED_TEST))
				अवरोध;
			set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
		पूर्ण

		अगर (adapter->nic_ops->config_led(adapter, 1, 0xf) == 0) अणु
			err = 0;
			अवरोध;
		पूर्ण

		dev_err(&adapter->pdev->dev,
			"Failed to set LED blink state.\n");
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		active = 0;

		अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
			अवरोध;

		अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
			अगर (qlcnic_diag_alloc_res(dev, QLCNIC_LED_TEST))
				अवरोध;
			set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
		पूर्ण

		अगर (adapter->nic_ops->config_led(adapter, 0, 0xf))
			dev_err(&adapter->pdev->dev,
				"Failed to reset LED blink state.\n");

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (test_and_clear_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state))
		qlcnic_diag_मुक्त_res(dev, drv_sds_rings);

	अगर (!active || err)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);

	वापस err;
पूर्ण

अटल व्योम
qlcnic_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	u32 wol_cfg;
	पूर्णांक err = 0;

	अगर (qlcnic_83xx_check(adapter))
		वापस;
	wol->supported = 0;
	wol->wolopts = 0;

	wol_cfg = QLCRD32(adapter, QLCNIC_WOL_CONFIG_NV, &err);
	अगर (err == -EIO)
		वापस;
	अगर (wol_cfg & (1UL << adapter->portnum))
		wol->supported |= WAKE_MAGIC;

	wol_cfg = QLCRD32(adapter, QLCNIC_WOL_CONFIG, &err);
	अगर (wol_cfg & (1UL << adapter->portnum))
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक
qlcnic_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(dev);
	u32 wol_cfg;
	पूर्णांक err = 0;

	अगर (qlcnic_83xx_check(adapter))
		वापस -EOPNOTSUPP;
	अगर (wol->wolopts & ~WAKE_MAGIC)
		वापस -EINVAL;

	wol_cfg = QLCRD32(adapter, QLCNIC_WOL_CONFIG_NV, &err);
	अगर (err == -EIO)
		वापस err;
	अगर (!(wol_cfg & (1 << adapter->portnum)))
		वापस -EOPNOTSUPP;

	wol_cfg = QLCRD32(adapter, QLCNIC_WOL_CONFIG, &err);
	अगर (err == -EIO)
		वापस err;
	अगर (wol->wolopts & WAKE_MAGIC)
		wol_cfg |= 1UL << adapter->portnum;
	अन्यथा
		wol_cfg &= ~(1UL << adapter->portnum);

	QLCWR32(adapter, QLCNIC_WOL_CONFIG, wol_cfg);

	वापस 0;
पूर्ण

/*
 * Set the coalescing parameters. Currently only normal is supported.
 * If rx_coalesce_usecs == 0 or rx_max_coalesced_frames == 0 then set the
 * firmware coalescing to शेष.
 */
अटल पूर्णांक qlcnic_set_पूर्णांकr_coalesce(काष्ठा net_device *netdev,
			काष्ठा ethtool_coalesce *ethcoal)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err;

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		वापस -EINVAL;

	/*
	* Return Error अगर unsupported values or
	* unsupported parameters are set.
	*/
	अगर (ethcoal->rx_coalesce_usecs > 0xffff ||
	    ethcoal->rx_max_coalesced_frames > 0xffff ||
	    ethcoal->tx_coalesce_usecs > 0xffff ||
	    ethcoal->tx_max_coalesced_frames > 0xffff)
		वापस -EINVAL;

	err = qlcnic_config_पूर्णांकr_coalesce(adapter, ethcoal);

	वापस err;
पूर्ण

अटल पूर्णांक qlcnic_get_पूर्णांकr_coalesce(काष्ठा net_device *netdev,
			काष्ठा ethtool_coalesce *ethcoal)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->is_up != QLCNIC_ADAPTER_UP_MAGIC)
		वापस -EINVAL;

	ethcoal->rx_coalesce_usecs = adapter->ahw->coal.rx_समय_us;
	ethcoal->rx_max_coalesced_frames = adapter->ahw->coal.rx_packets;
	ethcoal->tx_coalesce_usecs = adapter->ahw->coal.tx_समय_us;
	ethcoal->tx_max_coalesced_frames = adapter->ahw->coal.tx_packets;

	वापस 0;
पूर्ण

अटल u32 qlcnic_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	वापस adapter->ahw->msg_enable;
पूर्ण

अटल व्योम qlcnic_set_msglevel(काष्ठा net_device *netdev, u32 msglvl)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);

	adapter->ahw->msg_enable = msglvl;
पूर्ण

पूर्णांक qlcnic_enable_fw_dump_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	u32 val;

	अगर (qlcnic_84xx_check(adapter)) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;

		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		val &= ~QLC_83XX_IDC_DISABLE_FW_DUMP;
		QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);

		qlcnic_83xx_unlock_driver(adapter);
	पूर्ण अन्यथा अणु
		fw_dump->enable = true;
	पूर्ण

	dev_info(&adapter->pdev->dev, "FW dump enabled\n");

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_disable_fw_dump_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	u32 val;

	अगर (qlcnic_84xx_check(adapter)) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;

		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		val |= QLC_83XX_IDC_DISABLE_FW_DUMP;
		QLCWRX(adapter->ahw, QLC_83XX_IDC_CTRL, val);

		qlcnic_83xx_unlock_driver(adapter);
	पूर्ण अन्यथा अणु
		fw_dump->enable = false;
	पूर्ण

	dev_info(&adapter->pdev->dev, "FW dump disabled\n");

	वापस 0;
पूर्ण

bool qlcnic_check_fw_dump_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	bool state;
	u32 val;

	अगर (qlcnic_84xx_check(adapter)) अणु
		val = QLCRDX(adapter->ahw, QLC_83XX_IDC_CTRL);
		state = (val & QLC_83XX_IDC_DISABLE_FW_DUMP) ? false : true;
	पूर्ण अन्यथा अणु
		state = fw_dump->enable;
	पूर्ण

	वापस state;
पूर्ण

अटल पूर्णांक
qlcnic_get_dump_flag(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;

	अगर (!fw_dump->पंचांगpl_hdr) अणु
		netdev_err(adapter->netdev, "FW Dump not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (fw_dump->clr)
		dump->len = fw_dump->पंचांगpl_hdr_size + fw_dump->size;
	अन्यथा
		dump->len = 0;

	अगर (!qlcnic_check_fw_dump_state(adapter))
		dump->flag = ETH_FW_DUMP_DISABLE;
	अन्यथा
		dump->flag = fw_dump->cap_mask;

	dump->version = adapter->fw_version;
	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_get_dump_data(काष्ठा net_device *netdev, काष्ठा ethtool_dump *dump,
			व्योम *buffer)
अणु
	पूर्णांक i, copy_sz;
	u32 *hdr_ptr;
	__le32 *data;
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;

	अगर (!fw_dump->पंचांगpl_hdr) अणु
		netdev_err(netdev, "FW Dump not supported\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!fw_dump->clr) अणु
		netdev_info(netdev, "Dump not available\n");
		वापस -EINVAL;
	पूर्ण

	/* Copy ढाँचा header first */
	copy_sz = fw_dump->पंचांगpl_hdr_size;
	hdr_ptr = (u32 *)fw_dump->पंचांगpl_hdr;
	data = buffer;
	क्रम (i = 0; i < copy_sz/माप(u32); i++)
		*data++ = cpu_to_le32(*hdr_ptr++);

	/* Copy captured dump data */
	स_नकल(buffer + copy_sz, fw_dump->data, fw_dump->size);
	dump->len = copy_sz + fw_dump->size;
	dump->flag = fw_dump->cap_mask;

	/* Free dump area once data has been captured */
	vमुक्त(fw_dump->data);
	fw_dump->data = शून्य;
	fw_dump->clr = 0;
	netdev_info(netdev, "extracted the FW dump Successfully\n");
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_set_dump_mask(काष्ठा qlcnic_adapter *adapter, u32 mask)
अणु
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (!qlcnic_check_fw_dump_state(adapter)) अणु
		netdev_info(netdev,
			    "Can not change driver mask to 0x%x. FW dump not enabled\n",
			    mask);
		वापस -EOPNOTSUPP;
	पूर्ण

	fw_dump->cap_mask = mask;

	/* Store new capture mask in ढाँचा header as well*/
	qlcnic_store_cap_mask(adapter, fw_dump->पंचांगpl_hdr, mask);

	netdev_info(netdev, "Driver mask changed to: 0x%x\n", mask);
	वापस 0;
पूर्ण

अटल पूर्णांक
qlcnic_set_dump(काष्ठा net_device *netdev, काष्ठा ethtool_dump *val)
अणु
	काष्ठा qlcnic_adapter *adapter = netdev_priv(netdev);
	काष्ठा qlcnic_fw_dump *fw_dump = &adapter->ahw->fw_dump;
	bool valid_mask = false;
	पूर्णांक i, ret = 0;

	चयन (val->flag) अणु
	हाल QLCNIC_FORCE_FW_DUMP_KEY:
		अगर (!fw_dump->पंचांगpl_hdr) अणु
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		अगर (!qlcnic_check_fw_dump_state(adapter)) अणु
			netdev_info(netdev, "FW dump not enabled\n");
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		अगर (fw_dump->clr) अणु
			netdev_info(netdev,
				    "Previous dump not cleared, not forcing dump\n");
			अवरोध;
		पूर्ण

		netdev_info(netdev, "Forcing a FW dump\n");
		qlcnic_dev_request_reset(adapter, val->flag);
		अवरोध;
	हाल QLCNIC_DISABLE_FW_DUMP:
		अगर (!fw_dump->पंचांगpl_hdr) अणु
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		ret = qlcnic_disable_fw_dump_state(adapter);
		अवरोध;

	हाल QLCNIC_ENABLE_FW_DUMP:
		अगर (!fw_dump->पंचांगpl_hdr) अणु
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		ret = qlcnic_enable_fw_dump_state(adapter);
		अवरोध;

	हाल QLCNIC_FORCE_FW_RESET:
		netdev_info(netdev, "Forcing a FW reset\n");
		qlcnic_dev_request_reset(adapter, val->flag);
		adapter->flags &= ~QLCNIC_FW_RESET_OWNER;
		अवरोध;

	हाल QLCNIC_SET_QUIESCENT:
	हाल QLCNIC_RESET_QUIESCENT:
		अगर (test_bit(__QLCNIC_MAINTEन_अंकCE_MODE, &adapter->state))
			netdev_info(netdev, "Device is in non-operational state\n");
		अवरोध;

	शेष:
		अगर (!fw_dump->पंचांगpl_hdr) अणु
			netdev_err(netdev, "FW dump not supported\n");
			ret = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		क्रम (i = 0; i < ARRAY_SIZE(qlcnic_fw_dump_level); i++) अणु
			अगर (val->flag == qlcnic_fw_dump_level[i]) अणु
				valid_mask = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (valid_mask) अणु
			ret = qlcnic_set_dump_mask(adapter, val->flag);
		पूर्ण अन्यथा अणु
			netdev_info(netdev, "Invalid dump level: 0x%x\n",
				    val->flag);
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

स्थिर काष्ठा ethtool_ops qlcnic_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo = qlcnic_get_drvinfo,
	.get_regs_len = qlcnic_get_regs_len,
	.get_regs = qlcnic_get_regs,
	.get_link = ethtool_op_get_link,
	.get_eeprom_len = qlcnic_get_eeprom_len,
	.get_eeprom = qlcnic_get_eeprom,
	.get_ringparam = qlcnic_get_ringparam,
	.set_ringparam = qlcnic_set_ringparam,
	.get_channels = qlcnic_get_channels,
	.set_channels = qlcnic_set_channels,
	.get_छोड़ोparam = qlcnic_get_छोड़ोparam,
	.set_छोड़ोparam = qlcnic_set_छोड़ोparam,
	.get_wol = qlcnic_get_wol,
	.set_wol = qlcnic_set_wol,
	.self_test = qlcnic_diag_test,
	.get_strings = qlcnic_get_strings,
	.get_ethtool_stats = qlcnic_get_ethtool_stats,
	.get_sset_count = qlcnic_get_sset_count,
	.get_coalesce = qlcnic_get_पूर्णांकr_coalesce,
	.set_coalesce = qlcnic_set_पूर्णांकr_coalesce,
	.set_phys_id = qlcnic_set_led,
	.set_msglevel = qlcnic_set_msglevel,
	.get_msglevel = qlcnic_get_msglevel,
	.get_dump_flag = qlcnic_get_dump_flag,
	.get_dump_data = qlcnic_get_dump_data,
	.set_dump = qlcnic_set_dump,
	.get_link_ksettings = qlcnic_get_link_ksettings,
	.set_link_ksettings = qlcnic_set_link_ksettings,
पूर्ण;

स्थिर काष्ठा ethtool_ops qlcnic_sriov_vf_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_drvinfo		= qlcnic_get_drvinfo,
	.get_regs_len		= qlcnic_get_regs_len,
	.get_regs		= qlcnic_get_regs,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= qlcnic_get_eeprom_len,
	.get_eeprom		= qlcnic_get_eeprom,
	.get_ringparam		= qlcnic_get_ringparam,
	.set_ringparam		= qlcnic_set_ringparam,
	.get_channels		= qlcnic_get_channels,
	.get_छोड़ोparam		= qlcnic_get_छोड़ोparam,
	.get_wol		= qlcnic_get_wol,
	.get_strings		= qlcnic_get_strings,
	.get_ethtool_stats	= qlcnic_get_ethtool_stats,
	.get_sset_count		= qlcnic_get_sset_count,
	.get_coalesce		= qlcnic_get_पूर्णांकr_coalesce,
	.set_coalesce		= qlcnic_set_पूर्णांकr_coalesce,
	.set_msglevel		= qlcnic_set_msglevel,
	.get_msglevel		= qlcnic_get_msglevel,
	.get_link_ksettings	= qlcnic_get_link_ksettings,
पूर्ण;

स्थिर काष्ठा ethtool_ops qlcnic_ethtool_failed_ops = अणु
	.get_drvinfo		= qlcnic_get_drvinfo,
	.set_msglevel		= qlcnic_set_msglevel,
	.get_msglevel		= qlcnic_get_msglevel,
	.set_dump		= qlcnic_set_dump,
	.get_link_ksettings	= qlcnic_get_link_ksettings,
पूर्ण;
