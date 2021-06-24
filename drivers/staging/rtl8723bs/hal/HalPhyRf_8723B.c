<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*****************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश "odm_precomp.h"



/*---------------------------Define Local Constant---------------------------*/
/*  2010/04/25 MH Define the max tx घातer tracking tx agc घातer. */
#घोषणा		ODM_TXPWRTRACK_MAX_IDX8723B	6

/*  MACRO definition क्रम pRFCalibrateInfo->TxIQC_8723B[0] */
#घोषणा		PATH_S0							1 /*  RF_PATH_B */
#घोषणा		IDX_0xC94						0
#घोषणा		IDX_0xC80						1
#घोषणा		IDX_0xC4C						2
#घोषणा		IDX_0xC14						0
#घोषणा		IDX_0xCA0						1
#घोषणा		KEY							0
#घोषणा		VAL							1

/*  MACRO definition क्रम pRFCalibrateInfo->TxIQC_8723B[1] */
#घोषणा		PATH_S1							0 /*  RF_PATH_A */
#घोषणा		IDX_0xC9C						0
#घोषणा		IDX_0xC88						1
#घोषणा		IDX_0xC4C						2
#घोषणा		IDX_0xC1C						0
#घोषणा		IDX_0xC78						1


/*---------------------------Define Local Constant---------------------------*/

/* In the हाल that we fail to पढ़ो TxPowerTrack.txt, we use the table क्रम
 * 88E as the शेष table.
 */
अटल u8 DeltaSwingTableIdx_2GA_N_8188E[] = अणु
	0, 0, 0, 2, 2, 3, 3, 4,  4,  4,  4,  5,  5,  6,  6,
	7, 7, 7, 7, 8, 8, 9, 9, 10, 10, 10, 11, 11, 11, 11
पूर्ण;
अटल u8 DeltaSwingTableIdx_2GA_P_8188E[] = अणु
	0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4,
	4, 4, 4, 5, 5, 7, 7, 8, 8, 8, 9, 9, 9, 9, 9
पूर्ण;

/* 3 ============================================================ */
/* 3 Tx Power Tracking */
/* 3 ============================================================ */


अटल व्योम setIqkMatrix_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u8 OFDM_index,
	u8 RFPath,
	s32 IqkResult_X,
	s32 IqkResult_Y
)
अणु
	s32 ele_A = 0, ele_D, ele_C = 0, value32;

	अगर (OFDM_index >= OFDM_TABLE_SIZE)
		OFDM_index = OFDM_TABLE_SIZE-1;

	ele_D = (OFDMSwingTable_New[OFDM_index] & 0xFFC00000)>>22;

	/* new element A = element D x X */
	अगर ((IqkResult_X != 0) && (*(pDM_Odm->pBandType) == ODM_BAND_2_4G)) अणु
		अगर ((IqkResult_X & 0x00000200) != 0)	/* consider minus */
			IqkResult_X = IqkResult_X | 0xFFFFFC00;
		ele_A = ((IqkResult_X * ele_D)>>8)&0x000003FF;

		/* new element C = element D x Y */
		अगर ((IqkResult_Y & 0x00000200) != 0)
			IqkResult_Y = IqkResult_Y | 0xFFFFFC00;
		ele_C = ((IqkResult_Y * ele_D)>>8)&0x000003FF;

		/* अगर (RFPath == ODM_RF_PATH_A) */
		चयन (RFPath) अणु
		हाल ODM_RF_PATH_A:
			/* ग_लिखो new elements A, C, D to regC80 and regC94,
			 * element B is always 0
			 */
			value32 = (ele_D<<22)|((ele_C&0x3F)<<16)|ele_A;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, bMaskDWord, value32);

			value32 = (ele_C&0x000003C0)>>6;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XCTxAFE, bMaskH4Bits, value32);

			value32 = ((IqkResult_X * ele_D)>>7)&0x01;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT24, value32);
			अवरोध;
		हाल ODM_RF_PATH_B:
			/* ग_लिखो new elements A, C, D to regC88 and regC9C,
			 * element B is always 0
			 */
			value32 = (ele_D<<22)|((ele_C&0x3F)<<16)|ele_A;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, bMaskDWord, value32);

			value32 = (ele_C&0x000003C0)>>6;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XDTxAFE, bMaskH4Bits, value32);

			value32 = ((IqkResult_X * ele_D)>>7)&0x01;
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT28, value32);

			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (RFPath) अणु
		हाल ODM_RF_PATH_A:
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, bMaskDWord, OFDMSwingTable_New[OFDM_index]);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XCTxAFE, bMaskH4Bits, 0x00);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT24, 0x00);
			अवरोध;

		हाल ODM_RF_PATH_B:
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, bMaskDWord, OFDMSwingTable_New[OFDM_index]);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XDTxAFE, bMaskH4Bits, 0x00);
			PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT28, 0x00);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("TxPwrTracking path B: X = 0x%x, Y = 0x%x ele_A = 0x%x ele_C = 0x%x ele_D = 0x%x 0xeb4 = 0x%x 0xebc = 0x%x\n",
	(u32)IqkResult_X, (u32)IqkResult_Y, (u32)ele_A, (u32)ele_C, (u32)ele_D, (u32)IqkResult_X, (u32)IqkResult_Y));
पूर्ण


अटल व्योम setCCKFilterCoefficient(काष्ठा dm_odm_t *pDM_Odm, u8 CCKSwingIndex)
अणु
	अगर (!pDM_Odm->RFCalibrateInfo.bCCKinCH14) अणु
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa22, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][0]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa23, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][1]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa24, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][2]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa25, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][3]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa26, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][4]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa27, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][5]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa28, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][6]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa29, CCKSwingTable_Ch1_Ch13_New[CCKSwingIndex][7]);
	पूर्ण अन्यथा अणु
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa22, CCKSwingTable_Ch14_New[CCKSwingIndex][0]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa23, CCKSwingTable_Ch14_New[CCKSwingIndex][1]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa24, CCKSwingTable_Ch14_New[CCKSwingIndex][2]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa25, CCKSwingTable_Ch14_New[CCKSwingIndex][3]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa26, CCKSwingTable_Ch14_New[CCKSwingIndex][4]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa27, CCKSwingTable_Ch14_New[CCKSwingIndex][5]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa28, CCKSwingTable_Ch14_New[CCKSwingIndex][6]);
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xa29, CCKSwingTable_Ch14_New[CCKSwingIndex][7]);
	पूर्ण
पूर्ण

व्योम DoIQK_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u8 DeltaThermalIndex,
	u8 ThermalValue,
	u8 Threshold
)
अणु
पूर्ण

/*-----------------------------------------------------------------------------
 * Function:	odm_TxPwrTrackSetPwr88E()
 *
 * Overview:	88E change all channel tx घातer according to flag.
 *			OFDM & CCK are all dअगरferent.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Return:		NONE
 *
 * Revised History:
 *When		Who	Remark
 *04/23/2012	MHC	Create Version 0.
 *
 *---------------------------------------------------------------------------*/
व्योम ODM_TxPwrTrackSetPwr_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	क्रमागत pwrtrack_method Method,
	u8 RFPath,
	u8 ChannelMappedIndex
)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	u8 PwrTrackingLimit_OFDM = 34; /* 0dB */
	u8 PwrTrackingLimit_CCK = 28; /* 2dB */
	u8 TxRate = 0xFF;
	u8 Final_OFDM_Swing_Index = 0;
	u8 Final_CCK_Swing_Index = 0;

	अणु
		u16 rate = *(pDM_Odm->pForcedDataRate);

		अगर (!rate) अणु /* स्वतः rate */
			अगर (pDM_Odm->TxRate != 0xFF)
				TxRate = HwRateToMRate(pDM_Odm->TxRate);
		पूर्ण अन्यथा /* क्रमce rate */
			TxRate = (u8)rate;

	पूर्ण

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("===>ODM_TxPwrTrackSetPwr8723B\n"));

	अगर (TxRate != 0xFF) अणु
		/* 2 CCK */
		अगर ((TxRate >= MGN_1M) && (TxRate <= MGN_11M))
			PwrTrackingLimit_CCK = 28;	/* 2dB */
		/* 2 OFDM */
		अन्यथा अगर ((TxRate >= MGN_6M) && (TxRate <= MGN_48M))
			PwrTrackingLimit_OFDM = 36; /* 3dB */
		अन्यथा अगर (TxRate == MGN_54M)
			PwrTrackingLimit_OFDM = 34; /* 2dB */

		/* 2 HT */
		अन्यथा अगर ((TxRate >= MGN_MCS0) && (TxRate <= MGN_MCS2)) /* QPSK/BPSK */
			PwrTrackingLimit_OFDM = 38; /* 4dB */
		अन्यथा अगर ((TxRate >= MGN_MCS3) && (TxRate <= MGN_MCS4)) /* 16QAM */
			PwrTrackingLimit_OFDM = 36; /* 3dB */
		अन्यथा अगर ((TxRate >= MGN_MCS5) && (TxRate <= MGN_MCS7)) /* 64QAM */
			PwrTrackingLimit_OFDM = 34; /* 2dB */

		अन्यथा
			PwrTrackingLimit_OFDM =  pDM_Odm->DefaultOfdmIndex;   /* Default OFDM index = 30 */
	पूर्ण
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("TxRate = 0x%x, PwrTrackingLimit =%d\n", TxRate, PwrTrackingLimit_OFDM));

	अगर (Method == TXAGC) अणु
		काष्ठा adapter *Adapter = pDM_Odm->Adapter;

		ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD, ("odm_TxPwrTrackSetPwr8723B CH =%d\n", *(pDM_Odm->pChannel)));

		pDM_Odm->Remnant_OFDMSwingIdx[RFPath] = pDM_Odm->Absolute_OFDMSwingIdx[RFPath];

		pDM_Odm->Modअगरy_TxAGC_Flag_PathA = true;
		pDM_Odm->Modअगरy_TxAGC_Flag_PathA_CCK = true;

		PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, CCK);
		PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, OFDM);
		PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, HT_MCS0_MCS7);
	पूर्ण अन्यथा अगर (Method == BBSWING) अणु
		Final_OFDM_Swing_Index = pDM_Odm->DefaultOfdmIndex + pDM_Odm->Absolute_OFDMSwingIdx[RFPath];
		Final_CCK_Swing_Index = pDM_Odm->DefaultCckIndex + pDM_Odm->Absolute_OFDMSwingIdx[RFPath];

		/*  Adjust BB swing by OFDM IQ matrix */
		अगर (Final_OFDM_Swing_Index >= PwrTrackingLimit_OFDM)
			Final_OFDM_Swing_Index = PwrTrackingLimit_OFDM;
		अन्यथा अगर (Final_OFDM_Swing_Index <= 0)
			Final_OFDM_Swing_Index = 0;

		अगर (Final_CCK_Swing_Index >= CCK_TABLE_SIZE)
			Final_CCK_Swing_Index = CCK_TABLE_SIZE-1;
		अन्यथा अगर (pDM_Odm->BbSwingIdxCck <= 0)
			Final_CCK_Swing_Index = 0;

		setIqkMatrix_8723B(pDM_Odm, Final_OFDM_Swing_Index, RFPath,
			pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][0],
			pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][1]);

		setCCKFilterCoefficient(pDM_Odm, Final_CCK_Swing_Index);

	पूर्ण अन्यथा अगर (Method == MIX_MODE) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			("pDM_Odm->DefaultOfdmIndex =%d,  pDM_Odm->DefaultCCKIndex =%d, pDM_Odm->Absolute_OFDMSwingIdx[RFPath]=%d, RF_Path = %d\n",
			pDM_Odm->DefaultOfdmIndex, pDM_Odm->DefaultCckIndex, pDM_Odm->Absolute_OFDMSwingIdx[RFPath], RFPath));

		Final_OFDM_Swing_Index = pDM_Odm->DefaultOfdmIndex + pDM_Odm->Absolute_OFDMSwingIdx[RFPath];
		Final_CCK_Swing_Index = pDM_Odm->DefaultCckIndex + pDM_Odm->Absolute_OFDMSwingIdx[RFPath];

		अगर (Final_OFDM_Swing_Index > PwrTrackingLimit_OFDM) अणु /* BBSwing higher then Limit */
			pDM_Odm->Remnant_OFDMSwingIdx[RFPath] = Final_OFDM_Swing_Index - PwrTrackingLimit_OFDM;

			setIqkMatrix_8723B(pDM_Odm, PwrTrackingLimit_OFDM, RFPath,
				pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][0],
				pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][1]);

			pDM_Odm->Modअगरy_TxAGC_Flag_PathA = true;
			PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, OFDM);
			PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, HT_MCS0_MCS7);

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("******Path_A Over BBSwing Limit , PwrTrackingLimit = %d , Remnant TxAGC Value = %d\n",
				PwrTrackingLimit_OFDM, pDM_Odm->Remnant_OFDMSwingIdx[RFPath]));
		पूर्ण अन्यथा अगर (Final_OFDM_Swing_Index <= 0) अणु
			pDM_Odm->Remnant_OFDMSwingIdx[RFPath] = Final_OFDM_Swing_Index;

			setIqkMatrix_8723B(pDM_Odm, 0, RFPath,
				pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][0],
				pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][1]);

			pDM_Odm->Modअगरy_TxAGC_Flag_PathA = true;
			PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, OFDM);
			PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, HT_MCS0_MCS7);

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("******Path_A Lower then BBSwing lower bound  0 , Remnant TxAGC Value = %d\n",
				pDM_Odm->Remnant_OFDMSwingIdx[RFPath]));
		पूर्ण अन्यथा अणु
			setIqkMatrix_8723B(pDM_Odm, Final_OFDM_Swing_Index, RFPath,
				pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][0],
				pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[ChannelMappedIndex].Value[0][1]);

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("******Path_A Compensate with BBSwing , Final_OFDM_Swing_Index = %d\n", Final_OFDM_Swing_Index));

			अगर (pDM_Odm->Modअगरy_TxAGC_Flag_PathA) अणु /* If TxAGC has changed, reset TxAGC again */
				pDM_Odm->Remnant_OFDMSwingIdx[RFPath] = 0;
				PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, OFDM);
				PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, HT_MCS0_MCS7);
				pDM_Odm->Modअगरy_TxAGC_Flag_PathA = false;

				ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
					("******Path_A pDM_Odm->Modify_TxAGC_Flag = false\n"));
			पूर्ण
		पूर्ण

		अगर (Final_CCK_Swing_Index > PwrTrackingLimit_CCK) अणु
			pDM_Odm->Remnant_CCKSwingIdx = Final_CCK_Swing_Index - PwrTrackingLimit_CCK;
			setCCKFilterCoefficient(pDM_Odm, PwrTrackingLimit_CCK);
			pDM_Odm->Modअगरy_TxAGC_Flag_PathA_CCK = true;
			PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, CCK);

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("******Path_A CCK Over Limit , PwrTrackingLimit_CCK = %d , pDM_Odm->Remnant_CCKSwingIdx  = %d\n", PwrTrackingLimit_CCK, pDM_Odm->Remnant_CCKSwingIdx));
		पूर्ण अन्यथा अगर (Final_CCK_Swing_Index <= 0) अणु /*  Lowest CCK Index = 0 */
			pDM_Odm->Remnant_CCKSwingIdx = Final_CCK_Swing_Index;
			setCCKFilterCoefficient(pDM_Odm, 0);
			pDM_Odm->Modअगरy_TxAGC_Flag_PathA_CCK = true;
			PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, CCK);

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("******Path_A CCK Under Limit , PwrTrackingLimit_CCK = %d , pDM_Odm->Remnant_CCKSwingIdx  = %d\n", 0, pDM_Odm->Remnant_CCKSwingIdx));
		पूर्ण अन्यथा अणु
			setCCKFilterCoefficient(pDM_Odm, Final_CCK_Swing_Index);

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
				("******Path_A CCK Compensate with BBSwing , Final_CCK_Swing_Index = %d\n", Final_CCK_Swing_Index));

			अगर (pDM_Odm->Modअगरy_TxAGC_Flag_PathA_CCK) अणु /* If TxAGC has changed, reset TxAGC again */
				pDM_Odm->Remnant_CCKSwingIdx = 0;
				PHY_SetTxPowerIndexByRateSection(Adapter, RFPath, pHalData->CurrentChannel, CCK);
				pDM_Odm->Modअगरy_TxAGC_Flag_PathA_CCK = false;

				ODM_RT_TRACE(pDM_Odm, ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
					("******Path_A pDM_Odm->Modify_TxAGC_Flag_CCK = false\n"));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		वापस; /*  This method is not supported. */
पूर्ण

अटल व्योम GetDeltaSwingTable_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u8 **TemperatureUP_A,
	u8 **TemperatureDOWN_A,
	u8 **TemperatureUP_B,
	u8 **TemperatureDOWN_B
)
अणु
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा odm_rf_cal_t *pRFCalibrateInfo = &pDM_Odm->RFCalibrateInfo;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	u16 rate = *(pDM_Odm->pForcedDataRate);
	u8 channel = pHalData->CurrentChannel;

	अगर (1 <= channel && channel <= 14) अणु
		अगर (IS_CCK_RATE(rate)) अणु
			*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKA_P;
			*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKA_N;
			*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKB_P;
			*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_2GCCKB_N;
		पूर्ण अन्यथा अणु
			*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_2GA_P;
			*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_2GA_N;
			*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_2GB_P;
			*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_2GB_N;
		पूर्ण
	पूर्ण /*अन्यथा अगर (36 <= channel && channel <= 64) अणु
		*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[0];
		*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[0];
		*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[0];
		*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[0];
	पूर्ण अन्यथा अगर (100 <= channel && channel <= 140) अणु
		*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[1];
		*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[1];
		*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[1];
		*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[1];
	पूर्ण अन्यथा अगर (149 <= channel && channel <= 173) अणु
		*TemperatureUP_A   = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_P[2];
		*TemperatureDOWN_A = pRFCalibrateInfo->DeltaSwingTableIdx_5GA_N[2];
		*TemperatureUP_B   = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_P[2];
		*TemperatureDOWN_B = pRFCalibrateInfo->DeltaSwingTableIdx_5GB_N[2];
	पूर्ण*/अन्यथा अणु
		*TemperatureUP_A   = (u8 *)DeltaSwingTableIdx_2GA_P_8188E;
		*TemperatureDOWN_A = (u8 *)DeltaSwingTableIdx_2GA_N_8188E;
		*TemperatureUP_B   = (u8 *)DeltaSwingTableIdx_2GA_P_8188E;
		*TemperatureDOWN_B = (u8 *)DeltaSwingTableIdx_2GA_N_8188E;
	पूर्ण
पूर्ण


व्योम ConfigureTxघातerTrack_8723B(काष्ठा txpwrtrack_cfg *pConfig)
अणु
	pConfig->SwingTableSize_CCK = CCK_TABLE_SIZE;
	pConfig->SwingTableSize_OFDM = OFDM_TABLE_SIZE;
	pConfig->Threshold_IQK = IQK_THRESHOLD;
	pConfig->AverageThermalNum = AVG_THERMAL_NUM_8723B;
	pConfig->RfPathCount = MAX_PATH_NUM_8723B;
	pConfig->ThermalRegAddr = RF_T_METER_8723B;

	pConfig->ODM_TxPwrTrackSetPwr = ODM_TxPwrTrackSetPwr_8723B;
	pConfig->DoIQK = DoIQK_8723B;
	pConfig->PHY_LCCalibrate = PHY_LCCalibrate_8723B;
	pConfig->GetDeltaSwingTable = GetDeltaSwingTable_8723B;
पूर्ण

/* 1 7. IQK */
#घोषणा MAX_TOLERANCE		5
#घोषणा IQK_DELAY_TIME		1		/* ms */

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 phy_PathA_IQK_8723B(
	काष्ठा adapter *padapter, bool configPathB, u8 RF_Path
)
अणु
	u32 regEAC, regE94, regE9C, पंचांगp, Path_SEL_BB /*, regEA4*/;
	u8 result = 0x00;

	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	/*  Save RF Path */
	Path_SEL_BB = PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord);

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A IQK!\n"));

	/* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/* 	enable path A PA in TXIQK mode */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x18000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0003f);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xc7f87);
	/* 	disable path B PA in TXIQK mode */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xed, bRFRegOffsetMask, 0x00020); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x43, bRFRegOffsetMask, 0x40ec1); */

	/* 1 Tx IQK */
	/* IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord, 0x01007c00);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK, bMaskDWord, 0x01004800);
	/* path-A IQK setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path-A IQK setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x8214010a); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x821303ea);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x28110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_B, bMaskDWord, 0x82110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_B, bMaskDWord, 0x28110000);

	/* LO calibration setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Rsp, bMaskDWord, 0x00462911);

	/* enter IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* Ant चयन */
	अगर (configPathB || (RF_Path == 0))
		/*  wअगरi चयन to S1 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000000);
	अन्यथा
		/*  wअगरi चयन to S0 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);

	/* GNT_BT = 0 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00000800);

	/* One shot, path A LOK & IQK */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path A LOK & IQK!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	/*  delay x ms */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_8723B)); */
	/* Platक्रमmStallExecution(IQK_DELAY_TIME_8723B*1000); */
	mdelay(IQK_DELAY_TIME_8723B);

	/* restore Ant Path */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB);
	/* GNT_BT = 1 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00001800);

	/* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);


	/*  Check failed */
	regEAC = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord);
	regE94 = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord);
	regE9C = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe94 = 0x%x, 0xe9c = 0x%x\n", regE94, regE9C));
	/* monitor image घातer beक्रमe & after IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe90(before IQK) = 0x%x, 0xe98(afer IQK) = 0x%x\n",
	PHY_QueryBBReg(pDM_Odm->Adapter, 0xe90, bMaskDWord), PHY_QueryBBReg(pDM_Odm->Adapter, 0xe98, bMaskDWord)));


	/* Allen 20131125 */
	पंचांगp = (regE9C & 0x03FF0000)>>16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (
		!(regEAC & BIT28) &&
		(((regE94 & 0x03FF0000)>>16) != 0x142) &&
		(((regE9C & 0x03FF0000)>>16) != 0x42) &&
		(((regE94 & 0x03FF0000)>>16) < 0x110) &&
		(((regE94 & 0x03FF0000)>>16) > 0xf0) &&
		(पंचांगp < 0xf)
	)
		result |= 0x01;
	अन्यथा					/* अगर Tx not OK, ignore Rx */
		वापस result;

	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 phy_PathA_RxIQK8723B(
	काष्ठा adapter *padapter, bool configPathB, u8 RF_Path
)
अणु
	u32 regEAC, regE94, regE9C, regEA4, u4पंचांगp, पंचांगp, Path_SEL_BB;
	u8 result = 0x00;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A Rx IQK!\n")); */

	/*  Save RF Path */
	Path_SEL_BB = PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord);

	/* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A RX IQK:Get TXIMR setting\n"));
	/* 1 Get TXIMR setting */
	/* modअगरy RXIQK mode table */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path-A Rx IQK modify RXIQK mode table!\n")); */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x18000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0001f);
	/* LNA2 off, PA on क्रम Dcut */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf7fb7);
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x0); */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord, 0x01007c00);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK, bMaskDWord, 0x01004800);

	/* path-A IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_B, bMaskDWord, 0x38008c1c);

/* 	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x82160c1f); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x82130ff0);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x28110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_B, bMaskDWord, 0x82110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_B, bMaskDWord, 0x28110000);

	/* LO calibration setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Rsp, bMaskDWord, 0x0046a911);

	/* enter IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* Ant चयन */
	अगर (configPathB || (RF_Path == 0))
		/*  wअगरi चयन to S1 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000000);
	अन्यथा
		/*  wअगरi चयन to S0 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);

	/* GNT_BT = 0 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00000800);

	/* One shot, path A LOK & IQK */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path A LOK & IQK!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	/*  delay x ms */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_8723B)); */
	/* Platक्रमmStallExecution(IQK_DELAY_TIME_8723B*1000); */
	mdelay(IQK_DELAY_TIME_8723B);

	/* restore Ant Path */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB);
	/* GNT_BT = 1 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00001800);

	/* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/*  Check failed */
	regEAC = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord);
	regE94 = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord);
	regE9C = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe94 = 0x%x, 0xe9c = 0x%x\n", regE94, regE9C));
	/* monitor image घातer beक्रमe & after IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe90(before IQK) = 0x%x, 0xe98(afer IQK) = 0x%x\n",
	PHY_QueryBBReg(pDM_Odm->Adapter, 0xe90, bMaskDWord), PHY_QueryBBReg(pDM_Odm->Adapter, 0xe98, bMaskDWord)));

	/* Allen 20131125 */
	पंचांगp = (regE9C & 0x03FF0000)>>16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (
		!(regEAC & BIT28) &&
		(((regE94 & 0x03FF0000)>>16) != 0x142) &&
		(((regE9C & 0x03FF0000)>>16) != 0x42) &&
		(((regE94 & 0x03FF0000)>>16) < 0x110) &&
		(((regE94 & 0x03FF0000)>>16) > 0xf0) &&
		(पंचांगp < 0xf)
	)
		result |= 0x01;
	अन्यथा				/* अगर Tx not OK, ignore Rx */
		वापस result;

	u4पंचांगp = 0x80007C00 | (regE94&0x3FF0000) | ((regE9C&0x3FF0000) >> 16);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord, u4पंचांगp);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe40 = 0x%x u4tmp = 0x%x\n", PHY_QueryBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord), u4पंचांगp));


	/* 1 RX IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A RX IQK\n"));

	/* modअगरy RXIQK mode table */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path-A Rx IQK modify RXIQK mode table 2!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x18000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0001f);
	/* LAN2 on, PA off क्रम Dcut */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf7d77);
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x0); */

	/* PA, PAD setting */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xdf, bRFRegOffsetMask, 0xf80);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x55, bRFRegOffsetMask, 0x4021f);


	/* IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK, bMaskDWord, 0x01004800);

	/* path-A IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_B, bMaskDWord, 0x38008c1c);

	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x82110000);
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x281604c2); */
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x2813001f);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_B, bMaskDWord, 0x82110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_B, bMaskDWord, 0x28110000);

	/* LO calibration setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Rsp, bMaskDWord, 0x0046a8d1);

	/* enter IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* Ant चयन */
	अगर (configPathB || (RF_Path == 0))
		/*  wअगरi चयन to S1 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000000);
	अन्यथा
		/*  wअगरi चयन to S0 */
		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);

	/* GNT_BT = 0 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00000800);

	/* One shot, path A LOK & IQK */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path A LOK & IQK!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	/*  delay x ms */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_88E)); */
	/* Platक्रमmStallExecution(IQK_DELAY_TIME_8723B*1000); */
	mdelay(IQK_DELAY_TIME_8723B);

	/* restore Ant Path */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB);
	/* GNT_BT = 1 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00001800);

    /* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/*  Check failed */
	regEAC = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord);
	regEA4 = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_Beक्रमe_IQK_A_2, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xea4 = 0x%x, 0xeac = 0x%x\n", regEA4, regEAC));
	/* monitor image घातer beक्रमe & after IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xea0(before IQK) = 0x%x, 0xea8(afer IQK) = 0x%x\n",
	PHY_QueryBBReg(pDM_Odm->Adapter, 0xea0, bMaskDWord), PHY_QueryBBReg(pDM_Odm->Adapter, 0xea8, bMaskDWord)));

	/* 	PA/PAD controlled by 0x0 */
	/* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xdf, bRFRegOffsetMask, 0x780);

	/* Allen 20131125 */
	पंचांगp = (regEAC & 0x03FF0000)>>16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (
		!(regEAC & BIT27) && /* अगर Tx is OK, check whether Rx is OK */
		(((regEA4 & 0x03FF0000)>>16) != 0x132) &&
		(((regEAC & 0x03FF0000)>>16) != 0x36) &&
		(((regEA4 & 0x03FF0000)>>16) < 0x110) &&
		(((regEA4 & 0x03FF0000)>>16) > 0xf0) &&
		(पंचांगp < 0xf)
	)
		result |= 0x02;
	अन्यथा							/* अगर Tx not OK, ignore Rx */
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Path A Rx IQK fail!!\n"));
	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 phy_PathB_IQK_8723B(काष्ठा adapter *padapter)
अणु
	u32 regEAC, regE94, regE9C, पंचांगp, Path_SEL_BB/*, regEC4, regECC, Path_SEL_BB*/;
	u8 result = 0x00;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Path B IQK!\n"));

	/*  Save RF Path */
	Path_SEL_BB = PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord);

    /* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/* 	in TXIQK mode */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x20000); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0003f); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xc7f87); */
	/* 	enable path B PA in TXIQK mode */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xed, 0x20, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x43, bRFRegOffsetMask, 0x30fc1);



	/* 1 Tx IQK */
	/* IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord, 0x01007c00);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK, bMaskDWord, 0x01004800);
	/* path-A IQK setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path-B IQK setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_B, bMaskDWord, 0x38008c1c);

/* 	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x82140114); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x821303ea);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x28110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_B, bMaskDWord, 0x82110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_B, bMaskDWord, 0x28110000);

	/* LO calibration setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Rsp, bMaskDWord, 0x00462911);

	/* enter IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* चयन to path B */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xb0, bRFRegOffsetMask, 0xeffe0); */

	/* GNT_BT = 0 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00000800);

	/* One shot, path B LOK & IQK */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path B LOK & IQK!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	/*  delay x ms */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path B LOK & IQK.\n", IQK_DELAY_TIME_88E)); */
	/* Platक्रमmStallExecution(IQK_DELAY_TIME_88E*1000); */
	mdelay(IQK_DELAY_TIME_8723B);

	/* restore Ant Path */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB);
	/* GNT_BT = 1 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00001800);

    /* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0x948 = 0x%x\n", PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord))); */


	/*  Check failed */
	regEAC = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord);
	regE94 = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord);
	regE9C = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe94 = 0x%x, 0xe9c = 0x%x\n", regE94, regE9C));
	/* monitor image घातer beक्रमe & after IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe90(before IQK) = 0x%x, 0xe98(afer IQK) = 0x%x\n",
	PHY_QueryBBReg(pDM_Odm->Adapter, 0xe90, bMaskDWord), PHY_QueryBBReg(pDM_Odm->Adapter, 0xe98, bMaskDWord)));

	/* Allen 20131125 */
	पंचांगp = (regE9C & 0x03FF0000)>>16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (
		!(regEAC & BIT28) &&
		(((regE94 & 0x03FF0000)>>16) != 0x142) &&
		(((regE9C & 0x03FF0000)>>16) != 0x42) &&
		(((regE94 & 0x03FF0000)>>16) < 0x110) &&
		(((regE94 & 0x03FF0000)>>16) > 0xf0) &&
		(पंचांगp < 0xf)
	)
		result |= 0x01;

	वापस result;
पूर्ण

/* bit0 = 1 => Tx OK, bit1 = 1 => Rx OK */
अटल u8 phy_PathB_RxIQK8723B(काष्ठा adapter *padapter, bool configPathB)
अणु
	u32 regE94, regE9C, regEA4, regEAC, u4पंचांगp, पंचांगp, Path_SEL_BB;
	u8 result = 0x00;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B Rx IQK!\n")); */

	/*  Save RF Path */
	Path_SEL_BB = PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord);
    /* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/* चयन to path B */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);

	/* 1 Get TXIMR setting */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B RX IQK:Get TXIMR setting!\n"));
	/* modअगरy RXIQK mode table */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path-A Rx IQK modify RXIQK mode table!\n")); */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x18000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0001f);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf7fb7);
	/* खोलो PA S1 & SMIXER */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xed, 0x20, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x43, bRFRegOffsetMask, 0x30fcd);


	/* IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord, 0x01007c00);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK, bMaskDWord, 0x01004800);


	/* path-B IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_B, bMaskDWord, 0x38008c1c);

/* 	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x82160c1f); */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x82130ff0);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x28110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_B, bMaskDWord, 0x82110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_B, bMaskDWord, 0x28110000);

	/* LO calibration setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Rsp, bMaskDWord, 0x0046a911);

    /* enter IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* चयन to path B */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xb0, bRFRegOffsetMask, 0xeffe0); */

	/* GNT_BT = 0 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00000800);

	/* One shot, path B TXIQK @ RXIQK */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path B LOK & IQK!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);


	/*  delay x ms */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_88E)); */
	/* Platक्रमmStallExecution(IQK_DELAY_TIME_88E*1000); */
	mdelay(IQK_DELAY_TIME_8723B);

	/* restore Ant Path */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB);
	/* GNT_BT = 1 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00001800);

    /* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/*  Check failed */
	regEAC = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord);
	regE94 = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord);
	regE9C = PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe94 = 0x%x, 0xe9c = 0x%x\n", regE94, regE9C));
	/* monitor image घातer beक्रमe & after IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe90(before IQK) = 0x%x, 0xe98(afer IQK) = 0x%x\n",
		PHY_QueryBBReg(pDM_Odm->Adapter, 0xe90, bMaskDWord), PHY_QueryBBReg(pDM_Odm->Adapter, 0xe98, bMaskDWord)));

	/* Allen 20131125 */
	पंचांगp = (regE9C & 0x03FF0000)>>16;
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("tmp1 = 0x%x\n", पंचांगp)); */
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("tmp2 = 0x%x\n", पंचांगp)); */

	अगर (
		!(regEAC & BIT28) &&
		(((regE94 & 0x03FF0000)>>16) != 0x142) &&
		(((regE9C & 0x03FF0000)>>16) != 0x42)  &&
		(((regE94 & 0x03FF0000)>>16) < 0x110) &&
		(((regE94 & 0x03FF0000)>>16) > 0xf0) &&
		(पंचांगp < 0xf)
	)
			result |= 0x01;
	अन्यथा	/* अगर Tx not OK, ignore Rx */
		वापस result;

	u4पंचांगp = 0x80007C00 | (regE94&0x3FF0000)  | ((regE9C&0x3FF0000) >> 16);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord, u4पंचांगp);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xe40 = 0x%x u4tmp = 0x%x\n", PHY_QueryBBReg(pDM_Odm->Adapter, rTx_IQK, bMaskDWord), u4पंचांगp));

	/* 1 RX IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B RX IQK\n"));

	/* modअगरy RXIQK mode table */
	/* 20121009, Kordan> RF Mode = 3 */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x18000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0001f);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf7d77);
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x0); */

	/* खोलो PA S1 & बंद SMIXER */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xed, 0x20, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x43, bRFRegOffsetMask, 0x30ebd);

	/* PA, PAD setting */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xdf, bRFRegOffsetMask, 0xf80); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x56, bRFRegOffsetMask, 0x51000); */

	/* IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK, bMaskDWord, 0x01004800);

	/* path-B IQK setting */
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x18008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_B, bMaskDWord, 0x38008c1c);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_B, bMaskDWord, 0x38008c1c);

	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_A, bMaskDWord, 0x82110000);
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x281604c2); */
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_A, bMaskDWord, 0x2813001f);
	PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_PI_B, bMaskDWord, 0x82110000);
	PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_PI_B, bMaskDWord, 0x28110000);

	/* LO calibration setting */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LO calibration setting!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Rsp, bMaskDWord, 0x0046a8d1);

    /* enter IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x808000);

	/* चयन to path B */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, 0x00000280);
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xb0, bRFRegOffsetMask, 0xeffe0); */

	/* GNT_BT = 0 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00000800);

	/* One shot, path B LOK & IQK */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("One shot, path B LOK & IQK!\n")); */
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf9000000);
	PHY_SetBBReg(pDM_Odm->Adapter, rIQK_AGC_Pts, bMaskDWord, 0xf8000000);

	/*  delay x ms */
/* 	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Delay %d ms for One shot, path A LOK & IQK.\n", IQK_DELAY_TIME_88E)); */
	/* Platक्रमmStallExecution(IQK_DELAY_TIME_88E*1000); */
	mdelay(IQK_DELAY_TIME_8723B);

	/* restore Ant Path */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB);
	/* GNT_BT = 1 */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, 0x00001800);

    /* leave IQK mode */
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);

	/*  Check failed */
	regEAC = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord);
	regEA4 = PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_Beक्रमe_IQK_A_2, bMaskDWord);

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("0xeac = 0x%x\n", regEAC));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xea4 = 0x%x, 0xeac = 0x%x\n", regEA4, regEAC));
	/* monitor image घातer beक्रमe & after IQK */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("0xea0(before IQK) = 0x%x, 0xea8(afer IQK) = 0x%x\n",
		PHY_QueryBBReg(pDM_Odm->Adapter, 0xea0, bMaskDWord), PHY_QueryBBReg(pDM_Odm->Adapter, 0xea8, bMaskDWord)));

	/* 	PA/PAD controlled by 0x0 */
	/* leave IQK mode */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, 0xffffff00, 0x00000000); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_B, 0xdf, bRFRegOffsetMask, 0x180); */



	/* Allen 20131125 */
	पंचांगp = (regEAC & 0x03FF0000)>>16;
	अगर ((पंचांगp & 0x200) > 0)
		पंचांगp = 0x400 - पंचांगp;

	अगर (
		!(regEAC & BIT27) && /* अगर Tx is OK, check whether Rx is OK */
		(((regEA4 & 0x03FF0000)>>16) != 0x132) &&
		(((regEAC & 0x03FF0000)>>16) != 0x36) &&
		(((regEA4 & 0x03FF0000)>>16) < 0x110) &&
		(((regEA4 & 0x03FF0000)>>16) > 0xf0) &&
		(पंचांगp < 0xf)
	)
		result |= 0x02;
	अन्यथा
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Path B Rx IQK fail!!\n"));

	वापस result;
पूर्ण

अटल व्योम _PHY_PathAFillIQKMatrix8723B(
	काष्ठा adapter *padapter,
	bool bIQKOK,
	s32 result[][8],
	u8 final_candidate,
	bool bTxOnly
)
अणु
	u32 Oldval_0, X, TX0_A, reg;
	s32 Y, TX0_C;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	काष्ठा odm_rf_cal_t *pRFCalibrateInfo = &pDM_Odm->RFCalibrateInfo;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Path A IQ Calibration %s !\n", (bIQKOK)?"Success":"Failed"));

	अगर (final_candidate == 0xFF)
		वापस;

	अन्यथा अगर (bIQKOK) अणु
		Oldval_0 = (PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, bMaskDWord) >> 22) & 0x3FF;

		X = result[final_candidate][0];
		अगर ((X & 0x00000200) != 0)
			X = X | 0xFFFFFC00;
		TX0_A = (X * Oldval_0) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("X = 0x%x, TX0_A = 0x%x, Oldval_0 0x%x\n", X, TX0_A, Oldval_0));
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, 0x3FF, TX0_A);

		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT(31), ((X*Oldval_0>>7) & 0x1));

		Y = result[final_candidate][1];
		अगर ((Y & 0x00000200) != 0)
			Y = Y | 0xFFFFFC00;

		/* 2 Tx IQC */
		TX0_C = (Y * Oldval_0) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Y = 0x%x, TX = 0x%x\n", Y, TX0_C));
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XCTxAFE, 0xF0000000, ((TX0_C&0x3C0)>>6));
		pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC94][KEY] = rOFDM0_XCTxAFE;
		pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC94][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XCTxAFE, bMaskDWord);

		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, 0x003F0000, (TX0_C&0x3F));
		pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][KEY] = rOFDM0_XATxIQImbalance;
		pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XATxIQImbalance, bMaskDWord);

		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT(29), ((Y*Oldval_0>>7) & 0x1));
		pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC4C][KEY] = rOFDM0_ECCAThreshold;
		pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC4C][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskDWord);

		अगर (bTxOnly) अणु
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("_PHY_PathAFillIQKMatrix8723B only Tx OK\n"));

			/*  <20130226, Kordan> Saving RxIQC, otherwise not initialized. */
			pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][KEY] = rOFDM0_RxIQExtAnta;
			pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][VAL] = 0xfffffff & PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_RxIQExtAnta, bMaskDWord);
			pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][KEY] = rOFDM0_XARxIQImbalance;
/* 			pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XARxIQImbalance, bMaskDWord); */
			pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][VAL] = 0x40000100;
			वापस;
		पूर्ण

		reg = result[final_candidate][2];

		/* 2 Rx IQC */
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XARxIQImbalance, 0x3FF, reg);
		reg = result[final_candidate][3] & 0x3F;
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XARxIQImbalance, 0xFC00, reg);
		pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][KEY] = rOFDM0_XARxIQImbalance;
		pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XARxIQImbalance, bMaskDWord);

		reg = (result[final_candidate][3] >> 6) & 0xF;
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_RxIQExtAnta, 0xF0000000, reg);
		pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][KEY] = rOFDM0_RxIQExtAnta;
		pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_RxIQExtAnta, bMaskDWord);

	पूर्ण
पूर्ण

अटल व्योम _PHY_PathBFillIQKMatrix8723B(
	काष्ठा adapter *padapter,
	bool bIQKOK,
	s32 result[][8],
	u8 final_candidate,
	bool bTxOnly /* करो Tx only */
)
अणु
	u32 Oldval_1, X, TX1_A, reg;
	s32	Y, TX1_C;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	काष्ठा odm_rf_cal_t *pRFCalibrateInfo = &pDM_Odm->RFCalibrateInfo;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B IQ Calibration %s !\n", (bIQKOK)?"Success":"Failed"));

	अगर (final_candidate == 0xFF)
		वापस;

	अन्यथा अगर (bIQKOK) अणु
		Oldval_1 = (PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, bMaskDWord) >> 22) & 0x3FF;

		X = result[final_candidate][4];
		अगर ((X & 0x00000200) != 0)
			X = X | 0xFFFFFC00;
		TX1_A = (X * Oldval_1) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("X = 0x%x, TX1_A = 0x%x\n", X, TX1_A));

		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, 0x3FF, TX1_A);

		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT(27), ((X*Oldval_1>>7) & 0x1));

		Y = result[final_candidate][5];
		अगर ((Y & 0x00000200) != 0)
			Y = Y | 0xFFFFFC00;

		TX1_C = (Y * Oldval_1) >> 8;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Y = 0x%x, TX1_C = 0x%x\n", Y, TX1_C));

		/* 2 Tx IQC */
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XDTxAFE, 0xF0000000, ((TX1_C&0x3C0)>>6));
/* 		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC9C][KEY] = rOFDM0_XDTxAFE; */
/* 		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC9C][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XDTxAFE, bMaskDWord); */
		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC94][KEY] = rOFDM0_XCTxAFE;
		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC94][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XDTxAFE, bMaskDWord);

		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, 0x003F0000, (TX1_C&0x3F));
		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][KEY] = rOFDM0_XATxIQImbalance;
		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XBTxIQImbalance, bMaskDWord);

		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, BIT(25), ((Y*Oldval_1>>7) & 0x1));
		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC4C][KEY] = rOFDM0_ECCAThreshold;
		pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC4C][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_ECCAThreshold, bMaskDWord);

		अगर (bTxOnly) अणु
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("_PHY_PathBFillIQKMatrix8723B only Tx OK\n"));

			pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][KEY] = rOFDM0_XARxIQImbalance;
/* 			pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XARxIQImbalance, bMaskDWord); */
			pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][VAL] = 0x40000100;
			pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][KEY] = rOFDM0_RxIQExtAnta;
			pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][VAL] = 0x0fffffff & PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_RxIQExtAnta, bMaskDWord);
			वापस;
		पूर्ण

		/* 2 Rx IQC */
		reg = result[final_candidate][6];
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBRxIQImbalance, 0x3FF, reg);
		reg = result[final_candidate][7] & 0x3F;
		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_XBRxIQImbalance, 0xFC00, reg);
		pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][KEY] = rOFDM0_XARxIQImbalance;
		pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][VAL] = PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_XBRxIQImbalance, bMaskDWord);

		reg = (result[final_candidate][7] >> 6) & 0xF;
/* 		PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_AGCRSSITable, 0x0000F000, reg); */
		pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][KEY] = rOFDM0_RxIQExtAnta;
		pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][VAL] = (reg << 28)|(PHY_QueryBBReg(pDM_Odm->Adapter, rOFDM0_RxIQExtAnta, bMaskDWord)&0x0fffffff);
	पूर्ण
पूर्ण

/*  */
/*  2011/07/26 MH Add an API क्रम testing IQK fail हाल. */
/*  */
/*  MP Alपढ़ोy declare in odm.c */

व्योम ODM_SetIQCbyRFpath(काष्ठा dm_odm_t *pDM_Odm, u32 RFpath)
अणु

	काष्ठा odm_rf_cal_t *pRFCalibrateInfo = &pDM_Odm->RFCalibrateInfo;

	अगर (
		(pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][VAL] != 0x0) &&
		(pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][VAL] != 0x0) &&
		(pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][VAL] != 0x0) &&
		(pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][VAL] != 0x0)
	) अणु
		अगर (RFpath) अणु /* S1: RFpath = 0, S0:RFpath = 1 */
			/* S0 TX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC94][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC94][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC80][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC4C][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S0][IDX_0xC4C][VAL]);
			/* S0 RX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xC14][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S0][IDX_0xCA0][VAL]);
		पूर्ण अन्यथा अणु
			/* S1 TX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC94][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC94][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC80][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC4C][KEY], bMaskDWord, pRFCalibrateInfo->TxIQC_8723B[PATH_S1][IDX_0xC4C][VAL]);
			/* S1 RX IQC */
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xC14][VAL]);
			PHY_SetBBReg(pDM_Odm->Adapter, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][KEY], bMaskDWord, pRFCalibrateInfo->RxIQC_8723B[PATH_S1][IDX_0xCA0][VAL]);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool ODM_CheckPowerStatus(काष्ठा adapter *Adapter)
अणु
	वापस true;
पूर्ण

अटल व्योम _PHY_SaveADDARegisters8723B(
	काष्ठा adapter *padapter,
	u32 *ADDAReg,
	u32 *ADDABackup,
	u32 RegisterNum
)
अणु
	u32 i;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	अगर (!ODM_CheckPowerStatus(padapter))
		वापस;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Save ADDA parameters.\n"));
	क्रम (i = 0 ; i < RegisterNum ; i++) अणु
		ADDABackup[i] = PHY_QueryBBReg(pDM_Odm->Adapter, ADDAReg[i], bMaskDWord);
	पूर्ण
पूर्ण


अटल व्योम _PHY_SaveMACRegisters8723B(
	काष्ठा adapter *padapter, u32 *MACReg, u32 *MACBackup
)
अणु
	u32 i;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Save MAC parameters.\n"));
	क्रम (i = 0 ; i < (IQK_MAC_REG_NUM - 1); i++) अणु
		MACBackup[i] = rtw_पढ़ो8(pDM_Odm->Adapter, MACReg[i]);
	पूर्ण
	MACBackup[i] = rtw_पढ़ो32(pDM_Odm->Adapter, MACReg[i]);

पूर्ण


अटल व्योम _PHY_ReloadADDARegisters8723B(
	काष्ठा adapter *padapter,
	u32 *ADDAReg,
	u32 *ADDABackup,
	u32 RegiesterNum
)
अणु
	u32 i;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Reload ADDA power saving parameters !\n"));
	क्रम (i = 0 ; i < RegiesterNum; i++) अणु
		PHY_SetBBReg(pDM_Odm->Adapter, ADDAReg[i], bMaskDWord, ADDABackup[i]);
	पूर्ण
पूर्ण

अटल व्योम _PHY_ReloadMACRegisters8723B(
	काष्ठा adapter *padapter, u32 *MACReg, u32 *MACBackup
)
अणु
	u32 i;

	क्रम (i = 0 ; i < (IQK_MAC_REG_NUM - 1); i++) अणु
		rtw_ग_लिखो8(padapter, MACReg[i], (u8)MACBackup[i]);
	पूर्ण
	rtw_ग_लिखो32(padapter, MACReg[i], MACBackup[i]);
पूर्ण


अटल व्योम _PHY_PathADDAOn8723B(
	काष्ठा adapter *padapter,
	u32 *ADDAReg,
	bool is2T
)
अणु
	u32 pathOn;
	u32 i;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("ADDA ON.\n"));

	pathOn = 0x01c00014;
	अगर (!is2T) अणु
		pathOn = 0x01c00014;
		PHY_SetBBReg(pDM_Odm->Adapter, ADDAReg[0], bMaskDWord, 0x01c00014);
	पूर्ण अन्यथा अणु
		PHY_SetBBReg(pDM_Odm->Adapter, ADDAReg[0], bMaskDWord, pathOn);
	पूर्ण

	क्रम (i = 1 ; i < IQK_ADDA_REG_NUM ; i++) अणु
		PHY_SetBBReg(pDM_Odm->Adapter, ADDAReg[i], bMaskDWord, pathOn);
	पूर्ण

पूर्ण

अटल व्योम _PHY_MACSettingCalibration8723B(
	काष्ठा adapter *padapter, u32 *MACReg, u32 *MACBackup
)
अणु
	u32 i = 0;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("MAC settings for Calibration.\n"));

	rtw_ग_लिखो8(pDM_Odm->Adapter, MACReg[i], 0x3F);

	क्रम (i = 1 ; i < (IQK_MAC_REG_NUM - 1); i++) अणु
		rtw_ग_लिखो8(pDM_Odm->Adapter, MACReg[i], (u8)(MACBackup[i]&(~BIT3)));
	पूर्ण
	rtw_ग_लिखो8(pDM_Odm->Adapter, MACReg[i], (u8)(MACBackup[i]&(~BIT5)));

पूर्ण

अटल bool phy_SimularityCompare_8723B(
	काष्ठा adapter *padapter,
	s32 result[][8],
	u8  c1,
	u8  c2
)
अणु
	u32 i, j, dअगरf, SimularityBitMap, bound = 0;
	u8 final_candidate[2] = अणु0xFF, 0xFFपूर्ण; /* क्रम path A and path B */
	bool bResult = true;
	s32 पंचांगp1 = 0, पंचांगp2 = 0;

	bound = 8;
	SimularityBitMap = 0;

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
			अगर ((i == 2 || i == 6) && !SimularityBitMap) अणु
				अगर (result[c1][i]+result[c1][i+1] == 0)
					final_candidate[(i/4)] = c2;
				अन्यथा अगर (result[c2][i]+result[c2][i+1] == 0)
					final_candidate[(i/4)] = c1;
				अन्यथा
					SimularityBitMap = SimularityBitMap|(1<<i);
			पूर्ण अन्यथा
				SimularityBitMap = SimularityBitMap|(1<<i);
		पूर्ण
	पूर्ण

	अगर (SimularityBitMap == 0) अणु
		क्रम (i = 0; i < (bound/4); i++) अणु
			अगर (final_candidate[i] != 0xFF) अणु
				क्रम (j = i*4; j < (i+1)*4-2; j++)
					result[3][j] = result[final_candidate[i]][j];
				bResult = false;
			पूर्ण
		पूर्ण
		वापस bResult;
	पूर्ण अन्यथा अणु

		अगर (!(SimularityBitMap & 0x03)) अणु /* path A TX OK */
			क्रम (i = 0; i < 2; i++)
				result[3][i] = result[c1][i];
		पूर्ण

		अगर (!(SimularityBitMap & 0x0c)) अणु /* path A RX OK */
			क्रम (i = 2; i < 4; i++)
				result[3][i] = result[c1][i];
		पूर्ण

		अगर (!(SimularityBitMap & 0x30)) अणु /* path B TX OK */
			क्रम (i = 4; i < 6; i++)
				result[3][i] = result[c1][i];
		पूर्ण

		अगर (!(SimularityBitMap & 0xc0)) अणु /* path B RX OK */
			क्रम (i = 6; i < 8; i++)
				result[3][i] = result[c1][i];
		पूर्ण
		वापस false;
	पूर्ण
पूर्ण



अटल व्योम phy_IQCalibrate_8723B(
	काष्ठा adapter *padapter,
	s32 result[][8],
	u8 t,
	bool is2T,
	u8 RF_Path
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	u32 i;
	u8 PathAOK, PathBOK;
	u8 पंचांगp0xc50 = (u8)PHY_QueryBBReg(pDM_Odm->Adapter, 0xC50, bMaskByte0);
	u8 पंचांगp0xc58 = (u8)PHY_QueryBBReg(pDM_Odm->Adapter, 0xC58, bMaskByte0);
	u32 ADDA_REG[IQK_ADDA_REG_NUM] = अणु
		rFPGA0_XCD_SwitchControl,
		rBlue_Tooth,
		rRx_Wait_CCA,
		rTx_CCK_RFON,
		rTx_CCK_BBON,
		rTx_OFDM_RFON,
		rTx_OFDM_BBON,
		rTx_To_Rx,
		rTx_To_Tx,
		rRx_CCK,
		rRx_OFDM,
		rRx_Wait_RIFS,
		rRx_TO_Rx,
		rStandby,
		rSleep,
		rPMPD_ANAEN
	पूर्ण;
	u32 IQK_MAC_REG[IQK_MAC_REG_NUM] = अणु
		REG_TXPAUSE,
		REG_BCN_CTRL,
		REG_BCN_CTRL_1,
		REG_GPIO_MUXCFG
	पूर्ण;

	/* since 92C & 92D have the dअगरferent define in IQK_BB_REG */
	u32 IQK_BB_REG_92C[IQK_BB_REG_NUM] = अणु
		rOFDM0_TRxPathEnable,
		rOFDM0_TRMuxPar,
		rFPGA0_XCD_RFInterfaceSW,
		rConfig_AntA,
		rConfig_AntB,
		rFPGA0_XAB_RFInterfaceSW,
		rFPGA0_XA_RFInterfaceOE,
		rFPGA0_XB_RFInterfaceOE,
		rCCK0_AFESetting
	पूर्ण;
	स्थिर u32 retryCount = 2;

	/*  Note: IQ calibration must be perक्रमmed after loading */
	/* 		PHY_REG.txt , and radio_a, radio_b.txt */

	/* u32 bbvalue; */

	अगर (t == 0) अणु
/* 		 bbvalue = PHY_QueryBBReg(pDM_Odm->Adapter, rFPGA0_RFMOD, bMaskDWord); */
/* 			RT_DISP(FINIT, INIT_IQK, ("phy_IQCalibrate_8188E() ==>0x%08x\n", bbvalue)); */

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQ Calibration for %s for %d times\n", (is2T ? "2T2R" : "1T1R"), t));

		/*  Save ADDA parameters, turn Path A ADDA on */
		_PHY_SaveADDARegisters8723B(padapter, ADDA_REG, pDM_Odm->RFCalibrateInfo.ADDA_backup, IQK_ADDA_REG_NUM);
		_PHY_SaveMACRegisters8723B(padapter, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);
		_PHY_SaveADDARegisters8723B(padapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup, IQK_BB_REG_NUM);
	पूर्ण
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQ Calibration for %s for %d times\n", (is2T ? "2T2R" : "1T1R"), t));

	_PHY_PathADDAOn8723B(padapter, ADDA_REG, is2T);

/* no serial mode */

	/* save RF path क्रम 8723B */
/* 	Path_SEL_BB = PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord); */
/* 	Path_SEL_RF = PHY_QueryRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xb0, 0xfffff); */

	/* MAC settings */
	_PHY_MACSettingCalibration8723B(padapter, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);

	/* BB setting */
	/* PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_RFMOD, BIT24, 0x00); */
	PHY_SetBBReg(pDM_Odm->Adapter, rCCK0_AFESetting, 0x0f000000, 0xf);
	PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_TRxPathEnable, bMaskDWord, 0x03a05600);
	PHY_SetBBReg(pDM_Odm->Adapter, rOFDM0_TRMuxPar, bMaskDWord, 0x000800e4);
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_XCD_RFInterfaceSW, bMaskDWord, 0x22204000);


/* 	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_XAB_RFInterfaceSW, BIT10, 0x01); */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_XAB_RFInterfaceSW, BIT26, 0x01); */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_XA_RFInterfaceOE, BIT10, 0x00); */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_XB_RFInterfaceOE, BIT10, 0x00); */


/* RX IQ calibration setting क्रम 8723B D cut large current issue when leaving IPS */

	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x30000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0001f);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xf7fb7);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xed, 0x20, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x43, bRFRegOffsetMask, 0x60fbd);

/* path A TX IQK */
	क्रम (i = 0 ; i < retryCount ; i++) अणु
		PathAOK = phy_PathA_IQK_8723B(padapter, is2T, RF_Path);
/* 		अगर (PathAOK == 0x03) अणु */
		अगर (PathAOK == 0x01) अणु
			/*  Path A Tx IQK Success */
			PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);
			pDM_Odm->RFCalibrateInfo.TxLOK[ODM_RF_PATH_A] = PHY_QueryRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x8, bRFRegOffsetMask);

			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A Tx IQK Success!!\n"));
				result[t][0] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord)&0x3FF0000)>>16;
				result[t][1] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord)&0x3FF0000)>>16;
			अवरोध;
		पूर्ण
	पूर्ण

/* path A RXIQK */
	क्रम (i = 0 ; i < retryCount ; i++) अणु
		PathAOK = phy_PathA_RxIQK8723B(padapter, is2T, RF_Path);
		अगर (PathAOK == 0x03) अणु
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Path A Rx IQK Success!!\n"));
/* 				result[t][0] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord)&0x3FF0000)>>16; */
/* 				result[t][1] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord)&0x3FF0000)>>16; */
				result[t][2] = (PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_Beक्रमe_IQK_A_2, bMaskDWord)&0x3FF0000)>>16;
				result[t][3] = (PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord)&0x3FF0000)>>16;
			अवरोध;
		पूर्ण अन्यथा अणु
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A Rx IQK Fail!!\n"));
		पूर्ण
	पूर्ण

	अगर (0x00 == PathAOK) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path A IQK failed!!\n"));
	पूर्ण

/* path B IQK */
	अगर (is2T) अणु

		/* path B TX IQK */
		क्रम (i = 0 ; i < retryCount ; i++) अणु
			PathBOK = phy_PathB_IQK_8723B(padapter);
			अगर (PathBOK == 0x01) अणु
				/*  Path B Tx IQK Success */
				PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0x000000);
				pDM_Odm->RFCalibrateInfo.TxLOK[ODM_RF_PATH_B] = PHY_QueryRFReg(pDM_Odm->Adapter, ODM_RF_PATH_B, 0x8, bRFRegOffsetMask);

				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B Tx IQK Success!!\n"));
				result[t][4] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord)&0x3FF0000)>>16;
				result[t][5] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord)&0x3FF0000)>>16;
				अवरोध;
			पूर्ण
		पूर्ण

/* path B RX IQK */
		क्रम (i = 0 ; i < retryCount ; i++) अणु
			PathBOK = phy_PathB_RxIQK8723B(padapter, is2T);
			अगर (PathBOK == 0x03) अणु
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("Path B Rx IQK Success!!\n"));
/* 				result[t][0] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_Beक्रमe_IQK_A, bMaskDWord)&0x3FF0000)>>16; */
/* 				result[t][1] = (PHY_QueryBBReg(pDM_Odm->Adapter, rTx_Power_After_IQK_A, bMaskDWord)&0x3FF0000)>>16; */
				result[t][6] = (PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_Beक्रमe_IQK_A_2, bMaskDWord)&0x3FF0000)>>16;
				result[t][7] = (PHY_QueryBBReg(pDM_Odm->Adapter, rRx_Power_After_IQK_A_2, bMaskDWord)&0x3FF0000)>>16;
				अवरोध;
			पूर्ण अन्यथा अणु
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B Rx IQK Fail!!\n"));
			पूर्ण
		पूर्ण

/* Allen end */
		अगर (0x00 == PathBOK) अणु
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("Path B IQK failed!!\n"));
		पूर्ण
	पूर्ण

	/* Back to BB mode, load original value */
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQK:Back to BB mode, load original value!\n"));
	PHY_SetBBReg(pDM_Odm->Adapter, rFPGA0_IQK, bMaskH3Bytes, 0);

	अगर (t != 0) अणु
		/*  Reload ADDA घातer saving parameters */
		_PHY_ReloadADDARegisters8723B(padapter, ADDA_REG, pDM_Odm->RFCalibrateInfo.ADDA_backup, IQK_ADDA_REG_NUM);

		/*  Reload MAC parameters */
		_PHY_ReloadMACRegisters8723B(padapter, IQK_MAC_REG, pDM_Odm->RFCalibrateInfo.IQK_MAC_backup);

		_PHY_ReloadADDARegisters8723B(padapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup, IQK_BB_REG_NUM);

		/* Reload RF path */
/* 		PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB); */
/* 		PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xb0, 0xfffff, Path_SEL_RF); */

		/* Allen initial gain 0xc50 */
		/*  Restore RX initial gain */
		PHY_SetBBReg(pDM_Odm->Adapter, 0xc50, bMaskByte0, 0x50);
		PHY_SetBBReg(pDM_Odm->Adapter, 0xc50, bMaskByte0, पंचांगp0xc50);
		अगर (is2T) अणु
			PHY_SetBBReg(pDM_Odm->Adapter, 0xc58, bMaskByte0, 0x50);
			PHY_SetBBReg(pDM_Odm->Adapter, 0xc58, bMaskByte0, पंचांगp0xc58);
		पूर्ण

		/* load 0xe30 IQC शेष value */
		PHY_SetBBReg(pDM_Odm->Adapter, rTx_IQK_Tone_A, bMaskDWord, 0x01008c00);
		PHY_SetBBReg(pDM_Odm->Adapter, rRx_IQK_Tone_A, bMaskDWord, 0x01008c00);

	पूर्ण
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("phy_IQCalibrate_8723B() <==\n"));

पूर्ण


अटल व्योम phy_LCCalibrate_8723B(काष्ठा dm_odm_t *pDM_Odm, bool is2T)
अणु
	u8 पंचांगpReg;
	u32 RF_Amode = 0, RF_Bmode = 0, LC_Cal;
	काष्ठा adapter *padapter = pDM_Odm->Adapter;

	/* Check continuous TX and Packet TX */
	पंचांगpReg = rtw_पढ़ो8(pDM_Odm->Adapter, 0xd03);

	अगर ((पंचांगpReg&0x70) != 0)			/* Deal with contisuous TX हाल */
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xd03, पंचांगpReg&0x8F);	/* disable all continuous TX */
	अन्यथा							/*  Deal with Packet TX हाल */
		rtw_ग_लिखो8(pDM_Odm->Adapter, REG_TXPAUSE, 0xFF);		/*  block all queues */

	अगर ((पंचांगpReg&0x70) != 0) अणु
		/* 1. Read original RF mode */
		/* Path-A */
		RF_Amode = PHY_QueryRFReg(padapter, ODM_RF_PATH_A, RF_AC, bMask12Bits);

		/* Path-B */
		अगर (is2T)
			RF_Bmode = PHY_QueryRFReg(padapter, ODM_RF_PATH_B, RF_AC, bMask12Bits);

		/* 2. Set RF mode = standby mode */
		/* Path-A */
		PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_AC, bMask12Bits, (RF_Amode&0x8FFFF)|0x10000);

		/* Path-B */
		अगर (is2T)
			PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_B, RF_AC, bMask12Bits, (RF_Bmode&0x8FFFF)|0x10000);
	पूर्ण

	/* 3. Read RF reg18 */
	LC_Cal = PHY_QueryRFReg(padapter, ODM_RF_PATH_A, RF_CHNLBW, bMask12Bits);

	/* 4. Set LC calibration begin	bit15 */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xB0, bRFRegOffsetMask, 0xDFBE0); /*  LDO ON */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_CHNLBW, bMask12Bits, LC_Cal|0x08000);

	mdelay(100);

	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xB0, bRFRegOffsetMask, 0xDFFE0); /*  LDO OFF */

	/*  Channel 10 LC calibration issue क्रम 8723bs with 26M xtal */
	अगर (pDM_Odm->SupportInterface == ODM_ITRF_SDIO && pDM_Odm->PackageType >= 0x2) अणु
		PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_CHNLBW, bMask12Bits, LC_Cal);
	पूर्ण

	/* Restore original situation */
	अगर ((पंचांगpReg&0x70) != 0) अणु /* Deal with contisuous TX हाल */
		/* Path-A */
		rtw_ग_लिखो8(pDM_Odm->Adapter, 0xd03, पंचांगpReg);
		PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_AC, bMask12Bits, RF_Amode);

		/* Path-B */
		अगर (is2T)
			PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_B, RF_AC, bMask12Bits, RF_Bmode);
	पूर्ण अन्यथा /*  Deal with Packet TX हाल */
		rtw_ग_लिखो8(pDM_Odm->Adapter, REG_TXPAUSE, 0x00);
पूर्ण

/* Analog Pre-distortion calibration */
#घोषणा		APK_BB_REG_NUM	8
#घोषणा		APK_CURVE_REG_NUM 4
#घोषणा		PATH_NUM		2

#घोषणा		DP_BB_REG_NUM		7
#घोषणा		DP_RF_REG_NUM		1
#घोषणा		DP_RETRY_LIMIT		10
#घोषणा		DP_PATH_NUM	2
#घोषणा		DP_DPK_NUM			3
#घोषणा		DP_DPK_VALUE_NUM	2



/* IQK version:V2.5    20140123 */
/* IQK is controlled by Is2ant, RF path */
व्योम PHY_IQCalibrate_8723B(
	काष्ठा adapter *padapter,
	bool bReCovery,
	bool bRestore,
	bool Is2ant,	/* false:1ant, true:2-ant */
	u8 RF_Path	/* 0:S1, 1:S0 */
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);

	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	s32 result[4][8];	/* last is final result */
	u8 i, final_candidate;
	bool bPathAOK, bPathBOK;
	s32 RegE94, RegE9C, RegEA4, RegEAC, RegEB4, RegEBC, RegEC4, RegECC, RegTmp = 0;
	bool is12simular, is13simular, is23simular;
	bool bSingleTone = false, bCarrierSuppression = false;
	u32 IQK_BB_REG_92C[IQK_BB_REG_NUM] = अणु
		rOFDM0_XARxIQImbalance,
		rOFDM0_XBRxIQImbalance,
		rOFDM0_ECCAThreshold,
		rOFDM0_AGCRSSITable,
		rOFDM0_XATxIQImbalance,
		rOFDM0_XBTxIQImbalance,
		rOFDM0_XCTxAFE,
		rOFDM0_XDTxAFE,
		rOFDM0_RxIQExtAnta
	पूर्ण;
/* 	u32 		Path_SEL_BB = 0; */
	u32 		GNT_BT_शेष;
	u32 		StartTime;
	s32			ProgressingTime;

	अगर (!ODM_CheckPowerStatus(padapter))
		वापस;

	अगर (!(pDM_Odm->SupportAbility & ODM_RF_CALIBRATION))
		वापस;

	/*  20120213<Kordan> Turn on when continuous Tx to pass lab testing. (required by Edlu) */
	अगर (bSingleTone || bCarrierSuppression)
		वापस;

#अगर DISABLE_BB_RF
	वापस;
#पूर्ण_अगर
	अगर (pDM_Odm->RFCalibrateInfo.bIQKInProgress)
		वापस;


	pDM_Odm->RFCalibrateInfo.bIQKInProgress = true;

	अगर (bRestore) अणु
		u32 offset, data;
		u8 path, bResult = SUCCESS;
		काष्ठा odm_rf_cal_t *pRFCalibrateInfo = &pDM_Odm->RFCalibrateInfo;

		path = (PHY_QueryBBReg(pDM_Odm->Adapter, rS0S1_PathSwitch, bMaskByte0) == 0x00) ? ODM_RF_PATH_A : ODM_RF_PATH_B;

		/*  Restore TX IQK */
		क्रम (i = 0; i < 3; ++i) अणु
			offset = pRFCalibrateInfo->TxIQC_8723B[path][i][0];
			data = pRFCalibrateInfo->TxIQC_8723B[path][i][1];
			अगर ((offset == 0) || (data == 0)) अणु
				bResult = FAIL;
				अवरोध;
			पूर्ण
			PHY_SetBBReg(pDM_Odm->Adapter, offset, bMaskDWord, data);
		पूर्ण

		/*  Restore RX IQK */
		क्रम (i = 0; i < 2; ++i) अणु
			offset = pRFCalibrateInfo->RxIQC_8723B[path][i][0];
			data = pRFCalibrateInfo->RxIQC_8723B[path][i][1];
			अगर ((offset == 0) || (data == 0)) अणु
				bResult = FAIL;
				अवरोध;
			पूर्ण
			PHY_SetBBReg(pDM_Odm->Adapter, offset, bMaskDWord, data);
		पूर्ण

		अगर (pDM_Odm->RFCalibrateInfo.TxLOK[ODM_RF_PATH_A] == 0) अणु
			bResult = FAIL;
		पूर्ण अन्यथा अणु
			PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXM_IDAC, bRFRegOffsetMask, pDM_Odm->RFCalibrateInfo.TxLOK[ODM_RF_PATH_A]);
			PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_B, RF_TXM_IDAC, bRFRegOffsetMask, pDM_Odm->RFCalibrateInfo.TxLOK[ODM_RF_PATH_B]);
		पूर्ण

		अगर (bResult == SUCCESS)
			वापस;
	पूर्ण

	अगर (bReCovery) अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_LOUD, ("PHY_IQCalibrate_8723B: Return due to bReCovery!\n"));
		_PHY_ReloadADDARegisters8723B(padapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);
		वापस;
	पूर्ण
	StartTime = jअगरfies;
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("IQK:Start!!!\n"));

	/* save शेष GNT_BT */
	GNT_BT_शेष = PHY_QueryBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord);
	/*  Save RF Path */
/* 	Path_SEL_BB = PHY_QueryBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord); */
/* 	Path_SEL_RF = PHY_QueryRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xb0, 0xfffff); */

    /* set GNT_BT = 0, छोड़ो BT traffic */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, BIT12, 0x0); */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, BIT11, 0x1); */


	क्रम (i = 0; i < 8; i++) अणु
		result[0][i] = 0;
		result[1][i] = 0;
		result[2][i] = 0;
		result[3][i] = 0;
	पूर्ण

	final_candidate = 0xff;
	bPathAOK = false;
	bPathBOK = false;
	is12simular = false;
	is23simular = false;
	is13simular = false;


	क्रम (i = 0; i < 3; i++) अणु
		phy_IQCalibrate_8723B(padapter, result, i, Is2ant, RF_Path);

		अगर (i == 1) अणु
			is12simular = phy_SimularityCompare_8723B(padapter, result, 0, 1);
			अगर (is12simular) अणु
				final_candidate = 0;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQK: is12simular final_candidate is %x\n", final_candidate));
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == 2) अणु
			is13simular = phy_SimularityCompare_8723B(padapter, result, 0, 2);
			अगर (is13simular) अणु
				final_candidate = 0;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQK: is13simular final_candidate is %x\n", final_candidate));

				अवरोध;
			पूर्ण

			is23simular = phy_SimularityCompare_8723B(padapter, result, 1, 2);
			अगर (is23simular) अणु
				final_candidate = 1;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQK: is23simular final_candidate is %x\n", final_candidate));
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < 8; i++)
					RegTmp += result[3][i];

				अगर (RegTmp != 0)
					final_candidate = 3;
				अन्यथा
					final_candidate = 0xFF;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 4; i++) अणु
		RegE94 = result[i][0];
		RegE9C = result[i][1];
		RegEA4 = result[i][2];
		RegEAC = result[i][3];
		RegEB4 = result[i][4];
		RegEBC = result[i][5];
		RegEC4 = result[i][6];
		RegECC = result[i][7];
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("IQK: RegE94 =%x RegE9C =%x RegEA4 =%x RegEAC =%x RegEB4 =%x RegEBC =%x RegEC4 =%x RegECC =%x\n ", RegE94, RegE9C, RegEA4, RegEAC, RegEB4, RegEBC, RegEC4, RegECC));
	पूर्ण

	अगर (final_candidate != 0xff) अणु
		pDM_Odm->RFCalibrateInfo.RegE94 = RegE94 = result[final_candidate][0];
		pDM_Odm->RFCalibrateInfo.RegE9C = RegE9C = result[final_candidate][1];
		RegEA4 = result[final_candidate][2];
		RegEAC = result[final_candidate][3];
		pDM_Odm->RFCalibrateInfo.RegEB4 = RegEB4 = result[final_candidate][4];
		pDM_Odm->RFCalibrateInfo.RegEBC = RegEBC = result[final_candidate][5];
		RegEC4 = result[final_candidate][6];
		RegECC = result[final_candidate][7];
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("IQK: final_candidate is %x\n", final_candidate));
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("IQK: RegE94 =%x RegE9C =%x RegEA4 =%x RegEAC =%x RegEB4 =%x RegEBC =%x RegEC4 =%x RegECC =%x\n ", RegE94, RegE9C, RegEA4, RegEAC, RegEB4, RegEBC, RegEC4, RegECC));
		bPathAOK = bPathBOK = true;
	पूर्ण अन्यथा अणु
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("IQK: FAIL use default value\n"));

		pDM_Odm->RFCalibrateInfo.RegE94 = pDM_Odm->RFCalibrateInfo.RegEB4 = 0x100;	/* X शेष value */
		pDM_Odm->RFCalibrateInfo.RegE9C = pDM_Odm->RFCalibrateInfo.RegEBC = 0x0;		/* Y शेष value */
	पूर्ण

	अणु
		अगर (RegE94 != 0)
			_PHY_PathAFillIQKMatrix8723B(padapter, bPathAOK, result, final_candidate, (RegEA4 == 0));
	पूर्ण
	अणु
		अगर (RegEB4 != 0)
			_PHY_PathBFillIQKMatrix8723B(padapter, bPathBOK, result, final_candidate, (RegEC4 == 0));
	पूर्ण

/* To Fix BSOD when final_candidate is 0xff */
/* by sherry 20120321 */
	अगर (final_candidate < 4) अणु
		क्रम (i = 0; i < IQK_Matrix_REG_NUM; i++)
			pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[0].Value[0][i] = result[final_candidate][i];
		pDM_Odm->RFCalibrateInfo.IQKMatrixRegSetting[0].bIQKDone = true;
	पूर्ण
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("\nIQK OK Indexforchannel %d.\n", 0));

	_PHY_SaveADDARegisters8723B(padapter, IQK_BB_REG_92C, pDM_Odm->RFCalibrateInfo.IQK_BB_backup_recover, 9);

	/* restore GNT_BT */
	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, bMaskDWord, GNT_BT_शेष);
	/*  Restore RF Path */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, 0x948, bMaskDWord, Path_SEL_BB); */
/* 	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xb0, 0xfffff, Path_SEL_RF); */

	/* Resotr RX mode table parameter */
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_WE_LUT, 0x80000, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_RCK_OS, bRFRegOffsetMask, 0x18000);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G1, bRFRegOffsetMask, 0x0001f);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, RF_TXPA_G2, bRFRegOffsetMask, 0xe6177);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0xed, 0x20, 0x1);
	PHY_SetRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, 0x43, bRFRegOffsetMask, 0x300bd);

	/* set GNT_BT = HW control */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, BIT12, 0x0); */
/* 	PHY_SetBBReg(pDM_Odm->Adapter, 0x764, BIT11, 0x0); */

	अगर (Is2ant) अणु
		अगर (RF_Path == 0x0)	/* S1 */
			ODM_SetIQCbyRFpath(pDM_Odm, 0);
		अन्यथा	/* S0 */
			ODM_SetIQCbyRFpath(pDM_Odm, 1);
	पूर्ण

	pDM_Odm->RFCalibrateInfo.bIQKInProgress = false;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("IQK finished\n"));
	ProgressingTime = jअगरfies_to_msecs(jअगरfies - StartTime);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("IQK ProgressingTime = %d\n", ProgressingTime));


पूर्ण


व्योम PHY_LCCalibrate_8723B(काष्ठा dm_odm_t *pDM_Odm)
अणु
	bool		bSingleTone = false, bCarrierSuppression = false;
	u32 		समयout = 2000, समयcount = 0;
	u32 		StartTime;
	s32			ProgressingTime;

#अगर DISABLE_BB_RF
	वापस;
#पूर्ण_अगर

	अगर (!(pDM_Odm->SupportAbility & ODM_RF_CALIBRATION))
		वापस;

	/*  20120213<Kordan> Turn on when continuous Tx to pass lab testing. (required by Edlu) */
	अगर (bSingleTone || bCarrierSuppression)
		वापस;

	StartTime = jअगरfies;
	जबतक (*(pDM_Odm->pbScanInProcess) && समयcount < समयout) अणु
		mdelay(50);
		समयcount += 50;
	पूर्ण

	pDM_Odm->RFCalibrateInfo.bLCKInProgress = true;


	phy_LCCalibrate_8723B(pDM_Odm, false);


	pDM_Odm->RFCalibrateInfo.bLCKInProgress = false;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD, ("LCK:Finish!!!interface %d\n", pDM_Odm->InterfaceIndex));
	ProgressingTime = jअगरfies_to_msecs(jअगरfies - StartTime);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_CALIBRATION, ODM_DBG_LOUD,  ("LCK ProgressingTime = %d\n", ProgressingTime));
पूर्ण
