<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * As this function is मुख्यly ported from Winकरोws driver, so leave the name
 * little changed. If any confusion caused, tell me. Created by WB. 2008.05.08
 */
#समावेश "ieee80211.h"

u8 MCS_FILTER_ALL[16] = अणु0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;

u8 MCS_FILTER_1SS[16] = अणु0xff, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00पूर्ण;

u16 MCS_DATA_RATE[2][2][77] = अणु
	अणु	अणु13, 26, 39, 52, 78, 104, 117, 130, 26, 52, 78, 104, 156, 208, 234, 260,
		 39, 78, 117, 234, 312, 351, 390, 52, 104, 156, 208, 312, 416, 468, 520,
		 0, 78, 104, 130, 117, 156, 195, 104, 130, 130, 156, 182, 182, 208, 156, 195,
		 195, 234, 273, 273, 312, 130, 156, 181, 156, 181, 208, 234, 208, 234, 260, 260,
		 286, 195, 234, 273, 234, 273, 312, 351, 312, 351, 390, 390, 429पूर्ण,			// Long GI, 20MHz
		अणु14, 29, 43, 58, 87, 116, 130, 144, 29, 58, 87, 116, 173, 231, 260, 289,
		 43, 87, 130, 173, 260, 347, 390, 433, 58, 116, 173, 231, 347, 462, 520, 578,
		 0, 87, 116, 144, 130, 173, 217, 116, 144, 144, 173, 202, 202, 231, 173, 217,
		 217, 260, 303, 303, 347, 144, 173, 202, 173, 202, 231, 260, 231, 260, 289, 289,
		 318, 217, 260, 303, 260, 303, 347, 390, 347, 390, 433, 433, 477पूर्ण	पूर्ण,		// Short GI, 20MHz
	अणु	अणु27, 54, 81, 108, 162, 216, 243, 270, 54, 108, 162, 216, 324, 432, 486, 540,
		 81, 162, 243, 324, 486, 648, 729, 810, 108, 216, 324, 432, 648, 864, 972, 1080,
		 12, 162, 216, 270, 243, 324, 405, 216, 270, 270, 324, 378, 378, 432, 324, 405,
		 405, 486, 567, 567, 648, 270, 324, 378, 324, 378, 432, 486, 432, 486, 540, 540,
		 594, 405, 486, 567, 486, 567, 648, 729, 648, 729, 810, 810, 891पूर्ण,	// Long GI, 40MHz
		अणु30, 60, 90, 120, 180, 240, 270, 300, 60, 120, 180, 240, 360, 480, 540, 600,
		 90, 180, 270, 360, 540, 720, 810, 900, 120, 240, 360, 480, 720, 960, 1080, 1200,
		 13, 180, 240, 300, 270, 360, 450, 240, 300, 300, 360, 420, 420, 480, 360, 450,
		 450, 540, 630, 630, 720, 300, 360, 420, 360, 420, 480, 540, 480, 540, 600, 600,
		 660, 450, 540, 630, 540, 630, 720, 810, 720, 810, 900, 900, 990पूर्ण	पूर्ण	// Short GI, 40MHz
पूर्ण;

अटल u8 UNKNOWN_BORADCOM[3] = अणु0x00, 0x14, 0xbfपूर्ण;
अटल u8 LINKSYSWRT330_LINKSYSWRT300_BROADCOM[3] = अणु0x00, 0x1a, 0x70पूर्ण;
अटल u8 LINKSYSWRT350_LINKSYSWRT150_BROADCOM[3] = अणु0x00, 0x1d, 0x7eपूर्ण;
अटल u8 NETGEAR834Bv2_BROADCOM[3] = अणु0x00, 0x1b, 0x2fपूर्ण;
अटल u8 BELKINF5D8233V1_RALINK[3] = अणु0x00, 0x17, 0x3fपूर्ण;	//cosa 03202008
अटल u8 BELKINF5D82334V3_RALINK[3] = अणु0x00, 0x1c, 0xdfपूर्ण;
अटल u8 PCI_RALINK[3] = अणु0x00, 0x90, 0xccपूर्ण;
अटल u8 EDIMAX_RALINK[3] = अणु0x00, 0x0e, 0x2eपूर्ण;
अटल u8 AIRLINK_RALINK[3] = अणु0x00, 0x18, 0x02पूर्ण;
//अटल u8 DLINK_ATHEROS[3] = अणु0x00, 0x1c, 0xf0पूर्ण;
अटल u8 CISCO_BROADCOM[3] = अणु0x00, 0x17, 0x94पूर्ण;
/*
 * 2008/04/01 MH For Cisco G mode RX TP We need to change FW duration. Should we
 * put the code in other place??
 * अटल u8 WIFI_CISCO_G_AP[3] = अणु0x00, 0x40, 0x96पूर्ण;
 */
/*
 *function:  This function update शेष settings in pHTInfo काष्ठाure
 *   input:  PRT_HIGH_THROUGHPUT	pHTInfo
 *  output:  none
 *  वापस:  none
 *  notice:  These value need be modअगरied अगर any changes.
 */
व्योम HTUpdateDefaultSetting(काष्ठा ieee80211_device *ieee)
अणु
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	//स्थिर typeof( ((काष्ठा ieee80211_device *)0)->pHTInfo ) *__mptr = &pHTInfo;

	//prपूर्णांकk("pHTinfo:%p, &pHTinfo:%p, mptr:%p,  offsetof:%x\n", pHTInfo, &pHTInfo, __mptr, दुरत्व(काष्ठा ieee80211_device, pHTInfo));
	//prपूर्णांकk("===>ieee:%p,\n", ieee);
	// ShortGI support
	pHTInfo->bRegShortGI20MHz = 1;
	pHTInfo->bRegShortGI40MHz = 1;

	// 40MHz channel support
	pHTInfo->bRegBW40MHz = 1;

	// CCK rate support in 40MHz channel
	अगर (pHTInfo->bRegBW40MHz)
		pHTInfo->bRegSuppCCK = 1;
	अन्यथा
		pHTInfo->bRegSuppCCK = true;

	// AMSDU related
	pHTInfo->nAMSDU_MaxSize = 7935UL;
	pHTInfo->bAMSDU_Support = 0;

	// AMPDU related
	pHTInfo->bAMPDUEnable = 1;
	pHTInfo->AMPDU_Factor = 2; //// 0: 2n13(8K), 1:2n14(16K), 2:2n15(32K), 3:2n16(64k)
	pHTInfo->MPDU_Density = 0;// 0: No restriction, 1: 1/8usec, 2: 1/4usec, 3: 1/2usec, 4: 1usec, 5: 2usec, 6: 4usec, 7:8usec

	// MIMO Power Save
	pHTInfo->SelfMimoPs = 3;// 0: Static Mimo Ps, 1: Dynamic Mimo Ps, 3: No Limitation, 2: Reserved(Set to 3 स्वतःmatically.)
	अगर (pHTInfo->SelfMimoPs == 2)
		pHTInfo->SelfMimoPs = 3;
	// 8190 only. Assign rate operation mode to firmware
	ieee->bTxDisableRateFallBack = 0;
	ieee->bTxUseDriverAssingedRate = 0;

	/*
	 * 8190 only, Realtek proprietary aggregation mode
	 * Set MPDUDensity=2,   1: Set MPDUDensity=2(32k)  क्रम Realtek AP and set MPDUDensity=0(8k) क्रम others
	 */
	pHTInfo->bRegRT2RTAggregation = 1;//0: Set MPDUDensity=2,   1: Set MPDUDensity=2(32k)  क्रम Realtek AP and set MPDUDensity=0(8k) क्रम others

	// For Rx Reorder Control
	pHTInfo->bRegRxReorderEnable = 1;
	pHTInfo->RxReorderWinSize = 64;
	pHTInfo->RxReorderPendingTime = 30;

#अगर_घोषित USB_TX_DRIVER_AGGREGATION_ENABLE
	pHTInfo->UsbTxAggrNum = 4;
#पूर्ण_अगर
#अगर_घोषित USB_RX_AGGREGATION_SUPPORT
	pHTInfo->UsbRxFwAggrEn = 1;
	pHTInfo->UsbRxFwAggrPageNum = 24;
	pHTInfo->UsbRxFwAggrPacketNum = 8;
	pHTInfo->UsbRxFwAggrTimeout = 16; ////usb rx FW aggregation समयout threshold.It's in units of 64us
#पूर्ण_अगर
पूर्ण

/*
 *function:  This function prपूर्णांक out each field on HT capability
 *           IE मुख्यly from (Beacon/ProbeRsp/AssocReq)
 *   input:  u8*	CapIE       //Capability IE to be prपूर्णांकed out
 *	     u8*	TitleString //मुख्यly prपूर्णांक out caller function
 *  output:  none
 *  वापस:  none
 *  notice:  Driver should not prपूर्णांक out this message by शेष.
 */
व्योम HTDebugHTCapability(u8 *CapIE, u8 *TitleString)
अणु
	अटल u8	          EWC11NHTCap[] = अणु0x00, 0x90, 0x4c, 0x33पूर्ण;	// For 11n EWC definition, 2007.07.17, by Emily
	काष्ठा ht_capability_ele *pCapELE;

	अगर (!स_भेद(CapIE, EWC11NHTCap, माप(EWC11NHTCap))) अणु
		//EWC IE
		IEEE80211_DEBUG(IEEE80211_DL_HT, "EWC IE in %s()\n", __func__);
		pCapELE = (काष्ठा ht_capability_ele *)(&CapIE[4]);
	पूर्ण अन्यथा अणु
		pCapELE = (काष्ठा ht_capability_ele *)(&CapIE[0]);
	पूर्ण
	IEEE80211_DEBUG(IEEE80211_DL_HT, "<Log HT Capability>. Called by %s\n", TitleString);

	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tSupported Channel Width = %s\n", (pCapELE->ChlWidth) ? "20MHz" : "20/40MHz");
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tSupport Short GI for 20M = %s\n", (pCapELE->ShortGI20Mhz) ? "YES" : "NO");
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tSupport Short GI for 40M = %s\n", (pCapELE->ShortGI40Mhz) ? "YES" : "NO");
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tSupport TX STBC = %s\n", (pCapELE->TxSTBC) ? "YES" : "NO");
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tMax AMSDU Size = %s\n", (pCapELE->MaxAMSDUSize) ? "3839" : "7935");
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tSupport CCK in 20/40 mode = %s\n", (pCapELE->DssCCk) ? "YES" : "NO");
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tMax AMPDU Factor = %d\n", pCapELE->MaxRxAMPDUFactor);
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tMPDU Density = %d\n", pCapELE->MPDUDensity);
	IEEE80211_DEBUG(IEEE80211_DL_HT,  "\tMCS Rate Set = [%x][%x][%x][%x][%x]\n", pCapELE->MCS[0],\
				pCapELE->MCS[1], pCapELE->MCS[2], pCapELE->MCS[3], pCapELE->MCS[4]);
पूर्ण

/*
 *function:  This function prपूर्णांक out each field on HT Inक्रमmation
 *           IE मुख्यly from (Beacon/ProbeRsp)
 *   input:  u8*	InfoIE       //Capability IE to be prपूर्णांकed out
 *	     u8*	TitleString //मुख्यly prपूर्णांक out caller function
 *  output:  none
 *  वापस:  none
 *  notice:  Driver should not prपूर्णांक out this message by शेष.
 */
व्योम HTDebugHTInfo(u8 *InfoIE, u8 *TitleString)
अणु
	अटल u8	EWC11NHTInfo[] = अणु0x00, 0x90, 0x4c, 0x34पूर्ण;	// For 11n EWC definition, 2007.07.17, by Emily
	PHT_INFORMATION_ELE		pHTInfoEle;

	अगर (!स_भेद(InfoIE, EWC11NHTInfo, माप(EWC11NHTInfo))) अणु
		// Not EWC IE
		IEEE80211_DEBUG(IEEE80211_DL_HT, "EWC IE in %s()\n", __func__);
		pHTInfoEle = (PHT_INFORMATION_ELE)(&InfoIE[4]);
	पूर्ण अन्यथा अणु
		pHTInfoEle = (PHT_INFORMATION_ELE)(&InfoIE[0]);
	पूर्ण

	IEEE80211_DEBUG(IEEE80211_DL_HT, "<Log HT Information Element>. Called by %s\n", TitleString);

	IEEE80211_DEBUG(IEEE80211_DL_HT, "\tPrimary channel = %d\n", pHTInfoEle->ControlChl);
	IEEE80211_DEBUG(IEEE80211_DL_HT, "\tSecondary channel =");
	चयन (pHTInfoEle->ExtChlOffset) अणु
	हाल 0:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "Not Present\n");
		अवरोध;
	हाल 1:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "Upper channel\n");
		अवरोध;
	हाल 2:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "Reserved. Eooro!!!\n");
		अवरोध;
	हाल 3:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "Lower Channel\n");
		अवरोध;
	पूर्ण
	IEEE80211_DEBUG(IEEE80211_DL_HT, "\tRecommended channel width = %s\n", (pHTInfoEle->RecommemdedTxWidth) ? "20Mhz" : "40Mhz");

	IEEE80211_DEBUG(IEEE80211_DL_HT, "\tOperation mode for protection = ");
	चयन (pHTInfoEle->OptMode) अणु
	हाल 0:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "No Protection\n");
		अवरोध;
	हाल 1:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "HT non-member protection mode\n");
		अवरोध;
	हाल 2:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "Suggest to open protection\n");
		अवरोध;
	हाल 3:
		IEEE80211_DEBUG(IEEE80211_DL_HT, "HT mixed mode\n");
		अवरोध;
	पूर्ण

	IEEE80211_DEBUG(IEEE80211_DL_HT, "\tBasic MCS Rate Set = [%x][%x][%x][%x][%x]\n", pHTInfoEle->BasicMSC[0],\
				pHTInfoEle->BasicMSC[1], pHTInfoEle->BasicMSC[2], pHTInfoEle->BasicMSC[3], pHTInfoEle->BasicMSC[4]);
पूर्ण

अटल u16 HTMcsToDataRate(काष्ठा ieee80211_device *ieee, u8 nMcsRate)
अणु
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;

	u8	is40MHz = (pHTInfo->bCurBW40MHz) ? 1 : 0;
	u8	isShortGI = (pHTInfo->bCurBW40MHz) ?
						((pHTInfo->bCurShortGI40MHz) ? 1 : 0) :
						((pHTInfo->bCurShortGI20MHz) ? 1 : 0);
	वापस MCS_DATA_RATE[is40MHz][isShortGI][(nMcsRate & 0x7f)];
पूर्ण

/*
 *function:  This function वापसs current datarate.
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8				nDataRate
 *  output:  none
 *  वापस:  tx rate
 *  notice:  quite unsure about how to use this function //wb
 */
u16  TxCountToDataRate(काष्ठा ieee80211_device *ieee, u8 nDataRate)
अणु
	//PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	u16		CCKOFDMRate[12] = अणु0x02, 0x04, 0x0b, 0x16, 0x0c, 0x12, 0x18, 0x24, 0x30, 0x48, 0x60, 0x6cपूर्ण;
	u8	is40MHz = 0;
	u8	isShortGI = 0;

	अगर (nDataRate < 12) अणु
		वापस CCKOFDMRate[nDataRate];
	पूर्ण अन्यथा अणु
		अगर (nDataRate >= 0x10 && nDataRate <= 0x1f) अणु //अगर(nDataRate > 11 && nDataRate < 28 )
			is40MHz = 0;
			isShortGI = 0;

		      // nDataRate = nDataRate - 12;
		पूर्ण अन्यथा अगर (nDataRate >= 0x20  && nDataRate <= 0x2f) अणु //(27, 44)
			is40MHz = 1;
			isShortGI = 0;

			//nDataRate = nDataRate - 28;
		पूर्ण अन्यथा अगर (nDataRate >= 0x30  && nDataRate <= 0x3f) अणु //(43, 60)
			is40MHz = 0;
			isShortGI = 1;

			//nDataRate = nDataRate - 44;
		पूर्ण अन्यथा अगर (nDataRate >= 0x40  && nDataRate <= 0x4f) अणु //(59, 76)
			is40MHz = 1;
			isShortGI = 1;

			//nDataRate = nDataRate - 60;
		पूर्ण
		वापस MCS_DATA_RATE[is40MHz][isShortGI][nDataRate & 0xf];
	पूर्ण
पूर्ण

bool IsHTHalfNmodeAPs(काष्ठा ieee80211_device *ieee)
अणु
	bool			retValue = false;
	काष्ठा ieee80211_network *net = &ieee->current_network;

	अगर ((स_भेद(net->bssid, BELKINF5D8233V1_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, BELKINF5D82334V3_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, PCI_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, EDIMAX_RALINK, 3) == 0) ||
	    (स_भेद(net->bssid, AIRLINK_RALINK, 3) == 0) ||
	    (net->ralink_cap_exist))
		retValue = true;
	अन्यथा अगर ((स_भेद(net->bssid, UNKNOWN_BORADCOM, 3) == 0) ||
		 (स_भेद(net->bssid, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) == 0) ||
		 (स_भेद(net->bssid, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3) == 0) ||
		 (स_भेद(net->bssid, NETGEAR834Bv2_BROADCOM, 3) == 0) ||
		 (net->broadcom_cap_exist))
		retValue = true;
	अन्यथा अगर (net->bssht.bdRT2RTAggregation)
		retValue = true;
	अन्यथा
		retValue = false;

	वापस retValue;
पूर्ण

/*
 *function:  This function वापसs peer IOT.
 *   input:  काष्ठा ieee80211_device*	ieee
 *  output:  none
 *  वापस:
 *  notice:
 */
अटल व्योम HTIOTPeerDetermine(काष्ठा ieee80211_device *ieee)
अणु
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	काष्ठा ieee80211_network *net = &ieee->current_network;

	अगर (net->bssht.bdRT2RTAggregation)
		pHTInfo->IOTPeer = HT_IOT_PEER_REALTEK;
	अन्यथा अगर (net->broadcom_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	अन्यथा अगर ((स_भेद(net->bssid, UNKNOWN_BORADCOM, 3) == 0) ||
		 (स_भेद(net->bssid, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) == 0) ||
		 (स_भेद(net->bssid, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3) == 0) ||
		 (स_भेद(net->bssid, NETGEAR834Bv2_BROADCOM, 3) == 0))
		pHTInfo->IOTPeer = HT_IOT_PEER_BROADCOM;
	अन्यथा अगर ((स_भेद(net->bssid, BELKINF5D8233V1_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, BELKINF5D82334V3_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, PCI_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, EDIMAX_RALINK, 3) == 0) ||
		 (स_भेद(net->bssid, AIRLINK_RALINK, 3) == 0) ||
		 net->ralink_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_RALINK;
	अन्यथा अगर (net->atheros_cap_exist)
		pHTInfo->IOTPeer = HT_IOT_PEER_ATHEROS;
	अन्यथा अगर (स_भेद(net->bssid, CISCO_BROADCOM, 3) == 0)
		pHTInfo->IOTPeer = HT_IOT_PEER_CISCO;
	अन्यथा
		pHTInfo->IOTPeer = HT_IOT_PEER_UNKNOWN;

	IEEE80211_DEBUG(IEEE80211_DL_IOT, "Joseph debug!! IOTPEER: %x\n", pHTInfo->IOTPeer);
पूर्ण

/*
 *function:  Check whether driver should declare received rate up to MCS13
 *           only since some chipset is not good at receiving MCS14~15 frame
 *           from some AP.
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8 *			PeerMacAddr
 *  output:  none
 *  वापस:  वापस 1 अगर driver should declare MCS13 only(otherwise वापस 0)
 */
अटल u8 HTIOTActIsDisableMCS14(काष्ठा ieee80211_device *ieee, u8 *PeerMacAddr)
अणु
	वापस 0;
पूर्ण

/*
 * Function:	HTIOTActIsDisableMCS15
 *
 * Overview:	Check whether driver should declare capability of receiving
 *              MCS15
 *
 * Input:
 *			PADAPTER		Adapter,
 *
 * Output:		None
 * Return:	true अगर driver should disable MCS15
 * 2008.04.15	Emily
 */
अटल bool HTIOTActIsDisableMCS15(काष्ठा ieee80211_device *ieee)
अणु
	bool retValue = false;

#अगर_घोषित TODO
	// Apply क्रम 819u only
#अगर (HAL_CODE_BASE == RTL8192)

#अगर (DEV_BUS_TYPE == USB_INTERFACE)
	// Alway disable MCS15 by Jerry Chang's request.by Emily, 2008.04.15
	retValue = true;
#या_अगर (DEV_BUS_TYPE == PCI_INTERFACE)
	// Enable MCS15 अगर the peer is Cisco AP. by Emily, 2008.05.12
//	अगर(pBssDesc->bCiscoCapExist)
//		retValue = false;
//	अन्यथा
		retValue = false;
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर
	// Jerry Chang suggest that 8190 1x2 करोes not need to disable MCS15

	वापस retValue;
पूर्ण

/*
 * Function:	HTIOTActIsDisableMCSTwoSpatialStream
 *
 * Overview:	Check whether driver should declare capability of receiving
 *              All 2 ss packets
 *
 * Input:
 *			PADAPTER		Adapter,
 *
 * Output:		None
 * Return:	true अगर driver should disable all two spatial stream packet
 * 2008.04.21	Emily
 */
अटल bool HTIOTActIsDisableMCSTwoSpatialStream(काष्ठा ieee80211_device *ieee,
						 u8 *PeerMacAddr)
अणु
#अगर_घोषित TODO
	// Apply क्रम 819u only
#पूर्ण_अगर
	वापस false;
पूर्ण

/*
 *function:  Check whether driver should disable EDCA turbo mode
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8*			PeerMacAddr
 *  output:  none
 *  वापस:  वापस 1 अगर driver should disable EDCA turbo mode
 *           (otherwise वापस 0)
 */
अटल u8 HTIOTActIsDisableEDCATurbo(काष्ठा ieee80211_device *ieee,
				     u8 *PeerMacAddr)
अणु	/* शेष enable EDCA Turbo mode. */
	वापस false;
पूर्ण

/*
 *function:  Check whether we need to use OFDM to sned MGNT frame क्रम
 *           broadcom AP
 *   input:  काष्ठा ieee80211_network *network   //current network we live
 *  output:  none
 *  वापस:  वापस 1 अगर true
 */
अटल u8 HTIOTActIsMgntUseCCK6M(काष्ठा ieee80211_network *network)
अणु
	u8	retValue = 0;

	// 2008/01/25 MH Judeg अगर we need to use OFDM to sned MGNT frame क्रम broadcom AP.
	// 2008/01/28 MH We must prevent that we select null bssid to link.

	अगर (network->broadcom_cap_exist)
		retValue = 1;

	वापस retValue;
पूर्ण

अटल u8 HTIOTActIsCCDFsync(u8 *PeerMacAddr)
अणु
	u8	retValue = 0;

	अगर ((स_भेद(PeerMacAddr, UNKNOWN_BORADCOM, 3) == 0) ||
	    (स_भेद(PeerMacAddr, LINKSYSWRT330_LINKSYSWRT300_BROADCOM, 3) == 0) ||
	    (स_भेद(PeerMacAddr, LINKSYSWRT350_LINKSYSWRT150_BROADCOM, 3) == 0))
		retValue = 1;

	वापस retValue;
पूर्ण

व्योम HTResetIOTSetting(PRT_HIGH_THROUGHPUT pHTInfo)
अणु
	pHTInfo->IOTAction = 0;
	pHTInfo->IOTPeer = HT_IOT_PEER_UNKNOWN;
पूर्ण

/*
 *function:  Conकाष्ठा Capablility Element in Beacon... अगर HTEnable is turned on
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8*		     posHTCap //poपूर्णांकer to store Capability Ele
 *	     u8*		     len //store length of CE
 *	     u8			     IsEncrypt //whether encrypt, needed further
 *  output:  none
 *  वापस:  none
 *  notice:  posHTCap can't be null and should be initialized beक्रमe.
 */
व्योम HTConकाष्ठाCapabilityElement(काष्ठा ieee80211_device *ieee, u8 *posHTCap, u8 *len, u8 IsEncrypt)
अणु
	PRT_HIGH_THROUGHPUT	pHT = ieee->pHTInfo;
	काष्ठा ht_capability_ele   *pCapELE = शून्य;
	//u8 bIsDeclareMCS13;

	अगर (!posHTCap || !pHT) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				"posHTCap or pHTInfo can't be null in %s\n",
				__func__);
		वापस;
	पूर्ण
	स_रखो(posHTCap, 0, *len);
	अगर (pHT->ePeerHTSpecVer == HT_SPEC_VER_EWC) अणु
		u8	EWC11NHTCap[] = अणु0x00, 0x90, 0x4c, 0x33पूर्ण;	// For 11n EWC definition, 2007.07.17, by Emily

		स_नकल(posHTCap, EWC11NHTCap, माप(EWC11NHTCap));
		pCapELE = (काष्ठा ht_capability_ele *)&posHTCap[4];
	पूर्ण अन्यथा अणु
		pCapELE = (काष्ठा ht_capability_ele *)posHTCap;
	पूर्ण

	//HT capability info
	pCapELE->AdvCoding		= 0; // This feature is not supported now!!
	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		pCapELE->ChlWidth = 0;
	अन्यथा
		pCapELE->ChlWidth = (pHT->bRegBW40MHz ? 1 : 0);

//	pCapELE->ChlWidth		= (pHT->bRegBW40MHz?1:0);
	pCapELE->MimoPwrSave		= pHT->SelfMimoPs;
	pCapELE->GreenField		= 0; // This feature is not supported now!!
	pCapELE->ShortGI20Mhz		= 1; // We can receive Short GI!!
	pCapELE->ShortGI40Mhz		= 1; // We can receive Short GI!!
	//DbgPrपूर्णांक("TX HT cap/info ele BW=%d SG20=%d SG40=%d\n\r",
	//pCapELE->ChlWidth, pCapELE->ShortGI20Mhz, pCapELE->ShortGI40Mhz);
	pCapELE->TxSTBC			= 1;
	pCapELE->RxSTBC			= 0;
	pCapELE->DelayBA		= 0;	// Do not support now!!
	pCapELE->MaxAMSDUSize	        = (MAX_RECEIVE_BUFFER_SIZE >= 7935) ? 1 : 0;
	pCapELE->DssCCk			= ((pHT->bRegBW40MHz) ? (pHT->bRegSuppCCK ? 1 : 0) : 0);
	pCapELE->PSMP			= 0; // Do not support now!!
	pCapELE->LSigTxopProtect	= 0; // Do not support now!!

	/*
	 * MAC HT parameters info
	 * TODO: Nedd to take care of this part
	 */
	IEEE80211_DEBUG(IEEE80211_DL_HT, "TX HT cap/info ele BW=%d MaxAMSDUSize:%d DssCCk:%d\n", pCapELE->ChlWidth, pCapELE->MaxAMSDUSize, pCapELE->DssCCk);

	अगर (IsEncrypt) अणु
		pCapELE->MPDUDensity	= 7; // 8us
		pCapELE->MaxRxAMPDUFactor = 2; // 2 is क्रम 32 K and 3 is 64K
	पूर्ण अन्यथा अणु
		pCapELE->MaxRxAMPDUFactor = 3; // 2 is क्रम 32 K and 3 is 64K
		pCapELE->MPDUDensity	= 0; // no density
	पूर्ण

	//Supported MCS set
	स_नकल(pCapELE->MCS, ieee->Regकरोt11HTOperationalRateSet, 16);
	अगर (pHT->IOTAction & HT_IOT_ACT_DISABLE_MCS15)
		pCapELE->MCS[1] &= 0x7f;

	अगर (pHT->IOTAction & HT_IOT_ACT_DISABLE_MCS14)
		pCapELE->MCS[1] &= 0xbf;

	अगर (pHT->IOTAction & HT_IOT_ACT_DISABLE_ALL_2SS)
		pCapELE->MCS[1] &= 0x00;

	/*
	 * 2008.06.12
	 * For RTL819X, अगर pairwisekey = wep/tkip, ap is ralink, we support only MCS0~7.
	 */
	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev)) अणु
		पूर्णांक i;

		क्रम (i = 1; i < 16; i++)
			pCapELE->MCS[i] = 0;
	पूर्ण

	//Extended HT Capability Info
	स_रखो(&pCapELE->ExtHTCapInfo, 0, 2);

	//TXBF Capabilities
	स_रखो(pCapELE->TxBFCap, 0, 4);

	//Antenna Selection Capabilities
	pCapELE->ASCap = 0;
//add 2 to give space क्रम element ID and len when स्थिरruct frames
	अगर (pHT->ePeerHTSpecVer == HT_SPEC_VER_EWC)
		*len = 30 + 2;
	अन्यथा
		*len = 26 + 2;

//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_HT, posHTCap, *len -2);

	/*
	 * Prपूर्णांक each field in detail. Driver should not prपूर्णांक out this message
	 * by शेष
	 */
//	HTDebugHTCapability(posHTCap, (u8*)"HTConstructCapability()");
पूर्ण

/*
 *function:  Conकाष्ठा Inक्रमmation Element in Beacon... अगर HTEnable is turned on
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8*		     posHTCap //poपूर्णांकer to store Inक्रमmation Ele
 *	     u8*		     len   //store len of
 *	     u8			     IsEncrypt //whether encrypt, needed further
 *  output:  none
 *  वापस:  none
 *  notice:  posHTCap can't be null and be initialized beक्रमe.
 *           Only AP and IBSS sta should करो this
 */
व्योम HTConकाष्ठाInfoElement(काष्ठा ieee80211_device *ieee, u8 *posHTInfo, u8 *len, u8 IsEncrypt)
अणु
	PRT_HIGH_THROUGHPUT	pHT = ieee->pHTInfo;
	PHT_INFORMATION_ELE		pHTInfoEle = (PHT_INFORMATION_ELE)posHTInfo;

	अगर (!posHTInfo || !pHTInfoEle) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				"posHTInfo or pHTInfoEle can't be null in %s\n",
				__func__);
		वापस;
	पूर्ण

	स_रखो(posHTInfo, 0, *len);
	अगर ((ieee->iw_mode == IW_MODE_ADHOC) || (ieee->iw_mode == IW_MODE_MASTER)) अणु //ap mode is not currently supported
		pHTInfoEle->ControlChl			= ieee->current_network.channel;
		pHTInfoEle->ExtChlOffset		= ((!pHT->bRegBW40MHz) ? HT_EXTCHNL_OFFSET_NO_EXT :
											(ieee->current_network.channel <= 6) ?
												HT_EXTCHNL_OFFSET_UPPER : HT_EXTCHNL_OFFSET_LOWER);
		pHTInfoEle->RecommemdedTxWidth	= pHT->bRegBW40MHz;
		pHTInfoEle->RIFS					= 0;
		pHTInfoEle->PSMPAccessOnly		= 0;
		pHTInfoEle->SrvIntGranularity		= 0;
		pHTInfoEle->OptMode				= pHT->CurrentOpMode;
		pHTInfoEle->NonGFDevPresent		= 0;
		pHTInfoEle->DualBeacon			= 0;
		pHTInfoEle->SecondaryBeacon		= 0;
		pHTInfoEle->LSigTxopProtectFull		= 0;
		pHTInfoEle->PcoActive				= 0;
		pHTInfoEle->PcoPhase				= 0;

		स_रखो(pHTInfoEle->BasicMSC, 0, 16);

		*len = 22 + 2; //same above
	पूर्ण अन्यथा अणु
		//STA should not generate High Throughput Inक्रमmation Element
		*len = 0;
	पूर्ण
	//IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_HT, posHTInfo, *len - 2);
	//HTDebugHTInfo(posHTInfo, "HTConstructInforElement");
पूर्ण

/*
 * According to experiment, Realtek AP to STA (based on rtl8190) may achieve
 * best perक्रमmance अगर both STA and AP set limitation of aggregation size to
 * 32K, that is, set AMPDU density to 2 (Ref: IEEE 11n specअगरication).
 * However, अगर Realtek STA associates to other AP, STA should set limitation of
 * aggregation size to 8K, otherwise, perक्रमmance of traffic stream from STA to
 * AP will be much less than the traffic stream from AP to STA अगर both of the
 * stream runs concurrently at the same समय.
 *
 *  Frame Format
 *  Element ID		Length		OUI		Type1		Reserved
 *  1 byte		1 byte		3 bytes		1 byte		1 byte
 *
 *  OUI		= 0x00, 0xe0, 0x4c,
 *  Type	= 0x02
 *  Reserved	= 0x00
 *
 *  2007.8.21 by Emily
 */
/*
 *function:  Conकाष्ठा  Inक्रमmation Element in Beacon... in RT2RT condition
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8*		  posRT2RTAgg //poपूर्णांकer to store Inक्रमmation Ele
 *	     u8*		  len   //store len
 *  output:  none
 *  वापस:  none
 *  notice:
 */
व्योम HTConकाष्ठाRT2RTAggElement(काष्ठा ieee80211_device *ieee, u8 *posRT2RTAgg, u8 *len)
अणु
	अगर (!posRT2RTAgg) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				"posRT2RTAgg can't be null in %s\n",
				__func__);
		वापस;
	पूर्ण
	स_रखो(posRT2RTAgg, 0, *len);
	*posRT2RTAgg++ = 0x00;
	*posRT2RTAgg++ = 0xe0;
	*posRT2RTAgg++ = 0x4c;
	*posRT2RTAgg++ = 0x02;
	*posRT2RTAgg++ = 0x01;
	*posRT2RTAgg = 0x10;//*posRT2RTAgg = 0x02;

	अगर (ieee->bSupportRemoteWakeUp)
		*posRT2RTAgg |= 0x08;//RT_HT_CAP_USE_WOW;

	*len = 6 + 2;
	वापस;
#अगर_घोषित TODO
#अगर (HAL_CODE_BASE == RTL8192 && DEV_BUS_TYPE == USB_INTERFACE)
	/*
	//Emily. If it is required to Ask Realtek AP to send AMPDU during AES mode, enable this
	   section of code.
	अगर(IS_UNDER_11N_AES_MODE(Adapter))
	अणु
		posRT2RTAgg->octet[5] |= RT_HT_CAP_USE_AMPDU;
	पूर्णअन्यथा
	अणु
		posRT2RTAgg->octet[5] &= 0xfb;
	पूर्ण
	*/
#अन्यथा
	// Do Nothing
#पूर्ण_अगर

	posRT2RTAgg->Length = 6;
#पूर्ण_अगर
पूर्ण

/*
 *function:  Pick the right Rate Adaptive table to use
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8*		      pOperateMCS //A poपूर्णांकer to MCS rate biपंचांगap
 *  वापस:  always we वापस true
 *  notice:
 */
अटल u8 HT_PickMCSRate(काष्ठा ieee80211_device *ieee, u8 *pOperateMCS)
अणु
	अगर (!pOperateMCS) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				"pOperateMCS can't be null in %s\n",
				__func__);
		वापस false;
	पूर्ण

	चयन (ieee->mode) अणु
	हाल IEEE_A:
	हाल IEEE_B:
	हाल IEEE_G:
		//legacy rate routine handled at selectedrate

		//no MCS rate
		स_रखो(pOperateMCS, 0, 16);
		अवरोध;

	हाल IEEE_N_24G:	//assume CCK rate ok
	हाल IEEE_N_5G:
		// Legacy part we only use 6, 5.5,2,1 क्रम N_24G and 6 क्रम N_5G.
		// Legacy part shall be handled at SelectRateSet().

		//HT part
		// TODO: may be dअगरferent अगर we have dअगरferent number of antenna
		pOperateMCS[0] &= RATE_ADPT_1SS_MASK;	//support MCS 0~7
		pOperateMCS[1] &= RATE_ADPT_2SS_MASK;
		pOperateMCS[3] &= RATE_ADPT_MCS32_MASK;
		अवरोध;

	//should never reach here
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

/*
 *	Description:
 *		This function will get the highest speed rate in input MCS set.
 *
 *	/param	Adapter			Pionter to Adapter entity
 *			pMCSRateSet		Poपूर्णांकer to MCS rate biपंचांगap
 *			pMCSFilter		Poपूर्णांकer to MCS rate filter
 *
 *	/वापस	Highest MCS rate included in pMCSRateSet and filtered by pMCSFilter.
 *
 */
/*
 *function:  This function will get the highest speed rate in input MCS set.
 *   input:  काष्ठा ieee80211_device*	ieee
 *	     u8*			pMCSRateSet //Poपूर्णांकer to MCS rate biपंचांगap
 *	     u8*			pMCSFilter //Poपूर्णांकer to MCS rate filter
 *  वापस:  Highest MCS rate included in pMCSRateSet and filtered by pMCSFilter
 *  notice:
 */
u8 HTGetHighestMCSRate(काष्ठा ieee80211_device *ieee, u8 *pMCSRateSet, u8 *pMCSFilter)
अणु
	u8		i, j;
	u8		bitMap;
	u8		mcsRate = 0;
	u8		availableMcsRate[16];

	अगर (!pMCSRateSet || !pMCSFilter) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				"pMCSRateSet or pMCSFilter can't be null in %s\n",
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
					अगर (HTMcsToDataRate(ieee, (8 * i + j)) > HTMcsToDataRate(ieee, mcsRate))
						mcsRate = (8 * i + j);
				पूर्ण
				bitMap >>= 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस (mcsRate | 0x80);
पूर्ण

/*
 * 1.Filter our operation rate set with AP's rate set
 * 2.shall reference channel bandwidth, STBC, Antenna number
 * 3.generate rate adative table क्रम firmware
 * David 20060906
 *
 * \pHTSupportedCap: the connected STA's supported rate Capability element
 */
अटल u8 HTFilterMCSRate(काष्ठा ieee80211_device *ieee, u8 *pSupportMCS,
			  u8 *pOperateMCS)
अणु
	u8 i = 0;

	// filter out operational rate set not supported by AP, the length of it is 16
	क्रम (i = 0; i <= 15; i++)
		pOperateMCS[i] = ieee->Regकरोt11HTOperationalRateSet[i] & pSupportMCS[i];

	// TODO: adjust our operational rate set  according to our channel bandwidth, STBC and Antenna number
	/*
	 * TODO: fill suggested rate adaptive rate index and give firmware info
	 * using Tx command packet we also shall suggested the first start rate
	 * set according to our संकेत strength
	 */
	HT_PickMCSRate(ieee, pOperateMCS);

	// For RTL819X, अगर pairwisekey = wep/tkip, we support only MCS0~7.
	अगर (ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))
		pOperateMCS[1] = 0;

	/*
	 * For RTL819X, we support only MCS0~15.
	 * And also, we करो not know how to use MCS32 now.
	 */
	क्रम (i = 2; i <= 15; i++)
		pOperateMCS[i] = 0;

	वापस true;
पूर्ण

व्योम HTOnAssocRsp(काष्ठा ieee80211_device *ieee)
अणु
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	काष्ठा ht_capability_ele       *pPeerHTCap = शून्य;
	PHT_INFORMATION_ELE		pPeerHTInfo = शून्य;
	u16	nMaxAMSDUSize = 0;
	u8	*pMcsFilter = शून्य;

	अटल u8				EWC11NHTCap[] = अणु0x00, 0x90, 0x4c, 0x33पूर्ण;		// For 11n EWC definition, 2007.07.17, by Emily
	अटल u8				EWC11NHTInfo[] = अणु0x00, 0x90, 0x4c, 0x34पूर्ण;	// For 11n EWC definition, 2007.07.17, by Emily

	अगर (!pHTInfo->bCurrentHTSupport) अणु
		IEEE80211_DEBUG(IEEE80211_DL_ERR,
				"<=== %s: HT_DISABLE\n",
				__func__);
		वापस;
	पूर्ण
	IEEE80211_DEBUG(IEEE80211_DL_HT, "===> HTOnAssocRsp_wq(): HT_ENABLE\n");
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, pHTInfo->PeerHTCapBuf, माप(काष्ठा ht_capability_ele));
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA, pHTInfo->PeerHTInfoBuf, माप(HT_INFORMATION_ELE));

//	HTDebugHTCapability(pHTInfo->PeerHTCapBuf,"HTOnAssocRsp_wq");
//	HTDebugHTInfo(pHTInfo->PeerHTInfoBuf,"HTOnAssocRsp_wq");
	//
	अगर (!स_भेद(pHTInfo->PeerHTCapBuf, EWC11NHTCap, माप(EWC11NHTCap)))
		pPeerHTCap = (काष्ठा ht_capability_ele *)(&pHTInfo->PeerHTCapBuf[4]);
	अन्यथा
		pPeerHTCap = (काष्ठा ht_capability_ele *)(pHTInfo->PeerHTCapBuf);

	अगर (!स_भेद(pHTInfo->PeerHTInfoBuf, EWC11NHTInfo, माप(EWC11NHTInfo)))
		pPeerHTInfo = (PHT_INFORMATION_ELE)(&pHTInfo->PeerHTInfoBuf[4]);
	अन्यथा
		pPeerHTInfo = (PHT_INFORMATION_ELE)(pHTInfo->PeerHTInfoBuf);

	////////////////////////////////////////////////////////
	// Configurations:
	////////////////////////////////////////////////////////
	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA | IEEE80211_DL_HT, pPeerHTCap, माप(काष्ठा ht_capability_ele));
//	IEEE80211_DEBUG_DATA(IEEE80211_DL_DATA|IEEE80211_DL_HT, pPeerHTInfo, माप(HT_INFORMATION_ELE));
	// Config Supported Channel Width setting
	//
	HTSetConnectBwMode(ieee, (क्रमागत ht_channel_width)(pPeerHTCap->ChlWidth), (क्रमागत ht_extension_chan_offset)(pPeerHTInfo->ExtChlOffset));

	pHTInfo->bCurTxBW40MHz = (pPeerHTInfo->RecommemdedTxWidth == 1);

	/*
	 * Update लघु GI/ दीर्घ GI setting
	 *
	 * TODO:
	 */
	pHTInfo->bCurShortGI20MHz = pHTInfo->bRegShortGI20MHz &&
				    (pPeerHTCap->ShortGI20Mhz == 1);
	pHTInfo->bCurShortGI40MHz = pHTInfo->bRegShortGI40MHz &&
				   (pPeerHTCap->ShortGI40Mhz == 1);

	/*
	 * Config TX STBC setting
	 *
	 * TODO:
	 */

	/*
	 * Config DSSS/CCK  mode in 40MHz mode
	 *
	 * TODO:
	 */
	pHTInfo->bCurSuppCCK = pHTInfo->bRegSuppCCK &&
			       (pPeerHTCap->DssCCk == 1);

	/*
	 * Config and configure A-MSDU setting
	 */
	pHTInfo->bCurrent_AMSDU_Support = pHTInfo->bAMSDU_Support;

	nMaxAMSDUSize = (pPeerHTCap->MaxAMSDUSize == 0) ? 3839 : 7935;

	अगर (pHTInfo->nAMSDU_MaxSize > nMaxAMSDUSize)
		pHTInfo->nCurrent_AMSDU_MaxSize = nMaxAMSDUSize;
	अन्यथा
		pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;
	/*
	 * Config A-MPDU setting
	 */
	pHTInfo->bCurrentAMPDUEnable = pHTInfo->bAMPDUEnable;

	/*
	 * <1> Decide AMPDU Factor
	 * By Emily
	 */
	अगर (!pHTInfo->bRegRT2RTAggregation) अणु
		// Decide AMPDU Factor according to protocol handshake
		अगर (pHTInfo->AMPDU_Factor > pPeerHTCap->MaxRxAMPDUFactor)
			pHTInfo->CurrentAMPDUFactor = pPeerHTCap->MaxRxAMPDUFactor;
		अन्यथा
			pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;
	पूर्ण अन्यथा अणु
		/*
		 * Set MPDU density to 2 to Realtek AP, and set it to 0 क्रम others
		 * Replace MPDU factor declared in original association response frame क्रमmat. 2007.08.20 by Emily
		 */
		अगर (ieee->current_network.bssht.bdRT2RTAggregation) अणु
			अगर (ieee->pairwise_key_type != KEY_TYPE_NA)
				// Realtek may set 32k in security mode and 64k क्रम others
				pHTInfo->CurrentAMPDUFactor = pPeerHTCap->MaxRxAMPDUFactor;
			अन्यथा
				pHTInfo->CurrentAMPDUFactor = HT_AGG_SIZE_64K;
		पूर्ण अन्यथा अणु
			अगर (pPeerHTCap->MaxRxAMPDUFactor < HT_AGG_SIZE_32K)
				pHTInfo->CurrentAMPDUFactor = pPeerHTCap->MaxRxAMPDUFactor;
			अन्यथा
				pHTInfo->CurrentAMPDUFactor = HT_AGG_SIZE_32K;
		पूर्ण
	पूर्ण

	/*
	 * <2> Set AMPDU Minimum MPDU Start Spacing
	 * 802.11n 3.0 section 9.7d.3
	 */
	अगर (pHTInfo->MPDU_Density > pPeerHTCap->MPDUDensity)
		pHTInfo->CurrentMPDUDensity = pHTInfo->MPDU_Density;
	अन्यथा
		pHTInfo->CurrentMPDUDensity = pPeerHTCap->MPDUDensity;
	अगर (ieee->pairwise_key_type != KEY_TYPE_NA)
		pHTInfo->CurrentMPDUDensity	= 7; // 8us
	// Force TX AMSDU

	// Lanhsin: mark क्रम पंचांगp to aव्योम deauth by ap from  s3
	//अगर(स_भेद(pMgntInfo->Bssid, NETGEAR834Bv2_BROADCOM, 3)==0)
	अगर (0) अणु
		pHTInfo->bCurrentAMPDUEnable = false;
		pHTInfo->ForcedAMSDUMode = HT_AGG_FORCE_ENABLE;
		pHTInfo->ForcedAMSDUMaxSize = 7935;

		pHTInfo->IOTAction |=  HT_IOT_ACT_TX_USE_AMSDU_8K;
	पूर्ण

	// Rx Reorder Setting
	pHTInfo->bCurRxReorderEnable = pHTInfo->bRegRxReorderEnable;

	/*
	 * Filter out unsupported HT rate क्रम this AP
	 * Update RATR table
	 * This is only क्रम 8190 ,8192 or later product which using firmware to
	 * handle rate adaptive mechanism.
	 */

	/*
	 * Handle Ralink AP bad MCS rate set condition. Joseph.
	 * This fix the bug of Ralink AP. This may be हटाओd in the future.
	 */
	अगर (pPeerHTCap->MCS[0] == 0)
		pPeerHTCap->MCS[0] = 0xff;

	HTFilterMCSRate(ieee, pPeerHTCap->MCS, ieee->करोt11HTOperationalRateSet);

	/*
	 * Config MIMO Power Save setting
	 */
	pHTInfo->PeerMimoPs = pPeerHTCap->MimoPwrSave;
	अगर (pHTInfo->PeerMimoPs == MIMO_PS_STATIC)
		pMcsFilter = MCS_FILTER_1SS;
	अन्यथा
		pMcsFilter = MCS_FILTER_ALL;
	//WB add क्रम MCS8 bug
//	pMcsFilter = MCS_FILTER_1SS;
	ieee->HTHighestOperaRate = HTGetHighestMCSRate(ieee, ieee->करोt11HTOperationalRateSet, pMcsFilter);
	ieee->HTCurrentOperaRate = ieee->HTHighestOperaRate;

	/*
	 * Config current operation mode.
	 */
	pHTInfo->CurrentOpMode = pPeerHTInfo->OptMode;
पूर्ण

/*
 *function:  initialize HT info(काष्ठा PRT_HIGH_THROUGHPUT)
 *   input:  काष्ठा ieee80211_device*	ieee
 *  output:  none
 *  वापस:  none
 *  notice: This function is called when
 *                                  *  (1) MPInitialization Phase
 *                                  *  (2) Receiving of Deauthentication from AP
 */
// TODO: Should this funciton be called when receiving of Disassociation?
व्योम HTInitializeHTInfo(काष्ठा ieee80211_device *ieee)
अणु
	PRT_HIGH_THROUGHPUT pHTInfo = ieee->pHTInfo;

	/*
	 * These parameters will be reset when receiving deauthentication packet
	 */
	IEEE80211_DEBUG(IEEE80211_DL_HT, "===========>%s()\n", __func__);
	pHTInfo->bCurrentHTSupport = false;

	// 40MHz channel support
	pHTInfo->bCurBW40MHz = false;
	pHTInfo->bCurTxBW40MHz = false;

	// Short GI support
	pHTInfo->bCurShortGI20MHz = false;
	pHTInfo->bCurShortGI40MHz = false;
	pHTInfo->bForcedShortGI = false;

	/*
	 * CCK rate support
	 * This flag is set to true to support CCK rate by शेष.
	 * It will be affected by "pHTInfo->bRegSuppCCK" and AP capabilities
	 * only when associate to 11N BSS.
	 */
	pHTInfo->bCurSuppCCK = true;

	// AMSDU related
	pHTInfo->bCurrent_AMSDU_Support = false;
	pHTInfo->nCurrent_AMSDU_MaxSize = pHTInfo->nAMSDU_MaxSize;

	// AMPUD related
	pHTInfo->CurrentMPDUDensity = pHTInfo->MPDU_Density;
	pHTInfo->CurrentAMPDUFactor = pHTInfo->AMPDU_Factor;

	// Initialize all of the parameters related to 11n
	स_रखो(&pHTInfo->SelfHTCap, 0, माप(pHTInfo->SelfHTCap));
	स_रखो(&pHTInfo->SelfHTInfo, 0, माप(pHTInfo->SelfHTInfo));
	स_रखो(&pHTInfo->PeerHTCapBuf, 0, माप(pHTInfo->PeerHTCapBuf));
	स_रखो(&pHTInfo->PeerHTInfoBuf, 0, माप(pHTInfo->PeerHTInfoBuf));

	pHTInfo->bSwBwInProgress = false;

	// Set शेष IEEE spec क्रम Draft N
	pHTInfo->ePeerHTSpecVer = HT_SPEC_VER_IEEE;

	// Realtek proprietary aggregation mode
	pHTInfo->bCurrentRT2RTAggregation = false;
	pHTInfo->bCurrentRT2RTLongSlotTime = false;
	pHTInfo->IOTPeer = 0;
	pHTInfo->IOTAction = 0;

	//MCS rate initialized here
	अणु
		u8 *RegHTSuppRateSets = &ieee->RegHTSuppRateSet[0];

		RegHTSuppRateSets[0] = 0xFF;	//support MCS 0~7
		RegHTSuppRateSets[1] = 0xFF;	//support MCS 8~15
		RegHTSuppRateSets[4] = 0x01;	//support MCS 32
	पूर्ण
पूर्ण

/*
 *function:  initialize Bss HT काष्ठाure(काष्ठा PBSS_HT)
 *   input:  PBSS_HT pBssHT //to be initialized
 *  output:  none
 *  वापस:  none
 *  notice: This function is called when initialize network काष्ठाure
 */
व्योम HTInitializeBssDesc(PBSS_HT pBssHT)
अणु
	pBssHT->bdSupportHT = false;
	स_रखो(pBssHT->bdHTCapBuf, 0, माप(pBssHT->bdHTCapBuf));
	pBssHT->bdHTCapLen = 0;
	स_रखो(pBssHT->bdHTInfoBuf, 0, माप(pBssHT->bdHTInfoBuf));
	pBssHT->bdHTInfoLen = 0;

	pBssHT->bdHTSpecVer = HT_SPEC_VER_IEEE;

	pBssHT->bdRT2RTAggregation = false;
	pBssHT->bdRT2RTLongSlotTime = false;
पूर्ण

/*
 *function:  initialize Bss HT काष्ठाure(काष्ठा PBSS_HT)
 *   input:  काष्ठा ieee80211_device	*ieee
 *	     काष्ठा ieee80211_network	*pNetwork //usually current network
 *                                                  we are live in
 *  output:  none
 *  वापस:  none
 *  notice: This function should ONLY be called beक्रमe association
 */
व्योम HTResetSelfAndSavePeerSetting(काष्ठा ieee80211_device *ieee,	काष्ठा ieee80211_network *pNetwork)
अणु
	PRT_HIGH_THROUGHPUT		pHTInfo = ieee->pHTInfo;
//	u16						nMaxAMSDUSize;
//	काष्ठा ht_capability_ele       *pPeerHTCap = (काष्ठा ht_capability_ele *)pNetwork->bssht.bdHTCapBuf;
//	PHT_INFORMATION_ELE		pPeerHTInfo = (PHT_INFORMATION_ELE)pNetwork->bssht.bdHTInfoBuf;
//	u8*	pMcsFilter;
	u8	bIOTAction = 0;

	//
	//  Save Peer Setting beक्रमe Association
	//
	IEEE80211_DEBUG(IEEE80211_DL_HT, "==============>%s()\n", __func__);
	/*unmark bEnableHT flag here is the same reason why unmarked in function ieee80211_sofपंचांगac_new_net. WB 2008.09.10*/
//	अगर( pHTInfo->bEnableHT &&  pNetwork->bssht.bdSupportHT)
	अगर (pNetwork->bssht.bdSupportHT) अणु
		pHTInfo->bCurrentHTSupport = true;
		pHTInfo->ePeerHTSpecVer = pNetwork->bssht.bdHTSpecVer;

		// Save HTCap and HTInfo inक्रमmation Element
		अगर (pNetwork->bssht.bdHTCapLen > 0 &&	pNetwork->bssht.bdHTCapLen <= माप(pHTInfo->PeerHTCapBuf))
			स_नकल(pHTInfo->PeerHTCapBuf, pNetwork->bssht.bdHTCapBuf, pNetwork->bssht.bdHTCapLen);

		अगर (pNetwork->bssht.bdHTInfoLen > 0 && pNetwork->bssht.bdHTInfoLen <= माप(pHTInfo->PeerHTInfoBuf))
			स_नकल(pHTInfo->PeerHTInfoBuf, pNetwork->bssht.bdHTInfoBuf, pNetwork->bssht.bdHTInfoLen);

		// Check whether RT to RT aggregation mode is enabled
		अगर (pHTInfo->bRegRT2RTAggregation) अणु
			pHTInfo->bCurrentRT2RTAggregation = pNetwork->bssht.bdRT2RTAggregation;
			pHTInfo->bCurrentRT2RTLongSlotTime = pNetwork->bssht.bdRT2RTLongSlotTime;
		पूर्ण अन्यथा अणु
			pHTInfo->bCurrentRT2RTAggregation = false;
			pHTInfo->bCurrentRT2RTLongSlotTime = false;
		पूर्ण

		// Determine the IOT Peer Venकरोr.
		HTIOTPeerDetermine(ieee);

		/*
		 * Decide IOT Action
		 * Must be called after the parameter of pHTInfo->bCurrentRT2RTAggregation is decided
		 */
		pHTInfo->IOTAction = 0;
		bIOTAction = HTIOTActIsDisableMCS14(ieee, pNetwork->bssid);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_MCS14;

		bIOTAction = HTIOTActIsDisableMCS15(ieee);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_MCS15;

		bIOTAction = HTIOTActIsDisableMCSTwoSpatialStream(ieee, pNetwork->bssid);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_ALL_2SS;

		bIOTAction = HTIOTActIsDisableEDCATurbo(ieee, pNetwork->bssid);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_DISABLE_EDCA_TURBO;

		bIOTAction = HTIOTActIsMgntUseCCK6M(pNetwork);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_MGNT_USE_CCK_6M;

		bIOTAction = HTIOTActIsCCDFsync(pNetwork->bssid);
		अगर (bIOTAction)
			pHTInfo->IOTAction |= HT_IOT_ACT_CDD_FSYNC;
	पूर्ण अन्यथा अणु
		pHTInfo->bCurrentHTSupport = false;
		pHTInfo->bCurrentRT2RTAggregation = false;
		pHTInfo->bCurrentRT2RTLongSlotTime = false;

		pHTInfo->IOTAction = 0;
	पूर्ण
पूर्ण

व्योम HTUpdateSelfAndPeerSetting(काष्ठा ieee80211_device *ieee,	काष्ठा ieee80211_network *pNetwork)
अणु
	PRT_HIGH_THROUGHPUT	        pHTInfo = ieee->pHTInfo;
//	काष्ठा ht_capability_ele       *pPeerHTCap = (काष्ठा ht_capability_ele *)pNetwork->bssht.bdHTCapBuf;
	PHT_INFORMATION_ELE		pPeerHTInfo = (PHT_INFORMATION_ELE)pNetwork->bssht.bdHTInfoBuf;

	अगर (pHTInfo->bCurrentHTSupport) अणु
		/*
		 * Config current operation mode.
		 */
		अगर (pNetwork->bssht.bdHTInfoLen != 0)
			pHTInfo->CurrentOpMode = pPeerHTInfo->OptMode;

		/*
		 * <TODO: Config according to OBSS non-HT STA present!!>
		 */
	पूर्ण
पूर्ण
EXPORT_SYMBOL(HTUpdateSelfAndPeerSetting);

/*
 *function:  check whether HT control field exists
 *   input:  काष्ठा ieee80211_device	*ieee
 *	     u8*			pFrame //coming skb->data
 *  output:  none
 *  वापस:  वापस true अगर HT control field exists(false otherwise)
 *  notice:
 */
u8 HTCCheck(काष्ठा ieee80211_device *ieee, u8 *pFrame)
अणु
	अगर (ieee->pHTInfo->bCurrentHTSupport) अणु
		अगर ((IsQoSDataFrame(pFrame) && Frame_Order(pFrame)) == 1) अणु
			IEEE80211_DEBUG(IEEE80211_DL_HT, "HT CONTROL FILED EXIST!!\n");
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम HTSetConnectBwModeCallback(काष्ठा ieee80211_device *ieee)
अणु
	PRT_HIGH_THROUGHPUT pHTInfo = ieee->pHTInfo;

	IEEE80211_DEBUG(IEEE80211_DL_HT, "======>%s()\n", __func__);

	अगर (pHTInfo->bCurBW40MHz) अणु
		अगर (pHTInfo->CurSTAExtChnlOffset == HT_EXTCHNL_OFFSET_UPPER)
			ieee->set_chan(ieee->dev, ieee->current_network.channel + 2);
		अन्यथा अगर (pHTInfo->CurSTAExtChnlOffset == HT_EXTCHNL_OFFSET_LOWER)
			ieee->set_chan(ieee->dev, ieee->current_network.channel - 2);
		अन्यथा
			ieee->set_chan(ieee->dev, ieee->current_network.channel);

		ieee->SetBWModeHandler(ieee->dev, HT_CHANNEL_WIDTH_20_40, pHTInfo->CurSTAExtChnlOffset);
	पूर्ण अन्यथा अणु
		ieee->set_chan(ieee->dev, ieee->current_network.channel);
		ieee->SetBWModeHandler(ieee->dev, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
	पूर्ण

	pHTInfo->bSwBwInProgress = false;
पूर्ण

/*
 * This function set bandwidth mode in protocol layer.
 */
व्योम HTSetConnectBwMode(काष्ठा ieee80211_device *ieee, क्रमागत ht_channel_width Bandwidth, क्रमागत ht_extension_chan_offset Offset)
अणु
	PRT_HIGH_THROUGHPUT pHTInfo = ieee->pHTInfo;
//	u32 flags = 0;

	अगर (!pHTInfo->bRegBW40MHz)
		वापस;

	// To reduce dummy operation
//	अगर((pHTInfo->bCurBW40MHz==false && Bandwidth==HT_CHANNEL_WIDTH_20) ||
//	   (pHTInfo->bCurBW40MHz==true && Bandwidth==HT_CHANNEL_WIDTH_20_40 && Offset==pHTInfo->CurSTAExtChnlOffset))
//		वापस;

//	spin_lock_irqsave(&(ieee->bw_spinlock), flags);
	अगर (pHTInfo->bSwBwInProgress) अणु
//		spin_unlock_irqrestore(&(ieee->bw_spinlock), flags);
		वापस;
	पूर्ण
	//अगर in half N mode, set to 20M bandwidth please 09.08.2008 WB.
	अगर (Bandwidth == HT_CHANNEL_WIDTH_20_40 && (!ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev))) अणु
			// Handle Illegal extension channel offset!!
		अगर (ieee->current_network.channel < 2 && Offset == HT_EXTCHNL_OFFSET_LOWER)
			Offset = HT_EXTCHNL_OFFSET_NO_EXT;
		अगर (Offset == HT_EXTCHNL_OFFSET_UPPER || Offset == HT_EXTCHNL_OFFSET_LOWER) अणु
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

	pHTInfo->bSwBwInProgress = true;

	/*
	 * TODO: 2007.7.13 by Emily Wait 2000ms  in order to guarantee that
	 * चयनing bandwidth is executed after scan is finished. It is a
	 * temporal solution because software should ganrantee the last
	 * operation of चयनing bandwidth is executed properlly.
	 */
	HTSetConnectBwModeCallback(ieee);

//	spin_unlock_irqrestore(&(ieee->bw_spinlock), flags);
पूर्ण
