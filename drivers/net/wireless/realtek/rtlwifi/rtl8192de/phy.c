<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../pci.h"
#समावेश "../ps.h"
#समावेश "../core.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "table.h"
#समावेश "sw.h"
#समावेश "hw.h"

#घोषणा MAX_RF_IMR_INDEX			12
#घोषणा MAX_RF_IMR_INDEX_NORMAL			13
#घोषणा RF_REG_NUM_FOR_C_CUT_5G			6
#घोषणा RF_REG_NUM_FOR_C_CUT_5G_INTERNALPA	7
#घोषणा RF_REG_NUM_FOR_C_CUT_2G			5
#घोषणा RF_CHNL_NUM_5G				19
#घोषणा RF_CHNL_NUM_5G_40M			17
#घोषणा TARGET_CHNL_NUM_5G			221
#घोषणा TARGET_CHNL_NUM_2G			14
#घोषणा CV_CURVE_CNT				64

अटल u32 rf_reg_क्रम_5g_swchnl_normal[MAX_RF_IMR_INDEX_NORMAL] = अणु
	0, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x0
पूर्ण;

अटल u8 rf_reg_क्रम_c_cut_5g[RF_REG_NUM_FOR_C_CUT_5G] = अणु
	RF_SYN_G1, RF_SYN_G2, RF_SYN_G3, RF_SYN_G4, RF_SYN_G5, RF_SYN_G6
पूर्ण;

अटल u8 rf_reg_क्रम_c_cut_2g[RF_REG_NUM_FOR_C_CUT_2G] = अणु
	RF_SYN_G1, RF_SYN_G2, RF_SYN_G3, RF_SYN_G7, RF_SYN_G8
पूर्ण;

अटल u8 rf_क्रम_c_cut_5g_पूर्णांकernal_pa[RF_REG_NUM_FOR_C_CUT_5G_INTERNALPA] = अणु
	0x0B, 0x48, 0x49, 0x4B, 0x03, 0x04, 0x0E
पूर्ण;

अटल u32 rf_reg_mask_क्रम_c_cut_2g[RF_REG_NUM_FOR_C_CUT_2G] = अणु
	BIT(19) | BIT(18) | BIT(17) | BIT(14) | BIT(1),
	BIT(10) | BIT(9),
	BIT(18) | BIT(17) | BIT(16) | BIT(1),
	BIT(2) | BIT(1),
	BIT(15) | BIT(14) | BIT(13) | BIT(12) | BIT(11)
पूर्ण;

अटल u8 rf_chnl_5g[RF_CHNL_NUM_5G] = अणु
	36, 40, 44, 48, 52, 56, 60, 64, 100, 104, 108,
	112, 116, 120, 124, 128, 132, 136, 140
पूर्ण;

अटल u8 rf_chnl_5g_40m[RF_CHNL_NUM_5G_40M] = अणु
	38, 42, 46, 50, 54, 58, 62, 102, 106, 110, 114,
	118, 122, 126, 130, 134, 138
पूर्ण;
अटल u32 rf_reg_pram_c_5g[5][RF_REG_NUM_FOR_C_CUT_5G] = अणु
	अणु0xE43BE, 0xFC638, 0x77C0A, 0xDE471, 0xd7110, 0x8EB04पूर्ण,
	अणु0xE43BE, 0xFC078, 0xF7C1A, 0xE0C71, 0xD7550, 0xAEB04पूर्ण,
	अणु0xE43BF, 0xFF038, 0xF7C0A, 0xDE471, 0xE5550, 0xAEB04पूर्ण,
	अणु0xE43BF, 0xFF079, 0xF7C1A, 0xDE471, 0xE5550, 0xAEB04पूर्ण,
	अणु0xE43BF, 0xFF038, 0xF7C1A, 0xDE471, 0xd7550, 0xAEB04पूर्ण
पूर्ण;

अटल u32 rf_reg_param_क्रम_c_cut_2g[3][RF_REG_NUM_FOR_C_CUT_2G] = अणु
	अणु0x643BC, 0xFC038, 0x77C1A, 0x41289, 0x01840पूर्ण,
	अणु0x643BC, 0xFC038, 0x07C1A, 0x41289, 0x01840पूर्ण,
	अणु0x243BC, 0xFC438, 0x07C1A, 0x4128B, 0x0FC41पूर्ण
पूर्ण;

अटल u32 rf_syn_g4_क्रम_c_cut_2g = 0xD1C31 & 0x7FF;

अटल u32 rf_pram_c_5g_पूर्णांक_pa[3][RF_REG_NUM_FOR_C_CUT_5G_INTERNALPA] = अणु
	अणु0x01a00, 0x40443, 0x00eb5, 0x89bec, 0x94a12, 0x94a12, 0x94a12पूर्ण,
	अणु0x01800, 0xc0443, 0x00730, 0x896ee, 0x94a52, 0x94a52, 0x94a52पूर्ण,
	अणु0x01800, 0xc0443, 0x00730, 0x896ee, 0x94a12, 0x94a12, 0x94a12पूर्ण
पूर्ण;

/* [mode][patha+b][reg] */
अटल u32 rf_imr_param_normal[1][3][MAX_RF_IMR_INDEX_NORMAL] = अणु
	अणु
		/* channel 1-14. */
		अणु
			0x70000, 0x00ff0, 0x4400f, 0x00ff0, 0x0, 0x0, 0x0,
			0x0, 0x0, 0x64888, 0xe266c, 0x00090, 0x22fff
		पूर्ण,
		/* path 36-64 */
		अणु
			0x70000, 0x22880, 0x4470f, 0x55880, 0x00070, 0x88000,
			0x0, 0x88080, 0x70000, 0x64a82, 0xe466c, 0x00090,
			0x32c9a
		पूर्ण,
		/* 100 -165 */
		अणु
			0x70000, 0x44880, 0x4477f, 0x77880, 0x00070, 0x88000,
			0x0, 0x880b0, 0x0, 0x64b82, 0xe466c, 0x00090, 0x32c9a
		पूर्ण
	पूर्ण
पूर्ण;

अटल u32 curveindex_5g[TARGET_CHNL_NUM_5G] = अणु0पूर्ण;

अटल u32 curveindex_2g[TARGET_CHNL_NUM_2G] = अणु0पूर्ण;

अटल u32 tarअ_लोhnl_5g[TARGET_CHNL_NUM_5G] = अणु
	25141, 25116, 25091, 25066, 25041,
	25016, 24991, 24966, 24941, 24917,
	24892, 24867, 24843, 24818, 24794,
	24770, 24765, 24721, 24697, 24672,
	24648, 24624, 24600, 24576, 24552,
	24528, 24504, 24480, 24457, 24433,
	24409, 24385, 24362, 24338, 24315,
	24291, 24268, 24245, 24221, 24198,
	24175, 24151, 24128, 24105, 24082,
	24059, 24036, 24013, 23990, 23967,
	23945, 23922, 23899, 23876, 23854,
	23831, 23809, 23786, 23764, 23741,
	23719, 23697, 23674, 23652, 23630,
	23608, 23586, 23564, 23541, 23519,
	23498, 23476, 23454, 23432, 23410,
	23388, 23367, 23345, 23323, 23302,
	23280, 23259, 23237, 23216, 23194,
	23173, 23152, 23130, 23109, 23088,
	23067, 23046, 23025, 23003, 22982,
	22962, 22941, 22920, 22899, 22878,
	22857, 22837, 22816, 22795, 22775,
	22754, 22733, 22713, 22692, 22672,
	22652, 22631, 22611, 22591, 22570,
	22550, 22530, 22510, 22490, 22469,
	22449, 22429, 22409, 22390, 22370,
	22350, 22336, 22310, 22290, 22271,
	22251, 22231, 22212, 22192, 22173,
	22153, 22134, 22114, 22095, 22075,
	22056, 22037, 22017, 21998, 21979,
	21960, 21941, 21921, 21902, 21883,
	21864, 21845, 21826, 21807, 21789,
	21770, 21751, 21732, 21713, 21695,
	21676, 21657, 21639, 21620, 21602,
	21583, 21565, 21546, 21528, 21509,
	21491, 21473, 21454, 21436, 21418,
	21400, 21381, 21363, 21345, 21327,
	21309, 21291, 21273, 21255, 21237,
	21219, 21201, 21183, 21166, 21148,
	21130, 21112, 21095, 21077, 21059,
	21042, 21024, 21007, 20989, 20972,
	25679, 25653, 25627, 25601, 25575,
	25549, 25523, 25497, 25471, 25446,
	25420, 25394, 25369, 25343, 25318,
	25292, 25267, 25242, 25216, 25191,
	25166
पूर्ण;

/* channel 1~14 */
अटल u32 tarअ_लोhnl_2g[TARGET_CHNL_NUM_2G] = अणु
	26084, 26030, 25976, 25923, 25869, 25816, 25764,
	25711, 25658, 25606, 25554, 25502, 25451, 25328
पूर्ण;

अटल u32 _rtl92d_phy_calculate_bit_shअगरt(u32 biपंचांगask)
अणु
	u32 i = ffs(biपंचांगask);

	वापस i ? i - 1 : 32;
पूर्ण

u32 rtl92d_phy_query_bb_reg(काष्ठा ieee80211_hw *hw, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 वापसvalue, originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE, "regaddr(%#x), bitmask(%#x)\n",
		regaddr, biपंचांगask);
	अगर (rtlhal->during_mac1init_radioa || rtlhal->during_mac0init_radiob) अणु
		u8 dbi_direct = 0;

		/* mac1 use phy0 पढ़ो radio_b. */
		/* mac0 use phy1 पढ़ो radio_b. */
		अगर (rtlhal->during_mac1init_radioa)
			dbi_direct = BIT(3);
		अन्यथा अगर (rtlhal->during_mac0init_radiob)
			dbi_direct = BIT(3) | BIT(2);
		originalvalue = rtl92de_पढ़ो_dword_dbi(hw, (u16)regaddr,
			dbi_direct);
	पूर्ण अन्यथा अणु
		originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
	पूर्ण
	bitshअगरt = _rtl92d_phy_calculate_bit_shअगरt(biपंचांगask);
	वापसvalue = (originalvalue & biपंचांगask) >> bitshअगरt;
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"BBR MASK=0x%x Addr[0x%x]=0x%x\n",
		biपंचांगask, regaddr, originalvalue);
	वापस वापसvalue;
पूर्ण

व्योम rtl92d_phy_set_bb_reg(काष्ठा ieee80211_hw *hw,
			   u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u8 dbi_direct = 0;
	u32 originalvalue, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);
	अगर (rtlhal->during_mac1init_radioa)
		dbi_direct = BIT(3);
	अन्यथा अगर (rtlhal->during_mac0init_radiob)
		/* mac0 use phy1 ग_लिखो radio_b. */
		dbi_direct = BIT(3) | BIT(2);
	अगर (biपंचांगask != MASKDWORD) अणु
		अगर (rtlhal->during_mac1init_radioa ||
		    rtlhal->during_mac0init_radiob)
			originalvalue = rtl92de_पढ़ो_dword_dbi(hw,
					(u16) regaddr,
					dbi_direct);
		अन्यथा
			originalvalue = rtl_पढ़ो_dword(rtlpriv, regaddr);
		bitshअगरt = _rtl92d_phy_calculate_bit_shअगरt(biपंचांगask);
		data = ((originalvalue & (~biपंचांगask)) | (data << bitshअगरt));
	पूर्ण
	अगर (rtlhal->during_mac1init_radioa || rtlhal->during_mac0init_radiob)
		rtl92de_ग_लिखो_dword_dbi(hw, (u16) regaddr, data, dbi_direct);
	अन्यथा
		rtl_ग_लिखो_dword(rtlpriv, regaddr, data);
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x)\n",
		regaddr, biपंचांगask, data);
पूर्ण

अटल u32 _rtl92d_phy_rf_serial_पढ़ो(काष्ठा ieee80211_hw *hw,
				      क्रमागत radio_path rfpath, u32 offset)
अणु

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];
	u32 newoffset;
	u32 पंचांगpदीर्घ, पंचांगpदीर्घ2;
	u8 rfpi_enable = 0;
	u32 retvalue;

	newoffset = offset;
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
	udelay(50);
	udelay(50);
	rtl_set_bbreg(hw, RFPGA0_XA_HSSIPARAMETER2, MASKDWORD,
		पंचांगpदीर्घ | BLSSIREADEDGE);
	udelay(10);
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
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE, "RFR-%d Addr[0x%x] = 0x%x\n",
		rfpath, pphyreg->rf_rb, retvalue);
	वापस retvalue;
पूर्ण

अटल व्योम _rtl92d_phy_rf_serial_ग_लिखो(काष्ठा ieee80211_hw *hw,
					क्रमागत radio_path rfpath,
					u32 offset, u32 data)
अणु
	u32 data_and_addr;
	u32 newoffset;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];

	newoffset = offset;
	/* T65 RF */
	data_and_addr = ((newoffset << 20) | (data & 0x000fffff)) & 0x0fffffff;
	rtl_set_bbreg(hw, pphyreg->rf3wire_offset, MASKDWORD, data_and_addr);
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE, "RFW-%d Addr[0x%x]=0x%x\n",
		rfpath, pphyreg->rf3wire_offset, data_and_addr);
पूर्ण

u32 rtl92d_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			    क्रमागत radio_path rfpath, u32 regaddr, u32 biपंचांगask)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 original_value, पढ़ोback_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x)\n",
		regaddr, rfpath, biपंचांगask);
	spin_lock(&rtlpriv->locks.rf_lock);
	original_value = _rtl92d_phy_rf_serial_पढ़ो(hw, rfpath, regaddr);
	bitshअगरt = _rtl92d_phy_calculate_bit_shअगरt(biपंचांगask);
	पढ़ोback_value = (original_value & biपंचांगask) >> bitshअगरt;
	spin_unlock(&rtlpriv->locks.rf_lock);
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), rfpath(%#x), bitmask(%#x), original_value(%#x)\n",
		regaddr, rfpath, biपंचांगask, original_value);
	वापस पढ़ोback_value;
पूर्ण

व्योम rtl92d_phy_set_rf_reg(काष्ठा ieee80211_hw *hw, क्रमागत radio_path rfpath,
	u32 regaddr, u32 biपंचांगask, u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 original_value, bitshअगरt;

	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);
	अगर (biपंचांगask == 0)
		वापस;
	spin_lock(&rtlpriv->locks.rf_lock);
	अगर (rtlphy->rf_mode != RF_OP_BY_FW) अणु
		अगर (biपंचांगask != RFREG_OFFSET_MASK) अणु
			original_value = _rtl92d_phy_rf_serial_पढ़ो(hw,
				rfpath, regaddr);
			bitshअगरt = _rtl92d_phy_calculate_bit_shअगरt(biपंचांगask);
			data = ((original_value & (~biपंचांगask)) |
				(data << bitshअगरt));
		पूर्ण
		_rtl92d_phy_rf_serial_ग_लिखो(hw, rfpath, regaddr, data);
	पूर्ण
	spin_unlock(&rtlpriv->locks.rf_lock);
	rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
		"regaddr(%#x), bitmask(%#x), data(%#x), rfpath(%#x)\n",
		regaddr, biपंचांगask, data, rfpath);
पूर्ण

bool rtl92d_phy_mac_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;
	u32 arraylength;
	u32 *ptrarray;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Read Rtl819XMACPHY_Array\n");
	arraylength = MAC_2T_ARRAYLENGTH;
	ptrarray = rtl8192de_mac_2tarray;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Img:Rtl819XMAC_Array\n");
	क्रम (i = 0; i < arraylength; i = i + 2)
		rtl_ग_लिखो_byte(rtlpriv, ptrarray[i], (u8) ptrarray[i + 1]);
	अगर (rtlpriv->rtlhal.macphymode == SINGLEMAC_SINGLEPHY) अणु
		/* improve 2-stream TX EVM */
		/* rtl_ग_लिखो_byte(rtlpriv, 0x14,0x71); */
		/* AMPDU aggregation number 9 */
		/* rtl_ग_लिखो_word(rtlpriv, REG_MAX_AGGR_NUM, MAX_AGGR_NUM); */
		rtl_ग_लिखो_byte(rtlpriv, REG_MAX_AGGR_NUM, 0x0B);
	पूर्ण अन्यथा अणु
		/* 92D need to test to decide the num. */
		rtl_ग_लिखो_byte(rtlpriv, REG_MAX_AGGR_NUM, 0x07);
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम _rtl92d_phy_init_bb_rf_रेजिस्टर_definition(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	/* RF Interface Sowrtware Control */
	/* 16 LSBs अगर पढ़ो 32-bit from 0x870 */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x870 (16-bit क्रम 0x872) */
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfs = RFPGA0_XAB_RFINTERFACESW;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x874 */
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfs = RFPGA0_XCD_RFINTERFACESW;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x874 (16-bit क्रम 0x876) */

	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfs = RFPGA0_XCD_RFINTERFACESW;
	/* RF Interface Readback Value */
	/* 16 LSBs अगर पढ़ो 32-bit from 0x8E0 */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfi = RFPGA0_XAB_RFINTERFACERB;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x8E0 (16-bit क्रम 0x8E2) */
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfi = RFPGA0_XAB_RFINTERFACERB;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x8E4 */
	rtlphy->phyreg_def[RF90_PATH_C].rfपूर्णांकfi = RFPGA0_XCD_RFINTERFACERB;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x8E4 (16-bit क्रम 0x8E6) */
	rtlphy->phyreg_def[RF90_PATH_D].rfपूर्णांकfi = RFPGA0_XCD_RFINTERFACERB;

	/* RF Interface Output (and Enable) */
	/* 16 LSBs अगर पढ़ो 32-bit from 0x860 */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfo = RFPGA0_XA_RFINTERFACEOE;
	/* 16 LSBs अगर पढ़ो 32-bit from 0x864 */
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfo = RFPGA0_XB_RFINTERFACEOE;

	/* RF Interface (Output and)  Enable */
	/* 16 MSBs अगर पढ़ो 32-bit from 0x860 (16-bit क्रम 0x862) */
	rtlphy->phyreg_def[RF90_PATH_A].rfपूर्णांकfe = RFPGA0_XA_RFINTERFACEOE;
	/* 16 MSBs अगर पढ़ो 32-bit from 0x864 (16-bit क्रम 0x866) */
	rtlphy->phyreg_def[RF90_PATH_B].rfपूर्णांकfe = RFPGA0_XB_RFINTERFACEOE;

	/* Addr of LSSI. Wirte RF रेजिस्टर by driver */
	/* LSSI Parameter */
	rtlphy->phyreg_def[RF90_PATH_A].rf3wire_offset =
				 RFPGA0_XA_LSSIPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_B].rf3wire_offset =
				 RFPGA0_XB_LSSIPARAMETER;

	/* RF parameter */
	/* BB Band Select */
	rtlphy->phyreg_def[RF90_PATH_A].rflssi_select = RFPGA0_XAB_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_B].rflssi_select = RFPGA0_XAB_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_C].rflssi_select = RFPGA0_XCD_RFPARAMETER;
	rtlphy->phyreg_def[RF90_PATH_D].rflssi_select = RFPGA0_XCD_RFPARAMETER;

	/* Tx AGC Gain Stage (same क्रम all path. Should we हटाओ this?) */
	/* Tx gain stage */
	rtlphy->phyreg_def[RF90_PATH_A].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	/* Tx gain stage */
	rtlphy->phyreg_def[RF90_PATH_B].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	/* Tx gain stage */
	rtlphy->phyreg_def[RF90_PATH_C].rftxgain_stage = RFPGA0_TXGAINSTAGE;
	/* Tx gain stage */
	rtlphy->phyreg_def[RF90_PATH_D].rftxgain_stage = RFPGA0_TXGAINSTAGE;

	/* Tranceiver A~D HSSI Parameter-1 */
	/* wire control parameter1 */
	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para1 = RFPGA0_XA_HSSIPARAMETER1;
	/* wire control parameter1 */
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para1 = RFPGA0_XB_HSSIPARAMETER1;

	/* Tranceiver A~D HSSI Parameter-2 */
	/* wire control parameter2 */
	rtlphy->phyreg_def[RF90_PATH_A].rfhssi_para2 = RFPGA0_XA_HSSIPARAMETER2;
	/* wire control parameter2 */
	rtlphy->phyreg_def[RF90_PATH_B].rfhssi_para2 = RFPGA0_XB_HSSIPARAMETER2;

	/* RF चयन Control */
	/* TR/Ant चयन control */
	rtlphy->phyreg_def[RF90_PATH_A].rfsw_ctrl = RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_B].rfsw_ctrl = RFPGA0_XAB_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_C].rfsw_ctrl = RFPGA0_XCD_SWITCHCONTROL;
	rtlphy->phyreg_def[RF90_PATH_D].rfsw_ctrl = RFPGA0_XCD_SWITCHCONTROL;

	/* AGC control 1 */
	rtlphy->phyreg_def[RF90_PATH_A].rfagc_control1 = ROFDM0_XAAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_B].rfagc_control1 = ROFDM0_XBAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_C].rfagc_control1 = ROFDM0_XCAGCCORE1;
	rtlphy->phyreg_def[RF90_PATH_D].rfagc_control1 = ROFDM0_XDAGCCORE1;

	/* AGC control 2  */
	rtlphy->phyreg_def[RF90_PATH_A].rfagc_control2 = ROFDM0_XAAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_B].rfagc_control2 = ROFDM0_XBAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_C].rfagc_control2 = ROFDM0_XCAGCCORE2;
	rtlphy->phyreg_def[RF90_PATH_D].rfagc_control2 = ROFDM0_XDAGCCORE2;

	/* RX AFE control 1 */
	rtlphy->phyreg_def[RF90_PATH_A].rfrxiq_imbal = ROFDM0_XARXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_B].rfrxiq_imbal = ROFDM0_XBRXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_C].rfrxiq_imbal = ROFDM0_XCRXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_D].rfrxiq_imbal = ROFDM0_XDRXIQIMBALANCE;

	/*RX AFE control 1 */
	rtlphy->phyreg_def[RF90_PATH_A].rfrx_afe = ROFDM0_XARXAFE;
	rtlphy->phyreg_def[RF90_PATH_B].rfrx_afe = ROFDM0_XBRXAFE;
	rtlphy->phyreg_def[RF90_PATH_C].rfrx_afe = ROFDM0_XCRXAFE;
	rtlphy->phyreg_def[RF90_PATH_D].rfrx_afe = ROFDM0_XDRXAFE;

	/* Tx AFE control 1 */
	rtlphy->phyreg_def[RF90_PATH_A].rftxiq_imbal = ROFDM0_XATXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_B].rftxiq_imbal = ROFDM0_XBTXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_C].rftxiq_imbal = ROFDM0_XCTXIQIMBALANCE;
	rtlphy->phyreg_def[RF90_PATH_D].rftxiq_imbal = ROFDM0_XDTXIQIMBALANCE;

	/* Tx AFE control 2 */
	rtlphy->phyreg_def[RF90_PATH_A].rftx_afe = ROFDM0_XATXAFE;
	rtlphy->phyreg_def[RF90_PATH_B].rftx_afe = ROFDM0_XBTXAFE;
	rtlphy->phyreg_def[RF90_PATH_C].rftx_afe = ROFDM0_XCTXAFE;
	rtlphy->phyreg_def[RF90_PATH_D].rftx_afe = ROFDM0_XDTXAFE;

	/* Tranceiver LSSI Readback SI mode */
	rtlphy->phyreg_def[RF90_PATH_A].rf_rb = RFPGA0_XA_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rb = RFPGA0_XB_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_C].rf_rb = RFPGA0_XC_LSSIREADBACK;
	rtlphy->phyreg_def[RF90_PATH_D].rf_rb = RFPGA0_XD_LSSIREADBACK;

	/* Tranceiver LSSI Readback PI mode */
	rtlphy->phyreg_def[RF90_PATH_A].rf_rbpi = TRANSCEIVERA_HSPI_READBACK;
	rtlphy->phyreg_def[RF90_PATH_B].rf_rbpi = TRANSCEIVERB_HSPI_READBACK;
पूर्ण

अटल bool _rtl92d_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
	u8 configtype)
अणु
	पूर्णांक i;
	u32 *phy_regarray_table;
	u32 *agctab_array_table = शून्य;
	u32 *agctab_5garray_table;
	u16 phy_reg_arraylen, agctab_arraylen = 0, agctab_5garraylen;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	/* Normal chip,Mac0 use AGC_TAB.txt क्रम 2G and 5G band. */
	अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
		agctab_arraylen = AGCTAB_ARRAYLENGTH;
		agctab_array_table = rtl8192de_agctab_array;
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			" ===> phy:MAC0, Rtl819XAGCTAB_Array\n");
	पूर्ण अन्यथा अणु
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			agctab_arraylen = AGCTAB_2G_ARRAYLENGTH;
			agctab_array_table = rtl8192de_agctab_2garray;
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				" ===> phy:MAC1, Rtl819XAGCTAB_2GArray\n");
		पूर्ण अन्यथा अणु
			agctab_5garraylen = AGCTAB_5G_ARRAYLENGTH;
			agctab_5garray_table = rtl8192de_agctab_5garray;
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				" ===> phy:MAC1, Rtl819XAGCTAB_5GArray\n");

		पूर्ण
	पूर्ण
	phy_reg_arraylen = PHY_REG_2T_ARRAYLENGTH;
	phy_regarray_table = rtl8192de_phy_reg_2tarray;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		" ===> phy:Rtl819XPHY_REG_Array_PG\n");
	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_reg_arraylen; i = i + 2) अणु
			rtl_addr_delay(phy_regarray_table[i]);
			rtl_set_bbreg(hw, phy_regarray_table[i], MASKDWORD,
				      phy_regarray_table[i + 1]);
			udelay(1);
			rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
				"The phy_regarray_table[0] is %x Rtl819XPHY_REGArray[1] is %x\n",
				phy_regarray_table[i],
				phy_regarray_table[i + 1]);
		पूर्ण
	पूर्ण अन्यथा अगर (configtype == BASEBAND_CONFIG_AGC_TAB) अणु
		अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
			क्रम (i = 0; i < agctab_arraylen; i = i + 2) अणु
				rtl_set_bbreg(hw, agctab_array_table[i],
					MASKDWORD,
					agctab_array_table[i + 1]);
				/* Add 1us delay between BB/RF रेजिस्टर
				 * setting. */
				udelay(1);
				rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
					"The Rtl819XAGCTAB_Array_Table[0] is %u Rtl819XPHY_REGArray[1] is %u\n",
					agctab_array_table[i],
					agctab_array_table[i + 1]);
			पूर्ण
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"Normal Chip, MAC0, load Rtl819XAGCTAB_Array\n");
		पूर्ण अन्यथा अणु
			अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
				क्रम (i = 0; i < agctab_arraylen; i = i + 2) अणु
					rtl_set_bbreg(hw, agctab_array_table[i],
						MASKDWORD,
						agctab_array_table[i + 1]);
					/* Add 1us delay between BB/RF रेजिस्टर
					 * setting. */
					udelay(1);
					rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
						"The Rtl819XAGCTAB_Array_Table[0] is %u Rtl819XPHY_REGArray[1] is %u\n",
						agctab_array_table[i],
						agctab_array_table[i + 1]);
				पूर्ण
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"Load Rtl819XAGCTAB_2GArray\n");
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < agctab_5garraylen; i = i + 2) अणु
					rtl_set_bbreg(hw,
						agctab_5garray_table[i],
						MASKDWORD,
						agctab_5garray_table[i + 1]);
					/* Add 1us delay between BB/RF रेजिस्टरi
					 * setting. */
					udelay(1);
					rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
						"The Rtl819XAGCTAB_5GArray_Table[0] is %u Rtl819XPHY_REGArray[1] is %u\n",
						agctab_5garray_table[i],
						agctab_5garray_table[i + 1]);
				पूर्ण
				rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
					"Load Rtl819XAGCTAB_5GArray\n");
			पूर्ण
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल व्योम _rtl92d_store_pwrindex_dअगरfrate_offset(काष्ठा ieee80211_hw *hw,
						   u32 regaddr, u32 biपंचांगask,
						   u32 data)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	पूर्णांक index;

	अगर (regaddr == RTXAGC_A_RATE18_06)
		index = 0;
	अन्यथा अगर (regaddr == RTXAGC_A_RATE54_24)
		index = 1;
	अन्यथा अगर (regaddr == RTXAGC_A_CCK1_MCS32)
		index = 6;
	अन्यथा अगर (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && biपंचांगask == 0xffffff00)
		index = 7;
	अन्यथा अगर (regaddr == RTXAGC_A_MCS03_MCS00)
		index = 2;
	अन्यथा अगर (regaddr == RTXAGC_A_MCS07_MCS04)
		index = 3;
	अन्यथा अगर (regaddr == RTXAGC_A_MCS11_MCS08)
		index = 4;
	अन्यथा अगर (regaddr == RTXAGC_A_MCS15_MCS12)
		index = 5;
	अन्यथा अगर (regaddr == RTXAGC_B_RATE18_06)
		index = 8;
	अन्यथा अगर (regaddr == RTXAGC_B_RATE54_24)
		index = 9;
	अन्यथा अगर (regaddr == RTXAGC_B_CCK1_55_MCS32)
		index = 14;
	अन्यथा अगर (regaddr == RTXAGC_B_CCK11_A_CCK2_11 && biपंचांगask == 0x000000ff)
		index = 15;
	अन्यथा अगर (regaddr == RTXAGC_B_MCS03_MCS00)
		index = 10;
	अन्यथा अगर (regaddr == RTXAGC_B_MCS07_MCS04)
		index = 11;
	अन्यथा अगर (regaddr == RTXAGC_B_MCS11_MCS08)
		index = 12;
	अन्यथा अगर (regaddr == RTXAGC_B_MCS15_MCS12)
		index = 13;
	अन्यथा
		वापस;

	rtlphy->mcs_offset[rtlphy->pwrgroup_cnt][index] = data;
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
		"MCSTxPowerLevelOriginalOffset[%d][%d] = 0x%x\n",
		rtlphy->pwrgroup_cnt, index,
		rtlphy->mcs_offset[rtlphy->pwrgroup_cnt][index]);
	अगर (index == 13)
		rtlphy->pwrgroup_cnt++;
पूर्ण

अटल bool _rtl92d_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
	u8 configtype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;
	u32 *phy_regarray_table_pg;
	u16 phy_regarray_pg_len;

	phy_regarray_pg_len = PHY_REG_ARRAY_PG_LENGTH;
	phy_regarray_table_pg = rtl8192de_phy_reg_array_pg;
	अगर (configtype == BASEBAND_CONFIG_PHY_REG) अणु
		क्रम (i = 0; i < phy_regarray_pg_len; i = i + 3) अणु
			rtl_addr_delay(phy_regarray_table_pg[i]);
			_rtl92d_store_pwrindex_dअगरfrate_offset(hw,
				phy_regarray_table_pg[i],
				phy_regarray_table_pg[i + 1],
				phy_regarray_table_pg[i + 2]);
		पूर्ण
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_TRACE,
			"configtype != BaseBand_Config_PHY_REG\n");
	पूर्ण
	वापस true;
पूर्ण

अटल bool _rtl92d_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	bool rtstatus = true;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "==>\n");
	rtstatus = _rtl92d_phy_config_bb_with_headerfile(hw,
		BASEBAND_CONFIG_PHY_REG);
	अगर (!rtstatus) अणु
		pr_err("Write BB Reg Fail!!\n");
		वापस false;
	पूर्ण

	/* अगर (rtlphy->rf_type == RF_1T2R) अणु
	 *      _rtl92c_phy_bb_config_1t(hw);
	 *     rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Config to 1T!!\n");
	 *पूर्ण */

	अगर (rtlefuse->स्वतःload_failflag == false) अणु
		rtlphy->pwrgroup_cnt = 0;
		rtstatus = _rtl92d_phy_config_bb_with_pgheaderfile(hw,
			BASEBAND_CONFIG_PHY_REG);
	पूर्ण
	अगर (!rtstatus) अणु
		pr_err("BB_PG Reg Fail!!\n");
		वापस false;
	पूर्ण
	rtstatus = _rtl92d_phy_config_bb_with_headerfile(hw,
		BASEBAND_CONFIG_AGC_TAB);
	अगर (!rtstatus) अणु
		pr_err("AGC Table Fail\n");
		वापस false;
	पूर्ण
	rtlphy->cck_high_घातer = (bool) (rtl_get_bbreg(hw,
		RFPGA0_XA_HSSIPARAMETER2, 0x200));

	वापस true;
पूर्ण

bool rtl92d_phy_bb_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 regval;
	u32 regvaldw;
	u8 value;

	_rtl92d_phy_init_bb_rf_रेजिस्टर_definition(hw);
	regval = rtl_पढ़ो_word(rtlpriv, REG_SYS_FUNC_EN);
	rtl_ग_लिखो_word(rtlpriv, REG_SYS_FUNC_EN,
		       regval | BIT(13) | BIT(0) | BIT(1));
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_PLL_CTRL, 0x83);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_PLL_CTRL + 1, 0xdb);
	/* 0x1f bit7 bit6 represent क्रम mac0/mac1 driver पढ़ोy */
	value = rtl_पढ़ो_byte(rtlpriv, REG_RF_CTRL);
	rtl_ग_लिखो_byte(rtlpriv, REG_RF_CTRL, value | RF_EN | RF_RSTB |
		RF_SDMRSTB);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, FEN_PPLL | FEN_PCIEA |
		FEN_DIO_PCIE | FEN_BB_GLB_RSTN | FEN_BBRSTB);
	rtl_ग_लिखो_byte(rtlpriv, REG_AFE_XTAL_CTRL + 1, 0x80);
	अगर (!(IS_92D_SINGLEPHY(rtlpriv->rtlhal.version))) अणु
		regvaldw = rtl_पढ़ो_dword(rtlpriv, REG_LEDCFG0);
		rtl_ग_लिखो_dword(rtlpriv, REG_LEDCFG0, regvaldw | BIT(23));
	पूर्ण

	वापस _rtl92d_phy_bb_config(hw);
पूर्ण

bool rtl92d_phy_rf_config(काष्ठा ieee80211_hw *hw)
अणु
	वापस rtl92d_phy_rf6052_config(hw);
पूर्ण

bool rtl92d_phy_config_rf_with_headerfile(काष्ठा ieee80211_hw *hw,
					  क्रमागत rf_content content,
					  क्रमागत radio_path rfpath)
अणु
	पूर्णांक i;
	u32 *radioa_array_table;
	u32 *radiob_array_table;
	u16 radioa_arraylen, radiob_arraylen;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	radioa_arraylen = RADIOA_2T_ARRAYLENGTH;
	radioa_array_table = rtl8192de_radioa_2tarray;
	radiob_arraylen = RADIOB_2T_ARRAYLENGTH;
	radiob_array_table = rtl8192de_radiob_2tarray;
	अगर (rtlpriv->efuse.पूर्णांकernal_pa_5g[0]) अणु
		radioa_arraylen = RADIOA_2T_INT_PA_ARRAYLENGTH;
		radioa_array_table = rtl8192de_radioa_2t_पूर्णांक_paarray;
	पूर्ण
	अगर (rtlpriv->efuse.पूर्णांकernal_pa_5g[1]) अणु
		radiob_arraylen = RADIOB_2T_INT_PA_ARRAYLENGTH;
		radiob_array_table = rtl8192de_radiob_2t_पूर्णांक_paarray;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"PHY_ConfigRFWithHeaderFile() Radio_A:Rtl819XRadioA_1TArray\n");
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"PHY_ConfigRFWithHeaderFile() Radio_B:Rtl819XRadioB_1TArray\n");
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "Radio No %x\n", rfpath);

	/* this only happens when DMDP, mac0 start on 2.4G,
	 * mac1 start on 5G, mac 0 has to set phy0&phy1
	 * pathA or mac1 has to set phy0&phy1 pathA */
	अगर ((content == radiob_txt) && (rfpath == RF90_PATH_A)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			" ===> althougth Path A, we load radiob.txt\n");
		radioa_arraylen = radiob_arraylen;
		radioa_array_table = radiob_array_table;
	पूर्ण
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
		क्रम (i = 0; i < radioa_arraylen; i = i + 2) अणु
			rtl_rfreg_delay(hw, rfpath, radioa_array_table[i],
					RFREG_OFFSET_MASK,
					radioa_array_table[i + 1]);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_B:
		क्रम (i = 0; i < radiob_arraylen; i = i + 2) अणु
			rtl_rfreg_delay(hw, rfpath, radiob_array_table[i],
					RFREG_OFFSET_MASK,
					radiob_array_table[i + 1]);
		पूर्ण
		अवरोध;
	हाल RF90_PATH_C:
	हाल RF90_PATH_D:
		pr_err("switch case %#x not processed\n", rfpath);
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

व्योम rtl92d_phy_get_hw_reg_originalvalue(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	rtlphy->शेष_initialgain[0] =
	    (u8) rtl_get_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[1] =
	    (u8) rtl_get_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[2] =
	    (u8) rtl_get_bbreg(hw, ROFDM0_XCAGCCORE1, MASKBYTE0);
	rtlphy->शेष_initialgain[3] =
	    (u8) rtl_get_bbreg(hw, ROFDM0_XDAGCCORE1, MASKBYTE0);
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

अटल व्योम _rtl92d_get_txघातer_index(काष्ठा ieee80211_hw *hw, u8 channel,
	u8 *cckघातerlevel, u8 *ofdmघातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 index = (channel - 1);

	/* 1. CCK */
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		/* RF-A */
		cckघातerlevel[RF90_PATH_A] =
				 rtlefuse->txpwrlevel_cck[RF90_PATH_A][index];
		/* RF-B */
		cckघातerlevel[RF90_PATH_B] =
				 rtlefuse->txpwrlevel_cck[RF90_PATH_B][index];
	पूर्ण अन्यथा अणु
		cckघातerlevel[RF90_PATH_A] = 0;
		cckघातerlevel[RF90_PATH_B] = 0;
	पूर्ण
	/* 2. OFDM क्रम 1S or 2S */
	अगर (rtlphy->rf_type == RF_1T2R || rtlphy->rf_type == RF_1T1R) अणु
		/*  Read HT 40 OFDM TX घातer */
		ofdmघातerlevel[RF90_PATH_A] =
		    rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_A][index];
		ofdmघातerlevel[RF90_PATH_B] =
		    rtlefuse->txpwrlevel_ht40_1s[RF90_PATH_B][index];
	पूर्ण अन्यथा अगर (rtlphy->rf_type == RF_2T2R) अणु
		/* Read HT 40 OFDM TX घातer */
		ofdmघातerlevel[RF90_PATH_A] =
		    rtlefuse->txpwrlevel_ht40_2s[RF90_PATH_A][index];
		ofdmघातerlevel[RF90_PATH_B] =
		    rtlefuse->txpwrlevel_ht40_2s[RF90_PATH_B][index];
	पूर्ण
पूर्ण

अटल व्योम _rtl92d_ccxघातer_index_check(काष्ठा ieee80211_hw *hw,
	u8 channel, u8 *cckघातerlevel, u8 *ofdmघातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	rtlphy->cur_cck_txpwridx = cckघातerlevel[0];
	rtlphy->cur_ofdm24g_txpwridx = ofdmघातerlevel[0];
पूर्ण

अटल u8 _rtl92c_phy_get_rightchnlplace(u8 chnl)
अणु
	u8 place = chnl;

	अगर (chnl > 14) अणु
		क्रम (place = 14; place < माप(channel5g); place++) अणु
			अगर (channel5g[place] == chnl) अणु
				place++;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस place;
पूर्ण

व्योम rtl92d_phy_set_txघातer_level(काष्ठा ieee80211_hw *hw, u8 channel)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 cckघातerlevel[2], ofdmघातerlevel[2];

	अगर (!rtlefuse->txpwr_fromeprom)
		वापस;
	channel = _rtl92c_phy_get_rightchnlplace(channel);
	_rtl92d_get_txघातer_index(hw, channel, &cckघातerlevel[0],
		&ofdmघातerlevel[0]);
	अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
		_rtl92d_ccxघातer_index_check(hw, channel, &cckघातerlevel[0],
				&ofdmघातerlevel[0]);
	अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
		rtl92d_phy_rf6052_set_cck_txघातer(hw, &cckघातerlevel[0]);
	rtl92d_phy_rf6052_set_ofdm_txघातer(hw, &ofdmघातerlevel[0], channel);
पूर्ण

व्योम rtl92d_phy_set_bw_mode(काष्ठा ieee80211_hw *hw,
			    क्रमागत nl80211_channel_type ch_type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	अचिन्हित दीर्घ flag = 0;
	u8 reg_prsr_rsc;
	u8 reg_bw_opmode;

	अगर (rtlphy->set_bwmode_inprogress)
		वापस;
	अगर ((is_hal_stop(rtlhal)) || (RT_CANNOT_IO(hw))) अणु
		rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
			"FALSE driver sleep or unload\n");
		वापस;
	पूर्ण
	rtlphy->set_bwmode_inprogress = true;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "Switch to %s bandwidth\n",
		rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20 ?
		"20MHz" : "40MHz");
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
		/* SET BIT10 BIT11  क्रम receive cck */
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10) |
			      BIT(11), 3);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BRFMOD, 0x1);
		rtl_set_bbreg(hw, RFPGA1_RFMOD, BRFMOD, 0x1);
		/* Set Control channel to upper or lower.
		 * These settings are required only क्रम 40MHz */
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
			rtl_set_bbreg(hw, RCCK0_SYSTEM, BCCKSIDEBAND,
				(mac->cur_40_prime_sc >> 1));
			rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
		पूर्ण
		rtl_set_bbreg(hw, ROFDM1_LSTF, 0xC00, mac->cur_40_prime_sc);
		/* SET BIT10 BIT11  क्रम receive cck */
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10) |
			      BIT(11), 0);
		rtl_set_bbreg(hw, 0x818, (BIT(26) | BIT(27)),
			(mac->cur_40_prime_sc ==
			HAL_PRIME_CHNL_OFFSET_LOWER) ? 2 : 1);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n",
		       rtlphy->current_chan_bw);
		अवरोध;

	पूर्ण
	rtl92d_phy_rf6052_set_bandwidth(hw, rtlphy->current_chan_bw);
	rtlphy->set_bwmode_inprogress = false;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");
पूर्ण

अटल व्योम _rtl92d_phy_stop_trx_beक्रमe_changeband(काष्ठा ieee80211_hw *hw)
अणु
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0);
	rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKBYTE0, 0x00);
	rtl_set_bbreg(hw, ROFDM1_TRXPATHENABLE, BDWORD, 0x0);
पूर्ण

अटल व्योम rtl92d_phy_चयन_wirelessband(काष्ठा ieee80211_hw *hw, u8 band)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 value8;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "==>\n");
	rtlhal->bandset = band;
	rtlhal->current_bandtype = band;
	अगर (IS_92D_SINGLEPHY(rtlhal->version))
		rtlhal->bandset = BAND_ON_BOTH;
	/* stop RX/Tx */
	_rtl92d_phy_stop_trx_beक्रमe_changeband(hw);
	/* reconfig BB/RF according to wireless mode */
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		/* BB & RF Config */
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "====>2.4G\n");
		अगर (rtlhal->पूर्णांकerfaceindex == 1)
			_rtl92d_phy_config_bb_with_headerfile(hw,
				BASEBAND_CONFIG_AGC_TAB);
	पूर्ण अन्यथा अणु
		/* 5G band */
		rtl_dbg(rtlpriv, COMP_CMD, DBG_DMESG, "====>5G\n");
		अगर (rtlhal->पूर्णांकerfaceindex == 1)
			_rtl92d_phy_config_bb_with_headerfile(hw,
				BASEBAND_CONFIG_AGC_TAB);
	पूर्ण
	rtl92d_update_bbrf_configuration(hw);
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G)
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BCCKEN, 0x1);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 0x1);

	/* 20M BW. */
	/* rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER2, BIT(10), 1); */
	rtlhal->reloadtxघातerindex = true;
	/* notice fw know band status  0x81[1]/0x53[1] = 0: 5G, 1: 2G */
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		value8 = rtl_पढ़ो_byte(rtlpriv,	(rtlhal->पूर्णांकerfaceindex ==
			0 ? REG_MAC0 : REG_MAC1));
		value8 |= BIT(1);
		rtl_ग_लिखो_byte(rtlpriv, (rtlhal->पूर्णांकerfaceindex ==
			0 ? REG_MAC0 : REG_MAC1), value8);
	पूर्ण अन्यथा अणु
		value8 = rtl_पढ़ो_byte(rtlpriv, (rtlhal->पूर्णांकerfaceindex ==
			0 ? REG_MAC0 : REG_MAC1));
		value8 &= (~BIT(1));
		rtl_ग_लिखो_byte(rtlpriv, (rtlhal->पूर्णांकerfaceindex ==
			0 ? REG_MAC0 : REG_MAC1), value8);
	पूर्ण
	mdelay(1);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "<==Switch Band OK\n");
पूर्ण

अटल व्योम _rtl92d_phy_reload_imr_setting(काष्ठा ieee80211_hw *hw,
	u8 channel, u8 rfpath)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 imr_num = MAX_RF_IMR_INDEX;
	u32 rfmask = RFREG_OFFSET_MASK;
	u8 group, i;
	अचिन्हित दीर्घ flag = 0;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "====>path %d\n", rfpath);
	अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_5G) अणु
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "====>5G\n");
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BIT(25) | BIT(24), 0);
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0xf);
		/* fc area 0xd2c */
		अगर (channel > 99)
			rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(13) |
				      BIT(14), 2);
		अन्यथा
			rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(13) |
				      BIT(14), 1);
		/* leave 0 क्रम channel1-14. */
		group = channel <= 64 ? 1 : 2;
		imr_num = MAX_RF_IMR_INDEX_NORMAL;
		क्रम (i = 0; i < imr_num; i++)
			rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath,
				      rf_reg_क्रम_5g_swchnl_normal[i], rfmask,
				      rf_imr_param_normal[0][group][i]);
		rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0x00f00000, 0);
		rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN, 1);
	पूर्ण अन्यथा अणु
		/* G band. */
		rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
			"Load RF IMR parameters for G band. IMR already setting %d\n",
			rtlpriv->rtlhal.load_imअक्रमiqk_setting_क्रम2g);
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "====>2.4G\n");
		अगर (!rtlpriv->rtlhal.load_imअक्रमiqk_setting_क्रम2g) अणु
			rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
				"Load RF IMR parameters for G band. %d\n",
				rfpath);
			rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
			rtl_set_bbreg(hw, RFPGA0_RFMOD, BIT(25) | BIT(24), 0);
			rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4,
				      0x00f00000, 0xf);
			imr_num = MAX_RF_IMR_INDEX_NORMAL;
			क्रम (i = 0; i < imr_num; i++) अणु
				rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath,
					      rf_reg_क्रम_5g_swchnl_normal[i],
					      RFREG_OFFSET_MASK,
					      rf_imr_param_normal[0][0][i]);
			पूर्ण
			rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4,
				      0x00f00000, 0);
			rtl_set_bbreg(hw, RFPGA0_RFMOD, BOFDMEN | BCCKEN, 3);
			rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "<====\n");
पूर्ण

अटल व्योम _rtl92d_phy_enable_rf_env(काष्ठा ieee80211_hw *hw,
	u8 rfpath, u32 *pu4_regval)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];

	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "====>\n");
	/*----Store original RFENV control type----*/
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
	हाल RF90_PATH_C:
		*pu4_regval = rtl_get_bbreg(hw, pphyreg->rfपूर्णांकfs, BRFSI_RFENV);
		अवरोध;
	हाल RF90_PATH_B:
	हाल RF90_PATH_D:
		*pu4_regval =
		    rtl_get_bbreg(hw, pphyreg->rfपूर्णांकfs, BRFSI_RFENV << 16);
		अवरोध;
	पूर्ण
	/*----Set RF_ENV enable----*/
	rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfe, BRFSI_RFENV << 16, 0x1);
	udelay(1);
	/*----Set RF_ENV output high----*/
	rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfo, BRFSI_RFENV, 0x1);
	udelay(1);
	/* Set bit number of Address and Data क्रम RF रेजिस्टर */
	/* Set 1 to 4 bits क्रम 8255 */
	rtl_set_bbreg(hw, pphyreg->rfhssi_para2, B3WIREADDRESSLENGTH, 0x0);
	udelay(1);
	/*Set 0 to 12 bits क्रम 8255 */
	rtl_set_bbreg(hw, pphyreg->rfhssi_para2, B3WIREDATALENGTH, 0x0);
	udelay(1);
	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "<====\n");
पूर्ण

अटल व्योम _rtl92d_phy_restore_rf_env(काष्ठा ieee80211_hw *hw, u8 rfpath,
				       u32 *pu4_regval)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा bb_reg_def *pphyreg = &rtlphy->phyreg_def[rfpath];

	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "=====>\n");
	/*----Restore RFENV control type----*/
	चयन (rfpath) अणु
	हाल RF90_PATH_A:
	हाल RF90_PATH_C:
		rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfs, BRFSI_RFENV, *pu4_regval);
		अवरोध;
	हाल RF90_PATH_B:
	हाल RF90_PATH_D:
		rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfs, BRFSI_RFENV << 16,
			      *pu4_regval);
		अवरोध;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "<=====\n");
पूर्ण

अटल व्योम _rtl92d_phy_चयन_rf_setting(काष्ठा ieee80211_hw *hw, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u8 path = rtlhal->current_bandtype ==
	    BAND_ON_5G ? RF90_PATH_A : RF90_PATH_B;
	u8 index = 0, i = 0, rfpath = RF90_PATH_A;
	bool need_pwr_करोwn = false, पूर्णांकernal_pa = false;
	u32 u4regvalue, mask = 0x1C000, value = 0, u4पंचांगp, u4पंचांगp2;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "====>\n");
	/* config path A क्रम 5G */
	अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "====>5G\n");
		u4पंचांगp = curveindex_5g[channel - 1];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"ver 1 set RF-A, 5G, 0x28 = 0x%x !!\n", u4पंचांगp);
		क्रम (i = 0; i < RF_CHNL_NUM_5G; i++) अणु
			अगर (channel == rf_chnl_5g[i] && channel <= 140)
				index = 0;
		पूर्ण
		क्रम (i = 0; i < RF_CHNL_NUM_5G_40M; i++) अणु
			अगर (channel == rf_chnl_5g_40m[i] && channel <= 140)
				index = 1;
		पूर्ण
		अगर (channel == 149 || channel == 155 || channel == 161)
			index = 2;
		अन्यथा अगर (channel == 151 || channel == 153 || channel == 163
			 || channel == 165)
			index = 3;
		अन्यथा अगर (channel == 157 || channel == 159)
			index = 4;

		अगर (rtlhal->macphymode == DUALMAC_DUALPHY
		    && rtlhal->पूर्णांकerfaceindex == 1) अणु
			need_pwr_करोwn = rtl92d_phy_enable_anotherphy(hw, false);
			rtlhal->during_mac1init_radioa = true;
			/* asume no this हाल */
			अगर (need_pwr_करोwn)
				_rtl92d_phy_enable_rf_env(hw, path,
							  &u4regvalue);
		पूर्ण
		क्रम (i = 0; i < RF_REG_NUM_FOR_C_CUT_5G; i++) अणु
			अगर (i == 0 && (rtlhal->macphymode == DUALMAC_DUALPHY)) अणु
				rtl_set_rfreg(hw, (क्रमागत radio_path)path,
					      rf_reg_क्रम_c_cut_5g[i],
					      RFREG_OFFSET_MASK, 0xE439D);
			पूर्ण अन्यथा अगर (rf_reg_क्रम_c_cut_5g[i] == RF_SYN_G4) अणु
				u4पंचांगp2 = (rf_reg_pram_c_5g[index][i] &
				     0x7FF) | (u4पंचांगp << 11);
				अगर (channel == 36)
					u4पंचांगp2 &= ~(BIT(7) | BIT(6));
				rtl_set_rfreg(hw, (क्रमागत radio_path)path,
					      rf_reg_क्रम_c_cut_5g[i],
					      RFREG_OFFSET_MASK, u4पंचांगp2);
			पूर्ण अन्यथा अणु
				rtl_set_rfreg(hw, (क्रमागत radio_path)path,
					      rf_reg_क्रम_c_cut_5g[i],
					      RFREG_OFFSET_MASK,
					      rf_reg_pram_c_5g[index][i]);
			पूर्ण
			rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
				"offset 0x%x value 0x%x path %d index %d readback 0x%x\n",
				rf_reg_क्रम_c_cut_5g[i],
				rf_reg_pram_c_5g[index][i],
				path, index,
				rtl_get_rfreg(hw, (क्रमागत radio_path)path,
					      rf_reg_क्रम_c_cut_5g[i],
					      RFREG_OFFSET_MASK));
		पूर्ण
		अगर (need_pwr_करोwn)
			_rtl92d_phy_restore_rf_env(hw, path, &u4regvalue);
		अगर (rtlhal->during_mac1init_radioa)
			rtl92d_phy_घातerकरोwn_anotherphy(hw, false);
		अगर (channel < 149)
			value = 0x07;
		अन्यथा अगर (channel >= 149)
			value = 0x02;
		अगर (channel >= 36 && channel <= 64)
			index = 0;
		अन्यथा अगर (channel >= 100 && channel <= 140)
			index = 1;
		अन्यथा
			index = 2;
		क्रम (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
			rfpath++) अणु
			अगर (rtlhal->macphymode == DUALMAC_DUALPHY &&
				rtlhal->पूर्णांकerfaceindex == 1)	/* MAC 1 5G */
				पूर्णांकernal_pa = rtlpriv->efuse.पूर्णांकernal_pa_5g[1];
			अन्यथा
				पूर्णांकernal_pa =
					 rtlpriv->efuse.पूर्णांकernal_pa_5g[rfpath];
			अगर (पूर्णांकernal_pa) अणु
				क्रम (i = 0;
				     i < RF_REG_NUM_FOR_C_CUT_5G_INTERNALPA;
				     i++) अणु
					rtl_set_rfreg(hw, rfpath,
						rf_क्रम_c_cut_5g_पूर्णांकernal_pa[i],
						RFREG_OFFSET_MASK,
						rf_pram_c_5g_पूर्णांक_pa[index][i]);
					rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
						"offset 0x%x value 0x%x path %d index %d\n",
						rf_क्रम_c_cut_5g_पूर्णांकernal_pa[i],
						rf_pram_c_5g_पूर्णांक_pa[index][i],
						rfpath, index);
				पूर्ण
			पूर्ण अन्यथा अणु
				rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath, 0x0B,
					      mask, value);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "====>2.4G\n");
		u4पंचांगp = curveindex_2g[channel - 1];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"ver 3 set RF-B, 2G, 0x28 = 0x%x !!\n", u4पंचांगp);
		अगर (channel == 1 || channel == 2 || channel == 4 || channel == 9
		    || channel == 10 || channel == 11 || channel == 12)
			index = 0;
		अन्यथा अगर (channel == 3 || channel == 13 || channel == 14)
			index = 1;
		अन्यथा अगर (channel >= 5 && channel <= 8)
			index = 2;
		अगर (rtlhal->macphymode == DUALMAC_DUALPHY) अणु
			path = RF90_PATH_A;
			अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
				need_pwr_करोwn =
					 rtl92d_phy_enable_anotherphy(hw, true);
				rtlhal->during_mac0init_radiob = true;

				अगर (need_pwr_करोwn)
					_rtl92d_phy_enable_rf_env(hw, path,
								  &u4regvalue);
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < RF_REG_NUM_FOR_C_CUT_2G; i++) अणु
			अगर (rf_reg_क्रम_c_cut_2g[i] == RF_SYN_G7)
				rtl_set_rfreg(hw, (क्रमागत radio_path)path,
					rf_reg_क्रम_c_cut_2g[i],
					RFREG_OFFSET_MASK,
					(rf_reg_param_क्रम_c_cut_2g[index][i] |
					BIT(17)));
			अन्यथा
				rtl_set_rfreg(hw, (क्रमागत radio_path)path,
					      rf_reg_क्रम_c_cut_2g[i],
					      RFREG_OFFSET_MASK,
					      rf_reg_param_क्रम_c_cut_2g
					      [index][i]);
			rtl_dbg(rtlpriv, COMP_RF, DBG_TRACE,
				"offset 0x%x value 0x%x mak 0x%x path %d index %d readback 0x%x\n",
				rf_reg_क्रम_c_cut_2g[i],
				rf_reg_param_क्रम_c_cut_2g[index][i],
				rf_reg_mask_क्रम_c_cut_2g[i], path, index,
				rtl_get_rfreg(hw, (क्रमागत radio_path)path,
					      rf_reg_क्रम_c_cut_2g[i],
					      RFREG_OFFSET_MASK));
		पूर्ण
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"cosa ver 3 set RF-B, 2G, 0x28 = 0x%x !!\n",
			rf_syn_g4_क्रम_c_cut_2g | (u4पंचांगp << 11));

		rtl_set_rfreg(hw, (क्रमागत radio_path)path, RF_SYN_G4,
			      RFREG_OFFSET_MASK,
			      rf_syn_g4_क्रम_c_cut_2g | (u4पंचांगp << 11));
		अगर (need_pwr_करोwn)
			_rtl92d_phy_restore_rf_env(hw, path, &u4regvalue);
		अगर (rtlhal->during_mac0init_radiob)
			rtl92d_phy_घातerकरोwn_anotherphy(hw, true);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "<====\n");
पूर्ण

u8 rtl92d_get_rightchnlplace_क्रम_iqk(u8 chnl)
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

#घोषणा MAX_TOLERANCE		5
#घोषणा IQK_DELAY_TIME		1	/* ms */
#घोषणा MAX_TOLERANCE_92D	3

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 _rtl92d_phy_patha_iqk(काष्ठा ieee80211_hw *hw, bool configpathb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 regeac, rege94, rege9c, regea4;
	u8 result = 0;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path A IQK!\n");
	/* path-A IQK setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path-A IQK setting!\n");
	अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
		rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x10008c1f);
		rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x10008c1f);
	पूर्ण अन्यथा अणु
		rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x10008c22);
		rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x10008c22);
	पूर्ण
	rtl_set_bbreg(hw, 0xe38, MASKDWORD, 0x82140102);
	rtl_set_bbreg(hw, 0xe3c, MASKDWORD, 0x28160206);
	/* path-B IQK setting */
	अगर (configpathb) अणु
		rtl_set_bbreg(hw, 0xe50, MASKDWORD, 0x10008c22);
		rtl_set_bbreg(hw, 0xe54, MASKDWORD, 0x10008c22);
		rtl_set_bbreg(hw, 0xe58, MASKDWORD, 0x82140102);
		rtl_set_bbreg(hw, 0xe5c, MASKDWORD, 0x28160206);
	पूर्ण
	/* LO calibration setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "LO calibration setting!\n");
	rtl_set_bbreg(hw, 0xe4c, MASKDWORD, 0x00462911);
	/* One shot, path A LOK & IQK */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "One shot, path A LOK & IQK!\n");
	rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf9000000);
	rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf8000000);
	/* delay x ms */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"Delay %d ms for One shot, path A LOK & IQK\n",
		IQK_DELAY_TIME);
	mdelay(IQK_DELAY_TIME);
	/* Check failed */
	regeac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeac = 0x%x\n", regeac);
	rege94 = rtl_get_bbreg(hw, 0xe94, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xe94 = 0x%x\n", rege94);
	rege9c = rtl_get_bbreg(hw, 0xe9c, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xe9c = 0x%x\n", rege9c);
	regea4 = rtl_get_bbreg(hw, 0xea4, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xea4 = 0x%x\n", regea4);
	अगर (!(regeac & BIT(28)) && (((rege94 & 0x03FF0000) >> 16) != 0x142) &&
	    (((rege9c & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा			/* अगर Tx not OK, ignore Rx */
		वापस result;
	/* अगर Tx is OK, check whether Rx is OK */
	अगर (!(regeac & BIT(27)) && (((regea4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((regeac & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path A Rx IQK fail!!\n");
	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 _rtl92d_phy_patha_iqk_5g_normal(काष्ठा ieee80211_hw *hw,
					  bool configpathb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 regeac, rege94, rege9c, regea4;
	u8 result = 0;
	u8 i;
	u8 retrycount = 2;
	u32 TXOKBIT = BIT(28), RXOKBIT = BIT(27);

	अगर (rtlhal->पूर्णांकerfaceindex == 1) अणु	/* PHY1 */
		TXOKBIT = BIT(31);
		RXOKBIT = BIT(30);
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path A IQK!\n");
	/* path-A IQK setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path-A IQK setting!\n");
	rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x18008c1f);
	rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x18008c1f);
	rtl_set_bbreg(hw, 0xe38, MASKDWORD, 0x82140307);
	rtl_set_bbreg(hw, 0xe3c, MASKDWORD, 0x68160960);
	/* path-B IQK setting */
	अगर (configpathb) अणु
		rtl_set_bbreg(hw, 0xe50, MASKDWORD, 0x18008c2f);
		rtl_set_bbreg(hw, 0xe54, MASKDWORD, 0x18008c2f);
		rtl_set_bbreg(hw, 0xe58, MASKDWORD, 0x82110000);
		rtl_set_bbreg(hw, 0xe5c, MASKDWORD, 0x68110000);
	पूर्ण
	/* LO calibration setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "LO calibration setting!\n");
	rtl_set_bbreg(hw, 0xe4c, MASKDWORD, 0x00462911);
	/* path-A PA on */
	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, MASKDWORD, 0x07000f60);
	rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE, MASKDWORD, 0x66e60e30);
	क्रम (i = 0; i < retrycount; i++) अणु
		/* One shot, path A LOK & IQK */
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"One shot, path A LOK & IQK!\n");
		rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf9000000);
		rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf8000000);
		/* delay x ms */
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"Delay %d ms for One shot, path A LOK & IQK.\n",
			IQK_DELAY_TIME);
		mdelay(IQK_DELAY_TIME * 10);
		/* Check failed */
		regeac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeac = 0x%x\n", regeac);
		rege94 = rtl_get_bbreg(hw, 0xe94, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xe94 = 0x%x\n", rege94);
		rege9c = rtl_get_bbreg(hw, 0xe9c, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xe9c = 0x%x\n", rege9c);
		regea4 = rtl_get_bbreg(hw, 0xea4, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xea4 = 0x%x\n", regea4);
		अगर (!(regeac & TXOKBIT) &&
		     (((rege94 & 0x03FF0000) >> 16) != 0x142)) अणु
			result |= 0x01;
		पूर्ण अन्यथा अणु /* अगर Tx not OK, ignore Rx */
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path A Tx IQK fail!!\n");
			जारी;
		पूर्ण

		/* अगर Tx is OK, check whether Rx is OK */
		अगर (!(regeac & RXOKBIT) &&
		    (((regea4 & 0x03FF0000) >> 16) != 0x132)) अणु
			result |= 0x02;
			अवरोध;
		पूर्ण अन्यथा अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path A Rx IQK fail!!\n");
		पूर्ण
	पूर्ण
	/* path A PA off */
	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, MASKDWORD,
		      rtlphy->iqk_bb_backup[0]);
	rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE, MASKDWORD,
		      rtlphy->iqk_bb_backup[1]);
	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 _rtl92d_phy_pathb_iqk(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 regeac, regeb4, regebc, regec4, regecc;
	u8 result = 0;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path B IQK!\n");
	/* One shot, path B LOK & IQK */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "One shot, path A LOK & IQK!\n");
	rtl_set_bbreg(hw, 0xe60, MASKDWORD, 0x00000002);
	rtl_set_bbreg(hw, 0xe60, MASKDWORD, 0x00000000);
	/* delay x ms  */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"Delay %d ms for One shot, path B LOK & IQK\n", IQK_DELAY_TIME);
	mdelay(IQK_DELAY_TIME);
	/* Check failed */
	regeac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeac = 0x%x\n", regeac);
	regeb4 = rtl_get_bbreg(hw, 0xeb4, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeb4 = 0x%x\n", regeb4);
	regebc = rtl_get_bbreg(hw, 0xebc, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xebc = 0x%x\n", regebc);
	regec4 = rtl_get_bbreg(hw, 0xec4, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xec4 = 0x%x\n", regec4);
	regecc = rtl_get_bbreg(hw, 0xecc, MASKDWORD);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xecc = 0x%x\n", regecc);
	अगर (!(regeac & BIT(31)) && (((regeb4 & 0x03FF0000) >> 16) != 0x142) &&
	    (((regebc & 0x03FF0000) >> 16) != 0x42))
		result |= 0x01;
	अन्यथा
		वापस result;
	अगर (!(regeac & BIT(30)) && (((regec4 & 0x03FF0000) >> 16) != 0x132) &&
	    (((regecc & 0x03FF0000) >> 16) != 0x36))
		result |= 0x02;
	अन्यथा
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path B Rx IQK fail!!\n");
	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 _rtl92d_phy_pathb_iqk_5g_normal(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 regeac, regeb4, regebc, regec4, regecc;
	u8 result = 0;
	u8 i;
	u8 retrycount = 2;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path B IQK!\n");
	/* path-A IQK setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path-A IQK setting!\n");
	rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x18008c1f);
	rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x18008c1f);
	rtl_set_bbreg(hw, 0xe38, MASKDWORD, 0x82110000);
	rtl_set_bbreg(hw, 0xe3c, MASKDWORD, 0x68110000);

	/* path-B IQK setting */
	rtl_set_bbreg(hw, 0xe50, MASKDWORD, 0x18008c2f);
	rtl_set_bbreg(hw, 0xe54, MASKDWORD, 0x18008c2f);
	rtl_set_bbreg(hw, 0xe58, MASKDWORD, 0x82140307);
	rtl_set_bbreg(hw, 0xe5c, MASKDWORD, 0x68160960);

	/* LO calibration setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "LO calibration setting!\n");
	rtl_set_bbreg(hw, 0xe4c, MASKDWORD, 0x00462911);

	/* path-B PA on */
	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, MASKDWORD, 0x0f600700);
	rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE, MASKDWORD, 0x061f0d30);

	क्रम (i = 0; i < retrycount; i++) अणु
		/* One shot, path B LOK & IQK */
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"One shot, path A LOK & IQK!\n");
		rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xfa000000);
		rtl_set_bbreg(hw, 0xe48, MASKDWORD, 0xf8000000);

		/* delay x ms */
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"Delay %d ms for One shot, path B LOK & IQK.\n", 10);
		mdelay(IQK_DELAY_TIME * 10);

		/* Check failed */
		regeac = rtl_get_bbreg(hw, 0xeac, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeac = 0x%x\n", regeac);
		regeb4 = rtl_get_bbreg(hw, 0xeb4, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xeb4 = 0x%x\n", regeb4);
		regebc = rtl_get_bbreg(hw, 0xebc, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xebc = 0x%x\n", regebc);
		regec4 = rtl_get_bbreg(hw, 0xec4, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xec4 = 0x%x\n", regec4);
		regecc = rtl_get_bbreg(hw, 0xecc, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "0xecc = 0x%x\n", regecc);
		अगर (!(regeac & BIT(31)) &&
		    (((regeb4 & 0x03FF0000) >> 16) != 0x142))
			result |= 0x01;
		अन्यथा
			जारी;
		अगर (!(regeac & BIT(30)) &&
		    (((regec4 & 0x03FF0000) >> 16) != 0x132)) अणु
			result |= 0x02;
			अवरोध;
		पूर्ण अन्यथा अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path B Rx IQK fail!!\n");
		पूर्ण
	पूर्ण

	/* path B PA off */
	rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW, MASKDWORD,
		      rtlphy->iqk_bb_backup[0]);
	rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE, MASKDWORD,
		      rtlphy->iqk_bb_backup[2]);
	वापस result;
पूर्ण

अटल व्योम _rtl92d_phy_save_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					    u32 *adda_reg, u32 *adda_backup,
					    u32 regnum)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Save ADDA parameters.\n");
	क्रम (i = 0; i < regnum; i++)
		adda_backup[i] = rtl_get_bbreg(hw, adda_reg[i], MASKDWORD);
पूर्ण

अटल व्योम _rtl92d_phy_save_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
	u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Save MAC parameters.\n");
	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		macbackup[i] = rtl_पढ़ो_byte(rtlpriv, macreg[i]);
	macbackup[i] = rtl_पढ़ो_dword(rtlpriv, macreg[i]);
पूर्ण

अटल व्योम _rtl92d_phy_reload_adda_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					      u32 *adda_reg, u32 *adda_backup,
					      u32 regnum)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"Reload ADDA power saving parameters !\n");
	क्रम (i = 0; i < regnum; i++)
		rtl_set_bbreg(hw, adda_reg[i], MASKDWORD, adda_backup[i]);
पूर्ण

अटल व्योम _rtl92d_phy_reload_mac_रेजिस्टरs(काष्ठा ieee80211_hw *hw,
					     u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Reload MAC parameters !\n");
	क्रम (i = 0; i < (IQK_MAC_REG_NUM - 1); i++)
		rtl_ग_लिखो_byte(rtlpriv, macreg[i], (u8) macbackup[i]);
	rtl_ग_लिखो_byte(rtlpriv, macreg[i], macbackup[i]);
पूर्ण

अटल व्योम _rtl92d_phy_path_adda_on(काष्ठा ieee80211_hw *hw,
		u32 *adda_reg, bool patha_on, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 pathon;
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "ADDA ON.\n");
	pathon = patha_on ? 0x04db25a4 : 0x0b1b25a4;
	अगर (patha_on)
		pathon = rtlpriv->rtlhal.पूर्णांकerfaceindex == 0 ?
		    0x04db25a4 : 0x0b1b25a4;
	क्रम (i = 0; i < IQK_ADDA_REG_NUM; i++)
		rtl_set_bbreg(hw, adda_reg[i], MASKDWORD, pathon);
पूर्ण

अटल व्योम _rtl92d_phy_mac_setting_calibration(काष्ठा ieee80211_hw *hw,
						u32 *macreg, u32 *macbackup)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 i;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "MAC settings for Calibration.\n");
	rtl_ग_लिखो_byte(rtlpriv, macreg[0], 0x3F);

	क्रम (i = 1; i < (IQK_MAC_REG_NUM - 1); i++)
		rtl_ग_लिखो_byte(rtlpriv, macreg[i], (u8)(macbackup[i] &
			       (~BIT(3))));
	rtl_ग_लिखो_byte(rtlpriv, macreg[i], (u8) (macbackup[i] & (~BIT(5))));
पूर्ण

अटल व्योम _rtl92d_phy_patha_standby(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path-A standby mode!\n");

	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x0);
	rtl_set_bbreg(hw, RFPGA0_XA_LSSIPARAMETER, MASKDWORD, 0x00010000);
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
पूर्ण

अटल व्योम _rtl92d_phy_pimode_चयन(काष्ठा ieee80211_hw *hw, bool pi_mode)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 mode;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"BB Switch to %s mode!\n", pi_mode ? "PI" : "SI");
	mode = pi_mode ? 0x01000100 : 0x01000000;
	rtl_set_bbreg(hw, 0x820, MASKDWORD, mode);
	rtl_set_bbreg(hw, 0x828, MASKDWORD, mode);
पूर्ण

अटल व्योम _rtl92d_phy_iq_calibrate(काष्ठा ieee80211_hw *hw, दीर्घ result[][8],
				     u8 t, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 i;
	u8 patha_ok, pathb_ok;
	अटल u32 adda_reg[IQK_ADDA_REG_NUM] = अणु
		RFPGA0_XCD_SWITCHCONTROL, 0xe6c, 0xe70, 0xe74,
		0xe78, 0xe7c, 0xe80, 0xe84,
		0xe88, 0xe8c, 0xed0, 0xed4,
		0xed8, 0xedc, 0xee0, 0xeec
	पूर्ण;
	अटल u32 iqk_mac_reg[IQK_MAC_REG_NUM] = अणु
		0x522, 0x550, 0x551, 0x040
	पूर्ण;
	अटल u32 iqk_bb_reg[IQK_BB_REG_NUM] = अणु
		RFPGA0_XAB_RFINTERFACESW, RFPGA0_XA_RFINTERFACEOE,
		RFPGA0_XB_RFINTERFACEOE, ROFDM0_TRMUXPAR,
		RFPGA0_XCD_RFINTERFACESW, ROFDM0_TRXPATHENABLE,
		RFPGA0_RFMOD, RFPGA0_ANALOGPARAMETER4,
		ROFDM0_XAAGCCORE1, ROFDM0_XBAGCCORE1
	पूर्ण;
	स्थिर u32 retrycount = 2;
	u32 bbvalue;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "IQK for 2.4G :Start!!!\n");
	अगर (t == 0) अणु
		bbvalue = rtl_get_bbreg(hw, RFPGA0_RFMOD, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "==>0x%08x\n", bbvalue);
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "IQ Calibration for %s\n",
			is2t ? "2T2R" : "1T1R");

		/*  Save ADDA parameters, turn Path A ADDA on */
		_rtl92d_phy_save_adda_रेजिस्टरs(hw, adda_reg,
			rtlphy->adda_backup, IQK_ADDA_REG_NUM);
		_rtl92d_phy_save_mac_रेजिस्टरs(hw, iqk_mac_reg,
			rtlphy->iqk_mac_backup);
		_rtl92d_phy_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
			rtlphy->iqk_bb_backup, IQK_BB_REG_NUM);
	पूर्ण
	_rtl92d_phy_path_adda_on(hw, adda_reg, true, is2t);
	अगर (t == 0)
		rtlphy->rfpi_enable = (u8) rtl_get_bbreg(hw,
				RFPGA0_XA_HSSIPARAMETER1, BIT(8));

	/*  Switch BB to PI mode to करो IQ Calibration. */
	अगर (!rtlphy->rfpi_enable)
		_rtl92d_phy_pimode_चयन(hw, true);

	rtl_set_bbreg(hw, RFPGA0_RFMOD, BIT(24), 0x00);
	rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKDWORD, 0x03a05600);
	rtl_set_bbreg(hw, ROFDM0_TRMUXPAR, MASKDWORD, 0x000800e4);
	rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW, MASKDWORD, 0x22204000);
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0xf00000, 0x0f);
	अगर (is2t) अणु
		rtl_set_bbreg(hw, RFPGA0_XA_LSSIPARAMETER, MASKDWORD,
			      0x00010000);
		rtl_set_bbreg(hw, RFPGA0_XB_LSSIPARAMETER, MASKDWORD,
			      0x00010000);
	पूर्ण
	/* MAC settings */
	_rtl92d_phy_mac_setting_calibration(hw, iqk_mac_reg,
					    rtlphy->iqk_mac_backup);
	/* Page B init */
	rtl_set_bbreg(hw, 0xb68, MASKDWORD, 0x0f600000);
	अगर (is2t)
		rtl_set_bbreg(hw, 0xb6c, MASKDWORD, 0x0f600000);
	/* IQ calibration setting */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "IQK setting!\n");
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
	rtl_set_bbreg(hw, 0xe40, MASKDWORD, 0x01007c00);
	rtl_set_bbreg(hw, 0xe44, MASKDWORD, 0x01004800);
	क्रम (i = 0; i < retrycount; i++) अणु
		patha_ok = _rtl92d_phy_patha_iqk(hw, is2t);
		अगर (patha_ok == 0x03) अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path A IQK Success!!\n");
			result[t][0] = (rtl_get_bbreg(hw, 0xe94, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][1] = (rtl_get_bbreg(hw, 0xe9c, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][2] = (rtl_get_bbreg(hw, 0xea4, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][3] = (rtl_get_bbreg(hw, 0xeac, MASKDWORD) &
					0x3FF0000) >> 16;
			अवरोध;
		पूर्ण अन्यथा अगर (i == (retrycount - 1) && patha_ok == 0x01) अणु
			/* Tx IQK OK */
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path A IQK Only  Tx Success!!\n");

			result[t][0] = (rtl_get_bbreg(hw, 0xe94, MASKDWORD) &
					0x3FF0000) >> 16;
			result[t][1] = (rtl_get_bbreg(hw, 0xe9c, MASKDWORD) &
					0x3FF0000) >> 16;
		पूर्ण
	पूर्ण
	अगर (0x00 == patha_ok)
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path A IQK failed!!\n");
	अगर (is2t) अणु
		_rtl92d_phy_patha_standby(hw);
		/* Turn Path B ADDA on */
		_rtl92d_phy_path_adda_on(hw, adda_reg, false, is2t);
		क्रम (i = 0; i < retrycount; i++) अणु
			pathb_ok = _rtl92d_phy_pathb_iqk(hw);
			अगर (pathb_ok == 0x03) अणु
				RTPRINT(rtlpriv, FINIT, INIT_IQK,
					"Path B IQK Success!!\n");
				result[t][4] = (rtl_get_bbreg(hw, 0xeb4,
					       MASKDWORD) & 0x3FF0000) >> 16;
				result[t][5] = (rtl_get_bbreg(hw, 0xebc,
					       MASKDWORD) & 0x3FF0000) >> 16;
				result[t][6] = (rtl_get_bbreg(hw, 0xec4,
					       MASKDWORD) & 0x3FF0000) >> 16;
				result[t][7] = (rtl_get_bbreg(hw, 0xecc,
					       MASKDWORD) & 0x3FF0000) >> 16;
				अवरोध;
			पूर्ण अन्यथा अगर (i == (retrycount - 1) && pathb_ok == 0x01) अणु
				/* Tx IQK OK */
				RTPRINT(rtlpriv, FINIT, INIT_IQK,
					"Path B Only Tx IQK Success!!\n");
				result[t][4] = (rtl_get_bbreg(hw, 0xeb4,
					       MASKDWORD) & 0x3FF0000) >> 16;
				result[t][5] = (rtl_get_bbreg(hw, 0xebc,
					       MASKDWORD) & 0x3FF0000) >> 16;
			पूर्ण
		पूर्ण
		अगर (0x00 == pathb_ok)
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path B IQK failed!!\n");
	पूर्ण

	/* Back to BB mode, load original value */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"IQK:Back to BB mode, load original value!\n");

	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0);
	अगर (t != 0) अणु
		/* Switch back BB to SI mode after finish IQ Calibration. */
		अगर (!rtlphy->rfpi_enable)
			_rtl92d_phy_pimode_चयन(hw, false);
		/* Reload ADDA घातer saving parameters */
		_rtl92d_phy_reload_adda_रेजिस्टरs(hw, adda_reg,
				rtlphy->adda_backup, IQK_ADDA_REG_NUM);
		/* Reload MAC parameters */
		_rtl92d_phy_reload_mac_रेजिस्टरs(hw, iqk_mac_reg,
					rtlphy->iqk_mac_backup);
		अगर (is2t)
			_rtl92d_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
							  rtlphy->iqk_bb_backup,
							  IQK_BB_REG_NUM);
		अन्यथा
			_rtl92d_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
							  rtlphy->iqk_bb_backup,
							  IQK_BB_REG_NUM - 1);
		/* load 0xe30 IQC शेष value */
		rtl_set_bbreg(hw, 0xe30, MASKDWORD, 0x01008c00);
		rtl_set_bbreg(hw, 0xe34, MASKDWORD, 0x01008c00);
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "<==\n");
पूर्ण

अटल व्योम _rtl92d_phy_iq_calibrate_5g_normal(काष्ठा ieee80211_hw *hw,
					       दीर्घ result[][8], u8 t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u8 patha_ok, pathb_ok;
	अटल u32 adda_reg[IQK_ADDA_REG_NUM] = अणु
		RFPGA0_XCD_SWITCHCONTROL, 0xe6c, 0xe70, 0xe74,
		0xe78, 0xe7c, 0xe80, 0xe84,
		0xe88, 0xe8c, 0xed0, 0xed4,
		0xed8, 0xedc, 0xee0, 0xeec
	पूर्ण;
	अटल u32 iqk_mac_reg[IQK_MAC_REG_NUM] = अणु
		0x522, 0x550, 0x551, 0x040
	पूर्ण;
	अटल u32 iqk_bb_reg[IQK_BB_REG_NUM] = अणु
		RFPGA0_XAB_RFINTERFACESW, RFPGA0_XA_RFINTERFACEOE,
		RFPGA0_XB_RFINTERFACEOE, ROFDM0_TRMUXPAR,
		RFPGA0_XCD_RFINTERFACESW, ROFDM0_TRXPATHENABLE,
		RFPGA0_RFMOD, RFPGA0_ANALOGPARAMETER4,
		ROFDM0_XAAGCCORE1, ROFDM0_XBAGCCORE1
	पूर्ण;
	u32 bbvalue;
	bool is2t = IS_92D_SINGLEPHY(rtlhal->version);

	/* Note: IQ calibration must be perक्रमmed after loading
	 * PHY_REG.txt , and radio_a, radio_b.txt */

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "IQK for 5G NORMAL:Start!!!\n");
	mdelay(IQK_DELAY_TIME * 20);
	अगर (t == 0) अणु
		bbvalue = rtl_get_bbreg(hw, RFPGA0_RFMOD, MASKDWORD);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "==>0x%08x\n", bbvalue);
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "IQ Calibration for %s\n",
			is2t ? "2T2R" : "1T1R");
		/* Save ADDA parameters, turn Path A ADDA on */
		_rtl92d_phy_save_adda_रेजिस्टरs(hw, adda_reg,
						rtlphy->adda_backup,
						IQK_ADDA_REG_NUM);
		_rtl92d_phy_save_mac_रेजिस्टरs(hw, iqk_mac_reg,
					       rtlphy->iqk_mac_backup);
		अगर (is2t)
			_rtl92d_phy_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
							rtlphy->iqk_bb_backup,
							IQK_BB_REG_NUM);
		अन्यथा
			_rtl92d_phy_save_adda_रेजिस्टरs(hw, iqk_bb_reg,
							rtlphy->iqk_bb_backup,
							IQK_BB_REG_NUM - 1);
	पूर्ण
	_rtl92d_phy_path_adda_on(hw, adda_reg, true, is2t);
	/* MAC settings */
	_rtl92d_phy_mac_setting_calibration(hw, iqk_mac_reg,
			rtlphy->iqk_mac_backup);
	अगर (t == 0)
		rtlphy->rfpi_enable = (u8) rtl_get_bbreg(hw,
			RFPGA0_XA_HSSIPARAMETER1, BIT(8));
	/*  Switch BB to PI mode to करो IQ Calibration. */
	अगर (!rtlphy->rfpi_enable)
		_rtl92d_phy_pimode_चयन(hw, true);
	rtl_set_bbreg(hw, RFPGA0_RFMOD, BIT(24), 0x00);
	rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKDWORD, 0x03a05600);
	rtl_set_bbreg(hw, ROFDM0_TRMUXPAR, MASKDWORD, 0x000800e4);
	rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW, MASKDWORD, 0x22208000);
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0xf00000, 0x0f);

	/* Page B init */
	rtl_set_bbreg(hw, 0xb68, MASKDWORD, 0x0f600000);
	अगर (is2t)
		rtl_set_bbreg(hw, 0xb6c, MASKDWORD, 0x0f600000);
	/* IQ calibration setting  */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "IQK setting!\n");
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0x80800000);
	rtl_set_bbreg(hw, 0xe40, MASKDWORD, 0x10007c00);
	rtl_set_bbreg(hw, 0xe44, MASKDWORD, 0x01004800);
	patha_ok = _rtl92d_phy_patha_iqk_5g_normal(hw, is2t);
	अगर (patha_ok == 0x03) अणु
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path A IQK Success!!\n");
		result[t][0] = (rtl_get_bbreg(hw, 0xe94, MASKDWORD) &
				0x3FF0000) >> 16;
		result[t][1] = (rtl_get_bbreg(hw, 0xe9c, MASKDWORD) &
				0x3FF0000) >> 16;
		result[t][2] = (rtl_get_bbreg(hw, 0xea4, MASKDWORD) &
				0x3FF0000) >> 16;
		result[t][3] = (rtl_get_bbreg(hw, 0xeac, MASKDWORD) &
				0x3FF0000) >> 16;
	पूर्ण अन्यथा अगर (patha_ok == 0x01) अणु	/* Tx IQK OK */
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"Path A IQK Only  Tx Success!!\n");

		result[t][0] = (rtl_get_bbreg(hw, 0xe94, MASKDWORD) &
				0x3FF0000) >> 16;
		result[t][1] = (rtl_get_bbreg(hw, 0xe9c, MASKDWORD) &
				0x3FF0000) >> 16;
	पूर्ण अन्यथा अणु
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "Path A IQK Fail!!\n");
	पूर्ण
	अगर (is2t) अणु
		/* _rtl92d_phy_patha_standby(hw); */
		/* Turn Path B ADDA on  */
		_rtl92d_phy_path_adda_on(hw, adda_reg, false, is2t);
		pathb_ok = _rtl92d_phy_pathb_iqk_5g_normal(hw);
		अगर (pathb_ok == 0x03) अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path B IQK Success!!\n");
			result[t][4] = (rtl_get_bbreg(hw, 0xeb4, MASKDWORD) &
			     0x3FF0000) >> 16;
			result[t][5] = (rtl_get_bbreg(hw, 0xebc, MASKDWORD) &
			     0x3FF0000) >> 16;
			result[t][6] = (rtl_get_bbreg(hw, 0xec4, MASKDWORD) &
			     0x3FF0000) >> 16;
			result[t][7] = (rtl_get_bbreg(hw, 0xecc, MASKDWORD) &
			     0x3FF0000) >> 16;
		पूर्ण अन्यथा अगर (pathb_ok == 0x01) अणु /* Tx IQK OK */
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path B Only Tx IQK Success!!\n");
			result[t][4] = (rtl_get_bbreg(hw, 0xeb4, MASKDWORD) &
			     0x3FF0000) >> 16;
			result[t][5] = (rtl_get_bbreg(hw, 0xebc, MASKDWORD) &
			     0x3FF0000) >> 16;
		पूर्ण अन्यथा अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"Path B IQK failed!!\n");
		पूर्ण
	पूर्ण

	/* Back to BB mode, load original value */
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"IQK:Back to BB mode, load original value!\n");
	rtl_set_bbreg(hw, 0xe28, MASKDWORD, 0);
	अगर (t != 0) अणु
		अगर (is2t)
			_rtl92d_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
							  rtlphy->iqk_bb_backup,
							  IQK_BB_REG_NUM);
		अन्यथा
			_rtl92d_phy_reload_adda_रेजिस्टरs(hw, iqk_bb_reg,
							  rtlphy->iqk_bb_backup,
							  IQK_BB_REG_NUM - 1);
		/* Reload MAC parameters */
		_rtl92d_phy_reload_mac_रेजिस्टरs(hw, iqk_mac_reg,
				rtlphy->iqk_mac_backup);
		/*  Switch back BB to SI mode after finish IQ Calibration. */
		अगर (!rtlphy->rfpi_enable)
			_rtl92d_phy_pimode_चयन(hw, false);
		/* Reload ADDA घातer saving parameters */
		_rtl92d_phy_reload_adda_रेजिस्टरs(hw, adda_reg,
						  rtlphy->adda_backup,
						  IQK_ADDA_REG_NUM);
	पूर्ण
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "<==\n");
पूर्ण

अटल bool _rtl92d_phy_simularity_compare(काष्ठा ieee80211_hw *hw,
	दीर्घ result[][8], u8 c1, u8 c2)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 i, j, dअगरf, sim_biपंचांगap, bound;
	u8 final_candidate[2] = अणु0xFF, 0xFFपूर्ण;	/* क्रम path A and path B */
	bool bresult = true;
	bool is2t = IS_92D_SINGLEPHY(rtlhal->version);

	अगर (is2t)
		bound = 8;
	अन्यथा
		bound = 4;
	sim_biपंचांगap = 0;
	क्रम (i = 0; i < bound; i++) अणु
		dअगरf = (result[c1][i] > result[c2][i]) ? (result[c1][i] -
		       result[c2][i]) : (result[c2][i] - result[c1][i]);
		अगर (dअगरf > MAX_TOLERANCE_92D) अणु
			अगर ((i == 2 || i == 6) && !sim_biपंचांगap) अणु
				अगर (result[c1][i] + result[c1][i + 1] == 0)
					final_candidate[(i / 4)] = c2;
				अन्यथा अगर (result[c2][i] + result[c2][i + 1] == 0)
					final_candidate[(i / 4)] = c1;
				अन्यथा
					sim_biपंचांगap = sim_biपंचांगap | (1 << i);
			पूर्ण अन्यथा अणु
				sim_biपंचांगap = sim_biपंचांगap | (1 << i);
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (sim_biपंचांगap == 0) अणु
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
	अगर (!(sim_biपंचांगap & 0x0F)) अणु /* path A OK */
		क्रम (i = 0; i < 4; i++)
			result[3][i] = result[c1][i];
	पूर्ण अन्यथा अगर (!(sim_biपंचांगap & 0x03)) अणु /* path A, Tx OK */
		क्रम (i = 0; i < 2; i++)
			result[3][i] = result[c1][i];
	पूर्ण
	अगर (!(sim_biपंचांगap & 0xF0) && is2t) अणु /* path B OK */
		क्रम (i = 4; i < 8; i++)
			result[3][i] = result[c1][i];
	पूर्ण अन्यथा अगर (!(sim_biपंचांगap & 0x30)) अणु /* path B, Tx OK */
		क्रम (i = 4; i < 6; i++)
			result[3][i] = result[c1][i];
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम _rtl92d_phy_patha_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
					      bool iqk_ok, दीर्घ result[][8],
					      u8 final_candidate, bool txonly)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 oldval_0, val_x, tx0_a, reg;
	दीर्घ val_y, tx0_c;
	bool is2t = IS_92D_SINGLEPHY(rtlhal->version) ||
	    rtlhal->macphymode == DUALMAC_DUALPHY;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"Path A IQ Calibration %s !\n", iqk_ok ? "Success" : "Failed");
	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (iqk_ok) अणु
		oldval_0 = (rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
			MASKDWORD) >> 22) & 0x3FF;	/* OFDM0_D */
		val_x = result[final_candidate][0];
		अगर ((val_x & 0x00000200) != 0)
			val_x = val_x | 0xFFFFFC00;
		tx0_a = (val_x * oldval_0) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"X = 0x%x, tx0_a = 0x%x, oldval_0 0x%x\n",
			val_x, tx0_a, oldval_0);
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x3FF, tx0_a);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(24),
			      ((val_x * oldval_0 >> 7) & 0x1));
		val_y = result[final_candidate][1];
		अगर ((val_y & 0x00000200) != 0)
			val_y = val_y | 0xFFFFFC00;
		/* path B IQK result + 3 */
		अगर (rtlhal->पूर्णांकerfaceindex == 1 &&
			rtlhal->current_bandtype == BAND_ON_5G)
			val_y += 3;
		tx0_c = (val_y * oldval_0) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"Y = 0x%lx, tx0_c = 0x%lx\n",
			val_y, tx0_c);
		rtl_set_bbreg(hw, ROFDM0_XCTXAFE, 0xF0000000,
			      ((tx0_c & 0x3C0) >> 6));
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, 0x003F0000,
			      (tx0_c & 0x3F));
		अगर (is2t)
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(26),
				      ((val_y * oldval_0 >> 7) & 0x1));
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "0xC80 = 0x%x\n",
			rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
				      MASKDWORD));
		अगर (txonly) अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,  "only Tx OK\n");
			वापस;
		पूर्ण
		reg = result[final_candidate][2];
		rtl_set_bbreg(hw, ROFDM0_XARXIQIMBALANCE, 0x3FF, reg);
		reg = result[final_candidate][3] & 0x3F;
		rtl_set_bbreg(hw, ROFDM0_XARXIQIMBALANCE, 0xFC00, reg);
		reg = (result[final_candidate][3] >> 6) & 0xF;
		rtl_set_bbreg(hw, 0xca0, 0xF0000000, reg);
	पूर्ण
पूर्ण

अटल व्योम _rtl92d_phy_pathb_fill_iqk_matrix(काष्ठा ieee80211_hw *hw,
	bool iqk_ok, दीर्घ result[][8], u8 final_candidate, bool txonly)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 oldval_1, val_x, tx1_a, reg;
	दीर्घ val_y, tx1_c;

	RTPRINT(rtlpriv, FINIT, INIT_IQK, "Path B IQ Calibration %s !\n",
		iqk_ok ? "Success" : "Failed");
	अगर (final_candidate == 0xFF) अणु
		वापस;
	पूर्ण अन्यथा अगर (iqk_ok) अणु
		oldval_1 = (rtl_get_bbreg(hw, ROFDM0_XBTXIQIMBALANCE,
					  MASKDWORD) >> 22) & 0x3FF;
		val_x = result[final_candidate][4];
		अगर ((val_x & 0x00000200) != 0)
			val_x = val_x | 0xFFFFFC00;
		tx1_a = (val_x * oldval_1) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "X = 0x%x, tx1_a = 0x%x\n",
			val_x, tx1_a);
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, 0x3FF, tx1_a);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(28),
			      ((val_x * oldval_1 >> 7) & 0x1));
		val_y = result[final_candidate][5];
		अगर ((val_y & 0x00000200) != 0)
			val_y = val_y | 0xFFFFFC00;
		अगर (rtlhal->current_bandtype == BAND_ON_5G)
			val_y += 3;
		tx1_c = (val_y * oldval_1) >> 8;
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "Y = 0x%lx, tx1_c = 0x%lx\n",
			val_y, tx1_c);
		rtl_set_bbreg(hw, ROFDM0_XDTXAFE, 0xF0000000,
			      ((tx1_c & 0x3C0) >> 6));
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, 0x003F0000,
			      (tx1_c & 0x3F));
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(30),
			      ((val_y * oldval_1 >> 7) & 0x1));
		अगर (txonly)
			वापस;
		reg = result[final_candidate][6];
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0x3FF, reg);
		reg = result[final_candidate][7] & 0x3F;
		rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, 0xFC00, reg);
		reg = (result[final_candidate][7] >> 6) & 0xF;
		rtl_set_bbreg(hw, ROFDM0_AGCRSSITABLE, 0x0000F000, reg);
	पूर्ण
पूर्ण

व्योम rtl92d_phy_iq_calibrate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	दीर्घ result[4][8];
	u8 i, final_candidate, indexक्रमchannel;
	bool patha_ok, pathb_ok;
	दीर्घ rege94, rege9c, regea4, regeac, regeb4;
	दीर्घ regebc, regec4, regecc, regपंचांगp = 0;
	bool is12simular, is13simular, is23simular;
	अचिन्हित दीर्घ flag = 0;

	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"IQK:Start!!!channel %d\n", rtlphy->current_channel);
	क्रम (i = 0; i < 8; i++) अणु
		result[0][i] = 0;
		result[1][i] = 0;
		result[2][i] = 0;
		result[3][i] = 0;
	पूर्ण
	final_candidate = 0xff;
	patha_ok = false;
	pathb_ok = false;
	is12simular = false;
	is23simular = false;
	is13simular = false;
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"IQK !!!currentband %d\n", rtlhal->current_bandtype);
	rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
	क्रम (i = 0; i < 3; i++) अणु
		अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
			_rtl92d_phy_iq_calibrate_5g_normal(hw, result, i);
		पूर्ण अन्यथा अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			अगर (IS_92D_SINGLEPHY(rtlhal->version))
				_rtl92d_phy_iq_calibrate(hw, result, i, true);
			अन्यथा
				_rtl92d_phy_iq_calibrate(hw, result, i, false);
		पूर्ण
		अगर (i == 1) अणु
			is12simular = _rtl92d_phy_simularity_compare(hw, result,
								     0, 1);
			अगर (is12simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == 2) अणु
			is13simular = _rtl92d_phy_simularity_compare(hw, result,
								     0, 2);
			अगर (is13simular) अणु
				final_candidate = 0;
				अवरोध;
			पूर्ण
			is23simular = _rtl92d_phy_simularity_compare(hw, result,
								     1, 2);
			अगर (is23simular) अणु
				final_candidate = 1;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < 8; i++)
					regपंचांगp += result[3][i];

				अगर (regपंचांगp != 0)
					final_candidate = 3;
				अन्यथा
					final_candidate = 0xFF;
			पूर्ण
		पूर्ण
	पूर्ण
	rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
	क्रम (i = 0; i < 4; i++) अणु
		rege94 = result[i][0];
		rege9c = result[i][1];
		regea4 = result[i][2];
		regeac = result[i][3];
		regeb4 = result[i][4];
		regebc = result[i][5];
		regec4 = result[i][6];
		regecc = result[i][7];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"IQK: rege94=%lx rege9c=%lx regea4=%lx regeac=%lx regeb4=%lx regebc=%lx regec4=%lx regecc=%lx\n",
			rege94, rege9c, regea4, regeac, regeb4, regebc, regec4,
			regecc);
	पूर्ण
	अगर (final_candidate != 0xff) अणु
		rtlphy->reg_e94 = rege94 = result[final_candidate][0];
		rtlphy->reg_e9c = rege9c = result[final_candidate][1];
		regea4 = result[final_candidate][2];
		regeac = result[final_candidate][3];
		rtlphy->reg_eb4 = regeb4 = result[final_candidate][4];
		rtlphy->reg_ebc = regebc = result[final_candidate][5];
		regec4 = result[final_candidate][6];
		regecc = result[final_candidate][7];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"IQK: final_candidate is %x\n", final_candidate);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"IQK: rege94=%lx rege9c=%lx regea4=%lx regeac=%lx regeb4=%lx regebc=%lx regec4=%lx regecc=%lx\n",
			rege94, rege9c, regea4, regeac, regeb4, regebc, regec4,
			regecc);
		patha_ok = pathb_ok = true;
	पूर्ण अन्यथा अणु
		rtlphy->reg_e94 = rtlphy->reg_eb4 = 0x100; /* X शेष value */
		rtlphy->reg_e9c = rtlphy->reg_ebc = 0x0;   /* Y शेष value */
	पूर्ण
	अगर ((rege94 != 0) /*&&(regea4 != 0) */)
		_rtl92d_phy_patha_fill_iqk_matrix(hw, patha_ok, result,
				final_candidate, (regea4 == 0));
	अगर (IS_92D_SINGLEPHY(rtlhal->version)) अणु
		अगर ((regeb4 != 0) /*&&(regec4 != 0) */)
			_rtl92d_phy_pathb_fill_iqk_matrix(hw, pathb_ok, result,
						final_candidate, (regec4 == 0));
	पूर्ण
	अगर (final_candidate != 0xFF) अणु
		indexक्रमchannel = rtl92d_get_rightchnlplace_क्रम_iqk(
				  rtlphy->current_channel);

		क्रम (i = 0; i < IQK_MATRIX_REG_NUM; i++)
			rtlphy->iqk_matrix[indexक्रमchannel].
				value[0][i] = result[final_candidate][i];
		rtlphy->iqk_matrix[indexक्रमchannel].iqk_करोne =
			true;

		rtl_dbg(rtlpriv, COMP_SCAN | COMP_MLME, DBG_LOUD,
			"IQK OK indexforchannel %d\n", indexक्रमchannel);
	पूर्ण
पूर्ण

व्योम rtl92d_phy_reload_iqk_setting(काष्ठा ieee80211_hw *hw, u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u8 indexक्रमchannel;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "channel %d\n", channel);
	/*------Do IQK क्रम normal chip and test chip 5G band------- */
	indexक्रमchannel = rtl92d_get_rightchnlplace_क्रम_iqk(channel);
	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "indexforchannel %d done %d\n",
		indexक्रमchannel,
		 rtlphy->iqk_matrix[indexक्रमchannel].iqk_करोne);
	अगर (0 && !rtlphy->iqk_matrix[indexक्रमchannel].iqk_करोne &&
		rtlphy->need_iqk) अणु
		/* Re Do IQK. */
		rtl_dbg(rtlpriv, COMP_SCAN | COMP_INIT, DBG_LOUD,
			"Do IQK Matrix reg for channel:%d....\n", channel);
		rtl92d_phy_iq_calibrate(hw);
	पूर्ण अन्यथा अणु
		/* Just load the value. */
		/* 2G band just load once. */
		अगर (((!rtlhal->load_imअक्रमiqk_setting_क्रम2g) &&
		    indexक्रमchannel == 0) || indexक्रमchannel > 0) अणु
			rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
				"Just Read IQK Matrix reg for channel:%d....\n",
				channel);
			अगर ((rtlphy->iqk_matrix[indexक्रमchannel].
			     value[0] != शून्य)
				/*&&(regea4 != 0) */)
				_rtl92d_phy_patha_fill_iqk_matrix(hw, true,
					rtlphy->iqk_matrix[
					indexक्रमchannel].value,	0,
					(rtlphy->iqk_matrix[
					indexक्रमchannel].value[0][2] == 0));
			अगर (IS_92D_SINGLEPHY(rtlhal->version)) अणु
				अगर ((rtlphy->iqk_matrix[
					indexक्रमchannel].value[0][4] != 0)
					/*&&(regec4 != 0) */)
					_rtl92d_phy_pathb_fill_iqk_matrix(hw,
						true,
						rtlphy->iqk_matrix[
						indexक्रमchannel].value, 0,
						(rtlphy->iqk_matrix[
						indexक्रमchannel].value[0][6]
						== 0));
			पूर्ण
		पूर्ण
	पूर्ण
	rtlphy->need_iqk = false;
	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "<====\n");
पूर्ण

अटल u32 _rtl92d_phy_get_असल(u32 val1, u32 val2)
अणु
	u32 ret;

	अगर (val1 >= val2)
		ret = val1 - val2;
	अन्यथा
		ret = val2 - val1;
	वापस ret;
पूर्ण

अटल bool _rtl92d_is_legal_5g_channel(काष्ठा ieee80211_hw *hw, u8 channel)
अणु

	पूर्णांक i;

	क्रम (i = 0; i < माप(channel5g); i++)
		अगर (channel == channel5g[i])
			वापस true;
	वापस false;
पूर्ण

अटल व्योम _rtl92d_phy_calc_curvindex(काष्ठा ieee80211_hw *hw,
				       u32 *tarअ_लोhnl, u32 * curvecount_val,
				       bool is5g, u32 *curveindex)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 smallest_असल_val = 0xffffffff, u4पंचांगp;
	u8 i, j;
	u8 chnl_num = is5g ? TARGET_CHNL_NUM_5G : TARGET_CHNL_NUM_2G;

	क्रम (i = 0; i < chnl_num; i++) अणु
		अगर (is5g && !_rtl92d_is_legal_5g_channel(hw, i + 1))
			जारी;
		curveindex[i] = 0;
		क्रम (j = 0; j < (CV_CURVE_CNT * 2); j++) अणु
			u4पंचांगp = _rtl92d_phy_get_असल(tarअ_लोhnl[i],
				curvecount_val[j]);

			अगर (u4पंचांगp < smallest_असल_val) अणु
				curveindex[i] = j;
				smallest_असल_val = u4पंचांगp;
			पूर्ण
		पूर्ण
		smallest_असल_val = 0xffffffff;
		RTPRINT(rtlpriv, FINIT, INIT_IQK, "curveindex[%d] = %x\n",
			i, curveindex[i]);
	पूर्ण
पूर्ण

अटल व्योम _rtl92d_phy_reload_lck_setting(काष्ठा ieee80211_hw *hw,
		u8 channel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 erfpath = rtlpriv->rtlhal.current_bandtype ==
		BAND_ON_5G ? RF90_PATH_A :
		IS_92D_SINGLEPHY(rtlpriv->rtlhal.version) ?
		RF90_PATH_B : RF90_PATH_A;
	u32 u4पंचांगp = 0, u4regvalue = 0;
	bool bneed_घातerकरोwn_radio = false;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "path %d\n", erfpath);
	RTPRINT(rtlpriv, FINIT, INIT_IQK, "band type = %d\n",
		rtlpriv->rtlhal.current_bandtype);
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "channel = %d\n", channel);
	अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_5G) अणु/* Path-A क्रम 5G */
		u4पंचांगp = curveindex_5g[channel-1];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"ver 1 set RF-A, 5G,	0x28 = 0x%x !!\n", u4पंचांगp);
		अगर (rtlpriv->rtlhal.macphymode == DUALMAC_DUALPHY &&
			rtlpriv->rtlhal.पूर्णांकerfaceindex == 1) अणु
			bneed_घातerकरोwn_radio =
				rtl92d_phy_enable_anotherphy(hw, false);
			rtlpriv->rtlhal.during_mac1init_radioa = true;
			/* asume no this हाल */
			अगर (bneed_घातerकरोwn_radio)
				_rtl92d_phy_enable_rf_env(hw, erfpath,
							  &u4regvalue);
		पूर्ण
		rtl_set_rfreg(hw, erfpath, RF_SYN_G4, 0x3f800, u4पंचांगp);
		अगर (bneed_घातerकरोwn_radio)
			_rtl92d_phy_restore_rf_env(hw, erfpath, &u4regvalue);
		अगर (rtlpriv->rtlhal.during_mac1init_radioa)
			rtl92d_phy_घातerकरोwn_anotherphy(hw, false);
	पूर्ण अन्यथा अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G) अणु
		u4पंचांगp = curveindex_2g[channel-1];
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"ver 3 set RF-B, 2G, 0x28 = 0x%x !!\n", u4पंचांगp);
		अगर (rtlpriv->rtlhal.macphymode == DUALMAC_DUALPHY &&
			rtlpriv->rtlhal.पूर्णांकerfaceindex == 0) अणु
			bneed_घातerकरोwn_radio =
				rtl92d_phy_enable_anotherphy(hw, true);
			rtlpriv->rtlhal.during_mac0init_radiob = true;
			अगर (bneed_घातerकरोwn_radio)
				_rtl92d_phy_enable_rf_env(hw, erfpath,
							  &u4regvalue);
		पूर्ण
		rtl_set_rfreg(hw, erfpath, RF_SYN_G4, 0x3f800, u4पंचांगp);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"ver 3 set RF-B, 2G, 0x28 = 0x%x !!\n",
			rtl_get_rfreg(hw,  erfpath, RF_SYN_G4, 0x3f800));
		अगर (bneed_घातerकरोwn_radio)
			_rtl92d_phy_restore_rf_env(hw, erfpath, &u4regvalue);
		अगर (rtlpriv->rtlhal.during_mac0init_radiob)
			rtl92d_phy_घातerकरोwn_anotherphy(hw, true);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_CMD, DBG_LOUD, "<====\n");
पूर्ण

अटल व्योम _rtl92d_phy_lc_calibrate_sw(काष्ठा ieee80211_hw *hw, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 पंचांगpreg, index, rf_mode[2];
	u8 path = is2t ? 2 : 1;
	u8 i;
	u32 u4पंचांगp, offset;
	u32 curvecount_val[CV_CURVE_CNT * 2] = अणु0पूर्ण;
	u16 समयout = 800, समयcount = 0;

	/* Check continuous TX and Packet TX */
	पंचांगpreg = rtl_पढ़ो_byte(rtlpriv, 0xd03);
	/* अगर Deal with contisuous TX हाल, disable all continuous TX */
	/* अगर Deal with Packet TX हाल, block all queues */
	अगर ((पंचांगpreg & 0x70) != 0)
		rtl_ग_लिखो_byte(rtlpriv, 0xd03, पंचांगpreg & 0x8F);
	अन्यथा
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0xF00000, 0x0F);
	क्रम (index = 0; index < path; index++) अणु
		/* 1. Read original RF mode */
		offset = index == 0 ? ROFDM0_XAAGCCORE1 : ROFDM0_XBAGCCORE1;
		rf_mode[index] = rtl_पढ़ो_byte(rtlpriv, offset);
		/* 2. Set RF mode = standby mode */
		rtl_set_rfreg(hw, (क्रमागत radio_path)index, RF_AC,
			      RFREG_OFFSET_MASK, 0x010000);
		अगर (rtlpci->init_पढ़ोy) अणु
			/* चयन CV-curve control by LC-calibration */
			rtl_set_rfreg(hw, (क्रमागत radio_path)index, RF_SYN_G7,
				      BIT(17), 0x0);
			/* 4. Set LC calibration begin */
			rtl_set_rfreg(hw, (क्रमागत radio_path)index, RF_CHNLBW,
				      0x08000, 0x01);
		पूर्ण
		u4पंचांगp = rtl_get_rfreg(hw, (क्रमागत radio_path)index, RF_SYN_G6,
				  RFREG_OFFSET_MASK);
		जबतक ((!(u4पंचांगp & BIT(11))) && समयcount <= समयout) अणु
			mdelay(50);
			समयcount += 50;
			u4पंचांगp = rtl_get_rfreg(hw, (क्रमागत radio_path)index,
					      RF_SYN_G6, RFREG_OFFSET_MASK);
		पूर्ण
		RTPRINT(rtlpriv, FINIT, INIT_IQK,
			"PHY_LCK finish delay for %d ms=2\n", समयcount);
		rtl_get_rfreg(hw, index, RF_SYN_G4, RFREG_OFFSET_MASK);
		अगर (index == 0 && rtlhal->पूर्णांकerfaceindex == 0) अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"path-A / 5G LCK\n");
		पूर्ण अन्यथा अणु
			RTPRINT(rtlpriv, FINIT, INIT_IQK,
				"path-B / 2.4G LCK\n");
		पूर्ण
		स_रखो(&curvecount_val[0], 0, CV_CURVE_CNT * 2);
		/* Set LC calibration off */
		rtl_set_rfreg(hw, (क्रमागत radio_path)index, RF_CHNLBW,
			      0x08000, 0x0);
		RTPRINT(rtlpriv, FINIT, INIT_IQK,  "set RF 0x18[15] = 0\n");
		/* save Curve-counting number */
		क्रम (i = 0; i < CV_CURVE_CNT; i++) अणु
			u32 पढ़ोval = 0, पढ़ोval2 = 0;
			rtl_set_rfreg(hw, (क्रमागत radio_path)index, 0x3F,
				      0x7f, i);

			rtl_set_rfreg(hw, (क्रमागत radio_path)index, 0x4D,
				RFREG_OFFSET_MASK, 0x0);
			पढ़ोval = rtl_get_rfreg(hw, (क्रमागत radio_path)index,
					  0x4F, RFREG_OFFSET_MASK);
			curvecount_val[2 * i + 1] = (पढ़ोval & 0xfffe0) >> 5;
			/* reg 0x4f [4:0] */
			/* reg 0x50 [19:10] */
			पढ़ोval2 = rtl_get_rfreg(hw, (क्रमागत radio_path)index,
						 0x50, 0xffc00);
			curvecount_val[2 * i] = (((पढ़ोval & 0x1F) << 10) |
						 पढ़ोval2);
		पूर्ण
		अगर (index == 0 && rtlhal->पूर्णांकerfaceindex == 0)
			_rtl92d_phy_calc_curvindex(hw, tarअ_लोhnl_5g,
						   curvecount_val,
						   true, curveindex_5g);
		अन्यथा
			_rtl92d_phy_calc_curvindex(hw, tarअ_लोhnl_2g,
						   curvecount_val,
						   false, curveindex_2g);
		/* चयन CV-curve control mode */
		rtl_set_rfreg(hw, (क्रमागत radio_path)index, RF_SYN_G7,
			      BIT(17), 0x1);
	पूर्ण

	/* Restore original situation  */
	क्रम (index = 0; index < path; index++) अणु
		offset = index == 0 ? ROFDM0_XAAGCCORE1 : ROFDM0_XBAGCCORE1;
		rtl_ग_लिखो_byte(rtlpriv, offset, 0x50);
		rtl_ग_लिखो_byte(rtlpriv, offset, rf_mode[index]);
	पूर्ण
	अगर ((पंचांगpreg & 0x70) != 0)
		rtl_ग_लिखो_byte(rtlpriv, 0xd03, पंचांगpreg);
	अन्यथा /*Deal with Packet TX हाल */
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
	rtl_set_bbreg(hw, RFPGA0_ANALOGPARAMETER4, 0xF00000, 0x00);
	_rtl92d_phy_reload_lck_setting(hw, rtlpriv->phy.current_channel);
पूर्ण

अटल व्योम _rtl92d_phy_lc_calibrate(काष्ठा ieee80211_hw *hw, bool is2t)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "cosa PHY_LCK ver=2\n");
	_rtl92d_phy_lc_calibrate_sw(hw, is2t);
पूर्ण

व्योम rtl92d_phy_lc_calibrate(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 समयout = 2000, समयcount = 0;

	जबतक (rtlpriv->mac80211.act_scanning && समयcount < समयout) अणु
		udelay(50);
		समयcount += 50;
	पूर्ण

	rtlphy->lck_inprogress = true;
	RTPRINT(rtlpriv, FINIT, INIT_IQK,
		"LCK:Start!!! currentband %x delay %d ms\n",
		rtlhal->current_bandtype, समयcount);
	अगर (IS_92D_SINGLEPHY(rtlhal->version)) अणु
		_rtl92d_phy_lc_calibrate(hw, true);
	पूर्ण अन्यथा अणु
		/* For 1T1R */
		_rtl92d_phy_lc_calibrate(hw, false);
	पूर्ण
	rtlphy->lck_inprogress = false;
	RTPRINT(rtlpriv, FINIT, INIT_IQK,  "LCK:Finish!!!\n");
पूर्ण

व्योम rtl92d_phy_ap_calibrate(काष्ठा ieee80211_hw *hw, s8 delta)
अणु
	वापस;
पूर्ण

अटल bool _rtl92d_phy_set_sw_chnl_cmdarray(काष्ठा swchnlcmd *cmdtable,
		u32 cmdtableidx, u32 cmdtablesz, क्रमागत swchnlcmd_id cmdid,
		u32 para1, u32 para2, u32 msdelay)
अणु
	काष्ठा swchnlcmd *pcmd;

	अगर (cmdtable == शून्य) अणु
		WARN_ONCE(true, "rtl8192de: cmdtable cannot be NULL\n");
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

व्योम rtl92d_phy_reset_iqk_result(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 i;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
		"settings regs %d default regs %d\n",
		(पूर्णांक)(माप(rtlphy->iqk_matrix) /
		      माप(काष्ठा iqk_matrix_regs)),
		IQK_MATRIX_REG_NUM);
	/* 0xe94, 0xe9c, 0xea4, 0xeac, 0xeb4, 0xebc, 0xec4, 0xecc */
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

अटल bool _rtl92d_phy_sw_chnl_step_by_step(काष्ठा ieee80211_hw *hw,
					     u8 channel, u8 *stage, u8 *step,
					     u32 *delay)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
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
	_rtl92d_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					 MAX_PRECMD_CNT,
					 CMDID_SET_TXPOWEROWER_LEVEL, 0, 0, 0);
	_rtl92d_phy_set_sw_chnl_cmdarray(precommoncmd, precommoncmdcnt++,
					 MAX_PRECMD_CNT, CMDID_END, 0, 0, 0);
	postcommoncmdcnt = 0;
	_rtl92d_phy_set_sw_chnl_cmdarray(postcommoncmd, postcommoncmdcnt++,
					 MAX_POSTCMD_CNT, CMDID_END, 0, 0, 0);
	rfdependcmdcnt = 0;
	_rtl92d_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
					 MAX_RFDEPENDCMD_CNT, CMDID_RF_WRITEREG,
					 RF_CHNLBW, channel, 0);
	_rtl92d_phy_set_sw_chnl_cmdarray(rfdependcmd, rfdependcmdcnt++,
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
			rtl92d_phy_set_txघातer_level(hw, channel);
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
					0xffffff00) | currentcmd->para2);
				अगर (rtlpriv->rtlhal.current_bandtype ==
				    BAND_ON_5G) अणु
					अगर (currentcmd->para2 > 99)
						rtlphy->rfreg_chnlval[rfpath] =
						    rtlphy->rfreg_chnlval
						    [rfpath] | (BIT(18));
					अन्यथा
						rtlphy->rfreg_chnlval[rfpath] =
						    rtlphy->rfreg_chnlval
						    [rfpath] & (~BIT(18));
					rtlphy->rfreg_chnlval[rfpath] |=
						 (BIT(16) | BIT(8));
				पूर्ण अन्यथा अणु
					rtlphy->rfreg_chnlval[rfpath] &=
						~(BIT(8) | BIT(16) | BIT(18));
				पूर्ण
				rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath,
					      currentcmd->para1,
					      RFREG_OFFSET_MASK,
					      rtlphy->rfreg_chnlval[rfpath]);
				_rtl92d_phy_reload_imr_setting(hw, channel,
							       rfpath);
			पूर्ण
			_rtl92d_phy_चयन_rf_setting(hw, channel);
			/* करो IQK when all parameters are पढ़ोy */
			rtl92d_phy_reload_iqk_setting(hw, channel);
			अवरोध;
		शेष:
			pr_err("switch case %#x not processed\n",
			       currentcmd->cmdid);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण जबतक (true);
	(*delay) = currentcmd->msdelay;
	(*step)++;
	वापस false;
पूर्ण

u8 rtl92d_phy_sw_chnl(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u32 delay;
	u32 समयout = 1000, समयcount = 0;
	u8 channel = rtlphy->current_channel;
	u32 ret_value;

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
	अगर (rtlhal->macphymode == SINGLEMAC_SINGLEPHY &&
	    rtlhal->bandset == BAND_ON_BOTH) अणु
		ret_value = rtl_get_bbreg(hw, RFPGA0_XAB_RFPARAMETER,
					  MASKDWORD);
		अगर (rtlphy->current_channel > 14 && !(ret_value & BIT(0)))
			rtl92d_phy_चयन_wirelessband(hw, BAND_ON_5G);
		अन्यथा अगर (rtlphy->current_channel <= 14 && (ret_value & BIT(0)))
			rtl92d_phy_चयन_wirelessband(hw, BAND_ON_2_4G);
	पूर्ण
	चयन (rtlhal->current_bandtype) अणु
	हाल BAND_ON_5G:
		/* Get first channel error when change between
		 * 5G and 2.4G band. */
		अगर (channel <= 14)
			वापस 0;
		WARN_ONCE((channel <= 14), "rtl8192de: 5G but channel<=14\n");
		अवरोध;
	हाल BAND_ON_2_4G:
		/* Get first channel error when change between
		 * 5G and 2.4G band. */
		अगर (channel > 14)
			वापस 0;
		WARN_ONCE((channel > 14), "rtl8192de: 2G but channel>14\n");
		अवरोध;
	शेष:
		WARN_ONCE(true, "rtl8192de: Invalid WirelessMode(%#x)!!\n",
			  rtlpriv->mac80211.mode);
		अवरोध;
	पूर्ण
	rtlphy->sw_chnl_inprogress = true;
	अगर (channel == 0)
		channel = 1;
	rtlphy->sw_chnl_stage = 0;
	rtlphy->sw_chnl_step = 0;
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE,
		"switch to channel%d\n", rtlphy->current_channel);

	करो अणु
		अगर (!rtlphy->sw_chnl_inprogress)
			अवरोध;
		अगर (!_rtl92d_phy_sw_chnl_step_by_step(hw,
						      rtlphy->current_channel,
		    &rtlphy->sw_chnl_stage, &rtlphy->sw_chnl_step, &delay)) अणु
			अगर (delay > 0)
				mdelay(delay);
			अन्यथा
				जारी;
		पूर्ण अन्यथा अणु
			rtlphy->sw_chnl_inprogress = false;
		पूर्ण
		अवरोध;
	पूर्ण जबतक (true);
	rtl_dbg(rtlpriv, COMP_SCAN, DBG_TRACE, "<==\n");
	rtlphy->sw_chnl_inprogress = false;
	वापस 1;
पूर्ण

अटल व्योम rtl92d_phy_set_io(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *de_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"--->Cmd(%#x), set_io_inprogress(%d)\n",
		rtlphy->current_io_type, rtlphy->set_io_inprogress);
	चयन (rtlphy->current_io_type) अणु
	हाल IO_CMD_RESUME_DM_BY_SCAN:
		de_digtable->cur_igvalue = rtlphy->initgain_backup.xaagccore1;
		rtl92d_dm_ग_लिखो_dig(hw);
		rtl92d_phy_set_txघातer_level(hw, rtlphy->current_channel);
		अवरोध;
	हाल IO_CMD_PAUSE_DM_BY_SCAN:
		rtlphy->initgain_backup.xaagccore1 = de_digtable->cur_igvalue;
		de_digtable->cur_igvalue = 0x37;
		rtl92d_dm_ग_लिखो_dig(hw);
		अवरोध;
	शेष:
		pr_err("switch case %#x not processed\n",
		       rtlphy->current_io_type);
		अवरोध;
	पूर्ण
	rtlphy->set_io_inprogress = false;
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE, "<---(%#x)\n",
		rtlphy->current_io_type);
पूर्ण

bool rtl92d_phy_set_io_cmd(काष्ठा ieee80211_hw *hw, क्रमागत io_type iotype)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	bool postprocessing = false;

	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
		"-->IO Cmd(%#x), set_io_inprogress(%d)\n",
		 iotype, rtlphy->set_io_inprogress);
	करो अणु
		चयन (iotype) अणु
		हाल IO_CMD_RESUME_DM_BY_SCAN:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
				"[IO CMD] Resume DM after scan\n");
			postprocessing = true;
			अवरोध;
		हाल IO_CMD_PAUSE_DM_BY_SCAN:
			rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE,
				"[IO CMD] Pause DM before scan\n");
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
	rtl92d_phy_set_io(hw);
	rtl_dbg(rtlpriv, COMP_CMD, DBG_TRACE, "<--IO Type(%#x)\n", iotype);
	वापस true;
पूर्ण

अटल व्योम _rtl92d_phy_set_rfon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* a.  SYS_CLKR 0x08[11] = 1  restore MAC घड़ी */
	/* b.  SPS_CTRL 0x11[7:0] = 0x2b */
	अगर (rtlpriv->rtlhal.macphymode == SINGLEMAC_SINGLEPHY)
		rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x2b);
	/* c.  For PCIE: SYS_FUNC_EN 0x02[7:0] = 0xE3 enable BB TRX function */
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	/* RF_ON_EXCEP(d~g): */
	/* d.  APSD_CTRL 0x600[7:0] = 0x00 */
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x00);
	/* e.  SYS_FUNC_EN 0x02[7:0] = 0xE2  reset BB TRX function again */
	/* f.  SYS_FUNC_EN 0x02[7:0] = 0xE3  enable BB TRX function*/
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
	/* g.   txछोड़ो 0x522[7:0] = 0x00  enable mac tx queue */
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
पूर्ण

अटल व्योम _rtl92d_phy_set_rfsleep(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u32 u4bपंचांगp;
	u8 delay = 5;

	/* a.   TXPAUSE 0x522[7:0] = 0xFF  Pause MAC TX queue  */
	rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0xFF);
	/* b.   RF path 0 offset 0x00 = 0x00  disable RF  */
	rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);
	/* c.   APSD_CTRL 0x600[7:0] = 0x40 */
	rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x40);
	/* d. APSD_CTRL 0x600[7:0] = 0x00
	 * APSD_CTRL 0x600[7:0] = 0x00
	 * RF path 0 offset 0x00 = 0x00
	 * APSD_CTRL 0x600[7:0] = 0x40
	 * */
	u4bपंचांगp = rtl_get_rfreg(hw, RF90_PATH_A, 0, RFREG_OFFSET_MASK);
	जबतक (u4bपंचांगp != 0 && delay > 0) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x0);
		rtl_set_rfreg(hw, RF90_PATH_A, 0x00, RFREG_OFFSET_MASK, 0x00);
		rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x40);
		u4bपंचांगp = rtl_get_rfreg(hw, RF90_PATH_A, 0, RFREG_OFFSET_MASK);
		delay--;
	पूर्ण
	अगर (delay == 0) अणु
		/* Jump out the LPS turn off sequence to RF_ON_EXCEP */
		rtl_ग_लिखो_byte(rtlpriv, REG_APSD_CTRL, 0x00);

		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
		rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE3);
		rtl_ग_लिखो_byte(rtlpriv, REG_TXPAUSE, 0x00);
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Fail !!! Switch RF timeout\n");
		वापस;
	पूर्ण
	/* e.   For PCIE: SYS_FUNC_EN 0x02[7:0] = 0xE2 reset BB TRX function */
	rtl_ग_लिखो_byte(rtlpriv, REG_SYS_FUNC_EN, 0xE2);
	/* f.   SPS_CTRL 0x11[7:0] = 0x22 */
	अगर (rtlpriv->rtlhal.macphymode == SINGLEMAC_SINGLEPHY)
		rtl_ग_लिखो_byte(rtlpriv, REG_SPS0_CTRL, 0x22);
	/* g.    SYS_CLKR 0x08[11] = 0  gated MAC घड़ी */
पूर्ण

bool rtl92d_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				   क्रमागत rf_pwrstate rfpwr_state)
अणु

	bool bresult = true;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_pci_priv *pcipriv = rtl_pcipriv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	u8 i, queue_id;
	काष्ठा rtl8192_tx_ring *ring = शून्य;

	अगर (rfpwr_state == ppsc->rfpwr_state)
		वापस false;
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

			RT_CLEAR_PS_LEVEL(ppsc,
					  RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
				"awake, slept:%d ms state_inap:%x\n",
				jअगरfies_to_msecs(jअगरfies -
						 ppsc->last_sleep_jअगरfies),
				 rtlpriv->psc.state_inap);
			ppsc->last_awake_jअगरfies = jअगरfies;
			_rtl92d_phy_set_rfon(hw);
		पूर्ण

		अगर (mac->link_state == MAC80211_LINKED)
			rtlpriv->cfg->ops->led_control(hw,
					 LED_CTL_LINK);
		अन्यथा
			rtlpriv->cfg->ops->led_control(hw,
					 LED_CTL_NO_LINK);
		अवरोध;
	हाल ERFOFF:
		अगर (ppsc->reg_rfps_level & RT_RF_OFF_LEVL_HALT_NIC) अणु
			rtl_dbg(rtlpriv, COMP_RF, DBG_DMESG,
				"IPS Set eRf nic disable\n");
			rtl_ps_disable_nic(hw);
			RT_SET_PS_LEVEL(ppsc, RT_RF_OFF_LEVL_HALT_NIC);
		पूर्ण अन्यथा अणु
			अगर (ppsc->rfoff_reason == RF_CHANGE_BY_IPS)
				rtlpriv->cfg->ops->led_control(hw,
						 LED_CTL_NO_LINK);
			अन्यथा
				rtlpriv->cfg->ops->led_control(hw,
						 LED_CTL_POWER_OFF);
		पूर्ण
		अवरोध;
	हाल ERFSLEEP:
		अगर (ppsc->rfpwr_state == ERFOFF)
			वापस false;

		क्रम (queue_id = 0, i = 0;
		     queue_id < RTL_PCI_MAX_TX_QUEUE_COUNT;) अणु
			ring = &pcipriv->dev.tx_ring[queue_id];
			अगर (skb_queue_len(&ring->queue) == 0 ||
			    queue_id == BEACON_QUEUE) अणु
				queue_id++;
				जारी;
			पूर्ण अन्यथा अगर (rtlpci->pdev->current_state != PCI_D0) अणु
				rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
					"eRf Off/Sleep: %d times TcbBusyQueue[%d] !=0 but lower power state!\n",
					i + 1, queue_id);
				अवरोध;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"eRf Off/Sleep: %d times TcbBusyQueue[%d] =%d before doze!\n",
					i + 1, queue_id,
					skb_queue_len(&ring->queue));
				udelay(10);
				i++;
			पूर्ण

			अगर (i >= MAX_DOZE_WAITING_TIMES_9x) अणु
				rtl_dbg(rtlpriv, COMP_ERR, DBG_WARNING,
					"ERFOFF: %d times TcbBusyQueue[%d] = %d !\n",
					MAX_DOZE_WAITING_TIMES_9x, queue_id,
					skb_queue_len(&ring->queue));
				अवरोध;
			पूर्ण
		पूर्ण
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"Set rfsleep awakened:%d ms\n",
			 jअगरfies_to_msecs(jअगरfies - ppsc->last_awake_jअगरfies));
		rtl_dbg(rtlpriv, COMP_POWER, DBG_DMESG,
			"sleep awakened:%d ms state_inap:%x\n",
			jअगरfies_to_msecs(jअगरfies -
					 ppsc->last_awake_jअगरfies),
			rtlpriv->psc.state_inap);
		ppsc->last_sleep_jअगरfies = jअगरfies;
		_rtl92d_phy_set_rfsleep(hw);
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

व्योम rtl92d_phy_config_macphymode(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 offset = REG_MAC_PHY_CTRL_NORMAL;

	चयन (rtlhal->macphymode) अणु
	हाल DUALMAC_DUALPHY:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"MacPhyMode: DUALMAC_DUALPHY\n");
		rtl_ग_लिखो_byte(rtlpriv, offset, 0xF3);
		अवरोध;
	हाल SINGLEMAC_SINGLEPHY:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"MacPhyMode: SINGLEMAC_SINGLEPHY\n");
		rtl_ग_लिखो_byte(rtlpriv, offset, 0xF4);
		अवरोध;
	हाल DUALMAC_SINGLEPHY:
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
			"MacPhyMode: DUALMAC_SINGLEPHY\n");
		rtl_ग_लिखो_byte(rtlpriv, offset, 0xF1);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92d_phy_config_macphymode_info(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	चयन (rtlhal->macphymode) अणु
	हाल DUALMAC_SINGLEPHY:
		rtlphy->rf_type = RF_2T2R;
		rtlhal->version |= RF_TYPE_2T2R;
		rtlhal->bandset = BAND_ON_BOTH;
		rtlhal->current_bandtype = BAND_ON_2_4G;
		अवरोध;

	हाल SINGLEMAC_SINGLEPHY:
		rtlphy->rf_type = RF_2T2R;
		rtlhal->version |= RF_TYPE_2T2R;
		rtlhal->bandset = BAND_ON_BOTH;
		rtlhal->current_bandtype = BAND_ON_2_4G;
		अवरोध;

	हाल DUALMAC_DUALPHY:
		rtlphy->rf_type = RF_1T1R;
		rtlhal->version &= RF_TYPE_1T1R;
		/* Now we let MAC0 run on 5G band. */
		अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
			rtlhal->bandset = BAND_ON_5G;
			rtlhal->current_bandtype = BAND_ON_5G;
		पूर्ण अन्यथा अणु
			rtlhal->bandset = BAND_ON_2_4G;
			rtlhal->current_bandtype = BAND_ON_2_4G;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

u8 rtl92d_get_chnlgroup_fromarray(u8 chnl)
अणु
	u8 group;
	u8 channel_info[59] = अणु
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56,
		58, 60, 62, 64, 100, 102, 104, 106, 108,
		110, 112, 114, 116, 118, 120, 122, 124,
		126, 128, 130, 132, 134, 136, 138, 140,
		149, 151, 153, 155, 157, 159, 161, 163,
		165
	पूर्ण;

	अगर (channel_info[chnl] <= 3)
		group = 0;
	अन्यथा अगर (channel_info[chnl] <= 9)
		group = 1;
	अन्यथा अगर (channel_info[chnl] <= 14)
		group = 2;
	अन्यथा अगर (channel_info[chnl] <= 44)
		group = 3;
	अन्यथा अगर (channel_info[chnl] <= 54)
		group = 4;
	अन्यथा अगर (channel_info[chnl] <= 64)
		group = 5;
	अन्यथा अगर (channel_info[chnl] <= 112)
		group = 6;
	अन्यथा अगर (channel_info[chnl] <= 126)
		group = 7;
	अन्यथा अगर (channel_info[chnl] <= 140)
		group = 8;
	अन्यथा अगर (channel_info[chnl] <= 153)
		group = 9;
	अन्यथा अगर (channel_info[chnl] <= 159)
		group = 10;
	अन्यथा
		group = 11;
	वापस group;
पूर्ण

व्योम rtl92d_phy_set_घातeron(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	अचिन्हित दीर्घ flags;
	u8 value8;
	u16 i;
	u32 mac_reg = (rtlhal->पूर्णांकerfaceindex == 0 ? REG_MAC0 : REG_MAC1);

	/* notice fw know band status  0x81[1]/0x53[1] = 0: 5G, 1: 2G */
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		value8 = rtl_पढ़ो_byte(rtlpriv, mac_reg);
		value8 |= BIT(1);
		rtl_ग_लिखो_byte(rtlpriv, mac_reg, value8);
	पूर्ण अन्यथा अणु
		value8 = rtl_पढ़ो_byte(rtlpriv, mac_reg);
		value8 &= (~BIT(1));
		rtl_ग_लिखो_byte(rtlpriv, mac_reg, value8);
	पूर्ण

	अगर (rtlhal->macphymode == SINGLEMAC_SINGLEPHY) अणु
		value8 = rtl_पढ़ो_byte(rtlpriv, REG_MAC0);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC0, value8 | MAC0_ON);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&globalmutex_घातer, flags);
		अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
			value8 = rtl_पढ़ो_byte(rtlpriv, REG_MAC0);
			rtl_ग_लिखो_byte(rtlpriv, REG_MAC0, value8 | MAC0_ON);
		पूर्ण अन्यथा अणु
			value8 = rtl_पढ़ो_byte(rtlpriv, REG_MAC1);
			rtl_ग_लिखो_byte(rtlpriv, REG_MAC1, value8 | MAC1_ON);
		पूर्ण
		value8 = rtl_पढ़ो_byte(rtlpriv, REG_POWER_OFF_IN_PROCESS);
		spin_unlock_irqrestore(&globalmutex_घातer, flags);
		क्रम (i = 0; i < 200; i++) अणु
			अगर ((value8 & BIT(7)) == 0) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				udelay(500);
				spin_lock_irqsave(&globalmutex_घातer, flags);
				value8 = rtl_पढ़ो_byte(rtlpriv,
						    REG_POWER_OFF_IN_PROCESS);
				spin_unlock_irqrestore(&globalmutex_घातer,
						       flags);
			पूर्ण
		पूर्ण
		अगर (i == 200)
			WARN_ONCE(true, "rtl8192de: Another mac power off over time\n");
	पूर्ण
पूर्ण

व्योम rtl92d_phy_config_maccoexist_rfpage(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	चयन (rtlpriv->rtlhal.macphymode) अणु
	हाल DUALMAC_DUALPHY:
		rtl_ग_लिखो_byte(rtlpriv, REG_DMC, 0x0);
		rtl_ग_लिखो_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x08);
		rtl_ग_लिखो_word(rtlpriv, REG_TRXFF_BNDY + 2, 0x13ff);
		अवरोध;
	हाल DUALMAC_SINGLEPHY:
		rtl_ग_लिखो_byte(rtlpriv, REG_DMC, 0xf8);
		rtl_ग_लिखो_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x08);
		rtl_ग_लिखो_word(rtlpriv, REG_TRXFF_BNDY + 2, 0x13ff);
		अवरोध;
	हाल SINGLEMAC_SINGLEPHY:
		rtl_ग_लिखो_byte(rtlpriv, REG_DMC, 0x0);
		rtl_ग_लिखो_byte(rtlpriv, REG_RX_PKT_LIMIT, 0x10);
		rtl_ग_लिखो_word(rtlpriv, (REG_TRXFF_BNDY + 2), 0x27FF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92d_update_bbrf_configuration(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 rfpath, i;

	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "==>\n");
	/* r_select_5G क्रम path_A/B 0 क्रम 2.4G, 1 क्रम 5G */
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		/* r_select_5G क्रम path_A/B,0x878 */
		rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(0), 0x0);
		rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(15), 0x0);
		अगर (rtlhal->macphymode != DUALMAC_DUALPHY) अणु
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(16), 0x0);
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(31), 0x0);
		पूर्ण
		/* rssi_table_select:index 0 क्रम 2.4G.1~3 क्रम 5G,0xc78 */
		rtl_set_bbreg(hw, ROFDM0_AGCRSSITABLE, BIT(6) | BIT(7), 0x0);
		/* fc_area  0xd2c */
		rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(14) | BIT(13), 0x0);
		/* 5G LAN ON */
		rtl_set_bbreg(hw, 0xB30, 0x00F00000, 0xa);
		/* TX BB gain shअगरt*1,Just क्रम testchip,0xc80,0xc88 */
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, MASKDWORD,
			      0x40000100);
		rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, MASKDWORD,
			      0x40000100);
		अगर (rtlhal->macphymode == DUALMAC_DUALPHY) अणु
			rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW,
				      BIT(10) | BIT(6) | BIT(5),
				      ((rtlefuse->eeprom_c9 & BIT(3)) >> 3) |
				      (rtlefuse->eeprom_c9 & BIT(1)) |
				      ((rtlefuse->eeprom_cc & BIT(1)) << 4));
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE,
				      BIT(10) | BIT(6) | BIT(5),
				      ((rtlefuse->eeprom_c9 & BIT(2)) >> 2) |
				      ((rtlefuse->eeprom_c9 & BIT(0)) << 1) |
				      ((rtlefuse->eeprom_cc & BIT(0)) << 5));
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(15), 0);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW,
				      BIT(26) | BIT(22) | BIT(21) | BIT(10) |
				      BIT(6) | BIT(5),
				      ((rtlefuse->eeprom_c9 & BIT(3)) >> 3) |
				      (rtlefuse->eeprom_c9 & BIT(1)) |
				      ((rtlefuse->eeprom_cc & BIT(1)) << 4) |
				      ((rtlefuse->eeprom_c9 & BIT(7)) << 9) |
				      ((rtlefuse->eeprom_c9 & BIT(5)) << 12) |
				      ((rtlefuse->eeprom_cc & BIT(3)) << 18));
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE,
				      BIT(10) | BIT(6) | BIT(5),
				      ((rtlefuse->eeprom_c9 & BIT(2)) >> 2) |
				      ((rtlefuse->eeprom_c9 & BIT(0)) << 1) |
				      ((rtlefuse->eeprom_cc & BIT(0)) << 5));
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE,
				      BIT(10) | BIT(6) | BIT(5),
				      ((rtlefuse->eeprom_c9 & BIT(6)) >> 6) |
				      ((rtlefuse->eeprom_c9 & BIT(4)) >> 3) |
				      ((rtlefuse->eeprom_cc & BIT(2)) << 3));
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER,
				      BIT(31) | BIT(15), 0);
		पूर्ण
		/* 1.5V_LDO */
	पूर्ण अन्यथा अणु
		/* r_select_5G क्रम path_A/B */
		rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(0), 0x1);
		rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(15), 0x1);
		अगर (rtlhal->macphymode != DUALMAC_DUALPHY) अणु
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(16), 0x1);
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(31), 0x1);
		पूर्ण
		/* rssi_table_select:index 0 क्रम 2.4G.1~3 क्रम 5G */
		rtl_set_bbreg(hw, ROFDM0_AGCRSSITABLE, BIT(6) | BIT(7), 0x1);
		/* fc_area */
		rtl_set_bbreg(hw, ROFDM1_CFOTRACKING, BIT(14) | BIT(13), 0x1);
		/* 5G LAN ON */
		rtl_set_bbreg(hw, 0xB30, 0x00F00000, 0x0);
		/* TX BB gain shअगरt,Just क्रम testchip,0xc80,0xc88 */
		अगर (rtlefuse->पूर्णांकernal_pa_5g[0])
			rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, MASKDWORD,
				      0x2d4000b5);
		अन्यथा
			rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE, MASKDWORD,
				      0x20000080);
		अगर (rtlefuse->पूर्णांकernal_pa_5g[1])
			rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, MASKDWORD,
				      0x2d4000b5);
		अन्यथा
			rtl_set_bbreg(hw, ROFDM0_XBTXIQIMBALANCE, MASKDWORD,
				      0x20000080);
		अगर (rtlhal->macphymode == DUALMAC_DUALPHY) अणु
			rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW,
				      BIT(10) | BIT(6) | BIT(5),
				      (rtlefuse->eeprom_cc & BIT(5)));
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE, BIT(10),
				      ((rtlefuse->eeprom_cc & BIT(4)) >> 4));
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER, BIT(15),
				      (rtlefuse->eeprom_cc & BIT(4)) >> 4);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, RFPGA0_XAB_RFINTERFACESW,
				      BIT(26) | BIT(22) | BIT(21) | BIT(10) |
				      BIT(6) | BIT(5),
				      (rtlefuse->eeprom_cc & BIT(5)) |
				      ((rtlefuse->eeprom_cc & BIT(7)) << 14));
			rtl_set_bbreg(hw, RFPGA0_XA_RFINTERFACEOE, BIT(10),
				      ((rtlefuse->eeprom_cc & BIT(4)) >> 4));
			rtl_set_bbreg(hw, RFPGA0_XB_RFINTERFACEOE, BIT(10),
				      ((rtlefuse->eeprom_cc & BIT(6)) >> 6));
			rtl_set_bbreg(hw, RFPGA0_XAB_RFPARAMETER,
				      BIT(31) | BIT(15),
				      ((rtlefuse->eeprom_cc & BIT(4)) >> 4) |
				      ((rtlefuse->eeprom_cc & BIT(6)) << 10));
		पूर्ण
	पूर्ण
	/* update IQK related settings */
	rtl_set_bbreg(hw, ROFDM0_XARXIQIMBALANCE, MASKDWORD, 0x40000100);
	rtl_set_bbreg(hw, ROFDM0_XBRXIQIMBALANCE, MASKDWORD, 0x40000100);
	rtl_set_bbreg(hw, ROFDM0_XCTXAFE, 0xF0000000, 0x00);
	rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(30) | BIT(28) |
		      BIT(26) | BIT(24), 0x00);
	rtl_set_bbreg(hw, ROFDM0_XDTXAFE, 0xF0000000, 0x00);
	rtl_set_bbreg(hw, 0xca0, 0xF0000000, 0x00);
	rtl_set_bbreg(hw, ROFDM0_AGCRSSITABLE, 0x0000F000, 0x00);

	/* Update RF */
	क्रम (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
	     rfpath++) अणु
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			/* MOD_AG क्रम RF path_A 0x18 BIT8,BIT16 */
			rtl_set_rfreg(hw, rfpath, RF_CHNLBW, BIT(8) | BIT(16) |
				      BIT(18), 0);
			/* RF0x0b[16:14] =3b'111 */
			rtl_set_rfreg(hw, (क्रमागत radio_path)rfpath, 0x0B,
				      0x1c000, 0x07);
		पूर्ण अन्यथा अणु
			/* MOD_AG क्रम RF path_A 0x18 BIT8,BIT16 */
			rtl_set_rfreg(hw, rfpath, RF_CHNLBW, BIT(8) |
				      BIT(16) | BIT(18),
				      (BIT(16) | BIT(8)) >> 8);
		पूर्ण
	पूर्ण
	/* Update क्रम all band. */
	/* DMDP */
	अगर (rtlphy->rf_type == RF_1T1R) अणु
		/* Use antenna 0,0xc04,0xd04 */
		rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKBYTE0, 0x11);
		rtl_set_bbreg(hw, ROFDM1_TRXPATHENABLE, BDWORD, 0x1);

		/* enable ad/da घड़ी1 क्रम dual-phy reg0x888 */
		अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
			rtl_set_bbreg(hw, RFPGA0_ADDALLOCKEN, BIT(12) |
				      BIT(13), 0x3);
		पूर्ण अन्यथा अणु
			rtl92d_phy_enable_anotherphy(hw, false);
			rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD,
				"MAC1 use DBI to update 0x888\n");
			/* 0x888 */
			rtl92de_ग_लिखो_dword_dbi(hw, RFPGA0_ADDALLOCKEN,
						rtl92de_पढ़ो_dword_dbi(hw,
						RFPGA0_ADDALLOCKEN,
						BIT(3)) | BIT(12) | BIT(13),
						BIT(3));
			rtl92d_phy_घातerकरोwn_anotherphy(hw, false);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Single PHY */
		/* Use antenna 0 & 1,0xc04,0xd04 */
		rtl_set_bbreg(hw, ROFDM0_TRXPATHENABLE, MASKBYTE0, 0x33);
		rtl_set_bbreg(hw, ROFDM1_TRXPATHENABLE, BDWORD, 0x3);
		/* disable ad/da घड़ी1,0x888 */
		rtl_set_bbreg(hw, RFPGA0_ADDALLOCKEN, BIT(12) | BIT(13), 0);
	पूर्ण
	क्रम (rfpath = RF90_PATH_A; rfpath < rtlphy->num_total_rfpath;
	     rfpath++) अणु
		rtlphy->rfreg_chnlval[rfpath] = rtl_get_rfreg(hw, rfpath,
						RF_CHNLBW, RFREG_OFFSET_MASK);
		rtlphy->reg_rf3c[rfpath] = rtl_get_rfreg(hw, rfpath, 0x3C,
			RFREG_OFFSET_MASK);
	पूर्ण
	क्रम (i = 0; i < 2; i++)
		rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "RF 0x18 = 0x%x\n",
			rtlphy->rfreg_chnlval[i]);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "<==\n");

पूर्ण

bool rtl92d_phy_check_घातeroff(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 u1bपंचांगp;
	अचिन्हित दीर्घ flags;

	अगर (rtlhal->macphymode == SINGLEMAC_SINGLEPHY) अणु
		u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MAC0);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC0, u1bपंचांगp & (~MAC0_ON));
		वापस true;
	पूर्ण
	spin_lock_irqsave(&globalmutex_घातer, flags);
	अगर (rtlhal->पूर्णांकerfaceindex == 0) अणु
		u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MAC0);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC0, u1bपंचांगp & (~MAC0_ON));
		u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MAC1);
		u1bपंचांगp &= MAC1_ON;
	पूर्ण अन्यथा अणु
		u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MAC1);
		rtl_ग_लिखो_byte(rtlpriv, REG_MAC1, u1bपंचांगp & (~MAC1_ON));
		u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_MAC0);
		u1bपंचांगp &= MAC0_ON;
	पूर्ण
	अगर (u1bपंचांगp) अणु
		spin_unlock_irqrestore(&globalmutex_घातer, flags);
		वापस false;
	पूर्ण
	u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, REG_POWER_OFF_IN_PROCESS);
	u1bपंचांगp |= BIT(7);
	rtl_ग_लिखो_byte(rtlpriv, REG_POWER_OFF_IN_PROCESS, u1bपंचांगp);
	spin_unlock_irqrestore(&globalmutex_घातer, flags);
	वापस true;
पूर्ण
