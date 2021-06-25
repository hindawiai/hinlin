<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#समावेश "rtllib.h"
#समावेश "rtl819x_HT.h"
u8 MCS_FILTER_ALL[16] = अणु
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
पूर्ण;

u8 MCS_FILTER_1SS[16] = अणु
	0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण
;

u16 MCS_DATA_RATE[2][2][77] = अणु
	अणुअणु13, 26, 39, 52, 78, 104, 117, 130, 26, 52, 78, 104, 156, 208, 234,
	 260, 39, 78, 117, 234, 312, 351, 390, 52, 104, 156, 208, 312, 416,
	 468, 520, 0, 78, 104, 130, 117, 156, 195, 104, 130, 130, 156, 182,
	 182, 208, 156, 195, 195, 234, 273, 273, 312, 130, 156, 181, 156,
	 181, 208, 234, 208, 234, 260, 260, 286, 195, 234, 273, 234, 273,
	 312, 351, 312, 351, 390, 390, 429पूर्ण,
	अणु14, 29, 43, 58, 87, 116, 130, 144, 29, 58, 87, 116, 173, 231, 260, 289,
	 43, 87, 130, 173, 260, 347, 390, 433, 58, 116, 173, 231, 347, 462, 520,
	 578, 0, 87, 116, 144, 130, 173, 217, 116, 144, 144, 173, 202, 202, 231,
	 173, 217, 217, 260, 303, 303, 347, 144, 173, 202, 173, 202, 231, 260,
	 231, 260, 289, 289, 318, 217, 260, 303, 260, 303, 347, 390, 347, 390,
	 433, 433, 477पूर्ण पूर्ण,
	अणुअणु27, 54, 81, 108, 162, 216, 243, 270, 54, 108, 162, 216, 324, 432, 486,
	 540, 81, 162, 243, 324, 486, 648, 729, 810, 108, 216, 324, 432, 648,
	 864, 972, 1080, 12, 162, 216, 270, 243, 324, 405, 216, 270, 270, 324,
	 378, 378, 432, 324, 405, 405, 486, 567, 567, 648, 270, 324, 378, 324,
	 378, 432, 486, 432, 486, 540, 540, 594, 405, 486, 567, 486, 567, 648,
	 729, 648, 729, 810, 810, 891पूर्ण,
	अणु30, 60, 90, 120, 180, 240, 270, 300, 60, 120, 180, 240, 360, 480, 540,
	 600, 90, 180, 270, 360, 540, 720, 810, 900, 120, 240, 360, 480, 720,
	 960, 1080, 1200, 13, 180, 240, 300, 270, 360, 450, 240, 300, 300, 360,
	 420, 420, 480, 360, 450, 450, 540, 630, 630, 720, 300, 360, 420, 360,
	 420, 480, 540, 480, 540, 600, 600, 660, 450, 540, 630, 540, 630, 720,
	 810, 720, 810, 900, 900, 990पूर्ण पूर्ण
पूर्ण;

अटल u8 UNKNOWN_BORADCOM[3] = अणु0x00, 0x14, 0xbfपूर्ण;

अटल u8 LINKSYSWRT330_LINKSYSWRT300_BROADCOM[3] = अणु0x00, 0x1a, 0x70पूर्ण;

अटल u8 LINKSYSWRT350_LINKSYSWRT150_BROADCOM[3] = अणु0x00, 0x1d, 0x7eपूर्ण;

अटल u8 BELKINF5D8233V1_RALINK[3] = अणु0x00, 0x17, 0x3fपूर्ण;

अटल u8 BELKINF5D82334V3_RALINK[3] = अणु0x00, 0x1c, 0xdfपूर्ण;

अटल u8 PCI_RALINK[3] = अणु0x00, 0x90, 0xccपूर्ण;

अटल u8 EDIMAX_RALINK[3] = अणु0x00, 0x0e, 0x2eपूर्ण;

अटल u8 AIRLINK_RALINK[3] = अणु0x00, 0x18, 0x02पूर्ण;

अटल u8 DLINK_ATHEROS_1[3] = अणु0x00, 0x1c, 0xf0पूर्ण;

अटल u8 DLINK_ATHEROS_2[3] = अणु0x00, 0x21, 0x91पूर्ण;

अटल u8 CISCO_BROADCOM[3] = अणु0x00, 0x17, 0x94पूर्ण;

अटल u8 LINKSYS_MARVELL_4400N[3] = अणु0x00, 0x14, 0xa4पूर्ण;

व्योम HTUpdateDefaultSetting(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	pHTInfo->bAcceptAddbaReq = 1;

	pHTInfo->bRegShortGI20MHz = 1;
	pHTInfo->bRegShortGI40MHz = 1;

	pHTInfo->bRegBW40MHz = 1;

	अगर (pHTInfo->bRegBW40MHz)
		pHTInfo->bRegSuppCCK = 1;
	अन्यथा
		pHTInfo->bRegSuppCCK = true;

	pHTInfo->nAMSDU_MaxSize = 7935UL;
	pHTInfo->bAMSDU_Support = 0;

	pHTInfo->bAMPDUEnable = 1;
	pHTInfo->AMPDU_Factor = 2;
	pHTInfo->MPDU_Density = 0;

	pHTInfo->SelfMimoPs = 3;
	अगर (pHTInfo->SelfMimoPs == 2)
		pHTInfo->SelfMimoPs = 3;
	ieee->bTxDisableRateFallBack = 0;
	ieee->bTxUseDriverAssingedRate = 0;

	ieee->bTxEnableFwCalcDur = 1;

	pHTInfo->bRegRT2RTAggregation = 1;

	pHTInfo->bRegRxReorderEnable = 1;
	pHTInfo->RxReorderWinSize = 64;
	pHTInfo->RxReorderPendingTime = 30;
पूर्ण

अटल u16 HTMcsToDataRate(काष्ठा rtllib_device *ieee, u8 nMcsRate)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	u8	is40MHz = (pHTInfo->bCurBW40MHz) ? 1 : 0;
	u8	isShortGI = (pHTInfo->bCurBW40MHz) ?
			    ((pHTInfo->bCurShortGI40MHz) ? 1 : 0) :
			    ((pHTInfo->bCurShortGI20MHz) ? 1 : 0);
	वापस MCS_DATA_RATE[is40MHz][isShortGI][(nMcsRate & 0x7f)];
पूर्ण

u16  TxCountToDataRate(काष्ठा rtllib_device *ieee, u8 nDataRate)
अणु
	u16	CCKOFDMRate[12] = अणु0x02, 0x04, 0x0b, 0x16, 0x0c, 0x12, 0x18,
				   0x24, 0x30, 0x48, 0x60, 0x6cपूर्ण;
	u8	is40MHz = 0;
	u8	isShortGI = 0;

	अगर (nDataRate < 12)
		वापस CCKOFDMRate[nDataRate];
	अगर (nDataRate >= 0x10 && nDataRate <= 0x1f) अणु
		is40MHz = 0;
		isShortGI = 0;
	पूर्ण अन्यथा अगर (nDataRate >= 0x20  && nDataRate <= 0x2f) अणु
		is40MHz = 1;
		isShortGI = 0;
	पूर्ण अन्यथा अगर (nDataRate >= 0x30  && nDataRate <= 0x3f) अणु
		is40MHz = 0;
		isShortGI = 1;
	पूर्ण अन्यथा अगर (nDataRate >= 0x40  && nDataRate <= 0x4f) अणु
		is40MHz = 1;
		isShortGI = 1;
	पूर्ण
	वापस MCS_DATA_RATE[is40MHz][isShortGI][nDataRate & 0xf];
पूर्ण

bool IsHTHalfNmodeAPs(काष्ठा rtllib_device *ieee)
अणु
	bool			retValue = false;
	काष्ठा rtllib_network *net = &ieee->current_network;

	अगर ((स_भेद(net->bssid, BELKINF5D8233V1_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, BELKINF5D82334V3_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, PCI_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, EDIMAX_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, AIRLINK_RALINK, 3) == 0) ||
	    (net->ralink_cap_exist))
		retValue = true;
	अन्यथा अगर (!स_भेद(net->bssid, UNKNOWN_BORADCOM, 3) ||
		!स_भेद(net->bssid, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) ||
		!स_भेद(net->bssid, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3) ||
		(net->broadcom_cap_exist))
		retValue = true;
	अन्यथा अगर (net->bssht.bd_rt2rt_aggregation)
		retValue = true;
	अन्यथा
		retValue = false;

	वापस retValue;
पूर्ण

अटल व्योम HTIOTPeerDetermine(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	काष्ठा rtllib_network *net = &ieee->current_network;

	अगर (net->bssht.bd_rt2rt_aggregation) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_REALTEK;
		अगर (net->bssht.rt2rt_ht_mode & RT_HT_CAP_USE_92SE)
			pHTInfo->IOTPeer = HT_IOT_PEER_REALTEK_92SE;
		अगर (net->bssht.rt2rt_ht_mode & RT_HT_CAP_USE_SOFTAP)
			pHTInfo->IOTPeer = HT_IOT_PEER_92U_SOFTAP;
	पूर्ण अन्यथा अगर (net->broadcom_cap_exist) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	पूर्ण अन्यथा अगर (!स_भेद(net->bssid, UNKNOWN_BORADCOM, 3) ||
		 !स_भेद(net->bssid, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) ||
		 !स_भेद(net->bssid, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3)) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	पूर्ण अन्यथा अगर ((स_भेद(net->bssid, BELKINF5D8233V1_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, BELKINF5D82334V3_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, PCI_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, EDIMAX_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, AIRLINK_RALINK, 3) == 0) ||
		  net->ralink_cap_exist) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_RALINK;
	पूर्ण अन्यथा अगर ((net->atheros_cap_exist) ||
		(स_भेद(net->bssid, DLINK_ATHEROS_1, 3) == 0) ||
		(स_भेद(net->bssid, DLINK_ATHEROS_2, 3) == 0)) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_ATHEROS;
	पूर्ण अन्यथा अगर ((स_भेद(net->bssid, CISCO_BROADCOM, 3) == 0) ||
		  net->cisco_cap_exist) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_CISCO;
	पूर्ण अन्यथा अगर ((स_भेद(net->bssid, LINKSYS_MARVELL_4400N, 3) == 0) ||
		  net->marvell_cap_exist) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_MARVELL;
	पूर्ण अन्यथा अगर (net->airgo_cap_exist) अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_AIRGO;
	पूर्ण अन्यथा अणु
		pHTInfo->IOTPeer = HT_IOT_PEER_UNKNOWN;
	पूर्ण

	netdev_dbg(ieee->dev, "IOTPEER: %x\n", pHTInfo->IOTPeer);
पूर्ण

अटल u8 HTIOTActIsDisableMCS14(काष्ठा rtllib_device *ieee, u8 *PeerMacAddr)
अणु
	वापस 0;
पूर्ण

अटल bool HTIOTActIsDisableMCS15(काष्ठा rtllib_device *ieee)
अणु
	वापस false;
पूर्ण

अटल bool HTIOTActIsDisableMCSTwoSpatialStream(काष्ठा rtllib_device *ieee)
अणु
	वापस false;
पूर्ण

अटल u8 HTIOTActIsDisableEDCATurbo(काष्ठा rtllib_device *ieee,
				     u8 *PeerMacAddr)
अणु
	वापस false;
पूर्ण

अटल u8 HTIOTActIsMgntUseCCK6M(काष्ठा rtllib_device *ieee,
				 काष्ठा rtllib_network *network)
अणु
	u8	retValue = 0;

	अगर (ieee->pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM)
		retValue = 1;

	वापस retValue;
पूर्ण

अटल u8 HTIOTActIsCCDFsync(काष्ठा rtllib_device *ieee)
अणु
	u8	retValue = 0;

	अगर (ieee->pHTInfo->IOTPeer == HT_IOT_PEER_BROADCOM)
		retValue = 1;
	वापस retValue;
पूर्ण

अटल व्योम HTIOTActDetermineRaFunc(काष्ठा rtllib_device *ieee, bool bPeerRx2ss)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	pHTInfo->IOTRaFunc &= HT_IOT_RAFUNC_DISABLE_ALL;

	अगर (pHTInfo->IOTPeer == HT_IOT_PEER_RALINK && !bPeerRx2ss)
		pHTInfo->IOTRaFunc |= HT_IOT_RAFUNC_PEER_1R;

	अगर (pHTInfo->IOTAction & HT_IOT_ACT_AMSDU_ENABLE)
		pHTInfo->IOTRaFunc |= HT_IOT_RAFUNC_TX_AMSDU;
पूर्ण

व्योम HTResetIOTSetting(काष्ठा rt_hi_throughput *pHTInfo)
अणु
	pHTInfo->IOTAction = 0;
	pHTInfo->IOTPeer = HT_IOT_PEER_UNKNOWN;
	pHTInfo->IOTRaFunc = 0;
पूर्ण

व्योम HTConकाष्ठाCapabilityElement(काष्ठा rtllib_device *ieee, u8 *posHTCap,
				  u8 *len, u8 IsEncrypt, bool bAssoc)
अणु
	काष्ठा rt_hi_throughput *pHT = ieee->pHTInfo;
	काष्ठा ht_capab_ele *pCapELE = शून्य;

	अगर ((posHTCap == शून्य) || (pHT == शून्य)) अणु
		netdev_warn(ieee->dev,
			    "%s(): posHTCap and pHTInfo are null\n", __func__);
		वापस;
	पूर्ण
	स_रखो(posHTCap, 0, *len);

	अगर ((bAssoc) && (pHT->ePeerHTSpecVer == HT_SPEC_VER_EWC)) अणु
		u8	EWC11NHTCap[] = अणु0x00, 0x90, 0x4c, 0x33पूर्ण;

		स_नकल(posHTCap, EWC11NHTCap, माप(EWC11NHTCap));
		pCapELE = (काष्ठा ht_capab_ele *)&(posHTCap[4]);
		*len = 30 + 2;
	पूर्ण अन्यथा अणु
		pCapELE = (काष्ठा ht_capab_ele *)posHTCap;
		*len = 26 + 2;
	पूर्ण

	pCapELE->AdvCoding		= 0;
	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		pCapELE->ChlWidth = 0;
	अन्यथा
		pCapELE->ChlWidth = (pHT->bRegBW40MHz ? 1 : 0);

	pCapELE->MimoPwrSave		= pHT->SelfMimoPs;
	pCapELE->GreenField		= 0;
	pCapELE->ShortGI20Mhz		= 1;
	pCapELE->ShortGI40Mhz		= 1;

	pCapELE->TxSTBC			= 1;
	pCapELE->RxSTBC			= 0;
	pCapELE->DelayBA		= 0;
	pCapELE->MaxAMSDUSize = (MAX_RECEIVE_BUFFER_SIZE >= 7935) ? 1 : 0;
	pCapELE->DssCCk = ((pHT->bRegBW40MHz) ? (pHT->bRegSuppCCK ? 1 : 0) : 0);
	pCapELE->PSMP = 0;
	pCapELE->LSigTxopProtect = 0;

	netdev_dbg(ieee->dev,
		   "TX HT cap/info ele BW=%d MaxAMSDUSize:%d DssCCk:%d\n",
		   pCapELE->ChlWidth, pCapELE->MaxAMSDUSize, pCapELE->DssCCk);

	अगर (IsEncrypt) अणु
		pCapELE->MPDUDensity	= 7;
		pCapELE->MaxRxAMPDUFactor	= 2;
	पूर्ण अन्यथा अणु
		pCapELE->MaxRxAMPDUFactor	= 3;
		pCapELE->MPDUDensity	= 0;
	पूर्ण

	स_नकल(pCapELE->MCS, ieee->Regकरोt11HTOperationalRateSet, 16);
	स_रखो(&pCapELE->ExtHTCapInfo, 0, 2);
	स_रखो(pCapELE->TxBFCap, 0, 4);

	pCapELE->ASCap = 0;

	अगर (bAssoc) अणु
		अगर (pHT->IOTAction & HT_IOT_ACT_DISABLE_MCS15)
			pCapELE->MCS[1] &= 0x7f;

		अगर (pHT->IOTAction & HT_IOT_ACT_DISABLE_MCS14)
			pCapELE->MCS[1] &= 0xbf;

		अगर (pHT->IOTAction & HT_IOT_ACT_DISABLE_ALL_2SS)
			pCapELE->MCS[1] &= 0x00;

		अगर (pHT->IOTAction & HT_IOT_ACT_DISABLE_RX_40MHZ_SHORT_GI)
			pCapELE->ShortGI40Mhz		= 0;

		अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev)) अणु
			pCapELE->ChlWidth = 0;
			pCapELE->MCS[1] = 0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम HTConकाष्ठाInfoElement(काष्ठा rtllib_device *ieee, u8 *posHTInfo,
			    u8 *len, u8 IsEncrypt)
अणु
	काष्ठा rt_hi_throughput *pHT = ieee->pHTInfo;
	काष्ठा ht_info_ele *pHTInfoEle = (काष्ठा ht_info_ele *)posHTInfo;

	अगर ((posHTInfo == शून्य) || (pHTInfoEle == शून्य)) अणु
		netdev_warn(ieee->dev,
			    "%s(): posHTInfo and pHTInfoEle are null\n",
			    __func__);
		वापस;
	पूर्ण

	स_रखो(posHTInfo, 0, *len);
	अगर ((ieee->iw_mode == IW_MODE_ADHOC) ||
	    (ieee->iw_mode == IW_MODE_MASTER)) अणु
		pHTInfoEle->ControlChl	= ieee->current_network.channel;
		pHTInfoEle->ExtChlOffset = ((!pHT->bRegBW40MHz) ?
					    HT_EXTCHNL_OFFSET_NO_EXT :
					    (ieee->current_network.channel <= 6)
					    ? HT_EXTCHNL_OFFSET_UPPER :
					    HT_EXTCHNL_OFFSET_LOWER);
		pHTInfoEle->RecommemdedTxWidth	= pHT->bRegBW40MHz;
		pHTInfoEle->RIFS			= 0;
		pHTInfoEle->PSMPAccessOnly		= 0;
		pHTInfoEle->SrvIntGranularity		= 0;
		pHTInfoEle->OptMode			= pHT->CurrentOpMode;
		pHTInfoEle->NonGFDevPresent		= 0;
		pHTInfoEle->DualBeacon			= 0;
		pHTInfoEle->SecondaryBeacon		= 0;
		pHTInfoEle->LSigTxopProtectFull		= 0;
		pHTInfoEle->PcoActive			= 0;
		pHTInfoEle->PcoPhase			= 0;

		स_रखो(pHTInfoEle->BasicMSC, 0, 16);

		*len = 22 + 2;

	पूर्ण अन्यथा अणु
		*len = 0;
	पूर्ण
पूर्ण

व्योम HTConकाष्ठाRT2RTAggElement(काष्ठा rtllib_device *ieee, u8 *posRT2RTAgg,
				u8 *len)
अणु
	अगर (posRT2RTAgg == शून्य) अणु
		netdev_warn(ieee->dev, "%s(): posRT2RTAgg is null\n", __func__);
		वापस;
	पूर्ण
	स_रखो(posRT2RTAgg, 0, *len);
	*posRT2RTAgg++ = 0x00;
	*posRT2RTAgg++ = 0xe0;
	*posRT2RTAgg++ = 0x4c;
	*posRT2RTAgg++ = 0x02;
	*posRT2RTAgg++ = 0x01;

	*posRT2RTAgg = 0x30;

	अगर (ieee->bSupportRemoteWakeUp)
		*posRT2RTAgg |= RT_HT_CAP_USE_WOW;

	*len = 6 + 2;
पूर्ण

अटल u8 HT_PickMCSRate(काष्ठा rtllib_device *ieee, u8 *pOperateMCS)
अणु
	u8 i;

	अगर (pOperateMCS == शून्य) अणु
		netdev_warn(ieee->dev, "%s(): pOperateMCS is null\n", __func__);
		वापस false;
	पूर्ण

	चयन (ieee->mode) अणु
	हाल IEEE_A:
	हाल IEEE_B:
	हाल IEEE_G:
		क्रम (i = 0; i <= 15; i++)
			pOperateMCS[i] = 0;
		अवरोध;
	हाल IEEE_N_24G:
	हाल IEEE_N_5G:
		pOperateMCS[0] &= RATE_ADPT_1SS_MASK;
		pOperateMCS[1] &= RATE_ADPT_2SS_MASK;
		pOperateMCS[3] &= RATE_ADPT_MCS32_MASK;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

u8 HTGetHighestMCSRate(काष्ठा rtllib_device *ieee, u8 *pMCSRateSet,
		       u8 *pMCSFilter)
अणु
	u8		i, j;
	u8		bitMap;
	u8		mcsRate = 0;
	u8		availableMcsRate[16];

	अगर (pMCSRateSet == शून्य || pMCSFilter == शून्य) अणु
		netdev_warn(ieee->dev,
			    "%s(): pMCSRateSet and pMCSFilter are null\n",
			    __func__);
		वापस false;
	पूर्ण
	क्रम (i = 0; i < 16; i++)
		availableMcsRate[i] = pMCSRateSet[i] & pMCSFilter[i];

	क्रम (i = 0; i < 16; i++) अणु
		अगर (availableMcsRate[i] != 0)
			अवरोध;
	पूर्ण
	अगर (i == 16)
		वापस false;

	क्रम (i = 0; i < 16; i++) अणु
		अगर (availableMcsRate[i] != 0) अणु
			bitMap = availableMcsRate[i];
			क्रम (j = 0; j < 8; j++) अणु
				अगर ((bitMap % 2) != 0) अणु
					अगर (HTMcsToDataRate(ieee, (8 * i + j)) >
					    HTMcsToDataRate(ieee, mcsRate))
						mcsRate = 8 * i + j;
				पूर्ण
				bitMap >>= 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस mcsRate | 0x80;
पूर्ण

अटल u8 HTFilterMCSRate(काष्ठा rtllib_device *ieee, u8 *pSupportMCS,
			  u8 *pOperateMCS)
अणु
	u8 i;

	क्रम (i = 0; i <= 15; i++)
		pOperateMCS[i] = ieee->Regकरोt11TxHTOperationalRateSet[i] &
				 pSupportMCS[i];

	HT_PickMCSRate(ieee, pOperateMCS);

	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		pOperateMCS[1] = 0;

	क्रम (i = 2; i <= 15; i++)
		pOperateMCS[i] = 0;

	वापस true;
पूर्ण

व्योम HTSetConnectBwMode(काष्ठा rtllib_device *ieee,
			क्रमागत ht_channel_width Bandwidth,
			क्रमागत ht_extchnl_offset Offset);

व्योम HTOnAssocRsp(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	काष्ठा ht_capab_ele *pPeerHTCap = शून्य;
	काष्ठा ht_info_ele *pPeerHTInfo = शून्य;
	u16 nMaxAMSDUSize = 0;
	u8 *pMcsFilter = शून्य;

	अटल u8 EWC11NHTCap[] = अणु0x00, 0x90, 0x4c, 0x33पूर्ण;
	अटल u8 EWC11NHTInfo[] = अणु0x00, 0x90, 0x4c, 0x34पूर्ण;

	अगर (!pHTInfo->bCurrentHTSupport) अणु
		netdev_warn(ieee->dev, "%s(): HT_DISABLE\n", __func__);
		वापस;
	पूर्ण
	netdev_dbg(ieee->dev, "%s(): HT_ENABLE\n", __func__);

	अगर (!स_भेद(pHTInfo->PeerHTCapBuf, EWC11NHTCap, माप(EWC11NHTCap)))
		pPeerHTCap = (काष्ठा ht_capab_ele *)(&pHTInfo->PeerHTCapBuf[4]);
	अन्यथा
		pPeerHTCap = (काष्ठा ht_capab_ele *)(pHTInfo->PeerHTCapBuf);

	अगर (!स_भेद(pHTInfo->PeerHTInfoBuf, EWC11NHTInfo, माप(EWC11NHTInfo)))
		pPeerHTInfo = (काष्ठा ht_info_ele *)
			     (&pHTInfo->PeerHTInfoBuf[4]);
	अन्यथा
		pPeerHTInfo = (काष्ठा ht_info_ele *)(pHTInfo->PeerHTInfoBuf);

#अगर_घोषित VERBOSE_DEBUG
	prपूर्णांक_hex_dump_bytes("%s: ", __func__, DUMP_PREFIX_NONE,
			     pPeerHTCap, माप(काष्ठा ht_capab_ele));
#पूर्ण_अगर
	HTSetConnectBwMode(ieee, (क्रमागत ht_channel_width)(pPeerHTCap->ChlWidth),
			  (क्रमागत ht_extchnl_offset)(pPeerHTInfo->ExtChlOffset));
	pHTInfo->bCurTxBW40MHz = ((pPeerHTInfo->RecommemdedTxWidth == 1) ?
				 true : false);

	pHTInfo->bCurShortGI20MHz = ((pHTInfo->bRegShortGI20MHz) ?
				    ((pPeerHTCap->ShortGI20Mhz == 1) ?
				    true : false) : false);
	pHTInfo->bCurShortGI40MHz = ((pHTInfo->bRegShortGI40MHz) ?
				     ((pPeerHTCap->ShortGI40Mhz == 1) ?
				     true : false) : false);

	pHTInfo->bCurSuppCCK = ((pHTInfo->bRegSuppCCK) ?
			       ((pPeerHTCap->DssCCk == 1) ? true :
			       false) : false);

	pHTInfo->bCurrent_AMSDU_Support = pHTInfo->bAMSDU_Support;

	nMaxAMSDUSize = (pPeerHTCap->MaxAMSDUSize == 0) ? 3839 : 7935;

	अगर (pHTInfo->nAMSDU_MaxSize > nMaxAMSDUSize)
		pHTInfo->nCurrent_AMSDU_MaxSize = nMaxAMSDUSize;
	अन्यथा
		pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;

	pHTInfo->bCurrentAMPDUEnable = pHTInfo->bAMPDUEnable;
	अगर (ieee->rtllib_ap_sec_type &&
	   (ieee->rtllib_ap_sec_type(ieee) & (SEC_ALG_WEP | SEC_ALG_TKIP))) अणु
		अगर ((pHTInfo->IOTPeer == HT_IOT_PEER_ATHEROS) ||
				(pHTInfo->IOTPeer == HT_IOT_PEER_UNKNOWN))
			pHTInfo->bCurrentAMPDUEnable = false;
	पूर्ण

	अगर (!pHTInfo->bRegRT2RTAggregation) अणु
		अगर (pHTInfo->AMPDU_Factor > pPeerHTCap->MaxRxAMPDUFactor)
			pHTInfo->CurrentAMPDUFactor =
						 pPeerHTCap->MaxRxAMPDUFactor;
		अन्यथा
			pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;

	पूर्ण अन्यथा अणु
		अगर (ieee->current_network.bssht.bd_rt2rt_aggregation) अणु
			अगर (ieee->pairwise_key_type != KEY_TYPE_NA)
				pHTInfo->CurrentAMPDUFactor =
						 pPeerHTCap->MaxRxAMPDUFactor;
			अन्यथा
				pHTInfo->CurrentAMPDUFactor = HT_AGG_SIZE_64K;
		पूर्ण अन्यथा अणु
			अगर (pPeerHTCap->MaxRxAMPDUFactor < HT_AGG_SIZE_32K)
				pHTInfo->CurrentAMPDUFactor =
						 pPeerHTCap->MaxRxAMPDUFactor;
			अन्यथा
				pHTInfo->CurrentAMPDUFactor = HT_AGG_SIZE_32K;
		पूर्ण
	पूर्ण
	अगर (pHTInfo->MPDU_Density > pPeerHTCap->MPDUDensity)
		pHTInfo->CurrentMPDUDensity = pHTInfo->MPDU_Density;
	अन्यथा
		pHTInfo->CurrentMPDUDensity = pPeerHTCap->MPDUDensity;
	अगर (pHTInfo->IOTAction & HT_IOT_ACT_TX_USE_AMSDU_8K) अणु
		pHTInfo->bCurrentAMPDUEnable = false;
		pHTInfo->ForcedAMSDUMode = HT_AGG_FORCE_ENABLE;
		pHTInfo->ForcedAMSDUMaxSize = 7935;
	पूर्ण
	pHTInfo->bCurRxReorderEnable = pHTInfo->bRegRxReorderEnable;

	अगर (pPeerHTCap->MCS[0] == 0)
		pPeerHTCap->MCS[0] = 0xff;

	HTIOTActDetermineRaFunc(ieee, ((pPeerHTCap->MCS[1]) != 0));

	HTFilterMCSRate(ieee, pPeerHTCap->MCS, ieee->करोt11HTOperationalRateSet);

	pHTInfo->PeerMimoPs = pPeerHTCap->MimoPwrSave;
	अगर (pHTInfo->PeerMimoPs == MIMO_PS_STATIC)
		pMcsFilter = MCS_FILTER_1SS;
	अन्यथा
		pMcsFilter = MCS_FILTER_ALL;
	ieee->HTHighestOperaRate = HTGetHighestMCSRate(ieee,
				   ieee->करोt11HTOperationalRateSet, pMcsFilter);
	ieee->HTCurrentOperaRate = ieee->HTHighestOperaRate;

	pHTInfo->CurrentOpMode = pPeerHTInfo->OptMode;
पूर्ण

व्योम HTInitializeHTInfo(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	pHTInfo->bCurrentHTSupport = false;

	pHTInfo->bCurBW40MHz = false;
	pHTInfo->bCurTxBW40MHz = false;

	pHTInfo->bCurShortGI20MHz = false;
	pHTInfo->bCurShortGI40MHz = false;
	pHTInfo->bForcedShortGI = false;

	pHTInfo->bCurSuppCCK = true;

	pHTInfo->bCurrent_AMSDU_Support = false;
	pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;
	pHTInfo->CurrentMPDUDensity = pHTInfo->MPDU_Density;
	pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;

	स_रखो((व्योम *)(&(pHTInfo->SelfHTCap)), 0,
		माप(pHTInfo->SelfHTCap));
	स_रखो((व्योम *)(&(pHTInfo->SelfHTInfo)), 0,
		माप(pHTInfo->SelfHTInfo));
	स_रखो((व्योम *)(&(pHTInfo->PeerHTCapBuf)), 0,
		माप(pHTInfo->PeerHTCapBuf));
	स_रखो((व्योम *)(&(pHTInfo->PeerHTInfoBuf)), 0,
		माप(pHTInfo->PeerHTInfoBuf));

	pHTInfo->bSwBwInProgress = false;

	pHTInfo->ePeerHTSpecVer = HT_SPEC_VER_IEEE;

	pHTInfo->bCurrentRT2RTAggregation = false;
	pHTInfo->bCurrentRT2RTLongSlotTime = false;
	pHTInfo->RT2RT_HT_Mode = (क्रमागत rt_ht_capability)0;

	pHTInfo->IOTPeer = 0;
	pHTInfo->IOTAction = 0;
	pHTInfo->IOTRaFunc = 0;

	अणु
		u8 *RegHTSuppRateSets = &(ieee->RegHTSuppRateSet[0]);

		RegHTSuppRateSets[0] = 0xFF;
		RegHTSuppRateSets[1] = 0xFF;
		RegHTSuppRateSets[4] = 0x01;
	पूर्ण
पूर्ण

व्योम HTInitializeBssDesc(काष्ठा bss_ht *pBssHT)
अणु
	pBssHT->bd_support_ht = false;
	स_रखो(pBssHT->bd_ht_cap_buf, 0, माप(pBssHT->bd_ht_cap_buf));
	pBssHT->bd_ht_cap_len = 0;
	स_रखो(pBssHT->bd_ht_info_buf, 0, माप(pBssHT->bd_ht_info_buf));
	pBssHT->bd_ht_info_len = 0;

	pBssHT->bd_ht_spec_ver = HT_SPEC_VER_IEEE;

	pBssHT->bd_rt2rt_aggregation = false;
	pBssHT->bd_rt2rt_दीर्घ_slot_समय = false;
	pBssHT->rt2rt_ht_mode = (क्रमागत rt_ht_capability)0;
पूर्ण

व्योम HTResetSelfAndSavePeerSetting(काष्ठा rtllib_device *ieee,
				   काष्ठा rtllib_network *pNetwork)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	u8	bIOTAction = 0;

	/* unmark bEnableHT flag here is the same reason why unmarked in
	 * function rtllib_sofपंचांगac_new_net. WB 2008.09.10
	 */
	अगर (pNetwork->bssht.bd_support_ht) अणु
		pHTInfo->bCurrentHTSupport = true;
		pHTInfo->ePeerHTSpecVer = pNetwork->bssht.bd_ht_spec_ver;

		अगर (pNetwork->bssht.bd_ht_cap_len > 0 &&
		    pNetwork->bssht.bd_ht_cap_len <= माप(pHTInfo->PeerHTCapBuf))
			स_नकल(pHTInfo->PeerHTCapBuf,
			       pNetwork->bssht.bd_ht_cap_buf,
			       pNetwork->bssht.bd_ht_cap_len);

		अगर (pNetwork->bssht.bd_ht_info_len > 0 &&
		    pNetwork->bssht.bd_ht_info_len <=
		    माप(pHTInfo->PeerHTInfoBuf))
			स_नकल(pHTInfo->PeerHTInfoBuf,
			       pNetwork->bssht.bd_ht_info_buf,
			       pNetwork->bssht.bd_ht_info_len);

		अगर (pHTInfo->bRegRT2RTAggregation) अणु
			pHTInfo->bCurrentRT2RTAggregation =
				 pNetwork->bssht.bd_rt2rt_aggregation;
			pHTInfo->bCurrentRT2RTLongSlotTime =
				 pNetwork->bssht.bd_rt2rt_दीर्घ_slot_समय;
			pHTInfo->RT2RT_HT_Mode = pNetwork->bssht.rt2rt_ht_mode;
		पूर्ण अन्यथा अणु
			pHTInfo->bCurrentRT2RTAggregation = false;
			pHTInfo->bCurrentRT2RTLongSlotTime = false;
			pHTInfo->RT2RT_HT_Mode = (क्रमागत rt_ht_capability)0;
		पूर्ण

		HTIOTPeerDetermine(ieee);

		pHTInfo->IOTAction = 0;
		bIOTAction = HTIOTActIsDisableMCS14(ieee, pNetwork->bssid);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_MCS14;

		bIOTAction = HTIOTActIsDisableMCS15(ieee);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_MCS15;

		bIOTAction = HTIOTActIsDisableMCSTwoSpatialStream(ieee);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_ALL_2SS;

		bIOTAction = HTIOTActIsDisableEDCATurbo(ieee, pNetwork->bssid);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_EDCA_TURBO;

		bIOTAction = HTIOTActIsMgntUseCCK6M(ieee, pNetwork);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_MGNT_USE_CCK_6M;
		bIOTAction = HTIOTActIsCCDFsync(ieee);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_CDD_FSYNC;
	पूर्ण अन्यथा अणु
		pHTInfo->bCurrentHTSupport = false;
		pHTInfo->bCurrentRT2RTAggregation = false;
		pHTInfo->bCurrentRT2RTLongSlotTime = false;
		pHTInfo->RT2RT_HT_Mode = (क्रमागत rt_ht_capability)0;

		pHTInfo->IOTAction = 0;
		pHTInfo->IOTRaFunc = 0;
	पूर्ण
पूर्ण

व्योम HT_update_self_and_peer_setting(काष्ठा rtllib_device *ieee,
				     काष्ठा rtllib_network *pNetwork)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;
	काष्ठा ht_info_ele *pPeerHTInfo =
		 (काष्ठा ht_info_ele *)pNetwork->bssht.bd_ht_info_buf;

	अगर (pHTInfo->bCurrentHTSupport) अणु
		अगर (pNetwork->bssht.bd_ht_info_len != 0)
			pHTInfo->CurrentOpMode = pPeerHTInfo->OptMode;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(HT_update_self_and_peer_setting);

व्योम HTUseDefaultSetting(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	अगर (pHTInfo->bEnableHT) अणु
		pHTInfo->bCurrentHTSupport = true;
		pHTInfo->bCurSuppCCK = pHTInfo->bRegSuppCCK;

		pHTInfo->bCurBW40MHz = pHTInfo->bRegBW40MHz;
		pHTInfo->bCurShortGI20MHz = pHTInfo->bRegShortGI20MHz;

		pHTInfo->bCurShortGI40MHz = pHTInfo->bRegShortGI40MHz;

		अगर (ieee->iw_mode == IW_MODE_ADHOC)
			ieee->current_network.qos_data.active =
				 ieee->current_network.qos_data.supported;
		pHTInfo->bCurrent_AMSDU_Support = pHTInfo->bAMSDU_Support;
		pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;

		pHTInfo->bCurrentAMPDUEnable = pHTInfo->bAMPDUEnable;
		pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;

		pHTInfo->CurrentMPDUDensity = pHTInfo->CurrentMPDUDensity;

		HTFilterMCSRate(ieee, ieee->Regकरोt11TxHTOperationalRateSet,
				ieee->करोt11HTOperationalRateSet);
		ieee->HTHighestOperaRate = HTGetHighestMCSRate(ieee,
					   ieee->करोt11HTOperationalRateSet,
					   MCS_FILTER_ALL);
		ieee->HTCurrentOperaRate = ieee->HTHighestOperaRate;

	पूर्ण अन्यथा अणु
		pHTInfo->bCurrentHTSupport = false;
	पूर्ण
पूर्ण

u8 HTCCheck(काष्ठा rtllib_device *ieee, u8 *pFrame)
अणु
	अगर (ieee->pHTInfo->bCurrentHTSupport) अणु
		अगर ((IsQoSDataFrame(pFrame) && Frame_Order(pFrame)) == 1) अणु
			netdev_dbg(ieee->dev, "HT CONTROL FILED EXIST!!\n");
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम HTSetConnectBwModeCallback(काष्ठा rtllib_device *ieee)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	अगर (pHTInfo->bCurBW40MHz) अणु
		अगर (pHTInfo->CurSTAExtChnlOffset == HT_EXTCHNL_OFFSET_UPPER)
			ieee->set_chan(ieee->dev,
				       ieee->current_network.channel + 2);
		अन्यथा अगर (pHTInfo->CurSTAExtChnlOffset ==
			 HT_EXTCHNL_OFFSET_LOWER)
			ieee->set_chan(ieee->dev,
				       ieee->current_network.channel - 2);
		अन्यथा
			ieee->set_chan(ieee->dev,
				       ieee->current_network.channel);

		ieee->SetBWModeHandler(ieee->dev, HT_CHANNEL_WIDTH_20_40,
				       pHTInfo->CurSTAExtChnlOffset);
	पूर्ण अन्यथा अणु
		ieee->set_chan(ieee->dev, ieee->current_network.channel);
		ieee->SetBWModeHandler(ieee->dev, HT_CHANNEL_WIDTH_20,
				       HT_EXTCHNL_OFFSET_NO_EXT);
	पूर्ण

	pHTInfo->bSwBwInProgress = false;
पूर्ण

व्योम HTSetConnectBwMode(काष्ठा rtllib_device *ieee,
			क्रमागत ht_channel_width Bandwidth,
			क्रमागत ht_extchnl_offset Offset)
अणु
	काष्ठा rt_hi_throughput *pHTInfo = ieee->pHTInfo;

	अगर (!pHTInfo->bRegBW40MHz)
		वापस;

	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		Bandwidth = HT_CHANNEL_WIDTH_20;

	अगर (pHTInfo->bSwBwInProgress) अणु
		pr_info("%s: bSwBwInProgress!!\n", __func__);
		वापस;
	पूर्ण
	अगर (Bandwidth == HT_CHANNEL_WIDTH_20_40) अणु
		अगर (ieee->current_network.channel < 2 &&
		    Offset == HT_EXTCHNL_OFFSET_LOWER)
			Offset = HT_EXTCHNL_OFFSET_NO_EXT;
		अगर (Offset == HT_EXTCHNL_OFFSET_UPPER ||
		    Offset == HT_EXTCHNL_OFFSET_LOWER) अणु
			pHTInfo->bCurBW40MHz = true;
			pHTInfo->CurSTAExtChnlOffset = Offset;
		पूर्ण अन्यथा अणु
			pHTInfo->bCurBW40MHz = false;
			pHTInfo->CurSTAExtChnlOffset = HT_EXTCHNL_OFFSET_NO_EXT;
		पूर्ण
	पूर्ण अन्यथा अणु
		pHTInfo->bCurBW40MHz = false;
		pHTInfo->CurSTAExtChnlOffset = HT_EXTCHNL_OFFSET_NO_EXT;
	पूर्ण

	netdev_dbg(ieee->dev, "%s():pHTInfo->bCurBW40MHz:%x\n", __func__,
		   pHTInfo->bCurBW40MHz);

	pHTInfo->bSwBwInProgress = true;

	HTSetConnectBwModeCallback(ieee);
पूर्ण
