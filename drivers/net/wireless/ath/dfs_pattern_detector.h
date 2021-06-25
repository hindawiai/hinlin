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

#अगर_अघोषित DFS_PATTERN_DETECTOR_H
#घोषणा DFS_PATTERN_DETECTOR_H

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/nl80211.h>

/* tolerated deviation of radar समय stamp in usecs on both sides
 * TODO: this might need to be HW-dependent
 */
#घोषणा PRI_TOLERANCE	16

/**
 * काष्ठा ath_dfs_pool_stats - DFS Statistics क्रम global pools
 */
काष्ठा ath_dfs_pool_stats अणु
	u32 pool_reference;
	u32 pulse_allocated;
	u32 pulse_alloc_error;
	u32 pulse_used;
	u32 pseq_allocated;
	u32 pseq_alloc_error;
	u32 pseq_used;
पूर्ण;

/**
 * काष्ठा pulse_event - describing pulses reported by PHY
 * @ts: pulse समय stamp in us
 * @freq: channel frequency in MHz
 * @width: pulse duration in us
 * @rssi: rssi of radar event
 * @chirp: chirp detected in pulse
 */
काष्ठा pulse_event अणु
	u64 ts;
	u16 freq;
	u8 width;
	u8 rssi;
	bool chirp;
पूर्ण;

/**
 * काष्ठा radar_detector_specs - detector specs क्रम a radar pattern type
 * @type_id: pattern type, as defined by regulatory
 * @width_min: minimum radar pulse width in [us]
 * @width_max: maximum radar pulse width in [us]
 * @pri_min: minimum pulse repetition पूर्णांकerval in [us] (including tolerance)
 * @pri_max: minimum pri in [us] (including tolerance)
 * @num_pri: maximum number of dअगरferent pri क्रम this type
 * @ppb: pulses per bursts क्रम this type
 * @ppb_thresh: number of pulses required to trigger detection
 * @max_pri_tolerance: pulse समय stamp tolerance on both sides [us]
 * @chirp: chirp required क्रम the radar pattern
 */
काष्ठा radar_detector_specs अणु
	u8 type_id;
	u8 width_min;
	u8 width_max;
	u16 pri_min;
	u16 pri_max;
	u8 num_pri;
	u8 ppb;
	u8 ppb_thresh;
	u8 max_pri_tolerance;
	bool chirp;
पूर्ण;

/**
 * काष्ठा dfs_pattern_detector - DFS pattern detector
 * @निकास(): deकाष्ठाor
 * @set_dfs_करोमुख्य(): set DFS करोमुख्य, resets detector lines upon करोमुख्य changes
 * @add_pulse(): add radar pulse to detector, वापसs true on detection
 * @region: active DFS region, NL80211_DFS_UNSET until set
 * @num_radar_types: number of dअगरferent radar types
 * @last_pulse_ts: समय stamp of last valid pulse in usecs
 * @radar_detector_specs: array of radar detection specs
 * @channel_detectors: list connecting channel_detector elements
 */
काष्ठा dfs_pattern_detector अणु
	व्योम (*निकास)(काष्ठा dfs_pattern_detector *dpd);
	bool (*set_dfs_करोमुख्य)(काष्ठा dfs_pattern_detector *dpd,
			   क्रमागत nl80211_dfs_regions region);
	bool (*add_pulse)(काष्ठा dfs_pattern_detector *dpd,
			  काष्ठा pulse_event *pe,
			  काष्ठा radar_detector_specs *rs);

	काष्ठा ath_dfs_pool_stats (*get_stats)(काष्ठा dfs_pattern_detector *dpd);
	क्रमागत nl80211_dfs_regions region;
	u8 num_radar_types;
	u64 last_pulse_ts;
	/* needed क्रम ath_dbg() */
	काष्ठा ath_common *common;

	स्थिर काष्ठा radar_detector_specs *radar_spec;
	काष्ठा list_head channel_detectors;
पूर्ण;

/**
 * dfs_pattern_detector_init() - स्थिरructor क्रम pattern detector class
 * @param region: DFS करोमुख्य to be used, can be NL80211_DFS_UNSET at creation
 * @वापस instance poपूर्णांकer on success, शून्य otherwise
 */
बाह्य काष्ठा dfs_pattern_detector *
dfs_pattern_detector_init(काष्ठा ath_common *common,
			  क्रमागत nl80211_dfs_regions region);
#पूर्ण_अगर /* DFS_PATTERN_DETECTOR_H */
