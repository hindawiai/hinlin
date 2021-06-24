<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2010  Realtek Corporation.*/

#अगर_अघोषित __RTL_BTC_H__
#घोषणा __RTL_BTC_H__

#समावेश "halbt_precomp.h"

व्योम rtl_btc_init_variables(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_init_variables_wअगरi_only(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_deinit_variables(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_init_hal_vars(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_घातer_on_setting(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_init_hw_config(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_init_hw_config_wअगरi_only(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_ips_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 type);
व्योम rtl_btc_lps_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 type);
व्योम rtl_btc_scan_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 scantype);
व्योम rtl_btc_scan_notअगरy_wअगरi_only(काष्ठा rtl_priv *rtlpriv, u8 scantype);
व्योम rtl_btc_connect_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 action);
व्योम rtl_btc_mediastatus_notअगरy(काष्ठा rtl_priv *rtlpriv,
				क्रमागत rt_media_status mstatus);
व्योम rtl_btc_periodical(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_halt_notअगरy(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_btinfo_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 *पंचांगpbuf, u8 length);
व्योम rtl_btc_bपंचांगpinfo_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 *पंचांगp_buf, u8 length);
bool rtl_btc_is_limited_dig(काष्ठा rtl_priv *rtlpriv);
bool rtl_btc_is_disable_edca_turbo(काष्ठा rtl_priv *rtlpriv);
bool rtl_btc_is_bt_disabled(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_special_packet_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 pkt_type);
व्योम rtl_btc_चयन_band_notअगरy(काष्ठा rtl_priv *rtlpriv, u8 band_type,
				bool scanning);
व्योम rtl_btc_चयन_band_notअगरy_wअगरionly(काष्ठा rtl_priv *rtlpriv, u8 band_type,
					 bool scanning);
व्योम rtl_btc_display_bt_coex_info(काष्ठा rtl_priv *rtlpriv, काष्ठा seq_file *m);
व्योम rtl_btc_record_pwr_mode(काष्ठा rtl_priv *rtlpriv, u8 *buf, u8 len);
u8   rtl_btc_get_lps_val(काष्ठा rtl_priv *rtlpriv);
u8   rtl_btc_get_rpwm_val(काष्ठा rtl_priv *rtlpriv);
bool rtl_btc_is_bt_ctrl_lps(काष्ठा rtl_priv *rtlpriv);
bool rtl_btc_is_bt_lps_on(काष्ठा rtl_priv *rtlpriv);
व्योम rtl_btc_get_ampdu_cfg(काष्ठा rtl_priv *rtlpriv, u8 *reject_agg,
			   u8 *ctrl_agg_size, u8 *agg_size);

काष्ठा rtl_btc_ops *rtl_btc_get_ops_poपूर्णांकer(व्योम);

u8 rtl_get_hwpg_bt_exist(काष्ठा rtl_priv *rtlpriv);
u8 rtl_get_hwpg_bt_type(काष्ठा rtl_priv *rtlpriv);
u8 rtl_get_hwpg_ant_num(काष्ठा rtl_priv *rtlpriv);
u8 rtl_get_hwpg_single_ant_path(काष्ठा rtl_priv *rtlpriv);
u8 rtl_get_hwpg_package_type(काष्ठा rtl_priv *rtlpriv);

क्रमागत rt_media_status mgnt_link_status_query(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
