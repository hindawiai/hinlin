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
 **************************************************************/
/**************************************************************
 * include files
 **************************************************************/
#समावेश "halbt_precomp.h"
/**************************************************************
 * Global variables, these are अटल variables
 **************************************************************/
अटल काष्ठा coex_dm_8723b_2ant glcoex_dm_8723b_2ant;
अटल काष्ठा coex_dm_8723b_2ant *coex_dm = &glcoex_dm_8723b_2ant;
अटल काष्ठा coex_sta_8723b_2ant glcoex_sta_8723b_2ant;
अटल काष्ठा coex_sta_8723b_2ant *coex_sta = &glcoex_sta_8723b_2ant;

अटल स्थिर अक्षर *स्थिर glbt_info_src_8723b_2ant[] = अणु
	"BT Info[wifi fw]",
	"BT Info[bt rsp]",
	"BT Info[bt auto report]",
पूर्ण;

अटल u32 glcoex_ver_date_8723b_2ant = 20131113;
अटल u32 glcoex_ver_8723b_2ant = 0x3f;

/**************************************************************
 * local function proto type अगर needed
 **************************************************************/
/**************************************************************
 * local function start with btc8723b2ant_
 **************************************************************/
अटल u8 btc8723b2ant_bt_rssi_state(काष्ठा btc_coexist *btcoexist,
				     u8 level_num, u8 rssi_thresh,
				     u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	s32 bt_rssi = 0;
	u8 bt_rssi_state = coex_sta->pre_bt_rssi_state;

	bt_rssi = coex_sta->bt_rssi;

	अगर (level_num == 2) अणु
		अगर ((coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (bt_rssi >= rssi_thresh +
				       BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) अणु
				bt_rssi_state = BTC_RSSI_STATE_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state switch to High\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_rssi < rssi_thresh) अणु
				bt_rssi_state = BTC_RSSI_STATE_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state switch to Low\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (level_num == 3) अणु
		अगर (rssi_thresh > rssi_thresh1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], BT Rssi thresh error!!\n");
			वापस coex_sta->pre_bt_rssi_state;
		पूर्ण

		अगर ((coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (bt_rssi >= rssi_thresh +
				       BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) अणु
				bt_rssi_state = BTC_RSSI_STATE_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state switch to Medium\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अगर ((coex_sta->pre_bt_rssi_state ==
						BTC_RSSI_STATE_MEDIUM) ||
			   (coex_sta->pre_bt_rssi_state ==
						BTC_RSSI_STATE_STAY_MEDIUM)) अणु
			अगर (bt_rssi >= rssi_thresh1 +
				       BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) अणु
				bt_rssi_state = BTC_RSSI_STATE_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state switch to High\n");
			पूर्ण अन्यथा अगर (bt_rssi < rssi_thresh) अणु
				bt_rssi_state = BTC_RSSI_STATE_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state switch to Low\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state stay at Medium\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_rssi < rssi_thresh1) अणु
				bt_rssi_state = BTC_RSSI_STATE_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state switch to Medium\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Rssi state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण

	coex_sta->pre_bt_rssi_state = bt_rssi_state;

	वापस bt_rssi_state;
पूर्ण

अटल u8 btc8723b2ant_wअगरi_rssi_state(काष्ठा btc_coexist *btcoexist,
				       u8 index, u8 level_num,
				       u8 rssi_thresh, u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	s32 wअगरi_rssi = 0;
	u8 wअगरi_rssi_state = coex_sta->pre_wअगरi_rssi_state[index];

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);

	अगर (level_num == 2) अणु
		अगर ((coex_sta->pre_wअगरi_rssi_state[index] ==
						BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wअगरi_rssi_state[index] ==
						BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (wअगरi_rssi >= rssi_thresh +
					 BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state switch to High\n");
			पूर्ण अन्यथा अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (wअगरi_rssi < rssi_thresh) अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state switch to Low\n");
			पूर्ण अन्यथा अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (level_num == 3) अणु
		अगर (rssi_thresh > rssi_thresh1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], wifi RSSI thresh error!!\n");
			वापस coex_sta->pre_wअगरi_rssi_state[index];
		पूर्ण

		अगर ((coex_sta->pre_wअगरi_rssi_state[index] ==
						BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wअगरi_rssi_state[index] ==
						BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (wअगरi_rssi >= rssi_thresh +
					BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state switch to Medium\n");
			पूर्ण अन्यथा अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अगर ((coex_sta->pre_wअगरi_rssi_state[index] ==
						BTC_RSSI_STATE_MEDIUM) ||
			   (coex_sta->pre_wअगरi_rssi_state[index] ==
						BTC_RSSI_STATE_STAY_MEDIUM)) अणु
			अगर (wअगरi_rssi >= rssi_thresh1 +
					 BTC_RSSI_COEX_THRESH_TOL_8723B_2ANT) अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state switch to High\n");
			पूर्ण अन्यथा अगर (wअगरi_rssi < rssi_thresh) अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state switch to Low\n");
			पूर्ण अन्यथा अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state stay at Medium\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (wअगरi_rssi < rssi_thresh1) अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state switch to Medium\n");
			पूर्ण अन्यथा अणु
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], wifi RSSI state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण

	coex_sta->pre_wअगरi_rssi_state[index] = wअगरi_rssi_state;

	वापस wअगरi_rssi_state;
पूर्ण

अटल
व्योम btc8723b2ant_limited_rx(काष्ठा btc_coexist *btcoexist, bool क्रमce_exec,
			     bool rej_ap_agg_pkt, bool bt_ctrl_agg_buf_size,
			     u8 agg_buf_size)
अणु
	bool reject_rx_agg = rej_ap_agg_pkt;
	bool bt_ctrl_rx_agg_size = bt_ctrl_agg_buf_size;
	u8 rx_agg_size = agg_buf_size;

	/* ============================================ */
	/*	Rx Aggregation related setting		*/
	/* ============================================ */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_TO_REJ_AP_AGG_PKT,
			   &reject_rx_agg);
	/* decide BT control aggregation buf size or not */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE,
			   &bt_ctrl_rx_agg_size);
	/* aggregate buf size, only work when BT control Rx aggregate size */
	btcoexist->btc_set(btcoexist, BTC_SET_U1_AGG_BUF_SIZE, &rx_agg_size);
	/* real update aggregation setting */
	btcoexist->btc_set(btcoexist, BTC_SET_ACT_AGGREGATE_CTRL, शून्य);
पूर्ण

अटल व्योम btc8723b2ant_monitor_bt_ctr(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u32 reg_hp_txrx, reg_lp_txrx, u32पंचांगp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0;
	u32 reg_lp_tx = 0, reg_lp_rx = 0;

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

	अगर ((coex_sta->low_priority_rx >= 950) &&
	    (coex_sta->low_priority_rx >= coex_sta->low_priority_tx) &&
	    (!coex_sta->under_ips))
		bt_link_info->slave_role = true;
	अन्यथा
		bt_link_info->slave_role = false;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], High Priority Tx/Rx(reg 0x%x)=0x%x(%d)/0x%x(%d)\n",
		reg_hp_txrx, reg_hp_tx, reg_hp_tx, reg_hp_rx, reg_hp_rx);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Low Priority Tx/Rx(reg 0x%x)=0x%x(%d)/0x%x(%d)\n",
		reg_lp_txrx, reg_lp_tx, reg_lp_tx, reg_lp_rx, reg_lp_rx);

	/* reset counter */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0xc);
पूर्ण

अटल व्योम btc8723b2ant_monitor_wअगरi_ctr(काष्ठा btc_coexist *btcoexist)
अणु
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
पूर्ण

अटल व्योम btc8723b2ant_query_bt_info(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	coex_sta->c2h_bt_info_req_sent = true;

	h2c_parameter[0] |= BIT0;	/* trigger */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Query Bt Info, FW write 0x61 = 0x%x\n",
		h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x61, 1, h2c_parameter);
पूर्ण

अटल bool btc8723b2ant_is_wअगरi_status_changed(काष्ठा btc_coexist *btcoexist)
अणु
	अटल bool pre_wअगरi_busy;
	अटल bool pre_under_4way;
	अटल bool pre_bt_hs_on;
	bool wअगरi_busy = false, under_4way = false, bt_hs_on = false;
	bool wअगरi_connected = false;
	u8 wअगरi_rssi_state = BTC_RSSI_STATE_HIGH;
	u8 पंचांगp;

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

		पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
				 coex_dm->चयन_thres_offset;
		wअगरi_rssi_state =
		     btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, पंचांगp, 0);

		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_LOW))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम btc8723b2ant_update_bt_link_info(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	bt_link_info->bt_link_exist = coex_sta->bt_link_exist;
	bt_link_info->sco_exist = coex_sta->sco_exist;
	bt_link_info->a2dp_exist = coex_sta->a2dp_exist;
	bt_link_info->pan_exist = coex_sta->pan_exist;
	bt_link_info->hid_exist = coex_sta->hid_exist;

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

अटल u8 btc8723b2ant_action_algorithm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	u8 algorithm = BT_8723B_2ANT_COEX_ALGO_UNDEFINED;
	u8 num_of_dअगरf_profile = 0;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	अगर (!bt_link_info->bt_link_exist) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], No BT link exists!!!\n");
		वापस algorithm;
	पूर्ण

	अगर (bt_link_info->sco_exist)
		num_of_dअगरf_profile++;
	अगर (bt_link_info->hid_exist)
		num_of_dअगरf_profile++;
	अगर (bt_link_info->pan_exist)
		num_of_dअगरf_profile++;
	अगर (bt_link_info->a2dp_exist)
		num_of_dअगरf_profile++;

	अगर (num_of_dअगरf_profile == 1) अणु
		अगर (bt_link_info->sco_exist) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], SCO only\n");
			algorithm = BT_8723B_2ANT_COEX_ALGO_SCO;
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], HID only\n");
				algorithm = BT_8723B_2ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], A2DP only\n");
				algorithm = BT_8723B_2ANT_COEX_ALGO_A2DP;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], PAN(HS) only\n");
					algorithm =
						BT_8723B_2ANT_COEX_ALGO_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], PAN(EDR) only\n");
					algorithm =
						BT_8723B_2ANT_COEX_ALGO_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 2) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], SCO + HID\n");
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], SCO + A2DP ==> SCO\n");
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + PAN(HS)\n");
					algorithm = BT_8723B_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + PAN(EDR)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], HID + A2DP\n");
				algorithm = BT_8723B_2ANT_COEX_ALGO_HID_A2DP;
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + PAN(HS)\n");
					algorithm = BT_8723B_2ANT_COEX_ALGO_HID;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + PAN(EDR)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], A2DP + PAN(HS)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_A2DP_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex],A2DP + PAN(EDR)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_A2DP;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 3) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], SCO + HID + A2DP ==> HID\n");
				algorithm = BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + PAN(HS)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + PAN(EDR)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + A2DP + PAN(HS)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + A2DP + PAN(EDR) ==> HID\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + A2DP + PAN(HS)\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + A2DP + PAN(EDR)\n");
					algorithm =
					BT_8723B_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile >= 3) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], Error!!! SCO + HID + A2DP + PAN(HS)\n");
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + A2DP + PAN(EDR)==>PAN(EDR)+HID\n");
					algorithm =
					    BT_8723B_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस algorithm;
पूर्ण

अटल व्योम btc8723b2ant_set_fw_dac_swing_level(काष्ठा btc_coexist *btcoexist,
						u8 dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	/* There are several type of dacswing
	 * 0x18/ 0x10/ 0xc/ 0x8/ 0x4/ 0x6
	 */
	h2c_parameter[0] = dac_swing_lvl;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Set Dac Swing Level=0x%x\n", dac_swing_lvl);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], FW write 0x64=0x%x\n", h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x64, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8723b2ant_set_fw_dec_bt_pwr(काष्ठा btc_coexist *btcoexist,
					   u8 dec_bt_pwr_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	h2c_parameter[0] = dec_bt_pwr_lvl;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], decrease Bt Power Level : %u\n", dec_bt_pwr_lvl);

	btcoexist->btc_fill_h2c(btcoexist, 0x62, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8723b2ant_dec_bt_pwr(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u8 dec_bt_pwr_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Dec BT power level = %u\n", dec_bt_pwr_lvl);
	coex_dm->cur_dec_bt_pwr_lvl = dec_bt_pwr_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], PreDecBtPwrLvl=%d, CurDecBtPwrLvl=%d\n",
			coex_dm->pre_dec_bt_pwr_lvl,
			coex_dm->cur_dec_bt_pwr_lvl);

		अगर (coex_dm->pre_dec_bt_pwr_lvl == coex_dm->cur_dec_bt_pwr_lvl)
			वापस;
	पूर्ण
	btc8723b2ant_set_fw_dec_bt_pwr(btcoexist, coex_dm->cur_dec_bt_pwr_lvl);

	coex_dm->pre_dec_bt_pwr_lvl = coex_dm->cur_dec_bt_pwr_lvl;
पूर्ण

अटल
व्योम halbtc8723b2ant_set_bt_स्वतः_report(काष्ठा btc_coexist *btcoexist,
					bool enable_स्वतः_report)
अणु
	u8 h2c_parameter[1] = अणु0पूर्ण;

	h2c_parameter[0] = 0;

	अगर (enable_स्वतः_report)
		h2c_parameter[0] |= BIT(0);

	btcoexist->btc_fill_h2c(btcoexist, 0x68, 1, h2c_parameter);
पूर्ण

अटल
व्योम btc8723b2ant_bt_स्वतः_report(काष्ठा btc_coexist *btcoexist,
				 bool क्रमce_exec, bool enable_स्वतः_report)
अणु
	coex_dm->cur_bt_स्वतः_report = enable_स्वतः_report;

	अगर (!क्रमce_exec) अणु
		अगर (coex_dm->pre_bt_स्वतः_report == coex_dm->cur_bt_स्वतः_report)
			वापस;
	पूर्ण
	halbtc8723b2ant_set_bt_स्वतः_report(btcoexist,
					   coex_dm->cur_bt_स्वतः_report);

	coex_dm->pre_bt_स्वतः_report = coex_dm->cur_bt_स्वतः_report;
पूर्ण

अटल व्योम btc8723b2ant_fw_dac_swing_lvl(काष्ठा btc_coexist *btcoexist,
					  bool क्रमce_exec, u8 fw_dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s set FW Dac Swing level = %d\n",
		(क्रमce_exec ? "force to" : ""), fw_dac_swing_lvl);
	coex_dm->cur_fw_dac_swing_lvl = fw_dac_swing_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], preFwDacSwingLvl=%d, curFwDacSwingLvl=%d\n",
			coex_dm->pre_fw_dac_swing_lvl,
			coex_dm->cur_fw_dac_swing_lvl);

		अगर (coex_dm->pre_fw_dac_swing_lvl ==
		   coex_dm->cur_fw_dac_swing_lvl)
			वापस;
	पूर्ण

	btc8723b2ant_set_fw_dac_swing_level(btcoexist,
					    coex_dm->cur_fw_dac_swing_lvl);
	coex_dm->pre_fw_dac_swing_lvl = coex_dm->cur_fw_dac_swing_lvl;
पूर्ण

अटल व्योम btc8723b_set_penalty_txrate(काष्ठा btc_coexist *btcoexist,
					bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[6] = अणु0पूर्ण;

	h2c_parameter[0] = 0x6;	/* op_code, 0x6 = Retry_Penalty */

	अगर (low_penalty_ra) अणु
		h2c_parameter[1] |= BIT0;
		/* normal rate except MCS7/6/5, OFDM54/48/36 */
		h2c_parameter[2] = 0x00;
		h2c_parameter[3] = 0xf4; /* MCS7 or OFDM54 */
		h2c_parameter[4] = 0xf5; /* MCS6 or OFDM48 */
		h2c_parameter[5] = 0xf6; /* MCS5 or OFDM36 */
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set WiFi Low-Penalty Retry: %s",
		(low_penalty_ra ? "ON!!" : "OFF!!"));

	btcoexist->btc_fill_h2c(btcoexist, 0x69, 6, h2c_parameter);
पूर्ण

अटल व्योम btc8723b2ant_low_penalty_ra(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn LowPenaltyRA = %s\n",
		(क्रमce_exec ? "force to" : ""), (low_penalty_ra ?
						 "ON" : "OFF"));
	coex_dm->cur_low_penalty_ra = low_penalty_ra;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bPreLowPenaltyRa=%d, bCurLowPenaltyRa=%d\n",
			coex_dm->pre_low_penalty_ra,
			coex_dm->cur_low_penalty_ra);

		अगर (coex_dm->pre_low_penalty_ra == coex_dm->cur_low_penalty_ra)
			वापस;
	पूर्ण
	btc8723b_set_penalty_txrate(btcoexist, coex_dm->cur_low_penalty_ra);

	coex_dm->pre_low_penalty_ra = coex_dm->cur_low_penalty_ra;
पूर्ण

अटल व्योम btc8723b2ant_set_dac_swing_reg(काष्ठा btc_coexist *btcoexist,
					   u32 level)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 val = (u8) level;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Write SwDacSwing = 0x%x\n", level);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x883, 0x3e, val);
पूर्ण

अटल व्योम btc8723b2ant_set_sw_fullसमय_dac_swing(काष्ठा btc_coexist *btcoex,
						   bool sw_dac_swing_on,
						   u32 sw_dac_swing_lvl)
अणु
	अगर (sw_dac_swing_on)
		btc8723b2ant_set_dac_swing_reg(btcoex, sw_dac_swing_lvl);
	अन्यथा
		btc8723b2ant_set_dac_swing_reg(btcoex, 0x18);
पूर्ण

अटल व्योम btc8723b2ant_dac_swing(काष्ठा btc_coexist *btcoexist,
				   bool क्रमce_exec, bool dac_swing_on,
				   u32 dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn DacSwing=%s, dac_swing_lvl=0x%x\n",
		(क्रमce_exec ? "force to" : ""),
		(dac_swing_on ? "ON" : "OFF"), dac_swing_lvl);
	coex_dm->cur_dac_swing_on = dac_swing_on;
	coex_dm->cur_dac_swing_lvl = dac_swing_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bPreDacSwingOn=%d, preDacSwingLvl=0x%x, bCurDacSwingOn=%d, curDacSwingLvl=0x%x\n",
			coex_dm->pre_dac_swing_on,
			coex_dm->pre_dac_swing_lvl,
			coex_dm->cur_dac_swing_on,
			coex_dm->cur_dac_swing_lvl);

		अगर ((coex_dm->pre_dac_swing_on == coex_dm->cur_dac_swing_on) &&
		    (coex_dm->pre_dac_swing_lvl == coex_dm->cur_dac_swing_lvl))
			वापस;
	पूर्ण
	mdelay(30);
	btc8723b2ant_set_sw_fullसमय_dac_swing(btcoexist, dac_swing_on,
					       dac_swing_lvl);

	coex_dm->pre_dac_swing_on = coex_dm->cur_dac_swing_on;
	coex_dm->pre_dac_swing_lvl = coex_dm->cur_dac_swing_lvl;
पूर्ण

अटल व्योम btc8723b2ant_set_coex_table(काष्ठा btc_coexist *btcoexist,
					u32 val0x6c0, u32 val0x6c4,
					u32 val0x6c8, u8 val0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6c0=0x%x\n", val0x6c0);
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x6c0, val0x6c0);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6c4=0x%x\n", val0x6c4);
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x6c4, val0x6c4);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6c8=0x%x\n", val0x6c8);
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x6c8, val0x6c8);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set coex table, set 0x6cc=0x%x\n", val0x6cc);
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x6cc, val0x6cc);
पूर्ण

अटल व्योम btc8723b2ant_coex_table(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u32 val0x6c0,
				    u32 val0x6c4, u32 val0x6c8,
				    u8 val0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s write Coex Table 0x6c0=0x%x, 0x6c4=0x%x, 0x6c8=0x%x, 0x6cc=0x%x\n",
		क्रमce_exec ? "force to" : "",
		val0x6c0, val0x6c4, val0x6c8, val0x6cc);
	coex_dm->cur_val0x6c0 = val0x6c0;
	coex_dm->cur_val0x6c4 = val0x6c4;
	coex_dm->cur_val0x6c8 = val0x6c8;
	coex_dm->cur_val0x6cc = val0x6cc;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], preVal0x6c0=0x%x, preVal0x6c4=0x%x, preVal0x6c8=0x%x, preVal0x6cc=0x%x !!\n",
			coex_dm->pre_val0x6c0, coex_dm->pre_val0x6c4,
			coex_dm->pre_val0x6c8, coex_dm->pre_val0x6cc);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], curVal0x6c0=0x%x, curVal0x6c4=0x%x, curVal0x6c8=0x%x, curVal0x6cc=0x%x !!\n",
			coex_dm->cur_val0x6c0, coex_dm->cur_val0x6c4,
			coex_dm->cur_val0x6c8, coex_dm->cur_val0x6cc);

		अगर ((coex_dm->pre_val0x6c0 == coex_dm->cur_val0x6c0) &&
		    (coex_dm->pre_val0x6c4 == coex_dm->cur_val0x6c4) &&
		    (coex_dm->pre_val0x6c8 == coex_dm->cur_val0x6c8) &&
		    (coex_dm->pre_val0x6cc == coex_dm->cur_val0x6cc))
			वापस;
	पूर्ण
	btc8723b2ant_set_coex_table(btcoexist, val0x6c0, val0x6c4,
				    val0x6c8, val0x6cc);

	coex_dm->pre_val0x6c0 = coex_dm->cur_val0x6c0;
	coex_dm->pre_val0x6c4 = coex_dm->cur_val0x6c4;
	coex_dm->pre_val0x6c8 = coex_dm->cur_val0x6c8;
	coex_dm->pre_val0x6cc = coex_dm->cur_val0x6cc;
पूर्ण

अटल व्योम btc8723b2ant_coex_table_with_type(काष्ठा btc_coexist *btcoexist,
					      bool क्रमce_exec, u8 type)
अणु
	चयन (type) अणु
	हाल 0:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x55555555, 0xffffff, 0x3);
		अवरोध;
	हाल 1:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x5afa5afa, 0xffffff, 0x3);
		अवरोध;
	हाल 2:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x5ada5ada,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 3:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0xaaaaaaaa,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 4:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0xffffffff,
					0xffffffff, 0xffffff, 0x3);
		अवरोध;
	हाल 5:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					0x5fff5fff, 0xffffff, 0x3);
		अवरोध;
	हाल 6:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55ff55ff,
					0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 7:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 8:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 9:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 10:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 11:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 12:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 13:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 14:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 15:
		btc8723b2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_set_fw_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
						bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	अगर (enable)
		h2c_parameter[0] |= BIT0; /* function enable */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set FW for BT Ignore Wlan_Act, FW write 0x63=0x%x\n",
		h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x63, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8723b2ant_set_lps_rpwm(काष्ठा btc_coexist *btcoexist,
				      u8 lps_val, u8 rpwm_val)
अणु
	u8 lps = lps_val;
	u8 rpwm = rpwm_val;

	btcoexist->btc_set(btcoexist, BTC_SET_U1_LPS_VAL, &lps);
	btcoexist->btc_set(btcoexist, BTC_SET_U1_RPWM_VAL, &rpwm);
पूर्ण

अटल व्योम btc8723b2ant_lps_rpwm(काष्ठा btc_coexist *btcoexist,
				  bool क्रमce_exec, u8 lps_val, u8 rpwm_val)
अणु
	coex_dm->cur_lps = lps_val;
	coex_dm->cur_rpwm = rpwm_val;

	अगर (!क्रमce_exec) अणु
		अगर ((coex_dm->pre_lps == coex_dm->cur_lps) &&
		    (coex_dm->pre_rpwm == coex_dm->cur_rpwm))
			वापस;
	पूर्ण
	btc8723b2ant_set_lps_rpwm(btcoexist, lps_val, rpwm_val);

	coex_dm->pre_lps = coex_dm->cur_lps;
	coex_dm->pre_rpwm = coex_dm->cur_rpwm;
पूर्ण

अटल व्योम btc8723b2ant_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
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
	btc8723b2ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
पूर्ण

अटल व्योम btc8723b2ant_set_fw_ps_tdma(काष्ठा btc_coexist *btcoexist, u8 byte1,
					u8 byte2, u8 byte3, u8 byte4, u8 byte5)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[5];
	अगर ((coex_sta->a2dp_exist) && (coex_sta->hid_exist))
		byte5 = byte5 | 0x1;

	h2c_parameter[0] = byte1;
	h2c_parameter[1] = byte2;
	h2c_parameter[2] = byte3;
	h2c_parameter[3] = byte4;
	h2c_parameter[4] = byte5;

	coex_dm->ps_tdma_para[0] = byte1;
	coex_dm->ps_tdma_para[1] = byte2;
	coex_dm->ps_tdma_para[2] = byte3;
	coex_dm->ps_tdma_para[3] = byte4;
	coex_dm->ps_tdma_para[4] = byte5;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], FW write 0x60(5bytes)=0x%x%08x\n",
		h2c_parameter[0],
		h2c_parameter[1] << 24 | h2c_parameter[2] << 16 |
		h2c_parameter[3] << 8 | h2c_parameter[4]);

	btcoexist->btc_fill_h2c(btcoexist, 0x60, 5, h2c_parameter);
पूर्ण

अटल व्योम btc8723b2ant_sw_mechanism(काष्ठा btc_coexist *btcoexist,
				      bool shrink_rx_lpf, bool low_penalty_ra,
				      bool limited_dig, bool bt_lna_स्थिरrain)
अणु
	btc8723b2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, low_penalty_ra);
पूर्ण

अटल व्योम btc8723b2ant_set_ant_path(काष्ठा btc_coexist *btcoexist,
				      u8 antpos_type, bool init_hwcfg,
				      bool wअगरi_off)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u32 fw_ver = 0, u32पंचांगp = 0;
	bool pg_ext_चयन = false;
	bool use_ext_चयन = false;
	u8 h2c_parameter[2] = अणु0पूर्ण;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_EXT_SWITCH, &pg_ext_चयन);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);

	अगर ((fw_ver < 0xc0000) || pg_ext_चयन)
		use_ext_चयन = true;

	अगर (init_hwcfg) अणु
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x39, 0x8, 0x1);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x974, 0xff);
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x944, 0x3, 0x3);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x930, 0x77);
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x67, 0x20, 0x1);

		अगर (fw_ver >= 0x180000) अणु
			/* Use H2C to set GNT_BT to High to aव्योम A2DP click */
			h2c_parameter[0] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		पूर्ण अन्यथा अणु
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x18);
		पूर्ण

		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x948, 0x0);

		/* WiFi TRx Mask off */
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A,
					  0x1, 0xfffff, 0x0);

		अगर (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT) अणु
			/* tell firmware "no antenna inverse" */
			h2c_parameter[0] = 0;
		पूर्ण अन्यथा अणु
			/* tell firmware "antenna inverse" */
			h2c_parameter[0] = 1;
		पूर्ण

		अगर (use_ext_चयन) अणु
			/* ext चयन type */
			h2c_parameter[1] = 1;
		पूर्ण अन्यथा अणु
			/* पूर्णांक चयन type */
			h2c_parameter[1] = 0;
		पूर्ण
		btcoexist->btc_fill_h2c(btcoexist, 0x65, 2, h2c_parameter);
	पूर्ण अन्यथा अणु
		अगर (fw_ver >= 0x180000) अणु
			/* Use H2C to set GNT_BT to "Control by PTA"*/
			h2c_parameter[0] = 0;
			btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1,
						h2c_parameter);
		पूर्ण अन्यथा अणु
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x0);
		पूर्ण
	पूर्ण

	/* ext चयन setting */
	अगर (use_ext_चयन) अणु
		अगर (init_hwcfg) अणु
			/* 0x4c[23] = 0, 0x4c[24] = 1 Ant controlled by WL/BT */
			u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
			u32पंचांगp &= ~BIT23;
			u32पंचांगp |= BIT24;
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u32पंचांगp);
		पूर्ण

		/* fixed पूर्णांकernal चयन S1->WiFi, S0->BT */
		अगर (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT)
			btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x948, 0x0);
		अन्यथा
			btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x948, 0x280);

		चयन (antpos_type) अणु
		हाल BTC_ANT_WIFI_AT_MAIN:
			/* ext चयन मुख्य at wअगरi */
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x92c,
							   0x3, 0x1);
			अवरोध;
		हाल BTC_ANT_WIFI_AT_AUX:
			/* ext चयन aux at wअगरi */
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist,
							   0x92c, 0x3, 0x2);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* पूर्णांकernal चयन */
		अगर (init_hwcfg) अणु
			/* 0x4c[23] = 0, 0x4c[24] = 1 Ant controlled by WL/BT */
			u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
			u32पंचांगp |= BIT23;
			u32पंचांगp &= ~BIT24;
			btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u32पंचांगp);
		पूर्ण

		/* fixed ext चयन, S1->Main, S0->Aux */
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x64, 0x1, 0x0);
		चयन (antpos_type) अणु
		हाल BTC_ANT_WIFI_AT_MAIN:
			/* fixed पूर्णांकernal चयन S1->WiFi, S0->BT */
			btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x948, 0x0);
			अवरोध;
		हाल BTC_ANT_WIFI_AT_AUX:
			/* fixed पूर्णांकernal चयन S0->WiFi, S1->BT */
			btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x948, 0x280);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_ps_tdma(काष्ठा btc_coexist *btcoexist, bool क्रमce_exec,
				 bool turn_on, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u8 wअगरi_rssi_state, bt_rssi_state;
	s8 wअगरi_duration_adjust = 0x0;
	u8 tdma_byte4_modअगरy = 0x0;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	wअगरi_rssi_state = btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn %s PS TDMA, type=%d\n",
		(क्रमce_exec ? "force to" : ""),
		(turn_on ? "ON" : "OFF"), type);
	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	अगर (!(BTC_RSSI_HIGH(wअगरi_rssi_state) &&
	      BTC_RSSI_HIGH(bt_rssi_state)) && turn_on) अणु
		 /* क्रम WiFi RSSI low or BT RSSI low */
		type = type + 100;
		coex_dm->is_चयन_to_1करोt5_ant = true;
	पूर्ण अन्यथा अणु
		coex_dm->is_चयन_to_1करोt5_ant = false;
	पूर्ण

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bPrePsTdmaOn = %d, bCurPsTdmaOn = %d!!\n",
			coex_dm->pre_ps_tdma_on, coex_dm->cur_ps_tdma_on);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], prePsTdma = %d, curPsTdma = %d!!\n",
			coex_dm->pre_ps_tdma, coex_dm->cur_ps_tdma);

		अगर ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			वापस;
	पूर्ण

	अगर (coex_sta->scan_ap_num <= 5) अणु
		अगर (coex_sta->a2dp_bit_pool >= 45)
			wअगरi_duration_adjust = -15;
		अन्यथा अगर (coex_sta->a2dp_bit_pool >= 35)
			wअगरi_duration_adjust = -10;
		अन्यथा
			wअगरi_duration_adjust = 5;
	पूर्ण अन्यथा अगर (coex_sta->scan_ap_num <= 20) अणु
		अगर (coex_sta->a2dp_bit_pool >= 45)
			wअगरi_duration_adjust = -15;
		अन्यथा अगर (coex_sta->a2dp_bit_pool >= 35)
			wअगरi_duration_adjust = -10;
		अन्यथा
			wअगरi_duration_adjust = 0;
	पूर्ण अन्यथा अगर (coex_sta->scan_ap_num <= 40) अणु
		अगर (coex_sta->a2dp_bit_pool >= 45)
			wअगरi_duration_adjust = -15;
		अन्यथा अगर (coex_sta->a2dp_bit_pool >= 35)
			wअगरi_duration_adjust = -10;
		अन्यथा
			wअगरi_duration_adjust = -5;
	पूर्ण अन्यथा अणु
		अगर (coex_sta->a2dp_bit_pool >= 45)
			wअगरi_duration_adjust = -15;
		अन्यथा अगर (coex_sta->a2dp_bit_pool >= 35)
			wअगरi_duration_adjust = -10;
		अन्यथा
			wअगरi_duration_adjust = -10;
	पूर्ण

	अगर ((bt_link_info->slave_role) && (bt_link_info->a2dp_exist))
		/* 0x778 = 0x1 at wअगरi slot (no blocking BT Low-Pri pkts) */
		tdma_byte4_modअगरy = 0x1;

	अगर (turn_on) अणु
		चयन (type) अणु
		हाल 1:
		शेष:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c,
				0x03, 0xf1, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 2:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x03, 0xf1, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 3:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 4:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x03, 0xf1,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 5:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c,
				0x3, 0x70, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 6:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x3, 0x70, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 7:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 8:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x10,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 9:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c + wअगरi_duration_adjust,
				0x03, 0xf1, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 10:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x03, 0xf1, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 11:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 12:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 13:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c,
				0x3, 0x70, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 14:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x2d,
				0x3, 0x70, 0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 15:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 16:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0x70,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 17:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x2f,
						    0x2f, 0x60, 0x90);
			अवरोध;
		हाल 18:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x5, 0x5,
						    0xe1, 0x90);
			अवरोध;
		हाल 19:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0xe1, 0x90);
			अवरोध;
		हाल 20:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0x60, 0x90);
			अवरोध;
		हाल 21:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			अवरोध;

		हाल 23:
		हाल 123:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x35,
						    0x03, 0x71, 0x10);
			अवरोध;
		हाल 71:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xe3, 0x3c + wअगरi_duration_adjust,
				0x03, 0xf1, 0x90);
			अवरोध;
		हाल 101:
		हाल 105:
		हाल 113:
		हाल 171:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xd3, 0x3a + wअगरi_duration_adjust,
				0x03, 0x70, 0x50 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 102:
		हाल 106:
		हाल 110:
		हाल 114:
			btc8723b2ant_set_fw_ps_tdma(
				btcoexist, 0xd3, 0x2d + wअगरi_duration_adjust,
				0x03, 0x70, 0x50 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 103:
		हाल 107:
		हाल 111:
		हाल 115:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1c,
						    0x03, 0x70,
						    0x50 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 104:
		हाल 108:
		हाल 112:
		हाल 116:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x10,
						    0x03, 0x70,
						    0x50 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 109:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 121:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70,
						    0x90 | tdma_byte4_modअगरy);
			अवरोध;
		हाल 22:
		हाल 122:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x35,
						    0x03, 0x71, 0x11);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable PS tdma */
		चयन (type) अणु
		हाल 0:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			अवरोध;
		हाल 1:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x48, 0x0);
			अवरोध;
		शेष:
			btc8723b2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			अवरोध;
		पूर्ण
	पूर्ण

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
पूर्ण

अटल व्योम btc8723b2ant_ps_tdma_check_क्रम_घातer_save_state(
		काष्ठा btc_coexist *btcoexist, bool new_ps_state)
अणु
	u8 lps_mode = 0x0;

	btcoexist->btc_get(btcoexist, BTC_GET_U1_LPS_MODE, &lps_mode);

	अगर (lps_mode) अणु
		/* alपढ़ोy under LPS state */
		अगर (new_ps_state) अणु
			/* keep state under LPS, करो nothing. */
		पूर्ण अन्यथा अणु
			/* will leave LPS state, turn off psTdma first */
			btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* NO PS state */
		अगर (new_ps_state) अणु
			/* will enter LPS state, turn off psTdma first */
			btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		पूर्ण अन्यथा अणु
			/* keep state under NO PS state, करो nothing. */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_घातer_save_state(काष्ठा btc_coexist *btcoexist,
					  u8 ps_type, u8 lps_val, u8 rpwm_val)
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
		btc8723b2ant_ps_tdma_check_क्रम_घातer_save_state(btcoexist,
								true);
		btc8723b2ant_lps_rpwm(btcoexist, NORMAL_EXEC, lps_val,
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
		btc8723b2ant_ps_tdma_check_क्रम_घातer_save_state(btcoexist,
								false);
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_LEAVE_LPS, शून्य);
		coex_sta->क्रमce_lps_on = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_coex_alloff(काष्ठा btc_coexist *btcoexist)
अणु
	/* fw all off */
	btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	/* sw all off */
	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);

	/* hw all off */
	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
	btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम btc8723b2ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	/* क्रमce to reset coex mechanism*/
	btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	btc8723b2ant_ps_tdma(btcoexist, FORCE_EXEC, false, 1);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 6);
	btc8723b2ant_dec_bt_pwr(btcoexist, FORCE_EXEC, 0);

	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);

	coex_sta->pop_event_cnt = 0;
पूर्ण

अटल व्योम btc8723b2ant_action_bt_inquiry(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_connected = false;
	bool low_pwr_disable = true;
	bool scan = false, link = false, roam = false;

	btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
			   &low_pwr_disable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	अगर (coex_sta->bt_abnormal_scan) अणु
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 23);
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);
	पूर्ण अन्यथा अगर (scan || link || roam) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi link process + BT Inq/Page!!\n");
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
	पूर्ण अन्यथा अगर (wअगरi_connected) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi connected + BT Inq/Page!!\n");
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
	पूर्ण
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 6);
	btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);
पूर्ण

अटल व्योम btc8723b2ant_action_wअगरi_link_process(काष्ठा btc_coexist
						     *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u32 u32पंचांगp;
	u8 u8पंचांगpa, u8पंचांगpb;

	btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
	btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);

	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);

	u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x948);
	u8पंचांगpa = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765);
	u8पंचांगpb = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x76e);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], 0x948 = 0x%x, 0x765 = 0x%x, 0x76e = 0x%x\n",
		u32पंचांगp, u8पंचांगpa, u8पंचांगpb);
पूर्ण

अटल bool btc8723b2ant_action_wअगरi_idle_process(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 wअगरi_rssi_state1;
	u8 ap_num = 0;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
		 coex_dm->चयन_thres_offset - coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
	      coex_dm->चयन_thres_offset - coex_dm->चयन_thres_offset;
	btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM, &ap_num);

	/* office environment */
	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && (coex_sta->hid_exist) &&
	    (coex_sta->a2dp_exist)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi  idle process for BT HID+A2DP exist!!\n");

		btc8723b2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x6);
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		/* sw all off */
		btc8723b2ant_sw_mechanism(btcoexist, false, false, false,
					  false);
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

		वापस true;
	पूर्ण

	btc8723b2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x18);
	वापस false;
पूर्ण

अटल bool btc8723b2ant_is_common_action(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool common = false, wअगरi_connected = false;
	bool wअगरi_busy = false;
	bool bt_hs_on = false, low_pwr_disable = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);

	अगर (!wअगरi_connected) अणु
		low_pwr_disable = false;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC,
					false, false, 0x8);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi non-connected idle!!\n");

		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x0);
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		btc8723b2ant_sw_mechanism(btcoexist, false, false, false,
					  false);

		common = true;
	पूर्ण अन्यथा अणु
		अगर (BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		    coex_dm->bt_status) अणु
			low_pwr_disable = false;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);
			btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC,
						false, false, 0x8);

			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Wifi connected + BT non connected-idle!!\n");

			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x0);
			btc8723b2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 0);
			btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
			btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      0xb);
			btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8723b2ant_sw_mechanism(btcoexist, false, false,
						  false, false);

			common = true;
		पूर्ण अन्यथा अगर (BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE ==
			   coex_dm->bt_status) अणु
			low_pwr_disable = true;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			अगर (bt_hs_on)
				वापस false;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Wifi connected + BT connected-idle!!\n");
			btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC,
						false, false, 0x8);

			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x0);
			btc8723b2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 0);
			btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
			btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      0xb);
			btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8723b2ant_sw_mechanism(btcoexist, true, false,
						  false, false);

			common = true;
		पूर्ण अन्यथा अणु
			low_pwr_disable = true;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			अगर (wअगरi_busy) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], Wifi Connected-Busy + BT Busy!!\n");
				common = false;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], Wifi Connected-Idle + BT Busy!!\n");

				common =
				    btc8723b2ant_action_wअगरi_idle_process(
						btcoexist);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस common;
पूर्ण

अटल व्योम btc8723b2ant_tdma_duration_adjust(काष्ठा btc_coexist *btcoexist,
					  bool sco_hid, bool tx_छोड़ो,
					  u8 max_पूर्णांकerval)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल s32 up, dn, m, n, रुको_count;
	/*0: no change, +1: increase WiFi duration, -1: decrease WiFi duration*/
	s32 result;
	u8 retry_count = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], TdmaDurationAdjust()\n");

	अगर (!coex_dm->स्वतः_tdma_adjust) अणु
		coex_dm->स्वतः_tdma_adjust = true;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], first run TdmaDurationAdjust()!!\n");
		अगर (sco_hid) अणु
			अगर (tx_छोड़ो) अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 13);
					coex_dm->ps_tdma_du_adj_type = 13;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 9);
					coex_dm->ps_tdma_du_adj_type = 9;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
						     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tx_छोड़ो) अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 1);
					coex_dm->ps_tdma_du_adj_type = 1;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण
			पूर्ण
		पूर्ण

		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		result = 0;
		रुको_count = 0;
	पूर्ण अन्यथा अणु
		/*accquire the BT TRx retry count from BT_Info byte2*/
		retry_count = coex_sta->bt_retry_cnt;

		अगर ((coex_sta->low_priority_tx) > 1050 ||
		    (coex_sta->low_priority_rx) > 1250)
			retry_count++;

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], retry_count = %d\n", retry_count);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], up=%d, dn=%d, m=%d, n=%d, wait_count=%d\n",
			up, dn, m, n, रुको_count);
		result = 0;
		रुको_count++;
		 /* no retry in the last 2-second duration*/
		अगर (retry_count == 0) अणु
			up++;
			dn--;

			अगर (dn <= 0)
				dn = 0;

			अगर (up >= n) अणु
				/* अगर retry count during continuous n*2
				 * seconds is 0, enlarge WiFi duration
				 */
				रुको_count = 0;
				n = 3;
				up = 0;
				dn = 0;
				result = 1;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], Increase wifi duration!!\n");
			पूर्ण /* <=3 retry in the last 2-second duration*/
		पूर्ण अन्यथा अगर (retry_count <= 3) अणु
			up--;
			dn++;

			अगर (up <= 0)
				up = 0;

			अगर (dn == 2) अणु
				/* अगर continuous 2 retry count(every 2
				 * seconds) >0 and < 3, reduce WiFi duration
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
					"[BTCoex], Decrease wifi duration for retry_counter<3!!\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			/* retry count > 3, once retry count > 3, to reduce
			 *  WiFi duration
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
				"[BTCoex], Decrease wifi duration for retry_counter>3!!\n");
		पूर्ण

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], max Interval = %d\n", max_पूर्णांकerval);
		अगर (max_पूर्णांकerval == 1) अणु
			अगर (tx_छोड़ो) अणु
				अगर (coex_dm->cur_ps_tdma == 71) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 1) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 4) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 9) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 13);
					coex_dm->ps_tdma_du_adj_type = 13;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				पूर्ण

				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 5) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 13) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 8) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 5);
						coex_dm->ps_tdma_du_adj_type =
							5;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 13);
						coex_dm->ps_tdma_du_adj_type =
							13;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (coex_dm->cur_ps_tdma == 5) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 71);
					coex_dm->ps_tdma_du_adj_type = 71;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 8) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 13) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 9);
					coex_dm->ps_tdma_du_adj_type = 9;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				पूर्ण

				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 71) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 1);
						coex_dm->ps_tdma_du_adj_type =
							1;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 4) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 1);
						coex_dm->ps_tdma_du_adj_type =
							1;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 71);
						coex_dm->ps_tdma_du_adj_type =
							71;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 9);
						coex_dm->ps_tdma_du_adj_type =
							9;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
			अगर (tx_छोड़ो) अणु
				अगर (coex_dm->cur_ps_tdma == 1) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 4) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 9) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 5) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 13) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 8) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (coex_dm->cur_ps_tdma == 5) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 8) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 13) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 4) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
			अगर (tx_छोड़ो) अणु
				अगर (coex_dm->cur_ps_tdma == 1) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 4) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 9) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 5) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 13) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 8) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (coex_dm->cur_ps_tdma == 5) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 8) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 13) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
					btc8723b2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 4) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8723b2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], max Interval = %d\n", max_पूर्णांकerval);

	/* अगर current PsTdma not match with the recorded one (scan, dhcp, ...),
	 * then we have to adjust it back to the previous recorded one.
	 */
	अगर (coex_dm->cur_ps_tdma != coex_dm->ps_tdma_du_adj_type) अणु
		bool scan = false, link = false, roam = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], PsTdma type mismatch!!!, curPsTdma=%d, recordPsTdma=%d\n",
			coex_dm->cur_ps_tdma, coex_dm->ps_tdma_du_adj_type);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

		अगर (!scan && !link && !roam)
			btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
					     coex_dm->ps_tdma_du_adj_type);
		अन्यथा
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], roaming/link/scan is under progress, will adjust next time!!!\n");
	पूर्ण
पूर्ण

/* SCO only or SCO+PAN(HS) */
अटल व्योम btc8723b2ant_action_sco(काष्ठा btc_coexist *btcoexist)
अणु
	u8 bt_rssi_state;
	u32 wअगरi_bw;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8723b2ant_bt_rssi_state(
		btcoexist, 2, BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
					       coex_dm->चयन_thres_offset,
		0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 4);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर (BTC_WIFI_BW_LEGACY == wअगरi_bw)
		/* क्रम SCO quality at 11b/g mode */
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		/* क्रम SCO quality & wअगरi perक्रमmance balance at 11n mode */
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 8);

	/* क्रम voice quality */
	btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, true,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, true,
					  false, false);
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_action_hid(काष्ठा btc_coexist *btcoexist)
अणु
	u8 bt_rssi_state;
	u32 wअगरi_bw;
	u8 पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर (wअगरi_bw == BTC_WIFI_BW_LEGACY)
		/* क्रम HID at 11b/g mode */
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	अन्यथा
		/* क्रम HID quality & wअगरi perक्रमmance balance at 11n mode */
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 9);

	btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH))
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 9);
	अन्यथा
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 13);

	/* sw mechanism */
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40)
		btc8723b2ant_sw_mechanism(btcoexist, true, true, false, false);
	अन्यथा
		btc8723b2ant_sw_mechanism(btcoexist, false, true, false, false);
पूर्ण

/* A2DP only / PAN(EDR) only/ A2DP+PAN(HS) */
अटल व्योम btc8723b2ant_action_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;
	u8 ap_num = 0;
	u8 पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2, 40, 0);
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM, &ap_num);

	/* define the office environment */
	/* driver करोn't know AP num in Linux, so we will never enter this अगर */
	अगर (ap_num >= 10 && BTC_RSSI_HIGH(wअगरi_rssi_state1)) अणु
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x0);
		btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, false);
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

		/* sw mechanism */
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
		अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
			btc8723b2ant_sw_mechanism(btcoexist, true, false,
						  false, false);
		पूर्ण अन्यथा अणु
			btc8723b2ant_sw_mechanism(btcoexist, false, false,
						  false, false);
		पूर्ण
		वापस;
	पूर्ण

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 13);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH))
		btc8723b2ant_tdma_duration_adjust(btcoexist, false,
						  false, 1);
	अन्यथा
		btc8723b2ant_tdma_duration_adjust(btcoexist, false, true, 1);

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, false,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, false,
					  false, false);
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_action_a2dp_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 13);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	btc8723b2ant_tdma_duration_adjust(btcoexist, false, true, 2);

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, false,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, false,
					  false, false);
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_action_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 10);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 13);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH))
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 1);
	अन्यथा
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, false,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, false,
					  false, false);
	पूर्ण
पूर्ण

/* PAN(HS) only */
अटल व्योम btc8723b2ant_action_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	u8 bt_rssi_state;
	u32 wअगरi_bw;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, false,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, false,
					  false, false);
	पूर्ण
पूर्ण

/* PAN(EDR) + A2DP */
अटल व्योम btc8723b2ant_action_pan_edr_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	अन्यथा
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 12);
		अगर (BTC_WIFI_BW_HT40 == wअगरi_bw)
			btc8723b2ant_tdma_duration_adjust(btcoexist, false,
							  true, 3);
		अन्यथा
			btc8723b2ant_tdma_duration_adjust(btcoexist, false,
							  false, 3);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 3);
	पूर्ण

	/* sw mechanism	*/
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, false,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, false,
					  false, false);
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_action_pan_edr_hid(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 14);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
			btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      3);
			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x780);
		पूर्ण अन्यथा अणु
			btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      6);
			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x0);
		पूर्ण
		btc8723b2ant_tdma_duration_adjust(btcoexist, true, false, 2);
	पूर्ण अन्यथा अणु
		btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x0);
		btc8723b2ant_tdma_duration_adjust(btcoexist, true, true, 2);
	पूर्ण

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, true,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, true,
					  false, false);
	पूर्ण
पूर्ण

/* HID + A2DP + PAN(EDR) */
अटल व्योम btc8723b2ant_action_hid_a2dp_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 2, पंचांगp, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 14);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);


	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		अगर (BTC_WIFI_BW_HT40 == wअगरi_bw)
			btc8723b2ant_tdma_duration_adjust(btcoexist, true,
							  true, 2);
		अन्यथा
			btc8723b2ant_tdma_duration_adjust(btcoexist, true,
							  false, 3);
	पूर्ण अन्यथा अणु
		btc8723b2ant_tdma_duration_adjust(btcoexist, true, true, 3);
	पूर्ण

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, true,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, true,
					  false, false);
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_action_hid_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;
	u8 ap_num = 0;
	u8 पंचांगp = BT_8723B_2ANT_WIFI_RSSI_COEXSWITCH_THRES -
			coex_dm->चयन_thres_offset;

	btc8723b2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8723b2ant_wअगरi_rssi_state(btcoexist, 1, 2,
							पंचांगp, 0);
	पंचांगp = BT_8723B_2ANT_BT_RSSI_COEXSWITCH_THRES -
			 coex_dm->चयन_thres_offset;
	bt_rssi_state = btc8723b2ant_bt_rssi_state(btcoexist, 3, पंचांगp, 37);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8723b2ant_limited_rx(btcoexist, NORMAL_EXEC, false, true, 0x5);
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर (wअगरi_bw == BTC_WIFI_BW_LEGACY) अणु
		अगर (BTC_RSSI_HIGH(bt_rssi_state))
			btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		अन्यथा अगर (BTC_RSSI_MEDIUM(bt_rssi_state))
			btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		अन्यथा
			btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अणु
		/* only 802.11N mode we have to dec bt घातer to 4 degree */
		अगर (BTC_RSSI_HIGH(bt_rssi_state)) अणु
			/* need to check ap Number of Not */
			अगर (ap_num < 10)
				btc8723b2ant_dec_bt_pwr(btcoexist,
							NORMAL_EXEC, 4);
			अन्यथा
				btc8723b2ant_dec_bt_pwr(btcoexist,
							NORMAL_EXEC, 2);
		पूर्ण अन्यथा अगर (BTC_RSSI_MEDIUM(bt_rssi_state)) अणु
			btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		पूर्ण अन्यथा अणु
			btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		पूर्ण
	पूर्ण

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 14);
		btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	अगर (BTC_RSSI_HIGH(bt_rssi_state)) अणु
		अगर (ap_num < 10)
			btc8723b2ant_tdma_duration_adjust(btcoexist, true,
							  false, 1);
		अन्यथा
			btc8723b2ant_tdma_duration_adjust(btcoexist, true,
							  false, 3);
	पूर्ण अन्यथा अणु
		btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 18);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x456, 0x38);
		btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x42a, 0x0808);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x430, 0x0);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x434, 0x01010000);

		अगर (ap_num < 10)
			btc8723b2ant_tdma_duration_adjust(btcoexist, true,
							  true, 1);
		अन्यथा
			btc8723b2ant_tdma_duration_adjust(btcoexist, true,
							  true, 3);
	पूर्ण

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		btc8723b2ant_sw_mechanism(btcoexist, true, true,
					  false, false);
	पूर्ण अन्यथा अणु
		btc8723b2ant_sw_mechanism(btcoexist, false, true,
					  false, false);
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_action_wअगरi_multi_port(काष्ठा btc_coexist *btcoexist)
अणु
	btc8723b2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8723b2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	/* sw all off */
	btc8723b2ant_sw_mechanism(btcoexist, false, false, false, false);

	/* hw all off */
	btc8723b2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	btc8723b2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8723b2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
पूर्ण

अटल व्योम btc8723b2ant_run_coexist_mechanism(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 algorithm = 0;
	u32 num_of_wअगरi_link = 0;
	u32 wअगरi_link_status = 0;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool miracast_plus_bt = false;
	bool scan = false, link = false, roam = false;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], RunCoexistMechanism()===>\n");

	अगर (btcoexist->manual_control) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for Manual CTRL <===\n");
		वापस;
	पूर्ण

	अगर (coex_sta->under_ips) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], wifi is under IPS !!!\n");
		वापस;
	पूर्ण

	algorithm = btc8723b2ant_action_algorithm(btcoexist);
	अगर (coex_sta->c2h_bt_inquiry_page &&
	    (BT_8723B_2ANT_COEX_ALGO_PANHS != algorithm)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT is under inquiry/page scan !!\n");
		btc8723b2ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	अगर (scan || link || roam) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], WiFi is under Link Process !!\n");
		btc8723b2ant_action_wअगरi_link_process(btcoexist);
		वापस;
	पूर्ण

	/* क्रम P2P */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;

	अगर ((num_of_wअगरi_link >= 2) ||
	    (wअगरi_link_status & WIFI_P2P_GO_CONNECTED)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"############# [BTCoex],  Multi-Port num_of_wifi_link = %d, wifi_link_status = 0x%x\n",
			num_of_wअगरi_link, wअगरi_link_status);

		अगर (bt_link_info->bt_link_exist)
			miracast_plus_bt = true;
		अन्यथा
			miracast_plus_bt = false;

		btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
				   &miracast_plus_bt);
		btc8723b2ant_action_wअगरi_multi_port(btcoexist);

		वापस;
	पूर्ण

	miracast_plus_bt = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
			   &miracast_plus_bt);

	coex_dm->cur_algorithm = algorithm;
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Algorithm = %d\n",
		coex_dm->cur_algorithm);

	अगर (btc8723b2ant_is_common_action(btcoexist)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Action 2-Ant common\n");
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण अन्यथा अणु
		अगर (coex_dm->cur_algorithm != coex_dm->pre_algorithm) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], preAlgorithm=%d, curAlgorithm=%d\n",
				coex_dm->pre_algorithm,
				coex_dm->cur_algorithm);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण
		चयन (coex_dm->cur_algorithm) अणु
		हाल BT_8723B_2ANT_COEX_ALGO_SCO:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = SCO\n");
			btc8723b2ant_action_sco(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID\n");
			btc8723b2ant_action_hid(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = A2DP\n");
			btc8723b2ant_action_a2dp(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_A2DP_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = A2DP+PAN(HS)\n");
			btc8723b2ant_action_a2dp_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN(EDR)\n");
			btc8723b2ant_action_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HS mode\n");
			btc8723b2ant_action_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANEDR_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN+A2DP\n");
			btc8723b2ant_action_pan_edr_a2dp(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_PANEDR_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN(EDR)+HID\n");
			btc8723b2ant_action_pan_edr_hid(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID+A2DP+PAN\n");
			btc8723b2ant_action_hid_a2dp_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8723B_2ANT_COEX_ALGO_HID_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID+A2DP\n");
			btc8723b2ant_action_hid_a2dp(btcoexist);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = coexist All Off!!\n");
			btc8723b2ant_coex_alloff(btcoexist);
			अवरोध;
		पूर्ण
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	पूर्ण
पूर्ण

अटल व्योम btc8723b2ant_wअगरioff_hwcfg(काष्ठा btc_coexist *btcoexist)
अणु
	bool is_in_mp_mode = false;
	u8 h2c_parameter[2] = अणु0पूर्ण;
	u32 fw_ver = 0;

	/* set wlan_act to low */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);

	/* WiFi standby जबतक GNT_BT 0 -> 1 */
	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x780);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	अगर (fw_ver >= 0x180000) अणु
		/* Use H2C to set GNT_BT to HIGH */
		h2c_parameter[0] = 1;
		btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1, h2c_parameter);
	पूर्ण अन्यथा अणु
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x18);
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_IS_IN_MP_MODE,
			   &is_in_mp_mode);
	अगर (!is_in_mp_mode)
		/* BT select s0/s1 is controlled by BT */
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x67, 0x20, 0x0);
	अन्यथा
		/* BT select s0/s1 is controlled by WiFi */
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x67, 0x20, 0x1);
पूर्ण

/*********************************************************************
 *  बाह्य function start with ex_btc8723b2ant_
 *********************************************************************/
व्योम ex_btc8723b2ant_init_hwconfig(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 u8पंचांगp = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], 2Ant Init HW Config!!\n");
	coex_dm->bt_rf0x1e_backup =
		btcoexist->btc_get_rf_reg(btcoexist, BTC_RF_A, 0x1e, 0xfffff);

	/* 0x790[5:0] = 0x5 */
	u8पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x790);
	u8पंचांगp &= 0xc0;
	u8पंचांगp |= 0x5;
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x790, u8पंचांगp);

	/* Antenna config */
	btc8723b2ant_set_ant_path(btcoexist, BTC_ANT_WIFI_AT_MAIN,
				  true, false);
	coex_sta->dis_ver_info_cnt = 0;

	/* PTA parameter */
	btc8723b2ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);

	/* Enable counter statistics */
	/* 0x76e[3] = 1, WLAN_ACT controlled by PTA */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x778, 0x3);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x40, 0x20, 0x1);
	btcoexist->स्वतः_report_2ant = true;
पूर्ण

व्योम ex_btc8723b2ant_घातer_on_setting(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u16 u16पंचांगp = 0x0;
	u32 value = 0;

	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x67, 0x20);

	/* enable BB, REG_SYS_FUNC_EN such that we can ग_लिखो 0x948 correctly */
	u16पंचांगp = btcoexist->btc_पढ़ो_2byte(btcoexist, 0x2);
	btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x2, u16पंचांगp | BIT0 | BIT1);

	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x948, 0x0);

	अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_USB) अणु
		/* fixed at S0 क्रम USB पूर्णांकerface */
		board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
	पूर्ण अन्यथा अणु
		/* क्रम PCIE and SDIO पूर्णांकerface, we check efuse 0xc3[6] */
		अगर (board_info->single_ant_path == 0) अणु
			/* set to S1 */
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;
		पूर्ण अन्यथा अगर (board_info->single_ant_path == 1) अणु
			/* set to S0 */
			board_info->btdm_ant_pos = BTC_ANTENNA_AT_AUX_PORT;
		पूर्ण
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_ANTPOSREGRISTRY_CTRL,
				   &value);
	पूर्ण
पूर्ण

व्योम ex_btc8723b2ant_pre_load_firmware(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u8 u8पंचांगp = 0x4; /* Set BIT2 by शेष since it's 2ant हाल */

	/**
	 * S0 or S1 setting and Local रेजिस्टर setting(By this fw can get
	 * ant number, S0/S1, ... info)
	 *
	 * Local setting bit define
	 *	BIT0: "0" : no antenna inverse; "1" : antenna inverse
	 *	BIT1: "0" : पूर्णांकernal चयन; "1" : बाह्यal चयन
	 *	BIT2: "0" : one antenna; "1" : two antennas
	 *
	 * NOTE: here शेष all पूर्णांकernal चयन and 1-antenna ==> BIT1=0 and
	 * BIT2 = 0
	 */
	अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_USB) अणु
		/* fixed at S0 क्रम USB पूर्णांकerface */
		u8पंचांगp |= 0x1; /* antenna inverse */
		btcoexist->btc_ग_लिखो_local_reg_1byte(btcoexist, 0xfe08, u8पंचांगp);
	पूर्ण अन्यथा अणु
		/* क्रम PCIE and SDIO पूर्णांकerface, we check efuse 0xc3[6] */
		अगर (board_info->single_ant_path == 0) अणु
		पूर्ण अन्यथा अगर (board_info->single_ant_path == 1) अणु
			/* set to S0 */
			u8पंचांगp |= 0x1; /* antenna inverse */
		पूर्ण

		अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_PCI)
			btcoexist->btc_ग_लिखो_local_reg_1byte(btcoexist, 0x384,
							     u8पंचांगp);
		अन्यथा अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_SDIO)
			btcoexist->btc_ग_लिखो_local_reg_1byte(btcoexist, 0x60,
							     u8पंचांगp);
	पूर्ण
पूर्ण

व्योम ex_btc8723b2ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Coex Mechanism Init!!\n");
	btc8723b2ant_init_coex_dm(btcoexist);
पूर्ण

व्योम ex_btc8723b2ant_display_coex_info(काष्ठा btc_coexist *btcoexist,
				       काष्ठा seq_file *m)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u8 u8पंचांगp[4], i, bt_info_ext, ps_tdma_हाल = 0;
	u32 u32पंचांगp[4];
	bool roam = false, scan = false;
	bool link = false, wअगरi_under_5g = false;
	bool bt_hs_on = false, wअगरi_busy = false;
	s32 wअगरi_rssi = 0, bt_hs_rssi = 0;
	u32 wअगरi_bw, wअगरi_traffic_dir, fa_ofdm, fa_cck;
	u8 wअगरi_करोt11_chnl, wअगरi_hs_chnl;
	u32 fw_ver = 0, bt_patch_ver = 0;
	u8 ap_num = 0;

	seq_माला_दो(m, "\n ============[BT Coexist info]============");

	अगर (btcoexist->manual_control) अणु
		seq_माला_दो(m, "\n ==========[Under Manual Control]============");
		seq_माला_दो(m, "\n ==========================================");
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %d/ %d ",
		   "Ant PG number/ Ant mechanism:",
		   board_info->pg_ant_num, board_info->btdm_ant_num);

	seq_म_लिखो(m, "\n %-35s = %s / %d",
		   "BT stack/ hci ext ver",
		   ((stack_info->profile_notअगरied) ? "Yes" : "No"),
		   stack_info->hci_version);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER, &bt_patch_ver);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	seq_म_लिखो(m, "\n %-35s = %d_%x/ 0x%x/ 0x%x(%d)",
		   "CoexVer/ FwVer/ PatchVer",
		   glcoex_ver_date_8723b_2ant, glcoex_ver_8723b_2ant,
		   fw_ver, bt_patch_ver, bt_patch_ver);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_DOT11_CHNL,
			   &wअगरi_करोt11_chnl);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_HS_CHNL, &wअगरi_hs_chnl);

	seq_म_लिखो(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsChnl(HsMode)",
		   wअगरi_करोt11_chnl, wअगरi_hs_chnl, bt_hs_on);

	seq_म_लिखो(m, "\n %-35s = %3ph ",
		   "H2C Wifi inform bt chnl Info", coex_dm->wअगरi_chnl_info);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM, &ap_num);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d",
		   "Wifi rssi/ HS rssi/ AP#", wअगरi_rssi, bt_hs_rssi, ap_num);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d ",
		   "Wifi link/ roam/ scan", link, roam, scan);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION,
			   &wअगरi_traffic_dir);
	seq_म_लिखो(m, "\n %-35s = %s / %s/ %s ",
		   "Wifi status", (wअगरi_under_5g ? "5G" : "2.4G"),
		 ((wअगरi_bw == BTC_WIFI_BW_LEGACY) ? "Legacy" :
		 (((wअगरi_bw == BTC_WIFI_BW_HT40) ? "HT40" : "HT20"))),
		 ((!wअगरi_busy) ? "idle" :
		 ((wअगरi_traffic_dir == BTC_WIFI_TRAFFIC_TX) ?
		  "uplink" : "downlink")));

	seq_म_लिखो(m, "\n %-35s = %d / %d / %d / %d",
		   "SCO/HID/PAN/A2DP",
		   bt_link_info->sco_exist, bt_link_info->hid_exist,
		   bt_link_info->pan_exist, bt_link_info->a2dp_exist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_BT_LINK_INFO, m);

	bt_info_ext = coex_sta->bt_info_ext;
	seq_म_लिखो(m, "\n %-35s = %s",
		   "BT Info A2DP rate",
		   (bt_info_ext & BIT0) ? "Basic rate" : "EDR rate");

	क्रम (i = 0; i < BT_INFO_SRC_8723B_2ANT_MAX; i++) अणु
		अगर (coex_sta->bt_info_c2h_cnt[i]) अणु
			seq_म_लिखो(m, "\n %-35s = %7ph(%d)",
				   glbt_info_src_8723b_2ant[i],
				   coex_sta->bt_info_c2h[i],
				   coex_sta->bt_info_c2h_cnt[i]);
		पूर्ण
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %s/%s",
		   "PS state, IPS/LPS",
		   ((coex_sta->under_ips ? "IPS ON" : "IPS OFF")),
		   ((coex_sta->under_lps ? "LPS ON" : "LPS OFF")));
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD, m);

	/* Sw mechanism	*/
	seq_म_लिखो(m,
		   "\n %-35s", "============[Sw mechanism]============");
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d ",
		   "SM1[ShRf/ LpRA/ LimDig]", coex_dm->cur_rf_rx_lpf_shrink,
		   coex_dm->cur_low_penalty_ra, coex_dm->limited_dig);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d(0x%x) ",
		   "SM2[AgcT/ AdcB/ SwDacSwing(lvl)]",
		   coex_dm->cur_agc_table_en, coex_dm->cur_adc_back_off,
		   coex_dm->cur_dac_swing_on, coex_dm->cur_dac_swing_lvl);

	/* Fw mechanism	*/
	seq_म_लिखो(m, "\n %-35s",
		   "============[Fw mechanism]============");

	ps_tdma_हाल = coex_dm->cur_ps_tdma;
	seq_म_लिखो(m, "\n %-35s = %5ph case-%d (auto:%d)",
		   "PS TDMA", coex_dm->ps_tdma_para,
		   ps_tdma_हाल, coex_dm->स्वतः_tdma_adjust);

	seq_म_लिखो(m, "\n %-35s = %d/ %d ",
		   "DecBtPwr/ IgnWlanAct", coex_dm->cur_dec_bt_pwr_lvl,
		   coex_dm->cur_ignore_wlan_act);

	/* Hw setting */
	seq_म_लिखो(m, "\n %-35s",
		   "============[Hw setting]============");

	seq_म_लिखो(m, "\n %-35s = 0x%x",
		   "RF-A, 0x1e initVal", coex_dm->bt_rf0x1e_backup);

	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x778);
	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x880);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x778/0x880[29:25]", u8पंचांगp[0],
		   (u32पंचांगp[0] & 0x3e000000) >> 25);

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

	fa_ofdm = ((u32पंचांगp[0]&0xffff0000) >> 16) +
		  ((u32पंचांगp[1]&0xffff0000) >> 16) +
		   (u32पंचांगp[1] & 0xffff) +
		   (u32पंचांगp[2] & 0xffff) +
		  ((u32पंचांगp[3]&0xffff0000) >> 16) +
		   (u32पंचांगp[3] & 0xffff);
	fa_cck = (u8पंचांगp[0] << 8) + u8पंचांगp[1];

	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "OFDM-CCA/OFDM-FA/CCK-FA",
		   u32पंचांगp[0] & 0xffff, fa_ofdm, fa_cck);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c0);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c4);
	u32पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c8);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x6cc);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
		   "0x6c0/0x6c4/0x6c8/0x6cc(coexTable)",
		   u32पंचांगp[0], u32पंचांगp[1], u32पंचांगp[2], u8पंचांगp[0]);

	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x770(high-pri rx/tx)",
		   coex_sta->high_priority_rx, coex_sta->high_priority_tx);
	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x774(low-pri rx/tx)", coex_sta->low_priority_rx,
		   coex_sta->low_priority_tx);
	अगर (btcoexist->स्वतः_report_2ant)
		btc8723b2ant_monitor_bt_ctr(btcoexist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS, m);
पूर्ण

व्योम ex_btc8723b2ant_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_IPS_ENTER == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		btc8723b2ant_wअगरioff_hwcfg(btcoexist);
		btc8723b2ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
		btc8723b2ant_coex_alloff(btcoexist);
	पूर्ण अन्यथा अगर (BTC_IPS_LEAVE == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;
		ex_btc8723b2ant_init_hwconfig(btcoexist);
		btc8723b2ant_init_coex_dm(btcoexist);
		btc8723b2ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8723b2ant_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

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

व्योम ex_btc8723b2ant_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u32 u32पंचांगp;
	u8 u8पंचांगpa, u8पंचांगpb;

	u32पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x948);
	u8पंचांगpa = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765);
	u8पंचांगpb = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x76e);

	अगर (BTC_SCAN_START == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN START notify\n");
	अन्यथा अगर (BTC_SCAN_FINISH == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN FINISH notify\n");
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
			   &coex_sta->scan_ap_num);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"############# [BTCoex], 0x948=0x%x, 0x765=0x%x, 0x76e=0x%x\n",
		u32पंचांगp, u8पंचांगpa, u8पंचांगpb);
पूर्ण

व्योम ex_btc8723b2ant_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_ASSOCIATE_START == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT START notify\n");
	अन्यथा अगर (BTC_ASSOCIATE_FINISH == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT FINISH notify\n");
पूर्ण

व्योम ex_btc8723b2ant_media_status_notअगरy(काष्ठा btc_coexist *btcoexist,
					 u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[3] = अणु0पूर्ण;
	u32 wअगरi_bw;
	u8 wअगरi_central_chnl;
	u8 ap_num = 0;

	अगर (BTC_MEDIA_CONNECT == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA connect notify\n");
	अन्यथा
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA disconnect notify\n");

	/* only 2.4G we need to inक्रमm bt the chnl mask */
	btcoexist->btc_get(btcoexist,
		BTC_GET_U1_WIFI_CENTRAL_CHNL, &wअगरi_central_chnl);
	अगर ((BTC_MEDIA_CONNECT == type) &&
	    (wअगरi_central_chnl <= 14)) अणु
		h2c_parameter[0] = 0x1;
		h2c_parameter[1] = wअगरi_central_chnl;
		btcoexist->btc_get(btcoexist,
			BTC_GET_U4_WIFI_BW, &wअगरi_bw);
		अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
			h2c_parameter[2] = 0x30;
		पूर्ण अन्यथा अणु
			btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
					   &ap_num);
			अगर (ap_num < 10)
				h2c_parameter[2] = 0x30;
			अन्यथा
				h2c_parameter[2] = 0x20;
		पूर्ण
	पूर्ण

	coex_dm->wअगरi_chnl_info[0] = h2c_parameter[0];
	coex_dm->wअगरi_chnl_info[1] = h2c_parameter[1];
	coex_dm->wअगरi_chnl_info[2] = h2c_parameter[2];

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], FW write 0x66=0x%x\n",
		h2c_parameter[0] << 16 | h2c_parameter[1] << 8 |
		h2c_parameter[2]);

	btcoexist->btc_fill_h2c(btcoexist, 0x66, 3, h2c_parameter);
पूर्ण

व्योम ex_btc8723b2ant_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist,
					   u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (type == BTC_PACKET_DHCP)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], DHCP Packet notify\n");
पूर्ण

व्योम ex_btc8723b2ant_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist,
				    u8 *पंचांगpbuf, u8 length)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 bt_info = 0;
	u8 i, rsp_source = 0;
	bool bt_busy = false, limited_dig = false;
	bool wअगरi_connected = false;

	coex_sta->c2h_bt_info_req_sent = false;

	rsp_source = पंचांगpbuf[0]&0xf;
	अगर (rsp_source >= BT_INFO_SRC_8723B_2ANT_MAX)
		rsp_source = BT_INFO_SRC_8723B_2ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Bt info[%d], length=%d, hex data=[",
		rsp_source, length);
	क्रम (i = 0; i < length; i++) अणु
		coex_sta->bt_info_c2h[rsp_source][i] = पंचांगpbuf[i];
		अगर (i == 1)
			bt_info = पंचांगpbuf[i];
		अगर (i == length - 1)
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x]\n", पंचांगpbuf[i]);
		अन्यथा
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x, ", पंचांगpbuf[i]);
	पूर्ण

	अगर (btcoexist->manual_control) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), return for Manual CTRL<===\n");
		वापस;
	पूर्ण

	अगर (BT_INFO_SRC_8723B_2ANT_WIFI_FW != rsp_source) अणु
		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2] & 0xf;

		अगर (coex_sta->bt_retry_cnt >= 1)
			coex_sta->pop_event_cnt++;

		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->bt_info_ext = coex_sta->bt_info_c2h[rsp_source][4];

		अगर (coex_sta->bt_info_c2h[rsp_source][2] & 0x20)
			coex_sta->c2h_bt_remote_name_req = true;
		अन्यथा
			coex_sta->c2h_bt_remote_name_req = false;

		अगर (coex_sta->bt_info_c2h[rsp_source][1] == 0x49)
			coex_sta->a2dp_bit_pool =
				coex_sta->bt_info_c2h[rsp_source][6];
		अन्यथा
			coex_sta->a2dp_bit_pool = 0;

		/* Here we need to resend some wअगरi info to BT
		 * because BT is reset and loss of the info.
		 */
		अगर ((coex_sta->bt_info_ext & BIT1)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], BT ext info bit1 check, send wifi BW&Chnl to BT!!\n");
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
					   &wअगरi_connected);
			अगर (wअगरi_connected)
				ex_btc8723b2ant_media_status_notअगरy(
							btcoexist,
							BTC_MEDIA_CONNECT);
			अन्यथा
				ex_btc8723b2ant_media_status_notअगरy(
							btcoexist,
							BTC_MEDIA_DISCONNECT);
		पूर्ण

		अगर ((coex_sta->bt_info_ext & BIT3)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n");
			btc8723b2ant_ignore_wlan_act(btcoexist, FORCE_EXEC,
						     false);
		पूर्ण अन्यथा अणु
			/* BT alपढ़ोy NOT ignore Wlan active, करो nothing here.*/
		पूर्ण
		अगर (!btcoexist->स्वतः_report_2ant) अणु
			अगर (!(coex_sta->bt_info_ext & BIT4))
				btc8723b2ant_bt_स्वतः_report(btcoexist,
							    FORCE_EXEC, true);
		पूर्ण
	पूर्ण

	/* check BIT2 first ==> check अगर bt is under inquiry or page scan */
	अगर (bt_info & BT_INFO_8723B_2ANT_B_INQ_PAGE)
		coex_sta->c2h_bt_inquiry_page = true;
	अन्यथा
		coex_sta->c2h_bt_inquiry_page = false;

	अगर (!(bt_info & BT_INFO_8723B_2ANT_B_CONNECTION)) अणु
		/* set link exist status */
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	पूर्ण अन्यथा अणु
		/* connection exists */
		coex_sta->bt_link_exist = true;
		अगर (bt_info & BT_INFO_8723B_2ANT_B_FTP)
			coex_sta->pan_exist = true;
		अन्यथा
			coex_sta->pan_exist = false;
		अगर (bt_info & BT_INFO_8723B_2ANT_B_A2DP)
			coex_sta->a2dp_exist = true;
		अन्यथा
			coex_sta->a2dp_exist = false;
		अगर (bt_info & BT_INFO_8723B_2ANT_B_HID)
			coex_sta->hid_exist = true;
		अन्यथा
			coex_sta->hid_exist = false;
		अगर (bt_info & BT_INFO_8723B_2ANT_B_SCO_ESCO)
			coex_sta->sco_exist = true;
		अन्यथा
			coex_sta->sco_exist = false;

		अगर ((!coex_sta->hid_exist) &&
		    (!coex_sta->c2h_bt_inquiry_page) &&
		    (!coex_sta->sco_exist)) अणु
			अगर (coex_sta->high_priority_tx +
				    coex_sta->high_priority_rx >= 160) अणु
				coex_sta->hid_exist = true;
				bt_info = bt_info | 0x28;
			पूर्ण
		पूर्ण
	पूर्ण

	btc8723b2ant_update_bt_link_info(btcoexist);

	अगर (!(bt_info & BT_INFO_8723B_2ANT_B_CONNECTION)) अणु
		coex_dm->bt_status = BT_8723B_2ANT_BT_STATUS_NON_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n");
	/* connection exists but no busy */
	पूर्ण अन्यथा अगर (bt_info == BT_INFO_8723B_2ANT_B_CONNECTION) अणु
		coex_dm->bt_status = BT_8723B_2ANT_BT_STATUS_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n");
	पूर्ण अन्यथा अगर ((bt_info & BT_INFO_8723B_2ANT_B_SCO_ESCO) ||
		   (bt_info & BT_INFO_8723B_2ANT_B_SCO_BUSY)) अणु
		coex_dm->bt_status = BT_8723B_2ANT_BT_STATUS_SCO_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT SCO busy!!!\n");
	पूर्ण अन्यथा अगर (bt_info&BT_INFO_8723B_2ANT_B_ACL_BUSY) अणु
		coex_dm->bt_status = BT_8723B_2ANT_BT_STATUS_ACL_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT ACL busy!!!\n");
	पूर्ण अन्यथा अणु
		coex_dm->bt_status = BT_8723B_2ANT_BT_STATUS_MAX;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n");
	पूर्ण

	अगर ((BT_8723B_2ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) ||
	    (BT_8723B_2ANT_BT_STATUS_SCO_BUSY == coex_dm->bt_status) ||
	    (BT_8723B_2ANT_BT_STATUS_ACL_SCO_BUSY == coex_dm->bt_status)) अणु
		bt_busy = true;
		limited_dig = true;
	पूर्ण अन्यथा अणु
		bt_busy = false;
		limited_dig = false;
	पूर्ण

	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	coex_dm->limited_dig = limited_dig;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_LIMITED_DIG, &limited_dig);

	btc8723b2ant_run_coexist_mechanism(btcoexist);
पूर्ण

व्योम ex_btc8723b2ant_halt_notअगरy(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Halt notify\n");

	btc8723b2ant_wअगरioff_hwcfg(btcoexist);
	btc8723b2ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
	ex_btc8723b2ant_media_status_notअगरy(btcoexist, BTC_MEDIA_DISCONNECT);
पूर्ण

व्योम ex_btc8723b2ant_pnp_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pnp_state)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Pnp notify\n");

	अगर (pnp_state == BTC_WIFI_PNP_SLEEP) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to SLEEP\n");

		/* Driver करो not leave IPS/LPS when driver is going to sleep, so
		 * BTCoexistence think wअगरi is still under IPS/LPS
		 *
		 * BT should clear UnderIPS/UnderLPS state to aव्योम mismatch
		 * state after wakeup.
		 */
		coex_sta->under_ips = false;
		coex_sta->under_lps = false;
	पूर्ण अन्यथा अगर (pnp_state == BTC_WIFI_PNP_WAKE_UP) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to WAKE UP\n");
		ex_btc8723b2ant_init_hwconfig(btcoexist);
		btc8723b2ant_init_coex_dm(btcoexist);
		btc8723b2ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8723b2ant_periodical(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], ==========================Periodical===========================\n");

	अगर (coex_sta->dis_ver_info_cnt <= 5) अणु
		coex_sta->dis_ver_info_cnt += 1;
		अगर (coex_sta->dis_ver_info_cnt == 3) अणु
			/* Antenna config to set 0x765 = 0x0 (GNT_BT control by
			 * PTA) after initial
			 */
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Set GNT_BT control by PTA\n");
			btc8723b2ant_set_ant_path(
				btcoexist, BTC_ANT_WIFI_AT_MAIN, false, false);
		पूर्ण
	पूर्ण

	अगर (!btcoexist->स्वतः_report_2ant) अणु
		btc8723b2ant_query_bt_info(btcoexist);
	पूर्ण अन्यथा अणु
		btc8723b2ant_monitor_bt_ctr(btcoexist);
		btc8723b2ant_monitor_wअगरi_ctr(btcoexist);

		/* क्रम some BT speakers that High-Priority pkts appear beक्रमe
		 * playing, this will cause HID exist
		 */
		अगर ((coex_sta->high_priority_tx +
		    coex_sta->high_priority_rx < 50) &&
		    (bt_link_info->hid_exist))
			bt_link_info->hid_exist = false;

		अगर (btc8723b2ant_is_wअगरi_status_changed(btcoexist) ||
		    coex_dm->स्वतः_tdma_adjust)
			btc8723b2ant_run_coexist_mechanism(btcoexist);
	पूर्ण
पूर्ण
