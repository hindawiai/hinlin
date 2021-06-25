<शैली गुरु>
#अगर_अघोषित DC_DSC_H_
#घोषणा DC_DSC_H_
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 * Author: AMD
 */

/* put it here temporarily until linux has the new addresses official defined */
/* DP Extended DSC Capabilities */
#घोषणा DP_DSC_BRANCH_OVERALL_THROUGHPUT_0  0x0a0   /* DP 1.4a SCR */
#घोषणा DP_DSC_BRANCH_OVERALL_THROUGHPUT_1  0x0a1
#घोषणा DP_DSC_BRANCH_MAX_LINE_WIDTH        0x0a2
#समावेश "dc_types.h"

काष्ठा dc_dsc_bw_range अणु
	uपूर्णांक32_t min_kbps; /* Bandwidth अगर min_target_bpp_x16 is used */
	uपूर्णांक32_t min_target_bpp_x16;
	uपूर्णांक32_t max_kbps; /* Bandwidth अगर max_target_bpp_x16 is used */
	uपूर्णांक32_t max_target_bpp_x16;
	uपूर्णांक32_t stream_kbps; /* Uncompressed stream bandwidth */
पूर्ण;

काष्ठा display_stream_compressor अणु
	स्थिर काष्ठा dsc_funcs *funcs;
	काष्ठा dc_context *ctx;
	पूर्णांक inst;
पूर्ण;

काष्ठा dc_dsc_policy अणु
	bool use_min_slices_h;
	पूर्णांक max_slices_h; // Maximum available अगर 0
	पूर्णांक min_slice_height; // Must not be less than 8
	uपूर्णांक32_t max_target_bpp;
	uपूर्णांक32_t min_target_bpp;
	uपूर्णांक32_t preferred_bpp_x16;
	bool enable_dsc_when_not_needed;
पूर्ण;

bool dc_dsc_parse_dsc_dpcd(स्थिर काष्ठा dc *dc,
		स्थिर uपूर्णांक8_t *dpcd_dsc_basic_data,
		स्थिर uपूर्णांक8_t *dpcd_dsc_ext_data,
		काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps);

bool dc_dsc_compute_bandwidth_range(
		स्थिर काष्ठा display_stream_compressor *dsc,
		uपूर्णांक32_t dsc_min_slice_height_override,
		uपूर्णांक32_t min_bpp_x16,
		uपूर्णांक32_t max_bpp_x16,
		स्थिर काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps,
		स्थिर काष्ठा dc_crtc_timing *timing,
		काष्ठा dc_dsc_bw_range *range);

bool dc_dsc_compute_config(
		स्थिर काष्ठा display_stream_compressor *dsc,
		स्थिर काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps,
		uपूर्णांक32_t dsc_min_slice_height_override,
		uपूर्णांक32_t max_target_bpp_limit_override,
		uपूर्णांक32_t target_bandwidth_kbps,
		स्थिर काष्ठा dc_crtc_timing *timing,
		काष्ठा dc_dsc_config *dsc_cfg);

uपूर्णांक32_t dc_dsc_stream_bandwidth_in_kbps(uपूर्णांक32_t pix_clk_100hz, uपूर्णांक32_t bpp_x16);

व्योम dc_dsc_get_policy_क्रम_timing(स्थिर काष्ठा dc_crtc_timing *timing,
		uपूर्णांक32_t max_target_bpp_limit_override_x16,
		काष्ठा dc_dsc_policy *policy);

व्योम dc_dsc_policy_set_max_target_bpp_limit(uपूर्णांक32_t limit);

व्योम dc_dsc_policy_set_enable_dsc_when_not_needed(bool enable);

uपूर्णांक32_t dc_dsc_stream_bandwidth_in_kbps(uपूर्णांक32_t pix_clk_100hz, uपूर्णांक32_t bpp_x16);

#पूर्ण_अगर
