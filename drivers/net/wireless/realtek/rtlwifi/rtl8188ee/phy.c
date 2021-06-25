<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2013  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../ps.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "table.h"

अटल u32 _rtl88e_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
				      क्रमागत radio_path rfpath, u32 offset);
अटल व्योम _rtl88e_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
					क्रमागत radio_path rfpath, u32 offset,
					u32 data);
अटल u32 _rtl88e_phy_calculate_bit_shअगरt(u32 biपंचांगask)
अणु
	u32 i = ffs(biपंचांगask);

	वापस i ? i - 1 : 32;
पूर्ण
अटल bool _rtl88e_phy_bb8188e_config_parafile(काष्ठा ieee80211_hw *hw);
अटल bool _rtl88e_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw);
अटल bool phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
					  u8 configtype);
अटल bool phy_config_bb_with_pghdr(काष्ठा ieee80211_hw *hw,
				     u8 configtype);
अटल व्योम _rtl88e_phy_init_bb_rf_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw);
अटल bool _rtl88e_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
					     u32 cmdtableidx, u32 cmdtablesz,
					     क्रमागत swchnlcmd_id cmdid, u32 para1,
					     u32 para2, u32 msdelay);
अटल bool _rtl88e_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
					     u8 channel, u8 *stage, u8 *step,
					     u32 *delay);

अटल दीर्घ _rtl88e_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
					 क्रमागत wireless_mode wirelessmode,
					 u8 txpwridx);
अटल व्योम rtl88ee_phy_set_rf_on(काष्ठा ieee80211_hw *hw);
अटल व्योम rtl88e_phy_set_io(काष्ठा ieee80211_hw *hw);

u32 rtl88e_phy_query_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 वापसvalue, originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x)\n", regaddr, biपंचांगask);
	originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
	bitshअगरt = _rtl88e_phy_calculate_bit_shअगरt(biपंचांगask);
	वापसvalue = (originalvalue & biपंचांगask) >> bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"BBR MASK=0x%x Addr[0x%x]=0x%x\n", biपंचांगask,
		regaddr, originalvalue);

	वापस वापसvalue;

पूर्ण

व्योम rtl88e_phy_set_bb_reg(काष्ठा ieee80211_hw *hw,
			   u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);

	अगर (biपंचांगask != MASKDWORD) अणु
		originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
		bitshअगरt = _rtl88e_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((originalvalue & (~biपंचांगask)) | (data << bitshअगरt));
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, regaddr, data);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);
पूर्ण

u32 rtl88e_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			    क्रमागत radio_path rfpath, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, पढ़ोback_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x)\n",
		regaddr, rfpath, biपंचांगask);

	spin_lock(&rtlpriv->locks.rf_lock);


	original_value = _rtl88e_phy_rf_serial_पढ़ो(hw, rfpath, regaddr);
	bitshअगरt = _rtl88e_phy_calculate_bit_shअगरt(biपंचांगask);
	पढ़ोback_value = (original_value & biपंचांगask) >> bitshअगरt;

	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x), original_value(%#x)\n",
		regaddr, rfpath, biपंचांगask, original_value);
	वापस पढ़ोback_value;
पूर्ण

व्योम rtl88e_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
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
			original_value = _rtl88e_phy_rf_serial_पढ़ो(hw,
								    rfpath,
								    regaddr);
			bitshअगरt = _rtl88e_phy_calculate_bit_shअगरt(biपंचांगask);
			data =
			    ((original_value & (~biपंचांगask)) |
			     (data << bitshअगरt));
		पूर्ण

	_rtl88e_phy_rf_serial_ग_लिखो(hw, rfpath, regaddr, data);


	spin_unlock(&rtlpriv->locks.rf_lock);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);
पूर्ण

अटल u32 _rtl88e_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
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
	udelay(10);
	rtl_set_bbreg(hw, pphyreg->rfhssi_para2, MASKDWORD, पंचांगpदीर्घ2);
	udelay(120);
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

अटल व्योम _rtl88e_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
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
		"RFW-%d Addr[0x%x]=0x%x\n",
		rfpath, pphyreg->rf3wire_offset, data_and_addr);
पूर्ण

bool rtl88e_phy_mac_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool rtstatus = _rtl88e_phy_config_mac_with_headerfile(hw);

	rtl_ग_लिखो_byte(rtlpriv, 0x04CA, 0x0B);
	वापस rtstatus;
पूर्ण

bool rtl88e_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	bool rtstatus = true;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 regval;
	u8 b_reg_hwparafile = 1;
	u32 पंचांगp;
	_rtl88e_phy_init_bb_rf_रेजिस्टर_definition(hw);
	regval = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN,
		       regval | BIT(13) | BIT(0) | BIT(1));

	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, RF_EN | RF_RSTB | RF_SDMRSTB);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN,
		       FEN_PPLL | FEN_PCIEA | FEN_DIO_PCIE |
		       FEN_BB_GLB_RSTN | FEN_BBRSTB);
	पंचांगp = rtl_पढ़ो_dword(rtlpriv, 0x4c);
	rtl_ग_लिखो_dword(rtlpriv, 0x4c, पंचांगp | BIT(23));
	अगर (b_reg_hwparafile == 1)
		rtstatus = _rtl88e_phy_bb8188e_config_parafile(hw);
	वापस rtstatus;
पूर्ण

bool rtl88e_phy_rf_config(काष्ठा ieee80211_hw *hw)
अणु
	वापस rtl88e_phy_rf6052_config(hw);
पूर्ण

अटल bool _rtl88e_check_condition(काष्ठा ieee80211_hw *hw,
				    स्थिर u32  condition)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 _board = rtlefuse->board_type; /*need efuse define*/
	u32 _पूर्णांकerface = rtlhal->पूर्णांकerface;
	u32 _platक्रमm = 0x08;/*SupportPlatक्रमm */
	u32 cond;

	अगर (condition == 0xCDCDCDCD)
		वापस true;

	cond = condition & 0xFF;
	अगर ((_board & cond) == 0 && cond != 0x1F)
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

अटल व्योम _rtl8188e_config_rf_reg(काष्ठा ieee80211_hw *hw, u32 addr,
				    u32 data, क्रमागत radio_path rfpath,
				    u32 regaddr)
अणु
	अगर (addr == 0xffe) अणु
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
		rtl_set_rfreg(hw, rfpath, regaddr,
			      RFREG_OFFSET_MASK,
			      data);
		udelay(1);
	पूर्ण
पूर्ण

अटल व्योम _rtl8188e_config_rf_radio_a(काष्ठा ieee80211_hw *hw,
					u32 addr, u32 data)
अणु
	u32 content = 0x1000; /*RF Content: radio_a_txt*/
	u32 maskक्रमphyset = (u32)(content & 0xE000);

	_rtl8188e_config_rf_reg(hw, addr, data, RF90_PATH_A,
		addr | maskक्रमphyset);
पूर्ण

अटल व्योम _rtl8188e_config_bb_reg(काष्ठा ieee80211_hw *hw,
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

अटल bool _rtl88e_phy_bb8188e_config_parafile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus;

	rtstatus = phy_config_bb_with_headerfile(hw, BASEBAND_CONFIG_PHY_REG);
	अगर (!rtstatus) अणु
		pr_err("Write BB Reg Fail!!\n");
		वापस false;
	पूर्ण

	अगर (!rtlefuse->स्वतःload_failflag) अणु
		rtlphy->pwrgroup_cnt = 0;
		rtstatus =
		  phy_config_bb_with_pghdr(hw, BASEBAND_CONFIG_PHY_REG);
	पूर्ण
	अगर (!rtstatus) अणु
		pr_err("BB_PG Reg Fail!!\n");
		वापस false;
	पूर्ण
	rtstatus =
	  phy_config_bb_with_headerfile(hw, BASEBAND_CONFIG_AGC_TAB);
	अगर (!rtstatus) अणु
		pr_err("AGC Table Fail\n");
		वापस false;
	पूर्ण
	rtlphy->cck_high_घातer =
	  (bool)(rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, 0x200));

	वापस true;
पूर्ण

अटल bool _rtl88e_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;
	u32 arraylength;
	u32 *ptrarray;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Read Rtl8188EMACPHY_Array\n");
	arraylength = RTL8188EEMAC_1T_ARRAYLEN;
	ptrarray = RTL8188EEMAC_1T_ARRAY;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Img:RTL8188EEMAC_1T_ARRAY LEN %d\n", arraylength);
	क्रम (i = 0; i < arraylength; i = i + 2)
		rtl_ग_लिखो_byte(rtlpriv, ptrarray[i], (u8)ptrarray[i + 1]);
	वापस true;
पूर्ण

#घोषणा READ_NEXT_PAIR(v1, v2, i)			\
	करो अणु						\
		i += 2; v1 = array_table[i];		\
		v2 = array_table[i+1];			\
	पूर्ण जबतक (0)

अटल व्योम handle_branch1(काष्ठा ieee80211_hw *hw, u16 arraylen,
			   u32 *array_table)
अणु
	u32 v1;
	u32 v2;
	पूर्णांक i;

	क्रम (i = 0; i < arraylen; i = i + 2) अणु
		v1 = array_table[i];
		v2 = array_table[i+1];
		अगर (v1 < 0xcdcdcdcd) अणु
			_rtl8188e_config_bb_reg(hw, v1, v2);
		पूर्ण अन्यथा अणु /*This line is the start line of branch.*/
			/* to protect READ_NEXT_PAIR not overrun */
			अगर (i >= arraylen - 2)
				अवरोध;

			अगर (!_rtl88e_check_condition(hw, array_table[i])) अणु
				/*Discard the following (offset, data) pairs*/
				READ_NEXT_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < arraylen - 2)
					READ_NEXT_PAIR(v1, v2, i);
				i -= 2; /* prevent from क्रम-loop += 2*/
			पूर्ण अन्यथा अणु /* Configure matched pairs and skip
				  * to end of अगर-अन्यथा.
				  */
				READ_NEXT_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < arraylen - 2) अणु
					_rtl8188e_config_bb_reg(hw, v1, v2);
					READ_NEXT_PAIR(v1, v2, i);
				पूर्ण

				जबतक (v2 != 0xDEAD && i < arraylen - 2)
					READ_NEXT_PAIR(v1, v2, i);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम handle_branch2(काष्ठा ieee80211_hw *hw, u16 arraylen,
			   u32 *array_table)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 v1;
	u32 v2;
	पूर्णांक i;

	क्रम (i = 0; i < arraylen; i = i + 2) अणु
		v1 = array_table[i];
		v2 = array_table[i+1];
		अगर (v1 < 0xCDCDCDCD) अणु
			rtl_set_bbreg(hw, array_table[i], MASKDWORD,
				      array_table[i + 1]);
			udelay(1);
			जारी;
		पूर्ण अन्यथा अणु /*This line is the start line of branch.*/
			/* to protect READ_NEXT_PAIR not overrun */
			अगर (i >= arraylen - 2)
				अवरोध;

			अगर (!_rtl88e_check_condition(hw, array_table[i])) अणु
				/*Discard the following (offset, data) pairs*/
				READ_NEXT_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < arraylen - 2)
					READ_NEXT_PAIR(v1, v2, i);
				i -= 2; /* prevent from क्रम-loop += 2*/
			पूर्ण अन्यथा अणु /* Configure matched pairs and skip
				  * to end of अगर-अन्यथा.
				  */
				READ_NEXT_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD && i < arraylen - 2) अणु
					rtl_set_bbreg(hw, array_table[i],
						      MASKDWORD,
						      array_table[i + 1]);
					udelay(1);
					READ_NEXT_PAIR(v1, v2, i);
				पूर्ण

				जबतक (v2 != 0xDEAD && i < arraylen - 2)
					READ_NEXT_PAIR(v1, v2, i);
			पूर्ण
		पूर्ण
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"The agctab_array_table[0] is %x Rtl818EEPHY_REGArray[1] is %x\n",
			array_table[i], array_table[i + 1]);
	पूर्ण
पूर्ण

अटल bool phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
					  u8 configtype)
अणु
	u32 *array_table;
	u16 arraylen;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		arraylen = RTL8188EEPHY_REG_1TARRAYLEN;
		array_table = RTL8188EEPHY_REG_1TARRAY;
		handle_branch1(hw, arraylen, array_table);
	पूर्ण अन्यथा अगर (configtype == BASEBAND_CONFIG_AGC_TAB) अणु
		arraylen = RTL8188EEAGCTAB_1TARRAYLEN;
		array_table = RTL8188EEAGCTAB_1TARRAY;
		handle_branch2(hw, arraylen, array_table);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम store_pwrindex_rate_offset(काष्ठा ieee80211_hw *hw,
				       u32 regaddr, u32 biपंचांगask,
				       u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	पूर्णांक count = rtlphy->pwrgroup_cnt;

	अगर (regaddr == RTXAGC_A_RATE18_06) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][0] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][0] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][0]);
	पूर्ण
	अगर (regaddr == RTXAGC_A_RATE54_24) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][1] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][1] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][1]);
	पूर्ण
	अगर (regaddr == RTXAGC_A_CCK1_MCS32) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][6] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][6] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][6]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && biपंचांगask == 0xffffff00) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][7] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][7] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][7]);
	पूर्ण
	अगर (regaddr == RTXAGC_A_MCS03_MCS00) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][2] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][2] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][2]);
	पूर्ण
	अगर (regaddr == RTXAGC_A_MCS07_MCS04) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][3] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][3] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][3]);
	पूर्ण
	अगर (regaddr == RTXAGC_A_MCS11_MCS08) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][4] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][4] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][4]);
	पूर्ण
	अगर (regaddr == RTXAGC_A_MCS15_MCS12) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][5] = data;
		अगर (get_rf_type(rtlphy) == RF_1T1R) अणु
			count++;
			rtlphy->pwrgroup_cnt = count;
		पूर्ण
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][5] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][5]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_RATE18_06) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][8] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][8] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][8]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_RATE54_24) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][9] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][9] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][9]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_CCK1_55_MCS32) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][14] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][14] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][14]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && biपंचांगask == 0x000000ff) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][15] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][15] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][15]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_MCS03_MCS00) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][10] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][10] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][10]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_MCS07_MCS04) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][11] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][11] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][11]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_MCS11_MCS08) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][12] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][12] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][12]);
	पूर्ण
	अगर (regaddr == RTXAGC_B_MCS15_MCS12) अणु
		rtlphy->mcs_txpwrlevel_origoffset[count][13] = data;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
			"MCSTxPowerLevelOriginalOffset[%d][13] = 0x%x\n",
			count,
			rtlphy->mcs_txpwrlevel_origoffset[count][13]);
		अगर (get_rf_type(rtlphy) != RF_1T1R) अणु
			count++;
			rtlphy->pwrgroup_cnt = count;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool phy_config_bb_with_pghdr(काष्ठा ieee80211_hw *hw, u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;
	u32 *phy_reg_page;
	u16 phy_reg_page_len;
	u32 v1 = 0, v2 = 0;

	phy_reg_page_len = RTL8188EEPHY_REG_ARRAY_PGLEN;
	phy_reg_page = RTL8188EEPHY_REG_ARRAY_PG;

	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_reg_page_len; i = i + 3) अणु
			v1 = phy_reg_page[i];
			v2 = phy_reg_page[i+1];

			अगर (v1 < 0xcdcdcdcd) अणु
				अगर (phy_reg_page[i] == 0xfe)
					mdelay(50);
				अन्यथा अगर (phy_reg_page[i] == 0xfd)
					mdelay(5);
				अन्यथा अगर (phy_reg_page[i] == 0xfc)
					mdelay(1);
				अन्यथा अगर (phy_reg_page[i] == 0xfb)
					udelay(50);
				अन्यथा अगर (phy_reg_page[i] == 0xfa)
					udelay(5);
				अन्यथा अगर (phy_reg_page[i] == 0xf9)
					udelay(1);

				store_pwrindex_rate_offset(hw, phy_reg_page[i],
							   phy_reg_page[i + 1],
							   phy_reg_page[i + 2]);
				जारी;
			पूर्ण अन्यथा अणु
				अगर (!_rtl88e_check_condition(hw,
							     phy_reg_page[i])) अणु
					/*करोn't need the hw_body*/
				    i += 2; /* skip the pair of expression*/
				    /* to protect 'i+1' 'i+2' not overrun */
				    अगर (i >= phy_reg_page_len - 2)
					अवरोध;

				    v1 = phy_reg_page[i];
				    v2 = phy_reg_page[i+1];
				    जबतक (v2 != 0xDEAD &&
					   i < phy_reg_page_len - 5) अणु
					i += 3;
					v1 = phy_reg_page[i];
					v2 = phy_reg_page[i+1];
				    पूर्ण
				पूर्ण
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
	v1 = radioa_array_table[i]; \
	v2 = radioa_array_table[i+1]; \
पूर्ण जबतक (0)

अटल व्योम process_path_a(काष्ठा ieee80211_hw *hw,
			   u16  radioa_arraylen,
			   u32 *radioa_array_table)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 v1, v2;
	पूर्णांक i;

	क्रम (i = 0; i < radioa_arraylen; i = i + 2) अणु
		v1 = radioa_array_table[i];
		v2 = radioa_array_table[i+1];
		अगर (v1 < 0xcdcdcdcd) अणु
			_rtl8188e_config_rf_radio_a(hw, v1, v2);
		पूर्ण अन्यथा अणु /*This line is the start line of branch.*/
			/* to protect READ_NEXT_PAIR not overrun */
			अगर (i >= radioa_arraylen - 2)
				अवरोध;

			अगर (!_rtl88e_check_condition(hw, radioa_array_table[i])) अणु
				/*Discard the following (offset, data) pairs*/
				READ_NEXT_RF_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD &&
				       i < radioa_arraylen - 2) अणु
					READ_NEXT_RF_PAIR(v1, v2, i);
				पूर्ण
				i -= 2; /* prevent from क्रम-loop += 2*/
			पूर्ण अन्यथा अणु /* Configure matched pairs and
				  * skip to end of अगर-अन्यथा.
				  */
				READ_NEXT_RF_PAIR(v1, v2, i);
				जबतक (v2 != 0xDEAD &&
				       v2 != 0xCDEF &&
				       v2 != 0xCDCD &&
				       i < radioa_arraylen - 2) अणु
					_rtl8188e_config_rf_radio_a(hw, v1, v2);
					READ_NEXT_RF_PAIR(v1, v2, i);
				पूर्ण

				जबतक (v2 != 0xDEAD &&
				       i < radioa_arraylen - 2)
					READ_NEXT_RF_PAIR(v1, v2, i);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rtlhal->oem_id == RT_CID_819X_HP)
		_rtl8188e_config_rf_radio_a(hw, 0x52, 0x7E4BD);
पूर्ण

bool rtl88e_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत radio_path rfpath)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 *radioa_array_table;
	u16 radioa_arraylen;

	radioa_arraylen = RTL8188EE_RADIOA_1TARRAYLEN;
	radioa_array_table = RTL8188EE_RADIOA_1TARRAY;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"Radio_A:RTL8188EE_RADIOA_1TARRAY %d\n", radioa_arraylen);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "Radio No %x\n", rfpath);
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		process_path_a(hw, radioa_arraylen, radioa_array_table);
		अवरोध;
	हाल RF90_PATH_B:
	हाल RF90_PATH_C:
	हाल RF90_PATH_D:
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

व्योम rtl88e_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw)
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

अटल व्योम _rtl88e_phy_init_bb_rf_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfs = RFPGA0_XCD_RFINTERFACESW;
	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfs = RFPGA0_XCD_RFINTERFACESW;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfi = RFPGA0_XAB_RFINTERFACERB;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfi = RFPGA0_XAB_RFINTERFACERB;
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfi = RFPGA0_XCD_RFINTERFACERB;
	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfi = RFPGA0_XCD_RFINTERFACERB;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfo = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfo = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfe = RFPGA0_XA_RFINTERFACEOE;
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfe = RFPGA0_XB_RFINTERFACEOE;

	rtlphy->phyreg_def[RF90_PATH_A].rf3wire_offset =
	    RFPGA0_XA_LSSIPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_B].rf3wire_offset =
	    RFPGA0_XB_LSSIPARAMETER;

	rtlphy->phyreg_def[RF90_PATH_A].rflssi_select = RFPGA0_XAB_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_B].rflssi_select = RFPGA0_XAB_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_C].rflssi_select = RFPGA0_XCD_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_D].rflssi_select = RFPGA0_XCD_RFPARAMETER;

	rtlphy->phyreg_def[RF90_PATH_A].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	rtlphy->phyreg_def[RF90_PATH_B].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	rtlphy->phyreg_def[RF90_PATH_C].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	rtlphy->phyreg_def[RF90_PATH_D].rftxgain_stage = RFPGA0_TXGAINSTAGE;

	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para1 = RFPGA0_XA_HSSIPARAMETER1;
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para1 = RFPGA0_XB_HSSIPARAMETER1;

	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para2 = RFPGA0_XA_HSSIPARAMETER2;
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para2 = RFPGA0_XB_HSSIPARAMETER2;

	rtlphy->phyreg_def[RF90_PATH_A].rfsw_ctrl =
	    RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_B].rfsw_ctrl =
	    RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_C].rfsw_ctrl =
	    RFPGA0_XCD_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_D].rfsw_ctrl =
	    RFPGA0_XCD_SWITCHCONTROL;

	rtlphy->phyreg_def[RF90_PATH_A].rfagc_control1 = ROFDM0_XAAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_B].rfagc_control1 = ROFDM0_XBAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_C].rfagc_control1 = ROFDM0_XCAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_D].rfagc_control1 = ROFDM0_XDAGCCORE1;

	rtlphy->phyreg_def[RF90_PATH_A].rfagc_control2 = ROFDM0_XAAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_B].rfagc_control2 = ROFDM0_XBAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_C].rfagc_control2 = ROFDM0_XCAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_D].rfagc_control2 = ROFDM0_XDAGCCORE2;

	rtlphy->phyreg_def[RF90_PATH_A].rfrxiq_imbal = ROFDM0_XARXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_B].rfrxiq_imbal = ROFDM0_XBRXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_C].rfrxiq_imbal = ROFDM0_XCRXIQIMBANLANCE;
	rtlphy->phyreg_def[RF90_PATH_D].rfrxiq_imbal = ROFDM0_XDRXIQIMBALANCE;

	rtlphy->phyreg_def[RF90_PATH_A].rfrx_afe = ROFDM0_XARXAFE;
	rtlphy->phyreg_def[RF90_PATH_B].rfrx_afe = ROFDM0_XBRXAFE;
	rtlphy->phyreg_def[RF90_PATH_C].rfrx_afe = ROFDM0_XCRXAFE;
	rtlphy->phyreg_def[RF90_PATH_D].rfrx_afe = ROFDM0_XDRXAFE;

	rtlphy->phyreg_def[RF90_PATH_A].rftxiq_imbal = ROFDM0_XATXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_B].rftxiq_imbal = ROFDM0_XBTXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_C].rftxiq_imbal = ROFDM0_XCTXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_D].rftxiq_imbal = ROFDM0_XDTXIQIMBALANCE;

	rtlphy->phyreg_def[RF90_PATH_A].rftx_afe = ROFDM0_XATXAFE;
	rtlphy->phyreg_def[RF90_PATH_B].rftx_afe = ROFDM0_XBTXAFE;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rb = RFPGA0_XA_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rb = RFPGA0_XB_LSSIREADBACK;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rbpi = TRANSCEIVEA_HSPI_READBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rbpi = TRANSCEIVEB_HSPI_READBACK;
पूर्ण

व्योम rtl88e_phy_get_txघातer_level(काष्ठा ieee80211_hw *hw, दीर्घ *घातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 txpwr_level;
	दीर्घ txpwr_dbm;

	txpwr_level = rtlphy->cur_cck_txpwridx;
	txpwr_dbm = _rtl88e_phy_txpwr_idx_to_dbm(hw,
						 WIRELESS_MODE_B, txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx;
	अगर (_rtl88e_phy_txpwr_idx_to_dbm(hw,
					 WIRELESS_MODE_G,
					 txpwr_level) > txpwr_dbm)
		txpwr_dbm =
		    _rtl88e_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_G,
						 txpwr_level);
	txpwr_level = rtlphy->cur_ofdm24g_txpwridx;
	अगर (_rtl88e_phy_txpwr_idx_to_dbm(hw,
					 WIRELESS_MODE_N_24G,
					 txpwr_level) > txpwr_dbm)
		txpwr_dbm =
		    _rtl88e_phy_txpwr_idx_to_dbm(hw, WIRELESS_MODE_N_24G,
						 txpwr_level);
	*घातerlevel = txpwr_dbm;
पूर्ण

अटल व्योम handle_path_a(काष्ठा rtl_efuse *rtlefuse, u8 index,
			  u8 *cckघातerlevel, u8 *ofdmघातerlevel,
			  u8 *bw20घातerlevel, u8 *bw40घातerlevel)
अणु
	cckघातerlevel[RF90_PATH_A] =
	    rtlefuse->txpwrlevel_cck[RF90_PATH_A][index];
		/*-8~7 */
	अगर (rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][index] > 0x0f)
		bw20घातerlevel[RF90_PATH_A] =
		  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] -
		  (~(rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][index]) + 1);
	अन्यथा
		bw20घातerlevel[RF90_PATH_A] =
		  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] +
		  rtlefuse->txpwr_ht20dअगरf[RF90_PATH_A][index];
	अगर (rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][index] > 0xf)
		ofdmघातerlevel[RF90_PATH_A] =
		  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] -
		  (~(rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][index])+1);
	अन्यथा
		ofdmघातerlevel[RF90_PATH_A] =
		rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index] +
		  rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_A][index];
	bw40घातerlevel[RF90_PATH_A] =
	  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index];
पूर्ण

अटल व्योम _rtl88e_get_txघातer_index(काष्ठा ieee80211_hw *hw, u8 channel,
				      u8 *cckघातerlevel, u8 *ofdmघातerlevel,
				      u8 *bw20घातerlevel, u8 *bw40घातerlevel)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);
	u8 rf_path = 0;

	क्रम (rf_path = 0; rf_path < 2; rf_path++) अणु
		अगर (rf_path == RF90_PATH_A) अणु
			handle_path_a(rtlefuse, index, cckघातerlevel,
				      ofdmघातerlevel, bw20घातerlevel,
				      bw40घातerlevel);
		पूर्ण अन्यथा अगर (rf_path == RF90_PATH_B) अणु
			cckघातerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_cck[RF90_PATH_B][index];
			bw20घातerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index] +
			  rtlefuse->txpwr_ht20dअगरf[RF90_PATH_B][index];
			ofdmघातerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index] +
			  rtlefuse->txpwr_legacyhtdअगरf[RF90_PATH_B][index];
			bw40घातerlevel[RF90_PATH_B] =
			  rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index];
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम _rtl88e_ccxघातer_index_check(काष्ठा ieee80211_hw *hw,
					 u8 channel, u8 *cckघातerlevel,
					 u8 *ofdmघातerlevel, u8 *bw20घातerlevel,
					 u8 *bw40घातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	rtlphy->cur_cck_txpwridx = cckघातerlevel[0];
	rtlphy->cur_ofdm24g_txpwridx = ofdmघातerlevel[0];
	rtlphy->cur_bw20_txpwridx = bw20घातerlevel[0];
	rtlphy->cur_bw40_txpwridx = bw40घातerlevel[0];

पूर्ण

व्योम rtl88e_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 cckघातerlevel[MAX_TX_COUNT]  = अणु0पूर्ण;
	u8 ofdmघातerlevel[MAX_TX_COUNT] = अणु0पूर्ण;
	u8 bw20घातerlevel[MAX_TX_COUNT] = अणु0पूर्ण;
	u8 bw40घातerlevel[MAX_TX_COUNT] = अणु0पूर्ण;

	अगर (!rtlefuse->txpwr_fromeprom)
		वापस;
	_rtl88e_get_txघातer_index(hw, channel,
				  &cckघातerlevel[0], &ofdmघातerlevel[0],
				  &bw20घातerlevel[0], &bw40घातerlevel[0]);
	_rtl88e_ccxघातer_index_check(hw, channel,
				     &cckघातerlevel[0], &ofdmघातerlevel[0],
				     &bw20घातerlevel[0], &bw40घातerlevel[0]);
	rtl88e_phy_rf6052_set_cck_txघातer(hw, &cckघातerlevel[0]);
	rtl88e_phy_rf6052_set_ofdm_txघातer(hw, &ofdmघातerlevel[0],
					   &bw20घातerlevel[0],
					   &bw40घातerlevel[0], channel);
पूर्ण

अटल दीर्घ _rtl88e_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
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

व्योम rtl88e_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw, u8 operation)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	क्रमागत io_type iotype;

	अगर (!is_hal_stop(rtlhal)) अणु
		चयन (operation) अणु
		हाल SCAN_OPT_BACKUP_BAND0:
			iotype = IO_CMD_PAUSE_BAND0_DM_BY_SCAN;
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

व्योम rtl88e_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw)
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
		reg_prsr_rsc =
		    (reg_prsr_rsc & 0x90) | (mac->cur_40_prime_sc << 5);
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
	rtl88e_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD, "\n");
पूर्ण

व्योम rtl88e_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
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
		rtl88e_phy_set_bw_mode_callback(hw);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"false driver sleep or unload\n");
		rtlphy->set_bwmode_inprogress = false;
		rtlphy->current_chan_bw = पंचांगp_bw;
	पूर्ण
पूर्ण

व्योम rtl88e_phy_sw_chnl_callback(काष्ठा ieee80211_hw *hw)
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
		अगर (!_rtl88e_phy_sw_chnl_step_by_step
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

u8 rtl88e_phy_sw_chnl(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	अगर (rtlphy->sw_chnl_inprogress)
		वापस 0;
	अगर (rtlphy->set_bwmode_inprogress)
		वापस 0;
	WARN_ONCE((rtlphy->current_channel > 14),
		  "rtl8188ee: WIRELESS_MODE_G but channel>14");
	rtlphy->sw_chnl_inprogress = true;
	rtlphy->sw_chnl_stage = 0;
	rtlphy->sw_chnl_step = 0;
	अगर (!(is_hal_stop(rtlhal)) && !(RT_CANNOT_IO(hw))) अणु
		rtl88e_phy_sw_chnl_callback(hw);
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

अटल bool _rtl88e_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
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
	_rtl88e_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					 MAX_PRECMD_CNT,
					 CMDID_SET_TXPOWEROWER_LEVEL, 0, 0, 0);
	_rtl88e_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					 MAX_PRECMD_CNT, CMDID_END, 0, 0, 0);

	postcommoncmdcnt = 0;

	_rtl88e_phy_set_sw_chnl_cmdarray(postcommoncmd, postcommoncmdcnt++,
					 MAX_POSTCMD_CNT, CMDID_END, 0, 0, 0);

	rfdependcmdcnt = 0;

	WARN_ONCE((channel < 1 || channel > 14),
		  "rtl8188ee: illegal channel for Zebra: %d\n", channel);

	_rtl88e_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					 MAX_RFDEPENDCMD_CNT, CMDID_RF_WRITEREG,
					 RF_CHNLBW, channel, 10);

	_rtl88e_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					 MAX_RFDEPENDCMD_CNT, CMDID_END, 0, 0,
					 0);

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
			rtl88e_phy_set_txघातer_level(hw, channel);
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

अटल bool _rtl88e_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
					     u32 cmdtableidx, u32 cmdtablesz,
					     क्रमागत swchnlcmd_id cmdid,
					     u32 para1, u32 para2, u32 msdelay)
अणु
	काष्ठा swchnlcmd *pcmd;

	अगर (cmdtable == शून्य) अणु
		WARN_ONCE(true, "rtl8188ee: cmdtable cannot be NULL.\n");
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

अटल u8 _rtl88e_phy_path_a_iqk(काष्ठा ieee80211_hw *hw, bool config_pathb)
अणु
	u32 reg_eac, reg_e94, reg_e9c;
	u8 result = 0x00;

	rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x10008c1c);
	rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x30008c1c);
	rtl_set_bbreg(hw, 0xe38, MASKDWORD, 0x8214032a);
	rtl_set_bbreg(hw, 0xe3c, MASKDWORD, 0x28160000);

	rtl_set_bbreg(hw, 0xe4c, MASKDWORD, 0x00462911);
	rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, 0xe94, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, 0xe9c, MASKDWORD);
	rtl_get_bbreg(hw, 0xea4, MASKDWORD);

	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	वापस result;
पूर्ण

अटल u8 _rtl88e_phy_path_b_iqk(काष्ठा ieee80211_hw *hw)
अणु
	u32 reg_eac, reg_eb4, reg_ebc, reg_ec4, reg_ecc;
	u8 result = 0x00;

	rtl_set_bbreg(hw, 0xe60, MASKDWORD, 0x00000002);
	rtl_set_bbreg(hw, 0xe60, MASKDWORD, 0x00000000);
	mdelay(IQK_DELAY_TIME);
	reg_eac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	reg_eb4 = rtl_get_bbreg(hw, 0xeb4, MASKDWORD);
	reg_ebc = rtl_get_bbreg(hw, 0xebc, MASKDWORD);
	reg_ec4 = rtl_get_bbreg(hw, 0xec4, MASKDWORD);
	reg_ecc = rtl_get_bbreg(hw, 0xecc, MASKDWORD);

	अगर (!(reg_eac & BIT(31)) &&
	    (((reg_eb4 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_ebc & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा
		वापस result;
	अगर (!(reg_eac & BIT(30)) &&
	    (((reg_ec4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_ecc & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	वापस result;
पूर्ण

अटल u8 _rtl88e_phy_path_a_rx_iqk(काष्ठा ieee80211_hw *hw, bool config_pathb)
अणु
	u32 reg_eac, reg_e94, reg_e9c, reg_ea4, u32temp;
	u8 result = 0x00;

	/*Get TXIMR Setting*/
	/*Modअगरy RX IQK mode table*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0000f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf117b);
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/*IQK Setting*/
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x81004800);

	/*path a IQK setting*/
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x10008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x30008c1c);
	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82160804);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28160000);

	/*LO calibration Setting*/
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a911);
	/*one shot,path A LOK & iqk*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, RTX_POWER_BEFORE_IQK_A, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_A, MASKDWORD);


	अगर (!(reg_eac & BIT(28)) &&
	    (((reg_e94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((reg_e9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा
		वापस result;

	u32temp = 0x80007C00 | (reg_e94&0x3FF0000) |
		  ((reg_e9c&0x3FF0000) >> 16);
	rtl_set_bbreg(hw, RTX_IQK, MASKDWORD, u32temp);
	/*RX IQK*/
	/*Modअगरy RX IQK mode table*/
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x00000000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_WE_LUT, RFREG_OFFSET_MASK, 0x800a0);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_RCK_OS, RFREG_OFFSET_MASK, 0x30000);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G1, RFREG_OFFSET_MASK, 0x0000f);
	rtl_set_rfreg(hw, RF90_PATH_A, RF_TXPA_G2, RFREG_OFFSET_MASK, 0xf7ffa);
	rtl_set_bbreg(hw, RFPGA0_IQK, MASKDWORD, 0x80800000);

	/*IQK Setting*/
	rtl_set_bbreg(hw, RRX_IQK, MASKDWORD, 0x01004800);

	/*path a IQK setting*/
	rtl_set_bbreg(hw, RTX_IQK_TONE_A, MASKDWORD, 0x30008c1c);
	rtl_set_bbreg(hw, RRX_IQK_TONE_A, MASKDWORD, 0x10008c1c);
	rtl_set_bbreg(hw, RTX_IQK_PI_A, MASKDWORD, 0x82160c05);
	rtl_set_bbreg(hw, RRX_IQK_PI_A, MASKDWORD, 0x28160c05);

	/*LO calibration Setting*/
	rtl_set_bbreg(hw, RIQK_AGC_RSP, MASKDWORD, 0x0046a911);
	/*one shot,path A LOK & iqk*/
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, RIQK_AGC_PTS, MASKDWORD, 0xf8000000);

	mdelay(IQK_DELAY_TIME);

	reg_eac = rtl_get_bbreg(hw, RRX_POWER_AFTER_IQK_A_2, MASKDWORD);
	reg_e94 = rtl_get_bbreg(hw, RTX_POWER_BEFORE_IQK_A, MASKDWORD);
	reg_e9c = rtl_get_bbreg(hw, RTX_POWER_AFTER_IQK_A, MASKDWORD);
	reg_ea4 = rtl_get_bbreg(hw, RRX_POWER_BEFORE_IQK_A_2, MASKDWORD);

	अगर (!(reg_eac & BIT(27)) &&
	    (((reg_ea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((reg_eac & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	वापस result;
पूर्ण

अटल व्योम _rtl88e_phy_path_a_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
					       bool iqk_ok, दीर्घ result[][8],
					       u8 final_candidate, bool btxonly)
अणु
	u32 oldval_0, x, tx0_a, reg;
	दीर्घ y, tx0_c;

	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (iqk_ok) अणु
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
		rtl_set_bbreg(hw, 0xca0, 0xF0000000, reg);
	पूर्ण
पूर्ण

अटल व्योम _rtl88e_phy_save_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					    u32 *addareg, u32 *addabackup,
					    u32 रेजिस्टरnum)
अणु
	u32 i;

	क्रम (i = 0; i < रेजिस्टरnum; i++)
		addabackup[i] = rtl_get_bbreg(hw, addareg[i], MASKDWORD);
पूर्ण

अटल व्योम _rtl88e_phy_save_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					   u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		macbackup[i] = rtl_पढ़ो_byte(rtlpriv, macreg[i]);
	macbackup[i] = rtl_पढ़ो_dword(rtlpriv, macreg[i]);
पूर्ण

अटल व्योम _rtl88e_phy_reload_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					      u32 *addareg, u32 *addabackup,
					      u32 regiesternum)
अणु
	u32 i;

	क्रम (i = 0; i < regiesternum; i++)
		rtl_set_bbreg(hw, addareg[i], MASKDWORD, addabackup[i]);
पूर्ण

अटल व्योम _rtl88e_phy_reload_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					     u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		rtl_ग_लिखो_byte(rtlpriv, macreg[i], (u8) macbackup[i]);
	rtl_ग_लिखो_dword(rtlpriv, macreg[i], macbackup[i]);
पूर्ण

अटल व्योम _rtl88e_phy_path_adda_on(काष्ठा ieee80211_hw *hw,
				     u32 *addareg, bool is_patha_on, bool is2t)
अणु
	u32 pathon;
	u32 i;

	pathon = is_patha_on ? 0x04db25a4 : 0x0b1b25a4;
	अगर (!is2t) अणु
		pathon = 0x0bdb25a0;
		rtl_set_bbreg(hw, addareg[0], MASKDWORD, 0x0b1b25a0);
	पूर्ण अन्यथा अणु
		rtl_set_bbreg(hw, addareg[0], MASKDWORD, pathon);
	पूर्ण

	क्रम (i = 1; i < IQK_ADDA_REG_NUM; i++)
		rtl_set_bbreg(hw, addareg[i], MASKDWORD, pathon);
पूर्ण

अटल व्योम _rtl88e_phy_mac_setting_calibration(काष्ठा ieee80211_hw *hw,
						u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i = 0;

	rtl_ग_लिखो_byte(rtlpriv, macreg[i], 0x3F);

	क्रम (i = 1; i < (IQK_MAC_REG_NUM - 1); i++)
		rtl_ग_लिखो_byte(rtlpriv, macreg[i],
			       (u8) (macbackup[i] & (~BIT(3))));
	rtl_ग_लिखो_byte(rtlpriv, macreg[i], (u8) (macbackup[i] & (~BIT(5))));
पूर्ण

अटल व्योम _rtl88e_phy_path_a_standby(काष्ठा ieee80211_hw *hw)
अणु
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x0);
	rtl_set_bbreg(hw, 0x840, MASKDWORD, 0x00010000);
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
पूर्ण

अटल व्योम _rtl88e_phy_pi_mode_चयन(काष्ठा ieee80211_hw *hw, bool pi_mode)
अणु
	u32 mode;

	mode = pi_mode ? 0x01000100 : 0x01000000;
	rtl_set_bbreg(hw, 0x820, MASKDWORD, mode);
	rtl_set_bbreg(hw, 0x828, MASKDWORD, mode);
पूर्ण

अटल bool _rtl88e_phy_simularity_compare(काष्ठा ieee80211_hw *hw,
					   दीर्घ result[][8], u8 c1, u8 c2)
अणु
	u32 i, j, dअगरf, simularity_biपंचांगap, bound;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	u8 final_candidate[2] = अणु 0xFF, 0xFF पूर्ण;
	bool bresult = true, is2t = IS_92C_SERIAL(rtlhal->version);

	अगर (is2t)
		bound = 8;
	अन्यथा
		bound = 4;

	simularity_biपंचांगap = 0;

	क्रम (i = 0; i < bound; i++) अणु
		dअगरf = (result[c1][i] > result[c2][i]) ?
		    (result[c1][i] - result[c2][i]) :
		    (result[c2][i] - result[c1][i]);

		अगर (dअगरf > MAX_TOLERANCE) अणु
			अगर ((i == 2 || i == 6) && !simularity_biपंचांगap) अणु
				अगर (result[c1][i] + result[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				अन्यथा अगर (result[c2][i] + result[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				अन्यथा
					simularity_biपंचांगap = simularity_biपंचांगap |
					    (1 << i);
			पूर्ण अन्यथा
				simularity_biपंचांगap =
				    simularity_biपंचांगap | (1 << i);
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
	पूर्ण अन्यथा अगर (!(simularity_biपंचांगap & 0x0F)) अणु
		क्रम (i = 0; i < 4; i++)
			result[3][i] = result[c1][i];
		वापस false;
	पूर्ण अन्यथा अगर (!(simularity_biपंचांगap & 0xF0) && is2t) अणु
		क्रम (i = 4; i < 8; i++)
			result[3][i] = result[c1][i];
		वापस false;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण

पूर्ण

अटल व्योम _rtl88e_phy_iq_calibrate(काष्ठा ieee80211_hw *hw,
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
		0x870, 0x860, 0x864, 0x800
	पूर्ण;
	स्थिर u32 retrycount = 2;

	अगर (t == 0) अणु
		_rtl88e_phy_save_adda_रेजिस्टरs(hw, adda_reg,
						rtlphy->adda_backup, 16);
		_rtl88e_phy_save_mac_रेजिस्टरs(hw, iqk_mac_reg,
					       rtlphy->iqk_mac_backup);
		_rtl88e_phy_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
						rtlphy->iqk_bb_backup,
						IQK_BB_REG_NUM);
	पूर्ण
	_rtl88e_phy_path_adda_on(hw, adda_reg, true, is2t);
	अगर (t == 0) अणु
		rtlphy->rfpi_enable =
		  (u8)rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER1, BIT(8));
	पूर्ण

	अगर (!rtlphy->rfpi_enable)
		_rtl88e_phy_pi_mode_चयन(hw, true);
	/*BB Setting*/
	rtl_set_bbreg(hw, 0x800, BIT(24), 0x00);
	rtl_set_bbreg(hw, 0xc04, MASKDWORD, 0x03a05600);
	rtl_set_bbreg(hw, 0xc08, MASKDWORD, 0x000800e4);
	rtl_set_bbreg(hw, 0x874, MASKDWORD, 0x22204000);

	rtl_set_bbreg(hw, 0x870, BIT(10), 0x01);
	rtl_set_bbreg(hw, 0x870, BIT(26), 0x01);
	rtl_set_bbreg(hw, 0x860, BIT(10), 0x00);
	rtl_set_bbreg(hw, 0x864, BIT(10), 0x00);

	अगर (is2t) अणु
		rtl_set_bbreg(hw, 0x840, MASKDWORD, 0x00010000);
		rtl_set_bbreg(hw, 0x844, MASKDWORD, 0x00010000);
	पूर्ण
	_rtl88e_phy_mac_setting_calibration(hw, iqk_mac_reg,
					    rtlphy->iqk_mac_backup);
	rtl_set_bbreg(hw, 0xb68, MASKDWORD, 0x0f600000);
	अगर (is2t)
		rtl_set_bbreg(hw, 0xb6c, MASKDWORD, 0x0f600000);

	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
	rtl_set_bbreg(hw, 0xe40, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, 0xe44, MASKDWORD, 0x81004800);
	क्रम (i = 0; i < retrycount; i++) अणु
		patha_ok = _rtl88e_phy_path_a_iqk(hw, is2t);
		अगर (patha_ok == 0x01) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path A Tx IQK Success!!\n");
			result[t][0] = (rtl_get_bbreg(hw, 0xe94, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][1] = (rtl_get_bbreg(hw, 0xe9c, MASKDWORD) &
					0x3FF0000) >> 16;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < retrycount; i++) अणु
		patha_ok = _rtl88e_phy_path_a_rx_iqk(hw, is2t);
		अगर (patha_ok == 0x03) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path A Rx IQK Success!!\n");
			result[t][2] = (rtl_get_bbreg(hw, 0xea4, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][3] = (rtl_get_bbreg(hw, 0xeac, MASKDWORD) &
					0x3FF0000) >> 16;
			अवरोध;
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Path a RX iqk fail!!!\n");
		पूर्ण
	पूर्ण

	अगर (0 == patha_ok)
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"Path A IQK Success!!\n");
	अगर (is2t) अणु
		_rtl88e_phy_path_a_standby(hw);
		_rtl88e_phy_path_adda_on(hw, adda_reg, false, is2t);
		क्रम (i = 0; i < retrycount; i++) अणु
			pathb_ok = _rtl88e_phy_path_b_iqk(hw);
			अगर (pathb_ok == 0x03) अणु
				result[t][4] = (rtl_get_bbreg(hw,
							      0xeb4,
							      MASKDWORD) &
						0x3FF0000) >> 16;
				result[t][5] =
				    (rtl_get_bbreg(hw, 0xebc, MASKDWORD) &
				     0x3FF0000) >> 16;
				result[t][6] =
				    (rtl_get_bbreg(hw, 0xec4, MASKDWORD) &
				     0x3FF0000) >> 16;
				result[t][7] =
				    (rtl_get_bbreg(hw, 0xecc, MASKDWORD) &
				     0x3FF0000) >> 16;
				अवरोध;
			पूर्ण अन्यथा अगर (i == (retrycount - 1) && pathb_ok == 0x01) अणु
				result[t][4] = (rtl_get_bbreg(hw,
							      0xeb4,
							      MASKDWORD) &
						0x3FF0000) >> 16;
			पूर्ण
			result[t][5] = (rtl_get_bbreg(hw, 0xebc, MASKDWORD) &
					0x3FF0000) >> 16;
		पूर्ण
	पूर्ण

	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0);

	अगर (t != 0) अणु
		अगर (!rtlphy->rfpi_enable)
			_rtl88e_phy_pi_mode_चयन(hw, false);
		_rtl88e_phy_reload_adda_रेजिस्टरs(hw, adda_reg,
						  rtlphy->adda_backup, 16);
		_rtl88e_phy_reload_mac_रेजिस्टरs(hw, iqk_mac_reg,
						 rtlphy->iqk_mac_backup);
		_rtl88e_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
						  rtlphy->iqk_bb_backup,
						  IQK_BB_REG_NUM);

		rtl_set_bbreg(hw, 0x840, MASKDWORD, 0x00032ed3);
		अगर (is2t)
			rtl_set_bbreg(hw, 0x844, MASKDWORD, 0x00032ed3);
		rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x01008c00);
		rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x01008c00);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "88ee IQK Finish!!\n");
पूर्ण

अटल व्योम _rtl88e_phy_lc_calibrate(काष्ठा ieee80211_hw *hw, bool is2t)
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
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "\n");
पूर्ण

अटल व्योम _rtl88e_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw,
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

व्योम rtl88e_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, bool b_recovery)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	दीर्घ result[4][8];
	u8 i, final_candidate;
	bool b_patha_ok;
	दीर्घ reg_e94, reg_e9c, reg_ea4, reg_eb4, reg_ebc,
	    reg_पंचांगp = 0;
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

	अगर (b_recovery) अणु
		_rtl88e_phy_reload_adda_रेजिस्टरs(hw,
						  iqk_bb_reg,
						  rtlphy->iqk_bb_backup, 9);
		वापस;
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		result[0][i] = 0;
		result[1][i] = 0;
		result[2][i] = 0;
		result[3][i] = 0;
	पूर्ण
	final_candidate = 0xff;
	b_patha_ok = false;
	is12simular = false;
	is23simular = false;
	is13simular = false;
	क्रम (i = 0; i < 3; i++) अणु
		अगर (get_rf_type(rtlphy) == RF_2T2R)
			_rtl88e_phy_iq_calibrate(hw, result, i, true);
		अन्यथा
			_rtl88e_phy_iq_calibrate(hw, result, i, false);
		अगर (i == 1) अणु
			is12simular =
			  _rtl88e_phy_simularity_compare(hw, result, 0, 1);
			अगर (is12simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == 2) अणु
			is13simular =
			  _rtl88e_phy_simularity_compare(hw, result, 0, 2);
			अगर (is13simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
			is23simular =
			   _rtl88e_phy_simularity_compare(hw, result, 1, 2);
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
	पूर्ण
	अगर (final_candidate != 0xff) अणु
		reg_e94 = result[final_candidate][0];
		reg_e9c = result[final_candidate][1];
		reg_ea4 = result[final_candidate][2];
		reg_eb4 = result[final_candidate][4];
		reg_ebc = result[final_candidate][5];
		rtlphy->reg_eb4 = reg_eb4;
		rtlphy->reg_ebc = reg_ebc;
		rtlphy->reg_e94 = reg_e94;
		rtlphy->reg_e9c = reg_e9c;
		b_patha_ok = true;
	पूर्ण अन्यथा अणु
		rtlphy->reg_e94 = 0x100;
		rtlphy->reg_eb4 = 0x100;
		rtlphy->reg_e9c = 0x0;
		rtlphy->reg_ebc = 0x0;
	पूर्ण
	अगर (reg_e94 != 0) /*&&(reg_ea4 != 0) */
		_rtl88e_phy_path_a_fill_iqk_matrix(hw, b_patha_ok, result,
						   final_candidate,
						   (reg_ea4 == 0));
	अगर (final_candidate != 0xFF) अणु
		क्रम (i = 0; i < IQK_MATRIX_REG_NUM; i++)
			rtlphy->iqk_matrix[0].value[0][i] =
				result[final_candidate][i];
		rtlphy->iqk_matrix[0].iqk_करोne = true;

	पूर्ण
	_rtl88e_phy_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
					rtlphy->iqk_bb_backup, 9);
पूर्ण

व्योम rtl88e_phy_lc_calibrate(काष्ठा ieee80211_hw *hw)
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

	_rtl88e_phy_lc_calibrate(hw, false);

	rtlphy->lck_inprogress = false;
पूर्ण

व्योम rtl88e_phy_set_rfpath_चयन(काष्ठा ieee80211_hw *hw, bool bमुख्य)
अणु
	_rtl88e_phy_set_rfpath_चयन(hw, bमुख्य, false);
पूर्ण

bool rtl88e_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype)
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
	rtl88e_phy_set_io(hw);
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE, "IO Type(%#x)\n", iotype);
	वापस true;
पूर्ण

अटल व्योम rtl88e_phy_set_io(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"--->Cmd(%#x), set_io_inprogress(%d)\n",
		rtlphy->current_io_type, rtlphy->set_io_inprogress);
	चयन (rtlphy->current_io_type) अणु
	हाल IO_CMD_RESUME_DM_BY_SCAN:
		dm_digtable->cur_igvalue = rtlphy->initgain_backup.xaagccore1;
		/*rtl92c_dm_ग_लिखो_dig(hw);*/
		rtl88e_phy_set_txघातer_level(hw, rtlphy->current_channel);
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

अटल व्योम rtl88ee_phy_set_rf_on(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	/*rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x00);*/
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
पूर्ण

अटल व्योम _rtl88ee_phy_set_rf_sleep(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x22);
पूर्ण

अटल bool _rtl88ee_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
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
			पूर्ण जबतक (!rtstatus &&
				 (initializecount < 10));
			RT_CLEAR_PS_LEVEL(ppsc,
					  RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"Set ERFON slept:%d ms\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_sleep_jअगरfies));
			ppsc->last_awake_jअगरfies = jअगरfies;
			rtl88ee_phy_set_rf_on(hw);
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
	हाल ERFSLEEP:अणु
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
			_rtl88ee_phy_set_rf_sleep(hw);
			अवरोध;
		पूर्ण
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

bool rtl88e_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				   क्रमागत rf_pwrstate rfpwr_state)
अणु
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	bool bresult = false;

	अगर (rfpwr_state == ppsc->rfpwr_state)
		वापस bresult;
	bresult = _rtl88ee_phy_set_rf_घातer_state(hw, rfpwr_state);
	वापस bresult;
पूर्ण
