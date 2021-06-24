<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2012  Realtek Corporation.*/

/**************************************************************
 *   include files
 **************************************************************/
#समावेश "halbt_precomp.h"
/**************************************************************
 *   Global variables, these are अटल variables
 **************************************************************/
अटल काष्ठा coex_dm_8192e_2ant glcoex_dm_8192e_2ant;
अटल काष्ठा coex_dm_8192e_2ant *coex_dm = &glcoex_dm_8192e_2ant;
अटल काष्ठा coex_sta_8192e_2ant glcoex_sta_8192e_2ant;
अटल काष्ठा coex_sta_8192e_2ant *coex_sta = &glcoex_sta_8192e_2ant;

अटल स्थिर अक्षर *स्थिर glbt_info_src_8192e_2ant[] = अणु
	"BT Info[wifi fw]",
	"BT Info[bt rsp]",
	"BT Info[bt auto report]",
पूर्ण;

अटल u32 glcoex_ver_date_8192e_2ant = 20130902;
अटल u32 glcoex_ver_8192e_2ant = 0x34;

/**************************************************************
 *   local function proto type अगर needed
 **************************************************************/
/**************************************************************
 *   local function start with btc8192e2ant_
 **************************************************************/
अटल u8 btc8192e2ant_bt_rssi_state(काष्ठा btc_coexist *btcoexist,
				     u8 level_num, u8 rssi_thresh,
				     u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	पूर्णांक bt_rssi = 0;
	u8 bt_rssi_state = coex_sta->pre_bt_rssi_state;

	bt_rssi = coex_sta->bt_rssi;

	अगर (level_num == 2) अणु
		अगर ((coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (bt_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8192E_2ANT))
				bt_rssi_state = BTC_RSSI_STATE_HIGH;
			अन्यथा
				bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		पूर्ण अन्यथा अणु
			अगर (bt_rssi < rssi_thresh)
				bt_rssi_state = BTC_RSSI_STATE_LOW;
			अन्यथा
				bt_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
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
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8192E_2ANT))
				bt_rssi_state = BTC_RSSI_STATE_MEDIUM;
			अन्यथा
				bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		पूर्ण अन्यथा अगर ((coex_sta->pre_bt_rssi_state ==
			    BTC_RSSI_STATE_MEDIUM) ||
			   (coex_sta->pre_bt_rssi_state ==
			    BTC_RSSI_STATE_STAY_MEDIUM)) अणु
			अगर (bt_rssi >= (rssi_thresh1 +
					BTC_RSSI_COEX_THRESH_TOL_8192E_2ANT))
				bt_rssi_state = BTC_RSSI_STATE_HIGH;
			अन्यथा अगर (bt_rssi < rssi_thresh)
				bt_rssi_state = BTC_RSSI_STATE_LOW;
			अन्यथा
				bt_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
		पूर्ण अन्यथा अणु
			अगर (bt_rssi < rssi_thresh1)
				bt_rssi_state = BTC_RSSI_STATE_MEDIUM;
			अन्यथा
				bt_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		पूर्ण
	पूर्ण

	coex_sta->pre_bt_rssi_state = bt_rssi_state;

	वापस bt_rssi_state;
पूर्ण

अटल u8 btc8192e2ant_wअगरi_rssi_state(काष्ठा btc_coexist *btcoexist,
				       u8 index, u8 level_num, u8 rssi_thresh,
				       u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	पूर्णांक wअगरi_rssi = 0;
	u8 wअगरi_rssi_state = coex_sta->pre_wअगरi_rssi_state[index];

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);

	अगर (level_num == 2) अणु
		अगर ((coex_sta->pre_wअगरi_rssi_state[index] ==
		     BTC_RSSI_STATE_LOW) ||
		    (coex_sta->pre_wअगरi_rssi_state[index] ==
		     BTC_RSSI_STATE_STAY_LOW)) अणु
			अगर (wअगरi_rssi >=
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8192E_2ANT))
				wअगरi_rssi_state = BTC_RSSI_STATE_HIGH;
			अन्यथा
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		पूर्ण अन्यथा अणु
			अगर (wअगरi_rssi < rssi_thresh)
				wअगरi_rssi_state = BTC_RSSI_STATE_LOW;
			अन्यथा
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
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
			    (rssi_thresh + BTC_RSSI_COEX_THRESH_TOL_8192E_2ANT))
				wअगरi_rssi_state = BTC_RSSI_STATE_MEDIUM;
			अन्यथा
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_LOW;
		पूर्ण अन्यथा अगर ((coex_sta->pre_wअगरi_rssi_state[index] ==
			    BTC_RSSI_STATE_MEDIUM) ||
			   (coex_sta->pre_wअगरi_rssi_state[index] ==
			    BTC_RSSI_STATE_STAY_MEDIUM)) अणु
			अगर (wअगरi_rssi >= (rssi_thresh1 +
					 BTC_RSSI_COEX_THRESH_TOL_8192E_2ANT))
				wअगरi_rssi_state = BTC_RSSI_STATE_HIGH;
			अन्यथा अगर (wअगरi_rssi < rssi_thresh)
				wअगरi_rssi_state = BTC_RSSI_STATE_LOW;
			अन्यथा
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_MEDIUM;
		पूर्ण अन्यथा अणु
			अगर (wअगरi_rssi < rssi_thresh1)
				wअगरi_rssi_state = BTC_RSSI_STATE_MEDIUM;
			अन्यथा
				wअगरi_rssi_state = BTC_RSSI_STATE_STAY_HIGH;
		पूर्ण
	पूर्ण

	coex_sta->pre_wअगरi_rssi_state[index] = wअगरi_rssi_state;

	वापस wअगरi_rssi_state;
पूर्ण

अटल व्योम btc8192e2ant_monitor_bt_enable_disable(काष्ठा btc_coexist
						   *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल bool pre_bt_disabled;
	अटल u32 bt_disable_cnt;
	bool bt_active = true, bt_disabled = false;

	/* This function check अगर bt is disabled */

	अगर (coex_sta->high_priority_tx == 0 &&
	    coex_sta->high_priority_rx == 0 &&
	    coex_sta->low_priority_tx == 0 &&
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
		btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
				   &bt_disabled);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT is enabled !!\n");
	पूर्ण अन्यथा अणु
		bt_disable_cnt++;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bt all counters = 0, %d times!!\n",
			bt_disable_cnt);
		अगर (bt_disable_cnt >= 2) अणु
			bt_disabled = true;
			btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_DISABLE,
					   &bt_disabled);
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], BT is disabled !!\n");
		पूर्ण
	पूर्ण
	अगर (pre_bt_disabled != bt_disabled) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT is from %s to %s!!\n",
			(pre_bt_disabled ? "disabled" : "enabled"),
			(bt_disabled ? "disabled" : "enabled"));
		pre_bt_disabled = bt_disabled;
	पूर्ण
पूर्ण

अटल u32 btc8192e2ant_decide_ra_mask(काष्ठा btc_coexist *btcoexist,
				       u8 ss_type, u32 ra_mask_type)
अणु
	u32 dis_ra_mask = 0x0;

	चयन (ra_mask_type) अणु
	हाल 0: /* normal mode */
		अगर (ss_type == 2)
			dis_ra_mask = 0x0; /* enable 2ss */
		अन्यथा
			dis_ra_mask = 0xfff00000; /* disable 2ss */
		अवरोध;
	हाल 1: /* disable cck 1/2 */
		अगर (ss_type == 2)
			dis_ra_mask = 0x00000003; /* enable 2ss */
		अन्यथा
			dis_ra_mask = 0xfff00003; /* disable 2ss */
		अवरोध;
	हाल 2: /* disable cck 1/2/5.5, ofdm 6/9/12/18/24, mcs 0/1/2/3/4 */
		अगर (ss_type == 2)
			dis_ra_mask = 0x0001f1f7; /* enable 2ss */
		अन्यथा
			dis_ra_mask = 0xfff1f1f7; /* disable 2ss */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस dis_ra_mask;
पूर्ण

अटल व्योम btc8192e2ant_update_ra_mask(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, u32 dis_rate_mask)
अणु
	coex_dm->cur_ra_mask = dis_rate_mask;

	अगर (क्रमce_exec || (coex_dm->pre_ra_mask != coex_dm->cur_ra_mask))
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_UPDATE_RAMASK,
				   &coex_dm->cur_ra_mask);
	coex_dm->pre_ra_mask = coex_dm->cur_ra_mask;
पूर्ण

अटल व्योम btc8192e2ant_स्वतः_rate_fallback_retry(काष्ठा btc_coexist *btcoexist,
						  bool क्रमce_exec, u8 type)
अणु
	bool wअगरi_under_b_mode = false;

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

अटल व्योम btc8192e2ant_retry_limit(काष्ठा btc_coexist *btcoexist,
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

अटल व्योम btc8192e2ant_ampdu_maxसमय(काष्ठा btc_coexist *btcoexist,
				       bool क्रमce_exec, u8 type)
अणु
	coex_dm->cur_ampdu_समय_प्रकारype = type;

	अगर (क्रमce_exec || (coex_dm->pre_ampdu_समय_प्रकारype !=
			   coex_dm->cur_ampdu_समय_प्रकारype)) अणु
		चयन (coex_dm->cur_ampdu_समय_प्रकारype) अणु
		हाल 0:	/* normal mode */
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x456,
						coex_dm->backup_ampdu_maxसमय);
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

अटल व्योम btc8192e2ant_limited_tx(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u8 ra_mask_type,
				    u8 arfr_type, u8 retry_limit_type,
				    u8 ampdu_समय_प्रकारype)
अणु
	u32 dis_ra_mask = 0x0;

	coex_dm->cur_ra_mask_type = ra_mask_type;
	dis_ra_mask =
		 btc8192e2ant_decide_ra_mask(btcoexist, coex_dm->cur_ss_type,
					     ra_mask_type);
	btc8192e2ant_update_ra_mask(btcoexist, क्रमce_exec, dis_ra_mask);
	btc8192e2ant_स्वतः_rate_fallback_retry(btcoexist, क्रमce_exec, arfr_type);
	btc8192e2ant_retry_limit(btcoexist, क्रमce_exec, retry_limit_type);
	btc8192e2ant_ampdu_maxसमय(btcoexist, क्रमce_exec, ampdu_समय_प्रकारype);
पूर्ण

अटल व्योम btc8192e2ant_limited_rx(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, bool rej_ap_agg_pkt,
				    bool bt_ctrl_agg_buf_size,
				    u8 agg_buf_size)
अणु
	bool reject_rx_agg = rej_ap_agg_pkt;
	bool bt_ctrl_rx_agg_size = bt_ctrl_agg_buf_size;
	u8 rx_agg_size = agg_buf_size;

	/*********************************************
	 *	Rx Aggregation related setting
	 *********************************************/
	btcoexist->btc_set(btcoexist, BTC_SET_BL_TO_REJ_AP_AGG_PKT,
			   &reject_rx_agg);
	/* decide BT control aggregation buf size or not */
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_CTRL_AGG_SIZE,
			   &bt_ctrl_rx_agg_size);
	/* aggregation buf size, only work
	 * when BT control Rx aggregation size.
	 */
	btcoexist->btc_set(btcoexist, BTC_SET_U1_AGG_BUF_SIZE, &rx_agg_size);
	/* real update aggregation setting */
	btcoexist->btc_set(btcoexist, BTC_SET_ACT_AGGREGATE_CTRL, शून्य);
पूर्ण

अटल व्योम btc8192e2ant_monitor_bt_ctr(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u32 reg_hp_txrx, reg_lp_txrx, u32पंचांगp;
	u32 reg_hp_tx = 0, reg_hp_rx = 0, reg_lp_tx = 0, reg_lp_rx = 0;

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

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex] High Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
		reg_hp_txrx, reg_hp_tx, reg_hp_tx, reg_hp_rx, reg_hp_rx);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex] Low Priority Tx/Rx (reg 0x%x) = 0x%x(%d)/0x%x(%d)\n",
		reg_lp_txrx, reg_lp_tx, reg_lp_tx, reg_lp_rx, reg_lp_rx);

	/* reset counter */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0xc);
पूर्ण

अटल व्योम btc8192e2ant_query_bt_info(काष्ठा btc_coexist *btcoexist)
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

अटल
bool btc8192e2ant_is_wअगरi_status_changed(काष्ठा btc_coexist *btcoexist)
अणु
	अटल bool pre_wअगरi_busy = false, pre_under_4way = false,
		    pre_bt_hs_on = false;
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

अटल व्योम btc8192e2ant_update_bt_link_info(काष्ठा btc_coexist *btcoexist)
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

अटल u8 btc8192e2ant_action_algorithm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;
	bool bt_hs_on = false;
	u8 algorithm = BT_8192E_2ANT_COEX_ALGO_UNDEFINED;
	u8 num_of_dअगरf_profile = 0;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);

	अगर (!bt_link_info->bt_link_exist) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"No BT link exists!!!\n");
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
				"SCO only\n");
			algorithm = BT_8192E_2ANT_COEX_ALGO_SCO;
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"HID only\n");
				algorithm = BT_8192E_2ANT_COEX_ALGO_HID;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"A2DP only\n");
				algorithm = BT_8192E_2ANT_COEX_ALGO_A2DP;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"PAN(HS) only\n");
					algorithm =
						BT_8192E_2ANT_COEX_ALGO_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"PAN(EDR) only\n");
					algorithm =
						BT_8192E_2ANT_COEX_ALGO_PANEDR;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 2) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"SCO + HID\n");
				algorithm = BT_8192E_2ANT_COEX_ALGO_SCO;
			पूर्ण अन्यथा अगर (bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"SCO + A2DP ==> SCO\n");
				algorithm = BT_8192E_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						 "SCO + PAN(HS)\n");
					algorithm = BT_8192E_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						 "SCO + PAN(EDR)\n");
					algorithm =
						BT_8192E_2ANT_COEX_ALGO_SCO_PAN;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				अगर (stack_info->num_of_hid >= 2) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						 "HID*2 + A2DP\n");
					algorithm =
					BT_8192E_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						 "HID + A2DP\n");
					algorithm =
					    BT_8192E_2ANT_COEX_ALGO_HID_A2DP;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						 "HID + PAN(HS)\n");
					algorithm = BT_8192E_2ANT_COEX_ALGO_HID;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"HID + PAN(EDR)\n");
					algorithm =
					    BT_8192E_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"A2DP + PAN(HS)\n");
					algorithm =
					    BT_8192E_2ANT_COEX_ALGO_A2DP_PANHS;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"A2DP + PAN(EDR)\n");
					algorithm =
					    BT_8192E_2ANT_COEX_ALGO_PANEDR_A2DP;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (num_of_dअगरf_profile == 3) अणु
		अगर (bt_link_info->sco_exist) अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->a2dp_exist) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"SCO + HID + A2DP ==> HID\n");
				algorithm = BT_8192E_2ANT_COEX_ALGO_PANEDR_HID;
			पूर्ण अन्यथा अगर (bt_link_info->hid_exist &&
				   bt_link_info->pan_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"SCO + HID + PAN(HS)\n");
					algorithm = BT_8192E_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"SCO + HID + PAN(EDR)\n");
					algorithm =
						BT_8192E_2ANT_COEX_ALGO_SCO_PAN;
				पूर्ण
			पूर्ण अन्यथा अगर (bt_link_info->pan_exist &&
				   bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"SCO + A2DP + PAN(HS)\n");
					algorithm = BT_8192E_2ANT_COEX_ALGO_SCO;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"SCO + A2DP + PAN(EDR)\n");
					algorithm =
					    BT_8192E_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (bt_link_info->hid_exist &&
			    bt_link_info->pan_exist &&
			    bt_link_info->a2dp_exist) अणु
				अगर (bt_hs_on) अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"HID + A2DP + PAN(HS)\n");
					algorithm =
					    BT_8192E_2ANT_COEX_ALGO_HID_A2DP;
				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"HID + A2DP + PAN(EDR)\n");
					algorithm =
					BT_8192E_2ANT_COEX_ALGO_HID_A2DP_PANEDR;
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
						"ErrorSCO+HID+A2DP+PAN(HS)\n");

				पूर्ण अन्यथा अणु
					rtl_dbg(rtlpriv, COMP_BT_COEXIST,
						DBG_LOUD,
						"SCO+HID+A2DP+PAN(EDR)\n");
					algorithm =
					    BT_8192E_2ANT_COEX_ALGO_PANEDR_HID;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस algorithm;
पूर्ण

अटल व्योम btc8192e2ant_set_fw_dac_swing_level(काष्ठा btc_coexist *btcoexist,
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

अटल व्योम btc8192e2ant_set_fw_dec_bt_pwr(काष्ठा btc_coexist *btcoexist,
					   u8 dec_bt_pwr_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	h2c_parameter[0] = dec_bt_pwr_lvl;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex] decrease Bt Power level = %d, FW write 0x62 = 0x%x\n",
		dec_bt_pwr_lvl, h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x62, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8192e2ant_dec_bt_pwr(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u8 dec_bt_pwr_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s Dec BT power level = %d\n",
		क्रमce_exec ? "force to" : "", dec_bt_pwr_lvl);
	coex_dm->cur_dec_bt_pwr = dec_bt_pwr_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], preBtDecPwrLvl=%d, curBtDecPwrLvl=%d\n",
			coex_dm->pre_dec_bt_pwr, coex_dm->cur_dec_bt_pwr);
	पूर्ण
	btc8192e2ant_set_fw_dec_bt_pwr(btcoexist, coex_dm->cur_dec_bt_pwr);

	coex_dm->pre_dec_bt_pwr = coex_dm->cur_dec_bt_pwr;
पूर्ण

अटल व्योम btc8192e2ant_set_bt_स्वतः_report(काष्ठा btc_coexist *btcoexist,
					    bool enable_स्वतः_report)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	h2c_parameter[0] = 0;

	अगर (enable_स्वतः_report)
		h2c_parameter[0] |= BIT0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], BT FW auto report : %s, FW write 0x68 = 0x%x\n",
		(enable_स्वतः_report ? "Enabled!!" : "Disabled!!"),
		 h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x68, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8192e2ant_bt_स्वतः_report(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec,
					bool enable_स्वतः_report)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s BT Auto report = %s\n",
		(क्रमce_exec ? "force to" : ""),
		 ((enable_स्वतः_report) ? "Enabled" : "Disabled"));
	coex_dm->cur_bt_स्वतः_report = enable_स्वतः_report;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex] bPreBtAutoReport=%d, bCurBtAutoReport=%d\n",
			coex_dm->pre_bt_स्वतः_report,
			coex_dm->cur_bt_स्वतः_report);

		अगर (coex_dm->pre_bt_स्वतः_report == coex_dm->cur_bt_स्वतः_report)
			वापस;
	पूर्ण
	btc8192e2ant_set_bt_स्वतः_report(btcoexist,
					coex_dm->cur_bt_स्वतः_report);

	coex_dm->pre_bt_स्वतः_report = coex_dm->cur_bt_स्वतः_report;
पूर्ण

अटल व्योम btc8192e2ant_fw_dac_swing_lvl(काष्ठा btc_coexist *btcoexist,
					  bool क्रमce_exec, u8 fw_dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s set FW Dac Swing level = %d\n",
		(क्रमce_exec ? "force to" : ""), fw_dac_swing_lvl);
	coex_dm->cur_fw_dac_swing_lvl = fw_dac_swing_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex] preFwDacSwingLvl=%d, curFwDacSwingLvl=%d\n",
			coex_dm->pre_fw_dac_swing_lvl,
			coex_dm->cur_fw_dac_swing_lvl);

		अगर (coex_dm->pre_fw_dac_swing_lvl ==
		    coex_dm->cur_fw_dac_swing_lvl)
			वापस;
	पूर्ण

	btc8192e2ant_set_fw_dac_swing_level(btcoexist,
					    coex_dm->cur_fw_dac_swing_lvl);

	coex_dm->pre_fw_dac_swing_lvl = coex_dm->cur_fw_dac_swing_lvl;
पूर्ण

अटल व्योम btc8192e2ant_set_sw_rf_rx_lpf_corner(काष्ठा btc_coexist *btcoexist,
						 bool rx_rf_shrink_on)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (rx_rf_shrink_on) अणु
		/* Shrink RF Rx LPF corner */
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Shrink RF Rx LPF corner!!\n");
		btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1e,
					  0xfffff, 0xffffc);
	पूर्ण अन्यथा अणु
		/* Resume RF Rx LPF corner
		 * After initialized, we can use coex_dm->btRf0x1eBackup
		 */
		अगर (btcoexist->initialized) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], Resume RF Rx LPF corner!!\n");
			btcoexist->btc_set_rf_reg(btcoexist, BTC_RF_A, 0x1e,
						  0xfffff,
						  coex_dm->bt_rf0x1e_backup);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_rf_shrink(काष्ठा btc_coexist *btcoexist,
				   bool क्रमce_exec, bool rx_rf_shrink_on)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn Rx RF Shrink = %s\n",
		(क्रमce_exec ? "force to" : ""),
		((rx_rf_shrink_on) ? "ON" : "OFF"));
	coex_dm->cur_rf_rx_lpf_shrink = rx_rf_shrink_on;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex]bPreRfRxLpfShrink=%d,bCurRfRxLpfShrink=%d\n",
			coex_dm->pre_rf_rx_lpf_shrink,
			coex_dm->cur_rf_rx_lpf_shrink);

		अगर (coex_dm->pre_rf_rx_lpf_shrink ==
		    coex_dm->cur_rf_rx_lpf_shrink)
			वापस;
	पूर्ण
	btc8192e2ant_set_sw_rf_rx_lpf_corner(btcoexist,
					     coex_dm->cur_rf_rx_lpf_shrink);

	coex_dm->pre_rf_rx_lpf_shrink = coex_dm->cur_rf_rx_lpf_shrink;
पूर्ण

अटल व्योम btc8192e2ant_set_dac_swing_reg(काष्ठा btc_coexist *btcoexist,
					   u32 level)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 val = (u8)level;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Write SwDacSwing = 0x%x\n", level);
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0x883, 0x3e, val);
पूर्ण

अटल व्योम btc8192e2ant_set_sw_full_swing(काष्ठा btc_coexist *btcoexist,
					   bool sw_dac_swing_on,
					   u32 sw_dac_swing_lvl)
अणु
	अगर (sw_dac_swing_on)
		btc8192e2ant_set_dac_swing_reg(btcoexist, sw_dac_swing_lvl);
	अन्यथा
		btc8192e2ant_set_dac_swing_reg(btcoexist, 0x18);
पूर्ण

अटल व्योम btc8192e2ant_dac_swing(काष्ठा btc_coexist *btcoexist,
				   bool क्रमce_exec, bool dac_swing_on,
				   u32 dac_swing_lvl)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn DacSwing=%s, dac_swing_lvl = 0x%x\n",
		(क्रमce_exec ? "force to" : ""),
		((dac_swing_on) ? "ON" : "OFF"), dac_swing_lvl);
	coex_dm->cur_dac_swing_on = dac_swing_on;
	coex_dm->cur_dac_swing_lvl = dac_swing_lvl;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bPreDacSwingOn=%d, preDacSwingLvl = 0x%x, ",
			coex_dm->pre_dac_swing_on,
			coex_dm->pre_dac_swing_lvl);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"bCurDacSwingOn=%d, curDacSwingLvl = 0x%x\n",
			coex_dm->cur_dac_swing_on,
			coex_dm->cur_dac_swing_lvl);

		अगर ((coex_dm->pre_dac_swing_on == coex_dm->cur_dac_swing_on) &&
		    (coex_dm->pre_dac_swing_lvl == coex_dm->cur_dac_swing_lvl))
			वापस;
	पूर्ण
	mdelay(30);
	btc8192e2ant_set_sw_full_swing(btcoexist, dac_swing_on, dac_swing_lvl);

	coex_dm->pre_dac_swing_on = coex_dm->cur_dac_swing_on;
	coex_dm->pre_dac_swing_lvl = coex_dm->cur_dac_swing_lvl;
पूर्ण

अटल व्योम btc8192e2ant_set_agc_table(काष्ठा btc_coexist *btcoexist,
				       bool agc_table_en)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	/* BB AGC Gain Table */
	अगर (agc_table_en) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BB Agc Table On!\n");
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0x0a1A0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0x091B0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0x081C0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0x071D0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0x061E0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0x051F0001);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BB Agc Table Off!\n");
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0xaa1A0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0xa91B0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0xa81C0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0xa71D0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0xa61E0001);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0xc78, 0xa51F0001);
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_agc_table(काष्ठा btc_coexist *btcoexist,
				   bool क्रमce_exec, bool agc_table_en)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s %s Agc Table\n",
		(क्रमce_exec ? "force to" : ""),
		((agc_table_en) ? "Enable" : "Disable"));
	coex_dm->cur_agc_table_en = agc_table_en;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bPreAgcTableEn=%d, bCurAgcTableEn=%d\n",
			coex_dm->pre_agc_table_en,
			coex_dm->cur_agc_table_en);

		अगर (coex_dm->pre_agc_table_en == coex_dm->cur_agc_table_en)
			वापस;
	पूर्ण
	btc8192e2ant_set_agc_table(btcoexist, agc_table_en);

	coex_dm->pre_agc_table_en = coex_dm->cur_agc_table_en;
पूर्ण

अटल व्योम btc8192e2ant_set_coex_table(काष्ठा btc_coexist *btcoexist,
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

अटल व्योम btc8192e2ant_coex_table(काष्ठा btc_coexist *btcoexist,
				    bool क्रमce_exec, u32 val0x6c0, u32 val0x6c4,
				    u32 val0x6c8, u8 val0x6cc)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s write Coex Table 0x6c0 = 0x%x, ",
		(क्रमce_exec ? "force to" : ""), val0x6c0);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"0x6c4 = 0x%x, 0x6c8 = 0x%x, 0x6cc = 0x%x\n",
		val0x6c4, val0x6c8, val0x6cc);
	coex_dm->cur_val0x6c0 = val0x6c0;
	coex_dm->cur_val0x6c4 = val0x6c4;
	coex_dm->cur_val0x6c8 = val0x6c8;
	coex_dm->cur_val0x6cc = val0x6cc;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], preVal0x6c0 = 0x%x, preVal0x6c4 = 0x%x, ",
			coex_dm->pre_val0x6c0, coex_dm->pre_val0x6c4);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"preVal0x6c8 = 0x%x, preVal0x6cc = 0x%x !!\n",
			coex_dm->pre_val0x6c8, coex_dm->pre_val0x6cc);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], curVal0x6c0 = 0x%x, curVal0x6c4 = 0x%x\n",
			coex_dm->cur_val0x6c0, coex_dm->cur_val0x6c4);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"curVal0x6c8 = 0x%x, curVal0x6cc = 0x%x !!\n",
			coex_dm->cur_val0x6c8, coex_dm->cur_val0x6cc);

		अगर ((coex_dm->pre_val0x6c0 == coex_dm->cur_val0x6c0) &&
		    (coex_dm->pre_val0x6c4 == coex_dm->cur_val0x6c4) &&
		    (coex_dm->pre_val0x6c8 == coex_dm->cur_val0x6c8) &&
		    (coex_dm->pre_val0x6cc == coex_dm->cur_val0x6cc))
			वापस;
	पूर्ण
	btc8192e2ant_set_coex_table(btcoexist, val0x6c0, val0x6c4, val0x6c8,
				    val0x6cc);

	coex_dm->pre_val0x6c0 = coex_dm->cur_val0x6c0;
	coex_dm->pre_val0x6c4 = coex_dm->cur_val0x6c4;
	coex_dm->pre_val0x6c8 = coex_dm->cur_val0x6c8;
	coex_dm->pre_val0x6cc = coex_dm->cur_val0x6cc;
पूर्ण

अटल व्योम btc8192e2ant_coex_table_with_type(काष्ठा btc_coexist *btcoexist,
					      bool क्रमce_exec, u8 type)
अणु
	चयन (type) अणु
	हाल 0:
		btc8192e2ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 1:
		btc8192e2ant_coex_table(btcoexist, क्रमce_exec, 0x5a5a5a5a,
					0x5a5a5a5a, 0xffffff, 0x3);
		अवरोध;
	हाल 2:
		btc8192e2ant_coex_table(btcoexist, क्रमce_exec, 0x55555555,
					0x5ffb5ffb, 0xffffff, 0x3);
		अवरोध;
	हाल 3:
		btc8192e2ant_coex_table(btcoexist, क्रमce_exec, 0xdfffdfff,
					0x5fdb5fdb, 0xffffff, 0x3);
		अवरोध;
	हाल 4:
		btc8192e2ant_coex_table(btcoexist, क्रमce_exec, 0xdfffdfff,
					0x5ffb5ffb, 0xffffff, 0x3);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_set_fw_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
						bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[1] = अणु0पूर्ण;

	अगर (enable)
		h2c_parameter[0] |= BIT0; /* function enable */

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex]set FW for BT Ignore Wlan_Act, FW write 0x63 = 0x%x\n",
		h2c_parameter[0]);

	btcoexist->btc_fill_h2c(btcoexist, 0x63, 1, h2c_parameter);
पूर्ण

अटल व्योम btc8192e2ant_ignore_wlan_act(काष्ठा btc_coexist *btcoexist,
					 bool क्रमce_exec, bool enable)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn Ignore WlanAct %s\n",
		(क्रमce_exec ? "force to" : ""), (enable ? "ON" : "OFF"));
	coex_dm->cur_ignore_wlan_act = enable;

	अगर (!क्रमce_exec) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bPreIgnoreWlanAct = %d ",
			coex_dm->pre_ignore_wlan_act);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"bCurIgnoreWlanAct = %d!!\n",
			coex_dm->cur_ignore_wlan_act);

		अगर (coex_dm->pre_ignore_wlan_act ==
		    coex_dm->cur_ignore_wlan_act)
			वापस;
	पूर्ण
	btc8192e2ant_set_fw_ignore_wlan_act(btcoexist, enable);

	coex_dm->pre_ignore_wlan_act = coex_dm->cur_ignore_wlan_act;
पूर्ण

अटल व्योम btc8192e2ant_set_fw_ps_tdma(काष्ठा btc_coexist *btcoexist, u8 byte1,
					u8 byte2, u8 byte3, u8 byte4, u8 byte5)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	u8 h2c_parameter[5] = अणु0पूर्ण;

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
		h2c_parameter[1] << 24 | h2c_parameter[2] << 16 |
		h2c_parameter[3] << 8 | h2c_parameter[4]);

	btcoexist->btc_fill_h2c(btcoexist, 0x60, 5, h2c_parameter);
पूर्ण

अटल व्योम btc8192e2ant_sw_mechanism1(काष्ठा btc_coexist *btcoexist,
				       bool shrink_rx_lpf, bool low_penalty_ra,
				       bool limited_dig, bool btlan_स्थिरrain)
अणु
	btc8192e2ant_rf_shrink(btcoexist, NORMAL_EXEC, shrink_rx_lpf);
पूर्ण

अटल व्योम btc8192e2ant_sw_mechanism2(काष्ठा btc_coexist *btcoexist,
				       bool agc_table_shअगरt, bool adc_backoff,
				       bool sw_dac_swing, u32 dac_swing_lvl)
अणु
	btc8192e2ant_agc_table(btcoexist, NORMAL_EXEC, agc_table_shअगरt);
	btc8192e2ant_dac_swing(btcoexist, NORMAL_EXEC, sw_dac_swing,
			       dac_swing_lvl);
पूर्ण

अटल व्योम btc8192e2ant_ps_tdma(काष्ठा btc_coexist *btcoexist,
				 bool क्रमce_exec, bool turn_on, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s turn %s PS TDMA, type=%d\n",
		(क्रमce_exec ? "force to" : ""),
		(turn_on ? "ON" : "OFF"), type);
	coex_dm->cur_ps_tdma_on = turn_on;
	coex_dm->cur_ps_tdma = type;

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
	अगर (turn_on) अणु
		चयन (type) अणु
		हाल 1:
		शेष:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe1, 0x90);
			अवरोध;
		हाल 2:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0xe1, 0x90);
			अवरोध;
		हाल 3:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x90);
			अवरोध;
		हाल 4:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1, 0x90);
			अवरोध;
		हाल 5:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0x60, 0x90);
			अवरोध;
		हाल 6:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0x60, 0x90);
			अवरोध;
		हाल 7:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 8:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xa3, 0x10,
						    0x3, 0x70, 0x90);
			अवरोध;
		हाल 9:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe1, 0x10);
			अवरोध;
		हाल 10:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0xe1, 0x10);
			अवरोध;
		हाल 11:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf1, 0x10);
			अवरोध;
		हाल 12:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x10,
						    0x3, 0xf1, 0x10);
			अवरोध;
		हाल 13:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe0, 0x10);
			अवरोध;
		हाल 14:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x12, 0xe0, 0x10);
			अवरोध;
		हाल 15:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1c,
						    0x3, 0xf0, 0x10);
			अवरोध;
		हाल 16:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x12,
						    0x3, 0xf0, 0x10);
			अवरोध;
		हाल 17:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0x61, 0x20,
						    0x03, 0x10, 0x10);
			अवरोध;
		हाल 18:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x5,
						    0x5, 0xe1, 0x90);
			अवरोध;
		हाल 19:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0xe1, 0x90);
			अवरोध;
		हाल 20:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x25,
						    0x25, 0x60, 0x90);
			अवरोध;
		हाल 21:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x15,
						    0x03, 0x70, 0x90);
			अवरोध;
		हाल 71:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0xe3, 0x1a,
						    0x1a, 0xe1, 0x90);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable PS tdma */
		चयन (type) अणु
		शेष:
		हाल 0:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0x8, 0x0, 0x0,
						    0x0, 0x0);
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x92c, 0x4);
			अवरोध;
		हाल 1:
			btc8192e2ant_set_fw_ps_tdma(btcoexist, 0x0, 0x0, 0x0,
						    0x8, 0x0);
			mdelay(5);
			btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x92c, 0x20);
			अवरोध;
		पूर्ण
	पूर्ण

	/* update pre state */
	coex_dm->pre_ps_tdma_on = coex_dm->cur_ps_tdma_on;
	coex_dm->pre_ps_tdma = coex_dm->cur_ps_tdma;
पूर्ण

अटल व्योम btc8192e2ant_set_चयन_ss_type(काष्ठा btc_coexist *btcoexist,
					    u8 ss_type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 mimops = BTC_MIMO_PS_DYNAMIC;
	u32 dis_ra_mask = 0x0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], REAL set SS Type = %d\n", ss_type);

	dis_ra_mask = btc8192e2ant_decide_ra_mask(btcoexist, ss_type,
						  coex_dm->cur_ra_mask_type);
	btc8192e2ant_update_ra_mask(btcoexist, FORCE_EXEC, dis_ra_mask);

	अगर (ss_type == 1) अणु
		btc8192e2ant_ps_tdma(btcoexist, FORCE_EXEC, false, 1);
		/* चयन ofdm path */
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xc04, 0x11);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xd04, 0x1);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x90c, 0x81111111);
		/* चयन cck patch */
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xe77, 0x4, 0x1);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xa07, 0x81);
		mimops = BTC_MIMO_PS_STATIC;
	पूर्ण अन्यथा अगर (ss_type == 2) अणु
		btc8192e2ant_ps_tdma(btcoexist, FORCE_EXEC, false, 0);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xc04, 0x33);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xd04, 0x3);
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x90c, 0x81121313);
		btcoexist->btc_ग_लिखो_1byte_biपंचांगask(btcoexist, 0xe77, 0x4, 0x0);
		btcoexist->btc_ग_लिखो_1byte(btcoexist, 0xa07, 0x41);
		mimops = BTC_MIMO_PS_DYNAMIC;
	पूर्ण
	/* set rx 1ss or 2ss */
	btcoexist->btc_set(btcoexist, BTC_SET_ACT_SEND_MIMO_PS, &mimops);
पूर्ण

अटल व्योम btc8192e2ant_चयन_ss_type(काष्ठा btc_coexist *btcoexist,
					bool क्रमce_exec, u8 new_ss_type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], %s Switch SS Type = %d\n",
		(क्रमce_exec ? "force to" : ""), new_ss_type);
	coex_dm->cur_ss_type = new_ss_type;

	अगर (!क्रमce_exec) अणु
		अगर (coex_dm->pre_ss_type == coex_dm->cur_ss_type)
			वापस;
	पूर्ण
	btc8192e2ant_set_चयन_ss_type(btcoexist, coex_dm->cur_ss_type);

	coex_dm->pre_ss_type = coex_dm->cur_ss_type;
पूर्ण

अटल व्योम btc8192e2ant_coex_all_off(काष्ठा btc_coexist *btcoexist)
अणु
	/* fw all off */
	btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	/* sw all off */
	btc8192e2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8192e2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);

	/* hw all off */
	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
पूर्ण

अटल व्योम btc8192e2ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	/* क्रमce to reset coex mechanism */

	btc8192e2ant_ps_tdma(btcoexist, FORCE_EXEC, false, 1);
	btc8192e2ant_fw_dac_swing_lvl(btcoexist, FORCE_EXEC, 6);
	btc8192e2ant_dec_bt_pwr(btcoexist, FORCE_EXEC, 0);

	btc8192e2ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);
	btc8192e2ant_चयन_ss_type(btcoexist, FORCE_EXEC, 2);

	btc8192e2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8192e2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);
पूर्ण

अटल व्योम btc8192e2ant_action_bt_inquiry(काष्ठा btc_coexist *btcoexist)
अणु
	bool low_pwr_disable = true;

	btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
			   &low_pwr_disable);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);
	btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 3);
	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

	btc8192e2ant_sw_mechanism1(btcoexist, false, false, false, false);
	btc8192e2ant_sw_mechanism2(btcoexist, false, false, false, 0x18);
पूर्ण

अटल bool btc8192e2ant_is_common_action(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा btc_bt_link_info *bt_link_info = &btcoexist->bt_link_info;
	bool common = false, wअगरi_connected = false, wअगरi_busy = false;
	bool bt_hs_on = false, low_pwr_disable = false;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
			   &wअगरi_connected);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);

	अगर (bt_link_info->sco_exist || bt_link_info->hid_exist)
		btc8192e2ant_limited_tx(btcoexist, NORMAL_EXEC, 1, 0, 0, 0);
	अन्यथा
		btc8192e2ant_limited_tx(btcoexist, NORMAL_EXEC, 0, 0, 0, 0);

	अगर (!wअगरi_connected) अणु
		low_pwr_disable = false;
		btcoexist->btc_set(btcoexist, BTC_SET_ACT_DISABLE_LOW_POWER,
				   &low_pwr_disable);

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Wifi non-connected idle!!\n");

		अगर ((BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		     coex_dm->bt_status) ||
		    (BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE ==
		     coex_dm->bt_status)) अणु
			btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 2);
			btc8192e2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
			btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
		पूर्ण अन्यथा अणु
			btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
			btc8192e2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 0);
			btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);
		पूर्ण

		btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

		btc8192e2ant_sw_mechanism1(btcoexist, false, false, false,
					   false);
		btc8192e2ant_sw_mechanism2(btcoexist, false, false, false,
					   0x18);

		common = true;
	पूर्ण अन्यथा अणु
		अगर (BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
		    coex_dm->bt_status) अणु
			low_pwr_disable = false;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Wifi connected + BT non connected-idle!!\n");

			btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 2);
			btc8192e2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
			btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 0);
			btc8192e2ant_fw_dac_swing_lvl(btcoexist,
						      NORMAL_EXEC, 6);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);

			common = true;
		पूर्ण अन्यथा अगर (BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE ==
			   coex_dm->bt_status) अणु
			low_pwr_disable = true;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			अगर (bt_hs_on)
				वापस false;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Wifi connected + BT connected-idle!!\n");

			btc8192e2ant_चयन_ss_type(btcoexist,
						    NORMAL_EXEC, 2);
			btc8192e2ant_coex_table_with_type(btcoexist,
							  NORMAL_EXEC, 1);
			btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     false, 0);
			btc8192e2ant_fw_dac_swing_lvl(btcoexist,
						      NORMAL_EXEC, 6);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);

			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);

			common = true;
		पूर्ण अन्यथा अणु
			low_pwr_disable = true;
			btcoexist->btc_set(btcoexist,
					   BTC_SET_ACT_DISABLE_LOW_POWER,
					   &low_pwr_disable);

			अगर (wअगरi_busy) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"Wifi Connected-Busy + BT Busy!!\n");
				common = false;
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"Wifi Connected-Idle + BT Busy!!\n");

				btc8192e2ant_चयन_ss_type(btcoexist,
							    NORMAL_EXEC, 1);
				btc8192e2ant_coex_table_with_type(btcoexist,
								  NORMAL_EXEC,
								  2);
				btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC,
						     true, 21);
				btc8192e2ant_fw_dac_swing_lvl(btcoexist,
							      NORMAL_EXEC, 6);
				btc8192e2ant_dec_bt_pwr(btcoexist,
							NORMAL_EXEC, 0);
				btc8192e2ant_sw_mechanism1(btcoexist, false,
							   false, false, false);
				btc8192e2ant_sw_mechanism2(btcoexist, false,
							   false, false, 0x18);
				common = true;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस common;
पूर्ण

अटल व्योम btc8192e2ant_tdma_duration_adjust(काष्ठा btc_coexist *btcoexist,
					      bool sco_hid, bool tx_छोड़ो,
					      u8 max_पूर्णांकerval)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल पूर्णांक up, dn, m, n, रुको_cnt;
	u8 retry_cnt = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], TdmaDurationAdjust()\n");

	अगर (!coex_dm->स्वतः_tdma_adjust) अणु
		coex_dm->स्वतः_tdma_adjust = true;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], first run TdmaDurationAdjust()!!\n");
		अगर (sco_hid) अणु
			अगर (tx_छोड़ो) अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 13);
					coex_dm->tdma_adj_type = 13;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 14);
					coex_dm->tdma_adj_type = 14;
				पूर्ण अन्यथा अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 15);
					coex_dm->tdma_adj_type = 15;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 9);
					coex_dm->tdma_adj_type = 9;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 10);
					coex_dm->tdma_adj_type = 10;
				पूर्ण अन्यथा अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 11);
					coex_dm->tdma_adj_type = 11;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tx_छोड़ो) अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 5);
					coex_dm->tdma_adj_type = 5;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 6);
					coex_dm->tdma_adj_type = 6;
				पूर्ण अन्यथा अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 7);
					coex_dm->tdma_adj_type = 7;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (max_पूर्णांकerval == 1) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 1);
					coex_dm->tdma_adj_type = 1;
				पूर्ण अन्यथा अगर (max_पूर्णांकerval == 2) अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 2);
					coex_dm->tdma_adj_type = 2;
				पूर्ण अन्यथा अणु
					btc8192e2ant_ps_tdma(btcoexist,
							     NORMAL_EXEC,
							     true, 3);
					coex_dm->tdma_adj_type = 3;
				पूर्ण
			पूर्ण
		पूर्ण

		up = 0;
		dn = 0;
		m = 1;
		n = 3;
		रुको_cnt = 0;
	पूर्ण अन्यथा अणु
		/* accquire the BT TRx retry count from BT_Info byte2 */
		retry_cnt = coex_sta->bt_retry_cnt;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], retry_cnt = %d\n", retry_cnt);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], up=%d, dn=%d, m=%d, n=%d, wait_cnt=%d\n",
			up, dn, m, n, रुको_cnt);
		रुको_cnt++;
		/* no retry in the last 2-second duration */
		अगर (retry_cnt == 0) अणु
			up++;
			dn--;

			अगर (dn <= 0)
				dn = 0;

			अगर (up >= n) अणु
				रुको_cnt = 0;
				n = 3;
				up = 0;
				dn = 0;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"[BTCoex]Increase wifi duration!!\n");
			पूर्ण
		पूर्ण अन्यथा अगर (retry_cnt <= 3) अणु
			up--;
			dn++;

			अगर (up <= 0)
				up = 0;

			अगर (dn == 2) अणु
				अगर (रुको_cnt <= 2)
					m++;
				अन्यथा
					m = 1;

				अगर (m >= 20)
					m = 20;

				n = 3 * m;
				up = 0;
				dn = 0;
				रुको_cnt = 0;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"Reduce wifi duration for retry<3\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (रुको_cnt == 1)
				m++;
			अन्यथा
				m = 1;

			अगर (m >= 20)
				m = 20;

			n = 3*m;
			up = 0;
			dn = 0;
			रुको_cnt = 0;
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Decrease wifi duration for retryCounter>3!!\n");
		पूर्ण

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], max Interval = %d\n", max_पूर्णांकerval);
	पूर्ण

	/* अगर current PsTdma not match with
	 * the recorded one (when scan, dhcp...),
	 * then we have to adjust it back to the previous record one.
	 */
	अगर (coex_dm->cur_ps_tdma != coex_dm->tdma_adj_type) अणु
		bool scan = false, link = false, roam = false;

		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], PsTdma type mismatch!!!, ");
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"curPsTdma=%d, recordPsTdma=%d\n",
			 coex_dm->cur_ps_tdma, coex_dm->tdma_adj_type);

		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
		btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);

		अगर (!scan && !link && !roam)
			btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC,
					     true, coex_dm->tdma_adj_type);
		अन्यथा
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex], roaming/link/scan is under progress, will adjust next time!!!\n");
	पूर्ण
पूर्ण

/* SCO only or SCO+PAN(HS) */
अटल व्योम btc8192e2ant_action_sco(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 13);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 9);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 9);
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x6);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x6);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x6);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x6);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_action_sco_pan(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_STAY_LOW;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 4);

	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 10);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 10);
	पूर्ण

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x6);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x6);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x6);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x6);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_action_hid(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 13);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 9);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 9);
	पूर्ण

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* A2DP only / PAN(EDR) only/ A2DP+PAN(HS) */
अटल व्योम btc8192e2ant_action_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;
	bool दीर्घ_dist = false;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW ||
	     bt_rssi_state == BTC_RSSI_STATE_STAY_LOW) &&
	    (wअगरi_rssi_state == BTC_RSSI_STATE_LOW ||
	     wअगरi_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], A2dp, wifi/bt rssi both LOW!!\n");
		दीर्घ_dist = true;
	पूर्ण
	अगर (दीर्घ_dist) अणु
		btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, true,
					0x4);
	पूर्ण अन्यथा अणु
		btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
		btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false,
					0x8);
	पूर्ण

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	अगर (दीर्घ_dist)
		btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 0);
	अन्यथा
		btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

	अगर (दीर्घ_dist) अणु
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 17);
		coex_dm->स्वतः_tdma_adjust = false;
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अणु
		अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
		    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
			btc8192e2ant_tdma_duration_adjust(btcoexist, false,
							  true, 1);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
			   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
			btc8192e2ant_tdma_duration_adjust(btcoexist, false,
							  false, 1);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
			   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_tdma_duration_adjust(btcoexist, false,
							  false, 1);
			btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		पूर्ण
	पूर्ण

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_action_a2dp_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);
	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_tdma_duration_adjust(btcoexist, false, true, 2);
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_tdma_duration_adjust(btcoexist, false, false, 2);
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_tdma_duration_adjust(btcoexist, false, false, 2);
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
	पूर्ण

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   true, 0x6);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   true, 0x6);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   true, 0x6);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   true, 0x6);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_action_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 5);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 1);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 1);
	पूर्ण

	/* sw mechanism */
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* PAN(HS) only */
अटल व्योम btc8192e2ant_action_pan_hs(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
	पूर्ण
	btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, false, 1);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* PAN(EDR)+A2DP */
अटल व्योम btc8192e2ant_action_pan_edr_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 2);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_tdma_duration_adjust(btcoexist, false, true, 3);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_tdma_duration_adjust(btcoexist, false, false, 3);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_tdma_duration_adjust(btcoexist, false, false, 3);
	पूर्ण

	/* sw mechanism	*/
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, false,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_action_pan_edr_hid(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 14);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC, true, 10);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_ps_tdma(btcoexist, NORMAL_EXEC,
				     true, 10);
	पूर्ण

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

/* HID+A2DP+PAN(EDR) */
अटल व्योम btc8192e2ant_action_hid_a2dp_pan_edr(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btc8192e2ant_fw_dac_swing_lvl(btcoexist, NORMAL_EXEC, 6);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_tdma_duration_adjust(btcoexist, true, true, 3);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_tdma_duration_adjust(btcoexist, true, false, 3);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_tdma_duration_adjust(btcoexist, true, false, 3);
	पूर्ण

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_action_hid_a2dp(काष्ठा btc_coexist *btcoexist)
अणु
	u8 wअगरi_rssi_state, bt_rssi_state = BTC_RSSI_STATE_HIGH;
	u32 wअगरi_bw;

	wअगरi_rssi_state = btc8192e2ant_wअगरi_rssi_state(btcoexist, 0, 2, 15, 0);
	bt_rssi_state = btc8192e2ant_bt_rssi_state(btcoexist, 3, 34, 42);

	btc8192e2ant_चयन_ss_type(btcoexist, NORMAL_EXEC, 1);
	btc8192e2ant_limited_rx(btcoexist, NORMAL_EXEC, false, false, 0x8);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);

	btc8192e2ant_coex_table_with_type(btcoexist, NORMAL_EXEC, 3);

	अगर ((bt_rssi_state == BTC_RSSI_STATE_LOW) ||
	    (bt_rssi_state == BTC_RSSI_STATE_STAY_LOW)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 0);
		btc8192e2ant_tdma_duration_adjust(btcoexist, true, true, 2);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_MEDIUM) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_MEDIUM))	अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 2);
		btc8192e2ant_tdma_duration_adjust(btcoexist, true, false, 2);
	पूर्ण अन्यथा अगर ((bt_rssi_state == BTC_RSSI_STATE_HIGH) ||
		   (bt_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
		btc8192e2ant_dec_bt_pwr(btcoexist, NORMAL_EXEC, 4);
		btc8192e2ant_tdma_duration_adjust(btcoexist, true, false, 2);
	पूर्ण

	/* sw mechanism */
	अगर (BTC_WIFI_BW_HT40 == wअगरi_bw) अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, true, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((wअगरi_rssi_state == BTC_RSSI_STATE_HIGH) ||
		    (wअगरi_rssi_state == BTC_RSSI_STATE_STAY_HIGH)) अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, true, false,
						   false, 0x18);
		पूर्ण अन्यथा अणु
			btc8192e2ant_sw_mechanism1(btcoexist, false, true,
						   false, false);
			btc8192e2ant_sw_mechanism2(btcoexist, false, false,
						   false, 0x18);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_run_coexist_mechanism(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 algorithm = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], RunCoexistMechanism()===>\n");

	अगर (btcoexist->manual_control) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], return for Manual CTRL <===\n");
		वापस;
	पूर्ण

	अगर (coex_sta->under_ips) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], wifi is under IPS !!!\n");
		वापस;
	पूर्ण

	algorithm = btc8192e2ant_action_algorithm(btcoexist);
	अगर (coex_sta->c2h_bt_inquiry_page &&
	    (BT_8192E_2ANT_COEX_ALGO_PANHS != algorithm)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT is under inquiry/page scan !!\n");
		btc8192e2ant_action_bt_inquiry(btcoexist);
		वापस;
	पूर्ण

	coex_dm->cur_algorithm = algorithm;
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Algorithm = %d\n", coex_dm->cur_algorithm);

	अगर (btc8192e2ant_is_common_action(btcoexist)) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Action 2-Ant common\n");
		coex_dm->स्वतः_tdma_adjust = false;
	पूर्ण अन्यथा अणु
		अगर (coex_dm->cur_algorithm != coex_dm->pre_algorithm) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"[BTCoex] preAlgorithm=%d, curAlgorithm=%d\n",
				 coex_dm->pre_algorithm,
				 coex_dm->cur_algorithm);
			coex_dm->स्वतः_tdma_adjust = false;
		पूर्ण
		चयन (coex_dm->cur_algorithm) अणु
		हाल BT_8192E_2ANT_COEX_ALGO_SCO:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = SCO\n");
			btc8192e2ant_action_sco(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_SCO_PAN:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = SCO+PAN(EDR)\n");
			btc8192e2ant_action_sco_pan(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = HID\n");
			btc8192e2ant_action_hid(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = A2DP\n");
			btc8192e2ant_action_a2dp(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_A2DP_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = A2DP+PAN(HS)\n");
			btc8192e2ant_action_a2dp_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = PAN(EDR)\n");
			btc8192e2ant_action_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_PANHS:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = HS mode\n");
			btc8192e2ant_action_pan_hs(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_PANEDR_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = PAN+A2DP\n");
			btc8192e2ant_action_pan_edr_a2dp(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_PANEDR_HID:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = PAN(EDR)+HID\n");
			btc8192e2ant_action_pan_edr_hid(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_HID_A2DP_PANEDR:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = HID+A2DP+PAN\n");
			btc8192e2ant_action_hid_a2dp_pan_edr(btcoexist);
			अवरोध;
		हाल BT_8192E_2ANT_COEX_ALGO_HID_A2DP:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = HID+A2DP\n");
			btc8192e2ant_action_hid_a2dp(btcoexist);
			अवरोध;
		शेष:
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"Action 2-Ant, algorithm = unknown!!\n");
			/* btc8192e2ant_coex_all_off(btcoexist); */
			अवरोध;
		पूर्ण
		coex_dm->pre_algorithm = coex_dm->cur_algorithm;
	पूर्ण
पूर्ण

अटल व्योम btc8192e2ant_init_hwconfig(काष्ठा btc_coexist *btcoexist,
				       bool backup)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u16 u16पंचांगp = 0;
	u8 u8पंचांगp = 0;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], 2Ant Init HW Config!!\n");

	अगर (backup) अणु
		/* backup rf 0x1e value */
		coex_dm->bt_rf0x1e_backup =
			btcoexist->btc_get_rf_reg(btcoexist, BTC_RF_A,
						  0x1e, 0xfffff);

		coex_dm->backup_arfr_cnt1 = btcoexist->btc_पढ़ो_4byte(btcoexist,
								      0x430);
		coex_dm->backup_arfr_cnt2 = btcoexist->btc_पढ़ो_4byte(btcoexist,
								     0x434);
		coex_dm->backup_retry_limit = btcoexist->btc_पढ़ो_2byte(
								    btcoexist,
								    0x42a);
		coex_dm->backup_ampdu_maxसमय = btcoexist->btc_पढ़ो_1byte(
								    btcoexist,
								    0x456);
	पूर्ण

	/* antenna sw ctrl to bt */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x4f, 0x6);
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x944, 0x24);
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x930, 0x700700);
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x92c, 0x20);
	अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_USB)
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x64, 0x30430004);
	अन्यथा
		btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x64, 0x30030004);

	btc8192e2ant_coex_table_with_type(btcoexist, FORCE_EXEC, 0);

	/* antenna चयन control parameter */
	btcoexist->btc_ग_लिखो_4byte(btcoexist, 0x858, 0x55555555);

	/* coex parameters */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x778, 0x3);
	/* 0x790[5:0] = 0x5 */
	u8पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x790);
	u8पंचांगp &= 0xc0;
	u8पंचांगp |= 0x5;
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x790, u8पंचांगp);

	/* enable counter statistics */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x76e, 0x4);

	/* enable PTA */
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x40, 0x20);
	/* enable mailbox पूर्णांकerface */
	u16पंचांगp = btcoexist->btc_पढ़ो_2byte(btcoexist, 0x40);
	u16पंचांगp |= BIT9;
	btcoexist->btc_ग_लिखो_2byte(btcoexist, 0x40, u16पंचांगp);

	/* enable PTA I2C mailbox */
	u8पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x101);
	u8पंचांगp |= BIT4;
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x101, u8पंचांगp);

	/* enable bt घड़ी when wअगरi is disabled. */
	u8पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x93);
	u8पंचांगp |= BIT0;
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x93, u8पंचांगp);
	/* enable bt घड़ी when suspend. */
	u8पंचांगp = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x7);
	u8पंचांगp |= BIT0;
	btcoexist->btc_ग_लिखो_1byte(btcoexist, 0x7, u8पंचांगp);
पूर्ण

/************************************************************
 *   बाह्य function start with ex_btc8192e2ant_
 ************************************************************/

व्योम ex_btc8192e2ant_init_hwconfig(काष्ठा btc_coexist *btcoexist)
अणु
	btc8192e2ant_init_hwconfig(btcoexist, true);
पूर्ण

व्योम ex_btc8192e2ant_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Coex Mechanism Init!!\n");
	btc8192e2ant_init_coex_dm(btcoexist);
पूर्ण

व्योम ex_btc8192e2ant_display_coex_info(काष्ठा btc_coexist *btcoexist,
				       काष्ठा seq_file *m)
अणु
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;
	u8 u8पंचांगp[4], i, bt_info_ext, ps_tdma_हाल = 0;
	u16 u16पंचांगp[4];
	u32 u32पंचांगp[4];
	bool roam = false, scan = false, link = false, wअगरi_under_5g = false;
	bool bt_hs_on = false, wअगरi_busy = false;
	पूर्णांक wअगरi_rssi = 0, bt_hs_rssi = 0;
	u32 wअगरi_bw, wअगरi_traffic_dir;
	u8 wअगरi_करोt11_chnl, wअगरi_hs_chnl;
	u32 fw_ver = 0, bt_patch_ver = 0;

	seq_माला_दो(m, "\n ============[BT Coexist info]============");

	अगर (btcoexist->manual_control) अणु
		seq_माला_दो(m, "\n ===========[Under Manual Control]===========");
		seq_माला_दो(m, "\n ==========================================");
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %d/ %d ", "Ant PG number/ Ant mechanism:",
		   board_info->pg_ant_num, board_info->btdm_ant_num);

	seq_म_लिखो(m, "\n %-35s = %s / %d", "BT stack/ hci ext ver",
		   ((stack_info->profile_notअगरied) ? "Yes" : "No"),
		   stack_info->hci_version);

	btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER, &bt_patch_ver);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
	seq_म_लिखो(m, "\n %-35s = %d_%d/ 0x%x/ 0x%x(%d)",
		   "CoexVer/ FwVer/ PatchVer",
		   glcoex_ver_date_8192e_2ant, glcoex_ver_8192e_2ant,
		   fw_ver, bt_patch_ver, bt_patch_ver);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_DOT11_CHNL,
			   &wअगरi_करोt11_chnl);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_HS_CHNL, &wअगरi_hs_chnl);
	seq_म_लिखो(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsMode(HsChnl)",
		   wअगरi_करोt11_chnl, bt_hs_on, wअगरi_hs_chnl);

	seq_म_लिखो(m, "\n %-35s = %3ph ",
		   "H2C Wifi inform bt chnl Info", coex_dm->wअगरi_chnl_info);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "Wifi rssi/ HS rssi", wअगरi_rssi, bt_hs_rssi);

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
		   ((BTC_WIFI_BW_LEGACY == wअगरi_bw) ? "Legacy" :
			(((BTC_WIFI_BW_HT40 == wअगरi_bw) ? "HT40" : "HT20"))),
		   ((!wअगरi_busy) ? "idle" :
			((BTC_WIFI_TRAFFIC_TX == wअगरi_traffic_dir) ?
				"uplink" : "downlink")));

	seq_म_लिखो(m, "\n %-35s = [%s/ %d/ %d] ",
		   "BT [status/ rssi/ retryCnt]",
		   ((btcoexist->bt_info.bt_disabled) ? ("disabled") :
		    ((coex_sta->c2h_bt_inquiry_page) ?
		     ("inquiry/page scan") :
		      ((BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE ==
			coex_dm->bt_status) ? "non-connected idle" :
			 ((BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE ==
			   coex_dm->bt_status) ? "connected-idle" : "busy")))),
		   coex_sta->bt_rssi, coex_sta->bt_retry_cnt);

	seq_म_लिखो(m, "\n %-35s = %d / %d / %d / %d",
		   "SCO/HID/PAN/A2DP", stack_info->sco_exist,
		   stack_info->hid_exist, stack_info->pan_exist,
		   stack_info->a2dp_exist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_BT_LINK_INFO, m);

	bt_info_ext = coex_sta->bt_info_ext;
	seq_म_लिखो(m, "\n %-35s = %s",
		   "BT Info A2DP rate",
		   (bt_info_ext&BIT0) ? "Basic rate" : "EDR rate");

	क्रम (i = 0; i < BT_INFO_SRC_8192E_2ANT_MAX; i++) अणु
		अगर (coex_sta->bt_info_c2h_cnt[i]) अणु
			seq_म_लिखो(m, "\n %-35s = %7ph(%d)",
				   glbt_info_src_8192e_2ant[i],
				   coex_sta->bt_info_c2h[i],
				   coex_sta->bt_info_c2h_cnt[i]);
		पूर्ण
	पूर्ण

	seq_म_लिखो(m, "\n %-35s = %s/%s",
		   "PS state, IPS/LPS",
		   ((coex_sta->under_ips ? "IPS ON" : "IPS OFF")),
		   ((coex_sta->under_lps ? "LPS ON" : "LPS OFF")));
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_FW_PWR_MODE_CMD, m);

	seq_म_लिखो(m, "\n %-35s = 0x%x ", "SS Type",
		   coex_dm->cur_ss_type);

	/* Sw mechanism	*/
	seq_म_लिखो(m, "\n %-35s",
		   "============[Sw mechanism]============");
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d ",
		   "SM1[ShRf/ LpRA/ LimDig]", coex_dm->cur_rf_rx_lpf_shrink,
		   coex_dm->cur_low_penalty_ra, coex_dm->limited_dig);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d(0x%x) ",
		   "SM2[AgcT/ AdcB/ SwDacSwing(lvl)]",
		   coex_dm->cur_agc_table_en, coex_dm->cur_adc_back_off,
		   coex_dm->cur_dac_swing_on, coex_dm->cur_dac_swing_lvl);

	seq_म_लिखो(m, "\n %-35s = 0x%x ", "Rate Mask",
		   btcoexist->bt_info.ra_mask);

	/* Fw mechanism	*/
	seq_म_लिखो(m, "\n %-35s",
		   "============[Fw mechanism]============");

	ps_tdma_हाल = coex_dm->cur_ps_tdma;
	seq_म_लिखो(m,
		   "\n %-35s = %5ph case-%d (auto:%d)",
		   "PS TDMA", coex_dm->ps_tdma_para,
		   ps_tdma_हाल, coex_dm->स्वतः_tdma_adjust);

	seq_म_लिखो(m, "\n %-35s = %d/ %d ",
		   "DecBtPwr/ IgnWlanAct",
		   coex_dm->cur_dec_bt_pwr, coex_dm->cur_ignore_wlan_act);

	/* Hw setting */
	seq_म_लिखो(m, "\n %-35s",
		   "============[Hw setting]============");

	seq_म_लिखो(m, "\n %-35s = 0x%x",
		   "RF-A, 0x1e initVal", coex_dm->bt_rf0x1e_backup);

	seq_म_लिखो(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "backup ARFR1/ARFR2/RL/AMaxTime", coex_dm->backup_arfr_cnt1,
		   coex_dm->backup_arfr_cnt2, coex_dm->backup_retry_limit,
		   coex_dm->backup_ampdu_maxसमय);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x430);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x434);
	u16पंचांगp[0] = btcoexist->btc_पढ़ो_2byte(btcoexist, 0x42a);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x456);
	seq_म_लिखो(m, "\n %-35s = 0x%x/0x%x/0x%x/0x%x",
		   "0x430/0x434/0x42a/0x456",
		   u32पंचांगp[0], u32पंचांगp[1], u16पंचांगp[0], u8पंचांगp[0]);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xc04);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xd04);
	u32पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x90c);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x/ 0x%x",
		   "0xc04/ 0xd04/ 0x90c", u32पंचांगp[0], u32पंचांगp[1], u32पंचांगp[2]);

	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x778);
	seq_म_लिखो(m, "\n %-35s = 0x%x", "0x778", u8पंचांगp[0]);

	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x92c);
	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x930);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x92c/ 0x930", (u8पंचांगp[0]), u32पंचांगp[0]);

	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x40);
	u8पंचांगp[1] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x4f);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x40/ 0x4f", u8पंचांगp[0], u8पंचांगp[1]);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x550);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x522);
	seq_म_लिखो(m, "\n %-35s = 0x%x/ 0x%x",
		   "0x550(bcn ctrl)/0x522", u32पंचांगp[0], u8पंचांगp[0]);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0xc50);
	seq_म_लिखो(m, "\n %-35s = 0x%x", "0xc50(dig)",
		   u32पंचांगp[0]);

	u32पंचांगp[0] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c0);
	u32पंचांगp[1] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c4);
	u32पंचांगp[2] = btcoexist->btc_पढ़ो_4byte(btcoexist, 0x6c8);
	u8पंचांगp[0] = btcoexist->btc_पढ़ो_1byte(btcoexist, 0x6cc);
	seq_म_लिखो(m,
		   "\n %-35s = 0x%x/ 0x%x/ 0x%x/ 0x%x",
		   "0x6c0/0x6c4/0x6c8/0x6cc(coexTable)",
		   u32पंचांगp[0], u32पंचांगp[1], u32पंचांगp[2], u8पंचांगp[0]);

	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x770(hp rx[31:16]/tx[15:0])",
		   coex_sta->high_priority_rx, coex_sta->high_priority_tx);
	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "0x774(lp rx[31:16]/tx[15:0])",
		   coex_sta->low_priority_rx, coex_sta->low_priority_tx);
	अगर (btcoexist->स्वतः_report_2ant)
		btc8192e2ant_monitor_bt_ctr(btcoexist);
	btcoexist->btc_disp_dbg_msg(btcoexist, BTC_DBG_DISP_COEX_STATISTICS, m);
पूर्ण

व्योम ex_btc8192e2ant_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_IPS_ENTER == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS ENTER notify\n");
		coex_sta->under_ips = true;
		btc8192e2ant_coex_all_off(btcoexist);
	पूर्ण अन्यथा अगर (BTC_IPS_LEAVE == type) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], IPS LEAVE notify\n");
		coex_sta->under_ips = false;
	पूर्ण
पूर्ण

व्योम ex_btc8192e2ant_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
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

व्योम ex_btc8192e2ant_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_SCAN_START == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN START notify\n");
	अन्यथा अगर (BTC_SCAN_FINISH == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], SCAN FINISH notify\n");
पूर्ण

व्योम ex_btc8192e2ant_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (BTC_ASSOCIATE_START == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT START notify\n");
	अन्यथा अगर (BTC_ASSOCIATE_FINISH == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], CONNECT FINISH notify\n");
पूर्ण

व्योम ex_btc8192e2ant_media_status_notअगरy(काष्ठा btc_coexist *btcoexist,
					 u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 h2c_parameter[3] = अणु0पूर्ण;
	u32 wअगरi_bw;
	u8 wअगरi_center_chnl;

	अगर (btcoexist->manual_control ||
	    btcoexist->stop_coex_dm ||
	    btcoexist->bt_info.bt_disabled)
		वापस;

	अगर (BTC_MEDIA_CONNECT == type)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA connect notify\n");
	अन्यथा
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], MEDIA disconnect notify\n");

	/* only 2.4G we need to inक्रमm bt the chnl mask */
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_CENTRAL_CHNL,
			   &wअगरi_center_chnl);
	अगर ((BTC_MEDIA_CONNECT == type) &&
	    (wअगरi_center_chnl <= 14)) अणु
		h2c_parameter[0] = 0x1;
		h2c_parameter[1] = wअगरi_center_chnl;
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

व्योम ex_btc8192e2ant_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist,
					   u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (type == BTC_PACKET_DHCP)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], DHCP Packet notify\n");
पूर्ण

व्योम ex_btc8192e2ant_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist,
				    u8 *पंचांगp_buf, u8 length)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 bt_info = 0;
	u8 i, rsp_source = 0;
	bool bt_busy = false, limited_dig = false;
	bool wअगरi_connected = false;

	coex_sta->c2h_bt_info_req_sent = false;

	rsp_source = पंचांगp_buf[0] & 0xf;
	अगर (rsp_source >= BT_INFO_SRC_8192E_2ANT_MAX)
		rsp_source = BT_INFO_SRC_8192E_2ANT_WIFI_FW;
	coex_sta->bt_info_c2h_cnt[rsp_source]++;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"[BTCoex], Bt info[%d], length=%d, hex data = [",
		rsp_source, length);
	क्रम (i = 0; i < length; i++) अणु
		coex_sta->bt_info_c2h[rsp_source][i] = पंचांगp_buf[i];
		अगर (i == 1)
			bt_info = पंचांगp_buf[i];
		अगर (i == length-1)
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x]\n", पंचांगp_buf[i]);
		अन्यथा
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"0x%02x, ", पंचांगp_buf[i]);
	पूर्ण

	अगर (BT_INFO_SRC_8192E_2ANT_WIFI_FW != rsp_source) अणु
		/* [3:0] */
		coex_sta->bt_retry_cnt =
			coex_sta->bt_info_c2h[rsp_source][2] & 0xf;

		coex_sta->bt_rssi =
			coex_sta->bt_info_c2h[rsp_source][3] * 2 + 10;

		coex_sta->bt_info_ext =
			coex_sta->bt_info_c2h[rsp_source][4];

		/* Here we need to resend some wअगरi info to BT
		 * because bt is reset and loss of the info.
		 */
		अगर ((coex_sta->bt_info_ext & BIT1)) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
				"bit1, send wifi BW&Chnl to BT!!\n");
			btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_CONNECTED,
					   &wअगरi_connected);
			अगर (wअगरi_connected)
				ex_btc8192e2ant_media_status_notअगरy(
							btcoexist,
							BTC_MEDIA_CONNECT);
			अन्यथा
				ex_btc8192e2ant_media_status_notअगरy(
							btcoexist,
							BTC_MEDIA_DISCONNECT);
		पूर्ण

		अगर ((coex_sta->bt_info_ext & BIT3)) अणु
			अगर (!btcoexist->manual_control &&
			    !btcoexist->stop_coex_dm) अणु
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
					"bit3, BT NOT ignore Wlan active!\n");
				btc8192e2ant_ignore_wlan_act(btcoexist,
							     FORCE_EXEC,
							     false);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* BT alपढ़ोy NOT ignore Wlan active,
			 * करो nothing here.
			 */
		पूर्ण

		अगर (!btcoexist->स्वतः_report_2ant) अणु
			अगर (!(coex_sta->bt_info_ext & BIT4))
				btc8192e2ant_bt_स्वतः_report(btcoexist,
							    FORCE_EXEC,
							    true);
		पूर्ण
	पूर्ण

	/* check BIT2 first ==> check अगर bt is under inquiry or page scan */
	अगर (bt_info & BT_INFO_8192E_2ANT_B_INQ_PAGE)
		coex_sta->c2h_bt_inquiry_page = true;
	अन्यथा
		coex_sta->c2h_bt_inquiry_page = false;

	/* set link exist status */
	अगर (!(bt_info&BT_INFO_8192E_2ANT_B_CONNECTION)) अणु
		coex_sta->bt_link_exist = false;
		coex_sta->pan_exist = false;
		coex_sta->a2dp_exist = false;
		coex_sta->hid_exist = false;
		coex_sta->sco_exist = false;
	पूर्ण अन्यथा अणु/* connection exists */
		coex_sta->bt_link_exist = true;
		अगर (bt_info & BT_INFO_8192E_2ANT_B_FTP)
			coex_sta->pan_exist = true;
		अन्यथा
			coex_sta->pan_exist = false;
		अगर (bt_info & BT_INFO_8192E_2ANT_B_A2DP)
			coex_sta->a2dp_exist = true;
		अन्यथा
			coex_sta->a2dp_exist = false;
		अगर (bt_info & BT_INFO_8192E_2ANT_B_HID)
			coex_sta->hid_exist = true;
		अन्यथा
			coex_sta->hid_exist = false;
		अगर (bt_info & BT_INFO_8192E_2ANT_B_SCO_ESCO)
			coex_sta->sco_exist = true;
		अन्यथा
			coex_sta->sco_exist = false;
	पूर्ण

	btc8192e2ant_update_bt_link_info(btcoexist);

	अगर (!(bt_info & BT_INFO_8192E_2ANT_B_CONNECTION)) अणु
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_NON_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], BT Non-Connected idle!!!\n");
	पूर्ण अन्यथा अगर (bt_info == BT_INFO_8192E_2ANT_B_CONNECTION) अणु
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_CONNECTED_IDLE;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bt_infoNotify(), BT Connected-idle!!!\n");
	पूर्ण अन्यथा अगर ((bt_info & BT_INFO_8192E_2ANT_B_SCO_ESCO) ||
		   (bt_info & BT_INFO_8192E_2ANT_B_SCO_BUSY)) अणु
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_SCO_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bt_infoNotify(), BT SCO busy!!!\n");
	पूर्ण अन्यथा अगर (bt_info & BT_INFO_8192E_2ANT_B_ACL_BUSY) अणु
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_ACL_BUSY;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], bt_infoNotify(), BT ACL busy!!!\n");
	पूर्ण अन्यथा अणु
		coex_dm->bt_status = BT_8192E_2ANT_BT_STATUS_MAX;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex]bt_infoNotify(), BT Non-Defined state!!!\n");
	पूर्ण

	अगर ((BT_8192E_2ANT_BT_STATUS_ACL_BUSY == coex_dm->bt_status) ||
	    (BT_8192E_2ANT_BT_STATUS_SCO_BUSY == coex_dm->bt_status) ||
	    (BT_8192E_2ANT_BT_STATUS_ACL_SCO_BUSY == coex_dm->bt_status)) अणु
		bt_busy = true;
		limited_dig = true;
	पूर्ण अन्यथा अणु
		bt_busy = false;
		limited_dig = false;
	पूर्ण

	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_TRAFFIC_BUSY, &bt_busy);

	coex_dm->limited_dig = limited_dig;
	btcoexist->btc_set(btcoexist, BTC_SET_BL_BT_LIMITED_DIG, &limited_dig);

	btc8192e2ant_run_coexist_mechanism(btcoexist);
पूर्ण

व्योम ex_btc8192e2ant_halt_notअगरy(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD, "[BTCoex], Halt notify\n");

	btc8192e2ant_ignore_wlan_act(btcoexist, FORCE_EXEC, true);
	ex_btc8192e2ant_media_status_notअगरy(btcoexist, BTC_MEDIA_DISCONNECT);
पूर्ण

व्योम ex_btc8192e2ant_periodical(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	अटल u8 dis_ver_info_cnt;
	u32 fw_ver = 0, bt_patch_ver = 0;
	काष्ठा btc_board_info *board_info = &btcoexist->board_info;
	काष्ठा btc_stack_info *stack_info = &btcoexist->stack_info;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"=======================Periodical=======================\n");
	अगर (dis_ver_info_cnt <= 5) अणु
		dis_ver_info_cnt += 1;
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"************************************************\n");
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"Ant PG Num/ Ant Mech/ Ant Pos = %d/ %d/ %d\n",
			board_info->pg_ant_num, board_info->btdm_ant_num,
			board_info->btdm_ant_pos);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"BT stack/ hci ext ver = %s / %d\n",
			((stack_info->profile_notअगरied) ? "Yes" : "No"),
			stack_info->hci_version);
		btcoexist->btc_get(btcoexist, BTC_GET_U4_BT_PATCH_VER,
				   &bt_patch_ver);
		btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_FW_VER, &fw_ver);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"CoexVer/ FwVer/ PatchVer = %d_%x/ 0x%x/ 0x%x(%d)\n",
			glcoex_ver_date_8192e_2ant, glcoex_ver_8192e_2ant,
			fw_ver, bt_patch_ver, bt_patch_ver);
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"************************************************\n");
	पूर्ण

	अगर (!btcoexist->स्वतः_report_2ant) अणु
		btc8192e2ant_query_bt_info(btcoexist);
		btc8192e2ant_monitor_bt_ctr(btcoexist);
		btc8192e2ant_monitor_bt_enable_disable(btcoexist);
	पूर्ण अन्यथा अणु
		अगर (btc8192e2ant_is_wअगरi_status_changed(btcoexist) ||
		    coex_dm->स्वतः_tdma_adjust)
			btc8192e2ant_run_coexist_mechanism(btcoexist);
	पूर्ण
पूर्ण
