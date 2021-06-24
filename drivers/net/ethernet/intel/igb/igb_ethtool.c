<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007 - 2018 Intel Corporation. */

/* ethtool support क्रम igb */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mdपन.स>

#समावेश "igb.h"

काष्ठा igb_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा IGB_STAT(_name, _stat) अणु \
	.stat_string = _name, \
	.माप_stat = माप_field(काष्ठा igb_adapter, _stat), \
	.stat_offset = दुरत्व(काष्ठा igb_adapter, _stat) \
पूर्ण
अटल स्थिर काष्ठा igb_stats igb_gstrings_stats[] = अणु
	IGB_STAT("rx_packets", stats.gprc),
	IGB_STAT("tx_packets", stats.gptc),
	IGB_STAT("rx_bytes", stats.gorc),
	IGB_STAT("tx_bytes", stats.gotc),
	IGB_STAT("rx_broadcast", stats.bprc),
	IGB_STAT("tx_broadcast", stats.bptc),
	IGB_STAT("rx_multicast", stats.mprc),
	IGB_STAT("tx_multicast", stats.mptc),
	IGB_STAT("multicast", stats.mprc),
	IGB_STAT("collisions", stats.colc),
	IGB_STAT("rx_crc_errors", stats.crcerrs),
	IGB_STAT("rx_no_buffer_count", stats.rnbc),
	IGB_STAT("rx_missed_errors", stats.mpc),
	IGB_STAT("tx_aborted_errors", stats.ecol),
	IGB_STAT("tx_carrier_errors", stats.tncrs),
	IGB_STAT("tx_window_errors", stats.latecol),
	IGB_STAT("tx_abort_late_coll", stats.latecol),
	IGB_STAT("tx_deferred_ok", stats.dc),
	IGB_STAT("tx_single_coll_ok", stats.scc),
	IGB_STAT("tx_multi_coll_ok", stats.mcc),
	IGB_STAT("tx_timeout_count", tx_समयout_count),
	IGB_STAT("rx_long_length_errors", stats.roc),
	IGB_STAT("rx_short_length_errors", stats.ruc),
	IGB_STAT("rx_align_errors", stats.algnerrc),
	IGB_STAT("tx_tcp_seg_good", stats.tsctc),
	IGB_STAT("tx_tcp_seg_failed", stats.tsctfc),
	IGB_STAT("rx_flow_control_xon", stats.xonrxc),
	IGB_STAT("rx_flow_control_xoff", stats.xoffrxc),
	IGB_STAT("tx_flow_control_xon", stats.xontxc),
	IGB_STAT("tx_flow_control_xoff", stats.xofftxc),
	IGB_STAT("rx_long_byte_count", stats.gorc),
	IGB_STAT("tx_dma_out_of_sync", stats.करोosync),
	IGB_STAT("tx_smbus", stats.mgptc),
	IGB_STAT("rx_smbus", stats.mgprc),
	IGB_STAT("dropped_smbus", stats.mgpdc),
	IGB_STAT("os2bmc_rx_by_bmc", stats.o2bgptc),
	IGB_STAT("os2bmc_tx_by_bmc", stats.b2ospc),
	IGB_STAT("os2bmc_tx_by_host", stats.o2bspc),
	IGB_STAT("os2bmc_rx_by_host", stats.b2ogprc),
	IGB_STAT("tx_hwtstamp_timeouts", tx_hwtstamp_समयouts),
	IGB_STAT("tx_hwtstamp_skipped", tx_hwtstamp_skipped),
	IGB_STAT("rx_hwtstamp_cleared", rx_hwtstamp_cleared),
पूर्ण;

#घोषणा IGB_NETDEV_STAT(_net_stat) अणु \
	.stat_string = __stringअगरy(_net_stat), \
	.माप_stat = माप_field(काष्ठा rtnl_link_stats64, _net_stat), \
	.stat_offset = दुरत्व(काष्ठा rtnl_link_stats64, _net_stat) \
पूर्ण
अटल स्थिर काष्ठा igb_stats igb_gstrings_net_stats[] = अणु
	IGB_NETDEV_STAT(rx_errors),
	IGB_NETDEV_STAT(tx_errors),
	IGB_NETDEV_STAT(tx_dropped),
	IGB_NETDEV_STAT(rx_length_errors),
	IGB_NETDEV_STAT(rx_over_errors),
	IGB_NETDEV_STAT(rx_frame_errors),
	IGB_NETDEV_STAT(rx_fअगरo_errors),
	IGB_NETDEV_STAT(tx_fअगरo_errors),
	IGB_NETDEV_STAT(tx_heartbeat_errors)
पूर्ण;

#घोषणा IGB_GLOBAL_STATS_LEN	\
	(माप(igb_gstrings_stats) / माप(काष्ठा igb_stats))
#घोषणा IGB_NETDEV_STATS_LEN	\
	(माप(igb_gstrings_net_stats) / माप(काष्ठा igb_stats))
#घोषणा IGB_RX_QUEUE_STATS_LEN \
	(माप(काष्ठा igb_rx_queue_stats) / माप(u64))

#घोषणा IGB_TX_QUEUE_STATS_LEN 3 /* packets, bytes, restart_queue */

#घोषणा IGB_QUEUE_STATS_LEN \
	((((काष्ठा igb_adapter *)netdev_priv(netdev))->num_rx_queues * \
	  IGB_RX_QUEUE_STATS_LEN) + \
	 (((काष्ठा igb_adapter *)netdev_priv(netdev))->num_tx_queues * \
	  IGB_TX_QUEUE_STATS_LEN))
#घोषणा IGB_STATS_LEN \
	(IGB_GLOBAL_STATS_LEN + IGB_NETDEV_STATS_LEN + IGB_QUEUE_STATS_LEN)

क्रमागत igb_diagnostics_results अणु
	TEST_REG = 0,
	TEST_EEP,
	TEST_IRQ,
	TEST_LOOP,
	TEST_LINK
पूर्ण;

अटल स्थिर अक्षर igb_gstrings_test[][ETH_GSTRING_LEN] = अणु
	[TEST_REG]  = "Register test  (offline)",
	[TEST_EEP]  = "Eeprom test    (offline)",
	[TEST_IRQ]  = "Interrupt test (offline)",
	[TEST_LOOP] = "Loopback test  (offline)",
	[TEST_LINK] = "Link test   (on/offline)"
पूर्ण;
#घोषणा IGB_TEST_LEN (माप(igb_gstrings_test) / ETH_GSTRING_LEN)

अटल स्थिर अक्षर igb_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
#घोषणा IGB_PRIV_FLAGS_LEGACY_RX	BIT(0)
	"legacy-rx",
पूर्ण;

#घोषणा IGB_PRIV_FLAGS_STR_LEN ARRAY_SIZE(igb_priv_flags_strings)

अटल पूर्णांक igb_get_link_ksettings(काष्ठा net_device *netdev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_dev_spec_82575 *dev_spec = &hw->dev_spec._82575;
	काष्ठा e1000_sfp_flags *eth_flags = &dev_spec->eth_flags;
	u32 status;
	u32 speed;
	u32 supported, advertising;

	status = pm_runसमय_suspended(&adapter->pdev->dev) ?
		 0 : rd32(E1000_STATUS);
	अगर (hw->phy.media_type == e1000_media_type_copper) अणु

		supported = (SUPPORTED_10baseT_Half |
			     SUPPORTED_10baseT_Full |
			     SUPPORTED_100baseT_Half |
			     SUPPORTED_100baseT_Full |
			     SUPPORTED_1000baseT_Full|
			     SUPPORTED_Autoneg |
			     SUPPORTED_TP |
			     SUPPORTED_Pause);
		advertising = ADVERTISED_TP;

		अगर (hw->mac.स्वतःneg == 1) अणु
			advertising |= ADVERTISED_Autoneg;
			/* the e1000 स्वतःneg seems to match ethtool nicely */
			advertising |= hw->phy.स्वतःneg_advertised;
		पूर्ण

		cmd->base.port = PORT_TP;
		cmd->base.phy_address = hw->phy.addr;
	पूर्ण अन्यथा अणु
		supported = (SUPPORTED_FIBRE |
			     SUPPORTED_1000baseKX_Full |
			     SUPPORTED_Autoneg |
			     SUPPORTED_Pause);
		advertising = (ADVERTISED_FIBRE |
			       ADVERTISED_1000baseKX_Full);
		अगर (hw->mac.type == e1000_i354) अणु
			अगर ((hw->device_id ==
			     E1000_DEV_ID_I354_BACKPLANE_2_5GBPS) &&
			    !(status & E1000_STATUS_2P5_SKU_OVER)) अणु
				supported |= SUPPORTED_2500baseX_Full;
				supported &= ~SUPPORTED_1000baseKX_Full;
				advertising |= ADVERTISED_2500baseX_Full;
				advertising &= ~ADVERTISED_1000baseKX_Full;
			पूर्ण
		पूर्ण
		अगर (eth_flags->e100_base_fx || eth_flags->e100_base_lx) अणु
			supported |= SUPPORTED_100baseT_Full;
			advertising |= ADVERTISED_100baseT_Full;
		पूर्ण
		अगर (hw->mac.स्वतःneg == 1)
			advertising |= ADVERTISED_Autoneg;

		cmd->base.port = PORT_FIBRE;
	पूर्ण
	अगर (hw->mac.स्वतःneg != 1)
		advertising &= ~(ADVERTISED_Pause |
				 ADVERTISED_Asym_Pause);

	चयन (hw->fc.requested_mode) अणु
	हाल e1000_fc_full:
		advertising |= ADVERTISED_Pause;
		अवरोध;
	हाल e1000_fc_rx_छोड़ो:
		advertising |= (ADVERTISED_Pause |
				ADVERTISED_Asym_Pause);
		अवरोध;
	हाल e1000_fc_tx_छोड़ो:
		advertising |=  ADVERTISED_Asym_Pause;
		अवरोध;
	शेष:
		advertising &= ~(ADVERTISED_Pause |
				 ADVERTISED_Asym_Pause);
	पूर्ण
	अगर (status & E1000_STATUS_LU) अणु
		अगर ((status & E1000_STATUS_2P5_SKU) &&
		    !(status & E1000_STATUS_2P5_SKU_OVER)) अणु
			speed = SPEED_2500;
		पूर्ण अन्यथा अगर (status & E1000_STATUS_SPEED_1000) अणु
			speed = SPEED_1000;
		पूर्ण अन्यथा अगर (status & E1000_STATUS_SPEED_100) अणु
			speed = SPEED_100;
		पूर्ण अन्यथा अणु
			speed = SPEED_10;
		पूर्ण
		अगर ((status & E1000_STATUS_FD) ||
		    hw->phy.media_type != e1000_media_type_copper)
			cmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			cmd->base.duplex = DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	cmd->base.speed = speed;
	अगर ((hw->phy.media_type == e1000_media_type_fiber) ||
	    hw->mac.स्वतःneg)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	/* MDI-X => 2; MDI =>1; Invalid =>0 */
	अगर (hw->phy.media_type == e1000_media_type_copper)
		cmd->base.eth_tp_mdix = hw->phy.is_mdix ? ETH_TP_MDI_X :
						      ETH_TP_MDI;
	अन्यथा
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;

	अगर (hw->phy.mdix == AUTO_ALL_MODES)
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;
	अन्यथा
		cmd->base.eth_tp_mdix_ctrl = hw->phy.mdix;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_set_link_ksettings(काष्ठा net_device *netdev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 advertising;

	/* When SoL/IDER sessions are active, स्वतःneg/speed/duplex
	 * cannot be changed
	 */
	अगर (igb_check_reset_block(hw)) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot change link characteristics when SoL/IDER is active.\n");
		वापस -EINVAL;
	पूर्ण

	/* MDI setting is only allowed when स्वतःneg enabled because
	 * some hardware करोesn't allow MDI setting when speed or
	 * duplex is क्रमced.
	 */
	अगर (cmd->base.eth_tp_mdix_ctrl) अणु
		अगर (hw->phy.media_type != e1000_media_type_copper)
			वापस -EOPNOTSUPP;

		अगर ((cmd->base.eth_tp_mdix_ctrl != ETH_TP_MDI_AUTO) &&
		    (cmd->base.स्वतःneg != AUTONEG_ENABLE)) अणु
			dev_err(&adapter->pdev->dev, "forcing MDI/MDI-X state is not supported when link speed and/or duplex are forced\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	जबतक (test_and_set_bit(__IGB_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		hw->mac.स्वतःneg = 1;
		अगर (hw->phy.media_type == e1000_media_type_fiber) अणु
			hw->phy.स्वतःneg_advertised = advertising |
						     ADVERTISED_FIBRE |
						     ADVERTISED_Autoneg;
			चयन (adapter->link_speed) अणु
			हाल SPEED_2500:
				hw->phy.स्वतःneg_advertised =
					ADVERTISED_2500baseX_Full;
				अवरोध;
			हाल SPEED_1000:
				hw->phy.स्वतःneg_advertised =
					ADVERTISED_1000baseT_Full;
				अवरोध;
			हाल SPEED_100:
				hw->phy.स्वतःneg_advertised =
					ADVERTISED_100baseT_Full;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			hw->phy.स्वतःneg_advertised = advertising |
						     ADVERTISED_TP |
						     ADVERTISED_Autoneg;
		पूर्ण
		advertising = hw->phy.स्वतःneg_advertised;
		अगर (adapter->fc_स्वतःneg)
			hw->fc.requested_mode = e1000_fc_शेष;
	पूर्ण अन्यथा अणु
		u32 speed = cmd->base.speed;
		/* calling this overrides क्रमced MDI setting */
		अगर (igb_set_spd_dplx(adapter, speed, cmd->base.duplex)) अणु
			clear_bit(__IGB_RESETTING, &adapter->state);
			वापस -EINVAL;
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
		igb_करोwn(adapter);
		igb_up(adapter);
	पूर्ण अन्यथा
		igb_reset(adapter);

	clear_bit(__IGB_RESETTING, &adapter->state);
	वापस 0;
पूर्ण

अटल u32 igb_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;

	/* If the link is not reported up to netdev, पूर्णांकerrupts are disabled,
	 * and so the physical link state may have changed since we last
	 * looked. Set get_link_status to make sure that the true link
	 * state is पूर्णांकerrogated, rather than pulling a cached and possibly
	 * stale link state from the driver.
	 */
	अगर (!netअगर_carrier_ok(netdev))
		mac->get_link_status = 1;

	वापस igb_has_link(adapter);
पूर्ण

अटल व्योम igb_get_छोड़ोparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	छोड़ो->स्वतःneg =
		(adapter->fc_स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE);

	अगर (hw->fc.current_mode == e1000_fc_rx_छोड़ो)
		छोड़ो->rx_छोड़ो = 1;
	अन्यथा अगर (hw->fc.current_mode == e1000_fc_tx_छोड़ो)
		छोड़ो->tx_छोड़ो = 1;
	अन्यथा अगर (hw->fc.current_mode == e1000_fc_full) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक igb_set_छोड़ोparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक retval = 0;
	पूर्णांक i;

	/* 100basefx करोes not support setting link flow control */
	अगर (hw->dev_spec._82575.eth_flags.e100_base_fx)
		वापस -EINVAL;

	adapter->fc_स्वतःneg = छोड़ो->स्वतःneg;

	जबतक (test_and_set_bit(__IGB_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (adapter->fc_स्वतःneg == AUTONEG_ENABLE) अणु
		hw->fc.requested_mode = e1000_fc_शेष;
		अगर (netअगर_running(adapter->netdev)) अणु
			igb_करोwn(adapter);
			igb_up(adapter);
		पूर्ण अन्यथा अणु
			igb_reset(adapter);
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

		retval = ((hw->phy.media_type == e1000_media_type_copper) ?
			  igb_क्रमce_mac_fc(hw) : igb_setup_link(hw));

		/* Make sure SRRCTL considers new fc settings क्रम each ring */
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			काष्ठा igb_ring *ring = adapter->rx_ring[i];

			igb_setup_srrctl(adapter, ring);
		पूर्ण
	पूर्ण

	clear_bit(__IGB_RESETTING, &adapter->state);
	वापस retval;
पूर्ण

अटल u32 igb_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	वापस adapter->msg_enable;
पूर्ण

अटल व्योम igb_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	adapter->msg_enable = data;
पूर्ण

अटल पूर्णांक igb_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा IGB_REGS_LEN 740
	वापस IGB_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम igb_get_regs(काष्ठा net_device *netdev,
			 काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u8 i;

	स_रखो(p, 0, IGB_REGS_LEN * माप(u32));

	regs->version = (1u << 24) | (hw->revision_id << 16) | hw->device_id;

	/* General Registers */
	regs_buff[0] = rd32(E1000_CTRL);
	regs_buff[1] = rd32(E1000_STATUS);
	regs_buff[2] = rd32(E1000_CTRL_EXT);
	regs_buff[3] = rd32(E1000_MDIC);
	regs_buff[4] = rd32(E1000_SCTL);
	regs_buff[5] = rd32(E1000_CONNSW);
	regs_buff[6] = rd32(E1000_VET);
	regs_buff[7] = rd32(E1000_LEDCTL);
	regs_buff[8] = rd32(E1000_PBA);
	regs_buff[9] = rd32(E1000_PBS);
	regs_buff[10] = rd32(E1000_FRTIMER);
	regs_buff[11] = rd32(E1000_TCPTIMER);

	/* NVM Register */
	regs_buff[12] = rd32(E1000_EECD);

	/* Interrupt */
	/* Reading EICS क्रम EICR because they पढ़ो the
	 * same but EICS करोes not clear on पढ़ो
	 */
	regs_buff[13] = rd32(E1000_EICS);
	regs_buff[14] = rd32(E1000_EICS);
	regs_buff[15] = rd32(E1000_EIMS);
	regs_buff[16] = rd32(E1000_EIMC);
	regs_buff[17] = rd32(E1000_EIAC);
	regs_buff[18] = rd32(E1000_EIAM);
	/* Reading ICS क्रम ICR because they पढ़ो the
	 * same but ICS करोes not clear on पढ़ो
	 */
	regs_buff[19] = rd32(E1000_ICS);
	regs_buff[20] = rd32(E1000_ICS);
	regs_buff[21] = rd32(E1000_IMS);
	regs_buff[22] = rd32(E1000_IMC);
	regs_buff[23] = rd32(E1000_IAC);
	regs_buff[24] = rd32(E1000_IAM);
	regs_buff[25] = rd32(E1000_IMIRVP);

	/* Flow Control */
	regs_buff[26] = rd32(E1000_FCAL);
	regs_buff[27] = rd32(E1000_FCAH);
	regs_buff[28] = rd32(E1000_FCTTV);
	regs_buff[29] = rd32(E1000_FCRTL);
	regs_buff[30] = rd32(E1000_FCRTH);
	regs_buff[31] = rd32(E1000_FCRTV);

	/* Receive */
	regs_buff[32] = rd32(E1000_RCTL);
	regs_buff[33] = rd32(E1000_RXCSUM);
	regs_buff[34] = rd32(E1000_RLPML);
	regs_buff[35] = rd32(E1000_RFCTL);
	regs_buff[36] = rd32(E1000_MRQC);
	regs_buff[37] = rd32(E1000_VT_CTL);

	/* Transmit */
	regs_buff[38] = rd32(E1000_TCTL);
	regs_buff[39] = rd32(E1000_TCTL_EXT);
	regs_buff[40] = rd32(E1000_TIPG);
	regs_buff[41] = rd32(E1000_DTXCTL);

	/* Wake Up */
	regs_buff[42] = rd32(E1000_WUC);
	regs_buff[43] = rd32(E1000_WUFC);
	regs_buff[44] = rd32(E1000_WUS);
	regs_buff[45] = rd32(E1000_IPAV);
	regs_buff[46] = rd32(E1000_WUPL);

	/* MAC */
	regs_buff[47] = rd32(E1000_PCS_CFG0);
	regs_buff[48] = rd32(E1000_PCS_LCTL);
	regs_buff[49] = rd32(E1000_PCS_LSTAT);
	regs_buff[50] = rd32(E1000_PCS_ANADV);
	regs_buff[51] = rd32(E1000_PCS_LPAB);
	regs_buff[52] = rd32(E1000_PCS_NPTX);
	regs_buff[53] = rd32(E1000_PCS_LPABNP);

	/* Statistics */
	regs_buff[54] = adapter->stats.crcerrs;
	regs_buff[55] = adapter->stats.algnerrc;
	regs_buff[56] = adapter->stats.symerrs;
	regs_buff[57] = adapter->stats.rxerrc;
	regs_buff[58] = adapter->stats.mpc;
	regs_buff[59] = adapter->stats.scc;
	regs_buff[60] = adapter->stats.ecol;
	regs_buff[61] = adapter->stats.mcc;
	regs_buff[62] = adapter->stats.latecol;
	regs_buff[63] = adapter->stats.colc;
	regs_buff[64] = adapter->stats.dc;
	regs_buff[65] = adapter->stats.tncrs;
	regs_buff[66] = adapter->stats.sec;
	regs_buff[67] = adapter->stats.htdpmc;
	regs_buff[68] = adapter->stats.rlec;
	regs_buff[69] = adapter->stats.xonrxc;
	regs_buff[70] = adapter->stats.xontxc;
	regs_buff[71] = adapter->stats.xoffrxc;
	regs_buff[72] = adapter->stats.xofftxc;
	regs_buff[73] = adapter->stats.fcruc;
	regs_buff[74] = adapter->stats.prc64;
	regs_buff[75] = adapter->stats.prc127;
	regs_buff[76] = adapter->stats.prc255;
	regs_buff[77] = adapter->stats.prc511;
	regs_buff[78] = adapter->stats.prc1023;
	regs_buff[79] = adapter->stats.prc1522;
	regs_buff[80] = adapter->stats.gprc;
	regs_buff[81] = adapter->stats.bprc;
	regs_buff[82] = adapter->stats.mprc;
	regs_buff[83] = adapter->stats.gptc;
	regs_buff[84] = adapter->stats.gorc;
	regs_buff[86] = adapter->stats.gotc;
	regs_buff[88] = adapter->stats.rnbc;
	regs_buff[89] = adapter->stats.ruc;
	regs_buff[90] = adapter->stats.rfc;
	regs_buff[91] = adapter->stats.roc;
	regs_buff[92] = adapter->stats.rjc;
	regs_buff[93] = adapter->stats.mgprc;
	regs_buff[94] = adapter->stats.mgpdc;
	regs_buff[95] = adapter->stats.mgptc;
	regs_buff[96] = adapter->stats.tor;
	regs_buff[98] = adapter->stats.tot;
	regs_buff[100] = adapter->stats.tpr;
	regs_buff[101] = adapter->stats.tpt;
	regs_buff[102] = adapter->stats.ptc64;
	regs_buff[103] = adapter->stats.ptc127;
	regs_buff[104] = adapter->stats.ptc255;
	regs_buff[105] = adapter->stats.ptc511;
	regs_buff[106] = adapter->stats.ptc1023;
	regs_buff[107] = adapter->stats.ptc1522;
	regs_buff[108] = adapter->stats.mptc;
	regs_buff[109] = adapter->stats.bptc;
	regs_buff[110] = adapter->stats.tsctc;
	regs_buff[111] = adapter->stats.iac;
	regs_buff[112] = adapter->stats.rpthc;
	regs_buff[113] = adapter->stats.hgptc;
	regs_buff[114] = adapter->stats.hgorc;
	regs_buff[116] = adapter->stats.hgotc;
	regs_buff[118] = adapter->stats.lenerrs;
	regs_buff[119] = adapter->stats.scvpc;
	regs_buff[120] = adapter->stats.hrmpc;

	क्रम (i = 0; i < 4; i++)
		regs_buff[121 + i] = rd32(E1000_SRRCTL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[125 + i] = rd32(E1000_PSRTYPE(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[129 + i] = rd32(E1000_RDBAL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[133 + i] = rd32(E1000_RDBAH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[137 + i] = rd32(E1000_RDLEN(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[141 + i] = rd32(E1000_RDH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[145 + i] = rd32(E1000_RDT(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[149 + i] = rd32(E1000_RXDCTL(i));

	क्रम (i = 0; i < 10; i++)
		regs_buff[153 + i] = rd32(E1000_EITR(i));
	क्रम (i = 0; i < 8; i++)
		regs_buff[163 + i] = rd32(E1000_IMIR(i));
	क्रम (i = 0; i < 8; i++)
		regs_buff[171 + i] = rd32(E1000_IMIREXT(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[179 + i] = rd32(E1000_RAL(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[195 + i] = rd32(E1000_RAH(i));

	क्रम (i = 0; i < 4; i++)
		regs_buff[211 + i] = rd32(E1000_TDBAL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[215 + i] = rd32(E1000_TDBAH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[219 + i] = rd32(E1000_TDLEN(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[223 + i] = rd32(E1000_TDH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[227 + i] = rd32(E1000_TDT(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[231 + i] = rd32(E1000_TXDCTL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[235 + i] = rd32(E1000_TDWBAL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[239 + i] = rd32(E1000_TDWBAH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[243 + i] = rd32(E1000_DCA_TXCTRL(i));

	क्रम (i = 0; i < 4; i++)
		regs_buff[247 + i] = rd32(E1000_IP4AT_REG(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[251 + i] = rd32(E1000_IP6AT_REG(i));
	क्रम (i = 0; i < 32; i++)
		regs_buff[255 + i] = rd32(E1000_WUPM_REG(i));
	क्रम (i = 0; i < 128; i++)
		regs_buff[287 + i] = rd32(E1000_FFMT_REG(i));
	क्रम (i = 0; i < 128; i++)
		regs_buff[415 + i] = rd32(E1000_FFVT_REG(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[543 + i] = rd32(E1000_FFLT_REG(i));

	regs_buff[547] = rd32(E1000_TDFH);
	regs_buff[548] = rd32(E1000_TDFT);
	regs_buff[549] = rd32(E1000_TDFHS);
	regs_buff[550] = rd32(E1000_TDFPC);

	अगर (hw->mac.type > e1000_82580) अणु
		regs_buff[551] = adapter->stats.o2bgptc;
		regs_buff[552] = adapter->stats.b2ospc;
		regs_buff[553] = adapter->stats.o2bspc;
		regs_buff[554] = adapter->stats.b2ogprc;
	पूर्ण

	अगर (hw->mac.type == e1000_82576) अणु
		क्रम (i = 0; i < 12; i++)
			regs_buff[555 + i] = rd32(E1000_SRRCTL(i + 4));
		क्रम (i = 0; i < 4; i++)
			regs_buff[567 + i] = rd32(E1000_PSRTYPE(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[571 + i] = rd32(E1000_RDBAL(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[583 + i] = rd32(E1000_RDBAH(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[595 + i] = rd32(E1000_RDLEN(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[607 + i] = rd32(E1000_RDH(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[619 + i] = rd32(E1000_RDT(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[631 + i] = rd32(E1000_RXDCTL(i + 4));

		क्रम (i = 0; i < 12; i++)
			regs_buff[643 + i] = rd32(E1000_TDBAL(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[655 + i] = rd32(E1000_TDBAH(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[667 + i] = rd32(E1000_TDLEN(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[679 + i] = rd32(E1000_TDH(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[691 + i] = rd32(E1000_TDT(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[703 + i] = rd32(E1000_TXDCTL(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[715 + i] = rd32(E1000_TDWBAL(i + 4));
		क्रम (i = 0; i < 12; i++)
			regs_buff[727 + i] = rd32(E1000_TDWBAH(i + 4));
	पूर्ण

	अगर (hw->mac.type == e1000_i210 || hw->mac.type == e1000_i211)
		regs_buff[739] = rd32(E1000_I210_RR2DCDELAY);
पूर्ण

अटल पूर्णांक igb_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	वापस adapter->hw.nvm.word_size * 2;
पूर्ण

अटल पूर्णांक igb_get_eeprom(काष्ठा net_device *netdev,
			  काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	पूर्णांक first_word, last_word;
	पूर्णांक ret_val = 0;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	eeprom->magic = hw->venकरोr_id | (hw->device_id << 16);

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;

	eeprom_buff = kदो_स्मृति_array(last_word - first_word + 1, माप(u16),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	अगर (hw->nvm.type == e1000_nvm_eeprom_spi)
		ret_val = hw->nvm.ops.पढ़ो(hw, first_word,
					   last_word - first_word + 1,
					   eeprom_buff);
	अन्यथा अणु
		क्रम (i = 0; i < last_word - first_word + 1; i++) अणु
			ret_val = hw->nvm.ops.पढ़ो(hw, first_word + i, 1,
						   &eeprom_buff[i]);
			अगर (ret_val)
				अवरोध;
		पूर्ण
	पूर्ण

	/* Device's eeprom is always little-endian, word addressable */
	क्रम (i = 0; i < last_word - first_word + 1; i++)
		le16_to_cpus(&eeprom_buff[i]);

	स_नकल(bytes, (u8 *)eeprom_buff + (eeprom->offset & 1),
			eeprom->len);
	kमुक्त(eeprom_buff);

	वापस ret_val;
पूर्ण

अटल पूर्णांक igb_set_eeprom(काष्ठा net_device *netdev,
			  काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	व्योम *ptr;
	पूर्णांक max_len, first_word, last_word, ret_val = 0;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EOPNOTSUPP;

	अगर ((hw->mac.type >= e1000_i210) &&
	    !igb_get_flash_presence_i210(hw)) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (eeprom->magic != (hw->venकरोr_id | (hw->device_id << 16)))
		वापस -EFAULT;

	max_len = hw->nvm.word_size * 2;

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kदो_स्मृति(max_len, GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	ptr = (व्योम *)eeprom_buff;

	अगर (eeprom->offset & 1) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of first changed EEPROM word
		 * only the second byte of the word is being modअगरied
		 */
		ret_val = hw->nvm.ops.पढ़ो(hw, first_word, 1,
					    &eeprom_buff[0]);
		ptr++;
	पूर्ण
	अगर (((eeprom->offset + eeprom->len) & 1) && (ret_val == 0)) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of last changed EEPROM word
		 * only the first byte of the word is being modअगरied
		 */
		ret_val = hw->nvm.ops.पढ़ो(hw, last_word, 1,
				   &eeprom_buff[last_word - first_word]);
	पूर्ण

	/* Device's eeprom is always little-endian, word addressable */
	क्रम (i = 0; i < last_word - first_word + 1; i++)
		le16_to_cpus(&eeprom_buff[i]);

	स_नकल(ptr, bytes, eeprom->len);

	क्रम (i = 0; i < last_word - first_word + 1; i++)
		eeprom_buff[i] = cpu_to_le16(eeprom_buff[i]);

	ret_val = hw->nvm.ops.ग_लिखो(hw, first_word,
				    last_word - first_word + 1, eeprom_buff);

	/* Update the checksum अगर nvm ग_लिखो succeeded */
	अगर (ret_val == 0)
		hw->nvm.ops.update(hw);

	igb_set_fw_version(adapter);
	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल व्योम igb_get_drvinfo(काष्ठा net_device *netdev,
			    काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  igb_driver_name, माप(drvinfo->driver));

	/* EEPROM image version # is reported as firmware version # क्रम
	 * 82575 controllers
	 */
	strlcpy(drvinfo->fw_version, adapter->fw_version,
		माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));

	drvinfo->n_priv_flags = IGB_PRIV_FLAGS_STR_LEN;
पूर्ण

अटल व्योम igb_get_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = IGB_MAX_RXD;
	ring->tx_max_pending = IGB_MAX_TXD;
	ring->rx_pending = adapter->rx_ring_count;
	ring->tx_pending = adapter->tx_ring_count;
पूर्ण

अटल पूर्णांक igb_set_ringparam(काष्ठा net_device *netdev,
			     काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा igb_ring *temp_ring;
	पूर्णांक i, err = 0;
	u16 new_rx_count, new_tx_count;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	new_rx_count = min_t(u32, ring->rx_pending, IGB_MAX_RXD);
	new_rx_count = max_t(u16, new_rx_count, IGB_MIN_RXD);
	new_rx_count = ALIGN(new_rx_count, REQ_RX_DESCRIPTOR_MULTIPLE);

	new_tx_count = min_t(u32, ring->tx_pending, IGB_MAX_TXD);
	new_tx_count = max_t(u16, new_tx_count, IGB_MIN_TXD);
	new_tx_count = ALIGN(new_tx_count, REQ_TX_DESCRIPTOR_MULTIPLE);

	अगर ((new_tx_count == adapter->tx_ring_count) &&
	    (new_rx_count == adapter->rx_ring_count)) अणु
		/* nothing to करो */
		वापस 0;
	पूर्ण

	जबतक (test_and_set_bit(__IGB_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (!netअगर_running(adapter->netdev)) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			adapter->tx_ring[i]->count = new_tx_count;
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			adapter->rx_ring[i]->count = new_rx_count;
		adapter->tx_ring_count = new_tx_count;
		adapter->rx_ring_count = new_rx_count;
		जाओ clear_reset;
	पूर्ण

	अगर (adapter->num_tx_queues > adapter->num_rx_queues)
		temp_ring = vदो_स्मृति(array_size(माप(काष्ठा igb_ring),
					       adapter->num_tx_queues));
	अन्यथा
		temp_ring = vदो_स्मृति(array_size(माप(काष्ठा igb_ring),
					       adapter->num_rx_queues));

	अगर (!temp_ring) अणु
		err = -ENOMEM;
		जाओ clear_reset;
	पूर्ण

	igb_करोwn(adapter);

	/* We can't just मुक्त everything and then setup again,
	 * because the ISRs in MSI-X mode get passed poपूर्णांकers
	 * to the Tx and Rx ring काष्ठाs.
	 */
	अगर (new_tx_count != adapter->tx_ring_count) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			स_नकल(&temp_ring[i], adapter->tx_ring[i],
			       माप(काष्ठा igb_ring));

			temp_ring[i].count = new_tx_count;
			err = igb_setup_tx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					igb_मुक्त_tx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			igb_मुक्त_tx_resources(adapter->tx_ring[i]);

			स_नकल(adapter->tx_ring[i], &temp_ring[i],
			       माप(काष्ठा igb_ring));
		पूर्ण

		adapter->tx_ring_count = new_tx_count;
	पूर्ण

	अगर (new_rx_count != adapter->rx_ring_count) अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			स_नकल(&temp_ring[i], adapter->rx_ring[i],
			       माप(काष्ठा igb_ring));

			/* Clear copied XDP RX-queue info */
			स_रखो(&temp_ring[i].xdp_rxq, 0,
			       माप(temp_ring[i].xdp_rxq));

			temp_ring[i].count = new_rx_count;
			err = igb_setup_rx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					igb_मुक्त_rx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण

		पूर्ण

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			igb_मुक्त_rx_resources(adapter->rx_ring[i]);

			स_नकल(adapter->rx_ring[i], &temp_ring[i],
			       माप(काष्ठा igb_ring));
		पूर्ण

		adapter->rx_ring_count = new_rx_count;
	पूर्ण
err_setup:
	igb_up(adapter);
	vमुक्त(temp_ring);
clear_reset:
	clear_bit(__IGB_RESETTING, &adapter->state);
	वापस err;
पूर्ण

/* ethtool रेजिस्टर test data */
काष्ठा igb_reg_test अणु
	u16 reg;
	u16 reg_offset;
	u16 array_len;
	u16 test_type;
	u32 mask;
	u32 ग_लिखो;
पूर्ण;

/* In the hardware, रेजिस्टरs are laid out either singly, in arrays
 * spaced 0x100 bytes apart, or in contiguous tables.  We assume
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

/* i210 reg test */
अटल काष्ठा igb_reg_test reg_test_i210[] = अणु
	अणु E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	/* RDH is पढ़ो-only क्रम i210, only test RDT. */
	अणु E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 पूर्ण,
	अणु E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF पूर्ण,
	अणु E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु E1000_TDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF पूर्ण,
	अणु E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_HI,
						0x900FFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_MTA,	   0, 128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण
पूर्ण;

/* i350 reg test */
अटल काष्ठा igb_reg_test reg_test_i350[] = अणु
	अणु E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_VET,	   0x100, 1,  PATTERN_TEST, 0xFFFF0000, 0xFFFF0000 पूर्ण,
	अणु E1000_RDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु E1000_RDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	/* RDH is पढ़ो-only क्रम i350, only test RDT. */
	अणु E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 पूर्ण,
	अणु E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF पूर्ण,
	अणु E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु E1000_TDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु E1000_TDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_TDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF पूर्ण,
	अणु E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_HI,
						0xC3FFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA2,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA2,	   0, 16, TABLE64_TEST_HI,
						0xC3FFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_MTA,	   0, 128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;

/* 82580 reg test */
अटल काष्ठा igb_reg_test reg_test_82580[] = अणु
	अणु E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_VET,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	अणु E1000_RDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	/* RDH is पढ़ो-only क्रम 82580, only test RDT. */
	अणु E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 पूर्ण,
	अणु E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF पूर्ण,
	अणु E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	अणु E1000_TDBAL(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(4),  0x40,  4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(4),  0x40,  4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	अणु E1000_TDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_TDT(4),	   0x40,  4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF पूर्ण,
	अणु E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_HI,
						0x83FFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA2,	   0, 8, TABLE64_TEST_LO,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA2,	   0, 8, TABLE64_TEST_HI,
						0x83FFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_MTA,	   0, 128, TABLE32_TEST,
						0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;

/* 82576 reg test */
अटल काष्ठा igb_reg_test reg_test_82576[] = अणु
	अणु E1000_FCAL,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCAH,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCT,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_VET,	   0x100, 1,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAL(0),  0x100, 4, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(0),  0x100, 4, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(0),  0x100, 4, PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	अणु E1000_RDBAL(4),  0x40, 12, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(4),  0x40, 12, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(4),  0x40, 12, PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	/* Enable all RX queues beक्रमe testing. */
	अणु E1000_RXDCTL(0), 0x100, 4, WRITE_NO_TEST, 0,
	  E1000_RXDCTL_QUEUE_ENABLE पूर्ण,
	अणु E1000_RXDCTL(4), 0x40, 12, WRITE_NO_TEST, 0,
	  E1000_RXDCTL_QUEUE_ENABLE पूर्ण,
	/* RDH is पढ़ो-only क्रम 82576, only test RDT. */
	अणु E1000_RDT(0),	   0x100, 4,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RDT(4),	   0x40, 12,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RXDCTL(0), 0x100, 4,  WRITE_NO_TEST, 0, 0 पूर्ण,
	अणु E1000_RXDCTL(4), 0x40, 12,  WRITE_NO_TEST, 0, 0 पूर्ण,
	अणु E1000_FCRTH,	   0x100, 1,  PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 पूर्ण,
	अणु E1000_FCTTV,	   0x100, 1,  PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_TIPG,	   0x100, 1,  PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF पूर्ण,
	अणु E1000_TDBAL(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(0),  0x100, 4,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(0),  0x100, 4,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	अणु E1000_TDBAL(4),  0x40, 12,  PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(4),  0x40, 12,  PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(4),  0x40, 12,  PATTERN_TEST, 0x000FFFF0, 0x000FFFFF पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0x003FFFFB पूर्ण,
	अणु E1000_RCTL,	   0x100, 1,  SET_READ_TEST, 0x04CFB0FE, 0xFFFFFFFF पूर्ण,
	अणु E1000_TCTL,	   0x100, 1,  SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_LO, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA,	   0, 16, TABLE64_TEST_HI, 0x83FFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA2,	   0, 8, TABLE64_TEST_LO, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA2,	   0, 8, TABLE64_TEST_HI, 0x83FFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_MTA,	   0, 128, TABLE32_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;

/* 82575 रेजिस्टर test */
अटल काष्ठा igb_reg_test reg_test_82575[] = अणु
	अणु E1000_FCAL,      0x100, 1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCAH,      0x100, 1, PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_FCT,       0x100, 1, PATTERN_TEST, 0x0000FFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_VET,       0x100, 1, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAL(0),  0x100, 4, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDBAH(0),  0x100, 4, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RDLEN(0),  0x100, 4, PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	/* Enable all four RX queues beक्रमe testing. */
	अणु E1000_RXDCTL(0), 0x100, 4, WRITE_NO_TEST, 0,
	  E1000_RXDCTL_QUEUE_ENABLE पूर्ण,
	/* RDH is पढ़ो-only क्रम 82575, only test RDT. */
	अणु E1000_RDT(0),    0x100, 4, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RXDCTL(0), 0x100, 4, WRITE_NO_TEST, 0, 0 पूर्ण,
	अणु E1000_FCRTH,     0x100, 1, PATTERN_TEST, 0x0000FFF0, 0x0000FFF0 पूर्ण,
	अणु E1000_FCTTV,     0x100, 1, PATTERN_TEST, 0x0000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_TIPG,      0x100, 1, PATTERN_TEST, 0x3FFFFFFF, 0x3FFFFFFF पूर्ण,
	अणु E1000_TDBAL(0),  0x100, 4, PATTERN_TEST, 0xFFFFFF80, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDBAH(0),  0x100, 4, PATTERN_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_TDLEN(0),  0x100, 4, PATTERN_TEST, 0x000FFF80, 0x000FFFFF पूर्ण,
	अणु E1000_RCTL,      0x100, 1, SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_RCTL,      0x100, 1, SET_READ_TEST, 0x04CFB3FE, 0x003FFFFB पूर्ण,
	अणु E1000_RCTL,      0x100, 1, SET_READ_TEST, 0x04CFB3FE, 0xFFFFFFFF पूर्ण,
	अणु E1000_TCTL,      0x100, 1, SET_READ_TEST, 0xFFFFFFFF, 0x00000000 पूर्ण,
	अणु E1000_TXCW,      0x100, 1, PATTERN_TEST, 0xC000FFFF, 0x0000FFFF पूर्ण,
	अणु E1000_RA,        0, 16, TABLE64_TEST_LO, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_RA,        0, 16, TABLE64_TEST_HI, 0x800FFFFF, 0xFFFFFFFF पूर्ण,
	अणु E1000_MTA,       0, 128, TABLE32_TEST, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण,
	अणु 0, 0, 0, 0 पूर्ण
पूर्ण;

अटल bool reg_pattern_test(काष्ठा igb_adapter *adapter, u64 *data,
			     पूर्णांक reg, u32 mask, u32 ग_लिखो)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 pat, val;
	अटल स्थिर u32 _test[] = अणु
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFFपूर्ण;
	क्रम (pat = 0; pat < ARRAY_SIZE(_test); pat++) अणु
		wr32(reg, (_test[pat] & ग_लिखो));
		val = rd32(reg) & mask;
		अगर (val != (_test[pat] & ग_लिखो & mask)) अणु
			dev_err(&adapter->pdev->dev,
				"pattern test reg %04X failed: got 0x%08X expected 0x%08X\n",
				reg, val, (_test[pat] & ग_लिखो & mask));
			*data = reg;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool reg_set_and_check(काष्ठा igb_adapter *adapter, u64 *data,
			      पूर्णांक reg, u32 mask, u32 ग_लिखो)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 val;

	wr32(reg, ग_लिखो & mask);
	val = rd32(reg);
	अगर ((ग_लिखो & mask) != (val & mask)) अणु
		dev_err(&adapter->pdev->dev,
			"set/check reg %04X test failed: got 0x%08X expected 0x%08X\n",
			reg, (val & mask), (ग_लिखो & mask));
		*data = reg;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा REG_PATTERN_TEST(reg, mask, ग_लिखो) \
	करो अणु \
		अगर (reg_pattern_test(adapter, data, reg, mask, ग_लिखो)) \
			वापस 1; \
	पूर्ण जबतक (0)

#घोषणा REG_SET_AND_CHECK(reg, mask, ग_लिखो) \
	करो अणु \
		अगर (reg_set_and_check(adapter, data, reg, mask, ग_लिखो)) \
			वापस 1; \
	पूर्ण जबतक (0)

अटल पूर्णांक igb_reg_test(काष्ठा igb_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा igb_reg_test *test;
	u32 value, beक्रमe, after;
	u32 i, toggle;

	चयन (adapter->hw.mac.type) अणु
	हाल e1000_i350:
	हाल e1000_i354:
		test = reg_test_i350;
		toggle = 0x7FEFF3FF;
		अवरोध;
	हाल e1000_i210:
	हाल e1000_i211:
		test = reg_test_i210;
		toggle = 0x7FEFF3FF;
		अवरोध;
	हाल e1000_82580:
		test = reg_test_82580;
		toggle = 0x7FEFF3FF;
		अवरोध;
	हाल e1000_82576:
		test = reg_test_82576;
		toggle = 0x7FFFF3FF;
		अवरोध;
	शेष:
		test = reg_test_82575;
		toggle = 0x7FFFF3FF;
		अवरोध;
	पूर्ण

	/* Because the status रेजिस्टर is such a special हाल,
	 * we handle it separately from the rest of the रेजिस्टर
	 * tests.  Some bits are पढ़ो-only, some toggle, and some
	 * are writable on newer MACs.
	 */
	beक्रमe = rd32(E1000_STATUS);
	value = (rd32(E1000_STATUS) & toggle);
	wr32(E1000_STATUS, toggle);
	after = rd32(E1000_STATUS) & toggle;
	अगर (value != after) अणु
		dev_err(&adapter->pdev->dev,
			"failed STATUS register test got: 0x%08X expected: 0x%08X\n",
			after, value);
		*data = 1;
		वापस 1;
	पूर्ण
	/* restore previous status */
	wr32(E1000_STATUS, beक्रमe);

	/* Perक्रमm the reमुख्यder of the रेजिस्टर test, looping through
	 * the test table until we either fail or reach the null entry.
	 */
	जबतक (test->reg) अणु
		क्रम (i = 0; i < test->array_len; i++) अणु
			चयन (test->test_type) अणु
			हाल PATTERN_TEST:
				REG_PATTERN_TEST(test->reg +
						(i * test->reg_offset),
						test->mask,
						test->ग_लिखो);
				अवरोध;
			हाल SET_READ_TEST:
				REG_SET_AND_CHECK(test->reg +
						(i * test->reg_offset),
						test->mask,
						test->ग_लिखो);
				अवरोध;
			हाल WRITE_NO_TEST:
				ग_लिखोl(test->ग_लिखो,
				    (adapter->hw.hw_addr + test->reg)
					+ (i * test->reg_offset));
				अवरोध;
			हाल TABLE32_TEST:
				REG_PATTERN_TEST(test->reg + (i * 4),
						test->mask,
						test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_LO:
				REG_PATTERN_TEST(test->reg + (i * 8),
						test->mask,
						test->ग_लिखो);
				अवरोध;
			हाल TABLE64_TEST_HI:
				REG_PATTERN_TEST((test->reg + 4) + (i * 8),
						test->mask,
						test->ग_लिखो);
				अवरोध;
			पूर्ण
		पूर्ण
		test++;
	पूर्ण

	*data = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक igb_eeprom_test(काष्ठा igb_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	*data = 0;

	/* Validate eeprom on all parts but flashless */
	चयन (hw->mac.type) अणु
	हाल e1000_i210:
	हाल e1000_i211:
		अगर (igb_get_flash_presence_i210(hw)) अणु
			अगर (adapter->hw.nvm.ops.validate(&adapter->hw) < 0)
				*data = 2;
		पूर्ण
		अवरोध;
	शेष:
		अगर (adapter->hw.nvm.ops.validate(&adapter->hw) < 0)
			*data = 2;
		अवरोध;
	पूर्ण

	वापस *data;
पूर्ण

अटल irqवापस_t igb_test_पूर्णांकr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा igb_adapter *adapter = (काष्ठा igb_adapter *) data;
	काष्ठा e1000_hw *hw = &adapter->hw;

	adapter->test_icr |= rd32(E1000_ICR);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक igb_पूर्णांकr_test(काष्ठा igb_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 mask, ics_mask, i = 0, shared_पूर्णांक = true;
	u32 irq = adapter->pdev->irq;

	*data = 0;

	/* Hook up test पूर्णांकerrupt handler just क्रम this test */
	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		अगर (request_irq(adapter->msix_entries[0].vector,
				igb_test_पूर्णांकr, 0, netdev->name, adapter)) अणु
			*data = 1;
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अगर (adapter->flags & IGB_FLAG_HAS_MSI) अणु
		shared_पूर्णांक = false;
		अगर (request_irq(irq,
				igb_test_पूर्णांकr, 0, netdev->name, adapter)) अणु
			*data = 1;
			वापस -1;
		पूर्ण
	पूर्ण अन्यथा अगर (!request_irq(irq, igb_test_पूर्णांकr, IRQF_PROBE_SHARED,
				netdev->name, adapter)) अणु
		shared_पूर्णांक = false;
	पूर्ण अन्यथा अगर (request_irq(irq, igb_test_पूर्णांकr, IRQF_SHARED,
		 netdev->name, adapter)) अणु
		*data = 1;
		वापस -1;
	पूर्ण
	dev_info(&adapter->pdev->dev, "testing %s interrupt\n",
		(shared_पूर्णांक ? "shared" : "unshared"));

	/* Disable all the पूर्णांकerrupts */
	wr32(E1000_IMC, ~0);
	wrfl();
	usleep_range(10000, 11000);

	/* Define all writable bits क्रम ICS */
	चयन (hw->mac.type) अणु
	हाल e1000_82575:
		ics_mask = 0x37F47EDD;
		अवरोध;
	हाल e1000_82576:
		ics_mask = 0x77D4FBFD;
		अवरोध;
	हाल e1000_82580:
		ics_mask = 0x77DCFED5;
		अवरोध;
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_i210:
	हाल e1000_i211:
		ics_mask = 0x77DCFED5;
		अवरोध;
	शेष:
		ics_mask = 0x7FFFFFFF;
		अवरोध;
	पूर्ण

	/* Test each पूर्णांकerrupt */
	क्रम (; i < 31; i++) अणु
		/* Interrupt to test */
		mask = BIT(i);

		अगर (!(mask & ics_mask))
			जारी;

		अगर (!shared_पूर्णांक) अणु
			/* Disable the पूर्णांकerrupt to be reported in
			 * the cause रेजिस्टर and then क्रमce the same
			 * पूर्णांकerrupt and see अगर one माला_लो posted.  If
			 * an पूर्णांकerrupt was posted to the bus, the
			 * test failed.
			 */
			adapter->test_icr = 0;

			/* Flush any pending पूर्णांकerrupts */
			wr32(E1000_ICR, ~0);

			wr32(E1000_IMC, mask);
			wr32(E1000_ICS, mask);
			wrfl();
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

		/* Flush any pending पूर्णांकerrupts */
		wr32(E1000_ICR, ~0);

		wr32(E1000_IMS, mask);
		wr32(E1000_ICS, mask);
		wrfl();
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

			/* Flush any pending पूर्णांकerrupts */
			wr32(E1000_ICR, ~0);

			wr32(E1000_IMC, ~mask);
			wr32(E1000_ICS, ~mask);
			wrfl();
			usleep_range(10000, 11000);

			अगर (adapter->test_icr & mask) अणु
				*data = 5;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable all the पूर्णांकerrupts */
	wr32(E1000_IMC, ~0);
	wrfl();
	usleep_range(10000, 11000);

	/* Unhook test पूर्णांकerrupt handler */
	अगर (adapter->flags & IGB_FLAG_HAS_MSIX)
		मुक्त_irq(adapter->msix_entries[0].vector, adapter);
	अन्यथा
		मुक्त_irq(irq, adapter);

	वापस *data;
पूर्ण

अटल व्योम igb_मुक्त_desc_rings(काष्ठा igb_adapter *adapter)
अणु
	igb_मुक्त_tx_resources(&adapter->test_tx_ring);
	igb_मुक्त_rx_resources(&adapter->test_rx_ring);
पूर्ण

अटल पूर्णांक igb_setup_desc_rings(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा igb_ring *tx_ring = &adapter->test_tx_ring;
	काष्ठा igb_ring *rx_ring = &adapter->test_rx_ring;
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक ret_val;

	/* Setup Tx descriptor ring and Tx buffers */
	tx_ring->count = IGB_DEFAULT_TXD;
	tx_ring->dev = &adapter->pdev->dev;
	tx_ring->netdev = adapter->netdev;
	tx_ring->reg_idx = adapter->vfs_allocated_count;

	अगर (igb_setup_tx_resources(tx_ring)) अणु
		ret_val = 1;
		जाओ err_nomem;
	पूर्ण

	igb_setup_tctl(adapter);
	igb_configure_tx_ring(adapter, tx_ring);

	/* Setup Rx descriptor ring and Rx buffers */
	rx_ring->count = IGB_DEFAULT_RXD;
	rx_ring->dev = &adapter->pdev->dev;
	rx_ring->netdev = adapter->netdev;
	rx_ring->reg_idx = adapter->vfs_allocated_count;

	अगर (igb_setup_rx_resources(rx_ring)) अणु
		ret_val = 3;
		जाओ err_nomem;
	पूर्ण

	/* set the शेष queue to queue 0 of PF */
	wr32(E1000_MRQC, adapter->vfs_allocated_count << 3);

	/* enable receive ring */
	igb_setup_rctl(adapter);
	igb_configure_rx_ring(adapter, rx_ring);

	igb_alloc_rx_buffers(rx_ring, igb_desc_unused(rx_ring));

	वापस 0;

err_nomem:
	igb_मुक्त_desc_rings(adapter);
	वापस ret_val;
पूर्ण

अटल व्योम igb_phy_disable_receiver(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Write out to PHY रेजिस्टरs 29 and 30 to disable the Receiver. */
	igb_ग_लिखो_phy_reg(hw, 29, 0x001F);
	igb_ग_लिखो_phy_reg(hw, 30, 0x8FFC);
	igb_ग_लिखो_phy_reg(hw, 29, 0x001A);
	igb_ग_लिखो_phy_reg(hw, 30, 0x8FF0);
पूर्ण

अटल पूर्णांक igb_पूर्णांकegrated_phy_loopback(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_reg = 0;

	hw->mac.स्वतःneg = false;

	अगर (hw->phy.type == e1000_phy_m88) अणु
		अगर (hw->phy.id != I210_I_PHY_ID) अणु
			/* Auto-MDI/MDIX Off */
			igb_ग_लिखो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, 0x0808);
			/* reset to update Auto-MDI/MDIX */
			igb_ग_लिखो_phy_reg(hw, PHY_CONTROL, 0x9140);
			/* स्वतःneg off */
			igb_ग_लिखो_phy_reg(hw, PHY_CONTROL, 0x8140);
		पूर्ण अन्यथा अणु
			/* क्रमce 1000, set loopback  */
			igb_ग_लिखो_phy_reg(hw, I347AT4_PAGE_SELECT, 0);
			igb_ग_लिखो_phy_reg(hw, PHY_CONTROL, 0x4140);
		पूर्ण
	पूर्ण अन्यथा अगर (hw->phy.type == e1000_phy_82580) अणु
		/* enable MII loopback */
		igb_ग_लिखो_phy_reg(hw, I82580_PHY_LBK_CTRL, 0x8041);
	पूर्ण

	/* add small delay to aव्योम loopback test failure */
	msleep(50);

	/* क्रमce 1000, set loopback */
	igb_ग_लिखो_phy_reg(hw, PHY_CONTROL, 0x4140);

	/* Now set up the MAC to the same speed/duplex as the PHY. */
	ctrl_reg = rd32(E1000_CTRL);
	ctrl_reg &= ~E1000_CTRL_SPD_SEL; /* Clear the speed sel bits */
	ctrl_reg |= (E1000_CTRL_FRCSPD | /* Set the Force Speed Bit */
		     E1000_CTRL_FRCDPX | /* Set the Force Duplex Bit */
		     E1000_CTRL_SPD_1000 |/* Force Speed to 1000 */
		     E1000_CTRL_FD |	 /* Force Duplex to FULL */
		     E1000_CTRL_SLU);	 /* Set link up enable bit */

	अगर (hw->phy.type == e1000_phy_m88)
		ctrl_reg |= E1000_CTRL_ILOS; /* Invert Loss of Signal */

	wr32(E1000_CTRL, ctrl_reg);

	/* Disable the receiver on the PHY so when a cable is plugged in, the
	 * PHY करोes not begin to स्वतःneg when a cable is reconnected to the NIC.
	 */
	अगर (hw->phy.type == e1000_phy_m88)
		igb_phy_disable_receiver(adapter);

	msleep(500);
	वापस 0;
पूर्ण

अटल पूर्णांक igb_set_phy_loopback(काष्ठा igb_adapter *adapter)
अणु
	वापस igb_पूर्णांकegrated_phy_loopback(adapter);
पूर्ण

अटल पूर्णांक igb_setup_loopback_test(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 reg;

	reg = rd32(E1000_CTRL_EXT);

	/* use CTRL_EXT to identअगरy link type as SGMII can appear as copper */
	अगर (reg & E1000_CTRL_EXT_LINK_MODE_MASK) अणु
		अगर ((hw->device_id == E1000_DEV_ID_DH89XXCC_SGMII) ||
		(hw->device_id == E1000_DEV_ID_DH89XXCC_SERDES) ||
		(hw->device_id == E1000_DEV_ID_DH89XXCC_BACKPLANE) ||
		(hw->device_id == E1000_DEV_ID_DH89XXCC_SFP) ||
		(hw->device_id == E1000_DEV_ID_I354_SGMII) ||
		(hw->device_id == E1000_DEV_ID_I354_BACKPLANE_2_5GBPS)) अणु
			/* Enable DH89xxCC MPHY क्रम near end loopback */
			reg = rd32(E1000_MPHY_ADDR_CTL);
			reg = (reg & E1000_MPHY_ADDR_CTL_OFFSET_MASK) |
			E1000_MPHY_PCS_CLK_REG_OFFSET;
			wr32(E1000_MPHY_ADDR_CTL, reg);

			reg = rd32(E1000_MPHY_DATA);
			reg |= E1000_MPHY_PCS_CLK_REG_DIGINELBEN;
			wr32(E1000_MPHY_DATA, reg);
		पूर्ण

		reg = rd32(E1000_RCTL);
		reg |= E1000_RCTL_LBM_TCVR;
		wr32(E1000_RCTL, reg);

		wr32(E1000_SCTL, E1000_ENABLE_SERDES_LOOPBACK);

		reg = rd32(E1000_CTRL);
		reg &= ~(E1000_CTRL_RFCE |
			 E1000_CTRL_TFCE |
			 E1000_CTRL_LRST);
		reg |= E1000_CTRL_SLU |
		       E1000_CTRL_FD;
		wr32(E1000_CTRL, reg);

		/* Unset चयन control to serdes energy detect */
		reg = rd32(E1000_CONNSW);
		reg &= ~E1000_CONNSW_ENRGSRC;
		wr32(E1000_CONNSW, reg);

		/* Unset sigdetect क्रम SERDES loopback on
		 * 82580 and newer devices.
		 */
		अगर (hw->mac.type >= e1000_82580) अणु
			reg = rd32(E1000_PCS_CFG0);
			reg |= E1000_PCS_CFG_IGN_SD;
			wr32(E1000_PCS_CFG0, reg);
		पूर्ण

		/* Set PCS रेजिस्टर क्रम क्रमced speed */
		reg = rd32(E1000_PCS_LCTL);
		reg &= ~E1000_PCS_LCTL_AN_ENABLE;     /* Disable Autoneg*/
		reg |= E1000_PCS_LCTL_FLV_LINK_UP |   /* Force link up */
		       E1000_PCS_LCTL_FSV_1000 |      /* Force 1000    */
		       E1000_PCS_LCTL_FDV_FULL |      /* SerDes Full duplex */
		       E1000_PCS_LCTL_FSD |           /* Force Speed */
		       E1000_PCS_LCTL_FORCE_LINK;     /* Force Link */
		wr32(E1000_PCS_LCTL, reg);

		वापस 0;
	पूर्ण

	वापस igb_set_phy_loopback(adapter);
पूर्ण

अटल व्योम igb_loopback_cleanup(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;
	u16 phy_reg;

	अगर ((hw->device_id == E1000_DEV_ID_DH89XXCC_SGMII) ||
	(hw->device_id == E1000_DEV_ID_DH89XXCC_SERDES) ||
	(hw->device_id == E1000_DEV_ID_DH89XXCC_BACKPLANE) ||
	(hw->device_id == E1000_DEV_ID_DH89XXCC_SFP) ||
	(hw->device_id == E1000_DEV_ID_I354_SGMII)) अणु
		u32 reg;

		/* Disable near end loopback on DH89xxCC */
		reg = rd32(E1000_MPHY_ADDR_CTL);
		reg = (reg & E1000_MPHY_ADDR_CTL_OFFSET_MASK) |
		E1000_MPHY_PCS_CLK_REG_OFFSET;
		wr32(E1000_MPHY_ADDR_CTL, reg);

		reg = rd32(E1000_MPHY_DATA);
		reg &= ~E1000_MPHY_PCS_CLK_REG_DIGINELBEN;
		wr32(E1000_MPHY_DATA, reg);
	पूर्ण

	rctl = rd32(E1000_RCTL);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);
	wr32(E1000_RCTL, rctl);

	hw->mac.स्वतःneg = true;
	igb_पढ़ो_phy_reg(hw, PHY_CONTROL, &phy_reg);
	अगर (phy_reg & MII_CR_LOOPBACK) अणु
		phy_reg &= ~MII_CR_LOOPBACK;
		igb_ग_लिखो_phy_reg(hw, PHY_CONTROL, phy_reg);
		igb_phy_sw_reset(hw);
	पूर्ण
पूर्ण

अटल व्योम igb_create_lbtest_frame(काष्ठा sk_buff *skb,
				    अचिन्हित पूर्णांक frame_size)
अणु
	स_रखो(skb->data, 0xFF, frame_size);
	frame_size /= 2;
	स_रखो(&skb->data[frame_size], 0xAA, frame_size - 1);
	skb->data[frame_size + 10] = 0xBE;
	skb->data[frame_size + 12] = 0xAF;
पूर्ण

अटल पूर्णांक igb_check_lbtest_frame(काष्ठा igb_rx_buffer *rx_buffer,
				  अचिन्हित पूर्णांक frame_size)
अणु
	अचिन्हित अक्षर *data;
	bool match = true;

	frame_size >>= 1;

	data = kmap(rx_buffer->page);

	अगर (data[3] != 0xFF ||
	    data[frame_size + 10] != 0xBE ||
	    data[frame_size + 12] != 0xAF)
		match = false;

	kunmap(rx_buffer->page);

	वापस match;
पूर्ण

अटल पूर्णांक igb_clean_test_rings(काष्ठा igb_ring *rx_ring,
				काष्ठा igb_ring *tx_ring,
				अचिन्हित पूर्णांक size)
अणु
	जोड़ e1000_adv_rx_desc *rx_desc;
	काष्ठा igb_rx_buffer *rx_buffer_info;
	काष्ठा igb_tx_buffer *tx_buffer_info;
	u16 rx_ntc, tx_ntc, count = 0;

	/* initialize next to clean and descriptor values */
	rx_ntc = rx_ring->next_to_clean;
	tx_ntc = tx_ring->next_to_clean;
	rx_desc = IGB_RX_DESC(rx_ring, rx_ntc);

	जबतक (rx_desc->wb.upper.length) अणु
		/* check Rx buffer */
		rx_buffer_info = &rx_ring->rx_buffer_info[rx_ntc];

		/* sync Rx buffer क्रम CPU पढ़ो */
		dma_sync_single_क्रम_cpu(rx_ring->dev,
					rx_buffer_info->dma,
					size,
					DMA_FROM_DEVICE);

		/* verअगरy contents of skb */
		अगर (igb_check_lbtest_frame(rx_buffer_info, size))
			count++;

		/* sync Rx buffer क्रम device ग_लिखो */
		dma_sync_single_क्रम_device(rx_ring->dev,
					   rx_buffer_info->dma,
					   size,
					   DMA_FROM_DEVICE);

		/* unmap buffer on Tx side */
		tx_buffer_info = &tx_ring->tx_buffer_info[tx_ntc];

		/* Free all the Tx ring sk_buffs */
		dev_kमुक्त_skb_any(tx_buffer_info->skb);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer_info, dma),
				 dma_unmap_len(tx_buffer_info, len),
				 DMA_TO_DEVICE);
		dma_unmap_len_set(tx_buffer_info, len, 0);

		/* increment Rx/Tx next to clean counters */
		rx_ntc++;
		अगर (rx_ntc == rx_ring->count)
			rx_ntc = 0;
		tx_ntc++;
		अगर (tx_ntc == tx_ring->count)
			tx_ntc = 0;

		/* fetch next descriptor */
		rx_desc = IGB_RX_DESC(rx_ring, rx_ntc);
	पूर्ण

	netdev_tx_reset_queue(txring_txq(tx_ring));

	/* re-map buffers to ring, store next to clean values */
	igb_alloc_rx_buffers(rx_ring, count);
	rx_ring->next_to_clean = rx_ntc;
	tx_ring->next_to_clean = tx_ntc;

	वापस count;
पूर्ण

अटल पूर्णांक igb_run_loopback_test(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा igb_ring *tx_ring = &adapter->test_tx_ring;
	काष्ठा igb_ring *rx_ring = &adapter->test_rx_ring;
	u16 i, j, lc, good_cnt;
	पूर्णांक ret_val = 0;
	अचिन्हित पूर्णांक size = IGB_RX_HDR_LEN;
	netdev_tx_t tx_ret_val;
	काष्ठा sk_buff *skb;

	/* allocate test skb */
	skb = alloc_skb(size, GFP_KERNEL);
	अगर (!skb)
		वापस 11;

	/* place data पूर्णांकo test skb */
	igb_create_lbtest_frame(skb, size);
	skb_put(skb, size);

	/* Calculate the loop count based on the largest descriptor ring
	 * The idea is to wrap the largest ring a number of बार using 64
	 * send/receive pairs during each loop
	 */

	अगर (rx_ring->count <= tx_ring->count)
		lc = ((tx_ring->count / 64) * 2) + 1;
	अन्यथा
		lc = ((rx_ring->count / 64) * 2) + 1;

	क्रम (j = 0; j <= lc; j++) अणु /* loop count loop */
		/* reset count of good packets */
		good_cnt = 0;

		/* place 64 packets on the transmit queue*/
		क्रम (i = 0; i < 64; i++) अणु
			skb_get(skb);
			tx_ret_val = igb_xmit_frame_ring(skb, tx_ring);
			अगर (tx_ret_val == NETDEV_TX_OK)
				good_cnt++;
		पूर्ण

		अगर (good_cnt != 64) अणु
			ret_val = 12;
			अवरोध;
		पूर्ण

		/* allow 200 milliseconds क्रम packets to go from Tx to Rx */
		msleep(200);

		good_cnt = igb_clean_test_rings(rx_ring, tx_ring, size);
		अगर (good_cnt != 64) अणु
			ret_val = 13;
			अवरोध;
		पूर्ण
	पूर्ण /* end loop count loop */

	/* मुक्त the original skb */
	kमुक्त_skb(skb);

	वापस ret_val;
पूर्ण

अटल पूर्णांक igb_loopback_test(काष्ठा igb_adapter *adapter, u64 *data)
अणु
	/* PHY loopback cannot be perक्रमmed अगर SoL/IDER
	 * sessions are active
	 */
	अगर (igb_check_reset_block(&adapter->hw)) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot do PHY loopback test when SoL/IDER is active.\n");
		*data = 0;
		जाओ out;
	पूर्ण

	अगर (adapter->hw.mac.type == e1000_i354) अणु
		dev_info(&adapter->pdev->dev,
			"Loopback test not supported on i354.\n");
		*data = 0;
		जाओ out;
	पूर्ण
	*data = igb_setup_desc_rings(adapter);
	अगर (*data)
		जाओ out;
	*data = igb_setup_loopback_test(adapter);
	अगर (*data)
		जाओ err_loopback;
	*data = igb_run_loopback_test(adapter);
	igb_loopback_cleanup(adapter);

err_loopback:
	igb_मुक्त_desc_rings(adapter);
out:
	वापस *data;
पूर्ण

अटल पूर्णांक igb_link_test(काष्ठा igb_adapter *adapter, u64 *data)
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
			hw->mac.ops.check_क्रम_link(&adapter->hw);
			अगर (hw->mac.serdes_has_link)
				वापस *data;
			msleep(20);
		पूर्ण जबतक (i++ < 3750);

		*data = 1;
	पूर्ण अन्यथा अणु
		hw->mac.ops.check_क्रम_link(&adapter->hw);
		अगर (hw->mac.स्वतःneg)
			msleep(5000);

		अगर (!(rd32(E1000_STATUS) & E1000_STATUS_LU))
			*data = 1;
	पूर्ण
	वापस *data;
पूर्ण

अटल व्योम igb_diag_test(काष्ठा net_device *netdev,
			  काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	u16 स्वतःneg_advertised;
	u8 क्रमced_speed_duplex, स्वतःneg;
	bool अगर_running = netअगर_running(netdev);

	set_bit(__IGB_TESTING, &adapter->state);

	/* can't करो offline tests on media चयनing devices */
	अगर (adapter->hw.dev_spec._82575.mas_capable)
		eth_test->flags &= ~ETH_TEST_FL_OFFLINE;
	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		/* Offline tests */

		/* save speed, duplex, स्वतःneg settings */
		स्वतःneg_advertised = adapter->hw.phy.स्वतःneg_advertised;
		क्रमced_speed_duplex = adapter->hw.mac.क्रमced_speed_duplex;
		स्वतःneg = adapter->hw.mac.स्वतःneg;

		dev_info(&adapter->pdev->dev, "offline testing starting\n");

		/* घातer up link क्रम link test */
		igb_घातer_up_link(adapter);

		/* Link test perक्रमmed beक्रमe hardware reset so स्वतःneg करोesn't
		 * पूर्णांकerfere with test result
		 */
		अगर (igb_link_test(adapter, &data[TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (अगर_running)
			/* indicate we're in test mode */
			igb_बंद(netdev);
		अन्यथा
			igb_reset(adapter);

		अगर (igb_reg_test(adapter, &data[TEST_REG]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		अगर (igb_eeprom_test(adapter, &data[TEST_EEP]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		अगर (igb_पूर्णांकr_test(adapter, &data[TEST_IRQ]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igb_reset(adapter);
		/* घातer up link क्रम loopback test */
		igb_घातer_up_link(adapter);
		अगर (igb_loopback_test(adapter, &data[TEST_LOOP]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* restore speed, duplex, स्वतःneg settings */
		adapter->hw.phy.स्वतःneg_advertised = स्वतःneg_advertised;
		adapter->hw.mac.क्रमced_speed_duplex = क्रमced_speed_duplex;
		adapter->hw.mac.स्वतःneg = स्वतःneg;

		/* क्रमce this routine to रुको until स्वतःneg complete/समयout */
		adapter->hw.phy.स्वतःneg_रुको_to_complete = true;
		igb_reset(adapter);
		adapter->hw.phy.स्वतःneg_रुको_to_complete = false;

		clear_bit(__IGB_TESTING, &adapter->state);
		अगर (अगर_running)
			igb_खोलो(netdev);
	पूर्ण अन्यथा अणु
		dev_info(&adapter->pdev->dev, "online testing starting\n");

		/* PHY is घातered करोwn when पूर्णांकerface is करोwn */
		अगर (अगर_running && igb_link_test(adapter, &data[TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;
		अन्यथा
			data[TEST_LINK] = 0;

		/* Online tests aren't run; pass by शेष */
		data[TEST_REG] = 0;
		data[TEST_EEP] = 0;
		data[TEST_IRQ] = 0;
		data[TEST_LOOP] = 0;

		clear_bit(__IGB_TESTING, &adapter->state);
	पूर्ण
	msleep_पूर्णांकerruptible(4 * 1000);
पूर्ण

अटल व्योम igb_get_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	wol->wolopts = 0;

	अगर (!(adapter->flags & IGB_FLAG_WOL_SUPPORTED))
		वापस;

	wol->supported = WAKE_UCAST | WAKE_MCAST |
			 WAKE_BCAST | WAKE_MAGIC |
			 WAKE_PHY;

	/* apply any specअगरic unsupported masks here */
	चयन (adapter->hw.device_id) अणु
	शेष:
		अवरोध;
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

अटल पूर्णांक igb_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE | WAKE_FILTER))
		वापस -EOPNOTSUPP;

	अगर (!(adapter->flags & IGB_FLAG_WOL_SUPPORTED))
		वापस wol->wolopts ? -EOPNOTSUPP : 0;

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

/* bit defines क्रम adapter->led_status */
#घोषणा IGB_LED_ON		0

अटल पूर्णांक igb_set_phys_id(काष्ठा net_device *netdev,
			   क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		igb_blink_led(hw);
		वापस 2;
	हाल ETHTOOL_ID_ON:
		igb_blink_led(hw);
		अवरोध;
	हाल ETHTOOL_ID_OFF:
		igb_led_off(hw);
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		igb_led_off(hw);
		clear_bit(IGB_LED_ON, &adapter->led_status);
		igb_cleanup_led(hw);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_set_coalesce(काष्ठा net_device *netdev,
			    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	अगर ((ec->rx_coalesce_usecs > IGB_MAX_ITR_USECS) ||
	    ((ec->rx_coalesce_usecs > 3) &&
	     (ec->rx_coalesce_usecs < IGB_MIN_ITR_USECS)) ||
	    (ec->rx_coalesce_usecs == 2))
		वापस -EINVAL;

	अगर ((ec->tx_coalesce_usecs > IGB_MAX_ITR_USECS) ||
	    ((ec->tx_coalesce_usecs > 3) &&
	     (ec->tx_coalesce_usecs < IGB_MIN_ITR_USECS)) ||
	    (ec->tx_coalesce_usecs == 2))
		वापस -EINVAL;

	अगर ((adapter->flags & IGB_FLAG_QUEUE_PAIRS) && ec->tx_coalesce_usecs)
		वापस -EINVAL;

	/* If ITR is disabled, disable DMAC */
	अगर (ec->rx_coalesce_usecs == 0) अणु
		अगर (adapter->flags & IGB_FLAG_DMAC)
			adapter->flags &= ~IGB_FLAG_DMAC;
	पूर्ण

	/* convert to rate of irq's per second */
	अगर (ec->rx_coalesce_usecs && ec->rx_coalesce_usecs <= 3)
		adapter->rx_itr_setting = ec->rx_coalesce_usecs;
	अन्यथा
		adapter->rx_itr_setting = ec->rx_coalesce_usecs << 2;

	/* convert to rate of irq's per second */
	अगर (adapter->flags & IGB_FLAG_QUEUE_PAIRS)
		adapter->tx_itr_setting = adapter->rx_itr_setting;
	अन्यथा अगर (ec->tx_coalesce_usecs && ec->tx_coalesce_usecs <= 3)
		adapter->tx_itr_setting = ec->tx_coalesce_usecs;
	अन्यथा
		adapter->tx_itr_setting = ec->tx_coalesce_usecs << 2;

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		काष्ठा igb_q_vector *q_vector = adapter->q_vector[i];
		q_vector->tx.work_limit = adapter->tx_work_limit;
		अगर (q_vector->rx.ring)
			q_vector->itr_val = adapter->rx_itr_setting;
		अन्यथा
			q_vector->itr_val = adapter->tx_itr_setting;
		अगर (q_vector->itr_val && q_vector->itr_val <= 3)
			q_vector->itr_val = IGB_START_ITR;
		q_vector->set_itr = 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_get_coalesce(काष्ठा net_device *netdev,
			    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->rx_itr_setting <= 3)
		ec->rx_coalesce_usecs = adapter->rx_itr_setting;
	अन्यथा
		ec->rx_coalesce_usecs = adapter->rx_itr_setting >> 2;

	अगर (!(adapter->flags & IGB_FLAG_QUEUE_PAIRS)) अणु
		अगर (adapter->tx_itr_setting <= 3)
			ec->tx_coalesce_usecs = adapter->tx_itr_setting;
		अन्यथा
			ec->tx_coalesce_usecs = adapter->tx_itr_setting >> 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	अगर (netअगर_running(netdev))
		igb_reinit_locked(adapter);
	वापस 0;
पूर्ण

अटल पूर्णांक igb_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस IGB_STATS_LEN;
	हाल ETH_SS_TEST:
		वापस IGB_TEST_LEN;
	हाल ETH_SS_PRIV_FLAGS:
		वापस IGB_PRIV_FLAGS_STR_LEN;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम igb_get_ethtool_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा rtnl_link_stats64 *net_stats = &adapter->stats64;
	अचिन्हित पूर्णांक start;
	काष्ठा igb_ring *ring;
	पूर्णांक i, j;
	अक्षर *p;

	spin_lock(&adapter->stats64_lock);
	igb_update_stats(adapter);

	क्रम (i = 0; i < IGB_GLOBAL_STATS_LEN; i++) अणु
		p = (अक्षर *)adapter + igb_gstrings_stats[i].stat_offset;
		data[i] = (igb_gstrings_stats[i].माप_stat ==
			माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
	क्रम (j = 0; j < IGB_NETDEV_STATS_LEN; j++, i++) अणु
		p = (अक्षर *)net_stats + igb_gstrings_net_stats[j].stat_offset;
		data[i] = (igb_gstrings_net_stats[j].माप_stat ==
			माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
	क्रम (j = 0; j < adapter->num_tx_queues; j++) अणु
		u64	restart2;

		ring = adapter->tx_ring[j];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp);
			data[i]   = ring->tx_stats.packets;
			data[i+1] = ring->tx_stats.bytes;
			data[i+2] = ring->tx_stats.restart_queue;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->tx_syncp, start));
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp2);
			restart2  = ring->tx_stats.restart_queue2;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->tx_syncp2, start));
		data[i+2] += restart2;

		i += IGB_TX_QUEUE_STATS_LEN;
	पूर्ण
	क्रम (j = 0; j < adapter->num_rx_queues; j++) अणु
		ring = adapter->rx_ring[j];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->rx_syncp);
			data[i]   = ring->rx_stats.packets;
			data[i+1] = ring->rx_stats.bytes;
			data[i+2] = ring->rx_stats.drops;
			data[i+3] = ring->rx_stats.csum_err;
			data[i+4] = ring->rx_stats.alloc_failed;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->rx_syncp, start));
		i += IGB_RX_QUEUE_STATS_LEN;
	पूर्ण
	spin_unlock(&adapter->stats64_lock);
पूर्ण

अटल व्योम igb_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *igb_gstrings_test,
			IGB_TEST_LEN*ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < IGB_GLOBAL_STATS_LEN; i++)
			ethtool_प्र_लिखो(&p,
					igb_gstrings_stats[i].stat_string);
		क्रम (i = 0; i < IGB_NETDEV_STATS_LEN; i++)
			ethtool_प्र_लिखो(&p,
					igb_gstrings_net_stats[i].stat_string);
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			ethtool_प्र_लिखो(&p, "tx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "tx_queue_%u_bytes", i);
			ethtool_प्र_लिखो(&p, "tx_queue_%u_restart", i);
		पूर्ण
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			ethtool_प्र_लिखो(&p, "rx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_bytes", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_drops", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_csum_err", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_alloc_failed", i);
		पूर्ण
		/* BUG_ON(p - data != IGB_STATS_LEN * ETH_GSTRING_LEN); */
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(data, igb_priv_flags_strings,
		       IGB_PRIV_FLAGS_STR_LEN * ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक igb_get_ts_info(काष्ठा net_device *dev,
			   काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(dev);

	अगर (adapter->ptp_घड़ी)
		info->phc_index = ptp_घड़ी_index(adapter->ptp_घड़ी);
	अन्यथा
		info->phc_index = -1;

	चयन (adapter->hw.mac.type) अणु
	हाल e1000_82575:
		info->so_बारtamping =
			SOF_TIMESTAMPING_TX_SOFTWARE |
			SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		वापस 0;
	हाल e1000_82576:
	हाल e1000_82580:
	हाल e1000_i350:
	हाल e1000_i354:
	हाल e1000_i210:
	हाल e1000_i211:
		info->so_बारtamping =
			SOF_TIMESTAMPING_TX_SOFTWARE |
			SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE |
			SOF_TIMESTAMPING_TX_HARDWARE |
			SOF_TIMESTAMPING_RX_HARDWARE |
			SOF_TIMESTAMPING_RAW_HARDWARE;

		info->tx_types =
			BIT(HWTSTAMP_TX_OFF) |
			BIT(HWTSTAMP_TX_ON);

		info->rx_filters = BIT(HWTSTAMP_FILTER_NONE);

		/* 82576 करोes not support बारtamping all packets. */
		अगर (adapter->hw.mac.type >= e1000_82580)
			info->rx_filters |= BIT(HWTSTAMP_FILTER_ALL);
		अन्यथा
			info->rx_filters |=
				BIT(HWTSTAMP_FILTER_PTP_V1_L4_SYNC) |
				BIT(HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ) |
				BIT(HWTSTAMP_FILTER_PTP_V2_EVENT);

		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

#घोषणा ETHER_TYPE_FULL_MASK ((__क्रमce __be16)~0)
अटल पूर्णांक igb_get_ethtool_nfc_entry(काष्ठा igb_adapter *adapter,
				     काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp = &cmd->fs;
	काष्ठा igb_nfc_filter *rule = शून्य;

	/* report total rule count */
	cmd->data = IGB_MAX_RXNFC_FILTERS;

	hlist_क्रम_each_entry(rule, &adapter->nfc_filter_list, nfc_node) अणु
		अगर (fsp->location <= rule->sw_idx)
			अवरोध;
	पूर्ण

	अगर (!rule || fsp->location != rule->sw_idx)
		वापस -EINVAL;

	अगर (rule->filter.match_flags) अणु
		fsp->flow_type = ETHER_FLOW;
		fsp->ring_cookie = rule->action;
		अगर (rule->filter.match_flags & IGB_FILTER_FLAG_ETHER_TYPE) अणु
			fsp->h_u.ether_spec.h_proto = rule->filter.etype;
			fsp->m_u.ether_spec.h_proto = ETHER_TYPE_FULL_MASK;
		पूर्ण
		अगर (rule->filter.match_flags & IGB_FILTER_FLAG_VLAN_TCI) अणु
			fsp->flow_type |= FLOW_EXT;
			fsp->h_ext.vlan_tci = rule->filter.vlan_tci;
			fsp->m_ext.vlan_tci = htons(VLAN_PRIO_MASK);
		पूर्ण
		अगर (rule->filter.match_flags & IGB_FILTER_FLAG_DST_MAC_ADDR) अणु
			ether_addr_copy(fsp->h_u.ether_spec.h_dest,
					rule->filter.dst_addr);
			/* As we only support matching by the full
			 * mask, वापस the mask to userspace
			 */
			eth_broadcast_addr(fsp->m_u.ether_spec.h_dest);
		पूर्ण
		अगर (rule->filter.match_flags & IGB_FILTER_FLAG_SRC_MAC_ADDR) अणु
			ether_addr_copy(fsp->h_u.ether_spec.h_source,
					rule->filter.src_addr);
			/* As we only support matching by the full
			 * mask, वापस the mask to userspace
			 */
			eth_broadcast_addr(fsp->m_u.ether_spec.h_source);
		पूर्ण

		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक igb_get_ethtool_nfc_all(काष्ठा igb_adapter *adapter,
				   काष्ठा ethtool_rxnfc *cmd,
				   u32 *rule_locs)
अणु
	काष्ठा igb_nfc_filter *rule;
	पूर्णांक cnt = 0;

	/* report total rule count */
	cmd->data = IGB_MAX_RXNFC_FILTERS;

	hlist_क्रम_each_entry(rule, &adapter->nfc_filter_list, nfc_node) अणु
		अगर (cnt == cmd->rule_cnt)
			वापस -EMSGSIZE;
		rule_locs[cnt] = rule->sw_idx;
		cnt++;
	पूर्ण

	cmd->rule_cnt = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक igb_get_rss_hash_opts(काष्ठा igb_adapter *adapter,
				 काष्ठा ethtool_rxnfc *cmd)
अणु
	cmd->data = 0;

	/* Report शेष options क्रम RSS on igb */
	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल UDP_V4_FLOW:
		अगर (adapter->flags & IGB_FLAG_RSS_FIELD_IPV4_UDP)
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
		अगर (adapter->flags & IGB_FLAG_RSS_FIELD_IPV6_UDP)
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

अटल पूर्णांक igb_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			 u32 *rule_locs)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_rx_queues;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = adapter->nfc_filter_count;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = igb_get_ethtool_nfc_entry(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = igb_get_ethtool_nfc_all(adapter, cmd, rule_locs);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		ret = igb_get_rss_hash_opts(adapter, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

#घोषणा UDP_RSS_FLAGS (IGB_FLAG_RSS_FIELD_IPV4_UDP | \
		       IGB_FLAG_RSS_FIELD_IPV6_UDP)
अटल पूर्णांक igb_set_rss_hash_opt(काष्ठा igb_adapter *adapter,
				काष्ठा ethtool_rxnfc *nfc)
अणु
	u32 flags = adapter->flags;

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
			flags &= ~IGB_FLAG_RSS_FIELD_IPV4_UDP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			flags |= IGB_FLAG_RSS_FIELD_IPV4_UDP;
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
			flags &= ~IGB_FLAG_RSS_FIELD_IPV6_UDP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			flags |= IGB_FLAG_RSS_FIELD_IPV6_UDP;
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
	अगर (flags != adapter->flags) अणु
		काष्ठा e1000_hw *hw = &adapter->hw;
		u32 mrqc = rd32(E1000_MRQC);

		अगर ((flags & UDP_RSS_FLAGS) &&
		    !(adapter->flags & UDP_RSS_FLAGS))
			dev_err(&adapter->pdev->dev,
				"enabling UDP RSS: fragmented packets may arrive out of order to the stack above\n");

		adapter->flags = flags;

		/* Perक्रमm hash on these packet types */
		mrqc |= E1000_MRQC_RSS_FIELD_IPV4 |
			E1000_MRQC_RSS_FIELD_IPV4_TCP |
			E1000_MRQC_RSS_FIELD_IPV6 |
			E1000_MRQC_RSS_FIELD_IPV6_TCP;

		mrqc &= ~(E1000_MRQC_RSS_FIELD_IPV4_UDP |
			  E1000_MRQC_RSS_FIELD_IPV6_UDP);

		अगर (flags & IGB_FLAG_RSS_FIELD_IPV4_UDP)
			mrqc |= E1000_MRQC_RSS_FIELD_IPV4_UDP;

		अगर (flags & IGB_FLAG_RSS_FIELD_IPV6_UDP)
			mrqc |= E1000_MRQC_RSS_FIELD_IPV6_UDP;

		wr32(E1000_MRQC, mrqc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_rxnfc_ग_लिखो_etype_filter(काष्ठा igb_adapter *adapter,
					काष्ठा igb_nfc_filter *input)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u8 i;
	u32 etqf;
	u16 etype;

	/* find an empty etype filter रेजिस्टर */
	क्रम (i = 0; i < MAX_ETYPE_FILTER; ++i) अणु
		अगर (!adapter->etype_biपंचांगap[i])
			अवरोध;
	पूर्ण
	अगर (i == MAX_ETYPE_FILTER) अणु
		dev_err(&adapter->pdev->dev, "ethtool -N: etype filters are all used.\n");
		वापस -EINVAL;
	पूर्ण

	adapter->etype_biपंचांगap[i] = true;

	etqf = rd32(E1000_ETQF(i));
	etype = ntohs(input->filter.etype & ETHER_TYPE_FULL_MASK);

	etqf |= E1000_ETQF_FILTER_ENABLE;
	etqf &= ~E1000_ETQF_ETYPE_MASK;
	etqf |= (etype & E1000_ETQF_ETYPE_MASK);

	etqf &= ~E1000_ETQF_QUEUE_MASK;
	etqf |= ((input->action << E1000_ETQF_QUEUE_SHIFT)
		& E1000_ETQF_QUEUE_MASK);
	etqf |= E1000_ETQF_QUEUE_ENABLE;

	wr32(E1000_ETQF(i), etqf);

	input->etype_reg_index = i;

	वापस 0;
पूर्ण

अटल पूर्णांक igb_rxnfc_ग_लिखो_vlan_prio_filter(काष्ठा igb_adapter *adapter,
					    काष्ठा igb_nfc_filter *input)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u8 vlan_priority;
	u16 queue_index;
	u32 vlapqf;

	vlapqf = rd32(E1000_VLAPQF);
	vlan_priority = (ntohs(input->filter.vlan_tci) & VLAN_PRIO_MASK)
				>> VLAN_PRIO_SHIFT;
	queue_index = (vlapqf >> (vlan_priority * 4)) & E1000_VLAPQF_QUEUE_MASK;

	/* check whether this vlan prio is alपढ़ोy set */
	अगर ((vlapqf & E1000_VLAPQF_P_VALID(vlan_priority)) &&
	    (queue_index != input->action)) अणु
		dev_err(&adapter->pdev->dev, "ethtool rxnfc set vlan prio filter failed.\n");
		वापस -EEXIST;
	पूर्ण

	vlapqf |= E1000_VLAPQF_P_VALID(vlan_priority);
	vlapqf |= E1000_VLAPQF_QUEUE_SEL(vlan_priority, input->action);

	wr32(E1000_VLAPQF, vlapqf);

	वापस 0;
पूर्ण

पूर्णांक igb_add_filter(काष्ठा igb_adapter *adapter, काष्ठा igb_nfc_filter *input)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err = -EINVAL;

	अगर (hw->mac.type == e1000_i210 &&
	    !(input->filter.match_flags & ~IGB_FILTER_FLAG_SRC_MAC_ADDR)) अणु
		dev_err(&adapter->pdev->dev,
			"i210 doesn't support flow classification rules specifying only source addresses.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (input->filter.match_flags & IGB_FILTER_FLAG_ETHER_TYPE) अणु
		err = igb_rxnfc_ग_लिखो_etype_filter(adapter, input);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (input->filter.match_flags & IGB_FILTER_FLAG_DST_MAC_ADDR) अणु
		err = igb_add_mac_steering_filter(adapter,
						  input->filter.dst_addr,
						  input->action, 0);
		err = min_t(पूर्णांक, err, 0);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (input->filter.match_flags & IGB_FILTER_FLAG_SRC_MAC_ADDR) अणु
		err = igb_add_mac_steering_filter(adapter,
						  input->filter.src_addr,
						  input->action,
						  IGB_MAC_STATE_SRC_ADDR);
		err = min_t(पूर्णांक, err, 0);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (input->filter.match_flags & IGB_FILTER_FLAG_VLAN_TCI)
		err = igb_rxnfc_ग_लिखो_vlan_prio_filter(adapter, input);

	वापस err;
पूर्ण

अटल व्योम igb_clear_etype_filter_regs(काष्ठा igb_adapter *adapter,
					u16 reg_index)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 etqf = rd32(E1000_ETQF(reg_index));

	etqf &= ~E1000_ETQF_QUEUE_ENABLE;
	etqf &= ~E1000_ETQF_QUEUE_MASK;
	etqf &= ~E1000_ETQF_FILTER_ENABLE;

	wr32(E1000_ETQF(reg_index), etqf);

	adapter->etype_biपंचांगap[reg_index] = false;
पूर्ण

अटल व्योम igb_clear_vlan_prio_filter(काष्ठा igb_adapter *adapter,
				       u16 vlan_tci)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u8 vlan_priority;
	u32 vlapqf;

	vlan_priority = (vlan_tci & VLAN_PRIO_MASK) >> VLAN_PRIO_SHIFT;

	vlapqf = rd32(E1000_VLAPQF);
	vlapqf &= ~E1000_VLAPQF_P_VALID(vlan_priority);
	vlapqf &= ~E1000_VLAPQF_QUEUE_SEL(vlan_priority,
						E1000_VLAPQF_QUEUE_MASK);

	wr32(E1000_VLAPQF, vlapqf);
पूर्ण

पूर्णांक igb_erase_filter(काष्ठा igb_adapter *adapter, काष्ठा igb_nfc_filter *input)
अणु
	अगर (input->filter.match_flags & IGB_FILTER_FLAG_ETHER_TYPE)
		igb_clear_etype_filter_regs(adapter,
					    input->etype_reg_index);

	अगर (input->filter.match_flags & IGB_FILTER_FLAG_VLAN_TCI)
		igb_clear_vlan_prio_filter(adapter,
					   ntohs(input->filter.vlan_tci));

	अगर (input->filter.match_flags & IGB_FILTER_FLAG_SRC_MAC_ADDR)
		igb_del_mac_steering_filter(adapter, input->filter.src_addr,
					    input->action,
					    IGB_MAC_STATE_SRC_ADDR);

	अगर (input->filter.match_flags & IGB_FILTER_FLAG_DST_MAC_ADDR)
		igb_del_mac_steering_filter(adapter, input->filter.dst_addr,
					    input->action, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_update_ethtool_nfc_entry(काष्ठा igb_adapter *adapter,
					काष्ठा igb_nfc_filter *input,
					u16 sw_idx)
अणु
	काष्ठा igb_nfc_filter *rule, *parent;
	पूर्णांक err = -EINVAL;

	parent = शून्य;
	rule = शून्य;

	hlist_क्रम_each_entry(rule, &adapter->nfc_filter_list, nfc_node) अणु
		/* hash found, or no matching entry */
		अगर (rule->sw_idx >= sw_idx)
			अवरोध;
		parent = rule;
	पूर्ण

	/* अगर there is an old rule occupying our place हटाओ it */
	अगर (rule && (rule->sw_idx == sw_idx)) अणु
		अगर (!input)
			err = igb_erase_filter(adapter, rule);

		hlist_del(&rule->nfc_node);
		kमुक्त(rule);
		adapter->nfc_filter_count--;
	पूर्ण

	/* If no input this was a delete, err should be 0 अगर a rule was
	 * successfully found and हटाओd from the list अन्यथा -EINVAL
	 */
	अगर (!input)
		वापस err;

	/* initialize node */
	INIT_HLIST_NODE(&input->nfc_node);

	/* add filter to the list */
	अगर (parent)
		hlist_add_behind(&input->nfc_node, &parent->nfc_node);
	अन्यथा
		hlist_add_head(&input->nfc_node, &adapter->nfc_filter_list);

	/* update counts */
	adapter->nfc_filter_count++;

	वापस 0;
पूर्ण

अटल पूर्णांक igb_add_ethtool_nfc_entry(काष्ठा igb_adapter *adapter,
				     काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा igb_nfc_filter *input, *rule;
	पूर्णांक err = 0;

	अगर (!(netdev->hw_features & NETIF_F_NTUPLE))
		वापस -EOPNOTSUPP;

	/* Don't allow programming अगर the action is a queue greater than
	 * the number of online Rx queues.
	 */
	अगर ((fsp->ring_cookie == RX_CLS_FLOW_DISC) ||
	    (fsp->ring_cookie >= adapter->num_rx_queues)) अणु
		dev_err(&adapter->pdev->dev, "ethtool -N: The specified action is invalid\n");
		वापस -EINVAL;
	पूर्ण

	/* Don't allow indexes to exist outside of available space */
	अगर (fsp->location >= IGB_MAX_RXNFC_FILTERS) अणु
		dev_err(&adapter->pdev->dev, "Location out of range\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((fsp->flow_type & ~FLOW_EXT) != ETHER_FLOW)
		वापस -EINVAL;

	input = kzalloc(माप(*input), GFP_KERNEL);
	अगर (!input)
		वापस -ENOMEM;

	अगर (fsp->m_u.ether_spec.h_proto == ETHER_TYPE_FULL_MASK) अणु
		input->filter.etype = fsp->h_u.ether_spec.h_proto;
		input->filter.match_flags = IGB_FILTER_FLAG_ETHER_TYPE;
	पूर्ण

	/* Only support matching addresses by the full mask */
	अगर (is_broadcast_ether_addr(fsp->m_u.ether_spec.h_source)) अणु
		input->filter.match_flags |= IGB_FILTER_FLAG_SRC_MAC_ADDR;
		ether_addr_copy(input->filter.src_addr,
				fsp->h_u.ether_spec.h_source);
	पूर्ण

	/* Only support matching addresses by the full mask */
	अगर (is_broadcast_ether_addr(fsp->m_u.ether_spec.h_dest)) अणु
		input->filter.match_flags |= IGB_FILTER_FLAG_DST_MAC_ADDR;
		ether_addr_copy(input->filter.dst_addr,
				fsp->h_u.ether_spec.h_dest);
	पूर्ण

	अगर ((fsp->flow_type & FLOW_EXT) && fsp->m_ext.vlan_tci) अणु
		अगर (fsp->m_ext.vlan_tci != htons(VLAN_PRIO_MASK)) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण
		input->filter.vlan_tci = fsp->h_ext.vlan_tci;
		input->filter.match_flags |= IGB_FILTER_FLAG_VLAN_TCI;
	पूर्ण

	input->action = fsp->ring_cookie;
	input->sw_idx = fsp->location;

	spin_lock(&adapter->nfc_lock);

	hlist_क्रम_each_entry(rule, &adapter->nfc_filter_list, nfc_node) अणु
		अगर (!स_भेद(&input->filter, &rule->filter,
			    माप(input->filter))) अणु
			err = -EEXIST;
			dev_err(&adapter->pdev->dev,
				"ethtool: this filter is already set\n");
			जाओ err_out_w_lock;
		पूर्ण
	पूर्ण

	err = igb_add_filter(adapter, input);
	अगर (err)
		जाओ err_out_w_lock;

	igb_update_ethtool_nfc_entry(adapter, input, input->sw_idx);

	spin_unlock(&adapter->nfc_lock);
	वापस 0;

err_out_w_lock:
	spin_unlock(&adapter->nfc_lock);
err_out:
	kमुक्त(input);
	वापस err;
पूर्ण

अटल पूर्णांक igb_del_ethtool_nfc_entry(काष्ठा igb_adapter *adapter,
				     काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	पूर्णांक err;

	spin_lock(&adapter->nfc_lock);
	err = igb_update_ethtool_nfc_entry(adapter, शून्य, fsp->location);
	spin_unlock(&adapter->nfc_lock);

	वापस err;
पूर्ण

अटल पूर्णांक igb_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(dev);
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		ret = igb_set_rss_hash_opt(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLINS:
		ret = igb_add_ethtool_nfc_entry(adapter, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		ret = igb_del_ethtool_nfc_entry(adapter, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक igb_get_eee(काष्ठा net_device *netdev, काष्ठा ethtool_eee *edata)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ret_val;
	u16 phy_data;

	अगर ((hw->mac.type < e1000_i350) ||
	    (hw->phy.media_type != e1000_media_type_copper))
		वापस -EOPNOTSUPP;

	edata->supported = (SUPPORTED_1000baseT_Full |
			    SUPPORTED_100baseT_Full);
	अगर (!hw->dev_spec._82575.eee_disable)
		edata->advertised =
			mmd_eee_adv_to_ethtool_adv_t(adapter->eee_advert);

	/* The IPCNFG and EEER रेजिस्टरs are not supported on I354. */
	अगर (hw->mac.type == e1000_i354) अणु
		igb_get_eee_status_i354(hw, (bool *)&edata->eee_active);
	पूर्ण अन्यथा अणु
		u32 eeer;

		eeer = rd32(E1000_EEER);

		/* EEE status on negotiated link */
		अगर (eeer & E1000_EEER_EEE_NEG)
			edata->eee_active = true;

		अगर (eeer & E1000_EEER_TX_LPI_EN)
			edata->tx_lpi_enabled = true;
	पूर्ण

	/* EEE Link Partner Advertised */
	चयन (hw->mac.type) अणु
	हाल e1000_i350:
		ret_val = igb_पढ़ो_emi_reg(hw, E1000_EEE_LP_ADV_ADDR_I350,
					   &phy_data);
		अगर (ret_val)
			वापस -ENODATA;

		edata->lp_advertised = mmd_eee_adv_to_ethtool_adv_t(phy_data);
		अवरोध;
	हाल e1000_i354:
	हाल e1000_i210:
	हाल e1000_i211:
		ret_val = igb_पढ़ो_xmdio_reg(hw, E1000_EEE_LP_ADV_ADDR_I210,
					     E1000_EEE_LP_ADV_DEV_I210,
					     &phy_data);
		अगर (ret_val)
			वापस -ENODATA;

		edata->lp_advertised = mmd_eee_adv_to_ethtool_adv_t(phy_data);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	edata->eee_enabled = !hw->dev_spec._82575.eee_disable;

	अगर ((hw->mac.type == e1000_i354) &&
	    (edata->eee_enabled))
		edata->tx_lpi_enabled = true;

	/* Report correct negotiated EEE status क्रम devices that
	 * wrongly report EEE at half-duplex
	 */
	अगर (adapter->link_duplex == HALF_DUPLEX) अणु
		edata->eee_enabled = false;
		edata->eee_active = false;
		edata->tx_lpi_enabled = false;
		edata->advertised &= ~edata->advertised;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_set_eee(काष्ठा net_device *netdev,
		       काष्ठा ethtool_eee *edata)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा ethtool_eee eee_curr;
	bool adv1g_eee = true, adv100m_eee = true;
	s32 ret_val;

	अगर ((hw->mac.type < e1000_i350) ||
	    (hw->phy.media_type != e1000_media_type_copper))
		वापस -EOPNOTSUPP;

	स_रखो(&eee_curr, 0, माप(काष्ठा ethtool_eee));

	ret_val = igb_get_eee(netdev, &eee_curr);
	अगर (ret_val)
		वापस ret_val;

	अगर (eee_curr.eee_enabled) अणु
		अगर (eee_curr.tx_lpi_enabled != edata->tx_lpi_enabled) अणु
			dev_err(&adapter->pdev->dev,
				"Setting EEE tx-lpi is not supported\n");
			वापस -EINVAL;
		पूर्ण

		/* Tx LPI समयr is not implemented currently */
		अगर (edata->tx_lpi_समयr) अणु
			dev_err(&adapter->pdev->dev,
				"Setting EEE Tx LPI timer is not supported\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!edata->advertised || (edata->advertised &
		    ~(ADVERTISE_100_FULL | ADVERTISE_1000_FULL))) अणु
			dev_err(&adapter->pdev->dev,
				"EEE Advertisement supports only 100Tx and/or 100T full duplex\n");
			वापस -EINVAL;
		पूर्ण
		adv100m_eee = !!(edata->advertised & ADVERTISE_100_FULL);
		adv1g_eee = !!(edata->advertised & ADVERTISE_1000_FULL);

	पूर्ण अन्यथा अगर (!edata->eee_enabled) अणु
		dev_err(&adapter->pdev->dev,
			"Setting EEE options are not supported with EEE disabled\n");
		वापस -EINVAL;
	पूर्ण

	adapter->eee_advert = ethtool_adv_to_mmd_eee_adv_t(edata->advertised);
	अगर (hw->dev_spec._82575.eee_disable != !edata->eee_enabled) अणु
		hw->dev_spec._82575.eee_disable = !edata->eee_enabled;
		adapter->flags |= IGB_FLAG_EEE;

		/* reset link */
		अगर (netअगर_running(netdev))
			igb_reinit_locked(adapter);
		अन्यथा
			igb_reset(adapter);
	पूर्ण

	अगर (hw->mac.type == e1000_i354)
		ret_val = igb_set_eee_i354(hw, adv1g_eee, adv100m_eee);
	अन्यथा
		ret_val = igb_set_eee_i350(hw, adv1g_eee, adv100m_eee);

	अगर (ret_val) अणु
		dev_err(&adapter->pdev->dev,
			"Problem setting EEE advertisement options\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_get_module_info(काष्ठा net_device *netdev,
			       काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 status = 0;
	u16 sff8472_rev, addr_mode;
	bool page_swap = false;

	अगर ((hw->phy.media_type == e1000_media_type_copper) ||
	    (hw->phy.media_type == e1000_media_type_unknown))
		वापस -EOPNOTSUPP;

	/* Check whether we support SFF-8472 or not */
	status = igb_पढ़ो_phy_reg_i2c(hw, IGB_SFF_8472_COMP, &sff8472_rev);
	अगर (status)
		वापस -EIO;

	/* addressing mode is not supported */
	status = igb_पढ़ो_phy_reg_i2c(hw, IGB_SFF_8472_SWAP, &addr_mode);
	अगर (status)
		वापस -EIO;

	/* addressing mode is not supported */
	अगर ((addr_mode & 0xFF) & IGB_SFF_ADDRESSING_MODE) अणु
		hw_dbg("Address change required to access page 0xA2, but not supported. Please report the module type to the driver maintainers.\n");
		page_swap = true;
	पूर्ण

	अगर ((sff8472_rev & 0xFF) == IGB_SFF_8472_UNSUP || page_swap) अणु
		/* We have an SFP, but it करोes not support SFF-8472 */
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	पूर्ण अन्यथा अणु
		/* We have an SFP which supports a revision of SFF-8472 */
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igb_get_module_eeprom(काष्ठा net_device *netdev,
				 काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 status = 0;
	u16 *dataword;
	u16 first_word, last_word;
	पूर्णांक i = 0;

	अगर (ee->len == 0)
		वापस -EINVAL;

	first_word = ee->offset >> 1;
	last_word = (ee->offset + ee->len - 1) >> 1;

	dataword = kदो_स्मृति_array(last_word - first_word + 1, माप(u16),
				 GFP_KERNEL);
	अगर (!dataword)
		वापस -ENOMEM;

	/* Read EEPROM block, SFF-8079/SFF-8472, word at a समय */
	क्रम (i = 0; i < last_word - first_word + 1; i++) अणु
		status = igb_पढ़ो_phy_reg_i2c(hw, (first_word + i) * 2,
					      &dataword[i]);
		अगर (status) अणु
			/* Error occurred जबतक पढ़ोing module */
			kमुक्त(dataword);
			वापस -EIO;
		पूर्ण

		be16_to_cpus(&dataword[i]);
	पूर्ण

	स_नकल(data, (u8 *)dataword + (ee->offset & 1), ee->len);
	kमुक्त(dataword);

	वापस 0;
पूर्ण

अटल पूर्णांक igb_ethtool_begin(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	pm_runसमय_get_sync(&adapter->pdev->dev);
	वापस 0;
पूर्ण

अटल व्योम igb_ethtool_complete(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	pm_runसमय_put(&adapter->pdev->dev);
पूर्ण

अटल u32 igb_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	वापस IGB_RETA_SIZE;
पूर्ण

अटल पूर्णांक igb_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
			u8 *hfunc)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (!indir)
		वापस 0;
	क्रम (i = 0; i < IGB_RETA_SIZE; i++)
		indir[i] = adapter->rss_indir_tbl[i];

	वापस 0;
पूर्ण

व्योम igb_ग_लिखो_rss_indir_tbl(काष्ठा igb_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 reg = E1000_RETA(0);
	u32 shअगरt = 0;
	पूर्णांक i = 0;

	चयन (hw->mac.type) अणु
	हाल e1000_82575:
		shअगरt = 6;
		अवरोध;
	हाल e1000_82576:
		/* 82576 supports 2 RSS queues क्रम SR-IOV */
		अगर (adapter->vfs_allocated_count)
			shअगरt = 3;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	जबतक (i < IGB_RETA_SIZE) अणु
		u32 val = 0;
		पूर्णांक j;

		क्रम (j = 3; j >= 0; j--) अणु
			val <<= 8;
			val |= adapter->rss_indir_tbl[i + j];
		पूर्ण

		wr32(reg, val << shअगरt);
		reg += 4;
		i += 4;
	पूर्ण
पूर्ण

अटल पूर्णांक igb_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
			स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक i;
	u32 num_queues;

	/* We करो not allow change in unsupported parameters */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;
	अगर (!indir)
		वापस 0;

	num_queues = adapter->rss_queues;

	चयन (hw->mac.type) अणु
	हाल e1000_82576:
		/* 82576 supports 2 RSS queues क्रम SR-IOV */
		अगर (adapter->vfs_allocated_count)
			num_queues = 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Verअगरy user input. */
	क्रम (i = 0; i < IGB_RETA_SIZE; i++)
		अगर (indir[i] >= num_queues)
			वापस -EINVAL;


	क्रम (i = 0; i < IGB_RETA_SIZE; i++)
		adapter->rss_indir_tbl[i] = indir[i];

	igb_ग_लिखो_rss_indir_tbl(adapter);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक igb_max_channels(काष्ठा igb_adapter *adapter)
अणु
	वापस igb_get_max_rss_queues(adapter);
पूर्ण

अटल व्योम igb_get_channels(काष्ठा net_device *netdev,
			     काष्ठा ethtool_channels *ch)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);

	/* Report maximum channels */
	ch->max_combined = igb_max_channels(adapter);

	/* Report info क्रम other vector */
	अगर (adapter->flags & IGB_FLAG_HAS_MSIX) अणु
		ch->max_other = NON_Q_VECTORS;
		ch->other_count = NON_Q_VECTORS;
	पूर्ण

	ch->combined_count = adapter->rss_queues;
पूर्ण

अटल पूर्णांक igb_set_channels(काष्ठा net_device *netdev,
			    काष्ठा ethtool_channels *ch)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक count = ch->combined_count;
	अचिन्हित पूर्णांक max_combined = 0;

	/* Verअगरy they are not requesting separate vectors */
	अगर (!count || ch->rx_count || ch->tx_count)
		वापस -EINVAL;

	/* Verअगरy other_count is valid and has not been changed */
	अगर (ch->other_count != NON_Q_VECTORS)
		वापस -EINVAL;

	/* Verअगरy the number of channels करोesn't exceed hw limits */
	max_combined = igb_max_channels(adapter);
	अगर (count > max_combined)
		वापस -EINVAL;

	अगर (count != adapter->rss_queues) अणु
		adapter->rss_queues = count;
		igb_set_flag_queue_pairs(adapter, max_combined);

		/* Hardware has to reinitialize queues and पूर्णांकerrupts to
		 * match the new configuration.
		 */
		वापस igb_reinit_queues(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 igb_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	u32 priv_flags = 0;

	अगर (adapter->flags & IGB_FLAG_RX_LEGACY)
		priv_flags |= IGB_PRIV_FLAGS_LEGACY_RX;

	वापस priv_flags;
पूर्ण

अटल पूर्णांक igb_set_priv_flags(काष्ठा net_device *netdev, u32 priv_flags)
अणु
	काष्ठा igb_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक flags = adapter->flags;

	flags &= ~IGB_FLAG_RX_LEGACY;
	अगर (priv_flags & IGB_PRIV_FLAGS_LEGACY_RX)
		flags |= IGB_FLAG_RX_LEGACY;

	अगर (flags != adapter->flags) अणु
		adapter->flags = flags;

		/* reset पूर्णांकerface to repopulate queues */
		अगर (netअगर_running(netdev))
			igb_reinit_locked(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops igb_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo		= igb_get_drvinfo,
	.get_regs_len		= igb_get_regs_len,
	.get_regs		= igb_get_regs,
	.get_wol		= igb_get_wol,
	.set_wol		= igb_set_wol,
	.get_msglevel		= igb_get_msglevel,
	.set_msglevel		= igb_set_msglevel,
	.nway_reset		= igb_nway_reset,
	.get_link		= igb_get_link,
	.get_eeprom_len		= igb_get_eeprom_len,
	.get_eeprom		= igb_get_eeprom,
	.set_eeprom		= igb_set_eeprom,
	.get_ringparam		= igb_get_ringparam,
	.set_ringparam		= igb_set_ringparam,
	.get_छोड़ोparam		= igb_get_छोड़ोparam,
	.set_छोड़ोparam		= igb_set_छोड़ोparam,
	.self_test		= igb_diag_test,
	.get_strings		= igb_get_strings,
	.set_phys_id		= igb_set_phys_id,
	.get_sset_count		= igb_get_sset_count,
	.get_ethtool_stats	= igb_get_ethtool_stats,
	.get_coalesce		= igb_get_coalesce,
	.set_coalesce		= igb_set_coalesce,
	.get_ts_info		= igb_get_ts_info,
	.get_rxnfc		= igb_get_rxnfc,
	.set_rxnfc		= igb_set_rxnfc,
	.get_eee		= igb_get_eee,
	.set_eee		= igb_set_eee,
	.get_module_info	= igb_get_module_info,
	.get_module_eeprom	= igb_get_module_eeprom,
	.get_rxfh_indir_size	= igb_get_rxfh_indir_size,
	.get_rxfh		= igb_get_rxfh,
	.set_rxfh		= igb_set_rxfh,
	.get_channels		= igb_get_channels,
	.set_channels		= igb_set_channels,
	.get_priv_flags		= igb_get_priv_flags,
	.set_priv_flags		= igb_set_priv_flags,
	.begin			= igb_ethtool_begin,
	.complete		= igb_ethtool_complete,
	.get_link_ksettings	= igb_get_link_ksettings,
	.set_link_ksettings	= igb_set_link_ksettings,
पूर्ण;

व्योम igb_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &igb_ethtool_ops;
पूर्ण
