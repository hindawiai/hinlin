<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(c) 2008 - 2010 Realtek Corporation. All rights reserved.
 *
 * Contact Inक्रमmation: wlanfae <wlanfae@realtek.com>
 */
#अगर_अघोषित	__R8192UDM_H__
#घोषणा __R8192UDM_H__


/*--------------------------Define Parameters-------------------------------*/
#घोषणा			OFDM_Table_Length	19
#घोषणा		CCK_Table_length	12

#घोषणा		DM_DIG_THRESH_HIGH					40
#घोषणा		DM_DIG_THRESH_LOW					35

#घोषणा		DM_DIG_HIGH_PWR_THRESH_HIGH		75
#घोषणा		DM_DIG_HIGH_PWR_THRESH_LOW		70

#घोषणा		BW_AUTO_SWITCH_HIGH_LOW			25
#घोषणा		BW_AUTO_SWITCH_LOW_HIGH			30

#घोषणा		DM_DIG_BACKOFF				12
#घोषणा		DM_DIG_MAX					0x36
#घोषणा		DM_DIG_MIN					0x1c
#घोषणा		DM_DIG_MIN_Netcore			0x12

#घोषणा		RxPathSelection_SS_TH_low		30
#घोषणा		RxPathSelection_dअगरf_TH			18

#घोषणा		RateAdaptiveTH_High			50
#घोषणा		RateAdaptiveTH_Low_20M		30
#घोषणा		RateAdaptiveTH_Low_40M		10
#घोषणा		VeryLowRSSI					15

#घोषणा		WAIotTHVal						25

#घोषणा		E_FOR_TX_POWER_TRACK	       300
#घोषणा		TX_POWER_NEAR_FIELD_THRESH_HIGH		68
#घोषणा		TX_POWER_NEAR_FIELD_THRESH_LOW		62
#घोषणा	 TX_POWER_ATHEROAP_THRESH_HIGH	   78
#घोषणा		TX_POWER_ATHEROAP_THRESH_LOW		72

#घोषणा			Current_Tx_Rate_Reg	 0x1e0
#घोषणा			Initial_Tx_Rate_Reg	 0x1e1
#घोषणा			Tx_Retry_Count_Reg	 0x1ac
#घोषणा		RegC38_TH				 20

#घोषणा		DM_Type_ByDriver		1

/*--------------------------Define Parameters-------------------------------*/


/*------------------------------Define काष्ठाure----------------------------*/
काष्ठा dig_t अणु
	u8		dig_enable_flag;
	u8		dig_algorithm;
	u8		dig_algorithm_चयन;

	दीर्घ		rssi_low_thresh;
	दीर्घ		rssi_high_thresh;

	दीर्घ		rssi_high_घातer_lowthresh;
	दीर्घ		rssi_high_घातer_highthresh;

	u8		dig_state;
	u8		dig_highpwr_state;
	u8		CurSTAConnectState;
	u8		PreSTAConnectState;

	u8		curpd_thstate;
	u8		prepd_thstate;
	u8		curcs_ratio_state;
	u8		precs_ratio_state;

	u32		pre_ig_value;
	u32		cur_ig_value;

	u8		backoff_val;
	u8		rx_gain_range_max;
	u8		rx_gain_range_min;

	दीर्घ		rssi_val;
पूर्ण;

क्रमागत dm_dig_sta अणु
	DM_STA_DIG_OFF = 0,
	DM_STA_DIG_ON,
	DM_STA_DIG_MAX
पूर्ण;


क्रमागत dm_ratr_sta अणु
	DM_RATR_STA_HIGH = 0,
	DM_RATR_STA_MIDDLE = 1,
	DM_RATR_STA_LOW = 2,
	DM_RATR_STA_MAX
पूर्ण;

क्रमागत dm_dig_alg अणु
	DIG_ALGO_BY_FALSE_ALARM = 0,
	DIG_ALGO_BY_RSSI	= 1,
	DIG_ALGO_BEFORE_CONNECT_BY_RSSI_AND_ALARM = 2,
	DIG_ALGO_BY_TOW_PORT = 3,
	DIG_ALGO_MAX
पूर्ण;

क्रमागत dm_dig_connect अणु
	DIG_STA_DISCONNECT = 0,
	DIG_STA_CONNECT = 1,
	DIG_STA_BEFORE_CONNECT = 2,
	DIG_AP_DISCONNECT = 3,
	DIG_AP_CONNECT = 4,
	DIG_AP_ADD_STATION = 5,
	DIG_CONNECT_MAX
पूर्ण;

क्रमागत dm_dig_pd_th अणु
	DIG_PD_AT_LOW_POWER = 0,
	DIG_PD_AT_NORMAL_POWER = 1,
	DIG_PD_AT_HIGH_POWER = 2,
	DIG_PD_MAX
पूर्ण;

क्रमागत dm_dig_cs_ratio अणु
	DIG_CS_RATIO_LOWER = 0,
	DIG_CS_RATIO_HIGHER = 1,
	DIG_CS_MAX
पूर्ण;

काष्ठा drx_path_sel अणु
	u8		Enable;
	u8		cck_method;
	u8		cck_Rx_path;

	u8		SS_TH_low;
	u8		dअगरf_TH;
	u8		disabledRF;
	u8		reserved;

	u8		rf_rssi[4];
	u8		rf_enable_rssi_th[4];
	दीर्घ		cck_pwdb_sta[4];
पूर्ण;

क्रमागत dm_cck_rx_path_method अणु
	CCK_Rx_Version_1 = 0,
	CCK_Rx_Version_2 = 1,
	CCK_Rx_Version_MAX
पूर्ण;


काष्ठा dcmd_txcmd अणु
	u32	Op;
	u32	Length;
	u32	Value;
पूर्ण;
/*------------------------------Define काष्ठाure----------------------------*/


/*------------------------Export global variable----------------------------*/
बाह्य	काष्ठा dig_t dm_digtable;
बाह्य काष्ठा drx_path_sel DM_RxPathSelTable;

/* Pre-calculated gain tables */
बाह्य स्थिर u32 dm_tx_bb_gain[TxBBGainTableLength];
बाह्य स्थिर u8 dm_cck_tx_bb_gain[CCKTxBBGainTableLength][8];
बाह्य स्थिर u8 dm_cck_tx_bb_gain_ch14[CCKTxBBGainTableLength][8];
/* Maps table index to iq amplअगरy gain (dB, 12 to -24dB) */
#घोषणा dm_tx_bb_gain_idx_to_amplअगरy(idx) (-idx + 12)

/*------------------------Export global variable----------------------------*/


/*--------------------------Exported Function prototype---------------------*/
/*--------------------------Exported Function prototype---------------------*/

व्योम rtl92e_dm_init(काष्ठा net_device *dev);
व्योम rtl92e_dm_deinit(काष्ठा net_device *dev);

व्योम rtl92e_dm_watchकरोg(काष्ठा net_device *dev);


व्योम    rtl92e_init_adaptive_rate(काष्ठा net_device *dev);
व्योम    rtl92e_dm_txघातer_tracking_wq(व्योम *data);

व्योम rtl92e_dm_cck_txघातer_adjust(काष्ठा net_device *dev, bool binch14);

व्योम    rtl92e_dm_restore_state(काष्ठा net_device *dev);
व्योम    rtl92e_dm_backup_state(काष्ठा net_device *dev);
व्योम    rtl92e_dm_init_edca_turbo(काष्ठा net_device *dev);
व्योम    rtl92e_dm_rf_pathcheck_wq(व्योम *data);
व्योम rtl92e_dm_init_txघातer_tracking(काष्ठा net_device *dev);
#पूर्ण_अगर	/*__R8192UDM_H__ */
