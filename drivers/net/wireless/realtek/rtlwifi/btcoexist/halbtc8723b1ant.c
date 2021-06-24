<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2012  Realtek Corporation.*/

/***************************************************************
 * Description:
 *
 * This file is क्रम RTL8723B Co-exist mechanism
 *
 * History
 * 2012/11/15 Cosa first check in.
 *
 ***************************************************************/

/***************************************************************
 * include files
 ***************************************************************/
#समावेश "halbt_precomp.h"
/***************************************************************
 * Global variables, these are अटल variables
 ***************************************************************/
अटल काष्ठा coex_dm_8723b_1ant glcoex_dm_8723b_1ant;
अटल काष्ठा coex_dm_8723b_1ant *coex_dm = &glcoex_dm_8723b_1ant;
अटल काष्ठा coex_sta_8723b_1ant glcoex_sta_8723b_1ant;
अटल काष्ठा coex_sta_8723b_1ant *coex_sta = &glcoex_sta_8723b_1ant;

अटल स्थिर अक्षर *स्थिर glbt_info_src_8723b_1ant[] = अणु
	"BT Info[wifi fw]",
	"BT Info[bt rsp]",
	"BT Info[bt auto report]",
पूर्ण;

अटल u32 glcoex_ver_date_8723b_1ant = 20130918;
अटल u32 glcoex_ver_8723b_1ant = 0x47;

/***************************************************************
 * local function proto type अगर needed
 ***************************************************************/
/***************************************************************
 * local function start with halbtc8723b1ant_
 ***************************************************************/

अटल व्योम halbtc8723b1ant_updatera_mask(काष्ठा btc_coexist *btcoexist,
					  bool क्रमce_exec, u32 dis_rate_mask)
अणु
	coex_dm->curra_mask = dis_rate_mask;

	अगर (क्रमce_exec || (coex_dm->prera_mask != coex_dm->curra_mask))
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_UPDATE_RAMASK,
				   &coex_dm->curra_mask);

	coex_dm->prera_mask = coex_dm->curra_mask;
पूर्ण

अटल व्योम btc8723b1ant_स्वतः_rate_fb_retry(काष्ठा btc_coexist *btcoexist,
					    bool क्रमce_exec, u8 type)
अणु
	bool wअगरi_under_bmode = false;

	coex_dm->cur_arfr_type = type;

	अगर (क्रमce_exec || (coex_dm->pre_arfr_type != coex_dm->cur_arfr_type)) अणु
		चयन (coex_dm->cur_arfr_type) अणु
		हाल 0:	/* normal mode */
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x430,
						   coex_dm->backup_arfr_cnt1);
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x434,
						   coex_dm->backup_arfr_cnt2);
			अवरोध;
		हाल 1:
			btcoexist->btc_get(btcoexist,
					   BTC_GET_BL_WIFI_UNDER_B_MODE,
					   &wअगरi_under_bmode);
			अगर (wअगरi_under_bmode) अणु
				btcoexist->btc_ग_लिखो_4byte(btcoexist,
							   0x430, 0x0);
				btcoexist->btc_ग_लिखो_4byte(btcoexist,
							   0x434, 0x01010101);
			पूर्ण अन्यथा अणु
				btcoexist->btc_ग_लिखो_4byte(btcoexist,
							   0x430, 0x0);
				btcoexist->btc_ग_लिखो_4byte(btcoexist,
							   0x434, 0x04030201);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	coex_dm->pre_arfr_type = coex_dm->cur_arfr_type;
पूर्ण

अटल व्योम halbtc8723b1ant_retry_limit(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, u8 type)
अणु
	coex_dm->cur_retry_limit_type = type;

	अगर (क्रमce_exec || (coex_dm->pre_retry_limit_type !=
			   coex_dm->cur_retry_limit_type)) अणु
		चयन (coex_dm->cur_retry_limit_type) अणु
		हाल 0:	/* normal mode */
			btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x42a,
						   coex_dm->backup_retry_limit);
			अवरोध;
		हाल 1:	/* retry limit = 8 */
			btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x42a, 0x0808);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	coex_dm->pre_retry_limit_type = coex_dm->cur_retry_limit_type;
पूर्ण

अटल व्योम halbtc8723b1ant_ampdu_maxसमय(काष्ठा btc_coexist *btcoexist,
					  bool क्रमce_exec, u8 type)
अणु
	coex_dm->cur_ampdu_समय_प्रकारype = type;

	अगर (क्रमce_exec || (coex_dm->pre_ampdu_समय_प्रकारype !=
		coex_dm->cur_ampdu_समय_प्रकारype)) अणु
		चयन (coex_dm->cur_ampdu_समय_प्रकारype) अणु
		हाल 0:	/* normal mode */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x456,
					coex_dm->backup_ampdu_max_समय);
			अवरोध;
		हाल 1:	/* AMPDU timw = 0x38 * 32us */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x456, 0x38);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	coex_dm->pre_ampdu_समय_प्रकारype = coex_dm->cur_ampdu_समय_प्रकारype;
पूर्ण

अटल व्योम halbtc8723b1ant_limited_tx(काष्ठा btc_coexist *btcoexist,
				       bool क्रमce_exec, u8 ra_masktype,
				       u8 arfr_type, u8 retry_limit_type,
				       u8 ampdu_समय_प्रकारype)
अणु
	चयन (ra_masktype) अणु
	हाल 0:	/* normal mode */
		halbtc8723b1ant_updatera_mask(btcoexist, क्रमce_exec, 0x0);
		अवरोध;
	हाल 1:	/* disable cck 1/2 */
		halbtc8723b1ant_updatera_mask(btcoexist, क्रमce_exec,
					      0x00000003);
		अवरोध;
	/* disable cck 1/2/5.5, ofdm 6/9/12/18/24, mcs 0/1/2/3/4 */
	हाल 2:
		halbtc8723b1ant_updatera_mask(btcoexist, क्रमce_exec,
					      0x0001f1f7);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	btc8723b1ant_स्वतः_rate_fb_retry(btcoexist, क्रमce_exec, arfr_type);
	halbtc8723b1ant_retry_limit(btcoexist, क्रमce_exec, retry_limit_type);
	halbtc8723b1ant_ampdu_maxसमय(btcoexist, क्रमce_exec, ampdu_समय_प्रकारype);
पूर्ण

अटल व्योम halbtc8723b1ant_limited_rx(काष्ठा btc_coexist *btcoexist,
				       bool क्रमce_exec, bool rej_ap_agg_pkt,
				       bool bt_ctrl_agg_buf_size,
				       u8 agg_buf_size)
अणु
	bool reject_rx_agg = rej_ap_agg_pkt;
	bool bt_ctrl_rx_agg_size = bt_ctrl_agg_buf_size;
	u8 rxaggsize = agg_buf_size;

	/**********************************************
	 *	Rx Aggregation related setting
	 **********************************************/
	btcoexist->btc_set(btcoexist, BTC_SET_BL_TO_REJ_AP_AGG_PKT,
			   &reject_rx_agg);
	/* decide BT control aggregation buf size or not  */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE,
			   &bt_ctrl_rx_agg_size);
	/* aggregation buf size, only work
	 * when BT control Rx aggregation size.
	 */
	btcoexist->btc_set(btcoexist, BTC_SET_U1_AGG_BUF_SIZE, &rxaggsize);
	/* real update aggregation setting  */
	btcoexist->btc_set(btcoexist, BTC_SET_ACT_AGGREGATE_CTRL, शून्य);
पूर्ण

अटल व्योम halbtc8723b1ant_query_bt_info(काष्ठा btc_coexist *btcoexist)
अणु
	u8 h2c_parameter[1] = अणु0पूर्ण;

	coex_sta->c2h_bt_info_req_sent = true;

	/* trigger */
	h2c_parameter[0] |= BIT(0);

	btcoexist->btc_fill_h2c(btcoexist, 0x61, 1, h2c_parameter);
पूर्ण

अटल व्योम halbtc8723b1ant_monitor_bt_ctr(काष्ठा btc_coexist *btcoexist)
अणु
	u32 reg_hp_txrx, reg_lp_txrx, u32पंचांगp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0;
	u32 reg_lp_tx = 0, reg_lp_rx = 0;
	अटल u32 num_of_bt_counter_chk;

	reg_hp_txrx = 0x770;
	reg_lp_txrx = 0x774;

	u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, reg_hp_txrx);
	reg_hp_tx = u32पंचांगp & MASKLWORD;
	reg_hp_rx = (u32पंचांगp & MASKHWORD) >> 16;

	u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, reg_lp_txrx);
	reg_lp_tx = u32पंचांगp & MASKLWORD;
	reg_lp_rx = (u32पंचांगp & MASKHWORD) >> 16;

	coex_sta->high_priority_tx = reg_hp_tx;
	coex_sta->high_priority_rx = reg_hp_rx;
	coex_sta->low_priority_tx = reg_lp_tx;
	coex_sta->low_priority_rx = reg_lp_rx;

	अगर ((coex_sta->low_priority_tx > 1050) &&
	    (!coex_sta->c2h_bt_inquiry_page))
		coex_sta->pop_event_cnt++;

	/* reset counter */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0xc);

	/* This part is क्रम wअगरi FW and driver to update BT's status as
	 * disabled.
	 *
	 * The flow is as the following
	 * 1. disable BT
	 * 2. अगर all BT Tx/Rx counter = 0, after 6 sec we query bt info
	 * 3. Because BT will not rsp from mailbox, so wअगरi fw will know BT is
	 * disabled
	 *
	 * 4. FW will rsp c2h क्रम BT that driver will know BT is disabled.
	 */
	अगर ((reg_hp_tx == 0) && (reg_hp_rx == 0) && (reg_lp_tx == 0) &&
	    (reg_lp_rx == 0)) अणु
		num_of_bt_counter_chk++;
		अगर (num_of_bt_counter_chk == 3)
			halbtc8723b1ant_query_bt_info(btcoexist);
	पूर्ण अन्यथा अणु
		num_of_bt_counter_chk = 0;
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_monitor_wअगरi_ctr(काष्ठा btc_coexist *btcoexist)
अणु
	s32 wअगरi_rssi = 0;
	bool wअगरi_busy = false, wअगरi_under_b_mode = false;
	अटल u8 cck_lock_counter;
	u32 total_cnt;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_B_MODE,
			   &wअगरi_under_b_mode);

	अगर (coex_sta->under_ips) अणु
		coex_sta->crc_ok_cck = 0;
		coex_sta->crc_ok_11g = 0;
		coex_sta->crc_ok_11n = 0;
		coex_sta->crc_ok_11n_agg = 0;

		coex_sta->crc_err_cck = 0;
		coex_sta->crc_err_11g = 0;
		coex_sta->crc_err_11n = 0;
		coex_sta->crc_err_11n_agg = 0;
	पूर्ण अन्यथा अणु
		coex_sta->crc_ok_cck =
			btcoexist->btc_पढ़ो_4byte(btcoexist, 0xf88);
		coex_sta->crc_ok_11g =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0xf94);
		coex_sta->crc_ok_11n =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0xf90);
		coex_sta->crc_ok_11n_agg =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0xfb8);

		coex_sta->crc_err_cck =
			btcoexist->btc_पढ़ो_4byte(btcoexist, 0xf84);
		coex_sta->crc_err_11g =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0xf96);
		coex_sta->crc_err_11n =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0xf92);
		coex_sta->crc_err_11n_agg =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0xfba);
	पूर्ण

	/* reset counter */
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xf16, 0x1, 0x1);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xf16, 0x1, 0x0);

	अगर ((wअगरi_busy) && (wअगरi_rssi >= 30) && (!wअगरi_under_b_mode)) अणु
		total_cnt = coex_sta->crc_ok_cck + coex_sta->crc_ok_11g +
			    coex_sta->crc_ok_11n + coex_sta->crc_ok_11n_agg;

		अगर ((coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) ||
		    (coex_dm->bt_status ==
		     BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) ||
		    (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_SCO_BUSY)) अणु
			अगर (coex_sta->crc_ok_cck >
			    (total_cnt - coex_sta->crc_ok_cck)) अणु
				अगर (cck_lock_counter < 3)
					cck_lock_counter++;
			पूर्ण अन्यथा अणु
				अगर (cck_lock_counter > 0)
					cck_lock_counter--;
			पूर्ण

		पूर्ण अन्यथा अणु
			अगर (cck_lock_counter > 0)
				cck_lock_counter--;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cck_lock_counter > 0)
			cck_lock_counter--;
	पूर्ण

	अगर (!coex_sta->pre_ccklock) अणु
		अगर (cck_lock_counter >= 3)
			coex_sta->cck_lock = true;
		अन्यथा
			coex_sta->cck_lock = false;
	पूर्ण अन्यथा अणु
		अगर (cck_lock_counter == 0)
			coex_sta->cck_lock = false;
		अन्यथा
			coex_sta->cck_lock = true;
	पूर्ण

	अगर (coex_sta->cck_lock)
		coex_sta->cck_ever_lock = true;

	coex_sta->pre_ccklock = coex_sta->cck_lock;
पूर्ण

अटल bool btc8723b1ant_is_wअगरi_status_changed(काष्ठा btc_coexist *btcoexist)
अणु
	अटल bool pre_wअगरi_busy;
	अटल bool pre_under_4way, pre_bt_hs_on;
	bool wअगरi_busy = false, under_4way = false, bt_hs_on = false;
	bool wअगरi_connected = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	अगर (wअगरi_connected) अणु
		अगर (wअगरi_busy != pre_wअगरi_busy) अणु
			pre_wअगरi_busy = wअगरi_busy;
			वापस true;
		पूर्ण
		अगर (under_4way != pre_under_4way) अणु
			pre_under_4way = under_4way;
			वापस true;
		पूर्ण
		अगर (bt_hs_on != pre_bt_hs_on) अणु
			pre_bt_hs_on = bt_hs_on;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम halbtc8723b1ant_update_bt_link_info(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	bt_link_info->bt_link_exist = coex_sta->bt_link_exist;
	bt_link_info->sco_exist = coex_sta->sco_exist;
	bt_link_info->a2dp_exist = coex_sta->a2dp_exist;
	bt_link_info->pan_exist = coex_sta->pan_exist;
	bt_link_info->hid_exist = coex_sta->hid_exist;
	bt_link_info->bt_hi_pri_link_exist = coex_sta->bt_hi_pri_link_exist;

	/* work around क्रम HS mode. */
	अगर (bt_hs_on) अणु
		bt_link_info->pan_exist = true;
		bt_link_info->bt_link_exist = true;
	पूर्ण

	/* check अगर Sco only */
	अगर (bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->sco_only = true;
	अन्यथा
		bt_link_info->sco_only = false;

	/* check अगर A2dp only */
	अगर (!bt_link_info->sco_exist && bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->a2dp_only = true;
	अन्यथा
		bt_link_info->a2dp_only = false;

	/* check अगर Pan only */
	अगर (!bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    bt_link_info->pan_exist && !bt_link_info->hid_exist)
		bt_link_info->pan_only = true;
	अन्यथा
		bt_link_info->pan_only = false;

	/* check अगर Hid only */
	अगर (!bt_link_info->sco_exist && !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist && bt_link_info->hid_exist)
		bt_link_info->hid_only = true;
	अन्यथा
		bt_link_info->hid_only = false;
पूर्ण

अटल व्योम halbtc8723b1ant_set_bt_स्वतः_report(काष्ठा btc_coexist *btcoexist,
					       bool enable_स्वतः_report)
अणु
	u8 h2c_parameter[1] = अणु0पूर्ण;

	h2c_parameter[0] = 0;

	अगर (enable_स्वतः_report)
		h2c_parameter[0] |= BIT(0);

	btcoexist->btc_fill_h2c(btcoexist, 0x68, 1, h2c_parameter);
पूर्ण

अटल व्योम halbtc8723b1ant_bt_स्वतः_report(काष्ठा btc_coexist *btcoexist,
					   bool क्रमce_exec,
					   bool enable_स्वतः_report)
अणु
	coex_dm->cur_bt_स्वतः_report = enable_स्वतः_report;

	अगर (!क्रमce_exec) अणु
		अगर (coex_dm->pre_bt_स्वतः_report == coex_dm->cur_bt_स्वतः_report)
			वापस;
	पूर्ण
	halbtc8723b1ant_set_bt_स्वतः_report(btcoexist,
					   coex_dm->cur_bt_स्वतः_report);

	coex_dm->pre_bt_स्वतः_report = coex_dm->cur_bt_स्वतः_report;
पूर्ण

अटल व्योम btc8723b1ant_set_sw_pen_tx_rate_adapt(काष्ठा btc_coexist *btcoexist,
						  bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[6] = अणु0पूर्ण;

	h2c_parameter[0] = 0x6;	/* opCode, 0x6= Retry_Penalty */

	अगर (low_penalty_ra) अणु
		h2c_parameter[1] |= BIT0;
		/* normal rate except MCS7/6/5, OFDM54/48/36 */
		h2c_parameter[2] = 0x00;
		h2c_parameter[3] = 0xf7;  /* MCS7 or OFDM54 */
		h2c_parameter[4] = 0xf8;  /* MCS6 or OFDM48 */
		h2c_parameter[5] = 0xf9;  /* MCS5 or OFDM36 */
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set WiFi Low-Penalty Retry: %s",
		(low_penalty_ra ? "ON!!" : "OFF!!"));

	btcoexist->btc_fill_h2c(btcoexist, 0x69, 6, h2c_parameter);
पूर्ण

अटल व्योम halbtc8723b1ant_low_penalty_ra(काष्ठा btc_coexist *btcoexist,
					   bool क्रमce_exec, bool low_penalty_ra)
अणु
	coex_dm->cur_low_penalty_ra = low_penalty_ra;

	अगर (!क्रमce_exec) अणु
		अगर (coex_dm->pre_low_penalty_ra == coex_dm->cur_low_penalty_ra)
			वापस;
	पूर्ण
	btc8723b1ant_set_sw_pen_tx_rate_adapt(btcoexist,
					      coex_dm->cur_low_penalty_ra);

	coex_dm->pre_low_penalty_ra = coex_dm->cur_low_penalty_ra;
पूर्ण

अटल व्योम halbtc8723b1ant_set_coex_table(काष्ठा btc_coexist *btcoexist,
					   u32 val0x6c0, u32 val0x6c4,
					   u32 val0x6c8, u8 val0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6c0 = 0x%x\n", val0x6c0);
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x6c0, val0x6c0);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6c4 = 0x%x\n", val0x6c4);
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x6c4, val0x6c4);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6c8 = 0x%x\n", val0x6c8);
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x6c8, val0x6c8);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6cc = 0x%x\n", val0x6cc);
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cc, val0x6cc);
पूर्ण

अटल व्योम halbtc8723b1ant_coex_table(काष्ठा btc_coexist *btcoexist,
				       bool क्रमce_exec, u32 val0x6c0,
				       u32 val0x6c4, u32 val0x6c8,
				       u8 val0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s write Coex Table 0x6c0 = 0x%x, 0x6c4 = 0x%x, 0x6cc = 0x%x\n",
		 (क्रमce_exec ? "force to" : ""),
		 val0x6c0, val0x6c4, val0x6cc);
	coex_dm->cur_val0x6c0 = val0x6c0;
	coex_dm->cur_val0x6c4 = val0x6c4;
	coex_dm->cur_val0x6c8 = val0x6c8;
	coex_dm->cur_val0x6cc = val0x6cc;

	अगर (!क्रमce_exec) अणु
		अगर ((coex_dm->pre_val0x6c0 == coex_dm->cur_val0x6c0) &&
		    (coex_dm->pre_val0x6c4 == coex_dm->cur_val0x6c4) &&
		    (coex_dm->pre_val0x6c8 == coex_dm->cur_val0x6c8) &&
		    (coex_dm->pre_val0x6cc == coex_dm->cur_val0x6cc))
			वापस;
	पूर्ण
	halbtc8723b1ant_set_coex_table(btcoexist, val0x6c0, val0x6c4,
				       val0x6c8, val0x6cc);

	coex_dm->pre_val0x6c0 = coex_dm->cur_val0x6c0;
	coex_dm->pre_val0x6c4 = coex_dm->cur_val0x6c4;
	coex_dm->pre_val0x6c8 = coex_dm->cur_val0x6c8;
	coex_dm->pre_val0x6cc = coex_dm->cur_val0x6cc;
पूर्ण

अटल व्योम halbtc8723b1ant_coex_table_with_type(काष्ठा btc_coexist *btcoexist,
						 bool क्रमce_exec, u8 type)
अणु
	coex_sta->coex_table_type = type;

	चयन (type) अणु
	हाल 0:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					   0x55555555, 0xffffff, 0x3);
		अवरोध;
	हाल 1:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					   0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 2:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x5a5a5a5a,
					   0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 3:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					   0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 4:
		अगर ((coex_sta->cck_ever_lock) && (coex_sta->scan_ap_num <= 5))
			halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec,
						   0x55555555, 0xaaaa5a5a,
						   0xffffff, 0x3);
		अन्यथा
			halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec,
						   0x55555555, 0x5a5a5a5a,
						   0xffffff, 0x3);
		अवरोध;
	हाल 5:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x5a5a5a5a,
					   0x5aaa5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 6:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					   0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 7:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0xaaaaaaaa,
					   0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 8:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					   0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 9:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					   0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 10:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					   0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 11:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					   0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 12:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					   0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 13:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					   0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 14:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					   0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 15:
		halbtc8723b1ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					   0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
halbtc8723b1ant_set_fw_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
				       bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	अगर (enable)
		h2c_parameter[0] |= BIT0;	/* function enable */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set FW for BT Ignore Wlan_Act, FW write 0x63 = 0x%x\n",
		h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x63, 1, h2c_parameter);
पूर्ण

अटल व्योम halbtc8723b1ant_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
					    bool क्रमce_exec, bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn Ignore WlanAct %s\n",
		(क्रमce_exec ? "force to" : ""), (enable ? "ON" : "OFF"));
	coex_dm->cur_ignore_wlan_act = enable;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bPreIgnoreWlanAct = %d, bCurIgnoreWlanAct = %d!!\n",
			coex_dm->pre_ignore_wlan_act,
			 coex_dm->cur_ignore_wlan_act);

		अगर (coex_dm->pre_ignore_wlan_act ==
		    coex_dm->cur_ignore_wlan_act)
			वापस;
	पूर्ण
	halbtc8723b1ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
पूर्ण

अटल व्योम halbtc8723b1ant_set_fw_ps_tdma(काष्ठा btc_coexist *btcoexist,
					   u8 byte1, u8 byte2, u8 byte3,
					   u8 byte4, u8 byte5)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[5] = अणु0पूर्ण;
	u8 real_byte1 = byte1, real_byte5 = byte5;
	bool ap_enable = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);

	अगर (ap_enable) अणु
		अगर ((byte1 & BIT4) && !(byte1 & BIT5)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], FW for 1Ant AP mode\n");
			real_byte1 &= ~BIT4;
			real_byte1 |= BIT5;

			real_byte5 |= BIT5;
			real_byte5 &= ~BIT6;
		पूर्ण
	पूर्ण

	h2c_parameter[0] = real_byte1;
	h2c_parameter[1] = byte2;
	h2c_parameter[2] = byte3;
	h2c_parameter[3] = byte4;
	h2c_parameter[4] = real_byte5;

	coex_dm->ps_tdma_para[0] = real_byte1;
	coex_dm->ps_tdma_para[1] = byte2;
	coex_dm->ps_tdma_para[2] = byte3;
	coex_dm->ps_tdma_para[3] = byte4;
	coex_dm->ps_tdma_para[4] = real_byte5;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], PS-TDMA H2C cmd =0x%x%08x\n",
		h2c_parameter[0],
		h2c_parameter[1] << 24 |
		h2c_parameter[2] << 16 |
		h2c_parameter[3] << 8 |
		h2c_parameter[4]);

	btcoexist->btc_fill_h2c(btcoexist, 0x60, 5, h2c_parameter);
पूर्ण

अटल व्योम halbtc8723b1ant_set_lps_rpwm(काष्ठा btc_coexist *btcoexist,
					 u8 lps_val, u8 rpwm_val)
अणु
	u8 lps = lps_val;
	u8 rpwm = rpwm_val;

	btcoexist->btc_set(btcoexist, BTC_SET_U1_LPS_VAL, &lps);
	btcoexist->btc_set(btcoexist, BTC_SET_U1_RPWM_VAL, &rpwm);
पूर्ण

अटल व्योम halbtc8723b1ant_lps_rpwm(काष्ठा btc_coexist *btcoexist,
				     bool क्रमce_exec,
				     u8 lps_val, u8 rpwm_val)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s set lps/rpwm = 0x%x/0x%x\n",
		(क्रमce_exec ? "force to" : ""), lps_val, rpwm_val);
	coex_dm->cur_lps = lps_val;
	coex_dm->cur_rpwm = rpwm_val;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], LPS-RxBeaconMode = 0x%x , LPS-RPWM = 0x%x!!\n",
			coex_dm->cur_lps, coex_dm->cur_rpwm);

		अगर ((coex_dm->pre_lps == coex_dm->cur_lps) &&
		    (coex_dm->pre_rpwm == coex_dm->cur_rpwm)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], LPS-RPWM_Last = 0x%x , LPS-RPWM_Now = 0x%x!!\n",
				coex_dm->pre_rpwm, coex_dm->cur_rpwm);

			वापस;
		पूर्ण
	पूर्ण
	halbtc8723b1ant_set_lps_rpwm(btcoexist, lps_val, rpwm_val);

	coex_dm->pre_lps = coex_dm->cur_lps;
	coex_dm->pre_rpwm = coex_dm->cur_rpwm;
पूर्ण

अटल व्योम halbtc8723b1ant_sw_mechanism(काष्ठा btc_coexist *btcoexist,
					 bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], SM[LpRA] = %d\n", low_penalty_ra);

	halbtc8723b1ant_low_penalty_ra(btcoexist, NORMAL_EXEC, low_penalty_ra);
पूर्ण

अटल व्योम halbtc8723b1ant_set_ant_path(काष्ठा btc_coexist *btcoexist,
					 u8 ant_pos_type, bool क्रमce_exec,
					 bool init_hw_cfg, bool wअगरi_off)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u32 fw_ver = 0, u32पंचांगp = 0, cnt_bt_cal_chk = 0;
	bool pg_ext_चयन = false;
	bool use_ext_चयन = false;
	bool is_in_mp_mode = false;
	u8 h2c_parameter[2] = अणु0पूर्ण, u8पंचांगp = 0;

	coex_dm->cur_ant_pos_type = ant_pos_type;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_EXT_SWITCH, &pg_ext_चयन);
	/* [31:16] = fw ver, [15:0] = fw sub ver */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);

	अगर ((fw_ver < 0xc0000) || pg_ext_चयन)
		use_ext_चयन = true;

	अगर (init_hw_cfg) अणु
		/* WiFi TRx Mask on */
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x780);
		/* हटाओ due to पूर्णांकerrupt is disabled that polling c2h will
		 * fail and delay 100ms.
		 */

		अगर (fw_ver >= 0x180000) अणु
			/* Use H2C to set GNT_BT to HIGH */
			h2c_parameter[0] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		पूर्ण अन्यथा अणु
			/* set grant_bt to high */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x18);
		पूर्ण
		/* set wlan_act control by PTA */
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);

		/* BT select s0/s1 is controlled by BT */
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x67, 0x20, 0x0);
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x39, 0x8, 0x1);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x974, 0xff);
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x944, 0x3, 0x3);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x930, 0x77);
	पूर्ण अन्यथा अगर (wअगरi_off) अणु
		अगर (fw_ver >= 0x180000) अणु
			/* Use H2C to set GNT_BT to HIGH */
			h2c_parameter[0] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		पूर्ण अन्यथा अणु
			/* set grant_bt to high */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x18);
		पूर्ण
		/* set wlan_act to always low */
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE,
				   &is_in_mp_mode);
		अगर (!is_in_mp_mode)
			/* BT select s0/s1 is controlled by BT */
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x67,
							   0x20, 0x0);
		अन्यथा
			/* BT select s0/s1 is controlled by WiFi */
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x67,
							   0x20, 0x1);

		/* 0x4c[24:23]=00, Set Antenna control by BT_RFE_CTRL
		 * BT Venकरोr 0xac=0xf002
		 */
		u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
		u32पंचांगp &= ~BIT23;
		u32पंचांगp &= ~BIT24;
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u32पंचांगp);
	पूर्ण अन्यथा अणु
		/* Use H2C to set GNT_BT to LOW */
		अगर (fw_ver >= 0x180000) अणु
			अगर (btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765) != 0) अणु
				h2c_parameter[0] = 0;
				btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
							h2c_parameter);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* BT calibration check */
			जबतक (cnt_bt_cal_chk <= 20) अणु
				u8पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist,
								  0x49d);
				cnt_bt_cal_chk++;
				अगर (u8पंचांगp & BIT(0)) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], ########### BT is calibrating (wait cnt=%d) ###########\n",
						cnt_bt_cal_chk);
					mdelay(50);
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], ********** BT is NOT calibrating (wait cnt=%d)**********\n",
						cnt_bt_cal_chk);
					अवरोध;
				पूर्ण
			पूर्ण

			/* set grant_bt to PTA */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x0);
		पूर्ण

		अगर (btcoexist->btc_पढ़ो_1byte(btcoexist, 0x76e) != 0xc) अणु
			/* set wlan_act control by PTA */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0xc);
		पूर्ण

		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(
			btcoexist, 0x67, 0x20,
			0x1); /* BT select s0/s1 is controlled by WiFi */
	पूर्ण

	अगर (use_ext_चयन) अणु
		अगर (init_hw_cfg) अणु
			/* 0x4c[23] = 0, 0x4c[24] = 1
			 * Antenna control by WL/BT
			 */
			u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
			u32पंचांगp &= ~BIT23;
			u32पंचांगp |= BIT24;
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u32पंचांगp);

			/* fixed पूर्णांकernal चयन S1->WiFi, S0->BT */
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x948, 0x0);

			अगर (board_info->btdm_ant_pos ==
			    BTC_ANTENNA_AT_MAIN_PORT) अणु
				/* tell firmware "no antenna inverse" */
				h2c_parameter[0] = 0;
				/* ext चयन type */
				h2c_parameter[1] = 1;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			पूर्ण अन्यथा अणु
				/* tell firmware "antenna inverse" */
				h2c_parameter[0] = 1;
				/* ext चयन type */
				h2c_parameter[1] = 1;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			पूर्ण
		पूर्ण

		अगर (क्रमce_exec ||
		    (coex_dm->cur_ant_pos_type != coex_dm->pre_ant_pos_type)) अणु
			/* ext चयन setting */
			चयन (ant_pos_type) अणु
			हाल BTC_ANT_PATH_WIFI:
				अगर (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_ग_लिखो_1byte_biपंचांगask(
						btcoexist, 0x92c, 0x3, 0x1);
				अन्यथा
					btcoexist->btc_ग_लिखो_1byte_biपंचांगask(
						btcoexist, 0x92c, 0x3, 0x2);
				अवरोध;
			हाल BTC_ANT_PATH_BT:
				अगर (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_ग_लिखो_1byte_biपंचांगask(
						btcoexist, 0x92c, 0x3, 0x2);
				अन्यथा
					btcoexist->btc_ग_लिखो_1byte_biपंचांगask(
						btcoexist, 0x92c, 0x3, 0x1);
				अवरोध;
			शेष:
			हाल BTC_ANT_PATH_PTA:
				अगर (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_ग_लिखो_1byte_biपंचांगask(
						btcoexist, 0x92c, 0x3, 0x1);
				अन्यथा
					btcoexist->btc_ग_लिखो_1byte_biपंचांगask(
						btcoexist, 0x92c, 0x3, 0x2);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (init_hw_cfg) अणु
			/* 0x4c[23] = 1, 0x4c[24] = 0,
			 * Antenna control by 0x64
			 */
			u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
			u32पंचांगp |= BIT23;
			u32पंचांगp &= ~BIT24;
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u32पंचांगp);

			/* Fix Ext चयन Main->S1, Aux->S0 */
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x64, 0x1,
							   0x0);

			अगर (board_info->btdm_ant_pos ==
			    BTC_ANTENNA_AT_MAIN_PORT) अणु
				/* tell firmware "no antenna inverse" */
				h2c_parameter[0] = 0;
				/* पूर्णांकernal चयन type */
				h2c_parameter[1] = 0;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			पूर्ण अन्यथा अणु
				/* tell firmware "antenna inverse" */
				h2c_parameter[0] = 1;
				/* पूर्णांकernal चयन type */
				h2c_parameter[1] = 0;
				btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
							h2c_parameter);
			पूर्ण
		पूर्ण

		अगर (क्रमce_exec ||
		    (coex_dm->cur_ant_pos_type != coex_dm->pre_ant_pos_type)) अणु
			/* पूर्णांकernal चयन setting */
			चयन (ant_pos_type) अणु
			हाल BTC_ANT_PATH_WIFI:
				अगर (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_ग_लिखो_4byte(btcoexist,
							0x948, 0x0);
				अन्यथा
					btcoexist->btc_ग_लिखो_4byte(btcoexist,
							0x948, 0x280);
				अवरोध;
			हाल BTC_ANT_PATH_BT:
				अगर (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_ग_लिखो_4byte(btcoexist,
							0x948, 0x280);
				अन्यथा
					btcoexist->btc_ग_लिखो_4byte(btcoexist,
							0x948, 0x0);
				अवरोध;
			शेष:
			हाल BTC_ANT_PATH_PTA:
				अगर (board_info->btdm_ant_pos ==
				    BTC_ANTENNA_AT_MAIN_PORT)
					btcoexist->btc_ग_लिखो_4byte(btcoexist,
							0x948, 0x200);
				अन्यथा
					btcoexist->btc_ग_लिखो_4byte(btcoexist,
							0x948, 0x80);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	coex_dm->pre_ant_pos_type = coex_dm->cur_ant_pos_type;
पूर्ण

अटल व्योम halbtc8723b1ant_ps_tdma(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, bool turn_on, u8 type)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_busy = false;
	u8 rssi_adjust_val = 0;
	u8 ps_tdma_byte0_val = 0x51;
	u8 ps_tdma_byte3_val = 0x10;
	u8 ps_tdma_byte4_val = 0x50;
	s8 wअगरi_duration_adjust = 0x0;
	अटल bool pre_wअगरi_busy;

	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);

	अगर (wअगरi_busy != pre_wअगरi_busy) अणु
		क्रमce_exec = true;
		pre_wअगरi_busy = wअगरi_busy;
	पूर्ण

	अगर (!क्रमce_exec) अणु
		अगर ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			वापस;
	पूर्ण

	अगर (coex_sta->scan_ap_num <= 5) अणु
		wअगरi_duration_adjust = 5;

		अगर (coex_sta->a2dp_bit_pool >= 35)
			wअगरi_duration_adjust = -10;
		अन्यथा अगर (coex_sta->a2dp_bit_pool >= 45)
			wअगरi_duration_adjust = -15;
	पूर्ण अन्यथा अगर (coex_sta->scan_ap_num >= 40) अणु
		wअगरi_duration_adjust = -15;

		अगर (coex_sta->a2dp_bit_pool < 35)
			wअगरi_duration_adjust = -5;
		अन्यथा अगर (coex_sta->a2dp_bit_pool < 45)
			wअगरi_duration_adjust = -10;
	पूर्ण अन्यथा अगर (coex_sta->scan_ap_num >= 20) अणु
		wअगरi_duration_adjust = -10;

		अगर (coex_sta->a2dp_bit_pool >= 45)
			wअगरi_duration_adjust = -15;
	पूर्ण अन्यथा अणु
		wअगरi_duration_adjust = 0;

		अगर (coex_sta->a2dp_bit_pool >= 35)
			wअगरi_duration_adjust = -10;
		अन्यथा अगर (coex_sta->a2dp_bit_pool >= 45)
			wअगरi_duration_adjust = -15;
	पूर्ण

	अगर ((type == 1) || (type == 2) || (type == 9) || (type == 11) ||
	    (type == 101) || (type == 102) || (type == 109) || (type == 111)) अणु
		अगर (!coex_sta->क्रमce_lps_on) अणु
			/* Native घातer save TDMA, only क्रम A2DP-only हाल
			 * 1/2/9/11 जबतक wअगरi noisy threshold > 30
			 */

			/* no null-pkt */
			ps_tdma_byte0_val = 0x61;
			/* no tx-छोड़ो at BT-slot */
			ps_tdma_byte3_val = 0x11;
			/* 0x778 = d/1 toggle, no dynamic slot */
			ps_tdma_byte4_val = 0x10;
		पूर्ण अन्यथा अणु
			/* null-pkt */
			ps_tdma_byte0_val = 0x51;
			/* tx-छोड़ो at BT-slot */
			ps_tdma_byte3_val = 0x10;
			/* 0x778 = d/1 toggle, dynamic slot */
			ps_tdma_byte4_val = 0x50;
		पूर्ण
	पूर्ण अन्यथा अगर ((type == 3) || (type == 13) || (type == 14) ||
		   (type == 103) || (type == 113) || (type == 114)) अणु
		/* null-pkt */
		ps_tdma_byte0_val = 0x51;
		/* tx-छोड़ो at BT-slot */
		ps_tdma_byte3_val = 0x10;
		/* 0x778 = d/1 toggle, no dynamic slot */
		ps_tdma_byte4_val = 0x10;
	पूर्ण अन्यथा अणु /* native घातer save हाल */
		/* no null-pkt */
		ps_tdma_byte0_val = 0x61;
		/* no tx-छोड़ो at BT-slot */
		ps_tdma_byte3_val = 0x11;
		/* 0x778 = d/1 toggle, no dynamic slot */
		ps_tdma_byte4_val = 0x11;
		/* psTdmaByte4Va is not define क्रम 0x778 = d/1, 1/1 हाल */
	पूर्ण

	/* अगर (bt_link_info->slave_role) */
	अगर ((bt_link_info->slave_role) && (bt_link_info->a2dp_exist))
		/* 0x778 = 0x1 at wअगरi slot (no blocking BT Low-Pri pkts) */
		ps_tdma_byte4_val = ps_tdma_byte4_val | 0x1;

	अगर (type > 100) अणु
		/* set antenna control by SW	 */
		ps_tdma_byte0_val = ps_tdma_byte0_val | 0x82;
		/* set antenna no toggle, control by antenna भागersity */
		ps_tdma_byte3_val = ps_tdma_byte3_val | 0x60;
	पूर्ण

	अगर (turn_on) अणु
		चयन (type) अणु
		शेष:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x1a,
						      0x1a, 0x0,
						      ps_tdma_byte4_val);
			अवरोध;
		हाल 1:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x3a + wअगरi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);

			rssi_adjust_val = 11;
			अवरोध;
		हाल 2:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x2d + wअगरi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 3:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x30, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 4:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x15,
						      0x3, 0x14, 0x0);
			अवरोध;
		हाल 5:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x1f, 0x3,
				ps_tdma_byte3_val, 0x11);
			अवरोध;
		हाल 6:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x20, 0x3,
				ps_tdma_byte3_val, 0x11);
			अवरोध;
		हाल 7:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xc,
						       0x5, 0x0, 0x0);
			अवरोध;
		हाल 8:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x25,
						      0x3, 0x10, 0x0);
			अवरोध;
		हाल 9:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 10:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xa,
						       0xa, 0x0, 0x40);
			अवरोध;
		हाल 11:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 12:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x0a,
						      0x0a, 0x0, 0x50);
			अवरोध;
		हाल 13:
			अगर (coex_sta->scan_ap_num <= 3)
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, ps_tdma_byte0_val, 0x40, 0x3,
					ps_tdma_byte3_val, ps_tdma_byte4_val);
			अन्यथा
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
					ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 14:
			अगर (coex_sta->scan_ap_num <= 3)
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, 0x51, 0x30, 0x3, 0x10, 0x50);
			अन्यथा
				halbtc8723b1ant_set_fw_ps_tdma(
					btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
					ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 15:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xa,
						       0x3, 0x8, 0x0);
			अवरोध;
		हाल 16:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x15,
						      0x3, 0x10, 0x0);
			अवरोध;
		हाल 18:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x25,
						      0x3, 0x10, 0x0);
			अवरोध;
		हाल 20:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x3f, 0x03,
				ps_tdma_byte3_val, 0x10);
			अवरोध;
		हाल 21:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x25,
						      0x03, 0x11, 0x11);
			अवरोध;
		हाल 22:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, 0x10);
			अवरोध;
		हाल 23:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						      0x3, 0x31, 0x18);
			अवरोध;
		हाल 24:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						      0x3, 0x31, 0x18);
			अवरोध;
		हाल 25:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0xa,
						       0x3, 0x31, 0x18);
			अवरोध;
		हाल 26:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0xa,
						       0x3, 0x31, 0x18);
			अवरोध;
		हाल 27:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						      0x3, 0x31, 0x98);
			अवरोध;
		हाल 28:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x69, 0x25,
						      0x3, 0x31, 0x0);
			अवरोध;
		हाल 29:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xab, 0x1a,
						      0x1a, 0x1, 0x10);
			अवरोध;
		हाल 30:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x30,
						       0x3, 0x10, 0x10);
			अवरोध;
		हाल 31:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1a,
						      0x1a, 0, 0x58);
			अवरोध;
		हाल 32:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x35, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 33:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x35, 0x3,
				ps_tdma_byte3_val, 0x10);
			अवरोध;
		हाल 34:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x53, 0x1a,
						      0x1a, 0x0, 0x10);
			अवरोध;
		हाल 35:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x63, 0x1a,
						      0x1a, 0x0, 0x10);
			अवरोध;
		हाल 36:
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x12,
						      0x3, 0x14, 0x50);
			अवरोध;
		हाल 40:
			/* SoftAP only with no sta associated,BT disable ,TDMA
			 * mode क्रम घातer saving
			 *
			 * here softap mode screen off will cost 70-80mA क्रम
			 * phone
			 */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x23, 0x18,
						      0x00, 0x10, 0x24);
			अवरोध;

		हाल 101:
			/* क्रम 1-Ant translate to 2-Ant	 */
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x3a + wअगरi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 102:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val,
				0x2d + wअगरi_duration_adjust, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 103:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x3a, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 105:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x15, 0x3,
				ps_tdma_byte3_val, 0x11);
			अवरोध;
		हाल 106:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x20, 0x3,
				ps_tdma_byte3_val, 0x11);
			अवरोध;
		हाल 109:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 111:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 113:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 114:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x21, 0x3,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 120:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x3f, 0x03,
				ps_tdma_byte3_val, 0x10);
			अवरोध;
		हाल 122:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, 0x10);
			अवरोध;
		हाल 132:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, ps_tdma_byte4_val);
			अवरोध;
		हाल 133:
			halbtc8723b1ant_set_fw_ps_tdma(
				btcoexist, ps_tdma_byte0_val, 0x25, 0x03,
				ps_tdma_byte3_val, 0x11);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable PS tdma */
		चयन (type) अणु
		हाल 8: /* PTA Control */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x8, 0x0,
						       0x0, 0x0, 0x0);
			halbtc8723b1ant_set_ant_path(btcoexist,
						     BTC_ANT_PATH_PTA,
						     FORCE_EXEC,
						     false, false);
			अवरोध;
		हाल 0:
		शेष:
			/* Software control, Antenna at BT side */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0,
						       0x0, 0x0, 0x0);
			अवरोध;
		हाल 1: /* 2-Ant, 0x778=3, antenna control by ant भागersity */
			halbtc8723b1ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						       0x48, 0x0);
			अवरोध;
		पूर्ण
	पूर्ण
	rssi_adjust_val = 0;
	btcoexist->btc_set(btcoexist,
			   BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE,
			   &rssi_adjust_val);

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
पूर्ण

अटल
व्योम btc8723b1ant_tdma_dur_adj_क्रम_acl(काष्ठा btc_coexist *btcoexist,
				       u8 wअगरi_status)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल s32 up, dn, m, n, रुको_count;
	/*  0: no change, +1: increase WiFi duration,
	 * -1: decrease WiFi duration
	 */
	s32 result;
	u8 retry_count = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], TdmaDurationAdjustForAcl()\n");

	अगर ((wअगरi_status ==
	     BT_8723B_1ANT_WIFI_STATUS_NON_CONNECTED_ASSO_AUTH_SCAN) ||
	    (wअगरi_status == BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN) ||
	    (wअगरi_status == BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SPECIAL_PKT)) अणु
		अगर (coex_dm->cur_ps_tdma != 1 && coex_dm->cur_ps_tdma != 2 &&
		    coex_dm->cur_ps_tdma != 3 && coex_dm->cur_ps_tdma != 9) अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 9);
			coex_dm->ps_tdma_du_adj_type = 9;

			up = 0;
			dn = 0;
			m = 1;
			n = 3;
			result = 0;
			रुको_count = 0;
		पूर्ण
		वापस;
	पूर्ण

	अगर (!coex_dm->स्वतः_tdma_adjust) अणु
		coex_dm->स्वतः_tdma_adjust = true;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], first run TdmaDurationAdjust()!!\n");

		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 2);
		coex_dm->ps_tdma_du_adj_type = 2;

		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		result = 0;
		रुको_count = 0;
	पूर्ण अन्यथा अणु
		/* acquire the BT TRx retry count from BT_Info byte2 */
		retry_count = coex_sta->bt_retry_cnt;

		अगर ((coex_sta->low_priority_tx) > 1050 ||
		    (coex_sta->low_priority_rx) > 1250)
			retry_count++;

		result = 0;
		रुको_count++;
		/* no retry in the last 2-second duration */
		अगर (retry_count == 0) अणु
			up++;
			dn--;

			अगर (dn <= 0)
				dn = 0;

			अगर (up >= n) अणु
				/* अगर retry count during continuous n*2 seconds
				 * is 0, enlarge WiFi duration
				 */
				रुको_count = 0;
				n = 3;
				up = 0;
				dn = 0;
				result = 1;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], Increase wifi duration!!\n");
			पूर्ण
		पूर्ण अन्यथा अगर (retry_count <= 3) अणु
			/* <=3 retry in the last 2-second duration */
			up--;
			dn++;

			अगर (up <= 0)
				up = 0;

			अगर (dn == 2) अणु
				/* अगर continuous 2 retry count(every 2 seconds)
				 * >0 and < 3, reduce WiFi duration
				 */
				अगर (रुको_count <= 2)
					/* aव्योम loop between the two levels */
					m++;
				अन्यथा
					m = 1;

				अगर (m >= 20)
					/* maximum of m = 20 ' will recheck अगर
					 * need to adjust wअगरi duration in
					 * maximum समय पूर्णांकerval 120 seconds
					 */
					m = 20;

				n = 3 * m;
				up = 0;
				dn = 0;
				रुको_count = 0;
				result = -1;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], Decrease wifi duration for retryCounter<3!!\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			/* retry count > 3, once retry count > 3, to reduce
			 * WiFi duration
			 */
			अगर (रुको_count == 1)
				/* to aव्योम loop between the two levels */
				m++;
			अन्यथा
				m = 1;

			अगर (m >= 20)
				/* maximum of m = 20 ' will recheck अगर need to
				 * adjust wअगरi duration in maximum समय पूर्णांकerval
				 * 120 seconds
				 */
				m = 20;

			n = 3 * m;
			up = 0;
			dn = 0;
			रुको_count = 0;
			result = -1;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Decrease wifi duration for retryCounter>3!!\n");
		पूर्ण

		अगर (result == -1) अणु
			अगर (coex_dm->cur_ps_tdma == 1) अणु
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 2);
				coex_dm->ps_tdma_du_adj_type = 2;
			पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 9);
				coex_dm->ps_tdma_du_adj_type = 9;
			पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 11);
				coex_dm->ps_tdma_du_adj_type = 11;
			पूर्ण
		पूर्ण अन्यथा अगर (result == 1) अणु
			अगर (coex_dm->cur_ps_tdma == 11) अणु
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 9);
				coex_dm->ps_tdma_du_adj_type = 9;
			पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 2);
				coex_dm->ps_tdma_du_adj_type = 2;
			पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
				halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
							true, 1);
				coex_dm->ps_tdma_du_adj_type = 1;
			पूर्ण
		पूर्ण

		अगर (coex_dm->cur_ps_tdma != 1 && coex_dm->cur_ps_tdma != 2 &&
		    coex_dm->cur_ps_tdma != 9 && coex_dm->cur_ps_tdma != 11) अणु
			/* recover to previous adjust type */
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						coex_dm->ps_tdma_du_adj_type);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_ps_tdma_chk_pwr_save(काष्ठा btc_coexist *btcoexist,
					  bool new_ps_state)
अणु
	u8 lps_mode = 0x0;

	btcoexist->btc_get(btcoexist, BTC_GET_U1_LPS_MODE, &lps_mode);

	अगर (lps_mode) अणु
		/* alपढ़ोy under LPS state */
		अगर (new_ps_state) अणु
			/* keep state under LPS, करो nothing. */
		पूर्ण अन्यथा अणु
			/* will leave LPS state, turn off psTdma first */
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						false, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* NO PS state */
		अगर (new_ps_state) अणु
			/* will enter LPS state, turn off psTdma first */
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						false, 0);
		पूर्ण अन्यथा अणु
			/* keep state under NO PS state, करो nothing. */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_घातer_save_state(काष्ठा btc_coexist *btcoexist,
					     u8 ps_type, u8 lps_val,
					     u8 rpwm_val)
अणु
	bool low_pwr_disable = false;

	चयन (ps_type) अणु
	हाल BTC_PS_WIFI_NATIVE:
		/* recover to original 32k low घातer setting */
		low_pwr_disable = false;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_NORMAL_LPS, शून्य);
		coex_sta->क्रमce_lps_on = false;
		अवरोध;
	हाल BTC_PS_LPS_ON:
		halbtc8723b1ant_ps_tdma_chk_pwr_save(btcoexist, true);
		halbtc8723b1ant_lps_rpwm(btcoexist, NORMAL_EXEC, lps_val,
					 rpwm_val);
		/* when coex क्रमce to enter LPS, करो not enter 32k low घातer */
		low_pwr_disable = true;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		/* घातer save must executed beक्रमe psTdma */
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_ENTER_LPS, शून्य);
		coex_sta->क्रमce_lps_on = true;
		अवरोध;
	हाल BTC_PS_LPS_OFF:
		halbtc8723b1ant_ps_tdma_chk_pwr_save(btcoexist, false);
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_LEAVE_LPS, शून्य);
		coex_sta->क्रमce_lps_on = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_action_wअगरi_only(काष्ठा btc_coexist *btcoexist)
अणु
	halbtc8723b1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);
	halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
	halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
				     FORCE_EXEC, false, false);
पूर्ण

/* check अगर BT is disabled */
अटल व्योम halbtc8723b1ant_monitor_bt_enable_disable(काष्ठा btc_coexist
						      *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल u32 bt_disable_cnt;
	bool bt_active = true, bt_disabled = false;

	अगर (coex_sta->high_priority_tx == 0 &&
	    coex_sta->high_priority_rx == 0 && coex_sta->low_priority_tx == 0 &&
	    coex_sta->low_priority_rx == 0)
		bt_active = false;
	अगर (coex_sta->high_priority_tx == 0xffff &&
	    coex_sta->high_priority_rx == 0xffff &&
	    coex_sta->low_priority_tx == 0xffff &&
	    coex_sta->low_priority_rx == 0xffff)
		bt_active = false;
	अगर (bt_active) अणु
		bt_disable_cnt = 0;
		bt_disabled = false;
	पूर्ण अन्यथा अणु
		bt_disable_cnt++;
		अगर (bt_disable_cnt >= 2)
			bt_disabled = true;
	पूर्ण
	अगर (coex_sta->bt_disabled != bt_disabled) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT is from %s to %s!!\n",
			(coex_sta->bt_disabled ? "disabled" : "enabled"),
			(bt_disabled ? "disabled" : "enabled"));

		coex_sta->bt_disabled = bt_disabled;
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
				   &bt_disabled);
		अगर (bt_disabled) अणु
			halbtc8723b1ant_action_wअगरi_only(btcoexist);
			btcoexist->btc_set(btcoexist, BTC_SET_ACT_LEAVE_LPS,
					   शून्य);
			btcoexist->btc_set(btcoexist, BTC_SET_ACT_NORMAL_LPS,
					   शून्य);
		पूर्ण
	पूर्ण
पूर्ण

/*****************************************************
 *
 *	Non-Software Coex Mechanism start
 *
 *****************************************************/

अटल व्योम halbtc8723b1ant_action_bt_whck_test(काष्ठा btc_coexist *btcoexist)
अणु
	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0,
					 0x0);

	halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
	halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA, NORMAL_EXEC,
				     false, false);
	halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम halbtc8723b1ant_action_wअगरi_multiport(काष्ठा btc_coexist *btcoexist)
अणु
	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
	halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA, NORMAL_EXEC,
				     false, false);
	halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
पूर्ण

अटल व्योम halbtc8723b1ant_action_hs(काष्ठा btc_coexist *btcoexist)
अणु
	halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);
	halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
पूर्ण

अटल व्योम halbtc8723b1ant_action_bt_inquiry(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_connected = false, ap_enable = false;
	bool wअगरi_busy = false, bt_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	अगर (coex_sta->bt_abnormal_scan) अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 33);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	पूर्ण अन्यथा अगर (!wअगरi_connected && !coex_sta->wअगरi_is_high_pri_task) अणु
		halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अगर (bt_link_info->sco_exist || bt_link_info->hid_exist ||
		   bt_link_info->a2dp_exist) अणु
		/* SCO/HID/A2DP busy */
		halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
		अगर (coex_sta->c2h_bt_remote_name_req)
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						33);
		अन्यथा
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						32);

		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर (bt_link_info->pan_exist || wअगरi_busy) अणु
		halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
		अगर (coex_sta->c2h_bt_remote_name_req)
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						33);
		अन्यथा
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
						32);

		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	पूर्ण
पूर्ण

अटल व्योम btc8723b1ant_act_bt_sco_hid_only_busy(काष्ठा btc_coexist *btcoexist,
						  u8 wअगरi_status)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_connected = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);

	/* tdma and coex table */
	अगर (bt_link_info->sco_exist) अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);
	पूर्ण अन्यथा अणु
		/* HID */
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 6);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_action_wअगरi_connected_bt_acl_busy(
					काष्ठा btc_coexist *btcoexist,
					u8 wअगरi_status)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	अगर ((coex_sta->low_priority_rx >= 950) && (!coex_sta->under_ips))
		bt_link_info->slave_role = true;
	अन्यथा
		bt_link_info->slave_role = false;

	अगर (bt_link_info->hid_only) अणु /* HID */
		btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist, wअगरi_status);
		coex_dm->स्वतः_tdma_adjust = false;
		वापस;
	पूर्ण अन्यथा अगर (bt_link_info->a2dp_only) अणु /* A2DP */
		अगर (wअगरi_status == BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE) अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 32);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण अन्यथा अणु
			btc8723b1ant_tdma_dur_adj_क्रम_acl(btcoexist,
							  wअगरi_status);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
			coex_dm->स्वतः_tdma_adjust = true;
		पूर्ण
	पूर्ण अन्यथा अगर (((bt_link_info->a2dp_exist) && (bt_link_info->pan_exist)) ||
		   (bt_link_info->hid_exist && bt_link_info->a2dp_exist &&
		    bt_link_info->pan_exist)) अणु
		/* A2DP + PAN(OPP,FTP), HID + A2DP + PAN(OPP,FTP) */
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 13);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण अन्यथा अगर (bt_link_info->hid_exist && bt_link_info->a2dp_exist) अणु
		/* HID + A2DP */
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,	true, 14);
		coex_dm->स्वतः_tdma_adjust = false;

		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर (bt_link_info->pan_only ||
			(bt_link_info->hid_exist && bt_link_info->pan_exist)) अणु
		/* PAN(OPP,FTP), HID + PAN(OPP,FTP) */
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 3);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण अन्यथा अणु
		/* BT no-profile busy (0x9) */
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 33);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण
पूर्ण

अटल व्योम btc8723b1ant_action_wअगरi_not_conn(काष्ठा btc_coexist *btcoexist)
अणु
	/* घातer save state */
	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	/* tdma and coex table */
	halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
	halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA, NORMAL_EXEC,
				     false, false);
	halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम
btc8723b1ant_action_wअगरi_not_conn_scan(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	/* tdma and coex table */
	अगर (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) अणु
		अगर (bt_link_info->a2dp_exist) अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 32);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 22);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 20);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 1);
		पूर्ण
	पूर्ण अन्यथा अगर (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
		   coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY)अणु
		btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम
btc8723b1ant_act_wअगरi_not_conn_asso_auth(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	/* tdma and coex table */
	अगर ((bt_link_info->sco_exist) || (bt_link_info->hid_exist) ||
	    (bt_link_info->a2dp_exist)) अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 4);
	पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
		halbtc8723b1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 4);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम btc8723b1ant_action_wअगरi_conn_scan(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	/* tdma and coex table */
	अगर (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) अणु
		अगर (bt_link_info->a2dp_exist) अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 32);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist &&
			   bt_link_info->pan_exist) अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 22);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 20);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण अन्यथा अगर (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
		   coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) अणु
		btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_SCAN);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_action_wअगरi_connected_special_packet(
						काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);

	/* no special packet process क्रम both WiFi and BT very busy */
	अगर ((wअगरi_busy) &&
	    ((bt_link_info->pan_exist) || (coex_sta->num_of_profile >= 2)))
		वापस;

	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);

	/* tdma and coex table */
	अगर ((bt_link_info->sco_exist) || (bt_link_info->hid_exist)) अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 5);
	पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     NORMAL_EXEC, false, false);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_action_wअगरi_connected(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_busy = false;
	bool scan = false, link = false, roam = false;
	bool under_4way = false, ap_enable = false;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], CoexForWifiConnect()===>\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);
	अगर (under_4way) अणु
		halbtc8723b1ant_action_wअगरi_connected_special_packet(btcoexist);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexForWifiConnect(), return for wifi is under 4way<===\n");
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	अगर (scan || link || roam) अणु
		अगर (scan)
			btc8723b1ant_action_wअगरi_conn_scan(btcoexist);
		अन्यथा
			halbtc8723b1ant_action_wअगरi_connected_special_packet(
								     btcoexist);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexForWifiConnect(), return for wifi is under scan<===\n");
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	/* घातer save state */
	अगर (!ap_enable &&
	    coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY &&
	    !btcoexist->bt_link_info.hid_only) अणु
		अगर (btcoexist->bt_link_info.a2dp_only) अणु
			अगर (!wअगरi_busy) अणु
				halbtc8723b1ant_घातer_save_state(btcoexist,
							 BTC_PS_WIFI_NATIVE,
							 0x0, 0x0);
			पूर्ण अन्यथा अणु /* busy */
				अगर (coex_sta->scan_ap_num >=
				    BT_8723B_1ANT_WIFI_NOISY_THRESH)
					/* no क्रमce LPS, no PS-TDMA,
					 * use pure TDMA
					 */
					halbtc8723b1ant_घातer_save_state(
						btcoexist, BTC_PS_WIFI_NATIVE,
						0x0, 0x0);
				अन्यथा
					halbtc8723b1ant_घातer_save_state(
						btcoexist, BTC_PS_LPS_ON, 0x50,
						0x4);
			पूर्ण
		पूर्ण अन्यथा अगर ((!coex_sta->pan_exist) && (!coex_sta->a2dp_exist) &&
			   (!coex_sta->hid_exist))
			halbtc8723b1ant_घातer_save_state(
				btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		अन्यथा
			halbtc8723b1ant_घातer_save_state(btcoexist,
							 BTC_PS_LPS_ON,
							 0x50, 0x4);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
	पूर्ण
	/* tdma and coex table */
	अगर (!wअगरi_busy) अणु
		अगर (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) अणु
			halbtc8723b1ant_action_wअगरi_connected_bt_acl_busy(
				btcoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		पूर्ण अन्यथा अगर (coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
			   coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) अणु
			btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist,
				     BT_8723B_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						false, 8);
			halbtc8723b1ant_set_ant_path(btcoexist,
						     BTC_ANT_PATH_PTA,
						     NORMAL_EXEC, false, false);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 2);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY) अणु
			halbtc8723b1ant_action_wअगरi_connected_bt_acl_busy(
				btcoexist,
				BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY);
		पूर्ण अन्यथा अगर (coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
			   coex_dm->bt_status ==
				BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY) अणु
			btc8723b1ant_act_bt_sco_hid_only_busy(btcoexist,
				    BT_8723B_1ANT_WIFI_STATUS_CONNECTED_BUSY);
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC,
						true, 32);
			halbtc8723b1ant_set_ant_path(btcoexist,
						     BTC_ANT_PATH_PTA,
						     NORMAL_EXEC, false, false);
			halbtc8723b1ant_coex_table_with_type(btcoexist,
							     NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम halbtc8723b1ant_run_coexist_mechanism(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_connected = false, bt_hs_on = false, wअगरi_busy = false;
	bool increase_scan_dev_num = false;
	bool bt_ctrl_agg_buf_size = false;
	bool miracast_plus_bt = false;
	u8 agg_buf_size = 5;
	u8 iot_peer = BTC_IOT_PEER_UNKNOWN;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	u32 wअगरi_bw;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], RunCoexistMechanism()===>\n");

	अगर (btcoexist->manual_control) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for Manual CTRL <===\n");
		वापस;
	पूर्ण

	अगर (btcoexist->stop_coex_dm) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for Stop Coex DM <===\n");
		वापस;
	पूर्ण

	अगर (coex_sta->under_ips) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], wifi is under IPS !!!\n");
		वापस;
	पूर्ण

	अगर (coex_sta->bt_whck_test) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], wifi is under IPS !!!\n");
		halbtc8723b1ant_action_bt_whck_test(btcoexist);
		वापस;
	पूर्ण

	अगर (coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_BUSY ||
	    coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_SCO_BUSY ||
	    coex_dm->bt_status == BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY)
		increase_scan_dev_num = true;

	btcoexist->btc_set(btcoexist, BTC_SET_BL_INC_SCAN_DEV_NUM,
			   &increase_scan_dev_num);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;

	अगर (num_of_wअगरi_link >= 2 ||
	    wअगरi_link_status & WIFI_P2P_GO_CONNECTED) अणु
		अगर (bt_link_info->bt_link_exist) अणु
			halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 1, 1,
						   0, 1);
			miracast_plus_bt = true;
		पूर्ण अन्यथा अणु
			halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0,
						   0, 0);
			miracast_plus_bt = false;
		पूर्ण
		btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
				   &miracast_plus_bt);
		halbtc8723b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);

		अगर ((bt_link_info->a2dp_exist || wअगरi_busy) &&
		    (coex_sta->c2h_bt_inquiry_page))
			halbtc8723b1ant_action_bt_inquiry(btcoexist);
		अन्यथा
			halbtc8723b1ant_action_wअगरi_multiport(btcoexist);

		वापस;
	पूर्ण

	miracast_plus_bt = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
			   &miracast_plus_bt);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर (bt_link_info->bt_link_exist && wअगरi_connected) अणु
		halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 1, 1, 0, 1);

		btcoexist->btc_get(btcoexist, BTC_GET_U1_IOT_PEER, &iot_peer);

		अगर (iot_peer != BTC_IOT_PEER_CISCO &&
		    iot_peer != BTC_IOT_PEER_BROADCOM) अणु
			bool sco_exist = bt_link_info->sco_exist;

			halbtc8723b1ant_limited_rx(btcoexist,
						   NORMAL_EXEC, sco_exist,
						   false, 0x5);
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->sco_exist) अणु
				halbtc8723b1ant_limited_rx(btcoexist,
							   NORMAL_EXEC, true,
							   false, 0x5);
			पूर्ण अन्यथा अणु
				अगर (wअगरi_bw == BTC_WIFI_BW_HT40)
					halbtc8723b1ant_limited_rx(
						btcoexist, NORMAL_EXEC, false,
						true, 0x10);
				अन्यथा
					halbtc8723b1ant_limited_rx(
						btcoexist, NORMAL_EXEC, false,
						true, 0x8);
			पूर्ण
		पूर्ण

		halbtc8723b1ant_sw_mechanism(btcoexist, true);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);

		halbtc8723b1ant_limited_rx(btcoexist, NORMAL_EXEC, false, false,
					   0x5);

		halbtc8723b1ant_sw_mechanism(btcoexist, false);
	पूर्ण
	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		halbtc8723b1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		halbtc8723b1ant_action_hs(btcoexist);
		वापस;
	पूर्ण

	अगर (!wअगरi_connected) अणु
		bool scan = false, link = false, roam = false;

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], wifi is non connected-idle !!!\n");

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

		अगर (scan || link || roam) अणु
			अगर (scan)
				btc8723b1ant_action_wअगरi_not_conn_scan(
								     btcoexist);
			अन्यथा
				btc8723b1ant_act_wअगरi_not_conn_asso_auth(
								     btcoexist);
		पूर्ण अन्यथा अणु
			btc8723b1ant_action_wअगरi_not_conn(btcoexist);
		पूर्ण
	पूर्ण अन्यथा अणु /* wअगरi LPS/Busy */
		halbtc8723b1ant_action_wअगरi_connected(btcoexist);
	पूर्ण
पूर्ण

/* क्रमce coex mechanism to reset */
अटल व्योम halbtc8723b1ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	/* sw all off */
	halbtc8723b1ant_sw_mechanism(btcoexist, false);

	coex_sta->pop_event_cnt = 0;
पूर्ण

अटल व्योम halbtc8723b1ant_init_hw_config(काष्ठा btc_coexist *btcoexist,
					   bool backup, bool wअगरi_only)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u32 u32पंचांगp = 0;
	u8 u8पंचांगpa = 0, u8पंचांगpb = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], 1Ant Init HW Config!!\n");

	/* 0xf0[15:12] --> Chip Cut inक्रमmation */
	coex_sta->cut_version =
		(btcoexist->btc_पढ़ो_1byte(btcoexist, 0xf1) & 0xf0) >> 4;
	/* enable TBTT पूर्णांकerrupt */
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x550, 0x8, 0x1);

	/* 0x790[5:0] = 0x5 */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x790, 0x5);

	/* Enable counter statistics */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x778, 0x1);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x40, 0x20, 0x1);

	halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);

	/* Antenna config */
	अगर (wअगरi_only)
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_WIFI,
					     FORCE_EXEC, true, false);
	अन्यथा
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT,
					     FORCE_EXEC, true, false);

	/* PTA parameter */
	halbtc8723b1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);

	u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x948);
	u8पंचांगpa = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765);
	u8पंचांगpb = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x67);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"############# [BTCoex], 0x948=0x%x, 0x765=0x%x, 0x67=0x%x\n",
		u32पंचांगp, u8पंचांगpa, u8पंचांगpb);
पूर्ण

/**************************************************************
 * बाह्य function start with ex_btc8723b1ant_
 **************************************************************/
व्योम ex_btc8723b1ant_घातer_on_setting(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u8 u8पंचांगp = 0x0;
	u16 u16पंचांगp = 0x0;
	u32 value;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"xxxxxxxxxxxxxxxx Execute 8723b 1-Ant PowerOn Setting xxxxxxxxxxxxxxxx!!\n");

	btcoexist->stop_coex_dm = true;

	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x67, 0x20);

	/* enable BB, REG_SYS_FUNC_EN such that we can ग_लिखो 0x948 correctly. */
	u16पंचांगp = btcoexist->btc_पढ़ो_2byte(btcoexist, 0x2);
	btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x2, u16पंचांगp | BIT0 | BIT1);

	/* set GRAN_BT = 1 */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x18);
	/* set WLAN_ACT = 0 */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);

	/* S0 or S1 setting and Local रेजिस्टर setting(By the setting fw can get
	 * ant number, S0/S1, ... info)
	 *
	 * Local setting bit define
	 *	BIT0: "0" क्रम no antenna inverse; "1" क्रम antenna inverse
	 *	BIT1: "0" क्रम पूर्णांकernal चयन; "1" क्रम बाह्यal चयन
	 *	BIT2: "0" क्रम one antenna; "1" क्रम two antenna
	 * NOTE: here शेष all पूर्णांकernal चयन and 1-antenna ==> BIT1=0 and
	 * BIT2 = 0
	 */
	अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_USB) अणु
		/* fixed at S0 क्रम USB पूर्णांकerface */
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x948, 0x0);

		u8पंचांगp |= 0x1; /* antenna inverse */
		btcoexist->btc_ग_लिखो_local_reg_1byte(btcoexist, 0xfe08, u8पंचांगp);

		board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
	पूर्ण अन्यथा अणु
		/* क्रम PCIE and SDIO पूर्णांकerface, we check efuse 0xc3[6] */
		अगर (board_info->single_ant_path == 0) अणु
			/* set to S1 */
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x948, 0x280);
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;
			value = 1;
		पूर्ण अन्यथा अगर (board_info->single_ant_path == 1) अणु
			/* set to S0 */
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x948, 0x0);
			u8पंचांगp |= 0x1; /* antenna inverse */
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
			value = 0;
		पूर्ण

		btcoexist->btc_set(btcoexist, BTC_SET_ACT_ANTPOSREGRISTRY_CTRL,
				   &value);

		अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_PCI)
			btcoexist->btc_ग_लिखो_local_reg_1byte(btcoexist, 0x384,
							     u8पंचांगp);
		अन्यथा अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_SDIO)
			btcoexist->btc_ग_लिखो_local_reg_1byte(btcoexist, 0x60,
							     u8पंचांगp);
	पूर्ण
पूर्ण


व्योम ex_btc8723b1ant_init_hwconfig(काष्ठा btc_coexist *btcoexist,
				   bool wअगरi_only)
अणु
	halbtc8723b1ant_init_hw_config(btcoexist, true, wअगरi_only);
	btcoexist->stop_coex_dm = false;
पूर्ण

व्योम ex_btc8723b1ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Coex Mechanism Init!!\n");

	btcoexist->stop_coex_dm = false;

	halbtc8723b1ant_init_coex_dm(btcoexist);

	halbtc8723b1ant_query_bt_info(btcoexist);
पूर्ण

व्योम ex_btc8723b1ant_display_coex_info(काष्ठा btc_coexist *btcoexist,
				       काष्ठा seq_file *m)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u8 u8पंचांगp[4], i, bt_info_ext, pstdmaहाल = 0;
	u16 u16पंचांगp[4];
	u32 u32पंचांगp[4];
	bool roam = false, scan = false;
	bool link = false, wअगरi_under_5g = false;
	bool bt_hs_on = false, wअगरi_busy = false;
	s32 wअगरi_rssi = 0, bt_hs_rssi = 0;
	u32 wअगरi_bw, wअगरi_traffic_dir, fa_ofdm, fa_cck, wअगरi_link_status;
	u8 wअगरi_करोt11_chnl, wअगरi_hs_chnl;
	u32 fw_ver = 0, bt_patch_ver = 0;

	seq_माला_दो(m, "\n ============[BT Coexist info]============");

	अगर (btcoexist->manual_control) अणु
		seq_माला_दो(m, "\n ============[Under Manual Control]==========");
		seq_माला_दो(m, "\n ==========================================");
	पूर्ण
	अगर (btcoexist->stop_coex_dm) अणु
		seq_माला_दो(m, "\n ============[Coex is STOPPED]============");
		seq_माला_दो(m, "\n ==========================================");
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d",
		   "Ant PG Num/ Ant Mech/ Ant Pos:",
		   board_info->pg_ant_num, board_info->btdm_ant_num,
		   board_info->btdm_ant_pos);

	seq_म_लिखो(m, "\n %-35s = %s / %d",
		   "BT stack/ hci ext ver",
		   ((stack_info->profile_notअगरied) ? "Yes" : "No"),
		   stack_info->hci_version);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER, &bt_patch_ver);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	seq_म_लिखो(m, "\n %-35s = %d_%x/ 0x%x/ 0x%x(%d)",
		   "CoexVer/ FwVer/ PatchVer",
		   glcoex_ver_date_8723b_1ant, glcoex_ver_8723b_1ant,
		   fw_ver, bt_patch_ver, bt_patch_ver);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_DOT11_CHNL,
			   &wअगरi_करोt11_chnl);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_HS_CHNL, &wअगरi_hs_chnl);
	seq_म_लिखो(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsChnl(HsMode)",
		   wअगरi_करोt11_chnl, wअगरi_hs_chnl, bt_hs_on);

	seq_म_लिखो(m, "\n %-35s = %3ph ",
		   "H2C Wifi inform bt chnl Info",
		   coex_dm->wअगरi_chnl_info);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "Wifi rssi/ HS rssi", wअगरi_rssi, bt_hs_rssi);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d ",
		   "Wifi link/ roam/ scan", link, roam, scan);

	btcoexist->btc_get(btcoexist , BTC_GET_BL_WIFI_UNDER_5G,
			   &wअगरi_under_5g);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION,
			   &wअगरi_traffic_dir);

	seq_म_लिखो(m, "\n %-35s = %s / %s/ %s ",
		   "Wifi status", (wअगरi_under_5g ? "5G" : "2.4G"),
		   ((wअगरi_bw == BTC_WIFI_BW_LEGACY) ? "Legacy" :
		    ((wअगरi_bw == BTC_WIFI_BW_HT40) ? "HT40" : "HT20")),
		    ((!wअगरi_busy) ? "idle" :
		     ((wअगरi_traffic_dir == BTC_WIFI_TRAFFIC_TX) ?
		     "uplink" : "downlink")));

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d/ %d/ %d",
		   "sta/vwifi/hs/p2pGo/p2pGc",
		   ((wअगरi_link_status & WIFI_STA_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_AP_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_HS_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_P2P_GO_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_P2P_GC_CONNECTED) ? 1 : 0));

	seq_म_लिखो(m, "\n %-35s = [%s/ %d/ %d] ",
		   "BT [status/ rssi/ retryCnt]",
		   ((coex_sta->bt_disabled) ? ("disabled") :
		    ((coex_sta->c2h_bt_inquiry_page) ? ("inquiry/page scan") :
		     ((BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		       coex_dm->bt_status) ?
		      "non-connected idle" :
		      ((BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE ==
			coex_dm->bt_status) ?
		       "connected-idle" : "busy")))),
		       coex_sta->bt_rssi, coex_sta->bt_retry_cnt);

	seq_म_लिखो(m, "\n %-35s = %d / %d / %d / %d",
		   "SCO/HID/PAN/A2DP", bt_link_info->sco_exist,
		   bt_link_info->hid_exist, bt_link_info->pan_exist,
		   bt_link_info->a2dp_exist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_BT_LINK_INFO, m);

	bt_info_ext = coex_sta->bt_info_ext;
	seq_म_लिखो(m, "\n %-35s = %s",
		   "BT Info A2DP rate",
		   (bt_info_ext & BIT0) ? "Basic rate" : "EDR rate");

	क्रम (i = 0; i < BT_INFO_SRC_8723B_1ANT_MAX; i++) अणु
		अगर (coex_sta->bt_info_c2h_cnt[i]) अणु
			seq_म_लिखो(m, "\n %-35s = %7ph(%d)",
				   glbt_info_src_8723b_1ant[i],
				   coex_sta->bt_info_c2h[i],
				   coex_sta->bt_info_c2h_cnt[i]);
		पूर्ण
	पूर्ण
	seq_म_लिखो(m, "\n %-35s = %s/%s, (0x%x/0x%x)",
		   "PS state, IPS/LPS, (lps/rpwm)",
		   ((coex_sta->under_ips ? "IPS ON" : "IPS OFF")),
		   ((coex_sta->under_lps ? "LPS ON" : "LPS OFF")),
		   btcoexist->bt_info.lps_val,
		   btcoexist->bt_info.rpwm_val);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD, m);

	अगर (!btcoexist->manual_control) अणु
		/* Sw mechanism	*/
		seq_म_लिखो(m, "\n %-35s",
			   "============[Sw mechanism]============");

		seq_म_लिखो(m, "\n %-35s = %d/",
			   "SM[LowPenaltyRA]", coex_dm->cur_low_penalty_ra);

		seq_म_लिखो(m, "\n %-35s = %s/ %s/ %d ",
			   "DelBA/ BtCtrlAgg/ AggSize",
			   (btcoexist->bt_info.reject_agg_pkt ? "Yes" : "No"),
			   (btcoexist->bt_info.bt_ctrl_buf_size ? "Yes" : "No"),
			   btcoexist->bt_info.agg_buf_size);

		seq_म_लिखो(m, "\n %-35s = 0x%x ",
			   "Rate Mask", btcoexist->bt_info.ra_mask);

		/* Fw mechanism	*/
		seq_म_लिखो(m, "\n %-35s",
			   "============[Fw mechanism]============");

		pstdmaहाल = coex_dm->cur_ps_tdma;
		seq_म_लिखो(m, "\n %-35s = %5ph case-%d (auto:%d)",
			   "PS TDMA", coex_dm->ps_tdma_para,
			   pstdmaहाल, coex_dm->स्वतः_tdma_adjust);

		seq_म_लिखो(m, "\n %-35s = %d ",
			   "IgnWlanAct", coex_dm->cur_ignore_wlan_act);

		seq_म_लिखो(m, "\n %-35s = 0x%x ",
			   "Latest error condition(should be 0)",
			   coex_dm->error_condition);
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %d",
		   "Coex Table Type", coex_sta->coex_table_type);

	/* Hw setting */
	seq_म_लिखो(m, "\n %-35s",
		   "============[Hw setting]============");

	seq_म_लिखो(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "backup ARFR1/ARFR2/RL/AMaxTime", coex_dm->backup_arfr_cnt1,
		   coex_dm->backup_arfr_cnt2, coex_dm->backup_retry_limit,
		   coex_dm->backup_ampdu_max_समय);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x430);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x434);
	u16पंचांगp[0] = btcoexist->btc_पढ़ो_2byte(btcoexist, 0x42a);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x456);
	seq_म_लिखो(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "0x430/0x434/0x42a/0x456",
		   u32पंचांगp[0], u32पंचांगp[1], u16पंचांगp[0], u8पंचांगp[0]);

	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x778);
	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6cc);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x880);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x778/0x6cc/0x880[29:25]", u8पंचांगp[0], u32पंचांगp[0],
		   (u32पंचांगp[1] & 0x3e000000) >> 25);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x948);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x67);
	u8पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x948/ 0x67[5] / 0x765",
		   u32पंचांगp[0], ((u8पंचांगp[0] & 0x20) >> 5), u8पंचांगp[1]);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x92c);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x930);
	u32पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x944);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x92c[1:0]/ 0x930[7:0]/0x944[1:0]",
		   u32पंचांगp[0] & 0x3, u32पंचांगp[1] & 0xff, u32पंचांगp[2] & 0x3);

	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x39);
	u8पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x40);
	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
	u8पंचांगp[2] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x64);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
		   "0x38[11]/0x40/0x4c[24:23]/0x64[0]",
		   ((u8पंचांगp[0] & 0x8) >> 3), u8पंचांगp[1],
		    ((u32पंचांगp[0] & 0x01800000) >> 23), u8पंचांगp[2] & 0x1);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x550);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x522);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x550(bcn ctrl)/0x522", u32पंचांगp[0], u8पंचांगp[0]);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xc50);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x49c);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0xc50(dig)/0x49c(null-drop)", u32पंचांगp[0] & 0xff, u8पंचांगp[0]);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xda0);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xda4);
	u32पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xda8);
	u32पंचांगp[3] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xcf0);

	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xa5b);
	u8पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xa5c);

	fa_ofdm = ((u32पंचांगp[0] & 0xffff0000) >> 16) +
		  ((u32पंचांगp[1] & 0xffff0000) >> 16) +
		   (u32पंचांगp[1] & 0xffff) +
		   (u32पंचांगp[2] & 0xffff) +
		  ((u32पंचांगp[3] & 0xffff0000) >> 16) +
		   (u32पंचांगp[3] & 0xffff);
	fa_cck = (u8पंचांगp[0] << 8) + u8पंचांगp[1];

	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "OFDM-CCA/OFDM-FA/CCK-FA",
		 u32पंचांगp[0] & 0xffff, fa_ofdm, fa_cck);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c0);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c4);
	u32पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c8);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x6c0/0x6c4/0x6c8(coexTable)",
		   u32पंचांगp[0], u32पंचांगp[1], u32पंचांगp[2]);

	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x770(high-pri rx/tx)", coex_sta->high_priority_rx,
		   coex_sta->high_priority_tx);
	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x774(low-pri rx/tx)", coex_sta->low_priority_rx,
		   coex_sta->low_priority_tx);
	अगर (btcoexist->स्वतः_report_1ant)
		halbtc8723b1ant_monitor_bt_ctr(btcoexist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS, m);
पूर्ण

व्योम ex_btc8723b1ant_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm)
		वापस;

	अगर (BTC_IPS_ENTER == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;

		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT,
					     FORCE_EXEC, false, true);
		/* set PTA control */
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
		halbtc8723b1ant_coex_table_with_type(btcoexist,
						     NORMAL_EXEC, 0);
	पूर्ण अन्यथा अगर (BTC_IPS_LEAVE == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;

		halbtc8723b1ant_init_hw_config(btcoexist, false, false);
		halbtc8723b1ant_init_coex_dm(btcoexist);
		halbtc8723b1ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8723b1ant_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm)
		वापस;

	अगर (BTC_LPS_ENABLE == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], LPS ENABLE notify\n");
		coex_sta->under_lps = true;
	पूर्ण अन्यथा अगर (BTC_LPS_DISABLE == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], LPS DISABLE notify\n");
		coex_sta->under_lps = false;
	पूर्ण
पूर्ण

व्योम ex_btc8723b1ant_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_connected = false, bt_hs_on = false;
	u8 u8पंचांगpa, u8पंचांगpb;
	u32 u32पंचांगp;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	bool bt_ctrl_agg_buf_size = false;
	u8 agg_buf_size = 5;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm)
		वापस;

	अगर (type == BTC_SCAN_START) अणु
		coex_sta->wअगरi_is_high_pri_task = true;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN START notify\n");
		/* Force antenna setup क्रम no scan result issue */
		halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     FORCE_EXEC, false, false);
		u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x948);
		u8पंचांगpa = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765);
		u8पंचांगpb = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x67);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], 0x948=0x%x, 0x765=0x%x, 0x67=0x%x\n",
			u32पंचांगp, u8पंचांगpa, u8पंचांगpb);
	पूर्ण अन्यथा अणु
		coex_sta->wअगरi_is_high_pri_task = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN FINISH notify\n");

		btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
				   &coex_sta->scan_ap_num);
	पूर्ण

	अगर (coex_sta->bt_disabled)
		वापस;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);

	halbtc8723b1ant_query_bt_info(btcoexist);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;
	अगर (num_of_wअगरi_link >= 2) अणु
		halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);
		halbtc8723b1ant_action_wअगरi_multiport(btcoexist);
		वापस;
	पूर्ण

	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		halbtc8723b1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		halbtc8723b1ant_action_hs(btcoexist);
		वापस;
	पूर्ण

	अगर (BTC_SCAN_START == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN START notify\n");
		अगर (!wअगरi_connected)
			/* non-connected scan */
			btc8723b1ant_action_wअगरi_not_conn_scan(btcoexist);
		अन्यथा
			/* wअगरi is connected */
			btc8723b1ant_action_wअगरi_conn_scan(btcoexist);
	पूर्ण अन्यथा अगर (BTC_SCAN_FINISH == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN FINISH notify\n");
		अगर (!wअगरi_connected)
			/* non-connected scan */
			btc8723b1ant_action_wअगरi_not_conn(btcoexist);
		अन्यथा
			halbtc8723b1ant_action_wअगरi_connected(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8723b1ant_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_connected = false, bt_hs_on = false;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	bool bt_ctrl_agg_buf_size = false, under_4way = false;
	u8 agg_buf_size = 5;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		वापस;

	अगर (type == BTC_ASSOCIATE_START) अणु
		coex_sta->wअगरi_is_high_pri_task = true;

		/* Force antenna setup क्रम no scan result issue */
		halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     FORCE_EXEC, false, false);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT START notify\n");
		coex_dm->arp_cnt = 0;
	पूर्ण अन्यथा अणु
		coex_sta->wअगरi_is_high_pri_task = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT FINISH notify\n");
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status>>16;
	अगर (num_of_wअगरi_link >= 2) अणु
		halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);
		halbtc8723b1ant_action_wअगरi_multiport(btcoexist);
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		halbtc8723b1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		halbtc8723b1ant_action_hs(btcoexist);
		वापस;
	पूर्ण

	अगर (BTC_ASSOCIATE_START == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT START notify\n");
		btc8723b1ant_act_wअगरi_not_conn_asso_auth(btcoexist);
	पूर्ण अन्यथा अगर (BTC_ASSOCIATE_FINISH == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT FINISH notify\n");

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
				   &wअगरi_connected);
		अगर (!wअगरi_connected)
			/* non-connected scan */
			btc8723b1ant_action_wअगरi_not_conn(btcoexist);
		अन्यथा
			halbtc8723b1ant_action_wअगरi_connected(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8723b1ant_media_status_notअगरy(काष्ठा btc_coexist *btcoexist,
					 u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[3] = अणु0पूर्ण;
	u32 wअगरi_bw;
	u8 wअगरi_central_chnl;
	bool wअगरi_under_b_mode = false;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		वापस;

	अगर (type == BTC_MEDIA_CONNECT) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA connect notify\n");
		/* Force antenna setup क्रम no scan result issue */
		halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					     FORCE_EXEC, false, false);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_B_MODE,
				   &wअगरi_under_b_mode);

		/* Set CCK Tx/Rx high Pri except 11b mode */
		अगर (wअगरi_under_b_mode) अणु
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cf,
						   0x00); /* CCK Rx */
		पूर्ण अन्यथा अणु
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cd,
						   0x00); /* CCK Tx */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cf,
						   0x10); /* CCK Rx */
		पूर्ण

		coex_dm->backup_arfr_cnt1 =
			btcoexist->btc_पढ़ो_4byte(btcoexist, 0x430);
		coex_dm->backup_arfr_cnt2 =
			btcoexist->btc_पढ़ो_4byte(btcoexist, 0x434);
		coex_dm->backup_retry_limit =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0x42a);
		coex_dm->backup_ampdu_max_समय =
			btcoexist->btc_पढ़ो_1byte(btcoexist, 0x456);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA disconnect notify\n");
		coex_dm->arp_cnt = 0;

		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cd, 0x0); /* CCK Tx */
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cf, 0x0); /* CCK Rx */

		coex_sta->cck_ever_lock = false;
	पूर्ण

	/* only 2.4G we need to inक्रमm bt the chnl mask */
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL,
			   &wअगरi_central_chnl);

	अगर (type == BTC_MEDIA_CONNECT && wअगरi_central_chnl <= 14) अणु
		h2c_parameter[0] = 0x0;
		h2c_parameter[1] = wअगरi_central_chnl;
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
		अगर (BTC_WIFI_BW_HT40 == wअगरi_bw)
			h2c_parameter[2] = 0x30;
		अन्यथा
			h2c_parameter[2] = 0x20;
	पूर्ण

	coex_dm->wअगरi_chnl_info[0] = h2c_parameter[0];
	coex_dm->wअगरi_chnl_info[1] = h2c_parameter[1];
	coex_dm->wअगरi_chnl_info[2] = h2c_parameter[2];

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], FW write 0x66 = 0x%x\n",
		h2c_parameter[0] << 16 | h2c_parameter[1] << 8 |
		h2c_parameter[2]);

	btcoexist->btc_fill_h2c(btcoexist, 0x66, 3, h2c_parameter);
पूर्ण

व्योम ex_btc8723b1ant_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist,
					   u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool bt_hs_on = false;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	bool bt_ctrl_agg_buf_size = false, under_4way = false;
	u8 agg_buf_size = 5;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		वापस;

	अगर (type == BTC_PACKET_DHCP || type == BTC_PACKET_EAPOL ||
	    type == BTC_PACKET_ARP) अणु
		अगर (type == BTC_PACKET_ARP) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], special Packet ARP notify\n");

			coex_dm->arp_cnt++;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ARP Packet Count = %d\n",
				 coex_dm->arp_cnt);

			अगर ((coex_dm->arp_cnt >= 10) && (!under_4way))
				/* अगर APR PKT > 10 after connect, करो not go to
				 * ActionWअगरiConnectedSpecअगरicPacket(btcoexist)
				 */
				coex_sta->wअगरi_is_high_pri_task = false;
			अन्यथा
				coex_sta->wअगरi_is_high_pri_task = true;
		पूर्ण अन्यथा अणु
			coex_sta->wअगरi_is_high_pri_task = true;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], special Packet DHCP or EAPOL notify\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		coex_sta->wअगरi_is_high_pri_task = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], special Packet [Type = %d] notify\n",
			 type);
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
		&wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;
	अगर (num_of_wअगरi_link >= 2) अणु
		halbtc8723b1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		halbtc8723b1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					   bt_ctrl_agg_buf_size, agg_buf_size);
		halbtc8723b1ant_action_wअगरi_multiport(btcoexist);
		वापस;
	पूर्ण

	coex_sta->special_pkt_period_cnt = 0;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		halbtc8723b1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		halbtc8723b1ant_action_hs(btcoexist);
		वापस;
	पूर्ण

	अगर (BTC_PACKET_DHCP == type ||
	    BTC_PACKET_EAPOL == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], special Packet(%d) notify\n", type);
		halbtc8723b1ant_action_wअगरi_connected_special_packet(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8723b1ant_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist,
				    u8 *पंचांगp_buf, u8 length)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 bt_info = 0;
	u8 i, rsp_source = 0;
	bool wअगरi_connected = false;
	bool bt_busy = false;

	coex_sta->c2h_bt_info_req_sent = false;

	rsp_source = पंचांगp_buf[0] & 0xf;
	अगर (rsp_source >= BT_INFO_SRC_8723B_1ANT_MAX)
		rsp_source = BT_INFO_SRC_8723B_1ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Bt info[%d], length=%d, hex data = [",
		 rsp_source, length);
	क्रम (i = 0; i < length; i++) अणु
		coex_sta->bt_info_c2h[rsp_source][i] = पंचांगp_buf[i];
		अगर (i == 1)
			bt_info = पंचांगp_buf[i];
		अगर (i == length - 1)
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x]\n", पंचांगp_buf[i]);
		अन्यथा
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x, ", पंचांगp_buf[i]);
	पूर्ण

	/* अगर 0xff, it means BT is under WHCK test */
	अगर (bt_info == 0xff)
		coex_sta->bt_whck_test = true;
	अन्यथा
		coex_sta->bt_whck_test = false;

	अगर (rsp_source != BT_INFO_SRC_8723B_1ANT_WIFI_FW) अणु
		coex_sta->bt_retry_cnt = /* [3:0] */
			coex_sta->bt_info_c2h[rsp_source][2] & 0xf;

		अगर (coex_sta->bt_retry_cnt >= 1)
			coex_sta->pop_event_cnt++;

		अगर (coex_sta->bt_info_c2h[rsp_source][2] & 0x20)
			coex_sta->c2h_bt_remote_name_req = true;
		अन्यथा
			coex_sta->c2h_bt_remote_name_req = false;

		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 - 90;

		coex_sta->bt_info_ext =
			coex_sta->bt_info_c2h[rsp_source][4];

		अगर (coex_sta->bt_info_c2h[rsp_source][1] == 0x49) अणु
			coex_sta->a2dp_bit_pool =
				coex_sta->bt_info_c2h[rsp_source][6];
		पूर्ण अन्यथा अणु
			coex_sta->a2dp_bit_pool = 0;
		पूर्ण

		coex_sta->bt_tx_rx_mask =
			(coex_sta->bt_info_c2h[rsp_source][2] & 0x40);
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TX_RX_MASK,
				   &coex_sta->bt_tx_rx_mask);

		अगर (!coex_sta->bt_tx_rx_mask) अणु
			/* BT पूर्णांकo is responded by BT FW and BT RF REG
			 * 0x3C != 0x15 => Need to चयन BT TRx Mask
			 */
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Switch BT TRx Mask since BT RF REG 0x3C != 0x15\n");
			btcoexist->btc_set_bt_reg(btcoexist, BTC_BT_REG_RF,
						  0x3c, 0x15);

			/* BT TRx Mask lock 0x2c[0], 0x30[0] = 0 */
			btcoexist->btc_set_bt_reg(btcoexist, BTC_BT_REG_RF,
						  0x2c, 0x7c44);
			btcoexist->btc_set_bt_reg(btcoexist, BTC_BT_REG_RF,
						  0x30, 0x7c44);
		पूर्ण

		/* Here we need to resend some wअगरi info to BT
		 * because bt is reset and loss of the info.
		 */
		अगर (coex_sta->bt_info_ext & BIT1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], BT ext info bit1 check, send wifi BW&Chnl to BT!!\n");
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
					   &wअगरi_connected);
			अगर (wअगरi_connected)
				ex_btc8723b1ant_media_status_notअगरy(btcoexist,
						BTC_MEDIA_CONNECT);
			अन्यथा
				ex_btc8723b1ant_media_status_notअगरy(btcoexist,
						BTC_MEDIA_DISCONNECT);
		पूर्ण

		अगर (coex_sta->bt_info_ext & BIT3) अणु
			अगर (!btcoexist->manual_control &&
			    !btcoexist->stop_coex_dm) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit3 check, set BT NOT ignore Wlan active!!\n");
				halbtc8723b1ant_ignore_wlan_act(btcoexist,
								FORCE_EXEC,
								false);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* BT alपढ़ोy NOT ignore Wlan active, करो nothing here.*/
		पूर्ण
		अगर (!btcoexist->स्वतः_report_1ant) अणु
			अगर (coex_sta->bt_info_ext & BIT4) अणु
				/* BT स्वतः report alपढ़ोy enabled, करो nothing */
			पूर्ण अन्यथा अणु
				halbtc8723b1ant_bt_स्वतः_report(btcoexist,
							       FORCE_EXEC,
							       true);
			पूर्ण
		पूर्ण
	पूर्ण

	/* check BIT2 first ==> check अगर bt is under inquiry or page scan */
	अगर (bt_info & BT_INFO_8723B_1ANT_B_INQ_PAGE)
		coex_sta->c2h_bt_inquiry_page = true;
	अन्यथा
		coex_sta->c2h_bt_inquiry_page = false;

	coex_sta->num_of_profile = 0;

	/* set link exist status */
	अगर (!(bt_info & BT_INFO_8723B_1ANT_B_CONNECTION)) अणु
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;

		coex_sta->bt_hi_pri_link_exist = false;
	पूर्ण अन्यथा अणु
		/* connection exists */
		coex_sta->bt_link_exist = true;
		अगर (bt_info & BT_INFO_8723B_1ANT_B_FTP) अणु
			coex_sta->pan_exist = true;
			coex_sta->num_of_profile++;
		पूर्ण अन्यथा अणु
			coex_sta->pan_exist = false;
		पूर्ण
		अगर (bt_info & BT_INFO_8723B_1ANT_B_A2DP) अणु
			coex_sta->a2dp_exist = true;
			coex_sta->num_of_profile++;
		पूर्ण अन्यथा अणु
			coex_sta->a2dp_exist = false;
		पूर्ण
		अगर (bt_info & BT_INFO_8723B_1ANT_B_HID) अणु
			coex_sta->hid_exist = true;
			coex_sta->num_of_profile++;
		पूर्ण अन्यथा अणु
			coex_sta->hid_exist = false;
		पूर्ण
		अगर (bt_info & BT_INFO_8723B_1ANT_B_SCO_ESCO) अणु
			coex_sta->sco_exist = true;
			coex_sta->num_of_profile++;
		पूर्ण अन्यथा अणु
			coex_sta->sco_exist = false;
		पूर्ण

		अगर ((!coex_sta->hid_exist) &&
		    (!coex_sta->c2h_bt_inquiry_page) &&
		    (!coex_sta->sco_exist)) अणु
			अगर (coex_sta->high_priority_tx +
				    coex_sta->high_priority_rx >=
			    160) अणु
				coex_sta->hid_exist = true;
				coex_sta->wrong_profile_notअगरication++;
				coex_sta->num_of_profile++;
				bt_info = bt_info | 0x28;
			पूर्ण
		पूर्ण

		/* Add Hi-Pri Tx/Rx counter to aव्योम false detection */
		अगर (((coex_sta->hid_exist) || (coex_sta->sco_exist)) &&
		    (coex_sta->high_priority_tx + coex_sta->high_priority_rx >=
		     160) &&
		    (!coex_sta->c2h_bt_inquiry_page))
			coex_sta->bt_hi_pri_link_exist = true;

		अगर ((bt_info & BT_INFO_8723B_1ANT_B_ACL_BUSY) &&
		    (coex_sta->num_of_profile == 0)) अणु
			अगर (coex_sta->low_priority_tx +
				    coex_sta->low_priority_rx >=
			    160) अणु
				coex_sta->pan_exist = true;
				coex_sta->num_of_profile++;
				coex_sta->wrong_profile_notअगरication++;
				bt_info = bt_info | 0x88;
			पूर्ण
		पूर्ण
	पूर्ण

	halbtc8723b1ant_update_bt_link_info(btcoexist);

	/* mask profile bit क्रम connect-ilde identअगरication
	 * ( क्रम CSR हाल: A2DP idle --> 0x41)
	 */
	bt_info = bt_info & 0x1f;

	अगर (!(bt_info & BT_INFO_8723B_1ANT_B_CONNECTION)) अणु
		coex_dm->bt_status = BT_8723B_1ANT_BT_STATUS_NON_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Connected idle!\n");
	/* connection exists but no busy */
	पूर्ण अन्यथा अगर (bt_info == BT_INFO_8723B_1ANT_B_CONNECTION) अणु
		coex_dm->bt_status = BT_8723B_1ANT_BT_STATUS_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n");
	पूर्ण अन्यथा अगर ((bt_info & BT_INFO_8723B_1ANT_B_SCO_ESCO) ||
		(bt_info & BT_INFO_8723B_1ANT_B_SCO_BUSY)) अणु
		coex_dm->bt_status = BT_8723B_1ANT_BT_STATUS_SCO_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT SCO busy!!!\n");
	पूर्ण अन्यथा अगर (bt_info & BT_INFO_8723B_1ANT_B_ACL_BUSY) अणु
		अगर (BT_8723B_1ANT_BT_STATUS_ACL_BUSY != coex_dm->bt_status)
			coex_dm->स्वतः_tdma_adjust = false;

		coex_dm->bt_status = BT_8723B_1ANT_BT_STATUS_ACL_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT ACL busy!!!\n");
	पूर्ण अन्यथा अणु
		coex_dm->bt_status = BT_8723B_1ANT_BT_STATUS_MAX;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Defined state!!\n");
	पूर्ण

	अगर ((BT_8723B_1ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) ||
	    (BT_8723B_1ANT_BT_STATUS_SCO_BUSY == coex_dm->bt_status) ||
	    (BT_8723B_1ANT_BT_STATUS_ACL_SCO_BUSY == coex_dm->bt_status))
		bt_busy = true;
	अन्यथा
		bt_busy = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	halbtc8723b1ant_run_coexist_mechanism(btcoexist);
पूर्ण

व्योम ex_btc8723b1ant_rf_status_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u32 u32पंचांगp;
	u8 u8पंचांगpa, u8पंचांगpb, u8पंचांगpc;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], RF Status notify\n");

	अगर (type == BTC_RF_ON) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RF is turned ON!!\n");
		btcoexist->stop_coex_dm = false;
	पूर्ण अन्यथा अगर (type == BTC_RF_OFF) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RF is turned OFF!!\n");

		halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
		halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 0);
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT,
					     FORCE_EXEC, false, true);

		halbtc8723b1ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
		btcoexist->stop_coex_dm = true;

		u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x948);
		u8पंचांगpa = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765);
		u8पंचांगpb = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x67);
		u8पंचांगpc = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x76e);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"############# [BTCoex], 0x948=0x%x, 0x765=0x%x, 0x67=0x%x, 0x76e=0x%x\n",
			u32पंचांगp, u8पंचांगpa, u8पंचांगpb, u8पंचांगpc);
	पूर्ण
पूर्ण

व्योम ex_btc8723b1ant_halt_notअगरy(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Halt notify\n");

	btcoexist->stop_coex_dm = true;

	halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT, FORCE_EXEC,
				     false, true);

	halbtc8723b1ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);

	halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					 0x0, 0x0);
	halbtc8723b1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 0);

	ex_btc8723b1ant_media_status_notअगरy(btcoexist, BTC_MEDIA_DISCONNECT);

	btcoexist->stop_coex_dm = true;
पूर्ण

व्योम ex_btc8723b1ant_pnp_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pnp_state)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Pnp notify\n");

	अगर (BTC_WIFI_PNP_SLEEP == pnp_state) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to SLEEP\n");
		halbtc8723b1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT,
					     FORCE_EXEC, false, true);
		halbtc8723b1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
						 0x0, 0x0);
		halbtc8723b1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
		halbtc8723b1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

		/* Driver करो not leave IPS/LPS when driver is going to sleep, so
		 * BTCoexistence think wअगरi is still under IPS/LPS
		 *
		 * BT should clear UnderIPS/UnderLPS state to aव्योम mismatch
		 * state after wakeup.
		 */
		coex_sta->under_ips = false;
		coex_sta->under_lps = false;
		btcoexist->stop_coex_dm = true;
	पूर्ण अन्यथा अगर (BTC_WIFI_PNP_WAKE_UP == pnp_state) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to WAKE UP\n");
		btcoexist->stop_coex_dm = false;
		halbtc8723b1ant_init_hw_config(btcoexist, false, false);
		halbtc8723b1ant_init_coex_dm(btcoexist);
		halbtc8723b1ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8723b1ant_coex_dm_reset(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], *****************Coex DM Reset****************\n");

	halbtc8723b1ant_init_hw_config(btcoexist, false, false);
	halbtc8723b1ant_init_coex_dm(btcoexist);
पूर्ण

व्योम ex_btc8723b1ant_periodical(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], ==========================Periodical===========================\n");

	अगर (!btcoexist->स्वतः_report_1ant) अणु
		halbtc8723b1ant_query_bt_info(btcoexist);
		halbtc8723b1ant_monitor_bt_enable_disable(btcoexist);
	पूर्ण अन्यथा अणु
		halbtc8723b1ant_monitor_bt_ctr(btcoexist);
		halbtc8723b1ant_monitor_wअगरi_ctr(btcoexist);

		अगर ((coex_sta->high_priority_tx + coex_sta->high_priority_rx < 50) &&
		    bt_link_info->hid_exist)
			bt_link_info->hid_exist = false;

		अगर (btc8723b1ant_is_wअगरi_status_changed(btcoexist) ||
		    coex_dm->स्वतः_tdma_adjust) अणु
			halbtc8723b1ant_run_coexist_mechanism(btcoexist);
		पूर्ण
		coex_sta->special_pkt_period_cnt++;
	पूर्ण
पूर्ण
