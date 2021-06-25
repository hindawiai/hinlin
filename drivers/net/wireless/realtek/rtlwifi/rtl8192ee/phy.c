<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../ps.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "table.h"

अटल u32 _rtl92ee_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
				       क्रमागत radio_path rfpath, u32 offset);
अटल व्योम _rtl92ee_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
					 क्रमागत radio_path rfpath, u32 offset,
					 u32 data);
अटल u32 _rtl92ee_phy_calculate_bit_shअगरt(u32 biपंचांगask);
अटल bool _rtl92ee_phy_bb8192ee_config_parafile(काष्ठा ieee80211_hw *hw);
अटल bool _rtl92ee_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw);
अटल bool phy_config_bb_with_hdr_file(काष्ठा ieee80211_hw *hw,
					u8 configtype);
अटल bool phy_config_bb_with_pghdrfile(काष्ठा ieee80211_hw *hw,
					 u8 configtype);
अटल व्योम phy_init_bb_rf_रेजिस्टर_def(काष्ठा ieee80211_hw *hw);
अटल bool _rtl92ee_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
					      u32 cmdtableidx, u32 cmdtablesz,
					      क्रमागत swchnlcmd_id cmdid,
					      u32 para1, u32 para2,
					      u32 msdelay);
अटल bool _rtl92ee_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
					      u8 channel, u8 *stage,
					      u8 *step, u32 *delay);
अटल दीर्घ _rtl92ee_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
					  क्रमागत wireless_mode wirelessmode,
					  u8 txpwridx);
अटल व्योम rtl92ee_phy_set_rf_on(काष्ठा ieee80211_hw *hw);
अटल व्योम rtl92ee_phy_set_io(काष्ठा ieee80211_hw *hw);

u32 rtl92ee_phy_query_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 वापसvalue, originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x)\n", regaddr, biपंचांगask);
	originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
	bitshअगरt = _rtl92ee_phy_calculate_bit_shअगरt(biपंचांगask);
	वापसvalue = (originalvalue & biपंचांगask) >> bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"BBR MASK=0x%x Addr[0x%x]=0x%x\n",
		biपंचांगask, regaddr, originalvalue);

	वापस वापसvalue;
पूर्ण

व्योम rtl92ee_phy_set_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr,
			    u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);

	अगर (biपंचांगask != MASKDWORD) अणु
		originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
		bitshअगरt = _rtl92ee_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((originalvalue & (~biपंचांगask)) | (data << bitshअगरt));
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, regaddr, data);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);
पूर्ण

u32 rtl92ee_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			     क्रमागत radio_path rfpath, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, पढ़ोback_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x)\n",
		regaddr, rfpath, biपंचांगask);

	spin_lock(&rtlpriv->locks.rf_lock);

	original_value = _rtl92ee_phy_rf_serial_पढ़ो(hw , rfpath, regaddr);
	bitshअगरt = _rtl92ee_phy_calculate_bit_shअगरt(biपंचांगask);
	पढ़ोback_value = (original_value & biपंचांगask) >> bitshअगरt;

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x),rfpath(%#x),bitmask(%#x),original_value(%#x)\n",
		regaddr, rfpath, biपंचांगask, original_value);

	वापस पढ़ोback_value;
पूर्ण

व्योम rtl92ee_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
			    क्रमागत radio_path rfpath,
			    u32 addr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		addr, biपंचांगask, data, rfpath);

	spin_lock(&rtlpriv->locks.rf_lock);

	अगर (biपंचांगask != RFREG_OFFSET_MASK) अणु
		original_value = _rtl92ee_phy_rf_serial_पढ़ो(hw, rfpath, addr);
		bitshअगरt = _rtl92ee_phy_calculate_bit_shअगरt(biपंचांगask);
		data = (original_value & (~biपंचांगask)) | (data << bitshअगरt);
	पूर्ण

	_rtl92ee_phy_rf_serial_ग_लिखो(hw, rfpath, addr, data);

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		addr, biपंचांगask, data, rfpath);
पूर्ण

अटल u32 _rtl92ee_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
				       क्रमागत radio_path rfpath, u32 offset)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];
	u32 newoffset;
	u32 पंचांगpदीर्घ, पंचांगpदीर्घ2;
	u8 rfpi_enable = 0;
	u32 retvalue;

	offset &= 0xff;
	newoffset = offset;
	अगर (RT_CANNOT_IO(hw)) अणु
		pr_err("return all one\n");
		वापस 0xFFFFFFFF;
	पूर्ण
	पंचांगpदीर्घ = rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, MASKDWORD);
	अगर (rfpath == RF90_PATH_A)
		पंचांगpदीर्घ2 = पंचांगpदीर्घ;
	अन्यथा
		पंचांगpदीर्घ2 = rtl_get_bbreg(hw, pphyreg->rfhssi_para2, MASKDWORD);
	पंचांगpदीर्घ2 = (पंचांगpदीर्घ2 & (~BLSSIREADADDRESS)) |
		   (newoffset << 23) | BLSSIREADEDGE;
	rtl_set_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, MASKDWORD,
		      पंचांगpदीर्घ & (~BLSSIREADEDGE));
	rtl_set_bbreg(hw, pphyreg->rfhssi_para2, MASKDWORD, पंचांगpदीर्घ2);
	udelay(20);
	अगर (rfpath == RF90_PATH_A)
		rfpi_enable = (u8)rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER1,
						BIT(8));
	अन्यथा अगर (rfpath == RF90_PATH_B)
		rfpi_enable = (u8)rtl_get_bbreg(hw, RFPGA0_XB_HSSIPARAMETER1,
						BIT(8));
	अगर (rfpi_enable)
		retvalue = rtl_get_bbreg(hw, pphyreg->rf_rbpi,
					 BLSSIREADBACKDATA);
	अन्यथा
		retvalue = rtl_get_bbreg(hw, pphyreg->rf_rb,
					 BLSSIREADBACKDATA);
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"RFR-%d Addr[0x%x]=0x%x\n",
		rfpath, pphyreg->rf_rb, retvalue);
	वापस retvalue;
पूर्ण

अटल व्योम _rtl92ee_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
					 क्रमागत radio_path rfpath, u32 offset,
					 u32 data)
अणु
	u32 data_and_addr;
	u32 newoffset;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];

	अगर (RT_CANNOT_IO(hw)) अणु
		pr_err("stop\n");
		वापस;
	पूर्ण
	offset &= 0xff;
	newoffset = offset;
	data_and_addr = ((newoffset << 20) | (data & 0x000fffff)) & 0x0fffffff;
	rtl_set_bbreg(hw, pphyreg->rf3wire_offset, MASKDWORD, data_and_addr);
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"RFW-%d Addr[0x%x]=0x%x\n", rfpath,
		pphyreg->rf3wire_offset, data_and_addr);
पूर्ण

अटल u32 _rtl92ee_phy_calculate_bit_shअगरt(u32 biपंचांगask)
अणु
	u32 i = ffs(biपंचांगask);

	वापस i ? i - 1 : 32;
पूर्ण

bool rtl92ee_phy_mac_config(काष्ठा ieee80211_hw *hw)
अणु
	वापस _rtl92ee_phy_config_mac_with_headerfile(hw);
पूर्ण

bool rtl92ee_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool rtstatus = true;
	u16 regval;
	u32 पंचांगp;
	u8 crystal_cap;

	phy_init_bb_rf_रेजिस्टर_def(hw);
	regval = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN,
		       regval | BIT(13) | BIT(0) | BIT(1));

	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, RF_EN | RF_RSTB | RF_SDMRSTB);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN,
		       FEN_PPLL | FEN_PCIEA | FEN_DIO_PCIE |
		       FEN_BB_GLB_RSTN | FEN_BBRSTB);

	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL + 1, 0x80);

	पंचांगp = rtl_पढ़ो_dword(rtlpriv, 0x4c);
	rtl_ग_लिखो_dword(rtlpriv, 0x4c, पंचांगp | BIT(23));

	rtstatus = _rtl92ee_phy_bb8192ee_config_parafile(hw);

	crystal_cap = rtlpriv->efuse.eeprom_crystalcap & 0x3F;
	rtl_set_bbreg(hw, REG_MAC_PHY_CTRL, 0xFFF000,
		      (crystal_cap | (crystal_cap << 6)));
	वापस rtstatus;
पूर्ण

bool rtl92ee_phy_rf_config(काष्ठा ieee80211_hw *hw)
अणु
	वापस rtl92ee_phy_rf6052_config(hw);
पूर्ण

अटल bool _check_condition(काष्ठा ieee80211_hw *hw,
			     स्थिर u32  condition)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 _board = rtlefuse->board_type; /*need efuse define*/
	u32 _पूर्णांकerface = rtlhal->पूर्णांकerface;
	u32 _platक्रमm = 0x08;/*SupportPlatक्रमm */
	u32 cond = condition;

	अगर (condition == 0xCDCDCDCD)
		वापस true;

	cond = condition & 0xFF;
	अगर ((_board != cond) && (cond != 0xFF))
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

अटल व्योम _rtl92ee_config_rf_reg(काष्ठा ieee80211_hw *hw, u32 addr, u32 data,
				   क्रमागत radio_path rfpath, u32 regaddr)
अणु
	अगर (addr == 0xfe || addr == 0xffe) अणु
		mdelay(50);
	पूर्ण अन्यथा अणु
		rtl_set_rfreg(hw, rfpath, regaddr, RFREG_OFFSET_MASK, data);
		udelay(1);

		अगर (addr == 0xb6) अणु
			u32 getvalue;
			u8 count = 0;

			getvalue = rtl_get_rfreg(hw, rfpath, addr, MASKDWORD);
			udelay(1);

			जबतक ((getvalue >> 8) != (data >> 8)) अणु
				count++;
				rtl_set_rfreg(hw, rfpath, regaddr,
					      RFREG_OFFSET_MASK, data);
				udelay(1);
				getvalue = rtl_get_rfreg(hw, rfpath, addr,
							 MASKDWORD);
				अगर (count > 5)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (addr == 0xb2) अणु
			u32 getvalue;
			u8 count = 0;

			getvalue = rtl_get_rfreg(hw, rfpath, addr, MASKDWORD);
			udelay(1);

			जबतक (getvalue != data) अणु
				count++;
				rtl_set_rfreg(hw, rfpath, regaddr,
					      RFREG_OFFSET_MASK, data);
				udelay(1);
				rtl_set_rfreg(hw, rfpath, 0x18,
					      RFREG_OFFSET_MASK, 0x0fc07);
				udelay(1);
				getvalue = rtl_get_rfreg(hw, rfpath, addr,
							 MASKDWORD);
				अगर (count > 5)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_config_rf_radio_a(काष्ठा ieee80211_hw *hw,
				       u32 addr, u32 data)
अणु
	u32 content = 0x1000; /*RF Content: radio_a_txt*/
	u32 maskक्रमphyset = (u32)(content & 0xE000);

	_rtl92ee_config_rf_reg(hw, addr, data, RF90_PATH_A,
			       addr | maskक्रमphyset);
पूर्ण

अटल व्योम _rtl92ee_config_rf_radio_b(काष्ठा ieee80211_hw *hw,
				       u32 addr, u32 data)
अणु
	u32 content = 0x1001; /*RF Content: radio_b_txt*/
	u32 maskक्रमphyset = (u32)(content & 0xE000);

	_rtl92ee_config_rf_reg(hw, addr, data, RF90_PATH_B,
			       addr | maskक्रमphyset);
पूर्ण

अटल व्योम _rtl92ee_config_bb_reg(काष्ठा ieee80211_hw *hw,
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
		rtl_set_bbreg(hw, addr, MASKDWORD , data);

	udelay(1);
पूर्ण

अटल व्योम _rtl92ee_phy_init_tx_घातer_by_rate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	u8 band = BAND_ON_2_4G, rf = 0, txnum = 0, sec = 0;

	क्रम (; band <= BAND_ON_5G; ++band)
		क्रम (; rf < TX_PWR_BY_RATE_NUM_RF; ++rf)
			क्रम (; txnum < TX_PWR_BY_RATE_NUM_RF; ++txnum)
				क्रम (; sec < TX_PWR_BY_RATE_NUM_SECTION; ++sec)
					rtlphy->tx_घातer_by_rate_offset
					     [band][rf][txnum][sec] = 0;
पूर्ण

अटल व्योम _rtl92ee_phy_set_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw,
						  u8 band, u8 path,
						  u8 rate_section, u8 txnum,
						  u8 value)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	अगर (path > RF90_PATH_D) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Rf Path %d\n", path);
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
				"Invalid RateSection %d in 2.4G,Rf %d,%dTx\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Band %d\n", band);
	पूर्ण
पूर्ण

अटल u8 _rtl92ee_phy_get_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw,
						u8 band, u8 path, u8 txnum,
						u8 rate_section)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 value = 0;

	अगर (path > RF90_PATH_D) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Rf Path %d\n", path);
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
				"Invalid RateSection %d in 2.4G,Rf %d,%dTx\n",
				rate_section, path, txnum);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Invalid Band %d()\n", band);
	पूर्ण
	वापस value;
पूर्ण

अटल व्योम _rtl92ee_phy_store_txघातer_by_rate_base(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u16 raw = 0;
	u8 base = 0, path = 0;

	क्रम (path = RF90_PATH_A; path <= RF90_PATH_B; ++path) अणु
		अगर (path == RF90_PATH_A) अणु
			raw = (u16)(rtlphy->tx_घातer_by_rate_offset
				    [BAND_ON_2_4G][path][RF_1TX][3] >> 24) &
				    0xFF;
			base = (raw >> 4) * 10 + (raw & 0xF);
			_rtl92ee_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G,
							      path, CCK, RF_1TX,
							      base);
		पूर्ण अन्यथा अगर (path == RF90_PATH_B) अणु
			raw = (u16)(rtlphy->tx_घातer_by_rate_offset
				    [BAND_ON_2_4G][path][RF_1TX][3] >> 0) &
				    0xFF;
			base = (raw >> 4) * 10 + (raw & 0xF);
			_rtl92ee_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G,
							      path, CCK, RF_1TX,
							      base);
		पूर्ण
		raw = (u16)(rtlphy->tx_घातer_by_rate_offset
			    [BAND_ON_2_4G][path][RF_1TX][1] >> 24) & 0xFF;
		base = (raw >> 4) * 10 + (raw & 0xF);
		_rtl92ee_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path,
						      OFDM, RF_1TX, base);

		raw = (u16)(rtlphy->tx_घातer_by_rate_offset
			    [BAND_ON_2_4G][path][RF_1TX][5] >> 24) & 0xFF;
		base = (raw >> 4) * 10 + (raw & 0xF);
		_rtl92ee_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path,
						      HT_MCS0_MCS7, RF_1TX,
						      base);

		raw = (u16)(rtlphy->tx_घातer_by_rate_offset
			    [BAND_ON_2_4G][path][RF_2TX][7] >> 24) & 0xFF;
		base = (raw >> 4) * 10 + (raw & 0xF);
		_rtl92ee_phy_set_txघातer_by_rate_base(hw, BAND_ON_2_4G, path,
						      HT_MCS8_MCS15, RF_2TX,
						      base);
	पूर्ण
पूर्ण

अटल व्योम _phy_convert_txघातer_dbm_to_relative_value(u32 *data, u8 start,
						       u8 end, u8 base)
अणु
	s8 i = 0;
	u8 पंचांगp = 0;
	u32 temp_data = 0;

	क्रम (i = 3; i >= 0; --i) अणु
		अगर (i >= start && i <= end) अणु
			/* Get the exact value */
			पंचांगp = (u8)(*data >> (i * 8)) & 0xF;
			पंचांगp += ((u8)((*data >> (i * 8 + 4)) & 0xF)) * 10;

			/* Change the value to a relative value */
			पंचांगp = (पंचांगp > base) ? पंचांगp - base : base - पंचांगp;
		पूर्ण अन्यथा अणु
			पंचांगp = (u8)(*data >> (i * 8)) & 0xFF;
		पूर्ण
		temp_data <<= 8;
		temp_data |= पंचांगp;
	पूर्ण
	*data = temp_data;
पूर्ण

अटल व्योम phy_convert_txpwr_dbm_to_rel_val(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 base = 0, rf = 0, band = BAND_ON_2_4G;

	क्रम (rf = RF90_PATH_A; rf <= RF90_PATH_B; ++rf) अणु
		अगर (rf == RF90_PATH_A) अणु
			base = _rtl92ee_phy_get_txघातer_by_rate_base(hw, band,
								     rf, RF_1TX,
								     CCK);
			_phy_convert_txघातer_dbm_to_relative_value(
				&rtlphy->tx_घातer_by_rate_offset
				[band][rf][RF_1TX][2],
				1, 1, base);
			_phy_convert_txघातer_dbm_to_relative_value(
				&rtlphy->tx_घातer_by_rate_offset
				[band][rf][RF_1TX][3],
				1, 3, base);
		पूर्ण अन्यथा अगर (rf == RF90_PATH_B) अणु
			base = _rtl92ee_phy_get_txघातer_by_rate_base(hw, band,
								     rf, RF_1TX,
								     CCK);
			_phy_convert_txघातer_dbm_to_relative_value(
				&rtlphy->tx_घातer_by_rate_offset
				[band][rf][RF_1TX][3],
				0, 0, base);
			_phy_convert_txघातer_dbm_to_relative_value(
				&rtlphy->tx_घातer_by_rate_offset
				[band][rf][RF_1TX][2],
				1, 3, base);
		पूर्ण
		base = _rtl92ee_phy_get_txघातer_by_rate_base(hw, band, rf,
							     RF_1TX, OFDM);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[band][rf][RF_1TX][0],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[band][rf][RF_1TX][1],
			0, 3, base);

		base = _rtl92ee_phy_get_txघातer_by_rate_base(hw, band, rf,
							     RF_1TX,
							     HT_MCS0_MCS7);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[band][rf][RF_1TX][4],
			0, 3, base);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[band][rf][RF_1TX][5],
			0, 3, base);

		base = _rtl92ee_phy_get_txघातer_by_rate_base(hw, band, rf,
							     RF_2TX,
							     HT_MCS8_MCS15);
		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[band][rf][RF_2TX][6],
			0, 3, base);

		_phy_convert_txघातer_dbm_to_relative_value(
			&rtlphy->tx_घातer_by_rate_offset[band][rf][RF_2TX][7],
			0, 3, base);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
		"<==%s\n", __func__);
पूर्ण

अटल व्योम _rtl92ee_phy_txघातer_by_rate_configuration(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92ee_phy_store_txघातer_by_rate_base(hw);
	phy_convert_txpwr_dbm_to_rel_val(hw);
पूर्ण

अटल bool _rtl92ee_phy_bb8192ee_config_parafile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus;

	rtstatus = phy_config_bb_with_hdr_file(hw, BASEBAND_CONFIG_PHY_REG);
	अगर (!rtstatus) अणु
		pr_err("Write BB Reg Fail!!\n");
		वापस false;
	पूर्ण

	_rtl92ee_phy_init_tx_घातer_by_rate(hw);
	अगर (!rtlefuse->स्वतःload_failflag) अणु
		rtlphy->pwrgroup_cnt = 0;
		rtstatus =
		  phy_config_bb_with_pghdrfile(hw, BASEBAND_CONFIG_PHY_REG);
	पूर्ण
	_rtl92ee_phy_txघातer_by_rate_configuration(hw);
	अगर (!rtstatus) अणु
		pr_err("BB_PG Reg Fail!!\n");
		वापस false;
	पूर्ण
	rtstatus = phy_config_bb_with_hdr_file(hw, BASEBAND_CONFIG_AGC_TAB);
	अगर (!rtstatus) अणु
		pr_err("AGC Table Fail\n");
		वापस false;
	पूर्ण
	rtlphy->cck_high_घातer = (bool)(rtl_get_bbreg(hw,
						      RFPGA0_XA_HSSIPARAMETER2,
						      0x200));

	वापस true;
पूर्ण

अटल bool _rtl92ee_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;
	u32 arraylength;
	u32 *ptrarray;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Read Rtl8192EMACPHY_Array\n");
	arraylength = RTL8192EE_MAC_ARRAY_LEN;
	ptrarray = RTL8192EE_MAC_ARRAY;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Img:RTL8192EE_MAC_ARRAY LEN %d\n", arraylength);
	क्रम (i = 0; i < arraylength; i = i + 2)
		rtl_ग_लिखो_byte(rtlpriv, ptrarray[i], (u8)ptrarray[i + 1]);
	वापस true;
पूर्ण

#घोषणा READ_NEXT_PAIR(v1, v2, i) \
	करो अणु \
		i += 2; \
		v1 = array[i]; \
		v2 = array[i+1]; \
	पूर्ण जबतक (0)

अटल bool phy_config_bb_with_hdr_file(काष्ठा ieee80211_hw *hw,
					u8 configtype)
अणु
	पूर्णांक i;
	u32 *array;
	u16 len;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 v1 = 0, v2 = 0;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		len = RTL8192EE_PHY_REG_ARRAY_LEN;
		array = RTL8192EE_PHY_REG_ARRAY;

		क्रम (i = 0; i < len; i = i + 2) अणु
			v1 = array[i];
			v2 = array[i+1];
			अगर (v1 < 0xcdcdcdcd) अणु
				_rtl92ee_config_bb_reg(hw, v1, v2);
			पूर्ण अन्यथा अणु/*This line is the start line of branch.*/
				/* to protect READ_NEXT_PAIR not overrun */
				अगर (i >= len - 2)
					अवरोध;

				अगर (!_check_condition(hw , array[i])) अणु
					/*Discard the following pairs*/
					READ_NEXT_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD && i < len - 2) अणु
						READ_NEXT_PAIR(v1, v2, i);
					पूर्ण
					i -= 2; /* prevent from क्रम-loop += 2*/
				पूर्ण अन्यथा अणु
					/* Configure matched pairs and
					 * skip to end of अगर-अन्यथा.
					 */
					READ_NEXT_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD && i < len - 2) अणु
						_rtl92ee_config_bb_reg(hw, v1,
								       v2);
						READ_NEXT_PAIR(v1, v2, i);
					पूर्ण

					जबतक (v2 != 0xDEAD && i < len - 2)
						READ_NEXT_PAIR(v1, v2, i);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (configtype == BASEBAND_CONFIG_AGC_TAB) अणु
		len = RTL8192EE_AGC_TAB_ARRAY_LEN;
		array = RTL8192EE_AGC_TAB_ARRAY;

		क्रम (i = 0; i < len; i = i + 2) अणु
			v1 = array[i];
			v2 = array[i+1];
			अगर (v1 < 0xCDCDCDCD) अणु
				rtl_set_bbreg(hw, array[i], MASKDWORD,
					      array[i + 1]);
				udelay(1);
				जारी;
		    पूर्ण अन्यथाअणु/*This line is the start line of branch.*/
			  /* to protect READ_NEXT_PAIR not overrun */
				अगर (i >= len - 2)
					अवरोध;

				अगर (!_check_condition(hw , array[i])) अणु
					/*Discard the following pairs*/
					READ_NEXT_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD &&
					       i < len - 2) अणु
						READ_NEXT_PAIR(v1, v2, i);
					पूर्ण
					i -= 2; /* prevent from क्रम-loop += 2*/
				पूर्ण अन्यथा अणु
					/* Configure matched pairs and
					 * skip to end of अगर-अन्यथा.
					 */
					READ_NEXT_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD &&
					       i < len - 2) अणु
						rtl_set_bbreg(hw,
							      array[i],
							      MASKDWORD,
							      array[i + 1]);
						udelay(1);
						READ_NEXT_PAIR(v1 , v2 , i);
					पूर्ण

					जबतक (v2 != 0xDEAD &&
					       i < len - 2) अणु
						READ_NEXT_PAIR(v1 , v2 , i);
					पूर्ण
				पूर्ण
			पूर्ण
			rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
				"The agctab_array_table[0] is %x Rtl818EEPHY_REGArray[1] is %x\n",
				array[i],
				array[i + 1]);
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल u8 _rtl92ee_get_rate_section_index(u32 regaddr)
अणु
	u8 index = 0;

	चयन (regaddr) अणु
	हाल RTXAGC_A_RATE18_06:
	हाल RTXAGC_B_RATE18_06:
		index = 0;
		अवरोध;
	हाल RTXAGC_A_RATE54_24:
	हाल RTXAGC_B_RATE54_24:
		index = 1;
		अवरोध;
	हाल RTXAGC_A_CCK1_MCS32:
	हाल RTXAGC_B_CCK1_55_MCS32:
		index = 2;
		अवरोध;
	हाल RTXAGC_B_CCK11_A_CCK2_11:
		index = 3;
		अवरोध;
	हाल RTXAGC_A_MCS03_MCS00:
	हाल RTXAGC_B_MCS03_MCS00:
		index = 4;
		अवरोध;
	हाल RTXAGC_A_MCS07_MCS04:
	हाल RTXAGC_B_MCS07_MCS04:
		index = 5;
		अवरोध;
	हाल RTXAGC_A_MCS11_MCS08:
	हाल RTXAGC_B_MCS11_MCS08:
		index = 6;
		अवरोध;
	हाल RTXAGC_A_MCS15_MCS12:
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

अटल व्योम _rtl92ee_store_tx_घातer_by_rate(काष्ठा ieee80211_hw *hw,
					    क्रमागत band_type band,
					    क्रमागत radio_path rfpath,
					    u32 txnum, u32 regaddr,
					    u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 section = _rtl92ee_get_rate_section_index(regaddr);

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

	rtlphy->tx_घातer_by_rate_offset[band][rfpath][txnum][section] = data;
पूर्ण

अटल bool phy_config_bb_with_pghdrfile(काष्ठा ieee80211_hw *hw,
					 u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;
	u32 *phy_regarray_table_pg;
	u16 phy_regarray_pg_len;
	u32 v1 = 0, v2 = 0, v3 = 0, v4 = 0, v5 = 0, v6 = 0;

	phy_regarray_pg_len = RTL8192EE_PHY_REG_ARRAY_PG_LEN;
	phy_regarray_table_pg = RTL8192EE_PHY_REG_ARRAY_PG;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_regarray_pg_len; i = i + 6) अणु
			v1 = phy_regarray_table_pg[i];
			v2 = phy_regarray_table_pg[i+1];
			v3 = phy_regarray_table_pg[i+2];
			v4 = phy_regarray_table_pg[i+3];
			v5 = phy_regarray_table_pg[i+4];
			v6 = phy_regarray_table_pg[i+5];

			अगर (v1 < 0xcdcdcdcd) अणु
				_rtl92ee_store_tx_घातer_by_rate(hw, v1, v2, v3,
								v4, v5, v6);
				जारी;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"configtype != BaseBand_Config_PHY_REG\n");
	पूर्ण
	वापस true;
पूर्ण

#घोषणा READ_NEXT_RF_PAIR(v1, v2, i) \
	करो अणु \
		i += 2; \
		v1 = array[i]; \
		v2 = array[i+1]; \
	पूर्ण जबतक (0)

bool rtl92ee_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw  *hw,
					   क्रमागत radio_path rfpath)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;
	u32 *array;
	u16 len;
	u32 v1 = 0, v2 = 0;

	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		len = RTL8192EE_RADIOA_ARRAY_LEN;
		array = RTL8192EE_RADIOA_ARRAY;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Radio_A:RTL8192EE_RADIOA_ARRAY %d\n", len);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
		क्रम (i = 0; i < len; i = i + 2) अणु
			v1 = array[i];
			v2 = array[i+1];
			अगर (v1 < 0xcdcdcdcd) अणु
				_rtl92ee_config_rf_radio_a(hw, v1, v2);
				जारी;
			पूर्ण अन्यथा अणु/*This line is the start line of branch.*/
				/* to protect READ_NEXT_PAIR not overrun */
				अगर (i >= len - 2)
					अवरोध;

				अगर (!_check_condition(hw , array[i])) अणु
					/*Discard the following pairs*/
					READ_NEXT_RF_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD && i < len - 2) अणु
						READ_NEXT_RF_PAIR(v1, v2, i);
					पूर्ण
					i -= 2; /* prevent from क्रम-loop += 2*/
				पूर्ण अन्यथा अणु
					/* Configure matched pairs and
					 * skip to end of अगर-अन्यथा.
					 */
					READ_NEXT_RF_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD && i < len - 2) अणु
						_rtl92ee_config_rf_radio_a(hw,
									   v1,
									   v2);
						READ_NEXT_RF_PAIR(v1, v2, i);
					पूर्ण

					जबतक (v2 != 0xDEAD && i < len - 2)
						READ_NEXT_RF_PAIR(v1, v2, i);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;

	हाल RF90_PATH_B:
		len = RTL8192EE_RADIOB_ARRAY_LEN;
		array = RTL8192EE_RADIOB_ARRAY;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Radio_A:RTL8192EE_RADIOB_ARRAY %d\n", len);
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
		क्रम (i = 0; i < len; i = i + 2) अणु
			v1 = array[i];
			v2 = array[i+1];
			अगर (v1 < 0xcdcdcdcd) अणु
				_rtl92ee_config_rf_radio_b(hw, v1, v2);
				जारी;
			पूर्ण अन्यथा अणु/*This line is the start line of branch.*/
				/* to protect READ_NEXT_PAIR not overrun */
				अगर (i >= len - 2)
					अवरोध;

				अगर (!_check_condition(hw , array[i])) अणु
					/*Discard the following pairs*/
					READ_NEXT_RF_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD && i < len - 2) अणु
						READ_NEXT_RF_PAIR(v1, v2, i);
					पूर्ण
					i -= 2; /* prevent from क्रम-loop += 2*/
				पूर्ण अन्यथा अणु
					/* Configure matched pairs and
					 * skip to end of अगर-अन्यथा.
					 */
					READ_NEXT_RF_PAIR(v1, v2, i);
					जबतक (v2 != 0xDEAD &&
					       v2 != 0xCDEF &&
					       v2 != 0xCDCD && i < len - 2) अणु
						_rtl92ee_config_rf_radio_b(hw,
									   v1,
									   v2);
						READ_NEXT_RF_PAIR(v1, v2, i);
					पूर्ण

					जबतक (v2 != 0xDEAD && i < len - 2)
						READ_NEXT_RF_PAIR(v1, v2, i);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;
	हाल RF90_PATH_C:
	हाल RF90_PATH_D:
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

व्योम rtl92ee_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw)
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

अटल व्योम phy_init_bb_rf_रेजिस्टर_def(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfo = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfo = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfe = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfe = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rf3wire_offset =
							RFPGA0_XA_LSSIPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_B].rf3wire_offset =
							RFPGA0_XB_LSSIPARAMETER;

	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para2 = RFPGA0_XA_HSSIPARAMETER2;
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para2 = RFPGA0_XB_HSSIPARAMETER2;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rb = RFPGA0_XA_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rb = RFPGA0_XB_LSSIREADBACK;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rbpi = TRANSCEIVEA_HSPI_READBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rbpi = TRANSCEIVEB_HSPI_READBACK;
पूर्ण

व्योम rtl92ee_phy_get_txघातer_level(काष्ठा ieee80211_hw *hw, दीर्घ *घातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 txpwr_level;
	दीर्घ txpwr_dbm;

	txpwr_level = rtlphy->cur_cck_txpwridx;
	txpwr_dbm = _rtl92ee_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_B,
						  txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx;
	अगर (_rtl92ee_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_G, txpwr_level) >
	    txpwr_dbm)
		txpwr_dbm = _rtl92ee_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_G,
							  txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx;
	अगर (_rtl92ee_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_N_24G,
					  txpwr_level) > txpwr_dbm)
		txpwr_dbm = _rtl92ee_phy_txpwr_idx_to_dbm(hw,
							  WIRELESS_MODE_N_24G,
							  txpwr_level);
	*घातerlevel = txpwr_dbm;
पूर्ण

अटल u8 _rtl92ee_phy_get_ratesection_पूर्णांकxघातer_byrate(क्रमागत radio_path path,
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
		WARN_ONCE(true, "rtl8192ee: Rate_Section is Illegal\n");
		अवरोध;
	पूर्ण
	वापस rate_section;
पूर्ण

अटल u8 _rtl92ee_get_txघातer_by_rate(काष्ठा ieee80211_hw *hw,
				       क्रमागत band_type band,
				       क्रमागत radio_path rf, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 shअगरt = 0, sec, tx_num;
	s8 dअगरf = 0;

	sec = _rtl92ee_phy_get_ratesection_पूर्णांकxघातer_byrate(rf, rate);
	tx_num = RF_TX_NUM_NONIMPLEMENT;

	अगर (tx_num == RF_TX_NUM_NONIMPLEMENT) अणु
		अगर ((rate >= DESC92C_RATEMCS8 && rate <= DESC92C_RATEMCS15))
			tx_num = RF_2TX;
		अन्यथा
			tx_num = RF_1TX;
	पूर्ण

	चयन (rate) अणु
	हाल DESC92C_RATE1M:
	हाल DESC92C_RATE6M:
	हाल DESC92C_RATE24M:
	हाल DESC92C_RATEMCS0:
	हाल DESC92C_RATEMCS4:
	हाल DESC92C_RATEMCS8:
	हाल DESC92C_RATEMCS12:
		shअगरt = 0;
		अवरोध;
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
		WARN_ONCE(true, "rtl8192ee: Rate_Section is Illegal\n");
		अवरोध;
	पूर्ण

	dअगरf = (u8)(rtlphy->tx_घातer_by_rate_offset[band][rf][tx_num][sec] >>
		    shअगरt) & 0xff;

	वापस	dअगरf;
पूर्ण

अटल u8 _rtl92ee_get_txघातer_index(काष्ठा ieee80211_hw *hw,
				     क्रमागत radio_path rfpath, u8 rate,
				     u8 bw, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtlpriv);
	u8 index = (channel - 1);
	u8 tx_घातer = 0;
	u8 dअगरf = 0;

	अगर (channel < 1 || channel > 14) अणु
		index = 0;
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_DMESG,
			"Illegal channel!!\n");
	पूर्ण

	अगर (IS_CCK_RATE((s8)rate))
		tx_घातer = rtlefuse->txpwrlevel_cck[rfpath][index];
	अन्यथा अगर (DESC92C_RATE6M <= rate)
		tx_घातer = rtlefuse->txpwrlevel_ht40_1s[rfpath][index];

	/* OFDM-1T*/
	अगर (DESC92C_RATE6M <= rate && rate <= DESC92C_RATE54M &&
	    !IS_CCK_RATE((s8)rate))
		tx_घातer += rtlefuse->txpwr_legacyhtdअगरf[rfpath][TX_1S];

	/* BW20-1S, BW20-2S */
	अगर (bw == HT_CHANNEL_WIDTH_20) अणु
		अगर (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			tx_घातer += rtlefuse->txpwr_ht20dअगरf[rfpath][TX_1S];
		अगर (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			tx_घातer += rtlefuse->txpwr_ht20dअगरf[rfpath][TX_2S];
	पूर्ण अन्यथा अगर (bw == HT_CHANNEL_WIDTH_20_40) अणु/* BW40-1S, BW40-2S */
		अगर (DESC92C_RATEMCS0 <= rate && rate <= DESC92C_RATEMCS15)
			tx_घातer += rtlefuse->txpwr_ht40dअगरf[rfpath][TX_1S];
		अगर (DESC92C_RATEMCS8 <= rate && rate <= DESC92C_RATEMCS15)
			tx_घातer += rtlefuse->txpwr_ht40dअगरf[rfpath][TX_2S];
	पूर्ण

	अगर (rtlefuse->eeprom_regulatory != 2)
		dअगरf = _rtl92ee_get_txघातer_by_rate(hw, BAND_ON_2_4G,
						    rfpath, rate);

	tx_घातer += dअगरf;

	अगर (tx_घातer > MAX_POWER_INDEX)
		tx_घातer = MAX_POWER_INDEX;

	वापस tx_घातer;
पूर्ण

अटल व्योम _rtl92ee_set_txघातer_index(काष्ठा ieee80211_hw *hw, u8 pwr_idx,
				       क्रमागत radio_path rfpath, u8 rate)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rfpath == RF90_PATH_A) अणु
		चयन (rate) अणु
		हाल DESC92C_RATE1M:
			rtl_set_bbreg(hw, RTXAGC_A_CCK1_MCS32, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE2M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE5_5M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE11M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE6M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE9M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE12M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE18M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE18_06, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE24M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE36M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE48M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE54M:
			rtl_set_bbreg(hw, RTXAGC_A_RATE54_24, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS0:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS1:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS2:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS3:
			rtl_set_bbreg(hw, RTXAGC_A_MCS03_MCS00, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS4:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS5:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS6:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS7:
			rtl_set_bbreg(hw, RTXAGC_A_MCS07_MCS04, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS8:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS9:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS10:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS11:
			rtl_set_bbreg(hw, RTXAGC_A_MCS11_MCS08, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS12:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS13:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS14:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS15:
			rtl_set_bbreg(hw, RTXAGC_A_MCS15_MCS12, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"Invalid Rate!!\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (rfpath == RF90_PATH_B) अणु
		चयन (rate) अणु
		हाल DESC92C_RATE1M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE2M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE5_5M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE11M:
			rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE6M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE9M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE12M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE18M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE18_06, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE24M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE36M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE48M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATE54M:
			rtl_set_bbreg(hw, RTXAGC_B_RATE54_24, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS0:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS1:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS2:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS3:
			rtl_set_bbreg(hw, RTXAGC_B_MCS03_MCS00, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS4:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS5:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS6:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS7:
			rtl_set_bbreg(hw, RTXAGC_B_MCS07_MCS04, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS8:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS9:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS10:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS11:
			rtl_set_bbreg(hw, RTXAGC_B_MCS11_MCS08, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS12:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE0,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS13:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE1,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS14:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE2,
				      pwr_idx);
			अवरोध;
		हाल DESC92C_RATEMCS15:
			rtl_set_bbreg(hw, RTXAGC_B_MCS15_MCS12, MASKBYTE3,
				      pwr_idx);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"Invalid Rate!!\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "Invalid RFPath!!\n");
	पूर्ण
पूर्ण

अटल व्योम phy_set_txघातer_index_by_rate_array(काष्ठा ieee80211_hw *hw,
						क्रमागत radio_path rfpath, u8 bw,
						u8 channel, u8 *rates, u8 size)
अणु
	u8 i;
	u8 घातer_index;

	क्रम (i = 0; i < size; i++) अणु
		घातer_index = _rtl92ee_get_txघातer_index(hw, rfpath, rates[i],
							 bw, channel);
		_rtl92ee_set_txघातer_index(hw, घातer_index, rfpath, rates[i]);
	पूर्ण
पूर्ण

अटल व्योम phy_set_txघातer_index_by_rate_section(काष्ठा ieee80211_hw *hw,
						  क्रमागत radio_path rfpath,
						  u8 channel,
						  क्रमागत rate_section section)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	अगर (section == CCK) अणु
		u8 cck_rates[] = अणुDESC92C_RATE1M, DESC92C_RATE2M,
				  DESC92C_RATE5_5M, DESC92C_RATE11Mपूर्ण;
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G)
			phy_set_txघातer_index_by_rate_array(hw, rfpath,
							rtlphy->current_chan_bw,
							channel, cck_rates, 4);
	पूर्ण अन्यथा अगर (section == OFDM) अणु
		u8 ofdm_rates[] = अणुDESC92C_RATE6M, DESC92C_RATE9M,
				   DESC92C_RATE12M, DESC92C_RATE18M,
				   DESC92C_RATE24M, DESC92C_RATE36M,
				   DESC92C_RATE48M, DESC92C_RATE54Mपूर्ण;
		phy_set_txघातer_index_by_rate_array(hw, rfpath,
						    rtlphy->current_chan_bw,
						    channel, ofdm_rates, 8);
	पूर्ण अन्यथा अगर (section == HT_MCS0_MCS7) अणु
		u8 ht_rates1t[]  = अणुDESC92C_RATEMCS0, DESC92C_RATEMCS1,
				    DESC92C_RATEMCS2, DESC92C_RATEMCS3,
				    DESC92C_RATEMCS4, DESC92C_RATEMCS5,
				    DESC92C_RATEMCS6, DESC92C_RATEMCS7पूर्ण;
		phy_set_txघातer_index_by_rate_array(hw, rfpath,
						    rtlphy->current_chan_bw,
						    channel, ht_rates1t, 8);
	पूर्ण अन्यथा अगर (section == HT_MCS8_MCS15) अणु
		u8 ht_rates2t[]  = अणुDESC92C_RATEMCS8, DESC92C_RATEMCS9,
				    DESC92C_RATEMCS10, DESC92C_RATEMCS11,
				    DESC92C_RATEMCS12, DESC92C_RATEMCS13,
				    DESC92C_RATEMCS14, DESC92C_RATEMCS15पूर्ण;
		phy_set_txघातer_index_by_rate_array(hw, rfpath,
						    rtlphy->current_chan_bw,
						    channel, ht_rates2t, 8);
	पूर्ण अन्यथा
		rtl_dbg(rtlpriv, FPHY, PHY_TXPWR,
			"Invalid RateSection %d\n", section);
पूर्ण

व्योम rtl92ee_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtl_priv(hw)->phy;
	क्रमागत radio_path rfpath;

	अगर (!rtlefuse->txpwr_fromeprom)
		वापस;
	क्रम (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
	     rfpath++) अणु
		phy_set_txघातer_index_by_rate_section(hw, rfpath,
						      channel, CCK);
		phy_set_txघातer_index_by_rate_section(hw, rfpath,
						      channel, OFDM);
		phy_set_txघातer_index_by_rate_section(hw, rfpath,
						      channel,
						      HT_MCS0_MCS7);

		अगर (rtlphy->num_total_rfpath >= 2)
			phy_set_txघातer_index_by_rate_section(hw,
							      rfpath, channel,
							      HT_MCS8_MCS15);
	पूर्ण
पूर्ण

अटल दीर्घ _rtl92ee_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
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

व्योम rtl92ee_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw, u8 operation)
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

व्योम rtl92ee_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw)
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
		rtl_set_bbreg(hw, ROFDM0_TXPSEUDONOISEWGT,
			      (BIT(31) | BIT(30)), 0);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RCCK0_SYSTEM, BCCK_SIDEBAND,
			      (mac->cur_40_prime_sc >> 1));
		rtl_set_bbreg(hw, ROFDM1_LSTF, 0xC00,
			      mac->cur_40_prime_sc);

		rtl_set_bbreg(hw, 0x818, (BIT(26) | BIT(27)),
			      (mac->cur_40_prime_sc ==
			       HAL_PRIME_CHNL_OFFSET_LOWER) ? 2 : 1);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;
	पूर्ण
	rtl92ee_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD, "\n");
पूर्ण

व्योम rtl92ee_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
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
		rtl92ee_phy_set_bw_mode_callback(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"false driver sleep or unload\n");
		rtlphy->set_bwmode_inprogress = false;
		rtlphy->current_chan_bw = पंचांगp_bw;
	पूर्ण
पूर्ण

व्योम rtl92ee_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 delay;

	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"switch to channel%d\n", rtlphy->current_channel);
	अगर (is_hal_stop(rtlhal))
		वापस;
	करो अणु
		अगर (!rtlphy->sw_chnl_inprogress)
			अवरोध;
		अगर (!_rtl92ee_phy_sw_chnl_step_by_step
		    (hw, rtlphy->current_channel, &rtlphy->sw_chnl_stage,
		     &rtlphy->sw_chnl_step, &delay)) अणु
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

u8 rtl92ee_phy_sw_chnl(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlphy->sw_chnl_inprogress)
		वापस 0;
	अगर (rtlphy->set_bwmode_inprogress)
		वापस 0;
	WARN_ONCE((rtlphy->current_channel > 14),
		  "rtl8192ee: WIRELESS_MODE_G but channel>14");
	rtlphy->sw_chnl_inprogress = true;
	rtlphy->sw_chnl_stage = 0;
	rtlphy->sw_chnl_step = 0;
	अगर (!(is_hal_stop(rtlhal)) && !(RT_CANNOT_IO(hw))) अणु
		rtl92ee_phy_sw_chnl_callback(hw);
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

अटल bool _rtl92ee_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
					      u8 channel, u8 *stage, u8 *step,
					      u32 *delay)
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
	_rtl92ee_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					  MAX_PRECMD_CNT,
					  CMDID_SET_TXPOWEROWER_LEVEL, 0, 0, 0);
	_rtl92ee_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					  MAX_PRECMD_CNT, CMDID_END, 0, 0, 0);

	postcommoncmdcnt = 0;

	_rtl92ee_phy_set_sw_chnl_cmdarray(postcommoncmd, postcommoncmdcnt++,
					  MAX_POSTCMD_CNT, CMDID_END, 0, 0, 0);

	rfdependcmdcnt = 0;

	WARN_ONCE((channel < 1 || channel > 14),
		  "rtl8192ee: illegal channel for Zebra: %d\n", channel);

	_rtl92ee_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					  MAX_RFDEPENDCMD_CNT,
					  CMDID_RF_WRITEREG,
					  RF_CHNLBW, channel, 10);

	_rtl92ee_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					  MAX_RFDEPENDCMD_CNT, CMDID_END,
					  0, 0, 0);

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
			अगर ((*stage) == 2)
				वापस true;
			(*stage)++;
			(*step) = 0;
			जारी;
		पूर्ण

		चयन (currentcmd->cmdid) अणु
		हाल CMDID_SET_TXPOWEROWER_LEVEL:
			rtl92ee_phy_set_txघातer_level(hw, channel);
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
					  0xfffff00) | currentcmd->para2);

				rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath,
					      currentcmd->para1,
					      0x3ff,
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

अटल bool _rtl92ee_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
					      u32 cmdtableidx, u32 cmdtablesz,
					      क्रमागत swchnlcmd_id cmdid,
					      u32 para1, u32 para2, u32 msdelay)
अणु
	काष्ठा swchnlcmd *pcmd;

	अगर (cmdtable == शून्य) अणु
		WARN_ONCE(true, "rtl8192ee: cmdtable cannot be NULL.\n");
		वापस false;
	पूर्ण

	अगर (cmdtableidx >= cmdtablesz)
		वापस false;

	pcmd = cmdtable + cmdtableidx;
	pcmd->cmdid = cmdid;
	pcmd->para1 = para1;
	pcmd->para2 = para2;
	pcmd->msdelay = msdelay;
	वापस true;
पूर्ण

अटल u8 _rtl92ee_phy_path_a_iqk(काष्ठा ieee80211_hw *hw, bool config_pathb)
अणु
	u32 reg_eac, reg_e94, reg_e9c;
	u8 result = 0x00;
	/* path-A IQK setting */
	/* PA/PAD controlled by 0x0 */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_A, 0xdf, RFREG_OFFSET_MASK, 0x180);
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82140303);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x68160000);

	/*LO calibration setting*/
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x00462911);

	/*One shot, path A LOK & IQK*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, 0xe94, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, 0xe9c, MASKDWORD);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा
		वापस result;

	वापस result;
पूर्ण

अटल u8 _rtl92ee_phy_path_b_iqk(काष्ठा ieee80211_hw *hw)
अणु
	u32 reg_eac, reg_eb4, reg_ebc;
	u8 result = 0x00;

	/* PA/PAD controlled by 0x0 */
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_B, 0xdf, RFREG_OFFSET_MASK, 0x180);
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x00000000);
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);

	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x821403e2);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x68160000);

	/* LO calibration setting */
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x00462911);

	/*One shot, path B LOK & IQK*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xfa000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_eb4 = rtl_get_bbreg(hw, 0xeb4, MASKDWORD);
	reg_ebc = rtl_get_bbreg(hw, 0xebc, MASKDWORD);

	अगर (!(reg_eac & BIT(31)) &&
	    (((reg_eb4 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_ebc & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा
		वापस result;

	वापस result;
पूर्ण

अटल u8 _rtl92ee_phy_path_a_rx_iqk(काष्ठा ieee80211_hw *hw, bool config_pathb)
अणु
	u32 reg_eac, reg_e94, reg_e9c, reg_ea4 , u32temp;
	u8 result = 0x00;

	/*Get TXIMR Setting*/
	/*Modअगरy RX IQK mode table*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0000f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf117b);

	/*PA/PAD control by 0x56, and set = 0x0*/
	rtl_set_rfreg(hw, RF90_PATH_A, 0xdf, RFREG_OFFSET_MASK, 0x980);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x56, RFREG_OFFSET_MASK, 0x51000);

	/*enter IQK mode*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/*IQK Setting*/
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/*path a IQK setting*/
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82160c1f);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x68160c1f);

	/*LO calibration Setting*/
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a911);

	/*one shot,path A LOK & iqk*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xfa000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, RTX_POWER_BEFORE_IQK_A, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_A, MASKDWORD);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42)) अणु
		result |= 0x01;
	पूर्ण अन्यथा अणु
		/*	PA/PAD controlled by 0x0 */
		rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
		rtl_set_rfreg(hw, RF90_PATH_A, 0xdf, RFREG_OFFSET_MASK, 0x180);
		वापस result;
	पूर्ण

	u32temp = 0x80007C00 | (reg_e94 & 0x3FF0000)  |
		  ((reg_e9c & 0x3FF0000) >> 16);
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, u32temp);
	/*RX IQK*/
	/*Modअगरy RX IQK mode table*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);

	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0000f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf7ffa);

	/*PA/PAD control by 0x56, and set = 0x0*/
	rtl_set_rfreg(hw, RF90_PATH_A, 0xdf, RFREG_OFFSET_MASK, 0x980);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x56, RFREG_OFFSET_MASK, 0x51000);

	/*enter IQK mode*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/*IQK Setting*/
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/*path a IQK setting*/
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82160c1f);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28160c1f);

	/*LO calibration Setting*/
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a891);
	/*one shot,path A LOK & iqk*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xfa000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);
	/*Check failed*/
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_ea4 = rtl_get_bbreg(hw, RRX_POWER_BEFORE_IQK_A_2, MASKDWORD);

	/*PA/PAD controlled by 0x0*/
	/*leave IQK mode*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_A, 0xdf, RFREG_OFFSET_MASK, 0x180);
	/*अगर Tx is OK, check whether Rx is OK*/
	अगर (!(reg_eac & BIT(27)) &&
	    (((reg_ea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_eac & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;

	वापस result;
पूर्ण

अटल u8 _rtl92ee_phy_path_b_rx_iqk(काष्ठा ieee80211_hw *hw, bool config_pathb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 reg_eac, reg_eb4, reg_ebc, reg_ecc, reg_ec4, u32temp;
	u8 result = 0x00;

	/*Get TXIMR Setting*/
	/*Modअगरy RX IQK mode table*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);

	rtl_set_rfreg(hw, RF90_PATH_B, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0000f);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf117b);

	/*PA/PAD all off*/
	rtl_set_rfreg(hw, RF90_PATH_B, 0xdf, RFREG_OFFSET_MASK, 0x980);
	rtl_set_rfreg(hw, RF90_PATH_B, 0x56, RFREG_OFFSET_MASK, 0x51000);

	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/*IQK Setting*/
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/*path a IQK setting*/
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x18008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x38008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82160c1f);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x68160c1f);

	/*LO calibration Setting*/
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a911);

	/*one shot,path A LOK & iqk*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xfa000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	/* Check failed */
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_eb4 = rtl_get_bbreg(hw, RTX_POWER_BEFORE_IQK_B, MASKDWORD);
	reg_ebc = rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_B, MASKDWORD);

	अगर (!(reg_eac & BIT(31)) &&
	    (((reg_eb4 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_ebc & 0x03FF0000) >> 16) != 0x42)) अणु
		result |= 0x01;
	पूर्ण अन्यथा अणु
		/*	PA/PAD controlled by 0x0 */
		rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
		rtl_set_rfreg(hw, RF90_PATH_B, 0xdf, RFREG_OFFSET_MASK, 0x180);
		वापस result;
	पूर्ण

	u32temp = 0x80007C00 | (reg_eb4 & 0x3FF0000) |
		  ((reg_ebc & 0x3FF0000) >> 16);
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, u32temp);
	/*RX IQK*/
	/*Modअगरy RX IQK mode table*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);

	rtl_set_rfreg(hw, RF90_PATH_B, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0000f);
	rtl_set_rfreg(hw, RF90_PATH_B, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf7ffa);

	/*PA/PAD all off*/
	rtl_set_rfreg(hw, RF90_PATH_B, 0xdf, RFREG_OFFSET_MASK, 0x980);
	rtl_set_rfreg(hw, RF90_PATH_B, 0x56, RFREG_OFFSET_MASK, 0x51000);

	/*enter IQK mode*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/*IQK Setting*/
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/*path b IQK setting*/
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RTX_IQK_TONE_B, MASKDWORD, 0x38008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_B, MASKDWORD, 0x18008c1c);

	rtl_set_bbreg(hw, RTX_IQK_PI_B, MASKDWORD, 0x82160c1f);
	rtl_set_bbreg(hw, RRX_IQK_PI_B, MASKDWORD, 0x28160c1f);

	/*LO calibration Setting*/
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a891);
	/*one shot,path A LOK & iqk*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xfa000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);
	/*Check failed*/
	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_ec4 = rtl_get_bbreg(hw, RRX_POWER_BEFORE_IQK_B_2, MASKDWORD);
	reg_ecc = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_B_2, MASKDWORD);
	/*PA/PAD controlled by 0x0*/
	/*leave IQK mode*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_B, 0xdf, RFREG_OFFSET_MASK, 0x180);
	/*अगर Tx is OK, check whether Rx is OK*/
	अगर (!(reg_eac & BIT(30)) &&
	    (((reg_ec4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_ecc & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा
		rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "Path B Rx IQK fail!!\n");

	वापस result;
पूर्ण

अटल व्योम _rtl92ee_phy_path_a_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
						bool b_iqk_ok, दीर्घ result[][8],
						u8 final_candidate,
						bool btxonly)
अणु
	u32 oldval_0, x, tx0_a, reg;
	दीर्घ y, tx0_c;

	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (b_iqk_ok) अणु
		oldval_0 = (rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
					  MASKDWORD) >> 22) & 0x3FF;
		x = result[final_candidate][0];
		अगर ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;
		tx0_a = (x * oldval_0) >> 8;
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x3FF, tx0_a);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(31),
			      ((x * oldval_0 >> 7) & 0x1));
		y = result[final_candidate][1];
		अगर ((y & 0x00000200) != 0)
			y = y | 0xFFFFFC00;
		tx0_c = (y * oldval_0) >> 8;
		rtl_set_bbreg(hw, ROFDM0_XCTXAFE, 0xF0000000,
			      ((tx0_c & 0x3C0) >> 6));
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x003F0000,
			      (tx0_c & 0x3F));
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(29),
			      ((y * oldval_0 >> 7) & 0x1));

		अगर (btxonly)
			वापस;

		reg = result[final_candidate][2];
		rtl_set_bbreg(hw, ROFDM0_XARXIQIMBALANCE, 0x3FF, reg);

		reg = result[final_candidate][3] & 0x3F;
		rtl_set_bbreg(hw, ROFDM0_XARXIQIMBALANCE, 0xFC00, reg);

		reg = (result[final_candidate][3] >> 6) & 0xF;
		rtl_set_bbreg(hw, ROFDM0_RXIQEXTANTA, 0xF0000000, reg);
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_phy_path_b_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
						bool b_iqk_ok, दीर्घ result[][8],
						u8 final_candidate,
						bool btxonly)
अणु
	u32 oldval_1, x, tx1_a, reg;
	दीर्घ y, tx1_c;

	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (b_iqk_ok) अणु
		oldval_1 = (rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
					  MASKDWORD) >> 22) & 0x3FF;
		x = result[final_candidate][4];
		अगर ((x & 0x00000200) != 0)
			x = x | 0xFFFFFC00;
		tx1_a = (x * oldval_1) >> 8;
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x3FF, tx1_a);
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
		rtl_set_bbreg(hw, ROFDM0_AGCRSSITABLE, 0xF0000000, reg);
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_phy_save_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					     u32 *addareg, u32 *addabackup,
					     u32 रेजिस्टरnum)
अणु
	u32 i;

	क्रम (i = 0; i < रेजिस्टरnum; i++)
		addabackup[i] = rtl_get_bbreg(hw, addareg[i], MASKDWORD);
पूर्ण

अटल व्योम _rtl92ee_phy_save_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					    u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		macbackup[i] = rtl_पढ़ो_byte(rtlpriv, macreg[i]);

	macbackup[i] = rtl_पढ़ो_dword(rtlpriv, macreg[i]);
पूर्ण

अटल व्योम _rtl92ee_phy_reload_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					       u32 *addareg, u32 *addabackup,
					       u32 regiesternum)
अणु
	u32 i;

	क्रम (i = 0; i < regiesternum; i++)
		rtl_set_bbreg(hw, addareg[i], MASKDWORD, addabackup[i]);
पूर्ण

अटल व्योम _rtl92ee_phy_reload_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					      u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		rtl_ग_लिखो_byte(rtlpriv, macreg[i], (u8)macbackup[i]);
	rtl_ग_लिखो_dword(rtlpriv, macreg[i], macbackup[i]);
पूर्ण

अटल व्योम _rtl92ee_phy_path_adda_on(काष्ठा ieee80211_hw *hw, u32 *addareg,
				      bool is_patha_on, bool is2t)
अणु
	u32 i;

	क्रम (i = 0; i < IQK_ADDA_REG_NUM; i++)
		rtl_set_bbreg(hw, addareg[i], MASKDWORD, 0x0fc01616);
पूर्ण

अटल व्योम _rtl92ee_phy_mac_setting_calibration(काष्ठा ieee80211_hw *hw,
						 u32 *macreg, u32 *macbackup)
अणु
	rtl_set_bbreg(hw, 0x520, 0x00ff0000, 0xff);
पूर्ण

अटल व्योम _rtl92ee_phy_path_a_standby(काष्ठा ieee80211_hw *hw)
अणु
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x0);
	rtl_set_rfreg(hw, RF90_PATH_A, 0, RFREG_OFFSET_MASK, 0x10000);
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
पूर्ण

अटल bool _rtl92ee_phy_simularity_compare(काष्ठा ieee80211_hw *hw,
					    दीर्घ result[][8], u8 c1, u8 c2)
अणु
	u32 i, j, dअगरf, simularity_biपंचांगap, bound;

	u8 final_candidate[2] = अणु 0xFF, 0xFF पूर्ण;
	bool bresult = true/*, is2t = true*/;
	s32 पंचांगp1, पंचांगp2;

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
			पूर्ण अन्यथा अणु
				simularity_biपंचांगap |= (1 << i);
			पूर्ण
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
	पूर्ण
	अगर (!(simularity_biपंचांगap & 0x03)) अणु/*path A TX OK*/
		क्रम (i = 0; i < 2; i++)
			result[3][i] = result[c1][i];
	पूर्ण
	अगर (!(simularity_biपंचांगap & 0x0c)) अणु/*path A RX OK*/
		क्रम (i = 2; i < 4; i++)
			result[3][i] = result[c1][i];
	पूर्ण
	अगर (!(simularity_biपंचांगap & 0x30)) अणु/*path B TX OK*/
		क्रम (i = 4; i < 6; i++)
			result[3][i] = result[c1][i];
	पूर्ण
	अगर (!(simularity_biपंचांगap & 0xc0)) अणु/*path B RX OK*/
		क्रम (i = 6; i < 8; i++)
			result[3][i] = result[c1][i];
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम _rtl92ee_phy_iq_calibrate(काष्ठा ieee80211_hw *hw,
				      दीर्घ result[][8], u8 t, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 i;
	u8 patha_ok, pathb_ok;
	u8 पंचांगp_0xc50 = (u8)rtl_get_bbreg(hw, 0xc50, MASKBYTE0);
	u8 पंचांगp_0xc58 = (u8)rtl_get_bbreg(hw, 0xc58, MASKBYTE0);
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
		0x864, 0x800
	पूर्ण;
	स्थिर u32 retrycount = 2;

	अगर (t == 0) अणु
		_rtl92ee_phy_save_adda_रेजिस्टरs(hw, adda_reg,
						 rtlphy->adda_backup,
						 IQK_ADDA_REG_NUM);
		_rtl92ee_phy_save_mac_रेजिस्टरs(hw, iqk_mac_reg,
						rtlphy->iqk_mac_backup);
		_rtl92ee_phy_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
						 rtlphy->iqk_bb_backup,
						 IQK_BB_REG_NUM);
	पूर्ण

	_rtl92ee_phy_path_adda_on(hw, adda_reg, true, is2t);

	/*BB setting*/
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BIT(24), 0x00);
	rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKDWORD, 0x03a05600);
	rtl_set_bbreg(hw, ROFDM0_TRMUXPAR, MASKDWORD, 0x000800e4);
	rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW, MASKDWORD, 0x22208200);

	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, BIT(10), 0x01);
	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, BIT(26), 0x01);
	rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE, BIT(10), 0x01);
	rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE, BIT(10), 0x01);

	_rtl92ee_phy_mac_setting_calibration(hw, iqk_mac_reg,
					     rtlphy->iqk_mac_backup);
	/* Page B init*/
	/* IQ calibration setting*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	क्रम (i = 0 ; i < retrycount ; i++) अणु
		patha_ok = _rtl92ee_phy_path_a_iqk(hw, is2t);

		अगर (patha_ok == 0x01) अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
				"Path A Tx IQK Success!!\n");
			result[t][0] = (rtl_get_bbreg(hw,
						      RTX_POWER_BEFORE_IQK_A,
						      MASKDWORD) & 0x3FF0000)
						      >> 16;
			result[t][1] = (rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_A,
						      MASKDWORD) & 0x3FF0000)
						      >> 16;
			अवरोध;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
			"Path A Tx IQK Fail!!, ret = 0x%x\n",
			patha_ok);
	पूर्ण

	क्रम (i = 0 ; i < retrycount ; i++) अणु
		patha_ok = _rtl92ee_phy_path_a_rx_iqk(hw, is2t);

		अगर (patha_ok == 0x03) अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
				"Path A Rx IQK Success!!\n");
			result[t][2] = (rtl_get_bbreg(hw,
						      RRX_POWER_BEFORE_IQK_A_2,
						      MASKDWORD) & 0x3FF0000)
						      >> 16;
			result[t][3] = (rtl_get_bbreg(hw,
						      RRX_POWER_AFTER_IQK_A_2,
						      MASKDWORD) & 0x3FF0000)
						      >> 16;
			अवरोध;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
			"Path A Rx IQK Fail!!, ret = 0x%x\n",
			patha_ok);
	पूर्ण

	अगर (0x00 == patha_ok)
		rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
			"Path A IQK failed!!, ret = 0\n");
	अगर (is2t) अणु
		_rtl92ee_phy_path_a_standby(hw);
		/* Turn Path B ADDA on */
		_rtl92ee_phy_path_adda_on(hw, adda_reg, false, is2t);

		/* IQ calibration setting */
		rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);
		rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
		rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

		क्रम (i = 0 ; i < retrycount ; i++) अणु
			pathb_ok = _rtl92ee_phy_path_b_iqk(hw);
			अगर (pathb_ok == 0x01) अणु
				rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
					"Path B Tx IQK Success!!\n");
				result[t][4] = (rtl_get_bbreg(hw,
							RTX_POWER_BEFORE_IQK_B,
							MASKDWORD) & 0x3FF0000)
							>> 16;
				result[t][5] = (rtl_get_bbreg(hw,
							RTX_POWER_AFTER_IQK_B,
							MASKDWORD) & 0x3FF0000)
							>> 16;
				अवरोध;
			पूर्ण
			rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
				"Path B Tx IQK Fail!!, ret = 0x%x\n",
				pathb_ok);
		पूर्ण

		क्रम (i = 0 ; i < retrycount ; i++) अणु
			pathb_ok = _rtl92ee_phy_path_b_rx_iqk(hw, is2t);
			अगर (pathb_ok == 0x03) अणु
				rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
					"Path B Rx IQK Success!!\n");
				result[t][6] = (rtl_get_bbreg(hw,
						       RRX_POWER_BEFORE_IQK_B_2,
						       MASKDWORD) & 0x3FF0000)
						       >> 16;
				result[t][7] = (rtl_get_bbreg(hw,
						       RRX_POWER_AFTER_IQK_B_2,
						       MASKDWORD) & 0x3FF0000)
						       >> 16;
				अवरोध;
			पूर्ण
			rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
				"Path B Rx IQK Fail!!, ret = 0x%x\n",
				pathb_ok);
		पूर्ण

		अगर (0x00 == pathb_ok)
			rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
				"Path B IQK failed!!, ret = 0\n");
	पूर्ण
	/* Back to BB mode, load original value */
	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
		"IQK:Back to BB mode, load original value!\n");
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0);

	अगर (t != 0) अणु
		/* Reload ADDA घातer saving parameters */
		_rtl92ee_phy_reload_adda_रेजिस्टरs(hw, adda_reg,
						   rtlphy->adda_backup,
						   IQK_ADDA_REG_NUM);

		/* Reload MAC parameters */
		_rtl92ee_phy_reload_mac_रेजिस्टरs(hw, iqk_mac_reg,
						  rtlphy->iqk_mac_backup);

		_rtl92ee_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
						   rtlphy->iqk_bb_backup,
						   IQK_BB_REG_NUM);

		/* Restore RX initial gain */
		rtl_set_bbreg(hw, 0xc50, MASKBYTE0, 0x50);
		rtl_set_bbreg(hw, 0xc50, MASKBYTE0, पंचांगp_0xc50);
		अगर (is2t) अणु
			rtl_set_bbreg(hw, 0xc50, MASKBYTE0, 0x50);
			rtl_set_bbreg(hw, 0xc58, MASKBYTE0, पंचांगp_0xc58);
		पूर्ण

		/* load 0xe30 IQC शेष value */
		rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x01008c00);
		rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x01008c00);
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_phy_lc_calibrate(काष्ठा ieee80211_hw *hw, bool is2t)
अणु
	u8 पंचांगpreg;
	u32 rf_a_mode = 0, rf_b_mode = 0, lc_cal;
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
	lc_cal = rtl_get_rfreg(hw, RF90_PATH_A, 0x18, MASK12BITS);

	rtl_set_rfreg(hw, RF90_PATH_A, 0x18, MASK12BITS, lc_cal | 0x08000);

	mdelay(100);

	अगर ((पंचांगpreg & 0x70) != 0) अणु
		rtl_ग_लिखो_byte(rtlpriv, 0xd03, पंचांगpreg);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x00, MASK12BITS, rf_a_mode);

		अगर (is2t)
			rtl_set_rfreg(hw, RF90_PATH_B, 0x00, MASK12BITS,
				      rf_b_mode);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
	पूर्ण
पूर्ण

अटल व्योम _rtl92ee_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw,
					   bool bमुख्य, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "\n");

	अगर (is_hal_stop(rtlhal)) अणु
		u8 u1bपंचांगp;

		u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_LEDCFG0);
		rtl_ग_लिखो_byte(rtlpriv, REG_LEDCFG0, u1bपंचांगp | BIT(7));
		rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(13), 0x01);
	पूर्ण
	अगर (is2t) अणु
		अगर (bमुख्य)
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(6), 0x1);
		अन्यथा
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(6), 0x2);
	पूर्ण अन्यथा अणु
		rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, BIT(8) | BIT(9), 0);
		rtl_set_bbreg(hw, 0x914, MASKLWORD, 0x0201);

		/* We use the RF definition of MAIN and AUX,
		 * left antenna and right antenna repectively.
		 * Default output at AUX.
		 */
		अगर (bमुख्य) अणु
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE,
				      BIT(14) | BIT(13) | BIT(12), 0);
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(4) | BIT(3), 0);
			अगर (rtlefuse->antenna_भाग_प्रकारype == CGCS_RX_HW_ANTDIV)
				rtl_set_bbreg(hw, RCONFIG_RAM64x16, BIT(31), 0);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE,
				      BIT(14) | BIT(13) | BIT(12), 1);
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(5) | BIT(4) | BIT(3), 1);
			अगर (rtlefuse->antenna_भाग_प्रकारype == CGCS_RX_HW_ANTDIV)
				rtl_set_bbreg(hw, RCONFIG_RAM64x16, BIT(31), 1);
		पूर्ण
	पूर्ण
पूर्ण

#अघोषित IQK_ADDA_REG_NUM
#अघोषित IQK_DELAY_TIME

अटल u8 rtl92ee_get_rightchnlplace_क्रम_iqk(u8 chnl)
अणु
	u8 channel_all[59] = अणु
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58,
		60, 62, 64, 100, 102, 104, 106, 108, 110, 112,
		114, 116, 118, 120, 122, 124, 126, 128,	130,
		132, 134, 136, 138, 140, 149, 151, 153, 155,
		157, 159, 161, 163, 165
	पूर्ण;
	u8 place = chnl;

	अगर (chnl > 14) अणु
		क्रम (place = 14; place < माप(channel_all); place++) अणु
			अगर (channel_all[place] == chnl)
				वापस place - 13;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम rtl92ee_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	दीर्घ result[4][8];
	u8 i, final_candidate;
	bool b_patha_ok, b_pathb_ok;
	दीर्घ reg_e94, reg_e9c, reg_ea4;
	दीर्घ reg_eb4, reg_ebc, reg_ec4;
	bool is12simular, is13simular, is23simular;
	u8 idx;
	u32 iqk_bb_reg[IQK_BB_REG_NUM] = अणु
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

	अगर (b_recovery) अणु
		_rtl92ee_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
						   rtlphy->iqk_bb_backup, 9);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		result[0][i] = 0;
		result[1][i] = 0;
		result[2][i] = 0;

		अगर ((i == 0) || (i == 2) || (i == 4)  || (i == 6))
			result[3][i] = 0x100;
		अन्यथा
			result[3][i] = 0;
	पूर्ण
	final_candidate = 0xff;
	b_patha_ok = false;
	b_pathb_ok = false;
	is12simular = false;
	is23simular = false;
	is13simular = false;
	क्रम (i = 0; i < 3; i++) अणु
		_rtl92ee_phy_iq_calibrate(hw, result, i, true);
		अगर (i == 1) अणु
			is12simular = _rtl92ee_phy_simularity_compare(hw,
								      result,
								      0, 1);
			अगर (is12simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == 2) अणु
			is13simular = _rtl92ee_phy_simularity_compare(hw,
								      result,
								      0, 2);
			अगर (is13simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
			is23simular = _rtl92ee_phy_simularity_compare(hw,
								      result,
								      1, 2);
			अगर (is23simular)
				final_candidate = 1;
			अन्यथा
				final_candidate = 3;
		पूर्ण
	पूर्ण

	reg_e94 = result[3][0];
	reg_e9c = result[3][1];
	reg_ea4 = result[3][2];
	reg_eb4 = result[3][4];
	reg_ebc = result[3][5];
	reg_ec4 = result[3][6];

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
		_rtl92ee_phy_path_a_fill_iqk_matrix(hw, b_patha_ok, result,
						    final_candidate,
						    (reg_ea4 == 0));

	_rtl92ee_phy_path_b_fill_iqk_matrix(hw, b_pathb_ok, result,
					    final_candidate,
					    (reg_ec4 == 0));

	idx = rtl92ee_get_rightchnlplace_क्रम_iqk(rtlphy->current_channel);

	/* To Fix BSOD when final_candidate is 0xff */
	अगर (final_candidate < 4) अणु
		क्रम (i = 0; i < IQK_MATRIX_REG_NUM; i++)
			rtlphy->iqk_matrix[idx].value[0][i] =
				result[final_candidate][i];

		rtlphy->iqk_matrix[idx].iqk_करोne = true;
	पूर्ण
	_rtl92ee_phy_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
					 rtlphy->iqk_bb_backup, 9);
पूर्ण

व्योम rtl92ee_phy_lc_calibrate(काष्ठा ieee80211_hw *hw)
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

	_rtl92ee_phy_lc_calibrate(hw, false);

	rtlphy->lck_inprogress = false;
पूर्ण

व्योम rtl92ee_phy_ap_calibrate(काष्ठा ieee80211_hw *hw, s8 delta)
अणु
पूर्ण

व्योम rtl92ee_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य)
अणु
	_rtl92ee_phy_set_rfpath_चयन(hw, bमुख्य, false);
पूर्ण

bool rtl92ee_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype)
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
			rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
				"[IO CMD] Pause DM before scan.\n");
			postprocessing = true;
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_ERR, DBG_LOUD,
				"switch case %#x not processed\n", iotype);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (false);
	अगर (postprocessing && !rtlphy->set_io_inprogress) अणु
		rtlphy->set_io_inprogress = true;
		rtlphy->current_io_type = iotype;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
	rtl92ee_phy_set_io(hw);
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE, "IO Type(%#x)\n", iotype);
	वापस true;
पूर्ण

अटल व्योम rtl92ee_phy_set_io(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा dig_t *dm_dig = &rtlpriv->dm_digtable;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"--->Cmd(%#x), set_io_inprogress(%d)\n",
		rtlphy->current_io_type, rtlphy->set_io_inprogress);
	चयन (rtlphy->current_io_type) अणु
	हाल IO_CMD_RESUME_DM_BY_SCAN:
		rtl92ee_dm_ग_लिखो_dig(hw, rtlphy->initgain_backup.xaagccore1);
		rtl92ee_dm_ग_लिखो_cck_cca_thres(hw, rtlphy->initgain_backup.cca);
		rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE, "no set txpower\n");
		rtl92ee_phy_set_txघातer_level(hw, rtlphy->current_channel);
		अवरोध;
	हाल IO_CMD_PAUSE_BAND0_DM_BY_SCAN:
		/* 8192eebt */
		rtlphy->initgain_backup.xaagccore1 = dm_dig->cur_igvalue;
		rtl92ee_dm_ग_लिखो_dig(hw, 0x17);
		rtlphy->initgain_backup.cca = dm_dig->cur_cck_cca_thres;
		rtl92ee_dm_ग_लिखो_cck_cca_thres(hw, 0x40);
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

अटल व्योम rtl92ee_phy_set_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	/*rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x00);*/
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
पूर्ण

अटल व्योम _rtl92ee_phy_set_rf_sleep(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);

	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x22);
पूर्ण

अटल bool _rtl92ee_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
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
				"Set ERFON sleeping:%d ms\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_sleep_jअगरfies));
			ppsc->last_awake_jअगरfies = jअगरfies;
			rtl92ee_phy_set_rf_on(hw);
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
					"\n ERFSLEEP: %d times TcbBusyQueue[%d] = %d !\n",
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
		_rtl92ee_phy_set_rf_sleep(hw);
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

bool rtl92ee_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				    क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	bool bresult = false;

	अगर (rfpwr_state == ppsc->rfpwr_state)
		वापस bresult;
	bresult = _rtl92ee_phy_set_rf_घातer_state(hw, rfpwr_state);
	वापस bresult;
पूर्ण
