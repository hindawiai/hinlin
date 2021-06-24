<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../rtl8192ce/phy.h"

व्योम rtl92cu_bb_block_on(काष्ठा ieee80211_hw *hw);
bool rtl8192_phy_check_is_legal_rfpath(काष्ठा ieee80211_hw *hw, u32 rfpath);
व्योम rtl92c_phy_set_io(काष्ठा ieee80211_hw *hw);
bool _rtl92cu_phy_config_mac_with_headerfile(काष्ठा ieee80211_hw *hw);
bool rtl92cu_phy_bb_config(काष्ठा ieee80211_hw *hw);
u32 rtl92cu_phy_query_rf_reg(काष्ठा ieee80211_hw *hw,
			     क्रमागत radio_path rfpath, u32 regaddr, u32 biपंचांगask);
व्योम rtl92cu_phy_set_rf_reg(काष्ठा ieee80211_hw *hw,
			    क्रमागत radio_path rfpath,
			    u32 regaddr, u32 biपंचांगask, u32 data);
bool rtl92cu_phy_mac_config(काष्ठा ieee80211_hw *hw);
bool _rtl92cu_phy_config_bb_with_pgheaderfile(काष्ठा ieee80211_hw *hw,
					      u8 configtype);
व्योम _rtl92cu_phy_lc_calibrate(काष्ठा ieee80211_hw *hw, bool is2t);
bool _rtl92cu_phy_config_bb_with_headerfile(काष्ठा ieee80211_hw *hw,
					    u8 configtype);
व्योम rtl92cu_phy_set_bw_mode_callback(काष्ठा ieee80211_hw *hw);
bool rtl92cu_phy_set_rf_घातer_state(काष्ठा ieee80211_hw *hw,
				    क्रमागत rf_pwrstate rfpwr_state);
