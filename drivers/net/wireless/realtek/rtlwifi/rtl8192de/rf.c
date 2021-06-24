<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"
#समावेश "hw.h"

व्योम rtl92d_phy_rf6052_set_bandwidth(काष्ठा ieee80211_hw *hw, u8 bandwidth)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 rfpath;

	चयन (bandwidth) अणु
	हाल HT_CHANNEL_WIDTH_20:
		क्रम (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) अणु
			rtlphy->rfreg_chnlval[rfpath] = ((rtlphy->rfreg_chnlval
					[rfpath] & 0xfffff3ff) | 0x0400);
			rtl_set_rfreg(hw, rfpath, RF_CHNLBW, BIT(10) |
				      BIT(11), 0x01);

			rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
				"20M RF 0x18 = 0x%x\n",
				rtlphy->rfreg_chnlval[rfpath]);
		पूर्ण

		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		क्रम (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) अणु
			rtlphy->rfreg_chnlval[rfpath] =
			    ((rtlphy->rfreg_chnlval[rfpath] & 0xfffff3ff));
			rtl_set_rfreg(hw, rfpath, RF_CHNLBW, BIT(10) | BIT(11),
				      0x00);
			rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD,
				"40M RF 0x18 = 0x%x\n",
				rtlphy->rfreg_chnlval[rfpath]);
		पूर्ण
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n", bandwidth);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl92d_phy_rf6052_set_cck_txघातer(काष्ठा ieee80211_hw *hw,
				       u8 *pघातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 tx_agc[2] = अणु0, 0पूर्ण, पंचांगpval;
	bool turbo_scanoff = false;
	u8 idx1, idx2;
	u8 *ptr;

	अगर (rtlefuse->eeprom_regulatory != 0)
		turbo_scanoff = true;
	अगर (mac->act_scanning) अणु
		tx_agc[RF90_PATH_A] = 0x3f3f3f3f;
		tx_agc[RF90_PATH_B] = 0x3f3f3f3f;
		अगर (turbo_scanoff) अणु
			क्रम (idx1 = RF90_PATH_A; idx1 <= RF90_PATH_B; idx1++) अणु
				tx_agc[idx1] = pघातerlevel[idx1] |
				    (pघातerlevel[idx1] << 8) |
				    (pघातerlevel[idx1] << 16) |
				    (pघातerlevel[idx1] << 24);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (idx1 = RF90_PATH_A; idx1 <= RF90_PATH_B; idx1++) अणु
			tx_agc[idx1] = pघातerlevel[idx1] |
			    (pघातerlevel[idx1] << 8) |
			    (pघातerlevel[idx1] << 16) |
			    (pघातerlevel[idx1] << 24);
		पूर्ण
		अगर (rtlefuse->eeprom_regulatory == 0) अणु
			पंचांगpval = (rtlphy->mcs_offset[0][6]) +
			    (rtlphy->mcs_offset[0][7] << 8);
			tx_agc[RF90_PATH_A] += पंचांगpval;
			पंचांगpval = (rtlphy->mcs_offset[0][14]) +
			    (rtlphy->mcs_offset[0][15] << 24);
			tx_agc[RF90_PATH_B] += पंचांगpval;
		पूर्ण
	पूर्ण

	क्रम (idx1 = RF90_PATH_A; idx1 <= RF90_PATH_B; idx1++) अणु
		ptr = (u8 *) (&(tx_agc[idx1]));
		क्रम (idx2 = 0; idx2 < 4; idx2++) अणु
			अगर (*ptr > RF6052_MAX_TX_PWR)
				*ptr = RF6052_MAX_TX_PWR;
			ptr++;
		पूर्ण
	पूर्ण

	पंचांगpval = tx_agc[RF90_PATH_A] & 0xff;
	rtl_set_bbreg(hw, RTXAGC_A_CCK1_MCS32, MASKBYTE1, पंचांगpval);
	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 1M (rf-A) = 0x%x (reg 0x%x)\n",
		पंचांगpval, RTXAGC_A_CCK1_MCS32);
	पंचांगpval = tx_agc[RF90_PATH_A] >> 8;
	rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, 0xffffff00, पंचांगpval);
	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 2~11M (rf-A) = 0x%x (reg 0x%x)\n",
		पंचांगpval, RTXAGC_B_CCK11_A_CCK2_11);
	पंचांगpval = tx_agc[RF90_PATH_B] >> 24;
	rtl_set_bbreg(hw, RTXAGC_B_CCK11_A_CCK2_11, MASKBYTE0, पंचांगpval);
	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 11M (rf-B) = 0x%x (reg 0x%x)\n",
		पंचांगpval, RTXAGC_B_CCK11_A_CCK2_11);
	पंचांगpval = tx_agc[RF90_PATH_B] & 0x00ffffff;
	rtl_set_bbreg(hw, RTXAGC_B_CCK1_55_MCS32, 0xffffff00, पंचांगpval);
	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 1~5.5M (rf-B) = 0x%x (reg 0x%x)\n",
		पंचांगpval, RTXAGC_B_CCK1_55_MCS32);
पूर्ण

अटल व्योम _rtl92d_phy_get_घातer_base(काष्ठा ieee80211_hw *hw,
				       u8 *pघातerlevel, u8 channel,
				       u32 *ofdmbase, u32 *mcsbase)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 घातerbase0, घातerbase1;
	u8 legacy_pwrdअगरf, ht20_pwrdअगरf;
	u8 i, घातerlevel[2];

	क्रम (i = 0; i < 2; i++) अणु
		घातerlevel[i] = pघातerlevel[i];
		legacy_pwrdअगरf = rtlefuse->txpwr_legacyhtdअगरf[i][channel - 1];
		घातerbase0 = घातerlevel[i] + legacy_pwrdअगरf;
		घातerbase0 = (घातerbase0 << 24) | (घातerbase0 << 16) |
		    (घातerbase0 << 8) | घातerbase0;
		*(ofdmbase + i) = घातerbase0;
		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			" [OFDM power base index rf(%c) = 0x%x]\n",
			i == 0 ? 'A' : 'B', *(ofdmbase + i));
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20) अणु
			ht20_pwrdअगरf = rtlefuse->txpwr_ht20dअगरf[i][channel - 1];
			घातerlevel[i] += ht20_pwrdअगरf;
		पूर्ण
		घातerbase1 = घातerlevel[i];
		घातerbase1 = (घातerbase1 << 24) | (घातerbase1 << 16) |
			     (घातerbase1 << 8) | घातerbase1;
		*(mcsbase + i) = घातerbase1;
		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			" [MCS power base index rf(%c) = 0x%x]\n",
			i == 0 ? 'A' : 'B', *(mcsbase + i));
	पूर्ण
पूर्ण

अटल u8 _rtl92d_phy_get_chnlgroup_bypg(u8 chnlindex)
अणु
	u8 group;
	u8 channel_info[59] = अणु
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58,
		60, 62, 64, 100, 102, 104, 106, 108, 110, 112,
		114, 116, 118, 120, 122, 124, 126, 128,	130, 132,
		134, 136, 138, 140, 149, 151, 153, 155, 157, 159,
		161, 163, 165
	पूर्ण;

	अगर (channel_info[chnlindex] <= 3)	/* Chanel 1-3 */
		group = 0;
	अन्यथा अगर (channel_info[chnlindex] <= 9)	/* Channel 4-9 */
		group = 1;
	अन्यथा अगर (channel_info[chnlindex] <= 14)	/* Channel 10-14 */
		group = 2;
	अन्यथा अगर (channel_info[chnlindex] <= 64)
		group = 6;
	अन्यथा अगर (channel_info[chnlindex] <= 140)
		group = 7;
	अन्यथा
		group = 8;
	वापस group;
पूर्ण

अटल व्योम _rtl92d_get_txघातer_ग_लिखोval_by_regulatory(काष्ठा ieee80211_hw *hw,
						       u8 channel, u8 index,
						       u32 *घातerbase0,
						       u32 *घातerbase1,
						       u32 *p_outग_लिखोval)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 i, chnlgroup = 0, pwr_dअगरf_limit[4];
	u32 ग_लिखोval = 0, customer_limit, rf;

	क्रम (rf = 0; rf < 2; rf++) अणु
		चयन (rtlefuse->eeprom_regulatory) अणु
		हाल 0:
			chnlgroup = 0;
			ग_लिखोval = rtlphy->mcs_offset
					[chnlgroup][index +
					(rf ? 8 : 0)] + ((index < 2) ?
					घातerbase0[rf] :
					घातerbase1[rf]);
			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"RTK better performance, writeval(%c) = 0x%x\n",
				rf == 0 ? 'A' : 'B', ग_लिखोval);
			अवरोध;
		हाल 1:
			अगर (rtlphy->pwrgroup_cnt == 1)
				chnlgroup = 0;
			अगर (rtlphy->pwrgroup_cnt >= MAX_PG_GROUP) अणु
				chnlgroup = _rtl92d_phy_get_chnlgroup_bypg(
								channel - 1);
				अगर (rtlphy->current_chan_bw ==
				    HT_CHANNEL_WIDTH_20)
					chnlgroup++;
				अन्यथा
					chnlgroup += 4;
				ग_लिखोval = rtlphy->mcs_offset
						[chnlgroup][index +
						(rf ? 8 : 0)] + ((index < 2) ?
						घातerbase0[rf] :
						घातerbase1[rf]);
				RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
					"Realtek regulatory, 20MHz, writeval(%c) = 0x%x\n",
					rf == 0 ? 'A' : 'B', ग_लिखोval);
			पूर्ण
			अवरोध;
		हाल 2:
			ग_लिखोval = ((index < 2) ? घातerbase0[rf] :
				   घातerbase1[rf]);
			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"Better regulatory, writeval(%c) = 0x%x\n",
				rf == 0 ? 'A' : 'B', ग_लिखोval);
			अवरोध;
		हाल 3:
			chnlgroup = 0;
			अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
				RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
					"customer's limit, 40MHz rf(%c) = 0x%x\n",
					rf == 0 ? 'A' : 'B',
					rtlefuse->pwrgroup_ht40[rf]
					[channel - 1]);
			पूर्ण अन्यथा अणु
				RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
					"customer's limit, 20MHz rf(%c) = 0x%x\n",
					rf == 0 ? 'A' : 'B',
					rtlefuse->pwrgroup_ht20[rf]
					[channel - 1]);
			पूर्ण
			क्रम (i = 0; i < 4; i++) अणु
				pwr_dअगरf_limit[i] = (u8)((rtlphy->mcs_offset
					[chnlgroup][index + (rf ? 8 : 0)] &
					(0x7f << (i * 8))) >> (i * 8));
				अगर (rtlphy->current_chan_bw ==
				    HT_CHANNEL_WIDTH_20_40) अणु
					अगर (pwr_dअगरf_limit[i] >
					    rtlefuse->pwrgroup_ht40[rf]
					   [channel - 1])
						pwr_dअगरf_limit[i] =
							rtlefuse->pwrgroup_ht40
							[rf][channel - 1];
				पूर्ण अन्यथा अणु
					अगर (pwr_dअगरf_limit[i] >
					    rtlefuse->pwrgroup_ht20[rf][
						channel - 1])
						pwr_dअगरf_limit[i] =
						   rtlefuse->pwrgroup_ht20[rf]
						   [channel - 1];
				पूर्ण
			पूर्ण
			customer_limit = (pwr_dअगरf_limit[3] << 24) |
					 (pwr_dअगरf_limit[2] << 16) |
					 (pwr_dअगरf_limit[1] << 8) |
					 (pwr_dअगरf_limit[0]);
			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"Customer's limit rf(%c) = 0x%x\n",
				rf == 0 ? 'A' : 'B', customer_limit);
			ग_लिखोval = customer_limit + ((index < 2) ?
				   घातerbase0[rf] : घातerbase1[rf]);
			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"Customer, writeval rf(%c)= 0x%x\n",
				rf == 0 ? 'A' : 'B', ग_लिखोval);
			अवरोध;
		शेष:
			chnlgroup = 0;
			ग_लिखोval = rtlphy->mcs_offset[chnlgroup][index +
				   (rf ? 8 : 0)] + ((index < 2) ?
				   घातerbase0[rf] : घातerbase1[rf]);
			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"RTK better performance, writeval rf(%c) = 0x%x\n",
				rf == 0 ? 'A' : 'B', ग_लिखोval);
			अवरोध;
		पूर्ण
		*(p_outग_लिखोval + rf) = ग_लिखोval;
	पूर्ण
पूर्ण

अटल व्योम _rtl92d_ग_लिखो_ofdm_घातer_reg(काष्ठा ieee80211_hw *hw,
					 u8 index, u32 *pvalue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	अटल u16 regoffset_a[6] = अणु
		RTXAGC_A_RATE18_06, RTXAGC_A_RATE54_24,
		RTXAGC_A_MCS03_MCS00, RTXAGC_A_MCS07_MCS04,
		RTXAGC_A_MCS11_MCS08, RTXAGC_A_MCS15_MCS12
	पूर्ण;
	अटल u16 regoffset_b[6] = अणु
		RTXAGC_B_RATE18_06, RTXAGC_B_RATE54_24,
		RTXAGC_B_MCS03_MCS00, RTXAGC_B_MCS07_MCS04,
		RTXAGC_B_MCS11_MCS08, RTXAGC_B_MCS15_MCS12
	पूर्ण;
	u8 i, rf, pwr_val[4];
	u32 ग_लिखोval;
	u16 regoffset;

	क्रम (rf = 0; rf < 2; rf++) अणु
		ग_लिखोval = pvalue[rf];
		क्रम (i = 0; i < 4; i++) अणु
			pwr_val[i] = (u8) ((ग_लिखोval & (0x7f <<
				     (i * 8))) >> (i * 8));
			अगर (pwr_val[i] > RF6052_MAX_TX_PWR)
				pwr_val[i] = RF6052_MAX_TX_PWR;
		पूर्ण
		ग_लिखोval = (pwr_val[3] << 24) | (pwr_val[2] << 16) |
			   (pwr_val[1] << 8) | pwr_val[0];
		अगर (rf == 0)
			regoffset = regoffset_a[index];
		अन्यथा
			regoffset = regoffset_b[index];
		rtl_set_bbreg(hw, regoffset, MASKDWORD, ग_लिखोval);
		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			"Set 0x%x = %08x\n", regoffset, ग_लिखोval);
		अगर (((get_rf_type(rtlphy) == RF_2T2R) &&
		    (regoffset == RTXAGC_A_MCS15_MCS12 ||
		    regoffset == RTXAGC_B_MCS15_MCS12)) ||
		    ((get_rf_type(rtlphy) != RF_2T2R) &&
		    (regoffset == RTXAGC_A_MCS07_MCS04 ||
		    regoffset == RTXAGC_B_MCS07_MCS04))) अणु
			ग_लिखोval = pwr_val[3];
			अगर (regoffset == RTXAGC_A_MCS15_MCS12 ||
			    regoffset == RTXAGC_A_MCS07_MCS04)
				regoffset = 0xc90;
			अगर (regoffset == RTXAGC_B_MCS15_MCS12 ||
			    regoffset == RTXAGC_B_MCS07_MCS04)
				regoffset = 0xc98;
			क्रम (i = 0; i < 3; i++) अणु
				अगर (i != 2)
					ग_लिखोval = (ग_लिखोval > 8) ?
						   (ग_लिखोval - 8) : 0;
				अन्यथा
					ग_लिखोval = (ग_लिखोval > 6) ?
						   (ग_लिखोval - 6) : 0;
				rtl_ग_लिखो_byte(rtlpriv, (u32) (regoffset + i),
					       (u8) ग_लिखोval);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम rtl92d_phy_rf6052_set_ofdm_txघातer(काष्ठा ieee80211_hw *hw,
					u8 *pघातerlevel, u8 channel)
अणु
	u32 ग_लिखोval[2], घातerbase0[2], घातerbase1[2];
	u8 index;

	_rtl92d_phy_get_घातer_base(hw, pघातerlevel, channel,
			&घातerbase0[0],	&घातerbase1[0]);
	क्रम (index = 0; index < 6; index++) अणु
		_rtl92d_get_txघातer_ग_लिखोval_by_regulatory(hw,
				channel, index,	&घातerbase0[0],
				&घातerbase1[0],	&ग_लिखोval[0]);
		_rtl92d_ग_लिखो_ofdm_घातer_reg(hw, index, &ग_लिखोval[0]);
	पूर्ण
पूर्ण

bool rtl92d_phy_enable_anotherphy(काष्ठा ieee80211_hw *hw, bool bmac0)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u8 u1bपंचांगp;
	u8 direct = bmac0 ? BIT(3) | BIT(2) : BIT(3);
	u8 mac_reg = bmac0 ? REG_MAC1 : REG_MAC0;
	u8 mac_on_bit = bmac0 ? MAC1_ON : MAC0_ON;
	bool bresult = true; /* true: need to enable BB/RF घातer */

	rtlhal->during_mac0init_radiob = false;
	rtlhal->during_mac1init_radioa = false;
	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "===>\n");
	/* MAC0 Need PHY1 load radio_b.txt . Driver use DBI to ग_लिखो. */
	u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, mac_reg);
	अगर (!(u1bपंचांगp & mac_on_bit)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "enable BB & RF\n");
		/* Enable BB and RF घातer */
		rtl92de_ग_लिखो_dword_dbi(hw, REG_SYS_ISO_CTRL,
			rtl92de_पढ़ो_dword_dbi(hw, REG_SYS_ISO_CTRL, direct) |
				BIT(29) | BIT(16) | BIT(17), direct);
	पूर्ण अन्यथा अणु
		/* We think अगर MAC1 is ON,then radio_a.txt
		 * and radio_b.txt has been load. */
		bresult = false;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "<===\n");
	वापस bresult;

पूर्ण

व्योम rtl92d_phy_घातerकरोwn_anotherphy(काष्ठा ieee80211_hw *hw, bool bmac0)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u8 u1bपंचांगp;
	u8 direct = bmac0 ? BIT(3) | BIT(2) : BIT(3);
	u8 mac_reg = bmac0 ? REG_MAC1 : REG_MAC0;
	u8 mac_on_bit = bmac0 ? MAC1_ON : MAC0_ON;

	rtlhal->during_mac0init_radiob = false;
	rtlhal->during_mac1init_radioa = false;
	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "====>\n");
	/* check MAC0 enable or not again now, अगर
	 * enabled, not घातer करोwn radio A. */
	u1bपंचांगp = rtl_पढ़ो_byte(rtlpriv, mac_reg);
	अगर (!(u1bपंचांगp & mac_on_bit)) अणु
		rtl_dbg(rtlpriv, COMP_INIT, DBG_LOUD, "power down\n");
		/* घातer करोwn RF radio A according to YuNan's advice. */
		rtl92de_ग_लिखो_dword_dbi(hw, RFPGA0_XA_LSSIPARAMETER,
					0x00000000, direct);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_RF, DBG_LOUD, "<====\n");
पूर्ण

bool rtl92d_phy_rf6052_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	bool rtstatus = true;
	काष्ठा rtl_hal *rtlhal = &(rtlpriv->rtlhal);
	u32 u4_regvalue = 0;
	u8 rfpath;
	काष्ठा bb_reg_def *pphyreg;
	bool mac1_initradioa_first = false, mac0_initradiob_first = false;
	bool need_pwrकरोwn_radioa = false, need_pwrकरोwn_radiob = false;
	bool true_bpath = false;

	अगर (rtlphy->rf_type == RF_1T1R)
		rtlphy->num_total_rfpath = 1;
	अन्यथा
		rtlphy->num_total_rfpath = 2;

	/* Single phy mode: use radio_a radio_b config path_A path_B */
	/* seperately by MAC0, and MAC1 needn't configure RF; */
	/* Dual PHY mode:MAC0 use radio_a config 1st phy path_A, */
	/* MAC1 use radio_b config 2nd PHY path_A. */
	/* DMDP,MAC0 on G band,MAC1 on A band. */
	अगर (rtlhal->macphymode == DUALMAC_DUALPHY) अणु
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G &&
		    rtlhal->पूर्णांकerfaceindex == 0) अणु
			/* MAC0 needs PHY1 load radio_b.txt.
			 * Driver use DBI to ग_लिखो. */
			अगर (rtl92d_phy_enable_anotherphy(hw, true)) अणु
				rtlphy->num_total_rfpath = 2;
				mac0_initradiob_first = true;
			पूर्ण अन्यथा अणु
				/* We think अगर MAC1 is ON,then radio_a.txt and
				 * radio_b.txt has been load. */
				वापस rtstatus;
			पूर्ण
		पूर्ण अन्यथा अगर (rtlhal->current_bandtype == BAND_ON_5G &&
			   rtlhal->पूर्णांकerfaceindex == 1) अणु
			/* MAC1 needs PHY0 load radio_a.txt.
			 * Driver use DBI to ग_लिखो. */
			अगर (rtl92d_phy_enable_anotherphy(hw, false)) अणु
				rtlphy->num_total_rfpath = 2;
				mac1_initradioa_first = true;
			पूर्ण अन्यथा अणु
				/* We think अगर MAC0 is ON,then radio_a.txt and
				 * radio_b.txt has been load. */
				वापस rtstatus;
			पूर्ण
		पूर्ण अन्यथा अगर (rtlhal->पूर्णांकerfaceindex == 1) अणु
			/* MAC0 enabled, only init radia B.   */
			true_bpath = true;
		पूर्ण
	पूर्ण

	क्रम (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) अणु
		/* Mac1 use PHY0 ग_लिखो */
		अगर (mac1_initradioa_first) अणु
			अगर (rfpath == RF90_PATH_A) अणु
				rtlhal->during_mac1init_radioa = true;
				need_pwrकरोwn_radioa = true;
			पूर्ण अन्यथा अगर (rfpath == RF90_PATH_B) अणु
				rtlhal->during_mac1init_radioa = false;
				mac1_initradioa_first = false;
				rfpath = RF90_PATH_A;
				true_bpath = true;
				rtlphy->num_total_rfpath = 1;
			पूर्ण
		पूर्ण अन्यथा अगर (mac0_initradiob_first) अणु
			/* Mac0 use PHY1 ग_लिखो */
			अगर (rfpath == RF90_PATH_A)
				rtlhal->during_mac0init_radiob = false;
			अगर (rfpath == RF90_PATH_B) अणु
				rtlhal->during_mac0init_radiob = true;
				mac0_initradiob_first = false;
				need_pwrकरोwn_radiob = true;
				rfpath = RF90_PATH_A;
				true_bpath = true;
				rtlphy->num_total_rfpath = 1;
			पूर्ण
		पूर्ण
		pphyreg = &rtlphy->phyreg_def[rfpath];
		चयन (rfpath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			u4_regvalue = rtl_get_bbreg(hw, pphyreg->rfपूर्णांकfs,
						    BRFSI_RFENV);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			u4_regvalue = rtl_get_bbreg(hw, pphyreg->rfपूर्णांकfs,
				BRFSI_RFENV << 16);
			अवरोध;
		पूर्ण
		rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfe, BRFSI_RFENV << 16, 0x1);
		udelay(1);
		rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfo, BRFSI_RFENV, 0x1);
		udelay(1);
		/* Set bit number of Address and Data क्रम RF रेजिस्टर */
		/* Set 1 to 4 bits क्रम 8255 */
		rtl_set_bbreg(hw, pphyreg->rfhssi_para2,
			      B3WIREADDRESSLENGTH, 0x0);
		udelay(1);
		/* Set 0 to 12  bits क्रम 8255 */
		rtl_set_bbreg(hw, pphyreg->rfhssi_para2, B3WIREDATALENGTH, 0x0);
		udelay(1);
		चयन (rfpath) अणु
		हाल RF90_PATH_A:
			अगर (true_bpath)
				rtstatus = rtl92d_phy_config_rf_with_headerfile(
						hw, radiob_txt,
						(क्रमागत radio_path)rfpath);
			अन्यथा
				rtstatus = rtl92d_phy_config_rf_with_headerfile(
					     hw, radioa_txt,
					     (क्रमागत radio_path)rfpath);
			अवरोध;
		हाल RF90_PATH_B:
			rtstatus =
			    rtl92d_phy_config_rf_with_headerfile(hw, radiob_txt,
						(क्रमागत radio_path) rfpath);
			अवरोध;
		हाल RF90_PATH_C:
			अवरोध;
		हाल RF90_PATH_D:
			अवरोध;
		पूर्ण
		चयन (rfpath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfs, BRFSI_RFENV,
				      u4_regvalue);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			rtl_set_bbreg(hw, pphyreg->rfपूर्णांकfs, BRFSI_RFENV << 16,
				      u4_regvalue);
			अवरोध;
		पूर्ण
		अगर (!rtstatus) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
				"Radio[%d] Fail!!\n", rfpath);
			जाओ phy_rf_cfg_fail;
		पूर्ण

	पूर्ण

	/* check MAC0 enable or not again, अगर enabled,
	 * not घातer करोwn radio A. */
	/* check MAC1 enable or not again, अगर enabled,
	 * not घातer करोwn radio B. */
	अगर (need_pwrकरोwn_radioa)
		rtl92d_phy_घातerकरोwn_anotherphy(hw, false);
	अन्यथा अगर (need_pwrकरोwn_radiob)
		rtl92d_phy_घातerकरोwn_anotherphy(hw, true);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "<---\n");
	वापस rtstatus;

phy_rf_cfg_fail:
	वापस rtstatus;
पूर्ण
