<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2015 Intel Mobile Communications GmbH
 * Copyright(c) 2017 Intel Deutschland GmbH
 * Copyright(c) 2018 - 2019 Intel Corporation
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#अगर_अघोषित __rs_h__
#घोषणा __rs_h__

#समावेश <net/mac80211.h>

#समावेश "iwl-config.h"

#समावेश "fw-api.h"
#समावेश "iwl-trans.h"

#घोषणा RS_NAME "iwl-mvm-rs"

काष्ठा iwl_rs_rate_info अणु
	u8 plcp;	  /* uCode API:  IWL_RATE_6M_PLCP, etc. */
	u8 plcp_ht_siso;  /* uCode API:  IWL_RATE_SISO_6M_PLCP, etc. */
	u8 plcp_ht_mimo2; /* uCode API:  IWL_RATE_MIMO2_6M_PLCP, etc. */
	u8 plcp_vht_siso;
	u8 plcp_vht_mimo2;
	u8 prev_rs;      /* previous rate used in rs algo */
	u8 next_rs;      /* next rate used in rs algo */
पूर्ण;

#घोषणा IWL_RATE_60M_PLCP 3

क्रमागत अणु
	IWL_RATE_INVM_INDEX = IWL_RATE_COUNT,
	IWL_RATE_INVALID = IWL_RATE_COUNT,
पूर्ण;

#घोषणा LINK_QUAL_MAX_RETRY_NUM 16

क्रमागत अणु
	IWL_RATE_6M_INDEX_TABLE = 0,
	IWL_RATE_9M_INDEX_TABLE,
	IWL_RATE_12M_INDEX_TABLE,
	IWL_RATE_18M_INDEX_TABLE,
	IWL_RATE_24M_INDEX_TABLE,
	IWL_RATE_36M_INDEX_TABLE,
	IWL_RATE_48M_INDEX_TABLE,
	IWL_RATE_54M_INDEX_TABLE,
	IWL_RATE_1M_INDEX_TABLE,
	IWL_RATE_2M_INDEX_TABLE,
	IWL_RATE_5M_INDEX_TABLE,
	IWL_RATE_11M_INDEX_TABLE,
	IWL_RATE_INVM_INDEX_TABLE = IWL_RATE_INVM_INDEX - 1,
पूर्ण;

/* #घोषणा vs. क्रमागत to keep from शेषing to 'large integer' */
#घोषणा	IWL_RATE_6M_MASK   (1 << IWL_RATE_6M_INDEX)
#घोषणा	IWL_RATE_9M_MASK   (1 << IWL_RATE_9M_INDEX)
#घोषणा	IWL_RATE_12M_MASK  (1 << IWL_RATE_12M_INDEX)
#घोषणा	IWL_RATE_18M_MASK  (1 << IWL_RATE_18M_INDEX)
#घोषणा	IWL_RATE_24M_MASK  (1 << IWL_RATE_24M_INDEX)
#घोषणा	IWL_RATE_36M_MASK  (1 << IWL_RATE_36M_INDEX)
#घोषणा	IWL_RATE_48M_MASK  (1 << IWL_RATE_48M_INDEX)
#घोषणा	IWL_RATE_54M_MASK  (1 << IWL_RATE_54M_INDEX)
#घोषणा IWL_RATE_60M_MASK  (1 << IWL_RATE_60M_INDEX)
#घोषणा	IWL_RATE_1M_MASK   (1 << IWL_RATE_1M_INDEX)
#घोषणा	IWL_RATE_2M_MASK   (1 << IWL_RATE_2M_INDEX)
#घोषणा	IWL_RATE_5M_MASK   (1 << IWL_RATE_5M_INDEX)
#घोषणा	IWL_RATE_11M_MASK  (1 << IWL_RATE_11M_INDEX)


/* uCode API values क्रम HT/VHT bit rates */
क्रमागत अणु
	IWL_RATE_HT_SISO_MCS_0_PLCP = 0,
	IWL_RATE_HT_SISO_MCS_1_PLCP = 1,
	IWL_RATE_HT_SISO_MCS_2_PLCP = 2,
	IWL_RATE_HT_SISO_MCS_3_PLCP = 3,
	IWL_RATE_HT_SISO_MCS_4_PLCP = 4,
	IWL_RATE_HT_SISO_MCS_5_PLCP = 5,
	IWL_RATE_HT_SISO_MCS_6_PLCP = 6,
	IWL_RATE_HT_SISO_MCS_7_PLCP = 7,
	IWL_RATE_HT_MIMO2_MCS_0_PLCP = 0x8,
	IWL_RATE_HT_MIMO2_MCS_1_PLCP = 0x9,
	IWL_RATE_HT_MIMO2_MCS_2_PLCP = 0xA,
	IWL_RATE_HT_MIMO2_MCS_3_PLCP = 0xB,
	IWL_RATE_HT_MIMO2_MCS_4_PLCP = 0xC,
	IWL_RATE_HT_MIMO2_MCS_5_PLCP = 0xD,
	IWL_RATE_HT_MIMO2_MCS_6_PLCP = 0xE,
	IWL_RATE_HT_MIMO2_MCS_7_PLCP = 0xF,
	IWL_RATE_VHT_SISO_MCS_0_PLCP = 0,
	IWL_RATE_VHT_SISO_MCS_1_PLCP = 1,
	IWL_RATE_VHT_SISO_MCS_2_PLCP = 2,
	IWL_RATE_VHT_SISO_MCS_3_PLCP = 3,
	IWL_RATE_VHT_SISO_MCS_4_PLCP = 4,
	IWL_RATE_VHT_SISO_MCS_5_PLCP = 5,
	IWL_RATE_VHT_SISO_MCS_6_PLCP = 6,
	IWL_RATE_VHT_SISO_MCS_7_PLCP = 7,
	IWL_RATE_VHT_SISO_MCS_8_PLCP = 8,
	IWL_RATE_VHT_SISO_MCS_9_PLCP = 9,
	IWL_RATE_VHT_MIMO2_MCS_0_PLCP = 0x10,
	IWL_RATE_VHT_MIMO2_MCS_1_PLCP = 0x11,
	IWL_RATE_VHT_MIMO2_MCS_2_PLCP = 0x12,
	IWL_RATE_VHT_MIMO2_MCS_3_PLCP = 0x13,
	IWL_RATE_VHT_MIMO2_MCS_4_PLCP = 0x14,
	IWL_RATE_VHT_MIMO2_MCS_5_PLCP = 0x15,
	IWL_RATE_VHT_MIMO2_MCS_6_PLCP = 0x16,
	IWL_RATE_VHT_MIMO2_MCS_7_PLCP = 0x17,
	IWL_RATE_VHT_MIMO2_MCS_8_PLCP = 0x18,
	IWL_RATE_VHT_MIMO2_MCS_9_PLCP = 0x19,
	IWL_RATE_HT_SISO_MCS_INV_PLCP,
	IWL_RATE_HT_MIMO2_MCS_INV_PLCP = IWL_RATE_HT_SISO_MCS_INV_PLCP,
	IWL_RATE_VHT_SISO_MCS_INV_PLCP = IWL_RATE_HT_SISO_MCS_INV_PLCP,
	IWL_RATE_VHT_MIMO2_MCS_INV_PLCP = IWL_RATE_HT_SISO_MCS_INV_PLCP,
	IWL_RATE_HT_SISO_MCS_8_PLCP = IWL_RATE_HT_SISO_MCS_INV_PLCP,
	IWL_RATE_HT_SISO_MCS_9_PLCP = IWL_RATE_HT_SISO_MCS_INV_PLCP,
	IWL_RATE_HT_MIMO2_MCS_8_PLCP = IWL_RATE_HT_SISO_MCS_INV_PLCP,
	IWL_RATE_HT_MIMO2_MCS_9_PLCP = IWL_RATE_HT_SISO_MCS_INV_PLCP,
पूर्ण;

#घोषणा IWL_RATES_MASK ((1 << IWL_RATE_COUNT) - 1)

#घोषणा IWL_INVALID_VALUE    -1

#घोषणा TPC_MAX_REDUCTION		15
#घोषणा TPC_NO_REDUCTION		0
#घोषणा TPC_INVALID			0xff

#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_DEF	(63)
#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_MAX	(63)
/*
 * FIXME - various places in firmware API still use u8,
 * e.g. LQ command and SCD config command.
 * This should be 256 instead.
 */
#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_GEN2_DEF	(255)
#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_GEN2_MAX	(255)
#घोषणा LINK_QUAL_AGG_FRAME_LIMIT_MIN	(0)

#घोषणा LQ_SIZE		2	/* 2 mode tables:  "Active" and "Search" */

/* load per tid defines क्रम A-MPDU activation */
#घोषणा IWL_AGG_TPT_THREHOLD	0
#घोषणा IWL_AGG_ALL_TID		0xff

क्रमागत iwl_table_type अणु
	LQ_NONE,
	LQ_LEGACY_G,	/* legacy types */
	LQ_LEGACY_A,
	LQ_HT_SISO,	/* HT types */
	LQ_HT_MIMO2,
	LQ_VHT_SISO,    /* VHT types */
	LQ_VHT_MIMO2,
	LQ_HE_SISO,     /* HE types */
	LQ_HE_MIMO2,
	LQ_MAX,
पूर्ण;

काष्ठा rs_rate अणु
	पूर्णांक index;
	क्रमागत iwl_table_type type;
	u8 ant;
	u32 bw;
	bool sgi;
	bool ldpc;
	bool stbc;
	bool bfer;
पूर्ण;


#घोषणा is_type_legacy(type) (((type) == LQ_LEGACY_G) || \
			      ((type) == LQ_LEGACY_A))
#घोषणा is_type_ht_siso(type) ((type) == LQ_HT_SISO)
#घोषणा is_type_ht_mimo2(type) ((type) == LQ_HT_MIMO2)
#घोषणा is_type_vht_siso(type) ((type) == LQ_VHT_SISO)
#घोषणा is_type_vht_mimo2(type) ((type) == LQ_VHT_MIMO2)
#घोषणा is_type_he_siso(type) ((type) == LQ_HE_SISO)
#घोषणा is_type_he_mimo2(type) ((type) == LQ_HE_MIMO2)
#घोषणा is_type_siso(type) (is_type_ht_siso(type) || is_type_vht_siso(type) || \
			    is_type_he_siso(type))
#घोषणा is_type_mimo2(type) (is_type_ht_mimo2(type) || \
			     is_type_vht_mimo2(type) || is_type_he_mimo2(type))
#घोषणा is_type_mimo(type) (is_type_mimo2(type))
#घोषणा is_type_ht(type) (is_type_ht_siso(type) || is_type_ht_mimo2(type))
#घोषणा is_type_vht(type) (is_type_vht_siso(type) || is_type_vht_mimo2(type))
#घोषणा is_type_he(type) (is_type_he_siso(type) || is_type_he_mimo2(type))
#घोषणा is_type_a_band(type) ((type) == LQ_LEGACY_A)
#घोषणा is_type_g_band(type) ((type) == LQ_LEGACY_G)

#घोषणा is_legacy(rate)       is_type_legacy((rate)->type)
#घोषणा is_ht_siso(rate)      is_type_ht_siso((rate)->type)
#घोषणा is_ht_mimo2(rate)     is_type_ht_mimo2((rate)->type)
#घोषणा is_vht_siso(rate)     is_type_vht_siso((rate)->type)
#घोषणा is_vht_mimo2(rate)    is_type_vht_mimo2((rate)->type)
#घोषणा is_siso(rate)         is_type_siso((rate)->type)
#घोषणा is_mimo2(rate)        is_type_mimo2((rate)->type)
#घोषणा is_mimo(rate)         is_type_mimo((rate)->type)
#घोषणा is_ht(rate)           is_type_ht((rate)->type)
#घोषणा is_vht(rate)          is_type_vht((rate)->type)
#घोषणा is_he(rate)           is_type_he((rate)->type)
#घोषणा is_a_band(rate)       is_type_a_band((rate)->type)
#घोषणा is_g_band(rate)       is_type_g_band((rate)->type)

#घोषणा is_ht20(rate)         ((rate)->bw == RATE_MCS_CHAN_WIDTH_20)
#घोषणा is_ht40(rate)         ((rate)->bw == RATE_MCS_CHAN_WIDTH_40)
#घोषणा is_ht80(rate)         ((rate)->bw == RATE_MCS_CHAN_WIDTH_80)
#घोषणा is_ht160(rate)        ((rate)->bw == RATE_MCS_CHAN_WIDTH_160)

#घोषणा IWL_MAX_MCS_DISPLAY_SIZE	12

काष्ठा iwl_rate_mcs_info अणु
	अक्षर	mbps[IWL_MAX_MCS_DISPLAY_SIZE];
	अक्षर	mcs[IWL_MAX_MCS_DISPLAY_SIZE];
पूर्ण;

/**
 * काष्ठा iwl_lq_sta_rs_fw - rate and related statistics क्रम RS in FW
 * @last_rate_n_flags: last rate reported by FW
 * @sta_id: the id of the station
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
 * @dbg_fixed_rate: क्रम debug, use fixed rate अगर not 0
 * @dbg_agg_frame_count_lim: क्रम debug, max number of frames in A-MPDU
#पूर्ण_अगर
 * @chains: biपंचांगask of chains reported in %chain_संकेत
 * @chain_संकेत: per chain संकेत strength
 * @last_rssi: last rssi reported
 * @drv: poपूर्णांकer back to the driver data
 */

काष्ठा iwl_lq_sta_rs_fw अणु
	/* last tx rate_n_flags */
	u32 last_rate_n_flags;

	/* persistent fields - initialized only once - keep last! */
	काष्ठा lq_sta_pers_rs_fw अणु
		u32 sta_id;
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
		u32 dbg_fixed_rate;
		u16 dbg_agg_frame_count_lim;
#पूर्ण_अगर
		u8 chains;
		s8 chain_संकेत[IEEE80211_MAX_CHAINS];
		s8 last_rssi;
		काष्ठा iwl_mvm *drv;
	पूर्ण pers;
पूर्ण;

/**
 * काष्ठा iwl_rate_scale_data -- tx success history क्रम one rate
 */
काष्ठा iwl_rate_scale_data अणु
	u64 data;		/* biपंचांगap of successful frames */
	s32 success_counter;	/* number of frames successful */
	s32 success_ratio;	/* per-cent * 128  */
	s32 counter;		/* number of frames attempted */
	s32 average_tpt;	/* success ratio * expected throughput */
पूर्ण;

/* Possible Tx columns
 * Tx Column = a combo of legacy/siso/mimo x antenna x SGI
 */
क्रमागत rs_column अणु
	RS_COLUMN_LEGACY_ANT_A = 0,
	RS_COLUMN_LEGACY_ANT_B,
	RS_COLUMN_SISO_ANT_A,
	RS_COLUMN_SISO_ANT_B,
	RS_COLUMN_SISO_ANT_A_SGI,
	RS_COLUMN_SISO_ANT_B_SGI,
	RS_COLUMN_MIMO2,
	RS_COLUMN_MIMO2_SGI,

	RS_COLUMN_LAST = RS_COLUMN_MIMO2_SGI,
	RS_COLUMN_COUNT = RS_COLUMN_LAST + 1,
	RS_COLUMN_INVALID,
पूर्ण;

क्रमागत rs_ss_क्रमce_opt अणु
	RS_SS_FORCE_NONE = 0,
	RS_SS_FORCE_STBC,
	RS_SS_FORCE_BFER,
	RS_SS_FORCE_SISO,
पूर्ण;

/* Packet stats per rate */
काष्ठा rs_rate_stats अणु
	u64 success;
	u64 total;
पूर्ण;

/**
 * काष्ठा iwl_scale_tbl_info -- tx params and success history क्रम all rates
 *
 * There are two of these in काष्ठा iwl_lq_sta,
 * one क्रम "active", and one क्रम "search".
 */
काष्ठा iwl_scale_tbl_info अणु
	काष्ठा rs_rate rate;
	क्रमागत rs_column column;
	स्थिर u16 *expected_tpt;	/* throughput metrics; expected_tpt_G, etc. */
	काष्ठा iwl_rate_scale_data win[IWL_RATE_COUNT]; /* rate histories */
	/* per txघातer-reduction history */
	काष्ठा iwl_rate_scale_data tpc_win[TPC_MAX_REDUCTION + 1];
पूर्ण;

क्रमागत अणु
	RS_STATE_SEARCH_CYCLE_STARTED,
	RS_STATE_SEARCH_CYCLE_ENDED,
	RS_STATE_STAY_IN_COLUMN,
पूर्ण;

/**
 * काष्ठा iwl_lq_sta -- driver's rate scaling निजी काष्ठाure
 *
 * Poपूर्णांकer to this माला_लो passed back and क्रमth between driver and mac80211.
 */
काष्ठा iwl_lq_sta अणु
	u8 active_tbl;		/* index of active table, range 0-1 */
	u8 rs_state;            /* RS_STATE_* */
	u8 search_better_tbl;	/* 1: currently trying alternate mode */
	s32 last_tpt;

	/* The following determine when to search क्रम a new mode */
	u32 table_count_limit;
	u32 max_failure_limit;	/* # failed frames beक्रमe new search */
	u32 max_success_limit;	/* # successful frames beक्रमe new search */
	u32 table_count;
	u32 total_failed;	/* total failed frames, any/all rates */
	u32 total_success;	/* total successful frames, any/all rates */
	u64 flush_समयr;	/* समय staying in mode beक्रमe new search */

	u32 visited_columns;    /* Biपंचांगask marking which Tx columns were
				 * explored during a search cycle
				 */
	u64 last_tx;
	bool is_vht;
	bool ldpc;              /* LDPC Rx is supported by the STA */
	bool stbc_capable;      /* Tx STBC is supported by chip and Rx by STA */
	bool bfer_capable;      /* Remote supports beamक्रमmee and we BFer */

	क्रमागत nl80211_band band;

	/* The following are biपंचांगaps of rates; IWL_RATE_6M_MASK, etc. */
	अचिन्हित दीर्घ active_legacy_rate;
	अचिन्हित दीर्घ active_siso_rate;
	अचिन्हित दीर्घ active_mimo2_rate;

	/* Highest rate per Tx mode */
	u8 max_legacy_rate_idx;
	u8 max_siso_rate_idx;
	u8 max_mimo2_rate_idx;

	/* Optimal rate based on RSSI and STA caps.
	 * Used only to reflect link speed to userspace.
	 */
	काष्ठा rs_rate optimal_rate;
	अचिन्हित दीर्घ optimal_rate_mask;
	स्थिर काष्ठा rs_init_rate_info *optimal_rates;
	पूर्णांक optimal_nentries;

	u8 missed_rate_counter;

	काष्ठा iwl_lq_cmd lq;
	काष्ठा iwl_scale_tbl_info lq_info[LQ_SIZE]; /* "active", "search" */
	u8 tx_agg_tid_en;

	/* last tx rate_n_flags */
	u32 last_rate_n_flags;
	/* packets destined क्रम this STA are aggregated */
	u8 is_agg;

	/* tx घातer reduce क्रम this sta */
	पूर्णांक tpc_reduce;

	/* persistent fields - initialized only once - keep last! */
	काष्ठा lq_sta_pers अणु
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
		u32 dbg_fixed_rate;
		u8 dbg_fixed_txp_reduction;

		/* क्रमce STBC/BFER/SISO क्रम testing */
		क्रमागत rs_ss_क्रमce_opt ss_क्रमce;
#पूर्ण_अगर
		u8 chains;
		s8 chain_संकेत[IEEE80211_MAX_CHAINS];
		s8 last_rssi;
		काष्ठा rs_rate_stats tx_stats[RS_COLUMN_COUNT][IWL_RATE_COUNT];
		काष्ठा iwl_mvm *drv;
		spinlock_t lock; /* क्रम races in reinit/update table */
	पूर्ण pers;
पूर्ण;

/* ieee80211_tx_info's status_driver_data[0] is packed with lq color and txp
 * Note, it's iwlmvm <-> mac80211 पूर्णांकerface.
 * bits 0-7: reduced tx घातer
 * bits 8-10: LQ command's color
 */
#घोषणा RS_DRV_DATA_TXP_MSK 0xff
#घोषणा RS_DRV_DATA_LQ_COLOR_POS 8
#घोषणा RS_DRV_DATA_LQ_COLOR_MSK (7 << RS_DRV_DATA_LQ_COLOR_POS)
#घोषणा RS_DRV_DATA_LQ_COLOR_GET(_f) (((_f) & RS_DRV_DATA_LQ_COLOR_MSK) >>\
				      RS_DRV_DATA_LQ_COLOR_POS)
#घोषणा RS_DRV_DATA_PACK(_c, _p) ((व्योम *)(uपूर्णांकptr_t)\
				  (((uपूर्णांकptr_t)_p) |\
				   ((_c) << RS_DRV_DATA_LQ_COLOR_POS)))

/* Initialize station's rate scaling inक्रमmation after adding station */
व्योम iwl_mvm_rs_rate_init(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			  क्रमागत nl80211_band band, bool init);

/* Notअगरy RS about Tx status */
व्योम iwl_mvm_rs_tx_status(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
			  पूर्णांक tid, काष्ठा ieee80211_tx_info *info, bool ndp);

/**
 * iwl_rate_control_रेजिस्टर - Register the rate control algorithm callbacks
 *
 * Since the rate control algorithm is hardware specअगरic, there is no need
 * or reason to place it as a stand alone module.  The driver can call
 * iwl_rate_control_रेजिस्टर in order to रेजिस्टर the rate control callbacks
 * with the mac80211 subप्रणाली.  This should be perक्रमmed prior to calling
 * ieee80211_रेजिस्टर_hw
 *
 */
पूर्णांक iwl_mvm_rate_control_रेजिस्टर(व्योम);

/**
 * iwl_rate_control_unरेजिस्टर - Unरेजिस्टर the rate control callbacks
 *
 * This should be called after calling ieee80211_unरेजिस्टर_hw, but beक्रमe
 * the driver is unloaded.
 */
व्योम iwl_mvm_rate_control_unरेजिस्टर(व्योम);

काष्ठा iwl_mvm_sta;

पूर्णांक iwl_mvm_tx_protection(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
			  bool enable);

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम iwl_mvm_reset_frame_stats(काष्ठा iwl_mvm *mvm);
#पूर्ण_अगर

व्योम iwl_mvm_rs_add_sta(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta);
व्योम rs_fw_rate_init(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_sta *sta,
		     क्रमागत nl80211_band band, bool update);
पूर्णांक rs_fw_tx_protection(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_sta *mvmsta,
			bool enable);
व्योम iwl_mvm_tlc_update_notअगर(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_rx_cmd_buffer *rxb);

u16 rs_fw_get_max_amsdu_len(काष्ठा ieee80211_sta *sta);
#पूर्ण_अगर /* __rs__ */
