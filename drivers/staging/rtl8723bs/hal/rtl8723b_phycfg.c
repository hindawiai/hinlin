<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTL8723B_PHYCFG_C_

#समावेश <drv_types.h>
#समावेश <rtw_debug.h>
#समावेश <rtl8723b_hal.h>


/*---------------------------Define Local Constant---------------------------*/
/* Channel चयन:The size of command tables क्रम चयन channel*/
#घोषणा MAX_PRECMD_CNT 16
#घोषणा MAX_RFDEPENDCMD_CNT 16
#घोषणा MAX_POSTCMD_CNT 16

#घोषणा MAX_DOZE_WAITING_TIMES_9x 64

/**
 * phy_CalculateBitShअगरt - Get shअगरted position of the BitMask.
 * @BitMask: Biपंचांगask.
 *
 * Return:	Return the shअगरt bit position of the mask
 */
अटल	u32 phy_CalculateBitShअगरt(u32 BitMask)
अणु
	u32 i;

	क्रम (i = 0; i <= 31; i++) अणु
		अगर (((BitMask>>i) &  0x1) == 1)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण


/**
 * PHY_QueryBBReg - Read "specific bits" from BB रेजिस्टर.
 * @Adapter:
 * @RegAddr:	The target address to be पढ़ोback
 * @BitMask:	The target bit position in the target address
 *				to be पढ़ोback
 *
 * Return:	The पढ़ोback रेजिस्टर value
 *
 * .. Note::	This function is equal to "GetRegSetting" in PHY programming
 *			guide
 */
u32 PHY_QueryBBReg_8723B(काष्ठा adapter *Adapter, u32 RegAddr, u32 BitMask)
अणु
	u32 OriginalValue, BitShअगरt;

#अगर (DISABLE_BB_RF == 1)
	वापस 0;
#पूर्ण_अगर

	OriginalValue = rtw_पढ़ो32(Adapter, RegAddr);
	BitShअगरt = phy_CalculateBitShअगरt(BitMask);

	वापस (OriginalValue & BitMask) >> BitShअगरt;

पूर्ण


/**
 * PHY_SetBBReg - Write "Specific bits" to BB रेजिस्टर (page 8~).
 * @Adapter:
 * @RegAddr:	The target address to be modअगरied
 * @BitMask:	The target bit position in the target address
 *				to be modअगरied
 * @Data:		The new रेजिस्टर value in the target bit position
 *				of the target address
 *
 * .. Note::	This function is equal to "PutRegSetting" in PHY programming
 *			guide
 */

व्योम PHY_SetBBReg_8723B(
	काष्ठा adapter *Adapter,
	u32 RegAddr,
	u32 BitMask,
	u32 Data
)
अणु
	/* u16 BBWaitCounter	= 0; */
	u32 OriginalValue, BitShअगरt;

#अगर (DISABLE_BB_RF == 1)
	वापस;
#पूर्ण_अगर

	अगर (BitMask != bMaskDWord) अणु /* अगर not "double word" ग_लिखो */
		OriginalValue = rtw_पढ़ो32(Adapter, RegAddr);
		BitShअगरt = phy_CalculateBitShअगरt(BitMask);
		Data = ((OriginalValue & (~BitMask)) | ((Data << BitShअगरt) & BitMask));
	पूर्ण

	rtw_ग_लिखो32(Adapter, RegAddr, Data);

पूर्ण


/*  */
/*  2. RF रेजिस्टर R/W API */
/*  */

अटल u32 phy_RFSerialRead_8723B(
	काष्ठा adapter *Adapter, क्रमागत rf_path eRFPath, u32 Offset
)
अणु
	u32 retValue = 0;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा bb_रेजिस्टर_def *pPhyReg = &pHalData->PHYRegDef[eRFPath];
	u32 NewOffset;
	u32 पंचांगpदीर्घ2;
	u8 RfPiEnable = 0;
	u32 Maskक्रमPhySet = 0;
	पूर्णांक i = 0;

	/*  */
	/*  Make sure RF रेजिस्टर offset is correct */
	/*  */
	Offset &= 0xff;

	NewOffset = Offset;

	अगर (eRFPath == RF_PATH_A) अणु
		पंचांगpदीर्घ2 = PHY_QueryBBReg(Adapter, rFPGA0_XA_HSSIParameter2|Maskक्रमPhySet, bMaskDWord);
		पंचांगpदीर्घ2 = (पंचांगpदीर्घ2 & (~bLSSIReadAddress)) | (NewOffset<<23) | bLSSIReadEdge;	/* T65 RF */
		PHY_SetBBReg(Adapter, rFPGA0_XA_HSSIParameter2|Maskक्रमPhySet, bMaskDWord, पंचांगpदीर्घ2&(~bLSSIReadEdge));
	पूर्ण अन्यथा अणु
		पंचांगpदीर्घ2 = PHY_QueryBBReg(Adapter, rFPGA0_XB_HSSIParameter2|Maskक्रमPhySet, bMaskDWord);
		पंचांगpदीर्घ2 = (पंचांगpदीर्घ2 & (~bLSSIReadAddress)) | (NewOffset<<23) | bLSSIReadEdge;	/* T65 RF */
		PHY_SetBBReg(Adapter, rFPGA0_XB_HSSIParameter2|Maskक्रमPhySet, bMaskDWord, पंचांगpदीर्घ2&(~bLSSIReadEdge));
	पूर्ण

	पंचांगpदीर्घ2 = PHY_QueryBBReg(Adapter, rFPGA0_XA_HSSIParameter2|Maskक्रमPhySet, bMaskDWord);
	PHY_SetBBReg(Adapter, rFPGA0_XA_HSSIParameter2|Maskक्रमPhySet, bMaskDWord, पंचांगpदीर्घ2 & (~bLSSIReadEdge));
	PHY_SetBBReg(Adapter, rFPGA0_XA_HSSIParameter2|Maskक्रमPhySet, bMaskDWord, पंचांगpदीर्घ2 | bLSSIReadEdge);

	udelay(10);

	क्रम (i = 0; i < 2; i++)
		udelay(MAX_STALL_TIME);
	udelay(10);

	अगर (eRFPath == RF_PATH_A)
		RfPiEnable = (u8)PHY_QueryBBReg(Adapter, rFPGA0_XA_HSSIParameter1|Maskक्रमPhySet, BIT8);
	अन्यथा अगर (eRFPath == RF_PATH_B)
		RfPiEnable = (u8)PHY_QueryBBReg(Adapter, rFPGA0_XB_HSSIParameter1|Maskक्रमPhySet, BIT8);

	अगर (RfPiEnable) अणु
		/*  Read from BBreg8b8, 12 bits क्रम 8190, 20bits क्रम T65 RF */
		retValue = PHY_QueryBBReg(Adapter, pPhyReg->rfLSSIReadBackPi|Maskक्रमPhySet, bLSSIReadBackData);
	पूर्ण अन्यथा अणु
		/* Read from BBreg8a0, 12 bits क्रम 8190, 20 bits क्रम T65 RF */
		retValue = PHY_QueryBBReg(Adapter, pPhyReg->rfLSSIReadBack|Maskक्रमPhySet, bLSSIReadBackData);
	पूर्ण
	वापस retValue;

पूर्ण

/**
 * phy_RFSerialWrite_8723B - Write data to RF रेजिस्टर (page 8~).
 * @Adapter:
 * @eRFPath:	Radio path of A/B/C/D
 * @Offset:	The target address to be पढ़ो
 * @Data:	The new रेजिस्टर Data in the target bit position
 *			of the target to be पढ़ो
 *
 * .. Note::	Threre are three types of serial operations:
 *		1. Software serial ग_लिखो
 *		2. Hardware LSSI-Low Speed Serial Interface
 *		3. Hardware HSSI-High speed
 *		serial ग_लिखो. Driver need to implement (1) and (2).
 *		This function is equal to the combination of RF_ReadReg() and  RFLSSIRead()
 *
 * .. Note::		  For RF8256 only
 *		 The total count of RTL8256(Zebra4) रेजिस्टर is around 36 bit it only employs
 *		 4-bit RF address. RTL8256 uses "register mode control bit" (Reg00[12], Reg00[10])
 *		 to access रेजिस्टर address bigger than 0xf. See "Appendix-4 in PHY Configuration
 *		 programming guide" क्रम more details.
 *		 Thus, we define a sub-finction क्रम RTL8526 रेजिस्टर address conversion
 *	       ===========================================================
 *		 Register Mode		RegCTL[1]		RegCTL[0]		Note
 *							(Reg00[12])		(Reg00[10])
 *	       ===========================================================
 *		 Reg_Mode0				0				x			Reg 0 ~15(0x0 ~ 0xf)
 *	       ------------------------------------------------------------------
 *		 Reg_Mode1				1				0			Reg 16 ~30(0x1 ~ 0xf)
 *	       ------------------------------------------------------------------
 *		 Reg_Mode2				1				1			Reg 31 ~ 45(0x1 ~ 0xf)
 *	       ------------------------------------------------------------------
 *
 *2008/09/02	MH	Add 92S RF definition
 *
 *
 *
 */
अटल व्योम phy_RFSerialWrite_8723B(
	काष्ठा adapter *Adapter,
	क्रमागत rf_path eRFPath,
	u32 Offset,
	u32 Data
)
अणु
	u32 DataAndAddr = 0;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा bb_रेजिस्टर_def *pPhyReg = &pHalData->PHYRegDef[eRFPath];
	u32 NewOffset;

	Offset &= 0xff;

	/*  */
	/*  Switch page क्रम 8256 RF IC */
	/*  */
	NewOffset = Offset;

	/*  */
	/*  Put ग_लिखो addr in [5:0]  and ग_लिखो data in [31:16] */
	/*  */
	DataAndAddr = ((NewOffset<<20) | (Data&0x000fffff)) & 0x0fffffff;	/*  T65 RF */
	/*  */
	/*  Write Operation */
	/*  */
	PHY_SetBBReg(Adapter, pPhyReg->rf3wireOffset, bMaskDWord, DataAndAddr);
पूर्ण


/**
 * PHY_QueryRFReg - Query "Specific bits" to RF रेजिस्टर (page 8~).
 * @Adapter:
 * @eRFPath:	Radio path of A/B/C/D
 * @RegAdd:	The target address to be पढ़ो
 * @BitMask:	The target bit position in the target address
 *				to be पढ़ो
 *
 * Return:	Readback value
 *
 * .. Note::	This function is equal to "GetRFRegSetting" in PHY
 *			programming guide
 */
u32 PHY_QueryRFReg_8723B(
	काष्ठा adapter *Adapter,
	u8 eRFPath,
	u32 RegAddr,
	u32 BitMask
)
अणु
	u32 Original_Value, BitShअगरt;

#अगर (DISABLE_BB_RF == 1)
	वापस 0;
#पूर्ण_अगर

	Original_Value = phy_RFSerialRead_8723B(Adapter, eRFPath, RegAddr);
	BitShअगरt =  phy_CalculateBitShअगरt(BitMask);

	वापस (Original_Value & BitMask) >> BitShअगरt;
पूर्ण

/**
 * PHY_SetRFReg - Write "Specific bits" to RF रेजिस्टर (page 8~).
 * @Adapter:
 * @eRFPath:	Radio path of A/B/C/D
 * @RegAddr:	The target address to be modअगरied
 * @BitMask:	The target bit position in the target address
 *				to be modअगरied
 * @Data:	The new रेजिस्टर Data in the target bit position
 *								of the target address
 *
 * .. Note::	This function is equal to "PutRFRegSetting" in PHY
 *			programming guide.
 */
व्योम PHY_SetRFReg_8723B(
	काष्ठा adapter *Adapter,
	u8 eRFPath,
	u32 RegAddr,
	u32 BitMask,
	u32 Data
)
अणु
	u32 Original_Value, BitShअगरt;

#अगर (DISABLE_BB_RF == 1)
	वापस;
#पूर्ण_अगर

	/*  RF data is 12 bits only */
	अगर (BitMask != bRFRegOffsetMask) अणु
		Original_Value = phy_RFSerialRead_8723B(Adapter, eRFPath, RegAddr);
		BitShअगरt =  phy_CalculateBitShअगरt(BitMask);
		Data = ((Original_Value & (~BitMask)) | (Data<<BitShअगरt));
	पूर्ण

	phy_RFSerialWrite_8723B(Adapter, eRFPath, RegAddr, Data);
पूर्ण


/*  */
/*  3. Initial MAC/BB/RF config by पढ़ोing MAC/BB/RF txt. */
/*  */


/*-----------------------------------------------------------------------------
 * PHY_MACConfig8192C - Condig MAC by header file or parameter file.
 *
 * Revised History:
 *  When		Who		Remark
 *  08/12/2008	MHC		Create Version 0.
 *
 *---------------------------------------------------------------------------
 */
s32 PHY_MACConfig8723B(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);

	ODM_ReadAndConfig_MP_8723B_MAC_REG(&pHalData->odmpriv);
	वापस _SUCCESS;
पूर्ण

/**
 * phy_InitBBRFRegisterDefinition - Initialize Register definition offset क्रम
 *									Radio Path A/B/C/D
 * @Adapter:
 *
 * .. Note::		The initialization value is स्थिरant and it should never be changes
 */
अटल व्योम phy_InitBBRFRegisterDefinition(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data		*pHalData = GET_HAL_DATA(Adapter);

	/*  RF Interface Sowrtware Control */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfपूर्णांकfs = rFPGA0_XAB_RFInterfaceSW; /*  16 LSBs अगर पढ़ो 32-bit from 0x870 */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfपूर्णांकfs = rFPGA0_XAB_RFInterfaceSW; /*  16 MSBs अगर पढ़ो 32-bit from 0x870 (16-bit क्रम 0x872) */

	/*  RF Interface Output (and Enable) */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfपूर्णांकfo = rFPGA0_XA_RFInterfaceOE; /*  16 LSBs अगर पढ़ो 32-bit from 0x860 */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfपूर्णांकfo = rFPGA0_XB_RFInterfaceOE; /*  16 LSBs अगर पढ़ो 32-bit from 0x864 */

	/*  RF Interface (Output and)  Enable */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfपूर्णांकfe = rFPGA0_XA_RFInterfaceOE; /*  16 MSBs अगर पढ़ो 32-bit from 0x860 (16-bit क्रम 0x862) */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfपूर्णांकfe = rFPGA0_XB_RFInterfaceOE; /*  16 MSBs अगर पढ़ो 32-bit from 0x864 (16-bit क्रम 0x866) */

	pHalData->PHYRegDef[ODM_RF_PATH_A].rf3wireOffset = rFPGA0_XA_LSSIParameter; /* LSSI Parameter */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rf3wireOffset = rFPGA0_XB_LSSIParameter;

	pHalData->PHYRegDef[ODM_RF_PATH_A].rfHSSIPara2 = rFPGA0_XA_HSSIParameter2;  /* wire control parameter2 */
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfHSSIPara2 = rFPGA0_XB_HSSIParameter2;  /* wire control parameter2 */

	/*  Tranceiver Readback LSSI/HSPI mode */
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfLSSIReadBack = rFPGA0_XA_LSSIReadBack;
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfLSSIReadBack = rFPGA0_XB_LSSIReadBack;
	pHalData->PHYRegDef[ODM_RF_PATH_A].rfLSSIReadBackPi = TransceiverA_HSPI_Readback;
	pHalData->PHYRegDef[ODM_RF_PATH_B].rfLSSIReadBackPi = TransceiverB_HSPI_Readback;

पूर्ण

अटल पूर्णांक phy_BB8723b_Config_ParaFile(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	/*  Read Tx Power Limit File */
	PHY_InitTxPowerLimit(Adapter);
	अगर (
		Adapter->registrypriv.RegEnableTxPowerLimit == 1 ||
		(Adapter->registrypriv.RegEnableTxPowerLimit == 2 && pHalData->EEPROMRegulatory == 1)
	) अणु
		ODM_ConfigRFWithHeaderFile(&pHalData->odmpriv,
					   CONFIG_RF_TXPWR_LMT, 0);
	पूर्ण

	/*  */
	/*  1. Read PHY_REG.TXT BB INIT!! */
	/*  */
	ODM_ConfigBBWithHeaderFile(&pHalData->odmpriv, CONFIG_BB_PHY_REG);

	/*  If EEPROM or EFUSE स्वतःload OK, We must config by PHY_REG_PG.txt */
	PHY_InitTxPowerByRate(Adapter);
	अगर (
		Adapter->registrypriv.RegEnableTxPowerByRate == 1 ||
		(Adapter->registrypriv.RegEnableTxPowerByRate == 2 && pHalData->EEPROMRegulatory != 2)
	) अणु
		ODM_ConfigBBWithHeaderFile(&pHalData->odmpriv,
					   CONFIG_BB_PHY_REG_PG);

		अगर (pHalData->odmpriv.PhyRegPgValueType == PHY_REG_PG_EXACT_VALUE)
			PHY_TxPowerByRateConfiguration(Adapter);

		अगर (
			Adapter->registrypriv.RegEnableTxPowerLimit == 1 ||
			(Adapter->registrypriv.RegEnableTxPowerLimit == 2 && pHalData->EEPROMRegulatory == 1)
		)
			PHY_ConvertTxPowerLimitToPowerIndex(Adapter);
	पूर्ण

	/*  */
	/*  2. Read BB AGC table Initialization */
	/*  */
	ODM_ConfigBBWithHeaderFile(&pHalData->odmpriv, CONFIG_BB_AGC_TAB);

	वापस _SUCCESS;
पूर्ण


पूर्णांक PHY_BBConfig8723B(काष्ठा adapter *Adapter)
अणु
	पूर्णांक	rtStatus = _SUCCESS;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);
	u32 RegVal;
	u8 CrystalCap;

	phy_InitBBRFRegisterDefinition(Adapter);

	/*  Enable BB and RF */
	RegVal = rtw_पढ़ो16(Adapter, REG_SYS_FUNC_EN);
	rtw_ग_लिखो16(Adapter, REG_SYS_FUNC_EN, (u16)(RegVal|BIT13|BIT0|BIT1));

	rtw_ग_लिखो32(Adapter, 0x948, 0x280);	/*  Others use Antenna S1 */

	rtw_ग_लिखो8(Adapter, REG_RF_CTRL, RF_EN|RF_RSTB|RF_SDMRSTB);

	msleep(1);

	PHY_SetRFReg(Adapter, ODM_RF_PATH_A, 0x1, 0xfffff, 0x780);

	rtw_ग_लिखो8(Adapter, REG_SYS_FUNC_EN, FEN_PPLL|FEN_PCIEA|FEN_DIO_PCIE|FEN_BB_GLB_RSTn|FEN_BBRSTB);

	rtw_ग_लिखो8(Adapter, REG_AFE_XTAL_CTRL+1, 0x80);

	/*  */
	/*  Config BB and AGC */
	/*  */
	rtStatus = phy_BB8723b_Config_ParaFile(Adapter);

	/*  0x2C[23:18] = 0x2C[17:12] = CrystalCap */
	CrystalCap = pHalData->CrystalCap & 0x3F;
	PHY_SetBBReg(Adapter, REG_MAC_PHY_CTRL, 0xFFF000, (CrystalCap | (CrystalCap << 6)));

	वापस rtStatus;
पूर्ण

अटल व्योम phy_LCK_8723B(काष्ठा adapter *Adapter)
अणु
	PHY_SetRFReg(Adapter, RF_PATH_A, 0xB0, bRFRegOffsetMask, 0xDFBE0);
	PHY_SetRFReg(Adapter, RF_PATH_A, RF_CHNLBW, bRFRegOffsetMask, 0x8C01);
	mdelay(200);
	PHY_SetRFReg(Adapter, RF_PATH_A, 0xB0, bRFRegOffsetMask, 0xDFFE0);
पूर्ण

पूर्णांक PHY_RFConfig8723B(काष्ठा adapter *Adapter)
अणु
	पूर्णांक rtStatus = _SUCCESS;

	/*  */
	/*  RF config */
	/*  */
	rtStatus = PHY_RF6052_Config8723B(Adapter);

	phy_LCK_8723B(Adapter);

	वापस rtStatus;
पूर्ण

/**************************************************************************************************************
 *   Description:
 *       The low-level पूर्णांकerface to set TxAGC , called by both MP and Normal Driver.
 *
 *                                                                                    <20120830, Kordan>
 **************************************************************************************************************/

व्योम PHY_SetTxPowerIndex(
	काष्ठा adapter *Adapter,
	u32 PowerIndex,
	u8 RFPath,
	u8 Rate
)
अणु
	अगर (RFPath == ODM_RF_PATH_A || RFPath == ODM_RF_PATH_B) अणु
		चयन (Rate) अणु
		हाल MGN_1M:
			PHY_SetBBReg(Adapter, rTxAGC_A_CCK1_Mcs32, bMaskByte1, PowerIndex);
			अवरोध;
		हाल MGN_2M:
			PHY_SetBBReg(Adapter, rTxAGC_B_CCK11_A_CCK2_11, bMaskByte1, PowerIndex);
			अवरोध;
		हाल MGN_5_5M:
			PHY_SetBBReg(Adapter, rTxAGC_B_CCK11_A_CCK2_11, bMaskByte2, PowerIndex);
			अवरोध;
		हाल MGN_11M:
			PHY_SetBBReg(Adapter, rTxAGC_B_CCK11_A_CCK2_11, bMaskByte3, PowerIndex);
			अवरोध;

		हाल MGN_6M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte0, PowerIndex);
			अवरोध;
		हाल MGN_9M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte1, PowerIndex);
			अवरोध;
		हाल MGN_12M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte2, PowerIndex);
			अवरोध;
		हाल MGN_18M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate18_06, bMaskByte3, PowerIndex);
			अवरोध;

		हाल MGN_24M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte0, PowerIndex);
			अवरोध;
		हाल MGN_36M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte1, PowerIndex);
			अवरोध;
		हाल MGN_48M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte2, PowerIndex);
			अवरोध;
		हाल MGN_54M:
			PHY_SetBBReg(Adapter, rTxAGC_A_Rate54_24, bMaskByte3, PowerIndex);
			अवरोध;

		हाल MGN_MCS0:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte0, PowerIndex);
			अवरोध;
		हाल MGN_MCS1:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte1, PowerIndex);
			अवरोध;
		हाल MGN_MCS2:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte2, PowerIndex);
			अवरोध;
		हाल MGN_MCS3:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs03_Mcs00, bMaskByte3, PowerIndex);
			अवरोध;

		हाल MGN_MCS4:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte0, PowerIndex);
			अवरोध;
		हाल MGN_MCS5:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte1, PowerIndex);
			अवरोध;
		हाल MGN_MCS6:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte2, PowerIndex);
			अवरोध;
		हाल MGN_MCS7:
			PHY_SetBBReg(Adapter, rTxAGC_A_Mcs07_Mcs04, bMaskByte3, PowerIndex);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

u8 PHY_GetTxPowerIndex(
	काष्ठा adapter *padapter,
	u8 RFPath,
	u8 Rate,
	क्रमागत channel_width BandWidth,
	u8 Channel
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	s8 txPower = 0, घातerDअगरfByRate = 0, limit = 0;
	bool bIn24G = false;

	txPower = (s8) PHY_GetTxPowerIndexBase(padapter, RFPath, Rate, BandWidth, Channel, &bIn24G);
	घातerDअगरfByRate = PHY_GetTxPowerByRate(padapter, BAND_ON_2_4G, ODM_RF_PATH_A, RF_1TX, Rate);

	limit = phy_get_tx_pwr_lmt(
		padapter,
		padapter->registrypriv.RegPwrTblSel,
		(u8)(!bIn24G),
		pHalData->CurrentChannelBW,
		RFPath,
		Rate,
		pHalData->CurrentChannel
	);

	घातerDअगरfByRate = घातerDअगरfByRate > limit ? limit : घातerDअगरfByRate;
	txPower += घातerDअगरfByRate;

	txPower += PHY_GetTxPowerTrackingOffset(padapter, RFPath, Rate);

	अगर (txPower > MAX_POWER_INDEX)
		txPower = MAX_POWER_INDEX;

	वापस (u8) txPower;
पूर्ण

व्योम PHY_SetTxPowerLevel8723B(काष्ठा adapter *Adapter, u8 Channel)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	काष्ठा dm_odm_t *pDM_Odm = &pHalData->odmpriv;
	काष्ठा fat_t *pDM_FatTable = &pDM_Odm->DM_FatTable;
	u8 RFPath = ODM_RF_PATH_A;

	अगर (pHalData->AntDivCfg) अणु/*  antenna भागersity Enable */
		RFPath = ((pDM_FatTable->RxIdleAnt == MAIN_ANT) ? ODM_RF_PATH_A : ODM_RF_PATH_B);
	पूर्ण अन्यथा अणु /*  antenna भागersity disable */
		RFPath = pHalData->ant_path;
	पूर्ण

	PHY_SetTxPowerLevelByPath(Adapter, Channel, RFPath);
पूर्ण

व्योम PHY_GetTxPowerLevel8723B(काष्ठा adapter *Adapter, s32 *घातerlevel)
अणु
पूर्ण

अटल व्योम phy_SetRegBW_8723B(
	काष्ठा adapter *Adapter, क्रमागत channel_width CurrentBW
)
अणु
	u16 RegRfMod_BW, u2पंचांगp = 0;
	RegRfMod_BW = rtw_पढ़ो16(Adapter, REG_TRXPTCL_CTL_8723B);

	चयन (CurrentBW) अणु
	हाल CHANNEL_WIDTH_20:
		rtw_ग_लिखो16(Adapter, REG_TRXPTCL_CTL_8723B, (RegRfMod_BW & 0xFE7F)); /*  BIT 7 = 0, BIT 8 = 0 */
		अवरोध;

	हाल CHANNEL_WIDTH_40:
		u2पंचांगp = RegRfMod_BW | BIT7;
		rtw_ग_लिखो16(Adapter, REG_TRXPTCL_CTL_8723B, (u2पंचांगp & 0xFEFF)); /*  BIT 7 = 1, BIT 8 = 0 */
		अवरोध;

	हाल CHANNEL_WIDTH_80:
		u2पंचांगp = RegRfMod_BW | BIT8;
		rtw_ग_लिखो16(Adapter, REG_TRXPTCL_CTL_8723B, (u2पंचांगp & 0xFF7F)); /*  BIT 7 = 0, BIT 8 = 1 */
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u8 phy_GetSecondaryChnl_8723B(काष्ठा adapter *Adapter)
अणु
	u8 SCSettingOf40 = 0, SCSettingOf20 = 0;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	अगर (pHalData->CurrentChannelBW == CHANNEL_WIDTH_80) अणु
		अगर (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
			SCSettingOf40 = VHT_DATA_SC_40_LOWER_OF_80MHZ;
		अन्यथा अगर (pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
			SCSettingOf40 = VHT_DATA_SC_40_UPPER_OF_80MHZ;

		अगर (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_LOWEST_OF_80MHZ;
		अन्यथा अगर (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
		अन्यथा अगर (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		अन्यथा अगर (
			(pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER) &&
			(pHalData->nCur80MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
		)
			SCSettingOf20 = VHT_DATA_SC_20_UPPERST_OF_80MHZ;
	पूर्ण अन्यथा अगर (pHalData->CurrentChannelBW == CHANNEL_WIDTH_40) अणु
		अगर (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_UPPER)
			SCSettingOf20 = VHT_DATA_SC_20_UPPER_OF_80MHZ;
		अन्यथा अगर (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER)
			SCSettingOf20 = VHT_DATA_SC_20_LOWER_OF_80MHZ;
	पूर्ण

	वापस  (SCSettingOf40 << 4) | SCSettingOf20;
पूर्ण

अटल व्योम phy_PostSetBwMode8723B(काष्ठा adapter *Adapter)
अणु
	u8 SubChnlNum = 0;
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);


	/* 3 Set Reg668 Reg440 BW */
	phy_SetRegBW_8723B(Adapter, pHalData->CurrentChannelBW);

	/* 3 Set Reg483 */
	SubChnlNum = phy_GetSecondaryChnl_8723B(Adapter);
	rtw_ग_लिखो8(Adapter, REG_DATA_SC_8723B, SubChnlNum);

	/* 3 */
	/* 3<2>Set PHY related रेजिस्टर */
	/* 3 */
	चयन (pHalData->CurrentChannelBW) अणु
	/* 20 MHz channel*/
	हाल CHANNEL_WIDTH_20:
		PHY_SetBBReg(Adapter, rFPGA0_RFMOD, bRFMOD, 0x0);

		PHY_SetBBReg(Adapter, rFPGA1_RFMOD, bRFMOD, 0x0);

		PHY_SetBBReg(Adapter, rOFDM0_TxPseuकरोNoiseWgt, (BIT31|BIT30), 0x0);
		अवरोध;

	/* 40 MHz channel*/
	हाल CHANNEL_WIDTH_40:
		PHY_SetBBReg(Adapter, rFPGA0_RFMOD, bRFMOD, 0x1);

		PHY_SetBBReg(Adapter, rFPGA1_RFMOD, bRFMOD, 0x1);

		/*  Set Control channel to upper or lower. These settings are required only क्रम 40MHz */
		PHY_SetBBReg(Adapter, rCCK0_System, bCCKSideBand, (pHalData->nCur40MhzPrimeSC>>1));

		PHY_SetBBReg(Adapter, rOFDM1_LSTF, 0xC00, pHalData->nCur40MhzPrimeSC);

		PHY_SetBBReg(Adapter, 0x818, (BIT26|BIT27), (pHalData->nCur40MhzPrimeSC == HAL_PRIME_CHNL_OFFSET_LOWER) ? 2 : 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* 3<3>Set RF related रेजिस्टर */
	PHY_RF6052SetBandwidth8723B(Adapter, pHalData->CurrentChannelBW);
पूर्ण

अटल व्योम phy_SwChnl8723B(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);
	u8 channelToSW = pHalData->CurrentChannel;

	अगर (pHalData->rf_chip == RF_PSEUDO_11N)
		वापस;
	pHalData->RfRegChnlVal[0] = ((pHalData->RfRegChnlVal[0] & 0xfffff00) | channelToSW);
	PHY_SetRFReg(padapter, ODM_RF_PATH_A, RF_CHNLBW, 0x3FF, pHalData->RfRegChnlVal[0]);
	PHY_SetRFReg(padapter, ODM_RF_PATH_B, RF_CHNLBW, 0x3FF, pHalData->RfRegChnlVal[0]);
पूर्ण

अटल व्योम phy_SwChnlAndSetBwMode8723B(काष्ठा adapter *Adapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	अगर (Adapter->bDriverStopped || Adapter->bSurpriseRemoved)
		वापस;

	अगर (pHalData->bSwChnl) अणु
		phy_SwChnl8723B(Adapter);
		pHalData->bSwChnl = false;
	पूर्ण

	अगर (pHalData->bSetChnlBW) अणु
		phy_PostSetBwMode8723B(Adapter);
		pHalData->bSetChnlBW = false;
	पूर्ण

	PHY_SetTxPowerLevel8723B(Adapter, pHalData->CurrentChannel);
पूर्ण

अटल व्योम PHY_HandleSwChnlAndSetBW8723B(
	काष्ठा adapter *Adapter,
	bool bSwitchChannel,
	bool bSetBandWidth,
	u8 ChannelNum,
	क्रमागत channel_width ChnlWidth,
	क्रमागत extchnl_offset ExtChnlOffsetOf40MHz,
	क्रमागत extchnl_offset ExtChnlOffsetOf80MHz,
	u8 CenterFrequencyIndex1
)
अणु
	/* अटल bool		bInitialzed = false; */
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	u8 पंचांगpChannel = pHalData->CurrentChannel;
	क्रमागत channel_width पंचांगpBW = pHalData->CurrentChannelBW;
	u8 पंचांगpnCur40MhzPrimeSC = pHalData->nCur40MhzPrimeSC;
	u8 पंचांगpnCur80MhzPrimeSC = pHalData->nCur80MhzPrimeSC;
	u8 पंचांगpCenterFrequencyIndex1 = pHalData->CurrentCenterFrequencyIndex1;

	/* check is swchnl or setbw */
	अगर (!bSwitchChannel && !bSetBandWidth)
		वापस;

	/* skip change क्रम channel or bandwidth is the same */
	अगर (bSwitchChannel) अणु
		अणु
			अगर (HAL_IsLegalChannel(Adapter, ChannelNum))
				pHalData->bSwChnl = true;
		पूर्ण
	पूर्ण

	अगर (bSetBandWidth)
		pHalData->bSetChnlBW = true;

	अगर (!pHalData->bSetChnlBW && !pHalData->bSwChnl)
		वापस;


	अगर (pHalData->bSwChnl) अणु
		pHalData->CurrentChannel = ChannelNum;
		pHalData->CurrentCenterFrequencyIndex1 = ChannelNum;
	पूर्ण


	अगर (pHalData->bSetChnlBW) अणु
		pHalData->CurrentChannelBW = ChnlWidth;
		pHalData->nCur40MhzPrimeSC = ExtChnlOffsetOf40MHz;
		pHalData->nCur80MhzPrimeSC = ExtChnlOffsetOf80MHz;
		pHalData->CurrentCenterFrequencyIndex1 = CenterFrequencyIndex1;
	पूर्ण

	/* Switch workitem or set समयr to करो चयन channel or setbandwidth operation */
	अगर ((!Adapter->bDriverStopped) && (!Adapter->bSurpriseRemoved)) अणु
		phy_SwChnlAndSetBwMode8723B(Adapter);
	पूर्ण अन्यथा अणु
		अगर (pHalData->bSwChnl) अणु
			pHalData->CurrentChannel = पंचांगpChannel;
			pHalData->CurrentCenterFrequencyIndex1 = पंचांगpChannel;
		पूर्ण

		अगर (pHalData->bSetChnlBW) अणु
			pHalData->CurrentChannelBW = पंचांगpBW;
			pHalData->nCur40MhzPrimeSC = पंचांगpnCur40MhzPrimeSC;
			pHalData->nCur80MhzPrimeSC = पंचांगpnCur80MhzPrimeSC;
			pHalData->CurrentCenterFrequencyIndex1 = पंचांगpCenterFrequencyIndex1;
		पूर्ण
	पूर्ण
पूर्ण

व्योम PHY_SetBWMode8723B(
	काष्ठा adapter *Adapter,
	क्रमागत channel_width Bandwidth, /*  20M or 40M */
	अचिन्हित अक्षर Offset /*  Upper, Lower, or Don't care */
)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	PHY_HandleSwChnlAndSetBW8723B(Adapter, false, true, pHalData->CurrentChannel, Bandwidth, Offset, Offset, pHalData->CurrentChannel);
पूर्ण

/*  Call after initialization */
व्योम PHY_SwChnl8723B(काष्ठा adapter *Adapter, u8 channel)
अणु
	PHY_HandleSwChnlAndSetBW8723B(Adapter, true, false, channel, 0, 0, 0, channel);
पूर्ण

व्योम PHY_SetSwChnlBWMode8723B(
	काष्ठा adapter *Adapter,
	u8 channel,
	क्रमागत channel_width Bandwidth,
	u8 Offset40,
	u8 Offset80
)
अणु
	PHY_HandleSwChnlAndSetBW8723B(Adapter, true, true, channel, Bandwidth, Offset40, Offset80, channel);
पूर्ण
