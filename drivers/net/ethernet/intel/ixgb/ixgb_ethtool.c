<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2008 Intel Corporation. */

/* ethtool support क्रम ixgb */

#समावेश "ixgb.h"

#समावेश <linux/uaccess.h>

#घोषणा IXGB_ALL_RAR_ENTRIES 16

क्रमागत अणुNETDEV_STATS, IXGB_STATSपूर्ण;

काष्ठा ixgb_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक type;
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा IXGB_STAT(m)		IXGB_STATS, \
				माप_field(काष्ठा ixgb_adapter, m), \
				दुरत्व(काष्ठा ixgb_adapter, m)
#घोषणा IXGB_NETDEV_STAT(m)	NETDEV_STATS, \
				माप_field(काष्ठा net_device, m), \
				दुरत्व(काष्ठा net_device, m)

अटल काष्ठा ixgb_stats ixgb_gstrings_stats[] = अणु
	अणु"rx_packets", IXGB_NETDEV_STAT(stats.rx_packets)पूर्ण,
	अणु"tx_packets", IXGB_NETDEV_STAT(stats.tx_packets)पूर्ण,
	अणु"rx_bytes", IXGB_NETDEV_STAT(stats.rx_bytes)पूर्ण,
	अणु"tx_bytes", IXGB_NETDEV_STAT(stats.tx_bytes)पूर्ण,
	अणु"rx_errors", IXGB_NETDEV_STAT(stats.rx_errors)पूर्ण,
	अणु"tx_errors", IXGB_NETDEV_STAT(stats.tx_errors)पूर्ण,
	अणु"rx_dropped", IXGB_NETDEV_STAT(stats.rx_dropped)पूर्ण,
	अणु"tx_dropped", IXGB_NETDEV_STAT(stats.tx_dropped)पूर्ण,
	अणु"multicast", IXGB_NETDEV_STAT(stats.multicast)पूर्ण,
	अणु"collisions", IXGB_NETDEV_STAT(stats.collisions)पूर्ण,

/*	अणु "rx_length_errors", IXGB_NETDEV_STAT(stats.rx_length_errors) पूर्ण,	*/
	अणु"rx_over_errors", IXGB_NETDEV_STAT(stats.rx_over_errors)पूर्ण,
	अणु"rx_crc_errors", IXGB_NETDEV_STAT(stats.rx_crc_errors)पूर्ण,
	अणु"rx_frame_errors", IXGB_NETDEV_STAT(stats.rx_frame_errors)पूर्ण,
	अणु"rx_no_buffer_count", IXGB_STAT(stats.rnbc)पूर्ण,
	अणु"rx_fifo_errors", IXGB_NETDEV_STAT(stats.rx_fअगरo_errors)पूर्ण,
	अणु"rx_missed_errors", IXGB_NETDEV_STAT(stats.rx_missed_errors)पूर्ण,
	अणु"tx_aborted_errors", IXGB_NETDEV_STAT(stats.tx_पातed_errors)पूर्ण,
	अणु"tx_carrier_errors", IXGB_NETDEV_STAT(stats.tx_carrier_errors)पूर्ण,
	अणु"tx_fifo_errors", IXGB_NETDEV_STAT(stats.tx_fअगरo_errors)पूर्ण,
	अणु"tx_heartbeat_errors", IXGB_NETDEV_STAT(stats.tx_heartbeat_errors)पूर्ण,
	अणु"tx_window_errors", IXGB_NETDEV_STAT(stats.tx_winकरोw_errors)पूर्ण,
	अणु"tx_deferred_ok", IXGB_STAT(stats.dc)पूर्ण,
	अणु"tx_timeout_count", IXGB_STAT(tx_समयout_count) पूर्ण,
	अणु"tx_restart_queue", IXGB_STAT(restart_queue) पूर्ण,
	अणु"rx_long_length_errors", IXGB_STAT(stats.roc)पूर्ण,
	अणु"rx_short_length_errors", IXGB_STAT(stats.ruc)पूर्ण,
	अणु"tx_tcp_seg_good", IXGB_STAT(stats.tsctc)पूर्ण,
	अणु"tx_tcp_seg_failed", IXGB_STAT(stats.tsctfc)पूर्ण,
	अणु"rx_flow_control_xon", IXGB_STAT(stats.xonrxc)पूर्ण,
	अणु"rx_flow_control_xoff", IXGB_STAT(stats.xoffrxc)पूर्ण,
	अणु"tx_flow_control_xon", IXGB_STAT(stats.xontxc)पूर्ण,
	अणु"tx_flow_control_xoff", IXGB_STAT(stats.xofftxc)पूर्ण,
	अणु"rx_csum_offload_good", IXGB_STAT(hw_csum_rx_good)पूर्ण,
	अणु"rx_csum_offload_errors", IXGB_STAT(hw_csum_rx_error)पूर्ण,
	अणु"tx_csum_offload_good", IXGB_STAT(hw_csum_tx_good)पूर्ण,
	अणु"tx_csum_offload_errors", IXGB_STAT(hw_csum_tx_error)पूर्ण
पूर्ण;

#घोषणा IXGB_STATS_LEN	ARRAY_SIZE(ixgb_gstrings_stats)

अटल पूर्णांक
ixgb_get_link_ksettings(काष्ठा net_device *netdev,
			काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);

	ethtool_link_ksettings_zero_link_mode(cmd, advertising);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, 10000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);

	cmd->base.port = PORT_FIBRE;

	अगर (netअगर_carrier_ok(adapter->netdev)) अणु
		cmd->base.speed = SPEED_10000;
		cmd->base.duplex = DUPLEX_FULL;
	पूर्ण अन्यथा अणु
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण

	cmd->base.स्वतःneg = AUTONEG_DISABLE;
	वापस 0;
पूर्ण

व्योम ixgb_set_speed_duplex(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	/* be optimistic about our link, since we were up beक्रमe */
	adapter->link_speed = 10000;
	adapter->link_duplex = FULL_DUPLEX;
	netअगर_carrier_on(netdev);
	netअगर_wake_queue(netdev);
पूर्ण

अटल पूर्णांक
ixgb_set_link_ksettings(काष्ठा net_device *netdev,
			स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	u32 speed = cmd->base.speed;

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE ||
	    (speed + cmd->base.duplex != SPEED_10000 + DUPLEX_FULL))
		वापस -EINVAL;

	अगर (netअगर_running(adapter->netdev)) अणु
		ixgb_करोwn(adapter, true);
		ixgb_reset(adapter);
		ixgb_up(adapter);
		ixgb_set_speed_duplex(netdev);
	पूर्ण अन्यथा
		ixgb_reset(adapter);

	वापस 0;
पूर्ण

अटल व्योम
ixgb_get_छोड़ोparam(काष्ठा net_device *netdev,
			 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_hw *hw = &adapter->hw;

	छोड़ो->स्वतःneg = AUTONEG_DISABLE;

	अगर (hw->fc.type == ixgb_fc_rx_छोड़ो)
		छोड़ो->rx_छोड़ो = 1;
	अन्यथा अगर (hw->fc.type == ixgb_fc_tx_छोड़ो)
		छोड़ो->tx_छोड़ो = 1;
	अन्यथा अगर (hw->fc.type == ixgb_fc_full) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक
ixgb_set_छोड़ोparam(काष्ठा net_device *netdev,
			 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_hw *hw = &adapter->hw;

	अगर (छोड़ो->स्वतःneg == AUTONEG_ENABLE)
		वापस -EINVAL;

	अगर (छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		hw->fc.type = ixgb_fc_full;
	अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		hw->fc.type = ixgb_fc_rx_छोड़ो;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		hw->fc.type = ixgb_fc_tx_छोड़ो;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		hw->fc.type = ixgb_fc_none;

	अगर (netअगर_running(adapter->netdev)) अणु
		ixgb_करोwn(adapter, true);
		ixgb_up(adapter);
		ixgb_set_speed_duplex(netdev);
	पूर्ण अन्यथा
		ixgb_reset(adapter);

	वापस 0;
पूर्ण

अटल u32
ixgb_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	वापस adapter->msg_enable;
पूर्ण

अटल व्योम
ixgb_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	adapter->msg_enable = data;
पूर्ण
#घोषणा IXGB_GET_STAT(_A_, _R_) _A_->stats._R_

अटल पूर्णांक
ixgb_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा IXGB_REG_DUMP_LEN  136*माप(u32)
	वापस IXGB_REG_DUMP_LEN;
पूर्ण

अटल व्योम
ixgb_get_regs(काष्ठा net_device *netdev,
		   काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_hw *hw = &adapter->hw;
	u32 *reg = p;
	u32 *reg_start = reg;
	u8 i;

	/* the 1 (one) below indicates an attempt at versioning, अगर the
	 * पूर्णांकerface in ethtool or the driver changes, this 1 should be
	 * incremented */
	regs->version = (1<<24) | hw->revision_id << 16 | hw->device_id;

	/* General Registers */
	*reg++ = IXGB_READ_REG(hw, CTRL0);	/*   0 */
	*reg++ = IXGB_READ_REG(hw, CTRL1);	/*   1 */
	*reg++ = IXGB_READ_REG(hw, STATUS);	/*   2 */
	*reg++ = IXGB_READ_REG(hw, EECD);	/*   3 */
	*reg++ = IXGB_READ_REG(hw, MFS);	/*   4 */

	/* Interrupt */
	*reg++ = IXGB_READ_REG(hw, ICR);	/*   5 */
	*reg++ = IXGB_READ_REG(hw, ICS);	/*   6 */
	*reg++ = IXGB_READ_REG(hw, IMS);	/*   7 */
	*reg++ = IXGB_READ_REG(hw, IMC);	/*   8 */

	/* Receive */
	*reg++ = IXGB_READ_REG(hw, RCTL);	/*   9 */
	*reg++ = IXGB_READ_REG(hw, FCRTL);	/*  10 */
	*reg++ = IXGB_READ_REG(hw, FCRTH);	/*  11 */
	*reg++ = IXGB_READ_REG(hw, RDBAL);	/*  12 */
	*reg++ = IXGB_READ_REG(hw, RDBAH);	/*  13 */
	*reg++ = IXGB_READ_REG(hw, RDLEN);	/*  14 */
	*reg++ = IXGB_READ_REG(hw, RDH);	/*  15 */
	*reg++ = IXGB_READ_REG(hw, RDT);	/*  16 */
	*reg++ = IXGB_READ_REG(hw, RDTR);	/*  17 */
	*reg++ = IXGB_READ_REG(hw, RXDCTL);	/*  18 */
	*reg++ = IXGB_READ_REG(hw, RAIDC);	/*  19 */
	*reg++ = IXGB_READ_REG(hw, RXCSUM);	/*  20 */

	/* there are 16 RAR entries in hardware, we only use 3 */
	क्रम (i = 0; i < IXGB_ALL_RAR_ENTRIES; i++) अणु
		*reg++ = IXGB_READ_REG_ARRAY(hw, RAL, (i << 1)); /*21,...,51 */
		*reg++ = IXGB_READ_REG_ARRAY(hw, RAH, (i << 1)); /*22,...,52 */
	पूर्ण

	/* Transmit */
	*reg++ = IXGB_READ_REG(hw, TCTL);	/*  53 */
	*reg++ = IXGB_READ_REG(hw, TDBAL);	/*  54 */
	*reg++ = IXGB_READ_REG(hw, TDBAH);	/*  55 */
	*reg++ = IXGB_READ_REG(hw, TDLEN);	/*  56 */
	*reg++ = IXGB_READ_REG(hw, TDH);	/*  57 */
	*reg++ = IXGB_READ_REG(hw, TDT);	/*  58 */
	*reg++ = IXGB_READ_REG(hw, TIDV);	/*  59 */
	*reg++ = IXGB_READ_REG(hw, TXDCTL);	/*  60 */
	*reg++ = IXGB_READ_REG(hw, TSPMT);	/*  61 */
	*reg++ = IXGB_READ_REG(hw, PAP);	/*  62 */

	/* Physical */
	*reg++ = IXGB_READ_REG(hw, PCSC1);	/*  63 */
	*reg++ = IXGB_READ_REG(hw, PCSC2);	/*  64 */
	*reg++ = IXGB_READ_REG(hw, PCSS1);	/*  65 */
	*reg++ = IXGB_READ_REG(hw, PCSS2);	/*  66 */
	*reg++ = IXGB_READ_REG(hw, XPCSS);	/*  67 */
	*reg++ = IXGB_READ_REG(hw, UCCR);	/*  68 */
	*reg++ = IXGB_READ_REG(hw, XPCSTC);	/*  69 */
	*reg++ = IXGB_READ_REG(hw, MACA);	/*  70 */
	*reg++ = IXGB_READ_REG(hw, APAE);	/*  71 */
	*reg++ = IXGB_READ_REG(hw, ARD);	/*  72 */
	*reg++ = IXGB_READ_REG(hw, AIS);	/*  73 */
	*reg++ = IXGB_READ_REG(hw, MSCA);	/*  74 */
	*reg++ = IXGB_READ_REG(hw, MSRWD);	/*  75 */

	/* Statistics */
	*reg++ = IXGB_GET_STAT(adapter, tprl);	/*  76 */
	*reg++ = IXGB_GET_STAT(adapter, tprh);	/*  77 */
	*reg++ = IXGB_GET_STAT(adapter, gprcl);	/*  78 */
	*reg++ = IXGB_GET_STAT(adapter, gprch);	/*  79 */
	*reg++ = IXGB_GET_STAT(adapter, bprcl);	/*  80 */
	*reg++ = IXGB_GET_STAT(adapter, bprch);	/*  81 */
	*reg++ = IXGB_GET_STAT(adapter, mprcl);	/*  82 */
	*reg++ = IXGB_GET_STAT(adapter, mprch);	/*  83 */
	*reg++ = IXGB_GET_STAT(adapter, uprcl);	/*  84 */
	*reg++ = IXGB_GET_STAT(adapter, uprch);	/*  85 */
	*reg++ = IXGB_GET_STAT(adapter, vprcl);	/*  86 */
	*reg++ = IXGB_GET_STAT(adapter, vprch);	/*  87 */
	*reg++ = IXGB_GET_STAT(adapter, jprcl);	/*  88 */
	*reg++ = IXGB_GET_STAT(adapter, jprch);	/*  89 */
	*reg++ = IXGB_GET_STAT(adapter, gorcl);	/*  90 */
	*reg++ = IXGB_GET_STAT(adapter, gorch);	/*  91 */
	*reg++ = IXGB_GET_STAT(adapter, torl);	/*  92 */
	*reg++ = IXGB_GET_STAT(adapter, torh);	/*  93 */
	*reg++ = IXGB_GET_STAT(adapter, rnbc);	/*  94 */
	*reg++ = IXGB_GET_STAT(adapter, ruc);	/*  95 */
	*reg++ = IXGB_GET_STAT(adapter, roc);	/*  96 */
	*reg++ = IXGB_GET_STAT(adapter, rlec);	/*  97 */
	*reg++ = IXGB_GET_STAT(adapter, crcerrs);	/*  98 */
	*reg++ = IXGB_GET_STAT(adapter, icbc);	/*  99 */
	*reg++ = IXGB_GET_STAT(adapter, ecbc);	/* 100 */
	*reg++ = IXGB_GET_STAT(adapter, mpc);	/* 101 */
	*reg++ = IXGB_GET_STAT(adapter, tptl);	/* 102 */
	*reg++ = IXGB_GET_STAT(adapter, tpth);	/* 103 */
	*reg++ = IXGB_GET_STAT(adapter, gptcl);	/* 104 */
	*reg++ = IXGB_GET_STAT(adapter, gptch);	/* 105 */
	*reg++ = IXGB_GET_STAT(adapter, bptcl);	/* 106 */
	*reg++ = IXGB_GET_STAT(adapter, bptch);	/* 107 */
	*reg++ = IXGB_GET_STAT(adapter, mptcl);	/* 108 */
	*reg++ = IXGB_GET_STAT(adapter, mptch);	/* 109 */
	*reg++ = IXGB_GET_STAT(adapter, uptcl);	/* 110 */
	*reg++ = IXGB_GET_STAT(adapter, uptch);	/* 111 */
	*reg++ = IXGB_GET_STAT(adapter, vptcl);	/* 112 */
	*reg++ = IXGB_GET_STAT(adapter, vptch);	/* 113 */
	*reg++ = IXGB_GET_STAT(adapter, jptcl);	/* 114 */
	*reg++ = IXGB_GET_STAT(adapter, jptch);	/* 115 */
	*reg++ = IXGB_GET_STAT(adapter, gotcl);	/* 116 */
	*reg++ = IXGB_GET_STAT(adapter, gotch);	/* 117 */
	*reg++ = IXGB_GET_STAT(adapter, totl);	/* 118 */
	*reg++ = IXGB_GET_STAT(adapter, toth);	/* 119 */
	*reg++ = IXGB_GET_STAT(adapter, dc);	/* 120 */
	*reg++ = IXGB_GET_STAT(adapter, plt64c);	/* 121 */
	*reg++ = IXGB_GET_STAT(adapter, tsctc);	/* 122 */
	*reg++ = IXGB_GET_STAT(adapter, tsctfc);	/* 123 */
	*reg++ = IXGB_GET_STAT(adapter, ibic);	/* 124 */
	*reg++ = IXGB_GET_STAT(adapter, rfc);	/* 125 */
	*reg++ = IXGB_GET_STAT(adapter, lfc);	/* 126 */
	*reg++ = IXGB_GET_STAT(adapter, pfrc);	/* 127 */
	*reg++ = IXGB_GET_STAT(adapter, pftc);	/* 128 */
	*reg++ = IXGB_GET_STAT(adapter, mcfrc);	/* 129 */
	*reg++ = IXGB_GET_STAT(adapter, mcftc);	/* 130 */
	*reg++ = IXGB_GET_STAT(adapter, xonrxc);	/* 131 */
	*reg++ = IXGB_GET_STAT(adapter, xontxc);	/* 132 */
	*reg++ = IXGB_GET_STAT(adapter, xoffrxc);	/* 133 */
	*reg++ = IXGB_GET_STAT(adapter, xofftxc);	/* 134 */
	*reg++ = IXGB_GET_STAT(adapter, rjc);	/* 135 */

	regs->len = (reg - reg_start) * माप(u32);
पूर्ण

अटल पूर्णांक
ixgb_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	/* वापस size in bytes */
	वापस IXGB_EEPROM_SIZE << 1;
पूर्ण

अटल पूर्णांक
ixgb_get_eeprom(काष्ठा net_device *netdev,
		  काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_hw *hw = &adapter->hw;
	__le16 *eeprom_buff;
	पूर्णांक i, max_len, first_word, last_word;
	पूर्णांक ret_val = 0;

	अगर (eeprom->len == 0) अणु
		ret_val = -EINVAL;
		जाओ geeprom_error;
	पूर्ण

	eeprom->magic = hw->venकरोr_id | (hw->device_id << 16);

	max_len = ixgb_get_eeprom_len(netdev);

	अगर (eeprom->offset > eeprom->offset + eeprom->len) अणु
		ret_val = -EINVAL;
		जाओ geeprom_error;
	पूर्ण

	अगर ((eeprom->offset + eeprom->len) > max_len)
		eeprom->len = (max_len - eeprom->offset);

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;

	eeprom_buff = kदो_स्मृति_array(last_word - first_word + 1,
				    माप(__le16),
				    GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	/* note the eeprom was good because the driver loaded */
	क्रम (i = 0; i <= (last_word - first_word); i++)
		eeprom_buff[i] = ixgb_get_eeprom_word(hw, (first_word + i));

	स_नकल(bytes, (u8 *)eeprom_buff + (eeprom->offset & 1), eeprom->len);
	kमुक्त(eeprom_buff);

geeprom_error:
	वापस ret_val;
पूर्ण

अटल पूर्णांक
ixgb_set_eeprom(काष्ठा net_device *netdev,
		  काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_hw *hw = &adapter->hw;
	u16 *eeprom_buff;
	व्योम *ptr;
	पूर्णांक max_len, first_word, last_word;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EINVAL;

	अगर (eeprom->magic != (hw->venकरोr_id | (hw->device_id << 16)))
		वापस -EFAULT;

	max_len = ixgb_get_eeprom_len(netdev);

	अगर (eeprom->offset > eeprom->offset + eeprom->len)
		वापस -EINVAL;

	अगर ((eeprom->offset + eeprom->len) > max_len)
		eeprom->len = (max_len - eeprom->offset);

	first_word = eeprom->offset >> 1;
	last_word = (eeprom->offset + eeprom->len - 1) >> 1;
	eeprom_buff = kदो_स्मृति(max_len, GFP_KERNEL);
	अगर (!eeprom_buff)
		वापस -ENOMEM;

	ptr = (व्योम *)eeprom_buff;

	अगर (eeprom->offset & 1) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of first changed EEPROM word */
		/* only the second byte of the word is being modअगरied */
		eeprom_buff[0] = ixgb_पढ़ो_eeprom(hw, first_word);
		ptr++;
	पूर्ण
	अगर ((eeprom->offset + eeprom->len) & 1) अणु
		/* need पढ़ो/modअगरy/ग_लिखो of last changed EEPROM word */
		/* only the first byte of the word is being modअगरied */
		eeprom_buff[last_word - first_word]
			= ixgb_पढ़ो_eeprom(hw, last_word);
	पूर्ण

	स_नकल(ptr, bytes, eeprom->len);
	क्रम (i = 0; i <= (last_word - first_word); i++)
		ixgb_ग_लिखो_eeprom(hw, first_word + i, eeprom_buff[i]);

	/* Update the checksum over the first part of the EEPROM अगर needed */
	अगर (first_word <= EEPROM_CHECKSUM_REG)
		ixgb_update_eeprom_checksum(hw);

	kमुक्त(eeprom_buff);
	वापस 0;
पूर्ण

अटल व्योम
ixgb_get_drvinfo(काष्ठा net_device *netdev,
		   काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  ixgb_driver_name,
		माप(drvinfo->driver));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));
पूर्ण

अटल व्योम
ixgb_get_ringparam(काष्ठा net_device *netdev,
		काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_desc_ring *txdr = &adapter->tx_ring;
	काष्ठा ixgb_desc_ring *rxdr = &adapter->rx_ring;

	ring->rx_max_pending = MAX_RXD;
	ring->tx_max_pending = MAX_TXD;
	ring->rx_pending = rxdr->count;
	ring->tx_pending = txdr->count;
पूर्ण

अटल पूर्णांक
ixgb_set_ringparam(काष्ठा net_device *netdev,
		काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgb_desc_ring *txdr = &adapter->tx_ring;
	काष्ठा ixgb_desc_ring *rxdr = &adapter->rx_ring;
	काष्ठा ixgb_desc_ring tx_old, tx_new, rx_old, rx_new;
	पूर्णांक err;

	tx_old = adapter->tx_ring;
	rx_old = adapter->rx_ring;

	अगर ((ring->rx_mini_pending) || (ring->rx_jumbo_pending))
		वापस -EINVAL;

	अगर (netअगर_running(adapter->netdev))
		ixgb_करोwn(adapter, true);

	rxdr->count = max(ring->rx_pending,(u32)MIN_RXD);
	rxdr->count = min(rxdr->count,(u32)MAX_RXD);
	rxdr->count = ALIGN(rxdr->count, IXGB_REQ_RX_DESCRIPTOR_MULTIPLE);

	txdr->count = max(ring->tx_pending,(u32)MIN_TXD);
	txdr->count = min(txdr->count,(u32)MAX_TXD);
	txdr->count = ALIGN(txdr->count, IXGB_REQ_TX_DESCRIPTOR_MULTIPLE);

	अगर (netअगर_running(adapter->netdev)) अणु
		/* Try to get new resources beक्रमe deleting old */
		अगर ((err = ixgb_setup_rx_resources(adapter)))
			जाओ err_setup_rx;
		अगर ((err = ixgb_setup_tx_resources(adapter)))
			जाओ err_setup_tx;

		/* save the new, restore the old in order to मुक्त it,
		 * then restore the new back again */

		rx_new = adapter->rx_ring;
		tx_new = adapter->tx_ring;
		adapter->rx_ring = rx_old;
		adapter->tx_ring = tx_old;
		ixgb_मुक्त_rx_resources(adapter);
		ixgb_मुक्त_tx_resources(adapter);
		adapter->rx_ring = rx_new;
		adapter->tx_ring = tx_new;
		अगर ((err = ixgb_up(adapter)))
			वापस err;
		ixgb_set_speed_duplex(netdev);
	पूर्ण

	वापस 0;
err_setup_tx:
	ixgb_मुक्त_rx_resources(adapter);
err_setup_rx:
	adapter->rx_ring = rx_old;
	adapter->tx_ring = tx_old;
	ixgb_up(adapter);
	वापस err;
पूर्ण

अटल पूर्णांक
ixgb_set_phys_id(काष्ठा net_device *netdev, क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		वापस 2;

	हाल ETHTOOL_ID_ON:
		ixgb_led_on(&adapter->hw);
		अवरोध;

	हाल ETHTOOL_ID_OFF:
	हाल ETHTOOL_ID_INACTIVE:
		ixgb_led_off(&adapter->hw);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
ixgb_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस IXGB_STATS_LEN;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
ixgb_get_ethtool_stats(काष्ठा net_device *netdev,
		काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ixgb_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;
	अक्षर *p = शून्य;

	ixgb_update_stats(adapter);
	क्रम (i = 0; i < IXGB_STATS_LEN; i++) अणु
		चयन (ixgb_gstrings_stats[i].type) अणु
		हाल NETDEV_STATS:
			p = (अक्षर *) netdev +
					ixgb_gstrings_stats[i].stat_offset;
			अवरोध;
		हाल IXGB_STATS:
			p = (अक्षर *) adapter +
					ixgb_gstrings_stats[i].stat_offset;
			अवरोध;
		पूर्ण

		data[i] = (ixgb_gstrings_stats[i].माप_stat ==
			माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
पूर्ण

अटल व्योम
ixgb_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन(stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < IXGB_STATS_LEN; i++) अणु
			स_नकल(data + i * ETH_GSTRING_LEN,
			ixgb_gstrings_stats[i].stat_string,
			ETH_GSTRING_LEN);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ixgb_ethtool_ops = अणु
	.get_drvinfo = ixgb_get_drvinfo,
	.get_regs_len = ixgb_get_regs_len,
	.get_regs = ixgb_get_regs,
	.get_link = ethtool_op_get_link,
	.get_eeprom_len = ixgb_get_eeprom_len,
	.get_eeprom = ixgb_get_eeprom,
	.set_eeprom = ixgb_set_eeprom,
	.get_ringparam = ixgb_get_ringparam,
	.set_ringparam = ixgb_set_ringparam,
	.get_छोड़ोparam	= ixgb_get_छोड़ोparam,
	.set_छोड़ोparam	= ixgb_set_छोड़ोparam,
	.get_msglevel = ixgb_get_msglevel,
	.set_msglevel = ixgb_set_msglevel,
	.get_strings = ixgb_get_strings,
	.set_phys_id = ixgb_set_phys_id,
	.get_sset_count = ixgb_get_sset_count,
	.get_ethtool_stats = ixgb_get_ethtool_stats,
	.get_link_ksettings = ixgb_get_link_ksettings,
	.set_link_ksettings = ixgb_set_link_ksettings,
पूर्ण;

व्योम ixgb_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ixgb_ethtool_ops;
पूर्ण
