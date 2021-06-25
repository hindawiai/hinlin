<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित	__HALDMOUTSRC_H__
#घोषणा __HALDMOUTSRC_H__

/*  Definition */
/*  Define all team support ability. */

/*  Define क्रम all teams. Please Define the स्थिरant in your precomp header. */

/* define		DM_ODM_SUPPORT_AP			0 */
/* define		DM_ODM_SUPPORT_ADSL			0 */
/* define		DM_ODM_SUPPORT_CE			0 */
/* define		DM_ODM_SUPPORT_MP			1 */

/*  Define ODM SW team support flag. */

/*  Antenna Switch Relative Definition. */

/*  Add new function SwAntDivCheck8192C(). */
/*  This is the मुख्य function of Antenna भागersity function beक्रमe link. */
/*  Mainly, it just retains last scan result and scan again. */
/*  After that, it compares the scan result to see which one माला_लो better
 *  RSSI. It selects antenna with better receiving घातer and वापसs better
 *  scan result.
 */

#घोषणा	TP_MODE			0
#घोषणा	RSSI_MODE		1
#घोषणा	TRAFFIC_LOW		0
#घोषणा	TRAFFIC_HIGH		1

/* 3 Tx Power Tracking */
/* 3============================================================ */
#घोषणा		DPK_DELTA_MAPPING_NUM	13
#घोषणा		index_mapping_HP_NUM	15

/*  */
/* 3 PSD Handler */
/* 3============================================================ */

#घोषणा	AFH_PSD		1	/* 0:normal PSD scan, 1: only करो 20 pts PSD */
#घोषणा	MODE_40M	0	/* 0:20M, 1:40M */
#घोषणा	PSD_TH2		3
#घोषणा	PSD_CHM		20   /*  Minimum channel number क्रम BT AFH */
#घोषणा	SIR_STEP_SIZE	3
#घोषणा Smooth_Size_1	5
#घोषणा	Smooth_TH_1	3
#घोषणा Smooth_Size_2	10
#घोषणा	Smooth_TH_2	4
#घोषणा Smooth_Size_3	20
#घोषणा	Smooth_TH_3	4
#घोषणा Smooth_Step_Size 5
#घोषणा	Adaptive_SIR	1
#घोषणा	PSD_RESCAN	4
#घोषणा	PSD_SCAN_INTERVAL	700 /* ms */

/* 8723A High Power IGI Setting */
#घोषणा DM_DIG_HIGH_PWR_IGI_LOWER_BOUND	0x22
#घोषणा DM_DIG_Gmode_HIGH_PWR_IGI_LOWER_BOUND 0x28
#घोषणा DM_DIG_HIGH_PWR_THRESHOLD	0x3a

/*  LPS define */
#घोषणा DM_DIG_FA_TH0_LPS		4 /*  4 in lps */
#घोषणा DM_DIG_FA_TH1_LPS		15 /*  15 lps */
#घोषणा DM_DIG_FA_TH2_LPS		30 /*  30 lps */
#घोषणा RSSI_OFFSET_DIG			0x05;

काष्ठा rtw_dig अणु
	u8		Dig_Enable_Flag;
	u8		Dig_Ext_Port_Stage;

	पूर्णांक		RssiLowThresh;
	पूर्णांक		RssiHighThresh;

	u32		FALowThresh;
	u32		FAHighThresh;

	u8		CurSTAConnectState;
	u8		PreSTAConnectState;
	u8		CurMultiSTAConnectState;

	u8		PreIGValue;
	u8		CurIGValue;
	u8		BackupIGValue;

	s8		BackoffVal;
	s8		BackoffVal_range_max;
	s8		BackoffVal_range_min;
	u8		rx_gain_range_max;
	u8		rx_gain_range_min;
	u8		Rssi_val_min;

	u8		PreCCK_CCAThres;
	u8		CurCCK_CCAThres;
	u8		PreCCKPDState;
	u8		CurCCKPDState;

	u8		LargeFAHit;
	u8		ForbiddenIGI;
	u32		Recover_cnt;

	u8		DIG_Dynamic_MIN_0;
	u8		DIG_Dynamic_MIN_1;
	bool		bMediaConnect_0;
	bool		bMediaConnect_1;

	u32		AntDiv_RSSI_max;
	u32		RSSI_max;
पूर्ण;

काष्ठा rtl_ps अणु
	u8		PreCCAState;
	u8		CurCCAState;

	u8		PreRFState;
	u8		CurRFState;

	पूर्णांक		    Rssi_val_min;

	u8		initialize;
	u32		Reg874, RegC70, Reg85C, RegA74;

पूर्ण;

काष्ठा false_alarm_stats अणु
	u32	Cnt_Parity_Fail;
	u32	Cnt_Rate_Illegal;
	u32	Cnt_Crc8_fail;
	u32	Cnt_Mcs_fail;
	u32	Cnt_Ofdm_fail;
	u32	Cnt_Cck_fail;
	u32	Cnt_all;
	u32	Cnt_Fast_Fsync;
	u32	Cnt_SB_Search_fail;
	u32	Cnt_OFDM_CCA;
	u32	Cnt_CCK_CCA;
	u32	Cnt_CCA_all;
	u32	Cnt_BW_USC;	/* Gary */
	u32	Cnt_BW_LSC;	/* Gary */
पूर्ण;

काष्ठा rx_hpc अणु
	u8		RXHP_flag;
	u8		PSD_func_trigger;
	u8		PSD_biपंचांगap_RXHP[80];
	u8		Pre_IGI;
	u8		Cur_IGI;
	u8		Pre_pw_th;
	u8		Cur_pw_th;
	bool		First_समय_enter;
	bool		RXHP_enable;
	u8		TP_Mode;
	काष्ठा समयr_list PSDTimer;
पूर्ण;

#घोषणा ASSOCIATE_ENTRY_NUM	32 /*  Max size of AsocEntry[]. */
#घोषणा	ODM_ASSOCIATE_ENTRY_NUM	ASSOCIATE_ENTRY_NUM

/*  This indicates two dअगरferent steps. */
/*  In SWAW_STEP_PEAK, driver needs to चयन antenna and listen to
 *  the संकेत on the air.
 */
/*  In SWAW_STEP_DETERMINE, driver just compares the संकेत captured in
 *  SWAW_STEP_PEAK with original RSSI to determine अगर it is necessary to
 *  चयन antenna.
 */

#घोषणा SWAW_STEP_PEAK		0
#घोषणा SWAW_STEP_DETERMINE	1

#घोषणा	TP_MODE			0
#घोषणा	RSSI_MODE		1
#घोषणा	TRAFFIC_LOW		0
#घोषणा	TRAFFIC_HIGH		1

काष्ठा sw_ant_चयन अणु
	u8	try_flag;
	s32	PreRSSI;
	u8	CurAntenna;
	u8	PreAntenna;
	u8	RSSI_Trying;
	u8	TestMode;
	u8	bTriggerAntennaSwitch;
	u8	SelectAntennaMap;
	u8	RSSI_target;

	/*  Beक्रमe link Antenna Switch check */
	u8	SWAS_NoLink_State;
	u32	SWAS_NoLink_BK_Reg860;
	bool	ANTA_ON;	/* To indicate Ant A is or not */
	bool	ANTB_ON;	/* To indicate Ant B is on or not */

	s32	RSSI_sum_A;
	s32	RSSI_sum_B;
	s32	RSSI_cnt_A;
	s32	RSSI_cnt_B;
	u64	lastTxOkCnt;
	u64	lastRxOkCnt;
	u64	TXByteCnt_A;
	u64	TXByteCnt_B;
	u64	RXByteCnt_A;
	u64	RXByteCnt_B;
	u8	TrafficLoad;
	काष्ठा समयr_list SwAntennaSwitchTimer;
	/* Hybrid Antenna Diversity */
	u32	CCK_Ant1_Cnt[ASSOCIATE_ENTRY_NUM];
	u32	CCK_Ant2_Cnt[ASSOCIATE_ENTRY_NUM];
	u32	OFDM_Ant1_Cnt[ASSOCIATE_ENTRY_NUM];
	u32	OFDM_Ant2_Cnt[ASSOCIATE_ENTRY_NUM];
	u32	RSSI_Ant1_Sum[ASSOCIATE_ENTRY_NUM];
	u32	RSSI_Ant2_Sum[ASSOCIATE_ENTRY_NUM];
	u8	TxAnt[ASSOCIATE_ENTRY_NUM];
	u8	TargetSTA;
	u8	antsel;
	u8	RxIdleAnt;
पूर्ण;

काष्ठा edca_turbo अणु
	bool bCurrentTurboEDCA;
	bool bIsCurRDLState;
	u32	prv_traffic_idx; /*  edca turbo */
पूर्ण;

काष्ठा odm_rate_adapt अणु
	u8	Type;		/*  DM_Type_ByFW/DM_Type_ByDriver */
	u8	HighRSSIThresh;	/*  अगर RSSI > HighRSSIThresh	=> RATRState is DM_RATR_STA_HIGH */
	u8	LowRSSIThresh;	/*  अगर RSSI <= LowRSSIThresh	=> RATRState is DM_RATR_STA_LOW */
	u8	RATRState;	/*  Current RSSI level, DM_RATR_STA_HIGH/DM_RATR_STA_MIDDLE/DM_RATR_STA_LOW */
	u32	LastRATR;	/*  RATR Register Content */
पूर्ण;

#घोषणा IQK_MAC_REG_NUM		4
#घोषणा IQK_ADDA_REG_NUM	16
#घोषणा IQK_BB_REG_NUM		9
#घोषणा HP_THERMAL_NUM		8

#घोषणा AVG_THERMAL_NUM		8
#घोषणा IQK_Matrix_REG_NUM	8
#घोषणा IQK_Matrix_Settings_NUM	(1 + 24 + 21)

#घोषणा	DM_Type_ByFWi		0
#घोषणा	DM_Type_ByDriver	1

/*  Declare क्रम common info */

काष्ठा odm_phy_status_info अणु
	u8	RxPWDBAll;
	u8	SignalQuality;	 /*  in 0-100 index. */
	u8	RxMIMOSignalQuality[MAX_PATH_NUM_92CS]; /* EVM */
	u8	RxMIMOSignalStrength[MAX_PATH_NUM_92CS];/*  in 0~100 index */
	s8	RxPower; /*  in dBm Translate from PWdB */
	s8	RecvSignalPower;/*  Real घातer in dBm क्रम this packet, no
				 * beautअगरication and aggregation. Keep this raw
				 * info to be used क्रम the other procedures.
				 */
	u8	BTRxRSSIPercentage;
	u8	SignalStrength; /*  in 0-100 index. */
	u8	RxPwr[MAX_PATH_NUM_92CS];/* per-path's pwdb */
	u8	RxSNR[MAX_PATH_NUM_92CS];/* per-path's SNR */
पूर्ण;

काष्ठा odm_phy_dbg_info अणु
	/* ODM Write,debug info */
	s8	RxSNRdB[MAX_PATH_NUM_92CS];
	u64	NumQryPhyStatus;
	u64	NumQryPhyStatusCCK;
	u64	NumQryPhyStatusOFDM;
	/* Others */
	s32	RxEVM[MAX_PATH_NUM_92CS];
पूर्ण;

काष्ठा odm_per_pkt_info अणु
	s8	Rate;
	u8	StationID;
	bool	bPacketMatchBSSID;
	bool	bPacketToSelf;
	bool	bPacketBeacon;
पूर्ण;

काष्ठा odm_mac_status_info अणु
	u8	test;
पूर्ण;

क्रमागत odm_ability अणु
	/*  BB Team */
	ODM_DIG			= 0x00000001,
	ODM_HIGH_POWER		= 0x00000002,
	ODM_CCK_CCA_TH		= 0x00000004,
	ODM_FA_STATISTICS	= 0x00000008,
	ODM_RAMASK		= 0x00000010,
	ODM_RSSI_MONITOR	= 0x00000020,
	ODM_SW_ANTDIV		= 0x00000040,
	ODM_HW_ANTDIV		= 0x00000080,
	ODM_BB_PWRSV		= 0x00000100,
	ODM_2TPATHDIV		= 0x00000200,
	ODM_1TPATHDIV		= 0x00000400,
	ODM_PSD2AFH		= 0x00000800
पूर्ण;

/*  2011/10/20 MH Define Common info क्रमागत क्रम all team. */

क्रमागत odm_common_info_def अणु
	/*  Fixed value: */

	/* HOOK BEFORE REG INIT----------- */
	ODM_CMNINFO_PLATFORM = 0,
	ODM_CMNINFO_ABILITY,		/* ODM_ABILITY_E */
	ODM_CMNINFO_INTERFACE,		/* ODM_INTERFACE_E */
	ODM_CMNINFO_MP_TEST_CHIP,
	ODM_CMNINFO_IC_TYPE,		/* ODM_IC_TYPE_E */
	ODM_CMNINFO_CUT_VER,		/* ODM_CUT_VERSION_E */
	ODM_CMNINFO_RF_TYPE,		/* ODM_RF_PATH_E or ODM_RF_TYPE_E? */
	ODM_CMNINFO_BOARD_TYPE,		/* ODM_BOARD_TYPE_E */
	ODM_CMNINFO_EXT_LNA,		/* true */
	ODM_CMNINFO_EXT_PA,
	ODM_CMNINFO_EXT_TRSW,
	ODM_CMNINFO_PATCH_ID,		/* CUSTOMER ID */
	ODM_CMNINFO_BINHCT_TEST,
	ODM_CMNINFO_BWIFI_TEST,
	ODM_CMNINFO_SMART_CONCURRENT,
	/* HOOK BEFORE REG INIT-----------  */

	/*  Dynamic value: */
/*  POINTER REFERENCE-----------  */
	ODM_CMNINFO_MAC_PHY_MODE,	/*  ODM_MAC_PHY_MODE_E */
	ODM_CMNINFO_TX_UNI,
	ODM_CMNINFO_RX_UNI,
	ODM_CMNINFO_WM_MODE,		/*  ODM_WIRELESS_MODE_E */
	ODM_CMNINFO_BAND,		/*  ODM_BAND_TYPE_E */
	ODM_CMNINFO_SEC_CHNL_OFFSET,	/*  ODM_SEC_CHNL_OFFSET_E */
	ODM_CMNINFO_SEC_MODE,		/*  ODM_SECURITY_E */
	ODM_CMNINFO_BW,			/*  ODM_BW_E */
	ODM_CMNINFO_CHNL,

	ODM_CMNINFO_DMSP_GET_VALUE,
	ODM_CMNINFO_BUDDY_ADAPTOR,
	ODM_CMNINFO_DMSP_IS_MASTER,
	ODM_CMNINFO_SCAN,
	ODM_CMNINFO_POWER_SAVING,
	ODM_CMNINFO_ONE_PATH_CCA,	/*  ODM_CCA_PATH_E */
	ODM_CMNINFO_DRV_STOP,
	ODM_CMNINFO_PNP_IN,
	ODM_CMNINFO_INIT_ON,
	ODM_CMNINFO_ANT_TEST,
	ODM_CMNINFO_NET_CLOSED,
	ODM_CMNINFO_MP_MODE,
/*  POINTER REFERENCE----------- */

/* CALL BY VALUE------------- */
	ODM_CMNINFO_WIFI_सूचीECT,
	ODM_CMNINFO_WIFI_DISPLAY,
	ODM_CMNINFO_LINK,
	ODM_CMNINFO_RSSI_MIN,
	ODM_CMNINFO_DBG_COMP,			/*  u64 */
	ODM_CMNINFO_DBG_LEVEL,			/*  u32 */
	ODM_CMNINFO_RA_THRESHOLD_HIGH,		/*  u8 */
	ODM_CMNINFO_RA_THRESHOLD_LOW,		/*  u8 */
	ODM_CMNINFO_RF_ANTENNA_TYPE,		/*  u8 */
	ODM_CMNINFO_BT_DISABLED,
	ODM_CMNINFO_BT_OPERATION,
	ODM_CMNINFO_BT_DIG,
	ODM_CMNINFO_BT_BUSY,			/* Check Bt is using or not */
	ODM_CMNINFO_BT_DISABLE_EDCA,
/* CALL BY VALUE-------------*/

	/*  Dynamic ptr array hook iपंचांगs. */
	ODM_CMNINFO_STA_STATUS,
	ODM_CMNINFO_PHY_STATUS,
	ODM_CMNINFO_MAC_STATUS,
	ODM_CMNINFO_MAX,
पूर्ण;

/*  2011/10/20 MH Define ODM support ability.  ODM_CMNINFO_ABILITY */

क्रमागत odm_ability_def अणु
	/*  BB ODM section BIT 0-15 */
	ODM_BB_DIG			= BIT(0),
	ODM_BB_RA_MASK			= BIT(1),
	ODM_BB_DYNAMIC_TXPWR		= BIT(2),
	ODM_BB_FA_CNT			= BIT(3),
	ODM_BB_RSSI_MONITOR		= BIT(4),
	ODM_BB_CCK_PD			= BIT(5),
	ODM_BB_ANT_DIV			= BIT(6),
	ODM_BB_PWR_SAVE			= BIT(7),
	ODM_BB_PWR_TRA			= BIT(8),
	ODM_BB_RATE_ADAPTIVE		= BIT(9),
	ODM_BB_PATH_DIV			= BIT(10),
	ODM_BB_PSD			= BIT(11),
	ODM_BB_RXHP			= BIT(12),

	/*  MAC DM section BIT 16-23 */
	ODM_MAC_EDCA_TURBO		= BIT(16),
	ODM_MAC_EARLY_MODE		= BIT(17),

	/*  RF ODM section BIT 24-31 */
	ODM_RF_TX_PWR_TRACK		= BIT(24),
	ODM_RF_RX_GAIN_TRACK		= BIT(25),
	ODM_RF_CALIBRATION		= BIT(26),
पूर्ण;

#घोषणा ODM_RTL8188E		BIT(4)

/* ODM_CMNINFO_CUT_VER */
क्रमागत odm_cut_version अणु
	ODM_CUT_A	=	1,
	ODM_CUT_B	=	2,
	ODM_CUT_C	=	3,
	ODM_CUT_D	=	4,
	ODM_CUT_E	=	5,
	ODM_CUT_F	=	6,
	ODM_CUT_TEST	=	7,
पूर्ण;

/*  ODM_CMNINFO_RF_TYPE */
/*  For example 1T2R (A+AB = BIT0|BIT4|BIT5) */
क्रमागत odm_rf_path अणु
	ODM_RF_TX_A	=	BIT(0),
	ODM_RF_TX_B	=	BIT(1),
	ODM_RF_TX_C	=	BIT(2),
	ODM_RF_TX_D	=	BIT(3),
	ODM_RF_RX_A	=	BIT(4),
	ODM_RF_RX_B	=	BIT(5),
	ODM_RF_RX_C	=	BIT(6),
	ODM_RF_RX_D	=	BIT(7),
पूर्ण;

क्रमागत odm_rf_type अणु
	ODM_1T1R	=	0,
	ODM_1T2R	=	1,
	ODM_2T2R	=	2,
	ODM_2T3R	=	3,
	ODM_2T4R	=	4,
	ODM_3T3R	=	5,
	ODM_3T4R	=	6,
	ODM_4T4R	=	7,
पूर्ण;

/*  ODM Dynamic common info value definition */

क्रमागत odm_mac_phy_mode अणु
	ODM_SMSP	= 0,
	ODM_DMSP	= 1,
	ODM_DMDP	= 2,
पूर्ण;

क्रमागत odm_bt_coexist अणु
	ODM_BT_BUSY		= 1,
	ODM_BT_ON		= 2,
	ODM_BT_OFF		= 3,
	ODM_BT_NONE		= 4,
पूर्ण;

/*  ODM_CMNINFO_OP_MODE */
क्रमागत odm_operation_mode अणु
	ODM_NO_LINK		= BIT(0),
	ODM_LINK		= BIT(1),
	ODM_SCAN		= BIT(2),
	ODM_POWERSAVE		= BIT(3),
	ODM_AP_MODE		= BIT(4),
	ODM_CLIENT_MODE		= BIT(5),
	ODM_AD_HOC		= BIT(6),
	ODM_WIFI_सूचीECT		= BIT(7),
	ODM_WIFI_DISPLAY	= BIT(8),
पूर्ण;

/*  ODM_CMNINFO_WM_MODE */
क्रमागत odm_wireless_mode अणु
	ODM_WM_UNKNOWN	= 0x0,
	ODM_WM_B	= BIT(0),
	ODM_WM_G	= BIT(1),
	ODM_WM_A	= BIT(2),
	ODM_WM_N24G	= BIT(3),
	ODM_WM_N5G	= BIT(4),
	ODM_WM_AUTO	= BIT(5),
	ODM_WM_AC	= BIT(6),
पूर्ण;

/*  ODM_CMNINFO_BAND */
क्रमागत odm_band_type अणु
	ODM_BAND_2_4G	= BIT(0),
	ODM_BAND_5G	= BIT(1),
पूर्ण;

/*  ODM_CMNINFO_SEC_CHNL_OFFSET */
क्रमागत odm_sec_chnl_offset अणु
	ODM_DONT_CARE	= 0,
	ODM_BELOW	= 1,
	ODM_ABOVE	= 2
पूर्ण;

/*  ODM_CMNINFO_SEC_MODE */
क्रमागत odm_security अणु
	ODM_SEC_OPEN		= 0,
	ODM_SEC_WEP40		= 1,
	ODM_SEC_TKIP		= 2,
	ODM_SEC_RESERVE		= 3,
	ODM_SEC_AESCCMP		= 4,
	ODM_SEC_WEP104		= 5,
	ODM_WEP_WPA_MIXED	= 6, /*  WEP + WPA */
	ODM_SEC_SMS4		= 7,
पूर्ण;

/*  ODM_CMNINFO_BW */
क्रमागत odm_bw अणु
	ODM_BW20M		= 0,
	ODM_BW40M		= 1,
	ODM_BW80M		= 2,
	ODM_BW160M		= 3,
	ODM_BW10M		= 4,
पूर्ण;

/*  ODM_CMNINFO_BOARD_TYPE */
क्रमागत odm_board_type अणु
	ODM_BOARD_NORMAL	= 0,
	ODM_BOARD_HIGHPWR	= 1,
	ODM_BOARD_MINICARD	= 2,
	ODM_BOARD_SLIM		= 3,
	ODM_BOARD_COMBO		= 4,
पूर्ण;

/*  ODM_CMNINFO_ONE_PATH_CCA */
क्रमागत odm_cca_path अणु
	ODM_CCA_2R		= 0,
	ODM_CCA_1R_A		= 1,
	ODM_CCA_1R_B		= 2,
पूर्ण;

काष्ठा odm_ra_info अणु
	u8 RateID;
	u32 RateMask;
	u32 RAUseRate;
	u8 RateSGI;
	u8 RssiStaRA;
	u8 PreRssiStaRA;
	u8 SGIEnable;
	u8 DecisionRate;
	u8 PreRate;
	u8 HighestRate;
	u8 LowestRate;
	u32 NscUp;
	u32 NscDown;
	u16 RTY[5];
	u32 TOTAL;
	u16 DROP;
	u8 Active;
	u16 RptTime;
	u8 RAWaitingCounter;
	u8 RAPendingCounter;
	u8 PTActive;	/*  on or off */
	u8 PTTryState;	/*  0 trying state, 1 क्रम decision state */
	u8 PTStage;	/*  0~6 */
	u8 PTStopCount;	/* Stop PT counter */
	u8 PTPreRate;	/*  अगर rate change करो PT */
	u8 PTPreRssi;	/*  अगर RSSI change 5% करो PT */
	u8 PTModeSS;	/*  decide whitch rate should करो PT */
	u8 RAstage;	/*  StageRA, decide how many बार RA will be करोne
			 * between PT
			 */
	u8 PTSmoothFactor;
पूर्ण;

काष्ठा ijk_matrix_regs_set अणु
	bool	bIQKDone;
	s32	Value[1][IQK_Matrix_REG_NUM];
पूर्ण;

काष्ठा odm_rf_cal अणु
	/* क्रम tx घातer tracking */
	u32	RegA24; /*  क्रम TempCCK */
	s32	RegE94;
	s32	RegE9C;
	s32	RegEB4;
	s32	RegEBC;

	u8	TXPowercount;
	bool	bTXPowerTracking;
	u8	TxPowerTrackControl; /* क्रम mp mode, turn off txpwrtracking
				      * as शेष
				      */
	u8	TM_Trigger;
	u8	InternalPA5G[2];	/* pathA / pathB */

	u8	ThermalMeter[2];    /* ThermalMeter, index 0 क्रम RFIC0,
				     * and 1 क्रम RFIC1
				     */
	u8	ThermalValue;
	u8	ThermalValue_LCK;
	u8	ThermalValue_IQK;
	u8	ThermalValue_DPK;
	u8	ThermalValue_AVG[AVG_THERMAL_NUM];
	u8	ThermalValue_AVG_index;
	u8	ThermalValue_RxGain;
	u8	ThermalValue_Crystal;
	u8	ThermalValue_DPKstore;
	u8	ThermalValue_DPKtrack;
	bool	TxPowerTrackingInProgress;
	bool	bDPKenable;

	bool	bReloadtxघातerindex;
	u8	bRfPiEnable;
	u32	TXPowerTrackingCallbackCnt; /* cosa add क्रम debug */

	u8	bCCKinCH14;
	u8	CCK_index;
	u8	OFDM_index[2];
	bool bDoneTxघातer;

	u8	ThermalValue_HP[HP_THERMAL_NUM];
	u8	ThermalValue_HP_index;
	काष्ठा ijk_matrix_regs_set IQKMatrixRegSetting[IQK_Matrix_Settings_NUM];

	u8	Delta_IQK;
	u8	Delta_LCK;

	/* क्रम IQK */
	u32	RegC04;
	u32	Reg874;
	u32	RegC08;
	u32	RegB68;
	u32	RegB6C;
	u32	Reg870;
	u32	Reg860;
	u32	Reg864;

	bool	bIQKInitialized;
	bool	bLCKInProgress;
	bool	bAntennaDetected;
	u32	ADDA_backup[IQK_ADDA_REG_NUM];
	u32	IQK_MAC_backup[IQK_MAC_REG_NUM];
	u32	IQK_BB_backup_recover[9];
	u32	IQK_BB_backup[IQK_BB_REG_NUM];

	/* क्रम APK */
	u32	APKoutput[2][2]; /* path A/B; output1_1a/output1_2a */
	u8	bAPKकरोne;
	u8	bAPKThermalMeterIgnore;
	u8	bDPकरोne;
	u8	bDPPathAOK;
	u8	bDPPathBOK;
पूर्ण;

/*  ODM Dynamic common info value definition */

काष्ठा fast_ant_train अणु
	u8	Bssid[6];
	u8	antsel_rx_keep_0;
	u8	antsel_rx_keep_1;
	u8	antsel_rx_keep_2;
	u32	antSumRSSI[7];
	u32	antRSSIcnt[7];
	u32	antAveRSSI[7];
	u8	FAT_State;
	u32	TrainIdx;
	u8	antsel_a[ODM_ASSOCIATE_ENTRY_NUM];
	u8	antsel_b[ODM_ASSOCIATE_ENTRY_NUM];
	u8	antsel_c[ODM_ASSOCIATE_ENTRY_NUM];
	u32	MainAnt_Sum[ODM_ASSOCIATE_ENTRY_NUM];
	u32	AuxAnt_Sum[ODM_ASSOCIATE_ENTRY_NUM];
	u32	MainAnt_Cnt[ODM_ASSOCIATE_ENTRY_NUM];
	u32	AuxAnt_Cnt[ODM_ASSOCIATE_ENTRY_NUM];
	u8	RxIdleAnt;
	bool	bBecomeLinked;
पूर्ण;

क्रमागत fat_state अणु
	FAT_NORMAL_STATE		= 0,
	FAT_TRAINING_STATE		= 1,
पूर्ण;

क्रमागत ant_भाग_प्रकारype अणु
	NO_ANTDIV			= 0xFF,
	CG_TRX_HW_ANTDIV		= 0x01,
	CGCS_RX_HW_ANTDIV		= 0x02,
	FIXED_HW_ANTDIV			= 0x03,
	CG_TRX_SMART_ANTDIV		= 0x04,
	CGCS_RX_SW_ANTDIV		= 0x05,
पूर्ण;

/* Copy from SD4 defined काष्ठाure. We use to support PHY DM पूर्णांकegration. */
काष्ठा odm_dm_काष्ठा अणु
	/*	Add क्रम dअगरferent team use temporarily */
	काष्ठा adapter *Adapter;	/*  For CE/NIC team */
	काष्ठा rtl8192cd_priv *priv;	/*  For AP/ADSL team */
	/*  WHen you use above poपूर्णांकers, they must be initialized. */
	bool	odm_पढ़ोy;

	काष्ठा rtl8192cd_priv *fake_priv;
	u64	DebugComponents;
	u32	DebugLevel;

/*  ODM HANDLE, DRIVER NEEDS NOT TO HOOK------ */
	bool	bCckHighPower;
	u8	RFPathRxEnable;		/*  ODM_CMNINFO_RFPATH_ENABLE */
	u8	ControlChannel;
/*  ODM HANDLE, DRIVER NEEDS NOT TO HOOK------ */

/* 1  COMMON INFORMATION */
	/*  Init Value */
/* HOOK BEFORE REG INIT----------- */
	/*  ODM Platक्रमm info AP/ADSL/CE/MP = 1/2/3/4 */
	u8	SupportPlatक्रमm;
	/*  ODM Support Ability DIG/RATR/TX_PWR_TRACK/... = 1/2/3/... */
	u32	SupportAbility;
	/*  ODM PCIE/USB/SDIO/GSPI = 0/1/2/3 */
	u8	SupportInterface;
	/*  ODM composite or independent. Bit oriented/ 92C+92D+ .... or any
	 *  other type = 1/2/3/...
	 */
	u32	SupportICType;
	/*  Cut Version TestChip/A-cut/B-cut... = 0/1/2/3/... */
	u8	CutVersion;
	/*  Board Type Normal/HighPower/MiniCard/SLIM/Combo/. = 0/1/2/3/4/. */
	u8	BoardType;
	/*  with बाह्यal LNA  NO/Yes = 0/1 */
	u8	ExtLNA;
	/*  with बाह्यal PA  NO/Yes = 0/1 */
	u8	ExtPA;
	/*  with बाह्यal TRSW  NO/Yes = 0/1 */
	u8	ExtTRSW;
	u8	PatchID; /* Customer ID */
	bool	bInHctTest;
	bool	bWIFITest;

	bool	bDualMacSmartConcurrent;
	u32	BK_SupportAbility;
	u8	AntDivType;
/* HOOK BEFORE REG INIT----------- */

	/*  Dynamic Value */
/*  POINTER REFERENCE----------- */

	u8	u8_temp;
	bool	bool_temp;
	काष्ठा adapter *adapter_temp;

	/*  MAC PHY Mode SMSP/DMSP/DMDP = 0/1/2 */
	u8	*pMacPhyMode;
	/* TX Unicast byte count */
	u64	*pNumTxBytesUnicast;
	/* RX Unicast byte count */
	u64	*pNumRxBytesUnicast;
	/*  Wireless mode B/G/A/N = BIT0/BIT1/BIT2/BIT3 */
	u8	*pWirelessMode; /* ODM_WIRELESS_MODE_E */
	/*  Frequence band 2.4G/5G = 0/1 */
	u8	*pBandType;
	/*  Secondary channel offset करोn't_care/below/above = 0/1/2 */
	u8	*pSecChOffset;
	/*  Security mode Open/WEP/AES/TKIP = 0/1/2/3 */
	u8	*pSecurity;
	/*  BW info 20M/40M/80M = 0/1/2 */
	u8	*pBandWidth;
	/*  Central channel location Ch1/Ch2/.... */
	u8	*pChannel;	/* central channel number */
	/*  Common info क्रम 92D DMSP */

	bool	*pbGetValueFromOtherMac;
	काष्ठा adapter **pBuddyAdapter;
	bool	*pbMasterOfDMSP; /* MAC0: master, MAC1: slave */
	/*  Common info क्रम Status */
	bool	*pbScanInProcess;
	bool	*pbPowerSaving;
	/*  CCA Path 2-path/path-A/path-B = 0/1/2; using ODM_CCA_PATH_E. */
	u8	*pOnePathCCA;
	/* pMgntInfo->AntennaTest */
	u8	*pAntennaTest;
	bool	*pbNet_बंदd;
/*  POINTER REFERENCE----------- */
	/*  */
/* CALL BY VALUE------------- */
	bool	bWIFI_Direct;
	bool	bWIFI_Display;
	bool	bLinked;
	u8	RSSI_Min;
	u8	InterfaceIndex; /*  Add क्रम 92D  dual MAC: 0--Mac0 1--Mac1 */
	bool	bIsMPChip;
	bool	bOneEntryOnly;
	/*  Common info क्रम BTDM */
	bool	bBtDisabled;	/*  BT is disabled */
	bool	bBtHsOperation;	/*  BT HS mode is under progress */
	u8	btHsDigVal;	/*  use BT rssi to decide the DIG value */
	bool	bBtDisableEdcaTurbo;/* Under some condition, करोn't enable the
				     * EDCA Turbo
				     */
	bool	bBtBusy;			/*  BT is busy. */
/* CALL BY VALUE------------- */

	/* 2 Define STA info. */
	/*  _ODM_STA_INFO */
	/*  For MP, we need to reduce one array poपूर्णांकer क्रम शेष port.??*/
	काष्ठा sta_info *pODM_StaInfo[ODM_ASSOCIATE_ENTRY_NUM];

	u16	CurrminRptTime;
	काष्ठा odm_ra_info RAInfo[ODM_ASSOCIATE_ENTRY_NUM]; /* Use MacID as
							     * array index. STA MacID=0,
							     * VWiFi Client MacID=अणु1, ODM_ASSOCIATE_ENTRY_NUM-1पूर्ण
							     */
	/*  */
	/*  2012/02/14 MH Add to share 88E ra with other SW team. */
	/*  We need to colelct all support abilit to a proper area. */
	/*  */
	bool	RaSupport88E;

	/*  Define ........... */

	/*  Latest packet phy info (ODM ग_लिखो) */
	काष्ठा odm_phy_dbg_info PhyDbgInfo;

	/*  Latest packet phy info (ODM ग_लिखो) */
	काष्ठा odm_mac_status_info *pMacInfo;

	/*  Dअगरferent Team independt काष्ठाure?? */

	/* ODM Structure */
	काष्ठा fast_ant_train DM_FatTable;
	काष्ठा rtw_dig	DM_DigTable;
	काष्ठा rtl_ps	DM_PSTable;
	काष्ठा rx_hpc	DM_RXHP_Table;
	काष्ठा false_alarm_stats FalseAlmCnt;
	काष्ठा false_alarm_stats FlaseAlmCntBuddyAdapter;
	काष्ठा sw_ant_चयन DM_SWAT_Table;
	bool		RSSI_test;

	काष्ठा edca_turbo DM_EDCA_Table;
	u32		WMMEDCA_BE;
	/*  Copy from SD4 काष्ठाure */
	/*  */
	/*  ================================================== */
	/*  */

	bool	*pbDriverStopped;
	bool	*pbDriverIsGoingToPnpSetPowerSleep;
	bool	*pinit_adpt_in_progress;

	/* PSD */
	bool	bUserAssignLevel;
	काष्ठा समयr_list PSDTimer;
	u8	RSSI_BT;			/* come from BT */
	bool	bPSDinProcess;
	bool	bDMInitialGainEnable;

	/* क्रम rate adaptive, in fact,  88c/92c fw will handle this */
	u8	bUseRAMask;

	काष्ठा odm_rate_adapt RateAdaptive;

	काष्ठा odm_rf_cal RFCalibrateInfo;

	/*  TX घातer tracking */
	u8	BbSwingIdxOfdm;
	u8	BbSwingIdxOfdmCurrent;
	u8	BbSwingIdxOfdmBase;
	bool	BbSwingFlagOfdm;
	u8	BbSwingIdxCck;
	u8	BbSwingIdxCckCurrent;
	u8	BbSwingIdxCckBase;
	bool	BbSwingFlagCck;
	u8	*mp_mode;
	/*  ODM प्रणाली resource. */

	/*  ODM relative समय. */
	काष्ठा समयr_list PathDivSwitchTimer;
	/* 2011.09.27 add क्रम Path Diversity */
	काष्ठा समयr_list CCKPathDiversityTimer;
	काष्ठा समयr_list FastAntTrainingTimer;
पूर्ण;		/*  DM_Dynamic_Mechanism_Structure */

#घोषणा ODM_RF_PATH_MAX 3

क्रमागत ODM_RF_CONTENT अणु
	odm_radioa_txt = 0x1000,
	odm_radiob_txt = 0x1001,
	odm_radioc_txt = 0x1002,
	odm_radiod_txt = 0x1003
पूर्ण;

/*  Status code */
क्रमागत rt_status अणु
	RT_STATUS_SUCCESS,
	RT_STATUS_FAILURE,
	RT_STATUS_PENDING,
	RT_STATUS_RESOURCE,
	RT_STATUS_INVALID_CONTEXT,
	RT_STATUS_INVALID_PARAMETER,
	RT_STATUS_NOT_SUPPORT,
	RT_STATUS_OS_API_FAILED,
पूर्ण;

/* 3=========================================================== */
/* 3 DIG */
/* 3=========================================================== */

क्रमागत dm_dig_op अणु
	RT_TYPE_THRESH_HIGH	= 0,
	RT_TYPE_THRESH_LOW	= 1,
	RT_TYPE_BACKOFF		= 2,
	RT_TYPE_RX_GAIN_MIN	= 3,
	RT_TYPE_RX_GAIN_MAX	= 4,
	RT_TYPE_ENABLE		= 5,
	RT_TYPE_DISABLE		= 6,
	DIG_OP_TYPE_MAX
पूर्ण;

#घोषणा		DM_DIG_THRESH_HIGH	40
#घोषणा		DM_DIG_THRESH_LOW	35

#घोषणा		DM_SCAN_RSSI_TH		0x14 /* scan वापस issue क्रम LC */

#घोषणा		DM_false_ALARM_THRESH_LOW	400
#घोषणा		DM_false_ALARM_THRESH_HIGH	1000

#घोषणा		DM_DIG_MAX_NIC			0x4e
#घोषणा		DM_DIG_MIN_NIC			0x1e /* 0x22/0x1c */

#घोषणा		DM_DIG_MAX_AP			0x32
#घोषणा		DM_DIG_MIN_AP			0x20

#घोषणा		DM_DIG_MAX_NIC_HP		0x46
#घोषणा		DM_DIG_MIN_NIC_HP		0x2e

#घोषणा		DM_DIG_MAX_AP_HP		0x42
#घोषणा		DM_DIG_MIN_AP_HP		0x30

/* vivi 92c&92d has dअगरferent definition, 20110504 */
/* this is क्रम 92c */
#घोषणा		DM_DIG_FA_TH0			0x200/* 0x20 */
#घोषणा		DM_DIG_FA_TH1			0x300/* 0x100 */
#घोषणा		DM_DIG_FA_TH2			0x400/* 0x200 */
/* this is क्रम 92d */
#घोषणा		DM_DIG_FA_TH0_92D		0x100
#घोषणा		DM_DIG_FA_TH1_92D		0x400
#घोषणा		DM_DIG_FA_TH2_92D		0x600

#घोषणा		DM_DIG_BACKOFF_MAX		12
#घोषणा		DM_DIG_BACKOFF_MIN		-4
#घोषणा		DM_DIG_BACKOFF_DEFAULT		10

/* 3=========================================================== */
/* 3 AGC RX High Power Mode */
/* 3=========================================================== */
#घोषणा	  LNA_Low_Gain_1		0x64
#घोषणा	  LNA_Low_Gain_2		0x5A
#घोषणा	  LNA_Low_Gain_3		0x58

#घोषणा	  FA_RXHP_TH1			5000
#घोषणा	  FA_RXHP_TH2			1500
#घोषणा	  FA_RXHP_TH3			800
#घोषणा	  FA_RXHP_TH4			600
#घोषणा	  FA_RXHP_TH5			500

/* 3=========================================================== */
/* 3 EDCA */
/* 3=========================================================== */

/* 3=========================================================== */
/* 3 Dynamic Tx Power */
/* 3=========================================================== */
/* Dynamic Tx Power Control Threshold */
#घोषणा		TX_POWER_NEAR_FIELD_THRESH_LVL2	74
#घोषणा		TX_POWER_NEAR_FIELD_THRESH_LVL1	67
#घोषणा		TX_POWER_NEAR_FIELD_THRESH_AP		0x3F

#घोषणा		TxHighPwrLevel_Normal		0
#घोषणा		TxHighPwrLevel_Level1		1
#घोषणा		TxHighPwrLevel_Level2		2
#घोषणा		TxHighPwrLevel_BT1		3
#घोषणा		TxHighPwrLevel_BT2		4
#घोषणा		TxHighPwrLevel_15		5
#घोषणा		TxHighPwrLevel_35		6
#घोषणा		TxHighPwrLevel_50		7
#घोषणा		TxHighPwrLevel_70		8
#घोषणा		TxHighPwrLevel_100		9

/* 3=========================================================== */
/* 3 Rate Adaptive */
/* 3=========================================================== */
#घोषणा		DM_RATR_STA_INIT		0
#घोषणा		DM_RATR_STA_HIGH		1
#घोषणा		DM_RATR_STA_MIDDLE		2
#घोषणा		DM_RATR_STA_LOW			3

/* 3=========================================================== */
/* 3 BB Power Save */
/* 3=========================================================== */

क्रमागत dm_1r_cca अणु
	CCA_1R = 0,
	CCA_2R = 1,
	CCA_MAX = 2,
पूर्ण;

क्रमागत dm_rf अणु
	RF_Save = 0,
	RF_Normal = 1,
	RF_MAX = 2,
पूर्ण;

/* 3=========================================================== */
/* 3 Antenna Diversity */
/* 3=========================================================== */
क्रमागत dm_swas अणु
	Antenna_A = 1,
	Antenna_B = 2,
	Antenna_MAX = 3,
पूर्ण;

/*  Maximal number of antenna detection mechanism needs to perक्रमm. */
#घोषणा	MAX_ANTENNA_DETECTION_CNT	10

/*  Extern Global Variables. */
#घोषणा	OFDM_TABLE_SIZE_92C	37
#घोषणा	OFDM_TABLE_SIZE_92D	43
#घोषणा	CCK_TABLE_SIZE		33

बाह्य	u32 OFDMSwingTable[OFDM_TABLE_SIZE_92D];
बाह्य	u8 CCKSwingTable_Ch1_Ch13[CCK_TABLE_SIZE][8];
बाह्य	u8 CCKSwingTable_Ch14[CCK_TABLE_SIZE][8];

/*  check Sta poपूर्णांकer valid or not */
#घोषणा IS_STA_VALID(pSta)		(pSta)
/*  20100514 Joseph: Add definition क्रम antenna चयनing test after link. */
/*  This indicates two dअगरferent the steps. */
/*  In SWAW_STEP_PEAK, driver needs to चयन antenna and listen to the
 *  संकेत on the air.
 */
/*  In SWAW_STEP_DETERMINE, driver just compares the संकेत captured in
 *  SWAW_STEP_PEAK
 */
/*  with original RSSI to determine अगर it is necessary to चयन antenna. */
#घोषणा SWAW_STEP_PEAK		0
#घोषणा SWAW_STEP_DETERMINE	1

#घोषणा dm_CheckTXPowerTracking ODM_TXPowerTrackingCheck
#घोषणा dm_RF_Saving	ODM_RF_Saving

व्योम ODM_RF_Saving(काष्ठा odm_dm_काष्ठा *pDM_Odm, u8 bForceInNormal);
व्योम ODM_TXPowerTrackingCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम ODM_Write_CCK_CCA_Thres(काष्ठा odm_dm_काष्ठा *pDM_Odm, u8 CurCCK_CCAThres);
bool ODM_RAStateCheck(काष्ठा odm_dm_काष्ठा *pDM_Odm, s32 RSSI,
		      bool bForceUpdate, u8 *pRATRState);
u32 ConvertTo_dB(u32 Value);
u32 ODM_Get_Rate_Biपंचांगap(काष्ठा odm_dm_काष्ठा *pDM_Odm, u32 macid,
			u32 ra_mask, u8 rssi_level);
व्योम ODM_CmnInfoInit(काष्ठा odm_dm_काष्ठा *pDM_Odm,
		     क्रमागत odm_common_info_def CmnInfo, u32 Value);
व्योम ODM_CmnInfoUpdate(काष्ठा odm_dm_काष्ठा *pDM_Odm, u32 CmnInfo, u64 Value);
व्योम ODM_CmnInfoHook(काष्ठा odm_dm_काष्ठा *pDM_Odm,
		     क्रमागत odm_common_info_def CmnInfo, व्योम *pValue);
व्योम ODM_CmnInfoPtrArrayHook(काष्ठा odm_dm_काष्ठा *pDM_Odm,
			     क्रमागत odm_common_info_def CmnInfo,
			     u16 Index, व्योम *pValue);
व्योम ODM_DMInit(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम ODM_DMWatchकरोg(काष्ठा odm_dm_काष्ठा *pDM_Odm);
व्योम ODM_Write_DIG(काष्ठा odm_dm_काष्ठा *pDM_Odm, u8 CurrentIGI);

#पूर्ण_अगर
