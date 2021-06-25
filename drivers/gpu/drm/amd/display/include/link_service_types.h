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

#अगर_अघोषित __DAL_LINK_SERVICE_TYPES_H__
#घोषणा __DAL_LINK_SERVICE_TYPES_H__

#समावेश "grph_object_id.h"
#समावेश "dal_types.h"
#समावेश "irq_types.h"

/*काष्ठा mst_mgr_callback_object;*/
काष्ठा ddc;
काष्ठा irq_manager;

क्रमागत अणु
	MAX_CONTROLLER_NUM = 6
पूर्ण;

क्रमागत dp_घातer_state अणु
	DP_POWER_STATE_D0 = 1,
	DP_POWER_STATE_D3
पूर्ण;

क्रमागत edp_revision अणु
	/* eDP version 1.1 or lower */
	EDP_REVISION_11 = 0x00,
	/* eDP version 1.2 */
	EDP_REVISION_12 = 0x01,
	/* eDP version 1.3 */
	EDP_REVISION_13 = 0x02
पूर्ण;

क्रमागत अणु
	LINK_RATE_REF_FREQ_IN_KHZ = 27000 /*27MHz*/
पूर्ण;

क्रमागत link_training_result अणु
	LINK_TRAINING_SUCCESS,
	LINK_TRAINING_CR_FAIL_LANE0,
	LINK_TRAINING_CR_FAIL_LANE1,
	LINK_TRAINING_CR_FAIL_LANE23,
	/* CR DONE bit is cleared during EQ step */
	LINK_TRAINING_EQ_FAIL_CR,
	/* other failure during EQ step */
	LINK_TRAINING_EQ_FAIL_EQ,
	LINK_TRAINING_LQA_FAIL,
	/* one of the CR,EQ or symbol lock is dropped */
	LINK_TRAINING_LINK_LOSS,
पूर्ण;

काष्ठा link_training_settings अणु
	काष्ठा dc_link_settings link_settings;
	काष्ठा dc_lane_settings lane_settings[LANE_COUNT_DP_MAX];

	क्रमागत dc_voltage_swing *voltage_swing;
	क्रमागत dc_pre_emphasis *pre_emphasis;
	क्रमागत dc_post_cursor2 *post_cursor2;

	uपूर्णांक16_t cr_pattern_समय;
	uपूर्णांक16_t eq_pattern_समय;
	क्रमागत dc_dp_training_pattern pattern_क्रम_cr;
	क्रमागत dc_dp_training_pattern pattern_क्रम_eq;

	bool enhanced_framing;
	bool allow_invalid_msa_timing_param;
पूर्ण;

/*TODO: Move this क्रमागत test harness*/
/* Test patterns*/
क्रमागत dp_test_pattern अणु
	/* Input data is pass through Scrambler
	 * and 8b10b Encoder straight to output*/
	DP_TEST_PATTERN_VIDEO_MODE = 0,

	/* phy test patterns*/
	DP_TEST_PATTERN_PHY_PATTERN_BEGIN,
	DP_TEST_PATTERN_D102 = DP_TEST_PATTERN_PHY_PATTERN_BEGIN,
	DP_TEST_PATTERN_SYMBOL_ERROR,
	DP_TEST_PATTERN_PRBS7,
	DP_TEST_PATTERN_80BIT_CUSTOM,
	DP_TEST_PATTERN_CP2520_1,
	DP_TEST_PATTERN_CP2520_2,
	DP_TEST_PATTERN_HBR2_COMPLIANCE_EYE = DP_TEST_PATTERN_CP2520_2,
	DP_TEST_PATTERN_CP2520_3,

	/* Link Training Patterns */
	DP_TEST_PATTERN_TRAINING_PATTERN1,
	DP_TEST_PATTERN_TRAINING_PATTERN2,
	DP_TEST_PATTERN_TRAINING_PATTERN3,
	DP_TEST_PATTERN_TRAINING_PATTERN4,
	DP_TEST_PATTERN_PHY_PATTERN_END = DP_TEST_PATTERN_TRAINING_PATTERN4,

	/* link test patterns*/
	DP_TEST_PATTERN_COLOR_SQUARES,
	DP_TEST_PATTERN_COLOR_SQUARES_CEA,
	DP_TEST_PATTERN_VERTICAL_BARS,
	DP_TEST_PATTERN_HORIZONTAL_BARS,
	DP_TEST_PATTERN_COLOR_RAMP,

	/* audio test patterns*/
	DP_TEST_PATTERN_AUDIO_OPERATOR_DEFINED,
	DP_TEST_PATTERN_AUDIO_SAWTOOTH,

	DP_TEST_PATTERN_UNSUPPORTED
पूर्ण;

क्रमागत dp_test_pattern_color_space अणु
	DP_TEST_PATTERN_COLOR_SPACE_RGB,
	DP_TEST_PATTERN_COLOR_SPACE_YCBCR601,
	DP_TEST_PATTERN_COLOR_SPACE_YCBCR709,
	DP_TEST_PATTERN_COLOR_SPACE_UNDEFINED
पूर्ण;

क्रमागत dp_panel_mode अणु
	/* not required */
	DP_PANEL_MODE_DEFAULT,
	/* standard mode क्रम eDP */
	DP_PANEL_MODE_EDP,
	/* बाह्यal chips specअगरic settings */
	DP_PANEL_MODE_SPECIAL
पूर्ण;

/* DPCD_ADDR_TRAINING_LANEx_SET रेजिस्टरs value */
जोड़ dpcd_training_lane_set अणु
	काष्ठा अणु
#अगर defined(LITTLEENDIAN_CPU)
		uपूर्णांक8_t VOLTAGE_SWING_SET:2;
		uपूर्णांक8_t MAX_SWING_REACHED:1;
		uपूर्णांक8_t PRE_EMPHASIS_SET:2;
		uपूर्णांक8_t MAX_PRE_EMPHASIS_REACHED:1;
		/* following is reserved in DP 1.1 */
		uपूर्णांक8_t POST_CURSOR2_SET:2;
#या_अगर defined(BIGENDIAN_CPU)
		uपूर्णांक8_t POST_CURSOR2_SET:2;
		uपूर्णांक8_t MAX_PRE_EMPHASIS_REACHED:1;
		uपूर्णांक8_t PRE_EMPHASIS_SET:2;
		uपूर्णांक8_t MAX_SWING_REACHED:1;
		uपूर्णांक8_t VOLTAGE_SWING_SET:2;
#अन्यथा
	#त्रुटि ARCH not defined!
#पूर्ण_अगर
	पूर्ण bits;

	uपूर्णांक8_t raw;
पूर्ण;


/* DP MST stream allocation (payload bandwidth number) */
काष्ठा dp_mst_stream_allocation अणु
	uपूर्णांक8_t vcp_id;
	/* number of slots required क्रम the DP stream in
	 * transport packet */
	uपूर्णांक8_t slot_count;
पूर्ण;

/* DP MST stream allocation table */
काष्ठा dp_mst_stream_allocation_table अणु
	/* number of DP video streams */
	पूर्णांक stream_count;
	/* array of stream allocations */
	काष्ठा dp_mst_stream_allocation stream_allocations[MAX_CONTROLLER_NUM];
पूर्ण;

#पूर्ण_अगर /*__DAL_LINK_SERVICE_TYPES_H__*/
