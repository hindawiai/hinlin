<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../usb.h"
#समावेश "../ps.h"
#समावेश "../cam.h"
#समावेश "../stats.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "mac.h"
#समावेश "trx.h"
#समावेश "../rtl8192c/fw_common.h"

#समावेश <linux/module.h>

/* macro to लघुen lines */

#घोषणा LINK_Q	ui_link_quality
#घोषणा RX_EVM	rx_evm_percentage
#घोषणा RX_SIGQ	rx_mimo_sig_qual

व्योम rtl92c_पढ़ो_chip_version(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	क्रमागत version_8192c chip_version = VERSION_UNKNOWN;
	स्थिर अक्षर *versionid;
	u32 value32;

	value32 = rtl_पढ़ो_dword(rtlpriv, REG_SYS_CFG);
	अगर (value32 & TRP_VAUX_EN) अणु
		chip_version = (value32 & TYPE_ID) ? VERSION_TEST_CHIP_92C :
			       VERSION_TEST_CHIP_88C;
	पूर्ण अन्यथा अणु
		/* Normal mass production chip. */
		chip_version = NORMAL_CHIP;
		chip_version |= ((value32 & TYPE_ID) ? CHIP_92C : 0);
		chip_version |= ((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : 0);
		अगर (IS_VENDOR_UMC(chip_version))
			chip_version |= ((value32 & CHIP_VER_RTL_MASK) ?
					 CHIP_VENDOR_UMC_B_CUT : 0);
		अगर (IS_92C_SERIAL(chip_version)) अणु
			value32 = rtl_पढ़ो_dword(rtlpriv, REG_HPON_FSM);
			chip_version |= ((CHIP_BONDING_IDENTIFIER(value32) ==
				 CHIP_BONDING_92C_1T2R) ? CHIP_92C_1T2R : 0);
		पूर्ण
	पूर्ण
	rtlhal->version  = (क्रमागत version_8192c)chip_version;
	pr_info("Chip version 0x%x\n", chip_version);
	चयन (rtlhal->version) अणु
	हाल VERSION_NORMAL_TSMC_CHIP_92C_1T2R:
		versionid = "NORMAL_B_CHIP_92C";
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_92C:
		versionid = "NORMAL_TSMC_CHIP_92C";
		अवरोध;
	हाल VERSION_NORMAL_TSMC_CHIP_88C:
		versionid = "NORMAL_TSMC_CHIP_88C";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_1T2R_A_CUT:
		versionid = "NORMAL_UMC_CHIP_i92C_1T2R_A_CUT";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_A_CUT:
		versionid = "NORMAL_UMC_CHIP_92C_A_CUT";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_88C_A_CUT:
		versionid = "NORMAL_UMC_CHIP_88C_A_CUT";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_1T2R_B_CUT:
		versionid = "NORMAL_UMC_CHIP_92C_1T2R_B_CUT";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_92C_B_CUT:
		versionid = "NORMAL_UMC_CHIP_92C_B_CUT";
		अवरोध;
	हाल VERSION_NORMAL_UMC_CHIP_88C_B_CUT:
		versionid = "NORMAL_UMC_CHIP_88C_B_CUT";
		अवरोध;
	हाल VERSION_TEST_CHIP_92C:
		versionid = "TEST_CHIP_92C";
		अवरोध;
	हाल VERSION_TEST_CHIP_88C:
		versionid = "TEST_CHIP_88C";
		अवरोध;
	शेष:
		versionid = "UNKNOWN";
		अवरोध;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"Chip Version ID: %s\n", versionid);

	अगर (IS_92C_SERIAL(rtlhal->version))
		rtlphy->rf_type =
			 (IS_92C_1T2R(rtlhal->version)) ? RF_1T2R : RF_2T2R;
	अन्यथा
		rtlphy->rf_type = RF_1T1R;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Chip RF Type: %s\n",
		rtlphy->rf_type == RF_2T2R ? "RF_2T2R" : "RF_1T1R");
	अगर (get_rf_type(rtlphy) == RF_1T1R)
		rtlpriv->dm.rfpath_rxenable[0] = true;
	अन्यथा
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "VersionID = 0x%4x\n",
		rtlhal->version);
पूर्ण

/**
 * ग_लिखोLLT - LLT table ग_लिखो access
 * @hw: Poपूर्णांकer to the ieee80211_hw काष्ठाure.
 * @address: LLT logical address.
 * @data: LLT data content
 *
 * Realtek hardware access function.
 *
 */
bool rtl92c_llt_ग_लिखो(काष्ठा ieee80211_hw *hw, u32 address, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool status = true;
	दीर्घ count = 0;
	u32 value = _LLT_INIT_ADDR(address) |
	    _LLT_INIT_DATA(data) | _LLT_OP(_LLT_WRITE_ACCESS);

	rtl_ग_लिखो_dword(rtlpriv, REG_LLT_INIT, value);
	करो अणु
		value = rtl_पढ़ो_dword(rtlpriv, REG_LLT_INIT);
		अगर (_LLT_NO_ACTIVE == _LLT_OP_VALUE(value))
			अवरोध;
		अगर (count > POLLING_LLT_THRESHOLD) अणु
			pr_err("Failed to polling write LLT done at address %d! _LLT_OP_VALUE(%x)\n",
			       address, _LLT_OP_VALUE(value));
			status = false;
			अवरोध;
		पूर्ण
	पूर्ण जबतक (++count);
	वापस status;
पूर्ण

/**
 * rtl92c_init_LLT_table - Init LLT table
 * @hw: Poपूर्णांकer to the ieee80211_hw काष्ठाure.
 * @boundary: Page boundary.
 *
 * Realtek hardware access function.
 */
bool rtl92c_init_llt_table(काष्ठा ieee80211_hw *hw, u32 boundary)
अणु
	bool rst = true;
	u32	i;

	क्रम (i = 0; i < (boundary - 1); i++) अणु
		rst = rtl92c_llt_ग_लिखो(hw, i , i + 1);
		अगर (!rst) अणु
			pr_err("===> %s #1 fail\n", __func__);
			वापस rst;
		पूर्ण
	पूर्ण
	/* end of list */
	rst = rtl92c_llt_ग_लिखो(hw, (boundary - 1), 0xFF);
	अगर (!rst) अणु
		pr_err("===> %s #2 fail\n", __func__);
		वापस rst;
	पूर्ण
	/* Make the other pages as ring buffer
	 * This ring buffer is used as beacon buffer अगर we config this MAC
	 *  as two MAC transfer.
	 * Otherwise used as local loopback buffer.
	 */
	क्रम (i = boundary; i < LLT_LAST_ENTRY_OF_TX_PKT_BUFFER; i++) अणु
		rst = rtl92c_llt_ग_लिखो(hw, i, (i + 1));
		अगर (!rst) अणु
			pr_err("===> %s #3 fail\n", __func__);
			वापस rst;
		पूर्ण
	पूर्ण
	/* Let last entry poपूर्णांक to the start entry of ring buffer */
	rst = rtl92c_llt_ग_लिखो(hw, LLT_LAST_ENTRY_OF_TX_PKT_BUFFER, boundary);
	अगर (!rst) अणु
		pr_err("===> %s #4 fail\n", __func__);
		वापस rst;
	पूर्ण
	वापस rst;
पूर्ण

व्योम rtl92c_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddr, bool is_group, u8 enc_algo,
		     bool is_wepkey, bool clear_all)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 *macaddr = p_macaddr;
	u32 entry_id = 0;
	bool is_pairwise = false;
	अटल u8 cam_स्थिर_addr[4][6] = अणु
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x01पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x02पूर्ण,
		अणु0x00, 0x00, 0x00, 0x00, 0x00, 0x03पूर्ण
	पूर्ण;
	अटल u8 cam_स्थिर_broad[] = अणु
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	पूर्ण;

	अगर (clear_all) अणु
		u8 idx = 0;
		u8 cam_offset = 0;
		u8 clear_number = 5;

		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG, "clear_all\n");
		क्रम (idx = 0; idx < clear_number; idx++) अणु
			rtl_cam_mark_invalid(hw, cam_offset + idx);
			rtl_cam_empty_entry(hw, cam_offset + idx);
			अगर (idx < 5) अणु
				स_रखो(rtlpriv->sec.key_buf[idx], 0,
				       MAX_KEY_LEN);
				rtlpriv->sec.key_len[idx] = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (enc_algo) अणु
		हाल WEP40_ENCRYPTION:
			enc_algo = CAM_WEP40;
			अवरोध;
		हाल WEP104_ENCRYPTION:
			enc_algo = CAM_WEP104;
			अवरोध;
		हाल TKIP_ENCRYPTION:
			enc_algo = CAM_TKIP;
			अवरोध;
		हाल AESCCMP_ENCRYPTION:
			enc_algo = CAM_AES;
			अवरोध;
		शेष:
			pr_err("illegal switch case\n");
			enc_algo = CAM_TKIP;
			अवरोध;
		पूर्ण
		अगर (is_wepkey || rtlpriv->sec.use_शेषkey) अणु
			macaddr = cam_स्थिर_addr[key_index];
			entry_id = key_index;
		पूर्ण अन्यथा अणु
			अगर (is_group) अणु
				macaddr = cam_स्थिर_broad;
				entry_id = key_index;
			पूर्ण अन्यथा अणु
				अगर (mac->opmode == NL80211_IFTYPE_AP ||
				    mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
					entry_id = rtl_cam_get_मुक्त_entry(hw,
								 p_macaddr);
					अगर (entry_id >=  TOTAL_CAM_ENTRY) अणु
						pr_err("Can not find free hw security cam entry\n");
						वापस;
					पूर्ण
				पूर्ण अन्यथा अणु
					entry_id = CAM_PAIRWISE_KEY_POSITION;
				पूर्ण

				key_index = PAIRWISE_KEYIDX;
				is_pairwise = true;
			पूर्ण
		पूर्ण
		अगर (rtlpriv->sec.key_len[key_index] == 0) अणु
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"delete one entry\n");
			अगर (mac->opmode == NL80211_IFTYPE_AP ||
			    mac->opmode == NL80211_IFTYPE_MESH_POINT)
				rtl_cam_del_entry(hw, p_macaddr);
			rtl_cam_delete_one_entry(hw, p_macaddr, entry_id);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"The insert KEY length is %d\n",
				 rtlpriv->sec.key_len[PAIRWISE_KEYIDX]);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD,
				"The insert KEY is %x %x\n",
				rtlpriv->sec.key_buf[0][0],
				rtlpriv->sec.key_buf[0][1]);
			rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
				"add one entry\n");
			अगर (is_pairwise) अणु
				RT_PRINT_DATA(rtlpriv, COMP_SEC, DBG_LOUD,
					      "Pairwise Key content",
					      rtlpriv->sec.pairwise_key,
					      rtlpriv->sec.
					      key_len[PAIRWISE_KEYIDX]);
				rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
					"set Pairwise key\n");

				rtl_cam_add_one_entry(hw, macaddr, key_index,
						entry_id, enc_algo,
						CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.
						key_buf[key_index]);
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
					"set group key\n");
				अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
					rtl_cam_add_one_entry(hw,
						rtlefuse->dev_addr,
						PAIRWISE_KEYIDX,
						CAM_PAIRWISE_KEY_POSITION,
						enc_algo,
						CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.key_buf
						[entry_id]);
				पूर्ण
				rtl_cam_add_one_entry(hw, macaddr, key_index,
						entry_id, enc_algo,
						CAM_CONFIG_NO_USEDK,
						rtlpriv->sec.key_buf[entry_id]);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

u32 rtl92c_get_txdma_status(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	वापस rtl_पढ़ो_dword(rtlpriv, REG_TXDMA_STATUS);
पूर्ण

व्योम rtl92c_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	अगर (IS_HARDWARE_TYPE_8192CE(rtlpriv)) अणु
		rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, rtlpci->irq_mask[0] &
				0xFFFFFFFF);
		rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, rtlpci->irq_mask[1] &
				0xFFFFFFFF);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, rtlusb->irq_mask[0] &
				0xFFFFFFFF);
		rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, rtlusb->irq_mask[1] &
				0xFFFFFFFF);
	पूर्ण
पूर्ण

व्योम rtl92c_init_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	 rtl92c_enable_पूर्णांकerrupt(hw);
पूर्ण

व्योम rtl92c_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_dword(rtlpriv, REG_HIMR, IMR8190_DISABLED);
	rtl_ग_लिखो_dword(rtlpriv, REG_HIMRE, IMR8190_DISABLED);
पूर्ण

व्योम rtl92c_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl92c_dm_init_edca_turbo(hw);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM, (u8 *)&aci);
पूर्ण

व्योम rtl92c_init_driver_info_size(काष्ठा ieee80211_hw *hw, u8 size)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_RX_DRVINFO_SZ, size);
पूर्ण

पूर्णांक rtl92c_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type)
अणु
	u8 value;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		value = NT_NO_LINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"Set Network type to NO LINK!\n");
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		value = NT_LINK_AD_HOC;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"Set Network type to Ad Hoc!\n");
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		value = NT_LINK_AP;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"Set Network type to STA!\n");
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		value = NT_AS_AP;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"Set Network type to AP!\n");
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			"Network type %d not supported!\n", type);
		वापस -EOPNOTSUPP;
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, MSR, value);
	वापस 0;
पूर्ण

व्योम rtl92c_init_network_type(काष्ठा ieee80211_hw *hw)
अणु
	rtl92c_set_network_type(hw, NL80211_IFTYPE_UNSPECIFIED);
पूर्ण

व्योम rtl92c_init_adaptive_ctrl(काष्ठा ieee80211_hw *hw)
अणु
	u16	value16;
	u32	value32;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* Response Rate Set */
	value32 = rtl_पढ़ो_dword(rtlpriv, REG_RRSR);
	value32 &= ~RATE_BITMAP_ALL;
	value32 |= RATE_RRSR_CCK_ONLY_1M;
	rtl_ग_लिखो_dword(rtlpriv, REG_RRSR, value32);
	/* SIFS (used in NAV) */
	value16 = _SPEC_SIFS_CCK(0x10) | _SPEC_SIFS_OFDM(0x10);
	rtl_ग_लिखो_word(rtlpriv,  REG_SPEC_SIFS, value16);
	/* Retry Limit */
	value16 = _LRL(0x30) | _SRL(0x30);
	rtl_ग_लिखो_dword(rtlpriv,  REG_RL, value16);
पूर्ण

व्योम rtl92c_init_rate_fallback(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* Set Data Auto Rate Fallback Retry Count रेजिस्टर. */
	rtl_ग_लिखो_dword(rtlpriv,  REG_DARFRC, 0x00000000);
	rtl_ग_लिखो_dword(rtlpriv,  REG_DARFRC+4, 0x10080404);
	rtl_ग_लिखो_dword(rtlpriv,  REG_RARFRC, 0x04030201);
	rtl_ग_लिखो_dword(rtlpriv,  REG_RARFRC+4, 0x08070605);
पूर्ण

अटल व्योम rtl92c_set_cck_sअगरs(काष्ठा ieee80211_hw *hw, u8 trx_sअगरs,
				u8 ctx_sअगरs)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_CCK, trx_sअगरs);
	rtl_ग_लिखो_byte(rtlpriv, (REG_SIFS_CCK + 1), ctx_sअगरs);
पूर्ण

अटल व्योम rtl92c_set_ofdm_sअगरs(काष्ठा ieee80211_hw *hw, u8 trx_sअगरs,
				 u8 ctx_sअगरs)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_OFDM, trx_sअगरs);
	rtl_ग_लिखो_byte(rtlpriv, (REG_SIFS_OFDM + 1), ctx_sअगरs);
पूर्ण

व्योम rtl92c_init_edca_param(काष्ठा ieee80211_hw *hw,
			    u16 queue, u16 txop, u8 cw_min, u8 cw_max, u8 aअगरs)
अणु
	/* sequence: VO, VI, BE, BK ==> the same as 92C hardware design.
	 * referenc : क्रमागत nl80211_txq_q or ieee80211_set_wmm_शेष function.
	 */
	u32 value;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	value = (u32)aअगरs;
	value |= ((u32)cw_min & 0xF) << 8;
	value |= ((u32)cw_max & 0xF) << 12;
	value |= (u32)txop << 16;
	/* 92C hardware रेजिस्टर sequence is the same as queue number. */
	rtl_ग_लिखो_dword(rtlpriv, (REG_EDCA_VO_PARAM + (queue * 4)), value);
पूर्ण

व्योम rtl92c_init_edca(काष्ठा ieee80211_hw *hw)
अणु
	u16 value16;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* disable EDCCA count करोwn, to reduce collison and retry */
	value16 = rtl_पढ़ो_word(rtlpriv, REG_RD_CTRL);
	value16 |= DIS_EDCA_CNT_DWN;
	rtl_ग_लिखो_word(rtlpriv, REG_RD_CTRL, value16);
	/* Update SIFS timing.  ??????????
	 * pHalData->SअगरsTime = 0x0e0e0a0a; */
	rtl92c_set_cck_sअगरs(hw, 0xa, 0xa);
	rtl92c_set_ofdm_sअगरs(hw, 0xe, 0xe);
	/* Set CCK/OFDM SIFS to be 10us. */
	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_CCK, 0x0a0a);
	rtl_ग_लिखो_word(rtlpriv, REG_SIFS_OFDM, 0x1010);
	rtl_ग_लिखो_word(rtlpriv, REG_PROT_MODE_CTRL, 0x0204);
	rtl_ग_लिखो_dword(rtlpriv, REG_BAR_MODE_CTRL, 0x014004);
	/* TXOP */
	rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BE_PARAM, 0x005EA42B);
	rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BK_PARAM, 0x0000A44F);
	rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VI_PARAM, 0x005EA324);
	rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VO_PARAM, 0x002FA226);
	/* PIFS */
	rtl_ग_लिखो_byte(rtlpriv, REG_PIFS, 0x1C);
	/* AGGR BREAK TIME Register */
	rtl_ग_लिखो_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);
	rtl_ग_लिखो_word(rtlpriv, REG_NAV_PROT_LEN, 0x0040);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCNDMATIM, 0x02);
	rtl_ग_लिखो_byte(rtlpriv, REG_ATIMWND, 0x02);
पूर्ण

व्योम rtl92c_init_ampdu_aggregation(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_dword(rtlpriv, REG_AGGLEN_LMT, 0x99997631);
	rtl_ग_लिखो_byte(rtlpriv, REG_AGGR_BREAK_TIME, 0x16);
	/* init AMPDU aggregation number, tuning क्रम Tx's TP, */
	rtl_ग_लिखो_word(rtlpriv, 0x4CA, 0x0708);
पूर्ण

व्योम rtl92c_init_beacon_max_error(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_MAX_ERR, 0xFF);
पूर्ण

व्योम rtl92c_init_rdg_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_RD_CTRL, 0xFF);
	rtl_ग_लिखो_word(rtlpriv, REG_RD_NAV_NXT, 0x200);
	rtl_ग_लिखो_byte(rtlpriv, REG_RD_RESP_PKT_TH, 0x05);
पूर्ण

व्योम rtl92c_init_retry_function(काष्ठा ieee80211_hw *hw)
अणु
	u8	value8;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	value8 = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL);
	value8 |= EN_AMPDU_RTY_NEW;
	rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL, value8);
	/* Set ACK समयout */
	rtl_ग_लिखो_byte(rtlpriv, REG_ACKTO, 0x40);
पूर्ण

व्योम rtl92c_disable_fast_edca(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_word(rtlpriv, REG_FAST_EDCA_CTRL, 0);
पूर्ण

व्योम rtl92c_set_min_space(काष्ठा ieee80211_hw *hw, bool is2T)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 value = is2T ? MAX_MSS_DENSITY_2T : MAX_MSS_DENSITY_1T;

	rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE, value);
पूर्ण

/*==============================================================*/

अटल व्योम _rtl92c_query_rxphystatus(काष्ठा ieee80211_hw *hw,
				      काष्ठा rtl_stats *pstats,
				      काष्ठा rx_desc_92c *p_desc,
				      काष्ठा rx_fwinfo_92c *p_drvinfo,
				      bool packet_match_bssid,
				      bool packet_toself,
				      bool packet_beacon)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा phy_sts_cck_8192s_t *cck_buf;
	s8 rx_pwr_all = 0, rx_pwr[4];
	u8 rf_rx_num = 0, evm, pwdb_all;
	u8 i, max_spatial_stream;
	u32 rssi, total_rssi = 0;
	bool in_घातersavemode = false;
	bool is_cck_rate;
	__le32 *pdesc = (__le32 *)p_desc;

	is_cck_rate = RX_HAL_IS_CCK_RATE(p_desc->rxmcs);
	pstats->packet_matchbssid = packet_match_bssid;
	pstats->packet_toself = packet_toself;
	pstats->packet_beacon = packet_beacon;
	pstats->is_cck = is_cck_rate;
	pstats->RX_SIGQ[0] = -1;
	pstats->RX_SIGQ[1] = -1;
	अगर (is_cck_rate) अणु
		u8 report, cck_highpwr;

		cck_buf = (काष्ठा phy_sts_cck_8192s_t *)p_drvinfo;
		अगर (!in_घातersavemode)
			cck_highpwr = rtlphy->cck_high_घातer;
		अन्यथा
			cck_highpwr = false;
		अगर (!cck_highpwr) अणु
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;

			report = cck_buf->cck_agc_rpt & 0xc0;
			report = report >> 6;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -46 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -26 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -12 - (cck_agc_rpt & 0x3e);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 16 - (cck_agc_rpt & 0x3e);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			u8 cck_agc_rpt = cck_buf->cck_agc_rpt;

			report = p_drvinfo->cfosho[0] & 0x60;
			report = report >> 5;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -46 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -26 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -12 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 16 - ((cck_agc_rpt & 0x1f) << 1);
				अवरोध;
			पूर्ण
		पूर्ण
		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstats->rx_pwdb_all = pwdb_all;
		pstats->recvसंकेतघातer = rx_pwr_all;
		अगर (packet_match_bssid) अणु
			u8 sq;

			अगर (pstats->rx_pwdb_all > 40)
				sq = 100;
			अन्यथा अणु
				sq = cck_buf->sq_rpt;
				अगर (sq > 64)
					sq = 0;
				अन्यथा अगर (sq < 20)
					sq = 100;
				अन्यथा
					sq = ((64 - sq) * 100) / 44;
			पूर्ण
			pstats->संकेतquality = sq;
			pstats->RX_SIGQ[0] = sq;
			pstats->RX_SIGQ[1] = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtlpriv->dm.rfpath_rxenable[0] =
		    rtlpriv->dm.rfpath_rxenable[1] = true;
		क्रम (i = RF90_PATH_A; i < RF90_PATH_MAX; i++) अणु
			अगर (rtlpriv->dm.rfpath_rxenable[i])
				rf_rx_num++;
			rx_pwr[i] =
			    ((p_drvinfo->gain_trsw[i] & 0x3f) * 2) - 110;
			rssi = rtl_query_rxpwrpercentage(rx_pwr[i]);
			total_rssi += rssi;
			rtlpriv->stats.rx_snr_db[i] =
			    (दीर्घ)(p_drvinfo->rxsnr[i] / 2);

			अगर (packet_match_bssid)
				pstats->rx_mimo_संकेतstrength[i] = (u8) rssi;
		पूर्ण
		rx_pwr_all = ((p_drvinfo->pwdb_all >> 1) & 0x7f) - 110;
		pwdb_all = rtl_query_rxpwrpercentage(rx_pwr_all);
		pstats->rx_pwdb_all = pwdb_all;
		pstats->rxघातer = rx_pwr_all;
		pstats->recvसंकेतघातer = rx_pwr_all;
		अगर (get_rx_desc_rx_mcs(pdesc) &&
		    get_rx_desc_rx_mcs(pdesc) >= DESC_RATEMCS8 &&
		    get_rx_desc_rx_mcs(pdesc) <= DESC_RATEMCS15)
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;
		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			evm = rtl_evm_db_to_percentage(p_drvinfo->rxevm[i]);
			अगर (packet_match_bssid) अणु
				अगर (i == 0)
					pstats->संकेतquality =
					    (u8) (evm & 0xff);
				pstats->RX_SIGQ[i] =
				    (u8) (evm & 0xff);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (is_cck_rate)
		pstats->संकेतstrength =
		    (u8)(rtl_संकेत_scale_mapping(hw, pwdb_all));
	अन्यथा अगर (rf_rx_num != 0)
		pstats->संकेतstrength =
		    (u8)(rtl_संकेत_scale_mapping(hw, total_rssi /= rf_rx_num));
पूर्ण

व्योम rtl92c_translate_rx_संकेत_stuff(काष्ठा ieee80211_hw *hw,
					       काष्ठा sk_buff *skb,
					       काष्ठा rtl_stats *pstats,
					       काष्ठा rx_desc_92c *pdesc,
					       काष्ठा rx_fwinfo_92c *p_drvinfo)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr;
	u8 *पंचांगp_buf;
	u8 *praddr;
	__le16 fc;
	u16 type, cpu_fc;
	bool packet_matchbssid, packet_toself, packet_beacon = false;

	पंचांगp_buf = skb->data + pstats->rx_drvinfo_size + pstats->rx_bufshअगरt;
	hdr = (काष्ठा ieee80211_hdr *)पंचांगp_buf;
	fc = hdr->frame_control;
	cpu_fc = le16_to_cpu(fc);
	type = WLAN_FC_GET_TYPE(fc);
	praddr = hdr->addr1;
	packet_matchbssid =
	    ((IEEE80211_FTYPE_CTL != type) &&
	     ether_addr_equal(mac->bssid,
			      (cpu_fc & IEEE80211_FCTL_TODS) ? hdr->addr1 :
			      (cpu_fc & IEEE80211_FCTL_FROMDS) ? hdr->addr2 :
			      hdr->addr3) &&
	     (!pstats->hwerror) && (!pstats->crc) && (!pstats->icv));

	packet_toself = packet_matchbssid &&
	    ether_addr_equal(praddr, rtlefuse->dev_addr);
	अगर (ieee80211_is_beacon(fc))
		packet_beacon = true;
	_rtl92c_query_rxphystatus(hw, pstats, pdesc, p_drvinfo,
				   packet_matchbssid, packet_toself,
				   packet_beacon);
	rtl_process_phyinfo(hw, पंचांगp_buf, pstats);
पूर्ण
