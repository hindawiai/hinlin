<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*****************************************************************************
 *	Copyright(c) 2007,  RealTEK Technology Inc. All Right Reserved.
 *
 * Module:		Hal819xUsbDM.h	(RTL8192  Header H File)
 *
 *
 * Note:		For dynamic control definition स्थिरant काष्ठाure.
 *
 *
 * Export:
 *
 * Abbrev:
 *
 * History:
 *	Data		Who		Remark
 *	10/04/2007  MHC		Create initial version.
 *
 *****************************************************************************/
 /* Check to see अगर the file has been included alपढ़ोy.  */
#अगर_अघोषित	__R8192UDM_H__
#घोषणा __R8192UDM_H__

/*--------------------------Define Parameters-------------------------------*/
#घोषणा         DM_DIG_THRESH_HIGH                      40
#घोषणा         DM_DIG_THRESH_LOW                       35

#घोषणा         DM_DIG_HIGH_PWR_THRESH_HIGH             75
#घोषणा         DM_DIG_HIGH_PWR_THRESH_LOW              70

#घोषणा         BW_AUTO_SWITCH_HIGH_LOW                 25
#घोषणा         BW_AUTO_SWITCH_LOW_HIGH                 30

#घोषणा         DM_DIG_BACKOFF                          12
#घोषणा         DM_DIG_MAX                            0x36
#घोषणा         DM_DIG_MIN                            0x1c
#घोषणा         DM_DIG_MIN_NETCORE                    0x12

#घोषणा         RX_PATH_SELECTION_SS_TH_LOW             30
#घोषणा         RX_PATH_SELECTION_DIFF_TH               18

#घोषणा         RATE_ADAPTIVE_TH_HIGH                   50
#घोषणा         RATE_ADAPTIVE_TH_LOW_20M                30
#घोषणा         RATE_ADAPTIVE_TH_LOW_40M                10
#घोषणा         VERY_LOW_RSSI                           15
#घोषणा         CTS_TO_SELF_TH_VAL                      30

/* defined by vivi, क्रम tx घातer track */
#घोषणा         E_FOR_TX_POWER_TRACK                   300
/* Dynamic Tx Power Control Threshold */
#घोषणा         TX_POWER_NEAR_FIELD_THRESH_HIGH         68
#घोषणा         TX_POWER_NEAR_FIELD_THRESH_LOW          62
/* added by amy क्रम atheros AP */
#घोषणा         TX_POWER_ATHEROAP_THRESH_HIGH           78
#घोषणा         TX_POWER_ATHEROAP_THRESH_LOW            72

/* defined by vivi, क्रम showing on UI */
#घोषणा         CURRENT_TX_RATE_REG                  0x1b8
#घोषणा         INITIAL_TX_RATE_REG                  0x1b9
#घोषणा         TX_RETRY_COUNT_REG                   0x1ac
#घोषणा         REG_C38_TH                              20
/*--------------------------Define Parameters-------------------------------*/

/*------------------------------Define काष्ठाure----------------------------*/

क्रमागत dig_algorithm अणु
	DIG_ALGO_BY_FALSE_ALARM = 0,
	DIG_ALGO_BY_RSSI	= 1,
पूर्ण;

क्रमागत dynamic_init_gain_state अणु
	DM_STA_DIG_OFF = 0,
	DM_STA_DIG_ON,
	DM_STA_DIG_MAX
पूर्ण;

क्रमागत dig_connect अणु
	DIG_DISCONNECT = 0,
	DIG_CONNECT    = 1,
पूर्ण;

क्रमागत dig_pkt_detection_threshold अणु
	DIG_PD_AT_LOW_POWER    = 0,
	DIG_PD_AT_NORMAL_POWER = 1,
	DIG_PD_AT_HIGH_POWER   = 2,
पूर्ण;

क्रमागत dig_cck_cs_ratio_state अणु
	DIG_CS_RATIO_LOWER  = 0,
	DIG_CS_RATIO_HIGHER = 1,
पूर्ण;

/* 2007/10/04 MH Define upper and lower threshold of DIG enable or disable. */
काष्ठा dig अणु
	u8                                 dig_enable_flag;
	क्रमागत dig_algorithm                 dig_algorithm;
	u8                                 dig_algorithm_चयन;

	दीर्घ                               rssi_low_thresh;
	दीर्घ                               rssi_high_thresh;

	दीर्घ                               rssi_high_घातer_lowthresh;
	दीर्घ                               rssi_high_घातer_highthresh;

	क्रमागत dynamic_init_gain_state       dig_state;
	क्रमागत dynamic_init_gain_state       dig_highpwr_state;
	क्रमागत dig_connect                   cur_connect_state;
	क्रमागत dig_connect                   pre_connect_state;

	क्रमागत dig_pkt_detection_threshold   curpd_thstate;
	क्रमागत dig_pkt_detection_threshold   prepd_thstate;
	क्रमागत dig_cck_cs_ratio_state        curcs_ratio_state;
	क्रमागत dig_cck_cs_ratio_state        precs_ratio_state;

	u32                                pre_ig_value;
	u32                                cur_ig_value;

	u8                                 backoff_val;
	u8                                 rx_gain_range_min;

	दीर्घ                               rssi_val;
पूर्ण;

क्रमागत cck_rx_path_method अणु
	CCK_RX_VERSION_1 = 0,
	CCK_RX_VERSION_2 = 1,
पूर्ण;

काष्ठा dynamic_rx_path_sel अणु
	क्रमागत cck_rx_path_method            cck_method;
	u8                                 cck_rx_path;

	u8                                 disabled_rf;

	u8                                 rf_rssi[4];
	u8                                 rf_enable_rssi_th[4];
	दीर्घ                               cck_pwdb_sta[4];
पूर्ण;

काष्ठा tx_config_cmd अणु
	u32     cmd_op;        /* Command packet type. */
	u32     cmd_length;    /* Command packet length. */
	u32     cmd_value;
पूर्ण;

/*------------------------------Define काष्ठाure----------------------------*/

/*------------------------Export global variable----------------------------*/
बाह्य काष्ठा dig dm_digtable;
बाह्य u8 dm_shaकरोw[16][256];
/*------------------------Export global variable----------------------------*/

/*------------------------Export Marco Definition---------------------------*/

/*------------------------Export Marco Definition---------------------------*/

/*--------------------------Exported Function prototype---------------------*/
व्योम init_hal_dm(काष्ठा net_device *dev);
व्योम deinit_hal_dm(काष्ठा net_device *dev);
व्योम hal_dm_watchकरोg(काष्ठा net_device *dev);
व्योम init_rate_adaptive(काष्ठा net_device *dev);
व्योम dm_txघातer_trackingcallback(काष्ठा work_काष्ठा *work);
व्योम dm_restore_dynamic_mechanism_state(काष्ठा net_device *dev);
व्योम dm_क्रमce_tx_fw_info(काष्ठा net_device *dev,
			 u32 क्रमce_type, u32 क्रमce_value);
व्योम dm_init_edca_turbo(काष्ठा net_device *dev);
व्योम dm_rf_operation_test_callback(अचिन्हित दीर्घ data);
व्योम dm_rf_pathcheck_workitemcallback(काष्ठा work_काष्ठा *work);
व्योम dm_fsync_समयr_callback(काष्ठा समयr_list *t);
व्योम dm_cck_txघातer_adjust(काष्ठा net_device *dev, bool  binch14);
व्योम dm_shaकरोw_init(काष्ठा net_device *dev);
व्योम dm_initialize_txघातer_tracking(काष्ठा net_device *dev);
/*--------------------------Exported Function prototype---------------------*/

#पूर्ण_अगर	/*__R8192UDM_H__ */

/* End of r8192U_dm.h */
