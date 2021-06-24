<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

/*  This function is क्रम inband noise test utility only */
/*  To obtain the inband noise level(dbm), करो the following. */
/*  1. disable DIG and Power Saving */
/*  2. Set initial gain = 0x1a */
/*  3. Stop updating idle समय pwer report (क्रम driver पढ़ो) */
/* - 0x80c[25] */

#घोषणा Valid_Min				-35
#घोषणा Valid_Max			10
#घोषणा ValidCnt				5

अटल s16 odm_InbandNoise_Monitor_NSeries(
	काष्ठा dm_odm_t *pDM_Odm,
	u8 bPauseDIG,
	u8 IGIValue,
	u32 max_समय
)
अणु
	u32 पंचांगp4b;
	u8 max_rf_path = 0, rf_path;
	u8 reg_c50, reg_c58, valid_करोne = 0;
	काष्ठा noise_level noise_data;
	u32 start  = 0, func_start = 0, func_end = 0;

	func_start = jअगरfies;
	pDM_Odm->noise_level.noise_all = 0;

	अगर ((pDM_Odm->RFType == ODM_1T2R) || (pDM_Odm->RFType == ODM_2T2R))
		max_rf_path = 2;
	अन्यथा
		max_rf_path = 1;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("odm_DebugControlInbandNoise_Nseries() ==>\n"));

	स_रखो(&noise_data, 0, माप(काष्ठा noise_level));

	/*  */
	/*  Step 1. Disable DIG && Set initial gain. */
	/*  */

	अगर (bPauseDIG)
		odm_PauseDIG(pDM_Odm, ODM_PAUSE_DIG, IGIValue);
	/*  */
	/*  Step 2. Disable all घातer save क्रम पढ़ो रेजिस्टरs */
	/*  */
	/* dcmd_DebugControlPowerSave(padapter, PSDisable); */

	/*  */
	/*  Step 3. Get noise घातer level */
	/*  */
	start = jअगरfies;
	जबतक (1) अणु

		/* Stop updating idle समय pwer report (क्रम driver पढ़ो) */
		PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_TxGainStage, BIT25, 1);

		/* Read Noise Floor Report */
		पंचांगp4b = PHY_QueryBBReg(pDM_Odm->Adapter, 0x8f8, bMaskDWord);
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("Noise Floor Report (0x8f8) = 0x%08x\n", पंचांगp4b));

		/* PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XAAGCCore1, bMaskByte0, TestInitialGain); */
		/* अगर (max_rf_path == 2) */
		/* PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBAGCCore1, bMaskByte0, TestInitialGain); */

		/* update idle समय pwer report per 5us */
		PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_TxGainStage, BIT25, 0);

		noise_data.value[ODM_RF_PATH_A] = (u8)(पंचांगp4b&0xff);
		noise_data.value[ODM_RF_PATH_B]  = (u8)((पंचांगp4b&0xff00)>>8);

		ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("value_a = 0x%x(%d), value_b = 0x%x(%d)\n",
			noise_data.value[ODM_RF_PATH_A], noise_data.value[ODM_RF_PATH_A], noise_data.value[ODM_RF_PATH_B], noise_data.value[ODM_RF_PATH_B]));

		क्रम (rf_path = ODM_RF_PATH_A; rf_path < max_rf_path; rf_path++) अणु
			noise_data.sval[rf_path] = (s8)noise_data.value[rf_path];
			noise_data.sval[rf_path] /= 2;
		पूर्ण


		ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("sval_a = %d, sval_b = %d\n",
			noise_data.sval[ODM_RF_PATH_A], noise_data.sval[ODM_RF_PATH_B]));
		/* mdelay(10); */
		/* msleep(10); */

		क्रम (rf_path = ODM_RF_PATH_A; rf_path < max_rf_path; rf_path++) अणु
			अगर ((noise_data.valid_cnt[rf_path] < ValidCnt) && (noise_data.sval[rf_path] < Valid_Max && noise_data.sval[rf_path] >= Valid_Min)) अणु
				noise_data.valid_cnt[rf_path]++;
				noise_data.sum[rf_path] += noise_data.sval[rf_path];
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("RF_Path:%d Valid sval = %d\n", rf_path, noise_data.sval[rf_path]));
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("Sum of sval = %d,\n", noise_data.sum[rf_path]));
				अगर (noise_data.valid_cnt[rf_path] == ValidCnt) अणु
					valid_करोne++;
					ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("After divided, RF_Path:%d , sum = %d\n", rf_path, noise_data.sum[rf_path]));
				पूर्ण

			पूर्ण

		पूर्ण

		/* prपूर्णांकk("####### valid_done:%d #############\n", valid_करोne); */
		अगर ((valid_करोne == max_rf_path) || (jअगरfies_to_msecs(jअगरfies - start) > max_समय)) अणु
			क्रम (rf_path = ODM_RF_PATH_A; rf_path < max_rf_path; rf_path++) अणु
				/* prपूर्णांकk("%s PATH_%d - sum = %d, valid_cnt = %d\n", __func__, rf_path, noise_data.sum[rf_path], noise_data.valid_cnt[rf_path]); */
				अगर (noise_data.valid_cnt[rf_path])
					noise_data.sum[rf_path] /= noise_data.valid_cnt[rf_path];
				अन्यथा
					noise_data.sum[rf_path]  = 0;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
	reg_c50 = (s32)PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XAAGCCore1, bMaskByte0);
	reg_c50 &= ~BIT7;
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("0x%x = 0x%02x(%d)\n", rOFDM0_XAAGCCore1, reg_c50, reg_c50));
	pDM_Odm->noise_level.noise[ODM_RF_PATH_A] = -110 + reg_c50 + noise_data.sum[ODM_RF_PATH_A];
	pDM_Odm->noise_level.noise_all += pDM_Odm->noise_level.noise[ODM_RF_PATH_A];

	अगर (max_rf_path == 2) अणु
		reg_c58 = (s32)PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XBAGCCore1, bMaskByte0);
		reg_c58 &= ~BIT7;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("0x%x = 0x%02x(%d)\n", rOFDM0_XBAGCCore1, reg_c58, reg_c58));
		pDM_Odm->noise_level.noise[ODM_RF_PATH_B] = -110 + reg_c58 + noise_data.sum[ODM_RF_PATH_B];
		pDM_Odm->noise_level.noise_all += pDM_Odm->noise_level.noise[ODM_RF_PATH_B];
	पूर्ण
	pDM_Odm->noise_level.noise_all /= max_rf_path;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_COMMON,
		ODM_DBG_LOUD,
		(
			"noise_a = %d, noise_b = %d\n",
			pDM_Odm->noise_level.noise[ODM_RF_PATH_A],
			pDM_Odm->noise_level.noise[ODM_RF_PATH_B]
		)
	);

	/*  */
	/*  Step 4. Recover the Dig */
	/*  */
	अगर (bPauseDIG)
		odm_PauseDIG(pDM_Odm, ODM_RESUME_DIG, IGIValue);

	func_end = jअगरfies_to_msecs(jअगरfies - func_start);
	/* prपूर्णांकk("%s noise_a = %d, noise_b = %d noise_all:%d (%d ms)\n", __func__, */
	/* pDM_Odm->noise_level.noise[ODM_RF_PATH_A], */
	/* pDM_Odm->noise_level.noise[ODM_RF_PATH_B], */
	/* pDM_Odm->noise_level.noise_all, func_end); */

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_COMMON, ODM_DBG_LOUD, ("odm_DebugControlInbandNoise_Nseries() <==\n"));
	वापस pDM_Odm->noise_level.noise_all;

पूर्ण

s16 ODM_InbandNoise_Monitor(व्योम *pDM_VOID, u8 bPauseDIG, u8 IGIValue, u32 max_समय)
अणु
	वापस odm_InbandNoise_Monitor_NSeries(pDM_VOID, bPauseDIG, IGIValue, max_समय);
पूर्ण
