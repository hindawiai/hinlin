<शैली गुरु>
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

#समावेश <drm/drm_dsc.h>
#समावेश "dc_hw_types.h"
#समावेश "dsc.h"
#समावेश <drm/drm_dp_helper.h>
#समावेश "dc.h"
#समावेश "rc_calc.h"

/* This module's पूर्णांकernal functions */

/* शेष DSC policy target bitrate limit is 16bpp */
अटल uपूर्णांक32_t dsc_policy_max_target_bpp_limit = 16;

/* शेष DSC policy enables DSC only when needed */
अटल bool dsc_policy_enable_dsc_when_not_needed;

अटल bool dsc_buff_block_size_from_dpcd(पूर्णांक dpcd_buff_block_size, पूर्णांक *buff_block_size)
अणु

	चयन (dpcd_buff_block_size) अणु
	हाल DP_DSC_RC_BUF_BLK_SIZE_1:
		*buff_block_size = 1024;
		अवरोध;
	हाल DP_DSC_RC_BUF_BLK_SIZE_4:
		*buff_block_size = 4 * 1024;
		अवरोध;
	हाल DP_DSC_RC_BUF_BLK_SIZE_16:
		*buff_block_size = 16 * 1024;
		अवरोध;
	हाल DP_DSC_RC_BUF_BLK_SIZE_64:
		*buff_block_size = 64 * 1024;
		अवरोध;
	शेष: अणु
			dm_error("%s: DPCD DSC buffer size not recognized.\n", __func__);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण


अटल bool dsc_line_buff_depth_from_dpcd(पूर्णांक dpcd_line_buff_bit_depth, पूर्णांक *line_buff_bit_depth)
अणु
	अगर (0 <= dpcd_line_buff_bit_depth && dpcd_line_buff_bit_depth <= 7)
		*line_buff_bit_depth = dpcd_line_buff_bit_depth + 9;
	अन्यथा अगर (dpcd_line_buff_bit_depth == 8)
		*line_buff_bit_depth = 8;
	अन्यथा अणु
		dm_error("%s: DPCD DSC buffer depth not recognized.\n", __func__);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण


अटल bool dsc_throughput_from_dpcd(पूर्णांक dpcd_throughput, पूर्णांक *throughput)
अणु
	चयन (dpcd_throughput) अणु
	हाल DP_DSC_THROUGHPUT_MODE_0_UNSUPPORTED:
		*throughput = 0;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_170:
		*throughput = 170;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_340:
		*throughput = 340;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_400:
		*throughput = 400;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_450:
		*throughput = 450;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_500:
		*throughput = 500;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_550:
		*throughput = 550;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_600:
		*throughput = 600;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_650:
		*throughput = 650;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_700:
		*throughput = 700;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_750:
		*throughput = 750;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_800:
		*throughput = 800;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_850:
		*throughput = 850;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_900:
		*throughput = 900;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_950:
		*throughput = 950;
		अवरोध;
	हाल DP_DSC_THROUGHPUT_MODE_0_1000:
		*throughput = 1000;
		अवरोध;
	शेष: अणु
			dm_error("%s: DPCD DSC throughput mode not recognized.\n", __func__);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण


अटल bool dsc_bpp_increment_भाग_from_dpcd(uपूर्णांक8_t bpp_increment_dpcd, uपूर्णांक32_t *bpp_increment_भाग)
अणु
	// Mask bpp increment dpcd field to aव्योम पढ़ोing other fields
	bpp_increment_dpcd &= 0x7;

	चयन (bpp_increment_dpcd) अणु
	हाल 0:
		*bpp_increment_भाग = 16;
		अवरोध;
	हाल 1:
		*bpp_increment_भाग = 8;
		अवरोध;
	हाल 2:
		*bpp_increment_भाग = 4;
		अवरोध;
	हाल 3:
		*bpp_increment_भाग = 2;
		अवरोध;
	हाल 4:
		*bpp_increment_भाग = 1;
		अवरोध;
	शेष: अणु
		dm_error("%s: DPCD DSC bits-per-pixel increment not recognized.\n", __func__);
		वापस false;
	पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम get_dsc_enc_caps(
	स्थिर काष्ठा display_stream_compressor *dsc,
	काष्ठा dsc_enc_caps *dsc_enc_caps,
	पूर्णांक pixel_घड़ी_100Hz)
अणु
	// This is a अटल HW query, so we can use any DSC

	स_रखो(dsc_enc_caps, 0, माप(काष्ठा dsc_enc_caps));
	अगर (dsc) अणु
		अगर (!dsc->ctx->dc->debug.disable_dsc)
			dsc->funcs->dsc_get_enc_caps(dsc_enc_caps, pixel_घड़ी_100Hz);
		अगर (dsc->ctx->dc->debug.native422_support)
			dsc_enc_caps->color_क्रमmats.bits.YCBCR_NATIVE_422 = 1;
	पूर्ण
पूर्ण

/* Returns 'false' अगर no पूर्णांकersection was found क्रम at least one capablity.
 * It also implicitly validates some sink caps against invalid value of zero.
 */
अटल bool पूर्णांकersect_dsc_caps(
	स्थिर काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps,
	स्थिर काष्ठा dsc_enc_caps *dsc_enc_caps,
	क्रमागत dc_pixel_encoding pixel_encoding,
	काष्ठा dsc_enc_caps *dsc_common_caps)
अणु
	पूर्णांक32_t max_slices;
	पूर्णांक32_t total_sink_throughput;

	स_रखो(dsc_common_caps, 0, माप(काष्ठा dsc_enc_caps));

	dsc_common_caps->dsc_version = min(dsc_sink_caps->dsc_version, dsc_enc_caps->dsc_version);
	अगर (!dsc_common_caps->dsc_version)
		वापस false;

	dsc_common_caps->slice_caps.bits.NUM_SLICES_1 = dsc_sink_caps->slice_caps1.bits.NUM_SLICES_1 && dsc_enc_caps->slice_caps.bits.NUM_SLICES_1;
	dsc_common_caps->slice_caps.bits.NUM_SLICES_2 = dsc_sink_caps->slice_caps1.bits.NUM_SLICES_2 && dsc_enc_caps->slice_caps.bits.NUM_SLICES_2;
	dsc_common_caps->slice_caps.bits.NUM_SLICES_4 = dsc_sink_caps->slice_caps1.bits.NUM_SLICES_4 && dsc_enc_caps->slice_caps.bits.NUM_SLICES_4;
	dsc_common_caps->slice_caps.bits.NUM_SLICES_8 = dsc_sink_caps->slice_caps1.bits.NUM_SLICES_8 && dsc_enc_caps->slice_caps.bits.NUM_SLICES_8;
	अगर (!dsc_common_caps->slice_caps.raw)
		वापस false;

	dsc_common_caps->lb_bit_depth = min(dsc_sink_caps->lb_bit_depth, dsc_enc_caps->lb_bit_depth);
	अगर (!dsc_common_caps->lb_bit_depth)
		वापस false;

	dsc_common_caps->is_block_pred_supported = dsc_sink_caps->is_block_pred_supported && dsc_enc_caps->is_block_pred_supported;

	dsc_common_caps->color_क्रमmats.raw = dsc_sink_caps->color_क्रमmats.raw & dsc_enc_caps->color_क्रमmats.raw;
	अगर (!dsc_common_caps->color_क्रमmats.raw)
		वापस false;

	dsc_common_caps->color_depth.raw = dsc_sink_caps->color_depth.raw & dsc_enc_caps->color_depth.raw;
	अगर (!dsc_common_caps->color_depth.raw)
		वापस false;

	max_slices = 0;
	अगर (dsc_common_caps->slice_caps.bits.NUM_SLICES_1)
		max_slices = 1;

	अगर (dsc_common_caps->slice_caps.bits.NUM_SLICES_2)
		max_slices = 2;

	अगर (dsc_common_caps->slice_caps.bits.NUM_SLICES_4)
		max_slices = 4;

	total_sink_throughput = max_slices * dsc_sink_caps->throughput_mode_0_mps;
	अगर (pixel_encoding == PIXEL_ENCODING_YCBCR422 || pixel_encoding == PIXEL_ENCODING_YCBCR420)
		total_sink_throughput = max_slices * dsc_sink_caps->throughput_mode_1_mps;

	dsc_common_caps->max_total_throughput_mps = min(total_sink_throughput, dsc_enc_caps->max_total_throughput_mps);

	dsc_common_caps->max_slice_width = min(dsc_sink_caps->max_slice_width, dsc_enc_caps->max_slice_width);
	अगर (!dsc_common_caps->max_slice_width)
		वापस false;

	dsc_common_caps->bpp_increment_भाग = min(dsc_sink_caps->bpp_increment_भाग, dsc_enc_caps->bpp_increment_भाग);

	// TODO DSC: Remove this workaround क्रम N422 and 420 once it's fixed, or move it to get_dsc_encoder_caps()
	अगर (pixel_encoding == PIXEL_ENCODING_YCBCR422 || pixel_encoding == PIXEL_ENCODING_YCBCR420)
		dsc_common_caps->bpp_increment_भाग = min(dsc_common_caps->bpp_increment_भाग, (uपूर्णांक32_t)8);

	वापस true;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t dsc_भाग_by_10_round_up(uपूर्णांक32_t value)
अणु
	वापस (value + 9) / 10;
पूर्ण

/* Get DSC bandwidth range based on [min_bpp, max_bpp] target bitrate range, and timing's pixel घड़ी
 * and uncompressed bandwidth.
 */
अटल व्योम get_dsc_bandwidth_range(
		स्थिर uपूर्णांक32_t min_bpp_x16,
		स्थिर uपूर्णांक32_t max_bpp_x16,
		स्थिर काष्ठा dsc_enc_caps *dsc_caps,
		स्थिर काष्ठा dc_crtc_timing *timing,
		काष्ठा dc_dsc_bw_range *range)
अणु
	/* native stream bandwidth */
	range->stream_kbps = dc_bandwidth_in_kbps_from_timing(timing);

	/* max dsc target bpp */
	range->max_kbps = dc_dsc_stream_bandwidth_in_kbps(timing->pix_clk_100hz, max_bpp_x16);
	range->max_target_bpp_x16 = max_bpp_x16;
	अगर (range->max_kbps > range->stream_kbps) अणु
		/* max dsc target bpp is capped to native bandwidth */
		range->max_kbps = range->stream_kbps;
		range->max_target_bpp_x16 = calc_dsc_bpp_x16(range->stream_kbps, timing->pix_clk_100hz, dsc_caps->bpp_increment_भाग);
	पूर्ण

	/* min dsc target bpp */
	range->min_kbps = dc_dsc_stream_bandwidth_in_kbps(timing->pix_clk_100hz, min_bpp_x16);
	range->min_target_bpp_x16 = min_bpp_x16;
	अगर (range->min_kbps > range->max_kbps) अणु
		/* min dsc target bpp is capped to max dsc bandwidth*/
		range->min_kbps = range->max_kbps;
		range->min_target_bpp_x16 = range->max_target_bpp_x16;
	पूर्ण
पूर्ण


/* Decides अगर DSC should be used and calculates target bpp अगर it should, applying DSC policy.
 *
 * Returns:
 *     - 'true' अगर DSC was required by policy and was successfully applied
 *     - 'false' if DSC was not necessary (e.g. if uncompressed stream fits 'target_bandwidth_kbps'),
 *        or अगर it couldn't be applied based on DSC policy.
 */
अटल bool decide_dsc_target_bpp_x16(
		स्थिर काष्ठा dc_dsc_policy *policy,
		स्थिर काष्ठा dsc_enc_caps *dsc_common_caps,
		स्थिर पूर्णांक target_bandwidth_kbps,
		स्थिर काष्ठा dc_crtc_timing *timing,
		पूर्णांक *target_bpp_x16)
अणु
	bool should_use_dsc = false;
	काष्ठा dc_dsc_bw_range range;

	स_रखो(&range, 0, माप(range));

	get_dsc_bandwidth_range(policy->min_target_bpp * 16, policy->max_target_bpp * 16,
			dsc_common_caps, timing, &range);
	अगर (!policy->enable_dsc_when_not_needed && target_bandwidth_kbps >= range.stream_kbps) अणु
		/* enough bandwidth without dsc */
		*target_bpp_x16 = 0;
		should_use_dsc = false;
	पूर्ण अन्यथा अगर (policy->preferred_bpp_x16 > 0 &&
			policy->preferred_bpp_x16 <= range.max_target_bpp_x16 &&
			policy->preferred_bpp_x16 >= range.min_target_bpp_x16) अणु
		*target_bpp_x16 = policy->preferred_bpp_x16;
		should_use_dsc = true;
	पूर्ण अन्यथा अगर (target_bandwidth_kbps >= range.max_kbps) अणु
		/* use max target bpp allowed */
		*target_bpp_x16 = range.max_target_bpp_x16;
		should_use_dsc = true;
	पूर्ण अन्यथा अगर (target_bandwidth_kbps >= range.min_kbps) अणु
		/* use target bpp that can take entire target bandwidth */
		*target_bpp_x16 = calc_dsc_bpp_x16(target_bandwidth_kbps, timing->pix_clk_100hz, dsc_common_caps->bpp_increment_भाग);
		should_use_dsc = true;
	पूर्ण अन्यथा अणु
		/* not enough bandwidth to fulfill minimum requirement */
		*target_bpp_x16 = 0;
		should_use_dsc = false;
	पूर्ण

	वापस should_use_dsc;
पूर्ण

#घोषणा MIN_AVAILABLE_SLICES_SIZE  4

अटल पूर्णांक get_available_dsc_slices(जोड़ dsc_enc_slice_caps slice_caps, पूर्णांक *available_slices)
अणु
	पूर्णांक idx = 0;

	स_रखो(available_slices, -1, MIN_AVAILABLE_SLICES_SIZE);

	अगर (slice_caps.bits.NUM_SLICES_1)
		available_slices[idx++] = 1;

	अगर (slice_caps.bits.NUM_SLICES_2)
		available_slices[idx++] = 2;

	अगर (slice_caps.bits.NUM_SLICES_4)
		available_slices[idx++] = 4;

	अगर (slice_caps.bits.NUM_SLICES_8)
		available_slices[idx++] = 8;

	वापस idx;
पूर्ण


अटल पूर्णांक get_max_dsc_slices(जोड़ dsc_enc_slice_caps slice_caps)
अणु
	पूर्णांक max_slices = 0;
	पूर्णांक available_slices[MIN_AVAILABLE_SLICES_SIZE];
	पूर्णांक end_idx = get_available_dsc_slices(slice_caps, &available_slices[0]);

	अगर (end_idx > 0)
		max_slices = available_slices[end_idx - 1];

	वापस max_slices;
पूर्ण


// Increment sice number in available sice numbers stops अगर possible, or just increment अगर not
अटल पूर्णांक inc_num_slices(जोड़ dsc_enc_slice_caps slice_caps, पूर्णांक num_slices)
अणु
	// Get next bigger num slices available in common caps
	पूर्णांक available_slices[MIN_AVAILABLE_SLICES_SIZE];
	पूर्णांक end_idx;
	पूर्णांक i;
	पूर्णांक new_num_slices = num_slices;

	end_idx = get_available_dsc_slices(slice_caps, &available_slices[0]);
	अगर (end_idx == 0) अणु
		// No available slices found
		new_num_slices++;
		वापस new_num_slices;
	पूर्ण

	// Numbers of slices found - get the next bigger number
	क्रम (i = 0; i < end_idx; i++) अणु
		अगर (new_num_slices < available_slices[i]) अणु
			new_num_slices = available_slices[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (new_num_slices == num_slices) // No biger number of slices found
		new_num_slices++;

	वापस new_num_slices;
पूर्ण


// Decrement sice number in available sice numbers stops अगर possible, or just decrement अगर not. Stop at zero.
अटल पूर्णांक dec_num_slices(जोड़ dsc_enc_slice_caps slice_caps, पूर्णांक num_slices)
अणु
	// Get next bigger num slices available in common caps
	पूर्णांक available_slices[MIN_AVAILABLE_SLICES_SIZE];
	पूर्णांक end_idx;
	पूर्णांक i;
	पूर्णांक new_num_slices = num_slices;

	end_idx = get_available_dsc_slices(slice_caps, &available_slices[0]);
	अगर (end_idx == 0 && new_num_slices > 0) अणु
		// No numbers of slices found
		new_num_slices++;
		वापस new_num_slices;
	पूर्ण

	// Numbers of slices found - get the next smaller number
	क्रम (i = end_idx - 1; i >= 0; i--) अणु
		अगर (new_num_slices > available_slices[i]) अणु
			new_num_slices = available_slices[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (new_num_slices == num_slices) अणु
		// No smaller number of slices found
		new_num_slices--;
		अगर (new_num_slices < 0)
			new_num_slices = 0;
	पूर्ण

	वापस new_num_slices;
पूर्ण


// Choose next bigger number of slices अगर the requested number of slices is not available
अटल पूर्णांक fit_num_slices_up(जोड़ dsc_enc_slice_caps slice_caps, पूर्णांक num_slices)
अणु
	// Get next bigger num slices available in common caps
	पूर्णांक available_slices[MIN_AVAILABLE_SLICES_SIZE];
	पूर्णांक end_idx;
	पूर्णांक i;
	पूर्णांक new_num_slices = num_slices;

	end_idx = get_available_dsc_slices(slice_caps, &available_slices[0]);
	अगर (end_idx == 0) अणु
		// No available slices found
		new_num_slices++;
		वापस new_num_slices;
	पूर्ण

	// Numbers of slices found - get the equal or next bigger number
	क्रम (i = 0; i < end_idx; i++) अणु
		अगर (new_num_slices <= available_slices[i]) अणु
			new_num_slices = available_slices[i];
			अवरोध;
		पूर्ण
	पूर्ण

	वापस new_num_slices;
पूर्ण


/* Attempts to set DSC configuration क्रम the stream, applying DSC policy.
 * Returns 'true' if successful or 'false' अगर not.
 *
 * Parameters:
 *
 * dsc_sink_caps       - DSC sink decoder capabilities (from DPCD)
 *
 * dsc_enc_caps        - DSC encoder capabilities
 *
 * target_bandwidth_kbps  - Target bandwidth to fit the stream पूर्णांकo.
 *                          If 0, करो not calculate target bpp.
 *
 * timing              - The stream timing to fit पूर्णांकo 'target_bandwidth_kbps' or apply
 *                       maximum compression to, अगर 'target_badwidth == 0'
 *
 * dsc_cfg             - DSC configuration to use अगर it was possible to come up with
 *                       one क्रम the given inमाला_दो.
 *                       The target bitrate after DSC can be calculated by multiplying
 *                       dsc_cfg.bits_per_pixel (in U6.4 क्रमmat) by pixel rate, e.g.
 *
 *                       dsc_stream_bitrate_kbps = (पूर्णांक)उच्चमान(timing->pix_clk_khz * dsc_cfg.bits_per_pixel / 16.0);
 */
अटल bool setup_dsc_config(
		स्थिर काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps,
		स्थिर काष्ठा dsc_enc_caps *dsc_enc_caps,
		पूर्णांक target_bandwidth_kbps,
		स्थिर काष्ठा dc_crtc_timing *timing,
		पूर्णांक min_slice_height_override,
		पूर्णांक max_dsc_target_bpp_limit_override_x16,
		काष्ठा dc_dsc_config *dsc_cfg)
अणु
	काष्ठा dsc_enc_caps dsc_common_caps;
	पूर्णांक max_slices_h;
	पूर्णांक min_slices_h;
	पूर्णांक num_slices_h;
	पूर्णांक pic_width;
	पूर्णांक slice_width;
	पूर्णांक target_bpp;
	पूर्णांक sink_per_slice_throughput_mps;
	पूर्णांक branch_max_throughput_mps = 0;
	bool is_dsc_possible = false;
	पूर्णांक pic_height;
	पूर्णांक slice_height;
	काष्ठा dc_dsc_policy policy;

	स_रखो(dsc_cfg, 0, माप(काष्ठा dc_dsc_config));

	dc_dsc_get_policy_क्रम_timing(timing, max_dsc_target_bpp_limit_override_x16, &policy);
	pic_width = timing->h_addressable + timing->h_border_left + timing->h_border_right;
	pic_height = timing->v_addressable + timing->v_border_top + timing->v_border_bottom;

	अगर (!dsc_sink_caps->is_dsc_supported)
		जाओ करोne;

	अगर (dsc_sink_caps->branch_max_line_width && dsc_sink_caps->branch_max_line_width < pic_width)
		जाओ करोne;

	// Intersect decoder with encoder DSC caps and validate DSC settings
	is_dsc_possible = पूर्णांकersect_dsc_caps(dsc_sink_caps, dsc_enc_caps, timing->pixel_encoding, &dsc_common_caps);
	अगर (!is_dsc_possible)
		जाओ करोne;

	अगर (target_bandwidth_kbps > 0) अणु
		is_dsc_possible = decide_dsc_target_bpp_x16(
				&policy,
				&dsc_common_caps,
				target_bandwidth_kbps,
				timing,
				&target_bpp);
		dsc_cfg->bits_per_pixel = target_bpp;
	पूर्ण
	अगर (!is_dsc_possible)
		जाओ करोne;

	sink_per_slice_throughput_mps = 0;

	// Validate available DSC settings against the mode timing

	// Validate color क्रमmat (and pick up the throughput values)
	dsc_cfg->ycbcr422_simple = false;
	चयन (timing->pixel_encoding)	अणु
	हाल PIXEL_ENCODING_RGB:
		is_dsc_possible = (bool)dsc_common_caps.color_क्रमmats.bits.RGB;
		sink_per_slice_throughput_mps = dsc_sink_caps->throughput_mode_0_mps;
		branch_max_throughput_mps = dsc_sink_caps->branch_overall_throughput_0_mps;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR444:
		is_dsc_possible = (bool)dsc_common_caps.color_क्रमmats.bits.YCBCR_444;
		sink_per_slice_throughput_mps = dsc_sink_caps->throughput_mode_0_mps;
		branch_max_throughput_mps = dsc_sink_caps->branch_overall_throughput_0_mps;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR422:
		is_dsc_possible = (bool)dsc_common_caps.color_क्रमmats.bits.YCBCR_NATIVE_422;
		sink_per_slice_throughput_mps = dsc_sink_caps->throughput_mode_1_mps;
		branch_max_throughput_mps = dsc_sink_caps->branch_overall_throughput_1_mps;
		अगर (!is_dsc_possible) अणु
			is_dsc_possible = (bool)dsc_common_caps.color_क्रमmats.bits.YCBCR_SIMPLE_422;
			dsc_cfg->ycbcr422_simple = is_dsc_possible;
			sink_per_slice_throughput_mps = dsc_sink_caps->throughput_mode_0_mps;
		पूर्ण
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR420:
		is_dsc_possible = (bool)dsc_common_caps.color_क्रमmats.bits.YCBCR_NATIVE_420;
		sink_per_slice_throughput_mps = dsc_sink_caps->throughput_mode_1_mps;
		branch_max_throughput_mps = dsc_sink_caps->branch_overall_throughput_1_mps;
		अवरोध;
	शेष:
		is_dsc_possible = false;
	पूर्ण

	// Validate branch's maximum throughput
	अगर (branch_max_throughput_mps && dsc_भाग_by_10_round_up(timing->pix_clk_100hz) > branch_max_throughput_mps * 1000)
		is_dsc_possible = false;

	अगर (!is_dsc_possible)
		जाओ करोne;

	// Color depth
	चयन (timing->display_color_depth) अणु
	हाल COLOR_DEPTH_888:
		is_dsc_possible = (bool)dsc_common_caps.color_depth.bits.COLOR_DEPTH_8_BPC;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		is_dsc_possible = (bool)dsc_common_caps.color_depth.bits.COLOR_DEPTH_10_BPC;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		is_dsc_possible = (bool)dsc_common_caps.color_depth.bits.COLOR_DEPTH_12_BPC;
		अवरोध;
	शेष:
		is_dsc_possible = false;
	पूर्ण

	अगर (!is_dsc_possible)
		जाओ करोne;

	// Slice width (i.e. number of slices per line)
	max_slices_h = get_max_dsc_slices(dsc_common_caps.slice_caps);

	जबतक (max_slices_h > 0) अणु
		अगर (pic_width % max_slices_h == 0)
			अवरोध;

		max_slices_h = dec_num_slices(dsc_common_caps.slice_caps, max_slices_h);
	पूर्ण

	is_dsc_possible = (dsc_common_caps.max_slice_width > 0);
	अगर (!is_dsc_possible)
		जाओ करोne;

	min_slices_h = pic_width / dsc_common_caps.max_slice_width;
	अगर (pic_width % dsc_common_caps.max_slice_width)
		min_slices_h++;

	min_slices_h = fit_num_slices_up(dsc_common_caps.slice_caps, min_slices_h);

	जबतक (min_slices_h <= max_slices_h) अणु
		पूर्णांक pix_clk_per_slice_khz = dsc_भाग_by_10_round_up(timing->pix_clk_100hz) / min_slices_h;
		अगर (pix_clk_per_slice_khz <= sink_per_slice_throughput_mps * 1000)
			अवरोध;

		min_slices_h = inc_num_slices(dsc_common_caps.slice_caps, min_slices_h);
	पूर्ण

	अगर (pic_width % min_slices_h != 0)
		min_slices_h = 0; // DSC TODO: Maybe try increasing the number of slices first?

	is_dsc_possible = (min_slices_h <= max_slices_h);
	अगर (!is_dsc_possible)
		जाओ करोne;

	अगर (policy.use_min_slices_h) अणु
		अगर (min_slices_h > 0)
			num_slices_h = min_slices_h;
		अन्यथा अगर (max_slices_h > 0) अणु // Fall back to max slices अगर min slices is not working out
			अगर (policy.max_slices_h)
				num_slices_h = min(policy.max_slices_h, max_slices_h);
			अन्यथा
				num_slices_h = max_slices_h;
		पूर्ण अन्यथा
			is_dsc_possible = false;
	पूर्ण अन्यथा अणु
		अगर (max_slices_h > 0) अणु
			अगर (policy.max_slices_h)
				num_slices_h = min(policy.max_slices_h, max_slices_h);
			अन्यथा
				num_slices_h = max_slices_h;
		पूर्ण अन्यथा अगर (min_slices_h > 0) // Fall back to min slices अगर max slices is not possible
			num_slices_h = min_slices_h;
		अन्यथा
			is_dsc_possible = false;
	पूर्ण

	अगर (!is_dsc_possible)
		जाओ करोne;

	dsc_cfg->num_slices_h = num_slices_h;
	slice_width = pic_width / num_slices_h;

	is_dsc_possible = slice_width <= dsc_common_caps.max_slice_width;
	अगर (!is_dsc_possible)
		जाओ करोne;

	// Slice height (i.e. number of slices per column): start with policy and pick the first one that height is भागisible by.
	// For 4:2:0 make sure the slice height is भागisible by 2 as well.
	अगर (min_slice_height_override == 0)
		slice_height = min(policy.min_slice_height, pic_height);
	अन्यथा
		slice_height = min(min_slice_height_override, pic_height);

	जबतक (slice_height < pic_height && (pic_height % slice_height != 0 ||
		(timing->pixel_encoding == PIXEL_ENCODING_YCBCR420 && slice_height % 2 != 0)))
		slice_height++;

	अगर (timing->pixel_encoding == PIXEL_ENCODING_YCBCR420) // For the हाल when pic_height < dsc_policy.min_sice_height
		is_dsc_possible = (slice_height % 2 == 0);

	अगर (!is_dsc_possible)
		जाओ करोne;

	dsc_cfg->num_slices_v = pic_height/slice_height;

	// Final decission: can we करो DSC or not?
	अगर (is_dsc_possible) अणु
		// Fill out the rest of DSC settings
		dsc_cfg->block_pred_enable = dsc_common_caps.is_block_pred_supported;
		dsc_cfg->linebuf_depth = dsc_common_caps.lb_bit_depth;
		dsc_cfg->version_minor = (dsc_common_caps.dsc_version & 0xf0) >> 4;
	पूर्ण

करोne:
	अगर (!is_dsc_possible)
		स_रखो(dsc_cfg, 0, माप(काष्ठा dc_dsc_config));

	वापस is_dsc_possible;
पूर्ण

bool dc_dsc_parse_dsc_dpcd(स्थिर काष्ठा dc *dc, स्थिर uपूर्णांक8_t *dpcd_dsc_basic_data, स्थिर uपूर्णांक8_t *dpcd_dsc_branch_decoder_caps, काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps)
अणु
	अगर (!dpcd_dsc_basic_data)
		वापस false;

	dsc_sink_caps->is_dsc_supported = (dpcd_dsc_basic_data[DP_DSC_SUPPORT - DP_DSC_SUPPORT] & DP_DSC_DECOMPRESSION_IS_SUPPORTED) != 0;
	अगर (!dsc_sink_caps->is_dsc_supported)
		वापस false;

	dsc_sink_caps->dsc_version = dpcd_dsc_basic_data[DP_DSC_REV - DP_DSC_SUPPORT];

	अणु
		पूर्णांक buff_block_size;
		पूर्णांक buff_size;

		अगर (!dsc_buff_block_size_from_dpcd(dpcd_dsc_basic_data[DP_DSC_RC_BUF_BLK_SIZE - DP_DSC_SUPPORT], &buff_block_size))
			वापस false;

		buff_size = dpcd_dsc_basic_data[DP_DSC_RC_BUF_SIZE - DP_DSC_SUPPORT] + 1;
		dsc_sink_caps->rc_buffer_size = buff_size * buff_block_size;
	पूर्ण

	dsc_sink_caps->slice_caps1.raw = dpcd_dsc_basic_data[DP_DSC_SLICE_CAP_1 - DP_DSC_SUPPORT];
	अगर (!dsc_line_buff_depth_from_dpcd(dpcd_dsc_basic_data[DP_DSC_LINE_BUF_BIT_DEPTH - DP_DSC_SUPPORT], &dsc_sink_caps->lb_bit_depth))
		वापस false;

	dsc_sink_caps->is_block_pred_supported =
		(dpcd_dsc_basic_data[DP_DSC_BLK_PREDICTION_SUPPORT - DP_DSC_SUPPORT] & DP_DSC_BLK_PREDICTION_IS_SUPPORTED) != 0;

	dsc_sink_caps->edp_max_bits_per_pixel =
		dpcd_dsc_basic_data[DP_DSC_MAX_BITS_PER_PIXEL_LOW - DP_DSC_SUPPORT] |
		dpcd_dsc_basic_data[DP_DSC_MAX_BITS_PER_PIXEL_HI - DP_DSC_SUPPORT] << 8;

	dsc_sink_caps->color_क्रमmats.raw = dpcd_dsc_basic_data[DP_DSC_DEC_COLOR_FORMAT_CAP - DP_DSC_SUPPORT];
	dsc_sink_caps->color_depth.raw = dpcd_dsc_basic_data[DP_DSC_DEC_COLOR_DEPTH_CAP - DP_DSC_SUPPORT];

	अणु
		पूर्णांक dpcd_throughput = dpcd_dsc_basic_data[DP_DSC_PEAK_THROUGHPUT - DP_DSC_SUPPORT];

		अगर (!dsc_throughput_from_dpcd(dpcd_throughput & DP_DSC_THROUGHPUT_MODE_0_MASK, &dsc_sink_caps->throughput_mode_0_mps))
			वापस false;

		dpcd_throughput = (dpcd_throughput & DP_DSC_THROUGHPUT_MODE_1_MASK) >> DP_DSC_THROUGHPUT_MODE_1_SHIFT;
		अगर (!dsc_throughput_from_dpcd(dpcd_throughput, &dsc_sink_caps->throughput_mode_1_mps))
			वापस false;
	पूर्ण

	dsc_sink_caps->max_slice_width = dpcd_dsc_basic_data[DP_DSC_MAX_SLICE_WIDTH - DP_DSC_SUPPORT] * 320;
	dsc_sink_caps->slice_caps2.raw = dpcd_dsc_basic_data[DP_DSC_SLICE_CAP_2 - DP_DSC_SUPPORT];

	अगर (!dsc_bpp_increment_भाग_from_dpcd(dpcd_dsc_basic_data[DP_DSC_BITS_PER_PIXEL_INC - DP_DSC_SUPPORT], &dsc_sink_caps->bpp_increment_भाग))
		वापस false;

	अगर (dc->debug.dsc_bpp_increment_भाग) अणु
		/* dsc_bpp_increment_भाग should onl be 1, 2, 4, 8 or 16, but rather than rejecting invalid values,
		 * we'll accept all and get it पूर्णांकo range. This also makes the above check against 0 redundant,
		 * but that one stresses out the override will be only used अगर it's not 0.
		 */
		अगर (dc->debug.dsc_bpp_increment_भाग >= 1)
			dsc_sink_caps->bpp_increment_भाग = 1;
		अगर (dc->debug.dsc_bpp_increment_भाग >= 2)
			dsc_sink_caps->bpp_increment_भाग = 2;
		अगर (dc->debug.dsc_bpp_increment_भाग >= 4)
			dsc_sink_caps->bpp_increment_भाग = 4;
		अगर (dc->debug.dsc_bpp_increment_भाग >= 8)
			dsc_sink_caps->bpp_increment_भाग = 8;
		अगर (dc->debug.dsc_bpp_increment_भाग >= 16)
			dsc_sink_caps->bpp_increment_भाग = 16;
	पूर्ण

	/* Extended caps */
	अगर (dpcd_dsc_branch_decoder_caps == शून्य) अणु // branch decoder DPCD DSC data can be null क्रम non branch device
		dsc_sink_caps->branch_overall_throughput_0_mps = 0;
		dsc_sink_caps->branch_overall_throughput_1_mps = 0;
		dsc_sink_caps->branch_max_line_width = 0;
		वापस true;
	पूर्ण

	dsc_sink_caps->branch_overall_throughput_0_mps = dpcd_dsc_branch_decoder_caps[DP_DSC_BRANCH_OVERALL_THROUGHPUT_0 - DP_DSC_BRANCH_OVERALL_THROUGHPUT_0];
	अगर (dsc_sink_caps->branch_overall_throughput_0_mps == 0)
		dsc_sink_caps->branch_overall_throughput_0_mps = 0;
	अन्यथा अगर (dsc_sink_caps->branch_overall_throughput_0_mps == 1)
		dsc_sink_caps->branch_overall_throughput_0_mps = 680;
	अन्यथा अणु
		dsc_sink_caps->branch_overall_throughput_0_mps *= 50;
		dsc_sink_caps->branch_overall_throughput_0_mps += 600;
	पूर्ण

	dsc_sink_caps->branch_overall_throughput_1_mps = dpcd_dsc_branch_decoder_caps[DP_DSC_BRANCH_OVERALL_THROUGHPUT_1 - DP_DSC_BRANCH_OVERALL_THROUGHPUT_0];
	अगर (dsc_sink_caps->branch_overall_throughput_1_mps == 0)
		dsc_sink_caps->branch_overall_throughput_1_mps = 0;
	अन्यथा अगर (dsc_sink_caps->branch_overall_throughput_1_mps == 1)
		dsc_sink_caps->branch_overall_throughput_1_mps = 680;
	अन्यथा अणु
		dsc_sink_caps->branch_overall_throughput_1_mps *= 50;
		dsc_sink_caps->branch_overall_throughput_1_mps += 600;
	पूर्ण

	dsc_sink_caps->branch_max_line_width = dpcd_dsc_branch_decoder_caps[DP_DSC_BRANCH_MAX_LINE_WIDTH - DP_DSC_BRANCH_OVERALL_THROUGHPUT_0] * 320;
	ASSERT(dsc_sink_caps->branch_max_line_width == 0 || dsc_sink_caps->branch_max_line_width >= 5120);

	वापस true;
पूर्ण


/* If DSC is possbile, get DSC bandwidth range based on [min_bpp, max_bpp] target bitrate range and
 * timing's pixel घड़ी and uncompressed bandwidth.
 * If DSC is not possible, leave '*range' untouched.
 */
bool dc_dsc_compute_bandwidth_range(
		स्थिर काष्ठा display_stream_compressor *dsc,
		uपूर्णांक32_t dsc_min_slice_height_override,
		uपूर्णांक32_t min_bpp_x16,
		uपूर्णांक32_t max_bpp_x16,
		स्थिर काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps,
		स्थिर काष्ठा dc_crtc_timing *timing,
		काष्ठा dc_dsc_bw_range *range)
अणु
	bool is_dsc_possible = false;
	काष्ठा dsc_enc_caps dsc_enc_caps;
	काष्ठा dsc_enc_caps dsc_common_caps;
	काष्ठा dc_dsc_config config;

	get_dsc_enc_caps(dsc, &dsc_enc_caps, timing->pix_clk_100hz);

	is_dsc_possible = पूर्णांकersect_dsc_caps(dsc_sink_caps, &dsc_enc_caps,
			timing->pixel_encoding, &dsc_common_caps);

	अगर (is_dsc_possible)
		is_dsc_possible = setup_dsc_config(dsc_sink_caps, &dsc_enc_caps, 0, timing,
				dsc_min_slice_height_override, max_bpp_x16, &config);

	अगर (is_dsc_possible)
		get_dsc_bandwidth_range(min_bpp_x16, max_bpp_x16, &dsc_common_caps, timing, range);

	वापस is_dsc_possible;
पूर्ण

bool dc_dsc_compute_config(
		स्थिर काष्ठा display_stream_compressor *dsc,
		स्थिर काष्ठा dsc_dec_dpcd_caps *dsc_sink_caps,
		uपूर्णांक32_t dsc_min_slice_height_override,
		uपूर्णांक32_t max_target_bpp_limit_override,
		uपूर्णांक32_t target_bandwidth_kbps,
		स्थिर काष्ठा dc_crtc_timing *timing,
		काष्ठा dc_dsc_config *dsc_cfg)
अणु
	bool is_dsc_possible = false;
	काष्ठा dsc_enc_caps dsc_enc_caps;

	get_dsc_enc_caps(dsc, &dsc_enc_caps, timing->pix_clk_100hz);
	is_dsc_possible = setup_dsc_config(dsc_sink_caps,
			&dsc_enc_caps,
			target_bandwidth_kbps,
			timing, dsc_min_slice_height_override,
			max_target_bpp_limit_override * 16, dsc_cfg);
	वापस is_dsc_possible;
पूर्ण

uपूर्णांक32_t dc_dsc_stream_bandwidth_in_kbps(uपूर्णांक32_t pix_clk_100hz, uपूर्णांक32_t bpp_x16)
अणु
	काष्ठा fixed31_32 link_bw_kbps;
	link_bw_kbps = dc_fixpt_from_पूर्णांक(pix_clk_100hz);
	link_bw_kbps = dc_fixpt_भाग_पूर्णांक(link_bw_kbps, 160);
	link_bw_kbps = dc_fixpt_mul_पूर्णांक(link_bw_kbps, bpp_x16);
	वापस dc_fixpt_उच्चमान(link_bw_kbps);
पूर्ण

व्योम dc_dsc_get_policy_क्रम_timing(स्थिर काष्ठा dc_crtc_timing *timing, uपूर्णांक32_t max_target_bpp_limit_override_x16, काष्ठा dc_dsc_policy *policy)
अणु
	uपूर्णांक32_t bpc = 0;

	policy->min_target_bpp = 0;
	policy->max_target_bpp = 0;

	/* DSC Policy: Use minimum number of slices that fits the pixel घड़ी */
	policy->use_min_slices_h = true;

	/* DSC Policy: Use max available slices
	 * (in our हाल 4 क्रम or 8, depending on the mode)
	 */
	policy->max_slices_h = 0;

	/* DSC Policy: Use slice height recommended
	 * by VESA DSC Spपढ़ोsheet user guide
	 */
	policy->min_slice_height = 108;

	/* DSC Policy: follow DP specs with an पूर्णांकernal upper limit to 16 bpp
	 * क्रम better पूर्णांकeroperability
	 */
	चयन (timing->display_color_depth) अणु
	हाल COLOR_DEPTH_888:
		bpc = 8;
		अवरोध;
	हाल COLOR_DEPTH_101010:
		bpc = 10;
		अवरोध;
	हाल COLOR_DEPTH_121212:
		bpc = 12;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	चयन (timing->pixel_encoding) अणु
	हाल PIXEL_ENCODING_RGB:
	हाल PIXEL_ENCODING_YCBCR444:
	हाल PIXEL_ENCODING_YCBCR422: /* assume no YCbCr422 native support */
		/* DP specs limits to 8 */
		policy->min_target_bpp = 8;
		/* DP specs limits to 3 x bpc */
		policy->max_target_bpp = 3 * bpc;
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR420:
		/* DP specs limits to 6 */
		policy->min_target_bpp = 6;
		/* DP specs limits to 1.5 x bpc assume bpc is an even number */
		policy->max_target_bpp = bpc * 3 / 2;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	policy->preferred_bpp_x16 = timing->dsc_fixed_bits_per_pixel_x16;

	/* पूर्णांकernal upper limit, शेष 16 bpp */
	अगर (policy->max_target_bpp > dsc_policy_max_target_bpp_limit)
		policy->max_target_bpp = dsc_policy_max_target_bpp_limit;

	/* apply override */
	अगर (max_target_bpp_limit_override_x16 && policy->max_target_bpp > max_target_bpp_limit_override_x16 / 16)
		policy->max_target_bpp = max_target_bpp_limit_override_x16 / 16;

	/* enable DSC when not needed, शेष false */
	अगर (dsc_policy_enable_dsc_when_not_needed)
		policy->enable_dsc_when_not_needed = dsc_policy_enable_dsc_when_not_needed;
	अन्यथा
		policy->enable_dsc_when_not_needed = false;
पूर्ण

व्योम dc_dsc_policy_set_max_target_bpp_limit(uपूर्णांक32_t limit)
अणु
	dsc_policy_max_target_bpp_limit = limit;
पूर्ण

व्योम dc_dsc_policy_set_enable_dsc_when_not_needed(bool enable)
अणु
	dsc_policy_enable_dsc_when_not_needed = enable;
पूर्ण
