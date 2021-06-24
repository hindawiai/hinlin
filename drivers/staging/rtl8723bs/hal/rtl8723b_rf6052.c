<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/******************************************************************************
 *
 *
 * Module:	rtl8192c_rf6052.c	(Source C File)
 *
 * Note:	Provide RF 6052 series relative API.
 *
 * Function:
 *
 * Export:
 *
 * Abbrev:
 *
 * History:
 * Data			Who		Remark
 *
 * 09/25/2008	MHC		Create initial version.
 * 11/05/2008	MHC		Add API क्रम tw घातer setting.
 *
 *
******************************************************************************/

#समावेश <rtl8723b_hal.h>

/*---------------------------Define Local Constant---------------------------*/
/*---------------------------Define Local Constant---------------------------*/


/*------------------------Define global variable-----------------------------*/
/*------------------------Define global variable-----------------------------*/


/*------------------------Define local variable------------------------------*/
/*  2008/11/20 MH For Debug only, RF */
/*------------------------Define local variable------------------------------*/

/*-----------------------------------------------------------------------------
 * Function:    PHY_RF6052SetBandwidth()
 *
 * Overview:    This function is called by SetBWModeCallback8190Pci() only
 *
 * Input:       काष्ठा adapter *			Adapter
 *		WIRELESS_BANDWIDTH_E	Bandwidth	20M or 40M
 *
 * Output:      NONE
 *
 * Return:      NONE
 *
 * Note:		For RF type 0222D
 *---------------------------------------------------------------------------*/
व्योम PHY_RF6052SetBandwidth8723B(
	काष्ठा adapter *Adapter, क्रमागत channel_width Bandwidth
) /* 20M or 40M */
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	चयन (Bandwidth) अणु
	हाल CHANNEL_WIDTH_20:
		pHalData->RfRegChnlVal[0] = ((pHalData->RfRegChnlVal[0] & 0xfffff3ff) | BIT10 | BIT11);
		PHY_SetRFReg(Adapter, ODM_RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask, pHalData->RfRegChnlVal[0]);
		PHY_SetRFReg(Adapter, ODM_RF_PATH_B, RF_CHNLBW, bRFRegOffsetMask, pHalData->RfRegChnlVal[0]);
		अवरोध;

	हाल CHANNEL_WIDTH_40:
		pHalData->RfRegChnlVal[0] = ((pHalData->RfRegChnlVal[0] & 0xfffff3ff) | BIT10);
		PHY_SetRFReg(Adapter, ODM_RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask, pHalData->RfRegChnlVal[0]);
		PHY_SetRFReg(Adapter, ODM_RF_PATH_B, RF_CHNLBW, bRFRegOffsetMask, pHalData->RfRegChnlVal[0]);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

पूर्ण

अटल पूर्णांक phy_RF6052_Config_ParaFile(काष्ठा adapter *Adapter)
अणु
	u32 u4RegValue = 0;
	u8 eRFPath;
	काष्ठा bb_रेजिस्टर_def *pPhyReg;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	/* 3----------------------------------------------------------------- */
	/* 3 <2> Initialize RF */
	/* 3----------------------------------------------------------------- */
	/* क्रम (eRFPath = RF_PATH_A; eRFPath <pHalData->NumTotalRFPath; eRFPath++) */
	क्रम (eRFPath = 0; eRFPath < pHalData->NumTotalRFPath; eRFPath++) अणु

		pPhyReg = &pHalData->PHYRegDef[eRFPath];

		/*----Store original RFENV control type----*/
		चयन (eRFPath) अणु
		हाल RF_PATH_A:
		हाल RF_PATH_C:
			u4RegValue = PHY_QueryBBReg(Adapter, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV);
			अवरोध;
		हाल RF_PATH_B:
		हाल RF_PATH_D:
			u4RegValue = PHY_QueryBBReg(Adapter, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV << 16);
			अवरोध;
		पूर्ण

		/*----Set RF_ENV enable----*/
		PHY_SetBBReg(Adapter, pPhyReg->rfपूर्णांकfe, bRFSI_RFENV << 16, 0x1);
		udelay(1);/* Platक्रमmStallExecution(1); */

		/*----Set RF_ENV output high----*/
		PHY_SetBBReg(Adapter, pPhyReg->rfपूर्णांकfo, bRFSI_RFENV, 0x1);
		udelay(1);/* Platक्रमmStallExecution(1); */

		/* Set bit number of Address and Data क्रम RF रेजिस्टर */
		PHY_SetBBReg(Adapter, pPhyReg->rfHSSIPara2, b3WireAddressLength, 0x0);	/*  Set 1 to 4 bits क्रम 8255 */
		udelay(1);/* Platक्रमmStallExecution(1); */

		PHY_SetBBReg(Adapter, pPhyReg->rfHSSIPara2, b3WireDataLength, 0x0);	/*  Set 0 to 12  bits क्रम 8255 */
		udelay(1);/* Platक्रमmStallExecution(1); */

		/*----Initialize RF fom connfiguration file----*/
		चयन (eRFPath) अणु
		हाल RF_PATH_A:
		हाल RF_PATH_B:
			ODM_ConfigRFWithHeaderFile(&pHalData->odmpriv,
						   CONFIG_RF_RADIO, eRFPath);
			अवरोध;
		हाल RF_PATH_C:
		हाल RF_PATH_D:
			अवरोध;
		पूर्ण

		/*----Restore RFENV control type----*/
		चयन (eRFPath) अणु
		हाल RF_PATH_A:
		हाल RF_PATH_C:
			PHY_SetBBReg(Adapter, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV, u4RegValue);
			अवरोध;
		हाल RF_PATH_B:
		हाल RF_PATH_D:
			PHY_SetBBReg(Adapter, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV << 16, u4RegValue);
			अवरोध;
		पूर्ण
	पूर्ण

	/* 3 ----------------------------------------------------------------- */
	/* 3 Configuration of Tx Power Tracking */
	/* 3 ----------------------------------------------------------------- */

	ODM_ConfigRFWithTxPwrTrackHeaderFile(&pHalData->odmpriv);

	वापस _SUCCESS;
पूर्ण


पूर्णांक PHY_RF6052_Config8723B(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	/*  */
	/*  Initialize general global value */
	/*  */
	/*  TODO: Extend RF_PATH_C and RF_PATH_D in the future */
	अगर (pHalData->rf_type == RF_1T1R)
		pHalData->NumTotalRFPath = 1;
	अन्यथा
		pHalData->NumTotalRFPath = 2;

	/*  */
	/*  Config BB and RF */
	/*  */
	वापस phy_RF6052_Config_ParaFile(Adapter);

पूर्ण

/* End of HalRf6052.c */
