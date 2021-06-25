<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __REALTEK_PCI92SE_HW_H__
#घोषणा __REALTEK_PCI92SE_HW_H__

#घोषणा MSR_LINK_MANAGED   2
#घोषणा MSR_LINK_NONE      0
#घोषणा MSR_LINK_SHIFT     0
#घोषणा MSR_LINK_ADHOC     1
#घोषणा MSR_LINK_MASTER    3

क्रमागत WIRELESS_NETWORK_TYPE अणु
	WIRELESS_11B = 1,
	WIRELESS_11G = 2,
	WIRELESS_11A = 4,
	WIRELESS_11N = 8
पूर्ण;

व्योम rtl92se_get_hw_reg(काष्ठा ieee80211_hw *hw,
			u8 variable, u8 *val);
व्योम rtl92se_पढ़ो_eeprom_info(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_पूर्णांकerrupt_recognized(काष्ठा ieee80211_hw *hw,
				  काष्ठा rtl_पूर्णांक *पूर्णांक_vec);
पूर्णांक rtl92se_hw_init(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_card_disable(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_enable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_disable_पूर्णांकerrupt(काष्ठा ieee80211_hw *hw);
पूर्णांक rtl92se_set_network_type(काष्ठा ieee80211_hw *hw,
			     क्रमागत nl80211_अगरtype type);
व्योम rtl92se_set_check_bssid(काष्ठा ieee80211_hw *hw, bool check_bssid);
व्योम rtl92se_set_mac_addr(काष्ठा rtl_io *io, स्थिर u8 *addr);
व्योम rtl92se_set_qos(काष्ठा ieee80211_hw *hw, पूर्णांक aci);
व्योम rtl92se_set_beacon_related_रेजिस्टरs(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_set_beacon_पूर्णांकerval(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_update_पूर्णांकerrupt_mask(काष्ठा ieee80211_hw *hw,
				   u32 add_msr, u32 rm_msr);
व्योम rtl92se_set_hw_reg(काष्ठा ieee80211_hw *hw, u8 variable,
			u8 *val);
व्योम rtl92se_update_hal_rate_tbl(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u8 rssi_level, bool update_bw);
व्योम rtl92se_update_channel_access_setting(काष्ठा ieee80211_hw *hw);
bool rtl92se_gpio_radio_on_off_checking(काष्ठा ieee80211_hw *hw,
					u8 *valid);
व्योम rtl8192se_gpiobit3_cfg_inpuपंचांगode(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_enable_hw_security_config(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_set_key(काष्ठा ieee80211_hw *hw,
		     u32 key_index, u8 *macaddr, bool is_group,
		     u8 enc_algo, bool is_wepkey, bool clear_all);
व्योम rtl92se_suspend(काष्ठा ieee80211_hw *hw);
व्योम rtl92se_resume(काष्ठा ieee80211_hw *hw);

#पूर्ण_अगर
