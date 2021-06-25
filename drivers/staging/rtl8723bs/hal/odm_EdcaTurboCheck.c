<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "odm_precomp.h"

अटल u32 edca_setting_DL_GMode[HT_IOT_PEER_MAX] = अणु
/*UNKNOWN, REALTEK_90, ALTEK_92SE	BROADCOM, LINK	ATHEROS,
 *CISCO, MERU, MARVELL, 92U_AP, SELF_AP
 */
	0x4322, 0xa44f, 0x5e4322, 0xa42b, 0x5e4322, 0x4322,
	0xa42b, 0x5ea42b, 0xa44f, 0x5e4322, 0x5ea42b
पूर्ण;

अटल u32 edca_setting_UL[HT_IOT_PEER_MAX] = अणु
/*UNKNOWN, REALTEK_90, REALTEK_92SE, BROADCOM, RALINK, ATHEROS,
 *CISCO, MERU, MARVELL, 92U_AP, SELF_AP(DownLink/Tx)
 */
	0x5e4322, 0xa44f, 0x5e4322, 0x5ea32b, 0x5ea422,	0x5ea322,
	0x3ea430, 0x5ea42b, 0x5ea44f, 0x5e4322, 0x5e4322पूर्ण;

अटल u32 edca_setting_DL[HT_IOT_PEER_MAX] = अणु
/*UNKNOWN, REALTEK_90, REALTEK_92SE, BROADCOM, RALINK, ATHEROS,
 *CISCO, MERU, MARVELL, 92U_AP, SELF_AP(UpLink/Rx)
 */
	0xa44f, 0x5ea44f, 0x5e4322, 0x5ea42b, 0xa44f, 0xa630,
	0x5ea630, 0x5ea42b, 0xa44f, 0xa42b, 0xa42bपूर्ण;

व्योम ODM_EdcaTurboInit(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;

	pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
	pDM_Odm->DM_EDCA_Table.bIsCurRDLState = false;
	Adapter->recvpriv.bIsAnyNonBEPkts = false;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original VO PARAM: 0x%x\n",
		      rtw_पढ़ो32(pDM_Odm->Adapter, ODM_EDCA_VO_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original VI PARAM: 0x%x\n",
		      rtw_पढ़ो32(pDM_Odm->Adapter, ODM_EDCA_VI_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original BE PARAM: 0x%x\n",
		      rtw_पढ़ो32(pDM_Odm->Adapter, ODM_EDCA_BE_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original BK PARAM: 0x%x\n",
		      rtw_पढ़ो32(pDM_Odm->Adapter, ODM_EDCA_BK_PARAM)));
पूर्ण	/*  ODM_InitEdcaTurbo */

व्योम odm_EdcaTurboCheck(व्योम *pDM_VOID)
अणु
	/*  In HW पूर्णांकegration first stage, we provide 4 dअगरferent handles to
	 *  operate at the same समय. In stage2/3, we need to prove universal
	 *  पूर्णांकerface and merge all HW dynamic mechanism.
	 */
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("odm_EdcaTurboCheck ========================>\n"));

	अगर (!(pDM_Odm->SupportAbility & ODM_MAC_EDCA_TURBO))
		वापस;

	odm_EdcaTurboCheckCE(pDM_Odm);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("<========================odm_EdcaTurboCheck\n"));
पूर्ण	/*  odm_CheckEdcaTurbo */

व्योम odm_EdcaTurboCheckCE(व्योम *pDM_VOID)
अणु
	काष्ठा dm_odm_t *pDM_Odm = (काष्ठा dm_odm_t *)pDM_VOID;
	काष्ठा adapter *Adapter = pDM_Odm->Adapter;
	काष्ठा dvobj_priv *pdvobjpriv = adapter_to_dvobj(Adapter);
	काष्ठा recv_priv *precvpriv = &(Adapter->recvpriv);
	काष्ठा registry_priv *pregpriv = &Adapter->registrypriv;
	काष्ठा mlme_ext_priv *pmlmeext = &(Adapter->mlmeextpriv);
	काष्ठा mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u32 EDCA_BE_UL = 0x5ea42b;
	u32 EDCA_BE_DL = 0x5ea42b;
	u32 iot_peer = 0;
	u8 wirelessmode = 0xFF;		/* invalid value */
	u32 trafficIndex;
	u32 edca_param;
	u64	cur_tx_bytes = 0;
	u64	cur_rx_bytes = 0;
	u8 bbtchange = false;
	u8 biasonrx = false;
	काष्ठा hal_com_data	*pHalData = GET_HAL_DATA(Adapter);

	अगर (!pDM_Odm->bLinked) अणु
		precvpriv->bIsAnyNonBEPkts = false;
		वापस;
	पूर्ण

	अगर (pregpriv->wअगरi_spec == 1) अणु
		precvpriv->bIsAnyNonBEPkts = false;
		वापस;
	पूर्ण

	अगर (pDM_Odm->pwirelessmode)
		wirelessmode = *(pDM_Odm->pwirelessmode);

	iot_peer = pmlmeinfo->assoc_AP_venकरोr;

	अगर (iot_peer >=  HT_IOT_PEER_MAX) अणु
		precvpriv->bIsAnyNonBEPkts = false;
		वापस;
	पूर्ण

	/*  Check अगर the status needs to be changed. */
	अगर ((bbtchange) || (!precvpriv->bIsAnyNonBEPkts)) अणु
		cur_tx_bytes = pdvobjpriv->traffic_stat.cur_tx_bytes;
		cur_rx_bytes = pdvobjpriv->traffic_stat.cur_rx_bytes;

		/* traffic, TX or RX */
		अगर (biasonrx) अणु
			अगर (cur_tx_bytes > (cur_rx_bytes << 2)) अणु
				/*  Uplink TP is present. */
				trafficIndex = UP_LINK;
			पूर्ण अन्यथा अणु /*  Balance TP is present. */
				trafficIndex = DOWN_LINK;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (cur_rx_bytes > (cur_tx_bytes << 2)) अणु
				/*  Downlink TP is present. */
				trafficIndex = DOWN_LINK;
			पूर्ण अन्यथा अणु /*  Balance TP is present. */
				trafficIndex = UP_LINK;
			पूर्ण
		पूर्ण

		/* 92D txop can't be set to 0x3e क्रम cisco1250 */
		अगर ((iot_peer == HT_IOT_PEER_CISCO) &&
		    (wirelessmode == ODM_WM_N24G)) अणु
			EDCA_BE_DL = edca_setting_DL[iot_peer];
			EDCA_BE_UL = edca_setting_UL[iot_peer];
		पूर्ण अन्यथा अगर ((iot_peer == HT_IOT_PEER_CISCO) &&
			   ((wirelessmode == ODM_WM_G) ||
			    (wirelessmode == (ODM_WM_B | ODM_WM_G)) ||
			    (wirelessmode == ODM_WM_A) ||
			    (wirelessmode == ODM_WM_B))) अणु
			EDCA_BE_DL = edca_setting_DL_GMode[iot_peer];
		पूर्ण अन्यथा अगर ((iot_peer == HT_IOT_PEER_AIRGO) &&
			   ((wirelessmode == ODM_WM_G) ||
			    (wirelessmode == ODM_WM_A))) अणु
			EDCA_BE_DL = 0xa630;
		पूर्ण अन्यथा अगर (iot_peer == HT_IOT_PEER_MARVELL) अणु
			EDCA_BE_DL = edca_setting_DL[iot_peer];
			EDCA_BE_UL = edca_setting_UL[iot_peer];
		पूर्ण अन्यथा अगर (iot_peer == HT_IOT_PEER_ATHEROS) अणु
			/*  Set DL EDCA क्रम Atheros peer to 0x3ea42b. */
			EDCA_BE_DL = edca_setting_DL[iot_peer];
		पूर्ण

		अगर (trafficIndex == DOWN_LINK)
			edca_param = EDCA_BE_DL;
		अन्यथा
			edca_param = EDCA_BE_UL;

		rtw_ग_लिखो32(Adapter, REG_EDCA_BE_PARAM, edca_param);

		pDM_Odm->DM_EDCA_Table.prv_traffic_idx = trafficIndex;

		pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = true;
	पूर्ण अन्यथा अणु
		/*  Turn Off EDCA turbo here. */
		/*  Restore original EDCA according to the declaration of AP. */
		 अगर (pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA) अणु
			rtw_ग_लिखो32(Adapter, REG_EDCA_BE_PARAM, pHalData->AcParam_BE);
			pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
		पूर्ण
	पूर्ण
पूर्ण
