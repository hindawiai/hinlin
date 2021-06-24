<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _HAL_COM_PHYCFG_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <hal_data.h>
#समावेश <linux/kernel.h>

u8 PHY_GetTxPowerByRateBase(काष्ठा adapter *Adapter, u8 Band, u8 RfPath,
			    u8 TxNum, क्रमागत rate_section RateSection)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	u8	value = 0;

	अगर (RfPath > ODM_RF_PATH_D)
		वापस 0;

	अगर (Band == BAND_ON_2_4G) अणु
		चयन (RateSection) अणु
		हाल CCK:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][0];
			अवरोध;
		हाल OFDM:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][1];
			अवरोध;
		हाल HT_MCS0_MCS7:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][2];
			अवरोध;
		हाल HT_MCS8_MCS15:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][3];
			अवरोध;
		हाल HT_MCS16_MCS23:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][4];
			अवरोध;
		हाल HT_MCS24_MCS31:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][5];
			अवरोध;
		हाल VHT_1SSMCS0_1SSMCS9:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][6];
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][7];
			अवरोध;
		हाल VHT_3SSMCS0_3SSMCS9:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][8];
			अवरोध;
		हाल VHT_4SSMCS0_4SSMCS9:
			value = pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][9];
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (Band == BAND_ON_5G) अणु
		चयन (RateSection) अणु
		हाल OFDM:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][0];
			अवरोध;
		हाल HT_MCS0_MCS7:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][1];
			अवरोध;
		हाल HT_MCS8_MCS15:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][2];
			अवरोध;
		हाल HT_MCS16_MCS23:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][3];
			अवरोध;
		हाल HT_MCS24_MCS31:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][4];
			अवरोध;
		हाल VHT_1SSMCS0_1SSMCS9:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][5];
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][6];
			अवरोध;
		हाल VHT_3SSMCS0_3SSMCS9:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][7];
			अवरोध;
		हाल VHT_4SSMCS0_4SSMCS9:
			value = pHalData->TxPwrByRateBase5G[RfPath][TxNum][8];
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस value;
पूर्ण

अटल व्योम
phy_SetTxPowerByRateBase(
	काष्ठा adapter *Adapter,
	u8 Band,
	u8 RfPath,
	क्रमागत rate_section	RateSection,
	u8 TxNum,
	u8 Value
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);

	अगर (RfPath > ODM_RF_PATH_D)
		वापस;

	अगर (Band == BAND_ON_2_4G) अणु
		चयन (RateSection) अणु
		हाल CCK:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][0] = Value;
			अवरोध;
		हाल OFDM:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][1] = Value;
			अवरोध;
		हाल HT_MCS0_MCS7:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][2] = Value;
			अवरोध;
		हाल HT_MCS8_MCS15:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][3] = Value;
			अवरोध;
		हाल HT_MCS16_MCS23:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][4] = Value;
			अवरोध;
		हाल HT_MCS24_MCS31:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][5] = Value;
			अवरोध;
		हाल VHT_1SSMCS0_1SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][6] = Value;
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][7] = Value;
			अवरोध;
		हाल VHT_3SSMCS0_3SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][8] = Value;
			अवरोध;
		हाल VHT_4SSMCS0_4SSMCS9:
			pHalData->TxPwrByRateBase2_4G[RfPath][TxNum][9] = Value;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (Band == BAND_ON_5G) अणु
		चयन (RateSection) अणु
		हाल OFDM:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][0] = Value;
			अवरोध;
		हाल HT_MCS0_MCS7:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][1] = Value;
			अवरोध;
		हाल HT_MCS8_MCS15:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][2] = Value;
			अवरोध;
		हाल HT_MCS16_MCS23:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][3] = Value;
			अवरोध;
		हाल HT_MCS24_MCS31:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][4] = Value;
			अवरोध;
		हाल VHT_1SSMCS0_1SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][5] = Value;
			अवरोध;
		हाल VHT_2SSMCS0_2SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][6] = Value;
			अवरोध;
		हाल VHT_3SSMCS0_3SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][7] = Value;
			अवरोध;
		हाल VHT_4SSMCS0_4SSMCS9:
			pHalData->TxPwrByRateBase5G[RfPath][TxNum][8] = Value;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
phy_StoreTxPowerByRateBase(
काष्ठा adapter *padapter
	)
अणु
	u8 path, base;

	क्रम (path = ODM_RF_PATH_A; path <= ODM_RF_PATH_B; ++path) अणु
		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_11M);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, CCK, RF_1TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_54M);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, OFDM, RF_1TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, HT_MCS0_MCS7, RF_1TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_2TX, MGN_MCS15);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, HT_MCS8_MCS15, RF_2TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_3TX, MGN_MCS23);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, HT_MCS16_MCS23, RF_3TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_1TX, MGN_VHT1SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, VHT_1SSMCS0_1SSMCS9, RF_1TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_2TX, MGN_VHT2SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, VHT_2SSMCS0_2SSMCS9, RF_2TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, path, RF_3TX, MGN_VHT3SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_2_4G, path, VHT_3SSMCS0_3SSMCS9, RF_3TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_1TX, MGN_54M);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, OFDM, RF_1TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_1TX, MGN_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, HT_MCS0_MCS7, RF_1TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_2TX, MGN_MCS15);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, HT_MCS8_MCS15, RF_2TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_3TX, MGN_MCS23);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, HT_MCS16_MCS23, RF_3TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_1TX, MGN_VHT1SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, VHT_1SSMCS0_1SSMCS9, RF_1TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_2TX, MGN_VHT2SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, VHT_2SSMCS0_2SSMCS9, RF_2TX, base);

		base = PHY_GetTxPowerByRate(padapter, BAND_ON_5G, path, RF_3TX, MGN_VHT2SS_MCS7);
		phy_SetTxPowerByRateBase(padapter, BAND_ON_5G, path, VHT_3SSMCS0_3SSMCS9, RF_3TX, base);
	पूर्ण
पूर्ण

u8 PHY_GetRateSectionIndexOfTxPowerByRate(
	काष्ठा adapter *padapter, u32 RegAddr, u32 BitMask
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;
	u8	index = 0;

	अगर (pDM_Odm->PhyRegPgVersion == 0) अणु
		चयन (RegAddr) अणु
		हाल rTxAGC_A_Rate18_06:
			index = 0;
			अवरोध;
		हाल rTxAGC_A_Rate54_24:
			index = 1;
			अवरोध;
		हाल rTxAGC_A_CCK1_Mcs32:
			index = 6;
			अवरोध;
		हाल rTxAGC_B_CCK11_A_CCK2_11:
			अगर (BitMask == bMaskH3Bytes)
				index = 7;
			अन्यथा अगर (BitMask == 0x000000ff)
				index = 15;
			अवरोध;

		हाल rTxAGC_A_Mcs03_Mcs00:
			index = 2;
			अवरोध;
		हाल rTxAGC_A_Mcs07_Mcs04:
			index = 3;
			अवरोध;
		हाल rTxAGC_A_Mcs11_Mcs08:
			index = 4;
			अवरोध;
		हाल rTxAGC_A_Mcs15_Mcs12:
			index = 5;
			अवरोध;
		हाल rTxAGC_B_Rate18_06:
			index = 8;
			अवरोध;
		हाल rTxAGC_B_Rate54_24:
			index = 9;
			अवरोध;
		हाल rTxAGC_B_CCK1_55_Mcs32:
			index = 14;
			अवरोध;
		हाल rTxAGC_B_Mcs03_Mcs00:
			index = 10;
			अवरोध;
		हाल rTxAGC_B_Mcs07_Mcs04:
			index = 11;
			अवरोध;
		हाल rTxAGC_B_Mcs11_Mcs08:
			index = 12;
			अवरोध;
		हाल rTxAGC_B_Mcs15_Mcs12:
			index = 13;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस index;
पूर्ण

व्योम
PHY_GetRateValuesOfTxPowerByRate(
	काष्ठा adapter *padapter,
	u32	RegAddr,
	u32	BitMask,
	u32	Value,
	u8 *RateIndex,
	s8 *PwrByRateVal,
	u8 *RateNum
)
अणु
	u8 i = 0;

	चयन (RegAddr) अणु
	हाल rTxAGC_A_Rate18_06:
	हाल rTxAGC_B_Rate18_06:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_6M);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_9M);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_12M);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_18M);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल rTxAGC_A_Rate54_24:
	हाल rTxAGC_B_Rate54_24:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_24M);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_36M);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_48M);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_54M);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल rTxAGC_A_CCK1_Mcs32:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_1M);
		PwrByRateVal[0] = (s8) ((((Value >> (8 + 4)) & 0xF)) * 10 +
										((Value >> 8) & 0xF));
		*RateNum = 1;
		अवरोध;

	हाल rTxAGC_B_CCK11_A_CCK2_11:
		अगर (BitMask == 0xffffff00) अणु
			RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_2M);
			RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_5_5M);
			RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_11M);
			क्रम (i = 1; i < 4; ++i) अणु
				PwrByRateVal[i - 1] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
												((Value >> (i * 8)) & 0xF));
			पूर्ण
			*RateNum = 3;
		पूर्ण अन्यथा अगर (BitMask == 0x000000ff) अणु
			RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_11M);
			PwrByRateVal[0] = (s8) ((((Value >> 4) & 0xF)) * 10 + (Value & 0xF));
			*RateNum = 1;
		पूर्ण
		अवरोध;

	हाल rTxAGC_A_Mcs03_Mcs00:
	हाल rTxAGC_B_Mcs03_Mcs00:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS0);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS1);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS2);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS3);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल rTxAGC_A_Mcs07_Mcs04:
	हाल rTxAGC_B_Mcs07_Mcs04:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS4);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS5);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS6);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS7);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल rTxAGC_A_Mcs11_Mcs08:
	हाल rTxAGC_B_Mcs11_Mcs08:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS8);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS9);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS10);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS11);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल rTxAGC_A_Mcs15_Mcs12:
	हाल rTxAGC_B_Mcs15_Mcs12:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS12);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS13);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS14);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS15);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;

		अवरोध;

	हाल rTxAGC_B_CCK1_55_Mcs32:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_1M);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_2M);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_5_5M);
		क्रम (i = 1; i < 4; ++i) अणु
			PwrByRateVal[i - 1] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 3;
		अवरोध;

	हाल 0xC20:
	हाल 0xE20:
	हाल 0x1820:
	हाल 0x1a20:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_1M);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_2M);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_5_5M);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_11M);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC24:
	हाल 0xE24:
	हाल 0x1824:
	हाल 0x1a24:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_6M);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_9M);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_12M);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_18M);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC28:
	हाल 0xE28:
	हाल 0x1828:
	हाल 0x1a28:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_24M);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_36M);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_48M);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_54M);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC2C:
	हाल 0xE2C:
	हाल 0x182C:
	हाल 0x1a2C:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS0);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS1);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS2);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS3);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC30:
	हाल 0xE30:
	हाल 0x1830:
	हाल 0x1a30:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS4);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS5);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS6);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS7);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC34:
	हाल 0xE34:
	हाल 0x1834:
	हाल 0x1a34:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS8);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS9);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS10);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS11);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC38:
	हाल 0xE38:
	हाल 0x1838:
	हाल 0x1a38:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS12);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS13);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS14);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS15);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC3C:
	हाल 0xE3C:
	हाल 0x183C:
	हाल 0x1a3C:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS0);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS1);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS2);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS3);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC40:
	हाल 0xE40:
	हाल 0x1840:
	हाल 0x1a40:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS4);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS5);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS6);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS7);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC44:
	हाल 0xE44:
	हाल 0x1844:
	हाल 0x1a44:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS8);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT1SS_MCS9);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS0);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS1);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC48:
	हाल 0xE48:
	हाल 0x1848:
	हाल 0x1a48:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS2);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS3);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS4);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS5);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xC4C:
	हाल 0xE4C:
	हाल 0x184C:
	हाल 0x1a4C:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS6);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS7);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS8);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS9);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xCD8:
	हाल 0xED8:
	हाल 0x18D8:
	हाल 0x1aD8:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS16);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS17);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS18);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS19);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xCDC:
	हाल 0xEDC:
	हाल 0x18DC:
	हाल 0x1aDC:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS20);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS21);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS22);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_MCS23);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xCE0:
	हाल 0xEE0:
	हाल 0x18E0:
	हाल 0x1aE0:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS0);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS1);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS2);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS3);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xCE4:
	हाल 0xEE4:
	हाल 0x18E4:
	हाल 0x1aE4:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS4);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS5);
		RateIndex[2] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS6);
		RateIndex[3] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS7);
		क्रम (i = 0; i < 4; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	हाल 0xCE8:
	हाल 0xEE8:
	हाल 0x18E8:
	हाल 0x1aE8:
		RateIndex[0] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS8);
		RateIndex[1] = PHY_GetRateIndexOfTxPowerByRate(MGN_VHT3SS_MCS9);
		क्रम (i = 0; i < 2; ++i) अणु
			PwrByRateVal[i] = (s8) ((((Value >> (i * 8 + 4)) & 0xF)) * 10 +
											((Value >> (i * 8)) & 0xF));
		पूर्ण
		*RateNum = 4;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम PHY_StoreTxPowerByRateNew(
	काष्ठा adapter *padapter,
	u32	Band,
	u32	RfPath,
	u32	TxNum,
	u32	RegAddr,
	u32	BitMask,
	u32	Data
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 i = 0, rateIndex[4] = अणु0पूर्ण, rateNum = 0;
	s8	PwrByRateVal[4] = अणु0पूर्ण;

	PHY_GetRateValuesOfTxPowerByRate(padapter, RegAddr, BitMask, Data, rateIndex, PwrByRateVal, &rateNum);

	अगर (Band != BAND_ON_2_4G && Band != BAND_ON_5G)
		वापस;

	अगर (RfPath > ODM_RF_PATH_D)
		वापस;

	अगर (TxNum > ODM_RF_PATH_D)
		वापस;

	क्रम (i = 0; i < rateNum; ++i) अणु
		अगर (rateIndex[i] == PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS0) ||
			 rateIndex[i] == PHY_GetRateIndexOfTxPowerByRate(MGN_VHT2SS_MCS1))
			TxNum = RF_2TX;

		pHalData->TxPwrByRateOffset[Band][RfPath][TxNum][rateIndex[i]] = PwrByRateVal[i];
	पूर्ण
पूर्ण

अटल व्योम PHY_StoreTxPowerByRateOld(
	काष्ठा adapter *padapter, u32	RegAddr, u32 BitMask, u32 Data
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8	index = PHY_GetRateSectionIndexOfTxPowerByRate(padapter, RegAddr, BitMask);

	pHalData->MCSTxPowerLevelOriginalOffset[pHalData->pwrGroupCnt][index] = Data;
पूर्ण

व्योम PHY_InitTxPowerByRate(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 band, rfPath, TxNum, rate;

	क्रम (band = BAND_ON_2_4G; band <= BAND_ON_5G; ++band)
			क्रम (rfPath = 0; rfPath < TX_PWR_BY_RATE_NUM_RF; ++rfPath)
				क्रम (TxNum = 0; TxNum < TX_PWR_BY_RATE_NUM_RF; ++TxNum)
					क्रम (rate = 0; rate < TX_PWR_BY_RATE_NUM_RATE; ++rate)
						pHalData->TxPwrByRateOffset[band][rfPath][TxNum][rate] = 0;
पूर्ण

व्योम PHY_StoreTxPowerByRate(
	काष्ठा adapter *padapter,
	u32	Band,
	u32	RfPath,
	u32	TxNum,
	u32	RegAddr,
	u32	BitMask,
	u32	Data
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;

	अगर (pDM_Odm->PhyRegPgVersion > 0)
		PHY_StoreTxPowerByRateNew(padapter, Band, RfPath, TxNum, RegAddr, BitMask, Data);
	अन्यथा अगर (pDM_Odm->PhyRegPgVersion == 0) अणु
		PHY_StoreTxPowerByRateOld(padapter, RegAddr, BitMask, Data);

		अगर (RegAddr == rTxAGC_A_Mcs15_Mcs12 && pHalData->rf_type == RF_1T1R)
			pHalData->pwrGroupCnt++;
		अन्यथा अगर (RegAddr == rTxAGC_B_Mcs15_Mcs12 && pHalData->rf_type != RF_1T1R)
			pHalData->pwrGroupCnt++;
	पूर्ण
पूर्ण

अटल व्योम
phy_ConvertTxPowerByRateInDbmToRelativeValues(
काष्ठा adapter *padapter
	)
अणु
	u8	base = 0, i = 0, value = 0, band = 0, path = 0, txNum = 0;
	u8	cckRates[4] = अणु
		MGN_1M, MGN_2M, MGN_5_5M, MGN_11M
	पूर्ण;
	u8	ofdmRates[8] = अणु
		MGN_6M, MGN_9M, MGN_12M, MGN_18M, MGN_24M, MGN_36M, MGN_48M, MGN_54M
	पूर्ण;
	u8 mcs0_7Rates[8] = अणु
		MGN_MCS0, MGN_MCS1, MGN_MCS2, MGN_MCS3, MGN_MCS4, MGN_MCS5, MGN_MCS6, MGN_MCS7
	पूर्ण;
	u8 mcs8_15Rates[8] = अणु
		MGN_MCS8, MGN_MCS9, MGN_MCS10, MGN_MCS11, MGN_MCS12, MGN_MCS13, MGN_MCS14, MGN_MCS15
	पूर्ण;
	u8 mcs16_23Rates[8] = अणु
		MGN_MCS16, MGN_MCS17, MGN_MCS18, MGN_MCS19, MGN_MCS20, MGN_MCS21, MGN_MCS22, MGN_MCS23
	पूर्ण;
	u8 vht1ssRates[10] = अणु
		MGN_VHT1SS_MCS0, MGN_VHT1SS_MCS1, MGN_VHT1SS_MCS2, MGN_VHT1SS_MCS3, MGN_VHT1SS_MCS4,
		MGN_VHT1SS_MCS5, MGN_VHT1SS_MCS6, MGN_VHT1SS_MCS7, MGN_VHT1SS_MCS8, MGN_VHT1SS_MCS9
	पूर्ण;
	u8 vht2ssRates[10] = अणु
		MGN_VHT2SS_MCS0, MGN_VHT2SS_MCS1, MGN_VHT2SS_MCS2, MGN_VHT2SS_MCS3, MGN_VHT2SS_MCS4,
		MGN_VHT2SS_MCS5, MGN_VHT2SS_MCS6, MGN_VHT2SS_MCS7, MGN_VHT2SS_MCS8, MGN_VHT2SS_MCS9
	पूर्ण;
	u8 vht3ssRates[10] = अणु
		MGN_VHT3SS_MCS0, MGN_VHT3SS_MCS1, MGN_VHT3SS_MCS2, MGN_VHT3SS_MCS3, MGN_VHT3SS_MCS4,
		MGN_VHT3SS_MCS5, MGN_VHT3SS_MCS6, MGN_VHT3SS_MCS7, MGN_VHT3SS_MCS8, MGN_VHT3SS_MCS9
	पूर्ण;

	क्रम (band = BAND_ON_2_4G; band <= BAND_ON_5G; ++band) अणु
		क्रम (path = ODM_RF_PATH_A; path <= ODM_RF_PATH_D; ++path) अणु
			क्रम (txNum = RF_1TX; txNum < RF_MAX_TX_NUM; ++txNum) अणु
				/*  CCK */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_11M);
				क्रम (i = 0; i < ARRAY_SIZE(cckRates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, cckRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, cckRates[i], value - base);
				पूर्ण

				/*  OFDM */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_54M);
				क्रम (i = 0; i < माप(ofdmRates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, ofdmRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, ofdmRates[i], value - base);
				पूर्ण

				/*  HT MCS0~7 */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_MCS7);
				क्रम (i = 0; i < माप(mcs0_7Rates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, mcs0_7Rates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, mcs0_7Rates[i], value - base);
				पूर्ण

				/*  HT MCS8~15 */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_MCS15);
				क्रम (i = 0; i < माप(mcs8_15Rates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, mcs8_15Rates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, mcs8_15Rates[i], value - base);
				पूर्ण

				/*  HT MCS16~23 */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_MCS23);
				क्रम (i = 0; i < माप(mcs16_23Rates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, mcs16_23Rates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, mcs16_23Rates[i], value - base);
				पूर्ण

				/*  VHT 1SS */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_VHT1SS_MCS7);
				क्रम (i = 0; i < माप(vht1ssRates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, vht1ssRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, vht1ssRates[i], value - base);
				पूर्ण

				/*  VHT 2SS */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_VHT2SS_MCS7);
				क्रम (i = 0; i < माप(vht2ssRates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, vht2ssRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, vht2ssRates[i], value - base);
				पूर्ण

				/*  VHT 3SS */
				base = PHY_GetTxPowerByRate(padapter, band, path, txNum, MGN_VHT3SS_MCS7);
				क्रम (i = 0; i < माप(vht3ssRates); ++i) अणु
					value = PHY_GetTxPowerByRate(padapter, band, path, txNum, vht3ssRates[i]);
					PHY_SetTxPowerByRate(padapter, band, path, txNum, vht3ssRates[i], value - base);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
  * This function must be called अगर the value in the PHY_REG_PG.txt(or header)
  * is exact dBm values
  */
व्योम PHY_TxPowerByRateConfiguration(काष्ठा adapter *padapter)
अणु
	phy_StoreTxPowerByRateBase(padapter);
	phy_ConvertTxPowerByRateInDbmToRelativeValues(padapter);
पूर्ण

व्योम PHY_SetTxPowerIndexByRateSection(
	काष्ठा adapter *padapter, u8 RFPath, u8 Channel, u8 RateSection
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	अगर (RateSection == CCK) अणु
		u8 cckRates[]   = अणुMGN_1M, MGN_2M, MGN_5_5M, MGN_11Mपूर्ण;
		अगर (pHalData->CurrentBandType == BAND_ON_2_4G)
			PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
						     pHalData->CurrentChannelBW,
						     Channel, cckRates,
						     ARRAY_SIZE(cckRates));

	पूर्ण अन्यथा अगर (RateSection == OFDM) अणु
		u8 ofdmRates[]  = अणुMGN_6M, MGN_9M, MGN_12M, MGN_18M, MGN_24M, MGN_36M, MGN_48M, MGN_54Mपूर्ण;
		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, ofdmRates,
					       ARRAY_SIZE(ofdmRates));

	पूर्ण अन्यथा अगर (RateSection == HT_MCS0_MCS7) अणु
		u8 htRates1T[]  = अणुMGN_MCS0, MGN_MCS1, MGN_MCS2, MGN_MCS3, MGN_MCS4, MGN_MCS5, MGN_MCS6, MGN_MCS7पूर्ण;
		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, htRates1T,
					       ARRAY_SIZE(htRates1T));

	पूर्ण अन्यथा अगर (RateSection == HT_MCS8_MCS15) अणु
		u8 htRates2T[]  = अणुMGN_MCS8, MGN_MCS9, MGN_MCS10, MGN_MCS11, MGN_MCS12, MGN_MCS13, MGN_MCS14, MGN_MCS15पूर्ण;
		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, htRates2T,
					       ARRAY_SIZE(htRates2T));

	पूर्ण अन्यथा अगर (RateSection == HT_MCS16_MCS23) अणु
		u8 htRates3T[]  = अणुMGN_MCS16, MGN_MCS17, MGN_MCS18, MGN_MCS19, MGN_MCS20, MGN_MCS21, MGN_MCS22, MGN_MCS23पूर्ण;
		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, htRates3T,
					       ARRAY_SIZE(htRates3T));

	पूर्ण अन्यथा अगर (RateSection == HT_MCS24_MCS31) अणु
		u8 htRates4T[]  = अणुMGN_MCS24, MGN_MCS25, MGN_MCS26, MGN_MCS27, MGN_MCS28, MGN_MCS29, MGN_MCS30, MGN_MCS31पूर्ण;
		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, htRates4T,
					       ARRAY_SIZE(htRates4T));

	पूर्ण अन्यथा अगर (RateSection == VHT_1SSMCS0_1SSMCS9) अणु
		u8 vhtRates1T[] = अणुMGN_VHT1SS_MCS0, MGN_VHT1SS_MCS1, MGN_VHT1SS_MCS2, MGN_VHT1SS_MCS3, MGN_VHT1SS_MCS4,
				MGN_VHT1SS_MCS5, MGN_VHT1SS_MCS6, MGN_VHT1SS_MCS7, MGN_VHT1SS_MCS8, MGN_VHT1SS_MCS9पूर्ण;
		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, vhtRates1T,
					       ARRAY_SIZE(vhtRates1T));

	पूर्ण अन्यथा अगर (RateSection == VHT_2SSMCS0_2SSMCS9) अणु
		u8 vhtRates2T[] = अणुMGN_VHT2SS_MCS0, MGN_VHT2SS_MCS1, MGN_VHT2SS_MCS2, MGN_VHT2SS_MCS3, MGN_VHT2SS_MCS4,
				MGN_VHT2SS_MCS5, MGN_VHT2SS_MCS6, MGN_VHT2SS_MCS7, MGN_VHT2SS_MCS8, MGN_VHT2SS_MCS9पूर्ण;

		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, vhtRates2T,
					       ARRAY_SIZE(vhtRates2T));
	पूर्ण अन्यथा अगर (RateSection == VHT_3SSMCS0_3SSMCS9) अणु
		u8 vhtRates3T[] = अणुMGN_VHT3SS_MCS0, MGN_VHT3SS_MCS1, MGN_VHT3SS_MCS2, MGN_VHT3SS_MCS3, MGN_VHT3SS_MCS4,
				MGN_VHT3SS_MCS5, MGN_VHT3SS_MCS6, MGN_VHT3SS_MCS7, MGN_VHT3SS_MCS8, MGN_VHT3SS_MCS9पूर्ण;

		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, vhtRates3T,
					       ARRAY_SIZE(vhtRates3T));
	पूर्ण अन्यथा अगर (RateSection == VHT_4SSMCS0_4SSMCS9) अणु
		u8 vhtRates4T[] = अणुMGN_VHT4SS_MCS0, MGN_VHT4SS_MCS1, MGN_VHT4SS_MCS2, MGN_VHT4SS_MCS3, MGN_VHT4SS_MCS4,
				MGN_VHT4SS_MCS5, MGN_VHT4SS_MCS6, MGN_VHT4SS_MCS7, MGN_VHT4SS_MCS8, MGN_VHT4SS_MCS9पूर्ण;

		PHY_SetTxPowerIndexByRateArray(padapter, RFPath,
					       pHalData->CurrentChannelBW,
					       Channel, vhtRates4T,
					       ARRAY_SIZE(vhtRates4T));
	पूर्ण
पूर्ण

अटल bool phy_GetChnlIndex(u8 Channel, u8 *ChannelIdx)
अणु
	u8 channel5G[CHANNEL_MAX_NUMBER_5G] = अणु
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 100, 102,
		104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130,
		132, 134, 136, 138, 140, 142, 144, 149, 151, 153, 155, 157, 159, 161,
		163, 165, 167, 168, 169, 171, 173, 175, 177
	पूर्ण;
	u8  i = 0;
	bool bIn24G = true;

	अगर (Channel <= 14) अणु
		bIn24G = true;
		*ChannelIdx = Channel-1;
	पूर्ण अन्यथा अणु
		bIn24G = false;

		क्रम (i = 0; i < ARRAY_SIZE(channel5G); ++i) अणु
			अगर (channel5G[i] == Channel) अणु
				*ChannelIdx = i;
				वापस bIn24G;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस bIn24G;
पूर्ण

u8 PHY_GetTxPowerIndexBase(
	काष्ठा adapter *padapter,
	u8 RFPath,
	u8 Rate,
	क्रमागत channel_width	BandWidth,
	u8 Channel,
	bool *bIn24G
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 i = 0;	/* शेष set to 1S */
	u8 txPower = 0;
	u8 chnlIdx = (Channel-1);

	अगर (HAL_IsLegalChannel(padapter, Channel) == false)
		chnlIdx = 0;

	*bIn24G = phy_GetChnlIndex(Channel, &chnlIdx);

	अगर (*bIn24G) अणु /* 3 ============================== 2.4 G ============================== */
		अगर (IS_CCK_RATE(Rate))
			txPower = pHalData->Index24G_CCK_Base[RFPath][chnlIdx];
		अन्यथा अगर (MGN_6M <= Rate)
			txPower = pHalData->Index24G_BW40_Base[RFPath][chnlIdx];

		/*  OFDM-1T */
		अगर ((MGN_6M <= Rate && Rate <= MGN_54M) && !IS_CCK_RATE(Rate))
			txPower += pHalData->OFDM_24G_Dअगरf[RFPath][TX_1S];

		अगर (BandWidth == CHANNEL_WIDTH_20) अणु /*  BW20-1S, BW20-2S */
			अगर ((MGN_MCS0 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT1SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_24G_Dअगरf[RFPath][TX_1S];
			अगर ((MGN_MCS8 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT2SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_24G_Dअगरf[RFPath][TX_2S];
			अगर ((MGN_MCS16 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT3SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_24G_Dअगरf[RFPath][TX_3S];
			अगर ((MGN_MCS24 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT4SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_24G_Dअगरf[RFPath][TX_4S];

		पूर्ण अन्यथा अगर (BandWidth == CHANNEL_WIDTH_40) अणु /*  BW40-1S, BW40-2S */
			अगर ((MGN_MCS0 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT1SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_1S];
			अगर ((MGN_MCS8 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT2SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_2S];
			अगर ((MGN_MCS16 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT3SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_3S];
			अगर ((MGN_MCS24 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT4SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_4S];

		पूर्ण
		/*  Willis suggest aकरोpt BW 40M घातer index जबतक in BW 80 mode */
		अन्यथा अगर (BandWidth == CHANNEL_WIDTH_80) अणु
			अगर ((MGN_MCS0 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT1SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_1S];
			अगर ((MGN_MCS8 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT2SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_2S];
			अगर ((MGN_MCS16 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT3SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_3S];
			अगर ((MGN_MCS24 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT4SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_24G_Dअगरf[RFPath][TX_4S];

		पूर्ण
	पूर्ण अन्यथा अणु/* 3 ============================== 5 G ============================== */
		अगर (MGN_6M <= Rate)
			txPower = pHalData->Index5G_BW40_Base[RFPath][chnlIdx];

		/*  OFDM-1T */
		अगर ((MGN_6M <= Rate && Rate <= MGN_54M) && !IS_CCK_RATE(Rate))
			txPower += pHalData->OFDM_5G_Dअगरf[RFPath][TX_1S];

		/*  BW20-1S, BW20-2S */
		अगर (BandWidth == CHANNEL_WIDTH_20) अणु
			अगर ((MGN_MCS0 <= Rate && Rate <= MGN_MCS31)  || (MGN_VHT1SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_5G_Dअगरf[RFPath][TX_1S];
			अगर ((MGN_MCS8 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT2SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_5G_Dअगरf[RFPath][TX_2S];
			अगर ((MGN_MCS16 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT3SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_5G_Dअगरf[RFPath][TX_3S];
			अगर ((MGN_MCS24 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT4SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW20_5G_Dअगरf[RFPath][TX_4S];

		पूर्ण अन्यथा अगर (BandWidth == CHANNEL_WIDTH_40) अणु /*  BW40-1S, BW40-2S */
			अगर ((MGN_MCS0 <= Rate && Rate <= MGN_MCS31)  || (MGN_VHT1SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_5G_Dअगरf[RFPath][TX_1S];
			अगर ((MGN_MCS8 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT2SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_5G_Dअगरf[RFPath][TX_2S];
			अगर ((MGN_MCS16 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT3SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_5G_Dअगरf[RFPath][TX_3S];
			अगर ((MGN_MCS24 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT4SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW40_5G_Dअगरf[RFPath][TX_4S];

		पूर्ण अन्यथा अगर (BandWidth == CHANNEL_WIDTH_80) अणु /*  BW80-1S, BW80-2S */
			/*  <20121220, Kordan> Get the index of array "Index5G_BW80_Base". */
			u8 channel5G_80M[CHANNEL_MAX_NUMBER_5G_80M] = अणु42, 58, 106, 122, 138, 155, 171पूर्ण;
			क्रम (i = 0; i < ARRAY_SIZE(channel5G_80M); ++i)
				अगर (channel5G_80M[i] == Channel)
					chnlIdx = i;

			txPower = pHalData->Index5G_BW80_Base[RFPath][chnlIdx];

			अगर ((MGN_MCS0 <= Rate && Rate <= MGN_MCS31)  || (MGN_VHT1SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += + pHalData->BW80_5G_Dअगरf[RFPath][TX_1S];
			अगर ((MGN_MCS8 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT2SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW80_5G_Dअगरf[RFPath][TX_2S];
			अगर ((MGN_MCS16 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT3SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW80_5G_Dअगरf[RFPath][TX_3S];
			अगर ((MGN_MCS23 <= Rate && Rate <= MGN_MCS31) || (MGN_VHT4SS_MCS0 <= Rate && Rate <= MGN_VHT4SS_MCS9))
				txPower += pHalData->BW80_5G_Dअगरf[RFPath][TX_4S];
		पूर्ण
	पूर्ण

	वापस txPower;
पूर्ण

s8 PHY_GetTxPowerTrackingOffset(काष्ठा adapter *padapter, u8 RFPath, u8 Rate)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;
	s8 offset = 0;

	अगर (pDM_Odm->RFCalibrateInfo.TxPowerTrackControl  == false)
		वापस offset;

	अगर ((Rate == MGN_1M) || (Rate == MGN_2M) || (Rate == MGN_5_5M) || (Rate == MGN_11M))
		offset = pDM_Odm->Remnant_CCKSwingIdx;
	अन्यथा
		offset = pDM_Odm->Remnant_OFDMSwingIdx[RFPath];

	वापस offset;
पूर्ण

u8 PHY_GetRateIndexOfTxPowerByRate(u8 Rate)
अणु
	u8 index = 0;
	चयन (Rate) अणु
	हाल MGN_1M:
		index = 0;
		अवरोध;
	हाल MGN_2M:
		index = 1;
		अवरोध;
	हाल MGN_5_5M:
		index = 2;
		अवरोध;
	हाल MGN_11M:
		index = 3;
		अवरोध;
	हाल MGN_6M:
		index = 4;
		अवरोध;
	हाल MGN_9M:
		index = 5;
		अवरोध;
	हाल MGN_12M:
		index = 6;
		अवरोध;
	हाल MGN_18M:
		index = 7;
		अवरोध;
	हाल MGN_24M:
		index = 8;
		अवरोध;
	हाल MGN_36M:
		index = 9;
		अवरोध;
	हाल MGN_48M:
		index = 10;
		अवरोध;
	हाल MGN_54M:
		index = 11;
		अवरोध;
	हाल MGN_MCS0:
		index = 12;
		अवरोध;
	हाल MGN_MCS1:
		index = 13;
		अवरोध;
	हाल MGN_MCS2:
		index = 14;
		अवरोध;
	हाल MGN_MCS3:
		index = 15;
		अवरोध;
	हाल MGN_MCS4:
		index = 16;
		अवरोध;
	हाल MGN_MCS5:
		index = 17;
		अवरोध;
	हाल MGN_MCS6:
		index = 18;
		अवरोध;
	हाल MGN_MCS7:
		index = 19;
		अवरोध;
	हाल MGN_MCS8:
		index = 20;
		अवरोध;
	हाल MGN_MCS9:
		index = 21;
		अवरोध;
	हाल MGN_MCS10:
		index = 22;
		अवरोध;
	हाल MGN_MCS11:
		index = 23;
		अवरोध;
	हाल MGN_MCS12:
		index = 24;
		अवरोध;
	हाल MGN_MCS13:
		index = 25;
		अवरोध;
	हाल MGN_MCS14:
		index = 26;
		अवरोध;
	हाल MGN_MCS15:
		index = 27;
		अवरोध;
	हाल MGN_MCS16:
		index = 28;
		अवरोध;
	हाल MGN_MCS17:
		index = 29;
		अवरोध;
	हाल MGN_MCS18:
		index = 30;
		अवरोध;
	हाल MGN_MCS19:
		index = 31;
		अवरोध;
	हाल MGN_MCS20:
		index = 32;
		अवरोध;
	हाल MGN_MCS21:
		index = 33;
		अवरोध;
	हाल MGN_MCS22:
		index = 34;
		अवरोध;
	हाल MGN_MCS23:
		index = 35;
		अवरोध;
	हाल MGN_MCS24:
		index = 36;
		अवरोध;
	हाल MGN_MCS25:
		index = 37;
		अवरोध;
	हाल MGN_MCS26:
		index = 38;
		अवरोध;
	हाल MGN_MCS27:
		index = 39;
		अवरोध;
	हाल MGN_MCS28:
		index = 40;
		अवरोध;
	हाल MGN_MCS29:
		index = 41;
		अवरोध;
	हाल MGN_MCS30:
		index = 42;
		अवरोध;
	हाल MGN_MCS31:
		index = 43;
		अवरोध;
	हाल MGN_VHT1SS_MCS0:
		index = 44;
		अवरोध;
	हाल MGN_VHT1SS_MCS1:
		index = 45;
		अवरोध;
	हाल MGN_VHT1SS_MCS2:
		index = 46;
		अवरोध;
	हाल MGN_VHT1SS_MCS3:
		index = 47;
		अवरोध;
	हाल MGN_VHT1SS_MCS4:
		index = 48;
		अवरोध;
	हाल MGN_VHT1SS_MCS5:
		index = 49;
		अवरोध;
	हाल MGN_VHT1SS_MCS6:
		index = 50;
		अवरोध;
	हाल MGN_VHT1SS_MCS7:
		index = 51;
		अवरोध;
	हाल MGN_VHT1SS_MCS8:
		index = 52;
		अवरोध;
	हाल MGN_VHT1SS_MCS9:
		index = 53;
		अवरोध;
	हाल MGN_VHT2SS_MCS0:
		index = 54;
		अवरोध;
	हाल MGN_VHT2SS_MCS1:
		index = 55;
		अवरोध;
	हाल MGN_VHT2SS_MCS2:
		index = 56;
		अवरोध;
	हाल MGN_VHT2SS_MCS3:
		index = 57;
		अवरोध;
	हाल MGN_VHT2SS_MCS4:
		index = 58;
		अवरोध;
	हाल MGN_VHT2SS_MCS5:
		index = 59;
		अवरोध;
	हाल MGN_VHT2SS_MCS6:
		index = 60;
		अवरोध;
	हाल MGN_VHT2SS_MCS7:
		index = 61;
		अवरोध;
	हाल MGN_VHT2SS_MCS8:
		index = 62;
		अवरोध;
	हाल MGN_VHT2SS_MCS9:
		index = 63;
		अवरोध;
	हाल MGN_VHT3SS_MCS0:
		index = 64;
		अवरोध;
	हाल MGN_VHT3SS_MCS1:
		index = 65;
		अवरोध;
	हाल MGN_VHT3SS_MCS2:
		index = 66;
		अवरोध;
	हाल MGN_VHT3SS_MCS3:
		index = 67;
		अवरोध;
	हाल MGN_VHT3SS_MCS4:
		index = 68;
		अवरोध;
	हाल MGN_VHT3SS_MCS5:
		index = 69;
		अवरोध;
	हाल MGN_VHT3SS_MCS6:
		index = 70;
		अवरोध;
	हाल MGN_VHT3SS_MCS7:
		index = 71;
		अवरोध;
	हाल MGN_VHT3SS_MCS8:
		index = 72;
		अवरोध;
	हाल MGN_VHT3SS_MCS9:
		index = 73;
		अवरोध;
	हाल MGN_VHT4SS_MCS0:
		index = 74;
		अवरोध;
	हाल MGN_VHT4SS_MCS1:
		index = 75;
		अवरोध;
	हाल MGN_VHT4SS_MCS2:
		index = 76;
		अवरोध;
	हाल MGN_VHT4SS_MCS3:
		index = 77;
		अवरोध;
	हाल MGN_VHT4SS_MCS4:
		index = 78;
		अवरोध;
	हाल MGN_VHT4SS_MCS5:
		index = 79;
		अवरोध;
	हाल MGN_VHT4SS_MCS6:
		index = 80;
		अवरोध;
	हाल MGN_VHT4SS_MCS7:
		index = 81;
		अवरोध;
	हाल MGN_VHT4SS_MCS8:
		index = 82;
		अवरोध;
	हाल MGN_VHT4SS_MCS9:
		index = 83;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस index;
पूर्ण

s8 PHY_GetTxPowerByRate(
	काष्ठा adapter *padapter, u8 Band, u8 RFPath, u8 TxNum, u8 Rate
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	s8 value = 0;
	u8 rateIndex = PHY_GetRateIndexOfTxPowerByRate(Rate);

	अगर ((padapter->registrypriv.RegEnableTxPowerByRate == 2 && pHalData->EEPROMRegulatory == 2) ||
		   padapter->registrypriv.RegEnableTxPowerByRate == 0)
		वापस 0;

	अगर (Band != BAND_ON_2_4G && Band != BAND_ON_5G)
		वापस value;

	अगर (RFPath > ODM_RF_PATH_D)
		वापस value;

	अगर (TxNum >= RF_MAX_TX_NUM)
		वापस value;

	अगर (rateIndex >= TX_PWR_BY_RATE_NUM_RATE)
		वापस value;

	वापस pHalData->TxPwrByRateOffset[Band][RFPath][TxNum][rateIndex];

पूर्ण

व्योम PHY_SetTxPowerByRate(
	काष्ठा adapter *padapter,
	u8 Band,
	u8 RFPath,
	u8 TxNum,
	u8 Rate,
	s8 Value
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 rateIndex = PHY_GetRateIndexOfTxPowerByRate(Rate);

	अगर (Band != BAND_ON_2_4G && Band != BAND_ON_5G)
		वापस;

	अगर (RFPath > ODM_RF_PATH_D)
		वापस;

	अगर (TxNum >= RF_MAX_TX_NUM)
		वापस;

	अगर (rateIndex >= TX_PWR_BY_RATE_NUM_RATE)
		वापस;

	pHalData->TxPwrByRateOffset[Band][RFPath][TxNum][rateIndex] = Value;
पूर्ण

व्योम PHY_SetTxPowerLevelByPath(काष्ठा adapter *Adapter, u8 channel, u8 path)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	bool bIsIn24G = (pHalData->CurrentBandType == BAND_ON_2_4G);

	/* अगर (pMgntInfo->RegNByteAccess == 0) */
	अणु
		अगर (bIsIn24G)
			PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, CCK);

		PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, OFDM);
		PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, HT_MCS0_MCS7);

		अगर (pHalData->NumTotalRFPath >= 2)
			PHY_SetTxPowerIndexByRateSection(Adapter, path, channel, HT_MCS8_MCS15);

	पूर्ण
पूर्ण

व्योम PHY_SetTxPowerIndexByRateArray(
	काष्ठा adapter *padapter,
	u8 RFPath,
	क्रमागत channel_width BandWidth,
	u8 Channel,
	u8 *Rates,
	u8 RateArraySize
)
अणु
	u32 घातerIndex = 0;
	पूर्णांक	i = 0;

	क्रम (i = 0; i < RateArraySize; ++i) अणु
		घातerIndex = PHY_GetTxPowerIndex(padapter, RFPath, Rates[i], BandWidth, Channel);
		PHY_SetTxPowerIndex(padapter, घातerIndex, RFPath, Rates[i]);
	पूर्ण
पूर्ण

अटल s8 phy_GetWorldWideLimit(s8 *LimitTable)
अणु
	s8	min = LimitTable[0];
	u8 i = 0;

	क्रम (i = 0; i < MAX_REGULATION_NUM; ++i) अणु
		अगर (LimitTable[i] < min)
			min = LimitTable[i];
	पूर्ण

	वापस min;
पूर्ण

अटल s8 phy_GetChannelIndexOfTxPowerLimit(u8 Band, u8 Channel)
अणु
	s8	channelIndex = -1;
	u8 channel5G[CHANNEL_MAX_NUMBER_5G] = अणु
		36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 100, 102,
		104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128, 130,
		132, 134, 136, 138, 140, 142, 144, 149, 151, 153, 155, 157, 159, 161,
		163, 165, 167, 168, 169, 171, 173, 175, 177
	पूर्ण;
	u8 i = 0;
	अगर (Band == BAND_ON_2_4G)
		channelIndex = Channel - 1;
	अन्यथा अगर (Band == BAND_ON_5G) अणु
		क्रम (i = 0; i < ARRAY_SIZE(channel5G); ++i) अणु
			अगर (channel5G[i] == Channel)
				channelIndex = i;
		पूर्ण
	पूर्ण

	वापस channelIndex;
पूर्ण

अटल s16 get_bandwidth_idx(स्थिर क्रमागत channel_width bandwidth)
अणु
	चयन (bandwidth) अणु
	हाल CHANNEL_WIDTH_20:
		वापस 0;
	हाल CHANNEL_WIDTH_40:
		वापस 1;
	हाल CHANNEL_WIDTH_80:
		वापस 2;
	हाल CHANNEL_WIDTH_160:
		वापस 3;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल s16 get_rate_sctn_idx(स्थिर u8 rate)
अणु
	चयन (rate) अणु
	हाल MGN_1M: हाल MGN_2M: हाल MGN_5_5M: हाल MGN_11M:
		वापस 0;
	हाल MGN_6M: हाल MGN_9M: हाल MGN_12M: हाल MGN_18M:
	हाल MGN_24M: हाल MGN_36M: हाल MGN_48M: हाल MGN_54M:
		वापस 1;
	हाल MGN_MCS0: हाल MGN_MCS1: हाल MGN_MCS2: हाल MGN_MCS3:
	हाल MGN_MCS4: हाल MGN_MCS5: हाल MGN_MCS6: हाल MGN_MCS7:
		वापस 2;
	हाल MGN_MCS8: हाल MGN_MCS9: हाल MGN_MCS10: हाल MGN_MCS11:
	हाल MGN_MCS12: हाल MGN_MCS13: हाल MGN_MCS14: हाल MGN_MCS15:
		वापस 3;
	हाल MGN_MCS16: हाल MGN_MCS17: हाल MGN_MCS18: हाल MGN_MCS19:
	हाल MGN_MCS20: हाल MGN_MCS21: हाल MGN_MCS22: हाल MGN_MCS23:
		वापस 4;
	हाल MGN_MCS24: हाल MGN_MCS25: हाल MGN_MCS26: हाल MGN_MCS27:
	हाल MGN_MCS28: हाल MGN_MCS29: हाल MGN_MCS30: हाल MGN_MCS31:
		वापस 5;
	हाल MGN_VHT1SS_MCS0: हाल MGN_VHT1SS_MCS1: हाल MGN_VHT1SS_MCS2:
	हाल MGN_VHT1SS_MCS3: हाल MGN_VHT1SS_MCS4: हाल MGN_VHT1SS_MCS5:
	हाल MGN_VHT1SS_MCS6: हाल MGN_VHT1SS_MCS7: हाल MGN_VHT1SS_MCS8:
	हाल MGN_VHT1SS_MCS9:
		वापस 6;
	हाल MGN_VHT2SS_MCS0: हाल MGN_VHT2SS_MCS1: हाल MGN_VHT2SS_MCS2:
	हाल MGN_VHT2SS_MCS3: हाल MGN_VHT2SS_MCS4: हाल MGN_VHT2SS_MCS5:
	हाल MGN_VHT2SS_MCS6: हाल MGN_VHT2SS_MCS7: हाल MGN_VHT2SS_MCS8:
	हाल MGN_VHT2SS_MCS9:
		वापस 7;
	हाल MGN_VHT3SS_MCS0: हाल MGN_VHT3SS_MCS1: हाल MGN_VHT3SS_MCS2:
	हाल MGN_VHT3SS_MCS3: हाल MGN_VHT3SS_MCS4: हाल MGN_VHT3SS_MCS5:
	हाल MGN_VHT3SS_MCS6: हाल MGN_VHT3SS_MCS7: हाल MGN_VHT3SS_MCS8:
	हाल MGN_VHT3SS_MCS9:
		वापस 8;
	हाल MGN_VHT4SS_MCS0: हाल MGN_VHT4SS_MCS1: हाल MGN_VHT4SS_MCS2:
	हाल MGN_VHT4SS_MCS3: हाल MGN_VHT4SS_MCS4: हाल MGN_VHT4SS_MCS5:
	हाल MGN_VHT4SS_MCS6: हाल MGN_VHT4SS_MCS7: हाल MGN_VHT4SS_MCS8:
	हाल MGN_VHT4SS_MCS9:
		वापस 9;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

s8 phy_get_tx_pwr_lmt(काष्ठा adapter *adapter, u32 reg_pwr_tbl_sel,
		      क्रमागत band_type band_type, क्रमागत channel_width bandwidth,
		      u8 rf_path, u8 data_rate, u8 channel)
अणु
	s16 idx_band       = -1;
	s16 idx_regulation = -1;
	s16 idx_bandwidth  = -1;
	s16 idx_rate_sctn  = -1;
	s16 idx_channel    = -1;
	s8 pwr_lmt = MAX_POWER_INDEX;
	काष्ठा hal_com_data *hal_data = GET_HAL_DATA(adapter);

	अगर (((adapter->registrypriv.RegEnableTxPowerLimit == 2) &&
	     (hal_data->EEPROMRegulatory != 1)) ||
	    (adapter->registrypriv.RegEnableTxPowerLimit == 0))
		वापस MAX_POWER_INDEX;

	चयन (adapter->registrypriv.RegPwrTblSel) अणु
	हाल 1:
		idx_regulation = TXPWR_LMT_ETSI;
		अवरोध;
	हाल 2:
		idx_regulation = TXPWR_LMT_MKK;
		अवरोध;
	हाल 3:
		idx_regulation = TXPWR_LMT_FCC;
		अवरोध;
	हाल 4:
		idx_regulation = TXPWR_LMT_WW;
		अवरोध;
	शेष:
		idx_regulation = (band_type == BAND_ON_2_4G) ?
			hal_data->Regulation2_4G :
			hal_data->Regulation5G;
		अवरोध;
	पूर्ण

	अगर (band_type == BAND_ON_2_4G)
		idx_band = 0;
	अन्यथा अगर (band_type == BAND_ON_5G)
		idx_band = 1;

	idx_bandwidth = get_bandwidth_idx(bandwidth);
	idx_rate_sctn = get_rate_sctn_idx(data_rate);

	/*  workaround क्रम wrong index combination to obtain tx घातer limit, */
	/*  OFDM only exists in BW 20M */
	/*  CCK table will only be given in BW 20M */
	/*  HT on 80M will reference to HT on 40M */
	अगर (idx_rate_sctn == 0 || idx_rate_sctn == 1)
		idx_bandwidth = 0;
	अन्यथा अगर ((idx_rate_sctn == 2 || idx_rate_sctn == 3) &&
		 (band_type == BAND_ON_5G) && (idx_bandwidth == 2))
		idx_bandwidth = 1;

	अगर (band_type == BAND_ON_2_4G || band_type == BAND_ON_5G)
		channel = phy_GetChannelIndexOfTxPowerLimit(band_type, channel);

	अगर (idx_band == -1 || idx_regulation == -1 || idx_bandwidth == -1 ||
	    idx_rate_sctn == -1 || idx_channel == -1)
		वापस MAX_POWER_INDEX;

	अगर (band_type == BAND_ON_2_4G) अणु
		s8 limits[10] = अणु0पूर्ण; u8 i = 0;

		क्रम (i = 0; i < MAX_REGULATION_NUM; i++)
			limits[i] = hal_data->TxPwrLimit_2_4G[i]
							     [idx_bandwidth]
							     [idx_rate_sctn]
							     [idx_channel]
							     [rf_path];

		pwr_lmt = (idx_regulation == TXPWR_LMT_WW) ?
			phy_GetWorldWideLimit(limits) :
			hal_data->TxPwrLimit_2_4G[idx_regulation]
						 [idx_bandwidth]
						 [idx_rate_sctn]
						 [idx_channel]
						 [rf_path];

	पूर्ण अन्यथा अगर (band_type == BAND_ON_5G) अणु
		s8 limits[10] = अणु0पूर्ण; u8 i = 0;

		क्रम (i = 0; i < MAX_REGULATION_NUM; ++i)
			limits[i] = hal_data->TxPwrLimit_5G[i]
							   [idx_bandwidth]
							   [idx_rate_sctn]
							   [idx_channel]
							   [rf_path];

		pwr_lmt = (idx_regulation == TXPWR_LMT_WW) ?
			phy_GetWorldWideLimit(limits) :
			hal_data->TxPwrLimit_5G[idx_regulation]
					       [idx_bandwidth]
					       [idx_rate_sctn]
					       [idx_channel]
					       [rf_path];
	पूर्ण

	वापस pwr_lmt;
पूर्ण

अटल व्योम phy_CrossReferenceHTAndVHTTxPowerLimit(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(padapter);
	u8 regulation, bw, channel, rateSection;
	s8 tempPwrLmt = 0;

	क्रम (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) अणु
		क्रम (bw = 0; bw < MAX_5G_BANDWIDTH_NUM; ++bw) अणु
			क्रम (channel = 0; channel < CHANNEL_MAX_NUMBER_5G; ++channel) अणु
				क्रम (rateSection = 0; rateSection < MAX_RATE_SECTION_NUM; ++rateSection) अणु
					tempPwrLmt = pHalData->TxPwrLimit_5G[regulation][bw][rateSection][channel][ODM_RF_PATH_A];
					अगर (tempPwrLmt == MAX_POWER_INDEX) अणु
						u8 baseSection = 2, refSection = 6;
						अगर (bw == 0 || bw == 1) अणु /*  5G 20M 40M VHT and HT can cross reference */
							/*			1, bw, rateSection, channel, ODM_RF_PATH_A); */
							अगर (rateSection >= 2 && rateSection <= 9) अणु
								अगर (rateSection == 2) अणु
									baseSection = 2;
									refSection = 6;
								पूर्ण अन्यथा अगर (rateSection == 3) अणु
									baseSection = 3;
									refSection = 7;
								पूर्ण अन्यथा अगर (rateSection == 4) अणु
									baseSection = 4;
									refSection = 8;
								पूर्ण अन्यथा अगर (rateSection == 5) अणु
									baseSection = 5;
									refSection = 9;
								पूर्ण अन्यथा अगर (rateSection == 6) अणु
									baseSection = 6;
									refSection = 2;
								पूर्ण अन्यथा अगर (rateSection == 7) अणु
									baseSection = 7;
									refSection = 3;
								पूर्ण अन्यथा अगर (rateSection == 8) अणु
									baseSection = 8;
									refSection = 4;
								पूर्ण अन्यथा अगर (rateSection == 9) अणु
									baseSection = 9;
									refSection = 5;
								पूर्ण
								pHalData->TxPwrLimit_5G[regulation][bw][baseSection][channel][ODM_RF_PATH_A] =
									pHalData->TxPwrLimit_5G[regulation][bw][refSection][channel][ODM_RF_PATH_A];
							पूर्ण
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम PHY_ConvertTxPowerLimitToPowerIndex(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	u8 BW40PwrBasedBm2_4G = 0x2E;
	u8 regulation, bw, channel, rateSection;
	s8 tempValue = 0, tempPwrLmt = 0;
	u8 rfPath = 0;

	phy_CrossReferenceHTAndVHTTxPowerLimit(Adapter);

	क्रम (regulation = 0; regulation < MAX_REGULATION_NUM; ++regulation) अणु
		क्रम (bw = 0; bw < MAX_2_4G_BANDWIDTH_NUM; ++bw) अणु
			क्रम (channel = 0; channel < CHANNEL_MAX_NUMBER_2G; ++channel) अणु
				क्रम (rateSection = 0; rateSection < MAX_RATE_SECTION_NUM; ++rateSection) अणु
					tempPwrLmt = pHalData->TxPwrLimit_2_4G[regulation][bw][rateSection][channel][ODM_RF_PATH_A];

					क्रम (rfPath = ODM_RF_PATH_A; rfPath < MAX_RF_PATH_NUM; ++rfPath) अणु
						अगर (pHalData->odmpriv.PhyRegPgValueType == PHY_REG_PG_EXACT_VALUE) अणु
							अगर (rateSection == 5) /*  HT 4T */
								BW40PwrBasedBm2_4G = PHY_GetTxPowerByRateBase(Adapter, BAND_ON_2_4G, rfPath, RF_4TX, HT_MCS24_MCS31);
							अन्यथा अगर (rateSection == 4) /*  HT 3T */
								BW40PwrBasedBm2_4G = PHY_GetTxPowerByRateBase(Adapter, BAND_ON_2_4G, rfPath, RF_3TX, HT_MCS16_MCS23);
							अन्यथा अगर (rateSection == 3) /*  HT 2T */
								BW40PwrBasedBm2_4G = PHY_GetTxPowerByRateBase(Adapter, BAND_ON_2_4G, rfPath, RF_2TX, HT_MCS8_MCS15);
							अन्यथा अगर (rateSection == 2) /*  HT 1T */
								BW40PwrBasedBm2_4G = PHY_GetTxPowerByRateBase(Adapter, BAND_ON_2_4G, rfPath, RF_1TX, HT_MCS0_MCS7);
							अन्यथा अगर (rateSection == 1) /*  OFDM */
								BW40PwrBasedBm2_4G = PHY_GetTxPowerByRateBase(Adapter, BAND_ON_2_4G, rfPath, RF_1TX, OFDM);
							अन्यथा अगर (rateSection == 0) /*  CCK */
								BW40PwrBasedBm2_4G = PHY_GetTxPowerByRateBase(Adapter, BAND_ON_2_4G, rfPath, RF_1TX, CCK);
						पूर्ण अन्यथा
							BW40PwrBasedBm2_4G = Adapter->registrypriv.RegPowerBase * 2;

						अगर (tempPwrLmt != MAX_POWER_INDEX) अणु
							tempValue = tempPwrLmt - BW40PwrBasedBm2_4G;
							pHalData->TxPwrLimit_2_4G[regulation][bw][rateSection][channel][rfPath] = tempValue;
						पूर्ण
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम PHY_InitTxPowerLimit(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	u8 i, j, k, l, m;

	क्रम (i = 0; i < MAX_REGULATION_NUM; ++i) अणु
		क्रम (j = 0; j < MAX_2_4G_BANDWIDTH_NUM; ++j)
			क्रम (k = 0; k < MAX_RATE_SECTION_NUM; ++k)
				क्रम (m = 0; m < CHANNEL_MAX_NUMBER_2G; ++m)
					क्रम (l = 0; l < MAX_RF_PATH_NUM; ++l)
						pHalData->TxPwrLimit_2_4G[i][j][k][m][l] = MAX_POWER_INDEX;
	पूर्ण

	क्रम (i = 0; i < MAX_REGULATION_NUM; ++i) अणु
		क्रम (j = 0; j < MAX_5G_BANDWIDTH_NUM; ++j)
			क्रम (k = 0; k < MAX_RATE_SECTION_NUM; ++k)
				क्रम (m = 0; m < CHANNEL_MAX_NUMBER_5G; ++m)
					क्रम (l = 0; l < MAX_RF_PATH_NUM; ++l)
						pHalData->TxPwrLimit_5G[i][j][k][m][l] = MAX_POWER_INDEX;
	पूर्ण
पूर्ण

व्योम PHY_SetTxPowerLimit(
	काष्ठा adapter *Adapter,
	u8 *Regulation,
	u8 *Band,
	u8 *Bandwidth,
	u8 *RateSection,
	u8 *RfPath,
	u8 *Channel,
	u8 *PowerLimit
)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	u8 regulation = 0, bandwidth = 0, rateSection = 0, channel;
	s8 घातerLimit = 0, prevPowerLimit, channelIndex;

	GetU1ByteIntegerFromStringInDecimal((s8 *)Channel, &channel);
	GetU1ByteIntegerFromStringInDecimal((s8 *)PowerLimit, &घातerLimit);

	घातerLimit = घातerLimit > MAX_POWER_INDEX ? MAX_POWER_INDEX : घातerLimit;

	अगर (eqNByte(Regulation, (u8 *)("FCC"), 3))
		regulation = 0;
	अन्यथा अगर (eqNByte(Regulation, (u8 *)("MKK"), 3))
		regulation = 1;
	अन्यथा अगर (eqNByte(Regulation, (u8 *)("ETSI"), 4))
		regulation = 2;
	अन्यथा अगर (eqNByte(Regulation, (u8 *)("WW13"), 4))
		regulation = 3;

	अगर (eqNByte(RateSection, (u8 *)("CCK"), 3) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 0;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("OFDM"), 4) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 1;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 2;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("2T"), 2))
		rateSection = 3;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("3T"), 2))
		rateSection = 4;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("HT"), 2) && eqNByte(RfPath, (u8 *)("4T"), 2))
		rateSection = 5;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("1T"), 2))
		rateSection = 6;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("2T"), 2))
		rateSection = 7;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("3T"), 2))
		rateSection = 8;
	अन्यथा अगर (eqNByte(RateSection, (u8 *)("VHT"), 3) && eqNByte(RfPath, (u8 *)("4T"), 2))
		rateSection = 9;
	अन्यथा
		वापस;

	अगर (eqNByte(Bandwidth, (u8 *)("20M"), 3))
		bandwidth = 0;
	अन्यथा अगर (eqNByte(Bandwidth, (u8 *)("40M"), 3))
		bandwidth = 1;
	अन्यथा अगर (eqNByte(Bandwidth, (u8 *)("80M"), 3))
		bandwidth = 2;
	अन्यथा अगर (eqNByte(Bandwidth, (u8 *)("160M"), 4))
		bandwidth = 3;

	अगर (eqNByte(Band, (u8 *)("2.4G"), 4)) अणु
		channelIndex = phy_GetChannelIndexOfTxPowerLimit(BAND_ON_2_4G, channel);

		अगर (channelIndex == -1)
			वापस;

		prevPowerLimit = pHalData->TxPwrLimit_2_4G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A];

		अगर (घातerLimit < prevPowerLimit)
			pHalData->TxPwrLimit_2_4G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A] = घातerLimit;

	पूर्ण अन्यथा अगर (eqNByte(Band, (u8 *)("5G"), 2)) अणु
		channelIndex = phy_GetChannelIndexOfTxPowerLimit(BAND_ON_5G, channel);

		अगर (channelIndex == -1)
			वापस;

		prevPowerLimit = pHalData->TxPwrLimit_5G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A];

		अगर (घातerLimit < prevPowerLimit)
			pHalData->TxPwrLimit_5G[regulation][bandwidth][rateSection][channelIndex][ODM_RF_PATH_A] = घातerLimit;

	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण
पूर्ण

व्योम Hal_ChannelPlanToRegulation(काष्ठा adapter *Adapter, u16 ChannelPlan)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	pHalData->Regulation2_4G = TXPWR_LMT_WW;
	pHalData->Regulation5G = TXPWR_LMT_WW;

	चयन (ChannelPlan) अणु
	हाल RT_CHANNEL_DOMAIN_WORLD_शून्य:
		pHalData->Regulation2_4G = TXPWR_LMT_WW;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_ETSI1_शून्य:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_शून्य:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_MKK1_शून्य:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_ETSI2_शून्य:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_FCC1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_MKK1_MKK1:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		pHalData->Regulation5G = TXPWR_LMT_MKK;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_KCC1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_MKK;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_FCC2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_FCC3:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_FCC4:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_FCC5:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_FCC6:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_FCC7:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI3:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_MKK1_MKK2:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_MKK1_MKK3:
		pHalData->Regulation2_4G = TXPWR_LMT_MKK;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_NCC1:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_NCC2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_GLOBAL_शून्य:
		pHalData->Regulation2_4G = TXPWR_LMT_WW;
		pHalData->Regulation5G = TXPWR_LMT_WW;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_ETSI1_ETSI4:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_FCC2:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_NCC3:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI5:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_FCC8:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI6:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI7:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI8:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI9:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI10:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI11:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_NCC4:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI12:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_FCC9:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_WORLD_ETSI13:
		pHalData->Regulation2_4G = TXPWR_LMT_ETSI;
		pHalData->Regulation5G = TXPWR_LMT_ETSI;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_FCC1_FCC10:
		pHalData->Regulation2_4G = TXPWR_LMT_FCC;
		pHalData->Regulation5G = TXPWR_LMT_FCC;
		अवरोध;
	हाल RT_CHANNEL_DOMAIN_REALTEK_DEFINE: /* Realtek Reserve */
		pHalData->Regulation2_4G = TXPWR_LMT_WW;
		pHalData->Regulation5G = TXPWR_LMT_WW;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
