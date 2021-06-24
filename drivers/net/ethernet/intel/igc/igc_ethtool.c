<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

/* ethtool support क्रम igc */
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/mdपन.स>

#समावेश "igc.h"
#समावेश "igc_diag.h"

/* क्रमward declaration */
काष्ठा igc_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा IGC_STAT(_name, _stat) अणु \
	.stat_string = _name, \
	.माप_stat = माप_field(काष्ठा igc_adapter, _stat), \
	.stat_offset = दुरत्व(काष्ठा igc_adapter, _stat) \
पूर्ण

अटल स्थिर काष्ठा igc_stats igc_gstrings_stats[] = अणु
	IGC_STAT("rx_packets", stats.gprc),
	IGC_STAT("tx_packets", stats.gptc),
	IGC_STAT("rx_bytes", stats.gorc),
	IGC_STAT("tx_bytes", stats.gotc),
	IGC_STAT("rx_broadcast", stats.bprc),
	IGC_STAT("tx_broadcast", stats.bptc),
	IGC_STAT("rx_multicast", stats.mprc),
	IGC_STAT("tx_multicast", stats.mptc),
	IGC_STAT("multicast", stats.mprc),
	IGC_STAT("collisions", stats.colc),
	IGC_STAT("rx_crc_errors", stats.crcerrs),
	IGC_STAT("rx_no_buffer_count", stats.rnbc),
	IGC_STAT("rx_missed_errors", stats.mpc),
	IGC_STAT("tx_aborted_errors", stats.ecol),
	IGC_STAT("tx_carrier_errors", stats.tncrs),
	IGC_STAT("tx_window_errors", stats.latecol),
	IGC_STAT("tx_abort_late_coll", stats.latecol),
	IGC_STAT("tx_deferred_ok", stats.dc),
	IGC_STAT("tx_single_coll_ok", stats.scc),
	IGC_STAT("tx_multi_coll_ok", stats.mcc),
	IGC_STAT("tx_timeout_count", tx_समयout_count),
	IGC_STAT("rx_long_length_errors", stats.roc),
	IGC_STAT("rx_short_length_errors", stats.ruc),
	IGC_STAT("rx_align_errors", stats.algnerrc),
	IGC_STAT("tx_tcp_seg_good", stats.tsctc),
	IGC_STAT("tx_tcp_seg_failed", stats.tsctfc),
	IGC_STAT("rx_flow_control_xon", stats.xonrxc),
	IGC_STAT("rx_flow_control_xoff", stats.xoffrxc),
	IGC_STAT("tx_flow_control_xon", stats.xontxc),
	IGC_STAT("tx_flow_control_xoff", stats.xofftxc),
	IGC_STAT("rx_long_byte_count", stats.gorc),
	IGC_STAT("tx_dma_out_of_sync", stats.करोosync),
	IGC_STAT("tx_smbus", stats.mgptc),
	IGC_STAT("rx_smbus", stats.mgprc),
	IGC_STAT("dropped_smbus", stats.mgpdc),
	IGC_STAT("os2bmc_rx_by_bmc", stats.o2bgptc),
	IGC_STAT("os2bmc_tx_by_bmc", stats.b2ospc),
	IGC_STAT("os2bmc_tx_by_host", stats.o2bspc),
	IGC_STAT("os2bmc_rx_by_host", stats.b2ogprc),
	IGC_STAT("tx_hwtstamp_timeouts", tx_hwtstamp_समयouts),
	IGC_STAT("tx_hwtstamp_skipped", tx_hwtstamp_skipped),
	IGC_STAT("rx_hwtstamp_cleared", rx_hwtstamp_cleared),
	IGC_STAT("tx_lpi_counter", stats.tlpic),
	IGC_STAT("rx_lpi_counter", stats.rlpic),
पूर्ण;

#घोषणा IGC_NETDEV_STAT(_net_stat) अणु \
	.stat_string = __stringअगरy(_net_stat), \
	.माप_stat = माप_field(काष्ठा rtnl_link_stats64, _net_stat), \
	.stat_offset = दुरत्व(काष्ठा rtnl_link_stats64, _net_stat) \
पूर्ण

अटल स्थिर काष्ठा igc_stats igc_gstrings_net_stats[] = अणु
	IGC_NETDEV_STAT(rx_errors),
	IGC_NETDEV_STAT(tx_errors),
	IGC_NETDEV_STAT(tx_dropped),
	IGC_NETDEV_STAT(rx_length_errors),
	IGC_NETDEV_STAT(rx_over_errors),
	IGC_NETDEV_STAT(rx_frame_errors),
	IGC_NETDEV_STAT(rx_fअगरo_errors),
	IGC_NETDEV_STAT(tx_fअगरo_errors),
	IGC_NETDEV_STAT(tx_heartbeat_errors)
पूर्ण;

क्रमागत igc_diagnostics_results अणु
	TEST_REG = 0,
	TEST_EEP,
	TEST_IRQ,
	TEST_LOOP,
	TEST_LINK
पूर्ण;

अटल स्थिर अक्षर igc_gstrings_test[][ETH_GSTRING_LEN] = अणु
	[TEST_REG]  = "Register test  (offline)",
	[TEST_EEP]  = "Eeprom test    (offline)",
	[TEST_IRQ]  = "Interrupt test (offline)",
	[TEST_LOOP] = "Loopback test  (offline)",
	[TEST_LINK] = "Link test   (on/offline)"
पूर्ण;

#घोषणा IGC_TEST_LEN (माप(igc_gstrings_test) / ETH_GSTRING_LEN)

#घोषणा IGC_GLOBAL_STATS_LEN	\
	(माप(igc_gstrings_stats) / माप(काष्ठा igc_stats))
#घोषणा IGC_NETDEV_STATS_LEN	\
	(माप(igc_gstrings_net_stats) / माप(काष्ठा igc_stats))
#घोषणा IGC_RX_QUEUE_STATS_LEN \
	(माप(काष्ठा igc_rx_queue_stats) / माप(u64))
#घोषणा IGC_TX_QUEUE_STATS_LEN 3 /* packets, bytes, restart_queue */
#घोषणा IGC_QUEUE_STATS_LEN \
	((((काष्ठा igc_adapter *)netdev_priv(netdev))->num_rx_queues * \
	  IGC_RX_QUEUE_STATS_LEN) + \
	 (((काष्ठा igc_adapter *)netdev_priv(netdev))->num_tx_queues * \
	  IGC_TX_QUEUE_STATS_LEN))
#घोषणा IGC_STATS_LEN \
	(IGC_GLOBAL_STATS_LEN + IGC_NETDEV_STATS_LEN + IGC_QUEUE_STATS_LEN)

अटल स्थिर अक्षर igc_priv_flags_strings[][ETH_GSTRING_LEN] = अणु
#घोषणा IGC_PRIV_FLAGS_LEGACY_RX	BIT(0)
	"legacy-rx",
पूर्ण;

#घोषणा IGC_PRIV_FLAGS_STR_LEN ARRAY_SIZE(igc_priv_flags_strings)

अटल व्योम igc_ethtool_get_drvinfo(काष्ठा net_device *netdev,
				    काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	u16 nvm_version = 0;
	u16 gphy_version;

	strscpy(drvinfo->driver, igc_driver_name, माप(drvinfo->driver));

	/* NVM image version is reported as firmware version क्रम i225 device */
	hw->nvm.ops.पढ़ो(hw, IGC_NVM_DEV_STARTER, 1, &nvm_version);

	/* gPHY firmware version is reported as PHY FW version */
	gphy_version = igc_पढ़ो_phy_fw_version(hw);

	scnम_लिखो(adapter->fw_version,
		  माप(adapter->fw_version),
		  "%x:%x",
		  nvm_version,
		  gphy_version);

	strscpy(drvinfo->fw_version, adapter->fw_version,
		माप(drvinfo->fw_version));

	strscpy(drvinfo->bus_info, pci_name(adapter->pdev),
		माप(drvinfo->bus_info));

	drvinfo->n_priv_flags = IGC_PRIV_FLAGS_STR_LEN;
पूर्ण

अटल पूर्णांक igc_ethtool_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस IGC_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम igc_ethtool_get_regs(काष्ठा net_device *netdev,
				 काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u8 i;

	स_रखो(p, 0, IGC_REGS_LEN * माप(u32));

	regs->version = (2u << 24) | (hw->revision_id << 16) | hw->device_id;

	/* General Registers */
	regs_buff[0] = rd32(IGC_CTRL);
	regs_buff[1] = rd32(IGC_STATUS);
	regs_buff[2] = rd32(IGC_CTRL_EXT);
	regs_buff[3] = rd32(IGC_MDIC);
	regs_buff[4] = rd32(IGC_CONNSW);

	/* NVM Register */
	regs_buff[5] = rd32(IGC_EECD);

	/* Interrupt */
	/* Reading EICS क्रम EICR because they पढ़ो the
	 * same but EICS करोes not clear on पढ़ो
	 */
	regs_buff[6] = rd32(IGC_EICS);
	regs_buff[7] = rd32(IGC_EICS);
	regs_buff[8] = rd32(IGC_EIMS);
	regs_buff[9] = rd32(IGC_EIMC);
	regs_buff[10] = rd32(IGC_EIAC);
	regs_buff[11] = rd32(IGC_EIAM);
	/* Reading ICS क्रम ICR because they पढ़ो the
	 * same but ICS करोes not clear on पढ़ो
	 */
	regs_buff[12] = rd32(IGC_ICS);
	regs_buff[13] = rd32(IGC_ICS);
	regs_buff[14] = rd32(IGC_IMS);
	regs_buff[15] = rd32(IGC_IMC);
	regs_buff[16] = rd32(IGC_IAC);
	regs_buff[17] = rd32(IGC_IAM);

	/* Flow Control */
	regs_buff[18] = rd32(IGC_FCAL);
	regs_buff[19] = rd32(IGC_FCAH);
	regs_buff[20] = rd32(IGC_FCTTV);
	regs_buff[21] = rd32(IGC_FCRTL);
	regs_buff[22] = rd32(IGC_FCRTH);
	regs_buff[23] = rd32(IGC_FCRTV);

	/* Receive */
	regs_buff[24] = rd32(IGC_RCTL);
	regs_buff[25] = rd32(IGC_RXCSUM);
	regs_buff[26] = rd32(IGC_RLPML);
	regs_buff[27] = rd32(IGC_RFCTL);

	/* Transmit */
	regs_buff[28] = rd32(IGC_TCTL);
	regs_buff[29] = rd32(IGC_TIPG);

	/* Wake Up */

	/* MAC */

	/* Statistics */
	regs_buff[30] = adapter->stats.crcerrs;
	regs_buff[31] = adapter->stats.algnerrc;
	regs_buff[32] = adapter->stats.symerrs;
	regs_buff[33] = adapter->stats.rxerrc;
	regs_buff[34] = adapter->stats.mpc;
	regs_buff[35] = adapter->stats.scc;
	regs_buff[36] = adapter->stats.ecol;
	regs_buff[37] = adapter->stats.mcc;
	regs_buff[38] = adapter->stats.latecol;
	regs_buff[39] = adapter->stats.colc;
	regs_buff[40] = adapter->stats.dc;
	regs_buff[41] = adapter->stats.tncrs;
	regs_buff[42] = adapter->stats.sec;
	regs_buff[43] = adapter->stats.htdpmc;
	regs_buff[44] = adapter->stats.rlec;
	regs_buff[45] = adapter->stats.xonrxc;
	regs_buff[46] = adapter->stats.xontxc;
	regs_buff[47] = adapter->stats.xoffrxc;
	regs_buff[48] = adapter->stats.xofftxc;
	regs_buff[49] = adapter->stats.fcruc;
	regs_buff[50] = adapter->stats.prc64;
	regs_buff[51] = adapter->stats.prc127;
	regs_buff[52] = adapter->stats.prc255;
	regs_buff[53] = adapter->stats.prc511;
	regs_buff[54] = adapter->stats.prc1023;
	regs_buff[55] = adapter->stats.prc1522;
	regs_buff[56] = adapter->stats.gprc;
	regs_buff[57] = adapter->stats.bprc;
	regs_buff[58] = adapter->stats.mprc;
	regs_buff[59] = adapter->stats.gptc;
	regs_buff[60] = adapter->stats.gorc;
	regs_buff[61] = adapter->stats.gotc;
	regs_buff[62] = adapter->stats.rnbc;
	regs_buff[63] = adapter->stats.ruc;
	regs_buff[64] = adapter->stats.rfc;
	regs_buff[65] = adapter->stats.roc;
	regs_buff[66] = adapter->stats.rjc;
	regs_buff[67] = adapter->stats.mgprc;
	regs_buff[68] = adapter->stats.mgpdc;
	regs_buff[69] = adapter->stats.mgptc;
	regs_buff[70] = adapter->stats.tor;
	regs_buff[71] = adapter->stats.tot;
	regs_buff[72] = adapter->stats.tpr;
	regs_buff[73] = adapter->stats.tpt;
	regs_buff[74] = adapter->stats.ptc64;
	regs_buff[75] = adapter->stats.ptc127;
	regs_buff[76] = adapter->stats.ptc255;
	regs_buff[77] = adapter->stats.ptc511;
	regs_buff[78] = adapter->stats.ptc1023;
	regs_buff[79] = adapter->stats.ptc1522;
	regs_buff[80] = adapter->stats.mptc;
	regs_buff[81] = adapter->stats.bptc;
	regs_buff[82] = adapter->stats.tsctc;
	regs_buff[83] = adapter->stats.iac;
	regs_buff[84] = adapter->stats.rpthc;
	regs_buff[85] = adapter->stats.hgptc;
	regs_buff[86] = adapter->stats.hgorc;
	regs_buff[87] = adapter->stats.hgotc;
	regs_buff[88] = adapter->stats.lenerrs;
	regs_buff[89] = adapter->stats.scvpc;
	regs_buff[90] = adapter->stats.hrmpc;

	क्रम (i = 0; i < 4; i++)
		regs_buff[91 + i] = rd32(IGC_SRRCTL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[95 + i] = rd32(IGC_PSRTYPE(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[99 + i] = rd32(IGC_RDBAL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[103 + i] = rd32(IGC_RDBAH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[107 + i] = rd32(IGC_RDLEN(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[111 + i] = rd32(IGC_RDH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[115 + i] = rd32(IGC_RDT(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[119 + i] = rd32(IGC_RXDCTL(i));

	क्रम (i = 0; i < 10; i++)
		regs_buff[123 + i] = rd32(IGC_EITR(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[139 + i] = rd32(IGC_RAL(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[145 + i] = rd32(IGC_RAH(i));

	क्रम (i = 0; i < 4; i++)
		regs_buff[149 + i] = rd32(IGC_TDBAL(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[152 + i] = rd32(IGC_TDBAH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[156 + i] = rd32(IGC_TDLEN(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[160 + i] = rd32(IGC_TDH(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[164 + i] = rd32(IGC_TDT(i));
	क्रम (i = 0; i < 4; i++)
		regs_buff[168 + i] = rd32(IGC_TXDCTL(i));

	/* XXX: Due to a bug few lines above, RAL and RAH रेजिस्टरs are
	 * overwritten. To preserve the ABI, we ग_लिखो these रेजिस्टरs again in
	 * regs_buff.
	 */
	क्रम (i = 0; i < 16; i++)
		regs_buff[172 + i] = rd32(IGC_RAL(i));
	क्रम (i = 0; i < 16; i++)
		regs_buff[188 + i] = rd32(IGC_RAH(i));

	regs_buff[204] = rd32(IGC_VLANPQF);

	क्रम (i = 0; i < 8; i++)
		regs_buff[205 + i] = rd32(IGC_ETQF(i));

	regs_buff[213] = adapter->stats.tlpic;
	regs_buff[214] = adapter->stats.rlpic;
पूर्ण

अटल व्योम igc_ethtool_get_wol(काष्ठा net_device *netdev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	wol->wolopts = 0;

	अगर (!(adapter->flags & IGC_FLAG_WOL_SUPPORTED))
		वापस;

	wol->supported = WAKE_UCAST | WAKE_MCAST |
			 WAKE_BCAST | WAKE_MAGIC |
			 WAKE_PHY;

	/* apply any specअगरic unsupported masks here */
	चयन (adapter->hw.device_id) अणु
	शेष:
		अवरोध;
	पूर्ण

	अगर (adapter->wol & IGC_WUFC_EX)
		wol->wolopts |= WAKE_UCAST;
	अगर (adapter->wol & IGC_WUFC_MC)
		wol->wolopts |= WAKE_MCAST;
	अगर (adapter->wol & IGC_WUFC_BC)
		wol->wolopts |= WAKE_BCAST;
	अगर (adapter->wol & IGC_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
	अगर (adapter->wol & IGC_WUFC_LNKC)
		wol->wolopts |= WAKE_PHY;
पूर्ण

अटल पूर्णांक igc_ethtool_set_wol(काष्ठा net_device *netdev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	अगर (wol->wolopts & (WAKE_ARP | WAKE_MAGICSECURE | WAKE_FILTER))
		वापस -EOPNOTSUPP;

	अगर (!(adapter->flags & IGC_FLAG_WOL_SUPPORTED))
		वापस wol->wolopts ? -EOPNOTSUPP : 0;

	/* these settings will always override what we currently have */
	adapter->wol = 0;

	अगर (wol->wolopts & WAKE_UCAST)
		adapter->wol |= IGC_WUFC_EX;
	अगर (wol->wolopts & WAKE_MCAST)
		adapter->wol |= IGC_WUFC_MC;
	अगर (wol->wolopts & WAKE_BCAST)
		adapter->wol |= IGC_WUFC_BC;
	अगर (wol->wolopts & WAKE_MAGIC)
		adapter->wol |= IGC_WUFC_MAG;
	अगर (wol->wolopts & WAKE_PHY)
		adapter->wol |= IGC_WUFC_LNKC;
	device_set_wakeup_enable(&adapter->pdev->dev, adapter->wol);

	वापस 0;
पूर्ण

अटल u32 igc_ethtool_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	वापस adapter->msg_enable;
पूर्ण

अटल व्योम igc_ethtool_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	adapter->msg_enable = data;
पूर्ण

अटल पूर्णांक igc_ethtool_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	अगर (netअगर_running(netdev))
		igc_reinit_locked(adapter);
	वापस 0;
पूर्ण

अटल u32 igc_ethtool_get_link(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_mac_info *mac = &adapter->hw.mac;

	/* If the link is not reported up to netdev, पूर्णांकerrupts are disabled,
	 * and so the physical link state may have changed since we last
	 * looked. Set get_link_status to make sure that the true link
	 * state is पूर्णांकerrogated, rather than pulling a cached and possibly
	 * stale link state from the driver.
	 */
	अगर (!netअगर_carrier_ok(netdev))
		mac->get_link_status = 1;

	वापस igc_has_link(adapter);
पूर्ण

अटल पूर्णांक igc_ethtool_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	वापस adapter->hw.nvm.word_size * 2;
पूर्ण

अटल पूर्णांक igc_ethtool_get_eeprom(काष्ठा net_device *netdev,
				  काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक first_word, last_word;
	u16 *eeprom_buff;
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

	अगर (hw->nvm.type == igc_nvm_eeprom_spi) अणु
		ret_val = hw->nvm.ops.पढ़ो(hw, first_word,
					   last_word - first_word + 1,
					   eeprom_buff);
	पूर्ण अन्यथा अणु
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

अटल पूर्णांक igc_ethtool_set_eeprom(काष्ठा net_device *netdev,
				  काष्ठा ethtool_eeprom *eeprom, u8 *bytes)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक max_len, first_word, last_word, ret_val = 0;
	u16 *eeprom_buff;
	व्योम *ptr;
	u16 i;

	अगर (eeprom->len == 0)
		वापस -EOPNOTSUPP;

	अगर (hw->mac.type >= igc_i225 &&
	    !igc_get_flash_presence_i225(hw)) अणु
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
	अगर (((eeprom->offset + eeprom->len) & 1) && ret_val == 0) अणु
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

	kमुक्त(eeprom_buff);
	वापस ret_val;
पूर्ण

अटल व्योम igc_ethtool_get_ringparam(काष्ठा net_device *netdev,
				      काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	ring->rx_max_pending = IGC_MAX_RXD;
	ring->tx_max_pending = IGC_MAX_TXD;
	ring->rx_pending = adapter->rx_ring_count;
	ring->tx_pending = adapter->tx_ring_count;
पूर्ण

अटल पूर्णांक igc_ethtool_set_ringparam(काष्ठा net_device *netdev,
				     काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_ring *temp_ring;
	u16 new_rx_count, new_tx_count;
	पूर्णांक i, err = 0;

	अगर (ring->rx_mini_pending || ring->rx_jumbo_pending)
		वापस -EINVAL;

	new_rx_count = min_t(u32, ring->rx_pending, IGC_MAX_RXD);
	new_rx_count = max_t(u16, new_rx_count, IGC_MIN_RXD);
	new_rx_count = ALIGN(new_rx_count, REQ_RX_DESCRIPTOR_MULTIPLE);

	new_tx_count = min_t(u32, ring->tx_pending, IGC_MAX_TXD);
	new_tx_count = max_t(u16, new_tx_count, IGC_MIN_TXD);
	new_tx_count = ALIGN(new_tx_count, REQ_TX_DESCRIPTOR_MULTIPLE);

	अगर (new_tx_count == adapter->tx_ring_count &&
	    new_rx_count == adapter->rx_ring_count) अणु
		/* nothing to करो */
		वापस 0;
	पूर्ण

	जबतक (test_and_set_bit(__IGC_RESETTING, &adapter->state))
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
		temp_ring = vदो_स्मृति(array_size(माप(काष्ठा igc_ring),
					       adapter->num_tx_queues));
	अन्यथा
		temp_ring = vदो_स्मृति(array_size(माप(काष्ठा igc_ring),
					       adapter->num_rx_queues));

	अगर (!temp_ring) अणु
		err = -ENOMEM;
		जाओ clear_reset;
	पूर्ण

	igc_करोwn(adapter);

	/* We can't just मुक्त everything and then setup again,
	 * because the ISRs in MSI-X mode get passed poपूर्णांकers
	 * to the Tx and Rx ring काष्ठाs.
	 */
	अगर (new_tx_count != adapter->tx_ring_count) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			स_नकल(&temp_ring[i], adapter->tx_ring[i],
			       माप(काष्ठा igc_ring));

			temp_ring[i].count = new_tx_count;
			err = igc_setup_tx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					igc_मुक्त_tx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			igc_मुक्त_tx_resources(adapter->tx_ring[i]);

			स_नकल(adapter->tx_ring[i], &temp_ring[i],
			       माप(काष्ठा igc_ring));
		पूर्ण

		adapter->tx_ring_count = new_tx_count;
	पूर्ण

	अगर (new_rx_count != adapter->rx_ring_count) अणु
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			स_नकल(&temp_ring[i], adapter->rx_ring[i],
			       माप(काष्ठा igc_ring));

			temp_ring[i].count = new_rx_count;
			err = igc_setup_rx_resources(&temp_ring[i]);
			अगर (err) अणु
				जबतक (i) अणु
					i--;
					igc_मुक्त_rx_resources(&temp_ring[i]);
				पूर्ण
				जाओ err_setup;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			igc_मुक्त_rx_resources(adapter->rx_ring[i]);

			स_नकल(adapter->rx_ring[i], &temp_ring[i],
			       माप(काष्ठा igc_ring));
		पूर्ण

		adapter->rx_ring_count = new_rx_count;
	पूर्ण
err_setup:
	igc_up(adapter);
	vमुक्त(temp_ring);
clear_reset:
	clear_bit(__IGC_RESETTING, &adapter->state);
	वापस err;
पूर्ण

अटल व्योम igc_ethtool_get_छोड़ोparam(काष्ठा net_device *netdev,
				       काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;

	छोड़ो->स्वतःneg =
		(adapter->fc_स्वतःneg ? AUTONEG_ENABLE : AUTONEG_DISABLE);

	अगर (hw->fc.current_mode == igc_fc_rx_छोड़ो) अणु
		छोड़ो->rx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == igc_fc_tx_छोड़ो) अणु
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण अन्यथा अगर (hw->fc.current_mode == igc_fc_full) अणु
		छोड़ो->rx_छोड़ो = 1;
		छोड़ो->tx_छोड़ो = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक igc_ethtool_set_छोड़ोparam(काष्ठा net_device *netdev,
				      काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	पूर्णांक retval = 0;

	adapter->fc_स्वतःneg = छोड़ो->स्वतःneg;

	जबतक (test_and_set_bit(__IGC_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (adapter->fc_स्वतःneg == AUTONEG_ENABLE) अणु
		hw->fc.requested_mode = igc_fc_शेष;
		अगर (netअगर_running(adapter->netdev)) अणु
			igc_करोwn(adapter);
			igc_up(adapter);
		पूर्ण अन्यथा अणु
			igc_reset(adapter);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = igc_fc_full;
		अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = igc_fc_rx_छोड़ो;
		अन्यथा अगर (!छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = igc_fc_tx_छोड़ो;
		अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
			hw->fc.requested_mode = igc_fc_none;

		hw->fc.current_mode = hw->fc.requested_mode;

		retval = ((hw->phy.media_type == igc_media_type_copper) ?
			  igc_क्रमce_mac_fc(hw) : igc_setup_link(hw));
	पूर्ण

	clear_bit(__IGC_RESETTING, &adapter->state);
	वापस retval;
पूर्ण

अटल व्योम igc_ethtool_get_strings(काष्ठा net_device *netdev, u32 stringset,
				    u8 *data)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	u8 *p = data;
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_TEST:
		स_नकल(data, *igc_gstrings_test,
		       IGC_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < IGC_GLOBAL_STATS_LEN; i++) अणु
			स_नकल(p, igc_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < IGC_NETDEV_STATS_LEN; i++) अणु
			स_नकल(p, igc_gstrings_net_stats[i].stat_string,
			       ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			प्र_लिखो(p, "tx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "tx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "tx_queue_%u_restart", i);
			p += ETH_GSTRING_LEN;
		पूर्ण
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			प्र_लिखो(p, "rx_queue_%u_packets", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "rx_queue_%u_bytes", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "rx_queue_%u_drops", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "rx_queue_%u_csum_err", i);
			p += ETH_GSTRING_LEN;
			प्र_लिखो(p, "rx_queue_%u_alloc_failed", i);
			p += ETH_GSTRING_LEN;
		पूर्ण
		/* BUG_ON(p - data != IGC_STATS_LEN * ETH_GSTRING_LEN); */
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		स_नकल(data, igc_priv_flags_strings,
		       IGC_PRIV_FLAGS_STR_LEN * ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक igc_ethtool_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस IGC_STATS_LEN;
	हाल ETH_SS_TEST:
		वापस IGC_TEST_LEN;
	हाल ETH_SS_PRIV_FLAGS:
		वापस IGC_PRIV_FLAGS_STR_LEN;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम igc_ethtool_get_stats(काष्ठा net_device *netdev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा rtnl_link_stats64 *net_stats = &adapter->stats64;
	अचिन्हित पूर्णांक start;
	काष्ठा igc_ring *ring;
	पूर्णांक i, j;
	अक्षर *p;

	spin_lock(&adapter->stats64_lock);
	igc_update_stats(adapter);

	क्रम (i = 0; i < IGC_GLOBAL_STATS_LEN; i++) अणु
		p = (अक्षर *)adapter + igc_gstrings_stats[i].stat_offset;
		data[i] = (igc_gstrings_stats[i].माप_stat ==
			माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
	क्रम (j = 0; j < IGC_NETDEV_STATS_LEN; j++, i++) अणु
		p = (अक्षर *)net_stats + igc_gstrings_net_stats[j].stat_offset;
		data[i] = (igc_gstrings_net_stats[j].माप_stat ==
			माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण
	क्रम (j = 0; j < adapter->num_tx_queues; j++) अणु
		u64	restart2;

		ring = adapter->tx_ring[j];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp);
			data[i]   = ring->tx_stats.packets;
			data[i + 1] = ring->tx_stats.bytes;
			data[i + 2] = ring->tx_stats.restart_queue;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->tx_syncp, start));
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->tx_syncp2);
			restart2  = ring->tx_stats.restart_queue2;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->tx_syncp2, start));
		data[i + 2] += restart2;

		i += IGC_TX_QUEUE_STATS_LEN;
	पूर्ण
	क्रम (j = 0; j < adapter->num_rx_queues; j++) अणु
		ring = adapter->rx_ring[j];
		करो अणु
			start = u64_stats_fetch_begin_irq(&ring->rx_syncp);
			data[i]   = ring->rx_stats.packets;
			data[i + 1] = ring->rx_stats.bytes;
			data[i + 2] = ring->rx_stats.drops;
			data[i + 3] = ring->rx_stats.csum_err;
			data[i + 4] = ring->rx_stats.alloc_failed;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&ring->rx_syncp, start));
		i += IGC_RX_QUEUE_STATS_LEN;
	पूर्ण
	spin_unlock(&adapter->stats64_lock);
पूर्ण

अटल पूर्णांक igc_ethtool_get_coalesce(काष्ठा net_device *netdev,
				    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->rx_itr_setting <= 3)
		ec->rx_coalesce_usecs = adapter->rx_itr_setting;
	अन्यथा
		ec->rx_coalesce_usecs = adapter->rx_itr_setting >> 2;

	अगर (!(adapter->flags & IGC_FLAG_QUEUE_PAIRS)) अणु
		अगर (adapter->tx_itr_setting <= 3)
			ec->tx_coalesce_usecs = adapter->tx_itr_setting;
		अन्यथा
			ec->tx_coalesce_usecs = adapter->tx_itr_setting >> 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_set_coalesce(काष्ठा net_device *netdev,
				    काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	अगर (ec->rx_coalesce_usecs > IGC_MAX_ITR_USECS ||
	    (ec->rx_coalesce_usecs > 3 &&
	     ec->rx_coalesce_usecs < IGC_MIN_ITR_USECS) ||
	    ec->rx_coalesce_usecs == 2)
		वापस -EINVAL;

	अगर (ec->tx_coalesce_usecs > IGC_MAX_ITR_USECS ||
	    (ec->tx_coalesce_usecs > 3 &&
	     ec->tx_coalesce_usecs < IGC_MIN_ITR_USECS) ||
	    ec->tx_coalesce_usecs == 2)
		वापस -EINVAL;

	अगर ((adapter->flags & IGC_FLAG_QUEUE_PAIRS) && ec->tx_coalesce_usecs)
		वापस -EINVAL;

	/* If ITR is disabled, disable DMAC */
	अगर (ec->rx_coalesce_usecs == 0) अणु
		अगर (adapter->flags & IGC_FLAG_DMAC)
			adapter->flags &= ~IGC_FLAG_DMAC;
	पूर्ण

	/* convert to rate of irq's per second */
	अगर (ec->rx_coalesce_usecs && ec->rx_coalesce_usecs <= 3)
		adapter->rx_itr_setting = ec->rx_coalesce_usecs;
	अन्यथा
		adapter->rx_itr_setting = ec->rx_coalesce_usecs << 2;

	/* convert to rate of irq's per second */
	अगर (adapter->flags & IGC_FLAG_QUEUE_PAIRS)
		adapter->tx_itr_setting = adapter->rx_itr_setting;
	अन्यथा अगर (ec->tx_coalesce_usecs && ec->tx_coalesce_usecs <= 3)
		adapter->tx_itr_setting = ec->tx_coalesce_usecs;
	अन्यथा
		adapter->tx_itr_setting = ec->tx_coalesce_usecs << 2;

	क्रम (i = 0; i < adapter->num_q_vectors; i++) अणु
		काष्ठा igc_q_vector *q_vector = adapter->q_vector[i];

		q_vector->tx.work_limit = adapter->tx_work_limit;
		अगर (q_vector->rx.ring)
			q_vector->itr_val = adapter->rx_itr_setting;
		अन्यथा
			q_vector->itr_val = adapter->tx_itr_setting;
		अगर (q_vector->itr_val && q_vector->itr_val <= 3)
			q_vector->itr_val = IGC_START_ITR;
		q_vector->set_itr = 1;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा ETHER_TYPE_FULL_MASK ((__क्रमce __be16)~0)
अटल पूर्णांक igc_ethtool_get_nfc_rule(काष्ठा igc_adapter *adapter,
				    काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp = &cmd->fs;
	काष्ठा igc_nfc_rule *rule = शून्य;

	cmd->data = IGC_MAX_RXNFC_RULES;

	mutex_lock(&adapter->nfc_rule_lock);

	rule = igc_get_nfc_rule(adapter, fsp->location);
	अगर (!rule)
		जाओ out;

	fsp->flow_type = ETHER_FLOW;
	fsp->ring_cookie = rule->action;

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_ETHER_TYPE) अणु
		fsp->h_u.ether_spec.h_proto = htons(rule->filter.etype);
		fsp->m_u.ether_spec.h_proto = ETHER_TYPE_FULL_MASK;
	पूर्ण

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_VLAN_TCI) अणु
		fsp->flow_type |= FLOW_EXT;
		fsp->h_ext.vlan_tci = htons(rule->filter.vlan_tci);
		fsp->m_ext.vlan_tci = htons(VLAN_PRIO_MASK);
	पूर्ण

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_DST_MAC_ADDR) अणु
		ether_addr_copy(fsp->h_u.ether_spec.h_dest,
				rule->filter.dst_addr);
		eth_broadcast_addr(fsp->m_u.ether_spec.h_dest);
	पूर्ण

	अगर (rule->filter.match_flags & IGC_FILTER_FLAG_SRC_MAC_ADDR) अणु
		ether_addr_copy(fsp->h_u.ether_spec.h_source,
				rule->filter.src_addr);
		eth_broadcast_addr(fsp->m_u.ether_spec.h_source);
	पूर्ण

	mutex_unlock(&adapter->nfc_rule_lock);
	वापस 0;

out:
	mutex_unlock(&adapter->nfc_rule_lock);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक igc_ethtool_get_nfc_rules(काष्ठा igc_adapter *adapter,
				     काष्ठा ethtool_rxnfc *cmd,
				     u32 *rule_locs)
अणु
	काष्ठा igc_nfc_rule *rule;
	पूर्णांक cnt = 0;

	cmd->data = IGC_MAX_RXNFC_RULES;

	mutex_lock(&adapter->nfc_rule_lock);

	list_क्रम_each_entry(rule, &adapter->nfc_rule_list, list) अणु
		अगर (cnt == cmd->rule_cnt) अणु
			mutex_unlock(&adapter->nfc_rule_lock);
			वापस -EMSGSIZE;
		पूर्ण
		rule_locs[cnt] = rule->location;
		cnt++;
	पूर्ण

	mutex_unlock(&adapter->nfc_rule_lock);

	cmd->rule_cnt = cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_get_rss_hash_opts(काष्ठा igc_adapter *adapter,
					 काष्ठा ethtool_rxnfc *cmd)
अणु
	cmd->data = 0;

	/* Report शेष options क्रम RSS on igc */
	चयन (cmd->flow_type) अणु
	हाल TCP_V4_FLOW:
		cmd->data |= RXH_L4_B_0_1 | RXH_L4_B_2_3;
		fallthrough;
	हाल UDP_V4_FLOW:
		अगर (adapter->flags & IGC_FLAG_RSS_FIELD_IPV4_UDP)
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
		अगर (adapter->flags & IGC_FLAG_RSS_FIELD_IPV6_UDP)
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

अटल पूर्णांक igc_ethtool_get_rxnfc(काष्ठा net_device *dev,
				 काष्ठा ethtool_rxnfc *cmd, u32 *rule_locs)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(dev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = adapter->num_rx_queues;
		वापस 0;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = adapter->nfc_rule_count;
		वापस 0;
	हाल ETHTOOL_GRXCLSRULE:
		वापस igc_ethtool_get_nfc_rule(adapter, cmd);
	हाल ETHTOOL_GRXCLSRLALL:
		वापस igc_ethtool_get_nfc_rules(adapter, cmd, rule_locs);
	हाल ETHTOOL_GRXFH:
		वापस igc_ethtool_get_rss_hash_opts(adapter, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

#घोषणा UDP_RSS_FLAGS (IGC_FLAG_RSS_FIELD_IPV4_UDP | \
		       IGC_FLAG_RSS_FIELD_IPV6_UDP)
अटल पूर्णांक igc_ethtool_set_rss_hash_opt(काष्ठा igc_adapter *adapter,
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
			flags &= ~IGC_FLAG_RSS_FIELD_IPV4_UDP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			flags |= IGC_FLAG_RSS_FIELD_IPV4_UDP;
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
			flags &= ~IGC_FLAG_RSS_FIELD_IPV6_UDP;
			अवरोध;
		हाल (RXH_L4_B_0_1 | RXH_L4_B_2_3):
			flags |= IGC_FLAG_RSS_FIELD_IPV6_UDP;
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
		काष्ठा igc_hw *hw = &adapter->hw;
		u32 mrqc = rd32(IGC_MRQC);

		अगर ((flags & UDP_RSS_FLAGS) &&
		    !(adapter->flags & UDP_RSS_FLAGS))
			netdev_err(adapter->netdev,
				   "Enabling UDP RSS: fragmented packets may arrive out of order to the stack above\n");

		adapter->flags = flags;

		/* Perक्रमm hash on these packet types */
		mrqc |= IGC_MRQC_RSS_FIELD_IPV4 |
			IGC_MRQC_RSS_FIELD_IPV4_TCP |
			IGC_MRQC_RSS_FIELD_IPV6 |
			IGC_MRQC_RSS_FIELD_IPV6_TCP;

		mrqc &= ~(IGC_MRQC_RSS_FIELD_IPV4_UDP |
			  IGC_MRQC_RSS_FIELD_IPV6_UDP);

		अगर (flags & IGC_FLAG_RSS_FIELD_IPV4_UDP)
			mrqc |= IGC_MRQC_RSS_FIELD_IPV4_UDP;

		अगर (flags & IGC_FLAG_RSS_FIELD_IPV6_UDP)
			mrqc |= IGC_MRQC_RSS_FIELD_IPV6_UDP;

		wr32(IGC_MRQC, mrqc);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम igc_ethtool_init_nfc_rule(काष्ठा igc_nfc_rule *rule,
				      स्थिर काष्ठा ethtool_rx_flow_spec *fsp)
अणु
	INIT_LIST_HEAD(&rule->list);

	rule->action = fsp->ring_cookie;
	rule->location = fsp->location;

	अगर ((fsp->flow_type & FLOW_EXT) && fsp->m_ext.vlan_tci) अणु
		rule->filter.vlan_tci = ntohs(fsp->h_ext.vlan_tci);
		rule->filter.match_flags |= IGC_FILTER_FLAG_VLAN_TCI;
	पूर्ण

	अगर (fsp->m_u.ether_spec.h_proto == ETHER_TYPE_FULL_MASK) अणु
		rule->filter.etype = ntohs(fsp->h_u.ether_spec.h_proto);
		rule->filter.match_flags = IGC_FILTER_FLAG_ETHER_TYPE;
	पूर्ण

	/* Both source and destination address filters only support the full
	 * mask.
	 */
	अगर (is_broadcast_ether_addr(fsp->m_u.ether_spec.h_source)) अणु
		rule->filter.match_flags |= IGC_FILTER_FLAG_SRC_MAC_ADDR;
		ether_addr_copy(rule->filter.src_addr,
				fsp->h_u.ether_spec.h_source);
	पूर्ण

	अगर (is_broadcast_ether_addr(fsp->m_u.ether_spec.h_dest)) अणु
		rule->filter.match_flags |= IGC_FILTER_FLAG_DST_MAC_ADDR;
		ether_addr_copy(rule->filter.dst_addr,
				fsp->h_u.ether_spec.h_dest);
	पूर्ण
पूर्ण

/**
 * igc_ethtool_check_nfc_rule() - Check अगर NFC rule is valid
 * @adapter: Poपूर्णांकer to adapter
 * @rule: Rule under evaluation
 *
 * The driver करोesn't support rules with multiple matches so अगर more than
 * one bit in filter flags is set, @rule is considered invalid.
 *
 * Also, अगर there is alपढ़ोy another rule with the same filter in a dअगरferent
 * location, @rule is considered invalid.
 *
 * Context: Expects adapter->nfc_rule_lock to be held by caller.
 *
 * Return: 0 in हाल of success, negative त्रुटि_सं code otherwise.
 */
अटल पूर्णांक igc_ethtool_check_nfc_rule(काष्ठा igc_adapter *adapter,
				      काष्ठा igc_nfc_rule *rule)
अणु
	काष्ठा net_device *dev = adapter->netdev;
	u8 flags = rule->filter.match_flags;
	काष्ठा igc_nfc_rule *पंचांगp;

	अगर (!flags) अणु
		netdev_dbg(dev, "Rule with no match\n");
		वापस -EINVAL;
	पूर्ण

	अगर (flags & (flags - 1)) अणु
		netdev_dbg(dev, "Rule with multiple matches not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	list_क्रम_each_entry(पंचांगp, &adapter->nfc_rule_list, list) अणु
		अगर (!स_भेद(&rule->filter, &पंचांगp->filter,
			    माप(rule->filter)) &&
		    पंचांगp->location != rule->location) अणु
			netdev_dbg(dev, "Rule already exists\n");
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_add_nfc_rule(काष्ठा igc_adapter *adapter,
				    काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा igc_nfc_rule *rule, *old_rule;
	पूर्णांक err;

	अगर (!(netdev->hw_features & NETIF_F_NTUPLE)) अणु
		netdev_dbg(netdev, "N-tuple filters disabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((fsp->flow_type & ~FLOW_EXT) != ETHER_FLOW) अणु
		netdev_dbg(netdev, "Only ethernet flow type is supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर ((fsp->flow_type & FLOW_EXT) &&
	    fsp->m_ext.vlan_tci != htons(VLAN_PRIO_MASK)) अणु
		netdev_dbg(netdev, "VLAN mask not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (fsp->ring_cookie >= adapter->num_rx_queues) अणु
		netdev_dbg(netdev, "Invalid action\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fsp->location >= IGC_MAX_RXNFC_RULES) अणु
		netdev_dbg(netdev, "Invalid location\n");
		वापस -EINVAL;
	पूर्ण

	rule = kzalloc(माप(*rule), GFP_KERNEL);
	अगर (!rule)
		वापस -ENOMEM;

	igc_ethtool_init_nfc_rule(rule, fsp);

	mutex_lock(&adapter->nfc_rule_lock);

	err = igc_ethtool_check_nfc_rule(adapter, rule);
	अगर (err)
		जाओ err;

	old_rule = igc_get_nfc_rule(adapter, fsp->location);
	अगर (old_rule)
		igc_del_nfc_rule(adapter, old_rule);

	err = igc_add_nfc_rule(adapter, rule);
	अगर (err)
		जाओ err;

	mutex_unlock(&adapter->nfc_rule_lock);
	वापस 0;

err:
	mutex_unlock(&adapter->nfc_rule_lock);
	kमुक्त(rule);
	वापस err;
पूर्ण

अटल पूर्णांक igc_ethtool_del_nfc_rule(काष्ठा igc_adapter *adapter,
				    काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा igc_nfc_rule *rule;

	mutex_lock(&adapter->nfc_rule_lock);

	rule = igc_get_nfc_rule(adapter, fsp->location);
	अगर (!rule) अणु
		mutex_unlock(&adapter->nfc_rule_lock);
		वापस -EINVAL;
	पूर्ण

	igc_del_nfc_rule(adapter, rule);

	mutex_unlock(&adapter->nfc_rule_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_set_rxnfc(काष्ठा net_device *dev,
				 काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(dev);

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXFH:
		वापस igc_ethtool_set_rss_hash_opt(adapter, cmd);
	हाल ETHTOOL_SRXCLSRLINS:
		वापस igc_ethtool_add_nfc_rule(adapter, cmd);
	हाल ETHTOOL_SRXCLSRLDEL:
		वापस igc_ethtool_del_nfc_rule(adapter, cmd);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

व्योम igc_ग_लिखो_rss_indir_tbl(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 reg = IGC_RETA(0);
	u32 shअगरt = 0;
	पूर्णांक i = 0;

	जबतक (i < IGC_RETA_SIZE) अणु
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

अटल u32 igc_ethtool_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	वापस IGC_RETA_SIZE;
पूर्ण

अटल पूर्णांक igc_ethtool_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key,
				u8 *hfunc)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	पूर्णांक i;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;
	अगर (!indir)
		वापस 0;
	क्रम (i = 0; i < IGC_RETA_SIZE; i++)
		indir[i] = adapter->rss_indir_tbl[i];

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir,
				स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	u32 num_queues;
	पूर्णांक i;

	/* We करो not allow change in unsupported parameters */
	अगर (key ||
	    (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP))
		वापस -EOPNOTSUPP;
	अगर (!indir)
		वापस 0;

	num_queues = adapter->rss_queues;

	/* Verअगरy user input. */
	क्रम (i = 0; i < IGC_RETA_SIZE; i++)
		अगर (indir[i] >= num_queues)
			वापस -EINVAL;

	क्रम (i = 0; i < IGC_RETA_SIZE; i++)
		adapter->rss_indir_tbl[i] = indir[i];

	igc_ग_लिखो_rss_indir_tbl(adapter);

	वापस 0;
पूर्ण

अटल व्योम igc_ethtool_get_channels(काष्ठा net_device *netdev,
				     काष्ठा ethtool_channels *ch)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	/* Report maximum channels */
	ch->max_combined = igc_get_max_rss_queues(adapter);

	/* Report info क्रम other vector */
	अगर (adapter->flags & IGC_FLAG_HAS_MSIX) अणु
		ch->max_other = NON_Q_VECTORS;
		ch->other_count = NON_Q_VECTORS;
	पूर्ण

	ch->combined_count = adapter->rss_queues;
पूर्ण

अटल पूर्णांक igc_ethtool_set_channels(काष्ठा net_device *netdev,
				    काष्ठा ethtool_channels *ch)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक count = ch->combined_count;
	अचिन्हित पूर्णांक max_combined = 0;

	/* Verअगरy they are not requesting separate vectors */
	अगर (!count || ch->rx_count || ch->tx_count)
		वापस -EINVAL;

	/* Verअगरy other_count is valid and has not been changed */
	अगर (ch->other_count != NON_Q_VECTORS)
		वापस -EINVAL;

	/* Verअगरy the number of channels करोesn't exceed hw limits */
	max_combined = igc_get_max_rss_queues(adapter);
	अगर (count > max_combined)
		वापस -EINVAL;

	अगर (count != adapter->rss_queues) अणु
		adapter->rss_queues = count;
		igc_set_flag_queue_pairs(adapter, max_combined);

		/* Hardware has to reinitialize queues and पूर्णांकerrupts to
		 * match the new configuration.
		 */
		वापस igc_reinit_queues(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_get_ts_info(काष्ठा net_device *dev,
				   काष्ठा ethtool_ts_info *info)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(dev);

	अगर (adapter->ptp_घड़ी)
		info->phc_index = ptp_घड़ी_index(adapter->ptp_घड़ी);
	अन्यथा
		info->phc_index = -1;

	चयन (adapter->hw.mac.type) अणु
	हाल igc_i225:
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
		info->rx_filters |= BIT(HWTSTAMP_FILTER_ALL);

		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल u32 igc_ethtool_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	u32 priv_flags = 0;

	अगर (adapter->flags & IGC_FLAG_RX_LEGACY)
		priv_flags |= IGC_PRIV_FLAGS_LEGACY_RX;

	वापस priv_flags;
पूर्ण

अटल पूर्णांक igc_ethtool_set_priv_flags(काष्ठा net_device *netdev, u32 priv_flags)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	अचिन्हित पूर्णांक flags = adapter->flags;

	flags &= ~IGC_FLAG_RX_LEGACY;
	अगर (priv_flags & IGC_PRIV_FLAGS_LEGACY_RX)
		flags |= IGC_FLAG_RX_LEGACY;

	अगर (flags != adapter->flags) अणु
		adapter->flags = flags;

		/* reset पूर्णांकerface to repopulate queues */
		अगर (netअगर_running(netdev))
			igc_reinit_locked(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_get_eee(काष्ठा net_device *netdev,
			       काष्ठा ethtool_eee *edata)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 eeer;

	अगर (hw->dev_spec._base.eee_enable)
		edata->advertised =
			mmd_eee_adv_to_ethtool_adv_t(adapter->eee_advert);

	*edata = adapter->eee;
	edata->supported = SUPPORTED_Autoneg;

	eeer = rd32(IGC_EEER);

	/* EEE status on negotiated link */
	अगर (eeer & IGC_EEER_EEE_NEG)
		edata->eee_active = true;

	अगर (eeer & IGC_EEER_TX_LPI_EN)
		edata->tx_lpi_enabled = true;

	edata->eee_enabled = hw->dev_spec._base.eee_enable;

	edata->advertised = SUPPORTED_Autoneg;
	edata->lp_advertised = SUPPORTED_Autoneg;

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

अटल पूर्णांक igc_ethtool_set_eee(काष्ठा net_device *netdev,
			       काष्ठा ethtool_eee *edata)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा ethtool_eee eee_curr;
	s32 ret_val;

	स_रखो(&eee_curr, 0, माप(काष्ठा ethtool_eee));

	ret_val = igc_ethtool_get_eee(netdev, &eee_curr);
	अगर (ret_val) अणु
		netdev_err(netdev,
			   "Problem setting EEE advertisement options\n");
		वापस -EINVAL;
	पूर्ण

	अगर (eee_curr.eee_enabled) अणु
		अगर (eee_curr.tx_lpi_enabled != edata->tx_lpi_enabled) अणु
			netdev_err(netdev,
				   "Setting EEE tx-lpi is not supported\n");
			वापस -EINVAL;
		पूर्ण

		/* Tx LPI समयr is not implemented currently */
		अगर (edata->tx_lpi_समयr) अणु
			netdev_err(netdev,
				   "Setting EEE Tx LPI timer is not supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (!edata->eee_enabled) अणु
		netdev_err(netdev,
			   "Setting EEE options are not supported with EEE disabled\n");
		वापस -EINVAL;
	पूर्ण

	adapter->eee_advert = ethtool_adv_to_mmd_eee_adv_t(edata->advertised);
	अगर (hw->dev_spec._base.eee_enable != edata->eee_enabled) अणु
		hw->dev_spec._base.eee_enable = edata->eee_enabled;
		adapter->flags |= IGC_FLAG_EEE;

		/* reset link */
		अगर (netअगर_running(netdev))
			igc_reinit_locked(adapter);
		अन्यथा
			igc_reset(adapter);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक igc_ethtool_begin(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	pm_runसमय_get_sync(&adapter->pdev->dev);
	वापस 0;
पूर्ण

अटल व्योम igc_ethtool_complete(काष्ठा net_device *netdev)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);

	pm_runसमय_put(&adapter->pdev->dev);
पूर्ण

अटल पूर्णांक igc_ethtool_get_link_ksettings(काष्ठा net_device *netdev,
					  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 status;
	u32 speed;

	ethtool_link_ksettings_zero_link_mode(cmd, supported);
	ethtool_link_ksettings_zero_link_mode(cmd, advertising);

	/* supported link modes */
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10baseT_Half);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 10baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 100baseT_Half);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 100baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 1000baseT_Full);
	ethtool_link_ksettings_add_link_mode(cmd, supported, 2500baseT_Full);

	/* twisted pair */
	cmd->base.port = PORT_TP;
	cmd->base.phy_address = hw->phy.addr;

	/* advertising link modes */
	अगर (hw->phy.स्वतःneg_advertised & ADVERTISE_10_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, 10baseT_Half);
	अगर (hw->phy.स्वतःneg_advertised & ADVERTISE_10_FULL)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, 10baseT_Full);
	अगर (hw->phy.स्वतःneg_advertised & ADVERTISE_100_HALF)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, 100baseT_Half);
	अगर (hw->phy.स्वतःneg_advertised & ADVERTISE_100_FULL)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, 100baseT_Full);
	अगर (hw->phy.स्वतःneg_advertised & ADVERTISE_1000_FULL)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, 1000baseT_Full);
	अगर (hw->phy.स्वतःneg_advertised & ADVERTISE_2500_FULL)
		ethtool_link_ksettings_add_link_mode(cmd, advertising, 2500baseT_Full);

	/* set स्वतःneg settings */
	अगर (hw->mac.स्वतःneg == 1) अणु
		ethtool_link_ksettings_add_link_mode(cmd, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Autoneg);
	पूर्ण

	/* Set छोड़ो flow control settings */
	ethtool_link_ksettings_add_link_mode(cmd, supported, Pause);

	चयन (hw->fc.requested_mode) अणु
	हाल igc_fc_full:
		ethtool_link_ksettings_add_link_mode(cmd, advertising, Pause);
		अवरोध;
	हाल igc_fc_rx_छोड़ो:
		ethtool_link_ksettings_add_link_mode(cmd, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Asym_Pause);
		अवरोध;
	हाल igc_fc_tx_छोड़ो:
		ethtool_link_ksettings_add_link_mode(cmd, advertising,
						     Asym_Pause);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	status = pm_runसमय_suspended(&adapter->pdev->dev) ?
		 0 : rd32(IGC_STATUS);

	अगर (status & IGC_STATUS_LU) अणु
		अगर (status & IGC_STATUS_SPEED_1000) अणु
			/* For I225, STATUS will indicate 1G speed in both
			 * 1 Gbps and 2.5 Gbps link modes.
			 * An additional bit is used
			 * to dअगरferentiate between 1 Gbps and 2.5 Gbps.
			 */
			अगर (hw->mac.type == igc_i225 &&
			    (status & IGC_STATUS_SPEED_2500)) अणु
				speed = SPEED_2500;
			पूर्ण अन्यथा अणु
				speed = SPEED_1000;
			पूर्ण
		पूर्ण अन्यथा अगर (status & IGC_STATUS_SPEED_100) अणु
			speed = SPEED_100;
		पूर्ण अन्यथा अणु
			speed = SPEED_10;
		पूर्ण
		अगर ((status & IGC_STATUS_FD) ||
		    hw->phy.media_type != igc_media_type_copper)
			cmd->base.duplex = DUPLEX_FULL;
		अन्यथा
			cmd->base.duplex = DUPLEX_HALF;
	पूर्ण अन्यथा अणु
		speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	पूर्ण
	cmd->base.speed = speed;
	अगर (hw->mac.स्वतःneg)
		cmd->base.स्वतःneg = AUTONEG_ENABLE;
	अन्यथा
		cmd->base.स्वतःneg = AUTONEG_DISABLE;

	/* MDI-X => 2; MDI =>1; Invalid =>0 */
	अगर (hw->phy.media_type == igc_media_type_copper)
		cmd->base.eth_tp_mdix = hw->phy.is_mdix ? ETH_TP_MDI_X :
						      ETH_TP_MDI;
	अन्यथा
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;

	अगर (hw->phy.mdix == AUTO_ALL_MODES)
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;
	अन्यथा
		cmd->base.eth_tp_mdix_ctrl = hw->phy.mdix;

	वापस 0;
पूर्ण

अटल पूर्णांक
igc_ethtool_set_link_ksettings(काष्ठा net_device *netdev,
			       स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	काष्ठा net_device *dev = adapter->netdev;
	काष्ठा igc_hw *hw = &adapter->hw;
	u32 advertising;

	/* When adapter in resetting mode, स्वतःneg/speed/duplex
	 * cannot be changed
	 */
	अगर (igc_check_reset_block(hw)) अणु
		netdev_err(dev, "Cannot change link characteristics when reset is active\n");
		वापस -EINVAL;
	पूर्ण

	/* MDI setting is only allowed when स्वतःneg enabled because
	 * some hardware करोesn't allow MDI setting when speed or
	 * duplex is क्रमced.
	 */
	अगर (cmd->base.eth_tp_mdix_ctrl) अणु
		अगर (cmd->base.eth_tp_mdix_ctrl != ETH_TP_MDI_AUTO &&
		    cmd->base.स्वतःneg != AUTONEG_ENABLE) अणु
			netdev_err(dev, "Forcing MDI/MDI-X state is not supported when link speed and/or duplex are forced\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	जबतक (test_and_set_bit(__IGC_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);
	/* Converting to legacy u32 drops ETHTOOL_LINK_MODE_2500baseT_Full_BIT.
	 * We have to check this and convert it to ADVERTISE_2500_FULL
	 * (aka ETHTOOL_LINK_MODE_2500baseX_Full_BIT) explicitly.
	 */
	अगर (ethtool_link_ksettings_test_link_mode(cmd, advertising, 2500baseT_Full))
		advertising |= ADVERTISE_2500_FULL;

	अगर (cmd->base.स्वतःneg == AUTONEG_ENABLE) अणु
		hw->mac.स्वतःneg = 1;
		hw->phy.स्वतःneg_advertised = advertising;
		अगर (adapter->fc_स्वतःneg)
			hw->fc.requested_mode = igc_fc_शेष;
	पूर्ण अन्यथा अणु
		netdev_info(dev, "Force mode currently not supported\n");
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
		igc_करोwn(adapter);
		igc_up(adapter);
	पूर्ण अन्यथा अणु
		igc_reset(adapter);
	पूर्ण

	clear_bit(__IGC_RESETTING, &adapter->state);

	वापस 0;
पूर्ण

अटल व्योम igc_ethtool_diag_test(काष्ठा net_device *netdev,
				  काष्ठा ethtool_test *eth_test, u64 *data)
अणु
	काष्ठा igc_adapter *adapter = netdev_priv(netdev);
	bool अगर_running = netअगर_running(netdev);

	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		netdev_info(adapter->netdev, "Offline testing starting");
		set_bit(__IGC_TESTING, &adapter->state);

		/* Link test perक्रमmed beक्रमe hardware reset so स्वतःneg करोesn't
		 * पूर्णांकerfere with test result
		 */
		अगर (!igc_link_test(adapter, &data[TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		अगर (अगर_running)
			igc_बंद(netdev);
		अन्यथा
			igc_reset(adapter);

		netdev_info(adapter->netdev, "Register testing starting");
		अगर (!igc_reg_test(adapter, &data[TEST_REG]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igc_reset(adapter);

		netdev_info(adapter->netdev, "EEPROM testing starting");
		अगर (!igc_eeprom_test(adapter, &data[TEST_EEP]))
			eth_test->flags |= ETH_TEST_FL_FAILED;

		igc_reset(adapter);

		/* loopback and पूर्णांकerrupt tests
		 * will be implemented in the future
		 */
		data[TEST_LOOP] = 0;
		data[TEST_IRQ] = 0;

		clear_bit(__IGC_TESTING, &adapter->state);
		अगर (अगर_running)
			igc_खोलो(netdev);
	पूर्ण अन्यथा अणु
		netdev_info(adapter->netdev, "Online testing starting");

		/* रेजिस्टर, eeprom, पूर्णांकr and loopback tests not run online */
		data[TEST_REG] = 0;
		data[TEST_EEP] = 0;
		data[TEST_IRQ] = 0;
		data[TEST_LOOP] = 0;

		अगर (!igc_link_test(adapter, &data[TEST_LINK]))
			eth_test->flags |= ETH_TEST_FL_FAILED;
	पूर्ण

	msleep_पूर्णांकerruptible(4 * 1000);
पूर्ण

अटल स्थिर काष्ठा ethtool_ops igc_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS,
	.get_drvinfo		= igc_ethtool_get_drvinfo,
	.get_regs_len		= igc_ethtool_get_regs_len,
	.get_regs		= igc_ethtool_get_regs,
	.get_wol		= igc_ethtool_get_wol,
	.set_wol		= igc_ethtool_set_wol,
	.get_msglevel		= igc_ethtool_get_msglevel,
	.set_msglevel		= igc_ethtool_set_msglevel,
	.nway_reset		= igc_ethtool_nway_reset,
	.get_link		= igc_ethtool_get_link,
	.get_eeprom_len		= igc_ethtool_get_eeprom_len,
	.get_eeprom		= igc_ethtool_get_eeprom,
	.set_eeprom		= igc_ethtool_set_eeprom,
	.get_ringparam		= igc_ethtool_get_ringparam,
	.set_ringparam		= igc_ethtool_set_ringparam,
	.get_छोड़ोparam		= igc_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam		= igc_ethtool_set_छोड़ोparam,
	.get_strings		= igc_ethtool_get_strings,
	.get_sset_count		= igc_ethtool_get_sset_count,
	.get_ethtool_stats	= igc_ethtool_get_stats,
	.get_coalesce		= igc_ethtool_get_coalesce,
	.set_coalesce		= igc_ethtool_set_coalesce,
	.get_rxnfc		= igc_ethtool_get_rxnfc,
	.set_rxnfc		= igc_ethtool_set_rxnfc,
	.get_rxfh_indir_size	= igc_ethtool_get_rxfh_indir_size,
	.get_rxfh		= igc_ethtool_get_rxfh,
	.set_rxfh		= igc_ethtool_set_rxfh,
	.get_ts_info		= igc_ethtool_get_ts_info,
	.get_channels		= igc_ethtool_get_channels,
	.set_channels		= igc_ethtool_set_channels,
	.get_priv_flags		= igc_ethtool_get_priv_flags,
	.set_priv_flags		= igc_ethtool_set_priv_flags,
	.get_eee		= igc_ethtool_get_eee,
	.set_eee		= igc_ethtool_set_eee,
	.begin			= igc_ethtool_begin,
	.complete		= igc_ethtool_complete,
	.get_link_ksettings	= igc_ethtool_get_link_ksettings,
	.set_link_ksettings	= igc_ethtool_set_link_ksettings,
	.self_test		= igc_ethtool_diag_test,
पूर्ण;

व्योम igc_ethtool_set_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &igc_ethtool_ops;
पूर्ण
