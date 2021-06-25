<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश <linux/export.h>
#समावेश "dm_common.h"
#समावेश "phy_common.h"
#समावेश "../pci.h"
#समावेश "../base.h"
#समावेश "../core.h"

#घोषणा BT_RSSI_STATE_NORMAL_POWER	BIT(0)
#घोषणा BT_RSSI_STATE_AMDPU_OFF		BIT(1)
#घोषणा BT_RSSI_STATE_SPECIAL_LOW	BIT(2)
#घोषणा BT_RSSI_STATE_BG_EDCA_LOW	BIT(3)
#घोषणा BT_RSSI_STATE_TXPOWER_LOW	BIT(4)
#घोषणा BT_MASK				0x00ffffff

#घोषणा RTLPRIV			(काष्ठा rtl_priv *)
#घोषणा GET_UNDECORATED_AVERAGE_RSSI(_priv)	\
	((RTLPRIV(_priv))->mac80211.opmode == \
			     NL80211_IFTYPE_ADHOC) ?	\
	((RTLPRIV(_priv))->dm.entry_min_undec_sm_pwdb) : \
	((RTLPRIV(_priv))->dm.undec_sm_pwdb)

अटल स्थिर u32 ofdmswing_table[OFDM_TABLE_SIZE] = अणु
	0x7f8001fe,
	0x788001e2,
	0x71c001c7,
	0x6b8001ae,
	0x65400195,
	0x5fc0017f,
	0x5a400169,
	0x55400155,
	0x50800142,
	0x4c000130,
	0x47c0011f,
	0x43c0010f,
	0x40000100,
	0x3c8000f2,
	0x390000e4,
	0x35c000d7,
	0x32c000cb,
	0x300000c0,
	0x2d4000b5,
	0x2ac000ab,
	0x288000a2,
	0x26000098,
	0x24000090,
	0x22000088,
	0x20000080,
	0x1e400079,
	0x1c800072,
	0x1b00006c,
	0x19800066,
	0x18000060,
	0x16c0005b,
	0x15800056,
	0x14400051,
	0x1300004c,
	0x12000048,
	0x11000044,
	0x10000040,
पूर्ण;

अटल स्थिर u8 cckswing_table_ch1ch13[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04पूर्ण,
	अणु0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04पूर्ण,
	अणु0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03पूर्ण,
	अणु0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03पूर्ण,
	अणु0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03पूर्ण,
	अणु0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03पूर्ण,
	अणु0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03पूर्ण,
	अणु0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03पूर्ण,
	अणु0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02पूर्ण,
	अणु0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02पूर्ण,
	अणु0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02पूर्ण,
	अणु0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02पूर्ण,
	अणु0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02पूर्ण,
	अणु0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02पूर्ण,
	अणु0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02पूर्ण,
	अणु0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02पूर्ण,
	अणु0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01पूर्ण,
	अणु0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02पूर्ण,
	अणु0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01पूर्ण,
	अणु0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,
	अणु0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01पूर्ण,
	अणु0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण,
	अणु0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01पूर्ण,
	अणु0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01पूर्ण,
	अणु0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01पूर्ण,
	अणु0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01पूर्ण,
	अणु0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01पूर्ण,
	अणु0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण,
	अणु0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01पूर्ण,
	अणु0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण,
	अणु0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01पूर्ण,
	अणु0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01पूर्ण,
	अणु0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01पूर्ण
पूर्ण;

अटल स्थिर u8 cckswing_table_ch14[CCK_TABLE_SIZE][8] = अणु
	अणु0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00पूर्ण,
	अणु0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00पूर्ण
पूर्ण;

अटल u32 घातer_index_reg[6] = अणु0xc90, 0xc91, 0xc92, 0xc98, 0xc99, 0xc9aपूर्ण;

व्योम dm_restoreघातerindex(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8	index;

	क्रम (index = 0; index < 6; index++)
		rtl_ग_लिखो_byte(rtlpriv, घातer_index_reg[index],
			       rtlpriv->dm.घातerindex_backup[index]);
पूर्ण
EXPORT_SYMBOL_GPL(dm_restoreघातerindex);

व्योम dm_ग_लिखोघातerindex(काष्ठा ieee80211_hw *hw, u8 value)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 index;

	क्रम (index = 0; index < 6; index++)
		rtl_ग_लिखो_byte(rtlpriv, घातer_index_reg[index], value);
पूर्ण
EXPORT_SYMBOL_GPL(dm_ग_लिखोघातerindex);

व्योम dm_saveघातerindex(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 index;
	u8 पंचांगp;

	क्रम (index = 0; index < 6; index++) अणु
		पंचांगp = rtl_पढ़ो_byte(rtlpriv, घातer_index_reg[index]);
		rtlpriv->dm.घातerindex_backup[index] = पंचांगp;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dm_saveघातerindex);

अटल u8 rtl92c_dm_initial_gain_min_pwdb(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	दीर्घ rssi_val_min = 0;

	अगर ((dm_digtable->curmultista_cstate == DIG_MULTISTA_CONNECT) &&
	    (dm_digtable->cursta_cstate == DIG_STA_CONNECT)) अणु
		अगर (rtlpriv->dm.entry_min_undec_sm_pwdb != 0)
			rssi_val_min =
			    (rtlpriv->dm.entry_min_undec_sm_pwdb >
			     rtlpriv->dm.undec_sm_pwdb) ?
			    rtlpriv->dm.undec_sm_pwdb :
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
		अन्यथा
			rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
	पूर्ण अन्यथा अगर (dm_digtable->cursta_cstate == DIG_STA_CONNECT ||
		   dm_digtable->cursta_cstate == DIG_STA_BEFORE_CONNECT) अणु
		rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
	पूर्ण अन्यथा अगर (dm_digtable->curmultista_cstate == DIG_MULTISTA_CONNECT) अणु
		rssi_val_min = rtlpriv->dm.entry_min_undec_sm_pwdb;
	पूर्ण

	अगर (rssi_val_min > 100)
		rssi_val_min = 100;
	वापस (u8)rssi_val_min;
पूर्ण

अटल व्योम rtl92c_dm_false_alarm_counter_statistics(काष्ठा ieee80211_hw *hw)
अणु
	u32 ret_value;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा false_alarm_statistics *falsealm_cnt = &(rtlpriv->falsealm_cnt);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER1, MASKDWORD);
	falsealm_cnt->cnt_parity_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER2, MASKDWORD);
	falsealm_cnt->cnt_rate_illegal = (ret_value & 0xffff);
	falsealm_cnt->cnt_crc8_fail = ((ret_value & 0xffff0000) >> 16);

	ret_value = rtl_get_bbreg(hw, ROFDM_PHYCOUNTER3, MASKDWORD);
	falsealm_cnt->cnt_mcs_fail = (ret_value & 0xffff);

	ret_value = rtl_get_bbreg(hw, ROFDM0_FRAMESYNC, MASKDWORD);
	falsealm_cnt->cnt_fast_fsync_fail = (ret_value & 0xffff);
	falsealm_cnt->cnt_sb_search_fail = ((ret_value & 0xffff0000) >> 16);

	falsealm_cnt->cnt_ofdm_fail = falsealm_cnt->cnt_parity_fail +
				      falsealm_cnt->cnt_rate_illegal +
				      falsealm_cnt->cnt_crc8_fail +
				      falsealm_cnt->cnt_mcs_fail +
				      falsealm_cnt->cnt_fast_fsync_fail +
				      falsealm_cnt->cnt_sb_search_fail;

	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, BIT(14), 1);
	ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERLOWER, MASKBYTE0);
	falsealm_cnt->cnt_cck_fail = ret_value;

	ret_value = rtl_get_bbreg(hw, RCCK0_FACOUNTERUPPER, MASKBYTE3);
	falsealm_cnt->cnt_cck_fail += (ret_value & 0xff) << 8;
	falsealm_cnt->cnt_all = (falsealm_cnt->cnt_parity_fail +
				 falsealm_cnt->cnt_rate_illegal +
				 falsealm_cnt->cnt_crc8_fail +
				 falsealm_cnt->cnt_mcs_fail +
				 falsealm_cnt->cnt_cck_fail);

	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 1);
	rtl_set_bbreg(hw, ROFDM1_LSTF, 0x08000000, 0);
	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 0);
	rtl_set_bbreg(hw, RCCK0_FALSEALARMREPORT, 0x0000c000, 2);

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"cnt_parity_fail = %d, cnt_rate_illegal = %d, cnt_crc8_fail = %d, cnt_mcs_fail = %d\n",
		falsealm_cnt->cnt_parity_fail,
		falsealm_cnt->cnt_rate_illegal,
		falsealm_cnt->cnt_crc8_fail, falsealm_cnt->cnt_mcs_fail);

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"cnt_ofdm_fail = %x, cnt_cck_fail = %x, cnt_all = %x\n",
		falsealm_cnt->cnt_ofdm_fail,
		falsealm_cnt->cnt_cck_fail, falsealm_cnt->cnt_all);
पूर्ण

अटल व्योम rtl92c_dm_ctrl_initgain_by_fa(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	u8 value_igi = dm_digtable->cur_igvalue;

	अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH0)
		value_igi--;
	अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH1)
		value_igi += 0;
	अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < DM_DIG_FA_TH2)
		value_igi++;
	अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all >= DM_DIG_FA_TH2)
		value_igi += 2;

	अगर (value_igi > DM_DIG_FA_UPPER)
		value_igi = DM_DIG_FA_UPPER;
	अन्यथा अगर (value_igi < DM_DIG_FA_LOWER)
		value_igi = DM_DIG_FA_LOWER;

	अगर (rtlpriv->falsealm_cnt.cnt_all > 10000)
		value_igi = DM_DIG_FA_UPPER;

	dm_digtable->cur_igvalue = value_igi;
	rtl92c_dm_ग_लिखो_dig(hw);
पूर्ण

अटल व्योम rtl92c_dm_ctrl_initgain_by_rssi(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *digtable = &rtlpriv->dm_digtable;
	u32 isbt;

	/* modअगरy DIG lower bound, deal with abnormally large false alarm */
	अगर (rtlpriv->falsealm_cnt.cnt_all > 10000) अणु
		digtable->large_fa_hit++;
		अगर (digtable->क्रमbidden_igi < digtable->cur_igvalue) अणु
			digtable->क्रमbidden_igi = digtable->cur_igvalue;
			digtable->large_fa_hit = 1;
		पूर्ण

		अगर (digtable->large_fa_hit >= 3) अणु
			अगर ((digtable->क्रमbidden_igi + 1) >
			    digtable->rx_gain_max)
				digtable->rx_gain_min = digtable->rx_gain_max;
			अन्यथा
				digtable->rx_gain_min = (digtable->क्रमbidden_igi + 1);
			digtable->recover_cnt = 3600; /* 3600=2hr */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Recovery mechanism क्रम IGI lower bound */
		अगर (digtable->recover_cnt != 0) अणु
			digtable->recover_cnt--;
		पूर्ण अन्यथा अणु
			अगर (digtable->large_fa_hit == 0) अणु
				अगर ((digtable->क्रमbidden_igi-1) < DM_DIG_MIN) अणु
					digtable->क्रमbidden_igi = DM_DIG_MIN;
					digtable->rx_gain_min = DM_DIG_MIN;
				पूर्ण अन्यथा अणु
					digtable->क्रमbidden_igi--;
					digtable->rx_gain_min = digtable->क्रमbidden_igi + 1;
				पूर्ण
			पूर्ण अन्यथा अगर (digtable->large_fa_hit == 3) अणु
				digtable->large_fa_hit = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (rtlpriv->falsealm_cnt.cnt_all < 250) अणु
		isbt = rtl_पढ़ो_byte(rtlpriv, 0x4fd) & 0x01;

		अगर (!isbt) अणु
			अगर (rtlpriv->falsealm_cnt.cnt_all >
			    digtable->fa_lowthresh) अणु
				अगर ((digtable->back_val - 2) <
				   digtable->back_range_min)
					digtable->back_val = digtable->back_range_min;
				अन्यथा
					digtable->back_val -= 2;
			पूर्ण अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all <
				   digtable->fa_lowthresh) अणु
				अगर ((digtable->back_val + 2) >
				    digtable->back_range_max)
					digtable->back_val = digtable->back_range_max;
				अन्यथा
					digtable->back_val += 2;
			पूर्ण
		पूर्ण अन्यथा अणु
			digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Adjust initial gain by false alarm */
		अगर (rtlpriv->falsealm_cnt.cnt_all > 1000)
			digtable->cur_igvalue = digtable->pre_igvalue + 2;
		अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all > 750)
			digtable->cur_igvalue = digtable->pre_igvalue + 1;
		अन्यथा अगर (rtlpriv->falsealm_cnt.cnt_all < 500)
			digtable->cur_igvalue = digtable->pre_igvalue - 1;
	पूर्ण

	/* Check initial gain by upper/lower bound */
	अगर (digtable->cur_igvalue > digtable->rx_gain_max)
		digtable->cur_igvalue = digtable->rx_gain_max;

	अगर (digtable->cur_igvalue < digtable->rx_gain_min)
		digtable->cur_igvalue = digtable->rx_gain_min;

	rtl92c_dm_ग_लिखो_dig(hw);
पूर्ण

अटल व्योम rtl92c_dm_initial_gain_multi_sta(काष्ठा ieee80211_hw *hw)
अणु
	अटल u8 initialized; /* initialized to false */
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ rssi_strength = rtlpriv->dm.entry_min_undec_sm_pwdb;
	bool multi_sta = false;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC)
		multi_sta = true;

	अगर (!multi_sta ||
	    dm_digtable->cursta_cstate == DIG_STA_DISCONNECT) अणु
		initialized = false;
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
		वापस;
	पूर्ण अन्यथा अगर (!initialized) अणु
		initialized = true;
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_0;
		dm_digtable->cur_igvalue = 0x20;
		rtl92c_dm_ग_लिखो_dig(hw);
	पूर्ण

	अगर (dm_digtable->curmultista_cstate == DIG_MULTISTA_CONNECT) अणु
		अगर ((rssi_strength < dm_digtable->rssi_lowthresh) &&
		    (dm_digtable->dig_ext_port_stage != DIG_EXT_PORT_STAGE_1)) अणु

			अगर (dm_digtable->dig_ext_port_stage ==
			    DIG_EXT_PORT_STAGE_2) अणु
				dm_digtable->cur_igvalue = 0x20;
				rtl92c_dm_ग_लिखो_dig(hw);
			पूर्ण

			dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_1;
		पूर्ण अन्यथा अगर (rssi_strength > dm_digtable->rssi_highthresh) अणु
			dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_2;
			rtl92c_dm_ctrl_initgain_by_fa(hw);
		पूर्ण
	पूर्ण अन्यथा अगर (dm_digtable->dig_ext_port_stage != DIG_EXT_PORT_STAGE_0) अणु
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_0;
		dm_digtable->cur_igvalue = 0x20;
		rtl92c_dm_ग_लिखो_dig(hw);
	पूर्ण

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"curmultista_cstate = %x dig_ext_port_stage %x\n",
		dm_digtable->curmultista_cstate,
		dm_digtable->dig_ext_port_stage);
पूर्ण

अटल व्योम rtl92c_dm_initial_gain_sta(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_TRACE,
		"presta_cstate = %x, cursta_cstate = %x\n",
		dm_digtable->presta_cstate, dm_digtable->cursta_cstate);
	अगर (dm_digtable->presta_cstate == dm_digtable->cursta_cstate ||
	    dm_digtable->cursta_cstate == DIG_STA_BEFORE_CONNECT ||
	    dm_digtable->cursta_cstate == DIG_STA_CONNECT) अणु
		अगर (dm_digtable->cursta_cstate != DIG_STA_DISCONNECT) अणु
			dm_digtable->rssi_val_min =
			    rtl92c_dm_initial_gain_min_pwdb(hw);
			अगर (dm_digtable->rssi_val_min > 100)
				dm_digtable->rssi_val_min = 100;
			rtl92c_dm_ctrl_initgain_by_rssi(hw);
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable->rssi_val_min = 0;
		dm_digtable->dig_ext_port_stage = DIG_EXT_PORT_STAGE_MAX;
		dm_digtable->back_val = DM_DIG_BACKOFF_DEFAULT;
		dm_digtable->cur_igvalue = 0x20;
		dm_digtable->pre_igvalue = 0;
		rtl92c_dm_ग_लिखो_dig(hw);
	पूर्ण
पूर्ण

अटल व्योम rtl92c_dm_cck_packet_detection_thresh(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	अगर (dm_digtable->cursta_cstate == DIG_STA_CONNECT) अणु
		dm_digtable->rssi_val_min = rtl92c_dm_initial_gain_min_pwdb(hw);
		अगर (dm_digtable->rssi_val_min > 100)
			dm_digtable->rssi_val_min = 100;

		अगर (dm_digtable->pre_cck_pd_state == CCK_PD_STAGE_LOWRSSI) अणु
			अगर (dm_digtable->rssi_val_min <= 25)
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_LOWRSSI;
			अन्यथा
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_HIGHRSSI;
		पूर्ण अन्यथा अणु
			अगर (dm_digtable->rssi_val_min <= 20)
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_LOWRSSI;
			अन्यथा
				dm_digtable->cur_cck_pd_state =
				    CCK_PD_STAGE_HIGHRSSI;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_digtable->cur_cck_pd_state = CCK_PD_STAGE_MAX;
	पूर्ण

	अगर (dm_digtable->pre_cck_pd_state != dm_digtable->cur_cck_pd_state) अणु
		अगर ((dm_digtable->cur_cck_pd_state == CCK_PD_STAGE_LOWRSSI) ||
		    (dm_digtable->cur_cck_pd_state == CCK_PD_STAGE_MAX))
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0x83);
		अन्यथा
			rtl_set_bbreg(hw, RCCK0_CCA, MASKBYTE2, 0xcd);

		dm_digtable->pre_cck_pd_state = dm_digtable->cur_cck_pd_state;
	पूर्ण
पूर्ण

अटल व्योम rtl92c_dm_ctrl_initgain_by_twoport(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	अगर (mac->act_scanning)
		वापस;

	अगर (mac->link_state >= MAC80211_LINKED)
		dm_digtable->cursta_cstate = DIG_STA_CONNECT;
	अन्यथा
		dm_digtable->cursta_cstate = DIG_STA_DISCONNECT;

	dm_digtable->curmultista_cstate = DIG_MULTISTA_DISCONNECT;

	rtl92c_dm_initial_gain_sta(hw);
	rtl92c_dm_initial_gain_multi_sta(hw);
	rtl92c_dm_cck_packet_detection_thresh(hw);

	dm_digtable->presta_cstate = dm_digtable->cursta_cstate;
पूर्ण

अटल व्योम rtl92c_dm_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (!rtlpriv->dm.dm_initialgain_enable)
		वापस;
	अगर (!(rtlpriv->dm.dm_flag & DYNAMIC_FUNC_DIG))
		वापस;

	rtl92c_dm_ctrl_initgain_by_twoport(hw);
पूर्ण

अटल व्योम rtl92c_dm_init_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->rtlhal.पूर्णांकerface == INTF_USB &&
	    rtlpriv->rtlhal.board_type & 0x1) अणु
		dm_saveघातerindex(hw);
		rtlpriv->dm.dynamic_txघातer_enable = true;
	पूर्ण अन्यथा अणु
		rtlpriv->dm.dynamic_txघातer_enable = false;
	पूर्ण
	rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
	rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
पूर्ण

व्योम rtl92c_dm_ग_लिखो_dig(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा dig_t *dm_digtable = &rtlpriv->dm_digtable;

	rtl_dbg(rtlpriv, COMP_DIG, DBG_LOUD,
		"cur_igvalue = 0x%x, pre_igvalue = 0x%x, back_val = %d\n",
		dm_digtable->cur_igvalue, dm_digtable->pre_igvalue,
		dm_digtable->back_val);

	अगर (rtlpriv->rtlhal.पूर्णांकerface == INTF_USB &&
	    !dm_digtable->dig_enable_flag) अणु
		dm_digtable->pre_igvalue = 0x17;
		वापस;
	पूर्ण
	dm_digtable->cur_igvalue -= 1;
	अगर (dm_digtable->cur_igvalue < DM_DIG_MIN)
		dm_digtable->cur_igvalue = DM_DIG_MIN;

	अगर (dm_digtable->pre_igvalue != dm_digtable->cur_igvalue) अणु
		rtl_set_bbreg(hw, ROFDM0_XAAGCCORE1, 0x7f,
			      dm_digtable->cur_igvalue);
		rtl_set_bbreg(hw, ROFDM0_XBAGCCORE1, 0x7f,
			      dm_digtable->cur_igvalue);

		dm_digtable->pre_igvalue = dm_digtable->cur_igvalue;
	पूर्ण
	rtl_dbg(rtlpriv, COMP_DIG, DBG_WARNING,
		"dig values 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",
		dm_digtable->cur_igvalue, dm_digtable->pre_igvalue,
		dm_digtable->rssi_val_min, dm_digtable->back_val,
		dm_digtable->rx_gain_max, dm_digtable->rx_gain_min,
		dm_digtable->large_fa_hit, dm_digtable->क्रमbidden_igi);
पूर्ण
EXPORT_SYMBOL(rtl92c_dm_ग_लिखो_dig);

अटल व्योम rtl92c_dm_pwdb_monitor(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ पंचांगpentry_max_pwdb = 0, पंचांगpentry_min_pwdb = 0xff;

	अगर (mac->link_state != MAC80211_LINKED)
		वापस;

	अगर (mac->opmode == NL80211_IFTYPE_ADHOC ||
	    mac->opmode == NL80211_IFTYPE_AP) अणु
		/* TODO: Handle ADHOC and AP Mode */
	पूर्ण

	अगर (पंचांगpentry_max_pwdb != 0)
		rtlpriv->dm.entry_max_undec_sm_pwdb = पंचांगpentry_max_pwdb;
	अन्यथा
		rtlpriv->dm.entry_max_undec_sm_pwdb = 0;

	अगर (पंचांगpentry_min_pwdb != 0xff)
		rtlpriv->dm.entry_min_undec_sm_pwdb = पंचांगpentry_min_pwdb;
	अन्यथा
		rtlpriv->dm.entry_min_undec_sm_pwdb = 0;

/* TODO:
 *	अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
 *		अगर (rtlpriv->rtlhal.fw_पढ़ोy) अणु
 *			u32 param = (u32)(rtlpriv->dm.undec_sm_pwdb << 16);
 *			rtl8192c_set_rssi_cmd(hw, param);
 *		पूर्ण
 *	पूर्ण
 */
पूर्ण

व्योम rtl92c_dm_init_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.current_turbo_edca = false;
	rtlpriv->dm.is_any_nonbepkts = false;
	rtlpriv->dm.is_cur_rdlstate = false;
पूर्ण
EXPORT_SYMBOL(rtl92c_dm_init_edca_turbo);

अटल व्योम rtl92c_dm_check_edca_turbo(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	अटल u64 last_txok_cnt;
	अटल u64 last_rxok_cnt;
	अटल u32 last_bt_edca_ul;
	अटल u32 last_bt_edca_dl;
	u64 cur_txok_cnt = 0;
	u64 cur_rxok_cnt = 0;
	u32 edca_be_ul = 0x5ea42b;
	u32 edca_be_dl = 0x5ea42b;
	bool bt_change_edca = false;

	अगर ((last_bt_edca_ul != rtlpriv->btcoexist.bt_edca_ul) ||
	    (last_bt_edca_dl != rtlpriv->btcoexist.bt_edca_dl)) अणु
		rtlpriv->dm.current_turbo_edca = false;
		last_bt_edca_ul = rtlpriv->btcoexist.bt_edca_ul;
		last_bt_edca_dl = rtlpriv->btcoexist.bt_edca_dl;
	पूर्ण

	अगर (rtlpriv->btcoexist.bt_edca_ul != 0) अणु
		edca_be_ul = rtlpriv->btcoexist.bt_edca_ul;
		bt_change_edca = true;
	पूर्ण

	अगर (rtlpriv->btcoexist.bt_edca_dl != 0) अणु
		edca_be_ul = rtlpriv->btcoexist.bt_edca_dl;
		bt_change_edca = true;
	पूर्ण

	अगर (mac->link_state != MAC80211_LINKED) अणु
		rtlpriv->dm.current_turbo_edca = false;
		वापस;
	पूर्ण

	अगर ((!mac->ht_enable) && (!rtlpriv->btcoexist.bt_coexistence)) अणु
		अगर (!(edca_be_ul & 0xffff0000))
			edca_be_ul |= 0x005e0000;

		अगर (!(edca_be_dl & 0xffff0000))
			edca_be_dl |= 0x005e0000;
	पूर्ण

	अगर ((bt_change_edca) || ((!rtlpriv->dm.is_any_nonbepkts) &&
	     (!rtlpriv->dm.disable_framebursting))) अणु
		cur_txok_cnt = rtlpriv->stats.txbytesunicast - last_txok_cnt;
		cur_rxok_cnt = rtlpriv->stats.rxbytesunicast - last_rxok_cnt;

		अगर (cur_rxok_cnt > 4 * cur_txok_cnt) अणु
			अगर (!rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) अणु
				rtl_ग_लिखो_dword(rtlpriv,
						REG_EDCA_BE_PARAM,
						edca_be_dl);
				rtlpriv->dm.is_cur_rdlstate = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (rtlpriv->dm.is_cur_rdlstate ||
			    !rtlpriv->dm.current_turbo_edca) अणु
				rtl_ग_लिखो_dword(rtlpriv,
						REG_EDCA_BE_PARAM,
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

	rtlpriv->dm.is_any_nonbepkts = false;
	last_txok_cnt = rtlpriv->stats.txbytesunicast;
	last_rxok_cnt = rtlpriv->stats.rxbytesunicast;
पूर्ण

अटल व्योम rtl92c_dm_txघातer_tracking_callback_thermalmeter(काष्ठा ieee80211_hw
							     *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	u8 thermalvalue, delta, delta_lck, delta_iqk;
	दीर्घ ele_a, ele_d, temp_cck, val_x, value32;
	दीर्घ val_y, ele_c = 0;
	u8 ofdm_index[2], ofdm_index_old[2] = अणु0, 0पूर्ण, cck_index_old = 0;
	s8 cck_index = 0;
	पूर्णांक i;
	bool is2t = IS_92C_SERIAL(rtlhal->version);
	s8 txpwr_level[3] = अणु0, 0, 0पूर्ण;
	u8 ofdm_min_index = 6, rf;

	rtlpriv->dm.txघातer_trackinginit = true;
	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"%s\n", __func__);

	thermalvalue = (u8) rtl_get_rfreg(hw, RF90_PATH_A, RF_T_METER, 0x1f);

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"Readback Thermal Meter = 0x%x pre thermal meter 0x%x eeprom_thermalmeter 0x%x\n",
		thermalvalue, rtlpriv->dm.thermalvalue,
		rtlefuse->eeprom_thermalmeter);

	rtl92c_phy_ap_calibrate(hw, (thermalvalue -
				     rtlefuse->eeprom_thermalmeter));
	अगर (is2t)
		rf = 2;
	अन्यथा
		rf = 1;

	अगर (thermalvalue) अणु
		ele_d = rtl_get_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
				      MASKDWORD) & MASKOFDM_D;

		क्रम (i = 0; i < OFDM_TABLE_LENGTH; i++) अणु
			अगर (ele_d == (ofdmswing_table[i] & MASKOFDM_D)) अणु
				ofdm_index_old[0] = (u8) i;

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

			क्रम (i = 0; i < OFDM_TABLE_LENGTH; i++) अणु
				अगर (ele_d == (ofdmswing_table[i] &
				    MASKOFDM_D)) अणु
					ofdm_index_old[1] = (u8) i;
					rtl_dbg(rtlpriv, COMP_POWER_TRACKING,
						DBG_LOUD,
						"Initial pathB ele_d reg0x%x = 0x%lx, ofdm_index=0x%x\n",
						ROFDM0_XBTXIQIMBALANCE, ele_d,
						ofdm_index_old[1]);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		temp_cck =
		    rtl_get_bbreg(hw, RCCK0_TXFILTER2, MASKDWORD) & MASKCCK;

		क्रम (i = 0; i < CCK_TABLE_LENGTH; i++) अणु
			अगर (rtlpriv->dm.cck_inch14) अणु
				अगर (स_भेद((व्योम *)&temp_cck,
					   (व्योम *)&cckswing_table_ch14[i][2],
					   4) == 0) अणु
					cck_index_old = (u8) i;

					rtl_dbg(rtlpriv, COMP_POWER_TRACKING,
						DBG_LOUD,
						"Initial reg0x%x = 0x%lx, cck_index=0x%x, ch 14 %d\n",
						RCCK0_TXFILTER2, temp_cck,
						cck_index_old,
						rtlpriv->dm.cck_inch14);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (स_भेद((व्योम *)&temp_cck,
					   (व्योम *)
					   &cckswing_table_ch1ch13[i][2],
					   4) == 0) अणु
					cck_index_old = (u8) i;

					rtl_dbg(rtlpriv, COMP_POWER_TRACKING,
						DBG_LOUD,
						"Initial reg0x%x = 0x%lx, cck_index=0x%x, ch14 %d\n",
						RCCK0_TXFILTER2, temp_cck,
						cck_index_old,
						rtlpriv->dm.cck_inch14);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (!rtlpriv->dm.thermalvalue) अणु
			rtlpriv->dm.thermalvalue =
			    rtlefuse->eeprom_thermalmeter;
			rtlpriv->dm.thermalvalue_lck = thermalvalue;
			rtlpriv->dm.thermalvalue_iqk = thermalvalue;
			क्रम (i = 0; i < rf; i++)
				rtlpriv->dm.ofdm_index[i] = ofdm_index_old[i];
			rtlpriv->dm.cck_index = cck_index_old;
		पूर्ण
		/* Handle USB High PA boards */

		delta = (thermalvalue > rtlpriv->dm.thermalvalue) ?
		    (thermalvalue - rtlpriv->dm.thermalvalue) :
		    (rtlpriv->dm.thermalvalue - thermalvalue);

		delta_lck = (thermalvalue > rtlpriv->dm.thermalvalue_lck) ?
		    (thermalvalue - rtlpriv->dm.thermalvalue_lck) :
		    (rtlpriv->dm.thermalvalue_lck - thermalvalue);

		delta_iqk = (thermalvalue > rtlpriv->dm.thermalvalue_iqk) ?
		    (thermalvalue - rtlpriv->dm.thermalvalue_iqk) :
		    (rtlpriv->dm.thermalvalue_iqk - thermalvalue);

		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Readback Thermal Meter = 0x%x pre thermal meter 0x%x eeprom_thermalmeter 0x%x delta 0x%x delta_lck 0x%x delta_iqk 0x%x\n",
			thermalvalue, rtlpriv->dm.thermalvalue,
			rtlefuse->eeprom_thermalmeter, delta, delta_lck,
			delta_iqk);

		अगर (delta_lck > 1) अणु
			rtlpriv->dm.thermalvalue_lck = thermalvalue;
			rtl92c_phy_lc_calibrate(hw);
		पूर्ण

		अगर (delta > 0 && rtlpriv->dm.txघातer_track_control) अणु
			अगर (thermalvalue > rtlpriv->dm.thermalvalue) अणु
				क्रम (i = 0; i < rf; i++)
					rtlpriv->dm.ofdm_index[i] -= delta;
				rtlpriv->dm.cck_index -= delta;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < rf; i++)
					rtlpriv->dm.ofdm_index[i] += delta;
				rtlpriv->dm.cck_index += delta;
			पूर्ण

			अगर (is2t) अणु
				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"temp OFDM_A_index=0x%x, OFDM_B_index=0x%x, cck_index=0x%x\n",
					rtlpriv->dm.ofdm_index[0],
					rtlpriv->dm.ofdm_index[1],
					rtlpriv->dm.cck_index);
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"temp OFDM_A_index=0x%x, cck_index=0x%x\n",
					rtlpriv->dm.ofdm_index[0],
					rtlpriv->dm.cck_index);
			पूर्ण

			अगर (thermalvalue > rtlefuse->eeprom_thermalmeter) अणु
				क्रम (i = 0; i < rf; i++)
					ofdm_index[i] =
					    rtlpriv->dm.ofdm_index[i]
					    + 1;
				cck_index = rtlpriv->dm.cck_index + 1;
			पूर्ण अन्यथा अणु
				क्रम (i = 0; i < rf; i++)
					ofdm_index[i] =
					    rtlpriv->dm.ofdm_index[i];
				cck_index = rtlpriv->dm.cck_index;
			पूर्ण

			क्रम (i = 0; i < rf; i++) अणु
				अगर (txpwr_level[i] >= 0 &&
				    txpwr_level[i] <= 26) अणु
					अगर (thermalvalue >
					    rtlefuse->eeprom_thermalmeter) अणु
						अगर (delta < 5)
							ofdm_index[i] -= 1;

						अन्यथा
							ofdm_index[i] -= 2;
					पूर्ण अन्यथा अगर (delta > 5 && thermalvalue <
						   rtlefuse->
						   eeprom_thermalmeter) अणु
						ofdm_index[i] += 1;
					पूर्ण
				पूर्ण अन्यथा अगर (txpwr_level[i] >= 27 &&
					   txpwr_level[i] <= 32
					   && thermalvalue >
					   rtlefuse->eeprom_thermalmeter) अणु
					अगर (delta < 5)
						ofdm_index[i] -= 1;

					अन्यथा
						ofdm_index[i] -= 2;
				पूर्ण अन्यथा अगर (txpwr_level[i] >= 32 &&
					   txpwr_level[i] <= 38 &&
					   thermalvalue >
					   rtlefuse->eeprom_thermalmeter
					   && delta > 5) अणु
					ofdm_index[i] -= 1;
				पूर्ण
			पूर्ण

			अगर (txpwr_level[i] >= 0 && txpwr_level[i] <= 26) अणु
				अगर (thermalvalue >
				    rtlefuse->eeprom_thermalmeter) अणु
					अगर (delta < 5)
						cck_index -= 1;

					अन्यथा
						cck_index -= 2;
				पूर्ण अन्यथा अगर (delta > 5 && thermalvalue <
					   rtlefuse->eeprom_thermalmeter) अणु
					cck_index += 1;
				पूर्ण
			पूर्ण अन्यथा अगर (txpwr_level[i] >= 27 &&
				   txpwr_level[i] <= 32 &&
				   thermalvalue >
				   rtlefuse->eeprom_thermalmeter) अणु
				अगर (delta < 5)
					cck_index -= 1;

				अन्यथा
					cck_index -= 2;
			पूर्ण अन्यथा अगर (txpwr_level[i] >= 32 &&
				   txpwr_level[i] <= 38 &&
				   thermalvalue > rtlefuse->eeprom_thermalmeter
				   && delta > 5) अणु
				cck_index -= 1;
			पूर्ण

			क्रम (i = 0; i < rf; i++) अणु
				अगर (ofdm_index[i] > OFDM_TABLE_SIZE - 1)
					ofdm_index[i] = OFDM_TABLE_SIZE - 1;

				अन्यथा अगर (ofdm_index[i] < ofdm_min_index)
					ofdm_index[i] = ofdm_min_index;
			पूर्ण

			अगर (cck_index > CCK_TABLE_SIZE - 1)
				cck_index = CCK_TABLE_SIZE - 1;
			अन्यथा अगर (cck_index < 0)
				cck_index = 0;

			अगर (is2t) अणु
				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"new OFDM_A_index=0x%x, OFDM_B_index=0x%x, cck_index=0x%x\n",
					ofdm_index[0], ofdm_index[1],
					cck_index);
			पूर्ण अन्यथा अणु
				rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
					"new OFDM_A_index=0x%x, cck_index=0x%x\n",
					ofdm_index[0], cck_index);
			पूर्ण
		पूर्ण

		अगर (rtlpriv->dm.txघातer_track_control && delta != 0) अणु
			ele_d =
			    (ofdmswing_table[ofdm_index[0]] & 0xFFC00000) >> 22;
			val_x = rtlphy->reg_e94;
			val_y = rtlphy->reg_e9c;

			अगर (val_x != 0) अणु
				अगर ((val_x & 0x00000200) != 0)
					val_x = val_x | 0xFFFFFC00;
				ele_a = ((val_x * ele_d) >> 8) & 0x000003FF;

				अगर ((val_y & 0x00000200) != 0)
					val_y = val_y | 0xFFFFFC00;
				ele_c = ((val_y * ele_d) >> 8) & 0x000003FF;

				value32 = (ele_d << 22) |
				    ((ele_c & 0x3F) << 16) | ele_a;

				rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
					      MASKDWORD, value32);

				value32 = (ele_c & 0x000003C0) >> 6;
				rtl_set_bbreg(hw, ROFDM0_XCTXAFE, MASKH4BITS,
					      value32);

				value32 = ((val_x * ele_d) >> 7) & 0x01;
				rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
					      BIT(31), value32);

				value32 = ((val_y * ele_d) >> 7) & 0x01;
				rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
					      BIT(29), value32);
			पूर्ण अन्यथा अणु
				rtl_set_bbreg(hw, ROFDM0_XATXIQIMBALANCE,
					      MASKDWORD,
					      ofdmswing_table[ofdm_index[0]]);

				rtl_set_bbreg(hw, ROFDM0_XCTXAFE, MASKH4BITS,
					      0x00);
				rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
					      BIT(31) | BIT(29), 0x00);
			पूर्ण

			अगर (!rtlpriv->dm.cck_inch14) अणु
				rtl_ग_लिखो_byte(rtlpriv, 0xa22,
					       cckswing_table_ch1ch13[cck_index]
					       [0]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa23,
					       cckswing_table_ch1ch13[cck_index]
					       [1]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa24,
					       cckswing_table_ch1ch13[cck_index]
					       [2]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa25,
					       cckswing_table_ch1ch13[cck_index]
					       [3]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa26,
					       cckswing_table_ch1ch13[cck_index]
					       [4]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa27,
					       cckswing_table_ch1ch13[cck_index]
					       [5]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa28,
					       cckswing_table_ch1ch13[cck_index]
					       [6]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa29,
					       cckswing_table_ch1ch13[cck_index]
					       [7]);
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_byte(rtlpriv, 0xa22,
					       cckswing_table_ch14[cck_index]
					       [0]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa23,
					       cckswing_table_ch14[cck_index]
					       [1]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa24,
					       cckswing_table_ch14[cck_index]
					       [2]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa25,
					       cckswing_table_ch14[cck_index]
					       [3]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa26,
					       cckswing_table_ch14[cck_index]
					       [4]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa27,
					       cckswing_table_ch14[cck_index]
					       [5]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa28,
					       cckswing_table_ch14[cck_index]
					       [6]);
				rtl_ग_लिखो_byte(rtlpriv, 0xa29,
					       cckswing_table_ch14[cck_index]
					       [7]);
			पूर्ण

			अगर (is2t) अणु
				ele_d = (ofdmswing_table[ofdm_index[1]] &
					 0xFFC00000) >> 22;

				val_x = rtlphy->reg_eb4;
				val_y = rtlphy->reg_ebc;

				अगर (val_x != 0) अणु
					अगर ((val_x & 0x00000200) != 0)
						val_x = val_x | 0xFFFFFC00;
					ele_a = ((val_x * ele_d) >> 8) &
					    0x000003FF;

					अगर ((val_y & 0x00000200) != 0)
						val_y = val_y | 0xFFFFFC00;
					ele_c = ((val_y * ele_d) >> 8) &
					    0x00003FF;

					value32 = (ele_d << 22) |
					    ((ele_c & 0x3F) << 16) | ele_a;
					rtl_set_bbreg(hw,
						      ROFDM0_XBTXIQIMBALANCE,
						      MASKDWORD, value32);

					value32 = (ele_c & 0x000003C0) >> 6;
					rtl_set_bbreg(hw, ROFDM0_XDTXAFE,
						      MASKH4BITS, value32);

					value32 = ((val_x * ele_d) >> 7) & 0x01;
					rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
						      BIT(27), value32);

					value32 = ((val_y * ele_d) >> 7) & 0x01;
					rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
						      BIT(25), value32);
				पूर्ण अन्यथा अणु
					rtl_set_bbreg(hw,
						      ROFDM0_XBTXIQIMBALANCE,
						      MASKDWORD,
						      ofdmswing_table[ofdm_index
								      [1]]);
					rtl_set_bbreg(hw, ROFDM0_XDTXAFE,
						      MASKH4BITS, 0x00);
					rtl_set_bbreg(hw, ROFDM0_ECCATHRESHOLD,
						      BIT(27) | BIT(25), 0x00);
				पूर्ण

			पूर्ण
		पूर्ण

		अगर (delta_iqk > 3) अणु
			rtlpriv->dm.thermalvalue_iqk = thermalvalue;
			rtl92c_phy_iq_calibrate(hw, false);
		पूर्ण

		अगर (rtlpriv->dm.txघातer_track_control)
			rtlpriv->dm.thermalvalue = thermalvalue;
	पूर्ण

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD, "<===\n");

पूर्ण

अटल व्योम rtl92c_dm_initialize_txघातer_tracking_thermalmeter(
						काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.txघातer_tracking = true;
	rtlpriv->dm.txघातer_trackinginit = false;

	rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		"pMgntInfo->txpower_tracking = %d\n",
		rtlpriv->dm.txघातer_tracking);
पूर्ण

अटल व्योम rtl92c_dm_initialize_txघातer_tracking(काष्ठा ieee80211_hw *hw)
अणु
	rtl92c_dm_initialize_txघातer_tracking_thermalmeter(hw);
पूर्ण

अटल व्योम rtl92c_dm_txघातer_tracking_directcall(काष्ठा ieee80211_hw *hw)
अणु
	rtl92c_dm_txघातer_tracking_callback_thermalmeter(hw);
पूर्ण

अटल व्योम rtl92c_dm_check_txघातer_tracking_thermal_meter(
						काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (!rtlpriv->dm.txघातer_tracking)
		वापस;

	अगर (!rtlpriv->dm.पंचांग_trigger) अणु
		rtl_set_rfreg(hw, RF90_PATH_A, RF_T_METER, RFREG_OFFSET_MASK,
			      0x60);
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Trigger 92S Thermal Meter!!\n");
		rtlpriv->dm.पंचांग_trigger = 1;
		वापस;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			"Schedule TxPowerTracking direct call!!\n");
		rtl92c_dm_txघातer_tracking_directcall(hw);
		rtlpriv->dm.पंचांग_trigger = 0;
	पूर्ण
पूर्ण

व्योम rtl92c_dm_check_txघातer_tracking(काष्ठा ieee80211_hw *hw)
अणु
	rtl92c_dm_check_txघातer_tracking_thermal_meter(hw);
पूर्ण
EXPORT_SYMBOL(rtl92c_dm_check_txघातer_tracking);

व्योम rtl92c_dm_init_rate_adaptive_mask(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rate_adaptive *p_ra = &(rtlpriv->ra);

	p_ra->ratr_state = DM_RATR_STA_INIT;
	p_ra->pre_ratr_state = DM_RATR_STA_INIT;

	अगर (rtlpriv->dm.dm_type == DM_TYPE_BYDRIVER)
		rtlpriv->dm.useramask = true;
	अन्यथा
		rtlpriv->dm.useramask = false;

पूर्ण
EXPORT_SYMBOL(rtl92c_dm_init_rate_adaptive_mask);

अटल व्योम rtl92c_dm_init_dynamic_bb_घातersaving(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ps_t *dm_pstable = &rtlpriv->dm_pstable;

	dm_pstable->pre_ccastate = CCA_MAX;
	dm_pstable->cur_ccasate = CCA_MAX;
	dm_pstable->pre_rख_स्थितिe = RF_MAX;
	dm_pstable->cur_rख_स्थितिe = RF_MAX;
	dm_pstable->rssi_val_min = 0;
पूर्ण

व्योम rtl92c_dm_rf_saving(काष्ठा ieee80211_hw *hw, u8 bक्रमce_in_normal)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ps_t *dm_pstable = &rtlpriv->dm_pstable;

	अगर (!rtlpriv->reg_init) अणु
		rtlpriv->reg_874 = (rtl_get_bbreg(hw,
						  RFPGA0_XCD_RFINTERFACESW,
						  MASKDWORD) & 0x1CC000) >> 14;

		rtlpriv->reg_c70 = (rtl_get_bbreg(hw, ROFDM0_AGCPARAMETER1,
				    MASKDWORD) & BIT(3)) >> 3;

		rtlpriv->reg_85c = (rtl_get_bbreg(hw, RFPGA0_XCD_SWITCHCONTROL,
				    MASKDWORD) & 0xFF000000) >> 24;

		rtlpriv->reg_a74 = (rtl_get_bbreg(hw, 0xa74, MASKDWORD) &
				    0xF000) >> 12;

		rtlpriv->reg_init = true;
	पूर्ण

	अगर (!bक्रमce_in_normal) अणु
		अगर (dm_pstable->rssi_val_min != 0) अणु
			अगर (dm_pstable->pre_rख_स्थितिe == RF_NORMAL) अणु
				अगर (dm_pstable->rssi_val_min >= 30)
					dm_pstable->cur_rख_स्थितिe = RF_SAVE;
				अन्यथा
					dm_pstable->cur_rख_स्थितिe = RF_NORMAL;
			पूर्ण अन्यथा अणु
				अगर (dm_pstable->rssi_val_min <= 25)
					dm_pstable->cur_rख_स्थितिe = RF_NORMAL;
				अन्यथा
					dm_pstable->cur_rख_स्थितिe = RF_SAVE;
			पूर्ण
		पूर्ण अन्यथा अणु
			dm_pstable->cur_rख_स्थितिe = RF_MAX;
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_pstable->cur_rख_स्थितिe = RF_NORMAL;
	पूर्ण

	अगर (dm_pstable->pre_rख_स्थितिe != dm_pstable->cur_rख_स्थितिe) अणु
		अगर (dm_pstable->cur_rख_स्थितिe == RF_SAVE) अणु
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      0x1C0000, 0x2);
			rtl_set_bbreg(hw, ROFDM0_AGCPARAMETER1, BIT(3), 0);
			rtl_set_bbreg(hw, RFPGA0_XCD_SWITCHCONTROL,
				      0xFF000000, 0x63);
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      0xC000, 0x2);
			rtl_set_bbreg(hw, 0xa74, 0xF000, 0x3);
			rtl_set_bbreg(hw, 0x818, BIT(28), 0x0);
			rtl_set_bbreg(hw, 0x818, BIT(28), 0x1);
		पूर्ण अन्यथा अणु
			rtl_set_bbreg(hw, RFPGA0_XCD_RFINTERFACESW,
				      0x1CC000, rtlpriv->reg_874);
			rtl_set_bbreg(hw, ROFDM0_AGCPARAMETER1, BIT(3),
				      rtlpriv->reg_c70);
			rtl_set_bbreg(hw, RFPGA0_XCD_SWITCHCONTROL, 0xFF000000,
				      rtlpriv->reg_85c);
			rtl_set_bbreg(hw, 0xa74, 0xF000, rtlpriv->reg_a74);
			rtl_set_bbreg(hw, 0x818, BIT(28), 0x0);
		पूर्ण

		dm_pstable->pre_rख_स्थितिe = dm_pstable->cur_rख_स्थितिe;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl92c_dm_rf_saving);

अटल व्योम rtl92c_dm_dynamic_bb_घातersaving(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ps_t *dm_pstable = &rtlpriv->dm_pstable;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	/* Determine the minimum RSSI */
	अगर (((mac->link_state == MAC80211_NOLINK)) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		dm_pstable->rssi_val_min = 0;
		rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD, "Not connected to any\n");
	पूर्ण

	अगर (mac->link_state == MAC80211_LINKED) अणु
		अगर (mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			dm_pstable->rssi_val_min =
			    rtlpriv->dm.entry_min_undec_sm_pwdb;
			rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD,
				"AP Client PWDB = 0x%lx\n",
				dm_pstable->rssi_val_min);
		पूर्ण अन्यथा अणु
			dm_pstable->rssi_val_min = rtlpriv->dm.undec_sm_pwdb;
			rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD,
				"STA Default Port PWDB = 0x%lx\n",
				dm_pstable->rssi_val_min);
		पूर्ण
	पूर्ण अन्यथा अणु
		dm_pstable->rssi_val_min =
		    rtlpriv->dm.entry_min_undec_sm_pwdb;

		rtl_dbg(rtlpriv, DBG_LOUD, DBG_LOUD,
			"AP Ext Port PWDB = 0x%lx\n",
			dm_pstable->rssi_val_min);
	पूर्ण

	/* Power Saving क्रम 92C */
	अगर (IS_92C_SERIAL(rtlhal->version))
		;/* rtl92c_dm_1r_cca(hw); */
	अन्यथा
		rtl92c_dm_rf_saving(hw, false);
पूर्ण

व्योम rtl92c_dm_init(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->dm.dm_type = DM_TYPE_BYDRIVER;
	rtlpriv->dm.dm_flag = DYNAMIC_FUNC_DISABLE | DYNAMIC_FUNC_DIG;
	rtlpriv->dm.undec_sm_pwdb = -1;
	rtlpriv->dm.undec_sm_cck = -1;
	rtlpriv->dm.dm_initialgain_enable = true;
	rtl_dm_diginit(hw, 0x20);

	rtlpriv->dm.dm_flag |= HAL_DM_HIPWR_DISABLE;
	rtl92c_dm_init_dynamic_txघातer(hw);

	rtl92c_dm_init_edca_turbo(hw);
	rtl92c_dm_init_rate_adaptive_mask(hw);
	rtlpriv->dm.dm_flag |= DYNAMIC_FUNC_SS;
	rtl92c_dm_initialize_txघातer_tracking(hw);
	rtl92c_dm_init_dynamic_bb_घातersaving(hw);

	rtlpriv->dm.ofdm_pkt_cnt = 0;
	rtlpriv->dm.dm_rssi_sel = RSSI_DEFAULT;
पूर्ण
EXPORT_SYMBOL(rtl92c_dm_init);

व्योम rtl92c_dm_dynamic_txघातer(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	दीर्घ undec_sm_pwdb;

	अगर (!rtlpriv->dm.dynamic_txघातer_enable)
		वापस;

	अगर (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		वापस;
	पूर्ण

	अगर ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_TRACE,
			"Not connected to any\n");

		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
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

	अगर (undec_sm_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL2) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_LEVEL2;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n");
	पूर्ण अन्यथा अगर ((undec_sm_pwdb < (TX_POWER_NEAR_FIELD_THRESH_LVL2 - 3)) &&
		   (undec_sm_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL1)) अणु

		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_LEVEL1;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n");
	पूर्ण अन्यथा अगर (undec_sm_pwdb < (TX_POWER_NEAR_FIELD_THRESH_LVL1 - 5)) अणु
		rtlpriv->dm.dynamic_txhighघातer_lvl = TXHIGHPWRLEVEL_NORMAL;
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"TXHIGHPWRLEVEL_NORMAL\n");
	पूर्ण

	अगर ((rtlpriv->dm.dynamic_txhighघातer_lvl != rtlpriv->dm.last_dtp_lvl)) अणु
		rtl_dbg(rtlpriv, COMP_POWER, DBG_LOUD,
			"PHY_SetTxPowerLevel8192S() Channel = %d\n",
			 rtlphy->current_channel);
		rtl92c_phy_set_txघातer_level(hw, rtlphy->current_channel);
		अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
		    TXHIGHPWRLEVEL_NORMAL)
			dm_restoreघातerindex(hw);
		अन्यथा अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
			 TXHIGHPWRLEVEL_LEVEL1)
			dm_ग_लिखोघातerindex(hw, 0x14);
		अन्यथा अगर (rtlpriv->dm.dynamic_txhighघातer_lvl ==
			 TXHIGHPWRLEVEL_LEVEL2)
			dm_ग_लिखोघातerindex(hw, 0x10);
	पूर्ण
	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighघातer_lvl;
पूर्ण

व्योम rtl92c_dm_watchकरोg(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool fw_current_inpsmode = false;
	bool fw_ps_awake = true;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FW_PSMODE_STATUS,
				      (u8 *) (&fw_current_inpsmode));
	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_FWLPS_RF_ON,
				      (u8 *) (&fw_ps_awake));

	अगर (ppsc->p2p_ps_info.p2p_ps_mode)
		fw_ps_awake = false;

	अगर ((ppsc->rfpwr_state == ERFON) && ((!fw_current_inpsmode) &&
					     fw_ps_awake)
	    && (!ppsc->rfchange_inprogress)) अणु
		rtl92c_dm_pwdb_monitor(hw);
		rtl92c_dm_dig(hw);
		rtl92c_dm_false_alarm_counter_statistics(hw);
		rtl92c_dm_dynamic_bb_घातersaving(hw);
		rtl92c_dm_dynamic_txघातer(hw);
		rtl92c_dm_check_txघातer_tracking(hw);
		/* rtl92c_dm_refresh_rate_adaptive_mask(hw); */
		rtl92c_dm_bt_coexist(hw);
		rtl92c_dm_check_edca_turbo(hw);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl92c_dm_watchकरोg);

u8 rtl92c_bt_rssi_state_change(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	दीर्घ undec_sm_pwdb;
	u8 curr_bt_rssi_state = 0x00;

	अगर (rtlpriv->mac80211.link_state == MAC80211_LINKED) अणु
		undec_sm_pwdb = GET_UNDECORATED_AVERAGE_RSSI(rtlpriv);
	पूर्ण अन्यथा अणु
		अगर (rtlpriv->dm.entry_min_undec_sm_pwdb == 0)
			undec_sm_pwdb = 100;
		अन्यथा
			undec_sm_pwdb = rtlpriv->dm.entry_min_undec_sm_pwdb;
	पूर्ण

	/* Check RSSI to determine HighPower/NormalPower state क्रम
	 * BT coexistence. */
	अगर (undec_sm_pwdb >= 67)
		curr_bt_rssi_state &= (~BT_RSSI_STATE_NORMAL_POWER);
	अन्यथा अगर (undec_sm_pwdb < 62)
		curr_bt_rssi_state |= BT_RSSI_STATE_NORMAL_POWER;

	/* Check RSSI to determine AMPDU setting क्रम BT coexistence. */
	अगर (undec_sm_pwdb >= 40)
		curr_bt_rssi_state &= (~BT_RSSI_STATE_AMDPU_OFF);
	अन्यथा अगर (undec_sm_pwdb <= 32)
		curr_bt_rssi_state |= BT_RSSI_STATE_AMDPU_OFF;

	/* Marked RSSI state. It will be used to determine BT coexistence
	 * setting later. */
	अगर (undec_sm_pwdb < 35)
		curr_bt_rssi_state |=  BT_RSSI_STATE_SPECIAL_LOW;
	अन्यथा
		curr_bt_rssi_state &= (~BT_RSSI_STATE_SPECIAL_LOW);

	/* Check BT state related to BT_Idle in B/G mode. */
	अगर (undec_sm_pwdb < 15)
		curr_bt_rssi_state |=  BT_RSSI_STATE_BG_EDCA_LOW;
	अन्यथा
		curr_bt_rssi_state &= (~BT_RSSI_STATE_BG_EDCA_LOW);

	अगर (curr_bt_rssi_state != rtlpriv->btcoexist.bt_rssi_state) अणु
		rtlpriv->btcoexist.bt_rssi_state = curr_bt_rssi_state;
		वापस true;
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl92c_bt_rssi_state_change);

अटल bool rtl92c_bt_state_change(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	u32 polling, ratio_tx, ratio_pri;
	u32 bt_tx, bt_pri;
	u8 bt_state;
	u8 cur_service_type;

	अगर (rtlpriv->mac80211.link_state < MAC80211_LINKED)
		वापस false;

	bt_state = rtl_पढ़ो_byte(rtlpriv, 0x4fd);
	bt_tx = rtl_पढ़ो_dword(rtlpriv, 0x488) & BT_MASK;
	bt_pri = rtl_पढ़ो_dword(rtlpriv, 0x48c) & BT_MASK;
	polling = rtl_पढ़ो_dword(rtlpriv, 0x490);

	अगर (bt_tx == BT_MASK && bt_pri == BT_MASK &&
	    polling == 0xffffffff && bt_state == 0xff)
		वापस false;

	bt_state &= BIT(0);
	अगर (bt_state != rtlpriv->btcoexist.bt_cur_state) अणु
		rtlpriv->btcoexist.bt_cur_state = bt_state;

		अगर (rtlpriv->btcoexist.reg_bt_sco == 3) अणु
			rtlpriv->btcoexist.bt_service = BT_IDLE;

			bt_state = bt_state |
			  ((rtlpriv->btcoexist.bt_ant_isolation == 1) ?
			  0 : BIT(1)) | BIT(2);
			rtl_ग_लिखो_byte(rtlpriv, 0x4fd, bt_state);
		पूर्ण
		वापस true;
	पूर्ण

	ratio_tx = bt_tx * 1000 / polling;
	ratio_pri = bt_pri * 1000 / polling;
	rtlpriv->btcoexist.ratio_tx = ratio_tx;
	rtlpriv->btcoexist.ratio_pri = ratio_pri;

	अगर (bt_state && rtlpriv->btcoexist.reg_bt_sco == 3) अणु

		अगर ((ratio_tx < 30)  && (ratio_pri < 30))
			cur_service_type = BT_IDLE;
		अन्यथा अगर ((ratio_pri > 110) && (ratio_pri < 250))
			cur_service_type = BT_SCO;
		अन्यथा अगर ((ratio_tx >= 200) && (ratio_pri >= 200))
			cur_service_type = BT_BUSY;
		अन्यथा अगर ((ratio_tx >= 350) && (ratio_tx < 500))
			cur_service_type = BT_OTHERBUSY;
		अन्यथा अगर (ratio_tx >= 500)
			cur_service_type = BT_PAN;
		अन्यथा
			cur_service_type = BT_OTHER_ACTION;

		अगर (cur_service_type != rtlpriv->btcoexist.bt_service) अणु
			rtlpriv->btcoexist.bt_service = cur_service_type;
			bt_state = bt_state |
			   ((rtlpriv->btcoexist.bt_ant_isolation == 1) ?
			   0 : BIT(1)) |
			   ((rtlpriv->btcoexist.bt_service != BT_IDLE) ?
			   0 : BIT(2));

			/* Add पूर्णांकerrupt migration when bt is not ini
			 * idle state (no traffic). */
			अगर (rtlpriv->btcoexist.bt_service != BT_IDLE) अणु
				rtl_ग_लिखो_word(rtlpriv, 0x504, 0x0ccc);
				rtl_ग_लिखो_byte(rtlpriv, 0x506, 0x54);
				rtl_ग_लिखो_byte(rtlpriv, 0x507, 0x54);
			पूर्ण अन्यथा अणु
				rtl_ग_लिखो_byte(rtlpriv, 0x506, 0x00);
				rtl_ग_लिखो_byte(rtlpriv, 0x507, 0x00);
			पूर्ण

			rtl_ग_लिखो_byte(rtlpriv, 0x4fd, bt_state);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;

पूर्ण

अटल bool rtl92c_bt_wअगरi_connect_change(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	अटल bool media_connect;

	अगर (rtlpriv->mac80211.link_state < MAC80211_LINKED) अणु
		media_connect = false;
	पूर्ण अन्यथा अणु
		अगर (!media_connect) अणु
			media_connect = true;
			वापस true;
		पूर्ण
		media_connect = true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम rtl92c_bt_set_normal(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtlpriv->btcoexist.bt_service == BT_OTHERBUSY) अणु
		rtlpriv->btcoexist.bt_edca_ul = 0x5ea72b;
		rtlpriv->btcoexist.bt_edca_dl = 0x5ea72b;
	पूर्ण अन्यथा अगर (rtlpriv->btcoexist.bt_service == BT_BUSY) अणु
		rtlpriv->btcoexist.bt_edca_ul = 0x5eb82f;
		rtlpriv->btcoexist.bt_edca_dl = 0x5eb82f;
	पूर्ण अन्यथा अगर (rtlpriv->btcoexist.bt_service == BT_SCO) अणु
		अगर (rtlpriv->btcoexist.ratio_tx > 160) अणु
			rtlpriv->btcoexist.bt_edca_ul = 0x5ea72f;
			rtlpriv->btcoexist.bt_edca_dl = 0x5ea72f;
		पूर्ण अन्यथा अणु
			rtlpriv->btcoexist.bt_edca_ul = 0x5ea32b;
			rtlpriv->btcoexist.bt_edca_dl = 0x5ea42b;
		पूर्ण
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.bt_edca_ul = 0;
		rtlpriv->btcoexist.bt_edca_dl = 0;
	पूर्ण

	अगर ((rtlpriv->btcoexist.bt_service != BT_IDLE) &&
	    (rtlpriv->mac80211.mode == WIRELESS_MODE_G ||
	     (rtlpriv->mac80211.mode == (WIRELESS_MODE_G | WIRELESS_MODE_B))) &&
	    (rtlpriv->btcoexist.bt_rssi_state &
	     BT_RSSI_STATE_BG_EDCA_LOW)) अणु
		rtlpriv->btcoexist.bt_edca_ul = 0x5eb82b;
		rtlpriv->btcoexist.bt_edca_dl = 0x5eb82b;
	पूर्ण
पूर्ण

अटल व्योम rtl92c_bt_ant_isolation(काष्ठा ieee80211_hw *hw, u8 पंचांगp1byte)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	/* Only enable HW BT coexist when BT in "Busy" state. */
	अगर (rtlpriv->mac80211.venकरोr == PEER_CISCO &&
	    rtlpriv->btcoexist.bt_service == BT_OTHER_ACTION) अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);
	पूर्ण अन्यथा अणु
		अगर ((rtlpriv->btcoexist.bt_service == BT_BUSY) &&
		    (rtlpriv->btcoexist.bt_rssi_state &
		     BT_RSSI_STATE_NORMAL_POWER)) अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);
		पूर्ण अन्यथा अगर ((rtlpriv->btcoexist.bt_service ==
			    BT_OTHER_ACTION) && (rtlpriv->mac80211.mode <
			    WIRELESS_MODE_N_24G) &&
			    (rtlpriv->btcoexist.bt_rssi_state &
			    BT_RSSI_STATE_SPECIAL_LOW)) अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG, 0xa0);
		पूर्ण अन्यथा अणु
			rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG, पंचांगp1byte);
		पूर्ण
	पूर्ण

	अगर (rtlpriv->btcoexist.bt_service == BT_PAN)
		rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x10100);
	अन्यथा
		rtl_ग_लिखो_dword(rtlpriv, REG_GPIO_PIN_CTRL, 0x0);

	अगर (rtlpriv->btcoexist.bt_rssi_state &
	    BT_RSSI_STATE_NORMAL_POWER) अणु
		rtl92c_bt_set_normal(hw);
	पूर्ण अन्यथा अणु
		rtlpriv->btcoexist.bt_edca_ul = 0;
		rtlpriv->btcoexist.bt_edca_dl = 0;
	पूर्ण

	अगर (rtlpriv->btcoexist.bt_service != BT_IDLE) अणु
		rtlpriv->cfg->ops->set_rfreg(hw,
				 RF90_PATH_A,
				 0x1e,
				 0xf0, 0xf);
	पूर्ण अन्यथा अणु
		rtlpriv->cfg->ops->set_rfreg(hw,
		     RF90_PATH_A, 0x1e, 0xf0,
		     rtlpriv->btcoexist.bt_rfreg_origin_1e);
	पूर्ण

	अगर (!rtlpriv->dm.dynamic_txघातer_enable) अणु
		अगर (rtlpriv->btcoexist.bt_service != BT_IDLE) अणु
			अगर (rtlpriv->btcoexist.bt_rssi_state &
				BT_RSSI_STATE_TXPOWER_LOW) अणु
				rtlpriv->dm.dynamic_txhighघातer_lvl =
							TXHIGHPWRLEVEL_BT2;
			पूर्ण अन्यथा अणु
				rtlpriv->dm.dynamic_txhighघातer_lvl =
					TXHIGHPWRLEVEL_BT1;
			पूर्ण
		पूर्ण अन्यथा अणु
			rtlpriv->dm.dynamic_txhighघातer_lvl =
				TXHIGHPWRLEVEL_NORMAL;
		पूर्ण
		rtl92c_phy_set_txघातer_level(hw,
			rtlpriv->phy.current_channel);
	पूर्ण
पूर्ण

अटल व्योम rtl92c_check_bt_change(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 पंचांगp1byte = 0;

	अगर (IS_81XXC_VENDOR_UMC_B_CUT(rtlhal->version) &&
	    rtlpriv->btcoexist.bt_coexistence)
		पंचांगp1byte |= BIT(5);
	अगर (rtlpriv->btcoexist.bt_cur_state) अणु
		अगर (rtlpriv->btcoexist.bt_ant_isolation)
			rtl92c_bt_ant_isolation(hw, पंचांगp1byte);
	पूर्ण अन्यथा अणु
		rtl_ग_लिखो_byte(rtlpriv, REG_GPIO_MUXCFG, पंचांगp1byte);
		rtlpriv->cfg->ops->set_rfreg(hw, RF90_PATH_A, 0x1e, 0xf0,
				rtlpriv->btcoexist.bt_rfreg_origin_1e);

		rtlpriv->btcoexist.bt_edca_ul = 0;
		rtlpriv->btcoexist.bt_edca_dl = 0;
	पूर्ण
पूर्ण

व्योम rtl92c_dm_bt_coexist(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool wअगरi_connect_change;
	bool bt_state_change;
	bool rssi_state_change;

	अगर ((rtlpriv->btcoexist.bt_coexistence) &&
	    (rtlpriv->btcoexist.bt_coexist_type == BT_CSR_BC4)) अणु
		wअगरi_connect_change = rtl92c_bt_wअगरi_connect_change(hw);
		bt_state_change = rtl92c_bt_state_change(hw);
		rssi_state_change = rtl92c_bt_rssi_state_change(hw);

		अगर (wअगरi_connect_change || bt_state_change || rssi_state_change)
			rtl92c_check_bt_change(hw);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl92c_dm_bt_coexist);
