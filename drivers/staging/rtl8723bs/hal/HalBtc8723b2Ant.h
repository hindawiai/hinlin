<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
/*  The following is क्रम 8723B 2Ant BT Co-exist definition */
#घोषणा	BT_INFO_8723B_2ANT_B_FTP		BIT7
#घोषणा	BT_INFO_8723B_2ANT_B_A2DP		BIT6
#घोषणा	BT_INFO_8723B_2ANT_B_HID		BIT5
#घोषणा	BT_INFO_8723B_2ANT_B_SCO_BUSY		BIT4
#घोषणा	BT_INFO_8723B_2ANT_B_ACL_BUSY		BIT3
#घोषणा	BT_INFO_8723B_2ANT_B_INQ_PAGE		BIT2
#घोषणा	BT_INFO_8723B_2ANT_B_SCO_ESCO		BIT1
#घोषणा	BT_INFO_8723B_2ANT_B_CONNECTION		BIT0

#घोषणा		BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT		2

क्रमागत अणु
	BT_INFO_SRC_8723B_2ANT_WIFI_FW        = 0x0,
	BT_INFO_SRC_8723B_2ANT_BT_RSP         = 0x1,
	BT_INFO_SRC_8723B_2ANT_BT_ACTIVE_SEND = 0x2,
	BT_INFO_SRC_8723B_2ANT_MAX
पूर्ण;

क्रमागत अणु
	BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE = 0x0,
	BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE     = 0x1,
	BT_8723B_2ANT_BT_STATUS_INQ_PAGE           = 0x2,
	BT_8723B_2ANT_BT_STATUS_ACL_BUSY           = 0x3,
	BT_8723B_2ANT_BT_STATUS_SCO_BUSY           = 0x4,
	BT_8723B_2ANT_BT_STATUS_ACL_SCO_BUSY       = 0x5,
	BT_8723B_2ANT_BT_STATUS_MAX
पूर्ण;

क्रमागत अणु
	BT_8723B_2ANT_COEX_ALGO_UNDEFINED       = 0x0,
	BT_8723B_2ANT_COEX_ALGO_SCO             = 0x1,
	BT_8723B_2ANT_COEX_ALGO_HID             = 0x2,
	BT_8723B_2ANT_COEX_ALGO_A2DP            = 0x3,
	BT_8723B_2ANT_COEX_ALGO_A2DP_PANHS      = 0x4,
	BT_8723B_2ANT_COEX_ALGO_PANEDR          = 0x5,
	BT_8723B_2ANT_COEX_ALGO_PANHS           = 0x6,
	BT_8723B_2ANT_COEX_ALGO_PANEDR_A2DP     = 0x7,
	BT_8723B_2ANT_COEX_ALGO_PANEDR_HID      = 0x8,
	BT_8723B_2ANT_COEX_ALGO_HID_A2DP_PANEDR	= 0x9,
	BT_8723B_2ANT_COEX_ALGO_HID_A2DP        = 0xa,
	BT_8723B_2ANT_COEX_ALGO_MAX             = 0xb,
पूर्ण;

काष्ठा coex_dm_8723b_2ant अणु
	/*  fw mechanism */
	u8 preBtDecPwrLvl;
	u8 curBtDecPwrLvl;
	u8 preFwDacSwingLvl;
	u8 curFwDacSwingLvl;
	bool bCurIgnoreWlanAct;
	bool bPreIgnoreWlanAct;
	u8 prePsTdma;
	u8 curPsTdma;
	u8 psTdmaPara[5];
	u8 psTdmaDuAdjType;
	bool bResetTdmaAdjust;
	bool bAutoTdmaAdjust;
	bool bPrePsTdmaOn;
	bool bCurPsTdmaOn;
	bool bPreBtAutoReport;
	bool bCurBtAutoReport;

	/*  sw mechanism */
	bool bPreRfRxLpfShrink;
	bool bCurRfRxLpfShrink;
	u32 btRf0x1eBackup;
	bool bPreLowPenaltyRa;
	bool bCurLowPenaltyRa;
	bool bPreDacSwingOn;
	u32  preDacSwingLvl;
	bool bCurDacSwingOn;
	u32  curDacSwingLvl;
	bool bPreAdcBackOff;
	bool bCurAdcBackOff;
	bool bPreAgcTableEn;
	bool bCurAgcTableEn;
	u32 preVal0x6c0;
	u32 curVal0x6c0;
	u32 preVal0x6c4;
	u32 curVal0x6c4;
	u32 preVal0x6c8;
	u32 curVal0x6c8;
	u8 preVal0x6cc;
	u8 curVal0x6cc;
	bool bLimitedDig;

	/*  algorithm related */
	u8 preAlgorithm;
	u8 curAlgorithm;
	u8 btStatus;
	u8 wअगरiChnlInfo[3];

	bool bNeedRecover0x948;
	u32 backup0x948;
पूर्ण;

काष्ठा coex_sta_8723b_2ant अणु
	bool bBtLinkExist;
	bool bScoExist;
	bool bA2dpExist;
	bool bHidExist;
	bool bPanExist;

	bool bUnderLps;
	bool bUnderIps;
	u32 highPriorityTx;
	u32 highPriorityRx;
	u32 lowPriorityTx;
	u32 lowPriorityRx;
	u8 btRssi;
	bool bBtTxRxMask;
	u8 preBtRssiState;
	u8 preWअगरiRssiState[4];
	bool bC2hBtInfoReqSent;
	u8 btInfoC2h[BT_INFO_SRC_8723B_2ANT_MAX][10];
	u32 btInfoC2hCnt[BT_INFO_SRC_8723B_2ANT_MAX];
	bool bC2hBtInquiryPage;
	u8 btRetryCnt;
	u8 btInfoExt;
पूर्ण;

/*  */
/*  The following is पूर्णांकerface which will notअगरy coex module. */
/*  */
व्योम EXhalbtc8723b2ant_PowerOnSetting(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtc8723b2ant_InitHwConfig(काष्ठा btc_coexist *pBtCoexist, bool bWअगरiOnly);
व्योम EXhalbtc8723b2ant_InitCoexDm(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtc8723b2ant_IpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtc8723b2ant_LpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtc8723b2ant_ScanNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtc8723b2ant_ConnectNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtc8723b2ant_MediaStatusNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtc8723b2ant_SpecialPacketNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtc8723b2ant_BtInfoNotअगरy(
	काष्ठा btc_coexist *pBtCoexist, u8 *पंचांगpBuf, u8 length
);
व्योम EXhalbtc8723b2ant_HaltNotअगरy(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtc8723b2ant_PnpNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 pnpState);
व्योम EXhalbtc8723b2ant_Periodical(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtc8723b2ant_DisplayCoexInfo(काष्ठा btc_coexist *pBtCoexist);
