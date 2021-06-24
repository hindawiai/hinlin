<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "../wifi.h"
#समावेश "../base.h"
#समावेश "../core.h"
#समावेश "reg.h"
#समावेश "def.h"
#समावेश "phy.h"
#समावेश "dm.h"
#समावेश "fw.h"

अटल स्थिर u32 edca_setting_dl[PEER_MAX] = अणु
	0xa44f,		/* 0 UNKNOWN */
	0x5ea44f,	/* 1 REALTEK_90 */
	0x5ea44f,	/* 2 REALTEK_92SE */
	0xa630,		/* 3 BROAD	*/
	0xa44f,		/* 4 RAL */
	0xa630,		/* 5 ATH */
	0xa630,		/* 6 CISCO */
	0xa42b,		/* 7 MARV */
पूर्ण;

अटल स्थिर u32 edca_setting_dl_gmode[PEER_MAX] = अणु
	0x4322,		/* 0 UNKNOWN */
	0xa44f,		/* 1 REALTEK_90 */
	0x5ea44f,	/* 2 REALTEK_92SE */
	0xa42b,		/* 3 BROAD */
	0x5e4322,	/* 4 RAL */
	0x4322,		/* 5 ATH */
	0xa430,		/* 6 CISCO */
	0x5ea44f,	/* 7 MARV */
पूर्ण;

अटल स्थिर u32 edca_setting_ul[PEER_MAX] = अणु
	0x5e4322,	/* 0 UNKNOWN */
	0xa44f,		/* 1 REALTEK_90 */
	0x5ea44f,	/* 2 REALTEK_92SE */
	0x5ea322,	/* 3 BROAD */
	0x5ea422,	/* 4 RAL */
	0x5ea322,	/* 5 ATH */
	0x3ea44f,	/* 6 CISCO */
	0x5ea44f,	/* 7 MARV */
पूर्ण;

अटल व्योम _rtl92s_dm_check_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	अटल u64 last_txok_cnt;
	अटल u64 last_rxok_cnt;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;

	u32 edca_be_ul = edca_setting_ul[mac->venकरोr];
	u32 edca_be_dl = edca_setting_dl[mac->venकरोr];
	u32 edca_gmode = edca_setting_dl_gmode[mac->venकरोr];

	अगर (mac->link_state != MAC80211_LINKED) अणु
		rtlpriv->dm.current_turbo_edca = false;
		जाओ dm_checkedcaturbo_निकास;
	पूर्ण

	अगर ((!rtlpriv->dm.is_any_nonbepkts) &&
	    (!rtlpriv->dm.disable_framebursting)) अणु
		cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
		cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;

		अगर (rtlpriv->phy.rf_type == RF_1T2R) अणु
			अगर (cur_txok_cnt > 4 * cur_rxok_cnt) अणु
				/* Uplink TP is present. */
				अगर (rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) अणु
					rtl_ग_लिखो_dword(rtlpriv, EDCAPARA_BE,
							edca_be_ul);
					rtlpriv->dm.is_cur_rdlstate = false;
				पूर्ण
			पूर्ण अन्यथा अणु/* Balance TP is present. */
				अगर (!rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) अणु
					अगर (mac->mode == WIRELESS_MODE_G ||
					    mac->mode == WIRELESS_MODE_B)
						rtl_ग_लिखो_dword(rtlpriv,
								EDCAPARA_BE,
								edca_gmode);
					अन्यथा
						rtl_ग_लिखो_dword(rtlpriv,
								EDCAPARA_BE,
								edca_be_dl);
					rtlpriv->dm.is_cur_rdlstate = true;
				पूर्ण
			पूर्ण
			rtlpriv->dm.current_turbo_edca = true;
		पूर्ण अन्यथा अणु
			अगर (cur_rxok_cnt > 4 * cur_txok_cnt) अणु
				अगर (!rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) अणु
					अगर (mac->mode == WIRELESS_MODE_G ||
					    mac->mode == WIRELESS_MODE_B)
						rtl_ग_लिखो_dword(rtlpriv,
								EDCAPARA_BE,
								edca_gmode);
					अन्यथा
						rtl_ग_लिखो_dword(rtlpriv,
								EDCAPARA_BE,
								edca_be_dl);
					rtlpriv->dm.is_cur_rdlstate = true;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (rtlpriv->dm.is_cur_rdlstate ||
					!rtlpriv->dm.current_turbo_edca) अणु
					rtl_ग_लिखो_dword(rtlpriv, EDCAPARA_BE,
							edca_be_ul);
					rtlpriv->dm.is_cur_rdlstate = false;
				पूर्ण
			पूर्ण
			rtlpriv->dm.current_turbo_edca = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->dm.current_turbo_edca) अणु
			u8 पंचांगp = AC0_BE;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      &पंचांगp);
			rtlpriv->dm.current_turbo_edca = false;
		पूर्ण
	पूर्ण

dm_checkedcaturbo_निकास:
	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
पूर्ण

अटल व्योम _rtl92s_dm_txघातertracking_callback_thermalmeter(
					काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 thermalvalue = 0;
	u32 fw_cmd = 0;

	rtlpriv->dm.txघातer_trackinginit = true;

	thermalvalue = (u8)rtl_get_rfreg(hw, RF90_PATH_A, RF_T_METER, 0x1f);

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"Readback Thermal Meter = 0x%x pre thermal meter 0x%x eeprom_thermal meter 0x%x\n",
		thermalvalue,
		rtlpriv->dm.thermalvalue, rtlefuse->eeprom_thermalmeter);

	अगर (thermalvalue) अणु
		rtlpriv->dm.thermalvalue = thermalvalue;
		अगर (hal_get_firmwareversion(rtlpriv) >= 0x35) अणु
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_TXPWR_TRACK_THERMAL);
		पूर्ण अन्यथा अणु
			fw_cmd = (FW_TXPWR_TRACK_THERMAL |
				 (rtlpriv->efuse.thermalmeter[0] << 8) |
				 (thermalvalue << 16));

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Write to FW Thermal Val = 0x%x\n", fw_cmd);

			rtl_ग_लिखो_dword(rtlpriv, WFM5, fw_cmd);
			rtl92s_phy_chk_fwcmd_ioकरोne(hw);
		पूर्ण
	पूर्ण

	rtlpriv->dm.txघातercount = 0;
पूर्ण

अटल व्योम _rtl92s_dm_check_txघातertracking_thermalmeter(
					काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 tx_घातer_checkcnt = 5;

	/* 2T2R TP issue */
	अगर (rtlphy->rf_type == RF_2T2R)
		वापस;

	अगर (!rtlpriv->dm.txघातer_tracking)
		वापस;

	अगर (rtlpriv->dm.txघातercount <= tx_घातer_checkcnt) अणु
		rtlpriv->dm.txघातercount++;
		वापस;
	पूर्ण

	अगर (!rtlpriv->dm.पंचांग_trigger) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, RF_T_METER,
			      RFREG_OFFSET_MASK, 0x60);
		rtlpriv->dm.पंचांग_trigger = 1;
	पूर्ण अन्यथा अणु
		_rtl92s_dm_txघातertracking_callback_thermalmeter(hw);
		rtlpriv->dm.पंचांग_trigger = 0;
	पूर्ण
पूर्ण

अटल व्योम _rtl92s_dm_refresh_rateadaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rate_adaptive *ra = &(rtlpriv->ra);
	काष्ठा ieee80211_sta *sta = शून्य;
	u32 low_rssi_thresh = 0;
	u32 middle_rssi_thresh = 0;
	u32 high_rssi_thresh = 0;

	अगर (is_hal_stop(rtlhal))
		वापस;

	अगर (!rtlpriv->dm.useramask)
		वापस;

	अगर (hal_get_firmwareversion(rtlpriv) >= 61 &&
	    !rtlpriv->dm.inक्रमm_fw_driverctrldm) अणु
		rtl92s_phy_set_fw_cmd(hw, FW_CMD_CTRL_DM_BY_DRIVER);
		rtlpriv->dm.inक्रमm_fw_driverctrldm = true;
	पूर्ण

	अगर ((mac->link_state == MAC80211_LINKED) &&
	    (mac->opmode == NL80211_IFTYPE_STATION)) अणु
		चयन (ra->pre_ratr_state) अणु
		हाल DM_RATR_STA_HIGH:
			high_rssi_thresh = 40;
			middle_rssi_thresh = 30;
			low_rssi_thresh = 20;
			अवरोध;
		हाल DM_RATR_STA_MIDDLE:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 30;
			low_rssi_thresh = 20;
			अवरोध;
		हाल DM_RATR_STA_LOW:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 34;
			low_rssi_thresh = 20;
			अवरोध;
		हाल DM_RATR_STA_ULTRALOW:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 34;
			low_rssi_thresh = 24;
			अवरोध;
		शेष:
			high_rssi_thresh = 44;
			middle_rssi_thresh = 34;
			low_rssi_thresh = 24;
			अवरोध;
		पूर्ण

		अगर (rtlpriv->dm.undec_sm_pwdb > (दीर्घ)high_rssi_thresh) अणु
			ra->ratr_state = DM_RATR_STA_HIGH;
		पूर्ण अन्यथा अगर (rtlpriv->dm.undec_sm_pwdb >
			   (दीर्घ)middle_rssi_thresh) अणु
			ra->ratr_state = DM_RATR_STA_LOW;
		पूर्ण अन्यथा अगर (rtlpriv->dm.undec_sm_pwdb >
			   (दीर्घ)low_rssi_thresh) अणु
			ra->ratr_state = DM_RATR_STA_LOW;
		पूर्ण अन्यथा अणु
			ra->ratr_state = DM_RATR_STA_ULTRALOW;
		पूर्ण

		अगर (ra->pre_ratr_state != ra->ratr_state) अणु
			rtl_dbg(rtlpriv, COMP_RATE, DBG_LOUD,
				"RSSI = %ld RSSI_LEVEL = %d PreState = %d, CurState = %d\n",
				rtlpriv->dm.undec_sm_pwdb, ra->ratr_state,
				ra->pre_ratr_state, ra->ratr_state);

			rcu_पढ़ो_lock();
			sta = rtl_find_sta(hw, mac->bssid);
			अगर (sta)
				rtlpriv->cfg->ops->update_rate_tbl(hw, sta,
							   ra->ratr_state,
							   true);
			rcu_पढ़ो_unlock();

			ra->pre_ratr_state = ra->ratr_state;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl92s_dm_चयन_baseband_mrc(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	bool current_mrc;
	bool enable_mrc = true;
	दीर्घ पंचांगpentry_maxpwdb = 0;
	u8 rssi_a = 0;
	u8 rssi_b = 0;

	अगर (is_hal_stop(rtlhal))
		वापस;

	अगर ((rtlphy->rf_type == RF_1T1R) || (rtlphy->rf_type == RF_2T2R))
		वापस;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_MRC, (u8 *)(&current_mrc));

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (rtlpriv->dm.undec_sm_pwdb > पंचांगpentry_maxpwdb) अणु
			rssi_a = rtlpriv->stats.rx_rssi_percentage[RF90_PATH_A];
			rssi_b = rtlpriv->stats.rx_rssi_percentage[RF90_PATH_B];
		पूर्ण
	पूर्ण

	/* MRC settings would NOT affect TP on Wireless B mode. */
	अगर (mac->mode != WIRELESS_MODE_B) अणु
		अगर ((rssi_a == 0) && (rssi_b == 0)) अणु
			enable_mrc = true;
		पूर्ण अन्यथा अगर (rssi_b > 30) अणु
			/* Turn on B-Path */
			enable_mrc = true;
		पूर्ण अन्यथा अगर (rssi_b < 5) अणु
			/* Turn off B-path  */
			enable_mrc = false;
		/* Take care of RSSI dअगरferentiation. */
		पूर्ण अन्यथा अगर (rssi_a > 15 && (rssi_a >= rssi_b)) अणु
			अगर ((rssi_a - rssi_b) > 15)
				/* Turn off B-path  */
				enable_mrc = false;
			अन्यथा अगर ((rssi_a - rssi_b) < 10)
				/* Turn on B-Path */
				enable_mrc = true;
			अन्यथा
				enable_mrc = current_mrc;
		पूर्ण अन्यथा अणु
			/* Turn on B-Path */
			enable_mrc = true;
		पूर्ण
	पूर्ण

	/* Update MRC settings अगर needed. */
	अगर (enable_mrc != current_mrc)
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_MRC,
					      (u8 *)&enable_mrc);

पूर्ण

व्योम rtl92s_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.current_turbo_edca = false;
	rtlpriv->dm.is_any_nonbepkts = false;
	rtlpriv->dm.is_cur_rdlstate = false;
पूर्ण

अटल व्योम _rtl92s_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rate_adaptive *ra = &(rtlpriv->ra);

	ra->ratr_state = DM_RATR_STA_MAX;
	ra->pre_ratr_state = DM_RATR_STA_MAX;

	अगर (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER &&
	    hal_get_firmwareversion(rtlpriv) >= 60)
		rtlpriv->dm.useramask = true;
	अन्यथा
		rtlpriv->dm.useramask = false;

	rtlpriv->dm.useramask = false;
	rtlpriv->dm.inक्रमm_fw_driverctrldm = false;
पूर्ण

अटल व्योम _rtl92s_dm_init_txघातertracking_thermalmeter(
				काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.txघातer_tracking = true;
	rtlpriv->dm.txघातercount = 0;
	rtlpriv->dm.txघातer_trackinginit = false;
पूर्ण

अटल व्योम _rtl92s_dm_false_alarm_counter_statistics(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);
	u32 ret_value;

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER1, MASKDWORD);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER2, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER3, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);

	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
		falsealm_cnt->cnt_rate_illegal + falsealm_cnt->cnt_crc8_fail +
		falsealm_cnt->cnt_mcs_fail;

	/* पढ़ो CCK false alarm */
	ret_value = rtl_get_bbreg(hw, 0xc64, MASKDWORD);
	falsealm_cnt->cnt_cck_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_all =	falsealm_cnt->cnt_ofdm_fail +
		falsealm_cnt->cnt_cck_fail;
पूर्ण

अटल व्योम rtl92s_backoff_enable_flag(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *digtable = &rtlpriv->dm_digtable;
	काष्ठा false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);

	अगर (falsealm_cnt->cnt_all > digtable->fa_highthresh) अणु
		अगर ((digtable->back_val - 6) <
			digtable->backoffval_range_min)
			digtable->back_val = digtable->backoffval_range_min;
		अन्यथा
			digtable->back_val -= 6;
	पूर्ण अन्यथा अगर (falsealm_cnt->cnt_all < digtable->fa_lowthresh) अणु
		अगर ((digtable->back_val + 6) >
			digtable->backoffval_range_max)
			digtable->back_val =
				 digtable->backoffval_range_max;
		अन्यथा
			digtable->back_val += 6;
	पूर्ण
पूर्ण

अटल व्योम _rtl92s_dm_initial_gain_sta_beक्रमeconnect(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *digtable = &rtlpriv->dm_digtable;
	काष्ठा false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);
	अटल u8 initialized, क्रमce_ग_लिखो;
	u8 initial_gain = 0;

	अगर ((digtable->pre_sta_cstate == digtable->cur_sta_cstate) ||
	    (digtable->cur_sta_cstate == DIG_STA_BEFORE_CONNECT)) अणु
		अगर (digtable->cur_sta_cstate == DIG_STA_BEFORE_CONNECT) अणु
			अगर (rtlpriv->psc.rfpwr_state != ERFON)
				वापस;

			अगर (digtable->backoff_enable_flag)
				rtl92s_backoff_enable_flag(hw);
			अन्यथा
				digtable->back_val = DM_DIG_BACKOFF_MAX;

			अगर ((digtable->rssi_val + 10 - digtable->back_val) >
				digtable->rx_gain_max)
				digtable->cur_igvalue =
						digtable->rx_gain_max;
			अन्यथा अगर ((digtable->rssi_val + 10 - digtable->back_val)
				 < digtable->rx_gain_min)
				digtable->cur_igvalue =
						digtable->rx_gain_min;
			अन्यथा
				digtable->cur_igvalue = digtable->rssi_val + 10
					- digtable->back_val;

			अगर (falsealm_cnt->cnt_all > 10000)
				digtable->cur_igvalue =
					 (digtable->cur_igvalue > 0x33) ?
					 digtable->cur_igvalue : 0x33;

			अगर (falsealm_cnt->cnt_all > 16000)
				digtable->cur_igvalue =
						 digtable->rx_gain_max;
		/* connected -> connected or disconnected -> disconnected  */
		पूर्ण अन्यथा अणु
			/* Firmware control DIG, करो nothing in driver dm */
			वापस;
		पूर्ण
		/* disconnected -> connected or connected ->
		 * disconnected or beक्रमeconnect->(dis)connected */
	पूर्ण अन्यथा अणु
		/* Enable FW DIG */
		digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
		rtl92s_phy_set_fw_cmd(hw, FW_CMD_DIG_ENABLE);

		digtable->back_val = DM_DIG_BACKOFF_MAX;
		digtable->cur_igvalue = rtlpriv->phy.शेष_initialgain[0];
		digtable->pre_igvalue = 0;
		वापस;
	पूर्ण

	/* Forced writing to prevent from fw-dig overwriting. */
	अगर (digtable->pre_igvalue != rtl_get_bbreg(hw, ROFDM0_XAAGCCORE1,
						  MASKBYTE0))
		क्रमce_ग_लिखो = 1;

	अगर ((digtable->pre_igvalue != digtable->cur_igvalue) ||
	    !initialized || क्रमce_ग_लिखो) अणु
		/* Disable FW DIG */
		rtl92s_phy_set_fw_cmd(hw, FW_CMD_DIG_DISABLE);

		initial_gain = (u8)digtable->cur_igvalue;

		/* Set initial gain. */
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, MASKBYTE0, initial_gain);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, MASKBYTE0, initial_gain);
		digtable->pre_igvalue = digtable->cur_igvalue;
		initialized = 1;
		क्रमce_ग_लिखो = 0;
	पूर्ण
पूर्ण

अटल व्योम _rtl92s_dm_ctrl_initgain_bytwoport(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dig = &rtlpriv->dm_digtable;

	अगर (rtlpriv->mac80211.act_scanning)
		वापस;

	/* Decide the current status and अगर modअगरy initial gain or not */
	अगर (rtlpriv->mac80211.link_state >= MAC80211_LINKED ||
	    rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC)
		dig->cur_sta_cstate = DIG_STA_CONNECT;
	अन्यथा
		dig->cur_sta_cstate = DIG_STA_DISCONNECT;

	dig->rssi_val = rtlpriv->dm.undec_sm_pwdb;

	/* Change dig mode to rssi */
	अगर (dig->cur_sta_cstate != DIG_STA_DISCONNECT) अणु
		अगर (dig->dig_twoport_algorithm ==
		    DIG_TWO_PORT_ALGO_FALSE_ALARM) अणु
			dig->dig_twoport_algorithm = DIG_TWO_PORT_ALGO_RSSI;
			rtl92s_phy_set_fw_cmd(hw, FW_CMD_DIG_MODE_SS);
		पूर्ण
	पूर्ण

	_rtl92s_dm_false_alarm_counter_statistics(hw);
	_rtl92s_dm_initial_gain_sta_beक्रमeconnect(hw);

	dig->pre_sta_cstate = dig->cur_sta_cstate;
पूर्ण

अटल व्योम _rtl92s_dm_ctrl_initgain_byrssi(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा dig_t *digtable = &rtlpriv->dm_digtable;

	/* 2T2R TP issue */
	अगर (rtlphy->rf_type == RF_2T2R)
		वापस;

	अगर (!rtlpriv->dm.dm_initialgain_enable)
		वापस;

	अगर (digtable->dig_enable_flag == false)
		वापस;

	_rtl92s_dm_ctrl_initgain_bytwoport(hw);
पूर्ण

अटल व्योम _rtl92s_dm_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ undec_sm_pwdb;
	दीर्घ txpwr_threshold_lv1, txpwr_threshold_lv2;

	/* 2T2R TP issue */
	अगर (rtlphy->rf_type == RF_2T2R)
		वापस;

	अगर (!rtlpriv->dm.dynamic_txघातer_enable ||
	    rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TX_HIGHPWR_LEVEL_NORMAL;
		वापस;
	पूर्ण

	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"Not connected to any\n");

		rtlpriv->dm.dynamic_txhighघातer_lvl = TX_HIGHPWR_LEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TX_HIGHPWR_LEVEL_NORMAL;
		वापस;
	पूर्ण

	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण अन्यथा अणु
			undec_sm_pwdb = rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"STA Default Port PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण
	पूर्ण अन्यथा अणु
		undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;

		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"AP Ext Port PWDB = 0x%lx\n",
			undec_sm_pwdb);
	पूर्ण

	txpwr_threshold_lv2 = TX_POWER_NEAR_FIELD_THRESH_LVL2;
	txpwr_threshold_lv1 = TX_POWER_NEAR_FIELD_THRESH_LVL1;

	अगर (rtl_get_bbreg(hw, 0xc90, MASKBYTE0) == 1)
		rtlpriv->dm.dynamic_txhighघातer_lvl = TX_HIGHPWR_LEVEL_NORMAL;
	अन्यथा अगर (undec_sm_pwdb >= txpwr_threshold_lv2)
		rtlpriv->dm.dynamic_txhighघातer_lvl = TX_HIGHPWR_LEVEL_NORMAL2;
	अन्यथा अगर ((undec_sm_pwdb < (txpwr_threshold_lv2 - 3)) &&
		(undec_sm_pwdb >= txpwr_threshold_lv1))
		rtlpriv->dm.dynamic_txhighघातer_lvl = TX_HIGHPWR_LEVEL_NORMAL1;
	अन्यथा अगर (undec_sm_pwdb < (txpwr_threshold_lv1 - 3))
		rtlpriv->dm.dynamic_txhighघातer_lvl = TX_HIGHPWR_LEVEL_NORMAL;

	अगर ((rtlpriv->dm.dynamic_txhighघातer_lvl != rtlpriv->dm.last_dtp_lvl))
		rtl92s_phy_set_txघातer(hw, rtlphy->current_channel);

	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighघातer_lvl;
पूर्ण

अटल व्योम _rtl92s_dm_init_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *digtable = &rtlpriv->dm_digtable;

	/* Disable DIG scheme now.*/
	digtable->dig_enable_flag = true;
	digtable->backoff_enable_flag = true;

	अगर ((rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER) &&
	    (hal_get_firmwareversion(rtlpriv) >= 0x3c))
		digtable->dig_algorithm = DIG_ALGO_BY_TOW_PORT;
	अन्यथा
		digtable->dig_algorithm =
			 DIG_ALGO_BEFORE_CONNECT_BY_RSSI_AND_ALARM;

	digtable->dig_twoport_algorithm = DIG_TWO_PORT_ALGO_RSSI;
	digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
	/* off=by real rssi value, on=by digtable->rssi_val क्रम new dig */
	digtable->dig_dbgmode = DM_DBG_OFF;
	digtable->dig_slgorithm_चयन = 0;

	/* 2007/10/04 MH Define init gain threshol. */
	digtable->dig_state = DM_STA_DIG_MAX;
	digtable->dig_highpwrstate = DM_STA_DIG_MAX;

	digtable->cur_sta_cstate = DIG_STA_DISCONNECT;
	digtable->pre_sta_cstate = DIG_STA_DISCONNECT;
	digtable->cur_ap_cstate = DIG_AP_DISCONNECT;
	digtable->pre_ap_cstate = DIG_AP_DISCONNECT;

	digtable->rssi_lowthresh = DM_DIG_THRESH_LOW;
	digtable->rssi_highthresh = DM_DIG_THRESH_HIGH;

	digtable->fa_lowthresh = DM_FALSEALARM_THRESH_LOW;
	digtable->fa_highthresh = DM_FALSEALARM_THRESH_HIGH;

	digtable->rssi_highघातer_lowthresh = DM_DIG_HIGH_PWR_THRESH_LOW;
	digtable->rssi_highघातer_highthresh = DM_DIG_HIGH_PWR_THRESH_HIGH;

	/* क्रम dig debug rssi value */
	digtable->rssi_val = 50;
	digtable->back_val = DM_DIG_BACKOFF_MAX;
	digtable->rx_gain_max = DM_DIG_MAX;

	digtable->rx_gain_min = DM_DIG_MIN;

	digtable->backoffval_range_max = DM_DIG_BACKOFF_MAX;
	digtable->backoffval_range_min = DM_DIG_BACKOFF_MIN;
पूर्ण

अटल व्योम _rtl92s_dm_init_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर ((hal_get_firmwareversion(rtlpriv) >= 60) &&
	    (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER))
		rtlpriv->dm.dynamic_txघातer_enable = true;
	अन्यथा
		rtlpriv->dm.dynamic_txघातer_enable = false;

	rtlpriv->dm.last_dtp_lvl = TX_HIGHPWR_LEVEL_NORMAL;
	rtlpriv->dm.dynamic_txhighघातer_lvl = TX_HIGHPWR_LEVEL_NORMAL;
पूर्ण

व्योम rtl92s_dm_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtlpriv->dm.undec_sm_pwdb = -1;

	_rtl92s_dm_init_dynamic_txघातer(hw);
	rtl92s_dm_init_edca_turbo(hw);
	_rtl92s_dm_init_rate_adaptive_mask(hw);
	_rtl92s_dm_init_txघातertracking_thermalmeter(hw);
	_rtl92s_dm_init_dig(hw);

	rtl_ग_लिखो_dword(rtlpriv, WFM5, FW_CCA_CHK_ENABLE);
पूर्ण

व्योम rtl92s_dm_watchकरोg(काष्ठा ieee80211_hw *hw)
अणु
	_rtl92s_dm_check_edca_turbo(hw);
	_rtl92s_dm_check_txघातertracking_thermalmeter(hw);
	_rtl92s_dm_ctrl_initgain_byrssi(hw);
	_rtl92s_dm_dynamic_txघातer(hw);
	_rtl92s_dm_refresh_rateadaptive_mask(hw);
	_rtl92s_dm_चयन_baseband_mrc(hw);
पूर्ण

