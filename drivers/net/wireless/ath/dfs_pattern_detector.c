<शैली गुरु>
/*
 * Copyright (c) 2012 Neratec Solutions AG
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>

#समावेश "dfs_pattern_detector.h"
#समावेश "dfs_pri_detector.h"
#समावेश "ath.h"

/**
 * काष्ठा radar_types - contains array of patterns defined क्रम one DFS करोमुख्य
 * @region: regulatory DFS region
 * @num_radar_types: number of radar types to follow
 * @radar_types: radar types array
 */
काष्ठा radar_types अणु
	क्रमागत nl80211_dfs_regions region;
	u32 num_radar_types;
	स्थिर काष्ठा radar_detector_specs *radar_types;
पूर्ण;

/* percentage on ppb threshold to trigger detection */
#घोषणा MIN_PPB_THRESH	50
#घोषणा PPB_THRESH_RATE(PPB, RATE) ((PPB * RATE + 100 - RATE) / 100)
#घोषणा PPB_THRESH(PPB) PPB_THRESH_RATE(PPB, MIN_PPB_THRESH)
#घोषणा PRF2PRI(PRF) ((1000000 + PRF / 2) / PRF)
/* percentage of pulse width tolerance */
#घोषणा WIDTH_TOLERANCE 5
#घोषणा WIDTH_LOWER(X) ((X*(100-WIDTH_TOLERANCE)+50)/100)
#घोषणा WIDTH_UPPER(X) ((X*(100+WIDTH_TOLERANCE)+50)/100)

#घोषणा ETSI_PATTERN(ID, WMIN, WMAX, PMIN, PMAX, PRF, PPB, CHIRP)	\
अणु								\
	ID, WIDTH_LOWER(WMIN), WIDTH_UPPER(WMAX),		\
	(PRF2PRI(PMAX) - PRI_TOLERANCE),			\
	(PRF2PRI(PMIN) * PRF + PRI_TOLERANCE), PRF, PPB * PRF,	\
	PPB_THRESH(PPB), PRI_TOLERANCE,	CHIRP			\
पूर्ण

/* radar types as defined by ETSI EN-301-893 v1.5.1 */
अटल स्थिर काष्ठा radar_detector_specs etsi_radar_ref_types_v15[] = अणु
	ETSI_PATTERN(0,  0,  1,  700,  700, 1, 18, false),
	ETSI_PATTERN(1,  0,  5,  200, 1000, 1, 10, false),
	ETSI_PATTERN(2,  0, 15,  200, 1600, 1, 15, false),
	ETSI_PATTERN(3,  0, 15, 2300, 4000, 1, 25, false),
	ETSI_PATTERN(4, 20, 30, 2000, 4000, 1, 20, false),
	ETSI_PATTERN(5,  0,  2,  300,  400, 3, 10, false),
	ETSI_PATTERN(6,  0,  2,  400, 1200, 3, 15, false),
पूर्ण;

अटल स्थिर काष्ठा radar_types etsi_radar_types_v15 = अणु
	.region			= NL80211_DFS_ETSI,
	.num_radar_types	= ARRAY_SIZE(etsi_radar_ref_types_v15),
	.radar_types		= etsi_radar_ref_types_v15,
पूर्ण;

#घोषणा FCC_PATTERN(ID, WMIN, WMAX, PMIN, PMAX, PRF, PPB, CHIRP)	\
अणु								\
	ID, WIDTH_LOWER(WMIN), WIDTH_UPPER(WMAX),		\
	PMIN - PRI_TOLERANCE,					\
	PMAX * PRF + PRI_TOLERANCE, PRF, PPB * PRF,		\
	PPB_THRESH(PPB), PRI_TOLERANCE,	CHIRP			\
पूर्ण

/* radar types released on August 14, 2014
 * type 1 PRI values अक्रमomly selected within the range of 518 and 3066.
 * भागide it to 3 groups is good enough क्रम both of radar detection and
 * aव्योमing false detection based on practical test results
 * collected क्रम more than a year.
 */
अटल स्थिर काष्ठा radar_detector_specs fcc_radar_ref_types[] = अणु
	FCC_PATTERN(0, 0, 1, 1428, 1428, 1, 18, false),
	FCC_PATTERN(101, 0, 1, 518, 938, 1, 57, false),
	FCC_PATTERN(102, 0, 1, 938, 2000, 1, 27, false),
	FCC_PATTERN(103, 0, 1, 2000, 3066, 1, 18, false),
	FCC_PATTERN(2, 0, 5, 150, 230, 1, 23, false),
	FCC_PATTERN(3, 6, 10, 200, 500, 1, 16, false),
	FCC_PATTERN(4, 11, 20, 200, 500, 1, 12, false),
	FCC_PATTERN(5, 50, 100, 1000, 2000, 1, 1, true),
	FCC_PATTERN(6, 0, 1, 333, 333, 1, 9, false),
पूर्ण;

अटल स्थिर काष्ठा radar_types fcc_radar_types = अणु
	.region			= NL80211_DFS_FCC,
	.num_radar_types	= ARRAY_SIZE(fcc_radar_ref_types),
	.radar_types		= fcc_radar_ref_types,
पूर्ण;

#घोषणा JP_PATTERN(ID, WMIN, WMAX, PMIN, PMAX, PRF, PPB, RATE, CHIRP)	\
अणु								\
	ID, WIDTH_LOWER(WMIN), WIDTH_UPPER(WMAX),		\
	PMIN - PRI_TOLERANCE,					\
	PMAX * PRF + PRI_TOLERANCE, PRF, PPB * PRF,		\
	PPB_THRESH_RATE(PPB, RATE), PRI_TOLERANCE, CHIRP	\
पूर्ण
अटल स्थिर काष्ठा radar_detector_specs jp_radar_ref_types[] = अणु
	JP_PATTERN(0, 0, 1, 1428, 1428, 1, 18, 29, false),
	JP_PATTERN(1, 2, 3, 3846, 3846, 1, 18, 29, false),
	JP_PATTERN(2, 0, 1, 1388, 1388, 1, 18, 50, false),
	JP_PATTERN(3, 0, 4, 4000, 4000, 1, 18, 50, false),
	JP_PATTERN(4, 0, 5, 150, 230, 1, 23, 50, false),
	JP_PATTERN(5, 6, 10, 200, 500, 1, 16, 50, false),
	JP_PATTERN(6, 11, 20, 200, 500, 1, 12, 50, false),
	JP_PATTERN(7, 50, 100, 1000, 2000, 1, 3, 50, true),
	JP_PATTERN(5, 0, 1, 333, 333, 1, 9, 50, false),
पूर्ण;

अटल स्थिर काष्ठा radar_types jp_radar_types = अणु
	.region			= NL80211_DFS_JP,
	.num_radar_types	= ARRAY_SIZE(jp_radar_ref_types),
	.radar_types		= jp_radar_ref_types,
पूर्ण;

अटल स्थिर काष्ठा radar_types *dfs_करोमुख्यs[] = अणु
	&etsi_radar_types_v15,
	&fcc_radar_types,
	&jp_radar_types,
पूर्ण;

/**
 * get_dfs_करोमुख्य_radar_types() - get radar types क्रम a given DFS करोमुख्य
 * @region: regulatory DFS region
 *
 * Return value: radar_types ptr on success, शून्य अगर DFS करोमुख्य is not supported
 */
अटल स्थिर काष्ठा radar_types *
get_dfs_करोमुख्य_radar_types(क्रमागत nl80211_dfs_regions region)
अणु
	u32 i;
	क्रम (i = 0; i < ARRAY_SIZE(dfs_करोमुख्यs); i++) अणु
		अगर (dfs_करोमुख्यs[i]->region == region)
			वापस dfs_करोमुख्यs[i];
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * काष्ठा channel_detector - detector elements क्रम a DFS channel
 * @head: list_head
 * @freq: frequency क्रम this channel detector in MHz
 * @detectors: array of dynamically created detector elements क्रम this freq
 *
 * Channel detectors are required to provide multi-channel DFS detection, e.g.
 * to support off-channel scanning. A pattern detector has a list of channels
 * radar pulses have been reported क्रम in the past.
 */
काष्ठा channel_detector अणु
	काष्ठा list_head head;
	u16 freq;
	काष्ठा pri_detector **detectors;
पूर्ण;

/* channel_detector_reset() - reset detector lines क्रम a given channel */
अटल व्योम channel_detector_reset(काष्ठा dfs_pattern_detector *dpd,
				   काष्ठा channel_detector *cd)
अणु
	u32 i;
	अगर (cd == शून्य)
		वापस;
	क्रम (i = 0; i < dpd->num_radar_types; i++)
		cd->detectors[i]->reset(cd->detectors[i], dpd->last_pulse_ts);
पूर्ण

/* channel_detector_निकास() - deकाष्ठाor */
अटल व्योम channel_detector_निकास(काष्ठा dfs_pattern_detector *dpd,
				  काष्ठा channel_detector *cd)
अणु
	u32 i;
	अगर (cd == शून्य)
		वापस;
	list_del(&cd->head);
	क्रम (i = 0; i < dpd->num_radar_types; i++) अणु
		काष्ठा pri_detector *de = cd->detectors[i];
		अगर (de != शून्य)
			de->निकास(de);
	पूर्ण
	kमुक्त(cd->detectors);
	kमुक्त(cd);
पूर्ण

अटल काष्ठा channel_detector *
channel_detector_create(काष्ठा dfs_pattern_detector *dpd, u16 freq)
अणु
	u32 sz, i;
	काष्ठा channel_detector *cd;

	cd = kदो_स्मृति(माप(*cd), GFP_ATOMIC);
	अगर (cd == शून्य)
		जाओ fail;

	INIT_LIST_HEAD(&cd->head);
	cd->freq = freq;
	sz = माप(cd->detectors) * dpd->num_radar_types;
	cd->detectors = kzalloc(sz, GFP_ATOMIC);
	अगर (cd->detectors == शून्य)
		जाओ fail;

	क्रम (i = 0; i < dpd->num_radar_types; i++) अणु
		स्थिर काष्ठा radar_detector_specs *rs = &dpd->radar_spec[i];
		काष्ठा pri_detector *de = pri_detector_init(rs);
		अगर (de == शून्य)
			जाओ fail;
		cd->detectors[i] = de;
	पूर्ण
	list_add(&cd->head, &dpd->channel_detectors);
	वापस cd;

fail:
	ath_dbg(dpd->common, DFS,
		"failed to allocate channel_detector for freq=%d\n", freq);
	channel_detector_निकास(dpd, cd);
	वापस शून्य;
पूर्ण

/**
 * channel_detector_get() - get channel detector क्रम given frequency
 * @dpd: DPD instance poपूर्णांकer
 * @freq: freq frequency in MHz
 *
 * Return value: poपूर्णांकer to channel detector on success, शून्य otherwise
 *
 * Return existing channel detector क्रम the given frequency or वापस a
 * newly create one.
 */
अटल काष्ठा channel_detector *
channel_detector_get(काष्ठा dfs_pattern_detector *dpd, u16 freq)
अणु
	काष्ठा channel_detector *cd;
	list_क्रम_each_entry(cd, &dpd->channel_detectors, head) अणु
		अगर (cd->freq == freq)
			वापस cd;
	पूर्ण
	वापस channel_detector_create(dpd, freq);
पूर्ण

/*
 * DFS Pattern Detector
 */

/* dpd_reset(): reset all channel detectors */
अटल व्योम dpd_reset(काष्ठा dfs_pattern_detector *dpd)
अणु
	काष्ठा channel_detector *cd;
	list_क्रम_each_entry(cd, &dpd->channel_detectors, head)
		channel_detector_reset(dpd, cd);

पूर्ण
अटल व्योम dpd_निकास(काष्ठा dfs_pattern_detector *dpd)
अणु
	काष्ठा channel_detector *cd, *cd0;
	list_क्रम_each_entry_safe(cd, cd0, &dpd->channel_detectors, head)
		channel_detector_निकास(dpd, cd);
	kमुक्त(dpd);
पूर्ण

अटल bool
dpd_add_pulse(काष्ठा dfs_pattern_detector *dpd, काष्ठा pulse_event *event,
	      काष्ठा radar_detector_specs *rs)
अणु
	u32 i;
	काष्ठा channel_detector *cd;

	/*
	 * pulses received क्रम a non-supported or un-initialized
	 * करोमुख्य are treated as detected radars क्रम fail-safety
	 */
	अगर (dpd->region == NL80211_DFS_UNSET)
		वापस true;

	cd = channel_detector_get(dpd, event->freq);
	अगर (cd == शून्य)
		वापस false;

	/* reset detector on समय stamp wraparound, caused by TSF reset */
	अगर (event->ts < dpd->last_pulse_ts)
		dpd_reset(dpd);
	dpd->last_pulse_ts = event->ts;

	/* करो type inभागidual pattern matching */
	क्रम (i = 0; i < dpd->num_radar_types; i++) अणु
		काष्ठा pri_detector *pd = cd->detectors[i];
		काष्ठा pri_sequence *ps = pd->add_pulse(pd, event);
		अगर (ps != शून्य) अणु
			अगर (rs != शून्य)
				स_नकल(rs, pd->rs, माप(*rs));
			ath_dbg(dpd->common, DFS,
				"DFS: radar found on freq=%d: id=%d, pri=%d, "
				"count=%d, count_false=%d\n",
				event->freq, pd->rs->type_id,
				ps->pri, ps->count, ps->count_falses);
			pd->reset(pd, dpd->last_pulse_ts);
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा ath_dfs_pool_stats
dpd_get_stats(काष्ठा dfs_pattern_detector *dpd)
अणु
	वापस global_dfs_pool_stats;
पूर्ण

अटल bool dpd_set_करोमुख्य(काष्ठा dfs_pattern_detector *dpd,
			   क्रमागत nl80211_dfs_regions region)
अणु
	स्थिर काष्ठा radar_types *rt;
	काष्ठा channel_detector *cd, *cd0;

	अगर (dpd->region == region)
		वापस true;

	dpd->region = NL80211_DFS_UNSET;

	rt = get_dfs_करोमुख्य_radar_types(region);
	अगर (rt == शून्य)
		वापस false;

	/* delete all channel detectors क्रम previous DFS करोमुख्य */
	list_क्रम_each_entry_safe(cd, cd0, &dpd->channel_detectors, head)
		channel_detector_निकास(dpd, cd);
	dpd->radar_spec = rt->radar_types;
	dpd->num_radar_types = rt->num_radar_types;

	dpd->region = region;
	वापस true;
पूर्ण

अटल स्थिर काष्ठा dfs_pattern_detector शेष_dpd = अणु
	.निकास		= dpd_निकास,
	.set_dfs_करोमुख्य	= dpd_set_करोमुख्य,
	.add_pulse	= dpd_add_pulse,
	.get_stats	= dpd_get_stats,
	.region		= NL80211_DFS_UNSET,
पूर्ण;

काष्ठा dfs_pattern_detector *
dfs_pattern_detector_init(काष्ठा ath_common *common,
			  क्रमागत nl80211_dfs_regions region)
अणु
	काष्ठा dfs_pattern_detector *dpd;

	अगर (!IS_ENABLED(CONFIG_CFG80211_CERTIFICATION_ONUS))
		वापस शून्य;

	dpd = kदो_स्मृति(माप(*dpd), GFP_KERNEL);
	अगर (dpd == शून्य)
		वापस शून्य;

	*dpd = शेष_dpd;
	INIT_LIST_HEAD(&dpd->channel_detectors);

	dpd->common = common;
	अगर (dpd->set_dfs_करोमुख्य(dpd, region))
		वापस dpd;

	ath_dbg(common, DFS,"Could not set DFS domain to %d", region);
	kमुक्त(dpd);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(dfs_pattern_detector_init);
