<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../efuse.h"
#समावेश "../base.h"
#समावेश "../cam.h"
#समावेश "../ps.h"
#समावेश "../usb.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "../rtl8192c/phy_common.h"
#समावेश "mac.h"
#समावेश "dm.h"
#समावेश "../rtl8192c/dm_common.h"
#समावेश "../rtl8192c/fw_common.h"
#समावेश "hw.h"
#समावेश "../rtl8192ce/hw.h"
#समावेश "trx.h"
#समावेश "led.h"
#समावेश "table.h"

अटल व्योम _rtl92cu_phy_param_tab_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);

	rtlphy->hwparam_tables[MAC_REG].length = RTL8192CUMAC_2T_ARRAYLENGTH;
	rtlphy->hwparam_tables[MAC_REG].pdata = RTL8192CUMAC_2T_ARRAY;
	अगर (IS_HIGHT_PA(rtlefuse->board_type)) अणु
		rtlphy->hwparam_tables[PHY_REG_PG].length =
			RTL8192CUPHY_REG_ARRAY_PG_HPLENGTH;
		rtlphy->hwparam_tables[PHY_REG_PG].pdata =
			RTL8192CUPHY_REG_ARRAY_PG_HP;
	पूर्ण अन्यथा अणु
		rtlphy->hwparam_tables[PHY_REG_PG].length =
			RTL8192CUPHY_REG_ARRAY_PGLENGTH;
		rtlphy->hwparam_tables[PHY_REG_PG].pdata =
			RTL8192CUPHY_REG_ARRAY_PG;
	पूर्ण
	/* 2T */
	rtlphy->hwparam_tables[PHY_REG_2T].length =
			RTL8192CUPHY_REG_2TARRAY_LENGTH;
	rtlphy->hwparam_tables[PHY_REG_2T].pdata =
			RTL8192CUPHY_REG_2TARRAY;
	rtlphy->hwparam_tables[RADIOA_2T].length =
			RTL8192CURADIOA_2TARRAYLENGTH;
	rtlphy->hwparam_tables[RADIOA_2T].pdata =
			RTL8192CURADIOA_2TARRAY;
	rtlphy->hwparam_tables[RADIOB_2T].length =
			RTL8192CURADIOB_2TARRAYLENGTH;
	rtlphy->hwparam_tables[RADIOB_2T].pdata =
			RTL8192CU_RADIOB_2TARRAY;
	rtlphy->hwparam_tables[AGCTAB_2T].length =
			RTL8192CUAGCTAB_2TARRAYLENGTH;
	rtlphy->hwparam_tables[AGCTAB_2T].pdata =
			RTL8192CUAGCTAB_2TARRAY;
	/* 1T */
	अगर (IS_HIGHT_PA(rtlefuse->board_type)) अणु
		rtlphy->hwparam_tables[PHY_REG_1T].length =
			RTL8192CUPHY_REG_1T_HPARRAYLENGTH;
		rtlphy->hwparam_tables[PHY_REG_1T].pdata =
			RTL8192CUPHY_REG_1T_HPARRAY;
		rtlphy->hwparam_tables[RADIOA_1T].length =
			RTL8192CURADIOA_1T_HPARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOA_1T].pdata =
			RTL8192CURADIOA_1T_HPARRAY;
		rtlphy->hwparam_tables[RADIOB_1T].length =
			RTL8192CURADIOB_1TARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOB_1T].pdata =
			RTL8192CU_RADIOB_1TARRAY;
		rtlphy->hwparam_tables[AGCTAB_1T].length =
			RTL8192CUAGCTAB_1T_HPARRAYLENGTH;
		rtlphy->hwparam_tables[AGCTAB_1T].pdata =
			RTL8192CUAGCTAB_1T_HPARRAY;
	पूर्ण अन्यथा अणु
		rtlphy->hwparam_tables[PHY_REG_1T].length =
			 RTL8192CUPHY_REG_1TARRAY_LENGTH;
		rtlphy->hwparam_tables[PHY_REG_1T].pdata =
			RTL8192CUPHY_REG_1TARRAY;
		rtlphy->hwparam_tables[RADIOA_1T].length =
			RTL8192CURADIOA_1TARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOA_1T].pdata =
			RTL8192CU_RADIOA_1TARRAY;
		rtlphy->hwparam_tables[RADIOB_1T].length =
			RTL8192CURADIOB_1TARRAYLENGTH;
		rtlphy->hwparam_tables[RADIOB_1T].pdata =
			RTL8192CU_RADIOB_1TARRAY;
		rtlphy->hwparam_tables[AGCTAB_1T].length =
			RTL8192CUAGCTAB_1TARRAYLENGTH;
		rtlphy->hwparam_tables[AGCTAB_1T].pdata =
			RTL8192CUAGCTAB_1TARRAY;
	पूर्ण
पूर्ण

अटल व्योम _rtl92cu_पढ़ो_txघातer_info_from_hwpg(काष्ठा ieee80211_hw *hw,
						 bool स्वतःload_fail,
						 u8 *hwinfo)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 rf_path, index, tempval;
	u16 i;

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 3; i++) अणु
			अगर (!स्वतःload_fail) अणु
				rtlefuse->
				    eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERCCK + rf_path * 3 + i];
				rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
				    hwinfo[EEPROM_TXPOWERHT40_1S + rf_path * 3 +
					   i];
			पूर्ण अन्यथा अणु
				rtlefuse->
				    eeprom_chnlarea_txpwr_cck[rf_path][i] =
				    EEPROM_DEFAULT_TXPOWERLEVEL;
				rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path][i] =
				    EEPROM_DEFAULT_TXPOWERLEVEL;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		अगर (!स्वतःload_fail)
			tempval = hwinfo[EEPROM_TXPOWERHT40_2SDIFF + i];
		अन्यथा
			tempval = EEPROM_DEFAULT_HT40_2SDIFF;
		rtlefuse->eprom_chnl_txpwr_ht40_2sdf[RF90_PATH_A][i] =
		    (tempval & 0xf);
		rtlefuse->eprom_chnl_txpwr_ht40_2sdf[RF90_PATH_B][i] =
		    ((tempval & 0xf0) >> 4);
	पूर्ण
	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM CCK Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eeprom_chnlarea_txpwr_cck[rf_path][i]);
	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 1S Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eeprom_chnlarea_txpwr_ht40_1s[rf_path][i]);
	क्रम (rf_path = 0; rf_path < 2; rf_path++)
		क्रम (i = 0; i < 3; i++)
			RTPRINT(rtlpriv, FINIT, INIT_EEPROM,
				"RF(%d) EEPROM HT40 2S Diff Area(%d) = 0x%x\n",
				rf_path, i,
				rtlefuse->
				eprom_chnl_txpwr_ht40_2sdf[rf_path][i]);
	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			index = rtl92c_get_chnl_group((u8)i);
			rtlefuse->txpwrlevel_cck[rf_path][i] =
			    rtlefuse->eeprom_chnlarea_txpwr_cck[rf_path][index];
			rtlefuse->txpwrlevel_ht40_1s[rf_path][i] =
			    rtlefuse->
			    eeprom_chnlarea_txpwr_ht40_1s[rf_path][index];
			अगर ((rtlefuse->
			     eeprom_chnlarea_txpwr_ht40_1s[rf_path][index] -
			     rtlefuse->
			     eprom_chnl_txpwr_ht40_2sdf[rf_path][index])
			    > 0) अणु
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i] =
				    rtlefuse->
				    eeprom_chnlarea_txpwr_ht40_1s[rf_path]
				    [index] - rtlefuse->
				    eprom_chnl_txpwr_ht40_2sdf[rf_path]
				    [index];
			पूर्ण अन्यथा अणु
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i] = 0;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < 14; i++) अणु
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF(%d)-Ch(%d) [CCK / HT40_1S / HT40_2S] = [0x%x / 0x%x / 0x%x]\n", rf_path, i,
				rtlefuse->txpwrlevel_cck[rf_path][i],
				rtlefuse->txpwrlevel_ht40_1s[rf_path][i],
				rtlefuse->txpwrlevel_ht40_2s[rf_path][i]);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 3; i++) अणु
		अगर (!स्वतःload_fail) अणु
			rtlefuse->eeprom_pwrlimit_ht40[i] =
			    hwinfo[EEPROM_TXPWR_GROUP + i];
			rtlefuse->eeprom_pwrlimit_ht20[i] =
			    hwinfo[EEPROM_TXPWR_GROUP + 3 + i];
		पूर्ण अन्यथा अणु
			rtlefuse->eeprom_pwrlimit_ht40[i] = 0;
			rtlefuse->eeprom_pwrlimit_ht20[i] = 0;
		पूर्ण
	पूर्ण
	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		क्रम (i = 0; i < 14; i++) अणु
			index = rtl92c_get_chnl_group((u8)i);
			अगर (rf_path == RF90_PATH_A) अणु
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				    (rtlefuse->eeprom_pwrlimit_ht20[index]
				     & 0xf);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				    (rtlefuse->eeprom_pwrlimit_ht40[index]
				     & 0xf);
			पूर्ण अन्यथा अगर (rf_path == RF90_PATH_B) अणु
				rtlefuse->pwrgroup_ht20[rf_path][i] =
				    ((rtlefuse->eeprom_pwrlimit_ht20[index]
				      & 0xf0) >> 4);
				rtlefuse->pwrgroup_ht40[rf_path][i] =
				    ((rtlefuse->eeprom_pwrlimit_ht40[index]
				      & 0xf0) >> 4);
			पूर्ण
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht20[%d] = 0x%x\n",
				rf_path, i,
				rtlefuse->pwrgroup_ht20[rf_path][i]);
			RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
				"RF-%d pwrgroup_ht40[%d] = 0x%x\n",
				rf_path, i,
				rtlefuse->pwrgroup_ht40[rf_path][i]);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 14; i++) अणु
		index = rtl92c_get_chnl_group((u8)i);
		अगर (!स्वतःload_fail)
			tempval = hwinfo[EEPROM_TXPOWERHT20DIFF + index];
		अन्यथा
			tempval = EEPROM_DEFAULT_HT20_DIFF;
		rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i] = (tempval & 0xF);
		rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i] =
		    ((tempval >> 4) & 0xF);
		अगर (rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i] & BIT(3))
			rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i] |= 0xF0;
		अगर (rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i] & BIT(3))
			rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i] |= 0xF0;
		index = rtl92c_get_chnl_group((u8)i);
		अगर (!स्वतःload_fail)
			tempval = hwinfo[EEPROM_TXPOWER_OFDMDIFF + index];
		अन्यथा
			tempval = EEPROM_DEFAULT_LEGACYHTTXPOWERDIFF;
		rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][i] = (tempval & 0xF);
		rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_B][i] =
		    ((tempval >> 4) & 0xF);
	पूर्ण
	rtlefuse->legacy_ht_txघातerdअगरf =
	    rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][7];
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-A Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-A Legacy to Ht40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Ht20 to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][i]);
	क्रम (i = 0; i < 14; i++)
		RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
			"RF-B Legacy to HT40 Diff[%d] = 0x%x\n",
			i, rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_B][i]);
	अगर (!स्वतःload_fail)
		rtlefuse->eeprom_regulatory = (hwinfo[RF_OPTION1] & 0x7);
	अन्यथा
		rtlefuse->eeprom_regulatory = 0;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"eeprom_regulatory = 0x%x\n", rtlefuse->eeprom_regulatory);
	अगर (!स्वतःload_fail) अणु
		rtlefuse->eeprom_tssi[RF90_PATH_A] = hwinfo[EEPROM_TSSI_A];
		rtlefuse->eeprom_tssi[RF90_PATH_B] = hwinfo[EEPROM_TSSI_B];
	पूर्ण अन्यथा अणु
		rtlefuse->eeprom_tssi[RF90_PATH_A] = EEPROM_DEFAULT_TSSI;
		rtlefuse->eeprom_tssi[RF90_PATH_B] = EEPROM_DEFAULT_TSSI;
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"TSSI_A = 0x%x, TSSI_B = 0x%x\n",
		rtlefuse->eeprom_tssi[RF90_PATH_A],
		rtlefuse->eeprom_tssi[RF90_PATH_B]);
	अगर (!स्वतःload_fail)
		tempval = hwinfo[EEPROM_THERMAL_METER];
	अन्यथा
		tempval = EEPROM_DEFAULT_THERMALMETER;
	rtlefuse->eeprom_thermalmeter = (tempval & 0x1f);
	अगर (rtlefuse->eeprom_thermalmeter < 0x06 ||
	    rtlefuse->eeprom_thermalmeter > 0x1c)
		rtlefuse->eeprom_thermalmeter = 0x12;
	अगर (rtlefuse->eeprom_thermalmeter == 0x1f || स्वतःload_fail)
		rtlefuse->apk_thermalmeterignore = true;
	rtlefuse->thermalmeter[0] = rtlefuse->eeprom_thermalmeter;
	RTPRINT(rtlpriv, FINIT, INIT_TXPOWER,
		"thermalmeter = 0x%x\n", rtlefuse->eeprom_thermalmeter);
पूर्ण

अटल व्योम _rtl92cu_पढ़ो_board_type(काष्ठा ieee80211_hw *hw, u8 *contents)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 boardtype;

	अगर (IS_NORMAL_CHIP(rtlhal->version)) अणु
		boardtype = ((contents[EEPROM_RF_OPT1]) &
			    BOARD_TYPE_NORMAL_MASK) >> 5; /*bit[7:5]*/
	पूर्ण अन्यथा अणु
		boardtype = contents[EEPROM_RF_OPT4];
		boardtype &= BOARD_TYPE_TEST_MASK;
	पूर्ण
	rtlefuse->board_type = boardtype;
	अगर (IS_HIGHT_PA(rtlefuse->board_type))
		rtlefuse->बाह्यal_pa = 1;
	pr_info("Board Type %x\n", rtlefuse->board_type);
पूर्ण

अटल व्योम _rtl92cu_पढ़ो_adapter_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	पूर्णांक params[] = अणुRTL8190_EEPROM_ID, EEPROM_VID, EEPROM_DID,
			EEPROM_SVID, EEPROM_SMID, EEPROM_MAC_ADDR,
			EEPROM_CHANNELPLAN, EEPROM_VERSION, EEPROM_CUSTOMER_ID,
			0पूर्ण;
	u8 *hwinfo;

	hwinfo = kzalloc(HWSET_MAX_SIZE, GFP_KERNEL);
	अगर (!hwinfo)
		वापस;

	अगर (rtl_get_hwinfo(hw, rtlpriv, HWSET_MAX_SIZE, hwinfo, params))
		जाओ निकास;

	_rtl92cu_पढ़ो_txघातer_info_from_hwpg(hw,
					   rtlefuse->स्वतःload_failflag, hwinfo);
	_rtl92cu_पढ़ो_board_type(hw, hwinfo);

	rtlefuse->txpwr_fromeprom = true;
	अगर (rtlhal->oem_id == RT_CID_DEFAULT) अणु
		चयन (rtlefuse->eeprom_oemid) अणु
		हाल EEPROM_CID_DEFAULT:
			अगर (rtlefuse->eeprom_did == 0x8176) अणु
				अगर ((rtlefuse->eeprom_svid == 0x103C &&
				     rtlefuse->eeprom_smid == 0x1629))
					rtlhal->oem_id = RT_CID_819X_HP;
				अन्यथा
					rtlhal->oem_id = RT_CID_DEFAULT;
			पूर्ण अन्यथा अणु
				rtlhal->oem_id = RT_CID_DEFAULT;
			पूर्ण
			अवरोध;
		हाल EEPROM_CID_TOSHIBA:
			rtlhal->oem_id = RT_CID_TOSHIBA;
			अवरोध;
		हाल EEPROM_CID_QMI:
			rtlhal->oem_id = RT_CID_819X_QMI;
			अवरोध;
		हाल EEPROM_CID_WHQL:
		शेष:
			rtlhal->oem_id = RT_CID_DEFAULT;
			अवरोध;
		पूर्ण
	पूर्ण
निकास:
	kमुक्त(hwinfo);
पूर्ण

अटल व्योम _rtl92cu_hal_customized_behavior(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	चयन (rtlhal->oem_id) अणु
	हाल RT_CID_819X_HP:
		rtlpriv->ledctl.led_खोलोdrain = true;
		अवरोध;
	हाल RT_CID_819X_LENOVO:
	हाल RT_CID_DEFAULT:
	हाल RT_CID_TOSHIBA:
	हाल RT_CID_CCX:
	हाल RT_CID_819X_ACER:
	हाल RT_CID_WHQL:
	शेष:
		अवरोध;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "RT Customized ID: 0x%02X\n",
		rtlhal->oem_id);
पूर्ण

व्योम rtl92cu_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw)
अणु

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_u1b;

	अगर (!IS_NORMAL_CHIP(rtlhal->version))
		वापस;
	पंचांगp_u1b = rtl_पढ़ो_byte(rtlpriv, REG_9346CR);
	rtlefuse->epromtype = (पंचांगp_u1b & BOOT_FROM_EEPROM) ?
			       EEPROM_93C46 : EEPROM_BOOT_EFUSE;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "Boot from %s\n",
		पंचांगp_u1b & BOOT_FROM_EEPROM ? "EERROM" : "EFUSE");
	rtlefuse->स्वतःload_failflag = (पंचांगp_u1b & EEPROM_EN) ? false : true;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Autoload %s\n",
		पंचांगp_u1b & EEPROM_EN ? "OK!!" : "ERR!!");
	_rtl92cu_पढ़ो_adapter_info(hw);
	_rtl92cu_hal_customized_behavior(hw);
	वापस;
पूर्ण

अटल पूर्णांक _rtl92cu_init_घातer_on(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक		status = 0;
	u16		value16;
	u8		value8;
	/*  polling स्वतःload करोne. */
	u32	pollingcount = 0;

	करो अणु
		अगर (rtl_पढ़ो_byte(rtlpriv, REG_APS_FSMCO) & PFM_ALDN) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"Autoload Done!\n");
			अवरोध;
		पूर्ण
		अगर (pollingcount++ > 100) अणु
			pr_err("Failed to polling REG_APS_FSMCO[PFM_ALDN] done!\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण जबतक (true);
	/* 0. RSV_CTRL 0x1C[7:0] = 0 unlock ISO/CLK/Power control रेजिस्टर */
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0);
	/* Power on when re-enter from IPS/Radio off/card disable */
	/* enable SPS पूर्णांकo PWM mode */
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	udelay(100);
	value8 = rtl_पढ़ो_byte(rtlpriv, REG_LDOV12D_CTRL);
	अगर (0 == (value8 & LDV12_EN)) अणु
		value8 |= LDV12_EN;
		rtl_ग_लिखो_byte(rtlpriv, REG_LDOV12D_CTRL, value8);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
			" power-on :REG_LDOV12D_CTRL Reg0x21:0x%02x\n",
			value8);
		udelay(100);
		value8 = rtl_पढ़ो_byte(rtlpriv, REG_SYS_ISO_CTRL);
		value8 &= ~ISO_MD2PP;
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL, value8);
	पूर्ण
	/*  स्वतः enable WLAN */
	pollingcount = 0;
	value16 = rtl_पढ़ो_word(rtlpriv, REG_APS_FSMCO);
	value16 |= APFM_ONMAC;
	rtl_ग_लिखो_word(rtlpriv, REG_APS_FSMCO, value16);
	करो अणु
		अगर (!(rtl_पढ़ो_word(rtlpriv, REG_APS_FSMCO) & APFM_ONMAC)) अणु
			pr_info("MAC auto ON okay!\n");
			अवरोध;
		पूर्ण
		अगर (pollingcount++ > 1000) अणु
			pr_err("Failed to polling REG_APS_FSMCO[APFM_ONMAC] done!\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण जबतक (true);
	/* Enable Radio ,GPIO ,and LED function */
	rtl_ग_लिखो_word(rtlpriv, REG_APS_FSMCO, 0x0812);
	/* release RF digital isolation */
	value16 = rtl_पढ़ो_word(rtlpriv, REG_SYS_ISO_CTRL);
	value16 &= ~ISO_DIOR;
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_ISO_CTRL, value16);
	/* Reconsider when to करो this operation after asking HWSD. */
	pollingcount = 0;
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, (rtl_पढ़ो_byte(rtlpriv,
						REG_APSD_CTRL) & ~BIT(6)));
	करो अणु
		pollingcount++;
	पूर्ण जबतक ((pollingcount < 200) &&
		 (rtl_पढ़ो_byte(rtlpriv, REG_APSD_CTRL) & BIT(7)));
	/* Enable MAC DMA/WMAC/SCHEDULE/SEC block */
	value16 = rtl_पढ़ो_word(rtlpriv,  REG_CR);
	value16 |= (HCI_TXDMA_EN | HCI_RXDMA_EN | TXDMA_EN | RXDMA_EN |
		    PROTOCOL_EN | SCHEDULE_EN | MACTXEN | MACRXEN | ENSEC);
	rtl_ग_लिखो_word(rtlpriv, REG_CR, value16);
	वापस status;
पूर्ण

अटल व्योम _rtl92cu_init_queue_reserved_page(काष्ठा ieee80211_hw *hw,
					      bool wmm_enable,
					      u8 out_ep_num,
					      u8 queue_sel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool ischipn = IS_NORMAL_CHIP(rtlhal->version);
	u32 outepnum = (u32)out_ep_num;
	u32 numhq = 0;
	u32 numlq = 0;
	u32 numnq = 0;
	u32 numpubq;
	u32 value32;
	u8 value8;
	u32 txqpagक्रमागत, txqpageunit, txqreमुख्यinpage;

	अगर (!wmm_enable) अणु
		numpubq = (ischipn) ? CHIP_B_PAGE_NUM_PUBQ :
			  CHIP_A_PAGE_NUM_PUBQ;
		txqpagक्रमागत = TX_TOTAL_PAGE_NUMBER - numpubq;

		txqpageunit = txqpagक्रमागत / outepnum;
		txqreमुख्यinpage = txqpagक्रमागत % outepnum;
		अगर (queue_sel & TX_SELE_HQ)
			numhq = txqpageunit;
		अगर (queue_sel & TX_SELE_LQ)
			numlq = txqpageunit;
		/* HIGH priority queue always present in the configuration of
		 * 2 out-ep. Reमुख्यder pages have asचिन्हित to High queue */
		अगर (outepnum > 1 && txqreमुख्यinpage)
			numhq += txqreमुख्यinpage;
		/* NOTE: This step करोne beक्रमe writting REG_RQPN. */
		अगर (ischipn) अणु
			अगर (queue_sel & TX_SELE_NQ)
				numnq = txqpageunit;
			value8 = (u8)_NPQ(numnq);
			rtl_ग_लिखो_byte(rtlpriv,  REG_RQPN_NPQ, value8);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* क्रम WMM ,number of out-ep must more than or equal to 2! */
		numpubq = ischipn ? WMM_CHIP_B_PAGE_NUM_PUBQ :
			  WMM_CHIP_A_PAGE_NUM_PUBQ;
		अगर (queue_sel & TX_SELE_HQ) अणु
			numhq = ischipn ? WMM_CHIP_B_PAGE_NUM_HPQ :
				WMM_CHIP_A_PAGE_NUM_HPQ;
		पूर्ण
		अगर (queue_sel & TX_SELE_LQ) अणु
			numlq = ischipn ? WMM_CHIP_B_PAGE_NUM_LPQ :
				WMM_CHIP_A_PAGE_NUM_LPQ;
		पूर्ण
		/* NOTE: This step करोne beक्रमe writting REG_RQPN. */
		अगर (ischipn) अणु
			अगर (queue_sel & TX_SELE_NQ)
				numnq = WMM_CHIP_B_PAGE_NUM_NPQ;
			value8 = (u8)_NPQ(numnq);
			rtl_ग_लिखो_byte(rtlpriv, REG_RQPN_NPQ, value8);
		पूर्ण
	पूर्ण
	/* TX DMA */
	value32 = _HPQ(numhq) | _LPQ(numlq) | _PUBQ(numpubq) | LD_RQPN;
	rtl_ग_लिखो_dword(rtlpriv, REG_RQPN, value32);
पूर्ण

अटल व्योम _rtl92c_init_trx_buffer(काष्ठा ieee80211_hw *hw, bool wmm_enable)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8	txpktbuf_bndy;
	u8	value8;

	अगर (!wmm_enable)
		txpktbuf_bndy = TX_PAGE_BOUNDARY;
	अन्यथा /* क्रम WMM */
		txpktbuf_bndy = (IS_NORMAL_CHIP(rtlhal->version))
						? WMM_CHIP_B_TX_PAGE_BOUNDARY
						: WMM_CHIP_A_TX_PAGE_BOUNDARY;
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPKTBUF_WMAC_LBK_BF_HD, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TRXFF_BNDY, txpktbuf_bndy);
	rtl_ग_लिखो_byte(rtlpriv, REG_TDECTRL+1, txpktbuf_bndy);
	rtl_ग_लिखो_word(rtlpriv,  (REG_TRXFF_BNDY + 2), 0x27FF);
	value8 = _PSRX(RX_PAGE_SIZE_REG_VALUE) | _PSTX(PBP_128);
	rtl_ग_लिखो_byte(rtlpriv, REG_PBP, value8);
पूर्ण

अटल व्योम _rtl92c_init_chipn_reg_priority(काष्ठा ieee80211_hw *hw, u16 beq,
					    u16 bkq, u16 viq, u16 voq,
					    u16 mgtq, u16 hiq)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 value16 = (rtl_पढ़ो_word(rtlpriv, REG_TRXDMA_CTRL) & 0x7);

	value16 |= _TXDMA_BEQ_MAP(beq) | _TXDMA_BKQ_MAP(bkq) |
		   _TXDMA_VIQ_MAP(viq) | _TXDMA_VOQ_MAP(voq) |
		   _TXDMA_MGQ_MAP(mgtq) | _TXDMA_HIQ_MAP(hiq);
	rtl_ग_लिखो_word(rtlpriv,  REG_TRXDMA_CTRL, value16);
पूर्ण

अटल व्योम _rtl92cu_init_chipn_one_out_ep_priority(काष्ठा ieee80211_hw *hw,
						    bool wmm_enable,
						    u8 queue_sel)
अणु
	u16 value;

	चयन (queue_sel) अणु
	हाल TX_SELE_HQ:
		value = QUEUE_HIGH;
		अवरोध;
	हाल TX_SELE_LQ:
		value = QUEUE_LOW;
		अवरोध;
	हाल TX_SELE_NQ:
		value = QUEUE_NORMAL;
		अवरोध;
	शेष:
		WARN_ON(1); /* Shall not reach here! */
		वापस;
	पूर्ण
	_rtl92c_init_chipn_reg_priority(hw, value, value, value, value,
					value, value);
	pr_info("Tx queue select: 0x%02x\n", queue_sel);
पूर्ण

अटल व्योम _rtl92cu_init_chipn_two_out_ep_priority(काष्ठा ieee80211_hw *hw,
						     bool wmm_enable,
						     u8 queue_sel)
अणु
	u16 beq, bkq, viq, voq, mgtq, hiq;
	u16 valuehi;
	u16 valuelow;

	चयन (queue_sel) अणु
	हाल (TX_SELE_HQ | TX_SELE_LQ):
		valuehi = QUEUE_HIGH;
		valuelow = QUEUE_LOW;
		अवरोध;
	हाल (TX_SELE_NQ | TX_SELE_LQ):
		valuehi = QUEUE_NORMAL;
		valuelow = QUEUE_LOW;
		अवरोध;
	हाल (TX_SELE_HQ | TX_SELE_NQ):
		valuehi = QUEUE_HIGH;
		valuelow = QUEUE_NORMAL;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
	अगर (!wmm_enable) अणु
		beq = valuelow;
		bkq = valuelow;
		viq = valuehi;
		voq = valuehi;
		mgtq = valuehi;
		hiq = valuehi;
	पूर्ण अन्यथा अणु/* क्रम WMM ,CONFIG_OUT_EP_WIFI_MODE */
		beq = valuehi;
		bkq = valuelow;
		viq = valuelow;
		voq = valuehi;
		mgtq = valuehi;
		hiq = valuehi;
	पूर्ण
	_rtl92c_init_chipn_reg_priority(hw, beq, bkq, viq, voq, mgtq, hiq);
	pr_info("Tx queue select: 0x%02x\n", queue_sel);
पूर्ण

अटल व्योम _rtl92cu_init_chipn_three_out_ep_priority(काष्ठा ieee80211_hw *hw,
						      bool wmm_enable,
						      u8 queue_sel)
अणु
	u16 beq, bkq, viq, voq, mgtq, hiq;

	अगर (!wmm_enable) अणु /* typical setting */
		beq	= QUEUE_LOW;
		bkq	= QUEUE_LOW;
		viq	= QUEUE_NORMAL;
		voq	= QUEUE_HIGH;
		mgtq	= QUEUE_HIGH;
		hiq	= QUEUE_HIGH;
	पूर्ण अन्यथा अणु /* क्रम WMM */
		beq	= QUEUE_LOW;
		bkq	= QUEUE_NORMAL;
		viq	= QUEUE_NORMAL;
		voq	= QUEUE_HIGH;
		mgtq	= QUEUE_HIGH;
		hiq	= QUEUE_HIGH;
	पूर्ण
	_rtl92c_init_chipn_reg_priority(hw, beq, bkq, viq, voq, mgtq, hiq);
	pr_info("Tx queue select :0x%02x..\n", queue_sel);
पूर्ण

अटल व्योम _rtl92cu_init_chipn_queue_priority(काष्ठा ieee80211_hw *hw,
					       bool wmm_enable,
					       u8 out_ep_num,
					       u8 queue_sel)
अणु
	चयन (out_ep_num) अणु
	हाल 1:
		_rtl92cu_init_chipn_one_out_ep_priority(hw, wmm_enable,
							queue_sel);
		अवरोध;
	हाल 2:
		_rtl92cu_init_chipn_two_out_ep_priority(hw, wmm_enable,
							queue_sel);
		अवरोध;
	हाल 3:
		_rtl92cu_init_chipn_three_out_ep_priority(hw, wmm_enable,
							  queue_sel);
		अवरोध;
	शेष:
		WARN_ON(1); /* Shall not reach here! */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl92cu_init_chipt_queue_priority(काष्ठा ieee80211_hw *hw,
					       bool wmm_enable,
					       u8 out_ep_num,
					       u8 queue_sel)
अणु
	u8 hq_sele = 0;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	चयन (out_ep_num) अणु
	हाल 2:	/* (TX_SELE_HQ|TX_SELE_LQ) */
		अगर (!wmm_enable) /* typical setting */
			hq_sele =  HQSEL_VOQ | HQSEL_VIQ | HQSEL_MGTQ |
				   HQSEL_HIQ;
		अन्यथा	/* क्रम WMM */
			hq_sele = HQSEL_VOQ | HQSEL_BEQ | HQSEL_MGTQ |
				  HQSEL_HIQ;
		अवरोध;
	हाल 1:
		अगर (TX_SELE_LQ == queue_sel) अणु
			/* map all endpoपूर्णांक to Low queue */
			hq_sele = 0;
		पूर्ण अन्यथा अगर (TX_SELE_HQ == queue_sel) अणु
			/* map all endpoपूर्णांक to High queue */
			hq_sele =  HQSEL_VOQ | HQSEL_VIQ | HQSEL_BEQ |
				   HQSEL_BKQ | HQSEL_MGTQ | HQSEL_HIQ;
		पूर्ण
		अवरोध;
	शेष:
		WARN_ON(1); /* Shall not reach here! */
		अवरोध;
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, (REG_TRXDMA_CTRL+1), hq_sele);
	pr_info("Tx queue select :0x%02x..\n", hq_sele);
पूर्ण

अटल व्योम _rtl92cu_init_queue_priority(काष्ठा ieee80211_hw *hw,
						bool wmm_enable,
						u8 out_ep_num,
						u8 queue_sel)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (IS_NORMAL_CHIP(rtlhal->version))
		_rtl92cu_init_chipn_queue_priority(hw, wmm_enable, out_ep_num,
						   queue_sel);
	अन्यथा
		_rtl92cu_init_chipt_queue_priority(hw, wmm_enable, out_ep_num,
						   queue_sel);
पूर्ण

अटल व्योम _rtl92cu_init_wmac_setting(काष्ठा ieee80211_hw *hw)
अणु
	u16 value16;
	u32 value32;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	value32 = (RCR_APM | RCR_AM | RCR_ADF | RCR_AB | RCR_APPFCS |
		   RCR_APP_ICV | RCR_AMF | RCR_HTC_LOC_CTRL |
		   RCR_APP_MIC | RCR_APP_PHYSTS | RCR_ACRC32);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR, (u8 *)(&value32));
	/* Accept all multicast address */
	rtl_ग_लिखो_dword(rtlpriv,  REG_MAR, 0xFFFFFFFF);
	rtl_ग_लिखो_dword(rtlpriv,  REG_MAR + 4, 0xFFFFFFFF);
	/* Accept all management frames */
	value16 = 0xFFFF;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_MGT_FILTER,
				      (u8 *)(&value16));
	/* Reject all control frame - शेष value is 0 */
	value16 = 0x0;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_CTRL_FILTER,
				      (u8 *)(&value16));
	/* Accept all data frames */
	value16 = 0xFFFF;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_DATA_FILTER,
				      (u8 *)(&value16));
पूर्ण

अटल व्योम _rtl92cu_init_beacon_parameters(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	rtl_ग_लिखो_word(rtlpriv, REG_BCN_CTRL, 0x1010);

	/* TODO: Remove these magic number */
	rtl_ग_लिखो_word(rtlpriv, REG_TBTT_PROHIBIT, 0x6404);
	rtl_ग_लिखो_byte(rtlpriv, REG_DRVERLYINT, DRIVER_EARLY_INT_TIME);
	rtl_ग_लिखो_byte(rtlpriv, REG_BCNDMATIM, BCN_DMA_ATIME_INT_TIME);
	/* Change beacon AIFS to the largest number
	 * beacause test chip करोes not contension beक्रमe sending beacon.
	 */
	अगर (IS_NORMAL_CHIP(rtlhal->version))
		rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x660F);
	अन्यथा
		rtl_ग_लिखो_word(rtlpriv, REG_BCNTCFG, 0x66FF);
पूर्ण

अटल पूर्णांक _rtl92cu_init_mac(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(usb_priv);
	पूर्णांक err = 0;
	u32	boundary = 0;
	u8 wmm_enable = false; /* TODO */
	u8 out_ep_nums = rtlusb->out_ep_nums;
	u8 queue_sel = rtlusb->out_queue_sel;

	err = _rtl92cu_init_घातer_on(hw);

	अगर (err) अणु
		pr_err("Failed to init power on!\n");
		वापस err;
	पूर्ण
	अगर (!wmm_enable) अणु
		boundary = TX_PAGE_BOUNDARY;
	पूर्ण अन्यथा अणु /* क्रम WMM */
		boundary = (IS_NORMAL_CHIP(rtlhal->version))
					? WMM_CHIP_B_TX_PAGE_BOUNDARY
					: WMM_CHIP_A_TX_PAGE_BOUNDARY;
	पूर्ण
	अगर (!rtl92c_init_llt_table(hw, boundary)) अणु
		pr_err("Failed to init LLT Table!\n");
		वापस -EINVAL;
	पूर्ण
	_rtl92cu_init_queue_reserved_page(hw, wmm_enable, out_ep_nums,
					  queue_sel);
	_rtl92c_init_trx_buffer(hw, wmm_enable);
	_rtl92cu_init_queue_priority(hw, wmm_enable, out_ep_nums,
				     queue_sel);
	/* Get Rx PHY status in order to report RSSI and others. */
	rtl92c_init_driver_info_size(hw, RTL92C_DRIVER_INFO_SIZE);
	rtl92c_init_पूर्णांकerrupt(hw);
	rtl92c_init_network_type(hw);
	_rtl92cu_init_wmac_setting(hw);
	rtl92c_init_adaptive_ctrl(hw);
	rtl92c_init_edca(hw);
	rtl92c_init_rate_fallback(hw);
	rtl92c_init_retry_function(hw);
	rtlpriv->cfg->ops->set_bw_mode(hw, NL80211_CHAN_HT20);
	rtl92c_set_min_space(hw, IS_92C_SERIAL(rtlhal->version));
	_rtl92cu_init_beacon_parameters(hw);
	rtl92c_init_ampdu_aggregation(hw);
	rtl92c_init_beacon_max_error(hw);
	वापस err;
पूर्ण

व्योम rtl92cu_enable_hw_security_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 sec_reg_value = 0x0;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"PairwiseEncAlgorithm = %d GroupEncAlgorithm = %d\n",
		rtlpriv->sec.pairwise_enc_algorithm,
		rtlpriv->sec.group_enc_algorithm);
	अगर (rtlpriv->cfg->mod_params->sw_crypto || rtlpriv->sec.use_sw_sec) अणु
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
			"not open sw encryption\n");
		वापस;
	पूर्ण
	sec_reg_value = SCR_TXENCENABLE | SCR_RXDECENABLE;
	अगर (rtlpriv->sec.use_शेषkey) अणु
		sec_reg_value |= SCR_TXUSEDK;
		sec_reg_value |= SCR_RXUSEDK;
	पूर्ण
	अगर (IS_NORMAL_CHIP(rtlhal->version))
		sec_reg_value |= (SCR_RXBCUSEDK | SCR_TXBCUSEDK);
	rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, 0x02);
	rtl_dbg(rtlpriv, COMP_SEC, DBG_LOUD, "The SECR-value %x\n",
		sec_reg_value);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_WPA_CONFIG, &sec_reg_value);
पूर्ण

अटल व्योम _rtl92cu_hw_configure(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	/* To Fix MAC loopback mode fail. */
	rtl_ग_लिखो_byte(rtlpriv, REG_LDOHCI12_CTRL, 0x0f);
	rtl_ग_लिखो_byte(rtlpriv, 0x15, 0xe9);
	/* HW SEQ CTRL */
	/* set 0x0 to 0xFF by tynli. Default enable HW SEQ NUM. */
	rtl_ग_लिखो_byte(rtlpriv, REG_HWSEQ_CTRL, 0xFF);
	/* fixed USB पूर्णांकerface पूर्णांकerference issue */
	rtl_ग_लिखो_byte(rtlpriv, 0xfe40, 0xe0);
	rtl_ग_लिखो_byte(rtlpriv, 0xfe41, 0x8d);
	rtl_ग_लिखो_byte(rtlpriv, 0xfe42, 0x80);
	rtlusb->reg_bcn_ctrl_val = 0x18;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlusb->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _initpabias(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 pa_setting;

	/* FIXED PA current issue */
	pa_setting = efuse_पढ़ो_1byte(hw, 0x1FA);
	अगर (!(pa_setting & BIT(0))) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0FFFFF, 0x0F406);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0FFFFF, 0x4F406);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0FFFFF, 0x8F406);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x15, 0x0FFFFF, 0xCF406);
	पूर्ण
	अगर (!(pa_setting & BIT(1)) && IS_NORMAL_CHIP(rtlhal->version) &&
	    IS_92C_SERIAL(rtlhal->version)) अणु
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0FFFFF, 0x0F406);
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0FFFFF, 0x4F406);
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0FFFFF, 0x8F406);
		rtl_set_rfreg(hw, RF90_PATH_B, 0x15, 0x0FFFFF, 0xCF406);
	पूर्ण
	अगर (!(pa_setting & BIT(4))) अणु
		pa_setting = rtl_पढ़ो_byte(rtlpriv, 0x16);
		pa_setting &= 0x0F;
		rtl_ग_लिखो_byte(rtlpriv, 0x16, pa_setting | 0x90);
	पूर्ण
पूर्ण

पूर्णांक rtl92cu_hw_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;

	/* As this function can take a very दीर्घ समय (up to 350 ms)
	 * and can be called with irqs disabled, reenable the irqs
	 * to let the other devices जारी being serviced.
	 *
	 * It is safe करोing so since our own पूर्णांकerrupts will only be enabled
	 * in a subsequent step.
	 */
	local_save_flags(flags);
	local_irq_enable();

	rtlhal->fw_पढ़ोy = false;
	rtlhal->hw_type = HARDWARE_TYPE_RTL8192CU;
	err = _rtl92cu_init_mac(hw);
	अगर (err) अणु
		pr_err("init mac failed!\n");
		जाओ निकास;
	पूर्ण
	err = rtl92c_करोwnload_fw(hw);
	अगर (err) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Failed to download FW. Init HW without FW now..\n");
		err = 1;
		जाओ निकास;
	पूर्ण

	rtlhal->fw_पढ़ोy = true;
	rtlhal->last_hmeboxnum = 0; /* h2c */
	_rtl92cu_phy_param_tab_init(hw);
	rtl92cu_phy_mac_config(hw);
	rtl92cu_phy_bb_config(hw);
	rtlphy->rf_mode = RF_OP_BY_SW_3WIRE;
	rtl92c_phy_rf_config(hw);
	अगर (IS_VENDOR_UMC_A_CUT(rtlhal->version) &&
	    !IS_92C_SERIAL(rtlhal->version)) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G1, MASKDWORD, 0x30255);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_RX_G2, MASKDWORD, 0x50a00);
	पूर्ण
	rtlphy->rfreg_chnlval[0] = rtl_get_rfreg(hw, (क्रमागत radio_path)0,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtlphy->rfreg_chnlval[1] = rtl_get_rfreg(hw, (क्रमागत radio_path)1,
						 RF_CHNLBW, RFREG_OFFSET_MASK);
	rtl92cu_bb_block_on(hw);
	rtl_cam_reset_all_entry(hw);
	rtl92cu_enable_hw_security_config(hw);
	ppsc->rfpwr_state = ERFON;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);
	अगर (ppsc->rfpwr_state == ERFON) अणु
		rtl92c_phy_set_rfpath_चयन(hw, 1);
		अगर (rtlphy->iqk_initialized) अणु
			rtl92c_phy_iq_calibrate(hw, true);
		पूर्ण अन्यथा अणु
			rtl92c_phy_iq_calibrate(hw, false);
			rtlphy->iqk_initialized = true;
		पूर्ण
		rtl92c_dm_check_txघातer_tracking(hw);
		rtl92c_phy_lc_calibrate(hw);
	पूर्ण
	_rtl92cu_hw_configure(hw);
	_initpabias(hw);
	rtl92c_dm_init(hw);
निकास:
	local_irq_restore(flags);
	वापस err;
पूर्ण

अटल व्योम disable_rfafeandresetbb(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
/**************************************
a.	TXPAUSE 0x522[7:0] = 0xFF	Pause MAC TX queue
b.	RF path 0 offset 0x00 = 0x00	disable RF
c.	APSD_CTRL 0x600[7:0] = 0x40
d.	SYS_FUNC_EN 0x02[7:0] = 0x16	reset BB state machine
e.	SYS_FUNC_EN 0x02[7:0] = 0x14	reset BB state machine
***************************************/
	u8 erfpath = 0, value8 = 0;

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_rfreg(hw, (क्रमागत radio_path)erfpath, 0x0, MASKBYTE0, 0x0);

	value8 |= APSDOFF;
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, value8); /*0x40*/
	value8 = 0;
	value8 |= (FEN_USBD | FEN_USBA | FEN_BB_GLB_RSTN);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, value8);/*0x16*/
	value8 &= (~FEN_BB_GLB_RSTN);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, value8); /*0x14*/
पूर्ण

अटल व्योम  _resetdigitalprocedure1(काष्ठा ieee80211_hw *hw, bool withouthwsm)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlhal->fw_version <=  0x20) अणु
		/*****************************
		f. MCUFWDL 0x80[7:0]=0		reset MCU पढ़ोy status
		g. SYS_FUNC_EN 0x02[10]= 0	reset MCU reg, (8051 reset)
		h. SYS_FUNC_EN 0x02[15-12]= 5	reset MAC reg, DCORE
		i. SYS_FUNC_EN 0x02[10]= 1	enable MCU reg, (8051 enable)
		******************************/
		u16 valu16 = 0;

		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0);
		valu16 = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
		rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (valu16 &
			       (~FEN_CPUEN))); /* reset MCU ,8051 */
		valu16 = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN)&0x0FFF;
		rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (valu16 |
			      (FEN_HWPDN|FEN_ELDR))); /* reset MAC */
		valu16 = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
		rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN, (valu16 |
			       FEN_CPUEN)); /* enable MCU ,8051 */
	पूर्ण अन्यथा अणु
		u8 retry_cnts = 0;

		/* IF fw in RAM code, करो reset */
		अगर (rtl_पढ़ो_byte(rtlpriv, REG_MCUFWDL) & BIT(1)) अणु
			/* reset MCU पढ़ोy status */
			rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0);
			/* 8051 reset by self */
			rtl_ग_लिखो_byte(rtlpriv, REG_HMETFR+3, 0x20);
			जबतक ((retry_cnts++ < 100) &&
			       (FEN_CPUEN & rtl_पढ़ो_word(rtlpriv,
			       REG_SYS_FUNC_EN))) अणु
				udelay(50);
			पूर्ण
			अगर (retry_cnts >= 100) अणु
				pr_err("8051 reset failed!.........................\n");
				/* अगर 8051 reset fail, reset MAC. */
				rtl_ग_लिखो_byte(rtlpriv,
					       REG_SYS_FUNC_EN + 1,
					       0x50);
				udelay(100);
			पूर्ण
		पूर्ण
		/* Reset MAC and Enable 8051 */
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN + 1, 0x54);
		rtl_ग_लिखो_byte(rtlpriv, REG_MCUFWDL, 0);
	पूर्ण
	अगर (withouthwsm) अणु
		/*****************************
		  Without HW स्वतः state machine
		g.SYS_CLKR 0x08[15:0] = 0x30A3		disable MAC घड़ी
		h.AFE_PLL_CTRL 0x28[7:0] = 0x80		disable AFE PLL
		i.AFE_XTAL_CTRL 0x24[15:0] = 0x880F	gated AFE DIG_CLOCK
		j.SYS_ISu_CTRL 0x00[7:0] = 0xF9		isolated digital to PON
		******************************/
		rtl_ग_लिखो_word(rtlpriv, REG_SYS_CLKR, 0x70A3);
		rtl_ग_लिखो_byte(rtlpriv, REG_AFE_PLL_CTRL, 0x80);
		rtl_ग_लिखो_word(rtlpriv, REG_AFE_XTAL_CTRL, 0x880F);
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL, 0xF9);
	पूर्ण
पूर्ण

अटल व्योम _resetdigitalprocedure2(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
/*****************************
k. SYS_FUNC_EN 0x03[7:0] = 0x44		disable ELDR runction
l. SYS_CLKR 0x08[15:0] = 0x3083		disable ELDR घड़ी
m. SYS_ISO_CTRL 0x01[7:0] = 0x83	isolated ELDR to PON
******************************/
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_CLKR, 0x70A3);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_ISO_CTRL+1, 0x82);
पूर्ण

अटल व्योम _disablegpio(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
/***************************************
j. GPIO_PIN_CTRL 0x44[31:0]=0x000
k. Value = GPIO_PIN_CTRL[7:0]
l.  GPIO_PIN_CTRL 0x44[31:0] = 0x00FF0000 | (value <<8); ग_लिखो ext PIN level
m. GPIO_MUXCFG 0x42 [15:0] = 0x0780
n. LEDCFG 0x4C[15:0] = 0x8080
***************************************/
	u8	value8;
	u16	value16;
	u32	value32;

	/* 1. Disable GPIO[7:0] */
	rtl_ग_लिखो_word(rtlpriv, REG_GPIO_PIN_CTRL+2, 0x0000);
	value32 = rtl_पढ़ो_dword(rtlpriv, REG_GPIO_PIN_CTRL) & 0xFFFF00FF;
	value8 = (u8)(value32&0x000000FF);
	value32 |= ((value8<<8) | 0x00FF0000);
	rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, value32);
	/* 2. Disable GPIO[10:8] */
	rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG+3, 0x00);
	value16 = rtl_पढ़ो_word(rtlpriv, REG_GPIO_MUXCFG+2) & 0xFF0F;
	value8 = (u8)(value16&0x000F);
	value16 |= ((value8<<4) | 0x0780);
	rtl_ग_लिखो_word(rtlpriv, REG_GPIO_PIN_CTRL+2, value16);
	/* 3. Disable LED0 & 1 */
	rtl_ग_लिखो_word(rtlpriv, REG_LEDCFG0, 0x8080);
पूर्ण

अटल व्योम disable_analog(काष्ठा ieee80211_hw *hw, bool withouthwsm)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 value16 = 0;
	u8 value8 = 0;

	अगर (withouthwsm) अणु
		/*****************************
		n. LDOA15_CTRL 0x20[7:0] = 0x04	 disable A15 घातer
		o. LDOV12D_CTRL 0x21[7:0] = 0x54 disable digital core घातer
		r. When driver call disable, the ASIC will turn off reमुख्यing
		   घड़ी स्वतःmatically
		******************************/
		rtl_ग_लिखो_byte(rtlpriv, REG_LDOA15_CTRL, 0x04);
		value8 = rtl_पढ़ो_byte(rtlpriv, REG_LDOV12D_CTRL);
		value8 &= (~LDV12_EN);
		rtl_ग_लिखो_byte(rtlpriv, REG_LDOV12D_CTRL, value8);
	पूर्ण

/*****************************
h. SPS0_CTRL 0x11[7:0] = 0x23		enter PFM mode
i. APS_FSMCO 0x04[15:0] = 0x4802	set USB suspend
******************************/
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x23);
	value16 |= (APDM_HOST | AFSM_HSUS | PFM_ALDN);
	rtl_ग_लिखो_word(rtlpriv, REG_APS_FSMCO, (u16)value16);
	rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0E);
पूर्ण

अटल व्योम carddisable_hwsm(काष्ठा ieee80211_hw *hw)
अणु
	/* ==== RF Off Sequence ==== */
	disable_rfafeandresetbb(hw);
	/* ==== Reset digital sequence   ====== */
	_resetdigitalprocedure1(hw, false);
	/*  ==== Pull GPIO PIN to balance level and LED control ====== */
	_disablegpio(hw);
	/* ==== Disable analog sequence === */
	disable_analog(hw, false);
पूर्ण

अटल व्योम carddisablewithout_hwsm(काष्ठा ieee80211_hw *hw)
अणु
	/*==== RF Off Sequence ==== */
	disable_rfafeandresetbb(hw);
	/*  ==== Reset digital sequence   ====== */
	_resetdigitalprocedure1(hw, true);
	/*  ==== Pull GPIO PIN to balance level and LED control ====== */
	_disablegpio(hw);
	/*  ==== Reset digital sequence   ====== */
	_resetdigitalprocedure2(hw);
	/*  ==== Disable analog sequence === */
	disable_analog(hw, true);
पूर्ण

अटल व्योम _rtl92cu_set_bcn_ctrl_reg(काष्ठा ieee80211_hw *hw,
				      u8 set_bits, u8 clear_bits)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	rtlusb->reg_bcn_ctrl_val |= set_bits;
	rtlusb->reg_bcn_ctrl_val &= ~clear_bits;
	rtl_ग_लिखो_byte(rtlpriv, REG_BCN_CTRL, (u8)rtlusb->reg_bcn_ctrl_val);
पूर्ण

अटल व्योम _rtl92cu_stop_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 पंचांगp1byte = 0;

	अगर (IS_NORMAL_CHIP(rtlhal->version)) अणु
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
			       पंचांगp1byte & (~BIT(6)));
		rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0x64);
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
		पंचांगp1byte &= ~(BIT(0));
		rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp1byte);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE,
			       rtl_पढ़ो_byte(rtlpriv, REG_TXPAUSE) | BIT(6));
	पूर्ण
पूर्ण

अटल व्योम _rtl92cu_resume_tx_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 पंचांगp1byte = 0;

	अगर (IS_NORMAL_CHIP(rtlhal->version)) अणु
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2);
		rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
			       पंचांगp1byte | BIT(6));
		rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 1, 0xff);
		पंचांगp1byte = rtl_पढ़ो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2);
		पंचांगp1byte |= BIT(0);
		rtl_ग_लिखो_byte(rtlpriv, REG_TBTT_PROHIBIT + 2, पंचांगp1byte);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE,
			       rtl_पढ़ो_byte(rtlpriv, REG_TXPAUSE) & (~BIT(6)));
	पूर्ण
पूर्ण

अटल व्योम _rtl92cu_enable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	अगर (IS_NORMAL_CHIP(rtlhal->version))
		_rtl92cu_set_bcn_ctrl_reg(hw, 0, BIT(1));
	अन्यथा
		_rtl92cu_set_bcn_ctrl_reg(hw, 0, BIT(4));
पूर्ण

अटल व्योम _rtl92cu_disable_bcn_sub_func(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	अगर (IS_NORMAL_CHIP(rtlhal->version))
		_rtl92cu_set_bcn_ctrl_reg(hw, BIT(1), 0);
	अन्यथा
		_rtl92cu_set_bcn_ctrl_reg(hw, BIT(4), 0);
पूर्ण

अटल पूर्णांक _rtl92cu_set_media_status(काष्ठा ieee80211_hw *hw,
				     क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 bt_msr = rtl_पढ़ो_byte(rtlpriv, MSR);
	क्रमागत led_ctl_mode ledaction = LED_CTL_NO_LINK;

	bt_msr &= 0xfc;
	अगर (type == NL80211_IFTYPE_UNSPECIFIED || type ==
	    NL80211_IFTYPE_STATION) अणु
		_rtl92cu_stop_tx_beacon(hw);
		_rtl92cu_enable_bcn_sub_func(hw);
	पूर्ण अन्यथा अगर (type == NL80211_IFTYPE_ADHOC || type == NL80211_IFTYPE_AP) अणु
		_rtl92cu_resume_tx_beacon(hw);
		_rtl92cu_disable_bcn_sub_func(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"Set HW_VAR_MEDIA_STATUS:No such media status(%x)\n",
			type);
	पूर्ण
	चयन (type) अणु
	हाल NL80211_IFTYPE_UNSPECIFIED:
		bt_msr |= MSR_NOLINK;
		ledaction = LED_CTL_LINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to NO LINK!\n");
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		bt_msr |= MSR_ADHOC;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to Ad Hoc!\n");
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		bt_msr |= MSR_INFRA;
		ledaction = LED_CTL_LINK;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to STA!\n");
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		bt_msr |= MSR_AP;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Set Network type to AP!\n");
		अवरोध;
	शेष:
		pr_err("Network type %d not supported!\n", type);
		जाओ error_out;
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, MSR, bt_msr);
	rtlpriv->cfg->ops->led_control(hw, ledaction);
	अगर ((bt_msr & MSR_MASK) == MSR_AP)
		rtl_ग_लिखो_byte(rtlpriv, REG_BCNTCFG + 1, 0x00);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_BCNTCFG + 1, 0x66);
	वापस 0;
error_out:
	वापस 1;
पूर्ण

व्योम rtl92cu_card_disable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत nl80211_अगरtype opmode;

	mac->link_state = MAC80211_NOLINK;
	opmode = NL80211_IFTYPE_UNSPECIFIED;
	_rtl92cu_set_media_status(hw, opmode);
	rtlpriv->cfg->ops->led_control(hw, LED_CTL_POWER_OFF);
	RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
	अगर (rtlusb->disablehwsm)
		carddisable_hwsm(hw);
	अन्यथा
		carddisablewithout_hwsm(hw);

	/* after घातer off we should करो iqk again */
	rtlpriv->phy.iqk_initialized = false;
पूर्ण

व्योम rtl92cu_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 reg_rcr;

	अगर (rtlpriv->psc.rfpwr_state != ERFON)
		वापस;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RCR, (u8 *)(&reg_rcr));

	अगर (check_bssid) अणु
		u8 पंचांगp;

		अगर (IS_NORMAL_CHIP(rtlhal->version)) अणु
			reg_rcr |= (RCR_CBSSID_DATA | RCR_CBSSID_BCN);
			पंचांगp = BIT(4);
		पूर्ण अन्यथा अणु
			reg_rcr |= RCR_CBSSID;
			पंचांगp = BIT(4) | BIT(5);
		पूर्ण
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RCR,
					      (u8 *) (&reg_rcr));
		_rtl92cu_set_bcn_ctrl_reg(hw, 0, पंचांगp);
	पूर्ण अन्यथा अणु
		u8 पंचांगp;

		अगर (IS_NORMAL_CHIP(rtlhal->version)) अणु
			reg_rcr &= ~(RCR_CBSSID_DATA | RCR_CBSSID_BCN);
			पंचांगp = BIT(4);
		पूर्ण अन्यथा अणु
			reg_rcr &= ~RCR_CBSSID;
			पंचांगp = BIT(4) | BIT(5);
		पूर्ण
		reg_rcr &= (~(RCR_CBSSID_DATA | RCR_CBSSID_BCN));
		rtlpriv->cfg->ops->set_hw_reg(hw,
					      HW_VAR_RCR, (u8 *) (&reg_rcr));
		_rtl92cu_set_bcn_ctrl_reg(hw, पंचांगp, 0);
	पूर्ण
पूर्ण

/*========================================================================== */

पूर्णांक rtl92cu_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (_rtl92cu_set_media_status(hw, type))
		वापस -EOPNOTSUPP;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		अगर (type != NL80211_IFTYPE_AP)
			rtl92cu_set_check_bssid(hw, true);
	पूर्ण अन्यथा अणु
		rtl92cu_set_check_bssid(hw, false);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम _beacon_function_enable(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	_rtl92cu_set_bcn_ctrl_reg(hw, (BIT(4) | BIT(3) | BIT(1)), 0x00);
	rtl_ग_लिखो_byte(rtlpriv, REG_RD_CTRL+1, 0x6F);
पूर्ण

व्योम rtl92cu_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw)
अणु

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval, atim_winकरोw;
	u32 value32;

	bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;
	atim_winकरोw = 2;	/*FIX MERGE */
	rtl_ग_लिखो_word(rtlpriv, REG_ATIMWND, atim_winकरोw);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
	_rtl92cu_init_beacon_parameters(hw);
	rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, 0x09);
	/*
	 * Force beacon frame transmission even after receiving beacon frame
	 * from other ad hoc STA
	 *
	 *
	 * Reset TSF Timer to zero, added by Roger. 2008.06.24
	 */
	value32 = rtl_पढ़ो_dword(rtlpriv, REG_TCR);
	value32 &= ~TSFRST;
	rtl_ग_लिखो_dword(rtlpriv, REG_TCR, value32);
	value32 |= TSFRST;
	rtl_ग_लिखो_dword(rtlpriv, REG_TCR, value32);
	rtl_dbg(rtlpriv, COMP_INIT | COMP_BEACON, DBG_LOUD,
		"SetBeaconRelatedRegisters8192CUsb(): Set TCR(%x)\n",
		value32);
	/* TODO: Modअगरy later (Find the right parameters)
	 * NOTE: Fix test chip's bug (about contention windows's अक्रमomness) */
	अगर ((mac->opmode == NL80211_IFTYPE_ADHOC) ||
	    (mac->opmode == NL80211_IFTYPE_MESH_POINT) ||
	    (mac->opmode == NL80211_IFTYPE_AP)) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_CCK, 0x50);
		rtl_ग_लिखो_byte(rtlpriv, REG_RXTSF_OFFSET_OFDM, 0x50);
	पूर्ण
	_beacon_function_enable(hw);
पूर्ण

व्योम rtl92cu_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 bcn_पूर्णांकerval = mac->beacon_पूर्णांकerval;

	rtl_dbg(rtlpriv, COMP_BEACON, DBG_DMESG, "beacon_interval:%d\n",
		bcn_पूर्णांकerval);
	rtl_ग_लिखो_word(rtlpriv, REG_BCN_INTERVAL, bcn_पूर्णांकerval);
पूर्ण

व्योम rtl92cu_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				   u32 add_msr, u32 rm_msr)
अणु
पूर्ण

व्योम rtl92cu_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	चयन (variable) अणु
	हाल HW_VAR_RCR:
		*((u32 *)(val)) = mac->rx_conf;
		अवरोध;
	हाल HW_VAR_RF_STATE:
		*((क्रमागत rf_pwrstate *)(val)) = ppsc->rfpwr_state;
		अवरोध;
	हाल HW_VAR_FWLPS_RF_ON:अणु
			क्रमागत rf_pwrstate rख_स्थितिe;
			u32 val_rcr;

			rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RF_STATE,
						      (u8 *)(&rख_स्थितिe));
			अगर (rख_स्थितिe == ERFOFF) अणु
				*((bool *) (val)) = true;
			पूर्ण अन्यथा अणु
				val_rcr = rtl_पढ़ो_dword(rtlpriv, REG_RCR);
				val_rcr &= 0x00070000;
				अगर (val_rcr)
					*((bool *) (val)) = false;
				अन्यथा
					*((bool *) (val)) = true;
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS:
		*((bool *) (val)) = ppsc->fw_current_inpsmode;
		अवरोध;
	हाल HW_VAR_CORRECT_TSF:अणु
			u64 tsf;
			u32 *ptsf_low = (u32 *)&tsf;
			u32 *ptsf_high = ((u32 *)&tsf) + 1;

			*ptsf_high = rtl_पढ़ो_dword(rtlpriv, (REG_TSFTR + 4));
			*ptsf_low = rtl_पढ़ो_dword(rtlpriv, REG_TSFTR);
			*((u64 *)(val)) = tsf;
			अवरोध;
		पूर्ण
	हाल HW_VAR_MGT_FILTER:
		*((u16 *) (val)) = rtl_पढ़ो_word(rtlpriv, REG_RXFLTMAP0);
		अवरोध;
	हाल HW_VAR_CTRL_FILTER:
		*((u16 *) (val)) = rtl_पढ़ो_word(rtlpriv, REG_RXFLTMAP1);
		अवरोध;
	हाल HW_VAR_DATA_FILTER:
		*((u16 *) (val)) = rtl_पढ़ो_word(rtlpriv, REG_RXFLTMAP2);
		अवरोध;
	हाल HAL_DEF_WOWLAN:
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool usb_cmd_send_packet(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
  /* Currently nothing happens here.
   * Traffic stops after some seconds in WPA2 802.11n mode.
   * Maybe because rtl8192cu chip should be set from here?
   * If I understand correctly, the realtek venकरोr driver sends some urbs
   * अगर its "here".
   *
   * This is maybe necessary:
   * rtlpriv->cfg->ops->fill_tx_cmddesc(hw, buffer, 1, 1, skb);
   */
	dev_kमुक्त_skb(skb);

	वापस true;
पूर्ण

व्योम rtl92cu_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	क्रमागत wireless_mode wirelessmode = mac->mode;
	u8 idx = 0;

	चयन (variable) अणु
	हाल HW_VAR_ETHER_ADDR:अणु
			क्रम (idx = 0; idx < ETH_ALEN; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, (REG_MACID + idx),
					       val[idx]);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_BASIC_RATE:अणु
			u16 rate_cfg = ((u16 *) val)[0];
			u8 rate_index = 0;

			rate_cfg &= 0x15f;
			/* TODO */
			/* अगर (mac->current_network.vender == HT_IOT_PEER_CISCO
			 *     && ((rate_cfg & 0x150) == 0)) अणु
			 *	  rate_cfg |= 0x010;
			 * पूर्ण */
			rate_cfg |= 0x01;
			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR, rate_cfg & 0xff);
			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 1,
				       (rate_cfg >> 8) & 0xff);
			जबतक (rate_cfg > 0x1) अणु
				rate_cfg >>= 1;
				rate_index++;
			पूर्ण
			rtl_ग_लिखो_byte(rtlpriv, REG_INIRTS_RATE_SEL,
				       rate_index);
			अवरोध;
		पूर्ण
	हाल HW_VAR_BSSID:अणु
			क्रम (idx = 0; idx < ETH_ALEN; idx++) अणु
				rtl_ग_लिखो_byte(rtlpriv, (REG_BSSID + idx),
					       val[idx]);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_SIFS:अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_CCK + 1, val[0]);
			rtl_ग_लिखो_byte(rtlpriv, REG_SIFS_OFDM + 1, val[1]);
			rtl_ग_लिखो_byte(rtlpriv, REG_SPEC_SIFS + 1, val[0]);
			rtl_ग_लिखो_byte(rtlpriv, REG_MAC_SPEC_SIFS + 1, val[0]);
			rtl_ग_लिखो_byte(rtlpriv, REG_R2T_SIFS+1, val[0]);
			rtl_ग_लिखो_byte(rtlpriv, REG_T2T_SIFS+1, val[0]);
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD, "HW_VAR_SIFS\n");
			अवरोध;
		पूर्ण
	हाल HW_VAR_SLOT_TIME:अणु
			u8 e_aci;
			u8 QOS_MODE = 1;

			rtl_ग_लिखो_byte(rtlpriv, REG_SLOT, val[0]);
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"HW_VAR_SLOT_TIME %x\n", val[0]);
			अगर (QOS_MODE) अणु
				क्रम (e_aci = 0; e_aci < AC_MAX; e_aci++)
					rtlpriv->cfg->ops->set_hw_reg(hw,
								HW_VAR_AC_PARAM,
								&e_aci);
			पूर्ण अन्यथा अणु
				u8 sअगरsसमय = 0;
				u8	u1baअगरs;

				अगर (IS_WIRELESS_MODE_A(wirelessmode) ||
				    IS_WIRELESS_MODE_N_24G(wirelessmode) ||
				    IS_WIRELESS_MODE_N_5G(wirelessmode))
					sअगरsसमय = 16;
				अन्यथा
					sअगरsसमय = 10;
				u1baअगरs = sअगरsसमय + (2 *  val[0]);
				rtl_ग_लिखो_byte(rtlpriv, REG_EDCA_VO_PARAM,
					       u1baअगरs);
				rtl_ग_लिखो_byte(rtlpriv, REG_EDCA_VI_PARAM,
					       u1baअगरs);
				rtl_ग_लिखो_byte(rtlpriv, REG_EDCA_BE_PARAM,
					       u1baअगरs);
				rtl_ग_लिखो_byte(rtlpriv, REG_EDCA_BK_PARAM,
					       u1baअगरs);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_ACK_PREAMBLE:अणु
			u8 reg_पंचांगp;
			u8 लघु_preamble = (bool)*val;

			reg_पंचांगp = 0;
			अगर (लघु_preamble)
				reg_पंचांगp |= 0x80;
			rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 2, reg_पंचांगp);
			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_MIN_SPACE:अणु
			u8 min_spacing_to_set;
			u8 sec_min_space;

			min_spacing_to_set = *val;
			अगर (min_spacing_to_set <= 7) अणु
				चयन (rtlpriv->sec.pairwise_enc_algorithm) अणु
				हाल NO_ENCRYPTION:
				हाल AESCCMP_ENCRYPTION:
					sec_min_space = 0;
					अवरोध;
				हाल WEP40_ENCRYPTION:
				हाल WEP104_ENCRYPTION:
				हाल TKIP_ENCRYPTION:
					sec_min_space = 6;
					अवरोध;
				शेष:
					sec_min_space = 7;
					अवरोध;
				पूर्ण
				अगर (min_spacing_to_set < sec_min_space)
					min_spacing_to_set = sec_min_space;
				mac->min_space_cfg = ((mac->min_space_cfg &
						     0xf8) |
						     min_spacing_to_set);
				*val = min_spacing_to_set;
				rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
					"Set HW_VAR_AMPDU_MIN_SPACE: %#x\n",
					mac->min_space_cfg);
				rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
					       mac->min_space_cfg);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_SHORTGI_DENSITY:अणु
			u8 density_to_set;

			density_to_set = *val;
			density_to_set &= 0x1f;
			mac->min_space_cfg &= 0x07;
			mac->min_space_cfg |= (density_to_set << 3);
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"Set HW_VAR_SHORTGI_DENSITY: %#x\n",
				mac->min_space_cfg);
			rtl_ग_लिखो_byte(rtlpriv, REG_AMPDU_MIN_SPACE,
				       mac->min_space_cfg);
			अवरोध;
		पूर्ण
	हाल HW_VAR_AMPDU_FACTOR:अणु
			u8 regtoset_normal[4] = अणु0x41, 0xa8, 0x72, 0xb9पूर्ण;
			u8 factor_toset;
			u8 *p_regtoset = शून्य;
			u8 index = 0;

			p_regtoset = regtoset_normal;
			factor_toset = *val;
			अगर (factor_toset <= 3) अणु
				factor_toset = (1 << (factor_toset + 2));
				अगर (factor_toset > 0xf)
					factor_toset = 0xf;
				क्रम (index = 0; index < 4; index++) अणु
					अगर ((p_regtoset[index] & 0xf0) >
					    (factor_toset << 4))
						p_regtoset[index] =
						     (p_regtoset[index] & 0x0f)
						     | (factor_toset << 4);
					अगर ((p_regtoset[index] & 0x0f) >
					     factor_toset)
						p_regtoset[index] =
						     (p_regtoset[index] & 0xf0)
						     | (factor_toset);
					rtl_ग_लिखो_byte(rtlpriv,
						       (REG_AGGLEN_LMT + index),
						       p_regtoset[index]);
				पूर्ण
				rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
					"Set HW_VAR_AMPDU_FACTOR: %#x\n",
					factor_toset);
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_AC_PARAM:अणु
			u8 e_aci = *val;
			u32 u4b_ac_param;
			u16 cw_min = le16_to_cpu(mac->ac[e_aci].cw_min);
			u16 cw_max = le16_to_cpu(mac->ac[e_aci].cw_max);
			u16 tx_op = le16_to_cpu(mac->ac[e_aci].tx_op);

			u4b_ac_param = (u32) mac->ac[e_aci].aअगरs;
			u4b_ac_param |= (u32) ((cw_min & 0xF) <<
					 AC_PARAM_ECW_MIN_OFFSET);
			u4b_ac_param |= (u32) ((cw_max & 0xF) <<
					 AC_PARAM_ECW_MAX_OFFSET);
			u4b_ac_param |= (u32) tx_op << AC_PARAM_TXOP_OFFSET;
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"queue:%x, ac_param:%x\n",
				e_aci, u4b_ac_param);
			चयन (e_aci) अणु
			हाल AC1_BK:
				rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BK_PARAM,
						u4b_ac_param);
				अवरोध;
			हाल AC0_BE:
				rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BE_PARAM,
						u4b_ac_param);
				अवरोध;
			हाल AC2_VI:
				rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VI_PARAM,
						u4b_ac_param);
				अवरोध;
			हाल AC3_VO:
				rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_VO_PARAM,
						u4b_ac_param);
				अवरोध;
			शेष:
				WARN_ONCE(true, "rtl8192cu: invalid aci: %d !\n",
					  e_aci);
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण
	हाल HW_VAR_RCR:अणु
			rtl_ग_लिखो_dword(rtlpriv, REG_RCR, ((u32 *) (val))[0]);
			mac->rx_conf = ((u32 *) (val))[0];
			rtl_dbg(rtlpriv, COMP_RECV, DBG_DMESG,
				"### Set RCR(0x%08x) ###\n", mac->rx_conf);
			अवरोध;
		पूर्ण
	हाल HW_VAR_RETRY_LIMIT:अणु
			u8 retry_limit = val[0];

			rtl_ग_लिखो_word(rtlpriv, REG_RL,
				       retry_limit << RETRY_LIMIT_SHORT_SHIFT |
				       retry_limit << RETRY_LIMIT_LONG_SHIFT);
			rtl_dbg(rtlpriv, COMP_MLME, DBG_DMESG,
				"Set HW_VAR_RETRY_LIMIT(0x%08x)\n",
				retry_limit);
			अवरोध;
		पूर्ण
	हाल HW_VAR_DUAL_TSF_RST:
		rtl_ग_लिखो_byte(rtlpriv, REG_DUAL_TSF_RST, (BIT(0) | BIT(1)));
		अवरोध;
	हाल HW_VAR_EFUSE_BYTES:
		rtlefuse->efuse_usedbytes = *((u16 *) val);
		अवरोध;
	हाल HW_VAR_EFUSE_USAGE:
		rtlefuse->efuse_usedpercentage = *val;
		अवरोध;
	हाल HW_VAR_IO_CMD:
		rtl92c_phy_set_io_cmd(hw, (*(क्रमागत io_type *)val));
		अवरोध;
	हाल HW_VAR_WPA_CONFIG:
		rtl_ग_लिखो_byte(rtlpriv, REG_SECCFG, *val);
		अवरोध;
	हाल HW_VAR_SET_RPWM:अणु
			u8 rpwm_val = rtl_पढ़ो_byte(rtlpriv, REG_USB_HRPWM);

			अगर (rpwm_val & BIT(7))
				rtl_ग_लिखो_byte(rtlpriv, REG_USB_HRPWM, *val);
			अन्यथा
				rtl_ग_लिखो_byte(rtlpriv, REG_USB_HRPWM,
					       *val | BIT(7));
			अवरोध;
		पूर्ण
	हाल HW_VAR_H2C_FW_PWRMODE:अणु
			u8 psmode = *val;

			अगर ((psmode != FW_PS_ACTIVE_MODE) &&
			   (!IS_92C_SERIAL(rtlhal->version)))
				rtl92c_dm_rf_saving(hw, true);
			rtl92c_set_fw_pwrmode_cmd(hw, (*val));
			अवरोध;
		पूर्ण
	हाल HW_VAR_FW_PSMODE_STATUS:
		ppsc->fw_current_inpsmode = *((bool *) val);
		अवरोध;
	हाल HW_VAR_H2C_FW_JOINBSSRPT:अणु
			u8 mstatus = *val;
			u8 पंचांगp_reg422;
			bool recover = false;

			अगर (mstatus == RT_MEDIA_CONNECT) अणु
				rtlpriv->cfg->ops->set_hw_reg(hw,
							 HW_VAR_AID, शून्य);
				rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, 0x03);
				_rtl92cu_set_bcn_ctrl_reg(hw, 0, BIT(3));
				_rtl92cu_set_bcn_ctrl_reg(hw, BIT(4), 0);
				पंचांगp_reg422 = rtl_पढ़ो_byte(rtlpriv,
							REG_FWHW_TXQ_CTRL + 2);
				अगर (पंचांगp_reg422 & BIT(6))
					recover = true;
				rtl_ग_लिखो_byte(rtlpriv, REG_FWHW_TXQ_CTRL + 2,
					       पंचांगp_reg422 & (~BIT(6)));
				rtl92c_set_fw_rsvdpagepkt(hw,
							  &usb_cmd_send_packet);
				_rtl92cu_set_bcn_ctrl_reg(hw, BIT(3), 0);
				_rtl92cu_set_bcn_ctrl_reg(hw, 0, BIT(4));
				अगर (recover)
					rtl_ग_लिखो_byte(rtlpriv,
						 REG_FWHW_TXQ_CTRL + 2,
						पंचांगp_reg422 | BIT(6));
				rtl_ग_लिखो_byte(rtlpriv, REG_CR + 1, 0x02);
			पूर्ण
			rtl92c_set_fw_joinbss_report_cmd(hw, (*val));
			अवरोध;
		पूर्ण
	हाल HW_VAR_AID:अणु
			u16 u2bपंचांगp;

			u2bपंचांगp = rtl_पढ़ो_word(rtlpriv, REG_BCN_PSR_RPT);
			u2bपंचांगp &= 0xC000;
			rtl_ग_लिखो_word(rtlpriv, REG_BCN_PSR_RPT,
				       (u2bपंचांगp | mac->assoc_id));
			अवरोध;
		पूर्ण
	हाल HW_VAR_CORRECT_TSF:अणु
			u8 btype_ibss = val[0];

			अगर (btype_ibss)
				_rtl92cu_stop_tx_beacon(hw);
			_rtl92cu_set_bcn_ctrl_reg(hw, 0, BIT(3));
			rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR, (u32)(mac->tsf &
					0xffffffff));
			rtl_ग_लिखो_dword(rtlpriv, REG_TSFTR + 4,
					(u32)((mac->tsf >> 32) & 0xffffffff));
			_rtl92cu_set_bcn_ctrl_reg(hw, BIT(3), 0);
			अगर (btype_ibss)
				_rtl92cu_resume_tx_beacon(hw);
			अवरोध;
		पूर्ण
	हाल HW_VAR_MGT_FILTER:
		rtl_ग_लिखो_word(rtlpriv, REG_RXFLTMAP0, *(u16 *)val);
		mac->rx_mgt_filter = *(u16 *)val;
		अवरोध;
	हाल HW_VAR_CTRL_FILTER:
		rtl_ग_लिखो_word(rtlpriv, REG_RXFLTMAP1, *(u16 *)val);
		mac->rx_ctrl_filter = *(u16 *)val;
		अवरोध;
	हाल HW_VAR_DATA_FILTER:
		rtl_ग_लिखो_word(rtlpriv, REG_RXFLTMAP2, *(u16 *)val);
		mac->rx_data_filter = *(u16 *)val;
		अवरोध;
	हाल HW_VAR_KEEP_ALIVE:अणु
			u8 array[2];

			array[0] = 0xff;
			array[1] = *((u8 *)val);
			rtl92c_fill_h2c_cmd(hw, H2C_92C_KEEP_ALIVE_CTRL, 2,
					    array);
			अवरोध;
		पूर्ण
	शेष:
		pr_err("switch case %#x not processed\n", variable);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम rtl92cu_update_hal_rate_table(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 ratr_value;
	u8 ratr_index = 0;
	u8 nmode = mac->ht_enable;
	u8 mimo_ps = IEEE80211_SMPS_OFF;
	u16 लघुgi_rate;
	u32 पंचांगp_ratr_value;
	u8 curtxbw_40mhz = mac->bw_40;
	u8 curलघुgi_40mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
			       1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
			       1 : 0;
	क्रमागत wireless_mode wirelessmode = mac->mode;

	अगर (rtlhal->current_bandtype == BAND_ON_5G)
		ratr_value = sta->supp_rates[1] << 4;
	अन्यथा
		ratr_value = sta->supp_rates[0];
	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_value = 0xfff;

	ratr_value |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
			sta->ht_cap.mcs.rx_mask[0] << 12);
	चयन (wirelessmode) अणु
	हाल WIRELESS_MODE_B:
		अगर (ratr_value & 0x0000000c)
			ratr_value &= 0x0000000d;
		अन्यथा
			ratr_value &= 0x0000000f;
		अवरोध;
	हाल WIRELESS_MODE_G:
		ratr_value &= 0x00000FF5;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
	हाल WIRELESS_MODE_N_5G:
		nmode = 1;
		अगर (mimo_ps == IEEE80211_SMPS_STATIC) अणु
			ratr_value &= 0x0007F005;
		पूर्ण अन्यथा अणु
			u32 ratr_mask;

			अगर (get_rf_type(rtlphy) == RF_1T2R ||
			    get_rf_type(rtlphy) == RF_1T1R)
				ratr_mask = 0x000ff005;
			अन्यथा
				ratr_mask = 0x0f0ff005;

			ratr_value &= ratr_mask;
		पूर्ण
		अवरोध;
	शेष:
		अगर (rtlphy->rf_type == RF_1T2R)
			ratr_value &= 0x000ff0ff;
		अन्यथा
			ratr_value &= 0x0f0ff0ff;

		अवरोध;
	पूर्ण

	ratr_value &= 0x0FFFFFFF;

	अगर (nmode && ((curtxbw_40mhz &&
			 curलघुgi_40mhz) || (!curtxbw_40mhz &&
					       curलघुgi_20mhz))) अणु
		ratr_value |= 0x10000000;
		पंचांगp_ratr_value = (ratr_value >> 12);

		क्रम (लघुgi_rate = 15; लघुgi_rate > 0; लघुgi_rate--) अणु
			अगर ((1 << लघुgi_rate) & पंचांगp_ratr_value)
				अवरोध;
		पूर्ण

		लघुgi_rate = (लघुgi_rate << 12) | (लघुgi_rate << 8) |
		    (लघुgi_rate << 4) | (लघुgi_rate);
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, REG_ARFR0 + ratr_index * 4, ratr_value);

	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG, "%x\n",
		rtl_पढ़ो_dword(rtlpriv, REG_ARFR0));
पूर्ण

अटल व्योम rtl92cu_update_hal_rate_mask(काष्ठा ieee80211_hw *hw,
					 काष्ठा ieee80211_sta *sta,
					 u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u32 ratr_biपंचांगap;
	u8 ratr_index;
	u8 curtxbw_40mhz = (sta->bandwidth >= IEEE80211_STA_RX_BW_40) ? 1 : 0;
	u8 curलघुgi_40mhz = curtxbw_40mhz &&
			      (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40) ?
				1 : 0;
	u8 curलघुgi_20mhz = (sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20) ?
				1 : 0;
	क्रमागत wireless_mode wirelessmode = 0;
	bool लघुgi = false;
	u8 rate_mask[5];
	u8 macid = 0;
	u8 mimo_ps = IEEE80211_SMPS_OFF;

	sta_entry = (काष्ठा rtl_sta_info *) sta->drv_priv;
	wirelessmode = sta_entry->wireless_mode;
	अगर (mac->opmode == NL80211_IFTYPE_STATION ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT)
		curtxbw_40mhz = mac->bw_40;
	अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		mac->opmode == NL80211_IFTYPE_ADHOC)
		macid = sta->aid + 1;

	अगर (rtlhal->current_bandtype == BAND_ON_5G)
		ratr_biपंचांगap = sta->supp_rates[1] << 4;
	अन्यथा
		ratr_biपंचांगap = sta->supp_rates[0];
	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		ratr_biपंचांगap = 0xfff;
	ratr_biपंचांगap |= (sta->ht_cap.mcs.rx_mask[1] << 20 |
			sta->ht_cap.mcs.rx_mask[0] << 12);
	चयन (wirelessmode) अणु
	हाल WIRELESS_MODE_B:
		ratr_index = RATR_INX_WIRELESS_B;
		अगर (ratr_biपंचांगap & 0x0000000c)
			ratr_biपंचांगap &= 0x0000000d;
		अन्यथा
			ratr_biपंचांगap &= 0x0000000f;
		अवरोध;
	हाल WIRELESS_MODE_G:
		ratr_index = RATR_INX_WIRELESS_GB;

		अगर (rssi_level == 1)
			ratr_biपंचांगap &= 0x00000f00;
		अन्यथा अगर (rssi_level == 2)
			ratr_biपंचांगap &= 0x00000ff0;
		अन्यथा
			ratr_biपंचांगap &= 0x00000ff5;
		अवरोध;
	हाल WIRELESS_MODE_A:
		ratr_index = RATR_INX_WIRELESS_A;
		ratr_biपंचांगap &= 0x00000ff0;
		अवरोध;
	हाल WIRELESS_MODE_N_24G:
	हाल WIRELESS_MODE_N_5G:
		ratr_index = RATR_INX_WIRELESS_NGB;

		अगर (mimo_ps == IEEE80211_SMPS_STATIC) अणु
			अगर (rssi_level == 1)
				ratr_biपंचांगap &= 0x00070000;
			अन्यथा अगर (rssi_level == 2)
				ratr_biपंचांगap &= 0x0007f000;
			अन्यथा
				ratr_biपंचांगap &= 0x0007f005;
		पूर्ण अन्यथा अणु
			अगर (rtlphy->rf_type == RF_1T2R ||
			    rtlphy->rf_type == RF_1T1R) अणु
				अगर (curtxbw_40mhz) अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x000f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x000ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x000ff015;
				पूर्ण अन्यथा अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x000f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x000ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x000ff005;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (curtxbw_40mhz) अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x0f0f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x0f0ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x0f0ff015;
				पूर्ण अन्यथा अणु
					अगर (rssi_level == 1)
						ratr_biपंचांगap &= 0x0f0f0000;
					अन्यथा अगर (rssi_level == 2)
						ratr_biपंचांगap &= 0x0f0ff000;
					अन्यथा
						ratr_biपंचांगap &= 0x0f0ff005;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर ((curtxbw_40mhz && curलघुgi_40mhz) ||
		    (!curtxbw_40mhz && curलघुgi_20mhz)) अणु

			अगर (macid == 0)
				लघुgi = true;
			अन्यथा अगर (macid == 1)
				लघुgi = false;
		पूर्ण
		अवरोध;
	शेष:
		ratr_index = RATR_INX_WIRELESS_NGB;

		अगर (rtlphy->rf_type == RF_1T2R)
			ratr_biपंचांगap &= 0x000ff0ff;
		अन्यथा
			ratr_biपंचांगap &= 0x0f0ff0ff;
		अवरोध;
	पूर्ण
	sta_entry->ratr_index = ratr_index;

	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"ratr_bitmap :%x\n", ratr_biपंचांगap);
	*(u32 *)&rate_mask = (ratr_biपंचांगap & 0x0fffffff) |
				     (ratr_index << 28);
	rate_mask[4] = macid | (लघुgi ? 0x20 : 0x00) | 0x80;
	rtl_dbg(rtlpriv, COMP_RATR, DBG_DMESG,
		"Rate_index:%x, ratr_val:%x, %5phC\n",
		ratr_index, ratr_biपंचांगap, rate_mask);
	स_नकल(rtlpriv->rate_mask, rate_mask, 5);
	/* rtl92c_fill_h2c_cmd() करोes USB I/O and will result in a
	 * "scheduled while atomic" अगर called directly */
	schedule_work(&rtlpriv->works.fill_h2c_cmd);

	अगर (macid != 0)
		sta_entry->ratr_index = ratr_index;
पूर्ण

व्योम rtl92cu_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_sta *sta,
				 u8 rssi_level, bool update_bw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->dm.useramask)
		rtl92cu_update_hal_rate_mask(hw, sta, rssi_level, update_bw);
	अन्यथा
		rtl92cu_update_hal_rate_table(hw, sta);
पूर्ण

व्योम rtl92cu_update_channel_access_setting(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u16 sअगरs_समयr;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
				      &mac->slot_समय);
	अगर (!mac->ht_enable)
		sअगरs_समयr = 0x0a0a;
	अन्यथा
		sअगरs_समयr = 0x0e0e;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SIFS, (u8 *)&sअगरs_समयr);
पूर्ण

bool rtl92cu_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 * valid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	क्रमागत rf_pwrstate e_rfघातerstate_toset, cur_rख_स्थितिe;
	u8 u1पंचांगp = 0;
	bool actuallyset = false;
	अचिन्हित दीर्घ flag = 0;
	/* to करो - usb स्वतःsuspend */
	u8 usb_स्वतःsuspend = 0;

	अगर (ppsc->swrf_processing)
		वापस false;
	spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
	अगर (ppsc->rfchange_inprogress) अणु
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
		वापस false;
	पूर्ण अन्यथा अणु
		ppsc->rfchange_inprogress = true;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	पूर्ण
	cur_rख_स्थितिe = ppsc->rfpwr_state;
	अगर (usb_स्वतःsuspend) अणु
		/* to करो................... */
	पूर्ण अन्यथा अणु
		अगर (ppsc->pwrकरोwn_mode) अणु
			u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_HSISR);
			e_rfघातerstate_toset = (u1पंचांगp & BIT(7)) ?
					       ERFOFF : ERFON;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
				"pwrdown, 0x5c(BIT7)=%02x\n", u1पंचांगp);
		पूर्ण अन्यथा अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_MAC_PINMUX_CFG,
				       rtl_पढ़ो_byte(rtlpriv,
				       REG_MAC_PINMUX_CFG) & ~(BIT(3)));
			u1पंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_GPIO_IO_SEL);
			e_rfघातerstate_toset  = (u1पंचांगp & BIT(3)) ?
						 ERFON : ERFOFF;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
				"GPIO_IN=%02x\n", u1पंचांगp);
		पूर्ण
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "N-SS RF =%x\n",
			e_rfघातerstate_toset);
	पूर्ण
	अगर ((ppsc->hwradiooff) && (e_rfघातerstate_toset == ERFON)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"GPIOChangeRF  - HW Radio ON, RF ON\n");
		ppsc->hwradiooff = false;
		actuallyset = true;
	पूर्ण अन्यथा अगर ((!ppsc->hwradiooff) && (e_rfघातerstate_toset  ==
		    ERFOFF)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"GPIOChangeRF  - HW Radio OFF\n");
		ppsc->hwradiooff = true;
		actuallyset = true;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"pHalData->bHwRadioOff and eRfPowerStateToSet do not match: pHalData->bHwRadioOff %x, eRfPowerStateToSet %x\n",
			 ppsc->hwradiooff, e_rfघातerstate_toset);
	पूर्ण
	अगर (actuallyset) अणु
		ppsc->hwradiooff = true;
		अगर (e_rfघातerstate_toset == ERFON) अणु
			अगर ((ppsc->reg_rfps_level  & RT_RF_OFF_LEVL_ASPM) &&
			     RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_ASPM))
				RT_CLEAR_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_ASPM);
			अन्यथा अगर ((ppsc->reg_rfps_level  & RT_RF_OFF_LEVL_PCI_D3)
				 && RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_PCI_D3))
				RT_CLEAR_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_PCI_D3);
		पूर्ण
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
		/* For घातer करोwn module, we need to enable रेजिस्टर block
		 * contrl reg at 0x1c. Then enable घातer करोwn control bit
		 * of रेजिस्टर 0x04 BIT4 and BIT15 as 1.
		 */
		अगर (ppsc->pwrकरोwn_mode && e_rfघातerstate_toset == ERFOFF) अणु
			/* Enable रेजिस्टर area 0x0-0xc. */
			rtl_ग_लिखो_byte(rtlpriv, REG_RSV_CTRL, 0x0);
			rtl_ग_लिखो_word(rtlpriv, REG_APS_FSMCO, 0x8812);
		पूर्ण
		अगर (e_rfघातerstate_toset == ERFOFF) अणु
			अगर (ppsc->reg_rfps_level  & RT_RF_OFF_LEVL_ASPM)
				RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_ASPM);
			अन्यथा अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_PCI_D3)
				RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_PCI_D3);
		पूर्ण
	पूर्ण अन्यथा अगर (e_rfघातerstate_toset == ERFOFF || cur_rख_स्थितिe == ERFOFF) अणु
		/* Enter D3 or ASPM after GPIO had been करोne. */
		अगर (ppsc->reg_rfps_level  & RT_RF_OFF_LEVL_ASPM)
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_ASPM);
		अन्यथा अगर (ppsc->reg_rfps_level  & RT_RF_OFF_LEVL_PCI_D3)
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_PCI_D3);
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&rtlpriv->locks.rf_ps_lock, flag);
		ppsc->rfchange_inprogress = false;
		spin_unlock_irqrestore(&rtlpriv->locks.rf_ps_lock, flag);
	पूर्ण
	*valid = 1;
	वापस !ppsc->hwradiooff;
पूर्ण
