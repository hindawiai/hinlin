<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#अगर_अघोषित __ODMDIG_H__
#घोषणा __ODMDIG_H__

काष्ठा dig_t अणु /* _Dynamic_Initial_Gain_Threshold_ */
	bool bStopDIG;
	bool bPSDInProgress;

	u8 Dig_Enable_Flag;
	u8 Dig_Ext_Port_Stage;

	पूर्णांक RssiLowThresh;
	पूर्णांक RssiHighThresh;

	u32 FALowThresh;
	u32 FAHighThresh;

	u8 CurSTAConnectState;
	u8 PreSTAConnectState;
	u8 CurMultiSTAConnectState;

	u8 PreIGValue;
	u8 CurIGValue;
	u8 BackupIGValue;		/* MP DIG */
	u8 BT30_CurIGI;
	u8 IGIBackup;

	s8 BackoffVal;
	s8 BackoffVal_range_max;
	s8 BackoffVal_range_min;
	u8 rx_gain_range_max;
	u8 rx_gain_range_min;
	u8 Rssi_val_min;

	u8 PreCCK_CCAThres;
	u8 CurCCK_CCAThres;
	u8 PreCCKPDState;
	u8 CurCCKPDState;
	u8 CCKPDBackup;

	u8 LargeFAHit;
	u8 ForbiddenIGI;
	u32 Recover_cnt;

	u8 DIG_Dynamic_MIN_0;
	u8 DIG_Dynamic_MIN_1;
	bool bMediaConnect_0;
	bool bMediaConnect_1;

	u32 AntDiv_RSSI_max;
	u32 RSSI_max;

	u8 *pbP2pLinkInProgress;
पूर्ण;

काष्ठा  false_ALARM_STATISTICS अणु
	u32 Cnt_Parity_Fail;
	u32 Cnt_Rate_Illegal;
	u32 Cnt_Crc8_fail;
	u32 Cnt_Mcs_fail;
	u32 Cnt_Ofdm_fail;
	u32 Cnt_Ofdm_fail_pre; /* For RTL8881A */
	u32 Cnt_Cck_fail;
	u32 Cnt_all;
	u32 Cnt_Fast_Fsync;
	u32 Cnt_SB_Search_fail;
	u32 Cnt_OFDM_CCA;
	u32 Cnt_CCK_CCA;
	u32 Cnt_CCA_all;
	u32 Cnt_BW_USC; /* Gary */
	u32 Cnt_BW_LSC; /* Gary */
पूर्ण;

क्रमागत ODM_Pause_DIG_TYPE अणु
	ODM_PAUSE_DIG = BIT0,
	ODM_RESUME_DIG = BIT1
पूर्ण;

#घोषणा		DM_DIG_THRESH_HIGH			40
#घोषणा		DM_DIG_THRESH_LOW			35

#घोषणा		DMfalseALARM_THRESH_LOW	400
#घोषणा		DMfalseALARM_THRESH_HIGH	1000

#घोषणा		DM_DIG_MAX_NIC				0x3e
#घोषणा		DM_DIG_MIN_NIC				0x1e /* 0x22//0x1c */
#घोषणा		DM_DIG_MAX_OF_MIN_NIC		0x3e

#घोषणा		DM_DIG_MAX_AP					0x3e
#घोषणा		DM_DIG_MIN_AP					0x1c
#घोषणा		DM_DIG_MAX_OF_MIN			0x2A	/* 0x32 */
#घोषणा		DM_DIG_MIN_AP_DFS				0x20

#घोषणा		DM_DIG_MAX_NIC_HP			0x46
#घोषणा		DM_DIG_MIN_NIC_HP				0x2e

#घोषणा		DM_DIG_MAX_AP_HP				0x42
#घोषणा		DM_DIG_MIN_AP_HP				0x30

#घोषणा		DM_DIG_FA_TH0				0x200/* 0x20 */

#घोषणा		DM_DIG_FA_TH1					0x300
#घोषणा		DM_DIG_FA_TH2					0x400
/* this is क्रम 92d */
#घोषणा		DM_DIG_FA_TH0_92D				0x100
#घोषणा		DM_DIG_FA_TH1_92D				0x400
#घोषणा		DM_DIG_FA_TH2_92D				0x600

#घोषणा		DM_DIG_BACKOFF_MAX			12
#घोषणा		DM_DIG_BACKOFF_MIN			-4
#घोषणा		DM_DIG_BACKOFF_DEFAULT		10

#घोषणा			DM_DIG_FA_TH0_LPS				4 /*  4 in lps */
#घोषणा			DM_DIG_FA_TH1_LPS				15 /*  15 lps */
#घोषणा			DM_DIG_FA_TH2_LPS				30 /*  30 lps */
#घोषणा			RSSI_OFFSET_DIG				0x05

व्योम odm_NHMCounterStatisticsInit(व्योम *pDM_VOID);

व्योम odm_NHMCounterStatistics(व्योम *pDM_VOID);

व्योम odm_NHMBBInit(व्योम *pDM_VOID);

व्योम odm_NHMBB(व्योम *pDM_VOID);

व्योम odm_NHMCounterStatisticsReset(व्योम *pDM_VOID);

व्योम odm_GetNHMCounterStatistics(व्योम *pDM_VOID);

व्योम odm_SearchPwdBLowerBound(व्योम *pDM_VOID, u8 IGI_target);

व्योम odm_AdaptivityInit(व्योम *pDM_VOID);

व्योम odm_Adaptivity(व्योम *pDM_VOID, u8 IGI);

व्योम ODM_Write_DIG(व्योम *pDM_VOID, u8 CurrentIGI);

व्योम odm_PauseDIG(व्योम *pDM_VOID, क्रमागत ODM_Pause_DIG_TYPE PauseType, u8 IGIValue);

व्योम odm_DIGInit(व्योम *pDM_VOID);

व्योम odm_DIG(व्योम *pDM_VOID);

व्योम odm_DIGbyRSSI_LPS(व्योम *pDM_VOID);

व्योम odm_FalseAlarmCounterStatistics(व्योम *pDM_VOID);

व्योम odm_FAThresholdCheck(
	व्योम *pDM_VOID,
	bool bDFSBand,
	bool bPerक्रमmance,
	u32 RxTp,
	u32 TxTp,
	u32 *dm_FA_thres
);

u8 odm_ForbiddenIGICheck(व्योम *pDM_VOID, u8 DIG_Dynamic_MIN, u8 CurrentIGI);

bool odm_DigAbort(व्योम *pDM_VOID);

व्योम odm_CCKPacketDetectionThresh(व्योम *pDM_VOID);

व्योम ODM_Write_CCK_CCA_Thres(व्योम *pDM_VOID, u8 CurCCK_CCAThres);

#पूर्ण_अगर
