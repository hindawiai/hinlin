<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2014  Realtek Corporation.*/

#अगर_अघोषित __RTL92E_HW_H__
#घोषणा __RTL92E_HW_H__

व्योम rtl92ee_get_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl92ee_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांक_vec);
पूर्णांक rtl92ee_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_card_disable(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl92ee_set_network_type(काष्ठा ieee80211_hw *hw, क्रमागत nl80211_अगरtype type);
व्योम rtl92ee_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid);
व्योम rtl92ee_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci);
व्योम rtl92ee_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				   u32 add_msr, u32 rm_msr);
व्योम rtl92ee_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable, u8 *val);
व्योम rtl92ee_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_sta *sta, u8 rssi_level,
				 bool update_bw);
व्योम rtl92ee_update_channel_access_setting(काष्ठा ieee80211_hw *hw);
bool rtl92ee_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw, u8 *valid);
व्योम rtl92ee_enable_hw_security_config(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_set_key(काष्ठा ieee80211_hw *hw, u32 key_index,
		     u8 *p_macaddr, bool is_group, u8 enc_algo,
		     bool is_wepkey, bool clear_all);
व्योम rtl92ee_पढ़ो_bt_coexist_info_from_hwpg(काष्ठा ieee80211_hw *hw,
					    bool स्वतःload_fail, u8 *hwinfo);
व्योम rtl92ee_bt_reg_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_bt_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_suspend(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_resume(काष्ठा ieee80211_hw *hw);
व्योम rtl92ee_allow_all_destaddr(काष्ठा ieee80211_hw *hw, bool allow_all_da,
				bool ग_लिखो_पूर्णांकo_reg);
व्योम rtl92ee_fw_clk_off_समयr_callback(अचिन्हित दीर्घ data);
#पूर्ण_अगर
