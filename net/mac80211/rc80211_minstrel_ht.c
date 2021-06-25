<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010-2013 Felix Fietkau <nbd@खोलोwrt.org>
 * Copyright (C) 2019-2020 Intel Corporation
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/mac80211.h>
#समावेश "rate.h"
#समावेश "sta_info.h"
#समावेश "rc80211_minstrel_ht.h"

#घोषणा AVG_AMPDU_SIZE	16
#घोषणा AVG_PKT_SIZE	1200

#घोषणा SAMPLE_SWITCH_THR	100

/* Number of bits क्रम an average sized packet */
#घोषणा MCS_NBITS ((AVG_PKT_SIZE * AVG_AMPDU_SIZE) << 3)

/* Number of symbols क्रम a packet with (bps) bits per symbol */
#घोषणा MCS_NSYMS(bps) DIV_ROUND_UP(MCS_NBITS, (bps))

/* Transmission समय (nanoseconds) क्रम a packet containing (syms) symbols */
#घोषणा MCS_SYMBOL_TIME(sgi, syms)					\
	(sgi ?								\
	  ((syms) * 18000 + 4000) / 5 :	/* syms * 3.6 us */		\
	  ((syms) * 1000) << 2		/* syms * 4 us */		\
	)

/* Transmit duration क्रम the raw data part of an average sized packet */
#घोषणा MCS_DURATION(streams, sgi, bps) \
	(MCS_SYMBOL_TIME(sgi, MCS_NSYMS((streams) * (bps))) / AVG_AMPDU_SIZE)

#घोषणा BW_20			0
#घोषणा BW_40			1
#घोषणा BW_80			2

/*
 * Define group sort order: HT40 -> SGI -> #streams
 */
#घोषणा GROUP_IDX(_streams, _sgi, _ht40)	\
	MINSTREL_HT_GROUP_0 +			\
	MINSTREL_MAX_STREAMS * 2 * _ht40 +	\
	MINSTREL_MAX_STREAMS * _sgi +	\
	_streams - 1

#घोषणा _MAX(a, b) (((a)>(b))?(a):(b))

#घोषणा GROUP_SHIFT(duration)						\
	_MAX(0, 16 - __builtin_clz(duration))

/* MCS rate inक्रमmation क्रम an MCS group */
#घोषणा __MCS_GROUP(_streams, _sgi, _ht40, _s)				\
	[GROUP_IDX(_streams, _sgi, _ht40)] = अणु				\
	.streams = _streams,						\
	.shअगरt = _s,							\
	.bw = _ht40,							\
	.flags =							\
		IEEE80211_TX_RC_MCS |					\
		(_sgi ? IEEE80211_TX_RC_SHORT_GI : 0) |			\
		(_ht40 ? IEEE80211_TX_RC_40_MHZ_WIDTH : 0),		\
	.duration = अणु							\
		MCS_DURATION(_streams, _sgi, _ht40 ? 54 : 26) >> _s,	\
		MCS_DURATION(_streams, _sgi, _ht40 ? 108 : 52) >> _s,	\
		MCS_DURATION(_streams, _sgi, _ht40 ? 162 : 78) >> _s,	\
		MCS_DURATION(_streams, _sgi, _ht40 ? 216 : 104) >> _s,	\
		MCS_DURATION(_streams, _sgi, _ht40 ? 324 : 156) >> _s,	\
		MCS_DURATION(_streams, _sgi, _ht40 ? 432 : 208) >> _s,	\
		MCS_DURATION(_streams, _sgi, _ht40 ? 486 : 234) >> _s,	\
		MCS_DURATION(_streams, _sgi, _ht40 ? 540 : 260) >> _s	\
	पूर्ण								\
पूर्ण

#घोषणा MCS_GROUP_SHIFT(_streams, _sgi, _ht40)				\
	GROUP_SHIFT(MCS_DURATION(_streams, _sgi, _ht40 ? 54 : 26))

#घोषणा MCS_GROUP(_streams, _sgi, _ht40)				\
	__MCS_GROUP(_streams, _sgi, _ht40,				\
		    MCS_GROUP_SHIFT(_streams, _sgi, _ht40))

#घोषणा VHT_GROUP_IDX(_streams, _sgi, _bw)				\
	(MINSTREL_VHT_GROUP_0 +						\
	 MINSTREL_MAX_STREAMS * 2 * (_bw) +				\
	 MINSTREL_MAX_STREAMS * (_sgi) +				\
	 (_streams) - 1)

#घोषणा BW2VBPS(_bw, r3, r2, r1)					\
	(_bw == BW_80 ? r3 : _bw == BW_40 ? r2 : r1)

#घोषणा __VHT_GROUP(_streams, _sgi, _bw, _s)				\
	[VHT_GROUP_IDX(_streams, _sgi, _bw)] = अणु			\
	.streams = _streams,						\
	.shअगरt = _s,							\
	.bw = _bw,							\
	.flags =							\
		IEEE80211_TX_RC_VHT_MCS |				\
		(_sgi ? IEEE80211_TX_RC_SHORT_GI : 0) |			\
		(_bw == BW_80 ? IEEE80211_TX_RC_80_MHZ_WIDTH :		\
		 _bw == BW_40 ? IEEE80211_TX_RC_40_MHZ_WIDTH : 0),	\
	.duration = अणु							\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw,  117,  54,  26)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw,  234, 108,  52)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw,  351, 162,  78)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw,  468, 216, 104)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw,  702, 324, 156)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw,  936, 432, 208)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw, 1053, 486, 234)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw, 1170, 540, 260)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw, 1404, 648, 312)) >> _s,	\
		MCS_DURATION(_streams, _sgi,				\
			     BW2VBPS(_bw, 1560, 720, 346)) >> _s	\
	पूर्ण								\
पूर्ण

#घोषणा VHT_GROUP_SHIFT(_streams, _sgi, _bw)				\
	GROUP_SHIFT(MCS_DURATION(_streams, _sgi,			\
				 BW2VBPS(_bw,  117,  54,  26)))

#घोषणा VHT_GROUP(_streams, _sgi, _bw)					\
	__VHT_GROUP(_streams, _sgi, _bw,				\
		    VHT_GROUP_SHIFT(_streams, _sgi, _bw))

#घोषणा CCK_DURATION(_bitrate, _लघु)			\
	(1000 * (10 /* SIFS */ +			\
	 (_लघु ? 72 + 24 : 144 + 48) +		\
	 (8 * (AVG_PKT_SIZE + 4) * 10) / (_bitrate)))

#घोषणा CCK_DURATION_LIST(_लघु, _s)			\
	CCK_DURATION(10, _लघु) >> _s,			\
	CCK_DURATION(20, _लघु) >> _s,			\
	CCK_DURATION(55, _लघु) >> _s,			\
	CCK_DURATION(110, _लघु) >> _s

#घोषणा __CCK_GROUP(_s)					\
	[MINSTREL_CCK_GROUP] = अणु			\
		.streams = 1,				\
		.flags = 0,				\
		.shअगरt = _s,				\
		.duration = अणु				\
			CCK_DURATION_LIST(false, _s),	\
			CCK_DURATION_LIST(true, _s)	\
		पूर्ण					\
	पूर्ण

#घोषणा CCK_GROUP_SHIFT					\
	GROUP_SHIFT(CCK_DURATION(10, false))

#घोषणा CCK_GROUP __CCK_GROUP(CCK_GROUP_SHIFT)

#घोषणा OFDM_DURATION(_bitrate)				\
	(1000 * (16 /* SIFS + संकेत ext */ +		\
	 16 /* T_PREAMBLE */ +				\
	 4 /* T_SIGNAL */ +				\
	 4 * (((16 + 80 * (AVG_PKT_SIZE + 4) + 6) /	\
	      ((_bitrate) * 4)))))

#घोषणा OFDM_DURATION_LIST(_s)				\
	OFDM_DURATION(60) >> _s,			\
	OFDM_DURATION(90) >> _s,			\
	OFDM_DURATION(120) >> _s,			\
	OFDM_DURATION(180) >> _s,			\
	OFDM_DURATION(240) >> _s,			\
	OFDM_DURATION(360) >> _s,			\
	OFDM_DURATION(480) >> _s,			\
	OFDM_DURATION(540) >> _s

#घोषणा __OFDM_GROUP(_s)				\
	[MINSTREL_OFDM_GROUP] = अणु			\
		.streams = 1,				\
		.flags = 0,				\
		.shअगरt = _s,				\
		.duration = अणु				\
			OFDM_DURATION_LIST(_s),		\
		पूर्ण					\
	पूर्ण

#घोषणा OFDM_GROUP_SHIFT				\
	GROUP_SHIFT(OFDM_DURATION(60))

#घोषणा OFDM_GROUP __OFDM_GROUP(OFDM_GROUP_SHIFT)


अटल bool minstrel_vht_only = true;
module_param(minstrel_vht_only, bool, 0644);
MODULE_PARM_DESC(minstrel_vht_only,
		 "Use only VHT rates when VHT is supported by sta.");

/*
 * To enable sufficiently targeted rate sampling, MCS rates are भागided पूर्णांकo
 * groups, based on the number of streams and flags (HT40, SGI) that they
 * use.
 *
 * Sortorder has to be fixed क्रम GROUP_IDX macro to be applicable:
 * BW -> SGI -> #streams
 */
स्थिर काष्ठा mcs_group minstrel_mcs_groups[] = अणु
	MCS_GROUP(1, 0, BW_20),
	MCS_GROUP(2, 0, BW_20),
	MCS_GROUP(3, 0, BW_20),
	MCS_GROUP(4, 0, BW_20),

	MCS_GROUP(1, 1, BW_20),
	MCS_GROUP(2, 1, BW_20),
	MCS_GROUP(3, 1, BW_20),
	MCS_GROUP(4, 1, BW_20),

	MCS_GROUP(1, 0, BW_40),
	MCS_GROUP(2, 0, BW_40),
	MCS_GROUP(3, 0, BW_40),
	MCS_GROUP(4, 0, BW_40),

	MCS_GROUP(1, 1, BW_40),
	MCS_GROUP(2, 1, BW_40),
	MCS_GROUP(3, 1, BW_40),
	MCS_GROUP(4, 1, BW_40),

	CCK_GROUP,
	OFDM_GROUP,

	VHT_GROUP(1, 0, BW_20),
	VHT_GROUP(2, 0, BW_20),
	VHT_GROUP(3, 0, BW_20),
	VHT_GROUP(4, 0, BW_20),

	VHT_GROUP(1, 1, BW_20),
	VHT_GROUP(2, 1, BW_20),
	VHT_GROUP(3, 1, BW_20),
	VHT_GROUP(4, 1, BW_20),

	VHT_GROUP(1, 0, BW_40),
	VHT_GROUP(2, 0, BW_40),
	VHT_GROUP(3, 0, BW_40),
	VHT_GROUP(4, 0, BW_40),

	VHT_GROUP(1, 1, BW_40),
	VHT_GROUP(2, 1, BW_40),
	VHT_GROUP(3, 1, BW_40),
	VHT_GROUP(4, 1, BW_40),

	VHT_GROUP(1, 0, BW_80),
	VHT_GROUP(2, 0, BW_80),
	VHT_GROUP(3, 0, BW_80),
	VHT_GROUP(4, 0, BW_80),

	VHT_GROUP(1, 1, BW_80),
	VHT_GROUP(2, 1, BW_80),
	VHT_GROUP(3, 1, BW_80),
	VHT_GROUP(4, 1, BW_80),
पूर्ण;

स्थिर s16 minstrel_cck_bitrates[4] = अणु 10, 20, 55, 110 पूर्ण;
स्थिर s16 minstrel_ofdm_bitrates[8] = अणु 60, 90, 120, 180, 240, 360, 480, 540 पूर्ण;
अटल u8 sample_table[SAMPLE_COLUMNS][MCS_GROUP_RATES] __पढ़ो_mostly;
अटल स्थिर u8 minstrel_sample_seq[] = अणु
	MINSTREL_SAMPLE_TYPE_INC,
	MINSTREL_SAMPLE_TYPE_JUMP,
	MINSTREL_SAMPLE_TYPE_INC,
	MINSTREL_SAMPLE_TYPE_JUMP,
	MINSTREL_SAMPLE_TYPE_INC,
	MINSTREL_SAMPLE_TYPE_SLOW,
पूर्ण;

अटल व्योम
minstrel_ht_update_rates(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi);

/*
 * Some VHT MCSes are invalid (when Ndbps / Nes is not an पूर्णांकeger)
 * e.g क्रम MCS9@20MHzx1Nss: Ndbps=8x52*(5/6) Nes=1
 *
 * Returns the valid mcs map क्रम काष्ठा minstrel_mcs_group_data.supported
 */
अटल u16
minstrel_get_valid_vht_rates(पूर्णांक bw, पूर्णांक nss, __le16 mcs_map)
अणु
	u16 mask = 0;

	अगर (bw == BW_20) अणु
		अगर (nss != 3 && nss != 6)
			mask = BIT(9);
	पूर्ण अन्यथा अगर (bw == BW_80) अणु
		अगर (nss == 3 || nss == 7)
			mask = BIT(6);
		अन्यथा अगर (nss == 6)
			mask = BIT(9);
	पूर्ण अन्यथा अणु
		WARN_ON(bw != BW_40);
	पूर्ण

	चयन ((le16_to_cpu(mcs_map) >> (2 * (nss - 1))) & 3) अणु
	हाल IEEE80211_VHT_MCS_SUPPORT_0_7:
		mask |= 0x300;
		अवरोध;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_8:
		mask |= 0x200;
		अवरोध;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_9:
		अवरोध;
	शेष:
		mask = 0x3ff;
	पूर्ण

	वापस 0x3ff & ~mask;
पूर्ण

अटल bool
minstrel_ht_is_legacy_group(पूर्णांक group)
अणु
	वापस group == MINSTREL_CCK_GROUP ||
	       group == MINSTREL_OFDM_GROUP;
पूर्ण

/*
 * Look up an MCS group index based on mac80211 rate inक्रमmation
 */
अटल पूर्णांक
minstrel_ht_get_group_idx(काष्ठा ieee80211_tx_rate *rate)
अणु
	वापस GROUP_IDX((rate->idx / 8) + 1,
			 !!(rate->flags & IEEE80211_TX_RC_SHORT_GI),
			 !!(rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH));
पूर्ण

अटल पूर्णांक
minstrel_vht_get_group_idx(काष्ठा ieee80211_tx_rate *rate)
अणु
	वापस VHT_GROUP_IDX(ieee80211_rate_get_vht_nss(rate),
			     !!(rate->flags & IEEE80211_TX_RC_SHORT_GI),
			     !!(rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH) +
			     2*!!(rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH));
पूर्ण

अटल काष्ठा minstrel_rate_stats *
minstrel_ht_get_stats(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi,
		      काष्ठा ieee80211_tx_rate *rate)
अणु
	पूर्णांक group, idx;

	अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		group = minstrel_ht_get_group_idx(rate);
		idx = rate->idx % 8;
		जाओ out;
	पूर्ण

	अगर (rate->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		group = minstrel_vht_get_group_idx(rate);
		idx = ieee80211_rate_get_vht_mcs(rate);
		जाओ out;
	पूर्ण

	group = MINSTREL_CCK_GROUP;
	क्रम (idx = 0; idx < ARRAY_SIZE(mp->cck_rates); idx++) अणु
		अगर (rate->idx != mp->cck_rates[idx])
			जारी;

		/* लघु preamble */
		अगर ((mi->supported[group] & BIT(idx + 4)) &&
		    (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE))
			idx += 4;
		जाओ out;
	पूर्ण

	group = MINSTREL_OFDM_GROUP;
	क्रम (idx = 0; idx < ARRAY_SIZE(mp->ofdm_rates[0]); idx++)
		अगर (rate->idx == mp->ofdm_rates[mi->band][idx])
			जाओ out;

	idx = 0;
out:
	वापस &mi->groups[group].rates[idx];
पूर्ण

अटल अंतरभूत काष्ठा minstrel_rate_stats *
minstrel_get_ratestats(काष्ठा minstrel_ht_sta *mi, पूर्णांक index)
अणु
	वापस &mi->groups[MI_RATE_GROUP(index)].rates[MI_RATE_IDX(index)];
पूर्ण

अटल अंतरभूत पूर्णांक minstrel_get_duration(पूर्णांक index)
अणु
	स्थिर काष्ठा mcs_group *group = &minstrel_mcs_groups[MI_RATE_GROUP(index)];
	अचिन्हित पूर्णांक duration = group->duration[MI_RATE_IDX(index)];

	वापस duration << group->shअगरt;
पूर्ण

अटल अचिन्हित पूर्णांक
minstrel_ht_avg_ampdu_len(काष्ठा minstrel_ht_sta *mi)
अणु
	पूर्णांक duration;

	अगर (mi->avg_ampdu_len)
		वापस MINSTREL_TRUNC(mi->avg_ampdu_len);

	अगर (minstrel_ht_is_legacy_group(MI_RATE_GROUP(mi->max_tp_rate[0])))
		वापस 1;

	duration = minstrel_get_duration(mi->max_tp_rate[0]);

	अगर (duration > 400 * 1000)
		वापस 2;

	अगर (duration > 250 * 1000)
		वापस 4;

	अगर (duration > 150 * 1000)
		वापस 8;

	वापस 16;
पूर्ण

/*
 * Return current throughput based on the average A-MPDU length, taking पूर्णांकo
 * account the expected number of retransmissions and their expected length
 */
पूर्णांक
minstrel_ht_get_tp_avg(काष्ठा minstrel_ht_sta *mi, पूर्णांक group, पूर्णांक rate,
		       पूर्णांक prob_avg)
अणु
	अचिन्हित पूर्णांक nsecs = 0, overhead = mi->overhead;
	अचिन्हित पूर्णांक ampdu_len = 1;

	/* करो not account throughput अगर sucess prob is below 10% */
	अगर (prob_avg < MINSTREL_FRAC(10, 100))
		वापस 0;

	अगर (minstrel_ht_is_legacy_group(group))
		overhead = mi->overhead_legacy;
	अन्यथा
		ampdu_len = minstrel_ht_avg_ampdu_len(mi);

	nsecs = 1000 * overhead / ampdu_len;
	nsecs += minstrel_mcs_groups[group].duration[rate] <<
		 minstrel_mcs_groups[group].shअगरt;

	/*
	 * For the throughput calculation, limit the probability value to 90% to
	 * account क्रम collision related packet error rate fluctuation
	 * (prob is scaled - see MINSTREL_FRAC above)
	 */
	अगर (prob_avg > MINSTREL_FRAC(90, 100))
		prob_avg = MINSTREL_FRAC(90, 100);

	वापस MINSTREL_TRUNC(100 * ((prob_avg * 1000000) / nsecs));
पूर्ण

/*
 * Find & sort topmost throughput rates
 *
 * If multiple rates provide equal throughput the sorting is based on their
 * current success probability. Higher success probability is preferred among
 * MCS groups, CCK rates करो not provide aggregation and are thereक्रमe at last.
 */
अटल व्योम
minstrel_ht_sort_best_tp_rates(काष्ठा minstrel_ht_sta *mi, u16 index,
			       u16 *tp_list)
अणु
	पूर्णांक cur_group, cur_idx, cur_tp_avg, cur_prob;
	पूर्णांक पंचांगp_group, पंचांगp_idx, पंचांगp_tp_avg, पंचांगp_prob;
	पूर्णांक j = MAX_THR_RATES;

	cur_group = MI_RATE_GROUP(index);
	cur_idx = MI_RATE_IDX(index);
	cur_prob = mi->groups[cur_group].rates[cur_idx].prob_avg;
	cur_tp_avg = minstrel_ht_get_tp_avg(mi, cur_group, cur_idx, cur_prob);

	करो अणु
		पंचांगp_group = MI_RATE_GROUP(tp_list[j - 1]);
		पंचांगp_idx = MI_RATE_IDX(tp_list[j - 1]);
		पंचांगp_prob = mi->groups[पंचांगp_group].rates[पंचांगp_idx].prob_avg;
		पंचांगp_tp_avg = minstrel_ht_get_tp_avg(mi, पंचांगp_group, पंचांगp_idx,
						    पंचांगp_prob);
		अगर (cur_tp_avg < पंचांगp_tp_avg ||
		    (cur_tp_avg == पंचांगp_tp_avg && cur_prob <= पंचांगp_prob))
			अवरोध;
		j--;
	पूर्ण जबतक (j > 0);

	अगर (j < MAX_THR_RATES - 1) अणु
		स_हटाओ(&tp_list[j + 1], &tp_list[j], (माप(*tp_list) *
		       (MAX_THR_RATES - (j + 1))));
	पूर्ण
	अगर (j < MAX_THR_RATES)
		tp_list[j] = index;
पूर्ण

/*
 * Find and set the topmost probability rate per sta and per group
 */
अटल व्योम
minstrel_ht_set_best_prob_rate(काष्ठा minstrel_ht_sta *mi, u16 *dest, u16 index)
अणु
	काष्ठा minstrel_mcs_group_data *mg;
	काष्ठा minstrel_rate_stats *mrs;
	पूर्णांक पंचांगp_group, पंचांगp_idx, पंचांगp_tp_avg, पंचांगp_prob;
	पूर्णांक max_tp_group, max_tp_idx, max_tp_prob;
	पूर्णांक cur_tp_avg, cur_group, cur_idx;
	पूर्णांक max_gpr_group, max_gpr_idx;
	पूर्णांक max_gpr_tp_avg, max_gpr_prob;

	cur_group = MI_RATE_GROUP(index);
	cur_idx = MI_RATE_IDX(index);
	mg = &mi->groups[cur_group];
	mrs = &mg->rates[cur_idx];

	पंचांगp_group = MI_RATE_GROUP(*dest);
	पंचांगp_idx = MI_RATE_IDX(*dest);
	पंचांगp_prob = mi->groups[पंचांगp_group].rates[पंचांगp_idx].prob_avg;
	पंचांगp_tp_avg = minstrel_ht_get_tp_avg(mi, पंचांगp_group, पंचांगp_idx, पंचांगp_prob);

	/* अगर max_tp_rate[0] is from MCS_GROUP max_prob_rate get selected from
	 * MCS_GROUP as well as CCK_GROUP rates करो not allow aggregation */
	max_tp_group = MI_RATE_GROUP(mi->max_tp_rate[0]);
	max_tp_idx = MI_RATE_IDX(mi->max_tp_rate[0]);
	max_tp_prob = mi->groups[max_tp_group].rates[max_tp_idx].prob_avg;

	अगर (minstrel_ht_is_legacy_group(MI_RATE_GROUP(index)) &&
	    !minstrel_ht_is_legacy_group(max_tp_group))
		वापस;

	/* skip rates faster than max tp rate with lower prob */
	अगर (minstrel_get_duration(mi->max_tp_rate[0]) > minstrel_get_duration(index) &&
	    mrs->prob_avg < max_tp_prob)
		वापस;

	max_gpr_group = MI_RATE_GROUP(mg->max_group_prob_rate);
	max_gpr_idx = MI_RATE_IDX(mg->max_group_prob_rate);
	max_gpr_prob = mi->groups[max_gpr_group].rates[max_gpr_idx].prob_avg;

	अगर (mrs->prob_avg > MINSTREL_FRAC(75, 100)) अणु
		cur_tp_avg = minstrel_ht_get_tp_avg(mi, cur_group, cur_idx,
						    mrs->prob_avg);
		अगर (cur_tp_avg > पंचांगp_tp_avg)
			*dest = index;

		max_gpr_tp_avg = minstrel_ht_get_tp_avg(mi, max_gpr_group,
							max_gpr_idx,
							max_gpr_prob);
		अगर (cur_tp_avg > max_gpr_tp_avg)
			mg->max_group_prob_rate = index;
	पूर्ण अन्यथा अणु
		अगर (mrs->prob_avg > पंचांगp_prob)
			*dest = index;
		अगर (mrs->prob_avg > max_gpr_prob)
			mg->max_group_prob_rate = index;
	पूर्ण
पूर्ण


/*
 * Assign new rate set per sta and use CCK rates only अगर the fastest
 * rate (max_tp_rate[0]) is from CCK group. This prohibits such sorted
 * rate sets where MCS and CCK rates are mixed, because CCK rates can
 * not use aggregation.
 */
अटल व्योम
minstrel_ht_assign_best_tp_rates(काष्ठा minstrel_ht_sta *mi,
				 u16 पंचांगp_mcs_tp_rate[MAX_THR_RATES],
				 u16 पंचांगp_legacy_tp_rate[MAX_THR_RATES])
अणु
	अचिन्हित पूर्णांक पंचांगp_group, पंचांगp_idx, पंचांगp_cck_tp, पंचांगp_mcs_tp, पंचांगp_prob;
	पूर्णांक i;

	पंचांगp_group = MI_RATE_GROUP(पंचांगp_legacy_tp_rate[0]);
	पंचांगp_idx = MI_RATE_IDX(पंचांगp_legacy_tp_rate[0]);
	पंचांगp_prob = mi->groups[पंचांगp_group].rates[पंचांगp_idx].prob_avg;
	पंचांगp_cck_tp = minstrel_ht_get_tp_avg(mi, पंचांगp_group, पंचांगp_idx, पंचांगp_prob);

	पंचांगp_group = MI_RATE_GROUP(पंचांगp_mcs_tp_rate[0]);
	पंचांगp_idx = MI_RATE_IDX(पंचांगp_mcs_tp_rate[0]);
	पंचांगp_prob = mi->groups[पंचांगp_group].rates[पंचांगp_idx].prob_avg;
	पंचांगp_mcs_tp = minstrel_ht_get_tp_avg(mi, पंचांगp_group, पंचांगp_idx, पंचांगp_prob);

	अगर (पंचांगp_cck_tp > पंचांगp_mcs_tp) अणु
		क्रम(i = 0; i < MAX_THR_RATES; i++) अणु
			minstrel_ht_sort_best_tp_rates(mi, पंचांगp_legacy_tp_rate[i],
						       पंचांगp_mcs_tp_rate);
		पूर्ण
	पूर्ण

पूर्ण

/*
 * Try to increase robustness of max_prob rate by decrease number of
 * streams अगर possible.
 */
अटल अंतरभूत व्योम
minstrel_ht_prob_rate_reduce_streams(काष्ठा minstrel_ht_sta *mi)
अणु
	काष्ठा minstrel_mcs_group_data *mg;
	पूर्णांक पंचांगp_max_streams, group, पंचांगp_idx, पंचांगp_prob;
	पूर्णांक पंचांगp_tp = 0;

	अगर (!mi->sta->ht_cap.ht_supported)
		वापस;

	group = MI_RATE_GROUP(mi->max_tp_rate[0]);
	पंचांगp_max_streams = minstrel_mcs_groups[group].streams;
	क्रम (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) अणु
		mg = &mi->groups[group];
		अगर (!mi->supported[group] || group == MINSTREL_CCK_GROUP)
			जारी;

		पंचांगp_idx = MI_RATE_IDX(mg->max_group_prob_rate);
		पंचांगp_prob = mi->groups[group].rates[पंचांगp_idx].prob_avg;

		अगर (पंचांगp_tp < minstrel_ht_get_tp_avg(mi, group, पंचांगp_idx, पंचांगp_prob) &&
		   (minstrel_mcs_groups[group].streams < पंचांगp_max_streams)) अणु
				mi->max_prob_rate = mg->max_group_prob_rate;
				पंचांगp_tp = minstrel_ht_get_tp_avg(mi, group,
								पंचांगp_idx,
								पंचांगp_prob);
		पूर्ण
	पूर्ण
पूर्ण

अटल u16
__minstrel_ht_get_sample_rate(काष्ठा minstrel_ht_sta *mi,
			      क्रमागत minstrel_sample_type type)
अणु
	u16 *rates = mi->sample[type].sample_rates;
	u16 cur;
	पूर्णांक i;

	क्रम (i = 0; i < MINSTREL_SAMPLE_RATES; i++) अणु
		अगर (!rates[i])
			जारी;

		cur = rates[i];
		rates[i] = 0;
		वापस cur;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
minstrel_ewma(पूर्णांक old, पूर्णांक new, पूर्णांक weight)
अणु
	पूर्णांक dअगरf, incr;

	dअगरf = new - old;
	incr = (EWMA_DIV - weight) * dअगरf / EWMA_DIV;

	वापस old + incr;
पूर्ण

अटल अंतरभूत पूर्णांक minstrel_filter_avg_add(u16 *prev_1, u16 *prev_2, s32 in)
अणु
	s32 out_1 = *prev_1;
	s32 out_2 = *prev_2;
	s32 val;

	अगर (!in)
		in += 1;

	अगर (!out_1) अणु
		val = out_1 = in;
		जाओ out;
	पूर्ण

	val = MINSTREL_AVG_COEFF1 * in;
	val += MINSTREL_AVG_COEFF2 * out_1;
	val += MINSTREL_AVG_COEFF3 * out_2;
	val >>= MINSTREL_SCALE;

	अगर (val > 1 << MINSTREL_SCALE)
		val = 1 << MINSTREL_SCALE;
	अगर (val < 0)
		val = 1;

out:
	*prev_2 = out_1;
	*prev_1 = val;

	वापस val;
पूर्ण

/*
* Recalculate statistics and counters of a given rate
*/
अटल व्योम
minstrel_ht_calc_rate_stats(काष्ठा minstrel_priv *mp,
			    काष्ठा minstrel_rate_stats *mrs)
अणु
	अचिन्हित पूर्णांक cur_prob;

	अगर (unlikely(mrs->attempts > 0)) अणु
		cur_prob = MINSTREL_FRAC(mrs->success, mrs->attempts);
		minstrel_filter_avg_add(&mrs->prob_avg,
					&mrs->prob_avg_1, cur_prob);
		mrs->att_hist += mrs->attempts;
		mrs->succ_hist += mrs->success;
	पूर्ण

	mrs->last_success = mrs->success;
	mrs->last_attempts = mrs->attempts;
	mrs->success = 0;
	mrs->attempts = 0;
पूर्ण

अटल bool
minstrel_ht_find_sample_rate(काष्ठा minstrel_ht_sta *mi, पूर्णांक type, पूर्णांक idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MINSTREL_SAMPLE_RATES; i++) अणु
		u16 cur = mi->sample[type].sample_rates[i];

		अगर (cur == idx)
			वापस true;

		अगर (!cur)
			अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
minstrel_ht_move_sample_rates(काष्ठा minstrel_ht_sta *mi, पूर्णांक type,
			      u32 fast_rate_dur, u32 slow_rate_dur)
अणु
	u16 *rates = mi->sample[type].sample_rates;
	पूर्णांक i, j;

	क्रम (i = 0, j = 0; i < MINSTREL_SAMPLE_RATES; i++) अणु
		u32 duration;
		bool valid = false;
		u16 cur;

		cur = rates[i];
		अगर (!cur)
			जारी;

		duration = minstrel_get_duration(cur);
		चयन (type) अणु
		हाल MINSTREL_SAMPLE_TYPE_SLOW:
			valid = duration > fast_rate_dur &&
				duration < slow_rate_dur;
			अवरोध;
		हाल MINSTREL_SAMPLE_TYPE_INC:
		हाल MINSTREL_SAMPLE_TYPE_JUMP:
			valid = duration < fast_rate_dur;
			अवरोध;
		शेष:
			valid = false;
			अवरोध;
		पूर्ण

		अगर (!valid) अणु
			rates[i] = 0;
			जारी;
		पूर्ण

		अगर (i == j)
			जारी;

		rates[j++] = cur;
		rates[i] = 0;
	पूर्ण

	वापस j;
पूर्ण

अटल पूर्णांक
minstrel_ht_group_min_rate_offset(काष्ठा minstrel_ht_sta *mi, पूर्णांक group,
				  u32 max_duration)
अणु
	u16 supported = mi->supported[group];
	पूर्णांक i;

	क्रम (i = 0; i < MCS_GROUP_RATES && supported; i++, supported >>= 1) अणु
		अगर (!(supported & BIT(0)))
			जारी;

		अगर (minstrel_get_duration(MI_RATE(group, i)) >= max_duration)
			जारी;

		वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/*
 * Incremental update rates:
 * Flip through groups and pick the first group rate that is faster than the
 * highest currently selected rate
 */
अटल u16
minstrel_ht_next_inc_rate(काष्ठा minstrel_ht_sta *mi, u32 fast_rate_dur)
अणु
	u8 type = MINSTREL_SAMPLE_TYPE_INC;
	पूर्णांक i, index = 0;
	u8 group;

	group = mi->sample[type].sample_group;
	क्रम (i = 0; i < ARRAY_SIZE(minstrel_mcs_groups); i++) अणु
		group = (group + 1) % ARRAY_SIZE(minstrel_mcs_groups);

		index = minstrel_ht_group_min_rate_offset(mi, group,
							  fast_rate_dur);
		अगर (index < 0)
			जारी;

		index = MI_RATE(group, index & 0xf);
		अगर (!minstrel_ht_find_sample_rate(mi, type, index))
			जाओ out;
	पूर्ण
	index = 0;

out:
	mi->sample[type].sample_group = group;

	वापस index;
पूर्ण

अटल पूर्णांक
minstrel_ht_next_group_sample_rate(काष्ठा minstrel_ht_sta *mi, पूर्णांक group,
				   u16 supported, पूर्णांक offset)
अणु
	काष्ठा minstrel_mcs_group_data *mg = &mi->groups[group];
	u16 idx;
	पूर्णांक i;

	क्रम (i = 0; i < MCS_GROUP_RATES; i++) अणु
		idx = sample_table[mg->column][mg->index];
		अगर (++mg->index >= MCS_GROUP_RATES) अणु
			mg->index = 0;
			अगर (++mg->column >= ARRAY_SIZE(sample_table))
				mg->column = 0;
		पूर्ण

		अगर (idx < offset)
			जारी;

		अगर (!(supported & BIT(idx)))
			जारी;

		वापस MI_RATE(group, idx);
	पूर्ण

	वापस -1;
पूर्ण

/*
 * Jump rates:
 * Sample अक्रमom rates, use those that are faster than the highest
 * currently selected rate. Rates between the fastest and the slowest
 * get sorted पूर्णांकo the slow sample bucket, but only अगर it has room
 */
अटल u16
minstrel_ht_next_jump_rate(काष्ठा minstrel_ht_sta *mi, u32 fast_rate_dur,
			   u32 slow_rate_dur, पूर्णांक *slow_rate_ofs)
अणु
	काष्ठा minstrel_rate_stats *mrs;
	u32 max_duration = slow_rate_dur;
	पूर्णांक i, index, offset;
	u16 *slow_rates;
	u16 supported;
	u32 duration;
	u8 group;

	अगर (*slow_rate_ofs >= MINSTREL_SAMPLE_RATES)
		max_duration = fast_rate_dur;

	slow_rates = mi->sample[MINSTREL_SAMPLE_TYPE_SLOW].sample_rates;
	group = mi->sample[MINSTREL_SAMPLE_TYPE_JUMP].sample_group;
	क्रम (i = 0; i < ARRAY_SIZE(minstrel_mcs_groups); i++) अणु
		u8 type;

		group = (group + 1) % ARRAY_SIZE(minstrel_mcs_groups);

		supported = mi->supported[group];
		अगर (!supported)
			जारी;

		offset = minstrel_ht_group_min_rate_offset(mi, group,
							   max_duration);
		अगर (offset < 0)
			जारी;

		index = minstrel_ht_next_group_sample_rate(mi, group, supported,
							   offset);
		अगर (index < 0)
			जारी;

		duration = minstrel_get_duration(index);
		अगर (duration < fast_rate_dur)
			type = MINSTREL_SAMPLE_TYPE_JUMP;
		अन्यथा
			type = MINSTREL_SAMPLE_TYPE_SLOW;

		अगर (minstrel_ht_find_sample_rate(mi, type, index))
			जारी;

		अगर (type == MINSTREL_SAMPLE_TYPE_JUMP)
			जाओ found;

		अगर (*slow_rate_ofs >= MINSTREL_SAMPLE_RATES)
			जारी;

		अगर (duration >= slow_rate_dur)
			जारी;

		/* skip slow rates with high success probability */
		mrs = minstrel_get_ratestats(mi, index);
		अगर (mrs->prob_avg > MINSTREL_FRAC(95, 100))
			जारी;

		slow_rates[(*slow_rate_ofs)++] = index;
		अगर (*slow_rate_ofs >= MINSTREL_SAMPLE_RATES)
			max_duration = fast_rate_dur;
	पूर्ण
	index = 0;

found:
	mi->sample[MINSTREL_SAMPLE_TYPE_JUMP].sample_group = group;

	वापस index;
पूर्ण

अटल व्योम
minstrel_ht_refill_sample_rates(काष्ठा minstrel_ht_sta *mi)
अणु
	u32 prob_dur = minstrel_get_duration(mi->max_prob_rate);
	u32 tp_dur = minstrel_get_duration(mi->max_tp_rate[0]);
	u32 tp2_dur = minstrel_get_duration(mi->max_tp_rate[1]);
	u32 fast_rate_dur = min(min(tp_dur, tp2_dur), prob_dur);
	u32 slow_rate_dur = max(max(tp_dur, tp2_dur), prob_dur);
	u16 *rates;
	पूर्णांक i, j;

	rates = mi->sample[MINSTREL_SAMPLE_TYPE_INC].sample_rates;
	i = minstrel_ht_move_sample_rates(mi, MINSTREL_SAMPLE_TYPE_INC,
					  fast_rate_dur, slow_rate_dur);
	जबतक (i < MINSTREL_SAMPLE_RATES) अणु
		rates[i] = minstrel_ht_next_inc_rate(mi, tp_dur);
		अगर (!rates[i])
			अवरोध;

		i++;
	पूर्ण

	rates = mi->sample[MINSTREL_SAMPLE_TYPE_JUMP].sample_rates;
	i = minstrel_ht_move_sample_rates(mi, MINSTREL_SAMPLE_TYPE_JUMP,
					  fast_rate_dur, slow_rate_dur);
	j = minstrel_ht_move_sample_rates(mi, MINSTREL_SAMPLE_TYPE_SLOW,
					  fast_rate_dur, slow_rate_dur);
	जबतक (i < MINSTREL_SAMPLE_RATES) अणु
		rates[i] = minstrel_ht_next_jump_rate(mi, fast_rate_dur,
						      slow_rate_dur, &j);
		अगर (!rates[i])
			अवरोध;

		i++;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(mi->sample); i++)
		स_नकल(mi->sample[i].cur_sample_rates, mi->sample[i].sample_rates,
		       माप(mi->sample[i].cur_sample_rates));
पूर्ण


/*
 * Update rate statistics and select new primary rates
 *
 * Rules क्रम rate selection:
 *  - max_prob_rate must use only one stream, as a tradeoff between delivery
 *    probability and throughput during strong fluctuations
 *  - as दीर्घ as the max prob rate has a probability of more than 75%, pick
 *    higher throughput rates, even अगर the probablity is a bit lower
 */
अटल व्योम
minstrel_ht_update_stats(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi)
अणु
	काष्ठा minstrel_mcs_group_data *mg;
	काष्ठा minstrel_rate_stats *mrs;
	पूर्णांक group, i, j, cur_prob;
	u16 पंचांगp_mcs_tp_rate[MAX_THR_RATES], पंचांगp_group_tp_rate[MAX_THR_RATES];
	u16 पंचांगp_legacy_tp_rate[MAX_THR_RATES], पंचांगp_max_prob_rate;
	u16 index;
	bool ht_supported = mi->sta->ht_cap.ht_supported;

	अगर (mi->ampdu_packets > 0) अणु
		अगर (!ieee80211_hw_check(mp->hw, TX_STATUS_NO_AMPDU_LEN))
			mi->avg_ampdu_len = minstrel_ewma(mi->avg_ampdu_len,
				MINSTREL_FRAC(mi->ampdu_len, mi->ampdu_packets),
					      EWMA_LEVEL);
		अन्यथा
			mi->avg_ampdu_len = 0;
		mi->ampdu_len = 0;
		mi->ampdu_packets = 0;
	पूर्ण

	अगर (mi->supported[MINSTREL_CCK_GROUP])
		group = MINSTREL_CCK_GROUP;
	अन्यथा अगर (mi->supported[MINSTREL_OFDM_GROUP])
		group = MINSTREL_OFDM_GROUP;
	अन्यथा
		group = 0;

	index = MI_RATE(group, 0);
	क्रम (j = 0; j < ARRAY_SIZE(पंचांगp_legacy_tp_rate); j++)
		पंचांगp_legacy_tp_rate[j] = index;

	अगर (mi->supported[MINSTREL_VHT_GROUP_0])
		group = MINSTREL_VHT_GROUP_0;
	अन्यथा अगर (ht_supported)
		group = MINSTREL_HT_GROUP_0;
	अन्यथा अगर (mi->supported[MINSTREL_CCK_GROUP])
		group = MINSTREL_CCK_GROUP;
	अन्यथा
		group = MINSTREL_OFDM_GROUP;

	index = MI_RATE(group, 0);
	पंचांगp_max_prob_rate = index;
	क्रम (j = 0; j < ARRAY_SIZE(पंचांगp_mcs_tp_rate); j++)
		पंचांगp_mcs_tp_rate[j] = index;

	/* Find best rate sets within all MCS groups*/
	क्रम (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) अणु
		u16 *tp_rate = पंचांगp_mcs_tp_rate;
		u16 last_prob = 0;

		mg = &mi->groups[group];
		अगर (!mi->supported[group])
			जारी;

		/* (re)Initialize group rate indexes */
		क्रम(j = 0; j < MAX_THR_RATES; j++)
			पंचांगp_group_tp_rate[j] = MI_RATE(group, 0);

		अगर (group == MINSTREL_CCK_GROUP && ht_supported)
			tp_rate = पंचांगp_legacy_tp_rate;

		क्रम (i = MCS_GROUP_RATES - 1; i >= 0; i--) अणु
			अगर (!(mi->supported[group] & BIT(i)))
				जारी;

			index = MI_RATE(group, i);

			mrs = &mg->rates[i];
			mrs->retry_updated = false;
			minstrel_ht_calc_rate_stats(mp, mrs);

			अगर (mrs->att_hist)
				last_prob = max(last_prob, mrs->prob_avg);
			अन्यथा
				mrs->prob_avg = max(last_prob, mrs->prob_avg);
			cur_prob = mrs->prob_avg;

			अगर (minstrel_ht_get_tp_avg(mi, group, i, cur_prob) == 0)
				जारी;

			/* Find max throughput rate set */
			minstrel_ht_sort_best_tp_rates(mi, index, tp_rate);

			/* Find max throughput rate set within a group */
			minstrel_ht_sort_best_tp_rates(mi, index,
						       पंचांगp_group_tp_rate);
		पूर्ण

		स_नकल(mg->max_group_tp_rate, पंचांगp_group_tp_rate,
		       माप(mg->max_group_tp_rate));
	पूर्ण

	/* Assign new rate set per sta */
	minstrel_ht_assign_best_tp_rates(mi, पंचांगp_mcs_tp_rate,
					 पंचांगp_legacy_tp_rate);
	स_नकल(mi->max_tp_rate, पंचांगp_mcs_tp_rate, माप(mi->max_tp_rate));

	क्रम (group = 0; group < ARRAY_SIZE(minstrel_mcs_groups); group++) अणु
		अगर (!mi->supported[group])
			जारी;

		mg = &mi->groups[group];
		mg->max_group_prob_rate = MI_RATE(group, 0);

		क्रम (i = 0; i < MCS_GROUP_RATES; i++) अणु
			अगर (!(mi->supported[group] & BIT(i)))
				जारी;

			index = MI_RATE(group, i);

			/* Find max probability rate per group and global */
			minstrel_ht_set_best_prob_rate(mi, &पंचांगp_max_prob_rate,
						       index);
		पूर्ण
	पूर्ण

	mi->max_prob_rate = पंचांगp_max_prob_rate;

	/* Try to increase robustness of max_prob_rate*/
	minstrel_ht_prob_rate_reduce_streams(mi);
	minstrel_ht_refill_sample_rates(mi);

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	/* use fixed index अगर set */
	अगर (mp->fixed_rate_idx != -1) अणु
		क्रम (i = 0; i < 4; i++)
			mi->max_tp_rate[i] = mp->fixed_rate_idx;
		mi->max_prob_rate = mp->fixed_rate_idx;
	पूर्ण
#पूर्ण_अगर

	/* Reset update समयr */
	mi->last_stats_update = jअगरfies;
	mi->sample_समय = jअगरfies;
पूर्ण

अटल bool
minstrel_ht_txstat_valid(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi,
			 काष्ठा ieee80211_tx_rate *rate)
अणु
	पूर्णांक i;

	अगर (rate->idx < 0)
		वापस false;

	अगर (!rate->count)
		वापस false;

	अगर (rate->flags & IEEE80211_TX_RC_MCS ||
	    rate->flags & IEEE80211_TX_RC_VHT_MCS)
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(mp->cck_rates); i++)
		अगर (rate->idx == mp->cck_rates[i])
			वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(mp->ofdm_rates[0]); i++)
		अगर (rate->idx == mp->ofdm_rates[mi->band][i])
			वापस true;

	वापस false;
पूर्ण

अटल व्योम
minstrel_करोwngrade_rate(काष्ठा minstrel_ht_sta *mi, u16 *idx, bool primary)
अणु
	पूर्णांक group, orig_group;

	orig_group = group = MI_RATE_GROUP(*idx);
	जबतक (group > 0) अणु
		group--;

		अगर (!mi->supported[group])
			जारी;

		अगर (minstrel_mcs_groups[group].streams >
		    minstrel_mcs_groups[orig_group].streams)
			जारी;

		अगर (primary)
			*idx = mi->groups[group].max_group_tp_rate[0];
		अन्यथा
			*idx = mi->groups[group].max_group_tp_rate[1];
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
minstrel_aggr_check(काष्ठा ieee80211_sta *pubsta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	u16 tid;

	अगर (skb_get_queue_mapping(skb) == IEEE80211_AC_VO)
		वापस;

	अगर (unlikely(!ieee80211_is_data_qos(hdr->frame_control)))
		वापस;

	अगर (unlikely(skb->protocol == cpu_to_be16(ETH_P_PAE)))
		वापस;

	tid = ieee80211_get_tid(hdr);
	अगर (likely(sta->ampdu_mlme.tid_tx[tid]))
		वापस;

	ieee80211_start_tx_ba_session(pubsta, tid, 0);
पूर्ण

अटल व्योम
minstrel_ht_tx_status(व्योम *priv, काष्ठा ieee80211_supported_band *sband,
                      व्योम *priv_sta, काष्ठा ieee80211_tx_status *st)
अणु
	काष्ठा ieee80211_tx_info *info = st->info;
	काष्ठा minstrel_ht_sta *mi = priv_sta;
	काष्ठा ieee80211_tx_rate *ar = info->status.rates;
	काष्ठा minstrel_rate_stats *rate, *rate2;
	काष्ठा minstrel_priv *mp = priv;
	u32 update_पूर्णांकerval = mp->update_पूर्णांकerval;
	bool last, update = false;
	पूर्णांक i;

	/* This packet was aggregated but करोesn't carry status info */
	अगर ((info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !(info->flags & IEEE80211_TX_STAT_AMPDU))
		वापस;

	अगर (!(info->flags & IEEE80211_TX_STAT_AMPDU)) अणु
		info->status.ampdu_ack_len =
			(info->flags & IEEE80211_TX_STAT_ACK ? 1 : 0);
		info->status.ampdu_len = 1;
	पूर्ण

	/* wraparound */
	अगर (mi->total_packets >= ~0 - info->status.ampdu_len) अणु
		mi->total_packets = 0;
		mi->sample_packets = 0;
	पूर्ण

	mi->total_packets += info->status.ampdu_len;
	अगर (info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)
		mi->sample_packets += info->status.ampdu_len;

	mi->ampdu_packets++;
	mi->ampdu_len += info->status.ampdu_len;

	last = !minstrel_ht_txstat_valid(mp, mi, &ar[0]);
	क्रम (i = 0; !last; i++) अणु
		last = (i == IEEE80211_TX_MAX_RATES - 1) ||
		       !minstrel_ht_txstat_valid(mp, mi, &ar[i + 1]);

		rate = minstrel_ht_get_stats(mp, mi, &ar[i]);
		अगर (last)
			rate->success += info->status.ampdu_ack_len;

		rate->attempts += ar[i].count * info->status.ampdu_len;
	पूर्ण

	अगर (mp->hw->max_rates > 1) अणु
		/*
		 * check क्रम sudden death of spatial multiplexing,
		 * करोwngrade to a lower number of streams अगर necessary.
		 */
		rate = minstrel_get_ratestats(mi, mi->max_tp_rate[0]);
		अगर (rate->attempts > 30 &&
		    rate->success < rate->attempts / 4) अणु
			minstrel_करोwngrade_rate(mi, &mi->max_tp_rate[0], true);
			update = true;
		पूर्ण

		rate2 = minstrel_get_ratestats(mi, mi->max_tp_rate[1]);
		अगर (rate2->attempts > 30 &&
		    rate2->success < rate2->attempts / 4) अणु
			minstrel_करोwngrade_rate(mi, &mi->max_tp_rate[1], false);
			update = true;
		पूर्ण
	पूर्ण

	अगर (समय_after(jअगरfies, mi->last_stats_update + update_पूर्णांकerval)) अणु
		update = true;
		minstrel_ht_update_stats(mp, mi);
	पूर्ण

	अगर (update)
		minstrel_ht_update_rates(mp, mi);
पूर्ण

अटल व्योम
minstrel_calc_retransmit(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi,
                         पूर्णांक index)
अणु
	काष्ठा minstrel_rate_stats *mrs;
	अचिन्हित पूर्णांक tx_समय, tx_समय_rtscts, tx_समय_data;
	अचिन्हित पूर्णांक cw = mp->cw_min;
	अचिन्हित पूर्णांक स_समय = 0;
	अचिन्हित पूर्णांक t_slot = 9; /* FIXME */
	अचिन्हित पूर्णांक ampdu_len = minstrel_ht_avg_ampdu_len(mi);
	अचिन्हित पूर्णांक overhead = 0, overhead_rtscts = 0;

	mrs = minstrel_get_ratestats(mi, index);
	अगर (mrs->prob_avg < MINSTREL_FRAC(1, 10)) अणु
		mrs->retry_count = 1;
		mrs->retry_count_rtscts = 1;
		वापस;
	पूर्ण

	mrs->retry_count = 2;
	mrs->retry_count_rtscts = 2;
	mrs->retry_updated = true;

	tx_समय_data = minstrel_get_duration(index) * ampdu_len / 1000;

	/* Contention समय क्रम first 2 tries */
	स_समय = (t_slot * cw) >> 1;
	cw = min((cw << 1) | 1, mp->cw_max);
	स_समय += (t_slot * cw) >> 1;
	cw = min((cw << 1) | 1, mp->cw_max);

	अगर (minstrel_ht_is_legacy_group(MI_RATE_GROUP(index))) अणु
		overhead = mi->overhead_legacy;
		overhead_rtscts = mi->overhead_legacy_rtscts;
	पूर्ण अन्यथा अणु
		overhead = mi->overhead;
		overhead_rtscts = mi->overhead_rtscts;
	पूर्ण

	/* Total TX समय क्रम data and Contention after first 2 tries */
	tx_समय = स_समय + 2 * (overhead + tx_समय_data);
	tx_समय_rtscts = स_समय + 2 * (overhead_rtscts + tx_समय_data);

	/* See how many more tries we can fit inside segment size */
	करो अणु
		/* Contention समय क्रम this try */
		स_समय = (t_slot * cw) >> 1;
		cw = min((cw << 1) | 1, mp->cw_max);

		/* Total TX समय after this try */
		tx_समय += स_समय + overhead + tx_समय_data;
		tx_समय_rtscts += स_समय + overhead_rtscts + tx_समय_data;

		अगर (tx_समय_rtscts < mp->segment_size)
			mrs->retry_count_rtscts++;
	पूर्ण जबतक ((tx_समय < mp->segment_size) &&
	         (++mrs->retry_count < mp->max_retry));
पूर्ण


अटल व्योम
minstrel_ht_set_rate(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi,
                     काष्ठा ieee80211_sta_rates *ratetbl, पूर्णांक offset, पूर्णांक index)
अणु
	पूर्णांक group_idx = MI_RATE_GROUP(index);
	स्थिर काष्ठा mcs_group *group = &minstrel_mcs_groups[group_idx];
	काष्ठा minstrel_rate_stats *mrs;
	u8 idx;
	u16 flags = group->flags;

	mrs = minstrel_get_ratestats(mi, index);
	अगर (!mrs->retry_updated)
		minstrel_calc_retransmit(mp, mi, index);

	अगर (mrs->prob_avg < MINSTREL_FRAC(20, 100) || !mrs->retry_count) अणु
		ratetbl->rate[offset].count = 2;
		ratetbl->rate[offset].count_rts = 2;
		ratetbl->rate[offset].count_cts = 2;
	पूर्ण अन्यथा अणु
		ratetbl->rate[offset].count = mrs->retry_count;
		ratetbl->rate[offset].count_cts = mrs->retry_count;
		ratetbl->rate[offset].count_rts = mrs->retry_count_rtscts;
	पूर्ण

	index = MI_RATE_IDX(index);
	अगर (group_idx == MINSTREL_CCK_GROUP)
		idx = mp->cck_rates[index % ARRAY_SIZE(mp->cck_rates)];
	अन्यथा अगर (group_idx == MINSTREL_OFDM_GROUP)
		idx = mp->ofdm_rates[mi->band][index %
					       ARRAY_SIZE(mp->ofdm_rates[0])];
	अन्यथा अगर (flags & IEEE80211_TX_RC_VHT_MCS)
		idx = ((group->streams - 1) << 4) |
		      (index & 0xF);
	अन्यथा
		idx = index + (group->streams - 1) * 8;

	/* enable RTS/CTS अगर needed:
	 *  - अगर station is in dynamic SMPS (and streams > 1)
	 *  - क्रम fallback rates, to increase chances of getting through
	 */
	अगर (offset > 0 ||
	    (mi->sta->smps_mode == IEEE80211_SMPS_DYNAMIC &&
	     group->streams > 1)) अणु
		ratetbl->rate[offset].count = ratetbl->rate[offset].count_rts;
		flags |= IEEE80211_TX_RC_USE_RTS_CTS;
	पूर्ण

	ratetbl->rate[offset].idx = idx;
	ratetbl->rate[offset].flags = flags;
पूर्ण

अटल अंतरभूत पूर्णांक
minstrel_ht_get_prob_avg(काष्ठा minstrel_ht_sta *mi, पूर्णांक rate)
अणु
	पूर्णांक group = MI_RATE_GROUP(rate);
	rate = MI_RATE_IDX(rate);
	वापस mi->groups[group].rates[rate].prob_avg;
पूर्ण

अटल पूर्णांक
minstrel_ht_get_max_amsdu_len(काष्ठा minstrel_ht_sta *mi)
अणु
	पूर्णांक group = MI_RATE_GROUP(mi->max_prob_rate);
	स्थिर काष्ठा mcs_group *g = &minstrel_mcs_groups[group];
	पूर्णांक rate = MI_RATE_IDX(mi->max_prob_rate);
	अचिन्हित पूर्णांक duration;

	/* Disable A-MSDU अगर max_prob_rate is bad */
	अगर (mi->groups[group].rates[rate].prob_avg < MINSTREL_FRAC(50, 100))
		वापस 1;

	duration = g->duration[rate];
	duration <<= g->shअगरt;

	/* If the rate is slower than single-stream MCS1, make A-MSDU limit small */
	अगर (duration > MCS_DURATION(1, 0, 52))
		वापस 500;

	/*
	 * If the rate is slower than single-stream MCS4, limit A-MSDU to usual
	 * data packet size
	 */
	अगर (duration > MCS_DURATION(1, 0, 104))
		वापस 1600;

	/*
	 * If the rate is slower than single-stream MCS7, or अगर the max throughput
	 * rate success probability is less than 75%, limit A-MSDU to twice the usual
	 * data packet size
	 */
	अगर (duration > MCS_DURATION(1, 0, 260) ||
	    (minstrel_ht_get_prob_avg(mi, mi->max_tp_rate[0]) <
	     MINSTREL_FRAC(75, 100)))
		वापस 3200;

	/*
	 * HT A-MPDU limits maximum MPDU size under BA agreement to 4095 bytes.
	 * Since aggregation sessions are started/stopped without txq flush, use
	 * the limit here to aव्योम the complनिकासy of having to de-aggregate
	 * packets in the queue.
	 */
	अगर (!mi->sta->vht_cap.vht_supported)
		वापस IEEE80211_MAX_MPDU_LEN_HT_BA;

	/* unlimited */
	वापस 0;
पूर्ण

अटल व्योम
minstrel_ht_update_rates(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi)
अणु
	काष्ठा ieee80211_sta_rates *rates;
	पूर्णांक i = 0;

	rates = kzalloc(माप(*rates), GFP_ATOMIC);
	अगर (!rates)
		वापस;

	/* Start with max_tp_rate[0] */
	minstrel_ht_set_rate(mp, mi, rates, i++, mi->max_tp_rate[0]);

	अगर (mp->hw->max_rates >= 3) अणु
		/* At least 3 tx rates supported, use max_tp_rate[1] next */
		minstrel_ht_set_rate(mp, mi, rates, i++, mi->max_tp_rate[1]);
	पूर्ण

	अगर (mp->hw->max_rates >= 2) अणु
		minstrel_ht_set_rate(mp, mi, rates, i++, mi->max_prob_rate);
	पूर्ण

	mi->sta->max_rc_amsdu_len = minstrel_ht_get_max_amsdu_len(mi);
	rates->rate[i].idx = -1;
	rate_control_set_rates(mp->hw, mi->sta, rates);
पूर्ण

अटल u16
minstrel_ht_get_sample_rate(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi)
अणु
	u8 seq;

	अगर (mp->hw->max_rates > 1) अणु
		seq = mi->sample_seq;
		mi->sample_seq = (seq + 1) % ARRAY_SIZE(minstrel_sample_seq);
		seq = minstrel_sample_seq[seq];
	पूर्ण अन्यथा अणु
		seq = MINSTREL_SAMPLE_TYPE_INC;
	पूर्ण

	वापस __minstrel_ht_get_sample_rate(mi, seq);
पूर्ण

अटल व्योम
minstrel_ht_get_rate(व्योम *priv, काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
                     काष्ठा ieee80211_tx_rate_control *txrc)
अणु
	स्थिर काष्ठा mcs_group *sample_group;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(txrc->skb);
	काष्ठा ieee80211_tx_rate *rate = &info->status.rates[0];
	काष्ठा minstrel_ht_sta *mi = priv_sta;
	काष्ठा minstrel_priv *mp = priv;
	u16 sample_idx;

	अगर (!(info->flags & IEEE80211_TX_CTL_AMPDU) &&
	    !minstrel_ht_is_legacy_group(MI_RATE_GROUP(mi->max_prob_rate)))
		minstrel_aggr_check(sta, txrc->skb);

	info->flags |= mi->tx_flags;

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	अगर (mp->fixed_rate_idx != -1)
		वापस;
#पूर्ण_अगर

	/* Don't use EAPOL frames क्रम sampling on non-mrr hw */
	अगर (mp->hw->max_rates == 1 &&
	    (info->control.flags & IEEE80211_TX_CTRL_PORT_CTRL_PROTO))
		वापस;

	अगर (समय_is_after_jअगरfies(mi->sample_समय))
		वापस;

	mi->sample_समय = jअगरfies + MINSTREL_SAMPLE_INTERVAL;
	sample_idx = minstrel_ht_get_sample_rate(mp, mi);
	अगर (!sample_idx)
		वापस;

	sample_group = &minstrel_mcs_groups[MI_RATE_GROUP(sample_idx)];
	sample_idx = MI_RATE_IDX(sample_idx);

	अगर (sample_group == &minstrel_mcs_groups[MINSTREL_CCK_GROUP] &&
	    (sample_idx >= 4) != txrc->लघु_preamble)
		वापस;

	info->flags |= IEEE80211_TX_CTL_RATE_CTRL_PROBE;
	rate->count = 1;

	अगर (sample_group == &minstrel_mcs_groups[MINSTREL_CCK_GROUP]) अणु
		पूर्णांक idx = sample_idx % ARRAY_SIZE(mp->cck_rates);
		rate->idx = mp->cck_rates[idx];
	पूर्ण अन्यथा अगर (sample_group == &minstrel_mcs_groups[MINSTREL_OFDM_GROUP]) अणु
		पूर्णांक idx = sample_idx % ARRAY_SIZE(mp->ofdm_rates[0]);
		rate->idx = mp->ofdm_rates[mi->band][idx];
	पूर्ण अन्यथा अगर (sample_group->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		ieee80211_rate_set_vht(rate, MI_RATE_IDX(sample_idx),
				       sample_group->streams);
	पूर्ण अन्यथा अणु
		rate->idx = sample_idx + (sample_group->streams - 1) * 8;
	पूर्ण

	rate->flags = sample_group->flags;
पूर्ण

अटल व्योम
minstrel_ht_update_cck(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi,
		       काष्ठा ieee80211_supported_band *sband,
		       काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक i;

	अगर (sband->band != NL80211_BAND_2GHZ)
		वापस;

	अगर (sta->ht_cap.ht_supported &&
	    !ieee80211_hw_check(mp->hw, SUPPORTS_HT_CCK_RATES))
		वापस;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (mp->cck_rates[i] == 0xff ||
		    !rate_supported(sta, sband->band, mp->cck_rates[i]))
			जारी;

		mi->supported[MINSTREL_CCK_GROUP] |= BIT(i);
		अगर (sband->bitrates[i].flags & IEEE80211_RATE_SHORT_PREAMBLE)
			mi->supported[MINSTREL_CCK_GROUP] |= BIT(i + 4);
	पूर्ण
पूर्ण

अटल व्योम
minstrel_ht_update_ofdm(काष्ठा minstrel_priv *mp, काष्ठा minstrel_ht_sta *mi,
			काष्ठा ieee80211_supported_band *sband,
			काष्ठा ieee80211_sta *sta)
अणु
	स्थिर u8 *rates;
	पूर्णांक i;

	अगर (sta->ht_cap.ht_supported)
		वापस;

	rates = mp->ofdm_rates[sband->band];
	क्रम (i = 0; i < ARRAY_SIZE(mp->ofdm_rates[0]); i++) अणु
		अगर (rates[i] == 0xff ||
		    !rate_supported(sta, sband->band, rates[i]))
			जारी;

		mi->supported[MINSTREL_OFDM_GROUP] |= BIT(i);
	पूर्ण
पूर्ण

अटल व्योम
minstrel_ht_update_caps(व्योम *priv, काष्ठा ieee80211_supported_band *sband,
			काष्ठा cfg80211_chan_def *chandef,
			काष्ठा ieee80211_sta *sta, व्योम *priv_sta)
अणु
	काष्ठा minstrel_priv *mp = priv;
	काष्ठा minstrel_ht_sta *mi = priv_sta;
	काष्ठा ieee80211_mcs_info *mcs = &sta->ht_cap.mcs;
	u16 ht_cap = sta->ht_cap.cap;
	काष्ठा ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	स्थिर काष्ठा ieee80211_rate *ctl_rate;
	bool ldpc, erp;
	पूर्णांक use_vht;
	पूर्णांक n_supported = 0;
	पूर्णांक ack_dur;
	पूर्णांक stbc;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(minstrel_mcs_groups) != MINSTREL_GROUPS_NB);

	अगर (vht_cap->vht_supported)
		use_vht = vht_cap->vht_mcs.tx_mcs_map != cpu_to_le16(~0);
	अन्यथा
		use_vht = 0;

	स_रखो(mi, 0, माप(*mi));

	mi->sta = sta;
	mi->band = sband->band;
	mi->last_stats_update = jअगरfies;

	ack_dur = ieee80211_frame_duration(sband->band, 10, 60, 1, 1, 0);
	mi->overhead = ieee80211_frame_duration(sband->band, 0, 60, 1, 1, 0);
	mi->overhead += ack_dur;
	mi->overhead_rtscts = mi->overhead + 2 * ack_dur;

	ctl_rate = &sband->bitrates[rate_lowest_index(sband, sta)];
	erp = ctl_rate->flags & IEEE80211_RATE_ERP_G;
	ack_dur = ieee80211_frame_duration(sband->band, 10,
					   ctl_rate->bitrate, erp, 1,
					   ieee80211_chandef_get_shअगरt(chandef));
	mi->overhead_legacy = ack_dur;
	mi->overhead_legacy_rtscts = mi->overhead_legacy + 2 * ack_dur;

	mi->avg_ampdu_len = MINSTREL_FRAC(1, 1);

	अगर (!use_vht) अणु
		stbc = (ht_cap & IEEE80211_HT_CAP_RX_STBC) >>
			IEEE80211_HT_CAP_RX_STBC_SHIFT;

		ldpc = ht_cap & IEEE80211_HT_CAP_LDPC_CODING;
	पूर्ण अन्यथा अणु
		stbc = (vht_cap->cap & IEEE80211_VHT_CAP_RXSTBC_MASK) >>
			IEEE80211_VHT_CAP_RXSTBC_SHIFT;

		ldpc = vht_cap->cap & IEEE80211_VHT_CAP_RXLDPC;
	पूर्ण

	mi->tx_flags |= stbc << IEEE80211_TX_CTL_STBC_SHIFT;
	अगर (ldpc)
		mi->tx_flags |= IEEE80211_TX_CTL_LDPC;

	क्रम (i = 0; i < ARRAY_SIZE(mi->groups); i++) अणु
		u32 gflags = minstrel_mcs_groups[i].flags;
		पूर्णांक bw, nss;

		mi->supported[i] = 0;
		अगर (minstrel_ht_is_legacy_group(i))
			जारी;

		अगर (gflags & IEEE80211_TX_RC_SHORT_GI) अणु
			अगर (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH) अणु
				अगर (!(ht_cap & IEEE80211_HT_CAP_SGI_40))
					जारी;
			पूर्ण अन्यथा अणु
				अगर (!(ht_cap & IEEE80211_HT_CAP_SGI_20))
					जारी;
			पूर्ण
		पूर्ण

		अगर (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH &&
		    sta->bandwidth < IEEE80211_STA_RX_BW_40)
			जारी;

		nss = minstrel_mcs_groups[i].streams;

		/* Mark MCS > 7 as unsupported अगर STA is in अटल SMPS mode */
		अगर (sta->smps_mode == IEEE80211_SMPS_STATIC && nss > 1)
			जारी;

		/* HT rate */
		अगर (gflags & IEEE80211_TX_RC_MCS) अणु
			अगर (use_vht && minstrel_vht_only)
				जारी;

			mi->supported[i] = mcs->rx_mask[nss - 1];
			अगर (mi->supported[i])
				n_supported++;
			जारी;
		पूर्ण

		/* VHT rate */
		अगर (!vht_cap->vht_supported ||
		    WARN_ON(!(gflags & IEEE80211_TX_RC_VHT_MCS)) ||
		    WARN_ON(gflags & IEEE80211_TX_RC_160_MHZ_WIDTH))
			जारी;

		अगर (gflags & IEEE80211_TX_RC_80_MHZ_WIDTH) अणु
			अगर (sta->bandwidth < IEEE80211_STA_RX_BW_80 ||
			    ((gflags & IEEE80211_TX_RC_SHORT_GI) &&
			     !(vht_cap->cap & IEEE80211_VHT_CAP_SHORT_GI_80))) अणु
				जारी;
			पूर्ण
		पूर्ण

		अगर (gflags & IEEE80211_TX_RC_40_MHZ_WIDTH)
			bw = BW_40;
		अन्यथा अगर (gflags & IEEE80211_TX_RC_80_MHZ_WIDTH)
			bw = BW_80;
		अन्यथा
			bw = BW_20;

		mi->supported[i] = minstrel_get_valid_vht_rates(bw, nss,
				vht_cap->vht_mcs.tx_mcs_map);

		अगर (mi->supported[i])
			n_supported++;
	पूर्ण

	minstrel_ht_update_cck(mp, mi, sband, sta);
	minstrel_ht_update_ofdm(mp, mi, sband, sta);

	/* create an initial rate table with the lowest supported rates */
	minstrel_ht_update_stats(mp, mi);
	minstrel_ht_update_rates(mp, mi);
पूर्ण

अटल व्योम
minstrel_ht_rate_init(व्योम *priv, काष्ठा ieee80211_supported_band *sband,
		      काष्ठा cfg80211_chan_def *chandef,
                      काष्ठा ieee80211_sta *sta, व्योम *priv_sta)
अणु
	minstrel_ht_update_caps(priv, sband, chandef, sta, priv_sta);
पूर्ण

अटल व्योम
minstrel_ht_rate_update(व्योम *priv, काष्ठा ieee80211_supported_band *sband,
			काष्ठा cfg80211_chan_def *chandef,
                        काष्ठा ieee80211_sta *sta, व्योम *priv_sta,
                        u32 changed)
अणु
	minstrel_ht_update_caps(priv, sband, chandef, sta, priv_sta);
पूर्ण

अटल व्योम *
minstrel_ht_alloc_sta(व्योम *priv, काष्ठा ieee80211_sta *sta, gfp_t gfp)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा minstrel_ht_sta *mi;
	काष्ठा minstrel_priv *mp = priv;
	काष्ठा ieee80211_hw *hw = mp->hw;
	पूर्णांक max_rates = 0;
	पूर्णांक i;

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		sband = hw->wiphy->bands[i];
		अगर (sband && sband->n_bitrates > max_rates)
			max_rates = sband->n_bitrates;
	पूर्ण

	वापस kzalloc(माप(*mi), gfp);
पूर्ण

अटल व्योम
minstrel_ht_मुक्त_sta(व्योम *priv, काष्ठा ieee80211_sta *sta, व्योम *priv_sta)
अणु
	kमुक्त(priv_sta);
पूर्ण

अटल व्योम
minstrel_ht_fill_rate_array(u8 *dest, काष्ठा ieee80211_supported_band *sband,
			    स्थिर s16 *bitrates, पूर्णांक n_rates, u32 rate_flags)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		काष्ठा ieee80211_rate *rate = &sband->bitrates[i];

		अगर ((rate_flags & sband->bitrates[i].flags) != rate_flags)
			जारी;

		क्रम (j = 0; j < n_rates; j++) अणु
			अगर (rate->bitrate != bitrates[j])
				जारी;

			dest[j] = i;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
minstrel_ht_init_cck_rates(काष्ठा minstrel_priv *mp)
अणु
	अटल स्थिर s16 bitrates[4] = अणु 10, 20, 55, 110 पूर्ण;
	काष्ठा ieee80211_supported_band *sband;
	u32 rate_flags = ieee80211_chandef_rate_flags(&mp->hw->conf.chandef);

	स_रखो(mp->cck_rates, 0xff, माप(mp->cck_rates));
	sband = mp->hw->wiphy->bands[NL80211_BAND_2GHZ];
	अगर (!sband)
		वापस;

	BUILD_BUG_ON(ARRAY_SIZE(mp->cck_rates) != ARRAY_SIZE(bitrates));
	minstrel_ht_fill_rate_array(mp->cck_rates, sband,
				    minstrel_cck_bitrates,
				    ARRAY_SIZE(minstrel_cck_bitrates),
				    rate_flags);
पूर्ण

अटल व्योम
minstrel_ht_init_ofdm_rates(काष्ठा minstrel_priv *mp, क्रमागत nl80211_band band)
अणु
	अटल स्थिर s16 bitrates[8] = अणु 60, 90, 120, 180, 240, 360, 480, 540 पूर्ण;
	काष्ठा ieee80211_supported_band *sband;
	u32 rate_flags = ieee80211_chandef_rate_flags(&mp->hw->conf.chandef);

	स_रखो(mp->ofdm_rates[band], 0xff, माप(mp->ofdm_rates[band]));
	sband = mp->hw->wiphy->bands[band];
	अगर (!sband)
		वापस;

	BUILD_BUG_ON(ARRAY_SIZE(mp->ofdm_rates[band]) != ARRAY_SIZE(bitrates));
	minstrel_ht_fill_rate_array(mp->ofdm_rates[band], sband,
				    minstrel_ofdm_bitrates,
				    ARRAY_SIZE(minstrel_ofdm_bitrates),
				    rate_flags);
पूर्ण

अटल व्योम *
minstrel_ht_alloc(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा minstrel_priv *mp;
	पूर्णांक i;

	mp = kzalloc(माप(काष्ठा minstrel_priv), GFP_ATOMIC);
	अगर (!mp)
		वापस शून्य;

	/* contention winकरोw settings
	 * Just an approximation. Using the per-queue values would complicate
	 * the calculations and is probably unnecessary */
	mp->cw_min = 15;
	mp->cw_max = 1023;

	/* maximum समय that the hw is allowed to stay in one MRR segment */
	mp->segment_size = 6000;

	अगर (hw->max_rate_tries > 0)
		mp->max_retry = hw->max_rate_tries;
	अन्यथा
		/* safe शेष, करोes not necessarily have to match hw properties */
		mp->max_retry = 7;

	अगर (hw->max_rates >= 4)
		mp->has_mrr = true;

	mp->hw = hw;
	mp->update_पूर्णांकerval = HZ / 20;

	minstrel_ht_init_cck_rates(mp);
	क्रम (i = 0; i < ARRAY_SIZE(mp->hw->wiphy->bands); i++)
	    minstrel_ht_init_ofdm_rates(mp, i);

	वापस mp;
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
अटल व्योम minstrel_ht_add_debugfs(काष्ठा ieee80211_hw *hw, व्योम *priv,
				    काष्ठा dentry *debugfsdir)
अणु
	काष्ठा minstrel_priv *mp = priv;

	mp->fixed_rate_idx = (u32) -1;
	debugfs_create_u32("fixed_rate_idx", S_IRUGO | S_IWUGO, debugfsdir,
			   &mp->fixed_rate_idx);
पूर्ण
#पूर्ण_अगर

अटल व्योम
minstrel_ht_मुक्त(व्योम *priv)
अणु
	kमुक्त(priv);
पूर्ण

अटल u32 minstrel_ht_get_expected_throughput(व्योम *priv_sta)
अणु
	काष्ठा minstrel_ht_sta *mi = priv_sta;
	पूर्णांक i, j, prob, tp_avg;

	i = MI_RATE_GROUP(mi->max_tp_rate[0]);
	j = MI_RATE_IDX(mi->max_tp_rate[0]);
	prob = mi->groups[i].rates[j].prob_avg;

	/* convert tp_avg from pkt per second in kbps */
	tp_avg = minstrel_ht_get_tp_avg(mi, i, j, prob) * 10;
	tp_avg = tp_avg * AVG_PKT_SIZE * 8 / 1024;

	वापस tp_avg;
पूर्ण

अटल स्थिर काष्ठा rate_control_ops mac80211_minstrel_ht = अणु
	.name = "minstrel_ht",
	.tx_status_ext = minstrel_ht_tx_status,
	.get_rate = minstrel_ht_get_rate,
	.rate_init = minstrel_ht_rate_init,
	.rate_update = minstrel_ht_rate_update,
	.alloc_sta = minstrel_ht_alloc_sta,
	.मुक्त_sta = minstrel_ht_मुक्त_sta,
	.alloc = minstrel_ht_alloc,
	.मुक्त = minstrel_ht_मुक्त,
#अगर_घोषित CONFIG_MAC80211_DEBUGFS
	.add_debugfs = minstrel_ht_add_debugfs,
	.add_sta_debugfs = minstrel_ht_add_sta_debugfs,
#पूर्ण_अगर
	.get_expected_throughput = minstrel_ht_get_expected_throughput,
पूर्ण;


अटल व्योम __init init_sample_table(व्योम)
अणु
	पूर्णांक col, i, new_idx;
	u8 rnd[MCS_GROUP_RATES];

	स_रखो(sample_table, 0xff, माप(sample_table));
	क्रम (col = 0; col < SAMPLE_COLUMNS; col++) अणु
		pअक्रमom_bytes(rnd, माप(rnd));
		क्रम (i = 0; i < MCS_GROUP_RATES; i++) अणु
			new_idx = (i + rnd[i]) % MCS_GROUP_RATES;
			जबतक (sample_table[col][new_idx] != 0xff)
				new_idx = (new_idx + 1) % MCS_GROUP_RATES;

			sample_table[col][new_idx] = i;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __init
rc80211_minstrel_init(व्योम)
अणु
	init_sample_table();
	वापस ieee80211_rate_control_रेजिस्टर(&mac80211_minstrel_ht);
पूर्ण

व्योम
rc80211_minstrel_निकास(व्योम)
अणु
	ieee80211_rate_control_unरेजिस्टर(&mac80211_minstrel_ht);
पूर्ण
