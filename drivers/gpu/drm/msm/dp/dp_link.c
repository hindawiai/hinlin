<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#घोषणा pr_fmt(fmt)	"[drm-dp] %s: " fmt, __func__

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "dp_link.h"
#समावेश "dp_panel.h"

#घोषणा DP_TEST_REQUEST_MASK		0x7F

क्रमागत audio_sample_rate अणु
	AUDIO_SAMPLE_RATE_32_KHZ	= 0x00,
	AUDIO_SAMPLE_RATE_44_1_KHZ	= 0x01,
	AUDIO_SAMPLE_RATE_48_KHZ	= 0x02,
	AUDIO_SAMPLE_RATE_88_2_KHZ	= 0x03,
	AUDIO_SAMPLE_RATE_96_KHZ	= 0x04,
	AUDIO_SAMPLE_RATE_176_4_KHZ	= 0x05,
	AUDIO_SAMPLE_RATE_192_KHZ	= 0x06,
पूर्ण;

क्रमागत audio_pattern_type अणु
	AUDIO_TEST_PATTERN_OPERATOR_DEFINED	= 0x00,
	AUDIO_TEST_PATTERN_SAWTOOTH		= 0x01,
पूर्ण;

काष्ठा dp_link_request अणु
	u32 test_requested;
	u32 test_link_rate;
	u32 test_lane_count;
पूर्ण;

काष्ठा dp_link_निजी अणु
	u32 prev_sink_count;
	काष्ठा device *dev;
	काष्ठा drm_dp_aux *aux;
	काष्ठा dp_link dp_link;

	काष्ठा dp_link_request request;
	काष्ठा mutex psm_mutex;
	u8 link_status[DP_LINK_STATUS_SIZE];
पूर्ण;

अटल पूर्णांक dp_aux_link_घातer_up(काष्ठा drm_dp_aux *aux,
					काष्ठा dp_link_info *link)
अणु
	u8 value;
	पूर्णांक err;

	अगर (link->revision < 0x11)
		वापस 0;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_SET_POWER, &value);
	अगर (err < 0)
		वापस err;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D0;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_SET_POWER, value);
	अगर (err < 0)
		वापस err;

	usleep_range(1000, 2000);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_aux_link_घातer_करोwn(काष्ठा drm_dp_aux *aux,
					काष्ठा dp_link_info *link)
अणु
	u8 value;
	पूर्णांक err;

	अगर (link->revision < 0x11)
		वापस 0;

	err = drm_dp_dpcd_पढ़ोb(aux, DP_SET_POWER, &value);
	अगर (err < 0)
		वापस err;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D3;

	err = drm_dp_dpcd_ग_लिखोb(aux, DP_SET_POWER, value);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक dp_link_get_period(काष्ठा dp_link_निजी *link, पूर्णांक स्थिर addr)
अणु
	पूर्णांक ret = 0;
	u8 data;
	u32 स्थिर max_audio_period = 0xA;

	/* TEST_AUDIO_PERIOD_CH_XX */
	अगर (drm_dp_dpcd_पढ़ोb(link->aux, addr, &data) < 0) अणु
		DRM_ERROR("failed to read test_audio_period (0x%x)\n", addr);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Period - Bits 3:0 */
	data = data & 0xF;
	अगर ((पूर्णांक)data > max_audio_period) अणु
		DRM_ERROR("invalid test_audio_period_ch_1 = 0x%x\n", data);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	ret = data;
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक dp_link_parse_audio_channel_period(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;
	काष्ठा dp_link_test_audio *req = &link->dp_link.test_audio;

	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH1);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_1 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_1 = 0x%x\n", ret);

	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH2);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_2 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_2 = 0x%x\n", ret);

	/* TEST_AUDIO_PERIOD_CH_3 (Byte 0x275) */
	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH3);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_3 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_3 = 0x%x\n", ret);

	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH4);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_4 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_4 = 0x%x\n", ret);

	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH5);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_5 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_5 = 0x%x\n", ret);

	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH6);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_6 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_6 = 0x%x\n", ret);

	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH7);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_7 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_7 = 0x%x\n", ret);

	ret = dp_link_get_period(link, DP_TEST_AUDIO_PERIOD_CH8);
	अगर (ret == -EINVAL)
		जाओ निकास;

	req->test_audio_period_ch_8 = ret;
	DRM_DEBUG_DP("test_audio_period_ch_8 = 0x%x\n", ret);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक dp_link_parse_audio_pattern_type(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;
	u8 data;
	sमाप_प्रकार rlen;
	पूर्णांक स्थिर max_audio_pattern_type = 0x1;

	rlen = drm_dp_dpcd_पढ़ोb(link->aux,
				DP_TEST_AUDIO_PATTERN_TYPE, &data);
	अगर (rlen < 0) अणु
		DRM_ERROR("failed to read link audio mode. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	/* Audio Pattern Type - Bits 7:0 */
	अगर ((पूर्णांक)data > max_audio_pattern_type) अणु
		DRM_ERROR("invalid audio pattern type = 0x%x\n", data);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	link->dp_link.test_audio.test_audio_pattern_type = data;
	DRM_DEBUG_DP("audio pattern type = 0x%x\n", data);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक dp_link_parse_audio_mode(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;
	u8 data;
	sमाप_प्रकार rlen;
	पूर्णांक स्थिर max_audio_sampling_rate = 0x6;
	पूर्णांक स्थिर max_audio_channel_count = 0x8;
	पूर्णांक sampling_rate = 0x0;
	पूर्णांक channel_count = 0x0;

	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_TEST_AUDIO_MODE, &data);
	अगर (rlen < 0) अणु
		DRM_ERROR("failed to read link audio mode. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	/* Sampling Rate - Bits 3:0 */
	sampling_rate = data & 0xF;
	अगर (sampling_rate > max_audio_sampling_rate) अणु
		DRM_ERROR("sampling rate (0x%x) greater than max (0x%x)\n",
				sampling_rate, max_audio_sampling_rate);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	/* Channel Count - Bits 7:4 */
	channel_count = ((data & 0xF0) >> 4) + 1;
	अगर (channel_count > max_audio_channel_count) अणु
		DRM_ERROR("channel_count (0x%x) greater than max (0x%x)\n",
				channel_count, max_audio_channel_count);
		ret = -EINVAL;
		जाओ निकास;
	पूर्ण

	link->dp_link.test_audio.test_audio_sampling_rate = sampling_rate;
	link->dp_link.test_audio.test_audio_channel_count = channel_count;
	DRM_DEBUG_DP("sampling_rate = 0x%x, channel_count = 0x%x\n",
					sampling_rate, channel_count);
निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक dp_link_parse_audio_pattern_params(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;

	ret = dp_link_parse_audio_mode(link);
	अगर (ret)
		जाओ निकास;

	ret = dp_link_parse_audio_pattern_type(link);
	अगर (ret)
		जाओ निकास;

	ret = dp_link_parse_audio_channel_period(link);

निकास:
	वापस ret;
पूर्ण

अटल bool dp_link_is_video_pattern_valid(u32 pattern)
अणु
	चयन (pattern) अणु
	हाल DP_NO_TEST_PATTERN:
	हाल DP_COLOR_RAMP:
	हाल DP_BLACK_AND_WHITE_VERTICAL_LINES:
	हाल DP_COLOR_SQUARE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/**
 * dp_link_is_bit_depth_valid() - validates the bit depth requested
 * @tbd: bit depth requested by the sink
 *
 * Returns true अगर the requested bit depth is supported.
 */
अटल bool dp_link_is_bit_depth_valid(u32 tbd)
अणु
	/* DP_TEST_VIDEO_PATTERN_NONE is treated as invalid */
	चयन (tbd) अणु
	हाल DP_TEST_BIT_DEPTH_6:
	हाल DP_TEST_BIT_DEPTH_8:
	हाल DP_TEST_BIT_DEPTH_10:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक dp_link_parse_timing_params1(काष्ठा dp_link_निजी *link,
					पूर्णांक addr, पूर्णांक len, u32 *val)
अणु
	u8 bp[2];
	पूर्णांक rlen;

	अगर (len != 2)
		वापस -EINVAL;

	/* Read the requested video link pattern (Byte 0x221). */
	rlen = drm_dp_dpcd_पढ़ो(link->aux, addr, bp, len);
	अगर (rlen < len) अणु
		DRM_ERROR("failed to read 0x%x\n", addr);
		वापस -EINVAL;
	पूर्ण

	*val = bp[1] | (bp[0] << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_link_parse_timing_params2(काष्ठा dp_link_निजी *link,
					पूर्णांक addr, पूर्णांक len,
					u32 *val1, u32 *val2)
अणु
	u8 bp[2];
	पूर्णांक rlen;

	अगर (len != 2)
		वापस -EINVAL;

	/* Read the requested video link pattern (Byte 0x221). */
	rlen = drm_dp_dpcd_पढ़ो(link->aux, addr, bp, len);
	अगर (rlen < len) अणु
		DRM_ERROR("failed to read 0x%x\n", addr);
		वापस -EINVAL;
	पूर्ण

	*val1 = (bp[0] & BIT(7)) >> 7;
	*val2 = bp[1] | ((bp[0] & 0x7F) << 8);

	वापस 0;
पूर्ण

अटल पूर्णांक dp_link_parse_timing_params3(काष्ठा dp_link_निजी *link,
					पूर्णांक addr, u32 *val)
अणु
	u8 bp;
	u32 len = 1;
	पूर्णांक rlen;

	rlen = drm_dp_dpcd_पढ़ो(link->aux, addr, &bp, len);
	अगर (rlen < 1) अणु
		DRM_ERROR("failed to read 0x%x\n", addr);
		वापस -EINVAL;
	पूर्ण
	*val = bp;

	वापस 0;
पूर्ण

/**
 * dp_parse_video_pattern_params() - parses video pattern parameters from DPCD
 * @link: Display Port Driver data
 *
 * Returns 0 अगर it successfully parses the video link pattern and the link
 * bit depth requested by the sink and, and अगर the values parsed are valid.
 */
अटल पूर्णांक dp_link_parse_video_pattern_params(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;
	sमाप_प्रकार rlen;
	u8 bp;

	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_TEST_PATTERN, &bp);
	अगर (rlen < 0) अणु
		DRM_ERROR("failed to read link video pattern. rlen=%zd\n",
			rlen);
		वापस rlen;
	पूर्ण

	अगर (!dp_link_is_video_pattern_valid(bp)) अणु
		DRM_ERROR("invalid link video pattern = 0x%x\n", bp);
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	link->dp_link.test_video.test_video_pattern = bp;

	/* Read the requested color bit depth and dynamic range (Byte 0x232) */
	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_TEST_MISC0, &bp);
	अगर (rlen < 0) अणु
		DRM_ERROR("failed to read link bit depth. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	/* Dynamic Range */
	link->dp_link.test_video.test_dyn_range =
			(bp & DP_TEST_DYNAMIC_RANGE_CEA);

	/* Color bit depth */
	bp &= DP_TEST_BIT_DEPTH_MASK;
	अगर (!dp_link_is_bit_depth_valid(bp)) अणु
		DRM_ERROR("invalid link bit depth = 0x%x\n", bp);
		ret = -EINVAL;
		वापस ret;
	पूर्ण

	link->dp_link.test_video.test_bit_depth = bp;

	/* resolution timing params */
	ret = dp_link_parse_timing_params1(link, DP_TEST_H_TOTAL_HI, 2,
			&link->dp_link.test_video.test_h_total);
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_htotal(DP_TEST_H_TOTAL_HI)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params1(link, DP_TEST_V_TOTAL_HI, 2,
			&link->dp_link.test_video.test_v_total);
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_v_total(DP_TEST_V_TOTAL_HI)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params1(link, DP_TEST_H_START_HI, 2,
			&link->dp_link.test_video.test_h_start);
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_h_start(DP_TEST_H_START_HI)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params1(link, DP_TEST_V_START_HI, 2,
			&link->dp_link.test_video.test_v_start);
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_v_start(DP_TEST_V_START_HI)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params2(link, DP_TEST_HSYNC_HI, 2,
			&link->dp_link.test_video.test_hsync_pol,
			&link->dp_link.test_video.test_hsync_width);
	अगर (ret) अणु
		DRM_ERROR("failed to parse (DP_TEST_HSYNC_HI)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params2(link, DP_TEST_VSYNC_HI, 2,
			&link->dp_link.test_video.test_vsync_pol,
			&link->dp_link.test_video.test_vsync_width);
	अगर (ret) अणु
		DRM_ERROR("failed to parse (DP_TEST_VSYNC_HI)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params1(link, DP_TEST_H_WIDTH_HI, 2,
			&link->dp_link.test_video.test_h_width);
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_h_width(DP_TEST_H_WIDTH_HI)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params1(link, DP_TEST_V_HEIGHT_HI, 2,
			&link->dp_link.test_video.test_v_height);
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_v_height\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params3(link, DP_TEST_MISC1,
		&link->dp_link.test_video.test_rr_d);
	link->dp_link.test_video.test_rr_d &= DP_TEST_REFRESH_DENOMINATOR;
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_rr_d (DP_TEST_MISC1)\n");
		वापस ret;
	पूर्ण

	ret = dp_link_parse_timing_params3(link, DP_TEST_REFRESH_RATE_NUMERATOR,
		&link->dp_link.test_video.test_rr_n);
	अगर (ret) अणु
		DRM_ERROR("failed to parse test_rr_n\n");
		वापस ret;
	पूर्ण

	DRM_DEBUG_DP("link video pattern = 0x%x\n"
		"link dynamic range = 0x%x\n"
		"link bit depth = 0x%x\n"
		"TEST_H_TOTAL = %d, TEST_V_TOTAL = %d\n"
		"TEST_H_START = %d, TEST_V_START = %d\n"
		"TEST_HSYNC_POL = %d\n"
		"TEST_HSYNC_WIDTH = %d\n"
		"TEST_VSYNC_POL = %d\n"
		"TEST_VSYNC_WIDTH = %d\n"
		"TEST_H_WIDTH = %d\n"
		"TEST_V_HEIGHT = %d\n"
		"TEST_REFRESH_DENOMINATOR = %d\n"
		 "TEST_REFRESH_NUMERATOR = %d\n",
		link->dp_link.test_video.test_video_pattern,
		link->dp_link.test_video.test_dyn_range,
		link->dp_link.test_video.test_bit_depth,
		link->dp_link.test_video.test_h_total,
		link->dp_link.test_video.test_v_total,
		link->dp_link.test_video.test_h_start,
		link->dp_link.test_video.test_v_start,
		link->dp_link.test_video.test_hsync_pol,
		link->dp_link.test_video.test_hsync_width,
		link->dp_link.test_video.test_vsync_pol,
		link->dp_link.test_video.test_vsync_width,
		link->dp_link.test_video.test_h_width,
		link->dp_link.test_video.test_v_height,
		link->dp_link.test_video.test_rr_d,
		link->dp_link.test_video.test_rr_n);

	वापस ret;
पूर्ण

/**
 * dp_link_parse_link_training_params() - parses link training parameters from
 * DPCD
 * @link: Display Port Driver data
 *
 * Returns 0 अगर it successfully parses the link rate (Byte 0x219) and lane
 * count (Byte 0x220), and अगर these values parse are valid.
 */
अटल पूर्णांक dp_link_parse_link_training_params(काष्ठा dp_link_निजी *link)
अणु
	u8 bp;
	sमाप_प्रकार rlen;

	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_TEST_LINK_RATE,	&bp);
	अगर (rlen < 0) अणु
		DRM_ERROR("failed to read link rate. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	अगर (!is_link_rate_valid(bp)) अणु
		DRM_ERROR("invalid link rate = 0x%x\n", bp);
		वापस -EINVAL;
	पूर्ण

	link->request.test_link_rate = bp;
	DRM_DEBUG_DP("link rate = 0x%x\n", link->request.test_link_rate);

	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_TEST_LANE_COUNT, &bp);
	अगर (rlen < 0) अणु
		DRM_ERROR("failed to read lane count. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण
	bp &= DP_MAX_LANE_COUNT_MASK;

	अगर (!is_lane_count_valid(bp)) अणु
		DRM_ERROR("invalid lane count = 0x%x\n", bp);
		वापस -EINVAL;
	पूर्ण

	link->request.test_lane_count = bp;
	DRM_DEBUG_DP("lane count = 0x%x\n", link->request.test_lane_count);
	वापस 0;
पूर्ण

/**
 * dp_parse_phy_test_params() - parses the phy link parameters
 * @link: Display Port Driver data
 *
 * Parses the DPCD (Byte 0x248) क्रम the DP PHY link pattern that is being
 * requested.
 */
अटल पूर्णांक dp_link_parse_phy_test_params(काष्ठा dp_link_निजी *link)
अणु
	u8 data;
	sमाप_प्रकार rlen;

	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_PHY_TEST_PATTERN,
					&data);
	अगर (rlen < 0) अणु
		DRM_ERROR("failed to read phy link pattern. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	link->dp_link.phy_params.phy_test_pattern_sel = data & 0x07;

	DRM_DEBUG_DP("phy_test_pattern_sel = 0x%x\n", data);

	चयन (data) अणु
	हाल DP_PHY_TEST_PATTERN_SEL_MASK:
	हाल DP_PHY_TEST_PATTERN_NONE:
	हाल DP_PHY_TEST_PATTERN_D10_2:
	हाल DP_PHY_TEST_PATTERN_ERROR_COUNT:
	हाल DP_PHY_TEST_PATTERN_PRBS7:
	हाल DP_PHY_TEST_PATTERN_80BIT_CUSTOM:
	हाल DP_PHY_TEST_PATTERN_CP2520:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * dp_link_is_video_audio_test_requested() - checks क्रम audio/video link request
 * @link: link requested by the sink
 *
 * Returns true अगर the requested link is a permitted audio/video link.
 */
अटल bool dp_link_is_video_audio_test_requested(u32 link)
अणु
	u8 video_audio_test = (DP_TEST_LINK_VIDEO_PATTERN |
				DP_TEST_LINK_AUDIO_PATTERN |
				DP_TEST_LINK_AUDIO_DISABLED_VIDEO);

	वापस ((link & video_audio_test) &&
		!(link & ~video_audio_test));
पूर्ण

/**
 * dp_link_parse_request() - parses link request parameters from sink
 * @link: Display Port Driver data
 *
 * Parses the DPCD to check अगर an स्वतःmated link is requested (Byte 0x201),
 * and what type of link स्वतःmation is being requested (Byte 0x218).
 */
अटल पूर्णांक dp_link_parse_request(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;
	u8 data;
	sमाप_प्रकार rlen;

	/**
	 * Read the device service IRQ vector (Byte 0x201) to determine
	 * whether an स्वतःmated link has been requested by the sink.
	 */
	rlen = drm_dp_dpcd_पढ़ोb(link->aux,
				DP_DEVICE_SERVICE_IRQ_VECTOR, &data);
	अगर (rlen < 0) अणु
		DRM_ERROR("aux read failed. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	DRM_DEBUG_DP("device service irq vector = 0x%x\n", data);

	अगर (!(data & DP_AUTOMATED_TEST_REQUEST)) अणु
		DRM_DEBUG_DP("no test requested\n");
		वापस 0;
	पूर्ण

	/**
	 * Read the link request byte (Byte 0x218) to determine what type
	 * of स्वतःmated link has been requested by the sink.
	 */
	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_TEST_REQUEST, &data);
	अगर (rlen < 0) अणु
		DRM_ERROR("aux read failed. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	अगर (!data || (data == DP_TEST_LINK_FAUX_PATTERN)) अणु
		DRM_DEBUG_DP("link 0x%x not supported\n", data);
		जाओ end;
	पूर्ण

	DRM_DEBUG_DP("Test:(0x%x) requested\n", data);
	link->request.test_requested = data;
	अगर (link->request.test_requested == DP_TEST_LINK_PHY_TEST_PATTERN) अणु
		ret = dp_link_parse_phy_test_params(link);
		अगर (ret)
			जाओ end;
		ret = dp_link_parse_link_training_params(link);
		अगर (ret)
			जाओ end;
	पूर्ण

	अगर (link->request.test_requested == DP_TEST_LINK_TRAINING) अणु
		ret = dp_link_parse_link_training_params(link);
		अगर (ret)
			जाओ end;
	पूर्ण

	अगर (dp_link_is_video_audio_test_requested(
			link->request.test_requested)) अणु
		ret = dp_link_parse_video_pattern_params(link);
		अगर (ret)
			जाओ end;

		ret = dp_link_parse_audio_pattern_params(link);
	पूर्ण
end:
	/*
	 * Send a DP_TEST_ACK अगर all link parameters are valid, otherwise send
	 * a DP_TEST_NAK.
	 */
	अगर (ret) अणु
		link->dp_link.test_response = DP_TEST_NAK;
	पूर्ण अन्यथा अणु
		अगर (link->request.test_requested != DP_TEST_LINK_EDID_READ)
			link->dp_link.test_response = DP_TEST_ACK;
		अन्यथा
			link->dp_link.test_response =
				DP_TEST_EDID_CHECKSUM_WRITE;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * dp_link_parse_sink_count() - parses the sink count
 * @dp_link: poपूर्णांकer to link module data
 *
 * Parses the DPCD to check अगर there is an update to the sink count
 * (Byte 0x200), and whether all the sink devices connected have Content
 * Protection enabled.
 */
अटल पूर्णांक dp_link_parse_sink_count(काष्ठा dp_link *dp_link)
अणु
	sमाप_प्रकार rlen;
	bool cp_पढ़ोy;

	काष्ठा dp_link_निजी *link = container_of(dp_link,
			काष्ठा dp_link_निजी, dp_link);

	rlen = drm_dp_dpcd_पढ़ोb(link->aux, DP_SINK_COUNT,
				 &link->dp_link.sink_count);
	अगर (rlen < 0) अणु
		DRM_ERROR("sink count read failed. rlen=%zd\n", rlen);
		वापस rlen;
	पूर्ण

	cp_पढ़ोy = link->dp_link.sink_count & DP_SINK_CP_READY;

	link->dp_link.sink_count =
		DP_GET_SINK_COUNT(link->dp_link.sink_count);

	DRM_DEBUG_DP("sink_count = 0x%x, cp_ready = 0x%x\n",
		link->dp_link.sink_count, cp_पढ़ोy);
	वापस 0;
पूर्ण

अटल व्योम dp_link_parse_sink_status_field(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक len = 0;

	link->prev_sink_count = link->dp_link.sink_count;
	dp_link_parse_sink_count(&link->dp_link);

	len = drm_dp_dpcd_पढ़ो_link_status(link->aux,
		link->link_status);
	अगर (len < DP_LINK_STATUS_SIZE)
		DRM_ERROR("DP link status read failed\n");
	dp_link_parse_request(link);
पूर्ण

/**
 * dp_link_process_link_training_request() - processes new training requests
 * @link: Display Port link data
 *
 * This function will handle new link training requests that are initiated by
 * the sink. In particular, it will update the requested lane count and link
 * rate, and then trigger the link retraining procedure.
 *
 * The function will वापस 0 अगर a link training request has been processed,
 * otherwise it will वापस -EINVAL.
 */
अटल पूर्णांक dp_link_process_link_training_request(काष्ठा dp_link_निजी *link)
अणु
	अगर (link->request.test_requested != DP_TEST_LINK_TRAINING)
		वापस -EINVAL;

	DRM_DEBUG_DP("Test:0x%x link rate = 0x%x, lane count = 0x%x\n",
			DP_TEST_LINK_TRAINING,
			link->request.test_link_rate,
			link->request.test_lane_count);

	link->dp_link.link_params.num_lanes = link->request.test_lane_count;
	link->dp_link.link_params.rate = 
		drm_dp_bw_code_to_link_rate(link->request.test_link_rate);

	वापस 0;
पूर्ण

bool dp_link_send_test_response(काष्ठा dp_link *dp_link)
अणु
	काष्ठा dp_link_निजी *link = शून्य;
	पूर्णांक ret = 0;

	अगर (!dp_link) अणु
		DRM_ERROR("invalid input\n");
		वापस false;
	पूर्ण

	link = container_of(dp_link, काष्ठा dp_link_निजी, dp_link);

	ret = drm_dp_dpcd_ग_लिखोb(link->aux, DP_TEST_RESPONSE,
			dp_link->test_response);

	वापस ret == 1;
पूर्ण

पूर्णांक dp_link_psm_config(काष्ठा dp_link *dp_link,
			      काष्ठा dp_link_info *link_info, bool enable)
अणु
	काष्ठा dp_link_निजी *link = शून्य;
	पूर्णांक ret = 0;

	अगर (!dp_link) अणु
		DRM_ERROR("invalid params\n");
		वापस -EINVAL;
	पूर्ण

	link = container_of(dp_link, काष्ठा dp_link_निजी, dp_link);

	mutex_lock(&link->psm_mutex);
	अगर (enable)
		ret = dp_aux_link_घातer_करोwn(link->aux, link_info);
	अन्यथा
		ret = dp_aux_link_घातer_up(link->aux, link_info);

	अगर (ret)
		DRM_ERROR("Failed to %s low power mode\n", enable ?
							"enter" : "exit");
	अन्यथा
		dp_link->psm_enabled = enable;

	mutex_unlock(&link->psm_mutex);
	वापस ret;
पूर्ण

bool dp_link_send_edid_checksum(काष्ठा dp_link *dp_link, u8 checksum)
अणु
	काष्ठा dp_link_निजी *link = शून्य;
	पूर्णांक ret = 0;

	अगर (!dp_link) अणु
		DRM_ERROR("invalid input\n");
		वापस false;
	पूर्ण

	link = container_of(dp_link, काष्ठा dp_link_निजी, dp_link);

	ret = drm_dp_dpcd_ग_लिखोb(link->aux, DP_TEST_EDID_CHECKSUM,
						checksum);
	वापस ret == 1;
पूर्ण

अटल पूर्णांक dp_link_parse_vx_px(काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;

	DRM_DEBUG_DP("vx: 0=%d, 1=%d, 2=%d, 3=%d\n",
		drm_dp_get_adjust_request_voltage(link->link_status, 0),
		drm_dp_get_adjust_request_voltage(link->link_status, 1),
		drm_dp_get_adjust_request_voltage(link->link_status, 2),
		drm_dp_get_adjust_request_voltage(link->link_status, 3));

	DRM_DEBUG_DP("px: 0=%d, 1=%d, 2=%d, 3=%d\n",
		drm_dp_get_adjust_request_pre_emphasis(link->link_status, 0),
		drm_dp_get_adjust_request_pre_emphasis(link->link_status, 1),
		drm_dp_get_adjust_request_pre_emphasis(link->link_status, 2),
		drm_dp_get_adjust_request_pre_emphasis(link->link_status, 3));

	/**
	 * Update the voltage and pre-emphasis levels as per DPCD request
	 * vector.
	 */
	DRM_DEBUG_DP("Current: v_level = 0x%x, p_level = 0x%x\n",
			link->dp_link.phy_params.v_level,
			link->dp_link.phy_params.p_level);
	link->dp_link.phy_params.v_level =
		drm_dp_get_adjust_request_voltage(link->link_status, 0);
	link->dp_link.phy_params.p_level =
		drm_dp_get_adjust_request_pre_emphasis(link->link_status, 0);

	link->dp_link.phy_params.p_level >>= DP_TRAIN_PRE_EMPHASIS_SHIFT;

	DRM_DEBUG_DP("Requested: v_level = 0x%x, p_level = 0x%x\n",
			link->dp_link.phy_params.v_level,
			link->dp_link.phy_params.p_level);

	वापस ret;
पूर्ण

/**
 * dp_link_process_phy_test_pattern_request() - process new phy link requests
 * @link: Display Port Driver data
 *
 * This function will handle new phy link pattern requests that are initiated
 * by the sink. The function will वापस 0 अगर a phy link pattern has been
 * processed, otherwise it will वापस -EINVAL.
 */
अटल पूर्णांक dp_link_process_phy_test_pattern_request(
		काष्ठा dp_link_निजी *link)
अणु
	पूर्णांक ret = 0;

	अगर (!(link->request.test_requested & DP_TEST_LINK_PHY_TEST_PATTERN)) अणु
		DRM_DEBUG_DP("no phy test\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!is_link_rate_valid(link->request.test_link_rate) ||
		!is_lane_count_valid(link->request.test_lane_count)) अणु
		DRM_ERROR("Invalid: link rate = 0x%x,lane count = 0x%x\n",
				link->request.test_link_rate,
				link->request.test_lane_count);
		वापस -EINVAL;
	पूर्ण

	DRM_DEBUG_DP("Current: rate = 0x%x, lane count = 0x%x\n",
			link->dp_link.link_params.rate,
			link->dp_link.link_params.num_lanes);

	DRM_DEBUG_DP("Requested: rate = 0x%x, lane count = 0x%x\n",
			link->request.test_link_rate,
			link->request.test_lane_count);

	link->dp_link.link_params.num_lanes = link->request.test_lane_count;
	link->dp_link.link_params.rate =
		drm_dp_bw_code_to_link_rate(link->request.test_link_rate);

	ret = dp_link_parse_vx_px(link);

	अगर (ret)
		DRM_ERROR("parse_vx_px failed. ret=%d\n", ret);

	वापस ret;
पूर्ण

अटल u8 get_link_status(स्थिर u8 link_status[DP_LINK_STATUS_SIZE], पूर्णांक r)
अणु
	वापस link_status[r - DP_LANE0_1_STATUS];
पूर्ण

/**
 * dp_link_process_link_status_update() - processes link status updates
 * @link: Display Port link module data
 *
 * This function will check क्रम changes in the link status, e.g. घड़ी
 * recovery करोne on all lanes, and trigger link training अगर there is a
 * failure/error on the link.
 *
 * The function will वापस 0 अगर the a link status update has been processed,
 * otherwise it will वापस -EINVAL.
 */
अटल पूर्णांक dp_link_process_link_status_update(काष्ठा dp_link_निजी *link)
अणु
       bool channel_eq_करोne = drm_dp_channel_eq_ok(link->link_status,
                       link->dp_link.link_params.num_lanes);

       bool घड़ी_recovery_करोne = drm_dp_घड़ी_recovery_ok(link->link_status,
                       link->dp_link.link_params.num_lanes);

       DRM_DEBUG_DP("channel_eq_done = %d, clock_recovery_done = %d\n",
                        channel_eq_करोne, घड़ी_recovery_करोne);

       अगर (channel_eq_करोne && घड़ी_recovery_करोne)
               वापस -EINVAL;


       वापस 0;
पूर्ण

/**
 * dp_link_process_करोwnstream_port_status_change() - process port status changes
 * @link: Display Port Driver data
 *
 * This function will handle करोwnstream port updates that are initiated by
 * the sink. If the करोwnstream port status has changed, the EDID is पढ़ो via
 * AUX.
 *
 * The function will वापस 0 अगर a करोwnstream port update has been
 * processed, otherwise it will वापस -EINVAL.
 */
अटल पूर्णांक dp_link_process_ds_port_status_change(काष्ठा dp_link_निजी *link)
अणु
	अगर (get_link_status(link->link_status, DP_LANE_ALIGN_STATUS_UPDATED) &
					DP_DOWNSTREAM_PORT_STATUS_CHANGED)
		जाओ reset;

	अगर (link->prev_sink_count == link->dp_link.sink_count)
		वापस -EINVAL;

reset:
	/* reset prev_sink_count */
	link->prev_sink_count = link->dp_link.sink_count;

	वापस 0;
पूर्ण

अटल bool dp_link_is_video_pattern_requested(काष्ठा dp_link_निजी *link)
अणु
	वापस (link->request.test_requested & DP_TEST_LINK_VIDEO_PATTERN)
		&& !(link->request.test_requested &
		DP_TEST_LINK_AUDIO_DISABLED_VIDEO);
पूर्ण

अटल bool dp_link_is_audio_pattern_requested(काष्ठा dp_link_निजी *link)
अणु
	वापस (link->request.test_requested & DP_TEST_LINK_AUDIO_PATTERN);
पूर्ण

अटल व्योम dp_link_reset_data(काष्ठा dp_link_निजी *link)
अणु
	link->request = (स्थिर काष्ठा dp_link_request)अणु 0 पूर्ण;
	link->dp_link.test_video = (स्थिर काष्ठा dp_link_test_video)अणु 0 पूर्ण;
	link->dp_link.test_video.test_bit_depth = DP_TEST_BIT_DEPTH_UNKNOWN;
	link->dp_link.test_audio = (स्थिर काष्ठा dp_link_test_audio)अणु 0 पूर्ण;
	link->dp_link.phy_params.phy_test_pattern_sel = 0;
	link->dp_link.sink_request = 0;
	link->dp_link.test_response = 0;
पूर्ण

/**
 * dp_link_process_request() - handle HPD IRQ transition to HIGH
 * @dp_link: poपूर्णांकer to link module data
 *
 * This function will handle the HPD IRQ state transitions from LOW to HIGH
 * (including हालs when there are back to back HPD IRQ HIGH) indicating
 * the start of a new link training request or sink status update.
 */
पूर्णांक dp_link_process_request(काष्ठा dp_link *dp_link)
अणु
	पूर्णांक ret = 0;
	काष्ठा dp_link_निजी *link;

	अगर (!dp_link) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	link = container_of(dp_link, काष्ठा dp_link_निजी, dp_link);

	dp_link_reset_data(link);

	dp_link_parse_sink_status_field(link);

	अगर (link->request.test_requested == DP_TEST_LINK_EDID_READ) अणु
		dp_link->sink_request |= DP_TEST_LINK_EDID_READ;
		वापस ret;
	पूर्ण

	ret = dp_link_process_ds_port_status_change(link);
	अगर (!ret) अणु
		dp_link->sink_request |= DS_PORT_STATUS_CHANGED;
		वापस ret;
	पूर्ण

	ret = dp_link_process_link_training_request(link);
	अगर (!ret) अणु
		dp_link->sink_request |= DP_TEST_LINK_TRAINING;
		वापस ret;
	पूर्ण

	ret = dp_link_process_phy_test_pattern_request(link);
	अगर (!ret) अणु
		dp_link->sink_request |= DP_TEST_LINK_PHY_TEST_PATTERN;
		वापस ret;
	पूर्ण

	ret = dp_link_process_link_status_update(link);
	अगर (!ret) अणु
		dp_link->sink_request |= DP_LINK_STATUS_UPDATED;
		वापस ret;
	पूर्ण

	अगर (dp_link_is_video_pattern_requested(link)) अणु
		ret = 0;
		dp_link->sink_request |= DP_TEST_LINK_VIDEO_PATTERN;
	पूर्ण

	अगर (dp_link_is_audio_pattern_requested(link)) अणु
		dp_link->sink_request |= DP_TEST_LINK_AUDIO_PATTERN;
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक dp_link_get_colorimetry_config(काष्ठा dp_link *dp_link)
अणु
	u32 cc;
	काष्ठा dp_link_निजी *link;

	अगर (!dp_link) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	link = container_of(dp_link, काष्ठा dp_link_निजी, dp_link);

	/*
	 * Unless a video pattern CTS test is ongoing, use RGB_VESA
	 * Only RGB_VESA and RGB_CEA supported क्रम now
	 */
	अगर (dp_link_is_video_pattern_requested(link))
		cc = link->dp_link.test_video.test_dyn_range;
	अन्यथा
		cc = DP_TEST_DYNAMIC_RANGE_VESA;

	वापस cc;
पूर्ण

पूर्णांक dp_link_adjust_levels(काष्ठा dp_link *dp_link, u8 *link_status)
अणु
	पूर्णांक i;
	पूर्णांक v_max = 0, p_max = 0;

	अगर (!dp_link) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	/* use the max level across lanes */
	क्रम (i = 0; i < dp_link->link_params.num_lanes; i++) अणु
		u8 data_v = drm_dp_get_adjust_request_voltage(link_status, i);
		u8 data_p = drm_dp_get_adjust_request_pre_emphasis(link_status,
									 i);
		DRM_DEBUG_DP("lane=%d req_vol_swing=%d req_pre_emphasis=%d\n",
				i, data_v, data_p);
		अगर (v_max < data_v)
			v_max = data_v;
		अगर (p_max < data_p)
			p_max = data_p;
	पूर्ण

	dp_link->phy_params.v_level = v_max >> DP_TRAIN_VOLTAGE_SWING_SHIFT;
	dp_link->phy_params.p_level = p_max >> DP_TRAIN_PRE_EMPHASIS_SHIFT;

	/**
	 * Adjust the voltage swing and pre-emphasis level combination to within
	 * the allowable range.
	 */
	अगर (dp_link->phy_params.v_level > DP_TRAIN_VOLTAGE_SWING_MAX) अणु
		DRM_DEBUG_DP("Requested vSwingLevel=%d, change to %d\n",
			dp_link->phy_params.v_level,
			DP_TRAIN_VOLTAGE_SWING_MAX);
		dp_link->phy_params.v_level = DP_TRAIN_VOLTAGE_SWING_MAX;
	पूर्ण

	अगर (dp_link->phy_params.p_level > DP_TRAIN_PRE_EMPHASIS_MAX) अणु
		DRM_DEBUG_DP("Requested preEmphasisLevel=%d, change to %d\n",
			dp_link->phy_params.p_level,
			DP_TRAIN_PRE_EMPHASIS_MAX);
		dp_link->phy_params.p_level = DP_TRAIN_PRE_EMPHASIS_MAX;
	पूर्ण

	अगर ((dp_link->phy_params.p_level > DP_TRAIN_PRE_EMPHASIS_LVL_1)
		&& (dp_link->phy_params.v_level ==
			DP_TRAIN_VOLTAGE_SWING_LVL_2)) अणु
		DRM_DEBUG_DP("Requested preEmphasisLevel=%d, change to %d\n",
			dp_link->phy_params.p_level,
			DP_TRAIN_PRE_EMPHASIS_LVL_1);
		dp_link->phy_params.p_level = DP_TRAIN_PRE_EMPHASIS_LVL_1;
	पूर्ण

	DRM_DEBUG_DP("adjusted: v_level=%d, p_level=%d\n",
		dp_link->phy_params.v_level, dp_link->phy_params.p_level);

	वापस 0;
पूर्ण

व्योम dp_link_reset_phy_params_vx_px(काष्ठा dp_link *dp_link)
अणु
	dp_link->phy_params.v_level = 0;
	dp_link->phy_params.p_level = 0;
पूर्ण

u32 dp_link_get_test_bits_depth(काष्ठा dp_link *dp_link, u32 bpp)
अणु
	u32 tbd;

	/*
	 * Few simplistic rules and assumptions made here:
	 *    1. Test bit depth is bit depth per color component
	 *    2. Assume 3 color components
	 */
	चयन (bpp) अणु
	हाल 18:
		tbd = DP_TEST_BIT_DEPTH_6;
		अवरोध;
	हाल 24:
		tbd = DP_TEST_BIT_DEPTH_8;
		अवरोध;
	हाल 30:
		tbd = DP_TEST_BIT_DEPTH_10;
		अवरोध;
	शेष:
		tbd = DP_TEST_BIT_DEPTH_UNKNOWN;
		अवरोध;
	पूर्ण

	अगर (tbd != DP_TEST_BIT_DEPTH_UNKNOWN)
		tbd = (tbd >> DP_TEST_BIT_DEPTH_SHIFT);

	वापस tbd;
पूर्ण

काष्ठा dp_link *dp_link_get(काष्ठा device *dev, काष्ठा drm_dp_aux *aux)
अणु
	काष्ठा dp_link_निजी *link;
	काष्ठा dp_link *dp_link;

	अगर (!dev || !aux) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	link = devm_kzalloc(dev, माप(*link), GFP_KERNEL);
	अगर (!link)
		वापस ERR_PTR(-ENOMEM);

	link->dev   = dev;
	link->aux   = aux;

	mutex_init(&link->psm_mutex);
	dp_link = &link->dp_link;

	वापस dp_link;
पूर्ण
