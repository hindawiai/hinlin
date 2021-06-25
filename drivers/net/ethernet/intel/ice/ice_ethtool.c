<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

/* ethtool support क्रम ice */

#समावेश "ice.h"
#समावेश "ice_flow.h"
#समावेश "ice_fltr.h"
#समावेश "ice_lib.h"
#समावेश "ice_dcb_lib.h"
#समावेश <net/dcbnl.h>

काष्ठा ice_stats अणु
	अक्षर stat_string[ETH_GSTRING_LEN];
	पूर्णांक माप_stat;
	पूर्णांक stat_offset;
पूर्ण;

#घोषणा ICE_STAT(_type, _name, _stat) अणु \
	.stat_string = _name, \
	.माप_stat = माप_field(_type, _stat), \
	.stat_offset = दुरत्व(_type, _stat) \
पूर्ण

#घोषणा ICE_VSI_STAT(_name, _stat) \
		ICE_STAT(काष्ठा ice_vsi, _name, _stat)
#घोषणा ICE_PF_STAT(_name, _stat) \
		ICE_STAT(काष्ठा ice_pf, _name, _stat)

अटल पूर्णांक ice_q_stats_len(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);

	वापस ((np->vsi->alloc_txq + np->vsi->alloc_rxq) *
		(माप(काष्ठा ice_q_stats) / माप(u64)));
पूर्ण

#घोषणा ICE_PF_STATS_LEN	ARRAY_SIZE(ice_gstrings_pf_stats)
#घोषणा ICE_VSI_STATS_LEN	ARRAY_SIZE(ice_gstrings_vsi_stats)

#घोषणा ICE_PFC_STATS_LEN ( \
		(माप_field(काष्ठा ice_pf, stats.priority_xoff_rx) + \
		 माप_field(काष्ठा ice_pf, stats.priority_xon_rx) + \
		 माप_field(काष्ठा ice_pf, stats.priority_xoff_tx) + \
		 माप_field(काष्ठा ice_pf, stats.priority_xon_tx)) \
		 / माप(u64))
#घोषणा ICE_ALL_STATS_LEN(n)	(ICE_PF_STATS_LEN + ICE_PFC_STATS_LEN + \
				 ICE_VSI_STATS_LEN + ice_q_stats_len(n))

अटल स्थिर काष्ठा ice_stats ice_gstrings_vsi_stats[] = अणु
	ICE_VSI_STAT("rx_unicast", eth_stats.rx_unicast),
	ICE_VSI_STAT("tx_unicast", eth_stats.tx_unicast),
	ICE_VSI_STAT("rx_multicast", eth_stats.rx_multicast),
	ICE_VSI_STAT("tx_multicast", eth_stats.tx_multicast),
	ICE_VSI_STAT("rx_broadcast", eth_stats.rx_broadcast),
	ICE_VSI_STAT("tx_broadcast", eth_stats.tx_broadcast),
	ICE_VSI_STAT("rx_bytes", eth_stats.rx_bytes),
	ICE_VSI_STAT("tx_bytes", eth_stats.tx_bytes),
	ICE_VSI_STAT("rx_dropped", eth_stats.rx_discards),
	ICE_VSI_STAT("rx_unknown_protocol", eth_stats.rx_unknown_protocol),
	ICE_VSI_STAT("rx_alloc_fail", rx_buf_failed),
	ICE_VSI_STAT("rx_pg_alloc_fail", rx_page_failed),
	ICE_VSI_STAT("tx_errors", eth_stats.tx_errors),
	ICE_VSI_STAT("tx_linearize", tx_linearize),
	ICE_VSI_STAT("tx_busy", tx_busy),
	ICE_VSI_STAT("tx_restart", tx_restart),
पूर्ण;

क्रमागत ice_ethtool_test_id अणु
	ICE_ETH_TEST_REG = 0,
	ICE_ETH_TEST_EEPROM,
	ICE_ETH_TEST_INTR,
	ICE_ETH_TEST_LOOP,
	ICE_ETH_TEST_LINK,
पूर्ण;

अटल स्थिर अक्षर ice_gstrings_test[][ETH_GSTRING_LEN] = अणु
	"Register test  (offline)",
	"EEPROM test    (offline)",
	"Interrupt test (offline)",
	"Loopback test  (offline)",
	"Link test   (on/offline)",
पूर्ण;

#घोषणा ICE_TEST_LEN (माप(ice_gstrings_test) / ETH_GSTRING_LEN)

/* These PF_STATs might look like duplicates of some NETDEV_STATs,
 * but they aren't. This device is capable of supporting multiple
 * VSIs/netdevs on a single PF. The NETDEV_STATs are क्रम inभागidual
 * netdevs whereas the PF_STATs are क्रम the physical function that's
 * hosting these netdevs.
 *
 * The PF_STATs are appended to the netdev stats only when ethtool -S
 * is queried on the base PF netdev.
 */
अटल स्थिर काष्ठा ice_stats ice_gstrings_pf_stats[] = अणु
	ICE_PF_STAT("rx_bytes.nic", stats.eth.rx_bytes),
	ICE_PF_STAT("tx_bytes.nic", stats.eth.tx_bytes),
	ICE_PF_STAT("rx_unicast.nic", stats.eth.rx_unicast),
	ICE_PF_STAT("tx_unicast.nic", stats.eth.tx_unicast),
	ICE_PF_STAT("rx_multicast.nic", stats.eth.rx_multicast),
	ICE_PF_STAT("tx_multicast.nic", stats.eth.tx_multicast),
	ICE_PF_STAT("rx_broadcast.nic", stats.eth.rx_broadcast),
	ICE_PF_STAT("tx_broadcast.nic", stats.eth.tx_broadcast),
	ICE_PF_STAT("tx_errors.nic", stats.eth.tx_errors),
	ICE_PF_STAT("tx_timeout.nic", tx_समयout_count),
	ICE_PF_STAT("rx_size_64.nic", stats.rx_size_64),
	ICE_PF_STAT("tx_size_64.nic", stats.tx_size_64),
	ICE_PF_STAT("rx_size_127.nic", stats.rx_size_127),
	ICE_PF_STAT("tx_size_127.nic", stats.tx_size_127),
	ICE_PF_STAT("rx_size_255.nic", stats.rx_size_255),
	ICE_PF_STAT("tx_size_255.nic", stats.tx_size_255),
	ICE_PF_STAT("rx_size_511.nic", stats.rx_size_511),
	ICE_PF_STAT("tx_size_511.nic", stats.tx_size_511),
	ICE_PF_STAT("rx_size_1023.nic", stats.rx_size_1023),
	ICE_PF_STAT("tx_size_1023.nic", stats.tx_size_1023),
	ICE_PF_STAT("rx_size_1522.nic", stats.rx_size_1522),
	ICE_PF_STAT("tx_size_1522.nic", stats.tx_size_1522),
	ICE_PF_STAT("rx_size_big.nic", stats.rx_size_big),
	ICE_PF_STAT("tx_size_big.nic", stats.tx_size_big),
	ICE_PF_STAT("link_xon_rx.nic", stats.link_xon_rx),
	ICE_PF_STAT("link_xon_tx.nic", stats.link_xon_tx),
	ICE_PF_STAT("link_xoff_rx.nic", stats.link_xoff_rx),
	ICE_PF_STAT("link_xoff_tx.nic", stats.link_xoff_tx),
	ICE_PF_STAT("tx_dropped_link_down.nic", stats.tx_dropped_link_करोwn),
	ICE_PF_STAT("rx_undersize.nic", stats.rx_undersize),
	ICE_PF_STAT("rx_fragments.nic", stats.rx_fragments),
	ICE_PF_STAT("rx_oversize.nic", stats.rx_oversize),
	ICE_PF_STAT("rx_jabber.nic", stats.rx_jabber),
	ICE_PF_STAT("rx_csum_bad.nic", hw_csum_rx_error),
	ICE_PF_STAT("rx_length_errors.nic", stats.rx_len_errors),
	ICE_PF_STAT("rx_dropped.nic", stats.eth.rx_discards),
	ICE_PF_STAT("rx_crc_errors.nic", stats.crc_errors),
	ICE_PF_STAT("illegal_bytes.nic", stats.illegal_bytes),
	ICE_PF_STAT("mac_local_faults.nic", stats.mac_local_faults),
	ICE_PF_STAT("mac_remote_faults.nic", stats.mac_remote_faults),
	ICE_PF_STAT("fdir_sb_match.nic", stats.fd_sb_match),
	ICE_PF_STAT("fdir_sb_status.nic", stats.fd_sb_status),
पूर्ण;

अटल स्थिर u32 ice_regs_dump_list[] = अणु
	PFGEN_STATE,
	PRTGEN_STATUS,
	QRX_CTRL(0),
	QINT_TQCTL(0),
	QINT_RQCTL(0),
	PFINT_OICR_ENA,
	QRX_ITR(0),
पूर्ण;

काष्ठा ice_priv_flag अणु
	अक्षर name[ETH_GSTRING_LEN];
	u32 bitno;			/* bit position in pf->flags */
पूर्ण;

#घोषणा ICE_PRIV_FLAG(_name, _bitno) अणु \
	.name = _name, \
	.bitno = _bitno, \
पूर्ण

अटल स्थिर काष्ठा ice_priv_flag ice_gstrings_priv_flags[] = अणु
	ICE_PRIV_FLAG("link-down-on-close", ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA),
	ICE_PRIV_FLAG("fw-lldp-agent", ICE_FLAG_FW_LLDP_AGENT),
	ICE_PRIV_FLAG("vf-true-promisc-support",
		      ICE_FLAG_VF_TRUE_PROMISC_ENA),
	ICE_PRIV_FLAG("mdd-auto-reset-vf", ICE_FLAG_MDD_AUTO_RESET_VF),
	ICE_PRIV_FLAG("legacy-rx", ICE_FLAG_LEGACY_RX),
पूर्ण;

#घोषणा ICE_PRIV_FLAG_ARRAY_SIZE	ARRAY_SIZE(ice_gstrings_priv_flags)

अटल व्योम
ice_get_drvinfo(काष्ठा net_device *netdev, काष्ठा ethtool_drvinfo *drvinfo)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_orom_info *orom;
	काष्ठा ice_nvm_info *nvm;

	nvm = &hw->flash.nvm;
	orom = &hw->flash.orom;

	strscpy(drvinfo->driver, KBUILD_MODNAME, माप(drvinfo->driver));

	/* Display NVM version (from which the firmware version can be
	 * determined) which contains more pertinent inक्रमmation.
	 */
	snम_लिखो(drvinfo->fw_version, माप(drvinfo->fw_version),
		 "%x.%02x 0x%x %d.%d.%d", nvm->major, nvm->minor,
		 nvm->eetrack, orom->major, orom->build, orom->patch);

	strscpy(drvinfo->bus_info, pci_name(pf->pdev),
		माप(drvinfo->bus_info));
	drvinfo->n_priv_flags = ICE_PRIV_FLAG_ARRAY_SIZE;
पूर्ण

अटल पूर्णांक ice_get_regs_len(काष्ठा net_device __always_unused *netdev)
अणु
	वापस माप(ice_regs_dump_list);
पूर्ण

अटल व्योम
ice_get_regs(काष्ठा net_device *netdev, काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	u32 *regs_buf = (u32 *)p;
	अचिन्हित पूर्णांक i;

	regs->version = 1;

	क्रम (i = 0; i < ARRAY_SIZE(ice_regs_dump_list); ++i)
		regs_buf[i] = rd32(hw, ice_regs_dump_list[i]);
पूर्ण

अटल u32 ice_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;

#अगर_अघोषित CONFIG_DYNAMIC_DEBUG
	अगर (pf->hw.debug_mask)
		netdev_info(netdev, "hw debug_mask: 0x%llX\n",
			    pf->hw.debug_mask);
#पूर्ण_अगर /* !CONFIG_DYNAMIC_DEBUG */

	वापस pf->msg_enable;
पूर्ण

अटल व्योम ice_set_msglevel(काष्ठा net_device *netdev, u32 data)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;

#अगर_अघोषित CONFIG_DYNAMIC_DEBUG
	अगर (ICE_DBG_USER & data)
		pf->hw.debug_mask = data;
	अन्यथा
		pf->msg_enable = data;
#अन्यथा
	pf->msg_enable = data;
#पूर्ण_अगर /* !CONFIG_DYNAMIC_DEBUG */
पूर्ण

अटल पूर्णांक ice_get_eeprom_len(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;

	वापस (पूर्णांक)pf->hw.flash.flash_size;
पूर्ण

अटल पूर्णांक
ice_get_eeprom(काष्ठा net_device *netdev, काष्ठा ethtool_eeprom *eeprom,
	       u8 *bytes)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	पूर्णांक ret = 0;
	u8 *buf;

	dev = ice_pf_to_dev(pf);

	eeprom->magic = hw->venकरोr_id | (hw->device_id << 16);
	netdev_dbg(netdev, "GEEPROM cmd 0x%08x, offset 0x%08x, len 0x%08x\n",
		   eeprom->cmd, eeprom->offset, eeprom->len);

	buf = kzalloc(eeprom->len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	status = ice_acquire_nvm(hw, ICE_RES_READ);
	अगर (status) अणु
		dev_err(dev, "ice_acquire_nvm failed, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		ret = -EIO;
		जाओ out;
	पूर्ण

	status = ice_पढ़ो_flat_nvm(hw, eeprom->offset, &eeprom->len, buf,
				   false);
	अगर (status) अणु
		dev_err(dev, "ice_read_flat_nvm failed, err %s aq_err %s\n",
			ice_stat_str(status),
			ice_aq_str(hw->adminq.sq_last_status));
		ret = -EIO;
		जाओ release;
	पूर्ण

	स_नकल(bytes, buf, eeprom->len);
release:
	ice_release_nvm(hw);
out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/**
 * ice_active_vfs - check अगर there are any active VFs
 * @pf: board निजी काष्ठाure
 *
 * Returns true अगर an active VF is found, otherwise वापसs false
 */
अटल bool ice_active_vfs(काष्ठा ice_pf *pf)
अणु
	अचिन्हित पूर्णांक i;

	ice_क्रम_each_vf(pf, i) अणु
		काष्ठा ice_vf *vf = &pf->vf[i];

		अगर (test_bit(ICE_VF_STATE_ACTIVE, vf->vf_states))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_link_test - perक्रमm a link test on a given net_device
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * This function perक्रमms one of the self-tests required by ethtool.
 * Returns 0 on success, non-zero on failure.
 */
अटल u64 ice_link_test(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	क्रमागत ice_status status;
	bool link_up = false;

	netdev_info(netdev, "link test\n");
	status = ice_get_link_status(np->vsi->port_info, &link_up);
	अगर (status) अणु
		netdev_err(netdev, "link query error, status = %s\n",
			   ice_stat_str(status));
		वापस 1;
	पूर्ण

	अगर (!link_up)
		वापस 2;

	वापस 0;
पूर्ण

/**
 * ice_eeprom_test - perक्रमm an EEPROM test on a given net_device
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * This function perक्रमms one of the self-tests required by ethtool.
 * Returns 0 on success, non-zero on failure.
 */
अटल u64 ice_eeprom_test(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;

	netdev_info(netdev, "EEPROM test\n");
	वापस !!(ice_nvm_validate_checksum(&pf->hw));
पूर्ण

/**
 * ice_reg_pattern_test
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @reg: reg to be tested
 * @mask: bits to be touched
 */
अटल पूर्णांक ice_reg_pattern_test(काष्ठा ice_hw *hw, u32 reg, u32 mask)
अणु
	काष्ठा ice_pf *pf = (काष्ठा ice_pf *)hw->back;
	काष्ठा device *dev = ice_pf_to_dev(pf);
	अटल स्थिर u32 patterns[] = अणु
		0x5A5A5A5A, 0xA5A5A5A5,
		0x00000000, 0xFFFFFFFF
	पूर्ण;
	u32 val, orig_val;
	अचिन्हित पूर्णांक i;

	orig_val = rd32(hw, reg);
	क्रम (i = 0; i < ARRAY_SIZE(patterns); ++i) अणु
		u32 pattern = patterns[i] & mask;

		wr32(hw, reg, pattern);
		val = rd32(hw, reg);
		अगर (val == pattern)
			जारी;
		dev_err(dev, "%s: reg pattern test failed - reg 0x%08x pat 0x%08x val 0x%08x\n"
			, __func__, reg, pattern, val);
		वापस 1;
	पूर्ण

	wr32(hw, reg, orig_val);
	val = rd32(hw, reg);
	अगर (val != orig_val) अणु
		dev_err(dev, "%s: reg restore test failed - reg 0x%08x orig 0x%08x val 0x%08x\n"
			, __func__, reg, orig_val, val);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_reg_test - perक्रमm a रेजिस्टर test on a given net_device
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * This function perक्रमms one of the self-tests required by ethtool.
 * Returns 0 on success, non-zero on failure.
 */
अटल u64 ice_reg_test(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_hw *hw = np->vsi->port_info->hw;
	u32 पूर्णांक_elements = hw->func_caps.common_cap.num_msix_vectors ?
		hw->func_caps.common_cap.num_msix_vectors - 1 : 1;
	काष्ठा ice_diag_reg_test_info अणु
		u32 address;
		u32 mask;
		u32 elem_num;
		u32 elem_size;
	पूर्ण ice_reg_list[] = अणु
		अणुGLINT_ITR(0, 0), 0x00000fff, पूर्णांक_elements,
			GLINT_ITR(0, 1) - GLINT_ITR(0, 0)पूर्ण,
		अणुGLINT_ITR(1, 0), 0x00000fff, पूर्णांक_elements,
			GLINT_ITR(1, 1) - GLINT_ITR(1, 0)पूर्ण,
		अणुGLINT_ITR(0, 0), 0x00000fff, पूर्णांक_elements,
			GLINT_ITR(2, 1) - GLINT_ITR(2, 0)पूर्ण,
		अणुGLINT_CTL, 0xffff0001, 1, 0पूर्ण
	पूर्ण;
	अचिन्हित पूर्णांक i;

	netdev_dbg(netdev, "Register test\n");
	क्रम (i = 0; i < ARRAY_SIZE(ice_reg_list); ++i) अणु
		u32 j;

		क्रम (j = 0; j < ice_reg_list[i].elem_num; ++j) अणु
			u32 mask = ice_reg_list[i].mask;
			u32 reg = ice_reg_list[i].address +
				(j * ice_reg_list[i].elem_size);

			/* bail on failure (non-zero वापस) */
			अगर (ice_reg_pattern_test(hw, reg, mask))
				वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_lbtest_prepare_rings - configure Tx/Rx test rings
 * @vsi: poपूर्णांकer to the VSI काष्ठाure
 *
 * Function configures rings of a VSI क्रम loopback test without
 * enabling पूर्णांकerrupts or inक्रमming the kernel about new queues.
 *
 * Returns 0 on success, negative on failure.
 */
अटल पूर्णांक ice_lbtest_prepare_rings(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक status;

	status = ice_vsi_setup_tx_rings(vsi);
	अगर (status)
		जाओ err_setup_tx_ring;

	status = ice_vsi_setup_rx_rings(vsi);
	अगर (status)
		जाओ err_setup_rx_ring;

	status = ice_vsi_cfg(vsi);
	अगर (status)
		जाओ err_setup_rx_ring;

	status = ice_vsi_start_all_rx_rings(vsi);
	अगर (status)
		जाओ err_start_rx_ring;

	वापस status;

err_start_rx_ring:
	ice_vsi_मुक्त_rx_rings(vsi);
err_setup_rx_ring:
	ice_vsi_stop_lan_tx_rings(vsi, ICE_NO_RESET, 0);
err_setup_tx_ring:
	ice_vsi_मुक्त_tx_rings(vsi);

	वापस status;
पूर्ण

/**
 * ice_lbtest_disable_rings - disable Tx/Rx test rings after loopback test
 * @vsi: poपूर्णांकer to the VSI काष्ठाure
 *
 * Function stops and मुक्तs VSI rings after a loopback test.
 * Returns 0 on success, negative on failure.
 */
अटल पूर्णांक ice_lbtest_disable_rings(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक status;

	status = ice_vsi_stop_lan_tx_rings(vsi, ICE_NO_RESET, 0);
	अगर (status)
		netdev_err(vsi->netdev, "Failed to stop Tx rings, VSI %d error %d\n",
			   vsi->vsi_num, status);

	status = ice_vsi_stop_all_rx_rings(vsi);
	अगर (status)
		netdev_err(vsi->netdev, "Failed to stop Rx rings, VSI %d error %d\n",
			   vsi->vsi_num, status);

	ice_vsi_मुक्त_tx_rings(vsi);
	ice_vsi_मुक्त_rx_rings(vsi);

	वापस status;
पूर्ण

/**
 * ice_lbtest_create_frame - create test packet
 * @pf: poपूर्णांकer to the PF काष्ठाure
 * @ret_data: allocated frame buffer
 * @size: size of the packet data
 *
 * Function allocates a frame with a test pattern on specअगरic offsets.
 * Returns 0 on success, non-zero on failure.
 */
अटल पूर्णांक ice_lbtest_create_frame(काष्ठा ice_pf *pf, u8 **ret_data, u16 size)
अणु
	u8 *data;

	अगर (!pf)
		वापस -EINVAL;

	data = devm_kzalloc(ice_pf_to_dev(pf), size, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/* Since the ethernet test frame should always be at least
	 * 64 bytes दीर्घ, fill some octets in the payload with test data.
	 */
	स_रखो(data, 0xFF, size);
	data[32] = 0xDE;
	data[42] = 0xAD;
	data[44] = 0xBE;
	data[46] = 0xEF;

	*ret_data = data;

	वापस 0;
पूर्ण

/**
 * ice_lbtest_check_frame - verअगरy received loopback frame
 * @frame: poपूर्णांकer to the raw packet data
 *
 * Function verअगरies received test frame with a pattern.
 * Returns true अगर frame matches the pattern, false otherwise.
 */
अटल bool ice_lbtest_check_frame(u8 *frame)
अणु
	/* Validate bytes of a frame under offsets chosen earlier */
	अगर (frame[32] == 0xDE &&
	    frame[42] == 0xAD &&
	    frame[44] == 0xBE &&
	    frame[46] == 0xEF &&
	    frame[48] == 0xFF)
		वापस true;

	वापस false;
पूर्ण

/**
 * ice_diag_send - send test frames to the test ring
 * @tx_ring: poपूर्णांकer to the transmit ring
 * @data: poपूर्णांकer to the raw packet data
 * @size: size of the packet to send
 *
 * Function sends loopback packets on a test Tx ring.
 */
अटल पूर्णांक ice_diag_send(काष्ठा ice_ring *tx_ring, u8 *data, u16 size)
अणु
	काष्ठा ice_tx_desc *tx_desc;
	काष्ठा ice_tx_buf *tx_buf;
	dma_addr_t dma;
	u64 td_cmd;

	tx_desc = ICE_TX_DESC(tx_ring, tx_ring->next_to_use);
	tx_buf = &tx_ring->tx_buf[tx_ring->next_to_use];

	dma = dma_map_single(tx_ring->dev, data, size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(tx_ring->dev, dma))
		वापस -EINVAL;

	tx_desc->buf_addr = cpu_to_le64(dma);

	/* These flags are required क्रम a descriptor to be pushed out */
	td_cmd = (u64)(ICE_TX_DESC_CMD_EOP | ICE_TX_DESC_CMD_RS);
	tx_desc->cmd_type_offset_bsz =
		cpu_to_le64(ICE_TX_DESC_DTYPE_DATA |
			    (td_cmd << ICE_TXD_QW1_CMD_S) |
			    ((u64)0 << ICE_TXD_QW1_OFFSET_S) |
			    ((u64)size << ICE_TXD_QW1_TX_BUF_SZ_S) |
			    ((u64)0 << ICE_TXD_QW1_L2TAG1_S));

	tx_buf->next_to_watch = tx_desc;

	/* Force memory ग_लिखो to complete beक्रमe letting h/w know
	 * there are new descriptors to fetch.
	 */
	wmb();

	tx_ring->next_to_use++;
	अगर (tx_ring->next_to_use >= tx_ring->count)
		tx_ring->next_to_use = 0;

	ग_लिखोl_relaxed(tx_ring->next_to_use, tx_ring->tail);

	/* Wait until the packets get transmitted to the receive queue. */
	usleep_range(1000, 2000);
	dma_unmap_single(tx_ring->dev, dma, size, DMA_TO_DEVICE);

	वापस 0;
पूर्ण

#घोषणा ICE_LB_FRAME_SIZE 64
/**
 * ice_lbtest_receive_frames - receive and verअगरy test frames
 * @rx_ring: poपूर्णांकer to the receive ring
 *
 * Function receives loopback packets and verअगरy their correctness.
 * Returns number of received valid frames.
 */
अटल पूर्णांक ice_lbtest_receive_frames(काष्ठा ice_ring *rx_ring)
अणु
	काष्ठा ice_rx_buf *rx_buf;
	पूर्णांक valid_frames, i;
	u8 *received_buf;

	valid_frames = 0;

	क्रम (i = 0; i < rx_ring->count; i++) अणु
		जोड़ ice_32b_rx_flex_desc *rx_desc;

		rx_desc = ICE_RX_DESC(rx_ring, i);

		अगर (!(rx_desc->wb.status_error0 &
		    cpu_to_le16(ICE_TX_DESC_CMD_EOP | ICE_TX_DESC_CMD_RS)))
			जारी;

		rx_buf = &rx_ring->rx_buf[i];
		received_buf = page_address(rx_buf->page) + rx_buf->page_offset;

		अगर (ice_lbtest_check_frame(received_buf))
			valid_frames++;
	पूर्ण

	वापस valid_frames;
पूर्ण

/**
 * ice_loopback_test - perक्रमm a loopback test on a given net_device
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * This function perक्रमms one of the self-tests required by ethtool.
 * Returns 0 on success, non-zero on failure.
 */
अटल u64 ice_loopback_test(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *orig_vsi = np->vsi, *test_vsi;
	काष्ठा ice_pf *pf = orig_vsi->back;
	काष्ठा ice_ring *tx_ring, *rx_ring;
	u8 broadcast[ETH_ALEN], ret = 0;
	पूर्णांक num_frames, valid_frames;
	काष्ठा device *dev;
	u8 *tx_frame;
	पूर्णांक i;

	dev = ice_pf_to_dev(pf);
	netdev_info(netdev, "loopback test\n");

	test_vsi = ice_lb_vsi_setup(pf, pf->hw.port_info);
	अगर (!test_vsi) अणु
		netdev_err(netdev, "Failed to create a VSI for the loopback test\n");
		वापस 1;
	पूर्ण

	test_vsi->netdev = netdev;
	tx_ring = test_vsi->tx_rings[0];
	rx_ring = test_vsi->rx_rings[0];

	अगर (ice_lbtest_prepare_rings(test_vsi)) अणु
		ret = 2;
		जाओ lbtest_vsi_बंद;
	पूर्ण

	अगर (ice_alloc_rx_bufs(rx_ring, rx_ring->count)) अणु
		ret = 3;
		जाओ lbtest_rings_dis;
	पूर्ण

	/* Enable MAC loopback in firmware */
	अगर (ice_aq_set_mac_loopback(&pf->hw, true, शून्य)) अणु
		ret = 4;
		जाओ lbtest_mac_dis;
	पूर्ण

	/* Test VSI needs to receive broadcast packets */
	eth_broadcast_addr(broadcast);
	अगर (ice_fltr_add_mac(test_vsi, broadcast, ICE_FWD_TO_VSI)) अणु
		ret = 5;
		जाओ lbtest_mac_dis;
	पूर्ण

	अगर (ice_lbtest_create_frame(pf, &tx_frame, ICE_LB_FRAME_SIZE)) अणु
		ret = 7;
		जाओ हटाओ_mac_filters;
	पूर्ण

	num_frames = min_t(पूर्णांक, tx_ring->count, 32);
	क्रम (i = 0; i < num_frames; i++) अणु
		अगर (ice_diag_send(tx_ring, tx_frame, ICE_LB_FRAME_SIZE)) अणु
			ret = 8;
			जाओ lbtest_मुक्त_frame;
		पूर्ण
	पूर्ण

	valid_frames = ice_lbtest_receive_frames(rx_ring);
	अगर (!valid_frames)
		ret = 9;
	अन्यथा अगर (valid_frames != num_frames)
		ret = 10;

lbtest_मुक्त_frame:
	devm_kमुक्त(dev, tx_frame);
हटाओ_mac_filters:
	अगर (ice_fltr_हटाओ_mac(test_vsi, broadcast, ICE_FWD_TO_VSI))
		netdev_err(netdev, "Could not remove MAC filter for the test VSI\n");
lbtest_mac_dis:
	/* Disable MAC loopback after the test is completed. */
	अगर (ice_aq_set_mac_loopback(&pf->hw, false, शून्य))
		netdev_err(netdev, "Could not disable MAC loopback\n");
lbtest_rings_dis:
	अगर (ice_lbtest_disable_rings(test_vsi))
		netdev_err(netdev, "Could not disable test rings\n");
lbtest_vsi_बंद:
	test_vsi->netdev = शून्य;
	अगर (ice_vsi_release(test_vsi))
		netdev_err(netdev, "Failed to remove the test VSI\n");

	वापस ret;
पूर्ण

/**
 * ice_पूर्णांकr_test - perक्रमm an पूर्णांकerrupt test on a given net_device
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * This function perक्रमms one of the self-tests required by ethtool.
 * Returns 0 on success, non-zero on failure.
 */
अटल u64 ice_पूर्णांकr_test(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;
	u16 swic_old = pf->sw_पूर्णांक_count;

	netdev_info(netdev, "interrupt test\n");

	wr32(&pf->hw, GLINT_DYN_CTL(pf->oicr_idx),
	     GLINT_DYN_CTL_SW_ITR_INDX_M |
	     GLINT_DYN_CTL_INTENA_MSK_M |
	     GLINT_DYN_CTL_SWINT_TRIG_M);

	usleep_range(1000, 2000);
	वापस (swic_old == pf->sw_पूर्णांक_count);
पूर्ण

/**
 * ice_self_test - handler function क्रम perक्रमming a self-test by ethtool
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @eth_test: ethtool_test काष्ठाure
 * @data: required by ethtool.self_test
 *
 * This function is called after invoking 'ethtool -t devname' command where
 * devname is the name of the network device on which ethtool should operate.
 * It perक्रमms a set of self-tests to check अगर a device works properly.
 */
अटल व्योम
ice_self_test(काष्ठा net_device *netdev, काष्ठा ethtool_test *eth_test,
	      u64 *data)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	bool अगर_running = netअगर_running(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);

	अगर (eth_test->flags == ETH_TEST_FL_OFFLINE) अणु
		netdev_info(netdev, "offline testing starting\n");

		set_bit(ICE_TESTING, pf->state);

		अगर (ice_active_vfs(pf)) अणु
			dev_warn(dev, "Please take active VFs and Netqueues offline and restart the adapter before running NIC diagnostics\n");
			data[ICE_ETH_TEST_REG] = 1;
			data[ICE_ETH_TEST_EEPROM] = 1;
			data[ICE_ETH_TEST_INTR] = 1;
			data[ICE_ETH_TEST_LOOP] = 1;
			data[ICE_ETH_TEST_LINK] = 1;
			eth_test->flags |= ETH_TEST_FL_FAILED;
			clear_bit(ICE_TESTING, pf->state);
			जाओ skip_ol_tests;
		पूर्ण
		/* If the device is online then take it offline */
		अगर (अगर_running)
			/* indicate we're in test mode */
			ice_stop(netdev);

		data[ICE_ETH_TEST_LINK] = ice_link_test(netdev);
		data[ICE_ETH_TEST_EEPROM] = ice_eeprom_test(netdev);
		data[ICE_ETH_TEST_INTR] = ice_पूर्णांकr_test(netdev);
		data[ICE_ETH_TEST_LOOP] = ice_loopback_test(netdev);
		data[ICE_ETH_TEST_REG] = ice_reg_test(netdev);

		अगर (data[ICE_ETH_TEST_LINK] ||
		    data[ICE_ETH_TEST_EEPROM] ||
		    data[ICE_ETH_TEST_LOOP] ||
		    data[ICE_ETH_TEST_INTR] ||
		    data[ICE_ETH_TEST_REG])
			eth_test->flags |= ETH_TEST_FL_FAILED;

		clear_bit(ICE_TESTING, pf->state);

		अगर (अगर_running) अणु
			पूर्णांक status = ice_खोलो(netdev);

			अगर (status) अणु
				dev_err(dev, "Could not open device %s, err %d\n",
					pf->पूर्णांक_name, status);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Online tests */
		netdev_info(netdev, "online testing starting\n");

		data[ICE_ETH_TEST_LINK] = ice_link_test(netdev);
		अगर (data[ICE_ETH_TEST_LINK])
			eth_test->flags |= ETH_TEST_FL_FAILED;

		/* Offline only tests, not run in online; pass by शेष */
		data[ICE_ETH_TEST_REG] = 0;
		data[ICE_ETH_TEST_EEPROM] = 0;
		data[ICE_ETH_TEST_INTR] = 0;
		data[ICE_ETH_TEST_LOOP] = 0;
	पूर्ण

skip_ol_tests:
	netdev_info(netdev, "testing finished\n");
पूर्ण

अटल व्योम ice_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	अचिन्हित पूर्णांक i;
	u8 *p = data;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ICE_VSI_STATS_LEN; i++)
			ethtool_प्र_लिखो(&p,
					ice_gstrings_vsi_stats[i].stat_string);

		ice_क्रम_each_alloc_txq(vsi, i) अणु
			ethtool_प्र_लिखो(&p, "tx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "tx_queue_%u_bytes", i);
		पूर्ण

		ice_क्रम_each_alloc_rxq(vsi, i) अणु
			ethtool_प्र_लिखो(&p, "rx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_bytes", i);
		पूर्ण

		अगर (vsi->type != ICE_VSI_PF)
			वापस;

		क्रम (i = 0; i < ICE_PF_STATS_LEN; i++)
			ethtool_प्र_लिखो(&p,
					ice_gstrings_pf_stats[i].stat_string);

		क्रम (i = 0; i < ICE_MAX_USER_PRIORITY; i++) अणु
			ethtool_प्र_लिखो(&p, "tx_priority_%u_xon.nic", i);
			ethtool_प्र_लिखो(&p, "tx_priority_%u_xoff.nic", i);
		पूर्ण
		क्रम (i = 0; i < ICE_MAX_USER_PRIORITY; i++) अणु
			ethtool_प्र_लिखो(&p, "rx_priority_%u_xon.nic", i);
			ethtool_प्र_लिखो(&p, "rx_priority_%u_xoff.nic", i);
		पूर्ण
		अवरोध;
	हाल ETH_SS_TEST:
		स_नकल(data, ice_gstrings_test, ICE_TEST_LEN * ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_PRIV_FLAGS:
		क्रम (i = 0; i < ICE_PRIV_FLAG_ARRAY_SIZE; i++)
			ethtool_प्र_लिखो(&p, ice_gstrings_priv_flags[i].name);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
ice_set_phys_id(काष्ठा net_device *netdev, क्रमागत ethtool_phys_id_state state)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	bool led_active;

	चयन (state) अणु
	हाल ETHTOOL_ID_ACTIVE:
		led_active = true;
		अवरोध;
	हाल ETHTOOL_ID_INACTIVE:
		led_active = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ice_aq_set_port_id_led(np->vsi->port_info, !led_active, शून्य))
		वापस -EIO;

	वापस 0;
पूर्ण

/**
 * ice_set_fec_cfg - Set link FEC options
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @req_fec: FEC mode to configure
 */
अटल पूर्णांक ice_set_fec_cfg(काष्ठा net_device *netdev, क्रमागत ice_fec_mode req_fec)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_aqc_set_phy_cfg_data config = अणु 0 पूर्ण;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_port_info *pi;

	pi = vsi->port_info;
	अगर (!pi)
		वापस -EOPNOTSUPP;

	/* Changing the FEC parameters is not supported अगर not the PF VSI */
	अगर (vsi->type != ICE_VSI_PF) अणु
		netdev_info(netdev, "Changing FEC parameters only supported for PF VSI\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Proceed only अगर requesting dअगरferent FEC mode */
	अगर (pi->phy.curr_user_fec_req == req_fec)
		वापस 0;

	/* Copy the current user PHY configuration. The current user PHY
	 * configuration is initialized during probe from PHY capabilities
	 * software mode, and updated on set PHY configuration.
	 */
	स_नकल(&config, &pi->phy.curr_user_phy_cfg, माप(config));

	ice_cfg_phy_fec(pi, &config, req_fec);
	config.caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;

	अगर (ice_aq_set_phy_cfg(pi->hw, pi, &config, शून्य))
		वापस -EAGAIN;

	/* Save requested FEC config */
	pi->phy.curr_user_fec_req = req_fec;

	वापस 0;
पूर्ण

/**
 * ice_set_fecparam - Set FEC link options
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @fecparam: Ethtool काष्ठाure to retrieve FEC parameters
 */
अटल पूर्णांक
ice_set_fecparam(काष्ठा net_device *netdev, काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	क्रमागत ice_fec_mode fec;

	चयन (fecparam->fec) अणु
	हाल ETHTOOL_FEC_AUTO:
		fec = ICE_FEC_AUTO;
		अवरोध;
	हाल ETHTOOL_FEC_RS:
		fec = ICE_FEC_RS;
		अवरोध;
	हाल ETHTOOL_FEC_BASER:
		fec = ICE_FEC_BASER;
		अवरोध;
	हाल ETHTOOL_FEC_OFF:
	हाल ETHTOOL_FEC_NONE:
		fec = ICE_FEC_NONE;
		अवरोध;
	शेष:
		dev_warn(ice_pf_to_dev(vsi->back), "Unsupported FEC mode: %d\n",
			 fecparam->fec);
		वापस -EINVAL;
	पूर्ण

	वापस ice_set_fec_cfg(netdev, fec);
पूर्ण

/**
 * ice_get_fecparam - Get link FEC options
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @fecparam: Ethtool काष्ठाure to retrieve FEC parameters
 */
अटल पूर्णांक
ice_get_fecparam(काष्ठा net_device *netdev, काष्ठा ethtool_fecparam *fecparam)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_aqc_get_phy_caps_data *caps;
	काष्ठा ice_link_status *link_info;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_port_info *pi;
	क्रमागत ice_status status;
	पूर्णांक err = 0;

	pi = vsi->port_info;

	अगर (!pi)
		वापस -EOPNOTSUPP;
	link_info = &pi->phy.link_info;

	/* Set FEC mode based on negotiated link info */
	चयन (link_info->fec_info) अणु
	हाल ICE_AQ_LINK_25G_KR_FEC_EN:
		fecparam->active_fec = ETHTOOL_FEC_BASER;
		अवरोध;
	हाल ICE_AQ_LINK_25G_RS_528_FEC_EN:
	हाल ICE_AQ_LINK_25G_RS_544_FEC_EN:
		fecparam->active_fec = ETHTOOL_FEC_RS;
		अवरोध;
	शेष:
		fecparam->active_fec = ETHTOOL_FEC_OFF;
		अवरोध;
	पूर्ण

	caps = kzalloc(माप(*caps), GFP_KERNEL);
	अगर (!caps)
		वापस -ENOMEM;

	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP_MEDIA,
				     caps, शून्य);
	अगर (status) अणु
		err = -EAGAIN;
		जाओ करोne;
	पूर्ण

	/* Set supported/configured FEC modes based on PHY capability */
	अगर (caps->caps & ICE_AQC_PHY_EN_AUTO_FEC)
		fecparam->fec |= ETHTOOL_FEC_AUTO;
	अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_REQ)
		fecparam->fec |= ETHTOOL_FEC_BASER;
	अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_528_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_544_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN)
		fecparam->fec |= ETHTOOL_FEC_RS;
	अगर (caps->link_fec_options == 0)
		fecparam->fec |= ETHTOOL_FEC_OFF;

करोne:
	kमुक्त(caps);
	वापस err;
पूर्ण

/**
 * ice_nway_reset - restart स्वतःnegotiation
 * @netdev: network पूर्णांकerface device काष्ठाure
 */
अटल पूर्णांक ice_nway_reset(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	पूर्णांक err;

	/* If VSI state is up, then restart स्वतःneg with link up */
	अगर (!test_bit(ICE_DOWN, vsi->back->state))
		err = ice_set_link(vsi, true);
	अन्यथा
		err = ice_set_link(vsi, false);

	वापस err;
पूर्ण

/**
 * ice_get_priv_flags - report device निजी flags
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The get string set count and the string set should be matched क्रम each
 * flag वापसed.  Add new strings क्रम each flag to the ice_gstrings_priv_flags
 * array.
 *
 * Returns a u32 biपंचांगap of flags.
 */
अटल u32 ice_get_priv_flags(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	u32 i, ret_flags = 0;

	क्रम (i = 0; i < ICE_PRIV_FLAG_ARRAY_SIZE; i++) अणु
		स्थिर काष्ठा ice_priv_flag *priv_flag;

		priv_flag = &ice_gstrings_priv_flags[i];

		अगर (test_bit(priv_flag->bitno, pf->flags))
			ret_flags |= BIT(i);
	पूर्ण

	वापस ret_flags;
पूर्ण

/**
 * ice_set_priv_flags - set निजी flags
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @flags: bit flags to be set
 */
अटल पूर्णांक ice_set_priv_flags(काष्ठा net_device *netdev, u32 flags)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	DECLARE_BITMAP(change_flags, ICE_PF_FLAGS_NBITS);
	DECLARE_BITMAP(orig_flags, ICE_PF_FLAGS_NBITS);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	पूर्णांक ret = 0;
	u32 i;

	अगर (flags > BIT(ICE_PRIV_FLAG_ARRAY_SIZE))
		वापस -EINVAL;

	dev = ice_pf_to_dev(pf);
	set_bit(ICE_FLAG_ETHTOOL_CTXT, pf->flags);

	biपंचांगap_copy(orig_flags, pf->flags, ICE_PF_FLAGS_NBITS);
	क्रम (i = 0; i < ICE_PRIV_FLAG_ARRAY_SIZE; i++) अणु
		स्थिर काष्ठा ice_priv_flag *priv_flag;

		priv_flag = &ice_gstrings_priv_flags[i];

		अगर (flags & BIT(i))
			set_bit(priv_flag->bitno, pf->flags);
		अन्यथा
			clear_bit(priv_flag->bitno, pf->flags);
	पूर्ण

	biपंचांगap_xor(change_flags, pf->flags, orig_flags, ICE_PF_FLAGS_NBITS);

	/* Do not allow change to link-करोwn-on-बंद when Total Port Shutकरोwn
	 * is enabled.
	 */
	अगर (test_bit(ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA, change_flags) &&
	    test_bit(ICE_FLAG_TOTAL_PORT_SHUTDOWN_ENA, pf->flags)) अणु
		dev_err(dev, "Setting link-down-on-close not supported on this port\n");
		set_bit(ICE_FLAG_LINK_DOWN_ON_CLOSE_ENA, pf->flags);
		ret = -EINVAL;
		जाओ ethtool_निकास;
	पूर्ण

	अगर (test_bit(ICE_FLAG_FW_LLDP_AGENT, change_flags)) अणु
		अगर (!test_bit(ICE_FLAG_FW_LLDP_AGENT, pf->flags)) अणु
			क्रमागत ice_status status;

			/* Disable FW LLDP engine */
			status = ice_cfg_lldp_mib_change(&pf->hw, false);

			/* If unरेजिस्टरing क्रम LLDP events fails, this is
			 * not an error state, as there shouldn't be any
			 * events to respond to.
			 */
			अगर (status)
				dev_info(dev, "Failed to unreg for LLDP events\n");

			/* The AQ call to stop the FW LLDP agent will generate
			 * an error अगर the agent is alपढ़ोy stopped.
			 */
			status = ice_aq_stop_lldp(&pf->hw, true, true, शून्य);
			अगर (status)
				dev_warn(dev, "Fail to stop LLDP agent\n");
			/* Use हाल क्रम having the FW LLDP agent stopped
			 * will likely not need DCB, so failure to init is
			 * not a concern of ethtool
			 */
			status = ice_init_pf_dcb(pf, true);
			अगर (status)
				dev_warn(dev, "Fail to init DCB\n");

			pf->dcbx_cap &= ~DCB_CAP_DCBX_LLD_MANAGED;
			pf->dcbx_cap |= DCB_CAP_DCBX_HOST;
		पूर्ण अन्यथा अणु
			क्रमागत ice_status status;
			bool dcbx_agent_status;

			/* Remove rule to direct LLDP packets to शेष VSI.
			 * The FW LLDP engine will now be consuming them.
			 */
			ice_cfg_sw_lldp(vsi, false, false);

			/* AQ command to start FW LLDP agent will वापस an
			 * error अगर the agent is alपढ़ोy started
			 */
			status = ice_aq_start_lldp(&pf->hw, true, शून्य);
			अगर (status)
				dev_warn(dev, "Fail to start LLDP Agent\n");

			/* AQ command to start FW DCBX agent will fail अगर
			 * the agent is alपढ़ोy started
			 */
			status = ice_aq_start_stop_dcbx(&pf->hw, true,
							&dcbx_agent_status,
							शून्य);
			अगर (status)
				dev_dbg(dev, "Failed to start FW DCBX\n");

			dev_info(dev, "FW DCBX agent is %s\n",
				 dcbx_agent_status ? "ACTIVE" : "DISABLED");

			/* Failure to configure MIB change or init DCB is not
			 * relevant to ethtool.  Prपूर्णांक notअगरication that
			 * registration/init failed but करो not वापस error
			 * state to ethtool
			 */
			status = ice_init_pf_dcb(pf, true);
			अगर (status)
				dev_dbg(dev, "Fail to init DCB\n");

			/* Register क्रम MIB change events */
			status = ice_cfg_lldp_mib_change(&pf->hw, true);
			अगर (status)
				dev_dbg(dev, "Fail to enable MIB change events\n");

			pf->dcbx_cap &= ~DCB_CAP_DCBX_HOST;
			pf->dcbx_cap |= DCB_CAP_DCBX_LLD_MANAGED;

			ice_nway_reset(netdev);
		पूर्ण
	पूर्ण
	अगर (test_bit(ICE_FLAG_LEGACY_RX, change_flags)) अणु
		/* करोwn and up VSI so that changes of Rx cfg are reflected. */
		ice_करोwn(vsi);
		ice_up(vsi);
	पूर्ण
	/* करोn't allow modअगरication of this flag when a single VF is in
	 * promiscuous mode because it's not supported
	 */
	अगर (test_bit(ICE_FLAG_VF_TRUE_PROMISC_ENA, change_flags) &&
	    ice_is_any_vf_in_promisc(pf)) अणु
		dev_err(dev, "Changing vf-true-promisc-support flag while VF(s) are in promiscuous mode not supported\n");
		/* toggle bit back to previous state */
		change_bit(ICE_FLAG_VF_TRUE_PROMISC_ENA, pf->flags);
		ret = -EAGAIN;
	पूर्ण
ethtool_निकास:
	clear_bit(ICE_FLAG_ETHTOOL_CTXT, pf->flags);
	वापस ret;
पूर्ण

अटल पूर्णांक ice_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		/* The number (and order) of strings reported *must* reमुख्य
		 * स्थिरant क्रम a given netdevice. This function must not
		 * report a dअगरferent number based on run समय parameters
		 * (such as the number of queues in use, or the setting of
		 * a निजी ethtool flag). This is due to the nature of the
		 * ethtool stats API.
		 *
		 * Userspace programs such as ethtool must make 3 separate
		 * ioctl requests, one क्रम size, one क्रम the strings, and
		 * finally one क्रम the stats. Since these cross पूर्णांकo
		 * userspace, changes to the number or size could result in
		 * undefined memory access or incorrect string<->value
		 * correlations क्रम statistics.
		 *
		 * Even अगर it appears to be safe, changes to the size or
		 * order of strings will suffer from race conditions and are
		 * not safe.
		 */
		वापस ICE_ALL_STATS_LEN(netdev);
	हाल ETH_SS_TEST:
		वापस ICE_TEST_LEN;
	हाल ETH_SS_PRIV_FLAGS:
		वापस ICE_PRIV_FLAG_ARRAY_SIZE;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम
ice_get_ethtool_stats(काष्ठा net_device *netdev,
		      काष्ठा ethtool_stats __always_unused *stats, u64 *data)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_ring *ring;
	अचिन्हित पूर्णांक j;
	पूर्णांक i = 0;
	अक्षर *p;

	ice_update_pf_stats(pf);
	ice_update_vsi_stats(vsi);

	क्रम (j = 0; j < ICE_VSI_STATS_LEN; j++) अणु
		p = (अक्षर *)vsi + ice_gstrings_vsi_stats[j].stat_offset;
		data[i++] = (ice_gstrings_vsi_stats[j].माप_stat ==
			     माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण

	/* populate per queue stats */
	rcu_पढ़ो_lock();

	ice_क्रम_each_alloc_txq(vsi, j) अणु
		ring = READ_ONCE(vsi->tx_rings[j]);
		अगर (ring) अणु
			data[i++] = ring->stats.pkts;
			data[i++] = ring->stats.bytes;
		पूर्ण अन्यथा अणु
			data[i++] = 0;
			data[i++] = 0;
		पूर्ण
	पूर्ण

	ice_क्रम_each_alloc_rxq(vsi, j) अणु
		ring = READ_ONCE(vsi->rx_rings[j]);
		अगर (ring) अणु
			data[i++] = ring->stats.pkts;
			data[i++] = ring->stats.bytes;
		पूर्ण अन्यथा अणु
			data[i++] = 0;
			data[i++] = 0;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	अगर (vsi->type != ICE_VSI_PF)
		वापस;

	क्रम (j = 0; j < ICE_PF_STATS_LEN; j++) अणु
		p = (अक्षर *)pf + ice_gstrings_pf_stats[j].stat_offset;
		data[i++] = (ice_gstrings_pf_stats[j].माप_stat ==
			     माप(u64)) ? *(u64 *)p : *(u32 *)p;
	पूर्ण

	क्रम (j = 0; j < ICE_MAX_USER_PRIORITY; j++) अणु
		data[i++] = pf->stats.priority_xon_tx[j];
		data[i++] = pf->stats.priority_xoff_tx[j];
	पूर्ण

	क्रम (j = 0; j < ICE_MAX_USER_PRIORITY; j++) अणु
		data[i++] = pf->stats.priority_xon_rx[j];
		data[i++] = pf->stats.priority_xoff_rx[j];
	पूर्ण
पूर्ण

#घोषणा ICE_PHY_TYPE_LOW_MASK_MIN_1G	(ICE_PHY_TYPE_LOW_100BASE_TX | \
					 ICE_PHY_TYPE_LOW_100M_SGMII)

#घोषणा ICE_PHY_TYPE_LOW_MASK_MIN_25G	(ICE_PHY_TYPE_LOW_MASK_MIN_1G | \
					 ICE_PHY_TYPE_LOW_1000BASE_T | \
					 ICE_PHY_TYPE_LOW_1000BASE_SX | \
					 ICE_PHY_TYPE_LOW_1000BASE_LX | \
					 ICE_PHY_TYPE_LOW_1000BASE_KX | \
					 ICE_PHY_TYPE_LOW_1G_SGMII | \
					 ICE_PHY_TYPE_LOW_2500BASE_T | \
					 ICE_PHY_TYPE_LOW_2500BASE_X | \
					 ICE_PHY_TYPE_LOW_2500BASE_KX | \
					 ICE_PHY_TYPE_LOW_5GBASE_T | \
					 ICE_PHY_TYPE_LOW_5GBASE_KR | \
					 ICE_PHY_TYPE_LOW_10GBASE_T | \
					 ICE_PHY_TYPE_LOW_10G_SFI_DA | \
					 ICE_PHY_TYPE_LOW_10GBASE_SR | \
					 ICE_PHY_TYPE_LOW_10GBASE_LR | \
					 ICE_PHY_TYPE_LOW_10GBASE_KR_CR1 | \
					 ICE_PHY_TYPE_LOW_10G_SFI_AOC_ACC | \
					 ICE_PHY_TYPE_LOW_10G_SFI_C2C)

#घोषणा ICE_PHY_TYPE_LOW_MASK_100G	(ICE_PHY_TYPE_LOW_100GBASE_CR4 | \
					 ICE_PHY_TYPE_LOW_100GBASE_SR4 | \
					 ICE_PHY_TYPE_LOW_100GBASE_LR4 | \
					 ICE_PHY_TYPE_LOW_100GBASE_KR4 | \
					 ICE_PHY_TYPE_LOW_100G_CAUI4_AOC_ACC | \
					 ICE_PHY_TYPE_LOW_100G_CAUI4 | \
					 ICE_PHY_TYPE_LOW_100G_AUI4_AOC_ACC | \
					 ICE_PHY_TYPE_LOW_100G_AUI4 | \
					 ICE_PHY_TYPE_LOW_100GBASE_CR_PAM4 | \
					 ICE_PHY_TYPE_LOW_100GBASE_KR_PAM4 | \
					 ICE_PHY_TYPE_LOW_100GBASE_CP2 | \
					 ICE_PHY_TYPE_LOW_100GBASE_SR2 | \
					 ICE_PHY_TYPE_LOW_100GBASE_DR)

#घोषणा ICE_PHY_TYPE_HIGH_MASK_100G	(ICE_PHY_TYPE_HIGH_100GBASE_KR2_PAM4 | \
					 ICE_PHY_TYPE_HIGH_100G_CAUI2_AOC_ACC |\
					 ICE_PHY_TYPE_HIGH_100G_CAUI2 | \
					 ICE_PHY_TYPE_HIGH_100G_AUI2_AOC_ACC | \
					 ICE_PHY_TYPE_HIGH_100G_AUI2)

/**
 * ice_mask_min_supported_speeds
 * @phy_types_high: PHY type high
 * @phy_types_low: PHY type low to apply minimum supported speeds mask
 *
 * Apply minimum supported speeds mask to PHY type low. These are the speeds
 * क्रम ethtool supported link mode.
 */
अटल
व्योम ice_mask_min_supported_speeds(u64 phy_types_high, u64 *phy_types_low)
अणु
	/* अगर QSFP connection with 100G speed, minimum supported speed is 25G */
	अगर (*phy_types_low & ICE_PHY_TYPE_LOW_MASK_100G ||
	    phy_types_high & ICE_PHY_TYPE_HIGH_MASK_100G)
		*phy_types_low &= ~ICE_PHY_TYPE_LOW_MASK_MIN_25G;
	अन्यथा
		*phy_types_low &= ~ICE_PHY_TYPE_LOW_MASK_MIN_1G;
पूर्ण

#घोषणा ice_ethtool_advertise_link_mode(aq_link_speed, ethtool_link_mode)    \
	करो अणु								     \
		अगर (req_speeds & (aq_link_speed) ||			     \
		    (!req_speeds &&					     \
		     (advert_phy_type_lo & phy_type_mask_lo ||		     \
		      advert_phy_type_hi & phy_type_mask_hi)))		     \
			ethtool_link_ksettings_add_link_mode(ks, advertising,\
							ethtool_link_mode);  \
	पूर्ण जबतक (0)

/**
 * ice_phy_type_to_ethtool - convert the phy_types to ethtool link modes
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ks: ethtool link ksettings काष्ठा to fill out
 */
अटल व्योम
ice_phy_type_to_ethtool(काष्ठा net_device *netdev,
			काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	u64 advert_phy_type_lo = 0;
	u64 advert_phy_type_hi = 0;
	u64 phy_type_mask_lo = 0;
	u64 phy_type_mask_hi = 0;
	u64 phy_types_high = 0;
	u64 phy_types_low = 0;
	u16 req_speeds;

	req_speeds = vsi->port_info->phy.link_info.req_speeds;

	/* Check अगर lenient mode is supported and enabled, or in strict mode.
	 *
	 * In lenient mode the Supported link modes are the PHY types without
	 * media. The Advertising link mode is either 1. the user requested
	 * speed, 2. the override PHY mask, or 3. the PHY types with media.
	 *
	 * In strict mode Supported link mode are the PHY type with media,
	 * and Advertising link modes are the media PHY type or the speed
	 * requested by user.
	 */
	अगर (test_bit(ICE_FLAG_LINK_LENIENT_MODE_ENA, pf->flags)) अणु
		phy_types_low = le64_to_cpu(pf->nvm_phy_type_lo);
		phy_types_high = le64_to_cpu(pf->nvm_phy_type_hi);

		ice_mask_min_supported_speeds(phy_types_high, &phy_types_low);
		/* determine advertised modes based on link override only
		 * अगर it's supported and if the FW doesn't असलtract the
		 * driver from having to account क्रम link overrides
		 */
		अगर (ice_fw_supports_link_override(&pf->hw) &&
		    !ice_fw_supports_report_dflt_cfg(&pf->hw)) अणु
			काष्ठा ice_link_शेष_override_tlv *lकरो;

			lकरो = &pf->link_dflt_override;
			/* If override enabled and PHY mask set, then
			 * Advertising link mode is the पूर्णांकersection of the PHY
			 * types without media and the override PHY mask.
			 */
			अगर (lकरो->options & ICE_LINK_OVERRIDE_EN &&
			    (lकरो->phy_type_low || lकरो->phy_type_high)) अणु
				advert_phy_type_lo =
					le64_to_cpu(pf->nvm_phy_type_lo) &
					lकरो->phy_type_low;
				advert_phy_type_hi =
					le64_to_cpu(pf->nvm_phy_type_hi) &
					lकरो->phy_type_high;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* strict mode */
		phy_types_low = vsi->port_info->phy.phy_type_low;
		phy_types_high = vsi->port_info->phy.phy_type_high;
	पूर्ण

	/* If Advertising link mode PHY type is not using override PHY type,
	 * then use PHY type with media.
	 */
	अगर (!advert_phy_type_lo && !advert_phy_type_hi) अणु
		advert_phy_type_lo = vsi->port_info->phy.phy_type_low;
		advert_phy_type_hi = vsi->port_info->phy.phy_type_high;
	पूर्ण

	ethtool_link_ksettings_zero_link_mode(ks, supported);
	ethtool_link_ksettings_zero_link_mode(ks, advertising);

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_100BASE_TX |
			   ICE_PHY_TYPE_LOW_100M_SGMII;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100baseT_Full);

		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_100MB,
						100baseT_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_1000BASE_T |
			   ICE_PHY_TYPE_LOW_1G_SGMII;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseT_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_1000MB,
						1000baseT_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_1000BASE_KX;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseKX_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_1000MB,
						1000baseKX_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_1000BASE_SX |
			   ICE_PHY_TYPE_LOW_1000BASE_LX;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     1000baseX_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_1000MB,
						1000baseX_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_2500BASE_T;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     2500baseT_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_2500MB,
						2500baseT_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_2500BASE_X |
			   ICE_PHY_TYPE_LOW_2500BASE_KX;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     2500baseX_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_2500MB,
						2500baseX_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_5GBASE_T |
			   ICE_PHY_TYPE_LOW_5GBASE_KR;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     5000baseT_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_5GB,
						5000baseT_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_10GBASE_T |
			   ICE_PHY_TYPE_LOW_10G_SFI_DA |
			   ICE_PHY_TYPE_LOW_10G_SFI_AOC_ACC |
			   ICE_PHY_TYPE_LOW_10G_SFI_C2C;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseT_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_10GB,
						10000baseT_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_10GBASE_KR_CR1;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseKR_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_10GB,
						10000baseKR_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_10GBASE_SR;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseSR_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_10GB,
						10000baseSR_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_10GBASE_LR;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     10000baseLR_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_10GB,
						10000baseLR_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_25GBASE_T |
			   ICE_PHY_TYPE_LOW_25GBASE_CR |
			   ICE_PHY_TYPE_LOW_25GBASE_CR_S |
			   ICE_PHY_TYPE_LOW_25GBASE_CR1 |
			   ICE_PHY_TYPE_LOW_25G_AUI_AOC_ACC |
			   ICE_PHY_TYPE_LOW_25G_AUI_C2C;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseCR_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_25GB,
						25000baseCR_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_25GBASE_SR |
			   ICE_PHY_TYPE_LOW_25GBASE_LR;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseSR_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_25GB,
						25000baseSR_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_25GBASE_KR |
			   ICE_PHY_TYPE_LOW_25GBASE_KR_S |
			   ICE_PHY_TYPE_LOW_25GBASE_KR1;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     25000baseKR_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_25GB,
						25000baseKR_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_40GBASE_KR4;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseKR4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_40GB,
						40000baseKR4_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_40GBASE_CR4 |
			   ICE_PHY_TYPE_LOW_40G_XLAUI_AOC_ACC |
			   ICE_PHY_TYPE_LOW_40G_XLAUI;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseCR4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_40GB,
						40000baseCR4_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_40GBASE_SR4;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseSR4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_40GB,
						40000baseSR4_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_40GBASE_LR4;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     40000baseLR4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_40GB,
						40000baseLR4_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_50GBASE_CR2 |
			   ICE_PHY_TYPE_LOW_50G_LAUI2_AOC_ACC |
			   ICE_PHY_TYPE_LOW_50G_LAUI2 |
			   ICE_PHY_TYPE_LOW_50G_AUI2_AOC_ACC |
			   ICE_PHY_TYPE_LOW_50G_AUI2 |
			   ICE_PHY_TYPE_LOW_50GBASE_CP |
			   ICE_PHY_TYPE_LOW_50GBASE_SR |
			   ICE_PHY_TYPE_LOW_50G_AUI1_AOC_ACC |
			   ICE_PHY_TYPE_LOW_50G_AUI1;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     50000baseCR2_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_50GB,
						50000baseCR2_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_50GBASE_KR2 |
			   ICE_PHY_TYPE_LOW_50GBASE_KR_PAM4;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     50000baseKR2_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_50GB,
						50000baseKR2_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_50GBASE_SR2 |
			   ICE_PHY_TYPE_LOW_50GBASE_LR2 |
			   ICE_PHY_TYPE_LOW_50GBASE_FR |
			   ICE_PHY_TYPE_LOW_50GBASE_LR;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     50000baseSR2_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_50GB,
						50000baseSR2_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_100GBASE_CR4 |
			   ICE_PHY_TYPE_LOW_100G_CAUI4_AOC_ACC |
			   ICE_PHY_TYPE_LOW_100G_CAUI4 |
			   ICE_PHY_TYPE_LOW_100G_AUI4_AOC_ACC |
			   ICE_PHY_TYPE_LOW_100G_AUI4 |
			   ICE_PHY_TYPE_LOW_100GBASE_CR_PAM4 |
			   ICE_PHY_TYPE_LOW_100GBASE_CP2;
	phy_type_mask_hi = ICE_PHY_TYPE_HIGH_100G_CAUI2_AOC_ACC |
			   ICE_PHY_TYPE_HIGH_100G_CAUI2 |
			   ICE_PHY_TYPE_HIGH_100G_AUI2_AOC_ACC |
			   ICE_PHY_TYPE_HIGH_100G_AUI2;
	अगर (phy_types_low & phy_type_mask_lo ||
	    phy_types_high & phy_type_mask_hi) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseCR4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_100GB,
						100000baseCR4_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_100GBASE_SR4 |
			   ICE_PHY_TYPE_LOW_100GBASE_SR2;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseSR4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_100GB,
						100000baseSR4_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_100GBASE_LR4 |
			   ICE_PHY_TYPE_LOW_100GBASE_DR;
	अगर (phy_types_low & phy_type_mask_lo) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseLR4_ER4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_100GB,
						100000baseLR4_ER4_Full);
	पूर्ण

	phy_type_mask_lo = ICE_PHY_TYPE_LOW_100GBASE_KR4 |
			   ICE_PHY_TYPE_LOW_100GBASE_KR_PAM4;
	phy_type_mask_hi = ICE_PHY_TYPE_HIGH_100GBASE_KR2_PAM4;
	अगर (phy_types_low & phy_type_mask_lo ||
	    phy_types_high & phy_type_mask_hi) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported,
						     100000baseKR4_Full);
		ice_ethtool_advertise_link_mode(ICE_AQ_LINK_SPEED_100GB,
						100000baseKR4_Full);
	पूर्ण
पूर्ण

#घोषणा TEST_SET_BITS_TIMEOUT	50
#घोषणा TEST_SET_BITS_SLEEP_MAX	2000
#घोषणा TEST_SET_BITS_SLEEP_MIN	1000

/**
 * ice_get_settings_link_up - Get Link settings क्रम when link is up
 * @ks: ethtool ksettings to fill in
 * @netdev: network पूर्णांकerface device काष्ठाure
 */
अटल व्योम
ice_get_settings_link_up(काष्ठा ethtool_link_ksettings *ks,
			 काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_port_info *pi = np->vsi->port_info;
	काष्ठा ice_link_status *link_info;
	काष्ठा ice_vsi *vsi = np->vsi;

	link_info = &vsi->port_info->phy.link_info;

	/* Get supported and advertised settings from PHY ability with media */
	ice_phy_type_to_ethtool(netdev, ks);

	चयन (link_info->link_speed) अणु
	हाल ICE_AQ_LINK_SPEED_100GB:
		ks->base.speed = SPEED_100000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_50GB:
		ks->base.speed = SPEED_50000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_40GB:
		ks->base.speed = SPEED_40000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_25GB:
		ks->base.speed = SPEED_25000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_20GB:
		ks->base.speed = SPEED_20000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_10GB:
		ks->base.speed = SPEED_10000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_5GB:
		ks->base.speed = SPEED_5000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_2500MB:
		ks->base.speed = SPEED_2500;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_1000MB:
		ks->base.speed = SPEED_1000;
		अवरोध;
	हाल ICE_AQ_LINK_SPEED_100MB:
		ks->base.speed = SPEED_100;
		अवरोध;
	शेष:
		netdev_info(netdev, "WARNING: Unrecognized link_speed (0x%x).\n",
			    link_info->link_speed);
		अवरोध;
	पूर्ण
	ks->base.duplex = DUPLEX_FULL;

	अगर (link_info->an_info & ICE_AQ_AN_COMPLETED)
		ethtool_link_ksettings_add_link_mode(ks, lp_advertising,
						     Autoneg);

	/* Set flow control negotiated Rx/Tx छोड़ो */
	चयन (pi->fc.current_mode) अणु
	हाल ICE_FC_FULL:
		ethtool_link_ksettings_add_link_mode(ks, lp_advertising, Pause);
		अवरोध;
	हाल ICE_FC_TX_PAUSE:
		ethtool_link_ksettings_add_link_mode(ks, lp_advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ks, lp_advertising,
						     Asym_Pause);
		अवरोध;
	हाल ICE_FC_RX_PAUSE:
		ethtool_link_ksettings_add_link_mode(ks, lp_advertising,
						     Asym_Pause);
		अवरोध;
	हाल ICE_FC_PFC:
	शेष:
		ethtool_link_ksettings_del_link_mode(ks, lp_advertising, Pause);
		ethtool_link_ksettings_del_link_mode(ks, lp_advertising,
						     Asym_Pause);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ice_get_settings_link_करोwn - Get the Link settings when link is करोwn
 * @ks: ethtool ksettings to fill in
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Reports link settings that can be determined when link is करोwn
 */
अटल व्योम
ice_get_settings_link_करोwn(काष्ठा ethtool_link_ksettings *ks,
			   काष्ठा net_device *netdev)
अणु
	/* link is करोwn and the driver needs to fall back on
	 * supported PHY types to figure out what info to display
	 */
	ice_phy_type_to_ethtool(netdev, ks);

	/* With no link, speed and duplex are unknown */
	ks->base.speed = SPEED_UNKNOWN;
	ks->base.duplex = DUPLEX_UNKNOWN;
पूर्ण

/**
 * ice_get_link_ksettings - Get Link Speed and Duplex settings
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ks: ethtool ksettings
 *
 * Reports speed/duplex settings based on media_type
 */
अटल पूर्णांक
ice_get_link_ksettings(काष्ठा net_device *netdev,
		       काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_aqc_get_phy_caps_data *caps;
	काष्ठा ice_link_status *hw_link_info;
	काष्ठा ice_vsi *vsi = np->vsi;
	क्रमागत ice_status status;
	पूर्णांक err = 0;

	ethtool_link_ksettings_zero_link_mode(ks, supported);
	ethtool_link_ksettings_zero_link_mode(ks, advertising);
	ethtool_link_ksettings_zero_link_mode(ks, lp_advertising);
	hw_link_info = &vsi->port_info->phy.link_info;

	/* set speed and duplex */
	अगर (hw_link_info->link_info & ICE_AQ_LINK_UP)
		ice_get_settings_link_up(ks, netdev);
	अन्यथा
		ice_get_settings_link_करोwn(ks, netdev);

	/* set स्वतःneg settings */
	ks->base.स्वतःneg = (hw_link_info->an_info & ICE_AQ_AN_COMPLETED) ?
		AUTONEG_ENABLE : AUTONEG_DISABLE;

	/* set media type settings */
	चयन (vsi->port_info->phy.media_type) अणु
	हाल ICE_MEDIA_FIBER:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ks->base.port = PORT_FIBRE;
		अवरोध;
	हाल ICE_MEDIA_BASET:
		ethtool_link_ksettings_add_link_mode(ks, supported, TP);
		ethtool_link_ksettings_add_link_mode(ks, advertising, TP);
		ks->base.port = PORT_TP;
		अवरोध;
	हाल ICE_MEDIA_BACKPLANE:
		ethtool_link_ksettings_add_link_mode(ks, supported, Backplane);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Backplane);
		ks->base.port = PORT_NONE;
		अवरोध;
	हाल ICE_MEDIA_DA:
		ethtool_link_ksettings_add_link_mode(ks, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(ks, advertising, FIBRE);
		ks->base.port = PORT_DA;
		अवरोध;
	शेष:
		ks->base.port = PORT_OTHER;
		अवरोध;
	पूर्ण

	/* flow control is symmetric and always supported */
	ethtool_link_ksettings_add_link_mode(ks, supported, Pause);

	caps = kzalloc(माप(*caps), GFP_KERNEL);
	अगर (!caps)
		वापस -ENOMEM;

	status = ice_aq_get_phy_caps(vsi->port_info, false,
				     ICE_AQC_REPORT_ACTIVE_CFG, caps, शून्य);
	अगर (status) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	/* Set the advertised flow control based on the PHY capability */
	अगर ((caps->caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE) &&
	    (caps->caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE)) अणु
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
	पूर्ण अन्यथा अगर (caps->caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE) अणु
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
	पूर्ण अन्यथा अगर (caps->caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE) अणु
		ethtool_link_ksettings_add_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     Asym_Pause);
	पूर्ण अन्यथा अणु
		ethtool_link_ksettings_del_link_mode(ks, advertising, Pause);
		ethtool_link_ksettings_del_link_mode(ks, advertising,
						     Asym_Pause);
	पूर्ण

	/* Set advertised FEC modes based on PHY capability */
	ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_NONE);

	अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_REQ)
		ethtool_link_ksettings_add_link_mode(ks, advertising,
						     FEC_BASER);
	अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_528_REQ ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_544_REQ)
		ethtool_link_ksettings_add_link_mode(ks, advertising, FEC_RS);

	status = ice_aq_get_phy_caps(vsi->port_info, false,
				     ICE_AQC_REPORT_TOPO_CAP_MEDIA, caps, शून्य);
	अगर (status) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	/* Set supported FEC modes based on PHY capability */
	ethtool_link_ksettings_add_link_mode(ks, supported, FEC_NONE);

	अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_10G_KR_40G_KR4_EN ||
	    caps->link_fec_options & ICE_AQC_PHY_FEC_25G_KR_CLAUSE74_EN)
		ethtool_link_ksettings_add_link_mode(ks, supported, FEC_BASER);
	अगर (caps->link_fec_options & ICE_AQC_PHY_FEC_25G_RS_CLAUSE91_EN)
		ethtool_link_ksettings_add_link_mode(ks, supported, FEC_RS);

	/* Set supported and advertised स्वतःneg */
	अगर (ice_is_phy_caps_an_enabled(caps)) अणु
		ethtool_link_ksettings_add_link_mode(ks, supported, Autoneg);
		ethtool_link_ksettings_add_link_mode(ks, advertising, Autoneg);
	पूर्ण

करोne:
	kमुक्त(caps);
	वापस err;
पूर्ण

/**
 * ice_ksettings_find_adv_link_speed - Find advertising link speed
 * @ks: ethtool ksettings
 */
अटल u16
ice_ksettings_find_adv_link_speed(स्थिर काष्ठा ethtool_link_ksettings *ks)
अणु
	u16 adv_link_speed = 0;

	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  100baseT_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_100MB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  1000baseX_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_1000MB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  1000baseT_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  1000baseKX_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_1000MB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  2500baseT_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_2500MB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  2500baseX_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_2500MB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  5000baseT_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_5GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseT_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseKR_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_10GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseSR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  10000baseLR_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_10GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  25000baseCR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  25000baseSR_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  25000baseKR_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_25GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseCR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseSR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseLR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  40000baseKR4_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_40GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  50000baseCR2_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  50000baseKR2_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_50GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  50000baseSR2_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_50GB;
	अगर (ethtool_link_ksettings_test_link_mode(ks, advertising,
						  100000baseCR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  100000baseSR4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  100000baseLR4_ER4_Full) ||
	    ethtool_link_ksettings_test_link_mode(ks, advertising,
						  100000baseKR4_Full))
		adv_link_speed |= ICE_AQ_LINK_SPEED_100GB;

	वापस adv_link_speed;
पूर्ण

/**
 * ice_setup_स्वतःneg
 * @p: port info
 * @ks: ethtool_link_ksettings
 * @config: configuration that will be sent करोwn to FW
 * @स्वतःneg_enabled: स्वतःnegotiation is enabled or not
 * @स्वतःneg_changed: will there a change in स्वतःnegotiation
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Setup PHY स्वतःnegotiation feature
 */
अटल पूर्णांक
ice_setup_स्वतःneg(काष्ठा ice_port_info *p, काष्ठा ethtool_link_ksettings *ks,
		  काष्ठा ice_aqc_set_phy_cfg_data *config,
		  u8 स्वतःneg_enabled, u8 *स्वतःneg_changed,
		  काष्ठा net_device *netdev)
अणु
	पूर्णांक err = 0;

	*स्वतःneg_changed = 0;

	/* Check स्वतःneg */
	अगर (स्वतःneg_enabled == AUTONEG_ENABLE) अणु
		/* If स्वतःneg was not alपढ़ोy enabled */
		अगर (!(p->phy.link_info.an_info & ICE_AQ_AN_COMPLETED)) अणु
			/* If स्वतःneg is not supported, वापस error */
			अगर (!ethtool_link_ksettings_test_link_mode(ks,
								   supported,
								   Autoneg)) अणु
				netdev_info(netdev, "Autoneg not supported on this phy.\n");
				err = -EINVAL;
			पूर्ण अन्यथा अणु
				/* Autoneg is allowed to change */
				config->caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;
				*स्वतःneg_changed = 1;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If स्वतःneg is currently enabled */
		अगर (p->phy.link_info.an_info & ICE_AQ_AN_COMPLETED) अणु
			/* If स्वतःneg is supported 10GBASE_T is the only PHY
			 * that can disable it, so otherwise वापस error
			 */
			अगर (ethtool_link_ksettings_test_link_mode(ks,
								  supported,
								  Autoneg)) अणु
				netdev_info(netdev, "Autoneg cannot be disabled on this phy\n");
				err = -EINVAL;
			पूर्ण अन्यथा अणु
				/* Autoneg is allowed to change */
				config->caps &= ~ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;
				*स्वतःneg_changed = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/**
 * ice_set_link_ksettings - Set Speed and Duplex
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ks: ethtool ksettings
 *
 * Set speed/duplex per media_types advertised/क्रमced
 */
अटल पूर्णांक
ice_set_link_ksettings(काष्ठा net_device *netdev,
		       स्थिर काष्ठा ethtool_link_ksettings *ks)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	u8 स्वतःneg, समयout = TEST_SET_BITS_TIMEOUT;
	काष्ठा ethtool_link_ksettings copy_ks = *ks;
	काष्ठा ethtool_link_ksettings safe_ks = अणुपूर्ण;
	काष्ठा ice_aqc_get_phy_caps_data *phy_caps;
	काष्ठा ice_aqc_set_phy_cfg_data config;
	u16 adv_link_speed, curr_link_speed;
	काष्ठा ice_pf *pf = np->vsi->back;
	काष्ठा ice_port_info *pi;
	u8 स्वतःneg_changed = 0;
	क्रमागत ice_status status;
	u64 phy_type_high = 0;
	u64 phy_type_low = 0;
	पूर्णांक err = 0;
	bool linkup;

	pi = np->vsi->port_info;

	अगर (!pi)
		वापस -EIO;

	अगर (pi->phy.media_type != ICE_MEDIA_BASET &&
	    pi->phy.media_type != ICE_MEDIA_FIBER &&
	    pi->phy.media_type != ICE_MEDIA_BACKPLANE &&
	    pi->phy.media_type != ICE_MEDIA_DA &&
	    pi->phy.link_info.link_info & ICE_AQ_LINK_UP)
		वापस -EOPNOTSUPP;

	phy_caps = kzalloc(माप(*phy_caps), GFP_KERNEL);
	अगर (!phy_caps)
		वापस -ENOMEM;

	/* Get the PHY capabilities based on media */
	अगर (ice_fw_supports_report_dflt_cfg(pi->hw))
		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_DFLT_CFG,
					     phy_caps, शून्य);
	अन्यथा
		status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_TOPO_CAP_MEDIA,
					     phy_caps, शून्य);
	अगर (status) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	/* save स्वतःneg out of ksettings */
	स्वतःneg = copy_ks.base.स्वतःneg;

	/* Get link modes supported by hardware.*/
	ice_phy_type_to_ethtool(netdev, &safe_ks);

	/* and check against modes requested by user.
	 * Return an error अगर unsupported mode was set.
	 */
	अगर (!biपंचांगap_subset(copy_ks.link_modes.advertising,
			   safe_ks.link_modes.supported,
			   __ETHTOOL_LINK_MODE_MASK_NBITS)) अणु
		अगर (!test_bit(ICE_FLAG_LINK_LENIENT_MODE_ENA, pf->flags))
			netdev_info(netdev, "The selected speed is not supported by the current media. Please select a link speed that is supported by the current media.\n");
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	/* get our own copy of the bits to check against */
	स_रखो(&safe_ks, 0, माप(safe_ks));
	safe_ks.base.cmd = copy_ks.base.cmd;
	safe_ks.base.link_mode_masks_nwords =
		copy_ks.base.link_mode_masks_nwords;
	ice_get_link_ksettings(netdev, &safe_ks);

	/* set स्वतःneg back to what it currently is */
	copy_ks.base.स्वतःneg = safe_ks.base.स्वतःneg;
	/* we करोn't compare the speed */
	copy_ks.base.speed = safe_ks.base.speed;

	/* If copy_ks.base and safe_ks.base are not the same now, then they are
	 * trying to set something that we करो not support.
	 */
	अगर (स_भेद(&copy_ks.base, &safe_ks.base, माप(copy_ks.base))) अणु
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	जबतक (test_and_set_bit(ICE_CFG_BUSY, pf->state)) अणु
		समयout--;
		अगर (!समयout) अणु
			err = -EBUSY;
			जाओ करोne;
		पूर्ण
		usleep_range(TEST_SET_BITS_SLEEP_MIN, TEST_SET_BITS_SLEEP_MAX);
	पूर्ण

	/* Copy the current user PHY configuration. The current user PHY
	 * configuration is initialized during probe from PHY capabilities
	 * software mode, and updated on set PHY configuration.
	 */
	config = pi->phy.curr_user_phy_cfg;

	config.caps |= ICE_AQ_PHY_ENA_AUTO_LINK_UPDT;

	/* Check स्वतःneg */
	err = ice_setup_स्वतःneg(pi, &safe_ks, &config, स्वतःneg, &स्वतःneg_changed,
				netdev);

	अगर (err)
		जाओ करोne;

	/* Call to get the current link speed */
	pi->phy.get_link_info = true;
	status = ice_get_link_status(pi, &linkup);
	अगर (status) अणु
		err = -EIO;
		जाओ करोne;
	पूर्ण

	curr_link_speed = pi->phy.link_info.link_speed;
	adv_link_speed = ice_ksettings_find_adv_link_speed(ks);

	/* If speed didn't get set, set it to what it currently is.
	 * This is needed because अगर advertise is 0 (as it is when स्वतःneg
	 * is disabled) then speed won't get set.
	 */
	अगर (!adv_link_speed)
		adv_link_speed = curr_link_speed;

	/* Convert the advertise link speeds to their corresponded PHY_TYPE */
	ice_update_phy_type(&phy_type_low, &phy_type_high, adv_link_speed);

	अगर (!स्वतःneg_changed && adv_link_speed == curr_link_speed) अणु
		netdev_info(netdev, "Nothing changed, exiting without setting anything.\n");
		जाओ करोne;
	पूर्ण

	/* save the requested speeds */
	pi->phy.link_info.req_speeds = adv_link_speed;

	/* set link and स्वतः negotiation so changes take effect */
	config.caps |= ICE_AQ_PHY_ENA_LINK;

	/* check अगर there is a PHY type क्रम the requested advertised speed */
	अगर (!(phy_type_low || phy_type_high)) अणु
		netdev_info(netdev, "The selected speed is not supported by the current media. Please select a link speed that is supported by the current media.\n");
		err = -EOPNOTSUPP;
		जाओ करोne;
	पूर्ण

	/* पूर्णांकersect requested advertised speed PHY types with media PHY types
	 * क्रम set PHY configuration
	 */
	config.phy_type_high = cpu_to_le64(phy_type_high) &
			phy_caps->phy_type_high;
	config.phy_type_low = cpu_to_le64(phy_type_low) &
			phy_caps->phy_type_low;

	अगर (!(config.phy_type_high || config.phy_type_low)) अणु
		/* If there is no पूर्णांकersection and lenient mode is enabled, then
		 * पूर्णांकersect the requested advertised speed with NVM media type
		 * PHY types.
		 */
		अगर (test_bit(ICE_FLAG_LINK_LENIENT_MODE_ENA, pf->flags)) अणु
			config.phy_type_high = cpu_to_le64(phy_type_high) &
					       pf->nvm_phy_type_hi;
			config.phy_type_low = cpu_to_le64(phy_type_low) &
					      pf->nvm_phy_type_lo;
		पूर्ण अन्यथा अणु
			netdev_info(netdev, "The selected speed is not supported by the current media. Please select a link speed that is supported by the current media.\n");
			err = -EOPNOTSUPP;
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* If link is up put link करोwn */
	अगर (pi->phy.link_info.link_info & ICE_AQ_LINK_UP) अणु
		/* Tell the OS link is going करोwn, the link will go
		 * back up when fw says it is पढ़ोy asynchronously
		 */
		ice_prपूर्णांक_link_msg(np->vsi, false);
		netअगर_carrier_off(netdev);
		netअगर_tx_stop_all_queues(netdev);
	पूर्ण

	/* make the aq call */
	status = ice_aq_set_phy_cfg(&pf->hw, pi, &config, शून्य);
	अगर (status) अणु
		netdev_info(netdev, "Set phy config failed,\n");
		err = -EIO;
		जाओ करोne;
	पूर्ण

	/* Save speed request */
	pi->phy.curr_user_speed_req = adv_link_speed;
करोne:
	kमुक्त(phy_caps);
	clear_bit(ICE_CFG_BUSY, pf->state);

	वापस err;
पूर्ण

/**
 * ice_parse_hdrs - parses headers from RSS hash input
 * @nfc: ethtool rxnfc command
 *
 * This function parses the rxnfc command and वापसs पूर्णांकended
 * header types क्रम RSS configuration
 */
अटल u32 ice_parse_hdrs(काष्ठा ethtool_rxnfc *nfc)
अणु
	u32 hdrs = ICE_FLOW_SEG_HDR_NONE;

	चयन (nfc->flow_type) अणु
	हाल TCP_V4_FLOW:
		hdrs |= ICE_FLOW_SEG_HDR_TCP | ICE_FLOW_SEG_HDR_IPV4;
		अवरोध;
	हाल UDP_V4_FLOW:
		hdrs |= ICE_FLOW_SEG_HDR_UDP | ICE_FLOW_SEG_HDR_IPV4;
		अवरोध;
	हाल SCTP_V4_FLOW:
		hdrs |= ICE_FLOW_SEG_HDR_SCTP | ICE_FLOW_SEG_HDR_IPV4;
		अवरोध;
	हाल TCP_V6_FLOW:
		hdrs |= ICE_FLOW_SEG_HDR_TCP | ICE_FLOW_SEG_HDR_IPV6;
		अवरोध;
	हाल UDP_V6_FLOW:
		hdrs |= ICE_FLOW_SEG_HDR_UDP | ICE_FLOW_SEG_HDR_IPV6;
		अवरोध;
	हाल SCTP_V6_FLOW:
		hdrs |= ICE_FLOW_SEG_HDR_SCTP | ICE_FLOW_SEG_HDR_IPV6;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस hdrs;
पूर्ण

#घोषणा ICE_FLOW_HASH_FLD_IPV4_SA	BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_SA)
#घोषणा ICE_FLOW_HASH_FLD_IPV6_SA	BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_SA)
#घोषणा ICE_FLOW_HASH_FLD_IPV4_DA	BIT_ULL(ICE_FLOW_FIELD_IDX_IPV4_DA)
#घोषणा ICE_FLOW_HASH_FLD_IPV6_DA	BIT_ULL(ICE_FLOW_FIELD_IDX_IPV6_DA)
#घोषणा ICE_FLOW_HASH_FLD_TCP_SRC_PORT	BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_SRC_PORT)
#घोषणा ICE_FLOW_HASH_FLD_TCP_DST_PORT	BIT_ULL(ICE_FLOW_FIELD_IDX_TCP_DST_PORT)
#घोषणा ICE_FLOW_HASH_FLD_UDP_SRC_PORT	BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_SRC_PORT)
#घोषणा ICE_FLOW_HASH_FLD_UDP_DST_PORT	BIT_ULL(ICE_FLOW_FIELD_IDX_UDP_DST_PORT)
#घोषणा ICE_FLOW_HASH_FLD_SCTP_SRC_PORT	\
	BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_SRC_PORT)
#घोषणा ICE_FLOW_HASH_FLD_SCTP_DST_PORT	\
	BIT_ULL(ICE_FLOW_FIELD_IDX_SCTP_DST_PORT)

/**
 * ice_parse_hash_flds - parses hash fields from RSS hash input
 * @nfc: ethtool rxnfc command
 *
 * This function parses the rxnfc command and वापसs पूर्णांकended
 * hash fields क्रम RSS configuration
 */
अटल u64 ice_parse_hash_flds(काष्ठा ethtool_rxnfc *nfc)
अणु
	u64 hfld = ICE_HASH_INVALID;

	अगर (nfc->data & RXH_IP_SRC || nfc->data & RXH_IP_DST) अणु
		चयन (nfc->flow_type) अणु
		हाल TCP_V4_FLOW:
		हाल UDP_V4_FLOW:
		हाल SCTP_V4_FLOW:
			अगर (nfc->data & RXH_IP_SRC)
				hfld |= ICE_FLOW_HASH_FLD_IPV4_SA;
			अगर (nfc->data & RXH_IP_DST)
				hfld |= ICE_FLOW_HASH_FLD_IPV4_DA;
			अवरोध;
		हाल TCP_V6_FLOW:
		हाल UDP_V6_FLOW:
		हाल SCTP_V6_FLOW:
			अगर (nfc->data & RXH_IP_SRC)
				hfld |= ICE_FLOW_HASH_FLD_IPV6_SA;
			अगर (nfc->data & RXH_IP_DST)
				hfld |= ICE_FLOW_HASH_FLD_IPV6_DA;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (nfc->data & RXH_L4_B_0_1 || nfc->data & RXH_L4_B_2_3) अणु
		चयन (nfc->flow_type) अणु
		हाल TCP_V4_FLOW:
		हाल TCP_V6_FLOW:
			अगर (nfc->data & RXH_L4_B_0_1)
				hfld |= ICE_FLOW_HASH_FLD_TCP_SRC_PORT;
			अगर (nfc->data & RXH_L4_B_2_3)
				hfld |= ICE_FLOW_HASH_FLD_TCP_DST_PORT;
			अवरोध;
		हाल UDP_V4_FLOW:
		हाल UDP_V6_FLOW:
			अगर (nfc->data & RXH_L4_B_0_1)
				hfld |= ICE_FLOW_HASH_FLD_UDP_SRC_PORT;
			अगर (nfc->data & RXH_L4_B_2_3)
				hfld |= ICE_FLOW_HASH_FLD_UDP_DST_PORT;
			अवरोध;
		हाल SCTP_V4_FLOW:
		हाल SCTP_V6_FLOW:
			अगर (nfc->data & RXH_L4_B_0_1)
				hfld |= ICE_FLOW_HASH_FLD_SCTP_SRC_PORT;
			अगर (nfc->data & RXH_L4_B_2_3)
				hfld |= ICE_FLOW_HASH_FLD_SCTP_DST_PORT;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस hfld;
पूर्ण

/**
 * ice_set_rss_hash_opt - Enable/Disable flow types क्रम RSS hash
 * @vsi: the VSI being configured
 * @nfc: ethtool rxnfc command
 *
 * Returns Success अगर the flow input set is supported.
 */
अटल पूर्णांक
ice_set_rss_hash_opt(काष्ठा ice_vsi *vsi, काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_status status;
	काष्ठा device *dev;
	u64 hashed_flds;
	u32 hdrs;

	dev = ice_pf_to_dev(pf);
	अगर (ice_is_safe_mode(pf)) अणु
		dev_dbg(dev, "Advanced RSS disabled. Package download failed, vsi num = %d\n",
			vsi->vsi_num);
		वापस -EINVAL;
	पूर्ण

	hashed_flds = ice_parse_hash_flds(nfc);
	अगर (hashed_flds == ICE_HASH_INVALID) अणु
		dev_dbg(dev, "Invalid hash fields, vsi num = %d\n",
			vsi->vsi_num);
		वापस -EINVAL;
	पूर्ण

	hdrs = ice_parse_hdrs(nfc);
	अगर (hdrs == ICE_FLOW_SEG_HDR_NONE) अणु
		dev_dbg(dev, "Header type is not valid, vsi num = %d\n",
			vsi->vsi_num);
		वापस -EINVAL;
	पूर्ण

	status = ice_add_rss_cfg(&pf->hw, vsi->idx, hashed_flds, hdrs);
	अगर (status) अणु
		dev_dbg(dev, "ice_add_rss_cfg failed, vsi num = %d, error = %s\n",
			vsi->vsi_num, ice_stat_str(status));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_get_rss_hash_opt - Retrieve hash fields क्रम a given flow-type
 * @vsi: the VSI being configured
 * @nfc: ethtool rxnfc command
 */
अटल व्योम
ice_get_rss_hash_opt(काष्ठा ice_vsi *vsi, काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	u64 hash_flds;
	u32 hdrs;

	dev = ice_pf_to_dev(pf);

	nfc->data = 0;
	अगर (ice_is_safe_mode(pf)) अणु
		dev_dbg(dev, "Advanced RSS disabled. Package download failed, vsi num = %d\n",
			vsi->vsi_num);
		वापस;
	पूर्ण

	hdrs = ice_parse_hdrs(nfc);
	अगर (hdrs == ICE_FLOW_SEG_HDR_NONE) अणु
		dev_dbg(dev, "Header type is not valid, vsi num = %d\n",
			vsi->vsi_num);
		वापस;
	पूर्ण

	hash_flds = ice_get_rss_cfg(&pf->hw, vsi->idx, hdrs);
	अगर (hash_flds == ICE_HASH_INVALID) अणु
		dev_dbg(dev, "No hash fields found for the given header type, vsi num = %d\n",
			vsi->vsi_num);
		वापस;
	पूर्ण

	अगर (hash_flds & ICE_FLOW_HASH_FLD_IPV4_SA ||
	    hash_flds & ICE_FLOW_HASH_FLD_IPV6_SA)
		nfc->data |= (u64)RXH_IP_SRC;

	अगर (hash_flds & ICE_FLOW_HASH_FLD_IPV4_DA ||
	    hash_flds & ICE_FLOW_HASH_FLD_IPV6_DA)
		nfc->data |= (u64)RXH_IP_DST;

	अगर (hash_flds & ICE_FLOW_HASH_FLD_TCP_SRC_PORT ||
	    hash_flds & ICE_FLOW_HASH_FLD_UDP_SRC_PORT ||
	    hash_flds & ICE_FLOW_HASH_FLD_SCTP_SRC_PORT)
		nfc->data |= (u64)RXH_L4_B_0_1;

	अगर (hash_flds & ICE_FLOW_HASH_FLD_TCP_DST_PORT ||
	    hash_flds & ICE_FLOW_HASH_FLD_UDP_DST_PORT ||
	    hash_flds & ICE_FLOW_HASH_FLD_SCTP_DST_PORT)
		nfc->data |= (u64)RXH_L4_B_2_3;
पूर्ण

/**
 * ice_set_rxnfc - command to set Rx flow rules.
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @cmd: ethtool rxnfc command
 *
 * Returns 0 क्रम success and negative values क्रम errors
 */
अटल पूर्णांक ice_set_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		वापस ice_add_fdir_ethtool(vsi, cmd);
	हाल ETHTOOL_SRXCLSRLDEL:
		वापस ice_del_fdir_ethtool(vsi, cmd);
	हाल ETHTOOL_SRXFH:
		वापस ice_set_rss_hash_opt(vsi, cmd);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

/**
 * ice_get_rxnfc - command to get Rx flow classअगरication rules
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @cmd: ethtool rxnfc command
 * @rule_locs: buffer to rturn Rx flow classअगरication rules
 *
 * Returns Success अगर the command is supported.
 */
अटल पूर्णांक
ice_get_rxnfc(काष्ठा net_device *netdev, काष्ठा ethtool_rxnfc *cmd,
	      u32 __always_unused *rule_locs)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	पूर्णांक ret = -EOPNOTSUPP;
	काष्ठा ice_hw *hw;

	hw = &vsi->back->hw;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		cmd->data = vsi->rss_size;
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		cmd->rule_cnt = hw->fdir_active_fltr;
		/* report total rule count */
		cmd->data = ice_get_fdir_cnt_all(hw);
		ret = 0;
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		ret = ice_get_ethtool_fdir_entry(hw, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		ret = ice_get_fdir_fltr_ids(hw, cmd, (u32 *)rule_locs);
		अवरोध;
	हाल ETHTOOL_GRXFH:
		ice_get_rss_hash_opt(vsi, cmd);
		ret = 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
ice_get_ringparam(काष्ठा net_device *netdev, काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;

	ring->rx_max_pending = ICE_MAX_NUM_DESC;
	ring->tx_max_pending = ICE_MAX_NUM_DESC;
	ring->rx_pending = vsi->rx_rings[0]->count;
	ring->tx_pending = vsi->tx_rings[0]->count;

	/* Rx mini and jumbo rings are not supported */
	ring->rx_mini_max_pending = 0;
	ring->rx_jumbo_max_pending = 0;
	ring->rx_mini_pending = 0;
	ring->rx_jumbo_pending = 0;
पूर्ण

अटल पूर्णांक
ice_set_ringparam(काष्ठा net_device *netdev, काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा ice_ring *tx_rings = शून्य, *rx_rings = शून्य;
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_ring *xdp_rings = शून्य;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक i, समयout = 50, err = 0;
	u16 new_rx_cnt, new_tx_cnt;

	अगर (ring->tx_pending > ICE_MAX_NUM_DESC ||
	    ring->tx_pending < ICE_MIN_NUM_DESC ||
	    ring->rx_pending > ICE_MAX_NUM_DESC ||
	    ring->rx_pending < ICE_MIN_NUM_DESC) अणु
		netdev_err(netdev, "Descriptors requested (Tx: %d / Rx: %d) out of range [%d-%d] (increment %d)\n",
			   ring->tx_pending, ring->rx_pending,
			   ICE_MIN_NUM_DESC, ICE_MAX_NUM_DESC,
			   ICE_REQ_DESC_MULTIPLE);
		वापस -EINVAL;
	पूर्ण

	new_tx_cnt = ALIGN(ring->tx_pending, ICE_REQ_DESC_MULTIPLE);
	अगर (new_tx_cnt != ring->tx_pending)
		netdev_info(netdev, "Requested Tx descriptor count rounded up to %d\n",
			    new_tx_cnt);
	new_rx_cnt = ALIGN(ring->rx_pending, ICE_REQ_DESC_MULTIPLE);
	अगर (new_rx_cnt != ring->rx_pending)
		netdev_info(netdev, "Requested Rx descriptor count rounded up to %d\n",
			    new_rx_cnt);

	/* अगर nothing to करो वापस success */
	अगर (new_tx_cnt == vsi->tx_rings[0]->count &&
	    new_rx_cnt == vsi->rx_rings[0]->count) अणु
		netdev_dbg(netdev, "Nothing to change, descriptor count is same as requested\n");
		वापस 0;
	पूर्ण

	/* If there is a AF_XDP UMEM attached to any of Rx rings,
	 * disallow changing the number of descriptors -- regardless
	 * अगर the netdev is running or not.
	 */
	अगर (ice_xsk_any_rx_ring_ena(vsi))
		वापस -EBUSY;

	जबतक (test_and_set_bit(ICE_CFG_BUSY, pf->state)) अणु
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
		usleep_range(1000, 2000);
	पूर्ण

	/* set क्रम the next समय the netdev is started */
	अगर (!netअगर_running(vsi->netdev)) अणु
		क्रम (i = 0; i < vsi->alloc_txq; i++)
			vsi->tx_rings[i]->count = new_tx_cnt;
		क्रम (i = 0; i < vsi->alloc_rxq; i++)
			vsi->rx_rings[i]->count = new_rx_cnt;
		अगर (ice_is_xdp_ena_vsi(vsi))
			क्रम (i = 0; i < vsi->num_xdp_txq; i++)
				vsi->xdp_rings[i]->count = new_tx_cnt;
		vsi->num_tx_desc = (u16)new_tx_cnt;
		vsi->num_rx_desc = (u16)new_rx_cnt;
		netdev_dbg(netdev, "Link is down, descriptor count change happens when link is brought up\n");
		जाओ करोne;
	पूर्ण

	अगर (new_tx_cnt == vsi->tx_rings[0]->count)
		जाओ process_rx;

	/* alloc updated Tx resources */
	netdev_info(netdev, "Changing Tx descriptor count from %d to %d\n",
		    vsi->tx_rings[0]->count, new_tx_cnt);

	tx_rings = kसुस्मृति(vsi->num_txq, माप(*tx_rings), GFP_KERNEL);
	अगर (!tx_rings) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	ice_क्रम_each_txq(vsi, i) अणु
		/* clone ring and setup updated count */
		tx_rings[i] = *vsi->tx_rings[i];
		tx_rings[i].count = new_tx_cnt;
		tx_rings[i].desc = शून्य;
		tx_rings[i].tx_buf = शून्य;
		err = ice_setup_tx_ring(&tx_rings[i]);
		अगर (err) अणु
			जबतक (i--)
				ice_clean_tx_ring(&tx_rings[i]);
			kमुक्त(tx_rings);
			जाओ करोne;
		पूर्ण
	पूर्ण

	अगर (!ice_is_xdp_ena_vsi(vsi))
		जाओ process_rx;

	/* alloc updated XDP resources */
	netdev_info(netdev, "Changing XDP descriptor count from %d to %d\n",
		    vsi->xdp_rings[0]->count, new_tx_cnt);

	xdp_rings = kसुस्मृति(vsi->num_xdp_txq, माप(*xdp_rings), GFP_KERNEL);
	अगर (!xdp_rings) अणु
		err = -ENOMEM;
		जाओ मुक्त_tx;
	पूर्ण

	क्रम (i = 0; i < vsi->num_xdp_txq; i++) अणु
		/* clone ring and setup updated count */
		xdp_rings[i] = *vsi->xdp_rings[i];
		xdp_rings[i].count = new_tx_cnt;
		xdp_rings[i].desc = शून्य;
		xdp_rings[i].tx_buf = शून्य;
		err = ice_setup_tx_ring(&xdp_rings[i]);
		अगर (err) अणु
			जबतक (i--)
				ice_clean_tx_ring(&xdp_rings[i]);
			kमुक्त(xdp_rings);
			जाओ मुक्त_tx;
		पूर्ण
		ice_set_ring_xdp(&xdp_rings[i]);
	पूर्ण

process_rx:
	अगर (new_rx_cnt == vsi->rx_rings[0]->count)
		जाओ process_link;

	/* alloc updated Rx resources */
	netdev_info(netdev, "Changing Rx descriptor count from %d to %d\n",
		    vsi->rx_rings[0]->count, new_rx_cnt);

	rx_rings = kसुस्मृति(vsi->num_rxq, माप(*rx_rings), GFP_KERNEL);
	अगर (!rx_rings) अणु
		err = -ENOMEM;
		जाओ करोne;
	पूर्ण

	ice_क्रम_each_rxq(vsi, i) अणु
		/* clone ring and setup updated count */
		rx_rings[i] = *vsi->rx_rings[i];
		rx_rings[i].count = new_rx_cnt;
		rx_rings[i].desc = शून्य;
		rx_rings[i].rx_buf = शून्य;
		/* this is to allow wr32 to have something to ग_लिखो to
		 * during early allocation of Rx buffers
		 */
		rx_rings[i].tail = vsi->back->hw.hw_addr + PRTGEN_STATUS;

		err = ice_setup_rx_ring(&rx_rings[i]);
		अगर (err)
			जाओ rx_unwind;

		/* allocate Rx buffers */
		err = ice_alloc_rx_bufs(&rx_rings[i],
					ICE_DESC_UNUSED(&rx_rings[i]));
rx_unwind:
		अगर (err) अणु
			जबतक (i) अणु
				i--;
				ice_मुक्त_rx_ring(&rx_rings[i]);
			पूर्ण
			kमुक्त(rx_rings);
			err = -ENOMEM;
			जाओ मुक्त_tx;
		पूर्ण
	पूर्ण

process_link:
	/* Bring पूर्णांकerface करोwn, copy in the new ring info, then restore the
	 * पूर्णांकerface. अगर VSI is up, bring it करोwn and then back up
	 */
	अगर (!test_and_set_bit(ICE_VSI_DOWN, vsi->state)) अणु
		ice_करोwn(vsi);

		अगर (tx_rings) अणु
			ice_क्रम_each_txq(vsi, i) अणु
				ice_मुक्त_tx_ring(vsi->tx_rings[i]);
				*vsi->tx_rings[i] = tx_rings[i];
			पूर्ण
			kमुक्त(tx_rings);
		पूर्ण

		अगर (rx_rings) अणु
			ice_क्रम_each_rxq(vsi, i) अणु
				ice_मुक्त_rx_ring(vsi->rx_rings[i]);
				/* copy the real tail offset */
				rx_rings[i].tail = vsi->rx_rings[i]->tail;
				/* this is to fake out the allocation routine
				 * पूर्णांकo thinking it has to पुनः_स्मृति everything
				 * but the recycling logic will let us re-use
				 * the buffers allocated above
				 */
				rx_rings[i].next_to_use = 0;
				rx_rings[i].next_to_clean = 0;
				rx_rings[i].next_to_alloc = 0;
				*vsi->rx_rings[i] = rx_rings[i];
			पूर्ण
			kमुक्त(rx_rings);
		पूर्ण

		अगर (xdp_rings) अणु
			क्रम (i = 0; i < vsi->num_xdp_txq; i++) अणु
				ice_मुक्त_tx_ring(vsi->xdp_rings[i]);
				*vsi->xdp_rings[i] = xdp_rings[i];
			पूर्ण
			kमुक्त(xdp_rings);
		पूर्ण

		vsi->num_tx_desc = new_tx_cnt;
		vsi->num_rx_desc = new_rx_cnt;
		ice_up(vsi);
	पूर्ण
	जाओ करोne;

मुक्त_tx:
	/* error cleanup अगर the Rx allocations failed after getting Tx */
	अगर (tx_rings) अणु
		ice_क्रम_each_txq(vsi, i)
			ice_मुक्त_tx_ring(&tx_rings[i]);
		kमुक्त(tx_rings);
	पूर्ण

करोne:
	clear_bit(ICE_CFG_BUSY, pf->state);
	वापस err;
पूर्ण

/**
 * ice_get_छोड़ोparam - Get Flow Control status
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @छोड़ो: ethernet छोड़ो (flow control) parameters
 *
 * Get requested flow control status from PHY capability.
 * If स्वतःneg is true, then ethtool will send the ETHTOOL_GSET ioctl which
 * is handled by ice_get_link_ksettings. ice_get_link_ksettings will report
 * the negotiated Rx/Tx छोड़ो via lp_advertising.
 */
अटल व्योम
ice_get_छोड़ोparam(काष्ठा net_device *netdev, काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_port_info *pi = np->vsi->port_info;
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	काष्ठा ice_dcbx_cfg *dcbx_cfg;
	क्रमागत ice_status status;

	/* Initialize छोड़ो params */
	छोड़ो->rx_छोड़ो = 0;
	छोड़ो->tx_छोड़ो = 0;

	dcbx_cfg = &pi->qos_cfg.local_dcbx_cfg;

	pcaps = kzalloc(माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस;

	/* Get current PHY config */
	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_ACTIVE_CFG, pcaps,
				     शून्य);
	अगर (status)
		जाओ out;

	छोड़ो->स्वतःneg = ice_is_phy_caps_an_enabled(pcaps) ? AUTONEG_ENABLE :
							     AUTONEG_DISABLE;

	अगर (dcbx_cfg->pfc.pfcena)
		/* PFC enabled so report LFC as off */
		जाओ out;

	अगर (pcaps->caps & ICE_AQC_PHY_EN_TX_LINK_PAUSE)
		छोड़ो->tx_छोड़ो = 1;
	अगर (pcaps->caps & ICE_AQC_PHY_EN_RX_LINK_PAUSE)
		छोड़ो->rx_छोड़ो = 1;

out:
	kमुक्त(pcaps);
पूर्ण

/**
 * ice_set_छोड़ोparam - Set Flow Control parameter
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @छोड़ो: वापस Tx/Rx flow control status
 */
अटल पूर्णांक
ice_set_छोड़ोparam(काष्ठा net_device *netdev, काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_aqc_get_phy_caps_data *pcaps;
	काष्ठा ice_link_status *hw_link_info;
	काष्ठा ice_pf *pf = np->vsi->back;
	काष्ठा ice_dcbx_cfg *dcbx_cfg;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_port_info *pi;
	क्रमागत ice_status status;
	u8 aq_failures;
	bool link_up;
	पूर्णांक err = 0;
	u32 is_an;

	pi = vsi->port_info;
	hw_link_info = &pi->phy.link_info;
	dcbx_cfg = &pi->qos_cfg.local_dcbx_cfg;
	link_up = hw_link_info->link_info & ICE_AQ_LINK_UP;

	/* Changing the port's flow control is not supported if this isn't the
	 * PF VSI
	 */
	अगर (vsi->type != ICE_VSI_PF) अणु
		netdev_info(netdev, "Changing flow control parameters only supported for PF VSI\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Get छोड़ो param reports configured and negotiated flow control छोड़ो
	 * when ETHTOOL_GLINKSETTINGS is defined. Since ETHTOOL_GLINKSETTINGS is
	 * defined get छोड़ो param छोड़ो->स्वतःneg reports SW configured setting,
	 * so compare छोड़ो->स्वतःneg with SW configured to prevent the user from
	 * using set छोड़ो param to chance स्वतःneg.
	 */
	pcaps = kzalloc(माप(*pcaps), GFP_KERNEL);
	अगर (!pcaps)
		वापस -ENOMEM;

	/* Get current PHY config */
	status = ice_aq_get_phy_caps(pi, false, ICE_AQC_REPORT_ACTIVE_CFG, pcaps,
				     शून्य);
	अगर (status) अणु
		kमुक्त(pcaps);
		वापस -EIO;
	पूर्ण

	is_an = ice_is_phy_caps_an_enabled(pcaps) ? AUTONEG_ENABLE :
						    AUTONEG_DISABLE;

	kमुक्त(pcaps);

	अगर (छोड़ो->स्वतःneg != is_an) अणु
		netdev_info(netdev, "To change autoneg please use: ethtool -s <dev> autoneg <on|off>\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* If we have link and करोn't have स्वतःneg */
	अगर (!test_bit(ICE_DOWN, pf->state) &&
	    !(hw_link_info->an_info & ICE_AQ_AN_COMPLETED)) अणु
		/* Send message that it might not necessarily work*/
		netdev_info(netdev, "Autoneg did not complete so changing settings may not result in an actual change.\n");
	पूर्ण

	अगर (dcbx_cfg->pfc.pfcena) अणु
		netdev_info(netdev, "Priority flow control enabled. Cannot set link flow control.\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		pi->fc.req_mode = ICE_FC_FULL;
	अन्यथा अगर (छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		pi->fc.req_mode = ICE_FC_RX_PAUSE;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && छोड़ो->tx_छोड़ो)
		pi->fc.req_mode = ICE_FC_TX_PAUSE;
	अन्यथा अगर (!छोड़ो->rx_छोड़ो && !छोड़ो->tx_छोड़ो)
		pi->fc.req_mode = ICE_FC_NONE;
	अन्यथा
		वापस -EINVAL;

	/* Set the FC mode and only restart AN अगर link is up */
	status = ice_set_fc(pi, &aq_failures, link_up);

	अगर (aq_failures & ICE_SET_FC_AQ_FAIL_GET) अणु
		netdev_info(netdev, "Set fc failed on the get_phy_capabilities call with err %s aq_err %s\n",
			    ice_stat_str(status),
			    ice_aq_str(hw->adminq.sq_last_status));
		err = -EAGAIN;
	पूर्ण अन्यथा अगर (aq_failures & ICE_SET_FC_AQ_FAIL_SET) अणु
		netdev_info(netdev, "Set fc failed on the set_phy_config call with err %s aq_err %s\n",
			    ice_stat_str(status),
			    ice_aq_str(hw->adminq.sq_last_status));
		err = -EAGAIN;
	पूर्ण अन्यथा अगर (aq_failures & ICE_SET_FC_AQ_FAIL_UPDATE) अणु
		netdev_info(netdev, "Set fc failed on the get_link_info call with err %s aq_err %s\n",
			    ice_stat_str(status),
			    ice_aq_str(hw->adminq.sq_last_status));
		err = -EAGAIN;
	पूर्ण

	वापस err;
पूर्ण

/**
 * ice_get_rxfh_key_size - get the RSS hash key size
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the table size.
 */
अटल u32 ice_get_rxfh_key_size(काष्ठा net_device __always_unused *netdev)
अणु
	वापस ICE_VSIQF_HKEY_ARRAY_SIZE;
पूर्ण

/**
 * ice_get_rxfh_indir_size - get the Rx flow hash indirection table size
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns the table size.
 */
अटल u32 ice_get_rxfh_indir_size(काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);

	वापस np->vsi->rss_table_size;
पूर्ण

/**
 * ice_get_rxfh - get the Rx flow hash indirection table
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @indir: indirection table
 * @key: hash key
 * @hfunc: hash function
 *
 * Reads the indirection table directly from the hardware.
 */
अटल पूर्णांक
ice_get_rxfh(काष्ठा net_device *netdev, u32 *indir, u8 *key, u8 *hfunc)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक err, i;
	u8 *lut;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;

	अगर (!indir)
		वापस 0;

	अगर (!test_bit(ICE_FLAG_RSS_ENA, pf->flags)) अणु
		/* RSS not supported वापस error here */
		netdev_warn(netdev, "RSS is not configured on this VSI!\n");
		वापस -EIO;
	पूर्ण

	lut = kzalloc(vsi->rss_table_size, GFP_KERNEL);
	अगर (!lut)
		वापस -ENOMEM;

	err = ice_get_rss_key(vsi, key);
	अगर (err)
		जाओ out;

	err = ice_get_rss_lut(vsi, lut, vsi->rss_table_size);
	अगर (err)
		जाओ out;

	क्रम (i = 0; i < vsi->rss_table_size; i++)
		indir[i] = (u32)(lut[i]);

out:
	kमुक्त(lut);
	वापस err;
पूर्ण

/**
 * ice_set_rxfh - set the Rx flow hash indirection table
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @indir: indirection table
 * @key: hash key
 * @hfunc: hash function
 *
 * Returns -EINVAL अगर the table specअगरies an invalid queue ID, otherwise
 * वापसs 0 after programming the table.
 */
अटल पूर्णांक
ice_set_rxfh(काष्ठा net_device *netdev, स्थिर u32 *indir, स्थिर u8 *key,
	     स्थिर u8 hfunc)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	पूर्णांक err;

	dev = ice_pf_to_dev(pf);
	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	अगर (!test_bit(ICE_FLAG_RSS_ENA, pf->flags)) अणु
		/* RSS not supported वापस error here */
		netdev_warn(netdev, "RSS is not configured on this VSI!\n");
		वापस -EIO;
	पूर्ण

	अगर (key) अणु
		अगर (!vsi->rss_hkey_user) अणु
			vsi->rss_hkey_user =
				devm_kzalloc(dev, ICE_VSIQF_HKEY_ARRAY_SIZE,
					     GFP_KERNEL);
			अगर (!vsi->rss_hkey_user)
				वापस -ENOMEM;
		पूर्ण
		स_नकल(vsi->rss_hkey_user, key, ICE_VSIQF_HKEY_ARRAY_SIZE);

		err = ice_set_rss_key(vsi, vsi->rss_hkey_user);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!vsi->rss_lut_user) अणु
		vsi->rss_lut_user = devm_kzalloc(dev, vsi->rss_table_size,
						 GFP_KERNEL);
		अगर (!vsi->rss_lut_user)
			वापस -ENOMEM;
	पूर्ण

	/* Each 32 bits poपूर्णांकed by 'indir' is stored with a lut entry */
	अगर (indir) अणु
		पूर्णांक i;

		क्रम (i = 0; i < vsi->rss_table_size; i++)
			vsi->rss_lut_user[i] = (u8)(indir[i]);
	पूर्ण अन्यथा अणु
		ice_fill_rss_lut(vsi->rss_lut_user, vsi->rss_table_size,
				 vsi->rss_size);
	पूर्ण

	err = ice_set_rss_lut(vsi, vsi->rss_lut_user, vsi->rss_table_size);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/**
 * ice_get_max_txq - वापस the maximum number of Tx queues क्रम in a PF
 * @pf: PF काष्ठाure
 */
अटल पूर्णांक ice_get_max_txq(काष्ठा ice_pf *pf)
अणु
	वापस min3(pf->num_lan_msix, (u16)num_online_cpus(),
		    (u16)pf->hw.func_caps.common_cap.num_txq);
पूर्ण

/**
 * ice_get_max_rxq - वापस the maximum number of Rx queues क्रम in a PF
 * @pf: PF काष्ठाure
 */
अटल पूर्णांक ice_get_max_rxq(काष्ठा ice_pf *pf)
अणु
	वापस min3(pf->num_lan_msix, (u16)num_online_cpus(),
		    (u16)pf->hw.func_caps.common_cap.num_rxq);
पूर्ण

/**
 * ice_get_combined_cnt - वापस the current number of combined channels
 * @vsi: PF VSI poपूर्णांकer
 *
 * Go through all queue vectors and count ones that have both Rx and Tx ring
 * attached
 */
अटल u32 ice_get_combined_cnt(काष्ठा ice_vsi *vsi)
अणु
	u32 combined = 0;
	पूर्णांक q_idx;

	ice_क्रम_each_q_vector(vsi, q_idx) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[q_idx];

		अगर (q_vector->rx.ring && q_vector->tx.ring)
			combined++;
	पूर्ण

	वापस combined;
पूर्ण

/**
 * ice_get_channels - get the current and max supported channels
 * @dev: network पूर्णांकerface device काष्ठाure
 * @ch: ethtool channel data काष्ठाure
 */
अटल व्योम
ice_get_channels(काष्ठा net_device *dev, काष्ठा ethtool_channels *ch)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(dev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;

	/* report maximum channels */
	ch->max_rx = ice_get_max_rxq(pf);
	ch->max_tx = ice_get_max_txq(pf);
	ch->max_combined = min_t(पूर्णांक, ch->max_rx, ch->max_tx);

	/* report current channels */
	ch->combined_count = ice_get_combined_cnt(vsi);
	ch->rx_count = vsi->num_rxq - ch->combined_count;
	ch->tx_count = vsi->num_txq - ch->combined_count;

	/* report other queues */
	ch->other_count = test_bit(ICE_FLAG_FD_ENA, pf->flags) ? 1 : 0;
	ch->max_other = ch->other_count;
पूर्ण

/**
 * ice_get_valid_rss_size - वापस valid number of RSS queues
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @new_size: requested RSS queues
 */
अटल पूर्णांक ice_get_valid_rss_size(काष्ठा ice_hw *hw, पूर्णांक new_size)
अणु
	काष्ठा ice_hw_common_caps *caps = &hw->func_caps.common_cap;

	वापस min_t(पूर्णांक, new_size, BIT(caps->rss_table_entry_width));
पूर्ण

/**
 * ice_vsi_set_dflt_rss_lut - set शेष RSS LUT with requested RSS size
 * @vsi: VSI to reconfigure RSS LUT on
 * @req_rss_size: requested range of queue numbers क्रम hashing
 *
 * Set the VSI's RSS parameters, configure the RSS LUT based on these.
 */
अटल पूर्णांक ice_vsi_set_dflt_rss_lut(काष्ठा ice_vsi *vsi, पूर्णांक req_rss_size)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा device *dev;
	काष्ठा ice_hw *hw;
	पूर्णांक err;
	u8 *lut;

	dev = ice_pf_to_dev(pf);
	hw = &pf->hw;

	अगर (!req_rss_size)
		वापस -EINVAL;

	lut = kzalloc(vsi->rss_table_size, GFP_KERNEL);
	अगर (!lut)
		वापस -ENOMEM;

	/* set RSS LUT parameters */
	अगर (!test_bit(ICE_FLAG_RSS_ENA, pf->flags))
		vsi->rss_size = 1;
	अन्यथा
		vsi->rss_size = ice_get_valid_rss_size(hw, req_rss_size);

	/* create/set RSS LUT */
	ice_fill_rss_lut(lut, vsi->rss_table_size, vsi->rss_size);
	err = ice_set_rss_lut(vsi, lut, vsi->rss_table_size);
	अगर (err)
		dev_err(dev, "Cannot set RSS lut, err %d aq_err %s\n", err,
			ice_aq_str(hw->adminq.sq_last_status));

	kमुक्त(lut);
	वापस err;
पूर्ण

/**
 * ice_set_channels - set the number channels
 * @dev: network पूर्णांकerface device काष्ठाure
 * @ch: ethtool channel data काष्ठाure
 */
अटल पूर्णांक ice_set_channels(काष्ठा net_device *dev, काष्ठा ethtool_channels *ch)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(dev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	पूर्णांक new_rx = 0, new_tx = 0;
	u32 curr_combined;

	/* करो not support changing channels in Safe Mode */
	अगर (ice_is_safe_mode(pf)) अणु
		netdev_err(dev, "Changing channel in Safe Mode is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण
	/* करो not support changing other_count */
	अगर (ch->other_count != (test_bit(ICE_FLAG_FD_ENA, pf->flags) ? 1U : 0U))
		वापस -EINVAL;

	अगर (test_bit(ICE_FLAG_FD_ENA, pf->flags) && pf->hw.fdir_active_fltr) अणु
		netdev_err(dev, "Cannot set channels when Flow Director filters are active\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	curr_combined = ice_get_combined_cnt(vsi);

	/* these checks are क्रम हालs where user didn't specअगरy a particular
	 * value on cmd line but we get non-zero value anyway via
	 * get_channels(); look at ethtool.c in ethtool repository (the user
	 * space part), particularly, करो_schannels() routine
	 */
	अगर (ch->rx_count == vsi->num_rxq - curr_combined)
		ch->rx_count = 0;
	अगर (ch->tx_count == vsi->num_txq - curr_combined)
		ch->tx_count = 0;
	अगर (ch->combined_count == curr_combined)
		ch->combined_count = 0;

	अगर (!(ch->combined_count || (ch->rx_count && ch->tx_count))) अणु
		netdev_err(dev, "Please specify at least 1 Rx and 1 Tx channel\n");
		वापस -EINVAL;
	पूर्ण

	new_rx = ch->combined_count + ch->rx_count;
	new_tx = ch->combined_count + ch->tx_count;

	अगर (new_rx > ice_get_max_rxq(pf)) अणु
		netdev_err(dev, "Maximum allowed Rx channels is %d\n",
			   ice_get_max_rxq(pf));
		वापस -EINVAL;
	पूर्ण
	अगर (new_tx > ice_get_max_txq(pf)) अणु
		netdev_err(dev, "Maximum allowed Tx channels is %d\n",
			   ice_get_max_txq(pf));
		वापस -EINVAL;
	पूर्ण

	ice_vsi_recfg_qs(vsi, new_rx, new_tx);

	अगर (!netअगर_is_rxfh_configured(dev))
		वापस ice_vsi_set_dflt_rss_lut(vsi, new_rx);

	/* Update rss_size due to change in Rx queues */
	vsi->rss_size = ice_get_valid_rss_size(&pf->hw, new_rx);

	वापस 0;
पूर्ण

/**
 * ice_get_wol - get current Wake on LAN configuration
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @wol: Ethtool काष्ठाure to retrieve WoL settings
 */
अटल व्योम ice_get_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_pf *pf = np->vsi->back;

	अगर (np->vsi->type != ICE_VSI_PF)
		netdev_warn(netdev, "Wake on LAN is not supported on this interface!\n");

	/* Get WoL settings based on the HW capability */
	अगर (ice_is_wol_supported(&pf->hw)) अणु
		wol->supported = WAKE_MAGIC;
		wol->wolopts = pf->wol_ena ? WAKE_MAGIC : 0;
	पूर्ण अन्यथा अणु
		wol->supported = 0;
		wol->wolopts = 0;
	पूर्ण
पूर्ण

/**
 * ice_set_wol - set Wake on LAN on supported device
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @wol: Ethtool काष्ठाure to set WoL
 */
अटल पूर्णांक ice_set_wol(काष्ठा net_device *netdev, काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;

	अगर (vsi->type != ICE_VSI_PF || !ice_is_wol_supported(&pf->hw))
		वापस -EOPNOTSUPP;

	/* only magic packet is supported */
	अगर (wol->wolopts && wol->wolopts != WAKE_MAGIC)
		वापस -EOPNOTSUPP;

	/* Set WoL only अगर there is a new value */
	अगर (pf->wol_ena != !!wol->wolopts) अणु
		pf->wol_ena = !!wol->wolopts;
		device_set_wakeup_enable(ice_pf_to_dev(pf), pf->wol_ena);
		netdev_dbg(netdev, "WoL magic packet %sabled\n",
			   pf->wol_ena ? "en" : "dis");
	पूर्ण

	वापस 0;
पूर्ण

क्रमागत ice_container_type अणु
	ICE_RX_CONTAINER,
	ICE_TX_CONTAINER,
पूर्ण;

/**
 * ice_get_rc_coalesce - get ITR values क्रम specअगरic ring container
 * @ec: ethtool काष्ठाure to fill with driver's coalesce settings
 * @c_type: container type, Rx or Tx
 * @rc: ring container that the ITR values will come from
 *
 * Query the device क्रम ice_ring_container specअगरic ITR values. This is
 * करोne per ice_ring_container because each q_vector can have 1 or more rings
 * and all of said ring(s) will have the same ITR values.
 *
 * Returns 0 on success, negative otherwise.
 */
अटल पूर्णांक
ice_get_rc_coalesce(काष्ठा ethtool_coalesce *ec, क्रमागत ice_container_type c_type,
		    काष्ठा ice_ring_container *rc)
अणु
	काष्ठा ice_pf *pf;

	अगर (!rc->ring)
		वापस -EINVAL;

	pf = rc->ring->vsi->back;

	चयन (c_type) अणु
	हाल ICE_RX_CONTAINER:
		ec->use_adaptive_rx_coalesce = ITR_IS_DYNAMIC(rc);
		ec->rx_coalesce_usecs = rc->itr_setting;
		ec->rx_coalesce_usecs_high = rc->ring->q_vector->पूर्णांकrl;
		अवरोध;
	हाल ICE_TX_CONTAINER:
		ec->use_adaptive_tx_coalesce = ITR_IS_DYNAMIC(rc);
		ec->tx_coalesce_usecs = rc->itr_setting;
		अवरोध;
	शेष:
		dev_dbg(ice_pf_to_dev(pf), "Invalid c_type %d\n", c_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_get_q_coalesce - get a queue's ITR/INTRL (coalesce) settings
 * @vsi: VSI associated to the queue क्रम getting ITR/INTRL (coalesce) settings
 * @ec: coalesce settings to program the device with
 * @q_num: update ITR/INTRL (coalesce) settings क्रम this queue number/index
 *
 * Return 0 on success, and negative under the following conditions:
 * 1. Getting Tx or Rx ITR/INTRL (coalesce) settings failed.
 * 2. The q_num passed in is not a valid number/index क्रम Tx and Rx rings.
 */
अटल पूर्णांक
ice_get_q_coalesce(काष्ठा ice_vsi *vsi, काष्ठा ethtool_coalesce *ec, पूर्णांक q_num)
अणु
	अगर (q_num < vsi->num_rxq && q_num < vsi->num_txq) अणु
		अगर (ice_get_rc_coalesce(ec, ICE_RX_CONTAINER,
					&vsi->rx_rings[q_num]->q_vector->rx))
			वापस -EINVAL;
		अगर (ice_get_rc_coalesce(ec, ICE_TX_CONTAINER,
					&vsi->tx_rings[q_num]->q_vector->tx))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (q_num < vsi->num_rxq) अणु
		अगर (ice_get_rc_coalesce(ec, ICE_RX_CONTAINER,
					&vsi->rx_rings[q_num]->q_vector->rx))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (q_num < vsi->num_txq) अणु
		अगर (ice_get_rc_coalesce(ec, ICE_TX_CONTAINER,
					&vsi->tx_rings[q_num]->q_vector->tx))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __ice_get_coalesce - get ITR/INTRL values क्रम the device
 * @netdev: poपूर्णांकer to the netdev associated with this query
 * @ec: ethtool काष्ठाure to fill with driver's coalesce settings
 * @q_num: queue number to get the coalesce settings क्रम
 *
 * If the caller passes in a negative q_num then we वापस coalesce settings
 * based on queue number 0, अन्यथा use the actual q_num passed in.
 */
अटल पूर्णांक
__ice_get_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ec,
		   पूर्णांक q_num)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;

	अगर (q_num < 0)
		q_num = 0;

	अगर (ice_get_q_coalesce(vsi, ec, q_num))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
ice_get_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ec)
अणु
	वापस __ice_get_coalesce(netdev, ec, -1);
पूर्ण

अटल पूर्णांक
ice_get_per_q_coalesce(काष्ठा net_device *netdev, u32 q_num,
		       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __ice_get_coalesce(netdev, ec, q_num);
पूर्ण

/**
 * ice_set_rc_coalesce - set ITR values क्रम specअगरic ring container
 * @c_type: container type, Rx or Tx
 * @ec: ethtool काष्ठाure from user to update ITR settings
 * @rc: ring container that the ITR values will come from
 * @vsi: VSI associated to the ring container
 *
 * Set specअगरic ITR values. This is करोne per ice_ring_container because each
 * q_vector can have 1 or more rings and all of said ring(s) will have the same
 * ITR values.
 *
 * Returns 0 on success, negative otherwise.
 */
अटल पूर्णांक
ice_set_rc_coalesce(क्रमागत ice_container_type c_type, काष्ठा ethtool_coalesce *ec,
		    काष्ठा ice_ring_container *rc, काष्ठा ice_vsi *vsi)
अणु
	स्थिर अक्षर *c_type_str = (c_type == ICE_RX_CONTAINER) ? "rx" : "tx";
	u32 use_adaptive_coalesce, coalesce_usecs;
	काष्ठा ice_pf *pf = vsi->back;
	u16 itr_setting;

	अगर (!rc->ring)
		वापस -EINVAL;

	चयन (c_type) अणु
	हाल ICE_RX_CONTAINER:
		अगर (ec->rx_coalesce_usecs_high > ICE_MAX_INTRL ||
		    (ec->rx_coalesce_usecs_high &&
		     ec->rx_coalesce_usecs_high < pf->hw.पूर्णांकrl_gran)) अणु
			netdev_info(vsi->netdev, "Invalid value, %s-usecs-high valid values are 0 (disabled), %d-%d\n",
				    c_type_str, pf->hw.पूर्णांकrl_gran,
				    ICE_MAX_INTRL);
			वापस -EINVAL;
		पूर्ण
		अगर (ec->rx_coalesce_usecs_high != rc->ring->q_vector->पूर्णांकrl &&
		    (ec->use_adaptive_rx_coalesce || ec->use_adaptive_tx_coalesce)) अणु
			netdev_info(vsi->netdev, "Invalid value, %s-usecs-high cannot be changed if adaptive-tx or adaptive-rx is enabled\n",
				    c_type_str);
			वापस -EINVAL;
		पूर्ण
		अगर (ec->rx_coalesce_usecs_high != rc->ring->q_vector->पूर्णांकrl) अणु
			rc->ring->q_vector->पूर्णांकrl = ec->rx_coalesce_usecs_high;
			ice_ग_लिखो_पूर्णांकrl(rc->ring->q_vector,
					ec->rx_coalesce_usecs_high);
		पूर्ण

		use_adaptive_coalesce = ec->use_adaptive_rx_coalesce;
		coalesce_usecs = ec->rx_coalesce_usecs;

		अवरोध;
	हाल ICE_TX_CONTAINER:
		use_adaptive_coalesce = ec->use_adaptive_tx_coalesce;
		coalesce_usecs = ec->tx_coalesce_usecs;

		अवरोध;
	शेष:
		dev_dbg(ice_pf_to_dev(pf), "Invalid container type %d\n",
			c_type);
		वापस -EINVAL;
	पूर्ण

	itr_setting = rc->itr_setting;
	अगर (coalesce_usecs != itr_setting && use_adaptive_coalesce) अणु
		netdev_info(vsi->netdev, "%s interrupt throttling cannot be changed if adaptive-%s is enabled\n",
			    c_type_str, c_type_str);
		वापस -EINVAL;
	पूर्ण

	अगर (coalesce_usecs > ICE_ITR_MAX) अणु
		netdev_info(vsi->netdev, "Invalid value, %s-usecs range is 0-%d\n",
			    c_type_str, ICE_ITR_MAX);
		वापस -EINVAL;
	पूर्ण

	अगर (use_adaptive_coalesce) अणु
		rc->itr_mode = ITR_DYNAMIC;
	पूर्ण अन्यथा अणु
		rc->itr_mode = ITR_STATIC;
		/* store user facing value how it was set */
		rc->itr_setting = coalesce_usecs;
		/* ग_लिखो the change to the रेजिस्टर */
		ice_ग_लिखो_itr(rc, coalesce_usecs);
		/* क्रमce ग_लिखोs to take effect immediately, the flush shouldn't
		 * be करोne in the functions above because the पूर्णांकent is क्रम
		 * them to करो lazy ग_लिखोs.
		 */
		ice_flush(&pf->hw);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_set_q_coalesce - set a queue's ITR/INTRL (coalesce) settings
 * @vsi: VSI associated to the queue that need updating
 * @ec: coalesce settings to program the device with
 * @q_num: update ITR/INTRL (coalesce) settings क्रम this queue number/index
 *
 * Return 0 on success, and negative under the following conditions:
 * 1. Setting Tx or Rx ITR/INTRL (coalesce) settings failed.
 * 2. The q_num passed in is not a valid number/index क्रम Tx and Rx rings.
 */
अटल पूर्णांक
ice_set_q_coalesce(काष्ठा ice_vsi *vsi, काष्ठा ethtool_coalesce *ec, पूर्णांक q_num)
अणु
	अगर (q_num < vsi->num_rxq && q_num < vsi->num_txq) अणु
		अगर (ice_set_rc_coalesce(ICE_RX_CONTAINER, ec,
					&vsi->rx_rings[q_num]->q_vector->rx,
					vsi))
			वापस -EINVAL;

		अगर (ice_set_rc_coalesce(ICE_TX_CONTAINER, ec,
					&vsi->tx_rings[q_num]->q_vector->tx,
					vsi))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (q_num < vsi->num_rxq) अणु
		अगर (ice_set_rc_coalesce(ICE_RX_CONTAINER, ec,
					&vsi->rx_rings[q_num]->q_vector->rx,
					vsi))
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (q_num < vsi->num_txq) अणु
		अगर (ice_set_rc_coalesce(ICE_TX_CONTAINER, ec,
					&vsi->tx_rings[q_num]->q_vector->tx,
					vsi))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_prपूर्णांक_अगर_odd_usecs - prपूर्णांक message अगर user tries to set odd [tx|rx]-usecs
 * @netdev: netdev used क्रम prपूर्णांक
 * @itr_setting: previous user setting
 * @use_adaptive_coalesce: अगर adaptive coalesce is enabled or being enabled
 * @coalesce_usecs: requested value of [tx|rx]-usecs
 * @c_type_str: either "rx" or "tx" to match user set field of [tx|rx]-usecs
 */
अटल व्योम
ice_prपूर्णांक_अगर_odd_usecs(काष्ठा net_device *netdev, u16 itr_setting,
		       u32 use_adaptive_coalesce, u32 coalesce_usecs,
		       स्थिर अक्षर *c_type_str)
अणु
	अगर (use_adaptive_coalesce)
		वापस;

	अगर (itr_setting != coalesce_usecs && (coalesce_usecs % 2))
		netdev_info(netdev, "User set %s-usecs to %d, device only supports even values. Rounding down and attempting to set %s-usecs to %d\n",
			    c_type_str, coalesce_usecs, c_type_str,
			    ITR_REG_ALIGN(coalesce_usecs));
पूर्ण

/**
 * __ice_set_coalesce - set ITR/INTRL values क्रम the device
 * @netdev: poपूर्णांकer to the netdev associated with this query
 * @ec: ethtool काष्ठाure to fill with driver's coalesce settings
 * @q_num: queue number to get the coalesce settings क्रम
 *
 * If the caller passes in a negative q_num then we set the coalesce settings
 * क्रम all Tx/Rx queues, अन्यथा use the actual q_num passed in.
 */
अटल पूर्णांक
__ice_set_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ec,
		   पूर्णांक q_num)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;

	अगर (q_num < 0) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[0];
		पूर्णांक v_idx;

		अगर (q_vector) अणु
			ice_prपूर्णांक_अगर_odd_usecs(netdev, q_vector->rx.itr_setting,
					       ec->use_adaptive_rx_coalesce,
					       ec->rx_coalesce_usecs, "rx");

			ice_prपूर्णांक_अगर_odd_usecs(netdev, q_vector->tx.itr_setting,
					       ec->use_adaptive_tx_coalesce,
					       ec->tx_coalesce_usecs, "tx");
		पूर्ण

		ice_क्रम_each_q_vector(vsi, v_idx) अणु
			/* In some हालs अगर DCB is configured the num_[rx|tx]q
			 * can be less than vsi->num_q_vectors. This check
			 * accounts क्रम that so we करोn't report a false failure
			 */
			अगर (v_idx >= vsi->num_rxq && v_idx >= vsi->num_txq)
				जाओ set_complete;

			अगर (ice_set_q_coalesce(vsi, ec, v_idx))
				वापस -EINVAL;
		पूर्ण
		जाओ set_complete;
	पूर्ण

	अगर (ice_set_q_coalesce(vsi, ec, q_num))
		वापस -EINVAL;

set_complete:
	वापस 0;
पूर्ण

अटल पूर्णांक
ice_set_coalesce(काष्ठा net_device *netdev, काष्ठा ethtool_coalesce *ec)
अणु
	वापस __ice_set_coalesce(netdev, ec, -1);
पूर्ण

अटल पूर्णांक
ice_set_per_q_coalesce(काष्ठा net_device *netdev, u32 q_num,
		       काष्ठा ethtool_coalesce *ec)
अणु
	वापस __ice_set_coalesce(netdev, ec, q_num);
पूर्ण

#घोषणा ICE_I2C_EEPROM_DEV_ADDR		0xA0
#घोषणा ICE_I2C_EEPROM_DEV_ADDR2	0xA2
#घोषणा ICE_MODULE_TYPE_SFP		0x03
#घोषणा ICE_MODULE_TYPE_QSFP_PLUS	0x0D
#घोषणा ICE_MODULE_TYPE_QSFP28		0x11
#घोषणा ICE_MODULE_SFF_ADDR_MODE	0x04
#घोषणा ICE_MODULE_SFF_DIAG_CAPAB	0x40
#घोषणा ICE_MODULE_REVISION_ADDR	0x01
#घोषणा ICE_MODULE_SFF_8472_COMP	0x5E
#घोषणा ICE_MODULE_SFF_8472_SWAP	0x5C
#घोषणा ICE_MODULE_QSFP_MAX_LEN		640

/**
 * ice_get_module_info - get SFF module type and revision inक्रमmation
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @modinfo: module EEPROM size and layout inक्रमmation काष्ठाure
 */
अटल पूर्णांक
ice_get_module_info(काष्ठा net_device *netdev,
		    काष्ठा ethtool_modinfo *modinfo)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u8 sff8472_comp = 0;
	u8 sff8472_swap = 0;
	u8 sff8636_rev = 0;
	u8 value = 0;

	status = ice_aq_sff_eeprom(hw, 0, ICE_I2C_EEPROM_DEV_ADDR, 0x00, 0x00,
				   0, &value, 1, 0, शून्य);
	अगर (status)
		वापस -EIO;

	चयन (value) अणु
	हाल ICE_MODULE_TYPE_SFP:
		status = ice_aq_sff_eeprom(hw, 0, ICE_I2C_EEPROM_DEV_ADDR,
					   ICE_MODULE_SFF_8472_COMP, 0x00, 0,
					   &sff8472_comp, 1, 0, शून्य);
		अगर (status)
			वापस -EIO;
		status = ice_aq_sff_eeprom(hw, 0, ICE_I2C_EEPROM_DEV_ADDR,
					   ICE_MODULE_SFF_8472_SWAP, 0x00, 0,
					   &sff8472_swap, 1, 0, शून्य);
		अगर (status)
			वापस -EIO;

		अगर (sff8472_swap & ICE_MODULE_SFF_ADDR_MODE) अणु
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण अन्यथा अगर (sff8472_comp &&
			   (sff8472_swap & ICE_MODULE_SFF_DIAG_CAPAB)) अणु
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		पूर्ण
		अवरोध;
	हाल ICE_MODULE_TYPE_QSFP_PLUS:
	हाल ICE_MODULE_TYPE_QSFP28:
		status = ice_aq_sff_eeprom(hw, 0, ICE_I2C_EEPROM_DEV_ADDR,
					   ICE_MODULE_REVISION_ADDR, 0x00, 0,
					   &sff8636_rev, 1, 0, शून्य);
		अगर (status)
			वापस -EIO;
		/* Check revision compliance */
		अगर (sff8636_rev > 0x02) अणु
			/* Module is SFF-8636 compliant */
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ICE_MODULE_QSFP_MAX_LEN;
		पूर्ण अन्यथा अणु
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ICE_MODULE_QSFP_MAX_LEN;
		पूर्ण
		अवरोध;
	शेष:
		netdev_warn(netdev, "SFF Module Type not recognized.\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_get_module_eeprom - fill buffer with SFF EEPROM contents
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @ee: EEPROM dump request काष्ठाure
 * @data: buffer to be filled with EEPROM contents
 */
अटल पूर्णांक
ice_get_module_eeprom(काष्ठा net_device *netdev,
		      काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
#घोषणा SFF_READ_BLOCK_SIZE 8
	u8 value[SFF_READ_BLOCK_SIZE] = अणु 0 पूर्ण;
	u8 addr = ICE_I2C_EEPROM_DEV_ADDR;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	bool is_sfp = false;
	अचिन्हित पूर्णांक i, j;
	u16 offset = 0;
	u8 page = 0;

	अगर (!ee || !ee->len || !data)
		वापस -EINVAL;

	status = ice_aq_sff_eeprom(hw, 0, addr, offset, page, 0, value, 1, 0,
				   शून्य);
	अगर (status)
		वापस -EIO;

	अगर (value[0] == ICE_MODULE_TYPE_SFP)
		is_sfp = true;

	स_रखो(data, 0, ee->len);
	क्रम (i = 0; i < ee->len; i += SFF_READ_BLOCK_SIZE) अणु
		offset = i + ee->offset;
		page = 0;

		/* Check अगर we need to access the other memory page */
		अगर (is_sfp) अणु
			अगर (offset >= ETH_MODULE_SFF_8079_LEN) अणु
				offset -= ETH_MODULE_SFF_8079_LEN;
				addr = ICE_I2C_EEPROM_DEV_ADDR2;
			पूर्ण
		पूर्ण अन्यथा अणु
			जबतक (offset >= ETH_MODULE_SFF_8436_LEN) अणु
				/* Compute memory page number and offset. */
				offset -= ETH_MODULE_SFF_8436_LEN / 2;
				page++;
			पूर्ण
		पूर्ण

		/* Bit 2 of EEPROM address 0x02 declares upper
		 * pages are disabled on QSFP modules.
		 * SFP modules only ever use page 0.
		 */
		अगर (page == 0 || !(data[0x2] & 0x4)) अणु
			/* If i2c bus is busy due to slow page change or
			 * link management access, call can fail. This is normal.
			 * So we retry this a few बार.
			 */
			क्रम (j = 0; j < 4; j++) अणु
				status = ice_aq_sff_eeprom(hw, 0, addr, offset, page,
							   !is_sfp, value,
							   SFF_READ_BLOCK_SIZE,
							   0, शून्य);
				netdev_dbg(netdev, "SFF %02X %02X %02X %X = %02X%02X%02X%02X.%02X%02X%02X%02X (%X)\n",
					   addr, offset, page, is_sfp,
					   value[0], value[1], value[2], value[3],
					   value[4], value[5], value[6], value[7],
					   status);
				अगर (status) अणु
					usleep_range(1500, 2500);
					स_रखो(value, 0, SFF_READ_BLOCK_SIZE);
					जारी;
				पूर्ण
				अवरोध;
			पूर्ण

			/* Make sure we have enough room क्रम the new block */
			अगर ((i + SFF_READ_BLOCK_SIZE) < ee->len)
				स_नकल(data + i, value, SFF_READ_BLOCK_SIZE);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ice_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_USECS |
				     ETHTOOL_COALESCE_USE_ADAPTIVE |
				     ETHTOOL_COALESCE_RX_USECS_HIGH,
	.get_link_ksettings	= ice_get_link_ksettings,
	.set_link_ksettings	= ice_set_link_ksettings,
	.get_drvinfo		= ice_get_drvinfo,
	.get_regs_len		= ice_get_regs_len,
	.get_regs		= ice_get_regs,
	.get_wol		= ice_get_wol,
	.set_wol		= ice_set_wol,
	.get_msglevel		= ice_get_msglevel,
	.set_msglevel		= ice_set_msglevel,
	.self_test		= ice_self_test,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= ice_get_eeprom_len,
	.get_eeprom		= ice_get_eeprom,
	.get_coalesce		= ice_get_coalesce,
	.set_coalesce		= ice_set_coalesce,
	.get_strings		= ice_get_strings,
	.set_phys_id		= ice_set_phys_id,
	.get_ethtool_stats      = ice_get_ethtool_stats,
	.get_priv_flags		= ice_get_priv_flags,
	.set_priv_flags		= ice_set_priv_flags,
	.get_sset_count		= ice_get_sset_count,
	.get_rxnfc		= ice_get_rxnfc,
	.set_rxnfc		= ice_set_rxnfc,
	.get_ringparam		= ice_get_ringparam,
	.set_ringparam		= ice_set_ringparam,
	.nway_reset		= ice_nway_reset,
	.get_छोड़ोparam		= ice_get_छोड़ोparam,
	.set_छोड़ोparam		= ice_set_छोड़ोparam,
	.get_rxfh_key_size	= ice_get_rxfh_key_size,
	.get_rxfh_indir_size	= ice_get_rxfh_indir_size,
	.get_rxfh		= ice_get_rxfh,
	.set_rxfh		= ice_set_rxfh,
	.get_channels		= ice_get_channels,
	.set_channels		= ice_set_channels,
	.get_ts_info		= ethtool_op_get_ts_info,
	.get_per_queue_coalesce	= ice_get_per_q_coalesce,
	.set_per_queue_coalesce	= ice_set_per_q_coalesce,
	.get_fecparam		= ice_get_fecparam,
	.set_fecparam		= ice_set_fecparam,
	.get_module_info	= ice_get_module_info,
	.get_module_eeprom	= ice_get_module_eeprom,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops ice_ethtool_safe_mode_ops = अणु
	.get_link_ksettings	= ice_get_link_ksettings,
	.set_link_ksettings	= ice_set_link_ksettings,
	.get_drvinfo		= ice_get_drvinfo,
	.get_regs_len		= ice_get_regs_len,
	.get_regs		= ice_get_regs,
	.get_wol		= ice_get_wol,
	.set_wol		= ice_set_wol,
	.get_msglevel		= ice_get_msglevel,
	.set_msglevel		= ice_set_msglevel,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= ice_get_eeprom_len,
	.get_eeprom		= ice_get_eeprom,
	.get_strings		= ice_get_strings,
	.get_ethtool_stats	= ice_get_ethtool_stats,
	.get_sset_count		= ice_get_sset_count,
	.get_ringparam		= ice_get_ringparam,
	.set_ringparam		= ice_set_ringparam,
	.nway_reset		= ice_nway_reset,
	.get_channels		= ice_get_channels,
पूर्ण;

/**
 * ice_set_ethtool_safe_mode_ops - setup safe mode ethtool ops
 * @netdev: network पूर्णांकerface device काष्ठाure
 */
व्योम ice_set_ethtool_safe_mode_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ice_ethtool_safe_mode_ops;
पूर्ण

/**
 * ice_set_ethtool_ops - setup netdev ethtool ops
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * setup netdev ethtool ops with ice specअगरic ops
 */
व्योम ice_set_ethtool_ops(काष्ठा net_device *netdev)
अणु
	netdev->ethtool_ops = &ice_ethtool_ops;
पूर्ण
