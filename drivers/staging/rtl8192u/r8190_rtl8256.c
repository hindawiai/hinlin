<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is part of the rtl8192 driver
 *
 * This files contains programming code क्रम the rtl8256
 * radio frontend.
 *
 * *Many* thanks to Realtek Corp. क्रम their great support!
 */

#समावेश "r8192U.h"
#समावेश "r8192U_hw.h"
#समावेश "r819xU_phyreg.h"
#समावेश "r819xU_phy.h"
#समावेश "r8190_rtl8256.h"

/*
 * Forward declaration of local functions
 */
अटल व्योम phy_rf8256_config_para_file(काष्ठा net_device *dev);

/*--------------------------------------------------------------------------
 * Overview:	set RF band width (20M or 40M)
 * Input:       काष्ठा net_device*	dev
 *		WIRELESS_BANDWIDTH_E	Bandwidth	//20M or 40M
 * Output:      NONE
 * Return:      NONE
 * Note:	8226 support both 20M  and 40 MHz
 *--------------------------------------------------------------------------
 */
व्योम phy_set_rf8256_bandwidth(काष्ठा net_device *dev, क्रमागत ht_channel_width Bandwidth)
अणु
	u8	eRFPath;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	/* क्रम(eRFPath = RF90_PATH_A; eRFPath <pHalData->NumTotalRFPath;
	 *  eRFPath++)
	 */
	क्रम (eRFPath = 0; eRFPath < RF90_PATH_MAX; eRFPath++) अणु
		अगर (!rtl8192_phy_CheckIsLegalRFPath(dev, eRFPath))
			जारी;

		चयन (Bandwidth) अणु
		हाल HT_CHANNEL_WIDTH_20:
				अगर (priv->card_8192_version == VERSION_819XU_A ||
				    priv->card_8192_version == VERSION_819XU_B) अणु
					/* 8256 D-cut, E-cut, xiong: consider it later! */
					rtl8192_phy_SetRFReg(dev,
						(क्रमागत rf90_radio_path_e)eRFPath,
						0x0b, bMask12Bits, 0x100); /* phy para:1ba */
					rtl8192_phy_SetRFReg(dev,
						(क्रमागत rf90_radio_path_e)eRFPath,
						0x2c, bMask12Bits, 0x3d7);
					rtl8192_phy_SetRFReg(dev,
						(क्रमागत rf90_radio_path_e)eRFPath,
						0x0e, bMask12Bits, 0x021);
					rtl8192_phy_SetRFReg(dev,
						(क्रमागत rf90_radio_path_e)eRFPath,
						0x14, bMask12Bits, 0x5ab);
				पूर्ण अन्यथा अणु
					RT_TRACE(COMP_ERR, "%s(): unknown hardware version\n", __func__);
					पूर्ण
				अवरोध;
		हाल HT_CHANNEL_WIDTH_20_40:
				अगर (priv->card_8192_version == VERSION_819XU_A || priv->card_8192_version == VERSION_819XU_B) अणु /* 8256 D-cut, E-cut, xiong: consider it later! */
					rtl8192_phy_SetRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, 0x0b, bMask12Bits, 0x300); /* phy para:3ba */
					rtl8192_phy_SetRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, 0x2c, bMask12Bits, 0x3df);
					rtl8192_phy_SetRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, 0x0e, bMask12Bits, 0x0a1);

					अगर (priv->chan == 3 || priv->chan == 9)
						/* I need to set priv->chan whenever current channel changes */
						rtl8192_phy_SetRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, 0x14, bMask12Bits, 0x59b);
					अन्यथा
						rtl8192_phy_SetRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, 0x14, bMask12Bits, 0x5ab);
				पूर्ण अन्यथा अणु
					RT_TRACE(COMP_ERR, "%s(): unknown hardware version\n", __func__);
					पूर्ण
				अवरोध;
		शेष:
				RT_TRACE(COMP_ERR, "%s(): unknown Bandwidth: %#X\n", __func__, Bandwidth);
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*--------------------------------------------------------------------------
 * Overview:    Interface to config 8256
 * Input:       काष्ठा net_device*	dev
 * Output:      NONE
 * Return:      NONE
 *--------------------------------------------------------------------------
 */
व्योम phy_rf8256_config(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	/* Initialize general global value
	 *
	 * TODO: Extend RF_PATH_C and RF_PATH_D in the future
	 */
	priv->NumTotalRFPath = RTL819X_TOTAL_RF_PATH;
	/* Config BB and RF */
	phy_rf8256_config_para_file(dev);
पूर्ण

/*--------------------------------------------------------------------------
 * Overview:    Interface to config 8256
 * Input:       काष्ठा net_device*	dev
 * Output:      NONE
 * Return:      NONE
 *--------------------------------------------------------------------------
 */
अटल व्योम phy_rf8256_config_para_file(काष्ठा net_device *dev)
अणु
	u32	u4RegValue = 0;
	u8	eRFPath;
	BB_REGISTER_DEFINITION_T	*pPhyReg;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	u32	RegOffSetToBeCheck = 0x3;
	u32	RegValueToBeCheck = 0x7f1;
	u32	RF3_Final_Value = 0;
	u8	ConstRetryTimes = 5, RetryTimes = 5;
	u8 ret = 0;
	/* Initialize RF */
	क्रम (eRFPath = (क्रमागत rf90_radio_path_e)RF90_PATH_A; eRFPath < priv->NumTotalRFPath; eRFPath++) अणु
		अगर (!rtl8192_phy_CheckIsLegalRFPath(dev, eRFPath))
			जारी;

		pPhyReg = &priv->PHYRegDef[eRFPath];

		/* Joseph test क्रम लघुen RF config
		 * pHalData->RfReg0Value[eRFPath] =  rtl8192_phy_QueryRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, rGlobalCtrl, bMaskDWord);
		 * ----Store original RFENV control type
		 */
		चयन (eRFPath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			u4RegValue = rtl8192_QueryBBReg(dev, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			u4RegValue = rtl8192_QueryBBReg(dev, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV << 16);
			अवरोध;
		पूर्ण

		/*----Set RF_ENV enable----*/
		rtl8192_setBBreg(dev, pPhyReg->rfपूर्णांकfe, bRFSI_RFENV << 16, 0x1);

		/*----Set RF_ENV output high----*/
		rtl8192_setBBreg(dev, pPhyReg->rfपूर्णांकfo, bRFSI_RFENV, 0x1);

		/* Set bit number of Address and Data क्रम RF रेजिस्टर */
		rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, b3WireAddressLength, 0x0);	/* Set 0 to 4 bits क्रम Z-serial and set 1 to 6 bits क्रम 8258 */
		rtl8192_setBBreg(dev, pPhyReg->rfHSSIPara2, b3WireDataLength, 0x0);	/* Set 0 to 12 bits क्रम Z-serial and 8258, and set 1 to 14 bits क्रम ??? */

		rtl8192_phy_SetRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, 0x0, bMask12Bits, 0xbf);

		/* Check RF block (क्रम FPGA platक्रमm only)----
		 * TODO: this function should be हटाओd on ASIC , Emily 2007.2.2
		 */
		अगर (rtl8192_phy_checkBBAndRF(dev, HW90_BLOCK_RF, (क्रमागत rf90_radio_path_e)eRFPath)) अणु
			RT_TRACE(COMP_ERR, "phy_rf8256_config():Check Radio[%d] Fail!!\n", eRFPath);
			जाओ phy_RF8256_Config_ParaFile_Fail;
		पूर्ण

		RetryTimes = ConstRetryTimes;
		RF3_Final_Value = 0;
		/*----Initialize RF fom connfiguration file----*/
		चयन (eRFPath) अणु
		हाल RF90_PATH_A:
			जबतक (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) अणु
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (क्रमागत rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			पूर्ण
			अवरोध;
		हाल RF90_PATH_B:
			जबतक (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) अणु
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (क्रमागत rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			पूर्ण
			अवरोध;
		हाल RF90_PATH_C:
			जबतक (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) अणु
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (क्रमागत rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			पूर्ण
			अवरोध;
		हाल RF90_PATH_D:
			जबतक (RF3_Final_Value != RegValueToBeCheck && RetryTimes != 0) अणु
				ret = rtl8192_phy_ConfigRFWithHeaderFile(dev, (क्रमागत rf90_radio_path_e)eRFPath);
				RF3_Final_Value = rtl8192_phy_QueryRFReg(dev, (क्रमागत rf90_radio_path_e)eRFPath, RegOffSetToBeCheck, bMask12Bits);
				RT_TRACE(COMP_RF, "RF %d %d register final value: %x\n", eRFPath, RegOffSetToBeCheck, RF3_Final_Value);
				RetryTimes--;
			पूर्ण
			अवरोध;
		पूर्ण

		/*----Restore RFENV control type----*/
		चयन (eRFPath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			rtl8192_setBBreg(dev, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV, u4RegValue);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			rtl8192_setBBreg(dev, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV << 16, u4RegValue);
			अवरोध;
		पूर्ण

		अगर (ret) अणु
			RT_TRACE(COMP_ERR, "%s():Radio[%d] Fail!!", __func__, eRFPath);
			जाओ phy_RF8256_Config_ParaFile_Fail;
		पूर्ण
	पूर्ण

	RT_TRACE(COMP_PHY, "PHY Initialization Success\n");
	वापस;

phy_RF8256_Config_ParaFile_Fail:
	RT_TRACE(COMP_ERR, "PHY Initialization failed\n");
पूर्ण

व्योम phy_set_rf8256_cck_tx_घातer(काष्ठा net_device *dev, u8 घातerlevel)
अणु
	u32	TxAGC = 0;
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);

	TxAGC = घातerlevel;

	अगर (priv->bDynamicTxLowPower) अणु
		अगर (priv->CustomerID == RT_CID_819x_Netcore)
			TxAGC = 0x22;
		अन्यथा
			TxAGC += priv->CckPwEnl;
	पूर्ण

	अगर (TxAGC > 0x24)
		TxAGC = 0x24;
	rtl8192_setBBreg(dev, rTxAGC_CCK_Mcs32, bTxAGCRateCCK, TxAGC);
पूर्ण

व्योम phy_set_rf8256_ofdm_tx_घातer(काष्ठा net_device *dev, u8 घातerlevel)
अणु
	काष्ठा r8192_priv *priv = ieee80211_priv(dev);
	/* Joseph TxPower क्रम 8192 testing */
	u32 ग_लिखोVal, घातerBase0, घातerBase1, ग_लिखोVal_पंचांगp;
	u8 index = 0;
	u16 RegOffset[6] = अणु0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1cपूर्ण;
	u8 byte0, byte1, byte2, byte3;

	घातerBase0 = घातerlevel + priv->TxPowerDअगरf;	/* OFDM rates */
	घातerBase0 = (घातerBase0 << 24) | (घातerBase0 << 16) | (घातerBase0 << 8) | घातerBase0;
	घातerBase1 = घातerlevel;							/* MCS rates */
	घातerBase1 = (घातerBase1 << 24) | (घातerBase1 << 16) | (घातerBase1 << 8) | घातerBase1;

	क्रम (index = 0; index < 6; index++) अणु
		ग_लिखोVal = priv->MCSTxPowerLevelOriginalOffset[index] + ((index < 2) ? घातerBase0 : घातerBase1);
		byte0 = (u8)(ग_लिखोVal & 0x7f);
		byte1 = (u8)((ग_लिखोVal & 0x7f00) >> 8);
		byte2 = (u8)((ग_लिखोVal & 0x7f0000) >> 16);
		byte3 = (u8)((ग_लिखोVal & 0x7f000000) >> 24);

		अगर (byte0 > 0x24)
			/* Max घातer index = 0x24 */
			byte0 = 0x24;
		अगर (byte1 > 0x24)
			byte1 = 0x24;
		अगर (byte2 > 0x24)
			byte2 = 0x24;
		अगर (byte3 > 0x24)
			byte3 = 0x24;

		/* क्रम tx घातer track */
		अगर (index == 3) अणु
			ग_लिखोVal_पंचांगp = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
			priv->Pwr_Track = ग_लिखोVal_पंचांगp;
		पूर्ण

		अगर (priv->bDynamicTxHighPower) अणु
			/*Add by Jacken 2008/03/06
			 *Emily, 20080613. Set low tx घातer क्रम both MCS and legacy OFDM
			 */
			ग_लिखोVal = 0x03030303;
		पूर्ण अन्यथा अणु
			ग_लिखोVal = (byte3 << 24) | (byte2 << 16) | (byte1 << 8) | byte0;
		पूर्ण
		rtl8192_setBBreg(dev, RegOffset[index], 0x7f7f7f7f, ग_लिखोVal);
	पूर्ण
पूर्ण
