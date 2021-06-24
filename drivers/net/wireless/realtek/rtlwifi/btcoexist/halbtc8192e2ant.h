<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2012  Realtek Corporation.*/

/*****************************************************************
 *   The following is क्रम 8192E 2Ant BT Co-exist definition
 *****************************************************************/
#घोषणा	BT_INFO_8192E_2ANT_B_FTP			BIT7
#घोषणा	BT_INFO_8192E_2ANT_B_A2DP			BIT6
#घोषणा	BT_INFO_8192E_2ANT_B_HID			BIT5
#घोषणा	BT_INFO_8192E_2ANT_B_SCO_BUSY			BIT4
#घोषणा	BT_INFO_8192E_2ANT_B_ACL_BUSY			BIT3
#घोषणा	BT_INFO_8192E_2ANT_B_INQ_PAGE			BIT2
#घोषणा	BT_INFO_8192E_2ANT_B_SCO_ESCO			BIT1
#घोषणा	BT_INFO_8192E_2ANT_B_CONNECTION			BIT0

#घोषणा BTC_RSSI_COEX_THRESH_TOL_8192E_2ANT		2

क्रमागत bt_info_src_8192e_2ant अणु
	BT_INFO_SRC_8192E_2ANT_WIFI_FW			= 0x0,
	BT_INFO_SRC_8192E_2ANT_BT_RSP			= 0x1,
	BT_INFO_SRC_8192E_2ANT_BT_ACTIVE_SEND		= 0x2,
	BT_INFO_SRC_8192E_2ANT_MAX
पूर्ण;

क्रमागत bt_8192e_2ant_bt_status अणु
	BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE	= 0x0,
	BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE		= 0x1,
	BT_8192E_2ANT_BT_STATUS_INQ_PAGE		= 0x2,
	BT_8192E_2ANT_BT_STATUS_ACL_BUSY		= 0x3,
	BT_8192E_2ANT_BT_STATUS_SCO_BUSY		= 0x4,
	BT_8192E_2ANT_BT_STATUS_ACL_SCO_BUSY		= 0x5,
	BT_8192E_2ANT_BT_STATUS_MAX
पूर्ण;

क्रमागत bt_8192e_2ant_coex_algo अणु
	BT_8192E_2ANT_COEX_ALGO_UNDEFINED		= 0x0,
	BT_8192E_2ANT_COEX_ALGO_SCO			= 0x1,
	BT_8192E_2ANT_COEX_ALGO_SCO_PAN			= 0x2,
	BT_8192E_2ANT_COEX_ALGO_HID			= 0x3,
	BT_8192E_2ANT_COEX_ALGO_A2DP			= 0x4,
	BT_8192E_2ANT_COEX_ALGO_A2DP_PANHS		= 0x5,
	BT_8192E_2ANT_COEX_ALGO_PANEDR			= 0x6,
	BT_8192E_2ANT_COEX_ALGO_PANHS			= 0x7,
	BT_8192E_2ANT_COEX_ALGO_PANEDR_A2DP		= 0x8,
	BT_8192E_2ANT_COEX_ALGO_PANEDR_HID		= 0x9,
	BT_8192E_2ANT_COEX_ALGO_HID_A2DP_PANEDR		= 0xa,
	BT_8192E_2ANT_COEX_ALGO_HID_A2DP		= 0xb,
	BT_8192E_2ANT_COEX_ALGO_MAX			= 0xc
पूर्ण;

काष्ठा coex_dm_8192e_2ant अणु
	/* fw mechanism */
	u8 pre_dec_bt_pwr;
	u8 cur_dec_bt_pwr;
	u8 pre_fw_dac_swing_lvl;
	u8 cur_fw_dac_swing_lvl;
	bool cur_ignore_wlan_act;
	bool pre_ignore_wlan_act;
	u8 pre_ps_tdma;
	u8 cur_ps_tdma;
	u8 ps_tdma_para[5];
	u8 tdma_adj_type;
	bool reset_tdma_adjust;
	bool स्वतः_tdma_adjust;
	bool pre_ps_tdma_on;
	bool cur_ps_tdma_on;
	bool pre_bt_स्वतः_report;
	bool cur_bt_स्वतः_report;

	/* sw mechanism */
	bool pre_rf_rx_lpf_shrink;
	bool cur_rf_rx_lpf_shrink;
	u32 bt_rf0x1e_backup;
	bool pre_low_penalty_ra;
	bool cur_low_penalty_ra;
	bool pre_dac_swing_on;
	u32 pre_dac_swing_lvl;
	bool cur_dac_swing_on;
	u32 cur_dac_swing_lvl;
	bool pre_adc_back_off;
	bool cur_adc_back_off;
	bool pre_agc_table_en;
	bool cur_agc_table_en;
	u32 pre_val0x6c0;
	u32 cur_val0x6c0;
	u32 pre_val0x6c4;
	u32 cur_val0x6c4;
	u32 pre_val0x6c8;
	u32 cur_val0x6c8;
	u8 pre_val0x6cc;
	u8 cur_val0x6cc;
	bool limited_dig;

	u32 backup_arfr_cnt1;	/* Auto Rate Fallback Retry cnt */
	u32 backup_arfr_cnt2;	/* Auto Rate Fallback Retry cnt */
	u16 backup_retry_limit;
	u8 backup_ampdu_maxसमय;

	/* algorithm related */
	u8 pre_algorithm;
	u8 cur_algorithm;
	u8 bt_status;
	u8 wअगरi_chnl_info[3];

	u8 pre_ss_type;
	u8 cur_ss_type;

	u32 pre_ra_mask;
	u32 cur_ra_mask;
	u8 cur_ra_mask_type;
	u8 pre_arfr_type;
	u8 cur_arfr_type;
	u8 pre_retry_limit_type;
	u8 cur_retry_limit_type;
	u8 pre_ampdu_समय_प्रकारype;
	u8 cur_ampdu_समय_प्रकारype;
पूर्ण;

काष्ठा coex_sta_8192e_2ant अणु
	bool bt_link_exist;
	bool sco_exist;
	bool a2dp_exist;
	bool hid_exist;
	bool pan_exist;

	bool under_lps;
	bool under_ips;
	u32 high_priority_tx;
	u32 high_priority_rx;
	u32 low_priority_tx;
	u32 low_priority_rx;
	u8 bt_rssi;
	u8 pre_bt_rssi_state;
	u8 pre_wअगरi_rssi_state[4];
	bool c2h_bt_info_req_sent;
	u8 bt_info_c2h[BT_INFO_SRC_8192E_2ANT_MAX][10];
	u32 bt_info_c2h_cnt[BT_INFO_SRC_8192E_2ANT_MAX];
	bool c2h_bt_inquiry_page;
	u8 bt_retry_cnt;
	u8 bt_info_ext;
पूर्ण;

/****************************************************************
 *    The following is पूर्णांकerface which will notअगरy coex module.
 ****************************************************************/
व्योम ex_btc8192e2ant_init_hwconfig(काष्ठा btc_coexist *btcoexist);
व्योम ex_btc8192e2ant_init_coex_dm(काष्ठा btc_coexist *btcoexist);
व्योम ex_btc8192e2ant_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम ex_btc8192e2ant_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम ex_btc8192e2ant_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम ex_btc8192e2ant_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type);
व्योम ex_btc8192e2ant_media_status_notअगरy(काष्ठा btc_coexist *btcoexist,
					 u8 type);
व्योम ex_btc8192e2ant_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist,
					   u8 type);
व्योम ex_btc8192e2ant_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist,
				    u8 *पंचांगpbuf, u8 length);
व्योम ex_btc8192e2ant_stack_operation_notअगरy(काष्ठा btc_coexist *btcoexist,
					    u8 type);
व्योम ex_btc8192e2ant_halt_notअगरy(काष्ठा btc_coexist *btcoexist);
व्योम ex_btc8192e2ant_periodical(काष्ठा btc_coexist *btcoexist);
व्योम ex_btc8192e2ant_display_coex_info(काष्ठा btc_coexist *btcoexist,
				       काष्ठा seq_file *m);
