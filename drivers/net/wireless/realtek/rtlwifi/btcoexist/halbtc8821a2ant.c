<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2012  Realtek Corporation.*/

/************************************************************
 * Description:
 *
 * This file is क्रम RTL8821A Co-exist mechanism
 *
 * History
 * 2012/08/22 Cosa first check in.
 * 2012/11/14 Cosa Revise क्रम 8821A 2Ant out sourcing.
 *
 ************************************************************/

/************************************************************
 * include files
 ************************************************************/
#समावेश "halbt_precomp.h"
/************************************************************
 * Global variables, these are अटल variables
 ************************************************************/
अटल काष्ठा coex_dm_8821a_2ant glcoex_dm_8821a_2ant;
अटल काष्ठा coex_dm_8821a_2ant *coex_dm = &glcoex_dm_8821a_2ant;
अटल काष्ठा coex_sta_8821a_2ant glcoex_sta_8821a_2ant;
अटल काष्ठा coex_sta_8821a_2ant *coex_sta = &glcoex_sta_8821a_2ant;

अटल स्थिर अक्षर *स्थिर glbt_info_src_8821a_2ant[] = अणु
	"BT Info[wifi fw]",
	"BT Info[bt rsp]",
	"BT Info[bt auto report]",
पूर्ण;

अटल u32 glcoex_ver_date_8821a_2ant = 20130618;
अटल u32 glcoex_ver_8821a_2ant = 0x5050;

/************************************************************
 * local function proto type अगर needed
 *
 * local function start with btc8821a2ant_
 ************************************************************/
अटल u8 btc8821a2ant_bt_rssi_state(काष्ठा btc_coexist *btcoexist,
				     u8 level_num, u8 rssi_thresh,
				     u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	दीर्घ bt_rssi = 0;
	u8 bt_rssi_state = coex_sta->pre_bt_rssi_state;

	bt_rssi = coex_sta->bt_rssi;

	अगर (level_num == 2) अणु
		अगर ((coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (bt_rssi >=
			    rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT) अणु
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
			अगर (bt_rssi >=
			    (rssi_thresh +
			     BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) अणु
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
			अगर (bt_rssi >=
			    (rssi_thresh1 +
			     BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) अणु
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

अटल u8 btc8821a2ant_wअगरi_rssi_state(काष्ठा btc_coexist *btcoexist,
				       u8 index, u8 level_num,
				       u8 rssi_thresh, u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	दीर्घ wअगरi_rssi = 0;
	u8 wअगरi_rssi_state = coex_sta->pre_wअगरi_rssi_state[index];

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);

	अगर (level_num == 2) अणु
		अगर ((coex_sta->pre_wअगरi_rssi_state[index] ==
		     BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wअगरi_rssi_state[index] ==
		     BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (wअगरi_rssi >=
			    (rssi_thresh+BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) अणु
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
			अगर (wअगरi_rssi >=
			    (rssi_thresh +
			     BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) अणु
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
			अगर (wअगरi_rssi >= (rssi_thresh1 +
			    BTC_RSSI_COEX_THRESH_TOL_8821A_2ANT)) अणु
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
व्योम btc8821a2ant_limited_rx(काष्ठा btc_coexist *btcoexist, bool क्रमce_exec,
			     bool rej_ap_agg_pkt, bool bt_ctrl_agg_buf_size,
			     u8 agg_buf_size)
अणु
	bool reject_rx_agg = rej_ap_agg_pkt;
	bool bt_ctrl_rx_agg_size = bt_ctrl_agg_buf_size;
	u8 rx_agg_size = agg_buf_size;

	/* Rx Aggregation related setting */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_TO_REJ_AP_AGG_PKT,
			   &reject_rx_agg);
	/* decide BT control aggregation buf size or not */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE,
			   &bt_ctrl_rx_agg_size);
	/* aggregation buf size, works when BT control Rx aggregation size */
	btcoexist->btc_set(btcoexist, BTC_SET_U1_AGG_BUF_SIZE, &rx_agg_size);
	/* real update aggregation setting */
	btcoexist->btc_set(btcoexist, BTC_SET_ACT_AGGREGATE_CTRL, शून्य);
पूर्ण

अटल व्योम btc8821a2ant_monitor_bt_ctr(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u32 reg_hp_txrx, reg_lp_txrx, u4पंचांगp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;

	reg_hp_txrx = 0x770;
	reg_lp_txrx = 0x774;

	u4पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, reg_hp_txrx);
	reg_hp_tx = u4पंचांगp & MASKLWORD;
	reg_hp_rx = (u4पंचांगp & MASKHWORD) >> 16;

	u4पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, reg_lp_txrx);
	reg_lp_tx = u4पंचांगp & MASKLWORD;
	reg_lp_rx = (u4पंचांगp & MASKHWORD) >> 16;

	coex_sta->high_priority_tx = reg_hp_tx;
	coex_sta->high_priority_rx = reg_hp_rx;
	coex_sta->low_priority_tx = reg_lp_tx;
	coex_sta->low_priority_rx = reg_lp_rx;

	अगर ((coex_sta->low_priority_rx >= 950) &&
	    (coex_sta->low_priority_rx >= coex_sta->low_priority_tx) &&
	    (!coex_sta->under_ips))
		bt_link_info->slave_role = true;
	अन्यथा
		bt_link_info->slave_role = false;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], High Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
		reg_hp_txrx, reg_hp_tx, reg_hp_tx, reg_hp_rx, reg_hp_rx);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Low Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
		reg_lp_txrx, reg_lp_tx, reg_lp_tx, reg_lp_rx, reg_lp_rx);

	/* reset counter */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0xc);
पूर्ण

अटल व्योम btc8821a2ant_monitor_wअगरi_ctr(काष्ठा btc_coexist *btcoexist)
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

अटल व्योम btc8821a2ant_query_bt_info(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	coex_sta->c2h_bt_info_req_sent = true;

	h2c_parameter[0] |= BIT0; /* trigger */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Query Bt Info, FW write 0x61 = 0x%x\n",
		h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x61, 1, h2c_parameter);
पूर्ण

अटल bool btc8821a2ant_is_wअगरi_status_changed(काष्ठा btc_coexist *btcoexist)
अणु
	अटल bool pre_wअगरi_busy = true;
	अटल bool pre_under_4way = true;
	अटल bool pre_bt_hs_on = true;
	bool wअगरi_busy = false, under_4way = false, bt_hs_on = false;
	bool wअगरi_connected = false;
	u8 wअगरi_rssi_state = BTC_RSSI_STATE_HIGH;

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

		wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 3, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);

		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_LOW))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम btc8821a2ant_update_bt_link_info(काष्ठा btc_coexist *btcoexist)
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

अटल u8 btc8821a2ant_action_algorithm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	u8 algorithm = BT_8821A_2ANT_COEX_ALGO_UNDEFINED;
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
			algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], HID only\n");
				algorithm = BT_8821A_2ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], A2DP only\n");
				algorithm = BT_8821A_2ANT_COEX_ALGO_A2DP;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], PAN(HS) only\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], PAN(EDR) only\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 2) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], SCO + HID\n");
				algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], SCO + A2DP ==> SCO\n");
				algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + PAN(HS)\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + PAN(EDR)\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], HID + A2DP\n");
				algorithm = BT_8821A_2ANT_COEX_ALGO_HID_A2DP;
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + PAN(HS)\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_HID;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + PAN(EDR)\n");
					algorithm =
					    BT_8821A_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], A2DP + PAN(HS)\n");
					algorithm =
					    BT_8821A_2ANT_COEX_ALGO_A2DP_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], A2DP + PAN(EDR)\n");
					algorithm =
					    BT_8821A_2ANT_COEX_ALGO_PANEDR_A2DP;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 3) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], SCO + HID + A2DP ==> HID\n");
				algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + PAN(HS)\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + HID + PAN(EDR)\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + A2DP + PAN(HS)\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], SCO + A2DP + PAN(EDR) ==> HID\n");
					algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
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
					    BT_8821A_2ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], HID + A2DP + PAN(EDR)\n");
					algorithm =
					BT_8821A_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
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
					algorithm = BT_8821A_2ANT_COEX_ALGO_SCO;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस algorithm;
पूर्ण

अटल व्योम btc8821a2ant_set_fw_dac_swing_lvl(काष्ठा btc_coexist *btcoexist,
					      u8 dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	/* There are several type of dacswing
	 * 0x18/ 0x10/ 0xc/ 0x8/ 0x4/ 0x6
	 */
	h2c_parameter[0] = dac_swing_lvl;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Set Dac Swing Level = 0x%x\n", dac_swing_lvl);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], FW write 0x64 = 0x%x\n", h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x64, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8821a2ant_set_fw_dec_bt_pwr(काष्ठा btc_coexist *btcoexist,
					   u8 dec_bt_pwr_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	h2c_parameter[0] = dec_bt_pwr_lvl;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], decrease Bt Power Level : %u, FW write 0x62 = 0x%x\n",
		dec_bt_pwr_lvl, h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x62, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8821a2ant_dec_bt_pwr(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u8 dec_bt_pwr_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s Dec BT power level = %u\n",
		(क्रमce_exec ? "force to" : ""), dec_bt_pwr_lvl);
	coex_dm->cur_dec_bt_pwr_lvl = dec_bt_pwr_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_dec_bt_pwr_lvl = %d, cur_dec_bt_pwr_lvl = %d\n",
			coex_dm->pre_dec_bt_pwr_lvl,
			    coex_dm->cur_dec_bt_pwr_lvl);

		अगर (coex_dm->pre_dec_bt_pwr_lvl == coex_dm->cur_dec_bt_pwr_lvl)
			वापस;
	पूर्ण
	btc8821a2ant_set_fw_dec_bt_pwr(btcoexist, coex_dm->cur_dec_bt_pwr_lvl);

	coex_dm->pre_dec_bt_pwr_lvl = coex_dm->cur_dec_bt_pwr_lvl;
पूर्ण

अटल व्योम btc8821a2ant_fw_dac_swing_lvl(काष्ठा btc_coexist *btcoexist,
					  bool क्रमce_exec, u8 fw_dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s set FW Dac Swing level = %d\n",
		(क्रमce_exec ? "force to" : ""), fw_dac_swing_lvl);
	coex_dm->cur_fw_dac_swing_lvl = fw_dac_swing_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_fw_dac_swing_lvl = %d, cur_fw_dac_swing_lvl = %d\n",
			coex_dm->pre_fw_dac_swing_lvl,
			coex_dm->cur_fw_dac_swing_lvl);

		अगर (coex_dm->pre_fw_dac_swing_lvl ==
		    coex_dm->cur_fw_dac_swing_lvl)
			वापस;
	पूर्ण

	btc8821a2ant_set_fw_dac_swing_lvl(btcoexist,
					  coex_dm->cur_fw_dac_swing_lvl);

	coex_dm->pre_fw_dac_swing_lvl = coex_dm->cur_fw_dac_swing_lvl;
पूर्ण

अटल व्योम btc8821a2ant_set_sw_penalty_tx_rate_adaptive(
		काष्ठा btc_coexist *btcoexist, bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[6] = अणु0पूर्ण;

	h2c_parameter[0] = 0x6;	/* opCode, 0x6 = Retry_Penalty */

	अगर (low_penalty_ra) अणु
		h2c_parameter[1] |= BIT0;
		/* normal rate except MCS7/6/5, OFDM54/48/36 */
		h2c_parameter[2] = 0x00;
		/* MCS7 or OFDM54 */
		h2c_parameter[3] = 0xf5;
		/* MCS6 or OFDM48 */
		h2c_parameter[4] = 0xa0;
		/* MCS5 or OFDM36 */
		h2c_parameter[5] = 0xa0;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set WiFi Low-Penalty Retry: %s",
		(low_penalty_ra ? "ON!!" : "OFF!!"));

	btcoexist->btc_fill_h2c(btcoexist, 0x69, 6, h2c_parameter);
पूर्ण

अटल व्योम btc8821a2ant_low_penalty_ra(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn LowPenaltyRA = %s\n",
		(क्रमce_exec ? "force to" : ""),
		((low_penalty_ra) ? "ON" : "OFF"));
	coex_dm->cur_low_penalty_ra = low_penalty_ra;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_low_penalty_ra = %d, cur_low_penalty_ra = %d\n",
			coex_dm->pre_low_penalty_ra,
			coex_dm->cur_low_penalty_ra);

		अगर (coex_dm->pre_low_penalty_ra == coex_dm->cur_low_penalty_ra)
			वापस;
	पूर्ण
	btc8821a2ant_set_sw_penalty_tx_rate_adaptive(btcoexist,
					 coex_dm->cur_low_penalty_ra);

	coex_dm->pre_low_penalty_ra = coex_dm->cur_low_penalty_ra;
पूर्ण

अटल व्योम btc8821a2ant_set_dac_swing_reg(काष्ठा btc_coexist *btcoexist,
					   u32 level)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 val = (u8)level;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Write SwDacSwing = 0x%x\n", level);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xc5b, 0x3e, val);
पूर्ण

अटल व्योम btc8821a2ant_set_sw_full_dac_swing(काष्ठा btc_coexist *btcoexist,
					       bool sw_dac_swing_on,
					       u32 sw_dac_swing_lvl)
अणु
	अगर (sw_dac_swing_on)
		btc8821a2ant_set_dac_swing_reg(btcoexist, sw_dac_swing_lvl);
	अन्यथा
		btc8821a2ant_set_dac_swing_reg(btcoexist, 0x18);
पूर्ण

अटल व्योम btc8821a2ant_dac_swing(काष्ठा btc_coexist *btcoexist,
				   bool क्रमce_exec, bool dac_swing_on,
				   u32 dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn DacSwing = %s, dac_swing_lvl = 0x%x\n",
		(क्रमce_exec ? "force to" : ""),
		((dac_swing_on) ? "ON" : "OFF"),
		dac_swing_lvl);
	coex_dm->cur_dac_swing_on = dac_swing_on;
	coex_dm->cur_dac_swing_lvl = dac_swing_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_dac_swing_on = %d, pre_dac_swing_lvl = 0x%x, cur_dac_swing_on = %d, cur_dac_swing_lvl = 0x%x\n",
			coex_dm->pre_dac_swing_on,
			coex_dm->pre_dac_swing_lvl,
			coex_dm->cur_dac_swing_on,
			coex_dm->cur_dac_swing_lvl);

		अगर ((coex_dm->pre_dac_swing_on == coex_dm->cur_dac_swing_on) &&
		    (coex_dm->pre_dac_swing_lvl ==
		     coex_dm->cur_dac_swing_lvl))
			वापस;
	पूर्ण
	mdelay(30);
	btc8821a2ant_set_sw_full_dac_swing(btcoexist, dac_swing_on,
					   dac_swing_lvl);

	coex_dm->pre_dac_swing_on = coex_dm->cur_dac_swing_on;
	coex_dm->pre_dac_swing_lvl = coex_dm->cur_dac_swing_lvl;
पूर्ण

अटल व्योम btc8821a2ant_set_coex_table(काष्ठा btc_coexist *btcoexist,
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

अटल व्योम btc8821a2ant_coex_table(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u32 val0x6c0,
				    u32 val0x6c4, u32 val0x6c8, u8 val0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s write Coex Table 0x6c0 = 0x%x, 0x6c4 = 0x%x, 0x6c8 = 0x%x, 0x6cc = 0x%x\n",
		(क्रमce_exec ? "force to" : ""),
		val0x6c0, val0x6c4, val0x6c8, val0x6cc);
	coex_dm->cur_val0x6c0 = val0x6c0;
	coex_dm->cur_val0x6c4 = val0x6c4;
	coex_dm->cur_val0x6c8 = val0x6c8;
	coex_dm->cur_val0x6cc = val0x6cc;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_val0x6c0 = 0x%x, pre_val0x6c4 = 0x%x, pre_val0x6c8 = 0x%x, pre_val0x6cc = 0x%x !!\n",
			coex_dm->pre_val0x6c0,
			coex_dm->pre_val0x6c4,
			coex_dm->pre_val0x6c8,
			coex_dm->pre_val0x6cc);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], cur_val0x6c0 = 0x%x, cur_val0x6c4 = 0x%x, cur_val0x6c8 = 0x%x, cur_val0x6cc = 0x%x !!\n",
			coex_dm->cur_val0x6c0,
			coex_dm->cur_val0x6c4,
			coex_dm->cur_val0x6c8,
			coex_dm->cur_val0x6cc);

		अगर ((coex_dm->pre_val0x6c0 == coex_dm->cur_val0x6c0) &&
		    (coex_dm->pre_val0x6c4 == coex_dm->cur_val0x6c4) &&
		    (coex_dm->pre_val0x6c8 == coex_dm->cur_val0x6c8) &&
		    (coex_dm->pre_val0x6cc == coex_dm->cur_val0x6cc))
			वापस;
	पूर्ण
	btc8821a2ant_set_coex_table(btcoexist, val0x6c0, val0x6c4, val0x6c8,
				    val0x6cc);

	coex_dm->pre_val0x6c0 = coex_dm->cur_val0x6c0;
	coex_dm->pre_val0x6c4 = coex_dm->cur_val0x6c4;
	coex_dm->pre_val0x6c8 = coex_dm->cur_val0x6c8;
	coex_dm->pre_val0x6cc = coex_dm->cur_val0x6cc;
पूर्ण

अटल व्योम btc8821a2ant_coex_table_with_type(काष्ठा btc_coexist *btcoexist,
					      bool क्रमce_exec, u8 type)
अणु
	coex_sta->coex_table_type = type;

	चयन (type) अणु
	हाल 0:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x55555555, 0xffffff, 0x3);
		अवरोध;
	हाल 1:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x5afa5afa, 0xffffff, 0x3);
		अवरोध;
	हाल 2:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x5ada5ada,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 3:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0xaaaaaaaa,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 4:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0xffffffff,
					0xffffffff, 0xffffff, 0x3);
		अवरोध;
	हाल 5:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					0x5fff5fff, 0xffffff, 0x3);
		अवरोध;
	हाल 6:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55ff55ff,
					0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 7:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 8:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 9:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 10:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 11:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 12:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 13:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 14:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x5fff5fff,
					0x5ada5ada, 0xffffff, 0x3);
		अवरोध;
	हाल 15:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x55dd55dd,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 16:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0x5fdf5fdf,
					0x5fdb5fdb, 0xffffff, 0x3);
		अवरोध;
	हाल 17:
		btc8821a2ant_coex_table(btcoexist, क्रमce_exec, 0xfafafafa,
					0xfafafafa, 0xffffff, 0x3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_set_fw_ignore_wlan_act(काष्ठा btc_coexist *btcoex,
						bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoex->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	अगर (enable)
		h2c_parameter[0] |= BIT0; /* function enable */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set FW for BT Ignore Wlan_Act, FW write 0x63 = 0x%x\n",
		h2c_parameter[0]);

	btcoex->btc_fill_h2c(btcoex, 0x63, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8821a2ant_set_lps_rpwm(काष्ठा btc_coexist *btcoexist, u8 lps_val,
				      u8 rpwm_val)
अणु
	u8 lps = lps_val;
	u8 rpwm = rpwm_val;

	btcoexist->btc_set(btcoexist, BTC_SET_U1_LPS_VAL, &lps);
	btcoexist->btc_set(btcoexist, BTC_SET_U1_RPWM_VAL, &rpwm);
पूर्ण

अटल व्योम btc8821a2ant_lps_rpwm(काष्ठा btc_coexist *btcoexist,
				  bool क्रमce_exec, u8 lps_val, u8 rpwm_val)
अणु
	coex_dm->cur_lps = lps_val;
	coex_dm->cur_rpwm = rpwm_val;

	अगर (!क्रमce_exec) अणु
		अगर ((coex_dm->pre_lps == coex_dm->cur_lps) &&
		    (coex_dm->pre_rpwm == coex_dm->cur_rpwm))
			वापस;
	पूर्ण
	btc8821a2ant_set_lps_rpwm(btcoexist, lps_val, rpwm_val);

	coex_dm->pre_lps = coex_dm->cur_lps;
	coex_dm->pre_rpwm = coex_dm->cur_rpwm;
पूर्ण

अटल व्योम btc8821a2ant_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
					 bool क्रमce_exec, bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn Ignore WlanAct %s\n",
		(क्रमce_exec ? "force to" : ""), (enable ? "ON" : "OFF"));
	coex_dm->cur_ignore_wlan_act = enable;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_ignore_wlan_act = %d, cur_ignore_wlan_act = %d!!\n",
			coex_dm->pre_ignore_wlan_act,
			 coex_dm->cur_ignore_wlan_act);

		अगर (coex_dm->pre_ignore_wlan_act ==
		    coex_dm->cur_ignore_wlan_act)
			वापस;
	पूर्ण
	btc8821a2ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
पूर्ण

अटल व्योम btc8821a2ant_set_fw_ps_tdma(काष्ठा btc_coexist *btcoexist,
					u8 byte1, u8 byte2, u8 byte3,
					u8 byte4, u8 byte5)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[5];

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
		"[BTCoex], FW write 0x60(5bytes) = 0x%x%08x\n",
		h2c_parameter[0],
		h2c_parameter[1] << 24 |
		h2c_parameter[2] << 16 |
		h2c_parameter[3] << 8 |
		h2c_parameter[4]);

	btcoexist->btc_fill_h2c(btcoexist, 0x60, 5, h2c_parameter);
पूर्ण

अटल व्योम btc8821a2ant_sw_mechanism1(काष्ठा btc_coexist *btcoexist,
				       bool shrink_rx_lpf, bool low_penalty_ra,
				       bool limited_dig, bool bt_lna_स्थिरrain)
अणु
	btc8821a2ant_low_penalty_ra(btcoexist, NORMAL_EXEC, low_penalty_ra);
पूर्ण

अटल व्योम btc8821a2ant_sw_mechanism2(काष्ठा btc_coexist *btcoexist,
				       bool agc_table_shअगरt, bool adc_back_off,
				       bool sw_dac_swing, u32 dac_swing_lvl)
अणु
	btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, sw_dac_swing,
			       dac_swing_lvl);
पूर्ण

अटल व्योम btc8821a2ant_set_ant_path(काष्ठा btc_coexist *btcoexist,
				      u8 ant_pos_type, bool init_hw_cfg,
				      bool wअगरi_off)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u32 u4पंचांगp = 0;
	u8 h2c_parameter[2] = अणु0पूर्ण;

	अगर (init_hw_cfg) अणु
		/*  0x4c[23] = 0, 0x4c[24] = 1  Antenna control by WL/BT */
		u4पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
		u4पंचांगp &= ~BIT23;
		u4पंचांगp |= BIT24;
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u4पंचांगp);

		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x974, 0x3ff);

		अगर (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT) अणु
			/* tell firmware "antenna inverse"  ==> WRONG firmware
			 * antenna control code ==>need fw to fix
			 */
			h2c_parameter[0] = 1;
			h2c_parameter[1] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
						h2c_parameter);
		पूर्ण अन्यथा अणु
			/* tell firmware "no antenna inverse" ==> WRONG firmware
			 * antenna control code ==>need fw to fix
			 */
			h2c_parameter[0] = 0;
			h2c_parameter[1] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
						h2c_parameter);
		पूर्ण
	पूर्ण

	/* ext चयन setting */
	चयन (ant_pos_type) अणु
	हाल BTC_ANT_WIFI_AT_MAIN:
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7, 0x30, 0x1);
		अवरोध;
	हाल BTC_ANT_WIFI_AT_AUX:
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7, 0x30, 0x2);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_ps_tdma(काष्ठा btc_coexist *btcoexist,
				 bool क्रमce_exec, bool turn_on, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	u8 wअगरi_rssi_state, bt_rssi_state;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist, 2,
				BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	अगर (!(BTC_RSSI_HIGH(wअगरi_rssi_state) &&
	      BTC_RSSI_HIGH(bt_rssi_state)) &&
	    turn_on) अणु
		/* क्रम WiFi RSSI low or BT RSSI low */
		type = type + 100;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn %s PS TDMA, type = %d\n",
		(क्रमce_exec ? "force to" : ""), (turn_on ? "ON" : "OFF"),
		type);
	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_ps_tdma_on = %d, cur_ps_tdma_on = %d!!\n",
			coex_dm->pre_ps_tdma_on, coex_dm->cur_ps_tdma_on);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], pre_ps_tdma = %d, cur_ps_tdma = %d!!\n",
			coex_dm->pre_ps_tdma, coex_dm->cur_ps_tdma);

		अगर ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			वापस;
	पूर्ण
	अगर (turn_on) अणु
		चयन (type) अणु
		हाल 1:
		शेष:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 2:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 3:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x90);
			अवरोध;
		हाल 4:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 5:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 6:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 7:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 8:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x10,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 9:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 10:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 11:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x90);
			अवरोध;
		हाल 12:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1, 0x90);
			अवरोध;
		हाल 13:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 14:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x2d,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 15:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 16:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 17:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x2f,
						    0x2f, 0x60, 0x90);
			अवरोध;
		हाल 18:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x5, 0x5,
						    0xe1, 0x90);
			अवरोध;
		हाल 19:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0xe1, 0x90);
			अवरोध;
		हाल 20:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0x60, 0x90);
			अवरोध;
		हाल 21:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			अवरोध;
		हाल 23:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1e,
						    0x03, 0xf0, 0x14);
			अवरोध;
		हाल 24:
		हाल 124:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x3c,
						    0x03, 0x70, 0x50);
			अवरोध;
		हाल 25:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x14,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 26:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x30,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 71:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 101:
		हाल 105:
		हाल 171:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x3a,
						    0x03, 0x70, 0x50);
			अवरोध;
		हाल 102:
		हाल 106:
		हाल 110:
		हाल 114:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x2d,
						    0x03, 0x70, 0x50);
			अवरोध;
		हाल 103:
		हाल 107:
		हाल 111:
		हाल 115:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1c,
						    0x03, 0x70, 0x50);
			अवरोध;
		हाल 104:
		हाल 108:
		हाल 112:
		हाल 116:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x10,
						    0x03, 0x70, 0x50);
			अवरोध;
		हाल 109:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0xf1, 0x90);
			अवरोध;
		हाल 113:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x3c,
						    0x03, 0x70, 0x90);
			अवरोध;
		हाल 121:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			अवरोध;
		हाल 22:
		हाल 122:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x35,
						    0x03, 0x71, 0x11);
			अवरोध;
		हाल 123:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1c,
						    0x03, 0x70, 0x54);
			अवरोध;
		हाल 125:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x14,
						    0x03, 0x70, 0x50);
			अवरोध;
		हाल 126:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x30,
						    0x03, 0x70, 0x50);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable PS tdma */
		चयन (type) अणु
		हाल 0:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			अवरोध;
		हाल 1:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x48, 0x0);
			अवरोध;
		शेष:
			btc8821a2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x40, 0x0);
			अवरोध;
		पूर्ण
	पूर्ण

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
पूर्ण

अटल व्योम
btc8821a2ant_ps_tdma_check_क्रम_घातer_save_state(काष्ठा btc_coexist *btcoexist,
						bool new_ps_state)
अणु
	u8 lps_mode = 0x0;

	btcoexist->btc_get(btcoexist, BTC_GET_U1_LPS_MODE, &lps_mode);

	अगर (lps_mode) अणु
		/* alपढ़ोy under LPS state */
		अगर (new_ps_state) अणु
			/* keep state under LPS, करो nothing */
		पूर्ण अन्यथा अणु
			/* will leave LPS state, turn off psTdma first */
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* NO PS state */
		अगर (new_ps_state) अणु
			/* will enter LPS state, turn off psTdma first */
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		पूर्ण अन्यथा अणु
			/* keep state under NO PS state, करो nothing */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_घातer_save_state(काष्ठा btc_coexist *btcoexist,
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
		btc8821a2ant_ps_tdma_check_क्रम_घातer_save_state(btcoexist,
								true);
		btc8821a2ant_lps_rpwm(btcoexist, NORMAL_EXEC, lps_val,
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
		btc8821a2ant_ps_tdma_check_क्रम_घातer_save_state(btcoexist,
								false);
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_LEAVE_LPS, शून्य);
		coex_sta->क्रमce_lps_on = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_coex_all_off(काष्ठा btc_coexist *btcoexist)
अणु
	/* fw all off */
	btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	/* sw all off */
	btc8821a2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8821a2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);

	/* hw all off */
	btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम btc8821a2ant_coex_under_5g(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a2ant_coex_all_off(btcoexist);
	btc8821a2ant_ignore_wlan_act(btcoexist, NORMAL_EXEC, true);
पूर्ण

अटल व्योम btc8821a2ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	/* क्रमce to reset coex mechanism */
	btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8821a2ant_ps_tdma(btcoexist, FORCE_EXEC, false, 1);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 6);
	btc8821a2ant_dec_bt_pwr(btcoexist, FORCE_EXEC, 0);

	btc8821a2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8821a2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);
पूर्ण

अटल व्योम btc8821a2ant_action_bt_inquiry(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_connected = false;
	bool low_pwr_disable = true;
	bool scan = false, link = false, roam = false;

	btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	btc8821a2ant_bt_rssi_state(btcoexist,
				2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
			   &low_pwr_disable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	अगर (scan || link || roam) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi link process + BT Inq/Page!!\n");
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
	पूर्ण अन्यथा अगर (wअगरi_connected) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi connected + BT Inq/Page!!\n");
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi no-link + BT Inq/Page!!\n");
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
	पूर्ण

	btc8821a2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 6);
	btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btc8821a2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8821a2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);
पूर्ण

अटल व्योम btc8821a2ant_action_wअगरi_link_process(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 u8पंचांगpa, u8पंचांगpb;

	btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 15);
	btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);

	btc8821a2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8821a2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);

	u8पंचांगpa = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x765);
	u8पंचांगpb = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x76e);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], 0x765=0x%x, 0x76e=0x%x\n", u8पंचांगpa, u8पंचांगpb);
पूर्ण

अटल bool btc8821a2ant_action_wअगरi_idle_process(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 wअगरi_rssi_state1;
	u8 ap_num = 0;

	btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
			BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES - 20, 0);
	btc8821a2ant_bt_rssi_state(btcoexist,
				2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM, &ap_num);

	/* define the office environment */
	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && (coex_sta->hid_exist) &&
	    (coex_sta->a2dp_exist)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi  idle process for BT HID+A2DP exist!!\n");

		btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x6);
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		/* sw all off */
		btc8821a2ant_sw_mechanism1(btcoexist, false, false, false,
					   false);
		btc8821a2ant_sw_mechanism2(btcoexist, false, false, false,
					   0x18);

		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

		वापस true;
	पूर्ण अन्यथा अगर (coex_sta->pan_exist) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi  idle process for BT PAN exist!!\n");

		btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x6);
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		/* sw all off */
		btc8821a2ant_sw_mechanism1(btcoexist, false, false, false,
					   false);
		btc8821a2ant_sw_mechanism2(btcoexist, false, false, false,
					   0x18);

		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

		वापस true;
	पूर्ण
	btc8821a2ant_dac_swing(btcoexist, NORMAL_EXEC, true, 0x18);
	वापस false;
पूर्ण

अटल bool btc8821a2ant_is_common_action(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool common = false, wअगरi_connected = false, wअगरi_busy = false;
	bool low_pwr_disable = false;
	bool bt_hs_on = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);

	अगर (!wअगरi_connected) अणु
		low_pwr_disable = false;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false,
					0x8);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi non-connected idle!!\n");

		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x0);
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		btc8821a2ant_sw_mechanism1(btcoexist, false, false, false,
					   false);
		btc8821a2ant_sw_mechanism2(btcoexist, false, false, false,
					   0x18);

		common = true;
	पूर्ण अन्यथा अणु
		अगर (BT_8821A_2ANT_BT_STATUS_IDLE ==
		    coex_dm->bt_status) अणु
			low_pwr_disable = false;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);
			btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC,
						false, false, 0x8);

			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Wifi connected + BT non connected-idle!!\n");

			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x0);
			btc8821a2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 0);

			btc8821a2ant_घातer_save_state(
				btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
			btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      0xb);
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);

			common = true;
		पूर्ण अन्यथा अगर (BT_8821A_2ANT_BT_STATUS_CON_IDLE ==
			   coex_dm->bt_status) अणु
			low_pwr_disable = true;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			अगर (bt_hs_on)
				वापस false;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Wifi connected + BT connected-idle!!\n");
			btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC,
						false, false, 0x8);

			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1,
						  0xfffff, 0x0);
			btc8821a2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 0);

			btc8821a2ant_घातer_save_state(
				btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
			btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC,
						      0xb);
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
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
				    btc8821a2ant_action_wअगरi_idle_process(
					     btcoexist);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस common;
पूर्ण

अटल व्योम btc8821a2ant_tdma_duration_adjust(काष्ठा btc_coexist *btcoexist,
					      bool sco_hid, bool tx_छोड़ो,
					      u8 max_पूर्णांकerval)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल दीर्घ up, dn, m, n, रुको_count;
	 /* 0 : no change
	  * +1: increase WiFi duration
	  * -1: decrease WiFi duration
	  */
	पूर्णांक result;
	u8 retry_count = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], TdmaDurationAdjust()\n");

	अगर (coex_dm->स्वतः_tdma_adjust) अणु
		coex_dm->स्वतः_tdma_adjust = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], first run TdmaDurationAdjust()!!\n");
		अगर (sco_hid) अणु
			अगर (tx_छोड़ो) अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 13);
					coex_dm->ps_tdma_du_adj_type = 13;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 9);
					coex_dm->ps_tdma_du_adj_type = 9;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tx_छोड़ो) अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 1);
					coex_dm->ps_tdma_du_adj_type = 1;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 3) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 3);
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
		/* accquire the BT TRx retry count from BT_Info byte2 */
		retry_count = coex_sta->bt_retry_cnt;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], retry_count = %d\n", retry_count);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], up = %d, dn = %d, m = %d, n = %d, wait_count = %d\n",
			(पूर्णांक)up, (पूर्णांक)dn, (पूर्णांक)m, (पूर्णांक)n, (पूर्णांक)रुको_count);
		result = 0;
		रुको_count++;

		अगर (retry_count == 0) अणु
			/* no retry in the last 2-second duration */
			up++;
			dn--;

			अगर (dn <= 0)
				dn = 0;

			अगर (up >= n) अणु
				/* अगर (retry count == 0) क्रम 2*n seconds,
				 * make WiFi duration wider
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
				/* अगर retry count < 3 क्रम 2*2 seconds,
				 * shrink wअगरi duration
				 */
				अगर (रुको_count <= 2)
					m++; /* aव्योम bounce in two levels */
				अन्यथा
					m = 1;
				/* m max value is 20, max समय is 120 second,
				 * recheck अगर adjust WiFi duration.
				 */
				अगर (m >= 20)
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
			/* retry count > 3, अगर retry count > 3 happens once,
			 * shrink WiFi duration
			 */
			अगर (रुको_count == 1)
				m++; /* aव्योम bounce in two levels */
			अन्यथा
				m = 1;
			/* m max value is 20, max समय is 120 second,
			 * recheck अगर adjust WiFi duration.
			 */
			अगर (m >= 20)
				m = 20;

			n = 3 * m;
			up = 0;
			dn = 0;
			रुको_count = 0;
			result = -1;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Decrease wifi duration for retryCounter>3!!\n");
		पूर्ण

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], max Interval = %d\n", max_पूर्णांकerval);

		अगर (max_पूर्णांकerval == 1) अणु
			अगर (tx_छोड़ो) अणु
				अगर (coex_dm->cur_ps_tdma == 71) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 1) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 5);
					coex_dm->ps_tdma_du_adj_type = 5;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 4) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 9) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 13);
					coex_dm->ps_tdma_du_adj_type = 13;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				पूर्ण

				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 5) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 13) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 8) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 5);
						coex_dm->ps_tdma_du_adj_type =
							5;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 13);
						coex_dm->ps_tdma_du_adj_type =
							13;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (coex_dm->cur_ps_tdma == 5) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 71);
					coex_dm->ps_tdma_du_adj_type = 71;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 8) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 13) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 9);
					coex_dm->ps_tdma_du_adj_type = 9;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				पूर्ण

				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 71) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 1);
						coex_dm->ps_tdma_du_adj_type =
							1;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 4) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 1);
						coex_dm->ps_tdma_du_adj_type =
							1;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 71);
						coex_dm->ps_tdma_du_adj_type =
							71;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8821a2ant_ps_tdma(
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
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 6);
					coex_dm->ps_tdma_du_adj_type = 6;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 4) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 9) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 14);
					coex_dm->ps_tdma_du_adj_type = 14;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 5) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 13) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 8) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 6);
						coex_dm->ps_tdma_du_adj_type =
							6;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 14);
						coex_dm->ps_tdma_du_adj_type =
							14;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (coex_dm->cur_ps_tdma == 5) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 2);
					coex_dm->ps_tdma_du_adj_type = 2;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 8) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 13) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 10);
					coex_dm->ps_tdma_du_adj_type = 10;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 4) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 2);
						coex_dm->ps_tdma_du_adj_type =
							2;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 10);
						coex_dm->ps_tdma_du_adj_type =
							10;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8821a2ant_ps_tdma(
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
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 7);
					coex_dm->ps_tdma_du_adj_type = 7;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 4) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 8);
					coex_dm->ps_tdma_du_adj_type = 8;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 9) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 15);
					coex_dm->ps_tdma_du_adj_type = 15;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 16);
					coex_dm->ps_tdma_du_adj_type = 16;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 5) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 8);
						coex_dm->ps_tdma_du_adj_type =
							8;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 13) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 16);
						coex_dm->ps_tdma_du_adj_type =
							16;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 8) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 7);
						coex_dm->ps_tdma_du_adj_type =
							7;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 15);
						coex_dm->ps_tdma_du_adj_type =
							15;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (coex_dm->cur_ps_tdma == 5) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 6) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 7) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 3);
					coex_dm->ps_tdma_du_adj_type = 3;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 8) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 4);
					coex_dm->ps_tdma_du_adj_type = 4;
				पूर्ण
				अगर (coex_dm->cur_ps_tdma == 13) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 14) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 15) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 11);
					coex_dm->ps_tdma_du_adj_type = 11;
				पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 16) अणु
					btc8821a2ant_ps_tdma(btcoexist,
							NORMAL_EXEC, true, 12);
					coex_dm->ps_tdma_du_adj_type = 12;
				पूर्ण
				अगर (result == -1) अणु
					अगर (coex_dm->cur_ps_tdma == 1) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 4);
						coex_dm->ps_tdma_du_adj_type =
							4;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 9) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 12);
						coex_dm->ps_tdma_du_adj_type =
							12;
					पूर्ण
				पूर्ण अन्यथा अगर (result == 1) अणु
					अगर (coex_dm->cur_ps_tdma == 4) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 3) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 2) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 3);
						coex_dm->ps_tdma_du_adj_type =
							3;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 12) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 11) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण अन्यथा अगर (coex_dm->cur_ps_tdma == 10) अणु
						btc8821a2ant_ps_tdma(
							btcoexist, NORMAL_EXEC,
							true, 11);
						coex_dm->ps_tdma_du_adj_type =
							11;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* अगर current PsTdma not match with the recorded one
	 * (when scan, dhcp...), then we have to adjust it back to
	 * the previous recorded one.
	 */
	अगर (coex_dm->cur_ps_tdma != coex_dm->ps_tdma_du_adj_type) अणु
		bool scan = false, link = false, roam = false;

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], PsTdma type mismatch!!!, cur_ps_tdma = %d, recordPsTdma = %d\n",
			coex_dm->cur_ps_tdma, coex_dm->ps_tdma_du_adj_type);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

		अगर (!scan && !link && !roam) अणु
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true,
					     coex_dm->ps_tdma_du_adj_type);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], roaming/link/scan is under progress, will adjust next time!!!\n");
		पूर्ण
	पूर्ण
पूर्ण

/* SCO only or SCO+PAN(HS)*/
अटल व्योम btc8821a2ant_action_sco(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u8 wअगरi_rssi_state, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist, 2, 35, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 4);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, true);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, false);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर (wअगरi_bw == BTC_WIFI_BW_LEGACY) अणु
		/* क्रम SCO quality at 11b/g mode */
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण अन्यथा अणु
		/* क्रम SCO quality & wअगरi perक्रमmance balance at 11n mode */
		अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
			btc8821a2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 8);
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->sco_only)
				btc8821a2ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 17);
			अन्यथा
				btc8821a2ant_coex_table_with_type(
					btcoexist, NORMAL_EXEC, 12);
		पूर्ण
	पूर्ण

	btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	/* क्रम voice quality */
	btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);

	/* sw mechanism */
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   true, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   true, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   true, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   true, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_action_hid(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
		2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, true);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, false);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर (wअगरi_bw == BTC_WIFI_BW_LEGACY) अणु
		/* क्रम HID at 11b/g mode */
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	पूर्ण अन्यथा अणु
		/* क्रम HID quality & wअगरi perक्रमmance balance at 11n mode */
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण

	btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 24);

	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		/* sw mechanism */
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* sw mechanism */
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* A2DP only / PAN(EDR) only/ A2DP+PAN(HS) */
अटल व्योम btc8821a2ant_action_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, wअगरi_rssi_state1, bt_rssi_state;
	u8 ap_num = 0;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
		2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	अगर ((ap_num >= 10) && BTC_RSSI_HIGH(wअगरi_rssi_state1) &&
	    BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);

		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff,
					  0x0);
		btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false,
					0x8);
		btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);

		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 23);

		/* sw mechanism */
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
		अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   true, 0x6);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   true, 0x6);
		पूर्ण
		वापस;
	पूर्ण

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);
	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 13);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 23);
	पूर्ण अन्यथा अणु
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 23);
	पूर्ण

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_action_a2dp_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
		2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 13);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	btc8821a2ant_tdma_duration_adjust(btcoexist, false, true, 2);

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_action_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
				2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, true);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, false);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 10);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 13);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH))
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 26);
	अन्यथा
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 26);

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* PAN(HS) only */
अटल व्योम btc8821a2ant_action_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
				2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* PAN(EDR)+A2DP */
अटल व्योम btc8821a2ant_action_pan_edr_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
				2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	अन्यथा
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 12);

		अगर (wअगरi_bw == BTC_WIFI_BW_HT40)
			btc8821a2ant_tdma_duration_adjust(btcoexist, false,
							  true, 3);
		अन्यथा
			btc8821a2ant_tdma_duration_adjust(btcoexist, false,
							  false, 3);
	पूर्ण अन्यथा अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 13);
		btc8821a2ant_tdma_duration_adjust(btcoexist, false, true, 3);
	पूर्ण

	/* sw mechanism	 */
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_action_pan_edr_hid(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
				2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, true);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, false);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर (wअगरi_bw == BTC_WIFI_BW_LEGACY) अणु
		/* क्रम HID at 11b/g mode */
		btc8821a2ant_coex_table(btcoexist, NORMAL_EXEC, 0x55ff55ff,
					0x5a5f5a5f, 0xffff, 0x3);
	पूर्ण अन्यथा अणु
		/* क्रम HID quality & wअगरi perक्रमmance balance at 11n mode */
		btc8821a2ant_coex_table(btcoexist, NORMAL_EXEC, 0x55ff55ff,
					0x5a5f5a5f, 0xffff, 0x3);
	पूर्ण

	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 3);
		/* fw mechanism */
		अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     true, 10);
		पूर्ण अन्यथा अणु
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
		पूर्ण

		/* sw mechanism */
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		/* fw mechanism */
		अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 10);
		पूर्ण अन्यथा अणु
			btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
		पूर्ण

		/* sw mechanism */
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* HID+A2DP+PAN(EDR) */
अटल व्योम btc8821a2ant_act_hid_a2dp_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, wअगरi_rssi_state1, bt_rssi_state;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	wअगरi_rssi_state1 = btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
				2, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 0);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (BTC_RSSI_HIGH(bt_rssi_state))
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	अन्यथा
		btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	अगर (BTC_RSSI_HIGH(wअगरi_rssi_state1) && BTC_RSSI_HIGH(bt_rssi_state)) अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 14);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		अगर (wअगरi_bw == BTC_WIFI_BW_HT40)
			btc8821a2ant_tdma_duration_adjust(btcoexist, true,
							  true, 3);
		अन्यथा
			btc8821a2ant_tdma_duration_adjust(btcoexist, true,
							  false, 3);
	पूर्ण अन्यथा अणु
		btc8821a2ant_tdma_duration_adjust(btcoexist, true, true, 3);
	पूर्ण

	/* sw mechanism */
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_action_hid_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u32 wअगरi_bw;
	u8 wअगरi_rssi_state, bt_rssi_state;
	u8 ap_num = 0;

	wअगरi_rssi_state = btc8821a2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	btc8821a2ant_wअगरi_rssi_state(btcoexist, 1, 2,
				BT_8821A_2ANT_WIFI_RSSI_COEXSWITCH_THRES, 0);
	bt_rssi_state = btc8821a2ant_bt_rssi_state(btcoexist,
				3, BT_8821A_2ANT_BT_RSSI_COEXSWITCH_THRES, 37);

	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x0);

	btc8821a2ant_limited_rx(btcoexist, NORMAL_EXEC, false, true, 0x5);
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (wअगरi_bw == BTC_WIFI_BW_LEGACY) अणु
		अगर (BTC_RSSI_HIGH(bt_rssi_state))
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		अन्यथा अगर (BTC_RSSI_MEDIUM(bt_rssi_state))
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		अन्यथा
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अणु
		/* only 802.11N mode we have to dec bt घातer to 4 degree */
		अगर (BTC_RSSI_HIGH(bt_rssi_state)) अणु
			btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM,
					   &ap_num);
			अगर (ap_num < 10)
				btc8821a2ant_dec_bt_pwr(btcoexist,
							NORMAL_EXEC, 4);
			अन्यथा
				btc8821a2ant_dec_bt_pwr(btcoexist,
							NORMAL_EXEC, 2);
		पूर्ण अन्यथा अगर (BTC_RSSI_MEDIUM(bt_rssi_state)) अणु
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		पूर्ण अन्यथा अणु
			btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		पूर्ण
	पूर्ण

	अगर (wअगरi_bw == BTC_WIFI_BW_LEGACY) अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण अन्यथा अणु
		btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 14);
		btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON, 0x50,
					      0x4);
	पूर्ण

	अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 23);
	पूर्ण अन्यथा अणु
		btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 23);
	पूर्ण

	/* sw mechanism */
	अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8821a2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8821a2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_action_wअगरi_multi_port(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8821a2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	/* sw all off */
	btc8821a2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8821a2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);

	/* hw all off */
	btc8821a2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	btc8821a2ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8821a2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
पूर्ण

अटल व्योम btc8821a2ant_run_coexist_mechanism(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_under_5g = false;
	u8 algorithm = 0;
	u32 num_of_wअगरi_link = 0;
	u32 wअगरi_link_status = 0;
	bool miracast_plus_bt = false;
	bool scan = false, link = false, roam = false;

	अगर (btcoexist->manual_control) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Manual control!!!\n");
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);

	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), run 5G coex setting!!<===\n");
		btc8821a2ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	अगर (coex_sta->under_ips) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], wifi is under IPS !!!\n");
		वापस;
	पूर्ण

	algorithm = btc8821a2ant_action_algorithm(btcoexist);
	अगर (coex_sta->c2h_bt_inquiry_page &&
	    (BT_8821A_2ANT_COEX_ALGO_PANHS != algorithm)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT is under inquiry/page scan !!\n");
		btc8821a2ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

	अगर (scan || link || roam) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], WiFi is under Link Process !!\n");
		btc8821a2ant_action_wअगरi_link_process(btcoexist);
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
		btc8821a2ant_action_wअगरi_multi_port(btcoexist);

		वापस;
	पूर्ण

	miracast_plus_bt = false;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_MIRACAST_PLUS_BT,
			   &miracast_plus_bt);

	coex_dm->cur_algorithm = algorithm;
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Algorithm = %d\n", coex_dm->cur_algorithm);

	अगर (btc8821a2ant_is_common_action(btcoexist)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Action 2-Ant common\n");
		coex_dm->स्वतः_tdma_adjust = true;
	पूर्ण अन्यथा अणु
		अगर (coex_dm->cur_algorithm != coex_dm->pre_algorithm) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], pre_algorithm = %d, cur_algorithm = %d\n",
				coex_dm->pre_algorithm,
				coex_dm->cur_algorithm);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण
		चयन (coex_dm->cur_algorithm) अणु
		हाल BT_8821A_2ANT_COEX_ALGO_SCO:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = SCO\n");
			btc8821a2ant_action_sco(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID\n");
			btc8821a2ant_action_hid(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = A2DP\n");
			btc8821a2ant_action_a2dp(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_A2DP_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = A2DP+PAN(HS)\n");
			btc8821a2ant_action_a2dp_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN(EDR)\n");
			btc8821a2ant_action_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HS mode\n");
			btc8821a2ant_action_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_PANEDR_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN+A2DP\n");
			btc8821a2ant_action_pan_edr_a2dp(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_PANEDR_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = PAN(EDR)+HID\n");
			btc8821a2ant_action_pan_edr_hid(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID+A2DP+PAN\n");
			btc8821a2ant_act_hid_a2dp_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8821A_2ANT_COEX_ALGO_HID_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = HID+A2DP\n");
			btc8821a2ant_action_hid_a2dp(btcoexist);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action 2-Ant, algorithm = coexist All Off!!\n");
			btc8821a2ant_coex_all_off(btcoexist);
			अवरोध;
		पूर्ण
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	पूर्ण
पूर्ण

अटल व्योम btc8821a2ant_wअगरi_off_hw_cfg(काष्ठा btc_coexist *btcoexist)
अणु
	u8 h2c_parameter[2] = अणु0पूर्ण;
	u32 fw_ver = 0;

	/* set wlan_act to low */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);

	/* WiFi जाओ standby जबतक GNT_BT 0-->1 */
	btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1, 0xfffff, 0x780);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	अगर (fw_ver >= 0x180000) अणु
		/* Use H2C to set GNT_BT to HIGH */
		h2c_parameter[0] = 1;
		btcoexist->btc_fill_h2c(btcoexist, 0x6E, 1, h2c_parameter);
	पूर्ण अन्यथा अणु
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x765, 0x18);
	पूर्ण
पूर्ण

/**************************************************************
 * बाह्य function start with ex_btc8821a2ant_
 **************************************************************/
व्योम ex_btc8821a2ant_init_hwconfig(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 u1पंचांगp = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], 2Ant Init HW Config!!\n");

	/* backup rf 0x1e value */
	coex_dm->bt_rf0x1e_backup =
		btcoexist->btc_get_rf_reg(btcoexist, BTC_RF_A, 0x1e, 0xfffff);

	/* 0x790[5:0] = 0x5 */
	u1पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x790);
	u1पंचांगp &= 0xc0;
	u1पंचांगp |= 0x5;
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x790, u1पंचांगp);

	/* Antenna config */
	btc8821a2ant_set_ant_path(btcoexist, BTC_ANT_WIFI_AT_MAIN, true, false);
	coex_sta->dis_ver_info_cnt = 0;

	/* PTA parameter */
	btc8821a2ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);

	/* Enable counter statistics */
	/* 0x76e[3] = 1, WLAN_Act control by PTA */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x778, 0x3);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x40, 0x20, 0x1);
पूर्ण

व्योम ex_btc8821a2ant_pre_load_firmware(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u8 u8पंचांगp = 0x4; /* Set BIT2 by शेष since it's 2ant हाल */

	/**
	 * S0 or S1 setting and Local रेजिस्टर setting(By the setting fw can get
	 * ant number, S0/S1, ... info)
	 *
	 * Local setting bit define
	 *	BIT0: "0" क्रम no antenna inverse; "1" क्रम antenna inverse
	 *	BIT1: "0" क्रम पूर्णांकernal चयन; "1" क्रम बाह्यal चयन
	 *	BIT2: "0" क्रम one antenna; "1" क्रम two antenna
	 * NOTE: here शेष all पूर्णांकernal चयन and 1-antenna ==> BIT1=0 and
	 * BIT2=0
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

व्योम ex_btc8821a2ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Coex Mechanism Init!!\n");

	btc8821a2ant_init_coex_dm(btcoexist);
पूर्ण

व्योम ex_btc8821a2ant_display_coex_info(काष्ठा btc_coexist *btcoexist,
				       काष्ठा seq_file *m)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;
	u8 u1पंचांगp[4], i, bt_info_ext, ps_tdma_हाल = 0;
	u32 u4पंचांगp[4];
	bool roam = false, scan = false, link = false, wअगरi_under_5g = false;
	bool bt_hs_on = false, wअगरi_busy = false;
	दीर्घ wअगरi_rssi = 0, bt_hs_rssi = 0;
	u32 wअगरi_bw, wअगरi_traffic_dir;
	u8 wअगरi_करोt_11_chnl, wअगरi_hs_chnl;
	u32 fw_ver = 0, bt_patch_ver = 0;

	seq_माला_दो(m, "\n ============[BT Coexist info]============");

	seq_म_लिखो(m, "\n %-35s = %d/ %d ", "Ant PG number/ Ant mechanism:",
		   board_info->pg_ant_num, board_info->btdm_ant_num);

	अगर (btcoexist->manual_control) अणु
		seq_म_लिखो(m, "\n %-35s", "[Action Manual control]!!");
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %s / %d", "BT stack/ hci ext ver",
		   ((stack_info->profile_notअगरied) ? "Yes" : "No"),
		   stack_info->hci_version);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER, &bt_patch_ver);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	seq_म_लिखो(m, "\n %-35s = %d_%d/ 0x%x/ 0x%x(%d)",
		   "CoexVer/ FwVer/ PatchVer",
		   glcoex_ver_date_8821a_2ant, glcoex_ver_8821a_2ant,
		   fw_ver, bt_patch_ver, bt_patch_ver);

	btcoexist->btc_get(btcoexist,
		BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U1_WIFI_DOT11_CHNL, &wअगरi_करोt_11_chnl);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U1_WIFI_HS_CHNL, &wअगरi_hs_chnl);
	seq_म_लिखो(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsMode(HsChnl)",
		   wअगरi_करोt_11_chnl, bt_hs_on, wअगरi_hs_chnl);

	seq_म_लिखो(m, "\n %-35s = %3ph ",
		   "H2C Wifi inform bt chnl Info",
		   coex_dm->wअगरi_chnl_info);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	seq_म_लिखो(m, "\n %-35s = %ld/ %ld", "Wifi rssi/ HS rssi",
		   wअगरi_rssi, bt_hs_rssi);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d ", "Wifi link/ roam/ scan",
		   link, roam, scan);

	btcoexist->btc_get(btcoexist,
		BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	btcoexist->btc_get(btcoexist,
		BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_get(btcoexist,
		BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION, &wअगरi_traffic_dir);
	seq_म_लिखो(m, "\n %-35s = %s / %s/ %s ", "Wifi status",
		   (wअगरi_under_5g ? "5G" : "2.4G"),
		   ((BTC_WIFI_BW_LEGACY == wअगरi_bw) ? "Legacy" :
		    (((BTC_WIFI_BW_HT40 == wअगरi_bw) ? "HT40" : "HT20"))),
		   ((!wअगरi_busy) ? "idle" :
		    ((BTC_WIFI_TRAFFIC_TX == wअगरi_traffic_dir) ?
		     "uplink" : "downlink")));

	अगर (stack_info->profile_notअगरied) अणु
		seq_म_लिखो(m, "\n %-35s = %d / %d / %d / %d",
			   "SCO/HID/PAN/A2DP",
			   stack_info->sco_exist, stack_info->hid_exist,
			   stack_info->pan_exist, stack_info->a2dp_exist);

		btcoexist->btc_disp_dbg_msg(btcoexist,
					    BTC_DBG_DISP_BT_LINK_INFO,
					    m);
	पूर्ण

	bt_info_ext = coex_sta->bt_info_ext;
	seq_म_लिखो(m, "\n %-35s = %s", "BT Info A2DP rate",
		   (bt_info_ext&BIT0) ? "Basic rate" : "EDR rate");

	क्रम (i = 0; i < BT_INFO_SRC_8821A_2ANT_MAX; i++) अणु
		अगर (coex_sta->bt_info_c2h_cnt[i]) अणु
			seq_म_लिखो(m, "\n %-35s = %7ph(%d)",
				   glbt_info_src_8821a_2ant[i],
				   coex_sta->bt_info_c2h[i],
				   coex_sta->bt_info_c2h_cnt[i]);
		पूर्ण
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %s/%s",
		   "PS state, IPS/LPS",
		   ((coex_sta->under_ips ? "IPS ON" : "IPS OFF")),
		   ((coex_sta->under_lps ? "LPS ON" : "LPS OFF")));
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD, m);

	/* Sw mechanism*/
	seq_म_लिखो(m, "\n %-35s",
		   "============[Sw mechanism]============");
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d(0x%x) ",
		   "SM2[AgcT/ AdcB/ SwDacSwing(lvl)]",
		   coex_dm->cur_agc_table_en, coex_dm->cur_adc_back_off,
		   coex_dm->cur_dac_swing_on, coex_dm->cur_dac_swing_lvl);

	/* Fw mechanism*/
	seq_म_लिखो(m, "\n %-35s",
		   "============[Fw mechanism]============");

	अगर (!btcoexist->manual_control) अणु
		ps_tdma_हाल = coex_dm->cur_ps_tdma;
		seq_म_लिखो(m, "\n %-35s = %5ph case-%d",
			   "PS TDMA",
			   coex_dm->ps_tdma_para, ps_tdma_हाल);

		seq_म_लिखो(m, "\n %-35s = %d/ %d ", "DecBtPwr/ IgnWlanAct",
			   coex_dm->cur_dec_bt_pwr_lvl,
			   coex_dm->cur_ignore_wlan_act);
	पूर्ण

	/* Hw setting*/
	seq_म_लिखो(m, "\n %-35s", "============[Hw setting]============");

	seq_म_लिखो(m, "\n %-35s = 0x%x", "RF-A, 0x1e initVal",
		   coex_dm->bt_rf0x1e_backup);

	u1पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x778);
	u1पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x6cc);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x ",
		   "0x778 (W_Act)/ 0x6cc (CoTab Sel)",
		   u1पंचांगp[0], u1पंचांगp[1]);

	u1पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x8db);
	u1पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xc5b);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x8db(ADC)/0xc5b[29:25](DAC)",
		   ((u1पंचांगp[0] & 0x60) >> 5), ((u1पंचांगp[1] & 0x3e) >> 1));

	u4पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xcb4);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0xcb4[7:0](ctrl)/ 0xcb4[29:28](val)",
		   u4पंचांगp[0] & 0xff, ((u4पंचांगp[0] & 0x30000000) >> 28));

	u1पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x40);
	u4पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
	u4पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x974);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x40/ 0x4c[24:23]/ 0x974",
		   u1पंचांगp[0], ((u4पंचांगp[0] & 0x01800000) >> 23), u4पंचांगp[1]);

	u4पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x550);
	u1पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x522);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x550(bcn ctrl)/0x522",
		   u4पंचांगp[0], u1पंचांगp[0]);

	u4पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xc50);
	u1पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xa0a);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0xc50(DIG)/0xa0a(CCK-TH)",
		   u4पंचांगp[0], u1पंचांगp[0]);

	u4पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xf48);
	u1पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xa5b);
	u1पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xa5c);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "OFDM-FA/ CCK-FA",
		   u4पंचांगp[0], (u1पंचांगp[0] << 8) + u1पंचांगp[1]);

	u4पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c0);
	u4पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c4);
	u4पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c8);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x6c0/0x6c4/0x6c8",
		   u4पंचांगp[0], u4पंचांगp[1], u4पंचांगp[2]);

	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x770 (hi-pri Rx/Tx)",
		   coex_sta->high_priority_rx, coex_sta->high_priority_tx);
	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x774(low-pri Rx/Tx)",
		   coex_sta->low_priority_rx, coex_sta->low_priority_tx);

	/* Tx mgnt queue hang or not, 0x41b should = 0xf, ex: 0xd ==>hang*/
	u1पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x41b);
	seq_म_लिखो(m, "\n %-35s = 0x%x",
		   "0x41b (mgntQ hang chk == 0xf)",
		   u1पंचांगp[0]);

	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS, m);
पूर्ण

व्योम ex_btc8821a2ant_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_IPS_ENTER == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		btc8821a2ant_wअगरi_off_hw_cfg(btcoexist);
		btc8821a2ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
		btc8821a2ant_coex_all_off(btcoexist);
	पूर्ण अन्यथा अगर (BTC_IPS_LEAVE == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;
		ex_btc8821a2ant_init_hwconfig(btcoexist);
		btc8821a2ant_init_coex_dm(btcoexist);
		btc8821a2ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8821a2ant_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
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

व्योम ex_btc8821a2ant_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_SCAN_START == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN START notify\n");
	पूर्ण अन्यथा अगर (BTC_SCAN_FINISH == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN FINISH notify\n");
	पूर्ण
पूर्ण

व्योम ex_btc8821a2ant_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_ASSOCIATE_START == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT START notify\n");
	पूर्ण अन्यथा अगर (BTC_ASSOCIATE_FINISH == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT FINISH notify\n");
	पूर्ण
पूर्ण

व्योम ex_btc8821a2ant_media_status_notअगरy(काष्ठा btc_coexist *btcoexist,
					 u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[3] = अणु0पूर्ण;
	u32 wअगरi_bw;
	u8 wअगरi_central_chnl;
	u8 ap_num = 0;

	अगर (BTC_MEDIA_CONNECT == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA connect notify\n");
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA disconnect notify\n");
	पूर्ण

	/* only 2.4G we need to inक्रमm bt the chnl mask */
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL,
			   &wअगरi_central_chnl);
	अगर ((BTC_MEDIA_CONNECT == type) &&
	    (wअगरi_central_chnl <= 14)) अणु
		h2c_parameter[0] = 0x1;
		h2c_parameter[1] = wअगरi_central_chnl;
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
		अगर (wअगरi_bw == BTC_WIFI_BW_HT40) अणु
			h2c_parameter[2] = 0x30;
		पूर्ण अन्यथा अणु
			h2c_parameter[2] = 0x20;
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
		"[BTCoex], FW write 0x66 = 0x%x\n",
		h2c_parameter[0] << 16 |
		h2c_parameter[1] << 8 |
		h2c_parameter[2]);

	btcoexist->btc_fill_h2c(btcoexist, 0x66, 3, h2c_parameter);
पूर्ण

व्योम ex_btc8821a2ant_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist,
					   u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (type == BTC_PACKET_DHCP) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], DHCP Packet notify\n");
	पूर्ण
पूर्ण

व्योम ex_btc8821a2ant_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist,
				    u8 *पंचांगp_buf, u8 length)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 bt_info = 0;
	u8 i, rsp_source = 0;
	bool bt_busy = false, limited_dig = false;
	bool wअगरi_connected = false, wअगरi_under_5g = false;

	coex_sta->c2h_bt_info_req_sent = false;
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);

	rsp_source = पंचांगp_buf[0] & 0xf;
	अगर (rsp_source >= BT_INFO_SRC_8821A_2ANT_MAX)
		rsp_source = BT_INFO_SRC_8821A_2ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Bt info[%d], length = %d, hex data = [",
		rsp_source, length);
	क्रम (i = 0; i < length; i++) अणु
		coex_sta->bt_info_c2h[rsp_source][i] = पंचांगp_buf[i];
		अगर (i == 1)
			bt_info = पंचांगp_buf[i];
		अगर (i == length - 1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x]\n", पंचांगp_buf[i]);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x, ", पंचांगp_buf[i]);
		पूर्ण
	पूर्ण

	अगर (btcoexist->manual_control) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), return for Manual CTRL<===\n");
		वापस;
	पूर्ण

	अगर (BT_INFO_SRC_8821A_2ANT_WIFI_FW != rsp_source) अणु
		/* [3:0] */
		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2]&0xf;

		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->bt_info_ext = coex_sta->bt_info_c2h[rsp_source][4];

		coex_sta->bt_tx_rx_mask =
			(coex_sta->bt_info_c2h[rsp_source][2] & 0x40);
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TX_RX_MASK,
				   &coex_sta->bt_tx_rx_mask);
		अगर (coex_sta->bt_tx_rx_mask) अणु
			/* BT पूर्णांकo is responded by BT FW and BT RF REG 0x3C !=
			 * 0x01 => Need to चयन BT TRx Mask
			 */
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Switch BT TRx Mask since BT RF REG 0x3C != 0x01\n");
			btcoexist->btc_set_bt_reg(btcoexist, BTC_BT_REG_RF,
						  0x3c, 0x01);
		पूर्ण

		/* Here we need to resend some wअगरi info to BT
		 * because bt is reset and loss of the info
		 */
		अगर ((coex_sta->bt_info_ext & BIT1)) अणु
			btcoexist->btc_get(btcoexist,
				BTC_GET_BL_WIFI_CONNECTED, &wअगरi_connected);
			अगर (wअगरi_connected) अणु
				ex_btc8821a2ant_media_status_notअगरy(btcoexist,
					BTC_MEDIA_CONNECT);
			पूर्ण अन्यथा अणु
				ex_btc8821a2ant_media_status_notअगरy(btcoexist,
					BTC_MEDIA_DISCONNECT);
			पूर्ण

		पूर्ण

		अगर (!btcoexist->manual_control && !wअगरi_under_5g) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], BT ext info = 0x%x!!\n",
				coex_sta->bt_info_ext);
			अगर ((coex_sta->bt_info_ext & BIT(3))) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit3=1, wifi_connected=%d\n",
					wअगरi_connected);
				अगर (wअगरi_connected) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n");
					btc8821a2ant_ignore_wlan_act(btcoexist,
								     FORCE_EXEC,
								     false);
				पूर्ण
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit3=0, wifi_connected=%d\n",
					wअगरi_connected);
				/* BT alपढ़ोy NOT ignore Wlan active, करो nothing
				 * here.
				 */
				अगर (!wअगरi_connected) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT ext info bit3 check, set BT to ignore Wlan active!!\n");
					btc8821a2ant_ignore_wlan_act(
						btcoexist, FORCE_EXEC, true);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* check BIT2 first ==> check अगर bt is under inquiry or page scan*/
	अगर (bt_info & BT_INFO_8821A_2ANT_B_INQ_PAGE) अणु
		coex_sta->c2h_bt_inquiry_page = true;
	पूर्ण अन्यथा अणु
		coex_sta->c2h_bt_inquiry_page = false;
	पूर्ण
	/* set link exist status */
	अगर (!(bt_info & BT_INFO_8821A_2ANT_B_CONNECTION)) अणु
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	पूर्ण अन्यथा अणु /* connection exists */
		coex_sta->bt_link_exist = true;
		अगर (bt_info & BT_INFO_8821A_2ANT_B_FTP)
			coex_sta->pan_exist = true;
		अन्यथा
			coex_sta->pan_exist = false;
		अगर (bt_info & BT_INFO_8821A_2ANT_B_A2DP)
			coex_sta->a2dp_exist = true;
		अन्यथा
			coex_sta->a2dp_exist = false;
		अगर (bt_info & BT_INFO_8821A_2ANT_B_HID)
			coex_sta->hid_exist = true;
		अन्यथा
			coex_sta->hid_exist = false;
		अगर (bt_info & BT_INFO_8821A_2ANT_B_SCO_ESCO)
			coex_sta->sco_exist = true;
		अन्यथा
			coex_sta->sco_exist = false;

		अगर ((!coex_sta->hid_exist) &&
		    (!coex_sta->c2h_bt_inquiry_page) &&
		    (!coex_sta->sco_exist)) अणु
			अगर (coex_sta->high_priority_tx +
				    coex_sta->high_priority_rx >= 160)
				coex_sta->hid_exist = true;
		पूर्ण
	पूर्ण

	btc8821a2ant_update_bt_link_info(btcoexist);

	अगर (!(bt_info & BT_INFO_8821A_2ANT_B_CONNECTION)) अणु
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n");
	पूर्ण अन्यथा अगर (bt_info == BT_INFO_8821A_2ANT_B_CONNECTION) अणु
		/* connection exists but no busy */
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_CON_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n");
	पूर्ण अन्यथा अगर ((bt_info & BT_INFO_8821A_2ANT_B_SCO_ESCO) ||
		   (bt_info & BT_INFO_8821A_2ANT_B_SCO_BUSY)) अणु
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_SCO_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT SCO busy!!!\n");
	पूर्ण अन्यथा अगर (bt_info & BT_INFO_8821A_2ANT_B_ACL_BUSY) अणु
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_ACL_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT ACL busy!!!\n");
	पूर्ण अन्यथा अणु
		coex_dm->bt_status = BT_8821A_2ANT_BT_STATUS_MAX;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n");
	पूर्ण

	अगर ((coex_dm->bt_status == BT_8821A_2ANT_BT_STATUS_ACL_BUSY) ||
	    (coex_dm->bt_status == BT_8821A_2ANT_BT_STATUS_SCO_BUSY) ||
	    (coex_dm->bt_status == BT_8821A_2ANT_BT_STATUS_ACL_SCO_BUSY)) अणु
		bt_busy = true;
		limited_dig = true;
	पूर्ण अन्यथा अणु
		bt_busy = false;
		limited_dig = false;
	पूर्ण

	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	coex_dm->limited_dig = limited_dig;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_LIMITED_DIG, &limited_dig);

	btc8821a2ant_run_coexist_mechanism(btcoexist);
पूर्ण

व्योम ex_btc8821a2ant_halt_notअगरy(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Halt notify\n");

	btc8821a2ant_wअगरi_off_hw_cfg(btcoexist);
	btc8821a2ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
	ex_btc8821a2ant_media_status_notअगरy(btcoexist, BTC_MEDIA_DISCONNECT);
पूर्ण

व्योम ex_btc8821a2ant_pnp_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pnp_state)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Pnp notify\n");

	अगर (pnp_state == BTC_WIFI_PNP_SLEEP) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to SLEEP\n");
	पूर्ण अन्यथा अगर (pnp_state == BTC_WIFI_PNP_WAKE_UP) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to WAKE UP\n");
		ex_btc8821a2ant_init_hwconfig(btcoexist);
		btc8821a2ant_init_coex_dm(btcoexist);
		btc8821a2ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8821a2ant_periodical(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

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
			btc8821a2ant_set_ant_path(btcoexist,
					BTC_ANT_WIFI_AT_MAIN, false, false);
		पूर्ण
	पूर्ण

	अगर (btcoexist->स्वतः_report_2ant) अणु
		btc8821a2ant_query_bt_info(btcoexist);
	पूर्ण अन्यथा अणु
		btc8821a2ant_monitor_bt_ctr(btcoexist);
		btc8821a2ant_monitor_wअगरi_ctr(btcoexist);

		अगर (btc8821a2ant_is_wअगरi_status_changed(btcoexist) ||
		    coex_dm->स्वतः_tdma_adjust)
			btc8821a2ant_run_coexist_mechanism(btcoexist);
	पूर्ण
पूर्ण
