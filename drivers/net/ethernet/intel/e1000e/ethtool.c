<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

/* ethtool support क्रम e1000 */

#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "e1000.h"

क्रमागत अणु NETDEV_STATS, E1000_STATS पूर्ण;

काष्ठा e1000_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक type;
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

अटल स्थिर अक्षर e1000e_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
#घोषणा E1000E_PRIV_FLAGS_S0IX_ENABLED	BIT(0)
	"s0ix-enabled",
पूर्ण;

#घोषणा E1000E_PRIV_FLAGS_STR_LEN ARRAY_SIZE(e1000e_priv_flags_strings)

#घोषणा E1000_STAT(str, m) अणु \
		.stat_string = str, \
		.type = E1000_STATS, \
		.माप_stat = माप(((काष्ठा e1000_adapter *)0)->m), \
		.stat_offset = दुरत्व(काष्ठा e1000_adapter, m) पूर्ण
#घोषणा E1000_NETDEV_STAT(str, m) अणु \
		.stat_string = str, \
		.type = NETDEV_STATS, \
		.माप_stat = माप(((काष्ठा rtnl_link_stats64 *)0)->m), \
		.stat_offset = दुरत्व(काष्ठा rtnl_link_stats64, m) पूर्ण

अटल स्थिर काष्ठा e1000_stats e1000_gstrings_stats[] = अणु
	E1000_STAT("rx_packets", stats.gprc),
	E1000_STAT("tx_packets", stats.gptc),
	E1000_STAT("rx_bytes", stats.gorc),
	E1000_STAT("tx_bytes", stats.gotc),
	E1000_STAT("rx_broadcast", stats.bprc),
	E1000_STAT("tx_broadcast", stats.bptc),
	E1000_STAT("rx_multicast", stats.mprc),
	E1000_STAT("tx_multicast", stats.mptc),
	E1000_NETDEV_STAT("rx_errors", rx_errors),
	E1000_NETDEV_STAT("tx_errors", tx_errors),
	E1000_NETDEV_STAT("tx_dropped", tx_dropped),
	E1000_STAT("multicast", stats.mprc),
	E1000_STAT("collisions", stats.colc),
	E1000_NETDEV_STAT("rx_length_errors", rx_length_errors),
	E1000_NETDEV_STAT("rx_over_errors", rx_over_errors),
	E1000_STAT("rx_crc_errors", stats.crcerrs),
	E1000_NETDEV_STAT("rx_frame_errors", rx_frame_errors),
	E1000_STAT("rx_no_buffer_count", stats.rnbc),
	E1000_STAT("rx_missed_errors", stats.mpc),
	E1000_STAT("tx_aborted_errors", stats.ecol),
	E1000_STAT("tx_carrier_errors", stats.tncrs),
	E1000_NETDEV_STAT("tx_fifo_errors", tx_fअगरo_errors),
	E1000_NETDEV_STAT("tx_heartbeat_errors", tx_heartbeat_errors),
	E1000_STAT("tx_window_errors", stats.latecol),
	E1000_STAT("tx_abort_late_coll", stats.latecol),
	E1000_STAT("tx_deferred_ok", stats.dc),
	E1000_STAT("tx_single_coll_ok", stats.scc),
	E1000_STAT("tx_multi_coll_ok", stats.mcc),
	E1000_STAT("tx_timeout_count", tx_समयout_count),
	E1000_STAT("tx_restart_queue", restart_queue),
	E1000_STAT("rx_long_length_errors", stats.roc),
	E1000_STAT("rx_short_length_errors", stats.ruc),
	E1000_STAT("rx_align_errors", stats.algnerrc),
	E1000_STAT("tx_tcp_seg_good", stats.tsctc),
	E1000_STAT("tx_tcp_seg_failed", stats.tsctfc),
	E1000_STAT("rx_flow_control_xon", stats.xonrxc),
	E1000_STAT("rx_flow_control_xoff", stats.xoffrxc),
	E1000_STAT("tx_flow_control_xon", stats.xontxc),
	E1000_STAT("tx_flow_control_xoff", stats.xofftxc),
	E1000_STAT("rx_csum_offload_good", hw_csum_good),
	E1000_STAT("rx_csum_offload_errors", hw_csum_err),
	E1000_STAT("rx_header_split", rx_hdr_split),
	E1000_STAT("alloc_rx_buff_failed", alloc_rx_buff_failed),
	E1000_STAT("tx_smbus", stats.mgptc),
	E1000_STAT("rx_smbus", stats.mgprc),
	E1000_STAT("dropped_smbus", stats.mgpdc),
	E1000_STAT("rx_dma_failed", rx_dma_failed),
	E1000_STAT("tx_dma_failed", tx_dma_failed),
	E1000_STAT("rx_hwtstamp_cleared", rx_hwtstamp_cleared),
	E1000_STAT("uncorr_ecc_errors", uncorr_errors),
	E1000_STAT("corr_ecc_errors", corr_errors),
	E1000_STAT("tx_hwtstamp_timeouts", tx_hwtstamp_समयouts),
	E1000_STAT("tx_hwtstamp_skipped", tx_hwtstamp_skipped),
पूर्ण;

#घोषणा E1000_GLOBAL_STATS_LEN	ARRAY_SIZE(e1000_gstrings_stats)
#घोषणा E1000_STATS_LEN (E1000_GLOBAL_STATS_LEN)
अटल स्थिर अक्षर e1000_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register test  (offline)", "Eeprom test    (offline)",
	"Interrupt test (offline)", "Loopback test  (offline)",
	"Link test   (on/offline)"
पूर्ण;

#घोषणा E1000_TEST_LEN ARRAY_SIZE(e1000_gstrings_test)

अटल पूर्णांक e1000_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 speed, supported, advertising;

	अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		supported = (SUPPORTED_10baseT_Half |
			     SUPPORTED_10baseT_Full |
			     SUPPORTED_100baseT_Half |
			     SUPPORTED_100baseT_Full |
			     SUPPORTED_1000baseT_Full |
			     SUPPORTED_Autoneg |
			     SUPPORTED_TP);
		अगर (hw->phy.type == e1000_phy_अगरe)
			supported &= ~SUPPORTED_1000baseT_Full;
		advertising = ADVERTISED_TP;

		अगर (hw->mac.स्वतःneg == 1) अणु
			advertising |= ADVERTISED_Autoneg;
			/* the e1000 स्वतःneg seems to match ethtool nicely */
			advertising |= hw->phy.स्वतःneg_advertised;
		पूर्ण

		cmd->base.port = PORT_TP;
		cmd->base.phy_address = hw->phy.addr;
	पूर्ण अन्यथा अणु
		supported   = (SUPPORTED_1000baseT_Full |
			       SUPPORTED_FIBRE |
			       SUPPORTED_Autoneg);

		advertising = (ADVERTISED_1000baseT_Full |
			       ADVERTISED_FIBRE |
			       ADVERTISED_Autoneg);

		cmd->base.port = PORT_FIBRE;
	पूर्ण

	speed = SPEED_UNKNOWN;
	cmd->base.duplex = DUPLEX_UNKNOWN;

	अगर (netअगर_running(netdev)) अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			speed = adapter->link_speed;
			cmd->base.duplex = adapter->link_duplex - 1;
		पूर्ण
	पूर्ण अन्यथा अगर (!pm_runसमय_suspended(netdev->dev.parent)) अणु
		u32 status = er32(STATUS);

		अगर (status & E1000_STATUS_LU) अणु
			अगर (status & E1000_STATUS_SPEED_1000)
				speed = SPEED_1000;
			अन्यथा अगर (status & E1000_STATUS_SPEED_100)
				speed = SPEED_100;
			अन्यथा
				speed = SPEED_10;

			अगर (status & E1000_STATUS_FD)
				cmd->base.duplex = DUPLEX_FULL;
			अन्यथा
				cmd->base.duplex = DUPLEX_HALF;
		पूर्ण
	पूर्ण

	cmd->base.speed = speed;
	cmd->base.स्वतःneg = ((hw->phy.media_type == e1000_media_type_fiber) ||
			 hw->mac.स्वतःneg) ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	/* MDI-X => 2; MDI =>1; Invalid =>0 */
	अगर ((hw->phy.media_type == e1000_media_type_copper) &&
	    netअगर_carrier_ok(netdev))
		cmd->base.eth_tp_mdix = hw->phy.is_mdix ?
			ETH_TP_MDI_X : ETH_TP_MDI;
	अन्यथा
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;

	अगर (hw->phy.mdix == AUTO_ALL_MODES)
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;
	अन्यथा
		cmd->base.eth_tp_mdix_ctrl = hw->phy.mdix;

	अगर (hw->phy.media_type != e1000_media_type_copper)
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_set_spd_dplx(काष्ठा e1000_adapter *adapter, u32 spd, u8 dplx)
अणु
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;

	mac->स्वतःneg = 0;

	/* Make sure dplx is at most 1 bit and lsb of speed is not set
	 * क्रम the चयन() below to work
	 */
	अगर ((spd & 1) || (dplx & ~1))
		जाओ err_inval;

	/* Fiber NICs only allow 1000 gbps Full duplex */
	अगर ((adapter->hw.phy.media_type == e1000_media_type_fiber) &&
	    (spd != SPEED_1000) && (dplx != DUPLEX_FULL)) अणु
		जाओ err_inval;
	पूर्ण

	चयन (spd + dplx) अणु
	हाल SPEED_10 + DUPLEX_HALF:
		mac->क्रमced_speed_duplex = ADVERTISE_10_HALF;
		अवरोध;
	हाल SPEED_10 + DUPLEX_FULL:
		mac->क्रमced_speed_duplex = ADVERTISE_10_FULL;
		अवरोध;
	हाल SPEED_100 + DUPLEX_HALF:
		mac->क्रमced_speed_duplex = ADVERTISE_100_HALF;
		अवरोध;
	हाल SPEED_100 + DUPLEX_FULL:
		mac->क्रमced_speed_duplex = ADVERTISE_100_FULL;
		अवरोध;
	हाल SPEED_1000 + DUPLEX_FULL:
		अगर (adapter->hw.phy.media_type == e1000_media_type_copper) अणु
			mac->स्वतःneg = 1;
			adapter->hw.phy.स्वतःneg_advertised =
				ADVERTISE_1000_FULL;
		पूर्ण अन्यथा अणु
			mac->क्रमced_speed_duplex = ADVERTISE_1000_FULL;
		पूर्ण
		अवरोध;
	हाल SPEED_1000 + DUPLEX_HALF:	/* not supported */
	शेष:
		जाओ err_inval;
	पूर्ण

	/* clear MDI, MDI(-X) override is only allowed when स्वतःneg enabled */
	adapter->hw.phy.mdix = AUTO_ALL_MODES;

	वापस 0;

err_inval:
	e_err("Unsupported Speed/Duplex configuration\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक e1000_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक ret_val = 0;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	pm_runसमय_get_sync(netdev->dev.parent);

	/* When SoL/IDER sessions are active, स्वतःneg/speed/duplex
	 * cannot be changed
	 */
	अगर (hw->phy.ops.check_reset_block &&
	    hw->phy.ops.check_reset_block(hw)) अणु
		e_err("Cannot change link characteristics when SoL/IDER is active.\n");
		ret_val = -EINVAL;
		जाओ out;
	पूर्ण

	/* MDI setting is only allowed when स्वतःneg enabled because
	 * some hardware करोesn't allow MDI setting when speed or
	 * duplex is क्रमced.
	 */
	अगर (cmd->base.eth_tp_mdix_ctrl) अणु
		अगर (hw->phy.media_type != e1000_media_type_copper) अणु
			ret_val = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		अगर ((cmd->base.eth_tp_mdix_ctrl != ETH_TP_MDI_AUTO) &&
		    (cmd->base.स्वतःneg != AUTONEG_ENABLE)) अणु
			e_err("forcing MDI/MDI-X state is not supported when link speed and/or duplex are forced\n");
			ret_val = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		hw->mac.स्वतःneg = 1;
		अगर (hw->phy.media_type == e1000_media_type_fiber)
			hw->phy.स्वतःneg_advertised = ADVERTISED_1000baseT_Full |
			    ADVERTISED_FIBRE | ADVERTISED_Autoneg;
		अन्यथा
			hw->phy.स्वतःneg_advertised = advertising |
			    ADVERTISED_TP | ADVERTISED_Autoneg;
		advertising = hw->phy.स्वतःneg_advertised;
		अगर (adapter->fc_स्वतःneg)
			hw->fc.requested_mode = e1000_fc_शेष;
	पूर्ण अन्यथा अणु
		u32 speed = cmd->base.speed;
		/* calling this overrides क्रमced MDI setting */
		अगर (e1000_set_spd_dplx(adapter, speed, cmd->base.duplex)) अणु
			ret_val = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* MDI-X => 2; MDI => 1; Auto => 3 */
	अगर (cmd->base.eth_tp_mdix_ctrl) अणु
		/* fix up the value क्रम स्वतः (3 => 0) as zero is mapped
		 * पूर्णांकernally to स्वतः
		 */
		अगर (cmd->base.eth_tp_mdix_ctrl == ETH_TP_MDI_AUTO)
			hw->phy.mdix = AUTO_ALL_MODES;
		अन्यथा
			hw->phy.mdix = cmd->base.eth_tp_mdix_ctrl;
	पूर्ण

	/* reset the link */
	अगर (netअगर_running(adapter->netdev)) अणु
		e1000e_करोwn(adapter, true);
		e1000e_up(adapter);
	पूर्ण अन्यथा अणु
		e1000e_reset(adapter);
	पूर्ण

out:
	pm_runसमय_put_sync(netdev->dev.parent);
	clear_bit(__E1000_RESETTING, &adapter->state);
	वापस ret_val;
पूर्ण

अटल व्योम e1000_get_छोड़ोparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	छोड़ो->स्वतःneg =
	    (adapter->fc_स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE);

	अगर (hw->fc.current_mode == e1000_fc_rx_छोड़ो) अणु
		छोड़ो->rx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == e1000_fc_tx_छोड़ो) अणु
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == e1000_fc_full) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक e1000_set_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक retval = 0;

	adapter->fc_स्वतःneg = छोड़ो->स्वतःneg;

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	pm_runसमय_get_sync(netdev->dev.parent);

	अगर (adapter->fc_स्वतःneg == AUTONEG_ENABLE) अणु
		hw->fc.requested_mode = e1000_fc_शेष;
		अगर (netअगर_running(adapter->netdev)) अणु
			e1000e_करोwn(adapter, true);
			e1000e_up(adapter);
		पूर्ण अन्यथा अणु
			e1000e_reset(adapter);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = e1000_fc_full;
		अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = e1000_fc_rx_छोड़ो;
		अन्यथा अगर (!छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = e1000_fc_tx_छोड़ो;
		अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = e1000_fc_none;

		hw->fc.current_mode = hw->fc.requested_mode;

		अगर (hw->phy.media_type == e1000_media_type_fiber) अणु
			retval = hw->mac.ops.setup_link(hw);
			/* implicit जाओ out */
		पूर्ण अन्यथा अणु
			retval = e1000e_क्रमce_mac_fc(hw);
			अगर (retval)
				जाओ out;
			e1000e_set_fc_watermarks(hw);
		पूर्ण
	पूर्ण

out:
	pm_runसमय_put_sync(netdev->dev.parent);
	clear_bit(__E1000_RESETTING, &adapter->state);
	वापस retval;
पूर्ण

अटल u32 e1000_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	वापस adapter->msg_enable;
पूर्ण

अटल व्योम e1000_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	adapter->msg_enable = data;
पूर्ण

अटल पूर्णांक e1000_get_regs_len(काष्ठा net_device __always_unused *netdev)
अणु
#घोषणा E1000_REGS_LEN 32	/* overestimate */
	वापस E1000_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम e1000_get_regs(काष्ठा net_device *netdev,
			   काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u16 phy_data;

	pm_runसमय_get_sync(netdev->dev.parent);

	स_रखो(p, 0, E1000_REGS_LEN * माप(u32));

	regs->version = (1u << 24) |
			(adapter->pdev->revision << 16) |
			adapter->pdev->device;

	regs_buff[0] = er32(CTRL);
	regs_buff[1] = er32(STATUS);

	regs_buff[2] = er32(RCTL);
	regs_buff[3] = er32(RDLEN(0));
	regs_buff[4] = er32(RDH(0));
	regs_buff[5] = er32(RDT(0));
	regs_buff[6] = er32(RDTR);

	regs_buff[7] = er32(TCTL);
	regs_buff[8] = er32(TDLEN(0));
	regs_buff[9] = er32(TDH(0));
	regs_buff[10] = er32(TDT(0));
	regs_buff[11] = er32(TIDV);

	regs_buff[12] = adapter->hw.phy.type;	/* PHY type (IGP=1, M88=0) */

	/* ethtool करोesn't use anything past this poपूर्णांक, so all this
	 * code is likely legacy junk क्रम apps that may or may not exist
	 */
	अगर (hw->phy.type == e1000_phy_m88) अणु
		e1e_rphy(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
		regs_buff[13] = (u32)phy_data; /* cable length */
		regs_buff[14] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		regs_buff[15] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		regs_buff[16] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		e1e_rphy(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		regs_buff[17] = (u32)phy_data; /* extended 10bt distance */
		regs_buff[18] = regs_buff[13]; /* cable polarity */
		regs_buff[19] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		regs_buff[20] = regs_buff[17]; /* polarity correction */
		/* phy receive errors */
		regs_buff[22] = adapter->phy_stats.receive_errors;
		regs_buff[23] = regs_buff[13]; /* mdix mode */
	पूर्ण
	regs_buff[21] = 0;	/* was idle_errors */
	e1e_rphy(hw, MII_STAT1000, &phy_data);
	regs_buff[24] = (u32)phy_data;	/* phy local receiver status */
	regs_buff[25] = regs_buff[24];	/* phy remote receiver status */

	pm_runसमय_put_sync(netdev->dev.parent);
पूर्ण

अटल पूर्णांक e1000_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	वापस adapter->hw.nvm.word_size * 2;
पूर्ण

अटल पूर्णांक e1000_get_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	पूर्णांक first_word;
	पूर्णांक last_word;
	पूर्णांक ret_val = 0;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	eeprom->magic = adapter->pdev->venकरोr | (adapter->pdev->device << 16);

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;

	eeprom_buff = kदो_स्मृति_array(last_word - first_word + 1, माप(u16),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	pm_runसमय_get_sync(netdev->dev.parent);

	अगर (hw->nvm.type == e1000_nvm_eeprom_spi) अणु
		ret_val = e1000_पढ़ो_nvm(hw, first_word,
					 last_word - first_word + 1,
					 eeprom_buff);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < last_word - first_word + 1; i++) अणु
			ret_val = e1000_पढ़ो_nvm(hw, first_word + i, 1,
						 &eeprom_buff[i]);
			अगर (ret_val)
				अवरोध;
		पूर्ण
	पूर्ण

	pm_runसमय_put_sync(netdev->dev.parent);

	अगर (ret_val) अणु
		/* a पढ़ो error occurred, throw away the result */
		स_रखो(eeprom_buff, 0xff, माप(u16) *
		       (last_word - first_word + 1));
	पूर्ण अन्यथा अणु
		/* Device's eeprom is always little-endian, word addressable */
		क्रम (i = 0; i < last_word - first_word + 1; i++)
			le16_to_cpus(&eeprom_buff[i]);
	पूर्ण

	स_नकल(bytes, (u8 *)eeprom_buff + (eeprom->offset & 1), eeprom->len);
	kमुक्त(eeprom_buff);

	वापस ret_val;
पूर्ण

अटल पूर्णांक e1000_set_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	व्योम *ptr;
	पूर्णांक max_len;
	पूर्णांक first_word;
	पूर्णांक last_word;
	पूर्णांक ret_val = 0;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EOPNOTSUPP;

	अगर (eeprom->magic !=
	    (adapter->pdev->venकरोr | (adapter->pdev->device << 16)))
		वापस -EFAULT;

	अगर (adapter->flags & FLAG_READ_ONLY_NVM)
		वापस -EINVAL;

	max_len = hw->nvm.word_size * 2;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kदो_स्मृति(max_len, GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	ptr = (व्योम *)eeprom_buff;

	pm_runसमय_get_sync(netdev->dev.parent);

	अगर (eeprom->offset & 1) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of first changed EEPROM word */
		/* only the second byte of the word is being modअगरied */
		ret_val = e1000_पढ़ो_nvm(hw, first_word, 1, &eeprom_buff[0]);
		ptr++;
	पूर्ण
	अगर (((eeprom->offset + eeprom->len) & 1) && (!ret_val))
		/* need पढ़ो/modअगरy/ग_लिखो of last changed EEPROM word */
		/* only the first byte of the word is being modअगरied */
		ret_val = e1000_पढ़ो_nvm(hw, last_word, 1,
					 &eeprom_buff[last_word - first_word]);

	अगर (ret_val)
		जाओ out;

	/* Device's eeprom is always little-endian, word addressable */
	क्रम (i = 0; i < last_word - first_word + 1; i++)
		le16_to_cpus(&eeprom_buff[i]);

	स_नकल(ptr, bytes, eeprom->len);

	क्रम (i = 0; i < last_word - first_word + 1; i++)
		cpu_to_le16s(&eeprom_buff[i]);

	ret_val = e1000_ग_लिखो_nvm(hw, first_word,
				  last_word - first_word + 1, eeprom_buff);

	अगर (ret_val)
		जाओ out;

	/* Update the checksum over the first part of the EEPROM अगर needed
	 * and flush shaकरोw RAM क्रम applicable controllers
	 */
	अगर ((first_word <= NVM_CHECKSUM_REG) ||
	    (hw->mac.type == e1000_82583) ||
	    (hw->mac.type == e1000_82574) ||
	    (hw->mac.type == e1000_82573))
		ret_val = e1000e_update_nvm_checksum(hw);

out:
	pm_runसमय_put_sync(netdev->dev.parent);
	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल व्योम e1000_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, e1000e_driver_name, माप(drvinfo->driver));

	/* EEPROM image version # is reported as firmware version # क्रम
	 * PCI-E controllers
	 */
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%d.%d-%d",
		 (adapter->eeprom_vers & 0xF000) >> 12,
		 (adapter->eeprom_vers & 0x0FF0) >> 4,
		 (adapter->eeprom_vers & 0x000F));

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम e1000_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = E1000_MAX_RXD;
	ring->tx_max_pending = E1000_MAX_TXD;
	ring->rx_pending = adapter->rx_ring_count;
	ring->tx_pending = adapter->tx_ring_count;
पूर्ण

अटल पूर्णांक e1000_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_ring *temp_tx = शून्य, *temp_rx = शून्य;
	पूर्णांक err = 0, size = माप(काष्ठा e1000_ring);
	bool set_tx = false, set_rx = false;
	u16 new_rx_count, new_tx_count;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	new_rx_count = clamp_t(u32, ring->rx_pending, E1000_MIN_RXD,
			       E1000_MAX_RXD);
	new_rx_count = ALIGN(new_rx_count, REQ_RX_DESCRIPTOR_MULTIPLE);

	new_tx_count = clamp_t(u32, ring->tx_pending, E1000_MIN_TXD,
			       E1000_MAX_TXD);
	new_tx_count = ALIGN(new_tx_count, REQ_TX_DESCRIPTOR_MULTIPLE);

	अगर ((new_tx_count == adapter->tx_ring_count) &&
	    (new_rx_count == adapter->rx_ring_count))
		/* nothing to करो */
		वापस 0;

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (!netअगर_running(adapter->netdev)) अणु
		/* Set counts now and allocate resources during खोलो() */
		adapter->tx_ring->count = new_tx_count;
		adapter->rx_ring->count = new_rx_count;
		adapter->tx_ring_count = new_tx_count;
		adapter->rx_ring_count = new_rx_count;
		जाओ clear_reset;
	पूर्ण

	set_tx = (new_tx_count != adapter->tx_ring_count);
	set_rx = (new_rx_count != adapter->rx_ring_count);

	/* Allocate temporary storage क्रम ring updates */
	अगर (set_tx) अणु
		temp_tx = vदो_स्मृति(size);
		अगर (!temp_tx) अणु
			err = -ENOMEM;
			जाओ मुक्त_temp;
		पूर्ण
	पूर्ण
	अगर (set_rx) अणु
		temp_rx = vदो_स्मृति(size);
		अगर (!temp_rx) अणु
			err = -ENOMEM;
			जाओ मुक्त_temp;
		पूर्ण
	पूर्ण

	pm_runसमय_get_sync(netdev->dev.parent);

	e1000e_करोwn(adapter, true);

	/* We can't just मुक्त everything and then setup again, because the
	 * ISRs in MSI-X mode get passed poपूर्णांकers to the Tx and Rx ring
	 * काष्ठाs.  First, attempt to allocate new resources...
	 */
	अगर (set_tx) अणु
		स_नकल(temp_tx, adapter->tx_ring, size);
		temp_tx->count = new_tx_count;
		err = e1000e_setup_tx_resources(temp_tx);
		अगर (err)
			जाओ err_setup;
	पूर्ण
	अगर (set_rx) अणु
		स_नकल(temp_rx, adapter->rx_ring, size);
		temp_rx->count = new_rx_count;
		err = e1000e_setup_rx_resources(temp_rx);
		अगर (err)
			जाओ err_setup_rx;
	पूर्ण

	/* ...then मुक्त the old resources and copy back any new ring data */
	अगर (set_tx) अणु
		e1000e_मुक्त_tx_resources(adapter->tx_ring);
		स_नकल(adapter->tx_ring, temp_tx, size);
		adapter->tx_ring_count = new_tx_count;
	पूर्ण
	अगर (set_rx) अणु
		e1000e_मुक्त_rx_resources(adapter->rx_ring);
		स_नकल(adapter->rx_ring, temp_rx, size);
		adapter->rx_ring_count = new_rx_count;
	पूर्ण

err_setup_rx:
	अगर (err && set_tx)
		e1000e_मुक्त_tx_resources(temp_tx);
err_setup:
	e1000e_up(adapter);
	pm_runसमय_put_sync(netdev->dev.parent);
मुक्त_temp:
	vमुक्त(temp_tx);
	vमुक्त(temp_rx);
clear_reset:
	clear_bit(__E1000_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल bool reg_pattern_test(काष्ठा e1000_adapter *adapter, u64 *data,
			     पूर्णांक reg, पूर्णांक offset, u32 mask, u32 ग_लिखो)
अणु
	u32 pat, val;
	अटल स्थिर u32 test[] = अणु
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
	पूर्ण;
	क्रम (pat = 0; pat < ARRAY_SIZE(test); pat++) अणु
		E1000_WRITE_REG_ARRAY(&adapter->hw, reg, offset,
				      (test[pat] & ग_लिखो));
		val = E1000_READ_REG_ARRAY(&adapter->hw, reg, offset);
		अगर (val != (test[pat] & ग_लिखो & mask)) अणु
			e_err("pattern test failed (reg 0x%05X): got 0x%08X expected 0x%08X\n",
			      reg + (offset << 2), val,
			      (test[pat] & ग_लिखो & mask));
			*data = reg;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool reg_set_and_check(काष्ठा e1000_adapter *adapter, u64 *data,
			      पूर्णांक reg, u32 mask, u32 ग_लिखो)
अणु
	u32 val;

	__ew32(&adapter->hw, reg, ग_लिखो & mask);
	val = __er32(&adapter->hw, reg);
	अगर ((ग_लिखो & mask) != (val & mask)) अणु
		e_err("set/check test failed (reg 0x%05X): got 0x%08X expected 0x%08X\n",
		      reg, (val & mask), (ग_लिखो & mask));
		*data = reg;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

#घोषणा REG_PATTERN_TEST_ARRAY(reg, offset, mask, ग_लिखो)                       \
	करो अणु                                                                   \
		अगर (reg_pattern_test(adapter, data, reg, offset, mask, ग_लिखो)) \
			वापस 1;                                              \
	पूर्ण जबतक (0)
#घोषणा REG_PATTERN_TEST(reg, mask, ग_लिखो)                                     \
	REG_PATTERN_TEST_ARRAY(reg, 0, mask, ग_लिखो)

#घोषणा REG_SET_AND_CHECK(reg, mask, ग_लिखो)                                    \
	करो अणु                                                                   \
		अगर (reg_set_and_check(adapter, data, reg, mask, ग_लिखो))        \
			वापस 1;                                              \
	पूर्ण जबतक (0)

अटल पूर्णांक e1000_reg_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;
	u32 value;
	u32 beक्रमe;
	u32 after;
	u32 i;
	u32 toggle;
	u32 mask;
	u32 wlock_mac = 0;

	/* The status रेजिस्टर is Read Only, so a ग_लिखो should fail.
	 * Some bits that get toggled are ignored.  There are several bits
	 * on newer hardware that are r/w.
	 */
	चयन (mac->type) अणु
	हाल e1000_82571:
	हाल e1000_82572:
	हाल e1000_80003es2lan:
		toggle = 0x7FFFF3FF;
		अवरोध;
	शेष:
		toggle = 0x7FFFF033;
		अवरोध;
	पूर्ण

	beक्रमe = er32(STATUS);
	value = (er32(STATUS) & toggle);
	ew32(STATUS, toggle);
	after = er32(STATUS) & toggle;
	अगर (value != after) अणु
		e_err("failed STATUS register test got: 0x%08X expected: 0x%08X\n",
		      after, value);
		*data = 1;
		वापस 1;
	पूर्ण
	/* restore previous status */
	ew32(STATUS, beक्रमe);

	अगर (!(adapter->flags & FLAG_IS_ICH)) अणु
		REG_PATTERN_TEST(E1000_FCAL, 0xFFFFFFFF, 0xFFFFFFFF);
		REG_PATTERN_TEST(E1000_FCAH, 0x0000FFFF, 0xFFFFFFFF);
		REG_PATTERN_TEST(E1000_FCT, 0x0000FFFF, 0xFFFFFFFF);
		REG_PATTERN_TEST(E1000_VET, 0x0000FFFF, 0xFFFFFFFF);
	पूर्ण

	REG_PATTERN_TEST(E1000_RDTR, 0x0000FFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(E1000_RDBAH(0), 0xFFFFFFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(E1000_RDLEN(0), 0x000FFF80, 0x000FFFFF);
	REG_PATTERN_TEST(E1000_RDH(0), 0x0000FFFF, 0x0000FFFF);
	REG_PATTERN_TEST(E1000_RDT(0), 0x0000FFFF, 0x0000FFFF);
	REG_PATTERN_TEST(E1000_FCRTH, 0x0000FFF8, 0x0000FFF8);
	REG_PATTERN_TEST(E1000_FCTTV, 0x0000FFFF, 0x0000FFFF);
	REG_PATTERN_TEST(E1000_TIPG, 0x3FFFFFFF, 0x3FFFFFFF);
	REG_PATTERN_TEST(E1000_TDBAH(0), 0xFFFFFFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(E1000_TDLEN(0), 0x000FFF80, 0x000FFFFF);

	REG_SET_AND_CHECK(E1000_RCTL, 0xFFFFFFFF, 0x00000000);

	beक्रमe = ((adapter->flags & FLAG_IS_ICH) ? 0x06C3B33E : 0x06DFB3FE);
	REG_SET_AND_CHECK(E1000_RCTL, beक्रमe, 0x003FFFFB);
	REG_SET_AND_CHECK(E1000_TCTL, 0xFFFFFFFF, 0x00000000);

	REG_SET_AND_CHECK(E1000_RCTL, beक्रमe, 0xFFFFFFFF);
	REG_PATTERN_TEST(E1000_RDBAL(0), 0xFFFFFFF0, 0xFFFFFFFF);
	अगर (!(adapter->flags & FLAG_IS_ICH))
		REG_PATTERN_TEST(E1000_TXCW, 0xC000FFFF, 0x0000FFFF);
	REG_PATTERN_TEST(E1000_TDBAL(0), 0xFFFFFFF0, 0xFFFFFFFF);
	REG_PATTERN_TEST(E1000_TIDV, 0x0000FFFF, 0x0000FFFF);
	mask = 0x8003FFFF;
	चयन (mac->type) अणु
	हाल e1000_ich10lan:
	हाल e1000_pchlan:
	हाल e1000_pch2lan:
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		mask |= BIT(18);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (mac->type >= e1000_pch_lpt)
		wlock_mac = (er32(FWSM) & E1000_FWSM_WLOCK_MAC_MASK) >>
		    E1000_FWSM_WLOCK_MAC_SHIFT;

	क्रम (i = 0; i < mac->rar_entry_count; i++) अणु
		अगर (mac->type >= e1000_pch_lpt) अणु
			/* Cannot test ग_लिखो-रक्षित SHRAL[n] रेजिस्टरs */
			अगर ((wlock_mac == 1) || (wlock_mac && (i > wlock_mac)))
				जारी;

			/* SHRAH[9] dअगरferent than the others */
			अगर (i == 10)
				mask |= BIT(30);
			अन्यथा
				mask &= ~BIT(30);
		पूर्ण
		अगर (mac->type == e1000_pch2lan) अणु
			/* SHRAH[0,1,2] dअगरferent than previous */
			अगर (i == 1)
				mask &= 0xFFF4FFFF;
			/* SHRAH[3] dअगरferent than SHRAH[0,1,2] */
			अगर (i == 4)
				mask |= BIT(30);
			/* RAR[1-6] owned by management engine - skipping */
			अगर (i > 0)
				i += 6;
		पूर्ण

		REG_PATTERN_TEST_ARRAY(E1000_RA, ((i << 1) + 1), mask,
				       0xFFFFFFFF);
		/* reset index to actual value */
		अगर ((mac->type == e1000_pch2lan) && (i > 6))
			i -= 6;
	पूर्ण

	क्रम (i = 0; i < mac->mta_reg_count; i++)
		REG_PATTERN_TEST_ARRAY(E1000_MTA, i, 0xFFFFFFFF, 0xFFFFFFFF);

	*data = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_eeprom_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
	u16 temp;
	u16 checksum = 0;
	u16 i;

	*data = 0;
	/* Read and add up the contents of the EEPROM */
	क्रम (i = 0; i < (NVM_CHECKSUM_REG + 1); i++) अणु
		अगर ((e1000_पढ़ो_nvm(&adapter->hw, i, 1, &temp)) < 0) अणु
			*data = 1;
			वापस *data;
		पूर्ण
		checksum += temp;
	पूर्ण

	/* If Checksum is not Correct वापस error अन्यथा test passed */
	अगर ((checksum != (u16)NVM_SUM) && !(*data))
		*data = 2;

	वापस *data;
पूर्ण

अटल irqवापस_t e1000_test_पूर्णांकr(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = (काष्ठा net_device *)data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	adapter->test_icr |= er32(ICR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक e1000_पूर्णांकr_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 mask;
	u32 shared_पूर्णांक = 1;
	u32 irq = adapter->pdev->irq;
	पूर्णांक i;
	पूर्णांक ret_val = 0;
	पूर्णांक पूर्णांक_mode = E1000E_INT_MODE_LEGACY;

	*data = 0;

	/* NOTE: we करोn't test MSI/MSI-X पूर्णांकerrupts here, yet */
	अगर (adapter->पूर्णांक_mode == E1000E_INT_MODE_MSIX) अणु
		पूर्णांक_mode = adapter->पूर्णांक_mode;
		e1000e_reset_पूर्णांकerrupt_capability(adapter);
		adapter->पूर्णांक_mode = E1000E_INT_MODE_LEGACY;
		e1000e_set_पूर्णांकerrupt_capability(adapter);
	पूर्ण
	/* Hook up test पूर्णांकerrupt handler just क्रम this test */
	अगर (!request_irq(irq, e1000_test_पूर्णांकr, IRQF_PROBE_SHARED, netdev->name,
			 netdev)) अणु
		shared_पूर्णांक = 0;
	पूर्ण अन्यथा अगर (request_irq(irq, e1000_test_पूर्णांकr, IRQF_SHARED, netdev->name,
			       netdev)) अणु
		*data = 1;
		ret_val = -1;
		जाओ out;
	पूर्ण
	e_info("testing %s interrupt\n", (shared_पूर्णांक ? "shared" : "unshared"));

	/* Disable all the पूर्णांकerrupts */
	ew32(IMC, 0xFFFFFFFF);
	e1e_flush();
	usleep_range(10000, 11000);

	/* Test each पूर्णांकerrupt */
	क्रम (i = 0; i < 10; i++) अणु
		/* Interrupt to test */
		mask = BIT(i);

		अगर (adapter->flags & FLAG_IS_ICH) अणु
			चयन (mask) अणु
			हाल E1000_ICR_RXSEQ:
				जारी;
			हाल 0x00000100:
				अगर (adapter->hw.mac.type == e1000_ich8lan ||
				    adapter->hw.mac.type == e1000_ich9lan)
					जारी;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!shared_पूर्णांक) अणु
			/* Disable the पूर्णांकerrupt to be reported in
			 * the cause रेजिस्टर and then क्रमce the same
			 * पूर्णांकerrupt and see अगर one माला_लो posted.  If
			 * an पूर्णांकerrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;
			ew32(IMC, mask);
			ew32(ICS, mask);
			e1e_flush();
			usleep_range(10000, 11000);

			अगर (adapter->test_icr & mask) अणु
				*data = 3;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Enable the पूर्णांकerrupt to be reported in
		 * the cause रेजिस्टर and then क्रमce the same
		 * पूर्णांकerrupt and see अगर one माला_लो posted.  If
		 * an पूर्णांकerrupt was not posted to the bus, the
		 * test failed.
		 */
		adapter->test_icr = 0;
		ew32(IMS, mask);
		ew32(ICS, mask);
		e1e_flush();
		usleep_range(10000, 11000);

		अगर (!(adapter->test_icr & mask)) अणु
			*data = 4;
			अवरोध;
		पूर्ण

		अगर (!shared_पूर्णांक) अणु
			/* Disable the other पूर्णांकerrupts to be reported in
			 * the cause रेजिस्टर and then क्रमce the other
			 * पूर्णांकerrupts and see अगर any get posted.  If
			 * an पूर्णांकerrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;
			ew32(IMC, ~mask & 0x00007FFF);
			ew32(ICS, ~mask & 0x00007FFF);
			e1e_flush();
			usleep_range(10000, 11000);

			अगर (adapter->test_icr) अणु
				*data = 5;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable all the पूर्णांकerrupts */
	ew32(IMC, 0xFFFFFFFF);
	e1e_flush();
	usleep_range(10000, 11000);

	/* Unhook test पूर्णांकerrupt handler */
	मुक्त_irq(irq, netdev);

out:
	अगर (पूर्णांक_mode == E1000E_INT_MODE_MSIX) अणु
		e1000e_reset_पूर्णांकerrupt_capability(adapter);
		adapter->पूर्णांक_mode = पूर्णांक_mode;
		e1000e_set_पूर्णांकerrupt_capability(adapter);
	पूर्ण

	वापस ret_val;
पूर्ण

अटल व्योम e1000_मुक्त_desc_rings(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_ring *tx_ring = &adapter->test_tx_ring;
	काष्ठा e1000_ring *rx_ring = &adapter->test_rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_buffer *buffer_info;
	पूर्णांक i;

	अगर (tx_ring->desc && tx_ring->buffer_info) अणु
		क्रम (i = 0; i < tx_ring->count; i++) अणु
			buffer_info = &tx_ring->buffer_info[i];

			अगर (buffer_info->dma)
				dma_unmap_single(&pdev->dev,
						 buffer_info->dma,
						 buffer_info->length,
						 DMA_TO_DEVICE);
			dev_kमुक्त_skb(buffer_info->skb);
		पूर्ण
	पूर्ण

	अगर (rx_ring->desc && rx_ring->buffer_info) अणु
		क्रम (i = 0; i < rx_ring->count; i++) अणु
			buffer_info = &rx_ring->buffer_info[i];

			अगर (buffer_info->dma)
				dma_unmap_single(&pdev->dev,
						 buffer_info->dma,
						 2048, DMA_FROM_DEVICE);
			dev_kमुक्त_skb(buffer_info->skb);
		पूर्ण
	पूर्ण

	अगर (tx_ring->desc) अणु
		dma_मुक्त_coherent(&pdev->dev, tx_ring->size, tx_ring->desc,
				  tx_ring->dma);
		tx_ring->desc = शून्य;
	पूर्ण
	अगर (rx_ring->desc) अणु
		dma_मुक्त_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
				  rx_ring->dma);
		rx_ring->desc = शून्य;
	पूर्ण

	kमुक्त(tx_ring->buffer_info);
	tx_ring->buffer_info = शून्य;
	kमुक्त(rx_ring->buffer_info);
	rx_ring->buffer_info = शून्य;
पूर्ण

अटल पूर्णांक e1000_setup_desc_rings(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_ring *tx_ring = &adapter->test_tx_ring;
	काष्ठा e1000_ring *rx_ring = &adapter->test_rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;
	पूर्णांक i;
	पूर्णांक ret_val;

	/* Setup Tx descriptor ring and Tx buffers */

	अगर (!tx_ring->count)
		tx_ring->count = E1000_DEFAULT_TXD;

	tx_ring->buffer_info = kसुस्मृति(tx_ring->count,
				       माप(काष्ठा e1000_buffer), GFP_KERNEL);
	अगर (!tx_ring->buffer_info) अणु
		ret_val = 1;
		जाओ err_nomem;
	पूर्ण

	tx_ring->size = tx_ring->count * माप(काष्ठा e1000_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);
	tx_ring->desc = dma_alloc_coherent(&pdev->dev, tx_ring->size,
					   &tx_ring->dma, GFP_KERNEL);
	अगर (!tx_ring->desc) अणु
		ret_val = 2;
		जाओ err_nomem;
	पूर्ण
	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	ew32(TDBAL(0), ((u64)tx_ring->dma & 0x00000000FFFFFFFF));
	ew32(TDBAH(0), ((u64)tx_ring->dma >> 32));
	ew32(TDLEN(0), tx_ring->count * माप(काष्ठा e1000_tx_desc));
	ew32(TDH(0), 0);
	ew32(TDT(0), 0);
	ew32(TCTL, E1000_TCTL_PSP | E1000_TCTL_EN | E1000_TCTL_MULR |
	     E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT |
	     E1000_COLLISION_DISTANCE << E1000_COLD_SHIFT);

	क्रम (i = 0; i < tx_ring->count; i++) अणु
		काष्ठा e1000_tx_desc *tx_desc = E1000_TX_DESC(*tx_ring, i);
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक skb_size = 1024;

		skb = alloc_skb(skb_size, GFP_KERNEL);
		अगर (!skb) अणु
			ret_val = 3;
			जाओ err_nomem;
		पूर्ण
		skb_put(skb, skb_size);
		tx_ring->buffer_info[i].skb = skb;
		tx_ring->buffer_info[i].length = skb->len;
		tx_ring->buffer_info[i].dma =
		    dma_map_single(&pdev->dev, skb->data, skb->len,
				   DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev,
				      tx_ring->buffer_info[i].dma)) अणु
			ret_val = 4;
			जाओ err_nomem;
		पूर्ण
		tx_desc->buffer_addr = cpu_to_le64(tx_ring->buffer_info[i].dma);
		tx_desc->lower.data = cpu_to_le32(skb->len);
		tx_desc->lower.data |= cpu_to_le32(E1000_TXD_CMD_EOP |
						   E1000_TXD_CMD_IFCS |
						   E1000_TXD_CMD_RS);
		tx_desc->upper.data = 0;
	पूर्ण

	/* Setup Rx descriptor ring and Rx buffers */

	अगर (!rx_ring->count)
		rx_ring->count = E1000_DEFAULT_RXD;

	rx_ring->buffer_info = kसुस्मृति(rx_ring->count,
				       माप(काष्ठा e1000_buffer), GFP_KERNEL);
	अगर (!rx_ring->buffer_info) अणु
		ret_val = 5;
		जाओ err_nomem;
	पूर्ण

	rx_ring->size = rx_ring->count * माप(जोड़ e1000_rx_desc_extended);
	rx_ring->desc = dma_alloc_coherent(&pdev->dev, rx_ring->size,
					   &rx_ring->dma, GFP_KERNEL);
	अगर (!rx_ring->desc) अणु
		ret_val = 6;
		जाओ err_nomem;
	पूर्ण
	rx_ring->next_to_use = 0;
	rx_ring->next_to_clean = 0;

	rctl = er32(RCTL);
	अगर (!(adapter->flags2 & FLAG2_NO_DISABLE_RX))
		ew32(RCTL, rctl & ~E1000_RCTL_EN);
	ew32(RDBAL(0), ((u64)rx_ring->dma & 0xFFFFFFFF));
	ew32(RDBAH(0), ((u64)rx_ring->dma >> 32));
	ew32(RDLEN(0), rx_ring->size);
	ew32(RDH(0), 0);
	ew32(RDT(0), 0);
	rctl = E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_SZ_2048 |
	    E1000_RCTL_UPE | E1000_RCTL_MPE | E1000_RCTL_LPE |
	    E1000_RCTL_SBP | E1000_RCTL_SECRC |
	    E1000_RCTL_LBM_NO | E1000_RCTL_RDMTS_HALF |
	    (adapter->hw.mac.mc_filter_type << E1000_RCTL_MO_SHIFT);
	ew32(RCTL, rctl);

	क्रम (i = 0; i < rx_ring->count; i++) अणु
		जोड़ e1000_rx_desc_extended *rx_desc;
		काष्ठा sk_buff *skb;

		skb = alloc_skb(2048 + NET_IP_ALIGN, GFP_KERNEL);
		अगर (!skb) अणु
			ret_val = 7;
			जाओ err_nomem;
		पूर्ण
		skb_reserve(skb, NET_IP_ALIGN);
		rx_ring->buffer_info[i].skb = skb;
		rx_ring->buffer_info[i].dma =
		    dma_map_single(&pdev->dev, skb->data, 2048,
				   DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&pdev->dev,
				      rx_ring->buffer_info[i].dma)) अणु
			ret_val = 8;
			जाओ err_nomem;
		पूर्ण
		rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
		rx_desc->पढ़ो.buffer_addr =
		    cpu_to_le64(rx_ring->buffer_info[i].dma);
		स_रखो(skb->data, 0x00, skb->len);
	पूर्ण

	वापस 0;

err_nomem:
	e1000_मुक्त_desc_rings(adapter);
	वापस ret_val;
पूर्ण

अटल व्योम e1000_phy_disable_receiver(काष्ठा e1000_adapter *adapter)
अणु
	/* Write out to PHY रेजिस्टरs 29 and 30 to disable the Receiver. */
	e1e_wphy(&adapter->hw, 29, 0x001F);
	e1e_wphy(&adapter->hw, 30, 0x8FFC);
	e1e_wphy(&adapter->hw, 29, 0x001A);
	e1e_wphy(&adapter->hw, 30, 0x8FF0);
पूर्ण

अटल पूर्णांक e1000_पूर्णांकegrated_phy_loopback(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_reg = 0;
	u16 phy_reg = 0;
	s32 ret_val = 0;

	hw->mac.स्वतःneg = 0;

	अगर (hw->phy.type == e1000_phy_अगरe) अणु
		/* क्रमce 100, set loopback */
		e1e_wphy(hw, MII_BMCR, 0x6100);

		/* Now set up the MAC to the same speed/duplex as the PHY. */
		ctrl_reg = er32(CTRL);
		ctrl_reg &= ~E1000_CTRL_SPD_SEL; /* Clear the speed sel bits */
		ctrl_reg |= (E1000_CTRL_FRCSPD | /* Set the Force Speed Bit */
			     E1000_CTRL_FRCDPX | /* Set the Force Duplex Bit */
			     E1000_CTRL_SPD_100 |/* Force Speed to 100 */
			     E1000_CTRL_FD);	 /* Force Duplex to FULL */

		ew32(CTRL, ctrl_reg);
		e1e_flush();
		usleep_range(500, 1000);

		वापस 0;
	पूर्ण

	/* Specअगरic PHY configuration क्रम loopback */
	चयन (hw->phy.type) अणु
	हाल e1000_phy_m88:
		/* Auto-MDI/MDIX Off */
		e1e_wphy(hw, M88E1000_PHY_SPEC_CTRL, 0x0808);
		/* reset to update Auto-MDI/MDIX */
		e1e_wphy(hw, MII_BMCR, 0x9140);
		/* स्वतःneg off */
		e1e_wphy(hw, MII_BMCR, 0x8140);
		अवरोध;
	हाल e1000_phy_gg82563:
		e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, 0x1CC);
		अवरोध;
	हाल e1000_phy_bm:
		/* Set Default MAC Interface speed to 1GB */
		e1e_rphy(hw, PHY_REG(2, 21), &phy_reg);
		phy_reg &= ~0x0007;
		phy_reg |= 0x006;
		e1e_wphy(hw, PHY_REG(2, 21), phy_reg);
		/* Assert SW reset क्रम above settings to take effect */
		hw->phy.ops.commit(hw);
		usleep_range(1000, 2000);
		/* Force Full Duplex */
		e1e_rphy(hw, PHY_REG(769, 16), &phy_reg);
		e1e_wphy(hw, PHY_REG(769, 16), phy_reg | 0x000C);
		/* Set Link Up (in क्रमce link) */
		e1e_rphy(hw, PHY_REG(776, 16), &phy_reg);
		e1e_wphy(hw, PHY_REG(776, 16), phy_reg | 0x0040);
		/* Force Link */
		e1e_rphy(hw, PHY_REG(769, 16), &phy_reg);
		e1e_wphy(hw, PHY_REG(769, 16), phy_reg | 0x0040);
		/* Set Early Link Enable */
		e1e_rphy(hw, PHY_REG(769, 20), &phy_reg);
		e1e_wphy(hw, PHY_REG(769, 20), phy_reg | 0x0400);
		अवरोध;
	हाल e1000_phy_82577:
	हाल e1000_phy_82578:
		/* Workaround: K1 must be disabled क्रम stable 1Gbps operation */
		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val) अणु
			e_err("Cannot setup 1Gbps loopback.\n");
			वापस ret_val;
		पूर्ण
		e1000_configure_k1_ich8lan(hw, false);
		hw->phy.ops.release(hw);
		अवरोध;
	हाल e1000_phy_82579:
		/* Disable PHY energy detect घातer करोwn */
		e1e_rphy(hw, PHY_REG(0, 21), &phy_reg);
		e1e_wphy(hw, PHY_REG(0, 21), phy_reg & ~BIT(3));
		/* Disable full chip energy detect */
		e1e_rphy(hw, PHY_REG(776, 18), &phy_reg);
		e1e_wphy(hw, PHY_REG(776, 18), phy_reg | 1);
		/* Enable loopback on the PHY */
		e1e_wphy(hw, I82577_PHY_LBK_CTRL, 0x8001);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* क्रमce 1000, set loopback */
	e1e_wphy(hw, MII_BMCR, 0x4140);
	msleep(250);

	/* Now set up the MAC to the same speed/duplex as the PHY. */
	ctrl_reg = er32(CTRL);
	ctrl_reg &= ~E1000_CTRL_SPD_SEL; /* Clear the speed sel bits */
	ctrl_reg |= (E1000_CTRL_FRCSPD | /* Set the Force Speed Bit */
		     E1000_CTRL_FRCDPX | /* Set the Force Duplex Bit */
		     E1000_CTRL_SPD_1000 |/* Force Speed to 1000 */
		     E1000_CTRL_FD);	 /* Force Duplex to FULL */

	अगर (adapter->flags & FLAG_IS_ICH)
		ctrl_reg |= E1000_CTRL_SLU;	/* Set Link Up */

	अगर (hw->phy.media_type == e1000_media_type_copper &&
	    hw->phy.type == e1000_phy_m88) अणु
		ctrl_reg |= E1000_CTRL_ILOS;	/* Invert Loss of Signal */
	पूर्ण अन्यथा अणु
		/* Set the ILOS bit on the fiber Nic अगर half duplex link is
		 * detected.
		 */
		अगर ((er32(STATUS) & E1000_STATUS_FD) == 0)
			ctrl_reg |= (E1000_CTRL_ILOS | E1000_CTRL_SLU);
	पूर्ण

	ew32(CTRL, ctrl_reg);

	/* Disable the receiver on the PHY so when a cable is plugged in, the
	 * PHY करोes not begin to स्वतःneg when a cable is reconnected to the NIC.
	 */
	अगर (hw->phy.type == e1000_phy_m88)
		e1000_phy_disable_receiver(adapter);

	usleep_range(500, 1000);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_set_82571_fiber_loopback(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl = er32(CTRL);
	पूर्णांक link;

	/* special requirements क्रम 82571/82572 fiber adapters */

	/* jump through hoops to make sure link is up because serdes
	 * link is hardwired up
	 */
	ctrl |= E1000_CTRL_SLU;
	ew32(CTRL, ctrl);

	/* disable स्वतःneg */
	ctrl = er32(TXCW);
	ctrl &= ~BIT(31);
	ew32(TXCW, ctrl);

	link = (er32(STATUS) & E1000_STATUS_LU);

	अगर (!link) अणु
		/* set invert loss of संकेत */
		ctrl = er32(CTRL);
		ctrl |= E1000_CTRL_ILOS;
		ew32(CTRL, ctrl);
	पूर्ण

	/* special ग_लिखो to serdes control रेजिस्टर to enable SerDes analog
	 * loopback
	 */
	ew32(SCTL, E1000_SCTL_ENABLE_SERDES_LOOPBACK);
	e1e_flush();
	usleep_range(10000, 11000);

	वापस 0;
पूर्ण

/* only call this क्रम fiber/serdes connections to es2lan */
अटल पूर्णांक e1000_set_es2lan_mac_loopback(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrlext = er32(CTRL_EXT);
	u32 ctrl = er32(CTRL);

	/* save CTRL_EXT to restore later, reuse an empty variable (unused
	 * on mac_type 80003es2lan)
	 */
	adapter->tx_fअगरo_head = ctrlext;

	/* clear the serdes mode bits, putting the device पूर्णांकo mac loopback */
	ctrlext &= ~E1000_CTRL_EXT_LINK_MODE_PCIE_SERDES;
	ew32(CTRL_EXT, ctrlext);

	/* क्रमce speed to 1000/FD, link up */
	ctrl &= ~(E1000_CTRL_SPD_1000 | E1000_CTRL_SPD_100);
	ctrl |= (E1000_CTRL_SLU | E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX |
		 E1000_CTRL_SPD_1000 | E1000_CTRL_FD);
	ew32(CTRL, ctrl);

	/* set mac loopback */
	ctrl = er32(RCTL);
	ctrl |= E1000_RCTL_LBM_MAC;
	ew32(RCTL, ctrl);

	/* set testing mode parameters (no need to reset later) */
#घोषणा KMRNCTRLSTA_OPMODE (0x1F << 16)
#घोषणा KMRNCTRLSTA_OPMODE_1GB_FD_GMII 0x0582
	ew32(KMRNCTRLSTA,
	     (KMRNCTRLSTA_OPMODE | KMRNCTRLSTA_OPMODE_1GB_FD_GMII));

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_setup_loopback_test(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl, fext_nvm11, tarc0;

	अगर (hw->mac.type >= e1000_pch_spt) अणु
		fext_nvm11 = er32(FEXTNVM11);
		fext_nvm11 |= E1000_FEXTNVM11_DISABLE_MULR_FIX;
		ew32(FEXTNVM11, fext_nvm11);
		tarc0 = er32(TARC(0));
		/* clear bits 28 & 29 (control of MULR concurrent requests) */
		tarc0 &= 0xcfffffff;
		/* set bit 29 (value of MULR requests is now 2) */
		tarc0 |= 0x20000000;
		ew32(TARC(0), tarc0);
	पूर्ण
	अगर (hw->phy.media_type == e1000_media_type_fiber ||
	    hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
		चयन (hw->mac.type) अणु
		हाल e1000_80003es2lan:
			वापस e1000_set_es2lan_mac_loopback(adapter);
		हाल e1000_82571:
		हाल e1000_82572:
			वापस e1000_set_82571_fiber_loopback(adapter);
		शेष:
			rctl = er32(RCTL);
			rctl |= E1000_RCTL_LBM_TCVR;
			ew32(RCTL, rctl);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (hw->phy.media_type == e1000_media_type_copper) अणु
		वापस e1000_पूर्णांकegrated_phy_loopback(adapter);
	पूर्ण

	वापस 7;
पूर्ण

अटल व्योम e1000_loopback_cleanup(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl, fext_nvm11, tarc0;
	u16 phy_reg;

	rctl = er32(RCTL);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);
	ew32(RCTL, rctl);

	चयन (hw->mac.type) अणु
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		fext_nvm11 = er32(FEXTNVM11);
		fext_nvm11 &= ~E1000_FEXTNVM11_DISABLE_MULR_FIX;
		ew32(FEXTNVM11, fext_nvm11);
		tarc0 = er32(TARC(0));
		/* clear bits 28 & 29 (control of MULR concurrent requests) */
		/* set bit 29 (value of MULR requests is now 0) */
		tarc0 &= 0xcfffffff;
		ew32(TARC(0), tarc0);
		fallthrough;
	हाल e1000_80003es2lan:
		अगर (hw->phy.media_type == e1000_media_type_fiber ||
		    hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
			/* restore CTRL_EXT, stealing space from tx_fअगरo_head */
			ew32(CTRL_EXT, adapter->tx_fअगरo_head);
			adapter->tx_fअगरo_head = 0;
		पूर्ण
		fallthrough;
	हाल e1000_82571:
	हाल e1000_82572:
		अगर (hw->phy.media_type == e1000_media_type_fiber ||
		    hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
			ew32(SCTL, E1000_SCTL_DISABLE_SERDES_LOOPBACK);
			e1e_flush();
			usleep_range(10000, 11000);
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		hw->mac.स्वतःneg = 1;
		अगर (hw->phy.type == e1000_phy_gg82563)
			e1e_wphy(hw, GG82563_PHY_KMRN_MODE_CTRL, 0x180);
		e1e_rphy(hw, MII_BMCR, &phy_reg);
		अगर (phy_reg & BMCR_LOOPBACK) अणु
			phy_reg &= ~BMCR_LOOPBACK;
			e1e_wphy(hw, MII_BMCR, phy_reg);
			अगर (hw->phy.ops.commit)
				hw->phy.ops.commit(hw);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम e1000_create_lbtest_frame(काष्ठा sk_buff *skb,
				      अचिन्हित पूर्णांक frame_size)
अणु
	स_रखो(skb->data, 0xFF, frame_size);
	frame_size &= ~1;
	स_रखो(&skb->data[frame_size / 2], 0xAA, frame_size / 2 - 1);
	skb->data[frame_size / 2 + 10] = 0xBE;
	skb->data[frame_size / 2 + 12] = 0xAF;
पूर्ण

अटल पूर्णांक e1000_check_lbtest_frame(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक frame_size)
अणु
	frame_size &= ~1;
	अगर (*(skb->data + 3) == 0xFF)
		अगर ((*(skb->data + frame_size / 2 + 10) == 0xBE) &&
		    (*(skb->data + frame_size / 2 + 12) == 0xAF))
			वापस 0;
	वापस 13;
पूर्ण

अटल पूर्णांक e1000_run_loopback_test(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_ring *tx_ring = &adapter->test_tx_ring;
	काष्ठा e1000_ring *rx_ring = &adapter->test_rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_buffer *buffer_info;
	पूर्णांक i, j, k, l;
	पूर्णांक lc;
	पूर्णांक good_cnt;
	पूर्णांक ret_val = 0;
	अचिन्हित दीर्घ समय;

	ew32(RDT(0), rx_ring->count - 1);

	/* Calculate the loop count based on the largest descriptor ring
	 * The idea is to wrap the largest ring a number of बार using 64
	 * send/receive pairs during each loop
	 */

	अगर (rx_ring->count <= tx_ring->count)
		lc = ((tx_ring->count / 64) * 2) + 1;
	अन्यथा
		lc = ((rx_ring->count / 64) * 2) + 1;

	k = 0;
	l = 0;
	/* loop count loop */
	क्रम (j = 0; j <= lc; j++) अणु
		/* send the packets */
		क्रम (i = 0; i < 64; i++) अणु
			buffer_info = &tx_ring->buffer_info[k];

			e1000_create_lbtest_frame(buffer_info->skb, 1024);
			dma_sync_single_क्रम_device(&pdev->dev,
						   buffer_info->dma,
						   buffer_info->length,
						   DMA_TO_DEVICE);
			k++;
			अगर (k == tx_ring->count)
				k = 0;
		पूर्ण
		ew32(TDT(0), k);
		e1e_flush();
		msleep(200);
		समय = jअगरfies;	/* set the start समय क्रम the receive */
		good_cnt = 0;
		/* receive the sent packets */
		करो अणु
			buffer_info = &rx_ring->buffer_info[l];

			dma_sync_single_क्रम_cpu(&pdev->dev,
						buffer_info->dma, 2048,
						DMA_FROM_DEVICE);

			ret_val = e1000_check_lbtest_frame(buffer_info->skb,
							   1024);
			अगर (!ret_val)
				good_cnt++;
			l++;
			अगर (l == rx_ring->count)
				l = 0;
			/* समय + 20 msecs (200 msecs on 2.4) is more than
			 * enough समय to complete the receives, अगर it's
			 * exceeded, अवरोध and error off
			 */
		पूर्ण जबतक ((good_cnt < 64) && !समय_after(jअगरfies, समय + 20));
		अगर (good_cnt != 64) अणु
			ret_val = 13;	/* ret_val is the same as mis-compare */
			अवरोध;
		पूर्ण
		अगर (समय_after(jअगरfies, समय + 20)) अणु
			ret_val = 14;	/* error code क्रम समय out error */
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret_val;
पूर्ण

अटल पूर्णांक e1000_loopback_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* PHY loopback cannot be perक्रमmed अगर SoL/IDER sessions are active */
	अगर (hw->phy.ops.check_reset_block &&
	    hw->phy.ops.check_reset_block(hw)) अणु
		e_err("Cannot do PHY loopback test when SoL/IDER is active.\n");
		*data = 0;
		जाओ out;
	पूर्ण

	*data = e1000_setup_desc_rings(adapter);
	अगर (*data)
		जाओ out;

	*data = e1000_setup_loopback_test(adapter);
	अगर (*data)
		जाओ err_loopback;

	*data = e1000_run_loopback_test(adapter);
	e1000_loopback_cleanup(adapter);

err_loopback:
	e1000_मुक्त_desc_rings(adapter);
out:
	वापस *data;
पूर्ण

अटल पूर्णांक e1000_link_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	*data = 0;
	अगर (hw->phy.media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
		पूर्णांक i = 0;

		hw->mac.serdes_has_link = false;

		/* On some blade server designs, link establishment
		 * could take as दीर्घ as 2-3 minutes
		 */
		करो अणु
			hw->mac.ops.check_क्रम_link(hw);
			अगर (hw->mac.serdes_has_link)
				वापस *data;
			msleep(20);
		पूर्ण जबतक (i++ < 3750);

		*data = 1;
	पूर्ण अन्यथा अणु
		hw->mac.ops.check_क्रम_link(hw);
		अगर (hw->mac.स्वतःneg)
			/* On some Phy/चयन combinations, link establishment
			 * can take a few seconds more than expected.
			 */
			msleep_पूर्णांकerruptible(5000);

		अगर (!(er32(STATUS) & E1000_STATUS_LU))
			*data = 1;
	पूर्ण
	वापस *data;
पूर्ण

अटल पूर्णांक e1000e_get_sset_count(काष्ठा net_device __always_unused *netdev,
				 पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस E1000_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस E1000_STATS_LEN;
	हाल ETH_SS_PRIV_FLAGS:
		वापस E1000E_PRIV_FLAGS_STR_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम e1000_diag_test(काष्ठा net_device *netdev,
			    काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	u16 स्वतःneg_advertised;
	u8 क्रमced_speed_duplex;
	u8 स्वतःneg;
	bool अगर_running = netअगर_running(netdev);

	pm_runसमय_get_sync(netdev->dev.parent);

	set_bit(__E1000_TESTING, &adapter->state);

	अगर (!अगर_running) अणु
		/* Get control of and reset hardware */
		अगर (adapter->flags & FLAG_HAS_AMT)
			e1000e_get_hw_control(adapter);

		e1000e_घातer_up_phy(adapter);

		adapter->hw.phy.स्वतःneg_रुको_to_complete = 1;
		e1000e_reset(adapter);
		adapter->hw.phy.स्वतःneg_रुको_to_complete = 0;
	पूर्ण

	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		/* Offline tests */

		/* save speed, duplex, स्वतःneg settings */
		स्वतःneg_advertised = adapter->hw.phy.स्वतःneg_advertised;
		क्रमced_speed_duplex = adapter->hw.mac.क्रमced_speed_duplex;
		स्वतःneg = adapter->hw.mac.स्वतःneg;

		e_info("offline testing starting\n");

		अगर (अगर_running)
			/* indicate we're in test mode */
			e1000e_बंद(netdev);

		अगर (e1000_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000e_reset(adapter);
		अगर (e1000_eeprom_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000e_reset(adapter);
		अगर (e1000_पूर्णांकr_test(adapter, &data[2]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000e_reset(adapter);
		अगर (e1000_loopback_test(adapter, &data[3]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* क्रमce this routine to रुको until स्वतःneg complete/समयout */
		adapter->hw.phy.स्वतःneg_रुको_to_complete = 1;
		e1000e_reset(adapter);
		adapter->hw.phy.स्वतःneg_रुको_to_complete = 0;

		अगर (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* restore speed, duplex, स्वतःneg settings */
		adapter->hw.phy.स्वतःneg_advertised = स्वतःneg_advertised;
		adapter->hw.mac.क्रमced_speed_duplex = क्रमced_speed_duplex;
		adapter->hw.mac.स्वतःneg = स्वतःneg;
		e1000e_reset(adapter);

		clear_bit(__E1000_TESTING, &adapter->state);
		अगर (अगर_running)
			e1000e_खोलो(netdev);
	पूर्ण अन्यथा अणु
		/* Online tests */

		e_info("online testing starting\n");

		/* रेजिस्टर, eeprom, पूर्णांकr and loopback tests not run online */
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;

		अगर (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		clear_bit(__E1000_TESTING, &adapter->state);
	पूर्ण

	अगर (!अगर_running) अणु
		e1000e_reset(adapter);

		अगर (adapter->flags & FLAG_HAS_AMT)
			e1000e_release_hw_control(adapter);
	पूर्ण

	msleep_पूर्णांकerruptible(4 * 1000);

	pm_runसमय_put_sync(netdev->dev.parent);
पूर्ण

अटल व्योम e1000_get_wol(काष्ठा net_device *netdev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	wol->supported = 0;
	wol->wolopts = 0;

	अगर (!(adapter->flags & FLAG_HAS_WOL) ||
	    !device_can_wakeup(&adapter->pdev->dev))
		वापस;

	wol->supported = WAKE_UCAST | WAKE_MCAST |
	    WAKE_BCAST | WAKE_MAGIC | WAKE_PHY;

	/* apply any specअगरic unsupported masks here */
	अगर (adapter->flags & FLAG_NO_WAKE_UCAST) अणु
		wol->supported &= ~WAKE_UCAST;

		अगर (adapter->wol & E1000_WUFC_EX)
			e_err("Interface does not support directed (unicast) frame wake-up packets\n");
	पूर्ण

	अगर (adapter->wol & E1000_WUFC_EX)
		wol->wolopts |= WAKE_UCAST;
	अगर (adapter->wol & E1000_WUFC_MC)
		wol->wolopts |= WAKE_MCAST;
	अगर (adapter->wol & E1000_WUFC_BC)
		wol->wolopts |= WAKE_BCAST;
	अगर (adapter->wol & E1000_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
	अगर (adapter->wol & E1000_WUFC_LNKC)
		wol->wolopts |= WAKE_PHY;
पूर्ण

अटल पूर्णांक e1000_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (!(adapter->flags & FLAG_HAS_WOL) ||
	    !device_can_wakeup(&adapter->pdev->dev) ||
	    (wol->wolopts & ~(WAKE_UCAST | WAKE_MCAST | WAKE_BCAST |
			      WAKE_MAGIC | WAKE_PHY)))
		वापस -EOPNOTSUPP;

	/* these settings will always override what we currently have */
	adapter->wol = 0;

	अगर (wol->wolopts & WAKE_UCAST)
		adapter->wol |= E1000_WUFC_EX;
	अगर (wol->wolopts & WAKE_MCAST)
		adapter->wol |= E1000_WUFC_MC;
	अगर (wol->wolopts & WAKE_BCAST)
		adapter->wol |= E1000_WUFC_BC;
	अगर (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= E1000_WUFC_MAG;
	अगर (wol->wolopts & WAKE_PHY)
		adapter->wol |= E1000_WUFC_LNKC;

	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_set_phys_id(काष्ठा net_device *netdev,
			     क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		pm_runसमय_get_sync(netdev->dev.parent);

		अगर (!hw->mac.ops.blink_led)
			वापस 2;	/* cycle on/off twice per second */

		hw->mac.ops.blink_led(hw);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		अगर (hw->phy.type == e1000_phy_अगरe)
			e1e_wphy(hw, IFE_PHY_SPECIAL_CONTROL_LED, 0);
		hw->mac.ops.led_off(hw);
		hw->mac.ops.cleanup_led(hw);
		pm_runसमय_put_sync(netdev->dev.parent);
		अवरोध;

	हाल ETHTOOL_ID_ON:
		hw->mac.ops.led_on(hw);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		hw->mac.ops.led_off(hw);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->itr_setting <= 4)
		ec->rx_coalesce_usecs = adapter->itr_setting;
	अन्यथा
		ec->rx_coalesce_usecs = 1000000 / adapter->itr_setting;

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर ((ec->rx_coalesce_usecs > E1000_MAX_ITR_USECS) ||
	    ((ec->rx_coalesce_usecs > 4) &&
	     (ec->rx_coalesce_usecs < E1000_MIN_ITR_USECS)) ||
	    (ec->rx_coalesce_usecs == 2))
		वापस -EINVAL;

	अगर (ec->rx_coalesce_usecs == 4) अणु
		adapter->itr_setting = 4;
		adapter->itr = adapter->itr_setting;
	पूर्ण अन्यथा अगर (ec->rx_coalesce_usecs <= 3) अणु
		adapter->itr = 20000;
		adapter->itr_setting = ec->rx_coalesce_usecs;
	पूर्ण अन्यथा अणु
		adapter->itr = (1000000 / ec->rx_coalesce_usecs);
		adapter->itr_setting = adapter->itr & ~3;
	पूर्ण

	pm_runसमय_get_sync(netdev->dev.parent);

	अगर (adapter->itr_setting != 0)
		e1000e_ग_लिखो_itr(adapter, adapter->itr);
	अन्यथा
		e1000e_ग_लिखो_itr(adapter, 0);

	pm_runसमय_put_sync(netdev->dev.parent);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (!netअगर_running(netdev))
		वापस -EAGAIN;

	अगर (!adapter->hw.mac.स्वतःneg)
		वापस -EINVAL;

	pm_runसमय_get_sync(netdev->dev.parent);
	e1000e_reinit_locked(adapter);
	pm_runसमय_put_sync(netdev->dev.parent);

	वापस 0;
पूर्ण

अटल व्योम e1000_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats __always_unused *stats,
				    u64 *data)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा rtnl_link_stats64 net_stats;
	पूर्णांक i;
	अक्षर *p = शून्य;

	pm_runसमय_get_sync(netdev->dev.parent);

	dev_get_stats(netdev, &net_stats);

	pm_runसमय_put_sync(netdev->dev.parent);

	क्रम (i = 0; i < E1000_GLOBAL_STATS_LEN; i++) अणु
		चयन (e1000_gstrings_stats[i].type) अणु
		हाल NETDEV_STATS:
			p = (अक्षर *)&net_stats +
			    e1000_gstrings_stats[i].stat_offset;
			अवरोध;
		हाल E1000_STATS:
			p = (अक्षर *)adapter +
			    e1000_gstrings_stats[i].stat_offset;
			अवरोध;
		शेष:
			data[i] = 0;
			जारी;
		पूर्ण

		data[i] = (e1000_gstrings_stats[i].माप_stat ==
			   माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
पूर्ण

अटल व्योम e1000_get_strings(काष्ठा net_device __always_unused *netdev,
			      u32 stringset, u8 *data)
अणु
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, e1000_gstrings_test, माप(e1000_gstrings_test));
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < E1000_GLOBAL_STATS_LEN; i++) अणु
			स_नकल(p, e1000_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(data, e1000e_priv_flags_strings,
		       E1000E_PRIV_FLAGS_STR_LEN * ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक e1000_get_rxnfc(काष्ठा net_device *netdev,
			   काष्ठा ethtool_rxnfc *info,
			   u32 __always_unused *rule_locs)
अणु
	info->data = 0;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXFH: अणु
		काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
		काष्ठा e1000_hw *hw = &adapter->hw;
		u32 mrqc;

		pm_runसमय_get_sync(netdev->dev.parent);
		mrqc = er32(MRQC);
		pm_runसमय_put_sync(netdev->dev.parent);

		अगर (!(mrqc & E1000_MRQC_RSS_FIELD_MASK))
			वापस 0;

		चयन (info->flow_type) अणु
		हाल TCP_V4_FLOW:
			अगर (mrqc & E1000_MRQC_RSS_FIELD_IPV4_TCP)
				info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
			fallthrough;
		हाल UDP_V4_FLOW:
		हाल SCTP_V4_FLOW:
		हाल AH_ESP_V4_FLOW:
		हाल IPV4_FLOW:
			अगर (mrqc & E1000_MRQC_RSS_FIELD_IPV4)
				info->data |= RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		हाल TCP_V6_FLOW:
			अगर (mrqc & E1000_MRQC_RSS_FIELD_IPV6_TCP)
				info->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
			fallthrough;
		हाल UDP_V6_FLOW:
		हाल SCTP_V6_FLOW:
		हाल AH_ESP_V6_FLOW:
		हाल IPV6_FLOW:
			अगर (mrqc & E1000_MRQC_RSS_FIELD_IPV6)
				info->data |= RXH_IP_SRC | RXH_IP_DST;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		वापस 0;
	पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक e1000e_get_eee(काष्ठा net_device *netdev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 cap_addr, lpa_addr, pcs_stat_addr, phy_data;
	u32 ret_val;

	अगर (!(adapter->flags2 & FLAG2_HAS_EEE))
		वापस -EOPNOTSUPP;

	चयन (hw->phy.type) अणु
	हाल e1000_phy_82579:
		cap_addr = I82579_EEE_CAPABILITY;
		lpa_addr = I82579_EEE_LP_ABILITY;
		pcs_stat_addr = I82579_EEE_PCS_STATUS;
		अवरोध;
	हाल e1000_phy_i217:
		cap_addr = I217_EEE_CAPABILITY;
		lpa_addr = I217_EEE_LP_ABILITY;
		pcs_stat_addr = I217_EEE_PCS_STATUS;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	pm_runसमय_get_sync(netdev->dev.parent);

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val) अणु
		pm_runसमय_put_sync(netdev->dev.parent);
		वापस -EBUSY;
	पूर्ण

	/* EEE Capability */
	ret_val = e1000_पढ़ो_emi_reg_locked(hw, cap_addr, &phy_data);
	अगर (ret_val)
		जाओ release;
	edata->supported = mmd_eee_cap_to_ethtool_sup_t(phy_data);

	/* EEE Advertised */
	edata->advertised = mmd_eee_adv_to_ethtool_adv_t(adapter->eee_advert);

	/* EEE Link Partner Advertised */
	ret_val = e1000_पढ़ो_emi_reg_locked(hw, lpa_addr, &phy_data);
	अगर (ret_val)
		जाओ release;
	edata->lp_advertised = mmd_eee_adv_to_ethtool_adv_t(phy_data);

	/* EEE PCS Status */
	ret_val = e1000_पढ़ो_emi_reg_locked(hw, pcs_stat_addr, &phy_data);
	अगर (ret_val)
		जाओ release;
	अगर (hw->phy.type == e1000_phy_82579)
		phy_data <<= 8;

	/* Result of the EEE स्वतः negotiation - there is no रेजिस्टर that
	 * has the status of the EEE negotiation so करो a best-guess based
	 * on whether Tx or Rx LPI indications have been received.
	 */
	अगर (phy_data & (E1000_EEE_TX_LPI_RCVD | E1000_EEE_RX_LPI_RCVD))
		edata->eee_active = true;

	edata->eee_enabled = !hw->dev_spec.ich8lan.eee_disable;
	edata->tx_lpi_enabled = true;
	edata->tx_lpi_समयr = er32(LPIC) >> E1000_LPIC_LPIET_SHIFT;

release:
	hw->phy.ops.release(hw);
	अगर (ret_val)
		ret_val = -ENODATA;

	pm_runसमय_put_sync(netdev->dev.parent);

	वापस ret_val;
पूर्ण

अटल पूर्णांक e1000e_set_eee(काष्ठा net_device *netdev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा ethtool_eee eee_curr;
	s32 ret_val;

	ret_val = e1000e_get_eee(netdev, &eee_curr);
	अगर (ret_val)
		वापस ret_val;

	अगर (eee_curr.tx_lpi_enabled != edata->tx_lpi_enabled) अणु
		e_err("Setting EEE tx-lpi is not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (eee_curr.tx_lpi_समयr != edata->tx_lpi_समयr) अणु
		e_err("Setting EEE Tx LPI timer is not supported\n");
		वापस -EINVAL;
	पूर्ण

	अगर (edata->advertised & ~(ADVERTISE_100_FULL | ADVERTISE_1000_FULL)) अणु
		e_err("EEE advertisement supports only 100TX and/or 1000T full-duplex\n");
		वापस -EINVAL;
	पूर्ण

	adapter->eee_advert = ethtool_adv_to_mmd_eee_adv_t(edata->advertised);

	hw->dev_spec.ich8lan.eee_disable = !edata->eee_enabled;

	pm_runसमय_get_sync(netdev->dev.parent);

	/* reset the link */
	अगर (netअगर_running(netdev))
		e1000e_reinit_locked(adapter);
	अन्यथा
		e1000e_reset(adapter);

	pm_runसमय_put_sync(netdev->dev.parent);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000e_get_ts_info(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	ethtool_op_get_ts_info(netdev, info);

	अगर (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		वापस 0;

	info->so_बारtamping |= (SOF_TIMESTAMPING_TX_HARDWARE |
				  SOF_TIMESTAMPING_RX_HARDWARE |
				  SOF_TIMESTAMPING_RAW_HARDWARE);

	info->tx_types = BIT(HWTSTAMP_TX_OFF) | BIT(HWTSTAMP_TX_ON);

	info->rx_filters = (BIT(HWTSTAMP_FILTER_NONE) |
			    BIT(HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
			    BIT(HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_L4_SYNC) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_L2_SYNC) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_EVENT) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_SYNC) |
			    BIT(HWTSTAMP_FILTER_PTP_V2_DELAY_REQ) |
			    BIT(HWTSTAMP_FILTER_ALL));

	अगर (adapter->ptp_घड़ी)
		info->phc_index = ptp_घड़ी_index(adapter->ptp_घड़ी);

	वापस 0;
पूर्ण

अटल u32 e1000e_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	u32 priv_flags = 0;

	अगर (adapter->flags2 & FLAG2_ENABLE_S0IX_FLOWS)
		priv_flags |= E1000E_PRIV_FLAGS_S0IX_ENABLED;

	वापस priv_flags;
पूर्ण

अटल पूर्णांक e1000e_set_priv_flags(काष्ठा net_device *netdev, u32 priv_flags)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक flags2 = adapter->flags2;

	flags2 &= ~FLAG2_ENABLE_S0IX_FLOWS;
	अगर (priv_flags & E1000E_PRIV_FLAGS_S0IX_ENABLED) अणु
		काष्ठा e1000_hw *hw = &adapter->hw;

		अगर (hw->mac.type < e1000_pch_cnp)
			वापस -EINVAL;
		flags2 |= FLAG2_ENABLE_S0IX_FLOWS;
	पूर्ण

	अगर (flags2 != adapter->flags2)
		adapter->flags2 = flags2;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops e1000_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS,
	.get_drvinfo		= e1000_get_drvinfo,
	.get_regs_len		= e1000_get_regs_len,
	.get_regs		= e1000_get_regs,
	.get_wol		= e1000_get_wol,
	.set_wol		= e1000_set_wol,
	.get_msglevel		= e1000_get_msglevel,
	.set_msglevel		= e1000_set_msglevel,
	.nway_reset		= e1000_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= e1000_get_eeprom_len,
	.get_eeprom		= e1000_get_eeprom,
	.set_eeprom		= e1000_set_eeprom,
	.get_ringparam		= e1000_get_ringparam,
	.set_ringparam		= e1000_set_ringparam,
	.get_छोड़ोparam		= e1000_get_छोड़ोparam,
	.set_छोड़ोparam		= e1000_set_छोड़ोparam,
	.self_test		= e1000_diag_test,
	.get_strings		= e1000_get_strings,
	.set_phys_id		= e1000_set_phys_id,
	.get_ethtool_stats	= e1000_get_ethtool_stats,
	.get_sset_count		= e1000e_get_sset_count,
	.get_coalesce		= e1000_get_coalesce,
	.set_coalesce		= e1000_set_coalesce,
	.get_rxnfc		= e1000_get_rxnfc,
	.get_ts_info		= e1000e_get_ts_info,
	.get_eee		= e1000e_get_eee,
	.set_eee		= e1000e_set_eee,
	.get_link_ksettings	= e1000_get_link_ksettings,
	.set_link_ksettings	= e1000_set_link_ksettings,
	.get_priv_flags		= e1000e_get_priv_flags,
	.set_priv_flags		= e1000e_set_priv_flags,
पूर्ण;

व्योम e1000e_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &e1000_ethtool_ops;
पूर्ण
