<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2012 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित	__HALBTC_OUT_SRC_H__
#घोषणा __HALBTC_OUT_SRC_H__

#घोषणा NORMAL_EXEC		false
#घोषणा FORCE_EXEC		true

#घोषणा BTC_RF_OFF		0x0
#घोषणा BTC_RF_ON		0x1

#घोषणा BTC_RF_A		0x0
#घोषणा BTC_RF_B		0x1
#घोषणा BTC_RF_C		0x2
#घोषणा BTC_RF_D		0x3

#घोषणा BTC_SMSP		SINGLEMAC_SINGLEPHY
#घोषणा BTC_DMDP		DUALMAC_DUALPHY
#घोषणा BTC_DMSP		DUALMAC_SINGLEPHY
#घोषणा BTC_MP_UNKNOWN		0xff

#घोषणा BT_COEX_ANT_TYPE_PG	0
#घोषणा BT_COEX_ANT_TYPE_ANTDIV		1
#घोषणा BT_COEX_ANT_TYPE_DETECTED	2

#घोषणा BTC_MIMO_PS_STATIC	0	/*  1ss */
#घोषणा BTC_MIMO_PS_DYNAMIC	1	/*  2ss */

#घोषणा BTC_RATE_DISABLE	0
#घोषणा BTC_RATE_ENABLE		1

/*  single Antenna definition */
#घोषणा BTC_ANT_PATH_WIFI	0
#घोषणा BTC_ANT_PATH_BT		1
#घोषणा BTC_ANT_PATH_PTA	2
/*  dual Antenna definition */
#घोषणा BTC_ANT_WIFI_AT_MAIN	0
#घोषणा BTC_ANT_WIFI_AT_AUX	1
/*  coupler Antenna definition */
#घोषणा BTC_ANT_WIFI_AT_CPL_MAIN	0
#घोषणा BTC_ANT_WIFI_AT_CPL_AUX		1

क्रमागत अणु
	BTC_PS_WIFI_NATIVE	= 0,	/*  wअगरi original घातer save behavior */
	BTC_PS_LPS_ON		= 1,
	BTC_PS_LPS_OFF		= 2,
	BTC_PS_MAX
पूर्ण;

क्रमागत अणु
	BTC_BT_REG_RF		= 0,
	BTC_BT_REG_MODEM	= 1,
	BTC_BT_REG_BLUEWIZE	= 2,
	BTC_BT_REG_VENDOR	= 3,
	BTC_BT_REG_LE		= 4,
	BTC_BT_REG_MAX
पूर्ण;

क्रमागत btc_chip_पूर्णांकerface अणु
	BTC_INTF_UNKNOWN	= 0,
	BTC_INTF_PCI		= 1,
	BTC_INTF_USB		= 2,
	BTC_INTF_SDIO		= 3,
	BTC_INTF_MAX
पूर्ण;

क्रमागत अणु
	BTC_CHIP_UNDEF		= 0,
	BTC_CHIP_CSR_BC4	= 1,
	BTC_CHIP_CSR_BC8	= 2,
	BTC_CHIP_RTL8723A	= 3,
	BTC_CHIP_RTL8821	= 4,
	BTC_CHIP_RTL8723B	= 5,
	BTC_CHIP_MAX
पूर्ण;

क्रमागत अणु
	BTC_MSG_INTERFACE	= 0x0,
	BTC_MSG_ALGORITHM	= 0x1,
	BTC_MSG_MAX
पूर्ण;
बाह्य u32 		GLBtcDbgType[];

/*  following is क्रम BTC_MSG_INTERFACE */
#घोषणा INTF_INIT	BIT0
#घोषणा INTF_NOTIFY	BIT2

/*  following is क्रम BTC_ALGORITHM */
#घोषणा ALGO_BT_RSSI_STATE				BIT0
#घोषणा ALGO_WIFI_RSSI_STATE			BIT1
#घोषणा ALGO_BT_MONITOR					BIT2
#घोषणा ALGO_TRACE						BIT3
#घोषणा ALGO_TRACE_FW					BIT4
#घोषणा ALGO_TRACE_FW_DETAIL			BIT5
#घोषणा ALGO_TRACE_FW_EXEC				BIT6
#घोषणा ALGO_TRACE_SW					BIT7
#घोषणा ALGO_TRACE_SW_DETAIL			BIT8
#घोषणा ALGO_TRACE_SW_EXEC				BIT9

/*  following is क्रम wअगरi link status */
#घोषणा WIFI_STA_CONNECTED				BIT0
#घोषणा WIFI_AP_CONNECTED				BIT1
#घोषणा WIFI_HS_CONNECTED				BIT2
#घोषणा WIFI_P2P_GO_CONNECTED			BIT3
#घोषणा WIFI_P2P_GC_CONNECTED			BIT4

/*  following is क्रम command line utility */
#घोषणा CL_SPRINTF	snम_लिखो
#घोषणा CL_PRINTF	DCMD_Prपूर्णांकf

/*  The following is क्रम dbgview prपूर्णांक */
#अगर DBG
#घोषणा BTC_PRINT(dbgtype, dbgflag, prपूर्णांकstr)\
अणु\
	अगर (GLBtcDbgType[dbgtype] & dbgflag)\
		DbgPrपूर्णांक prपूर्णांकstr;\
पूर्ण

#घोषणा BTC_PRINT_ADDR(dbgtype, dbgflag, prपूर्णांकstr, _Ptr)\
अणु\
	अगर (GLBtcDbgType[dbgtype] & dbgflag) अणु\
		पूर्णांक __i;\
		u8 *ptr = (u8 *)_Ptr;\
		DbgPrपूर्णांक prपूर्णांकstr;\
		DbgPrपूर्णांक(" ");\
		क्रम (__i = 0; __i < 6; __i++)\
			DbgPrपूर्णांक("%02X%s", ptr[__i], (__i == 5) ? "" : "-");\
		DbgPrपूर्णांक("\n");\
	पूर्ण \
पूर्ण

#घोषणा BTC_PRINT_DATA(dbgtype, dbgflag, _TitleString, _HexData, _HexDataLen)\
अणु\
	अगर (GLBtcDbgType[dbgtype] & dbgflag) अणु\
		पूर्णांक __i;\
		u8 *ptr = (u8 *)_HexData;\
		DbgPrपूर्णांक(_TitleString);\
		क्रम (__i = 0; __i < (पूर्णांक)_HexDataLen; __i++) अणु\
			DbgPrपूर्णांक("%02X%s", ptr[__i], (((__i + 1) % 4) == 0) ? "  " : " ");\
			अगर (((__i + 1) % 16) == 0)\
				DbgPrपूर्णांक("\n");\
		पूर्ण \
		DbgPrपूर्णांक("\n");\
	पूर्ण \
पूर्ण

#अन्यथा
#घोषणा BTC_PRINT(dbgtype, dbgflag, prपूर्णांकstr)		 no_prपूर्णांकk prपूर्णांकstr
#घोषणा BTC_PRINT_F(dbgtype, dbgflag, prपूर्णांकstr)		 no_prपूर्णांकk prपूर्णांकstr
#घोषणा BTC_PRINT_ADDR(dbgtype, dbgflag, prपूर्णांकstr, _Ptr) no_prपूर्णांकk prपूर्णांकstr
#घोषणा BTC_PRINT_DATA(dbgtype, dbgflag, _TitleString, _HexData, _HexDataLen) \
			no_prपूर्णांकk("%s %p %zu", _TitleString, _HexData, _HexDataLen)
#पूर्ण_अगर

काष्ठा btc_board_info अणु
	/*  The following is some board inक्रमmation */
	u8 btChipType;
	u8 pgAntNum;	/*  pg ant number */
	u8 btdmAntNum;	/*  ant number क्रम btdm */
	u8 btdmAntPos;		/* Bryant Add to indicate Antenna Position क्रम (pgAntNum = 2) && (btdmAntNum = 1)  (DPDT+1Ant हाल) */
	u8 singleAntPath;	/*  current used क्रम 8723b only, 1 =>s0,  0 =>s1 */
	/* bool				bBtExist; */
पूर्ण;

क्रमागत अणु
	BTC_RSSI_STATE_HIGH			    = 0x0,
	BTC_RSSI_STATE_MEDIUM			= 0x1,
	BTC_RSSI_STATE_LOW			    = 0x2,
	BTC_RSSI_STATE_STAY_HIGH		= 0x3,
	BTC_RSSI_STATE_STAY_MEDIUM		= 0x4,
	BTC_RSSI_STATE_STAY_LOW			= 0x5,
	BTC_RSSI_MAX
पूर्ण;
#घोषणा BTC_RSSI_HIGH(_rssi_)	((_rssi_ == BTC_RSSI_STATE_HIGH || _rssi_ == BTC_RSSI_STATE_STAY_HIGH) ? true : false)
#घोषणा BTC_RSSI_MEDIUM(_rssi_)	((_rssi_ == BTC_RSSI_STATE_MEDIUM || _rssi_ == BTC_RSSI_STATE_STAY_MEDIUM) ? true : false)
#घोषणा BTC_RSSI_LOW(_rssi_)	((_rssi_ == BTC_RSSI_STATE_LOW || _rssi_ == BTC_RSSI_STATE_STAY_LOW) ? true : false)

क्रमागत अणु
	BTC_WIFI_BW_LEGACY			= 0x0,
	BTC_WIFI_BW_HT20			= 0x1,
	BTC_WIFI_BW_HT40			= 0x2,
	BTC_WIFI_BW_MAX
पूर्ण;

क्रमागत अणु
	BTC_WIFI_TRAFFIC_TX			= 0x0,
	BTC_WIFI_TRAFFIC_RX			= 0x1,
	BTC_WIFI_TRAFFIC_MAX
पूर्ण;

क्रमागत अणु
	BTC_WIFI_PNP_WAKE_UP		= 0x0,
	BTC_WIFI_PNP_SLEEP			= 0x1,
	BTC_WIFI_PNP_MAX
पूर्ण;

/*  defined क्रम BFP_BTC_GET */
क्रमागत अणु
	/*  type bool */
	BTC_GET_BL_HS_OPERATION,
	BTC_GET_BL_HS_CONNECTING,
	BTC_GET_BL_WIFI_CONNECTED,
	BTC_GET_BL_WIFI_BUSY,
	BTC_GET_BL_WIFI_SCAN,
	BTC_GET_BL_WIFI_LINK,
	BTC_GET_BL_WIFI_ROAM,
	BTC_GET_BL_WIFI_4_WAY_PROGRESS,
	BTC_GET_BL_WIFI_UNDER_5G,
	BTC_GET_BL_WIFI_AP_MODE_ENABLE,
	BTC_GET_BL_WIFI_ENABLE_ENCRYPTION,
	BTC_GET_BL_WIFI_UNDER_B_MODE,
	BTC_GET_BL_EXT_SWITCH,
	BTC_GET_BL_WIFI_IS_IN_MP_MODE,

	/*  type s32 */
	BTC_GET_S4_WIFI_RSSI,
	BTC_GET_S4_HS_RSSI,

	/*  type u32 */
	BTC_GET_U4_WIFI_BW,
	BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION,
	BTC_GET_U4_WIFI_FW_VER,
	BTC_GET_U4_WIFI_LINK_STATUS,
	BTC_GET_U4_BT_PATCH_VER,

	/*  type u8 */
	BTC_GET_U1_WIFI_DOT11_CHNL,
	BTC_GET_U1_WIFI_CENTRAL_CHNL,
	BTC_GET_U1_WIFI_HS_CHNL,
	BTC_GET_U1_MAC_PHY_MODE,
	BTC_GET_U1_AP_NUM,

	/*  क्रम 1Ant ====== */
	BTC_GET_U1_LPS_MODE,

	BTC_GET_MAX
पूर्ण;

/*  defined क्रम BFP_BTC_SET */
क्रमागत अणु
	/*  type bool */
	BTC_SET_BL_BT_DISABLE,
	BTC_SET_BL_BT_TRAFFIC_BUSY,
	BTC_SET_BL_BT_LIMITED_DIG,
	BTC_SET_BL_FORCE_TO_ROAM,
	BTC_SET_BL_TO_REJ_AP_AGG_PKT,
	BTC_SET_BL_BT_CTRL_AGG_SIZE,
	BTC_SET_BL_INC_SCAN_DEV_NUM,
	BTC_SET_BL_BT_TX_RX_MASK,

	/*  type u8 */
	BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON,
	BTC_SET_U1_AGG_BUF_SIZE,

	/*  type trigger some action */
	BTC_SET_ACT_GET_BT_RSSI,
	BTC_SET_ACT_AGGREGATE_CTRL,
	/*  क्रम 1Ant ====== */
	/*  type bool */

	/*  type u8 */
	BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE,
	BTC_SET_U1_LPS_VAL,
	BTC_SET_U1_RPWM_VAL,
	/*  type trigger some action */
	BTC_SET_ACT_LEAVE_LPS,
	BTC_SET_ACT_ENTER_LPS,
	BTC_SET_ACT_NORMAL_LPS,
	BTC_SET_ACT_DISABLE_LOW_POWER,
	BTC_SET_ACT_UPDATE_RAMASK,
	BTC_SET_ACT_SEND_MIMO_PS,
	/*  BT Coex related */
	BTC_SET_ACT_CTRL_BT_INFO,
	BTC_SET_ACT_CTRL_BT_COEX,
	BTC_SET_ACT_CTRL_8723B_ANT,
	/*  */
	BTC_SET_MAX
पूर्ण;

क्रमागत अणु
	BTC_DBG_DISP_COEX_STATISTICS		= 0x0,
	BTC_DBG_DISP_BT_LINK_INFO			= 0x1,
	BTC_DBG_DISP_FW_PWR_MODE_CMD		= 0x2,
	BTC_DBG_DISP_MAX
पूर्ण;

क्रमागत अणु
	BTC_IPS_LEAVE						= 0x0,
	BTC_IPS_ENTER						= 0x1,
	BTC_IPS_MAX
पूर्ण;

क्रमागत अणु
	BTC_LPS_DISABLE						= 0x0,
	BTC_LPS_ENABLE						= 0x1,
	BTC_LPS_MAX
पूर्ण;

क्रमागत अणु
	BTC_SCAN_FINISH						= 0x0,
	BTC_SCAN_START						= 0x1,
	BTC_SCAN_MAX
पूर्ण;

क्रमागत अणु
	BTC_ASSOCIATE_FINISH				= 0x0,
	BTC_ASSOCIATE_START					= 0x1,
	BTC_ASSOCIATE_MAX
पूर्ण;

क्रमागत अणु
	BTC_MEDIA_DISCONNECT				= 0x0,
	BTC_MEDIA_CONNECT					= 0x1,
	BTC_MEDIA_MAX
पूर्ण;

क्रमागत अणु
	BTC_PACKET_UNKNOWN					= 0x0,
	BTC_PACKET_DHCP						= 0x1,
	BTC_PACKET_ARP						= 0x2,
	BTC_PACKET_EAPOL					= 0x3,
	BTC_PACKET_MAX
पूर्ण;

/* Bryant Add */
क्रमागत अणु
	BTC_ANTENNA_AT_MAIN_PORT = 0x1,
	BTC_ANTENNA_AT_AUX_PORT  = 0x2,
पूर्ण;

प्रकार u8 (*BFP_BTC_R1)(व्योम *pBtcContext, u32 RegAddr);
प्रकार u16(*BFP_BTC_R2)(व्योम *pBtcContext, u32 RegAddr);
प्रकार u32 (*BFP_BTC_R4)(व्योम *pBtcContext, u32 RegAddr);
प्रकार व्योम (*BFP_BTC_W1)(व्योम *pBtcContext, u32 RegAddr, u8 Data);
प्रकार व्योम(*BFP_BTC_W1_BIT_MASK)(
	व्योम *pBtcContext, u32 regAddr, u8 bitMask, u8 data1b
);
प्रकार व्योम (*BFP_BTC_W2)(व्योम *pBtcContext, u32 RegAddr, u16 Data);
प्रकार व्योम (*BFP_BTC_W4)(व्योम *pBtcContext, u32 RegAddr, u32 Data);
प्रकार व्योम (*BFP_BTC_LOCAL_REG_W1)(व्योम *pBtcContext, u32 RegAddr, u8 Data);
प्रकार व्योम (*BFP_BTC_SET_BB_REG)(
	व्योम *pBtcContext, u32 RegAddr, u32 BitMask, u32 Data
);
प्रकार u32 (*BFP_BTC_GET_BB_REG)(व्योम *pBtcContext, u32 RegAddr, u32 BitMask);
प्रकार व्योम (*BFP_BTC_SET_RF_REG)(
	व्योम *pBtcContext, u8 eRFPath, u32 RegAddr, u32 BitMask, u32 Data
);
प्रकार u32 (*BFP_BTC_GET_RF_REG)(
	व्योम *pBtcContext, u8 eRFPath, u32 RegAddr, u32 BitMask
);
प्रकार व्योम (*BFP_BTC_FILL_H2C)(
	व्योम *pBtcContext, u8 elementId, u32 cmdLen, u8 *pCmdBuffer
);

प्रकार	u8 (*BFP_BTC_GET)(व्योम *pBtCoexist, u8 getType, व्योम *pOutBuf);

प्रकार	u8 (*BFP_BTC_SET)(व्योम *pBtCoexist, u8 setType, व्योम *pInBuf);
प्रकार व्योम (*BFP_BTC_SET_BT_REG)(
	व्योम *pBtcContext, u8 regType, u32 offset, u32 value
);
प्रकार u32 (*BFP_BTC_GET_BT_REG)(व्योम *pBtcContext, u8 regType, u32 offset);
प्रकार व्योम (*BFP_BTC_DISP_DBG_MSG)(व्योम *pBtCoexist, u8 dispType);

काष्ठा btc_bt_info अणु
	bool bBtDisabled;
	u8 rssiAdjustForAgcTableOn;
	u8 rssiAdjustFor1AntCoexType;
	bool bPreBtCtrlAggBufSize;
	bool bBtCtrlAggBufSize;
	bool bRejectAggPkt;
	bool bIncreaseScanDevNum;
	bool bBtTxRxMask;
	u8 preAggBufSize;
	u8 aggBufSize;
	bool bBtBusy;
	bool bLimitedDig;
	u16 btHciVer;
	u16 btRealFwVer;
	u8 btFwVer;
	u32 getBtFwVerCnt;

	bool bBtDisableLowPwr;

	bool bBtCtrlLps;
	bool bBtLpsOn;
	bool bForceToRoam;	/*  क्रम 1Ant solution */
	u8 lpsVal;
	u8 rpwmVal;
	u32 raMask;
पूर्ण;

काष्ठा btc_stack_info अणु
	bool bProfileNotअगरied;
	u16 hciVersion;	/*  stack hci version */
	u8 numOfLink;
	bool bBtLinkExist;
	bool bScoExist;
	bool bAclExist;
	bool bA2dpExist;
	bool bHidExist;
	u8 numOfHid;
	bool bPanExist;
	bool bUnknownAclExist;
	s8 minBtRssi;
पूर्ण;

काष्ठा btc_bt_link_info अणु
	bool bBtLinkExist;
	bool bScoExist;
	bool bScoOnly;
	bool bA2dpExist;
	bool bA2dpOnly;
	bool bHidExist;
	bool bHidOnly;
	bool bPanExist;
	bool bPanOnly;
	bool bSlaveRole;
पूर्ण;

काष्ठा btc_statistics अणु
	u32 cntBind;
	u32 cntPowerOn;
	u32 cntInitHwConfig;
	u32 cntInitCoexDm;
	u32 cntIpsNotअगरy;
	u32 cntLpsNotअगरy;
	u32 cntScanNotअगरy;
	u32 cntConnectNotअगरy;
	u32 cntMediaStatusNotअगरy;
	u32 cntSpecialPacketNotअगरy;
	u32 cntBtInfoNotअगरy;
	u32 cntRfStatusNotअगरy;
	u32 cntPeriodical;
	u32 cntCoexDmSwitch;
	u32 cntStackOperationNotअगरy;
	u32 cntDbgCtrl;
पूर्ण;

काष्ठा btc_coexist अणु
	bool bBinded;		/*  make sure only one adapter can bind the data context */
	व्योम *Adapter;		/*  शेष adapter */
	काष्ठा btc_board_info boardInfo;
	काष्ठा btc_bt_info btInfo;		/*  some bt info referenced by non-bt module */
	काष्ठा btc_stack_info stackInfo;
	काष्ठा btc_bt_link_info btLinkInfo;
	क्रमागत btc_chip_पूर्णांकerface chipInterface;

	bool bInitilized;
	bool bStopCoexDm;
	bool bManualControl;
	u8 *cliBuf;
	काष्ठा btc_statistics statistics;
	u8 pwrModeVal[10];

	/*  function poपूर्णांकers */
	/*  io related */
	BFP_BTC_R1 fBtcRead1Byte;
	BFP_BTC_W1 fBtcWrite1Byte;
	BFP_BTC_W1_BIT_MASK fBtcWrite1ByteBitMask;
	BFP_BTC_R2 fBtcRead2Byte;
	BFP_BTC_W2 fBtcWrite2Byte;
	BFP_BTC_R4 fBtcRead4Byte;
	BFP_BTC_W4 fBtcWrite4Byte;
	BFP_BTC_LOCAL_REG_W1 fBtcWriteLocalReg1Byte;
	/*  पढ़ो/ग_लिखो bb related */
	BFP_BTC_SET_BB_REG fBtcSetBbReg;
	BFP_BTC_GET_BB_REG fBtcGetBbReg;

	/*  पढ़ो/ग_लिखो rf related */
	BFP_BTC_SET_RF_REG fBtcSetRfReg;
	BFP_BTC_GET_RF_REG fBtcGetRfReg;

	/*  fill h2c related */
	BFP_BTC_FILL_H2C fBtcFillH2c;
	/*  other */
	BFP_BTC_DISP_DBG_MSG fBtcDispDbgMsg;
	/*  normal get/set related */
	BFP_BTC_GET fBtcGet;
	BFP_BTC_SET fBtcSet;

	BFP_BTC_GET_BT_REG fBtcGetBtReg;
	BFP_BTC_SET_BT_REG fBtcSetBtReg;
पूर्ण;

बाह्य काष्ठा btc_coexist GLBtCoexist;

व्योम EXhalbtcoutsrc_PowerOnSetting(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtcoutsrc_InitHwConfig(काष्ठा btc_coexist *pBtCoexist, u8 bWअगरiOnly);
व्योम EXhalbtcoutsrc_InitCoexDm(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtcoutsrc_IpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtcoutsrc_LpsNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtcoutsrc_ScanNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 type);
व्योम EXhalbtcoutsrc_ConnectNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 action);
व्योम EXhalbtcoutsrc_MediaStatusNotअगरy(
	काष्ठा btc_coexist *pBtCoexist, क्रमागत rt_media_status mediaStatus
);
व्योम EXhalbtcoutsrc_SpecialPacketNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 pktType);
व्योम EXhalbtcoutsrc_BtInfoNotअगरy(
	काष्ठा btc_coexist *pBtCoexist, u8 *पंचांगpBuf, u8 length
);
व्योम EXhalbtcoutsrc_HaltNotअगरy(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtcoutsrc_PnpNotअगरy(काष्ठा btc_coexist *pBtCoexist, u8 pnpState);
व्योम EXhalbtcoutsrc_Periodical(काष्ठा btc_coexist *pBtCoexist);
व्योम EXhalbtcoutsrc_SetChipType(u8 chipType);
व्योम EXhalbtcoutsrc_SetAntNum(u8 type, u8 antNum);
व्योम EXhalbtcoutsrc_SetSingleAntPath(u8 singleAntPath);
व्योम EXhalbtcoutsrc_DisplayBtCoexInfo(काष्ठा btc_coexist *pBtCoexist);

#पूर्ण_अगर
