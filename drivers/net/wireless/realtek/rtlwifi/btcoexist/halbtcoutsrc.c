<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2007-2013  Realtek Corporation.*/

#समावेश "halbt_precomp.h"

/***************************************************
 *		Debug related function
 ***************************************************/

अटल स्थिर अक्षर *स्थिर gl_btc_wअगरi_bw_string[] = अणु
	"11bg",
	"HT20",
	"HT40",
	"HT80",
	"HT160"
पूर्ण;

अटल स्थिर अक्षर *स्थिर gl_btc_wअगरi_freq_string[] = अणु
	"2.4G",
	"5G"
पूर्ण;

अटल bool halbtc_is_bt_coexist_available(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (!btcoexist->binded || शून्य == btcoexist->adapter)
		वापस false;

	वापस true;
पूर्ण

अटल bool halbtc_is_wअगरi_busy(काष्ठा rtl_priv *rtlpriv)
अणु
	अगर (rtlpriv->link_info.busytraffic)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल व्योम halbtc_dbg_init(व्योम)
अणु
पूर्ण

/***************************************************
 *		helper function
 ***************************************************/
अटल bool is_any_client_connect_to_ap(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	bool ret = false;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT ||
	    mac->opmode == NL80211_IFTYPE_AP) अणु
		spin_lock_bh(&rtlpriv->locks.entry_list_lock);
		अगर (!list_empty(&rtlpriv->entry_list))
			ret = true;
		spin_unlock_bh(&rtlpriv->locks.entry_list_lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल bool halbtc_legacy(काष्ठा rtl_priv *adapter)
अणु
	काष्ठा rtl_priv *rtlpriv = adapter;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);

	bool is_legacy = false;

	अगर ((mac->mode == WIRELESS_MODE_B) || (mac->mode == WIRELESS_MODE_G))
		is_legacy = true;

	वापस is_legacy;
पूर्ण

bool halbtc_is_wअगरi_uplink(काष्ठा rtl_priv *adapter)
अणु
	काष्ठा rtl_priv *rtlpriv = adapter;

	अगर (rtlpriv->link_info.tx_busy_traffic)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल u32 halbtc_get_wअगरi_bw(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u32 wअगरi_bw = BTC_WIFI_BW_HT20;

	अगर (halbtc_legacy(rtlpriv)) अणु
		wअगरi_bw = BTC_WIFI_BW_LEGACY;
	पूर्ण अन्यथा अणु
		चयन (rtlphy->current_chan_bw) अणु
		हाल HT_CHANNEL_WIDTH_20:
			wअगरi_bw = BTC_WIFI_BW_HT20;
			अवरोध;
		हाल HT_CHANNEL_WIDTH_20_40:
			wअगरi_bw = BTC_WIFI_BW_HT40;
			अवरोध;
		हाल HT_CHANNEL_WIDTH_80:
			wअगरi_bw = BTC_WIFI_BW_HT80;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस wअगरi_bw;
पूर्ण

अटल u8 halbtc_get_wअगरi_central_chnl(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा rtl_phy	*rtlphy = &(rtlpriv->phy);
	u8 chnl = 1;

	अगर (rtlphy->current_channel != 0)
		chnl = rtlphy->current_channel;
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"%s:%d\n", __func__, chnl);
	वापस chnl;
पूर्ण

अटल u8 rtl_get_hwpg_single_ant_path(काष्ठा rtl_priv *rtlpriv)
अणु
	वापस rtlpriv->btcoexist.btc_info.single_ant_path;
पूर्ण

अटल u8 rtl_get_hwpg_bt_type(काष्ठा rtl_priv *rtlpriv)
अणु
	वापस rtlpriv->btcoexist.btc_info.bt_type;
पूर्ण

अटल u8 rtl_get_hwpg_ant_num(काष्ठा rtl_priv *rtlpriv)
अणु
	u8 num;

	अगर (rtlpriv->btcoexist.btc_info.ant_num == ANT_X2)
		num = 2;
	अन्यथा
		num = 1;

	वापस num;
पूर्ण

अटल u8 rtl_get_hwpg_package_type(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	वापस rtlhal->package_type;
पूर्ण

अटल
u8 rtl_get_hwpg_rfe_type(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	वापस rtlhal->rfe_type;
पूर्ण

अटल
bool halbtc_is_hw_mailbox_exist(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (IS_HARDWARE_TYPE_8812(btcoexist->adapter))
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल
bool halbtc_send_bt_mp_operation(काष्ठा btc_coexist *btcoexist, u8 op_code,
				 u8 *cmd, u32 len, अचिन्हित दीर्घ रुको_ms)
अणु
	काष्ठा rtl_priv *rtlpriv;
	स्थिर u8 oper_ver = 0;
	u8 req_num;

	अगर (!halbtc_is_hw_mailbox_exist(btcoexist))
		वापस false;

	अगर (रुको_ms)	/* beक्रमe h2c to aव्योम race condition */
		reinit_completion(&btcoexist->bt_mp_comp);

	rtlpriv = btcoexist->adapter;

	/* fill req_num by op_code, and rtl_btc_bपंचांगpinfo_notअगरy() use it
	 * to know message type
	 */
	चयन (op_code) अणु
	हाल BT_OP_GET_BT_VERSION:
		req_num = BT_SEQ_GET_BT_VERSION;
		अवरोध;
	हाल BT_OP_GET_AFH_MAP_L:
		req_num = BT_SEQ_GET_AFH_MAP_L;
		अवरोध;
	हाल BT_OP_GET_AFH_MAP_M:
		req_num = BT_SEQ_GET_AFH_MAP_M;
		अवरोध;
	हाल BT_OP_GET_AFH_MAP_H:
		req_num = BT_SEQ_GET_AFH_MAP_H;
		अवरोध;
	हाल BT_OP_GET_BT_COEX_SUPPORTED_FEATURE:
		req_num = BT_SEQ_GET_BT_COEX_SUPPORTED_FEATURE;
		अवरोध;
	हाल BT_OP_GET_BT_COEX_SUPPORTED_VERSION:
		req_num = BT_SEQ_GET_BT_COEX_SUPPORTED_VERSION;
		अवरोध;
	हाल BT_OP_GET_BT_ANT_DET_VAL:
		req_num = BT_SEQ_GET_BT_ANT_DET_VAL;
		अवरोध;
	हाल BT_OP_GET_BT_BLE_SCAN_PARA:
		req_num = BT_SEQ_GET_BT_BLE_SCAN_PARA;
		अवरोध;
	हाल BT_OP_GET_BT_BLE_SCAN_TYPE:
		req_num = BT_SEQ_GET_BT_BLE_SCAN_TYPE;
		अवरोध;
	हाल BT_OP_GET_BT_DEVICE_INFO:
		req_num = BT_SEQ_GET_BT_DEVICE_INFO;
		अवरोध;
	हाल BT_OP_GET_BT_FORBIDDEN_SLOT_VAL:
		req_num = BT_SEQ_GET_BT_FORB_SLOT_VAL;
		अवरोध;
	हाल BT_OP_WRITE_REG_ADDR:
	हाल BT_OP_WRITE_REG_VALUE:
	हाल BT_OP_READ_REG:
	शेष:
		req_num = BT_SEQ_DONT_CARE;
		अवरोध;
	पूर्ण

	cmd[0] |= (oper_ver & 0x0f);		/* Set OperVer */
	cmd[0] |= ((req_num << 4) & 0xf0);	/* Set ReqNum */
	cmd[1] = op_code;
	rtlpriv->cfg->ops->fill_h2c_cmd(rtlpriv->mac80211.hw, 0x67, len, cmd);

	/* रुको? */
	अगर (!रुको_ms)
		वापस true;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"btmpinfo wait req_num=%d wait=%ld\n", req_num, रुको_ms);

	अगर (रुको_क्रम_completion_समयout(&btcoexist->bt_mp_comp,
					msecs_to_jअगरfies(रुको_ms)) == 0) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"btmpinfo wait (req_num=%d) timeout\n", req_num);

		वापस false;	/* समयout */
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम halbtc_leave_lps(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv;
	bool ap_enable = false;

	rtlpriv = btcoexist->adapter;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);

	अगर (ap_enable) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"%s()<--dont leave lps under AP mode\n", __func__);
		वापस;
	पूर्ण

	btcoexist->bt_info.bt_ctrl_lps = true;
	btcoexist->bt_info.bt_lps_on = false;
	/* FIXME: Context is unclear. Is it allowed to block? */
	rtl_lps_leave(rtlpriv->mac80211.hw, false);
पूर्ण

अटल व्योम halbtc_enter_lps(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv;
	bool ap_enable = false;

	rtlpriv = btcoexist->adapter;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_AP_MODE_ENABLE,
			   &ap_enable);

	अगर (ap_enable) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			"%s()<--dont enter lps under AP mode\n", __func__);
		वापस;
	पूर्ण

	btcoexist->bt_info.bt_ctrl_lps = true;
	btcoexist->bt_info.bt_lps_on = true;
	/* FIXME: Context is unclear. Is it allowed to block? */
	rtl_lps_enter(rtlpriv->mac80211.hw, false);
पूर्ण

अटल व्योम halbtc_normal_lps(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv;

	rtlpriv = btcoexist->adapter;

	अगर (btcoexist->bt_info.bt_ctrl_lps) अणु
		btcoexist->bt_info.bt_lps_on = false;
		/* FIXME: Context is unclear. Is it allowed to block? */
		rtl_lps_leave(rtlpriv->mac80211.hw, false);
		btcoexist->bt_info.bt_ctrl_lps = false;
	पूर्ण
पूर्ण

अटल व्योम halbtc_pre_normal_lps(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (btcoexist->bt_info.bt_ctrl_lps) अणु
		btcoexist->bt_info.bt_lps_on = false;
		/* FIXME: Context is unclear. Is it allowed to block? */
		rtl_lps_leave(rtlpriv->mac80211.hw, false);
	पूर्ण
पूर्ण

अटल व्योम halbtc_post_normal_lps(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (btcoexist->bt_info.bt_ctrl_lps)
		btcoexist->bt_info.bt_ctrl_lps = false;
पूर्ण

अटल व्योम halbtc_leave_low_घातer(काष्ठा btc_coexist *btcoexist)
अणु
पूर्ण

अटल व्योम halbtc_normal_low_घातer(काष्ठा btc_coexist *btcoexist)
अणु
पूर्ण

अटल व्योम halbtc_disable_low_घातer(काष्ठा btc_coexist *btcoexist,
				     bool low_pwr_disable)
अणु
	/* TODO: original/leave 32k low घातer */
	btcoexist->bt_info.bt_disable_low_pwr = low_pwr_disable;
पूर्ण

अटल व्योम halbtc_aggregation_check(काष्ठा btc_coexist *btcoexist)
अणु
	bool need_to_act = false;
	अटल अचिन्हित दीर्घ pre_समय;
	अचिन्हित दीर्घ cur_समय = 0;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	/* To व्योम continuous deleteBA=>addBA=>deleteBA=>addBA
	 * This function is not allowed to continuous called
	 * It can only be called after 8 seconds
	 */

	cur_समय = jअगरfies;
	अगर (jअगरfies_to_msecs(cur_समय - pre_समय) <= 8000) अणु
		/* over 8 seconds you can execute this function again. */
		वापस;
	पूर्ण
	pre_समय = cur_समय;

	अगर (btcoexist->bt_info.reject_agg_pkt) अणु
		need_to_act = true;
		btcoexist->bt_info.pre_reject_agg_pkt =
			btcoexist->bt_info.reject_agg_pkt;
	पूर्ण अन्यथा अणु
		अगर (btcoexist->bt_info.pre_reject_agg_pkt) अणु
			need_to_act = true;
			btcoexist->bt_info.pre_reject_agg_pkt =
				btcoexist->bt_info.reject_agg_pkt;
		पूर्ण

		अगर (btcoexist->bt_info.pre_bt_ctrl_agg_buf_size !=
		    btcoexist->bt_info.bt_ctrl_agg_buf_size) अणु
			need_to_act = true;
			btcoexist->bt_info.pre_bt_ctrl_agg_buf_size =
				btcoexist->bt_info.bt_ctrl_agg_buf_size;
		पूर्ण

		अगर (btcoexist->bt_info.bt_ctrl_agg_buf_size) अणु
			अगर (btcoexist->bt_info.pre_agg_buf_size !=
			    btcoexist->bt_info.agg_buf_size) अणु
				need_to_act = true;
			पूर्ण
			btcoexist->bt_info.pre_agg_buf_size =
				btcoexist->bt_info.agg_buf_size;
		पूर्ण

		अगर (need_to_act)
			rtl_rx_ampdu_apply(rtlpriv);
	पूर्ण
पूर्ण

अटल u32 halbtc_get_bt_patch_version(काष्ठा btc_coexist *btcoexist)
अणु
	u8 cmd_buffer[4] = अणु0पूर्ण;

	अगर (btcoexist->bt_info.bt_real_fw_ver)
		जाओ label_करोne;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_BT_VERSION,
				    cmd_buffer, 4, 200);

label_करोne:
	वापस btcoexist->bt_info.bt_real_fw_ver;
पूर्ण

अटल u32 halbtc_get_bt_coex_supported_feature(व्योम *btc_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[4] = अणु0पूर्ण;

	अगर (btcoexist->bt_info.bt_supported_feature)
		जाओ label_करोne;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist,
				    BT_OP_GET_BT_COEX_SUPPORTED_FEATURE,
				    cmd_buffer, 4, 200);

label_करोne:
	वापस btcoexist->bt_info.bt_supported_feature;
पूर्ण

अटल u32 halbtc_get_bt_coex_supported_version(व्योम *btc_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[4] = अणु0पूर्ण;

	अगर (btcoexist->bt_info.bt_supported_version)
		जाओ label_करोne;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist,
				    BT_OP_GET_BT_COEX_SUPPORTED_VERSION,
				    cmd_buffer, 4, 200);

label_करोne:
	वापस btcoexist->bt_info.bt_supported_version;
पूर्ण

अटल u32 halbtc_get_bt_device_info(व्योम *btc_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[4] = अणु0पूर्ण;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist,
				    BT_OP_GET_BT_DEVICE_INFO,
				    cmd_buffer, 4, 200);

	वापस btcoexist->bt_info.bt_device_info;
पूर्ण

अटल u32 halbtc_get_bt_क्रमbidden_slot_val(व्योम *btc_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[4] = अणु0पूर्ण;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist,
				    BT_OP_GET_BT_FORBIDDEN_SLOT_VAL,
				    cmd_buffer, 4, 200);

	वापस btcoexist->bt_info.bt_क्रमb_slot_val;
पूर्ण

अटल u32 halbtc_get_wअगरi_link_status(काष्ठा btc_coexist *btcoexist)
अणु
	/* वापस value:
	 * [31:16] => connected port number
	 * [15:0]  => port connected bit define
	 */
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	u32 ret_val = 0;
	u32 port_connected_status = 0, num_of_connected_port = 0;

	अगर (mac->opmode == NL80211_IFTYPE_STATION &&
	    mac->link_state >= MAC80211_LINKED) अणु
		port_connected_status |= WIFI_STA_CONNECTED;
		num_of_connected_port++;
	पूर्ण
	/* AP & ADHOC & MESH */
	अगर (is_any_client_connect_to_ap(btcoexist)) अणु
		port_connected_status |= WIFI_AP_CONNECTED;
		num_of_connected_port++;
	पूर्ण
	/* TODO: P2P Connected Status */

	ret_val = (num_of_connected_port << 16) | port_connected_status;

	वापस ret_val;
पूर्ण

अटल s32 halbtc_get_wअगरi_rssi(काष्ठा rtl_priv *rtlpriv)
अणु
	वापस rtlpriv->dm.undec_sm_pwdb;
पूर्ण

अटल bool halbtc_get(व्योम *व्योम_btcoexist, u8 get_type, व्योम *out_buf)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)व्योम_btcoexist;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	bool *bool_पंचांगp = (bool *)out_buf;
	पूर्णांक *s32_पंचांगp = (पूर्णांक *)out_buf;
	u32 *u32_पंचांगp = (u32 *)out_buf;
	u8 *u8_पंचांगp = (u8 *)out_buf;
	bool पंचांगp = false;
	bool ret = true;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस false;

	चयन (get_type) अणु
	हाल BTC_GET_BL_HS_OPERATION:
		*bool_पंचांगp = false;
		ret = false;
		अवरोध;
	हाल BTC_GET_BL_HS_CONNECTING:
		*bool_पंचांगp = false;
		ret = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_CONNECTED:
		अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_STATION &&
		    rtlpriv->mac80211.link_state >= MAC80211_LINKED)
			पंचांगp = true;
		अगर (is_any_client_connect_to_ap(btcoexist))
			पंचांगp = true;
		*bool_पंचांगp = पंचांगp;
		अवरोध;
	हाल BTC_GET_BL_WIFI_DUAL_BAND_CONNECTED:
		*u8_पंचांगp = BTC_MULTIPORT_SCC;
		अवरोध;
	हाल BTC_GET_BL_WIFI_BUSY:
		अगर (halbtc_is_wअगरi_busy(rtlpriv))
			*bool_पंचांगp = true;
		अन्यथा
			*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_SCAN:
		अगर (mac->act_scanning)
			*bool_पंचांगp = true;
		अन्यथा
			*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_LINK:
		अगर (mac->link_state == MAC80211_LINKING)
			*bool_पंचांगp = true;
		अन्यथा
			*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_ROAM:
		अगर (mac->link_state == MAC80211_LINKING)
			*bool_पंचांगp = true;
		अन्यथा
			*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_4_WAY_PROGRESS:
		*bool_पंचांगp = rtlpriv->btcoexist.btc_info.in_4way;
		अवरोध;
	हाल BTC_GET_BL_WIFI_UNDER_5G:
		अगर (rtlhal->current_bandtype == BAND_ON_5G)
			*bool_पंचांगp = true;
		अन्यथा
			*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_AP_MODE_ENABLE:
		अगर (mac->opmode == NL80211_IFTYPE_AP)
			*bool_पंचांगp = true;
		अन्यथा
			*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_ENABLE_ENCRYPTION:
		अगर (NO_ENCRYPTION == rtlpriv->sec.pairwise_enc_algorithm)
			*bool_पंचांगp = false;
		अन्यथा
			*bool_पंचांगp = true;
		अवरोध;
	हाल BTC_GET_BL_WIFI_UNDER_B_MODE:
		अगर (rtlpriv->mac80211.mode == WIRELESS_MODE_B)
			*bool_पंचांगp = true;
		अन्यथा
			*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_EXT_SWITCH:
		*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_WIFI_IS_IN_MP_MODE:
		*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_IS_ASUS_8723B:
		*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_BL_RF4CE_CONNECTED:
		*bool_पंचांगp = false;
		अवरोध;
	हाल BTC_GET_S4_WIFI_RSSI:
		*s32_पंचांगp = halbtc_get_wअगरi_rssi(rtlpriv);
		अवरोध;
	हाल BTC_GET_S4_HS_RSSI:
		*s32_पंचांगp = 0;
		ret = false;
		अवरोध;
	हाल BTC_GET_U4_WIFI_BW:
		*u32_पंचांगp = halbtc_get_wअगरi_bw(btcoexist);
		अवरोध;
	हाल BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION:
		अगर (halbtc_is_wअगरi_uplink(rtlpriv))
			*u32_पंचांगp = BTC_WIFI_TRAFFIC_TX;
		अन्यथा
			*u32_पंचांगp = BTC_WIFI_TRAFFIC_RX;
		अवरोध;
	हाल BTC_GET_U4_WIFI_FW_VER:
		*u32_पंचांगp = (rtlhal->fw_version << 16) | rtlhal->fw_subversion;
		अवरोध;
	हाल BTC_GET_U4_WIFI_LINK_STATUS:
		*u32_पंचांगp = halbtc_get_wअगरi_link_status(btcoexist);
		अवरोध;
	हाल BTC_GET_U4_BT_PATCH_VER:
		*u32_पंचांगp = halbtc_get_bt_patch_version(btcoexist);
		अवरोध;
	हाल BTC_GET_U4_VENDOR:
		*u32_पंचांगp = BTC_VENDOR_OTHER;
		अवरोध;
	हाल BTC_GET_U4_SUPPORTED_VERSION:
		*u32_पंचांगp = halbtc_get_bt_coex_supported_version(btcoexist);
		अवरोध;
	हाल BTC_GET_U4_SUPPORTED_FEATURE:
		*u32_पंचांगp = halbtc_get_bt_coex_supported_feature(btcoexist);
		अवरोध;
	हाल BTC_GET_U4_BT_DEVICE_INFO:
		*u32_पंचांगp = halbtc_get_bt_device_info(btcoexist);
		अवरोध;
	हाल BTC_GET_U4_BT_FORBIDDEN_SLOT_VAL:
		*u32_पंचांगp = halbtc_get_bt_क्रमbidden_slot_val(btcoexist);
		अवरोध;
	हाल BTC_GET_U4_WIFI_IQK_TOTAL:
		*u32_पंचांगp =
			btcoexist->btc_phydm_query_phy_counter(btcoexist,
							       DM_INFO_IQK_ALL);
		अवरोध;
	हाल BTC_GET_U4_WIFI_IQK_OK:
		*u32_पंचांगp =
			btcoexist->btc_phydm_query_phy_counter(btcoexist,
							       DM_INFO_IQK_OK);
		अवरोध;
	हाल BTC_GET_U4_WIFI_IQK_FAIL:
		*u32_पंचांगp =
			btcoexist->btc_phydm_query_phy_counter(btcoexist,
							       DM_INFO_IQK_NG);
		अवरोध;
	हाल BTC_GET_U1_WIFI_DOT11_CHNL:
		*u8_पंचांगp = rtlphy->current_channel;
		अवरोध;
	हाल BTC_GET_U1_WIFI_CENTRAL_CHNL:
		*u8_पंचांगp = halbtc_get_wअगरi_central_chnl(btcoexist);
		अवरोध;
	हाल BTC_GET_U1_WIFI_HS_CHNL:
		*u8_पंचांगp = 0;
		ret = false;
		अवरोध;
	हाल BTC_GET_U1_AP_NUM:
		*u8_पंचांगp = rtlpriv->btcoexist.btc_info.ap_num;
		अवरोध;
	हाल BTC_GET_U1_ANT_TYPE:
		*u8_पंचांगp = (u8)BTC_ANT_TYPE_0;
		अवरोध;
	हाल BTC_GET_U1_IOT_PEER:
		*u8_पंचांगp = 0;
		अवरोध;

		/************* 1Ant **************/
	हाल BTC_GET_U1_LPS_MODE:
		*u8_पंचांगp = btcoexist->pwr_mode_val[0];
		अवरोध;

	शेष:
		ret = false;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool halbtc_set(व्योम *व्योम_btcoexist, u8 set_type, व्योम *in_buf)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)व्योम_btcoexist;
	bool *bool_पंचांगp = (bool *)in_buf;
	u8 *u8_पंचांगp = (u8 *)in_buf;
	u32 *u32_पंचांगp = (u32 *)in_buf;
	bool ret = true;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस false;

	चयन (set_type) अणु
	/* set some bool type variables. */
	हाल BTC_SET_BL_BT_DISABLE:
		btcoexist->bt_info.bt_disabled = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_BT_TRAFFIC_BUSY:
		btcoexist->bt_info.bt_busy = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_BT_LIMITED_DIG:
		btcoexist->bt_info.limited_dig = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_FORCE_TO_ROAM:
		btcoexist->bt_info.क्रमce_to_roam = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_TO_REJ_AP_AGG_PKT:
		btcoexist->bt_info.reject_agg_pkt = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_BT_CTRL_AGG_SIZE:
		btcoexist->bt_info.bt_ctrl_agg_buf_size = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_INC_SCAN_DEV_NUM:
		btcoexist->bt_info.increase_scan_dev_num = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_BT_TX_RX_MASK:
		btcoexist->bt_info.bt_tx_rx_mask = *bool_पंचांगp;
		अवरोध;
	हाल BTC_SET_BL_MIRACAST_PLUS_BT:
		btcoexist->bt_info.miracast_plus_bt = *bool_पंचांगp;
		अवरोध;
		/* set some u1Byte type variables. */
	हाल BTC_SET_U1_RSSI_ADJ_VAL_FOR_AGC_TABLE_ON:
		btcoexist->bt_info.rssi_adjust_क्रम_agc_table_on = *u8_पंचांगp;
		अवरोध;
	हाल BTC_SET_U1_AGG_BUF_SIZE:
		btcoexist->bt_info.agg_buf_size = *u8_पंचांगp;
		अवरोध;

	/* the following are some action which will be triggered */
	हाल BTC_SET_ACT_GET_BT_RSSI:
		ret = false;
		अवरोध;
	हाल BTC_SET_ACT_AGGREGATE_CTRL:
		halbtc_aggregation_check(btcoexist);
		अवरोध;

	/* 1Ant */
	हाल BTC_SET_U1_RSSI_ADJ_VAL_FOR_1ANT_COEX_TYPE:
		btcoexist->bt_info.rssi_adjust_क्रम_1ant_coex_type = *u8_पंचांगp;
		अवरोध;
	हाल BTC_SET_UI_SCAN_SIG_COMPENSATION:
		अवरोध;
	हाल BTC_SET_U1_LPS_VAL:
		btcoexist->bt_info.lps_val = *u8_पंचांगp;
		अवरोध;
	हाल BTC_SET_U1_RPWM_VAL:
		btcoexist->bt_info.rpwm_val = *u8_पंचांगp;
		अवरोध;
	/* the following are some action which will be triggered  */
	हाल BTC_SET_ACT_LEAVE_LPS:
		halbtc_leave_lps(btcoexist);
		अवरोध;
	हाल BTC_SET_ACT_ENTER_LPS:
		halbtc_enter_lps(btcoexist);
		अवरोध;
	हाल BTC_SET_ACT_NORMAL_LPS:
		halbtc_normal_lps(btcoexist);
		अवरोध;
	हाल BTC_SET_ACT_PRE_NORMAL_LPS:
		halbtc_pre_normal_lps(btcoexist);
		अवरोध;
	हाल BTC_SET_ACT_POST_NORMAL_LPS:
		halbtc_post_normal_lps(btcoexist);
		अवरोध;
	हाल BTC_SET_ACT_DISABLE_LOW_POWER:
		halbtc_disable_low_घातer(btcoexist, *bool_पंचांगp);
		अवरोध;
	हाल BTC_SET_ACT_UPDATE_RAMASK:
		btcoexist->bt_info.ra_mask = *u32_पंचांगp;
		अवरोध;
	हाल BTC_SET_ACT_SEND_MIMO_PS:
		अवरोध;
	हाल BTC_SET_ACT_CTRL_BT_INFO: /*रुको क्रम 8812/8821*/
		अवरोध;
	हाल BTC_SET_ACT_CTRL_BT_COEX:
		अवरोध;
	हाल BTC_SET_ACT_CTRL_8723B_ANT:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम halbtc_display_coex_statistics(काष्ठा btc_coexist *btcoexist,
					   काष्ठा seq_file *m)
अणु
पूर्ण

अटल व्योम halbtc_display_bt_link_info(काष्ठा btc_coexist *btcoexist,
					काष्ठा seq_file *m)
अणु
पूर्ण

अटल व्योम halbtc_display_wअगरi_status(काष्ठा btc_coexist *btcoexist,
				       काष्ठा seq_file *m)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	s32 wअगरi_rssi = 0, bt_hs_rssi = 0;
	bool scan = false, link = false, roam = false, wअगरi_busy = false;
	bool wअगरi_under_b_mode = false;
	bool wअगरi_under_5g = false;
	u32 wअगरi_bw = BTC_WIFI_BW_HT20;
	u32 wअगरi_traffic_dir = BTC_WIFI_TRAFFIC_TX;
	u32 wअगरi_freq = BTC_FREQ_2_4G;
	u32 wअगरi_link_status = 0x0;
	bool bt_hs_on = false, under_ips = false, under_lps = false;
	bool low_घातer = false, dc_mode = false;
	u8 wअगरi_chnl = 0, wअगरi_hs_chnl = 0;
	u8 ap_num = 0;

	wअगरi_link_status = halbtc_get_wअगरi_link_status(btcoexist);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d/ %d/ %d",
		   "STA/vWifi/HS/p2pGo/p2pGc",
		   ((wअगरi_link_status & WIFI_STA_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_AP_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_HS_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_P2P_GO_CONNECTED) ? 1 : 0),
		   ((wअगरi_link_status & WIFI_P2P_GC_CONNECTED) ? 1 : 0));

	btcoexist->btc_get(btcoexist, BTC_GET_BL_HS_OPERATION, &bt_hs_on);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_DOT11_CHNL, &wअगरi_chnl);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_WIFI_HS_CHNL, &wअगरi_hs_chnl);
	seq_म_लिखो(m, "\n %-35s = %d / %d(%d)",
		   "Dot11 channel / HsChnl(High Speed)",
		   wअगरi_chnl, wअगरi_hs_chnl, bt_hs_on);

	btcoexist->btc_get(btcoexist, BTC_GET_S4_WIFI_RSSI, &wअगरi_rssi);
	btcoexist->btc_get(btcoexist, BTC_GET_S4_HS_RSSI, &bt_hs_rssi);
	seq_म_लिखो(m, "\n %-35s = %d/ %d",
		   "Wifi rssi/ HS rssi",
		   wअगरi_rssi - 100, bt_hs_rssi - 100);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_SCAN, &scan);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_LINK, &link);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_ROAM, &roam);
	seq_म_लिखो(m, "\n %-35s = %d/ %d/ %d ",
		   "Wifi link/ roam/ scan",
		   link, roam, scan);

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_BW, &wअगरi_bw);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_BUSY, &wअगरi_busy);
	btcoexist->btc_get(btcoexist, BTC_GET_U4_WIFI_TRAFFIC_सूचीECTION,
			   &wअगरi_traffic_dir);
	btcoexist->btc_get(btcoexist, BTC_GET_U1_AP_NUM, &ap_num);
	wअगरi_freq = (wअगरi_under_5g ? BTC_FREQ_5G : BTC_FREQ_2_4G);
	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_B_MODE,
			   &wअगरi_under_b_mode);

	seq_म_लिखो(m, "\n %-35s = %s / %s/ %s/ AP=%d ",
		   "Wifi freq/ bw/ traffic",
		   gl_btc_wअगरi_freq_string[wअगरi_freq],
		   ((wअगरi_under_b_mode) ? "11b" :
		    gl_btc_wअगरi_bw_string[wअगरi_bw]),
		   ((!wअगरi_busy) ? "idle" : ((BTC_WIFI_TRAFFIC_TX ==
					      wअगरi_traffic_dir) ? "uplink" :
					     "downlink")),
		   ap_num);

	/* घातer status	 */
	dc_mode = true;	/*TODO*/
	under_ips = rtlpriv->psc.inactive_pwrstate == ERFOFF ? 1 : 0;
	under_lps = rtlpriv->psc.करोt11_psmode == EACTIVE ? 0 : 1;
	low_घातer = 0; /*TODO*/
	seq_म_लिखो(m, "\n %-35s = %s%s%s%s",
		   "Power Status",
		   (dc_mode ? "DC mode" : "AC mode"),
		   (under_ips ? ", IPS ON" : ""),
		   (under_lps ? ", LPS ON" : ""),
		   (low_घातer ? ", 32k" : ""));

	seq_म_लिखो(m,
		   "\n %-35s = %6ph (0x%x/0x%x)",
		   "Power mode cmd(lps/rpwm)",
		   btcoexist->pwr_mode_val,
		   btcoexist->bt_info.lps_val,
		   btcoexist->bt_info.rpwm_val);
पूर्ण

/************************************************************
 *		IO related function
 ************************************************************/
अटल u8 halbtc_पढ़ो_1byte(व्योम *bt_context, u32 reg_addr)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	वापस	rtl_पढ़ो_byte(rtlpriv, reg_addr);
पूर्ण

अटल u16 halbtc_पढ़ो_2byte(व्योम *bt_context, u32 reg_addr)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	वापस	rtl_पढ़ो_word(rtlpriv, reg_addr);
पूर्ण

अटल u32 halbtc_पढ़ो_4byte(व्योम *bt_context, u32 reg_addr)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	वापस	rtl_पढ़ो_dword(rtlpriv, reg_addr);
पूर्ण

अटल व्योम halbtc_ग_लिखो_1byte(व्योम *bt_context, u32 reg_addr, u32 data)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_ग_लिखो_byte(rtlpriv, reg_addr, data);
पूर्ण

अटल व्योम halbtc_biपंचांगask_ग_लिखो_1byte(व्योम *bt_context, u32 reg_addr,
				       u32 bit_mask, u8 data)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 original_value, bit_shअगरt = 0;
	u8 i;

	अगर (bit_mask != MASKDWORD) अणु/*अगर not "double word" ग_लिखो*/
		original_value = rtl_पढ़ो_byte(rtlpriv, reg_addr);
		क्रम (i = 0; i <= 7; i++) अणु
			अगर ((bit_mask>>i) & 0x1)
				अवरोध;
		पूर्ण
		bit_shअगरt = i;
		data = (original_value & (~bit_mask)) |
			((data << bit_shअगरt) & bit_mask);
	पूर्ण
	rtl_ग_लिखो_byte(rtlpriv, reg_addr, data);
पूर्ण

अटल व्योम halbtc_ग_लिखो_2byte(व्योम *bt_context, u32 reg_addr, u16 data)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_ग_लिखो_word(rtlpriv, reg_addr, data);
पूर्ण

अटल व्योम halbtc_ग_लिखो_4byte(व्योम *bt_context, u32 reg_addr, u32 data)
अणु
	काष्ठा btc_coexist *btcoexist =
		(काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_ग_लिखो_dword(rtlpriv, reg_addr, data);
पूर्ण

अटल व्योम halbtc_ग_लिखो_local_reg_1byte(व्योम *btc_context, u32 reg_addr,
					 u8 data)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_SDIO)
		;
	अन्यथा अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_PCI)
		rtl_ग_लिखो_byte(rtlpriv, reg_addr, data);
	अन्यथा अगर (btcoexist->chip_पूर्णांकerface == BTC_INTF_USB)
		rtl_ग_लिखो_byte(rtlpriv, reg_addr, data);
पूर्ण

अटल व्योम halbtc_set_bbreg(व्योम *bt_context, u32 reg_addr, u32 bit_mask,
			     u32 data)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_set_bbreg(rtlpriv->mac80211.hw, reg_addr, bit_mask, data);
पूर्ण

अटल u32 halbtc_get_bbreg(व्योम *bt_context, u32 reg_addr, u32 bit_mask)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	वापस rtl_get_bbreg(rtlpriv->mac80211.hw, reg_addr, bit_mask);
पूर्ण

अटल व्योम halbtc_set_rfreg(व्योम *bt_context, u8 rf_path, u32 reg_addr,
			     u32 bit_mask, u32 data)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtl_set_rfreg(rtlpriv->mac80211.hw, rf_path, reg_addr, bit_mask, data);
पूर्ण

अटल u32 halbtc_get_rfreg(व्योम *bt_context, u8 rf_path, u32 reg_addr,
			    u32 bit_mask)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	वापस rtl_get_rfreg(rtlpriv->mac80211.hw, rf_path, reg_addr, bit_mask);
पूर्ण

अटल व्योम halbtc_fill_h2c_cmd(व्योम *bt_context, u8 element_id,
				u32 cmd_len, u8 *cmd_buf)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	rtlpriv->cfg->ops->fill_h2c_cmd(rtlpriv->mac80211.hw, element_id,
					cmd_len, cmd_buf);
पूर्ण

व्योम halbtc_send_wअगरi_port_id_cmd(व्योम *bt_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	u8 cmd_buf[1] = अणु0पूर्ण;	/* port id [2:0] = 0 */

	rtlpriv->cfg->ops->fill_h2c_cmd(rtlpriv->mac80211.hw, H2C_BT_PORT_ID,
					1, cmd_buf);
पूर्ण

व्योम halbtc_set_शेष_port_id_cmd(व्योम *bt_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा ieee80211_hw *hw = rtlpriv->mac80211.hw;

	अगर (!rtlpriv->cfg->ops->set_शेष_port_id_cmd)
		वापस;

	rtlpriv->cfg->ops->set_शेष_port_id_cmd(hw);
पूर्ण

अटल
व्योम halbtc_set_bt_reg(व्योम *btc_context, u8 reg_type, u32 offset, u32 set_val)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer1[4] = अणु0पूर्ण;
	u8 cmd_buffer2[4] = अणु0पूर्ण;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	*((__le16 *)&cmd_buffer1[2]) = cpu_to_le16((u16)set_val);
	अगर (!halbtc_send_bt_mp_operation(btcoexist, BT_OP_WRITE_REG_VALUE,
					 cmd_buffer1, 4, 200))
		वापस;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	cmd_buffer2[2] = reg_type;
	*((u8 *)&cmd_buffer2[3]) = (u8)offset;
	halbtc_send_bt_mp_operation(btcoexist, BT_OP_WRITE_REG_ADDR,
				    cmd_buffer2, 4, 200);
पूर्ण

अटल व्योम halbtc_display_dbg_msg(व्योम *bt_context, u8 disp_type,
				   काष्ठा seq_file *m)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)bt_context;

	चयन (disp_type) अणु
	हाल BTC_DBG_DISP_COEX_STATISTICS:
		halbtc_display_coex_statistics(btcoexist, m);
		अवरोध;
	हाल BTC_DBG_DISP_BT_LINK_INFO:
		halbtc_display_bt_link_info(btcoexist, m);
		अवरोध;
	हाल BTC_DBG_DISP_WIFI_STATUS:
		halbtc_display_wअगरi_status(btcoexist, m);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 halbtc_get_bt_reg(व्योम *btc_context, u8 reg_type, u32 offset)
अणु
	वापस 0;
पूर्ण

अटल bool halbtc_under_ips(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtlpriv);
	क्रमागत rf_pwrstate rtstate;

	अगर (ppsc->inactiveps) अणु
		rtstate = ppsc->rfpwr_state;

		अगर (rtstate != ERFON &&
		    ppsc->rfoff_reason == RF_CHANGE_BY_IPS) अणु
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल
u32 halbtc_get_phydm_version(व्योम *btc_context)
अणु
	वापस 0;
पूर्ण

अटल
व्योम halbtc_phydm_modअगरy_ra_pcr_threshold(व्योम *btc_context,
					  u8 ra_offset_direction,
					  u8 ra_threshold_offset)
अणु
पूर्ण

अटल
u32 halbtc_phydm_query_phy_counter(व्योम *btc_context, क्रमागत dm_info_query dm_id)
अणु
	वापस 0;
पूर्ण

अटल u8 halbtc_get_ant_det_val_from_bt(व्योम *btc_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[4] = अणु0पूर्ण;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_BT_ANT_DET_VAL,
				    cmd_buffer, 4, 200);

	/* need रुको completion to वापस correct value */

	वापस btcoexist->bt_info.bt_ant_det_val;
पूर्ण

अटल u8 halbtc_get_ble_scan_type_from_bt(व्योम *btc_context)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[4] = अणु0पूर्ण;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_BT_BLE_SCAN_TYPE,
				    cmd_buffer, 4, 200);

	/* need रुको completion to वापस correct value */

	वापस btcoexist->bt_info.bt_ble_scan_type;
पूर्ण

अटल u32 halbtc_get_ble_scan_para_from_bt(व्योम *btc_context, u8 scan_type)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[4] = अणु0पूर्ण;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_BT_BLE_SCAN_PARA,
				    cmd_buffer, 4, 200);

	/* need रुको completion to वापस correct value */

	वापस btcoexist->bt_info.bt_ble_scan_para;
पूर्ण

अटल bool halbtc_get_bt_afh_map_from_bt(व्योम *btc_context, u8 map_type,
					  u8 *afh_map)
अणु
	काष्ठा btc_coexist *btcoexist = (काष्ठा btc_coexist *)btc_context;
	u8 cmd_buffer[2] = अणु0पूर्ण;
	bool ret;
	u32 *afh_map_l = (u32 *)afh_map;
	u32 *afh_map_m = (u32 *)(afh_map + 4);
	u16 *afh_map_h = (u16 *)(afh_map + 8);

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	ret = halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_AFH_MAP_L,
					  cmd_buffer, 2, 200);
	अगर (!ret)
		जाओ निकास;

	*afh_map_l = btcoexist->bt_info.afh_map_l;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	ret = halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_AFH_MAP_M,
					  cmd_buffer, 2, 200);
	अगर (!ret)
		जाओ निकास;

	*afh_map_m = btcoexist->bt_info.afh_map_m;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	ret = halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_AFH_MAP_H,
					  cmd_buffer, 2, 200);
	अगर (!ret)
		जाओ निकास;

	*afh_map_h = btcoexist->bt_info.afh_map_h;

निकास:
	वापस ret;
पूर्ण

/*****************************************************************
 *         Extern functions called by other module
 *****************************************************************/
bool exhalbtc_initlize_variables(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस false;

	halbtc_dbg_init();

	btcoexist->btc_पढ़ो_1byte = halbtc_पढ़ो_1byte;
	btcoexist->btc_ग_लिखो_1byte = halbtc_ग_लिखो_1byte;
	btcoexist->btc_ग_लिखो_1byte_biपंचांगask = halbtc_biपंचांगask_ग_लिखो_1byte;
	btcoexist->btc_पढ़ो_2byte = halbtc_पढ़ो_2byte;
	btcoexist->btc_ग_लिखो_2byte = halbtc_ग_लिखो_2byte;
	btcoexist->btc_पढ़ो_4byte = halbtc_पढ़ो_4byte;
	btcoexist->btc_ग_लिखो_4byte = halbtc_ग_लिखो_4byte;
	btcoexist->btc_ग_लिखो_local_reg_1byte = halbtc_ग_लिखो_local_reg_1byte;

	btcoexist->btc_set_bb_reg = halbtc_set_bbreg;
	btcoexist->btc_get_bb_reg = halbtc_get_bbreg;

	btcoexist->btc_set_rf_reg = halbtc_set_rfreg;
	btcoexist->btc_get_rf_reg = halbtc_get_rfreg;

	btcoexist->btc_fill_h2c = halbtc_fill_h2c_cmd;
	btcoexist->btc_disp_dbg_msg = halbtc_display_dbg_msg;

	btcoexist->btc_get = halbtc_get;
	btcoexist->btc_set = halbtc_set;
	btcoexist->btc_set_bt_reg = halbtc_set_bt_reg;
	btcoexist->btc_get_bt_reg = halbtc_get_bt_reg;

	btcoexist->bt_info.bt_ctrl_buf_size = false;
	btcoexist->bt_info.agg_buf_size = 5;

	btcoexist->bt_info.increase_scan_dev_num = false;

	btcoexist->btc_get_bt_coex_supported_feature =
					halbtc_get_bt_coex_supported_feature;
	btcoexist->btc_get_bt_coex_supported_version =
					halbtc_get_bt_coex_supported_version;
	btcoexist->btc_get_bt_phydm_version = halbtc_get_phydm_version;
	btcoexist->btc_phydm_modअगरy_ra_pcr_threshold =
					halbtc_phydm_modअगरy_ra_pcr_threshold;
	btcoexist->btc_phydm_query_phy_counter = halbtc_phydm_query_phy_counter;
	btcoexist->btc_get_ant_det_val_from_bt = halbtc_get_ant_det_val_from_bt;
	btcoexist->btc_get_ble_scan_type_from_bt =
					halbtc_get_ble_scan_type_from_bt;
	btcoexist->btc_get_ble_scan_para_from_bt =
					halbtc_get_ble_scan_para_from_bt;
	btcoexist->btc_get_bt_afh_map_from_bt =
					halbtc_get_bt_afh_map_from_bt;

	init_completion(&btcoexist->bt_mp_comp);

	वापस true;
पूर्ण

bool exhalbtc_initlize_variables_wअगरi_only(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा wअगरi_only_cfg *wअगरionly_cfg = rtl_btc_wअगरi_only(rtlpriv);
	काष्ठा wअगरi_only_haldata *wअगरionly_haldata;

	अगर (!wअगरionly_cfg)
		वापस false;

	wअगरionly_cfg->adapter = rtlpriv;

	चयन (rtlpriv->rtlhal.पूर्णांकerface) अणु
	हाल INTF_PCI:
		wअगरionly_cfg->chip_पूर्णांकerface = WIFIONLY_INTF_PCI;
		अवरोध;
	हाल INTF_USB:
		wअगरionly_cfg->chip_पूर्णांकerface = WIFIONLY_INTF_USB;
		अवरोध;
	शेष:
		wअगरionly_cfg->chip_पूर्णांकerface = WIFIONLY_INTF_UNKNOWN;
		अवरोध;
	पूर्ण

	wअगरionly_haldata = &wअगरionly_cfg->haldata_info;

	wअगरionly_haldata->customer_id = CUSTOMER_NORMAL;
	wअगरionly_haldata->efuse_pg_antnum = rtl_get_hwpg_ant_num(rtlpriv);
	wअगरionly_haldata->efuse_pg_antpath =
					rtl_get_hwpg_single_ant_path(rtlpriv);
	wअगरionly_haldata->rfe_type = rtl_get_hwpg_rfe_type(rtlpriv);
	wअगरionly_haldata->ant_भाग_cfg = 0;

	वापस true;
पूर्ण

bool exhalbtc_bind_bt_coex_withadapter(व्योम *adapter)
अणु
	काष्ठा rtl_priv *rtlpriv = adapter;
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 ant_num, chip_type, single_ant_path;

	अगर (!btcoexist)
		वापस false;

	अगर (btcoexist->binded)
		वापस false;

	चयन (rtlpriv->rtlhal.पूर्णांकerface) अणु
	हाल INTF_PCI:
		btcoexist->chip_पूर्णांकerface = BTC_INTF_PCI;
		अवरोध;
	हाल INTF_USB:
		btcoexist->chip_पूर्णांकerface = BTC_INTF_USB;
		अवरोध;
	शेष:
		btcoexist->chip_पूर्णांकerface = BTC_INTF_UNKNOWN;
		अवरोध;
	पूर्ण

	btcoexist->binded = true;
	btcoexist->statistics.cnt_bind++;

	btcoexist->adapter = adapter;

	btcoexist->stack_info.profile_notअगरied = false;

	btcoexist->bt_info.bt_ctrl_agg_buf_size = false;
	btcoexist->bt_info.agg_buf_size = 5;

	btcoexist->bt_info.increase_scan_dev_num = false;
	btcoexist->bt_info.miracast_plus_bt = false;

	chip_type = rtl_get_hwpg_bt_type(rtlpriv);
	exhalbtc_set_chip_type(btcoexist, chip_type);
	ant_num = rtl_get_hwpg_ant_num(rtlpriv);
	exhalbtc_set_ant_num(rtlpriv, BT_COEX_ANT_TYPE_PG, ant_num);

	/* set शेष antenna position to मुख्य  port */
	btcoexist->board_info.btdm_ant_pos = BTC_ANTENNA_AT_MAIN_PORT;

	single_ant_path = rtl_get_hwpg_single_ant_path(rtlpriv);
	exhalbtc_set_single_ant_path(btcoexist, single_ant_path);

	अगर (rtl_get_hwpg_package_type(rtlpriv) == 0)
		btcoexist->board_info.tfbga_package = false;
	अन्यथा अगर (rtl_get_hwpg_package_type(rtlpriv) == 1)
		btcoexist->board_info.tfbga_package = false;
	अन्यथा
		btcoexist->board_info.tfbga_package = true;

	अगर (btcoexist->board_info.tfbga_package)
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Package Type = TFBGA\n");
	अन्यथा
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
			"[BTCoex], Package Type = Non-TFBGA\n");

	btcoexist->board_info.rfe_type = rtl_get_hwpg_rfe_type(rtlpriv);
	btcoexist->board_info.ant_भाग_cfg = 0;

	वापस true;
पूर्ण

व्योम exhalbtc_घातer_on_setting(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	btcoexist->statistics.cnt_घातer_on++;

	अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_घातer_on_setting(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_घातer_on_setting(btcoexist);
	पूर्ण
पूर्ण

व्योम exhalbtc_pre_load_firmware(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	btcoexist->statistics.cnt_pre_load_firmware++;

	अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_pre_load_firmware(btcoexist);
	पूर्ण
पूर्ण

व्योम exhalbtc_init_hw_config(काष्ठा btc_coexist *btcoexist, bool wअगरi_only)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	btcoexist->statistics.cnt_init_hw_config++;

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_init_hwconfig(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_init_hwconfig(btcoexist, wअगरi_only);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_init_hwconfig(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_init_hwconfig(btcoexist, wअगरi_only);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723A(btcoexist->adapter)) अणु
		/* 8723A has no this function */
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_init_hwconfig(btcoexist);
	पूर्ण
पूर्ण

व्योम exhalbtc_init_hw_config_wअगरi_only(काष्ठा wअगरi_only_cfg *wअगरionly_cfg)
अणु
पूर्ण

व्योम exhalbtc_init_coex_dm(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	btcoexist->statistics.cnt_init_coex_dm++;

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_init_coex_dm(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_init_coex_dm(btcoexist);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_init_coex_dm(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_init_coex_dm(btcoexist);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_init_coex_dm(btcoexist);
	पूर्ण

	btcoexist->initialized = true;
पूर्ण

व्योम exhalbtc_ips_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	u8 ips_type;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_ips_notअगरy++;
	अगर (btcoexist->manual_control)
		वापस;

	अगर (ERFOFF == type)
		ips_type = BTC_IPS_ENTER;
	अन्यथा
		ips_type = BTC_IPS_LEAVE;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_ips_notअगरy(btcoexist, ips_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_ips_notअगरy(btcoexist, ips_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_ips_notअगरy(btcoexist, ips_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_ips_notअगरy(btcoexist, ips_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_ips_notअगरy(btcoexist, ips_type);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_lps_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	u8 lps_type;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_lps_notअगरy++;
	अगर (btcoexist->manual_control)
		वापस;

	अगर (EACTIVE == type)
		lps_type = BTC_LPS_DISABLE;
	अन्यथा
		lps_type = BTC_LPS_ENABLE;

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_lps_notअगरy(btcoexist, lps_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_lps_notअगरy(btcoexist, lps_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_lps_notअगरy(btcoexist, lps_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_lps_notअगरy(btcoexist, lps_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_lps_notअगरy(btcoexist, lps_type);
	पूर्ण
पूर्ण

व्योम exhalbtc_scan_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	u8 scan_type;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_scan_notअगरy++;
	अगर (btcoexist->manual_control)
		वापस;

	अगर (type)
		scan_type = BTC_SCAN_START;
	अन्यथा
		scan_type = BTC_SCAN_FINISH;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_scan_notअगरy(btcoexist, scan_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_scan_notअगरy(btcoexist, scan_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_scan_notअगरy(btcoexist, scan_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_scan_notअगरy(btcoexist, scan_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_scan_notअगरy(btcoexist, scan_type);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_scan_notअगरy_wअगरi_only(काष्ठा wअगरi_only_cfg *wअगरionly_cfg,
				    u8 is_5g)
अणु
पूर्ण

व्योम exhalbtc_connect_notअगरy(काष्ठा btc_coexist *btcoexist, u8 action)
अणु
	u8 asso_type;
	bool wअगरi_under_5g;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_connect_notअगरy++;
	अगर (btcoexist->manual_control)
		वापस;

	btcoexist->btc_get(btcoexist, BTC_GET_BL_WIFI_UNDER_5G, &wअगरi_under_5g);

	अगर (action)
		asso_type = BTC_ASSOCIATE_START;
	अन्यथा
		asso_type = BTC_ASSOCIATE_FINISH;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_connect_notअगरy(btcoexist, asso_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_connect_notअगरy(btcoexist, asso_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_connect_notअगरy(btcoexist, asso_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_connect_notअगरy(btcoexist, asso_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_connect_notअगरy(btcoexist, asso_type);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_mediastatus_notअगरy(काष्ठा btc_coexist *btcoexist,
				 क्रमागत rt_media_status media_status)
अणु
	u8 status;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_media_status_notअगरy++;
	अगर (btcoexist->manual_control)
		वापस;

	अगर (RT_MEDIA_CONNECT == media_status)
		status = BTC_MEDIA_CONNECT;
	अन्यथा
		status = BTC_MEDIA_DISCONNECT;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_media_status_notअगरy(btcoexist, status);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_media_status_notअगरy(btcoexist, status);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_media_status_notअगरy(btcoexist, status);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_media_status_notअगरy(btcoexist, status);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_media_status_notअगरy(btcoexist, status);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_special_packet_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pkt_type)
अणु
	u8 packet_type;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_special_packet_notअगरy++;
	अगर (btcoexist->manual_control)
		वापस;

	अगर (pkt_type == PACKET_DHCP) अणु
		packet_type = BTC_PACKET_DHCP;
	पूर्ण अन्यथा अगर (pkt_type == PACKET_EAPOL) अणु
		packet_type = BTC_PACKET_EAPOL;
	पूर्ण अन्यथा अगर (pkt_type == PACKET_ARP) अणु
		packet_type = BTC_PACKET_ARP;
	पूर्ण अन्यथा अणु
		packet_type = BTC_PACKET_UNKNOWN;
		वापस;
	पूर्ण

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_special_packet_notअगरy(btcoexist,
							      packet_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_special_packet_notअगरy(btcoexist,
							      packet_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_special_packet_notअगरy(btcoexist,
							      packet_type);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_special_packet_notअगरy(btcoexist,
							      packet_type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_special_packet_notअगरy(btcoexist,
							      packet_type);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_bt_info_notअगरy(काष्ठा btc_coexist *btcoexist,
			     u8 *पंचांगp_buf, u8 length)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_bt_info_notअगरy++;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_bt_info_notअगरy(btcoexist, पंचांगp_buf,
						       length);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_bt_info_notअगरy(btcoexist, पंचांगp_buf,
						       length);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_bt_info_notअगरy(btcoexist, पंचांगp_buf,
						       length);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_bt_info_notअगरy(btcoexist, पंचांगp_buf,
						       length);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_bt_info_notअगरy(btcoexist, पंचांगp_buf,
						       length);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_rf_status_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_rf_status_notअगरy(btcoexist, type);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
	पूर्ण
पूर्ण

व्योम exhalbtc_halt_notअगरy(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_halt_notअगरy(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_halt_notअगरy(btcoexist);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_halt_notअगरy(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_halt_notअगरy(btcoexist);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_halt_notअगरy(btcoexist);
	पूर्ण

	btcoexist->binded = false;
पूर्ण

व्योम exhalbtc_pnp_notअगरy(काष्ठा btc_coexist *btcoexist, u8 pnp_state)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	/* currently only 1ant we have to करो the notअगरication,
	 * once pnp is notअगरied to sleep state, we have to leave LPS that
	 * we can sleep normally.
	 */

	अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_pnp_notअगरy(btcoexist, pnp_state);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_pnp_notअगरy(btcoexist, pnp_state);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_pnp_notअगरy(btcoexist, pnp_state);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_pnp_notअगरy(btcoexist, pnp_state);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
	पूर्ण
पूर्ण

व्योम exhalbtc_coex_dm_चयन(काष्ठा btc_coexist *btcoexist)
अणु
	काष्ठा rtl_priv *rtlpriv = btcoexist->adapter;

	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_coex_dm_चयन++;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 1) अणु
			btcoexist->stop_coex_dm = true;
			ex_btc8723b1ant_coex_dm_reset(btcoexist);
			exhalbtc_set_ant_num(rtlpriv,
					     BT_COEX_ANT_TYPE_DETECTED, 2);
			ex_btc8723b2ant_init_hwconfig(btcoexist);
			ex_btc8723b2ant_init_coex_dm(btcoexist);
			btcoexist->stop_coex_dm = false;
		पूर्ण
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_periodical(काष्ठा btc_coexist *btcoexist)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_periodical++;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_periodical(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			अगर (!halbtc_under_ips(btcoexist))
				ex_btc8821a1ant_periodical(btcoexist);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_periodical(btcoexist);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_periodical(btcoexist);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_periodical(btcoexist);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_dbg_control(काष्ठा btc_coexist *btcoexist,
			  u8 code, u8 len, u8 *data)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
	btcoexist->statistics.cnt_dbg_ctrl++;

	halbtc_leave_low_घातer(btcoexist);

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_antenna_detection(काष्ठा btc_coexist *btcoexist, u32 cent_freq,
				u32 offset, u32 span, u32 seconds)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;
पूर्ण

व्योम exhalbtc_stack_update_profile_info(व्योम)
अणु
पूर्ण

व्योम exhalbtc_update_min_bt_rssi(काष्ठा btc_coexist *btcoexist, s8 bt_rssi)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	btcoexist->stack_info.min_bt_rssi = bt_rssi;
पूर्ण

व्योम exhalbtc_set_hci_version(काष्ठा btc_coexist *btcoexist, u16 hci_version)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	btcoexist->stack_info.hci_version = hci_version;
पूर्ण

व्योम exhalbtc_set_bt_patch_version(काष्ठा btc_coexist *btcoexist,
				   u16 bt_hci_version, u16 bt_patch_version)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	btcoexist->bt_info.bt_real_fw_ver = bt_patch_version;
	btcoexist->bt_info.bt_hci_ver = bt_hci_version;
पूर्ण

व्योम exhalbtc_set_chip_type(काष्ठा btc_coexist *btcoexist, u8 chip_type)
अणु
	चयन (chip_type) अणु
	शेष:
	हाल BT_2WIRE:
	हाल BT_ISSC_3WIRE:
	हाल BT_ACCEL:
	हाल BT_RTL8756:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_UNDEF;
		अवरोध;
	हाल BT_CSR_BC4:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_CSR_BC4;
		अवरोध;
	हाल BT_CSR_BC8:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_CSR_BC8;
		अवरोध;
	हाल BT_RTL8723A:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_RTL8723A;
		अवरोध;
	हाल BT_RTL8821A:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_RTL8821;
		अवरोध;
	हाल BT_RTL8723B:
		btcoexist->board_info.bt_chip_type = BTC_CHIP_RTL8723B;
		अवरोध;
	पूर्ण
पूर्ण

व्योम exhalbtc_set_ant_num(काष्ठा rtl_priv *rtlpriv, u8 type, u8 ant_num)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	अगर (BT_COEX_ANT_TYPE_PG == type) अणु
		btcoexist->board_info.pg_ant_num = ant_num;
		btcoexist->board_info.btdm_ant_num = ant_num;
	पूर्ण अन्यथा अगर (BT_COEX_ANT_TYPE_ANTDIV == type) अणु
		btcoexist->board_info.btdm_ant_num = ant_num;
	पूर्ण अन्यथा अगर (type == BT_COEX_ANT_TYPE_DETECTED) अणु
		btcoexist->board_info.btdm_ant_num = ant_num;
		अगर (rtlpriv->cfg->mod_params->ant_sel == 1)
			btcoexist->board_info.btdm_ant_pos =
				BTC_ANTENNA_AT_AUX_PORT;
		अन्यथा
			btcoexist->board_info.btdm_ant_pos =
				BTC_ANTENNA_AT_MAIN_PORT;
	पूर्ण
पूर्ण

/* Currently used by 8723b only, S0 or S1 */
व्योम exhalbtc_set_single_ant_path(काष्ठा btc_coexist *btcoexist,
				  u8 single_ant_path)
अणु
	btcoexist->board_info.single_ant_path = single_ant_path;
पूर्ण

व्योम exhalbtc_display_bt_coex_info(काष्ठा btc_coexist *btcoexist,
				   काष्ठा seq_file *m)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	halbtc_leave_low_घातer(btcoexist);

	अगर (IS_HARDWARE_TYPE_8821(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8821a2ant_display_coex_info(btcoexist, m);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8821a1ant_display_coex_info(btcoexist, m);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8723B(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8723b2ant_display_coex_info(btcoexist, m);
		अन्यथा अगर (btcoexist->board_info.btdm_ant_num == 1)
			ex_btc8723b1ant_display_coex_info(btcoexist, m);
	पूर्ण अन्यथा अगर (IS_HARDWARE_TYPE_8192E(btcoexist->adapter)) अणु
		अगर (btcoexist->board_info.btdm_ant_num == 2)
			ex_btc8192e2ant_display_coex_info(btcoexist, m);
	पूर्ण

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_चयन_band_notअगरy(काष्ठा btc_coexist *btcoexist, u8 type)
अणु
	अगर (!halbtc_is_bt_coexist_available(btcoexist))
		वापस;

	अगर (btcoexist->manual_control)
		वापस;

	halbtc_leave_low_घातer(btcoexist);

	halbtc_normal_low_घातer(btcoexist);
पूर्ण

व्योम exhalbtc_चयन_band_notअगरy_wअगरi_only(काष्ठा wअगरi_only_cfg *wअगरionly_cfg,
					   u8 is_5g)
अणु
पूर्ण
