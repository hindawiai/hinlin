<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "phy_common.h"
#समावेश "../rtl8723ae/reg.h"
#समावेश <linux/module.h>

/* These routines are common to RTL8723AE and RTL8723bE */

u32 rtl8723_phy_query_bb_reg(काष्ठा ieee80211_hw *hw,
			     u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 वापसvalue, originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x)\n", regaddr, biपंचांगask);
	originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
	bitshअगरt = rtl8723_phy_calculate_bit_shअगरt(biपंचांगask);
	वापसvalue = (originalvalue & biपंचांगask) >> bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"BBR MASK=0x%x Addr[0x%x]=0x%x\n", biपंचांगask,
		regaddr, originalvalue);
	वापस वापसvalue;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_query_bb_reg);

व्योम rtl8723_phy_set_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr,
			      u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n", regaddr, biपंचांगask,
		data);

	अगर (biपंचांगask != MASKDWORD) अणु
		originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
		bitshअगरt = rtl8723_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((originalvalue & (~biपंचांगask)) | (data << bitshअगरt));
	पूर्ण

	rtl_ग_लिखो_dword(rtlpriv, regaddr, data);

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_set_bb_reg);

u32 rtl8723_phy_calculate_bit_shअगरt(u32 biपंचांगask)
अणु
	u32 i = ffs(biपंचांगask);

	वापस i ? i - 1 : 32;
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_calculate_bit_shअगरt);

u32 rtl8723_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
			       क्रमागत radio_path rfpath, u32 offset)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
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
	rtl_set_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, MASKDWORD,
		      पंचांगpदीर्घ | BLSSIREADEDGE);
	udelay(120);
	अगर (rfpath == RF90_PATH_A)
		rfpi_enable = (u8) rtl_get_bbreg(hw, RFPGA0_XA_HSSIPARAMETER1,
						 BIT(8));
	अन्यथा अगर (rfpath == RF90_PATH_B)
		rfpi_enable = (u8) rtl_get_bbreg(hw, RFPGA0_XB_HSSIPARAMETER1,
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
EXPORT_SYMBOL_GPL(rtl8723_phy_rf_serial_पढ़ो);

व्योम rtl8723_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
				 क्रमागत radio_path rfpath,
				 u32 offset, u32 data)
अणु
	u32 data_and_addr;
	u32 newoffset;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
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
		rfpath, pphyreg->rf3wire_offset,
		data_and_addr);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_rf_serial_ग_लिखो);

दीर्घ rtl8723_phy_txpwr_idx_to_dbm(काष्ठा ieee80211_hw *hw,
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
EXPORT_SYMBOL_GPL(rtl8723_phy_txpwr_idx_to_dbm);

व्योम rtl8723_phy_init_bb_rf_reg_def(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

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

	rtlphy->phyreg_def[RF90_PATH_A].rfsw_ctrl = RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_B].rfsw_ctrl = RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_C].rfsw_ctrl = RFPGA0_XCD_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_D].rfsw_ctrl = RFPGA0_XCD_SWITCHCONTROL;

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
	rtlphy->phyreg_def[RF90_PATH_C].rftx_afe = ROFDM0_XCTXAFE;
	rtlphy->phyreg_def[RF90_PATH_D].rftx_afe = ROFDM0_XDTXAFE;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rb = RFPGA0_XA_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rb = RFPGA0_XB_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_C].rf_rb = RFPGA0_XC_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_D].rf_rb = RFPGA0_XD_LSSIREADBACK;

	rtlphy->phyreg_def[RF90_PATH_A].rf_rbpi = TRANSCEIVEA_HSPI_READBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rbpi = TRANSCEIVEB_HSPI_READBACK;

पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_init_bb_rf_reg_def);

bool rtl8723_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
				      u32 cmdtableidx,
				      u32 cmdtablesz,
				      क्रमागत swchnlcmd_id cmdid,
				      u32 para1, u32 para2,
				      u32 msdelay)
अणु
	काष्ठा swchnlcmd *pcmd;

	अगर (cmdtable == शून्य) अणु
		WARN_ONCE(true, "rtl8723-common: cmdtable cannot be NULL.\n");
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
EXPORT_SYMBOL_GPL(rtl8723_phy_set_sw_chnl_cmdarray);

व्योम rtl8723_phy_path_a_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
					bool iqk_ok,
					दीर्घ result[][8],
					u8 final_candidate,
					bool btxonly)
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
EXPORT_SYMBOL_GPL(rtl8723_phy_path_a_fill_iqk_matrix);

व्योम rtl8723_save_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw, u32 *addareg,
				 u32 *addabackup, u32 रेजिस्टरnum)
अणु
	u32 i;

	क्रम (i = 0; i < रेजिस्टरnum; i++)
		addabackup[i] = rtl_get_bbreg(hw, addareg[i], MASKDWORD);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_save_adda_रेजिस्टरs);

व्योम rtl8723_phy_save_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
				    u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		macbackup[i] = rtl_पढ़ो_byte(rtlpriv, macreg[i]);
	macbackup[i] = rtl_पढ़ो_dword(rtlpriv, macreg[i]);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_save_mac_रेजिस्टरs);

व्योम rtl8723_phy_reload_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
				       u32 *addareg, u32 *addabackup,
				       u32 regiesternum)
अणु
	u32 i;

	क्रम (i = 0; i < regiesternum; i++)
		rtl_set_bbreg(hw, addareg[i], MASKDWORD, addabackup[i]);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_reload_adda_रेजिस्टरs);

व्योम rtl8723_phy_reload_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
				      u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		rtl_ग_लिखो_byte(rtlpriv, macreg[i], (u8) macbackup[i]);
	rtl_ग_लिखो_dword(rtlpriv, macreg[i], macbackup[i]);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_reload_mac_रेजिस्टरs);

व्योम rtl8723_phy_path_adda_on(काष्ठा ieee80211_hw *hw, u32 *addareg,
			      bool is_patha_on, bool is2t)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 pathon;
	u32 i;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8723AE) अणु
		pathon = is_patha_on ? 0x04db25a4 : 0x0b1b25a4;
		अगर (!is2t) अणु
			pathon = 0x0bdb25a0;
			rtl_set_bbreg(hw, addareg[0], MASKDWORD, 0x0b1b25a0);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, addareg[0], MASKDWORD, pathon);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* rtl8723be */
		pathon = 0x01c00014;
		rtl_set_bbreg(hw, addareg[0], MASKDWORD, pathon);
	पूर्ण

	क्रम (i = 1; i < IQK_ADDA_REG_NUM; i++)
		rtl_set_bbreg(hw, addareg[i], MASKDWORD, pathon);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_path_adda_on);

व्योम rtl8723_phy_mac_setting_calibration(काष्ठा ieee80211_hw *hw,
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
EXPORT_SYMBOL_GPL(rtl8723_phy_mac_setting_calibration);

व्योम rtl8723_phy_path_a_standby(काष्ठा ieee80211_hw *hw)
अणु
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x0);
	rtl_set_bbreg(hw, 0x840, MASKDWORD, 0x00010000);
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_path_a_standby);

व्योम rtl8723_phy_pi_mode_चयन(काष्ठा ieee80211_hw *hw, bool pi_mode)
अणु
	u32 mode;

	mode = pi_mode ? 0x01000100 : 0x01000000;
	rtl_set_bbreg(hw, 0x820, MASKDWORD, mode);
	rtl_set_bbreg(hw, 0x828, MASKDWORD, mode);
पूर्ण
EXPORT_SYMBOL_GPL(rtl8723_phy_pi_mode_चयन);
