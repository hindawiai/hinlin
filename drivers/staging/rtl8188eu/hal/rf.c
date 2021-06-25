<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <phy.h>
#समावेश <rf.h>
#समावेश <rtl8188e_hal.h>

व्योम rtl88eu_phy_rf6052_set_bandwidth(काष्ठा adapter *adapt,
				      क्रमागत ht_channel_width bandwidth)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;

	चयन (bandwidth) अणु
	हाल HT_CHANNEL_WIDTH_20:
		hal_data->RfRegChnlVal[0] = ((hal_data->RfRegChnlVal[0] &
					      0xfffff3ff) | BIT(10) | BIT(11));
		phy_set_rf_reg(adapt, RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask,
			       hal_data->RfRegChnlVal[0]);
		अवरोध;
	हाल HT_CHANNEL_WIDTH_40:
		hal_data->RfRegChnlVal[0] = ((hal_data->RfRegChnlVal[0] &
					      0xfffff3ff) | BIT(10));
		phy_set_rf_reg(adapt, RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask,
			       hal_data->RfRegChnlVal[0]);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl88eu_phy_rf6052_set_cck_txघातer(काष्ठा adapter *adapt, u8 *घातerlevel)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	काष्ठा dm_priv *pdmpriv = &hal_data->dmpriv;
	काष्ठा mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	u32 tx_agc[2] = अणु0, 0पूर्ण, पंचांगpval = 0, pwrtrac_value;
	u8 idx1, idx2;
	u8 *ptr;
	u8 direction;

	अगर (pmlmeext->sitesurvey_res.state == SCAN_PROCESS) अणु
		tx_agc[RF_PATH_A] = 0x3f3f3f3f;
		tx_agc[RF_PATH_B] = 0x3f3f3f3f;
		क्रम (idx1 = RF_PATH_A; idx1 <= RF_PATH_B; idx1++) अणु
			tx_agc[idx1] = घातerlevel[idx1] |
				      (घातerlevel[idx1] << 8) |
				      (घातerlevel[idx1] << 16) |
				      (घातerlevel[idx1] << 24);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pdmpriv->DynamicTxHighPowerLvl == TxHighPwrLevel_Level1) अणु
			tx_agc[RF_PATH_A] = 0x10101010;
			tx_agc[RF_PATH_B] = 0x10101010;
		पूर्ण अन्यथा अगर (pdmpriv->DynamicTxHighPowerLvl == TxHighPwrLevel_Level2) अणु
			tx_agc[RF_PATH_A] = 0x00000000;
			tx_agc[RF_PATH_B] = 0x00000000;
		पूर्ण अन्यथा अणु
			क्रम (idx1 = RF_PATH_A; idx1 <= RF_PATH_B; idx1++) अणु
				tx_agc[idx1] = घातerlevel[idx1] |
					       (घातerlevel[idx1] << 8) |
					       (घातerlevel[idx1] << 16) |
					       (घातerlevel[idx1] << 24);
			पूर्ण
			अगर (hal_data->EEPROMRegulatory == 0) अणु
				पंचांगpval = hal_data->MCSTxPowerLevelOriginalOffset[0][6] +
					 (hal_data->MCSTxPowerLevelOriginalOffset[0][7] << 8);
				tx_agc[RF_PATH_A] += पंचांगpval;

				पंचांगpval = hal_data->MCSTxPowerLevelOriginalOffset[0][14] +
					 (hal_data->MCSTxPowerLevelOriginalOffset[0][15] << 24);
				tx_agc[RF_PATH_B] += पंचांगpval;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (idx1 = RF_PATH_A; idx1 <= RF_PATH_B; idx1++) अणु
		ptr = (u8 *)(&tx_agc[idx1]);
		क्रम (idx2 = 0; idx2 < 4; idx2++) अणु
			अगर (*ptr > RF6052_MAX_TX_PWR)
				*ptr = RF6052_MAX_TX_PWR;
			ptr++;
		पूर्ण
	पूर्ण
	rtl88eu_dm_txघातer_track_adjust(&hal_data->odmpriv, 1, &direction,
					&pwrtrac_value);

	अगर (direction == 1) अणु
		/*  Increase TX घातer */
		tx_agc[0] += pwrtrac_value;
		tx_agc[1] += pwrtrac_value;
	पूर्ण अन्यथा अगर (direction == 2) अणु
		/*  Decrease TX घातer */
		tx_agc[0] -=  pwrtrac_value;
		tx_agc[1] -=  pwrtrac_value;
	पूर्ण

	/*  rf-A cck tx घातer */
	पंचांगpval = tx_agc[RF_PATH_A] & 0xff;
	phy_set_bb_reg(adapt, rTxAGC_A_CCK1_Mcs32, bMaskByte1, पंचांगpval);
	पंचांगpval = tx_agc[RF_PATH_A] >> 8;
	phy_set_bb_reg(adapt, rTxAGC_B_CCK11_A_CCK2_11, 0xffffff00, पंचांगpval);

	/*  rf-B cck tx घातer */
	पंचांगpval = tx_agc[RF_PATH_B] >> 24;
	phy_set_bb_reg(adapt, rTxAGC_B_CCK11_A_CCK2_11, bMaskByte0, पंचांगpval);
	पंचांगpval = tx_agc[RF_PATH_B] & 0x00ffffff;
	phy_set_bb_reg(adapt, rTxAGC_B_CCK1_55_Mcs32, 0xffffff00, पंचांगpval);
पूर्ण

/*  घातerbase0 क्रम OFDM rates */
/*  घातerbase1 क्रम HT MCS rates */
अटल व्योम getघातerbase88e(काष्ठा adapter *adapt, u8 *pwr_level_ofdm,
			    u8 *pwr_level_bw20, u8 *pwr_level_bw40,
			    u8 channel, u32 *ofdmbase, u32 *mcs_base)
अणु
	u32 घातerbase0, घातerbase1;
	u8 i, घातerlevel[2];

	क्रम (i = 0; i < 2; i++) अणु
		घातerbase0 = pwr_level_ofdm[i];

		घातerbase0 = (घातerbase0 << 24) | (घातerbase0 << 16) |
			     (घातerbase0 << 8) | घातerbase0;
		*(ofdmbase + i) = घातerbase0;
	पूर्ण
	/* Check HT20 to HT40 dअगरf */
	अगर (adapt->HalData->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
		घातerlevel[0] = pwr_level_bw20[0];
	अन्यथा
		घातerlevel[0] = pwr_level_bw40[0];
	घातerbase1 = घातerlevel[0];
	घातerbase1 = (घातerbase1 << 24) | (घातerbase1 << 16) |
		     (घातerbase1 << 8) | घातerbase1;
	*mcs_base = घातerbase1;
पूर्ण

अटल व्योम get_rx_घातer_val_by_reg(काष्ठा adapter *adapt, u8 channel,
				    u8 index, u32 *घातerbase0, u32 *घातerbase1,
				    u32 *out_val)
अणु
	काष्ठा hal_data_8188e *hal_data = adapt->HalData;
	काष्ठा dm_priv	*pdmpriv = &hal_data->dmpriv;
	u8 i, chnlGroup = 0, pwr_dअगरf_limit[4], customer_pwr_limit;
	s8 pwr_dअगरf = 0;
	u32 ग_लिखो_val, customer_limit, rf;
	u8 regulatory = hal_data->EEPROMRegulatory;

	/*  Index 0 & 1= legacy OFDM, 2-5=HT_MCS rate */

	क्रम (rf = 0; rf < 2; rf++) अणु
		u8 j = index + (rf ? 8 : 0);

		चयन (regulatory) अणु
		हाल 0:
			chnlGroup = 0;
			ग_लिखो_val = hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][index + (rf ? 8 : 0)] +
				((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);
			अवरोध;
		हाल 1: /*  Realtek regulatory */
			/*  increase घातer dअगरf defined by Realtek क्रम regulatory */
			अगर (hal_data->pwrGroupCnt == 1)
				chnlGroup = 0;
			अगर (hal_data->pwrGroupCnt >= hal_data->PGMaxGroup)
				Hal_GetChnlGroup88E(channel, &chnlGroup);

			ग_लिखो_val = hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][index + (rf ? 8 : 0)] +
					((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);
			अवरोध;
		हाल 2:	/*  Better regulatory */
				/*  करोn't increase any घातer dअगरf */
			ग_लिखो_val = (index < 2) ? घातerbase0[rf] : घातerbase1[rf];
			अवरोध;
		हाल 3:	/*  Customer defined घातer dअगरf. */
				/*  increase घातer dअगरf defined by customer. */
			chnlGroup = 0;

			अगर (index < 2)
				pwr_dअगरf = hal_data->TxPwrLegacyHtDअगरf[rf][channel - 1];
			अन्यथा अगर (hal_data->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
				pwr_dअगरf = hal_data->TxPwrHt20Dअगरf[rf][channel - 1];

			अगर (hal_data->CurrentChannelBW == HT_CHANNEL_WIDTH_40)
				customer_pwr_limit = hal_data->PwrGroupHT40[rf][channel - 1];
			अन्यथा
				customer_pwr_limit = hal_data->PwrGroupHT20[rf][channel - 1];

			अगर (pwr_dअगरf >= customer_pwr_limit)
				pwr_dअगरf = 0;
			अन्यथा
				pwr_dअगरf = customer_pwr_limit - pwr_dअगरf;

			क्रम (i = 0; i < 4; i++) अणु
				pwr_dअगरf_limit[i] = (u8)((hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][j] &
							 (0x7f << (i * 8))) >> (i * 8));

				अगर (pwr_dअगरf_limit[i] > pwr_dअगरf)
					pwr_dअगरf_limit[i] = pwr_dअगरf;
			पूर्ण
			customer_limit = (pwr_dअगरf_limit[3] << 24) |
					 (pwr_dअगरf_limit[2] << 16) |
					 (pwr_dअगरf_limit[1] << 8) |
					 (pwr_dअगरf_limit[0]);
			ग_लिखो_val = customer_limit + ((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);
			अवरोध;
		शेष:
			chnlGroup = 0;
			ग_लिखो_val = hal_data->MCSTxPowerLevelOriginalOffset[chnlGroup][j] +
					((index < 2) ? घातerbase0[rf] : घातerbase1[rf]);
			अवरोध;
		पूर्ण
/*  20100427 Joseph: Driver dynamic Tx घातer shall not affect Tx घातer. It shall be determined by घातer training mechanism. */
/*  Currently, we cannot fully disable driver dynamic tx घातer mechanism because it is referenced by BT coexist mechanism. */
/*  In the future, two mechanism shall be separated from each other and मुख्यtained independently. Thanks क्रम Lanhsin's reminder. */
		/* 92d करो not need this */
		अगर (pdmpriv->DynamicTxHighPowerLvl == TxHighPwrLevel_Level1)
			ग_लिखो_val = 0x14141414;
		अन्यथा अगर (pdmpriv->DynamicTxHighPowerLvl == TxHighPwrLevel_Level2)
			ग_लिखो_val = 0x00000000;

		*(out_val + rf) = ग_लिखो_val;
	पूर्ण
पूर्ण

अटल व्योम ग_लिखो_ofdm_pwr_reg(काष्ठा adapter *adapt, u8 index, u32 *pvalue)
अणु
	u16 regoffset_a[6] = अणु rTxAGC_A_Rate18_06, rTxAGC_A_Rate54_24,
			       rTxAGC_A_Mcs03_Mcs00, rTxAGC_A_Mcs07_Mcs04,
			       rTxAGC_A_Mcs11_Mcs08, rTxAGC_A_Mcs15_Mcs12 पूर्ण;
	u16 regoffset_b[6] = अणु rTxAGC_B_Rate18_06, rTxAGC_B_Rate54_24,
			       rTxAGC_B_Mcs03_Mcs00, rTxAGC_B_Mcs07_Mcs04,
			       rTxAGC_B_Mcs11_Mcs08, rTxAGC_B_Mcs15_Mcs12 पूर्ण;
	u8 i, rf, pwr_val[4];
	u32 ग_लिखो_val;
	u16 regoffset;

	क्रम (rf = 0; rf < 2; rf++) अणु
		ग_लिखो_val = pvalue[rf];
		क्रम (i = 0; i < 4; i++) अणु
			pwr_val[i] = (u8)((ग_लिखो_val & (0x7f << (i * 8))) >> (i * 8));
			अगर (pwr_val[i]  > RF6052_MAX_TX_PWR)
				pwr_val[i]  = RF6052_MAX_TX_PWR;
		पूर्ण
		ग_लिखो_val = (pwr_val[3] << 24) | (pwr_val[2] << 16) |
			    (pwr_val[1] << 8) | pwr_val[0];

		अगर (rf == 0)
			regoffset = regoffset_a[index];
		अन्यथा
			regoffset = regoffset_b[index];

		phy_set_bb_reg(adapt, regoffset, bMaskDWord, ग_लिखो_val);
	पूर्ण
पूर्ण

व्योम rtl88eu_phy_rf6052_set_ofdm_txघातer(काष्ठा adapter *adapt,
					 u8 *pwr_level_ofdm,
					 u8 *pwr_level_bw20,
					 u8 *pwr_level_bw40, u8 channel)
अणु
	u32 ग_लिखो_val[2], घातerbase0[2], घातerbase1[2], pwrtrac_value;
	u8 direction;
	u8 index = 0;

	getघातerbase88e(adapt, pwr_level_ofdm, pwr_level_bw20, pwr_level_bw40,
			channel, &घातerbase0[0], &घातerbase1[0]);

	rtl88eu_dm_txघातer_track_adjust(&adapt->HalData->odmpriv, 0,
					&direction, &pwrtrac_value);

	क्रम (index = 0; index < 6; index++) अणु
		get_rx_घातer_val_by_reg(adapt, channel, index,
					&घातerbase0[0], &घातerbase1[0],
					&ग_लिखो_val[0]);

		अगर (direction == 1) अणु
			ग_लिखो_val[0] += pwrtrac_value;
			ग_लिखो_val[1] += pwrtrac_value;
		पूर्ण अन्यथा अगर (direction == 2) अणु
			ग_लिखो_val[0] -= pwrtrac_value;
			ग_लिखो_val[1] -= pwrtrac_value;
		पूर्ण
		ग_लिखो_ofdm_pwr_reg(adapt, index, &ग_लिखो_val[0]);
	पूर्ण
पूर्ण
