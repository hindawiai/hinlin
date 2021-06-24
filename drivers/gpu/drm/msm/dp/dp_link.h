<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DP_LINK_H_
#घोषणा _DP_LINK_H_

#समावेश "dp_aux.h"

#घोषणा DS_PORT_STATUS_CHANGED 0x200
#घोषणा DP_TEST_BIT_DEPTH_UNKNOWN 0xFFFFFFFF
#घोषणा DP_LINK_CAP_ENHANCED_FRAMING (1 << 0)

काष्ठा dp_link_info अणु
	अचिन्हित अक्षर revision;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक num_lanes;
	अचिन्हित दीर्घ capabilities;
पूर्ण;

क्रमागत dp_link_voltage_level अणु
	DP_TRAIN_VOLTAGE_SWING_LVL_0	= 0,
	DP_TRAIN_VOLTAGE_SWING_LVL_1	= 1,
	DP_TRAIN_VOLTAGE_SWING_LVL_2	= 2,
	DP_TRAIN_VOLTAGE_SWING_MAX	= DP_TRAIN_VOLTAGE_SWING_LVL_2,
पूर्ण;

क्रमागत dp_link_preemaphasis_level अणु
	DP_TRAIN_PRE_EMPHASIS_LVL_0	= 0,
	DP_TRAIN_PRE_EMPHASIS_LVL_1	= 1,
	DP_TRAIN_PRE_EMPHASIS_LVL_2	= 2,
	DP_TRAIN_PRE_EMPHASIS_MAX	= DP_TRAIN_PRE_EMPHASIS_LVL_2,
पूर्ण;

काष्ठा dp_link_test_video अणु
	u32 test_video_pattern;
	u32 test_bit_depth;
	u32 test_dyn_range;
	u32 test_h_total;
	u32 test_v_total;
	u32 test_h_start;
	u32 test_v_start;
	u32 test_hsync_pol;
	u32 test_hsync_width;
	u32 test_vsync_pol;
	u32 test_vsync_width;
	u32 test_h_width;
	u32 test_v_height;
	u32 test_rr_d;
	u32 test_rr_n;
पूर्ण;

काष्ठा dp_link_test_audio अणु
	u32 test_audio_sampling_rate;
	u32 test_audio_channel_count;
	u32 test_audio_pattern_type;
	u32 test_audio_period_ch_1;
	u32 test_audio_period_ch_2;
	u32 test_audio_period_ch_3;
	u32 test_audio_period_ch_4;
	u32 test_audio_period_ch_5;
	u32 test_audio_period_ch_6;
	u32 test_audio_period_ch_7;
	u32 test_audio_period_ch_8;
पूर्ण;

काष्ठा dp_link_phy_params अणु
	u32 phy_test_pattern_sel;
	u8 v_level;
	u8 p_level;
पूर्ण;

काष्ठा dp_link अणु
	u32 sink_request;
	u32 test_response;
	bool psm_enabled;

	u8 sink_count;
	काष्ठा dp_link_test_video test_video;
	काष्ठा dp_link_test_audio test_audio;
	काष्ठा dp_link_phy_params phy_params;
	काष्ठा dp_link_info link_params;
पूर्ण;

/**
 * mdss_dp_test_bit_depth_to_bpp() - convert test bit depth to bpp
 * @tbd: test bit depth
 *
 * Returns the bits per pixel (bpp) to be used corresponding to the
 * git bit depth value. This function assumes that bit depth has
 * alपढ़ोy been validated.
 */
अटल अंतरभूत u32 dp_link_bit_depth_to_bpp(u32 tbd)
अणु
	/*
	 * Few simplistic rules and assumptions made here:
	 *    1. Bit depth is per color component
	 *    2. If bit depth is unknown वापस 0
	 *    3. Assume 3 color components
	 */
	चयन (tbd) अणु
	हाल DP_TEST_BIT_DEPTH_6:
		वापस 18;
	हाल DP_TEST_BIT_DEPTH_8:
		वापस 24;
	हाल DP_TEST_BIT_DEPTH_10:
		वापस 30;
	हाल DP_TEST_BIT_DEPTH_UNKNOWN:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/**
 * dp_test_bit_depth_to_bpc() - convert test bit depth to bpc
 * @tbd: test bit depth
 *
 * Returns the bits per comp (bpc) to be used corresponding to the
 * bit depth value. This function assumes that bit depth has
 * alपढ़ोy been validated.
 */
अटल अंतरभूत u32 dp_link_bit_depth_to_bpc(u32 tbd)
अणु
	चयन (tbd) अणु
	हाल DP_TEST_BIT_DEPTH_6:
		वापस 6;
	हाल DP_TEST_BIT_DEPTH_8:
		वापस 8;
	हाल DP_TEST_BIT_DEPTH_10:
		वापस 10;
	हाल DP_TEST_BIT_DEPTH_UNKNOWN:
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम dp_link_reset_phy_params_vx_px(काष्ठा dp_link *dp_link);
u32 dp_link_get_test_bits_depth(काष्ठा dp_link *dp_link, u32 bpp);
पूर्णांक dp_link_process_request(काष्ठा dp_link *dp_link);
पूर्णांक dp_link_get_colorimetry_config(काष्ठा dp_link *dp_link);
पूर्णांक dp_link_adjust_levels(काष्ठा dp_link *dp_link, u8 *link_status);
bool dp_link_send_test_response(काष्ठा dp_link *dp_link);
पूर्णांक dp_link_psm_config(काष्ठा dp_link *dp_link,
		काष्ठा dp_link_info *link_info, bool enable);
bool dp_link_send_edid_checksum(काष्ठा dp_link *dp_link, u8 checksum);

/**
 * dp_link_get() - get the functionalities of dp test module
 *
 *
 * वापस: a poपूर्णांकer to dp_link काष्ठा
 */
काष्ठा dp_link *dp_link_get(काष्ठा device *dev, काष्ठा drm_dp_aux *aux);

#पूर्ण_अगर /* _DP_LINK_H_ */
