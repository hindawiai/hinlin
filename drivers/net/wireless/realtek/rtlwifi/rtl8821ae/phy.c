<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../ps.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "table.h"
#समावेश "trx.h"
#समावेश "../btcoexist/halbt_precomp.h"
#समावेश "hw.h"
#समावेश "../efuse.h"

#घोषणा READ_NEXT_PAIR(array_table, v1, v2, i) \
	करो अणु \
		i += 2; \
		v1 = array_table[i]; \
		v2 = array_table[i+1]; \
	पूर्ण जबतक (0)

अटल u32 _rtl8821ae_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
					 क्रमागत radio_path rfpath, u32 offset);
अटल व्योम _rtl8821ae_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
					   क्रमागत radio_path rfpath, u32 offset,
					   u32 data);
अटल u32 _rtl8821ae_phy_calculate_bit_shअगरt(u32 biपंचांगask)
अणु
	u32 i = ffs(biपंचांगask);

	वापस i ? i - 1 : 32;
पूर्ण
अटल bool _rtl8821ae_phy_bb8821a_config_parafile(काष्ठा ieee80211_hw *hw);
/*अटल bool _rtl8812ae_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw);*/
अटल bool _rtl8821ae_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw);
अटल bool _rtl8821ae_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
						     u8 configtype);
अटल bool _rtl8821ae_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
						       u8 configtype);
अटल व्योम phy_init_bb_rf_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw);

अटल दीर्घ _rtl8821ae_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
					    क्रमागत wireless_mode wirelessmode,
					    u8 txpwridx);
अटल व्योम rtl8821ae_phy_set_rf_on(काष्ठा ieee80211_hw *hw);
अटल व्योम rtl8821ae_phy_set_io(काष्ठा ieee80211_hw *hw);

अटल व्योम rtl8812ae_fixspur(काष्ठा ieee80211_hw *hw,
			      क्रमागत ht_channel_width band_width, u8 channel)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	/*C cut Item12 ADC FIFO CLOCK*/
	अगर (IS_VENDOR_8812A_C_CUT(rtlhal->version)) अणु
		अगर (band_width == HT_CHANNEL_WIDTH_20_40 && channel == 11)
			rtl_set_bbreg(hw, RRFMOD, 0xC00, 0x3);
			/* 0x8AC[11:10] = 2'b11*/
		अन्यथा
			rtl_set_bbreg(hw, RRFMOD, 0xC00, 0x2);
			/* 0x8AC[11:10] = 2'b10*/

		/* <20120914, Kordan> A workaround to resolve
		 * 2480Mhz spur by setting ADC घड़ी as 160M. (Asked by Binson)
		 */
		अगर (band_width == HT_CHANNEL_WIDTH_20 &&
		    (channel == 13 || channel == 14)) अणु
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x3);
			/*0x8AC[9:8] = 2'b11*/
			rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 1);
			/* 0x8C4[30] = 1*/
		पूर्ण अन्यथा अगर (band_width == HT_CHANNEL_WIDTH_20_40 &&
			   channel == 11) अणु
			rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 1);
			/*0x8C4[30] = 1*/
		पूर्ण अन्यथा अगर (band_width != HT_CHANNEL_WIDTH_80) अणु
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x2);
			/*0x8AC[9:8] = 2'b10*/
			rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 0);
			/*0x8C4[30] = 0*/
		पूर्ण
	पूर्ण अन्यथा अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
		/* <20120914, Kordan> A workaround to resolve
		 * 2480Mhz spur by setting ADC घड़ी as 160M.
		 */
		अगर (band_width == HT_CHANNEL_WIDTH_20 &&
		    (channel == 13 || channel == 14))
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x3);
			/*0x8AC[9:8] = 11*/
		अन्यथा अगर (channel  <= 14) /*2.4G only*/
			rtl_set_bbreg(hw, RRFMOD, 0x300, 0x2);
			/*0x8AC[9:8] = 10*/
	पूर्ण
पूर्ण

u32 rtl8821ae_phy_query_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr,
			       u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 वापसvalue, originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x)\n",
		regaddr, biपंचांगask);
	originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
	bitshअगरt = _rtl8821ae_phy_calculate_bit_shअगरt(biपंचांगask);
	वापसvalue = (originalvalue & biपंचांगask) >> bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"BBR MASK=0x%x Addr[0x%x]=0x%x\n",
		biपंचांगask, regaddr, originalvalue);
	वापस वापसvalue;
पूर्ण

व्योम rtl8821ae_phy_set_bb_reg(काष्ठा ieee80211_hw *hw,
			      u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);

	अगर (biपंचांगask != MASKDWORD) अणु
		originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
		bitshअगरt = _rtl8821ae_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((originalvalue & (~biपंचांगask)) |
			((data << bitshअगरt) & biपंचांगask));
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, regaddr, data);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);
पूर्ण

u32 rtl8821ae_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			       क्रमागत radio_path rfpath, u32 regaddr,
			       u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, पढ़ोback_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x)\n",
		regaddr, rfpath, biपंचांगask);

	spin_lock(&rtlpriv->locks.rf_lock);

	original_value = _rtl8821ae_phy_rf_serial_पढ़ो(hw, rfpath, regaddr);
	bitshअगरt = _rtl8821ae_phy_calculate_bit_shअगरt(biपंचांगask);
	पढ़ोback_value = (original_value & biपंचांगask) >> bitshअगरt;

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x), original_value(%#x)\n",
		regaddr, rfpath, biपंचांगask, original_value);

	वापस पढ़ोback_value;
पूर्ण

व्योम rtl8821ae_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
			   क्रमागत radio_path rfpath,
			   u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);

	spin_lock(&rtlpriv->locks.rf_lock);

	अगर (biपंचांगask != RFREG_OFFSET_MASK) अणु
		original_value =
		   _rtl8821ae_phy_rf_serial_पढ़ो(hw, rfpath, regaddr);
		bitshअगरt = _rtl8821ae_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((original_value & (~biपंचांगask)) | (data << bitshअगरt));
	पूर्ण

	_rtl8821ae_phy_rf_serial_ग_लिखो(hw, rfpath, regaddr, data);

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		 regaddr, biपंचांगask, data, rfpath);
पूर्ण

अटल u32 _rtl8821ae_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
					 क्रमागत radio_path rfpath, u32 offset)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	bool is_pi_mode = false;
	u32 retvalue = 0;

	/* 2009/06/17 MH We can not execute IO क्रम घातer
	save or other accident mode.*/
	अगर (RT_CANNOT_IO(hw)) अणु
		pr_err("return all one\n");
		वापस 0xFFFFFFFF;
	पूर्ण
	/* <20120809, Kordan> CCA OFF(when entering),
		asked by James to aव्योम पढ़ोing the wrong value.
	    <20120828, Kordan> Toggling CCA would affect RF 0x0, skip it!*/
	अगर (offset != 0x0 &&
	    !((rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) ||
	    (IS_VENDOR_8812A_C_CUT(rtlhal->version))))
		rtl_set_bbreg(hw, RCCAONSEC, 0x8, 1);
	offset &= 0xff;

	अगर (rfpath == RF90_PATH_A)
		is_pi_mode = (bool)rtl_get_bbreg(hw, 0xC00, 0x4);
	अन्यथा अगर (rfpath == RF90_PATH_B)
		is_pi_mode = (bool)rtl_get_bbreg(hw, 0xE00, 0x4);

	rtl_set_bbreg(hw, RHSSIREAD_8821AE, 0xff, offset);

	अगर ((rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) ||
	    (IS_VENDOR_8812A_C_CUT(rtlhal->version)))
		udelay(20);

	अगर (is_pi_mode) अणु
		अगर (rfpath == RF90_PATH_A)
			retvalue =
			  rtl_get_bbreg(hw, RA_PIREAD_8821A, BLSSIREADBACKDATA);
		अन्यथा अगर (rfpath == RF90_PATH_B)
			retvalue =
			  rtl_get_bbreg(hw, RB_PIREAD_8821A, BLSSIREADBACKDATA);
	पूर्ण अन्यथा अणु
		अगर (rfpath == RF90_PATH_A)
			retvalue =
			  rtl_get_bbreg(hw, RA_SIREAD_8821A, BLSSIREADBACKDATA);
		अन्यथा अगर (rfpath == RF90_PATH_B)
			retvalue =
			  rtl_get_bbreg(hw, RB_SIREAD_8821A, BLSSIREADBACKDATA);
	पूर्ण

	/*<20120809, Kordan> CCA ON(when निकासing),
	 * asked by James to aव्योम पढ़ोing the wrong value.
	 *   <20120828, Kordan> Toggling CCA would affect RF 0x0, skip it!
	 */
	अगर (offset != 0x0 &&
	    !((rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) ||
	    (IS_VENDOR_8812A_C_CUT(rtlhal->version))))
		rtl_set_bbreg(hw, RCCAONSEC, 0x8, 0);
	वापस retvalue;
पूर्ण

अटल व्योम _rtl8821ae_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
					   क्रमागत radio_path rfpath, u32 offset,
					   u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];
	u32 data_and_addr;
	u32 newoffset;

	अगर (RT_CANNOT_IO(hw)) अणु
		pr_err("stop\n");
		वापस;
	पूर्ण
	offset &= 0xff;
	newoffset = offset;
	data_and_addr = ((newoffset << 20) |
			 (data & 0x000fffff)) & 0x0fffffff;
	rtl_set_bbreg(hw, pphyreg->rf3wire_offset, MASKDWORD, data_and_addr);
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"RFW-%d Addr[0x%x]=0x%x\n",
		rfpath, pphyreg->rf3wire_offset, data_and_addr);
पूर्ण

bool rtl8821ae_phy_mac_config(काष्ठा ieee80211_hw *hw)
अणु
	bool rtstatus = 0;

	rtstatus = _rtl8821ae_phy_config_mac_with_headerfile(hw);

	वापस rtstatus;
पूर्ण

bool rtl8821ae_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	bool rtstatus = true;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 regval;
	u8 crystal_cap;

	phy_init_bb_rf_रेजिस्टर_definition(hw);

	regval = rtl_पढ़ो_byte(rtlpriv, REG_SYS_FUNC_EN);
	regval |= FEN_PCIEA;
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, regval);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN,
		       regval | FEN_BB_GLB_RSTN | FEN_BBRSTB);

	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, 0x7);
	rtl_ग_लिखो_byte(rtlpriv, REG_OPT_CTRL + 2, 0x7);

	rtstatus = _rtl8821ae_phy_bb8821a_config_parafile(hw);

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
		crystal_cap = rtlefuse->crystalcap & 0x3F;
		rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0x7FF80000,
			      (crystal_cap | (crystal_cap << 6)));
	पूर्ण अन्यथा अणु
		crystal_cap = rtlefuse->crystalcap & 0x3F;
		rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
			      (crystal_cap | (crystal_cap << 6)));
	पूर्ण
	rtlphy->reg_837 = rtl_पढ़ो_byte(rtlpriv, 0x837);

	वापस rtstatus;
पूर्ण

bool rtl8821ae_phy_rf_config(काष्ठा ieee80211_hw *hw)
अणु
	वापस rtl8821ae_phy_rf6052_config(hw);
पूर्ण

अटल व्योम _rtl8812ae_phy_set_rfe_reg_24g(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp;

	चयन (rtlhal->rfe_type) अणु
	हाल 3:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x54337770);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x54337770);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, 0x900, 0x00000303, 0x1);
		अवरोध;
	हाल 4:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x77777777);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77777777);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x001);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x001);
		अवरोध;
	हाल 5:
		rtl_ग_लिखो_byte(rtlpriv, RA_RFE_PINMUX + 2, 0x77);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77777777);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, RA_RFE_INV + 3);
		rtl_ग_लिखो_byte(rtlpriv, RA_RFE_INV + 3, पंचांगp & ~0x1);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x000);
		अवरोध;
	हाल 1:
		अगर (rtlpriv->btcoexist.bt_coexistence) अणु
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xffffff, 0x777777);
			rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD,
				      0x77777777);
			rtl_set_bbreg(hw, RA_RFE_INV, 0x33f00000, 0x000);
			rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x000);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 0:
	हाल 2:
	शेष:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x77777777);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77777777);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x000);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x000);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl8812ae_phy_set_rfe_reg_5g(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp;

	चयन (rtlhal->rfe_type) अणु
	हाल 0:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x77337717);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77337717);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		अवरोध;
	हाल 1:
		अगर (rtlpriv->btcoexist.bt_coexistence) अणु
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xffffff, 0x337717);
			rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD,
				      0x77337717);
			rtl_set_bbreg(hw, RA_RFE_INV, 0x33f00000, 0x000);
			rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x000);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD,
				      0x77337717);
			rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD,
				      0x77337717);
			rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x000);
			rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x000);
		पूर्ण
		अवरोध;
	हाल 3:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x54337717);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x54337717);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, 0x900, 0x00000303, 0x1);
		अवरोध;
	हाल 5:
		rtl_ग_लिखो_byte(rtlpriv, RA_RFE_PINMUX + 2, 0x33);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77337777);
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, RA_RFE_INV + 3);
		rtl_ग_लिखो_byte(rtlpriv, RA_RFE_INV + 3, पंचांगp | 0x1);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		अवरोध;
	हाल 2:
	हाल 4:
	शेष:
		rtl_set_bbreg(hw, RA_RFE_PINMUX, BMASKDWORD, 0x77337777);
		rtl_set_bbreg(hw, RB_RFE_PINMUX, BMASKDWORD, 0x77337777);
		rtl_set_bbreg(hw, RA_RFE_INV, BMASKRFEINV, 0x010);
		rtl_set_bbreg(hw, RB_RFE_INV, BMASKRFEINV, 0x010);
		अवरोध;
	पूर्ण
पूर्ण

u32 phy_get_tx_swing_8812A(काष्ठा ieee80211_hw *hw, u8	band,
			   u8 rf_path)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_dm *rtldm = rtl_dm(rtlpriv);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	s8 reg_swing_2g = -1;/* 0xff; */
	s8 reg_swing_5g = -1;/* 0xff; */
	s8 swing_2g = -1 * reg_swing_2g;
	s8 swing_5g = -1 * reg_swing_5g;
	u32  out = 0x200;
	स्थिर s8 स्वतः_temp = -1;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
		"===> PHY_GetTXBBSwing_8812A, bbSwing_2G: %d, bbSwing_5G: %d,autoload_failflag=%d.\n",
		(पूर्णांक)swing_2g, (पूर्णांक)swing_5g,
		(पूर्णांक)rtlefuse->स्वतःload_failflag);

	अगर (rtlefuse->स्वतःload_failflag) अणु
		अगर (band == BAND_ON_2_4G) अणु
			rtldm->swing_dअगरf_2g = swing_2g;
			अगर (swing_2g == 0) अणु
				out = 0x200; /* 0 dB */
			पूर्ण अन्यथा अगर (swing_2g == -3) अणु
				out = 0x16A; /* -3 dB */
			पूर्ण अन्यथा अगर (swing_2g == -6) अणु
				out = 0x101; /* -6 dB */
			पूर्ण अन्यथा अगर (swing_2g == -9) अणु
				out = 0x0B6; /* -9 dB */
			पूर्ण अन्यथा अणु
				rtldm->swing_dअगरf_2g = 0;
				out = 0x200;
			पूर्ण
		पूर्ण अन्यथा अगर (band == BAND_ON_5G) अणु
			rtldm->swing_dअगरf_5g = swing_5g;
			अगर (swing_5g == 0) अणु
				out = 0x200; /* 0 dB */
			पूर्ण अन्यथा अगर (swing_5g == -3) अणु
				out = 0x16A; /* -3 dB */
			पूर्ण अन्यथा अगर (swing_5g == -6) अणु
				out = 0x101; /* -6 dB */
			पूर्ण अन्यथा अगर (swing_5g == -9) अणु
				out = 0x0B6; /* -9 dB */
			पूर्ण अन्यथा अणु
				अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
					rtldm->swing_dअगरf_5g = -3;
					out = 0x16A;
				पूर्ण अन्यथा अणु
					rtldm->swing_dअगरf_5g = 0;
					out = 0x200;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			rtldm->swing_dअगरf_2g = -3;
			rtldm->swing_dअगरf_5g = -3;
			out = 0x16A; /* -3 dB */
		पूर्ण
	पूर्ण अन्यथा अणु
		u32 swing = 0, swing_a = 0, swing_b = 0;

		अगर (band == BAND_ON_2_4G) अणु
			अगर (reg_swing_2g == स्वतः_temp) अणु
				efuse_shaकरोw_पढ़ो(hw, 1, 0xC6, (u32 *)&swing);
				swing = (swing == 0xFF) ? 0x00 : swing;
			पूर्ण अन्यथा अगर (swing_2g ==  0) अणु
				swing = 0x00; /* 0 dB */
			पूर्ण अन्यथा अगर (swing_2g == -3) अणु
				swing = 0x05; /* -3 dB */
			पूर्ण अन्यथा अगर (swing_2g == -6) अणु
				swing = 0x0A; /* -6 dB */
			पूर्ण अन्यथा अगर (swing_2g == -9) अणु
				swing = 0xFF; /* -9 dB */
			पूर्ण अन्यथा अणु
				swing = 0x00;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (reg_swing_5g == स्वतः_temp) अणु
				efuse_shaकरोw_पढ़ो(hw, 1, 0xC7, (u32 *)&swing);
				swing = (swing == 0xFF) ? 0x00 : swing;
			पूर्ण अन्यथा अगर (swing_5g ==  0) अणु
				swing = 0x00; /* 0 dB */
			पूर्ण अन्यथा अगर (swing_5g == -3) अणु
				swing = 0x05; /* -3 dB */
			पूर्ण अन्यथा अगर (swing_5g == -6) अणु
				swing = 0x0A; /* -6 dB */
			पूर्ण अन्यथा अगर (swing_5g == -9) अणु
				swing = 0xFF; /* -9 dB */
			पूर्ण अन्यथा अणु
				swing = 0x00;
			पूर्ण
		पूर्ण

		swing_a = (swing & 0x3) >> 0; /* 0xC6/C7[1:0] */
		swing_b = (swing & 0xC) >> 2; /* 0xC6/C7[3:2] */
		rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
			"===> PHY_GetTXBBSwing_8812A, swingA: 0x%X, swingB: 0x%X\n",
			swing_a, swing_b);

		/* 3 Path-A */
		अगर (swing_a == 0x0) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = 0;
			अन्यथा
				rtldm->swing_dअगरf_5g = 0;
			out = 0x200; /* 0 dB */
		पूर्ण अन्यथा अगर (swing_a == 0x1) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = -3;
			अन्यथा
				rtldm->swing_dअगरf_5g = -3;
			out = 0x16A; /* -3 dB */
		पूर्ण अन्यथा अगर (swing_a == 0x2) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = -6;
			अन्यथा
				rtldm->swing_dअगरf_5g = -6;
			out = 0x101; /* -6 dB */
		पूर्ण अन्यथा अगर (swing_a == 0x3) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = -9;
			अन्यथा
				rtldm->swing_dअगरf_5g = -9;
			out = 0x0B6; /* -9 dB */
		पूर्ण
		/* 3 Path-B */
		अगर (swing_b == 0x0) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = 0;
			अन्यथा
				rtldm->swing_dअगरf_5g = 0;
			out = 0x200; /* 0 dB */
		पूर्ण अन्यथा अगर (swing_b == 0x1) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = -3;
			अन्यथा
				rtldm->swing_dअगरf_5g = -3;
			out = 0x16A; /* -3 dB */
		पूर्ण अन्यथा अगर (swing_b == 0x2) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = -6;
			अन्यथा
				rtldm->swing_dअगरf_5g = -6;
			out = 0x101; /* -6 dB */
		पूर्ण अन्यथा अगर (swing_b == 0x3) अणु
			अगर (band == BAND_ON_2_4G)
				rtldm->swing_dअगरf_2g = -9;
			अन्यथा
				rtldm->swing_dअगरf_5g = -9;
			out = 0x0B6; /* -9 dB */
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
		"<=== PHY_GetTXBBSwing_8812A, out = 0x%X\n", out);
	वापस out;
पूर्ण

व्योम rtl8821ae_phy_चयन_wirelessband(काष्ठा ieee80211_hw *hw, u8 band)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_dm *rtldm = rtl_dm(rtlpriv);
	u8 current_band = rtlhal->current_bandtype;
	s8 bb_dअगरf_between_band;

	rtl8821ae_phy_query_bb_reg(hw, RTXPATH, 0xf0);
	rtl8821ae_phy_query_bb_reg(hw, RCCK_RX, 0x0f000000);
	rtlhal->current_bandtype = (क्रमागत band_type) band;
	/* reconfig BB/RF according to wireless mode */
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		/* BB & RF Config */
		rtl_set_bbreg(hw, ROFDMCCKEN, BOFDMEN|BCCKEN, 0x03);

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
			/* 0xCB0[15:12] = 0x7 (LNA_On)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF000, 0x7);
			/* 0xCB0[7:4] = 0x7 (PAPE_A)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF0, 0x7);
		पूर्ण

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			/*0x834[1:0] = 0x1*/
			rtl_set_bbreg(hw, 0x834, 0x3, 0x1);
		पूर्ण

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
			/* 0xC1C[11:8] = 0 */
			rtl_set_bbreg(hw, RA_TXSCALE, 0xF00, 0);
		पूर्ण अन्यथा अणु
			/* 0x82C[1:0] = 2b'00 */
			rtl_set_bbreg(hw, 0x82c, 0x3, 0);
		पूर्ण

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			_rtl8812ae_phy_set_rfe_reg_24g(hw);

		rtl_set_bbreg(hw, RTXPATH, 0xf0, 0x1);
		rtl_set_bbreg(hw, RCCK_RX, 0x0f000000, 0x1);

		rtl_ग_लिखो_byte(rtlpriv, REG_CCK_CHECK, 0x0);
	पूर्ण अन्यथा अणु/* 5G band */
		u16 count, reg_41a;

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
			/*0xCB0[15:12] = 0x5 (LNA_On)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF000, 0x5);
			/*0xCB0[7:4] = 0x4 (PAPE_A)*/
			rtl_set_bbreg(hw, RA_RFE_PINMUX, 0xF0, 0x4);
		पूर्ण
		/*CCK_CHECK_en*/
		rtl_ग_लिखो_byte(rtlpriv, REG_CCK_CHECK, 0x80);

		count = 0;
		reg_41a = rtl_पढ़ो_word(rtlpriv, REG_TXPKT_EMPTY);
		rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
			"Reg41A value %d\n", reg_41a);
		reg_41a &= 0x30;
		जबतक ((reg_41a != 0x30) && (count < 50)) अणु
			udelay(50);
			rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD, "Delay 50us\n");

			reg_41a = rtl_पढ़ो_word(rtlpriv, REG_TXPKT_EMPTY);
			reg_41a &= 0x30;
			count++;
			rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
				"Reg41A value %d\n", reg_41a);
		पूर्ण
		अगर (count != 0)
			rtl_dbg(rtlpriv, COMP_MLME, DBG_LOUD,
				"PHY_SwitchWirelessBand8812(): Switch to 5G Band. Count = %d reg41A=0x%x\n",
				count, reg_41a);

		/* 2012/02/01, Sinda add registry to चयन workaround
		without दीर्घ-run verअगरication क्रम scan issue. */
		rtl_set_bbreg(hw, ROFDMCCKEN, BOFDMEN|BCCKEN, 0x03);

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			/*0x834[1:0] = 0x2*/
			rtl_set_bbreg(hw, 0x834, 0x3, 0x2);
		पूर्ण

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
			/* AGC table select */
			/* 0xC1C[11:8] = 1*/
			rtl_set_bbreg(hw, RA_TXSCALE, 0xF00, 1);
		पूर्ण अन्यथा
			/* 0x82C[1:0] = 2'b00 */
			rtl_set_bbreg(hw, 0x82c, 0x3, 1);

		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
			_rtl8812ae_phy_set_rfe_reg_5g(hw);

		rtl_set_bbreg(hw, RTXPATH, 0xf0, 0);
		rtl_set_bbreg(hw, RCCK_RX, 0x0f000000, 0xf);

		rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
			"==>PHY_SwitchWirelessBand8812() BAND_ON_5G settings OFDM index 0x%x\n",
			rtlpriv->dm.ofdm_index[RF90_PATH_A]);
	पूर्ण

	अगर ((rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) ||
	    (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)) अणु
		/* 0xC1C[31:21] */
		rtl_set_bbreg(hw, RA_TXSCALE, 0xFFE00000,
			      phy_get_tx_swing_8812A(hw, band, RF90_PATH_A));
		/* 0xE1C[31:21] */
		rtl_set_bbreg(hw, RB_TXSCALE, 0xFFE00000,
			      phy_get_tx_swing_8812A(hw, band, RF90_PATH_B));

		/* <20121005, Kordan> When TxPowerTrack is ON,
		 *	we should take care of the change of BB swing.
		 *   That is, reset all info to trigger Tx घातer tracking.
		 */
		अगर (band != current_band) अणु
			bb_dअगरf_between_band =
				(rtldm->swing_dअगरf_2g - rtldm->swing_dअगरf_5g);
			bb_dअगरf_between_band = (band == BAND_ON_2_4G) ?
						bb_dअगरf_between_band :
						(-1 * bb_dअगरf_between_band);
			rtldm->शेष_ofdm_index += bb_dअगरf_between_band * 2;
		पूर्ण
		rtl8821ae_dm_clear_txघातer_tracking_state(hw);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"<==%s():Switch Band OK.\n", __func__);
	वापस;
पूर्ण

अटल bool _rtl8821ae_check_positive(काष्ठा ieee80211_hw *hw,
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
		"	(Platform, Interface) = (0x%X, 0x%X)\n", 0x04, पूर्णांकf);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"	(Board, Package) = (0x%X, 0x%X)\n",
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
	पूर्ण अन्यथा
		वापस false;
पूर्ण

अटल bool _rtl8821ae_check_condition(काष्ठा ieee80211_hw *hw,
				       स्थिर u32 condition)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 _board = rtlefuse->board_type; /*need efuse define*/
	u32 _पूर्णांकerface = 0x01; /* ODM_ITRF_PCIE */
	u32 _platक्रमm = 0x08;/* ODM_WIN */
	u32 cond = condition;

	अगर (condition == 0xCDCDCDCD)
		वापस true;

	cond = condition & 0xFF;
	अगर ((_board != cond) && cond != 0xFF)
		वापस false;

	cond = condition & 0xFF00;
	cond = cond >> 8;
	अगर ((_पूर्णांकerface & cond) == 0 && cond != 0x07)
		वापस false;

	cond = condition & 0xFF0000;
	cond = cond >> 16;
	अगर ((_platक्रमm & cond) == 0 && cond != 0x0F)
		वापस false;
	वापस true;
पूर्ण

अटल व्योम _rtl8821ae_config_rf_reg(काष्ठा ieee80211_hw *hw,
				     u32 addr, u32 data,
				     क्रमागत radio_path rfpath, u32 regaddr)
अणु
	अगर (addr == 0xfe || addr == 0xffe) अणु
		/* In order not to disturb BT music when
		 * wअगरi init.(1ant NIC only)
		 */
		mdelay(50);
	पूर्ण अन्यथा अणु
		rtl_set_rfreg(hw, rfpath, regaddr, RFREG_OFFSET_MASK, data);
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_config_rf_radio_a(काष्ठा ieee80211_hw *hw,
					 u32 addr, u32 data)
अणु
	u32 content = 0x1000; /*RF Content: radio_a_txt*/
	u32 maskक्रमphyset = (u32)(content & 0xE000);

	_rtl8821ae_config_rf_reg(hw, addr, data,
				 RF90_PATH_A, addr | maskक्रमphyset);
पूर्ण

अटल व्योम _rtl8821ae_config_rf_radio_b(काष्ठा ieee80211_hw *hw,
					 u32 addr, u32 data)
अणु
	u32 content = 0x1001; /*RF Content: radio_b_txt*/
	u32 maskक्रमphyset = (u32)(content & 0xE000);

	_rtl8821ae_config_rf_reg(hw, addr, data,
				 RF90_PATH_B, addr | maskक्रमphyset);
पूर्ण

अटल व्योम _rtl8821ae_config_bb_reg(काष्ठा ieee80211_hw *hw,
				     u32 addr, u32 data)
अणु
	अगर (addr == 0xfe)
		mdelay(50);
	अन्यथा अगर (addr == 0xfd)
		mdelay(5);
	अन्यथा अगर (addr == 0xfc)
		mdelay(1);
	अन्यथा अगर (addr == 0xfb)
		udelay(50);
	अन्यथा अगर (addr == 0xfa)
		udelay(5);
	अन्यथा अगर (addr == 0xf9)
		udelay(1);
	अन्यथा
		rtl_set_bbreg(hw, addr, MASKDWORD, data);

	udelay(1);
पूर्ण

अटल व्योम _rtl8821ae_phy_init_tx_घातer_by_rate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 band, rfpath, txnum, rate_section;

	क्रम (band = BAND_ON_2_4G; band <= BAND_ON_5G; ++band)
		क्रम (rfpath = 0; rfpath < TX_PWR_BY_RATE_NUM_RF; ++rfpath)
			क्रम (txnum = 0; txnum < TX_PWR_BY_RATE_NUM_RF; ++txnum)
				क्रम (rate_section = 0;
				     rate_section < TX_PWR_BY_RATE_NUM_SECTION;
				     ++rate_section)
					rtlphy->tx_घातer_by_rate_offset[band]
					    [rfpath][txnum][rate_section] = 0;
पूर्ण

अटल व्योम _rtl8821ae_phy_set_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw,
					  u8 band, u8 path,
					  u8 rate_section,
					  u8 txnum, u8 value)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	अगर (path > RF90_PATH_D) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Rf Path %d in phy_SetTxPowerByRatBase()\n", path);
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
		हाल VHT_1SSMCS0_1SSMCS9:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][4] = value;
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			rtlphy->txpwr_by_rate_base_24g[path][txnum][5] = value;
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Invalid RateSection %d in Band 2.4G,Rf Path %d, %dTx in PHY_SetTxPowerByRateBase()\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (band == BAND_ON_5G) अणु
		चयन (rate_section) अणु
		हाल OFDM:
			rtlphy->txpwr_by_rate_base_5g[path][txnum][0] = value;
			अवरोध;
		हाल HT_MCS0_MCS7:
			rtlphy->txpwr_by_rate_base_5g[path][txnum][1] = value;
			अवरोध;
		हाल HT_MCS8_MCS15:
			rtlphy->txpwr_by_rate_base_5g[path][txnum][2] = value;
			अवरोध;
		हाल VHT_1SSMCS0_1SSMCS9:
			rtlphy->txpwr_by_rate_base_5g[path][txnum][3] = value;
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			rtlphy->txpwr_by_rate_base_5g[path][txnum][4] = value;
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Invalid RateSection %d in Band 5G, Rf Path %d, %dTx in PHY_SetTxPowerByRateBase()\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Band %d in PHY_SetTxPowerByRateBase()\n", band);
	पूर्ण
पूर्ण

अटल u8 _rtl8821ae_phy_get_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw,
						  u8 band, u8 path,
						  u8 txnum, u8 rate_section)
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
		हाल VHT_1SSMCS0_1SSMCS9:
			value = rtlphy->txpwr_by_rate_base_24g[path][txnum][4];
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			value = rtlphy->txpwr_by_rate_base_24g[path][txnum][5];
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Invalid RateSection %d in Band 2.4G, Rf Path %d, %dTx in PHY_GetTxPowerByRateBase()\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (band == BAND_ON_5G) अणु
		चयन (rate_section) अणु
		हाल OFDM:
			value = rtlphy->txpwr_by_rate_base_5g[path][txnum][0];
			अवरोध;
		हाल HT_MCS0_MCS7:
			value = rtlphy->txpwr_by_rate_base_5g[path][txnum][1];
			अवरोध;
		हाल HT_MCS8_MCS15:
			value = rtlphy->txpwr_by_rate_base_5g[path][txnum][2];
			अवरोध;
		हाल VHT_1SSMCS0_1SSMCS9:
			value = rtlphy->txpwr_by_rate_base_5g[path][txnum][3];
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			value = rtlphy->txpwr_by_rate_base_5g[path][txnum][4];
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Invalid RateSection %d in Band 5G, Rf Path %d, %dTx in PHY_GetTxPowerByRateBase()\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Band %d in PHY_GetTxPowerByRateBase()\n", band);
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम _rtl8821ae_phy_store_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u16 rawvalue = 0;
	u8 base = 0, path = 0;

	क्रम (path = RF90_PATH_A; path <= RF90_PATH_B; ++path) अणु
		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][path][RF_1TX][0] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path, CCK, RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][path][RF_1TX][2] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path, OFDM, RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][path][RF_1TX][4] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path, HT_MCS0_MCS7, RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][path][RF_2TX][6] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path, HT_MCS8_MCS15, RF_2TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][path][RF_1TX][8] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path, VHT_1SSMCS0_1SSMCS9, RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][path][RF_2TX][11] >> 8) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path, VHT_2SSMCS0_2SSMCS9, RF_2TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][path][RF_1TX][2] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_5G, path, OFDM, RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][path][RF_1TX][4] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_5G, path, HT_MCS0_MCS7, RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][path][RF_2TX][6] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_5G, path, HT_MCS8_MCS15, RF_2TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][path][RF_1TX][8] >> 24) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_5G, path, VHT_1SSMCS0_1SSMCS9, RF_1TX, base);

		rawvalue = (u16)(rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][path][RF_2TX][11] >> 8) & 0xFF;
		base = (rawvalue >> 4) * 10 + (rawvalue & 0xF);
		_rtl8821ae_phy_set_txघातer_by_rate_base(hw, BAND_ON_5G, path, VHT_2SSMCS0_2SSMCS9, RF_2TX, base);
	पूर्ण
पूर्ण

अटल व्योम _phy_convert_txघातer_dbm_to_relative_value(u32 *data, u8 start,
						u8 end, u8 base_val)
अणु
	पूर्णांक i;
	u8 temp_value = 0;
	u32 temp_data = 0;

	क्रम (i = 3; i >= 0; --i) अणु
		अगर (i >= start && i <= end) अणु
			/* Get the exact value */
			temp_value = (u8)(*data >> (i * 8)) & 0xF;
			temp_value += ((u8)((*data >> (i * 8 + 4)) & 0xF)) * 10;

			/* Change the value to a relative value */
			temp_value = (temp_value > base_val) ? temp_value -
					base_val : base_val - temp_value;
		पूर्ण अन्यथा अणु
			temp_value = (u8)(*data >> (i * 8)) & 0xFF;
		पूर्ण
		temp_data <<= 8;
		temp_data |= temp_value;
	पूर्ण
	*data = temp_data;
पूर्ण

अटल व्योम _rtl8812ae_phy_cross_reference_ht_and_vht_txघातer_limit(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 regulation, bw, channel, rate_section;
	s8 temp_pwrlmt = 0;

	क्रम (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) अणु
		क्रम (bw = 0; bw < MAX_5G_BANDWIDTH_NUM; ++bw) अणु
			क्रम (channel = 0; channel < CHANNEL_MAX_NUMBER_5G; ++channel) अणु
				क्रम (rate_section = 0; rate_section < MAX_RATE_SECTION_NUM; ++rate_section) अणु
					temp_pwrlmt = rtlphy->txpwr_limit_5g[regulation]
						[bw][rate_section][channel][RF90_PATH_A];
					अगर (temp_pwrlmt == MAX_POWER_INDEX) अणु
						अगर (bw == 0 || bw == 1) अणु /*5G 20M 40M VHT and HT can cross reference*/
							rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
								"No power limit table of the specified band %d, bandwidth %d, ratesection %d, channel %d, rf path %d\n",
								1, bw, rate_section, channel, RF90_PATH_A);
							अगर (rate_section == 2) अणु
								rtlphy->txpwr_limit_5g[regulation][bw][2][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][4][channel][RF90_PATH_A];
							पूर्ण अन्यथा अगर (rate_section == 4) अणु
								rtlphy->txpwr_limit_5g[regulation][bw][4][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][2][channel][RF90_PATH_A];
							पूर्ण अन्यथा अगर (rate_section == 3) अणु
								rtlphy->txpwr_limit_5g[regulation][bw][3][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][5][channel][RF90_PATH_A];
							पूर्ण अन्यथा अगर (rate_section == 5) अणु
								rtlphy->txpwr_limit_5g[regulation][bw][5][channel][RF90_PATH_A] =
									rtlphy->txpwr_limit_5g[regulation][bw][3][channel][RF90_PATH_A];
							पूर्ण

							rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
								"use other value %d\n",
								temp_pwrlmt);
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल u8 _rtl8812ae_phy_get_txघातer_by_rate_base_index(काष्ठा ieee80211_hw *hw,
						   क्रमागत band_type band, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 index = 0;
	अगर (band == BAND_ON_2_4G) अणु
		चयन (rate) अणु
		हाल MGN_1M:
		हाल MGN_2M:
		हाल MGN_5_5M:
		हाल MGN_11M:
			index = 0;
			अवरोध;

		हाल MGN_6M:
		हाल MGN_9M:
		हाल MGN_12M:
		हाल MGN_18M:
		हाल MGN_24M:
		हाल MGN_36M:
		हाल MGN_48M:
		हाल MGN_54M:
			index = 1;
			अवरोध;

		हाल MGN_MCS0:
		हाल MGN_MCS1:
		हाल MGN_MCS2:
		हाल MGN_MCS3:
		हाल MGN_MCS4:
		हाल MGN_MCS5:
		हाल MGN_MCS6:
		हाल MGN_MCS7:
			index = 2;
			अवरोध;

		हाल MGN_MCS8:
		हाल MGN_MCS9:
		हाल MGN_MCS10:
		हाल MGN_MCS11:
		हाल MGN_MCS12:
		हाल MGN_MCS13:
		हाल MGN_MCS14:
		हाल MGN_MCS15:
			index = 3;
			अवरोध;

		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Wrong rate 0x%x to obtain index in 2.4G in PHY_GetTxPowerByRateBaseIndex()\n",
				rate);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (band == BAND_ON_5G) अणु
		चयन (rate) अणु
		हाल MGN_6M:
		हाल MGN_9M:
		हाल MGN_12M:
		हाल MGN_18M:
		हाल MGN_24M:
		हाल MGN_36M:
		हाल MGN_48M:
		हाल MGN_54M:
			index = 0;
			अवरोध;

		हाल MGN_MCS0:
		हाल MGN_MCS1:
		हाल MGN_MCS2:
		हाल MGN_MCS3:
		हाल MGN_MCS4:
		हाल MGN_MCS5:
		हाल MGN_MCS6:
		हाल MGN_MCS7:
			index = 1;
			अवरोध;

		हाल MGN_MCS8:
		हाल MGN_MCS9:
		हाल MGN_MCS10:
		हाल MGN_MCS11:
		हाल MGN_MCS12:
		हाल MGN_MCS13:
		हाल MGN_MCS14:
		हाल MGN_MCS15:
			index = 2;
			अवरोध;

		हाल MGN_VHT1SS_MCS0:
		हाल MGN_VHT1SS_MCS1:
		हाल MGN_VHT1SS_MCS2:
		हाल MGN_VHT1SS_MCS3:
		हाल MGN_VHT1SS_MCS4:
		हाल MGN_VHT1SS_MCS5:
		हाल MGN_VHT1SS_MCS6:
		हाल MGN_VHT1SS_MCS7:
		हाल MGN_VHT1SS_MCS8:
		हाल MGN_VHT1SS_MCS9:
			index = 3;
			अवरोध;

		हाल MGN_VHT2SS_MCS0:
		हाल MGN_VHT2SS_MCS1:
		हाल MGN_VHT2SS_MCS2:
		हाल MGN_VHT2SS_MCS3:
		हाल MGN_VHT2SS_MCS4:
		हाल MGN_VHT2SS_MCS5:
		हाल MGN_VHT2SS_MCS6:
		हाल MGN_VHT2SS_MCS7:
		हाल MGN_VHT2SS_MCS8:
		हाल MGN_VHT2SS_MCS9:
			index = 4;
			अवरोध;

		शेष:
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Wrong rate 0x%x to obtain index in 5G in PHY_GetTxPowerByRateBaseIndex()\n",
				rate);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस index;
पूर्ण

अटल व्योम _rtl8812ae_phy_convert_txघातer_limit_to_घातer_index(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 bw40_pwr_base_dbm2_4G, bw40_pwr_base_dbm5G;
	u8 regulation, bw, channel, rate_section;
	u8 base_index2_4G = 0;
	u8 base_index5G = 0;
	s8 temp_value = 0, temp_pwrlmt = 0;
	u8 rf_path = 0;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"=====> _rtl8812ae_phy_convert_txpower_limit_to_power_index()\n");

	_rtl8812ae_phy_cross_reference_ht_and_vht_txघातer_limit(hw);

	क्रम (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) अणु
		क्रम (bw = 0; bw < MAX_2_4G_BANDWIDTH_NUM; ++bw) अणु
			क्रम (channel = 0; channel < CHANNEL_MAX_NUMBER_2G; ++channel) अणु
				क्रम (rate_section = 0; rate_section < MAX_RATE_SECTION_NUM; ++rate_section) अणु
					/* obtain the base dBm values in 2.4G band
					 CCK => 11M, OFDM => 54M, HT 1T => MCS7, HT 2T => MCS15*/
					अगर (rate_section == 0) अणु /*CCK*/
						base_index2_4G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_2_4G, MGN_11M);
					पूर्ण अन्यथा अगर (rate_section == 1) अणु /*OFDM*/
						base_index2_4G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_2_4G, MGN_54M);
					पूर्ण अन्यथा अगर (rate_section == 2) अणु /*HT IT*/
						base_index2_4G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_2_4G, MGN_MCS7);
					पूर्ण अन्यथा अगर (rate_section == 3) अणु /*HT 2T*/
						base_index2_4G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_2_4G, MGN_MCS15);
					पूर्ण

					temp_pwrlmt = rtlphy->txpwr_limit_2_4g[regulation]
						[bw][rate_section][channel][RF90_PATH_A];

					क्रम (rf_path = RF90_PATH_A;
						rf_path < MAX_RF_PATH_NUM;
						++rf_path) अणु
						अगर (rate_section == 3)
							bw40_pwr_base_dbm2_4G =
							rtlphy->txpwr_by_rate_base_24g[rf_path][RF_2TX][base_index2_4G];
						अन्यथा
							bw40_pwr_base_dbm2_4G =
							rtlphy->txpwr_by_rate_base_24g[rf_path][RF_1TX][base_index2_4G];

						अगर (temp_pwrlmt != MAX_POWER_INDEX) अणु
							temp_value = temp_pwrlmt - bw40_pwr_base_dbm2_4G;
							rtlphy->txpwr_limit_2_4g[regulation]
								[bw][rate_section][channel][rf_path] =
								temp_value;
						पूर्ण

						rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
							"TxPwrLimit_2_4G[regulation %d][bw %d][rateSection %d][channel %d] = %d\n(TxPwrLimit in dBm %d - BW40PwrLmt2_4G[channel %d][rfpath %d] %d)\n",
							regulation, bw, rate_section, channel,
							rtlphy->txpwr_limit_2_4g[regulation][bw]
							[rate_section][channel][rf_path], (temp_pwrlmt == 63)
							? 0 : temp_pwrlmt/2, channel, rf_path,
							bw40_pwr_base_dbm2_4G);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) अणु
		क्रम (bw = 0; bw < MAX_5G_BANDWIDTH_NUM; ++bw) अणु
			क्रम (channel = 0; channel < CHANNEL_MAX_NUMBER_5G; ++channel) अणु
				क्रम (rate_section = 0; rate_section < MAX_RATE_SECTION_NUM; ++rate_section) अणु
					/* obtain the base dBm values in 5G band
					 OFDM => 54M, HT 1T => MCS7, HT 2T => MCS15,
					VHT => 1SSMCS7, VHT 2T => 2SSMCS7*/
					अगर (rate_section == 1) अणु /*OFDM*/
						base_index5G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_5G, MGN_54M);
					पूर्ण अन्यथा अगर (rate_section == 2) अणु /*HT 1T*/
						base_index5G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_5G, MGN_MCS7);
					पूर्ण अन्यथा अगर (rate_section == 3) अणु /*HT 2T*/
						base_index5G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_5G, MGN_MCS15);
					पूर्ण अन्यथा अगर (rate_section == 4) अणु /*VHT 1T*/
						base_index5G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_5G, MGN_VHT1SS_MCS7);
					पूर्ण अन्यथा अगर (rate_section == 5) अणु /*VHT 2T*/
						base_index5G =
							_rtl8812ae_phy_get_txघातer_by_rate_base_index(hw,
							BAND_ON_5G, MGN_VHT2SS_MCS7);
					पूर्ण

					temp_pwrlmt = rtlphy->txpwr_limit_5g[regulation]
						[bw][rate_section][channel]
						[RF90_PATH_A];

					क्रम (rf_path = RF90_PATH_A;
					     rf_path < MAX_RF_PATH_NUM;
					     ++rf_path) अणु
						अगर (rate_section == 3 || rate_section == 5)
							bw40_pwr_base_dbm5G =
							rtlphy->txpwr_by_rate_base_5g[rf_path]
							[RF_2TX][base_index5G];
						अन्यथा
							bw40_pwr_base_dbm5G =
							rtlphy->txpwr_by_rate_base_5g[rf_path]
							[RF_1TX][base_index5G];

						अगर (temp_pwrlmt != MAX_POWER_INDEX) अणु
							temp_value =
								temp_pwrlmt - bw40_pwr_base_dbm5G;
							rtlphy->txpwr_limit_5g[regulation]
								[bw][rate_section][channel]
								[rf_path] = temp_value;
						पूर्ण

						rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
							"TxPwrLimit_5G[regulation %d][bw %d][rateSection %d][channel %d] =%d\n(TxPwrLimit in dBm %d - BW40PwrLmt5G[chnl group %d][rfpath %d] %d)\n",
							regulation, bw, rate_section,
							channel, rtlphy->txpwr_limit_5g[regulation]
							[bw][rate_section][channel][rf_path],
							temp_pwrlmt, channel, rf_path, bw40_pwr_base_dbm5G);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"<===== %s()\n", __func__);
पूर्ण

अटल व्योम _rtl8821ae_phy_init_txघातer_limit(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 i, j, k, l, m;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"=====>`%s()!\n", __func__);

	क्रम (i = 0; i < MAX_REGULATION_NUM; ++i) अणु
		क्रम (j = 0; j < MAX_2_4G_BANDWIDTH_NUM; ++j)
			क्रम (k = 0; k < MAX_RATE_SECTION_NUM; ++k)
				क्रम (m = 0; m < CHANNEL_MAX_NUMBER_2G; ++m)
					क्रम (l = 0; l < MAX_RF_PATH_NUM; ++l)
						rtlphy->txpwr_limit_2_4g
								[i][j][k][m][l]
							= MAX_POWER_INDEX;
	पूर्ण
	क्रम (i = 0; i < MAX_REGULATION_NUM; ++i) अणु
		क्रम (j = 0; j < MAX_5G_BANDWIDTH_NUM; ++j)
			क्रम (k = 0; k < MAX_RATE_SECTION_NUM; ++k)
				क्रम (m = 0; m < CHANNEL_MAX_NUMBER_5G; ++m)
					क्रम (l = 0; l < MAX_RF_PATH_NUM; ++l)
						rtlphy->txpwr_limit_5g
								[i][j][k][m][l]
							= MAX_POWER_INDEX;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"<===== %s()!\n", __func__);
पूर्ण

अटल व्योम _rtl8821ae_phy_convert_txघातer_dbm_to_relative_value(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 base = 0, rfpath = 0;

	क्रम (rfpath = RF90_PATH_A; rfpath <= RF90_PATH_B; ++rfpath) अणु
		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G, rfpath, RF_1TX, CCK);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][0],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G, rfpath, RF_1TX, OFDM);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][1],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][2],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G, rfpath, RF_1TX, HT_MCS0_MCS7);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][3],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][4],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G, rfpath, RF_2TX, HT_MCS8_MCS15);

		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_2TX][5],
			0, 3, base);

		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_2TX][6],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G, rfpath, RF_1TX, VHT_1SSMCS0_1SSMCS9);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][7],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][8],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][9],
			0, 1, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_2_4G, rfpath, RF_2TX, VHT_2SSMCS0_2SSMCS9);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_1TX][9],
			2, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_2TX][10],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_2_4G][rfpath][RF_2TX][11],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_5G, rfpath, RF_1TX, OFDM);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][1],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][2],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_5G, rfpath, RF_1TX, HT_MCS0_MCS7);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][3],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][4],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_5G, rfpath, RF_2TX, HT_MCS8_MCS15);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_2TX][5],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_2TX][6],
			0, 3, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_5G, rfpath, RF_1TX, VHT_1SSMCS0_1SSMCS9);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][7],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][8],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][9],
			0, 1, base);

		base = _rtl8821ae_phy_get_txघातer_by_rate_base(hw, BAND_ON_5G, rfpath, RF_2TX, VHT_2SSMCS0_2SSMCS9);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_1TX][9],
			2, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_2TX][10],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[BAND_ON_5G][rfpath][RF_2TX][11],
			0, 3, base);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
		"<===_rtl8821ae_phy_convert_txpower_dbm_to_relative_value()\n");
पूर्ण

अटल व्योम _rtl8821ae_phy_txघातer_by_rate_configuration(काष्ठा ieee80211_hw *hw)
अणु
	_rtl8821ae_phy_store_txघातer_by_rate_base(hw);
	_rtl8821ae_phy_convert_txघातer_dbm_to_relative_value(hw);
पूर्ण

/* string is in decimal */
अटल bool _rtl8812ae_get_पूर्णांकeger_from_string(स्थिर अक्षर *str, u8 *pपूर्णांक)
अणु
	u16 i = 0;
	*pपूर्णांक = 0;

	जबतक (str[i] != '\0') अणु
		अगर (str[i] >= '0' && str[i] <= '9') अणु
			*pपूर्णांक *= 10;
			*pपूर्णांक += (str[i] - '0');
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		++i;
	पूर्ण

	वापस true;
पूर्ण

अटल bool _rtl8812ae_eq_n_byte(स्थिर अक्षर *str1, स्थिर अक्षर *str2, u32 num)
अणु
	अगर (num == 0)
		वापस false;
	जबतक (num > 0) अणु
		num--;
		अगर (str1[num] != str2[num])
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल s8 _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(काष्ठा ieee80211_hw *hw,
					      u8 band, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	s8 channel_index = -1;
	u8  i = 0;

	अगर (band == BAND_ON_2_4G)
		channel_index = channel - 1;
	अन्यथा अगर (band == BAND_ON_5G) अणु
		क्रम (i = 0; i < माप(channel5g)/माप(u8); ++i) अणु
			अगर (channel5g[i] == channel)
				channel_index = i;
		पूर्ण
	पूर्ण अन्यथा
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "Invalid Band %d in %s\n",
			band,  __func__);

	अगर (channel_index == -1)
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Invalid Channel %d of Band %d in %s\n", channel,
			band, __func__);

	वापस channel_index;
पूर्ण

अटल व्योम _rtl8812ae_phy_set_txघातer_limit(काष्ठा ieee80211_hw *hw,
				      स्थिर अक्षर *pregulation,
				      स्थिर अक्षर *pband, स्थिर अक्षर *pbandwidth,
				      स्थिर अक्षर *prate_section, स्थिर अक्षर *prf_path,
				      स्थिर अक्षर *pchannel, स्थिर अक्षर *pघातer_limit)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 regulation = 0, bandwidth = 0, rate_section = 0, channel;
	u8 channel_index;
	s8 घातer_limit = 0, prev_घातer_limit, ret;

	अगर (!_rtl8812ae_get_पूर्णांकeger_from_string(pchannel, &channel) ||
	    !_rtl8812ae_get_पूर्णांकeger_from_string(pघातer_limit,
						&घातer_limit)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Illegal index of pwr_lmt table [chnl %d][val %d]\n",
			channel, घातer_limit);
	पूर्ण

	घातer_limit = घातer_limit > MAX_POWER_INDEX ?
		      MAX_POWER_INDEX : घातer_limit;

	अगर (_rtl8812ae_eq_n_byte(pregulation, "FCC", 3))
		regulation = 0;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(pregulation, "MKK", 3))
		regulation = 1;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(pregulation, "ETSI", 4))
		regulation = 2;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(pregulation, "WW13", 4))
		regulation = 3;

	अगर (_rtl8812ae_eq_n_byte(prate_section, "CCK", 3))
		rate_section = 0;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(prate_section, "OFDM", 4))
		rate_section = 1;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(prate_section, "HT", 2) &&
		 _rtl8812ae_eq_n_byte(prf_path, "1T", 2))
		rate_section = 2;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(prate_section, "HT", 2) &&
		 _rtl8812ae_eq_n_byte(prf_path, "2T", 2))
		rate_section = 3;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(prate_section, "VHT", 3) &&
		 _rtl8812ae_eq_n_byte(prf_path, "1T", 2))
		rate_section = 4;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(prate_section, "VHT", 3) &&
		 _rtl8812ae_eq_n_byte(prf_path, "2T", 2))
		rate_section = 5;

	अगर (_rtl8812ae_eq_n_byte(pbandwidth, "20M", 3))
		bandwidth = 0;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(pbandwidth, "40M", 3))
		bandwidth = 1;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(pbandwidth, "80M", 3))
		bandwidth = 2;
	अन्यथा अगर (_rtl8812ae_eq_n_byte(pbandwidth, "160M", 4))
		bandwidth = 3;

	अगर (_rtl8812ae_eq_n_byte(pband, "2.4G", 4)) अणु
		ret = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
							       BAND_ON_2_4G,
							       channel);

		अगर (ret == -1)
			वापस;

		channel_index = ret;

		prev_घातer_limit = rtlphy->txpwr_limit_2_4g[regulation]
						[bandwidth][rate_section]
						[channel_index][RF90_PATH_A];

		अगर (घातer_limit < prev_घातer_limit)
			rtlphy->txpwr_limit_2_4g[regulation][bandwidth]
				[rate_section][channel_index][RF90_PATH_A] =
								   घातer_limit;

		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"2.4G [regula %d][bw %d][sec %d][chnl %d][val %d]\n",
			regulation, bandwidth, rate_section, channel_index,
			rtlphy->txpwr_limit_2_4g[regulation][bandwidth]
				[rate_section][channel_index][RF90_PATH_A]);
	पूर्ण अन्यथा अगर (_rtl8812ae_eq_n_byte(pband, "5G", 2)) अणु
		ret = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
							       BAND_ON_5G,
							       channel);

		अगर (ret == -1)
			वापस;

		channel_index = ret;

		prev_घातer_limit = rtlphy->txpwr_limit_5g[regulation][bandwidth]
						[rate_section][channel_index]
						[RF90_PATH_A];

		अगर (घातer_limit < prev_घातer_limit)
			rtlphy->txpwr_limit_5g[regulation][bandwidth]
			[rate_section][channel_index][RF90_PATH_A] = घातer_limit;

		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"5G: [regul %d][bw %d][sec %d][chnl %d][val %d]\n",
			regulation, bandwidth, rate_section, channel,
			rtlphy->txpwr_limit_5g[regulation][bandwidth]
				[rate_section][channel_index][RF90_PATH_A]);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"Cannot recognize the band info in %s\n", pband);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम _rtl8812ae_phy_config_bb_txpwr_lmt(काष्ठा ieee80211_hw *hw,
					  स्थिर अक्षर *regulation, स्थिर अक्षर *band,
					  स्थिर अक्षर *bandwidth, स्थिर अक्षर *rate_section,
					  स्थिर अक्षर *rf_path, स्थिर अक्षर *channel,
					  स्थिर अक्षर *घातer_limit)
अणु
	_rtl8812ae_phy_set_txघातer_limit(hw, regulation, band, bandwidth,
					 rate_section, rf_path, channel,
					 घातer_limit);
पूर्ण

अटल व्योम _rtl8821ae_phy_पढ़ो_and_config_txpwr_lmt(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 i = 0;
	u32 array_len;
	स्थिर अक्षर **array;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
		array_len = RTL8812AE_TXPWR_LMT_ARRAY_LEN;
		array = RTL8812AE_TXPWR_LMT;
	पूर्ण अन्यथा अणु
		array_len = RTL8821AE_TXPWR_LMT_ARRAY_LEN;
		array = RTL8821AE_TXPWR_LMT;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "\n");

	क्रम (i = 0; i < array_len; i += 7) अणु
		स्थिर अक्षर *regulation = array[i];
		स्थिर अक्षर *band = array[i+1];
		स्थिर अक्षर *bandwidth = array[i+2];
		स्थिर अक्षर *rate = array[i+3];
		स्थिर अक्षर *rf_path = array[i+4];
		स्थिर अक्षर *chnl = array[i+5];
		स्थिर अक्षर *val = array[i+6];

		_rtl8812ae_phy_config_bb_txpwr_lmt(hw, regulation, band,
						   bandwidth, rate, rf_path,
						   chnl, val);
	पूर्ण
पूर्ण

अटल bool _rtl8821ae_phy_bb8821a_config_parafile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus;

	_rtl8821ae_phy_init_txघातer_limit(hw);

	/* RegEnableTxPowerLimit == 1 क्रम 8812a & 8821a */
	अगर (rtlefuse->eeprom_regulatory != 2)
		_rtl8821ae_phy_पढ़ो_and_config_txpwr_lmt(hw);

	rtstatus = _rtl8821ae_phy_config_bb_with_headerfile(hw,
						       BASEBAND_CONFIG_PHY_REG);
	अगर (!rtstatus) अणु
		pr_err("Write BB Reg Fail!!\n");
		वापस false;
	पूर्ण
	_rtl8821ae_phy_init_tx_घातer_by_rate(hw);
	अगर (!rtlefuse->स्वतःload_failflag) अणु
		rtstatus = _rtl8821ae_phy_config_bb_with_pgheaderfile(hw,
						    BASEBAND_CONFIG_PHY_REG);
	पूर्ण
	अगर (!rtstatus) अणु
		pr_err("BB_PG Reg Fail!!\n");
		वापस false;
	पूर्ण

	_rtl8821ae_phy_txघातer_by_rate_configuration(hw);

	/* RegEnableTxPowerLimit == 1 क्रम 8812a & 8821a */
	अगर (rtlefuse->eeprom_regulatory != 2)
		_rtl8812ae_phy_convert_txघातer_limit_to_घातer_index(hw);

	rtstatus = _rtl8821ae_phy_config_bb_with_headerfile(hw,
						BASEBAND_CONFIG_AGC_TAB);

	अगर (!rtstatus) अणु
		pr_err("AGC Table Fail\n");
		वापस false;
	पूर्ण
	rtlphy->cck_high_घातer = (bool)(rtl_get_bbreg(hw,
			RFPGA0_XA_HSSIPARAMETER2, 0x200));
	वापस true;
पूर्ण

अटल bool
__rtl8821ae_phy_config_with_headerfile(काष्ठा ieee80211_hw *hw,
				       u32 *array_table, u16 arraylen,
				       व्योम (*set_reg)(काष्ठा ieee80211_hw *hw,
						       u32 regaddr, u32 data))
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
				अगर (cond == COND_ENDIF) अणु/*end*/
					matched = true;
					skipped = false;
				पूर्ण अन्यथा अगर (cond == COND_ELSE) /*अन्यथा*/
					matched = skipped ? false : true;
				अन्यथा अणु/*अगर , अन्यथा अगर*/
					अगर (skipped) अणु
						matched = false;
					पूर्ण अन्यथा अणु
						अगर (_rtl8821ae_check_positive(
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

अटल bool _rtl8821ae_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 arraylength;
	u32 *ptrarray;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Read MAC_REG_Array\n");
	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		arraylength = RTL8821AE_MAC_1T_ARRAYLEN;
		ptrarray = RTL8821AE_MAC_REG_ARRAY;
	पूर्ण अन्यथा अणु
		arraylength = RTL8812AE_MAC_1T_ARRAYLEN;
		ptrarray = RTL8812AE_MAC_REG_ARRAY;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Img: MAC_REG_ARRAY LEN %d\n", arraylength);

	वापस __rtl8821ae_phy_config_with_headerfile(hw,
			ptrarray, arraylength, rtl_ग_लिखो_byte_with_val32);
पूर्ण

अटल bool _rtl8821ae_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
						     u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 *array_table;
	u16 arraylen;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			arraylen = RTL8812AE_PHY_REG_1TARRAYLEN;
			array_table = RTL8812AE_PHY_REG_ARRAY;
		पूर्ण अन्यथा अणु
			arraylen = RTL8821AE_PHY_REG_1TARRAYLEN;
			array_table = RTL8821AE_PHY_REG_ARRAY;
		पूर्ण

		वापस __rtl8821ae_phy_config_with_headerfile(hw,
				array_table, arraylen,
				_rtl8821ae_config_bb_reg);
	पूर्ण अन्यथा अगर (configtype == BASEBAND_CONFIG_AGC_TAB) अणु
		अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
			arraylen = RTL8812AE_AGC_TAB_1TARRAYLEN;
			array_table = RTL8812AE_AGC_TAB_ARRAY;
		पूर्ण अन्यथा अणु
			arraylen = RTL8821AE_AGC_TAB_1TARRAYLEN;
			array_table = RTL8821AE_AGC_TAB_ARRAY;
		पूर्ण

		वापस __rtl8821ae_phy_config_with_headerfile(hw,
				array_table, arraylen,
				rtl_set_bbreg_with_dwmask);
	पूर्ण
	वापस true;
पूर्ण

अटल u8 _rtl8821ae_get_rate_section_index(u32 regaddr)
अणु
	u8 index = 0;
	regaddr &= 0xFFF;
	अगर (regaddr >= 0xC20 && regaddr <= 0xC4C)
		index = (u8)((regaddr - 0xC20) / 4);
	अन्यथा अगर (regaddr >= 0xE20 && regaddr <= 0xE4C)
		index = (u8)((regaddr - 0xE20) / 4);
	अन्यथा
		WARN_ONCE(true,
			  "rtl8821ae: Invalid RegAddr 0x%x\n", regaddr);
	वापस index;
पूर्ण

अटल व्योम _rtl8821ae_store_tx_घातer_by_rate(काष्ठा ieee80211_hw *hw,
					      u32 band, u32 rfpath,
					      u32 txnum, u32 regaddr,
					      u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 rate_section = _rtl8821ae_get_rate_section_index(regaddr);

	अगर (band != BAND_ON_2_4G && band != BAND_ON_5G) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid Band %d\n", band);
		band = BAND_ON_2_4G;
	पूर्ण
	अगर (rfpath >= MAX_RF_PATH) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid RfPath %d\n", rfpath);
		rfpath = MAX_RF_PATH - 1;
	पूर्ण
	अगर (txnum >= MAX_RF_PATH) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_WARNING, "Invalid TxNum %d\n", txnum);
		txnum = MAX_RF_PATH - 1;
	पूर्ण
	rtlphy->tx_घातer_by_rate_offset[band][rfpath][txnum][rate_section] = data;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"TxPwrByRateOffset[Band %d][RfPath %d][TxNum %d][RateSection %d] = 0x%x\n",
		band, rfpath, txnum, rate_section,
		rtlphy->tx_घातer_by_rate_offset[band][rfpath][txnum][rate_section]);
पूर्ण

अटल bool _rtl8821ae_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
							u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	पूर्णांक i;
	u32 *array;
	u16 arraylen;
	u32 v1, v2, v3, v4, v5, v6;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE) अणु
		arraylen = RTL8812AE_PHY_REG_ARRAY_PGLEN;
		array = RTL8812AE_PHY_REG_ARRAY_PG;
	पूर्ण अन्यथा अणु
		arraylen = RTL8821AE_PHY_REG_ARRAY_PGLEN;
		array = RTL8821AE_PHY_REG_ARRAY_PG;
	पूर्ण

	अगर (configtype != BASEBAND_CONFIG_PHY_REG) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"configtype != BaseBand_Config_PHY_REG\n");
		वापस true;
	पूर्ण
	क्रम (i = 0; i < arraylen; i += 6) अणु
		v1 = array[i];
		v2 = array[i+1];
		v3 = array[i+2];
		v4 = array[i+3];
		v5 = array[i+4];
		v6 = array[i+5];

		अगर (v1 < 0xCDCDCDCD) अणु
			अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE &&
				(v4 == 0xfe || v4 == 0xffe)) अणु
				msleep(50);
				जारी;
			पूर्ण

			अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
				अगर (v4 == 0xfe)
					msleep(50);
				अन्यथा अगर (v4 == 0xfd)
					mdelay(5);
				अन्यथा अगर (v4 == 0xfc)
					mdelay(1);
				अन्यथा अगर (v4 == 0xfb)
					udelay(50);
				अन्यथा अगर (v4 == 0xfa)
					udelay(5);
				अन्यथा अगर (v4 == 0xf9)
					udelay(1);
			पूर्ण
			_rtl8821ae_store_tx_घातer_by_rate(hw, v1, v2, v3,
							  v4, v5, v6);
			जारी;
		पूर्ण अन्यथा अणु
			 /*करोn't need the hw_body*/
			अगर (!_rtl8821ae_check_condition(hw, v1)) अणु
				i += 2; /* skip the pair of expression*/
				v1 = array[i];
				v2 = array[i+1];
				v3 = array[i+2];
				जबतक (v2 != 0xDEAD) अणु
					i += 3;
					v1 = array[i];
					v2 = array[i+1];
					v3 = array[i+2];
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

bool rtl8812ae_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					     क्रमागत radio_path rfpath)
अणु
	u32 *radioa_array_table_a, *radioa_array_table_b;
	u16 radioa_arraylen_a, radioa_arraylen_b;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	radioa_arraylen_a = RTL8812AE_RADIOA_1TARRAYLEN;
	radioa_array_table_a = RTL8812AE_RADIOA_ARRAY;
	radioa_arraylen_b = RTL8812AE_RADIOB_1TARRAYLEN;
	radioa_array_table_b = RTL8812AE_RADIOB_ARRAY;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Radio_A:RTL8821AE_RADIOA_ARRAY %d\n", radioa_arraylen_a);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		वापस __rtl8821ae_phy_config_with_headerfile(hw,
				radioa_array_table_a, radioa_arraylen_a,
				_rtl8821ae_config_rf_radio_a);
	हाल RF90_PATH_B:
		वापस __rtl8821ae_phy_config_with_headerfile(hw,
				radioa_array_table_b, radioa_arraylen_b,
				_rtl8821ae_config_rf_radio_b);
	हाल RF90_PATH_C:
	हाल RF90_PATH_D:
		pr_err("switch case %#x not processed\n", rfpath);
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

bool rtl8821ae_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
						क्रमागत radio_path rfpath)
अणु
	u32 *radioa_array_table;
	u16 radioa_arraylen;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	radioa_arraylen = RTL8821AE_RADIOA_1TARRAYLEN;
	radioa_array_table = RTL8821AE_RADIOA_ARRAY;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Radio_A:RTL8821AE_RADIOA_ARRAY %d\n", radioa_arraylen);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		वापस __rtl8821ae_phy_config_with_headerfile(hw,
			radioa_array_table, radioa_arraylen,
			_rtl8821ae_config_rf_radio_a);

	हाल RF90_PATH_B:
	हाल RF90_PATH_C:
	हाल RF90_PATH_D:
		pr_err("switch case %#x not processed\n", rfpath);
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

व्योम rtl8821ae_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw)
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

	rtlphy->framesync = (u8)rtl_get_bbreg(hw,
					       ROFDM0_RXDETECTOR3, MASKBYTE0);
	rtlphy->framesync_c34 = rtl_get_bbreg(hw,
					      ROFDM0_RXDETECTOR2, MASKDWORD);

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"Default framesync (0x%x) = 0x%x\n",
		ROFDM0_RXDETECTOR3, rtlphy->framesync);
पूर्ण

अटल व्योम phy_init_bb_rf_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfo = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfo = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfe = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfe = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rf3wire_offset = RA_LSSIWRITE_8821A;
	rtlphy->phyreg_def[RF90_PATH_B].rf3wire_offset = RB_LSSIWRITE_8821A;

	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para2 = RHSSIREAD_8821AE;
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para2 = RHSSIREAD_8821AE;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rb = RA_SIREAD_8821A;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rb = RB_SIREAD_8821A;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rbpi = RA_PIREAD_8821A;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rbpi = RB_PIREAD_8821A;
पूर्ण

व्योम rtl8821ae_phy_get_txघातer_level(काष्ठा ieee80211_hw *hw, दीर्घ *घातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 txpwr_level;
	दीर्घ txpwr_dbm;

	txpwr_level = rtlphy->cur_cck_txpwridx;
	txpwr_dbm = _rtl8821ae_phy_txpwr_idx_to_dbm(hw,
						 WIRELESS_MODE_B, txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx;
	अगर (_rtl8821ae_phy_txpwr_idx_to_dbm(hw,
					 WIRELESS_MODE_G,
					 txpwr_level) > txpwr_dbm)
		txpwr_dbm =
		    _rtl8821ae_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_G,
						 txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx;
	अगर (_rtl8821ae_phy_txpwr_idx_to_dbm(hw,
					 WIRELESS_MODE_N_24G,
					 txpwr_level) > txpwr_dbm)
		txpwr_dbm =
		    _rtl8821ae_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_N_24G,
						 txpwr_level);
	*घातerlevel = txpwr_dbm;
पूर्ण

अटल bool _rtl8821ae_phy_get_chnl_index(u8 channel, u8 *chnl_index)
अणु
	u8 i = 0;
	bool in_24g = true;

	अगर (channel <= 14) अणु
		in_24g = true;
		*chnl_index = channel - 1;
	पूर्ण अन्यथा अणु
		in_24g = false;

		क्रम (i = 0; i < CHANNEL_MAX_NUMBER_5G; ++i) अणु
			अगर (channel5g[i] == channel) अणु
				*chnl_index = i;
				वापस in_24g;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस in_24g;
पूर्ण

अटल s8 _rtl8821ae_phy_get_ratesection_पूर्णांकxघातer_byrate(u8 path, u8 rate)
अणु
	s8 rate_section = 0;
	चयन (rate) अणु
	हाल DESC_RATE1M:
	हाल DESC_RATE2M:
	हाल DESC_RATE5_5M:
	हाल DESC_RATE11M:
		rate_section = 0;
		अवरोध;
	हाल DESC_RATE6M:
	हाल DESC_RATE9M:
	हाल DESC_RATE12M:
	हाल DESC_RATE18M:
		rate_section = 1;
		अवरोध;
	हाल DESC_RATE24M:
	हाल DESC_RATE36M:
	हाल DESC_RATE48M:
	हाल DESC_RATE54M:
		rate_section = 2;
		अवरोध;
	हाल DESC_RATEMCS0:
	हाल DESC_RATEMCS1:
	हाल DESC_RATEMCS2:
	हाल DESC_RATEMCS3:
		rate_section = 3;
		अवरोध;
	हाल DESC_RATEMCS4:
	हाल DESC_RATEMCS5:
	हाल DESC_RATEMCS6:
	हाल DESC_RATEMCS7:
		rate_section = 4;
		अवरोध;
	हाल DESC_RATEMCS8:
	हाल DESC_RATEMCS9:
	हाल DESC_RATEMCS10:
	हाल DESC_RATEMCS11:
		rate_section = 5;
		अवरोध;
	हाल DESC_RATEMCS12:
	हाल DESC_RATEMCS13:
	हाल DESC_RATEMCS14:
	हाल DESC_RATEMCS15:
		rate_section = 6;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS0:
	हाल DESC_RATEVHT1SS_MCS1:
	हाल DESC_RATEVHT1SS_MCS2:
	हाल DESC_RATEVHT1SS_MCS3:
		rate_section = 7;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS4:
	हाल DESC_RATEVHT1SS_MCS5:
	हाल DESC_RATEVHT1SS_MCS6:
	हाल DESC_RATEVHT1SS_MCS7:
		rate_section = 8;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS8:
	हाल DESC_RATEVHT1SS_MCS9:
	हाल DESC_RATEVHT2SS_MCS0:
	हाल DESC_RATEVHT2SS_MCS1:
		rate_section = 9;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS2:
	हाल DESC_RATEVHT2SS_MCS3:
	हाल DESC_RATEVHT2SS_MCS4:
	हाल DESC_RATEVHT2SS_MCS5:
		rate_section = 10;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS6:
	हाल DESC_RATEVHT2SS_MCS7:
	हाल DESC_RATEVHT2SS_MCS8:
	हाल DESC_RATEVHT2SS_MCS9:
		rate_section = 11;
		अवरोध;
	शेष:
		WARN_ONCE(true, "rtl8821ae: Rate_Section is Illegal\n");
		अवरोध;
	पूर्ण

	वापस rate_section;
पूर्ण

अटल s8 _rtl8812ae_phy_get_world_wide_limit(s8  *limit_table)
अणु
	s8 min = limit_table[0];
	u8 i = 0;

	क्रम (i = 0; i < MAX_REGULATION_NUM; ++i) अणु
		अगर (limit_table[i] < min)
			min = limit_table[i];
	पूर्ण
	वापस min;
पूर्ण

अटल s8 _rtl8812ae_phy_get_txघातer_limit(काष्ठा ieee80211_hw *hw,
					     u8 band,
					     क्रमागत ht_channel_width bandwidth,
					     क्रमागत radio_path rf_path,
					     u8 rate, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	लघु band_temp = -1, regulation = -1, bandwidth_temp = -1,
		 rate_section = -1, channel_temp = -1;
	u16 regu, bdwidth, sec, chnl;
	s8 घातer_limit = MAX_POWER_INDEX;

	अगर (rtlefuse->eeprom_regulatory == 2)
		वापस MAX_POWER_INDEX;

	regulation = TXPWR_LMT_WW;

	अगर (band == BAND_ON_2_4G)
		band_temp = 0;
	अन्यथा अगर (band == BAND_ON_5G)
		band_temp = 1;

	अगर (bandwidth == HT_CHANNEL_WIDTH_20)
		bandwidth_temp = 0;
	अन्यथा अगर (bandwidth == HT_CHANNEL_WIDTH_20_40)
		bandwidth_temp = 1;
	अन्यथा अगर (bandwidth == HT_CHANNEL_WIDTH_80)
		bandwidth_temp = 2;

	चयन (rate) अणु
	हाल DESC_RATE1M:
	हाल DESC_RATE2M:
	हाल DESC_RATE5_5M:
	हाल DESC_RATE11M:
		rate_section = 0;
		अवरोध;
	हाल DESC_RATE6M:
	हाल DESC_RATE9M:
	हाल DESC_RATE12M:
	हाल DESC_RATE18M:
	हाल DESC_RATE24M:
	हाल DESC_RATE36M:
	हाल DESC_RATE48M:
	हाल DESC_RATE54M:
		rate_section = 1;
		अवरोध;
	हाल DESC_RATEMCS0:
	हाल DESC_RATEMCS1:
	हाल DESC_RATEMCS2:
	हाल DESC_RATEMCS3:
	हाल DESC_RATEMCS4:
	हाल DESC_RATEMCS5:
	हाल DESC_RATEMCS6:
	हाल DESC_RATEMCS7:
		rate_section = 2;
		अवरोध;
	हाल DESC_RATEMCS8:
	हाल DESC_RATEMCS9:
	हाल DESC_RATEMCS10:
	हाल DESC_RATEMCS11:
	हाल DESC_RATEMCS12:
	हाल DESC_RATEMCS13:
	हाल DESC_RATEMCS14:
	हाल DESC_RATEMCS15:
		rate_section = 3;
		अवरोध;
	हाल DESC_RATEVHT1SS_MCS0:
	हाल DESC_RATEVHT1SS_MCS1:
	हाल DESC_RATEVHT1SS_MCS2:
	हाल DESC_RATEVHT1SS_MCS3:
	हाल DESC_RATEVHT1SS_MCS4:
	हाल DESC_RATEVHT1SS_MCS5:
	हाल DESC_RATEVHT1SS_MCS6:
	हाल DESC_RATEVHT1SS_MCS7:
	हाल DESC_RATEVHT1SS_MCS8:
	हाल DESC_RATEVHT1SS_MCS9:
		rate_section = 4;
		अवरोध;
	हाल DESC_RATEVHT2SS_MCS0:
	हाल DESC_RATEVHT2SS_MCS1:
	हाल DESC_RATEVHT2SS_MCS2:
	हाल DESC_RATEVHT2SS_MCS3:
	हाल DESC_RATEVHT2SS_MCS4:
	हाल DESC_RATEVHT2SS_MCS5:
	हाल DESC_RATEVHT2SS_MCS6:
	हाल DESC_RATEVHT2SS_MCS7:
	हाल DESC_RATEVHT2SS_MCS8:
	हाल DESC_RATEVHT2SS_MCS9:
		rate_section = 5;
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Wrong rate 0x%x\n", rate);
		अवरोध;
	पूर्ण

	अगर (band_temp == BAND_ON_5G  && rate_section == 0)
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Wrong rate 0x%x: No CCK in 5G Band\n", rate);

	/*workaround क्रम wrong index combination to obtain tx घातer limit,
	  OFDM only exists in BW 20M*/
	अगर (rate_section == 1)
		bandwidth_temp = 0;

	/*workaround क्रम wrong index combination to obtain tx घातer limit,
	 *HT on 80M will reference to HT on 40M
	 */
	अगर ((rate_section == 2 || rate_section == 3) && band == BAND_ON_5G &&
	    bandwidth_temp == 2)
		bandwidth_temp = 1;

	अगर (band == BAND_ON_2_4G)
		channel_temp = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
		BAND_ON_2_4G, channel);
	अन्यथा अगर (band == BAND_ON_5G)
		channel_temp = _rtl8812ae_phy_get_chnl_idx_of_txpwr_lmt(hw,
		BAND_ON_5G, channel);
	अन्यथा अगर (band == BAND_ON_BOTH) अणु
		;/* BAND_ON_BOTH करोn't care temporarily */
	पूर्ण

	अगर (band_temp == -1 || regulation == -1 || bandwidth_temp == -1 ||
		rate_section == -1 || channel_temp == -1) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Wrong index value to access power limit table [band %d][regulation %d][bandwidth %d][rf_path %d][rate_section %d][chnl %d]\n",
			band_temp, regulation, bandwidth_temp, rf_path,
			rate_section, channel_temp);
		वापस MAX_POWER_INDEX;
	पूर्ण

	regu = regulation;
	bdwidth = bandwidth_temp;
	sec = rate_section;
	chnl = channel_temp;

	अगर (band == BAND_ON_2_4G) अणु
		s8 limits[10] = अणु0पूर्ण;
		u8 i;

		क्रम (i = 0; i < 4; ++i)
			limits[i] = rtlphy->txpwr_limit_2_4g[i][bdwidth]
			[sec][chnl][rf_path];

		घातer_limit = (regulation == TXPWR_LMT_WW) ?
			_rtl8812ae_phy_get_world_wide_limit(limits) :
			rtlphy->txpwr_limit_2_4g[regu][bdwidth]
					[sec][chnl][rf_path];
	पूर्ण अन्यथा अगर (band == BAND_ON_5G) अणु
		s8 limits[10] = अणु0पूर्ण;
		u8 i;

		क्रम (i = 0; i < MAX_REGULATION_NUM; ++i)
			limits[i] = rtlphy->txpwr_limit_5g[i][bdwidth]
			[sec][chnl][rf_path];

		घातer_limit = (regulation == TXPWR_LMT_WW) ?
			_rtl8812ae_phy_get_world_wide_limit(limits) :
			rtlphy->txpwr_limit_5g[regu][chnl]
			[sec][chnl][rf_path];
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"No power limit table of the specified band\n");
	पूर्ण
	वापस घातer_limit;
पूर्ण

अटल s8 _rtl8821ae_phy_get_txघातer_by_rate(काष्ठा ieee80211_hw *hw,
					u8 band, u8 path, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 shअगरt = 0, rate_section, tx_num;
	s8 tx_pwr_dअगरf = 0;
	s8 limit = 0;

	rate_section = _rtl8821ae_phy_get_ratesection_पूर्णांकxघातer_byrate(path, rate);
	tx_num = RF_TX_NUM_NONIMPLEMENT;

	अगर (tx_num == RF_TX_NUM_NONIMPLEMENT) अणु
		अगर ((rate >= DESC_RATEMCS8 && rate <= DESC_RATEMCS15) ||
			(rate >= DESC_RATEVHT2SS_MCS2 && rate <= DESC_RATEVHT2SS_MCS9))
			tx_num = RF_2TX;
		अन्यथा
			tx_num = RF_1TX;
	पूर्ण

	चयन (rate) अणु
	हाल DESC_RATE1M:
	हाल DESC_RATE6M:
	हाल DESC_RATE24M:
	हाल DESC_RATEMCS0:
	हाल DESC_RATEMCS4:
	हाल DESC_RATEMCS8:
	हाल DESC_RATEMCS12:
	हाल DESC_RATEVHT1SS_MCS0:
	हाल DESC_RATEVHT1SS_MCS4:
	हाल DESC_RATEVHT1SS_MCS8:
	हाल DESC_RATEVHT2SS_MCS2:
	हाल DESC_RATEVHT2SS_MCS6:
		shअगरt = 0;
		अवरोध;
	हाल DESC_RATE2M:
	हाल DESC_RATE9M:
	हाल DESC_RATE36M:
	हाल DESC_RATEMCS1:
	हाल DESC_RATEMCS5:
	हाल DESC_RATEMCS9:
	हाल DESC_RATEMCS13:
	हाल DESC_RATEVHT1SS_MCS1:
	हाल DESC_RATEVHT1SS_MCS5:
	हाल DESC_RATEVHT1SS_MCS9:
	हाल DESC_RATEVHT2SS_MCS3:
	हाल DESC_RATEVHT2SS_MCS7:
		shअगरt = 8;
		अवरोध;
	हाल DESC_RATE5_5M:
	हाल DESC_RATE12M:
	हाल DESC_RATE48M:
	हाल DESC_RATEMCS2:
	हाल DESC_RATEMCS6:
	हाल DESC_RATEMCS10:
	हाल DESC_RATEMCS14:
	हाल DESC_RATEVHT1SS_MCS2:
	हाल DESC_RATEVHT1SS_MCS6:
	हाल DESC_RATEVHT2SS_MCS0:
	हाल DESC_RATEVHT2SS_MCS4:
	हाल DESC_RATEVHT2SS_MCS8:
		shअगरt = 16;
		अवरोध;
	हाल DESC_RATE11M:
	हाल DESC_RATE18M:
	हाल DESC_RATE54M:
	हाल DESC_RATEMCS3:
	हाल DESC_RATEMCS7:
	हाल DESC_RATEMCS11:
	हाल DESC_RATEMCS15:
	हाल DESC_RATEVHT1SS_MCS3:
	हाल DESC_RATEVHT1SS_MCS7:
	हाल DESC_RATEVHT2SS_MCS1:
	हाल DESC_RATEVHT2SS_MCS5:
	हाल DESC_RATEVHT2SS_MCS9:
		shअगरt = 24;
		अवरोध;
	शेष:
		WARN_ONCE(true, "rtl8821ae: Rate_Section is Illegal\n");
		अवरोध;
	पूर्ण

	tx_pwr_dअगरf = (u8)(rtlphy->tx_घातer_by_rate_offset[band][path]
		[tx_num][rate_section] >> shअगरt) & 0xff;

	/* RegEnableTxPowerLimit == 1 क्रम 8812a & 8821a */
	अगर (rtlpriv->efuse.eeprom_regulatory != 2) अणु
		limit = _rtl8812ae_phy_get_txघातer_limit(hw, band,
			rtlphy->current_chan_bw, path, rate,
			rtlphy->current_channel);

		अगर (rate == DESC_RATEVHT1SS_MCS8 || rate == DESC_RATEVHT1SS_MCS9  ||
			 rate == DESC_RATEVHT2SS_MCS8 || rate == DESC_RATEVHT2SS_MCS9) अणु
			अगर (limit < 0) अणु
				अगर (tx_pwr_dअगरf < (-limit))
					tx_pwr_dअगरf = -limit;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (limit < 0)
				tx_pwr_dअगरf = limit;
			अन्यथा
				tx_pwr_dअगरf = tx_pwr_dअगरf > limit ? limit : tx_pwr_dअगरf;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Maximum power by rate %d, final power by rate %d\n",
			limit, tx_pwr_dअगरf);
	पूर्ण

	वापस	tx_pwr_dअगरf;
पूर्ण

अटल u8 _rtl8821ae_get_txघातer_index(काष्ठा ieee80211_hw *hw, u8 path,
					u8 rate, u8 bandwidth, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);
	u8 txघातer = 0;
	bool in_24g = false;
	s8 घातerdअगरf_byrate = 0;

	अगर (((rtlhal->current_bandtype == BAND_ON_2_4G) &&
	    (channel > 14 || channel < 1)) ||
	    ((rtlhal->current_bandtype == BAND_ON_5G) && (channel <= 14))) अणु
		index = 0;
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Illegal channel!!\n");
	पूर्ण

	in_24g = _rtl8821ae_phy_get_chnl_index(channel, &index);
	अगर (in_24g) अणु
		अगर (RTL8821AE_RX_HAL_IS_CCK_RATE(rate))
			txघातer = rtlefuse->txpwrlevel_cck[path][index];
		अन्यथा अगर (DESC_RATE6M <= rate)
			txघातer = rtlefuse->txpwrlevel_ht40_1s[path][index];
		अन्यथा
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD, "invalid rate\n");

		अगर (DESC_RATE6M <= rate && rate <= DESC_RATE54M &&
		    !RTL8821AE_RX_HAL_IS_CCK_RATE(rate))
			txघातer += rtlefuse->txpwr_legacyhtdअगरf[path][TX_1S];

		अगर (bandwidth == HT_CHANNEL_WIDTH_20) अणु
			अगर ((DESC_RATEMCS0 <= rate && rate <= DESC_RATEMCS15) ||
				(DESC_RATEVHT1SS_MCS0 <= rate && rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_ht20dअगरf[path][TX_1S];
			अगर ((DESC_RATEMCS8 <= rate && rate <= DESC_RATEMCS15) ||
				(DESC_RATEVHT2SS_MCS0 <= rate && rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_ht20dअगरf[path][TX_2S];
		पूर्ण अन्यथा अगर (bandwidth == HT_CHANNEL_WIDTH_20_40) अणु
			अगर ((DESC_RATEMCS0 <= rate && rate <= DESC_RATEMCS15) ||
				(DESC_RATEVHT1SS_MCS0 <= rate && rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_ht40dअगरf[path][TX_1S];
			अगर ((DESC_RATEMCS8 <= rate && rate <= DESC_RATEMCS15) ||
				(DESC_RATEVHT2SS_MCS0 <= rate && rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_ht40dअगरf[path][TX_2S];
		पूर्ण अन्यथा अगर (bandwidth == HT_CHANNEL_WIDTH_80) अणु
			अगर ((DESC_RATEMCS0 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT1SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_ht40dअगरf[path][TX_1S];
			अगर ((DESC_RATEMCS8 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT2SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_ht40dअगरf[path][TX_2S];
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (DESC_RATE6M <= rate)
			txघातer = rtlefuse->txpwr_5g_bw40base[path][index];
		अन्यथा
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_WARNING,
				"INVALID Rate.\n");

		अगर (DESC_RATE6M <= rate && rate <= DESC_RATE54M &&
		    !RTL8821AE_RX_HAL_IS_CCK_RATE(rate))
			txघातer += rtlefuse->txpwr_5g_ofdmdअगरf[path][TX_1S];

		अगर (bandwidth == HT_CHANNEL_WIDTH_20) अणु
			अगर ((DESC_RATEMCS0 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT1SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_5g_bw20dअगरf[path][TX_1S];
			अगर ((DESC_RATEMCS8 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT2SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_5g_bw20dअगरf[path][TX_2S];
		पूर्ण अन्यथा अगर (bandwidth == HT_CHANNEL_WIDTH_20_40) अणु
			अगर ((DESC_RATEMCS0 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT1SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_5g_bw40dअगरf[path][TX_1S];
			अगर ((DESC_RATEMCS8 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT2SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer += rtlefuse->txpwr_5g_bw40dअगरf[path][TX_2S];
		पूर्ण अन्यथा अगर (bandwidth == HT_CHANNEL_WIDTH_80) अणु
			u8 i;

			क्रम (i = 0; i < माप(channel5g_80m) / माप(u8); ++i)
				अगर (channel5g_80m[i] == channel)
					index = i;

			अगर ((DESC_RATEMCS0 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT1SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer = rtlefuse->txpwr_5g_bw80base[path][index]
					+ rtlefuse->txpwr_5g_bw80dअगरf[path][TX_1S];
			अगर ((DESC_RATEMCS8 <= rate && rate <= DESC_RATEMCS15) ||
			    (DESC_RATEVHT2SS_MCS0 <= rate &&
			     rate <= DESC_RATEVHT2SS_MCS9))
				txघातer = rtlefuse->txpwr_5g_bw80base[path][index]
					+ rtlefuse->txpwr_5g_bw80dअगरf[path][TX_1S]
					+ rtlefuse->txpwr_5g_bw80dअगरf[path][TX_2S];
		    पूर्ण
	पूर्ण
	अगर (rtlefuse->eeprom_regulatory != 2)
		घातerdअगरf_byrate =
		  _rtl8821ae_phy_get_txघातer_by_rate(hw, (u8)(!in_24g),
						     path, rate);

	अगर (rate == DESC_RATEVHT1SS_MCS8 || rate == DESC_RATEVHT1SS_MCS9 ||
	    rate == DESC_RATEVHT2SS_MCS8 || rate == DESC_RATEVHT2SS_MCS9)
		txघातer -= घातerdअगरf_byrate;
	अन्यथा
		txघातer += घातerdअगरf_byrate;

	अगर (rate > DESC_RATE11M)
		txघातer += rtlpriv->dm.remnant_ofdm_swing_idx[path];
	अन्यथा
		txघातer += rtlpriv->dm.remnant_cck_idx;

	अगर (txघातer > MAX_POWER_INDEX)
		txघातer = MAX_POWER_INDEX;

	वापस txघातer;
पूर्ण

अटल व्योम _rtl8821ae_phy_set_txघातer_index(काष्ठा ieee80211_hw *hw,
					     u8 घातer_index, u8 path, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (path == RF90_PATH_A) अणु
		चयन (rate) अणु
		हाल DESC_RATE1M:
			rtl_set_bbreg(hw, RTXAGC_A_CCK11_CCK1,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATE2M:
			rtl_set_bbreg(hw, RTXAGC_A_CCK11_CCK1,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATE5_5M:
			rtl_set_bbreg(hw, RTXAGC_A_CCK11_CCK1,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATE11M:
			rtl_set_bbreg(hw, RTXAGC_A_CCK11_CCK1,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATE6M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM18_OFDM6,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATE9M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM18_OFDM6,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATE12M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM18_OFDM6,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATE18M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM18_OFDM6,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATE24M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM54_OFDM24,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATE36M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM54_OFDM24,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATE48M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM54_OFDM24,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATE54M:
			rtl_set_bbreg(hw, RTXAGC_A_OFDM54_OFDM24,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS0:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS1:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS2:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS3:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS4:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS5:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS6:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS7:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS8:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS9:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS10:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS11:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS12:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS13:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS14:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS15:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS0:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS1:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS2:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS3:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS4:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS5:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS6:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS7:
			rtl_set_bbreg(hw, RTXAGC_A_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS8:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS9:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS0:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS1:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS2:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS3:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS4:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS5:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS6:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS7:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS8:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS9:
			rtl_set_bbreg(hw, RTXAGC_A_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE3, घातer_index);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"Invalid Rate!!\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (path == RF90_PATH_B) अणु
		चयन (rate) अणु
		हाल DESC_RATE1M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_CCK1,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATE2M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_CCK1,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATE5_5M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_CCK1,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATE11M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_CCK1,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATE6M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM18_OFDM6,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATE9M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM18_OFDM6,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATE12M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM18_OFDM6,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATE18M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM18_OFDM6,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATE24M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM54_OFDM24,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATE36M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM54_OFDM24,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATE48M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM54_OFDM24,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATE54M:
			rtl_set_bbreg(hw, RTXAGC_B_OFDM54_OFDM24,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS0:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS1:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS2:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS3:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS4:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS5:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS6:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS7:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS8:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS9:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS10:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS11:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS12:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS13:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS14:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEMCS15:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS0:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS1:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS2:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS3:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX3_NSS1INDEX0,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS4:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS5:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS6:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS7:
			rtl_set_bbreg(hw, RTXAGC_B_NSS1INDEX7_NSS1INDEX4,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS8:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS9:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS0:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS1:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX1_NSS1INDEX8,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS2:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS3:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS4:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS5:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX5_NSS2INDEX2,
				      MASKBYTE3, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS6:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE0, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS7:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE1, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS8:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE2, घातer_index);
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS9:
			rtl_set_bbreg(hw, RTXAGC_B_NSS2INDEX9_NSS2INDEX6,
				      MASKBYTE3, घातer_index);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"Invalid Rate!!\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Invalid RFPath!!\n");
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_phy_set_txघातer_level_by_path(काष्ठा ieee80211_hw *hw,
						     u8 *array, u8 path,
						     u8 channel, u8 size)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 i;
	u8 घातer_index;

	क्रम (i = 0; i < size; i++) अणु
		घातer_index =
		  _rtl8821ae_get_txघातer_index(hw, path, array[i],
					       rtlphy->current_chan_bw,
					       channel);
		_rtl8821ae_phy_set_txघातer_index(hw, घातer_index, path,
						 array[i]);
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_phy_txघातer_training_by_path(काष्ठा ieee80211_hw *hw,
						    u8 bw, u8 channel, u8 path)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	u8 i;
	u32 घातer_level, data, offset;

	अगर (path >= rtlphy->num_total_rfpath)
		वापस;

	data = 0;
	अगर (path == RF90_PATH_A) अणु
		घातer_level =
			_rtl8821ae_get_txघातer_index(hw, RF90_PATH_A,
			DESC_RATEMCS7, bw, channel);
		offset =  RA_TXPWRTRAING;
	पूर्ण अन्यथा अणु
		घातer_level =
			_rtl8821ae_get_txघातer_index(hw, RF90_PATH_B,
			DESC_RATEMCS7, bw, channel);
		offset =  RB_TXPWRTRAING;
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		अगर (i == 0)
			घातer_level = घातer_level - 10;
		अन्यथा अगर (i == 1)
			घातer_level = घातer_level - 8;
		अन्यथा
			घातer_level = घातer_level - 6;

		data |= (((घातer_level > 2) ? (घातer_level) : 2) << (i * 8));
	पूर्ण
	rtl_set_bbreg(hw, offset, 0xffffff, data);
पूर्ण

व्योम rtl8821ae_phy_set_txघातer_level_by_path(काष्ठा ieee80211_hw *hw,
					     u8 channel, u8 path)
अणु
	/* काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw)); */
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 cck_rates[]  = अणुDESC_RATE1M, DESC_RATE2M, DESC_RATE5_5M,
			      DESC_RATE11Mपूर्ण;
	u8 sizes_of_cck_retes = 4;
	u8 ofdm_rates[]  = अणुDESC_RATE6M, DESC_RATE9M, DESC_RATE12M,
				DESC_RATE18M, DESC_RATE24M, DESC_RATE36M,
				DESC_RATE48M, DESC_RATE54Mपूर्ण;
	u8 sizes_of_ofdm_retes = 8;
	u8 ht_rates_1t[]  = अणुDESC_RATEMCS0, DESC_RATEMCS1, DESC_RATEMCS2,
				DESC_RATEMCS3, DESC_RATEMCS4, DESC_RATEMCS5,
				DESC_RATEMCS6, DESC_RATEMCS7पूर्ण;
	u8 sizes_of_ht_retes_1t = 8;
	u8 ht_rates_2t[]  = अणुDESC_RATEMCS8, DESC_RATEMCS9,
				DESC_RATEMCS10, DESC_RATEMCS11,
				DESC_RATEMCS12, DESC_RATEMCS13,
				DESC_RATEMCS14, DESC_RATEMCS15पूर्ण;
	u8 sizes_of_ht_retes_2t = 8;
	u8 vht_rates_1t[]  = अणुDESC_RATEVHT1SS_MCS0, DESC_RATEVHT1SS_MCS1,
				DESC_RATEVHT1SS_MCS2, DESC_RATEVHT1SS_MCS3,
				DESC_RATEVHT1SS_MCS4, DESC_RATEVHT1SS_MCS5,
				DESC_RATEVHT1SS_MCS6, DESC_RATEVHT1SS_MCS7,
			     DESC_RATEVHT1SS_MCS8, DESC_RATEVHT1SS_MCS9पूर्ण;
	u8 vht_rates_2t[]  = अणुDESC_RATEVHT2SS_MCS0, DESC_RATEVHT2SS_MCS1,
				DESC_RATEVHT2SS_MCS2, DESC_RATEVHT2SS_MCS3,
				DESC_RATEVHT2SS_MCS4, DESC_RATEVHT2SS_MCS5,
				DESC_RATEVHT2SS_MCS6, DESC_RATEVHT2SS_MCS7,
				DESC_RATEVHT2SS_MCS8, DESC_RATEVHT2SS_MCS9पूर्ण;
	u8 sizes_of_vht_retes = 10;

	अगर (rtlhal->current_bandtype == BAND_ON_2_4G)
		_rtl8821ae_phy_set_txघातer_level_by_path(hw, cck_rates, path, channel,
							 sizes_of_cck_retes);

	_rtl8821ae_phy_set_txघातer_level_by_path(hw, ofdm_rates, path, channel,
						 sizes_of_ofdm_retes);
	_rtl8821ae_phy_set_txघातer_level_by_path(hw, ht_rates_1t, path, channel,
						 sizes_of_ht_retes_1t);
	_rtl8821ae_phy_set_txघातer_level_by_path(hw, vht_rates_1t, path, channel,
						 sizes_of_vht_retes);

	अगर (rtlphy->num_total_rfpath >= 2) अणु
		_rtl8821ae_phy_set_txघातer_level_by_path(hw, ht_rates_2t, path,
							 channel,
							 sizes_of_ht_retes_2t);
		_rtl8821ae_phy_set_txघातer_level_by_path(hw, vht_rates_2t, path,
							 channel,
							 sizes_of_vht_retes);
	पूर्ण

	_rtl8821ae_phy_txघातer_training_by_path(hw, rtlphy->current_chan_bw,
						channel, path);
पूर्ण

/*just in हाल, ग_लिखो txघातer in DW, to reduce समय*/
व्योम rtl8821ae_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 path = 0;

	क्रम (path = RF90_PATH_A; path < rtlphy->num_total_rfpath; ++path)
		rtl8821ae_phy_set_txघातer_level_by_path(hw, channel, path);
पूर्ण

अटल दीर्घ _rtl8821ae_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
					    क्रमागत wireless_mode wirelessmode,
					    u8 txpwridx)
अणु
	दीर्घ offset;
	दीर्घ pwrout_dbm;

	चयन (wirelessmode) अणु
	हाल WIRELESS_MODE_B:
		offset = -7;
		अवरोध;
	हाल WIRELESS_MODE_G:
	हाल WIRELESS_MODE_N_24G:
		offset = -8;
		अवरोध;
	शेष:
		offset = -8;
		अवरोध;
	पूर्ण
	pwrout_dbm = txpwridx / 2 + offset;
	वापस pwrout_dbm;
पूर्ण

व्योम rtl8821ae_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw, u8 operation)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	क्रमागत io_type iotype = IO_CMD_PAUSE_BAND0_DM_BY_SCAN;

	अगर (!is_hal_stop(rtlhal)) अणु
		चयन (operation) अणु
		हाल SCAN_OPT_BACKUP_BAND0:
			iotype = IO_CMD_PAUSE_BAND0_DM_BY_SCAN;
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_IO_CMD,
						      (u8 *)&iotype);

			अवरोध;
		हाल SCAN_OPT_BACKUP_BAND1:
			iotype = IO_CMD_PAUSE_BAND1_DM_BY_SCAN;
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_IO_CMD,
						      (u8 *)&iotype);

			अवरोध;
		हाल SCAN_OPT_RESTORE:
			iotype = IO_CMD_RESUME_DM_BY_SCAN;
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_IO_CMD,
						      (u8 *)&iotype);
			अवरोध;
		शेष:
			pr_err("Unknown Scan Backup operation.\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_phy_set_reg_bw(काष्ठा rtl_priv *rtlpriv, u8 bw)
अणु
	u16 reg_rf_mode_bw, पंचांगp = 0;

	reg_rf_mode_bw = rtl_पढ़ो_word(rtlpriv, REG_TRXPTCL_CTL);
	चयन (bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl_ग_लिखो_word(rtlpriv, REG_TRXPTCL_CTL, reg_rf_mode_bw & 0xFE7F);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		पंचांगp = reg_rf_mode_bw | BIT(7);
		rtl_ग_लिखो_word(rtlpriv, REG_TRXPTCL_CTL, पंचांगp & 0xFEFF);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_80:
		पंचांगp = reg_rf_mode_bw | BIT(8);
		rtl_ग_लिखो_word(rtlpriv, REG_TRXPTCL_CTL, पंचांगp & 0xFF7F);
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING, "unknown Bandwidth: 0x%x\n", bw);
		अवरोध;
	पूर्ण
पूर्ण

अटल u8 _rtl8821ae_phy_get_secondary_chnl(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	u8 sc_set_40 = 0, sc_set_20 = 0;

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) अणु
		अगर (mac->cur_80_prime_sc == PRIME_CHNL_OFFSET_LOWER)
			sc_set_40 = VHT_DATA_SC_40_LOWER_OF_80MHZ;
		अन्यथा अगर (mac->cur_80_prime_sc == PRIME_CHNL_OFFSET_UPPER)
			sc_set_40 = VHT_DATA_SC_40_UPPER_OF_80MHZ;
		अन्यथा
			pr_err("SCMapping: Not Correct Primary40MHz Setting\n");

		अगर ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_LOWER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER))
			sc_set_20 = VHT_DATA_SC_20_LOWEST_OF_80MHZ;
		अन्यथा अगर ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_UPPER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_LOWER))
			sc_set_20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		अन्यथा अगर ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_LOWER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_UPPER))
			sc_set_20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		अन्यथा अगर ((mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_UPPER) &&
			(mac->cur_80_prime_sc == HAL_PRIME_CHNL_OFFSET_UPPER))
			sc_set_20 = VHT_DATA_SC_20_UPPERST_OF_80MHZ;
		अन्यथा
			pr_err("SCMapping: Not Correct Primary40MHz Setting\n");
	पूर्ण अन्यथा अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
		अगर (mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_UPPER)
			sc_set_20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		अन्यथा अगर (mac->cur_40_prime_sc == PRIME_CHNL_OFFSET_LOWER)
			sc_set_20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		अन्यथा
			pr_err("SCMapping: Not Correct Primary40MHz Setting\n");
	पूर्ण
	वापस (sc_set_40 << 4) | sc_set_20;
पूर्ण

व्योम rtl8821ae_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 sub_chnl = 0;
	u8 l1pk_val = 0;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"Switch to %s bandwidth\n",
		(rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		 "20MHz" :
		 (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40 ?
		  "40MHz" : "80MHz")));

	_rtl8821ae_phy_set_reg_bw(rtlpriv, rtlphy->current_chan_bw);
	sub_chnl = _rtl8821ae_phy_get_secondary_chnl(rtlpriv);
	rtl_ग_लिखो_byte(rtlpriv, 0x0483, sub_chnl);

	चयन (rtlphy->current_chan_bw) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl_set_bbreg(hw, RRFMOD, 0x003003C3, 0x00300200);
		rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 0);

		अगर (rtlphy->rf_type == RF_2T2R)
			rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, 7);
		अन्यथा
			rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, 8);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RRFMOD, 0x003003C3, 0x00300201);
		rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 0);
		rtl_set_bbreg(hw, RRFMOD, 0x3C, sub_chnl);
		rtl_set_bbreg(hw, RCCAONSEC, 0xf0000000, sub_chnl);

		अगर (rtlphy->reg_837 & BIT(2))
			l1pk_val = 6;
		अन्यथा अणु
			अगर (rtlphy->rf_type == RF_2T2R)
				l1pk_val = 7;
			अन्यथा
				l1pk_val = 8;
		पूर्ण
		/* 0x848[25:22] = 0x6 */
		rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, l1pk_val);

		अगर (sub_chnl == VHT_DATA_SC_20_UPPER_OF_80MHZ)
			rtl_set_bbreg(hw, RCCK_SYSTEM, BCCK_SYSTEM, 1);
		अन्यथा
			rtl_set_bbreg(hw, RCCK_SYSTEM, BCCK_SYSTEM, 0);
		अवरोध;

	हाल HT_CHANNEL_WIDTH_80:
		 /* 0x8ac[21,20,9:6,1,0]=8'b11100010 */
		rtl_set_bbreg(hw, RRFMOD, 0x003003C3, 0x00300202);
		/* 0x8c4[30] = 1 */
		rtl_set_bbreg(hw, RADC_BUF_CLK, BIT(30), 1);
		rtl_set_bbreg(hw, RRFMOD, 0x3C, sub_chnl);
		rtl_set_bbreg(hw, RCCAONSEC, 0xf0000000, sub_chnl);

		अगर (rtlphy->reg_837 & BIT(2))
			l1pk_val = 5;
		अन्यथा अणु
			अगर (rtlphy->rf_type == RF_2T2R)
				l1pk_val = 6;
			अन्यथा
				l1pk_val = 7;
		पूर्ण
		rtl_set_bbreg(hw, RL1PEAKTH, 0x03C00000, l1pk_val);

		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण

	rtl8812ae_fixspur(hw, rtlphy->current_chan_bw, rtlphy->current_channel);

	rtl8821ae_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD, "\n");
पूर्ण

व्योम rtl8821ae_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp_bw = rtlphy->current_chan_bw;

	अगर (rtlphy->set_bwmode_inprogress)
		वापस;
	rtlphy->set_bwmode_inprogress = true;
	अगर ((!is_hal_stop(rtlhal)) && !(RT_CANNOT_IO(hw)))
		rtl8821ae_phy_set_bw_mode_callback(hw);
	अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"FALSE driver sleep or unload\n");
		rtlphy->set_bwmode_inprogress = false;
		rtlphy->current_chan_bw = पंचांगp_bw;
	पूर्ण
पूर्ण

व्योम rtl8821ae_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 channel = rtlphy->current_channel;
	u8 path;
	u32 data;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"switch to channel%d\n", rtlphy->current_channel);
	अगर (is_hal_stop(rtlhal))
		वापस;

	अगर (36 <= channel && channel <= 48)
		data = 0x494;
	अन्यथा अगर (50 <= channel && channel <= 64)
		data = 0x453;
	अन्यथा अगर (100 <= channel && channel <= 116)
		data = 0x452;
	अन्यथा अगर (118 <= channel)
		data = 0x412;
	अन्यथा
		data = 0x96a;
	rtl_set_bbreg(hw, RFC_AREA, 0x1ffe0000, data);

	क्रम (path = RF90_PATH_A; path < rtlphy->num_total_rfpath; path++) अणु
		अगर (36 <= channel && channel <= 64)
			data = 0x101;
		अन्यथा अगर (100 <= channel && channel <= 140)
			data = 0x301;
		अन्यथा अगर (140 < channel)
			data = 0x501;
		अन्यथा
			data = 0x000;
		rtl8821ae_phy_set_rf_reg(hw, path, RF_CHNLBW,
			BIT(18)|BIT(17)|BIT(16)|BIT(9)|BIT(8), data);

		rtl8821ae_phy_set_rf_reg(hw, path, RF_CHNLBW,
			BMASKBYTE0, channel);

		अगर (channel > 14) अणु
			अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
				अगर (36 <= channel && channel <= 64)
					data = 0x114E9;
				अन्यथा
					data = 0x110E9;
				rtl8821ae_phy_set_rf_reg(hw, path, RF_APK,
					BRFREGOFFSETMASK, data);
			पूर्ण
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "\n");
पूर्ण

u8 rtl8821ae_phy_sw_chnl(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 समयout = 1000, समयcount = 0;
	u8 channel = rtlphy->current_channel;

	अगर (rtlphy->sw_chnl_inprogress)
		वापस 0;
	अगर (rtlphy->set_bwmode_inprogress)
		वापस 0;

	अगर ((is_hal_stop(rtlhal)) || (RT_CANNOT_IO(hw))) अणु
		rtl_dbg(rtlpriv, COMP_CHAN, DBG_LOUD,
			"sw_chnl_inprogress false driver sleep or unload\n");
		वापस 0;
	पूर्ण
	जबतक (rtlphy->lck_inprogress && समयcount < समयout) अणु
		mdelay(50);
		समयcount += 50;
	पूर्ण

	अगर (rtlphy->current_channel > 14 && rtlhal->current_bandtype != BAND_ON_5G)
		rtl8821ae_phy_चयन_wirelessband(hw, BAND_ON_5G);
	अन्यथा अगर (rtlphy->current_channel <= 14 && rtlhal->current_bandtype != BAND_ON_2_4G)
		rtl8821ae_phy_चयन_wirelessband(hw, BAND_ON_2_4G);

	rtlphy->sw_chnl_inprogress = true;
	अगर (channel == 0)
		channel = 1;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"switch to channel%d, band type is %d\n",
		rtlphy->current_channel, rtlhal->current_bandtype);

	rtl8821ae_phy_sw_chnl_callback(hw);

	rtl8821ae_dm_clear_txघातer_tracking_state(hw);
	rtl8821ae_phy_set_txघातer_level(hw, rtlphy->current_channel);

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "\n");
	rtlphy->sw_chnl_inprogress = false;
	वापस 1;
पूर्ण

u8 _rtl8812ae_get_right_chnl_place_क्रम_iqk(u8 chnl)
अणु
	अटल स्थिर u8 channel_all[TARGET_CHNL_NUM_2G_5G_8812] = अणु
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
		14, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54,
		56, 58, 60, 62, 64, 100, 102, 104, 106, 108,
		110, 112, 114, 116, 118, 120, 122, 124, 126,
		128, 130, 132, 134, 136, 138, 140, 149, 151,
		153, 155, 157, 159, 161, 163, 165पूर्ण;
	u8 place;

	अगर (chnl > 14) अणु
		क्रम (place = 14; place < माप(channel_all); place++)
			अगर (channel_all[place] == chnl)
				वापस place-13;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा MACBB_REG_NUM 10
#घोषणा AFE_REG_NUM 14
#घोषणा RF_REG_NUM 3

अटल व्योम _rtl8821ae_iqk_backup_macbb(काष्ठा ieee80211_hw *hw,
					u32 *macbb_backup,
					u32 *backup_macbb_reg, u32 mac_bb_num)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
	/*save MACBB शेष value*/
	क्रम (i = 0; i < mac_bb_num; i++)
		macbb_backup[i] = rtl_पढ़ो_dword(rtlpriv, backup_macbb_reg[i]);

	rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "BackupMacBB Success!!!!\n");
पूर्ण

अटल व्योम _rtl8821ae_iqk_backup_afe(काष्ठा ieee80211_hw *hw, u32 *afe_backup,
				      u32 *backup_afe_REG, u32 afe_num)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
	/*Save AFE Parameters */
	क्रम (i = 0; i < afe_num; i++)
		afe_backup[i] = rtl_पढ़ो_dword(rtlpriv, backup_afe_REG[i]);
	rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "BackupAFE Success!!!!\n");
पूर्ण

अटल व्योम _rtl8821ae_iqk_backup_rf(काष्ठा ieee80211_hw *hw, u32 *rfa_backup,
				     u32 *rfb_backup, u32 *backup_rf_reg,
				     u32 rf_num)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
	/*Save RF Parameters*/
	क्रम (i = 0; i < rf_num; i++) अणु
		rfa_backup[i] = rtl_get_rfreg(hw, RF90_PATH_A, backup_rf_reg[i],
					      BMASKDWORD);
		rfb_backup[i] = rtl_get_rfreg(hw, RF90_PATH_B, backup_rf_reg[i],
					      BMASKDWORD);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "BackupRF Success!!!!\n");
पूर्ण

अटल व्योम _rtl8821ae_iqk_configure_mac(
		काष्ठा ieee80211_hw *hw
		)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	/* ========MAC रेजिस्टर setting========*/
	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
	rtl_ग_लिखो_byte(rtlpriv, 0x522, 0x3f);
	rtl_set_bbreg(hw, 0x550, BIT(11) | BIT(3), 0x0);
	rtl_ग_लिखो_byte(rtlpriv, 0x808, 0x00);		/*RX ante off*/
	rtl_set_bbreg(hw, 0x838, 0xf, 0xc);		/*CCA off*/
पूर्ण

अटल व्योम _rtl8821ae_iqk_tx_fill_iqc(काष्ठा ieee80211_hw *hw,
				       क्रमागत radio_path path, u32 tx_x, u32 tx_y)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	चयन (path) अणु
	हाल RF90_PATH_A:
		/* [31] = 1 --> Page C1 */
		rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1);
		rtl_ग_लिखो_dword(rtlpriv, 0xc90, 0x00000080);
		rtl_ग_लिखो_dword(rtlpriv, 0xcc4, 0x20040000);
		rtl_ग_लिखो_dword(rtlpriv, 0xcc8, 0x20000000);
		rtl_set_bbreg(hw, 0xccc, 0x000007ff, tx_y);
		rtl_set_bbreg(hw, 0xcd4, 0x000007ff, tx_x);
		rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
			"TX_X = %x;;TX_Y = %x =====> fill to IQC\n",
			tx_x, tx_y);
		rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
			"0xcd4 = %x;;0xccc = %x ====>fill to IQC\n",
			rtl_get_bbreg(hw, 0xcd4, 0x000007ff),
			rtl_get_bbreg(hw, 0xccc, 0x000007ff));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_iqk_rx_fill_iqc(काष्ठा ieee80211_hw *hw,
				       क्रमागत radio_path path, u32 rx_x, u32 rx_y)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	चयन (path) अणु
	हाल RF90_PATH_A:
		rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
		rtl_set_bbreg(hw, 0xc10, 0x000003ff, rx_x>>1);
		rtl_set_bbreg(hw, 0xc10, 0x03ff0000, rx_y>>1);
		rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
			"rx_x = %x;;rx_y = %x ====>fill to IQC\n",
			rx_x >> 1, rx_y >> 1);
		rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
			"0xc10 = %x ====>fill to IQC\n",
			rtl_पढ़ो_dword(rtlpriv, 0xc10));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा cal_num 10

अटल व्योम _rtl8821ae_iqk_tx(काष्ठा ieee80211_hw *hw, क्रमागत radio_path path)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u32	tx_fail, rx_fail, delay_count, iqk_पढ़ोy, cal_retry, cal = 0, temp_reg65;
	पूर्णांक	tx_x = 0, tx_y = 0, rx_x = 0, rx_y = 0, tx_average = 0, rx_average = 0;
	पूर्णांक	tx_x0[cal_num], tx_y0[cal_num], tx_x0_rxk[cal_num],
		tx_y0_rxk[cal_num], rx_x0[cal_num], rx_y0[cal_num],
		tx_dt[cal_num], rx_dt[cal_num];
	bool	tx0iqkok = false, rx0iqkok = false;
	bool	vdf_enable = false;
	पूर्णांक	i, k, vdf_y[3], vdf_x[3],
		ii, dx = 0, dy = 0, tx_finish = 0, rx_finish = 0;

	rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
		"BandWidth = %d.\n",
		rtlphy->current_chan_bw);
	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80)
		vdf_enable = true;

	जबतक (cal < cal_num) अणु
		चयन (path) अणु
		हाल RF90_PATH_A:
			temp_reg65 = rtl_get_rfreg(hw, path, 0x65, 0xffffffff);
			/* Path-A LOK */
			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /*[31] = 0 --> Page C*/
			/*========Path-A AFE all on========*/
			/*Port 0 DAC/ADC on*/
			rtl_ग_लिखो_dword(rtlpriv, 0xc60, 0x77777777);
			rtl_ग_लिखो_dword(rtlpriv, 0xc64, 0x77777777);
			rtl_ग_लिखो_dword(rtlpriv, 0xc68, 0x19791979);
			rtl_ग_लिखो_dword(rtlpriv, 0xc6c, 0x19791979);
			rtl_ग_लिखो_dword(rtlpriv, 0xc70, 0x19791979);
			rtl_ग_लिखो_dword(rtlpriv, 0xc74, 0x19791979);
			rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x19791979);
			rtl_ग_लिखो_dword(rtlpriv, 0xc7c, 0x19791979);
			rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x19791979);
			rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x19791979);

			rtl_set_bbreg(hw, 0xc00, 0xf, 0x4); /*hardware 3-wire off*/

			/* LOK Setting */
			/* ====== LOK ====== */
			/*DAC/ADC sampling rate (160 MHz)*/
			rtl_set_bbreg(hw, 0xc5c, BIT(26) | BIT(25) | BIT(24), 0x7);

			/* 2. LoK RF Setting (at BW = 20M) */
			rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80002);
			rtl_set_rfreg(hw, path, 0x18, 0x00c00, 0x3);     /* BW 20M */
			rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x20000);
			rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0003f);
			rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xf3fc3);
			rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d5);
			rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
			rtl_set_bbreg(hw, 0xcb8, 0xf, 0xd);
			rtl_ग_लिखो_dword(rtlpriv, 0x90c, 0x00008000);
			rtl_ग_लिखो_dword(rtlpriv, 0xb00, 0x03000100);
			rtl_set_bbreg(hw, 0xc94, BIT(0), 0x1);
			rtl_ग_लिखो_dword(rtlpriv, 0x978, 0x29002000);/* TX (X,Y) */
			rtl_ग_लिखो_dword(rtlpriv, 0x97c, 0xa9002000);/* RX (X,Y) */
			rtl_ग_लिखो_dword(rtlpriv, 0x984, 0x00462910);/* [0]:AGC_en, [15]:idac_K_Mask */

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
			rtl_ग_लिखो_dword(rtlpriv, 0xc88, 0x821403f4);

			अगर (rtlhal->current_bandtype)
				rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x68163e96);
			अन्यथा
				rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x28163e96);

			rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x18008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
			rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x38008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
			rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8रआ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
			rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xfa000000);
			rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xf8000000);

			mdelay(10); /* Delay 10ms */
			rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00000000);

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
			rtl_set_rfreg(hw, path, 0x58, 0x7fe00, rtl_get_rfreg(hw, path, 0x8, 0xffc00)); /* Load LOK */

			चयन (rtlphy->current_chan_bw) अणु
			हाल 1:
				rtl_set_rfreg(hw, path, 0x18, 0x00c00, 0x1);
				अवरोध;
			हाल 2:
				rtl_set_rfreg(hw, path, 0x18, 0x00c00, 0x0);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */

			/* 3. TX RF Setting */
			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
			rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
			rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x20000);
			rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0003f);
			rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xf3fc3);
			rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d5);
			rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
			rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);
			/* ODM_SetBBReg(pDM_Odm, 0xcb8, 0xf, 0xd); */
			rtl_ग_लिखो_dword(rtlpriv, 0x90c, 0x00008000);
			rtl_ग_लिखो_dword(rtlpriv, 0xb00, 0x03000100);
			rtl_set_bbreg(hw, 0xc94, BIT(0), 0x1);
			rtl_ग_लिखो_dword(rtlpriv, 0x978, 0x29002000);/* TX (X,Y) */
			rtl_ग_लिखो_dword(rtlpriv, 0x97c, 0xa9002000);/* RX (X,Y) */
			rtl_ग_लिखो_dword(rtlpriv, 0x984, 0x0046a910);/* [0]:AGC_en, [15]:idac_K_Mask */

			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
			rtl_ग_लिखो_dword(rtlpriv, 0xc88, 0x821403f1);
			अगर (rtlhal->current_bandtype)
				rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x40163e96);
			अन्यथा
				rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x00163e96);

			अगर (vdf_enable) अणु
				rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "VDF_enable\n");
				क्रम (k = 0; k <= 2; k++) अणु
					चयन (k) अणु
					हाल 0:
						rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x18008c38);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
						rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x38008c38);/* RX_TONE_idx[9:0], RxK_Mask[29] */
						rtl_set_bbreg(hw, 0xce8, BIT(31), 0x0);
						अवरोध;
					हाल 1:
						rtl_set_bbreg(hw, 0xc80, BIT(28), 0x0);
						rtl_set_bbreg(hw, 0xc84, BIT(28), 0x0);
						rtl_set_bbreg(hw, 0xce8, BIT(31), 0x0);
						अवरोध;
					हाल 2:
						rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
							"vdf_y[1] = %x;;;vdf_y[0] = %x\n", vdf_y[1]>>21 & 0x00007ff, vdf_y[0]>>21 & 0x00007ff);
						rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
							"vdf_x[1] = %x;;;vdf_x[0] = %x\n", vdf_x[1]>>21 & 0x00007ff, vdf_x[0]>>21 & 0x00007ff);
						tx_dt[cal] = (vdf_y[1]>>20)-(vdf_y[0]>>20);
						tx_dt[cal] = ((16*tx_dt[cal])*10000/15708);
						tx_dt[cal] = (tx_dt[cal] >> 1)+(tx_dt[cal] & BIT(0));
						rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x18008c20);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
						rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x38008c20);/* RX_TONE_idx[9:0], RxK_Mask[29] */
						rtl_set_bbreg(hw, 0xce8, BIT(31), 0x1);
						rtl_set_bbreg(hw, 0xce8, 0x3fff0000, tx_dt[cal] & 0x00003fff);
						अवरोध;
					शेष:
						अवरोध;
					पूर्ण
					rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8रआ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
					cal_retry = 0;
					जबतक (1) अणु
						/* one shot */
						rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xfa000000);
						rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xf8000000);

						mdelay(10); /* Delay 10ms */
						rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00000000);
						delay_count = 0;
						जबतक (1) अणु
							iqk_पढ़ोy = rtl_get_bbreg(hw, 0xd00, BIT(10));
							अगर ((~iqk_पढ़ोy) || (delay_count > 20))
								अवरोध;
							अन्यथाअणु
								mdelay(1);
								delay_count++;
							पूर्ण
						पूर्ण

						अगर (delay_count < 20) अणु							/* If 20ms No Result, then cal_retry++ */
							/* ============TXIQK Check============== */
							tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

							अगर (~tx_fail) अणु
								rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x02000000);
								vdf_x[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x04000000);
								vdf_y[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								tx0iqkok = true;
								अवरोध;
							पूर्ण अन्यथा अणु
								rtl_set_bbreg(hw, 0xccc, 0x000007ff, 0x0);
								rtl_set_bbreg(hw, 0xcd4, 0x000007ff, 0x200);
								tx0iqkok = false;
								cal_retry++;
								अगर (cal_retry == 10)
									अवरोध;
							पूर्ण
						पूर्ण अन्यथा अणु
							tx0iqkok = false;
							cal_retry++;
							अगर (cal_retry == 10)
								अवरोध;
						पूर्ण
					पूर्ण
				पूर्ण
				अगर (k == 3) अणु
					tx_x0[cal] = vdf_x[k-1];
					tx_y0[cal] = vdf_y[k-1];
				पूर्ण
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x18008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
				rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x38008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
				rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8रआ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
				cal_retry = 0;
				जबतक (1) अणु
					/* one shot */
					rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xfa000000);
					rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xf8000000);

					mdelay(10); /* Delay 10ms */
					rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00000000);
					delay_count = 0;
					जबतक (1) अणु
						iqk_पढ़ोy = rtl_get_bbreg(hw, 0xd00, BIT(10));
						अगर ((~iqk_पढ़ोy) || (delay_count > 20))
							अवरोध;
						अन्यथाअणु
							mdelay(1);
							delay_count++;
						पूर्ण
					पूर्ण

					अगर (delay_count < 20) अणु							/* If 20ms No Result, then cal_retry++ */
						/* ============TXIQK Check============== */
						tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

						अगर (~tx_fail) अणु
							rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x02000000);
							tx_x0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x04000000);
							tx_y0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							tx0iqkok = true;
							अवरोध;
						पूर्ण अन्यथा अणु
							rtl_set_bbreg(hw, 0xccc, 0x000007ff, 0x0);
							rtl_set_bbreg(hw, 0xcd4, 0x000007ff, 0x200);
							tx0iqkok = false;
							cal_retry++;
							अगर (cal_retry == 10)
								अवरोध;
						पूर्ण
					पूर्ण अन्यथा अणु
						tx0iqkok = false;
						cal_retry++;
						अगर (cal_retry == 10)
							अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (!tx0iqkok)
				अवरोध;				/* TXK fail, Don't करो RXK */

			अगर (vdf_enable == 1) अणु
				rtl_set_bbreg(hw, 0xce8, BIT(31), 0x0);    /* TX VDF Disable */
				rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "RXVDF Start\n");
				क्रम (k = 0; k <= 2; k++) अणु
					/* ====== RX mode TXK (RXK Step 1) ====== */
					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
					/* 1. TX RF Setting */
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
					rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
					rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x00029);
					rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xd7ffb);
					rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, temp_reg65);
					rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);

					rtl_set_bbreg(hw, 0xcb8, 0xf, 0xd);
					rtl_ग_लिखो_dword(rtlpriv, 0x978, 0x29002000);/* TX (X,Y) */
					rtl_ग_लिखो_dword(rtlpriv, 0x97c, 0xa9002000);/* RX (X,Y) */
					rtl_ग_लिखो_dword(rtlpriv, 0x984, 0x0046a910);/* [0]:AGC_en, [15]:idac_K_Mask */
					rtl_ग_लिखो_dword(rtlpriv, 0x90c, 0x00008000);
					rtl_ग_लिखो_dword(rtlpriv, 0xb00, 0x03000100);
					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
					चयन (k) अणु
					हाल 0:
						अणु
							rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x18008c38);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
							rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x38008c38);/* RX_TONE_idx[9:0], RxK_Mask[29] */
							rtl_set_bbreg(hw, 0xce8, BIT(30), 0x0);
						पूर्ण
						अवरोध;
					हाल 1:
						अणु
							rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x08008c38);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
							rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x28008c38);/* RX_TONE_idx[9:0], RxK_Mask[29] */
							rtl_set_bbreg(hw, 0xce8, BIT(30), 0x0);
						पूर्ण
						अवरोध;
					हाल 2:
						अणु
							rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
								"VDF_Y[1] = %x;;;VDF_Y[0] = %x\n",
								vdf_y[1] >> 21 & 0x00007ff,
								vdf_y[0] >> 21 & 0x00007ff);
							rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
								"VDF_X[1] = %x;;;VDF_X[0] = %x\n",
								vdf_x[1] >> 21 & 0x00007ff,
								vdf_x[0] >> 21 & 0x00007ff);
							rx_dt[cal] = (vdf_y[1]>>20)-(vdf_y[0]>>20);
							rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "Rx_dt = %d\n",
								rx_dt[cal]);
							rx_dt[cal] = ((16*rx_dt[cal])*10000/13823);
							rx_dt[cal] = (rx_dt[cal] >> 1)+(rx_dt[cal] & BIT(0));
							rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x18008c20);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
							rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x38008c20);/* RX_TONE_idx[9:0], RxK_Mask[29] */
							rtl_set_bbreg(hw, 0xce8, 0x00003fff, rx_dt[cal] & 0x00003fff);
						पूर्ण
						अवरोध;
					शेष:
						अवरोध;
					पूर्ण
					rtl_ग_लिखो_dword(rtlpriv, 0xc88, 0x821603e0);
					rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x68163e96);
					rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8रआ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
					cal_retry = 0;
					जबतक (1) अणु
						/* one shot */
						rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xfa000000);
						rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xf8000000);

						mdelay(10); /* Delay 10ms */
						rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00000000);
						delay_count = 0;
						जबतक (1) अणु
							iqk_पढ़ोy = rtl_get_bbreg(hw, 0xd00, BIT(10));
							अगर ((~iqk_पढ़ोy) || (delay_count > 20))
								अवरोध;
							अन्यथाअणु
								mdelay(1);
								delay_count++;
							पूर्ण
						पूर्ण

						अगर (delay_count < 20) अणु							/* If 20ms No Result, then cal_retry++ */
							/* ============TXIQK Check============== */
							tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

							अगर (~tx_fail) अणु
								rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x02000000);
								tx_x0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x04000000);
								tx_y0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								tx0iqkok = true;
								अवरोध;
							पूर्ण अन्यथाअणु
								tx0iqkok = false;
								cal_retry++;
								अगर (cal_retry == 10)
									अवरोध;
							पूर्ण
						पूर्ण अन्यथा अणु
							tx0iqkok = false;
							cal_retry++;
							अगर (cal_retry == 10)
								अवरोध;
						पूर्ण
					पूर्ण

					अगर (!tx0iqkok) अणु   /* If RX mode TXK fail, then take TXK Result */
						tx_x0_rxk[cal] = tx_x0[cal];
						tx_y0_rxk[cal] = tx_y0[cal];
						tx0iqkok = true;
						rtl_dbg(rtlpriv,
							COMP_IQK,
							DBG_LOUD,
							"RXK Step 1 fail\n");
					पूर्ण

					/* ====== RX IQK ====== */
					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
					/* 1. RX RF Setting */
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
					rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
					rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0002f);
					rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xfffbb);
					rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x88001);
					rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d8);
					rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);

					rtl_set_bbreg(hw, 0x978, 0x03FF8000, (tx_x0_rxk[cal])>>21&0x000007ff);
					rtl_set_bbreg(hw, 0x978, 0x000007FF, (tx_y0_rxk[cal])>>21&0x000007ff);
					rtl_set_bbreg(hw, 0x978, BIT(31), 0x1);
					rtl_set_bbreg(hw, 0x97c, BIT(31), 0x0);
					rtl_set_bbreg(hw, 0xcb8, 0xF, 0xe);
					rtl_ग_लिखो_dword(rtlpriv, 0x90c, 0x00008000);
					rtl_ग_लिखो_dword(rtlpriv, 0x984, 0x0046a911);

					rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
					rtl_set_bbreg(hw, 0xc80, BIT(29), 0x1);
					rtl_set_bbreg(hw, 0xc84, BIT(29), 0x0);
					rtl_ग_लिखो_dword(rtlpriv, 0xc88, 0x02140119);

					rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x28160d00); /* pDM_Odm->SupportInterface == 1 */

					अगर (k == 2)
						rtl_set_bbreg(hw, 0xce8, BIT(30), 0x1);  /* RX VDF Enable */
					rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8रआ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */

					cal_retry = 0;
					जबतक (1) अणु
						/* one shot */
						rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xfa000000);
						rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xf8000000);

						mdelay(10); /* Delay 10ms */
						rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00000000);
						delay_count = 0;
						जबतक (1) अणु
							iqk_पढ़ोy = rtl_get_bbreg(hw, 0xd00, BIT(10));
							अगर ((~iqk_पढ़ोy) || (delay_count > 20))
								अवरोध;
							अन्यथाअणु
								mdelay(1);
								delay_count++;
							पूर्ण
						पूर्ण

						अगर (delay_count < 20) अणु	/* If 20ms No Result, then cal_retry++ */
							/* ============RXIQK Check============== */
							rx_fail = rtl_get_bbreg(hw, 0xd00, BIT(11));
							अगर (rx_fail == 0) अणु
								rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x06000000);
								vdf_x[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x08000000);
								vdf_y[k] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
								rx0iqkok = true;
								अवरोध;
							पूर्ण अन्यथा अणु
								rtl_set_bbreg(hw, 0xc10, 0x000003ff, 0x200>>1);
								rtl_set_bbreg(hw, 0xc10, 0x03ff0000, 0x0>>1);
								rx0iqkok = false;
								cal_retry++;
								अगर (cal_retry == 10)
									अवरोध;

							पूर्ण
						पूर्ण अन्यथाअणु
							rx0iqkok = false;
							cal_retry++;
							अगर (cal_retry == 10)
								अवरोध;
						पूर्ण
					पूर्ण

				पूर्ण
				अगर (k == 3) अणु
					rx_x0[cal] = vdf_x[k-1];
					rx_y0[cal] = vdf_y[k-1];
				पूर्ण
				rtl_set_bbreg(hw, 0xce8, BIT(31), 0x1);    /* TX VDF Enable */
			पूर्ण

			अन्यथाअणु
				/* ====== RX mode TXK (RXK Step 1) ====== */
				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
				/* 1. TX RF Setting */
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
				rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
				rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x00029);
				rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xd7ffb);
				rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, temp_reg65);
				rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x8a001);
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);
				rtl_ग_लिखो_dword(rtlpriv, 0x90c, 0x00008000);
				rtl_ग_लिखो_dword(rtlpriv, 0xb00, 0x03000100);
				rtl_ग_लिखो_dword(rtlpriv, 0x984, 0x0046a910);/* [0]:AGC_en, [15]:idac_K_Mask */

				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
				rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x18008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
				rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x38008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
				rtl_ग_लिखो_dword(rtlpriv, 0xc88, 0x821603e0);
				/* ODM_Write4Byte(pDM_Odm, 0xc8c, 0x68163e96); */
				rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8रआ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */
				cal_retry = 0;
				जबतक (1) अणु
					/* one shot */
					rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xfa000000);
					rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xf8000000);

					mdelay(10); /* Delay 10ms */
					rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00000000);
					delay_count = 0;
					जबतक (1) अणु
						iqk_पढ़ोy = rtl_get_bbreg(hw, 0xd00, BIT(10));
						अगर ((~iqk_पढ़ोy) || (delay_count > 20))
							अवरोध;
						अन्यथाअणु
							mdelay(1);
							delay_count++;
						पूर्ण
					पूर्ण

					अगर (delay_count < 20) अणु							/* If 20ms No Result, then cal_retry++ */
						/* ============TXIQK Check============== */
						tx_fail = rtl_get_bbreg(hw, 0xd00, BIT(12));

						अगर (~tx_fail) अणु
							rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x02000000);
							tx_x0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x04000000);
							tx_y0_rxk[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							tx0iqkok = true;
							अवरोध;
						पूर्ण अन्यथा अणु
							tx0iqkok = false;
							cal_retry++;
							अगर (cal_retry == 10)
								अवरोध;
						पूर्ण
					पूर्ण अन्यथाअणु
						tx0iqkok = false;
						cal_retry++;
						अगर (cal_retry == 10)
							अवरोध;
					पूर्ण
				पूर्ण

				अगर (!tx0iqkok) अणु   /* If RX mode TXK fail, then take TXK Result */
					tx_x0_rxk[cal] = tx_x0[cal];
					tx_y0_rxk[cal] = tx_y0[cal];
					tx0iqkok = true;
					rtl_dbg(rtlpriv, COMP_IQK,
						DBG_LOUD, "1");
				पूर्ण

				/* ====== RX IQK ====== */
				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
				/* 1. RX RF Setting */
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x80000);
				rtl_set_rfreg(hw, path, 0x30, RFREG_OFFSET_MASK, 0x30000);
				rtl_set_rfreg(hw, path, 0x31, RFREG_OFFSET_MASK, 0x0002f);
				rtl_set_rfreg(hw, path, 0x32, RFREG_OFFSET_MASK, 0xfffbb);
				rtl_set_rfreg(hw, path, 0x8f, RFREG_OFFSET_MASK, 0x88001);
				rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, 0x931d8);
				rtl_set_rfreg(hw, path, 0xef, RFREG_OFFSET_MASK, 0x00000);

				rtl_set_bbreg(hw, 0x978, 0x03FF8000, (tx_x0_rxk[cal])>>21&0x000007ff);
				rtl_set_bbreg(hw, 0x978, 0x000007FF, (tx_y0_rxk[cal])>>21&0x000007ff);
				rtl_set_bbreg(hw, 0x978, BIT(31), 0x1);
				rtl_set_bbreg(hw, 0x97c, BIT(31), 0x0);
				/* ODM_SetBBReg(pDM_Odm, 0xcb8, 0xF, 0xe); */
				rtl_ग_लिखो_dword(rtlpriv, 0x90c, 0x00008000);
				rtl_ग_लिखो_dword(rtlpriv, 0x984, 0x0046a911);

				rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
				rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x38008c10);/* TX_TONE_idx[9:0], TxK_Mask[29] TX_Tone = 16 */
				rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x18008c10);/* RX_TONE_idx[9:0], RxK_Mask[29] */
				rtl_ग_लिखो_dword(rtlpriv, 0xc88, 0x02140119);

				rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x28160d00); /*pDM_Odm->SupportInterface == 1*/

				rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00100000);/* cb8[20] \B1N SI/PI \A8रआ\CE\C5v\A4\C1\B5\B9 iqk_dpk module */

				cal_retry = 0;
				जबतक (1) अणु
					/* one shot */
					rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xfa000000);
					rtl_ग_लिखो_dword(rtlpriv, 0x980, 0xf8000000);

					mdelay(10); /* Delay 10ms */
					rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x00000000);
					delay_count = 0;
					जबतक (1) अणु
						iqk_पढ़ोy = rtl_get_bbreg(hw, 0xd00, BIT(10));
						अगर ((~iqk_पढ़ोy) || (delay_count > 20))
							अवरोध;
						अन्यथाअणु
							mdelay(1);
							delay_count++;
						पूर्ण
					पूर्ण

					अगर (delay_count < 20) अणु	/* If 20ms No Result, then cal_retry++ */
						/* ============RXIQK Check============== */
						rx_fail = rtl_get_bbreg(hw, 0xd00, BIT(11));
						अगर (rx_fail == 0) अणु
							rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x06000000);
							rx_x0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x08000000);
							rx_y0[cal] = rtl_get_bbreg(hw, 0xd00, 0x07ff0000)<<21;
							rx0iqkok = true;
							अवरोध;
						पूर्ण अन्यथाअणु
							rtl_set_bbreg(hw, 0xc10, 0x000003ff, 0x200>>1);
							rtl_set_bbreg(hw, 0xc10, 0x03ff0000, 0x0>>1);
							rx0iqkok = false;
							cal_retry++;
							अगर (cal_retry == 10)
								अवरोध;

						पूर्ण
					पूर्ण अन्यथाअणु
						rx0iqkok = false;
						cal_retry++;
						अगर (cal_retry == 10)
							अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			अगर (tx0iqkok)
				tx_average++;
			अगर (rx0iqkok)
				rx_average++;
			rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
			rtl_set_rfreg(hw, path, 0x65, RFREG_OFFSET_MASK, temp_reg65);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		cal++;
	पूर्ण

	/* FillIQK Result */
	चयन (path) अणु
	हाल RF90_PATH_A:
		rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
			"========Path_A =======\n");
		अगर (tx_average == 0)
			अवरोध;

		क्रम (i = 0; i < tx_average; i++) अणु
			rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
				"TX_X0_RXK[%d] = %x ;; TX_Y0_RXK[%d] = %x\n", i,
				(tx_x0_rxk[i]) >> 21 & 0x000007ff, i,
				(tx_y0_rxk[i]) >> 21 & 0x000007ff);
			rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
				"TX_X0[%d] = %x ;; TX_Y0[%d] = %x\n", i,
				(tx_x0[i]) >> 21 & 0x000007ff, i,
				(tx_y0[i]) >> 21 & 0x000007ff);
		पूर्ण
		क्रम (i = 0; i < tx_average; i++) अणु
			क्रम (ii = i+1; ii < tx_average; ii++) अणु
				dx = (tx_x0[i]>>21) - (tx_x0[ii]>>21);
				अगर (dx < 3 && dx > -3) अणु
					dy = (tx_y0[i]>>21) - (tx_y0[ii]>>21);
					अगर (dy < 3 && dy > -3) अणु
						tx_x = ((tx_x0[i]>>21) + (tx_x0[ii]>>21))/2;
						tx_y = ((tx_y0[i]>>21) + (tx_y0[ii]>>21))/2;
						tx_finish = 1;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (tx_finish == 1)
				अवरोध;
		पूर्ण

		अगर (tx_finish == 1)
			_rtl8821ae_iqk_tx_fill_iqc(hw, path, tx_x, tx_y); /* ? */
		अन्यथा
			_rtl8821ae_iqk_tx_fill_iqc(hw, path, 0x200, 0x0);

		अगर (rx_average == 0)
			अवरोध;

		क्रम (i = 0; i < rx_average; i++)
			rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
				"RX_X0[%d] = %x ;; RX_Y0[%d] = %x\n", i,
				(rx_x0[i])>>21&0x000007ff, i,
				(rx_y0[i])>>21&0x000007ff);
		क्रम (i = 0; i < rx_average; i++) अणु
			क्रम (ii = i+1; ii < rx_average; ii++) अणु
				dx = (rx_x0[i]>>21) - (rx_x0[ii]>>21);
				अगर (dx < 4 && dx > -4) अणु
					dy = (rx_y0[i]>>21) - (rx_y0[ii]>>21);
					अगर (dy < 4 && dy > -4) अणु
						rx_x = ((rx_x0[i]>>21) + (rx_x0[ii]>>21))/2;
						rx_y = ((rx_y0[i]>>21) + (rx_y0[ii]>>21))/2;
						rx_finish = 1;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (rx_finish == 1)
				अवरोध;
		पूर्ण

		अगर (rx_finish == 1)
			_rtl8821ae_iqk_rx_fill_iqc(hw, path, rx_x, rx_y);
		अन्यथा
			_rtl8821ae_iqk_rx_fill_iqc(hw, path, 0x200, 0x0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_iqk_restore_rf(काष्ठा ieee80211_hw *hw,
				      क्रमागत radio_path path,
				      u32 *backup_rf_reg,
				      u32 *rf_backup, u32 rf_reg_num)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
	क्रम (i = 0; i < RF_REG_NUM; i++)
		rtl_set_rfreg(hw, path, backup_rf_reg[i], RFREG_OFFSET_MASK,
			      rf_backup[i]);

	चयन (path) अणु
	हाल RF90_PATH_A:
		rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
			"RestoreRF Path A Success!!!!\n");
		अवरोध;
	शेष:
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_iqk_restore_afe(काष्ठा ieee80211_hw *hw,
				       u32 *afe_backup, u32 *backup_afe_reg,
				       u32 afe_num)
अणु
	u32 i;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
	/* Reload AFE Parameters */
	क्रम (i = 0; i < afe_num; i++)
		rtl_ग_लिखो_dword(rtlpriv, backup_afe_reg[i], afe_backup[i]);
	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x1); /* [31] = 1 --> Page C1 */
	rtl_ग_लिखो_dword(rtlpriv, 0xc80, 0x0);
	rtl_ग_लिखो_dword(rtlpriv, 0xc84, 0x0);
	rtl_ग_लिखो_dword(rtlpriv, 0xc88, 0x0);
	rtl_ग_लिखो_dword(rtlpriv, 0xc8c, 0x3c000000);
	rtl_ग_लिखो_dword(rtlpriv, 0xc90, 0x00000080);
	rtl_ग_लिखो_dword(rtlpriv, 0xc94, 0x00000000);
	rtl_ग_लिखो_dword(rtlpriv, 0xcc4, 0x20040000);
	rtl_ग_लिखो_dword(rtlpriv, 0xcc8, 0x20000000);
	rtl_ग_लिखो_dword(rtlpriv, 0xcb8, 0x0);
	rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "RestoreAFE Success!!!!\n");
पूर्ण

अटल व्योम _rtl8821ae_iqk_restore_macbb(काष्ठा ieee80211_hw *hw,
					 u32 *macbb_backup,
					 u32 *backup_macbb_reg,
					 u32 macbb_num)
अणु
	u32 i;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_set_bbreg(hw, 0x82c, BIT(31), 0x0); /* [31] = 0 --> Page C */
	/* Reload MacBB Parameters */
	क्रम (i = 0; i < macbb_num; i++)
		rtl_ग_लिखो_dword(rtlpriv, backup_macbb_reg[i], macbb_backup[i]);
	rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD, "RestoreMacBB Success!!!!\n");
पूर्ण

#अघोषित MACBB_REG_NUM
#अघोषित AFE_REG_NUM
#अघोषित RF_REG_NUM

#घोषणा MACBB_REG_NUM 11
#घोषणा AFE_REG_NUM 12
#घोषणा RF_REG_NUM 3

अटल व्योम _rtl8821ae_phy_iq_calibrate(काष्ठा ieee80211_hw *hw)
अणु
	u32	macbb_backup[MACBB_REG_NUM];
	u32 afe_backup[AFE_REG_NUM];
	u32 rfa_backup[RF_REG_NUM];
	u32 rfb_backup[RF_REG_NUM];
	u32 backup_macbb_reg[MACBB_REG_NUM] = अणु
		0xb00, 0x520, 0x550, 0x808, 0x90c, 0xc00, 0xc50,
		0xe00, 0xe50, 0x838, 0x82c
	पूर्ण;
	u32 backup_afe_reg[AFE_REG_NUM] = अणु
		0xc5c, 0xc60, 0xc64, 0xc68, 0xc6c, 0xc70, 0xc74,
		0xc78, 0xc7c, 0xc80, 0xc84, 0xcb8
	पूर्ण;
	u32	backup_rf_reg[RF_REG_NUM] = अणु0x65, 0x8f, 0x0पूर्ण;

	_rtl8821ae_iqk_backup_macbb(hw, macbb_backup, backup_macbb_reg,
				    MACBB_REG_NUM);
	_rtl8821ae_iqk_backup_afe(hw, afe_backup, backup_afe_reg, AFE_REG_NUM);
	_rtl8821ae_iqk_backup_rf(hw, rfa_backup, rfb_backup, backup_rf_reg,
				 RF_REG_NUM);

	_rtl8821ae_iqk_configure_mac(hw);
	_rtl8821ae_iqk_tx(hw, RF90_PATH_A);
	_rtl8821ae_iqk_restore_rf(hw, RF90_PATH_A, backup_rf_reg, rfa_backup,
				  RF_REG_NUM);

	_rtl8821ae_iqk_restore_afe(hw, afe_backup, backup_afe_reg, AFE_REG_NUM);
	_rtl8821ae_iqk_restore_macbb(hw, macbb_backup, backup_macbb_reg,
				     MACBB_REG_NUM);
पूर्ण

अटल व्योम _rtl8821ae_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool मुख्य)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	/* काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw)); */
	/* काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw)); */
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "\n");

	अगर (मुख्य)
		rtl_set_bbreg(hw, RA_RFE_PINMUX + 4, BIT(29) | BIT(28), 0x1);
	अन्यथा
		rtl_set_bbreg(hw, RA_RFE_PINMUX + 4, BIT(29) | BIT(28), 0x2);
पूर्ण

#अघोषित IQK_ADDA_REG_NUM
#अघोषित IQK_DELAY_TIME

व्योम rtl8812ae_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery)
अणु
पूर्ण

व्योम rtl8812ae_करो_iqk(काष्ठा ieee80211_hw *hw, u8 delta_thermal_index,
		      u8 thermal_value, u8 threshold)
अणु
	काष्ठा rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));

	rtldm->thermalvalue_iqk = thermal_value;
	rtl8812ae_phy_iq_calibrate(hw, false);
पूर्ण

व्योम rtl8821ae_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	अगर (!rtlphy->lck_inprogress) अणु
		spin_lock(&rtlpriv->locks.iqk_lock);
		rtlphy->lck_inprogress = true;
		spin_unlock(&rtlpriv->locks.iqk_lock);

		_rtl8821ae_phy_iq_calibrate(hw);

		spin_lock(&rtlpriv->locks.iqk_lock);
		rtlphy->lck_inprogress = false;
		spin_unlock(&rtlpriv->locks.iqk_lock);
	पूर्ण
पूर्ण

व्योम rtl8821ae_reset_iqk_result(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 i;

	rtl_dbg(rtlpriv, COMP_IQK, DBG_LOUD,
		"rtl8812ae_dm_reset_iqk_result:: settings regs %d default regs %d\n",
		(पूर्णांक)(माप(rtlphy->iqk_matrix) /
		माप(काष्ठा iqk_matrix_regs)),
		IQK_MATRIX_SETTINGS_NUM);

	क्रम (i = 0; i < IQK_MATRIX_SETTINGS_NUM; i++) अणु
		rtlphy->iqk_matrix[i].value[0][0] = 0x100;
		rtlphy->iqk_matrix[i].value[0][2] = 0x100;
		rtlphy->iqk_matrix[i].value[0][4] = 0x100;
		rtlphy->iqk_matrix[i].value[0][6] = 0x100;

		rtlphy->iqk_matrix[i].value[0][1] = 0x0;
		rtlphy->iqk_matrix[i].value[0][3] = 0x0;
		rtlphy->iqk_matrix[i].value[0][5] = 0x0;
		rtlphy->iqk_matrix[i].value[0][7] = 0x0;

		rtlphy->iqk_matrix[i].iqk_करोne = false;
	पूर्ण
पूर्ण

व्योम rtl8821ae_करो_iqk(काष्ठा ieee80211_hw *hw, u8 delta_thermal_index,
		      u8 thermal_value, u8 threshold)
अणु
	काष्ठा rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));

	rtl8821ae_reset_iqk_result(hw);

	rtldm->thermalvalue_iqk = thermal_value;
	rtl8821ae_phy_iq_calibrate(hw, false);
पूर्ण

व्योम rtl8821ae_phy_lc_calibrate(काष्ठा ieee80211_hw *hw)
अणु
पूर्ण

व्योम rtl8821ae_phy_ap_calibrate(काष्ठा ieee80211_hw *hw, s8 delta)
अणु
पूर्ण

व्योम rtl8821ae_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य)
अणु
	_rtl8821ae_phy_set_rfpath_चयन(hw, bमुख्य);
पूर्ण

bool rtl8821ae_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	bool postprocessing = false;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"-->IO Cmd(%#x), set_io_inprogress(%d)\n",
		iotype, rtlphy->set_io_inprogress);
	करो अणु
		चयन (iotype) अणु
		हाल IO_CMD_RESUME_DM_BY_SCAN:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
				"[IO CMD] Resume DM after scan.\n");
			postprocessing = true;
			अवरोध;
		हाल IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		हाल IO_CMD_PAUSE_BAND1_DM_BY_SCAN:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
				"[IO CMD] Pause DM before scan.\n");
			postprocessing = true;
			अवरोध;
		शेष:
			pr_err("switch case %#x not processed\n",
			       iotype);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (false);
	अगर (postprocessing && !rtlphy->set_io_inprogress) अणु
		rtlphy->set_io_inprogress = true;
		rtlphy->current_io_type = iotype;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
	rtl8821ae_phy_set_io(hw);
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE, "IO Type(%#x)\n", iotype);
	वापस true;
पूर्ण

अटल व्योम rtl8821ae_phy_set_io(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"--->Cmd(%#x), set_io_inprogress(%d)\n",
		rtlphy->current_io_type, rtlphy->set_io_inprogress);
	चयन (rtlphy->current_io_type) अणु
	हाल IO_CMD_RESUME_DM_BY_SCAN:
		अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC)
			_rtl8821ae_resume_tx_beacon(hw);
		rtl8821ae_dm_ग_लिखो_dig(hw, rtlphy->initgain_backup.xaagccore1);
		rtl8821ae_dm_ग_लिखो_cck_cca_thres(hw,
						 rtlphy->initgain_backup.cca);
		अवरोध;
	हाल IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC)
			_rtl8821ae_stop_tx_beacon(hw);
		rtlphy->initgain_backup.xaagccore1 = dm_digtable->cur_igvalue;
		rtl8821ae_dm_ग_लिखो_dig(hw, 0x17);
		rtlphy->initgain_backup.cca = dm_digtable->cur_cck_cca_thres;
		rtl8821ae_dm_ग_लिखो_cck_cca_thres(hw, 0x40);
		अवरोध;
	हाल IO_CMD_PAUSE_BAND1_DM_BY_SCAN:
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n",
		       rtlphy->current_io_type);
		अवरोध;
	पूर्ण
	rtlphy->set_io_inprogress = false;
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"(%#x)\n", rtlphy->current_io_type);
पूर्ण

अटल व्योम rtl8821ae_phy_set_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
पूर्ण

अटल bool _rtl8821ae_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
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
			bool rtstatus = false;
			u32 initializecount = 0;

			करो अणु
				initializecount++;
				rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
					"IPS Set eRf nic enable\n");
				rtstatus = rtl_ps_enable_nic(hw);
			पूर्ण जबतक (!rtstatus && (initializecount < 10));
			RT_CLEAR_PS_LEVEL(ppsc,
					  RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"Set ERFON slept:%d ms\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_sleep_jअगरfies));
			ppsc->last_awake_jअगरfies = jअगरfies;
			rtl8821ae_phy_set_rf_on(hw);
		पूर्ण
		अगर (mac->link_state == MAC80211_LINKED) अणु
			rtlpriv->cfg->ops->led_control(hw,
						       LED_CTL_LINK);
		पूर्ण अन्यथा अणु
			rtlpriv->cfg->ops->led_control(hw,
						       LED_CTL_NO_LINK);
		पूर्ण
		अवरोध;
	हाल ERFOFF:
		क्रम (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) अणु
			ring = &pcipriv->dev.tx_ring[queue_id];
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
					"\n ERFSLEEP: %d times TcbBusyQueue[%d] = %d !\n",
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
	शेष:
		pr_err("switch case %#x not processed\n",
		       rfpwr_state);
		bresult = false;
		अवरोध;
	पूर्ण
	अगर (bresult)
		ppsc->rfpwr_state = rfpwr_state;
	वापस bresult;
पूर्ण

bool rtl8821ae_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				      क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	bool bresult = false;

	अगर (rfpwr_state == ppsc->rfpwr_state)
		वापस bresult;
	bresult = _rtl8821ae_phy_set_rf_घातer_state(hw, rfpwr_state);
	वापस bresult;
पूर्ण
