<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

व्योम odm_ConfigRFReg_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u32 Addr,
	u32 Data,
	क्रमागत odm_rf_radio_path_e RF_PATH,
	u32 RegAddr
)
अणु
	अगर (Addr == 0xfe || Addr == 0xffe)
		msleep(50);
	अन्यथा अणु
		PHY_SetRFReg(pDM_Odm->Adapter, RF_PATH, RegAddr, bRFRegOffsetMask, Data);
		/*  Add 1us delay between BB/RF रेजिस्टर setting. */
		udelay(1);

		/* For disable/enable test in high temperature, the B6 value will fail to fill. Suggestion by BB Stanley, 2013.06.25. */
		अगर (Addr == 0xb6) अणु
			u32 getvalue = 0;
			u8 count = 0;

			getvalue = PHY_QueryRFReg(
				pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord
			);

			udelay(1);

			जबतक ((getvalue>>8) != (Data>>8)) अणु
				count++;
				PHY_SetRFReg(pDM_Odm->Adapter, RF_PATH, RegAddr, bRFRegOffsetMask, Data);
				udelay(1);
				getvalue = PHY_QueryRFReg(pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord);
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_INIT,
					ODM_DBG_TRACE,
					(
						"===> ODM_ConfigRFWithHeaderFile: [B6] getvalue 0x%x, Data 0x%x, count %d\n",
						getvalue,
						Data,
						count
					)
				);
				अगर (count > 5)
					अवरोध;
			पूर्ण
		पूर्ण

		अगर (Addr == 0xb2) अणु
			u32 getvalue = 0;
			u8 count = 0;

			getvalue = PHY_QueryRFReg(
				pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord
			);

			udelay(1);

			जबतक (getvalue != Data) अणु
				count++;
				PHY_SetRFReg(
					pDM_Odm->Adapter,
					RF_PATH,
					RegAddr,
					bRFRegOffsetMask,
					Data
				);
				udelay(1);
				/* Do LCK againg */
				PHY_SetRFReg(
					pDM_Odm->Adapter,
					RF_PATH,
					0x18,
					bRFRegOffsetMask,
					0x0fc07
				);
				udelay(1);
				getvalue = PHY_QueryRFReg(
					pDM_Odm->Adapter, RF_PATH, Addr, bMaskDWord
				);
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_INIT,
					ODM_DBG_TRACE,
					(
						"===> ODM_ConfigRFWithHeaderFile: [B2] getvalue 0x%x, Data 0x%x, count %d\n",
						getvalue,
						Data,
						count
					)
				);

				अगर (count > 5)
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण


व्योम odm_ConfigRF_RadioA_8723B(काष्ठा dm_odm_t *pDM_Odm, u32 Addr, u32 Data)
अणु
	u32  content = 0x1000; /*  RF_Content: radioa_txt */
	u32 maskक्रमPhySet = (u32)(content&0xE000);

	odm_ConfigRFReg_8723B(
		pDM_Odm,
		Addr,
		Data,
		ODM_RF_PATH_A,
		Addr|maskक्रमPhySet
	);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_TRACE,
		(
			"===> ODM_ConfigRFWithHeaderFile: [RadioA] %08X %08X\n",
			Addr,
			Data
		)
	);
पूर्ण

व्योम odm_ConfigMAC_8723B(काष्ठा dm_odm_t *pDM_Odm, u32 Addr, u8 Data)
अणु
	rtw_ग_लिखो8(pDM_Odm->Adapter, Addr, Data);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_TRACE,
		(
			"===> ODM_ConfigMACWithHeaderFile: [MAC_REG] %08X %08X\n",
			Addr,
			Data
		)
	);
पूर्ण

व्योम odm_ConfigBB_AGC_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u32 Addr,
	u32 Biपंचांगask,
	u32 Data
)
अणु
	PHY_SetBBReg(pDM_Odm->Adapter, Addr, Biपंचांगask, Data);
	/*  Add 1us delay between BB/RF रेजिस्टर setting. */
	udelay(1);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_TRACE,
		(
			"===> ODM_ConfigBBWithHeaderFile: [AGC_TAB] %08X %08X\n",
			Addr,
			Data
		)
	);
पूर्ण

व्योम odm_ConfigBB_PHY_REG_PG_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u32 Band,
	u32 RfPath,
	u32 TxNum,
	u32 Addr,
	u32 Biपंचांगask,
	u32 Data
)
अणु
	अगर (Addr == 0xfe || Addr == 0xffe)
		msleep(50);
	अन्यथा अणु
		PHY_StoreTxPowerByRate(pDM_Odm->Adapter, Band, RfPath, TxNum, Addr, Biपंचांगask, Data);
	पूर्ण
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_INIT,
		ODM_DBG_LOUD,
		(
			"===> ODM_ConfigBBWithHeaderFile: [PHY_REG] %08X %08X %08X\n",
			Addr,
			Biपंचांगask,
			Data
		)
	);
पूर्ण

व्योम odm_ConfigBB_PHY_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u32 Addr,
	u32 Biपंचांगask,
	u32 Data
)
अणु
	अगर (Addr == 0xfe)
		msleep(50);
	अन्यथा अगर (Addr == 0xfd)
		mdelay(5);
	अन्यथा अगर (Addr == 0xfc)
		mdelay(1);
	अन्यथा अगर (Addr == 0xfb)
		udelay(50);
	अन्यथा अगर (Addr == 0xfa)
		udelay(5);
	अन्यथा अगर (Addr == 0xf9)
		udelay(1);
	अन्यथा अणु
		PHY_SetBBReg(pDM_Odm->Adapter, Addr, Biपंचांगask, Data);
	पूर्ण

	/*  Add 1us delay between BB/RF रेजिस्टर setting. */
	udelay(1);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_INIT, ODM_DBG_TRACE, ("===> ODM_ConfigBBWithHeaderFile: [PHY_REG] %08X %08X\n", Addr, Data));
पूर्ण

व्योम odm_ConfigBB_TXPWR_LMT_8723B(
	काष्ठा dm_odm_t *pDM_Odm,
	u8 *Regulation,
	u8 *Band,
	u8 *Bandwidth,
	u8 *RateSection,
	u8 *RfPath,
	u8 *Channel,
	u8 *PowerLimit
)
अणु
	PHY_SetTxPowerLimit(
		pDM_Odm->Adapter,
		Regulation,
		Band,
		Bandwidth,
		RateSection,
		RfPath,
		Channel,
		PowerLimit
	);
पूर्ण
