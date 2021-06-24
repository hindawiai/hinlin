<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

/* include "Mp_Precomp.h" */
#समावेश "odm_precomp.h"


#घोषणा CALCULATE_SWINGTALBE_OFFSET(_offset, _direction, _size, _deltaThermal) \
	करो अणु\
		क्रम (_offset = 0; _offset < _size; _offset++) अणु\
			अगर (_deltaThermal < thermalThreshold[_direction][_offset]) अणु\
				अगर (_offset != 0)\
					_offset--;\
				अवरोध;\
			पूर्ण \
		पूर्ण \
		अगर (_offset >= _size)\
			_offset = _size-1;\
	पूर्ण जबतक (0)


व्योम ConfigureTxघातerTrack(काष्ठा dm_odm_t *pDM_Odm, काष्ठा txpwrtrack_cfg *pConfig)
अणु
	ConfigureTxघातerTrack_8723B(pConfig);
पूर्ण

/*  */
/*  <20121113, Kordan> This function should be called when TxAGC changed. */
/*  Otherwise the previous compensation is gone, because we record the */
/*  delta of temperature between two TxPowerTracking watch करोgs. */
/*  */
/*  NOTE: If Tx BB swing or Tx scaling is varअगरied during run-समय, still */
/*        need to call this function. */
/*  */
व्योम ODM_ClearTxPowerTrackingState(काष्ठा dm_odm_t *pDM_Odm)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(pDM_Odm->Adapter);
	u8 p = 0;

	pDM_Odm->BbSwingIdxCckBase = pDM_Odm->DefaultCckIndex;
	pDM_Odm->BbSwingIdxCck = pDM_Odm->DefaultCckIndex;
	pDM_Odm->RFCalibrateInfo.CCK_index = 0;

	क्रम (p = ODM_RF_PATH_A; p < MAX_RF_PATH; ++p) अणु
		pDM_Odm->BbSwingIdxOfdmBase[p] = pDM_Odm->DefaultOfdmIndex;
		pDM_Odm->BbSwingIdxOfdm[p] = pDM_Odm->DefaultOfdmIndex;
		pDM_Odm->RFCalibrateInfo.OFDM_index[p] = pDM_Odm->DefaultOfdmIndex;

		pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = 0;
		pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[p] = 0;
		pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[p] = 0;
		pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = 0;

		/*  Initial Mix mode घातer tracking */
		pDM_Odm->Absolute_OFDMSwingIdx[p] = 0;
		pDM_Odm->Remnant_OFDMSwingIdx[p] = 0;
	पूर्ण

	/* Initial at Modअगरy Tx Scaling Mode */
	pDM_Odm->Modअगरy_TxAGC_Flag_PathA = false;
	/* Initial at Modअगरy Tx Scaling Mode */
	pDM_Odm->Modअगरy_TxAGC_Flag_PathB = false;
	pDM_Odm->Remnant_CCKSwingIdx = 0;
	pDM_Odm->RFCalibrateInfo.ThermalValue = pHalData->EEPROMThermalMeter;
	pDM_Odm->RFCalibrateInfo.ThermalValue_IQK = pHalData->EEPROMThermalMeter;
	pDM_Odm->RFCalibrateInfo.ThermalValue_LCK = pHalData->EEPROMThermalMeter;
पूर्ण

व्योम ODM_TXPowerTrackingCallback_ThermalMeter(काष्ठा adapter *Adapter)
अणु

	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	u8 ThermalValue = 0, delta, delta_LCK, delta_IQK, p = 0, i = 0;
	u8 ThermalValue_AVG_count = 0;
	u32 ThermalValue_AVG = 0;

	u8 OFDM_min_index = 0;  /*  OFDM BB Swing should be less than +3.0dB, which is required by Arthur */
	u8 Indexक्रमchannel = 0; /*  GetRightChnlPlaceक्रमIQK(pHalData->CurrentChannel) */

	काष्ठा txpwrtrack_cfg c;


	/* 4 1. The following TWO tables decide the final index of OFDM/CCK swing table. */
	u8 *deltaSwingTableIdx_TUP_A;
	u8 *deltaSwingTableIdx_TDOWN_A;
	u8 *deltaSwingTableIdx_TUP_B;
	u8 *deltaSwingTableIdx_TDOWN_B;

	/* 4 2. Initialization (7 steps in total) */

	ConfigureTxघातerTrack(pDM_Odm, &c);

	(*c.GetDeltaSwingTable)(
		pDM_Odm,
		(u8 **)&deltaSwingTableIdx_TUP_A,
		(u8 **)&deltaSwingTableIdx_TDOWN_A,
		(u8 **)&deltaSwingTableIdx_TUP_B,
		(u8 **)&deltaSwingTableIdx_TDOWN_B
	);

	/* cosa add क्रम debug */
	pDM_Odm->RFCalibrateInfo.TXPowerTrackingCallbackCnt++;
	pDM_Odm->RFCalibrateInfo.bTXPowerTrackingInit = true;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_TX_PWR_TRACK,
		ODM_DBG_LOUD,
		(
			"===>ODM_TXPowerTrackingCallback_ThermalMeter,\npDM_Odm->BbSwingIdxCckBase: %d, pDM_Odm->BbSwingIdxOfdmBase[A]: %d, pDM_Odm->DefaultOfdmIndex: %d\n",
			pDM_Odm->BbSwingIdxCckBase,
			pDM_Odm->BbSwingIdxOfdmBase[ODM_RF_PATH_A],
			pDM_Odm->DefaultOfdmIndex
		)
	);

	ThermalValue = (u8)PHY_QueryRFReg(pDM_Odm->Adapter, ODM_RF_PATH_A, c.ThermalRegAddr, 0xfc00);	/* 0x42: RF Reg[15:10] 88E */
	अगर (
		!pDM_Odm->RFCalibrateInfo.TxPowerTrackControl ||
		pHalData->EEPROMThermalMeter == 0 ||
		pHalData->EEPROMThermalMeter == 0xFF
	)
		वापस;

	/* 4 3. Initialize ThermalValues of RFCalibrateInfo */

	अगर (pDM_Odm->RFCalibrateInfo.bReloadtxघातerindex)
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			("reload ofdm index for band switch\n")
		);

	/* 4 4. Calculate average thermal meter */

	pDM_Odm->RFCalibrateInfo.ThermalValue_AVG[pDM_Odm->RFCalibrateInfo.ThermalValue_AVG_index] = ThermalValue;
	pDM_Odm->RFCalibrateInfo.ThermalValue_AVG_index++;
	अगर (pDM_Odm->RFCalibrateInfo.ThermalValue_AVG_index == c.AverageThermalNum)   /* Average बार =  c.AverageThermalNum */
		pDM_Odm->RFCalibrateInfo.ThermalValue_AVG_index = 0;

	क्रम (i = 0; i < c.AverageThermalNum; i++) अणु
		अगर (pDM_Odm->RFCalibrateInfo.ThermalValue_AVG[i]) अणु
			ThermalValue_AVG += pDM_Odm->RFCalibrateInfo.ThermalValue_AVG[i];
			ThermalValue_AVG_count++;
		पूर्ण
	पूर्ण

	/* Calculate Average ThermalValue after average enough बार */
	अगर (ThermalValue_AVG_count) अणु
		ThermalValue = (u8)(ThermalValue_AVG / ThermalValue_AVG_count);
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_TX_PWR_TRACK,
			ODM_DBG_LOUD,
			(
				"AVG Thermal Meter = 0x%X, EFUSE Thermal Base = 0x%X\n",
				ThermalValue,
				pHalData->EEPROMThermalMeter
			)
		);
	पूर्ण

	/* 4 5. Calculate delta, delta_LCK, delta_IQK. */
	/* delta" here is used to determine whether thermal value changes or not. */
	delta =
		(ThermalValue > pDM_Odm->RFCalibrateInfo.ThermalValue) ?
		(ThermalValue - pDM_Odm->RFCalibrateInfo.ThermalValue) :
		(pDM_Odm->RFCalibrateInfo.ThermalValue - ThermalValue);
	delta_LCK =
		(ThermalValue > pDM_Odm->RFCalibrateInfo.ThermalValue_LCK) ?
		(ThermalValue - pDM_Odm->RFCalibrateInfo.ThermalValue_LCK) :
		(pDM_Odm->RFCalibrateInfo.ThermalValue_LCK - ThermalValue);
	delta_IQK =
		(ThermalValue > pDM_Odm->RFCalibrateInfo.ThermalValue_IQK) ?
		(ThermalValue - pDM_Odm->RFCalibrateInfo.ThermalValue_IQK) :
		(pDM_Odm->RFCalibrateInfo.ThermalValue_IQK - ThermalValue);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_TX_PWR_TRACK,
		ODM_DBG_LOUD,
		(
			"(delta, delta_LCK, delta_IQK) = (%d, %d, %d)\n",
			delta,
			delta_LCK,
			delta_IQK
		)
	);

	/* 4 6. If necessary, करो LCK. */
	/*  Delta temperature is equal to or larger than 20 centigrade. */
	अगर (delta_LCK >= c.Threshold_IQK) अणु
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_TX_PWR_TRACK,
			ODM_DBG_LOUD,
			(
				"delta_LCK(%d) >= Threshold_IQK(%d)\n",
				delta_LCK,
				c.Threshold_IQK
			)
		);
		pDM_Odm->RFCalibrateInfo.ThermalValue_LCK = ThermalValue;
		अगर (c.PHY_LCCalibrate)
			(*c.PHY_LCCalibrate)(pDM_Odm);
	पूर्ण

	/* 3 7. If necessary, move the index of swing table to adjust Tx घातer. */
	अगर (delta > 0 && pDM_Odm->RFCalibrateInfo.TxPowerTrackControl) अणु
		/* delta" here is used to record the असलolute value of dअगरference. */
		delta =
			ThermalValue > pHalData->EEPROMThermalMeter ?
			(ThermalValue - pHalData->EEPROMThermalMeter) :
			(pHalData->EEPROMThermalMeter - ThermalValue);

		अगर (delta >= TXPWR_TRACK_TABLE_SIZE)
			delta = TXPWR_TRACK_TABLE_SIZE - 1;

		/* 4 7.1 The Final Power Index = BaseIndex + PowerIndexOffset */
		अगर (ThermalValue > pHalData->EEPROMThermalMeter) अणु
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"deltaSwingTableIdx_TUP_A[%d] = %d\n",
					delta,
					deltaSwingTableIdx_TUP_A[delta]
				)
			);
			pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[ODM_RF_PATH_A] =
				pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_A];
			pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_A] =
				deltaSwingTableIdx_TUP_A[delta];

			/*  Record delta swing क्रम mix mode घातer tracking */
			pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] =
				deltaSwingTableIdx_TUP_A[delta];

			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"******Temp is higher and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
					pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A]
				)
			);

			अगर (c.RfPathCount > 1) अणु
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_TX_PWR_TRACK,
					ODM_DBG_LOUD,
					(
						"deltaSwingTableIdx_TUP_B[%d] = %d\n",
						delta,
						deltaSwingTableIdx_TUP_B[delta]
					)
				);
				pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[ODM_RF_PATH_B] =
					pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_B];
				pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_B] =
					deltaSwingTableIdx_TUP_B[delta];

				/*  Record delta swing क्रम mix mode घातer tracking */
				pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] =
					deltaSwingTableIdx_TUP_B[delta];
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_TX_PWR_TRACK,
					ODM_DBG_LOUD,
					(
						"******Temp is higher and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] = %d\n",
						pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B]
					)
				);
			पूर्ण

		पूर्ण अन्यथा अणु
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"deltaSwingTableIdx_TDOWN_A[%d] = %d\n",
					delta,
					deltaSwingTableIdx_TDOWN_A[delta]
				)
			);

			pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[ODM_RF_PATH_A] =
				pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_A];
			pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_A] =
				-1 * deltaSwingTableIdx_TDOWN_A[delta];

			/*  Record delta swing क्रम mix mode घातer tracking */
			pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] =
				-1 * deltaSwingTableIdx_TDOWN_A[delta];

			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"******Temp is lower and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
					pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A]
				)
			);

			अगर (c.RfPathCount > 1) अणु
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_TX_PWR_TRACK,
					ODM_DBG_LOUD,
					(
						"deltaSwingTableIdx_TDOWN_B[%d] = %d\n",
						delta,
						deltaSwingTableIdx_TDOWN_B[delta]
					)
				);

				pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[ODM_RF_PATH_B] =
					pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_B];
				pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[ODM_RF_PATH_B] =
					-1 * deltaSwingTableIdx_TDOWN_B[delta];

				 /*  Record delta swing क्रम mix mode घातer tracking */
				pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] =
					-1 * deltaSwingTableIdx_TDOWN_B[delta];

				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_TX_PWR_TRACK,
					ODM_DBG_LOUD,
					(
						"******Temp is lower and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] = %d\n",
						pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B]
					)
				);
			पूर्ण
		पूर्ण

		क्रम (p = ODM_RF_PATH_A; p < c.RfPathCount; p++) अणु
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"\n\n ================================ [Path-%c] Calculating PowerIndexOffset ================================\n",
					(p == ODM_RF_PATH_A ? 'A' : 'B')
				)
			);

			अगर (
				pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[p] ==
				pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[p]
			) /*  If Thermal value changes but lookup table value still the same */
				pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = 0;
			अन्यथा
				pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[p] - pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[p];      /*  Power Index Dअगरf between 2 बार Power Tracking */

			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"[Path-%c] PowerIndexOffset(%d) = DeltaPowerIndex(%d) - DeltaPowerIndexLast(%d)\n",
					(
						p == ODM_RF_PATH_A ? 'A' : 'B'),
						pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p],
						pDM_Odm->RFCalibrateInfo.DeltaPowerIndex[p],
						pDM_Odm->RFCalibrateInfo.DeltaPowerIndexLast[p]
					)
				);

			pDM_Odm->RFCalibrateInfo.OFDM_index[p] =
				pDM_Odm->BbSwingIdxOfdmBase[p] +
				pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p];

			pDM_Odm->RFCalibrateInfo.CCK_index =
				pDM_Odm->BbSwingIdxCckBase +
				pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p];

			pDM_Odm->BbSwingIdxCck =
				pDM_Odm->RFCalibrateInfo.CCK_index;

			pDM_Odm->BbSwingIdxOfdm[p] =
				pDM_Odm->RFCalibrateInfo.OFDM_index[p];

			/*  *************Prपूर्णांक BB Swing Base and Index Offset************* */
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"The 'CCK' final index(%d) = BaseIndex(%d) + PowerIndexOffset(%d)\n",
					pDM_Odm->BbSwingIdxCck,
					pDM_Odm->BbSwingIdxCckBase,
					pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p]
				)
			);
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"The 'OFDM' final index(%d) = BaseIndex[%c](%d) + PowerIndexOffset(%d)\n",
					pDM_Odm->BbSwingIdxOfdm[p],
					(p == ODM_RF_PATH_A ? 'A' : 'B'),
					pDM_Odm->BbSwingIdxOfdmBase[p],
					pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p]
				)
			);

			/* 4 7.1 Handle boundary conditions of index. */
			अगर (pDM_Odm->RFCalibrateInfo.OFDM_index[p] > c.SwingTableSize_OFDM-1)
				pDM_Odm->RFCalibrateInfo.OFDM_index[p] = c.SwingTableSize_OFDM-1;
			अन्यथा अगर (pDM_Odm->RFCalibrateInfo.OFDM_index[p] < OFDM_min_index)
				pDM_Odm->RFCalibrateInfo.OFDM_index[p] = OFDM_min_index;
		पूर्ण
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_TX_PWR_TRACK,
			ODM_DBG_LOUD,
			("\n\n ========================================================================================================\n")
		);
		अगर (pDM_Odm->RFCalibrateInfo.CCK_index > c.SwingTableSize_CCK-1)
			pDM_Odm->RFCalibrateInfo.CCK_index = c.SwingTableSize_CCK-1;
		/* अन्यथा अगर (pDM_Odm->RFCalibrateInfo.CCK_index < 0) */
			/* pDM_Odm->RFCalibrateInfo.CCK_index = 0; */
	पूर्ण अन्यथा अणु
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_TX_PWR_TRACK,
			ODM_DBG_LOUD,
			(
				"The thermal meter is unchanged or TxPowerTracking OFF(%d): ThermalValue: %d , pDM_Odm->RFCalibrateInfo.ThermalValue: %d\n",
				pDM_Odm->RFCalibrateInfo.TxPowerTrackControl,
				ThermalValue,
				pDM_Odm->RFCalibrateInfo.ThermalValue
			)
		);

			क्रम (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
				pDM_Odm->RFCalibrateInfo.PowerIndexOffset[p] = 0;
	पूर्ण
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_TX_PWR_TRACK,
		ODM_DBG_LOUD,
		(
			"TxPowerTracking: [CCK] Swing Current Index: %d, Swing Base Index: %d\n",
			pDM_Odm->RFCalibrateInfo.CCK_index,
			pDM_Odm->BbSwingIdxCckBase
		)
	);

	/* Prपूर्णांक Swing base & current */
	क्रम (p = ODM_RF_PATH_A; p < c.RfPathCount; p++) अणु
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_TX_PWR_TRACK,
			ODM_DBG_LOUD,
			(
				"TxPowerTracking: [OFDM] Swing Current Index: %d, Swing Base Index[%c]: %d\n",
				pDM_Odm->RFCalibrateInfo.OFDM_index[p],
				(p == ODM_RF_PATH_A ? 'A' : 'B'),
				pDM_Odm->BbSwingIdxOfdmBase[p]
			)
		);
	पूर्ण

	अगर (
		(pDM_Odm->RFCalibrateInfo.PowerIndexOffset[ODM_RF_PATH_A] != 0 ||
		 pDM_Odm->RFCalibrateInfo.PowerIndexOffset[ODM_RF_PATH_B] != 0) &&
		 pDM_Odm->RFCalibrateInfo.TxPowerTrackControl
	 ) अणु
		/* 4 7.2 Configure the Swing Table to adjust Tx Power. */

		pDM_Odm->RFCalibrateInfo.bTxPowerChanged = true; /*  Always true after Tx Power is adjusted by घातer tracking. */
		/*  */
		/*  2012/04/23 MH According to Luke's suggestion, we can not ग_लिखो BB digital */
		/*  to increase TX घातer. Otherwise, EVM will be bad. */
		/*  */
		/*  2012/04/25 MH Add क्रम tx घातer tracking to set tx घातer in tx agc क्रम 88E. */
		अगर (ThermalValue > pDM_Odm->RFCalibrateInfo.ThermalValue) अणु
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"Temperature Increasing(A): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
					pDM_Odm->RFCalibrateInfo.PowerIndexOffset[ODM_RF_PATH_A],
					delta,
					ThermalValue,
					pHalData->EEPROMThermalMeter,
					pDM_Odm->RFCalibrateInfo.ThermalValue
				)
			);

			अगर (c.RfPathCount > 1)
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_TX_PWR_TRACK,
					ODM_DBG_LOUD,
					(
						"Temperature Increasing(B): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
						pDM_Odm->RFCalibrateInfo.PowerIndexOffset[ODM_RF_PATH_B],
						delta,
						ThermalValue,
						pHalData->EEPROMThermalMeter,
						pDM_Odm->RFCalibrateInfo.ThermalValue
					)
				);

		पूर्ण अन्यथा अगर (ThermalValue < pDM_Odm->RFCalibrateInfo.ThermalValue) अणु /*  Low temperature */
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"Temperature Decreasing(A): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
					pDM_Odm->RFCalibrateInfo.PowerIndexOffset[ODM_RF_PATH_A],
					delta,
					ThermalValue,
					pHalData->EEPROMThermalMeter,
					pDM_Odm->RFCalibrateInfo.ThermalValue
				)
			);

			अगर (c.RfPathCount > 1)
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_TX_PWR_TRACK,
					ODM_DBG_LOUD,
					(
						"Temperature Decreasing(B): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
						pDM_Odm->RFCalibrateInfo.PowerIndexOffset[ODM_RF_PATH_B],
						delta,
						ThermalValue,
						pHalData->EEPROMThermalMeter,
						pDM_Odm->RFCalibrateInfo.ThermalValue
					)
				);

		पूर्ण

		अगर (ThermalValue > pHalData->EEPROMThermalMeter) अणु
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"Temperature(%d) higher than PG value(%d)\n",
					ThermalValue,
					pHalData->EEPROMThermalMeter
				)
			);

			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				("**********Enter POWER Tracking MIX_MODE**********\n")
			);
			क्रम (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
					(*c.ODM_TxPwrTrackSetPwr)(pDM_Odm, MIX_MODE, p, 0);
		पूर्ण अन्यथा अणु
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				(
					"Temperature(%d) lower than PG value(%d)\n",
					ThermalValue,
					pHalData->EEPROMThermalMeter
				)
			);

			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_TX_PWR_TRACK,
				ODM_DBG_LOUD,
				("**********Enter POWER Tracking MIX_MODE**********\n")
			);
			क्रम (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
				(*c.ODM_TxPwrTrackSetPwr)(pDM_Odm, MIX_MODE, p, Indexक्रमchannel);
		पूर्ण

		/*  Record last समय Power Tracking result as base. */
		pDM_Odm->BbSwingIdxCckBase = pDM_Odm->BbSwingIdxCck;
		क्रम (p = ODM_RF_PATH_A; p < c.RfPathCount; p++)
			pDM_Odm->BbSwingIdxOfdmBase[p] = pDM_Odm->BbSwingIdxOfdm[p];

		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_TX_PWR_TRACK, ODM_DBG_LOUD,
			(
				"pDM_Odm->RFCalibrateInfo.ThermalValue = %d ThermalValue = %d\n",
				pDM_Odm->RFCalibrateInfo.ThermalValue,
				ThermalValue
			)
		);

		/* Record last Power Tracking Thermal Value */
		pDM_Odm->RFCalibrateInfo.ThermalValue = ThermalValue;
	पूर्ण

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_TX_PWR_TRACK,
		ODM_DBG_LOUD,
		("<===ODM_TXPowerTrackingCallback_ThermalMeter\n")
	);

	pDM_Odm->RFCalibrateInfo.TXPowercount = 0;
पूर्ण
