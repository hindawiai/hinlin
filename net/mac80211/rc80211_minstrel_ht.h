<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010 Felix Fietkau <nbd@खोलोwrt.org>
 */

#अगर_अघोषित __RC_MINSTREL_HT_H
#घोषणा __RC_MINSTREL_HT_H

#समावेश <linux/bitfield.h>

/* number of highest throughput rates to consider*/
#घोषणा MAX_THR_RATES 4
#घोषणा SAMPLE_COLUMNS	10	/* number of columns in sample table */

/* scaled fraction values */
#घोषणा MINSTREL_SCALE  12
#घोषणा MINSTREL_FRAC(val, भाग) (((val) << MINSTREL_SCALE) / भाग)
#घोषणा MINSTREL_TRUNC(val) ((val) >> MINSTREL_SCALE)

#घोषणा EWMA_LEVEL	96	/* ewma weighting factor [/EWMA_DIV] */
#घोषणा EWMA_DIV	128

/*
 * Coefficients क्रम moving average with noise filter (period=16),
 * scaled by 10 bits
 *
 * a1 = exp(-pi * वर्ग_मूल(2) / period)
 * coeff2 = 2 * a1 * cos(वर्ग_मूल(2) * 2 * pi / period)
 * coeff3 = -sqr(a1)
 * coeff1 = 1 - coeff2 - coeff3
 */
#घोषणा MINSTREL_AVG_COEFF1		(MINSTREL_FRAC(1, 1) - \
					 MINSTREL_AVG_COEFF2 - \
					 MINSTREL_AVG_COEFF3)
#घोषणा MINSTREL_AVG_COEFF2		0x00001499
#घोषणा MINSTREL_AVG_COEFF3		-0x0000092e

/*
 * The number of streams can be changed to 2 to reduce code
 * size and memory footprपूर्णांक.
 */
#घोषणा MINSTREL_MAX_STREAMS		4
#घोषणा MINSTREL_HT_STREAM_GROUPS	4 /* BW(=2) * SGI(=2) */
#घोषणा MINSTREL_VHT_STREAM_GROUPS	6 /* BW(=3) * SGI(=2) */

#घोषणा MINSTREL_HT_GROUPS_NB	(MINSTREL_MAX_STREAMS *		\
				 MINSTREL_HT_STREAM_GROUPS)
#घोषणा MINSTREL_VHT_GROUPS_NB	(MINSTREL_MAX_STREAMS *		\
				 MINSTREL_VHT_STREAM_GROUPS)
#घोषणा MINSTREL_LEGACY_GROUPS_NB	2
#घोषणा MINSTREL_GROUPS_NB	(MINSTREL_HT_GROUPS_NB +	\
				 MINSTREL_VHT_GROUPS_NB +	\
				 MINSTREL_LEGACY_GROUPS_NB)

#घोषणा MINSTREL_HT_GROUP_0	0
#घोषणा MINSTREL_CCK_GROUP	(MINSTREL_HT_GROUP_0 + MINSTREL_HT_GROUPS_NB)
#घोषणा MINSTREL_OFDM_GROUP	(MINSTREL_CCK_GROUP + 1)
#घोषणा MINSTREL_VHT_GROUP_0	(MINSTREL_OFDM_GROUP + 1)

#घोषणा MCS_GROUP_RATES		10

#घोषणा MI_RATE_IDX_MASK	GENMASK(3, 0)
#घोषणा MI_RATE_GROUP_MASK	GENMASK(15, 4)

#घोषणा MI_RATE(_group, _idx)				\
	(FIELD_PREP(MI_RATE_GROUP_MASK, _group) |	\
	 FIELD_PREP(MI_RATE_IDX_MASK, _idx))

#घोषणा MI_RATE_IDX(_rate) FIELD_GET(MI_RATE_IDX_MASK, _rate)
#घोषणा MI_RATE_GROUP(_rate) FIELD_GET(MI_RATE_GROUP_MASK, _rate)

#घोषणा MINSTREL_SAMPLE_RATES		5 /* rates per sample type */
#घोषणा MINSTREL_SAMPLE_INTERVAL	(HZ / 50)

काष्ठा minstrel_priv अणु
	काष्ठा ieee80211_hw *hw;
	bool has_mrr;
	अचिन्हित पूर्णांक cw_min;
	अचिन्हित पूर्णांक cw_max;
	अचिन्हित पूर्णांक max_retry;
	अचिन्हित पूर्णांक segment_size;
	अचिन्हित पूर्णांक update_पूर्णांकerval;

	u8 cck_rates[4];
	u8 ofdm_rates[NUM_NL80211_BANDS][8];

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	/*
	 * enable fixed rate processing per RC
	 *   - ग_लिखो अटल index to debugfs:ieee80211/phyX/rc/fixed_rate_idx
	 *   - ग_लिखो -1 to enable RC processing again
	 *   - setting will be applied on next update
	 */
	u32 fixed_rate_idx;
#पूर्ण_अगर
पूर्ण;


काष्ठा mcs_group अणु
	u16 flags;
	u8 streams;
	u8 shअगरt;
	u8 bw;
	u16 duration[MCS_GROUP_RATES];
पूर्ण;

बाह्य स्थिर s16 minstrel_cck_bitrates[4];
बाह्य स्थिर s16 minstrel_ofdm_bitrates[8];
बाह्य स्थिर काष्ठा mcs_group minstrel_mcs_groups[];

काष्ठा minstrel_rate_stats अणु
	/* current / last sampling period attempts/success counters */
	u16 attempts, last_attempts;
	u16 success, last_success;

	/* total attempts/success counters */
	u32 att_hist, succ_hist;

	/* prob_avg - moving average of prob */
	u16 prob_avg;
	u16 prob_avg_1;

	/* maximum retry counts */
	u8 retry_count;
	u8 retry_count_rtscts;

	bool retry_updated;
पूर्ण;

क्रमागत minstrel_sample_type अणु
	MINSTREL_SAMPLE_TYPE_INC,
	MINSTREL_SAMPLE_TYPE_JUMP,
	MINSTREL_SAMPLE_TYPE_SLOW,
	__MINSTREL_SAMPLE_TYPE_MAX
पूर्ण;

काष्ठा minstrel_mcs_group_data अणु
	u8 index;
	u8 column;

	/* sorted rate set within a MCS group*/
	u16 max_group_tp_rate[MAX_THR_RATES];
	u16 max_group_prob_rate;

	/* MCS rate statistics */
	काष्ठा minstrel_rate_stats rates[MCS_GROUP_RATES];
पूर्ण;

काष्ठा minstrel_sample_category अणु
	u8 sample_group;
	u16 sample_rates[MINSTREL_SAMPLE_RATES];
	u16 cur_sample_rates[MINSTREL_SAMPLE_RATES];
पूर्ण;

काष्ठा minstrel_ht_sta अणु
	काष्ठा ieee80211_sta *sta;

	/* ampdu length (average, per sampling पूर्णांकerval) */
	अचिन्हित पूर्णांक ampdu_len;
	अचिन्हित पूर्णांक ampdu_packets;

	/* ampdu length (EWMA) */
	अचिन्हित पूर्णांक avg_ampdu_len;

	/* overall sorted rate set */
	u16 max_tp_rate[MAX_THR_RATES];
	u16 max_prob_rate;

	/* समय of last status update */
	अचिन्हित दीर्घ last_stats_update;

	/* overhead समय in usec क्रम each frame */
	अचिन्हित पूर्णांक overhead;
	अचिन्हित पूर्णांक overhead_rtscts;
	अचिन्हित पूर्णांक overhead_legacy;
	अचिन्हित पूर्णांक overhead_legacy_rtscts;

	अचिन्हित पूर्णांक total_packets;
	अचिन्हित पूर्णांक sample_packets;

	/* tx flags to add क्रम frames क्रम this sta */
	u32 tx_flags;

	u8 band;

	u8 sample_seq;
	u16 sample_rate;

	अचिन्हित दीर्घ sample_समय;
	काष्ठा minstrel_sample_category sample[__MINSTREL_SAMPLE_TYPE_MAX];

	/* Bitfield of supported MCS rates of all groups */
	u16 supported[MINSTREL_GROUPS_NB];

	/* MCS rate group info and statistics */
	काष्ठा minstrel_mcs_group_data groups[MINSTREL_GROUPS_NB];
पूर्ण;

व्योम minstrel_ht_add_sta_debugfs(व्योम *priv, व्योम *priv_sta, काष्ठा dentry *dir);
पूर्णांक minstrel_ht_get_tp_avg(काष्ठा minstrel_ht_sta *mi, पूर्णांक group, पूर्णांक rate,
			   पूर्णांक prob_avg);

#पूर्ण_अगर
