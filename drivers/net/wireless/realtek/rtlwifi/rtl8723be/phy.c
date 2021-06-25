<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../ps.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "../rtl8723com/phy_common.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "../rtl8723com/dm_common.h"
#समावेश "table.h"
#समावेश "trx.h"
#समावेश <linux/kernel.h>

अटल bool _rtl8723be_phy_bb8723b_config_parafile(काष्ठा ieee80211_hw *hw);
अटल bool _rtl8723be_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw);
अटल bool _rtl8723be_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
						     u8 configtype);
अटल bool _rtl8723be_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
						       u8 configtype);
अटल bool _rtl8723be_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
						u8 channel, u8 *stage,
						u8 *step, u32 *delay);

अटल व्योम rtl8723be_phy_set_rf_on(काष्ठा ieee80211_hw *hw);
अटल व्योम rtl8723be_phy_set_io(काष्ठा ieee80211_hw *hw);

u32 rtl8723be_phy_query_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
			       u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, पढ़ोback_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x)\n",
		regaddr, rfpath, biपंचांगask);

	spin_lock(&rtlpriv->locks.rf_lock);

	original_value = rtl8723_phy_rf_serial_पढ़ो(hw, rfpath, regaddr);
	bitshअगरt = rtl8723_phy_calculate_bit_shअगरt(biपंचांगask);
	पढ़ोback_value = (original_value & biपंचांगask) >> bitshअगरt;

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x), original_value(%#x)\n",
		regaddr, rfpath, biपंचांगask, original_value);

	वापस पढ़ोback_value;
पूर्ण

व्योम rtl8723be_phy_set_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path path,
			      u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, path);

	spin_lock(&rtlpriv->locks.rf_lock);

	अगर (biपंचांगask != RFREG_OFFSET_MASK) अणु
			original_value = rtl8723_phy_rf_serial_पढ़ो(hw, path,
								    regaddr);
			bitshअगरt = rtl8723_phy_calculate_bit_shअगरt(biपंचांगask);
			data = ((original_value & (~biपंचांगask)) |
				(data << bitshअगरt));
		पूर्ण

	rtl8723_phy_rf_serial_ग_लिखो(hw, path, regaddr, data);

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, path);

पूर्ण

bool rtl8723be_phy_mac_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool rtstatus = _rtl8723be_phy_config_mac_with_headerfile(hw);

	rtl_ग_लिखो_byte(rtlpriv, 0x04CA, 0x0B);
	वापस rtstatus;
पूर्ण

bool rtl8723be_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	bool rtstatus = true;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 regval;
	u8 b_reg_hwparafile = 1;
	u32 पंचांगp;
	u8 crystalcap = rtlpriv->efuse.crystalcap;
	rtl8723_phy_init_bb_rf_reg_def(hw);
	regval = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN,
		       regval | BIT(13) | BIT(0) | BIT(1));

	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, RF_EN | RF_RSTB | RF_SDMRSTB);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN,
		       FEN_PPLL | FEN_PCIEA | FEN_DIO_PCIE |
		       FEN_BB_GLB_RSTN | FEN_BBRSTB);
	पंचांगp = rtl_पढ़ो_dword(rtlpriv, 0x4c);
	rtl_ग_लिखो_dword(rtlpriv, 0x4c, पंचांगp | BIT(23));

	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL + 1, 0x80);

	अगर (b_reg_hwparafile == 1)
		rtstatus = _rtl8723be_phy_bb8723b_config_parafile(hw);

	crystalcap = crystalcap & 0x3F;
	rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
		      (crystalcap | crystalcap << 6));

	वापस rtstatus;
पूर्ण

bool rtl8723be_phy_rf_config(काष्ठा ieee80211_hw *hw)
अणु
	वापस rtl8723be_phy_rf6052_config(hw);
पूर्ण

अटल bool _rtl8723be_check_positive(काष्ठा ieee80211_hw *hw,
				      स्थिर u32 condition1,
				      स्थिर u32 condition2)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 cut_ver = ((rtlhal->version & CHIP_VER_RTL_MASK)
					>> CHIP_VER_RTL_SHIFT);
	u32 पूर्णांकf = (rtlhal->पूर्णांकerface == INTF_USB ? BIT(1) : BIT(0));

	u8  board_type = ((rtlhal->board_type & BIT(4)) >> 4) << 0 | /* _GLNA */
			 ((rtlhal->board_type & BIT(3)) >> 3) << 1 | /* _GPA  */
			 ((rtlhal->board_type & BIT(7)) >> 7) << 2 | /* _ALNA */
			 ((rtlhal->board_type & BIT(6)) >> 6) << 3 | /* _APA  */
			 ((rtlhal->board_type & BIT(2)) >> 2) << 4;  /* _BT   */

	u32 cond1 = condition1, cond2 = condition2;
	u32 driver1 = cut_ver << 24 |	/* CUT ver */
		      0 << 20 |			/* पूर्णांकerface 2/2 */
		      0x04 << 16 |		/* platक्रमm */
		      rtlhal->package_type << 12 |
		      पूर्णांकf << 8 |			/* पूर्णांकerface 1/2 */
		      board_type;

	u32 driver2 = rtlhal->type_glna <<  0 |
		      rtlhal->type_gpa  <<  8 |
		      rtlhal->type_alna << 16 |
		      rtlhal->type_apa  << 24;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"===> [8812A] CheckPositive (cond1, cond2) = (0x%X 0x%X)\n",
		cond1, cond2);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"===> [8812A] CheckPositive (driver1, driver2) = (0x%X 0x%X)\n",
		driver1, driver2);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"(Platform, Interface) = (0x%X, 0x%X)\n", 0x04, पूर्णांकf);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"(Board, Package) = (0x%X, 0x%X)\n",
		rtlhal->board_type, rtlhal->package_type);

	/*============== Value Defined Check ===============*/
	/*QFN Type [15:12] and Cut Version [27:24] need to करो value check*/

	अगर (((cond1 & 0x0000F000) != 0) && ((cond1 & 0x0000F000) !=
		(driver1 & 0x0000F000)))
		वापस false;
	अगर (((cond1 & 0x0F000000) != 0) && ((cond1 & 0x0F000000) !=
		(driver1 & 0x0F000000)))
		वापस false;

	/*=============== Bit Defined Check ================*/
	/* We करोn't care [31:28] */

	cond1   &= 0x00FF0FFF;
	driver1 &= 0x00FF0FFF;

	अगर ((cond1 & driver1) == cond1) अणु
		u32 mask = 0;

		अगर ((cond1 & 0x0F) == 0) /* BoardType is DONTCARE*/
			वापस true;

		अगर ((cond1 & BIT(0)) != 0) /*GLNA*/
			mask |= 0x000000FF;
		अगर ((cond1 & BIT(1)) != 0) /*GPA*/
			mask |= 0x0000FF00;
		अगर ((cond1 & BIT(2)) != 0) /*ALNA*/
			mask |= 0x00FF0000;
		अगर ((cond1 & BIT(3)) != 0) /*APA*/
			mask |= 0xFF000000;

		/* BoardType of each RF path is matched*/
		अगर ((cond2 & mask) == (driver2 & mask))
			वापस true;
		अन्यथा
			वापस false;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम _rtl8723be_config_rf_reg(काष्ठा ieee80211_hw *hw, u32 addr,
				     u32 data, क्रमागत radio_path rfpath,
				     u32 regaddr)
अणु
	अगर (addr == 0xfe || addr == 0xffe) अणु
		/* In order not to disturb BT music
		 *	when wअगरi init.(1ant NIC only)
		 */
		mdelay(50);
	पूर्ण अन्यथा अणु
		rtl_set_rfreg(hw, rfpath, regaddr, RFREG_OFFSET_MASK, data);
		udelay(1);
	पूर्ण
पूर्ण
अटल व्योम _rtl8723be_config_rf_radio_a(काष्ठा ieee80211_hw *hw,
					 u32 addr, u32 data)
अणु
	u32 content = 0x1000; /*RF Content: radio_a_txt*/
	u32 maskक्रमphyset = (u32)(content & 0xE000);

	_rtl8723be_config_rf_reg(hw, addr, data, RF90_PATH_A,
				 addr | maskक्रमphyset);

पूर्ण

अटल व्योम _rtl8723be_phy_init_tx_घातer_by_rate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	u8 band, path, txnum, section;

	क्रम (band = BAND_ON_2_4G; band <= BAND_ON_5G; ++band)
		क्रम (path = 0; path < TX_PWR_BY_RATE_NUM_RF; ++path)
			क्रम (txnum = 0; txnum < TX_PWR_BY_RATE_NUM_RF; ++txnum)
				क्रम (section = 0;
				     section < TX_PWR_BY_RATE_NUM_SECTION;
				     ++section)
					rtlphy->tx_घातer_by_rate_offset
					  [band][path][txnum][section] = 0;
पूर्ण

अटल व्योम _rtl8723be_config_bb_reg(काष्ठा ieee80211_hw *hw,
				     u32 addr, u32 data)
अणु
	अगर (addr == 0xfe) अणु
		mdelay(50);
	पूर्ण अन्यथा अगर (addr == 0xfd) अणु
		mdelay(5);
	पूर्ण अन्यथा अगर (addr == 0xfc) अणु
		mdelay(1);
	पूर्ण अन्यथा अगर (addr == 0xfb) अणु
		udelay(50);
	पूर्ण अन्यथा अगर (addr == 0xfa) अणु
		udelay(5);
	पूर्ण अन्यथा अगर (addr == 0xf9) अणु
		udelay(1);
	पूर्ण अन्यथा अणु
		rtl_set_bbreg(hw, addr, MASKDWORD, data);
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम _rtl8723be_phy_set_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw,
						    u8 band,
						    u8 path, u8 rate_section,
						    u8 txnum, u8 value)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	अगर (path > RF90_PATH_D) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Rf Path %d in phy_SetTxPowerByRatBase()\n",
			path);
		वापस;
	पूर्ण

	अगर (band == BAND_ON_2_4G) अणु
		चयन (rate_section) अणु
		हाल CCK:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][0] = value;
			अवरोध;
		हाल OFDM:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][1] = value;
			अवरोध;
		हाल HT_MCS0_MCS7:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][2] = value;
			अवरोध;
		हाल HT_MCS8_MCS15:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][3] = value;
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Invalid RateSection %d in Band 2.4G, Rf Path %d, %dTx in PHY_SetTxPowerByRateBase()\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Band %d in PHY_SetTxPowerByRateBase()\n",
			band);
	पूर्ण

पूर्ण

अटल u8 _rtl8723be_phy_get_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw,
						  u8 band, u8 path, u8 txnum,
						  u8 rate_section)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 value = 0;
	अगर (path > RF90_PATH_D) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Rf Path %d in PHY_GetTxPowerByRateBase()\n",
			path);
		वापस 0;
	पूर्ण

	अगर (band == BAND_ON_2_4G) अणु
		चयन (rate_section) अणु
		हाल CCK:
			value = rtlphy->txpwr_by_rate_base_24g[path][txnum][0];
			अवरोध;
		हाल OFDM:
			value = rtlphy->txpwr_by_rate_base_24g[path][txnum][1];
			अवरोध;
		हाल HT_MCS0_MCS7:
			value = rtlphy->txpwr_by_rate_base_24g[path][txnum][2];
			अवरोध;
		हाल HT_MCS8_MCS15:
			value = rtlphy->txpwr_by_rate_base_24g[path][txnum][3];
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Invalid RateSection %d in Band 2.4G, Rf Path %d, %dTx in PHY_GetTxPowerByRateBase()\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Band %d in PHY_GetTxPowerByRateBase()\n",
			band);
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम _rtl8723be_phy_store_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u16 rawvalue = 0;
	u8 base = 0, path = 0;

	क्रम (path = RF90_PATH_A; path <= RF90_PATH_B; ++path) अणु
		अगर (path == RF90_PATH_A) अणु
			rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset
				[BAND_ON_2_4G][path][RF_1TX][3] >> 24) & 0xFF;
			base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
			_rtl8723be_phy_set_txघातer_by_rate_base(hw,
				BAND_ON_2_4G, path, CCK, RF_1TX, base);
		पूर्ण अन्यथा अगर (path == RF90_PATH_B) अणु
			rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset
				[BAND_ON_2_4G][path][RF_1TX][3] >> 0) & 0xFF;
			base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
			_rtl8723be_phy_set_txघातer_by_rate_base(hw,
								BAND_ON_2_4G,
								path, CCK,
								RF_1TX, base);
		पूर्ण
		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset
				[BAND_ON_2_4G][path][RF_1TX][1] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8723be_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G,
							path, OFDM, RF_1TX,
							base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset
				[BAND_ON_2_4G][path][RF_1TX][5] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8723be_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G,
							path, HT_MCS0_MCS7,
							RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset
				[BAND_ON_2_4G][path][RF_2TX][7] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8723be_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G,
							path, HT_MCS8_MCS15,
							RF_2TX, base);
	पूर्ण
पूर्ण

अटल व्योम _phy_convert_txघातer_dbm_to_relative_value(u32 *data, u8 start,
						u8 end, u8 base_val)
अणु
	s8 i = 0;
	u8 temp_value = 0;
	u32 temp_data = 0;

	क्रम (i = 3; i >= 0; --i) अणु
		अगर (i >= start && i <= end) अणु
			/* Get the exact value */
			temp_value = (u8)(*data >> (i * 8)) & 0xF;
			temp_value += ((u8)((*data >> (i*8 + 4)) & 0xF)) * 10;

			/* Change the value to a relative value */
			temp_value = (temp_value > base_val) ?
				     temp_value - base_val :
				     base_val - temp_value;
		पूर्ण अन्यथा अणु
			temp_value = (u8)(*data >> (i * 8)) & 0xFF;
		पूर्ण
		temp_data <<= 8;
		temp_data |= temp_value;
	पूर्ण
	*data = temp_data;
पूर्ण

अटल व्योम _rtl8723be_phy_convert_txघातer_dbm_to_relative_value(
							काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 base = 0, rfpath = RF90_PATH_A;

	base = _rtl8723be_phy_get_txघातer_by_rate_base(hw,
			BAND_ON_2_4G, rfpath, RF_1TX, CCK);
	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][2],
	    1, 1, base);
	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][3],
	    1, 3, base);

	base = _rtl8723be_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G, rfpath,
						       RF_1TX, OFDM);
	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][0],
	    0, 3, base);
	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][1],
	    0, 3, base);

	base = _rtl8723be_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G,
						rfpath, RF_1TX, HT_MCS0_MCS7);
	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][4],
	    0, 3, base);
	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][5],
	    0, 3, base);

	base = _rtl8723be_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G,
						       rfpath, RF_2TX,
						       HT_MCS8_MCS15);
	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_2TX][6],
	    0, 3, base);

	_phy_convert_txघातer_dbm_to_relative_value(
	    &rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_2TX][7],
	    0, 3, base);

	rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
		"<===%s\n", __func__);
पूर्ण

अटल व्योम phy_txघातer_by_rate_config(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8723be_phy_store_txघातer_by_rate_base(hw);
	_rtl8723be_phy_convert_txघातer_dbm_to_relative_value(hw);
पूर्ण

अटल bool _rtl8723be_phy_bb8723b_config_parafile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus;

	/* चयन ant to BT */
	अगर (rtlpriv->rtlhal.पूर्णांकerface == INTF_USB) अणु
		rtl_ग_लिखो_dword(rtlpriv, 0x948, 0x0);
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->btcoexist.btc_info.single_ant_path == 0)
			rtl_ग_लिखो_dword(rtlpriv, 0x948, 0x280);
		अन्यथा
			rtl_ग_लिखो_dword(rtlpriv, 0x948, 0x0);
	पूर्ण

	rtstatus = _rtl8723be_phy_config_bb_with_headerfile(hw,
						BASEBAND_CONFIG_PHY_REG);
	अगर (!rtstatus) अणु
		pr_err("Write BB Reg Fail!!\n");
		वापस false;
	पूर्ण
	_rtl8723be_phy_init_tx_घातer_by_rate(hw);
	अगर (!rtlefuse->स्वतःload_failflag) अणु
		rtlphy->pwrgroup_cnt = 0;
		rtstatus = _rtl8723be_phy_config_bb_with_pgheaderfile(hw,
						BASEBAND_CONFIG_PHY_REG);
	पूर्ण
	phy_txघातer_by_rate_config(hw);
	अगर (!rtstatus) अणु
		pr_err("BB_PG Reg Fail!!\n");
		वापस false;
	पूर्ण
	rtstatus = _rtl8723be_phy_config_bb_with_headerfile(hw,
						BASEBAND_CONFIG_AGC_TAB);
	अगर (!rtstatus) अणु
		pr_err("AGC Table Fail\n");
		वापस false;
	पूर्ण
	rtlphy->cck_high_घातer = (bool)(rtl_get_bbreg(hw,
						      RFPGA0_XA_HSSIPARAMETER2,
						      0x200));
	वापस true;
पूर्ण

अटल bool rtl8723be_phy_config_with_headerfile(काष्ठा ieee80211_hw *hw,
						 u32 *array_table,
						 u16 arraylen,
		व्योम (*set_reg)(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 data))
अणु
	#घोषणा COND_ELSE  2
	#घोषणा COND_ENDIF 3

	पूर्णांक i = 0;
	u8 cond;
	bool matched = true, skipped = false;

	जबतक ((i + 1) < arraylen) अणु
		u32 v1 = array_table[i];
		u32 v2 = array_table[i + 1];

		अगर (v1 & (BIT(31) | BIT(30))) अणु/*positive & negative condition*/
			अगर (v1 & BIT(31)) अणु/* positive condition*/
				cond  = (u8)((v1 & (BIT(29) | BIT(28))) >> 28);
				अगर (cond == COND_ENDIF) अणु /*end*/
					matched = true;
					skipped = false;
				पूर्ण अन्यथा अगर (cond == COND_ELSE) अणु /*अन्यथा*/
					matched = skipped ? false : true;
				पूर्ण अन्यथा अणु/*अगर , अन्यथा अगर*/
					अगर (skipped) अणु
						matched = false;
					पूर्ण अन्यथा अणु
						अगर (_rtl8723be_check_positive(
								hw, v1, v2)) अणु
							matched = true;
							skipped = true;
						पूर्ण अन्यथा अणु
							matched = false;
							skipped = false;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अगर (v1 & BIT(30)) अणु /*negative condition*/
			/*करो nothing*/
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (matched)
				set_reg(hw, v1, v2);
		पूर्ण
		i = i + 2;
	पूर्ण

	वापस true;
पूर्ण

अटल bool _rtl8723be_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Read rtl8723beMACPHY_Array\n");

	वापस rtl8723be_phy_config_with_headerfile(hw,
			RTL8723BEMAC_1T_ARRAY, RTL8723BEMAC_1T_ARRAYLEN,
			rtl_ग_लिखो_byte_with_val32);
पूर्ण

अटल bool _rtl8723be_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
						     u8 configtype)
अणु

	अगर (configtype == BASEBAND_CONFIG_PHY_REG)
		वापस rtl8723be_phy_config_with_headerfile(hw,
				RTL8723BEPHY_REG_1TARRAY,
				RTL8723BEPHY_REG_1TARRAYLEN,
				_rtl8723be_config_bb_reg);
	अन्यथा अगर (configtype == BASEBAND_CONFIG_AGC_TAB)
		वापस rtl8723be_phy_config_with_headerfile(hw,
				RTL8723BEAGCTAB_1TARRAY,
				RTL8723BEAGCTAB_1TARRAYLEN,
				rtl_set_bbreg_with_dwmask);

	वापस false;
पूर्ण

अटल u8 _rtl8723be_get_rate_section_index(u32 regaddr)
अणु
	u8 index = 0;

	चयन (regaddr) अणु
	हाल RTXAGC_A_RATE18_06:
		index = 0;
	अवरोध;
	हाल RTXAGC_A_RATE54_24:
		index = 1;
	अवरोध;
	हाल RTXAGC_A_CCK1_MCS32:
		index = 2;
	अवरोध;
	हाल RTXAGC_B_CCK11_A_CCK2_11:
		index = 3;
	अवरोध;
	हाल RTXAGC_A_MCS03_MCS00:
		index = 4;
	अवरोध;
	हाल RTXAGC_A_MCS07_MCS04:
		index = 5;
	अवरोध;
	हाल RTXAGC_A_MCS11_MCS08:
		index = 6;
	अवरोध;
	हाल RTXAGC_A_MCS15_MCS12:
		index = 7;
	अवरोध;
	हाल RTXAGC_B_RATE18_06:
		index = 0;
	अवरोध;
	हाल RTXAGC_B_RATE54_24:
		index = 1;
	अवरोध;
	हाल RTXAGC_B_CCK1_55_MCS32:
		index = 2;
	अवरोध;
	हाल RTXAGC_B_MCS03_MCS00:
		index = 4;
	अवरोध;
	हाल RTXAGC_B_MCS07_MCS04:
		index = 5;
	अवरोध;
	हाल RTXAGC_B_MCS11_MCS08:
		index = 6;
	अवरोध;
	हाल RTXAGC_B_MCS15_MCS12:
		index = 7;
	अवरोध;
	शेष:
		regaddr &= 0xFFF;
		अगर (regaddr >= 0xC20 && regaddr <= 0xC4C)
			index = (u8)((regaddr - 0xC20) / 4);
		अन्यथा अगर (regaddr >= 0xE20 && regaddr <= 0xE4C)
			index = (u8)((regaddr - 0xE20) / 4);
		अवरोध;
	पूर्ण
	वापस index;
पूर्ण

अटल व्योम _rtl8723be_store_tx_घातer_by_rate(काष्ठा ieee80211_hw *hw,
					      u32 band, u32 rfpath,
					      u32 txnum, u32 regaddr,
					      u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 rate_section = _rtl8723be_get_rate_section_index(regaddr);

	अगर (band != BAND_ON_2_4G && band != BAND_ON_5G) अणु
		rtl_dbg(rtlpriv, FPHY, PHY_TXPWR, "Invalid Band %d\n", band);
		वापस;
	पूर्ण
	अगर (rfpath > MAX_RF_PATH - 1) अणु
		rtl_dbg(rtlpriv, FPHY, PHY_TXPWR,
			"Invalid RfPath %d\n", rfpath);
		वापस;
	पूर्ण
	अगर (txnum > MAX_RF_PATH - 1) अणु
		rtl_dbg(rtlpriv, FPHY, PHY_TXPWR, "Invalid TxNum %d\n", txnum);
		वापस;
	पूर्ण

	rtlphy->tx_घातer_by_rate_offset[band][rfpath][txnum][rate_section] =
									data;

पूर्ण

अटल bool _rtl8723be_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
						       u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;
	u32 *phy_regarray_table_pg;
	u16 phy_regarray_pg_len;
	u32 v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0, v6 = 0;

	phy_regarray_pg_len = RTL8723BEPHY_REG_ARRAY_PGLEN;
	phy_regarray_table_pg = RTL8723BEPHY_REG_ARRAY_PG;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_regarray_pg_len; i = i + 6) अणु
			v1 = phy_regarray_table_pg[i];
			v2 = phy_regarray_table_pg[i+1];
			v3 = phy_regarray_table_pg[i+2];
			v4 = phy_regarray_table_pg[i+3];
			v5 = phy_regarray_table_pg[i+4];
			v6 = phy_regarray_table_pg[i+5];

			अगर (v1 < 0xcdcdcdcd) अणु
				अगर (phy_regarray_table_pg[i] == 0xfe ||
				    phy_regarray_table_pg[i] == 0xffe)
					mdelay(50);
				अन्यथा
					_rtl8723be_store_tx_घातer_by_rate(hw,
							v1, v2, v3, v4, v5, v6);
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"configtype != BaseBand_Config_PHY_REG\n");
	पूर्ण
	वापस true;
पूर्ण

bool rtl8723be_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					     क्रमागत radio_path rfpath)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool ret = true;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		ret =  rtl8723be_phy_config_with_headerfile(hw,
				RTL8723BE_RADIOA_1TARRAY,
				RTL8723BE_RADIOA_1TARRAYLEN,
				_rtl8723be_config_rf_radio_a);

		अगर (rtlhal->oem_id == RT_CID_819X_HP)
			_rtl8723be_config_rf_radio_a(hw, 0x52, 0x7E4BD);
		अवरोध;
	हाल RF90_PATH_B:
	हाल RF90_PATH_C:
		अवरोध;
	हाल RF90_PATH_D:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", rfpath);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

व्योम rtl8723be_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	rtlphy->शेष_initialgain[0] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[1] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[2] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XCAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[3] =
	    (u8)rtl_get_bbreg(hw, ROFDM0_XDAGCCORE1, MASKBYTE0);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"Default initial gain (c50=0x%x, c58=0x%x, c60=0x%x, c68=0x%x\n",
		rtlphy->शेष_initialgain[0],
		rtlphy->शेष_initialgain[1],
		rtlphy->शेष_initialgain[2],
		rtlphy->शेष_initialgain[3]);

	rtlphy->framesync = (u8)rtl_get_bbreg(hw, ROFDM0_RXDETECTOR3,
					       MASKBYTE0);
	rtlphy->framesync_c34 = rtl_get_bbreg(hw, ROFDM0_RXDETECTOR2,
					      MASKDWORD);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"Default framesync (0x%x) = 0x%x\n",
		ROFDM0_RXDETECTOR3, rtlphy->framesync);
पूर्ण

अटल u8 _rtl8723be_phy_get_ratesection_पूर्णांकxघातer_byrate(क्रमागत radio_path path,
							  u8 rate)
अणु
	u8 rate_section = 0;

	चयन (rate) अणु
	हाल DESC92C_RATE1M:
		rate_section = 2;
		अवरोध;

	हाल DESC92C_RATE2M:
	हाल DESC92C_RATE5_5M:
		अगर (path == RF90_PATH_A)
			rate_section = 3;
		अन्यथा अगर (path == RF90_PATH_B)
			rate_section = 2;
		अवरोध;

	हाल DESC92C_RATE11M:
		rate_section = 3;
		अवरोध;

	हाल DESC92C_RATE6M:
	हाल DESC92C_RATE9M:
	हाल DESC92C_RATE12M:
	हाल DESC92C_RATE18M:
		rate_section = 0;
		अवरोध;

	हाल DESC92C_RATE24M:
	हाल DESC92C_RATE36M:
	हाल DESC92C_RATE48M:
	हाल DESC92C_RATE54M:
		rate_section = 1;
		अवरोध;

	हाल DESC92C_RATEMCS0:
	हाल DESC92C_RATEMCS1:
	हाल DESC92C_RATEMCS2:
	हाल DESC92C_RATEMCS3:
		rate_section = 4;
		अवरोध;

	हाल DESC92C_RATEMCS4:
	हाल DESC92C_RATEMCS5:
	हाल DESC92C_RATEMCS6:
	हाल DESC92C_RATEMCS7:
		rate_section = 5;
		अवरोध;

	हाल DESC92C_RATEMCS8:
	हाल DESC92C_RATEMCS9:
	हाल DESC92C_RATEMCS10:
	हाल DESC92C_RATEMCS11:
		rate_section = 6;
		अवरोध;

	हाल DESC92C_RATEMCS12:
	हाल DESC92C_RATEMCS13:
	हाल DESC92C_RATEMCS14:
	हाल DESC92C_RATEMCS15:
		rate_section = 7;
		अवरोध;

	शेष:
		WARN_ONCE(true, "rtl8723be: Rate_Section is Illegal\n");
		अवरोध;
	पूर्ण

	वापस rate_section;
पूर्ण

अटल u8 _rtl8723be_get_txघातer_by_rate(काष्ठा ieee80211_hw *hw,
					 क्रमागत band_type band,
					 क्रमागत radio_path rfpath, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 shअगरt = 0, rate_section, tx_num;
	s8 tx_pwr_dअगरf = 0;

	rate_section = _rtl8723be_phy_get_ratesection_पूर्णांकxघातer_byrate(rfpath,
								       rate);
	tx_num = RF_TX_NUM_NONIMPLEMENT;

	अगर (tx_num == RF_TX_NUM_NONIMPLEMENT) अणु
		अगर (rate >= DESC92C_RATEMCS8 && rate <= DESC92C_RATEMCS15)
			tx_num = RF_2TX;
		अन्यथा
			tx_num = RF_1TX;
	पूर्ण

	चयन (rate) अणु
	हाल DESC92C_RATE6M:
	हाल DESC92C_RATE24M:
	हाल DESC92C_RATEMCS0:
	हाल DESC92C_RATEMCS4:
	हाल DESC92C_RATEMCS8:
	हाल DESC92C_RATEMCS12:
		shअगरt = 0;
		अवरोध;
	हाल DESC92C_RATE1M:
	हाल DESC92C_RATE2M:
	हाल DESC92C_RATE9M:
	हाल DESC92C_RATE36M:
	हाल DESC92C_RATEMCS1:
	हाल DESC92C_RATEMCS5:
	हाल DESC92C_RATEMCS9:
	हाल DESC92C_RATEMCS13:
		shअगरt = 8;
		अवरोध;
	हाल DESC92C_RATE5_5M:
	हाल DESC92C_RATE12M:
	हाल DESC92C_RATE48M:
	हाल DESC92C_RATEMCS2:
	हाल DESC92C_RATEMCS6:
	हाल DESC92C_RATEMCS10:
	हाल DESC92C_RATEMCS14:
		shअगरt = 16;
		अवरोध;
	हाल DESC92C_RATE11M:
	हाल DESC92C_RATE18M:
	हाल DESC92C_RATE54M:
	हाल DESC92C_RATEMCS3:
	हाल DESC92C_RATEMCS7:
	हाल DESC92C_RATEMCS11:
	हाल DESC92C_RATEMCS15:
		shअगरt = 24;
		अवरोध;
	शेष:
		WARN_ONCE(true, "rtl8723be: Rate_Section is Illegal\n");
		अवरोध;
	पूर्ण
	tx_pwr_dअगरf = (u8)(rtlphy->tx_घातer_by_rate_offset[band][rfpath][tx_num]
					  [rate_section] >> shअगरt) & 0xff;

	वापस	tx_pwr_dअगरf;
पूर्ण

अटल u8 _rtl8723be_get_txघातer_index(काष्ठा ieee80211_hw *hw, u8 path,
				       u8 rate, u8 bandwidth, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);
	u8 txघातer = 0;
	u8 घातer_dअगरf_byrate = 0;

	अगर (channel > 14 || channel < 1) अणु
		index = 0;
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Illegal channel!\n");
	पूर्ण
	अगर (RX_HAL_IS_CCK_RATE(rate))
		txघातer = rtlefuse->txpwrlevel_cck[path][index];
	अन्यथा अगर (DESC92C_RATE6M <= rate)
		txघातer = rtlefuse->txpwrlevel_ht40_1s[path][index];
	अन्यथा
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"invalid rate\n");

	अगर (DESC92C_RATE6M <= rate && rate <= DESC92C_RATE54M &&
	    !RX_HAL_IS_CCK_RATE(rate))
		txघातer += rtlefuse->txpwr_legacyhtdअगरf[0][TX_1S];

	अगर (bandwidth == HT_CHANNEL_WIDTH_20) अणु
		अगर (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			txघातer += rtlefuse->txpwr_ht20dअगरf[0][TX_1S];
		अगर (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			txघातer += rtlefuse->txpwr_ht20dअगरf[0][TX_2S];
	पूर्ण अन्यथा अगर (bandwidth == HT_CHANNEL_WIDTH_20_40) अणु
		अगर (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			txघातer += rtlefuse->txpwr_ht40dअगरf[0][TX_1S];
		अगर (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			txघातer += rtlefuse->txpwr_ht40dअगरf[0][TX_2S];
	पूर्ण

	अगर (rtlefuse->eeprom_regulatory != 2)
		घातer_dअगरf_byrate = _rtl8723be_get_txघातer_by_rate(hw,
								   BAND_ON_2_4G,
								   path, rate);

	txघातer += घातer_dअगरf_byrate;

	अगर (txघातer > MAX_POWER_INDEX)
		txघातer = MAX_POWER_INDEX;

	वापस txघातer;
पूर्ण

अटल व्योम _rtl8723be_phy_set_txघातer_index(काष्ठा ieee80211_hw *hw,
					     u8 घातer_index, u8 path, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अगर (path == RF90_PATH_A) अणु
		चयन (rate) अणु
		हाल DESC92C_RATE1M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_CCK1_MCS32,
					       MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC92C_RATE2M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_B_CCK11_A_CCK2_11,
					       MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC92C_RATE5_5M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_B_CCK11_A_CCK2_11,
					       MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC92C_RATE11M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_B_CCK11_A_CCK2_11,
					       MASKBYTE3, घातer_index);
			अवरोध;

		हाल DESC92C_RATE6M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC92C_RATE9M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC92C_RATE12M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC92C_RATE18M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE18_06,
					       MASKBYTE3, घातer_index);
			अवरोध;

		हाल DESC92C_RATE24M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC92C_RATE36M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC92C_RATE48M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC92C_RATE54M:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_RATE54_24,
					       MASKBYTE3, घातer_index);
			अवरोध;

		हाल DESC92C_RATEMCS0:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS1:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS2:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS3:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS03_MCS00,
					       MASKBYTE3, घातer_index);
			अवरोध;

		हाल DESC92C_RATEMCS4:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS5:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS6:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS7:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS07_MCS04,
					       MASKBYTE3, घातer_index);
			अवरोध;

		हाल DESC92C_RATEMCS8:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS9:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS10:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC92C_RATEMCS11:
			rtl8723_phy_set_bb_reg(hw, RTXAGC_A_MCS11_MCS08,
					       MASKBYTE3, घातer_index);
			अवरोध;

		शेष:
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "Invalid Rate!!\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "Invalid RFPath!!\n");
	पूर्ण
पूर्ण

व्योम rtl8723be_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 cck_rates[]  = अणुDESC92C_RATE1M, DESC92C_RATE2M,
			   DESC92C_RATE5_5M, DESC92C_RATE11Mपूर्ण;
	u8 ofdm_rates[]  = अणुDESC92C_RATE6M, DESC92C_RATE9M,
			    DESC92C_RATE12M, DESC92C_RATE18M,
			    DESC92C_RATE24M, DESC92C_RATE36M,
			    DESC92C_RATE48M, DESC92C_RATE54Mपूर्ण;
	u8 ht_rates_1t[]  = अणुDESC92C_RATEMCS0, DESC92C_RATEMCS1,
			     DESC92C_RATEMCS2, DESC92C_RATEMCS3,
			     DESC92C_RATEMCS4, DESC92C_RATEMCS5,
			     DESC92C_RATEMCS6, DESC92C_RATEMCS7पूर्ण;
	u8 i;
	u8 घातer_index;

	अगर (!rtlefuse->txpwr_fromeprom)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(cck_rates); i++) अणु
		घातer_index = _rtl8723be_get_txघातer_index(hw, RF90_PATH_A,
					cck_rates[i],
					rtl_priv(hw)->phy.current_chan_bw,
					channel);
		_rtl8723be_phy_set_txघातer_index(hw, घातer_index, RF90_PATH_A,
						 cck_rates[i]);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(ofdm_rates); i++) अणु
		घातer_index = _rtl8723be_get_txघातer_index(hw, RF90_PATH_A,
					ofdm_rates[i],
					rtl_priv(hw)->phy.current_chan_bw,
					channel);
		_rtl8723be_phy_set_txघातer_index(hw, घातer_index, RF90_PATH_A,
						 ofdm_rates[i]);
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(ht_rates_1t); i++) अणु
		घातer_index = _rtl8723be_get_txघातer_index(hw, RF90_PATH_A,
					ht_rates_1t[i],
					rtl_priv(hw)->phy.current_chan_bw,
					channel);
		_rtl8723be_phy_set_txघातer_index(hw, घातer_index, RF90_PATH_A,
						 ht_rates_1t[i]);
	पूर्ण
पूर्ण

व्योम rtl8723be_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw, u8 operation)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	क्रमागत io_type iotype;

	अगर (!is_hal_stop(rtlhal)) अणु
		चयन (operation) अणु
		हाल SCAN_OPT_BACKUP_BAND0:
			iotype = IO_CMD_PAUSE_BAND0_DM_BY_SCAN;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_IO_CMD,
						      (u8 *)&iotype);

			अवरोध;
		हाल SCAN_OPT_RESTORE:
			iotype = IO_CMD_RESUME_DM_BY_SCAN;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_IO_CMD,
						      (u8 *)&iotype);
			अवरोध;
		शेष:
			pr_err("Unknown Scan Backup operation.\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl8723be_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 reg_bw_opmode;
	u8 reg_prsr_rsc;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"Switch to %s bandwidth\n",
		rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		"20MHz" : "40MHz");

	अगर (is_hal_stop(rtlhal)) अणु
		rtlphy->set_bwmode_inprogress = false;
		वापस;
	पूर्ण

	reg_bw_opmode = rtl_पढ़ो_byte(rtlpriv, REG_BWOPMODE);
	reg_prsr_rsc = rtl_पढ़ो_byte(rtlpriv, REG_RRSR + 2);

	चयन (rtlphy->current_chan_bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		reg_bw_opmode |= BW_OPMODE_20MHZ;
		rtl_ग_लिखो_byte(rtlpriv, REG_BWOPMODE, reg_bw_opmode);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		reg_bw_opmode &= ~BW_OPMODE_20MHZ;
		rtl_ग_लिखो_byte(rtlpriv, REG_BWOPMODE, reg_bw_opmode);
		reg_prsr_rsc = (reg_prsr_rsc & 0x90) |
			       (mac->cur_40_prime_sc << 5);
		rtl_ग_लिखो_byte(rtlpriv, REG_RRSR + 2, reg_prsr_rsc);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण

	चयन (rtlphy->current_chan_bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x0);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x0);
	/*	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10), 1);*/
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x1);

		rtl_set_bbreg(hw, RCCK0_SYSTEM, BCCK_SIDEBAND,
			      (mac->cur_40_prime_sc >> 1));
		rtl_set_bbreg(hw, ROFDM1_LSTF, 0xC00, mac->cur_40_prime_sc);
		/*rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10), 0);*/

		rtl_set_bbreg(hw, 0x818, (BIT(26) | BIT(27)),
			      (mac->cur_40_prime_sc ==
			       HAL_PRIME_CHNL_OFFSET_LOWER) ? 2 : 1);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण
	rtl8723be_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD, "\n");
पूर्ण

व्योम rtl8723be_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_bw = rtlphy->current_chan_bw;

	अगर (rtlphy->set_bwmode_inprogress)
		वापस;
	rtlphy->set_bwmode_inprogress = true;
	अगर ((!is_hal_stop(rtlhal)) && !(RT_CANNOT_IO(hw))) अणु
		rtl8723be_phy_set_bw_mode_callback(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"false driver sleep or unload\n");
		rtlphy->set_bwmode_inprogress = false;
		rtlphy->current_chan_bw = पंचांगp_bw;
	पूर्ण
पूर्ण

व्योम rtl8723be_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 delay = 0;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"switch to channel%d\n", rtlphy->current_channel);
	अगर (is_hal_stop(rtlhal))
		वापस;
	करो अणु
		अगर (!rtlphy->sw_chnl_inprogress)
			अवरोध;
		अगर (!_rtl8723be_phy_sw_chnl_step_by_step(hw,
							 rtlphy->current_channel,
							 &rtlphy->sw_chnl_stage,
							 &rtlphy->sw_chnl_step,
							 &delay)) अणु
			अगर (delay > 0)
				mdelay(delay);
			अन्यथा
				जारी;
		पूर्ण अन्यथा अणु
			rtlphy->sw_chnl_inprogress = false;
		पूर्ण
		अवरोध;
	पूर्ण जबतक (true);
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "\n");
पूर्ण

u8 rtl8723be_phy_sw_chnl(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlphy->sw_chnl_inprogress)
		वापस 0;
	अगर (rtlphy->set_bwmode_inprogress)
		वापस 0;
	WARN_ONCE((rtlphy->current_channel > 14),
		  "rtl8723be: WIRELESS_MODE_G but channel>14");
	rtlphy->sw_chnl_inprogress = true;
	rtlphy->sw_chnl_stage = 0;
	rtlphy->sw_chnl_step = 0;
	अगर (!(is_hal_stop(rtlhal)) && !(RT_CANNOT_IO(hw))) अणु
		rtl8723be_phy_sw_chnl_callback(hw);
		rtl_dbg(rtlpriv, COMP_CHAN, DBG_LOUD,
			"sw_chnl_inprogress false schedule workitem current channel %d\n",
			rtlphy->current_channel);
		rtlphy->sw_chnl_inprogress = false;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_CHAN, DBG_LOUD,
			"sw_chnl_inprogress false driver sleep or unload\n");
		rtlphy->sw_chnl_inprogress = false;
	पूर्ण
	वापस 1;
पूर्ण

अटल bool _rtl8723be_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
						u8 channel, u8 *stage,
						u8 *step, u32 *delay)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा swchnlcmd precommoncmd[MAX_PRECMD_CNT];
	u32 precommoncmdcnt;
	काष्ठा swchnlcmd postcommoncmd[MAX_POSTCMD_CNT];
	u32 postcommoncmdcnt;
	काष्ठा swchnlcmd rfdependcmd[MAX_RFDEPENDCMD_CNT];
	u32 rfdependcmdcnt;
	काष्ठा swchnlcmd *currentcmd = शून्य;
	u8 rfpath;
	u8 num_total_rfpath = rtlphy->num_total_rfpath;

	precommoncmdcnt = 0;
	rtl8723_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					 MAX_PRECMD_CNT,
					 CMDID_SET_TXPOWEROWER_LEVEL,
					 0, 0, 0);
	rtl8723_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					 MAX_PRECMD_CNT, CMDID_END, 0, 0, 0);

	postcommoncmdcnt = 0;

	rtl8723_phy_set_sw_chnl_cmdarray(postcommoncmd, postcommoncmdcnt++,
					 MAX_POSTCMD_CNT, CMDID_END,
					    0, 0, 0);

	rfdependcmdcnt = 0;

	WARN_ONCE((channel < 1 || channel > 14),
		  "rtl8723be: illegal channel for Zebra: %d\n", channel);

	rtl8723_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					 MAX_RFDEPENDCMD_CNT,
					 CMDID_RF_WRITEREG,
					 RF_CHNLBW, channel, 10);

	rtl8723_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					 MAX_RFDEPENDCMD_CNT,
					    CMDID_END, 0, 0, 0);

	करो अणु
		चयन (*stage) अणु
		हाल 0:
			currentcmd = &precommoncmd[*step];
			अवरोध;
		हाल 1:
			currentcmd = &rfdependcmd[*step];
			अवरोध;
		हाल 2:
			currentcmd = &postcommoncmd[*step];
			अवरोध;
		शेष:
			pr_err("Invalid 'stage' = %d, Check it!\n",
			       *stage);
			वापस true;
		पूर्ण

		अगर (currentcmd->cmdid == CMDID_END) अणु
			अगर ((*stage) == 2) अणु
				वापस true;
			पूर्ण अन्यथा अणु
				(*stage)++;
				(*step) = 0;
				जारी;
			पूर्ण
		पूर्ण

		चयन (currentcmd->cmdid) अणु
		हाल CMDID_SET_TXPOWEROWER_LEVEL:
			rtl8723be_phy_set_txघातer_level(hw, channel);
			अवरोध;
		हाल CMDID_WRITEPORT_ULONG:
			rtl_ग_लिखो_dword(rtlpriv, currentcmd->para1,
					currentcmd->para2);
			अवरोध;
		हाल CMDID_WRITEPORT_USHORT:
			rtl_ग_लिखो_word(rtlpriv, currentcmd->para1,
				       (u16)currentcmd->para2);
			अवरोध;
		हाल CMDID_WRITEPORT_UCHAR:
			rtl_ग_लिखो_byte(rtlpriv, currentcmd->para1,
				       (u8)currentcmd->para2);
			अवरोध;
		हाल CMDID_RF_WRITEREG:
			क्रम (rfpath = 0; rfpath < num_total_rfpath; rfpath++) अणु
				rtlphy->rfreg_chnlval[rfpath] =
				    ((rtlphy->rfreg_chnlval[rfpath] &
				      0xfffffc00) | currentcmd->para2);

				rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath,
					      currentcmd->para1,
					      RFREG_OFFSET_MASK,
					      rtlphy->rfreg_chnlval[rfpath]);
			पूर्ण
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
				"switch case %#x not processed\n",
				currentcmd->cmdid);
			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण जबतक (true);

	(*delay) = currentcmd->msdelay;
	(*step)++;
	वापस false;
पूर्ण

अटल u8 _rtl8723be_phy_path_a_iqk(काष्ठा ieee80211_hw *hw)
अणु
	u32 reg_eac, reg_e94, reg_e9c, पंचांगp;
	u8 result = 0x00;

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	/* चयन to path A */
	rtl_set_bbreg(hw, 0x948, MASKDWORD, 0x00000000);
	/* enable path A PA in TXIQK mode */
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x20000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0003f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xc7f87);

	/* 1. TX IQK */
	/* path-A IQK setting */
	/* IQK setting */
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);
	/* path-A IQK setting */
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x821403ea);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28160000);
	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28110000);
	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x00462911);
	/* enter IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* One shot, path A LOK & IQK */
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, 0xe94, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, 0xe9c, MASKDWORD);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा /* अगर Tx not OK, ignore Rx */
		वापस result;

	/* Allen 20131125 */
	पंचांगp = (reg_e9c & 0x03FF0000) >> 16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) < 0x110) &&
	    (((reg_e94 & 0x03FF0000) >> 16) > 0xf0) &&
	    (पंचांगp < 0xf))
		result |= 0x01;
	अन्यथा /* अगर Tx not OK, ignore Rx */
		वापस result;

	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 _rtl8723be_phy_path_a_rx_iqk(काष्ठा ieee80211_hw *hw)
अणु
	u32 reg_eac, reg_e94, reg_e9c, reg_ea4, u32पंचांगp, पंचांगp;
	u8 result = 0x00;

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	/* चयन to path A */
	rtl_set_bbreg(hw, 0x948, MASKDWORD, 0x00000000);

	/* 1 Get TXIMR setting */
	/* modअगरy RXIQK mode table */
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0001f);
	/* LNA2 off, PA on क्रम Dcut */
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf7fb7);
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* IQK setting */
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/* path-A IQK setting */
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82160ff0);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28110000);
	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28110000);

	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a911);

	/* enter IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* One shot, path A LOK & IQK */
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, RTX_POWER_BEFORE_IQK_A, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_A, MASKDWORD);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा /* अगर Tx not OK, ignore Rx */
		वापस result;

	/* Allen 20131125 */
	पंचांगp = (reg_e9c & 0x03FF0000) >> 16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) < 0x110) &&
	    (((reg_e94 & 0x03FF0000) >> 16) > 0xf0) &&
	    (पंचांगp < 0xf))
		result |= 0x01;
	अन्यथा /* अगर Tx not OK, ignore Rx */
		वापस result;

	u32पंचांगp = 0x80007C00 | (reg_e94 & 0x3FF0000) |
		 ((reg_e9c & 0x3FF0000) >> 16);
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, u32पंचांगp);

	/* 1 RX IQK */
	/* modअगरy RXIQK mode table */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0001f);
	/* LAN2 on, PA off क्रम Dcut */
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf7d77);

	/* PA, PAD setting */
	rtl_set_rfreg(hw, RF90_PATH_A, 0xdf, RFREG_OFFSET_MASK, 0xf80);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x55, RFREG_OFFSET_MASK, 0x4021f);

	/* IQK setting */
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/* path-A IQK setting */
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x2816001f);
	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28110000);

	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a8d1);

	/* enter IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* One shot, path A LOK & IQK */
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_ea4 = rtl_get_bbreg(hw, RRX_POWER_BEFORE_IQK_A_2, MASKDWORD);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_A, 0xdf, RFREG_OFFSET_MASK, 0x780);

	/* Allen 20131125 */
	पंचांगp = (reg_eac & 0x03FF0000) >> 16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;
	/* अगर Tx is OK, check whether Rx is OK */
	अगर (!(reg_eac & BIT(27)) &&
	    (((reg_ea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_eac & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा अगर (!(reg_eac & BIT(27)) &&
		 (((reg_ea4 & 0x03FF0000) >> 16) < 0x110) &&
		 (((reg_ea4 & 0x03FF0000) >> 16) > 0xf0) &&
		 (पंचांगp < 0xf))
		result |= 0x02;

	वापस result;
पूर्ण

अटल u8 _rtl8723be_phy_path_b_iqk(काष्ठा ieee80211_hw *hw)
अणु
	u32 reg_eac, reg_e94, reg_e9c, पंचांगp;
	u8 result = 0x00;

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	/* चयन to path B */
	rtl_set_bbreg(hw, 0x948, MASKDWORD, 0x00000280);

	/* enable path B PA in TXIQK mode */
	rtl_set_rfreg(hw, RF90_PATH_A, 0xed, RFREG_OFFSET_MASK, 0x00020);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x43, RFREG_OFFSET_MASK, 0x40fc1);

	/* 1 Tx IQK */
	/* IQK setting */
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);
	/* path-A IQK setting */
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x821403ea);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28110000);
	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28110000);

	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x00462911);

	/* enter IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* One shot, path B LOK & IQK */
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, RTX_POWER_BEFORE_IQK_A, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_A, MASKDWORD);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा
		वापस result;

	/* Allen 20131125 */
	पंचांगp = (reg_e9c & 0x03FF0000) >> 16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) < 0x110) &&
	    (((reg_e94 & 0x03FF0000) >> 16) > 0xf0) &&
	    (पंचांगp < 0xf))
		result |= 0x01;
	अन्यथा
		वापस result;

	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 _rtl8723be_phy_path_b_rx_iqk(काष्ठा ieee80211_hw *hw)
अणु
	u32 reg_e94, reg_e9c, reg_ea4, reg_eac, u32पंचांगp, पंचांगp;
	u8 result = 0x00;

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	/* चयन to path B */
	rtl_set_bbreg(hw, 0x948, MASKDWORD, 0x00000280);

	/* 1 Get TXIMR setting */
	/* modअगरy RXIQK mode table */
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0001f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf7ff7);

	/* खोलो PA S1 & SMIXER */
	rtl_set_rfreg(hw, RF90_PATH_A, 0xed, RFREG_OFFSET_MASK, 0x00020);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x43, RFREG_OFFSET_MASK, 0x60fed);

	/* IQK setting */
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/* path-B IQK setting */
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82160ff0);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28110000);
	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28110000);

	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a911);
	/* enter IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* One shot, path B TXIQK @ RXIQK */
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, RTX_POWER_BEFORE_IQK_A, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_A, MASKDWORD);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा	/* अगर Tx not OK, ignore Rx */
		वापस result;

	/* Allen 20131125 */
	पंचांगp = (reg_e9c & 0x03FF0000) >> 16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) < 0x110) &&
	    (((reg_e94 & 0x03FF0000) >> 16) > 0xf0) &&
	    (पंचांगp < 0xf))
		result |= 0x01;
	अन्यथा
		वापस result;

	u32पंचांगp = 0x80007C00 | (reg_e94 & 0x3FF0000)  |
		 ((reg_e9c & 0x3FF0000) >> 16);
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, u32पंचांगp);

	/* 1 RX IQK */

	/* <20121009, Kordan> RF Mode = 3 */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0001f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf7d77);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, 0x80000, 0x0);

	/* खोलो PA S1 & बंद SMIXER */
	rtl_set_rfreg(hw, RF90_PATH_A, 0xed, RFREG_OFFSET_MASK, 0x00020);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x43, RFREG_OFFSET_MASK, 0x60fbd);

	/* IQK setting */
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/* path-B IQK setting */
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x2816001f);
	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28110000);

	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a8d1);
	/* enter IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/* One shot, path B LOK & IQK */
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* leave IQK mode */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_ea4 = rtl_get_bbreg(hw, RRX_POWER_BEFORE_IQK_A_2, MASKDWORD);

	/* Allen 20131125 */
	पंचांगp = (reg_eac & 0x03FF0000) >> 16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	/* अगर Tx is OK, check whether Rx is OK */
	अगर (!(reg_eac & BIT(27)) &&
	    (((reg_ea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_eac & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा अगर (!(reg_eac & BIT(27)) &&
		 (((reg_ea4 & 0x03FF0000) >> 16) < 0x110) &&
		 (((reg_ea4 & 0x03FF0000) >> 16) > 0xf0) &&
		 (पंचांगp < 0xf))
		result |= 0x02;
	अन्यथा
		वापस result;

	वापस result;
पूर्ण

अटल व्योम _rtl8723be_phy_path_b_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
						  bool b_iqk_ok,
						  दीर्घ result[][8],
						  u8 final_candidate,
						  bool btxonly)
अणु
	u32 oldval_1, x, tx1_a, reg;
	दीर्घ y, tx1_c;

	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (b_iqk_ok) अणु
		oldval_1 = (rtl_get_bbreg(hw, ROFDM0_XBTXIQIMBALANCE,
					  MASKDWORD) >> 22) & 0x3FF;
		x = result[final_candidate][4];
		अगर ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;
		tx1_a = (x * oldval_1) >> 8;
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, 0x3FF, tx1_a);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(27),
			      ((x * oldval_1 >> 7) & 0x1));
		y = result[final_candidate][5];
		अगर ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;
		tx1_c = (y * oldval_1) >> 8;
		rtl_set_bbreg(hw, ROFDM0_XDTXAFE, 0xF0000000,
			      ((tx1_c & 0x3C0) >> 6));
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, 0x003F0000,
			      (tx1_c & 0x3F));
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(25),
			      ((y * oldval_1 >> 7) & 0x1));
		अगर (btxonly)
			वापस;
		reg = result[final_candidate][6];
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0x3FF, reg);
		reg = result[final_candidate][7] & 0x3F;
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0xFC00, reg);
		reg = (result[final_candidate][7] >> 6) & 0xF;
		/* rtl_set_bbreg(hw, 0xca0, 0xF0000000, reg); */
	पूर्ण
पूर्ण

अटल bool _rtl8723be_phy_simularity_compare(काष्ठा ieee80211_hw *hw,
					      दीर्घ result[][8], u8 c1, u8 c2)
अणु
	u32 i, j, dअगरf, simularity_biपंचांगap, bound = 0;

	u8 final_candidate[2] = अणु0xFF, 0xFFपूर्ण; /* क्रम path A and path B */
	bool bresult = true; /* is2t = true*/
	s32 पंचांगp1 = 0, पंचांगp2 = 0;

	bound = 8;

	simularity_biपंचांगap = 0;

	क्रम (i = 0; i < bound; i++) अणु
		अगर ((i == 1) || (i == 3) || (i == 5) || (i == 7)) अणु
			अगर ((result[c1][i] & 0x00000200) != 0)
				पंचांगp1 = result[c1][i] | 0xFFFFFC00;
			अन्यथा
				पंचांगp1 = result[c1][i];

			अगर ((result[c2][i] & 0x00000200) != 0)
				पंचांगp2 = result[c2][i] | 0xFFFFFC00;
			अन्यथा
				पंचांगp2 = result[c2][i];
		पूर्ण अन्यथा अणु
			पंचांगp1 = result[c1][i];
			पंचांगp2 = result[c2][i];
		पूर्ण

		dअगरf = (पंचांगp1 > पंचांगp2) ? (पंचांगp1 - पंचांगp2) : (पंचांगp2 - पंचांगp1);

		अगर (dअगरf > MAX_TOLERANCE) अणु
			अगर ((i == 2 || i == 6) && !simularity_biपंचांगap) अणु
				अगर (result[c1][i] + result[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				अन्यथा अगर (result[c2][i] + result[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				अन्यथा
					simularity_biपंचांगap |= (1 << i);
			पूर्ण अन्यथा
				simularity_biपंचांगap |= (1 << i);
		पूर्ण
	पूर्ण

	अगर (simularity_biपंचांगap == 0) अणु
		क्रम (i = 0; i < (bound / 4); i++) अणु
			अगर (final_candidate[i] != 0xFF) अणु
				क्रम (j = i * 4; j < (i + 1) * 4 - 2; j++)
					result[3][j] =
						result[final_candidate[i]][j];
				bresult = false;
			पूर्ण
		पूर्ण
		वापस bresult;
	पूर्ण अन्यथा अणु
		अगर (!(simularity_biपंचांगap & 0x03)) अणु /* path A TX OK */
			क्रम (i = 0; i < 2; i++)
				result[3][i] = result[c1][i];
		पूर्ण
		अगर (!(simularity_biपंचांगap & 0x0c)) अणु /* path A RX OK */
			क्रम (i = 2; i < 4; i++)
				result[3][i] = result[c1][i];
		पूर्ण
		अगर (!(simularity_biपंचांगap & 0x30)) अणु /* path B TX OK */
			क्रम (i = 4; i < 6; i++)
				result[3][i] = result[c1][i];
		पूर्ण
		अगर (!(simularity_biपंचांगap & 0xc0)) अणु /* path B RX OK */
			क्रम (i = 6; i < 8; i++)
				result[3][i] = result[c1][i];
		पूर्ण
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम _rtl8723be_phy_iq_calibrate(काष्ठा ieee80211_hw *hw,
					दीर्घ result[][8], u8 t, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 i;
	u8 patha_ok, pathb_ok;
	u32 adda_reg[IQK_ADDA_REG_NUM] = अणु
		0x85c, 0xe6c, 0xe70, 0xe74,
		0xe78, 0xe7c, 0xe80, 0xe84,
		0xe88, 0xe8c, 0xed0, 0xed4,
		0xed8, 0xedc, 0xee0, 0xeec
	पूर्ण;

	u32 iqk_mac_reg[IQK_MAC_REG_NUM] = अणु
		0x522, 0x550, 0x551, 0x040
	पूर्ण;
	u32 iqk_bb_reg[IQK_BB_REG_NUM] = अणु
		ROFDM0_TRXPATHENABLE, ROFDM0_TRMUXPAR,
		RFPGA0_XCD_RFINTERFACESW, 0xb68, 0xb6c,
		0x870, 0x860,
		0x864, 0xa04
	पूर्ण;
	स्थिर u32 retrycount = 2;

	u32 path_sel_bb;/* path_sel_rf */

	u8 पंचांगp_reg_c50, पंचांगp_reg_c58;

	पंचांगp_reg_c50 = rtl_get_bbreg(hw, 0xc50, MASKBYTE0);
	पंचांगp_reg_c58 = rtl_get_bbreg(hw, 0xc58, MASKBYTE0);

	अगर (t == 0) अणु
		rtl8723_save_adda_रेजिस्टरs(hw, adda_reg,
					    rtlphy->adda_backup, 16);
		rtl8723_phy_save_mac_रेजिस्टरs(hw, iqk_mac_reg,
					       rtlphy->iqk_mac_backup);
		rtl8723_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
					    rtlphy->iqk_bb_backup,
					    IQK_BB_REG_NUM);
	पूर्ण
	rtl8723_phy_path_adda_on(hw, adda_reg, true, is2t);
	अगर (t == 0) अणु
		rtlphy->rfpi_enable = (u8)rtl_get_bbreg(hw,
						RFPGA0_XA_HSSIPARAMETER1,
						BIT(8));
	पूर्ण

	path_sel_bb = rtl_get_bbreg(hw, 0x948, MASKDWORD);

	rtl8723_phy_mac_setting_calibration(hw, iqk_mac_reg,
					    rtlphy->iqk_mac_backup);
	/*BB Setting*/
	rtl_set_bbreg(hw, 0xa04, 0x0f000000, 0xf);
	rtl_set_bbreg(hw, 0xc04, MASKDWORD, 0x03a05600);
	rtl_set_bbreg(hw, 0xc08, MASKDWORD, 0x000800e4);
	rtl_set_bbreg(hw, 0x874, MASKDWORD, 0x22204000);

	/* path A TX IQK */
	क्रम (i = 0; i < retrycount; i++) अणु
		patha_ok = _rtl8723be_phy_path_a_iqk(hw);
		अगर (patha_ok == 0x01) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path A Tx IQK Success!!\n");
			result[t][0] = (rtl_get_bbreg(hw, 0xe94, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][1] = (rtl_get_bbreg(hw, 0xe9c, MASKDWORD) &
					0x3FF0000) >> 16;
			अवरोध;
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path A Tx IQK Fail!!\n");
		पूर्ण
	पूर्ण
	/* path A RX IQK */
	क्रम (i = 0; i < retrycount; i++) अणु
		patha_ok = _rtl8723be_phy_path_a_rx_iqk(hw);
		अगर (patha_ok == 0x03) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path A Rx IQK Success!!\n");
			result[t][2] = (rtl_get_bbreg(hw, 0xea4, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][3] = (rtl_get_bbreg(hw, 0xeac, MASKDWORD) &
					0x3FF0000) >> 16;
			अवरोध;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Path A Rx IQK Fail!!\n");
	पूर्ण

	अगर (0x00 == patha_ok)
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Path A IQK Fail!!\n");

	अगर (is2t) अणु
		/* path B TX IQK */
		क्रम (i = 0; i < retrycount; i++) अणु
			pathb_ok = _rtl8723be_phy_path_b_iqk(hw);
			अगर (pathb_ok == 0x01) अणु
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"Path B Tx IQK Success!!\n");
				result[t][4] = (rtl_get_bbreg(hw, 0xe94,
							      MASKDWORD) &
							      0x3FF0000) >> 16;
				result[t][5] = (rtl_get_bbreg(hw, 0xe9c,
							      MASKDWORD) &
							      0x3FF0000) >> 16;
				अवरोध;
			पूर्ण
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path B Tx IQK Fail!!\n");
		पूर्ण
		/* path B RX IQK */
		क्रम (i = 0; i < retrycount; i++) अणु
			pathb_ok = _rtl8723be_phy_path_b_rx_iqk(hw);
			अगर (pathb_ok == 0x03) अणु
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"Path B Rx IQK Success!!\n");
				result[t][6] = (rtl_get_bbreg(hw, 0xea4,
							      MASKDWORD) &
							      0x3FF0000) >> 16;
				result[t][7] = (rtl_get_bbreg(hw, 0xeac,
							      MASKDWORD) &
							      0x3FF0000) >> 16;
				अवरोध;
			पूर्ण
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path B Rx IQK Fail!!\n");
		पूर्ण
	पूर्ण

	/* Back to BB mode, load original value */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0);

	अगर (t != 0) अणु
		rtl8723_phy_reload_adda_रेजिस्टरs(hw, adda_reg,
						  rtlphy->adda_backup, 16);
		rtl8723_phy_reload_mac_रेजिस्टरs(hw, iqk_mac_reg,
						 rtlphy->iqk_mac_backup);
		rtl8723_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
						  rtlphy->iqk_bb_backup,
						  IQK_BB_REG_NUM);

		rtl_set_bbreg(hw, 0x948, MASKDWORD, path_sel_bb);
		/*rtl_set_rfreg(hw, RF90_PATH_B, 0xb0, 0xfffff, path_sel_rf);*/

		rtl_set_bbreg(hw, 0xc50, MASKBYTE0, 0x50);
		rtl_set_bbreg(hw, 0xc50, MASKBYTE0, पंचांगp_reg_c50);
		अगर (is2t) अणु
			rtl_set_bbreg(hw, 0xc58, MASKBYTE0, 0x50);
			rtl_set_bbreg(hw, 0xc58, MASKBYTE0, पंचांगp_reg_c58);
		पूर्ण
		rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x01008c00);
		rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x01008c00);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "8723be IQK Finish!!\n");
पूर्ण

अटल u8 _get_right_chnl_place_क्रम_iqk(u8 chnl)
अणु
	u8 channel_all[TARGET_CHNL_NUM_2G_5G] = अणु
			1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
			13, 14, 36, 38, 40, 42, 44, 46,
			48, 50, 52, 54, 56, 58, 60, 62, 64,
			100, 102, 104, 106, 108, 110,
			112, 114, 116, 118, 120, 122,
			124, 126, 128, 130, 132, 134, 136,
			138, 140, 149, 151, 153, 155, 157,
			159, 161, 163, 165पूर्ण;
	u8 place = chnl;

	अगर (chnl > 14) अणु
		क्रम (place = 14; place < माप(channel_all); place++) अणु
			अगर (channel_all[place] == chnl)
				वापस place - 13;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम _rtl8723be_phy_lc_calibrate(काष्ठा ieee80211_hw *hw, bool is2t)
अणु
	u8 पंचांगpreg;
	u32 rf_a_mode = 0, rf_b_mode = 0;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	पंचांगpreg = rtl_पढ़ो_byte(rtlpriv, 0xd03);

	अगर ((पंचांगpreg & 0x70) != 0)
		rtl_ग_लिखो_byte(rtlpriv, 0xd03, पंचांगpreg & 0x8F);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);

	अगर ((पंचांगpreg & 0x70) != 0) अणु
		rf_a_mode = rtl_get_rfreg(hw, RF90_PATH_A, 0x00, MASK12BITS);

		अगर (is2t)
			rf_b_mode = rtl_get_rfreg(hw, RF90_PATH_B, 0x00,
						  MASK12BITS);

		rtl_set_rfreg(hw, RF90_PATH_A, 0x00, MASK12BITS,
			      (rf_a_mode & 0x8FFFF) | 0x10000);

		अगर (is2t)
			rtl_set_rfreg(hw, RF90_PATH_B, 0x00, MASK12BITS,
				      (rf_b_mode & 0x8FFFF) | 0x10000);
	पूर्ण
	rtl_get_rfreg(hw, RF90_PATH_A, 0x18, MASK12BITS);

	rtl_set_rfreg(hw, RF90_PATH_A, 0xb0, RFREG_OFFSET_MASK, 0xdfbe0);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x18, MASK12BITS, 0x8c0a);

	/* In order not to disturb BT music when wअगरi init.(1ant NIC only) */
	/*mdelay(100);*/
	/* In order not to disturb BT music when wअगरi init.(1ant NIC only) */
	mdelay(50);

	rtl_set_rfreg(hw, RF90_PATH_A, 0xb0, RFREG_OFFSET_MASK, 0xdffe0);

	अगर ((पंचांगpreg & 0x70) != 0) अणु
		rtl_ग_लिखो_byte(rtlpriv, 0xd03, पंचांगpreg);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x00, MASK12BITS, rf_a_mode);

		अगर (is2t)
			rtl_set_rfreg(hw, RF90_PATH_B, 0x00,
				      MASK12BITS, rf_b_mode);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "\n");
पूर्ण

अटल व्योम _rtl8723be_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw,
					     bool bमुख्य, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "\n");

	अगर (bमुख्य) /* left antenna */
		rtl_set_bbreg(hw, 0x92C, MASKDWORD, 0x1);
	अन्यथा
		rtl_set_bbreg(hw, 0x92C, MASKDWORD, 0x2);
पूर्ण

#अघोषित IQK_ADDA_REG_NUM
#अघोषित IQK_DELAY_TIME
/* IQK is merge from Merge Temp */
व्योम rtl8723be_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	दीर्घ result[4][8];
	u8 i, final_candidate, idx;
	bool b_patha_ok, b_pathb_ok;
	दीर्घ reg_e94, reg_e9c, reg_ea4, reg_eb4, reg_ebc, reg_ec4;
	दीर्घ reg_पंचांगp = 0;
	bool is12simular, is13simular, is23simular;
	u32 iqk_bb_reg[9] = अणु
		ROFDM0_XARXIQIMBALANCE,
		ROFDM0_XBRXIQIMBALANCE,
		ROFDM0_ECCATHRESHOLD,
		ROFDM0_AGCRSSITABLE,
		ROFDM0_XATXIQIMBALANCE,
		ROFDM0_XBTXIQIMBALANCE,
		ROFDM0_XCTXAFE,
		ROFDM0_XDTXAFE,
		ROFDM0_RXIQEXTANTA
	पूर्ण;
	u32 path_sel_bb = 0; /* path_sel_rf = 0 */

	अगर (rtlphy->lck_inprogress)
		वापस;

	spin_lock(&rtlpriv->locks.iqk_lock);
	rtlphy->lck_inprogress = true;
	spin_unlock(&rtlpriv->locks.iqk_lock);

	अगर (b_recovery) अणु
		rtl8723_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
						  rtlphy->iqk_bb_backup, 9);
		जाओ label_करोne;
	पूर्ण
	/* Save RF Path */
	path_sel_bb = rtl_get_bbreg(hw, 0x948, MASKDWORD);
	/* path_sel_rf = rtl_get_rfreg(hw, RF90_PATH_A, 0xb0, 0xfffff); */

	क्रम (i = 0; i < 8; i++) अणु
		result[0][i] = 0;
		result[1][i] = 0;
		result[2][i] = 0;
		result[3][i] = 0;
	पूर्ण
	final_candidate = 0xff;
	b_patha_ok = false;
	b_pathb_ok = false;
	is12simular = false;
	is23simular = false;
	is13simular = false;
	क्रम (i = 0; i < 3; i++) अणु
		_rtl8723be_phy_iq_calibrate(hw, result, i, true);
		अगर (i == 1) अणु
			is12simular = _rtl8723be_phy_simularity_compare(hw,
									result,
									0, 1);
			अगर (is12simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == 2) अणु
			is13simular = _rtl8723be_phy_simularity_compare(hw,
									result,
									0, 2);
			अगर (is13simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
			is23simular = _rtl8723be_phy_simularity_compare(hw,
									result,
									1, 2);
			अगर (is23simular) अणु
				final_candidate = 1;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < 8; i++)
					reg_पंचांगp += result[3][i];

				अगर (reg_पंचांगp != 0)
					final_candidate = 3;
				अन्यथा
					final_candidate = 0xFF;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < 4; i++) अणु
		reg_e94 = result[i][0];
		reg_e9c = result[i][1];
		reg_ea4 = result[i][2];
		reg_eb4 = result[i][4];
		reg_ebc = result[i][5];
		reg_ec4 = result[i][6];
	पूर्ण
	अगर (final_candidate != 0xff) अणु
		reg_e94 = result[final_candidate][0];
		rtlphy->reg_e94 = reg_e94;
		reg_e9c = result[final_candidate][1];
		rtlphy->reg_e9c = reg_e9c;
		reg_ea4 = result[final_candidate][2];
		reg_eb4 = result[final_candidate][4];
		rtlphy->reg_eb4 = reg_eb4;
		reg_ebc = result[final_candidate][5];
		rtlphy->reg_ebc = reg_ebc;
		reg_ec4 = result[final_candidate][6];
		b_patha_ok = true;
		b_pathb_ok = true;
	पूर्ण अन्यथा अणु
		rtlphy->reg_e94 = 0x100;
		rtlphy->reg_eb4 = 0x100;
		rtlphy->reg_e9c = 0x0;
		rtlphy->reg_ebc = 0x0;
	पूर्ण
	अगर (reg_e94 != 0)
		rtl8723_phy_path_a_fill_iqk_matrix(hw, b_patha_ok, result,
						   final_candidate,
						   (reg_ea4 == 0));
	अगर (reg_eb4 != 0)
		_rtl8723be_phy_path_b_fill_iqk_matrix(hw, b_pathb_ok, result,
						      final_candidate,
						      (reg_ec4 == 0));

	idx = _get_right_chnl_place_क्रम_iqk(rtlphy->current_channel);

	अगर (final_candidate < 4) अणु
		क्रम (i = 0; i < IQK_MATRIX_REG_NUM; i++)
			rtlphy->iqk_matrix[idx].value[0][i] =
						result[final_candidate][i];
		rtlphy->iqk_matrix[idx].iqk_करोne = true;

	पूर्ण
	rtl8723_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
				    rtlphy->iqk_bb_backup, 9);

	rtl_set_bbreg(hw, 0x948, MASKDWORD, path_sel_bb);
	/* rtl_set_rfreg(hw, RF90_PATH_A, 0xb0, 0xfffff, path_sel_rf); */

label_करोne:
	spin_lock(&rtlpriv->locks.iqk_lock);
	rtlphy->lck_inprogress = false;
	spin_unlock(&rtlpriv->locks.iqk_lock);
पूर्ण

व्योम rtl8723be_phy_lc_calibrate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = &rtlpriv->rtlhal;
	u32 समयout = 2000, समयcount = 0;

	जबतक (rtlpriv->mac80211.act_scanning && समयcount < समयout) अणु
		udelay(50);
		समयcount += 50;
	पूर्ण

	rtlphy->lck_inprogress = true;
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"LCK:Start!!! currentband %x delay %d ms\n",
		 rtlhal->current_bandtype, समयcount);

	_rtl8723be_phy_lc_calibrate(hw, false);

	rtlphy->lck_inprogress = false;
पूर्ण

व्योम rtl8723be_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य)
अणु
	_rtl8723be_phy_set_rfpath_चयन(hw, bमुख्य, true);
पूर्ण

bool rtl8723be_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	bool b_postprocessing = false;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"-->IO Cmd(%#x), set_io_inprogress(%d)\n",
		iotype, rtlphy->set_io_inprogress);
	करो अणु
		चयन (iotype) अणु
		हाल IO_CMD_RESUME_DM_BY_SCAN:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
				"[IO CMD] Resume DM after scan.\n");
			b_postprocessing = true;
			अवरोध;
		हाल IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
				"[IO CMD] Pause DM before scan.\n");
			b_postprocessing = true;
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
				"switch case %#x not processed\n", iotype);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (false);
	अगर (b_postprocessing && !rtlphy->set_io_inprogress) अणु
		rtlphy->set_io_inprogress = true;
		rtlphy->current_io_type = iotype;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
	rtl8723be_phy_set_io(hw);
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE, "IO Type(%#x)\n", iotype);
	वापस true;
पूर्ण

अटल व्योम rtl8723be_phy_set_io(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"--->Cmd(%#x), set_io_inprogress(%d)\n",
		rtlphy->current_io_type, rtlphy->set_io_inprogress);
	चयन (rtlphy->current_io_type) अणु
	हाल IO_CMD_RESUME_DM_BY_SCAN:
		dm_digtable->cur_igvalue = rtlphy->initgain_backup.xaagccore1;
		/*rtl92c_dm_ग_लिखो_dig(hw);*/
		rtl8723be_phy_set_txघातer_level(hw, rtlphy->current_channel);
		rtl_set_bbreg(hw, RCCK0_CCA, 0xff0000, 0x83);
		अवरोध;
	हाल IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		rtlphy->initgain_backup.xaagccore1 = dm_digtable->cur_igvalue;
		dm_digtable->cur_igvalue = 0x17;
		rtl_set_bbreg(hw, RCCK0_CCA, 0xff0000, 0x40);
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n",
			rtlphy->current_io_type);
		अवरोध;
	पूर्ण
	rtlphy->set_io_inprogress = false;
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"(%#x)\n", rtlphy->current_io_type);
पूर्ण

अटल व्योम rtl8723be_phy_set_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
पूर्ण

अटल व्योम _rtl8723be_phy_set_rf_sleep(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x22);
पूर्ण

अटल bool _rtl8723be_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
					      क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool bresult = true;
	u8 i, queue_id;
	काष्ठा rtl8192_tx_ring *ring = शून्य;

	चयन (rfpwr_state) अणु
	हाल ERFON:
		अगर ((ppsc->rfpwr_state == ERFOFF) &&
		     RT_IN_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC)) अणु
			bool rtstatus;
			u32 initializecount = 0;
			करो अणु
				initializecount++;
				rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
					"IPS Set eRf nic enable\n");
				rtstatus = rtl_ps_enable_nic(hw);
			पूर्ण जबतक (!rtstatus && (initializecount < 10));
			RT_CLEAR_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"Set ERFON slept:%d ms\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_sleep_jअगरfies));
			ppsc->last_awake_jअगरfies = jअगरfies;
			rtl8723be_phy_set_rf_on(hw);
		पूर्ण
		अगर (mac->link_state == MAC80211_LINKED)
			rtlpriv->cfg->ops->led_control(hw, LED_CTL_LINK);
		अन्यथा
			rtlpriv->cfg->ops->led_control(hw, LED_CTL_NO_LINK);

		अवरोध;

	हाल ERFOFF:
		क्रम (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) अणु
			ring = &pcipriv->dev.tx_ring[queue_id];
			/* Don't check BEACON Q.
			 * BEACON Q is always not empty,
			 * because '_rtl8723be_cmd_send_packet'
			 */
			अगर (queue_id == BEACON_QUEUE ||
			    skb_queue_len(&ring->queue) == 0) अणु
				queue_id++;
				जारी;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"eRf Off/Sleep: %d times TcbBusyQueue[%d] =%d before doze!\n",
					(i + 1), queue_id,
					skb_queue_len(&ring->queue));

				udelay(10);
				i++;
			पूर्ण
			अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"ERFSLEEP: %d times TcbBusyQueue[%d] = %d !\n",
					MAX_DOZE_WAITING_TIMES_9x,
					queue_id,
					skb_queue_len(&ring->queue));
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC) अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"IPS Set eRf nic disable\n");
			rtl_ps_disable_nic(hw);
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS) अणु
				rtlpriv->cfg->ops->led_control(hw,
							       LED_CTL_NO_LINK);
			पूर्ण अन्यथा अणु
				rtlpriv->cfg->ops->led_control(hw,
							     LED_CTL_POWER_OFF);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ERFSLEEP:
		अगर (ppsc->rfpwr_state == ERFOFF)
			अवरोध;
		क्रम (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) अणु
			ring = &pcipriv->dev.tx_ring[queue_id];
			अगर (skb_queue_len(&ring->queue) == 0) अणु
				queue_id++;
				जारी;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"eRf Off/Sleep: %d times TcbBusyQueue[%d] =%d before doze!\n",
					(i + 1), queue_id,
					skb_queue_len(&ring->queue));

				udelay(10);
				i++;
			पूर्ण
			अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"ERFSLEEP: %d times TcbBusyQueue[%d] = %d !\n",
					MAX_DOZE_WAITING_TIMES_9x,
					queue_id,
					skb_queue_len(&ring->queue));
				अवरोध;
			पूर्ण
		पूर्ण
		rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
			"Set ERFSLEEP awaked:%d ms\n",
			jअगरfies_to_msecs(jअगरfies -
					 ppsc->last_awake_jअगरfies));
		ppsc->last_sleep_jअगरfies = jअगरfies;
		_rtl8723be_phy_set_rf_sleep(hw);
		अवरोध;

	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
			"switch case %#x not processed\n", rfpwr_state);
		bresult = false;
		अवरोध;
	पूर्ण
	अगर (bresult)
		ppsc->rfpwr_state = rfpwr_state;
	वापस bresult;
पूर्ण

bool rtl8723be_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				      क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	bool bresult = false;

	अगर (rfpwr_state == ppsc->rfpwr_state)
		वापस bresult;
	bresult = _rtl8723be_phy_set_rf_घातer_state(hw, rfpwr_state);
	वापस bresult;
पूर्ण
