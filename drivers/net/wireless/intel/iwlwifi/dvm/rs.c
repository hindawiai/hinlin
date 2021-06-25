<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 *
 * Copyright(c) 2005 - 2014 Intel Corporation. All rights reserved.
 * Copyright (C) 2019 - 2020 Intel Corporation
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

#समावेश "dev.h"
#समावेश "agn.h"

#घोषणा RS_NAME "iwl-agn-rs"

#घोषणा NUM_TRY_BEFORE_ANT_TOGGLE 1
#घोषणा IWL_NUMBER_TRY      1
#घोषणा IWL_HT_NUMBER_TRY   3

#घोषणा IWL_RATE_MAX_WINDOW		62	/* # tx in history winकरोw */
#घोषणा IWL_RATE_MIN_FAILURE_TH		6	/* min failures to calc tpt */
#घोषणा IWL_RATE_MIN_SUCCESS_TH		8	/* min successes to calc tpt */

/* max allowed rate miss beक्रमe sync LQ cmd */
#घोषणा IWL_MISSED_RATE_MAX		15
/* max समय to accum history 2 seconds */
#घोषणा IWL_RATE_SCALE_FLUSH_INTVL   (3*HZ)

अटल u8 rs_ht_to_legacy[] = अणु
	IWL_RATE_6M_INDEX, IWL_RATE_6M_INDEX,
	IWL_RATE_6M_INDEX, IWL_RATE_6M_INDEX,
	IWL_RATE_6M_INDEX,
	IWL_RATE_6M_INDEX, IWL_RATE_9M_INDEX,
	IWL_RATE_12M_INDEX, IWL_RATE_18M_INDEX,
	IWL_RATE_24M_INDEX, IWL_RATE_36M_INDEX,
	IWL_RATE_48M_INDEX, IWL_RATE_54M_INDEX
पूर्ण;

अटल स्थिर u8 ant_toggle_lookup[] = अणु
	/*ANT_NONE -> */ ANT_NONE,
	/*ANT_A    -> */ ANT_B,
	/*ANT_B    -> */ ANT_C,
	/*ANT_AB   -> */ ANT_BC,
	/*ANT_C    -> */ ANT_A,
	/*ANT_AC   -> */ ANT_AB,
	/*ANT_BC   -> */ ANT_AC,
	/*ANT_ABC  -> */ ANT_ABC,
पूर्ण;

#घोषणा IWL_DECLARE_RATE_INFO(r, s, ip, in, rp, rn, pp, np)    \
	[IWL_RATE_##r##M_INDEX] = अणु IWL_RATE_##r##M_PLCP,      \
				    IWL_RATE_SISO_##s##M_PLCP, \
				    IWL_RATE_MIMO2_##s##M_PLCP,\
				    IWL_RATE_MIMO3_##s##M_PLCP,\
				    IWL_RATE_##r##M_IEEE,      \
				    IWL_RATE_##ip##M_INDEX,    \
				    IWL_RATE_##in##M_INDEX,    \
				    IWL_RATE_##rp##M_INDEX,    \
				    IWL_RATE_##rn##M_INDEX,    \
				    IWL_RATE_##pp##M_INDEX,    \
				    IWL_RATE_##np##M_INDEX पूर्ण

/*
 * Parameter order:
 *   rate, ht rate, prev rate, next rate, prev tgg rate, next tgg rate
 *
 * If there isn't a valid next or previous rate then INV is used which
 * maps to IWL_RATE_INVALID
 *
 */
स्थिर काष्ठा iwl_rate_info iwl_rates[IWL_RATE_COUNT] = अणु
	IWL_DECLARE_RATE_INFO(1, INV, INV, 2, INV, 2, INV, 2),    /*  1mbps */
	IWL_DECLARE_RATE_INFO(2, INV, 1, 5, 1, 5, 1, 5),          /*  2mbps */
	IWL_DECLARE_RATE_INFO(5, INV, 2, 6, 2, 11, 2, 11),        /*5.5mbps */
	IWL_DECLARE_RATE_INFO(11, INV, 9, 12, 9, 12, 5, 18),      /* 11mbps */
	IWL_DECLARE_RATE_INFO(6, 6, 5, 9, 5, 11, 5, 11),        /*  6mbps */
	IWL_DECLARE_RATE_INFO(9, 6, 6, 11, 6, 11, 5, 11),       /*  9mbps */
	IWL_DECLARE_RATE_INFO(12, 12, 11, 18, 11, 18, 11, 18),   /* 12mbps */
	IWL_DECLARE_RATE_INFO(18, 18, 12, 24, 12, 24, 11, 24),   /* 18mbps */
	IWL_DECLARE_RATE_INFO(24, 24, 18, 36, 18, 36, 18, 36),   /* 24mbps */
	IWL_DECLARE_RATE_INFO(36, 36, 24, 48, 24, 48, 24, 48),   /* 36mbps */
	IWL_DECLARE_RATE_INFO(48, 48, 36, 54, 36, 54, 36, 54),   /* 48mbps */
	IWL_DECLARE_RATE_INFO(54, 54, 48, INV, 48, INV, 48, INV),/* 54mbps */
	IWL_DECLARE_RATE_INFO(60, 60, 48, INV, 48, INV, 48, INV),/* 60mbps */
	/* FIXME:RS:          ^^    should be INV (legacy) */
पूर्ण;

अटल अंतरभूत u8 rs_extract_rate(u32 rate_n_flags)
अणु
	वापस (u8)(rate_n_flags & RATE_MCS_RATE_MSK);
पूर्ण

अटल पूर्णांक iwl_hwrate_to_plcp_idx(u32 rate_n_flags)
अणु
	पूर्णांक idx = 0;

	/* HT rate क्रमmat */
	अगर (rate_n_flags & RATE_MCS_HT_MSK) अणु
		idx = rs_extract_rate(rate_n_flags);

		अगर (idx >= IWL_RATE_MIMO3_6M_PLCP)
			idx = idx - IWL_RATE_MIMO3_6M_PLCP;
		अन्यथा अगर (idx >= IWL_RATE_MIMO2_6M_PLCP)
			idx = idx - IWL_RATE_MIMO2_6M_PLCP;

		idx += IWL_FIRST_OFDM_RATE;
		/* skip 9M not supported in ht*/
		अगर (idx >= IWL_RATE_9M_INDEX)
			idx += 1;
		अगर ((idx >= IWL_FIRST_OFDM_RATE) && (idx <= IWL_LAST_OFDM_RATE))
			वापस idx;

	/* legacy rate क्रमmat, search क्रम match in table */
	पूर्ण अन्यथा अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(iwl_rates); idx++)
			अगर (iwl_rates[idx].plcp ==
					rs_extract_rate(rate_n_flags))
				वापस idx;
	पूर्ण

	वापस -1;
पूर्ण

अटल व्योम rs_rate_scale_perक्रमm(काष्ठा iwl_priv *priv,
				   काष्ठा sk_buff *skb,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा iwl_lq_sta *lq_sta);
अटल व्योम rs_fill_link_cmd(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_lq_sta *lq_sta, u32 rate_n_flags);
अटल व्योम rs_stay_in_table(काष्ठा iwl_lq_sta *lq_sta, bool क्रमce_search);


#अगर_घोषित CONFIG_MAC80211_DEBUGFS
अटल व्योम rs_dbgfs_set_mcs(काष्ठा iwl_lq_sta *lq_sta,
			     u32 *rate_n_flags, पूर्णांक index);
#अन्यथा
अटल व्योम rs_dbgfs_set_mcs(काष्ठा iwl_lq_sta *lq_sta,
			     u32 *rate_n_flags, पूर्णांक index)
अणुपूर्ण
#पूर्ण_अगर

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
	7, 13, 35, 58, 40, 57, 72, 98, 121, 154, 177, 186, 0
पूर्ण;

अटल स्थिर u16 expected_tpt_siso20MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 42, 0,  76, 102, 124, 159, 183, 193, 202पूर्ण, /* Norm */
	अणु0, 0, 0, 0, 46, 0,  82, 110, 132, 168, 192, 202, 210पूर्ण, /* SGI */
	अणु0, 0, 0, 0, 47, 0,  91, 133, 171, 242, 305, 334, 362पूर्ण, /* AGG */
	अणु0, 0, 0, 0, 52, 0, 101, 145, 187, 264, 330, 361, 390पूर्ण, /* AGG+SGI */
पूर्ण;

अटल स्थिर u16 expected_tpt_siso40MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0,  77, 0, 127, 160, 184, 220, 242, 250, 257पूर्ण, /* Norm */
	अणु0, 0, 0, 0,  83, 0, 135, 169, 193, 229, 250, 257, 264पूर्ण, /* SGI */
	अणु0, 0, 0, 0,  94, 0, 177, 249, 313, 423, 512, 550, 586पूर्ण, /* AGG */
	अणु0, 0, 0, 0, 104, 0, 193, 270, 338, 454, 545, 584, 620पूर्ण, /* AGG+SGI */
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo2_20MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0,  74, 0, 123, 155, 179, 214, 236, 244, 251पूर्ण, /* Norm */
	अणु0, 0, 0, 0,  81, 0, 131, 164, 188, 223, 243, 251, 257पूर्ण, /* SGI */
	अणु0, 0, 0, 0,  89, 0, 167, 235, 296, 402, 488, 526, 560पूर्ण, /* AGG */
	अणु0, 0, 0, 0,  97, 0, 182, 255, 320, 431, 520, 558, 593पूर्ण, /* AGG+SGI*/
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo2_40MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 123, 0, 182, 214, 235, 264, 279, 285, 289पूर्ण, /* Norm */
	अणु0, 0, 0, 0, 131, 0, 191, 222, 242, 270, 284, 289, 293पूर्ण, /* SGI */
	अणु0, 0, 0, 0, 171, 0, 305, 410, 496, 634, 731, 771, 805पूर्ण, /* AGG */
	अणु0, 0, 0, 0, 186, 0, 329, 439, 527, 667, 764, 803, 838पूर्ण, /* AGG+SGI */
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo3_20MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0,  99, 0, 153, 186, 208, 239, 256, 263, 268पूर्ण, /* Norm */
	अणु0, 0, 0, 0, 106, 0, 162, 194, 215, 246, 262, 268, 273पूर्ण, /* SGI */
	अणु0, 0, 0, 0, 134, 0, 249, 346, 431, 574, 685, 732, 775पूर्ण, /* AGG */
	अणु0, 0, 0, 0, 148, 0, 272, 376, 465, 614, 727, 775, 818पूर्ण, /* AGG+SGI */
पूर्ण;

अटल स्थिर u16 expected_tpt_mimo3_40MHz[4][IWL_RATE_COUNT] = अणु
	अणु0, 0, 0, 0, 152, 0, 211, 239, 255, 279,  290,  294,  297पूर्ण, /* Norm */
	अणु0, 0, 0, 0, 160, 0, 219, 245, 261, 284,  294,  297,  300पूर्ण, /* SGI */
	अणु0, 0, 0, 0, 254, 0, 443, 584, 695, 868,  984, 1030, 1070पूर्ण, /* AGG */
	अणु0, 0, 0, 0, 277, 0, 478, 624, 737, 911, 1026, 1070, 1109पूर्ण, /* AGG+SGI */
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

अटल व्योम rs_rate_scale_clear_winकरोw(काष्ठा iwl_rate_scale_data *winकरोw)
अणु
	winकरोw->data = 0;
	winकरोw->success_counter = 0;
	winकरोw->success_ratio = IWL_INVALID_VALUE;
	winकरोw->counter = 0;
	winकरोw->average_tpt = IWL_INVALID_VALUE;
	winकरोw->stamp = 0;
पूर्ण

अटल अंतरभूत u8 rs_is_valid_ant(u8 valid_antenna, u8 ant_type)
अणु
	वापस (ant_type & valid_antenna) == ant_type;
पूर्ण

/*
 *	हटाओs the old data from the statistics. All data that is older than
 *	TID_MAX_TIME_DIFF, will be deleted.
 */
अटल व्योम rs_tl_rm_old_stats(काष्ठा iwl_traffic_load *tl, u32 curr_समय)
अणु
	/* The oldest age we want to keep */
	u32 oldest_समय = curr_समय - TID_MAX_TIME_DIFF;

	जबतक (tl->queue_count &&
	       (tl->समय_stamp < oldest_समय)) अणु
		tl->total -= tl->packet_count[tl->head];
		tl->packet_count[tl->head] = 0;
		tl->समय_stamp += TID_QUEUE_CELL_SPACING;
		tl->queue_count--;
		tl->head++;
		अगर (tl->head >= TID_QUEUE_MAX_SIZE)
			tl->head = 0;
	पूर्ण
पूर्ण

/*
 *	increment traffic load value क्रम tid and also हटाओ
 *	any old values अगर passed the certain समय period
 */
अटल u8 rs_tl_add_packet(काष्ठा iwl_lq_sta *lq_data,
			   काष्ठा ieee80211_hdr *hdr)
अणु
	u32 curr_समय = jअगरfies_to_msecs(jअगरfies);
	u32 समय_dअगरf;
	s32 index;
	काष्ठा iwl_traffic_load *tl = शून्य;
	u8 tid;

	अगर (ieee80211_is_data_qos(hdr->frame_control)) अणु
		u8 *qc = ieee80211_get_qos_ctl(hdr);
		tid = qc[0] & 0xf;
	पूर्ण अन्यथा
		वापस IWL_MAX_TID_COUNT;

	अगर (unlikely(tid >= IWL_MAX_TID_COUNT))
		वापस IWL_MAX_TID_COUNT;

	tl = &lq_data->load[tid];

	curr_समय -= curr_समय % TID_ROUND_VALUE;

	/* Happens only क्रम the first packet. Initialize the data */
	अगर (!(tl->queue_count)) अणु
		tl->total = 1;
		tl->समय_stamp = curr_समय;
		tl->queue_count = 1;
		tl->head = 0;
		tl->packet_count[0] = 1;
		वापस IWL_MAX_TID_COUNT;
	पूर्ण

	समय_dअगरf = TIME_WRAP_AROUND(tl->समय_stamp, curr_समय);
	index = समय_dअगरf / TID_QUEUE_CELL_SPACING;

	/* The history is too दीर्घ: हटाओ data that is older than */
	/* TID_MAX_TIME_DIFF */
	अगर (index >= TID_QUEUE_MAX_SIZE)
		rs_tl_rm_old_stats(tl, curr_समय);

	index = (tl->head + index) % TID_QUEUE_MAX_SIZE;
	tl->packet_count[index] = tl->packet_count[index] + 1;
	tl->total = tl->total + 1;

	अगर ((index + 1) > tl->queue_count)
		tl->queue_count = index + 1;

	वापस tid;
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
/*
 * Program the device to use fixed rate क्रम frame transmit
 * This is क्रम debugging/testing only
 * once the device start use fixed rate, we need to reload the module
 * to being back the normal operation.
 */
अटल व्योम rs_program_fix_rate(काष्ठा iwl_priv *priv,
				काष्ठा iwl_lq_sta *lq_sta)
अणु
	काष्ठा iwl_station_priv *sta_priv =
		container_of(lq_sta, काष्ठा iwl_station_priv, lq_sta);
	काष्ठा iwl_rxon_context *ctx = sta_priv->ctx;

	lq_sta->active_legacy_rate = 0x0FFF;	/* 1 - 54 MBits, includes CCK */
	lq_sta->active_siso_rate   = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */
	lq_sta->active_mimo2_rate  = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */
	lq_sta->active_mimo3_rate  = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */

	IWL_DEBUG_RATE(priv, "sta_id %d rate 0x%X\n",
		lq_sta->lq.sta_id, lq_sta->dbg_fixed_rate);

	अगर (lq_sta->dbg_fixed_rate) अणु
		rs_fill_link_cmd(शून्य, lq_sta, lq_sta->dbg_fixed_rate);
		iwl_send_lq_cmd(lq_sta->drv, ctx, &lq_sta->lq, CMD_ASYNC,
				false);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
	get the traffic load value क्रम tid
*/
अटल व्योम rs_tl_get_load(काष्ठा iwl_lq_sta *lq_data, u8 tid)
अणु
	u32 curr_समय = jअगरfies_to_msecs(jअगरfies);
	u32 समय_dअगरf;
	s32 index;
	काष्ठा iwl_traffic_load *tl = शून्य;

	अगर (tid >= IWL_MAX_TID_COUNT)
		वापस;

	tl = &(lq_data->load[tid]);

	curr_समय -= curr_समय % TID_ROUND_VALUE;

	अगर (!(tl->queue_count))
		वापस;

	समय_dअगरf = TIME_WRAP_AROUND(tl->समय_stamp, curr_समय);
	index = समय_dअगरf / TID_QUEUE_CELL_SPACING;

	/* The history is too दीर्घ: हटाओ data that is older than */
	/* TID_MAX_TIME_DIFF */
	अगर (index >= TID_QUEUE_MAX_SIZE)
		rs_tl_rm_old_stats(tl, curr_समय);
पूर्ण

अटल पूर्णांक rs_tl_turn_on_agg_क्रम_tid(काष्ठा iwl_priv *priv,
				      काष्ठा iwl_lq_sta *lq_data, u8 tid,
				      काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक ret = -EAGAIN;

	/*
	 * Don't create TX aggregation sessions when in high
	 * BT traffic, as they would just be disrupted by BT.
	 */
	अगर (priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH) अणु
		IWL_DEBUG_COEX(priv,
			       "BT traffic (%d), no aggregation allowed\n",
			       priv->bt_traffic_load);
		वापस ret;
	पूर्ण

	rs_tl_get_load(lq_data, tid);

	IWL_DEBUG_HT(priv, "Starting Tx agg: STA: %pM tid: %d\n",
			sta->addr, tid);
	ret = ieee80211_start_tx_ba_session(sta, tid, 5000);
	अगर (ret == -EAGAIN) अणु
		/*
		 * driver and mac80211 is out of sync
		 * this might be cause by reloading firmware
		 * stop the tx ba session here
		 */
		IWL_ERR(priv, "Fail start Tx agg on tid: %d\n",
			tid);
		ieee80211_stop_tx_ba_session(sta, tid);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम rs_tl_turn_on_agg(काष्ठा iwl_priv *priv, u8 tid,
			      काष्ठा iwl_lq_sta *lq_data,
			      काष्ठा ieee80211_sta *sta)
अणु
	अगर (tid < IWL_MAX_TID_COUNT)
		rs_tl_turn_on_agg_क्रम_tid(priv, lq_data, tid, sta);
	अन्यथा
		IWL_ERR(priv, "tid exceeds max TID count: %d/%d\n",
			tid, IWL_MAX_TID_COUNT);
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
अटल पूर्णांक rs_collect_tx_data(काष्ठा iwl_scale_tbl_info *tbl,
			      पूर्णांक scale_index, पूर्णांक attempts, पूर्णांक successes)
अणु
	काष्ठा iwl_rate_scale_data *winकरोw = शून्य;
	अटल स्थिर u64 mask = (((u64)1) << (IWL_RATE_MAX_WINDOW - 1));
	s32 fail_count, tpt;

	अगर (scale_index < 0 || scale_index >= IWL_RATE_COUNT)
		वापस -EINVAL;

	/* Select winकरोw क्रम current tx bit rate */
	winकरोw = &(tbl->win[scale_index]);

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
	अगर ((fail_count >= IWL_RATE_MIN_FAILURE_TH) ||
	    (winकरोw->success_counter >= IWL_RATE_MIN_SUCCESS_TH))
		winकरोw->average_tpt = (winकरोw->success_ratio * tpt + 64) / 128;
	अन्यथा
		winकरोw->average_tpt = IWL_INVALID_VALUE;

	/* Tag this winकरोw as having been updated */
	winकरोw->stamp = jअगरfies;

	वापस 0;
पूर्ण

/*
 * Fill uCode API rate_n_flags field, based on "search" or "active" table.
 */
/* FIXME:RS:हटाओ this function and put the flags अटलally in the table */
अटल u32 rate_n_flags_from_tbl(काष्ठा iwl_priv *priv,
				 काष्ठा iwl_scale_tbl_info *tbl,
				 पूर्णांक index, u8 use_green)
अणु
	u32 rate_n_flags = 0;

	अगर (is_legacy(tbl->lq_type)) अणु
		rate_n_flags = iwl_rates[index].plcp;
		अगर (index >= IWL_FIRST_CCK_RATE && index <= IWL_LAST_CCK_RATE)
			rate_n_flags |= RATE_MCS_CCK_MSK;

	पूर्ण अन्यथा अगर (is_Ht(tbl->lq_type)) अणु
		अगर (index > IWL_LAST_OFDM_RATE) अणु
			IWL_ERR(priv, "Invalid HT rate index %d\n", index);
			index = IWL_LAST_OFDM_RATE;
		पूर्ण
		rate_n_flags = RATE_MCS_HT_MSK;

		अगर (is_siso(tbl->lq_type))
			rate_n_flags |=	iwl_rates[index].plcp_siso;
		अन्यथा अगर (is_mimo2(tbl->lq_type))
			rate_n_flags |=	iwl_rates[index].plcp_mimo2;
		अन्यथा
			rate_n_flags |=	iwl_rates[index].plcp_mimo3;
	पूर्ण अन्यथा अणु
		IWL_ERR(priv, "Invalid tbl->lq_type %d\n", tbl->lq_type);
	पूर्ण

	rate_n_flags |= ((tbl->ant_type << RATE_MCS_ANT_POS) &
						     RATE_MCS_ANT_ABC_MSK);

	अगर (is_Ht(tbl->lq_type)) अणु
		अगर (tbl->is_ht40) अणु
			अगर (tbl->is_dup)
				rate_n_flags |= RATE_MCS_DUP_MSK;
			अन्यथा
				rate_n_flags |= RATE_MCS_HT40_MSK;
		पूर्ण
		अगर (tbl->is_SGI)
			rate_n_flags |= RATE_MCS_SGI_MSK;

		अगर (use_green) अणु
			rate_n_flags |= RATE_MCS_GF_MSK;
			अगर (is_siso(tbl->lq_type) && tbl->is_SGI) अणु
				rate_n_flags &= ~RATE_MCS_SGI_MSK;
				IWL_ERR(priv, "GF was set with SGI:SISO\n");
			पूर्ण
		पूर्ण
	पूर्ण
	वापस rate_n_flags;
पूर्ण

/*
 * Interpret uCode API's rate_n_flags क्रमmat,
 * fill "search" or "active" tx mode table.
 */
अटल पूर्णांक rs_get_tbl_info_from_mcs(स्थिर u32 rate_n_flags,
				    क्रमागत nl80211_band band,
				    काष्ठा iwl_scale_tbl_info *tbl,
				    पूर्णांक *rate_idx)
अणु
	u32 ant_msk = (rate_n_flags & RATE_MCS_ANT_ABC_MSK);
	u8 num_of_ant = get_num_of_ant_from_rate(rate_n_flags);
	u8 mcs;

	स_रखो(tbl, 0, माप(काष्ठा iwl_scale_tbl_info));
	*rate_idx = iwl_hwrate_to_plcp_idx(rate_n_flags);

	अगर (*rate_idx  == IWL_RATE_INVALID) अणु
		*rate_idx = -1;
		वापस -EINVAL;
	पूर्ण
	tbl->is_SGI = 0;	/* शेष legacy setup */
	tbl->is_ht40 = 0;
	tbl->is_dup = 0;
	tbl->ant_type = (ant_msk >> RATE_MCS_ANT_POS);
	tbl->lq_type = LQ_NONE;
	tbl->max_search = IWL_MAX_SEARCH;

	/* legacy rate क्रमmat */
	अगर (!(rate_n_flags & RATE_MCS_HT_MSK)) अणु
		अगर (num_of_ant == 1) अणु
			अगर (band == NL80211_BAND_5GHZ)
				tbl->lq_type = LQ_A;
			अन्यथा
				tbl->lq_type = LQ_G;
		पूर्ण
	/* HT rate क्रमmat */
	पूर्ण अन्यथा अणु
		अगर (rate_n_flags & RATE_MCS_SGI_MSK)
			tbl->is_SGI = 1;

		अगर ((rate_n_flags & RATE_MCS_HT40_MSK) ||
		    (rate_n_flags & RATE_MCS_DUP_MSK))
			tbl->is_ht40 = 1;

		अगर (rate_n_flags & RATE_MCS_DUP_MSK)
			tbl->is_dup = 1;

		mcs = rs_extract_rate(rate_n_flags);

		/* SISO */
		अगर (mcs <= IWL_RATE_SISO_60M_PLCP) अणु
			अगर (num_of_ant == 1)
				tbl->lq_type = LQ_SISO; /*अन्यथा NONE*/
		/* MIMO2 */
		पूर्ण अन्यथा अगर (mcs <= IWL_RATE_MIMO2_60M_PLCP) अणु
			अगर (num_of_ant == 2)
				tbl->lq_type = LQ_MIMO2;
		/* MIMO3 */
		पूर्ण अन्यथा अणु
			अगर (num_of_ant == 3) अणु
				tbl->max_search = IWL_MAX_11N_MIMO3_SEARCH;
				tbl->lq_type = LQ_MIMO3;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* चयन to another antenna/antennas and वापस 1 */
/* अगर no other valid antenna found, वापस 0 */
अटल पूर्णांक rs_toggle_antenna(u32 valid_ant, u32 *rate_n_flags,
			     काष्ठा iwl_scale_tbl_info *tbl)
अणु
	u8 new_ant_type;

	अगर (!tbl->ant_type || tbl->ant_type > ANT_ABC)
		वापस 0;

	अगर (!rs_is_valid_ant(valid_ant, tbl->ant_type))
		वापस 0;

	new_ant_type = ant_toggle_lookup[tbl->ant_type];

	जबतक ((new_ant_type != tbl->ant_type) &&
	       !rs_is_valid_ant(valid_ant, new_ant_type))
		new_ant_type = ant_toggle_lookup[new_ant_type];

	अगर (new_ant_type == tbl->ant_type)
		वापस 0;

	tbl->ant_type = new_ant_type;
	*rate_n_flags &= ~RATE_MCS_ANT_ABC_MSK;
	*rate_n_flags |= new_ant_type << RATE_MCS_ANT_POS;
	वापस 1;
पूर्ण

/*
 * Green-field mode is valid अगर the station supports it and
 * there are no non-GF stations present in the BSS.
 */
अटल bool rs_use_green(काष्ठा ieee80211_sta *sta)
अणु
	/*
	 * There's a bug somewhere in this code that causes the
	 * scaling to get stuck because GF+SGI can't be combined
	 * in SISO rates. Until we find that bug, disable GF, it
	 * has only limited benefit and we still पूर्णांकeroperate with
	 * GF APs since we can always receive GF transmissions.
	 */
	वापस false;
पूर्ण

/*
 * rs_get_supported_rates - get the available rates
 *
 * अगर management frame or broadcast frame only वापस
 * basic available rates.
 *
 */
अटल u16 rs_get_supported_rates(काष्ठा iwl_lq_sta *lq_sta,
				  काष्ठा ieee80211_hdr *hdr,
				  क्रमागत iwl_table_type rate_type)
अणु
	अगर (is_legacy(rate_type)) अणु
		वापस lq_sta->active_legacy_rate;
	पूर्ण अन्यथा अणु
		अगर (is_siso(rate_type))
			वापस lq_sta->active_siso_rate;
		अन्यथा अगर (is_mimo2(rate_type))
			वापस lq_sta->active_mimo2_rate;
		अन्यथा
			वापस lq_sta->active_mimo3_rate;
	पूर्ण
पूर्ण

अटल u16 rs_get_adjacent_rate(काष्ठा iwl_priv *priv, u8 index, u16 rate_mask,
				पूर्णांक rate_type)
अणु
	u8 high = IWL_RATE_INVALID;
	u8 low = IWL_RATE_INVALID;

	/* 802.11A or ht walks to the next literal adjacent rate in
	 * the rate table */
	अगर (is_a_band(rate_type) || !is_legacy(rate_type)) अणु
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
		IWL_DEBUG_RATE(priv, "Skipping masked lower rate: %d\n", low);
	पूर्ण

	high = index;
	जबतक (high != IWL_RATE_INVALID) अणु
		high = iwl_rates[high].next_rs;
		अगर (high == IWL_RATE_INVALID)
			अवरोध;
		अगर (rate_mask & (1 << high))
			अवरोध;
		IWL_DEBUG_RATE(priv, "Skipping masked higher rate: %d\n", high);
	पूर्ण

	वापस (high << 8) | low;
पूर्ण

अटल u32 rs_get_lower_rate(काष्ठा iwl_lq_sta *lq_sta,
			     काष्ठा iwl_scale_tbl_info *tbl,
			     u8 scale_index, u8 ht_possible)
अणु
	s32 low;
	u16 rate_mask;
	u16 high_low;
	u8 चयन_to_legacy = 0;
	u8 is_green = lq_sta->is_green;
	काष्ठा iwl_priv *priv = lq_sta->drv;

	/* check अगर we need to चयन from HT to legacy rates.
	 * assumption is that mandatory rates (1Mbps or 6Mbps)
	 * are always supported (spec demand) */
	अगर (!is_legacy(tbl->lq_type) && (!ht_possible || !scale_index)) अणु
		चयन_to_legacy = 1;
		scale_index = rs_ht_to_legacy[scale_index];
		अगर (lq_sta->band == NL80211_BAND_5GHZ)
			tbl->lq_type = LQ_A;
		अन्यथा
			tbl->lq_type = LQ_G;

		अगर (num_of_ant(tbl->ant_type) > 1)
			tbl->ant_type =
			    first_antenna(priv->nvm_data->valid_tx_ant);

		tbl->is_ht40 = 0;
		tbl->is_SGI = 0;
		tbl->max_search = IWL_MAX_SEARCH;
	पूर्ण

	rate_mask = rs_get_supported_rates(lq_sta, शून्य, tbl->lq_type);

	/* Mask with station rate restriction */
	अगर (is_legacy(tbl->lq_type)) अणु
		/* supp_rates has no CCK bits in A mode */
		अगर (lq_sta->band == NL80211_BAND_5GHZ)
			rate_mask  = (u16)(rate_mask &
			   (lq_sta->supp_rates << IWL_FIRST_OFDM_RATE));
		अन्यथा
			rate_mask = (u16)(rate_mask & lq_sta->supp_rates);
	पूर्ण

	/* If we चयनed from HT to legacy, check current rate */
	अगर (चयन_to_legacy && (rate_mask & (1 << scale_index))) अणु
		low = scale_index;
		जाओ out;
	पूर्ण

	high_low = rs_get_adjacent_rate(lq_sta->drv, scale_index, rate_mask,
					tbl->lq_type);
	low = high_low & 0xff;

	अगर (low == IWL_RATE_INVALID)
		low = scale_index;

out:
	वापस rate_n_flags_from_tbl(lq_sta->drv, tbl, low, is_green);
पूर्ण

/*
 * Simple function to compare two rate scale table types
 */
अटल bool table_type_matches(काष्ठा iwl_scale_tbl_info *a,
			       काष्ठा iwl_scale_tbl_info *b)
अणु
	वापस (a->lq_type == b->lq_type) && (a->ant_type == b->ant_type) &&
		(a->is_SGI == b->is_SGI);
पूर्ण

अटल व्योम rs_bt_update_lq(काष्ठा iwl_priv *priv, काष्ठा iwl_rxon_context *ctx,
			    काष्ठा iwl_lq_sta *lq_sta)
अणु
	काष्ठा iwl_scale_tbl_info *tbl;
	bool full_concurrent = priv->bt_full_concurrent;

	अगर ((priv->bt_traffic_load != priv->last_bt_traffic_load) ||
	    (priv->bt_full_concurrent != full_concurrent)) अणु
		priv->bt_full_concurrent = full_concurrent;
		priv->last_bt_traffic_load = priv->bt_traffic_load;

		/* Update uCode's rate table. */
		tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
		rs_fill_link_cmd(priv, lq_sta, tbl->current_rate);
		iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, CMD_ASYNC, false);

		queue_work(priv->workqueue, &priv->bt_full_concurrency);
	पूर्ण
पूर्ण

/*
 * mac80211 sends us Tx status
 */
अटल व्योम rs_tx_status(व्योम *priv_r, काष्ठा ieee80211_supported_band *sband,
			 काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
			 काष्ठा sk_buff *skb)
अणु
	पूर्णांक legacy_success;
	पूर्णांक retries;
	पूर्णांक rs_index, mac_index, i;
	काष्ठा iwl_lq_sta *lq_sta = priv_sta;
	काष्ठा iwl_link_quality_cmd *table;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा iwl_op_mode *op_mode = (काष्ठा iwl_op_mode *)priv_r;
	काष्ठा iwl_priv *priv = IWL_OP_MODE_GET_DVM(op_mode);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	क्रमागत mac80211_rate_control_flags mac_flags;
	u32 tx_rate;
	काष्ठा iwl_scale_tbl_info tbl_type;
	काष्ठा iwl_scale_tbl_info *curr_tbl, *other_tbl, *पंचांगp_tbl;
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	काष्ठा iwl_rxon_context *ctx = sta_priv->ctx;

	IWL_DEBUG_RATE_LIMIT(priv, "get frame ack response, update rate scale window\n");

	/* Treat uninitialized rate scaling data same as non-existing. */
	अगर (!lq_sta) अणु
		IWL_DEBUG_RATE(priv, "Station rate scaling not created yet.\n");
		वापस;
	पूर्ण अन्यथा अगर (!lq_sta->drv) अणु
		IWL_DEBUG_RATE(priv, "Rate scaling not initialized yet.\n");
		वापस;
	पूर्ण

	अगर (!ieee80211_is_data(hdr->frame_control) ||
	    info->flags & IEEE80211_TX_CTL_NO_ACK)
		वापस;

	/* This packet was aggregated but करोesn't carry status info */
	अगर ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(info->flags & IEEE80211_TX_STAT_AMPDU))
		वापस;

	/*
	 * Ignore this Tx frame response अगर its initial rate करोesn't match
	 * that of latest Link Quality command.  There may be stragglers
	 * from a previous Link Quality command, but we're no दीर्घer पूर्णांकerested
	 * in those; they're either from the "active" mode while we're trying
	 * to check "search" mode, or a prior "search" mode after we've moved
	 * to a new "search" mode (which might become the new "active" mode).
	 */
	table = &lq_sta->lq;
	tx_rate = le32_to_cpu(table->rs_table[0].rate_n_flags);
	rs_get_tbl_info_from_mcs(tx_rate, priv->band, &tbl_type, &rs_index);
	अगर (priv->band == NL80211_BAND_5GHZ)
		rs_index -= IWL_FIRST_OFDM_RATE;
	mac_flags = info->status.rates[0].flags;
	mac_index = info->status.rates[0].idx;
	/* For HT packets, map MCS to PLCP */
	अगर (mac_flags & IEEE80211_TX_RC_MCS) अणु
		mac_index &= RATE_MCS_CODE_MSK;	/* Remove # of streams */
		अगर (mac_index >= (IWL_RATE_9M_INDEX - IWL_FIRST_OFDM_RATE))
			mac_index++;
		/*
		 * mac80211 HT index is always zero-indexed; we need to move
		 * HT OFDM rates after CCK rates in 2.4 GHz band
		 */
		अगर (priv->band == NL80211_BAND_2GHZ)
			mac_index += IWL_FIRST_OFDM_RATE;
	पूर्ण
	/* Here we actually compare this rate to the latest LQ command */
	अगर ((mac_index < 0) ||
	    (tbl_type.is_SGI != !!(mac_flags & IEEE80211_TX_RC_SHORT_GI)) ||
	    (tbl_type.is_ht40 != !!(mac_flags & IEEE80211_TX_RC_40_MHZ_WIDTH)) ||
	    (tbl_type.is_dup != !!(mac_flags & IEEE80211_TX_RC_DUP_DATA)) ||
	    (tbl_type.ant_type != info->status.antenna) ||
	    (!!(tx_rate & RATE_MCS_HT_MSK) != !!(mac_flags & IEEE80211_TX_RC_MCS)) ||
	    (!!(tx_rate & RATE_MCS_GF_MSK) != !!(mac_flags & IEEE80211_TX_RC_GREEN_FIELD)) ||
	    (rs_index != mac_index)) अणु
		IWL_DEBUG_RATE(priv, "initial rate %d does not match %d (0x%x)\n", mac_index, rs_index, tx_rate);
		/*
		 * Since rates mis-match, the last LQ command may have failed.
		 * After IWL_MISSED_RATE_MAX mis-matches, resync the uCode with
		 * ... driver.
		 */
		lq_sta->missed_rate_counter++;
		अगर (lq_sta->missed_rate_counter > IWL_MISSED_RATE_MAX) अणु
			lq_sta->missed_rate_counter = 0;
			iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, CMD_ASYNC, false);
		पूर्ण
		/* Regardless, ignore this status info क्रम outdated rate */
		वापस;
	पूर्ण अन्यथा
		/* Rate did match, so reset the missed_rate_counter */
		lq_sta->missed_rate_counter = 0;

	/* Figure out अगर rate scale algorithm is in active or search table */
	अगर (table_type_matches(&tbl_type,
				&(lq_sta->lq_info[lq_sta->active_tbl]))) अणु
		curr_tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
		other_tbl = &(lq_sta->lq_info[1 - lq_sta->active_tbl]);
	पूर्ण अन्यथा अगर (table_type_matches(&tbl_type,
				&lq_sta->lq_info[1 - lq_sta->active_tbl])) अणु
		curr_tbl = &(lq_sta->lq_info[1 - lq_sta->active_tbl]);
		other_tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	पूर्ण अन्यथा अणु
		IWL_DEBUG_RATE(priv, "Neither active nor search matches tx rate\n");
		पंचांगp_tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
		IWL_DEBUG_RATE(priv, "active- lq:%x, ant:%x, SGI:%d\n",
			पंचांगp_tbl->lq_type, पंचांगp_tbl->ant_type, पंचांगp_tbl->is_SGI);
		पंचांगp_tbl = &(lq_sta->lq_info[1 - lq_sta->active_tbl]);
		IWL_DEBUG_RATE(priv, "search- lq:%x, ant:%x, SGI:%d\n",
			पंचांगp_tbl->lq_type, पंचांगp_tbl->ant_type, पंचांगp_tbl->is_SGI);
		IWL_DEBUG_RATE(priv, "actual- lq:%x, ant:%x, SGI:%d\n",
			tbl_type.lq_type, tbl_type.ant_type, tbl_type.is_SGI);
		/*
		 * no matching table found, let's by-pass the data collection
		 * and जारी to perक्रमm rate scale to find the rate table
		 */
		rs_stay_in_table(lq_sta, true);
		जाओ करोne;
	पूर्ण

	/*
	 * Updating the frame history depends on whether packets were
	 * aggregated.
	 *
	 * For aggregation, all packets were transmitted at the same rate, the
	 * first index पूर्णांकo rate scale table.
	 */
	अगर (info->flags & IEEE80211_TX_STAT_AMPDU) अणु
		tx_rate = le32_to_cpu(table->rs_table[0].rate_n_flags);
		rs_get_tbl_info_from_mcs(tx_rate, priv->band, &tbl_type,
				&rs_index);
		rs_collect_tx_data(curr_tbl, rs_index,
				   info->status.ampdu_len,
				   info->status.ampdu_ack_len);

		/* Update success/fail counts अगर not searching क्रम new mode */
		अगर (lq_sta->stay_in_tbl) अणु
			lq_sta->total_success += info->status.ampdu_ack_len;
			lq_sta->total_failed += (info->status.ampdu_len -
					info->status.ampdu_ack_len);
		पूर्ण
	पूर्ण अन्यथा अणु
	/*
	 * For legacy, update frame history with क्रम each Tx retry.
	 */
		retries = info->status.rates[0].count - 1;
		/* HW करोesn't send more than 15 retries */
		retries = min(retries, 15);

		/* The last transmission may have been successful */
		legacy_success = !!(info->flags & IEEE80211_TX_STAT_ACK);
		/* Collect data क्रम each rate used during failed TX attempts */
		क्रम (i = 0; i <= retries; ++i) अणु
			tx_rate = le32_to_cpu(table->rs_table[i].rate_n_flags);
			rs_get_tbl_info_from_mcs(tx_rate, priv->band,
					&tbl_type, &rs_index);
			/*
			 * Only collect stats अगर retried rate is in the same RS
			 * table as active/search.
			 */
			अगर (table_type_matches(&tbl_type, curr_tbl))
				पंचांगp_tbl = curr_tbl;
			अन्यथा अगर (table_type_matches(&tbl_type, other_tbl))
				पंचांगp_tbl = other_tbl;
			अन्यथा
				जारी;
			rs_collect_tx_data(पंचांगp_tbl, rs_index, 1,
					   i < retries ? 0 : legacy_success);
		पूर्ण

		/* Update success/fail counts अगर not searching क्रम new mode */
		अगर (lq_sta->stay_in_tbl) अणु
			lq_sta->total_success += legacy_success;
			lq_sta->total_failed += retries + (1 - legacy_success);
		पूर्ण
	पूर्ण
	/* The last TX rate is cached in lq_sta; it's set in अगर/अन्यथा above */
	lq_sta->last_rate_n_flags = tx_rate;
करोne:
	/* See अगर there's a better rate or modulation mode to try. */
	अगर (sta && sta->supp_rates[sband->band])
		rs_rate_scale_perक्रमm(priv, skb, sta, lq_sta);

	अगर (priv->lib->bt_params && priv->lib->bt_params->advanced_bt_coexist)
		rs_bt_update_lq(priv, ctx, lq_sta);
पूर्ण

/*
 * Begin a period of staying with a selected modulation mode.
 * Set "stay_in_tbl" flag to prevent any mode चयनes.
 * Set frame tx success limits according to legacy vs. high-throughput,
 * and reset overall (spanning all rates) tx success history statistics.
 * These control how दीर्घ we stay using same modulation mode beक्रमe
 * searching क्रम a new mode.
 */
अटल व्योम rs_set_stay_in_table(काष्ठा iwl_priv *priv, u8 is_legacy,
				 काष्ठा iwl_lq_sta *lq_sta)
अणु
	IWL_DEBUG_RATE(priv, "we are staying in the same table\n");
	lq_sta->stay_in_tbl = 1;	/* only place this माला_लो set */
	अगर (is_legacy) अणु
		lq_sta->table_count_limit = IWL_LEGACY_TABLE_COUNT;
		lq_sta->max_failure_limit = IWL_LEGACY_FAILURE_LIMIT;
		lq_sta->max_success_limit = IWL_LEGACY_SUCCESS_LIMIT;
	पूर्ण अन्यथा अणु
		lq_sta->table_count_limit = IWL_NONE_LEGACY_TABLE_COUNT;
		lq_sta->max_failure_limit = IWL_NONE_LEGACY_FAILURE_LIMIT;
		lq_sta->max_success_limit = IWL_NONE_LEGACY_SUCCESS_LIMIT;
	पूर्ण
	lq_sta->table_count = 0;
	lq_sta->total_failed = 0;
	lq_sta->total_success = 0;
	lq_sta->flush_समयr = jअगरfies;
	lq_sta->action_counter = 0;
पूर्ण

/*
 * Find correct throughput table क्रम given mode of modulation
 */
अटल व्योम rs_set_expected_tpt_table(काष्ठा iwl_lq_sta *lq_sta,
				      काष्ठा iwl_scale_tbl_info *tbl)
अणु
	/* Used to choose among HT tables */
	स्थिर u16 (*ht_tbl_poपूर्णांकer)[IWL_RATE_COUNT];

	/* Check क्रम invalid LQ type */
	अगर (WARN_ON_ONCE(!is_legacy(tbl->lq_type) && !is_Ht(tbl->lq_type))) अणु
		tbl->expected_tpt = expected_tpt_legacy;
		वापस;
	पूर्ण

	/* Legacy rates have only one table */
	अगर (is_legacy(tbl->lq_type)) अणु
		tbl->expected_tpt = expected_tpt_legacy;
		वापस;
	पूर्ण

	/* Choose among many HT tables depending on number of streams
	 * (SISO/MIMO2/MIMO3), channel width (20/40), SGI, and aggregation
	 * status */
	अगर (is_siso(tbl->lq_type) && (!tbl->is_ht40 || lq_sta->is_dup))
		ht_tbl_poपूर्णांकer = expected_tpt_siso20MHz;
	अन्यथा अगर (is_siso(tbl->lq_type))
		ht_tbl_poपूर्णांकer = expected_tpt_siso40MHz;
	अन्यथा अगर (is_mimo2(tbl->lq_type) && (!tbl->is_ht40 || lq_sta->is_dup))
		ht_tbl_poपूर्णांकer = expected_tpt_mimo2_20MHz;
	अन्यथा अगर (is_mimo2(tbl->lq_type))
		ht_tbl_poपूर्णांकer = expected_tpt_mimo2_40MHz;
	अन्यथा अगर (is_mimo3(tbl->lq_type) && (!tbl->is_ht40 || lq_sta->is_dup))
		ht_tbl_poपूर्णांकer = expected_tpt_mimo3_20MHz;
	अन्यथा /* अगर (is_mimo3(tbl->lq_type)) <-- must be true */
		ht_tbl_poपूर्णांकer = expected_tpt_mimo3_40MHz;

	अगर (!tbl->is_SGI && !lq_sta->is_agg)		/* Normal */
		tbl->expected_tpt = ht_tbl_poपूर्णांकer[0];
	अन्यथा अगर (tbl->is_SGI && !lq_sta->is_agg)	/* SGI */
		tbl->expected_tpt = ht_tbl_poपूर्णांकer[1];
	अन्यथा अगर (!tbl->is_SGI && lq_sta->is_agg)	/* AGG */
		tbl->expected_tpt = ht_tbl_poपूर्णांकer[2];
	अन्यथा						/* AGG+SGI */
		tbl->expected_tpt = ht_tbl_poपूर्णांकer[3];
पूर्ण

/*
 * Find starting rate क्रम new "search" high-throughput mode of modulation.
 * Goal is to find lowest expected rate (under perfect conditions) that is
 * above the current measured throughput of "active" mode, to give new mode
 * a fair chance to prove itself without too many challenges.
 *
 * This माला_लो called when transitioning to more aggressive modulation
 * (i.e. legacy to SISO or MIMO, or SISO to MIMO), as well as less aggressive
 * (i.e. MIMO to SISO).  When moving to MIMO, bit rate will typically need
 * to decrease to match "active" throughput.  When moving from MIMO to SISO,
 * bit rate will typically need to increase, but not अगर perक्रमmance was bad.
 */
अटल s32 rs_get_best_rate(काष्ठा iwl_priv *priv,
			    काष्ठा iwl_lq_sta *lq_sta,
			    काष्ठा iwl_scale_tbl_info *tbl,	/* "search" */
			    u16 rate_mask, s8 index)
अणु
	/* "active" values */
	काष्ठा iwl_scale_tbl_info *active_tbl =
	    &(lq_sta->lq_info[lq_sta->active_tbl]);
	s32 active_sr = active_tbl->win[index].success_ratio;
	s32 active_tpt = active_tbl->expected_tpt[index];
	/* expected "search" throughput */
	स्थिर u16 *tpt_tbl = tbl->expected_tpt;

	s32 new_rate, high, low, start_hi;
	u16 high_low;
	s8 rate = index;

	new_rate = high = low = start_hi = IWL_RATE_INVALID;

	क्रम (; ;) अणु
		high_low = rs_get_adjacent_rate(priv, rate, rate_mask,
						tbl->lq_type);

		low = high_low & 0xff;
		high = (high_low >> 8) & 0xff;

		/*
		 * Lower the "search" bit rate, to give new "search" mode
		 * approximately the same throughput as "active" अगर:
		 *
		 * 1) "Active" mode has been working modestly well (but not
		 *    great), and expected "search" throughput (under perfect
		 *    conditions) at candidate rate is above the actual
		 *    measured "active" throughput (but less than expected
		 *    "active" throughput under perfect conditions).
		 * OR
		 * 2) "Active" mode has been working perfectly or very well
		 *    and expected "search" throughput (under perfect
		 *    conditions) at candidate rate is above expected
		 *    "active" throughput (under perfect conditions).
		 */
		अगर ((((100 * tpt_tbl[rate]) > lq_sta->last_tpt) &&
		     ((active_sr > IWL_RATE_DECREASE_TH) &&
		      (active_sr <= IWL_RATE_HIGH_TH) &&
		      (tpt_tbl[rate] <= active_tpt))) ||
		    ((active_sr >= IWL_RATE_SCALE_SWITCH) &&
		     (tpt_tbl[rate] > active_tpt))) अणु

			/* (2nd or later pass)
			 * If we've alपढ़ोy tried to उठाओ the rate, and are
			 * now trying to lower it, use the higher rate. */
			अगर (start_hi != IWL_RATE_INVALID) अणु
				new_rate = start_hi;
				अवरोध;
			पूर्ण

			new_rate = rate;

			/* Loop again with lower rate */
			अगर (low != IWL_RATE_INVALID)
				rate = low;

			/* Lower rate not available, use the original */
			अन्यथा
				अवरोध;

		/* Else try to उठाओ the "search" rate to match "active" */
		पूर्ण अन्यथा अणु
			/* (2nd or later pass)
			 * If we've alपढ़ोy tried to lower the rate, and are
			 * now trying to उठाओ it, use the lower rate. */
			अगर (new_rate != IWL_RATE_INVALID)
				अवरोध;

			/* Loop again with higher rate */
			अन्यथा अगर (high != IWL_RATE_INVALID) अणु
				start_hi = high;
				rate = high;

			/* Higher rate not available, use the original */
			पूर्ण अन्यथा अणु
				new_rate = rate;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस new_rate;
पूर्ण

/*
 * Set up search table क्रम MIMO2
 */
अटल पूर्णांक rs_चयन_to_mimo2(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_lq_sta *lq_sta,
			     काष्ठा ieee80211_conf *conf,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा iwl_scale_tbl_info *tbl, पूर्णांक index)
अणु
	u16 rate_mask;
	s32 rate;
	s8 is_green = lq_sta->is_green;
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	काष्ठा iwl_rxon_context *ctx = sta_priv->ctx;

	अगर (!conf_is_ht(conf) || !sta->ht_cap.ht_supported)
		वापस -1;

	अगर (sta->smps_mode == IEEE80211_SMPS_STATIC)
		वापस -1;

	/* Need both Tx chains/antennas to support MIMO */
	अगर (priv->hw_params.tx_chains_num < 2)
		वापस -1;

	IWL_DEBUG_RATE(priv, "LQ: try to switch to MIMO2\n");

	tbl->lq_type = LQ_MIMO2;
	tbl->is_dup = lq_sta->is_dup;
	tbl->action = 0;
	tbl->max_search = IWL_MAX_SEARCH;
	rate_mask = lq_sta->active_mimo2_rate;

	अगर (iwl_is_ht40_tx_allowed(priv, ctx, sta))
		tbl->is_ht40 = 1;
	अन्यथा
		tbl->is_ht40 = 0;

	rs_set_expected_tpt_table(lq_sta, tbl);

	rate = rs_get_best_rate(priv, lq_sta, tbl, rate_mask, index);

	IWL_DEBUG_RATE(priv, "LQ: MIMO2 best rate %d mask %X\n", rate, rate_mask);
	अगर ((rate == IWL_RATE_INVALID) || !((1 << rate) & rate_mask)) अणु
		IWL_DEBUG_RATE(priv, "Can't switch with index %d rate mask %x\n",
						rate, rate_mask);
		वापस -1;
	पूर्ण
	tbl->current_rate = rate_n_flags_from_tbl(priv, tbl, rate, is_green);

	IWL_DEBUG_RATE(priv, "LQ: Switch to new mcs %X index is green %X\n",
		     tbl->current_rate, is_green);
	वापस 0;
पूर्ण

/*
 * Set up search table क्रम MIMO3
 */
अटल पूर्णांक rs_चयन_to_mimo3(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_lq_sta *lq_sta,
			     काष्ठा ieee80211_conf *conf,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा iwl_scale_tbl_info *tbl, पूर्णांक index)
अणु
	u16 rate_mask;
	s32 rate;
	s8 is_green = lq_sta->is_green;
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	काष्ठा iwl_rxon_context *ctx = sta_priv->ctx;

	अगर (!conf_is_ht(conf) || !sta->ht_cap.ht_supported)
		वापस -1;

	अगर (sta->smps_mode == IEEE80211_SMPS_STATIC)
		वापस -1;

	/* Need both Tx chains/antennas to support MIMO */
	अगर (priv->hw_params.tx_chains_num < 3)
		वापस -1;

	IWL_DEBUG_RATE(priv, "LQ: try to switch to MIMO3\n");

	tbl->lq_type = LQ_MIMO3;
	tbl->is_dup = lq_sta->is_dup;
	tbl->action = 0;
	tbl->max_search = IWL_MAX_11N_MIMO3_SEARCH;
	rate_mask = lq_sta->active_mimo3_rate;

	अगर (iwl_is_ht40_tx_allowed(priv, ctx, sta))
		tbl->is_ht40 = 1;
	अन्यथा
		tbl->is_ht40 = 0;

	rs_set_expected_tpt_table(lq_sta, tbl);

	rate = rs_get_best_rate(priv, lq_sta, tbl, rate_mask, index);

	IWL_DEBUG_RATE(priv, "LQ: MIMO3 best rate %d mask %X\n",
		rate, rate_mask);
	अगर ((rate == IWL_RATE_INVALID) || !((1 << rate) & rate_mask)) अणु
		IWL_DEBUG_RATE(priv, "Can't switch with index %d rate mask %x\n",
						rate, rate_mask);
		वापस -1;
	पूर्ण
	tbl->current_rate = rate_n_flags_from_tbl(priv, tbl, rate, is_green);

	IWL_DEBUG_RATE(priv, "LQ: Switch to new mcs %X index is green %X\n",
		     tbl->current_rate, is_green);
	वापस 0;
पूर्ण

/*
 * Set up search table क्रम SISO
 */
अटल पूर्णांक rs_चयन_to_siso(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_lq_sta *lq_sta,
			     काष्ठा ieee80211_conf *conf,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा iwl_scale_tbl_info *tbl, पूर्णांक index)
अणु
	u16 rate_mask;
	u8 is_green = lq_sta->is_green;
	s32 rate;
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	काष्ठा iwl_rxon_context *ctx = sta_priv->ctx;

	अगर (!conf_is_ht(conf) || !sta->ht_cap.ht_supported)
		वापस -1;

	IWL_DEBUG_RATE(priv, "LQ: try to switch to SISO\n");

	tbl->is_dup = lq_sta->is_dup;
	tbl->lq_type = LQ_SISO;
	tbl->action = 0;
	tbl->max_search = IWL_MAX_SEARCH;
	rate_mask = lq_sta->active_siso_rate;

	अगर (iwl_is_ht40_tx_allowed(priv, ctx, sta))
		tbl->is_ht40 = 1;
	अन्यथा
		tbl->is_ht40 = 0;

	अगर (is_green)
		tbl->is_SGI = 0; /*11n spec: no SGI in SISO+Greenfield*/

	rs_set_expected_tpt_table(lq_sta, tbl);
	rate = rs_get_best_rate(priv, lq_sta, tbl, rate_mask, index);

	IWL_DEBUG_RATE(priv, "LQ: get best rate %d mask %X\n", rate, rate_mask);
	अगर ((rate == IWL_RATE_INVALID) || !((1 << rate) & rate_mask)) अणु
		IWL_DEBUG_RATE(priv, "can not switch with index %d rate mask %x\n",
			     rate, rate_mask);
		वापस -1;
	पूर्ण
	tbl->current_rate = rate_n_flags_from_tbl(priv, tbl, rate, is_green);
	IWL_DEBUG_RATE(priv, "LQ: Switch to new mcs %X index is green %X\n",
		     tbl->current_rate, is_green);
	वापस 0;
पूर्ण

/*
 * Try to चयन to new modulation mode from legacy
 */
अटल व्योम rs_move_legacy_other(काष्ठा iwl_priv *priv,
				 काष्ठा iwl_lq_sta *lq_sta,
				 काष्ठा ieee80211_conf *conf,
				 काष्ठा ieee80211_sta *sta,
				 पूर्णांक index)
अणु
	काष्ठा iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	काष्ठा iwl_scale_tbl_info *search_tbl =
				&(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	काष्ठा iwl_rate_scale_data *winकरोw = &(tbl->win[index]);
	u32 sz = (माप(काष्ठा iwl_scale_tbl_info) -
		  (माप(काष्ठा iwl_rate_scale_data) * IWL_RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = priv->nvm_data->valid_tx_ant;
	u8 tx_chains_num = priv->hw_params.tx_chains_num;
	पूर्णांक ret = 0;
	u8 update_search_tbl_counter = 0;

	चयन (priv->bt_traffic_load) अणु
	हाल IWL_BT_COEX_TRAFFIC_LOAD_NONE:
		/* nothing */
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_LOW:
		/* aव्योम antenna B unless MIMO */
		अगर (tbl->action == IWL_LEGACY_SWITCH_ANTENNA2)
			tbl->action = IWL_LEGACY_SWITCH_SISO;
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_HIGH:
	हाल IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS:
		/* aव्योम antenna B and MIMO */
		valid_tx_ant =
			first_antenna(priv->nvm_data->valid_tx_ant);
		अगर (tbl->action >= IWL_LEGACY_SWITCH_ANTENNA2 &&
		    tbl->action != IWL_LEGACY_SWITCH_SISO)
			tbl->action = IWL_LEGACY_SWITCH_SISO;
		अवरोध;
	शेष:
		IWL_ERR(priv, "Invalid BT load %d\n", priv->bt_traffic_load);
		अवरोध;
	पूर्ण

	अगर (!iwl_ht_enabled(priv))
		/* stay in Legacy */
		tbl->action = IWL_LEGACY_SWITCH_ANTENNA1;
	अन्यथा अगर (iwl_tx_ant_restriction(priv) == IWL_ANT_OK_SINGLE &&
		   tbl->action > IWL_LEGACY_SWITCH_SISO)
		tbl->action = IWL_LEGACY_SWITCH_SISO;

	/* configure as 1x1 अगर bt full concurrency */
	अगर (priv->bt_full_concurrent) अणु
		अगर (!iwl_ht_enabled(priv))
			tbl->action = IWL_LEGACY_SWITCH_ANTENNA1;
		अन्यथा अगर (tbl->action >= IWL_LEGACY_SWITCH_ANTENNA2)
			tbl->action = IWL_LEGACY_SWITCH_SISO;
		valid_tx_ant =
			first_antenna(priv->nvm_data->valid_tx_ant);
	पूर्ण

	start_action = tbl->action;
	क्रम (; ;) अणु
		lq_sta->action_counter++;
		चयन (tbl->action) अणु
		हाल IWL_LEGACY_SWITCH_ANTENNA1:
		हाल IWL_LEGACY_SWITCH_ANTENNA2:
			IWL_DEBUG_RATE(priv, "LQ: Legacy toggle Antenna\n");

			अगर ((tbl->action == IWL_LEGACY_SWITCH_ANTENNA1 &&
							tx_chains_num <= 1) ||
			    (tbl->action == IWL_LEGACY_SWITCH_ANTENNA2 &&
							tx_chains_num <= 2))
				अवरोध;

			/* Don't change antenna अगर success has been great */
			अगर (winकरोw->success_ratio >= IWL_RS_GOOD_RATIO &&
			    !priv->bt_full_concurrent &&
			    priv->bt_traffic_load ==
					IWL_BT_COEX_TRAFFIC_LOAD_NONE)
				अवरोध;

			/* Set up search table to try other antenna */
			स_नकल(search_tbl, tbl, sz);

			अगर (rs_toggle_antenna(valid_tx_ant,
				&search_tbl->current_rate, search_tbl)) अणु
				update_search_tbl_counter = 1;
				rs_set_expected_tpt_table(lq_sta, search_tbl);
				जाओ out;
			पूर्ण
			अवरोध;
		हाल IWL_LEGACY_SWITCH_SISO:
			IWL_DEBUG_RATE(priv, "LQ: Legacy switch to SISO\n");

			/* Set up search table to try SISO */
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;
			ret = rs_चयन_to_siso(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret) अणु
				lq_sta->action_counter = 0;
				जाओ out;
			पूर्ण

			अवरोध;
		हाल IWL_LEGACY_SWITCH_MIMO2_AB:
		हाल IWL_LEGACY_SWITCH_MIMO2_AC:
		हाल IWL_LEGACY_SWITCH_MIMO2_BC:
			IWL_DEBUG_RATE(priv, "LQ: Legacy switch to MIMO2\n");

			/* Set up search table to try MIMO */
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;

			अगर (tbl->action == IWL_LEGACY_SWITCH_MIMO2_AB)
				search_tbl->ant_type = ANT_AB;
			अन्यथा अगर (tbl->action == IWL_LEGACY_SWITCH_MIMO2_AC)
				search_tbl->ant_type = ANT_AC;
			अन्यथा
				search_tbl->ant_type = ANT_BC;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_mimo2(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret) अणु
				lq_sta->action_counter = 0;
				जाओ out;
			पूर्ण
			अवरोध;

		हाल IWL_LEGACY_SWITCH_MIMO3_ABC:
			IWL_DEBUG_RATE(priv, "LQ: Legacy switch to MIMO3\n");

			/* Set up search table to try MIMO3 */
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;

			search_tbl->ant_type = ANT_ABC;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_mimo3(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret) अणु
				lq_sta->action_counter = 0;
				जाओ out;
			पूर्ण
			अवरोध;
		पूर्ण
		tbl->action++;
		अगर (tbl->action > IWL_LEGACY_SWITCH_MIMO3_ABC)
			tbl->action = IWL_LEGACY_SWITCH_ANTENNA1;

		अगर (tbl->action == start_action)
			अवरोध;

	पूर्ण
	search_tbl->lq_type = LQ_NONE;
	वापस;

out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	अगर (tbl->action > IWL_LEGACY_SWITCH_MIMO3_ABC)
		tbl->action = IWL_LEGACY_SWITCH_ANTENNA1;
	अगर (update_search_tbl_counter)
		search_tbl->action = tbl->action;
पूर्ण

/*
 * Try to चयन to new modulation mode from SISO
 */
अटल व्योम rs_move_siso_to_other(काष्ठा iwl_priv *priv,
				  काष्ठा iwl_lq_sta *lq_sta,
				  काष्ठा ieee80211_conf *conf,
				  काष्ठा ieee80211_sta *sta, पूर्णांक index)
अणु
	u8 is_green = lq_sta->is_green;
	काष्ठा iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	काष्ठा iwl_scale_tbl_info *search_tbl =
				&(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	काष्ठा iwl_rate_scale_data *winकरोw = &(tbl->win[index]);
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	u32 sz = (माप(काष्ठा iwl_scale_tbl_info) -
		  (माप(काष्ठा iwl_rate_scale_data) * IWL_RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = priv->nvm_data->valid_tx_ant;
	u8 tx_chains_num = priv->hw_params.tx_chains_num;
	u8 update_search_tbl_counter = 0;
	पूर्णांक ret;

	चयन (priv->bt_traffic_load) अणु
	हाल IWL_BT_COEX_TRAFFIC_LOAD_NONE:
		/* nothing */
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_LOW:
		/* aव्योम antenna B unless MIMO */
		अगर (tbl->action == IWL_SISO_SWITCH_ANTENNA2)
			tbl->action = IWL_SISO_SWITCH_MIMO2_AB;
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_HIGH:
	हाल IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS:
		/* aव्योम antenna B and MIMO */
		valid_tx_ant =
			first_antenna(priv->nvm_data->valid_tx_ant);
		अगर (tbl->action != IWL_SISO_SWITCH_ANTENNA1)
			tbl->action = IWL_SISO_SWITCH_ANTENNA1;
		अवरोध;
	शेष:
		IWL_ERR(priv, "Invalid BT load %d\n", priv->bt_traffic_load);
		अवरोध;
	पूर्ण

	अगर (iwl_tx_ant_restriction(priv) == IWL_ANT_OK_SINGLE &&
	    tbl->action > IWL_SISO_SWITCH_ANTENNA2) अणु
		/* stay in SISO */
		tbl->action = IWL_SISO_SWITCH_ANTENNA1;
	पूर्ण

	/* configure as 1x1 अगर bt full concurrency */
	अगर (priv->bt_full_concurrent) अणु
		valid_tx_ant =
			first_antenna(priv->nvm_data->valid_tx_ant);
		अगर (tbl->action >= IWL_LEGACY_SWITCH_ANTENNA2)
			tbl->action = IWL_SISO_SWITCH_ANTENNA1;
	पूर्ण

	start_action = tbl->action;
	क्रम (;;) अणु
		lq_sta->action_counter++;
		चयन (tbl->action) अणु
		हाल IWL_SISO_SWITCH_ANTENNA1:
		हाल IWL_SISO_SWITCH_ANTENNA2:
			IWL_DEBUG_RATE(priv, "LQ: SISO toggle Antenna\n");
			अगर ((tbl->action == IWL_SISO_SWITCH_ANTENNA1 &&
						tx_chains_num <= 1) ||
			    (tbl->action == IWL_SISO_SWITCH_ANTENNA2 &&
						tx_chains_num <= 2))
				अवरोध;

			अगर (winकरोw->success_ratio >= IWL_RS_GOOD_RATIO &&
			    !priv->bt_full_concurrent &&
			    priv->bt_traffic_load ==
					IWL_BT_COEX_TRAFFIC_LOAD_NONE)
				अवरोध;

			स_नकल(search_tbl, tbl, sz);
			अगर (rs_toggle_antenna(valid_tx_ant,
				       &search_tbl->current_rate, search_tbl)) अणु
				update_search_tbl_counter = 1;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल IWL_SISO_SWITCH_MIMO2_AB:
		हाल IWL_SISO_SWITCH_MIMO2_AC:
		हाल IWL_SISO_SWITCH_MIMO2_BC:
			IWL_DEBUG_RATE(priv, "LQ: SISO switch to MIMO2\n");
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;

			अगर (tbl->action == IWL_SISO_SWITCH_MIMO2_AB)
				search_tbl->ant_type = ANT_AB;
			अन्यथा अगर (tbl->action == IWL_SISO_SWITCH_MIMO2_AC)
				search_tbl->ant_type = ANT_AC;
			अन्यथा
				search_tbl->ant_type = ANT_BC;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_mimo2(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret)
				जाओ out;
			अवरोध;
		हाल IWL_SISO_SWITCH_GI:
			अगर (!tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_20))
				अवरोध;
			अगर (tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_40))
				अवरोध;

			IWL_DEBUG_RATE(priv, "LQ: SISO toggle SGI/NGI\n");

			स_नकल(search_tbl, tbl, sz);
			अगर (is_green) अणु
				अगर (!tbl->is_SGI)
					अवरोध;
				अन्यथा
					IWL_ERR(priv,
						"SGI was set in GF+SISO\n");
			पूर्ण
			search_tbl->is_SGI = !tbl->is_SGI;
			rs_set_expected_tpt_table(lq_sta, search_tbl);
			अगर (tbl->is_SGI) अणु
				s32 tpt = lq_sta->last_tpt / 100;
				अगर (tpt >= search_tbl->expected_tpt[index])
					अवरोध;
			पूर्ण
			search_tbl->current_rate =
				rate_n_flags_from_tbl(priv, search_tbl,
						      index, is_green);
			update_search_tbl_counter = 1;
			जाओ out;
		हाल IWL_SISO_SWITCH_MIMO3_ABC:
			IWL_DEBUG_RATE(priv, "LQ: SISO switch to MIMO3\n");
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;
			search_tbl->ant_type = ANT_ABC;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_mimo3(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret)
				जाओ out;
			अवरोध;
		पूर्ण
		tbl->action++;
		अगर (tbl->action > IWL_LEGACY_SWITCH_MIMO3_ABC)
			tbl->action = IWL_SISO_SWITCH_ANTENNA1;

		अगर (tbl->action == start_action)
			अवरोध;
	पूर्ण
	search_tbl->lq_type = LQ_NONE;
	वापस;

 out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	अगर (tbl->action > IWL_SISO_SWITCH_MIMO3_ABC)
		tbl->action = IWL_SISO_SWITCH_ANTENNA1;
	अगर (update_search_tbl_counter)
		search_tbl->action = tbl->action;
पूर्ण

/*
 * Try to चयन to new modulation mode from MIMO2
 */
अटल व्योम rs_move_mimo2_to_other(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_lq_sta *lq_sta,
				   काष्ठा ieee80211_conf *conf,
				   काष्ठा ieee80211_sta *sta, पूर्णांक index)
अणु
	s8 is_green = lq_sta->is_green;
	काष्ठा iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	काष्ठा iwl_scale_tbl_info *search_tbl =
				&(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	काष्ठा iwl_rate_scale_data *winकरोw = &(tbl->win[index]);
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	u32 sz = (माप(काष्ठा iwl_scale_tbl_info) -
		  (माप(काष्ठा iwl_rate_scale_data) * IWL_RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = priv->nvm_data->valid_tx_ant;
	u8 tx_chains_num = priv->hw_params.tx_chains_num;
	u8 update_search_tbl_counter = 0;
	पूर्णांक ret;

	चयन (priv->bt_traffic_load) अणु
	हाल IWL_BT_COEX_TRAFFIC_LOAD_NONE:
		/* nothing */
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_HIGH:
	हाल IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS:
		/* aव्योम antenna B and MIMO */
		अगर (tbl->action != IWL_MIMO2_SWITCH_SISO_A)
			tbl->action = IWL_MIMO2_SWITCH_SISO_A;
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_LOW:
		/* aव्योम antenna B unless MIMO */
		अगर (tbl->action == IWL_MIMO2_SWITCH_SISO_B ||
		    tbl->action == IWL_MIMO2_SWITCH_SISO_C)
			tbl->action = IWL_MIMO2_SWITCH_SISO_A;
		अवरोध;
	शेष:
		IWL_ERR(priv, "Invalid BT load %d\n", priv->bt_traffic_load);
		अवरोध;
	पूर्ण

	अगर ((iwl_tx_ant_restriction(priv) == IWL_ANT_OK_SINGLE) &&
	    (tbl->action < IWL_MIMO2_SWITCH_SISO_A ||
	     tbl->action > IWL_MIMO2_SWITCH_SISO_C)) अणु
		/* चयन in SISO */
		tbl->action = IWL_MIMO2_SWITCH_SISO_A;
	पूर्ण

	/* configure as 1x1 अगर bt full concurrency */
	अगर (priv->bt_full_concurrent &&
	    (tbl->action < IWL_MIMO2_SWITCH_SISO_A ||
	     tbl->action > IWL_MIMO2_SWITCH_SISO_C))
		tbl->action = IWL_MIMO2_SWITCH_SISO_A;

	start_action = tbl->action;
	क्रम (;;) अणु
		lq_sta->action_counter++;
		चयन (tbl->action) अणु
		हाल IWL_MIMO2_SWITCH_ANTENNA1:
		हाल IWL_MIMO2_SWITCH_ANTENNA2:
			IWL_DEBUG_RATE(priv, "LQ: MIMO2 toggle Antennas\n");

			अगर (tx_chains_num <= 2)
				अवरोध;

			अगर (winकरोw->success_ratio >= IWL_RS_GOOD_RATIO)
				अवरोध;

			स_नकल(search_tbl, tbl, sz);
			अगर (rs_toggle_antenna(valid_tx_ant,
				       &search_tbl->current_rate, search_tbl)) अणु
				update_search_tbl_counter = 1;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल IWL_MIMO2_SWITCH_SISO_A:
		हाल IWL_MIMO2_SWITCH_SISO_B:
		हाल IWL_MIMO2_SWITCH_SISO_C:
			IWL_DEBUG_RATE(priv, "LQ: MIMO2 switch to SISO\n");

			/* Set up new search table क्रम SISO */
			स_नकल(search_tbl, tbl, sz);

			अगर (tbl->action == IWL_MIMO2_SWITCH_SISO_A)
				search_tbl->ant_type = ANT_A;
			अन्यथा अगर (tbl->action == IWL_MIMO2_SWITCH_SISO_B)
				search_tbl->ant_type = ANT_B;
			अन्यथा
				search_tbl->ant_type = ANT_C;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_siso(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret)
				जाओ out;

			अवरोध;

		हाल IWL_MIMO2_SWITCH_GI:
			अगर (!tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_20))
				अवरोध;
			अगर (tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_40))
				अवरोध;

			IWL_DEBUG_RATE(priv, "LQ: MIMO2 toggle SGI/NGI\n");

			/* Set up new search table क्रम MIMO2 */
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = !tbl->is_SGI;
			rs_set_expected_tpt_table(lq_sta, search_tbl);
			/*
			 * If active table alपढ़ोy uses the fastest possible
			 * modulation (dual stream with लघु guard पूर्णांकerval),
			 * and it's working well, there's no need to look
			 * क्रम a better type of modulation!
			 */
			अगर (tbl->is_SGI) अणु
				s32 tpt = lq_sta->last_tpt / 100;
				अगर (tpt >= search_tbl->expected_tpt[index])
					अवरोध;
			पूर्ण
			search_tbl->current_rate =
				rate_n_flags_from_tbl(priv, search_tbl,
						      index, is_green);
			update_search_tbl_counter = 1;
			जाओ out;

		हाल IWL_MIMO2_SWITCH_MIMO3_ABC:
			IWL_DEBUG_RATE(priv, "LQ: MIMO2 switch to MIMO3\n");
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;
			search_tbl->ant_type = ANT_ABC;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_mimo3(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret)
				जाओ out;

			अवरोध;
		पूर्ण
		tbl->action++;
		अगर (tbl->action > IWL_MIMO2_SWITCH_MIMO3_ABC)
			tbl->action = IWL_MIMO2_SWITCH_ANTENNA1;

		अगर (tbl->action == start_action)
			अवरोध;
	पूर्ण
	search_tbl->lq_type = LQ_NONE;
	वापस;
 out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	अगर (tbl->action > IWL_MIMO2_SWITCH_MIMO3_ABC)
		tbl->action = IWL_MIMO2_SWITCH_ANTENNA1;
	अगर (update_search_tbl_counter)
		search_tbl->action = tbl->action;

पूर्ण

/*
 * Try to चयन to new modulation mode from MIMO3
 */
अटल व्योम rs_move_mimo3_to_other(काष्ठा iwl_priv *priv,
				   काष्ठा iwl_lq_sta *lq_sta,
				   काष्ठा ieee80211_conf *conf,
				   काष्ठा ieee80211_sta *sta, पूर्णांक index)
अणु
	s8 is_green = lq_sta->is_green;
	काष्ठा iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
	काष्ठा iwl_scale_tbl_info *search_tbl =
				&(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
	काष्ठा iwl_rate_scale_data *winकरोw = &(tbl->win[index]);
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	u32 sz = (माप(काष्ठा iwl_scale_tbl_info) -
		  (माप(काष्ठा iwl_rate_scale_data) * IWL_RATE_COUNT));
	u8 start_action;
	u8 valid_tx_ant = priv->nvm_data->valid_tx_ant;
	u8 tx_chains_num = priv->hw_params.tx_chains_num;
	पूर्णांक ret;
	u8 update_search_tbl_counter = 0;

	चयन (priv->bt_traffic_load) अणु
	हाल IWL_BT_COEX_TRAFFIC_LOAD_NONE:
		/* nothing */
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_HIGH:
	हाल IWL_BT_COEX_TRAFFIC_LOAD_CONTINUOUS:
		/* aव्योम antenna B and MIMO */
		अगर (tbl->action != IWL_MIMO3_SWITCH_SISO_A)
			tbl->action = IWL_MIMO3_SWITCH_SISO_A;
		अवरोध;
	हाल IWL_BT_COEX_TRAFFIC_LOAD_LOW:
		/* aव्योम antenna B unless MIMO */
		अगर (tbl->action == IWL_MIMO3_SWITCH_SISO_B ||
		    tbl->action == IWL_MIMO3_SWITCH_SISO_C)
			tbl->action = IWL_MIMO3_SWITCH_SISO_A;
		अवरोध;
	शेष:
		IWL_ERR(priv, "Invalid BT load %d\n", priv->bt_traffic_load);
		अवरोध;
	पूर्ण

	अगर ((iwl_tx_ant_restriction(priv) == IWL_ANT_OK_SINGLE) &&
	    (tbl->action < IWL_MIMO3_SWITCH_SISO_A ||
	     tbl->action > IWL_MIMO3_SWITCH_SISO_C)) अणु
		/* चयन in SISO */
		tbl->action = IWL_MIMO3_SWITCH_SISO_A;
	पूर्ण

	/* configure as 1x1 अगर bt full concurrency */
	अगर (priv->bt_full_concurrent &&
	    (tbl->action < IWL_MIMO3_SWITCH_SISO_A ||
	     tbl->action > IWL_MIMO3_SWITCH_SISO_C))
		tbl->action = IWL_MIMO3_SWITCH_SISO_A;

	start_action = tbl->action;
	क्रम (;;) अणु
		lq_sta->action_counter++;
		चयन (tbl->action) अणु
		हाल IWL_MIMO3_SWITCH_ANTENNA1:
		हाल IWL_MIMO3_SWITCH_ANTENNA2:
			IWL_DEBUG_RATE(priv, "LQ: MIMO3 toggle Antennas\n");

			अगर (tx_chains_num <= 3)
				अवरोध;

			अगर (winकरोw->success_ratio >= IWL_RS_GOOD_RATIO)
				अवरोध;

			स_नकल(search_tbl, tbl, sz);
			अगर (rs_toggle_antenna(valid_tx_ant,
				       &search_tbl->current_rate, search_tbl))
				जाओ out;
			अवरोध;
		हाल IWL_MIMO3_SWITCH_SISO_A:
		हाल IWL_MIMO3_SWITCH_SISO_B:
		हाल IWL_MIMO3_SWITCH_SISO_C:
			IWL_DEBUG_RATE(priv, "LQ: MIMO3 switch to SISO\n");

			/* Set up new search table क्रम SISO */
			स_नकल(search_tbl, tbl, sz);

			अगर (tbl->action == IWL_MIMO3_SWITCH_SISO_A)
				search_tbl->ant_type = ANT_A;
			अन्यथा अगर (tbl->action == IWL_MIMO3_SWITCH_SISO_B)
				search_tbl->ant_type = ANT_B;
			अन्यथा
				search_tbl->ant_type = ANT_C;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_siso(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret)
				जाओ out;

			अवरोध;

		हाल IWL_MIMO3_SWITCH_MIMO2_AB:
		हाल IWL_MIMO3_SWITCH_MIMO2_AC:
		हाल IWL_MIMO3_SWITCH_MIMO2_BC:
			IWL_DEBUG_RATE(priv, "LQ: MIMO3 switch to MIMO2\n");

			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = 0;
			अगर (tbl->action == IWL_MIMO3_SWITCH_MIMO2_AB)
				search_tbl->ant_type = ANT_AB;
			अन्यथा अगर (tbl->action == IWL_MIMO3_SWITCH_MIMO2_AC)
				search_tbl->ant_type = ANT_AC;
			अन्यथा
				search_tbl->ant_type = ANT_BC;

			अगर (!rs_is_valid_ant(valid_tx_ant, search_tbl->ant_type))
				अवरोध;

			ret = rs_चयन_to_mimo2(priv, lq_sta, conf, sta,
						 search_tbl, index);
			अगर (!ret)
				जाओ out;

			अवरोध;

		हाल IWL_MIMO3_SWITCH_GI:
			अगर (!tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_20))
				अवरोध;
			अगर (tbl->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_40))
				अवरोध;

			IWL_DEBUG_RATE(priv, "LQ: MIMO3 toggle SGI/NGI\n");

			/* Set up new search table क्रम MIMO */
			स_नकल(search_tbl, tbl, sz);
			search_tbl->is_SGI = !tbl->is_SGI;
			rs_set_expected_tpt_table(lq_sta, search_tbl);
			/*
			 * If active table alपढ़ोy uses the fastest possible
			 * modulation (dual stream with लघु guard पूर्णांकerval),
			 * and it's working well, there's no need to look
			 * क्रम a better type of modulation!
			 */
			अगर (tbl->is_SGI) अणु
				s32 tpt = lq_sta->last_tpt / 100;
				अगर (tpt >= search_tbl->expected_tpt[index])
					अवरोध;
			पूर्ण
			search_tbl->current_rate =
				rate_n_flags_from_tbl(priv, search_tbl,
						      index, is_green);
			update_search_tbl_counter = 1;
			जाओ out;
		पूर्ण
		tbl->action++;
		अगर (tbl->action > IWL_MIMO3_SWITCH_GI)
			tbl->action = IWL_MIMO3_SWITCH_ANTENNA1;

		अगर (tbl->action == start_action)
			अवरोध;
	पूर्ण
	search_tbl->lq_type = LQ_NONE;
	वापस;
 out:
	lq_sta->search_better_tbl = 1;
	tbl->action++;
	अगर (tbl->action > IWL_MIMO3_SWITCH_GI)
		tbl->action = IWL_MIMO3_SWITCH_ANTENNA1;
	अगर (update_search_tbl_counter)
		search_tbl->action = tbl->action;
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
	पूर्णांक i;
	पूर्णांक active_tbl;
	पूर्णांक flush_पूर्णांकerval_passed = 0;
	काष्ठा iwl_priv *priv;

	priv = lq_sta->drv;
	active_tbl = lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	/* If we've been disallowing search, see अगर we should now allow it */
	अगर (lq_sta->stay_in_tbl) अणु

		/* Elapsed समय using current modulation mode */
		अगर (lq_sta->flush_समयr)
			flush_पूर्णांकerval_passed =
			समय_after(jअगरfies,
					(अचिन्हित दीर्घ)(lq_sta->flush_समयr +
					IWL_RATE_SCALE_FLUSH_INTVL));

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
		    ((!lq_sta->search_better_tbl) && (lq_sta->flush_समयr)
		     && (flush_पूर्णांकerval_passed))) अणु
			IWL_DEBUG_RATE(priv, "LQ: stay is expired %d %d %d\n",
				     lq_sta->total_failed,
				     lq_sta->total_success,
				     flush_पूर्णांकerval_passed);

			/* Allow search क्रम new mode */
			lq_sta->stay_in_tbl = 0;	/* only place reset */
			lq_sta->total_failed = 0;
			lq_sta->total_success = 0;
			lq_sta->flush_समयr = 0;

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

				IWL_DEBUG_RATE(priv, "LQ: stay in table clear win\n");
				क्रम (i = 0; i < IWL_RATE_COUNT; i++)
					rs_rate_scale_clear_winकरोw(
						&(tbl->win[i]));
			पूर्ण
		पूर्ण

		/* If transitioning to allow "search", reset all history
		 * biपंचांगaps and stats in active table (this will become the new
		 * "search" table). */
		अगर (!lq_sta->stay_in_tbl) अणु
			क्रम (i = 0; i < IWL_RATE_COUNT; i++)
				rs_rate_scale_clear_winकरोw(&(tbl->win[i]));
		पूर्ण
	पूर्ण
पूर्ण

/*
 * setup rate table in uCode
 */
अटल व्योम rs_update_rate_tbl(काष्ठा iwl_priv *priv,
			       काष्ठा iwl_rxon_context *ctx,
			       काष्ठा iwl_lq_sta *lq_sta,
			       काष्ठा iwl_scale_tbl_info *tbl,
			       पूर्णांक index, u8 is_green)
अणु
	u32 rate;

	/* Update uCode's rate table. */
	rate = rate_n_flags_from_tbl(priv, tbl, index, is_green);
	rs_fill_link_cmd(priv, lq_sta, rate);
	iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, CMD_ASYNC, false);
पूर्ण

/*
 * Do rate scaling and search क्रम new modulation mode.
 */
अटल व्योम rs_rate_scale_perक्रमm(काष्ठा iwl_priv *priv,
				  काष्ठा sk_buff *skb,
				  काष्ठा ieee80211_sta *sta,
				  काष्ठा iwl_lq_sta *lq_sta)
अणु
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	पूर्णांक low = IWL_RATE_INVALID;
	पूर्णांक high = IWL_RATE_INVALID;
	पूर्णांक index;
	पूर्णांक i;
	काष्ठा iwl_rate_scale_data *winकरोw = शून्य;
	पूर्णांक current_tpt = IWL_INVALID_VALUE;
	पूर्णांक low_tpt = IWL_INVALID_VALUE;
	पूर्णांक high_tpt = IWL_INVALID_VALUE;
	u32 fail_count;
	s8 scale_action = 0;
	u16 rate_mask;
	u8 update_lq = 0;
	काष्ठा iwl_scale_tbl_info *tbl, *tbl1;
	u16 rate_scale_index_msk = 0;
	u8 is_green = 0;
	u8 active_tbl = 0;
	u8 करोne_search = 0;
	u16 high_low;
	s32 sr;
	u8 tid = IWL_MAX_TID_COUNT;
	काष्ठा iwl_tid_data *tid_data;
	काष्ठा iwl_station_priv *sta_priv = (व्योम *)sta->drv_priv;
	काष्ठा iwl_rxon_context *ctx = sta_priv->ctx;

	IWL_DEBUG_RATE(priv, "rate scale calculate new rate for skb\n");

	/* Send management frames and NO_ACK data using lowest rate. */
	/* TODO: this could probably be improved.. */
	अगर (!ieee80211_is_data(hdr->frame_control) ||
	    info->flags & IEEE80211_TX_CTL_NO_ACK)
		वापस;

	lq_sta->supp_rates = sta->supp_rates[lq_sta->band];

	tid = rs_tl_add_packet(lq_sta, hdr);
	अगर ((tid != IWL_MAX_TID_COUNT) &&
	    (lq_sta->tx_agg_tid_en & (1 << tid))) अणु
		tid_data = &priv->tid_data[lq_sta->lq.sta_id][tid];
		अगर (tid_data->agg.state == IWL_AGG_OFF)
			lq_sta->is_agg = 0;
		अन्यथा
			lq_sta->is_agg = 1;
	पूर्ण अन्यथा
		lq_sta->is_agg = 0;

	/*
	 * Select rate-scale / modulation-mode table to work with in
	 * the rest of this function:  "search" अगर searching क्रम better
	 * modulation mode, or "active" अगर करोing rate scaling within a mode.
	 */
	अगर (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	अन्यथा
		active_tbl = 1 - lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);
	अगर (is_legacy(tbl->lq_type))
		lq_sta->is_green = 0;
	अन्यथा
		lq_sta->is_green = rs_use_green(sta);
	is_green = lq_sta->is_green;

	/* current tx rate */
	index = lq_sta->last_txrate_idx;

	IWL_DEBUG_RATE(priv, "Rate scale index %d for type %d\n", index,
		       tbl->lq_type);

	/* rates available क्रम this association, and क्रम modulation mode */
	rate_mask = rs_get_supported_rates(lq_sta, hdr, tbl->lq_type);

	IWL_DEBUG_RATE(priv, "mask 0x%04X\n", rate_mask);

	/* mask with station rate restriction */
	अगर (is_legacy(tbl->lq_type)) अणु
		अगर (lq_sta->band == NL80211_BAND_5GHZ)
			/* supp_rates has no CCK bits in A mode */
			rate_scale_index_msk = (u16) (rate_mask &
				(lq_sta->supp_rates << IWL_FIRST_OFDM_RATE));
		अन्यथा
			rate_scale_index_msk = (u16) (rate_mask &
						      lq_sta->supp_rates);

	पूर्ण अन्यथा
		rate_scale_index_msk = rate_mask;

	अगर (!rate_scale_index_msk)
		rate_scale_index_msk = rate_mask;

	अगर (!((1 << index) & rate_scale_index_msk)) अणु
		IWL_ERR(priv, "Current Rate is not valid\n");
		अगर (lq_sta->search_better_tbl) अणु
			/* revert to active table अगर search table is not valid*/
			tbl->lq_type = LQ_NONE;
			lq_sta->search_better_tbl = 0;
			tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);
			/* get "active" rate info */
			index = iwl_hwrate_to_plcp_idx(tbl->current_rate);
			rs_update_rate_tbl(priv, ctx, lq_sta, tbl,
					   index, is_green);
		पूर्ण
		वापस;
	पूर्ण

	/* Get expected throughput table and history winकरोw क्रम current rate */
	अगर (!tbl->expected_tpt) अणु
		IWL_ERR(priv, "tbl->expected_tpt is NULL\n");
		वापस;
	पूर्ण

	/* क्रमce user max rate अगर set by user */
	अगर ((lq_sta->max_rate_idx != -1) &&
	    (lq_sta->max_rate_idx < index)) अणु
		index = lq_sta->max_rate_idx;
		update_lq = 1;
		winकरोw = &(tbl->win[index]);
		जाओ lq_update;
	पूर्ण

	winकरोw = &(tbl->win[index]);

	/*
	 * If there is not enough history to calculate actual average
	 * throughput, keep analyzing results of more tx frames, without
	 * changing rate or mode (bypass most of the rest of this function).
	 * Set up new rate table in uCode only अगर old rate is not supported
	 * in current association (use new rate found above).
	 */
	fail_count = winकरोw->counter - winकरोw->success_counter;
	अगर ((fail_count < IWL_RATE_MIN_FAILURE_TH) &&
			(winकरोw->success_counter < IWL_RATE_MIN_SUCCESS_TH)) अणु
		IWL_DEBUG_RATE(priv, "LQ: still below TH. succ=%d total=%d "
			       "for index %d\n",
			       winकरोw->success_counter, winकरोw->counter, index);

		/* Can't calculate this yet; not enough history */
		winकरोw->average_tpt = IWL_INVALID_VALUE;

		/* Should we stay with this modulation mode,
		 * or search क्रम a new one? */
		rs_stay_in_table(lq_sta, false);

		जाओ out;
	पूर्ण
	/* Else we have enough samples; calculate estimate of
	 * actual average throughput */
	अगर (winकरोw->average_tpt != ((winकरोw->success_ratio *
			tbl->expected_tpt[index] + 64) / 128)) अणु
		IWL_ERR(priv, "expected_tpt should have been calculated by now\n");
		winकरोw->average_tpt = ((winकरोw->success_ratio *
					tbl->expected_tpt[index] + 64) / 128);
	पूर्ण

	/* If we are searching क्रम better modulation mode, check success. */
	अगर (lq_sta->search_better_tbl &&
	    (iwl_tx_ant_restriction(priv) == IWL_ANT_OK_MULTI)) अणु
		/* If good success, जारी using the "search" mode;
		 * no need to send new link quality command, since we're
		 * continuing to use the setup that we've been trying. */
		अगर (winकरोw->average_tpt > lq_sta->last_tpt) अणु

			IWL_DEBUG_RATE(priv, "LQ: SWITCHING TO NEW TABLE "
					"suc=%d cur-tpt=%d old-tpt=%d\n",
					winकरोw->success_ratio,
					winकरोw->average_tpt,
					lq_sta->last_tpt);

			अगर (!is_legacy(tbl->lq_type))
				lq_sta->enable_counter = 1;

			/* Swap tables; "search" becomes "active" */
			lq_sta->active_tbl = active_tbl;
			current_tpt = winकरोw->average_tpt;

		/* Else poor success; go back to mode in "active" table */
		पूर्ण अन्यथा अणु

			IWL_DEBUG_RATE(priv, "LQ: GOING BACK TO THE OLD TABLE "
					"suc=%d cur-tpt=%d old-tpt=%d\n",
					winकरोw->success_ratio,
					winकरोw->average_tpt,
					lq_sta->last_tpt);

			/* Nullअगरy "search" table */
			tbl->lq_type = LQ_NONE;

			/* Revert to "active" table */
			active_tbl = lq_sta->active_tbl;
			tbl = &(lq_sta->lq_info[active_tbl]);

			/* Revert to "active" rate and throughput info */
			index = iwl_hwrate_to_plcp_idx(tbl->current_rate);
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
	high_low = rs_get_adjacent_rate(priv, index, rate_scale_index_msk,
					tbl->lq_type);
	low = high_low & 0xff;
	high = (high_low >> 8) & 0xff;

	/* If user set max rate, करोnt allow higher than user स्थिरrain */
	अगर ((lq_sta->max_rate_idx != -1) &&
	    (lq_sta->max_rate_idx < high))
		high = IWL_RATE_INVALID;

	sr = winकरोw->success_ratio;

	/* Collect measured throughमाला_दो क्रम current and adjacent rates */
	current_tpt = winकरोw->average_tpt;
	अगर (low != IWL_RATE_INVALID)
		low_tpt = tbl->win[low].average_tpt;
	अगर (high != IWL_RATE_INVALID)
		high_tpt = tbl->win[high].average_tpt;

	scale_action = 0;

	/* Too many failures, decrease rate */
	अगर ((sr <= IWL_RATE_DECREASE_TH) || (current_tpt == 0)) अणु
		IWL_DEBUG_RATE(priv, "decrease rate because of low success_ratio\n");
		scale_action = -1;

	/* No throughput measured yet क्रम adjacent rates; try increase. */
	पूर्ण अन्यथा अगर ((low_tpt == IWL_INVALID_VALUE) &&
		   (high_tpt == IWL_INVALID_VALUE)) अणु

		अगर (high != IWL_RATE_INVALID && sr >= IWL_RATE_INCREASE_TH)
			scale_action = 1;
		अन्यथा अगर (low != IWL_RATE_INVALID)
			scale_action = 0;
	पूर्ण

	/* Both adjacent throughमाला_दो are measured, but neither one has better
	 * throughput; we're using the best rate, don't change it! */
	अन्यथा अगर ((low_tpt != IWL_INVALID_VALUE) &&
		 (high_tpt != IWL_INVALID_VALUE) &&
		 (low_tpt < current_tpt) &&
		 (high_tpt < current_tpt))
		scale_action = 0;

	/* At least one adjacent rate's throughput is measured,
	 * and may have better perक्रमmance. */
	अन्यथा अणु
		/* Higher adjacent rate's throughput is measured */
		अगर (high_tpt != IWL_INVALID_VALUE) अणु
			/* Higher rate has better throughput */
			अगर (high_tpt > current_tpt &&
					sr >= IWL_RATE_INCREASE_TH) अणु
				scale_action = 1;
			पूर्ण अन्यथा अणु
				scale_action = 0;
			पूर्ण

		/* Lower adjacent rate's throughput is measured */
		पूर्ण अन्यथा अगर (low_tpt != IWL_INVALID_VALUE) अणु
			/* Lower rate has better throughput */
			अगर (low_tpt > current_tpt) अणु
				IWL_DEBUG_RATE(priv,
				    "decrease rate because of low tpt\n");
				scale_action = -1;
			पूर्ण अन्यथा अगर (sr >= IWL_RATE_INCREASE_TH) अणु
				scale_action = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Sanity check; asked क्रम decrease, but success rate or throughput
	 * has been good at old rate.  Don't change it. */
	अगर ((scale_action == -1) && (low != IWL_RATE_INVALID) &&
		    ((sr > IWL_RATE_HIGH_TH) ||
		     (current_tpt > (100 * tbl->expected_tpt[low]))))
		scale_action = 0;
	अगर (!iwl_ht_enabled(priv) && !is_legacy(tbl->lq_type))
		scale_action = -1;
	अगर (iwl_tx_ant_restriction(priv) != IWL_ANT_OK_MULTI &&
		(is_mimo2(tbl->lq_type) || is_mimo3(tbl->lq_type)))
		scale_action = -1;

	अगर ((priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH) &&
	     (is_mimo2(tbl->lq_type) || is_mimo3(tbl->lq_type))) अणु
		अगर (lq_sta->last_bt_traffic > priv->bt_traffic_load) अणु
			/*
			 * करोn't set scale_action, don't want to scale up अगर
			 * the rate scale करोesn't otherwise think that is a
			 * good idea.
			 */
		पूर्ण अन्यथा अगर (lq_sta->last_bt_traffic <= priv->bt_traffic_load) अणु
			scale_action = -1;
		पूर्ण
	पूर्ण
	lq_sta->last_bt_traffic = priv->bt_traffic_load;

	अगर ((priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH) &&
	     (is_mimo2(tbl->lq_type) || is_mimo3(tbl->lq_type))) अणु
		/* search क्रम a new modulation */
		rs_stay_in_table(lq_sta, true);
		जाओ lq_update;
	पूर्ण

	चयन (scale_action) अणु
	हाल -1:
		/* Decrease starting rate, update uCode's rate table */
		अगर (low != IWL_RATE_INVALID) अणु
			update_lq = 1;
			index = low;
		पूर्ण

		अवरोध;
	हाल 1:
		/* Increase starting rate, update uCode's rate table */
		अगर (high != IWL_RATE_INVALID) अणु
			update_lq = 1;
			index = high;
		पूर्ण

		अवरोध;
	हाल 0:
		/* No change */
	शेष:
		अवरोध;
	पूर्ण

	IWL_DEBUG_RATE(priv, "choose rate scale index %d action %d low %d "
		    "high %d type %d\n",
		     index, scale_action, low, high, tbl->lq_type);

lq_update:
	/* Replace uCode's rate table क्रम the destination station. */
	अगर (update_lq)
		rs_update_rate_tbl(priv, ctx, lq_sta, tbl, index, is_green);

	अगर (iwl_tx_ant_restriction(priv) == IWL_ANT_OK_MULTI) अणु
		/* Should we stay with this modulation mode,
		 * or search क्रम a new one? */
	  rs_stay_in_table(lq_sta, false);
	पूर्ण
	/*
	 * Search क्रम new modulation mode अगर we're:
	 * 1)  Not changing rates right now
	 * 2)  Not just finishing up a search
	 * 3)  Allowing a new search
	 */
	अगर (!update_lq && !करोne_search && !lq_sta->stay_in_tbl && winकरोw->counter) अणु
		/* Save current throughput to compare with "search" throughput*/
		lq_sta->last_tpt = current_tpt;

		/* Select a new "search" modulation mode to try.
		 * If one is found, set up the new "search" table. */
		अगर (is_legacy(tbl->lq_type))
			rs_move_legacy_other(priv, lq_sta, conf, sta, index);
		अन्यथा अगर (is_siso(tbl->lq_type))
			rs_move_siso_to_other(priv, lq_sta, conf, sta, index);
		अन्यथा अगर (is_mimo2(tbl->lq_type))
			rs_move_mimo2_to_other(priv, lq_sta, conf, sta, index);
		अन्यथा
			rs_move_mimo3_to_other(priv, lq_sta, conf, sta, index);

		/* If new "search" mode was selected, set up in uCode table */
		अगर (lq_sta->search_better_tbl) अणु
			/* Access the "search" table, clear its history. */
			tbl = &(lq_sta->lq_info[(1 - lq_sta->active_tbl)]);
			क्रम (i = 0; i < IWL_RATE_COUNT; i++)
				rs_rate_scale_clear_winकरोw(&(tbl->win[i]));

			/* Use new "search" start rate */
			index = iwl_hwrate_to_plcp_idx(tbl->current_rate);

			IWL_DEBUG_RATE(priv, "Switch current  mcs: %X index: %d\n",
				     tbl->current_rate, index);
			rs_fill_link_cmd(priv, lq_sta, tbl->current_rate);
			iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, CMD_ASYNC, false);
		पूर्ण अन्यथा
			करोne_search = 1;
	पूर्ण

	अगर (करोne_search && !lq_sta->stay_in_tbl) अणु
		/* If the "active" (non-search) mode was legacy,
		 * and we've tried चयनing antennas,
		 * but we haven't been able to try HT modes (not available),
		 * stay with best antenna legacy modulation क्रम a जबतक
		 * beक्रमe next round of mode comparisons. */
		tbl1 = &(lq_sta->lq_info[lq_sta->active_tbl]);
		अगर (is_legacy(tbl1->lq_type) && !conf_is_ht(conf) &&
		    lq_sta->action_counter > tbl1->max_search) अणु
			IWL_DEBUG_RATE(priv, "LQ: STAY in legacy table\n");
			rs_set_stay_in_table(priv, 1, lq_sta);
		पूर्ण

		/* If we're in an HT mode, and all 3 mode चयन actions
		 * have been tried and compared, stay in this best modulation
		 * mode क्रम a जबतक beक्रमe next round of mode comparisons. */
		अगर (lq_sta->enable_counter &&
		    (lq_sta->action_counter >= tbl1->max_search) &&
		    iwl_ht_enabled(priv)) अणु
			अगर ((lq_sta->last_tpt > IWL_AGG_TPT_THREHOLD) &&
			    (lq_sta->tx_agg_tid_en & (1 << tid)) &&
			    (tid != IWL_MAX_TID_COUNT)) अणु
				u8 sta_id = lq_sta->lq.sta_id;
				tid_data = &priv->tid_data[sta_id][tid];
				अगर (tid_data->agg.state == IWL_AGG_OFF) अणु
					IWL_DEBUG_RATE(priv,
						       "try to aggregate tid %d\n",
						       tid);
					rs_tl_turn_on_agg(priv, tid,
							  lq_sta, sta);
				पूर्ण
			पूर्ण
			rs_set_stay_in_table(priv, 0, lq_sta);
		पूर्ण
	पूर्ण

out:
	tbl->current_rate = rate_n_flags_from_tbl(priv, tbl, index, is_green);
	lq_sta->last_txrate_idx = index;
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
अटल व्योम rs_initialize_lq(काष्ठा iwl_priv *priv,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा iwl_lq_sta *lq_sta)
अणु
	काष्ठा iwl_scale_tbl_info *tbl;
	पूर्णांक rate_idx;
	पूर्णांक i;
	u32 rate;
	u8 use_green = rs_use_green(sta);
	u8 active_tbl = 0;
	u8 valid_tx_ant;
	काष्ठा iwl_station_priv *sta_priv;
	काष्ठा iwl_rxon_context *ctx;

	अगर (!sta || !lq_sta)
		वापस;

	sta_priv = (व्योम *)sta->drv_priv;
	ctx = sta_priv->ctx;

	i = lq_sta->last_txrate_idx;

	valid_tx_ant = priv->nvm_data->valid_tx_ant;

	अगर (!lq_sta->search_better_tbl)
		active_tbl = lq_sta->active_tbl;
	अन्यथा
		active_tbl = 1 - lq_sta->active_tbl;

	tbl = &(lq_sta->lq_info[active_tbl]);

	अगर ((i < 0) || (i >= IWL_RATE_COUNT))
		i = 0;

	rate = iwl_rates[i].plcp;
	tbl->ant_type = first_antenna(valid_tx_ant);
	rate |= tbl->ant_type << RATE_MCS_ANT_POS;

	अगर (i >= IWL_FIRST_CCK_RATE && i <= IWL_LAST_CCK_RATE)
		rate |= RATE_MCS_CCK_MSK;

	rs_get_tbl_info_from_mcs(rate, priv->band, tbl, &rate_idx);
	अगर (!rs_is_valid_ant(valid_tx_ant, tbl->ant_type))
	    rs_toggle_antenna(valid_tx_ant, &rate, tbl);

	rate = rate_n_flags_from_tbl(priv, tbl, rate_idx, use_green);
	tbl->current_rate = rate;
	rs_set_expected_tpt_table(lq_sta, tbl);
	rs_fill_link_cmd(शून्य, lq_sta, rate);
	priv->stations[lq_sta->lq.sta_id].lq = &lq_sta->lq;
	iwl_send_lq_cmd(priv, ctx, &lq_sta->lq, 0, true);
पूर्ण

अटल व्योम rs_get_rate(व्योम *priv_r, काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
			काष्ठा ieee80211_tx_rate_control *txrc)
अणु

	काष्ठा sk_buff *skb = txrc->skb;
	काष्ठा ieee80211_supported_band *sband = txrc->sband;
	काष्ठा iwl_op_mode *op_mode __maybe_unused =
			(काष्ठा iwl_op_mode *)priv_r;
	काष्ठा iwl_priv *priv __maybe_unused = IWL_OP_MODE_GET_DVM(op_mode);
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा iwl_lq_sta *lq_sta = priv_sta;
	पूर्णांक rate_idx;

	IWL_DEBUG_RATE_LIMIT(priv, "rate scale calculate new rate for skb\n");

	/* Get max rate अगर user set max rate */
	अगर (lq_sta) अणु
		lq_sta->max_rate_idx = fls(txrc->rate_idx_mask) - 1;
		अगर ((sband->band == NL80211_BAND_5GHZ) &&
		    (lq_sta->max_rate_idx != -1))
			lq_sta->max_rate_idx += IWL_FIRST_OFDM_RATE;
		अगर ((lq_sta->max_rate_idx < 0) ||
		    (lq_sta->max_rate_idx >= IWL_RATE_COUNT))
			lq_sta->max_rate_idx = -1;
	पूर्ण

	/* Treat uninitialized rate scaling data same as non-existing. */
	अगर (lq_sta && !lq_sta->drv) अणु
		IWL_DEBUG_RATE(priv, "Rate scaling not initialized yet.\n");
		priv_sta = शून्य;
	पूर्ण

	rate_idx  = lq_sta->last_txrate_idx;

	अगर (lq_sta->last_rate_n_flags & RATE_MCS_HT_MSK) अणु
		rate_idx -= IWL_FIRST_OFDM_RATE;
		/* 6M and 9M shared same MCS index */
		rate_idx = (rate_idx > 0) ? (rate_idx - 1) : 0;
		अगर (rs_extract_rate(lq_sta->last_rate_n_flags) >=
		    IWL_RATE_MIMO3_6M_PLCP)
			rate_idx = rate_idx + (2 * MCS_INDEX_PER_STREAM);
		अन्यथा अगर (rs_extract_rate(lq_sta->last_rate_n_flags) >=
			 IWL_RATE_MIMO2_6M_PLCP)
			rate_idx = rate_idx + MCS_INDEX_PER_STREAM;
		info->control.rates[0].flags = IEEE80211_TX_RC_MCS;
		अगर (lq_sta->last_rate_n_flags & RATE_MCS_SGI_MSK)
			info->control.rates[0].flags |= IEEE80211_TX_RC_SHORT_GI;
		अगर (lq_sta->last_rate_n_flags & RATE_MCS_DUP_MSK)
			info->control.rates[0].flags |= IEEE80211_TX_RC_DUP_DATA;
		अगर (lq_sta->last_rate_n_flags & RATE_MCS_HT40_MSK)
			info->control.rates[0].flags |= IEEE80211_TX_RC_40_MHZ_WIDTH;
		अगर (lq_sta->last_rate_n_flags & RATE_MCS_GF_MSK)
			info->control.rates[0].flags |= IEEE80211_TX_RC_GREEN_FIELD;
	पूर्ण अन्यथा अणु
		/* Check क्रम invalid rates */
		अगर ((rate_idx < 0) || (rate_idx >= IWL_RATE_COUNT_LEGACY) ||
				((sband->band == NL80211_BAND_5GHZ) &&
				 (rate_idx < IWL_FIRST_OFDM_RATE)))
			rate_idx = rate_lowest_index(sband, sta);
		/* On valid 5 GHz rate, adjust index */
		अन्यथा अगर (sband->band == NL80211_BAND_5GHZ)
			rate_idx -= IWL_FIRST_OFDM_RATE;
		info->control.rates[0].flags = 0;
	पूर्ण
	info->control.rates[0].idx = rate_idx;
	info->control.rates[0].count = 1;
पूर्ण

अटल व्योम *rs_alloc_sta(व्योम *priv_rate, काष्ठा ieee80211_sta *sta,
			  gfp_t gfp)
अणु
	काष्ठा iwl_station_priv *sta_priv = (काष्ठा iwl_station_priv *) sta->drv_priv;
	काष्ठा iwl_op_mode *op_mode __maybe_unused =
			(काष्ठा iwl_op_mode *)priv_rate;
	काष्ठा iwl_priv *priv __maybe_unused = IWL_OP_MODE_GET_DVM(op_mode);

	IWL_DEBUG_RATE(priv, "create station rate scale window\n");

	वापस &sta_priv->lq_sta;
पूर्ण

/*
 * Called after adding a new station to initialize rate scaling
 */
व्योम iwl_rs_rate_init(काष्ठा iwl_priv *priv, काष्ठा ieee80211_sta *sta, u8 sta_id)
अणु
	पूर्णांक i, j;
	काष्ठा ieee80211_hw *hw = priv->hw;
	काष्ठा ieee80211_conf *conf = &priv->hw->conf;
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	काष्ठा iwl_station_priv *sta_priv;
	काष्ठा iwl_lq_sta *lq_sta;
	काष्ठा ieee80211_supported_band *sband;
	अचिन्हित दीर्घ supp; /* must be अचिन्हित दीर्घ क्रम क्रम_each_set_bit */

	sta_priv = (काष्ठा iwl_station_priv *) sta->drv_priv;
	lq_sta = &sta_priv->lq_sta;
	sband = hw->wiphy->bands[conf->chandef.chan->band];


	lq_sta->lq.sta_id = sta_id;

	क्रम (j = 0; j < LQ_SIZE; j++)
		क्रम (i = 0; i < IWL_RATE_COUNT; i++)
			rs_rate_scale_clear_winकरोw(&lq_sta->lq_info[j].win[i]);

	lq_sta->flush_समयr = 0;
	lq_sta->supp_rates = sta->supp_rates[sband->band];

	IWL_DEBUG_RATE(priv, "LQ: *** rate scale station global init for station %d ***\n",
		       sta_id);
	/* TODO: what is a good starting rate क्रम STA? About middle? Maybe not
	 * the lowest or the highest rate.. Could consider using RSSI from
	 * previous packets? Need to have IEEE 802.1X auth succeed immediately
	 * after assoc.. */

	lq_sta->is_dup = 0;
	lq_sta->max_rate_idx = -1;
	lq_sta->missed_rate_counter = IWL_MISSED_RATE_MAX;
	lq_sta->is_green = rs_use_green(sta);
	lq_sta->band = sband->band;
	/*
	 * active legacy rates as per supported rates biपंचांगap
	 */
	supp = sta->supp_rates[sband->band];
	lq_sta->active_legacy_rate = 0;
	क्रम_each_set_bit(i, &supp, BITS_PER_LONG)
		lq_sta->active_legacy_rate |= BIT(sband->bitrates[i].hw_value);

	/*
	 * active_siso_rate mask includes 9 MBits (bit 5), and CCK (bits 0-3),
	 * supp_rates[] करोes not; shअगरt to convert क्रमmat, क्रमce 9 MBits off.
	 */
	lq_sta->active_siso_rate = ht_cap->mcs.rx_mask[0] << 1;
	lq_sta->active_siso_rate |= ht_cap->mcs.rx_mask[0] & 0x1;
	lq_sta->active_siso_rate &= ~((u16)0x2);
	lq_sta->active_siso_rate <<= IWL_FIRST_OFDM_RATE;

	/* Same here */
	lq_sta->active_mimo2_rate = ht_cap->mcs.rx_mask[1] << 1;
	lq_sta->active_mimo2_rate |= ht_cap->mcs.rx_mask[1] & 0x1;
	lq_sta->active_mimo2_rate &= ~((u16)0x2);
	lq_sta->active_mimo2_rate <<= IWL_FIRST_OFDM_RATE;

	lq_sta->active_mimo3_rate = ht_cap->mcs.rx_mask[2] << 1;
	lq_sta->active_mimo3_rate |= ht_cap->mcs.rx_mask[2] & 0x1;
	lq_sta->active_mimo3_rate &= ~((u16)0x2);
	lq_sta->active_mimo3_rate <<= IWL_FIRST_OFDM_RATE;

	IWL_DEBUG_RATE(priv, "SISO-RATE=%X MIMO2-RATE=%X MIMO3-RATE=%X\n",
		     lq_sta->active_siso_rate,
		     lq_sta->active_mimo2_rate,
		     lq_sta->active_mimo3_rate);

	/* These values will be overridden later */
	lq_sta->lq.general_params.single_stream_ant_msk =
		first_antenna(priv->nvm_data->valid_tx_ant);
	lq_sta->lq.general_params.dual_stream_ant_msk =
		priv->nvm_data->valid_tx_ant &
		~first_antenna(priv->nvm_data->valid_tx_ant);
	अगर (!lq_sta->lq.general_params.dual_stream_ant_msk) अणु
		lq_sta->lq.general_params.dual_stream_ant_msk = ANT_AB;
	पूर्ण अन्यथा अगर (num_of_ant(priv->nvm_data->valid_tx_ant) == 2) अणु
		lq_sta->lq.general_params.dual_stream_ant_msk =
			priv->nvm_data->valid_tx_ant;
	पूर्ण

	/* as शेष allow aggregation क्रम all tids */
	lq_sta->tx_agg_tid_en = IWL_AGG_ALL_TID;
	lq_sta->drv = priv;

	/* Set last_txrate_idx to lowest rate */
	lq_sta->last_txrate_idx = rate_lowest_index(sband, sta);
	अगर (sband->band == NL80211_BAND_5GHZ)
		lq_sta->last_txrate_idx += IWL_FIRST_OFDM_RATE;
	lq_sta->is_agg = 0;
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	lq_sta->dbg_fixed_rate = 0;
#पूर्ण_अगर

	rs_initialize_lq(priv, sta, lq_sta);
पूर्ण

अटल व्योम rs_fill_link_cmd(काष्ठा iwl_priv *priv,
			     काष्ठा iwl_lq_sta *lq_sta, u32 new_rate)
अणु
	काष्ठा iwl_scale_tbl_info tbl_type;
	पूर्णांक index = 0;
	पूर्णांक rate_idx;
	पूर्णांक repeat_rate = 0;
	u8 ant_toggle_cnt = 0;
	u8 use_ht_possible = 1;
	u8 valid_tx_ant = 0;
	काष्ठा iwl_station_priv *sta_priv =
		container_of(lq_sta, काष्ठा iwl_station_priv, lq_sta);
	काष्ठा iwl_link_quality_cmd *lq_cmd = &lq_sta->lq;

	/* Override starting rate (index 0) अगर needed क्रम debug purposes */
	rs_dbgfs_set_mcs(lq_sta, &new_rate, index);

	/* Interpret new_rate (rate_n_flags) */
	rs_get_tbl_info_from_mcs(new_rate, lq_sta->band,
				  &tbl_type, &rate_idx);

	अगर (priv && priv->bt_full_concurrent) अणु
		/* 1x1 only */
		tbl_type.ant_type =
			first_antenna(priv->nvm_data->valid_tx_ant);
	पूर्ण

	/* How many बार should we repeat the initial rate? */
	अगर (is_legacy(tbl_type.lq_type)) अणु
		ant_toggle_cnt = 1;
		repeat_rate = IWL_NUMBER_TRY;
	पूर्ण अन्यथा अणु
		repeat_rate = min(IWL_HT_NUMBER_TRY,
				  LINK_QUAL_AGG_DISABLE_START_DEF - 1);
	पूर्ण

	lq_cmd->general_params.mimo_delimiter =
			is_mimo(tbl_type.lq_type) ? 1 : 0;

	/* Fill 1st table entry (index 0) */
	lq_cmd->rs_table[index].rate_n_flags = cpu_to_le32(new_rate);

	अगर (num_of_ant(tbl_type.ant_type) == 1) अणु
		lq_cmd->general_params.single_stream_ant_msk =
						tbl_type.ant_type;
	पूर्ण अन्यथा अगर (num_of_ant(tbl_type.ant_type) == 2) अणु
		lq_cmd->general_params.dual_stream_ant_msk =
						tbl_type.ant_type;
	पूर्ण /* otherwise we करोn't modअगरy the existing value */

	index++;
	repeat_rate--;
	अगर (priv) अणु
		अगर (priv->bt_full_concurrent)
			valid_tx_ant = ANT_A;
		अन्यथा
			valid_tx_ant = priv->nvm_data->valid_tx_ant;
	पूर्ण

	/* Fill rest of rate table */
	जबतक (index < LINK_QUAL_MAX_RETRY_NUM) अणु
		/* Repeat initial/next rate.
		 * For legacy IWL_NUMBER_TRY == 1, this loop will not execute.
		 * For HT IWL_HT_NUMBER_TRY == 3, this executes twice. */
		जबतक (repeat_rate > 0 && (index < LINK_QUAL_MAX_RETRY_NUM)) अणु
			अगर (is_legacy(tbl_type.lq_type)) अणु
				अगर (ant_toggle_cnt < NUM_TRY_BEFORE_ANT_TOGGLE)
					ant_toggle_cnt++;
				अन्यथा अगर (priv &&
					 rs_toggle_antenna(valid_tx_ant,
							&new_rate, &tbl_type))
					ant_toggle_cnt = 1;
			पूर्ण

			/* Override next rate अगर needed क्रम debug purposes */
			rs_dbgfs_set_mcs(lq_sta, &new_rate, index);

			/* Fill next table entry */
			lq_cmd->rs_table[index].rate_n_flags =
					cpu_to_le32(new_rate);
			repeat_rate--;
			index++;
		पूर्ण

		rs_get_tbl_info_from_mcs(new_rate, lq_sta->band, &tbl_type,
						&rate_idx);

		अगर (priv && priv->bt_full_concurrent) अणु
			/* 1x1 only */
			tbl_type.ant_type =
			    first_antenna(priv->nvm_data->valid_tx_ant);
		पूर्ण

		/* Indicate to uCode which entries might be MIMO.
		 * If initial rate was MIMO, this will finally end up
		 * as (IWL_HT_NUMBER_TRY * 2), after 2nd pass, otherwise 0. */
		अगर (is_mimo(tbl_type.lq_type))
			lq_cmd->general_params.mimo_delimiter = index;

		/* Get next rate */
		new_rate = rs_get_lower_rate(lq_sta, &tbl_type, rate_idx,
					     use_ht_possible);

		/* How many बार should we repeat the next rate? */
		अगर (is_legacy(tbl_type.lq_type)) अणु
			अगर (ant_toggle_cnt < NUM_TRY_BEFORE_ANT_TOGGLE)
				ant_toggle_cnt++;
			अन्यथा अगर (priv &&
				 rs_toggle_antenna(valid_tx_ant,
						   &new_rate, &tbl_type))
				ant_toggle_cnt = 1;

			repeat_rate = IWL_NUMBER_TRY;
		पूर्ण अन्यथा अणु
			repeat_rate = IWL_HT_NUMBER_TRY;
		पूर्ण

		/* Don't allow HT rates after next pass.
		 * rs_get_lower_rate() will change type to LQ_A or LQ_G. */
		use_ht_possible = 0;

		/* Override next rate अगर needed क्रम debug purposes */
		rs_dbgfs_set_mcs(lq_sta, &new_rate, index);

		/* Fill next table entry */
		lq_cmd->rs_table[index].rate_n_flags = cpu_to_le32(new_rate);

		index++;
		repeat_rate--;
	पूर्ण

	lq_cmd->agg_params.agg_frame_cnt_limit =
		sta_priv->max_agg_bufsize ?: LINK_QUAL_AGG_FRAME_LIMIT_DEF;
	lq_cmd->agg_params.agg_dis_start_th = LINK_QUAL_AGG_DISABLE_START_DEF;

	lq_cmd->agg_params.agg_समय_limit =
		cpu_to_le16(LINK_QUAL_AGG_TIME_LIMIT_DEF);
	/*
	 * overग_लिखो अगर needed, pass aggregation समय limit
	 * to uCode in uSec
	 */
	अगर (priv && priv->lib->bt_params &&
	    priv->lib->bt_params->agg_समय_limit &&
	    priv->bt_traffic_load >= IWL_BT_COEX_TRAFFIC_LOAD_HIGH)
		lq_cmd->agg_params.agg_समय_limit =
			cpu_to_le16(priv->lib->bt_params->agg_समय_limit);
पूर्ण

अटल व्योम *rs_alloc(काष्ठा ieee80211_hw *hw)
अणु
	वापस hw->priv;
पूर्ण
/* rate scale requires मुक्त function to be implemented */
अटल व्योम rs_मुक्त(व्योम *priv_rate)
अणु
	वापस;
पूर्ण

अटल व्योम rs_मुक्त_sta(व्योम *priv_r, काष्ठा ieee80211_sta *sta,
			व्योम *priv_sta)
अणु
	काष्ठा iwl_op_mode *op_mode __maybe_unused = priv_r;
	काष्ठा iwl_priv *priv __maybe_unused = IWL_OP_MODE_GET_DVM(op_mode);

	IWL_DEBUG_RATE(priv, "enter\n");
	IWL_DEBUG_RATE(priv, "leave\n");
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
अटल व्योम rs_dbgfs_set_mcs(काष्ठा iwl_lq_sta *lq_sta,
			     u32 *rate_n_flags, पूर्णांक index)
अणु
	काष्ठा iwl_priv *priv;
	u8 valid_tx_ant;
	u8 ant_sel_tx;

	priv = lq_sta->drv;
	valid_tx_ant = priv->nvm_data->valid_tx_ant;
	अगर (lq_sta->dbg_fixed_rate) अणु
		ant_sel_tx =
		  ((lq_sta->dbg_fixed_rate & RATE_MCS_ANT_ABC_MSK)
		  >> RATE_MCS_ANT_POS);
		अगर ((valid_tx_ant & ant_sel_tx) == ant_sel_tx) अणु
			*rate_n_flags = lq_sta->dbg_fixed_rate;
			IWL_DEBUG_RATE(priv, "Fixed rate ON\n");
		पूर्ण अन्यथा अणु
			lq_sta->dbg_fixed_rate = 0;
			IWL_ERR(priv,
			    "Invalid antenna selection 0x%X, Valid is 0x%X\n",
			    ant_sel_tx, valid_tx_ant);
			IWL_DEBUG_RATE(priv, "Fixed rate OFF\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		IWL_DEBUG_RATE(priv, "Fixed rate OFF\n");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार rs_sta_dbgfs_scale_table_ग_लिखो(काष्ठा file *file,
			स्थिर अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	काष्ठा iwl_priv *priv;
	अक्षर buf[64];
	माप_प्रकार buf_size;
	u32 parsed_rate;


	priv = lq_sta->drv;
	स_रखो(buf, 0, माप(buf));
	buf_size = min(count, माप(buf) -  1);
	अगर (copy_from_user(buf, user_buf, buf_size))
		वापस -EFAULT;

	अगर (माला_पूछो(buf, "%x", &parsed_rate) == 1)
		lq_sta->dbg_fixed_rate = parsed_rate;
	अन्यथा
		lq_sta->dbg_fixed_rate = 0;

	rs_program_fix_rate(priv, lq_sta);

	वापस count;
पूर्ण

अटल sमाप_प्रकार rs_sta_dbgfs_scale_table_पढ़ो(काष्ठा file *file,
			अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buff;
	पूर्णांक desc = 0;
	पूर्णांक i = 0;
	पूर्णांक index = 0;
	sमाप_प्रकार ret;

	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	काष्ठा iwl_priv *priv;
	काष्ठा iwl_scale_tbl_info *tbl = &(lq_sta->lq_info[lq_sta->active_tbl]);

	priv = lq_sta->drv;
	buff = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	desc += प्र_लिखो(buff+desc, "sta_id %d\n", lq_sta->lq.sta_id);
	desc += प्र_लिखो(buff+desc, "failed=%d success=%d rate=0%X\n",
			lq_sta->total_failed, lq_sta->total_success,
			lq_sta->active_legacy_rate);
	desc += प्र_लिखो(buff+desc, "fixed rate 0x%X\n",
			lq_sta->dbg_fixed_rate);
	desc += प्र_लिखो(buff+desc, "valid_tx_ant %s%s%s\n",
	    (priv->nvm_data->valid_tx_ant & ANT_A) ? "ANT_A," : "",
	    (priv->nvm_data->valid_tx_ant & ANT_B) ? "ANT_B," : "",
	    (priv->nvm_data->valid_tx_ant & ANT_C) ? "ANT_C" : "");
	desc += प्र_लिखो(buff+desc, "lq type %s\n",
	   (is_legacy(tbl->lq_type)) ? "legacy" : "HT");
	अगर (is_Ht(tbl->lq_type)) अणु
		desc += प्र_लिखो(buff + desc, " %s",
		   (is_siso(tbl->lq_type)) ? "SISO" :
		   ((is_mimo2(tbl->lq_type)) ? "MIMO2" : "MIMO3"));
		desc += प्र_लिखो(buff + desc, " %s",
		   (tbl->is_ht40) ? "40MHz" : "20MHz");
		desc += प्र_लिखो(buff + desc, " %s %s %s\n",
		   (tbl->is_SGI) ? "SGI" : "",
		   (lq_sta->is_green) ? "GF enabled" : "",
		   (lq_sta->is_agg) ? "AGG on" : "");
	पूर्ण
	desc += प्र_लिखो(buff+desc, "last tx rate=0x%X\n",
		lq_sta->last_rate_n_flags);
	desc += प्र_लिखो(buff+desc, "general:"
		"flags=0x%X mimo-d=%d s-ant0x%x d-ant=0x%x\n",
		lq_sta->lq.general_params.flags,
		lq_sta->lq.general_params.mimo_delimiter,
		lq_sta->lq.general_params.single_stream_ant_msk,
		lq_sta->lq.general_params.dual_stream_ant_msk);

	desc += प्र_लिखो(buff+desc, "agg:"
			"time_limit=%d dist_start_th=%d frame_cnt_limit=%d\n",
			le16_to_cpu(lq_sta->lq.agg_params.agg_समय_limit),
			lq_sta->lq.agg_params.agg_dis_start_th,
			lq_sta->lq.agg_params.agg_frame_cnt_limit);

	desc += प्र_लिखो(buff+desc,
			"Start idx [0]=0x%x [1]=0x%x [2]=0x%x [3]=0x%x\n",
			lq_sta->lq.general_params.start_rate_index[0],
			lq_sta->lq.general_params.start_rate_index[1],
			lq_sta->lq.general_params.start_rate_index[2],
			lq_sta->lq.general_params.start_rate_index[3]);

	क्रम (i = 0; i < LINK_QUAL_MAX_RETRY_NUM; i++) अणु
		index = iwl_hwrate_to_plcp_idx(
			le32_to_cpu(lq_sta->lq.rs_table[i].rate_n_flags));
		अगर (is_legacy(tbl->lq_type)) अणु
			desc += प्र_लिखो(buff+desc, " rate[%d] 0x%X %smbps\n",
				i, le32_to_cpu(lq_sta->lq.rs_table[i].rate_n_flags),
				iwl_rate_mcs[index].mbps);
		पूर्ण अन्यथा अणु
			desc += प्र_लिखो(buff+desc, " rate[%d] 0x%X %smbps (%s)\n",
				i, le32_to_cpu(lq_sta->lq.rs_table[i].rate_n_flags),
				iwl_rate_mcs[index].mbps, iwl_rate_mcs[index].mcs);
		पूर्ण
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

	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;

	buff = kदो_स्मृति(1024, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	क्रम (i = 0; i < LQ_SIZE; i++) अणु
		desc += प्र_लिखो(buff+desc,
				"%s type=%d SGI=%d HT40=%d DUP=%d GF=%d\n"
				"rate=0x%X\n",
				lq_sta->active_tbl == i ? "*" : "x",
				lq_sta->lq_info[i].lq_type,
				lq_sta->lq_info[i].is_SGI,
				lq_sta->lq_info[i].is_ht40,
				lq_sta->lq_info[i].is_dup,
				lq_sta->is_green,
				lq_sta->lq_info[i].current_rate);
		क्रम (j = 0; j < IWL_RATE_COUNT; j++) अणु
			desc += प्र_लिखो(buff+desc,
				"counter=%d success=%d %%=%d\n",
				lq_sta->lq_info[i].win[j].counter,
				lq_sta->lq_info[i].win[j].success_counter,
				lq_sta->lq_info[i].win[j].success_ratio);
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

अटल sमाप_प्रकार rs_sta_dbgfs_rate_scale_data_पढ़ो(काष्ठा file *file,
			अक्षर __user *user_buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा iwl_lq_sta *lq_sta = file->निजी_data;
	काष्ठा iwl_scale_tbl_info *tbl = &lq_sta->lq_info[lq_sta->active_tbl];
	अक्षर buff[120];
	पूर्णांक desc = 0;

	अगर (is_Ht(tbl->lq_type))
		desc += प्र_लिखो(buff+desc,
				"Bit Rate= %d Mb/s\n",
				tbl->expected_tpt[lq_sta->last_txrate_idx]);
	अन्यथा
		desc += प्र_लिखो(buff+desc,
				"Bit Rate= %d Mb/s\n",
				iwl_rates[lq_sta->last_txrate_idx].ieee >> 1);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buff, desc);
पूर्ण

अटल स्थिर काष्ठा file_operations rs_sta_dbgfs_rate_scale_data_ops = अणु
	.पढ़ो = rs_sta_dbgfs_rate_scale_data_पढ़ो,
	.खोलो = simple_खोलो,
	.llseek = शेष_llseek,
पूर्ण;

अटल व्योम rs_add_debugfs(व्योम *priv, व्योम *priv_sta,
					काष्ठा dentry *dir)
अणु
	काष्ठा iwl_lq_sta *lq_sta = priv_sta;

	debugfs_create_file("rate_scale_table", 0600, dir, lq_sta,
			    &rs_sta_dbgfs_scale_table_ops);
	debugfs_create_file("rate_stats_table", 0400, dir, lq_sta,
			    &rs_sta_dbgfs_stats_table_ops);
	debugfs_create_file("rate_scale_data", 0400, dir, lq_sta,
			    &rs_sta_dbgfs_rate_scale_data_ops);
	debugfs_create_u8("tx_agg_tid_enable", 0600, dir,
			  &lq_sta->tx_agg_tid_en);

पूर्ण
#पूर्ण_अगर

/*
 * Initialization of rate scaling inक्रमmation is करोne by driver after
 * the station is added. Since mac80211 calls this function beक्रमe a
 * station is added we ignore it.
 */
अटल व्योम rs_rate_init_stub(व्योम *priv_r, काष्ठा ieee80211_supported_band *sband,
			      काष्ठा cfg80211_chan_def *chandef,
			      काष्ठा ieee80211_sta *sta, व्योम *priv_sta)
अणु
पूर्ण

अटल स्थिर काष्ठा rate_control_ops rs_ops = अणु
	.name = RS_NAME,
	.tx_status = rs_tx_status,
	.get_rate = rs_get_rate,
	.rate_init = rs_rate_init_stub,
	.alloc = rs_alloc,
	.मुक्त = rs_मुक्त,
	.alloc_sta = rs_alloc_sta,
	.मुक्त_sta = rs_मुक्त_sta,
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	.add_sta_debugfs = rs_add_debugfs,
#पूर्ण_अगर
पूर्ण;

पूर्णांक iwlagn_rate_control_रेजिस्टर(व्योम)
अणु
	वापस ieee80211_rate_control_रेजिस्टर(&rs_ops);
पूर्ण

व्योम iwlagn_rate_control_unरेजिस्टर(व्योम)
अणु
	ieee80211_rate_control_unरेजिस्टर(&rs_ops);
पूर्ण

