<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "rf.h"
#समावेश "dm.h"


अटल व्योम _rtl92s_get_घातerbase(काष्ठा ieee80211_hw *hw, u8 *p_pwrlevel,
				  u8 chnl, u32 *ofdmbase, u32 *mcsbase,
				  u8 *p_final_pwridx)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 pwrbase0, pwrbase1;
	u8 legacy_pwrdअगरf = 0, ht20_pwrdअगरf = 0;
	u8 i, pwrlevel[4];

	क्रम (i = 0; i < 2; i++)
		pwrlevel[i] = p_pwrlevel[i];

	/* We only care about the path A क्रम legacy. */
	अगर (rtlefuse->eeprom_version < 2) अणु
		pwrbase0 = pwrlevel[0] + (rtlefuse->legacy_ht_txघातerdअगरf & 0xf);
	पूर्ण अन्यथा अणु
		legacy_pwrdअगरf = rtlefuse->txpwr_legacyhtdअगरf
						[RF90_PATH_A][chnl - 1];

		/* For legacy OFDM, tx pwr always > HT OFDM pwr.
		 * We करो not care Path B
		 * legacy OFDM pwr dअगरf. NO BB रेजिस्टर
		 * to notअगरy HW. */
		pwrbase0 = pwrlevel[0] + legacy_pwrdअगरf;
	पूर्ण

	pwrbase0 = (pwrbase0 << 24) | (pwrbase0 << 16) | (pwrbase0 << 8) |
		    pwrbase0;
	*ofdmbase = pwrbase0;

	/* MCS rates */
	अगर (rtlefuse->eeprom_version >= 2) अणु
		/* Check HT20 to HT40 dअगरf	*/
		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20) अणु
			क्रम (i = 0; i < 2; i++) अणु
				/* rf-A, rf-B */
				/* HT 20<->40 pwr dअगरf */
				ht20_pwrdअगरf = rtlefuse->txpwr_ht20dअगरf
							[i][chnl - 1];

				अगर (ht20_pwrdअगरf < 8) /* 0~+7 */
					pwrlevel[i] += ht20_pwrdअगरf;
				अन्यथा /* index8-15=-8~-1 */
					pwrlevel[i] -= (16 - ht20_pwrdअगरf);
			पूर्ण
		पूर्ण
	पूर्ण

	/* use index of rf-A */
	pwrbase1 = pwrlevel[0];
	pwrbase1 = (pwrbase1 << 24) | (pwrbase1 << 16) | (pwrbase1 << 8) |
				pwrbase1;
	*mcsbase = pwrbase1;

	/* The following is क्रम Antenna
	 * dअगरf from Ant-B to Ant-A */
	p_final_pwridx[0] = pwrlevel[0];
	p_final_pwridx[1] = pwrlevel[1];

	चयन (rtlefuse->eeprom_regulatory) अणु
	हाल 3:
		/* The following is क्रम calculation
		 * of the घातer dअगरf क्रम Ant-B to Ant-A. */
		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
			p_final_pwridx[0] += rtlefuse->pwrgroup_ht40
						[RF90_PATH_A][
						chnl - 1];
			p_final_pwridx[1] += rtlefuse->pwrgroup_ht40
						[RF90_PATH_B][
						chnl - 1];
		पूर्ण अन्यथा अणु
			p_final_pwridx[0] += rtlefuse->pwrgroup_ht20
						[RF90_PATH_A][
						chnl - 1];
			p_final_pwridx[1] += rtlefuse->pwrgroup_ht20
						[RF90_PATH_B][
						chnl - 1];
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"40MHz finalpwr_idx (A / B) = 0x%x / 0x%x\n",
			p_final_pwridx[0], p_final_pwridx[1]);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"20MHz finalpwr_idx (A / B) = 0x%x / 0x%x\n",
			p_final_pwridx[0], p_final_pwridx[1]);
	पूर्ण
पूर्ण

अटल व्योम _rtl92s_set_antennadअगरf(काष्ठा ieee80211_hw *hw,
				    u8 *p_final_pwridx)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	s8 ant_pwr_dअगरf = 0;
	u32	u4reg_val = 0;

	अगर (rtlphy->rf_type == RF_2T2R) अणु
		ant_pwr_dअगरf = p_final_pwridx[1] - p_final_pwridx[0];

		/* range is from 7~-8,
		 * index = 0x0~0xf */
		अगर (ant_pwr_dअगरf > 7)
			ant_pwr_dअगरf = 7;
		अगर (ant_pwr_dअगरf < -8)
			ant_pwr_dअगरf = -8;

		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Antenna Diff from RF-B to RF-A = %d (0x%x)\n",
			ant_pwr_dअगरf, ant_pwr_dअगरf & 0xf);

		ant_pwr_dअगरf &= 0xf;
	पूर्ण

	/* Antenna TX घातer dअगरference */
	rtlefuse->antenna_txpwdअगरf[2] = 0;/* RF-D, करोn't care */
	rtlefuse->antenna_txpwdअगरf[1] = 0;/* RF-C, करोn't care */
	rtlefuse->antenna_txpwdअगरf[0] = (u8)(ant_pwr_dअगरf);	/* RF-B */

	u4reg_val = rtlefuse->antenna_txpwdअगरf[2] << 8 |
				rtlefuse->antenna_txpwdअगरf[1] << 4 |
				rtlefuse->antenna_txpwdअगरf[0];

	rtl_set_bbreg(hw, RFPGA0_TXGAINSTAGE, (BXBTXAGC | BXCTXAGC | BXDTXAGC),
		      u4reg_val);

	rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD, "Write BCD-Diff(0x%x) = 0x%x\n",
		RFPGA0_TXGAINSTAGE, u4reg_val);
पूर्ण

अटल व्योम _rtl92s_get_txघातer_ग_लिखोval_byregulatory(काष्ठा ieee80211_hw *hw,
						      u8 chnl, u8 index,
						      u32 pwrbase0,
						      u32 pwrbase1,
						      u32 *p_outग_लिखो_val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 i, chnlgroup, pwrdअगरf_limit[4];
	u32 ग_लिखोval, customer_limit;

	/* Index 0 & 1= legacy OFDM, 2-5=HT_MCS rate */
	चयन (rtlefuse->eeprom_regulatory) अणु
	हाल 0:
		/* Realtek better perक्रमmance increase घातer dअगरf
		 * defined by Realtek क्रम large घातer */
		chnlgroup = 0;

		ग_लिखोval = rtlphy->mcs_offset[chnlgroup][index] +
				((index < 2) ? pwrbase0 : pwrbase1);

		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"RTK better performance, writeval = 0x%x\n", ग_लिखोval);
		अवरोध;
	हाल 1:
		/* Realtek regulatory increase घातer dअगरf defined
		 * by Realtek क्रम regulatory */
		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
			ग_लिखोval = ((index < 2) ? pwrbase0 : pwrbase1);

			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"Realtek regulatory, 40MHz, writeval = 0x%x\n",
				ग_लिखोval);
		पूर्ण अन्यथा अणु
			chnlgroup = 0;

			अगर (rtlphy->pwrgroup_cnt >= 3) अणु
				अगर (chnl <= 3)
					chnlgroup = 0;
				अन्यथा अगर (chnl >= 4 && chnl <= 8)
					chnlgroup = 1;
				अन्यथा अगर (chnl > 8)
					chnlgroup = 2;
				अगर (rtlphy->pwrgroup_cnt == 4)
					chnlgroup++;
			पूर्ण

			ग_लिखोval = rtlphy->mcs_offset[chnlgroup][index]
					+ ((index < 2) ?
					pwrbase0 : pwrbase1);

			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"Realtek regulatory, 20MHz, writeval = 0x%x\n",
				ग_लिखोval);
		पूर्ण
		अवरोध;
	हाल 2:
		/* Better regulatory करोn't increase any घातer dअगरf */
		ग_लिखोval = ((index < 2) ? pwrbase0 : pwrbase1);
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Better regulatory, writeval = 0x%x\n", ग_लिखोval);
		अवरोध;
	हाल 3:
		/* Customer defined घातer dअगरf. increase घातer dअगरf
		  defined by customer. */
		chnlgroup = 0;

		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"customer's limit, 40MHz = 0x%x\n",
				rtlefuse->pwrgroup_ht40
				[RF90_PATH_A][chnl - 1]);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"customer's limit, 20MHz = 0x%x\n",
				rtlefuse->pwrgroup_ht20
				[RF90_PATH_A][chnl - 1]);
		पूर्ण

		क्रम (i = 0; i < 4; i++) अणु
			pwrdअगरf_limit[i] = (u8)((rtlphy->mcs_offset
				[chnlgroup][index] & (0x7f << (i * 8)))
				>> (i * 8));

			अगर (rtlphy->current_chan_bw ==
			    HT_CHANNEL_WIDTH_20_40) अणु
				अगर (pwrdअगरf_limit[i] >
				    rtlefuse->pwrgroup_ht40
				    [RF90_PATH_A][chnl - 1]) अणु
					pwrdअगरf_limit[i] =
					  rtlefuse->pwrgroup_ht40
					  [RF90_PATH_A][chnl - 1];
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (pwrdअगरf_limit[i] >
				    rtlefuse->pwrgroup_ht20
				    [RF90_PATH_A][chnl - 1]) अणु
					pwrdअगरf_limit[i] =
					    rtlefuse->pwrgroup_ht20
					    [RF90_PATH_A][chnl - 1];
				पूर्ण
			पूर्ण
		पूर्ण

		customer_limit = (pwrdअगरf_limit[3] << 24) |
				(pwrdअगरf_limit[2] << 16) |
				(pwrdअगरf_limit[1] << 8) |
				(pwrdअगरf_limit[0]);
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Customer's limit = 0x%x\n", customer_limit);

		ग_लिखोval = customer_limit + ((index < 2) ?
					     pwrbase0 : pwrbase1);
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"Customer, writeval = 0x%x\n", ग_लिखोval);
		अवरोध;
	शेष:
		chnlgroup = 0;
		ग_लिखोval = rtlphy->mcs_offset[chnlgroup][index] +
				((index < 2) ? pwrbase0 : pwrbase1);
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"RTK better performance, writeval = 0x%x\n", ग_लिखोval);
		अवरोध;
	पूर्ण

	अगर (rtlpriv->dm.dynamic_txhighघातer_lvl == TX_HIGH_PWR_LEVEL_LEVEL1)
		ग_लिखोval = 0x10101010;
	अन्यथा अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
		 TX_HIGH_PWR_LEVEL_LEVEL2)
		ग_लिखोval = 0x0;

	*p_outग_लिखो_val = ग_लिखोval;

पूर्ण

अटल व्योम _rtl92s_ग_लिखो_ofdm_घातerreg(काष्ठा ieee80211_hw *hw,
					u8 index, u32 val)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u16 regoffset[6] = अणु0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1cपूर्ण;
	u8 i, rfa_pwr[4];
	u8 rfa_lower_bound = 0, rfa_upper_bound = 0, rf_pwr_dअगरf = 0;
	u32 ग_लिखोval = val;

	/* If path A and Path B coexist, we must limit Path A tx घातer.
	 * Protect Path B pwr over or under flow. We need to calculate
	 * upper and lower bound of path A tx घातer. */
	अगर (rtlphy->rf_type == RF_2T2R) अणु
		rf_pwr_dअगरf = rtlefuse->antenna_txpwdअगरf[0];

		/* Dअगरf=-8~-1 */
		अगर (rf_pwr_dअगरf >= 8) अणु
			/* Prevent underflow!! */
			rfa_lower_bound = 0x10 - rf_pwr_dअगरf;
		/* अगर (rf_pwr_dअगरf >= 0) Dअगरf = 0-7 */
		पूर्ण अन्यथा अणु
			rfa_upper_bound = RF6052_MAX_TX_PWR - rf_pwr_dअगरf;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		rfa_pwr[i] = (u8)((ग_लिखोval & (0x7f << (i * 8))) >> (i * 8));
		अगर (rfa_pwr[i]  > RF6052_MAX_TX_PWR)
			rfa_pwr[i]  = RF6052_MAX_TX_PWR;

		/* If path A and Path B coexist, we must limit Path A tx घातer.
		 * Protect Path B pwr over or under flow. We need to calculate
		 * upper and lower bound of path A tx घातer. */
		अगर (rtlphy->rf_type == RF_2T2R) अणु
			/* Dअगरf=-8~-1 */
			अगर (rf_pwr_dअगरf >= 8) अणु
				/* Prevent underflow!! */
				अगर (rfa_pwr[i] < rfa_lower_bound)
					rfa_pwr[i] = rfa_lower_bound;
			/* Dअगरf = 0-7 */
			पूर्ण अन्यथा अगर (rf_pwr_dअगरf >= 1) अणु
				/* Prevent overflow */
				अगर (rfa_pwr[i] > rfa_upper_bound)
					rfa_pwr[i] = rfa_upper_bound;
			पूर्ण
		पूर्ण

	पूर्ण

	ग_लिखोval = (rfa_pwr[3] << 24) | (rfa_pwr[2] << 16) | (rfa_pwr[1] << 8) |
				rfa_pwr[0];

	rtl_set_bbreg(hw, regoffset[index], 0x7f7f7f7f, ग_लिखोval);
पूर्ण

व्योम rtl92s_phy_rf6052_set_ofdmtxघातer(काष्ठा ieee80211_hw *hw,
				       u8 *p_pwrlevel, u8 chnl)
अणु
	u32 ग_लिखोval, pwrbase0, pwrbase1;
	u8 index = 0;
	u8 finalpwr_idx[4];

	_rtl92s_get_घातerbase(hw, p_pwrlevel, chnl, &pwrbase0, &pwrbase1,
			&finalpwr_idx[0]);
	_rtl92s_set_antennadअगरf(hw, &finalpwr_idx[0]);

	क्रम (index = 0; index < 6; index++) अणु
		_rtl92s_get_txघातer_ग_लिखोval_byregulatory(hw, chnl, index,
				pwrbase0, pwrbase1, &ग_लिखोval);

		_rtl92s_ग_लिखो_ofdm_घातerreg(hw, index, ग_लिखोval);
	पूर्ण
पूर्ण

व्योम rtl92s_phy_rf6052_set_ccktxघातer(काष्ठा ieee80211_hw *hw, u8 pwrlevel)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u32 txagc = 0;
	bool करोnt_inc_cck_or_turboscanoff = false;

	अगर (((rtlefuse->eeprom_version >= 2) &&
	      (rtlefuse->txpwr_safetyflag == 1)) ||
	      ((rtlefuse->eeprom_version >= 2) &&
	      (rtlefuse->eeprom_regulatory != 0)))
		करोnt_inc_cck_or_turboscanoff = true;

	अगर (mac->act_scanning) अणु
		txagc = 0x3f;
		अगर (करोnt_inc_cck_or_turboscanoff)
			txagc = pwrlevel;
	पूर्ण अन्यथा अणु
		txagc = pwrlevel;

		अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
		    TX_HIGH_PWR_LEVEL_LEVEL1)
			txagc = 0x10;
		अन्यथा अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
			TX_HIGH_PWR_LEVEL_LEVEL2)
			txagc = 0x0;
	पूर्ण

	अगर (txagc > RF6052_MAX_TX_PWR)
		txagc = RF6052_MAX_TX_PWR;

	rtl_set_bbreg(hw, RTXAGC_CCK_MCS32, BTX_AGCRATECCK, txagc);

पूर्ण

bool rtl92s_phy_rf6052_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u32 u4reg_val = 0;
	u8 rfpath;
	bool rtstatus = true;
	काष्ठा bb_reg_def *pphyreg;

	/* Initialize RF */
	क्रम (rfpath = 0; rfpath < rtlphy->num_total_rfpath; rfpath++) अणु

		pphyreg = &rtlphy->phyreg_def[rfpath];

		/* Store original RFENV control type */
		चयन (rfpath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			u4reg_val = rtl92s_phy_query_bb_reg(hw,
							    pphyreg->rfपूर्णांकfs,
							    BRFSI_RFENV);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			u4reg_val = rtl92s_phy_query_bb_reg(hw,
							    pphyreg->rfपूर्णांकfs,
							    BRFSI_RFENV << 16);
			अवरोध;
		पूर्ण

		/* Set RF_ENV enable */
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfपूर्णांकfe,
				      BRFSI_RFENV << 16, 0x1);

		/* Set RF_ENV output high */
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfपूर्णांकfo, BRFSI_RFENV, 0x1);

		/* Set bit number of Address and Data क्रम RF रेजिस्टर */
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfhssi_para2,
				B3WIRE_ADDRESSLENGTH, 0x0);
		rtl92s_phy_set_bb_reg(hw, pphyreg->rfhssi_para2,
				B3WIRE_DATALENGTH, 0x0);

		/* Initialize RF fom connfiguration file */
		चयन (rfpath) अणु
		हाल RF90_PATH_A:
			rtstatus = rtl92s_phy_config_rf(hw,
						(क्रमागत radio_path)rfpath);
			अवरोध;
		हाल RF90_PATH_B:
			rtstatus = rtl92s_phy_config_rf(hw,
						(क्रमागत radio_path)rfpath);
			अवरोध;
		हाल RF90_PATH_C:
			अवरोध;
		हाल RF90_PATH_D:
			अवरोध;
		पूर्ण

		/* Restore RFENV control type */
		चयन (rfpath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			rtl92s_phy_set_bb_reg(hw, pphyreg->rfपूर्णांकfs, BRFSI_RFENV,
					      u4reg_val);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			rtl92s_phy_set_bb_reg(hw, pphyreg->rfपूर्णांकfs,
					      BRFSI_RFENV << 16,
					      u4reg_val);
			अवरोध;
		पूर्ण

		अगर (!rtstatus) अणु
			pr_err("Radio[%d] Fail!!\n", rfpath);
			जाओ fail;
		पूर्ण

	पूर्ण

	वापस rtstatus;

fail:
	वापस rtstatus;
पूर्ण

व्योम rtl92s_phy_rf6052_set_bandwidth(काष्ठा ieee80211_hw *hw, u8 bandwidth)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	चयन (bandwidth) अणु
	हाल HT_CHANNEL_WIDTH_20:
		rtlphy->rfreg_chnlval[0] = ((rtlphy->rfreg_chnlval[0] &
					   0xfffff3ff) | 0x0400);
		rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, RFREG_OFFSET_MASK,
					rtlphy->rfreg_chnlval[0]);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_20_40:
		rtlphy->rfreg_chnlval[0] = ((rtlphy->rfreg_chnlval[0] &
					    0xfffff3ff));
		rtl_set_rfreg(hw, RF90_PATH_A, RF_CHNLBW, RFREG_OFFSET_MASK,
					rtlphy->rfreg_chnlval[0]);
		अवरोध;
	शेष:
		pr_err("unknown bandwidth: %#X\n", bandwidth);
		अवरोध;
	पूर्ण
पूर्ण
