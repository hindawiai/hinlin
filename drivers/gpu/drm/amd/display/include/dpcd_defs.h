<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_DPCD_DEFS_H__
#घोषणा __DAL_DPCD_DEFS_H__

#समावेश <drm/drm_dp_helper.h>
#अगर_अघोषित DP_SINK_HW_REVISION_START // can हटाओ this once the define माला_लो पूर्णांकo linux drm_dp_helper.h
#घोषणा DP_SINK_HW_REVISION_START 0x409
#पूर्ण_अगर

क्रमागत dpcd_revision अणु
	DPCD_REV_10 = 0x10,
	DPCD_REV_11 = 0x11,
	DPCD_REV_12 = 0x12,
	DPCD_REV_13 = 0x13,
	DPCD_REV_14 = 0x14
पूर्ण;

/* these are the types stored at DOWNSTREAMPORT_PRESENT */
क्रमागत dpcd_करोwnstream_port_type अणु
	DOWNSTREAM_DP = 0,
	DOWNSTREAM_VGA,
	DOWNSTREAM_DVI_HDMI_DP_PLUS_PLUS,/* DVI, HDMI, DP++ */
	DOWNSTREAM_NONDDC /* has no EDID (TV,CV) */
पूर्ण;

क्रमागत dpcd_link_test_patterns अणु
	LINK_TEST_PATTERN_NONE = 0,
	LINK_TEST_PATTERN_COLOR_RAMP,
	LINK_TEST_PATTERN_VERTICAL_BARS,
	LINK_TEST_PATTERN_COLOR_SQUARES
पूर्ण;

क्रमागत dpcd_test_color_क्रमmat अणु
	TEST_COLOR_FORMAT_RGB = 0,
	TEST_COLOR_FORMAT_YCBCR422,
	TEST_COLOR_FORMAT_YCBCR444
पूर्ण;

क्रमागत dpcd_test_bit_depth अणु
	TEST_BIT_DEPTH_6 = 0,
	TEST_BIT_DEPTH_8,
	TEST_BIT_DEPTH_10,
	TEST_BIT_DEPTH_12,
	TEST_BIT_DEPTH_16
पूर्ण;

/* PHY (encoder) test patterns
The order of test patterns follows DPCD रेजिस्टर PHY_TEST_PATTERN (0x248)
*/
क्रमागत dpcd_phy_test_patterns अणु
	PHY_TEST_PATTERN_NONE = 0,
	PHY_TEST_PATTERN_D10_2,
	PHY_TEST_PATTERN_SYMBOL_ERROR,
	PHY_TEST_PATTERN_PRBS7,
	PHY_TEST_PATTERN_80BIT_CUSTOM,/* For DP1.2 only */
	PHY_TEST_PATTERN_CP2520_1,
	PHY_TEST_PATTERN_CP2520_2,
	PHY_TEST_PATTERN_CP2520_3, /* same as TPS4 */
पूर्ण;

क्रमागत dpcd_test_dyn_range अणु
	TEST_DYN_RANGE_VESA = 0,
	TEST_DYN_RANGE_CEA
पूर्ण;

क्रमागत dpcd_audio_test_pattern अणु
	AUDIO_TEST_PATTERN_OPERATOR_DEFINED = 0,/* direct HW translation */
	AUDIO_TEST_PATTERN_SAWTOOTH
पूर्ण;

क्रमागत dpcd_audio_sampling_rate अणु
	AUDIO_SAMPLING_RATE_32KHZ = 0,/* direct HW translation */
	AUDIO_SAMPLING_RATE_44_1KHZ,
	AUDIO_SAMPLING_RATE_48KHZ,
	AUDIO_SAMPLING_RATE_88_2KHZ,
	AUDIO_SAMPLING_RATE_96KHZ,
	AUDIO_SAMPLING_RATE_176_4KHZ,
	AUDIO_SAMPLING_RATE_192KHZ
पूर्ण;

क्रमागत dpcd_audio_channels अणु
	AUDIO_CHANNELS_1 = 0,/* direct HW translation */
	AUDIO_CHANNELS_2,
	AUDIO_CHANNELS_3,
	AUDIO_CHANNELS_4,
	AUDIO_CHANNELS_5,
	AUDIO_CHANNELS_6,
	AUDIO_CHANNELS_7,
	AUDIO_CHANNELS_8,

	AUDIO_CHANNELS_COUNT
पूर्ण;

क्रमागत dpcd_audio_test_pattern_periods अणु
	DPCD_AUDIO_TEST_PATTERN_PERIOD_NOTUSED = 0,/* direct HW translation */
	DPCD_AUDIO_TEST_PATTERN_PERIOD_3,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_6,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_12,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_24,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_48,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_96,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_192,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_384,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_768,
	DPCD_AUDIO_TEST_PATTERN_PERIOD_1536
पूर्ण;

/* This क्रमागत is क्रम programming DPCD TRAINING_PATTERN_SET */
क्रमागत dpcd_training_patterns अणु
	DPCD_TRAINING_PATTERN_VIDEOIDLE = 0,/* direct HW translation! */
	DPCD_TRAINING_PATTERN_1,
	DPCD_TRAINING_PATTERN_2,
	DPCD_TRAINING_PATTERN_3,
	DPCD_TRAINING_PATTERN_4 = 7
पूर्ण;

/* This क्रमागत is क्रम use with PsrSinkPsrStatus.bits.sinkSelfRefreshStatus
It defines the possible PSR states. */
क्रमागत dpcd_psr_sink_states अणु
	PSR_SINK_STATE_INACTIVE = 0,
	PSR_SINK_STATE_ACTIVE_CAPTURE_DISPLAY_ON_SOURCE_TIMING = 1,
	PSR_SINK_STATE_ACTIVE_DISPLAY_FROM_SINK_RFB = 2,
	PSR_SINK_STATE_ACTIVE_CAPTURE_DISPLAY_ON_SINK_TIMING = 3,
	PSR_SINK_STATE_ACTIVE_CAPTURE_TIMING_RESYNC = 4,
	PSR_SINK_STATE_SINK_INTERNAL_ERROR = 7,
पूर्ण;

#घोषणा DP_SOURCE_TABLE_REVISION	    0x310
#घोषणा DP_SOURCE_PAYLOAD_SIZE		    0x311
#घोषणा DP_SOURCE_SINK_CAP		    0x317
#घोषणा DP_SOURCE_BACKLIGHT_LEVEL	    0x320
#घोषणा DP_SOURCE_BACKLIGHT_CURRENT_PEAK    0x326
#घोषणा DP_SOURCE_BACKLIGHT_CONTROL	    0x32E
#घोषणा DP_SOURCE_BACKLIGHT_ENABLE	    0x32F
#घोषणा DP_SOURCE_MINIMUM_HBLANK_SUPPORTED	0x340

#पूर्ण_अगर /* __DAL_DPCD_DEFS_H__ */
