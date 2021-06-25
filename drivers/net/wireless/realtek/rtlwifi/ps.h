<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#अगर_अघोषित __REALTEK_RTL_PCI_PS_H__
#घोषणा __REALTEK_RTL_PCI_PS_H__

#घोषणा MAX_SW_LPS_SLEEP_INTV	5

bool rtl_ps_enable_nic(काष्ठा ieee80211_hw *hw);
bool rtl_ps_disable_nic(काष्ठा ieee80211_hw *hw);
व्योम rtl_ips_nic_off(काष्ठा ieee80211_hw *hw);
व्योम rtl_ips_nic_on(काष्ठा ieee80211_hw *hw);
व्योम rtl_ips_nic_off_wq_callback(काष्ठा work_काष्ठा *work);
व्योम rtl_lps_enter(काष्ठा ieee80211_hw *hw, bool may_block);
व्योम rtl_lps_leave(काष्ठा ieee80211_hw *hw, bool may_block);

व्योम rtl_lps_set_psmode(काष्ठा ieee80211_hw *hw, u8 rt_psmode);

व्योम rtl_swlps_beacon(काष्ठा ieee80211_hw *hw, व्योम *data, अचिन्हित पूर्णांक len);
व्योम rtl_swlps_wq_callback(काष्ठा work_काष्ठा *work);
व्योम rtl_swlps_rfon_wq_callback(काष्ठा work_काष्ठा *work);
व्योम rtl_swlps_rf_awake(काष्ठा ieee80211_hw *hw);
व्योम rtl_swlps_rf_sleep(काष्ठा ieee80211_hw *hw);
व्योम rtl_p2p_ps_cmd(काष्ठा ieee80211_hw *hw , u8 p2p_ps_state);
व्योम rtl_p2p_info(काष्ठा ieee80211_hw *hw, व्योम *data, अचिन्हित पूर्णांक len);
व्योम rtl_lps_change_work_callback(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर
