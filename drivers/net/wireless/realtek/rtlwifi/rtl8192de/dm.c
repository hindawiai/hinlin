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

#घोषणा UNDEC_SM_PWDB	entry_min_undec_sm_pwdb

अटल स्थिर u32 ofdmswing_table[OFDM_TABLE_SIZE_92D] = अणु
	0x7f8001fe,		/* 0, +6.0dB */
	0x788001e2,		/* 1, +5.5dB */
	0x71c001c7,		/* 2, +5.0dB */
	0x6b8001ae,		/* 3, +4.5dB */
	0x65400195,		/* 4, +4.0dB */
	0x5fc0017f,		/* 5, +3.5dB */
	0x5a400169,		/* 6, +3.0dB */
	0x55400155,		/* 7, +2.5dB */
	0x50800142,		/* 8, +2.0dB */
	0x4c000130,		/* 9, +1.5dB */
	0x47c0011f,		/* 10, +1.0dB */
	0x43c0010f,		/* 11, +0.5dB */
	0x40000100,		/* 12, +0dB */
	0x3c8000f2,		/* 13, -0.5dB */
	0x390000e4,		/* 14, -1.0dB */
	0x35c000d7,		/* 15, -1.5dB */
	0x32c000cb,		/* 16, -2.0dB */
	0x300000c0,		/* 17, -2.5dB */
	0x2d4000b5,		/* 18, -3.0dB */
	0x2ac000ab,		/* 19, -3.5dB */
	0x288000a2,		/* 20, -4.0dB */
	0x26000098,		/* 21, -4.5dB */
	0x24000090,		/* 22, -5.0dB */
	0x22000088,		/* 23, -5.5dB */
	0x20000080,		/* 24, -6.0dB */
	0x1e400079,		/* 25, -6.5dB */
	0x1c800072,		/* 26, -7.0dB */
	0x1b00006c,		/* 27. -7.5dB */
	0x19800066,		/* 28, -8.0dB */
	0x18000060,		/* 29, -8.5dB */
	0x16c0005b,		/* 30, -9.0dB */
	0x15800056,		/* 31, -9.5dB */
	0x14400051,		/* 32, -10.0dB */
	0x1300004c,		/* 33, -10.5dB */
	0x12000048,		/* 34, -11.0dB */
	0x11000044,		/* 35, -11.5dB */
	0x10000040,		/* 36, -12.0dB */
	0x0f00003c,		/* 37, -12.5dB */
	0x0e400039,		/* 38, -13.0dB */
	0x0d800036,		/* 39, -13.5dB */
	0x0cc00033,		/* 40, -14.0dB */
	0x0c000030,		/* 41, -14.5dB */
	0x0b40002d,		/* 42, -15.0dB */
पूर्ण;

अटल स्थिर u8 cckswing_table_ch1ch13[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण,    /* 0, +0dB */
	अणु0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04पूर्ण,    /* 1, -0.5dB */
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण,    /* 2, -1.0dB */
	अणु0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03पूर्ण,    /* 3, -1.5dB */
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण,    /* 4, -2.0dB */
	अणु0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03पूर्ण,    /* 5, -2.5dB */
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण,    /* 6, -3.0dB */
	अणु0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03पूर्ण,    /* 7, -3.5dB */
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण,    /* 8, -4.0dB */
	अणु0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02पूर्ण,    /* 9, -4.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण,    /* 10, -5.0dB */
	अणु0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02पूर्ण,    /* 11, -5.5dB */
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण,    /* 12, -6.0dB */
	अणु0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02पूर्ण,    /* 13, -6.5dB */
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण,    /* 14, -7.0dB */
	अणु0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02पूर्ण,    /* 15, -7.5dB */
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण,    /* 16, -8.0dB */
	अणु0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02पूर्ण,    /* 17, -8.5dB */
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण,    /* 18, -9.0dB */
	अणु0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,    /* 19, -9.5dB */
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,    /* 20, -10.0dB */
	अणु0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण,    /* 21, -10.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण,    /* 22, -11.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01पूर्ण,    /* 23, -11.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01पूर्ण,    /* 24, -12.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01पूर्ण,    /* 25, -12.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01पूर्ण,    /* 26, -13.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण,    /* 27, -13.5dB */
	अणु0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण,    /* 28, -14.0dB */
	अणु0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण,    /* 29, -14.5dB */
	अणु0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण,    /* 30, -15.0dB */
	अणु0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01पूर्ण,    /* 31, -15.5dB */
	अणु0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01पूर्ण     /* 32, -16.0dB */
पूर्ण;

अटल स्थिर u8 cckswing_table_ch14[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 0, +0dB */
	अणु0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 1, -0.5dB */
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 2, -1.0dB */
	अणु0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 3, -1.5dB */
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 4, -2.0dB */
	अणु0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 5, -2.5dB */
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 6, -3.0dB */
	अणु0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 7, -3.5dB */
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 8, -4.0dB */
	अणु0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 9, -4.5dB */
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 10, -5.0dB */
	अणु0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 11, -5.5dB */
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 12, -6.0dB */
	अणु0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 13, -6.5dB */
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 14, -7.0dB */
	अणु0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 15, -7.5dB */
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 16, -8.0dB */
	अणु0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 17, -8.5dB */
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 18, -9.0dB */
	अणु0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 19, -9.5dB */
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 20, -10.0dB */
	अणु0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 21, -10.5dB */
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 22, -11.0dB */
	अणु0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 23, -11.5dB */
	अणु0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 24, -12.0dB */
	अणु0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 25, -12.5dB */
	अणु0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 26, -13.0dB */
	अणु0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 27, -13.5dB */
	अणु0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 28, -14.0dB */
	अणु0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 29, -14.5dB */
	अणु0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 30, -15.0dB */
	अणु0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,    /* 31, -15.5dB */
	अणु0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00पूर्ण     /* 32, -16.0dB */
पूर्ण;

अटल व्योम rtl92d_dm_false_alarm_counter_statistics(काष्ठा ieee80211_hw *hw)
अणु
	u32 ret_value;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);
	अचिन्हित दीर्घ flag = 0;

	/* hold ofdm counter */
	rtl_set_bbreg(hw, ROFDM0_LSTF, BIT(31), 1); /* hold page C counter */
	rtl_set_bbreg(hw, ROFDM1_LSTF, BIT(31), 1); /*hold page D counter */

	ret_value = rtl_get_bbreg(hw, ROFDM0_FRAMESYNC, MASKDWORD);
	falsealm_cnt->cnt_fast_fsync_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_sb_search_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER1, MASKDWORD);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER2, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);
	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER3, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
				      falsealm_cnt->cnt_rate_illegal +
				      falsealm_cnt->cnt_crc8_fail +
				      falsealm_cnt->cnt_mcs_fail +
				      falsealm_cnt->cnt_fast_fsync_fail +
				      falsealm_cnt->cnt_sb_search_fail;

	अगर (rtlpriv->rtlhal.current_bandtype != BAND_ON_5G) अणु
		/* hold cck counter */
		rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
		ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERLOWER, MASKBYTE0);
		falsealm_cnt->cnt_cck_fail = ret_value;
		ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERUPPER, MASKBYTE3);
		falsealm_cnt->cnt_cck_fail += (ret_value & 0xff) << 8;
		rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
	पूर्ण अन्यथा अणु
		falsealm_cnt->cnt_cck_fail = 0;
	पूर्ण

	/* reset false alarm counter रेजिस्टरs */
	falsealm_cnt->cnt_all = falsealm_cnt->cnt_fast_fsync_fail +
				falsealm_cnt->cnt_sb_search_fail +
				falsealm_cnt->cnt_parity_fail +
				falsealm_cnt->cnt_rate_illegal +
				falsealm_cnt->cnt_crc8_fail +
				falsealm_cnt->cnt_mcs_fail +
				falsealm_cnt->cnt_cck_fail;

	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 1);
	/* update ofdm counter */
	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 0);
	/* update page C counter */
	rtl_set_bbreg(hw, ROFDM0_LSTF, BIT(31), 0);
	/* update page D counter */
	rtl_set_bbreg(hw, ROFDM1_LSTF, BIT(31), 0);
	अगर (rtlpriv->rtlhal.current_bandtype != BAND_ON_5G) अणु
		/* reset cck counter */
		rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
		rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 0);
		/* enable cck counter */
		rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 2);
		rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"Cnt_Fast_Fsync_fail = %x, Cnt_SB_Search_fail = %x\n",
		falsealm_cnt->cnt_fast_fsync_fail,
		falsealm_cnt->cnt_sb_search_fail);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"Cnt_Parity_Fail = %x, Cnt_Rate_Illegal = %x, Cnt_Crc8_fail = %x, Cnt_Mcs_fail = %x\n",
		falsealm_cnt->cnt_parity_fail,
		falsealm_cnt->cnt_rate_illegal,
		falsealm_cnt->cnt_crc8_fail,
		falsealm_cnt->cnt_mcs_fail);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"Cnt_Ofdm_fail = %x, Cnt_Cck_fail = %x, Cnt_all = %x\n",
		falsealm_cnt->cnt_ofdm_fail,
		falsealm_cnt->cnt_cck_fail,
		falsealm_cnt->cnt_all);
पूर्ण

अटल व्योम rtl92d_dm_find_minimum_rssi(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *de_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtlpriv);

	/* Determine the minimum RSSI  */
	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.UNDEC_SM_PWDB == 0)) अणु
		de_digtable->min_undec_pwdb_क्रम_dm = 0;
		rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
			"Not connected to any\n");
	पूर्ण
	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_AP ||
		    mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			de_digtable->min_undec_pwdb_क्रम_dm =
			    rtlpriv->dm.UNDEC_SM_PWDB;
			rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				 rtlpriv->dm.UNDEC_SM_PWDB);
		पूर्ण अन्यथा अणु
			de_digtable->min_undec_pwdb_क्रम_dm =
			    rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
				"STA Default Port PWDB = 0x%x\n",
				de_digtable->min_undec_pwdb_क्रम_dm);
		पूर्ण
	पूर्ण अन्यथा अणु
		de_digtable->min_undec_pwdb_क्रम_dm = rtlpriv->dm.UNDEC_SM_PWDB;
		rtl_dbg(rtlpriv, COMP_BB_POWERSAVING, DBG_LOUD,
			"AP Ext Port or disconnect PWDB = 0x%x\n",
			de_digtable->min_undec_pwdb_क्रम_dm);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "MinUndecoratedPWDBForDM =%d\n",
		de_digtable->min_undec_pwdb_क्रम_dm);
पूर्ण

अटल व्योम rtl92d_dm_cck_packet_detection_thresh(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *de_digtable = &rtlpriv->dm_digtable;
	अचिन्हित दीर्घ flag = 0;

	अगर (de_digtable->cursta_cstate == DIG_STA_CONNECT) अणु
		अगर (de_digtable->pre_cck_pd_state == CCK_PD_STAGE_LOWRSSI) अणु
			अगर (de_digtable->min_undec_pwdb_क्रम_dm <= 25)
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_LOWRSSI;
			अन्यथा
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_HIGHRSSI;
		पूर्ण अन्यथा अणु
			अगर (de_digtable->min_undec_pwdb_क्रम_dm <= 20)
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_LOWRSSI;
			अन्यथा
				de_digtable->cur_cck_pd_state =
							 CCK_PD_STAGE_HIGHRSSI;
		पूर्ण
	पूर्ण अन्यथा अणु
		de_digtable->cur_cck_pd_state = CCK_PD_STAGE_LOWRSSI;
	पूर्ण
	अगर (de_digtable->pre_cck_pd_state != de_digtable->cur_cck_pd_state) अणु
		अगर (de_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI) अणु
			rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x83);
			rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
		पूर्ण अन्यथा अणु
			rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);
			rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
		पूर्ण
		de_digtable->pre_cck_pd_state = de_digtable->cur_cck_pd_state;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "CurSTAConnectState=%s\n",
		de_digtable->cursta_cstate == DIG_STA_CONNECT ?
		"DIG_STA_CONNECT " : "DIG_STA_DISCONNECT");
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "CCKPDStage=%s\n",
		de_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI ?
		"Low RSSI " : "High RSSI ");
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "is92d single phy =%x\n",
		IS_92D_SINGLEPHY(rtlpriv->rtlhal.version));

पूर्ण

व्योम rtl92d_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *de_digtable = &rtlpriv->dm_digtable;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"cur_igvalue = 0x%x, pre_igvalue = 0x%x, back_val = %d\n",
		de_digtable->cur_igvalue, de_digtable->pre_igvalue,
		de_digtable->back_val);
	अगर (de_digtable->dig_enable_flag == false) अणु
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "DIG is disabled\n");
		de_digtable->pre_igvalue = 0x17;
		वापस;
	पूर्ण
	अगर (de_digtable->pre_igvalue != de_digtable->cur_igvalue) अणु
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f,
			      de_digtable->cur_igvalue);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, 0x7f,
			      de_digtable->cur_igvalue);
		de_digtable->pre_igvalue = de_digtable->cur_igvalue;
	पूर्ण
पूर्ण

अटल व्योम rtl92d_early_mode_enabled(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा dig_t *de_digtable = &rtlpriv->dm_digtable;

	अगर ((rtlpriv->mac80211.link_state >= MAC80211_LINKED) &&
	    (rtlpriv->mac80211.venकरोr == PEER_CISCO)) अणु
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "IOT_PEER = CISCO\n");
		अगर (de_digtable->last_min_undec_pwdb_क्रम_dm >= 50
		    && de_digtable->min_undec_pwdb_क्रम_dm < 50) अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_EARLY_MODE_CONTROL, 0x00);
			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"Early Mode Off\n");
		पूर्ण अन्यथा अगर (de_digtable->last_min_undec_pwdb_क्रम_dm <= 55 &&
			   de_digtable->min_undec_pwdb_क्रम_dm > 55) अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_EARLY_MODE_CONTROL, 0x0f);
			rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
				"Early Mode On\n");
		पूर्ण
	पूर्ण अन्यथा अगर (!(rtl_पढ़ो_byte(rtlpriv, REG_EARLY_MODE_CONTROL) & 0xf)) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_EARLY_MODE_CONTROL, 0x0f);
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "Early Mode On\n");
	पूर्ण
पूर्ण

अटल व्योम rtl92d_dm_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *de_digtable = &rtlpriv->dm_digtable;
	u8 value_igi = de_digtable->cur_igvalue;
	काष्ठा false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "==>\n");
	अगर (rtlpriv->rtlhal.earlymode_enable) अणु
		rtl92d_early_mode_enabled(rtlpriv);
		de_digtable->last_min_undec_pwdb_क्रम_dm =
				 de_digtable->min_undec_pwdb_क्रम_dm;
	पूर्ण
	अगर (!rtlpriv->dm.dm_initialgain_enable)
		वापस;

	/* because we will send data pkt when scanning
	 * this will cause some ap like gear-3700 wep TP
	 * lower अगर we वापस here, this is the dअगरf of
	 * mac80211 driver vs ieee80211 driver */
	/* अगर (rtlpriv->mac80211.act_scanning)
	 *      वापस; */

	/* Not STA mode वापस पंचांगp */
	अगर (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		वापस;
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "progress\n");
	/* Decide the current status and अगर modअगरy initial gain or not */
	अगर (rtlpriv->mac80211.link_state >= MAC80211_LINKED)
		de_digtable->cursta_cstate = DIG_STA_CONNECT;
	अन्यथा
		de_digtable->cursta_cstate = DIG_STA_DISCONNECT;

	/* adjust initial gain according to false alarm counter */
	अगर (falsealm_cnt->cnt_all < DM_DIG_FA_TH0)
		value_igi--;
	अन्यथा अगर (falsealm_cnt->cnt_all < DM_DIG_FA_TH1)
		value_igi += 0;
	अन्यथा अगर (falsealm_cnt->cnt_all < DM_DIG_FA_TH2)
		value_igi++;
	अन्यथा अगर (falsealm_cnt->cnt_all >= DM_DIG_FA_TH2)
		value_igi += 2;
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"dm_DIG() Before: large_fa_hit=%d, forbidden_igi=%x\n",
		de_digtable->large_fa_hit, de_digtable->क्रमbidden_igi);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"dm_DIG() Before: Recover_cnt=%d, rx_gain_min=%x\n",
		de_digtable->recover_cnt, de_digtable->rx_gain_min);

	/* deal with abnormally large false alarm */
	अगर (falsealm_cnt->cnt_all > 10000) अणु
		rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
			"dm_DIG(): Abnormally false alarm case\n");

		de_digtable->large_fa_hit++;
		अगर (de_digtable->क्रमbidden_igi < de_digtable->cur_igvalue) अणु
			de_digtable->क्रमbidden_igi = de_digtable->cur_igvalue;
			de_digtable->large_fa_hit = 1;
		पूर्ण
		अगर (de_digtable->large_fa_hit >= 3) अणु
			अगर ((de_digtable->क्रमbidden_igi + 1) > DM_DIG_MAX)
				de_digtable->rx_gain_min = DM_DIG_MAX;
			अन्यथा
				de_digtable->rx_gain_min =
				    (de_digtable->क्रमbidden_igi + 1);
			de_digtable->recover_cnt = 3600;	/* 3600=2hr */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Recovery mechanism क्रम IGI lower bound */
		अगर (de_digtable->recover_cnt != 0) अणु
			de_digtable->recover_cnt--;
		पूर्ण अन्यथा अणु
			अगर (de_digtable->large_fa_hit == 0) अणु
				अगर ((de_digtable->क्रमbidden_igi - 1) <
				    DM_DIG_FA_LOWER) अणु
					de_digtable->क्रमbidden_igi =
							 DM_DIG_FA_LOWER;
					de_digtable->rx_gain_min =
							 DM_DIG_FA_LOWER;

				पूर्ण अन्यथा अणु
					de_digtable->क्रमbidden_igi--;
					de_digtable->rx_gain_min =
					    (de_digtable->क्रमbidden_igi + 1);
				पूर्ण
			पूर्ण अन्यथा अगर (de_digtable->large_fa_hit == 3) अणु
				de_digtable->large_fa_hit = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"dm_DIG() After: large_fa_hit=%d, forbidden_igi=%x\n",
		de_digtable->large_fa_hit, de_digtable->क्रमbidden_igi);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"dm_DIG() After: recover_cnt=%d, rx_gain_min=%x\n",
		de_digtable->recover_cnt, de_digtable->rx_gain_min);

	अगर (value_igi > DM_DIG_MAX)
		value_igi = DM_DIG_MAX;
	अन्यथा अगर (value_igi < de_digtable->rx_gain_min)
		value_igi = de_digtable->rx_gain_min;
	de_digtable->cur_igvalue = value_igi;
	rtl92d_dm_ग_लिखो_dig(hw);
	अगर (rtlpriv->rtlhal.current_bandtype != BAND_ON_5G)
		rtl92d_dm_cck_packet_detection_thresh(hw);
	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD, "<<==\n");
पूर्ण

अटल व्योम rtl92d_dm_init_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dynamic_txघातer_enable = true;
	rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
	rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
पूर्ण

अटल व्योम rtl92d_dm_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ undec_sm_pwdb;

	अगर ((!rtlpriv->dm.dynamic_txघातer_enable)
	    || rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		वापस;
	पूर्ण
	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.UNDEC_SM_PWDB == 0)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"Not connected to any\n");
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
		वापस;
	पूर्ण
	अगर (mac->link_state >= MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			undec_sm_pwdb =
			    rtlpriv->dm.UNDEC_SM_PWDB;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"IBSS Client PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण अन्यथा अणु
			undec_sm_pwdb =
			    rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"STA Default Port PWDB = 0x%lx\n",
				undec_sm_pwdb);
		पूर्ण
	पूर्ण अन्यथा अणु
		undec_sm_pwdb =
		    rtlpriv->dm.UNDEC_SM_PWDB;

		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"AP Ext Port PWDB = 0x%lx\n",
			undec_sm_pwdb);
	पूर्ण
	अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
		अगर (undec_sm_pwdb >= 0x33) अणु
			rtlpriv->dm.dynamic_txhighघातer_lvl =
						 TXHIGHPWRLEVEL_LEVEL2;
			rtl_dbg(rtlpriv, COMP_HIPWR, DBG_LOUD,
				"5G:TxHighPwrLevel_Level2 (TxPwr=0x0)\n");
		पूर्ण अन्यथा अगर ((undec_sm_pwdb < 0x33)
			   && (undec_sm_pwdb >= 0x2b)) अणु
			rtlpriv->dm.dynamic_txhighघातer_lvl =
						 TXHIGHPWRLEVEL_LEVEL1;
			rtl_dbg(rtlpriv, COMP_HIPWR, DBG_LOUD,
				"5G:TxHighPwrLevel_Level1 (TxPwr=0x10)\n");
		पूर्ण अन्यथा अगर (undec_sm_pwdb < 0x2b) अणु
			rtlpriv->dm.dynamic_txhighघातer_lvl =
						 TXHIGHPWRLEVEL_NORMAL;
			rtl_dbg(rtlpriv, COMP_HIPWR, DBG_LOUD,
				"5G:TxHighPwrLevel_Normal\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (undec_sm_pwdb >=
		    TX_POWER_NEAR_FIELD_THRESH_LVL2) अणु
			rtlpriv->dm.dynamic_txhighघातer_lvl =
						 TXHIGHPWRLEVEL_LEVEL2;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n");
		पूर्ण अन्यथा
		    अगर ((undec_sm_pwdb <
			 (TX_POWER_NEAR_FIELD_THRESH_LVL2 - 3))
			&& (undec_sm_pwdb >=
			    TX_POWER_NEAR_FIELD_THRESH_LVL1)) अणु

			rtlpriv->dm.dynamic_txhighघातer_lvl =
						 TXHIGHPWRLEVEL_LEVEL1;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n");
		पूर्ण अन्यथा अगर (undec_sm_pwdb <
			   (TX_POWER_NEAR_FIELD_THRESH_LVL1 - 5)) अणु
			rtlpriv->dm.dynamic_txhighघातer_lvl =
						 TXHIGHPWRLEVEL_NORMAL;
			rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
				"TXHIGHPWRLEVEL_NORMAL\n");
		पूर्ण
	पूर्ण
	अगर ((rtlpriv->dm.dynamic_txhighघातer_lvl != rtlpriv->dm.last_dtp_lvl)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"PHY_SetTxPowerLevel8192S() Channel = %d\n",
			rtlphy->current_channel);
		rtl92d_phy_set_txघातer_level(hw, rtlphy->current_channel);
	पूर्ण
	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighघातer_lvl;
पूर्ण

अटल व्योम rtl92d_dm_pwdb_monitor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* AP & ADHOC & MESH will वापस पंचांगp */
	अगर (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		वापस;
	/* Indicate Rx संकेत strength to FW. */
	अगर (rtlpriv->dm.useramask) अणु
		u32 temp = rtlpriv->dm.undec_sm_pwdb;

		temp <<= 16;
		temp |= 0x100;
		/* fw v12 cmdid 5:use max macid ,क्रम nic ,
		 * शेष macid is 0 ,max macid is 1 */
		rtl92d_fill_h2c_cmd(hw, H2C_RSSI_REPORT, 3, (u8 *) (&temp));
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, 0x4fe,
			       (u8) rtlpriv->dm.undec_sm_pwdb);
	पूर्ण
पूर्ण

व्योम rtl92d_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.current_turbo_edca = false;
	rtlpriv->dm.is_any_nonbepkts = false;
	rtlpriv->dm.is_cur_rdlstate = false;
पूर्ण

अटल व्योम rtl92d_dm_check_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	अटल u64 last_txok_cnt;
	अटल u64 last_rxok_cnt;
	u64 cur_txok_cnt;
	u64 cur_rxok_cnt;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b;

	अगर (mac->link_state != MAC80211_LINKED) अणु
		rtlpriv->dm.current_turbo_edca = false;
		जाओ निकास;
	पूर्ण

	/* Enable BEQ TxOP limit configuration in wireless G-mode. */
	/* To check whether we shall क्रमce turn on TXOP configuration. */
	अगर ((!rtlpriv->dm.disable_framebursting) &&
	    (rtlpriv->sec.pairwise_enc_algorithm == WEP40_ENCRYPTION ||
	    rtlpriv->sec.pairwise_enc_algorithm == WEP104_ENCRYPTION ||
	    rtlpriv->sec.pairwise_enc_algorithm == TKIP_ENCRYPTION)) अणु
		/* Force TxOP limit to 0x005e क्रम UL. */
		अगर (!(edca_be_ul & 0xffff0000))
			edca_be_ul |= 0x005e0000;
		/* Force TxOP limit to 0x005e क्रम DL. */
		अगर (!(edca_be_dl & 0xffff0000))
			edca_be_dl |= 0x005e0000;
	पूर्ण

	अगर ((!rtlpriv->dm.is_any_nonbepkts) &&
	    (!rtlpriv->dm.disable_framebursting)) अणु
		cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
		cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;
		अगर (cur_rxok_cnt > 4 * cur_txok_cnt) अणु
			अगर (!rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BE_PARAM,
						edca_be_dl);
				rtlpriv->dm.is_cur_rdlstate = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) अणु
				rtl_ग_लिखो_dword(rtlpriv, REG_EDCA_BE_PARAM,
						edca_be_ul);
				rtlpriv->dm.is_cur_rdlstate = false;
			पूर्ण
		पूर्ण
		rtlpriv->dm.current_turbo_edca = true;
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->dm.current_turbo_edca) अणु
			u8 पंचांगp = AC0_BE;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AC_PARAM,
						      &पंचांगp);
			rtlpriv->dm.current_turbo_edca = false;
		पूर्ण
	पूर्ण

निकास:
	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
पूर्ण

अटल व्योम rtl92d_dm_rxgain_tracking_thermalmeter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 index_mapping[RX_INDEX_MAPPING_NUM] = अणु
		0x0f, 0x0f, 0x0d, 0x0c, 0x0b,
		0x0a, 0x09, 0x08, 0x07, 0x06,
		0x05, 0x04, 0x04, 0x03, 0x02
	पूर्ण;
	पूर्णांक i;
	u32 u4पंचांगp;

	u4पंचांगp = (index_mapping[(rtlpriv->efuse.eeprom_thermalmeter -
				rtlpriv->dm.thermalvalue_rxgain)]) << 12;
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"===> Rx Gain %x\n", u4पंचांगp);
	क्रम (i = RF90_PATH_A; i < rtlpriv->phy.num_total_rfpath; i++)
		rtl_set_rfreg(hw, i, 0x3C, RFREG_OFFSET_MASK,
			      (rtlpriv->phy.reg_rf3c[i] & (~(0xF000))) | u4पंचांगp);
पूर्ण

अटल व्योम rtl92d_bandtype_2_4G(काष्ठा ieee80211_hw *hw, दीर्घ *temp_cckg,
				 u8 *cck_index_old)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;
	अचिन्हित दीर्घ flag = 0;
	दीर्घ temp_cck;
	स्थिर u8 *cckswing;

	/* Query CCK शेष setting From 0xa24 */
	rtl92d_acquire_cckandrw_pagea_ctl(hw, &flag);
	temp_cck = rtl_get_bbreg(hw, RCCK0_TXFILTER2,
				 MASKDWORD) & MASKCCK;
	rtl92d_release_cckandrw_pagea_ctl(hw, &flag);
	क्रम (i = 0; i < CCK_TABLE_LENGTH; i++) अणु
		अगर (rtlpriv->dm.cck_inch14)
			cckswing = &cckswing_table_ch14[i][2];
		अन्यथा
			cckswing = &cckswing_table_ch1ch13[i][2];

		अगर (temp_cck == le32_to_cpu(*((__le32 *)cckswing))) अणु
			*cck_index_old = (u8)i;
			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Initial reg0x%x = 0x%lx, cck_index = 0x%x, ch14 %d\n",
				RCCK0_TXFILTER2, temp_cck,
				*cck_index_old,
				rtlpriv->dm.cck_inch14);
			अवरोध;
		पूर्ण
	पूर्ण
	*temp_cckg = temp_cck;
पूर्ण

अटल व्योम rtl92d_bandtype_5G(काष्ठा rtl_hal *rtlhal, u8 *ofdm_index,
			       bool *पूर्णांकernal_pa, u8 thermalvalue, u8 delta,
			       u8 rf, काष्ठा rtl_efuse *rtlefuse,
			       काष्ठा rtl_priv *rtlpriv, काष्ठा rtl_phy *rtlphy,
			       स्थिर u8 index_mapping[5][INDEX_MAPPING_NUM],
			       स्थिर u8 index_mapping_pa[8][INDEX_MAPPING_NUM])
अणु
	पूर्णांक i;
	u8 index;
	u8 offset = 0;

	क्रम (i = 0; i < rf; i++) अणु
		अगर (rtlhal->macphymode == DUALMAC_DUALPHY &&
		    rtlhal->पूर्णांकerfaceindex == 1)	/* MAC 1 5G */
			*पूर्णांकernal_pa = rtlefuse->पूर्णांकernal_pa_5g[1];
		अन्यथा
			*पूर्णांकernal_pa = rtlefuse->पूर्णांकernal_pa_5g[i];
		अगर (*पूर्णांकernal_pa) अणु
			अगर (rtlhal->पूर्णांकerfaceindex == 1 || i == rf)
				offset = 4;
			अन्यथा
				offset = 0;
			अगर (rtlphy->current_channel >= 100 &&
				rtlphy->current_channel <= 165)
				offset += 2;
		पूर्ण अन्यथा अणु
			अगर (rtlhal->पूर्णांकerfaceindex == 1 || i == rf)
				offset = 2;
			अन्यथा
				offset = 0;
		पूर्ण
		अगर (thermalvalue > rtlefuse->eeprom_thermalmeter)
			offset++;
		अगर (*पूर्णांकernal_pa) अणु
			अगर (delta > INDEX_MAPPING_NUM - 1)
				index = index_mapping_pa[offset]
						    [INDEX_MAPPING_NUM - 1];
			अन्यथा
				index =
				     index_mapping_pa[offset][delta];
		पूर्ण अन्यथा अणु
			अगर (delta > INDEX_MAPPING_NUM - 1)
				index =
				   index_mapping[offset][INDEX_MAPPING_NUM - 1];
			अन्यथा
				index = index_mapping[offset][delta];
		पूर्ण
		अगर (thermalvalue > rtlefuse->eeprom_thermalmeter) अणु
			अगर (*पूर्णांकernal_pa && thermalvalue > 0x12) अणु
				ofdm_index[i] = rtlpriv->dm.ofdm_index[i] -
						((delta / 2) * 3 + (delta % 2));
			पूर्ण अन्यथा अणु
				ofdm_index[i] -= index;
			पूर्ण
		पूर्ण अन्यथा अणु
			ofdm_index[i] += index;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rtl92d_dm_txघातer_tracking_callback_thermalmeter(
			काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 thermalvalue, delta, delta_lck, delta_iqk, delta_rxgain;
	u8 offset, thermalvalue_avg_count = 0;
	u32 thermalvalue_avg = 0;
	bool पूर्णांकernal_pa = false;
	दीर्घ ele_a = 0, ele_d, temp_cck, val_x, value32;
	दीर्घ val_y, ele_c = 0;
	u8 ofdm_index[2];
	s8 cck_index = 0;
	u8 ofdm_index_old[2] = अणु0, 0पूर्ण;
	s8 cck_index_old = 0;
	u8 index;
	पूर्णांक i;
	bool is2t = IS_92D_SINGLEPHY(rtlhal->version);
	u8 ofdm_min_index = 6, ofdm_min_index_पूर्णांकernal_pa = 3, rf;
	u8 indexक्रमchannel =
	    rtl92d_get_rightchnlplace_क्रम_iqk(rtlphy->current_channel);
	अटल स्थिर u8 index_mapping[5][INDEX_MAPPING_NUM] = अणु
		/* 5G, path A/MAC 0, decrease घातer  */
		अणु0, 1, 3, 6, 8, 9,	11, 13, 14, 16, 17, 18, 18पूर्ण,
		/* 5G, path A/MAC 0, increase घातer  */
		अणु0, 2, 4, 5, 7, 10,	12, 14, 16, 18, 18, 18, 18पूर्ण,
		/* 5G, path B/MAC 1, decrease घातer */
		अणु0, 2, 3, 6, 8, 9,	11, 13, 14, 16, 17, 18, 18पूर्ण,
		/* 5G, path B/MAC 1, increase घातer */
		अणु0, 2, 4, 5, 7, 10,	13, 16, 16, 18, 18, 18, 18पूर्ण,
		/* 2.4G, क्रम decreas घातer */
		अणु0, 1, 2, 3, 4, 5,	6, 7, 7, 8, 9, 10, 10पूर्ण,
	पूर्ण;
	अटल स्थिर u8 index_mapping_पूर्णांकernal_pa[8][INDEX_MAPPING_NUM] = अणु
		/* 5G, path A/MAC 0, ch36-64, decrease घातer  */
		अणु0, 1, 2, 4, 6, 7,	9, 11, 12, 14, 15, 16, 16पूर्ण,
		/* 5G, path A/MAC 0, ch36-64, increase घातer  */
		अणु0, 2, 4, 5, 7, 10,	12, 14, 16, 18, 18, 18, 18पूर्ण,
		/* 5G, path A/MAC 0, ch100-165, decrease घातer  */
		अणु0, 1, 2, 3, 5, 6,	8, 10, 11, 13, 14, 15, 15पूर्ण,
		/* 5G, path A/MAC 0, ch100-165, increase घातer  */
		अणु0, 2, 4, 5, 7, 10,	12, 14, 16, 18, 18, 18, 18पूर्ण,
		/* 5G, path B/MAC 1, ch36-64, decrease घातer */
		अणु0, 1, 2, 4, 6, 7,	9, 11, 12, 14, 15, 16, 16पूर्ण,
		/* 5G, path B/MAC 1, ch36-64, increase घातer */
		अणु0, 2, 4, 5, 7, 10,	13, 16, 16, 18, 18, 18, 18पूर्ण,
		/* 5G, path B/MAC 1, ch100-165, decrease घातer */
		अणु0, 1, 2, 3, 5, 6,	8, 9, 10, 12, 13, 14, 14पूर्ण,
		/* 5G, path B/MAC 1, ch100-165, increase घातer */
		अणु0, 2, 4, 5, 7, 10,	13, 16, 16, 18, 18, 18, 18पूर्ण,
	पूर्ण;

	rtlpriv->dm.txघातer_trackinginit = true;
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD, "\n");
	thermalvalue = (u8) rtl_get_rfreg(hw, RF90_PATH_A, RF_T_METER, 0xf800);
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"Readback Thermal Meter = 0x%x pre thermal meter 0x%x eeprom_thermalmeter 0x%x\n",
		thermalvalue,
		rtlpriv->dm.thermalvalue, rtlefuse->eeprom_thermalmeter);
	rtl92d_phy_ap_calibrate(hw, (thermalvalue -
				     rtlefuse->eeprom_thermalmeter));

	अगर (!thermalvalue)
		जाओ निकास;

	अगर (is2t)
		rf = 2;
	अन्यथा
		rf = 1;

	अगर (rtlpriv->dm.thermalvalue && !rtlhal->reloadtxघातerindex)
		जाओ old_index_करोne;

	ele_d = rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,  MASKDWORD) & MASKOFDM_D;
	क्रम (i = 0; i < OFDM_TABLE_SIZE_92D; i++) अणु
		अगर (ele_d == (ofdmswing_table[i] & MASKOFDM_D)) अणु
			ofdm_index_old[0] = (u8)i;

			rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				"Initial pathA ele_d reg0x%x = 0x%lx, ofdm_index=0x%x\n",
				ROFDM0_XATXIQIMBALANCE,
				ele_d, ofdm_index_old[0]);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (is2t) अणु
		ele_d = rtl_get_bbreg(hw, ROFDM0_XBTXIQIMBALANCE,
				      MASKDWORD) & MASKOFDM_D;
		क्रम (i = 0; i < OFDM_TABLE_SIZE_92D; i++) अणु
			अगर (ele_d ==
			    (ofdmswing_table[i] & MASKOFDM_D)) अणु
				ofdm_index_old[1] = (u8)i;
				rtl_dbg(rtlpriv, COMP_POWER_TRACKING,
					DBG_LOUD,
					"Initial pathB ele_d reg 0x%x = 0x%lx, ofdm_index = 0x%x\n",
					ROFDM0_XBTXIQIMBALANCE, ele_d,
					ofdm_index_old[1]);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		rtl92d_bandtype_2_4G(hw, &temp_cck, &cck_index_old);
	पूर्ण अन्यथा अणु
		temp_cck = 0x090e1317;
		cck_index_old = 12;
	पूर्ण

	अगर (!rtlpriv->dm.thermalvalue) अणु
		rtlpriv->dm.thermalvalue = rtlefuse->eeprom_thermalmeter;
		rtlpriv->dm.thermalvalue_lck = thermalvalue;
		rtlpriv->dm.thermalvalue_iqk = thermalvalue;
		rtlpriv->dm.thermalvalue_rxgain = rtlefuse->eeprom_thermalmeter;
		क्रम (i = 0; i < rf; i++)
			rtlpriv->dm.ofdm_index[i] = ofdm_index_old[i];
		rtlpriv->dm.cck_index = cck_index_old;
	पूर्ण
	अगर (rtlhal->reloadtxघातerindex) अणु
		क्रम (i = 0; i < rf; i++)
			rtlpriv->dm.ofdm_index[i] = ofdm_index_old[i];
		rtlpriv->dm.cck_index = cck_index_old;
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"reload ofdm index for band switch\n");
	पूर्ण
old_index_करोne:
	क्रम (i = 0; i < rf; i++)
		ofdm_index[i] = rtlpriv->dm.ofdm_index[i];

	rtlpriv->dm.thermalvalue_avg
		    [rtlpriv->dm.thermalvalue_avg_index] = thermalvalue;
	rtlpriv->dm.thermalvalue_avg_index++;
	अगर (rtlpriv->dm.thermalvalue_avg_index == AVG_THERMAL_NUM)
		rtlpriv->dm.thermalvalue_avg_index = 0;
	क्रम (i = 0; i < AVG_THERMAL_NUM; i++) अणु
		अगर (rtlpriv->dm.thermalvalue_avg[i]) अणु
			thermalvalue_avg += rtlpriv->dm.thermalvalue_avg[i];
			thermalvalue_avg_count++;
		पूर्ण
	पूर्ण
	अगर (thermalvalue_avg_count)
		thermalvalue = (u8)(thermalvalue_avg / thermalvalue_avg_count);
	अगर (rtlhal->reloadtxघातerindex) अणु
		delta = (thermalvalue > rtlefuse->eeprom_thermalmeter) ?
		    (thermalvalue - rtlefuse->eeprom_thermalmeter) :
		    (rtlefuse->eeprom_thermalmeter - thermalvalue);
		rtlhal->reloadtxघातerindex = false;
		rtlpriv->dm.करोne_txघातer = false;
	पूर्ण अन्यथा अगर (rtlpriv->dm.करोne_txघातer) अणु
		delta = (thermalvalue > rtlpriv->dm.thermalvalue) ?
		    (thermalvalue - rtlpriv->dm.thermalvalue) :
		    (rtlpriv->dm.thermalvalue - thermalvalue);
	पूर्ण अन्यथा अणु
		delta = (thermalvalue > rtlefuse->eeprom_thermalmeter) ?
		    (thermalvalue - rtlefuse->eeprom_thermalmeter) :
		    (rtlefuse->eeprom_thermalmeter - thermalvalue);
	पूर्ण
	delta_lck = (thermalvalue > rtlpriv->dm.thermalvalue_lck) ?
	    (thermalvalue - rtlpriv->dm.thermalvalue_lck) :
	    (rtlpriv->dm.thermalvalue_lck - thermalvalue);
	delta_iqk = (thermalvalue > rtlpriv->dm.thermalvalue_iqk) ?
	    (thermalvalue - rtlpriv->dm.thermalvalue_iqk) :
	    (rtlpriv->dm.thermalvalue_iqk - thermalvalue);
	delta_rxgain =
		(thermalvalue > rtlpriv->dm.thermalvalue_rxgain) ?
		(thermalvalue - rtlpriv->dm.thermalvalue_rxgain) :
		(rtlpriv->dm.thermalvalue_rxgain - thermalvalue);
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"Readback Thermal Meter = 0x%x pre thermal meter 0x%x eeprom_thermalmeter 0x%x delta 0x%x delta_lck 0x%x delta_iqk 0x%x\n",
		thermalvalue, rtlpriv->dm.thermalvalue,
		rtlefuse->eeprom_thermalmeter, delta, delta_lck,
		delta_iqk);
	अगर (delta_lck > rtlefuse->delta_lck && rtlefuse->delta_lck != 0) अणु
		rtlpriv->dm.thermalvalue_lck = thermalvalue;
		rtl92d_phy_lc_calibrate(hw);
	पूर्ण

	अगर (delta == 0 || !rtlpriv->dm.txघातer_track_control)
		जाओ check_delta;

	rtlpriv->dm.करोne_txघातer = true;
	delta = (thermalvalue > rtlefuse->eeprom_thermalmeter) ?
	    (thermalvalue - rtlefuse->eeprom_thermalmeter) :
	    (rtlefuse->eeprom_thermalmeter - thermalvalue);
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		offset = 4;
		अगर (delta > INDEX_MAPPING_NUM - 1)
			index = index_mapping[offset][INDEX_MAPPING_NUM - 1];
		अन्यथा
			index = index_mapping[offset][delta];
		अगर (thermalvalue > rtlpriv->dm.thermalvalue) अणु
			क्रम (i = 0; i < rf; i++)
				ofdm_index[i] -= delta;
			cck_index -= delta;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < rf; i++)
				ofdm_index[i] += index;
			cck_index += index;
		पूर्ण
	पूर्ण अन्यथा अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
		rtl92d_bandtype_5G(rtlhal, ofdm_index,
				   &पूर्णांकernal_pa, thermalvalue,
				   delta, rf, rtlefuse, rtlpriv,
				   rtlphy, index_mapping,
				   index_mapping_पूर्णांकernal_pa);
	पूर्ण
	अगर (is2t) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"temp OFDM_A_index=0x%x, OFDM_B_index = 0x%x,cck_index=0x%x\n",
			rtlpriv->dm.ofdm_index[0],
			rtlpriv->dm.ofdm_index[1],
			rtlpriv->dm.cck_index);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"temp OFDM_A_index=0x%x,cck_index = 0x%x\n",
			rtlpriv->dm.ofdm_index[0],
			rtlpriv->dm.cck_index);
	पूर्ण
	क्रम (i = 0; i < rf; i++) अणु
		अगर (ofdm_index[i] > OFDM_TABLE_SIZE_92D - 1) अणु
			ofdm_index[i] = OFDM_TABLE_SIZE_92D - 1;
		पूर्ण अन्यथा अगर (पूर्णांकernal_pa ||
			   rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			अगर (ofdm_index[i] < ofdm_min_index_पूर्णांकernal_pa)
				ofdm_index[i] = ofdm_min_index_पूर्णांकernal_pa;
		पूर्ण अन्यथा अगर (ofdm_index[i] < ofdm_min_index) अणु
			ofdm_index[i] = ofdm_min_index;
		पूर्ण
	पूर्ण
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		अगर (cck_index > CCK_TABLE_SIZE - 1) अणु
			cck_index = CCK_TABLE_SIZE - 1;
		पूर्ण अन्यथा अगर (cck_index < 0) अणु
			cck_index = 0;
		पूर्ण
	पूर्ण
	अगर (is2t) अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"new OFDM_A_index=0x%x, OFDM_B_index = 0x%x, cck_index=0x%x\n",
			ofdm_index[0], ofdm_index[1],
			cck_index);
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"new OFDM_A_index=0x%x,cck_index = 0x%x\n",
			ofdm_index[0], cck_index);
	पूर्ण
	ele_d = (ofdmswing_table[ofdm_index[0]] & 0xFFC00000) >> 22;
	val_x = rtlphy->iqk_matrix[indexक्रमchannel].value[0][0];
	val_y = rtlphy->iqk_matrix[indexक्रमchannel].value[0][1];
	अगर (val_x != 0) अणु
		अगर ((val_x & 0x00000200) != 0)
			val_x = val_x | 0xFFFFFC00;
		ele_a = ((val_x * ele_d) >> 8) & 0x000003FF;

		/* new element C = element D x Y */
		अगर ((val_y & 0x00000200) != 0)
			val_y = val_y | 0xFFFFFC00;
		ele_c = ((val_y * ele_d) >> 8) & 0x000003FF;

		/* ग_लिखो new elements A, C, D to regC80 and
		 * regC94, element B is always 0
		 */
		value32 = (ele_d << 22) | ((ele_c & 0x3F) << 16) | ele_a;
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
			      MASKDWORD, value32);

		value32 = (ele_c & 0x000003C0) >> 6;
		rtl_set_bbreg(hw, ROFDM0_XCTXAFE, MASKH4BITS,
			      value32);

		value32 = ((val_x * ele_d) >> 7) & 0x01;
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD, BIT(24),
			      value32);

	पूर्ण अन्यथा अणु
		rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
			      MASKDWORD,
			      ofdmswing_table[(u8)ofdm_index[0]]);
		rtl_set_bbreg(hw, ROFDM0_XCTXAFE, MASKH4BITS,
			      0x00);
		rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
			      BIT(24), 0x00);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"TxPwrTracking for interface %d path A: X = 0x%lx, Y = 0x%lx ele_A = 0x%lx ele_C = 0x%lx ele_D = 0x%lx 0xe94 = 0x%lx 0xe9c = 0x%lx\n",
		rtlhal->पूर्णांकerfaceindex,
		val_x, val_y, ele_a, ele_c, ele_d,
		val_x, val_y);

	अगर (cck_index >= CCK_TABLE_SIZE)
		cck_index = CCK_TABLE_SIZE - 1;
	अगर (cck_index < 0)
		cck_index = 0;
	अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
		/* Adjust CCK according to IQK result */
		अगर (!rtlpriv->dm.cck_inch14) अणु
			rtl_ग_लिखो_byte(rtlpriv, 0xa22,
				       cckswing_table_ch1ch13[cck_index][0]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa23,
				       cckswing_table_ch1ch13[cck_index][1]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa24,
				       cckswing_table_ch1ch13[cck_index][2]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa25,
				       cckswing_table_ch1ch13[cck_index][3]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa26,
				       cckswing_table_ch1ch13[cck_index][4]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa27,
				       cckswing_table_ch1ch13[cck_index][5]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa28,
				       cckswing_table_ch1ch13[cck_index][6]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa29,
				       cckswing_table_ch1ch13[cck_index][7]);
		पूर्ण अन्यथा अणु
			rtl_ग_लिखो_byte(rtlpriv, 0xa22,
				       cckswing_table_ch14[cck_index][0]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa23,
				       cckswing_table_ch14[cck_index][1]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa24,
				       cckswing_table_ch14[cck_index][2]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa25,
				       cckswing_table_ch14[cck_index][3]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa26,
				       cckswing_table_ch14[cck_index][4]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa27,
				       cckswing_table_ch14[cck_index][5]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa28,
				       cckswing_table_ch14[cck_index][6]);
			rtl_ग_लिखो_byte(rtlpriv, 0xa29,
				       cckswing_table_ch14[cck_index][7]);
		पूर्ण
	पूर्ण
	अगर (is2t) अणु
		ele_d = (ofdmswing_table[ofdm_index[1]] & 0xFFC00000) >> 22;
		val_x = rtlphy->iqk_matrix[indexक्रमchannel].value[0][4];
		val_y = rtlphy->iqk_matrix[indexक्रमchannel].value[0][5];
		अगर (val_x != 0) अणु
			अगर ((val_x & 0x00000200) != 0)
				/* consider minus */
				val_x = val_x | 0xFFFFFC00;
			ele_a = ((val_x * ele_d) >> 8) & 0x000003FF;
			/* new element C = element D x Y */
			अगर ((val_y & 0x00000200) != 0)
				val_y = val_y | 0xFFFFFC00;
			ele_c = ((val_y * ele_d) >> 8) & 0x00003FF;
			/* ग_लिखो new elements A, C, D to regC88
			 * and regC9C, element B is always 0
			 */
			value32 = (ele_d << 22) | ((ele_c & 0x3F) << 16) | ele_a;
			rtl_set_bbreg(hw,
				      ROFDM0_XBTXIQIMBALANCE,
				      MASKDWORD, value32);
			value32 = (ele_c & 0x000003C0) >> 6;
			rtl_set_bbreg(hw, ROFDM0_XDTXAFE,
				      MASKH4BITS, value32);
			value32 = ((val_x * ele_d) >> 7) & 0x01;
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
				      BIT(28), value32);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw,
				      ROFDM0_XBTXIQIMBALANCE,
				      MASKDWORD,
				      ofdmswing_table[ofdm_index[1]]);
			rtl_set_bbreg(hw, ROFDM0_XDTXAFE,
				      MASKH4BITS, 0x00);
			rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
				      BIT(28), 0x00);
		पूर्ण
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"TxPwrTracking path B: X = 0x%lx, Y = 0x%lx ele_A = 0x%lx ele_C = 0x%lx ele_D = 0x%lx 0xeb4 = 0x%lx 0xebc = 0x%lx\n",
			val_x, val_y, ele_a, ele_c,
			ele_d, val_x, val_y);
	पूर्ण
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"TxPwrTracking 0xc80 = 0x%x, 0xc94 = 0x%x RF 0x24 = 0x%x\n",
		rtl_get_bbreg(hw, 0xc80, MASKDWORD),
		rtl_get_bbreg(hw, 0xc94, MASKDWORD),
		rtl_get_rfreg(hw, RF90_PATH_A, 0x24,
			      RFREG_OFFSET_MASK));

check_delta:
	अगर (delta_iqk > rtlefuse->delta_iqk && rtlefuse->delta_iqk != 0) अणु
		rtl92d_phy_reset_iqk_result(hw);
		rtlpriv->dm.thermalvalue_iqk = thermalvalue;
		rtl92d_phy_iq_calibrate(hw);
	पूर्ण
	अगर (delta_rxgain > 0 && rtlhal->current_bandtype == BAND_ON_5G &&
	    thermalvalue <= rtlefuse->eeprom_thermalmeter) अणु
		rtlpriv->dm.thermalvalue_rxgain = thermalvalue;
		rtl92d_dm_rxgain_tracking_thermalmeter(hw);
	पूर्ण
	अगर (rtlpriv->dm.txघातer_track_control)
		rtlpriv->dm.thermalvalue = thermalvalue;

निकास:
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD, "<===\n");
पूर्ण

अटल व्योम rtl92d_dm_initialize_txघातer_tracking(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.txघातer_tracking = true;
	rtlpriv->dm.txघातer_trackinginit = false;
	rtlpriv->dm.txघातer_track_control = true;
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"pMgntInfo->txpower_tracking = %d\n",
		rtlpriv->dm.txघातer_tracking);
पूर्ण

व्योम rtl92d_dm_check_txघातer_tracking_thermal_meter(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (!rtlpriv->dm.txघातer_tracking)
		वापस;

	अगर (!rtlpriv->dm.पंचांग_trigger) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, RF_T_METER, BIT(17) |
			      BIT(16), 0x03);
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Trigger 92S Thermal Meter!!\n");
		rtlpriv->dm.पंचांग_trigger = 1;
		वापस;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Schedule TxPowerTracking direct call!!\n");
		rtl92d_dm_txघातer_tracking_callback_thermalmeter(hw);
		rtlpriv->dm.पंचांग_trigger = 0;
	पूर्ण
पूर्ण

व्योम rtl92d_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rate_adaptive *ra = &(rtlpriv->ra);

	ra->ratr_state = DM_RATR_STA_INIT;
	ra->pre_ratr_state = DM_RATR_STA_INIT;
	अगर (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER)
		rtlpriv->dm.useramask = true;
	अन्यथा
		rtlpriv->dm.useramask = false;
पूर्ण

व्योम rtl92d_dm_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtl_dm_diginit(hw, 0x20);
	rtlpriv->dm_digtable.rx_gain_max = DM_DIG_FA_UPPER;
	rtlpriv->dm_digtable.rx_gain_min = DM_DIG_FA_LOWER;
	rtl92d_dm_init_dynamic_txघातer(hw);
	rtl92d_dm_init_edca_turbo(hw);
	rtl92d_dm_init_rate_adaptive_mask(hw);
	rtl92d_dm_initialize_txघातer_tracking(hw);
पूर्ण

व्योम rtl92d_dm_watchकरोg(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fwps_awake = true;

	/* 1. RF is OFF. (No need to करो DM.)
	 * 2. Fw is under घातer saving mode क्रम FwLPS.
	 *    (Prevent from SW/FW I/O racing.)
	 * 3. IPS workitem is scheduled. (Prevent from IPS sequence
	 *    to be swapped with DM.
	 * 4. RFChangeInProgress is TRUE.
	 *    (Prevent from broken by IPS/HW/SW Rf off.) */

	अगर ((ppsc->rfpwr_state == ERFON) && ((!fw_current_inpsmode) &&
	    fwps_awake) && (!ppsc->rfchange_inprogress)) अणु
		rtl92d_dm_pwdb_monitor(hw);
		rtl92d_dm_false_alarm_counter_statistics(hw);
		rtl92d_dm_find_minimum_rssi(hw);
		rtl92d_dm_dig(hw);
		/* rtl92d_dm_dynamic_bb_घातersaving(hw); */
		rtl92d_dm_dynamic_txघातer(hw);
		/* rtl92d_dm_check_txघातer_tracking_thermal_meter(hw); */
		/* rtl92d_dm_refresh_rate_adaptive_mask(hw); */
		/* rtl92d_dm_पूर्णांकerrupt_migration(hw); */
		rtl92d_dm_check_edca_turbo(hw);
	पूर्ण
पूर्ण
