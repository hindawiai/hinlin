<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2012  Realtek Corporation.*/

/**************************************************************
 * Description:
 *
 * This file is क्रम RTL8821A Co-exist mechanism
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
अटल काष्ठा coex_dm_8821a_1ant glcoex_dm_8821a_1ant;
अटल काष्ठा coex_dm_8821a_1ant *coex_dm = &glcoex_dm_8821a_1ant;
अटल काष्ठा coex_sta_8821a_1ant glcoex_sta_8821a_1ant;
अटल काष्ठा coex_sta_8821a_1ant *coex_sta = &glcoex_sta_8821a_1ant;
अटल व्योम btc8821a1ant_act_bt_sco_hid_only_busy(काष्ठा btc_coexist *btcoexist,
						  u8 wअगरi_status);

अटल स्थिर अक्षर *स्थिर glbt_info_src_8821a_1ant[] = अणु
	  "BT Info[wifi fw]",
	  "BT Info[bt rsp]",
	  "BT Info[bt auto report]",
पूर्ण;

अटल u32 glcoex_ver_date_8821a_1ant = 20130816;
अटल u32 glcoex_ver_8821a_1ant = 0x41;

/**************************************************************
 * local function proto type अगर needed
 *
 * local function start with btc8821a1ant_
 **************************************************************/
अटल u8 btc8821a1ant_bt_rssi_state(काष्ठा btc_coexist *btcoexist,
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
			अगर (bt_rssi >= (rssi_thresh +
					BTC_RSSI_COEX_THRESH_TOL_8821A_1ANT)) अणु
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
			अगर (bt_rssi >= (rssi_thresh +
					BTC_RSSI_COEX_THRESH_TOL_8821A_1ANT)) अणु
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
			अगर (bt_rssi >= (rssi_thresh1 +
					BTC_RSSI_COEX_THRESH_TOL_8821A_1ANT)) अणु
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

अटल u8 btc8821a1ant_wअगरi_rssi_state(काष्ठा btc_coexist *btcoexist,
				       u8 index, u8 level_num, u8 rssi_thresh,
				       u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	दीर्घ	wअगरi_rssi = 0;
	u8	wअगरi_rssi_state = coex_sta->pre_wअगरi_rssi_state[index];

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);

	अगर (level_num == 2) अणु
		अगर ((coex_sta->pre_wअगरi_rssi_state[index] ==
		     BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wअगरi_rssi_state[index] ==
		     BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (wअगरi_rssi >= (rssi_thresh +
					BTC_RSSI_COEX_THRESH_TOL_8821A_1ANT)) अणु
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
			अगर (wअगरi_rssi >= (rssi_thresh +
					BTC_RSSI_COEX_THRESH_TOL_8821A_1ANT)) अणु
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
					BTC_RSSI_COEX_THRESH_TOL_8821A_1ANT)) अणु
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

अटल व्योम btc8821a1ant_update_ra_mask(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, u32 dis_rate_mask)
अणु
	coex_dm->cur_ra_mask = dis_rate_mask;

	अगर (क्रमce_exec ||
	    (coex_dm->pre_ra_mask != coex_dm->cur_ra_mask)) अणु
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_UPDATE_RAMASK,
				   &coex_dm->cur_ra_mask);
	पूर्ण
	coex_dm->pre_ra_mask = coex_dm->cur_ra_mask;
पूर्ण

अटल व्योम btc8821a1ant_स्वतः_rate_fb_retry(काष्ठा btc_coexist *btcoexist,
					    bool क्रमce_exec, u8 type)
अणु
	bool wअगरi_under_b_mode = false;

	coex_dm->cur_arfr_type = type;

	अगर (क्रमce_exec ||
	    (coex_dm->pre_arfr_type != coex_dm->cur_arfr_type)) अणु
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
					   &wअगरi_under_b_mode);
			अगर (wअगरi_under_b_mode) अणु
				btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x430,
							   0x0);
				btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x434,
							   0x01010101);
			पूर्ण अन्यथा अणु
				btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x430,
							   0x0);
				btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x434,
							   0x04030201);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	coex_dm->pre_arfr_type = coex_dm->cur_arfr_type;
पूर्ण

अटल व्योम btc8821a1ant_retry_limit(काष्ठा btc_coexist *btcoexist,
				     bool क्रमce_exec, u8 type)
अणु
	coex_dm->cur_retry_limit_type = type;

	अगर (क्रमce_exec ||
	    (coex_dm->pre_retry_limit_type != coex_dm->cur_retry_limit_type)) अणु
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

अटल व्योम btc8821a1ant_ampdu_max_समय(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, u8 type)
अणु
	coex_dm->cur_ampdu_समय_प्रकारype = type;

	अगर (क्रमce_exec ||
	    (coex_dm->pre_ampdu_समय_प्रकारype != coex_dm->cur_ampdu_समय_प्रकारype)) अणु
		चयन (coex_dm->cur_ampdu_समय_प्रकारype) अणु
		हाल 0:	/* normal mode */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x456,
						   coex_dm->backup_ampdu_max_समय);
			अवरोध;
		हाल 1:	/* AMPDU समय = 0x38 * 32us */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x456, 0x38);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	coex_dm->pre_ampdu_समय_प्रकारype = coex_dm->cur_ampdu_समय_प्रकारype;
पूर्ण

अटल व्योम btc8821a1ant_limited_tx(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u8 ra_mask_type,
				    u8 arfr_type, u8 retry_limit_type,
				    u8 ampdu_समय_प्रकारype)
अणु
	चयन (ra_mask_type) अणु
	हाल 0:	/* normal mode */
		btc8821a1ant_update_ra_mask(btcoexist, क्रमce_exec, 0x0);
		अवरोध;
	हाल 1:	/* disable cck 1/2 */
		btc8821a1ant_update_ra_mask(btcoexist, क्रमce_exec,
					    0x00000003);
		अवरोध;
	हाल 2:	/* disable cck 1/2/5.5, ofdm 6/9/12/18/24, mcs 0/1/2/3/4 */
		btc8821a1ant_update_ra_mask(btcoexist, क्रमce_exec,
					    0x0001f1f7);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	btc8821a1ant_स्वतः_rate_fb_retry(btcoexist, क्रमce_exec, arfr_type);
	btc8821a1ant_retry_limit(btcoexist, क्रमce_exec, retry_limit_type);
	btc8821a1ant_ampdu_max_समय(btcoexist, क्रमce_exec, ampdu_समय_प्रकारype);
पूर्ण

अटल व्योम btc8821a1ant_limited_rx(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, bool rej_ap_agg_pkt,
				    bool bt_ctrl_agg_buf_size, u8 agg_buf_size)
अणु
	bool reject_rx_agg = rej_ap_agg_pkt;
	bool bt_ctrl_rx_agg_size = bt_ctrl_agg_buf_size;
	u8 rx_agg_size = agg_buf_size;

	/* Rx Aggregation related setting */
	btcoexist->btc_set(btcoexist,
		 BTC_SET_BL_TO_REJ_AP_AGG_PKT, &reject_rx_agg);
	/* decide BT control aggregation buf size or not */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE,
			   &bt_ctrl_rx_agg_size);
	/* aggregation buf size, only work when BT control Rx agg size */
	btcoexist->btc_set(btcoexist, BTC_SET_U1_AGG_BUF_SIZE, &rx_agg_size);
	/* real update aggregation setting */
	btcoexist->btc_set(btcoexist, BTC_SET_ACT_AGGREGATE_CTRL, शून्य);
पूर्ण

अटल व्योम btc8821a1ant_monitor_bt_ctr(काष्ठा btc_coexist *btcoexist)
अणु
	u32 reg_hp_tx_rx, reg_lp_tx_rx, u4_पंचांगp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;

	reg_hp_tx_rx = 0x770;
	reg_lp_tx_rx = 0x774;

	u4_पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, reg_hp_tx_rx);
	reg_hp_tx = u4_पंचांगp & MASKLWORD;
	reg_hp_rx = (u4_पंचांगp & MASKHWORD) >> 16;

	u4_पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, reg_lp_tx_rx);
	reg_lp_tx = u4_पंचांगp & MASKLWORD;
	reg_lp_rx = (u4_पंचांगp & MASKHWORD) >> 16;

	coex_sta->high_priority_tx = reg_hp_tx;
	coex_sta->high_priority_rx = reg_hp_rx;
	coex_sta->low_priority_tx = reg_lp_tx;
	coex_sta->low_priority_rx = reg_lp_rx;

	/* reset counter */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0xc);
पूर्ण

अटल व्योम btc8821a1ant_query_bt_info(काष्ठा btc_coexist *btcoexist)
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

अटल व्योम btc8821a1ant_update_bt_link_info(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info	*bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	bt_link_info->bt_link_exist = coex_sta->bt_link_exist;
	bt_link_info->sco_exist = coex_sta->sco_exist;
	bt_link_info->a2dp_exist = coex_sta->a2dp_exist;
	bt_link_info->pan_exist = coex_sta->pan_exist;
	bt_link_info->hid_exist = coex_sta->hid_exist;

	/* work around क्रम HS mode */
	अगर (bt_hs_on) अणु
		bt_link_info->pan_exist = true;
		bt_link_info->bt_link_exist = true;
	पूर्ण

	/* check अगर Sco only */
	अगर (bt_link_info->sco_exist &&
	    !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist &&
	    !bt_link_info->hid_exist)
		bt_link_info->sco_only = true;
	अन्यथा
		bt_link_info->sco_only = false;

	/* check अगर A2dp only */
	अगर (!bt_link_info->sco_exist &&
	    bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist &&
	    !bt_link_info->hid_exist)
		bt_link_info->a2dp_only = true;
	अन्यथा
		bt_link_info->a2dp_only = false;

	/* check अगर Pan only */
	अगर (!bt_link_info->sco_exist &&
	    !bt_link_info->a2dp_exist &&
	    bt_link_info->pan_exist &&
	    !bt_link_info->hid_exist)
		bt_link_info->pan_only = true;
	अन्यथा
		bt_link_info->pan_only = false;

	/* check अगर Hid only */
	अगर (!bt_link_info->sco_exist &&
	    !bt_link_info->a2dp_exist &&
	    !bt_link_info->pan_exist &&
	    bt_link_info->hid_exist)
		bt_link_info->hid_only = true;
	अन्यथा
		bt_link_info->hid_only = false;
पूर्ण

अटल u8 btc8821a1ant_action_algorithm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool bt_hs_on = false;
	u8 algorithm = BT_8821A_1ANT_COEX_ALGO_UNDEFINED;
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
				"[BTCoex], BT Profile = SCO only\n");
			algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Profile = HID only\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Profile = A2DP only\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_A2DP;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = PAN(HS) only\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = PAN(EDR) only\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 2) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Profile = SCO + HID\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Profile = SCO + A2DP ==> SCO\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = SCO + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = SCO + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Profile = HID + A2DP\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = HID + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = HID + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = A2DP + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_A2DP_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = A2DP + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_A2DP;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 3) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT Profile = SCO + HID + A2DP ==> HID\n");
				algorithm = BT_8821A_1ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = SCO + HID + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = SCO + HID + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = SCO + A2DP + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = SCO + A2DP + PAN(EDR) ==> HID\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = HID + A2DP + PAN(HS)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = HID + A2DP + PAN(EDR)\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_HID_A2DP_PANEDR;
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
						"[BTCoex], Error!!! BT Profile = SCO + HID + A2DP + PAN(HS)\n");

				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"[BTCoex], BT Profile = SCO + HID + A2DP + PAN(EDR)==>PAN(EDR)+HID\n");
					algorithm = BT_8821A_1ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस algorithm;
पूर्ण

अटल व्योम btc8821a1ant_set_sw_penalty_tx_rate(काष्ठा btc_coexist *btcoexist,
						bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[6] = अणु0पूर्ण;

	h2c_parameter[0] = 0x6;	/* opCode, 0x6= Retry_Penalty*/

	अगर (low_penalty_ra) अणु
		h2c_parameter[1] |= BIT0;
		/* normal rate except MCS7/6/5, OFDM54/48/36 */
		h2c_parameter[2] = 0x00;
		h2c_parameter[3] = 0xf7; /* MCS7 or OFDM54 */
		h2c_parameter[4] = 0xf8; /* MCS6 or OFDM48 */
		h2c_parameter[5] = 0xf9; /* MCS5 or OFDM36 */
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set WiFi Low-Penalty Retry: %s",
		(low_penalty_ra ? "ON!!" : "OFF!!"));

	btcoexist->btc_fill_h2c(btcoexist, 0x69, 6, h2c_parameter);
पूर्ण

अटल व्योम btc8821a1ant_low_penalty_ra(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, bool low_penalty_ra)
अणु
	coex_dm->cur_low_penalty_ra = low_penalty_ra;

	अगर (!क्रमce_exec) अणु
		अगर (coex_dm->pre_low_penalty_ra == coex_dm->cur_low_penalty_ra)
			वापस;
	पूर्ण
	btc8821a1ant_set_sw_penalty_tx_rate(btcoexist,
					    coex_dm->cur_low_penalty_ra);

	coex_dm->pre_low_penalty_ra = coex_dm->cur_low_penalty_ra;
पूर्ण

अटल व्योम btc8821a1ant_set_coex_table(काष्ठा btc_coexist *btcoexist,
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

अटल व्योम btc8821a1ant_coex_table(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u32 val0x6c0, u32 val0x6c4,
				    u32 val0x6c8, u8 val0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s write Coex Table 0x6c0 = 0x%x, 0x6c4 = 0x%x, 0x6c8 = 0x%x, 0x6cc = 0x%x\n",
		(क्रमce_exec ? "force to" : ""), val0x6c0, val0x6c4,
		val0x6c8, val0x6cc);
	coex_dm->cur_val_0x6c0 = val0x6c0;
	coex_dm->cur_val_0x6c4 = val0x6c4;
	coex_dm->cur_val_0x6c8 = val0x6c8;
	coex_dm->cur_val_0x6cc = val0x6cc;

	अगर (!क्रमce_exec) अणु
		अगर ((coex_dm->pre_val_0x6c0 == coex_dm->cur_val_0x6c0) &&
		    (coex_dm->pre_val_0x6c4 == coex_dm->cur_val_0x6c4) &&
		    (coex_dm->pre_val_0x6c8 == coex_dm->cur_val_0x6c8) &&
		    (coex_dm->pre_val_0x6cc == coex_dm->cur_val_0x6cc))
			वापस;
	पूर्ण
	btc8821a1ant_set_coex_table(btcoexist, val0x6c0, val0x6c4,
				    val0x6c8, val0x6cc);

	coex_dm->pre_val_0x6c0 = coex_dm->cur_val_0x6c0;
	coex_dm->pre_val_0x6c4 = coex_dm->cur_val_0x6c4;
	coex_dm->pre_val_0x6c8 = coex_dm->cur_val_0x6c8;
	coex_dm->pre_val_0x6cc = coex_dm->cur_val_0x6cc;
पूर्ण

अटल व्योम btc8821a1ant_coex_table_with_type(काष्ठा btc_coexist *btcoexist,
					      bool क्रमce_exec, u8 type)
अणु
	चयन (type) अणु
	हाल 0:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x55555555, 0xffffff, 0x3);
		अवरोध;
	हाल 1:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 2:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0x5a5a5a5a,
					0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 3:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0x5a5a5a5a,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	हाल 4:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 5:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0x5a5a5a5a,
					0xaaaa5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 6:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0xaaaa5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 7:
		btc8821a1ant_coex_table(btcoexist, क्रमce_exec, 0xaaaaaaaa,
					0xaaaaaaaa, 0xffffff, 0x3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_set_fw_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
						bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	अगर (enable)
		h2c_parameter[0] |= BIT0; /* function enable */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], set FW for BT Ignore Wlan_Act, FW write 0x63 = 0x%x\n",
		h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x63, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8821a1ant_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
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
	btc8821a1ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
पूर्ण

अटल व्योम btc8821a1ant_set_fw_ps_tdma(काष्ठा btc_coexist *btcoexist, u8 byte1,
					u8 byte2, u8 byte3, u8 byte4, u8 byte5)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[5] = अणु0पूर्ण;
	u8 real_byte1 = byte1, real_byte5 = byte5;
	bool ap_enable = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);

	अगर (ap_enable) अणु
		अगर (byte1 & BIT4 && !(byte1 & BIT5)) अणु
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

अटल व्योम btc8821a1ant_set_lps_rpwm(काष्ठा btc_coexist *btcoexist,
				      u8 lps_val, u8 rpwm_val)
अणु
	u8 lps = lps_val;
	u8 rpwm = rpwm_val;

	btcoexist->btc_set(btcoexist, BTC_SET_U1_LPS_VAL, &lps);
	btcoexist->btc_set(btcoexist, BTC_SET_U1_RPWM_VAL, &rpwm);
पूर्ण

अटल व्योम btc8821a1ant_lps_rpwm(काष्ठा btc_coexist *btcoexist,
				  bool क्रमce_exec, u8 lps_val, u8 rpwm_val)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s set lps/rpwm = 0x%x/0x%x\n",
		(क्रमce_exec ? "force to" : ""), lps_val, rpwm_val);
	coex_dm->cur_lps = lps_val;
	coex_dm->cur_rpwm = rpwm_val;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], LPS-RxBeaconMode = 0x%x, LPS-RPWM = 0x%x!!\n",
			coex_dm->cur_lps, coex_dm->cur_rpwm);

		अगर ((coex_dm->pre_lps == coex_dm->cur_lps) &&
		    (coex_dm->pre_rpwm == coex_dm->cur_rpwm)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], LPS-RPWM_Last = 0x%x, LPS-RPWM_Now = 0x%x!!\n",
				coex_dm->pre_rpwm, coex_dm->cur_rpwm);

			वापस;
		पूर्ण
	पूर्ण
	btc8821a1ant_set_lps_rpwm(btcoexist, lps_val, rpwm_val);

	coex_dm->pre_lps = coex_dm->cur_lps;
	coex_dm->pre_rpwm = coex_dm->cur_rpwm;
पूर्ण

अटल व्योम btc8821a1ant_sw_mechanism(काष्ठा btc_coexist *btcoexist,
				      bool low_penalty_ra)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], SM[LpRA] = %d\n", low_penalty_ra);

	btc8821a1ant_low_penalty_ra(btcoexist, NORMAL_EXEC, low_penalty_ra);
पूर्ण

अटल व्योम btc8821a1ant_set_ant_path(काष्ठा btc_coexist *btcoexist,
				      u8 ant_pos_type, bool init_hw_cfg,
				      bool wअगरi_off)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	u32 u4_पंचांगp = 0;
	u8 h2c_parameter[2] = अणु0पूर्ण;

	अगर (init_hw_cfg) अणु
		/* 0x4c[23] = 0, 0x4c[24] = 1  Antenna control by WL/BT */
		u4_पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
		u4_पंचांगp &= ~BIT23;
		u4_पंचांगp |= BIT24;
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u4_पंचांगp);

		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x975, 0x3, 0x3);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xcb4, 0x77);

		अगर (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT) अणु
			/* tell firmware "antenna inverse"
			 * WRONG firmware antenna control code, need fw to fix
			 */
			h2c_parameter[0] = 1;
			h2c_parameter[1] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
						h2c_parameter);
		पूर्ण अन्यथा अणु
			/* tell firmware "no antenna inverse"
			 * WRONG firmware antenna control code, need fw to fix
			 */
			h2c_parameter[0] = 0;
			h2c_parameter[1] = 1;
			btcoexist->btc_fill_h2c(btcoexist, 0x65, 2,
						h2c_parameter);
		पूर्ण
	पूर्ण अन्यथा अगर (wअगरi_off) अणु
		/* 0x4c[24:23] = 00, Set Antenna control
		 * by BT_RFE_CTRL BT Venकरोr 0xac = 0xf002
		 */
		u4_पंचांगp = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
		u4_पंचांगp &= ~BIT23;
		u4_पंचांगp &= ~BIT24;
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x4c, u4_पंचांगp);

		/* 0x765 = 0x18 */
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x765, 0x18, 0x3);
	पूर्ण अन्यथा अणु
		/* 0x765 = 0x0 */
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x765, 0x18, 0x0);
	पूर्ण

	/* ext चयन setting */
	चयन (ant_pos_type) अणु
	हाल BTC_ANT_PATH_WIFI:
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xcb4, 0x77);
		अगर (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT)
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7,
							   0x30, 0x1);
		अन्यथा
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7,
							   0x30, 0x2);
		अवरोध;
	हाल BTC_ANT_PATH_BT:
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xcb4, 0x77);
		अगर (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT)
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7,
							   0x30, 0x2);
		अन्यथा
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7,
							   0x30, 0x1);
		अवरोध;
	शेष:
	हाल BTC_ANT_PATH_PTA:
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xcb4, 0x66);
		अगर (board_info->btdm_ant_pos == BTC_ANTENNA_AT_MAIN_PORT)
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7,
							   0x30, 0x1);
		अन्यथा
			btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xcb7,
							   0x30, 0x2);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_ps_tdma(काष्ठा btc_coexist *btcoexist,
				 bool क्रमce_exec, bool turn_on, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 rssi_adjust_val = 0;

	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

	अगर (!क्रमce_exec) अणु
		अगर (coex_dm->cur_ps_tdma_on) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** TDMA(on, %d) **********\n",
				coex_dm->cur_ps_tdma);
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ********** TDMA(off, %d) **********\n",
				coex_dm->cur_ps_tdma);
		पूर्ण
		अगर ((coex_dm->pre_ps_tdma_on == coex_dm->cur_ps_tdma_on) &&
		    (coex_dm->pre_ps_tdma == coex_dm->cur_ps_tdma))
			वापस;
	पूर्ण
	अगर (turn_on) अणु
		चयन (type) अणु
		शेष:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x1a,
						    0x1a, 0x0, 0x50);
			अवरोध;
		हाल 1:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x3a,
						    0x03, 0x10, 0x50);
			rssi_adjust_val = 11;
			अवरोध;
		हाल 2:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x2b,
						    0x03, 0x10, 0x50);
			rssi_adjust_val = 14;
			अवरोध;
		हाल 3:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x1d,
						    0x1d, 0x0, 0x10);
			अवरोध;
		हाल 4:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x15,
						    0x3, 0x14, 0x0);
			rssi_adjust_val = 17;
			अवरोध;
		हाल 5:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x15,
						    0x3, 0x11, 0x10);
			अवरोध;
		हाल 6:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x20,
						    0x3, 0x11, 0x13);
			अवरोध;
		हाल 7:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xc,
						    0x5, 0x0, 0x0);
			अवरोध;
		हाल 8:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x25,
						    0x3, 0x10, 0x0);
			अवरोध;
		हाल 9:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x21,
						    0x3, 0x10, 0x50);
			rssi_adjust_val = 18;
			अवरोध;
		हाल 10:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xa,
						    0xa, 0x0, 0x40);
			अवरोध;
		हाल 11:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x15,
						    0x03, 0x10, 0x50);
			rssi_adjust_val = 20;
			अवरोध;
		हाल 12:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x0a,
						    0x0a, 0x0, 0x50);
			अवरोध;
		हाल 13:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x12,
						    0x12, 0x0, 0x50);
			अवरोध;
		हाल 14:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x1e,
						    0x3, 0x10, 0x14);
			अवरोध;
		हाल 15:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x13, 0xa,
						    0x3, 0x8, 0x0);
			अवरोध;
		हाल 16:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x15,
						    0x3, 0x10, 0x0);
			rssi_adjust_val = 18;
			अवरोध;
		हाल 18:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x93, 0x25,
						    0x3, 0x10, 0x0);
			rssi_adjust_val = 14;
			अवरोध;
		हाल 20:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x35,
						    0x03, 0x11, 0x10);
			अवरोध;
		हाल 21:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x25,
						    0x03, 0x11, 0x11);
			अवरोध;
		हाल 22:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x25,
						    0x03, 0x11, 0x10);
			अवरोध;
		हाल 23:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x3, 0x31, 0x18);
			rssi_adjust_val = 22;
			अवरोध;
		हाल 24:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x3, 0x31, 0x18);
			rssi_adjust_val = 22;
			अवरोध;
		हाल 25:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0xa,
						    0x3, 0x31, 0x18);
			rssi_adjust_val = 22;
			अवरोध;
		हाल 26:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0xa,
						    0x3, 0x31, 0x18);
			rssi_adjust_val = 22;
			अवरोध;
		हाल 27:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x3, 0x31, 0x98);
			rssi_adjust_val = 22;
			अवरोध;
		हाल 28:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x69, 0x25,
						    0x3, 0x31, 0x0);
			अवरोध;
		हाल 29:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xab, 0x1a,
						    0x1a, 0x1, 0x10);
			अवरोध;
		हाल 30:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x30,
						    0x3, 0x10, 0x10);
			अवरोध;
		हाल 31:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x1a,
						    0x1a, 0, 0x58);
			अवरोध;
		हाल 32:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x61, 0x35,
						    0x3, 0x11, 0x11);
			अवरोध;
		हाल 33:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x25,
						    0x3, 0x30, 0x90);
			अवरोध;
		हाल 34:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x53, 0x1a,
						    0x1a, 0x0, 0x10);
			अवरोध;
		हाल 35:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x63, 0x1a,
						    0x1a, 0x0, 0x10);
			अवरोध;
		हाल 36:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0xd3, 0x12,
						    0x3, 0x14, 0x50);
			अवरोध;
		हाल 40:
			/* SoftAP only with no sta associated, BT disable, TDMA
			 * mode क्रम घातer saving
			 *
			 * here softap mode screen off will cost 70-80mA क्रम
			 * phone
			 */
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x23, 0x18,
						    0x00, 0x10, 0x24);
			अवरोध;
		हाल 41:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x15,
						    0x3, 0x11, 0x11);
			अवरोध;
		हाल 42:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x20,
						    0x3, 0x11, 0x11);
			अवरोध;
		हाल 43:
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x51, 0x30,
						    0x3, 0x10, 0x11);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable PS tdma */
		चयन (type) अणु
		हाल 8:
			/* PTA Control */
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x8, 0x0, 0x0,
						    0x0, 0x0);
			btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
						  false, false);
			अवरोध;
		हाल 0:
		शेष:
			/* Software control, Antenna at BT side */
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x0, 0x0);
			btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT,
						  false, false);
			अवरोध;
		हाल 9:
			/* Software control, Antenna at WiFi side */
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x0, 0x0);
			btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_WIFI,
						  false, false);
			अवरोध;
		हाल 10:
			/* under 5G */
			btc8821a1ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x8, 0x0);
			btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT,
						  false, false);
			अवरोध;
		पूर्ण
	पूर्ण
	rssi_adjust_val = 0;
	btcoexist->btc_set(btcoexist,
		 BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE, &rssi_adjust_val);

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
पूर्ण

अटल bool btc8821a1ant_is_common_action(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool common = false, wअगरi_connected = false, wअगरi_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);

	अगर (!wअगरi_connected &&
	    BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDLE ==
	    coex_dm->bt_status) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi non connected-idle + BT non connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	पूर्ण अन्यथा अगर (wअगरi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		    coex_dm->bt_status)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi connected + BT non connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	पूर्ण अन्यथा अगर (!wअगरi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE ==
		    coex_dm->bt_status)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi non connected-idle + BT connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	पूर्ण अन्यथा अगर (wअगरi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE ==
		    coex_dm->bt_status)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi connected + BT connected-idle!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	पूर्ण अन्यथा अगर (!wअगरi_connected &&
		   (BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE !=
		    coex_dm->bt_status)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi non connected-idle + BT Busy!!\n");
		btc8821a1ant_sw_mechanism(btcoexist, false);

		common = true;
	पूर्ण अन्यथा अणु
		अगर (wअगरi_busy) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Wifi Connected-Busy + BT Busy!!\n");
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Wifi Connected-Idle + BT Busy!!\n");
		पूर्ण

		common = false;
	पूर्ण

	वापस common;
पूर्ण

अटल व्योम btc8821a1ant_ps_tdma_check_क्रम_pwr_save(काष्ठा btc_coexist *btcoex,
						    bool new_ps_state)
अणु
	u8 lps_mode = 0x0;

	btcoex->btc_get(btcoex, BTC_GET_U1_LPS_MODE, &lps_mode);

	अगर (lps_mode) अणु
		/* alपढ़ोy under LPS state */
		अगर (new_ps_state) अणु
			/* keep state under LPS, करो nothing */
		पूर्ण अन्यथा अणु
			/* will leave LPS state, turn off psTdma first */
			btc8821a1ant_ps_tdma(btcoex, NORMAL_EXEC, false, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* NO PS state*/
		अगर (new_ps_state) अणु
			/* will enter LPS state, turn off psTdma first */
			btc8821a1ant_ps_tdma(btcoex, NORMAL_EXEC, false, 0);
		पूर्ण अन्यथा अणु
			/* keep state under NO PS state, करो nothing */
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_घातer_save_state(काष्ठा btc_coexist *btcoexist,
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
		अवरोध;
	हाल BTC_PS_LPS_ON:
		btc8821a1ant_ps_tdma_check_क्रम_pwr_save(btcoexist,
							true);
		btc8821a1ant_lps_rpwm(btcoexist, NORMAL_EXEC, lps_val,
				      rpwm_val);
		/* when coex क्रमce to enter LPS, करो not enter 32k low घातer */
		low_pwr_disable = true;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);
		/* घातer save must executed beक्रमe psTdma */
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_ENTER_LPS, शून्य);
		अवरोध;
	हाल BTC_PS_LPS_OFF:
		btc8821a1ant_ps_tdma_check_क्रम_pwr_save(btcoexist, false);
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_LEAVE_LPS, शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_coex_under_5g(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
				      0x0, 0x0);
	btc8821a1ant_ignore_wlan_act(btcoexist, NORMAL_EXEC, true);

	btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 10);

	btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);

	btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);

	btc8821a1ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 5);
पूर्ण

/***********************************************
 *
 *	Software Coex Mechanism start
 *
 ***********************************************/

/* SCO only or SCO+PAN(HS) */
अटल व्योम btc8821a1ant_action_sco(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, true);
पूर्ण

अटल व्योम btc8821a1ant_action_hid(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, true);
पूर्ण

/* A2DP only / PAN(EDR) only/ A2DP+PAN(HS) */
अटल व्योम btc8821a1ant_action_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, false);
पूर्ण

अटल व्योम btc8821a1ant_action_a2dp_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, false);
पूर्ण

अटल व्योम btc8821a1ant_action_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, false);
पूर्ण

/* PAN(HS) only */
अटल व्योम btc8821a1ant_action_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, false);
पूर्ण

/* PAN(EDR)+A2DP */
अटल व्योम btc8821a1ant_action_pan_edr_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, false);
पूर्ण

अटल व्योम btc8821a1ant_action_pan_edr_hid(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, true);
पूर्ण

/* HID+A2DP+PAN(EDR) */
अटल व्योम btc8821a1ant_action_hid_a2dp_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, true);
पूर्ण

अटल व्योम btc8821a1ant_action_hid_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_sw_mechanism(btcoexist, true);
पूर्ण

/***********************************************
 *
 *	Non-Software Coex Mechanism start
 *
 ***********************************************/
अटल
व्योम btc8821a1ant_action_wअगरi_multi_port(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	/* tdma and coex table */
	अगर (coex_dm->bt_status == BT_8821A_1ANT_BT_STATUS_ACL_BUSY) अणु
		अगर (bt_link_info->a2dp_exist) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
		पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist &&
			   bt_link_info->pan_exist) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 4);
		पूर्ण अन्यथा अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण अन्यथा अगर ((coex_dm->bt_status == BT_8821A_1ANT_BT_STATUS_SCO_BUSY) ||
		   (BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY ==
		    coex_dm->bt_status)) अणु
		btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
				BT_8821A_1ANT_WIFI_STATUS_CONNECTED_SCAN);
	पूर्ण अन्यथा अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल
व्योम btc8821a1ant_action_wअगरi_not_connected_asso_auth(
					काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0,
				      0x0);

	/* tdma and coex table */
	अगर ((bt_link_info->sco_exist) || (bt_link_info->hid_exist)) अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
	पूर्ण अन्यथा अगर ((bt_link_info->a2dp_exist) || (bt_link_info->pan_exist)) अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण


अटल व्योम btc8821a1ant_action_hs(काष्ठा btc_coexist *btcoexist)
अणु
	btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);
	btc8821a1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 2);
पूर्ण

अटल व्योम btc8821a1ant_action_bt_inquiry(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_connected = false;
	bool ap_enable = false;
	bool wअगरi_busy = false, bt_busy = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	अगर (!wअगरi_connected && !coex_sta->wअगरi_is_high_pri_task) अणु
		btc8821a1ant_घातer_save_state(btcoexist,
					      BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अगर ((bt_link_info->sco_exist) || (bt_link_info->a2dp_exist) ||
		   (bt_link_info->hid_only)) अणु
		/* SCO/HID-only busy */
		btc8821a1ant_घातer_save_state(btcoexist,
					      BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अगर ((bt_link_info->a2dp_exist) && (bt_link_info->hid_exist)) अणु
		/* A2DP+HID busy */
		btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);

		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
	पूर्ण अन्यथा अगर ((bt_link_info->pan_exist) || (wअगरi_busy)) अणु
		btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);

		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 7);
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_act_bt_sco_hid_only_busy(काष्ठा btc_coexist *btcoexist,
						  u8 wअगरi_status)
अणु
	/* tdma and coex table */
	btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);

	btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
पूर्ण

अटल व्योम btc8821a1ant_act_wअगरi_con_bt_acl_busy(काष्ठा btc_coexist *btcoexist,
						  u8 wअगरi_status)
अणु
	u8 bt_rssi_state;

	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	bt_rssi_state = btc8821a1ant_bt_rssi_state(btcoexist, 2, 28, 0);

	अगर (bt_link_info->hid_only) अणु
		/* HID */
		btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
						      wअगरi_status);
		coex_dm->स्वतः_tdma_adjust = false;
		वापस;
	पूर्ण अन्यथा अगर (bt_link_info->a2dp_only) अणु
		/* A2DP */
		अगर (wअगरi_status == BT_8821A_1ANT_WIFI_STATUS_CONNECTED_IDLE) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण अन्यथा अगर ((bt_rssi_state != BTC_RSSI_STATE_HIGH) &&
			   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
		पूर्ण अन्यथा अणु
			/* क्रम low BT RSSI */
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण
	पूर्ण अन्यथा अगर (bt_link_info->hid_exist && bt_link_info->a2dp_exist) अणु
		/* HID+A2DP */
		अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     true, 14);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण अन्यथा अणु
			/*क्रम low BT RSSI*/
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     true, 14);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण

		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
	पूर्ण अन्यथा अगर ((bt_link_info->pan_only) ||
		(bt_link_info->hid_exist && bt_link_info->pan_exist)) अणु
		/* PAN(OPP, FTP), HID+PAN(OPP, FTP) */
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 3);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 6);
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण अन्यथा अगर (((bt_link_info->a2dp_exist) && (bt_link_info->pan_exist)) ||
		   (bt_link_info->hid_exist && bt_link_info->a2dp_exist &&
		    bt_link_info->pan_exist)) अणु
		/* A2DP+PAN(OPP, FTP), HID+A2DP+PAN(OPP, FTP) */
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 43);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण अन्यथा अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 11);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण
पूर्ण

अटल
व्योम btc8821a1ant_action_wअगरi_not_connected(काष्ठा btc_coexist *btcoexist)
अणु
	/* घातer save state */
	btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/* tdma and coex table */
	btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
	btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम btc8821a1ant_act_wअगरi_not_conn_scan(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/* tdma and coex table */
	अगर (coex_dm->bt_status == BT_8821A_1ANT_BT_STATUS_ACL_BUSY) अणु
		अगर (bt_link_info->a2dp_exist) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
		पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist &&
			   bt_link_info->pan_exist) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 22);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 4);
		पूर्ण अन्यथा अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण अन्यथा अगर ((coex_dm->bt_status == BT_8821A_1ANT_BT_STATUS_SCO_BUSY) ||
		   (BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY ==
		    coex_dm->bt_status)) अणु
		btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
				BT_8821A_1ANT_WIFI_STATUS_CONNECTED_SCAN);
	पूर्ण अन्यथा अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल
व्योम btc8821a1ant_action_wअगरi_connected_scan(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	/* घातer save state */
	btc8821a1ant_घातer_save_state(btcoexist,
				      BTC_PS_WIFI_NATIVE, 0x0, 0x0);

	/* tdma and coex table */
	अगर (BT_8821A_1ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) अणु
		अगर (bt_link_info->a2dp_exist) अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
		पूर्ण अन्यथा अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण अन्यथा अगर ((coex_dm->bt_status == BT_8821A_1ANT_BT_STATUS_SCO_BUSY) ||
		   (coex_dm->bt_status ==
		    BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY)) अणु
		btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
			BT_8821A_1ANT_WIFI_STATUS_CONNECTED_SCAN);
	पूर्ण अन्यथा अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_act_wअगरi_conn_sp_pkt(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;

	btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
				      0x0, 0x0);

	/* tdma and coex table */
	अगर ((bt_link_info->sco_exist) || (bt_link_info->hid_exist) ||
	    (bt_link_info->a2dp_exist)) अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 32);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण

	अगर ((bt_link_info->hid_exist) && (bt_link_info->a2dp_exist)) अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 1);
	पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 20);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);
	पूर्ण अन्यथा अणु
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_action_wअगरi_connected(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_busy = false;
	bool scan = false, link = false, roam = false;
	bool under_4way = false;
	bool ap_enable = false;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], CoexForWifiConnect()===>\n");

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_4_WAY_PROGRESS,
			   &under_4way);
	अगर (under_4way) अणु
		btc8821a1ant_act_wअगरi_conn_sp_pkt(btcoexist);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexForWifiConnect(), return for wifi is under 4way<===\n");
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	अगर (scan || link || roam) अणु
		अगर (scan)
			btc8821a1ant_action_wअगरi_connected_scan(btcoexist);
		अन्यथा
			btc8821a1ant_act_wअगरi_conn_sp_pkt(btcoexist);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexForWifiConnect(), return for wifi is under scan<===\n");
		वापस;
	पूर्ण

	/* घातer save state*/
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	अगर (BT_8821A_1ANT_BT_STATUS_ACL_BUSY ==
	    coex_dm->bt_status && !ap_enable &&
	    !btcoexist->bt_link_info.hid_only) अणु
		अगर (!wअगरi_busy && btcoexist->bt_link_info.a2dp_only)
			/* A2DP */
			btc8821a1ant_घातer_save_state(btcoexist,
						BTC_PS_WIFI_NATIVE, 0x0, 0x0);
		अन्यथा
			btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_LPS_ON,
						      0x50, 0x4);
	पूर्ण अन्यथा अणु
		btc8821a1ant_घातer_save_state(btcoexist,
					      BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
	पूर्ण

	/* tdma and coex table */
	अगर (!wअगरi_busy) अणु
		अगर (BT_8821A_1ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) अणु
			btc8821a1ant_act_wअगरi_con_bt_acl_busy(btcoexist,
				BT_8821A_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		पूर्ण अन्यथा अगर ((BT_8821A_1ANT_BT_STATUS_SCO_BUSY ==
			    coex_dm->bt_status) ||
			   (BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY ==
			    coex_dm->bt_status)) अणु
			btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
				BT_8821A_1ANT_WIFI_STATUS_CONNECTED_IDLE);
		पूर्ण अन्यथा अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 2);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (BT_8821A_1ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) अणु
			btc8821a1ant_act_wअगरi_con_bt_acl_busy(btcoexist,
				BT_8821A_1ANT_WIFI_STATUS_CONNECTED_BUSY);
		पूर्ण अन्यथा अगर ((BT_8821A_1ANT_BT_STATUS_SCO_BUSY ==
			    coex_dm->bt_status) ||
			   (BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY ==
			    coex_dm->bt_status)) अणु
			btc8821a1ant_act_bt_sco_hid_only_busy(btcoexist,
				BT_8821A_1ANT_WIFI_STATUS_CONNECTED_BUSY);
		पूर्ण अन्यथा अणु
			btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 8);
			btc8821a1ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 2);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_run_sw_coex_mech(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 algorithm = 0;

	algorithm = btc8821a1ant_action_algorithm(btcoexist);
	coex_dm->cur_algorithm = algorithm;

	अगर (!btc8821a1ant_is_common_action(btcoexist)) अणु
		चयन (coex_dm->cur_algorithm) अणु
		हाल BT_8821A_1ANT_COEX_ALGO_SCO:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = SCO\n");
			btc8821a1ant_action_sco(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = HID\n");
			btc8821a1ant_action_hid(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = A2DP\n");
			btc8821a1ant_action_a2dp(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_A2DP_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = A2DP+PAN(HS)\n");
			btc8821a1ant_action_a2dp_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = PAN(EDR)\n");
			btc8821a1ant_action_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = HS mode\n");
			btc8821a1ant_action_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_PANEDR_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = PAN+A2DP\n");
			btc8821a1ant_action_pan_edr_a2dp(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_PANEDR_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = PAN(EDR)+HID\n");
			btc8821a1ant_action_pan_edr_hid(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_HID_A2DP_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = HID+A2DP+PAN\n");
			btc8821a1ant_action_hid_a2dp_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8821A_1ANT_COEX_ALGO_HID_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = HID+A2DP\n");
			btc8821a1ant_action_hid_a2dp(btcoexist);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Action algorithm = coexist All Off!!\n");
			/*btc8821a1ant_coex_all_off(btcoexist);*/
			अवरोध;
		पूर्ण
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_run_coexist_mechanism(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool wअगरi_connected = false, bt_hs_on = false;
	bool increase_scan_dev_num = false;
	bool bt_ctrl_agg_buf_size = false;
	u8 agg_buf_size = 5;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	bool wअगरi_under_5g = false;

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

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	अगर ((BT_8821A_1ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) ||
	    (BT_8821A_1ANT_BT_STATUS_SCO_BUSY == coex_dm->bt_status) ||
	    (BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY == coex_dm->bt_status))
		increase_scan_dev_num = true;

	btcoexist->btc_set(btcoexist, BTC_SET_BL_INC_SCAN_DEV_NUM,
			   &increase_scan_dev_num);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;
	अगर ((num_of_wअगरi_link >= 2) ||
	    (wअगरi_link_status & WIFI_P2P_GO_CONNECTED)) अणु
		btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		btc8821a1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					bt_ctrl_agg_buf_size, agg_buf_size);
		btc8821a1ant_action_wअगरi_multi_port(btcoexist);
		वापस;
	पूर्ण

	अगर (!bt_link_info->sco_exist && !bt_link_info->hid_exist) अणु
		btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
	पूर्ण अन्यथा अणु
		अगर (wअगरi_connected) अणु
			btc8821a1ant_wअगरi_rssi_state(btcoexist, 1, 2,
							     30, 0);
			btc8821a1ant_limited_tx(btcoexist,
						NORMAL_EXEC, 1, 1,
						0, 1);
		पूर्ण अन्यथा अणु
			btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC,
						0, 0, 0, 0);
		पूर्ण
	पूर्ण

	अगर (bt_link_info->sco_exist) अणु
		bt_ctrl_agg_buf_size = true;
		agg_buf_size = 0x3;
	पूर्ण अन्यथा अगर (bt_link_info->hid_exist) अणु
		bt_ctrl_agg_buf_size = true;
		agg_buf_size = 0x5;
	पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist || bt_link_info->pan_exist) अणु
		bt_ctrl_agg_buf_size = true;
		agg_buf_size = 0x8;
	पूर्ण
	btc8821a1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
				bt_ctrl_agg_buf_size, agg_buf_size);

	btc8821a1ant_run_sw_coex_mech(btcoexist);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		btc8821a1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		btc8821a1ant_action_hs(btcoexist);
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
				btc8821a1ant_act_wअगरi_not_conn_scan(btcoexist);
			अन्यथा
				btc8821a1ant_action_wअगरi_not_connected_asso_auth(
					btcoexist);
		पूर्ण अन्यथा अणु
			btc8821a1ant_action_wअगरi_not_connected(btcoexist);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* wअगरi LPS/Busy */
		btc8821a1ant_action_wअगरi_connected(btcoexist);
	पूर्ण
पूर्ण

अटल व्योम btc8821a1ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	/* क्रमce to reset coex mechanism
	 * sw all off
	 */
	btc8821a1ant_sw_mechanism(btcoexist, false);

	btc8821a1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);
पूर्ण

अटल व्योम btc8821a1ant_init_hw_config(काष्ठा btc_coexist *btcoexist,
					bool back_up, bool wअगरi_only)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 u1_पंचांगp = 0;
	bool wअगरi_under_5g = false;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], 1Ant Init HW Config!!\n");

	अगर (wअगरi_only)
		वापस;

	अगर (back_up) अणु
		coex_dm->backup_arfr_cnt1 = btcoexist->btc_पढ़ो_4byte(btcoexist,
								      0x430);
		coex_dm->backup_arfr_cnt2 = btcoexist->btc_पढ़ो_4byte(btcoexist,
								      0x434);
		coex_dm->backup_retry_limit =
			btcoexist->btc_पढ़ो_2byte(btcoexist, 0x42a);
		coex_dm->backup_ampdu_max_समय =
			btcoexist->btc_पढ़ो_1byte(btcoexist, 0x456);
	पूर्ण

	/* 0x790[5:0] = 0x5 */
	u1_पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x790);
	u1_पंचांगp &= 0xc0;
	u1_पंचांगp |= 0x5;
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x790, u1_पंचांगp);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);

	/* Antenna config */
	अगर (wअगरi_under_5g)
		btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT,
					  true, false);
	अन्यथा
		btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_PTA,
					  true, false);
	/* PTA parameter */
	btc8821a1ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);

	/* Enable counter statistics
	 * 0x76e[3] =1, WLAN_Act control by PTA
	 */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0xc);
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x778, 0x3);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x40, 0x20, 0x1);
पूर्ण

/**************************************************************
 * बाह्य function start with ex_btc8821a1ant_
 **************************************************************/
व्योम ex_btc8821a1ant_init_hwconfig(काष्ठा btc_coexist *btcoexist, bool wअगरionly)
अणु
	btc8821a1ant_init_hw_config(btcoexist, true, wअगरionly);
	btcoexist->स्वतः_report_1ant = true;
पूर्ण

व्योम ex_btc8821a1ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Coex Mechanism Init!!\n");

	btcoexist->stop_coex_dm = false;

	btc8821a1ant_init_coex_dm(btcoexist);

	btc8821a1ant_query_bt_info(btcoexist);
पूर्ण

व्योम ex_btc8821a1ant_display_coex_info(काष्ठा btc_coexist *btcoexist,
				       काष्ठा seq_file *m)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	u8 u1_पंचांगp[4], i, bt_info_ext, ps_tdma_हाल = 0;
	u16 u2_पंचांगp[4];
	u32 u4_पंचांगp[4];
	bool roam = false, scan = false, link = false, wअगरi_under_5g = false;
	bool bt_hs_on = false, wअगरi_busy = false;
	दीर्घ wअगरi_rssi = 0, bt_hs_rssi = 0;
	u32 wअगरi_bw, wअगरi_traffic_dir;
	u8 wअगरi_करोt11_chnl, wअगरi_hs_chnl;
	u32 fw_ver = 0, bt_patch_ver = 0;

	seq_माला_दो(m, "\n ============[BT Coexist info]============");

	अगर (btcoexist->manual_control) अणु
		seq_माला_दो(m, "\n ============[Under Manual Control]============");
		seq_माला_दो(m, "\n ==========================================");
	पूर्ण
	अगर (btcoexist->stop_coex_dm) अणु
		seq_माला_दो(m, "\n ============[Coex is STOPPED]============");
		seq_माला_दो(m, "\n ==========================================");
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d",
		   "Ant PG Num/ Ant Mech/ Ant Pos:",
		   board_info->pg_ant_num,
		   board_info->btdm_ant_num,
		   board_info->btdm_ant_pos);

	seq_म_लिखो(m, "\n %-35s = %s / %d", "BT stack/ hci ext ver",
		   ((stack_info->profile_notअगरied) ? "Yes" : "No"),
		   stack_info->hci_version);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER,
			   &bt_patch_ver);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	seq_म_लिखो(m, "\n %-35s = %d_%x/ 0x%x/ 0x%x(%d)",
		   "CoexVer/ FwVer/ PatchVer",
		   glcoex_ver_date_8821a_1ant,
		   glcoex_ver_8821a_1ant,
		   fw_ver, bt_patch_ver,
		   bt_patch_ver);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION,
			   &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_DOT11_CHNL,
			   &wअगरi_करोt11_chnl);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_HS_CHNL,
			   &wअगरi_hs_chnl);
	seq_म_लिखो(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsChnl(HsMode)",
		   wअगरi_करोt11_chnl, wअगरi_hs_chnl, bt_hs_on);

	seq_म_लिखो(m, "\n %-35s = %3ph ",
		   "H2C Wifi inform bt chnl Info",
		   coex_dm->wअगरi_chnl_info);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	seq_म_लिखो(m, "\n %-35s = %d/ %d", "Wifi rssi/ HS rssi",
		   (पूर्णांक)wअगरi_rssi, (पूर्णांक)bt_hs_rssi);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d ", "Wifi link/ roam/ scan",
		   link, roam, scan);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G,
			   &wअगरi_under_5g);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW,
			   &wअगरi_bw);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY,
			   &wअगरi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION,
			   &wअगरi_traffic_dir);
	seq_म_लिखो(m, "\n %-35s = %s / %s/ %s ", "Wifi status",
		   (wअगरi_under_5g ? "5G" : "2.4G"),
		   ((wअगरi_bw == BTC_WIFI_BW_LEGACY) ? "Legacy" :
		   (((wअगरi_bw == BTC_WIFI_BW_HT40) ? "HT40" : "HT20"))),
		   ((!wअगरi_busy) ? "idle" :
		   ((wअगरi_traffic_dir == BTC_WIFI_TRAFFIC_TX) ?
		   "uplink" : "downlink")));
	seq_म_लिखो(m, "\n %-35s = [%s/ %d/ %d] ",
		   "BT [status/ rssi/ retryCnt]",
		   ((coex_sta->bt_disabled) ? ("disabled") :
		   ((coex_sta->c2h_bt_inquiry_page) ? ("inquiry/page scan") :
		   ((BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		     coex_dm->bt_status) ?
		   "non-connected idle" :
		   ((BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE ==
		     coex_dm->bt_status) ?
		   "connected-idle" : "busy")))),
		   coex_sta->bt_rssi, coex_sta->bt_retry_cnt);

	seq_म_लिखो(m, "\n %-35s = %d / %d / %d / %d", "SCO/HID/PAN/A2DP",
		   bt_link_info->sco_exist,
		   bt_link_info->hid_exist,
		   bt_link_info->pan_exist,
		   bt_link_info->a2dp_exist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_BT_LINK_INFO, m);

	bt_info_ext = coex_sta->bt_info_ext;
	seq_म_लिखो(m, "\n %-35s = %s",
		   "BT Info A2DP rate",
		   (bt_info_ext & BIT0) ?
		   "Basic rate" : "EDR rate");

	क्रम (i = 0; i < BT_INFO_SRC_8821A_1ANT_MAX; i++) अणु
		अगर (coex_sta->bt_info_c2h_cnt[i]) अणु
			seq_म_लिखो(m, "\n %-35s = %7ph(%d)",
				   glbt_info_src_8821a_1ant[i],
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
		/* Sw mechanism*/
		seq_म_लिखो(m, "\n %-35s",
			   "============[Sw mechanism]============");

		seq_म_लिखो(m, "\n %-35s = %d", "SM[LowPenaltyRA]",
			   coex_dm->cur_low_penalty_ra);

		seq_म_लिखो(m, "\n %-35s = %s/ %s/ %d ",
			   "DelBA/ BtCtrlAgg/ AggSize",
			   (btcoexist->bt_info.reject_agg_pkt ? "Yes" : "No"),
			   (btcoexist->bt_info.bt_ctrl_buf_size ? "Yes" : "No"),
			   btcoexist->bt_info.agg_buf_size);
		seq_म_लिखो(m, "\n %-35s = 0x%x ", "Rate Mask",
			   btcoexist->bt_info.ra_mask);

		/* Fw mechanism */
		seq_म_लिखो(m, "\n %-35s",
			   "============[Fw mechanism]============");

		ps_tdma_हाल = coex_dm->cur_ps_tdma;
		seq_म_लिखो(m, "\n %-35s = %5ph case-%d (auto:%d)",
			   "PS TDMA",
			   coex_dm->ps_tdma_para,
			   ps_tdma_हाल,
			   coex_dm->स्वतः_tdma_adjust);

		seq_म_लिखो(m, "\n %-35s = 0x%x ",
			   "Latest error condition(should be 0)",
			   coex_dm->error_condition);

		seq_म_लिखो(m, "\n %-35s = %d ", "IgnWlanAct",
			   coex_dm->cur_ignore_wlan_act);
	पूर्ण

	/* Hw setting */
	seq_म_लिखो(m, "\n %-35s", "============[Hw setting]============");

	seq_म_लिखो(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "backup ARFR1/ARFR2/RL/AMaxTime",
		   coex_dm->backup_arfr_cnt1,
		   coex_dm->backup_arfr_cnt2,
		   coex_dm->backup_retry_limit,
		   coex_dm->backup_ampdu_max_समय);

	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x430);
	u4_पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x434);
	u2_पंचांगp[0] = btcoexist->btc_पढ़ो_2byte(btcoexist, 0x42a);
	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x456);
	seq_म_लिखो(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "0x430/0x434/0x42a/0x456",
		   u4_पंचांगp[0], u4_पंचांगp[1], u2_पंचांगp[0], u1_पंचांगp[0]);

	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x778);
	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xc58);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x", "0x778/ 0xc58[29:25]",
		   u1_पंचांगp[0], (u4_पंचांगp[0] & 0x3e000000) >> 25);

	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x8db);
	seq_म_लिखो(m, "\n %-35s = 0x%x", "0x8db[6:5]",
		   ((u1_पंचांगp[0] & 0x60) >> 5));

	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x975);
	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xcb4);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0xcb4[29:28]/0xcb4[7:0]/0x974[9:8]",
		   (u4_पंचांगp[0] & 0x30000000) >> 28,
		    u4_पंचांगp[0] & 0xff,
		    u1_पंचांगp[0] & 0x3);

	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x40);
	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x4c);
	u1_पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x64);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0x40/0x4c[24:23]/0x64[0]",
		   u1_पंचांगp[0], ((u4_पंचांगp[0] & 0x01800000) >> 23),
		   u1_पंचांगp[1] & 0x1);

	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x550);
	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x522);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x", "0x550(bcn ctrl)/0x522",
		   u4_पंचांगp[0], u1_पंचांगp[0]);

	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xc50);
	seq_म_लिखो(m, "\n %-35s = 0x%x", "0xc50(dig)",
		   u4_पंचांगp[0] & 0xff);

	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xf48);
	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xa5d);
	u1_पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0xa5c);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x", "OFDM-FA/ CCK-FA",
		   u4_पंचांगp[0], (u1_पंचांगp[0] << 8) + u1_पंचांगp[1]);

	u4_पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c0);
	u4_पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c4);
	u4_पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c8);
	u1_पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x6cc);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
		   "0x6c0/0x6c4/0x6c8/0x6cc(coexTable)",
		   u4_पंचांगp[0], u4_पंचांगp[1], u4_पंचांगp[2], u1_पंचांगp[0]);

	seq_म_लिखो(m, "\n %-35s = %d/ %d", "0x770(high-pri rx/tx)",
		   coex_sta->high_priority_rx, coex_sta->high_priority_tx);
	seq_म_लिखो(m, "\n %-35s = %d/ %d", "0x774(low-pri rx/tx)",
		   coex_sta->low_priority_rx, coex_sta->low_priority_tx);
	अगर (btcoexist->स्वतः_report_1ant)
		btc8821a1ant_monitor_bt_ctr(btcoexist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS, m);
पूर्ण

व्योम ex_btc8821a1ant_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_under_5g = false;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm)
		वापस;
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	अगर (BTC_IPS_ENTER == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		btc8821a1ant_set_ant_path(btcoexist,
					  BTC_ANT_PATH_BT, false, true);
		/* set PTA control */
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
		btc8821a1ant_coex_table_with_type(btcoexist,
						  NORMAL_EXEC, 0);
	पूर्ण अन्यथा अगर (BTC_IPS_LEAVE == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;

		btc8821a1ant_init_hw_config(btcoexist, false, false);
		btc8821a1ant_init_coex_dm(btcoexist);
		btc8821a1ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8821a1ant_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
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

व्योम ex_btc8821a1ant_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_connected = false, bt_hs_on = false;
	bool bt_ctrl_agg_buf_size = false;
	bool wअगरi_under_5g = false;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	u8 agg_buf_size = 5;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm)
		वापस;
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	अगर (type == BTC_SCAN_START) अणु
		coex_sta->wअगरi_is_high_pri_task = true;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN START notify\n");

		/* Force antenna setup क्रम no scan result issue */
		btc8821a1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 8);
	पूर्ण अन्यथा अणु
		coex_sta->wअगरi_is_high_pri_task = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN FINISH notify\n");
	पूर्ण

	अगर (coex_sta->bt_disabled)
		वापस;

	btcoexist->btc_get(btcoexist,
		 BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist,
		 BTC_GET_BL_WIFI_CONNECTED, &wअगरi_connected);

	btc8821a1ant_query_bt_info(btcoexist);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;
	अगर (num_of_wअगरi_link >= 2) अणु
		btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		btc8821a1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					bt_ctrl_agg_buf_size, agg_buf_size);
		btc8821a1ant_action_wअगरi_multi_port(btcoexist);
		वापस;
	पूर्ण

	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		btc8821a1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		btc8821a1ant_action_hs(btcoexist);
		वापस;
	पूर्ण

	अगर (BTC_SCAN_START == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN START notify\n");
		अगर (!wअगरi_connected) अणु
			/* non-connected scan */
			btc8821a1ant_act_wअगरi_not_conn_scan(btcoexist);
		पूर्ण अन्यथा अणु
			/* wअगरi is connected */
			btc8821a1ant_action_wअगरi_connected_scan(btcoexist);
		पूर्ण
	पूर्ण अन्यथा अगर (BTC_SCAN_FINISH == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN FINISH notify\n");
		अगर (!wअगरi_connected) अणु
			/* non-connected scan */
			btc8821a1ant_action_wअगरi_not_connected(btcoexist);
		पूर्ण अन्यथा अणु
			btc8821a1ant_action_wअगरi_connected(btcoexist);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ex_btc8821a1ant_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_connected = false, bt_hs_on = false;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	bool bt_ctrl_agg_buf_size = false;
	bool wअगरi_under_5g = false;
	u8 agg_buf_size = 5;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		वापस;
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	अगर (type == BTC_ASSOCIATE_START) अणु
		coex_sta->wअगरi_is_high_pri_task = true;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT START notify\n");
		coex_dm->arp_cnt = 0;
	पूर्ण अन्यथा अणु
		coex_sta->wअगरi_is_high_pri_task = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT FINISH notify\n");
		coex_dm->arp_cnt = 0;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;
	अगर (num_of_wअगरi_link >= 2) अणु
		btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		btc8821a1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					bt_ctrl_agg_buf_size, agg_buf_size);
		btc8821a1ant_action_wअगरi_multi_port(btcoexist);
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		btc8821a1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		btc8821a1ant_action_hs(btcoexist);
		वापस;
	पूर्ण

	अगर (BTC_ASSOCIATE_START == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT START notify\n");
		btc8821a1ant_act_wअगरi_not_conn_scan(btcoexist);
	पूर्ण अन्यथा अगर (BTC_ASSOCIATE_FINISH == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT FINISH notify\n");

		btcoexist->btc_get(btcoexist,
			 BTC_GET_BL_WIFI_CONNECTED, &wअगरi_connected);
		अगर (!wअगरi_connected) अणु
			/* non-connected scan */
			btc8821a1ant_action_wअगरi_not_connected(btcoexist);
		पूर्ण अन्यथा अणु
			btc8821a1ant_action_wअगरi_connected(btcoexist);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ex_btc8821a1ant_media_status_notअगरy(काष्ठा btc_coexist *btcoexist,
					 u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[3] = अणु0पूर्ण;
	u32 wअगरi_bw;
	u8 wअगरi_central_chnl;
	bool wअगरi_under_5g = false;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		वापस;
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	अगर (BTC_MEDIA_CONNECT == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA connect notify\n");
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA disconnect notify\n");
		coex_dm->arp_cnt = 0;
	पूर्ण

	/* only 2.4G we need to inक्रमm bt the chnl mask */
	btcoexist->btc_get(btcoexist,
			   BTC_GET_U1_WIFI_CENTRAL_CHNL,
			   &wअगरi_central_chnl);
	अगर ((type == BTC_MEDIA_CONNECT) &&
	    (wअगरi_central_chnl <= 14)) अणु
		h2c_parameter[0] = 0x0;
		h2c_parameter[1] = wअगरi_central_chnl;
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
		अगर (wअगरi_bw == BTC_WIFI_BW_HT40)
			h2c_parameter[2] = 0x30;
		अन्यथा
			h2c_parameter[2] = 0x20;
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

व्योम ex_btc8821a1ant_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist,
					   u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool bt_hs_on = false;
	bool bt_ctrl_agg_buf_size = false;
	bool wअगरi_under_5g = false;
	u32 wअगरi_link_status = 0;
	u32 num_of_wअगरi_link = 0;
	u8 agg_buf_size = 5;

	अगर (btcoexist->manual_control || btcoexist->stop_coex_dm ||
	    coex_sta->bt_disabled)
		वापस;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	अगर (type == BTC_PACKET_DHCP || type == BTC_PACKET_EAPOL ||
	    type == BTC_PACKET_ARP) अणु
		coex_sta->wअगरi_is_high_pri_task = true;

		अगर (type == BTC_PACKET_ARP) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], specific Packet ARP notify\n");
		पूर्ण अन्यथा अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], specific Packet DHCP or EAPOL notify\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		coex_sta->wअगरi_is_high_pri_task = false;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], specific Packet [Type = %d] notify\n",
			type);
	पूर्ण

	coex_sta->special_pkt_period_cnt = 0;

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_LINK_STATUS,
			   &wअगरi_link_status);
	num_of_wअगरi_link = wअगरi_link_status >> 16;
	अगर (num_of_wअगरi_link >= 2) अणु
		btc8821a1ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);
		btc8821a1ant_limited_rx(btcoexist, NORMAL_EXEC, false,
					bt_ctrl_agg_buf_size, agg_buf_size);
		btc8821a1ant_action_wअगरi_multi_port(btcoexist);
		वापस;
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	अगर (coex_sta->c2h_bt_inquiry_page) अणु
		btc8821a1ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण अन्यथा अगर (bt_hs_on) अणु
		btc8821a1ant_action_hs(btcoexist);
		वापस;
	पूर्ण

	अगर (type == BTC_PACKET_DHCP || type == BTC_PACKET_EAPOL ||
	    type == BTC_PACKET_ARP) अणु
		अगर (type == BTC_PACKET_ARP) अणु
			coex_dm->arp_cnt++;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], ARP Packet Count = %d\n",
				coex_dm->arp_cnt);
			अगर (coex_dm->arp_cnt >= 10)
				/* अगर APR PKT > 10 after connect, करो not go to
				 * btc8821a1ant_act_wअगरi_conn_sp_pkt
				 */
				वापस;
		पूर्ण

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], special Packet(%d) notify\n", type);
		btc8821a1ant_act_wअगरi_conn_sp_pkt(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8821a1ant_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist,
				    u8 *पंचांगp_buf, u8 length)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 i;
	u8 bt_info = 0;
	u8 rsp_source = 0;
	bool wअगरi_connected = false;
	bool bt_busy = false;
	bool wअगरi_under_5g = false;

	coex_sta->c2h_bt_info_req_sent = false;

	btcoexist->btc_get(btcoexist,
		 BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);

	rsp_source = पंचांगp_buf[0] & 0xf;
	अगर (rsp_source >= BT_INFO_SRC_8821A_1ANT_MAX)
		rsp_source = BT_INFO_SRC_8821A_1ANT_WIFI_FW;
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

	अगर (BT_INFO_SRC_8821A_1ANT_WIFI_FW != rsp_source) अणु
		/* [3:0] */
		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2] & 0xf;

		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->bt_info_ext = coex_sta->bt_info_c2h[rsp_source][4];

		coex_sta->bt_tx_rx_mask =
			(coex_sta->bt_info_c2h[rsp_source][2] & 0x40);
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TX_RX_MASK,
				   &coex_sta->bt_tx_rx_mask);
		अगर (!coex_sta->bt_tx_rx_mask) अणु
			/* BT पूर्णांकo is responded by BT FW and BT RF REG 0x3C !=
			 * 0x15 => Need to चयन BT TRx Mask
			 */
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Switch BT TRx Mask since BT RF REG 0x3C != 0x15\n");
			btcoexist->btc_set_bt_reg(btcoexist, BTC_BT_REG_RF,
						  0x3c, 0x15);
		पूर्ण

		/* Here we need to resend some wअगरi info to BT
		 * because bt is reset and lost the info
		 */
		अगर (coex_sta->bt_info_ext & BIT1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], BT ext info bit1 check, send wifi BW&Chnl to BT!!\n");
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
					   &wअगरi_connected);
			अगर (wअगरi_connected) अणु
				ex_btc8821a1ant_media_status_notअगरy(btcoexist,
							       BTC_MEDIA_CONNECT);
			पूर्ण अन्यथा अणु
				ex_btc8821a1ant_media_status_notअगरy(btcoexist,
							       BTC_MEDIA_DISCONNECT);
			पूर्ण
		पूर्ण

		अगर ((coex_sta->bt_info_ext & BIT3) && !wअगरi_under_5g) अणु
			अगर (!btcoexist->manual_control &&
			    !btcoexist->stop_coex_dm) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex], BT ext info bit3 check, set BT NOT to ignore Wlan active!!\n");
				btc8821a1ant_ignore_wlan_act(btcoexist,
							     FORCE_EXEC,
							     false);
			पूर्ण
		पूर्ण
	पूर्ण

	/* check BIT2 first ==> check अगर bt is under inquiry or page scan */
	अगर (bt_info & BT_INFO_8821A_1ANT_B_INQ_PAGE)
		coex_sta->c2h_bt_inquiry_page = true;
	अन्यथा
		coex_sta->c2h_bt_inquiry_page = false;

	/* set link exist status */
	अगर (!(bt_info & BT_INFO_8821A_1ANT_B_CONNECTION)) अणु
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	पूर्ण अन्यथा अणु
		/* connection exists */
		coex_sta->bt_link_exist = true;
		अगर (bt_info & BT_INFO_8821A_1ANT_B_FTP)
			coex_sta->pan_exist = true;
		अन्यथा
			coex_sta->pan_exist = false;
		अगर (bt_info & BT_INFO_8821A_1ANT_B_A2DP)
			coex_sta->a2dp_exist = true;
		अन्यथा
			coex_sta->a2dp_exist = false;
		अगर (bt_info & BT_INFO_8821A_1ANT_B_HID)
			coex_sta->hid_exist = true;
		अन्यथा
			coex_sta->hid_exist = false;
		अगर (bt_info & BT_INFO_8821A_1ANT_B_SCO_ESCO)
			coex_sta->sco_exist = true;
		अन्यथा
			coex_sta->sco_exist = false;
	पूर्ण

	btc8821a1ant_update_bt_link_info(btcoexist);

	/* mask profile bit क्रम connect-ilde identअगरication
	 * (क्रम CSR हाल: A2DP idle --> 0x41)
	 */
	bt_info = bt_info & 0x1f;

	अगर (!(bt_info & BT_INFO_8821A_1ANT_B_CONNECTION)) अणु
		coex_dm->bt_status = BT_8821A_1ANT_BT_STATUS_NON_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Connected idle!!!\n");
	पूर्ण अन्यथा अगर (bt_info == BT_INFO_8821A_1ANT_B_CONNECTION) अणु
		/* connection exists but no busy */
		coex_dm->bt_status = BT_8821A_1ANT_BT_STATUS_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Connected-idle!!!\n");
	पूर्ण अन्यथा अगर ((bt_info&BT_INFO_8821A_1ANT_B_SCO_ESCO) ||
		(bt_info & BT_INFO_8821A_1ANT_B_SCO_BUSY)) अणु
		coex_dm->bt_status = BT_8821A_1ANT_BT_STATUS_SCO_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT SCO busy!!!\n");
	पूर्ण अन्यथा अगर (bt_info & BT_INFO_8821A_1ANT_B_ACL_BUSY) अणु
		अगर (BT_8821A_1ANT_BT_STATUS_ACL_BUSY != coex_dm->bt_status)
			coex_dm->स्वतः_tdma_adjust = false;
		coex_dm->bt_status = BT_8821A_1ANT_BT_STATUS_ACL_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT ACL busy!!!\n");
	पूर्ण अन्यथा अणु
		coex_dm->bt_status = BT_8821A_1ANT_BT_STATUS_MAX;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BtInfoNotify(), BT Non-Defined state!!!\n");
	पूर्ण

	अगर ((BT_8821A_1ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) ||
	    (BT_8821A_1ANT_BT_STATUS_SCO_BUSY == coex_dm->bt_status) ||
	    (BT_8821A_1ANT_BT_STATUS_ACL_SCO_BUSY == coex_dm->bt_status))
		bt_busy = true;
	अन्यथा
		bt_busy = false;
	btcoexist->btc_set(btcoexist,
			   BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	btc8821a1ant_run_coexist_mechanism(btcoexist);
पूर्ण

व्योम ex_btc8821a1ant_halt_notअगरy(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_under_5g = false;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Halt notify\n");
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण


	btcoexist->stop_coex_dm = true;

	btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT, false, true);
	btc8821a1ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);

	btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE, 0x0, 0x0);
	btc8821a1ant_ps_tdma(btcoexist, FORCE_EXEC, false, 0);

	ex_btc8821a1ant_media_status_notअगरy(btcoexist, BTC_MEDIA_DISCONNECT);
पूर्ण

व्योम ex_btc8821a1ant_pnp_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pnp_state)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	bool wअगरi_under_5g = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	अगर (wअगरi_under_5g) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], RunCoexistMechanism(), return for 5G <===\n");
		btc8821a1ant_coex_under_5g(btcoexist);
		वापस;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Pnp notify\n");

	अगर (BTC_WIFI_PNP_SLEEP == pnp_state) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to SLEEP\n");
		/* BT should clear UnderIPS/UnderLPS state to aव्योम mismatch
		 * state after wakeup.
		 */
		coex_sta->under_ips = false;
		coex_sta->under_lps = false;
		btcoexist->stop_coex_dm = true;
		btc8821a1ant_घातer_save_state(btcoexist, BTC_PS_WIFI_NATIVE,
					      0x0, 0x0);
		btc8821a1ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
		btc8821a1ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
		btc8821a1ant_set_ant_path(btcoexist, BTC_ANT_PATH_BT, false,
					  true);
	पूर्ण अन्यथा अगर (BTC_WIFI_PNP_WAKE_UP == pnp_state) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Pnp notify to WAKE UP\n");
		btcoexist->stop_coex_dm = false;
		btc8821a1ant_init_hw_config(btcoexist, false, false);
		btc8821a1ant_init_coex_dm(btcoexist);
		btc8821a1ant_query_bt_info(btcoexist);
	पूर्ण
पूर्ण

व्योम ex_btc8821a1ant_periodical(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल u8 dis_ver_info_cnt;
	u32 fw_ver = 0, bt_patch_ver = 0;
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], ==========================Periodical===========================\n");

	अगर (dis_ver_info_cnt <= 5) अणु
		dis_ver_info_cnt += 1;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ****************************************************************\n");
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Ant PG Num/ Ant Mech/ Ant Pos = %d/ %d/ %d\n",
			board_info->pg_ant_num,
			board_info->btdm_ant_num,
			board_info->btdm_ant_pos);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT stack/ hci ext ver = %s / %d\n",
			stack_info->profile_notअगरied ? "Yes" : "No",
			stack_info->hci_version);
		btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER,
				   &bt_patch_ver);
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CoexVer/ FwVer/ PatchVer = %d_%x/ 0x%x/ 0x%x(%d)\n",
			glcoex_ver_date_8821a_1ant,
			glcoex_ver_8821a_1ant,
			fw_ver, bt_patch_ver,
			bt_patch_ver);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], ****************************************************************\n");
	पूर्ण

	अगर (!btcoexist->स्वतः_report_1ant) अणु
		btc8821a1ant_query_bt_info(btcoexist);
		btc8821a1ant_monitor_bt_ctr(btcoexist);
	पूर्ण अन्यथा अणु
		coex_sta->special_pkt_period_cnt++;
	पूर्ण
पूर्ण
