<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Based on the r8180 driver, which is:
 * Copyright 2004-2005 Andrea Merello <andrea.merello@gmail.com>, et al.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtl_core.h"
#समावेश "r8192E_phy.h"
#समावेश "r8192E_phyreg.h"
#समावेश "r8190P_rtl8256.h"
#समावेश "r8192E_cmdpkt.h"
#समावेश "rtl_dm.h"
#समावेश "rtl_wx.h"

अटल पूर्णांक WDCAPARA_ADD[] = अणुEDCAPARA_BE, EDCAPARA_BK, EDCAPARA_VI,
			     EDCAPARA_VOपूर्ण;

व्योम rtl92e_start_beacon(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	काष्ठा rtllib_network *net = &priv->rtllib->current_network;
	u16 BcnTimeCfg = 0;
	u16 BcnCW = 6;
	u16 BcnIFS = 0xf;

	rtl92e_irq_disable(dev);

	rtl92e_ग_लिखोw(dev, ATIMWND, 2);

	rtl92e_ग_लिखोw(dev, BCN_INTERVAL, net->beacon_पूर्णांकerval);
	rtl92e_ग_लिखोw(dev, BCN_DRV_EARLY_INT, 10);
	rtl92e_ग_लिखोw(dev, BCN_DMATIME, 256);

	rtl92e_ग_लिखोb(dev, BCN_ERR_THRESH, 100);

	BcnTimeCfg |= BcnCW<<BCN_TCFG_CW_SHIFT;
	BcnTimeCfg |= BcnIFS<<BCN_TCFG_IFS;
	rtl92e_ग_लिखोw(dev, BCN_TCFG, BcnTimeCfg);
	rtl92e_irq_enable(dev);
पूर्ण

अटल व्योम _rtl92e_update_msr(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u8 msr;
	क्रमागत led_ctl_mode LedAction = LED_CTL_NO_LINK;

	msr  = rtl92e_पढ़ोb(dev, MSR);
	msr &= ~MSR_LINK_MASK;

	चयन (priv->rtllib->iw_mode) अणु
	हाल IW_MODE_INFRA:
		अगर (priv->rtllib->state == RTLLIB_LINKED)
			msr |= (MSR_LINK_MANAGED << MSR_LINK_SHIFT);
		अन्यथा
			msr |= (MSR_LINK_NONE << MSR_LINK_SHIFT);
		LedAction = LED_CTL_LINK;
		अवरोध;
	हाल IW_MODE_ADHOC:
		अगर (priv->rtllib->state == RTLLIB_LINKED)
			msr |= (MSR_LINK_ADHOC << MSR_LINK_SHIFT);
		अन्यथा
			msr |= (MSR_LINK_NONE << MSR_LINK_SHIFT);
		अवरोध;
	हाल IW_MODE_MASTER:
		अगर (priv->rtllib->state == RTLLIB_LINKED)
			msr |= (MSR_LINK_MASTER << MSR_LINK_SHIFT);
		अन्यथा
			msr |= (MSR_LINK_NONE << MSR_LINK_SHIFT);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rtl92e_ग_लिखोb(dev, MSR, msr);
	अगर (priv->rtllib->LedControlHandler)
		priv->rtllib->LedControlHandler(dev, LedAction);
पूर्ण

व्योम rtl92e_set_reg(काष्ठा net_device *dev, u8 variable, u8 *val)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	चयन (variable) अणु
	हाल HW_VAR_BSSID:
		/* BSSIDR 2 byte alignment */
		rtl92e_ग_लिखोw(dev, BSSIDR, *(u16 *)val);
		rtl92e_ग_लिखोl(dev, BSSIDR + 2, *(u32 *)(val + 2));
		अवरोध;

	हाल HW_VAR_MEDIA_STATUS:
	अणु
		क्रमागत rt_op_mode OpMode = *((क्रमागत rt_op_mode *)(val));
		u8 btMsr = rtl92e_पढ़ोb(dev, MSR);

		btMsr &= 0xfc;

		चयन (OpMode) अणु
		हाल RT_OP_MODE_INFRASTRUCTURE:
			btMsr |= MSR_INFRA;
			अवरोध;

		हाल RT_OP_MODE_IBSS:
			btMsr |= MSR_ADHOC;
			अवरोध;

		हाल RT_OP_MODE_AP:
			btMsr |= MSR_AP;
			अवरोध;

		शेष:
			btMsr |= MSR_NOLINK;
			अवरोध;
		पूर्ण

		rtl92e_ग_लिखोb(dev, MSR, btMsr);

	पूर्ण
	अवरोध;

	हाल HW_VAR_CECHK_BSSID:
	अणु
		u32	RegRCR, Type;

		Type = val[0];
		RegRCR = rtl92e_पढ़ोl(dev, RCR);
		priv->ReceiveConfig = RegRCR;

		अगर (Type)
			RegRCR |= (RCR_CBSSID);
		अन्यथा
			RegRCR &= (~RCR_CBSSID);

		rtl92e_ग_लिखोl(dev, RCR, RegRCR);
		priv->ReceiveConfig = RegRCR;

	पूर्ण
	अवरोध;

	हाल HW_VAR_SLOT_TIME:

		priv->slot_समय = val[0];
		rtl92e_ग_लिखोb(dev, SLOT_TIME, val[0]);

		अवरोध;

	हाल HW_VAR_ACK_PREAMBLE:
	अणु
		u32 regTmp;

		priv->लघु_preamble = (bool)*val;
		regTmp = priv->basic_rate;
		अगर (priv->लघु_preamble)
			regTmp |= BRSR_AckShortPmb;
		rtl92e_ग_लिखोl(dev, RRSR, regTmp);
		अवरोध;
	पूर्ण

	हाल HW_VAR_CPU_RST:
		rtl92e_ग_लिखोl(dev, CPU_GEN, ((u32 *)(val))[0]);
		अवरोध;

	हाल HW_VAR_AC_PARAM:
	अणु
		u8	pAcParam = *val;
		u32	eACI = pAcParam;
		u8		u1bAIFS;
		u32		u4bAcParam;
		u8 mode = priv->rtllib->mode;
		काष्ठा rtllib_qos_parameters *qop =
			 &priv->rtllib->current_network.qos_data.parameters;

		u1bAIFS = qop->aअगरs[pAcParam] *
			  ((mode&(IEEE_G|IEEE_N_24G)) ? 9 : 20) + aSअगरsTime;

		rtl92e_dm_init_edca_turbo(dev);

		u4bAcParam = (le16_to_cpu(qop->tx_op_limit[pAcParam]) <<
			      AC_PARAM_TXOP_LIMIT_OFFSET) |
				((le16_to_cpu(qop->cw_max[pAcParam])) <<
				 AC_PARAM_ECW_MAX_OFFSET) |
				((le16_to_cpu(qop->cw_min[pAcParam])) <<
				 AC_PARAM_ECW_MIN_OFFSET) |
				(((u32)u1bAIFS) << AC_PARAM_AIFS_OFFSET);

		RT_TRACE(COMP_DBG, "%s():HW_VAR_AC_PARAM eACI:%x:%x\n",
			 __func__, eACI, u4bAcParam);
		चयन (eACI) अणु
		हाल AC1_BK:
			rtl92e_ग_लिखोl(dev, EDCAPARA_BK, u4bAcParam);
			अवरोध;

		हाल AC0_BE:
			rtl92e_ग_लिखोl(dev, EDCAPARA_BE, u4bAcParam);
			अवरोध;

		हाल AC2_VI:
			rtl92e_ग_लिखोl(dev, EDCAPARA_VI, u4bAcParam);
			अवरोध;

		हाल AC3_VO:
			rtl92e_ग_लिखोl(dev, EDCAPARA_VO, u4bAcParam);
			अवरोध;

		शेष:
			netdev_info(dev, "SetHwReg8185(): invalid ACI: %d !\n",
				    eACI);
			अवरोध;
		पूर्ण
		priv->rtllib->SetHwRegHandler(dev, HW_VAR_ACM_CTRL,
					      &pAcParam);
		अवरोध;
	पूर्ण

	हाल HW_VAR_ACM_CTRL:
	अणु
		काष्ठा rtllib_qos_parameters *qos_parameters =
			 &priv->rtllib->current_network.qos_data.parameters;
		u8 pAcParam = *val;
		u32 eACI = pAcParam;
		जोड़ aci_aअगरsn *pAciAअगरsn = (जोड़ aci_aअगरsn *) &
					      (qos_parameters->aअगरs[0]);
		u8 acm = pAciAअगरsn->f.acm;
		u8 AcmCtrl = rtl92e_पढ़ोb(dev, AcmHwCtrl);

		RT_TRACE(COMP_DBG, "===========>%s():HW_VAR_ACM_CTRL:%x\n",
			 __func__, eACI);
		AcmCtrl = AcmCtrl | ((priv->AcmMethod == 2) ? 0x0 : 0x1);

		अगर (acm) अणु
			चयन (eACI) अणु
			हाल AC0_BE:
				AcmCtrl |= AcmHw_BeqEn;
				अवरोध;

			हाल AC2_VI:
				AcmCtrl |= AcmHw_ViqEn;
				अवरोध;

			हाल AC3_VO:
				AcmCtrl |= AcmHw_VoqEn;
				अवरोध;

			शेष:
				RT_TRACE(COMP_QOS,
					 "SetHwReg8185(): [HW_VAR_ACM_CTRL] acm set failed: eACI is %d\n",
					 eACI);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (eACI) अणु
			हाल AC0_BE:
				AcmCtrl &= (~AcmHw_BeqEn);
				अवरोध;

			हाल AC2_VI:
				AcmCtrl &= (~AcmHw_ViqEn);
				अवरोध;

			हाल AC3_VO:
				AcmCtrl &= (~AcmHw_BeqEn);
				अवरोध;

			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		RT_TRACE(COMP_QOS,
			 "SetHwReg8190pci(): [HW_VAR_ACM_CTRL] Write 0x%X\n",
			 AcmCtrl);
		rtl92e_ग_लिखोb(dev, AcmHwCtrl, AcmCtrl);
		अवरोध;
	पूर्ण

	हाल HW_VAR_SIFS:
		rtl92e_ग_लिखोb(dev, SIFS, val[0]);
		rtl92e_ग_लिखोb(dev, SIFS+1, val[0]);
		अवरोध;

	हाल HW_VAR_RF_TIMING:
	अणु
		u8 Rf_Timing = *val;

		rtl92e_ग_लिखोb(dev, rFPGA0_RFTiming1, Rf_Timing);
		अवरोध;
	पूर्ण

	शेष:
		अवरोध;
	पूर्ण

पूर्ण

अटल व्योम _rtl92e_पढ़ो_eeprom_info(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	स्थिर u8 bMac_Tmp_Addr[ETH_ALEN] = अणु0x00, 0xe0, 0x4c, 0x00, 0x00, 0x01पूर्ण;
	u8 tempval;
	u8 ICVer8192, ICVer8256;
	u16 i, usValue, IC_Version;
	u16 EEPROMId;

	RT_TRACE(COMP_INIT, "====> %s\n", __func__);

	EEPROMId = rtl92e_eeprom_पढ़ो(dev, 0);
	अगर (EEPROMId != RTL8190_EEPROM_ID) अणु
		netdev_err(dev, "%s(): Invalid EEPROM ID: %x\n", __func__,
			   EEPROMId);
		priv->AutoloadFailFlag = true;
	पूर्ण अन्यथा अणु
		priv->AutoloadFailFlag = false;
	पूर्ण

	अगर (!priv->AutoloadFailFlag) अणु
		priv->eeprom_vid = rtl92e_eeprom_पढ़ो(dev, EEPROM_VID >> 1);
		priv->eeprom_did = rtl92e_eeprom_पढ़ो(dev, EEPROM_DID >> 1);

		usValue = rtl92e_eeprom_पढ़ो(dev,
					     (u16)(EEPROM_Customer_ID>>1)) >> 8;
		priv->eeprom_CustomerID = (u8)(usValue & 0xff);
		usValue = rtl92e_eeprom_पढ़ो(dev,
					     EEPROM_ICVersion_ChannelPlan>>1);
		priv->eeprom_ChannelPlan = usValue&0xff;
		IC_Version = (usValue & 0xff00)>>8;

		ICVer8192 = IC_Version & 0xf;
		ICVer8256 = (IC_Version & 0xf0)>>4;
		RT_TRACE(COMP_INIT, "\nICVer8192 = 0x%x\n", ICVer8192);
		RT_TRACE(COMP_INIT, "\nICVer8256 = 0x%x\n", ICVer8256);
		अगर (ICVer8192 == 0x2) अणु
			अगर (ICVer8256 == 0x5)
				priv->card_8192_version = VERSION_8190_BE;
		पूर्ण
		चयन (priv->card_8192_version) अणु
		हाल VERSION_8190_BD:
		हाल VERSION_8190_BE:
			अवरोध;
		शेष:
			priv->card_8192_version = VERSION_8190_BD;
			अवरोध;
		पूर्ण
		RT_TRACE(COMP_INIT, "\nIC Version = 0x%x\n",
			  priv->card_8192_version);
	पूर्ण अन्यथा अणु
		priv->card_8192_version = VERSION_8190_BD;
		priv->eeprom_vid = 0;
		priv->eeprom_did = 0;
		priv->eeprom_CustomerID = 0;
		priv->eeprom_ChannelPlan = 0;
		RT_TRACE(COMP_INIT, "\nIC Version = 0x%x\n", 0xff);
	पूर्ण

	RT_TRACE(COMP_INIT, "EEPROM VID = 0x%4x\n", priv->eeprom_vid);
	RT_TRACE(COMP_INIT, "EEPROM DID = 0x%4x\n", priv->eeprom_did);
	RT_TRACE(COMP_INIT, "EEPROM Customer ID: 0x%2x\n",
		 priv->eeprom_CustomerID);

	अगर (!priv->AutoloadFailFlag) अणु
		क्रम (i = 0; i < 6; i += 2) अणु
			usValue = rtl92e_eeprom_पढ़ो(dev,
				 (EEPROM_NODE_ADDRESS_BYTE_0 + i) >> 1);
			*(u16 *)(&dev->dev_addr[i]) = usValue;
		पूर्ण
	पूर्ण अन्यथा अणु
		ether_addr_copy(dev->dev_addr, bMac_Tmp_Addr);
	पूर्ण

	RT_TRACE(COMP_INIT, "Permanent Address = %pM\n",
		 dev->dev_addr);

	अगर (priv->card_8192_version > VERSION_8190_BD)
		priv->bTXPowerDataReadFromEEPORM = true;
	अन्यथा
		priv->bTXPowerDataReadFromEEPORM = false;

	priv->rf_type = RTL819X_DEFAULT_RF_TYPE;

	अगर (priv->card_8192_version > VERSION_8190_BD) अणु
		अगर (!priv->AutoloadFailFlag) अणु
			tempval = (rtl92e_eeprom_पढ़ो(dev,
						      (EEPROM_RFInd_PowerDअगरf >> 1))) & 0xff;
			priv->EEPROMLegacyHTTxPowerDअगरf = tempval & 0xf;

			अगर (tempval&0x80)
				priv->rf_type = RF_1T2R;
			अन्यथा
				priv->rf_type = RF_2T4R;
		पूर्ण अन्यथा अणु
			priv->EEPROMLegacyHTTxPowerDअगरf = 0x04;
		पूर्ण
		RT_TRACE(COMP_INIT, "EEPROMLegacyHTTxPowerDiff = %d\n",
			priv->EEPROMLegacyHTTxPowerDअगरf);

		अगर (!priv->AutoloadFailFlag)
			priv->EEPROMThermalMeter = (u8)(((rtl92e_eeprom_पढ़ो(dev,
						   (EEPROM_ThermalMeter>>1))) &
						   0xff00)>>8);
		अन्यथा
			priv->EEPROMThermalMeter = EEPROM_Default_ThermalMeter;
		RT_TRACE(COMP_INIT, "ThermalMeter = %d\n",
			 priv->EEPROMThermalMeter);
		priv->TSSI_13dBm = priv->EEPROMThermalMeter * 100;

		अगर (priv->epromtype == EEPROM_93C46) अणु
			अगर (!priv->AutoloadFailFlag) अणु
				usValue = rtl92e_eeprom_पढ़ो(dev,
					  EEPROM_TxPwDअगरf_CrystalCap >> 1);
				priv->EEPROMAntPwDअगरf = usValue & 0x0fff;
				priv->EEPROMCrystalCap = (u8)((usValue & 0xf000)
							 >> 12);
			पूर्ण अन्यथा अणु
				priv->EEPROMAntPwDअगरf =
					 EEPROM_Default_AntTxPowerDअगरf;
				priv->EEPROMCrystalCap =
					 EEPROM_Default_TxPwDअगरf_CrystalCap;
			पूर्ण
			RT_TRACE(COMP_INIT, "EEPROMAntPwDiff = %d\n",
				 priv->EEPROMAntPwDअगरf);
			RT_TRACE(COMP_INIT, "EEPROMCrystalCap = %d\n",
				 priv->EEPROMCrystalCap);

			क्रम (i = 0; i < 14; i += 2) अणु
				अगर (!priv->AutoloadFailFlag)
					usValue = rtl92e_eeprom_पढ़ो(dev,
						  (EEPROM_TxPwIndex_CCK + i) >> 1);
				अन्यथा
					usValue = EEPROM_Default_TxPower;
				*((u16 *)(&priv->EEPROMTxPowerLevelCCK[i])) =
								 usValue;
				RT_TRACE(COMP_INIT,
					 "CCK Tx Power Level, Index %d = 0x%02x\n",
					 i, priv->EEPROMTxPowerLevelCCK[i]);
				RT_TRACE(COMP_INIT,
					 "CCK Tx Power Level, Index %d = 0x%02x\n",
					 i+1, priv->EEPROMTxPowerLevelCCK[i+1]);
			पूर्ण
			क्रम (i = 0; i < 14; i += 2) अणु
				अगर (!priv->AutoloadFailFlag)
					usValue = rtl92e_eeprom_पढ़ो(dev,
						(EEPROM_TxPwIndex_OFDM_24G + i) >> 1);
				अन्यथा
					usValue = EEPROM_Default_TxPower;
				*((u16 *)(&priv->EEPROMTxPowerLevelOFDM24G[i]))
							 = usValue;
				RT_TRACE(COMP_INIT,
					 "OFDM 2.4G Tx Power Level, Index %d = 0x%02x\n",
					 i, priv->EEPROMTxPowerLevelOFDM24G[i]);
				RT_TRACE(COMP_INIT,
					 "OFDM 2.4G Tx Power Level, Index %d = 0x%02x\n",
					 i + 1,
					 priv->EEPROMTxPowerLevelOFDM24G[i+1]);
			पूर्ण
		पूर्ण
		अगर (priv->epromtype == EEPROM_93C46) अणु
			क्रम (i = 0; i < 14; i++) अणु
				priv->TxPowerLevelCCK[i] =
					 priv->EEPROMTxPowerLevelCCK[i];
				priv->TxPowerLevelOFDM24G[i] =
					 priv->EEPROMTxPowerLevelOFDM24G[i];
			पूर्ण
			priv->LegacyHTTxPowerDअगरf =
					 priv->EEPROMLegacyHTTxPowerDअगरf;
			priv->AntennaTxPwDअगरf[0] = priv->EEPROMAntPwDअगरf & 0xf;
			priv->AntennaTxPwDअगरf[1] = (priv->EEPROMAntPwDअगरf &
							0xf0) >> 4;
			priv->AntennaTxPwDअगरf[2] = (priv->EEPROMAntPwDअगरf &
							0xf00) >> 8;
			priv->CrystalCap = priv->EEPROMCrystalCap;
			priv->ThermalMeter[0] = priv->EEPROMThermalMeter & 0xf;
			priv->ThermalMeter[1] = (priv->EEPROMThermalMeter &
						     0xf0) >> 4;
		पूर्ण अन्यथा अगर (priv->epromtype == EEPROM_93C56) अणु

			क्रम (i = 0; i < 3; i++) अणु
				priv->TxPowerLevelCCK_A[i] =
					 priv->EEPROMRfACCKChnl1TxPwLevel[0];
				priv->TxPowerLevelOFDM24G_A[i] =
					 priv->EEPROMRfAOfdmChnlTxPwLevel[0];
				priv->TxPowerLevelCCK_C[i] =
					 priv->EEPROMRfCCCKChnl1TxPwLevel[0];
				priv->TxPowerLevelOFDM24G_C[i] =
					 priv->EEPROMRfCOfdmChnlTxPwLevel[0];
			पूर्ण
			क्रम (i = 3; i < 9; i++) अणु
				priv->TxPowerLevelCCK_A[i]  =
					 priv->EEPROMRfACCKChnl1TxPwLevel[1];
				priv->TxPowerLevelOFDM24G_A[i] =
					 priv->EEPROMRfAOfdmChnlTxPwLevel[1];
				priv->TxPowerLevelCCK_C[i] =
					 priv->EEPROMRfCCCKChnl1TxPwLevel[1];
				priv->TxPowerLevelOFDM24G_C[i] =
					 priv->EEPROMRfCOfdmChnlTxPwLevel[1];
			पूर्ण
			क्रम (i = 9; i < 14; i++) अणु
				priv->TxPowerLevelCCK_A[i]  =
					 priv->EEPROMRfACCKChnl1TxPwLevel[2];
				priv->TxPowerLevelOFDM24G_A[i] =
					 priv->EEPROMRfAOfdmChnlTxPwLevel[2];
				priv->TxPowerLevelCCK_C[i] =
					 priv->EEPROMRfCCCKChnl1TxPwLevel[2];
				priv->TxPowerLevelOFDM24G_C[i] =
					 priv->EEPROMRfCOfdmChnlTxPwLevel[2];
			पूर्ण
			क्रम (i = 0; i < 14; i++)
				RT_TRACE(COMP_INIT,
					 "priv->TxPowerLevelCCK_A[%d] = 0x%x\n",
					 i, priv->TxPowerLevelCCK_A[i]);
			क्रम (i = 0; i < 14; i++)
				RT_TRACE(COMP_INIT,
					 "priv->TxPowerLevelOFDM24G_A[%d] = 0x%x\n",
					 i, priv->TxPowerLevelOFDM24G_A[i]);
			क्रम (i = 0; i < 14; i++)
				RT_TRACE(COMP_INIT,
					 "priv->TxPowerLevelCCK_C[%d] = 0x%x\n",
					 i, priv->TxPowerLevelCCK_C[i]);
			क्रम (i = 0; i < 14; i++)
				RT_TRACE(COMP_INIT,
					 "priv->TxPowerLevelOFDM24G_C[%d] = 0x%x\n",
					 i, priv->TxPowerLevelOFDM24G_C[i]);
			priv->LegacyHTTxPowerDअगरf =
				 priv->EEPROMLegacyHTTxPowerDअगरf;
			priv->AntennaTxPwDअगरf[0] = 0;
			priv->AntennaTxPwDअगरf[1] = 0;
			priv->AntennaTxPwDअगरf[2] = 0;
			priv->CrystalCap = priv->EEPROMCrystalCap;
			priv->ThermalMeter[0] = priv->EEPROMThermalMeter & 0xf;
			priv->ThermalMeter[1] = (priv->EEPROMThermalMeter &
						     0xf0) >> 4;
		पूर्ण
	पूर्ण

	अगर (priv->rf_type == RF_1T2R) अणु
		/* no matter what checkpatch says, the braces are needed */
		RT_TRACE(COMP_INIT, "\n1T2R config\n");
	पूर्ण अन्यथा अगर (priv->rf_type == RF_2T4R) अणु
		RT_TRACE(COMP_INIT, "\n2T4R config\n");
	पूर्ण

	rtl92e_init_adaptive_rate(dev);

	priv->rf_chip = RF_8256;

	अगर (priv->RegChannelPlan == 0xf)
		priv->ChannelPlan = priv->eeprom_ChannelPlan;
	अन्यथा
		priv->ChannelPlan = priv->RegChannelPlan;

	अगर (priv->eeprom_vid == 0x1186 &&  priv->eeprom_did == 0x3304)
		priv->CustomerID =  RT_CID_DLINK;

	चयन (priv->eeprom_CustomerID) अणु
	हाल EEPROM_CID_DEFAULT:
		priv->CustomerID = RT_CID_DEFAULT;
		अवरोध;
	हाल EEPROM_CID_CAMEO:
		priv->CustomerID = RT_CID_819x_CAMEO;
		अवरोध;
	हाल  EEPROM_CID_RUNTOP:
		priv->CustomerID = RT_CID_819x_RUNTOP;
		अवरोध;
	हाल EEPROM_CID_NetCore:
		priv->CustomerID = RT_CID_819x_Netcore;
		अवरोध;
	हाल EEPROM_CID_TOSHIBA:
		priv->CustomerID = RT_CID_TOSHIBA;
		अगर (priv->eeprom_ChannelPlan&0x80)
			priv->ChannelPlan = priv->eeprom_ChannelPlan&0x7f;
		अन्यथा
			priv->ChannelPlan = 0x0;
		RT_TRACE(COMP_INIT, "Toshiba ChannelPlan = 0x%x\n",
			priv->ChannelPlan);
		अवरोध;
	हाल EEPROM_CID_Nettronix:
		priv->ScanDelay = 100;
		priv->CustomerID = RT_CID_Nettronix;
		अवरोध;
	हाल EEPROM_CID_Pronet:
		priv->CustomerID = RT_CID_PRONET;
		अवरोध;
	हाल EEPROM_CID_DLINK:
		priv->CustomerID = RT_CID_DLINK;
		अवरोध;

	हाल EEPROM_CID_WHQL:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (priv->ChannelPlan > CHANNEL_PLAN_LEN - 1)
		priv->ChannelPlan = 0;
	priv->ChannelPlan = COUNTRY_CODE_WORLD_WIDE_13;

	अगर (priv->eeprom_vid == 0x1186 &&  priv->eeprom_did == 0x3304)
		priv->rtllib->bSupportRemoteWakeUp = true;
	अन्यथा
		priv->rtllib->bSupportRemoteWakeUp = false;

	RT_TRACE(COMP_INIT, "RegChannelPlan(%d)\n", priv->RegChannelPlan);
	RT_TRACE(COMP_INIT, "ChannelPlan = %d\n", priv->ChannelPlan);
	RT_TRACE(COMP_TRACE, "<==== ReadAdapterInfo\n");
पूर्ण

व्योम rtl92e_get_eeprom_size(काष्ठा net_device *dev)
अणु
	u16 curCR;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	RT_TRACE(COMP_INIT, "===========>%s()\n", __func__);
	curCR = rtl92e_पढ़ोw(dev, EPROM_CMD);
	RT_TRACE(COMP_INIT, "read from Reg Cmd9346CR(%x):%x\n", EPROM_CMD,
		 curCR);
	priv->epromtype = (curCR & EPROM_CMD_9356SEL) ? EEPROM_93C56 :
			  EEPROM_93C46;
	RT_TRACE(COMP_INIT, "<===========%s(), epromtype:%d\n", __func__,
		 priv->epromtype);
	_rtl92e_पढ़ो_eeprom_info(dev);
पूर्ण

अटल व्योम _rtl92e_hwconfig(काष्ठा net_device *dev)
अणु
	u32 regRATR = 0, regRRSR = 0;
	u8 regBwOpMode = 0, regTmp = 0;
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	चयन (priv->rtllib->mode) अणु
	हाल WIRELESS_MODE_B:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK;
		regRRSR = RATE_ALL_CCK;
		अवरोध;
	हाल WIRELESS_MODE_A:
		regBwOpMode = BW_OPMODE_5G | BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_OFDM_AG;
		regRRSR = RATE_ALL_OFDM_AG;
		अवरोध;
	हाल WIRELESS_MODE_G:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		अवरोध;
	हाल WIRELESS_MODE_AUTO:
	हाल WIRELESS_MODE_N_24G:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG |
			  RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
		regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		अवरोध;
	हाल WIRELESS_MODE_N_5G:
		regBwOpMode = BW_OPMODE_5G;
		regRATR = RATE_ALL_OFDM_AG | RATE_ALL_OFDM_1SS |
			  RATE_ALL_OFDM_2SS;
		regRRSR = RATE_ALL_OFDM_AG;
		अवरोध;
	शेष:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		अवरोध;
	पूर्ण

	rtl92e_ग_लिखोb(dev, BW_OPMODE, regBwOpMode);
	अणु
		u32 ratr_value;

		ratr_value = regRATR;
		अगर (priv->rf_type == RF_1T2R)
			ratr_value &= ~(RATE_ALL_OFDM_2SS);
		rtl92e_ग_लिखोl(dev, RATR0, ratr_value);
		rtl92e_ग_लिखोb(dev, UFWP, 1);
	पूर्ण
	regTmp = rtl92e_पढ़ोb(dev, 0x313);
	regRRSR = ((regTmp) << 24) | (regRRSR & 0x00ffffff);
	rtl92e_ग_लिखोl(dev, RRSR, regRRSR);

	rtl92e_ग_लिखोw(dev, RETRY_LIMIT,
		      priv->ShortRetryLimit << RETRY_LIMIT_SHORT_SHIFT |
		      priv->LongRetryLimit << RETRY_LIMIT_LONG_SHIFT);
पूर्ण

bool rtl92e_start_adapter(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u32 ulRegRead;
	bool rtStatus = true;
	u8 पंचांगpvalue;
	u8 ICVersion, SwitchingRegulatorOutput;
	bool bfirmwareok = true;
	u32 पंचांगpRegA, TempCCk;
	पूर्णांक i = 0;
	u32 retry_बार = 0;

	RT_TRACE(COMP_INIT, "====>%s()\n", __func__);
	priv->being_init_adapter = true;

start:
	rtl92e_reset_desc_ring(dev);
	priv->Rf_Mode = RF_OP_By_SW_3wire;
	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
		rtl92e_ग_लिखोb(dev, ANAPAR, 0x37);
		mdelay(500);
	पूर्ण
	priv->pFirmware->status = FW_STATUS_0_INIT;

	अगर (priv->RegRfOff)
		priv->rtllib->eRFPowerState = eRfOff;

	ulRegRead = rtl92e_पढ़ोl(dev, CPU_GEN);
	अगर (priv->pFirmware->status == FW_STATUS_0_INIT)
		ulRegRead |= CPU_GEN_SYSTEM_RESET;
	अन्यथा अगर (priv->pFirmware->status == FW_STATUS_5_READY)
		ulRegRead |= CPU_GEN_FIRMWARE_RESET;
	अन्यथा
		netdev_err(dev, "%s(): undefined firmware state: %d.\n",
			   __func__, priv->pFirmware->status);

	rtl92e_ग_लिखोl(dev, CPU_GEN, ulRegRead);

	ICVersion = rtl92e_पढ़ोb(dev, IC_VERRSION);
	अगर (ICVersion >= 0x4) अणु
		SwitchingRegulatorOutput = rtl92e_पढ़ोb(dev, SWREGULATOR);
		अगर (SwitchingRegulatorOutput  != 0xb8) अणु
			rtl92e_ग_लिखोb(dev, SWREGULATOR, 0xa8);
			mdelay(1);
			rtl92e_ग_लिखोb(dev, SWREGULATOR, 0xb8);
		पूर्ण
	पूर्ण
	RT_TRACE(COMP_INIT, "BB Config Start!\n");
	rtStatus = rtl92e_config_bb(dev);
	अगर (!rtStatus) अणु
		netdev_warn(dev, "%s(): Failed to configure BB\n", __func__);
		वापस rtStatus;
	पूर्ण
	RT_TRACE(COMP_INIT, "BB Config Finished!\n");

	priv->LoopbackMode = RTL819X_NO_LOOPBACK;
	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
		ulRegRead = rtl92e_पढ़ोl(dev, CPU_GEN);
		अगर (priv->LoopbackMode == RTL819X_NO_LOOPBACK)
			ulRegRead = (ulRegRead & CPU_GEN_NO_LOOPBACK_MSK) |
				    CPU_GEN_NO_LOOPBACK_SET;
		अन्यथा अगर (priv->LoopbackMode == RTL819X_MAC_LOOPBACK)
			ulRegRead |= CPU_CCK_LOOPBACK;
		अन्यथा
			netdev_err(dev, "%s: Invalid loopback mode setting.\n",
				   __func__);

		rtl92e_ग_लिखोl(dev, CPU_GEN, ulRegRead);

		udelay(500);
	पूर्ण
	_rtl92e_hwconfig(dev);
	rtl92e_ग_लिखोb(dev, CMDR, CR_RE | CR_TE);

	rtl92e_ग_लिखोb(dev, PCIF, ((MXDMA2_NoLimit<<MXDMA2_RX_SHIFT) |
				  (MXDMA2_NoLimit<<MXDMA2_TX_SHIFT)));
	rtl92e_ग_लिखोl(dev, MAC0, ((u32 *)dev->dev_addr)[0]);
	rtl92e_ग_लिखोw(dev, MAC4, ((u16 *)(dev->dev_addr + 4))[0]);
	rtl92e_ग_लिखोl(dev, RCR, priv->ReceiveConfig);

	rtl92e_ग_लिखोl(dev, RQPN1, NUM_OF_PAGE_IN_FW_QUEUE_BK <<
		      RSVD_FW_QUEUE_PAGE_BK_SHIFT |
		      NUM_OF_PAGE_IN_FW_QUEUE_BE <<
		      RSVD_FW_QUEUE_PAGE_BE_SHIFT |
		      NUM_OF_PAGE_IN_FW_QUEUE_VI <<
		      RSVD_FW_QUEUE_PAGE_VI_SHIFT |
		      NUM_OF_PAGE_IN_FW_QUEUE_VO <<
		      RSVD_FW_QUEUE_PAGE_VO_SHIFT);
	rtl92e_ग_लिखोl(dev, RQPN2, NUM_OF_PAGE_IN_FW_QUEUE_MGNT <<
		      RSVD_FW_QUEUE_PAGE_MGNT_SHIFT);
	rtl92e_ग_लिखोl(dev, RQPN3, APPLIED_RESERVED_QUEUE_IN_FW |
		      NUM_OF_PAGE_IN_FW_QUEUE_BCN <<
		      RSVD_FW_QUEUE_PAGE_BCN_SHIFT|
		      NUM_OF_PAGE_IN_FW_QUEUE_PUB <<
		      RSVD_FW_QUEUE_PAGE_PUB_SHIFT);

	rtl92e_tx_enable(dev);
	rtl92e_rx_enable(dev);
	ulRegRead = (0xFFF00000 & rtl92e_पढ़ोl(dev, RRSR))  |
		     RATE_ALL_OFDM_AG | RATE_ALL_CCK;
	rtl92e_ग_लिखोl(dev, RRSR, ulRegRead);
	rtl92e_ग_लिखोl(dev, RATR0+4*7, (RATE_ALL_OFDM_AG | RATE_ALL_CCK));

	rtl92e_ग_लिखोb(dev, ACK_TIMEOUT, 0x30);

	अगर (priv->ResetProgress == RESET_TYPE_NORESET)
		rtl92e_set_wireless_mode(dev, priv->rtllib->mode);
	rtl92e_cam_reset(dev);
	अणु
		u8 SECR_value = 0x0;

		SECR_value |= SCR_TxEncEnable;
		SECR_value |= SCR_RxDecEnable;
		SECR_value |= SCR_NoSKMC;
		rtl92e_ग_लिखोb(dev, SECR, SECR_value);
	पूर्ण
	rtl92e_ग_लिखोw(dev, ATIMWND, 2);
	rtl92e_ग_लिखोw(dev, BCN_INTERVAL, 100);

	क्रम (i = 0; i < QOS_QUEUE_NUM; i++)
		rtl92e_ग_लिखोl(dev, WDCAPARA_ADD[i], 0x005e4332);

	rtl92e_ग_लिखोb(dev, 0xbe, 0xc0);

	rtl92e_config_mac(dev);

	अगर (priv->card_8192_version > (u8) VERSION_8190_BD) अणु
		rtl92e_get_tx_घातer(dev);
		rtl92e_set_tx_घातer(dev, priv->chan);
	पूर्ण

	पंचांगpvalue = rtl92e_पढ़ोb(dev, IC_VERRSION);
	priv->IC_Cut = पंचांगpvalue;
	RT_TRACE(COMP_INIT, "priv->IC_Cut= 0x%x\n", priv->IC_Cut);
	अगर (priv->IC_Cut >= IC_VersionCut_D) अणु
		अगर (priv->IC_Cut == IC_VersionCut_D) अणु
			/* no matter what checkpatch says, braces are needed */
			RT_TRACE(COMP_INIT, "D-cut\n");
		पूर्ण अन्यथा अगर (priv->IC_Cut == IC_VersionCut_E) अणु
			RT_TRACE(COMP_INIT, "E-cut\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		RT_TRACE(COMP_INIT, "Before C-cut\n");
	पूर्ण

	RT_TRACE(COMP_INIT, "Load Firmware!\n");
	bfirmwareok = rtl92e_init_fw(dev);
	अगर (!bfirmwareok) अणु
		अगर (retry_बार < 10) अणु
			retry_बार++;
			जाओ start;
		पूर्ण अन्यथा अणु
			rtStatus = false;
			जाओ end;
		पूर्ण
	पूर्ण
	RT_TRACE(COMP_INIT, "Load Firmware finished!\n");
	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
		RT_TRACE(COMP_INIT, "RF Config Started!\n");
		rtStatus = rtl92e_config_phy(dev);
		अगर (!rtStatus) अणु
			netdev_info(dev, "RF Config failed\n");
			वापस rtStatus;
		पूर्ण
		RT_TRACE(COMP_INIT, "RF Config Finished!\n");
	पूर्ण

	rtl92e_set_bb_reg(dev, rFPGA0_RFMOD, bCCKEn, 0x1);
	rtl92e_set_bb_reg(dev, rFPGA0_RFMOD, bOFDMEn, 0x1);

	rtl92e_ग_लिखोb(dev, 0x87, 0x0);

	अगर (priv->RegRfOff) अणु
		RT_TRACE((COMP_INIT | COMP_RF | COMP_POWER),
			  "%s(): Turn off RF for RegRfOff ----------\n",
			  __func__);
		rtl92e_set_rf_state(dev, eRfOff, RF_CHANGE_BY_SW);
	पूर्ण अन्यथा अगर (priv->rtllib->RfOffReason > RF_CHANGE_BY_PS) अणु
		RT_TRACE((COMP_INIT|COMP_RF|COMP_POWER),
			 "%s(): Turn off RF for RfOffReason(%d) ----------\n",
			 __func__, priv->rtllib->RfOffReason);
		rtl92e_set_rf_state(dev, eRfOff, priv->rtllib->RfOffReason);
	पूर्ण अन्यथा अगर (priv->rtllib->RfOffReason >= RF_CHANGE_BY_IPS) अणु
		RT_TRACE((COMP_INIT|COMP_RF|COMP_POWER),
			 "%s(): Turn off RF for RfOffReason(%d) ----------\n",
			 __func__, priv->rtllib->RfOffReason);
		rtl92e_set_rf_state(dev, eRfOff, priv->rtllib->RfOffReason);
	पूर्ण अन्यथा अणु
		RT_TRACE((COMP_INIT|COMP_RF|COMP_POWER), "%s(): RF-ON\n",
			  __func__);
		priv->rtllib->eRFPowerState = eRfOn;
		priv->rtllib->RfOffReason = 0;
	पूर्ण

	अगर (priv->rtllib->FwRWRF)
		priv->Rf_Mode = RF_OP_By_FW;
	अन्यथा
		priv->Rf_Mode = RF_OP_By_SW_3wire;

	अगर (priv->ResetProgress == RESET_TYPE_NORESET) अणु
		rtl92e_dm_init_txघातer_tracking(dev);

		अगर (priv->IC_Cut >= IC_VersionCut_D) अणु
			पंचांगpRegA = rtl92e_get_bb_reg(dev, rOFDM0_XATxIQImbalance,
						    bMaskDWord);
			rtl92e_get_bb_reg(dev, rOFDM0_XCTxIQImbalance, bMaskDWord);

			क्रम (i = 0; i < TxBBGainTableLength; i++) अणु
				अगर (पंचांगpRegA == dm_tx_bb_gain[i]) अणु
					priv->rfa_txघातertrackingindex = (u8)i;
					priv->rfa_txघातertrackingindex_real =
						 (u8)i;
					priv->rfa_txघातertracking_शेष =
						 priv->rfa_txघातertrackingindex;
					अवरोध;
				पूर्ण
			पूर्ण

			TempCCk = rtl92e_get_bb_reg(dev, rCCK0_TxFilter1,
						    bMaskByte2);

			क्रम (i = 0; i < CCKTxBBGainTableLength; i++) अणु
				अगर (TempCCk == dm_cck_tx_bb_gain[i][0]) अणु
					priv->CCKPresentAttentuation_20Mशेष = (u8)i;
					अवरोध;
				पूर्ण
			पूर्ण
			priv->CCKPresentAttentuation_40Mशेष = 0;
			priv->CCKPresentAttentuation_dअगरference = 0;
			priv->CCKPresentAttentuation =
				  priv->CCKPresentAttentuation_20Mशेष;
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->rfa_txpowertrackingindex_initial = %d\n",
				 priv->rfa_txघातertrackingindex);
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->rfa_txpowertrackingindex_real__initial = %d\n",
				 priv->rfa_txघातertrackingindex_real);
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->CCKPresentAttentuation_difference_initial = %d\n",
				  priv->CCKPresentAttentuation_dअगरference);
			RT_TRACE(COMP_POWER_TRACKING,
				 "priv->CCKPresentAttentuation_initial = %d\n",
				 priv->CCKPresentAttentuation);
			priv->btxघातer_tracking = false;
		पूर्ण
	पूर्ण
	rtl92e_irq_enable(dev);
end:
	priv->being_init_adapter = false;
	वापस rtStatus;
पूर्ण

अटल व्योम _rtl92e_net_update(काष्ठा net_device *dev)
अणु

	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_network *net;
	u16 BcnTimeCfg = 0, BcnCW = 6, BcnIFS = 0xf;
	u16 rate_config = 0;

	net = &priv->rtllib->current_network;
	rtl92e_config_rate(dev, &rate_config);
	priv->करोt11CurrentPreambleMode = PREAMBLE_AUTO;
	priv->basic_rate = rate_config &= 0x15f;
	rtl92e_ग_लिखोw(dev, BSSIDR, *(u16 *)net->bssid);
	rtl92e_ग_लिखोl(dev, BSSIDR + 2, *(u32 *)(net->bssid + 2));

	अगर (priv->rtllib->iw_mode == IW_MODE_ADHOC) अणु
		rtl92e_ग_लिखोw(dev, ATIMWND, 2);
		rtl92e_ग_लिखोw(dev, BCN_DMATIME, 256);
		rtl92e_ग_लिखोw(dev, BCN_INTERVAL, net->beacon_पूर्णांकerval);
		rtl92e_ग_लिखोw(dev, BCN_DRV_EARLY_INT, 10);
		rtl92e_ग_लिखोb(dev, BCN_ERR_THRESH, 100);

		BcnTimeCfg |= (BcnCW<<BCN_TCFG_CW_SHIFT);
		BcnTimeCfg |= BcnIFS<<BCN_TCFG_IFS;

		rtl92e_ग_लिखोw(dev, BCN_TCFG, BcnTimeCfg);
	पूर्ण
पूर्ण

व्योम rtl92e_link_change(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	अगर (!priv->up)
		वापस;

	अगर (ieee->state == RTLLIB_LINKED) अणु
		_rtl92e_net_update(dev);
		priv->ops->update_ratr_table(dev);
		अगर ((ieee->pairwise_key_type == KEY_TYPE_WEP40) ||
		    (ieee->pairwise_key_type == KEY_TYPE_WEP104))
			rtl92e_enable_hw_security_config(dev);
	पूर्ण अन्यथा अणु
		rtl92e_ग_लिखोb(dev, 0x173, 0);
	पूर्ण
	_rtl92e_update_msr(dev);

	अगर (ieee->iw_mode == IW_MODE_INFRA || ieee->iw_mode == IW_MODE_ADHOC) अणु
		u32 reg;

		reg = rtl92e_पढ़ोl(dev, RCR);
		अगर (priv->rtllib->state == RTLLIB_LINKED) अणु
			अगर (ieee->IntelPromiscuousModeInfo.bPromiscuousOn)
				;
			अन्यथा
				priv->ReceiveConfig = reg |= RCR_CBSSID;
		पूर्ण अन्यथा
			priv->ReceiveConfig = reg &= ~RCR_CBSSID;

		rtl92e_ग_लिखोl(dev, RCR, reg);
	पूर्ण
पूर्ण

व्योम rtl92e_set_monitor_mode(काष्ठा net_device *dev, bool bAllowAllDA,
			     bool WriteIntoReg)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	अगर (bAllowAllDA)
		priv->ReceiveConfig |= RCR_AAP;
	अन्यथा
		priv->ReceiveConfig &= ~RCR_AAP;

	अगर (WriteIntoReg)
		rtl92e_ग_लिखोl(dev, RCR, priv->ReceiveConfig);
पूर्ण

अटल u8 _rtl92e_rate_mgn_to_hw(u8 rate)
अणु
	u8  ret = DESC90_RATE1M;

	चयन (rate) अणु
	हाल MGN_1M:
		ret = DESC90_RATE1M;
		अवरोध;
	हाल MGN_2M:
		ret = DESC90_RATE2M;
		अवरोध;
	हाल MGN_5_5M:
		ret = DESC90_RATE5_5M;
		अवरोध;
	हाल MGN_11M:
		ret = DESC90_RATE11M;
		अवरोध;
	हाल MGN_6M:
		ret = DESC90_RATE6M;
		अवरोध;
	हाल MGN_9M:
		ret = DESC90_RATE9M;
		अवरोध;
	हाल MGN_12M:
		ret = DESC90_RATE12M;
		अवरोध;
	हाल MGN_18M:
		ret = DESC90_RATE18M;
		अवरोध;
	हाल MGN_24M:
		ret = DESC90_RATE24M;
		अवरोध;
	हाल MGN_36M:
		ret = DESC90_RATE36M;
		अवरोध;
	हाल MGN_48M:
		ret = DESC90_RATE48M;
		अवरोध;
	हाल MGN_54M:
		ret = DESC90_RATE54M;
		अवरोध;
	हाल MGN_MCS0:
		ret = DESC90_RATEMCS0;
		अवरोध;
	हाल MGN_MCS1:
		ret = DESC90_RATEMCS1;
		अवरोध;
	हाल MGN_MCS2:
		ret = DESC90_RATEMCS2;
		अवरोध;
	हाल MGN_MCS3:
		ret = DESC90_RATEMCS3;
		अवरोध;
	हाल MGN_MCS4:
		ret = DESC90_RATEMCS4;
		अवरोध;
	हाल MGN_MCS5:
		ret = DESC90_RATEMCS5;
		अवरोध;
	हाल MGN_MCS6:
		ret = DESC90_RATEMCS6;
		अवरोध;
	हाल MGN_MCS7:
		ret = DESC90_RATEMCS7;
		अवरोध;
	हाल MGN_MCS8:
		ret = DESC90_RATEMCS8;
		अवरोध;
	हाल MGN_MCS9:
		ret = DESC90_RATEMCS9;
		अवरोध;
	हाल MGN_MCS10:
		ret = DESC90_RATEMCS10;
		अवरोध;
	हाल MGN_MCS11:
		ret = DESC90_RATEMCS11;
		अवरोध;
	हाल MGN_MCS12:
		ret = DESC90_RATEMCS12;
		अवरोध;
	हाल MGN_MCS13:
		ret = DESC90_RATEMCS13;
		अवरोध;
	हाल MGN_MCS14:
		ret = DESC90_RATEMCS14;
		अवरोध;
	हाल MGN_MCS15:
		ret = DESC90_RATEMCS15;
		अवरोध;
	हाल (0x80|0x20):
		ret = DESC90_RATEMCS32;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल u8 _rtl92e_hw_queue_to_fw_queue(काष्ठा net_device *dev, u8 QueueID,
				       u8 priority)
अणु
	u8 QueueSelect = 0x0;

	चयन (QueueID) अणु
	हाल BE_QUEUE:
		QueueSelect = QSLT_BE;
		अवरोध;

	हाल BK_QUEUE:
		QueueSelect = QSLT_BK;
		अवरोध;

	हाल VO_QUEUE:
		QueueSelect = QSLT_VO;
		अवरोध;

	हाल VI_QUEUE:
		QueueSelect = QSLT_VI;
		अवरोध;
	हाल MGNT_QUEUE:
		QueueSelect = QSLT_MGNT;
		अवरोध;
	हाल BEACON_QUEUE:
		QueueSelect = QSLT_BEACON;
		अवरोध;
	हाल TXCMD_QUEUE:
		QueueSelect = QSLT_CMD;
		अवरोध;
	हाल HIGH_QUEUE:
		QueueSelect = QSLT_HIGH;
		अवरोध;
	शेष:
		netdev_warn(dev, "%s(): Impossible Queue Selection: %d\n",
			    __func__, QueueID);
		अवरोध;
	पूर्ण
	वापस QueueSelect;
पूर्ण

अटल u8 _rtl92e_query_is_लघु(u8 TxHT, u8 TxRate, काष्ठा cb_desc *tcb_desc)
अणु
	u8   पंचांगp_Short;

	पंचांगp_Short = (TxHT == 1) ? ((tcb_desc->bUseShortGI) ? 1 : 0) :
			((tcb_desc->bUseShortPreamble) ? 1 : 0);
	अगर (TxHT == 1 && TxRate != DESC90_RATEMCS15)
		पंचांगp_Short = 0;

	वापस पंचांगp_Short;
पूर्ण

व्योम  rtl92e_fill_tx_desc(काष्ठा net_device *dev, काष्ठा tx_desc *pdesc,
			  काष्ठा cb_desc *cb_desc, काष्ठा sk_buff *skb)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	dma_addr_t mapping;
	काष्ठा tx_fwinfo_8190pci *pTxFwInfo;

	pTxFwInfo = (काष्ठा tx_fwinfo_8190pci *)skb->data;
	स_रखो(pTxFwInfo, 0, माप(काष्ठा tx_fwinfo_8190pci));
	pTxFwInfo->TxHT = (cb_desc->data_rate & 0x80) ? 1 : 0;
	pTxFwInfo->TxRate = _rtl92e_rate_mgn_to_hw((u8)cb_desc->data_rate);
	pTxFwInfo->EnableCPUDur = cb_desc->bTxEnableFwCalcDur;
	pTxFwInfo->Short = _rtl92e_query_is_लघु(pTxFwInfo->TxHT,
						  pTxFwInfo->TxRate, cb_desc);

	अगर (cb_desc->bAMPDUEnable) अणु
		pTxFwInfo->AllowAggregation = 1;
		pTxFwInfo->RxMF = cb_desc->ampdu_factor;
		pTxFwInfo->RxAMD = cb_desc->ampdu_density;
	पूर्ण अन्यथा अणु
		pTxFwInfo->AllowAggregation = 0;
		pTxFwInfo->RxMF = 0;
		pTxFwInfo->RxAMD = 0;
	पूर्ण

	pTxFwInfo->RtsEnable =	(cb_desc->bRTSEnable) ? 1 : 0;
	pTxFwInfo->CtsEnable = (cb_desc->bCTSEnable) ? 1 : 0;
	pTxFwInfo->RtsSTBC = (cb_desc->bRTSSTBC) ? 1 : 0;
	pTxFwInfo->RtsHT = (cb_desc->rts_rate&0x80) ? 1 : 0;
	pTxFwInfo->RtsRate = _rtl92e_rate_mgn_to_hw((u8)cb_desc->rts_rate);
	pTxFwInfo->RtsBandwidth = 0;
	pTxFwInfo->RtsSubcarrier = cb_desc->RTSSC;
	pTxFwInfo->RtsShort = (pTxFwInfo->RtsHT == 0) ?
			  (cb_desc->bRTSUseShortPreamble ? 1 : 0) :
			  (cb_desc->bRTSUseShortGI ? 1 : 0);
	अगर (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20_40) अणु
		अगर (cb_desc->bPacketBW) अणु
			pTxFwInfo->TxBandwidth = 1;
			pTxFwInfo->TxSubCarrier = 0;
		पूर्ण अन्यथा अणु
			pTxFwInfo->TxBandwidth = 0;
			pTxFwInfo->TxSubCarrier = priv->nCur40MhzPrimeSC;
		पूर्ण
	पूर्ण अन्यथा अणु
		pTxFwInfo->TxBandwidth = 0;
		pTxFwInfo->TxSubCarrier = 0;
	पूर्ण

	स_रखो((u8 *)pdesc, 0, 12);

	mapping = dma_map_single(&priv->pdev->dev, skb->data, skb->len,
				 DMA_TO_DEVICE);
	अगर (dma_mapping_error(&priv->pdev->dev, mapping)) अणु
		netdev_err(dev, "%s(): DMA Mapping error\n", __func__);
		वापस;
	पूर्ण

	pdesc->LINIP = 0;
	pdesc->CmdInit = 1;
	pdesc->Offset = माप(काष्ठा tx_fwinfo_8190pci) + 8;
	pdesc->PktSize = (u16)skb->len-माप(काष्ठा tx_fwinfo_8190pci);

	pdesc->SecCAMID = 0;
	pdesc->RATid = cb_desc->RATRIndex;


	pdesc->NoEnc = 1;
	pdesc->SecType = 0x0;
	अगर (cb_desc->bHwSec) अणु
		अटल u8 पंचांगp;

		अगर (!पंचांगp) अणु
			RT_TRACE(COMP_DBG, "==>================hw sec\n");
			पंचांगp = 1;
		पूर्ण
		चयन (priv->rtllib->pairwise_key_type) अणु
		हाल KEY_TYPE_WEP40:
		हाल KEY_TYPE_WEP104:
			pdesc->SecType = 0x1;
			pdesc->NoEnc = 0;
			अवरोध;
		हाल KEY_TYPE_TKIP:
			pdesc->SecType = 0x2;
			pdesc->NoEnc = 0;
			अवरोध;
		हाल KEY_TYPE_CCMP:
			pdesc->SecType = 0x3;
			pdesc->NoEnc = 0;
			अवरोध;
		हाल KEY_TYPE_NA:
			pdesc->SecType = 0x0;
			pdesc->NoEnc = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	pdesc->PktId = 0x0;

	pdesc->QueueSelect = _rtl92e_hw_queue_to_fw_queue(dev,
							  cb_desc->queue_index,
							  cb_desc->priority);
	pdesc->TxFWInfoSize = माप(काष्ठा tx_fwinfo_8190pci);

	pdesc->DISFB = cb_desc->bTxDisableRateFallBack;
	pdesc->USERATE = cb_desc->bTxUseDriverAssingedRate;

	pdesc->FirstSeg = 1;
	pdesc->LastSeg = 1;
	pdesc->TxBufferSize = skb->len;

	pdesc->TxBuffAddr = mapping;
पूर्ण

व्योम  rtl92e_fill_tx_cmd_desc(काष्ठा net_device *dev, काष्ठा tx_desc_cmd *entry,
			      काष्ठा cb_desc *cb_desc, काष्ठा sk_buff *skb)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	dma_addr_t mapping = dma_map_single(&priv->pdev->dev, skb->data,
					    skb->len, DMA_TO_DEVICE);

	अगर (dma_mapping_error(&priv->pdev->dev, mapping))
		netdev_err(dev, "%s(): DMA Mapping error\n", __func__);
	स_रखो(entry, 0, 12);
	entry->LINIP = cb_desc->bLastIniPkt;
	entry->FirstSeg = 1;
	entry->LastSeg = 1;
	अगर (cb_desc->bCmdOrInit == DESC_PACKET_TYPE_INIT) अणु
		entry->CmdInit = DESC_PACKET_TYPE_INIT;
	पूर्ण अन्यथा अणु
		काष्ठा tx_desc *entry_पंचांगp = (काष्ठा tx_desc *)entry;

		entry_पंचांगp->CmdInit = DESC_PACKET_TYPE_NORMAL;
		entry_पंचांगp->Offset = माप(काष्ठा tx_fwinfo_8190pci) + 8;
		entry_पंचांगp->PktSize = (u16)(cb_desc->pkt_size +
				      entry_पंचांगp->Offset);
		entry_पंचांगp->QueueSelect = QSLT_CMD;
		entry_पंचांगp->TxFWInfoSize = 0x08;
		entry_पंचांगp->RATid = (u8)DESC_PACKET_TYPE_INIT;
	पूर्ण
	entry->TxBufferSize = skb->len;
	entry->TxBuffAddr = mapping;
	entry->OWN = 1;
पूर्ण

अटल u8 _rtl92e_rate_hw_to_mgn(bool bIsHT, u8 rate)
अणु
	u8  ret_rate = 0x02;

	अगर (!bIsHT) अणु
		चयन (rate) अणु
		हाल DESC90_RATE1M:
			ret_rate = MGN_1M;
			अवरोध;
		हाल DESC90_RATE2M:
			ret_rate = MGN_2M;
			अवरोध;
		हाल DESC90_RATE5_5M:
			ret_rate = MGN_5_5M;
			अवरोध;
		हाल DESC90_RATE11M:
			ret_rate = MGN_11M;
			अवरोध;
		हाल DESC90_RATE6M:
			ret_rate = MGN_6M;
			अवरोध;
		हाल DESC90_RATE9M:
			ret_rate = MGN_9M;
			अवरोध;
		हाल DESC90_RATE12M:
			ret_rate = MGN_12M;
			अवरोध;
		हाल DESC90_RATE18M:
			ret_rate = MGN_18M;
			अवरोध;
		हाल DESC90_RATE24M:
			ret_rate = MGN_24M;
			अवरोध;
		हाल DESC90_RATE36M:
			ret_rate = MGN_36M;
			अवरोध;
		हाल DESC90_RATE48M:
			ret_rate = MGN_48M;
			अवरोध;
		हाल DESC90_RATE54M:
			ret_rate = MGN_54M;
			अवरोध;

		शेष:
			RT_TRACE(COMP_RECV,
				 "%s: Non supportedRate [%x], bIsHT = %d!!!\n",
				 __func__, rate, bIsHT);
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		चयन (rate) अणु
		हाल DESC90_RATEMCS0:
			ret_rate = MGN_MCS0;
			अवरोध;
		हाल DESC90_RATEMCS1:
			ret_rate = MGN_MCS1;
			अवरोध;
		हाल DESC90_RATEMCS2:
			ret_rate = MGN_MCS2;
			अवरोध;
		हाल DESC90_RATEMCS3:
			ret_rate = MGN_MCS3;
			अवरोध;
		हाल DESC90_RATEMCS4:
			ret_rate = MGN_MCS4;
			अवरोध;
		हाल DESC90_RATEMCS5:
			ret_rate = MGN_MCS5;
			अवरोध;
		हाल DESC90_RATEMCS6:
			ret_rate = MGN_MCS6;
			अवरोध;
		हाल DESC90_RATEMCS7:
			ret_rate = MGN_MCS7;
			अवरोध;
		हाल DESC90_RATEMCS8:
			ret_rate = MGN_MCS8;
			अवरोध;
		हाल DESC90_RATEMCS9:
			ret_rate = MGN_MCS9;
			अवरोध;
		हाल DESC90_RATEMCS10:
			ret_rate = MGN_MCS10;
			अवरोध;
		हाल DESC90_RATEMCS11:
			ret_rate = MGN_MCS11;
			अवरोध;
		हाल DESC90_RATEMCS12:
			ret_rate = MGN_MCS12;
			अवरोध;
		हाल DESC90_RATEMCS13:
			ret_rate = MGN_MCS13;
			अवरोध;
		हाल DESC90_RATEMCS14:
			ret_rate = MGN_MCS14;
			अवरोध;
		हाल DESC90_RATEMCS15:
			ret_rate = MGN_MCS15;
			अवरोध;
		हाल DESC90_RATEMCS32:
			ret_rate = 0x80 | 0x20;
			अवरोध;

		शेष:
			RT_TRACE(COMP_RECV,
				 "%s: Non supported Rate [%x], bIsHT = %d!!!\n",
				 __func__, rate, bIsHT);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret_rate;
पूर्ण

अटल दीर्घ _rtl92e_संकेत_scale_mapping(काष्ठा r8192_priv *priv, दीर्घ currsig)
अणु
	दीर्घ retsig;

	अगर (currsig >= 61 && currsig <= 100)
		retsig = 90 + ((currsig - 60) / 4);
	अन्यथा अगर (currsig >= 41 && currsig <= 60)
		retsig = 78 + ((currsig - 40) / 2);
	अन्यथा अगर (currsig >= 31 && currsig <= 40)
		retsig = 66 + (currsig - 30);
	अन्यथा अगर (currsig >= 21 && currsig <= 30)
		retsig = 54 + (currsig - 20);
	अन्यथा अगर (currsig >= 5 && currsig <= 20)
		retsig = 42 + (((currsig - 5) * 2) / 3);
	अन्यथा अगर (currsig == 4)
		retsig = 36;
	अन्यथा अगर (currsig == 3)
		retsig = 27;
	अन्यथा अगर (currsig == 2)
		retsig = 18;
	अन्यथा अगर (currsig == 1)
		retsig = 9;
	अन्यथा
		retsig = currsig;

	वापस retsig;
पूर्ण


#घोषणा	 rx_hal_is_cck_rate(_pdrvinfo)\
			((_pdrvinfo->RxRate == DESC90_RATE1M ||\
			_pdrvinfo->RxRate == DESC90_RATE2M ||\
			_pdrvinfo->RxRate == DESC90_RATE5_5M ||\
			_pdrvinfo->RxRate == DESC90_RATE11M) &&\
			!_pdrvinfo->RxHT)

अटल व्योम _rtl92e_query_rxphystatus(
	काष्ठा r8192_priv *priv,
	काष्ठा rtllib_rx_stats *pstats,
	काष्ठा rx_desc  *pdesc,
	काष्ठा rx_fwinfo   *pdrvinfo,
	काष्ठा rtllib_rx_stats *precord_stats,
	bool bpacket_match_bssid,
	bool bpacket_toself,
	bool bPacketBeacon,
	bool bToSelfBA
	)
अणु
	काष्ठा phy_sts_ofdm_819xpci *pofdm_buf;
	काष्ठा phy_sts_cck_819xpci *pcck_buf;
	काष्ठा phy_ofdm_rx_status_rxsc_sgien_exपूर्णांकfflag *prxsc;
	u8 *prxpkt;
	u8 i, max_spatial_stream, पंचांगp_rxsnr, पंचांगp_rxevm, rxsc_sgien_exflg;
	s8 rx_pwr[4], rx_pwr_all = 0;
	s8 rx_snrX, rx_evmX;
	u8 evm, pwdb_all;
	u32 RSSI, total_rssi = 0;
	u8 is_cck_rate = 0;
	u8 rf_rx_num = 0;
	अटल	u8 check_reg824;
	अटल	u32 reg824_bit9;

	priv->stats.numqry_phystatus++;

	is_cck_rate = rx_hal_is_cck_rate(pdrvinfo);
	स_रखो(precord_stats, 0, माप(काष्ठा rtllib_rx_stats));
	pstats->bPacketMatchBSSID = precord_stats->bPacketMatchBSSID =
				    bpacket_match_bssid;
	pstats->bPacketToSelf = precord_stats->bPacketToSelf = bpacket_toself;
	pstats->bIsCCK = precord_stats->bIsCCK = is_cck_rate;
	pstats->bPacketBeacon = precord_stats->bPacketBeacon = bPacketBeacon;
	pstats->bToSelfBA = precord_stats->bToSelfBA = bToSelfBA;
	अगर (check_reg824 == 0) अणु
		reg824_bit9 = rtl92e_get_bb_reg(priv->rtllib->dev,
						rFPGA0_XA_HSSIParameter2,
						0x200);
		check_reg824 = 1;
	पूर्ण


	prxpkt = (u8 *)pdrvinfo;

	prxpkt += माप(काष्ठा rx_fwinfo);

	pcck_buf = (काष्ठा phy_sts_cck_819xpci *)prxpkt;
	pofdm_buf = (काष्ठा phy_sts_ofdm_819xpci *)prxpkt;

	pstats->RxMIMOSignalQuality[0] = -1;
	pstats->RxMIMOSignalQuality[1] = -1;
	precord_stats->RxMIMOSignalQuality[0] = -1;
	precord_stats->RxMIMOSignalQuality[1] = -1;

	अगर (is_cck_rate) अणु
		u8 report;

		priv->stats.numqry_phystatusCCK++;
		अगर (!reg824_bit9) अणु
			report = pcck_buf->cck_agc_rpt & 0xc0;
			report >>= 6;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -35 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -23 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -11 - (pcck_buf->cck_agc_rpt &
					     0x3e);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = 8 - (pcck_buf->cck_agc_rpt & 0x3e);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			report = pcck_buf->cck_agc_rpt & 0x60;
			report >>= 5;
			चयन (report) अणु
			हाल 0x3:
				rx_pwr_all = -35 -
					((pcck_buf->cck_agc_rpt &
					0x1f) << 1);
				अवरोध;
			हाल 0x2:
				rx_pwr_all = -23 -
					((pcck_buf->cck_agc_rpt &
					 0x1f) << 1);
				अवरोध;
			हाल 0x1:
				rx_pwr_all = -11 -
					 ((pcck_buf->cck_agc_rpt &
					 0x1f) << 1);
				अवरोध;
			हाल 0x0:
				rx_pwr_all = -8 -
					 ((pcck_buf->cck_agc_rpt &
					 0x1f) << 1);
				अवरोध;
			पूर्ण
		पूर्ण

		pwdb_all = rtl92e_rx_db_to_percent(rx_pwr_all);
		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		pstats->RecvSignalPower = rx_pwr_all;

		अगर (bpacket_match_bssid) अणु
			u8	sq;

			अगर (pstats->RxPWDBAll > 40) अणु
				sq = 100;
			पूर्ण अन्यथा अणु
				sq = pcck_buf->sq_rpt;

				अगर (pcck_buf->sq_rpt > 64)
					sq = 0;
				अन्यथा अगर (pcck_buf->sq_rpt < 20)
					sq = 100;
				अन्यथा
					sq = ((64-sq) * 100) / 44;
			पूर्ण
			pstats->SignalQuality = sq;
			precord_stats->SignalQuality = sq;
			pstats->RxMIMOSignalQuality[0] = sq;
			precord_stats->RxMIMOSignalQuality[0] = sq;
			pstats->RxMIMOSignalQuality[1] = -1;
			precord_stats->RxMIMOSignalQuality[1] = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		priv->stats.numqry_phystatusHT++;
		क्रम (i = RF90_PATH_A; i < RF90_PATH_MAX; i++) अणु
			अगर (priv->brfpath_rxenable[i])
				rf_rx_num++;

			rx_pwr[i] = ((pofdm_buf->trsw_gain_X[i] & 0x3F) *
				     2) - 110;

			पंचांगp_rxsnr = pofdm_buf->rxsnr_X[i];
			rx_snrX = (s8)(पंचांगp_rxsnr);
			rx_snrX /= 2;
			priv->stats.rxSNRdB[i] = (दीर्घ)rx_snrX;

			RSSI = rtl92e_rx_db_to_percent(rx_pwr[i]);
			अगर (priv->brfpath_rxenable[i])
				total_rssi += RSSI;

			अगर (bpacket_match_bssid) अणु
				pstats->RxMIMOSignalStrength[i] = (u8) RSSI;
				precord_stats->RxMIMOSignalStrength[i] =
								(u8) RSSI;
			पूर्ण
		पूर्ण


		rx_pwr_all = (((pofdm_buf->pwdb_all) >> 1) & 0x7f) - 106;
		pwdb_all = rtl92e_rx_db_to_percent(rx_pwr_all);

		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		pstats->RxPower = precord_stats->RxPower =	rx_pwr_all;
		pstats->RecvSignalPower = rx_pwr_all;
		अगर (pdrvinfo->RxHT && pdrvinfo->RxRate >= DESC90_RATEMCS8 &&
		    pdrvinfo->RxRate <= DESC90_RATEMCS15)
			max_spatial_stream = 2;
		अन्यथा
			max_spatial_stream = 1;

		क्रम (i = 0; i < max_spatial_stream; i++) अणु
			पंचांगp_rxevm = pofdm_buf->rxevm_X[i];
			rx_evmX = (s8)(पंचांगp_rxevm);

			rx_evmX /= 2;

			evm = rtl92e_evm_db_to_percent(rx_evmX);
			अगर (bpacket_match_bssid) अणु
				अगर (i == 0) अणु
					pstats->SignalQuality = evm & 0xff;
					precord_stats->SignalQuality = evm & 0xff;
				पूर्ण
				pstats->RxMIMOSignalQuality[i] = evm & 0xff;
				precord_stats->RxMIMOSignalQuality[i] = evm & 0xff;
			पूर्ण
		पूर्ण


		rxsc_sgien_exflg = pofdm_buf->rxsc_sgien_exflg;
		prxsc = (काष्ठा phy_ofdm_rx_status_rxsc_sgien_exपूर्णांकfflag *)
			&rxsc_sgien_exflg;
		अगर (pdrvinfo->BW)
			priv->stats.received_bwtype[1+prxsc->rxsc]++;
		अन्यथा
			priv->stats.received_bwtype[0]++;
	पूर्ण

	अगर (is_cck_rate) अणु
		pstats->SignalStrength = precord_stats->SignalStrength =
					 (u8)(_rtl92e_संकेत_scale_mapping(priv,
					 (दीर्घ)pwdb_all));

	पूर्ण अन्यथा अणु
		अगर (rf_rx_num != 0)
			pstats->SignalStrength = precord_stats->SignalStrength =
					 (u8)(_rtl92e_संकेत_scale_mapping(priv,
					 (दीर्घ)(total_rssi /= rf_rx_num)));
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_process_phyinfo(काष्ठा r8192_priv *priv, u8 *buffer,
				    काष्ठा rtllib_rx_stats *prev_st,
				    काष्ठा rtllib_rx_stats *curr_st)
अणु
	bool bcheck = false;
	u8	rfpath;
	u32 ij, पंचांगp_val;
	अटल u32 slide_rssi_index, slide_rssi_statistics;
	अटल u32 slide_evm_index, slide_evm_statistics;
	अटल u32 last_rssi, last_evm;
	अटल u32 slide_beacon_adc_pwdb_index;
	अटल u32 slide_beacon_adc_pwdb_statistics;
	अटल u32 last_beacon_adc_pwdb;
	काष्ठा rtllib_hdr_3addr *hdr;
	u16 sc;
	अचिन्हित पूर्णांक seq;

	hdr = (काष्ठा rtllib_hdr_3addr *)buffer;
	sc = le16_to_cpu(hdr->seq_ctl);
	seq = WLAN_GET_SEQ_SEQ(sc);
	curr_st->Seq_Num = seq;
	अगर (!prev_st->bIsAMPDU)
		bcheck = true;

	अगर (slide_rssi_statistics++ >= PHY_RSSI_SLID_WIN_MAX) अणु
		slide_rssi_statistics = PHY_RSSI_SLID_WIN_MAX;
		last_rssi = priv->stats.slide_संकेत_strength[slide_rssi_index];
		priv->stats.slide_rssi_total -= last_rssi;
	पूर्ण
	priv->stats.slide_rssi_total += prev_st->SignalStrength;

	priv->stats.slide_संकेत_strength[slide_rssi_index++] =
					 prev_st->SignalStrength;
	अगर (slide_rssi_index >= PHY_RSSI_SLID_WIN_MAX)
		slide_rssi_index = 0;

	पंचांगp_val = priv->stats.slide_rssi_total/slide_rssi_statistics;
	priv->stats.संकेत_strength = rtl92e_translate_to_dbm(priv,
							      (u8)पंचांगp_val);
	curr_st->rssi = priv->stats.संकेत_strength;
	अगर (!prev_st->bPacketMatchBSSID) अणु
		अगर (!prev_st->bToSelfBA)
			वापस;
	पूर्ण

	अगर (!bcheck)
		वापस;

	priv->stats.num_process_phyinfo++;
	अगर (!prev_st->bIsCCK && prev_st->bPacketToSelf) अणु
		क्रम (rfpath = RF90_PATH_A; rfpath < RF90_PATH_C; rfpath++) अणु
			अगर (!rtl92e_is_legal_rf_path(priv->rtllib->dev, rfpath))
				जारी;
			RT_TRACE(COMP_DBG,
				 "Jacken -> pPreviousstats->RxMIMOSignalStrength[rfpath]  = %d\n",
				 prev_st->RxMIMOSignalStrength[rfpath]);
			अगर (priv->stats.rx_rssi_percentage[rfpath] == 0) अणु
				priv->stats.rx_rssi_percentage[rfpath] =
					 prev_st->RxMIMOSignalStrength[rfpath];
			पूर्ण
			अगर (prev_st->RxMIMOSignalStrength[rfpath]  >
			    priv->stats.rx_rssi_percentage[rfpath]) अणु
				priv->stats.rx_rssi_percentage[rfpath] =
					((priv->stats.rx_rssi_percentage[rfpath]
					* (RX_SMOOTH - 1)) +
					(prev_st->RxMIMOSignalStrength
					[rfpath])) / (RX_SMOOTH);
				priv->stats.rx_rssi_percentage[rfpath] =
					 priv->stats.rx_rssi_percentage[rfpath]
					 + 1;
			पूर्ण अन्यथा अणु
				priv->stats.rx_rssi_percentage[rfpath] =
				   ((priv->stats.rx_rssi_percentage[rfpath] *
				   (RX_SMOOTH-1)) +
				   (prev_st->RxMIMOSignalStrength[rfpath])) /
				   (RX_SMOOTH);
			पूर्ण
			RT_TRACE(COMP_DBG,
				 "Jacken -> priv->RxStats.RxRSSIPercentage[rfPath]  = %d\n",
				 priv->stats.rx_rssi_percentage[rfpath]);
		पूर्ण
	पूर्ण


	अगर (prev_st->bPacketBeacon) अणु
		अगर (slide_beacon_adc_pwdb_statistics++ >=
		    PHY_Beacon_RSSI_SLID_WIN_MAX) अणु
			slide_beacon_adc_pwdb_statistics =
					 PHY_Beacon_RSSI_SLID_WIN_MAX;
			last_beacon_adc_pwdb = priv->stats.Slide_Beacon_pwdb
					       [slide_beacon_adc_pwdb_index];
			priv->stats.Slide_Beacon_Total -= last_beacon_adc_pwdb;
		पूर्ण
		priv->stats.Slide_Beacon_Total += prev_st->RxPWDBAll;
		priv->stats.Slide_Beacon_pwdb[slide_beacon_adc_pwdb_index] =
							 prev_st->RxPWDBAll;
		slide_beacon_adc_pwdb_index++;
		अगर (slide_beacon_adc_pwdb_index >= PHY_Beacon_RSSI_SLID_WIN_MAX)
			slide_beacon_adc_pwdb_index = 0;
		prev_st->RxPWDBAll = priv->stats.Slide_Beacon_Total /
				     slide_beacon_adc_pwdb_statistics;
		अगर (prev_st->RxPWDBAll >= 3)
			prev_st->RxPWDBAll -= 3;
	पूर्ण

	RT_TRACE(COMP_RXDESC, "Smooth %s PWDB = %d\n",
				prev_st->bIsCCK ? "CCK" : "OFDM",
				prev_st->RxPWDBAll);

	अगर (prev_st->bPacketToSelf || prev_st->bPacketBeacon ||
	    prev_st->bToSelfBA) अणु
		अगर (priv->undecorated_smoothed_pwdb < 0)
			priv->undecorated_smoothed_pwdb = prev_st->RxPWDBAll;
		अगर (prev_st->RxPWDBAll > (u32)priv->undecorated_smoothed_pwdb) अणु
			priv->undecorated_smoothed_pwdb =
					(((priv->undecorated_smoothed_pwdb) *
					(RX_SMOOTH-1)) +
					(prev_st->RxPWDBAll)) / (RX_SMOOTH);
			priv->undecorated_smoothed_pwdb =
					 priv->undecorated_smoothed_pwdb + 1;
		पूर्ण अन्यथा अणु
			priv->undecorated_smoothed_pwdb =
					(((priv->undecorated_smoothed_pwdb) *
					(RX_SMOOTH-1)) +
					(prev_st->RxPWDBAll)) / (RX_SMOOTH);
		पूर्ण
		rtl92e_update_rx_statistics(priv, prev_st);
	पूर्ण

	अगर (prev_st->SignalQuality != 0) अणु
		अगर (prev_st->bPacketToSelf || prev_st->bPacketBeacon ||
		    prev_st->bToSelfBA) अणु
			अगर (slide_evm_statistics++ >= PHY_RSSI_SLID_WIN_MAX) अणु
				slide_evm_statistics = PHY_RSSI_SLID_WIN_MAX;
				last_evm =
					 priv->stats.slide_evm[slide_evm_index];
				priv->stats.slide_evm_total -= last_evm;
			पूर्ण

			priv->stats.slide_evm_total += prev_st->SignalQuality;

			priv->stats.slide_evm[slide_evm_index++] =
						 prev_st->SignalQuality;
			अगर (slide_evm_index >= PHY_RSSI_SLID_WIN_MAX)
				slide_evm_index = 0;

			पंचांगp_val = priv->stats.slide_evm_total /
				  slide_evm_statistics;
			priv->stats.संकेत_quality = पंचांगp_val;
			priv->stats.last_संकेत_strength_inpercent = पंचांगp_val;
		पूर्ण

		अगर (prev_st->bPacketToSelf ||
		    prev_st->bPacketBeacon ||
		    prev_st->bToSelfBA) अणु
			क्रम (ij = 0; ij < 2; ij++) अणु
				अगर (prev_st->RxMIMOSignalQuality[ij] != -1) अणु
					अगर (priv->stats.rx_evm_percentage[ij] == 0)
						priv->stats.rx_evm_percentage[ij] =
						   prev_st->RxMIMOSignalQuality[ij];
					priv->stats.rx_evm_percentage[ij] =
					  ((priv->stats.rx_evm_percentage[ij] *
					  (RX_SMOOTH - 1)) +
					  (prev_st->RxMIMOSignalQuality[ij])) /
					  (RX_SMOOTH);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92e_translate_rx_संकेत_stats(काष्ठा net_device *dev,
					      काष्ठा sk_buff *skb,
					      काष्ठा rtllib_rx_stats *pstats,
					      काष्ठा rx_desc *pdesc,
					      काष्ठा rx_fwinfo *pdrvinfo)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	bool bpacket_match_bssid, bpacket_toself;
	bool bPacketBeacon = false;
	काष्ठा rtllib_hdr_3addr *hdr;
	bool bToSelfBA = false;
	अटल काष्ठा rtllib_rx_stats  previous_stats;
	u16 fc, type;
	u8 *पंचांगp_buf;
	u8 *praddr;

	पंचांगp_buf = skb->data + pstats->RxDrvInfoSize + pstats->RxBufShअगरt;

	hdr = (काष्ठा rtllib_hdr_3addr *)पंचांगp_buf;
	fc = le16_to_cpu(hdr->frame_ctl);
	type = WLAN_FC_GET_TYPE(fc);
	praddr = hdr->addr1;

	bpacket_match_bssid =
		((type != RTLLIB_FTYPE_CTL) &&
		 ether_addr_equal(priv->rtllib->current_network.bssid,
				  (fc & RTLLIB_FCTL_TODS) ? hdr->addr1 :
				  (fc & RTLLIB_FCTL_FROMDS) ? hdr->addr2 :
				  hdr->addr3) &&
		 (!pstats->bHwError) && (!pstats->bCRC) && (!pstats->bICV));
	bpacket_toself = bpacket_match_bssid &&		/* check this */
			 ether_addr_equal(praddr, priv->rtllib->dev->dev_addr);
	अगर (WLAN_FC_GET_FRAMETYPE(fc) == RTLLIB_STYPE_BEACON)
		bPacketBeacon = true;
	अगर (bpacket_match_bssid)
		priv->stats.numpacket_matchbssid++;
	अगर (bpacket_toself)
		priv->stats.numpacket_toself++;
	_rtl92e_process_phyinfo(priv, पंचांगp_buf, &previous_stats, pstats);
	_rtl92e_query_rxphystatus(priv, pstats, pdesc, pdrvinfo,
				  &previous_stats, bpacket_match_bssid,
				  bpacket_toself, bPacketBeacon, bToSelfBA);
	rtl92e_copy_mpdu_stats(pstats, &previous_stats);
पूर्ण

अटल व्योम _rtl92e_update_received_rate_histogram_stats(
					   काष्ठा net_device *dev,
					   काष्ठा rtllib_rx_stats *pstats)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	u32 rcvType = 1;
	u32 rateIndex;
	u32 preamble_guardपूर्णांकerval;

	अगर (pstats->bCRC)
		rcvType = 2;
	अन्यथा अगर (pstats->bICV)
		rcvType = 3;

	अगर (pstats->bShortPreamble)
		preamble_guardपूर्णांकerval = 1;
	अन्यथा
		preamble_guardपूर्णांकerval = 0;

	चयन (pstats->rate) अणु
	हाल MGN_1M:
		rateIndex = 0;
		अवरोध;
	हाल MGN_2M:
		rateIndex = 1;
		अवरोध;
	हाल MGN_5_5M:
		rateIndex = 2;
		अवरोध;
	हाल MGN_11M:
		rateIndex = 3;
		अवरोध;
	हाल MGN_6M:
		rateIndex = 4;
		अवरोध;
	हाल MGN_9M:
		rateIndex = 5;
		अवरोध;
	हाल MGN_12M:
		rateIndex = 6;
		अवरोध;
	हाल MGN_18M:
		rateIndex = 7;
		अवरोध;
	हाल MGN_24M:
		rateIndex = 8;
		अवरोध;
	हाल MGN_36M:
		rateIndex = 9;
		अवरोध;
	हाल MGN_48M:
		rateIndex = 10;
		अवरोध;
	हाल MGN_54M:
		rateIndex = 11;
		अवरोध;
	हाल MGN_MCS0:
		rateIndex = 12;
		अवरोध;
	हाल MGN_MCS1:
		rateIndex = 13;
		अवरोध;
	हाल MGN_MCS2:
		rateIndex = 14;
		अवरोध;
	हाल MGN_MCS3:
		rateIndex = 15;
		अवरोध;
	हाल MGN_MCS4:
		rateIndex = 16;
		अवरोध;
	हाल MGN_MCS5:
		rateIndex = 17;
		अवरोध;
	हाल MGN_MCS6:
		rateIndex = 18;
		अवरोध;
	हाल MGN_MCS7:
		rateIndex = 19;
		अवरोध;
	हाल MGN_MCS8:
		rateIndex = 20;
		अवरोध;
	हाल MGN_MCS9:
		rateIndex = 21;
		अवरोध;
	हाल MGN_MCS10:
		rateIndex = 22;
		अवरोध;
	हाल MGN_MCS11:
		rateIndex = 23;
		अवरोध;
	हाल MGN_MCS12:
		rateIndex = 24;
		अवरोध;
	हाल MGN_MCS13:
		rateIndex = 25;
		अवरोध;
	हाल MGN_MCS14:
		rateIndex = 26;
		अवरोध;
	हाल MGN_MCS15:
		rateIndex = 27;
		अवरोध;
	शेष:
		rateIndex = 28;
		अवरोध;
	पूर्ण
	priv->stats.received_preamble_GI[preamble_guardपूर्णांकerval][rateIndex]++;
	priv->stats.received_rate_histogram[0][rateIndex]++;
	priv->stats.received_rate_histogram[rcvType][rateIndex]++;
पूर्ण

bool rtl92e_get_rx_stats(काष्ठा net_device *dev, काष्ठा rtllib_rx_stats *stats,
			 काष्ठा rx_desc *pdesc, काष्ठा sk_buff *skb)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rx_fwinfo *pDrvInfo = शून्य;

	stats->bICV = pdesc->ICV;
	stats->bCRC = pdesc->CRC32;
	stats->bHwError = pdesc->CRC32 | pdesc->ICV;

	stats->Length = pdesc->Length;
	अगर (stats->Length < 24)
		stats->bHwError |= 1;

	अगर (stats->bHwError) अणु
		stats->bShअगरt = false;

		अगर (pdesc->CRC32) अणु
			अगर (pdesc->Length < 500)
				priv->stats.rxcrcerrmin++;
			अन्यथा अगर (pdesc->Length > 1000)
				priv->stats.rxcrcerrmax++;
			अन्यथा
				priv->stats.rxcrcerrmid++;
		पूर्ण
		वापस false;
	पूर्ण

	stats->RxDrvInfoSize = pdesc->RxDrvInfoSize;
	stats->RxBufShअगरt = (pdesc->Shअगरt) & 0x03;
	stats->Decrypted = !pdesc->SWDec;

	pDrvInfo = (काष्ठा rx_fwinfo *)(skb->data + stats->RxBufShअगरt);

	stats->rate = _rtl92e_rate_hw_to_mgn((bool)pDrvInfo->RxHT,
					     (u8)pDrvInfo->RxRate);
	stats->bShortPreamble = pDrvInfo->SPLCP;

	_rtl92e_update_received_rate_histogram_stats(dev, stats);

	stats->bIsAMPDU = (pDrvInfo->PartAggr == 1);
	stats->bFirstMPDU = (pDrvInfo->PartAggr == 1) &&
			    (pDrvInfo->FirstAGGR == 1);

	stats->TimeStampLow = pDrvInfo->TSFL;
	stats->TimeStampHigh = rtl92e_पढ़ोl(dev, TSFR+4);

	rtl92e_update_rx_pkt_बारtamp(dev, stats);

	अगर ((stats->RxBufShअगरt + stats->RxDrvInfoSize) > 0)
		stats->bShअगरt = 1;

	stats->RxIs40MHzPacket = pDrvInfo->BW;

	_rtl92e_translate_rx_संकेत_stats(dev, skb, stats, pdesc, pDrvInfo);

	अगर (pDrvInfo->FirstAGGR == 1 || pDrvInfo->PartAggr == 1)
		RT_TRACE(COMP_RXDESC,
			 "pDrvInfo->FirstAGGR = %d, pDrvInfo->PartAggr = %d\n",
			 pDrvInfo->FirstAGGR, pDrvInfo->PartAggr);
	skb_trim(skb, skb->len - 4/*sCrcLng*/);


	stats->packetlength = stats->Length-4;
	stats->fraglength = stats->packetlength;
	stats->fragoffset = 0;
	stats->ntotalfrag = 1;
	वापस true;
पूर्ण

व्योम rtl92e_stop_adapter(काष्ठा net_device *dev, bool reset)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	पूर्णांक i;
	u8	OpMode;
	u8	u1bTmp;
	u32	ulRegRead;

	OpMode = RT_OP_MODE_NO_LINK;
	priv->rtllib->SetHwRegHandler(dev, HW_VAR_MEDIA_STATUS, &OpMode);

	अगर (!priv->rtllib->bSupportRemoteWakeUp) अणु
		u1bTmp = 0x0;
		rtl92e_ग_लिखोb(dev, CMDR, u1bTmp);
	पूर्ण

	mdelay(20);

	अगर (!reset) अणु
		mdelay(150);

		priv->bHwRfOffAction = 2;

		अगर (!priv->rtllib->bSupportRemoteWakeUp) अणु
			rtl92e_set_rf_off(dev);
			ulRegRead = rtl92e_पढ़ोl(dev, CPU_GEN);
			ulRegRead |= CPU_GEN_SYSTEM_RESET;
			rtl92e_ग_लिखोl(dev, CPU_GEN, ulRegRead);
		पूर्ण अन्यथा अणु
			rtl92e_ग_लिखोl(dev, WFCRC0, 0xffffffff);
			rtl92e_ग_लिखोl(dev, WFCRC1, 0xffffffff);
			rtl92e_ग_लिखोl(dev, WFCRC2, 0xffffffff);


			rtl92e_ग_लिखोb(dev, PMR, 0x5);
			rtl92e_ग_लिखोb(dev, MacBlkCtrl, 0xa);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_purge(&priv->rtllib->skb_रुकोQ[i]);
	क्रम (i = 0; i < MAX_QUEUE_SIZE; i++)
		skb_queue_purge(&priv->rtllib->skb_aggQ[i]);

	skb_queue_purge(&priv->skb_queue);
पूर्ण

व्योम rtl92e_update_ratr_table(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;
	u8 *pMcsRate = ieee->करोt11HTOperationalRateSet;
	u32 ratr_value = 0;
	u16 rate_config = 0;
	u8 rate_index = 0;

	rtl92e_config_rate(dev, &rate_config);
	ratr_value = rate_config | *pMcsRate << 12;
	चयन (ieee->mode) अणु
	हाल IEEE_A:
		ratr_value &= 0x00000FF0;
		अवरोध;
	हाल IEEE_B:
		ratr_value &= 0x0000000F;
		अवरोध;
	हाल IEEE_G:
	हाल IEEE_G|IEEE_B:
		ratr_value &= 0x00000FF7;
		अवरोध;
	हाल IEEE_N_24G:
	हाल IEEE_N_5G:
		अगर (ieee->pHTInfo->PeerMimoPs == 0) अणु
			ratr_value &= 0x0007F007;
		पूर्ण अन्यथा अणु
			अगर (priv->rf_type == RF_1T2R)
				ratr_value &= 0x000FF007;
			अन्यथा
				ratr_value &= 0x0F81F007;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ratr_value &= 0x0FFFFFFF;
	अगर (ieee->pHTInfo->bCurTxBW40MHz &&
	    ieee->pHTInfo->bCurShortGI40MHz)
		ratr_value |= 0x80000000;
	अन्यथा अगर (!ieee->pHTInfo->bCurTxBW40MHz &&
		  ieee->pHTInfo->bCurShortGI20MHz)
		ratr_value |= 0x80000000;
	rtl92e_ग_लिखोl(dev, RATR0+rate_index*4, ratr_value);
	rtl92e_ग_लिखोb(dev, UFWP, 1);
पूर्ण

व्योम
rtl92e_init_variables(काष्ठा net_device  *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);

	म_नकल(priv->nick, "rtl8192E");

	priv->rtllib->sofपंचांगac_features  = IEEE_SOFTMAC_SCAN |
		IEEE_SOFTMAC_ASSOCIATE | IEEE_SOFTMAC_PROBERQ |
		IEEE_SOFTMAC_PROBERS | IEEE_SOFTMAC_TX_QUEUE;

	priv->rtllib->tx_headroom = माप(काष्ठा tx_fwinfo_8190pci);

	priv->ShortRetryLimit = 0x30;
	priv->LongRetryLimit = 0x30;

	priv->ReceiveConfig = RCR_ADD3	|
		RCR_AMF | RCR_ADF |
		RCR_AICV |
		RCR_AB | RCR_AM | RCR_APM |
		RCR_AAP | ((u32)7<<RCR_MXDMA_OFFSET) |
		((u32)7 << RCR_FIFO_OFFSET) | RCR_ONLYERLPKT;

	priv->irq_mask[0] = (u32)(IMR_ROK | IMR_VODOK | IMR_VIDOK |
			    IMR_BEDOK | IMR_BKDOK | IMR_HCCADOK |
			    IMR_MGNTDOK | IMR_COMDOK | IMR_HIGHDOK |
			    IMR_BDOK | IMR_RXCMDOK | IMR_TIMEOUT0 |
			    IMR_RDU | IMR_RXFOVW | IMR_TXFOVW |
			    IMR_BcnInt | IMR_TBDOK | IMR_TBDER);

	priv->PwrDoमुख्यProtect = false;

	priv->bfirst_after_करोwn = false;
पूर्ण

व्योम rtl92e_enable_irq(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);

	priv->irq_enabled = 1;

	rtl92e_ग_लिखोl(dev, INTA_MASK, priv->irq_mask[0]);

पूर्ण

व्योम rtl92e_disable_irq(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);

	rtl92e_ग_लिखोl(dev, INTA_MASK, 0);

	priv->irq_enabled = 0;
पूर्ण

व्योम rtl92e_clear_irq(काष्ठा net_device *dev)
अणु
	u32 पंचांगp;

	पंचांगp = rtl92e_पढ़ोl(dev, ISR);
	rtl92e_ग_लिखोl(dev, ISR, पंचांगp);
पूर्ण


व्योम rtl92e_enable_rx(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);

	rtl92e_ग_लिखोl(dev, RDQDA, priv->rx_ring_dma[RX_MPDU_QUEUE]);
पूर्ण

अटल स्थिर u32 TX_DESC_BASE[] = अणु
	BKQDA, BEQDA, VIQDA, VOQDA, HCCAQDA, CQDA, MQDA, HQDA, BQDA
पूर्ण;

व्योम rtl92e_enable_tx(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = (काष्ठा r8192_priv *)rtllib_priv(dev);
	u32 i;

	क्रम (i = 0; i < MAX_TX_QUEUE_COUNT; i++)
		rtl92e_ग_लिखोl(dev, TX_DESC_BASE[i], priv->tx_ring[i].dma);
पूर्ण


व्योम rtl92e_ack_irq(काष्ठा net_device *dev, u32 *p_पूर्णांकa, u32 *p_पूर्णांकb)
अणु
	*p_पूर्णांकa = rtl92e_पढ़ोl(dev, ISR);
	rtl92e_ग_लिखोl(dev, ISR, *p_पूर्णांकa);
पूर्ण

bool rtl92e_is_rx_stuck(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	u16		  RegRxCounter = rtl92e_पढ़ोw(dev, 0x130);
	bool		  bStuck = false;
	अटल u8	  rx_chk_cnt;
	u32		SlotIndex = 0, TotalRxStuckCount = 0;
	u8		i;
	u8		SilentResetRxSoltNum = 4;

	RT_TRACE(COMP_RESET, "%s(): RegRxCounter is %d, RxCounter is %d\n",
		 __func__, RegRxCounter, priv->RxCounter);

	rx_chk_cnt++;
	अगर (priv->undecorated_smoothed_pwdb >= (RateAdaptiveTH_High+5)) अणु
		rx_chk_cnt = 0;
	पूर्ण अन्यथा अगर ((priv->undecorated_smoothed_pwdb < (RateAdaptiveTH_High + 5))
	  && (((priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) &&
	  (priv->undecorated_smoothed_pwdb >= RateAdaptiveTH_Low_40M))
	  || ((priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20) &&
	  (priv->undecorated_smoothed_pwdb >= RateAdaptiveTH_Low_20M)))) अणु
		अगर (rx_chk_cnt < 2)
			वापस bStuck;
		rx_chk_cnt = 0;
	पूर्ण अन्यथा अगर ((((priv->CurrentChannelBW != HT_CHANNEL_WIDTH_20) &&
		  (priv->undecorated_smoothed_pwdb < RateAdaptiveTH_Low_40M)) ||
		((priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20) &&
		 (priv->undecorated_smoothed_pwdb < RateAdaptiveTH_Low_20M))) &&
		priv->undecorated_smoothed_pwdb >= VeryLowRSSI) अणु
		अगर (rx_chk_cnt < 4)
			वापस bStuck;
		rx_chk_cnt = 0;
	पूर्ण अन्यथा अणु
		अगर (rx_chk_cnt < 8)
			वापस bStuck;
		rx_chk_cnt = 0;
	पूर्ण


	SlotIndex = (priv->SilentResetRxSlotIndex++)%SilentResetRxSoltNum;

	अगर (priv->RxCounter == RegRxCounter) अणु
		priv->SilentResetRxStuckEvent[SlotIndex] = 1;

		क्रम (i = 0; i < SilentResetRxSoltNum; i++)
			TotalRxStuckCount += priv->SilentResetRxStuckEvent[i];

		अगर (TotalRxStuckCount == SilentResetRxSoltNum) अणु
			bStuck = true;
			क्रम (i = 0; i < SilentResetRxSoltNum; i++)
				TotalRxStuckCount +=
					 priv->SilentResetRxStuckEvent[i];
		पूर्ण


	पूर्ण अन्यथा अणु
		priv->SilentResetRxStuckEvent[SlotIndex] = 0;
	पूर्ण

	priv->RxCounter = RegRxCounter;

	वापस bStuck;
पूर्ण

bool rtl92e_is_tx_stuck(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	bool	bStuck = false;
	u16	RegTxCounter = rtl92e_पढ़ोw(dev, 0x128);

	RT_TRACE(COMP_RESET, "%s():RegTxCounter is %d,TxCounter is %d\n",
		 __func__, RegTxCounter, priv->TxCounter);

	अगर (priv->TxCounter == RegTxCounter)
		bStuck = true;

	priv->TxCounter = RegTxCounter;

	वापस bStuck;
पूर्ण

bool rtl92e_get_nmode_support_by_sec(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	अगर (ieee->rtllib_ap_sec_type &&
	   (ieee->rtllib_ap_sec_type(priv->rtllib)&(SEC_ALG_WEP |
				     SEC_ALG_TKIP))) अणु
		वापस false;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण
पूर्ण

bool rtl92e_is_halfn_supported_by_ap(काष्ठा net_device *dev)
अणु
	काष्ठा r8192_priv *priv = rtllib_priv(dev);
	काष्ठा rtllib_device *ieee = priv->rtllib;

	वापस ieee->bHalfWirelessN24GMode;
पूर्ण
