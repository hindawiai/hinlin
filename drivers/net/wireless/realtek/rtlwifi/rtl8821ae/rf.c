<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"

अटल bool _rtl8821ae_phy_rf6052_config_parafile(काष्ठा ieee80211_hw *hw);

व्योम rtl8821ae_phy_rf6052_set_bandwidth(काष्ठा ieee80211_hw *hw, u8 bandwidth)
अणु
	चयन (bandwidth) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, BIT(11)|BIT(10), 3);
		rtl_set_rfreg(hw, RF90_PATH_B, RF_CHNLBW, BIT(11)|BIT(10), 3);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, BIT(11)|BIT(10), 1);
		rtl_set_rfreg(hw, RF90_PATH_B, RF_CHNLBW, BIT(11)|BIT(10), 1);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_80:
		rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, BIT(11)|BIT(10), 0);
		rtl_set_rfreg(hw, RF90_PATH_B, RF_CHNLBW, BIT(11)|BIT(10), 0);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n", bandwidth);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl8821ae_phy_rf6052_set_cck_txघातer(काष्ठा ieee80211_hw *hw,
					  u8 *pघातerlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 tx_agc[2] = अणु0, 0पूर्ण, पंचांगpval;
	bool turbo_scanoff = false;
	u8 idx1, idx2;
	u8 *ptr;
	u8 direction;
	u32 pwrtrac_value;

	अगर (rtlefuse->eeprom_regulatory != 0)
		turbo_scanoff = true;

	अगर (mac->act_scanning) अणु
		tx_agc[RF90_PATH_A] = 0x3f3f3f3f;
		tx_agc[RF90_PATH_B] = 0x3f3f3f3f;

		अगर (turbo_scanoff) अणु
			क्रम (idx1 = RF90_PATH_A;
				idx1 <= RF90_PATH_B;
				idx1++) अणु
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
			पंचांगpval =
			    (rtlphy->mcs_txpwrlevel_origoffset[0][6]) +
			    (rtlphy->mcs_txpwrlevel_origoffset[0][7] <<
			     8);
			tx_agc[RF90_PATH_A] += पंचांगpval;

			पंचांगpval = (rtlphy->mcs_txpwrlevel_origoffset[0][14]) +
			    (rtlphy->mcs_txpwrlevel_origoffset[0][15] <<
			     24);
			tx_agc[RF90_PATH_B] += पंचांगpval;
		पूर्ण
	पूर्ण

	क्रम (idx1 = RF90_PATH_A; idx1 <= RF90_PATH_B; idx1++) अणु
		ptr = (u8 *)(&tx_agc[idx1]);
		क्रम (idx2 = 0; idx2 < 4; idx2++) अणु
			अगर (*ptr > RF6052_MAX_TX_PWR)
				*ptr = RF6052_MAX_TX_PWR;
			ptr++;
		पूर्ण
	पूर्ण
	rtl8821ae_dm_txघातer_track_adjust(hw, 1, &direction, &pwrtrac_value);
	अगर (direction == 1) अणु
		tx_agc[0] += pwrtrac_value;
		tx_agc[1] += pwrtrac_value;
	पूर्ण अन्यथा अगर (direction == 2) अणु
		tx_agc[0] -= pwrtrac_value;
		tx_agc[1] -= pwrtrac_value;
	पूर्ण
	पंचांगpval = tx_agc[RF90_PATH_A];
	rtl_set_bbreg(hw, RTXAGC_A_CCK11_CCK1, MASKDWORD, पंचांगpval);

	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 1~11M (rf-A) = 0x%x (reg 0x%x)\n", पंचांगpval,
		 RTXAGC_A_CCK11_CCK1);

	पंचांगpval = tx_agc[RF90_PATH_B];
	rtl_set_bbreg(hw, RTXAGC_B_CCK11_CCK1, MASKDWORD, पंचांगpval);

	RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
		"CCK PWR 11M (rf-B) = 0x%x (reg 0x%x)\n", पंचांगpval,
		 RTXAGC_B_CCK11_CCK1);
पूर्ण

अटल व्योम rtl8821ae_phy_get_घातer_base(काष्ठा ieee80211_hw *hw,
					 u8 *pघातerlevel_ofdm,
					 u8 *pघातerlevel_bw20,
					 u8 *pघातerlevel_bw40, u8 channel,
					 u32 *ofdmbase, u32 *mcsbase)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 घातerbase0, घातerbase1;
	u8 i, घातerlevel[2];

	क्रम (i = 0; i < 2; i++) अणु
		घातerbase0 = pघातerlevel_ofdm[i];

		घातerbase0 = (घातerbase0 << 24) | (घातerbase0 << 16) |
		    (घातerbase0 << 8) | घातerbase0;
		*(ofdmbase + i) = घातerbase0;
		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			" [OFDM power base index rf(%c) = 0x%x]\n",
			 ((i == 0) ? 'A' : 'B'), *(ofdmbase + i));
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20)
			घातerlevel[i] = pघातerlevel_bw20[i];
		अन्यथा
			घातerlevel[i] = pघातerlevel_bw40[i];

		घातerbase1 = घातerlevel[i];
		घातerbase1 = (घातerbase1 << 24) |
		    (घातerbase1 << 16) | (घातerbase1 << 8) | घातerbase1;

		*(mcsbase + i) = घातerbase1;

		RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
			" [MCS power base index rf(%c) = 0x%x]\n",
			 ((i == 0) ? 'A' : 'B'), *(mcsbase + i));
	पूर्ण
पूर्ण

अटल व्योम get_txघातer_ग_लिखोval_by_regulatory(काष्ठा ieee80211_hw *hw,
					       u8 channel, u8 index,
					       u32 *घातerbase0,
					       u32 *घातerbase1,
					       u32 *p_outग_लिखोval)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 i, chnlgroup = 0, pwr_dअगरf_limit[4], pwr_dअगरf = 0, customer_pwr_dअगरf;
	u32 ग_लिखोval, customer_limit, rf;

	क्रम (rf = 0; rf < 2; rf++) अणु
		चयन (rtlefuse->eeprom_regulatory) अणु
		हाल 0:
			chnlgroup = 0;

			ग_लिखोval =
			    rtlphy->mcs_txpwrlevel_origoffset[chnlgroup][index +
							(rf ? 8 : 0)]
			    + ((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);

			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"RTK better performance, writeval(%c) = 0x%x\n",
				 ((rf == 0) ? 'A' : 'B'), ग_लिखोval);
			अवरोध;
		हाल 1:
			अगर (rtlphy->pwrgroup_cnt == 1) अणु
				chnlgroup = 0;
			पूर्ण अन्यथा अणु
				अगर (channel < 3)
					chnlgroup = 0;
				अन्यथा अगर (channel < 6)
					chnlgroup = 1;
				अन्यथा अगर (channel < 9)
					chnlgroup = 2;
				अन्यथा अगर (channel < 12)
					chnlgroup = 3;
				अन्यथा अगर (channel < 14)
					chnlgroup = 4;
				अन्यथा अगर (channel == 14)
					chnlgroup = 5;
			पूर्ण

			ग_लिखोval =
			    rtlphy->mcs_txpwrlevel_origoffset[chnlgroup]
			    [index + (rf ? 8 : 0)] + ((index < 2) ?
						      घातerbase0[rf] :
						      घातerbase1[rf]);

			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"Realtek regulatory, 20MHz, writeval(%c) = 0x%x\n",
				 ((rf == 0) ? 'A' : 'B'), ग_लिखोval);

			अवरोध;
		हाल 2:
			ग_लिखोval =
			    ((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);

			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"Better regulatory, writeval(%c) = 0x%x\n",
				 ((rf == 0) ? 'A' : 'B'), ग_लिखोval);
			अवरोध;
		हाल 3:
			chnlgroup = 0;

			अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
				RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
					"customer's limit, 40MHz rf(%c) = 0x%x\n",
					 ((rf == 0) ? 'A' : 'B'),
					 rtlefuse->pwrgroup_ht40[rf][channel -
								     1]);
			पूर्ण अन्यथा अणु
				RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
					"customer's limit, 20MHz rf(%c) = 0x%x\n",
					 ((rf == 0) ? 'A' : 'B'),
					 rtlefuse->pwrgroup_ht20[rf][channel -
								     1]);
			पूर्ण

			अगर (index < 2)
				pwr_dअगरf = rtlefuse->txpwr_legacyhtdअगरf[rf][channel-1];
			अन्यथा अगर (rtlphy->current_chan_bw ==  HT_CHANNEL_WIDTH_20)
				pwr_dअगरf =
				  rtlefuse->txpwr_ht20dअगरf[rf][channel-1];

			अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40)
				customer_pwr_dअगरf =
				  rtlefuse->pwrgroup_ht40[rf][channel-1];
			अन्यथा
				customer_pwr_dअगरf =
				  rtlefuse->pwrgroup_ht20[rf][channel-1];

			अगर (pwr_dअगरf > customer_pwr_dअगरf)
				pwr_dअगरf = 0;
			अन्यथा
				pwr_dअगरf = customer_pwr_dअगरf - pwr_dअगरf;

			क्रम (i = 0; i < 4; i++) अणु
				pwr_dअगरf_limit[i] =
				    (u8)((rtlphy->mcs_txpwrlevel_origoffset
				    [chnlgroup][index + (rf ? 8 : 0)] &
				    (0x7f << (i * 8))) >> (i * 8));

				अगर (pwr_dअगरf_limit[i] > pwr_dअगरf)
					pwr_dअगरf_limit[i] = pwr_dअगरf;
			पूर्ण

			customer_limit = (pwr_dअगरf_limit[3] << 24) |
			    (pwr_dअगरf_limit[2] << 16) |
			    (pwr_dअगरf_limit[1] << 8) | (pwr_dअगरf_limit[0]);

			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"Customer's limit rf(%c) = 0x%x\n",
				 ((rf == 0) ? 'A' : 'B'), customer_limit);

			ग_लिखोval = customer_limit +
			    ((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);

			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"Customer, writeval rf(%c)= 0x%x\n",
				 ((rf == 0) ? 'A' : 'B'), ग_लिखोval);
			अवरोध;
		शेष:
			chnlgroup = 0;
			ग_लिखोval =
			    rtlphy->mcs_txpwrlevel_origoffset[chnlgroup]
			    [index + (rf ? 8 : 0)]
			    + ((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);

			RTPRINT(rtlpriv, FPHY, PHY_TXPWR,
				"RTK better performance, writeval rf(%c) = 0x%x\n",
				 ((rf == 0) ? 'A' : 'B'), ग_लिखोval);
			अवरोध;
		पूर्ण

		अगर (rtlpriv->dm.dynamic_txhighघातer_lvl == TXHIGHPWRLEVEL_BT1)
			ग_लिखोval = ग_लिखोval - 0x06060606;
		अन्यथा अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
			 TXHIGHPWRLEVEL_BT2)
			ग_लिखोval = ग_लिखोval - 0x0c0c0c0c;
		*(p_outग_लिखोval + rf) = ग_लिखोval;
	पूर्ण
पूर्ण

अटल व्योम _rtl8821ae_ग_लिखो_ofdm_घातer_reg(काष्ठा ieee80211_hw *hw,
					    u8 index, u32 *pvalue)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u16 regoffset_a[6] = अणु
		RTXAGC_A_OFDM18_OFDM6, RTXAGC_A_OFDM54_OFDM24,
		RTXAGC_A_MCS03_MCS00, RTXAGC_A_MCS07_MCS04,
		RTXAGC_A_MCS11_MCS08, RTXAGC_A_MCS15_MCS12
	पूर्ण;
	u16 regoffset_b[6] = अणु
		RTXAGC_B_OFDM18_OFDM6, RTXAGC_B_OFDM54_OFDM24,
		RTXAGC_B_MCS03_MCS00, RTXAGC_B_MCS07_MCS04,
		RTXAGC_B_MCS11_MCS08, RTXAGC_B_MCS15_MCS12
	पूर्ण;
	u8 i, rf, pwr_val[4];
	u32 ग_लिखोval;
	u16 regoffset;

	क्रम (rf = 0; rf < 2; rf++) अणु
		ग_लिखोval = pvalue[rf];
		क्रम (i = 0; i < 4; i++) अणु
			pwr_val[i] = (u8)((ग_लिखोval & (0x7f <<
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
	पूर्ण
पूर्ण

व्योम rtl8821ae_phy_rf6052_set_ofdm_txघातer(काष्ठा ieee80211_hw *hw,
					   u8 *pघातerlevel_ofdm,
					   u8 *pघातerlevel_bw20,
					   u8 *pघातerlevel_bw40,
					   u8 channel)
अणु
	u32 ग_लिखोval[2], घातerbase0[2], घातerbase1[2];
	u8 index;
	u8 direction;
	u32 pwrtrac_value;

	rtl8821ae_phy_get_घातer_base(hw, pघातerlevel_ofdm,
				     pघातerlevel_bw20,
				     pघातerlevel_bw40,
				     channel,
				     &घातerbase0[0],
				     &घातerbase1[0]);

	rtl8821ae_dm_txघातer_track_adjust(hw, 1, &direction, &pwrtrac_value);

	क्रम (index = 0; index < 6; index++) अणु
		get_txघातer_ग_लिखोval_by_regulatory(hw, channel, index,
						   &घातerbase0[0],
						   &घातerbase1[0],
						   &ग_लिखोval[0]);
		अगर (direction == 1) अणु
			ग_लिखोval[0] += pwrtrac_value;
			ग_लिखोval[1] += pwrtrac_value;
		पूर्ण अन्यथा अगर (direction == 2) अणु
			ग_लिखोval[0] -= pwrtrac_value;
			ग_लिखोval[1] -= pwrtrac_value;
		पूर्ण
		_rtl8821ae_ग_लिखो_ofdm_घातer_reg(hw, index, &ग_लिखोval[0]);
	पूर्ण
पूर्ण

bool rtl8821ae_phy_rf6052_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;

	अगर (rtlphy->rf_type == RF_1T1R)
		rtlphy->num_total_rfpath = 1;
	अन्यथा
		rtlphy->num_total_rfpath = 2;

	वापस _rtl8821ae_phy_rf6052_config_parafile(hw);
पूर्ण

अटल bool _rtl8821ae_phy_rf6052_config_parafile(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 rfpath;
	bool rtstatus = true;

	क्रम (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) अणु
		चयन (rfpath) अणु
		हाल RF90_PATH_A: अणु
			अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
				rtstatus =
				  rtl8812ae_phy_config_rf_with_headerfile(hw,
							(क्रमागत radio_path)rfpath);
			अन्यथा
				rtstatus =
				  rtl8821ae_phy_config_rf_with_headerfile(hw,
							(क्रमागत radio_path)rfpath);
			अवरोध;
			पूर्ण
		हाल RF90_PATH_B:
			अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE)
				rtstatus =
				  rtl8812ae_phy_config_rf_with_headerfile(hw,
							(क्रमागत radio_path)rfpath);
			अन्यथा
				rtstatus =
				  rtl8821ae_phy_config_rf_with_headerfile(hw,
							(क्रमागत radio_path)rfpath);
			अवरोध;
		हाल RF90_PATH_C:
			अवरोध;
		हाल RF90_PATH_D:
			अवरोध;
		पूर्ण

		अगर (!rtstatus) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE,
				"Radio[%d] Fail!!\n", rfpath);
			वापस false;
		पूर्ण
	पूर्ण

	/*put arrays in dm.c*/
	rtl_dbg(rtlpriv, COMP_INIT, DBG_TRACE, "\n");
	वापस rtstatus;
पूर्ण
