<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2019 Felix Fietkau <nbd@nbd.name>
 */

#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "sta_info.h"

#घोषणा AVG_PKT_SIZE	1024

/* Number of bits क्रम an average sized packet */
#घोषणा MCS_NBITS (AVG_PKT_SIZE << 3)

/* Number of kilo-symbols (symbols * 1024) क्रम a packet with (bps) bits per
 * symbol. We use k-symbols to aव्योम rounding in the _TIME macros below.
 */
#घोषणा MCS_N_KSYMS(bps) DIV_ROUND_UP(MCS_NBITS << 10, (bps))

/* Transmission समय (in 1024 * usec) क्रम a packet containing (ksyms) * 1024
 * symbols.
 */
#घोषणा MCS_SYMBOL_TIME(sgi, ksyms)					\
	(sgi ?								\
	  ((ksyms) * 4 * 18) / 20 :		/* 3.6 us per sym */	\
	  ((ksyms) * 4)			/* 4.0 us per sym */	\
	)

/* Transmit duration क्रम the raw data part of an average sized packet */
#घोषणा MCS_DURATION(streams, sgi, bps) \
	((u32)MCS_SYMBOL_TIME(sgi, MCS_N_KSYMS((streams) * (bps))))

#घोषणा MCS_DURATION_S(shअगरt, streams, sgi, bps)		\
	((u16)((MCS_DURATION(streams, sgi, bps) >> shअगरt)))

/* These should match the values in क्रमागत nl80211_he_gi */
#घोषणा HE_GI_08 0
#घोषणा HE_GI_16 1
#घोषणा HE_GI_32 2

/* Transmission समय (1024 usec) क्रम a packet containing (ksyms) * k-symbols */
#घोषणा HE_SYMBOL_TIME(gi, ksyms)					\
	(gi == HE_GI_08 ?						\
	 ((ksyms) * 16 * 17) / 20 :		/* 13.6 us per sym */	\
	 (gi == HE_GI_16 ?						\
	  ((ksyms) * 16 * 18) / 20 :		/* 14.4 us per sym */	\
	  ((ksyms) * 16)			/* 16.0 us per sym */	\
	 ))

/* Transmit duration क्रम the raw data part of an average sized packet */
#घोषणा HE_DURATION(streams, gi, bps) \
	((u32)HE_SYMBOL_TIME(gi, MCS_N_KSYMS((streams) * (bps))))

#घोषणा HE_DURATION_S(shअगरt, streams, gi, bps)		\
	(HE_DURATION(streams, gi, bps) >> shअगरt)

#घोषणा BW_20			0
#घोषणा BW_40			1
#घोषणा BW_80			2
#घोषणा BW_160			3

/*
 * Define group sort order: HT40 -> SGI -> #streams
 */
#घोषणा IEEE80211_MAX_STREAMS		4
#घोषणा IEEE80211_HT_STREAM_GROUPS	4 /* BW(=2) * SGI(=2) */
#घोषणा IEEE80211_VHT_STREAM_GROUPS	8 /* BW(=4) * SGI(=2) */

#घोषणा IEEE80211_HE_MAX_STREAMS	8
#घोषणा IEEE80211_HE_STREAM_GROUPS	12 /* BW(=4) * GI(=3) */

#घोषणा IEEE80211_HT_GROUPS_NB	(IEEE80211_MAX_STREAMS *	\
				 IEEE80211_HT_STREAM_GROUPS)
#घोषणा IEEE80211_VHT_GROUPS_NB	(IEEE80211_MAX_STREAMS *	\
					 IEEE80211_VHT_STREAM_GROUPS)
#घोषणा IEEE80211_HE_GROUPS_NB	(IEEE80211_HE_MAX_STREAMS *	\
				 IEEE80211_HE_STREAM_GROUPS)
#घोषणा IEEE80211_GROUPS_NB	(IEEE80211_HT_GROUPS_NB +	\
				 IEEE80211_VHT_GROUPS_NB +	\
				 IEEE80211_HE_GROUPS_NB)

#घोषणा IEEE80211_HT_GROUP_0	0
#घोषणा IEEE80211_VHT_GROUP_0	(IEEE80211_HT_GROUP_0 + IEEE80211_HT_GROUPS_NB)
#घोषणा IEEE80211_HE_GROUP_0	(IEEE80211_VHT_GROUP_0 + IEEE80211_VHT_GROUPS_NB)

#घोषणा MCS_GROUP_RATES		12

#घोषणा HT_GROUP_IDX(_streams, _sgi, _ht40)	\
	IEEE80211_HT_GROUP_0 +			\
	IEEE80211_MAX_STREAMS * 2 * _ht40 +	\
	IEEE80211_MAX_STREAMS * _sgi +		\
	_streams - 1

#घोषणा _MAX(a, b) (((a)>(b))?(a):(b))

#घोषणा GROUP_SHIFT(duration)						\
	_MAX(0, 16 - __builtin_clz(duration))

/* MCS rate inक्रमmation क्रम an MCS group */
#घोषणा __MCS_GROUP(_streams, _sgi, _ht40, _s)				\
	[HT_GROUP_IDX(_streams, _sgi, _ht40)] = अणु			\
	.shअगरt = _s,							\
	.duration = अणु							\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 54 : 26),	\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 108 : 52),	\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 162 : 78),	\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 216 : 104),	\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 324 : 156),	\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 432 : 208),	\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 486 : 234),	\
		MCS_DURATION_S(_s, _streams, _sgi, _ht40 ? 540 : 260)	\
	पूर्ण								\
पूर्ण

#घोषणा MCS_GROUP_SHIFT(_streams, _sgi, _ht40)				\
	GROUP_SHIFT(MCS_DURATION(_streams, _sgi, _ht40 ? 54 : 26))

#घोषणा MCS_GROUP(_streams, _sgi, _ht40)				\
	__MCS_GROUP(_streams, _sgi, _ht40,				\
		    MCS_GROUP_SHIFT(_streams, _sgi, _ht40))

#घोषणा VHT_GROUP_IDX(_streams, _sgi, _bw)				\
	(IEEE80211_VHT_GROUP_0 +					\
	 IEEE80211_MAX_STREAMS * 2 * (_bw) +				\
	 IEEE80211_MAX_STREAMS * (_sgi) +				\
	 (_streams) - 1)

#घोषणा BW2VBPS(_bw, r4, r3, r2, r1)					\
	(_bw == BW_160 ? r4 : _bw == BW_80 ? r3 : _bw == BW_40 ? r2 : r1)

#घोषणा __VHT_GROUP(_streams, _sgi, _bw, _s)				\
	[VHT_GROUP_IDX(_streams, _sgi, _bw)] = अणु			\
	.shअगरt = _s,							\
	.duration = अणु							\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw,  234,  117,  54,  26)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw,  468,  234, 108,  52)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw,  702,  351, 162,  78)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw,  936,  468, 216, 104)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw, 1404,  702, 324, 156)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw, 1872,  936, 432, 208)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw, 2106, 1053, 486, 234)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw, 2340, 1170, 540, 260)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw, 2808, 1404, 648, 312)),	\
		MCS_DURATION_S(_s, _streams, _sgi,			\
			       BW2VBPS(_bw, 3120, 1560, 720, 346))	\
        पूर्ण								\
पूर्ण

#घोषणा VHT_GROUP_SHIFT(_streams, _sgi, _bw)				\
	GROUP_SHIFT(MCS_DURATION(_streams, _sgi,			\
				 BW2VBPS(_bw, 243, 117,  54,  26)))

#घोषणा VHT_GROUP(_streams, _sgi, _bw)					\
	__VHT_GROUP(_streams, _sgi, _bw,				\
		    VHT_GROUP_SHIFT(_streams, _sgi, _bw))


#घोषणा HE_GROUP_IDX(_streams, _gi, _bw)				\
	(IEEE80211_HE_GROUP_0 +					\
	 IEEE80211_HE_MAX_STREAMS * 3 * (_bw) +			\
	 IEEE80211_HE_MAX_STREAMS * (_gi) +				\
	 (_streams) - 1)

#घोषणा __HE_GROUP(_streams, _gi, _bw, _s)				\
	[HE_GROUP_IDX(_streams, _gi, _bw)] = अणु			\
	.shअगरt = _s,							\
	.duration = अणु							\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,   979,  489,  230,  115)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,  1958,  979,  475,  230)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,  2937, 1468,  705,  345)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,  3916, 1958,  936,  475)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,  5875, 2937, 1411,  705)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,  7833, 3916, 1872,  936)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,  8827, 4406, 2102, 1051)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw,  9806, 4896, 2347, 1166)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw, 11764, 5875, 2808, 1411)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw, 13060, 6523, 3124, 1555)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw, 14702, 7344, 3513, 1756)),	\
		HE_DURATION_S(_s, _streams, _gi,			\
			      BW2VBPS(_bw, 16329, 8164, 3902, 1944))	\
        पूर्ण								\
पूर्ण

#घोषणा HE_GROUP_SHIFT(_streams, _gi, _bw)				\
	GROUP_SHIFT(HE_DURATION(_streams, _gi,			\
				BW2VBPS(_bw,   979,  489,  230,  115)))

#घोषणा HE_GROUP(_streams, _gi, _bw)					\
	__HE_GROUP(_streams, _gi, _bw,				\
		   HE_GROUP_SHIFT(_streams, _gi, _bw))
काष्ठा mcs_group अणु
	u8 shअगरt;
	u16 duration[MCS_GROUP_RATES];
पूर्ण;

अटल स्थिर काष्ठा mcs_group airसमय_mcs_groups[] = अणु
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

	VHT_GROUP(1, 0, BW_160),
	VHT_GROUP(2, 0, BW_160),
	VHT_GROUP(3, 0, BW_160),
	VHT_GROUP(4, 0, BW_160),

	VHT_GROUP(1, 1, BW_160),
	VHT_GROUP(2, 1, BW_160),
	VHT_GROUP(3, 1, BW_160),
	VHT_GROUP(4, 1, BW_160),

	HE_GROUP(1, HE_GI_08, BW_20),
	HE_GROUP(2, HE_GI_08, BW_20),
	HE_GROUP(3, HE_GI_08, BW_20),
	HE_GROUP(4, HE_GI_08, BW_20),
	HE_GROUP(5, HE_GI_08, BW_20),
	HE_GROUP(6, HE_GI_08, BW_20),
	HE_GROUP(7, HE_GI_08, BW_20),
	HE_GROUP(8, HE_GI_08, BW_20),

	HE_GROUP(1, HE_GI_16, BW_20),
	HE_GROUP(2, HE_GI_16, BW_20),
	HE_GROUP(3, HE_GI_16, BW_20),
	HE_GROUP(4, HE_GI_16, BW_20),
	HE_GROUP(5, HE_GI_16, BW_20),
	HE_GROUP(6, HE_GI_16, BW_20),
	HE_GROUP(7, HE_GI_16, BW_20),
	HE_GROUP(8, HE_GI_16, BW_20),

	HE_GROUP(1, HE_GI_32, BW_20),
	HE_GROUP(2, HE_GI_32, BW_20),
	HE_GROUP(3, HE_GI_32, BW_20),
	HE_GROUP(4, HE_GI_32, BW_20),
	HE_GROUP(5, HE_GI_32, BW_20),
	HE_GROUP(6, HE_GI_32, BW_20),
	HE_GROUP(7, HE_GI_32, BW_20),
	HE_GROUP(8, HE_GI_32, BW_20),

	HE_GROUP(1, HE_GI_08, BW_40),
	HE_GROUP(2, HE_GI_08, BW_40),
	HE_GROUP(3, HE_GI_08, BW_40),
	HE_GROUP(4, HE_GI_08, BW_40),
	HE_GROUP(5, HE_GI_08, BW_40),
	HE_GROUP(6, HE_GI_08, BW_40),
	HE_GROUP(7, HE_GI_08, BW_40),
	HE_GROUP(8, HE_GI_08, BW_40),

	HE_GROUP(1, HE_GI_16, BW_40),
	HE_GROUP(2, HE_GI_16, BW_40),
	HE_GROUP(3, HE_GI_16, BW_40),
	HE_GROUP(4, HE_GI_16, BW_40),
	HE_GROUP(5, HE_GI_16, BW_40),
	HE_GROUP(6, HE_GI_16, BW_40),
	HE_GROUP(7, HE_GI_16, BW_40),
	HE_GROUP(8, HE_GI_16, BW_40),

	HE_GROUP(1, HE_GI_32, BW_40),
	HE_GROUP(2, HE_GI_32, BW_40),
	HE_GROUP(3, HE_GI_32, BW_40),
	HE_GROUP(4, HE_GI_32, BW_40),
	HE_GROUP(5, HE_GI_32, BW_40),
	HE_GROUP(6, HE_GI_32, BW_40),
	HE_GROUP(7, HE_GI_32, BW_40),
	HE_GROUP(8, HE_GI_32, BW_40),

	HE_GROUP(1, HE_GI_08, BW_80),
	HE_GROUP(2, HE_GI_08, BW_80),
	HE_GROUP(3, HE_GI_08, BW_80),
	HE_GROUP(4, HE_GI_08, BW_80),
	HE_GROUP(5, HE_GI_08, BW_80),
	HE_GROUP(6, HE_GI_08, BW_80),
	HE_GROUP(7, HE_GI_08, BW_80),
	HE_GROUP(8, HE_GI_08, BW_80),

	HE_GROUP(1, HE_GI_16, BW_80),
	HE_GROUP(2, HE_GI_16, BW_80),
	HE_GROUP(3, HE_GI_16, BW_80),
	HE_GROUP(4, HE_GI_16, BW_80),
	HE_GROUP(5, HE_GI_16, BW_80),
	HE_GROUP(6, HE_GI_16, BW_80),
	HE_GROUP(7, HE_GI_16, BW_80),
	HE_GROUP(8, HE_GI_16, BW_80),

	HE_GROUP(1, HE_GI_32, BW_80),
	HE_GROUP(2, HE_GI_32, BW_80),
	HE_GROUP(3, HE_GI_32, BW_80),
	HE_GROUP(4, HE_GI_32, BW_80),
	HE_GROUP(5, HE_GI_32, BW_80),
	HE_GROUP(6, HE_GI_32, BW_80),
	HE_GROUP(7, HE_GI_32, BW_80),
	HE_GROUP(8, HE_GI_32, BW_80),

	HE_GROUP(1, HE_GI_08, BW_160),
	HE_GROUP(2, HE_GI_08, BW_160),
	HE_GROUP(3, HE_GI_08, BW_160),
	HE_GROUP(4, HE_GI_08, BW_160),
	HE_GROUP(5, HE_GI_08, BW_160),
	HE_GROUP(6, HE_GI_08, BW_160),
	HE_GROUP(7, HE_GI_08, BW_160),
	HE_GROUP(8, HE_GI_08, BW_160),

	HE_GROUP(1, HE_GI_16, BW_160),
	HE_GROUP(2, HE_GI_16, BW_160),
	HE_GROUP(3, HE_GI_16, BW_160),
	HE_GROUP(4, HE_GI_16, BW_160),
	HE_GROUP(5, HE_GI_16, BW_160),
	HE_GROUP(6, HE_GI_16, BW_160),
	HE_GROUP(7, HE_GI_16, BW_160),
	HE_GROUP(8, HE_GI_16, BW_160),

	HE_GROUP(1, HE_GI_32, BW_160),
	HE_GROUP(2, HE_GI_32, BW_160),
	HE_GROUP(3, HE_GI_32, BW_160),
	HE_GROUP(4, HE_GI_32, BW_160),
	HE_GROUP(5, HE_GI_32, BW_160),
	HE_GROUP(6, HE_GI_32, BW_160),
	HE_GROUP(7, HE_GI_32, BW_160),
	HE_GROUP(8, HE_GI_32, BW_160),
पूर्ण;

अटल u32
ieee80211_calc_legacy_rate_duration(u16 bitrate, bool लघु_pre,
				    bool cck, पूर्णांक len)
अणु
	u32 duration;

	अगर (cck) अणु
		duration = 144 + 48; /* preamble + PLCP */
		अगर (लघु_pre)
			duration >>= 1;

		duration += 10; /* SIFS */
	पूर्ण अन्यथा अणु
		duration = 20 + 16; /* premable + SIFS */
	पूर्ण

	len <<= 3;
	duration += (len * 10) / bitrate;

	वापस duration;
पूर्ण

अटल u32 ieee80211_get_rate_duration(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_rx_status *status,
				       u32 *overhead)
अणु
	bool sgi = status->enc_flags & RX_ENC_FLAG_SHORT_GI;
	पूर्णांक bw, streams;
	पूर्णांक group, idx;
	u32 duration;

	चयन (status->bw) अणु
	हाल RATE_INFO_BW_20:
		bw = BW_20;
		अवरोध;
	हाल RATE_INFO_BW_40:
		bw = BW_40;
		अवरोध;
	हाल RATE_INFO_BW_80:
		bw = BW_80;
		अवरोध;
	हाल RATE_INFO_BW_160:
		bw = BW_160;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	चयन (status->encoding) अणु
	हाल RX_ENC_VHT:
		streams = status->nss;
		idx = status->rate_idx;
		group = VHT_GROUP_IDX(streams, sgi, bw);
		अवरोध;
	हाल RX_ENC_HT:
		streams = ((status->rate_idx >> 3) & 3) + 1;
		idx = status->rate_idx & 7;
		group = HT_GROUP_IDX(streams, sgi, bw);
		अवरोध;
	हाल RX_ENC_HE:
		streams = status->nss;
		idx = status->rate_idx;
		group = HE_GROUP_IDX(streams, status->he_gi, bw);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	अगर (WARN_ON_ONCE((status->encoding != RX_ENC_HE && streams > 4) ||
			 (status->encoding == RX_ENC_HE && streams > 8)))
		वापस 0;

	duration = airसमय_mcs_groups[group].duration[idx];
	duration <<= airसमय_mcs_groups[group].shअगरt;
	*overhead = 36 + (streams << 2);

	वापस duration;
पूर्ण


u32 ieee80211_calc_rx_airसमय(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_rx_status *status,
			      पूर्णांक len)
अणु
	काष्ठा ieee80211_supported_band *sband;
	u32 duration, overhead = 0;

	अगर (status->encoding == RX_ENC_LEGACY) अणु
		स्थिर काष्ठा ieee80211_rate *rate;
		bool sp = status->enc_flags & RX_ENC_FLAG_SHORTPRE;
		bool cck;

		अगर (WARN_ON_ONCE(status->band > NL80211_BAND_5GHZ))
			वापस 0;

		sband = hw->wiphy->bands[status->band];
		अगर (!sband || status->rate_idx >= sband->n_bitrates)
			वापस 0;

		rate = &sband->bitrates[status->rate_idx];
		cck = rate->flags & IEEE80211_RATE_MANDATORY_B;

		वापस ieee80211_calc_legacy_rate_duration(rate->bitrate, sp,
							   cck, len);
	पूर्ण

	duration = ieee80211_get_rate_duration(hw, status, &overhead);
	अगर (!duration)
		वापस 0;

	duration *= len;
	duration /= AVG_PKT_SIZE;
	duration /= 1024;

	वापस duration + overhead;
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_calc_rx_airसमय);

अटल bool ieee80211_fill_rate_info(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_rx_status *stat, u8 band,
				     काष्ठा rate_info *ri)
अणु
	काष्ठा ieee80211_supported_band *sband = hw->wiphy->bands[band];
	पूर्णांक i;

	अगर (!ri || !sband)
	    वापस false;

	stat->bw = ri->bw;
	stat->nss = ri->nss;
	stat->rate_idx = ri->mcs;

	अगर (ri->flags & RATE_INFO_FLAGS_HE_MCS)
		stat->encoding = RX_ENC_HE;
	अन्यथा अगर (ri->flags & RATE_INFO_FLAGS_VHT_MCS)
		stat->encoding = RX_ENC_VHT;
	अन्यथा अगर (ri->flags & RATE_INFO_FLAGS_MCS)
		stat->encoding = RX_ENC_HT;
	अन्यथा
		stat->encoding = RX_ENC_LEGACY;

	अगर (ri->flags & RATE_INFO_FLAGS_SHORT_GI)
		stat->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	stat->he_gi = ri->he_gi;

	अगर (stat->encoding != RX_ENC_LEGACY)
		वापस true;

	stat->rate_idx = 0;
	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		अगर (ri->legacy != sband->bitrates[i].bitrate)
			जारी;

		stat->rate_idx = i;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक ieee80211_fill_rx_status(काष्ठा ieee80211_rx_status *stat,
				    काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_tx_rate *rate,
				    काष्ठा rate_info *ri, u8 band, पूर्णांक len)
अणु
	स_रखो(stat, 0, माप(*stat));
	stat->band = band;

	अगर (ieee80211_fill_rate_info(hw, stat, band, ri))
		वापस 0;

	अगर (rate->idx < 0 || !rate->count)
		वापस -1;

	अगर (rate->flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		stat->bw = RATE_INFO_BW_160;
	अन्यथा अगर (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		stat->bw = RATE_INFO_BW_80;
	अन्यथा अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		stat->bw = RATE_INFO_BW_40;
	अन्यथा
		stat->bw = RATE_INFO_BW_20;

	stat->enc_flags = 0;
	अगर (rate->flags & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		stat->enc_flags |= RX_ENC_FLAG_SHORTPRE;
	अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		stat->enc_flags |= RX_ENC_FLAG_SHORT_GI;

	stat->rate_idx = rate->idx;
	अगर (rate->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		stat->encoding = RX_ENC_VHT;
		stat->rate_idx = ieee80211_rate_get_vht_mcs(rate);
		stat->nss = ieee80211_rate_get_vht_nss(rate);
	पूर्ण अन्यथा अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		stat->encoding = RX_ENC_HT;
	पूर्ण अन्यथा अणु
		stat->encoding = RX_ENC_LEGACY;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 ieee80211_calc_tx_airसमय_rate(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_tx_rate *rate,
					  काष्ठा rate_info *ri,
					  u8 band, पूर्णांक len)
अणु
	काष्ठा ieee80211_rx_status stat;

	अगर (ieee80211_fill_rx_status(&stat, hw, rate, ri, band, len))
		वापस 0;

	वापस ieee80211_calc_rx_airसमय(hw, &stat, len);
पूर्ण

u32 ieee80211_calc_tx_airसमय(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_tx_info *info,
			      पूर्णांक len)
अणु
	u32 duration = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(info->status.rates); i++) अणु
		काष्ठा ieee80211_tx_rate *rate = &info->status.rates[i];
		u32 cur_duration;

		cur_duration = ieee80211_calc_tx_airसमय_rate(hw, rate, शून्य,
							      info->band, len);
		अगर (!cur_duration)
			अवरोध;

		duration += cur_duration * rate->count;
	पूर्ण

	वापस duration;
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_calc_tx_airसमय);

u32 ieee80211_calc_expected_tx_airसमय(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *pubsta,
				       पूर्णांक len, bool ampdu)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_chanctx_conf *conf;
	पूर्णांक rateidx, shअगरt = 0;
	bool cck, लघु_pream;
	u32 basic_rates;
	u8 band = 0;
	u16 rate;

	len += 38; /* Ethernet header length */

	conf = rcu_dereference(vअगर->chanctx_conf);
	अगर (conf) अणु
		band = conf->def.chan->band;
		shअगरt = ieee80211_chandef_get_shअगरt(&conf->def);
	पूर्ण

	अगर (pubsta) अणु
		काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info,
						    sta);
		काष्ठा ieee80211_rx_status stat;
		काष्ठा ieee80211_tx_rate *rate = &sta->tx_stats.last_rate;
		काष्ठा rate_info *ri = &sta->tx_stats.last_rate_info;
		u32 duration, overhead;
		u8 agg_shअगरt;

		अगर (ieee80211_fill_rx_status(&stat, hw, rate, ri, band, len))
			वापस 0;

		अगर (stat.encoding == RX_ENC_LEGACY || !ampdu)
			वापस ieee80211_calc_rx_airसमय(hw, &stat, len);

		duration = ieee80211_get_rate_duration(hw, &stat, &overhead);
		/*
		 * Assume that HT/VHT transmission on any AC except VO will
		 * use aggregation. Since we करोn't have reliable reporting
		 * of aggregation length, assume an average size based on the
		 * tx rate.
		 * This will not be very accurate, but much better than simply
		 * assuming un-aggregated tx in all हालs.
		 */
		अगर (duration > 400 * 1024) /* <= VHT20 MCS2 1S */
			agg_shअगरt = 1;
		अन्यथा अगर (duration > 250 * 1024) /* <= VHT20 MCS3 1S or MCS1 2S */
			agg_shअगरt = 2;
		अन्यथा अगर (duration > 150 * 1024) /* <= VHT20 MCS5 1S or MCS2 2S */
			agg_shअगरt = 3;
		अन्यथा अगर (duration > 70 * 1024) /* <= VHT20 MCS5 2S */
			agg_shअगरt = 4;
		अन्यथा अगर (stat.encoding != RX_ENC_HE ||
			 duration > 20 * 1024) /* <= HE40 MCS6 2S */
			agg_shअगरt = 5;
		अन्यथा
			agg_shअगरt = 6;

		duration *= len;
		duration /= AVG_PKT_SIZE;
		duration /= 1024;
		duration += (overhead >> agg_shअगरt);

		वापस max_t(u32, duration, 4);
	पूर्ण

	अगर (!conf)
		वापस 0;

	/* No station to get latest rate from, so calculate the worst-हाल
	 * duration using the lowest configured basic rate.
	 */
	sband = hw->wiphy->bands[band];

	basic_rates = vअगर->bss_conf.basic_rates;
	लघु_pream = vअगर->bss_conf.use_लघु_preamble;

	rateidx = basic_rates ? ffs(basic_rates) - 1 : 0;
	rate = sband->bitrates[rateidx].bitrate << shअगरt;
	cck = sband->bitrates[rateidx].flags & IEEE80211_RATE_MANDATORY_B;

	वापस ieee80211_calc_legacy_rate_duration(rate, लघु_pream, cck, len);
पूर्ण
