<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "hal_bt_coexist.h"
#समावेश "../pci.h"
#समावेश "dm.h"
#समावेश "fw.h"
#समावेश "phy.h"
#समावेश "reg.h"
#समावेश "hal_btc.h"

अटल bool bt_operation_on;

व्योम rtl8723e_dm_bt_reject_ap_aggregated_packet(काष्ठा ieee80211_hw *hw,
						bool b_reject)
अणु
पूर्ण

व्योम _rtl8723_dm_bt_check_wअगरi_state(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	अगर (rtlpriv->link_info.busytraffic) अणु
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_IDLE;

		अगर (rtlpriv->link_info.tx_busy_traffic)
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_UPLINK;
		अन्यथा
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_UPLINK;

		अगर (rtlpriv->link_info.rx_busy_traffic)
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_DOWNLINK;
		अन्यथा
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_DOWNLINK;
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.cstate |= BT_COEX_STATE_WIFI_IDLE;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_UPLINK;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_DOWNLINK;
	पूर्ण

	अगर (rtlpriv->mac80211.mode == WIRELESS_MODE_G ||
	    rtlpriv->mac80211.mode == WIRELESS_MODE_B) अणु
		rtlpriv->btcoexist.cstate |=
			BT_COEX_STATE_WIFI_LEGACY;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_HT20;
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_HT40;
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_LEGACY;
		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_20_40) अणु
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_HT40;
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_HT20;
		पूर्ण अन्यथा अणु
			rtlpriv->btcoexist.cstate |=
				BT_COEX_STATE_WIFI_HT20;
			rtlpriv->btcoexist.cstate &=
				~BT_COEX_STATE_WIFI_HT40;
		पूर्ण
	पूर्ण

	अगर (bt_operation_on)
		rtlpriv->btcoexist.cstate |= BT_COEX_STATE_BT30;
	अन्यथा
		rtlpriv->btcoexist.cstate &= ~BT_COEX_STATE_BT30;
पूर्ण

u8 rtl8723e_dm_bt_check_coex_rssi_state1(काष्ठा ieee80211_hw *hw,
					 u8 level_num, u8 rssi_thresh,
					 u8 rssi_thresh1)

अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	दीर्घ undecoratedsmoothed_pwdb;
	u8 bt_rssi_state = 0;

	undecoratedsmoothed_pwdb = rtl8723e_dm_bt_get_rx_ss(hw);

	अगर (level_num == 2) अणु
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_RSSI_1_MEDIUM;

		अगर ((rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_LOW) ||
		    (rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_STAY_LOW)) अणु
			अगर (undecoratedsmoothed_pwdb >=
			    (rssi_thresh + BT_FW_COEX_THRESH_TOL)) अणु
				bt_rssi_state = BT_RSSI_STATE_HIGH;
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_RSSI_1_HIGH;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state switch to High\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (undecoratedsmoothed_pwdb < rssi_thresh) अणु
				bt_rssi_state = BT_RSSI_STATE_LOW;
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_RSSI_1_LOW;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state switch to Low\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (level_num == 3) अणु
		अगर (rssi_thresh > rssi_thresh1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[DM][BT], RSSI_1 thresh error!!\n");
			वापस rtlpriv->btcoexist.bt_pre_rssi_state;
		पूर्ण

		अगर ((rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_LOW) ||
		    (rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_STAY_LOW)) अणु
			अगर (undecoratedsmoothed_pwdb >=
			    (rssi_thresh+BT_FW_COEX_THRESH_TOL)) अणु
				bt_rssi_state = BT_RSSI_STATE_MEDIUM;
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_RSSI_1_MEDIUM;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_LOW;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state switch to Medium\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अगर ((rtlpriv->btcoexist.bt_pre_rssi_state ==
			    BT_RSSI_STATE_MEDIUM) ||
			   (rtlpriv->btcoexist.bt_pre_rssi_state ==
			    BT_RSSI_STATE_STAY_MEDIUM)) अणु
			अगर (undecoratedsmoothed_pwdb >=
			    (rssi_thresh1 + BT_FW_COEX_THRESH_TOL)) अणु
				bt_rssi_state = BT_RSSI_STATE_HIGH;
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_RSSI_1_HIGH;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_LOW;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state switch to High\n");
			पूर्ण अन्यथा अगर (undecoratedsmoothed_pwdb < rssi_thresh) अणु
				bt_rssi_state = BT_RSSI_STATE_LOW;
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_RSSI_1_LOW;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_HIGH;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state switch to Low\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state stay at Medium\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (undecoratedsmoothed_pwdb < rssi_thresh1) अणु
				bt_rssi_state = BT_RSSI_STATE_MEDIUM;
				rtlpriv->btcoexist.cstate |=
					BT_COEX_STATE_WIFI_RSSI_1_MEDIUM;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_HIGH;
				rtlpriv->btcoexist.cstate &=
					~BT_COEX_STATE_WIFI_RSSI_1_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state switch to Medium\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI_1 state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण
	rtlpriv->btcoexist.bt_pre_rssi_state1 = bt_rssi_state;

	वापस bt_rssi_state;
पूर्ण

u8 rtl8723e_dm_bt_check_coex_rssi_state(काष्ठा ieee80211_hw *hw,
					u8 level_num,
					u8 rssi_thresh,
					u8 rssi_thresh1)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	दीर्घ undecoratedsmoothed_pwdb = 0;
	u8 bt_rssi_state = 0;

	undecoratedsmoothed_pwdb = rtl8723e_dm_bt_get_rx_ss(hw);

	अगर (level_num == 2) अणु
		rtlpriv->btcoexist.cstate &=
			~BT_COEX_STATE_WIFI_RSSI_MEDIUM;

		अगर ((rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_LOW) ||
		    (rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_STAY_LOW)) अणु
			अगर (undecoratedsmoothed_pwdb >=
			    (rssi_thresh + BT_FW_COEX_THRESH_TOL)) अणु
				bt_rssi_state = BT_RSSI_STATE_HIGH;
				rtlpriv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_RSSI_HIGH;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state switch to High\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (undecoratedsmoothed_pwdb < rssi_thresh) अणु
				bt_rssi_state = BT_RSSI_STATE_LOW;
				rtlpriv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_RSSI_LOW;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state switch to Low\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (level_num == 3) अणु
		अगर (rssi_thresh > rssi_thresh1) अणु
			rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
				"[DM][BT], RSSI thresh error!!\n");
			वापस rtlpriv->btcoexist.bt_pre_rssi_state;
		पूर्ण
		अगर ((rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_LOW) ||
		    (rtlpriv->btcoexist.bt_pre_rssi_state ==
		     BT_RSSI_STATE_STAY_LOW)) अणु
			अगर (undecoratedsmoothed_pwdb >=
			    (rssi_thresh + BT_FW_COEX_THRESH_TOL)) अणु
				bt_rssi_state = BT_RSSI_STATE_MEDIUM;
				rtlpriv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_RSSI_MEDIUM;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_LOW;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state switch to Medium\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state stay at Low\n");
			पूर्ण
		पूर्ण अन्यथा अगर ((rtlpriv->btcoexist.bt_pre_rssi_state ==
				BT_RSSI_STATE_MEDIUM) ||
			(rtlpriv->btcoexist.bt_pre_rssi_state ==
				BT_RSSI_STATE_STAY_MEDIUM)) अणु
			अगर (undecoratedsmoothed_pwdb >=
			    (rssi_thresh1 + BT_FW_COEX_THRESH_TOL)) अणु
				bt_rssi_state = BT_RSSI_STATE_HIGH;
				rtlpriv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_RSSI_HIGH;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_LOW;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state switch to High\n");
			पूर्ण अन्यथा अगर (undecoratedsmoothed_pwdb < rssi_thresh) अणु
				bt_rssi_state = BT_RSSI_STATE_LOW;
				rtlpriv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_RSSI_LOW;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_HIGH;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state switch to Low\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_MEDIUM;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state stay at Medium\n");
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (undecoratedsmoothed_pwdb < rssi_thresh1) अणु
				bt_rssi_state = BT_RSSI_STATE_MEDIUM;
				rtlpriv->btcoexist.cstate
					|= BT_COEX_STATE_WIFI_RSSI_MEDIUM;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_HIGH;
				rtlpriv->btcoexist.cstate
					&= ~BT_COEX_STATE_WIFI_RSSI_LOW;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state switch to Medium\n");
			पूर्ण अन्यथा अणु
				bt_rssi_state = BT_RSSI_STATE_STAY_HIGH;
				rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
					"[DM][BT], RSSI state stay at High\n");
			पूर्ण
		पूर्ण
	पूर्ण
	rtlpriv->btcoexist.bt_pre_rssi_state = bt_rssi_state;
	वापस bt_rssi_state;
पूर्ण

दीर्घ rtl8723e_dm_bt_get_rx_ss(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	दीर्घ undecoratedsmoothed_pwdb = 0;

	अगर (rtlpriv->mac80211.link_state >= MAC80211_LINKED) अणु
		undecoratedsmoothed_pwdb =
			GET_UNDECORATED_AVERAGE_RSSI(rtlpriv);
	पूर्ण अन्यथा अणु
		undecoratedsmoothed_pwdb
			= rtlpriv->dm.entry_min_undec_sm_pwdb;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"%s = %ld\n", __func__,
		undecoratedsmoothed_pwdb);

	वापस undecoratedsmoothed_pwdb;
पूर्ण

व्योम rtl8723e_dm_bt_balance(काष्ठा ieee80211_hw *hw,
			    bool balance_on, u8 ms0, u8 ms1)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 h2c_parameter[3] = अणु0पूर्ण;

	अगर (balance_on) अणु
		h2c_parameter[2] = 1;
		h2c_parameter[1] = ms1;
		h2c_parameter[0] = ms0;
		rtlpriv->btcoexist.fw_coexist_all_off = false;
	पूर्ण अन्यथा अणु
		h2c_parameter[2] = 0;
		h2c_parameter[1] = 0;
		h2c_parameter[0] = 0;
	पूर्ण
	rtlpriv->btcoexist.balance_on = balance_on;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"[DM][BT], Balance=[%s:%dms:%dms], write 0xc=0x%x\n",
		balance_on ? "ON" : "OFF", ms0, ms1, h2c_parameter[0] << 16 |
		h2c_parameter[1] << 8 | h2c_parameter[2]);

	rtl8723e_fill_h2c_cmd(hw, 0xc, 3, h2c_parameter);
पूर्ण


व्योम rtl8723e_dm_bt_agc_table(काष्ठा ieee80211_hw *hw, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (type == BT_AGCTABLE_OFF) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BT]AGCTable Off!\n");
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x641c0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x631d0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x621e0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x611f0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x60200001);

		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x32000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x71000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0xb0000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0xfc000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_G1, 0xfffff, 0x30355);
	पूर्ण अन्यथा अगर (type == BT_AGCTABLE_ON) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BT]AGCTable On!\n");
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x4e1c0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x4d1d0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x4c1e0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x4b1f0001);
		rtl_ग_लिखो_dword(rtlpriv, 0xc78, 0x4a200001);

		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0xdc000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x90000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x51000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_AGC_HP, 0xfffff, 0x12000);
		rtl8723e_phy_set_rf_reg(hw, RF90_PATH_A,
					RF_RX_G1, 0xfffff, 0x00355);

		rtlpriv->btcoexist.sw_coexist_all_off = false;
	पूर्ण
पूर्ण

व्योम rtl8723e_dm_bt_bb_back_off_level(काष्ठा ieee80211_hw *hw, u8 type)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (type == BT_BB_BACKOFF_OFF) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BT]BBBackOffLevel Off!\n");
		rtl_ग_लिखो_dword(rtlpriv, 0xc04, 0x3a05611);
	पूर्ण अन्यथा अगर (type == BT_BB_BACKOFF_ON) अणु
		rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
			"[BT]BBBackOffLevel On!\n");
		rtl_ग_लिखो_dword(rtlpriv, 0xc04, 0x3a07611);
		rtlpriv->btcoexist.sw_coexist_all_off = false;
	पूर्ण
पूर्ण

व्योम rtl8723e_dm_bt_fw_coex_all_off(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"rtl8723e_dm_bt_fw_coex_all_off()\n");

	अगर (rtlpriv->btcoexist.fw_coexist_all_off)
		वापस;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"rtl8723e_dm_bt_fw_coex_all_off(), real Do\n");
	rtl8723e_dm_bt_fw_coex_all_off_8723a(hw);
	rtlpriv->btcoexist.fw_coexist_all_off = true;
पूर्ण

व्योम rtl8723e_dm_bt_sw_coex_all_off(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"%s\n", __func__);

	अगर (rtlpriv->btcoexist.sw_coexist_all_off)
		वापस;

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"%s, real Do\n", __func__);
	rtl8723e_dm_bt_sw_coex_all_off_8723a(hw);
	rtlpriv->btcoexist.sw_coexist_all_off = true;
पूर्ण

व्योम rtl8723e_dm_bt_hw_coex_all_off(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"%s\n", __func__);

	अगर (rtlpriv->btcoexist.hw_coexist_all_off)
		वापस;
	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_TRACE,
		"%s, real Do\n", __func__);

	rtl8723e_dm_bt_hw_coex_all_off_8723a(hw);

	rtlpriv->btcoexist.hw_coexist_all_off = true;
पूर्ण

व्योम rtl8723e_btdm_coex_all_off(काष्ठा ieee80211_hw *hw)
अणु
	rtl8723e_dm_bt_fw_coex_all_off(hw);
	rtl8723e_dm_bt_sw_coex_all_off(hw);
	rtl8723e_dm_bt_hw_coex_all_off(hw);
पूर्ण

bool rtl8723e_dm_bt_is_coexist_state_changed(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर ((rtlpriv->btcoexist.previous_state == rtlpriv->btcoexist.cstate) &&
	    (rtlpriv->btcoexist.previous_state_h ==
	     rtlpriv->btcoexist.cstate_h))
		वापस false;
	वापस true;
पूर्ण

bool rtl8723e_dm_bt_is_wअगरi_up_link(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->link_info.tx_busy_traffic)
		वापस true;
	वापस false;
पूर्ण
