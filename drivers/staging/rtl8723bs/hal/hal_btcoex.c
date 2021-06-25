<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा __HAL_BTCOEX_C__

#समावेश <hal_data.h>
#समावेश <rtw_debug.h>
#समावेश <hal_btcoex.h>
#समावेश <Mp_Precomp.h>

/* 		Global variables */

काष्ठा btc_coexist GLBtCoexist;
अटल u8 GLBtcWiFiInScanState;
अटल u8 GLBtcWiFiInIQKState;

u32 GLBtcDbgType[BTC_MSG_MAX];
अटल u8 GLBtcDbgBuf[BT_TMP_BUF_SIZE];

काष्ठा btcdbginfo अणु /* _btcoexdbginfo */
	u8 *info;
	u32 size; /*  buffer total size */
	u32 len; /*  now used length */
पूर्ण;

अटल काष्ठा btcdbginfo GLBtcDbgInfo;

#घोषणा	BT_Operation(Adapter)						false

अटल व्योम DBG_BT_INFO_INIT(काष्ठा btcdbginfo *pinfo, u8 *pbuf, u32 size)
अणु
	अगर (!pinfo)
		वापस;

	स_रखो(pinfo, 0, माप(काष्ठा btcdbginfo));

	अगर (pbuf && size) अणु
		pinfo->info = pbuf;
		pinfo->size = size;
	पूर्ण
पूर्ण

व्योम DBG_BT_INFO(u8 *dbgmsg)
अणु
	काष्ठा btcdbginfo *pinfo;
	u32 msglen;
	u8 *pbuf;


	pinfo = &GLBtcDbgInfo;

	अगर (!pinfo->info)
		वापस;

	msglen = म_माप(dbgmsg);
	अगर (pinfo->len + msglen > pinfo->size)
		वापस;

	pbuf = pinfo->info + pinfo->len;
	स_नकल(pbuf, dbgmsg, msglen);
	pinfo->len += msglen;
पूर्ण

/*  */
/* 		Debug related function */
/*  */
अटल u8 halbtcoutsrc_IsBtCoexistAvailable(काष्ठा btc_coexist *pBtCoexist)
अणु
	अगर (!pBtCoexist->bBinded || !pBtCoexist->Adapter)
		वापस false;

	वापस true;
पूर्ण

अटल व्योम halbtcoutsrc_DbgInit(व्योम)
अणु
	u8 i;

	क्रम (i = 0; i < BTC_MSG_MAX; i++)
		GLBtcDbgType[i] = 0;

	GLBtcDbgType[BTC_MSG_INTERFACE]			=	\
/* 			INTF_INIT								| */
/* 			INTF_NOTIFY							| */
			0;

	GLBtcDbgType[BTC_MSG_ALGORITHM]			=	\
/* 			ALGO_BT_RSSI_STATE					| */
/* 			ALGO_WIFI_RSSI_STATE					| */
/* 			ALGO_BT_MONITOR						| */
/* 			ALGO_TRACE							| */
/* 			ALGO_TRACE_FW						| */
/* 			ALGO_TRACE_FW_DETAIL				| */
/* 			ALGO_TRACE_FW_EXEC					| */
/* 			ALGO_TRACE_SW						| */
/* 			ALGO_TRACE_SW_DETAIL				| */
/* 			ALGO_TRACE_SW_EXEC					| */
			0;
पूर्ण

अटल व्योम halbtcoutsrc_LeaveLps(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा adapter *padapter;


	padapter = pBtCoexist->Adapter;

	pBtCoexist->btInfo.bBtCtrlLps = true;
	pBtCoexist->btInfo.bBtLpsOn = false;

	rtw_btcoex_LPS_Leave(padapter);
पूर्ण

अटल व्योम halbtcoutsrc_EnterLps(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा adapter *padapter;


	padapter = pBtCoexist->Adapter;

	pBtCoexist->btInfo.bBtCtrlLps = true;
	pBtCoexist->btInfo.bBtLpsOn = true;

	rtw_btcoex_LPS_Enter(padapter);
पूर्ण

अटल व्योम halbtcoutsrc_NormalLps(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा adapter *padapter;


	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Normal LPS behavior!!!\n"));

	padapter = pBtCoexist->Adapter;

	अगर (pBtCoexist->btInfo.bBtCtrlLps) अणु
		pBtCoexist->btInfo.bBtLpsOn = false;
		rtw_btcoex_LPS_Leave(padapter);
		pBtCoexist->btInfo.bBtCtrlLps = false;

		/*  recover the LPS state to the original */
	पूर्ण
पूर्ण

/*
 *  Constraपूर्णांक:
 *   1. this function will request pwrctrl->lock
 */
अटल व्योम halbtcoutsrc_LeaveLowPower(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा adapter *padapter;
	s32 पढ़ोy;
	अचिन्हित दीर्घ sसमय;
	अचिन्हित दीर्घ uसमय;
	u32 समयout; /*  unit: ms */


	padapter = pBtCoexist->Adapter;
	पढ़ोy = _FAIL;
#अगर_घोषित LPS_RPWM_WAIT_MS
	समयout = LPS_RPWM_WAIT_MS;
#अन्यथा /*  !LPS_RPWM_WAIT_MS */
	समयout = 30;
#पूर्ण_अगर /*  !LPS_RPWM_WAIT_MS */

	sसमय = jअगरfies;
	करो अणु
		पढ़ोy = rtw_रेजिस्टर_task_alive(padapter, BTCOEX_ALIVE);
		अगर (_SUCCESS == पढ़ोy)
			अवरोध;

		uसमय = jअगरfies_to_msecs(jअगरfies - sसमय);
		अगर (uसमय > समयout)
			अवरोध;

		msleep(1);
	पूर्ण जबतक (1);
पूर्ण

/*
 *  Constraपूर्णांक:
 *   1. this function will request pwrctrl->lock
 */
अटल व्योम halbtcoutsrc_NormalLowPower(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा adapter *padapter;


	padapter = pBtCoexist->Adapter;
	rtw_unरेजिस्टर_task_alive(padapter, BTCOEX_ALIVE);
पूर्ण

अटल व्योम halbtcoutsrc_DisableLowPower(काष्ठा btc_coexist *pBtCoexist, u8 bLowPwrDisable)
अणु
	pBtCoexist->btInfo.bBtDisableLowPwr = bLowPwrDisable;
	अगर (bLowPwrDisable)
		halbtcoutsrc_LeaveLowPower(pBtCoexist);		/*  leave 32k low घातer. */
	अन्यथा
		halbtcoutsrc_NormalLowPower(pBtCoexist);	/*  original 32k low घातer behavior. */
पूर्ण

अटल व्योम halbtcoutsrc_AggregationCheck(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा adapter *padapter;
	bool bNeedToAct;


	padapter = pBtCoexist->Adapter;
	bNeedToAct = false;

	अगर (pBtCoexist->btInfo.bRejectAggPkt) अणु
		rtw_btcoex_RejectApAggregatedPacket(padapter, true);
	पूर्ण अन्यथा अणु
		अगर (pBtCoexist->btInfo.bPreBtCtrlAggBufSize !=
			pBtCoexist->btInfo.bBtCtrlAggBufSize) अणु
			bNeedToAct = true;
			pBtCoexist->btInfo.bPreBtCtrlAggBufSize = pBtCoexist->btInfo.bBtCtrlAggBufSize;
		पूर्ण

		अगर (pBtCoexist->btInfo.bBtCtrlAggBufSize) अणु
			अगर (pBtCoexist->btInfo.preAggBufSize !=
				pBtCoexist->btInfo.aggBufSize)अणु
				bNeedToAct = true;
			पूर्ण
			pBtCoexist->btInfo.preAggBufSize = pBtCoexist->btInfo.aggBufSize;
		पूर्ण

		अगर (bNeedToAct) अणु
			rtw_btcoex_RejectApAggregatedPacket(padapter, true);
			rtw_btcoex_RejectApAggregatedPacket(padapter, false);
		पूर्ण
	पूर्ण
पूर्ण

अटल u8 halbtcoutsrc_IsWअगरiBusy(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv;


	pmlmepriv = &padapter->mlmepriv;

	अगर (check_fwstate(pmlmepriv, WIFI_ASOC_STATE) == true) अणु
		अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true)
			वापस true;
		अगर (pmlmepriv->LinkDetectInfo.bBusyTraffic)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल u32 _halbtcoutsrc_GetWअगरiLinkStatus(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_priv *pmlmepriv;
	u8 bp2p;
	u32 portConnectedStatus;


	pmlmepriv = &padapter->mlmepriv;
	bp2p = false;
	portConnectedStatus = 0;

	अगर (check_fwstate(pmlmepriv, WIFI_ASOC_STATE) == true) अणु
		अगर (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) अणु
			अगर (bp2p)
				portConnectedStatus |= WIFI_P2P_GO_CONNECTED;
			अन्यथा
				portConnectedStatus |= WIFI_AP_CONNECTED;
		पूर्ण अन्यथा अणु
			अगर (bp2p)
				portConnectedStatus |= WIFI_P2P_GC_CONNECTED;
			अन्यथा
				portConnectedStatus |= WIFI_STA_CONNECTED;
		पूर्ण
	पूर्ण

	वापस portConnectedStatus;
पूर्ण

अटल u32 halbtcoutsrc_GetWअगरiLinkStatus(काष्ठा btc_coexist *pBtCoexist)
अणु
	/*  */
	/*  वापस value: */
	/*  [31:16]=> connected port number */
	/*  [15:0]=> port connected bit define */
	/*  */

	काष्ठा adapter *padapter;
	u32 retVal;
	u32 portConnectedStatus, numOfConnectedPort;


	padapter = pBtCoexist->Adapter;
	portConnectedStatus = 0;
	numOfConnectedPort = 0;

	retVal = _halbtcoutsrc_GetWअगरiLinkStatus(padapter);
	अगर (retVal) अणु
		portConnectedStatus |= retVal;
		numOfConnectedPort++;
	पूर्ण

	retVal = (numOfConnectedPort << 16) | portConnectedStatus;

	वापस retVal;
पूर्ण

अटल u32 halbtcoutsrc_GetBtPatchVer(काष्ठा btc_coexist *pBtCoexist)
अणु
	वापस pBtCoexist->btInfo.btRealFwVer;
पूर्ण

अटल s32 halbtcoutsrc_GetWअगरiRssi(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData = GET_HAL_DATA(padapter);

	वापस pHalData->dmpriv.EntryMinUndecoratedSmoothedPWDB;
पूर्ण

अटल u8 halbtcoutsrc_GetWअगरiScanAPNum(काष्ठा adapter *padapter)
अणु
	काष्ठा mlme_ext_priv *pmlmeext;
	अटल u8 scan_AP_num;

	pmlmeext = &padapter->mlmeextpriv;

	अगर (!GLBtcWiFiInScanState) अणु
		अगर (pmlmeext->sitesurvey_res.bss_cnt > 0xFF)
			scan_AP_num = 0xFF;
		अन्यथा
			scan_AP_num = (u8)pmlmeext->sitesurvey_res.bss_cnt;
	पूर्ण

	वापस scan_AP_num;
पूर्ण

अटल u8 halbtcoutsrc_Get(व्योम *pBtcContext, u8 getType, व्योम *pOutBuf)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;
	काष्ठा hal_com_data *pHalData;
	काष्ठा mlme_ext_priv *mlmeext;
	u8 *pu8;
	s32 *pS4Tmp;
	u32 *pU4Tmp;
	u8 ret;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस false;

	padapter = pBtCoexist->Adapter;
	pHalData = GET_HAL_DATA(padapter);
	mlmeext = &padapter->mlmeextpriv;
	pu8 = pOutBuf;
	pS4Tmp = pOutBuf;
	pU4Tmp = pOutBuf;
	ret = true;

	चयन (getType) अणु
	हाल BTC_GET_BL_HS_OPERATION:
		*pu8 = false;
		ret = false;
		अवरोध;

	हाल BTC_GET_BL_HS_CONNECTING:
		*pu8 = false;
		ret = false;
		अवरोध;

	हाल BTC_GET_BL_WIFI_CONNECTED:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_ASOC_STATE);
		अवरोध;

	हाल BTC_GET_BL_WIFI_BUSY:
		*pu8 = halbtcoutsrc_IsWअगरiBusy(padapter);
		अवरोध;

	हाल BTC_GET_BL_WIFI_SCAN:
		/* Use the value of the new variable GLBtcWiFiInScanState to judge whether WiFi is in scan state or not, since the originally used flag
			WIFI_SITE_MONITOR in fwstate may not be cleared in समय */
		*pu8 = GLBtcWiFiInScanState;
		अवरोध;

	हाल BTC_GET_BL_WIFI_LINK:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_UNDER_LINKING);
		अवरोध;

	हाल BTC_GET_BL_WIFI_ROAM:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_UNDER_LINKING);
		अवरोध;

	हाल BTC_GET_BL_WIFI_4_WAY_PROGRESS:
		*pu8 = false;
		अवरोध;

	हाल BTC_GET_BL_WIFI_UNDER_5G:
		*pu8 = pHalData->CurrentBandType == 1;
		अवरोध;

	हाल BTC_GET_BL_WIFI_AP_MODE_ENABLE:
		*pu8 = check_fwstate(&padapter->mlmepriv, WIFI_AP_STATE);
		अवरोध;

	हाल BTC_GET_BL_WIFI_ENABLE_ENCRYPTION:
		*pu8 = padapter->securitypriv.करोt11PrivacyAlgrthm != 0;
		अवरोध;

	हाल BTC_GET_BL_WIFI_UNDER_B_MODE:
		अगर (mlmeext->cur_wireless_mode == WIRELESS_11B)
			*pu8 = true;
		अन्यथा
			*pu8 = false;
		अवरोध;

	हाल BTC_GET_BL_WIFI_IS_IN_MP_MODE:
		*pu8 = false;
		अवरोध;

	हाल BTC_GET_BL_EXT_SWITCH:
		*pu8 = false;
		अवरोध;

	हाल BTC_GET_S4_WIFI_RSSI:
		*pS4Tmp = halbtcoutsrc_GetWअगरiRssi(padapter);
		अवरोध;

	हाल BTC_GET_S4_HS_RSSI:
		*pS4Tmp = 0;
		ret = false;
		अवरोध;

	हाल BTC_GET_U4_WIFI_BW:
		अगर (IsLegacyOnly(mlmeext->cur_wireless_mode))
			*pU4Tmp = BTC_WIFI_BW_LEGACY;
		अन्यथा अगर (pHalData->CurrentChannelBW == CHANNEL_WIDTH_20)
			*pU4Tmp = BTC_WIFI_BW_HT20;
		अन्यथा
			*pU4Tmp = BTC_WIFI_BW_HT40;
		अवरोध;

	हाल BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION:
		अणु
			काष्ठा rt_link_detect_t *plinkinfo;
			plinkinfo = &padapter->mlmepriv.LinkDetectInfo;

			अगर (plinkinfo->NumTxOkInPeriod > plinkinfo->NumRxOkInPeriod)
				*pU4Tmp = BTC_WIFI_TRAFFIC_TX;
			अन्यथा
				*pU4Tmp = BTC_WIFI_TRAFFIC_RX;
		पूर्ण
		अवरोध;

	हाल BTC_GET_U4_WIFI_FW_VER:
		*pU4Tmp = pHalData->FirmwareVersion << 16;
		*pU4Tmp |= pHalData->FirmwareSubVersion;
		अवरोध;

	हाल BTC_GET_U4_WIFI_LINK_STATUS:
		*pU4Tmp = halbtcoutsrc_GetWअगरiLinkStatus(pBtCoexist);
		अवरोध;

	हाल BTC_GET_U4_BT_PATCH_VER:
		*pU4Tmp = halbtcoutsrc_GetBtPatchVer(pBtCoexist);
		अवरोध;

	हाल BTC_GET_U1_WIFI_DOT11_CHNL:
		*pu8 = padapter->mlmeextpriv.cur_channel;
		अवरोध;

	हाल BTC_GET_U1_WIFI_CENTRAL_CHNL:
		*pu8 = pHalData->CurrentChannel;
		अवरोध;

	हाल BTC_GET_U1_WIFI_HS_CHNL:
		*pu8 = 0;
		ret = false;
		अवरोध;

	हाल BTC_GET_U1_MAC_PHY_MODE:
		*pu8 = BTC_SMSP;
/* 			*pU1Tmp = BTC_DMSP; */
/* 			*pU1Tmp = BTC_DMDP; */
/* 			*pU1Tmp = BTC_MP_UNKNOWN; */
		अवरोध;

	हाल BTC_GET_U1_AP_NUM:
		*pu8 = halbtcoutsrc_GetWअगरiScanAPNum(padapter);
		अवरोध;

	/* 1Ant =========== */
	हाल BTC_GET_U1_LPS_MODE:
		*pu8 = padapter->dvobj->pwrctl_priv.pwr_mode;
		अवरोध;

	शेष:
		ret = false;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u8 halbtcoutsrc_Set(व्योम *pBtcContext, u8 setType, व्योम *pInBuf)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;
	u8 *pu8;
	u32 *pU4Tmp;
	u8 ret;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;
	pu8 = pInBuf;
	pU4Tmp = pInBuf;
	ret = true;

	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस false;

	चयन (setType) अणु
	/*  set some u8 type variables. */
	हाल BTC_SET_BL_BT_DISABLE:
		pBtCoexist->btInfo.bBtDisabled = *pu8;
		अवरोध;

	हाल BTC_SET_BL_BT_TRAFFIC_BUSY:
		pBtCoexist->btInfo.bBtBusy = *pu8;
		अवरोध;

	हाल BTC_SET_BL_BT_LIMITED_DIG:
		pBtCoexist->btInfo.bLimitedDig = *pu8;
		अवरोध;

	हाल BTC_SET_BL_FORCE_TO_ROAM:
		pBtCoexist->btInfo.bForceToRoam = *pu8;
		अवरोध;

	हाल BTC_SET_BL_TO_REJ_AP_AGG_PKT:
		pBtCoexist->btInfo.bRejectAggPkt = *pu8;
		अवरोध;

	हाल BTC_SET_BL_BT_CTRL_AGG_SIZE:
		pBtCoexist->btInfo.bBtCtrlAggBufSize = *pu8;
		अवरोध;

	हाल BTC_SET_BL_INC_SCAN_DEV_NUM:
		pBtCoexist->btInfo.bIncreaseScanDevNum = *pu8;
		अवरोध;

	हाल BTC_SET_BL_BT_TX_RX_MASK:
		pBtCoexist->btInfo.bBtTxRxMask = *pu8;
		अवरोध;

	/*  set some u8 type variables. */
	हाल BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON:
		pBtCoexist->btInfo.rssiAdjustForAgcTableOn = *pu8;
		अवरोध;

	हाल BTC_SET_U1_AGG_BUF_SIZE:
		pBtCoexist->btInfo.aggBufSize = *pu8;
		अवरोध;

	/*  the following are some action which will be triggered */
	हाल BTC_SET_ACT_GET_BT_RSSI:
		ret = false;
		अवरोध;

	हाल BTC_SET_ACT_AGGREGATE_CTRL:
		halbtcoutsrc_AggregationCheck(pBtCoexist);
		अवरोध;

	/* 1Ant =========== */
	/*  set some u8 type variables. */
	हाल BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE:
		pBtCoexist->btInfo.rssiAdjustFor1AntCoexType = *pu8;
		अवरोध;

	हाल BTC_SET_U1_LPS_VAL:
		pBtCoexist->btInfo.lpsVal = *pu8;
		अवरोध;

	हाल BTC_SET_U1_RPWM_VAL:
		pBtCoexist->btInfo.rpwmVal = *pu8;
		अवरोध;

	/*  the following are some action which will be triggered */
	हाल BTC_SET_ACT_LEAVE_LPS:
		halbtcoutsrc_LeaveLps(pBtCoexist);
		अवरोध;

	हाल BTC_SET_ACT_ENTER_LPS:
		halbtcoutsrc_EnterLps(pBtCoexist);
		अवरोध;

	हाल BTC_SET_ACT_NORMAL_LPS:
		halbtcoutsrc_NormalLps(pBtCoexist);
		अवरोध;

	हाल BTC_SET_ACT_DISABLE_LOW_POWER:
		halbtcoutsrc_DisableLowPower(pBtCoexist, *pu8);
		अवरोध;

	हाल BTC_SET_ACT_UPDATE_RAMASK:
		pBtCoexist->btInfo.raMask = *pU4Tmp;

		अगर (check_fwstate(&padapter->mlmepriv, WIFI_ASOC_STATE) == true) अणु
			काष्ठा sta_info *psta;
			काष्ठा wlan_bssid_ex *cur_network;

			cur_network = &padapter->mlmeextpriv.mlmext_info.network;
			psta = rtw_get_stainfo(&padapter->stapriv, cur_network->MacAddress);
			rtw_hal_update_ra_mask(psta, 0);
		पूर्ण
		अवरोध;

	हाल BTC_SET_ACT_SEND_MIMO_PS:
		ret = false;
		अवरोध;

	हाल BTC_SET_ACT_CTRL_BT_INFO:
		ret = false;
		अवरोध;

	हाल BTC_SET_ACT_CTRL_BT_COEX:
		ret = false;
		अवरोध;
	हाल BTC_SET_ACT_CTRL_8723B_ANT:
		ret = false;
		अवरोध;
	/*  */
	शेष:
		ret = false;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम halbtcoutsrc_DisplayFwPwrModeCmd(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 *cliBuf = pBtCoexist->cliBuf;

	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %02x %02x %02x %02x %02x %02x ", "Power mode cmd ", \
		pBtCoexist->pwrModeVal[0], pBtCoexist->pwrModeVal[1],
		pBtCoexist->pwrModeVal[2], pBtCoexist->pwrModeVal[3],
		pBtCoexist->pwrModeVal[4], pBtCoexist->pwrModeVal[5]);
	CL_PRINTF(cliBuf);
पूर्ण

/*  */
/* 		IO related function */
/*  */
अटल u8 halbtcoutsrc_Read1Byte(व्योम *pBtcContext, u32 RegAddr)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	वापस rtw_पढ़ो8(padapter, RegAddr);
पूर्ण

अटल u16 halbtcoutsrc_Read2Byte(व्योम *pBtcContext, u32 RegAddr)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	वापस	rtw_पढ़ो16(padapter, RegAddr);
पूर्ण

अटल u32 halbtcoutsrc_Read4Byte(व्योम *pBtcContext, u32 RegAddr)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	वापस	rtw_पढ़ो32(padapter, RegAddr);
पूर्ण

अटल व्योम halbtcoutsrc_Write1Byte(व्योम *pBtcContext, u32 RegAddr, u8 Data)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	rtw_ग_लिखो8(padapter, RegAddr, Data);
पूर्ण

अटल व्योम halbtcoutsrc_BitMaskWrite1Byte(व्योम *pBtcContext, u32 regAddr, u8 bitMask, u8 data1b)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;
	u8 originalValue, bitShअगरt;
	u8 i;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;
	originalValue = 0;
	bitShअगरt = 0;

	अगर (bitMask != 0xFF) अणु
		originalValue = rtw_पढ़ो8(padapter, regAddr);

		क्रम (i = 0; i <= 7; i++) अणु
			अगर ((bitMask >> i) & 0x1)
				अवरोध;
		पूर्ण
		bitShअगरt = i;

		data1b = (originalValue & ~bitMask) | ((data1b << bitShअगरt) & bitMask);
	पूर्ण

	rtw_ग_लिखो8(padapter, regAddr, data1b);
पूर्ण

अटल व्योम halbtcoutsrc_Write2Byte(व्योम *pBtcContext, u32 RegAddr, u16 Data)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	rtw_ग_लिखो16(padapter, RegAddr, Data);
पूर्ण

अटल व्योम halbtcoutsrc_Write4Byte(व्योम *pBtcContext, u32 RegAddr, u32 Data)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	rtw_ग_लिखो32(padapter, RegAddr, Data);
पूर्ण

अटल व्योम halbtcoutsrc_WriteLocalReg1Byte(व्योम *pBtcContext, u32 RegAddr, u8 Data)
अणु
	काष्ठा btc_coexist *pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	काष्ठा adapter *Adapter = pBtCoexist->Adapter;

	अगर (BTC_INTF_SDIO == pBtCoexist->chipInterface)
		rtw_ग_लिखो8(Adapter, SDIO_LOCAL_BASE | RegAddr, Data);
	अन्यथा
		rtw_ग_लिखो8(Adapter, RegAddr, Data);
पूर्ण

अटल व्योम halbtcoutsrc_SetBbReg(व्योम *pBtcContext, u32 RegAddr, u32 BitMask, u32 Data)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	PHY_SetBBReg(padapter, RegAddr, BitMask, Data);
पूर्ण


अटल u32 halbtcoutsrc_GetBbReg(व्योम *pBtcContext, u32 RegAddr, u32 BitMask)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	वापस PHY_QueryBBReg(padapter, RegAddr, BitMask);
पूर्ण

अटल व्योम halbtcoutsrc_SetRfReg(व्योम *pBtcContext, u8 eRFPath, u32 RegAddr, u32 BitMask, u32 Data)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	PHY_SetRFReg(padapter, eRFPath, RegAddr, BitMask, Data);
पूर्ण

अटल u32 halbtcoutsrc_GetRfReg(व्योम *pBtcContext, u8 eRFPath, u32 RegAddr, u32 BitMask)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	वापस PHY_QueryRFReg(padapter, eRFPath, RegAddr, BitMask);
पूर्ण

अटल व्योम halbtcoutsrc_SetBtReg(व्योम *pBtcContext, u8 RegType, u32 RegAddr, u32 Data)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;
	u8 CmdBuffer1[4] = अणु0पूर्ण;
	u8 CmdBuffer2[4] = अणु0पूर्ण;
	u8 *AddrToSet = (u8 *)&RegAddr;
	u8 *ValueToSet = (u8 *)&Data;
	u8 OperVer = 0;
	u8 ReqNum = 0;

	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	CmdBuffer1[0] |= (OperVer & 0x0f);						/* Set OperVer */
	CmdBuffer1[0] |= ((ReqNum << 4) & 0xf0);				/* Set ReqNum */
	CmdBuffer1[1] = 0x0d;									/* Set OpCode to BT_LO_OP_WRITE_REG_VALUE */
	CmdBuffer1[2] = ValueToSet[0];							/* Set WriteRegValue */
	rtw_hal_fill_h2c_cmd(padapter, 0x67, 4, &(CmdBuffer1[0]));

	msleep(200);
	ReqNum++;

	CmdBuffer2[0] |= (OperVer & 0x0f);						/* Set OperVer */
	CmdBuffer2[0] |= ((ReqNum << 4) & 0xf0);				/* Set ReqNum */
	CmdBuffer2[1] = 0x0c;									/* Set OpCode of BT_LO_OP_WRITE_REG_ADDR */
	CmdBuffer2[3] = AddrToSet[0];							/* Set WriteRegAddr */
	rtw_hal_fill_h2c_cmd(padapter, 0x67, 4, &(CmdBuffer2[0]));
पूर्ण

अटल u32 halbtcoutsrc_GetBtReg(व्योम *pBtcContext, u8 RegType, u32 RegAddr)
अणु
	/* To be implemented. Always वापस 0 temporarily */
	वापस 0;
पूर्ण

अटल व्योम halbtcoutsrc_FillH2cCmd(व्योम *pBtcContext, u8 elementId, u32 cmdLen, u8 *pCmdBuffer)
अणु
	काष्ठा btc_coexist *pBtCoexist;
	काष्ठा adapter *padapter;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	padapter = pBtCoexist->Adapter;

	rtw_hal_fill_h2c_cmd(padapter, elementId, cmdLen, pCmdBuffer);
पूर्ण

अटल व्योम halbtcoutsrc_DisplayDbgMsg(व्योम *pBtcContext, u8 dispType)
अणु
	काष्ठा btc_coexist *pBtCoexist;


	pBtCoexist = (काष्ठा btc_coexist *)pBtcContext;
	चयन (dispType) अणु
	हाल BTC_DBG_DISP_COEX_STATISTICS:
		अवरोध;
	हाल BTC_DBG_DISP_BT_LINK_INFO:
		अवरोध;
	हाल BTC_DBG_DISP_FW_PWR_MODE_CMD:
		halbtcoutsrc_DisplayFwPwrModeCmd(pBtCoexist);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*  */
/* 		Extern functions called by other module */
/*  */
अटल u8 EXhalbtcoutsrc_BindBtCoexWithAdapter(व्योम *padapter)
अणु
	काष्ठा btc_coexist *pBtCoexist = &GLBtCoexist;

	अगर (pBtCoexist->bBinded)
		वापस false;
	अन्यथा
		pBtCoexist->bBinded = true;

	pBtCoexist->statistics.cntBind++;

	pBtCoexist->Adapter = padapter;

	pBtCoexist->stackInfo.bProfileNotअगरied = false;

	pBtCoexist->btInfo.bBtCtrlAggBufSize = false;
	pBtCoexist->btInfo.aggBufSize = 5;

	pBtCoexist->btInfo.bIncreaseScanDevNum = false;

	/*  set शेष antenna position to मुख्य  port */
	pBtCoexist->boardInfo.btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT;

	वापस true;
पूर्ण

व्योम hal_btcoex_Initialize(व्योम *padapter)
अणु
	काष्ठा btc_coexist *pBtCoexist;

	स_रखो(&GLBtCoexist, 0, माप(GLBtCoexist));

	pBtCoexist = &GLBtCoexist;

	/* pBtCoexist->statistics.cntBind++; */

	halbtcoutsrc_DbgInit();

	pBtCoexist->chipInterface = BTC_INTF_SDIO;

	EXhalbtcoutsrc_BindBtCoexWithAdapter(padapter);

	pBtCoexist->fBtcRead1Byte = halbtcoutsrc_Read1Byte;
	pBtCoexist->fBtcWrite1Byte = halbtcoutsrc_Write1Byte;
	pBtCoexist->fBtcWrite1ByteBitMask = halbtcoutsrc_BitMaskWrite1Byte;
	pBtCoexist->fBtcRead2Byte = halbtcoutsrc_Read2Byte;
	pBtCoexist->fBtcWrite2Byte = halbtcoutsrc_Write2Byte;
	pBtCoexist->fBtcRead4Byte = halbtcoutsrc_Read4Byte;
	pBtCoexist->fBtcWrite4Byte = halbtcoutsrc_Write4Byte;
	pBtCoexist->fBtcWriteLocalReg1Byte = halbtcoutsrc_WriteLocalReg1Byte;

	pBtCoexist->fBtcSetBbReg = halbtcoutsrc_SetBbReg;
	pBtCoexist->fBtcGetBbReg = halbtcoutsrc_GetBbReg;

	pBtCoexist->fBtcSetRfReg = halbtcoutsrc_SetRfReg;
	pBtCoexist->fBtcGetRfReg = halbtcoutsrc_GetRfReg;

	pBtCoexist->fBtcFillH2c = halbtcoutsrc_FillH2cCmd;
	pBtCoexist->fBtcDispDbgMsg = halbtcoutsrc_DisplayDbgMsg;

	pBtCoexist->fBtcGet = halbtcoutsrc_Get;
	pBtCoexist->fBtcSet = halbtcoutsrc_Set;
	pBtCoexist->fBtcGetBtReg = halbtcoutsrc_GetBtReg;
	pBtCoexist->fBtcSetBtReg = halbtcoutsrc_SetBtReg;

	pBtCoexist->cliBuf = &GLBtcDbgBuf[0];

	pBtCoexist->boardInfo.singleAntPath = 0;

	GLBtcWiFiInScanState = false;

	GLBtcWiFiInIQKState = false;
पूर्ण

व्योम EXhalbtcoutsrc_PowerOnSetting(काष्ठा btc_coexist *pBtCoexist)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	/* Power on setting function is only added in 8723B currently */
	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_PowerOnSetting(pBtCoexist);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_PowerOnSetting(pBtCoexist);
पूर्ण

व्योम EXhalbtcoutsrc_InitHwConfig(काष्ठा btc_coexist *pBtCoexist, u8 bWअगरiOnly)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	pBtCoexist->statistics.cntInitHwConfig++;

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_InitHwConfig(pBtCoexist, bWअगरiOnly);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_InitHwConfig(pBtCoexist, bWअगरiOnly);
पूर्ण

व्योम EXhalbtcoutsrc_InitCoexDm(काष्ठा btc_coexist *pBtCoexist)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	pBtCoexist->statistics.cntInitCoexDm++;

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_InitCoexDm(pBtCoexist);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_InitCoexDm(pBtCoexist);

	pBtCoexist->bInitilized = true;
पूर्ण

व्योम EXhalbtcoutsrc_IpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	u8 ipsType;

	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	pBtCoexist->statistics.cntIpsNotअगरy++;
	अगर (pBtCoexist->bManualControl)
		वापस;

	अगर (IPS_NONE == type)
		ipsType = BTC_IPS_LEAVE;
	अन्यथा
		ipsType = BTC_IPS_ENTER;

	/*  All notअगरy is called in cmd thपढ़ो, करोn't need to leave low घातer again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_IpsNotअगरy(pBtCoexist, ipsType);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_IpsNotअगरy(pBtCoexist, ipsType);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
पूर्ण

व्योम EXhalbtcoutsrc_LpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	u8 lpsType;


	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	pBtCoexist->statistics.cntLpsNotअगरy++;
	अगर (pBtCoexist->bManualControl)
		वापस;

	अगर (PS_MODE_ACTIVE == type)
		lpsType = BTC_LPS_DISABLE;
	अन्यथा
		lpsType = BTC_LPS_ENABLE;

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_LpsNotअगरy(pBtCoexist, lpsType);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_LpsNotअगरy(pBtCoexist, lpsType);
पूर्ण

व्योम EXhalbtcoutsrc_ScanNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	u8 scanType;

	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;
	pBtCoexist->statistics.cntScanNotअगरy++;
	अगर (pBtCoexist->bManualControl)
		वापस;

	अगर (type) अणु
		scanType = BTC_SCAN_START;
		GLBtcWiFiInScanState = true;
	पूर्ण अन्यथा अणु
		scanType = BTC_SCAN_FINISH;
		GLBtcWiFiInScanState = false;
	पूर्ण

	/*  All notअगरy is called in cmd thपढ़ो, करोn't need to leave low घातer again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_ScanNotअगरy(pBtCoexist, scanType);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_ScanNotअगरy(pBtCoexist, scanType);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
पूर्ण

व्योम EXhalbtcoutsrc_ConnectNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 action)
अणु
	u8 assoType;

	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;
	pBtCoexist->statistics.cntConnectNotअगरy++;
	अगर (pBtCoexist->bManualControl)
		वापस;

	अगर (action)
		assoType = BTC_ASSOCIATE_START;
	अन्यथा
		assoType = BTC_ASSOCIATE_FINISH;

	/*  All notअगरy is called in cmd thपढ़ो, करोn't need to leave low घातer again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_ConnectNotअगरy(pBtCoexist, assoType);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_ConnectNotअगरy(pBtCoexist, assoType);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
पूर्ण

व्योम EXhalbtcoutsrc_MediaStatusNotअगरy(काष्ठा btc_coexist *pBtCoexist, क्रमागत
	rt_media_status mediaStatus)
अणु
	u8 mStatus;

	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	pBtCoexist->statistics.cntMediaStatusNotअगरy++;
	अगर (pBtCoexist->bManualControl)
		वापस;

	अगर (RT_MEDIA_CONNECT == mediaStatus)
		mStatus = BTC_MEDIA_CONNECT;
	अन्यथा
		mStatus = BTC_MEDIA_DISCONNECT;

	/*  All notअगरy is called in cmd thपढ़ो, करोn't need to leave low घातer again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_MediaStatusNotअगरy(pBtCoexist, mStatus);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_MediaStatusNotअगरy(pBtCoexist, mStatus);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
पूर्ण

व्योम EXhalbtcoutsrc_SpecialPacketNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 pktType)
अणु
	u8 packetType;

	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;
	pBtCoexist->statistics.cntSpecialPacketNotअगरy++;
	अगर (pBtCoexist->bManualControl)
		वापस;

	अगर (PACKET_DHCP == pktType) अणु
		packetType = BTC_PACKET_DHCP;
	पूर्ण अन्यथा अगर (PACKET_EAPOL == pktType) अणु
		packetType = BTC_PACKET_EAPOL;
	पूर्ण अन्यथा अगर (PACKET_ARP == pktType) अणु
		packetType = BTC_PACKET_ARP;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	/*  All notअगरy is called in cmd thपढ़ो, करोn't need to leave low घातer again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_SpecialPacketNotअगरy(pBtCoexist, packetType);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_SpecialPacketNotअगरy(pBtCoexist, packetType);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
पूर्ण

व्योम EXhalbtcoutsrc_BtInfoNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 *पंचांगpBuf, u8 length)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	pBtCoexist->statistics.cntBtInfoNotअगरy++;

	/*  All notअगरy is called in cmd thपढ़ो, करोn't need to leave low घातer again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_BtInfoNotअगरy(pBtCoexist, पंचांगpBuf, length);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_BtInfoNotअगरy(pBtCoexist, पंचांगpBuf, length);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
पूर्ण

व्योम EXhalbtcoutsrc_HaltNotअगरy(काष्ठा btc_coexist *pBtCoexist)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_HaltNotअगरy(pBtCoexist);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_HaltNotअगरy(pBtCoexist);

	pBtCoexist->bBinded = false;
पूर्ण

व्योम EXhalbtcoutsrc_PnpNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 pnpState)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	/*  */
	/*  currently only 1ant we have to करो the notअगरication, */
	/*  once pnp is notअगरied to sleep state, we have to leave LPS that we can sleep normally. */
	/*  */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_PnpNotअगरy(pBtCoexist, pnpState);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_PnpNotअगरy(pBtCoexist, pnpState);
पूर्ण

व्योम EXhalbtcoutsrc_Periodical(काष्ठा btc_coexist *pBtCoexist)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;
	pBtCoexist->statistics.cntPeriodical++;

	/*  Periodical should be called in cmd thपढ़ो, */
	/*  करोn't need to leave low घातer again */
/* 	halbtcoutsrc_LeaveLowPower(pBtCoexist); */

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_Periodical(pBtCoexist);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_Periodical(pBtCoexist);

/* 	halbtcoutsrc_NormalLowPower(pBtCoexist); */
पूर्ण

व्योम EXhalbtcoutsrc_SetChipType(u8 chipType)
अणु
	GLBtCoexist.boardInfo.btChipType = BTC_CHIP_RTL8723B;
पूर्ण

व्योम EXhalbtcoutsrc_SetAntNum(u8 type, u8 antNum)
अणु
	अगर (BT_COEX_ANT_TYPE_PG == type) अणु
		GLBtCoexist.boardInfo.pgAntNum = antNum;
		GLBtCoexist.boardInfo.btdmAntNum = antNum;
	पूर्ण अन्यथा अगर (BT_COEX_ANT_TYPE_ANTDIV == type) अणु
		GLBtCoexist.boardInfo.btdmAntNum = antNum;
		/* GLBtCoexist.boardInfo.btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT; */
	पूर्ण अन्यथा अगर (BT_COEX_ANT_TYPE_DETECTED == type) अणु
		GLBtCoexist.boardInfo.btdmAntNum = antNum;
		/* GLBtCoexist.boardInfo.btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT; */
	पूर्ण
पूर्ण

/*  */
/*  Currently used by 8723b only, S0 or S1 */
/*  */
व्योम EXhalbtcoutsrc_SetSingleAntPath(u8 singleAntPath)
अणु
	GLBtCoexist.boardInfo.singleAntPath = singleAntPath;
पूर्ण

व्योम EXhalbtcoutsrc_DisplayBtCoexInfo(काष्ठा btc_coexist *pBtCoexist)
अणु
	अगर (!halbtcoutsrc_IsBtCoexistAvailable(pBtCoexist))
		वापस;

	halbtcoutsrc_LeaveLowPower(pBtCoexist);

	अगर (pBtCoexist->boardInfo.btdmAntNum == 2)
		EXhalbtc8723b2ant_DisplayCoexInfo(pBtCoexist);
	अन्यथा अगर (pBtCoexist->boardInfo.btdmAntNum == 1)
		EXhalbtc8723b1ant_DisplayCoexInfo(pBtCoexist);

	halbtcoutsrc_NormalLowPower(pBtCoexist);
पूर्ण

/*
 * Description:
 *Run BT-Coexist mechanism or not
 *
 */
व्योम hal_btcoex_SetBTCoexist(काष्ठा adapter *padapter, u8 bBtExist)
अणु
	काष्ठा hal_com_data *pHalData;


	pHalData = GET_HAL_DATA(padapter);
	pHalData->bt_coexist.bBtExist = bBtExist;
पूर्ण

/*
 * Dewcription:
 *Check is co-exist mechanism enabled or not
 *
 * Return:
 *true	Enable BT co-exist mechanism
 *false	Disable BT co-exist mechanism
 */
bool hal_btcoex_IsBtExist(काष्ठा adapter *padapter)
अणु
	काष्ठा hal_com_data *pHalData;


	pHalData = GET_HAL_DATA(padapter);
	वापस pHalData->bt_coexist.bBtExist;
पूर्ण

bool hal_btcoex_IsBtDisabled(काष्ठा adapter *padapter)
अणु
	अगर (!hal_btcoex_IsBtExist(padapter))
		वापस true;

	अगर (GLBtCoexist.btInfo.bBtDisabled)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

व्योम hal_btcoex_SetChipType(काष्ठा adapter *padapter, u8 chipType)
अणु
	काष्ठा hal_com_data *pHalData;


	pHalData = GET_HAL_DATA(padapter);
	pHalData->bt_coexist.btChipType = chipType;

	EXhalbtcoutsrc_SetChipType(chipType);
पूर्ण

व्योम hal_btcoex_SetPgAntNum(काष्ठा adapter *padapter, u8 antNum)
अणु
	काष्ठा hal_com_data *pHalData;


	pHalData = GET_HAL_DATA(padapter);

	pHalData->bt_coexist.btTotalAntNum = antNum;
	EXhalbtcoutsrc_SetAntNum(BT_COEX_ANT_TYPE_PG, antNum);
पूर्ण

व्योम hal_btcoex_SetSingleAntPath(काष्ठा adapter *padapter, u8 singleAntPath)
अणु
	EXhalbtcoutsrc_SetSingleAntPath(singleAntPath);
पूर्ण

व्योम hal_btcoex_PowerOnSetting(काष्ठा adapter *padapter)
अणु
	EXhalbtcoutsrc_PowerOnSetting(&GLBtCoexist);
पूर्ण

व्योम hal_btcoex_InitHwConfig(काष्ठा adapter *padapter, u8 bWअगरiOnly)
अणु
	अगर (!hal_btcoex_IsBtExist(padapter))
		वापस;

	EXhalbtcoutsrc_InitHwConfig(&GLBtCoexist, bWअगरiOnly);
	EXhalbtcoutsrc_InitCoexDm(&GLBtCoexist);
पूर्ण

व्योम hal_btcoex_IpsNotअगरy(काष्ठा adapter *padapter, u8 type)
अणु
	EXhalbtcoutsrc_IpsNotअगरy(&GLBtCoexist, type);
पूर्ण

व्योम hal_btcoex_LpsNotअगरy(काष्ठा adapter *padapter, u8 type)
अणु
	EXhalbtcoutsrc_LpsNotअगरy(&GLBtCoexist, type);
पूर्ण

व्योम hal_btcoex_ScanNotअगरy(काष्ठा adapter *padapter, u8 type)
अणु
	EXhalbtcoutsrc_ScanNotअगरy(&GLBtCoexist, type);
पूर्ण

व्योम hal_btcoex_ConnectNotअगरy(काष्ठा adapter *padapter, u8 action)
अणु
	EXhalbtcoutsrc_ConnectNotअगरy(&GLBtCoexist, action);
पूर्ण

व्योम hal_btcoex_MediaStatusNotअगरy(काष्ठा adapter *padapter, u8 mediaStatus)
अणु
	EXhalbtcoutsrc_MediaStatusNotअगरy(&GLBtCoexist, mediaStatus);
पूर्ण

व्योम hal_btcoex_SpecialPacketNotअगरy(काष्ठा adapter *padapter, u8 pktType)
अणु
	EXhalbtcoutsrc_SpecialPacketNotअगरy(&GLBtCoexist, pktType);
पूर्ण

व्योम hal_btcoex_IQKNotअगरy(काष्ठा adapter *padapter, u8 state)
अणु
	GLBtcWiFiInIQKState = state;
पूर्ण

व्योम hal_btcoex_BtInfoNotअगरy(काष्ठा adapter *padapter, u8 length, u8 *पंचांगpBuf)
अणु
	अगर (GLBtcWiFiInIQKState)
		वापस;

	EXhalbtcoutsrc_BtInfoNotअगरy(&GLBtCoexist, पंचांगpBuf, length);
पूर्ण

व्योम hal_btcoex_SuspendNotअगरy(काष्ठा adapter *padapter, u8 state)
अणु
	अगर (state == 1)
		state = BTC_WIFI_PNP_SLEEP;
	अन्यथा
		state = BTC_WIFI_PNP_WAKE_UP;

	EXhalbtcoutsrc_PnpNotअगरy(&GLBtCoexist, state);
पूर्ण

व्योम hal_btcoex_HaltNotअगरy(काष्ठा adapter *padapter)
अणु
	EXhalbtcoutsrc_HaltNotअगरy(&GLBtCoexist);
पूर्ण

व्योम hal_btcoex_Handler(काष्ठा adapter *padapter)
अणु
	EXhalbtcoutsrc_Periodical(&GLBtCoexist);
पूर्ण

s32 hal_btcoex_IsBTCoexCtrlAMPDUSize(काष्ठा adapter *padapter)
अणु
	वापस (s32)GLBtCoexist.btInfo.bBtCtrlAggBufSize;
पूर्ण

व्योम hal_btcoex_SetManualControl(काष्ठा adapter *padapter, u8 bmanual)
अणु
	GLBtCoexist.bManualControl = bmanual;
पूर्ण

bool hal_btcoex_IsBtControlLps(काष्ठा adapter *padapter)
अणु
	अगर (!hal_btcoex_IsBtExist(padapter))
		वापस false;

	अगर (GLBtCoexist.btInfo.bBtDisabled)
		वापस false;

	अगर (GLBtCoexist.btInfo.bBtCtrlLps)
		वापस true;

	वापस false;
पूर्ण

bool hal_btcoex_IsLpsOn(काष्ठा adapter *padapter)
अणु
	अगर (!hal_btcoex_IsBtExist(padapter))
		वापस false;

	अगर (GLBtCoexist.btInfo.bBtDisabled)
		वापस false;

	अगर (GLBtCoexist.btInfo.bBtLpsOn)
		वापस true;

	वापस false;
पूर्ण

u8 hal_btcoex_RpwmVal(काष्ठा adapter *padapter)
अणु
	वापस GLBtCoexist.btInfo.rpwmVal;
पूर्ण

u8 hal_btcoex_LpsVal(काष्ठा adapter *padapter)
अणु
	वापस GLBtCoexist.btInfo.lpsVal;
पूर्ण

u32 hal_btcoex_GetRaMask(काष्ठा adapter *padapter)
अणु
	अगर (!hal_btcoex_IsBtExist(padapter))
		वापस 0;

	अगर (GLBtCoexist.btInfo.bBtDisabled)
		वापस 0;

	अगर (GLBtCoexist.boardInfo.btdmAntNum != 1)
		वापस 0;

	वापस GLBtCoexist.btInfo.raMask;
पूर्ण

व्योम hal_btcoex_RecordPwrMode(काष्ठा adapter *padapter, u8 *pCmdBuf, u8 cmdLen)
अणु
	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_EXEC, ("[BTCoex], FW write pwrModeCmd = 0x%04x%08x\n",
		pCmdBuf[0] << 8 | pCmdBuf[1],
		pCmdBuf[2] << 24 | pCmdBuf[3] << 16 | pCmdBuf[4] << 8 | pCmdBuf[5]));

	स_नकल(GLBtCoexist.pwrModeVal, pCmdBuf, cmdLen);
पूर्ण

व्योम hal_btcoex_DisplayBtCoexInfo(काष्ठा adapter *padapter, u8 *pbuf, u32 bufsize)
अणु
	काष्ठा btcdbginfo *pinfo;


	pinfo = &GLBtcDbgInfo;
	DBG_BT_INFO_INIT(pinfo, pbuf, bufsize);
	EXhalbtcoutsrc_DisplayBtCoexInfo(&GLBtCoexist);
	DBG_BT_INFO_INIT(pinfo, शून्य, 0);
पूर्ण

व्योम hal_btcoex_SetDBG(काष्ठा adapter *padapter, u32 *pDbgModule)
अणु
	u32 i;


	अगर (!pDbgModule)
		वापस;

	क्रम (i = 0; i < BTC_MSG_MAX; i++)
		GLBtcDbgType[i] = pDbgModule[i];
पूर्ण

u32 hal_btcoex_GetDBG(काष्ठा adapter *padapter, u8 *pStrBuf, u32 bufSize)
अणु
	s32 count;
	u8 *pstr;
	u32 leftSize;


	अगर (!pStrBuf || bufSize == 0)
		वापस 0;

	pstr = pStrBuf;
	leftSize = bufSize;

	count = rtw_प्र_लिखो(pstr, leftSize, "#define DBG\t%d\n", DBG);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;

	count = rtw_प्र_लिखो(pstr, leftSize, "BTCOEX Debug Setting:\n");
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;

	count = rtw_प्र_लिखो(pstr, leftSize,
		"INTERFACE / ALGORITHM: 0x%08X / 0x%08X\n\n",
		GLBtcDbgType[BTC_MSG_INTERFACE],
		GLBtcDbgType[BTC_MSG_ALGORITHM]);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;

	count = rtw_प्र_लिखो(pstr, leftSize, "INTERFACE Debug Setting Definition:\n");
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[0]=%d for INTF_INIT\n",
		(GLBtcDbgType[BTC_MSG_INTERFACE] & INTF_INIT) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[2]=%d for INTF_NOTIFY\n\n",
		(GLBtcDbgType[BTC_MSG_INTERFACE] & INTF_NOTIFY) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;

	count = rtw_प्र_लिखो(pstr, leftSize, "ALGORITHM Debug Setting Definition:\n");
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[0]=%d for BT_RSSI_STATE\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_BT_RSSI_STATE) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[1]=%d for WIFI_RSSI_STATE\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_WIFI_RSSI_STATE) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[2]=%d for BT_MONITOR\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_BT_MONITOR) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[3]=%d for TRACE\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_TRACE) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[4]=%d for TRACE_FW\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_TRACE_FW) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[5]=%d for TRACE_FW_DETAIL\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_TRACE_FW_DETAIL) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[6]=%d for TRACE_FW_EXEC\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_TRACE_FW_EXEC) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[7]=%d for TRACE_SW\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_TRACE_SW) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[8]=%d for TRACE_SW_DETAIL\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_TRACE_SW_DETAIL) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;
	count = rtw_प्र_लिखो(pstr, leftSize, "\tbit[9]=%d for TRACE_SW_EXEC\n",
		(GLBtcDbgType[BTC_MSG_ALGORITHM] & ALGO_TRACE_SW_EXEC) ? 1 : 0);
	अगर ((count < 0) || (count >= leftSize))
		जाओ निकास;
	pstr += count;
	leftSize -= count;

निकास:
	count = pstr - pStrBuf;

	वापस count;
पूर्ण
