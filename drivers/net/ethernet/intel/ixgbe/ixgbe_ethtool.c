<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* ethtool support क्रम ixgbe */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/uaccess.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_phy.h"


#घोषणा IXGBE_ALL_RAR_ENTRIES 16

क्रमागत अणुNETDEV_STATS, IXGBE_STATSपूर्ण;

काष्ठा ixgbe_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक type;
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा IXGBE_STAT(m)		IXGBE_STATS, \
				माप(((काष्ठा ixgbe_adapter *)0)->m), \
				दुरत्व(काष्ठा ixgbe_adapter, m)
#घोषणा IXGBE_NETDEV_STAT(m)	NETDEV_STATS, \
				माप(((काष्ठा rtnl_link_stats64 *)0)->m), \
				दुरत्व(काष्ठा rtnl_link_stats64, m)

अटल स्थिर काष्ठा ixgbe_stats ixgbe_gstrings_stats[] = अणु
	अणु"rx_packets", IXGBE_NETDEV_STAT(rx_packets)पूर्ण,
	अणु"tx_packets", IXGBE_NETDEV_STAT(tx_packets)पूर्ण,
	अणु"rx_bytes", IXGBE_NETDEV_STAT(rx_bytes)पूर्ण,
	अणु"tx_bytes", IXGBE_NETDEV_STAT(tx_bytes)पूर्ण,
	अणु"rx_pkts_nic", IXGBE_STAT(stats.gprc)पूर्ण,
	अणु"tx_pkts_nic", IXGBE_STAT(stats.gptc)पूर्ण,
	अणु"rx_bytes_nic", IXGBE_STAT(stats.gorc)पूर्ण,
	अणु"tx_bytes_nic", IXGBE_STAT(stats.gotc)पूर्ण,
	अणु"lsc_int", IXGBE_STAT(lsc_पूर्णांक)पूर्ण,
	अणु"tx_busy", IXGBE_STAT(tx_busy)पूर्ण,
	अणु"non_eop_descs", IXGBE_STAT(non_eop_descs)पूर्ण,
	अणु"rx_errors", IXGBE_NETDEV_STAT(rx_errors)पूर्ण,
	अणु"tx_errors", IXGBE_NETDEV_STAT(tx_errors)पूर्ण,
	अणु"rx_dropped", IXGBE_NETDEV_STAT(rx_dropped)पूर्ण,
	अणु"tx_dropped", IXGBE_NETDEV_STAT(tx_dropped)पूर्ण,
	अणु"multicast", IXGBE_NETDEV_STAT(multicast)पूर्ण,
	अणु"broadcast", IXGBE_STAT(stats.bprc)पूर्ण,
	अणु"rx_no_buffer_count", IXGBE_STAT(stats.rnbc[0]) पूर्ण,
	अणु"collisions", IXGBE_NETDEV_STAT(collisions)पूर्ण,
	अणु"rx_over_errors", IXGBE_NETDEV_STAT(rx_over_errors)पूर्ण,
	अणु"rx_crc_errors", IXGBE_NETDEV_STAT(rx_crc_errors)पूर्ण,
	अणु"rx_frame_errors", IXGBE_NETDEV_STAT(rx_frame_errors)पूर्ण,
	अणु"hw_rsc_aggregated", IXGBE_STAT(rsc_total_count)पूर्ण,
	अणु"hw_rsc_flushed", IXGBE_STAT(rsc_total_flush)पूर्ण,
	अणु"fdir_match", IXGBE_STAT(stats.fdirmatch)पूर्ण,
	अणु"fdir_miss", IXGBE_STAT(stats.fdirmiss)पूर्ण,
	अणु"fdir_overflow", IXGBE_STAT(fdir_overflow)पूर्ण,
	अणु"rx_fifo_errors", IXGBE_NETDEV_STAT(rx_fअगरo_errors)पूर्ण,
	अणु"rx_missed_errors", IXGBE_NETDEV_STAT(rx_missed_errors)पूर्ण,
	अणु"tx_aborted_errors", IXGBE_NETDEV_STAT(tx_पातed_errors)पूर्ण,
	अणु"tx_carrier_errors", IXGBE_NETDEV_STAT(tx_carrier_errors)पूर्ण,
	अणु"tx_fifo_errors", IXGBE_NETDEV_STAT(tx_fअगरo_errors)पूर्ण,
	अणु"tx_heartbeat_errors", IXGBE_NETDEV_STAT(tx_heartbeat_errors)पूर्ण,
	अणु"tx_timeout_count", IXGBE_STAT(tx_समयout_count)पूर्ण,
	अणु"tx_restart_queue", IXGBE_STAT(restart_queue)पूर्ण,
	अणु"rx_length_errors", IXGBE_STAT(stats.rlec)पूर्ण,
	अणु"rx_long_length_errors", IXGBE_STAT(stats.roc)पूर्ण,
	अणु"rx_short_length_errors", IXGBE_STAT(stats.ruc)पूर्ण,
	अणु"tx_flow_control_xon", IXGBE_STAT(stats.lxontxc)पूर्ण,
	अणु"rx_flow_control_xon", IXGBE_STAT(stats.lxonrxc)पूर्ण,
	अणु"tx_flow_control_xoff", IXGBE_STAT(stats.lxofftxc)पूर्ण,
	अणु"rx_flow_control_xoff", IXGBE_STAT(stats.lxoffrxc)पूर्ण,
	अणु"rx_csum_offload_errors", IXGBE_STAT(hw_csum_rx_error)पूर्ण,
	अणु"alloc_rx_page", IXGBE_STAT(alloc_rx_page)पूर्ण,
	अणु"alloc_rx_page_failed", IXGBE_STAT(alloc_rx_page_failed)पूर्ण,
	अणु"alloc_rx_buff_failed", IXGBE_STAT(alloc_rx_buff_failed)पूर्ण,
	अणु"rx_no_dma_resources", IXGBE_STAT(hw_rx_no_dma_resources)पूर्ण,
	अणु"os2bmc_rx_by_bmc", IXGBE_STAT(stats.o2bgptc)पूर्ण,
	अणु"os2bmc_tx_by_bmc", IXGBE_STAT(stats.b2ospc)पूर्ण,
	अणु"os2bmc_tx_by_host", IXGBE_STAT(stats.o2bspc)पूर्ण,
	अणु"os2bmc_rx_by_host", IXGBE_STAT(stats.b2ogprc)पूर्ण,
	अणु"tx_hwtstamp_timeouts", IXGBE_STAT(tx_hwtstamp_समयouts)पूर्ण,
	अणु"tx_hwtstamp_skipped", IXGBE_STAT(tx_hwtstamp_skipped)पूर्ण,
	अणु"rx_hwtstamp_cleared", IXGBE_STAT(rx_hwtstamp_cleared)पूर्ण,
	अणु"tx_ipsec", IXGBE_STAT(tx_ipsec)पूर्ण,
	अणु"rx_ipsec", IXGBE_STAT(rx_ipsec)पूर्ण,
#अगर_घोषित IXGBE_FCOE
	अणु"fcoe_bad_fccrc", IXGBE_STAT(stats.fccrc)पूर्ण,
	अणु"rx_fcoe_dropped", IXGBE_STAT(stats.fcoerpdc)पूर्ण,
	अणु"rx_fcoe_packets", IXGBE_STAT(stats.fcoeprc)पूर्ण,
	अणु"rx_fcoe_dwords", IXGBE_STAT(stats.fcoedwrc)पूर्ण,
	अणु"fcoe_noddp", IXGBE_STAT(stats.fcoe_noddp)पूर्ण,
	अणु"fcoe_noddp_ext_buff", IXGBE_STAT(stats.fcoe_noddp_ext_buff)पूर्ण,
	अणु"tx_fcoe_packets", IXGBE_STAT(stats.fcoeptc)पूर्ण,
	अणु"tx_fcoe_dwords", IXGBE_STAT(stats.fcoedwtc)पूर्ण,
#पूर्ण_अगर /* IXGBE_FCOE */
पूर्ण;

/* ixgbe allocates num_tx_queues and num_rx_queues symmetrically so
 * we set the num_rx_queues to evaluate to num_tx_queues. This is
 * used because we करो not have a good way to get the max number of
 * rx queues with CONFIG_RPS disabled.
 */
#घोषणा IXGBE_NUM_RX_QUEUES netdev->num_tx_queues

#घोषणा IXGBE_QUEUE_STATS_LEN ( \
	(netdev->num_tx_queues + IXGBE_NUM_RX_QUEUES) * \
	(माप(काष्ठा ixgbe_queue_stats) / माप(u64)))
#घोषणा IXGBE_GLOBAL_STATS_LEN ARRAY_SIZE(ixgbe_gstrings_stats)
#घोषणा IXGBE_PB_STATS_LEN ( \
			(माप(((काष्ठा ixgbe_adapter *)0)->stats.pxonrxc) + \
			 माप(((काष्ठा ixgbe_adapter *)0)->stats.pxontxc) + \
			 माप(((काष्ठा ixgbe_adapter *)0)->stats.pxoffrxc) + \
			 माप(((काष्ठा ixgbe_adapter *)0)->stats.pxofftxc)) \
			/ माप(u64))
#घोषणा IXGBE_STATS_LEN (IXGBE_GLOBAL_STATS_LEN + \
			 IXGBE_PB_STATS_LEN + \
			 IXGBE_QUEUE_STATS_LEN)

अटल स्थिर अक्षर ixgbe_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register test  (offline)", "Eeprom test    (offline)",
	"Interrupt test (offline)", "Loopback test  (offline)",
	"Link test   (on/offline)"
पूर्ण;
#घोषणा IXGBE_TEST_LEN माप(ixgbe_gstrings_test) / ETH_GSTRING_LEN

अटल स्थिर अक्षर ixgbe_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
#घोषणा IXGBE_PRIV_FLAGS_LEGACY_RX	BIT(0)
	"legacy-rx",
#घोषणा IXGBE_PRIV_FLAGS_VF_IPSEC_EN	BIT(1)
	"vf-ipsec",
पूर्ण;

#घोषणा IXGBE_PRIV_FLAGS_STR_LEN ARRAY_SIZE(ixgbe_priv_flags_strings)

#घोषणा ixgbe_isbackplane(type) ((type) == ixgbe_media_type_backplane)

अटल व्योम ixgbe_set_supported_10gtypes(काष्ठा ixgbe_hw *hw,
					 काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!ixgbe_isbackplane(hw->phy.media_type)) अणु
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     10000baseT_Full);
		वापस;
	पूर्ण

	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_82598:
	हाल IXGBE_DEV_ID_82599_KX4:
	हाल IXGBE_DEV_ID_82599_KX4_MEZZ:
	हाल IXGBE_DEV_ID_X550EM_X_KX4:
		ethtool_link_ksettings_add_link_mode
			(cmd, supported, 10000baseKX4_Full);
		अवरोध;
	हाल IXGBE_DEV_ID_82598_BX:
	हाल IXGBE_DEV_ID_82599_KR:
	हाल IXGBE_DEV_ID_X550EM_X_KR:
	हाल IXGBE_DEV_ID_X550EM_X_XFI:
		ethtool_link_ksettings_add_link_mode
			(cmd, supported, 10000baseKR_Full);
		अवरोध;
	शेष:
		ethtool_link_ksettings_add_link_mode
			(cmd, supported, 10000baseKX4_Full);
		ethtool_link_ksettings_add_link_mode
			(cmd, supported, 10000baseKR_Full);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_set_advertising_10gtypes(काष्ठा ixgbe_hw *hw,
					   काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!ixgbe_isbackplane(hw->phy.media_type)) अणु
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     10000baseT_Full);
		वापस;
	पूर्ण

	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_82598:
	हाल IXGBE_DEV_ID_82599_KX4:
	हाल IXGBE_DEV_ID_82599_KX4_MEZZ:
	हाल IXGBE_DEV_ID_X550EM_X_KX4:
		ethtool_link_ksettings_add_link_mode
			(cmd, advertising, 10000baseKX4_Full);
		अवरोध;
	हाल IXGBE_DEV_ID_82598_BX:
	हाल IXGBE_DEV_ID_82599_KR:
	हाल IXGBE_DEV_ID_X550EM_X_KR:
	हाल IXGBE_DEV_ID_X550EM_X_XFI:
		ethtool_link_ksettings_add_link_mode
			(cmd, advertising, 10000baseKR_Full);
		अवरोध;
	शेष:
		ethtool_link_ksettings_add_link_mode
			(cmd, advertising, 10000baseKX4_Full);
		ethtool_link_ksettings_add_link_mode
			(cmd, advertising, 10000baseKR_Full);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	ixgbe_link_speed supported_link;
	bool स्वतःneg = false;

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_zero_link_mode(cmd, advertising);

	hw->mac.ops.get_link_capabilities(hw, &supported_link, &स्वतःneg);

	/* set the supported link speeds */
	अगर (supported_link & IXGBE_LINK_SPEED_10GB_FULL) अणु
		ixgbe_set_supported_10gtypes(hw, cmd);
		ixgbe_set_advertising_10gtypes(hw, cmd);
	पूर्ण
	अगर (supported_link & IXGBE_LINK_SPEED_5GB_FULL)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     5000baseT_Full);

	अगर (supported_link & IXGBE_LINK_SPEED_2_5GB_FULL)
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     2500baseT_Full);

	अगर (supported_link & IXGBE_LINK_SPEED_1GB_FULL) अणु
		अगर (ixgbe_isbackplane(hw->phy.media_type)) अणु
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     1000baseKX_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     1000baseKX_Full);
		पूर्ण अन्यथा अणु
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     1000baseT_Full);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     1000baseT_Full);
		पूर्ण
	पूर्ण
	अगर (supported_link & IXGBE_LINK_SPEED_100_FULL) अणु
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     100baseT_Full);
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     100baseT_Full);
	पूर्ण
	अगर (supported_link & IXGBE_LINK_SPEED_10_FULL) अणु
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     10baseT_Full);
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     10baseT_Full);
	पूर्ण

	/* set the advertised speeds */
	अगर (hw->phy.स्वतःneg_advertised) अणु
		ethtool_link_ksettings_zero_link_mode(cmd, advertising);
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_10_FULL)
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     10baseT_Full);
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_100_FULL)
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     100baseT_Full);
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_10GB_FULL)
			ixgbe_set_advertising_10gtypes(hw, cmd);
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_1GB_FULL) अणु
			अगर (ethtool_link_ksettings_test_link_mode
				(cmd, supported, 1000baseKX_Full))
				ethtool_link_ksettings_add_link_mode
					(cmd, advertising, 1000baseKX_Full);
			अन्यथा
				ethtool_link_ksettings_add_link_mode
					(cmd, advertising, 1000baseT_Full);
		पूर्ण
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_5GB_FULL)
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     5000baseT_Full);
		अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_2_5GB_FULL)
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     2500baseT_Full);
	पूर्ण अन्यथा अणु
		अगर (hw->phy.multispeed_fiber && !स्वतःneg) अणु
			अगर (supported_link & IXGBE_LINK_SPEED_10GB_FULL)
				ethtool_link_ksettings_add_link_mode
					(cmd, advertising, 10000baseT_Full);
		पूर्ण
	पूर्ण

	अगर (स्वतःneg) अणु
		ethtool_link_ksettings_add_link_mode(cmd, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(cmd, advertising, Autoneg);
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	पूर्ण अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	/* Determine the reमुख्यing settings based on the PHY type. */
	चयन (adapter->hw.phy.type) अणु
	हाल ixgbe_phy_tn:
	हाल ixgbe_phy_aq:
	हाल ixgbe_phy_x550em_ext_t:
	हाल ixgbe_phy_fw:
	हाल ixgbe_phy_cu_unknown:
		ethtool_link_ksettings_add_link_mode(cmd, supported, TP);
		ethtool_link_ksettings_add_link_mode(cmd, advertising, TP);
		cmd->base.port = PORT_TP;
		अवरोध;
	हाल ixgbe_phy_qt:
		ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);
		cmd->base.port = PORT_FIBRE;
		अवरोध;
	हाल ixgbe_phy_nl:
	हाल ixgbe_phy_sfp_passive_tyco:
	हाल ixgbe_phy_sfp_passive_unknown:
	हाल ixgbe_phy_sfp_ftl:
	हाल ixgbe_phy_sfp_avago:
	हाल ixgbe_phy_sfp_पूर्णांकel:
	हाल ixgbe_phy_sfp_unknown:
	हाल ixgbe_phy_qsfp_passive_unknown:
	हाल ixgbe_phy_qsfp_active_unknown:
	हाल ixgbe_phy_qsfp_पूर्णांकel:
	हाल ixgbe_phy_qsfp_unknown:
		/* SFP+ devices, further checking needed */
		चयन (adapter->hw.phy.sfp_type) अणु
		हाल ixgbe_sfp_type_da_cu:
		हाल ixgbe_sfp_type_da_cu_core0:
		हाल ixgbe_sfp_type_da_cu_core1:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     FIBRE);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     FIBRE);
			cmd->base.port = PORT_DA;
			अवरोध;
		हाल ixgbe_sfp_type_sr:
		हाल ixgbe_sfp_type_lr:
		हाल ixgbe_sfp_type_srlr_core0:
		हाल ixgbe_sfp_type_srlr_core1:
		हाल ixgbe_sfp_type_1g_sx_core0:
		हाल ixgbe_sfp_type_1g_sx_core1:
		हाल ixgbe_sfp_type_1g_lx_core0:
		हाल ixgbe_sfp_type_1g_lx_core1:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     FIBRE);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     FIBRE);
			cmd->base.port = PORT_FIBRE;
			अवरोध;
		हाल ixgbe_sfp_type_not_present:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     FIBRE);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     FIBRE);
			cmd->base.port = PORT_NONE;
			अवरोध;
		हाल ixgbe_sfp_type_1g_cu_core0:
		हाल ixgbe_sfp_type_1g_cu_core1:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     TP);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     TP);
			cmd->base.port = PORT_TP;
			अवरोध;
		हाल ixgbe_sfp_type_unknown:
		शेष:
			ethtool_link_ksettings_add_link_mode(cmd, supported,
							     FIBRE);
			ethtool_link_ksettings_add_link_mode(cmd, advertising,
							     FIBRE);
			cmd->base.port = PORT_OTHER;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल ixgbe_phy_xaui:
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     FIBRE);
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     FIBRE);
		cmd->base.port = PORT_NONE;
		अवरोध;
	हाल ixgbe_phy_unknown:
	हाल ixgbe_phy_generic:
	हाल ixgbe_phy_sfp_unsupported:
	शेष:
		ethtool_link_ksettings_add_link_mode(cmd, supported,
						     FIBRE);
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     FIBRE);
		cmd->base.port = PORT_OTHER;
		अवरोध;
	पूर्ण

	/* Indicate छोड़ो support */
	ethtool_link_ksettings_add_link_mode(cmd, supported, Pause);

	चयन (hw->fc.requested_mode) अणु
	हाल ixgbe_fc_full:
		ethtool_link_ksettings_add_link_mode(cmd, advertising, Pause);
		अवरोध;
	हाल ixgbe_fc_rx_छोड़ो:
		ethtool_link_ksettings_add_link_mode(cmd, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Asym_Pause);
		अवरोध;
	हाल ixgbe_fc_tx_छोड़ो:
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Asym_Pause);
		अवरोध;
	शेष:
		ethtool_link_ksettings_del_link_mode(cmd, advertising, Pause);
		ethtool_link_ksettings_del_link_mode(cmd, advertising,
						     Asym_Pause);
	पूर्ण

	अगर (netअगर_carrier_ok(netdev)) अणु
		चयन (adapter->link_speed) अणु
		हाल IXGBE_LINK_SPEED_10GB_FULL:
			cmd->base.speed = SPEED_10000;
			अवरोध;
		हाल IXGBE_LINK_SPEED_5GB_FULL:
			cmd->base.speed = SPEED_5000;
			अवरोध;
		हाल IXGBE_LINK_SPEED_2_5GB_FULL:
			cmd->base.speed = SPEED_2500;
			अवरोध;
		हाल IXGBE_LINK_SPEED_1GB_FULL:
			cmd->base.speed = SPEED_1000;
			अवरोध;
		हाल IXGBE_LINK_SPEED_100_FULL:
			cmd->base.speed = SPEED_100;
			अवरोध;
		हाल IXGBE_LINK_SPEED_10_FULL:
			cmd->base.speed = SPEED_10;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		cmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 advertised, old;
	s32 err = 0;

	अगर ((hw->phy.media_type == ixgbe_media_type_copper) ||
	    (hw->phy.multispeed_fiber)) अणु
		/*
		 * this function करोes not support duplex क्रमcing, but can
		 * limit the advertising of the adapter to the specअगरied speed
		 */
		अगर (!biपंचांगap_subset(cmd->link_modes.advertising,
				   cmd->link_modes.supported,
				   __ETHTOOL_LINK_MODE_MASK_NBITS))
			वापस -EINVAL;

		/* only allow one speed at a समय अगर no स्वतःneg */
		अगर (!cmd->base.स्वतःneg && hw->phy.multispeed_fiber) अणु
			अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising,
								  10000baseT_Full) &&
			    ethtool_link_ksettings_test_link_mode(cmd, advertising,
								  1000baseT_Full))
				वापस -EINVAL;
		पूर्ण

		old = hw->phy.स्वतःneg_advertised;
		advertised = 0;
		अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising,
							  10000baseT_Full))
			advertised |= IXGBE_LINK_SPEED_10GB_FULL;
		अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising,
							  5000baseT_Full))
			advertised |= IXGBE_LINK_SPEED_5GB_FULL;
		अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising,
							  2500baseT_Full))
			advertised |= IXGBE_LINK_SPEED_2_5GB_FULL;
		अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising,
							  1000baseT_Full))
			advertised |= IXGBE_LINK_SPEED_1GB_FULL;

		अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising,
							  100baseT_Full))
			advertised |= IXGBE_LINK_SPEED_100_FULL;

		अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising,
							  10baseT_Full))
			advertised |= IXGBE_LINK_SPEED_10_FULL;

		अगर (old == advertised)
			वापस err;
		/* this sets the link speed and restarts स्वतः-neg */
		जबतक (test_and_set_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
			usleep_range(1000, 2000);

		hw->mac.स्वतःtry_restart = true;
		err = hw->mac.ops.setup_link(hw, advertised, true);
		अगर (err) अणु
			e_info(probe, "setup link failed with code %d\n", err);
			hw->mac.ops.setup_link(hw, old, true);
		पूर्ण
		clear_bit(__IXGBE_IN_SFP_INIT, &adapter->state);
	पूर्ण अन्यथा अणु
		/* in this हाल we currently only support 10Gb/FULL */
		u32 speed = cmd->base.speed;

		अगर ((cmd->base.स्वतःneg == AUTONEG_ENABLE) ||
		    (!ethtool_link_ksettings_test_link_mode(cmd, advertising,
							    10000baseT_Full)) ||
		    (speed + cmd->base.duplex != SPEED_10000 + DUPLEX_FULL))
			वापस -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम ixgbe_get_छोड़ो_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_छोड़ो_stats *stats)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw_stats *hwstats = &adapter->stats;

	stats->tx_छोड़ो_frames = hwstats->lxontxc + hwstats->lxofftxc;
	stats->rx_छोड़ो_frames = hwstats->lxonrxc + hwstats->lxoffrxc;
पूर्ण

अटल व्योम ixgbe_get_छोड़ोparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (ixgbe_device_supports_स्वतःneg_fc(hw) &&
	    !hw->fc.disable_fc_स्वतःneg)
		छोड़ो->स्वतःneg = 1;
	अन्यथा
		छोड़ो->स्वतःneg = 0;

	अगर (hw->fc.current_mode == ixgbe_fc_rx_छोड़ो) अणु
		छोड़ो->rx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == ixgbe_fc_tx_छोड़ो) अणु
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == ixgbe_fc_full) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_set_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_fc_info fc = hw->fc;

	/* 82598 करोes no support link flow control with DCB enabled */
	अगर ((hw->mac.type == ixgbe_mac_82598EB) &&
	    (adapter->flags & IXGBE_FLAG_DCB_ENABLED))
		वापस -EINVAL;

	/* some devices करो not support स्वतःneg of link flow control */
	अगर ((छोड़ो->स्वतःneg == AUTONEG_ENABLE) &&
	    !ixgbe_device_supports_स्वतःneg_fc(hw))
		वापस -EINVAL;

	fc.disable_fc_स्वतःneg = (छोड़ो->स्वतःneg != AUTONEG_ENABLE);

	अगर ((छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो) || छोड़ो->स्वतःneg)
		fc.requested_mode = ixgbe_fc_full;
	अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		fc.requested_mode = ixgbe_fc_rx_छोड़ो;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		fc.requested_mode = ixgbe_fc_tx_छोड़ो;
	अन्यथा
		fc.requested_mode = ixgbe_fc_none;

	/* अगर the thing changed then we'll update and use new स्वतःneg */
	अगर (स_भेद(&fc, &hw->fc, माप(काष्ठा ixgbe_fc_info))) अणु
		hw->fc = fc;
		अगर (netअगर_running(netdev))
			ixgbe_reinit_locked(adapter);
		अन्यथा
			ixgbe_reset(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 ixgbe_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	वापस adapter->msg_enable;
पूर्ण

अटल व्योम ixgbe_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	adapter->msg_enable = data;
पूर्ण

अटल पूर्णांक ixgbe_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा IXGBE_REGS_LEN  1145
	वापस IXGBE_REGS_LEN * माप(u32);
पूर्ण

#घोषणा IXGBE_GET_STAT(_A_, _R_) _A_->stats._R_

अटल व्योम ixgbe_get_regs(काष्ठा net_device *netdev,
			   काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u8 i;

	स_रखो(p, 0, IXGBE_REGS_LEN * माप(u32));

	regs->version = hw->mac.type << 24 | hw->revision_id << 16 |
			hw->device_id;

	/* General Registers */
	regs_buff[0] = IXGBE_READ_REG(hw, IXGBE_CTRL);
	regs_buff[1] = IXGBE_READ_REG(hw, IXGBE_STATUS);
	regs_buff[2] = IXGBE_READ_REG(hw, IXGBE_CTRL_EXT);
	regs_buff[3] = IXGBE_READ_REG(hw, IXGBE_ESDP);
	regs_buff[4] = IXGBE_READ_REG(hw, IXGBE_EODSDP);
	regs_buff[5] = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
	regs_buff[6] = IXGBE_READ_REG(hw, IXGBE_FRTIMER);
	regs_buff[7] = IXGBE_READ_REG(hw, IXGBE_TCPTIMER);

	/* NVM Register */
	regs_buff[8] = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
	regs_buff[9] = IXGBE_READ_REG(hw, IXGBE_EERD);
	regs_buff[10] = IXGBE_READ_REG(hw, IXGBE_FLA(hw));
	regs_buff[11] = IXGBE_READ_REG(hw, IXGBE_EEMNGCTL);
	regs_buff[12] = IXGBE_READ_REG(hw, IXGBE_EEMNGDATA);
	regs_buff[13] = IXGBE_READ_REG(hw, IXGBE_FLMNGCTL);
	regs_buff[14] = IXGBE_READ_REG(hw, IXGBE_FLMNGDATA);
	regs_buff[15] = IXGBE_READ_REG(hw, IXGBE_FLMNGCNT);
	regs_buff[16] = IXGBE_READ_REG(hw, IXGBE_FLOP);
	regs_buff[17] = IXGBE_READ_REG(hw, IXGBE_GRC(hw));

	/* Interrupt */
	/* करोn't पढ़ो EICR because it can clear पूर्णांकerrupt causes, instead
	 * पढ़ो EICS which is a shaकरोw but करोesn't clear EICR */
	regs_buff[18] = IXGBE_READ_REG(hw, IXGBE_EICS);
	regs_buff[19] = IXGBE_READ_REG(hw, IXGBE_EICS);
	regs_buff[20] = IXGBE_READ_REG(hw, IXGBE_EIMS);
	regs_buff[21] = IXGBE_READ_REG(hw, IXGBE_EIMC);
	regs_buff[22] = IXGBE_READ_REG(hw, IXGBE_EIAC);
	regs_buff[23] = IXGBE_READ_REG(hw, IXGBE_EIAM);
	regs_buff[24] = IXGBE_READ_REG(hw, IXGBE_EITR(0));
	regs_buff[25] = IXGBE_READ_REG(hw, IXGBE_IVAR(0));
	regs_buff[26] = IXGBE_READ_REG(hw, IXGBE_MSIXT);
	regs_buff[27] = IXGBE_READ_REG(hw, IXGBE_MSIXPBA);
	regs_buff[28] = IXGBE_READ_REG(hw, IXGBE_PBACL(0));
	regs_buff[29] = IXGBE_READ_REG(hw, IXGBE_GPIE);

	/* Flow Control */
	regs_buff[30] = IXGBE_READ_REG(hw, IXGBE_PFCTOP);
	क्रम (i = 0; i < 4; i++)
		regs_buff[31 + i] = IXGBE_READ_REG(hw, IXGBE_FCTTV(i));
	क्रम (i = 0; i < 8; i++) अणु
		चयन (hw->mac.type) अणु
		हाल ixgbe_mac_82598EB:
			regs_buff[35 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTL(i));
			regs_buff[43 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTH(i));
			अवरोध;
		हाल ixgbe_mac_82599EB:
		हाल ixgbe_mac_X540:
		हाल ixgbe_mac_X550:
		हाल ixgbe_mac_X550EM_x:
		हाल ixgbe_mac_x550em_a:
			regs_buff[35 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTL_82599(i));
			regs_buff[43 + i] = IXGBE_READ_REG(hw, IXGBE_FCRTH_82599(i));
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	regs_buff[51] = IXGBE_READ_REG(hw, IXGBE_FCRTV);
	regs_buff[52] = IXGBE_READ_REG(hw, IXGBE_TFCS);

	/* Receive DMA */
	क्रम (i = 0; i < 64; i++)
		regs_buff[53 + i] = IXGBE_READ_REG(hw, IXGBE_RDBAL(i));
	क्रम (i = 0; i < 64; i++)
		regs_buff[117 + i] = IXGBE_READ_REG(hw, IXGBE_RDBAH(i));
	क्रम (i = 0; i < 64; i++)
		regs_buff[181 + i] = IXGBE_READ_REG(hw, IXGBE_RDLEN(i));
	क्रम (i = 0; i < 64; i++)
		regs_buff[245 + i] = IXGBE_READ_REG(hw, IXGBE_RDH(i));
	क्रम (i = 0; i < 64; i++)
		regs_buff[309 + i] = IXGBE_READ_REG(hw, IXGBE_RDT(i));
	क्रम (i = 0; i < 64; i++)
		regs_buff[373 + i] = IXGBE_READ_REG(hw, IXGBE_RXDCTL(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[437 + i] = IXGBE_READ_REG(hw, IXGBE_SRRCTL(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[453 + i] = IXGBE_READ_REG(hw, IXGBE_DCA_RXCTRL(i));
	regs_buff[469] = IXGBE_READ_REG(hw, IXGBE_RDRXCTL);
	क्रम (i = 0; i < 8; i++)
		regs_buff[470 + i] = IXGBE_READ_REG(hw, IXGBE_RXPBSIZE(i));
	regs_buff[478] = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	regs_buff[479] = IXGBE_READ_REG(hw, IXGBE_DROPEN);

	/* Receive */
	regs_buff[480] = IXGBE_READ_REG(hw, IXGBE_RXCSUM);
	regs_buff[481] = IXGBE_READ_REG(hw, IXGBE_RFCTL);
	क्रम (i = 0; i < 16; i++)
		regs_buff[482 + i] = IXGBE_READ_REG(hw, IXGBE_RAL(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[498 + i] = IXGBE_READ_REG(hw, IXGBE_RAH(i));
	regs_buff[514] = IXGBE_READ_REG(hw, IXGBE_PSRTYPE(0));
	regs_buff[515] = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	regs_buff[516] = IXGBE_READ_REG(hw, IXGBE_VLNCTRL);
	regs_buff[517] = IXGBE_READ_REG(hw, IXGBE_MCSTCTRL);
	regs_buff[518] = IXGBE_READ_REG(hw, IXGBE_MRQC);
	regs_buff[519] = IXGBE_READ_REG(hw, IXGBE_VMD_CTL);
	क्रम (i = 0; i < 8; i++)
		regs_buff[520 + i] = IXGBE_READ_REG(hw, IXGBE_IMIR(i));
	क्रम (i = 0; i < 8; i++)
		regs_buff[528 + i] = IXGBE_READ_REG(hw, IXGBE_IMIREXT(i));
	regs_buff[536] = IXGBE_READ_REG(hw, IXGBE_IMIRVP);

	/* Transmit */
	क्रम (i = 0; i < 32; i++)
		regs_buff[537 + i] = IXGBE_READ_REG(hw, IXGBE_TDBAL(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[569 + i] = IXGBE_READ_REG(hw, IXGBE_TDBAH(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[601 + i] = IXGBE_READ_REG(hw, IXGBE_TDLEN(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[633 + i] = IXGBE_READ_REG(hw, IXGBE_TDH(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[665 + i] = IXGBE_READ_REG(hw, IXGBE_TDT(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[697 + i] = IXGBE_READ_REG(hw, IXGBE_TXDCTL(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[729 + i] = IXGBE_READ_REG(hw, IXGBE_TDWBAL(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[761 + i] = IXGBE_READ_REG(hw, IXGBE_TDWBAH(i));
	regs_buff[793] = IXGBE_READ_REG(hw, IXGBE_DTXCTL);
	क्रम (i = 0; i < 16; i++)
		regs_buff[794 + i] = IXGBE_READ_REG(hw, IXGBE_DCA_TXCTRL(i));
	regs_buff[810] = IXGBE_READ_REG(hw, IXGBE_TIPG);
	क्रम (i = 0; i < 8; i++)
		regs_buff[811 + i] = IXGBE_READ_REG(hw, IXGBE_TXPBSIZE(i));
	regs_buff[819] = IXGBE_READ_REG(hw, IXGBE_MNGTXMAP);

	/* Wake Up */
	regs_buff[820] = IXGBE_READ_REG(hw, IXGBE_WUC);
	regs_buff[821] = IXGBE_READ_REG(hw, IXGBE_WUFC);
	regs_buff[822] = IXGBE_READ_REG(hw, IXGBE_WUS);
	regs_buff[823] = IXGBE_READ_REG(hw, IXGBE_IPAV);
	regs_buff[824] = IXGBE_READ_REG(hw, IXGBE_IP4AT);
	regs_buff[825] = IXGBE_READ_REG(hw, IXGBE_IP6AT);
	regs_buff[826] = IXGBE_READ_REG(hw, IXGBE_WUPL);
	regs_buff[827] = IXGBE_READ_REG(hw, IXGBE_WUPM);
	regs_buff[828] = IXGBE_READ_REG(hw, IXGBE_FHFT(0));

	/* DCB */
	regs_buff[829] = IXGBE_READ_REG(hw, IXGBE_RMCS);   /* same as FCCFG  */
	regs_buff[831] = IXGBE_READ_REG(hw, IXGBE_PDPMCS); /* same as RTTPCS */

	चयन (hw->mac.type) अणु
	हाल ixgbe_mac_82598EB:
		regs_buff[830] = IXGBE_READ_REG(hw, IXGBE_DPMCS);
		regs_buff[832] = IXGBE_READ_REG(hw, IXGBE_RUPPBMR);
		क्रम (i = 0; i < 8; i++)
			regs_buff[833 + i] =
				IXGBE_READ_REG(hw, IXGBE_RT2CR(i));
		क्रम (i = 0; i < 8; i++)
			regs_buff[841 + i] =
				IXGBE_READ_REG(hw, IXGBE_RT2SR(i));
		क्रम (i = 0; i < 8; i++)
			regs_buff[849 + i] =
				IXGBE_READ_REG(hw, IXGBE_TDTQ2TCCR(i));
		क्रम (i = 0; i < 8; i++)
			regs_buff[857 + i] =
				IXGBE_READ_REG(hw, IXGBE_TDTQ2TCSR(i));
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		regs_buff[830] = IXGBE_READ_REG(hw, IXGBE_RTTDCS);
		regs_buff[832] = IXGBE_READ_REG(hw, IXGBE_RTRPCS);
		क्रम (i = 0; i < 8; i++)
			regs_buff[833 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTRPT4C(i));
		क्रम (i = 0; i < 8; i++)
			regs_buff[841 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTRPT4S(i));
		क्रम (i = 0; i < 8; i++)
			regs_buff[849 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTTDT2C(i));
		क्रम (i = 0; i < 8; i++)
			regs_buff[857 + i] =
				IXGBE_READ_REG(hw, IXGBE_RTTDT2S(i));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < 8; i++)
		regs_buff[865 + i] =
		IXGBE_READ_REG(hw, IXGBE_TDPT2TCCR(i)); /* same as RTTPT2C */
	क्रम (i = 0; i < 8; i++)
		regs_buff[873 + i] =
		IXGBE_READ_REG(hw, IXGBE_TDPT2TCSR(i)); /* same as RTTPT2S */

	/* Statistics */
	regs_buff[881] = IXGBE_GET_STAT(adapter, crcerrs);
	regs_buff[882] = IXGBE_GET_STAT(adapter, illerrc);
	regs_buff[883] = IXGBE_GET_STAT(adapter, errbc);
	regs_buff[884] = IXGBE_GET_STAT(adapter, mspdc);
	क्रम (i = 0; i < 8; i++)
		regs_buff[885 + i] = IXGBE_GET_STAT(adapter, mpc[i]);
	regs_buff[893] = IXGBE_GET_STAT(adapter, mlfc);
	regs_buff[894] = IXGBE_GET_STAT(adapter, mrfc);
	regs_buff[895] = IXGBE_GET_STAT(adapter, rlec);
	regs_buff[896] = IXGBE_GET_STAT(adapter, lxontxc);
	regs_buff[897] = IXGBE_GET_STAT(adapter, lxonrxc);
	regs_buff[898] = IXGBE_GET_STAT(adapter, lxofftxc);
	regs_buff[899] = IXGBE_GET_STAT(adapter, lxoffrxc);
	क्रम (i = 0; i < 8; i++)
		regs_buff[900 + i] = IXGBE_GET_STAT(adapter, pxontxc[i]);
	क्रम (i = 0; i < 8; i++)
		regs_buff[908 + i] = IXGBE_GET_STAT(adapter, pxonrxc[i]);
	क्रम (i = 0; i < 8; i++)
		regs_buff[916 + i] = IXGBE_GET_STAT(adapter, pxofftxc[i]);
	क्रम (i = 0; i < 8; i++)
		regs_buff[924 + i] = IXGBE_GET_STAT(adapter, pxoffrxc[i]);
	regs_buff[932] = IXGBE_GET_STAT(adapter, prc64);
	regs_buff[933] = IXGBE_GET_STAT(adapter, prc127);
	regs_buff[934] = IXGBE_GET_STAT(adapter, prc255);
	regs_buff[935] = IXGBE_GET_STAT(adapter, prc511);
	regs_buff[936] = IXGBE_GET_STAT(adapter, prc1023);
	regs_buff[937] = IXGBE_GET_STAT(adapter, prc1522);
	regs_buff[938] = IXGBE_GET_STAT(adapter, gprc);
	regs_buff[939] = IXGBE_GET_STAT(adapter, bprc);
	regs_buff[940] = IXGBE_GET_STAT(adapter, mprc);
	regs_buff[941] = IXGBE_GET_STAT(adapter, gptc);
	regs_buff[942] = (u32)IXGBE_GET_STAT(adapter, gorc);
	regs_buff[943] = (u32)(IXGBE_GET_STAT(adapter, gorc) >> 32);
	regs_buff[944] = (u32)IXGBE_GET_STAT(adapter, gotc);
	regs_buff[945] = (u32)(IXGBE_GET_STAT(adapter, gotc) >> 32);
	क्रम (i = 0; i < 8; i++)
		regs_buff[946 + i] = IXGBE_GET_STAT(adapter, rnbc[i]);
	regs_buff[954] = IXGBE_GET_STAT(adapter, ruc);
	regs_buff[955] = IXGBE_GET_STAT(adapter, rfc);
	regs_buff[956] = IXGBE_GET_STAT(adapter, roc);
	regs_buff[957] = IXGBE_GET_STAT(adapter, rjc);
	regs_buff[958] = IXGBE_GET_STAT(adapter, mngprc);
	regs_buff[959] = IXGBE_GET_STAT(adapter, mngpdc);
	regs_buff[960] = IXGBE_GET_STAT(adapter, mngptc);
	regs_buff[961] = (u32)IXGBE_GET_STAT(adapter, tor);
	regs_buff[962] = (u32)(IXGBE_GET_STAT(adapter, tor) >> 32);
	regs_buff[963] = IXGBE_GET_STAT(adapter, tpr);
	regs_buff[964] = IXGBE_GET_STAT(adapter, tpt);
	regs_buff[965] = IXGBE_GET_STAT(adapter, ptc64);
	regs_buff[966] = IXGBE_GET_STAT(adapter, ptc127);
	regs_buff[967] = IXGBE_GET_STAT(adapter, ptc255);
	regs_buff[968] = IXGBE_GET_STAT(adapter, ptc511);
	regs_buff[969] = IXGBE_GET_STAT(adapter, ptc1023);
	regs_buff[970] = IXGBE_GET_STAT(adapter, ptc1522);
	regs_buff[971] = IXGBE_GET_STAT(adapter, mptc);
	regs_buff[972] = IXGBE_GET_STAT(adapter, bptc);
	regs_buff[973] = IXGBE_GET_STAT(adapter, xec);
	क्रम (i = 0; i < 16; i++)
		regs_buff[974 + i] = IXGBE_GET_STAT(adapter, qprc[i]);
	क्रम (i = 0; i < 16; i++)
		regs_buff[990 + i] = IXGBE_GET_STAT(adapter, qptc[i]);
	क्रम (i = 0; i < 16; i++)
		regs_buff[1006 + i] = IXGBE_GET_STAT(adapter, qbrc[i]);
	क्रम (i = 0; i < 16; i++)
		regs_buff[1022 + i] = IXGBE_GET_STAT(adapter, qbtc[i]);

	/* MAC */
	regs_buff[1038] = IXGBE_READ_REG(hw, IXGBE_PCS1GCFIG);
	regs_buff[1039] = IXGBE_READ_REG(hw, IXGBE_PCS1GLCTL);
	regs_buff[1040] = IXGBE_READ_REG(hw, IXGBE_PCS1GLSTA);
	regs_buff[1041] = IXGBE_READ_REG(hw, IXGBE_PCS1GDBG0);
	regs_buff[1042] = IXGBE_READ_REG(hw, IXGBE_PCS1GDBG1);
	regs_buff[1043] = IXGBE_READ_REG(hw, IXGBE_PCS1GANA);
	regs_buff[1044] = IXGBE_READ_REG(hw, IXGBE_PCS1GANLP);
	regs_buff[1045] = IXGBE_READ_REG(hw, IXGBE_PCS1GANNP);
	regs_buff[1046] = IXGBE_READ_REG(hw, IXGBE_PCS1GANLPNP);
	regs_buff[1047] = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	regs_buff[1048] = IXGBE_READ_REG(hw, IXGBE_HLREG1);
	regs_buff[1049] = IXGBE_READ_REG(hw, IXGBE_PAP);
	regs_buff[1050] = IXGBE_READ_REG(hw, IXGBE_MACA);
	regs_buff[1051] = IXGBE_READ_REG(hw, IXGBE_APAE);
	regs_buff[1052] = IXGBE_READ_REG(hw, IXGBE_ARD);
	regs_buff[1053] = IXGBE_READ_REG(hw, IXGBE_AIS);
	regs_buff[1054] = IXGBE_READ_REG(hw, IXGBE_MSCA);
	regs_buff[1055] = IXGBE_READ_REG(hw, IXGBE_MSRWD);
	regs_buff[1056] = IXGBE_READ_REG(hw, IXGBE_MLADD);
	regs_buff[1057] = IXGBE_READ_REG(hw, IXGBE_MHADD);
	regs_buff[1058] = IXGBE_READ_REG(hw, IXGBE_TREG);
	regs_buff[1059] = IXGBE_READ_REG(hw, IXGBE_PCSS1);
	regs_buff[1060] = IXGBE_READ_REG(hw, IXGBE_PCSS2);
	regs_buff[1061] = IXGBE_READ_REG(hw, IXGBE_XPCSS);
	regs_buff[1062] = IXGBE_READ_REG(hw, IXGBE_SERDESC);
	regs_buff[1063] = IXGBE_READ_REG(hw, IXGBE_MACS);
	regs_buff[1064] = IXGBE_READ_REG(hw, IXGBE_AUTOC);
	regs_buff[1065] = IXGBE_READ_REG(hw, IXGBE_LINKS);
	regs_buff[1066] = IXGBE_READ_REG(hw, IXGBE_AUTOC2);
	regs_buff[1067] = IXGBE_READ_REG(hw, IXGBE_AUTOC3);
	regs_buff[1068] = IXGBE_READ_REG(hw, IXGBE_ANLP1);
	regs_buff[1069] = IXGBE_READ_REG(hw, IXGBE_ANLP2);
	regs_buff[1070] = IXGBE_READ_REG(hw, IXGBE_ATLASCTL);

	/* Diagnostic */
	regs_buff[1071] = IXGBE_READ_REG(hw, IXGBE_RDSTATCTL);
	क्रम (i = 0; i < 8; i++)
		regs_buff[1072 + i] = IXGBE_READ_REG(hw, IXGBE_RDSTAT(i));
	regs_buff[1080] = IXGBE_READ_REG(hw, IXGBE_RDHMPN);
	क्रम (i = 0; i < 4; i++)
		regs_buff[1081 + i] = IXGBE_READ_REG(hw, IXGBE_RIC_DW(i));
	regs_buff[1085] = IXGBE_READ_REG(hw, IXGBE_RDPROBE);
	regs_buff[1086] = IXGBE_READ_REG(hw, IXGBE_TDSTATCTL);
	क्रम (i = 0; i < 8; i++)
		regs_buff[1087 + i] = IXGBE_READ_REG(hw, IXGBE_TDSTAT(i));
	regs_buff[1095] = IXGBE_READ_REG(hw, IXGBE_TDHMPN);
	क्रम (i = 0; i < 4; i++)
		regs_buff[1096 + i] = IXGBE_READ_REG(hw, IXGBE_TIC_DW(i));
	regs_buff[1100] = IXGBE_READ_REG(hw, IXGBE_TDPROBE);
	regs_buff[1101] = IXGBE_READ_REG(hw, IXGBE_TXBUFCTRL);
	क्रम (i = 0; i < 4; i++)
		regs_buff[1102 + i] = IXGBE_READ_REG(hw, IXGBE_TXBUFDATA(i));
	regs_buff[1106] = IXGBE_READ_REG(hw, IXGBE_RXBUFCTRL);
	क्रम (i = 0; i < 4; i++)
		regs_buff[1107 + i] = IXGBE_READ_REG(hw, IXGBE_RXBUFDATA(i));
	क्रम (i = 0; i < 8; i++)
		regs_buff[1111 + i] = IXGBE_READ_REG(hw, IXGBE_PCIE_DIAG(i));
	regs_buff[1119] = IXGBE_READ_REG(hw, IXGBE_RFVAL);
	regs_buff[1120] = IXGBE_READ_REG(hw, IXGBE_MDFTC1);
	regs_buff[1121] = IXGBE_READ_REG(hw, IXGBE_MDFTC2);
	regs_buff[1122] = IXGBE_READ_REG(hw, IXGBE_MDFTFIFO1);
	regs_buff[1123] = IXGBE_READ_REG(hw, IXGBE_MDFTFIFO2);
	regs_buff[1124] = IXGBE_READ_REG(hw, IXGBE_MDFTS);
	regs_buff[1125] = IXGBE_READ_REG(hw, IXGBE_PCIEECCCTL);
	regs_buff[1126] = IXGBE_READ_REG(hw, IXGBE_PBTXECC);
	regs_buff[1127] = IXGBE_READ_REG(hw, IXGBE_PBRXECC);

	/* 82599 X540 specअगरic रेजिस्टरs  */
	regs_buff[1128] = IXGBE_READ_REG(hw, IXGBE_MFLCN);

	/* 82599 X540 specअगरic DCB रेजिस्टरs  */
	regs_buff[1129] = IXGBE_READ_REG(hw, IXGBE_RTRUP2TC);
	regs_buff[1130] = IXGBE_READ_REG(hw, IXGBE_RTTUP2TC);
	क्रम (i = 0; i < 4; i++)
		regs_buff[1131 + i] = IXGBE_READ_REG(hw, IXGBE_TXLLQ(i));
	regs_buff[1135] = IXGBE_READ_REG(hw, IXGBE_RTTBCNRM);
					/* same as RTTQCNRM */
	regs_buff[1136] = IXGBE_READ_REG(hw, IXGBE_RTTBCNRD);
					/* same as RTTQCNRR */

	/* X540 specअगरic DCB रेजिस्टरs  */
	regs_buff[1137] = IXGBE_READ_REG(hw, IXGBE_RTTQCNCR);
	regs_buff[1138] = IXGBE_READ_REG(hw, IXGBE_RTTQCNTG);

	/* Security config रेजिस्टरs */
	regs_buff[1139] = IXGBE_READ_REG(hw, IXGBE_SECTXCTRL);
	regs_buff[1140] = IXGBE_READ_REG(hw, IXGBE_SECTXSTAT);
	regs_buff[1141] = IXGBE_READ_REG(hw, IXGBE_SECTXBUFFAF);
	regs_buff[1142] = IXGBE_READ_REG(hw, IXGBE_SECTXMINIFG);
	regs_buff[1143] = IXGBE_READ_REG(hw, IXGBE_SECRXCTRL);
	regs_buff[1144] = IXGBE_READ_REG(hw, IXGBE_SECRXSTAT);
पूर्ण

अटल पूर्णांक ixgbe_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	वापस adapter->hw.eeprom.word_size * 2;
पूर्ण

अटल पूर्णांक ixgbe_get_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	पूर्णांक first_word, last_word, eeprom_len;
	पूर्णांक ret_val = 0;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	eeprom->magic = hw->venकरोr_id | (hw->device_id << 16);

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_len = last_word - first_word + 1;

	eeprom_buff = kदो_स्मृति_array(eeprom_len, माप(u16), GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	ret_val = hw->eeprom.ops.पढ़ो_buffer(hw, first_word, eeprom_len,
					     eeprom_buff);

	/* Device's eeprom is always little-endian, word addressable */
	क्रम (i = 0; i < eeprom_len; i++)
		le16_to_cpus(&eeprom_buff[i]);

	स_नकल(bytes, (u8 *)eeprom_buff + (eeprom->offset & 1), eeprom->len);
	kमुक्त(eeprom_buff);

	वापस ret_val;
पूर्ण

अटल पूर्णांक ixgbe_set_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	व्योम *ptr;
	पूर्णांक max_len, first_word, last_word, ret_val = 0;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	अगर (eeprom->magic != (hw->venकरोr_id | (hw->device_id << 16)))
		वापस -EINVAL;

	max_len = hw->eeprom.word_size * 2;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kदो_स्मृति(max_len, GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	ptr = eeprom_buff;

	अगर (eeprom->offset & 1) अणु
		/*
		 * need पढ़ो/modअगरy/ग_लिखो of first changed EEPROM word
		 * only the second byte of the word is being modअगरied
		 */
		ret_val = hw->eeprom.ops.पढ़ो(hw, first_word, &eeprom_buff[0]);
		अगर (ret_val)
			जाओ err;

		ptr++;
	पूर्ण
	अगर ((eeprom->offset + eeprom->len) & 1) अणु
		/*
		 * need पढ़ो/modअगरy/ग_लिखो of last changed EEPROM word
		 * only the first byte of the word is being modअगरied
		 */
		ret_val = hw->eeprom.ops.पढ़ो(hw, last_word,
					  &eeprom_buff[last_word - first_word]);
		अगर (ret_val)
			जाओ err;
	पूर्ण

	/* Device's eeprom is always little-endian, word addressable */
	क्रम (i = 0; i < last_word - first_word + 1; i++)
		le16_to_cpus(&eeprom_buff[i]);

	स_नकल(ptr, bytes, eeprom->len);

	क्रम (i = 0; i < last_word - first_word + 1; i++)
		cpu_to_le16s(&eeprom_buff[i]);

	ret_val = hw->eeprom.ops.ग_लिखो_buffer(hw, first_word,
					      last_word - first_word + 1,
					      eeprom_buff);

	/* Update the checksum */
	अगर (ret_val == 0)
		hw->eeprom.ops.update_checksum(hw);

err:
	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल व्योम ixgbe_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, ixgbe_driver_name, माप(drvinfo->driver));

	strlcpy(drvinfo->fw_version, adapter->eeprom_id,
		माप(drvinfo->fw_version));

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));

	drvinfo->n_priv_flags = IXGBE_PRIV_FLAGS_STR_LEN;
पूर्ण

अटल व्योम ixgbe_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_ring *tx_ring = adapter->tx_ring[0];
	काष्ठा ixgbe_ring *rx_ring = adapter->rx_ring[0];

	ring->rx_max_pending = IXGBE_MAX_RXD;
	ring->tx_max_pending = IXGBE_MAX_TXD;
	ring->rx_pending = rx_ring->count;
	ring->tx_pending = tx_ring->count;
पूर्ण

अटल पूर्णांक ixgbe_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_ring *temp_ring;
	पूर्णांक i, j, err = 0;
	u32 new_rx_count, new_tx_count;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	new_tx_count = clamp_t(u32, ring->tx_pending,
			       IXGBE_MIN_TXD, IXGBE_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, IXGBE_REQ_TX_DESCRIPTOR_MULTIPLE);

	new_rx_count = clamp_t(u32, ring->rx_pending,
			       IXGBE_MIN_RXD, IXGBE_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, IXGBE_REQ_RX_DESCRIPTOR_MULTIPLE);

	अगर ((new_tx_count == adapter->tx_ring_count) &&
	    (new_rx_count == adapter->rx_ring_count)) अणु
		/* nothing to करो */
		वापस 0;
	पूर्ण

	जबतक (test_and_set_bit(__IXGBE_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (!netअगर_running(adapter->netdev)) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			adapter->tx_ring[i]->count = new_tx_count;
		क्रम (i = 0; i < adapter->num_xdp_queues; i++)
			adapter->xdp_ring[i]->count = new_tx_count;
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			adapter->rx_ring[i]->count = new_rx_count;
		adapter->tx_ring_count = new_tx_count;
		adapter->xdp_ring_count = new_tx_count;
		adapter->rx_ring_count = new_rx_count;
		जाओ clear_reset;
	पूर्ण

	/* allocate temporary buffer to store rings in */
	i = max_t(पूर्णांक, adapter->num_tx_queues + adapter->num_xdp_queues,
		  adapter->num_rx_queues);
	temp_ring = vदो_स्मृति(array_size(i, माप(काष्ठा ixgbe_ring)));

	अगर (!temp_ring) अणु
		err = -ENOMEM;
		जाओ clear_reset;
	पूर्ण

	ixgbe_करोwn(adapter);

	/*
	 * Setup new Tx resources and मुक्त the old Tx resources in that order.
	 * We can then assign the new resources to the rings via a स_नकल.
	 * The advantage to this approach is that we are guaranteed to still
	 * have resources even in the हाल of an allocation failure.
	 */
	अगर (new_tx_count != adapter->tx_ring_count) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			स_नकल(&temp_ring[i], adapter->tx_ring[i],
			       माप(काष्ठा ixgbe_ring));

			temp_ring[i].count = new_tx_count;
			err = ixgbe_setup_tx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					ixgbe_मुक्त_tx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण
		पूर्ण

		क्रम (j = 0; j < adapter->num_xdp_queues; j++, i++) अणु
			स_नकल(&temp_ring[i], adapter->xdp_ring[j],
			       माप(काष्ठा ixgbe_ring));

			temp_ring[i].count = new_tx_count;
			err = ixgbe_setup_tx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					ixgbe_मुक्त_tx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			ixgbe_मुक्त_tx_resources(adapter->tx_ring[i]);

			स_नकल(adapter->tx_ring[i], &temp_ring[i],
			       माप(काष्ठा ixgbe_ring));
		पूर्ण
		क्रम (j = 0; j < adapter->num_xdp_queues; j++, i++) अणु
			ixgbe_मुक्त_tx_resources(adapter->xdp_ring[j]);

			स_नकल(adapter->xdp_ring[j], &temp_ring[i],
			       माप(काष्ठा ixgbe_ring));
		पूर्ण

		adapter->tx_ring_count = new_tx_count;
	पूर्ण

	/* Repeat the process क्रम the Rx rings अगर needed */
	अगर (new_rx_count != adapter->rx_ring_count) अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			स_नकल(&temp_ring[i], adapter->rx_ring[i],
			       माप(काष्ठा ixgbe_ring));

			/* Clear copied XDP RX-queue info */
			स_रखो(&temp_ring[i].xdp_rxq, 0,
			       माप(temp_ring[i].xdp_rxq));

			temp_ring[i].count = new_rx_count;
			err = ixgbe_setup_rx_resources(adapter, &temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					ixgbe_मुक्त_rx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण

		पूर्ण

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			ixgbe_मुक्त_rx_resources(adapter->rx_ring[i]);

			स_नकल(adapter->rx_ring[i], &temp_ring[i],
			       माप(काष्ठा ixgbe_ring));
		पूर्ण

		adapter->rx_ring_count = new_rx_count;
	पूर्ण

err_setup:
	ixgbe_up(adapter);
	vमुक्त(temp_ring);
clear_reset:
	clear_bit(__IXGBE_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल पूर्णांक ixgbe_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस IXGBE_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस IXGBE_STATS_LEN;
	हाल ETH_SS_PRIV_FLAGS:
		वापस IXGBE_PRIV_FLAGS_STR_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम ixgbe_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा rtnl_link_stats64 temp;
	स्थिर काष्ठा rtnl_link_stats64 *net_stats;
	अचिन्हित पूर्णांक start;
	काष्ठा ixgbe_ring *ring;
	पूर्णांक i, j;
	अक्षर *p = शून्य;

	ixgbe_update_stats(adapter);
	net_stats = dev_get_stats(netdev, &temp);
	क्रम (i = 0; i < IXGBE_GLOBAL_STATS_LEN; i++) अणु
		चयन (ixgbe_gstrings_stats[i].type) अणु
		हाल NETDEV_STATS:
			p = (अक्षर *) net_stats +
					ixgbe_gstrings_stats[i].stat_offset;
			अवरोध;
		हाल IXGBE_STATS:
			p = (अक्षर *) adapter +
					ixgbe_gstrings_stats[i].stat_offset;
			अवरोध;
		शेष:
			data[i] = 0;
			जारी;
		पूर्ण

		data[i] = (ixgbe_gstrings_stats[i].माप_stat ==
			   माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
	क्रम (j = 0; j < netdev->num_tx_queues; j++) अणु
		ring = adapter->tx_ring[j];
		अगर (!ring) अणु
			data[i] = 0;
			data[i+1] = 0;
			i += 2;
			जारी;
		पूर्ण

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i]   = ring->stats.packets;
			data[i+1] = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	पूर्ण
	क्रम (j = 0; j < IXGBE_NUM_RX_QUEUES; j++) अणु
		ring = adapter->rx_ring[j];
		अगर (!ring) अणु
			data[i] = 0;
			data[i+1] = 0;
			i += 2;
			जारी;
		पूर्ण

		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->syncp);
			data[i]   = ring->stats.packets;
			data[i+1] = ring->stats.bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->syncp, start));
		i += 2;
	पूर्ण

	क्रम (j = 0; j < IXGBE_MAX_PACKET_BUFFERS; j++) अणु
		data[i++] = adapter->stats.pxontxc[j];
		data[i++] = adapter->stats.pxofftxc[j];
	पूर्ण
	क्रम (j = 0; j < IXGBE_MAX_PACKET_BUFFERS; j++) अणु
		data[i++] = adapter->stats.pxonrxc[j];
		data[i++] = adapter->stats.pxoffrxc[j];
	पूर्ण
पूर्ण

अटल व्योम ixgbe_get_strings(काष्ठा net_device *netdev, u32 stringset,
			      u8 *data)
अणु
	अचिन्हित पूर्णांक i;
	u8 *p = data;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		क्रम (i = 0; i < IXGBE_TEST_LEN; i++)
			ethtool_प्र_लिखो(&p, ixgbe_gstrings_test[i]);
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < IXGBE_GLOBAL_STATS_LEN; i++)
			ethtool_प्र_लिखो(&p,
					ixgbe_gstrings_stats[i].stat_string);
		क्रम (i = 0; i < netdev->num_tx_queues; i++) अणु
			ethtool_प्र_लिखो(&p, "tx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "tx_queue_%u_bytes", i);
		पूर्ण
		क्रम (i = 0; i < IXGBE_NUM_RX_QUEUES; i++) अणु
			ethtool_प्र_लिखो(&p, "rx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_bytes", i);
		पूर्ण
		क्रम (i = 0; i < IXGBE_MAX_PACKET_BUFFERS; i++) अणु
			ethtool_प्र_लिखो(&p, "tx_pb_%u_pxon", i);
			ethtool_प्र_लिखो(&p, "tx_pb_%u_pxoff", i);
		पूर्ण
		क्रम (i = 0; i < IXGBE_MAX_PACKET_BUFFERS; i++) अणु
			ethtool_प्र_लिखो(&p, "rx_pb_%u_pxon", i);
			ethtool_प्र_लिखो(&p, "rx_pb_%u_pxoff", i);
		पूर्ण
		/* BUG_ON(p - data != IXGBE_STATS_LEN * ETH_GSTRING_LEN); */
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(data, ixgbe_priv_flags_strings,
		       IXGBE_PRIV_FLAGS_STR_LEN * ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_link_test(काष्ठा ixgbe_adapter *adapter, u64 *data)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	bool link_up;
	u32 link_speed = 0;

	अगर (ixgbe_हटाओd(hw->hw_addr)) अणु
		*data = 1;
		वापस 1;
	पूर्ण
	*data = 0;

	hw->mac.ops.check_link(hw, &link_speed, &link_up, true);
	अगर (link_up)
		वापस *data;
	अन्यथा
		*data = 1;
	वापस *data;
पूर्ण

/* ethtool रेजिस्टर test data */
काष्ठा ixgbe_reg_test अणु
	u16 reg;
	u8  array_len;
	u8  test_type;
	u32 mask;
	u32 ग_लिखो;
पूर्ण;

/* In the hardware, रेजिस्टरs are laid out either singly, in arrays
 * spaced 0x40 bytes apart, or in contiguous tables.  We assume
 * most tests take place on arrays or single रेजिस्टरs (handled
 * as a single-element array) and special-हाल the tables.
 * Table tests are always pattern tests.
 *
 * We also make provision क्रम some required setup steps by specअगरying
 * रेजिस्टरs to be written without any पढ़ो-back testing.
 */

#घोषणा PATTERN_TEST	1
#घोषणा SET_READ_TEST	2
#घोषणा WRITE_NO_TEST	3
#घोषणा TABLE32_TEST	4
#घोषणा TABLE64_TEST_LO	5
#घोषणा TABLE64_TEST_HI	6

/* शेष 82599 रेजिस्टर test */
अटल स्थिर काष्ठा ixgbe_reg_test reg_test_82599[] = अणु
	अणु IXGBE_FCRTL_82599(0), 1, PATTERN_TEST, 0x8007FFF0, 0x8007FFF0 पूर्ण,
	अणु IXGBE_FCRTH_82599(0), 1, PATTERN_TEST, 0x8007FFF0, 0x8007FFF0 पूर्ण,
	अणु IXGBE_PFCTOP, 1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_VLNCTRL, 1, PATTERN_TEST, 0x00000000, 0x00000000 पूर्ण,
	अणु IXGBE_RDBAL(0), 4, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFF80 पूर्ण,
	अणु IXGBE_RDBAH(0), 4, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_RDLEN(0), 4, PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु IXGBE_RXDCTL(0), 4, WRITE_NO_TEST, 0, IXGBE_RXDCTL_ENABLE पूर्ण,
	अणु IXGBE_RDT(0), 4, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु IXGBE_RXDCTL(0), 4, WRITE_NO_TEST, 0, 0 पूर्ण,
	अणु IXGBE_FCRTH(0), 1, PATTERN_TEST, 0x8007FFF0, 0x8007FFF0 पूर्ण,
	अणु IXGBE_FCTTV(0), 1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_TDBAL(0), 4, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_TDBAH(0), 4, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_TDLEN(0), 4, PATTERN_TEST, 0x000FFF80, 0x000FFF80 पूर्ण,
	अणु IXGBE_RXCTRL, 1, SET_READ_TEST, 0x00000001, 0x00000001 पूर्ण,
	अणु IXGBE_RAL(0), 16, TABLE64_TEST_LO, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_RAL(0), 16, TABLE64_TEST_HI, 0x8001FFFF, 0x800CFFFF पूर्ण,
	अणु IXGBE_MTA(0), 128, TABLE32_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु .reg = 0 पूर्ण
पूर्ण;

/* शेष 82598 रेजिस्टर test */
अटल स्थिर काष्ठा ixgbe_reg_test reg_test_82598[] = अणु
	अणु IXGBE_FCRTL(0), 1, PATTERN_TEST, 0x8007FFF0, 0x8007FFF0 पूर्ण,
	अणु IXGBE_FCRTH(0), 1, PATTERN_TEST, 0x8007FFF0, 0x8007FFF0 पूर्ण,
	अणु IXGBE_PFCTOP, 1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_VLNCTRL, 1, PATTERN_TEST, 0x00000000, 0x00000000 पूर्ण,
	अणु IXGBE_RDBAL(0), 4, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_RDBAH(0), 4, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_RDLEN(0), 4, PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	/* Enable all four RX queues beक्रमe testing. */
	अणु IXGBE_RXDCTL(0), 4, WRITE_NO_TEST, 0, IXGBE_RXDCTL_ENABLE पूर्ण,
	/* RDH is पढ़ो-only क्रम 82598, only test RDT. */
	अणु IXGBE_RDT(0), 4, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु IXGBE_RXDCTL(0), 4, WRITE_NO_TEST, 0, 0 पूर्ण,
	अणु IXGBE_FCRTH(0), 1, PATTERN_TEST, 0x8007FFF0, 0x8007FFF0 पूर्ण,
	अणु IXGBE_FCTTV(0), 1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_TIPG, 1, PATTERN_TEST, 0x000000FF, 0x000000FF पूर्ण,
	अणु IXGBE_TDBAL(0), 4, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_TDBAH(0), 4, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_TDLEN(0), 4, PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु IXGBE_RXCTRL, 1, SET_READ_TEST, 0x00000003, 0x00000003 पूर्ण,
	अणु IXGBE_DTXCTL, 1, SET_READ_TEST, 0x00000005, 0x00000005 पूर्ण,
	अणु IXGBE_RAL(0), 16, TABLE64_TEST_LO, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु IXGBE_RAL(0), 16, TABLE64_TEST_HI, 0x800CFFFF, 0x800CFFFF पूर्ण,
	अणु IXGBE_MTA(0), 128, TABLE32_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु .reg = 0 पूर्ण
पूर्ण;

अटल bool reg_pattern_test(काष्ठा ixgbe_adapter *adapter, u64 *data, पूर्णांक reg,
			     u32 mask, u32 ग_लिखो)
अणु
	u32 pat, val, beक्रमe;
	अटल स्थिर u32 test_pattern[] = अणु
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFFपूर्ण;

	अगर (ixgbe_हटाओd(adapter->hw.hw_addr)) अणु
		*data = 1;
		वापस true;
	पूर्ण
	क्रम (pat = 0; pat < ARRAY_SIZE(test_pattern); pat++) अणु
		beक्रमe = ixgbe_पढ़ो_reg(&adapter->hw, reg);
		ixgbe_ग_लिखो_reg(&adapter->hw, reg, test_pattern[pat] & ग_लिखो);
		val = ixgbe_पढ़ो_reg(&adapter->hw, reg);
		अगर (val != (test_pattern[pat] & ग_लिखो & mask)) अणु
			e_err(drv, "pattern test reg %04X failed: got 0x%08X expected 0x%08X\n",
			      reg, val, (test_pattern[pat] & ग_लिखो & mask));
			*data = reg;
			ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
			वापस true;
		पूर्ण
		ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
	पूर्ण
	वापस false;
पूर्ण

अटल bool reg_set_and_check(काष्ठा ixgbe_adapter *adapter, u64 *data, पूर्णांक reg,
			      u32 mask, u32 ग_लिखो)
अणु
	u32 val, beक्रमe;

	अगर (ixgbe_हटाओd(adapter->hw.hw_addr)) अणु
		*data = 1;
		वापस true;
	पूर्ण
	beक्रमe = ixgbe_पढ़ो_reg(&adapter->hw, reg);
	ixgbe_ग_लिखो_reg(&adapter->hw, reg, ग_लिखो & mask);
	val = ixgbe_पढ़ो_reg(&adapter->hw, reg);
	अगर ((ग_लिखो & mask) != (val & mask)) अणु
		e_err(drv, "set/check reg %04X test failed: got 0x%08X expected 0x%08X\n",
		      reg, (val & mask), (ग_लिखो & mask));
		*data = reg;
		ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
		वापस true;
	पूर्ण
	ixgbe_ग_लिखो_reg(&adapter->hw, reg, beक्रमe);
	वापस false;
पूर्ण

अटल पूर्णांक ixgbe_reg_test(काष्ठा ixgbe_adapter *adapter, u64 *data)
अणु
	स्थिर काष्ठा ixgbe_reg_test *test;
	u32 value, beक्रमe, after;
	u32 i, toggle;

	अगर (ixgbe_हटाओd(adapter->hw.hw_addr)) अणु
		e_err(drv, "Adapter removed - register test blocked\n");
		*data = 1;
		वापस 1;
	पूर्ण
	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82598EB:
		toggle = 0x7FFFF3FF;
		test = reg_test_82598;
		अवरोध;
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		toggle = 0x7FFFF30F;
		test = reg_test_82599;
		अवरोध;
	शेष:
		*data = 1;
		वापस 1;
	पूर्ण

	/*
	 * Because the status रेजिस्टर is such a special हाल,
	 * we handle it separately from the rest of the रेजिस्टर
	 * tests.  Some bits are पढ़ो-only, some toggle, and some
	 * are ग_लिखोable on newer MACs.
	 */
	beक्रमe = ixgbe_पढ़ो_reg(&adapter->hw, IXGBE_STATUS);
	value = (ixgbe_पढ़ो_reg(&adapter->hw, IXGBE_STATUS) & toggle);
	ixgbe_ग_लिखो_reg(&adapter->hw, IXGBE_STATUS, toggle);
	after = ixgbe_पढ़ो_reg(&adapter->hw, IXGBE_STATUS) & toggle;
	अगर (value != after) अणु
		e_err(drv, "failed STATUS register test got: 0x%08X expected: 0x%08X\n",
		      after, value);
		*data = 1;
		वापस 1;
	पूर्ण
	/* restore previous status */
	ixgbe_ग_लिखो_reg(&adapter->hw, IXGBE_STATUS, beक्रमe);

	/*
	 * Perक्रमm the reमुख्यder of the रेजिस्टर test, looping through
	 * the test table until we either fail or reach the null entry.
	 */
	जबतक (test->reg) अणु
		क्रम (i = 0; i < test->array_len; i++) अणु
			bool b = false;

			चयन (test->test_type) अणु
			हाल PATTERN_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 0x40),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल SET_READ_TEST:
				b = reg_set_and_check(adapter, data,
						      test->reg + (i * 0x40),
						      test->mask,
						      test->ग_लिखो);
				अवरोध;
			हाल WRITE_NO_TEST:
				ixgbe_ग_लिखो_reg(&adapter->hw,
						test->reg + (i * 0x40),
						test->ग_लिखो);
				अवरोध;
			हाल TABLE32_TEST:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 4),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_LO:
				b = reg_pattern_test(adapter, data,
						     test->reg + (i * 8),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_HI:
				b = reg_pattern_test(adapter, data,
						     (test->reg + 4) + (i * 8),
						     test->mask,
						     test->ग_लिखो);
				अवरोध;
			पूर्ण
			अगर (b)
				वापस 1;
		पूर्ण
		test++;
	पूर्ण

	*data = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_eeprom_test(काष्ठा ixgbe_adapter *adapter, u64 *data)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	अगर (hw->eeprom.ops.validate_checksum(hw, शून्य))
		*data = 1;
	अन्यथा
		*data = 0;
	वापस *data;
पूर्ण

अटल irqवापस_t ixgbe_test_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = (काष्ठा net_device *) data;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	adapter->test_icr |= IXGBE_READ_REG(&adapter->hw, IXGBE_EICR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ixgbe_पूर्णांकr_test(काष्ठा ixgbe_adapter *adapter, u64 *data)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u32 mask, i = 0, shared_पूर्णांक = true;
	u32 irq = adapter->pdev->irq;

	*data = 0;

	/* Hook up test पूर्णांकerrupt handler just क्रम this test */
	अगर (adapter->msix_entries) अणु
		/* NOTE: we करोn't test MSI-X पूर्णांकerrupts here, yet */
		वापस 0;
	पूर्ण अन्यथा अगर (adapter->flags & IXGBE_FLAG_MSI_ENABLED) अणु
		shared_पूर्णांक = false;
		अगर (request_irq(irq, ixgbe_test_पूर्णांकr, 0, netdev->name,
				netdev)) अणु
			*data = 1;
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अगर (!request_irq(irq, ixgbe_test_पूर्णांकr, IRQF_PROBE_SHARED,
				netdev->name, netdev)) अणु
		shared_पूर्णांक = false;
	पूर्ण अन्यथा अगर (request_irq(irq, ixgbe_test_पूर्णांकr, IRQF_SHARED,
			       netdev->name, netdev)) अणु
		*data = 1;
		वापस -1;
	पूर्ण
	e_info(hw, "testing %s interrupt\n", shared_पूर्णांक ?
	       "shared" : "unshared");

	/* Disable all the पूर्णांकerrupts */
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC, 0xFFFFFFFF);
	IXGBE_WRITE_FLUSH(&adapter->hw);
	usleep_range(10000, 20000);

	/* Test each पूर्णांकerrupt */
	क्रम (; i < 10; i++) अणु
		/* Interrupt to test */
		mask = BIT(i);

		अगर (!shared_पूर्णांक) अणु
			/*
			 * Disable the पूर्णांकerrupts to be reported in
			 * the cause रेजिस्टर and then क्रमce the same
			 * पूर्णांकerrupt and see अगर one माला_लो posted.  If
			 * an पूर्णांकerrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC,
					~mask & 0x00007FFF);
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_EICS,
					~mask & 0x00007FFF);
			IXGBE_WRITE_FLUSH(&adapter->hw);
			usleep_range(10000, 20000);

			अगर (adapter->test_icr & mask) अणु
				*data = 3;
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * Enable the पूर्णांकerrupt to be reported in the cause
		 * रेजिस्टर and then क्रमce the same पूर्णांकerrupt and see
		 * अगर one माला_लो posted.  If an पूर्णांकerrupt was not posted
		 * to the bus, the test failed.
		 */
		adapter->test_icr = 0;
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMS, mask);
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_EICS, mask);
		IXGBE_WRITE_FLUSH(&adapter->hw);
		usleep_range(10000, 20000);

		अगर (!(adapter->test_icr & mask)) अणु
			*data = 4;
			अवरोध;
		पूर्ण

		अगर (!shared_पूर्णांक) अणु
			/*
			 * Disable the other पूर्णांकerrupts to be reported in
			 * the cause रेजिस्टर and then क्रमce the other
			 * पूर्णांकerrupts and see अगर any get posted.  If
			 * an पूर्णांकerrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC,
					~mask & 0x00007FFF);
			IXGBE_WRITE_REG(&adapter->hw, IXGBE_EICS,
					~mask & 0x00007FFF);
			IXGBE_WRITE_FLUSH(&adapter->hw);
			usleep_range(10000, 20000);

			अगर (adapter->test_icr) अणु
				*data = 5;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable all the पूर्णांकerrupts */
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_EIMC, 0xFFFFFFFF);
	IXGBE_WRITE_FLUSH(&adapter->hw);
	usleep_range(10000, 20000);

	/* Unhook test पूर्णांकerrupt handler */
	मुक्त_irq(irq, netdev);

	वापस *data;
पूर्ण

अटल व्योम ixgbe_मुक्त_desc_rings(काष्ठा ixgbe_adapter *adapter)
अणु
	/* Shut करोwn the DMA engines now so they can be reinitialized later,
	 * since the test rings and normally used rings should overlap on
	 * queue 0 we can just use the standard disable Rx/Tx calls and they
	 * will take care of disabling the test rings क्रम us.
	 */

	/* first Rx */
	ixgbe_disable_rx(adapter);

	/* now Tx */
	ixgbe_disable_tx(adapter);

	ixgbe_reset(adapter);

	ixgbe_मुक्त_tx_resources(&adapter->test_tx_ring);
	ixgbe_मुक्त_rx_resources(&adapter->test_rx_ring);
पूर्ण

अटल पूर्णांक ixgbe_setup_desc_rings(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_ring *tx_ring = &adapter->test_tx_ring;
	काष्ठा ixgbe_ring *rx_ring = &adapter->test_rx_ring;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 rctl, reg_data;
	पूर्णांक ret_val;
	पूर्णांक err;

	/* Setup Tx descriptor ring and Tx buffers */
	tx_ring->count = IXGBE_DEFAULT_TXD;
	tx_ring->queue_index = 0;
	tx_ring->dev = &adapter->pdev->dev;
	tx_ring->netdev = adapter->netdev;
	tx_ring->reg_idx = adapter->tx_ring[0]->reg_idx;

	err = ixgbe_setup_tx_resources(tx_ring);
	अगर (err)
		वापस 1;

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_82599EB:
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		reg_data = IXGBE_READ_REG(&adapter->hw, IXGBE_DMATXCTL);
		reg_data |= IXGBE_DMATXCTL_TE;
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_DMATXCTL, reg_data);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	ixgbe_configure_tx_ring(adapter, tx_ring);

	/* Setup Rx Descriptor ring and Rx buffers */
	rx_ring->count = IXGBE_DEFAULT_RXD;
	rx_ring->queue_index = 0;
	rx_ring->dev = &adapter->pdev->dev;
	rx_ring->netdev = adapter->netdev;
	rx_ring->reg_idx = adapter->rx_ring[0]->reg_idx;

	err = ixgbe_setup_rx_resources(adapter, rx_ring);
	अगर (err) अणु
		ret_val = 4;
		जाओ err_nomem;
	पूर्ण

	hw->mac.ops.disable_rx(hw);

	ixgbe_configure_rx_ring(adapter, rx_ring);

	rctl = IXGBE_READ_REG(&adapter->hw, IXGBE_RXCTRL);
	rctl |= IXGBE_RXCTRL_DMBYPS;
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_RXCTRL, rctl);

	hw->mac.ops.enable_rx(hw);

	वापस 0;

err_nomem:
	ixgbe_मुक्त_desc_rings(adapter);
	वापस ret_val;
पूर्ण

अटल पूर्णांक ixgbe_setup_loopback_test(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u32 reg_data;


	/* Setup MAC loopback */
	reg_data = IXGBE_READ_REG(hw, IXGBE_HLREG0);
	reg_data |= IXGBE_HLREG0_LPBK;
	IXGBE_WRITE_REG(hw, IXGBE_HLREG0, reg_data);

	reg_data = IXGBE_READ_REG(hw, IXGBE_FCTRL);
	reg_data |= IXGBE_FCTRL_BAM | IXGBE_FCTRL_SBP | IXGBE_FCTRL_MPE;
	IXGBE_WRITE_REG(hw, IXGBE_FCTRL, reg_data);

	/* X540 and X550 needs to set the MACC.FLU bit to क्रमce link up */
	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		reg_data = IXGBE_READ_REG(hw, IXGBE_MACC);
		reg_data |= IXGBE_MACC_FLU;
		IXGBE_WRITE_REG(hw, IXGBE_MACC, reg_data);
		अवरोध;
	शेष:
		अगर (hw->mac.orig_स्वतःc) अणु
			reg_data = hw->mac.orig_स्वतःc | IXGBE_AUTOC_FLU;
			IXGBE_WRITE_REG(hw, IXGBE_AUTOC, reg_data);
		पूर्ण अन्यथा अणु
			वापस 10;
		पूर्ण
	पूर्ण
	IXGBE_WRITE_FLUSH(hw);
	usleep_range(10000, 20000);

	/* Disable Atlas Tx lanes; re-enabled in reset path */
	अगर (hw->mac.type == ixgbe_mac_82598EB) अणु
		u8 atlas;

		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_REG_EN;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_LPBK, atlas);

		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_10G, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_10G_QL_ALL;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_10G, atlas);

		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_1G, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_1G_QL_ALL;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_1G, atlas);

		hw->mac.ops.पढ़ो_analog_reg8(hw, IXGBE_ATLAS_PDN_AN, &atlas);
		atlas |= IXGBE_ATLAS_PDN_TX_AN_QL_ALL;
		hw->mac.ops.ग_लिखो_analog_reg8(hw, IXGBE_ATLAS_PDN_AN, atlas);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ixgbe_loopback_cleanup(काष्ठा ixgbe_adapter *adapter)
अणु
	u32 reg_data;

	reg_data = IXGBE_READ_REG(&adapter->hw, IXGBE_HLREG0);
	reg_data &= ~IXGBE_HLREG0_LPBK;
	IXGBE_WRITE_REG(&adapter->hw, IXGBE_HLREG0, reg_data);
पूर्ण

अटल व्योम ixgbe_create_lbtest_frame(काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक frame_size)
अणु
	स_रखो(skb->data, 0xFF, frame_size);
	frame_size >>= 1;
	स_रखो(&skb->data[frame_size], 0xAA, frame_size / 2 - 1);
	skb->data[frame_size + 10] = 0xBE;
	skb->data[frame_size + 12] = 0xAF;
पूर्ण

अटल bool ixgbe_check_lbtest_frame(काष्ठा ixgbe_rx_buffer *rx_buffer,
				     अचिन्हित पूर्णांक frame_size)
अणु
	अचिन्हित अक्षर *data;
	bool match = true;

	frame_size >>= 1;

	data = kmap(rx_buffer->page) + rx_buffer->page_offset;

	अगर (data[3] != 0xFF ||
	    data[frame_size + 10] != 0xBE ||
	    data[frame_size + 12] != 0xAF)
		match = false;

	kunmap(rx_buffer->page);

	वापस match;
पूर्ण

अटल u16 ixgbe_clean_test_rings(काष्ठा ixgbe_ring *rx_ring,
				  काष्ठा ixgbe_ring *tx_ring,
				  अचिन्हित पूर्णांक size)
अणु
	जोड़ ixgbe_adv_rx_desc *rx_desc;
	u16 rx_ntc, tx_ntc, count = 0;

	/* initialize next to clean and descriptor values */
	rx_ntc = rx_ring->next_to_clean;
	tx_ntc = tx_ring->next_to_clean;
	rx_desc = IXGBE_RX_DESC(rx_ring, rx_ntc);

	जबतक (tx_ntc != tx_ring->next_to_use) अणु
		जोड़ ixgbe_adv_tx_desc *tx_desc;
		काष्ठा ixgbe_tx_buffer *tx_buffer;

		tx_desc = IXGBE_TX_DESC(tx_ring, tx_ntc);

		/* अगर DD is not set transmit has not completed */
		अगर (!(tx_desc->wb.status & cpu_to_le32(IXGBE_TXD_STAT_DD)))
			वापस count;

		/* unmap buffer on Tx side */
		tx_buffer = &tx_ring->tx_buffer_info[tx_ntc];

		/* Free all the Tx ring sk_buffs */
		dev_kमुक्त_skb_any(tx_buffer->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);
		dma_unmap_len_set(tx_buffer, len, 0);

		/* increment Tx next to clean counter */
		tx_ntc++;
		अगर (tx_ntc == tx_ring->count)
			tx_ntc = 0;
	पूर्ण

	जबतक (rx_desc->wb.upper.length) अणु
		काष्ठा ixgbe_rx_buffer *rx_buffer;

		/* check Rx buffer */
		rx_buffer = &rx_ring->rx_buffer_info[rx_ntc];

		/* sync Rx buffer क्रम CPU पढ़ो */
		dma_sync_single_क्रम_cpu(rx_ring->dev,
					rx_buffer->dma,
					ixgbe_rx_bufsz(rx_ring),
					DMA_FROM_DEVICE);

		/* verअगरy contents of skb */
		अगर (ixgbe_check_lbtest_frame(rx_buffer, size))
			count++;
		अन्यथा
			अवरोध;

		/* sync Rx buffer क्रम device ग_लिखो */
		dma_sync_single_क्रम_device(rx_ring->dev,
					   rx_buffer->dma,
					   ixgbe_rx_bufsz(rx_ring),
					   DMA_FROM_DEVICE);

		/* increment Rx next to clean counter */
		rx_ntc++;
		अगर (rx_ntc == rx_ring->count)
			rx_ntc = 0;

		/* fetch next descriptor */
		rx_desc = IXGBE_RX_DESC(rx_ring, rx_ntc);
	पूर्ण

	netdev_tx_reset_queue(txring_txq(tx_ring));

	/* re-map buffers to ring, store next to clean values */
	ixgbe_alloc_rx_buffers(rx_ring, count);
	rx_ring->next_to_clean = rx_ntc;
	tx_ring->next_to_clean = tx_ntc;

	वापस count;
पूर्ण

अटल पूर्णांक ixgbe_run_loopback_test(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_ring *tx_ring = &adapter->test_tx_ring;
	काष्ठा ixgbe_ring *rx_ring = &adapter->test_rx_ring;
	पूर्णांक i, j, lc, good_cnt, ret_val = 0;
	अचिन्हित पूर्णांक size = 1024;
	netdev_tx_t tx_ret_val;
	काष्ठा sk_buff *skb;
	u32 flags_orig = adapter->flags;

	/* DCB can modअगरy the frames on Tx */
	adapter->flags &= ~IXGBE_FLAG_DCB_ENABLED;

	/* allocate test skb */
	skb = alloc_skb(size, GFP_KERNEL);
	अगर (!skb)
		वापस 11;

	/* place data पूर्णांकo test skb */
	ixgbe_create_lbtest_frame(skb, size);
	skb_put(skb, size);

	/*
	 * Calculate the loop count based on the largest descriptor ring
	 * The idea is to wrap the largest ring a number of बार using 64
	 * send/receive pairs during each loop
	 */

	अगर (rx_ring->count <= tx_ring->count)
		lc = ((tx_ring->count / 64) * 2) + 1;
	अन्यथा
		lc = ((rx_ring->count / 64) * 2) + 1;

	क्रम (j = 0; j <= lc; j++) अणु
		/* reset count of good packets */
		good_cnt = 0;

		/* place 64 packets on the transmit queue*/
		क्रम (i = 0; i < 64; i++) अणु
			skb_get(skb);
			tx_ret_val = ixgbe_xmit_frame_ring(skb,
							   adapter,
							   tx_ring);
			अगर (tx_ret_val == NETDEV_TX_OK)
				good_cnt++;
		पूर्ण

		अगर (good_cnt != 64) अणु
			ret_val = 12;
			अवरोध;
		पूर्ण

		/* allow 200 milliseconds क्रम packets to go from Tx to Rx */
		msleep(200);

		good_cnt = ixgbe_clean_test_rings(rx_ring, tx_ring, size);
		अगर (good_cnt != 64) अणु
			ret_val = 13;
			अवरोध;
		पूर्ण
	पूर्ण

	/* मुक्त the original skb */
	kमुक्त_skb(skb);
	adapter->flags = flags_orig;

	वापस ret_val;
पूर्ण

अटल पूर्णांक ixgbe_loopback_test(काष्ठा ixgbe_adapter *adapter, u64 *data)
अणु
	*data = ixgbe_setup_desc_rings(adapter);
	अगर (*data)
		जाओ out;
	*data = ixgbe_setup_loopback_test(adapter);
	अगर (*data)
		जाओ err_loopback;
	*data = ixgbe_run_loopback_test(adapter);
	ixgbe_loopback_cleanup(adapter);

err_loopback:
	ixgbe_मुक्त_desc_rings(adapter);
out:
	वापस *data;
पूर्ण

अटल व्योम ixgbe_diag_test(काष्ठा net_device *netdev,
			    काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	bool अगर_running = netअगर_running(netdev);

	अगर (ixgbe_हटाओd(adapter->hw.hw_addr)) अणु
		e_err(hw, "Adapter removed - test blocked\n");
		data[0] = 1;
		data[1] = 1;
		data[2] = 1;
		data[3] = 1;
		data[4] = 1;
		eth_test->flags |= ETH_TEST_FL_FAILED;
		वापस;
	पूर्ण
	set_bit(__IXGBE_TESTING, &adapter->state);
	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		काष्ठा ixgbe_hw *hw = &adapter->hw;

		अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
			पूर्णांक i;
			क्रम (i = 0; i < adapter->num_vfs; i++) अणु
				अगर (adapter->vfinfo[i].clear_to_send) अणु
					netdev_warn(netdev, "offline diagnostic is not supported when VFs are present\n");
					data[0] = 1;
					data[1] = 1;
					data[2] = 1;
					data[3] = 1;
					data[4] = 1;
					eth_test->flags |= ETH_TEST_FL_FAILED;
					clear_bit(__IXGBE_TESTING,
						  &adapter->state);
					वापस;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Offline tests */
		e_info(hw, "offline testing starting\n");

		/* Link test perक्रमmed beक्रमe hardware reset so स्वतःneg करोesn't
		 * पूर्णांकerfere with test result
		 */
		अगर (ixgbe_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (अगर_running)
			/* indicate we're in test mode */
			ixgbe_बंद(netdev);
		अन्यथा
			ixgbe_reset(adapter);

		e_info(hw, "register testing starting\n");
		अगर (ixgbe_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		ixgbe_reset(adapter);
		e_info(hw, "eeprom testing starting\n");
		अगर (ixgbe_eeprom_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		ixgbe_reset(adapter);
		e_info(hw, "interrupt testing starting\n");
		अगर (ixgbe_पूर्णांकr_test(adapter, &data[2]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* If SRIOV or VMDq is enabled then skip MAC
		 * loopback diagnostic. */
		अगर (adapter->flags & (IXGBE_FLAG_SRIOV_ENABLED |
				      IXGBE_FLAG_VMDQ_ENABLED)) अणु
			e_info(hw, "Skip MAC loopback diagnostic in VT mode\n");
			data[3] = 0;
			जाओ skip_loopback;
		पूर्ण

		ixgbe_reset(adapter);
		e_info(hw, "loopback testing starting\n");
		अगर (ixgbe_loopback_test(adapter, &data[3]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

skip_loopback:
		ixgbe_reset(adapter);

		/* clear testing bit and वापस adapter to previous state */
		clear_bit(__IXGBE_TESTING, &adapter->state);
		अगर (अगर_running)
			ixgbe_खोलो(netdev);
		अन्यथा अगर (hw->mac.ops.disable_tx_laser)
			hw->mac.ops.disable_tx_laser(hw);
	पूर्ण अन्यथा अणु
		e_info(hw, "online testing starting\n");

		/* Online tests */
		अगर (ixgbe_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Offline tests aren't run; pass by शेष */
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;

		clear_bit(__IXGBE_TESTING, &adapter->state);
	पूर्ण
पूर्ण

अटल पूर्णांक ixgbe_wol_exclusion(काष्ठा ixgbe_adapter *adapter,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक retval = 0;

	/* WOL not supported क्रम all devices */
	अगर (!ixgbe_wol_supported(adapter, hw->device_id,
				 hw->subप्रणाली_device_id)) अणु
		retval = 1;
		wol->supported = 0;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम ixgbe_get_wol(काष्ठा net_device *netdev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_UCAST | WAKE_MCAST |
			 WAKE_BCAST | WAKE_MAGIC;
	wol->wolopts = 0;

	अगर (ixgbe_wol_exclusion(adapter, wol) ||
	    !device_can_wakeup(&adapter->pdev->dev))
		वापस;

	अगर (adapter->wol & IXGBE_WUFC_EX)
		wol->wolopts |= WAKE_UCAST;
	अगर (adapter->wol & IXGBE_WUFC_MC)
		wol->wolopts |= WAKE_MCAST;
	अगर (adapter->wol & IXGBE_WUFC_BC)
		wol->wolopts |= WAKE_BCAST;
	अगर (adapter->wol & IXGBE_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
पूर्ण

अटल पूर्णांक ixgbe_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_PHY | WAKE_ARP | WAKE_MAGICSECURE |
			    WAKE_FILTER))
		वापस -EOPNOTSUPP;

	अगर (ixgbe_wol_exclusion(adapter, wol))
		वापस wol->wolopts ? -EOPNOTSUPP : 0;

	adapter->wol = 0;

	अगर (wol->wolopts & WAKE_UCAST)
		adapter->wol |= IXGBE_WUFC_EX;
	अगर (wol->wolopts & WAKE_MCAST)
		adapter->wol |= IXGBE_WUFC_MC;
	अगर (wol->wolopts & WAKE_BCAST)
		adapter->wol |= IXGBE_WUFC_BC;
	अगर (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= IXGBE_WUFC_MAG;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		ixgbe_reinit_locked(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_set_phys_id(काष्ठा net_device *netdev,
			     क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (!hw->mac.ops.led_on || !hw->mac.ops.led_off)
		वापस -EOPNOTSUPP;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		adapter->led_reg = IXGBE_READ_REG(hw, IXGBE_LEDCTL);
		वापस 2;

	हाल ETHTOOL_ID_ON:
		hw->mac.ops.led_on(hw, hw->mac.led_link_act);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		hw->mac.ops.led_off(hw, hw->mac.led_link_act);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		/* Restore LED settings */
		IXGBE_WRITE_REG(&adapter->hw, IXGBE_LEDCTL, adapter->led_reg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	/* only valid अगर in स्थिरant ITR mode */
	अगर (adapter->rx_itr_setting <= 1)
		ec->rx_coalesce_usecs = adapter->rx_itr_setting;
	अन्यथा
		ec->rx_coalesce_usecs = adapter->rx_itr_setting >> 2;

	/* अगर in mixed tx/rx queues per vector mode, report only rx settings */
	अगर (adapter->q_vector[0]->tx.count && adapter->q_vector[0]->rx.count)
		वापस 0;

	/* only valid अगर in स्थिरant ITR mode */
	अगर (adapter->tx_itr_setting <= 1)
		ec->tx_coalesce_usecs = adapter->tx_itr_setting;
	अन्यथा
		ec->tx_coalesce_usecs = adapter->tx_itr_setting >> 2;

	वापस 0;
पूर्ण

/*
 * this function must be called beक्रमe setting the new value of
 * rx_itr_setting
 */
अटल bool ixgbe_update_rsc(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	/* nothing to करो अगर LRO or RSC are not enabled */
	अगर (!(adapter->flags2 & IXGBE_FLAG2_RSC_CAPABLE) ||
	    !(netdev->features & NETIF_F_LRO))
		वापस false;

	/* check the feature flag value and enable RSC अगर necessary */
	अगर (adapter->rx_itr_setting == 1 ||
	    adapter->rx_itr_setting > IXGBE_MIN_RSC_ITR) अणु
		अगर (!(adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED)) अणु
			adapter->flags2 |= IXGBE_FLAG2_RSC_ENABLED;
			e_info(probe, "rx-usecs value high enough to re-enable RSC\n");
			वापस true;
		पूर्ण
	/* अगर पूर्णांकerrupt rate is too high then disable RSC */
	पूर्ण अन्यथा अगर (adapter->flags2 & IXGBE_FLAG2_RSC_ENABLED) अणु
		adapter->flags2 &= ~IXGBE_FLAG2_RSC_ENABLED;
		e_info(probe, "rx-usecs set too low, disabling RSC\n");
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक ixgbe_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_q_vector *q_vector;
	पूर्णांक i;
	u16 tx_itr_param, rx_itr_param, tx_itr_prev;
	bool need_reset = false;

	अगर (adapter->q_vector[0]->tx.count && adapter->q_vector[0]->rx.count) अणु
		/* reject Tx specअगरic changes in हाल of mixed RxTx vectors */
		अगर (ec->tx_coalesce_usecs)
			वापस -EINVAL;
		tx_itr_prev = adapter->rx_itr_setting;
	पूर्ण अन्यथा अणु
		tx_itr_prev = adapter->tx_itr_setting;
	पूर्ण

	अगर ((ec->rx_coalesce_usecs > (IXGBE_MAX_EITR >> 2)) ||
	    (ec->tx_coalesce_usecs > (IXGBE_MAX_EITR >> 2)))
		वापस -EINVAL;

	अगर (ec->rx_coalesce_usecs > 1)
		adapter->rx_itr_setting = ec->rx_coalesce_usecs << 2;
	अन्यथा
		adapter->rx_itr_setting = ec->rx_coalesce_usecs;

	अगर (adapter->rx_itr_setting == 1)
		rx_itr_param = IXGBE_20K_ITR;
	अन्यथा
		rx_itr_param = adapter->rx_itr_setting;

	अगर (ec->tx_coalesce_usecs > 1)
		adapter->tx_itr_setting = ec->tx_coalesce_usecs << 2;
	अन्यथा
		adapter->tx_itr_setting = ec->tx_coalesce_usecs;

	अगर (adapter->tx_itr_setting == 1)
		tx_itr_param = IXGBE_12K_ITR;
	अन्यथा
		tx_itr_param = adapter->tx_itr_setting;

	/* mixed Rx/Tx */
	अगर (adapter->q_vector[0]->tx.count && adapter->q_vector[0]->rx.count)
		adapter->tx_itr_setting = adapter->rx_itr_setting;

	/* detect ITR changes that require update of TXDCTL.WTHRESH */
	अगर ((adapter->tx_itr_setting != 1) &&
	    (adapter->tx_itr_setting < IXGBE_100K_ITR)) अणु
		अगर ((tx_itr_prev == 1) ||
		    (tx_itr_prev >= IXGBE_100K_ITR))
			need_reset = true;
	पूर्ण अन्यथा अणु
		अगर ((tx_itr_prev != 1) &&
		    (tx_itr_prev < IXGBE_100K_ITR))
			need_reset = true;
	पूर्ण

	/* check the old value and enable RSC अगर necessary */
	need_reset |= ixgbe_update_rsc(adapter);

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		q_vector = adapter->q_vector[i];
		अगर (q_vector->tx.count && !q_vector->rx.count)
			/* tx only */
			q_vector->itr = tx_itr_param;
		अन्यथा
			/* rx only or mixed */
			q_vector->itr = rx_itr_param;
		ixgbe_ग_लिखो_eitr(q_vector);
	पूर्ण

	/*
	 * करो reset here at the end to make sure EITR==0 हाल is handled
	 * correctly w.r.t stopping tx, and changing TXDCTL.WTHRESH settings
	 * also locks in RSC enable/disable which requires reset
	 */
	अगर (need_reset)
		ixgbe_करो_reset(netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_ethtool_fdir_entry(काष्ठा ixgbe_adapter *adapter,
					काष्ठा ethtool_rxnfc *cmd)
अणु
	जोड़ ixgbe_atr_input *mask = &adapter->fdir_mask;
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा hlist_node *node2;
	काष्ठा ixgbe_fdir_filter *rule = शून्य;

	/* report total rule count */
	cmd->data = (1024 << adapter->fdir_pballoc) - 2;

	hlist_क्रम_each_entry_safe(rule, node2,
				  &adapter->fdir_filter_list, fdir_node) अणु
		अगर (fsp->location <= rule->sw_idx)
			अवरोध;
	पूर्ण

	अगर (!rule || fsp->location != rule->sw_idx)
		वापस -EINVAL;

	/* fill out the flow spec entry */

	/* set flow type field */
	चयन (rule->filter.क्रमmatted.flow_type) अणु
	हाल IXGBE_ATR_FLOW_TYPE_TCPV4:
		fsp->flow_type = TCP_V4_FLOW;
		अवरोध;
	हाल IXGBE_ATR_FLOW_TYPE_UDPV4:
		fsp->flow_type = UDP_V4_FLOW;
		अवरोध;
	हाल IXGBE_ATR_FLOW_TYPE_SCTPV4:
		fsp->flow_type = SCTP_V4_FLOW;
		अवरोध;
	हाल IXGBE_ATR_FLOW_TYPE_IPV4:
		fsp->flow_type = IP_USER_FLOW;
		fsp->h_u.usr_ip4_spec.ip_ver = ETH_RX_NFC_IP4;
		fsp->h_u.usr_ip4_spec.proto = 0;
		fsp->m_u.usr_ip4_spec.proto = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	fsp->h_u.tcp_ip4_spec.psrc = rule->filter.क्रमmatted.src_port;
	fsp->m_u.tcp_ip4_spec.psrc = mask->क्रमmatted.src_port;
	fsp->h_u.tcp_ip4_spec.pdst = rule->filter.क्रमmatted.dst_port;
	fsp->m_u.tcp_ip4_spec.pdst = mask->क्रमmatted.dst_port;
	fsp->h_u.tcp_ip4_spec.ip4src = rule->filter.क्रमmatted.src_ip[0];
	fsp->m_u.tcp_ip4_spec.ip4src = mask->क्रमmatted.src_ip[0];
	fsp->h_u.tcp_ip4_spec.ip4dst = rule->filter.क्रमmatted.dst_ip[0];
	fsp->m_u.tcp_ip4_spec.ip4dst = mask->क्रमmatted.dst_ip[0];
	fsp->h_ext.vlan_tci = rule->filter.क्रमmatted.vlan_id;
	fsp->m_ext.vlan_tci = mask->क्रमmatted.vlan_id;
	fsp->h_ext.vlan_etype = rule->filter.क्रमmatted.flex_bytes;
	fsp->m_ext.vlan_etype = mask->क्रमmatted.flex_bytes;
	fsp->h_ext.data[1] = htonl(rule->filter.क्रमmatted.vm_pool);
	fsp->m_ext.data[1] = htonl(mask->क्रमmatted.vm_pool);
	fsp->flow_type |= FLOW_EXT;

	/* record action */
	अगर (rule->action == IXGBE_Fसूची_DROP_QUEUE)
		fsp->ring_cookie = RX_CLS_FLOW_DISC;
	अन्यथा
		fsp->ring_cookie = rule->action;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_ethtool_fdir_all(काष्ठा ixgbe_adapter *adapter,
				      काष्ठा ethtool_rxnfc *cmd,
				      u32 *rule_locs)
अणु
	काष्ठा hlist_node *node2;
	काष्ठा ixgbe_fdir_filter *rule;
	पूर्णांक cnt = 0;

	/* report total rule count */
	cmd->data = (1024 << adapter->fdir_pballoc) - 2;

	hlist_क्रम_each_entry_safe(rule, node2,
				  &adapter->fdir_filter_list, fdir_node) अणु
		अगर (cnt == cmd->rule_cnt)
			वापस -EMSGSIZE;
		rule_locs[cnt] = rule->sw_idx;
		cnt++;
	पूर्ण

	cmd->rule_cnt = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_rss_hash_opts(काष्ठा ixgbe_adapter *adapter,
				   काष्ठा ethtool_rxnfc *cmd)
अणु
	cmd->data = 0;

	/* Report शेष options क्रम RSS on ixgbe */
	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल UDP_V4_FLOW:
		अगर (adapter->flags2 & IXGBE_FLAG2_RSS_FIELD_IPV4_UDP)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल IPV4_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	हाल TCP_V6_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल UDP_V6_FLOW:
		अगर (adapter->flags2 & IXGBE_FLAG2_RSS_FIELD_IPV6_UDP)
			cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल SCTP_V6_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
	हाल IPV6_FLOW:
		cmd->data |= RXH_IP_SRC | RXH_IP_DST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			   u32 *rule_locs)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_rx_queues;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = adapter->fdir_filter_count;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = ixgbe_get_ethtool_fdir_entry(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = ixgbe_get_ethtool_fdir_all(adapter, cmd, rule_locs);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		ret = ixgbe_get_rss_hash_opts(adapter, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ixgbe_update_ethtool_fdir_entry(काष्ठा ixgbe_adapter *adapter,
				    काष्ठा ixgbe_fdir_filter *input,
				    u16 sw_idx)
अणु
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा hlist_node *node2;
	काष्ठा ixgbe_fdir_filter *rule, *parent;
	पूर्णांक err = -EINVAL;

	parent = शून्य;
	rule = शून्य;

	hlist_क्रम_each_entry_safe(rule, node2,
				  &adapter->fdir_filter_list, fdir_node) अणु
		/* hash found, or no matching entry */
		अगर (rule->sw_idx >= sw_idx)
			अवरोध;
		parent = rule;
	पूर्ण

	/* अगर there is an old rule occupying our place हटाओ it */
	अगर (rule && (rule->sw_idx == sw_idx)) अणु
		अगर (!input || (rule->filter.क्रमmatted.bkt_hash !=
			       input->filter.क्रमmatted.bkt_hash)) अणु
			err = ixgbe_fdir_erase_perfect_filter_82599(hw,
								&rule->filter,
								sw_idx);
		पूर्ण

		hlist_del(&rule->fdir_node);
		kमुक्त(rule);
		adapter->fdir_filter_count--;
	पूर्ण

	/*
	 * If no input this was a delete, err should be 0 अगर a rule was
	 * successfully found and हटाओd from the list अन्यथा -EINVAL
	 */
	अगर (!input)
		वापस err;

	/* initialize node and set software index */
	INIT_HLIST_NODE(&input->fdir_node);

	/* add filter to the list */
	अगर (parent)
		hlist_add_behind(&input->fdir_node, &parent->fdir_node);
	अन्यथा
		hlist_add_head(&input->fdir_node,
			       &adapter->fdir_filter_list);

	/* update counts */
	adapter->fdir_filter_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_flowspec_to_flow_type(काष्ठा ethtool_rx_flow_spec *fsp,
				       u8 *flow_type)
अणु
	चयन (fsp->flow_type & ~FLOW_EXT) अणु
	हाल TCP_V4_FLOW:
		*flow_type = IXGBE_ATR_FLOW_TYPE_TCPV4;
		अवरोध;
	हाल UDP_V4_FLOW:
		*flow_type = IXGBE_ATR_FLOW_TYPE_UDPV4;
		अवरोध;
	हाल SCTP_V4_FLOW:
		*flow_type = IXGBE_ATR_FLOW_TYPE_SCTPV4;
		अवरोध;
	हाल IP_USER_FLOW:
		चयन (fsp->h_u.usr_ip4_spec.proto) अणु
		हाल IPPROTO_TCP:
			*flow_type = IXGBE_ATR_FLOW_TYPE_TCPV4;
			अवरोध;
		हाल IPPROTO_UDP:
			*flow_type = IXGBE_ATR_FLOW_TYPE_UDPV4;
			अवरोध;
		हाल IPPROTO_SCTP:
			*flow_type = IXGBE_ATR_FLOW_TYPE_SCTPV4;
			अवरोध;
		हाल 0:
			अगर (!fsp->m_u.usr_ip4_spec.proto) अणु
				*flow_type = IXGBE_ATR_FLOW_TYPE_IPV4;
				अवरोध;
			पूर्ण
			fallthrough;
		शेष:
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ixgbe_add_ethtool_fdir_entry(काष्ठा ixgbe_adapter *adapter,
					काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ixgbe_fdir_filter *input;
	जोड़ ixgbe_atr_input mask;
	u8 queue;
	पूर्णांक err;

	अगर (!(adapter->flags & IXGBE_FLAG_Fसूची_PERFECT_CAPABLE))
		वापस -EOPNOTSUPP;

	/* ring_cookie is a masked पूर्णांकo a set of queues and ixgbe pools or
	 * we use the drop index.
	 */
	अगर (fsp->ring_cookie == RX_CLS_FLOW_DISC) अणु
		queue = IXGBE_Fसूची_DROP_QUEUE;
	पूर्ण अन्यथा अणु
		u32 ring = ethtool_get_flow_spec_ring(fsp->ring_cookie);
		u8 vf = ethtool_get_flow_spec_ring_vf(fsp->ring_cookie);

		अगर (!vf && (ring >= adapter->num_rx_queues))
			वापस -EINVAL;
		अन्यथा अगर (vf &&
			 ((vf > adapter->num_vfs) ||
			   ring >= adapter->num_rx_queues_per_pool))
			वापस -EINVAL;

		/* Map the ring onto the असलolute queue index */
		अगर (!vf)
			queue = adapter->rx_ring[ring]->reg_idx;
		अन्यथा
			queue = ((vf - 1) *
				adapter->num_rx_queues_per_pool) + ring;
	पूर्ण

	/* Don't allow indexes to exist outside of available space */
	अगर (fsp->location >= ((1024 << adapter->fdir_pballoc) - 2)) अणु
		e_err(drv, "Location out of range\n");
		वापस -EINVAL;
	पूर्ण

	input = kzalloc(माप(*input), GFP_ATOMIC);
	अगर (!input)
		वापस -ENOMEM;

	स_रखो(&mask, 0, माप(जोड़ ixgbe_atr_input));

	/* set SW index */
	input->sw_idx = fsp->location;

	/* record flow type */
	अगर (!ixgbe_flowspec_to_flow_type(fsp,
					 &input->filter.क्रमmatted.flow_type)) अणु
		e_err(drv, "Unrecognized flow type\n");
		जाओ err_out;
	पूर्ण

	mask.क्रमmatted.flow_type = IXGBE_ATR_L4TYPE_IPV6_MASK |
				   IXGBE_ATR_L4TYPE_MASK;

	अगर (input->filter.क्रमmatted.flow_type == IXGBE_ATR_FLOW_TYPE_IPV4)
		mask.क्रमmatted.flow_type &= IXGBE_ATR_L4TYPE_IPV6_MASK;

	/* Copy input पूर्णांकo क्रमmatted काष्ठाures */
	input->filter.क्रमmatted.src_ip[0] = fsp->h_u.tcp_ip4_spec.ip4src;
	mask.क्रमmatted.src_ip[0] = fsp->m_u.tcp_ip4_spec.ip4src;
	input->filter.क्रमmatted.dst_ip[0] = fsp->h_u.tcp_ip4_spec.ip4dst;
	mask.क्रमmatted.dst_ip[0] = fsp->m_u.tcp_ip4_spec.ip4dst;
	input->filter.क्रमmatted.src_port = fsp->h_u.tcp_ip4_spec.psrc;
	mask.क्रमmatted.src_port = fsp->m_u.tcp_ip4_spec.psrc;
	input->filter.क्रमmatted.dst_port = fsp->h_u.tcp_ip4_spec.pdst;
	mask.क्रमmatted.dst_port = fsp->m_u.tcp_ip4_spec.pdst;

	अगर (fsp->flow_type & FLOW_EXT) अणु
		input->filter.क्रमmatted.vm_pool =
				(अचिन्हित अक्षर)ntohl(fsp->h_ext.data[1]);
		mask.क्रमmatted.vm_pool =
				(अचिन्हित अक्षर)ntohl(fsp->m_ext.data[1]);
		input->filter.क्रमmatted.vlan_id = fsp->h_ext.vlan_tci;
		mask.क्रमmatted.vlan_id = fsp->m_ext.vlan_tci;
		input->filter.क्रमmatted.flex_bytes =
						fsp->h_ext.vlan_etype;
		mask.क्रमmatted.flex_bytes = fsp->m_ext.vlan_etype;
	पूर्ण

	/* determine अगर we need to drop or route the packet */
	अगर (fsp->ring_cookie == RX_CLS_FLOW_DISC)
		input->action = IXGBE_Fसूची_DROP_QUEUE;
	अन्यथा
		input->action = fsp->ring_cookie;

	spin_lock(&adapter->fdir_perfect_lock);

	अगर (hlist_empty(&adapter->fdir_filter_list)) अणु
		/* save mask and program input mask पूर्णांकo HW */
		स_नकल(&adapter->fdir_mask, &mask, माप(mask));
		err = ixgbe_fdir_set_input_mask_82599(hw, &mask);
		अगर (err) अणु
			e_err(drv, "Error writing mask\n");
			जाओ err_out_w_lock;
		पूर्ण
	पूर्ण अन्यथा अगर (स_भेद(&adapter->fdir_mask, &mask, माप(mask))) अणु
		e_err(drv, "Only one mask supported per port\n");
		जाओ err_out_w_lock;
	पूर्ण

	/* apply mask and compute/store hash */
	ixgbe_atr_compute_perfect_hash_82599(&input->filter, &mask);

	/* program filters to filter memory */
	err = ixgbe_fdir_ग_लिखो_perfect_filter_82599(hw,
				&input->filter, input->sw_idx, queue);
	अगर (err)
		जाओ err_out_w_lock;

	ixgbe_update_ethtool_fdir_entry(adapter, input, input->sw_idx);

	spin_unlock(&adapter->fdir_perfect_lock);

	वापस err;
err_out_w_lock:
	spin_unlock(&adapter->fdir_perfect_lock);
err_out:
	kमुक्त(input);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ixgbe_del_ethtool_fdir_entry(काष्ठा ixgbe_adapter *adapter,
					काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	पूर्णांक err;

	spin_lock(&adapter->fdir_perfect_lock);
	err = ixgbe_update_ethtool_fdir_entry(adapter, शून्य, fsp->location);
	spin_unlock(&adapter->fdir_perfect_lock);

	वापस err;
पूर्ण

#घोषणा UDP_RSS_FLAGS (IXGBE_FLAG2_RSS_FIELD_IPV4_UDP | \
		       IXGBE_FLAG2_RSS_FIELD_IPV6_UDP)
अटल पूर्णांक ixgbe_set_rss_hash_opt(काष्ठा ixgbe_adapter *adapter,
				  काष्ठा ethtool_rxnfc *nfc)
अणु
	u32 flags2 = adapter->flags2;

	/*
	 * RSS करोes not support anything other than hashing
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
			flags2 &= ~IXGBE_FLAG2_RSS_FIELD_IPV4_UDP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			flags2 |= IXGBE_FLAG2_RSS_FIELD_IPV4_UDP;
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
			flags2 &= ~IXGBE_FLAG2_RSS_FIELD_IPV6_UDP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			flags2 |= IXGBE_FLAG2_RSS_FIELD_IPV6_UDP;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल AH_ESP_V4_FLOW:
	हाल AH_V4_FLOW:
	हाल ESP_V4_FLOW:
	हाल SCTP_V4_FLOW:
	हाल AH_ESP_V6_FLOW:
	हाल AH_V6_FLOW:
	हाल ESP_V6_FLOW:
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
	अगर (flags2 != adapter->flags2) अणु
		काष्ठा ixgbe_hw *hw = &adapter->hw;
		u32 mrqc;
		अचिन्हित पूर्णांक pf_pool = adapter->num_vfs;

		अगर ((hw->mac.type >= ixgbe_mac_X550) &&
		    (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
			mrqc = IXGBE_READ_REG(hw, IXGBE_PFVFMRQC(pf_pool));
		अन्यथा
			mrqc = IXGBE_READ_REG(hw, IXGBE_MRQC);

		अगर ((flags2 & UDP_RSS_FLAGS) &&
		    !(adapter->flags2 & UDP_RSS_FLAGS))
			e_warn(drv, "enabling UDP RSS: fragmented packets may arrive out of order to the stack above\n");

		adapter->flags2 = flags2;

		/* Perक्रमm hash on these packet types */
		mrqc |= IXGBE_MRQC_RSS_FIELD_IPV4
		      | IXGBE_MRQC_RSS_FIELD_IPV4_TCP
		      | IXGBE_MRQC_RSS_FIELD_IPV6
		      | IXGBE_MRQC_RSS_FIELD_IPV6_TCP;

		mrqc &= ~(IXGBE_MRQC_RSS_FIELD_IPV4_UDP |
			  IXGBE_MRQC_RSS_FIELD_IPV6_UDP);

		अगर (flags2 & IXGBE_FLAG2_RSS_FIELD_IPV4_UDP)
			mrqc |= IXGBE_MRQC_RSS_FIELD_IPV4_UDP;

		अगर (flags2 & IXGBE_FLAG2_RSS_FIELD_IPV6_UDP)
			mrqc |= IXGBE_MRQC_RSS_FIELD_IPV6_UDP;

		अगर ((hw->mac.type >= ixgbe_mac_X550) &&
		    (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
			IXGBE_WRITE_REG(hw, IXGBE_PFVFMRQC(pf_pool), mrqc);
		अन्यथा
			IXGBE_WRITE_REG(hw, IXGBE_MRQC, mrqc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		ret = ixgbe_add_ethtool_fdir_entry(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = ixgbe_del_ethtool_fdir_entry(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_SRXFH:
		ret = ixgbe_set_rss_hash_opt(adapter, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ixgbe_rss_indir_tbl_max(काष्ठा ixgbe_adapter *adapter)
अणु
	अगर (adapter->hw.mac.type < ixgbe_mac_X550)
		वापस 16;
	अन्यथा
		वापस 64;
पूर्ण

अटल u32 ixgbe_get_rxfh_key_size(काष्ठा net_device *netdev)
अणु
	वापस IXGBE_RSS_KEY_SIZE;
पूर्ण

अटल u32 ixgbe_rss_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	वापस ixgbe_rss_indir_tbl_entries(adapter);
पूर्ण

अटल व्योम ixgbe_get_reta(काष्ठा ixgbe_adapter *adapter, u32 *indir)
अणु
	पूर्णांक i, reta_size = ixgbe_rss_indir_tbl_entries(adapter);
	u16 rss_m = adapter->ring_feature[RING_F_RSS].mask;

	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		rss_m = adapter->ring_feature[RING_F_RSS].indices - 1;

	क्रम (i = 0; i < reta_size; i++)
		indir[i] = adapter->rss_indir_tbl[i] & rss_m;
पूर्ण

अटल पूर्णांक ixgbe_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			  u8 *hfunc)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (indir)
		ixgbe_get_reta(adapter, indir);

	अगर (key)
		स_नकल(key, adapter->rss_key, ixgbe_get_rxfh_key_size(netdev));

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			  स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;
	u32 reta_entries = ixgbe_rss_indir_tbl_entries(adapter);

	अगर (hfunc)
		वापस -EINVAL;

	/* Fill out the redirection table */
	अगर (indir) अणु
		पूर्णांक max_queues = min_t(पूर्णांक, adapter->num_rx_queues,
				       ixgbe_rss_indir_tbl_max(adapter));

		/*Allow at least 2 queues w/ SR-IOV.*/
		अगर ((adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) &&
		    (max_queues < 2))
			max_queues = 2;

		/* Verअगरy user input. */
		क्रम (i = 0; i < reta_entries; i++)
			अगर (indir[i] >= max_queues)
				वापस -EINVAL;

		क्रम (i = 0; i < reta_entries; i++)
			adapter->rss_indir_tbl[i] = indir[i];

		ixgbe_store_reta(adapter);
	पूर्ण

	/* Fill out the rss hash key */
	अगर (key) अणु
		स_नकल(adapter->rss_key, key, ixgbe_get_rxfh_key_size(netdev));
		ixgbe_store_key(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_ts_info(काष्ठा net_device *dev,
			     काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);

	/* we always support बारtamping disabled */
	info->rx_filters = BIT(HWTSTAMP_FILTER_NONE);

	चयन (adapter->hw.mac.type) अणु
	हाल ixgbe_mac_X550:
	हाल ixgbe_mac_X550EM_x:
	हाल ixgbe_mac_x550em_a:
		info->rx_filters |= BIT(HWTSTAMP_FILTER_ALL);
		अवरोध;
	हाल ixgbe_mac_X540:
	हाल ixgbe_mac_82599EB:
		info->rx_filters |=
			BIT(HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			BIT(HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			BIT(HWTSTAMP_FILTER_PTP_V2_EVENT);
		अवरोध;
	शेष:
		वापस ethtool_op_get_ts_info(dev, info);
	पूर्ण

	info->so_बारtamping =
		SOF_TIMESTAMPING_TX_SOFTWARE |
		SOF_TIMESTAMPING_RX_SOFTWARE |
		SOF_TIMESTAMPING_SOFTWARE |
		SOF_TIMESTAMPING_TX_HARDWARE |
		SOF_TIMESTAMPING_RX_HARDWARE |
		SOF_TIMESTAMPING_RAW_HARDWARE;

	अगर (adapter->ptp_घड़ी)
		info->phc_index = ptp_घड़ी_index(adapter->ptp_घड़ी);
	अन्यथा
		info->phc_index = -1;

	info->tx_types =
		BIT(HWTSTAMP_TX_OFF) |
		BIT(HWTSTAMP_TX_ON);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक ixgbe_max_channels(काष्ठा ixgbe_adapter *adapter)
अणु
	अचिन्हित पूर्णांक max_combined;
	u8 tcs = adapter->hw_tcs;

	अगर (!(adapter->flags & IXGBE_FLAG_MSIX_ENABLED)) अणु
		/* We only support one q_vector without MSI-X */
		max_combined = 1;
	पूर्ण अन्यथा अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
		/* Limit value based on the queue mask */
		max_combined = adapter->ring_feature[RING_F_RSS].mask + 1;
	पूर्ण अन्यथा अगर (tcs > 1) अणु
		/* For DCB report channels per traffic class */
		अगर (adapter->hw.mac.type == ixgbe_mac_82598EB) अणु
			/* 8 TC w/ 4 queues per TC */
			max_combined = 4;
		पूर्ण अन्यथा अगर (tcs > 4) अणु
			/* 8 TC w/ 8 queues per TC */
			max_combined = 8;
		पूर्ण अन्यथा अणु
			/* 4 TC w/ 16 queues per TC */
			max_combined = 16;
		पूर्ण
	पूर्ण अन्यथा अगर (adapter->atr_sample_rate) अणु
		/* support up to 64 queues with ATR */
		max_combined = IXGBE_MAX_Fसूची_INDICES;
	पूर्ण अन्यथा अणु
		/* support up to 16 queues with RSS */
		max_combined = ixgbe_max_rss_indices(adapter);
	पूर्ण

	वापस max_combined;
पूर्ण

अटल व्योम ixgbe_get_channels(काष्ठा net_device *dev,
			       काष्ठा ethtool_channels *ch)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);

	/* report maximum channels */
	ch->max_combined = ixgbe_max_channels(adapter);

	/* report info क्रम other vector */
	अगर (adapter->flags & IXGBE_FLAG_MSIX_ENABLED) अणु
		ch->max_other = NON_Q_VECTORS;
		ch->other_count = NON_Q_VECTORS;
	पूर्ण

	/* record RSS queues */
	ch->combined_count = adapter->ring_feature[RING_F_RSS].indices;

	/* nothing अन्यथा to report अगर RSS is disabled */
	अगर (ch->combined_count == 1)
		वापस;

	/* we करो not support ATR queueing अगर SR-IOV is enabled */
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		वापस;

	/* same thing goes क्रम being DCB enabled */
	अगर (adapter->hw_tcs > 1)
		वापस;

	/* अगर ATR is disabled we can निकास */
	अगर (!adapter->atr_sample_rate)
		वापस;

	/* report flow director queues as maximum channels */
	ch->combined_count = adapter->ring_feature[RING_F_Fसूची].indices;
पूर्ण

अटल पूर्णांक ixgbe_set_channels(काष्ठा net_device *dev,
			      काष्ठा ethtool_channels *ch)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	अचिन्हित पूर्णांक count = ch->combined_count;
	u8 max_rss_indices = ixgbe_max_rss_indices(adapter);

	/* verअगरy they are not requesting separate vectors */
	अगर (!count || ch->rx_count || ch->tx_count)
		वापस -EINVAL;

	/* verअगरy other_count has not changed */
	अगर (ch->other_count != NON_Q_VECTORS)
		वापस -EINVAL;

	/* verअगरy the number of channels करोes not exceed hardware limits */
	अगर (count > ixgbe_max_channels(adapter))
		वापस -EINVAL;

	/* update feature limits from largest to smallest supported values */
	adapter->ring_feature[RING_F_Fसूची].limit = count;

	/* cap RSS limit */
	अगर (count > max_rss_indices)
		count = max_rss_indices;
	adapter->ring_feature[RING_F_RSS].limit = count;

#अगर_घोषित IXGBE_FCOE
	/* cap FCoE limit at 8 */
	अगर (count > IXGBE_FCRETA_SIZE)
		count = IXGBE_FCRETA_SIZE;
	adapter->ring_feature[RING_F_FCOE].limit = count;

#पूर्ण_अगर
	/* use setup TC to update any traffic class queue mapping */
	वापस ixgbe_setup_tc(dev, adapter->hw_tcs);
पूर्ण

अटल पूर्णांक ixgbe_get_module_info(काष्ठा net_device *dev,
				       काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	s32 status;
	u8 sff8472_rev, addr_mode;
	bool page_swap = false;

	अगर (hw->phy.type == ixgbe_phy_fw)
		वापस -ENXIO;

	/* Check whether we support SFF-8472 or not */
	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					     IXGBE_SFF_SFF_8472_COMP,
					     &sff8472_rev);
	अगर (status)
		वापस -EIO;

	/* addressing mode is not supported */
	status = hw->phy.ops.पढ़ो_i2c_eeprom(hw,
					     IXGBE_SFF_SFF_8472_SWAP,
					     &addr_mode);
	अगर (status)
		वापस -EIO;

	अगर (addr_mode & IXGBE_SFF_ADDRESSING_MODE) अणु
		e_err(drv, "Address change required to access page 0xA2, but not supported. Please report the module type to the driver maintainers.\n");
		page_swap = true;
	पूर्ण

	अगर (sff8472_rev == IXGBE_SFF_SFF_8472_UNSUP || page_swap ||
	    !(addr_mode & IXGBE_SFF_DDM_IMPLEMENTED)) अणु
		/* We have a SFP, but it करोes not support SFF-8472 */
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	पूर्ण अन्यथा अणु
		/* We have a SFP which supports a revision of SFF-8472. */
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_module_eeprom(काष्ठा net_device *dev,
					 काष्ठा ethtool_eeprom *ee,
					 u8 *data)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	s32 status = IXGBE_ERR_PHY_ADDR_INVALID;
	u8 databyte = 0xFF;
	पूर्णांक i = 0;

	अगर (ee->len == 0)
		वापस -EINVAL;

	अगर (hw->phy.type == ixgbe_phy_fw)
		वापस -ENXIO;

	क्रम (i = ee->offset; i < ee->offset + ee->len; i++) अणु
		/* I2C पढ़ोs can take दीर्घ समय */
		अगर (test_bit(__IXGBE_IN_SFP_INIT, &adapter->state))
			वापस -EBUSY;

		अगर (i < ETH_MODULE_SFF_8079_LEN)
			status = hw->phy.ops.पढ़ो_i2c_eeprom(hw, i, &databyte);
		अन्यथा
			status = hw->phy.ops.पढ़ो_i2c_sff8472(hw, i, &databyte);

		अगर (status)
			वापस -EIO;

		data[i - ee->offset] = databyte;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा अणु
	ixgbe_link_speed mac_speed;
	u32 supported;
पूर्ण ixgbe_ls_map[] = अणु
	अणु IXGBE_LINK_SPEED_10_FULL, SUPPORTED_10baseT_Full पूर्ण,
	अणु IXGBE_LINK_SPEED_100_FULL, SUPPORTED_100baseT_Full पूर्ण,
	अणु IXGBE_LINK_SPEED_1GB_FULL, SUPPORTED_1000baseT_Full पूर्ण,
	अणु IXGBE_LINK_SPEED_2_5GB_FULL, SUPPORTED_2500baseX_Full पूर्ण,
	अणु IXGBE_LINK_SPEED_10GB_FULL, SUPPORTED_10000baseT_Full पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u32 lp_advertised;
	u32 mac_speed;
पूर्ण ixgbe_lp_map[] = अणु
	अणु FW_PHY_ACT_UD_2_100M_TX_EEE, SUPPORTED_100baseT_Full पूर्ण,
	अणु FW_PHY_ACT_UD_2_1G_T_EEE, SUPPORTED_1000baseT_Full पूर्ण,
	अणु FW_PHY_ACT_UD_2_10G_T_EEE, SUPPORTED_10000baseT_Full पूर्ण,
	अणु FW_PHY_ACT_UD_2_1G_KX_EEE, SUPPORTED_1000baseKX_Full पूर्ण,
	अणु FW_PHY_ACT_UD_2_10G_KX4_EEE, SUPPORTED_10000baseKX4_Full पूर्ण,
	अणु FW_PHY_ACT_UD_2_10G_KR_EEE, SUPPORTED_10000baseKR_Fullपूर्ण,
पूर्ण;

अटल पूर्णांक
ixgbe_get_eee_fw(काष्ठा ixgbe_adapter *adapter, काष्ठा ethtool_eee *edata)
अणु
	u32 info[FW_PHY_ACT_DATA_COUNT] = अणु 0 पूर्ण;
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	s32 rc;
	u16 i;

	rc = ixgbe_fw_phy_activity(hw, FW_PHY_ACT_UD_2, &info);
	अगर (rc)
		वापस rc;

	edata->lp_advertised = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ixgbe_lp_map); ++i) अणु
		अगर (info[0] & ixgbe_lp_map[i].lp_advertised)
			edata->lp_advertised |= ixgbe_lp_map[i].mac_speed;
	पूर्ण

	edata->supported = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ixgbe_ls_map); ++i) अणु
		अगर (hw->phy.eee_speeds_supported & ixgbe_ls_map[i].mac_speed)
			edata->supported |= ixgbe_ls_map[i].supported;
	पूर्ण

	edata->advertised = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ixgbe_ls_map); ++i) अणु
		अगर (hw->phy.eee_speeds_advertised & ixgbe_ls_map[i].mac_speed)
			edata->advertised |= ixgbe_ls_map[i].supported;
	पूर्ण

	edata->eee_enabled = !!edata->advertised;
	edata->tx_lpi_enabled = edata->eee_enabled;
	अगर (edata->advertised & edata->lp_advertised)
		edata->eee_active = true;

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_get_eee(काष्ठा net_device *netdev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;

	अगर (!(adapter->flags2 & IXGBE_FLAG2_EEE_CAPABLE))
		वापस -EOPNOTSUPP;

	अगर (hw->phy.eee_speeds_supported && hw->phy.type == ixgbe_phy_fw)
		वापस ixgbe_get_eee_fw(adapter, edata);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक ixgbe_set_eee(काष्ठा net_device *netdev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	काष्ठा ethtool_eee eee_data;
	s32 ret_val;

	अगर (!(adapter->flags2 & IXGBE_FLAG2_EEE_CAPABLE))
		वापस -EOPNOTSUPP;

	स_रखो(&eee_data, 0, माप(काष्ठा ethtool_eee));

	ret_val = ixgbe_get_eee(netdev, &eee_data);
	अगर (ret_val)
		वापस ret_val;

	अगर (eee_data.eee_enabled && !edata->eee_enabled) अणु
		अगर (eee_data.tx_lpi_enabled != edata->tx_lpi_enabled) अणु
			e_err(drv, "Setting EEE tx-lpi is not supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (eee_data.tx_lpi_समयr != edata->tx_lpi_समयr) अणु
			e_err(drv,
			      "Setting EEE Tx LPI timer is not supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (eee_data.advertised != edata->advertised) अणु
			e_err(drv,
			      "Setting EEE advertised speeds is not supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (eee_data.eee_enabled != edata->eee_enabled) अणु
		अगर (edata->eee_enabled) अणु
			adapter->flags2 |= IXGBE_FLAG2_EEE_ENABLED;
			hw->phy.eee_speeds_advertised =
						   hw->phy.eee_speeds_supported;
		पूर्ण अन्यथा अणु
			adapter->flags2 &= ~IXGBE_FLAG2_EEE_ENABLED;
			hw->phy.eee_speeds_advertised = 0;
		पूर्ण

		/* reset link */
		अगर (netअगर_running(netdev))
			ixgbe_reinit_locked(adapter);
		अन्यथा
			ixgbe_reset(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 ixgbe_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	u32 priv_flags = 0;

	अगर (adapter->flags2 & IXGBE_FLAG2_RX_LEGACY)
		priv_flags |= IXGBE_PRIV_FLAGS_LEGACY_RX;

	अगर (adapter->flags2 & IXGBE_FLAG2_VF_IPSEC_ENABLED)
		priv_flags |= IXGBE_PRIV_FLAGS_VF_IPSEC_EN;

	वापस priv_flags;
पूर्ण

अटल पूर्णांक ixgbe_set_priv_flags(काष्ठा net_device *netdev, u32 priv_flags)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक flags2 = adapter->flags2;

	flags2 &= ~IXGBE_FLAG2_RX_LEGACY;
	अगर (priv_flags & IXGBE_PRIV_FLAGS_LEGACY_RX)
		flags2 |= IXGBE_FLAG2_RX_LEGACY;

	flags2 &= ~IXGBE_FLAG2_VF_IPSEC_ENABLED;
	अगर (priv_flags & IXGBE_PRIV_FLAGS_VF_IPSEC_EN)
		flags2 |= IXGBE_FLAG2_VF_IPSEC_ENABLED;

	अगर (flags2 != adapter->flags2) अणु
		adapter->flags2 = flags2;

		/* reset पूर्णांकerface to repopulate queues */
		अगर (netअगर_running(netdev))
			ixgbe_reinit_locked(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ixgbe_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo            = ixgbe_get_drvinfo,
	.get_regs_len           = ixgbe_get_regs_len,
	.get_regs               = ixgbe_get_regs,
	.get_wol                = ixgbe_get_wol,
	.set_wol                = ixgbe_set_wol,
	.nway_reset             = ixgbe_nway_reset,
	.get_link               = ethtool_op_get_link,
	.get_eeprom_len         = ixgbe_get_eeprom_len,
	.get_eeprom             = ixgbe_get_eeprom,
	.set_eeprom             = ixgbe_set_eeprom,
	.get_ringparam          = ixgbe_get_ringparam,
	.set_ringparam          = ixgbe_set_ringparam,
	.get_छोड़ो_stats	= ixgbe_get_छोड़ो_stats,
	.get_छोड़ोparam         = ixgbe_get_छोड़ोparam,
	.set_छोड़ोparam         = ixgbe_set_छोड़ोparam,
	.get_msglevel           = ixgbe_get_msglevel,
	.set_msglevel           = ixgbe_set_msglevel,
	.self_test              = ixgbe_diag_test,
	.get_strings            = ixgbe_get_strings,
	.set_phys_id            = ixgbe_set_phys_id,
	.get_sset_count         = ixgbe_get_sset_count,
	.get_ethtool_stats      = ixgbe_get_ethtool_stats,
	.get_coalesce           = ixgbe_get_coalesce,
	.set_coalesce           = ixgbe_set_coalesce,
	.get_rxnfc		= ixgbe_get_rxnfc,
	.set_rxnfc		= ixgbe_set_rxnfc,
	.get_rxfh_indir_size	= ixgbe_rss_indir_size,
	.get_rxfh_key_size	= ixgbe_get_rxfh_key_size,
	.get_rxfh		= ixgbe_get_rxfh,
	.set_rxfh		= ixgbe_set_rxfh,
	.get_eee		= ixgbe_get_eee,
	.set_eee		= ixgbe_set_eee,
	.get_channels		= ixgbe_get_channels,
	.set_channels		= ixgbe_set_channels,
	.get_priv_flags		= ixgbe_get_priv_flags,
	.set_priv_flags		= ixgbe_set_priv_flags,
	.get_ts_info		= ixgbe_get_ts_info,
	.get_module_info	= ixgbe_get_module_info,
	.get_module_eeprom	= ixgbe_get_module_eeprom,
	.get_link_ksettings     = ixgbe_get_link_ksettings,
	.set_link_ksettings     = ixgbe_set_link_ksettings,
पूर्ण;

व्योम ixgbe_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ixgbe_ethtool_ops;
पूर्ण
