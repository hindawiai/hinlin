<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "Mp_Precomp.h"

/* defines */
#घोषणा HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(val)			      \
करो अणु									      \
	halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, val);           \
	pCoexDm->psTdmaDuAdjType = val;                                       \
पूर्ण जबतक (0)

/*  Global variables, these are अटल variables */
अटल काष्ठा coex_dm_8723b_2ant GLCoexDm8723b2Ant;
अटल काष्ठा coex_dm_8723b_2ant *pCoexDm = &GLCoexDm8723b2Ant;
अटल काष्ठा coex_sta_8723b_2ant GLCoexSta8723b2Ant;
अटल काष्ठा coex_sta_8723b_2ant *pCoexSta = &GLCoexSta8723b2Ant;

अटल स्थिर अक्षर *स्थिर GLBtInfoSrc8723b2Ant[] = अणु
	"BT Info[wifi fw]",
	"BT Info[bt rsp]",
	"BT Info[bt auto report]",
पूर्ण;

अटल u32 GLCoexVerDate8723b2Ant = 20131211;
अटल u32 GLCoexVer8723b2Ant = 0x40;

/*  local function start with halbtc8723b2ant_ */
अटल u8 halbtc8723b2ant_BtRssiState(
	u8 levelNum, u8 rssiThresh, u8 rssiThresh1
)
अणु
	s32 btRssi = 0;
	u8 btRssiState = pCoexSta->preBtRssiState;

	btRssi = pCoexSta->btRssi;

	अगर (levelNum == 2) अणु
		अगर (
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_LOW) ||
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_STAY_LOW)
		) अणु
			अगर (btRssi >= (rssiThresh + BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) अणु
				btRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state switch to High\n"));
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state stay at Low\n"));
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (btRssi < rssiThresh) अणु
				btRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state switch to Low\n"));
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state stay at High\n"));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (levelNum == 3) अणु
		अगर (rssiThresh > rssiThresh1) अणु
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi thresh error!!\n"));
			वापस pCoexSta->preBtRssiState;
		पूर्ण

		अगर (
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_LOW) ||
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_STAY_LOW)
		) अणु
			अगर (btRssi >= (rssiThresh + BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) अणु
				btRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state switch to Medium\n"));
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state stay at Low\n"));
			पूर्ण
		पूर्ण अन्यथा अगर (
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_MEDIUM) ||
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_STAY_MEDIUM)
		) अणु
			अगर (btRssi >= (rssiThresh1 + BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) अणु
				btRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state switch to High\n"));
			पूर्ण अन्यथा अगर (btRssi < rssiThresh) अणु
				btRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state switch to Low\n"));
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state stay at Medium\n"));
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (btRssi < rssiThresh1) अणु
				btRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state switch to Medium\n"));
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_BT_RSSI_STATE, ("[BTCoex], BT Rssi state stay at High\n"));
			पूर्ण
		पूर्ण
	पूर्ण

	pCoexSta->preBtRssiState = btRssiState;

	वापस btRssiState;
पूर्ण

अटल u8 halbtc8723b2ant_WअगरiRssiState(
	काष्ठा btc_coexist *pBtCoexist,
	u8 index,
	u8 levelNum,
	u8 rssiThresh,
	u8 rssiThresh1
)
अणु
	s32 wअगरiRssi = 0;
	u8 wअगरiRssiState = pCoexSta->preWअगरiRssiState[index];

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_WIFI_RSSI, &wअगरiRssi);

	अगर (levelNum == 2) अणु
		अगर (
			(pCoexSta->preWअगरiRssiState[index] == BTC_RSSI_STATE_LOW) ||
			(pCoexSta->preWअगरiRssiState[index] == BTC_RSSI_STATE_STAY_LOW)
		) अणु
			अगर (wअगरiRssi >= (rssiThresh + BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) अणु
				wअगरiRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to High\n"));
			पूर्ण अन्यथा अणु
				wअगरiRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at Low\n"));
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (wअगरiRssi < rssiThresh) अणु
				wअगरiRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Low\n"));
			पूर्ण अन्यथा अणु
				wअगरiRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at High\n"));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (levelNum == 3) अणु
		अगर (rssiThresh > rssiThresh1) अणु
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI thresh error!!\n"));
			वापस pCoexSta->preWअगरiRssiState[index];
		पूर्ण

		अगर (
			(pCoexSta->preWअगरiRssiState[index] == BTC_RSSI_STATE_LOW) ||
			(pCoexSta->preWअगरiRssiState[index] == BTC_RSSI_STATE_STAY_LOW)
		) अणु
			अगर (wअगरiRssi >= (rssiThresh + BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) अणु
				wअगरiRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Medium\n"));
			पूर्ण अन्यथा अणु
				wअगरiRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at Low\n"));
			पूर्ण
		पूर्ण अन्यथा अगर (
			(pCoexSta->preWअगरiRssiState[index] == BTC_RSSI_STATE_MEDIUM) ||
			(pCoexSta->preWअगरiRssiState[index] == BTC_RSSI_STATE_STAY_MEDIUM)
		) अणु
			अगर (wअगरiRssi >= (rssiThresh1 + BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT)) अणु
				wअगरiRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to High\n"));
			पूर्ण अन्यथा अगर (wअगरiRssi < rssiThresh) अणु
				wअगरiRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Low\n"));
			पूर्ण अन्यथा अणु
				wअगरiRssiState = BTC_RSSI_STATE_STAY_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at Medium\n"));
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (wअगरiRssi < rssiThresh1) अणु
				wअगरiRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state switch to Medium\n"));
			पूर्ण अन्यथा अणु
				wअगरiRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_WIFI_RSSI_STATE, ("[BTCoex], wifi RSSI state stay at High\n"));
			पूर्ण
		पूर्ण
	पूर्ण

	pCoexSta->preWअगरiRssiState[index] = wअगरiRssiState;

	वापस wअगरiRssiState;
पूर्ण

अटल व्योम halbtc8723b2ant_LimitedRx(
	काष्ठा btc_coexist *pBtCoexist,
	bool bForceExec,
	bool bRejApAggPkt,
	bool bBtCtrlAggBufSize,
	u8 aggBufSize
)
अणु
	bool bRejectRxAgg = bRejApAggPkt;
	bool bBtCtrlRxAggSize = bBtCtrlAggBufSize;
	u8 rxAggSize = aggBufSize;

	/*  */
	/* 	Rx Aggregation related setting */
	/*  */
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_TO_REJ_AP_AGG_PKT, &bRejectRxAgg);
	/*  decide BT control aggregation buf size or not */
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE, &bBtCtrlRxAggSize);
	/*  aggregation buf size, only work when BT control Rx aggregation size. */
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_U1_AGG_BUF_SIZE, &rxAggSize);
	/*  real update aggregation setting */
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_AGGREGATE_CTRL, शून्य);
पूर्ण

अटल व्योम halbtc8723b2ant_MonitorBtCtr(काष्ठा btc_coexist *pBtCoexist)
अणु
	u32 regHPTxRx, regLPTxRx, u4Tmp;
	u32 regHPTx = 0, regHPRx = 0, regLPTx = 0, regLPRx = 0;

	regHPTxRx = 0x770;
	regLPTxRx = 0x774;

	u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, regHPTxRx);
	regHPTx = u4Tmp & bMaskLWord;
	regHPRx = (u4Tmp & bMaskHWord) >> 16;

	u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, regLPTxRx);
	regLPTx = u4Tmp & bMaskLWord;
	regLPRx = (u4Tmp & bMaskHWord) >> 16;

	pCoexSta->highPriorityTx = regHPTx;
	pCoexSta->highPriorityRx = regHPRx;
	pCoexSta->lowPriorityTx = regLPTx;
	pCoexSta->lowPriorityRx = regLPRx;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_BT_MONITOR,
		(
			"[BTCoex], High Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
			regHPTxRx,
			regHPTx,
			regHPTx,
			regHPRx,
			regHPRx
		)
	);
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_BT_MONITOR,
		(
			"[BTCoex], Low Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
			regLPTxRx,
			regLPTx,
			regLPTx,
			regLPRx,
			regLPRx
		)
	);

	/*  reset counter */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0xc);
पूर्ण

अटल व्योम halbtc8723b2ant_QueryBtInfo(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 	H2C_Parameter[1] = अणु0पूर्ण;

	pCoexSta->bC2hBtInfoReqSent = true;

	H2C_Parameter[0] |= BIT0;	/*  trigger */

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		("[BTCoex], Query Bt Info, FW write 0x61 = 0x%x\n", H2C_Parameter[0])
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x61, 1, H2C_Parameter);
पूर्ण

अटल bool halbtc8723b2ant_IsWअगरiStatusChanged(काष्ठा btc_coexist *pBtCoexist)
अणु
	अटल bool	bPreWअगरiBusy, bPreUnder4way, bPreBtHsOn;
	bool bWअगरiBusy = false, bUnder4way = false, bBtHsOn = false;
	bool bWअगरiConnected = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS, &bUnder4way);

	अगर (bWअगरiConnected) अणु
		अगर (bWअगरiBusy != bPreWअगरiBusy) अणु
			bPreWअगरiBusy = bWअगरiBusy;
			वापस true;
		पूर्ण

		अगर (bUnder4way != bPreUnder4way) अणु
			bPreUnder4way = bUnder4way;
			वापस true;
		पूर्ण

		अगर (bBtHsOn != bPreBtHsOn) अणु
			bPreBtHsOn = bBtHsOn;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम halbtc8723b2ant_UpdateBtLinkInfo(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bBtHsOn = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);

	pBtLinkInfo->bBtLinkExist = pCoexSta->bBtLinkExist;
	pBtLinkInfo->bScoExist = pCoexSta->bScoExist;
	pBtLinkInfo->bA2dpExist = pCoexSta->bA2dpExist;
	pBtLinkInfo->bPanExist = pCoexSta->bPanExist;
	pBtLinkInfo->bHidExist = pCoexSta->bHidExist;

	/*  work around क्रम HS mode. */
	अगर (bBtHsOn) अणु
		pBtLinkInfo->bPanExist = true;
		pBtLinkInfo->bBtLinkExist = true;
	पूर्ण

	/*  check अगर Sco only */
	अगर (
		pBtLinkInfo->bScoExist &&
		!pBtLinkInfo->bA2dpExist &&
		!pBtLinkInfo->bPanExist &&
		!pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bScoOnly = true;
	अन्यथा
		pBtLinkInfo->bScoOnly = false;

	/*  check अगर A2dp only */
	अगर (
		!pBtLinkInfo->bScoExist &&
		pBtLinkInfo->bA2dpExist &&
		!pBtLinkInfo->bPanExist &&
		!pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bA2dpOnly = true;
	अन्यथा
		pBtLinkInfo->bA2dpOnly = false;

	/*  check अगर Pan only */
	अगर (
		!pBtLinkInfo->bScoExist &&
		!pBtLinkInfo->bA2dpExist &&
		pBtLinkInfo->bPanExist &&
		!pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bPanOnly = true;
	अन्यथा
		pBtLinkInfo->bPanOnly = false;

	/*  check अगर Hid only */
	अगर (
		!pBtLinkInfo->bScoExist &&
		!pBtLinkInfo->bA2dpExist &&
		!pBtLinkInfo->bPanExist &&
		pBtLinkInfo->bHidExist
	)
		pBtLinkInfo->bHidOnly = true;
	अन्यथा
		pBtLinkInfo->bHidOnly = false;
पूर्ण

अटल u8 halbtc8723b2ant_ActionAlgorithm(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bBtHsOn = false;
	u8 algorithm = BT_8723B_2ANT_COEX_ALGO_UNDEFINED;
	u8 numOfDअगरfProfile = 0;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);

	अगर (!pBtLinkInfo->bBtLinkExist) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], No BT link exists!!!\n"));
		वापस algorithm;
	पूर्ण

	अगर (pBtLinkInfo->bScoExist)
		numOfDअगरfProfile++;

	अगर (pBtLinkInfo->bHidExist)
		numOfDअगरfProfile++;

	अगर (pBtLinkInfo->bPanExist)
		numOfDअगरfProfile++;

	अगर (pBtLinkInfo->bA2dpExist)
		numOfDअगरfProfile++;

	अगर (numOfDअगरfProfile == 1) अणु
		अगर (pBtLinkInfo->bScoExist) अणु
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO only\n"));
			algorithm = BT_8723B_2ANT_COEX_ALGO_SCO;
		पूर्ण अन्यथा अणु
			अगर (pBtLinkInfo->bHidExist) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID only\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bA2dpExist) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], A2DP only\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_A2DP;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], PAN(HS) only\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANHS;
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], PAN(EDR) only\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (numOfDअगरfProfile == 2) अणु
		अगर (pBtLinkInfo->bScoExist) अणु
			अगर (pBtLinkInfo->bHidExist) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + HID\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bA2dpExist) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + A2DP ==> SCO\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bA2dpExist
			) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + A2DP\n"));
				algorithm = BT_8723B_2ANT_COEX_ALGO_HID_A2DP;
			पूर्ण अन्यथा अगर (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_HID;
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], A2DP + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_A2DP_PANHS;
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], A2DP + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_A2DP;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (numOfDअगरfProfile == 3) अणु
		अगर (pBtLinkInfo->bScoExist) अणु
			अगर (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bA2dpExist
			) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], SCO + HID + A2DP ==> HID\n")
				);
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], SCO + HID + PAN(HS)\n")
					);
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], SCO + HID + PAN(EDR)\n")
					);
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + A2DP + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + A2DP + PAN(EDR) ==> HID\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + A2DP + PAN(HS)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], HID + A2DP + PAN(EDR)\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (numOfDअगरfProfile >= 3) अणु
		अगर (pBtLinkInfo->bScoExist) अणु
			अगर (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Error!!! SCO + HID + A2DP + PAN(HS)\n"));

				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], SCO + HID + A2DP + PAN(EDR) ==>PAN(EDR)+HID\n"));
					algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस algorithm;
पूर्ण

अटल व्योम halbtc8723b2ant_SetFwDacSwingLevel(
	काष्ठा btc_coexist *pBtCoexist, u8 dacSwingLvl
)
अणु
	u8 	H2C_Parameter[1] = अणु0पूर्ण;

	/*  There are several type of dacswing */
	/*  0x18/ 0x10/ 0xc/ 0x8/ 0x4/ 0x6 */
	H2C_Parameter[0] = dacSwingLvl;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		("[BTCoex], Set Dac Swing Level = 0x%x\n", dacSwingLvl)
	);
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		("[BTCoex], FW write 0x64 = 0x%x\n", H2C_Parameter[0])
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x64, 1, H2C_Parameter);
पूर्ण

अटल व्योम halbtc8723b2ant_SetFwDecBtPwr(
	काष्ठा btc_coexist *pBtCoexist, u8 decBtPwrLvl
)
अणु
	u8 	H2C_Parameter[1] = अणु0पूर्ण;

	H2C_Parameter[0] = decBtPwrLvl;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], decrease Bt Power level = %d, FW write 0x62 = 0x%x\n",
			decBtPwrLvl,
			H2C_Parameter[0]
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x62, 1, H2C_Parameter);
पूर्ण

अटल व्योम halbtc8723b2ant_DecBtPwr(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 decBtPwrLvl
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		(
			"[BTCoex], %s Dec BT power level = %d\n",
			(bForceExec ? "force to" : ""),
			decBtPwrLvl
		)
	);
	pCoexDm->curBtDecPwrLvl = decBtPwrLvl;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], preBtDecPwrLvl =%d, curBtDecPwrLvl =%d\n",
				pCoexDm->preBtDecPwrLvl,
				pCoexDm->curBtDecPwrLvl
			)
		);

		अगर (pCoexDm->preBtDecPwrLvl == pCoexDm->curBtDecPwrLvl)
			वापस;
	पूर्ण
	halbtc8723b2ant_SetFwDecBtPwr(pBtCoexist, pCoexDm->curBtDecPwrLvl);

	pCoexDm->preBtDecPwrLvl = pCoexDm->curBtDecPwrLvl;
पूर्ण

अटल व्योम halbtc8723b2ant_FwDacSwingLvl(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 fwDacSwingLvl
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		(
			"[BTCoex], %s set FW Dac Swing level = %d\n",
			(bForceExec ? "force to" : ""),
			fwDacSwingLvl
		)
	);
	pCoexDm->curFwDacSwingLvl = fwDacSwingLvl;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], preFwDacSwingLvl =%d, curFwDacSwingLvl =%d\n",
				pCoexDm->preFwDacSwingLvl,
				pCoexDm->curFwDacSwingLvl
			)
		);

		अगर (pCoexDm->preFwDacSwingLvl == pCoexDm->curFwDacSwingLvl)
			वापस;
	पूर्ण

	halbtc8723b2ant_SetFwDacSwingLevel(pBtCoexist, pCoexDm->curFwDacSwingLvl);

	pCoexDm->preFwDacSwingLvl = pCoexDm->curFwDacSwingLvl;
पूर्ण

अटल व्योम halbtc8723b2ant_SetSwRfRxLpfCorner(
	काष्ठा btc_coexist *pBtCoexist,
	bool bRxRfShrinkOn
)
अणु
	अगर (bRxRfShrinkOn) अणु
		/* Shrink RF Rx LPF corner */
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_EXEC,
			("[BTCoex], Shrink RF Rx LPF corner!!\n")
		);
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1e, 0xfffff, 0xffffc);
	पूर्ण अन्यथा अणु
		/* Resume RF Rx LPF corner */
		/*  After initialized, we can use pCoexDm->btRf0x1eBackup */
		अगर (pBtCoexist->bInitilized) अणु
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], Resume RF Rx LPF corner!!\n"));
			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1e, 0xfffff, pCoexDm->btRf0x1eBackup);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_RfShrink(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, bool bRxRfShrinkOn
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW,
		(
			"[BTCoex], %s turn Rx RF Shrink = %s\n",
			(bForceExec ? "force to" : ""),
			(bRxRfShrinkOn ? "ON" : "OFF")
		)
	);
	pCoexDm->bCurRfRxLpfShrink = bRxRfShrinkOn;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], bPreRfRxLpfShrink =%d, bCurRfRxLpfShrink =%d\n",
				pCoexDm->bPreRfRxLpfShrink,
				pCoexDm->bCurRfRxLpfShrink
			)
		);

		अगर (pCoexDm->bPreRfRxLpfShrink == pCoexDm->bCurRfRxLpfShrink)
			वापस;
	पूर्ण
	halbtc8723b2ant_SetSwRfRxLpfCorner(pBtCoexist, pCoexDm->bCurRfRxLpfShrink);

	pCoexDm->bPreRfRxLpfShrink = pCoexDm->bCurRfRxLpfShrink;
पूर्ण

अटल व्योम halbtc8723b2ant_SetSwPenaltyTxRateAdaptive(
	काष्ठा btc_coexist *pBtCoexist, bool bLowPenaltyRa
)
अणु
	u8 	H2C_Parameter[6] = अणु0पूर्ण;

	H2C_Parameter[0] = 0x6;	/*  opCode, 0x6 = Retry_Penalty */

	अगर (bLowPenaltyRa) अणु
		H2C_Parameter[1] |= BIT0;
		H2C_Parameter[2] = 0x00;  /* normal rate except MCS7/6/5, OFDM54/48/36 */
		H2C_Parameter[3] = 0xf7;  /* MCS7 or OFDM54 */
		H2C_Parameter[4] = 0xf8;  /* MCS6 or OFDM48 */
		H2C_Parameter[5] = 0xf9;	/* MCS5 or OFDM36 */
	पूर्ण

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], set WiFi Low-Penalty Retry: %s",
			(bLowPenaltyRa ? "ON!!" : "OFF!!")
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x69, 6, H2C_Parameter);
पूर्ण

अटल व्योम halbtc8723b2ant_LowPenaltyRa(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, bool bLowPenaltyRa
)
अणु
	/* वापस; */
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW,
		(
			"[BTCoex], %s turn LowPenaltyRA = %s\n",
			(bForceExec ? "force to" : ""),
			(bLowPenaltyRa ? "ON" : "OFF")
		)
	);
	pCoexDm->bCurLowPenaltyRa = bLowPenaltyRa;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], bPreLowPenaltyRa =%d, bCurLowPenaltyRa =%d\n",
				pCoexDm->bPreLowPenaltyRa,
				pCoexDm->bCurLowPenaltyRa
			)
		);

		अगर (pCoexDm->bPreLowPenaltyRa == pCoexDm->bCurLowPenaltyRa)
			वापस;
	पूर्ण
	halbtc8723b2ant_SetSwPenaltyTxRateAdaptive(pBtCoexist, pCoexDm->bCurLowPenaltyRa);

	pCoexDm->bPreLowPenaltyRa = pCoexDm->bCurLowPenaltyRa;
पूर्ण

अटल व्योम halbtc8723b2ant_SetDacSwingReg(काष्ठा btc_coexist *pBtCoexist, u32 level)
अणु
	u8 val = (u8)level;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], Write SwDacSwing = 0x%x\n", level)
	);
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x883, 0x3e, val);
पूर्ण

अटल व्योम halbtc8723b2ant_SetSwFullTimeDacSwing(
	काष्ठा btc_coexist *pBtCoexist, bool bSwDacSwingOn, u32 swDacSwingLvl
)
अणु
	अगर (bSwDacSwingOn)
		halbtc8723b2ant_SetDacSwingReg(pBtCoexist, swDacSwingLvl);
	अन्यथा
		halbtc8723b2ant_SetDacSwingReg(pBtCoexist, 0x18);
पूर्ण


अटल व्योम halbtc8723b2ant_DacSwing(
	काष्ठा btc_coexist *pBtCoexist,
	bool bForceExec,
	bool bDacSwingOn,
	u32 dacSwingLvl
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW,
		(
			"[BTCoex], %s turn DacSwing =%s, dacSwingLvl = 0x%x\n",
			(bForceExec ? "force to" : ""),
			(bDacSwingOn ? "ON" : "OFF"),
			dacSwingLvl
		)
	);
	pCoexDm->bCurDacSwingOn = bDacSwingOn;
	pCoexDm->curDacSwingLvl = dacSwingLvl;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], bPreDacSwingOn =%d, preDacSwingLvl = 0x%x, bCurDacSwingOn =%d, curDacSwingLvl = 0x%x\n",
				pCoexDm->bPreDacSwingOn,
				pCoexDm->preDacSwingLvl,
				pCoexDm->bCurDacSwingOn,
				pCoexDm->curDacSwingLvl
			)
		);

		अगर ((pCoexDm->bPreDacSwingOn == pCoexDm->bCurDacSwingOn) &&
			(pCoexDm->preDacSwingLvl == pCoexDm->curDacSwingLvl))
			वापस;
	पूर्ण
	mdelay(30);
	halbtc8723b2ant_SetSwFullTimeDacSwing(pBtCoexist, bDacSwingOn, dacSwingLvl);

	pCoexDm->bPreDacSwingOn = pCoexDm->bCurDacSwingOn;
	pCoexDm->preDacSwingLvl = pCoexDm->curDacSwingLvl;
पूर्ण

अटल व्योम halbtc8723b2ant_SetAgcTable(
	काष्ठा btc_coexist *pBtCoexist, bool bAgcTableEn
)
अणु
	u8 rssiAdjustVal = 0;

	/* BB AGC Gain Table */
	अगर (bAgcTableEn) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], BB Agc Table On!\n"));
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0x6e1A0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0x6d1B0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0x6c1C0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0x6b1D0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0x6a1E0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0x691F0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0x68200001);
	पूर्ण अन्यथा अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], BB Agc Table Off!\n"));
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0xaa1A0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0xa91B0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0xa81C0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0xa71D0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0xa61E0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0xa51F0001);
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0xc78, 0xa4200001);
	पूर्ण


	/* RF Gain */
	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0xef, 0xfffff, 0x02000);
	अगर (bAgcTableEn) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], Agc Table On!\n"));
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x3b, 0xfffff, 0x38fff);
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x3b, 0xfffff, 0x38ffe);
	पूर्ण अन्यथा अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], Agc Table Off!\n"));
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x3b, 0xfffff, 0x380c3);
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x3b, 0xfffff, 0x28ce6);
	पूर्ण
	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0xef, 0xfffff, 0x0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0xed, 0xfffff, 0x1);
	अगर (bAgcTableEn) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], Agc Table On!\n"));
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x40, 0xfffff, 0x38fff);
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x40, 0xfffff, 0x38ffe);
	पूर्ण अन्यथा अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_SW_EXEC, ("[BTCoex], Agc Table Off!\n"));
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x40, 0xfffff, 0x380c3);
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x40, 0xfffff, 0x28ce6);
	पूर्ण
	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0xed, 0xfffff, 0x0);

	/*  set rssiAdjustVal क्रम wअगरi module. */
	अगर (bAgcTableEn)
		rssiAdjustVal = 8;

	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON, &rssiAdjustVal);
पूर्ण

अटल व्योम halbtc8723b2ant_AgcTable(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, bool bAgcTableEn
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW,
		(
			"[BTCoex], %s %s Agc Table\n",
			(bForceExec ? "force to" : ""),
			(bAgcTableEn ? "Enable" : "Disable")
		)
	);
	pCoexDm->bCurAgcTableEn = bAgcTableEn;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], bPreAgcTableEn =%d, bCurAgcTableEn =%d\n",
				pCoexDm->bPreAgcTableEn,
				pCoexDm->bCurAgcTableEn
			)
		);

		अगर (pCoexDm->bPreAgcTableEn == pCoexDm->bCurAgcTableEn)
			वापस;
	पूर्ण
	halbtc8723b2ant_SetAgcTable(pBtCoexist, bAgcTableEn);

	pCoexDm->bPreAgcTableEn = pCoexDm->bCurAgcTableEn;
पूर्ण

अटल व्योम halbtc8723b2ant_SetCoexTable(
	काष्ठा btc_coexist *pBtCoexist,
	u32 val0x6c0,
	u32 val0x6c4,
	u32 val0x6c8,
	u8 val0x6cc
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6c0 = 0x%x\n", val0x6c0)
	);
	pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x6c0, val0x6c0);

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6c4 = 0x%x\n", val0x6c4)
	);
	pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x6c4, val0x6c4);

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6c8 = 0x%x\n", val0x6c8)
	);
	pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x6c8, val0x6c8);

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW_EXEC,
		("[BTCoex], set coex table, set 0x6cc = 0x%x\n", val0x6cc)
	);
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cc, val0x6cc);
पूर्ण

अटल व्योम halbtc8723b2ant_CoexTable(
	काष्ठा btc_coexist *pBtCoexist,
	bool bForceExec,
	u32 val0x6c0,
	u32 val0x6c4,
	u32 val0x6c8,
	u8 val0x6cc
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_SW,
		(
			"[BTCoex], %s write Coex Table 0x6c0 = 0x%x, 0x6c4 = 0x%x, 0x6c8 = 0x%x, 0x6cc = 0x%x\n",
			(bForceExec ? "force to" : ""),
			val0x6c0,
			val0x6c4,
			val0x6c8,
			val0x6cc
		)
	);
	pCoexDm->curVal0x6c0 = val0x6c0;
	pCoexDm->curVal0x6c4 = val0x6c4;
	pCoexDm->curVal0x6c8 = val0x6c8;
	pCoexDm->curVal0x6cc = val0x6cc;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], preVal0x6c0 = 0x%x, preVal0x6c4 = 0x%x, preVal0x6c8 = 0x%x, preVal0x6cc = 0x%x !!\n",
				pCoexDm->preVal0x6c0,
				pCoexDm->preVal0x6c4,
				pCoexDm->preVal0x6c8,
				pCoexDm->preVal0x6cc
			)
		);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_SW_DETAIL,
			(
				"[BTCoex], curVal0x6c0 = 0x%x, curVal0x6c4 = 0x%x, curVal0x6c8 = 0x%x, curVal0x6cc = 0x%x !!\n",
				pCoexDm->curVal0x6c0,
				pCoexDm->curVal0x6c4,
				pCoexDm->curVal0x6c8,
				pCoexDm->curVal0x6cc
			)
		);

		अगर (
			(pCoexDm->preVal0x6c0 == pCoexDm->curVal0x6c0) &&
			(pCoexDm->preVal0x6c4 == pCoexDm->curVal0x6c4) &&
			(pCoexDm->preVal0x6c8 == pCoexDm->curVal0x6c8) &&
			(pCoexDm->preVal0x6cc == pCoexDm->curVal0x6cc)
		)
			वापस;
	पूर्ण
	halbtc8723b2ant_SetCoexTable(pBtCoexist, val0x6c0, val0x6c4, val0x6c8, val0x6cc);

	pCoexDm->preVal0x6c0 = pCoexDm->curVal0x6c0;
	pCoexDm->preVal0x6c4 = pCoexDm->curVal0x6c4;
	pCoexDm->preVal0x6c8 = pCoexDm->curVal0x6c8;
	pCoexDm->preVal0x6cc = pCoexDm->curVal0x6cc;
पूर्ण

अटल व्योम halbtc8723b2ant_CoexTableWithType(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 type
)
अणु
	चयन (type) अणु
	हाल 0:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55555555, 0x55555555, 0xffff, 0x3);
		अवरोध;
	हाल 1:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55555555, 0x5afa5afa, 0xffff, 0x3);
		अवरोध;
	हाल 2:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x5a5a5a5a, 0x5a5a5a5a, 0xffff, 0x3);
		अवरोध;
	हाल 3:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0xaaaaaaaa, 0xaaaaaaaa, 0xffff, 0x3);
		अवरोध;
	हाल 4:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0xffffffff, 0xffffffff, 0xffff, 0x3);
		अवरोध;
	हाल 5:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x5fff5fff, 0x5fff5fff, 0xffff, 0x3);
		अवरोध;
	हाल 6:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55ff55ff, 0x5a5a5a5a, 0xffff, 0x3);
		अवरोध;
	हाल 7:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55ff55ff, 0xfafafafa, 0xffff, 0x3);
		अवरोध;
	हाल 8:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x5aea5aea, 0x5aea5aea, 0xffff, 0x3);
		अवरोध;
	हाल 9:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55ff55ff, 0x5aea5aea, 0xffff, 0x3);
		अवरोध;
	हाल 10:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55ff55ff, 0x5aff5aff, 0xffff, 0x3);
		अवरोध;
	हाल 11:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55ff55ff, 0x5a5f5a5f, 0xffff, 0x3);
		अवरोध;
	हाल 12:
		halbtc8723b2ant_CoexTable(pBtCoexist, bForceExec, 0x55ff55ff, 0x5f5f5f5f, 0xffff, 0x3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_SetFwIgnoreWlanAct(
	काष्ठा btc_coexist *pBtCoexist, bool bEnable
)
अणु
	u8 	H2C_Parameter[1] = अणु0पूर्ण;

	अगर (bEnable)
		H2C_Parameter[0] |= BIT0;		/*  function enable */

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], set FW for BT Ignore Wlan_Act, FW write 0x63 = 0x%x\n",
			H2C_Parameter[0]
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x63, 1, H2C_Parameter);
पूर्ण

अटल व्योम halbtc8723b2ant_IgnoreWlanAct(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, bool bEnable
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		(
			"[BTCoex], %s turn Ignore WlanAct %s\n",
			(bForceExec ? "force to" : ""),
			(bEnable ? "ON" : "OFF")
		)
	);

	pCoexDm->bCurIgnoreWlanAct = bEnable;

	अगर (!bForceExec) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], bPreIgnoreWlanAct = %d, bCurIgnoreWlanAct = %d!!\n",
			pCoexDm->bPreIgnoreWlanAct, pCoexDm->bCurIgnoreWlanAct));

		अगर (pCoexDm->bPreIgnoreWlanAct == pCoexDm->bCurIgnoreWlanAct)
			वापस;
	पूर्ण
	halbtc8723b2ant_SetFwIgnoreWlanAct(pBtCoexist, bEnable);

	pCoexDm->bPreIgnoreWlanAct = pCoexDm->bCurIgnoreWlanAct;
पूर्ण

अटल व्योम halbtc8723b2ant_SetFwPstdma(
	काष्ठा btc_coexist *pBtCoexist,
	u8 byte1,
	u8 byte2,
	u8 byte3,
	u8 byte4,
	u8 byte5
)
अणु
	u8 	H2C_Parameter[5] = अणु0पूर्ण;

	H2C_Parameter[0] = byte1;
	H2C_Parameter[1] = byte2;
	H2C_Parameter[2] = byte3;
	H2C_Parameter[3] = byte4;
	H2C_Parameter[4] = byte5;

	pCoexDm->psTdmaPara[0] = byte1;
	pCoexDm->psTdmaPara[1] = byte2;
	pCoexDm->psTdmaPara[2] = byte3;
	pCoexDm->psTdmaPara[3] = byte4;
	pCoexDm->psTdmaPara[4] = byte5;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], FW write 0x60(5bytes) = 0x%x%08x\n",
			H2C_Parameter[0],
			H2C_Parameter[1] << 24 |
			H2C_Parameter[2] << 16 |
			H2C_Parameter[3] << 8 |
			H2C_Parameter[4]
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x60, 5, H2C_Parameter);
पूर्ण

अटल व्योम halbtc8723b2ant_SwMechanism1(
	काष्ठा btc_coexist *pBtCoexist,
	bool bShrinkRxLPF,
	bool bLowPenaltyRA,
	bool bLimitedDIG,
	bool bBTLNAConstrain
)
अणु
	halbtc8723b2ant_RfShrink(pBtCoexist, NORMAL_EXEC, bShrinkRxLPF);
	halbtc8723b2ant_LowPenaltyRa(pBtCoexist, NORMAL_EXEC, bLowPenaltyRA);
पूर्ण

अटल व्योम halbtc8723b2ant_SwMechanism2(
	काष्ठा btc_coexist *pBtCoexist,
	bool bAGCTableShअगरt,
	bool bADCBackOff,
	bool bSWDACSwing,
	u32 dacSwingLvl
)
अणु
	halbtc8723b2ant_AgcTable(pBtCoexist, NORMAL_EXEC, bAGCTableShअगरt);
	halbtc8723b2ant_DacSwing(pBtCoexist, NORMAL_EXEC, bSWDACSwing, dacSwingLvl);
पूर्ण

अटल व्योम halbtc8723b2ant_SetAntPath(
	काष्ठा btc_coexist *pBtCoexist, u8 antPosType, bool bInitHwCfg, bool bWअगरiOff
)
अणु
	काष्ठा btc_board_info *pBoardInfo = &pBtCoexist->boardInfo;
	u32 fwVer = 0, u4Tmp = 0;
	bool bPgExtSwitch = false;
	bool bUseExtSwitch = false;
	u8 	H2C_Parameter[2] = अणु0पूर्ण;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_EXT_SWITCH, &bPgExtSwitch);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);	/*  [31:16]=fw ver, [15:0]=fw sub ver */

	अगर ((fwVer > 0 && fwVer < 0xc0000) || bPgExtSwitch)
		bUseExtSwitch = true;

	अगर (bInitHwCfg) अणु
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x39, 0x8, 0x1);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x974, 0xff);
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x944, 0x3, 0x3);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x930, 0x77);
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1);

		अगर (fwVer >= 0x180000) अणु
			/* Use H2C to set GNT_BT to LOW */
			H2C_Parameter[0] = 0;
			pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
		पूर्ण अन्यथा अणु
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x0);
		पूर्ण

		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);

		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0); /* WiFi TRx Mask off */
		pBtCoexist->fBtcSetBtReg(pBtCoexist, BTC_BT_REG_RF, 0x3c, 0x01); /* BT TRx Mask off */

		अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT) अणु
			/* tell firmware "no antenna inverse" */
			H2C_Parameter[0] = 0;
		पूर्ण अन्यथा अणु
			/* tell firmware "antenna inverse" */
			H2C_Parameter[0] = 1;
		पूर्ण

		अगर (bUseExtSwitch) अणु
			/* ext चयन type */
			H2C_Parameter[1] = 1;
		पूर्ण अन्यथा अणु
			/* पूर्णांक चयन type */
			H2C_Parameter[1] = 0;
		पूर्ण
		pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
	पूर्ण

	/*  ext चयन setting */
	अगर (bUseExtSwitch) अणु
		अगर (bInitHwCfg) अणु
			/*  0x4c[23]= 0, 0x4c[24]= 1  Antenna control by WL/BT */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp &= ~BIT23;
			u4Tmp |= BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);
		पूर्ण

		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0); /*  fixed पूर्णांकernal चयन S1->WiFi, S0->BT */
		चयन (antPosType) अणु
		हाल BTC_ANT_WIFI_AT_MAIN:
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);	/*  ext चयन मुख्य at wअगरi */
			अवरोध;
		हाल BTC_ANT_WIFI_AT_AUX:
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);	/*  ext चयन aux at wअगरi */
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु /*  पूर्णांकernal चयन */
		अगर (bInitHwCfg) अणु
			/*  0x4c[23]= 0, 0x4c[24]= 1  Antenna control by WL/BT */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp |= BIT23;
			u4Tmp &= ~BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);
		पूर्ण

		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x64, 0x1, 0x0); /* fixed बाह्यal चयन S1->Main, S0->Aux */
		चयन (antPosType) अणु
		हाल BTC_ANT_WIFI_AT_MAIN:
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0); /*  fixed पूर्णांकernal चयन S1->WiFi, S0->BT */
			अवरोध;
		हाल BTC_ANT_WIFI_AT_AUX:
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280); /*  fixed पूर्णांकernal चयन S0->WiFi, S1->BT */
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_PsTdma(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, bool bTurnOn, u8 type
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		(
			"[BTCoex], %s turn %s PS TDMA, type =%d\n",
			(bForceExec ? "force to" : ""),
			(bTurnOn ? "ON" : "OFF"),
			type
		)
	);
	pCoexDm->bCurPsTdmaOn = bTurnOn;
	pCoexDm->curPsTdma = type;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], bPrePsTdmaOn = %d, bCurPsTdmaOn = %d!!\n",
				pCoexDm->bPrePsTdmaOn,
				pCoexDm->bCurPsTdmaOn
			)
		);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], prePsTdma = %d, curPsTdma = %d!!\n",
				pCoexDm->prePsTdma, pCoexDm->curPsTdma
			)
		);

		अगर (
			(pCoexDm->bPrePsTdmaOn == pCoexDm->bCurPsTdmaOn) &&
			(pCoexDm->prePsTdma == pCoexDm->curPsTdma)
		)
			वापस;
	पूर्ण

	अगर (bTurnOn) अणु
		चयन (type) अणु
		हाल 1:
		शेष:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0xe1, 0x90);
			अवरोध;
		हाल 2:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0xe1, 0x90);
			अवरोध;
		हाल 3:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1c, 0x3, 0xf1, 0x90);
			अवरोध;
		हाल 4:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x10, 0x03, 0xf1, 0x90);
			अवरोध;
		हाल 5:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0x60, 0x90);
			अवरोध;
		हाल 6:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0x60, 0x90);
			अवरोध;
		हाल 7:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1c, 0x3, 0x70, 0x90);
			अवरोध;
		हाल 8:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xa3, 0x10, 0x3, 0x70, 0x90);
			अवरोध;
		हाल 9:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0xe1, 0x90);
			अवरोध;
		हाल 10:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0xe1, 0x90);
			अवरोध;
		हाल 11:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0xa, 0xa, 0xe1, 0x90);
			अवरोध;
		हाल 12:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x5, 0x5, 0xe1, 0x90);
			अवरोध;
		हाल 13:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0x60, 0x90);
			अवरोध;
		हाल 14:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x12, 0x12, 0x60, 0x90);
			अवरोध;
		हाल 15:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0xa, 0xa, 0x60, 0x90);
			अवरोध;
		हाल 16:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x5, 0x5, 0x60, 0x90);
			अवरोध;
		हाल 17:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xa3, 0x2f, 0x2f, 0x60, 0x90);
			अवरोध;
		हाल 18:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x5, 0x5, 0xe1, 0x90);
			अवरोध;
		हाल 19:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x25, 0x25, 0xe1, 0x90);
			अवरोध;
		हाल 20:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x25, 0x25, 0x60, 0x90);
			अवरोध;
		हाल 21:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x15, 0x03, 0x70, 0x90);
			अवरोध;
		हाल 71:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0xe3, 0x1a, 0x1a, 0xe1, 0x90);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*  disable PS tdma */
		चयन (type) अणु
		हाल 0:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x40, 0x0);
			अवरोध;
		हाल 1:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x48, 0x0);
			अवरोध;
		शेष:
			halbtc8723b2ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x40, 0x0);
			अवरोध;
		पूर्ण
	पूर्ण

	/*  update pre state */
	pCoexDm->bPrePsTdmaOn = pCoexDm->bCurPsTdmaOn;
	pCoexDm->prePsTdma = pCoexDm->curPsTdma;
पूर्ण

अटल व्योम halbtc8723b2ant_CoexAllOff(काष्ठा btc_coexist *pBtCoexist)
अणु
	/*  fw all off */
	halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
	halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	/*  sw all off */
	halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
	halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

	/*  hw all off */
	/* pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0); */
	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम halbtc8723b2ant_InitCoexDm(काष्ठा btc_coexist *pBtCoexist)
अणु
	/*  क्रमce to reset coex mechanism */

	halbtc8723b2ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 1);
	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, FORCE_EXEC, 6);
	halbtc8723b2ant_DecBtPwr(pBtCoexist, FORCE_EXEC, 0);

	halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
	halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
पूर्ण

अटल व्योम halbtc8723b2ant_ActionBtInquiry(काष्ठा btc_coexist *pBtCoexist)
अणु
	bool bWअगरiConnected = false;
	bool bLowPwrDisable = true;

	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);

	अगर (bWअगरiConnected) अणु
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 3);
	पूर्ण अन्यथा अणु
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
	पूर्ण

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, FORCE_EXEC, 6);
	halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
	halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

	pCoexDm->bNeedRecover0x948 = true;
	pCoexDm->backup0x948 = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);

	halbtc8723b2ant_SetAntPath(pBtCoexist, BTC_ANT_WIFI_AT_AUX, false, false);
पूर्ण

अटल bool halbtc8723b2ant_IsCommonAction(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 btRssiState = BTC_RSSI_STATE_HIGH;
	bool bCommon = false, bWअगरiConnected = false, bWअगरiBusy = false;
	bool bBtHsOn = false, bLowPwrDisable = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);

	अगर (!bWअगरiConnected) अणु
		bLowPwrDisable = false;
		pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);
		halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi non-connected idle!!\n"));

		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
		halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

		halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
		halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

		bCommon = true;
	पूर्ण अन्यथा अणु
		अगर (BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus) अणु
			bLowPwrDisable = false;
			pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);
			halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi connected + BT non connected-idle!!\n"));

			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
			halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
			halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
			halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 0xb);
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

			bCommon = true;
		पूर्ण अन्यथा अगर (BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus) अणु
			bLowPwrDisable = true;
			pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);

			अगर (bBtHsOn)
				वापस false;

			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi connected + BT connected-idle!!\n"));
			halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
			halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
			halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);
			halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 0xb);
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);

			bCommon = true;
		पूर्ण अन्यथा अणु
			bLowPwrDisable = true;
			pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable);

			अगर (bWअगरiBusy) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi Connected-Busy + BT Busy!!\n"));
				bCommon = false;
			पूर्ण अन्यथा अणु
				अगर (bBtHsOn)
					वापस false;

				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi Connected-Idle + BT Busy!!\n"));
				btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);
				halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

				pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
				halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
				halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 21);
				halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 0xb);

				अगर (BTC_RSSI_HIGH(btRssiState))
					halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
				अन्यथा
					halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

				halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
				halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
				bCommon = true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस bCommon;
पूर्ण

अटल व्योम halbtc8723b2ant_TdmaDurationAdjust(
	काष्ठा btc_coexist *pBtCoexist, bool bScoHid, bool bTxPause, u8 maxInterval
)
अणु
	अटल s32 up, dn, m, n, WaitCount;
	s32 result;   /* 0: no change, +1: increase WiFi duration, -1: decrease WiFi duration */
	u8 retryCount = 0;

	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW, ("[BTCoex], TdmaDurationAdjust()\n"));

	अगर (!pCoexDm->bAutoTdmaAdjust) अणु
		pCoexDm->bAutoTdmaAdjust = true;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], first run TdmaDurationAdjust()!!\n"));
		अणु
			अगर (bScoHid) अणु
				अगर (bTxPause) अणु
					अगर (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(13);
					अन्यथा अगर (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					अन्यथा
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				पूर्ण अन्यथा अणु
					अगर (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(9);
					अन्यथा अगर (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					अन्यथा
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (bTxPause) अणु
					अगर (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
					अन्यथा अगर (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					अन्यथा
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				पूर्ण अन्यथा अणु
					अगर (maxInterval == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(1);
					अन्यथा अगर (maxInterval == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					अन्यथा
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				पूर्ण
			पूर्ण
		पूर्ण
		/*  */
		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		result = 0;
		WaitCount = 0;
	पूर्ण अन्यथा अणु
		/* acquire the BT TRx retry count from BT_Info byte2 */
		retryCount = pCoexSta->btRetryCnt;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], retryCount = %d\n", retryCount));
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], up =%d, dn =%d, m =%d, n =%d, WaitCount =%d\n",
				up, dn, m, n, WaitCount
			)
		);
		result = 0;
		WaitCount++;

		अगर (retryCount == 0) अणु /*  no retry in the last 2-second duration */
			up++;
			dn--;

			अगर (dn <= 0)
				dn = 0;

			अगर (up >= n) अणु /*  अगर ़ ःॉज n ो 2ॉई retry countॉज0, ो	्ऋडो/एWiFi duration */
				WaitCount = 0;
				n = 3;
				up = 0;
				dn = 0;
				result = 1;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], Increase wifi duration!!\n"));
			पूर्ण
		पूर्ण अन्यथा अगर (retryCount <= 3) अणु /*  <=3 retry in the last 2-second duration */
			up--;
			dn++;

			अगर (up <= 0)
				up = 0;

			अगर (dn == 2) अणु /*  अगर ़ ःॉज 2 ो 2ॉई retry count< 3, ो	्ऋडॉऋWiFi duration */
				अगर (WaitCount <= 2)
					m++; /*  ़डोdच ॉखोउोऊो leveldचऐdठो */
				अन्यथा
					m = 1;

				अगर (m >= 20) /* m ौ ोअईो ञ = 20 ' ौ ोअई120ॉई recheckौ/ोइ्ऋडौख WiFi duration. */
					m = 20;

				n = 3 * m;
				up = 0;
				dn = 0;
				WaitCount = 0;
				result = -1;
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], Decrease wifi duration for retryCounter<3!!\n"));
			पूर्ण
		पूर्ण अन्यथा अणु /* retry count > 3, ोऋ्इ1ौएँ retry count > 3, ो	्ऋडॉऋWiFi duration */
			अगर (WaitCount == 1)
				m++; /*  ़डोdच ॉखोउोऊो leveldचऐdठो */
			अन्यथा
				m = 1;

			अगर (m >= 20) /* m ौ ोअईो ञ = 20 ' ौ ोअई120ॉई recheckौ/ोइ्ऋडौख WiFi duration. */
				m = 20;

			n = 3 * m;
			up = 0;
			dn = 0;
			WaitCount = 0;
			result = -1;
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], Decrease wifi duration for retryCounter>3!!\n"));
		पूर्ण

		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], max Interval = %d\n", maxInterval));
		अगर (maxInterval == 1) अणु
			अगर (bTxPause) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 1\n"));

				अगर (pCoexDm->curPsTdma == 71)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
				अन्यथा अगर (pCoexDm->curPsTdma == 1)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
				अन्यथा अगर (pCoexDm->curPsTdma == 2)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
				अन्यथा अगर (pCoexDm->curPsTdma == 3)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				अन्यथा अगर (pCoexDm->curPsTdma == 4)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);

				अगर (pCoexDm->curPsTdma == 9)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(13);
				अन्यथा अगर (pCoexDm->curPsTdma == 10)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				अन्यथा अगर (pCoexDm->curPsTdma == 11)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				अन्यथा अगर (pCoexDm->curPsTdma == 12)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);

				अगर (result == -1) अणु
					अगर (pCoexDm->curPsTdma == 5)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					अन्यथा अगर (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);
					अन्यथा अगर (pCoexDm->curPsTdma == 13)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					अन्यथा अगर (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (pCoexDm->curPsTdma == 8)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					अन्यथा अगर (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(5);
					अन्यथा अगर (pCoexDm->curPsTdma == 16)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					अन्यथा अगर (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(13);
				पूर्ण
			पूर्ण अन्यथा अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 0\n"));
				अगर (pCoexDm->curPsTdma == 5)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(71);
				अन्यथा अगर (pCoexDm->curPsTdma == 6)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
				अन्यथा अगर (pCoexDm->curPsTdma == 7)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				अन्यथा अगर (pCoexDm->curPsTdma == 8)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);

				अगर (pCoexDm->curPsTdma == 13)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(9);
				अन्यथा अगर (pCoexDm->curPsTdma == 14)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				अन्यथा अगर (pCoexDm->curPsTdma == 15)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				अन्यथा अगर (pCoexDm->curPsTdma == 16)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);

				अगर (result == -1) अणु
					अगर (pCoexDm->curPsTdma == 71)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(1);
					अन्यथा अगर (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					अन्यथा अगर (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);
					अन्यथा अगर (pCoexDm->curPsTdma == 9)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					अन्यथा अगर (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (pCoexDm->curPsTdma == 4)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					अन्यथा अगर (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(1);
					अन्यथा अगर (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(71);
					अन्यथा अगर (pCoexDm->curPsTdma == 12)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					अन्यथा अगर (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(9);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (maxInterval == 2) अणु
			अगर (bTxPause) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 1\n"));
				अगर (pCoexDm->curPsTdma == 1)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
				अन्यथा अगर (pCoexDm->curPsTdma == 2)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
				अन्यथा अगर (pCoexDm->curPsTdma == 3)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				अन्यथा अगर (pCoexDm->curPsTdma == 4)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);

				अगर (pCoexDm->curPsTdma == 9)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				अन्यथा अगर (pCoexDm->curPsTdma == 10)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				अन्यथा अगर (pCoexDm->curPsTdma == 11)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				अन्यथा अगर (pCoexDm->curPsTdma == 12)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);

				अगर (result == -1) अणु
					अगर (pCoexDm->curPsTdma == 5)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					अन्यथा अगर (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);
					अन्यथा अगर (pCoexDm->curPsTdma == 13)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					अन्यथा अगर (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (pCoexDm->curPsTdma == 8)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					अन्यथा अगर (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(6);
					अन्यथा अगर (pCoexDm->curPsTdma == 16)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
					अन्यथा अगर (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(14);
				पूर्ण
			पूर्ण अन्यथा अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 0\n"));
				अगर (pCoexDm->curPsTdma == 5)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
				अन्यथा अगर (pCoexDm->curPsTdma == 6)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
				अन्यथा अगर (pCoexDm->curPsTdma == 7)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				अन्यथा अगर (pCoexDm->curPsTdma == 8)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);

				अगर (pCoexDm->curPsTdma == 13)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				अन्यथा अगर (pCoexDm->curPsTdma == 14)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				अन्यथा अगर (pCoexDm->curPsTdma == 15)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				अन्यथा अगर (pCoexDm->curPsTdma == 16)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);

				अगर (result == -1) अणु
					अगर (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					अन्यथा अगर (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);
					अन्यथा अगर (pCoexDm->curPsTdma == 9)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					अन्यथा अगर (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (pCoexDm->curPsTdma == 4)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					अन्यथा अगर (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(2);
					अन्यथा अगर (pCoexDm->curPsTdma == 12)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
					अन्यथा अगर (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(10);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (maxInterval == 3) अणु
			अगर (bTxPause) अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 1\n"));
				अगर (pCoexDm->curPsTdma == 1)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				अन्यथा अगर (pCoexDm->curPsTdma == 2)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				अन्यथा अगर (pCoexDm->curPsTdma == 3)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
				अन्यथा अगर (pCoexDm->curPsTdma == 4)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);

				अगर (pCoexDm->curPsTdma == 9)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				अन्यथा अगर (pCoexDm->curPsTdma == 10)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				अन्यथा अगर (pCoexDm->curPsTdma == 11)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				अन्यथा अगर (pCoexDm->curPsTdma == 12)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);

				अगर (result == -1) अणु
					अगर (pCoexDm->curPsTdma == 5)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(8);
					अन्यथा अगर (pCoexDm->curPsTdma == 13)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(16);
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (pCoexDm->curPsTdma == 8)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 7)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 6)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(7);
					अन्यथा अगर (pCoexDm->curPsTdma == 16)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 15)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
					अन्यथा अगर (pCoexDm->curPsTdma == 14)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(15);
				पूर्ण
			पूर्ण अन्यथा अणु
				BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], TxPause = 0\n"));
				अगर (pCoexDm->curPsTdma == 5)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				अन्यथा अगर (pCoexDm->curPsTdma == 6)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				अन्यथा अगर (pCoexDm->curPsTdma == 7)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
				अन्यथा अगर (pCoexDm->curPsTdma == 8)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);

				अगर (pCoexDm->curPsTdma == 13)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				अन्यथा अगर (pCoexDm->curPsTdma == 14)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				अन्यथा अगर (pCoexDm->curPsTdma == 15)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				अन्यथा अगर (pCoexDm->curPsTdma == 16)
					HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);

				अगर (result == -1) अणु
					अगर (pCoexDm->curPsTdma == 1)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(4);
					अन्यथा अगर (pCoexDm->curPsTdma == 9)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(12);
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (pCoexDm->curPsTdma == 4)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 3)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 2)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(3);
					अन्यथा अगर (pCoexDm->curPsTdma == 12)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 11)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
					अन्यथा अगर (pCoexDm->curPsTdma == 10)
						HAL_BTC8723B2ANT_DMA_DURATION_ADJUST(11);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/*  अगर current PsTdma not match with the recorded one (when scan, dhcp...), */
	/*  then we have to adjust it back to the previous record one. */
	अगर (pCoexDm->curPsTdma != pCoexDm->psTdmaDuAdjType) अणु
		bool bScan = false, bLink = false, bRoam = false;
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], PsTdma type mismatch!!!, curPsTdma =%d, recordPsTdma =%d\n",
				pCoexDm->curPsTdma,
				pCoexDm->psTdmaDuAdjType
			)
		);

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);

		अगर (!bScan && !bLink && !bRoam)
			halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, pCoexDm->psTdmaDuAdjType);
		अन्यथा अणु
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], roaming/link/scan is under progress, will adjust next time!!!\n"));
		पूर्ण
	पूर्ण
पूर्ण

/*  SCO only or SCO+PAN(HS) */
अटल व्योम halbtc8723b2ant_ActionSco(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 4);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);

	अगर (BTC_WIFI_BW_LEGACY == wअगरiBw) /* क्रम SCO quality at 11b/g mode */
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा  /* क्रम SCO quality & wअगरi perक्रमmance balance at 11n mode */
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 8);

	halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0); /* क्रम voice quality */

	/*  sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x4);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, true, 0x4);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x4);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, true, 0x4);
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम halbtc8723b2ant_ActionHid(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);

	अगर (BTC_WIFI_BW_LEGACY == wअगरiBw) /* क्रम HID at 11b/g mode */
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
	अन्यथा  /* क्रम HID quality & wअगरi perक्रमmance balance at 11n mode */
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 9);

	अगर (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	)
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
	अन्यथा
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 13);

	/*  sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* A2DP only / PAN(EDR) only/ A2DP+PAN(HS) */
अटल व्योम halbtc8723b2ant_ActionA2dp(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, wअगरiRssiState1, btRssiState;
	u32 wअगरiBw;
	u8 apNum = 0;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	wअगरiRssiState1 = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 1, 2, 40, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);

	/*  define the office environment */
	अगर (apNum >= 10 && BTC_RSSI_HIGH(wअगरiRssiState1)) अणु
		/* DbgPrपूर्णांक(" AP#>10(%d)\n", apNum); */
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
		halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);
		halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);

		/*  sw mechanism */
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
		अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, true, 0x18);
		पूर्ण
		वापस;
	पूर्ण

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);

	अगर (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	)
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, false, 1);
	अन्यथा
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, true, 1);

	/*  sw mechanism */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_ActionA2dpPanHs(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);

	halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, true, 2);

	/*  sw mechanism */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_ActionPanEdr(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 10);

	अगर (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	)
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 1);
	अन्यथा
		halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 5);

	/*  sw mechanism */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण


/* PAN(HS) only */
अटल व्योम halbtc8723b2ant_ActionPanHs(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);

	halbtc8723b2ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 1);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* PAN(EDR)+A2DP */
अटल व्योम halbtc8723b2ant_ActionPanEdrA2dp(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);

	अगर (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	) अणु
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 12);
		अगर (BTC_WIFI_BW_HT40 == wअगरiBw)
			halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, true, 3);
		अन्यथा
			halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, false, 3);
	पूर्ण अन्यथा अणु
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, false, true, 3);
	पूर्ण

	/*  sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, false, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_ActionPanEdrHid(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	अगर (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	) अणु
		अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
			halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 3);
			halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 11);
			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x780);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
			halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
			pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
		पूर्ण
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, false, 2);
	पूर्ण अन्यथा अणु
		halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);
		halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 11);
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, true, 2);
	पूर्ण

	/*  sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/*  HID+A2DP+PAN(EDR) */
अटल व्योम halbtc8723b2ant_ActionHidA2dpPanEdr(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x8);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(btRssiState))
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
	अन्यथा
		halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);

	अगर (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	) अणु
		अगर (BTC_WIFI_BW_HT40 == wअगरiBw)
			halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, true, 2);
		अन्यथा
			halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, false, 3);
	पूर्ण अन्यथा
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, true, 3);

	/*  sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_ActionHidA2dp(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 wअगरiRssiState, btRssiState;
	u32 wअगरiBw;
	u8 apNum = 0;

	wअगरiRssiState = halbtc8723b2ant_WअगरiRssiState(pBtCoexist, 0, 2, 15, 0);
	/* btRssiState = halbtc8723b2ant_BtRssiState(2, 29, 0); */
	btRssiState = halbtc8723b2ant_BtRssiState(3, 29, 37);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	halbtc8723b2ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, true, 0x5);

	halbtc8723b2ant_FwDacSwingLvl(pBtCoexist, NORMAL_EXEC, 6);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
	अगर (BTC_WIFI_BW_LEGACY == wअगरiBw) अणु
		अगर (BTC_RSSI_HIGH(btRssiState))
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		अन्यथा अगर (BTC_RSSI_MEDIUM(btRssiState))
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		अन्यथा
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अणु
		/*  only 802.11N mode we have to dec bt घातer to 4 degree */
		अगर (BTC_RSSI_HIGH(btRssiState)) अणु
			pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);
			/*  need to check ap Number of Not */
			अगर (apNum < 10)
				halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 4);
			अन्यथा
				halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		पूर्ण अन्यथा अगर (BTC_RSSI_MEDIUM(btRssiState))
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 2);
		अन्यथा
			halbtc8723b2ant_DecBtPwr(pBtCoexist, NORMAL_EXEC, 0);
	पूर्ण

	halbtc8723b2ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);

	अगर (
		(btRssiState == BTC_RSSI_STATE_HIGH) ||
		(btRssiState == BTC_RSSI_STATE_STAY_HIGH)
	)
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, false, 2);
	अन्यथा
		halbtc8723b2ant_TdmaDurationAdjust(pBtCoexist, true, true, 2);

	/*  sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरiBw) अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, true, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (
			(wअगरiRssiState == BTC_RSSI_STATE_HIGH) ||
			(wअगरiRssiState == BTC_RSSI_STATE_STAY_HIGH)
		) अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, true, false, false, 0x18);
		पूर्ण अन्यथा अणु
			halbtc8723b2ant_SwMechanism1(pBtCoexist, false, true, false, false);
			halbtc8723b2ant_SwMechanism2(pBtCoexist, false, false, false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_RunCoexistMechanism(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 algorithm = 0;

	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism() ===>\n"));

	अगर (pBtCoexist->bManualControl) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism(), return for Manual CTRL <===\n"));
		वापस;
	पूर्ण

	अगर (pCoexSta->bUnderIps) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], wifi is under IPS !!!\n"));
		वापस;
	पूर्ण

	algorithm = halbtc8723b2ant_ActionAlgorithm(pBtCoexist);
	अगर (pCoexSta->bC2hBtInquiryPage && (BT_8723B_2ANT_COEX_ALGO_PANHS != algorithm)) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BT is under inquiry/page scan !!\n"));
		halbtc8723b2ant_ActionBtInquiry(pBtCoexist);
		वापस;
	पूर्ण अन्यथा अणु
		अगर (pCoexDm->bNeedRecover0x948) अणु
			pCoexDm->bNeedRecover0x948 = false;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, pCoexDm->backup0x948);
		पूर्ण
	पूर्ण

	pCoexDm->curAlgorithm = algorithm;
	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Algorithm = %d\n", pCoexDm->curAlgorithm));

	अगर (halbtc8723b2ant_IsCommonAction(pBtCoexist)) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant common.\n"));
		pCoexDm->bAutoTdmaAdjust = false;
	पूर्ण अन्यथा अणु
		अगर (pCoexDm->curAlgorithm != pCoexDm->preAlgorithm) अणु
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE,
				(
					"[BTCoex], preAlgorithm =%d, curAlgorithm =%d\n",
					pCoexDm->preAlgorithm,
					pCoexDm->curAlgorithm
				)
			);
			pCoexDm->bAutoTdmaAdjust = false;
		पूर्ण


		चयन (pCoexDm->curAlgorithm) अणु
		हाल BT_8723B_2ANT_COEX_ALGO_SCO:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = SCO.\n"));
			halbtc8723b2ant_ActionSco(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_HID:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = HID.\n"));
			halbtc8723b2ant_ActionHid(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = A2DP.\n"));
			halbtc8723b2ant_ActionA2dp(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_A2DP_PANHS:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = A2DP+PAN(HS).\n"));
			halbtc8723b2ant_ActionA2dpPanHs(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANEDR:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = PAN(EDR).\n"));
			halbtc8723b2ant_ActionPanEdr(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANHS:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = HS mode.\n"));
			halbtc8723b2ant_ActionPanHs(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANEDR_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = PAN+A2DP.\n"));
			halbtc8723b2ant_ActionPanEdrA2dp(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANEDR_HID:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = PAN(EDR)+HID.\n"));
			halbtc8723b2ant_ActionPanEdrHid(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = HID+A2DP+PAN.\n"));
			halbtc8723b2ant_ActionHidA2dpPanEdr(pBtCoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_HID_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = HID+A2DP.\n"));
			halbtc8723b2ant_ActionHidA2dp(pBtCoexist);
			अवरोध;
		शेष:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action 2-Ant, algorithm = coexist All Off!!\n"));
			halbtc8723b2ant_CoexAllOff(pBtCoexist);
			अवरोध;
		पूर्ण
		pCoexDm->preAlgorithm = pCoexDm->curAlgorithm;
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b2ant_WअगरiOffHwCfg(काष्ठा btc_coexist *pBtCoexist)
अणु
	bool bIsInMpMode = false;
	u8 H2C_Parameter[2] = अणु0पूर्ण;
	u32 fwVer = 0;

	/*  set wlan_act to low */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

	pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x780); /* WiFi जाओ standby जबतक GNT_BT 0-->1 */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);
	अगर (fwVer >= 0x180000) अणु
		/* Use H2C to set GNT_BT to HIGH */
		H2C_Parameter[0] = 1;
		pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
	पूर्ण अन्यथा
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE, &bIsInMpMode);
	अगर (!bIsInMpMode)
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x0); /* BT select s0/s1 is controlled by BT */
	अन्यथा
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1); /* BT select s0/s1 is controlled by WiFi */
पूर्ण

अटल व्योम halbtc8723b2ant_InitHwConfig(काष्ठा btc_coexist *pBtCoexist, bool bBackUp)
अणु
	u8 u1Tmp = 0;

	BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], 2Ant Init HW Config!!\n"));

	/*  backup rf 0x1e value */
	pCoexDm->btRf0x1eBackup =
		pBtCoexist->fBtcGetRfReg(pBtCoexist, BTC_RF_A, 0x1e, 0xfffff);

	/*  0x790[5:0]= 0x5 */
	u1Tmp = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x790);
	u1Tmp &= 0xc0;
	u1Tmp |= 0x5;
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x790, u1Tmp);

	/* Antenna config */
	halbtc8723b2ant_SetAntPath(pBtCoexist, BTC_ANT_WIFI_AT_MAIN, true, false);

	/*  PTA parameter */
	halbtc8723b2ant_CoexTableWithType(pBtCoexist, FORCE_EXEC, 0);

	/*  Enable counter statistics */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0xc); /* 0x76e[3] = 1, WLAN_Act control by PTA */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x778, 0x3);
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x40, 0x20, 0x1);
पूर्ण

/*  */
/*  work around function start with wa_halbtc8723b2ant_ */
/*  */
/*  */
/*  बाह्य function start with EXhalbtc8723b2ant_ */
/*  */
व्योम EXhalbtc8723b2ant_PowerOnSetting(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_board_info *pBoardInfo = &pBtCoexist->boardInfo;
	u8 u1Tmp = 0x4; /* Set BIT2 by शेष since it's 2ant हाल */
	u16 u2Tmp = 0x0;

	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x67, 0x20);

	/*  enable BB, REG_SYS_FUNC_EN such that we can ग_लिखो 0x948 correctly. */
	u2Tmp = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0x2);
	pBtCoexist->fBtcWrite2Byte(pBtCoexist, 0x2, u2Tmp | BIT0 | BIT1);

	/*  set GRAN_BT = 1 */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);
	/*  set WLAN_ACT = 0 */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

	/*  */
	/*  S0 or S1 setting and Local रेजिस्टर setting(By the setting fw can get ant number, S0/S1, ... info) */
	/*  Local setting bit define */
	/* 	BIT0: "0" क्रम no antenna inverse; "1" क्रम antenna inverse */
	/* 	BIT1: "0" क्रम पूर्णांकernal चयन; "1" क्रम बाह्यal चयन */
	/* 	BIT2: "0" क्रम one antenna; "1" क्रम two antenna */
	/*  NOTE: here शेष all पूर्णांकernal चयन and 1-antenna ==> BIT1 = 0 and BIT2 = 0 */
	अगर (pBtCoexist->chipInterface == BTC_INTF_USB) अणु
		/*  fixed at S0 क्रम USB पूर्णांकerface */
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);

		u1Tmp |= 0x1;	/*  antenna inverse */
		pBtCoexist->fBtcWriteLocalReg1Byte(pBtCoexist, 0xfe08, u1Tmp);

		pBoardInfo->btdmAntPos = BTC_ANTENNA_AT_AUX_PORT;
	पूर्ण अन्यथा अणु
		/*  क्रम PCIE and SDIO पूर्णांकerface, we check efuse 0xc3[6] */
		अगर (pBoardInfo->singleAntPath == 0) अणु
			/*  set to S1 */
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280);
			pBoardInfo->btdmAntPos = BTC_ANTENNA_AT_MAIN_PORT;
		पूर्ण अन्यथा अगर (pBoardInfo->singleAntPath == 1) अणु
			/*  set to S0 */
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);
			u1Tmp |= 0x1;	/*  antenna inverse */
			pBoardInfo->btdmAntPos = BTC_ANTENNA_AT_AUX_PORT;
		पूर्ण

		अगर (pBtCoexist->chipInterface == BTC_INTF_PCI)
			pBtCoexist->fBtcWriteLocalReg1Byte(pBtCoexist, 0x384, u1Tmp);
		अन्यथा अगर (pBtCoexist->chipInterface == BTC_INTF_SDIO)
			pBtCoexist->fBtcWriteLocalReg1Byte(pBtCoexist, 0x60, u1Tmp);
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b2ant_InitHwConfig(काष्ठा btc_coexist *pBtCoexist, bool bWअगरiOnly)
अणु
	halbtc8723b2ant_InitHwConfig(pBtCoexist, true);
पूर्ण

व्योम EXhalbtc8723b2ant_InitCoexDm(काष्ठा btc_coexist *pBtCoexist)
अणु
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], Coex Mechanism Init!!\n"));

	halbtc8723b2ant_InitCoexDm(pBtCoexist);
पूर्ण

व्योम EXhalbtc8723b2ant_DisplayCoexInfo(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_board_info *pBoardInfo = &pBtCoexist->boardInfo;
	काष्ठा btc_stack_info *pStackInfo = &pBtCoexist->stackInfo;
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	u8 *cliBuf = pBtCoexist->cliBuf;
	u8 u1Tmp[4], i, btInfoExt, psTdmaCase = 0;
	u32 u4Tmp[4];
	bool bRoam = false, bScan = false, bLink = false, bWअगरiUnder5G = false;
	bool bBtHsOn = false, bWअगरiBusy = false;
	s32 wअगरiRssi = 0, btHsRssi = 0;
	u32 wअगरiBw, wअगरiTrafficDir, faOfdm, faCck;
	u8 wअगरiDot11Chnl, wअगरiHsChnl;
	u32 fwVer = 0, btPatchVer = 0;
	u8 apNum = 0;

	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n ============[BT Coexist info]============");
	CL_PRINTF(cliBuf);

	अगर (pBtCoexist->bManualControl) अणु
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n ============[Under Manual Control]============");
		CL_PRINTF(cliBuf);
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n ==========================================");
		CL_PRINTF(cliBuf);
	पूर्ण

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d ", "Ant PG number/ Ant mechanism:", \
		pBoardInfo->pgAntNum,
		pBoardInfo->btdmAntNum
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s / %d", "BT stack/ hci ext ver", \
		(pStackInfo->bProfileNotअगरied ? "Yes" : "No"),
		pStackInfo->hciVersion
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_BT_PATCH_VER, &btPatchVer);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d_%x/ 0x%x/ 0x%x(%d)", "CoexVer/ FwVer/ PatchVer", \
		GLCoexVerDate8723b2Ant, GLCoexVer8723b2Ant, fwVer, btPatchVer, btPatchVer);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_WIFI_DOT11_CHNL, &wअगरiDot11Chnl);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_WIFI_HS_CHNL, &wअगरiHsChnl);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d / %d(%d)", "Dot11 channel / HsChnl(HsMode)", \
		wअगरiDot11Chnl,
		wअगरiHsChnl,
		bBtHsOn
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %02x %02x %02x ", "H2C Wifi inform bt chnl Info", \
		pCoexDm->wअगरiChnlInfo[0],
		pCoexDm->wअगरiChnlInfo[1],
		pCoexDm->wअगरiChnlInfo[2]
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_WIFI_RSSI, &wअगरiRssi);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_HS_RSSI, &btHsRssi);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d", "Wifi rssi/ HS rssi/ AP#", \
		wअगरiRssi,
		btHsRssi,
		apNum
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d ", "Wifi bLink/ bRoam/ bScan", \
		bLink,
		bRoam,
		bScan
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_UNDER_5G, &bWअगरiUnder5G);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION, &wअगरiTrafficDir);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s / %s/ %s ", "Wifi status", \
		(bWअगरiUnder5G ? "5G" : "2.4G"),
		((BTC_WIFI_BW_LEGACY == wअगरiBw) ? "Legacy" : (((BTC_WIFI_BW_HT40 == wअगरiBw) ? "HT40" : "HT20"))),
		((!bWअगरiBusy) ? "idle" : ((BTC_WIFI_TRAFFIC_TX == wअगरiTrafficDir) ? "uplink" : "downlink"))
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = [%s/ %d/ %d] ", "BT [status/ rssi/ retryCnt]", \
		((pBtCoexist->btInfo.bBtDisabled) ? ("disabled") : ((pCoexSta->bC2hBtInquiryPage) ? ("inquiry/page scan") : ((BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus) ? "non-connected idle" :
		((BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus) ? "connected-idle" : "busy")))),
		pCoexSta->btRssi,
		pCoexSta->btRetryCnt
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d / %d / %d / %d", "SCO/HID/PAN/A2DP", \
		pBtLinkInfo->bScoExist,
		pBtLinkInfo->bHidExist,
		pBtLinkInfo->bPanExist,
		pBtLinkInfo->bA2dpExist
	);
	CL_PRINTF(cliBuf);
	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_BT_LINK_INFO);

	btInfoExt = pCoexSta->btInfoExt;
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s", "BT Info A2DP rate", \
		(btInfoExt & BIT0) ? "Basic rate" : "EDR rate"
	);
	CL_PRINTF(cliBuf);

	क्रम (i = 0; i < BT_INFO_SRC_8723B_2ANT_MAX; i++) अणु
		अगर (pCoexSta->btInfoC2hCnt[i]) अणु
			CL_SPRINTF(
				cliBuf,
				BT_TMP_BUF_SIZE,
				"\r\n %-35s = %02x %02x %02x %02x %02x %02x %02x(%d)", GLBtInfoSrc8723b2Ant[i], \
				pCoexSta->btInfoC2h[i][0],
				pCoexSta->btInfoC2h[i][1],
				pCoexSta->btInfoC2h[i][2],
				pCoexSta->btInfoC2h[i][3],
				pCoexSta->btInfoC2h[i][4],
				pCoexSta->btInfoC2h[i][5],
				pCoexSta->btInfoC2h[i][6],
				pCoexSta->btInfoC2hCnt[i]
			);
			CL_PRINTF(cliBuf);
		पूर्ण
	पूर्ण

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s/%s", "PS state, IPS/LPS", \
		((pCoexSta->bUnderIps ? "IPS ON" : "IPS OFF")),
		((pCoexSta->bUnderLps ? "LPS ON" : "LPS OFF"))
	);
	CL_PRINTF(cliBuf);
	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD);

	/*  Sw mechanism */
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s", "============[Sw mechanism]============"
	);
	CL_PRINTF(cliBuf);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d ", "SM1[ShRf/ LpRA/ LimDig]", \
		pCoexDm->bCurRfRxLpfShrink,
		pCoexDm->bCurLowPenaltyRa,
		pCoexDm->bLimitedDig
	);
	CL_PRINTF(cliBuf);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d(0x%x) ",
		"SM2[AgcT/ AdcB/ SwDacSwing(lvl)]", \
		pCoexDm->bCurAgcTableEn,
		pCoexDm->bCurAdcBackOff,
		pCoexDm->bCurDacSwingOn,
		pCoexDm->curDacSwingLvl
	);
	CL_PRINTF(cliBuf);

	/*  Fw mechanism */
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s", "============[Fw mechanism]============");
	CL_PRINTF(cliBuf);

	psTdmaCase = pCoexDm->curPsTdma;
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %02x %02x %02x %02x %02x case-%d (auto:%d)", "PS TDMA", \
		pCoexDm->psTdmaPara[0],
		pCoexDm->psTdmaPara[1],
		pCoexDm->psTdmaPara[2],
		pCoexDm->psTdmaPara[3],
		pCoexDm->psTdmaPara[4],
		psTdmaCase, pCoexDm->bAutoTdmaAdjust
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d ", "DecBtPwr/ IgnWlanAct", \
		pCoexDm->curBtDecPwrLvl,
		pCoexDm->bCurIgnoreWlanAct
	);
	CL_PRINTF(cliBuf);

	/*  Hw setting */
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s", "============[Hw setting]============");
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x", "RF-A, 0x1e initVal", \
		pCoexDm->btRf0x1eBackup
	);
	CL_PRINTF(cliBuf);

	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x778);
	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x880);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x", "0x778/0x880[29:25]", \
		u1Tmp[0],
		(u4Tmp[0] & 0x3e000000) >> 25
	);
	CL_PRINTF(cliBuf);


	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x67);
	u1Tmp[1] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x765);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "0x948/ 0x67[5] / 0x765", \
		u4Tmp[0],
		((u1Tmp[0] & 0x20) >> 5),
		u1Tmp[1]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x92c);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x930);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x944);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "0x92c[1:0]/ 0x930[7:0]/0x944[1:0]", \
		u4Tmp[0] & 0x3,
		u4Tmp[1] & 0xff,
		u4Tmp[2] & 0x3
	);
	CL_PRINTF(cliBuf);


	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x39);
	u1Tmp[1] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x40);
	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
	u1Tmp[2] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x64);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x", "0x38[11]/0x40/0x4c[24:23]/0x64[0]", \
		((u1Tmp[0] & 0x8) >> 3),
		u1Tmp[1],
		((u4Tmp[0] & 0x01800000) >> 23),
		u1Tmp[2] & 0x1
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x550);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x522);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x", "0x550(bcn ctrl)/0x522", \
		u4Tmp[0],
		u1Tmp[0]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xc50);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x49c);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x", "0xc50(dig)/0x49c(null-drop)", \
		u4Tmp[0] & 0xff,
		u1Tmp[0]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xda0);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xda4);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xda8);
	u4Tmp[3] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xcf0);

	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0xa5b);
	u1Tmp[1] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0xa5c);

	faOfdm =
		((u4Tmp[0] & 0xffff0000) >> 16) +
		((u4Tmp[1] & 0xffff0000) >> 16) +
		(u4Tmp[1] & 0xffff) +  (u4Tmp[2] & 0xffff) + \
		((u4Tmp[3] & 0xffff0000) >> 16) +
		(u4Tmp[3] & 0xffff);

	faCck = (u1Tmp[0] << 8) + u1Tmp[1];

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "OFDM-CCA/OFDM-FA/CCK-FA", \
		u4Tmp[0] & 0xffff,
		faOfdm,
		faCck
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c0);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c4);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c8);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x6cc);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x", "0x6c0/0x6c4/0x6c8/0x6cc(coexTable)", \
		u4Tmp[0],
		u4Tmp[1],
		u4Tmp[2],
		u1Tmp[0]
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d", "0x770(high-pri rx/tx)", \
		pCoexSta->highPriorityRx,
		pCoexSta->highPriorityTx
	);
	CL_PRINTF(cliBuf);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d", "0x774(low-pri rx/tx)", \
		pCoexSta->lowPriorityRx,
		pCoexSta->lowPriorityTx
	);
	CL_PRINTF(cliBuf);

	halbtc8723b2ant_MonitorBtCtr(pBtCoexist);
	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_COEX_STATISTICS);
पूर्ण


व्योम EXhalbtc8723b2ant_IpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	अगर (BTC_IPS_ENTER == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS ENTER notify\n"));
		pCoexSta->bUnderIps = true;
		halbtc8723b2ant_WअगरiOffHwCfg(pBtCoexist);
		halbtc8723b2ant_IgnoreWlanAct(pBtCoexist, FORCE_EXEC, true);
		halbtc8723b2ant_CoexAllOff(pBtCoexist);
	पूर्ण अन्यथा अगर (BTC_IPS_LEAVE == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS LEAVE notify\n"));
		pCoexSta->bUnderIps = false;
		halbtc8723b2ant_InitHwConfig(pBtCoexist, false);
		halbtc8723b2ant_InitCoexDm(pBtCoexist);
		halbtc8723b2ant_QueryBtInfo(pBtCoexist);
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b2ant_LpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	अगर (BTC_LPS_ENABLE == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], LPS ENABLE notify\n"));
		pCoexSta->bUnderLps = true;
	पूर्ण अन्यथा अगर (BTC_LPS_DISABLE == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], LPS DISABLE notify\n"));
		pCoexSta->bUnderLps = false;
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b2ant_ScanNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	अगर (BTC_SCAN_START == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], SCAN START notify\n"));
	पूर्ण अन्यथा अगर (BTC_SCAN_FINISH == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], SCAN FINISH notify\n"));
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b2ant_ConnectNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	अगर (BTC_ASSOCIATE_START == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT START notify\n"));
	पूर्ण अन्यथा अगर (BTC_ASSOCIATE_FINISH == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT FINISH notify\n"));
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b2ant_MediaStatusNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	u8 H2C_Parameter[3] = अणु0पूर्ण;
	u32 wअगरiBw;
	u8 wअगरiCentralChnl;
	u8 apNum = 0;

	अगर (BTC_MEDIA_CONNECT == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], MEDIA connect notify\n"));
	पूर्ण अन्यथा अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], MEDIA disconnect notify\n"));
	पूर्ण

	/*  only 2.4G we need to inक्रमm bt the chnl mask */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL, &wअगरiCentralChnl);
	अगर ((BTC_MEDIA_CONNECT == type) && (wअगरiCentralChnl <= 14)) अणु
		H2C_Parameter[0] = 0x1;
		H2C_Parameter[1] = wअगरiCentralChnl;
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
		अगर (BTC_WIFI_BW_HT40 == wअगरiBw)
			H2C_Parameter[2] = 0x30;
		अन्यथा अणु
			pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_AP_NUM, &apNum);
			अगर (apNum < 10)
				H2C_Parameter[2] = 0x30;
			अन्यथा
				H2C_Parameter[2] = 0x20;
		पूर्ण
	पूर्ण

	pCoexDm->wअगरiChnlInfo[0] = H2C_Parameter[0];
	pCoexDm->wअगरiChnlInfo[1] = H2C_Parameter[1];
	pCoexDm->wअगरiChnlInfo[2] = H2C_Parameter[2];

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], FW write 0x66 = 0x%x\n",
			H2C_Parameter[0] << 16 | H2C_Parameter[1] << 8 | H2C_Parameter[2]
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x66, 3, H2C_Parameter);
पूर्ण

व्योम EXhalbtc8723b2ant_SpecialPacketNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	अगर (type == BTC_PACKET_DHCP) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], DHCP Packet notify\n"));
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b2ant_BtInfoNotअगरy(
	काष्ठा btc_coexist *pBtCoexist, u8 *पंचांगpBuf, u8 length
)
अणु
	u8 	btInfo = 0;
	u8 	i, rspSource = 0;
	bool bBtBusy = false, bLimitedDig = false;
	bool bWअगरiConnected = false;

	pCoexSta->bC2hBtInfoReqSent = false;

	rspSource = पंचांगpBuf[0] & 0xf;
	अगर (rspSource >= BT_INFO_SRC_8723B_2ANT_MAX)
		rspSource = BT_INFO_SRC_8723B_2ANT_WIFI_FW;

	pCoexSta->btInfoC2hCnt[rspSource]++;

	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Bt info[%d], length =%d, hex data =[", rspSource, length));
	क्रम (i = 0; i < length; i++) अणु
		pCoexSta->btInfoC2h[rspSource][i] = पंचांगpBuf[i];
		अगर (i == 1)
			btInfo = पंचांगpBuf[i];

		अगर (i == length - 1) अणु
			BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("0x%02x]\n", पंचांगpBuf[i]));
		पूर्ण अन्यथा अणु
			BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("0x%02x, ", पंचांगpBuf[i]));
		पूर्ण
	पूर्ण

	अगर (pBtCoexist->bManualControl) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), return for Manual CTRL<===\n"));
		वापस;
	पूर्ण

	अगर (BT_INFO_SRC_8723B_2ANT_WIFI_FW != rspSource) अणु
		pCoexSta->btRetryCnt = pCoexSta->btInfoC2h[rspSource][2] & 0xf; /* [3:0] */

		pCoexSta->btRssi = pCoexSta->btInfoC2h[rspSource][3] * 2 + 10;

		pCoexSta->btInfoExt = pCoexSta->btInfoC2h[rspSource][4];

		pCoexSta->bBtTxRxMask = (pCoexSta->btInfoC2h[rspSource][2] & 0x40);
		pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_BT_TX_RX_MASK, &pCoexSta->bBtTxRxMask);
		अगर (pCoexSta->bBtTxRxMask) अणु
			/* BT पूर्णांकo is responded by BT FW and BT RF REG 0x3C != 0x01 => Need to चयन BT TRx Mask */
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Switch BT TRx Mask since BT RF REG 0x3C != 0x01\n"));
			pBtCoexist->fBtcSetBtReg(pBtCoexist, BTC_BT_REG_RF, 0x3c, 0x01);
		पूर्ण

		/*  Here we need to resend some wअगरi info to BT */
		/*  because bt is reset and loss of the info. */
		अगर ((pCoexSta->btInfoExt & BIT1)) अणु
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BT ext info bit1 check, send wifi BW&Chnl to BT!!\n"));
			pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);

			अगर (bWअगरiConnected)
				EXhalbtc8723b2ant_MediaStatusNotअगरy(pBtCoexist, BTC_MEDIA_CONNECT);
			अन्यथा
				EXhalbtc8723b2ant_MediaStatusNotअगरy(pBtCoexist, BTC_MEDIA_DISCONNECT);
		पूर्ण

		अगर ((pCoexSta->btInfoExt & BIT3)) अणु
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n"));
			halbtc8723b2ant_IgnoreWlanAct(pBtCoexist, FORCE_EXEC, false);
		पूर्ण अन्यथा अणु
			/*  BT alपढ़ोy NOT ignore Wlan active, करो nothing here. */
		पूर्ण
	पूर्ण

	/*  check BIT2 first ==> check अगर bt is under inquiry or page scan */
	अगर (btInfo & BT_INFO_8723B_2ANT_B_INQ_PAGE)
		pCoexSta->bC2hBtInquiryPage = true;
	अन्यथा
		pCoexSta->bC2hBtInquiryPage = false;

	/*  set link exist status */
	अगर (!(btInfo & BT_INFO_8723B_2ANT_B_CONNECTION)) अणु
		pCoexSta->bBtLinkExist = false;
		pCoexSta->bPanExist = false;
		pCoexSta->bA2dpExist = false;
		pCoexSta->bHidExist = false;
		pCoexSta->bScoExist = false;
	पूर्ण अन्यथा अणु /*  connection exists */
		pCoexSta->bBtLinkExist = true;
		अगर (btInfo & BT_INFO_8723B_2ANT_B_FTP)
			pCoexSta->bPanExist = true;
		अन्यथा
			pCoexSta->bPanExist = false;
		अगर (btInfo & BT_INFO_8723B_2ANT_B_A2DP)
			pCoexSta->bA2dpExist = true;
		अन्यथा
			pCoexSta->bA2dpExist = false;
		अगर (btInfo & BT_INFO_8723B_2ANT_B_HID)
			pCoexSta->bHidExist = true;
		अन्यथा
			pCoexSta->bHidExist = false;
		अगर (btInfo & BT_INFO_8723B_2ANT_B_SCO_ESCO)
			pCoexSta->bScoExist = true;
		अन्यथा
			pCoexSta->bScoExist = false;
	पूर्ण

	halbtc8723b2ant_UpdateBtLinkInfo(pBtCoexist);

	अगर (!(btInfo & BT_INFO_8723B_2ANT_B_CONNECTION)) अणु
		pCoexDm->btStatus = BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n"));
	पूर्ण अन्यथा अगर (btInfo == BT_INFO_8723B_2ANT_B_CONNECTION)	अणु /*  connection exists but no busy */
		pCoexDm->btStatus = BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n"));
	पूर्ण अन्यथा अगर (
		(btInfo & BT_INFO_8723B_2ANT_B_SCO_ESCO) ||
		(btInfo & BT_INFO_8723B_2ANT_B_SCO_BUSY)
	) अणु
		pCoexDm->btStatus = BT_8723B_2ANT_BT_STATUS_SCO_BUSY;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT SCO busy!!!\n"));
	पूर्ण अन्यथा अगर (btInfo & BT_INFO_8723B_2ANT_B_ACL_BUSY) अणु
		pCoexDm->btStatus = BT_8723B_2ANT_BT_STATUS_ACL_BUSY;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT ACL busy!!!\n"));
	पूर्ण अन्यथा अणु
		pCoexDm->btStatus = BT_8723B_2ANT_BT_STATUS_MAX;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n"));
	पूर्ण

	अगर (
		(BT_8723B_2ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_2ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_2ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
	) अणु
		bBtBusy = true;
		bLimitedDig = true;
	पूर्ण अन्यथा अणु
		bBtBusy = false;
		bLimitedDig = false;
	पूर्ण

	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bBtBusy);

	pCoexDm->bLimitedDig = bLimitedDig;
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_BT_LIMITED_DIG, &bLimitedDig);

	halbtc8723b2ant_RunCoexistMechanism(pBtCoexist);
पूर्ण

व्योम EXhalbtc8723b2ant_HaltNotअगरy(काष्ठा btc_coexist *pBtCoexist)
अणु
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Halt notify\n"));

	halbtc8723b2ant_WअगरiOffHwCfg(pBtCoexist);
	pBtCoexist->fBtcSetBtReg(pBtCoexist, BTC_BT_REG_RF, 0x3c, 0x15); /* BT जाओ standby जबतक GNT_BT 1-->0 */
	halbtc8723b2ant_IgnoreWlanAct(pBtCoexist, FORCE_EXEC, true);

	EXhalbtc8723b2ant_MediaStatusNotअगरy(pBtCoexist, BTC_MEDIA_DISCONNECT);
पूर्ण

व्योम EXhalbtc8723b2ant_PnpNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 pnpState)
अणु
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify\n"));

	अगर (BTC_WIFI_PNP_SLEEP == pnpState) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify to SLEEP\n"));
	पूर्ण अन्यथा अगर (BTC_WIFI_PNP_WAKE_UP == pnpState) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify to WAKE UP\n"));
		halbtc8723b2ant_InitHwConfig(pBtCoexist, false);
		halbtc8723b2ant_InitCoexDm(pBtCoexist);
		halbtc8723b2ant_QueryBtInfo(pBtCoexist);
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b2ant_Periodical(काष्ठा btc_coexist *pBtCoexist)
अणु
	अटल u8 disVerInfoCnt;
	u32 fwVer = 0, btPatchVer = 0;

	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], ==========================Periodical ===========================\n"));

	अगर (disVerInfoCnt <= 5) अणु
		disVerInfoCnt += 1;
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ****************************************************************\n"));
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_BT_PATCH_VER, &btPatchVer);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], CoexVer/ FwVer/ PatchVer = %d_%x/ 0x%x/ 0x%x(%d)\n", \
			GLCoexVerDate8723b2Ant, GLCoexVer8723b2Ant, fwVer, btPatchVer, btPatchVer));
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ****************************************************************\n"));
	पूर्ण

	अगर (
		halbtc8723b2ant_IsWअगरiStatusChanged(pBtCoexist) ||
		pCoexDm->bAutoTdmaAdjust
	)
		halbtc8723b2ant_RunCoexistMechanism(pBtCoexist);
पूर्ण
