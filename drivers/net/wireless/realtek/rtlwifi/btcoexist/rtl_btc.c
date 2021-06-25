<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2013  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/module.h>

#समावेश "rtl_btc.h"
#समावेश "halbt_precomp.h"

अटल काष्ठा rtl_btc_ops rtl_btc_operation = अणु
	.btc_init_variables = rtl_btc_init_variables,
	.btc_init_variables_wअगरi_only = rtl_btc_init_variables_wअगरi_only,
	.btc_deinit_variables = rtl_btc_deinit_variables,
	.btc_init_hal_vars = rtl_btc_init_hal_vars,
	.btc_घातer_on_setting = rtl_btc_घातer_on_setting,
	.btc_init_hw_config = rtl_btc_init_hw_config,
	.btc_init_hw_config_wअगरi_only = rtl_btc_init_hw_config_wअगरi_only,
	.btc_ips_notअगरy = rtl_btc_ips_notअगरy,
	.btc_lps_notअगरy = rtl_btc_lps_notअगरy,
	.btc_scan_notअगरy = rtl_btc_scan_notअगरy,
	.btc_scan_notअगरy_wअगरi_only = rtl_btc_scan_notअगरy_wअगरi_only,
	.btc_connect_notअगरy = rtl_btc_connect_notअगरy,
	.btc_mediastatus_notअगरy = rtl_btc_mediastatus_notअगरy,
	.btc_periodical = rtl_btc_periodical,
	.btc_halt_notअगरy = rtl_btc_halt_notअगरy,
	.btc_btinfo_notअगरy = rtl_btc_btinfo_notअगरy,
	.btc_bपंचांगpinfo_notअगरy = rtl_btc_bपंचांगpinfo_notअगरy,
	.btc_is_limited_dig = rtl_btc_is_limited_dig,
	.btc_is_disable_edca_turbo = rtl_btc_is_disable_edca_turbo,
	.btc_is_bt_disabled = rtl_btc_is_bt_disabled,
	.btc_special_packet_notअगरy = rtl_btc_special_packet_notअगरy,
	.btc_चयन_band_notअगरy = rtl_btc_चयन_band_notअगरy,
	.btc_चयन_band_notअगरy_wअगरi_only = rtl_btc_चयन_band_notअगरy_wअगरionly,
	.btc_record_pwr_mode = rtl_btc_record_pwr_mode,
	.btc_get_lps_val = rtl_btc_get_lps_val,
	.btc_get_rpwm_val = rtl_btc_get_rpwm_val,
	.btc_is_bt_ctrl_lps = rtl_btc_is_bt_ctrl_lps,
	.btc_is_bt_lps_on = rtl_btc_is_bt_lps_on,
	.btc_get_ampdu_cfg = rtl_btc_get_ampdu_cfg,
	.btc_display_bt_coex_info = rtl_btc_display_bt_coex_info,
पूर्ण;

व्योम rtl_btc_display_bt_coex_info(काष्ठा rtl_priv *rtlpriv, काष्ठा seq_file *m)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist) अणु
		seq_माला_दो(m, "btc_coexist context is NULL!\n");
		वापस;
	पूर्ण

	exhalbtc_display_bt_coex_info(btcoexist, m);
पूर्ण

व्योम rtl_btc_record_pwr_mode(काष्ठा rtl_priv *rtlpriv, u8 *buf, u8 len)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 safe_len;

	अगर (!btcoexist)
		वापस;

	safe_len = माप(btcoexist->pwr_mode_val);

	अगर (safe_len > len)
		safe_len = len;

	स_नकल(btcoexist->pwr_mode_val, buf, safe_len);
पूर्ण

u8 rtl_btc_get_lps_val(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस 0;

	वापस btcoexist->bt_info.lps_val;
पूर्ण

u8 rtl_btc_get_rpwm_val(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस 0;

	वापस btcoexist->bt_info.rpwm_val;
पूर्ण

bool rtl_btc_is_bt_ctrl_lps(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस false;

	वापस btcoexist->bt_info.bt_ctrl_lps;
पूर्ण

bool rtl_btc_is_bt_lps_on(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस false;

	वापस btcoexist->bt_info.bt_lps_on;
पूर्ण

व्योम rtl_btc_get_ampdu_cfg(काष्ठा rtl_priv *rtlpriv, u8 *reject_agg,
			   u8 *ctrl_agg_size, u8 *agg_size)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist) अणु
		*reject_agg = false;
		*ctrl_agg_size = false;
		वापस;
	पूर्ण

	अगर (reject_agg)
		*reject_agg = btcoexist->bt_info.reject_agg_pkt;
	अगर (ctrl_agg_size)
		*ctrl_agg_size = btcoexist->bt_info.bt_ctrl_agg_buf_size;
	अगर (agg_size)
		*agg_size = btcoexist->bt_info.agg_buf_size;
पूर्ण

अटल व्योम rtl_btc_alloc_variable(काष्ठा rtl_priv *rtlpriv, bool wअगरi_only)
अणु
	अगर (wअगरi_only)
		rtlpriv->btcoexist.wअगरi_only_context =
			kzalloc(माप(काष्ठा wअगरi_only_cfg), GFP_KERNEL);
	अन्यथा
		rtlpriv->btcoexist.btc_context =
			kzalloc(माप(काष्ठा btc_coexist), GFP_KERNEL);
पूर्ण

अटल व्योम rtl_btc_मुक्त_variable(काष्ठा rtl_priv *rtlpriv)
अणु
	kमुक्त(rtlpriv->btcoexist.btc_context);
	rtlpriv->btcoexist.btc_context = शून्य;

	kमुक्त(rtlpriv->btcoexist.wअगरi_only_context);
	rtlpriv->btcoexist.wअगरi_only_context = शून्य;
पूर्ण

व्योम rtl_btc_init_variables(काष्ठा rtl_priv *rtlpriv)
अणु
	rtl_btc_alloc_variable(rtlpriv, false);

	exhalbtc_initlize_variables(rtlpriv);
	exhalbtc_bind_bt_coex_withadapter(rtlpriv);
पूर्ण

व्योम rtl_btc_init_variables_wअगरi_only(काष्ठा rtl_priv *rtlpriv)
अणु
	rtl_btc_alloc_variable(rtlpriv, true);

	exhalbtc_initlize_variables_wअगरi_only(rtlpriv);
पूर्ण

व्योम rtl_btc_deinit_variables(काष्ठा rtl_priv *rtlpriv)
अणु
	rtl_btc_मुक्त_variable(rtlpriv);
पूर्ण

व्योम rtl_btc_init_hal_vars(काष्ठा rtl_priv *rtlpriv)
अणु
	/* move ant_num, bt_type and single_ant_path to
	 * exhalbtc_bind_bt_coex_withadapter()
	 */
पूर्ण

व्योम rtl_btc_घातer_on_setting(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_घातer_on_setting(btcoexist);
पूर्ण

व्योम rtl_btc_init_hw_config(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	u8 bt_exist;

	bt_exist = rtl_get_hwpg_bt_exist(rtlpriv);
	rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
		"%s, bt_exist is %d\n", __func__, bt_exist);

	अगर (!btcoexist)
		वापस;

	exhalbtc_init_hw_config(btcoexist, !bt_exist);
	exhalbtc_init_coex_dm(btcoexist);
पूर्ण

व्योम rtl_btc_init_hw_config_wअगरi_only(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा wअगरi_only_cfg *wअगरionly_cfg = rtl_btc_wअगरi_only(rtlpriv);

	अगर (!wअगरionly_cfg)
		वापस;

	exhalbtc_init_hw_config_wअगरi_only(wअगरionly_cfg);
पूर्ण

व्योम rtl_btc_ips_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 type)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_ips_notअगरy(btcoexist, type);

	अगर (type == ERFON) अणु
		/* In some situation, it करोesn't scan after leaving IPS, and
		 * this will cause btcoex in wrong state.
		 */
		exhalbtc_scan_notअगरy(btcoexist, 1);
		exhalbtc_scan_notअगरy(btcoexist, 0);
	पूर्ण
पूर्ण

व्योम rtl_btc_lps_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 type)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_lps_notअगरy(btcoexist, type);
पूर्ण

व्योम rtl_btc_scan_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 scantype)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_scan_notअगरy(btcoexist, scantype);
पूर्ण

व्योम rtl_btc_scan_notअगरy_wअगरi_only(काष्ठा rtl_priv *rtlpriv, u8 scantype)
अणु
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा wअगरi_only_cfg *wअगरionly_cfg = rtl_btc_wअगरi_only(rtlpriv);
	u8 is_5g = (rtlhal->current_bandtype == BAND_ON_5G);

	अगर (!wअगरionly_cfg)
		वापस;

	exhalbtc_scan_notअगरy_wअगरi_only(wअगरionly_cfg, is_5g);
पूर्ण

व्योम rtl_btc_connect_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 action)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_connect_notअगरy(btcoexist, action);
पूर्ण

व्योम rtl_btc_mediastatus_notअगरy(काष्ठा rtl_priv *rtlpriv,
				क्रमागत rt_media_status mstatus)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_mediastatus_notअगरy(btcoexist, mstatus);
पूर्ण

व्योम rtl_btc_periodical(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	/*rtl_bt_dm_monitor();*/
	exhalbtc_periodical(btcoexist);
पूर्ण

व्योम rtl_btc_halt_notअगरy(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_halt_notअगरy(btcoexist);
पूर्ण

व्योम rtl_btc_btinfo_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 *पंचांगp_buf, u8 length)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	exhalbtc_bt_info_notअगरy(btcoexist, पंचांगp_buf, length);
पूर्ण

व्योम rtl_btc_bपंचांगpinfo_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 *पंचांगp_buf, u8 length)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 extid, seq;
	u16 bt_real_fw_ver;
	u8 bt_fw_ver;
	u8 *data;

	अगर (!btcoexist)
		वापस;

	अगर ((length < 4) || (!पंचांगp_buf))
		वापस;

	extid = पंचांगp_buf[0];
	/* not response from BT FW then निकास*/
	अगर (extid != 1) /* C2H_TRIG_BY_BT_FW = 1 */
		वापस;

	seq = पंचांगp_buf[2] >> 4;
	data = &पंचांगp_buf[3];

	/* BT Firmware version response */
	चयन (seq) अणु
	हाल BT_SEQ_GET_BT_VERSION:
		bt_real_fw_ver = पंचांगp_buf[3] | (पंचांगp_buf[4] << 8);
		bt_fw_ver = पंचांगp_buf[5];

		btcoexist->bt_info.bt_real_fw_ver = bt_real_fw_ver;
		btcoexist->bt_info.bt_fw_ver = bt_fw_ver;
		अवरोध;
	हाल BT_SEQ_GET_AFH_MAP_L:
		btcoexist->bt_info.afh_map_l = le32_to_cpu(*(__le32 *)data);
		अवरोध;
	हाल BT_SEQ_GET_AFH_MAP_M:
		btcoexist->bt_info.afh_map_m = le32_to_cpu(*(__le32 *)data);
		अवरोध;
	हाल BT_SEQ_GET_AFH_MAP_H:
		btcoexist->bt_info.afh_map_h = le16_to_cpu(*(__le16 *)data);
		अवरोध;
	हाल BT_SEQ_GET_BT_COEX_SUPPORTED_FEATURE:
		btcoexist->bt_info.bt_supported_feature = पंचांगp_buf[3] |
							  (पंचांगp_buf[4] << 8);
		अवरोध;
	हाल BT_SEQ_GET_BT_COEX_SUPPORTED_VERSION:
		btcoexist->bt_info.bt_supported_version = पंचांगp_buf[3] |
							  (पंचांगp_buf[4] << 8);
		अवरोध;
	हाल BT_SEQ_GET_BT_ANT_DET_VAL:
		btcoexist->bt_info.bt_ant_det_val = पंचांगp_buf[3];
		अवरोध;
	हाल BT_SEQ_GET_BT_BLE_SCAN_PARA:
		btcoexist->bt_info.bt_ble_scan_para = पंचांगp_buf[3] |
						      (पंचांगp_buf[4] << 8) |
						      (पंचांगp_buf[5] << 16) |
						      (पंचांगp_buf[6] << 24);
		अवरोध;
	हाल BT_SEQ_GET_BT_BLE_SCAN_TYPE:
		btcoexist->bt_info.bt_ble_scan_type = पंचांगp_buf[3];
		अवरोध;
	हाल BT_SEQ_GET_BT_DEVICE_INFO:
		btcoexist->bt_info.bt_device_info =
						le32_to_cpu(*(__le32 *)data);
		अवरोध;
	हाल BT_OP_GET_BT_FORBIDDEN_SLOT_VAL:
		btcoexist->bt_info.bt_क्रमb_slot_val =
						le32_to_cpu(*(__le32 *)data);
		अवरोध;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		"btmpinfo complete req_num=%d\n", seq);

	complete(&btcoexist->bt_mp_comp);
पूर्ण

bool rtl_btc_is_limited_dig(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस false;

	वापस btcoexist->bt_info.limited_dig;
पूर्ण

bool rtl_btc_is_disable_edca_turbo(काष्ठा rtl_priv *rtlpriv)
अणु
	bool bt_change_edca = false;
	u32 cur_edca_val;
	u32 edca_bt_hs_uplink = 0x5ea42b, edca_bt_hs_करोwnlink = 0x5ea42b;
	u32 edca_hs;
	u32 edca_addr = 0x504;

	cur_edca_val = rtl_पढ़ो_dword(rtlpriv, edca_addr);
	अगर (halbtc_is_wअगरi_uplink(rtlpriv)) अणु
		अगर (cur_edca_val != edca_bt_hs_uplink) अणु
			edca_hs = edca_bt_hs_uplink;
			bt_change_edca = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cur_edca_val != edca_bt_hs_करोwnlink) अणु
			edca_hs = edca_bt_hs_करोwnlink;
			bt_change_edca = true;
		पूर्ण
	पूर्ण

	अगर (bt_change_edca)
		rtl_ग_लिखो_dword(rtlpriv, edca_addr, edca_hs);

	वापस true;
पूर्ण

bool rtl_btc_is_bt_disabled(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस true;

	/* It seems 'bt_disabled' is never be initialized or set. */
	अगर (btcoexist->bt_info.bt_disabled)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

व्योम rtl_btc_special_packet_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 pkt_type)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);

	अगर (!btcoexist)
		वापस;

	वापस exhalbtc_special_packet_notअगरy(btcoexist, pkt_type);
पूर्ण

व्योम rtl_btc_चयन_band_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 band_type,
				bool scanning)
अणु
	काष्ठा btc_coexist *btcoexist = rtl_btc_coexist(rtlpriv);
	u8 type = BTC_NOT_SWITCH;

	अगर (!btcoexist)
		वापस;

	चयन (band_type) अणु
	हाल BAND_ON_2_4G:
		अगर (scanning)
			type = BTC_SWITCH_TO_24G;
		अन्यथा
			type = BTC_SWITCH_TO_24G_NOFORSCAN;
		अवरोध;

	हाल BAND_ON_5G:
		type = BTC_SWITCH_TO_5G;
		अवरोध;
	पूर्ण

	अगर (type != BTC_NOT_SWITCH)
		exhalbtc_चयन_band_notअगरy(btcoexist, type);
पूर्ण

व्योम rtl_btc_चयन_band_notअगरy_wअगरionly(काष्ठा rtl_priv *rtlpriv, u8 band_type,
					 bool scanning)
अणु
	काष्ठा wअगरi_only_cfg *wअगरionly_cfg = rtl_btc_wअगरi_only(rtlpriv);
	u8 is_5g = (band_type == BAND_ON_5G);

	अगर (!wअगरionly_cfg)
		वापस;

	exhalbtc_चयन_band_notअगरy_wअगरi_only(wअगरionly_cfg, is_5g);
पूर्ण

काष्ठा rtl_btc_ops *rtl_btc_get_ops_poपूर्णांकer(व्योम)
अणु
	वापस &rtl_btc_operation;
पूर्ण
EXPORT_SYMBOL(rtl_btc_get_ops_poपूर्णांकer);


क्रमागत rt_media_status mgnt_link_status_query(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	क्रमागत rt_media_status    m_status = RT_MEDIA_DISCONNECT;

	u8 bibss = (mac->opmode == NL80211_IFTYPE_ADHOC) ? 1 : 0;

	अगर (bibss || rtlpriv->mac80211.link_state >= MAC80211_LINKED)
		m_status = RT_MEDIA_CONNECT;

	वापस m_status;
पूर्ण

u8 rtl_get_hwpg_bt_exist(काष्ठा rtl_priv *rtlpriv)
अणु
	वापस rtlpriv->btcoexist.btc_info.btcoexist;
पूर्ण

MODULE_AUTHOR("Page He	<page_he@realsil.com.cn>");
MODULE_AUTHOR("Realtek WlanFAE	<wlanfae@realtek.com>");
MODULE_AUTHOR("Larry Finger	<Larry.FInger@lwfinger.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek 802.11n PCI wireless core");

अटल पूर्णांक __init rtl_btcoexist_module_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम __निकास rtl_btcoexist_module_निकास(व्योम)
अणु
	वापस;
पूर्ण

module_init(rtl_btcoexist_module_init);
module_निकास(rtl_btcoexist_module_निकास);
