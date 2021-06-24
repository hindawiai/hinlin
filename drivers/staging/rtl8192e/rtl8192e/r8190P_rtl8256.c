<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "r8192E_phyreg.h"
#समावेश "r8192E_phy.h"
#समावेश "r8190P_rtl8256.h"

व्योम rtl92e_set_bandwidth(काष्ठा net_device *dev,
			  क्रमागत ht_channel_width Bandwidth)
अणु
	u8	eRFPath;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (priv->card_8192_version != VERSION_8190_BD &&
	    priv->card_8192_version != VERSION_8190_BE) अणु
		netdev_warn(dev, "%s(): Unknown HW version.\n", __func__);
		वापस;
	पूर्ण

	क्रम (eRFPath = 0; eRFPath < priv->NumTotalRFPath; eRFPath++) अणु
		अगर (!rtl92e_is_legal_rf_path(dev, eRFPath))
			जारी;

		चयन (Bandwidth) अणु
		हाल HT_CHANNEL_WIDTH_20:
			rtl92e_set_rf_reg(dev, (क्रमागत rf90_radio_path)eRFPath,
					  0x0b, bMask12Bits, 0x100);
			rtl92e_set_rf_reg(dev, (क्रमागत rf90_radio_path)eRFPath,
					  0x2c, bMask12Bits, 0x3d7);
			rtl92e_set_rf_reg(dev, (क्रमागत rf90_radio_path)eRFPath,
					  0x0e, bMask12Bits, 0x021);
			अवरोध;
		हाल HT_CHANNEL_WIDTH_20_40:
			rtl92e_set_rf_reg(dev, (क्रमागत rf90_radio_path)eRFPath,
					  0x0b, bMask12Bits, 0x300);
			rtl92e_set_rf_reg(dev, (क्रमागत rf90_radio_path)eRFPath,
					  0x2c, bMask12Bits, 0x3ff);
			rtl92e_set_rf_reg(dev, (क्रमागत rf90_radio_path)eRFPath,
					  0x0e, bMask12Bits, 0x0e1);
			अवरोध;
		शेष:
			netdev_err(dev, "%s(): Unknown bandwidth: %#X\n",
				   __func__, Bandwidth);
			अवरोध;

		पूर्ण
	पूर्ण
पूर्ण

bool rtl92e_config_rf(काष्ठा net_device *dev)
अणु
	u32	u4RegValue = 0;
	u8	eRFPath;
	bool rtStatus = true;
	काष्ठा bb_reg_definition *pPhyReg;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32	RegOffSetToBeCheck = 0x3;
	u32	RegValueToBeCheck = 0x7f1;
	u32	RF3_Final_Value = 0;
	u8	ConstRetryTimes = 5, RetryTimes = 5;
	u8 ret = 0;

	priv->NumTotalRFPath = RTL819X_TOTAL_RF_PATH;

	क्रम (eRFPath = (क्रमागत rf90_radio_path)RF90_PATH_A;
	     eRFPath < priv->NumTotalRFPath; eRFPath++) अणु
		अगर (!rtl92e_is_legal_rf_path(dev, eRFPath))
			जारी;

		pPhyReg = &priv->PHYRegDef[eRFPath];


		चयन (eRFPath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			u4RegValue = rtl92e_get_bb_reg(dev, pPhyReg->rfपूर्णांकfs,
						       bRFSI_RFENV);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			u4RegValue = rtl92e_get_bb_reg(dev, pPhyReg->rfपूर्णांकfs,
						       bRFSI_RFENV<<16);
			अवरोध;
		पूर्ण

		rtl92e_set_bb_reg(dev, pPhyReg->rfपूर्णांकfe, bRFSI_RFENV<<16, 0x1);

		rtl92e_set_bb_reg(dev, pPhyReg->rfपूर्णांकfo, bRFSI_RFENV, 0x1);

		rtl92e_set_bb_reg(dev, pPhyReg->rfHSSIPara2,
				  b3WireAddressLength, 0x0);
		rtl92e_set_bb_reg(dev, pPhyReg->rfHSSIPara2,
				  b3WireDataLength, 0x0);

		rtl92e_set_rf_reg(dev, (क्रमागत rf90_radio_path)eRFPath, 0x0,
				  bMask12Bits, 0xbf);

		rtStatus = rtl92e_check_bb_and_rf(dev, HW90_BLOCK_RF,
						  (क्रमागत rf90_radio_path)eRFPath);
		अगर (!rtStatus) अणु
			netdev_err(dev, "%s(): Failed to check RF Path %d.\n",
				   __func__, eRFPath);
			जाओ fail;
		पूर्ण

		RetryTimes = ConstRetryTimes;
		RF3_Final_Value = 0;
		जबतक (RF3_Final_Value != RegValueToBeCheck &&
		       RetryTimes != 0) अणु
			ret = rtl92e_config_rf_path(dev,
						(क्रमागत rf90_radio_path)eRFPath);
			RF3_Final_Value = rtl92e_get_rf_reg(dev,
						(क्रमागत rf90_radio_path)eRFPath,
						RegOffSetToBeCheck,
						bMask12Bits);
			RT_TRACE(COMP_RF,
				 "RF %d %d register final value: %x\n",
				 eRFPath, RegOffSetToBeCheck,
				 RF3_Final_Value);
			RetryTimes--;
		पूर्ण

		चयन (eRFPath) अणु
		हाल RF90_PATH_A:
		हाल RF90_PATH_C:
			rtl92e_set_bb_reg(dev, pPhyReg->rfपूर्णांकfs, bRFSI_RFENV,
					  u4RegValue);
			अवरोध;
		हाल RF90_PATH_B:
		हाल RF90_PATH_D:
			rtl92e_set_bb_reg(dev, pPhyReg->rfपूर्णांकfs,
					  bRFSI_RFENV<<16, u4RegValue);
			अवरोध;
		पूर्ण

		अगर (ret) अणु
			netdev_err(dev,
				   "%s(): Failed to initialize RF Path %d.\n",
				   __func__, eRFPath);
			जाओ fail;
		पूर्ण

	पूर्ण

	RT_TRACE(COMP_PHY, "PHY Initialization Success\n");
	वापस true;

fail:
	वापस false;
पूर्ण

व्योम rtl92e_set_cck_tx_घातer(काष्ठा net_device *dev, u8 घातerlevel)
अणु
	u32	TxAGC = 0;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	TxAGC = घातerlevel;
	अगर (priv->bDynamicTxLowPower) अणु
		अगर (priv->CustomerID == RT_CID_819x_Netcore)
			TxAGC = 0x22;
		अन्यथा
			TxAGC += priv->CckPwEnl;
	पूर्ण
	अगर (TxAGC > 0x24)
		TxAGC = 0x24;
	rtl92e_set_bb_reg(dev, rTxAGC_CCK_Mcs32, bTxAGCRateCCK, TxAGC);
पूर्ण


व्योम rtl92e_set_ofdm_tx_घातer(काष्ठा net_device *dev, u8 घातerlevel)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 ग_लिखोVal, घातerBase0, घातerBase1, ग_लिखोVal_पंचांगp;
	u8 index = 0;
	u16 RegOffset[6] = अणु0xe00, 0xe04, 0xe10, 0xe14, 0xe18, 0xe1cपूर्ण;
	u8 byte0, byte1, byte2, byte3;

	घातerBase0 = घातerlevel + priv->LegacyHTTxPowerDअगरf;
	घातerBase0 = (घातerBase0 << 24) | (घातerBase0 << 16) |
		     (घातerBase0 << 8) | घातerBase0;
	घातerBase1 = घातerlevel;
	घातerBase1 = (घातerBase1 << 24) | (घातerBase1 << 16) |
		     (घातerBase1 << 8) | घातerBase1;

	क्रम (index = 0; index < 6; index++) अणु
		ग_लिखोVal = (u32)(priv->MCSTxPowerLevelOriginalOffset[index] +
			   ((index < 2) ? घातerBase0 : घातerBase1));
		byte0 = (u8)(ग_लिखोVal & 0x7f);
		byte1 = (u8)((ग_लिखोVal & 0x7f00)>>8);
		byte2 = (u8)((ग_लिखोVal & 0x7f0000)>>16);
		byte3 = (u8)((ग_लिखोVal & 0x7f000000)>>24);
		अगर (byte0 > 0x24)
			byte0 = 0x24;
		अगर (byte1 > 0x24)
			byte1 = 0x24;
		अगर (byte2 > 0x24)
			byte2 = 0x24;
		अगर (byte3 > 0x24)
			byte3 = 0x24;

		अगर (index == 3) अणु
			ग_लिखोVal_पंचांगp = (byte3 << 24) | (byte2 << 16) |
				       (byte1 << 8) | byte0;
			priv->Pwr_Track = ग_लिखोVal_पंचांगp;
		पूर्ण

		अगर (priv->bDynamicTxHighPower)
			ग_लिखोVal = 0x03030303;
		अन्यथा
			ग_लिखोVal = (byte3 << 24) | (byte2 << 16) |
				   (byte1 << 8) | byte0;
		rtl92e_set_bb_reg(dev, RegOffset[index], 0x7f7f7f7f, ग_लिखोVal);
	पूर्ण

पूर्ण
