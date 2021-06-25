<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#समावेश "Mp_Precomp.h"

/*  Global variables, these are अटल variables */
अटल काष्ठा coex_dm_8723b_1ant GLCoexDm8723b1Ant;
अटल काष्ठा coex_dm_8723b_1ant *pCoexDm = &GLCoexDm8723b1Ant;
अटल काष्ठा coex_sta_8723b_1ant GLCoexSta8723b1Ant;
अटल काष्ठा coex_sta_8723b_1ant *pCoexSta = &GLCoexSta8723b1Ant;

अटल स्थिर अक्षर *स्थिर GLBtInfoSrc8723b1Ant[] = अणु
	"BT Info[wifi fw]",
	"BT Info[bt rsp]",
	"BT Info[bt auto report]",
पूर्ण;

अटल u32 GLCoexVerDate8723b1Ant = 20140507;
अटल u32 GLCoexVer8723b1Ant = 0x4e;

/*  local function proto type अगर needed */
/*  local function start with halbtc8723b1ant_ */
अटल u8 halbtc8723b1ant_BtRssiState(
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
			अगर (btRssi >= (rssiThresh + BTC_RSSI_COEX_THRESH_TOL_8723B_1ANT)) अणु

				btRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state switch to High\n")
				);
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state stay at Low\n")
				);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (btRssi < rssiThresh) अणु
				btRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state switch to Low\n")
				);
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state stay at High\n")
				);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (levelNum == 3) अणु
		अगर (rssiThresh > rssiThresh1) अणु
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_BT_RSSI_STATE,
				("[BTCoex], BT Rssi thresh error!!\n")
			);
			वापस pCoexSta->preBtRssiState;
		पूर्ण

		अगर (
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_LOW) ||
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_STAY_LOW)
		) अणु
			अगर (btRssi >= (rssiThresh + BTC_RSSI_COEX_THRESH_TOL_8723B_1ANT)) अणु
				btRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state switch to Medium\n")
				);
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_LOW;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state stay at Low\n")
				);
			पूर्ण
		पूर्ण अन्यथा अगर (
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_MEDIUM) ||
			(pCoexSta->preBtRssiState == BTC_RSSI_STATE_STAY_MEDIUM)
		) अणु
			अगर (btRssi >= (rssiThresh1 + BTC_RSSI_COEX_THRESH_TOL_8723B_1ANT)) अणु
				btRssiState = BTC_RSSI_STATE_HIGH;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state switch to High\n")
				);
			पूर्ण अन्यथा अगर (btRssi < rssiThresh) अणु
				btRssiState = BTC_RSSI_STATE_LOW;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state switch to Low\n")
				);
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_MEDIUM;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state stay at Medium\n")
				);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (btRssi < rssiThresh1) अणु
				btRssiState = BTC_RSSI_STATE_MEDIUM;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state switch to Medium\n")
				);
			पूर्ण अन्यथा अणु
				btRssiState = BTC_RSSI_STATE_STAY_HIGH;
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_BT_RSSI_STATE,
					("[BTCoex], BT Rssi state stay at High\n")
				);
			पूर्ण
		पूर्ण
	पूर्ण

	pCoexSta->preBtRssiState = btRssiState;

	वापस btRssiState;
पूर्ण

अटल व्योम halbtc8723b1ant_UpdateRaMask(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u32 disRateMask
)
अणु
	pCoexDm->curRaMask = disRateMask;

	अगर (bForceExec || (pCoexDm->preRaMask != pCoexDm->curRaMask))
		pBtCoexist->fBtcSet(
			pBtCoexist,
			BTC_SET_ACT_UPDATE_RAMASK,
			&pCoexDm->curRaMask
		);
	pCoexDm->preRaMask = pCoexDm->curRaMask;
पूर्ण

अटल व्योम halbtc8723b1ant_AutoRateFallbackRetry(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 type
)
अणु
	bool bWअगरiUnderBMode = false;

	pCoexDm->curArfrType = type;

	अगर (bForceExec || (pCoexDm->preArfrType != pCoexDm->curArfrType)) अणु
		चयन (pCoexDm->curArfrType) अणु
		हाल 0:	/*  normal mode */
			pBtCoexist->fBtcWrite4Byte(
				pBtCoexist, 0x430, pCoexDm->backupArfrCnt1
			);
			pBtCoexist->fBtcWrite4Byte(
				pBtCoexist, 0x434, pCoexDm->backupArfrCnt2
			);
			अवरोध;
		हाल 1:
			pBtCoexist->fBtcGet(
				pBtCoexist, BTC_GET_BL_WIFI_UNDER_B_MODE, &bWअगरiUnderBMode
			);
			अगर (bWअगरiUnderBMode) अणु
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x430, 0x0);
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x434, 0x01010101);
			पूर्ण अन्यथा अणु
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x430, 0x0);
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x434, 0x04030201);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pCoexDm->preArfrType = pCoexDm->curArfrType;
पूर्ण

अटल व्योम halbtc8723b1ant_RetryLimit(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 type
)
अणु
	pCoexDm->curRetryLimitType = type;

	अगर (
		bForceExec ||
		(pCoexDm->preRetryLimitType != pCoexDm->curRetryLimitType)
	) अणु
		चयन (pCoexDm->curRetryLimitType) अणु
		हाल 0:	/*  normal mode */
			pBtCoexist->fBtcWrite2Byte(
				pBtCoexist, 0x42a, pCoexDm->backupRetryLimit
			);
			अवरोध;
		हाल 1:	/*  retry limit =8 */
			pBtCoexist->fBtcWrite2Byte(pBtCoexist, 0x42a, 0x0808);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pCoexDm->preRetryLimitType = pCoexDm->curRetryLimitType;
पूर्ण

अटल व्योम halbtc8723b1ant_AmpduMaxTime(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 type
)
अणु
	pCoexDm->curAmpduTimeType = type;

	अगर (
		bForceExec || (pCoexDm->preAmpduTimeType != pCoexDm->curAmpduTimeType)
	) अणु
		चयन (pCoexDm->curAmpduTimeType) अणु
		हाल 0:	/*  normal mode */
			pBtCoexist->fBtcWrite1Byte(
				pBtCoexist, 0x456, pCoexDm->backupAmpduMaxTime
			);
			अवरोध;
		हाल 1:	/*  AMPDU timw = 0x38 * 32us */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x456, 0x38);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	pCoexDm->preAmpduTimeType = pCoexDm->curAmpduTimeType;
पूर्ण

अटल व्योम halbtc8723b1ant_LimitedTx(
	काष्ठा btc_coexist *pBtCoexist,
	bool bForceExec,
	u8 raMaskType,
	u8 arfrType,
	u8 retryLimitType,
	u8 ampduTimeType
)
अणु
	चयन (raMaskType) अणु
	हाल 0:	/*  normal mode */
		halbtc8723b1ant_UpdateRaMask(pBtCoexist, bForceExec, 0x0);
		अवरोध;
	हाल 1:	/*  disable cck 1/2 */
		halbtc8723b1ant_UpdateRaMask(pBtCoexist, bForceExec, 0x00000003);
		अवरोध;
	हाल 2:	/*  disable cck 1/2/5.5, ofdm 6/9/12/18/24, mcs 0/1/2/3/4 */
		halbtc8723b1ant_UpdateRaMask(pBtCoexist, bForceExec, 0x0001f1f7);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	halbtc8723b1ant_AutoRateFallbackRetry(pBtCoexist, bForceExec, arfrType);
	halbtc8723b1ant_RetryLimit(pBtCoexist, bForceExec, retryLimitType);
	halbtc8723b1ant_AmpduMaxTime(pBtCoexist, bForceExec, ampduTimeType);
पूर्ण

अटल व्योम halbtc8723b1ant_LimitedRx(
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
	pBtCoexist->fBtcSet(
		pBtCoexist, BTC_SET_BL_TO_REJ_AP_AGG_PKT, &bRejectRxAgg
	);
	/*  decide BT control aggregation buf size or not */
	pBtCoexist->fBtcSet(
		pBtCoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE, &bBtCtrlRxAggSize
	);
	/*  aggregation buf size, only work when BT control Rx aggregation size. */
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_U1_AGG_BUF_SIZE, &rxAggSize);
	/*  real update aggregation setting */
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_AGGREGATE_CTRL, शून्य);


पूर्ण

अटल व्योम halbtc8723b1ant_QueryBtInfo(काष्ठा btc_coexist *pBtCoexist)
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

अटल व्योम halbtc8723b1ant_MonitorBtCtr(काष्ठा btc_coexist *pBtCoexist)
अणु
	u32 regHPTxRx, regLPTxRx, u4Tmp;
	u32 regHPTx = 0, regHPRx = 0, regLPTx = 0, regLPRx = 0;
	अटल u8 NumOfBtCounterChk;

       /* to aव्योम 0x76e[3] = 1 (WLAN_Act control by PTA) during IPS */
	/* अगर (! (pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x76e) & 0x8)) */

	अगर (pCoexSta->bUnderIps) अणु
		pCoexSta->highPriorityTx = 65535;
		pCoexSta->highPriorityRx = 65535;
		pCoexSta->lowPriorityTx = 65535;
		pCoexSta->lowPriorityRx = 65535;
		वापस;
	पूर्ण

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

	अगर ((pCoexSta->lowPriorityTx >= 1050) && (!pCoexSta->bC2hBtInquiryPage))
		pCoexSta->popEventCnt++;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE,
		(
			"[BTCoex], Hi-Pri Rx/Tx: %d/%d, Lo-Pri Rx/Tx: %d/%d\n",
			regHPRx,
			regHPTx,
			regLPRx,
			regLPTx
		)
	);

	/*  reset counter */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0xc);

	अगर ((regHPTx == 0) && (regHPRx == 0) && (regLPTx == 0) && (regLPRx == 0)) अणु
		NumOfBtCounterChk++;
		अगर (NumOfBtCounterChk >= 3) अणु
			halbtc8723b1ant_QueryBtInfo(pBtCoexist);
			NumOfBtCounterChk = 0;
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम halbtc8723b1ant_MonitorWiFiCtr(काष्ठा btc_coexist *pBtCoexist)
अणु
	s32	wअगरiRssi = 0;
	bool bWअगरiBusy = false, bWअगरiUnderBMode = false;
	अटल u8 nCCKLockCounter;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_S4_WIFI_RSSI, &wअगरiRssi);
	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_BL_WIFI_UNDER_B_MODE, &bWअगरiUnderBMode
	);

	अगर (pCoexSta->bUnderIps) अणु
		pCoexSta->nCRCOK_CCK = 0;
		pCoexSta->nCRCOK_11g = 0;
		pCoexSta->nCRCOK_11n = 0;
		pCoexSta->nCRCOK_11nAgg = 0;

		pCoexSta->nCRCErr_CCK = 0;
		pCoexSta->nCRCErr_11g = 0;
		pCoexSta->nCRCErr_11n = 0;
		pCoexSta->nCRCErr_11nAgg = 0;
	पूर्ण अन्यथा अणु
		pCoexSta->nCRCOK_CCK	= pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xf88);
		pCoexSta->nCRCOK_11g	= pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf94);
		pCoexSta->nCRCOK_11n	= pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf90);
		pCoexSta->nCRCOK_11nAgg = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xfb8);

		pCoexSta->nCRCErr_CCK	 = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xf84);
		pCoexSta->nCRCErr_11g	 = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf96);
		pCoexSta->nCRCErr_11n	 = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xf92);
		pCoexSta->nCRCErr_11nAgg = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0xfba);
	पूर्ण


	/* reset counter */
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0xf16, 0x1, 0x1);
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0xf16, 0x1, 0x0);

	अगर (bWअगरiBusy && (wअगरiRssi >= 30) && !bWअगरiUnderBMode) अणु
		अगर (
			(pCoexDm->btStatus == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) ||
			(pCoexDm->btStatus == BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) ||
			(pCoexDm->btStatus == BT_8723B_1ANT_BT_STATUS_SCO_BUSY)
		) अणु
			अगर (
				pCoexSta->nCRCOK_CCK > (
					pCoexSta->nCRCOK_11g +
					pCoexSta->nCRCOK_11n +
					pCoexSta->nCRCOK_11nAgg
				)
			) अणु
				अगर (nCCKLockCounter < 5)
				 nCCKLockCounter++;
			पूर्ण अन्यथा अणु
				अगर (nCCKLockCounter > 0)
				 nCCKLockCounter--;
			पूर्ण

		पूर्ण अन्यथा अणु
			अगर (nCCKLockCounter > 0)
			  nCCKLockCounter--;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (nCCKLockCounter > 0)
			nCCKLockCounter--;
	पूर्ण

	अगर (!pCoexSta->bPreCCKLock) अणु

		अगर (nCCKLockCounter >= 5)
		 pCoexSta->bCCKLock = true;
		अन्यथा
		 pCoexSta->bCCKLock = false;
	पूर्ण अन्यथा अणु
		अगर (nCCKLockCounter == 0)
		 pCoexSta->bCCKLock = false;
		अन्यथा
		 pCoexSta->bCCKLock = true;
	पूर्ण

	pCoexSta->bPreCCKLock =  pCoexSta->bCCKLock;


पूर्ण

अटल bool halbtc8723b1ant_IsWअगरiStatusChanged(काष्ठा btc_coexist *pBtCoexist)
अणु
	अटल bool	bPreWअगरiBusy, bPreUnder4way, bPreBtHsOn;
	bool bWअगरiBusy = false, bUnder4way = false, bBtHsOn = false;
	bool bWअगरiConnected = false;

	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected
	);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS, &bUnder4way
	);

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

अटल व्योम halbtc8723b1ant_UpdateBtLinkInfo(काष्ठा btc_coexist *pBtCoexist)
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

अटल u8 halbtc8723b1ant_ActionAlgorithm(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bBtHsOn = false;
	u8 algorithm = BT_8723B_1ANT_COEX_ALGO_UNDEFINED;
	u8 numOfDअगरfProfile = 0;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);

	अगर (!pBtLinkInfo->bBtLinkExist) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], No BT link exists!!!\n")
		);
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
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE,
				("[BTCoex], BT Profile = SCO only\n")
			);
			algorithm = BT_8723B_1ANT_COEX_ALGO_SCO;
		पूर्ण अन्यथा अणु
			अगर (pBtLinkInfo->bHidExist) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], BT Profile = HID only\n")
				);
				algorithm = BT_8723B_1ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bA2dpExist) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], BT Profile = A2DP only\n")
				);
				algorithm = BT_8723B_1ANT_COEX_ALGO_A2DP;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = PAN(HS) only\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANHS;
				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = PAN(EDR) only\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (numOfDअगरfProfile == 2) अणु
		अगर (pBtLinkInfo->bScoExist) अणु
			अगर (pBtLinkInfo->bHidExist) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], BT Profile = SCO + HID\n")
				);
				algorithm = BT_8723B_1ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bA2dpExist) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], BT Profile = SCO + A2DP ==> SCO\n")
				);
				algorithm = BT_8723B_1ANT_COEX_ALGO_SCO;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = SCO + PAN(HS)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = SCO + PAN(EDR)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (pBtLinkInfo->bHidExist && pBtLinkInfo->bA2dpExist) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], BT Profile = HID + A2DP\n")
				);
				algorithm = BT_8723B_1ANT_COEX_ALGO_HID_A2DP;
			पूर्ण अन्यथा अगर (pBtLinkInfo->bHidExist && pBtLinkInfo->bPanExist) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = HID + PAN(HS)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = HID + PAN(EDR)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist && pBtLinkInfo->bA2dpExist) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = A2DP + PAN(HS)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_A2DP_PANHS;
				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = A2DP + PAN(EDR)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANEDR_A2DP;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (numOfDअगरfProfile == 3) अणु
		अगर (pBtLinkInfo->bScoExist) अणु
			अगर (pBtLinkInfo->bHidExist && pBtLinkInfo->bA2dpExist) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], BT Profile = SCO + HID + A2DP ==> HID\n")
				);
				algorithm = BT_8723B_1ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (
				pBtLinkInfo->bHidExist && pBtLinkInfo->bPanExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BT Profile = SCO + HID + PAN(HS)\n"));
					algorithm = BT_8723B_1ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BT Profile = SCO + HID + PAN(EDR)\n"));
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist && pBtLinkInfo->bA2dpExist) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BT Profile = SCO + A2DP + PAN(HS)\n"));
					algorithm = BT_8723B_1ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = SCO + A2DP + PAN(EDR) ==> HID\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (
				pBtLinkInfo->bHidExist &&
				pBtLinkInfo->bPanExist &&
				pBtLinkInfo->bA2dpExist
			) अणु
				अगर (bBtHsOn) अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = HID + A2DP + PAN(HS)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = HID + A2DP + PAN(EDR)\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_HID_A2DP_PANEDR;
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
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], Error!!! BT Profile = SCO + HID + A2DP + PAN(HS)\n")
					);

				पूर्ण अन्यथा अणु
					BTC_PRINT(
						BTC_MSG_ALGORITHM,
						ALGO_TRACE,
						("[BTCoex], BT Profile = SCO + HID + A2DP + PAN(EDR) ==>PAN(EDR)+HID\n")
					);
					algorithm = BT_8723B_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस algorithm;
पूर्ण

अटल व्योम halbtc8723b1ant_SetSwPenaltyTxRateAdaptive(
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

अटल व्योम halbtc8723b1ant_LowPenaltyRa(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, bool bLowPenaltyRa
)
अणु
	pCoexDm->bCurLowPenaltyRa = bLowPenaltyRa;

	अगर (!bForceExec) अणु
		अगर (pCoexDm->bPreLowPenaltyRa == pCoexDm->bCurLowPenaltyRa)
			वापस;
	पूर्ण
	halbtc8723b1ant_SetSwPenaltyTxRateAdaptive(
		pBtCoexist, pCoexDm->bCurLowPenaltyRa
	);

	pCoexDm->bPreLowPenaltyRa = pCoexDm->bCurLowPenaltyRa;
पूर्ण

अटल व्योम halbtc8723b1ant_SetCoexTable(
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

अटल व्योम halbtc8723b1ant_CoexTable(
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
			"[BTCoex], %s write Coex Table 0x6c0 = 0x%x, 0x6c4 = 0x%x, 0x6cc = 0x%x\n",
			(bForceExec ? "force to" : ""),
			val0x6c0, val0x6c4, val0x6cc
		)
	);
	pCoexDm->curVal0x6c0 = val0x6c0;
	pCoexDm->curVal0x6c4 = val0x6c4;
	pCoexDm->curVal0x6c8 = val0x6c8;
	pCoexDm->curVal0x6cc = val0x6cc;

	अगर (!bForceExec) अणु
		अगर (
			(pCoexDm->preVal0x6c0 == pCoexDm->curVal0x6c0) &&
		    (pCoexDm->preVal0x6c4 == pCoexDm->curVal0x6c4) &&
		    (pCoexDm->preVal0x6c8 == pCoexDm->curVal0x6c8) &&
		    (pCoexDm->preVal0x6cc == pCoexDm->curVal0x6cc)
		)
			वापस;
	पूर्ण

	halbtc8723b1ant_SetCoexTable(
		pBtCoexist, val0x6c0, val0x6c4, val0x6c8, val0x6cc
	);

	pCoexDm->preVal0x6c0 = pCoexDm->curVal0x6c0;
	pCoexDm->preVal0x6c4 = pCoexDm->curVal0x6c4;
	pCoexDm->preVal0x6c8 = pCoexDm->curVal0x6c8;
	pCoexDm->preVal0x6cc = pCoexDm->curVal0x6cc;
पूर्ण

अटल व्योम halbtc8723b1ant_CoexTableWithType(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 type
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE,
		("[BTCoex], ********** CoexTable(%d) **********\n", type)
	);

	pCoexSta->nCoexTableType = type;

	चयन (type) अणु
	हाल 0:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0x55555555, 0x55555555, 0xffffff, 0x3
		);
		अवरोध;
	हाल 1:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0x55555555, 0x5a5a5a5a, 0xffffff, 0x3
		);
		अवरोध;
	हाल 2:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0x5a5a5a5a, 0x5a5a5a5a, 0xffffff, 0x3
		);
		अवरोध;
	हाल 3:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0xaaaa5555, 0xaaaa5a5a, 0xffffff, 0x3
		);
		अवरोध;
	हाल 4:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0x55555555, 0xaaaa5a5a, 0xffffff, 0x3
		);
		अवरोध;
	हाल 5:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0x5a5a5a5a, 0xaaaa5a5a, 0xffffff, 0x3
		);
		अवरोध;
	हाल 6:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0x55555555, 0xaaaaaaaa, 0xffffff, 0x3
		);
		अवरोध;
	हाल 7:
		halbtc8723b1ant_CoexTable(
			pBtCoexist, bForceExec, 0xaaaaaaaa, 0xaaaaaaaa, 0xffffff, 0x3
		);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_SetFwIgnoreWlanAct(
	काष्ठा btc_coexist *pBtCoexist, bool bEnable
)
अणु
	u8 H2C_Parameter[1] = अणु0पूर्ण;

	अगर (bEnable)
		H2C_Parameter[0] |= BIT0; /* function enable */

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

अटल व्योम halbtc8723b1ant_IgnoreWlanAct(
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
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], bPreIgnoreWlanAct = %d, bCurIgnoreWlanAct = %d!!\n",
				pCoexDm->bPreIgnoreWlanAct,
				pCoexDm->bCurIgnoreWlanAct
			)
		);

		अगर (pCoexDm->bPreIgnoreWlanAct == pCoexDm->bCurIgnoreWlanAct)
			वापस;
	पूर्ण
	halbtc8723b1ant_SetFwIgnoreWlanAct(pBtCoexist, bEnable);

	pCoexDm->bPreIgnoreWlanAct = pCoexDm->bCurIgnoreWlanAct;
पूर्ण

अटल व्योम halbtc8723b1ant_SetLpsRpwm(
	काष्ठा btc_coexist *pBtCoexist, u8 lpsVal, u8 rpwmVal
)
अणु
	u8 lps = lpsVal;
	u8 rpwm = rpwmVal;

	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_U1_LPS_VAL, &lps);
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_U1_RPWM_VAL, &rpwm);
पूर्ण

अटल व्योम halbtc8723b1ant_LpsRpwm(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, u8 lpsVal, u8 rpwmVal
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		(
			"[BTCoex], %s set lps/rpwm = 0x%x/0x%x\n",
			(bForceExec ? "force to" : ""),
			lpsVal,
			rpwmVal
		)
	);
	pCoexDm->curLps = lpsVal;
	pCoexDm->curRpwm = rpwmVal;

	अगर (!bForceExec) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			(
				"[BTCoex], LPS-RxBeaconMode = 0x%x , LPS-RPWM = 0x%x!!\n",
				pCoexDm->curLps,
				pCoexDm->curRpwm
			)
		);

		अगर (
			(pCoexDm->preLps == pCoexDm->curLps) &&
			(pCoexDm->preRpwm == pCoexDm->curRpwm)
		) अणु
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE_FW_DETAIL,
				(
					"[BTCoex], LPS-RPWM_Last = 0x%x , LPS-RPWM_Now = 0x%x!!\n",
					pCoexDm->preRpwm,
					pCoexDm->curRpwm
				)
			);

			वापस;
		पूर्ण
	पूर्ण
	halbtc8723b1ant_SetLpsRpwm(pBtCoexist, lpsVal, rpwmVal);

	pCoexDm->preLps = pCoexDm->curLps;
	pCoexDm->preRpwm = pCoexDm->curRpwm;
पूर्ण

अटल व्योम halbtc8723b1ant_SwMechanism(
	काष्ठा btc_coexist *pBtCoexist, bool bLowPenaltyRA
)
अणु
	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_BT_MONITOR,
		("[BTCoex], SM[LpRA] = %d\n", bLowPenaltyRA)
	);

	halbtc8723b1ant_LowPenaltyRa(pBtCoexist, NORMAL_EXEC, bLowPenaltyRA);
पूर्ण

अटल व्योम halbtc8723b1ant_SetAntPath(
	काष्ठा btc_coexist *pBtCoexist, u8 antPosType, bool bInitHwCfg, bool bWअगरiOff
)
अणु
	काष्ठा btc_board_info *pBoardInfo = &pBtCoexist->boardInfo;
	u32 fwVer = 0, u4Tmp = 0, cntBtCalChk = 0;
	bool bPgExtSwitch = false;
	bool bUseExtSwitch = false;
	bool bIsInMpMode = false;
	u8 H2C_Parameter[2] = अणु0पूर्ण, u1Tmp = 0;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_EXT_SWITCH, &bPgExtSwitch);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer); /*  [31:16]=fw ver, [15:0]=fw sub ver */

	अगर ((fwVer > 0 && fwVer < 0xc0000) || bPgExtSwitch)
		bUseExtSwitch = true;

	अगर (bInitHwCfg) अणु
		pBtCoexist->fBtcSetRfReg(pBtCoexist, BTC_RF_A, 0x1, 0xfffff, 0x780); /* WiFi TRx Mask on */
		pBtCoexist->fBtcSetBtReg(pBtCoexist, BTC_BT_REG_RF, 0x3c, 0x15); /* BT TRx Mask on */

		अगर (fwVer >= 0x180000) अणु
			/* Use H2C to set GNT_BT to HIGH */
			H2C_Parameter[0] = 1;
			pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
		पूर्ण अन्यथा /*  set grant_bt to high */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);

		/* set wlan_act control by PTA */
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1); /* BT select s0/s1 is controlled by WiFi */

		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x39, 0x8, 0x1);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x974, 0xff);
		pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x944, 0x3, 0x3);
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x930, 0x77);
	पूर्ण अन्यथा अगर (bWअगरiOff) अणु
		अगर (fwVer >= 0x180000) अणु
			/* Use H2C to set GNT_BT to HIGH */
			H2C_Parameter[0] = 1;
			pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
		पूर्ण अन्यथा /*  set grant_bt to high */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x18);

		/* set wlan_act to always low */
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0x4);

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE, &bIsInMpMode);
		अगर (!bIsInMpMode)
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x0); /* BT select s0/s1 is controlled by BT */
		अन्यथा
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x67, 0x20, 0x1); /* BT select s0/s1 is controlled by WiFi */

		/*  0x4c[24:23]= 00, Set Antenna control by BT_RFE_CTRL	BT Venकरोr 0xac = 0xf002 */
		u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
		u4Tmp &= ~BIT23;
		u4Tmp &= ~BIT24;
		pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);
	पूर्ण अन्यथा अणु
		/* Use H2C to set GNT_BT to LOW */
		अगर (fwVer >= 0x180000) अणु
			अगर (pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x765) != 0) अणु
				H2C_Parameter[0] = 0;
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x6E, 1, H2C_Parameter);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*  BT calibration check */
			जबतक (cntBtCalChk <= 20) अणु
				u1Tmp = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x49d);
				cntBtCalChk++;

				अगर (u1Tmp & BIT0) अणु
					BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ########### BT is calibrating (wait cnt =%d) ###########\n", cntBtCalChk));
					mdelay(50);
				पूर्ण अन्यथा अणु
					BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ********** BT is NOT calibrating (wait cnt =%d)**********\n", cntBtCalChk));
					अवरोध;
				पूर्ण
			पूर्ण

			/*  set grant_bt to PTA */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x765, 0x0);
		पूर्ण

		अगर (pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x76e) != 0xc)
			/* set wlan_act control by PTA */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x76e, 0xc);
	पूर्ण

	अगर (bUseExtSwitch) अणु
		अगर (bInitHwCfg) अणु
			/*  0x4c[23]= 0, 0x4c[24]= 1  Antenna control by WL/BT */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp &= ~BIT23;
			u4Tmp |= BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);

			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0); /*  fixed पूर्णांकernal चयन S1->WiFi, S0->BT */

			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT) अणु
				/* tell firmware "no antenna inverse" */
				H2C_Parameter[0] = 0;
				H2C_Parameter[1] = 1;  /* ext चयन type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			पूर्ण अन्यथा अणु
				/* tell firmware "antenna inverse" */
				H2C_Parameter[0] = 1;
				H2C_Parameter[1] = 1;  /* ext चयन type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			पूर्ण
		पूर्ण


		/*  ext चयन setting */
		चयन (antPosType) अणु
		हाल BTC_ANT_PATH_WIFI:
			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);
			अन्यथा
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);
			अवरोध;
		हाल BTC_ANT_PATH_BT:
			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);
			अन्यथा
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);
			अवरोध;
		शेष:
		हाल BTC_ANT_PATH_PTA:
			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x1);
			अन्यथा
				pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x92c, 0x3, 0x2);
			अवरोध;
		पूर्ण

	पूर्ण अन्यथा अणु
		अगर (bInitHwCfg) अणु
			/*  0x4c[23]= 1, 0x4c[24]= 0  Antenna control by 0x64 */
			u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x4c);
			u4Tmp |= BIT23;
			u4Tmp &= ~BIT24;
			pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x4c, u4Tmp);

			/* Fix Ext चयन Main->S1, Aux->S0 */
			pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x64, 0x1, 0x0);

			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT) अणु

				/* tell firmware "no antenna inverse" */
				H2C_Parameter[0] = 0;
				H2C_Parameter[1] = 0;  /* पूर्णांकernal चयन type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			पूर्ण अन्यथा अणु

				/* tell firmware "antenna inverse" */
				H2C_Parameter[0] = 1;
				H2C_Parameter[1] = 0;  /* पूर्णांकernal चयन type */
				pBtCoexist->fBtcFillH2c(pBtCoexist, 0x65, 2, H2C_Parameter);
			पूर्ण
		पूर्ण


		/*  पूर्णांकernal चयन setting */
		चयन (antPosType) अणु
		हाल BTC_ANT_PATH_WIFI:
			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);
			अन्यथा
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280);
			अवरोध;
		हाल BTC_ANT_PATH_BT:
			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x280);
			अन्यथा
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x0);
			अवरोध;
		शेष:
		हाल BTC_ANT_PATH_PTA:
			अगर (pBoardInfo->btdmAntPos == BTC_ANTENNA_AT_MAIN_PORT)
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x200);
			अन्यथा
				pBtCoexist->fBtcWrite4Byte(pBtCoexist, 0x948, 0x80);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_SetFwPstdma(
	काष्ठा btc_coexist *pBtCoexist, u8 byte1, u8 byte2, u8 byte3, u8 byte4, u8 byte5
)
अणु
	u8 H2C_Parameter[5] = अणु0पूर्ण;
	u8 realByte1 = byte1, realByte5 = byte5;
	bool bApEnable = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE, &bApEnable);

	अगर (bApEnable) अणु
		अगर (byte1 & BIT4 && !(byte1 & BIT5)) अणु
			BTC_PRINT(
				BTC_MSG_INTERFACE,
				INTF_NOTIFY,
				("[BTCoex], FW for 1Ant AP mode\n")
			);
			realByte1 &= ~BIT4;
			realByte1 |= BIT5;

			realByte5 |= BIT5;
			realByte5 &= ~BIT6;
		पूर्ण
	पूर्ण

	H2C_Parameter[0] = realByte1;
	H2C_Parameter[1] = byte2;
	H2C_Parameter[2] = byte3;
	H2C_Parameter[3] = byte4;
	H2C_Parameter[4] = realByte5;

	pCoexDm->psTdmaPara[0] = realByte1;
	pCoexDm->psTdmaPara[1] = byte2;
	pCoexDm->psTdmaPara[2] = byte3;
	pCoexDm->psTdmaPara[3] = byte4;
	pCoexDm->psTdmaPara[4] = realByte5;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW_EXEC,
		(
			"[BTCoex], PS-TDMA H2C cmd = 0x%x%08x\n",
			H2C_Parameter[0],
			H2C_Parameter[1] << 24 |
			H2C_Parameter[2] << 16 |
			H2C_Parameter[3] << 8 |
			H2C_Parameter[4]
		)
	);

	pBtCoexist->fBtcFillH2c(pBtCoexist, 0x60, 5, H2C_Parameter);
पूर्ण


अटल व्योम halbtc8723b1ant_PsTdma(
	काष्ठा btc_coexist *pBtCoexist, bool bForceExec, bool bTurnOn, u8 type
)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bWअगरiBusy = false;
	u8 rssiAdjustVal = 0;
	u8 psTdmaByte4Val = 0x50, psTdmaByte0Val = 0x51, psTdmaByte3Val =  0x10;
	s8 nWiFiDurationAdjust = 0x0;
	/* u32 		fwVer = 0; */

	/* BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW, ("[BTCoex], %s turn %s PS TDMA, type =%d\n", */
	/* 	(bForceExec? "force to":""), (bTurnOn? "ON":"OFF"), type)); */
	pCoexDm->bCurPsTdmaOn = bTurnOn;
	pCoexDm->curPsTdma = type;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);

	अगर (pCoexDm->bCurPsTdmaOn) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			(
				"[BTCoex], ********** TDMA(on, %d) **********\n",
				pCoexDm->curPsTdma
			)
		);
	पूर्ण अन्यथा अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			(
				"[BTCoex], ********** TDMA(off, %d) **********\n",
				pCoexDm->curPsTdma
			)
		);
	पूर्ण

	अगर (!bForceExec) अणु
		अगर (
			(pCoexDm->bPrePsTdmaOn == pCoexDm->bCurPsTdmaOn) &&
			(pCoexDm->prePsTdma == pCoexDm->curPsTdma)
		)
			वापस;
	पूर्ण

	अगर (pCoexSta->nScanAPNum <= 5)
		nWiFiDurationAdjust = 5;
	अन्यथा अगर  (pCoexSta->nScanAPNum >= 40)
		nWiFiDurationAdjust = -15;
	अन्यथा अगर  (pCoexSta->nScanAPNum >= 20)
		nWiFiDurationAdjust = -10;

	अगर (!pCoexSta->bForceLpsOn) अणु /* only क्रम A2DP-only हाल 1/2/9/11 */
		psTdmaByte0Val = 0x61;  /* no null-pkt */
		psTdmaByte3Val = 0x11; /*  no tx-छोड़ो at BT-slot */
		psTdmaByte4Val = 0x10; /*  0x778 = d/1 toggle */
	पूर्ण


	अगर (bTurnOn) अणु
		अगर (pBtLinkInfo->bSlaveRole)
			psTdmaByte4Val = psTdmaByte4Val | 0x1;  /* 0x778 = 0x1 at wअगरi slot (no blocking BT Low-Pri pkts) */


		चयन (type) अणु
		शेष:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x51, 0x1a, 0x1a, 0x0, psTdmaByte4Val
			);
			अवरोध;
		हाल 1:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist,
				psTdmaByte0Val,
				0x3a + nWiFiDurationAdjust,
				0x03,
				psTdmaByte3Val,
				psTdmaByte4Val
			);
			अवरोध;
		हाल 2:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist,
				psTdmaByte0Val,
				0x2d + nWiFiDurationAdjust,
				0x03,
				psTdmaByte3Val,
				psTdmaByte4Val
			);
			अवरोध;
		हाल 3:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x51, 0x1d, 0x1d, 0x0, 0x10
			);
			अवरोध;
		हाल 4:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x93, 0x15, 0x3, 0x14, 0x0
			);
			अवरोध;
		हाल 5:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x61, 0x15, 0x3, 0x11, 0x10
			);
			अवरोध;
		हाल 6:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x61, 0x20, 0x3, 0x11, 0x11
			);
			अवरोध;
		हाल 7:
			halbtc8723b1ant_SetFwPstdma(pBtCoexist, 0x13, 0xc, 0x5, 0x0, 0x0);
			अवरोध;
		हाल 8:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x93, 0x25, 0x3, 0x10, 0x0
			);
			अवरोध;
		हाल 9:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist,
				psTdmaByte0Val,
				0x21,
				0x3,
				psTdmaByte3Val,
				psTdmaByte4Val
			);
			अवरोध;
		हाल 10:
			halbtc8723b1ant_SetFwPstdma(pBtCoexist, 0x13, 0xa, 0xa, 0x0, 0x40);
			अवरोध;
		हाल 11:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist,
				psTdmaByte0Val,
				0x21,
				0x03,
				psTdmaByte3Val,
				psTdmaByte4Val
			);
			अवरोध;
		हाल 12:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x51, 0x0a, 0x0a, 0x0, 0x50
			);
			अवरोध;
		हाल 13:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x51, 0x12, 0x12, 0x0, 0x10
			);
			अवरोध;
		हाल 14:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x51, 0x21, 0x3, 0x10, psTdmaByte4Val
			);
			अवरोध;
		हाल 15:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x13, 0xa, 0x3, 0x8, 0x0
			);
			अवरोध;
		हाल 16:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x93, 0x15, 0x3, 0x10, 0x0
			);
			अवरोध;
		हाल 18:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x93, 0x25, 0x3, 0x10, 0x0
			);
			अवरोध;
		हाल 20:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x61, 0x3f, 0x03, 0x11, 0x10

			);
			अवरोध;
		हाल 21:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x61, 0x25, 0x03, 0x11, 0x11
			);
			अवरोध;
		हाल 22:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x61, 0x25, 0x03, 0x11, 0x10
			);
			अवरोध;
		हाल 23:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xe3, 0x25, 0x3, 0x31, 0x18
			);
			अवरोध;
		हाल 24:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xe3, 0x15, 0x3, 0x31, 0x18
			);
			अवरोध;
		हाल 25:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xe3, 0xa, 0x3, 0x31, 0x18
			);
			अवरोध;
		हाल 26:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xe3, 0xa, 0x3, 0x31, 0x18
			);
			अवरोध;
		हाल 27:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xe3, 0x25, 0x3, 0x31, 0x98
			);
			अवरोध;
		हाल 28:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x69, 0x25, 0x3, 0x31, 0x0
			);
			अवरोध;
		हाल 29:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xab, 0x1a, 0x1a, 0x1, 0x10
			);
			अवरोध;
		हाल 30:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x51, 0x30, 0x3, 0x10, 0x10
			);
			अवरोध;
		हाल 31:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xd3, 0x1a, 0x1a, 0x0, 0x58
			);
			अवरोध;
		हाल 32:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x61, 0x35, 0x3, 0x11, 0x11
			);
			अवरोध;
		हाल 33:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xa3, 0x25, 0x3, 0x30, 0x90
			);
			अवरोध;
		हाल 34:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x53, 0x1a, 0x1a, 0x0, 0x10
			);
			अवरोध;
		हाल 35:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x63, 0x1a, 0x1a, 0x0, 0x10
			);
			अवरोध;
		हाल 36:
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0xd3, 0x12, 0x3, 0x14, 0x50
			);
			अवरोध;
		हाल 40: /*  SoftAP only with no sta associated, BT disable , TDMA mode क्रम घातer saving */
			/* here softap mode screen off will cost 70-80mA क्रम phone */
			halbtc8723b1ant_SetFwPstdma(
				pBtCoexist, 0x23, 0x18, 0x00, 0x10, 0x24
			);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु

		/*  disable PS tdma */
		चयन (type) अणु
		हाल 8: /* PTA Control */
			halbtc8723b1ant_SetFwPstdma(pBtCoexist, 0x8, 0x0, 0x0, 0x0, 0x0);
			halbtc8723b1ant_SetAntPath(
				pBtCoexist, BTC_ANT_PATH_PTA, false, false
			);
			अवरोध;
		हाल 0:
		शेष:  /* Software control, Antenna at BT side */
			halbtc8723b1ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x0, 0x0);
			halbtc8723b1ant_SetAntPath(
				pBtCoexist, BTC_ANT_PATH_BT, false, false
			);
			अवरोध;
		हाल 9:   /* Software control, Antenna at WiFi side */
			halbtc8723b1ant_SetFwPstdma(pBtCoexist, 0x0, 0x0, 0x0, 0x0, 0x0);
			halbtc8723b1ant_SetAntPath(
				pBtCoexist, BTC_ANT_PATH_WIFI, false, false
			);
			अवरोध;
		पूर्ण
	पूर्ण

	rssiAdjustVal = 0;
	pBtCoexist->fBtcSet(
		pBtCoexist, BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE, &rssiAdjustVal
	);

	/*  update pre state */
	pCoexDm->bPrePsTdmaOn = pCoexDm->bCurPsTdmaOn;
	pCoexDm->prePsTdma = pCoexDm->curPsTdma;
पूर्ण

अटल bool halbtc8723b1ant_IsCommonAction(काष्ठा btc_coexist *pBtCoexist)
अणु
	bool bCommon = false, bWअगरiConnected = false, bWअगरiBusy = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);

	अगर (
		!bWअगरiConnected &&
		BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus
	) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi non connected-idle + BT non connected-idle!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	पूर्ण अन्यथा अगर (
		bWअगरiConnected &&
		(BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus)
	) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi connected + BT non connected-idle!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	पूर्ण अन्यथा अगर (
		!bWअगरiConnected &&
		(BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus)
	) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi non connected-idle + BT connected-idle!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	पूर्ण अन्यथा अगर (
		bWअगरiConnected &&
		(BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus)
	) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Wifi connected + BT connected-idle!!\n"));

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	पूर्ण अन्यथा अगर (
		!bWअगरiConnected &&
		(BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE != pCoexDm->btStatus)
	) अणु
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], Wifi non connected-idle + BT Busy!!\n")
		);

		/* halbtc8723b1ant_SwMechanism(pBtCoexist, false); */

		bCommon = true;
	पूर्ण अन्यथा अणु
		अगर (bWअगरiBusy) अणु
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE,
				("[BTCoex], Wifi Connected-Busy + BT Busy!!\n")
			);
		पूर्ण अन्यथा अणु
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE,
				("[BTCoex], Wifi Connected-Idle + BT Busy!!\n")
			);
		पूर्ण

		bCommon = false;
	पूर्ण

	वापस bCommon;
पूर्ण


अटल व्योम halbtc8723b1ant_TdmaDurationAdjustForAcl(
	काष्ठा btc_coexist *pBtCoexist, u8 wअगरiStatus
)
अणु
	अटल s32 up, dn, m, n, WaitCount;
	s32 result;   /* 0: no change, +1: increase WiFi duration, -1: decrease WiFi duration */
	u8 retryCount = 0, btInfoExt;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE_FW,
		("[BTCoex], TdmaDurationAdjustForAcl()\n")
	);

	अगर (
		(BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN == wअगरiStatus) ||
		(BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN == wअगरiStatus) ||
		(BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SPECIAL_PKT == wअगरiStatus)
	) अणु
		अगर (
			pCoexDm->curPsTdma != 1 &&
			pCoexDm->curPsTdma != 2 &&
			pCoexDm->curPsTdma != 3 &&
			pCoexDm->curPsTdma != 9
		) अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
			pCoexDm->psTdmaDuAdjType = 9;

			up = 0;
			dn = 0;
			m = 1;
			n = 3;
			result = 0;
			WaitCount = 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!pCoexDm->bAutoTdmaAdjust) अणु
		pCoexDm->bAutoTdmaAdjust = true;
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE_FW_DETAIL,
			("[BTCoex], first run TdmaDurationAdjust()!!\n")
		);

		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 2);
		pCoexDm->psTdmaDuAdjType = 2;
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
		btInfoExt = pCoexSta->btInfoExt;
		/* BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], retryCount = %d\n", retryCount)); */
		/* BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE_FW_DETAIL, ("[BTCoex], up =%d, dn =%d, m =%d, n =%d, WaitCount =%d\n", */
		/* 	up, dn, m, n, WaitCount)); */

		अगर (pCoexSta->lowPriorityTx > 1050 || pCoexSta->lowPriorityRx > 1250)
			retryCount++;

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
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE_FW_DETAIL,
					("[BTCoex], Increase wifi duration!!\n")
				);
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
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE_FW_DETAIL,
				("[BTCoex], Decrease wifi duration for retryCounter>3!!\n")
			);
		पूर्ण

		अगर (result == -1) अणु
			अगर (
				BT_INFO_8723B_1ANT_A2DP_BASIC_RATE(btInfoExt) &&
				((pCoexDm->curPsTdma == 1) || (pCoexDm->curPsTdma == 2))
			) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			पूर्ण अन्यथा अगर (pCoexDm->curPsTdma == 1) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 2);
				pCoexDm->psTdmaDuAdjType = 2;
			पूर्ण अन्यथा अगर (pCoexDm->curPsTdma == 2) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			पूर्ण अन्यथा अगर (pCoexDm->curPsTdma == 9) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 11);
				pCoexDm->psTdmaDuAdjType = 11;
			पूर्ण
		पूर्ण अन्यथा अगर (result == 1) अणु
			अगर (
				BT_INFO_8723B_1ANT_A2DP_BASIC_RATE(btInfoExt) &&
				((pCoexDm->curPsTdma == 1) || (pCoexDm->curPsTdma == 2))
			) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			पूर्ण अन्यथा अगर (pCoexDm->curPsTdma == 11) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 9);
				pCoexDm->psTdmaDuAdjType = 9;
			पूर्ण अन्यथा अगर (pCoexDm->curPsTdma == 9) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 2);
				pCoexDm->psTdmaDuAdjType = 2;
			पूर्ण अन्यथा अगर (pCoexDm->curPsTdma == 2) अणु
				halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 1);
				pCoexDm->psTdmaDuAdjType = 1;
			पूर्ण
		पूर्ण अन्यथा अणु	  /* no change */
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE_FW_DETAIL,
				(
					"[BTCoex], ********** TDMA(on, %d) **********\n",
					pCoexDm->curPsTdma
				)
			);
		पूर्ण

		अगर (
			pCoexDm->curPsTdma != 1 &&
			pCoexDm->curPsTdma != 2 &&
			pCoexDm->curPsTdma != 9 &&
			pCoexDm->curPsTdma != 11
		) /*  recover to previous adjust type */
			halbtc8723b1ant_PsTdma(
				pBtCoexist, NORMAL_EXEC, true, pCoexDm->psTdmaDuAdjType
			);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_PsTdmaCheckForPowerSaveState(
	काष्ठा btc_coexist *pBtCoexist, bool bNewPsState
)
अणु
	u8 lpsMode = 0x0;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_LPS_MODE, &lpsMode);

	अगर (lpsMode) अणु	/*  alपढ़ोy under LPS state */
		अगर (bNewPsState) अणु
			/*  keep state under LPS, करो nothing. */
		पूर्ण अन्यथा /*  will leave LPS state, turn off psTdma first */
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
	पूर्ण अन्यथा अणु						/*  NO PS state */
		अगर (bNewPsState) /*  will enter LPS state, turn off psTdma first */
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
		अन्यथा अणु
			/*  keep state under NO PS state, करो nothing. */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_PowerSaveState(
	काष्ठा btc_coexist *pBtCoexist, u8 psType, u8 lpsVal, u8 rpwmVal
)
अणु
	bool bLowPwrDisable = false;

	चयन (psType) अणु
	हाल BTC_PS_WIFI_NATIVE:
		/*  recover to original 32k low घातer setting */
		bLowPwrDisable = false;
		pBtCoexist->fBtcSet(
			pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable
		);
		pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_NORMAL_LPS, शून्य);
		pCoexSta->bForceLpsOn = false;
		अवरोध;
	हाल BTC_PS_LPS_ON:
		halbtc8723b1ant_PsTdmaCheckForPowerSaveState(pBtCoexist, true);
		halbtc8723b1ant_LpsRpwm(pBtCoexist, NORMAL_EXEC, lpsVal, rpwmVal);
		/*  when coex क्रमce to enter LPS, करो not enter 32k low घातer. */
		bLowPwrDisable = true;
		pBtCoexist->fBtcSet(
			pBtCoexist, BTC_SET_ACT_DISABLE_LOW_POWER, &bLowPwrDisable
		);
		/*  घातer save must executed beक्रमe psTdma. */
		pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_ENTER_LPS, शून्य);
		pCoexSta->bForceLpsOn = true;
		अवरोध;
	हाल BTC_PS_LPS_OFF:
		halbtc8723b1ant_PsTdmaCheckForPowerSaveState(pBtCoexist, false);
		pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_ACT_LEAVE_LPS, शून्य);
		pCoexSta->bForceLpsOn = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*  */
/*  */
/* 	Software Coex Mechanism start */
/*  */
/*  */

/*  */
/*  */
/* 	Non-Software Coex Mechanism start */
/*  */
/*  */
अटल व्योम halbtc8723b1ant_ActionWअगरiMultiPort(काष्ठा btc_coexist *pBtCoexist)
अणु
	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);
	halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
पूर्ण

अटल व्योम halbtc8723b1ant_ActionHs(काष्ठा btc_coexist *pBtCoexist)
अणु
	halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 5);
	halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
पूर्ण

अटल व्योम halbtc8723b1ant_ActionBtInquiry(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bWअगरiConnected = false;
	bool bApEnable = false;
	bool bWअगरiBusy = false;
	bool bBtBusy = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE, &bApEnable);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bBtBusy);

	अगर (!bWअगरiConnected && !pCoexSta->bWiFiIsHighPriTask) अणु
		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);

		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अगर (
		pBtLinkInfo->bScoExist ||
		pBtLinkInfo->bHidExist ||
		pBtLinkInfo->bA2dpExist
	) अणु
		/*  SCO/HID/A2DP busy */
		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 32);

		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist || bWअगरiBusy) अणु
		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 20);

		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);

		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ActionBtScoHidOnlyBusy(
	काष्ठा btc_coexist *pBtCoexist, u8 wअगरiStatus
)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bWअगरiConnected = false;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);

	/*  tdma and coex table */

	अगर (pBtLinkInfo->bScoExist) अणु
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 5);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 5);
	पूर्ण अन्यथा अणु /* HID */
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 6);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 5);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ActionWअगरiConnectedBtAclBusy(
	काष्ठा btc_coexist *pBtCoexist, u8 wअगरiStatus
)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	halbtc8723b1ant_BtRssiState(2, 28, 0);

	अगर ((pCoexSta->lowPriorityRx >= 1000) && (pCoexSta->lowPriorityRx != 65535))
		pBtLinkInfo->bSlaveRole = true;
	अन्यथा
		pBtLinkInfo->bSlaveRole = false;

	अगर (pBtLinkInfo->bHidOnly) अणु /* HID */
		halbtc8723b1ant_ActionBtScoHidOnlyBusy(pBtCoexist, wअगरiStatus);
		pCoexDm->bAutoTdmaAdjust = false;
		वापस;
	पूर्ण अन्यथा अगर (pBtLinkInfo->bA2dpOnly) अणु /* A2DP */
		अगर (BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE == wअगरiStatus) अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 32);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
			pCoexDm->bAutoTdmaAdjust = false;
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_TdmaDurationAdjustForAcl(pBtCoexist, wअगरiStatus);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
			pCoexDm->bAutoTdmaAdjust = true;
		पूर्ण
	पूर्ण अन्यथा अगर (pBtLinkInfo->bHidExist && pBtLinkInfo->bA2dpExist) अणु /* HID+A2DP */
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 14);
		pCoexDm->bAutoTdmaAdjust = false;

		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर (
		pBtLinkInfo->bPanOnly ||
		(pBtLinkInfo->bHidExist && pBtLinkInfo->bPanExist)
	) अणु /* PAN(OPP, FTP), HID+PAN(OPP, FTP) */
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 3);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		pCoexDm->bAutoTdmaAdjust = false;
	पूर्ण अन्यथा अगर (
		(pBtLinkInfo->bA2dpExist && pBtLinkInfo->bPanExist) ||
		(pBtLinkInfo->bHidExist && pBtLinkInfo->bA2dpExist && pBtLinkInfo->bPanExist)
	) अणु /* A2DP+PAN(OPP, FTP), HID+A2DP+PAN(OPP, FTP) */
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 13);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		pCoexDm->bAutoTdmaAdjust = false;
	पूर्ण अन्यथा अणु
		/* BT no-profile busy (0x9) */
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		pCoexDm->bAutoTdmaAdjust = false;
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ActionWअगरiNotConnected(काष्ठा btc_coexist *pBtCoexist)
अणु
	/*  घातer save state */
	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/*  tdma and coex table */
	halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 8);
	halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम halbtc8723b1ant_ActionWअगरiNotConnectedScan(
	काष्ठा btc_coexist *pBtCoexist
)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;

	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/*  tdma and coex table */
	अगर (BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) अणु
		अगर (pBtLinkInfo->bA2dpExist) अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 32);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		पूर्ण अन्यथा अगर (pBtLinkInfo->bA2dpExist && pBtLinkInfo->bPanExist) अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 22);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 20);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण अन्यथा अगर (
		(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
	) अणु
		halbtc8723b1ant_ActionBtScoHidOnlyBusy(
			pBtCoexist, BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN
		);
	पूर्ण अन्यथा अणु
		/* Bryant Add */
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ActionWअगरiNotConnectedAssoAuth(
	काष्ठा btc_coexist *pBtCoexist
)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;

	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/*  tdma and coex table */
	अगर (
		(pBtLinkInfo->bScoExist) ||
		(pBtLinkInfo->bHidExist) ||
		(pBtLinkInfo->bA2dpExist)
	) अणु
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist) अणु
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 20);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ActionWअगरiConnectedScan(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;

	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/*  tdma and coex table */
	अगर (BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) अणु
		अगर (pBtLinkInfo->bA2dpExist) अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 32);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		पूर्ण अन्यथा अगर (pBtLinkInfo->bA2dpExist && pBtLinkInfo->bPanExist) अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 22);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 20);
			halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण अन्यथा अगर (
		(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
	) अणु
		halbtc8723b1ant_ActionBtScoHidOnlyBusy(
			pBtCoexist, BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN
		);
	पूर्ण अन्यथा अणु
		/* Bryant Add */
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ActionWअगरiConnectedSpecialPacket(
	काष्ठा btc_coexist *pBtCoexist
)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;

	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/*  tdma and coex table */
	अगर (
		(pBtLinkInfo->bScoExist) ||
		(pBtLinkInfo->bHidExist) ||
		(pBtLinkInfo->bA2dpExist)
	) अणु
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर (pBtLinkInfo->bPanExist) अणु
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, true, 20);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ActionWअगरiConnected(काष्ठा btc_coexist *pBtCoexist)
अणु
	bool bWअगरiBusy = false;
	bool bScan = false, bLink = false, bRoam = false;
	bool bUnder4way = false, bApEnable = false;

	BTC_PRINT(
		BTC_MSG_ALGORITHM,
		ALGO_TRACE,
		("[BTCoex], CoexForWifiConnect() ===>\n")
	);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS, &bUnder4way);
	अगर (bUnder4way) अणु
		halbtc8723b1ant_ActionWअगरiConnectedSpecialPacket(pBtCoexist);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], CoexForWifiConnect(), return for wifi is under 4way<===\n")
		);
		वापस;
	पूर्ण

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);
	अगर (bScan || bLink || bRoam) अणु
		अगर (bScan)
			halbtc8723b1ant_ActionWअगरiConnectedScan(pBtCoexist);
		अन्यथा
			halbtc8723b1ant_ActionWअगरiConnectedSpecialPacket(pBtCoexist);
		BTC_PRINT(
			BTC_MSG_ALGORITHM,
			ALGO_TRACE,
			("[BTCoex], CoexForWifiConnect(), return for wifi is under scan<===\n")
		);
		वापस;
	पूर्ण

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE, &bApEnable);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);

	/*  घातer save state */
	अगर (
		!bApEnable &&
		BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus &&
		!pBtCoexist->btLinkInfo.bHidOnly
	) अणु
		अगर (pBtCoexist->btLinkInfo.bA2dpOnly) अणु /* A2DP */
			अगर (!bWअगरiBusy)
				halbtc8723b1ant_PowerSaveState(
					pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0
				);
			अन्यथा अणु /* busy */
				अगर  (pCoexSta->nScanAPNum >= BT_8723B_1ANT_WIFI_NOISY_THRESH)  /* no क्रमce LPS, no PS-TDMA, use pure TDMA */
					halbtc8723b1ant_PowerSaveState(
						pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0
					);
				अन्यथा
					halbtc8723b1ant_PowerSaveState(
						pBtCoexist, BTC_PS_LPS_ON, 0x50, 0x4
					);
			पूर्ण
		पूर्ण अन्यथा अगर (
			(!pCoexSta->bPanExist) &&
			(!pCoexSta->bA2dpExist) &&
			(!pCoexSta->bHidExist)
		)
			halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		अन्यथा
			halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_LPS_ON, 0x50, 0x4);
	पूर्ण अन्यथा
		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/*  tdma and coex table */
	अगर (!bWअगरiBusy) अणु
		अगर (BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) अणु
			halbtc8723b1ant_ActionWअगरiConnectedBtAclBusy(
				pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE
			);
		पूर्ण अन्यथा अगर (
			(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
			(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
		) अणु
			halbtc8723b1ant_ActionBtScoHidOnlyBusy(pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);

			अगर ((pCoexSta->highPriorityTx) + (pCoexSta->highPriorityRx) <= 60)
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
			अन्यथा
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) अणु
			halbtc8723b1ant_ActionWअगरiConnectedBtAclBusy(
				pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY
			);
		पूर्ण अन्यथा अगर (
			(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
			(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
		) अणु
			halbtc8723b1ant_ActionBtScoHidOnlyBusy(
				pBtCoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY
			);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 8);

			अगर ((pCoexSta->highPriorityTx) + (pCoexSta->highPriorityRx) <= 60)
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
			अन्यथा
				halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 7);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_RunSwCoexistMechanism(काष्ठा btc_coexist *pBtCoexist)
अणु
	u8 algorithm = 0;

	algorithm = halbtc8723b1ant_ActionAlgorithm(pBtCoexist);
	pCoexDm->curAlgorithm = algorithm;

	अगर (halbtc8723b1ant_IsCommonAction(pBtCoexist)) अणु

	पूर्ण अन्यथा अणु
		चयन (pCoexDm->curAlgorithm) अणु
		हाल BT_8723B_1ANT_COEX_ALGO_SCO:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = SCO.\n"));
			/* halbtc8723b1ant_ActionSco(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_HID:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HID.\n"));
			/* halbtc8723b1ant_ActionHid(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = A2DP.\n"));
			/* halbtc8723b1ant_ActionA2dp(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_A2DP_PANHS:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = A2DP+PAN(HS).\n"));
			/* halbtc8723b1ant_ActionA2dpPanHs(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_PANEDR:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = PAN(EDR).\n"));
			/* halbtc8723b1ant_ActionPanEdr(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_PANHS:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HS mode.\n"));
			/* halbtc8723b1ant_ActionPanHs(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_PANEDR_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = PAN+A2DP.\n"));
			/* halbtc8723b1ant_ActionPanEdrA2dp(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_PANEDR_HID:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = PAN(EDR)+HID.\n"));
			/* halbtc8723b1ant_ActionPanEdrHid(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_HID_A2DP_PANEDR:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HID+A2DP+PAN.\n"));
			/* halbtc8723b1ant_ActionHidA2dpPanEdr(pBtCoexist); */
			अवरोध;
		हाल BT_8723B_1ANT_COEX_ALGO_HID_A2DP:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = HID+A2DP.\n"));
			/* halbtc8723b1ant_ActionHidA2dp(pBtCoexist); */
			अवरोध;
		शेष:
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Action algorithm = coexist All Off!!\n"));
			अवरोध;
		पूर्ण
		pCoexDm->preAlgorithm = pCoexDm->curAlgorithm;
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_RunCoexistMechanism(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	bool bWअगरiConnected = false, bBtHsOn = false;
	bool bIncreaseScanDevNum = false;
	bool bBtCtrlAggBufSize = false;
	u8 aggBufSize = 5;
	u32 wअगरiLinkStatus = 0;
	u32 numOfWअगरiLink = 0;

	BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism() ===>\n"));

	अगर (pBtCoexist->bManualControl) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism(), return for Manual CTRL <===\n"));
		वापस;
	पूर्ण

	अगर (pBtCoexist->bStopCoexDm) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], RunCoexistMechanism(), return for Stop Coex DM <===\n"));
		वापस;
	पूर्ण

	अगर (pCoexSta->bUnderIps) अणु
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], wifi is under IPS !!!\n"));
		वापस;
	पूर्ण

	अगर (
		(BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
	)अणु
		bIncreaseScanDevNum = true;
	पूर्ण

	pBtCoexist->fBtcSet(
		pBtCoexist,
		BTC_SET_BL_INC_SCAN_DEV_NUM,
		&bIncreaseScanDevNum
	);
	pBtCoexist->fBtcGet(
		pBtCoexist,
		BTC_GET_BL_WIFI_CONNECTED,
		&bWअगरiConnected
	);

	pBtCoexist->fBtcGet(
		pBtCoexist,
		BTC_GET_U4_WIFI_LINK_STATUS,
		&wअगरiLinkStatus
	);
	numOfWअगरiLink = wअगरiLinkStatus >> 16;

	अगर ((numOfWअगरiLink >= 2) || (wअगरiLinkStatus & WIFI_P2P_GO_CONNECTED)) अणु
		BTC_PRINT(
			BTC_MSG_INTERFACE,
			INTF_NOTIFY,
			(
				"############# [BTCoex],  Multi-Port numOfWifiLink = %d, wifiLinkStatus = 0x%x\n",
				numOfWअगरiLink,
				wअगरiLinkStatus
			)
		);
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, bBtCtrlAggBufSize, aggBufSize);

		अगर ((pBtLinkInfo->bA2dpExist) && (pCoexSta->bC2hBtInquiryPage)) अणु
			BTC_PRINT(
				BTC_MSG_INTERFACE,
				INTF_NOTIFY,
				("############# [BTCoex],  BT Is Inquirying\n")
			);
			halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		पूर्ण अन्यथा
			halbtc8723b1ant_ActionWअगरiMultiPort(pBtCoexist);

		वापस;
	पूर्ण

	अगर ((pBtLinkInfo->bBtLinkExist) && (bWअगरiConnected)) अणु
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 1, 1, 0, 1);

		अगर (pBtLinkInfo->bScoExist)
			halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, true, 0x5);
		अन्यथा
			halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, true, 0x8);

		halbtc8723b1ant_SwMechanism(pBtCoexist, true);
		halbtc8723b1ant_RunSwCoexistMechanism(pBtCoexist);  /* just prपूर्णांक debug message */
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);

		halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, false, 0x5);

		halbtc8723b1ant_SwMechanism(pBtCoexist, false);
		halbtc8723b1ant_RunSwCoexistMechanism(pBtCoexist); /* just prपूर्णांक debug message */
	पूर्ण

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	अगर (pCoexSta->bC2hBtInquiryPage) अणु
		BTC_PRINT(
			BTC_MSG_INTERFACE,
			INTF_NOTIFY,
			("############# [BTCoex],  BT Is Inquirying\n")
		);
		halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		वापस;
	पूर्ण अन्यथा अगर (bBtHsOn) अणु
		halbtc8723b1ant_ActionHs(pBtCoexist);
		वापस;
	पूर्ण


	अगर (!bWअगरiConnected) अणु
		bool bScan = false, bLink = false, bRoam = false;

		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], wifi is non connected-idle !!!\n"));

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);

		अगर (bScan || bLink || bRoam) अणु
			 अगर (bScan)
				halbtc8723b1ant_ActionWअगरiNotConnectedScan(pBtCoexist);
			 अन्यथा
				halbtc8723b1ant_ActionWअगरiNotConnectedAssoAuth(pBtCoexist);
		पूर्ण अन्यथा
			halbtc8723b1ant_ActionWअगरiNotConnected(pBtCoexist);
	पूर्ण अन्यथा /*  wअगरi LPS/Busy */
		halbtc8723b1ant_ActionWअगरiConnected(pBtCoexist);
पूर्ण

अटल व्योम halbtc8723b1ant_InitCoexDm(काष्ठा btc_coexist *pBtCoexist)
अणु
	/*  क्रमce to reset coex mechanism */

	/*  sw all off */
	halbtc8723b1ant_SwMechanism(pBtCoexist, false);

	/* halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 8); */
	halbtc8723b1ant_CoexTableWithType(pBtCoexist, FORCE_EXEC, 0);

	pCoexSta->popEventCnt = 0;
पूर्ण

अटल व्योम halbtc8723b1ant_InitHwConfig(
	काष्ठा btc_coexist *pBtCoexist,
	bool bBackUp,
	bool bWअगरiOnly
)
अणु
	u32 u4Tmp = 0;/*  fwVer; */
	u8 u1Tmpa = 0, u1Tmpb = 0;

	BTC_PRINT(
		BTC_MSG_INTERFACE,
		INTF_INIT,
		("[BTCoex], 1Ant Init HW Config!!\n")
	);

	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x550, 0x8, 0x1);  /* enable TBTT nterrupt */

	/*  0x790[5:0]= 0x5 */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x790, 0x5);

	/*  Enable counter statistics */
	pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x778, 0x1);
	pBtCoexist->fBtcWrite1ByteBitMask(pBtCoexist, 0x40, 0x20, 0x1);

	/* Antenna config */
	अगर (bWअगरiOnly) अणु
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_WIFI, true, false);
		halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 9);
	पूर्ण अन्यथा
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, true, false);

	/*  PTA parameter */
	halbtc8723b1ant_CoexTableWithType(pBtCoexist, FORCE_EXEC, 0);

	u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);
	u1Tmpa = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x765);
	u1Tmpb = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x67);

	BTC_PRINT(
		BTC_MSG_INTERFACE,
		INTF_NOTIFY,
		(
			"############# [BTCoex], 0x948 = 0x%x, 0x765 = 0x%x, 0x67 = 0x%x\n",
			u4Tmp,
			u1Tmpa,
			u1Tmpb
		)
	);
पूर्ण

/*  */
/*  work around function start with wa_halbtc8723b1ant_ */
/*  */
/*  */
/*  बाह्य function start with EXhalbtc8723b1ant_ */
/*  */
व्योम EXhalbtc8723b1ant_PowerOnSetting(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_board_info *pBoardInfo = &pBtCoexist->boardInfo;
	u8 u1Tmp = 0x0;
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

व्योम EXhalbtc8723b1ant_InitHwConfig(काष्ठा btc_coexist *pBtCoexist, bool bWअगरiOnly)
अणु
	halbtc8723b1ant_InitHwConfig(pBtCoexist, true, bWअगरiOnly);
पूर्ण

व्योम EXhalbtc8723b1ant_InitCoexDm(काष्ठा btc_coexist *pBtCoexist)
अणु
	BTC_PRINT(
		BTC_MSG_INTERFACE,
		INTF_INIT,
		("[BTCoex], Coex Mechanism Init!!\n")
	);

	pBtCoexist->bStopCoexDm = false;

	halbtc8723b1ant_InitCoexDm(pBtCoexist);

	halbtc8723b1ant_QueryBtInfo(pBtCoexist);
पूर्ण

व्योम EXhalbtc8723b1ant_DisplayCoexInfo(काष्ठा btc_coexist *pBtCoexist)
अणु
	काष्ठा btc_board_info *pBoardInfo = &pBtCoexist->boardInfo;
	काष्ठा btc_stack_info *pStackInfo = &pBtCoexist->stackInfo;
	काष्ठा btc_bt_link_info *pBtLinkInfo = &pBtCoexist->btLinkInfo;
	u8 *cliBuf = pBtCoexist->cliBuf;
	u8 u1Tmp[4], i, btInfoExt, psTdmaCase = 0;
	u16 u2Tmp[4];
	u32 u4Tmp[4];
	bool bRoam = false;
	bool bScan = false;
	bool bLink = false;
	bool bWअगरiUnder5G = false;
	bool bWअगरiUnderBMode = false;
	bool bBtHsOn = false;
	bool bWअगरiBusy = false;
	s32 wअगरiRssi = 0, btHsRssi = 0;
	u32 wअगरiBw, wअगरiTrafficDir, faOfdm, faCck, wअगरiLinkStatus;
	u8 wअगरiDot11Chnl, wअगरiHsChnl;
	u32 fwVer = 0, btPatchVer = 0;
	अटल u8 PopReportIn10s;

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n ============[BT Coexist info]============"
	);
	CL_PRINTF(cliBuf);

	अगर (pBtCoexist->bManualControl) अणु
		CL_SPRINTF(
			cliBuf,
			BT_TMP_BUF_SIZE,
			"\r\n ============[Under Manual Control]============"
		);
		CL_PRINTF(cliBuf);
		CL_SPRINTF(cliBuf,
			BT_TMP_BUF_SIZE,
			"\r\n =========================================="
		);
		CL_PRINTF(cliBuf);
	पूर्ण
	अगर (pBtCoexist->bStopCoexDm) अणु
		CL_SPRINTF(
			cliBuf,
			BT_TMP_BUF_SIZE,
			"\r\n ============[Coex is STOPPED]============"
		);
		CL_PRINTF(cliBuf);
		CL_SPRINTF(
			cliBuf,
			BT_TMP_BUF_SIZE,
			"\r\n =========================================="
		);
		CL_PRINTF(cliBuf);
	पूर्ण

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d", "Ant PG Num/ Ant Mech/ Ant Pos:", \
		pBoardInfo->pgAntNum,
		pBoardInfo->btdmAntNum,
		pBoardInfo->btdmAntPos
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s / %d", "BT stack/ hci ext ver", \
		((pStackInfo->bProfileNotअगरied) ? "Yes" : "No"),
		pStackInfo->hciVersion
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_BT_PATCH_VER, &btPatchVer);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_FW_VER, &fwVer);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d_%x/ 0x%x/ 0x%x(%d)", "CoexVer/ FwVer/ PatchVer", \
		GLCoexVerDate8723b1Ant,
		GLCoexVer8723b1Ant,
		fwVer,
		btPatchVer,
		btPatchVer
	);
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
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d", "Wifi rssi/ HS rssi", \
		wअगरiRssi - 100, btHsRssi - 100
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_SCAN, &bScan);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_LINK, &bLink);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_ROAM, &bRoam);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d/ %s", "Wifi bLink/ bRoam/ bScan/ bHi-Pri", \
		bLink, bRoam, bScan, ((pCoexSta->bWiFiIsHighPriTask) ? "1" : "0")
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_UNDER_5G, &bWअगरiUnder5G);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_BUSY, &bWअगरiBusy);
	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION, &wअगरiTrafficDir
	);
	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_BL_WIFI_UNDER_B_MODE, &bWअगरiUnderBMode
	);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s / %s/ %s/ AP =%d/ %s ", "Wifi status", \
		(bWअगरiUnder5G ? "5G" : "2.4G"),
		((bWअगरiUnderBMode) ? "11b" : ((BTC_WIFI_BW_LEGACY == wअगरiBw) ? "11bg" : (((BTC_WIFI_BW_HT40 == wअगरiBw) ? "HT40" : "HT20")))),
		((!bWअगरiBusy) ? "idle" : ((BTC_WIFI_TRAFFIC_TX == wअगरiTrafficDir) ? "uplink" : "downlink")),
		pCoexSta->nScanAPNum,
		(pCoexSta->bCCKLock) ? "Lock" : "noLock"
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_U4_WIFI_LINK_STATUS, &wअगरiLinkStatus
	);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d/ %d/ %d", "sta/vwifi/hs/p2pGo/p2pGc", \
		((wअगरiLinkStatus & WIFI_STA_CONNECTED) ? 1 : 0),
		((wअगरiLinkStatus & WIFI_AP_CONNECTED) ? 1 : 0),
		((wअगरiLinkStatus & WIFI_HS_CONNECTED) ? 1 : 0),
		((wअगरiLinkStatus & WIFI_P2P_GO_CONNECTED) ? 1 : 0),
		((wअगरiLinkStatus & WIFI_P2P_GC_CONNECTED) ? 1 : 0)
	);
	CL_PRINTF(cliBuf);


	PopReportIn10s++;
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = [%s/ %d/ %d/ %d] ", "BT [status/ rssi/ retryCnt/ popCnt]", \
		((pBtCoexist->btInfo.bBtDisabled) ? ("disabled") : ((pCoexSta->bC2hBtInquiryPage) ? ("inquiry/page scan") : ((BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE == pCoexDm->btStatus) ? "non-connected idle" :
		((BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE == pCoexDm->btStatus) ? "connected-idle" : "busy")))),
		pCoexSta->btRssi, pCoexSta->btRetryCnt, pCoexSta->popEventCnt
	);
	CL_PRINTF(cliBuf);

	अगर (PopReportIn10s >= 5) अणु
		pCoexSta->popEventCnt = 0;
		PopReportIn10s = 0;
	पूर्ण


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

	अगर (pStackInfo->bProfileNotअगरied) अणु
		pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_BT_LINK_INFO);
	पूर्ण अन्यथा अणु
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %s", "BT Role", \
		(pBtLinkInfo->bSlaveRole) ? "Slave" : "Master");
		CL_PRINTF(cliBuf);
	पूर्ण


	btInfoExt = pCoexSta->btInfoExt;
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s", "BT Info A2DP rate", \
		(btInfoExt & BIT0) ? "Basic rate" : "EDR rate"
	);
	CL_PRINTF(cliBuf);

	क्रम (i = 0; i < BT_INFO_SRC_8723B_1ANT_MAX; i++) अणु
		अगर (pCoexSta->btInfoC2hCnt[i]) अणु
			CL_SPRINTF(
				cliBuf,
				BT_TMP_BUF_SIZE,
				"\r\n %-35s = %02x %02x %02x %02x %02x %02x %02x(%d)", GLBtInfoSrc8723b1Ant[i], \
				pCoexSta->btInfoC2h[i][0], pCoexSta->btInfoC2h[i][1],
				pCoexSta->btInfoC2h[i][2], pCoexSta->btInfoC2h[i][3],
				pCoexSta->btInfoC2h[i][4], pCoexSta->btInfoC2h[i][5],
				pCoexSta->btInfoC2h[i][6], pCoexSta->btInfoC2hCnt[i]
			);
			CL_PRINTF(cliBuf);
		पूर्ण
	पूर्ण
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %s/%s, (0x%x/0x%x)", "PS state, IPS/LPS, (lps/rpwm)", \
		(pCoexSta->bUnderIps ? "IPS ON" : "IPS OFF"),
		(pCoexSta->bUnderLps ? "LPS ON" : "LPS OFF"),
		pBtCoexist->btInfo.lpsVal,
		pBtCoexist->btInfo.rpwmVal
	);
	CL_PRINTF(cliBuf);
	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD);

	अगर (!pBtCoexist->bManualControl) अणु
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
			"\r\n %-35s = %d", "SM[LowPenaltyRA]", \
			pCoexDm->bCurLowPenaltyRa
		);
		CL_PRINTF(cliBuf);

		CL_SPRINTF(
			cliBuf,
			BT_TMP_BUF_SIZE,
			"\r\n %-35s = %s/ %s/ %d ", "DelBA/ BtCtrlAgg/ AggSize", \
			(pBtCoexist->btInfo.bRejectAggPkt ? "Yes" : "No"),
			(pBtCoexist->btInfo.bBtCtrlAggBufSize ? "Yes" : "No"),
			pBtCoexist->btInfo.aggBufSize
		);
		CL_PRINTF(cliBuf);
		CL_SPRINTF(
			cliBuf,
			BT_TMP_BUF_SIZE,
			"\r\n %-35s = 0x%x ", "Rate Mask", \
			pBtCoexist->btInfo.raMask
		);
		CL_PRINTF(cliBuf);

		/*  Fw mechanism */
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s", "============[Fw mechanism]============");
		CL_PRINTF(cliBuf);

		psTdmaCase = pCoexDm->curPsTdma;
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %02x %02x %02x %02x %02x case-%d (auto:%d)", "PS TDMA", \
			pCoexDm->psTdmaPara[0], pCoexDm->psTdmaPara[1],
			pCoexDm->psTdmaPara[2], pCoexDm->psTdmaPara[3],
			pCoexDm->psTdmaPara[4], psTdmaCase, pCoexDm->bAutoTdmaAdjust);
		CL_PRINTF(cliBuf);

		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d", "Coex Table Type", \
			pCoexSta->nCoexTableType);
		CL_PRINTF(cliBuf);

		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = %d", "IgnWlanAct", \
			pCoexDm->bCurIgnoreWlanAct);
		CL_PRINTF(cliBuf);

		/*
		CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = 0x%x ", "Latest error condition(should be 0)", \
			pCoexDm->errorCondition);
		CL_PRINTF(cliBuf);
		*/
	पूर्ण

	/*  Hw setting */
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s", "============[Hw setting]============");
	CL_PRINTF(cliBuf);

	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = 0x%x/0x%x/0x%x/0x%x", "backup ARFR1/ARFR2/RL/AMaxTime", \
		pCoexDm->backupArfrCnt1, pCoexDm->backupArfrCnt2, pCoexDm->backupRetryLimit, pCoexDm->backupAmpduMaxTime);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x430);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x434);
	u2Tmp[0] = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0x42a);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x456);
	CL_SPRINTF(cliBuf, BT_TMP_BUF_SIZE, "\r\n %-35s = 0x%x/0x%x/0x%x/0x%x", "0x430/0x434/0x42a/0x456", \
		u4Tmp[0], u4Tmp[1], u2Tmp[0], u1Tmp[0]);
	CL_PRINTF(cliBuf);

	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x778);
	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6cc);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x880);
	CL_SPRINTF(
		cliBuf, BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "0x778/0x6cc/0x880[29:25]", \
		u1Tmp[0], u4Tmp[0],  (u4Tmp[1] & 0x3e000000) >> 25
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x67);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x764);
	u1Tmp[1] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x76e);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x", "0x948/ 0x67[5] / 0x764 / 0x76e", \
		u4Tmp[0], ((u1Tmp[0] & 0x20) >> 5), (u4Tmp[1] & 0xffff), u1Tmp[1]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x92c);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x930);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x944);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "0x92c[1:0]/ 0x930[7:0]/0x944[1:0]", \
		u4Tmp[0] & 0x3, u4Tmp[1] & 0xff, u4Tmp[2] & 0x3
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
		u4Tmp[0], u1Tmp[0]
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0xc50);
	u1Tmp[0] = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x49c);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x", "0xc50(dig)/0x49c(null-drop)", \
		u4Tmp[0] & 0xff, u1Tmp[0]
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
		((u4Tmp[3] & 0xffff0000) >> 16) + (u4Tmp[3] & 0xffff);
	faCck = (u1Tmp[0] << 8) + u1Tmp[1];

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "OFDM-CCA/OFDM-FA/CCK-FA", \
		u4Tmp[0] & 0xffff, faOfdm, faCck
	);
	CL_PRINTF(cliBuf);


	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d/ %d", "CRC_OK CCK/11g/11n/11n-Agg", \
		pCoexSta->nCRCOK_CCK,
		pCoexSta->nCRCOK_11g,
		pCoexSta->nCRCOK_11n,
		pCoexSta->nCRCOK_11nAgg
	);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d/ %d/ %d", "CRC_Err CCK/11g/11n/11n-Agg", \
		pCoexSta->nCRCErr_CCK,
		pCoexSta->nCRCErr_11g,
		pCoexSta->nCRCErr_11n,
		pCoexSta->nCRCErr_11nAgg
	);
	CL_PRINTF(cliBuf);

	u4Tmp[0] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c0);
	u4Tmp[1] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c4);
	u4Tmp[2] = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x6c8);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = 0x%x/ 0x%x/ 0x%x", "0x6c0/0x6c4/0x6c8(coexTable)", \
		u4Tmp[0], u4Tmp[1], u4Tmp[2]);
	CL_PRINTF(cliBuf);

	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d", "0x770(high-pri rx/tx)", \
		pCoexSta->highPriorityRx, pCoexSta->highPriorityTx
	);
	CL_PRINTF(cliBuf);
	CL_SPRINTF(
		cliBuf,
		BT_TMP_BUF_SIZE,
		"\r\n %-35s = %d/ %d", "0x774(low-pri rx/tx)", \
		pCoexSta->lowPriorityRx, pCoexSta->lowPriorityTx
	);
	CL_PRINTF(cliBuf);

	pBtCoexist->fBtcDispDbgMsg(pBtCoexist, BTC_DBG_DISP_COEX_STATISTICS);
पूर्ण


व्योम EXhalbtc8723b1ant_IpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	अगर (pBtCoexist->bManualControl ||	pBtCoexist->bStopCoexDm)
		वापस;

	अगर (BTC_IPS_ENTER == type) अणु
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS ENTER notify\n")
		);
		pCoexSta->bUnderIps = true;

		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 0);
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, false, true);
	पूर्ण अन्यथा अगर (BTC_IPS_LEAVE == type) अणु
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], IPS LEAVE notify\n")
		);
		pCoexSta->bUnderIps = false;

		halbtc8723b1ant_InitHwConfig(pBtCoexist, false, false);
		halbtc8723b1ant_InitCoexDm(pBtCoexist);
		halbtc8723b1ant_QueryBtInfo(pBtCoexist);
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b1ant_LpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	अगर (pBtCoexist->bManualControl || pBtCoexist->bStopCoexDm)
		वापस;

	अगर (BTC_LPS_ENABLE == type) अणु
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], LPS ENABLE notify\n")
		);
		pCoexSta->bUnderLps = true;
	पूर्ण अन्यथा अगर (BTC_LPS_DISABLE == type) अणु
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], LPS DISABLE notify\n")
		);
		pCoexSta->bUnderLps = false;
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b1ant_ScanNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	bool bWअगरiConnected = false, bBtHsOn = false;
	u32 wअगरiLinkStatus = 0;
	u32 numOfWअगरiLink = 0;
	bool bBtCtrlAggBufSize = false;
	u8 aggBufSize = 5;

	u8 u1Tmpa, u1Tmpb;
	u32 u4Tmp;

	अगर (pBtCoexist->bManualControl || pBtCoexist->bStopCoexDm)
		वापस;

	अगर (BTC_SCAN_START == type) अणु
		pCoexSta->bWiFiIsHighPriTask = true;
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], SCAN START notify\n")
		);

		halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 8);  /* Force antenna setup क्रम no scan result issue */
		u4Tmp = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x948);
		u1Tmpa = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x765);
		u1Tmpb = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x67);


		BTC_PRINT(
			BTC_MSG_INTERFACE,
			INTF_NOTIFY,
			(
				"[BTCoex], 0x948 = 0x%x, 0x765 = 0x%x, 0x67 = 0x%x\n",
				u4Tmp,
				u1Tmpa,
				u1Tmpb
			)
		);
	पूर्ण अन्यथा अणु
		pCoexSta->bWiFiIsHighPriTask = false;
		BTC_PRINT(
			BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], SCAN FINISH notify\n")
		);

		pBtCoexist->fBtcGet(
			pBtCoexist, BTC_GET_U1_AP_NUM, &pCoexSta->nScanAPNum
		);
	पूर्ण

	अगर (pBtCoexist->btInfo.bBtDisabled)
		वापस;

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);

	halbtc8723b1ant_QueryBtInfo(pBtCoexist);

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_LINK_STATUS, &wअगरiLinkStatus);
	numOfWअगरiLink = wअगरiLinkStatus >> 16;

	अगर (numOfWअगरiLink >= 2) अणु
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_LimitedRx(
			pBtCoexist, NORMAL_EXEC, false, bBtCtrlAggBufSize, aggBufSize
		);
		halbtc8723b1ant_ActionWअगरiMultiPort(pBtCoexist);
		वापस;
	पूर्ण

	अगर (pCoexSta->bC2hBtInquiryPage) अणु
		halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		वापस;
	पूर्ण अन्यथा अगर (bBtHsOn) अणु
		halbtc8723b1ant_ActionHs(pBtCoexist);
		वापस;
	पूर्ण

	अगर (BTC_SCAN_START == type) अणु
		/* BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], SCAN START notify\n")); */
		अगर (!bWअगरiConnected)	/*  non-connected scan */
			halbtc8723b1ant_ActionWअगरiNotConnectedScan(pBtCoexist);
		अन्यथा	/*  wअगरi is connected */
			halbtc8723b1ant_ActionWअगरiConnectedScan(pBtCoexist);
	पूर्ण अन्यथा अगर (BTC_SCAN_FINISH == type) अणु
		/* BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], SCAN FINISH notify\n")); */
		अगर (!bWअगरiConnected)	/*  non-connected scan */
			halbtc8723b1ant_ActionWअगरiNotConnected(pBtCoexist);
		अन्यथा
			halbtc8723b1ant_ActionWअगरiConnected(pBtCoexist);
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b1ant_ConnectNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	bool bWअगरiConnected = false, bBtHsOn = false;
	u32 wअगरiLinkStatus = 0;
	u32 numOfWअगरiLink = 0;
	bool bBtCtrlAggBufSize = false;
	u8 aggBufSize = 5;

	अगर (
		pBtCoexist->bManualControl ||
		pBtCoexist->bStopCoexDm ||
		pBtCoexist->btInfo.bBtDisabled
	)
		वापस;

	अगर (BTC_ASSOCIATE_START == type) अणु
		pCoexSta->bWiFiIsHighPriTask = true;
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT START notify\n"));
		 pCoexDm->nArpCnt = 0;
	पूर्ण अन्यथा अणु
		pCoexSta->bWiFiIsHighPriTask = false;
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT FINISH notify\n"));
		/* pCoexDm->nArpCnt = 0; */
	पूर्ण

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_LINK_STATUS, &wअगरiLinkStatus);
	numOfWअगरiLink = wअगरiLinkStatus >> 16;
	अगर (numOfWअगरiLink >= 2) अणु
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_LimitedRx(pBtCoexist, NORMAL_EXEC, false, bBtCtrlAggBufSize, aggBufSize);
		halbtc8723b1ant_ActionWअगरiMultiPort(pBtCoexist);
		वापस;
	पूर्ण

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	अगर (pCoexSta->bC2hBtInquiryPage) अणु
		halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		वापस;
	पूर्ण अन्यथा अगर (bBtHsOn) अणु
		halbtc8723b1ant_ActionHs(pBtCoexist);
		वापस;
	पूर्ण

	अगर (BTC_ASSOCIATE_START == type) अणु
		/* BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT START notify\n")); */
		halbtc8723b1ant_ActionWअगरiNotConnectedAssoAuth(pBtCoexist);
	पूर्ण अन्यथा अगर (BTC_ASSOCIATE_FINISH == type) अणु
		/* BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], CONNECT FINISH notify\n")); */

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);
		अगर (!bWअगरiConnected) /*  non-connected scan */
			halbtc8723b1ant_ActionWअगरiNotConnected(pBtCoexist);
		अन्यथा
			halbtc8723b1ant_ActionWअगरiConnected(pBtCoexist);
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b1ant_MediaStatusNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	u8 H2C_Parameter[3] = अणु0पूर्ण;
	u32 wअगरiBw;
	u8 wअगरiCentralChnl;
	bool bWअगरiUnderBMode = false;

	अगर (
		pBtCoexist->bManualControl ||
		pBtCoexist->bStopCoexDm ||
		pBtCoexist->btInfo.bBtDisabled
	)
		वापस;

	अगर (BTC_MEDIA_CONNECT == type) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], MEDIA connect notify\n"));

		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_UNDER_B_MODE, &bWअगरiUnderBMode);

		/* Set CCK Tx/Rx high Pri except 11b mode */
		अगर (bWअगरiUnderBMode) अणु
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cd, 0x00); /* CCK Tx */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cf, 0x00); /* CCK Rx */
		पूर्ण अन्यथा अणु
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cd, 0x10); /* CCK Tx */
			pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cf, 0x10); /* CCK Rx */
		पूर्ण

		pCoexDm->backupArfrCnt1 = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x430);
		pCoexDm->backupArfrCnt2 = pBtCoexist->fBtcRead4Byte(pBtCoexist, 0x434);
		pCoexDm->backupRetryLimit = pBtCoexist->fBtcRead2Byte(pBtCoexist, 0x42a);
		pCoexDm->backupAmpduMaxTime = pBtCoexist->fBtcRead1Byte(pBtCoexist, 0x456);
	पूर्ण अन्यथा अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], MEDIA disconnect notify\n"));
		pCoexDm->nArpCnt = 0;

		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cd, 0x0); /* CCK Tx */
		pBtCoexist->fBtcWrite1Byte(pBtCoexist, 0x6cf, 0x0); /* CCK Rx */
	पूर्ण

	/*  only 2.4G we need to inक्रमm bt the chnl mask */
	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL, &wअगरiCentralChnl);
	अगर ((BTC_MEDIA_CONNECT == type) && (wअगरiCentralChnl <= 14)) अणु
		/* H2C_Parameter[0] = 0x1; */
		H2C_Parameter[0] = 0x0;
		H2C_Parameter[1] = wअगरiCentralChnl;
		pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_U4_WIFI_BW, &wअगरiBw);

		अगर (BTC_WIFI_BW_HT40 == wअगरiBw)
			H2C_Parameter[2] = 0x30;
		अन्यथा
			H2C_Parameter[2] = 0x20;
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

व्योम EXhalbtc8723b1ant_SpecialPacketNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type)
अणु
	bool bBtHsOn = false;
	u32 wअगरiLinkStatus = 0;
	u32 numOfWअगरiLink = 0;
	bool bBtCtrlAggBufSize = false;
	u8 aggBufSize = 5;

	अगर (
		pBtCoexist->bManualControl ||
		pBtCoexist->bStopCoexDm ||
		pBtCoexist->btInfo.bBtDisabled
	)
		वापस;

	अगर (
		BTC_PACKET_DHCP == type ||
		BTC_PACKET_EAPOL == type ||
		BTC_PACKET_ARP == type
	) अणु
		अगर (BTC_PACKET_ARP == type) अणु
			BTC_PRINT(
				BTC_MSG_INTERFACE,
				INTF_NOTIFY,
				("[BTCoex], special Packet ARP notify\n")
			);

			pCoexDm->nArpCnt++;
			BTC_PRINT(
				BTC_MSG_INTERFACE,
				INTF_NOTIFY,
				("[BTCoex], ARP Packet Count = %d\n", pCoexDm->nArpCnt)
			);

			अगर (pCoexDm->nArpCnt >= 10) /*  अगर APR PKT > 10 after connect, करो not go to ActionWअगरiConnectedSpecialPacket(pBtCoexist) */
				pCoexSta->bWiFiIsHighPriTask = false;
			अन्यथा
				pCoexSta->bWiFiIsHighPriTask = true;
		पूर्ण अन्यथा अणु
			pCoexSta->bWiFiIsHighPriTask = true;
			BTC_PRINT(
				BTC_MSG_INTERFACE,
				INTF_NOTIFY,
				("[BTCoex], special Packet DHCP or EAPOL notify\n")
			);
		पूर्ण
	पूर्ण अन्यथा अणु
		pCoexSta->bWiFiIsHighPriTask = false;
		BTC_PRINT(
			BTC_MSG_INTERFACE,
			INTF_NOTIFY,
			("[BTCoex], special Packet [Type = %d] notify\n", type)
		);
	पूर्ण

	pCoexSta->specialPktPeriodCnt = 0;

	pBtCoexist->fBtcGet(
		pBtCoexist, BTC_GET_U4_WIFI_LINK_STATUS, &wअगरiLinkStatus
	);
	numOfWअगरiLink = wअगरiLinkStatus >> 16;

	अगर (numOfWअगरiLink >= 2) अणु
		halbtc8723b1ant_LimitedTx(pBtCoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_LimitedRx(
			pBtCoexist, NORMAL_EXEC, false, bBtCtrlAggBufSize, aggBufSize
		);
		halbtc8723b1ant_ActionWअगरiMultiPort(pBtCoexist);
		वापस;
	पूर्ण

	pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_HS_OPERATION, &bBtHsOn);
	अगर (pCoexSta->bC2hBtInquiryPage) अणु
		halbtc8723b1ant_ActionBtInquiry(pBtCoexist);
		वापस;
	पूर्ण अन्यथा अगर (bBtHsOn) अणु
		halbtc8723b1ant_ActionHs(pBtCoexist);
		वापस;
	पूर्ण

	अगर (
		BTC_PACKET_DHCP == type ||
		BTC_PACKET_EAPOL == type ||
		((BTC_PACKET_ARP == type) && (pCoexSta->bWiFiIsHighPriTask))
	)
		halbtc8723b1ant_ActionWअगरiConnectedSpecialPacket(pBtCoexist);
पूर्ण

व्योम EXhalbtc8723b1ant_BtInfoNotअगरy(
	काष्ठा btc_coexist *pBtCoexist, u8 *पंचांगpBuf, u8 length
)
अणु
	u8 btInfo = 0;
	u8 i, rspSource = 0;
	bool bWअगरiConnected = false;
	bool bBtBusy = false;

	pCoexSta->bC2hBtInfoReqSent = false;

	rspSource = पंचांगpBuf[0] & 0xf;
	अगर (rspSource >= BT_INFO_SRC_8723B_1ANT_MAX)
		rspSource = BT_INFO_SRC_8723B_1ANT_WIFI_FW;
	pCoexSta->btInfoC2hCnt[rspSource]++;

	BTC_PRINT(
		BTC_MSG_INTERFACE,
		INTF_NOTIFY,
		("[BTCoex], Bt info[%d], length =%d, hex data =[",
		rspSource,
		length)
	);
	क्रम (i = 0; i < length; i++) अणु
		pCoexSta->btInfoC2h[rspSource][i] = पंचांगpBuf[i];
		अगर (i == 1)
			btInfo = पंचांगpBuf[i];
		अगर (i == length - 1)
			BTC_PRINT(
				BTC_MSG_INTERFACE, INTF_NOTIFY, ("0x%02x]\n", पंचांगpBuf[i])
			);
		अन्यथा
			BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("0x%02x, ", पंचांगpBuf[i]));
	पूर्ण

	अगर (BT_INFO_SRC_8723B_1ANT_WIFI_FW != rspSource) अणु
		pCoexSta->btRetryCnt = pCoexSta->btInfoC2h[rspSource][2] & 0xf;

		अगर (pCoexSta->btRetryCnt >= 1)
			pCoexSta->popEventCnt++;

		अगर (pCoexSta->btInfoC2h[rspSource][2] & 0x20)
			pCoexSta->bC2hBtPage = true;
		अन्यथा
			pCoexSta->bC2hBtPage = false;

		pCoexSta->btRssi = pCoexSta->btInfoC2h[rspSource][3] * 2 - 90;
		/* pCoexSta->btInfoC2h[rspSource][3]*2+10; */

		pCoexSta->btInfoExt = pCoexSta->btInfoC2h[rspSource][4];

		pCoexSta->bBtTxRxMask = (pCoexSta->btInfoC2h[rspSource][2] & 0x40);
		pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_BT_TX_RX_MASK, &pCoexSta->bBtTxRxMask);

		अगर (!pCoexSta->bBtTxRxMask) अणु
			/* BT पूर्णांकo is responded by BT FW and BT RF REG 0x3C != 0x15 => Need to चयन BT TRx Mask */
			BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], Switch BT TRx Mask since BT RF REG 0x3C != 0x15\n"));
			pBtCoexist->fBtcSetBtReg(pBtCoexist, BTC_BT_REG_RF, 0x3c, 0x15);
		पूर्ण

		/*  Here we need to resend some wअगरi info to BT */
		/*  because bt is reset and loss of the info. */
		अगर (pCoexSta->btInfoExt & BIT1) अणु
			BTC_PRINT(
				BTC_MSG_ALGORITHM,
				ALGO_TRACE,
				("[BTCoex], BT ext info bit1 check, send wifi BW&Chnl to BT!!\n")
			);
			pBtCoexist->fBtcGet(pBtCoexist, BTC_GET_BL_WIFI_CONNECTED, &bWअगरiConnected);
			अगर (bWअगरiConnected)
				EXhalbtc8723b1ant_MediaStatusNotअगरy(pBtCoexist, BTC_MEDIA_CONNECT);
			अन्यथा
				EXhalbtc8723b1ant_MediaStatusNotअगरy(pBtCoexist, BTC_MEDIA_DISCONNECT);
		पूर्ण

		अगर (pCoexSta->btInfoExt & BIT3) अणु
			अगर (!pBtCoexist->bManualControl && !pBtCoexist->bStopCoexDm) अणु
				BTC_PRINT(
					BTC_MSG_ALGORITHM,
					ALGO_TRACE,
					("[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n")
				);
				halbtc8723b1ant_IgnoreWlanAct(pBtCoexist, FORCE_EXEC, false);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*  BT alपढ़ोy NOT ignore Wlan active, करो nothing here. */
		पूर्ण
	पूर्ण

	/*  check BIT2 first ==> check अगर bt is under inquiry or page scan */
	अगर (btInfo & BT_INFO_8723B_1ANT_B_INQ_PAGE)
		pCoexSta->bC2hBtInquiryPage = true;
	अन्यथा
		pCoexSta->bC2hBtInquiryPage = false;

	/*  set link exist status */
	अगर (!(btInfo & BT_INFO_8723B_1ANT_B_CONNECTION)) अणु
		pCoexSta->bBtLinkExist = false;
		pCoexSta->bPanExist = false;
		pCoexSta->bA2dpExist = false;
		pCoexSta->bHidExist = false;
		pCoexSta->bScoExist = false;
	पूर्ण अन्यथा अणु	/*  connection exists */
		pCoexSta->bBtLinkExist = true;
		अगर (btInfo & BT_INFO_8723B_1ANT_B_FTP)
			pCoexSta->bPanExist = true;
		अन्यथा
			pCoexSta->bPanExist = false;

		अगर (btInfo & BT_INFO_8723B_1ANT_B_A2DP)
			pCoexSta->bA2dpExist = true;
		अन्यथा
			pCoexSta->bA2dpExist = false;

		अगर (btInfo & BT_INFO_8723B_1ANT_B_HID)
			pCoexSta->bHidExist = true;
		अन्यथा
			pCoexSta->bHidExist = false;

		अगर (btInfo & BT_INFO_8723B_1ANT_B_SCO_ESCO)
			pCoexSta->bScoExist = true;
		अन्यथा
			pCoexSta->bScoExist = false;
	पूर्ण

	halbtc8723b1ant_UpdateBtLinkInfo(pBtCoexist);

	btInfo = btInfo & 0x1f;  /* mask profile bit क्रम connect-ilde identअगरication (क्रम CSR हाल: A2DP idle --> 0x41) */

	अगर (!(btInfo & BT_INFO_8723B_1ANT_B_CONNECTION)) अणु
		pCoexDm->btStatus = BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n"));
	पूर्ण अन्यथा अगर (btInfo == BT_INFO_8723B_1ANT_B_CONNECTION)	अणु
		/*  connection exists but no busy */
		pCoexDm->btStatus = BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n"));
	पूर्ण अन्यथा अगर (
		(btInfo & BT_INFO_8723B_1ANT_B_SCO_ESCO) ||
		(btInfo & BT_INFO_8723B_1ANT_B_SCO_BUSY)
	) अणु
		pCoexDm->btStatus = BT_8723B_1ANT_BT_STATUS_SCO_BUSY;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT SCO busy!!!\n"));
	पूर्ण अन्यथा अगर (btInfo & BT_INFO_8723B_1ANT_B_ACL_BUSY) अणु
		अगर (BT_8723B_1ANT_BT_STATUS_ACL_BUSY != pCoexDm->btStatus)
			pCoexDm->bAutoTdmaAdjust = false;

		pCoexDm->btStatus = BT_8723B_1ANT_BT_STATUS_ACL_BUSY;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT ACL busy!!!\n"));
	पूर्ण अन्यथा अणु
		pCoexDm->btStatus = BT_8723B_1ANT_BT_STATUS_MAX;
		BTC_PRINT(BTC_MSG_ALGORITHM, ALGO_TRACE, ("[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n"));
	पूर्ण

	अगर (
		(BT_8723B_1ANT_BT_STATUS_ACL_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_SCO_BUSY == pCoexDm->btStatus) ||
		(BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == pCoexDm->btStatus)
	)
		bBtBusy = true;
	अन्यथा
		bBtBusy = false;
	pBtCoexist->fBtcSet(pBtCoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bBtBusy);

	halbtc8723b1ant_RunCoexistMechanism(pBtCoexist);
पूर्ण

व्योम EXhalbtc8723b1ant_HaltNotअगरy(काष्ठा btc_coexist *pBtCoexist)
अणु
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Halt notify\n"));

	halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	halbtc8723b1ant_PsTdma(pBtCoexist, FORCE_EXEC, false, 0);
	halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, false, true);

	halbtc8723b1ant_IgnoreWlanAct(pBtCoexist, FORCE_EXEC, true);

	EXhalbtc8723b1ant_MediaStatusNotअगरy(pBtCoexist, BTC_MEDIA_DISCONNECT);

	pBtCoexist->bStopCoexDm = true;
पूर्ण

व्योम EXhalbtc8723b1ant_PnpNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 pnpState)
अणु
	BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify\n"));

	अगर (BTC_WIFI_PNP_SLEEP == pnpState) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify to SLEEP\n"));

		halbtc8723b1ant_PowerSaveState(pBtCoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		halbtc8723b1ant_PsTdma(pBtCoexist, NORMAL_EXEC, false, 0);
		halbtc8723b1ant_CoexTableWithType(pBtCoexist, NORMAL_EXEC, 2);
		halbtc8723b1ant_SetAntPath(pBtCoexist, BTC_ANT_PATH_BT, false, true);

		pBtCoexist->bStopCoexDm = true;
	पूर्ण अन्यथा अगर (BTC_WIFI_PNP_WAKE_UP == pnpState) अणु
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_NOTIFY, ("[BTCoex], Pnp notify to WAKE UP\n"));
		pBtCoexist->bStopCoexDm = false;
		halbtc8723b1ant_InitHwConfig(pBtCoexist, false, false);
		halbtc8723b1ant_InitCoexDm(pBtCoexist);
		halbtc8723b1ant_QueryBtInfo(pBtCoexist);
	पूर्ण
पूर्ण

व्योम EXhalbtc8723b1ant_Periodical(काष्ठा btc_coexist *pBtCoexist)
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
			GLCoexVerDate8723b1Ant, GLCoexVer8723b1Ant, fwVer, btPatchVer, btPatchVer));
		BTC_PRINT(BTC_MSG_INTERFACE, INTF_INIT, ("[BTCoex], ****************************************************************\n"));
	पूर्ण

	halbtc8723b1ant_MonitorBtCtr(pBtCoexist);
	halbtc8723b1ant_MonitorWiFiCtr(pBtCoexist);

	अगर (
		halbtc8723b1ant_IsWअगरiStatusChanged(pBtCoexist) ||
		pCoexDm->bAutoTdmaAdjust
	)
		halbtc8723b1ant_RunCoexistMechanism(pBtCoexist);

	pCoexSta->specialPktPeriodCnt++;
पूर्ण
