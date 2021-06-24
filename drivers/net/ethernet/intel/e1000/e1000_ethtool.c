<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2006 Intel Corporation. */

/* ethtool support क्रम e1000 */

#समावेश "e1000.h"
#समावेश <linux/jअगरfies.h>
#समावेश <linux/uaccess.h>

क्रमागत अणुNETDEV_STATS, E1000_STATSपूर्ण;

काष्ठा e1000_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक type;
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा E1000_STAT(m)		E1000_STATS, \
				माप(((काष्ठा e1000_adapter *)0)->m), \
				दुरत्व(काष्ठा e1000_adapter, m)
#घोषणा E1000_NETDEV_STAT(m)	NETDEV_STATS, \
				माप(((काष्ठा net_device *)0)->m), \
				दुरत्व(काष्ठा net_device, m)

अटल स्थिर काष्ठा e1000_stats e1000_gstrings_stats[] = अणु
	अणु "rx_packets", E1000_STAT(stats.gprc) पूर्ण,
	अणु "tx_packets", E1000_STAT(stats.gptc) पूर्ण,
	अणु "rx_bytes", E1000_STAT(stats.gorcl) पूर्ण,
	अणु "tx_bytes", E1000_STAT(stats.gotcl) पूर्ण,
	अणु "rx_broadcast", E1000_STAT(stats.bprc) पूर्ण,
	अणु "tx_broadcast", E1000_STAT(stats.bptc) पूर्ण,
	अणु "rx_multicast", E1000_STAT(stats.mprc) पूर्ण,
	अणु "tx_multicast", E1000_STAT(stats.mptc) पूर्ण,
	अणु "rx_errors", E1000_STAT(stats.rxerrc) पूर्ण,
	अणु "tx_errors", E1000_STAT(stats.txerrc) पूर्ण,
	अणु "tx_dropped", E1000_NETDEV_STAT(stats.tx_dropped) पूर्ण,
	अणु "multicast", E1000_STAT(stats.mprc) पूर्ण,
	अणु "collisions", E1000_STAT(stats.colc) पूर्ण,
	अणु "rx_length_errors", E1000_STAT(stats.rlerrc) पूर्ण,
	अणु "rx_over_errors", E1000_NETDEV_STAT(stats.rx_over_errors) पूर्ण,
	अणु "rx_crc_errors", E1000_STAT(stats.crcerrs) पूर्ण,
	अणु "rx_frame_errors", E1000_NETDEV_STAT(stats.rx_frame_errors) पूर्ण,
	अणु "rx_no_buffer_count", E1000_STAT(stats.rnbc) पूर्ण,
	अणु "rx_missed_errors", E1000_STAT(stats.mpc) पूर्ण,
	अणु "tx_aborted_errors", E1000_STAT(stats.ecol) पूर्ण,
	अणु "tx_carrier_errors", E1000_STAT(stats.tncrs) पूर्ण,
	अणु "tx_fifo_errors", E1000_NETDEV_STAT(stats.tx_fअगरo_errors) पूर्ण,
	अणु "tx_heartbeat_errors", E1000_NETDEV_STAT(stats.tx_heartbeat_errors) पूर्ण,
	अणु "tx_window_errors", E1000_STAT(stats.latecol) पूर्ण,
	अणु "tx_abort_late_coll", E1000_STAT(stats.latecol) पूर्ण,
	अणु "tx_deferred_ok", E1000_STAT(stats.dc) पूर्ण,
	अणु "tx_single_coll_ok", E1000_STAT(stats.scc) पूर्ण,
	अणु "tx_multi_coll_ok", E1000_STAT(stats.mcc) पूर्ण,
	अणु "tx_timeout_count", E1000_STAT(tx_समयout_count) पूर्ण,
	अणु "tx_restart_queue", E1000_STAT(restart_queue) पूर्ण,
	अणु "rx_long_length_errors", E1000_STAT(stats.roc) पूर्ण,
	अणु "rx_short_length_errors", E1000_STAT(stats.ruc) पूर्ण,
	अणु "rx_align_errors", E1000_STAT(stats.algnerrc) पूर्ण,
	अणु "tx_tcp_seg_good", E1000_STAT(stats.tsctc) पूर्ण,
	अणु "tx_tcp_seg_failed", E1000_STAT(stats.tsctfc) पूर्ण,
	अणु "rx_flow_control_xon", E1000_STAT(stats.xonrxc) पूर्ण,
	अणु "rx_flow_control_xoff", E1000_STAT(stats.xoffrxc) पूर्ण,
	अणु "tx_flow_control_xon", E1000_STAT(stats.xontxc) पूर्ण,
	अणु "tx_flow_control_xoff", E1000_STAT(stats.xofftxc) पूर्ण,
	अणु "rx_long_byte_count", E1000_STAT(stats.gorcl) पूर्ण,
	अणु "rx_csum_offload_good", E1000_STAT(hw_csum_good) पूर्ण,
	अणु "rx_csum_offload_errors", E1000_STAT(hw_csum_err) पूर्ण,
	अणु "alloc_rx_buff_failed", E1000_STAT(alloc_rx_buff_failed) पूर्ण,
	अणु "tx_smbus", E1000_STAT(stats.mgptc) पूर्ण,
	अणु "rx_smbus", E1000_STAT(stats.mgprc) पूर्ण,
	अणु "dropped_smbus", E1000_STAT(stats.mgpdc) पूर्ण,
पूर्ण;

#घोषणा E1000_QUEUE_STATS_LEN 0
#घोषणा E1000_GLOBAL_STATS_LEN ARRAY_SIZE(e1000_gstrings_stats)
#घोषणा E1000_STATS_LEN (E1000_GLOBAL_STATS_LEN + E1000_QUEUE_STATS_LEN)
अटल स्थिर अक्षर e1000_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register test  (offline)", "Eeprom test    (offline)",
	"Interrupt test (offline)", "Loopback test  (offline)",
	"Link test   (on/offline)"
पूर्ण;

#घोषणा E1000_TEST_LEN	ARRAY_SIZE(e1000_gstrings_test)

अटल पूर्णांक e1000_get_link_ksettings(काष्ठा net_device *netdev,
				    काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 supported, advertising;

	अगर (hw->media_type == e1000_media_type_copper) अणु
		supported = (SUPPORTED_10baseT_Half |
			     SUPPORTED_10baseT_Full |
			     SUPPORTED_100baseT_Half |
			     SUPPORTED_100baseT_Full |
			     SUPPORTED_1000baseT_Full|
			     SUPPORTED_Autoneg |
			     SUPPORTED_TP);
		advertising = ADVERTISED_TP;

		अगर (hw->स्वतःneg == 1) अणु
			advertising |= ADVERTISED_Autoneg;
			/* the e1000 स्वतःneg seems to match ethtool nicely */
			advertising |= hw->स्वतःneg_advertised;
		पूर्ण

		cmd->base.port = PORT_TP;
		cmd->base.phy_address = hw->phy_addr;
	पूर्ण अन्यथा अणु
		supported   = (SUPPORTED_1000baseT_Full |
			       SUPPORTED_FIBRE |
			       SUPPORTED_Autoneg);

		advertising = (ADVERTISED_1000baseT_Full |
			       ADVERTISED_FIBRE |
			       ADVERTISED_Autoneg);

		cmd->base.port = PORT_FIBRE;
	पूर्ण

	अगर (er32(STATUS) & E1000_STATUS_LU) अणु
		e1000_get_speed_and_duplex(hw, &adapter->link_speed,
					   &adapter->link_duplex);
		cmd->base.speed = adapter->link_speed;

		/* unक्रमtunately FULL_DUPLEX != DUPLEX_FULL
		 * and HALF_DUPLEX != DUPLEX_HALF
		 */
		अगर (adapter->link_duplex == FULL_DUPLEX)
			cmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			cmd->base.duplex = DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	cmd->base.स्वतःneg = ((hw->media_type == e1000_media_type_fiber) ||
			 hw->स्वतःneg) ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	/* MDI-X => 1; MDI => 0 */
	अगर ((hw->media_type == e1000_media_type_copper) &&
	    netअगर_carrier_ok(netdev))
		cmd->base.eth_tp_mdix = (!!adapter->phy_info.mdix_mode ?
				     ETH_TP_MDI_X : ETH_TP_MDI);
	अन्यथा
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;

	अगर (hw->mdix == AUTO_ALL_MODES)
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;
	अन्यथा
		cmd->base.eth_tp_mdix_ctrl = hw->mdix;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_set_link_ksettings(काष्ठा net_device *netdev,
				    स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 advertising;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	/* MDI setting is only allowed when स्वतःneg enabled because
	 * some hardware करोesn't allow MDI setting when speed or
	 * duplex is क्रमced.
	 */
	अगर (cmd->base.eth_tp_mdix_ctrl) अणु
		अगर (hw->media_type != e1000_media_type_copper)
			वापस -EOPNOTSUPP;

		अगर ((cmd->base.eth_tp_mdix_ctrl != ETH_TP_MDI_AUTO) &&
		    (cmd->base.स्वतःneg != AUTONEG_ENABLE)) अणु
			e_err(drv, "forcing MDI/MDI-X state is not supported when link speed and/or duplex are forced\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->flags))
		msleep(1);

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		hw->स्वतःneg = 1;
		अगर (hw->media_type == e1000_media_type_fiber)
			hw->स्वतःneg_advertised = ADVERTISED_1000baseT_Full |
						 ADVERTISED_FIBRE |
						 ADVERTISED_Autoneg;
		अन्यथा
			hw->स्वतःneg_advertised = advertising |
						 ADVERTISED_TP |
						 ADVERTISED_Autoneg;
	पूर्ण अन्यथा अणु
		u32 speed = cmd->base.speed;
		/* calling this overrides क्रमced MDI setting */
		अगर (e1000_set_spd_dplx(adapter, speed, cmd->base.duplex)) अणु
			clear_bit(__E1000_RESETTING, &adapter->flags);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* MDI-X => 2; MDI => 1; Auto => 3 */
	अगर (cmd->base.eth_tp_mdix_ctrl) अणु
		अगर (cmd->base.eth_tp_mdix_ctrl == ETH_TP_MDI_AUTO)
			hw->mdix = AUTO_ALL_MODES;
		अन्यथा
			hw->mdix = cmd->base.eth_tp_mdix_ctrl;
	पूर्ण

	/* reset the link */

	अगर (netअगर_running(adapter->netdev)) अणु
		e1000_करोwn(adapter);
		e1000_up(adapter);
	पूर्ण अन्यथा अणु
		e1000_reset(adapter);
	पूर्ण
	clear_bit(__E1000_RESETTING, &adapter->flags);
	वापस 0;
पूर्ण

अटल u32 e1000_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	/* If the link is not reported up to netdev, पूर्णांकerrupts are disabled,
	 * and so the physical link state may have changed since we last
	 * looked. Set get_link_status to make sure that the true link
	 * state is पूर्णांकerrogated, rather than pulling a cached and possibly
	 * stale link state from the driver.
	 */
	अगर (!netअगर_carrier_ok(netdev))
		adapter->hw.get_link_status = 1;

	वापस e1000_has_link(adapter);
पूर्ण

अटल व्योम e1000_get_छोड़ोparam(काष्ठा net_device *netdev,
				 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	छोड़ो->स्वतःneg =
		(adapter->fc_स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE);

	अगर (hw->fc == E1000_FC_RX_PAUSE) अणु
		छोड़ो->rx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc == E1000_FC_TX_PAUSE) अणु
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc == E1000_FC_FULL) अणु
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

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->flags))
		msleep(1);

	अगर (छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		hw->fc = E1000_FC_FULL;
	अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		hw->fc = E1000_FC_RX_PAUSE;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		hw->fc = E1000_FC_TX_PAUSE;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		hw->fc = E1000_FC_NONE;

	hw->original_fc = hw->fc;

	अगर (adapter->fc_स्वतःneg == AUTONEG_ENABLE) अणु
		अगर (netअगर_running(adapter->netdev)) अणु
			e1000_करोwn(adapter);
			e1000_up(adapter);
		पूर्ण अन्यथा अणु
			e1000_reset(adapter);
		पूर्ण
	पूर्ण अन्यथा
		retval = ((hw->media_type == e1000_media_type_fiber) ?
			  e1000_setup_link(hw) : e1000_क्रमce_mac_fc(hw));

	clear_bit(__E1000_RESETTING, &adapter->flags);
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

अटल पूर्णांक e1000_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा E1000_REGS_LEN 32
	वापस E1000_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम e1000_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs,
			   व्योम *p)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u16 phy_data;

	स_रखो(p, 0, E1000_REGS_LEN * माप(u32));

	regs->version = (1 << 24) | (hw->revision_id << 16) | hw->device_id;

	regs_buff[0]  = er32(CTRL);
	regs_buff[1]  = er32(STATUS);

	regs_buff[2]  = er32(RCTL);
	regs_buff[3]  = er32(RDLEN);
	regs_buff[4]  = er32(RDH);
	regs_buff[5]  = er32(RDT);
	regs_buff[6]  = er32(RDTR);

	regs_buff[7]  = er32(TCTL);
	regs_buff[8]  = er32(TDLEN);
	regs_buff[9]  = er32(TDH);
	regs_buff[10] = er32(TDT);
	regs_buff[11] = er32(TIDV);

	regs_buff[12] = hw->phy_type;  /* PHY type (IGP=1, M88=0) */
	अगर (hw->phy_type == e1000_phy_igp) अणु
		e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PAGE_SELECT,
				    IGP01E1000_PHY_AGC_A);
		e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_AGC_A &
				   IGP01E1000_PHY_PAGE_SELECT, &phy_data);
		regs_buff[13] = (u32)phy_data; /* cable length */
		e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PAGE_SELECT,
				    IGP01E1000_PHY_AGC_B);
		e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_AGC_B &
				   IGP01E1000_PHY_PAGE_SELECT, &phy_data);
		regs_buff[14] = (u32)phy_data; /* cable length */
		e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PAGE_SELECT,
				    IGP01E1000_PHY_AGC_C);
		e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_AGC_C &
				   IGP01E1000_PHY_PAGE_SELECT, &phy_data);
		regs_buff[15] = (u32)phy_data; /* cable length */
		e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PAGE_SELECT,
				    IGP01E1000_PHY_AGC_D);
		e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_AGC_D &
				   IGP01E1000_PHY_PAGE_SELECT, &phy_data);
		regs_buff[16] = (u32)phy_data; /* cable length */
		regs_buff[17] = 0; /* extended 10bt distance (not needed) */
		e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PAGE_SELECT, 0x0);
		e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PORT_STATUS &
				   IGP01E1000_PHY_PAGE_SELECT, &phy_data);
		regs_buff[18] = (u32)phy_data; /* cable polarity */
		e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PAGE_SELECT,
				    IGP01E1000_PHY_PCS_INIT_REG);
		e1000_पढ़ो_phy_reg(hw, IGP01E1000_PHY_PCS_INIT_REG &
				   IGP01E1000_PHY_PAGE_SELECT, &phy_data);
		regs_buff[19] = (u32)phy_data; /* cable polarity */
		regs_buff[20] = 0; /* polarity correction enabled (always) */
		regs_buff[22] = 0; /* phy receive errors (unavailable) */
		regs_buff[23] = regs_buff[18]; /* mdix mode */
		e1000_ग_लिखो_phy_reg(hw, IGP01E1000_PHY_PAGE_SELECT, 0x0);
	पूर्ण अन्यथा अणु
		e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_STATUS, &phy_data);
		regs_buff[13] = (u32)phy_data; /* cable length */
		regs_buff[14] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		regs_buff[15] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		regs_buff[16] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		regs_buff[17] = (u32)phy_data; /* extended 10bt distance */
		regs_buff[18] = regs_buff[13]; /* cable polarity */
		regs_buff[19] = 0;  /* Dummy (to align w/ IGP phy reg dump) */
		regs_buff[20] = regs_buff[17]; /* polarity correction */
		/* phy receive errors */
		regs_buff[22] = adapter->phy_stats.receive_errors;
		regs_buff[23] = regs_buff[13]; /* mdix mode */
	पूर्ण
	regs_buff[21] = adapter->phy_stats.idle_errors;  /* phy idle errors */
	e1000_पढ़ो_phy_reg(hw, PHY_1000T_STATUS, &phy_data);
	regs_buff[24] = (u32)phy_data;  /* phy local receiver status */
	regs_buff[25] = regs_buff[24];  /* phy remote receiver status */
	अगर (hw->mac_type >= e1000_82540 &&
	    hw->media_type == e1000_media_type_copper) अणु
		regs_buff[26] = er32(MANC);
	पूर्ण
पूर्ण

अटल पूर्णांक e1000_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	वापस hw->eeprom.word_size * 2;
पूर्ण

अटल पूर्णांक e1000_get_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
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

	अगर (hw->eeprom.type == e1000_eeprom_spi)
		ret_val = e1000_पढ़ो_eeprom(hw, first_word,
					    last_word - first_word + 1,
					    eeprom_buff);
	अन्यथा अणु
		क्रम (i = 0; i < last_word - first_word + 1; i++) अणु
			ret_val = e1000_पढ़ो_eeprom(hw, first_word + i, 1,
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

अटल पूर्णांक e1000_set_eeprom(काष्ठा net_device *netdev,
			    काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	व्योम *ptr;
	पूर्णांक max_len, first_word, last_word, ret_val = 0;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EOPNOTSUPP;

	अगर (eeprom->magic != (hw->venकरोr_id | (hw->device_id << 16)))
		वापस -EFAULT;

	max_len = hw->eeprom.word_size * 2;

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
		ret_val = e1000_पढ़ो_eeprom(hw, first_word, 1,
					    &eeprom_buff[0]);
		ptr++;
	पूर्ण
	अगर (((eeprom->offset + eeprom->len) & 1) && (ret_val == 0)) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of last changed EEPROM word
		 * only the first byte of the word is being modअगरied
		 */
		ret_val = e1000_पढ़ो_eeprom(hw, last_word, 1,
					    &eeprom_buff[last_word - first_word]);
	पूर्ण

	/* Device's eeprom is always little-endian, word addressable */
	क्रम (i = 0; i < last_word - first_word + 1; i++)
		le16_to_cpus(&eeprom_buff[i]);

	स_नकल(ptr, bytes, eeprom->len);

	क्रम (i = 0; i < last_word - first_word + 1; i++)
		eeprom_buff[i] = cpu_to_le16(eeprom_buff[i]);

	ret_val = e1000_ग_लिखो_eeprom(hw, first_word,
				     last_word - first_word + 1, eeprom_buff);

	/* Update the checksum over the first part of the EEPROM अगर needed */
	अगर ((ret_val == 0) && (first_word <= EEPROM_CHECKSUM_REG))
		e1000_update_eeprom_checksum(hw);

	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल व्योम e1000_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  e1000_driver_name,
		माप(drvinfo->driver));

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम e1000_get_ringparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	e1000_mac_type mac_type = hw->mac_type;
	काष्ठा e1000_tx_ring *txdr = adapter->tx_ring;
	काष्ठा e1000_rx_ring *rxdr = adapter->rx_ring;

	ring->rx_max_pending = (mac_type < e1000_82544) ? E1000_MAX_RXD :
		E1000_MAX_82544_RXD;
	ring->tx_max_pending = (mac_type < e1000_82544) ? E1000_MAX_TXD :
		E1000_MAX_82544_TXD;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
पूर्ण

अटल पूर्णांक e1000_set_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	e1000_mac_type mac_type = hw->mac_type;
	काष्ठा e1000_tx_ring *txdr, *tx_old;
	काष्ठा e1000_rx_ring *rxdr, *rx_old;
	पूर्णांक i, err;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->flags))
		msleep(1);

	अगर (netअगर_running(adapter->netdev))
		e1000_करोwn(adapter);

	tx_old = adapter->tx_ring;
	rx_old = adapter->rx_ring;

	err = -ENOMEM;
	txdr = kसुस्मृति(adapter->num_tx_queues, माप(काष्ठा e1000_tx_ring),
		       GFP_KERNEL);
	अगर (!txdr)
		जाओ err_alloc_tx;

	rxdr = kसुस्मृति(adapter->num_rx_queues, माप(काष्ठा e1000_rx_ring),
		       GFP_KERNEL);
	अगर (!rxdr)
		जाओ err_alloc_rx;

	adapter->tx_ring = txdr;
	adapter->rx_ring = rxdr;

	rxdr->count = max(ring->rx_pending, (u32)E1000_MIN_RXD);
	rxdr->count = min(rxdr->count, (u32)(mac_type < e1000_82544 ?
			  E1000_MAX_RXD : E1000_MAX_82544_RXD));
	rxdr->count = ALIGN(rxdr->count, REQ_RX_DESCRIPTOR_MULTIPLE);
	txdr->count = max(ring->tx_pending, (u32)E1000_MIN_TXD);
	txdr->count = min(txdr->count, (u32)(mac_type < e1000_82544 ?
			  E1000_MAX_TXD : E1000_MAX_82544_TXD));
	txdr->count = ALIGN(txdr->count, REQ_TX_DESCRIPTOR_MULTIPLE);

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		txdr[i].count = txdr->count;
	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		rxdr[i].count = rxdr->count;

	err = 0;
	अगर (netअगर_running(adapter->netdev)) अणु
		/* Try to get new resources beक्रमe deleting old */
		err = e1000_setup_all_rx_resources(adapter);
		अगर (err)
			जाओ err_setup_rx;
		err = e1000_setup_all_tx_resources(adapter);
		अगर (err)
			जाओ err_setup_tx;

		/* save the new, restore the old in order to मुक्त it,
		 * then restore the new back again
		 */

		adapter->rx_ring = rx_old;
		adapter->tx_ring = tx_old;
		e1000_मुक्त_all_rx_resources(adapter);
		e1000_मुक्त_all_tx_resources(adapter);
		adapter->rx_ring = rxdr;
		adapter->tx_ring = txdr;
		err = e1000_up(adapter);
	पूर्ण
	kमुक्त(tx_old);
	kमुक्त(rx_old);

	clear_bit(__E1000_RESETTING, &adapter->flags);
	वापस err;

err_setup_tx:
	e1000_मुक्त_all_rx_resources(adapter);
err_setup_rx:
	adapter->rx_ring = rx_old;
	adapter->tx_ring = tx_old;
	kमुक्त(rxdr);
err_alloc_rx:
	kमुक्त(txdr);
err_alloc_tx:
	अगर (netअगर_running(adapter->netdev))
		e1000_up(adapter);
	clear_bit(__E1000_RESETTING, &adapter->flags);
	वापस err;
पूर्ण

अटल bool reg_pattern_test(काष्ठा e1000_adapter *adapter, u64 *data, पूर्णांक reg,
			     u32 mask, u32 ग_लिखो)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	अटल स्थिर u32 test[] = अणु
		0x5A5A5A5A, 0xA5A5A5A5, 0x00000000, 0xFFFFFFFF
	पूर्ण;
	u8 __iomem *address = hw->hw_addr + reg;
	u32 पढ़ो;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(test); i++) अणु
		ग_लिखोl(ग_लिखो & test[i], address);
		पढ़ो = पढ़ोl(address);
		अगर (पढ़ो != (ग_लिखो & test[i] & mask)) अणु
			e_err(drv, "pattern test reg %04X failed: "
			      "got 0x%08X expected 0x%08X\n",
			      reg, पढ़ो, (ग_लिखो & test[i] & mask));
			*data = reg;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool reg_set_and_check(काष्ठा e1000_adapter *adapter, u64 *data, पूर्णांक reg,
			      u32 mask, u32 ग_लिखो)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u8 __iomem *address = hw->hw_addr + reg;
	u32 पढ़ो;

	ग_लिखोl(ग_लिखो & mask, address);
	पढ़ो = पढ़ोl(address);
	अगर ((पढ़ो & mask) != (ग_लिखो & mask)) अणु
		e_err(drv, "set/check reg %04X test failed: "
		      "got 0x%08X expected 0x%08X\n",
		      reg, (पढ़ो & mask), (ग_लिखो & mask));
		*data = reg;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

#घोषणा REG_PATTERN_TEST(reg, mask, ग_लिखो)			     \
	करो अणु							     \
		अगर (reg_pattern_test(adapter, data,		     \
			     (hw->mac_type >= e1000_82543)   \
			     ? E1000_##reg : E1000_82542_##reg,	     \
			     mask, ग_लिखो))			     \
			वापस 1;				     \
	पूर्ण जबतक (0)

#घोषणा REG_SET_AND_CHECK(reg, mask, ग_लिखो)			     \
	करो अणु							     \
		अगर (reg_set_and_check(adapter, data,		     \
			      (hw->mac_type >= e1000_82543)  \
			      ? E1000_##reg : E1000_82542_##reg,     \
			      mask, ग_लिखो))			     \
			वापस 1;				     \
	पूर्ण जबतक (0)

अटल पूर्णांक e1000_reg_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
	u32 value, beक्रमe, after;
	u32 i, toggle;
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* The status रेजिस्टर is Read Only, so a ग_लिखो should fail.
	 * Some bits that get toggled are ignored.
	 */

	/* there are several bits on newer hardware that are r/w */
	toggle = 0xFFFFF833;

	beक्रमe = er32(STATUS);
	value = (er32(STATUS) & toggle);
	ew32(STATUS, toggle);
	after = er32(STATUS) & toggle;
	अगर (value != after) अणु
		e_err(drv, "failed STATUS register test got: "
		      "0x%08X expected: 0x%08X\n", after, value);
		*data = 1;
		वापस 1;
	पूर्ण
	/* restore previous status */
	ew32(STATUS, beक्रमe);

	REG_PATTERN_TEST(FCAL, 0xFFFFFFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(FCAH, 0x0000FFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(FCT, 0x0000FFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(VET, 0x0000FFFF, 0xFFFFFFFF);

	REG_PATTERN_TEST(RDTR, 0x0000FFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(RDBAH, 0xFFFFFFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(RDLEN, 0x000FFF80, 0x000FFFFF);
	REG_PATTERN_TEST(RDH, 0x0000FFFF, 0x0000FFFF);
	REG_PATTERN_TEST(RDT, 0x0000FFFF, 0x0000FFFF);
	REG_PATTERN_TEST(FCRTH, 0x0000FFF8, 0x0000FFF8);
	REG_PATTERN_TEST(FCTTV, 0x0000FFFF, 0x0000FFFF);
	REG_PATTERN_TEST(TIPG, 0x3FFFFFFF, 0x3FFFFFFF);
	REG_PATTERN_TEST(TDBAH, 0xFFFFFFFF, 0xFFFFFFFF);
	REG_PATTERN_TEST(TDLEN, 0x000FFF80, 0x000FFFFF);

	REG_SET_AND_CHECK(RCTL, 0xFFFFFFFF, 0x00000000);

	beक्रमe = 0x06DFB3FE;
	REG_SET_AND_CHECK(RCTL, beक्रमe, 0x003FFFFB);
	REG_SET_AND_CHECK(TCTL, 0xFFFFFFFF, 0x00000000);

	अगर (hw->mac_type >= e1000_82543) अणु
		REG_SET_AND_CHECK(RCTL, beक्रमe, 0xFFFFFFFF);
		REG_PATTERN_TEST(RDBAL, 0xFFFFFFF0, 0xFFFFFFFF);
		REG_PATTERN_TEST(TXCW, 0xC000FFFF, 0x0000FFFF);
		REG_PATTERN_TEST(TDBAL, 0xFFFFFFF0, 0xFFFFFFFF);
		REG_PATTERN_TEST(TIDV, 0x0000FFFF, 0x0000FFFF);
		value = E1000_RAR_ENTRIES;
		क्रम (i = 0; i < value; i++) अणु
			REG_PATTERN_TEST(RA + (((i << 1) + 1) << 2),
					 0x8003FFFF, 0xFFFFFFFF);
		पूर्ण
	पूर्ण अन्यथा अणु
		REG_SET_AND_CHECK(RCTL, 0xFFFFFFFF, 0x01FFFFFF);
		REG_PATTERN_TEST(RDBAL, 0xFFFFF000, 0xFFFFFFFF);
		REG_PATTERN_TEST(TXCW, 0x0000FFFF, 0x0000FFFF);
		REG_PATTERN_TEST(TDBAL, 0xFFFFF000, 0xFFFFFFFF);
	पूर्ण

	value = E1000_MC_TBL_SIZE;
	क्रम (i = 0; i < value; i++)
		REG_PATTERN_TEST(MTA + (i << 2), 0xFFFFFFFF, 0xFFFFFFFF);

	*data = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक e1000_eeprom_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 temp;
	u16 checksum = 0;
	u16 i;

	*data = 0;
	/* Read and add up the contents of the EEPROM */
	क्रम (i = 0; i < (EEPROM_CHECKSUM_REG + 1); i++) अणु
		अगर ((e1000_पढ़ो_eeprom(hw, i, 1, &temp)) < 0) अणु
			*data = 1;
			अवरोध;
		पूर्ण
		checksum += temp;
	पूर्ण

	/* If Checksum is not Correct वापस error अन्यथा test passed */
	अगर ((checksum != (u16)EEPROM_SUM) && !(*data))
		*data = 2;

	वापस *data;
पूर्ण

अटल irqवापस_t e1000_test_पूर्णांकr(पूर्णांक irq, व्योम *data)
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
	u32 mask, i = 0;
	bool shared_पूर्णांक = true;
	u32 irq = adapter->pdev->irq;
	काष्ठा e1000_hw *hw = &adapter->hw;

	*data = 0;

	/* NOTE: we करोn't test MSI पूर्णांकerrupts here, yet
	 * Hook up test पूर्णांकerrupt handler just क्रम this test
	 */
	अगर (!request_irq(irq, e1000_test_पूर्णांकr, IRQF_PROBE_SHARED, netdev->name,
			 netdev))
		shared_पूर्णांक = false;
	अन्यथा अगर (request_irq(irq, e1000_test_पूर्णांकr, IRQF_SHARED,
			     netdev->name, netdev)) अणु
		*data = 1;
		वापस -1;
	पूर्ण
	e_info(hw, "testing %s interrupt\n", (shared_पूर्णांक ?
	       "shared" : "unshared"));

	/* Disable all the पूर्णांकerrupts */
	ew32(IMC, 0xFFFFFFFF);
	E1000_WRITE_FLUSH();
	msleep(10);

	/* Test each पूर्णांकerrupt */
	क्रम (; i < 10; i++) अणु
		/* Interrupt to test */
		mask = 1 << i;

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
			E1000_WRITE_FLUSH();
			msleep(10);

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
		E1000_WRITE_FLUSH();
		msleep(10);

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
			E1000_WRITE_FLUSH();
			msleep(10);

			अगर (adapter->test_icr) अणु
				*data = 5;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable all the पूर्णांकerrupts */
	ew32(IMC, 0xFFFFFFFF);
	E1000_WRITE_FLUSH();
	msleep(10);

	/* Unhook test पूर्णांकerrupt handler */
	मुक्त_irq(irq, netdev);

	वापस *data;
पूर्ण

अटल व्योम e1000_मुक्त_desc_rings(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_tx_ring *txdr = &adapter->test_tx_ring;
	काष्ठा e1000_rx_ring *rxdr = &adapter->test_rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक i;

	अगर (txdr->desc && txdr->buffer_info) अणु
		क्रम (i = 0; i < txdr->count; i++) अणु
			अगर (txdr->buffer_info[i].dma)
				dma_unmap_single(&pdev->dev,
						 txdr->buffer_info[i].dma,
						 txdr->buffer_info[i].length,
						 DMA_TO_DEVICE);
			dev_kमुक्त_skb(txdr->buffer_info[i].skb);
		पूर्ण
	पूर्ण

	अगर (rxdr->desc && rxdr->buffer_info) अणु
		क्रम (i = 0; i < rxdr->count; i++) अणु
			अगर (rxdr->buffer_info[i].dma)
				dma_unmap_single(&pdev->dev,
						 rxdr->buffer_info[i].dma,
						 E1000_RXBUFFER_2048,
						 DMA_FROM_DEVICE);
			kमुक्त(rxdr->buffer_info[i].rxbuf.data);
		पूर्ण
	पूर्ण

	अगर (txdr->desc) अणु
		dma_मुक्त_coherent(&pdev->dev, txdr->size, txdr->desc,
				  txdr->dma);
		txdr->desc = शून्य;
	पूर्ण
	अगर (rxdr->desc) अणु
		dma_मुक्त_coherent(&pdev->dev, rxdr->size, rxdr->desc,
				  rxdr->dma);
		rxdr->desc = शून्य;
	पूर्ण

	kमुक्त(txdr->buffer_info);
	txdr->buffer_info = शून्य;
	kमुक्त(rxdr->buffer_info);
	rxdr->buffer_info = शून्य;
पूर्ण

अटल पूर्णांक e1000_setup_desc_rings(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_tx_ring *txdr = &adapter->test_tx_ring;
	काष्ठा e1000_rx_ring *rxdr = &adapter->test_rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	u32 rctl;
	पूर्णांक i, ret_val;

	/* Setup Tx descriptor ring and Tx buffers */

	अगर (!txdr->count)
		txdr->count = E1000_DEFAULT_TXD;

	txdr->buffer_info = kसुस्मृति(txdr->count, माप(काष्ठा e1000_tx_buffer),
				    GFP_KERNEL);
	अगर (!txdr->buffer_info) अणु
		ret_val = 1;
		जाओ err_nomem;
	पूर्ण

	txdr->size = txdr->count * माप(काष्ठा e1000_tx_desc);
	txdr->size = ALIGN(txdr->size, 4096);
	txdr->desc = dma_alloc_coherent(&pdev->dev, txdr->size, &txdr->dma,
					GFP_KERNEL);
	अगर (!txdr->desc) अणु
		ret_val = 2;
		जाओ err_nomem;
	पूर्ण
	txdr->next_to_use = txdr->next_to_clean = 0;

	ew32(TDBAL, ((u64)txdr->dma & 0x00000000FFFFFFFF));
	ew32(TDBAH, ((u64)txdr->dma >> 32));
	ew32(TDLEN, txdr->count * माप(काष्ठा e1000_tx_desc));
	ew32(TDH, 0);
	ew32(TDT, 0);
	ew32(TCTL, E1000_TCTL_PSP | E1000_TCTL_EN |
	     E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT |
	     E1000_FDX_COLLISION_DISTANCE << E1000_COLD_SHIFT);

	क्रम (i = 0; i < txdr->count; i++) अणु
		काष्ठा e1000_tx_desc *tx_desc = E1000_TX_DESC(*txdr, i);
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक size = 1024;

		skb = alloc_skb(size, GFP_KERNEL);
		अगर (!skb) अणु
			ret_val = 3;
			जाओ err_nomem;
		पूर्ण
		skb_put(skb, size);
		txdr->buffer_info[i].skb = skb;
		txdr->buffer_info[i].length = skb->len;
		txdr->buffer_info[i].dma =
			dma_map_single(&pdev->dev, skb->data, skb->len,
				       DMA_TO_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, txdr->buffer_info[i].dma)) अणु
			ret_val = 4;
			जाओ err_nomem;
		पूर्ण
		tx_desc->buffer_addr = cpu_to_le64(txdr->buffer_info[i].dma);
		tx_desc->lower.data = cpu_to_le32(skb->len);
		tx_desc->lower.data |= cpu_to_le32(E1000_TXD_CMD_EOP |
						   E1000_TXD_CMD_IFCS |
						   E1000_TXD_CMD_RPS);
		tx_desc->upper.data = 0;
	पूर्ण

	/* Setup Rx descriptor ring and Rx buffers */

	अगर (!rxdr->count)
		rxdr->count = E1000_DEFAULT_RXD;

	rxdr->buffer_info = kसुस्मृति(rxdr->count, माप(काष्ठा e1000_rx_buffer),
				    GFP_KERNEL);
	अगर (!rxdr->buffer_info) अणु
		ret_val = 5;
		जाओ err_nomem;
	पूर्ण

	rxdr->size = rxdr->count * माप(काष्ठा e1000_rx_desc);
	rxdr->desc = dma_alloc_coherent(&pdev->dev, rxdr->size, &rxdr->dma,
					GFP_KERNEL);
	अगर (!rxdr->desc) अणु
		ret_val = 6;
		जाओ err_nomem;
	पूर्ण
	rxdr->next_to_use = rxdr->next_to_clean = 0;

	rctl = er32(RCTL);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);
	ew32(RDBAL, ((u64)rxdr->dma & 0xFFFFFFFF));
	ew32(RDBAH, ((u64)rxdr->dma >> 32));
	ew32(RDLEN, rxdr->size);
	ew32(RDH, 0);
	ew32(RDT, 0);
	rctl = E1000_RCTL_EN | E1000_RCTL_BAM | E1000_RCTL_SZ_2048 |
		E1000_RCTL_LBM_NO | E1000_RCTL_RDMTS_HALF |
		(hw->mc_filter_type << E1000_RCTL_MO_SHIFT);
	ew32(RCTL, rctl);

	क्रम (i = 0; i < rxdr->count; i++) अणु
		काष्ठा e1000_rx_desc *rx_desc = E1000_RX_DESC(*rxdr, i);
		u8 *buf;

		buf = kzalloc(E1000_RXBUFFER_2048 + NET_SKB_PAD + NET_IP_ALIGN,
			      GFP_KERNEL);
		अगर (!buf) अणु
			ret_val = 7;
			जाओ err_nomem;
		पूर्ण
		rxdr->buffer_info[i].rxbuf.data = buf;

		rxdr->buffer_info[i].dma =
			dma_map_single(&pdev->dev,
				       buf + NET_SKB_PAD + NET_IP_ALIGN,
				       E1000_RXBUFFER_2048, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, rxdr->buffer_info[i].dma)) अणु
			ret_val = 8;
			जाओ err_nomem;
		पूर्ण
		rx_desc->buffer_addr = cpu_to_le64(rxdr->buffer_info[i].dma);
	पूर्ण

	वापस 0;

err_nomem:
	e1000_मुक्त_desc_rings(adapter);
	वापस ret_val;
पूर्ण

अटल व्योम e1000_phy_disable_receiver(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Write out to PHY रेजिस्टरs 29 and 30 to disable the Receiver. */
	e1000_ग_लिखो_phy_reg(hw, 29, 0x001F);
	e1000_ग_लिखो_phy_reg(hw, 30, 0x8FFC);
	e1000_ग_लिखो_phy_reg(hw, 29, 0x001A);
	e1000_ग_लिखो_phy_reg(hw, 30, 0x8FF0);
पूर्ण

अटल व्योम e1000_phy_reset_clk_and_crs(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 phy_reg;

	/* Because we reset the PHY above, we need to re-क्रमce TX_CLK in the
	 * Extended PHY Specअगरic Control Register to 25MHz घड़ी.  This
	 * value शेषs back to a 2.5MHz घड़ी when the PHY is reset.
	 */
	e1000_पढ़ो_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_reg);
	phy_reg |= M88E1000_EPSCR_TX_CLK_25;
	e1000_ग_लिखो_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_reg);

	/* In addition, because of the s/w reset above, we need to enable
	 * CRS on TX.  This must be set क्रम both full and half duplex
	 * operation.
	 */
	e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_reg);
	phy_reg |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
	e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_reg);
पूर्ण

अटल पूर्णांक e1000_nonपूर्णांकegrated_phy_loopback(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_reg;
	u16 phy_reg;

	/* Setup the Device Control Register क्रम PHY loopback test. */

	ctrl_reg = er32(CTRL);
	ctrl_reg |= (E1000_CTRL_ILOS |		/* Invert Loss-Of-Signal */
		     E1000_CTRL_FRCSPD |	/* Set the Force Speed Bit */
		     E1000_CTRL_FRCDPX |	/* Set the Force Duplex Bit */
		     E1000_CTRL_SPD_1000 |	/* Force Speed to 1000 */
		     E1000_CTRL_FD);		/* Force Duplex to FULL */

	ew32(CTRL, ctrl_reg);

	/* Read the PHY Specअगरic Control Register (0x10) */
	e1000_पढ़ो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_reg);

	/* Clear Auto-Crossover bits in PHY Specअगरic Control Register
	 * (bits 6:5).
	 */
	phy_reg &= ~M88E1000_PSCR_AUTO_X_MODE;
	e1000_ग_लिखो_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_reg);

	/* Perक्रमm software reset on the PHY */
	e1000_phy_reset(hw);

	/* Have to setup TX_CLK and TX_CRS after software reset */
	e1000_phy_reset_clk_and_crs(adapter);

	e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, 0x8100);

	/* Wait क्रम reset to complete. */
	udelay(500);

	/* Have to setup TX_CLK and TX_CRS after software reset */
	e1000_phy_reset_clk_and_crs(adapter);

	/* Write out to PHY रेजिस्टरs 29 and 30 to disable the Receiver. */
	e1000_phy_disable_receiver(adapter);

	/* Set the loopback bit in the PHY control रेजिस्टर. */
	e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_reg);
	phy_reg |= MII_CR_LOOPBACK;
	e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, phy_reg);

	/* Setup TX_CLK and TX_CRS one more समय. */
	e1000_phy_reset_clk_and_crs(adapter);

	/* Check Phy Configuration */
	e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_reg);
	अगर (phy_reg != 0x4100)
		वापस 9;

	e1000_पढ़ो_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_reg);
	अगर (phy_reg != 0x0070)
		वापस 10;

	e1000_पढ़ो_phy_reg(hw, 29, &phy_reg);
	अगर (phy_reg != 0x001A)
		वापस 11;

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_पूर्णांकegrated_phy_loopback(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_reg = 0;
	u32 stat_reg = 0;

	hw->स्वतःneg = false;

	अगर (hw->phy_type == e1000_phy_m88) अणु
		/* Auto-MDI/MDIX Off */
		e1000_ग_लिखो_phy_reg(hw,
				    M88E1000_PHY_SPEC_CTRL, 0x0808);
		/* reset to update Auto-MDI/MDIX */
		e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, 0x9140);
		/* स्वतःneg off */
		e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, 0x8140);
	पूर्ण

	ctrl_reg = er32(CTRL);

	/* क्रमce 1000, set loopback */
	e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, 0x4140);

	/* Now set up the MAC to the same speed/duplex as the PHY. */
	ctrl_reg = er32(CTRL);
	ctrl_reg &= ~E1000_CTRL_SPD_SEL; /* Clear the speed sel bits */
	ctrl_reg |= (E1000_CTRL_FRCSPD | /* Set the Force Speed Bit */
			E1000_CTRL_FRCDPX | /* Set the Force Duplex Bit */
			E1000_CTRL_SPD_1000 |/* Force Speed to 1000 */
			E1000_CTRL_FD); /* Force Duplex to FULL */

	अगर (hw->media_type == e1000_media_type_copper &&
	    hw->phy_type == e1000_phy_m88)
		ctrl_reg |= E1000_CTRL_ILOS; /* Invert Loss of Signal */
	अन्यथा अणु
		/* Set the ILOS bit on the fiber Nic is half
		 * duplex link is detected.
		 */
		stat_reg = er32(STATUS);
		अगर ((stat_reg & E1000_STATUS_FD) == 0)
			ctrl_reg |= (E1000_CTRL_ILOS | E1000_CTRL_SLU);
	पूर्ण

	ew32(CTRL, ctrl_reg);

	/* Disable the receiver on the PHY so when a cable is plugged in, the
	 * PHY करोes not begin to स्वतःneg when a cable is reconnected to the NIC.
	 */
	अगर (hw->phy_type == e1000_phy_m88)
		e1000_phy_disable_receiver(adapter);

	udelay(500);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_set_phy_loopback(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 phy_reg = 0;
	u16 count = 0;

	चयन (hw->mac_type) अणु
	हाल e1000_82543:
		अगर (hw->media_type == e1000_media_type_copper) अणु
			/* Attempt to setup Loopback mode on Non-पूर्णांकegrated PHY.
			 * Some PHY रेजिस्टरs get corrupted at अक्रमom, so
			 * attempt this 10 बार.
			 */
			जबतक (e1000_nonपूर्णांकegrated_phy_loopback(adapter) &&
			       count++ < 10);
			अगर (count < 11)
				वापस 0;
		पूर्ण
		अवरोध;

	हाल e1000_82544:
	हाल e1000_82540:
	हाल e1000_82545:
	हाल e1000_82545_rev_3:
	हाल e1000_82546:
	हाल e1000_82546_rev_3:
	हाल e1000_82541:
	हाल e1000_82541_rev_2:
	हाल e1000_82547:
	हाल e1000_82547_rev_2:
		वापस e1000_पूर्णांकegrated_phy_loopback(adapter);
	शेष:
		/* Default PHY loopback work is to पढ़ो the MII
		 * control रेजिस्टर and निश्चित bit 14 (loopback mode).
		 */
		e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_reg);
		phy_reg |= MII_CR_LOOPBACK;
		e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, phy_reg);
		वापस 0;
	पूर्ण

	वापस 8;
पूर्ण

अटल पूर्णांक e1000_setup_loopback_test(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;

	अगर (hw->media_type == e1000_media_type_fiber ||
	    hw->media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
		चयन (hw->mac_type) अणु
		हाल e1000_82545:
		हाल e1000_82546:
		हाल e1000_82545_rev_3:
		हाल e1000_82546_rev_3:
			वापस e1000_set_phy_loopback(adapter);
		शेष:
			rctl = er32(RCTL);
			rctl |= E1000_RCTL_LBM_TCVR;
			ew32(RCTL, rctl);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अगर (hw->media_type == e1000_media_type_copper) अणु
		वापस e1000_set_phy_loopback(adapter);
	पूर्ण

	वापस 7;
पूर्ण

अटल व्योम e1000_loopback_cleanup(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;
	u16 phy_reg;

	rctl = er32(RCTL);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);
	ew32(RCTL, rctl);

	चयन (hw->mac_type) अणु
	हाल e1000_82545:
	हाल e1000_82546:
	हाल e1000_82545_rev_3:
	हाल e1000_82546_rev_3:
	शेष:
		hw->स्वतःneg = true;
		e1000_पढ़ो_phy_reg(hw, PHY_CTRL, &phy_reg);
		अगर (phy_reg & MII_CR_LOOPBACK) अणु
			phy_reg &= ~MII_CR_LOOPBACK;
			e1000_ग_लिखो_phy_reg(hw, PHY_CTRL, phy_reg);
			e1000_phy_reset(hw);
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

अटल पूर्णांक e1000_check_lbtest_frame(स्थिर अचिन्हित अक्षर *data,
				    अचिन्हित पूर्णांक frame_size)
अणु
	frame_size &= ~1;
	अगर (*(data + 3) == 0xFF) अणु
		अगर ((*(data + frame_size / 2 + 10) == 0xBE) &&
		    (*(data + frame_size / 2 + 12) == 0xAF)) अणु
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 13;
पूर्ण

अटल पूर्णांक e1000_run_loopback_test(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_tx_ring *txdr = &adapter->test_tx_ring;
	काष्ठा e1000_rx_ring *rxdr = &adapter->test_rx_ring;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक i, j, k, l, lc, good_cnt, ret_val = 0;
	अचिन्हित दीर्घ समय;

	ew32(RDT, rxdr->count - 1);

	/* Calculate the loop count based on the largest descriptor ring
	 * The idea is to wrap the largest ring a number of बार using 64
	 * send/receive pairs during each loop
	 */

	अगर (rxdr->count <= txdr->count)
		lc = ((txdr->count / 64) * 2) + 1;
	अन्यथा
		lc = ((rxdr->count / 64) * 2) + 1;

	k = l = 0;
	क्रम (j = 0; j <= lc; j++) अणु /* loop count loop */
		क्रम (i = 0; i < 64; i++) अणु /* send the packets */
			e1000_create_lbtest_frame(txdr->buffer_info[i].skb,
						  1024);
			dma_sync_single_क्रम_device(&pdev->dev,
						   txdr->buffer_info[k].dma,
						   txdr->buffer_info[k].length,
						   DMA_TO_DEVICE);
			अगर (unlikely(++k == txdr->count))
				k = 0;
		पूर्ण
		ew32(TDT, k);
		E1000_WRITE_FLUSH();
		msleep(200);
		समय = jअगरfies; /* set the start समय क्रम the receive */
		good_cnt = 0;
		करो अणु /* receive the sent packets */
			dma_sync_single_क्रम_cpu(&pdev->dev,
						rxdr->buffer_info[l].dma,
						E1000_RXBUFFER_2048,
						DMA_FROM_DEVICE);

			ret_val = e1000_check_lbtest_frame(
					rxdr->buffer_info[l].rxbuf.data +
					NET_SKB_PAD + NET_IP_ALIGN,
					1024);
			अगर (!ret_val)
				good_cnt++;
			अगर (unlikely(++l == rxdr->count))
				l = 0;
			/* समय + 20 msecs (200 msecs on 2.4) is more than
			 * enough समय to complete the receives, अगर it's
			 * exceeded, अवरोध and error off
			 */
		पूर्ण जबतक (good_cnt < 64 && समय_after(समय + 20, jअगरfies));

		अगर (good_cnt != 64) अणु
			ret_val = 13; /* ret_val is the same as mis-compare */
			अवरोध;
		पूर्ण
		अगर (समय_after_eq(jअगरfies, समय + 2)) अणु
			ret_val = 14; /* error code क्रम समय out error */
			अवरोध;
		पूर्ण
	पूर्ण /* end loop count loop */
	वापस ret_val;
पूर्ण

अटल पूर्णांक e1000_loopback_test(काष्ठा e1000_adapter *adapter, u64 *data)
अणु
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
	अगर (hw->media_type == e1000_media_type_पूर्णांकernal_serdes) अणु
		पूर्णांक i = 0;

		hw->serdes_has_link = false;

		/* On some blade server designs, link establishment
		 * could take as दीर्घ as 2-3 minutes
		 */
		करो अणु
			e1000_check_क्रम_link(hw);
			अगर (hw->serdes_has_link)
				वापस *data;
			msleep(20);
		पूर्ण जबतक (i++ < 3750);

		*data = 1;
	पूर्ण अन्यथा अणु
		e1000_check_क्रम_link(hw);
		अगर (hw->स्वतःneg)  /* अगर स्वतः_neg is set रुको क्रम it */
			msleep(4000);

		अगर (!(er32(STATUS) & E1000_STATUS_LU))
			*data = 1;
	पूर्ण
	वापस *data;
पूर्ण

अटल पूर्णांक e1000_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_TEST:
		वापस E1000_TEST_LEN;
	हाल ETH_SS_STATS:
		वापस E1000_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम e1000_diag_test(काष्ठा net_device *netdev,
			    काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	bool अगर_running = netअगर_running(netdev);

	set_bit(__E1000_TESTING, &adapter->flags);
	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		/* Offline tests */

		/* save speed, duplex, स्वतःneg settings */
		u16 स्वतःneg_advertised = hw->स्वतःneg_advertised;
		u8 क्रमced_speed_duplex = hw->क्रमced_speed_duplex;
		u8 स्वतःneg = hw->स्वतःneg;

		e_info(hw, "offline testing starting\n");

		/* Link test perक्रमmed beक्रमe hardware reset so स्वतःneg करोesn't
		 * पूर्णांकerfere with test result
		 */
		अगर (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (अगर_running)
			/* indicate we're in test mode */
			e1000_बंद(netdev);
		अन्यथा
			e1000_reset(adapter);

		अगर (e1000_reg_test(adapter, &data[0]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000_reset(adapter);
		अगर (e1000_eeprom_test(adapter, &data[1]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000_reset(adapter);
		अगर (e1000_पूर्णांकr_test(adapter, &data[2]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		e1000_reset(adapter);
		/* make sure the phy is घातered up */
		e1000_घातer_up_phy(adapter);
		अगर (e1000_loopback_test(adapter, &data[3]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* restore speed, duplex, स्वतःneg settings */
		hw->स्वतःneg_advertised = स्वतःneg_advertised;
		hw->क्रमced_speed_duplex = क्रमced_speed_duplex;
		hw->स्वतःneg = स्वतःneg;

		e1000_reset(adapter);
		clear_bit(__E1000_TESTING, &adapter->flags);
		अगर (अगर_running)
			e1000_खोलो(netdev);
	पूर्ण अन्यथा अणु
		e_info(hw, "online testing starting\n");
		/* Online tests */
		अगर (e1000_link_test(adapter, &data[4]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Online tests aren't run; pass by शेष */
		data[0] = 0;
		data[1] = 0;
		data[2] = 0;
		data[3] = 0;

		clear_bit(__E1000_TESTING, &adapter->flags);
	पूर्ण
	msleep_पूर्णांकerruptible(4 * 1000);
पूर्ण

अटल पूर्णांक e1000_wol_exclusion(काष्ठा e1000_adapter *adapter,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक retval = 1; /* fail by शेष */

	चयन (hw->device_id) अणु
	हाल E1000_DEV_ID_82542:
	हाल E1000_DEV_ID_82543GC_FIBER:
	हाल E1000_DEV_ID_82543GC_COPPER:
	हाल E1000_DEV_ID_82544EI_FIBER:
	हाल E1000_DEV_ID_82546EB_QUAD_COPPER:
	हाल E1000_DEV_ID_82545EM_FIBER:
	हाल E1000_DEV_ID_82545EM_COPPER:
	हाल E1000_DEV_ID_82546GB_QUAD_COPPER:
	हाल E1000_DEV_ID_82546GB_PCIE:
		/* these करोn't support WoL at all */
		wol->supported = 0;
		अवरोध;
	हाल E1000_DEV_ID_82546EB_FIBER:
	हाल E1000_DEV_ID_82546GB_FIBER:
		/* Wake events not supported on port B */
		अगर (er32(STATUS) & E1000_STATUS_FUNC_1) अणु
			wol->supported = 0;
			अवरोध;
		पूर्ण
		/* वापस success क्रम non excluded adapter ports */
		retval = 0;
		अवरोध;
	हाल E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		/* quad port adapters only support WoL on port A */
		अगर (!adapter->quad_port_a) अणु
			wol->supported = 0;
			अवरोध;
		पूर्ण
		/* वापस success क्रम non excluded adapter ports */
		retval = 0;
		अवरोध;
	शेष:
		/* dual port cards only support WoL on port A from now on
		 * unless it was enabled in the eeprom क्रम port B
		 * so exclude FUNC_1 ports from having WoL enabled
		 */
		अगर (er32(STATUS) & E1000_STATUS_FUNC_1 &&
		    !adapter->eeprom_wol) अणु
			wol->supported = 0;
			अवरोध;
		पूर्ण

		retval = 0;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम e1000_get_wol(काष्ठा net_device *netdev,
			  काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	wol->supported = WAKE_UCAST | WAKE_MCAST | WAKE_BCAST | WAKE_MAGIC;
	wol->wolopts = 0;

	/* this function will set ->supported = 0 and वापस 1 अगर wol is not
	 * supported by this hardware
	 */
	अगर (e1000_wol_exclusion(adapter, wol) ||
	    !device_can_wakeup(&adapter->pdev->dev))
		वापस;

	/* apply any specअगरic unsupported masks here */
	चयन (hw->device_id) अणु
	हाल E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		/* KSP3 करोes not support UCAST wake-ups */
		wol->supported &= ~WAKE_UCAST;

		अगर (adapter->wol & E1000_WUFC_EX)
			e_err(drv, "Interface does not support directed "
			      "(unicast) frame wake-up packets\n");
		अवरोध;
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
पूर्ण

अटल पूर्णांक e1000_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (wol->wolopts & (WAKE_PHY | WAKE_ARP | WAKE_MAGICSECURE))
		वापस -EOPNOTSUPP;

	अगर (e1000_wol_exclusion(adapter, wol) ||
	    !device_can_wakeup(&adapter->pdev->dev))
		वापस wol->wolopts ? -EOPNOTSUPP : 0;

	चयन (hw->device_id) अणु
	हाल E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		अगर (wol->wolopts & WAKE_UCAST) अणु
			e_err(drv, "Interface does not support directed "
			      "(unicast) frame wake-up packets\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

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
		e1000_setup_led(hw);
		वापस 2;

	हाल ETHTOOL_ID_ON:
		e1000_led_on(hw);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
		e1000_led_off(hw);
		अवरोध;

	हाल ETHTOOL_ID_INACTIVE:
		e1000_cleanup_led(hw);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->hw.mac_type < e1000_82545)
		वापस -EOPNOTSUPP;

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
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (hw->mac_type < e1000_82545)
		वापस -EOPNOTSUPP;

	अगर ((ec->rx_coalesce_usecs > E1000_MAX_ITR_USECS) ||
	    ((ec->rx_coalesce_usecs > 4) &&
	     (ec->rx_coalesce_usecs < E1000_MIN_ITR_USECS)) ||
	    (ec->rx_coalesce_usecs == 2))
		वापस -EINVAL;

	अगर (ec->rx_coalesce_usecs == 4) अणु
		adapter->itr = adapter->itr_setting = 4;
	पूर्ण अन्यथा अगर (ec->rx_coalesce_usecs <= 3) अणु
		adapter->itr = 20000;
		adapter->itr_setting = ec->rx_coalesce_usecs;
	पूर्ण अन्यथा अणु
		adapter->itr = (1000000 / ec->rx_coalesce_usecs);
		adapter->itr_setting = adapter->itr & ~3;
	पूर्ण

	अगर (adapter->itr_setting != 0)
		ew32(ITR, 1000000000 / (adapter->itr * 256));
	अन्यथा
		ew32(ITR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		e1000_reinit_locked(adapter);
	वापस 0;
पूर्ण

अटल व्योम e1000_get_ethtool_stats(काष्ठा net_device *netdev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;
	स्थिर काष्ठा e1000_stats *stat = e1000_gstrings_stats;

	e1000_update_stats(adapter);
	क्रम (i = 0; i < E1000_GLOBAL_STATS_LEN; i++, stat++) अणु
		अक्षर *p;

		चयन (stat->type) अणु
		हाल NETDEV_STATS:
			p = (अक्षर *)netdev + stat->stat_offset;
			अवरोध;
		हाल E1000_STATS:
			p = (अक्षर *)adapter + stat->stat_offset;
			अवरोध;
		शेष:
			netdev_WARN_ONCE(netdev, "Invalid E1000 stat type: %u index %d\n",
					 stat->type, i);
			जारी;
		पूर्ण

		अगर (stat->माप_stat == माप(u64))
			data[i] = *(u64 *)p;
		अन्यथा
			data[i] = *(u32 *)p;
	पूर्ण
/* BUG_ON(i != E1000_STATS_LEN); */
पूर्ण

अटल व्योम e1000_get_strings(काष्ठा net_device *netdev, u32 stringset,
			      u8 *data)
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
		/* BUG_ON(p - data != E1000_STATS_LEN * ETH_GSTRING_LEN); */
		अवरोध;
	पूर्ण
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
	.get_link		= e1000_get_link,
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
	.get_sset_count		= e1000_get_sset_count,
	.get_coalesce		= e1000_get_coalesce,
	.set_coalesce		= e1000_set_coalesce,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_link_ksettings	= e1000_get_link_ksettings,
	.set_link_ksettings	= e1000_set_link_ksettings,
पूर्ण;

व्योम e1000_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &e1000_ethtool_ops;
पूर्ण
