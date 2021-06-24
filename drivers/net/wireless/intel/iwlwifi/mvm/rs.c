<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2005 - 2014, 2018 - 2021 Intel Corporation. All rights reserved.
 * Copyright(c) 2013 - 2015 Intel Mobile Communications GmbH
 * Copyright(c) 2016 - 2017 Intel Deutschland GmbH
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/
#समावेश <linux/kernel.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <net/mac80211.h>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/delay.h>

#समावेश <linux/workqueue.h>
#समावेश "rs.h"
#समावेश "fw-api.h"
#समावेश "sta.h"
#समावेश "iwl-op-mode.h"
#समावेश "mvm.h"
#समावेश "debugfs.h"

#घोषणा IWL_RATE_MAX_WINDOW		62	/* # tx in history winकरोw */

/* Calculations of success ratio are करोne in fixed poपूर्णांक where 12800 is 100%.
 * Use this macro when dealing with thresholds स्थिरs set as a percentage
 */
#घोषणा RS_PERCENT(x) (128 * x)

अटल u8 rs_ht_to_legacy[] = अणु
	[IWL_RATE_MCS_0_INDEX] = IWL_RATE_6M_INDEX,
	[IWL_RATE_MCS_1_INDEX] = IWL_RATE_9M_INDEX,
	[IWL_RATE_MCS_2_INDEX] = IWL_RATE_12M_INDEX,
	[IWL_RATE_MCS_3_INDEX] = IWL_RATE_18M_INDEX,
	[IWL_RATE_MCS_4_INDEX] = IWL_RATE_24M_INDEX,
	[IWL_RATE_MCS_5_INDEX] = IWL_RATE_36M_INDEX,
	[IWL_RATE_MCS_6_INDEX] = IWL_RATE_48M_INDEX,
	[IWL_RATE_MCS_7_INDEX] = IWL_RATE_54M_INDEX,
	[IWL_RATE_MCS_8_INDEX] = IWL_RATE_54M_INDEX,
	[IWL_RATE_MCS_9_INDEX] = IWL_RATE_54M_INDEX,
पूर्ण;

अटल स्थिर u8 ant_toggle_lookup[] = अणु
	[ANT_NONE] = ANT_NONE,
	[ANT_A] = ANT_B,
	[ANT_B] = ANT_A,
	[ANT_AB] = ANT_AB,
पूर्ण;

#घोषणा IWL_DECLARE_RATE_INFO(r, s, rp, rn)			      \
	[IWL_RATE_##r##M_INDEX] = अणु IWL_RATE_##r##M_PLCP,	      \
				    IWL_RATE_HT_SISO_MCS_##s##_PLCP,  \
				    IWL_RATE_HT_MIMO2_MCS_##s##_PLCP, \
				    IWL_RATE_VHT_SISO_MCS_##s##_PLCP, \
				    IWL_RATE_VHT_MIMO2_MCS_##s##_PLCP,\
				    IWL_RATE_##rp##M_INDEX,	      \
				    IWL_RATE_##rn##M_INDEX पूर्ण

#घोषणा IWL_DECLARE_MCS_RATE(s)						  \
	[IWL_RATE_MCS_##s##_INDEX] = अणु IWL_RATE_INVM_PLCP,		  \
				       IWL_RATE_HT_SISO_MCS_##s##_PLCP,	  \
				       IWL_RATE_HT_MIMO2_MCS_##s##_PLCP,  \
				       IWL_RATE_VHT_SISO_MCS_##s##_PLCP,  \
				       IWL_RATE_VHT_MIMO2_MCS_##s##_PLCP, \
				       IWL_RATE_INVM_INDEX,	          \
				       IWL_RATE_INVM_INDEX पूर्ण

/*
 * Parameter order:
 *   rate, ht rate, prev rate, next rate
 *
 * If there isn't a valid next or previous rate then INV is used which
 * maps to IWL_RATE_INVALID
 *
 */
अटल स्थिर काष्ठा iwl_rs_rate_info iwl_rates[IWL_RATE_COUNT] = अणु
	IWL_DECLARE_RATE_INFO(1, INV, INV, 2),   /*  1mbps */
	IWL_DECLARE_RATE_INFO(2, INV, 1, 5),     /*  2mbps */
	IWL_DECLARE_RATE_INFO(5, INV, 2, 11),    /*5.5mbps */
	IWL_DECLARE_RATE_INFO(11, INV, 9, 12),   /* 11mbps */
	IWL_DECLARE_RATE_INFO(6, 0, 5, 11),      /*  6mbps ; MCS 0 */
	IWL_DECLARE_RATE_INFO(9, INV, 6, 11),    /*  9mbps */
	IWL_DECLARE_RATE_INFO(12, 1, 11, 18),    /* 12mbps ; MCS 1 */
	IWL_DECLARE_RATE_INFO(18, 2, 12, 24),    /* 18mbps ; MCS 2 */
	IWL_DECLARE_RATE_INFO(24, 3, 18, 36),    /* 24mbps ; MCS 3 */
	IWL_DECLARE_RATE_INFO(36, 4, 24, 48),    /* 36mbps ; MCS 4 */
	IWL_DECLARE_RATE_INFO(48, 5, 36, 54),    /* 48mbps ; MCS 5 */
	IWL_DECLARE_RATE_INFO(54, 6, 48, INV),   /* 54mbps ; MCS 6 */
	IWL_DECLARE_MCS_RATE(7),                 /* MCS 7 */
	IWL_DECLARE_MCS_RATE(8),                 /* MCS 8 */
	IWL_DECLARE_MCS_RATE(9),                 /* MCS 9 */
पूर्ण;

क्रमागत rs_action अणु
	RS_ACTION_STAY = 0,
	RS_ACTION_DOWNSCALE = -1,
	RS_ACTION_UPSCALE = 1,
पूर्ण;

क्रमागत rs_column_mode अणु
	RS_INVALID = 0,
	RS_LEGACY,
	RS_SISO,
	RS_MIMO2,
पूर्ण;

#घोषणा MAX_NEXT_COLUMNS 7
#घोषणा MAX_COLUMN_CHECKS 3

काष्ठा rs_tx_column;

प्रकार bool (*allow_column_func_t) (काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_sta *sta,
				     काष्ठा rs_rate *rate,
				     स्थिर काष्ठा rs_tx_column *next_col);

काष्ठा rs_tx_column अणु
	क्रमागत rs_column_mode mode;
	u8 ant;
	bool sgi;
	क्रमागत rs_column next_columns[MAX_NEXT_COLUMNS];
	allow_column_func_t checks[MAX_COLUMN_CHECKS];
पूर्ण;

अटल bool rs_ant_allow(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			 काष्ठा rs_rate *rate,
			 स्थिर काष्ठा rs_tx_column *next_col)
अणु
	वापस iwl_mvm_bt_coex_is_ant_avail(mvm, next_col->ant);
पूर्ण

अटल bool rs_mimo_allow(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			  काष्ठा rs_rate *rate,
			  स्थिर काष्ठा rs_tx_column *next_col)
अणु
	अगर (!sta->ht_cap.ht_supported)
		वापस false;

	अगर (sta->smps_mode == IEEE80211_SMPS_STATIC)
		वापस false;

	अगर (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) < 2)
		वापस false;

	अगर (!iwl_mvm_bt_coex_is_mimo_allowed(mvm, sta))
		वापस false;

	अगर (mvm->nvm_data->sku_cap_mimo_disabled)
		वापस false;

	वापस true;
पूर्ण

अटल bool rs_siso_allow(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			  काष्ठा rs_rate *rate,
			  स्थिर काष्ठा rs_tx_column *next_col)
अणु
	अगर (!sta->ht_cap.ht_supported)
		वापस false;

	वापस true;
पूर्ण

अटल bool rs_sgi_allow(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			 काष्ठा rs_rate *rate,
			 स्थिर काष्ठा rs_tx_column *next_col)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;

	अगर (is_ht20(rate) && (ht_cap->cap &
			     IEEE80211_HT_CAP_SGI_20))
		वापस true;
	अगर (is_ht40(rate) && (ht_cap->cap &
			     IEEE80211_HT_CAP_SGI_40))
		वापस true;
	अगर (is_ht80(rate) && (vht_cap->cap &
			     IEEE80211_VHT_CAP_SHORT_GI_80))
		वापस true;
	अगर (is_ht160(rate) && (vht_cap->cap &
			     IEEE80211_VHT_CAP_SHORT_GI_160))
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा rs_tx_column rs_tx_columns[] = अणु
	[RS_COLUMN_LEGACY_ANT_A] = अणु
		.mode = RS_LEGACY,
		.ant = ANT_A,
		.next_columns = अणु
			RS_COLUMN_LEGACY_ANT_B,
			RS_COLUMN_SISO_ANT_A,
			RS_COLUMN_MIMO2,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_ant_allow,
		पूर्ण,
	पूर्ण,
	[RS_COLUMN_LEGACY_ANT_B] = अणु
		.mode = RS_LEGACY,
		.ant = ANT_B,
		.next_columns = अणु
			RS_COLUMN_LEGACY_ANT_A,
			RS_COLUMN_SISO_ANT_B,
			RS_COLUMN_MIMO2,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_ant_allow,
		पूर्ण,
	पूर्ण,
	[RS_COLUMN_SISO_ANT_A] = अणु
		.mode = RS_SISO,
		.ant = ANT_A,
		.next_columns = अणु
			RS_COLUMN_SISO_ANT_B,
			RS_COLUMN_MIMO2,
			RS_COLUMN_SISO_ANT_A_SGI,
			RS_COLUMN_LEGACY_ANT_A,
			RS_COLUMN_LEGACY_ANT_B,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_siso_allow,
			rs_ant_allow,
		पूर्ण,
	पूर्ण,
	[RS_COLUMN_SISO_ANT_B] = अणु
		.mode = RS_SISO,
		.ant = ANT_B,
		.next_columns = अणु
			RS_COLUMN_SISO_ANT_A,
			RS_COLUMN_MIMO2,
			RS_COLUMN_SISO_ANT_B_SGI,
			RS_COLUMN_LEGACY_ANT_A,
			RS_COLUMN_LEGACY_ANT_B,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_siso_allow,
			rs_ant_allow,
		पूर्ण,
	पूर्ण,
	[RS_COLUMN_SISO_ANT_A_SGI] = अणु
		.mode = RS_SISO,
		.ant = ANT_A,
		.sgi = true,
		.next_columns = अणु
			RS_COLUMN_SISO_ANT_B_SGI,
			RS_COLUMN_MIMO2_SGI,
			RS_COLUMN_SISO_ANT_A,
			RS_COLUMN_LEGACY_ANT_A,
			RS_COLUMN_LEGACY_ANT_B,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_siso_allow,
			rs_ant_allow,
			rs_sgi_allow,
		पूर्ण,
	पूर्ण,
	[RS_COLUMN_SISO_ANT_B_SGI] = अणु
		.mode = RS_SISO,
		.ant = ANT_B,
		.sgi = true,
		.next_columns = अणु
			RS_COLUMN_SISO_ANT_A_SGI,
			RS_COLUMN_MIMO2_SGI,
			RS_COLUMN_SISO_ANT_B,
			RS_COLUMN_LEGACY_ANT_A,
			RS_COLUMN_LEGACY_ANT_B,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_siso_allow,
			rs_ant_allow,
			rs_sgi_allow,
		पूर्ण,
	पूर्ण,
	[RS_COLUMN_MIMO2] = अणु
		.mode = RS_MIMO2,
		.ant = ANT_AB,
		.next_columns = अणु
			RS_COLUMN_SISO_ANT_A,
			RS_COLUMN_MIMO2_SGI,
			RS_COLUMN_LEGACY_ANT_A,
			RS_COLUMN_LEGACY_ANT_B,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_mimo_allow,
		पूर्ण,
	पूर्ण,
	[RS_COLUMN_MIMO2_SGI] = अणु
		.mode = RS_MIMO2,
		.ant = ANT_AB,
		.sgi = true,
		.next_columns = अणु
			RS_COLUMN_SISO_ANT_A_SGI,
			RS_COLUMN_MIMO2,
			RS_COLUMN_LEGACY_ANT_A,
			RS_COLUMN_LEGACY_ANT_B,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
			RS_COLUMN_INVALID,
		पूर्ण,
		.checks = अणु
			rs_mimo_allow,
			rs_sgi_allow,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल अंतरभूत u8 rs_extract_rate(u32 rate_n_flags)
अणु
	/* also works क्रम HT because bits 7:6 are zero there */
	वापस (u8)(rate_n_flags & RATE_LEGACY_RATE_MSK);
पूर्ण

अटल पूर्णांक iwl_hwrate_to_plcp_idx(u32 rate_n_flags)
अणु
	पूर्णांक idx = 0;

	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		idx = rate_n_flags & RATE_HT_MCS_RATE_CODE_MSK;
		idx += IWL_RATE_MCS_0_INDEX;

		/* skip 9M not supported in HT*/
		अगर (idx >= IWL_RATE_9M_INDEX)
			idx += 1;
		अगर ((idx >= IWL_FIRST_HT_RATE) && (idx <= IWL_LAST_HT_RATE))
			वापस idx;
	पूर्ण अन्यथा अगर (rate_n_flags & RATE_MCS_VHT_MSK ||
		   rate_n_flags & RATE_MCS_HE_MSK) अणु
		idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
		idx += IWL_RATE_MCS_0_INDEX;

		/* skip 9M not supported in VHT*/
		अगर (idx >= IWL_RATE_9M_INDEX)
			idx++;
		अगर ((idx >= IWL_FIRST_VHT_RATE) && (idx <= IWL_LAST_VHT_RATE))
			वापस idx;
		अगर ((rate_n_flags & RATE_MCS_HE_MSK) &&
		    (idx <= IWL_LAST_HE_RATE))
			वापस idx;
	पूर्ण अन्यथा अणु
		/* legacy rate क्रमmat, search क्रम match in table */

		u8 legacy_rate = rs_extract_rate(rate_n_flags);
		क्रम (idx = 0; idx < ARRAY_SIZE(iwl_rates); idx++)
			अगर (iwl_rates[idx].plcp == legacy_rate)
				वापस idx;
	पूर्ण

	वापस IWL_RATE_INVALID;
पूर्ण

अटल व्योम rs_rate_scale_perक्रमm(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा iwl_lq_sta *lq_sta,
				  पूर्णांक tid, bool ndp);
अटल व्योम rs_fill_lq_cmd(काष्ठा iwl_mvm *mvm,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा iwl_lq_sta *lq_sta,
			   स्थिर काष्ठा rs_rate *initial_rate);
अटल व्योम rs_stay_in_table(काष्ठा iwl_lq_sta *lq_sta, bool क्रमce_search);

/*
 * The following tables contain the expected throughput metrics क्रम all rates
 *
 *	1, 2, 5.5, 11, 6, 9, 12, 18, 24, 36, 48, 54, 60 MBits
 *
 * where invalid entries are zeros.
 *
 * CCK rates are only valid in legacy table and will only be used in G
 * (2.4 GHz) band.
 */
अटल स्थिर u16 expected_tpt_legacy[IWL_RATE_COUNT] = अणु
	7, 13, 35, 58, 40, 57, 72, 98, 121, 154, 177, 186, 0, 0, 0
पूर्ण;

/* Expected TpT tables. 4 indexes:
 * 0 - NGI, 1 - SGI, 2 - AGG+NGI, 3 - AGG+SGI
 */
अटल स्थिर u16 expected_tpt_siso_20MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 42, 0,  76, 102, 124, 159, 183, 193, 202, 216, 0पूर्ण,
	अणु0, 0, 0, 0, 46, 0,  82, 110, 132, 168, 192, 202, 210, 225, 0पूर्ण,
	अणु0, 0, 0, 0, 49, 0,  97, 145, 192, 285, 375, 420, 464, 551, 0पूर्ण,
	अणु0, 0, 0, 0, 54, 0, 108, 160, 213, 315, 415, 465, 513, 608, 0पूर्ण,
पूर्ण;

अटल स्थिर u16 expected_tpt_siso_40MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0,  77, 0, 127, 160, 184, 220, 242, 250,  257,  269,  275पूर्ण,
	अणु0, 0, 0, 0,  83, 0, 135, 169, 193, 229, 250, 257,  264,  275,  280पूर्ण,
	अणु0, 0, 0, 0, 101, 0, 199, 295, 389, 570, 744, 828,  911, 1070, 1173पूर्ण,
	अणु0, 0, 0, 0, 112, 0, 220, 326, 429, 629, 819, 912, 1000, 1173, 1284पूर्ण,
पूर्ण;

अटल स्थिर u16 expected_tpt_siso_80MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 130, 0, 191, 223, 244,  273,  288,  294,  298,  305,  308पूर्ण,
	अणु0, 0, 0, 0, 138, 0, 200, 231, 251,  279,  293,  298,  302,  308,  312पूर्ण,
	अणु0, 0, 0, 0, 217, 0, 429, 634, 834, 1220, 1585, 1760, 1931, 2258, 2466पूर्ण,
	अणु0, 0, 0, 0, 241, 0, 475, 701, 921, 1343, 1741, 1931, 2117, 2468, 2691पूर्ण,
पूर्ण;

अटल स्थिर u16 expected_tpt_siso_160MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 191, 0, 244, 288,  298,  308,  313,  318,  323,  328,  330पूर्ण,
	अणु0, 0, 0, 0, 200, 0, 251, 293,  302,  312,  317,  322,  327,  332,  334पूर्ण,
	अणु0, 0, 0, 0, 439, 0, 875, 1307, 1736, 2584, 3419, 3831, 4240, 5049, 5581पूर्ण,
	अणु0, 0, 0, 0, 488, 0, 972, 1451, 1925, 2864, 3785, 4240, 4691, 5581, 6165पूर्ण,
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo2_20MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0,  74, 0, 123, 155, 179, 213, 235, 243, 250,  261, 0पूर्ण,
	अणु0, 0, 0, 0,  81, 0, 131, 164, 187, 221, 242, 250, 256,  267, 0पूर्ण,
	अणु0, 0, 0, 0,  98, 0, 193, 286, 375, 550, 718, 799, 878, 1032, 0पूर्ण,
	अणु0, 0, 0, 0, 109, 0, 214, 316, 414, 607, 790, 879, 965, 1132, 0पूर्ण,
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo2_40MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 123, 0, 182, 214, 235,  264,  279,  285,  289,  296,  300पूर्ण,
	अणु0, 0, 0, 0, 131, 0, 191, 222, 242,  270,  284,  289,  293,  300,  303पूर्ण,
	अणु0, 0, 0, 0, 200, 0, 390, 571, 741, 1067, 1365, 1505, 1640, 1894, 2053पूर्ण,
	अणु0, 0, 0, 0, 221, 0, 430, 630, 816, 1169, 1490, 1641, 1784, 2053, 2221पूर्ण,
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo2_80MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 182, 0, 240,  264,  278,  299,  308,  311,  313,  317,  319पूर्ण,
	अणु0, 0, 0, 0, 190, 0, 247,  269,  282,  302,  310,  313,  315,  319,  320पूर्ण,
	अणु0, 0, 0, 0, 428, 0, 833, 1215, 1577, 2254, 2863, 3147, 3418, 3913, 4219पूर्ण,
	अणु0, 0, 0, 0, 474, 0, 920, 1338, 1732, 2464, 3116, 3418, 3705, 4225, 4545पूर्ण,
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo2_160MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 240, 0, 278,  308,  313,  319,  322,  324,  328,  330,   334पूर्ण,
	अणु0, 0, 0, 0, 247, 0, 282,  310,  315,  320,  323,  325,  329,  332,   338पूर्ण,
	अणु0, 0, 0, 0, 875, 0, 1735, 2582, 3414, 5043, 6619, 7389, 8147, 9629,  10592पूर्ण,
	अणु0, 0, 0, 0, 971, 0, 1925, 2861, 3779, 5574, 7304, 8147, 8976, 10592, 11640पूर्ण,
पूर्ण;

/* mbps, mcs */
अटल स्थिर काष्ठा iwl_rate_mcs_info iwl_rate_mcs[IWL_RATE_COUNT] = अणु
	अणु  "1", "BPSK DSSS"पूर्ण,
	अणु  "2", "QPSK DSSS"पूर्ण,
	अणु"5.5", "BPSK CCK"पूर्ण,
	अणु "11", "QPSK CCK"पूर्ण,
	अणु  "6", "BPSK 1/2"पूर्ण,
	अणु  "9", "BPSK 1/2"पूर्ण,
	अणु "12", "QPSK 1/2"पूर्ण,
	अणु "18", "QPSK 3/4"पूर्ण,
	अणु "24", "16QAM 1/2"पूर्ण,
	अणु "36", "16QAM 3/4"पूर्ण,
	अणु "48", "64QAM 2/3"पूर्ण,
	अणु "54", "64QAM 3/4"पूर्ण,
	अणु "60", "64QAM 5/6"पूर्ण,
पूर्ण;

#घोषणा MCS_INDEX_PER_STREAM	(8)

अटल स्थिर अक्षर *rs_pretty_ant(u8 ant)
अणु
	अटल स्थिर अक्षर * स्थिर ant_name[] = अणु
		[ANT_NONE] = "None",
		[ANT_A]    = "A",
		[ANT_B]    = "B",
		[ANT_AB]   = "AB",
		[ANT_C]    = "C",
		[ANT_AC]   = "AC",
		[ANT_BC]   = "BC",
		[ANT_ABC]  = "ABC",
	पूर्ण;

	अगर (ant > ANT_ABC)
		वापस "UNKNOWN";

	वापस ant_name[ant];
पूर्ण

अटल स्थिर अक्षर *rs_pretty_lq_type(क्रमागत iwl_table_type type)
अणु
	अटल स्थिर अक्षर * स्थिर lq_types[] = अणु
		[LQ_NONE] = "NONE",
		[LQ_LEGACY_A] = "LEGACY_A",
		[LQ_LEGACY_G] = "LEGACY_G",
		[LQ_HT_SISO] = "HT SISO",
		[LQ_HT_MIMO2] = "HT MIMO",
		[LQ_VHT_SISO] = "VHT SISO",
		[LQ_VHT_MIMO2] = "VHT MIMO",
		[LQ_HE_SISO] = "HE SISO",
		[LQ_HE_MIMO2] = "HE MIMO",
	पूर्ण;

	अगर (type < LQ_NONE || type >= LQ_MAX)
		वापस "UNKNOWN";

	वापस lq_types[type];
पूर्ण

अटल अक्षर *rs_pretty_rate(स्थिर काष्ठा rs_rate *rate)
अणु
	अटल अक्षर buf[40];
	अटल स्थिर अक्षर * स्थिर legacy_rates[] = अणु
		[IWL_RATE_1M_INDEX] = "1M",
		[IWL_RATE_2M_INDEX] = "2M",
		[IWL_RATE_5M_INDEX] = "5.5M",
		[IWL_RATE_11M_INDEX] = "11M",
		[IWL_RATE_6M_INDEX] = "6M",
		[IWL_RATE_9M_INDEX] = "9M",
		[IWL_RATE_12M_INDEX] = "12M",
		[IWL_RATE_18M_INDEX] = "18M",
		[IWL_RATE_24M_INDEX] = "24M",
		[IWL_RATE_36M_INDEX] = "36M",
		[IWL_RATE_48M_INDEX] = "48M",
		[IWL_RATE_54M_INDEX] = "54M",
	पूर्ण;
	अटल स्थिर अक्षर *स्थिर ht_vht_rates[] = अणु
		[IWL_RATE_MCS_0_INDEX] = "MCS0",
		[IWL_RATE_MCS_1_INDEX] = "MCS1",
		[IWL_RATE_MCS_2_INDEX] = "MCS2",
		[IWL_RATE_MCS_3_INDEX] = "MCS3",
		[IWL_RATE_MCS_4_INDEX] = "MCS4",
		[IWL_RATE_MCS_5_INDEX] = "MCS5",
		[IWL_RATE_MCS_6_INDEX] = "MCS6",
		[IWL_RATE_MCS_7_INDEX] = "MCS7",
		[IWL_RATE_MCS_8_INDEX] = "MCS8",
		[IWL_RATE_MCS_9_INDEX] = "MCS9",
	पूर्ण;
	स्थिर अक्षर *rate_str;

	अगर (is_type_legacy(rate->type) && (rate->index <= IWL_RATE_54M_INDEX))
		rate_str = legacy_rates[rate->index];
	अन्यथा अगर ((is_type_ht(rate->type) || is_type_vht(rate->type)) &&
		 (rate->index >= IWL_RATE_MCS_0_INDEX) &&
		 (rate->index <= IWL_RATE_MCS_9_INDEX))
		rate_str = ht_vht_rates[rate->index];
	अन्यथा
		rate_str = "BAD_RATE";

	प्र_लिखो(buf, "(%s|%s|%s)", rs_pretty_lq_type(rate->type),
		rs_pretty_ant(rate->ant), rate_str);
	वापस buf;
पूर्ण

अटल अंतरभूत व्योम rs_dump_rate(काष्ठा iwl_mvm *mvm, स्थिर काष्ठा rs_rate *rate,
				स्थिर अक्षर *prefix)
अणु
	IWL_DEBUG_RATE(mvm,
		       "%s: %s BW: %d SGI: %d LDPC: %d STBC: %d\n",
		       prefix, rs_pretty_rate(rate), rate->bw,
		       rate->sgi, rate->ldpc, rate->stbc);
पूर्ण

अटल व्योम rs_rate_scale_clear_winकरोw(काष्ठा iwl_rate_scale_data *winकरोw)
अणु
	winकरोw->data = 0;
	winकरोw->success_counter = 0;
	winकरोw->success_ratio = IWL_INVALID_VALUE;
	winकरोw->counter = 0;
	winकरोw->average_tpt = IWL_INVALID_VALUE;
पूर्ण

अटल व्योम rs_rate_scale_clear_tbl_winकरोws(काष्ठा iwl_mvm *mvm,
					    काष्ठा iwl_scale_tbl_info *tbl)
अणु
	पूर्णांक i;

	IWL_DEBUG_RATE(mvm, "Clearing up window stats\n");
	क्रम (i = 0; i < IWL_RATE_COUNT; i++)
		rs_rate_scale_clear_winकरोw(&tbl->win[i]);

	क्रम (i = 0; i < ARRAY_SIZE(tbl->tpc_win); i++)
		rs_rate_scale_clear_winकरोw(&tbl->tpc_win[i]);
पूर्ण

अटल अंतरभूत u8 rs_is_valid_ant(u8 valid_antenna, u8 ant_type)
अणु
	वापस (ant_type & valid_antenna) == ant_type;
पूर्ण

अटल पूर्णांक rs_tl_turn_on_agg_क्रम_tid(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_lq_sta *lq_data, u8 tid,
				     काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक ret;

	IWL_DEBUG_HT(mvm, "Starting Tx agg: STA: %pM tid: %d\n",
		     sta->addr, tid);

	/* start BA session until the peer sends del BA */
	ret = ieee80211_start_tx_ba_session(sta, tid, 0);
	अगर (ret == -EAGAIN) अणु
		/*
		 * driver and mac80211 is out of sync
		 * this might be cause by reloading firmware
		 * stop the tx ba session here
		 */
		IWL_ERR(mvm, "Fail start Tx agg on tid: %d\n",
			tid);
		ieee80211_stop_tx_ba_session(sta, tid);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rs_tl_turn_on_agg(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
			      u8 tid, काष्ठा iwl_lq_sta *lq_sta,
			      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा iwl_mvm_tid_data *tid_data;

	/*
	 * In AP mode, tid can be equal to IWL_MAX_TID_COUNT
	 * when the frame is not QoS
	 */
	अगर (WARN_ON_ONCE(tid > IWL_MAX_TID_COUNT)) अणु
		IWL_ERR(mvm, "tid exceeds max TID count: %d/%d\n",
			tid, IWL_MAX_TID_COUNT);
		वापस;
	पूर्ण अन्यथा अगर (tid == IWL_MAX_TID_COUNT) अणु
		वापस;
	पूर्ण

	tid_data = &mvmsta->tid_data[tid];
	अगर (mvmsta->sta_state >= IEEE80211_STA_AUTHORIZED &&
	    tid_data->state == IWL_AGG_OFF &&
	    (lq_sta->tx_agg_tid_en & BIT(tid)) &&
	    tid_data->tx_count_last >= IWL_MVM_RS_AGG_START_THRESHOLD) अणु
		IWL_DEBUG_RATE(mvm, "try to aggregate tid %d\n", tid);
		अगर (rs_tl_turn_on_agg_क्रम_tid(mvm, lq_sta, tid, sta) == 0)
			tid_data->state = IWL_AGG_QUEUED;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक get_num_of_ant_from_rate(u32 rate_n_flags)
अणु
	वापस !!(rate_n_flags & RATE_MCS_ANT_A_MSK) +
	       !!(rate_n_flags & RATE_MCS_ANT_B_MSK) +
	       !!(rate_n_flags & RATE_MCS_ANT_C_MSK);
पूर्ण

/*
 * Static function to get the expected throughput from an iwl_scale_tbl_info
 * that wraps a शून्य poपूर्णांकer check
 */
अटल s32 get_expected_tpt(काष्ठा iwl_scale_tbl_info *tbl, पूर्णांक rs_index)
अणु
	अगर (tbl->expected_tpt)
		वापस tbl->expected_tpt[rs_index];
	वापस 0;
पूर्ण

/*
 * rs_collect_tx_data - Update the success/failure sliding winकरोw
 *
 * We keep a sliding winकरोw of the last 62 packets transmitted
 * at this rate.  winकरोw->data contains the biपंचांगask of successful
 * packets.
 */
अटल पूर्णांक _rs_collect_tx_data(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_scale_tbl_info *tbl,
			       पूर्णांक scale_index, पूर्णांक attempts, पूर्णांक successes,
			       काष्ठा iwl_rate_scale_data *winकरोw)
अणु
	अटल स्थिर u64 mask = (((u64)1) << (IWL_RATE_MAX_WINDOW - 1));
	s32 fail_count, tpt;

	/* Get expected throughput */
	tpt = get_expected_tpt(tbl, scale_index);

	/*
	 * Keep track of only the latest 62 tx frame attempts in this rate's
	 * history winकरोw; anything older isn't really relevant any more.
	 * If we have filled up the sliding winकरोw, drop the oldest attempt;
	 * अगर the oldest attempt (highest bit in biपंचांगap) shows "success",
	 * subtract "1" from the success counter (this is the मुख्य reason
	 * we keep these biपंचांगaps!).
	 */
	जबतक (attempts > 0) अणु
		अगर (winकरोw->counter >= IWL_RATE_MAX_WINDOW) अणु
			/* हटाओ earliest */
			winकरोw->counter = IWL_RATE_MAX_WINDOW - 1;

			अगर (winकरोw->data & mask) अणु
				winकरोw->data &= ~mask;
				winकरोw->success_counter--;
			पूर्ण
		पूर्ण

		/* Increment frames-attempted counter */
		winकरोw->counter++;

		/* Shअगरt biपंचांगap by one frame to throw away oldest history */
		winकरोw->data <<= 1;

		/* Mark the most recent #successes attempts as successful */
		अगर (successes > 0) अणु
			winकरोw->success_counter++;
			winकरोw->data |= 0x1;
			successes--;
		पूर्ण

		attempts--;
	पूर्ण

	/* Calculate current success ratio, aव्योम भागide-by-0! */
	अगर (winकरोw->counter > 0)
		winकरोw->success_ratio = 128 * (100 * winकरोw->success_counter)
					/ winकरोw->counter;
	अन्यथा
		winकरोw->success_ratio = IWL_INVALID_VALUE;

	fail_count = winकरोw->counter - winकरोw->success_counter;

	/* Calculate average throughput, अगर we have enough history. */
	अगर ((fail_count >= IWL_MVM_RS_RATE_MIN_FAILURE_TH) ||
	    (winकरोw->success_counter >= IWL_MVM_RS_RATE_MIN_SUCCESS_TH))
		winकरोw->average_tpt = (winकरोw->success_ratio * tpt + 64) / 128;
	अन्यथा
		winकरोw->average_tpt = IWL_INVALID_VALUE;

	वापस 0;
पूर्ण

अटल पूर्णांक rs_collect_tpc_data(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_lq_sta *lq_sta,
			       काष्ठा iwl_scale_tbl_info *tbl,
			       पूर्णांक scale_index, पूर्णांक attempts, पूर्णांक successes,
			       u8 reduced_txp)
अणु
	काष्ठा iwl_rate_scale_data *winकरोw = शून्य;

	अगर (WARN_ON_ONCE(reduced_txp > TPC_MAX_REDUCTION))
		वापस -EINVAL;

	winकरोw = &tbl->tpc_win[reduced_txp];
	वापस  _rs_collect_tx_data(mvm, tbl, scale_index, attempts, successes,
				    winकरोw);
पूर्ण

अटल व्योम rs_update_tid_tpt_stats(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_mvm_sta *mvmsta,
				    u8 tid, पूर्णांक successes)
अणु
	काष्ठा iwl_mvm_tid_data *tid_data;

	अगर (tid >= IWL_MAX_TID_COUNT)
		वापस;

	tid_data = &mvmsta->tid_data[tid];

	/*
	 * Measure अगर there're enough successful transmits per second.
	 * These statistics are used only to decide अगर we can start a
	 * BA session, so it should be updated only when A-MPDU is
	 * off.
	 */
	अगर (tid_data->state != IWL_AGG_OFF)
		वापस;

	अगर (समय_is_beक्रमe_jअगरfies(tid_data->tpt_meas_start + HZ) ||
	    (tid_data->tx_count >= IWL_MVM_RS_AGG_START_THRESHOLD)) अणु
		tid_data->tx_count_last = tid_data->tx_count;
		tid_data->tx_count = 0;
		tid_data->tpt_meas_start = jअगरfies;
	पूर्ण अन्यथा अणु
		tid_data->tx_count += successes;
	पूर्ण
पूर्ण

अटल पूर्णांक rs_collect_tlc_data(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_mvm_sta *mvmsta, u8 tid,
			       काष्ठा iwl_scale_tbl_info *tbl,
			       पूर्णांक scale_index, पूर्णांक attempts, पूर्णांक successes)
अणु
	काष्ठा iwl_rate_scale_data *winकरोw = शून्य;

	अगर (scale_index < 0 || scale_index >= IWL_RATE_COUNT)
		वापस -EINVAL;

	अगर (tbl->column != RS_COLUMN_INVALID) अणु
		काष्ठा lq_sta_pers *pers = &mvmsta->lq_sta.rs_drv.pers;

		pers->tx_stats[tbl->column][scale_index].total += attempts;
		pers->tx_stats[tbl->column][scale_index].success += successes;
	पूर्ण

	rs_update_tid_tpt_stats(mvm, mvmsta, tid, successes);

	/* Select winकरोw क्रम current tx bit rate */
	winकरोw = &(tbl->win[scale_index]);
	वापस _rs_collect_tx_data(mvm, tbl, scale_index, attempts, successes,
				   winकरोw);
पूर्ण

/* Convert rs_rate object पूर्णांकo ucode rate biपंचांगask */
अटल u32 ucode_rate_from_rs_rate(काष्ठा iwl_mvm *mvm,
				  काष्ठा rs_rate *rate)
अणु
	u32 ucode_rate = 0;
	पूर्णांक index = rate->index;

	ucode_rate |= ((rate->ant << RATE_MCS_ANT_POS) &
			 RATE_MCS_ANT_ABC_MSK);

	अगर (is_legacy(rate)) अणु
		ucode_rate |= iwl_rates[index].plcp;
		अगर (index >= IWL_FIRST_CCK_RATE && index <= IWL_LAST_CCK_RATE)
			ucode_rate |= RATE_MCS_CCK_MSK;
		वापस ucode_rate;
	पूर्ण

	/* set RTS protection क्रम all non legacy rates
	 * This helps with congested environments reducing the conflict cost to
	 * RTS retries only, instead of the entire BA packet.
	 */
	ucode_rate |= RATE_MCS_RTS_REQUIRED_MSK;

	अगर (is_ht(rate)) अणु
		अगर (index < IWL_FIRST_HT_RATE || index > IWL_LAST_HT_RATE) अणु
			IWL_ERR(mvm, "Invalid HT rate index %d\n", index);
			index = IWL_LAST_HT_RATE;
		पूर्ण
		ucode_rate |= RATE_MCS_HT_MSK;

		अगर (is_ht_siso(rate))
			ucode_rate |= iwl_rates[index].plcp_ht_siso;
		अन्यथा अगर (is_ht_mimo2(rate))
			ucode_rate |= iwl_rates[index].plcp_ht_mimo2;
		अन्यथा
			WARN_ON_ONCE(1);
	पूर्ण अन्यथा अगर (is_vht(rate)) अणु
		अगर (index < IWL_FIRST_VHT_RATE || index > IWL_LAST_VHT_RATE) अणु
			IWL_ERR(mvm, "Invalid VHT rate index %d\n", index);
			index = IWL_LAST_VHT_RATE;
		पूर्ण
		ucode_rate |= RATE_MCS_VHT_MSK;
		अगर (is_vht_siso(rate))
			ucode_rate |= iwl_rates[index].plcp_vht_siso;
		अन्यथा अगर (is_vht_mimo2(rate))
			ucode_rate |= iwl_rates[index].plcp_vht_mimo2;
		अन्यथा
			WARN_ON_ONCE(1);

	पूर्ण अन्यथा अणु
		IWL_ERR(mvm, "Invalid rate->type %d\n", rate->type);
	पूर्ण

	अगर (is_siso(rate) && rate->stbc) अणु
		/* To enable STBC we need to set both a flag and ANT_AB */
		ucode_rate |= RATE_MCS_ANT_AB_MSK;
		ucode_rate |= RATE_MCS_STBC_MSK;
	पूर्ण

	ucode_rate |= rate->bw;
	अगर (rate->sgi)
		ucode_rate |= RATE_MCS_SGI_MSK;
	अगर (rate->ldpc)
		ucode_rate |= RATE_MCS_LDPC_MSK;

	वापस ucode_rate;
पूर्ण

/* Convert a ucode rate पूर्णांकo an rs_rate object */
अटल पूर्णांक rs_rate_from_ucode_rate(स्थिर u32 ucode_rate,
				   क्रमागत nl80211_band band,
				   काष्ठा rs_rate *rate)
अणु
	u32 ant_msk = ucode_rate & RATE_MCS_ANT_ABC_MSK;
	u8 num_of_ant = get_num_of_ant_from_rate(ucode_rate);
	u8 nss;

	स_रखो(rate, 0, माप(*rate));
	rate->index = iwl_hwrate_to_plcp_idx(ucode_rate);

	अगर (rate->index == IWL_RATE_INVALID)
		वापस -EINVAL;

	rate->ant = (ant_msk >> RATE_MCS_ANT_POS);

	/* Legacy */
	अगर (!(ucode_rate & RATE_MCS_HT_MSK) &&
	    !(ucode_rate & RATE_MCS_VHT_MSK) &&
	    !(ucode_rate & RATE_MCS_HE_MSK)) अणु
		अगर (num_of_ant == 1) अणु
			अगर (band == NL80211_BAND_5GHZ)
				rate->type = LQ_LEGACY_A;
			अन्यथा
				rate->type = LQ_LEGACY_G;
		पूर्ण

		वापस 0;
	पूर्ण

	/* HT, VHT or HE */
	अगर (ucode_rate & RATE_MCS_SGI_MSK)
		rate->sgi = true;
	अगर (ucode_rate & RATE_MCS_LDPC_MSK)
		rate->ldpc = true;
	अगर (ucode_rate & RATE_MCS_STBC_MSK)
		rate->stbc = true;
	अगर (ucode_rate & RATE_MCS_BF_MSK)
		rate->bfer = true;

	rate->bw = ucode_rate & RATE_MCS_CHAN_WIDTH_MSK;

	अगर (ucode_rate & RATE_MCS_HT_MSK) अणु
		nss = ((ucode_rate & RATE_HT_MCS_NSS_MSK) >>
		       RATE_HT_MCS_NSS_POS) + 1;

		अगर (nss == 1) अणु
			rate->type = LQ_HT_SISO;
			WARN_ONCE(!rate->stbc && !rate->bfer && num_of_ant != 1,
				  "stbc %d bfer %d",
				  rate->stbc, rate->bfer);
		पूर्ण अन्यथा अगर (nss == 2) अणु
			rate->type = LQ_HT_MIMO2;
			WARN_ON_ONCE(num_of_ant != 2);
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण अन्यथा अगर (ucode_rate & RATE_MCS_VHT_MSK) अणु
		nss = ((ucode_rate & RATE_VHT_MCS_NSS_MSK) >>
		       RATE_VHT_MCS_NSS_POS) + 1;

		अगर (nss == 1) अणु
			rate->type = LQ_VHT_SISO;
			WARN_ONCE(!rate->stbc && !rate->bfer && num_of_ant != 1,
				  "stbc %d bfer %d",
				  rate->stbc, rate->bfer);
		पूर्ण अन्यथा अगर (nss == 2) अणु
			rate->type = LQ_VHT_MIMO2;
			WARN_ON_ONCE(num_of_ant != 2);
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण अन्यथा अगर (ucode_rate & RATE_MCS_HE_MSK) अणु
		nss = ((ucode_rate & RATE_VHT_MCS_NSS_MSK) >>
		      RATE_VHT_MCS_NSS_POS) + 1;

		अगर (nss == 1) अणु
			rate->type = LQ_HE_SISO;
			WARN_ONCE(!rate->stbc && !rate->bfer && num_of_ant != 1,
				  "stbc %d bfer %d", rate->stbc, rate->bfer);
		पूर्ण अन्यथा अगर (nss == 2) अणु
			rate->type = LQ_HE_MIMO2;
			WARN_ON_ONCE(num_of_ant != 2);
		पूर्ण अन्यथा अणु
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण

	WARN_ON_ONCE(rate->bw == RATE_MCS_CHAN_WIDTH_80 &&
		     !is_he(rate) && !is_vht(rate));

	वापस 0;
पूर्ण

/* चयन to another antenna/antennas and वापस 1 */
/* अगर no other valid antenna found, वापस 0 */
अटल पूर्णांक rs_toggle_antenna(u32 valid_ant, काष्ठा rs_rate *rate)
अणु
	u8 new_ant_type;

	अगर (!rate->ant || WARN_ON_ONCE(rate->ant & ANT_C))
		वापस 0;

	अगर (!rs_is_valid_ant(valid_ant, rate->ant))
		वापस 0;

	new_ant_type = ant_toggle_lookup[rate->ant];

	जबतक ((new_ant_type != rate->ant) &&
	       !rs_is_valid_ant(valid_ant, new_ant_type))
		new_ant_type = ant_toggle_lookup[new_ant_type];

	अगर (new_ant_type == rate->ant)
		वापस 0;

	rate->ant = new_ant_type;

	वापस 1;
पूर्ण

अटल u16 rs_get_supported_rates(काष्ठा iwl_lq_sta *lq_sta,
				  काष्ठा rs_rate *rate)
अणु
	अगर (is_legacy(rate))
		वापस lq_sta->active_legacy_rate;
	अन्यथा अगर (is_siso(rate))
		वापस lq_sta->active_siso_rate;
	अन्यथा अगर (is_mimo2(rate))
		वापस lq_sta->active_mimo2_rate;

	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

अटल u16 rs_get_adjacent_rate(काष्ठा iwl_mvm *mvm, u8 index, u16 rate_mask,
				पूर्णांक rate_type)
अणु
	u8 high = IWL_RATE_INVALID;
	u8 low = IWL_RATE_INVALID;

	/* 802.11A or ht walks to the next literal adjacent rate in
	 * the rate table */
	अगर (is_type_a_band(rate_type) || !is_type_legacy(rate_type)) अणु
		पूर्णांक i;
		u32 mask;

		/* Find the previous rate that is in the rate mask */
		i = index - 1;
		अगर (i >= 0)
			mask = BIT(i);
		क्रम (; i >= 0; i--, mask >>= 1) अणु
			अगर (rate_mask & mask) अणु
				low = i;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Find the next rate that is in the rate mask */
		i = index + 1;
		क्रम (mask = (1 << i); i < IWL_RATE_COUNT; i++, mask <<= 1) अणु
			अगर (rate_mask & mask) अणु
				high = i;
				अवरोध;
			पूर्ण
		पूर्ण

		वापस (high << 8) | low;
	पूर्ण

	low = index;
	जबतक (low != IWL_RATE_INVALID) अणु
		low = iwl_rates[low].prev_rs;
		अगर (low == IWL_RATE_INVALID)
			अवरोध;
		अगर (rate_mask & (1 << low))
			अवरोध;
	पूर्ण

	high = index;
	जबतक (high != IWL_RATE_INVALID) अणु
		high = iwl_rates[high].next_rs;
		अगर (high == IWL_RATE_INVALID)
			अवरोध;
		अगर (rate_mask & (1 << high))
			अवरोध;
	पूर्ण

	वापस (high << 8) | low;
पूर्ण

अटल अंतरभूत bool rs_rate_supported(काष्ठा iwl_lq_sta *lq_sta,
				     काष्ठा rs_rate *rate)
अणु
	वापस BIT(rate->index) & rs_get_supported_rates(lq_sta, rate);
पूर्ण

/* Get the next supported lower rate in the current column.
 * Return true अगर bottom rate in the current column was reached
 */
अटल bool rs_get_lower_rate_in_column(काष्ठा iwl_lq_sta *lq_sta,
					काष्ठा rs_rate *rate)
अणु
	u8 low;
	u16 high_low;
	u16 rate_mask;
	काष्ठा iwl_mvm *mvm = lq_sta->pers.drv;

	rate_mask = rs_get_supported_rates(lq_sta, rate);
	high_low = rs_get_adjacent_rate(mvm, rate->index, rate_mask,
					rate->type);
	low = high_low & 0xff;

	/* Bottom rate of column reached */
	अगर (low == IWL_RATE_INVALID)
		वापस true;

	rate->index = low;
	वापस false;
पूर्ण

/* Get the next rate to use following a column करोwngrade */
अटल व्योम rs_get_lower_rate_करोwn_column(काष्ठा iwl_lq_sta *lq_sta,
					  काष्ठा rs_rate *rate)
अणु
	काष्ठा iwl_mvm *mvm = lq_sta->pers.drv;

	अगर (is_legacy(rate)) अणु
		/* No column to करोwngrade from Legacy */
		वापस;
	पूर्ण अन्यथा अगर (is_siso(rate)) अणु
		/* Downgrade to Legacy अगर we were in SISO */
		अगर (lq_sta->band == NL80211_BAND_5GHZ)
			rate->type = LQ_LEGACY_A;
		अन्यथा
			rate->type = LQ_LEGACY_G;

		rate->bw = RATE_MCS_CHAN_WIDTH_20;

		WARN_ON_ONCE(rate->index < IWL_RATE_MCS_0_INDEX ||
			     rate->index > IWL_RATE_MCS_9_INDEX);

		rate->index = rs_ht_to_legacy[rate->index];
		rate->ldpc = false;
	पूर्ण अन्यथा अणु
		/* Downgrade to SISO with same MCS अगर in MIMO  */
		rate->type = is_vht_mimo2(rate) ?
			LQ_VHT_SISO : LQ_HT_SISO;
	पूर्ण

	अगर (num_of_ant(rate->ant) > 1)
		rate->ant = first_antenna(iwl_mvm_get_valid_tx_ant(mvm));

	/* Relevant in both चयनing to SISO or Legacy */
	rate->sgi = false;

	अगर (!rs_rate_supported(lq_sta, rate))
		rs_get_lower_rate_in_column(lq_sta, rate);
पूर्ण

/* Check अगर both rates share the same column */
अटल अंतरभूत bool rs_rate_column_match(काष्ठा rs_rate *a,
					काष्ठा rs_rate *b)
अणु
	bool ant_match;

	अगर (a->stbc || a->bfer)
		ant_match = (b->ant == ANT_A || b->ant == ANT_B);
	अन्यथा
		ant_match = (a->ant == b->ant);

	वापस (a->type == b->type) && (a->bw == b->bw) && (a->sgi == b->sgi)
		&& ant_match;
पूर्ण

अटल अंतरभूत क्रमागत rs_column rs_get_column_from_rate(काष्ठा rs_rate *rate)
अणु
	अगर (is_legacy(rate)) अणु
		अगर (rate->ant == ANT_A)
			वापस RS_COLUMN_LEGACY_ANT_A;

		अगर (rate->ant == ANT_B)
			वापस RS_COLUMN_LEGACY_ANT_B;

		जाओ err;
	पूर्ण

	अगर (is_siso(rate)) अणु
		अगर (rate->ant == ANT_A || rate->stbc || rate->bfer)
			वापस rate->sgi ? RS_COLUMN_SISO_ANT_A_SGI :
				RS_COLUMN_SISO_ANT_A;

		अगर (rate->ant == ANT_B)
			वापस rate->sgi ? RS_COLUMN_SISO_ANT_B_SGI :
				RS_COLUMN_SISO_ANT_B;

		जाओ err;
	पूर्ण

	अगर (is_mimo(rate))
		वापस rate->sgi ? RS_COLUMN_MIMO2_SGI : RS_COLUMN_MIMO2;

err:
	वापस RS_COLUMN_INVALID;
पूर्ण

अटल u8 rs_get_tid(काष्ठा ieee80211_hdr *hdr)
अणु
	u8 tid = IWL_MAX_TID_COUNT;

	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & 0xf;
	पूर्ण

	अगर (unlikely(tid > IWL_MAX_TID_COUNT))
		tid = IWL_MAX_TID_COUNT;

	वापस tid;
पूर्ण

/*
 * mac80211 sends us Tx status
 */
अटल व्योम rs_drv_mac80211_tx_status(व्योम *mvm_r,
				      काष्ठा ieee80211_supported_band *sband,
				      काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा iwl_op_mode *op_mode = mvm_r;
	काष्ठा iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	अगर (!mvmsta->vअगर)
		वापस;

	अगर (!ieee80211_is_data(hdr->frame_control) ||
	    info->flags & IEEE80211_TX_CTL_NO_ACK)
		वापस;

	iwl_mvm_rs_tx_status(mvm, sta, rs_get_tid(hdr), info,
			     ieee80211_is_qos_nullfunc(hdr->frame_control));
पूर्ण

/*
 * Begin a period of staying with a selected modulation mode.
 * Set "stay_in_tbl" flag to prevent any mode चयनes.
 * Set frame tx success limits according to legacy vs. high-throughput,
 * and reset overall (spanning all rates) tx success history statistics.
 * These control how दीर्घ we stay using same modulation mode beक्रमe
 * searching क्रम a new mode.
 */
अटल व्योम rs_set_stay_in_table(काष्ठा iwl_mvm *mvm, u8 is_legacy,
				 काष्ठा iwl_lq_sta *lq_sta)
अणु
	IWL_DEBUG_RATE(mvm, "Moving to RS_STATE_STAY_IN_COLUMN\n");
	lq_sta->rs_state = RS_STATE_STAY_IN_COLUMN;
	अगर (is_legacy) अणु
		lq_sta->table_count_limit = IWL_MVM_RS_LEGACY_TABLE_COUNT;
		lq_sta->max_failure_limit = IWL_MVM_RS_LEGACY_FAILURE_LIMIT;
		lq_sta->max_success_limit = IWL_MVM_RS_LEGACY_SUCCESS_LIMIT;
	पूर्ण अन्यथा अणु
		lq_sta->table_count_limit = IWL_MVM_RS_NON_LEGACY_TABLE_COUNT;
		lq_sta->max_failure_limit = IWL_MVM_RS_NON_LEGACY_FAILURE_LIMIT;
		lq_sta->max_success_limit = IWL_MVM_RS_NON_LEGACY_SUCCESS_LIMIT;
	पूर्ण
	lq_sta->table_count = 0;
	lq_sta->total_failed = 0;
	lq_sta->total_success = 0;
	lq_sta->flush_समयr = jअगरfies;
	lq_sta->visited_columns = 0;
पूर्ण

अटल अंतरभूत पूर्णांक rs_get_max_rate_from_mask(अचिन्हित दीर्घ rate_mask)
अणु
	अगर (rate_mask)
		वापस find_last_bit(&rate_mask, BITS_PER_LONG);
	वापस IWL_RATE_INVALID;
पूर्ण

अटल पूर्णांक rs_get_max_allowed_rate(काष्ठा iwl_lq_sta *lq_sta,
				   स्थिर काष्ठा rs_tx_column *column)
अणु
	चयन (column->mode) अणु
	हाल RS_LEGACY:
		वापस lq_sta->max_legacy_rate_idx;
	हाल RS_SISO:
		वापस lq_sta->max_siso_rate_idx;
	हाल RS_MIMO2:
		वापस lq_sta->max_mimo2_rate_idx;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	वापस lq_sta->max_legacy_rate_idx;
पूर्ण

अटल स्थिर u16 *rs_get_expected_tpt_table(काष्ठा iwl_lq_sta *lq_sta,
					    स्थिर काष्ठा rs_tx_column *column,
					    u32 bw)
अणु
	/* Used to choose among HT tables */
	स्थिर u16 (*ht_tbl_poपूर्णांकer)[IWL_RATE_COUNT];

	अगर (WARN_ON_ONCE(column->mode != RS_LEGACY &&
			 column->mode != RS_SISO &&
			 column->mode != RS_MIMO2))
		वापस expected_tpt_legacy;

	/* Legacy rates have only one table */
	अगर (column->mode == RS_LEGACY)
		वापस expected_tpt_legacy;

	ht_tbl_poपूर्णांकer = expected_tpt_mimo2_20MHz;
	/* Choose among many HT tables depending on number of streams
	 * (SISO/MIMO2), channel width (20/40/80), SGI, and aggregation
	 * status */
	अगर (column->mode == RS_SISO) अणु
		चयन (bw) अणु
		हाल RATE_MCS_CHAN_WIDTH_20:
			ht_tbl_poपूर्णांकer = expected_tpt_siso_20MHz;
			अवरोध;
		हाल RATE_MCS_CHAN_WIDTH_40:
			ht_tbl_poपूर्णांकer = expected_tpt_siso_40MHz;
			अवरोध;
		हाल RATE_MCS_CHAN_WIDTH_80:
			ht_tbl_poपूर्णांकer = expected_tpt_siso_80MHz;
			अवरोध;
		हाल RATE_MCS_CHAN_WIDTH_160:
			ht_tbl_poपूर्णांकer = expected_tpt_siso_160MHz;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण अन्यथा अगर (column->mode == RS_MIMO2) अणु
		चयन (bw) अणु
		हाल RATE_MCS_CHAN_WIDTH_20:
			ht_tbl_poपूर्णांकer = expected_tpt_mimo2_20MHz;
			अवरोध;
		हाल RATE_MCS_CHAN_WIDTH_40:
			ht_tbl_poपूर्णांकer = expected_tpt_mimo2_40MHz;
			अवरोध;
		हाल RATE_MCS_CHAN_WIDTH_80:
			ht_tbl_poपूर्णांकer = expected_tpt_mimo2_80MHz;
			अवरोध;
		हाल RATE_MCS_CHAN_WIDTH_160:
			ht_tbl_poपूर्णांकer = expected_tpt_mimo2_160MHz;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
	पूर्ण

	अगर (!column->sgi && !lq_sta->is_agg)		/* Normal */
		वापस ht_tbl_poपूर्णांकer[0];
	अन्यथा अगर (column->sgi && !lq_sta->is_agg)        /* SGI */
		वापस ht_tbl_poपूर्णांकer[1];
	अन्यथा अगर (!column->sgi && lq_sta->is_agg)        /* AGG */
		वापस ht_tbl_poपूर्णांकer[2];
	अन्यथा						/* AGG+SGI */
		वापस ht_tbl_poपूर्णांकer[3];
पूर्ण

अटल व्योम rs_set_expected_tpt_table(काष्ठा iwl_lq_sta *lq_sta,
				      काष्ठा iwl_scale_tbl_info *tbl)
अणु
	काष्ठा rs_rate *rate = &tbl->rate;
	स्थिर काष्ठा rs_tx_column *column = &rs_tx_columns[tbl->column];

	tbl->expected_tpt = rs_get_expected_tpt_table(lq_sta, column, rate->bw);
पूर्ण

/* rs uses two tables, one is active and the second is क्रम searching better
 * configuration. This function, according to the index of the currently
 * active table वापसs the search table, which is located at the
 * index complementary to 1 according to the active table (active = 1,
 * search = 0 or active = 0, search = 1).
 * Since lq_info is an arary of size 2, make sure index cannot be out of bounds.
 */
अटल अंतरभूत u8 rs_search_tbl(u8 active_tbl)
अणु
	वापस (active_tbl ^ 1) & 1;
पूर्ण

अटल s32 rs_get_best_rate(काष्ठा iwl_mvm *mvm,
			    काष्ठा iwl_lq_sta *lq_sta,
			    काष्ठा iwl_scale_tbl_info *tbl,	/* "search" */
			    अचिन्हित दीर्घ rate_mask, s8 index)
अणु
	काष्ठा iwl_scale_tbl_info *active_tbl =
	    &(lq_sta->lq_info[lq_sta->active_tbl]);
	s32 success_ratio = active_tbl->win[index].success_ratio;
	u16 expected_current_tpt = active_tbl->expected_tpt[index];
	स्थिर u16 *tpt_tbl = tbl->expected_tpt;
	u16 high_low;
	u32 target_tpt;
	पूर्णांक rate_idx;

	अगर (success_ratio >= RS_PERCENT(IWL_MVM_RS_SR_NO_DECREASE)) अणु
		target_tpt = 100 * expected_current_tpt;
		IWL_DEBUG_RATE(mvm,
			       "SR %d high. Find rate exceeding EXPECTED_CURRENT %d\n",
			       success_ratio, target_tpt);
	पूर्ण अन्यथा अणु
		target_tpt = lq_sta->last_tpt;
		IWL_DEBUG_RATE(mvm,
			       "SR %d not that good. Find rate exceeding ACTUAL_TPT %d\n",
			       success_ratio, target_tpt);
	पूर्ण

	rate_idx = find_first_bit(&rate_mask, BITS_PER_LONG);

	जबतक (rate_idx != IWL_RATE_INVALID) अणु
		अगर (target_tpt < (100 * tpt_tbl[rate_idx]))
			अवरोध;

		high_low = rs_get_adjacent_rate(mvm, rate_idx, rate_mask,
						tbl->rate.type);

		rate_idx = (high_low >> 8) & 0xff;
	पूर्ण

	IWL_DEBUG_RATE(mvm, "Best rate found %d target_tp %d expected_new %d\n",
		       rate_idx, target_tpt,
		       rate_idx != IWL_RATE_INVALID ?
		       100 * tpt_tbl[rate_idx] : IWL_INVALID_VALUE);

	वापस rate_idx;
पूर्ण

अटल u32 rs_bw_from_sta_bw(काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ieee80211_sta_vht_cap *sta_vht_cap = &sta->vht_cap;
	काष्ठा ieee80211_vht_cap vht_cap = अणु
		.vht_cap_info = cpu_to_le32(sta_vht_cap->cap),
		.supp_mcs = sta_vht_cap->vht_mcs,
	पूर्ण;

	चयन (sta->bandwidth) अणु
	हाल IEEE80211_STA_RX_BW_160:
		/*
		 * Don't use 160 MHz अगर VHT extended NSS support
		 * says we cannot use 2 streams, we करोn't want to
		 * deal with this.
		 * We only check MCS 0 - they will support that अगर
		 * we got here at all and we करोn't care which MCS,
		 * we want to determine a more global state.
		 */
		अगर (ieee80211_get_vht_max_nss(&vht_cap,
					      IEEE80211_VHT_CHANWIDTH_160MHZ,
					      0, true,
					      sta->rx_nss) < sta->rx_nss)
			वापस RATE_MCS_CHAN_WIDTH_80;
		वापस RATE_MCS_CHAN_WIDTH_160;
	हाल IEEE80211_STA_RX_BW_80:
		वापस RATE_MCS_CHAN_WIDTH_80;
	हाल IEEE80211_STA_RX_BW_40:
		वापस RATE_MCS_CHAN_WIDTH_40;
	हाल IEEE80211_STA_RX_BW_20:
	शेष:
		वापस RATE_MCS_CHAN_WIDTH_20;
	पूर्ण
पूर्ण

/*
 * Check whether we should जारी using same modulation mode, or
 * begin search क्रम a new mode, based on:
 * 1) # tx successes or failures जबतक using this mode
 * 2) # बार calling this function
 * 3) elapsed समय in this mode (not used, क्रम now)
 */
अटल व्योम rs_stay_in_table(काष्ठा iwl_lq_sta *lq_sta, bool क्रमce_search)
अणु
	काष्ठा iwl_scale_tbl_info *tbl;
	पूर्णांक active_tbl;
	पूर्णांक flush_पूर्णांकerval_passed = 0;
	काष्ठा iwl_mvm *mvm;

	mvm = lq_sta->pers.drv;
	active_tbl = lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	/* If we've been disallowing search, see अगर we should now allow it */
	अगर (lq_sta->rs_state == RS_STATE_STAY_IN_COLUMN) अणु
		/* Elapsed समय using current modulation mode */
		अगर (lq_sta->flush_समयr)
			flush_पूर्णांकerval_passed =
				समय_after(jअगरfies,
					   (अचिन्हित दीर्घ)(lq_sta->flush_समयr +
							   (IWL_MVM_RS_STAY_IN_COLUMN_TIMEOUT * HZ)));

		/*
		 * Check अगर we should allow search क्रम new modulation mode.
		 * If many frames have failed or succeeded, or we've used
		 * this same modulation क्रम a दीर्घ समय, allow search, and
		 * reset history stats that keep track of whether we should
		 * allow a new search.  Also (below) reset all biपंचांगaps and
		 * stats in active history.
		 */
		अगर (क्रमce_search ||
		    (lq_sta->total_failed > lq_sta->max_failure_limit) ||
		    (lq_sta->total_success > lq_sta->max_success_limit) ||
		    ((!lq_sta->search_better_tbl) &&
		     (lq_sta->flush_समयr) && (flush_पूर्णांकerval_passed))) अणु
			IWL_DEBUG_RATE(mvm,
				       "LQ: stay is expired %d %d %d\n",
				     lq_sta->total_failed,
				     lq_sta->total_success,
				     flush_पूर्णांकerval_passed);

			/* Allow search क्रम new mode */
			lq_sta->rs_state = RS_STATE_SEARCH_CYCLE_STARTED;
			IWL_DEBUG_RATE(mvm,
				       "Moving to RS_STATE_SEARCH_CYCLE_STARTED\n");
			lq_sta->total_failed = 0;
			lq_sta->total_success = 0;
			lq_sta->flush_समयr = 0;
			/* mark the current column as visited */
			lq_sta->visited_columns = BIT(tbl->column);
		/*
		 * Else अगर we've used this modulation mode enough repetitions
		 * (regardless of elapsed समय or success/failure), reset
		 * history biपंचांगaps and rate-specअगरic stats क्रम all rates in
		 * active table.
		 */
		पूर्ण अन्यथा अणु
			lq_sta->table_count++;
			अगर (lq_sta->table_count >=
			    lq_sta->table_count_limit) अणु
				lq_sta->table_count = 0;

				IWL_DEBUG_RATE(mvm,
					       "LQ: stay in table clear win\n");
				rs_rate_scale_clear_tbl_winकरोws(mvm, tbl);
			पूर्ण
		पूर्ण

		/* If transitioning to allow "search", reset all history
		 * biपंचांगaps and stats in active table (this will become the new
		 * "search" table). */
		अगर (lq_sta->rs_state == RS_STATE_SEARCH_CYCLE_STARTED) अणु
			rs_rate_scale_clear_tbl_winकरोws(mvm, tbl);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rs_set_amsdu_len(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			     काष्ठा iwl_scale_tbl_info *tbl,
			     क्रमागत rs_action scale_action)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	पूर्णांक i;

	sta->max_amsdu_len = rs_fw_get_max_amsdu_len(sta);

	/*
	 * In हाल TLC offload is not active amsdu_enabled is either 0xFFFF
	 * or 0, since there is no per-TID alg.
	 */
	अगर ((!is_vht(&tbl->rate) && !is_ht(&tbl->rate)) ||
	    tbl->rate.index < IWL_RATE_MCS_5_INDEX ||
	    scale_action == RS_ACTION_DOWNSCALE)
		mvmsta->amsdu_enabled = 0;
	अन्यथा
		mvmsta->amsdu_enabled = 0xFFFF;

	अगर (mvmsta->vअगर->bss_conf.he_support &&
	    !iwlwअगरi_mod_params.disable_11ax)
		mvmsta->max_amsdu_len = sta->max_amsdu_len;
	अन्यथा
		mvmsta->max_amsdu_len = min_t(पूर्णांक, sta->max_amsdu_len, 8500);

	sta->max_rc_amsdu_len = mvmsta->max_amsdu_len;

	क्रम (i = 0; i < IWL_MAX_TID_COUNT; i++) अणु
		अगर (mvmsta->amsdu_enabled)
			sta->max_tid_amsdu_len[i] =
				iwl_mvm_max_amsdu_size(mvm, sta, i);
		अन्यथा
			/*
			 * Not so elegant, but this will effectively
			 * prevent AMSDU on this TID
			 */
			sta->max_tid_amsdu_len[i] = 1;
	पूर्ण
पूर्ण

/*
 * setup rate table in uCode
 */
अटल व्योम rs_update_rate_tbl(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा iwl_lq_sta *lq_sta,
			       काष्ठा iwl_scale_tbl_info *tbl)
अणु
	rs_fill_lq_cmd(mvm, sta, lq_sta, &tbl->rate);
	iwl_mvm_send_lq_cmd(mvm, &lq_sta->lq);
पूर्ण

अटल bool rs_tweak_rate_tbl(काष्ठा iwl_mvm *mvm,
			      काष्ठा ieee80211_sta *sta,
			      काष्ठा iwl_lq_sta *lq_sta,
			      काष्ठा iwl_scale_tbl_info *tbl,
			      क्रमागत rs_action scale_action)
अणु
	अगर (rs_bw_from_sta_bw(sta) != RATE_MCS_CHAN_WIDTH_80)
		वापस false;

	अगर (!is_vht_siso(&tbl->rate))
		वापस false;

	अगर ((tbl->rate.bw == RATE_MCS_CHAN_WIDTH_80) &&
	    (tbl->rate.index == IWL_RATE_MCS_0_INDEX) &&
	    (scale_action == RS_ACTION_DOWNSCALE)) अणु
		tbl->rate.bw = RATE_MCS_CHAN_WIDTH_20;
		tbl->rate.index = IWL_RATE_MCS_4_INDEX;
		IWL_DEBUG_RATE(mvm, "Switch 80Mhz SISO MCS0 -> 20Mhz MCS4\n");
		जाओ tweaked;
	पूर्ण

	/* Go back to 80Mhz MCS1 only अगर we've established that 20Mhz MCS5 is
	 * sustainable, i.e. we're past the test window. We can't go back
	 * अगर MCS5 is just tested as this will happen always after चयनing
	 * to 20Mhz MCS4 because the rate stats are cleared.
	 */
	अगर ((tbl->rate.bw == RATE_MCS_CHAN_WIDTH_20) &&
	    (((tbl->rate.index == IWL_RATE_MCS_5_INDEX) &&
	     (scale_action == RS_ACTION_STAY)) ||
	     ((tbl->rate.index > IWL_RATE_MCS_5_INDEX) &&
	      (scale_action == RS_ACTION_UPSCALE)))) अणु
		tbl->rate.bw = RATE_MCS_CHAN_WIDTH_80;
		tbl->rate.index = IWL_RATE_MCS_1_INDEX;
		IWL_DEBUG_RATE(mvm, "Switch 20Mhz SISO MCS5 -> 80Mhz MCS1\n");
		जाओ tweaked;
	पूर्ण

	वापस false;

tweaked:
	rs_set_expected_tpt_table(lq_sta, tbl);
	rs_rate_scale_clear_tbl_winकरोws(mvm, tbl);
	वापस true;
पूर्ण

अटल क्रमागत rs_column rs_get_next_column(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_lq_sta *lq_sta,
					 काष्ठा ieee80211_sta *sta,
					 काष्ठा iwl_scale_tbl_info *tbl)
अणु
	पूर्णांक i, j, max_rate;
	क्रमागत rs_column next_col_id;
	स्थिर काष्ठा rs_tx_column *curr_col = &rs_tx_columns[tbl->column];
	स्थिर काष्ठा rs_tx_column *next_col;
	allow_column_func_t allow_func;
	u8 valid_ants = iwl_mvm_get_valid_tx_ant(mvm);
	स्थिर u16 *expected_tpt_tbl;
	u16 tpt, max_expected_tpt;

	क्रम (i = 0; i < MAX_NEXT_COLUMNS; i++) अणु
		next_col_id = curr_col->next_columns[i];

		अगर (next_col_id == RS_COLUMN_INVALID)
			जारी;

		अगर (lq_sta->visited_columns & BIT(next_col_id)) अणु
			IWL_DEBUG_RATE(mvm, "Skip already visited column %d\n",
				       next_col_id);
			जारी;
		पूर्ण

		next_col = &rs_tx_columns[next_col_id];

		अगर (!rs_is_valid_ant(valid_ants, next_col->ant)) अणु
			IWL_DEBUG_RATE(mvm,
				       "Skip column %d as ANT config isn't supported by chip. valid_ants 0x%x column ant 0x%x\n",
				       next_col_id, valid_ants, next_col->ant);
			जारी;
		पूर्ण

		क्रम (j = 0; j < MAX_COLUMN_CHECKS; j++) अणु
			allow_func = next_col->checks[j];
			अगर (allow_func && !allow_func(mvm, sta, &tbl->rate,
						      next_col))
				अवरोध;
		पूर्ण

		अगर (j != MAX_COLUMN_CHECKS) अणु
			IWL_DEBUG_RATE(mvm,
				       "Skip column %d: not allowed (check %d failed)\n",
				       next_col_id, j);

			जारी;
		पूर्ण

		tpt = lq_sta->last_tpt / 100;
		expected_tpt_tbl = rs_get_expected_tpt_table(lq_sta, next_col,
						     rs_bw_from_sta_bw(sta));
		अगर (WARN_ON_ONCE(!expected_tpt_tbl))
			जारी;

		max_rate = rs_get_max_allowed_rate(lq_sta, next_col);
		अगर (max_rate == IWL_RATE_INVALID) अणु
			IWL_DEBUG_RATE(mvm,
				       "Skip column %d: no rate is allowed in this column\n",
				       next_col_id);
			जारी;
		पूर्ण

		max_expected_tpt = expected_tpt_tbl[max_rate];
		अगर (tpt >= max_expected_tpt) अणु
			IWL_DEBUG_RATE(mvm,
				       "Skip column %d: can't beat current TPT. Max expected %d current %d\n",
				       next_col_id, max_expected_tpt, tpt);
			जारी;
		पूर्ण

		IWL_DEBUG_RATE(mvm,
			       "Found potential column %d. Max expected %d current %d\n",
			       next_col_id, max_expected_tpt, tpt);
		अवरोध;
	पूर्ण

	अगर (i == MAX_NEXT_COLUMNS)
		वापस RS_COLUMN_INVALID;

	वापस next_col_id;
पूर्ण

अटल पूर्णांक rs_चयन_to_column(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_lq_sta *lq_sta,
			       काष्ठा ieee80211_sta *sta,
			       क्रमागत rs_column col_id)
अणु
	काष्ठा iwl_scale_tbl_info *tbl = &lq_sta->lq_info[lq_sta->active_tbl];
	काष्ठा iwl_scale_tbl_info *search_tbl =
		&lq_sta->lq_info[rs_search_tbl(lq_sta->active_tbl)];
	काष्ठा rs_rate *rate = &search_tbl->rate;
	स्थिर काष्ठा rs_tx_column *column = &rs_tx_columns[col_id];
	स्थिर काष्ठा rs_tx_column *curr_column = &rs_tx_columns[tbl->column];
	अचिन्हित दीर्घ rate_mask = 0;
	u32 rate_idx = 0;

	स_नकल(search_tbl, tbl, दुरत्व(काष्ठा iwl_scale_tbl_info, win));

	rate->sgi = column->sgi;
	rate->ant = column->ant;

	अगर (column->mode == RS_LEGACY) अणु
		अगर (lq_sta->band == NL80211_BAND_5GHZ)
			rate->type = LQ_LEGACY_A;
		अन्यथा
			rate->type = LQ_LEGACY_G;

		rate->bw = RATE_MCS_CHAN_WIDTH_20;
		rate->ldpc = false;
		rate_mask = lq_sta->active_legacy_rate;
	पूर्ण अन्यथा अगर (column->mode == RS_SISO) अणु
		rate->type = lq_sta->is_vht ? LQ_VHT_SISO : LQ_HT_SISO;
		rate_mask = lq_sta->active_siso_rate;
	पूर्ण अन्यथा अगर (column->mode == RS_MIMO2) अणु
		rate->type = lq_sta->is_vht ? LQ_VHT_MIMO2 : LQ_HT_MIMO2;
		rate_mask = lq_sta->active_mimo2_rate;
	पूर्ण अन्यथा अणु
		WARN_ONCE(1, "Bad column mode");
	पूर्ण

	अगर (column->mode != RS_LEGACY) अणु
		rate->bw = rs_bw_from_sta_bw(sta);
		rate->ldpc = lq_sta->ldpc;
	पूर्ण

	search_tbl->column = col_id;
	rs_set_expected_tpt_table(lq_sta, search_tbl);

	lq_sta->visited_columns |= BIT(col_id);

	/* Get the best matching rate अगर we're changing modes. e.g.
	 * SISO->MIMO, LEGACY->SISO, MIMO->SISO
	 */
	अगर (curr_column->mode != column->mode) अणु
		rate_idx = rs_get_best_rate(mvm, lq_sta, search_tbl,
					    rate_mask, rate->index);

		अगर ((rate_idx == IWL_RATE_INVALID) ||
		    !(BIT(rate_idx) & rate_mask)) अणु
			IWL_DEBUG_RATE(mvm,
				       "can not switch with index %d"
				       " rate mask %lx\n",
				       rate_idx, rate_mask);

			जाओ err;
		पूर्ण

		rate->index = rate_idx;
	पूर्ण

	IWL_DEBUG_RATE(mvm, "Switched to column %d: Index %d\n",
		       col_id, rate->index);

	वापस 0;

err:
	rate->type = LQ_NONE;
	वापस -1;
पूर्ण

अटल क्रमागत rs_action rs_get_rate_action(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_scale_tbl_info *tbl,
					 s32 sr, पूर्णांक low, पूर्णांक high,
					 पूर्णांक current_tpt,
					 पूर्णांक low_tpt, पूर्णांक high_tpt)
अणु
	क्रमागत rs_action action = RS_ACTION_STAY;

	अगर ((sr <= RS_PERCENT(IWL_MVM_RS_SR_FORCE_DECREASE)) ||
	    (current_tpt == 0)) अणु
		IWL_DEBUG_RATE(mvm,
			       "Decrease rate because of low SR\n");
		वापस RS_ACTION_DOWNSCALE;
	पूर्ण

	अगर ((low_tpt == IWL_INVALID_VALUE) &&
	    (high_tpt == IWL_INVALID_VALUE) &&
	    (high != IWL_RATE_INVALID)) अणु
		IWL_DEBUG_RATE(mvm,
			       "No data about high/low rates. Increase rate\n");
		वापस RS_ACTION_UPSCALE;
	पूर्ण

	अगर ((high_tpt == IWL_INVALID_VALUE) &&
	    (high != IWL_RATE_INVALID) &&
	    (low_tpt != IWL_INVALID_VALUE) &&
	    (low_tpt < current_tpt)) अणु
		IWL_DEBUG_RATE(mvm,
			       "No data about high rate and low rate is worse. Increase rate\n");
		वापस RS_ACTION_UPSCALE;
	पूर्ण

	अगर ((high_tpt != IWL_INVALID_VALUE) &&
	    (high_tpt > current_tpt)) अणु
		IWL_DEBUG_RATE(mvm,
			       "Higher rate is better. Increate rate\n");
		वापस RS_ACTION_UPSCALE;
	पूर्ण

	अगर ((low_tpt != IWL_INVALID_VALUE) &&
	    (high_tpt != IWL_INVALID_VALUE) &&
	    (low_tpt < current_tpt) &&
	    (high_tpt < current_tpt)) अणु
		IWL_DEBUG_RATE(mvm,
			       "Both high and low are worse. Maintain rate\n");
		वापस RS_ACTION_STAY;
	पूर्ण

	अगर ((low_tpt != IWL_INVALID_VALUE) &&
	    (low_tpt > current_tpt)) अणु
		IWL_DEBUG_RATE(mvm,
			       "Lower rate is better\n");
		action = RS_ACTION_DOWNSCALE;
		जाओ out;
	पूर्ण

	अगर ((low_tpt == IWL_INVALID_VALUE) &&
	    (low != IWL_RATE_INVALID)) अणु
		IWL_DEBUG_RATE(mvm,
			       "No data about lower rate\n");
		action = RS_ACTION_DOWNSCALE;
		जाओ out;
	पूर्ण

	IWL_DEBUG_RATE(mvm, "Maintain rate\n");

out:
	अगर ((action == RS_ACTION_DOWNSCALE) && (low != IWL_RATE_INVALID)) अणु
		अगर (sr >= RS_PERCENT(IWL_MVM_RS_SR_NO_DECREASE)) अणु
			IWL_DEBUG_RATE(mvm,
				       "SR is above NO DECREASE. Avoid downscale\n");
			action = RS_ACTION_STAY;
		पूर्ण अन्यथा अगर (current_tpt > (100 * tbl->expected_tpt[low])) अणु
			IWL_DEBUG_RATE(mvm,
				       "Current TPT is higher than max expected in low rate. Avoid downscale\n");
			action = RS_ACTION_STAY;
		पूर्ण अन्यथा अणु
			IWL_DEBUG_RATE(mvm, "Decrease rate\n");
		पूर्ण
	पूर्ण

	वापस action;
पूर्ण

अटल bool rs_stbc_allow(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			  काष्ठा iwl_lq_sta *lq_sta)
अणु
	/* Our chip supports Tx STBC and the peer is an HT/VHT STA which
	 * supports STBC of at least 1*SS
	 */
	अगर (!lq_sta->stbc_capable)
		वापस false;

	अगर (!iwl_mvm_bt_coex_is_mimo_allowed(mvm, sta))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम rs_get_adjacent_txp(काष्ठा iwl_mvm *mvm, पूर्णांक index,
				पूर्णांक *weaker, पूर्णांक *stronger)
अणु
	*weaker = index + IWL_MVM_RS_TPC_TX_POWER_STEP;
	अगर (*weaker > TPC_MAX_REDUCTION)
		*weaker = TPC_INVALID;

	*stronger = index - IWL_MVM_RS_TPC_TX_POWER_STEP;
	अगर (*stronger < 0)
		*stronger = TPC_INVALID;
पूर्ण

अटल bool rs_tpc_allowed(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा rs_rate *rate, क्रमागत nl80211_band band)
अणु
	पूर्णांक index = rate->index;
	bool cam = (iwlmvm_mod_params.घातer_scheme == IWL_POWER_SCHEME_CAM);
	bool sta_ps_disabled = (vअगर->type == NL80211_IFTYPE_STATION &&
				!vअगर->bss_conf.ps);

	IWL_DEBUG_RATE(mvm, "cam: %d sta_ps_disabled %d\n",
		       cam, sta_ps_disabled);
	/*
	 * allow tpc only अगर घातer management is enabled, or bt coex
	 * activity grade allows it and we are on 2.4Ghz.
	 */
	अगर ((cam || sta_ps_disabled) &&
	    !iwl_mvm_bt_coex_is_tpc_allowed(mvm, band))
		वापस false;

	IWL_DEBUG_RATE(mvm, "check rate, table type: %d\n", rate->type);
	अगर (is_legacy(rate))
		वापस index == IWL_RATE_54M_INDEX;
	अगर (is_ht(rate))
		वापस index == IWL_RATE_MCS_7_INDEX;
	अगर (is_vht(rate))
		वापस index == IWL_RATE_MCS_9_INDEX;

	WARN_ON_ONCE(1);
	वापस false;
पूर्ण

क्रमागत tpc_action अणु
	TPC_ACTION_STAY,
	TPC_ACTION_DECREASE,
	TPC_ACTION_INCREASE,
	TPC_ACTION_NO_RESTIRCTION,
पूर्ण;

अटल क्रमागत tpc_action rs_get_tpc_action(काष्ठा iwl_mvm *mvm,
					 s32 sr, पूर्णांक weak, पूर्णांक strong,
					 पूर्णांक current_tpt,
					 पूर्णांक weak_tpt, पूर्णांक strong_tpt)
अणु
	/* stay until we have valid tpt */
	अगर (current_tpt == IWL_INVALID_VALUE) अणु
		IWL_DEBUG_RATE(mvm, "no current tpt. stay.\n");
		वापस TPC_ACTION_STAY;
	पूर्ण

	/* Too many failures, increase txp */
	अगर (sr <= RS_PERCENT(IWL_MVM_RS_TPC_SR_FORCE_INCREASE) ||
	    current_tpt == 0) अणु
		IWL_DEBUG_RATE(mvm, "increase txp because of weak SR\n");
		वापस TPC_ACTION_NO_RESTIRCTION;
	पूर्ण

	/* try decreasing first अगर applicable */
	अगर (sr >= RS_PERCENT(IWL_MVM_RS_TPC_SR_NO_INCREASE) &&
	    weak != TPC_INVALID) अणु
		अगर (weak_tpt == IWL_INVALID_VALUE &&
		    (strong_tpt == IWL_INVALID_VALUE ||
		     current_tpt >= strong_tpt)) अणु
			IWL_DEBUG_RATE(mvm,
				       "no weak txp measurement. decrease txp\n");
			वापस TPC_ACTION_DECREASE;
		पूर्ण

		अगर (weak_tpt > current_tpt) अणु
			IWL_DEBUG_RATE(mvm,
				       "lower txp has better tpt. decrease txp\n");
			वापस TPC_ACTION_DECREASE;
		पूर्ण
	पूर्ण

	/* next, increase अगर needed */
	अगर (sr < RS_PERCENT(IWL_MVM_RS_TPC_SR_NO_INCREASE) &&
	    strong != TPC_INVALID) अणु
		अगर (weak_tpt == IWL_INVALID_VALUE &&
		    strong_tpt != IWL_INVALID_VALUE &&
		    current_tpt < strong_tpt) अणु
			IWL_DEBUG_RATE(mvm,
				       "higher txp has better tpt. increase txp\n");
			वापस TPC_ACTION_INCREASE;
		पूर्ण

		अगर (weak_tpt < current_tpt &&
		    (strong_tpt == IWL_INVALID_VALUE ||
		     strong_tpt > current_tpt)) अणु
			IWL_DEBUG_RATE(mvm,
				       "lower txp has worse tpt. increase txp\n");
			वापस TPC_ACTION_INCREASE;
		पूर्ण
	पूर्ण

	IWL_DEBUG_RATE(mvm, "no need to increase or decrease txp - stay\n");
	वापस TPC_ACTION_STAY;
पूर्ण

अटल bool rs_tpc_perक्रमm(काष्ठा iwl_mvm *mvm,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा iwl_lq_sta *lq_sta,
			   काष्ठा iwl_scale_tbl_info *tbl)
अणु
	काष्ठा iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा ieee80211_vअगर *vअगर = mvm_sta->vअगर;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	क्रमागत nl80211_band band;
	काष्ठा iwl_rate_scale_data *winकरोw;
	काष्ठा rs_rate *rate = &tbl->rate;
	क्रमागत tpc_action action;
	s32 sr;
	u8 cur = lq_sta->lq.reduced_tpc;
	पूर्णांक current_tpt;
	पूर्णांक weak, strong;
	पूर्णांक weak_tpt = IWL_INVALID_VALUE, strong_tpt = IWL_INVALID_VALUE;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	अगर (lq_sta->pers.dbg_fixed_txp_reduction <= TPC_MAX_REDUCTION) अणु
		IWL_DEBUG_RATE(mvm, "fixed tpc: %d\n",
			       lq_sta->pers.dbg_fixed_txp_reduction);
		lq_sta->lq.reduced_tpc = lq_sta->pers.dbg_fixed_txp_reduction;
		वापस cur != lq_sta->pers.dbg_fixed_txp_reduction;
	पूर्ण
#पूर्ण_अगर

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(vअगर->chanctx_conf);
	अगर (WARN_ON(!chanctx_conf))
		band = NUM_NL80211_BANDS;
	अन्यथा
		band = chanctx_conf->def.chan->band;
	rcu_पढ़ो_unlock();

	अगर (!rs_tpc_allowed(mvm, vअगर, rate, band)) अणु
		IWL_DEBUG_RATE(mvm,
			       "tpc is not allowed. remove txp restrictions\n");
		lq_sta->lq.reduced_tpc = TPC_NO_REDUCTION;
		वापस cur != TPC_NO_REDUCTION;
	पूर्ण

	rs_get_adjacent_txp(mvm, cur, &weak, &strong);

	/* Collect measured throughमाला_दो क्रम current and adjacent rates */
	winकरोw = tbl->tpc_win;
	sr = winकरोw[cur].success_ratio;
	current_tpt = winकरोw[cur].average_tpt;
	अगर (weak != TPC_INVALID)
		weak_tpt = winकरोw[weak].average_tpt;
	अगर (strong != TPC_INVALID)
		strong_tpt = winकरोw[strong].average_tpt;

	IWL_DEBUG_RATE(mvm,
		       "(TPC: %d): cur_tpt %d SR %d weak %d strong %d weak_tpt %d strong_tpt %d\n",
		       cur, current_tpt, sr, weak, strong,
		       weak_tpt, strong_tpt);

	action = rs_get_tpc_action(mvm, sr, weak, strong,
				   current_tpt, weak_tpt, strong_tpt);

	/* override actions अगर we are on the edge */
	अगर (weak == TPC_INVALID && action == TPC_ACTION_DECREASE) अणु
		IWL_DEBUG_RATE(mvm, "already in lowest txp, stay\n");
		action = TPC_ACTION_STAY;
	पूर्ण अन्यथा अगर (strong == TPC_INVALID &&
		   (action == TPC_ACTION_INCREASE ||
		    action == TPC_ACTION_NO_RESTIRCTION)) अणु
		IWL_DEBUG_RATE(mvm, "already in highest txp, stay\n");
		action = TPC_ACTION_STAY;
	पूर्ण

	चयन (action) अणु
	हाल TPC_ACTION_DECREASE:
		lq_sta->lq.reduced_tpc = weak;
		वापस true;
	हाल TPC_ACTION_INCREASE:
		lq_sta->lq.reduced_tpc = strong;
		वापस true;
	हाल TPC_ACTION_NO_RESTIRCTION:
		lq_sta->lq.reduced_tpc = TPC_NO_REDUCTION;
		वापस true;
	हाल TPC_ACTION_STAY:
		/* करो nothing */
		अवरोध;
	पूर्ण
	वापस false;
पूर्ण

/*
 * Do rate scaling and search क्रम new modulation mode.
 */
अटल व्योम rs_rate_scale_perक्रमm(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा iwl_lq_sta *lq_sta,
				  पूर्णांक tid, bool ndp)
अणु
	पूर्णांक low = IWL_RATE_INVALID;
	पूर्णांक high = IWL_RATE_INVALID;
	पूर्णांक index;
	काष्ठा iwl_rate_scale_data *winकरोw = शून्य;
	पूर्णांक current_tpt = IWL_INVALID_VALUE;
	पूर्णांक low_tpt = IWL_INVALID_VALUE;
	पूर्णांक high_tpt = IWL_INVALID_VALUE;
	u32 fail_count;
	क्रमागत rs_action scale_action = RS_ACTION_STAY;
	u16 rate_mask;
	u8 update_lq = 0;
	काष्ठा iwl_scale_tbl_info *tbl, *tbl1;
	u8 active_tbl = 0;
	u8 करोne_search = 0;
	u16 high_low;
	s32 sr;
	u8 prev_agg = lq_sta->is_agg;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा rs_rate *rate;

	lq_sta->is_agg = !!mvmsta->agg_tids;

	/*
	 * Select rate-scale / modulation-mode table to work with in
	 * the rest of this function:  "search" अगर searching क्रम better
	 * modulation mode, or "active" अगर करोing rate scaling within a mode.
	 */
	अगर (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	अन्यथा
		active_tbl = rs_search_tbl(lq_sta->active_tbl);

	tbl = &(lq_sta->lq_info[active_tbl]);
	rate = &tbl->rate;

	अगर (prev_agg != lq_sta->is_agg) अणु
		IWL_DEBUG_RATE(mvm,
			       "Aggregation changed: prev %d current %d. Update expected TPT table\n",
			       prev_agg, lq_sta->is_agg);
		rs_set_expected_tpt_table(lq_sta, tbl);
		rs_rate_scale_clear_tbl_winकरोws(mvm, tbl);
	पूर्ण

	/* current tx rate */
	index = rate->index;

	/* rates available क्रम this association, and क्रम modulation mode */
	rate_mask = rs_get_supported_rates(lq_sta, rate);

	अगर (!(BIT(index) & rate_mask)) अणु
		IWL_ERR(mvm, "Current Rate is not valid\n");
		अगर (lq_sta->search_better_tbl) अणु
			/* revert to active table अगर search table is not valid*/
			rate->type = LQ_NONE;
			lq_sta->search_better_tbl = 0;
			tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
			rs_update_rate_tbl(mvm, sta, lq_sta, tbl);
		पूर्ण
		वापस;
	पूर्ण

	/* Get expected throughput table and history winकरोw क्रम current rate */
	अगर (!tbl->expected_tpt) अणु
		IWL_ERR(mvm, "tbl->expected_tpt is NULL\n");
		वापस;
	पूर्ण

	/* TODO: handle rate_idx_mask and rate_idx_mcs_mask */
	winकरोw = &(tbl->win[index]);

	/*
	 * If there is not enough history to calculate actual average
	 * throughput, keep analyzing results of more tx frames, without
	 * changing rate or mode (bypass most of the rest of this function).
	 * Set up new rate table in uCode only अगर old rate is not supported
	 * in current association (use new rate found above).
	 */
	fail_count = winकरोw->counter - winकरोw->success_counter;
	अगर ((fail_count < IWL_MVM_RS_RATE_MIN_FAILURE_TH) &&
	    (winकरोw->success_counter < IWL_MVM_RS_RATE_MIN_SUCCESS_TH)) अणु
		IWL_DEBUG_RATE(mvm,
			       "%s: Test Window: succ %d total %d\n",
			       rs_pretty_rate(rate),
			       winकरोw->success_counter, winकरोw->counter);

		/* Can't calculate this yet; not enough history */
		winकरोw->average_tpt = IWL_INVALID_VALUE;

		/* Should we stay with this modulation mode,
		 * or search क्रम a new one? */
		rs_stay_in_table(lq_sta, false);

		वापस;
	पूर्ण

	/* If we are searching क्रम better modulation mode, check success. */
	अगर (lq_sta->search_better_tbl) अणु
		/* If good success, जारी using the "search" mode;
		 * no need to send new link quality command, since we're
		 * continuing to use the setup that we've been trying. */
		अगर (winकरोw->average_tpt > lq_sta->last_tpt) अणु
			IWL_DEBUG_RATE(mvm,
				       "SWITCHING TO NEW TABLE SR: %d "
				       "cur-tpt %d old-tpt %d\n",
				       winकरोw->success_ratio,
				       winकरोw->average_tpt,
				       lq_sta->last_tpt);

			/* Swap tables; "search" becomes "active" */
			lq_sta->active_tbl = active_tbl;
			current_tpt = winकरोw->average_tpt;
		/* Else poor success; go back to mode in "active" table */
		पूर्ण अन्यथा अणु
			IWL_DEBUG_RATE(mvm,
				       "GOING BACK TO THE OLD TABLE: SR %d "
				       "cur-tpt %d old-tpt %d\n",
				       winकरोw->success_ratio,
				       winकरोw->average_tpt,
				       lq_sta->last_tpt);

			/* Nullअगरy "search" table */
			rate->type = LQ_NONE;

			/* Revert to "active" table */
			active_tbl = lq_sta->active_tbl;
			tbl = &(lq_sta->lq_info[active_tbl]);

			/* Revert to "active" rate and throughput info */
			index = tbl->rate.index;
			current_tpt = lq_sta->last_tpt;

			/* Need to set up a new rate table in uCode */
			update_lq = 1;
		पूर्ण

		/* Either way, we've made a decision; modulation mode
		 * search is करोne, allow rate adjusपंचांगent next समय. */
		lq_sta->search_better_tbl = 0;
		करोne_search = 1;	/* Don't चयन modes below! */
		जाओ lq_update;
	पूर्ण

	/* (Else) not in search of better modulation mode, try क्रम better
	 * starting rate, जबतक staying in this mode. */
	high_low = rs_get_adjacent_rate(mvm, index, rate_mask, rate->type);
	low = high_low & 0xff;
	high = (high_low >> 8) & 0xff;

	/* TODO: handle rate_idx_mask and rate_idx_mcs_mask */

	sr = winकरोw->success_ratio;

	/* Collect measured throughमाला_दो क्रम current and adjacent rates */
	current_tpt = winकरोw->average_tpt;
	अगर (low != IWL_RATE_INVALID)
		low_tpt = tbl->win[low].average_tpt;
	अगर (high != IWL_RATE_INVALID)
		high_tpt = tbl->win[high].average_tpt;

	IWL_DEBUG_RATE(mvm,
		       "%s: cur_tpt %d SR %d low %d high %d low_tpt %d high_tpt %d\n",
		       rs_pretty_rate(rate), current_tpt, sr,
		       low, high, low_tpt, high_tpt);

	scale_action = rs_get_rate_action(mvm, tbl, sr, low, high,
					  current_tpt, low_tpt, high_tpt);

	/* Force a search in हाल BT करोesn't like us being in MIMO */
	अगर (is_mimo(rate) &&
	    !iwl_mvm_bt_coex_is_mimo_allowed(mvm, sta)) अणु
		IWL_DEBUG_RATE(mvm,
			       "BT Coex forbids MIMO. Search for new config\n");
		rs_stay_in_table(lq_sta, true);
		जाओ lq_update;
	पूर्ण

	चयन (scale_action) अणु
	हाल RS_ACTION_DOWNSCALE:
		/* Decrease starting rate, update uCode's rate table */
		अगर (low != IWL_RATE_INVALID) अणु
			update_lq = 1;
			index = low;
		पूर्ण अन्यथा अणु
			IWL_DEBUG_RATE(mvm,
				       "At the bottom rate. Can't decrease\n");
		पूर्ण

		अवरोध;
	हाल RS_ACTION_UPSCALE:
		/* Increase starting rate, update uCode's rate table */
		अगर (high != IWL_RATE_INVALID) अणु
			update_lq = 1;
			index = high;
		पूर्ण अन्यथा अणु
			IWL_DEBUG_RATE(mvm,
				       "At the top rate. Can't increase\n");
		पूर्ण

		अवरोध;
	हाल RS_ACTION_STAY:
		/* No change */
		अगर (lq_sta->rs_state == RS_STATE_STAY_IN_COLUMN)
			update_lq = rs_tpc_perक्रमm(mvm, sta, lq_sta, tbl);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

lq_update:
	/* Replace uCode's rate table क्रम the destination station. */
	अगर (update_lq) अणु
		tbl->rate.index = index;
		अगर (IWL_MVM_RS_80_20_FAR_RANGE_TWEAK)
			rs_tweak_rate_tbl(mvm, sta, lq_sta, tbl, scale_action);
		rs_set_amsdu_len(mvm, sta, tbl, scale_action);
		rs_update_rate_tbl(mvm, sta, lq_sta, tbl);
	पूर्ण

	rs_stay_in_table(lq_sta, false);

	/*
	 * Search क्रम new modulation mode अगर we're:
	 * 1)  Not changing rates right now
	 * 2)  Not just finishing up a search
	 * 3)  Allowing a new search
	 */
	अगर (!update_lq && !करोne_search &&
	    lq_sta->rs_state == RS_STATE_SEARCH_CYCLE_STARTED
	    && winकरोw->counter) अणु
		क्रमागत rs_column next_column;

		/* Save current throughput to compare with "search" throughput*/
		lq_sta->last_tpt = current_tpt;

		IWL_DEBUG_RATE(mvm,
			       "Start Search: update_lq %d done_search %d rs_state %d win->counter %d\n",
			       update_lq, करोne_search, lq_sta->rs_state,
			       winकरोw->counter);

		next_column = rs_get_next_column(mvm, lq_sta, sta, tbl);
		अगर (next_column != RS_COLUMN_INVALID) अणु
			पूर्णांक ret = rs_चयन_to_column(mvm, lq_sta, sta,
						      next_column);
			अगर (!ret)
				lq_sta->search_better_tbl = 1;
		पूर्ण अन्यथा अणु
			IWL_DEBUG_RATE(mvm,
				       "No more columns to explore in search cycle. Go to RS_STATE_SEARCH_CYCLE_ENDED\n");
			lq_sta->rs_state = RS_STATE_SEARCH_CYCLE_ENDED;
		पूर्ण

		/* If new "search" mode was selected, set up in uCode table */
		अगर (lq_sta->search_better_tbl) अणु
			/* Access the "search" table, clear its history. */
			tbl = &lq_sta->lq_info[rs_search_tbl(lq_sta->active_tbl)];
			rs_rate_scale_clear_tbl_winकरोws(mvm, tbl);

			/* Use new "search" start rate */
			index = tbl->rate.index;

			rs_dump_rate(mvm, &tbl->rate,
				     "Switch to SEARCH TABLE:");
			rs_update_rate_tbl(mvm, sta, lq_sta, tbl);
		पूर्ण अन्यथा अणु
			करोne_search = 1;
		पूर्ण
	पूर्ण

	अगर (!ndp)
		rs_tl_turn_on_agg(mvm, mvmsta, tid, lq_sta, sta);

	अगर (करोne_search && lq_sta->rs_state == RS_STATE_SEARCH_CYCLE_ENDED) अणु
		tbl1 = &(lq_sta->lq_info[lq_sta->active_tbl]);
		rs_set_stay_in_table(mvm, is_legacy(&tbl1->rate), lq_sta);
	पूर्ण
पूर्ण

काष्ठा rs_init_rate_info अणु
	s8 rssi;
	u8 rate_idx;
पूर्ण;

अटल स्थिर काष्ठा rs_init_rate_info rs_optimal_rates_24ghz_legacy[] = अणु
	अणु -60, IWL_RATE_54M_INDEX पूर्ण,
	अणु -64, IWL_RATE_48M_INDEX पूर्ण,
	अणु -68, IWL_RATE_36M_INDEX पूर्ण,
	अणु -80, IWL_RATE_24M_INDEX पूर्ण,
	अणु -84, IWL_RATE_18M_INDEX पूर्ण,
	अणु -85, IWL_RATE_12M_INDEX पूर्ण,
	अणु -86, IWL_RATE_11M_INDEX पूर्ण,
	अणु -88, IWL_RATE_5M_INDEX  पूर्ण,
	अणु -90, IWL_RATE_2M_INDEX  पूर्ण,
	अणु S8_MIN, IWL_RATE_1M_INDEX पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rs_init_rate_info rs_optimal_rates_5ghz_legacy[] = अणु
	अणु -60, IWL_RATE_54M_INDEX पूर्ण,
	अणु -64, IWL_RATE_48M_INDEX पूर्ण,
	अणु -72, IWL_RATE_36M_INDEX पूर्ण,
	अणु -80, IWL_RATE_24M_INDEX पूर्ण,
	अणु -84, IWL_RATE_18M_INDEX पूर्ण,
	अणु -85, IWL_RATE_12M_INDEX पूर्ण,
	अणु -87, IWL_RATE_9M_INDEX  पूर्ण,
	अणु S8_MIN, IWL_RATE_6M_INDEX पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rs_init_rate_info rs_optimal_rates_ht[] = अणु
	अणु -60, IWL_RATE_MCS_7_INDEX पूर्ण,
	अणु -64, IWL_RATE_MCS_6_INDEX पूर्ण,
	अणु -68, IWL_RATE_MCS_5_INDEX पूर्ण,
	अणु -72, IWL_RATE_MCS_4_INDEX पूर्ण,
	अणु -80, IWL_RATE_MCS_3_INDEX पूर्ण,
	अणु -84, IWL_RATE_MCS_2_INDEX पूर्ण,
	अणु -85, IWL_RATE_MCS_1_INDEX पूर्ण,
	अणु S8_MIN, IWL_RATE_MCS_0_INDEXपूर्ण,
पूर्ण;

/* MCS index 9 is not valid क्रम 20MHz VHT channel width,
 * but is ok क्रम 40, 80 and 160MHz channels.
 */
अटल स्थिर काष्ठा rs_init_rate_info rs_optimal_rates_vht_20mhz[] = अणु
	अणु -60, IWL_RATE_MCS_8_INDEX पूर्ण,
	अणु -64, IWL_RATE_MCS_7_INDEX पूर्ण,
	अणु -68, IWL_RATE_MCS_6_INDEX पूर्ण,
	अणु -72, IWL_RATE_MCS_5_INDEX पूर्ण,
	अणु -80, IWL_RATE_MCS_4_INDEX पूर्ण,
	अणु -84, IWL_RATE_MCS_3_INDEX पूर्ण,
	अणु -85, IWL_RATE_MCS_2_INDEX पूर्ण,
	अणु -87, IWL_RATE_MCS_1_INDEX पूर्ण,
	अणु S8_MIN, IWL_RATE_MCS_0_INDEXपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा rs_init_rate_info rs_optimal_rates_vht[] = अणु
	अणु -60, IWL_RATE_MCS_9_INDEX पूर्ण,
	अणु -64, IWL_RATE_MCS_8_INDEX पूर्ण,
	अणु -68, IWL_RATE_MCS_7_INDEX पूर्ण,
	अणु -72, IWL_RATE_MCS_6_INDEX पूर्ण,
	अणु -80, IWL_RATE_MCS_5_INDEX पूर्ण,
	अणु -84, IWL_RATE_MCS_4_INDEX पूर्ण,
	अणु -85, IWL_RATE_MCS_3_INDEX पूर्ण,
	अणु -87, IWL_RATE_MCS_2_INDEX पूर्ण,
	अणु -88, IWL_RATE_MCS_1_INDEX पूर्ण,
	अणु S8_MIN, IWL_RATE_MCS_0_INDEX पूर्ण,
पूर्ण;

#घोषणा IWL_RS_LOW_RSSI_THRESHOLD (-76) /* dBm */

/* Init the optimal rate based on STA caps
 * This combined with rssi is used to report the last tx rate
 * to userspace when we haven't transmitted enough frames.
 */
अटल व्योम rs_init_optimal_rate(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा iwl_lq_sta *lq_sta)
अणु
	काष्ठा rs_rate *rate = &lq_sta->optimal_rate;

	अगर (lq_sta->max_mimo2_rate_idx != IWL_RATE_INVALID)
		rate->type = lq_sta->is_vht ? LQ_VHT_MIMO2 : LQ_HT_MIMO2;
	अन्यथा अगर (lq_sta->max_siso_rate_idx != IWL_RATE_INVALID)
		rate->type = lq_sta->is_vht ? LQ_VHT_SISO : LQ_HT_SISO;
	अन्यथा अगर (lq_sta->band == NL80211_BAND_5GHZ)
		rate->type = LQ_LEGACY_A;
	अन्यथा
		rate->type = LQ_LEGACY_G;

	rate->bw = rs_bw_from_sta_bw(sta);
	rate->sgi = rs_sgi_allow(mvm, sta, rate, शून्य);

	/* ANT/LDPC/STBC aren't relevant क्रम the rate reported to userspace */

	अगर (is_mimo(rate)) अणु
		lq_sta->optimal_rate_mask = lq_sta->active_mimo2_rate;
	पूर्ण अन्यथा अगर (is_siso(rate)) अणु
		lq_sta->optimal_rate_mask = lq_sta->active_siso_rate;
	पूर्ण अन्यथा अणु
		lq_sta->optimal_rate_mask = lq_sta->active_legacy_rate;

		अगर (lq_sta->band == NL80211_BAND_5GHZ) अणु
			lq_sta->optimal_rates = rs_optimal_rates_5ghz_legacy;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_5ghz_legacy);
		पूर्ण अन्यथा अणु
			lq_sta->optimal_rates = rs_optimal_rates_24ghz_legacy;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_24ghz_legacy);
		पूर्ण
	पूर्ण

	अगर (is_vht(rate)) अणु
		अगर (rate->bw == RATE_MCS_CHAN_WIDTH_20) अणु
			lq_sta->optimal_rates = rs_optimal_rates_vht_20mhz;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_vht_20mhz);
		पूर्ण अन्यथा अणु
			lq_sta->optimal_rates = rs_optimal_rates_vht;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_vht);
		पूर्ण
	पूर्ण अन्यथा अगर (is_ht(rate)) अणु
		lq_sta->optimal_rates = rs_optimal_rates_ht;
		lq_sta->optimal_nentries = ARRAY_SIZE(rs_optimal_rates_ht);
	पूर्ण
पूर्ण

/* Compute the optimal rate index based on RSSI */
अटल काष्ठा rs_rate *rs_get_optimal_rate(काष्ठा iwl_mvm *mvm,
					   काष्ठा iwl_lq_sta *lq_sta)
अणु
	काष्ठा rs_rate *rate = &lq_sta->optimal_rate;
	पूर्णांक i;

	rate->index = find_first_bit(&lq_sta->optimal_rate_mask,
				     BITS_PER_LONG);

	क्रम (i = 0; i < lq_sta->optimal_nentries; i++) अणु
		पूर्णांक rate_idx = lq_sta->optimal_rates[i].rate_idx;

		अगर ((lq_sta->pers.last_rssi >= lq_sta->optimal_rates[i].rssi) &&
		    (BIT(rate_idx) & lq_sta->optimal_rate_mask)) अणु
			rate->index = rate_idx;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rate;
पूर्ण

/* Choose an initial legacy rate and antenna to use based on the RSSI
 * of last Rx
 */
अटल व्योम rs_get_initial_rate(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_sta *sta,
				काष्ठा iwl_lq_sta *lq_sta,
				क्रमागत nl80211_band band,
				काष्ठा rs_rate *rate)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	पूर्णांक i, nentries;
	अचिन्हित दीर्घ active_rate;
	s8 best_rssi = S8_MIN;
	u8 best_ant = ANT_NONE;
	u8 valid_tx_ant = iwl_mvm_get_valid_tx_ant(mvm);
	स्थिर काष्ठा rs_init_rate_info *initial_rates;

	क्रम (i = 0; i < ARRAY_SIZE(lq_sta->pers.chain_संकेत); i++) अणु
		अगर (!(lq_sta->pers.chains & BIT(i)))
			जारी;

		अगर (lq_sta->pers.chain_संकेत[i] > best_rssi) अणु
			best_rssi = lq_sta->pers.chain_संकेत[i];
			best_ant = BIT(i);
		पूर्ण
	पूर्ण

	IWL_DEBUG_RATE(mvm, "Best ANT: %s Best RSSI: %d\n",
		       rs_pretty_ant(best_ant), best_rssi);

	अगर (best_ant != ANT_A && best_ant != ANT_B)
		rate->ant = first_antenna(valid_tx_ant);
	अन्यथा
		rate->ant = best_ant;

	rate->sgi = false;
	rate->ldpc = false;
	rate->bw = RATE_MCS_CHAN_WIDTH_20;

	rate->index = find_first_bit(&lq_sta->active_legacy_rate,
				     BITS_PER_LONG);

	अगर (band == NL80211_BAND_5GHZ) अणु
		rate->type = LQ_LEGACY_A;
		initial_rates = rs_optimal_rates_5ghz_legacy;
		nentries = ARRAY_SIZE(rs_optimal_rates_5ghz_legacy);
	पूर्ण अन्यथा अणु
		rate->type = LQ_LEGACY_G;
		initial_rates = rs_optimal_rates_24ghz_legacy;
		nentries = ARRAY_SIZE(rs_optimal_rates_24ghz_legacy);
	पूर्ण

	अगर (!IWL_MVM_RS_RSSI_BASED_INIT_RATE)
		जाओ out;

	/* Start from a higher rate अगर the corresponding debug capability
	 * is enabled. The rate is chosen according to AP capabilities.
	 * In हाल of VHT/HT when the rssi is low fallback to the हाल of
	 * legacy rates.
	 */
	अगर (sta->vht_cap.vht_supported &&
	    best_rssi > IWL_RS_LOW_RSSI_THRESHOLD) अणु
		/*
		 * In AP mode, when a new station associates, rs is initialized
		 * immediately upon association completion, beक्रमe the phy
		 * context is updated with the association parameters, so the
		 * sta bandwidth might be wider than the phy context allows.
		 * To aव्योम this issue, always initialize rs with 20mhz
		 * bandwidth rate, and after authorization, when the phy context
		 * is alपढ़ोy up-to-date, re-init rs with the correct bw.
		 */
		u32 bw = mvmsta->sta_state < IEEE80211_STA_AUTHORIZED ?
				RATE_MCS_CHAN_WIDTH_20 : rs_bw_from_sta_bw(sta);

		चयन (bw) अणु
		हाल RATE_MCS_CHAN_WIDTH_40:
		हाल RATE_MCS_CHAN_WIDTH_80:
		हाल RATE_MCS_CHAN_WIDTH_160:
			initial_rates = rs_optimal_rates_vht;
			nentries = ARRAY_SIZE(rs_optimal_rates_vht);
			अवरोध;
		हाल RATE_MCS_CHAN_WIDTH_20:
			initial_rates = rs_optimal_rates_vht_20mhz;
			nentries = ARRAY_SIZE(rs_optimal_rates_vht_20mhz);
			अवरोध;
		शेष:
			IWL_ERR(mvm, "Invalid BW %d\n", sta->bandwidth);
			जाओ out;
		पूर्ण

		active_rate = lq_sta->active_siso_rate;
		rate->type = LQ_VHT_SISO;
		rate->bw = bw;
	पूर्ण अन्यथा अगर (sta->ht_cap.ht_supported &&
		   best_rssi > IWL_RS_LOW_RSSI_THRESHOLD) अणु
		initial_rates = rs_optimal_rates_ht;
		nentries = ARRAY_SIZE(rs_optimal_rates_ht);
		active_rate = lq_sta->active_siso_rate;
		rate->type = LQ_HT_SISO;
	पूर्ण अन्यथा अणु
		active_rate = lq_sta->active_legacy_rate;
	पूर्ण

	क्रम (i = 0; i < nentries; i++) अणु
		पूर्णांक rate_idx = initial_rates[i].rate_idx;

		अगर ((best_rssi >= initial_rates[i].rssi) &&
		    (BIT(rate_idx) & active_rate)) अणु
			rate->index = rate_idx;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	rs_dump_rate(mvm, rate, "INITIAL");
पूर्ण

/* Save info about RSSI of last Rx */
व्योम rs_update_last_rssi(काष्ठा iwl_mvm *mvm,
			 काष्ठा iwl_mvm_sta *mvmsta,
			 काष्ठा ieee80211_rx_status *rx_status)
अणु
	काष्ठा iwl_lq_sta *lq_sta = &mvmsta->lq_sta.rs_drv;
	पूर्णांक i;

	lq_sta->pers.chains = rx_status->chains;
	lq_sta->pers.chain_संकेत[0] = rx_status->chain_संकेत[0];
	lq_sta->pers.chain_संकेत[1] = rx_status->chain_संकेत[1];
	lq_sta->pers.chain_संकेत[2] = rx_status->chain_संकेत[2];
	lq_sta->pers.last_rssi = S8_MIN;

	क्रम (i = 0; i < ARRAY_SIZE(lq_sta->pers.chain_संकेत); i++) अणु
		अगर (!(lq_sta->pers.chains & BIT(i)))
			जारी;

		अगर (lq_sta->pers.chain_संकेत[i] > lq_sta->pers.last_rssi)
			lq_sta->pers.last_rssi = lq_sta->pers.chain_संकेत[i];
	पूर्ण
पूर्ण

/*
 * rs_initialize_lq - Initialize a station's hardware rate table
 *
 * The uCode's station table contains a table of fallback rates
 * क्रम स्वतःmatic fallback during transmission.
 *
 * NOTE: This sets up a शेष set of values.  These will be replaced later
 *       अगर the driver's iwl-agn-rs rate scaling algorithm is used, instead of
 *       rc80211_simple.
 *
 * NOTE: Run REPLY_ADD_STA command to set up station table entry, beक्रमe
 *       calling this function (which runs REPLY_TX_LINK_QUALITY_CMD,
 *       which requires station table entry to exist).
 */
अटल व्योम rs_initialize_lq(काष्ठा iwl_mvm *mvm,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा iwl_lq_sta *lq_sta,
			     क्रमागत nl80211_band band)
अणु
	काष्ठा iwl_scale_tbl_info *tbl;
	काष्ठा rs_rate *rate;
	u8 active_tbl = 0;

	अगर (!sta || !lq_sta)
		वापस;

	अगर (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	अन्यथा
		active_tbl = rs_search_tbl(lq_sta->active_tbl);

	tbl = &(lq_sta->lq_info[active_tbl]);
	rate = &tbl->rate;

	rs_get_initial_rate(mvm, sta, lq_sta, band, rate);
	rs_init_optimal_rate(mvm, sta, lq_sta);

	WARN_ONCE(rate->ant != ANT_A && rate->ant != ANT_B,
		  "ant: 0x%x, chains 0x%x, fw tx ant: 0x%x, nvm tx ant: 0x%x\n",
		  rate->ant, lq_sta->pers.chains, mvm->fw->valid_tx_ant,
		  mvm->nvm_data ? mvm->nvm_data->valid_tx_ant : ANT_INVALID);

	tbl->column = rs_get_column_from_rate(rate);

	rs_set_expected_tpt_table(lq_sta, tbl);
	rs_fill_lq_cmd(mvm, sta, lq_sta, rate);
	/* TODO restore station should remember the lq cmd */
	iwl_mvm_send_lq_cmd(mvm, &lq_sta->lq);
पूर्ण

अटल व्योम rs_drv_get_rate(व्योम *mvm_r, काष्ठा ieee80211_sta *sta,
			    व्योम *mvm_sta,
			    काष्ठा ieee80211_tx_rate_control *txrc)
अणु
	काष्ठा iwl_op_mode *op_mode = mvm_r;
	काष्ठा iwl_mvm *mvm __maybe_unused = IWL_OP_MODE_GET_MVM(op_mode);
	काष्ठा sk_buff *skb = txrc->skb;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा iwl_lq_sta *lq_sta;
	काष्ठा rs_rate *optimal_rate;
	u32 last_ucode_rate;

	अगर (sta && !iwl_mvm_sta_from_mac80211(sta)->vअगर) अणु
		/* अगर vअगर isn't initialized mvm doesn't know about
		 * this station, so करोn't करो anything with the it
		 */
		sta = शून्य;
		mvm_sta = शून्य;
	पूर्ण

	अगर (!mvm_sta)
		वापस;

	lq_sta = mvm_sta;
	iwl_mvm_hwrate_to_tx_rate(lq_sta->last_rate_n_flags,
				  info->band, &info->control.rates[0]);
	info->control.rates[0].count = 1;

	/* Report the optimal rate based on rssi and STA caps अगर we haven't
	 * converged yet (too little traffic) or exploring other modulations
	 */
	अगर (lq_sta->rs_state != RS_STATE_STAY_IN_COLUMN) अणु
		optimal_rate = rs_get_optimal_rate(mvm, lq_sta);
		last_ucode_rate = ucode_rate_from_rs_rate(mvm,
							  optimal_rate);
		iwl_mvm_hwrate_to_tx_rate(last_ucode_rate, info->band,
					  &txrc->reported_rate);
	पूर्ण
पूर्ण

अटल व्योम *rs_drv_alloc_sta(व्योम *mvm_rate, काष्ठा ieee80211_sta *sta,
			      gfp_t gfp)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_op_mode *op_mode = (काष्ठा iwl_op_mode *)mvm_rate;
	काष्ठा iwl_mvm *mvm  = IWL_OP_MODE_GET_MVM(op_mode);
	काष्ठा iwl_lq_sta *lq_sta = &mvmsta->lq_sta.rs_drv;

	IWL_DEBUG_RATE(mvm, "create station rate scale window\n");

	lq_sta->pers.drv = mvm;
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	lq_sta->pers.dbg_fixed_rate = 0;
	lq_sta->pers.dbg_fixed_txp_reduction = TPC_INVALID;
	lq_sta->pers.ss_क्रमce = RS_SS_FORCE_NONE;
#पूर्ण_अगर
	lq_sta->pers.chains = 0;
	स_रखो(lq_sta->pers.chain_संकेत, 0, माप(lq_sta->pers.chain_संकेत));
	lq_sta->pers.last_rssi = S8_MIN;

	वापस lq_sta;
पूर्ण

अटल पूर्णांक rs_vht_highest_rx_mcs_index(काष्ठा ieee80211_sta_vht_cap *vht_cap,
				       पूर्णांक nss)
अणु
	u16 rx_mcs = le16_to_cpu(vht_cap->vht_mcs.rx_mcs_map) &
		(0x3 << (2 * (nss - 1)));
	rx_mcs >>= (2 * (nss - 1));

	अगर (rx_mcs == IEEE80211_VHT_MCS_SUPPORT_0_7)
		वापस IWL_RATE_MCS_7_INDEX;
	अन्यथा अगर (rx_mcs == IEEE80211_VHT_MCS_SUPPORT_0_8)
		वापस IWL_RATE_MCS_8_INDEX;
	अन्यथा अगर (rx_mcs == IEEE80211_VHT_MCS_SUPPORT_0_9)
		वापस IWL_RATE_MCS_9_INDEX;

	WARN_ON_ONCE(rx_mcs != IEEE80211_VHT_MCS_NOT_SUPPORTED);
	वापस -1;
पूर्ण

अटल व्योम rs_vht_set_enabled_rates(काष्ठा ieee80211_sta *sta,
				     काष्ठा ieee80211_sta_vht_cap *vht_cap,
				     काष्ठा iwl_lq_sta *lq_sta)
अणु
	पूर्णांक i;
	पूर्णांक highest_mcs = rs_vht_highest_rx_mcs_index(vht_cap, 1);

	अगर (highest_mcs >= IWL_RATE_MCS_0_INDEX) अणु
		क्रम (i = IWL_RATE_MCS_0_INDEX; i <= highest_mcs; i++) अणु
			अगर (i == IWL_RATE_9M_INDEX)
				जारी;

			/* VHT MCS9 isn't valid क्रम 20Mhz क्रम NSS=1,2 */
			अगर (i == IWL_RATE_MCS_9_INDEX &&
			    sta->bandwidth == IEEE80211_STA_RX_BW_20)
				जारी;

			lq_sta->active_siso_rate |= BIT(i);
		पूर्ण
	पूर्ण

	अगर (sta->rx_nss < 2)
		वापस;

	highest_mcs = rs_vht_highest_rx_mcs_index(vht_cap, 2);
	अगर (highest_mcs >= IWL_RATE_MCS_0_INDEX) अणु
		क्रम (i = IWL_RATE_MCS_0_INDEX; i <= highest_mcs; i++) अणु
			अगर (i == IWL_RATE_9M_INDEX)
				जारी;

			/* VHT MCS9 isn't valid क्रम 20Mhz क्रम NSS=1,2 */
			अगर (i == IWL_RATE_MCS_9_INDEX &&
			    sta->bandwidth == IEEE80211_STA_RX_BW_20)
				जारी;

			lq_sta->active_mimo2_rate |= BIT(i);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rs_ht_init(काष्ठा iwl_mvm *mvm,
		       काष्ठा ieee80211_sta *sta,
		       काष्ठा iwl_lq_sta *lq_sta,
		       काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	/* active_siso_rate mask includes 9 MBits (bit 5),
	 * and CCK (bits 0-3), supp_rates[] करोes not;
	 * shअगरt to convert क्रमmat, क्रमce 9 MBits off.
	 */
	lq_sta->active_siso_rate = ht_cap->mcs.rx_mask[0] << 1;
	lq_sta->active_siso_rate |= ht_cap->mcs.rx_mask[0] & 0x1;
	lq_sta->active_siso_rate &= ~((u16)0x2);
	lq_sta->active_siso_rate <<= IWL_FIRST_OFDM_RATE;

	lq_sta->active_mimo2_rate = ht_cap->mcs.rx_mask[1] << 1;
	lq_sta->active_mimo2_rate |= ht_cap->mcs.rx_mask[1] & 0x1;
	lq_sta->active_mimo2_rate &= ~((u16)0x2);
	lq_sta->active_mimo2_rate <<= IWL_FIRST_OFDM_RATE;

	अगर (mvm->cfg->ht_params->ldpc &&
	    (ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING))
		lq_sta->ldpc = true;

	अगर (mvm->cfg->ht_params->stbc &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1) &&
	    (ht_cap->cap & IEEE80211_HT_CAP_RX_STBC))
		lq_sta->stbc_capable = true;

	lq_sta->is_vht = false;
पूर्ण

अटल व्योम rs_vht_init(काष्ठा iwl_mvm *mvm,
			काष्ठा ieee80211_sta *sta,
			काष्ठा iwl_lq_sta *lq_sta,
			काष्ठा ieee80211_sta_vht_cap *vht_cap)
अणु
	rs_vht_set_enabled_rates(sta, vht_cap, lq_sta);

	अगर (mvm->cfg->ht_params->ldpc &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_RXLDPC))
		lq_sta->ldpc = true;

	अगर (mvm->cfg->ht_params->stbc &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1) &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_RXSTBC_MASK))
		lq_sta->stbc_capable = true;

	अगर (fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_BEAMFORMER) &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1) &&
	    (vht_cap->cap & IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE))
		lq_sta->bfer_capable = true;

	lq_sta->is_vht = true;
पूर्ण

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम iwl_mvm_reset_frame_stats(काष्ठा iwl_mvm *mvm)
अणु
	spin_lock_bh(&mvm->drv_stats_lock);
	स_रखो(&mvm->drv_rx_stats, 0, माप(mvm->drv_rx_stats));
	spin_unlock_bh(&mvm->drv_stats_lock);
पूर्ण

व्योम iwl_mvm_update_frame_stats(काष्ठा iwl_mvm *mvm, u32 rate, bool agg)
अणु
	u8 nss = 0;

	spin_lock(&mvm->drv_stats_lock);

	अगर (agg)
		mvm->drv_rx_stats.agg_frames++;

	mvm->drv_rx_stats.success_frames++;

	चयन (rate & RATE_MCS_CHAN_WIDTH_MSK) अणु
	हाल RATE_MCS_CHAN_WIDTH_20:
		mvm->drv_rx_stats.bw_20_frames++;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_40:
		mvm->drv_rx_stats.bw_40_frames++;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_80:
		mvm->drv_rx_stats.bw_80_frames++;
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_160:
		mvm->drv_rx_stats.bw_160_frames++;
		अवरोध;
	शेष:
		WARN_ONCE(1, "bad BW. rate 0x%x", rate);
	पूर्ण

	अगर (rate & RATE_MCS_HT_MSK) अणु
		mvm->drv_rx_stats.ht_frames++;
		nss = ((rate & RATE_HT_MCS_NSS_MSK) >> RATE_HT_MCS_NSS_POS) + 1;
	पूर्ण अन्यथा अगर (rate & RATE_MCS_VHT_MSK) अणु
		mvm->drv_rx_stats.vht_frames++;
		nss = ((rate & RATE_VHT_MCS_NSS_MSK) >>
		       RATE_VHT_MCS_NSS_POS) + 1;
	पूर्ण अन्यथा अणु
		mvm->drv_rx_stats.legacy_frames++;
	पूर्ण

	अगर (nss == 1)
		mvm->drv_rx_stats.siso_frames++;
	अन्यथा अगर (nss == 2)
		mvm->drv_rx_stats.mimo2_frames++;

	अगर (rate & RATE_MCS_SGI_MSK)
		mvm->drv_rx_stats.sgi_frames++;
	अन्यथा
		mvm->drv_rx_stats.ngi_frames++;

	mvm->drv_rx_stats.last_rates[mvm->drv_rx_stats.last_frame_idx] = rate;
	mvm->drv_rx_stats.last_frame_idx =
		(mvm->drv_rx_stats.last_frame_idx + 1) %
			ARRAY_SIZE(mvm->drv_rx_stats.last_rates);

	spin_unlock(&mvm->drv_stats_lock);
पूर्ण
#पूर्ण_अगर

/*
 * Called after adding a new station to initialize rate scaling
 */
अटल व्योम rs_drv_rate_init(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			     क्रमागत nl80211_band band)
अणु
	पूर्णांक i, j;
	काष्ठा ieee80211_hw *hw = mvm->hw;
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_lq_sta *lq_sta = &mvmsta->lq_sta.rs_drv;
	काष्ठा ieee80211_supported_band *sband;
	अचिन्हित दीर्घ supp; /* must be अचिन्हित दीर्घ क्रम क्रम_each_set_bit */

	lockdep_निश्चित_held(&mvmsta->lq_sta.rs_drv.pers.lock);

	/* clear all non-persistent lq data */
	स_रखो(lq_sta, 0, दुरत्व(typeof(*lq_sta), pers));

	sband = hw->wiphy->bands[band];

	lq_sta->lq.sta_id = mvmsta->sta_id;
	mvmsta->amsdu_enabled = 0;
	mvmsta->max_amsdu_len = sta->max_amsdu_len;

	क्रम (j = 0; j < LQ_SIZE; j++)
		rs_rate_scale_clear_tbl_winकरोws(mvm, &lq_sta->lq_info[j]);

	lq_sta->flush_समयr = 0;
	lq_sta->last_tx = jअगरfies;

	IWL_DEBUG_RATE(mvm,
		       "LQ: *** rate scale station global init for station %d ***\n",
		       mvmsta->sta_id);
	/* TODO: what is a good starting rate क्रम STA? About middle? Maybe not
	 * the lowest or the highest rate.. Could consider using RSSI from
	 * previous packets? Need to have IEEE 802.1X auth succeed immediately
	 * after assoc.. */

	lq_sta->missed_rate_counter = IWL_MVM_RS_MISSED_RATE_MAX;
	lq_sta->band = sband->band;
	/*
	 * active legacy rates as per supported rates biपंचांगap
	 */
	supp = sta->supp_rates[sband->band];
	lq_sta->active_legacy_rate = 0;
	क्रम_each_set_bit(i, &supp, BITS_PER_LONG)
		lq_sta->active_legacy_rate |= BIT(sband->bitrates[i].hw_value);

	/* TODO: should probably account क्रम rx_highest क्रम both HT/VHT */
	अगर (!vht_cap || !vht_cap->vht_supported)
		rs_ht_init(mvm, sta, lq_sta, ht_cap);
	अन्यथा
		rs_vht_init(mvm, sta, lq_sta, vht_cap);

	lq_sta->max_legacy_rate_idx =
		rs_get_max_rate_from_mask(lq_sta->active_legacy_rate);
	lq_sta->max_siso_rate_idx =
		rs_get_max_rate_from_mask(lq_sta->active_siso_rate);
	lq_sta->max_mimo2_rate_idx =
		rs_get_max_rate_from_mask(lq_sta->active_mimo2_rate);

	IWL_DEBUG_RATE(mvm,
		       "LEGACY=%lX SISO=%lX MIMO2=%lX VHT=%d LDPC=%d STBC=%d BFER=%d\n",
		       lq_sta->active_legacy_rate,
		       lq_sta->active_siso_rate,
		       lq_sta->active_mimo2_rate,
		       lq_sta->is_vht, lq_sta->ldpc, lq_sta->stbc_capable,
		       lq_sta->bfer_capable);
	IWL_DEBUG_RATE(mvm, "MAX RATE: LEGACY=%d SISO=%d MIMO2=%d\n",
		       lq_sta->max_legacy_rate_idx,
		       lq_sta->max_siso_rate_idx,
		       lq_sta->max_mimo2_rate_idx);

	/* These values will be overridden later */
	lq_sta->lq.single_stream_ant_msk =
		iwl_mvm_bt_coex_get_single_ant_msk(mvm, iwl_mvm_get_valid_tx_ant(mvm));
	lq_sta->lq.dual_stream_ant_msk = ANT_AB;

	/* as शेष allow aggregation क्रम all tids */
	lq_sta->tx_agg_tid_en = IWL_AGG_ALL_TID;
	lq_sta->is_agg = 0;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	iwl_mvm_reset_frame_stats(mvm);
#पूर्ण_अगर
	rs_initialize_lq(mvm, sta, lq_sta, band);
पूर्ण

अटल व्योम rs_drv_rate_update(व्योम *mvm_r,
			       काष्ठा ieee80211_supported_band *sband,
			       काष्ठा cfg80211_chan_def *chandef,
			       काष्ठा ieee80211_sta *sta,
			       व्योम *priv_sta, u32 changed)
अणु
	काष्ठा iwl_op_mode *op_mode = mvm_r;
	काष्ठा iwl_mvm *mvm __maybe_unused = IWL_OP_MODE_GET_MVM(op_mode);
	u8 tid;

	अगर (!iwl_mvm_sta_from_mac80211(sta)->vअगर)
		वापस;

	/* Stop any ongoing aggregations as rs starts off assuming no agg */
	क्रम (tid = 0; tid < IWL_MAX_TID_COUNT; tid++)
		ieee80211_stop_tx_ba_session(sta, tid);

	iwl_mvm_rs_rate_init(mvm, sta, sband->band, true);
पूर्ण

अटल व्योम __iwl_mvm_rs_tx_status(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_sta *sta,
				   पूर्णांक tid, काष्ठा ieee80211_tx_info *info,
				   bool ndp)
अणु
	पूर्णांक legacy_success;
	पूर्णांक retries;
	पूर्णांक i;
	काष्ठा iwl_lq_cmd *table;
	u32 lq_hwrate;
	काष्ठा rs_rate lq_rate, tx_resp_rate;
	काष्ठा iwl_scale_tbl_info *curr_tbl, *other_tbl, *पंचांगp_tbl;
	u32 tlc_info = (uपूर्णांकptr_t)info->status.status_driver_data[0];
	u8 reduced_txp = tlc_info & RS_DRV_DATA_TXP_MSK;
	u8 lq_color = RS_DRV_DATA_LQ_COLOR_GET(tlc_info);
	u32 tx_resp_hwrate = (uपूर्णांकptr_t)info->status.status_driver_data[1];
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_lq_sta *lq_sta = &mvmsta->lq_sta.rs_drv;

	अगर (!lq_sta->pers.drv) अणु
		IWL_DEBUG_RATE(mvm, "Rate scaling not initialized yet.\n");
		वापस;
	पूर्ण

	/* This packet was aggregated but करोesn't carry status info */
	अगर ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(info->flags & IEEE80211_TX_STAT_AMPDU))
		वापस;

	अगर (rs_rate_from_ucode_rate(tx_resp_hwrate, info->band,
				    &tx_resp_rate)) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	/* Disable last tx check अगर we are debugging with fixed rate but
	 * update tx stats
	 */
	अगर (lq_sta->pers.dbg_fixed_rate) अणु
		पूर्णांक index = tx_resp_rate.index;
		क्रमागत rs_column column;
		पूर्णांक attempts, success;

		column = rs_get_column_from_rate(&tx_resp_rate);
		अगर (WARN_ONCE(column == RS_COLUMN_INVALID,
			      "Can't map rate 0x%x to column",
			      tx_resp_hwrate))
			वापस;

		अगर (info->flags & IEEE80211_TX_STAT_AMPDU) अणु
			attempts = info->status.ampdu_len;
			success = info->status.ampdu_ack_len;
		पूर्ण अन्यथा अणु
			attempts = info->status.rates[0].count;
			success = !!(info->flags & IEEE80211_TX_STAT_ACK);
		पूर्ण

		lq_sta->pers.tx_stats[column][index].total += attempts;
		lq_sta->pers.tx_stats[column][index].success += success;

		IWL_DEBUG_RATE(mvm, "Fixed rate 0x%x success %d attempts %d\n",
			       tx_resp_hwrate, success, attempts);
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (समय_after(jअगरfies,
		       (अचिन्हित दीर्घ)(lq_sta->last_tx +
				       (IWL_MVM_RS_IDLE_TIMEOUT * HZ)))) अणु
		IWL_DEBUG_RATE(mvm, "Tx idle for too long. reinit rs\n");
		/* reach here only in हाल of driver RS, call directly
		 * the unlocked version
		 */
		rs_drv_rate_init(mvm, sta, info->band);
		वापस;
	पूर्ण
	lq_sta->last_tx = jअगरfies;

	/* Ignore this Tx frame response अगर its initial rate करोesn't match
	 * that of latest Link Quality command.  There may be stragglers
	 * from a previous Link Quality command, but we're no दीर्घer पूर्णांकerested
	 * in those; they're either from the "active" mode while we're trying
	 * to check "search" mode, or a prior "search" mode after we've moved
	 * to a new "search" mode (which might become the new "active" mode).
	 */
	table = &lq_sta->lq;
	lq_hwrate = le32_to_cpu(table->rs_table[0]);
	अगर (rs_rate_from_ucode_rate(lq_hwrate, info->band, &lq_rate)) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	/* Here we actually compare this rate to the latest LQ command */
	अगर (lq_color != LQ_FLAG_COLOR_GET(table->flags)) अणु
		IWL_DEBUG_RATE(mvm,
			       "tx resp color 0x%x does not match 0x%x\n",
			       lq_color, LQ_FLAG_COLOR_GET(table->flags));

		/* Since rates mis-match, the last LQ command may have failed.
		 * After IWL_MISSED_RATE_MAX mis-matches, resync the uCode with
		 * ... driver.
		 */
		lq_sta->missed_rate_counter++;
		अगर (lq_sta->missed_rate_counter > IWL_MVM_RS_MISSED_RATE_MAX) अणु
			lq_sta->missed_rate_counter = 0;
			IWL_DEBUG_RATE(mvm,
				       "Too many rates mismatch. Send sync LQ. rs_state %d\n",
				       lq_sta->rs_state);
			iwl_mvm_send_lq_cmd(mvm, &lq_sta->lq);
		पूर्ण
		/* Regardless, ignore this status info क्रम outdated rate */
		वापस;
	पूर्ण

	/* Rate did match, so reset the missed_rate_counter */
	lq_sta->missed_rate_counter = 0;

	अगर (!lq_sta->search_better_tbl) अणु
		curr_tbl = &lq_sta->lq_info[lq_sta->active_tbl];
		other_tbl = &lq_sta->lq_info[rs_search_tbl(lq_sta->active_tbl)];
	पूर्ण अन्यथा अणु
		curr_tbl = &lq_sta->lq_info[rs_search_tbl(lq_sta->active_tbl)];
		other_tbl = &lq_sta->lq_info[lq_sta->active_tbl];
	पूर्ण

	अगर (WARN_ON_ONCE(!rs_rate_column_match(&lq_rate, &curr_tbl->rate))) अणु
		IWL_DEBUG_RATE(mvm,
			       "Neither active nor search matches tx rate\n");
		पंचांगp_tbl = &lq_sta->lq_info[lq_sta->active_tbl];
		rs_dump_rate(mvm, &पंचांगp_tbl->rate, "ACTIVE");
		पंचांगp_tbl = &lq_sta->lq_info[rs_search_tbl(lq_sta->active_tbl)];
		rs_dump_rate(mvm, &पंचांगp_tbl->rate, "SEARCH");
		rs_dump_rate(mvm, &lq_rate, "ACTUAL");

		/* no matching table found, let's by-pass the data collection
		 * and जारी to perक्रमm rate scale to find the rate table
		 */
		rs_stay_in_table(lq_sta, true);
		जाओ करोne;
	पूर्ण

	/* Updating the frame history depends on whether packets were
	 * aggregated.
	 *
	 * For aggregation, all packets were transmitted at the same rate, the
	 * first index पूर्णांकo rate scale table.
	 */
	अगर (info->flags & IEEE80211_TX_STAT_AMPDU) अणु
		rs_collect_tpc_data(mvm, lq_sta, curr_tbl, tx_resp_rate.index,
				    info->status.ampdu_len,
				    info->status.ampdu_ack_len,
				    reduced_txp);

		/* ampdu_ack_len = 0 marks no BA was received. For TLC, treat
		 * it as a single frame loss as we करोn't want the success ratio
		 * to dip too quickly because a BA wasn't received.
		 * For TPC, there's no need क्रम this optimisation since we want
		 * to recover very quickly from a bad घातer reduction and,
		 * thereक्रमe we'd like the success ratio to get an immediate hit
		 * when failing to get a BA, so we'd चयन back to a lower or
		 * zero घातer reduction. When FW transmits agg with a rate
		 * dअगरferent from the initial rate, it will not use reduced txp
		 * and will send BA notअगरication twice (one empty with reduced
		 * txp equal to the value from LQ and one with reduced txp 0).
		 * We need to update counters क्रम each txp level accordingly.
		 */
		अगर (info->status.ampdu_ack_len == 0)
			info->status.ampdu_len = 1;

		rs_collect_tlc_data(mvm, mvmsta, tid, curr_tbl,
				    tx_resp_rate.index,
				    info->status.ampdu_len,
				    info->status.ampdu_ack_len);

		/* Update success/fail counts अगर not searching क्रम new mode */
		अगर (lq_sta->rs_state == RS_STATE_STAY_IN_COLUMN) अणु
			lq_sta->total_success += info->status.ampdu_ack_len;
			lq_sta->total_failed += (info->status.ampdu_len -
					info->status.ampdu_ack_len);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* For legacy, update frame history with क्रम each Tx retry. */
		retries = info->status.rates[0].count - 1;
		/* HW करोesn't send more than 15 retries */
		retries = min(retries, 15);

		/* The last transmission may have been successful */
		legacy_success = !!(info->flags & IEEE80211_TX_STAT_ACK);
		/* Collect data क्रम each rate used during failed TX attempts */
		क्रम (i = 0; i <= retries; ++i) अणु
			lq_hwrate = le32_to_cpu(table->rs_table[i]);
			अगर (rs_rate_from_ucode_rate(lq_hwrate, info->band,
						    &lq_rate)) अणु
				WARN_ON_ONCE(1);
				वापस;
			पूर्ण

			/* Only collect stats अगर retried rate is in the same RS
			 * table as active/search.
			 */
			अगर (rs_rate_column_match(&lq_rate, &curr_tbl->rate))
				पंचांगp_tbl = curr_tbl;
			अन्यथा अगर (rs_rate_column_match(&lq_rate,
						      &other_tbl->rate))
				पंचांगp_tbl = other_tbl;
			अन्यथा
				जारी;

			rs_collect_tpc_data(mvm, lq_sta, पंचांगp_tbl,
					    tx_resp_rate.index, 1,
					    i < retries ? 0 : legacy_success,
					    reduced_txp);
			rs_collect_tlc_data(mvm, mvmsta, tid, पंचांगp_tbl,
					    tx_resp_rate.index, 1,
					    i < retries ? 0 : legacy_success);
		पूर्ण

		/* Update success/fail counts अगर not searching क्रम new mode */
		अगर (lq_sta->rs_state == RS_STATE_STAY_IN_COLUMN) अणु
			lq_sta->total_success += legacy_success;
			lq_sta->total_failed += retries + (1 - legacy_success);
		पूर्ण
	पूर्ण
	/* The last TX rate is cached in lq_sta; it's set in अगर/अन्यथा above */
	lq_sta->last_rate_n_flags = lq_hwrate;
	IWL_DEBUG_RATE(mvm, "reduced txpower: %d\n", reduced_txp);
करोne:
	/* See अगर there's a better rate or modulation mode to try. */
	अगर (sta->supp_rates[info->band])
		rs_rate_scale_perक्रमm(mvm, sta, lq_sta, tid, ndp);
पूर्ण

व्योम iwl_mvm_rs_tx_status(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			  पूर्णांक tid, काष्ठा ieee80211_tx_info *info, bool ndp)
अणु
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

	/* If it's locked we are in middle of init flow
	 * just रुको क्रम next tx status to update the lq_sta data
	 */
	अगर (!spin_trylock(&mvmsta->lq_sta.rs_drv.pers.lock))
		वापस;

	__iwl_mvm_rs_tx_status(mvm, sta, tid, info, ndp);
	spin_unlock(&mvmsta->lq_sta.rs_drv.pers.lock);
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
अटल व्योम rs_build_rates_table_from_fixed(काष्ठा iwl_mvm *mvm,
					    काष्ठा iwl_lq_cmd *lq_cmd,
					    क्रमागत nl80211_band band,
					    u32 ucode_rate)
अणु
	काष्ठा rs_rate rate;
	पूर्णांक i;
	पूर्णांक num_rates = ARRAY_SIZE(lq_cmd->rs_table);
	__le32 ucode_rate_le32 = cpu_to_le32(ucode_rate);
	u8 ant = (ucode_rate & RATE_MCS_ANT_ABC_MSK) >> RATE_MCS_ANT_POS;

	क्रम (i = 0; i < num_rates; i++)
		lq_cmd->rs_table[i] = ucode_rate_le32;

	अगर (rs_rate_from_ucode_rate(ucode_rate, band, &rate)) अणु
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	अगर (is_mimo(&rate))
		lq_cmd->mimo_delim = num_rates - 1;
	अन्यथा
		lq_cmd->mimo_delim = 0;

	lq_cmd->reduced_tpc = 0;

	अगर (num_of_ant(ant) == 1)
		lq_cmd->single_stream_ant_msk = ant;

	अगर (!mvm->trans->trans_cfg->gen2)
		lq_cmd->agg_frame_cnt_limit = LINK_QUAL_AGG_FRAME_LIMIT_DEF;
	अन्यथा
		lq_cmd->agg_frame_cnt_limit =
			LINK_QUAL_AGG_FRAME_LIMIT_GEN2_DEF;
पूर्ण
#पूर्ण_अगर /* CONFIG_MAC80211_DEBUGFS */

अटल व्योम rs_fill_rates_क्रम_column(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_lq_sta *lq_sta,
				     काष्ठा rs_rate *rate,
				     __le32 *rs_table, पूर्णांक *rs_table_index,
				     पूर्णांक num_rates, पूर्णांक num_retries,
				     u8 valid_tx_ant, bool toggle_ant)
अणु
	पूर्णांक i, j;
	__le32 ucode_rate;
	bool bottom_reached = false;
	पूर्णांक prev_rate_idx = rate->index;
	पूर्णांक end = LINK_QUAL_MAX_RETRY_NUM;
	पूर्णांक index = *rs_table_index;

	क्रम (i = 0; i < num_rates && index < end; i++) अणु
		क्रम (j = 0; j < num_retries && index < end; j++, index++) अणु
			ucode_rate = cpu_to_le32(ucode_rate_from_rs_rate(mvm,
									 rate));
			rs_table[index] = ucode_rate;
			अगर (toggle_ant)
				rs_toggle_antenna(valid_tx_ant, rate);
		पूर्ण

		prev_rate_idx = rate->index;
		bottom_reached = rs_get_lower_rate_in_column(lq_sta, rate);
		अगर (bottom_reached && !is_legacy(rate))
			अवरोध;
	पूर्ण

	अगर (!bottom_reached && !is_legacy(rate))
		rate->index = prev_rate_idx;

	*rs_table_index = index;
पूर्ण

/* Building the rate table is non trivial. When we're in MIMO2/VHT/80Mhz/SGI
 * column the rate table should look like this:
 *
 * rate[0] 0x400F019 VHT | ANT: AB BW: 80Mhz MCS: 9 NSS: 2 SGI
 * rate[1] 0x400F019 VHT | ANT: AB BW: 80Mhz MCS: 9 NSS: 2 SGI
 * rate[2] 0x400F018 VHT | ANT: AB BW: 80Mhz MCS: 8 NSS: 2 SGI
 * rate[3] 0x400F018 VHT | ANT: AB BW: 80Mhz MCS: 8 NSS: 2 SGI
 * rate[4] 0x400F017 VHT | ANT: AB BW: 80Mhz MCS: 7 NSS: 2 SGI
 * rate[5] 0x400F017 VHT | ANT: AB BW: 80Mhz MCS: 7 NSS: 2 SGI
 * rate[6] 0x4005007 VHT | ANT: A BW: 80Mhz MCS: 7 NSS: 1 NGI
 * rate[7] 0x4009006 VHT | ANT: B BW: 80Mhz MCS: 6 NSS: 1 NGI
 * rate[8] 0x4005005 VHT | ANT: A BW: 80Mhz MCS: 5 NSS: 1 NGI
 * rate[9] 0x800B Legacy | ANT: B Rate: 36 Mbps
 * rate[10] 0x4009 Legacy | ANT: A Rate: 24 Mbps
 * rate[11] 0x8007 Legacy | ANT: B Rate: 18 Mbps
 * rate[12] 0x4005 Legacy | ANT: A Rate: 12 Mbps
 * rate[13] 0x800F Legacy | ANT: B Rate: 9 Mbps
 * rate[14] 0x400D Legacy | ANT: A Rate: 6 Mbps
 * rate[15] 0x800D Legacy | ANT: B Rate: 6 Mbps
 */
अटल व्योम rs_build_rates_table(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_sta *sta,
				 काष्ठा iwl_lq_sta *lq_sta,
				 स्थिर काष्ठा rs_rate *initial_rate)
अणु
	काष्ठा rs_rate rate;
	पूर्णांक num_rates, num_retries, index = 0;
	u8 valid_tx_ant = 0;
	काष्ठा iwl_lq_cmd *lq_cmd = &lq_sta->lq;
	bool toggle_ant = false;
	u32 color;

	स_नकल(&rate, initial_rate, माप(rate));

	valid_tx_ant = iwl_mvm_get_valid_tx_ant(mvm);

	/* TODO: हटाओ old API when min FW API hits 14 */
	अगर (!fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_LQ_SS_PARAMS) &&
	    rs_stbc_allow(mvm, sta, lq_sta))
		rate.stbc = true;

	अगर (is_siso(&rate)) अणु
		num_rates = IWL_MVM_RS_INITIAL_SISO_NUM_RATES;
		num_retries = IWL_MVM_RS_HT_VHT_RETRIES_PER_RATE;
	पूर्ण अन्यथा अगर (is_mimo(&rate)) अणु
		num_rates = IWL_MVM_RS_INITIAL_MIMO_NUM_RATES;
		num_retries = IWL_MVM_RS_HT_VHT_RETRIES_PER_RATE;
	पूर्ण अन्यथा अणु
		num_rates = IWL_MVM_RS_INITIAL_LEGACY_NUM_RATES;
		num_retries = IWL_MVM_RS_INITIAL_LEGACY_RETRIES;
		toggle_ant = true;
	पूर्ण

	rs_fill_rates_क्रम_column(mvm, lq_sta, &rate, lq_cmd->rs_table, &index,
				 num_rates, num_retries, valid_tx_ant,
				 toggle_ant);

	rs_get_lower_rate_करोwn_column(lq_sta, &rate);

	अगर (is_siso(&rate)) अणु
		num_rates = IWL_MVM_RS_SECONDARY_SISO_NUM_RATES;
		num_retries = IWL_MVM_RS_SECONDARY_SISO_RETRIES;
		lq_cmd->mimo_delim = index;
	पूर्ण अन्यथा अगर (is_legacy(&rate)) अणु
		num_rates = IWL_MVM_RS_SECONDARY_LEGACY_NUM_RATES;
		num_retries = IWL_MVM_RS_SECONDARY_LEGACY_RETRIES;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(1);
	पूर्ण

	toggle_ant = true;

	rs_fill_rates_क्रम_column(mvm, lq_sta, &rate, lq_cmd->rs_table, &index,
				 num_rates, num_retries, valid_tx_ant,
				 toggle_ant);

	rs_get_lower_rate_करोwn_column(lq_sta, &rate);

	num_rates = IWL_MVM_RS_SECONDARY_LEGACY_NUM_RATES;
	num_retries = IWL_MVM_RS_SECONDARY_LEGACY_RETRIES;

	rs_fill_rates_क्रम_column(mvm, lq_sta, &rate, lq_cmd->rs_table, &index,
				 num_rates, num_retries, valid_tx_ant,
				 toggle_ant);

	/* update the color of the LQ command (as a counter at bits 1-3) */
	color = LQ_FLAGS_COLOR_INC(LQ_FLAG_COLOR_GET(lq_cmd->flags));
	lq_cmd->flags = LQ_FLAG_COLOR_SET(lq_cmd->flags, color);
पूर्ण

काष्ठा rs_bfer_active_iter_data अणु
	काष्ठा ieee80211_sta *exclude_sta;
	काष्ठा iwl_mvm_sta *bfer_mvmsta;
पूर्ण;

अटल व्योम rs_bfer_active_iter(व्योम *_data,
				काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rs_bfer_active_iter_data *data = _data;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा iwl_lq_cmd *lq_cmd = &mvmsta->lq_sta.rs_drv.lq;
	u32 ss_params = le32_to_cpu(lq_cmd->ss_params);

	अगर (sta == data->exclude_sta)
		वापस;

	/* The current sta has BFER allowed */
	अगर (ss_params & LQ_SS_BFER_ALLOWED) अणु
		WARN_ON_ONCE(data->bfer_mvmsta != शून्य);

		data->bfer_mvmsta = mvmsta;
	पूर्ण
पूर्ण

अटल पूर्णांक rs_bfer_priority(काष्ठा iwl_mvm_sta *sta)
अणु
	पूर्णांक prio = -1;
	क्रमागत nl80211_अगरtype vअगरtype = ieee80211_vअगर_type_p2p(sta->vअगर);

	चयन (vअगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		prio = 3;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		prio = 2;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		prio = 1;
		अवरोध;
	शेष:
		WARN_ONCE(true, "viftype %d sta_id %d", vअगरtype, sta->sta_id);
		prio = -1;
	पूर्ण

	वापस prio;
पूर्ण

/* Returns >0 अगर sta1 has a higher BFER priority compared to sta2 */
अटल पूर्णांक rs_bfer_priority_cmp(काष्ठा iwl_mvm_sta *sta1,
				काष्ठा iwl_mvm_sta *sta2)
अणु
	पूर्णांक prio1 = rs_bfer_priority(sta1);
	पूर्णांक prio2 = rs_bfer_priority(sta2);

	अगर (prio1 > prio2)
		वापस 1;
	अगर (prio1 < prio2)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम rs_set_lq_ss_params(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_sta *sta,
				काष्ठा iwl_lq_sta *lq_sta,
				स्थिर काष्ठा rs_rate *initial_rate)
अणु
	काष्ठा iwl_lq_cmd *lq_cmd = &lq_sta->lq;
	काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	काष्ठा rs_bfer_active_iter_data data = अणु
		.exclude_sta = sta,
		.bfer_mvmsta = शून्य,
	पूर्ण;
	काष्ठा iwl_mvm_sta *bfer_mvmsta = शून्य;
	u32 ss_params = LQ_SS_PARAMS_VALID;

	अगर (!iwl_mvm_bt_coex_is_mimo_allowed(mvm, sta))
		जाओ out;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	/* Check अगर क्रमcing the decision is configured.
	 * Note that SISO is क्रमced by not allowing STBC or BFER
	 */
	अगर (lq_sta->pers.ss_क्रमce == RS_SS_FORCE_STBC)
		ss_params |= (LQ_SS_STBC_1SS_ALLOWED | LQ_SS_FORCE);
	अन्यथा अगर (lq_sta->pers.ss_क्रमce == RS_SS_FORCE_BFER)
		ss_params |= (LQ_SS_BFER_ALLOWED | LQ_SS_FORCE);

	अगर (lq_sta->pers.ss_क्रमce != RS_SS_FORCE_NONE) अणु
		IWL_DEBUG_RATE(mvm, "Forcing single stream Tx decision %d\n",
			       lq_sta->pers.ss_क्रमce);
		जाओ out;
	पूर्ण
#पूर्ण_अगर

	अगर (lq_sta->stbc_capable)
		ss_params |= LQ_SS_STBC_1SS_ALLOWED;

	अगर (!lq_sta->bfer_capable)
		जाओ out;

	ieee80211_iterate_stations_atomic(mvm->hw,
					  rs_bfer_active_iter,
					  &data);
	bfer_mvmsta = data.bfer_mvmsta;

	/* This code is safe as it करोesn't run concurrently क्रम dअगरferent
	 * stations. This is guaranteed by the fact that calls to
	 * ieee80211_tx_status wouldn't run concurrently क्रम a single HW.
	 */
	अगर (!bfer_mvmsta) अणु
		IWL_DEBUG_RATE(mvm, "No sta with BFER allowed found. Allow\n");

		ss_params |= LQ_SS_BFER_ALLOWED;
		जाओ out;
	पूर्ण

	IWL_DEBUG_RATE(mvm, "Found existing sta %d with BFER activated\n",
		       bfer_mvmsta->sta_id);

	/* Disallow BFER on another STA अगर active and we're a higher priority */
	अगर (rs_bfer_priority_cmp(mvmsta, bfer_mvmsta) > 0) अणु
		काष्ठा iwl_lq_cmd *bfersta_lq_cmd =
			&bfer_mvmsta->lq_sta.rs_drv.lq;
		u32 bfersta_ss_params = le32_to_cpu(bfersta_lq_cmd->ss_params);

		bfersta_ss_params &= ~LQ_SS_BFER_ALLOWED;
		bfersta_lq_cmd->ss_params = cpu_to_le32(bfersta_ss_params);
		iwl_mvm_send_lq_cmd(mvm, bfersta_lq_cmd);

		ss_params |= LQ_SS_BFER_ALLOWED;
		IWL_DEBUG_RATE(mvm,
			       "Lower priority BFER sta found (%d). Switch BFER\n",
			       bfer_mvmsta->sta_id);
	पूर्ण
out:
	lq_cmd->ss_params = cpu_to_le32(ss_params);
पूर्ण

अटल व्योम rs_fill_lq_cmd(काष्ठा iwl_mvm *mvm,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा iwl_lq_sta *lq_sta,
			   स्थिर काष्ठा rs_rate *initial_rate)
अणु
	काष्ठा iwl_lq_cmd *lq_cmd = &lq_sta->lq;
	काष्ठा iwl_mvm_sta *mvmsta;
	काष्ठा iwl_mvm_vअगर *mvmvअगर;

	lq_cmd->agg_disable_start_th = IWL_MVM_RS_AGG_DISABLE_START;
	lq_cmd->agg_समय_limit =
		cpu_to_le16(IWL_MVM_RS_AGG_TIME_LIMIT);

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	अगर (lq_sta->pers.dbg_fixed_rate) अणु
		rs_build_rates_table_from_fixed(mvm, lq_cmd,
						lq_sta->band,
						lq_sta->pers.dbg_fixed_rate);
		वापस;
	पूर्ण
#पूर्ण_अगर
	अगर (WARN_ON_ONCE(!sta || !initial_rate))
		वापस;

	rs_build_rates_table(mvm, sta, lq_sta, initial_rate);

	अगर (fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_LQ_SS_PARAMS))
		rs_set_lq_ss_params(mvm, sta, lq_sta, initial_rate);

	mvmsta = iwl_mvm_sta_from_mac80211(sta);
	mvmvअगर = iwl_mvm_vअगर_from_mac80211(mvmsta->vअगर);

	अगर (!fw_has_capa(&mvm->fw->ucode_capa, IWL_UCODE_TLV_CAPA_COEX_SCHEMA_2) &&
	    num_of_ant(initial_rate->ant) == 1)
		lq_cmd->single_stream_ant_msk = initial_rate->ant;

	lq_cmd->agg_frame_cnt_limit = mvmsta->max_agg_bufsize;

	/*
	 * In हाल of low latency, tell the firmware to leave a frame in the
	 * Tx Fअगरo so that it can start a transaction in the same TxOP. This
	 * basically allows the firmware to send bursts.
	 */
	अगर (iwl_mvm_vअगर_low_latency(mvmvअगर))
		lq_cmd->agg_frame_cnt_limit--;

	अगर (mvmsta->vअगर->p2p)
		lq_cmd->flags |= LQ_FLAG_USE_RTS_MSK;

	lq_cmd->agg_समय_limit =
			cpu_to_le16(iwl_mvm_coex_agg_समय_limit(mvm, sta));
पूर्ण

अटल व्योम *rs_alloc(काष्ठा ieee80211_hw *hw)
अणु
	वापस hw->priv;
पूर्ण

/* rate scale requires मुक्त function to be implemented */
अटल व्योम rs_मुक्त(व्योम *mvm_rate)
अणु
	वापस;
पूर्ण

अटल व्योम rs_मुक्त_sta(व्योम *mvm_r, काष्ठा ieee80211_sta *sta, व्योम *mvm_sta)
अणु
	काष्ठा iwl_op_mode *op_mode __maybe_unused = mvm_r;
	काष्ठा iwl_mvm *mvm __maybe_unused = IWL_OP_MODE_GET_MVM(op_mode);

	IWL_DEBUG_RATE(mvm, "enter\n");
	IWL_DEBUG_RATE(mvm, "leave\n");
पूर्ण

पूर्णांक rs_pretty_prपूर्णांक_rate(अक्षर *buf, पूर्णांक bufsz, स्थिर u32 rate)
अणु

	अक्षर *type, *bw;
	u8 mcs = 0, nss = 0;
	u8 ant = (rate & RATE_MCS_ANT_ABC_MSK) >> RATE_MCS_ANT_POS;

	अगर (!(rate & RATE_MCS_HT_MSK) &&
	    !(rate & RATE_MCS_VHT_MSK) &&
	    !(rate & RATE_MCS_HE_MSK)) अणु
		पूर्णांक index = iwl_hwrate_to_plcp_idx(rate);

		वापस scnम_लिखो(buf, bufsz, "Legacy | ANT: %s Rate: %s Mbps",
				 rs_pretty_ant(ant),
				 index == IWL_RATE_INVALID ? "BAD" :
				 iwl_rate_mcs[index].mbps);
	पूर्ण

	अगर (rate & RATE_MCS_VHT_MSK) अणु
		type = "VHT";
		mcs = rate & RATE_VHT_MCS_RATE_CODE_MSK;
		nss = ((rate & RATE_VHT_MCS_NSS_MSK)
		       >> RATE_VHT_MCS_NSS_POS) + 1;
	पूर्ण अन्यथा अगर (rate & RATE_MCS_HT_MSK) अणु
		type = "HT";
		mcs = rate & RATE_HT_MCS_INDEX_MSK;
		nss = ((rate & RATE_HT_MCS_NSS_MSK)
		       >> RATE_HT_MCS_NSS_POS) + 1;
	पूर्ण अन्यथा अगर (rate & RATE_MCS_HE_MSK) अणु
		type = "HE";
		mcs = rate & RATE_VHT_MCS_RATE_CODE_MSK;
		nss = ((rate & RATE_VHT_MCS_NSS_MSK)
		       >> RATE_VHT_MCS_NSS_POS) + 1;
	पूर्ण अन्यथा अणु
		type = "Unknown"; /* shouldn't happen */
	पूर्ण

	चयन (rate & RATE_MCS_CHAN_WIDTH_MSK) अणु
	हाल RATE_MCS_CHAN_WIDTH_20:
		bw = "20Mhz";
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_40:
		bw = "40Mhz";
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_80:
		bw = "80Mhz";
		अवरोध;
	हाल RATE_MCS_CHAN_WIDTH_160:
		bw = "160Mhz";
		अवरोध;
	शेष:
		bw = "BAD BW";
	पूर्ण

	वापस scnम_लिखो(buf, bufsz,
			 "0x%x: %s | ANT: %s BW: %s MCS: %d NSS: %d %s%s%s%s%s",
			 rate, type, rs_pretty_ant(ant), bw, mcs, nss,
			 (rate & RATE_MCS_SGI_MSK) ? "SGI " : "NGI ",
			 (rate & RATE_MCS_STBC_MSK) ? "STBC " : "",
			 (rate & RATE_MCS_LDPC_MSK) ? "LDPC " : "",
			 (rate & RATE_HE_DUAL_CARRIER_MODE_MSK) ? "DCM " : "",
			 (rate & RATE_MCS_BF_MSK) ? "BF " : "");
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
/*
 * Program the device to use fixed rate क्रम frame transmit
 * This is क्रम debugging/testing only
 * once the device start use fixed rate, we need to reload the module
 * to being back the normal operation.
 */
अटल व्योम rs_program_fix_rate(काष्ठा iwl_mvm *mvm,
				काष्ठा iwl_lq_sta *lq_sta)
अणु
	lq_sta->active_legacy_rate = 0x0FFF;	/* 1 - 54 MBits, includes CCK */
	lq_sta->active_siso_rate   = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */
	lq_sta->active_mimo2_rate  = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */

	IWL_DEBUG_RATE(mvm, "sta_id %d rate 0x%X\n",
		       lq_sta->lq.sta_id, lq_sta->pers.dbg_fixed_rate);

	अगर (lq_sta->pers.dbg_fixed_rate) अणु
		rs_fill_lq_cmd(mvm, शून्य, lq_sta, शून्य);
		iwl_mvm_send_lq_cmd(lq_sta->pers.drv, &lq_sta->lq);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार rs_sta_dbgfs_scale_table_ग_लिखो(काष्ठा file *file,
			स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	काष्ठा iwl_mvm *mvm;
	अक्षर buf[64];
	माप_प्रकार buf_size;
	u32 parsed_rate;

	mvm = lq_sta->pers.drv;
	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	अगर (माला_पूछो(buf, "%x", &parsed_rate) == 1)
		lq_sta->pers.dbg_fixed_rate = parsed_rate;
	अन्यथा
		lq_sta->pers.dbg_fixed_rate = 0;

	rs_program_fix_rate(mvm, lq_sta);

	वापस count;
पूर्ण

अटल sमाप_प्रकार rs_sta_dbgfs_scale_table_पढ़ो(काष्ठा file *file,
			अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buff;
	पूर्णांक desc = 0;
	पूर्णांक i = 0;
	sमाप_प्रकार ret;
	अटल स्थिर माप_प्रकार bufsz = 2048;

	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	काष्ठा iwl_mvm_sta *mvmsta =
		container_of(lq_sta, काष्ठा iwl_mvm_sta, lq_sta.rs_drv);
	काष्ठा iwl_mvm *mvm;
	काष्ठा iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	काष्ठा rs_rate *rate = &tbl->rate;
	u32 ss_params;

	mvm = lq_sta->pers.drv;
	buff = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	desc += scnम_लिखो(buff + desc, bufsz - desc,
			  "sta_id %d\n", lq_sta->lq.sta_id);
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			  "failed=%d success=%d rate=0%lX\n",
			  lq_sta->total_failed, lq_sta->total_success,
			  lq_sta->active_legacy_rate);
	desc += scnम_लिखो(buff + desc, bufsz - desc, "fixed rate 0x%X\n",
			  lq_sta->pers.dbg_fixed_rate);
	desc += scnम_लिखो(buff + desc, bufsz - desc, "valid_tx_ant %s%s%s\n",
	    (iwl_mvm_get_valid_tx_ant(mvm) & ANT_A) ? "ANT_A," : "",
	    (iwl_mvm_get_valid_tx_ant(mvm) & ANT_B) ? "ANT_B," : "",
	    (iwl_mvm_get_valid_tx_ant(mvm) & ANT_C) ? "ANT_C" : "");
	desc += scnम_लिखो(buff + desc, bufsz - desc, "lq type %s\n",
			  (is_legacy(rate)) ? "legacy" :
			  is_vht(rate) ? "VHT" : "HT");
	अगर (!is_legacy(rate)) अणु
		desc += scnम_लिखो(buff + desc, bufsz - desc, " %s",
		   (is_siso(rate)) ? "SISO" : "MIMO2");
		desc += scnम_लिखो(buff + desc, bufsz - desc, " %s",
				(is_ht20(rate)) ? "20MHz" :
				(is_ht40(rate)) ? "40MHz" :
				(is_ht80(rate)) ? "80MHz" :
				(is_ht160(rate)) ? "160MHz" : "BAD BW");
		desc += scnम_लिखो(buff + desc, bufsz - desc, " %s %s %s %s\n",
				(rate->sgi) ? "SGI" : "NGI",
				(rate->ldpc) ? "LDPC" : "BCC",
				(lq_sta->is_agg) ? "AGG on" : "",
				(mvmsta->amsdu_enabled) ? "AMSDU on" : "");
	पूर्ण
	desc += scnम_लिखो(buff + desc, bufsz - desc, "last tx rate=0x%X\n",
			lq_sta->last_rate_n_flags);
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			"general: flags=0x%X mimo-d=%d s-ant=0x%x d-ant=0x%x\n",
			lq_sta->lq.flags,
			lq_sta->lq.mimo_delim,
			lq_sta->lq.single_stream_ant_msk,
			lq_sta->lq.dual_stream_ant_msk);

	desc += scnम_लिखो(buff + desc, bufsz - desc,
			"agg: time_limit=%d dist_start_th=%d frame_cnt_limit=%d\n",
			le16_to_cpu(lq_sta->lq.agg_समय_limit),
			lq_sta->lq.agg_disable_start_th,
			lq_sta->lq.agg_frame_cnt_limit);

	desc += scnम_लिखो(buff + desc, bufsz - desc, "reduced tpc=%d\n",
			  lq_sta->lq.reduced_tpc);
	ss_params = le32_to_cpu(lq_sta->lq.ss_params);
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			"single stream params: %s%s%s%s\n",
			(ss_params & LQ_SS_PARAMS_VALID) ?
			"VALID" : "INVALID",
			(ss_params & LQ_SS_BFER_ALLOWED) ?
			", BFER" : "",
			(ss_params & LQ_SS_STBC_1SS_ALLOWED) ?
			", STBC" : "",
			(ss_params & LQ_SS_FORCE) ?
			", FORCE" : "");
	desc += scnम_लिखो(buff + desc, bufsz - desc,
			"Start idx [0]=0x%x [1]=0x%x [2]=0x%x [3]=0x%x\n",
			lq_sta->lq.initial_rate_index[0],
			lq_sta->lq.initial_rate_index[1],
			lq_sta->lq.initial_rate_index[2],
			lq_sta->lq.initial_rate_index[3]);

	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++) अणु
		u32 r = le32_to_cpu(lq_sta->lq.rs_table[i]);

		desc += scnम_लिखो(buff + desc, bufsz - desc,
				  " rate[%d] 0x%X ", i, r);
		desc += rs_pretty_prपूर्णांक_rate(buff + desc, bufsz - desc, r);
		अगर (desc < bufsz - 1)
			buff[desc++] = '\n';
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, desc);
	kमुक्त(buff);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations rs_sta_dbgfs_scale_table_ops = अणु
	.ग_लिखो = rs_sta_dbgfs_scale_table_ग_लिखो,
	.पढ़ो = rs_sta_dbgfs_scale_table_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;
अटल sमाप_प्रकार rs_sta_dbgfs_stats_table_पढ़ो(काष्ठा file *file,
			अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buff;
	पूर्णांक desc = 0;
	पूर्णांक i, j;
	sमाप_प्रकार ret;
	काष्ठा iwl_scale_tbl_info *tbl;
	काष्ठा rs_rate *rate;
	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;

	buff = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	क्रम (i = 0; i < LQ_SIZE; i++) अणु
		tbl = &(lq_sta->lq_info[i]);
		rate = &tbl->rate;
		desc += प्र_लिखो(buff+desc,
				"%s type=%d SGI=%d BW=%s DUP=0\n"
				"index=%d\n",
				lq_sta->active_tbl == i ? "*" : "x",
				rate->type,
				rate->sgi,
				is_ht20(rate) ? "20MHz" :
				is_ht40(rate) ? "40MHz" :
				is_ht80(rate) ? "80MHz" :
				is_ht160(rate) ? "160MHz" : "ERR",
				rate->index);
		क्रम (j = 0; j < IWL_RATE_COUNT; j++) अणु
			desc += प्र_लिखो(buff+desc,
				"counter=%d success=%d %%=%d\n",
				tbl->win[j].counter,
				tbl->win[j].success_counter,
				tbl->win[j].success_ratio);
		पूर्ण
	पूर्ण
	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, desc);
	kमुक्त(buff);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations rs_sta_dbgfs_stats_table_ops = अणु
	.पढ़ो = rs_sta_dbgfs_stats_table_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार rs_sta_dbgfs_drv_tx_stats_पढ़ो(काष्ठा file *file,
					      अक्षर __user *user_buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	अटल स्थिर अक्षर * स्थिर column_name[] = अणु
		[RS_COLUMN_LEGACY_ANT_A] = "LEGACY_ANT_A",
		[RS_COLUMN_LEGACY_ANT_B] = "LEGACY_ANT_B",
		[RS_COLUMN_SISO_ANT_A] = "SISO_ANT_A",
		[RS_COLUMN_SISO_ANT_B] = "SISO_ANT_B",
		[RS_COLUMN_SISO_ANT_A_SGI] = "SISO_ANT_A_SGI",
		[RS_COLUMN_SISO_ANT_B_SGI] = "SISO_ANT_B_SGI",
		[RS_COLUMN_MIMO2] = "MIMO2",
		[RS_COLUMN_MIMO2_SGI] = "MIMO2_SGI",
	पूर्ण;

	अटल स्थिर अक्षर * स्थिर rate_name[] = अणु
		[IWL_RATE_1M_INDEX] = "1M",
		[IWL_RATE_2M_INDEX] = "2M",
		[IWL_RATE_5M_INDEX] = "5.5M",
		[IWL_RATE_11M_INDEX] = "11M",
		[IWL_RATE_6M_INDEX] = "6M|MCS0",
		[IWL_RATE_9M_INDEX] = "9M",
		[IWL_RATE_12M_INDEX] = "12M|MCS1",
		[IWL_RATE_18M_INDEX] = "18M|MCS2",
		[IWL_RATE_24M_INDEX] = "24M|MCS3",
		[IWL_RATE_36M_INDEX] = "36M|MCS4",
		[IWL_RATE_48M_INDEX] = "48M|MCS5",
		[IWL_RATE_54M_INDEX] = "54M|MCS6",
		[IWL_RATE_MCS_7_INDEX] = "MCS7",
		[IWL_RATE_MCS_8_INDEX] = "MCS8",
		[IWL_RATE_MCS_9_INDEX] = "MCS9",
		[IWL_RATE_MCS_10_INDEX] = "MCS10",
		[IWL_RATE_MCS_11_INDEX] = "MCS11",
	पूर्ण;

	अक्षर *buff, *pos, *endpos;
	पूर्णांक col, rate;
	sमाप_प्रकार ret;
	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	काष्ठा rs_rate_stats *stats;
	अटल स्थिर माप_प्रकार bufsz = 1024;

	buff = kदो_स्मृति(bufsz, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	pos = buff;
	endpos = pos + bufsz;

	pos += scnम_लिखो(pos, endpos - pos, "COLUMN,");
	क्रम (rate = 0; rate < IWL_RATE_COUNT; rate++)
		pos += scnम_लिखो(pos, endpos - pos, "%s,", rate_name[rate]);
	pos += scnम_लिखो(pos, endpos - pos, "\n");

	क्रम (col = 0; col < RS_COLUMN_COUNT; col++) अणु
		pos += scnम_लिखो(pos, endpos - pos,
				 "%s,", column_name[col]);

		क्रम (rate = 0; rate < IWL_RATE_COUNT; rate++) अणु
			stats = &(lq_sta->pers.tx_stats[col][rate]);
			pos += scnम_लिखो(pos, endpos - pos,
					 "%llu/%llu,",
					 stats->success,
					 stats->total);
		पूर्ण
		pos += scnम_लिखो(pos, endpos - pos, "\n");
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, pos - buff);
	kमुक्त(buff);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार rs_sta_dbgfs_drv_tx_stats_ग_लिखो(काष्ठा file *file,
					       स्थिर अक्षर __user *user_buf,
					       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	स_रखो(lq_sta->pers.tx_stats, 0, माप(lq_sta->pers.tx_stats));

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations rs_sta_dbgfs_drv_tx_stats_ops = अणु
	.पढ़ो = rs_sta_dbgfs_drv_tx_stats_पढ़ो,
	.ग_लिखो = rs_sta_dbgfs_drv_tx_stats_ग_लिखो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल sमाप_प्रकार iwl_dbgfs_ss_क्रमce_पढ़ो(काष्ठा file *file,
				       अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	अक्षर buf[12];
	पूर्णांक bufsz = माप(buf);
	पूर्णांक pos = 0;
	अटल स्थिर अक्षर * स्थिर ss_क्रमce_name[] = अणु
		[RS_SS_FORCE_NONE] = "none",
		[RS_SS_FORCE_STBC] = "stbc",
		[RS_SS_FORCE_BFER] = "bfer",
		[RS_SS_FORCE_SISO] = "siso",
	पूर्ण;

	pos += scnम_लिखो(buf+pos, bufsz-pos, "%s\n",
			 ss_क्रमce_name[lq_sta->pers.ss_क्रमce]);
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, pos);
पूर्ण

अटल sमाप_प्रकार iwl_dbgfs_ss_क्रमce_ग_लिखो(काष्ठा iwl_lq_sta *lq_sta, अक्षर *buf,
					माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_mvm *mvm = lq_sta->pers.drv;
	पूर्णांक ret = 0;

	अगर (!म_भेदन("none", buf, 4)) अणु
		lq_sta->pers.ss_क्रमce = RS_SS_FORCE_NONE;
	पूर्ण अन्यथा अगर (!म_भेदन("siso", buf, 4)) अणु
		lq_sta->pers.ss_क्रमce = RS_SS_FORCE_SISO;
	पूर्ण अन्यथा अगर (!म_भेदन("stbc", buf, 4)) अणु
		अगर (lq_sta->stbc_capable) अणु
			lq_sta->pers.ss_क्रमce = RS_SS_FORCE_STBC;
		पूर्ण अन्यथा अणु
			IWL_ERR(mvm,
				"can't force STBC. peer doesn't support\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (!म_भेदन("bfer", buf, 4)) अणु
		अगर (lq_sta->bfer_capable) अणु
			lq_sta->pers.ss_क्रमce = RS_SS_FORCE_BFER;
		पूर्ण अन्यथा अणु
			IWL_ERR(mvm,
				"can't force BFER. peer doesn't support\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		IWL_ERR(mvm, "valid values none|siso|stbc|bfer\n");
		ret = -EINVAL;
	पूर्ण
	वापस ret ?: count;
पूर्ण

#घोषणा MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz) \
	_MVM_DEBUGFS_READ_WRITE_खाता_OPS(name, bufsz, काष्ठा iwl_lq_sta)
#घोषणा MVM_DEBUGFS_ADD_खाता_RS(name, parent, mode) करो अणु		\
		debugfs_create_file(#name, mode, parent, lq_sta,	\
				    &iwl_dbgfs_##name##_ops);		\
	पूर्ण जबतक (0)

MVM_DEBUGFS_READ_WRITE_खाता_OPS(ss_क्रमce, 32);

अटल व्योम rs_drv_add_sta_debugfs(व्योम *mvm, व्योम *priv_sta,
				   काष्ठा dentry *dir)
अणु
	काष्ठा iwl_lq_sta *lq_sta = priv_sta;
	काष्ठा iwl_mvm_sta *mvmsta;

	mvmsta = container_of(lq_sta, काष्ठा iwl_mvm_sta, lq_sta.rs_drv);

	अगर (!mvmsta->vअगर)
		वापस;

	debugfs_create_file("rate_scale_table", 0600, dir,
			    lq_sta, &rs_sta_dbgfs_scale_table_ops);
	debugfs_create_file("rate_stats_table", 0400, dir,
			    lq_sta, &rs_sta_dbgfs_stats_table_ops);
	debugfs_create_file("drv_tx_stats", 0600, dir,
			    lq_sta, &rs_sta_dbgfs_drv_tx_stats_ops);
	debugfs_create_u8("tx_agg_tid_enable", 0600, dir,
			  &lq_sta->tx_agg_tid_en);
	debugfs_create_u8("reduced_tpc", 0600, dir,
			  &lq_sta->pers.dbg_fixed_txp_reduction);

	MVM_DEBUGFS_ADD_खाता_RS(ss_क्रमce, dir, 0600);
पूर्ण
#पूर्ण_अगर

/*
 * Initialization of rate scaling inक्रमmation is करोne by driver after
 * the station is added. Since mac80211 calls this function beक्रमe a
 * station is added we ignore it.
 */
अटल व्योम rs_rate_init_ops(व्योम *mvm_r,
			     काष्ठा ieee80211_supported_band *sband,
			     काष्ठा cfg80211_chan_def *chandef,
			     काष्ठा ieee80211_sta *sta, व्योम *mvm_sta)
अणु
पूर्ण

/* ops क्रम rate scaling implemented in the driver */
अटल स्थिर काष्ठा rate_control_ops rs_mvm_ops_drv = अणु
	.name = RS_NAME,
	.tx_status = rs_drv_mac80211_tx_status,
	.get_rate = rs_drv_get_rate,
	.rate_init = rs_rate_init_ops,
	.alloc = rs_alloc,
	.मुक्त = rs_मुक्त,
	.alloc_sta = rs_drv_alloc_sta,
	.मुक्त_sta = rs_मुक्त_sta,
	.rate_update = rs_drv_rate_update,
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	.add_sta_debugfs = rs_drv_add_sta_debugfs,
#पूर्ण_अगर
	.capa = RATE_CTRL_CAPA_VHT_EXT_NSS_BW,
पूर्ण;

व्योम iwl_mvm_rs_rate_init(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			  क्रमागत nl80211_band band, bool update)
अणु
	अगर (iwl_mvm_has_tlc_offload(mvm)) अणु
		rs_fw_rate_init(mvm, sta, band, update);
	पूर्ण अन्यथा अणु
		काष्ठा iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);

		spin_lock(&mvmsta->lq_sta.rs_drv.pers.lock);
		rs_drv_rate_init(mvm, sta, band);
		spin_unlock(&mvmsta->lq_sta.rs_drv.pers.lock);
	पूर्ण
पूर्ण

पूर्णांक iwl_mvm_rate_control_रेजिस्टर(व्योम)
अणु
	वापस ieee80211_rate_control_रेजिस्टर(&rs_mvm_ops_drv);
पूर्ण

व्योम iwl_mvm_rate_control_unरेजिस्टर(व्योम)
अणु
	ieee80211_rate_control_unरेजिस्टर(&rs_mvm_ops_drv);
पूर्ण

अटल पूर्णांक rs_drv_tx_protection(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
				bool enable)
अणु
	काष्ठा iwl_lq_cmd *lq = &mvmsta->lq_sta.rs_drv.lq;

	lockdep_निश्चित_held(&mvm->mutex);

	अगर (enable) अणु
		अगर (mvmsta->tx_protection == 0)
			lq->flags |= LQ_FLAG_USE_RTS_MSK;
		mvmsta->tx_protection++;
	पूर्ण अन्यथा अणु
		mvmsta->tx_protection--;
		अगर (mvmsta->tx_protection == 0)
			lq->flags &= ~LQ_FLAG_USE_RTS_MSK;
	पूर्ण

	वापस iwl_mvm_send_lq_cmd(mvm, lq);
पूर्ण

/**
 * iwl_mvm_tx_protection - ask FW to enable RTS/CTS protection
 * @mvm: The mvm component
 * @mvmsta: The station
 * @enable: Enable Tx protection?
 */
पूर्णांक iwl_mvm_tx_protection(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
			  bool enable)
अणु
	अगर (iwl_mvm_has_tlc_offload(mvm))
		वापस rs_fw_tx_protection(mvm, mvmsta, enable);
	अन्यथा
		वापस rs_drv_tx_protection(mvm, mvmsta, enable);
पूर्ण
