<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#समावेश "dm_services.h"
#समावेश "dcn_calc_auto.h"
#समावेश "dcn_calc_math.h"

/*
 * NOTE:
 *   This file is gcc-parseable HW gospel, coming straight from HW engineers.
 *
 * It करोesn't adhere to Linux kernel style and someबार will करो things in odd
 * ways. Unless there is something clearly wrong with it the code should
 * reमुख्य as-is as it provides us with a guarantee from HW that it is correct.
 */

/*REVISION#250*/
व्योम scaler_settings_calculation(काष्ठा dcn_bw_पूर्णांकernal_vars *v)
अणु
	पूर्णांक k;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->allow_dअगरferent_hratio_vratio == dcn_bw_yes) अणु
			अगर (v->source_scan[k] == dcn_bw_hor) अणु
				v->h_ratio[k] = v->viewport_width[k] / v->scaler_rec_out_width[k];
				v->v_ratio[k] = v->viewport_height[k] / v->scaler_recout_height[k];
			पूर्ण
			अन्यथा अणु
				v->h_ratio[k] = v->viewport_height[k] / v->scaler_rec_out_width[k];
				v->v_ratio[k] = v->viewport_width[k] / v->scaler_recout_height[k];
			पूर्ण
		पूर्ण
		अन्यथा अणु
			अगर (v->source_scan[k] == dcn_bw_hor) अणु
				v->h_ratio[k] =dcn_bw_max2(v->viewport_width[k] / v->scaler_rec_out_width[k], v->viewport_height[k] / v->scaler_recout_height[k]);
			पूर्ण
			अन्यथा अणु
				v->h_ratio[k] =dcn_bw_max2(v->viewport_height[k] / v->scaler_rec_out_width[k], v->viewport_width[k] / v->scaler_recout_height[k]);
			पूर्ण
			v->v_ratio[k] = v->h_ratio[k];
		पूर्ण
		अगर (v->पूर्णांकerlace_output[k] == 1.0) अणु
			v->v_ratio[k] = 2.0 * v->v_ratio[k];
		पूर्ण
		अगर (v->underscan_output[k] == 1.0) अणु
			v->h_ratio[k] = v->h_ratio[k] * v->under_scan_factor;
			v->v_ratio[k] = v->v_ratio[k] * v->under_scan_factor;
		पूर्ण
	पूर्ण
	/*scaler taps calculation*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->h_ratio[k] > 1.0) अणु
			v->acceptable_quality_hta_ps =dcn_bw_min2(v->max_hscl_taps, 2.0 *dcn_bw_उच्चमान2(v->h_ratio[k], 1.0));
		पूर्ण
		अन्यथा अगर (v->h_ratio[k] < 1.0) अणु
			v->acceptable_quality_hta_ps = 4.0;
		पूर्ण
		अन्यथा अणु
			v->acceptable_quality_hta_ps = 1.0;
		पूर्ण
		अगर (v->ta_pscalculation == dcn_bw_override) अणु
			v->htaps[k] = v->override_hta_ps[k];
		पूर्ण
		अन्यथा अणु
			v->htaps[k] = v->acceptable_quality_hta_ps;
		पूर्ण
		अगर (v->v_ratio[k] > 1.0) अणु
			v->acceptable_quality_vta_ps =dcn_bw_min2(v->max_vscl_taps, 2.0 *dcn_bw_उच्चमान2(v->v_ratio[k], 1.0));
		पूर्ण
		अन्यथा अगर (v->v_ratio[k] < 1.0) अणु
			v->acceptable_quality_vta_ps = 4.0;
		पूर्ण
		अन्यथा अणु
			v->acceptable_quality_vta_ps = 1.0;
		पूर्ण
		अगर (v->ta_pscalculation == dcn_bw_override) अणु
			v->vtaps[k] = v->override_vta_ps[k];
		पूर्ण
		अन्यथा अणु
			v->vtaps[k] = v->acceptable_quality_vta_ps;
		पूर्ण
		अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16) अणु
			v->vta_pschroma[k] = 0.0;
			v->hta_pschroma[k] = 0.0;
		पूर्ण
		अन्यथा अणु
			अगर (v->ta_pscalculation == dcn_bw_override) अणु
				v->vta_pschroma[k] = v->override_vta_pschroma[k];
				v->hta_pschroma[k] = v->override_hta_pschroma[k];
			पूर्ण
			अन्यथा अणु
				v->vta_pschroma[k] = v->acceptable_quality_vta_ps;
				v->hta_pschroma[k] = v->acceptable_quality_hta_ps;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम mode_support_and_प्रणाली_configuration(काष्ठा dcn_bw_पूर्णांकernal_vars *v)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक k;
	/*mode support, voltage state and soc configuration*/

	/*scale ratio support check*/

	v->scale_ratio_support = dcn_bw_yes;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->h_ratio[k] > v->max_hscl_ratio || v->v_ratio[k] > v->max_vscl_ratio || v->h_ratio[k] > v->htaps[k] || v->v_ratio[k] > v->vtaps[k] || (v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_64 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_32 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_16 && (v->h_ratio[k] / 2.0 > v->hta_pschroma[k] || v->v_ratio[k] / 2.0 > v->vta_pschroma[k]))) अणु
			v->scale_ratio_support = dcn_bw_no;
		पूर्ण
	पूर्ण
	/*source क्रमmat, pixel क्रमmat and scan support check*/

	v->source_क्रमmat_pixel_and_scan_support = dcn_bw_yes;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर ((v->source_surface_mode[k] == dcn_bw_sw_linear && v->source_scan[k] != dcn_bw_hor) || ((v->source_surface_mode[k] == dcn_bw_sw_4_kb_d || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_x || v->source_surface_mode[k] == dcn_bw_sw_var_d || v->source_surface_mode[k] == dcn_bw_sw_var_d_x) && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_64)) अणु
			v->source_क्रमmat_pixel_and_scan_support = dcn_bw_no;
		पूर्ण
	पूर्ण
	/*bandwidth support check*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->source_scan[k] == dcn_bw_hor) अणु
			v->swath_width_ysingle_dpp[k] = v->viewport_width[k];
		पूर्ण
		अन्यथा अणु
			v->swath_width_ysingle_dpp[k] = v->viewport_height[k];
		पूर्ण
		अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64) अणु
			v->byte_per_pixel_in_dety[k] = 8.0;
			v->byte_per_pixel_in_detc[k] = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32) अणु
			v->byte_per_pixel_in_dety[k] = 4.0;
			v->byte_per_pixel_in_detc[k] = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16) अणु
			v->byte_per_pixel_in_dety[k] = 2.0;
			v->byte_per_pixel_in_detc[k] = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8) अणु
			v->byte_per_pixel_in_dety[k] = 1.0;
			v->byte_per_pixel_in_detc[k] = 2.0;
		पूर्ण
		अन्यथा अणु
			v->byte_per_pixel_in_dety[k] = 4.0f / 3.0f;
			v->byte_per_pixel_in_detc[k] = 8.0f / 3.0f;
		पूर्ण
	पूर्ण
	v->total_पढ़ो_bandwidth_consumed_gbyte_per_second = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->पढ़ो_bandwidth[k] = v->swath_width_ysingle_dpp[k] * (dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) * v->v_ratio[k] +dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 2.0 * v->v_ratio[k] / 2) / (v->htotal[k] / v->pixel_घड़ी[k]);
		अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
			v->पढ़ो_bandwidth[k] = v->पढ़ो_bandwidth[k] * (1 + 1 / 256);
		पूर्ण
		अगर (v->pte_enable == dcn_bw_yes && v->source_scan[k] != dcn_bw_hor && (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d_x)) अणु
			v->पढ़ो_bandwidth[k] = v->पढ़ो_bandwidth[k] * (1 + 1 / 64);
		पूर्ण
		अन्यथा अगर (v->pte_enable == dcn_bw_yes && v->source_scan[k] == dcn_bw_hor && (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32) && (v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_x)) अणु
			v->पढ़ो_bandwidth[k] = v->पढ़ो_bandwidth[k] * (1 + 1 / 256);
		पूर्ण
		अन्यथा अगर (v->pte_enable == dcn_bw_yes) अणु
			v->पढ़ो_bandwidth[k] = v->पढ़ो_bandwidth[k] * (1 + 1 / 512);
		पूर्ण
		v->total_पढ़ो_bandwidth_consumed_gbyte_per_second = v->total_पढ़ो_bandwidth_consumed_gbyte_per_second + v->पढ़ो_bandwidth[k] / 1000.0;
	पूर्ण
	v->total_ग_लिखो_bandwidth_consumed_gbyte_per_second = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->output[k] == dcn_bw_ग_लिखोback && v->output_क्रमmat[k] == dcn_bw_444) अणु
			v->ग_लिखो_bandwidth[k] = v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k]) * 4.0;
		पूर्ण
		अन्यथा अगर (v->output[k] == dcn_bw_ग_लिखोback) अणु
			v->ग_लिखो_bandwidth[k] = v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k]) * 1.5;
		पूर्ण
		अन्यथा अणु
			v->ग_लिखो_bandwidth[k] = 0.0;
		पूर्ण
		v->total_ग_लिखो_bandwidth_consumed_gbyte_per_second = v->total_ग_लिखो_bandwidth_consumed_gbyte_per_second + v->ग_लिखो_bandwidth[k] / 1000.0;
	पूर्ण
	v->total_bandwidth_consumed_gbyte_per_second = v->total_पढ़ो_bandwidth_consumed_gbyte_per_second + v->total_ग_लिखो_bandwidth_consumed_gbyte_per_second;
	v->dcc_enabled_in_any_plane = dcn_bw_no;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
			v->dcc_enabled_in_any_plane = dcn_bw_yes;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		v->वापस_bw_todcn_per_state =dcn_bw_min2(v->वापस_bus_width * v->dcfclk_per_state[i], v->fabric_and_dram_bandwidth_per_state[i] * 1000.0 * v->percent_of_ideal_drambw_received_after_urg_latency / 100.0);
		v->वापस_bw_per_state[i] = v->वापस_bw_todcn_per_state;
		अगर (v->dcc_enabled_in_any_plane == dcn_bw_yes && v->वापस_bw_todcn_per_state > v->dcfclk_per_state[i] * v->वापस_bus_width / 4.0) अणु
			v->वापस_bw_per_state[i] =dcn_bw_min2(v->वापस_bw_per_state[i], v->वापस_bw_todcn_per_state * 4.0 * (1.0 - v->urgent_latency / ((v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 / (v->वापस_bw_todcn_per_state - v->dcfclk_per_state[i] * v->वापस_bus_width / 4.0) + v->urgent_latency)));
		पूर्ण
		v->critical_poपूर्णांक = 2.0 * v->वापस_bus_width * v->dcfclk_per_state[i] * v->urgent_latency / (v->वापस_bw_todcn_per_state * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0);
		अगर (v->dcc_enabled_in_any_plane == dcn_bw_yes && v->critical_poपूर्णांक > 1.0 && v->critical_poपूर्णांक < 4.0) अणु
			v->वापस_bw_per_state[i] =dcn_bw_min2(v->वापस_bw_per_state[i], dcn_bw_घात(4.0 * v->वापस_bw_todcn_per_state * (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 * v->वापस_bus_width * v->dcfclk_per_state[i] * v->urgent_latency / (v->वापस_bw_todcn_per_state * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0), 2));
		पूर्ण
		v->वापस_bw_todcn_per_state =dcn_bw_min2(v->वापस_bus_width * v->dcfclk_per_state[i], v->fabric_and_dram_bandwidth_per_state[i] * 1000.0);
		अगर (v->dcc_enabled_in_any_plane == dcn_bw_yes && v->वापस_bw_todcn_per_state > v->dcfclk_per_state[i] * v->वापस_bus_width / 4.0) अणु
			v->वापस_bw_per_state[i] =dcn_bw_min2(v->वापस_bw_per_state[i], v->वापस_bw_todcn_per_state * 4.0 * (1.0 - v->urgent_latency / ((v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 / (v->वापस_bw_todcn_per_state - v->dcfclk_per_state[i] * v->वापस_bus_width / 4.0) + v->urgent_latency)));
		पूर्ण
		v->critical_poपूर्णांक = 2.0 * v->वापस_bus_width * v->dcfclk_per_state[i] * v->urgent_latency / (v->वापस_bw_todcn_per_state * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0);
		अगर (v->dcc_enabled_in_any_plane == dcn_bw_yes && v->critical_poपूर्णांक > 1.0 && v->critical_poपूर्णांक < 4.0) अणु
			v->वापस_bw_per_state[i] =dcn_bw_min2(v->वापस_bw_per_state[i], dcn_bw_घात(4.0 * v->वापस_bw_todcn_per_state * (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 * v->वापस_bus_width * v->dcfclk_per_state[i] * v->urgent_latency / (v->वापस_bw_todcn_per_state * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0), 2));
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		अगर ((v->total_पढ़ो_bandwidth_consumed_gbyte_per_second * 1000.0 <= v->वापस_bw_per_state[i]) && (v->total_bandwidth_consumed_gbyte_per_second * 1000.0 <= v->fabric_and_dram_bandwidth_per_state[i] * 1000.0 * v->percent_of_ideal_drambw_received_after_urg_latency / 100.0)) अणु
			v->bandwidth_support[i] = dcn_bw_yes;
		पूर्ण
		अन्यथा अणु
			v->bandwidth_support[i] = dcn_bw_no;
		पूर्ण
	पूर्ण
	/*ग_लिखोback latency support check*/

	v->ग_लिखोback_latency_support = dcn_bw_yes;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->output[k] == dcn_bw_ग_लिखोback && v->output_क्रमmat[k] == dcn_bw_444 && v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k]) * 4.0 > (v->ग_लिखोback_luma_buffer_size + v->ग_लिखोback_chroma_buffer_size) * 1024.0 / v->ग_लिखो_back_latency) अणु
			v->ग_लिखोback_latency_support = dcn_bw_no;
		पूर्ण
		अन्यथा अगर (v->output[k] == dcn_bw_ग_लिखोback && v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k]) >dcn_bw_min2(v->ग_लिखोback_luma_buffer_size, 2.0 * v->ग_लिखोback_chroma_buffer_size) * 1024.0 / v->ग_लिखो_back_latency) अणु
			v->ग_लिखोback_latency_support = dcn_bw_no;
		पूर्ण
	पूर्ण
	/*re-ordering buffer support check*/

	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		v->urgent_round_trip_and_out_of_order_latency_per_state[i] = (v->round_trip_ping_latency_cycles + 32.0) / v->dcfclk_per_state[i] + v->urgent_out_of_order_वापस_per_channel * v->number_of_channels / v->वापस_bw_per_state[i];
		अगर ((v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 / v->वापस_bw_per_state[i] > v->urgent_round_trip_and_out_of_order_latency_per_state[i]) अणु
			v->rob_support[i] = dcn_bw_yes;
		पूर्ण
		अन्यथा अणु
			v->rob_support[i] = dcn_bw_no;
		पूर्ण
	पूर्ण
	/*display io support check*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->output[k] == dcn_bw_dp && v->dsc_capability == dcn_bw_yes) अणु
			अगर (v->output_क्रमmat[k] == dcn_bw_420) अणु
				v->required_output_bw = v->pixel_घड़ी[k] / 2.0;
			पूर्ण
			अन्यथा अणु
				v->required_output_bw = v->pixel_घड़ी[k];
			पूर्ण
		पूर्ण
		अन्यथा अगर (v->output_क्रमmat[k] == dcn_bw_420) अणु
			v->required_output_bw = v->pixel_घड़ी[k] * 3.0 / 2.0;
		पूर्ण
		अन्यथा अणु
			v->required_output_bw = v->pixel_घड़ी[k] * 3.0;
		पूर्ण
		अगर (v->output[k] == dcn_bw_hdmi) अणु
			v->required_phyclk[k] = v->required_output_bw;
			चयन (v->output_deep_color[k]) अणु
			हाल dcn_bw_encoder_10bpc:
				v->required_phyclk[k] =  v->required_phyclk[k] * 5.0 / 4;
			अवरोध;
			हाल dcn_bw_encoder_12bpc:
				v->required_phyclk[k] =  v->required_phyclk[k] * 3.0 / 2;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			v->required_phyclk[k] = v->required_phyclk[k] / 3.0;
		पूर्ण
		अन्यथा अगर (v->output[k] == dcn_bw_dp) अणु
			v->required_phyclk[k] = v->required_output_bw / 4.0;
		पूर्ण
		अन्यथा अणु
			v->required_phyclk[k] = 0.0;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		v->dio_support[i] = dcn_bw_yes;
		क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
			अगर (v->required_phyclk[k] > v->phyclk_per_state[i] || (v->output[k] == dcn_bw_hdmi && v->required_phyclk[k] > 600.0)) अणु
				v->dio_support[i] = dcn_bw_no;
			पूर्ण
		पूर्ण
	पूर्ण
	/*total available ग_लिखोback support check*/

	v->total_number_of_active_ग_लिखोback = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->output[k] == dcn_bw_ग_लिखोback) अणु
			v->total_number_of_active_ग_लिखोback = v->total_number_of_active_ग_लिखोback + 1.0;
		पूर्ण
	पूर्ण
	अगर (v->total_number_of_active_ग_लिखोback <= v->max_num_ग_लिखोback) अणु
		v->total_available_ग_लिखोback_support = dcn_bw_yes;
	पूर्ण
	अन्यथा अणु
		v->total_available_ग_लिखोback_support = dcn_bw_no;
	पूर्ण
	/*maximum dispclk/dppclk support check*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->h_ratio[k] > 1.0) अणु
			v->pscl_factor[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput * v->h_ratio[k] /dcn_bw_उच्चमान2(v->htaps[k] / 6.0, 1.0));
		पूर्ण
		अन्यथा अणु
			v->pscl_factor[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput);
		पूर्ण
		अगर (v->byte_per_pixel_in_detc[k] == 0.0) अणु
			v->pscl_factor_chroma[k] = 0.0;
			v->min_dppclk_using_single_dpp[k] = v->pixel_घड़ी[k] *dcn_bw_max3(v->vtaps[k] / 6.0 *dcn_bw_min2(1.0, v->h_ratio[k]), v->h_ratio[k] * v->v_ratio[k] / v->pscl_factor[k], 1.0);
		पूर्ण
		अन्यथा अणु
			अगर (v->h_ratio[k] / 2.0 > 1.0) अणु
				v->pscl_factor_chroma[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput * v->h_ratio[k] / 2.0 /dcn_bw_उच्चमान2(v->hta_pschroma[k] / 6.0, 1.0));
			पूर्ण
			अन्यथा अणु
				v->pscl_factor_chroma[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput);
			पूर्ण
			v->min_dppclk_using_single_dpp[k] = v->pixel_घड़ी[k] *dcn_bw_max5(v->vtaps[k] / 6.0 *dcn_bw_min2(1.0, v->h_ratio[k]), v->h_ratio[k] * v->v_ratio[k] / v->pscl_factor[k], v->vta_pschroma[k] / 6.0 *dcn_bw_min2(1.0, v->h_ratio[k] / 2.0), v->h_ratio[k] * v->v_ratio[k] / 4.0 / v->pscl_factor_chroma[k], 1.0);
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर ((v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16)) अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->पढ़ो256_block_height_y[k] = 1.0;
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64) अणु
				v->पढ़ो256_block_height_y[k] = 4.0;
			पूर्ण
			अन्यथा अणु
				v->पढ़ो256_block_height_y[k] = 8.0;
			पूर्ण
			v->पढ़ो256_block_width_y[k] = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / v->पढ़ो256_block_height_y[k];
			v->पढ़ो256_block_height_c[k] = 0.0;
			v->पढ़ो256_block_width_c[k] = 0.0;
		पूर्ण
		अन्यथा अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->पढ़ो256_block_height_y[k] = 1.0;
				v->पढ़ो256_block_height_c[k] = 1.0;
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8) अणु
				v->पढ़ो256_block_height_y[k] = 16.0;
				v->पढ़ो256_block_height_c[k] = 8.0;
			पूर्ण
			अन्यथा अणु
				v->पढ़ो256_block_height_y[k] = 8.0;
				v->पढ़ो256_block_height_c[k] = 8.0;
			पूर्ण
			v->पढ़ो256_block_width_y[k] = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / v->पढ़ो256_block_height_y[k];
			v->पढ़ो256_block_width_c[k] = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / v->पढ़ो256_block_height_c[k];
		पूर्ण
		अगर (v->source_scan[k] == dcn_bw_hor) अणु
			v->max_swath_height_y[k] = v->पढ़ो256_block_height_y[k];
			v->max_swath_height_c[k] = v->पढ़ो256_block_height_c[k];
		पूर्ण
		अन्यथा अणु
			v->max_swath_height_y[k] = v->पढ़ो256_block_width_y[k];
			v->max_swath_height_c[k] = v->पढ़ो256_block_width_c[k];
		पूर्ण
		अगर ((v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16)) अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear || (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 && (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_var_s || v->source_surface_mode[k] == dcn_bw_sw_var_s_x) && v->source_scan[k] == dcn_bw_hor)) अणु
				v->min_swath_height_y[k] = v->max_swath_height_y[k];
			पूर्ण
			अन्यथा अणु
				v->min_swath_height_y[k] = v->max_swath_height_y[k] / 2.0;
			पूर्ण
			v->min_swath_height_c[k] = v->max_swath_height_c[k];
		पूर्ण
		अन्यथा अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->min_swath_height_y[k] = v->max_swath_height_y[k];
				v->min_swath_height_c[k] = v->max_swath_height_c[k];
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8 && v->source_scan[k] == dcn_bw_hor) अणु
				v->min_swath_height_y[k] = v->max_swath_height_y[k] / 2.0;
				अगर (v->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes) अणु
					v->min_swath_height_c[k] = v->max_swath_height_c[k];
				पूर्ण
				अन्यथा अणु
					v->min_swath_height_c[k] = v->max_swath_height_c[k] / 2.0;
				पूर्ण
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_10 && v->source_scan[k] == dcn_bw_hor) अणु
				v->min_swath_height_c[k] = v->max_swath_height_c[k] / 2.0;
				अगर (v->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes) अणु
					v->min_swath_height_y[k] = v->max_swath_height_y[k];
				पूर्ण
				अन्यथा अणु
					v->min_swath_height_y[k] = v->max_swath_height_y[k] / 2.0;
				पूर्ण
			पूर्ण
			अन्यथा अणु
				v->min_swath_height_y[k] = v->max_swath_height_y[k];
				v->min_swath_height_c[k] = v->max_swath_height_c[k];
			पूर्ण
		पूर्ण
		अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
			v->maximum_swath_width = 8192.0;
		पूर्ण
		अन्यथा अणु
			v->maximum_swath_width = 5120.0;
		पूर्ण
		v->number_of_dpp_required_क्रम_det_size =dcn_bw_उच्चमान2(v->swath_width_ysingle_dpp[k] /dcn_bw_min2(v->maximum_swath_width, v->det_buffer_size_in_kbyte * 1024.0 / 2.0 / (v->byte_per_pixel_in_dety[k] * v->min_swath_height_y[k] + v->byte_per_pixel_in_detc[k] / 2.0 * v->min_swath_height_c[k])), 1.0);
		अगर (v->byte_per_pixel_in_detc[k] == 0.0) अणु
			v->number_of_dpp_required_क्रम_lb_size =dcn_bw_उच्चमान2((v->vtaps[k] +dcn_bw_max2(dcn_bw_उच्चमान2(v->v_ratio[k], 1.0) - 2, 0.0)) * v->swath_width_ysingle_dpp[k] /dcn_bw_max2(v->h_ratio[k], 1.0) * v->lb_bit_per_pixel[k] / v->line_buffer_size, 1.0);
		पूर्ण
		अन्यथा अणु
			v->number_of_dpp_required_क्रम_lb_size =dcn_bw_max2(dcn_bw_उच्चमान2((v->vtaps[k] +dcn_bw_max2(dcn_bw_उच्चमान2(v->v_ratio[k], 1.0) - 2, 0.0)) * v->swath_width_ysingle_dpp[k] /dcn_bw_max2(v->h_ratio[k], 1.0) * v->lb_bit_per_pixel[k] / v->line_buffer_size, 1.0),dcn_bw_उच्चमान2((v->vta_pschroma[k] +dcn_bw_max2(dcn_bw_उच्चमान2(v->v_ratio[k] / 2.0, 1.0) - 2, 0.0)) * v->swath_width_ysingle_dpp[k] / 2.0 /dcn_bw_max2(v->h_ratio[k] / 2.0, 1.0) * v->lb_bit_per_pixel[k] / v->line_buffer_size, 1.0));
		पूर्ण
		v->number_of_dpp_required_क्रम_det_and_lb_size[k] =dcn_bw_max2(v->number_of_dpp_required_क्रम_det_size, v->number_of_dpp_required_क्रम_lb_size);
	पूर्ण
	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		क्रम (j = 0; j <= 1; j++) अणु
			v->total_number_of_active_dpp[i][j] = 0.0;
			v->required_dispclk[i][j] = 0.0;
			v->dispclk_dppclk_support[i][j] = dcn_bw_yes;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				v->min_dispclk_using_single_dpp =dcn_bw_max2(v->pixel_घड़ी[k], v->min_dppclk_using_single_dpp[k] * (j + 1)) * (1.0 + v->करोwnspपढ़ोing / 100.0);
				अगर (v->odm_capability == dcn_bw_yes) अणु
					v->min_dispclk_using_dual_dpp =dcn_bw_max2(v->pixel_घड़ी[k] / 2.0, v->min_dppclk_using_single_dpp[k] / 2.0 * (j + 1)) * (1.0 + v->करोwnspपढ़ोing / 100.0);
				पूर्ण
				अन्यथा अणु
					v->min_dispclk_using_dual_dpp =dcn_bw_max2(v->pixel_घड़ी[k], v->min_dppclk_using_single_dpp[k] / 2.0 * (j + 1)) * (1.0 + v->करोwnspपढ़ोing / 100.0);
				पूर्ण
				अगर (i < number_of_states) अणु
					v->min_dispclk_using_single_dpp = v->min_dispclk_using_single_dpp * (1.0 + v->dispclk_ramping_margin / 100.0);
					v->min_dispclk_using_dual_dpp = v->min_dispclk_using_dual_dpp * (1.0 + v->dispclk_ramping_margin / 100.0);
				पूर्ण
				अगर (v->min_dispclk_using_single_dpp <=dcn_bw_min2(v->max_dispclk[i], (j + 1) * v->max_dppclk[i]) && v->number_of_dpp_required_क्रम_det_and_lb_size[k] <= 1.0) अणु
					v->no_of_dpp[i][j][k] = 1.0;
					v->required_dispclk[i][j] =dcn_bw_max2(v->required_dispclk[i][j], v->min_dispclk_using_single_dpp);
				पूर्ण
				अन्यथा अगर (v->min_dispclk_using_dual_dpp <=dcn_bw_min2(v->max_dispclk[i], (j + 1) * v->max_dppclk[i])) अणु
					v->no_of_dpp[i][j][k] = 2.0;
					v->required_dispclk[i][j] =dcn_bw_max2(v->required_dispclk[i][j], v->min_dispclk_using_dual_dpp);
				पूर्ण
				अन्यथा अणु
					v->no_of_dpp[i][j][k] = 2.0;
					v->required_dispclk[i][j] =dcn_bw_max2(v->required_dispclk[i][j], v->min_dispclk_using_dual_dpp);
					v->dispclk_dppclk_support[i][j] = dcn_bw_no;
				पूर्ण
				v->total_number_of_active_dpp[i][j] = v->total_number_of_active_dpp[i][j] + v->no_of_dpp[i][j][k];
			पूर्ण
			अगर (v->total_number_of_active_dpp[i][j] > v->max_num_dpp) अणु
				v->total_number_of_active_dpp[i][j] = 0.0;
				v->required_dispclk[i][j] = 0.0;
				v->dispclk_dppclk_support[i][j] = dcn_bw_yes;
				क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
					v->min_dispclk_using_single_dpp =dcn_bw_max2(v->pixel_घड़ी[k], v->min_dppclk_using_single_dpp[k] * (j + 1)) * (1.0 + v->करोwnspपढ़ोing / 100.0);
					v->min_dispclk_using_dual_dpp =dcn_bw_max2(v->pixel_घड़ी[k], v->min_dppclk_using_single_dpp[k] / 2.0 * (j + 1)) * (1.0 + v->करोwnspपढ़ोing / 100.0);
					अगर (i < number_of_states) अणु
						v->min_dispclk_using_single_dpp = v->min_dispclk_using_single_dpp * (1.0 + v->dispclk_ramping_margin / 100.0);
						v->min_dispclk_using_dual_dpp = v->min_dispclk_using_dual_dpp * (1.0 + v->dispclk_ramping_margin / 100.0);
					पूर्ण
					अगर (v->number_of_dpp_required_क्रम_det_and_lb_size[k] <= 1.0) अणु
						v->no_of_dpp[i][j][k] = 1.0;
						v->required_dispclk[i][j] =dcn_bw_max2(v->required_dispclk[i][j], v->min_dispclk_using_single_dpp);
						अगर (v->min_dispclk_using_single_dpp >dcn_bw_min2(v->max_dispclk[i], (j + 1) * v->max_dppclk[i])) अणु
							v->dispclk_dppclk_support[i][j] = dcn_bw_no;
						पूर्ण
					पूर्ण
					अन्यथा अणु
						v->no_of_dpp[i][j][k] = 2.0;
						v->required_dispclk[i][j] =dcn_bw_max2(v->required_dispclk[i][j], v->min_dispclk_using_dual_dpp);
						अगर (v->min_dispclk_using_dual_dpp >dcn_bw_min2(v->max_dispclk[i], (j + 1) * v->max_dppclk[i])) अणु
							v->dispclk_dppclk_support[i][j] = dcn_bw_no;
						पूर्ण
					पूर्ण
					v->total_number_of_active_dpp[i][j] = v->total_number_of_active_dpp[i][j] + v->no_of_dpp[i][j][k];
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*viewport size check*/

	v->viewport_size_support = dcn_bw_yes;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->number_of_dpp_required_क्रम_det_and_lb_size[k] > 2.0) अणु
			v->viewport_size_support = dcn_bw_no;
		पूर्ण
	पूर्ण
	/*total available pipes support check*/

	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		क्रम (j = 0; j <= 1; j++) अणु
			अगर (v->total_number_of_active_dpp[i][j] <= v->max_num_dpp) अणु
				v->total_available_pipes_support[i][j] = dcn_bw_yes;
			पूर्ण
			अन्यथा अणु
				v->total_available_pipes_support[i][j] = dcn_bw_no;
			पूर्ण
		पूर्ण
	पूर्ण
	/*urgent latency support check*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
			क्रम (j = 0; j <= 1; j++) अणु
				v->swath_width_yper_state[i][j][k] = v->swath_width_ysingle_dpp[k] / v->no_of_dpp[i][j][k];
				v->swath_width_granularity_y = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / v->max_swath_height_y[k];
				v->rounded_up_max_swath_size_bytes_y = (dcn_bw_उच्चमान2(v->swath_width_yper_state[i][j][k] - 1.0, v->swath_width_granularity_y) + v->swath_width_granularity_y) * v->byte_per_pixel_in_dety[k] * v->max_swath_height_y[k];
				अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_10) अणु
					v->rounded_up_max_swath_size_bytes_y =dcn_bw_उच्चमान2(v->rounded_up_max_swath_size_bytes_y, 256.0) + 256;
				पूर्ण
				अगर (v->max_swath_height_c[k] > 0.0) अणु
					v->swath_width_granularity_c = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / v->max_swath_height_c[k];
				पूर्ण
				v->rounded_up_max_swath_size_bytes_c = (dcn_bw_उच्चमान2(v->swath_width_yper_state[i][j][k] / 2.0 - 1.0, v->swath_width_granularity_c) + v->swath_width_granularity_c) * v->byte_per_pixel_in_detc[k] * v->max_swath_height_c[k];
				अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_10) अणु
					v->rounded_up_max_swath_size_bytes_c =dcn_bw_उच्चमान2(v->rounded_up_max_swath_size_bytes_c, 256.0) + 256;
				पूर्ण
				अगर (v->rounded_up_max_swath_size_bytes_y + v->rounded_up_max_swath_size_bytes_c <= v->det_buffer_size_in_kbyte * 1024.0 / 2.0) अणु
					v->swath_height_yper_state[i][j][k] = v->max_swath_height_y[k];
					v->swath_height_cper_state[i][j][k] = v->max_swath_height_c[k];
				पूर्ण
				अन्यथा अणु
					v->swath_height_yper_state[i][j][k] = v->min_swath_height_y[k];
					v->swath_height_cper_state[i][j][k] = v->min_swath_height_c[k];
				पूर्ण
				अगर (v->byte_per_pixel_in_detc[k] == 0.0) अणु
					v->lines_in_det_luma = v->det_buffer_size_in_kbyte * 1024.0 / v->byte_per_pixel_in_dety[k] / v->swath_width_yper_state[i][j][k];
					v->lines_in_det_chroma = 0.0;
				पूर्ण
				अन्यथा अगर (v->swath_height_yper_state[i][j][k] <= v->swath_height_cper_state[i][j][k]) अणु
					v->lines_in_det_luma = v->det_buffer_size_in_kbyte * 1024.0 / 2.0 / v->byte_per_pixel_in_dety[k] / v->swath_width_yper_state[i][j][k];
					v->lines_in_det_chroma = v->det_buffer_size_in_kbyte * 1024.0 / 2.0 / v->byte_per_pixel_in_detc[k] / (v->swath_width_yper_state[i][j][k] / 2.0);
				पूर्ण
				अन्यथा अणु
					v->lines_in_det_luma = v->det_buffer_size_in_kbyte * 1024.0 * 2.0 / 3.0 / v->byte_per_pixel_in_dety[k] / v->swath_width_yper_state[i][j][k];
					v->lines_in_det_chroma = v->det_buffer_size_in_kbyte * 1024.0 / 3.0 / v->byte_per_pixel_in_dety[k] / (v->swath_width_yper_state[i][j][k] / 2.0);
				पूर्ण
				v->effective_lb_latency_hiding_source_lines_luma =dcn_bw_min2(v->max_line_buffer_lines,dcn_bw_न्यूनमान2(v->line_buffer_size / v->lb_bit_per_pixel[k] / (v->swath_width_yper_state[i][j][k] /dcn_bw_max2(v->h_ratio[k], 1.0)), 1.0)) - (v->vtaps[k] - 1.0);
				v->effective_lb_latency_hiding_source_lines_chroma =dcn_bw_min2(v->max_line_buffer_lines,dcn_bw_न्यूनमान2(v->line_buffer_size / v->lb_bit_per_pixel[k] / (v->swath_width_yper_state[i][j][k] / 2.0 /dcn_bw_max2(v->h_ratio[k] / 2.0, 1.0)), 1.0)) - (v->vta_pschroma[k] - 1.0);
				v->effective_detlb_lines_luma =dcn_bw_न्यूनमान2(v->lines_in_det_luma +dcn_bw_min2(v->lines_in_det_luma * v->required_dispclk[i][j] * v->byte_per_pixel_in_dety[k] * v->pscl_factor[k] / v->वापस_bw_per_state[i], v->effective_lb_latency_hiding_source_lines_luma), v->swath_height_yper_state[i][j][k]);
				v->effective_detlb_lines_chroma =dcn_bw_न्यूनमान2(v->lines_in_det_chroma +dcn_bw_min2(v->lines_in_det_chroma * v->required_dispclk[i][j] * v->byte_per_pixel_in_detc[k] * v->pscl_factor_chroma[k] / v->वापस_bw_per_state[i], v->effective_lb_latency_hiding_source_lines_chroma), v->swath_height_cper_state[i][j][k]);
				अगर (v->byte_per_pixel_in_detc[k] == 0.0) अणु
					v->urgent_latency_support_us_per_state[i][j][k] = v->effective_detlb_lines_luma * (v->htotal[k] / v->pixel_घड़ी[k]) / v->v_ratio[k] - v->effective_detlb_lines_luma * v->swath_width_yper_state[i][j][k] *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / (v->वापस_bw_per_state[i] / v->no_of_dpp[i][j][k]);
				पूर्ण
				अन्यथा अणु
					v->urgent_latency_support_us_per_state[i][j][k] =dcn_bw_min2(v->effective_detlb_lines_luma * (v->htotal[k] / v->pixel_घड़ी[k]) / v->v_ratio[k] - v->effective_detlb_lines_luma * v->swath_width_yper_state[i][j][k] *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / (v->वापस_bw_per_state[i] / v->no_of_dpp[i][j][k]), v->effective_detlb_lines_chroma * (v->htotal[k] / v->pixel_घड़ी[k]) / (v->v_ratio[k] / 2.0) - v->effective_detlb_lines_chroma * v->swath_width_yper_state[i][j][k] / 2.0 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / (v->वापस_bw_per_state[i] / v->no_of_dpp[i][j][k]));
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		क्रम (j = 0; j <= 1; j++) अणु
			v->urgent_latency_support[i][j] = dcn_bw_yes;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->urgent_latency_support_us_per_state[i][j][k] < v->urgent_latency / 1.0) अणु
					v->urgent_latency_support[i][j] = dcn_bw_no;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*prefetch check*/

	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		क्रम (j = 0; j <= 1; j++) अणु
			v->total_number_of_dcc_active_dpp[i][j] = 0.0;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
					v->total_number_of_dcc_active_dpp[i][j] = v->total_number_of_dcc_active_dpp[i][j] + v->no_of_dpp[i][j][k];
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		क्रम (j = 0; j <= 1; j++) अणु
			v->projected_dcfclk_deep_sleep = 8.0;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				v->projected_dcfclk_deep_sleep =dcn_bw_max2(v->projected_dcfclk_deep_sleep, v->pixel_घड़ी[k] / 16.0);
				अगर (v->byte_per_pixel_in_detc[k] == 0.0) अणु
					अगर (v->v_ratio[k] <= 1.0) अणु
						v->projected_dcfclk_deep_sleep =dcn_bw_max2(v->projected_dcfclk_deep_sleep, 1.1 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / 64.0 * v->h_ratio[k] * v->pixel_घड़ी[k] / v->no_of_dpp[i][j][k]);
					पूर्ण
					अन्यथा अणु
						v->projected_dcfclk_deep_sleep =dcn_bw_max2(v->projected_dcfclk_deep_sleep, 1.1 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / 64.0 * v->pscl_factor[k] * v->required_dispclk[i][j] / (1 + j));
					पूर्ण
				पूर्ण
				अन्यथा अणु
					अगर (v->v_ratio[k] <= 1.0) अणु
						v->projected_dcfclk_deep_sleep =dcn_bw_max2(v->projected_dcfclk_deep_sleep, 1.1 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / 32.0 * v->h_ratio[k] * v->pixel_घड़ी[k] / v->no_of_dpp[i][j][k]);
					पूर्ण
					अन्यथा अणु
						v->projected_dcfclk_deep_sleep =dcn_bw_max2(v->projected_dcfclk_deep_sleep, 1.1 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / 32.0 * v->pscl_factor[k] * v->required_dispclk[i][j] / (1 + j));
					पूर्ण
					अगर (v->v_ratio[k] / 2.0 <= 1.0) अणु
						v->projected_dcfclk_deep_sleep =dcn_bw_max2(v->projected_dcfclk_deep_sleep, 1.1 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 32.0 * v->h_ratio[k] / 2.0 * v->pixel_घड़ी[k] / v->no_of_dpp[i][j][k]);
					पूर्ण
					अन्यथा अणु
						v->projected_dcfclk_deep_sleep =dcn_bw_max2(v->projected_dcfclk_deep_sleep, 1.1 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 32.0 * v->pscl_factor_chroma[k] * v->required_dispclk[i][j] / (1 + j));
					पूर्ण
				पूर्ण
			पूर्ण
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
					v->meta_req_height_y = 8.0 * v->पढ़ो256_block_height_y[k];
					v->meta_req_width_y = 64.0 * 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / v->meta_req_height_y;
					v->meta_surface_width_y =dcn_bw_उच्चमान2(v->viewport_width[k] / v->no_of_dpp[i][j][k] - 1.0, v->meta_req_width_y) + v->meta_req_width_y;
					v->meta_surface_height_y =dcn_bw_उच्चमान2(v->viewport_height[k] - 1.0, v->meta_req_height_y) + v->meta_req_height_y;
					अगर (v->pte_enable == dcn_bw_yes) अणु
						v->meta_pte_bytes_per_frame_y = (dcn_bw_उच्चमान2((v->meta_surface_width_y * v->meta_surface_height_y *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
					पूर्ण
					अन्यथा अणु
						v->meta_pte_bytes_per_frame_y = 0.0;
					पूर्ण
					अगर (v->source_scan[k] == dcn_bw_hor) अणु
						v->meta_row_bytes_y = v->meta_surface_width_y * v->meta_req_height_y *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / 256.0;
					पूर्ण
					अन्यथा अणु
						v->meta_row_bytes_y = v->meta_surface_height_y * v->meta_req_width_y *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / 256.0;
					पूर्ण
				पूर्ण
				अन्यथा अणु
					v->meta_pte_bytes_per_frame_y = 0.0;
					v->meta_row_bytes_y = 0.0;
				पूर्ण
				अगर (v->pte_enable == dcn_bw_yes) अणु
					अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
						v->macro_tile_block_size_bytes_y = 256.0;
						v->macro_tile_block_height_y = 1.0;
					पूर्ण
					अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d_x) अणु
						v->macro_tile_block_size_bytes_y = 4096.0;
						v->macro_tile_block_height_y = 4.0 * v->पढ़ो256_block_height_y[k];
					पूर्ण
					अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_x) अणु
						v->macro_tile_block_size_bytes_y = 64.0 * 1024;
						v->macro_tile_block_height_y = 16.0 * v->पढ़ो256_block_height_y[k];
					पूर्ण
					अन्यथा अणु
						v->macro_tile_block_size_bytes_y = 256.0 * 1024;
						v->macro_tile_block_height_y = 32.0 * v->पढ़ो256_block_height_y[k];
					पूर्ण
					अगर (v->macro_tile_block_size_bytes_y <= 65536.0) अणु
						v->data_pte_req_height_y = v->macro_tile_block_height_y;
					पूर्ण
					अन्यथा अणु
						v->data_pte_req_height_y = 16.0 * v->पढ़ो256_block_height_y[k];
					पूर्ण
					v->data_pte_req_width_y = 4096.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) / v->data_pte_req_height_y * 8;
					अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
						v->dpte_bytes_per_row_y = 64.0 * (dcn_bw_उच्चमान2((v->viewport_width[k] / v->no_of_dpp[i][j][k] *dcn_bw_min2(128.0, dcn_bw_घात(2.0,dcn_bw_न्यूनमान2(dcn_bw_log(v->pte_buffer_size_in_requests * v->data_pte_req_width_y / (v->viewport_width[k] / v->no_of_dpp[i][j][k]), 2.0), 1.0))) - 1.0) / v->data_pte_req_width_y, 1.0) + 1);
					पूर्ण
					अन्यथा अगर (v->source_scan[k] == dcn_bw_hor) अणु
						v->dpte_bytes_per_row_y = 64.0 * (dcn_bw_उच्चमान2((v->viewport_width[k] / v->no_of_dpp[i][j][k] - 1.0) / v->data_pte_req_width_y, 1.0) + 1);
					पूर्ण
					अन्यथा अणु
						v->dpte_bytes_per_row_y = 64.0 * (dcn_bw_उच्चमान2((v->viewport_height[k] - 1.0) / v->data_pte_req_height_y, 1.0) + 1);
					पूर्ण
				पूर्ण
				अन्यथा अणु
					v->dpte_bytes_per_row_y = 0.0;
				पूर्ण
				अगर ((v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_64 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_32 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_16)) अणु
					अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
						v->meta_req_height_c = 8.0 * v->पढ़ो256_block_height_c[k];
						v->meta_req_width_c = 64.0 * 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / v->meta_req_height_c;
						v->meta_surface_width_c =dcn_bw_उच्चमान2(v->viewport_width[k] / v->no_of_dpp[i][j][k] / 2.0 - 1.0, v->meta_req_width_c) + v->meta_req_width_c;
						v->meta_surface_height_c =dcn_bw_उच्चमान2(v->viewport_height[k] / 2.0 - 1.0, v->meta_req_height_c) + v->meta_req_height_c;
						अगर (v->pte_enable == dcn_bw_yes) अणु
							v->meta_pte_bytes_per_frame_c = (dcn_bw_उच्चमान2((v->meta_surface_width_c * v->meta_surface_height_c *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
						पूर्ण
						अन्यथा अणु
							v->meta_pte_bytes_per_frame_c = 0.0;
						पूर्ण
						अगर (v->source_scan[k] == dcn_bw_hor) अणु
							v->meta_row_bytes_c = v->meta_surface_width_c * v->meta_req_height_c *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 256.0;
						पूर्ण
						अन्यथा अणु
							v->meta_row_bytes_c = v->meta_surface_height_c * v->meta_req_width_c *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 256.0;
						पूर्ण
					पूर्ण
					अन्यथा अणु
						v->meta_pte_bytes_per_frame_c = 0.0;
						v->meta_row_bytes_c = 0.0;
					पूर्ण
					अगर (v->pte_enable == dcn_bw_yes) अणु
						अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
							v->macro_tile_block_size_bytes_c = 256.0;
							v->macro_tile_block_height_c = 1.0;
						पूर्ण
						अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d_x) अणु
							v->macro_tile_block_size_bytes_c = 4096.0;
							v->macro_tile_block_height_c = 4.0 * v->पढ़ो256_block_height_c[k];
						पूर्ण
						अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_x) अणु
							v->macro_tile_block_size_bytes_c = 64.0 * 1024;
							v->macro_tile_block_height_c = 16.0 * v->पढ़ो256_block_height_c[k];
						पूर्ण
						अन्यथा अणु
							v->macro_tile_block_size_bytes_c = 256.0 * 1024;
							v->macro_tile_block_height_c = 32.0 * v->पढ़ो256_block_height_c[k];
						पूर्ण
						v->macro_tile_block_width_c = v->macro_tile_block_size_bytes_c /dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / v->macro_tile_block_height_c;
						अगर (v->macro_tile_block_size_bytes_c <= 65536.0) अणु
							v->data_pte_req_height_c = v->macro_tile_block_height_c;
						पूर्ण
						अन्यथा अणु
							v->data_pte_req_height_c = 16.0 * v->पढ़ो256_block_height_c[k];
						पूर्ण
						v->data_pte_req_width_c = 4096.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / v->data_pte_req_height_c * 8;
						अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
							v->dpte_bytes_per_row_c = 64.0 * (dcn_bw_उच्चमान2((v->viewport_width[k] / v->no_of_dpp[i][j][k] / 2.0 * dcn_bw_min2(128.0, dcn_bw_घात(2.0,dcn_bw_न्यूनमान2(dcn_bw_log(v->pte_buffer_size_in_requests * v->data_pte_req_width_c / (v->viewport_width[k] / v->no_of_dpp[i][j][k] / 2.0), 2.0), 1.0))) - 1.0) / v->data_pte_req_width_c, 1.0) + 1);
						पूर्ण
						अन्यथा अगर (v->source_scan[k] == dcn_bw_hor) अणु
							v->dpte_bytes_per_row_c = 64.0 * (dcn_bw_उच्चमान2((v->viewport_width[k] / v->no_of_dpp[i][j][k] / 2.0 - 1.0) / v->data_pte_req_width_c, 1.0) + 1);
						पूर्ण
						अन्यथा अणु
							v->dpte_bytes_per_row_c = 64.0 * (dcn_bw_उच्चमान2((v->viewport_height[k] / 2.0 - 1.0) / v->data_pte_req_height_c, 1.0) + 1);
						पूर्ण
					पूर्ण
					अन्यथा अणु
						v->dpte_bytes_per_row_c = 0.0;
					पूर्ण
				पूर्ण
				अन्यथा अणु
					v->dpte_bytes_per_row_c = 0.0;
					v->meta_pte_bytes_per_frame_c = 0.0;
					v->meta_row_bytes_c = 0.0;
				पूर्ण
				v->dpte_bytes_per_row[k] = v->dpte_bytes_per_row_y + v->dpte_bytes_per_row_c;
				v->meta_pte_bytes_per_frame[k] = v->meta_pte_bytes_per_frame_y + v->meta_pte_bytes_per_frame_c;
				v->meta_row_bytes[k] = v->meta_row_bytes_y + v->meta_row_bytes_c;
				v->v_init_y = (v->v_ratio[k] + v->vtaps[k] + 1.0 + v->पूर्णांकerlace_output[k] * 0.5 * v->v_ratio[k]) / 2.0;
				v->prefill_y[k] =dcn_bw_न्यूनमान2(v->v_init_y, 1.0);
				v->max_num_sw_y[k] =dcn_bw_उच्चमान2((v->prefill_y[k] - 1.0) / v->swath_height_yper_state[i][j][k], 1.0) + 1;
				अगर (v->prefill_y[k] > 1.0) अणु
					v->max_partial_sw_y =dcn_bw_mod((v->prefill_y[k] - 2.0), v->swath_height_yper_state[i][j][k]);
				पूर्ण
				अन्यथा अणु
					v->max_partial_sw_y =dcn_bw_mod((v->prefill_y[k] + v->swath_height_yper_state[i][j][k] - 2.0), v->swath_height_yper_state[i][j][k]);
				पूर्ण
				v->max_partial_sw_y =dcn_bw_max2(1.0, v->max_partial_sw_y);
				v->prefetch_lines_y[k] = v->max_num_sw_y[k] * v->swath_height_yper_state[i][j][k] + v->max_partial_sw_y;
				अगर ((v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_64 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_32 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_16)) अणु
					v->v_init_c = (v->v_ratio[k] / 2.0 + v->vtaps[k] + 1.0 + v->पूर्णांकerlace_output[k] * 0.5 * v->v_ratio[k] / 2.0) / 2.0;
					v->prefill_c[k] =dcn_bw_न्यूनमान2(v->v_init_c, 1.0);
					v->max_num_sw_c[k] =dcn_bw_उच्चमान2((v->prefill_c[k] - 1.0) / v->swath_height_cper_state[i][j][k], 1.0) + 1;
					अगर (v->prefill_c[k] > 1.0) अणु
						v->max_partial_sw_c =dcn_bw_mod((v->prefill_c[k] - 2.0), v->swath_height_cper_state[i][j][k]);
					पूर्ण
					अन्यथा अणु
						v->max_partial_sw_c =dcn_bw_mod((v->prefill_c[k] + v->swath_height_cper_state[i][j][k] - 2.0), v->swath_height_cper_state[i][j][k]);
					पूर्ण
					v->max_partial_sw_c =dcn_bw_max2(1.0, v->max_partial_sw_c);
					v->prefetch_lines_c[k] = v->max_num_sw_c[k] * v->swath_height_cper_state[i][j][k] + v->max_partial_sw_c;
				पूर्ण
				अन्यथा अणु
					v->prefetch_lines_c[k] = 0.0;
				पूर्ण
				v->dst_x_after_scaler = 90.0 * v->pixel_घड़ी[k] / (v->required_dispclk[i][j] / (j + 1)) + 42.0 * v->pixel_घड़ी[k] / v->required_dispclk[i][j];
				अगर (v->no_of_dpp[i][j][k] > 1.0) अणु
					v->dst_x_after_scaler = v->dst_x_after_scaler + v->scaler_rec_out_width[k] / 2.0;
				पूर्ण
				अगर (v->output_क्रमmat[k] == dcn_bw_420) अणु
					v->dst_y_after_scaler = 1.0;
				पूर्ण
				अन्यथा अणु
					v->dst_y_after_scaler = 0.0;
				पूर्ण
				v->समय_calc = 24.0 / v->projected_dcfclk_deep_sleep;
				v->v_update_offset[k][j] = dcn_bw_उच्चमान2(v->htotal[k] / 4.0, 1.0);
				v->total_repeater_delay = v->max_पूर्णांकer_dcn_tile_repeaters * (2.0 / (v->required_dispclk[i][j] / (j + 1)) + 3.0 / v->required_dispclk[i][j]);
				v->v_update_width[k][j] = (14.0 / v->projected_dcfclk_deep_sleep + 12.0 / (v->required_dispclk[i][j] / (j + 1)) + v->total_repeater_delay) * v->pixel_घड़ी[k];
				v->v_पढ़ोy_offset[k][j] = dcn_bw_max2(150.0 / (v->required_dispclk[i][j] / (j + 1)), v->total_repeater_delay + 20.0 / v->projected_dcfclk_deep_sleep + 10.0 / (v->required_dispclk[i][j] / (j + 1))) * v->pixel_घड़ी[k];
				v->समय_setup = (v->v_update_offset[k][j] + v->v_update_width[k][j] + v->v_पढ़ोy_offset[k][j]) / v->pixel_घड़ी[k];
				v->extra_latency = v->urgent_round_trip_and_out_of_order_latency_per_state[i] + (v->total_number_of_active_dpp[i][j] * v->pixel_chunk_size_in_kbyte + v->total_number_of_dcc_active_dpp[i][j] * v->meta_chunk_size) * 1024.0 / v->वापस_bw_per_state[i];
				अगर (v->pte_enable == dcn_bw_yes) अणु
					v->extra_latency = v->extra_latency + v->total_number_of_active_dpp[i][j] * v->pte_chunk_size * 1024.0 / v->वापस_bw_per_state[i];
				पूर्ण
				अगर (v->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one == dcn_bw_yes) अणु
					v->maximum_vstartup = v->vtotal[k] - v->vactive[k] - 1.0;
				पूर्ण
				अन्यथा अणु
					v->maximum_vstartup = v->v_sync_plus_back_porch[k] - 1.0;
				पूर्ण

				करो अणु
					v->line_बार_क्रम_prefetch[k] = v->maximum_vstartup - v->urgent_latency / (v->htotal[k] / v->pixel_घड़ी[k]) - (v->समय_calc + v->समय_setup) / (v->htotal[k] / v->pixel_घड़ी[k]) - (v->dst_y_after_scaler + v->dst_x_after_scaler / v->htotal[k]);
					v->line_बार_क्रम_prefetch[k] =dcn_bw_न्यूनमान2(4.0 * (v->line_बार_क्रम_prefetch[k] + 0.125), 1.0) / 4;
					v->prefetch_bw[k] = (v->meta_pte_bytes_per_frame[k] + 2.0 * v->meta_row_bytes[k] + 2.0 * v->dpte_bytes_per_row[k] + v->prefetch_lines_y[k] * v->swath_width_yper_state[i][j][k] *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) + v->prefetch_lines_c[k] * v->swath_width_yper_state[i][j][k] / 2.0 *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0)) / (v->line_बार_क्रम_prefetch[k] * v->htotal[k] / v->pixel_घड़ी[k]);

					अगर (v->pte_enable == dcn_bw_yes && v->dcc_enable[k] == dcn_bw_yes) अणु
						v->समय_क्रम_meta_pte_without_immediate_flip = dcn_bw_max3(
								v->meta_pte_bytes_frame[k] / v->prefetch_bw[k],
								v->extra_latency,
								v->htotal[k] / v->pixel_घड़ी[k] / 4.0);
					पूर्ण अन्यथा अणु
						v->समय_क्रम_meta_pte_without_immediate_flip = v->htotal[k] / v->pixel_घड़ी[k] / 4.0;
					पूर्ण

					अगर (v->pte_enable == dcn_bw_yes || v->dcc_enable[k] == dcn_bw_yes) अणु
						v->समय_क्रम_meta_and_dpte_row_without_immediate_flip = dcn_bw_max3((
								v->meta_row_bytes[k] + v->dpte_bytes_per_row[k]) / v->prefetch_bw[k],
								v->htotal[k] / v->pixel_घड़ी[k] - v->समय_क्रम_meta_pte_without_immediate_flip,
								v->extra_latency);
					पूर्ण अन्यथा अणु
						v->समय_क्रम_meta_and_dpte_row_without_immediate_flip = dcn_bw_max2(
								v->htotal[k] / v->pixel_घड़ी[k] - v->समय_क्रम_meta_pte_without_immediate_flip,
								v->extra_latency - v->समय_क्रम_meta_pte_with_immediate_flip);
					पूर्ण

					v->lines_क्रम_meta_pte_without_immediate_flip[k] =dcn_bw_न्यूनमान2(4.0 * (v->समय_क्रम_meta_pte_without_immediate_flip / (v->htotal[k] / v->pixel_घड़ी[k]) + 0.125), 1.0) / 4;
					v->lines_क्रम_meta_and_dpte_row_without_immediate_flip[k] =dcn_bw_न्यूनमान2(4.0 * (v->समय_क्रम_meta_and_dpte_row_without_immediate_flip / (v->htotal[k] / v->pixel_घड़ी[k]) + 0.125), 1.0) / 4;
					v->maximum_vstartup = v->maximum_vstartup - 1;

					अगर (v->lines_क्रम_meta_pte_without_immediate_flip[k] < 32.0 && v->lines_क्रम_meta_and_dpte_row_without_immediate_flip[k] < 16.0)
						अवरोध;

				पूर्ण जबतक(1);
			पूर्ण
			v->bw_available_क्रम_immediate_flip = v->वापस_bw_per_state[i];
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				v->bw_available_क्रम_immediate_flip = v->bw_available_क्रम_immediate_flip -dcn_bw_max2(v->पढ़ो_bandwidth[k], v->prefetch_bw[k]);
			पूर्ण
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				v->total_immediate_flip_bytes[k] = 0.0;
				अगर ((v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10)) अणु
					v->total_immediate_flip_bytes[k] = v->total_immediate_flip_bytes[k] + v->meta_pte_bytes_per_frame[k] + v->meta_row_bytes[k] + v->dpte_bytes_per_row[k];
				पूर्ण
			पूर्ण
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->pte_enable == dcn_bw_yes && v->dcc_enable[k] == dcn_bw_yes) अणु
					v->समय_क्रम_meta_pte_with_immediate_flip =dcn_bw_max5(v->meta_pte_bytes_per_frame[k] / v->prefetch_bw[k], v->meta_pte_bytes_per_frame[k] * v->total_immediate_flip_bytes[k] / (v->bw_available_क्रम_immediate_flip * (v->meta_pte_bytes_per_frame[k] + v->meta_row_bytes[k] + v->dpte_bytes_per_row[k])), v->extra_latency, v->urgent_latency, v->htotal[k] / v->pixel_घड़ी[k] / 4.0);
				पूर्ण
				अन्यथा अणु
					v->समय_क्रम_meta_pte_with_immediate_flip = v->htotal[k] / v->pixel_घड़ी[k] / 4.0;
				पूर्ण
				अगर (v->pte_enable == dcn_bw_yes || v->dcc_enable[k] == dcn_bw_yes) अणु
					v->समय_क्रम_meta_and_dpte_row_with_immediate_flip =dcn_bw_max5((v->meta_row_bytes[k] + v->dpte_bytes_per_row[k]) / v->prefetch_bw[k], (v->meta_row_bytes[k] + v->dpte_bytes_per_row[k]) * v->total_immediate_flip_bytes[k] / (v->bw_available_क्रम_immediate_flip * (v->meta_pte_bytes_per_frame[k] + v->meta_row_bytes[k] + v->dpte_bytes_per_row[k])), v->htotal[k] / v->pixel_घड़ी[k] - v->समय_क्रम_meta_pte_with_immediate_flip, v->extra_latency, 2.0 * v->urgent_latency);
				पूर्ण
				अन्यथा अणु
					v->समय_क्रम_meta_and_dpte_row_with_immediate_flip =dcn_bw_max2(v->htotal[k] / v->pixel_घड़ी[k] - v->समय_क्रम_meta_pte_with_immediate_flip, v->extra_latency - v->समय_क्रम_meta_pte_with_immediate_flip);
				पूर्ण
				v->lines_क्रम_meta_pte_with_immediate_flip[k] =dcn_bw_न्यूनमान2(4.0 * (v->समय_क्रम_meta_pte_with_immediate_flip / (v->htotal[k] / v->pixel_घड़ी[k]) + 0.125), 1.0) / 4;
				v->lines_क्रम_meta_and_dpte_row_with_immediate_flip[k] =dcn_bw_न्यूनमान2(4.0 * (v->समय_क्रम_meta_and_dpte_row_with_immediate_flip / (v->htotal[k] / v->pixel_घड़ी[k]) + 0.125), 1.0) / 4;
				v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip = v->line_बार_क्रम_prefetch[k] - v->lines_क्रम_meta_pte_with_immediate_flip[k] - v->lines_क्रम_meta_and_dpte_row_with_immediate_flip[k];
				v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip = v->line_बार_क्रम_prefetch[k] - v->lines_क्रम_meta_pte_without_immediate_flip[k] - v->lines_क्रम_meta_and_dpte_row_without_immediate_flip[k];
				अगर (v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip > 0.0) अणु
					v->v_ratio_pre_ywith_immediate_flip[i][j][k] = v->prefetch_lines_y[k] / v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip;
					अगर ((v->swath_height_yper_state[i][j][k] > 4.0)) अणु
						अगर (v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip - (v->prefill_y[k] - 3.0) / 2.0 > 0.0) अणु
							v->v_ratio_pre_ywith_immediate_flip[i][j][k] =dcn_bw_max2(v->v_ratio_pre_ywith_immediate_flip[i][j][k], (v->max_num_sw_y[k] * v->swath_height_yper_state[i][j][k]) / (v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip - (v->prefill_y[k] - 3.0) / 2.0));
						पूर्ण
						अन्यथा अणु
							v->v_ratio_pre_ywith_immediate_flip[i][j][k] = 999999.0;
						पूर्ण
					पूर्ण
					v->v_ratio_pre_cwith_immediate_flip[i][j][k] = v->prefetch_lines_c[k] / v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip;
					अगर ((v->swath_height_cper_state[i][j][k] > 4.0)) अणु
						अगर (v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip - (v->prefill_c[k] - 3.0) / 2.0 > 0.0) अणु
							v->v_ratio_pre_cwith_immediate_flip[i][j][k] =dcn_bw_max2(v->v_ratio_pre_cwith_immediate_flip[i][j][k], (v->max_num_sw_c[k] * v->swath_height_cper_state[i][j][k]) / (v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip - (v->prefill_c[k] - 3.0) / 2.0));
						पूर्ण
						अन्यथा अणु
							v->v_ratio_pre_cwith_immediate_flip[i][j][k] = 999999.0;
						पूर्ण
					पूर्ण
					v->required_prefetch_pixel_data_bw_with_immediate_flip[i][j][k] = v->no_of_dpp[i][j][k] * (v->prefetch_lines_y[k] / v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) + v->prefetch_lines_c[k] / v->line_बार_to_request_prefetch_pixel_data_with_immediate_flip *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 2.0) * v->swath_width_yper_state[i][j][k] / (v->htotal[k] / v->pixel_घड़ी[k]);
				पूर्ण
				अन्यथा अणु
					v->v_ratio_pre_ywith_immediate_flip[i][j][k] = 999999.0;
					v->v_ratio_pre_cwith_immediate_flip[i][j][k] = 999999.0;
					v->required_prefetch_pixel_data_bw_with_immediate_flip[i][j][k] = 999999.0;
				पूर्ण
				अगर (v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip > 0.0) अणु
					v->v_ratio_pre_ywithout_immediate_flip[i][j][k] = v->prefetch_lines_y[k] / v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip;
					अगर ((v->swath_height_yper_state[i][j][k] > 4.0)) अणु
						अगर (v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip - (v->prefill_y[k] - 3.0) / 2.0 > 0.0) अणु
							v->v_ratio_pre_ywithout_immediate_flip[i][j][k] =dcn_bw_max2(v->v_ratio_pre_ywithout_immediate_flip[i][j][k], (v->max_num_sw_y[k] * v->swath_height_yper_state[i][j][k]) / (v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip - (v->prefill_y[k] - 3.0) / 2.0));
						पूर्ण
						अन्यथा अणु
							v->v_ratio_pre_ywithout_immediate_flip[i][j][k] = 999999.0;
						पूर्ण
					पूर्ण
					v->v_ratio_pre_cwithout_immediate_flip[i][j][k] = v->prefetch_lines_c[k] / v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip;
					अगर ((v->swath_height_cper_state[i][j][k] > 4.0)) अणु
						अगर (v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip - (v->prefill_c[k] - 3.0) / 2.0 > 0.0) अणु
							v->v_ratio_pre_cwithout_immediate_flip[i][j][k] =dcn_bw_max2(v->v_ratio_pre_cwithout_immediate_flip[i][j][k], (v->max_num_sw_c[k] * v->swath_height_cper_state[i][j][k]) / (v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip - (v->prefill_c[k] - 3.0) / 2.0));
						पूर्ण
						अन्यथा अणु
							v->v_ratio_pre_cwithout_immediate_flip[i][j][k] = 999999.0;
						पूर्ण
					पूर्ण
					v->required_prefetch_pixel_data_bw_without_immediate_flip[i][j][k] = v->no_of_dpp[i][j][k] * (v->prefetch_lines_y[k] / v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip *dcn_bw_उच्चमान2(v->byte_per_pixel_in_dety[k], 1.0) + v->prefetch_lines_c[k] / v->line_बार_to_request_prefetch_pixel_data_without_immediate_flip *dcn_bw_उच्चमान2(v->byte_per_pixel_in_detc[k], 2.0) / 2.0) * v->swath_width_yper_state[i][j][k] / (v->htotal[k] / v->pixel_घड़ी[k]);
				पूर्ण
				अन्यथा अणु
					v->v_ratio_pre_ywithout_immediate_flip[i][j][k] = 999999.0;
					v->v_ratio_pre_cwithout_immediate_flip[i][j][k] = 999999.0;
					v->required_prefetch_pixel_data_bw_without_immediate_flip[i][j][k] = 999999.0;
				पूर्ण
			पूर्ण
			v->maximum_पढ़ो_bandwidth_with_prefetch_with_immediate_flip = 0.0;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर ((v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10)) अणु
					v->maximum_पढ़ो_bandwidth_with_prefetch_with_immediate_flip = v->maximum_पढ़ो_bandwidth_with_prefetch_with_immediate_flip +dcn_bw_max2(v->पढ़ो_bandwidth[k], v->required_prefetch_pixel_data_bw_with_immediate_flip[i][j][k]) +dcn_bw_max2(v->meta_pte_bytes_per_frame[k] / (v->lines_क्रम_meta_pte_with_immediate_flip[k] * v->htotal[k] / v->pixel_घड़ी[k]), (v->meta_row_bytes[k] + v->dpte_bytes_per_row[k]) / (v->lines_क्रम_meta_and_dpte_row_with_immediate_flip[k] * v->htotal[k] / v->pixel_घड़ी[k]));
				पूर्ण
				अन्यथा अणु
					v->maximum_पढ़ो_bandwidth_with_prefetch_with_immediate_flip = v->maximum_पढ़ो_bandwidth_with_prefetch_with_immediate_flip +dcn_bw_max2(v->पढ़ो_bandwidth[k], v->required_prefetch_pixel_data_bw_without_immediate_flip[i][j][k]);
				पूर्ण
			पूर्ण
			v->maximum_पढ़ो_bandwidth_with_prefetch_without_immediate_flip = 0.0;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				v->maximum_पढ़ो_bandwidth_with_prefetch_without_immediate_flip = v->maximum_पढ़ो_bandwidth_with_prefetch_without_immediate_flip +dcn_bw_max2(v->पढ़ो_bandwidth[k], v->required_prefetch_pixel_data_bw_without_immediate_flip[i][j][k]);
			पूर्ण
			v->prefetch_supported_with_immediate_flip[i][j] = dcn_bw_yes;
			अगर (v->maximum_पढ़ो_bandwidth_with_prefetch_with_immediate_flip > v->वापस_bw_per_state[i]) अणु
				v->prefetch_supported_with_immediate_flip[i][j] = dcn_bw_no;
			पूर्ण
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->line_बार_क्रम_prefetch[k] < 2.0 || v->lines_क्रम_meta_pte_with_immediate_flip[k] >= 8.0 || v->lines_क्रम_meta_and_dpte_row_with_immediate_flip[k] >= 16.0) अणु
					v->prefetch_supported_with_immediate_flip[i][j] = dcn_bw_no;
				पूर्ण
			पूर्ण
			v->prefetch_supported_without_immediate_flip[i][j] = dcn_bw_yes;
			अगर (v->maximum_पढ़ो_bandwidth_with_prefetch_without_immediate_flip > v->वापस_bw_per_state[i]) अणु
				v->prefetch_supported_without_immediate_flip[i][j] = dcn_bw_no;
			पूर्ण
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->line_बार_क्रम_prefetch[k] < 2.0 || v->lines_क्रम_meta_pte_without_immediate_flip[k] >= 8.0 || v->lines_क्रम_meta_and_dpte_row_without_immediate_flip[k] >= 16.0) अणु
					v->prefetch_supported_without_immediate_flip[i][j] = dcn_bw_no;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i <= number_of_states_plus_one; i++) अणु
		क्रम (j = 0; j <= 1; j++) अणु
			v->v_ratio_in_prefetch_supported_with_immediate_flip[i][j] = dcn_bw_yes;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर ((((v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10) && (v->v_ratio_pre_ywith_immediate_flip[i][j][k] > 4.0 || v->v_ratio_pre_cwith_immediate_flip[i][j][k] > 4.0)) || ((v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8 || v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_10) && (v->v_ratio_pre_ywithout_immediate_flip[i][j][k] > 4.0 || v->v_ratio_pre_cwithout_immediate_flip[i][j][k] > 4.0)))) अणु
					v->v_ratio_in_prefetch_supported_with_immediate_flip[i][j] = dcn_bw_no;
				पूर्ण
			पूर्ण
			v->v_ratio_in_prefetch_supported_without_immediate_flip[i][j] = dcn_bw_yes;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर ((v->v_ratio_pre_ywithout_immediate_flip[i][j][k] > 4.0 || v->v_ratio_pre_cwithout_immediate_flip[i][j][k] > 4.0)) अणु
					v->v_ratio_in_prefetch_supported_without_immediate_flip[i][j] = dcn_bw_no;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	/*mode support, voltage state and soc configuration*/

	क्रम (i = number_of_states_plus_one; i >= 0; i--) अणु
		क्रम (j = 0; j <= 1; j++) अणु
			अगर (v->scale_ratio_support == dcn_bw_yes && v->source_क्रमmat_pixel_and_scan_support == dcn_bw_yes && v->viewport_size_support == dcn_bw_yes && v->bandwidth_support[i] == dcn_bw_yes && v->dio_support[i] == dcn_bw_yes && v->urgent_latency_support[i][j] == dcn_bw_yes && v->rob_support[i] == dcn_bw_yes && v->dispclk_dppclk_support[i][j] == dcn_bw_yes && v->total_available_pipes_support[i][j] == dcn_bw_yes && v->total_available_ग_लिखोback_support == dcn_bw_yes && v->ग_लिखोback_latency_support == dcn_bw_yes) अणु
				अगर (v->prefetch_supported_with_immediate_flip[i][j] == dcn_bw_yes && v->v_ratio_in_prefetch_supported_with_immediate_flip[i][j] == dcn_bw_yes) अणु
					v->mode_support_with_immediate_flip[i][j] = dcn_bw_yes;
				पूर्ण
				अन्यथा अणु
					v->mode_support_with_immediate_flip[i][j] = dcn_bw_no;
				पूर्ण
				अगर (v->prefetch_supported_without_immediate_flip[i][j] == dcn_bw_yes && v->v_ratio_in_prefetch_supported_without_immediate_flip[i][j] == dcn_bw_yes) अणु
					v->mode_support_without_immediate_flip[i][j] = dcn_bw_yes;
				पूर्ण
				अन्यथा अणु
					v->mode_support_without_immediate_flip[i][j] = dcn_bw_no;
				पूर्ण
			पूर्ण
			अन्यथा अणु
				v->mode_support_with_immediate_flip[i][j] = dcn_bw_no;
				v->mode_support_without_immediate_flip[i][j] = dcn_bw_no;
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = number_of_states_plus_one; i >= 0; i--) अणु
		अगर ((i == number_of_states_plus_one || v->mode_support_with_immediate_flip[i][1] == dcn_bw_yes || v->mode_support_with_immediate_flip[i][0] == dcn_bw_yes) && i >= v->voltage_override_level) अणु
			v->voltage_level_with_immediate_flip = i;
		पूर्ण
	पूर्ण
	क्रम (i = number_of_states_plus_one; i >= 0; i--) अणु
		अगर ((i == number_of_states_plus_one || v->mode_support_without_immediate_flip[i][1] == dcn_bw_yes || v->mode_support_without_immediate_flip[i][0] == dcn_bw_yes) && i >= v->voltage_override_level) अणु
			v->voltage_level_without_immediate_flip = i;
		पूर्ण
	पूर्ण
	अगर (v->voltage_level_with_immediate_flip == number_of_states_plus_one) अणु
		v->immediate_flip_supported = dcn_bw_no;
		v->voltage_level = v->voltage_level_without_immediate_flip;
	पूर्ण
	अन्यथा अणु
		v->immediate_flip_supported = dcn_bw_yes;
		v->voltage_level = v->voltage_level_with_immediate_flip;
	पूर्ण
	v->dcfclk = v->dcfclk_per_state[v->voltage_level];
	v->fabric_and_dram_bandwidth = v->fabric_and_dram_bandwidth_per_state[v->voltage_level];
	क्रम (j = 0; j <= 1; j++) अणु
		v->required_dispclk_per_ratio[j] = v->required_dispclk[v->voltage_level][j];
		क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
			v->dpp_per_plane_per_ratio[j][k] = v->no_of_dpp[v->voltage_level][j][k];
		पूर्ण
		v->dispclk_dppclk_support_per_ratio[j] = v->dispclk_dppclk_support[v->voltage_level][j];
	पूर्ण
	v->max_phyclk = v->phyclk_per_state[v->voltage_level];
पूर्ण
व्योम display_pipe_configuration(काष्ठा dcn_bw_पूर्णांकernal_vars *v)
अणु
	पूर्णांक j;
	पूर्णांक k;
	/*display pipe configuration*/

	क्रम (j = 0; j <= 1; j++) अणु
		v->total_number_of_active_dpp_per_ratio[j] = 0.0;
		क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
			v->total_number_of_active_dpp_per_ratio[j] = v->total_number_of_active_dpp_per_ratio[j] + v->dpp_per_plane_per_ratio[j][k];
		पूर्ण
	पूर्ण
	अगर ((v->dispclk_dppclk_support_per_ratio[0] == dcn_bw_yes && v->dispclk_dppclk_support_per_ratio[1] == dcn_bw_no) || (v->dispclk_dppclk_support_per_ratio[0] == v->dispclk_dppclk_support_per_ratio[1] && (v->total_number_of_active_dpp_per_ratio[0] < v->total_number_of_active_dpp_per_ratio[1] || (((v->total_number_of_active_dpp_per_ratio[0] == v->total_number_of_active_dpp_per_ratio[1]) && v->required_dispclk_per_ratio[0] <= 0.5 * v->required_dispclk_per_ratio[1]))))) अणु
		v->dispclk_dppclk_ratio = 1;
		v->final_error_message = v->error_message[0];
	पूर्ण
	अन्यथा अणु
		v->dispclk_dppclk_ratio = 2;
		v->final_error_message = v->error_message[1];
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->dpp_per_plane[k] = v->dpp_per_plane_per_ratio[v->dispclk_dppclk_ratio - 1][k];
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64) अणु
			v->byte_per_pix_dety = 8.0;
			v->byte_per_pix_detc = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32) अणु
			v->byte_per_pix_dety = 4.0;
			v->byte_per_pix_detc = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16) अणु
			v->byte_per_pix_dety = 2.0;
			v->byte_per_pix_detc = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8) अणु
			v->byte_per_pix_dety = 1.0;
			v->byte_per_pix_detc = 2.0;
		पूर्ण
		अन्यथा अणु
			v->byte_per_pix_dety = 4.0f / 3.0f;
			v->byte_per_pix_detc = 8.0f / 3.0f;
		पूर्ण
		अगर ((v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16)) अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->पढ़ो256_bytes_block_height_y = 1.0;
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64) अणु
				v->पढ़ो256_bytes_block_height_y = 4.0;
			पूर्ण
			अन्यथा अणु
				v->पढ़ो256_bytes_block_height_y = 8.0;
			पूर्ण
			v->पढ़ो256_bytes_block_width_y = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pix_dety, 1.0) / v->पढ़ो256_bytes_block_height_y;
			v->पढ़ो256_bytes_block_height_c = 0.0;
			v->पढ़ो256_bytes_block_width_c = 0.0;
		पूर्ण
		अन्यथा अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->पढ़ो256_bytes_block_height_y = 1.0;
				v->पढ़ो256_bytes_block_height_c = 1.0;
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8) अणु
				v->पढ़ो256_bytes_block_height_y = 16.0;
				v->पढ़ो256_bytes_block_height_c = 8.0;
			पूर्ण
			अन्यथा अणु
				v->पढ़ो256_bytes_block_height_y = 8.0;
				v->पढ़ो256_bytes_block_height_c = 8.0;
			पूर्ण
			v->पढ़ो256_bytes_block_width_y = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pix_dety, 1.0) / v->पढ़ो256_bytes_block_height_y;
			v->पढ़ो256_bytes_block_width_c = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pix_detc, 2.0) / v->पढ़ो256_bytes_block_height_c;
		पूर्ण
		अगर (v->source_scan[k] == dcn_bw_hor) अणु
			v->maximum_swath_height_y = v->पढ़ो256_bytes_block_height_y;
			v->maximum_swath_height_c = v->पढ़ो256_bytes_block_height_c;
		पूर्ण
		अन्यथा अणु
			v->maximum_swath_height_y = v->पढ़ो256_bytes_block_width_y;
			v->maximum_swath_height_c = v->पढ़ो256_bytes_block_width_c;
		पूर्ण
		अगर ((v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16)) अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear || (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 && (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_var_s || v->source_surface_mode[k] == dcn_bw_sw_var_s_x) && v->source_scan[k] == dcn_bw_hor)) अणु
				v->minimum_swath_height_y = v->maximum_swath_height_y;
			पूर्ण
			अन्यथा अणु
				v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
			पूर्ण
			v->minimum_swath_height_c = v->maximum_swath_height_c;
		पूर्ण
		अन्यथा अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->minimum_swath_height_y = v->maximum_swath_height_y;
				v->minimum_swath_height_c = v->maximum_swath_height_c;
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8 && v->source_scan[k] == dcn_bw_hor) अणु
				v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
				अगर (v->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes) अणु
					v->minimum_swath_height_c = v->maximum_swath_height_c;
				पूर्ण
				अन्यथा अणु
					v->minimum_swath_height_c = v->maximum_swath_height_c / 2.0;
				पूर्ण
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_10 && v->source_scan[k] == dcn_bw_hor) अणु
				v->minimum_swath_height_c = v->maximum_swath_height_c / 2.0;
				अगर (v->bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed == dcn_bw_yes) अणु
					v->minimum_swath_height_y = v->maximum_swath_height_y;
				पूर्ण
				अन्यथा अणु
					v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
				पूर्ण
			पूर्ण
			अन्यथा अणु
				v->minimum_swath_height_y = v->maximum_swath_height_y;
				v->minimum_swath_height_c = v->maximum_swath_height_c;
			पूर्ण
		पूर्ण
		अगर (v->source_scan[k] == dcn_bw_hor) अणु
			v->swath_width = v->viewport_width[k] / v->dpp_per_plane[k];
		पूर्ण
		अन्यथा अणु
			v->swath_width = v->viewport_height[k] / v->dpp_per_plane[k];
		पूर्ण
		v->swath_width_granularity_y = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pix_dety, 1.0) / v->maximum_swath_height_y;
		v->rounded_up_max_swath_size_bytes_y = (dcn_bw_उच्चमान2(v->swath_width - 1.0, v->swath_width_granularity_y) + v->swath_width_granularity_y) * v->byte_per_pix_dety * v->maximum_swath_height_y;
		अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_10) अणु
			v->rounded_up_max_swath_size_bytes_y =dcn_bw_उच्चमान2(v->rounded_up_max_swath_size_bytes_y, 256.0) + 256;
		पूर्ण
		अगर (v->maximum_swath_height_c > 0.0) अणु
			v->swath_width_granularity_c = 256.0 /dcn_bw_उच्चमान2(v->byte_per_pix_detc, 2.0) / v->maximum_swath_height_c;
		पूर्ण
		v->rounded_up_max_swath_size_bytes_c = (dcn_bw_उच्चमान2(v->swath_width / 2.0 - 1.0, v->swath_width_granularity_c) + v->swath_width_granularity_c) * v->byte_per_pix_detc * v->maximum_swath_height_c;
		अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_10) अणु
			v->rounded_up_max_swath_size_bytes_c =dcn_bw_उच्चमान2(v->rounded_up_max_swath_size_bytes_c, 256.0) + 256;
		पूर्ण
		अगर (v->rounded_up_max_swath_size_bytes_y + v->rounded_up_max_swath_size_bytes_c <= v->det_buffer_size_in_kbyte * 1024.0 / 2.0) अणु
			v->swath_height_y[k] = v->maximum_swath_height_y;
			v->swath_height_c[k] = v->maximum_swath_height_c;
		पूर्ण
		अन्यथा अणु
			v->swath_height_y[k] = v->minimum_swath_height_y;
			v->swath_height_c[k] = v->minimum_swath_height_c;
		पूर्ण
		अगर (v->swath_height_c[k] == 0.0) अणु
			v->det_buffer_size_y[k] = v->det_buffer_size_in_kbyte * 1024.0;
			v->det_buffer_size_c[k] = 0.0;
		पूर्ण
		अन्यथा अगर (v->swath_height_y[k] <= v->swath_height_c[k]) अणु
			v->det_buffer_size_y[k] = v->det_buffer_size_in_kbyte * 1024.0 / 2.0;
			v->det_buffer_size_c[k] = v->det_buffer_size_in_kbyte * 1024.0 / 2.0;
		पूर्ण
		अन्यथा अणु
			v->det_buffer_size_y[k] = v->det_buffer_size_in_kbyte * 1024.0 * 2.0 / 3.0;
			v->det_buffer_size_c[k] = v->det_buffer_size_in_kbyte * 1024.0 / 3.0;
		पूर्ण
	पूर्ण
पूर्ण
व्योम dispclkdppclkdcfclk_deep_sleep_prefetch_parameters_watermarks_and_perक्रमmance_calculation(काष्ठा dcn_bw_पूर्णांकernal_vars *v)
अणु
	पूर्णांक k;
	/*dispclk and dppclk calculation*/

	v->dispclk_with_ramping = 0.0;
	v->dispclk_without_ramping = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->h_ratio[k] > 1.0) अणु
			v->pscl_throughput[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput * v->h_ratio[k] /dcn_bw_उच्चमान2(v->htaps[k] / 6.0, 1.0));
		पूर्ण
		अन्यथा अणु
			v->pscl_throughput[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput);
		पूर्ण
		v->dppclk_using_single_dpp_luma = v->pixel_घड़ी[k] *dcn_bw_max3(v->vtaps[k] / 6.0 *dcn_bw_min2(1.0, v->h_ratio[k]), v->h_ratio[k] * v->v_ratio[k] / v->pscl_throughput[k], 1.0);
		अगर ((v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10)) अणु
			v->pscl_throughput_chroma[k] = 0.0;
			v->dppclk_using_single_dpp = v->dppclk_using_single_dpp_luma;
		पूर्ण
		अन्यथा अणु
			अगर (v->h_ratio[k] > 1.0) अणु
				v->pscl_throughput_chroma[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput * v->h_ratio[k] / 2.0 /dcn_bw_उच्चमान2(v->hta_pschroma[k] / 6.0, 1.0));
			पूर्ण
			अन्यथा अणु
				v->pscl_throughput_chroma[k] =dcn_bw_min2(v->max_dchub_topscl_throughput, v->max_pscl_tolb_throughput);
			पूर्ण
			v->dppclk_using_single_dpp_chroma = v->pixel_घड़ी[k] *dcn_bw_max3(v->vta_pschroma[k] / 6.0 *dcn_bw_min2(1.0, v->h_ratio[k] / 2.0), v->h_ratio[k] * v->v_ratio[k] / 4.0 / v->pscl_throughput_chroma[k], 1.0);
			v->dppclk_using_single_dpp =dcn_bw_max2(v->dppclk_using_single_dpp_luma, v->dppclk_using_single_dpp_chroma);
		पूर्ण
		अगर (v->odm_capable == dcn_bw_yes) अणु
			v->dispclk_with_ramping =dcn_bw_max2(v->dispclk_with_ramping,dcn_bw_max2(v->dppclk_using_single_dpp / v->dpp_per_plane[k] * v->dispclk_dppclk_ratio, v->pixel_घड़ी[k] / v->dpp_per_plane[k]) * (1.0 + v->करोwnspपढ़ोing / 100.0) * (1.0 + v->dispclk_ramping_margin / 100.0));
			v->dispclk_without_ramping =dcn_bw_max2(v->dispclk_without_ramping,dcn_bw_max2(v->dppclk_using_single_dpp / v->dpp_per_plane[k] * v->dispclk_dppclk_ratio, v->pixel_घड़ी[k] / v->dpp_per_plane[k]) * (1.0 + v->करोwnspपढ़ोing / 100.0));
		पूर्ण
		अन्यथा अणु
			v->dispclk_with_ramping =dcn_bw_max2(v->dispclk_with_ramping,dcn_bw_max2(v->dppclk_using_single_dpp / v->dpp_per_plane[k] * v->dispclk_dppclk_ratio, v->pixel_घड़ी[k]) * (1.0 + v->करोwnspपढ़ोing / 100.0) * (1.0 + v->dispclk_ramping_margin / 100.0));
			v->dispclk_without_ramping =dcn_bw_max2(v->dispclk_without_ramping,dcn_bw_max2(v->dppclk_using_single_dpp / v->dpp_per_plane[k] * v->dispclk_dppclk_ratio, v->pixel_घड़ी[k]) * (1.0 + v->करोwnspपढ़ोing / 100.0));
		पूर्ण
	पूर्ण
	अगर (v->dispclk_without_ramping > v->max_dispclk[number_of_states]) अणु
		v->dispclk = v->dispclk_without_ramping;
	पूर्ण
	अन्यथा अगर (v->dispclk_with_ramping > v->max_dispclk[number_of_states]) अणु
		v->dispclk = v->max_dispclk[number_of_states];
	पूर्ण
	अन्यथा अणु
		v->dispclk = v->dispclk_with_ramping;
	पूर्ण
	v->dppclk = v->dispclk / v->dispclk_dppclk_ratio;
	/*urgent watermark*/

	v->वापस_bandwidth_to_dcn =dcn_bw_min2(v->वापस_bus_width * v->dcfclk, v->fabric_and_dram_bandwidth * 1000.0 * v->percent_of_ideal_drambw_received_after_urg_latency / 100.0);
	v->dcc_enabled_any_plane = dcn_bw_no;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
			v->dcc_enabled_any_plane = dcn_bw_yes;
		पूर्ण
	पूर्ण
	v->वापस_bw = v->वापस_bandwidth_to_dcn;
	अगर (v->dcc_enabled_any_plane == dcn_bw_yes && v->वापस_bandwidth_to_dcn > v->dcfclk * v->वापस_bus_width / 4.0) अणु
		v->वापस_bw =dcn_bw_min2(v->वापस_bw, v->वापस_bandwidth_to_dcn * 4.0 * (1.0 - v->urgent_latency / ((v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 / (v->वापस_bandwidth_to_dcn - v->dcfclk * v->वापस_bus_width / 4.0) + v->urgent_latency)));
	पूर्ण
	v->critical_compression = 2.0 * v->वापस_bus_width * v->dcfclk * v->urgent_latency / (v->वापस_bandwidth_to_dcn * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0);
	अगर (v->dcc_enabled_any_plane == dcn_bw_yes && v->critical_compression > 1.0 && v->critical_compression < 4.0) अणु
		v->वापस_bw =dcn_bw_min2(v->वापस_bw, dcn_bw_घात(4.0 * v->वापस_bandwidth_to_dcn * (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 * v->वापस_bus_width * v->dcfclk * v->urgent_latency / (v->वापस_bandwidth_to_dcn * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0), 2));
	पूर्ण
	v->वापस_bandwidth_to_dcn =dcn_bw_min2(v->वापस_bus_width * v->dcfclk, v->fabric_and_dram_bandwidth * 1000.0);
	अगर (v->dcc_enabled_any_plane == dcn_bw_yes && v->वापस_bandwidth_to_dcn > v->dcfclk * v->वापस_bus_width / 4.0) अणु
		v->वापस_bw =dcn_bw_min2(v->वापस_bw, v->वापस_bandwidth_to_dcn * 4.0 * (1.0 - v->urgent_latency / ((v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 / (v->वापस_bandwidth_to_dcn - v->dcfclk * v->वापस_bus_width / 4.0) + v->urgent_latency)));
	पूर्ण
	v->critical_compression = 2.0 * v->वापस_bus_width * v->dcfclk * v->urgent_latency / (v->वापस_bandwidth_to_dcn * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0);
	अगर (v->dcc_enabled_any_plane == dcn_bw_yes && v->critical_compression > 1.0 && v->critical_compression < 4.0) अणु
		v->वापस_bw =dcn_bw_min2(v->वापस_bw, dcn_bw_घात(4.0 * v->वापस_bandwidth_to_dcn * (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0 * v->वापस_bus_width * v->dcfclk * v->urgent_latency / (v->वापस_bandwidth_to_dcn * v->urgent_latency + (v->rob_buffer_size_in_kbyte - v->pixel_chunk_size_in_kbyte) * 1024.0), 2));
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->source_scan[k] == dcn_bw_hor) अणु
			v->swath_width_y[k] = v->viewport_width[k] / v->dpp_per_plane[k];
		पूर्ण
		अन्यथा अणु
			v->swath_width_y[k] = v->viewport_height[k] / v->dpp_per_plane[k];
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64) अणु
			v->byte_per_pixel_dety[k] = 8.0;
			v->byte_per_pixel_detc[k] = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32) अणु
			v->byte_per_pixel_dety[k] = 4.0;
			v->byte_per_pixel_detc[k] = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16) अणु
			v->byte_per_pixel_dety[k] = 2.0;
			v->byte_per_pixel_detc[k] = 0.0;
		पूर्ण
		अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8) अणु
			v->byte_per_pixel_dety[k] = 1.0;
			v->byte_per_pixel_detc[k] = 2.0;
		पूर्ण
		अन्यथा अणु
			v->byte_per_pixel_dety[k] = 4.0f / 3.0f;
			v->byte_per_pixel_detc[k] = 8.0f / 3.0f;
		पूर्ण
	पूर्ण
	v->total_data_पढ़ो_bandwidth = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->पढ़ो_bandwidth_plane_luma[k] = v->swath_width_y[k] * v->dpp_per_plane[k] *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / (v->htotal[k] / v->pixel_घड़ी[k]) * v->v_ratio[k];
		v->पढ़ो_bandwidth_plane_chroma[k] = v->swath_width_y[k] / 2.0 * v->dpp_per_plane[k] *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / (v->htotal[k] / v->pixel_घड़ी[k]) * v->v_ratio[k] / 2.0;
		v->total_data_पढ़ो_bandwidth = v->total_data_पढ़ो_bandwidth + v->पढ़ो_bandwidth_plane_luma[k] + v->पढ़ो_bandwidth_plane_chroma[k];
	पूर्ण
	v->total_active_dpp = 0.0;
	v->total_dcc_active_dpp = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->total_active_dpp = v->total_active_dpp + v->dpp_per_plane[k];
		अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
			v->total_dcc_active_dpp = v->total_dcc_active_dpp + v->dpp_per_plane[k];
		पूर्ण
	पूर्ण
	v->urgent_round_trip_and_out_of_order_latency = (v->round_trip_ping_latency_cycles + 32.0) / v->dcfclk + v->urgent_out_of_order_वापस_per_channel * v->number_of_channels / v->वापस_bw;
	v->last_pixel_of_line_extra_watermark = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->v_ratio[k] <= 1.0) अणु
			v->display_pipe_line_delivery_समय_luma[k] = v->swath_width_y[k] * v->dpp_per_plane[k] / v->h_ratio[k] / v->pixel_घड़ी[k];
		पूर्ण
		अन्यथा अणु
			v->display_pipe_line_delivery_समय_luma[k] = v->swath_width_y[k] / v->pscl_throughput[k] / v->dppclk;
		पूर्ण
		v->data_fabric_line_delivery_समय_luma = v->swath_width_y[k] * v->swath_height_y[k] *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / (v->वापस_bw * v->पढ़ो_bandwidth_plane_luma[k] / v->dpp_per_plane[k] / v->total_data_पढ़ो_bandwidth);
		v->last_pixel_of_line_extra_watermark =dcn_bw_max2(v->last_pixel_of_line_extra_watermark, v->data_fabric_line_delivery_समय_luma - v->display_pipe_line_delivery_समय_luma[k]);
		अगर (v->byte_per_pixel_detc[k] == 0.0) अणु
			v->display_pipe_line_delivery_समय_chroma[k] = 0.0;
		पूर्ण
		अन्यथा अणु
			अगर (v->v_ratio[k] / 2.0 <= 1.0) अणु
				v->display_pipe_line_delivery_समय_chroma[k] = v->swath_width_y[k] / 2.0 * v->dpp_per_plane[k] / (v->h_ratio[k] / 2.0) / v->pixel_घड़ी[k];
			पूर्ण
			अन्यथा अणु
				v->display_pipe_line_delivery_समय_chroma[k] = v->swath_width_y[k] / 2.0 / v->pscl_throughput_chroma[k] / v->dppclk;
			पूर्ण
			v->data_fabric_line_delivery_समय_chroma = v->swath_width_y[k] / 2.0 * v->swath_height_c[k] *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / (v->वापस_bw * v->पढ़ो_bandwidth_plane_chroma[k] / v->dpp_per_plane[k] / v->total_data_पढ़ो_bandwidth);
			v->last_pixel_of_line_extra_watermark =dcn_bw_max2(v->last_pixel_of_line_extra_watermark, v->data_fabric_line_delivery_समय_chroma - v->display_pipe_line_delivery_समय_chroma[k]);
		पूर्ण
	पूर्ण
	v->urgent_extra_latency = v->urgent_round_trip_and_out_of_order_latency + (v->total_active_dpp * v->pixel_chunk_size_in_kbyte + v->total_dcc_active_dpp * v->meta_chunk_size) * 1024.0 / v->वापस_bw;
	अगर (v->pte_enable == dcn_bw_yes) अणु
		v->urgent_extra_latency = v->urgent_extra_latency + v->total_active_dpp * v->pte_chunk_size * 1024.0 / v->वापस_bw;
	पूर्ण
	v->urgent_watermark = v->urgent_latency + v->last_pixel_of_line_extra_watermark + v->urgent_extra_latency;
	v->ptemeta_urgent_watermark = v->urgent_watermark + 2.0 * v->urgent_latency;
	/*nb p-state/dram घड़ी change watermark*/

	v->dram_घड़ी_change_watermark = v->dram_घड़ी_change_latency + v->urgent_watermark;
	v->total_active_ग_लिखोback = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->output[k] == dcn_bw_ग_लिखोback) अणु
			v->total_active_ग_लिखोback = v->total_active_ग_लिखोback + 1.0;
		पूर्ण
	पूर्ण
	अगर (v->total_active_ग_लिखोback <= 1.0) अणु
		v->ग_लिखोback_dram_घड़ी_change_watermark = v->dram_घड़ी_change_latency + v->ग_लिखो_back_latency;
	पूर्ण
	अन्यथा अणु
		v->ग_लिखोback_dram_घड़ी_change_watermark = v->dram_घड़ी_change_latency + v->ग_लिखो_back_latency + v->ग_लिखोback_chunk_size * 1024.0 / 32.0 / v->socclk;
	पूर्ण
	/*stutter efficiency*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->lines_in_dety[k] = v->det_buffer_size_y[k] / v->byte_per_pixel_dety[k] / v->swath_width_y[k];
		v->lines_in_dety_rounded_करोwn_to_swath[k] =dcn_bw_न्यूनमान2(v->lines_in_dety[k], v->swath_height_y[k]);
		v->full_det_buffering_समय_y[k] = v->lines_in_dety_rounded_करोwn_to_swath[k] * (v->htotal[k] / v->pixel_घड़ी[k]) / v->v_ratio[k];
		अगर (v->byte_per_pixel_detc[k] > 0.0) अणु
			v->lines_in_detc[k] = v->det_buffer_size_c[k] / v->byte_per_pixel_detc[k] / (v->swath_width_y[k] / 2.0);
			v->lines_in_detc_rounded_करोwn_to_swath[k] =dcn_bw_न्यूनमान2(v->lines_in_detc[k], v->swath_height_c[k]);
			v->full_det_buffering_समय_c[k] = v->lines_in_detc_rounded_करोwn_to_swath[k] * (v->htotal[k] / v->pixel_घड़ी[k]) / (v->v_ratio[k] / 2.0);
		पूर्ण
		अन्यथा अणु
			v->lines_in_detc[k] = 0.0;
			v->lines_in_detc_rounded_करोwn_to_swath[k] = 0.0;
			v->full_det_buffering_समय_c[k] = 999999.0;
		पूर्ण
	पूर्ण
	v->min_full_det_buffering_समय = 999999.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->full_det_buffering_समय_y[k] < v->min_full_det_buffering_समय) अणु
			v->min_full_det_buffering_समय = v->full_det_buffering_समय_y[k];
			v->frame_समय_क्रम_min_full_det_buffering_समय = v->vtotal[k] * v->htotal[k] / v->pixel_घड़ी[k];
		पूर्ण
		अगर (v->full_det_buffering_समय_c[k] < v->min_full_det_buffering_समय) अणु
			v->min_full_det_buffering_समय = v->full_det_buffering_समय_c[k];
			v->frame_समय_क्रम_min_full_det_buffering_समय = v->vtotal[k] * v->htotal[k] / v->pixel_घड़ी[k];
		पूर्ण
	पूर्ण
	v->average_पढ़ो_bandwidth_gbyte_per_second = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
			v->average_पढ़ो_bandwidth_gbyte_per_second = v->average_पढ़ो_bandwidth_gbyte_per_second + v->पढ़ो_bandwidth_plane_luma[k] / v->dcc_rate[k] / 1000.0 + v->पढ़ो_bandwidth_plane_chroma[k] / v->dcc_rate[k] / 1000.0;
		पूर्ण
		अन्यथा अणु
			v->average_पढ़ो_bandwidth_gbyte_per_second = v->average_पढ़ो_bandwidth_gbyte_per_second + v->पढ़ो_bandwidth_plane_luma[k] / 1000.0 + v->पढ़ो_bandwidth_plane_chroma[k] / 1000.0;
		पूर्ण
		अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
			v->average_पढ़ो_bandwidth_gbyte_per_second = v->average_पढ़ो_bandwidth_gbyte_per_second + v->पढ़ो_bandwidth_plane_luma[k] / 1000.0 / 256.0 + v->पढ़ो_bandwidth_plane_chroma[k] / 1000.0 / 256.0;
		पूर्ण
		अगर (v->pte_enable == dcn_bw_yes) अणु
			v->average_पढ़ो_bandwidth_gbyte_per_second = v->average_पढ़ो_bandwidth_gbyte_per_second + v->पढ़ो_bandwidth_plane_luma[k] / 1000.0 / 512.0 + v->पढ़ो_bandwidth_plane_chroma[k] / 1000.0 / 512.0;
		पूर्ण
	पूर्ण
	v->part_of_burst_that_fits_in_rob =dcn_bw_min2(v->min_full_det_buffering_समय * v->total_data_पढ़ो_bandwidth, v->rob_buffer_size_in_kbyte * 1024.0 * v->total_data_पढ़ो_bandwidth / (v->average_पढ़ो_bandwidth_gbyte_per_second * 1000.0));
	v->stutter_burst_समय = v->part_of_burst_that_fits_in_rob * (v->average_पढ़ो_bandwidth_gbyte_per_second * 1000.0) / v->total_data_पढ़ो_bandwidth / v->वापस_bw + (v->min_full_det_buffering_समय * v->total_data_पढ़ो_bandwidth - v->part_of_burst_that_fits_in_rob) / (v->dcfclk * 64.0);
	अगर (v->total_active_ग_लिखोback == 0.0) अणु
		v->stutter_efficiency_not_including_vblank = (1.0 - (v->sr_निकास_समय + v->stutter_burst_समय) / v->min_full_det_buffering_समय) * 100.0;
	पूर्ण
	अन्यथा अणु
		v->stutter_efficiency_not_including_vblank = 0.0;
	पूर्ण
	v->smallest_vblank = 999999.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->synchronized_vblank == dcn_bw_yes || v->number_of_active_planes == 1) अणु
			v->v_blank_समय = (v->vtotal[k] - v->vactive[k]) * v->htotal[k] / v->pixel_घड़ी[k];
		पूर्ण
		अन्यथा अणु
			v->v_blank_समय = 0.0;
		पूर्ण
		v->smallest_vblank =dcn_bw_min2(v->smallest_vblank, v->v_blank_समय);
	पूर्ण
	v->stutter_efficiency = (v->stutter_efficiency_not_including_vblank / 100.0 * (v->frame_समय_क्रम_min_full_det_buffering_समय - v->smallest_vblank) + v->smallest_vblank) / v->frame_समय_क्रम_min_full_det_buffering_समय * 100.0;
	/*dcfclk deep sleep*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->byte_per_pixel_detc[k] > 0.0) अणु
			v->dcfclk_deep_sleep_per_plane[k] =dcn_bw_max2(1.1 * v->swath_width_y[k] *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / 32.0 / v->display_pipe_line_delivery_समय_luma[k], 1.1 * v->swath_width_y[k] / 2.0 *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / 32.0 / v->display_pipe_line_delivery_समय_chroma[k]);
		पूर्ण
		अन्यथा अणु
			v->dcfclk_deep_sleep_per_plane[k] = 1.1 * v->swath_width_y[k] *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / 64.0 / v->display_pipe_line_delivery_समय_luma[k];
		पूर्ण
		v->dcfclk_deep_sleep_per_plane[k] =dcn_bw_max2(v->dcfclk_deep_sleep_per_plane[k], v->pixel_घड़ी[k] / 16.0);
	पूर्ण
	v->dcf_clk_deep_sleep = 8.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->dcf_clk_deep_sleep =dcn_bw_max2(v->dcf_clk_deep_sleep, v->dcfclk_deep_sleep_per_plane[k]);
	पूर्ण
	/*stutter watermark*/

	v->stutter_निकास_watermark = v->sr_निकास_समय + v->last_pixel_of_line_extra_watermark + v->urgent_extra_latency + 10.0 / v->dcf_clk_deep_sleep;
	v->stutter_enter_plus_निकास_watermark = v->sr_enter_plus_निकास_समय + v->last_pixel_of_line_extra_watermark + v->urgent_extra_latency;
	/*urgent latency supported*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->effective_det_plus_lb_lines_luma =dcn_bw_न्यूनमान2(v->lines_in_dety[k] +dcn_bw_min2(v->lines_in_dety[k] * v->dppclk * v->byte_per_pixel_dety[k] * v->pscl_throughput[k] / (v->वापस_bw / v->dpp_per_plane[k]), v->effective_lb_latency_hiding_source_lines_luma), v->swath_height_y[k]);
		v->urgent_latency_support_us_luma = v->effective_det_plus_lb_lines_luma * (v->htotal[k] / v->pixel_घड़ी[k]) / v->v_ratio[k] - v->effective_det_plus_lb_lines_luma * v->swath_width_y[k] * v->byte_per_pixel_dety[k] / (v->वापस_bw / v->dpp_per_plane[k]);
		अगर (v->byte_per_pixel_detc[k] > 0.0) अणु
			v->effective_det_plus_lb_lines_chroma =dcn_bw_न्यूनमान2(v->lines_in_detc[k] +dcn_bw_min2(v->lines_in_detc[k] * v->dppclk * v->byte_per_pixel_detc[k] * v->pscl_throughput_chroma[k] / (v->वापस_bw / v->dpp_per_plane[k]), v->effective_lb_latency_hiding_source_lines_chroma), v->swath_height_c[k]);
			v->urgent_latency_support_us_chroma = v->effective_det_plus_lb_lines_chroma * (v->htotal[k] / v->pixel_घड़ी[k]) / (v->v_ratio[k] / 2.0) - v->effective_det_plus_lb_lines_chroma * (v->swath_width_y[k] / 2.0) * v->byte_per_pixel_detc[k] / (v->वापस_bw / v->dpp_per_plane[k]);
			v->urgent_latency_support_us[k] =dcn_bw_min2(v->urgent_latency_support_us_luma, v->urgent_latency_support_us_chroma);
		पूर्ण
		अन्यथा अणु
			v->urgent_latency_support_us[k] = v->urgent_latency_support_us_luma;
		पूर्ण
	पूर्ण
	v->min_urgent_latency_support_us = 999999.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->min_urgent_latency_support_us =dcn_bw_min2(v->min_urgent_latency_support_us, v->urgent_latency_support_us[k]);
	पूर्ण
	/*non-urgent latency tolerance*/

	v->non_urgent_latency_tolerance = v->min_urgent_latency_support_us - v->urgent_watermark;
	/*prefetch*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर ((v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_32 || v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_16)) अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->block_height256_bytes_y = 1.0;
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_rgb_sub_64) अणु
				v->block_height256_bytes_y = 4.0;
			पूर्ण
			अन्यथा अणु
				v->block_height256_bytes_y = 8.0;
			पूर्ण
			v->block_height256_bytes_c = 0.0;
		पूर्ण
		अन्यथा अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->block_height256_bytes_y = 1.0;
				v->block_height256_bytes_c = 1.0;
			पूर्ण
			अन्यथा अगर (v->source_pixel_क्रमmat[k] == dcn_bw_yuv420_sub_8) अणु
				v->block_height256_bytes_y = 16.0;
				v->block_height256_bytes_c = 8.0;
			पूर्ण
			अन्यथा अणु
				v->block_height256_bytes_y = 8.0;
				v->block_height256_bytes_c = 8.0;
			पूर्ण
		पूर्ण
		अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
			v->meta_request_width_y = 64.0 * 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / (8.0 * v->block_height256_bytes_y);
			v->meta_surf_width_y =dcn_bw_उच्चमान2(v->swath_width_y[k] - 1.0, v->meta_request_width_y) + v->meta_request_width_y;
			v->meta_surf_height_y =dcn_bw_उच्चमान2(v->viewport_height[k] - 1.0, 8.0 * v->block_height256_bytes_y) + 8.0 * v->block_height256_bytes_y;
			अगर (v->pte_enable == dcn_bw_yes) अणु
				v->meta_pte_bytes_frame_y = (dcn_bw_उच्चमान2((v->meta_surf_width_y * v->meta_surf_height_y *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
			पूर्ण
			अन्यथा अणु
				v->meta_pte_bytes_frame_y = 0.0;
			पूर्ण
			अगर (v->source_scan[k] == dcn_bw_hor) अणु
				v->meta_row_byte_y = v->meta_surf_width_y * 8.0 * v->block_height256_bytes_y *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / 256.0;
			पूर्ण
			अन्यथा अणु
				v->meta_row_byte_y = v->meta_surf_height_y * v->meta_request_width_y *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / 256.0;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			v->meta_pte_bytes_frame_y = 0.0;
			v->meta_row_byte_y = 0.0;
		पूर्ण
		अगर (v->pte_enable == dcn_bw_yes) अणु
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->macro_tile_size_byte_y = 256.0;
				v->macro_tile_height_y = 1.0;
			पूर्ण
			अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d_x) अणु
				v->macro_tile_size_byte_y = 4096.0;
				v->macro_tile_height_y = 4.0 * v->block_height256_bytes_y;
			पूर्ण
			अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_x) अणु
				v->macro_tile_size_byte_y = 64.0 * 1024;
				v->macro_tile_height_y = 16.0 * v->block_height256_bytes_y;
			पूर्ण
			अन्यथा अणु
				v->macro_tile_size_byte_y = 256.0 * 1024;
				v->macro_tile_height_y = 32.0 * v->block_height256_bytes_y;
			पूर्ण
			अगर (v->macro_tile_size_byte_y <= 65536.0) अणु
				v->pixel_pte_req_height_y = v->macro_tile_height_y;
			पूर्ण
			अन्यथा अणु
				v->pixel_pte_req_height_y = 16.0 * v->block_height256_bytes_y;
			पूर्ण
			v->pixel_pte_req_width_y = 4096.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) / v->pixel_pte_req_height_y * 8;
			अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
				v->pixel_pte_bytes_per_row_y = 64.0 * (dcn_bw_उच्चमान2((v->swath_width_y[k] *dcn_bw_min2(128.0, dcn_bw_घात(2.0,dcn_bw_न्यूनमान2(dcn_bw_log(v->pte_buffer_size_in_requests * v->pixel_pte_req_width_y / v->swath_width_y[k], 2.0), 1.0))) - 1.0) / v->pixel_pte_req_width_y, 1.0) + 1);
			पूर्ण
			अन्यथा अगर (v->source_scan[k] == dcn_bw_hor) अणु
				v->pixel_pte_bytes_per_row_y = 64.0 * (dcn_bw_उच्चमान2((v->swath_width_y[k] - 1.0) / v->pixel_pte_req_width_y, 1.0) + 1);
			पूर्ण
			अन्यथा अणु
				v->pixel_pte_bytes_per_row_y = 64.0 * (dcn_bw_उच्चमान2((v->viewport_height[k] - 1.0) / v->pixel_pte_req_height_y, 1.0) + 1);
			पूर्ण
		पूर्ण
		अन्यथा अणु
			v->pixel_pte_bytes_per_row_y = 0.0;
		पूर्ण
		अगर ((v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_64 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_32 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_16)) अणु
			अगर (v->dcc_enable[k] == dcn_bw_yes) अणु
				v->meta_request_width_c = 64.0 * 256.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / (8.0 * v->block_height256_bytes_c);
				v->meta_surf_width_c =dcn_bw_उच्चमान2(v->swath_width_y[k] / 2.0 - 1.0, v->meta_request_width_c) + v->meta_request_width_c;
				v->meta_surf_height_c =dcn_bw_उच्चमान2(v->viewport_height[k] / 2.0 - 1.0, 8.0 * v->block_height256_bytes_c) + 8.0 * v->block_height256_bytes_c;
				अगर (v->pte_enable == dcn_bw_yes) अणु
					v->meta_pte_bytes_frame_c = (dcn_bw_उच्चमान2((v->meta_surf_width_c * v->meta_surf_height_c *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
				पूर्ण
				अन्यथा अणु
					v->meta_pte_bytes_frame_c = 0.0;
				पूर्ण
				अगर (v->source_scan[k] == dcn_bw_hor) अणु
					v->meta_row_byte_c = v->meta_surf_width_c * 8.0 * v->block_height256_bytes_c *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / 256.0;
				पूर्ण
				अन्यथा अणु
					v->meta_row_byte_c = v->meta_surf_height_c * v->meta_request_width_c *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / 256.0;
				पूर्ण
			पूर्ण
			अन्यथा अणु
				v->meta_pte_bytes_frame_c = 0.0;
				v->meta_row_byte_c = 0.0;
			पूर्ण
			अगर (v->pte_enable == dcn_bw_yes) अणु
				अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
					v->macro_tile_size_bytes_c = 256.0;
					v->macro_tile_height_c = 1.0;
				पूर्ण
				अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_4_kb_s || v->source_surface_mode[k] == dcn_bw_sw_4_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d || v->source_surface_mode[k] == dcn_bw_sw_4_kb_d_x) अणु
					v->macro_tile_size_bytes_c = 4096.0;
					v->macro_tile_height_c = 4.0 * v->block_height256_bytes_c;
				पूर्ण
				अन्यथा अगर (v->source_surface_mode[k] == dcn_bw_sw_64_kb_s || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_s_x || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_t || v->source_surface_mode[k] == dcn_bw_sw_64_kb_d_x) अणु
					v->macro_tile_size_bytes_c = 64.0 * 1024;
					v->macro_tile_height_c = 16.0 * v->block_height256_bytes_c;
				पूर्ण
				अन्यथा अणु
					v->macro_tile_size_bytes_c = 256.0 * 1024;
					v->macro_tile_height_c = 32.0 * v->block_height256_bytes_c;
				पूर्ण
				अगर (v->macro_tile_size_bytes_c <= 65536.0) अणु
					v->pixel_pte_req_height_c = v->macro_tile_height_c;
				पूर्ण
				अन्यथा अणु
					v->pixel_pte_req_height_c = 16.0 * v->block_height256_bytes_c;
				पूर्ण
				v->pixel_pte_req_width_c = 4096.0 /dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / v->pixel_pte_req_height_c * 8;
				अगर (v->source_surface_mode[k] == dcn_bw_sw_linear) अणु
					v->pixel_pte_bytes_per_row_c = 64.0 * (dcn_bw_उच्चमान2((v->swath_width_y[k] / 2.0 * dcn_bw_min2(128.0, dcn_bw_घात(2.0,dcn_bw_न्यूनमान2(dcn_bw_log(v->pte_buffer_size_in_requests * v->pixel_pte_req_width_c / (v->swath_width_y[k] / 2.0), 2.0), 1.0))) - 1.0) / v->pixel_pte_req_width_c, 1.0) + 1);
				पूर्ण
				अन्यथा अगर (v->source_scan[k] == dcn_bw_hor) अणु
					v->pixel_pte_bytes_per_row_c = 64.0 * (dcn_bw_उच्चमान2((v->swath_width_y[k] / 2.0 - 1.0) / v->pixel_pte_req_width_c, 1.0) + 1);
				पूर्ण
				अन्यथा अणु
					v->pixel_pte_bytes_per_row_c = 64.0 * (dcn_bw_उच्चमान2((v->viewport_height[k] / 2.0 - 1.0) / v->pixel_pte_req_height_c, 1.0) + 1);
				पूर्ण
			पूर्ण
			अन्यथा अणु
				v->pixel_pte_bytes_per_row_c = 0.0;
			पूर्ण
		पूर्ण
		अन्यथा अणु
			v->pixel_pte_bytes_per_row_c = 0.0;
			v->meta_pte_bytes_frame_c = 0.0;
			v->meta_row_byte_c = 0.0;
		पूर्ण
		v->pixel_pte_bytes_per_row[k] = v->pixel_pte_bytes_per_row_y + v->pixel_pte_bytes_per_row_c;
		v->meta_pte_bytes_frame[k] = v->meta_pte_bytes_frame_y + v->meta_pte_bytes_frame_c;
		v->meta_row_byte[k] = v->meta_row_byte_y + v->meta_row_byte_c;
		v->v_init_pre_fill_y[k] =dcn_bw_न्यूनमान2((v->v_ratio[k] + v->vtaps[k] + 1.0 + v->पूर्णांकerlace_output[k] * 0.5 * v->v_ratio[k]) / 2.0, 1.0);
		v->max_num_swath_y[k] =dcn_bw_उच्चमान2((v->v_init_pre_fill_y[k] - 1.0) / v->swath_height_y[k], 1.0) + 1;
		अगर (v->v_init_pre_fill_y[k] > 1.0) अणु
			v->max_partial_swath_y =dcn_bw_mod((v->v_init_pre_fill_y[k] - 2.0), v->swath_height_y[k]);
		पूर्ण
		अन्यथा अणु
			v->max_partial_swath_y =dcn_bw_mod((v->v_init_pre_fill_y[k] + v->swath_height_y[k] - 2.0), v->swath_height_y[k]);
		पूर्ण
		v->max_partial_swath_y =dcn_bw_max2(1.0, v->max_partial_swath_y);
		v->prefetch_source_lines_y[k] = v->max_num_swath_y[k] * v->swath_height_y[k] + v->max_partial_swath_y;
		अगर ((v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_64 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_32 && v->source_pixel_क्रमmat[k] != dcn_bw_rgb_sub_16)) अणु
			v->v_init_pre_fill_c[k] =dcn_bw_न्यूनमान2((v->v_ratio[k] / 2.0 + v->vtaps[k] + 1.0 + v->पूर्णांकerlace_output[k] * 0.5 * v->v_ratio[k] / 2.0) / 2.0, 1.0);
			v->max_num_swath_c[k] =dcn_bw_उच्चमान2((v->v_init_pre_fill_c[k] - 1.0) / v->swath_height_c[k], 1.0) + 1;
			अगर (v->v_init_pre_fill_c[k] > 1.0) अणु
				v->max_partial_swath_c =dcn_bw_mod((v->v_init_pre_fill_c[k] - 2.0), v->swath_height_c[k]);
			पूर्ण
			अन्यथा अणु
				v->max_partial_swath_c =dcn_bw_mod((v->v_init_pre_fill_c[k] + v->swath_height_c[k] - 2.0), v->swath_height_c[k]);
			पूर्ण
			v->max_partial_swath_c =dcn_bw_max2(1.0, v->max_partial_swath_c);
		पूर्ण
		अन्यथा अणु
			v->max_num_swath_c[k] = 0.0;
			v->max_partial_swath_c = 0.0;
		पूर्ण
		v->prefetch_source_lines_c[k] = v->max_num_swath_c[k] * v->swath_height_c[k] + v->max_partial_swath_c;
	पूर्ण
	v->t_calc = 24.0 / v->dcf_clk_deep_sleep;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one == dcn_bw_yes) अणु
			v->max_vstartup_lines[k] = v->vtotal[k] - v->vactive[k] - 1.0;
		पूर्ण
		अन्यथा अणु
			v->max_vstartup_lines[k] = v->v_sync_plus_back_porch[k] - 1.0;
		पूर्ण
	पूर्ण
	v->next_prefetch_mode = 0.0;
	करो अणु
		v->v_startup_lines = 13.0;
		करो अणु
			v->planes_with_room_to_increase_vstartup_prefetch_bw_less_than_active_bw = dcn_bw_yes;
			v->planes_with_room_to_increase_vstartup_vratio_prefetch_more_than4 = dcn_bw_no;
			v->planes_with_room_to_increase_vstartup_destination_line_बार_क्रम_prefetch_less_than2 = dcn_bw_no;
			v->v_ratio_prefetch_more_than4 = dcn_bw_no;
			v->destination_line_बार_क्रम_prefetch_less_than2 = dcn_bw_no;
			v->prefetch_mode = v->next_prefetch_mode;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				v->dstx_after_scaler = 90.0 * v->pixel_घड़ी[k] / v->dppclk + 42.0 * v->pixel_घड़ी[k] / v->dispclk;
				अगर (v->dpp_per_plane[k] > 1.0) अणु
					v->dstx_after_scaler = v->dstx_after_scaler + v->scaler_rec_out_width[k] / 2.0;
				पूर्ण
				अगर (v->output_क्रमmat[k] == dcn_bw_420) अणु
					v->dsty_after_scaler = 1.0;
				पूर्ण
				अन्यथा अणु
					v->dsty_after_scaler = 0.0;
				पूर्ण
				v->v_update_offset_pix[k] = dcn_bw_उच्चमान2(v->htotal[k] / 4.0, 1.0);
				v->total_repeater_delay_समय = v->max_पूर्णांकer_dcn_tile_repeaters * (2.0 / v->dppclk + 3.0 / v->dispclk);
				v->v_update_width_pix[k] = (14.0 / v->dcf_clk_deep_sleep + 12.0 / v->dppclk + v->total_repeater_delay_समय) * v->pixel_घड़ी[k];
				v->v_पढ़ोy_offset_pix[k] = dcn_bw_max2(150.0 / v->dppclk, v->total_repeater_delay_समय + 20.0 / v->dcf_clk_deep_sleep + 10.0 / v->dppclk) * v->pixel_घड़ी[k];
				v->t_setup = (v->v_update_offset_pix[k] + v->v_update_width_pix[k] + v->v_पढ़ोy_offset_pix[k]) / v->pixel_घड़ी[k];
				v->v_startup[k] =dcn_bw_min2(v->v_startup_lines, v->max_vstartup_lines[k]);
				अगर (v->prefetch_mode == 0.0) अणु
					v->t_रुको =dcn_bw_max3(v->dram_घड़ी_change_latency + v->urgent_latency, v->sr_enter_plus_निकास_समय, v->urgent_latency);
				पूर्ण
				अन्यथा अगर (v->prefetch_mode == 1.0) अणु
					v->t_रुको =dcn_bw_max2(v->sr_enter_plus_निकास_समय, v->urgent_latency);
				पूर्ण
				अन्यथा अणु
					v->t_रुको = v->urgent_latency;
				पूर्ण
				v->destination_lines_क्रम_prefetch[k] =dcn_bw_न्यूनमान2(4.0 * (v->v_startup[k] - v->t_रुको / (v->htotal[k] / v->pixel_घड़ी[k]) - (v->t_calc + v->t_setup) / (v->htotal[k] / v->pixel_घड़ी[k]) - (v->dsty_after_scaler + v->dstx_after_scaler / v->htotal[k]) + 0.125), 1.0) / 4;
				अगर (v->destination_lines_क्रम_prefetch[k] > 0.0) अणु
					v->prefetch_bandwidth[k] = (v->meta_pte_bytes_frame[k] + 2.0 * v->meta_row_byte[k] + 2.0 * v->pixel_pte_bytes_per_row[k] + v->prefetch_source_lines_y[k] * v->swath_width_y[k] *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) + v->prefetch_source_lines_c[k] * v->swath_width_y[k] / 2.0 *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0)) / (v->destination_lines_क्रम_prefetch[k] * v->htotal[k] / v->pixel_घड़ी[k]);
				पूर्ण
				अन्यथा अणु
					v->prefetch_bandwidth[k] = 999999.0;
				पूर्ण
			पूर्ण
			v->bandwidth_available_क्रम_immediate_flip = v->वापस_bw;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				v->bandwidth_available_क्रम_immediate_flip = v->bandwidth_available_क्रम_immediate_flip -dcn_bw_max2(v->पढ़ो_bandwidth_plane_luma[k] + v->पढ़ो_bandwidth_plane_chroma[k], v->prefetch_bandwidth[k]);
			पूर्ण
			v->tot_immediate_flip_bytes = 0.0;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->immediate_flip_supported == dcn_bw_yes && (v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10)) अणु
					v->tot_immediate_flip_bytes = v->tot_immediate_flip_bytes + v->meta_pte_bytes_frame[k] + v->meta_row_byte[k] + v->pixel_pte_bytes_per_row[k];
				पूर्ण
			पूर्ण
			v->max_rd_bandwidth = 0.0;
			क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
				अगर (v->pte_enable == dcn_bw_yes && v->dcc_enable[k] == dcn_bw_yes) अणु
					अगर (v->immediate_flip_supported == dcn_bw_yes && (v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10)) अणु
						v->समय_क्रम_fetching_meta_pte =dcn_bw_max5(v->meta_pte_bytes_frame[k] / v->prefetch_bandwidth[k], v->meta_pte_bytes_frame[k] * v->tot_immediate_flip_bytes / (v->bandwidth_available_क्रम_immediate_flip * (v->meta_pte_bytes_frame[k] + v->meta_row_byte[k] + v->pixel_pte_bytes_per_row[k])), v->urgent_extra_latency, v->urgent_latency, v->htotal[k] / v->pixel_घड़ी[k] / 4.0);
					पूर्ण
					अन्यथा अणु
						v->समय_क्रम_fetching_meta_pte =dcn_bw_max3(v->meta_pte_bytes_frame[k] / v->prefetch_bandwidth[k], v->urgent_extra_latency, v->htotal[k] / v->pixel_घड़ी[k] / 4.0);
					पूर्ण
				पूर्ण
				अन्यथा अणु
					v->समय_क्रम_fetching_meta_pte = v->htotal[k] / v->pixel_घड़ी[k] / 4.0;
				पूर्ण
				v->destination_lines_to_request_vm_inv_blank[k] =dcn_bw_न्यूनमान2(4.0 * (v->समय_क्रम_fetching_meta_pte / (v->htotal[k] / v->pixel_घड़ी[k]) + 0.125), 1.0) / 4;
				अगर ((v->pte_enable == dcn_bw_yes || v->dcc_enable[k] == dcn_bw_yes)) अणु
					अगर (v->immediate_flip_supported == dcn_bw_yes && (v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10)) अणु
						v->समय_क्रम_fetching_row_in_vblank =dcn_bw_max5((v->meta_row_byte[k] + v->pixel_pte_bytes_per_row[k]) / v->prefetch_bandwidth[k], (v->meta_row_byte[k] + v->pixel_pte_bytes_per_row[k]) * v->tot_immediate_flip_bytes / (v->bandwidth_available_क्रम_immediate_flip * (v->meta_pte_bytes_frame[k] + v->meta_row_byte[k] + v->pixel_pte_bytes_per_row[k])), v->urgent_extra_latency, 2.0 * v->urgent_latency, v->htotal[k] / v->pixel_घड़ी[k] - v->समय_क्रम_fetching_meta_pte);
					पूर्ण
					अन्यथा अणु
						v->समय_क्रम_fetching_row_in_vblank =dcn_bw_max3((v->meta_row_byte[k] + v->pixel_pte_bytes_per_row[k]) / v->prefetch_bandwidth[k], v->urgent_extra_latency, v->htotal[k] / v->pixel_घड़ी[k] - v->समय_क्रम_fetching_meta_pte);
					पूर्ण
				पूर्ण
				अन्यथा अणु
					v->समय_क्रम_fetching_row_in_vblank =dcn_bw_max2(v->urgent_extra_latency - v->समय_क्रम_fetching_meta_pte, v->htotal[k] / v->pixel_घड़ी[k] - v->समय_क्रम_fetching_meta_pte);
				पूर्ण
				v->destination_lines_to_request_row_in_vblank[k] =dcn_bw_न्यूनमान2(4.0 * (v->समय_क्रम_fetching_row_in_vblank / (v->htotal[k] / v->pixel_घड़ी[k]) + 0.125), 1.0) / 4;
				v->lines_to_request_prefetch_pixel_data = v->destination_lines_क्रम_prefetch[k] - v->destination_lines_to_request_vm_inv_blank[k] - v->destination_lines_to_request_row_in_vblank[k];
				अगर (v->lines_to_request_prefetch_pixel_data > 0.0) अणु
					v->v_ratio_prefetch_y[k] = v->prefetch_source_lines_y[k] / v->lines_to_request_prefetch_pixel_data;
					अगर ((v->swath_height_y[k] > 4.0)) अणु
						अगर (v->lines_to_request_prefetch_pixel_data > (v->v_init_pre_fill_y[k] - 3.0) / 2.0) अणु
							v->v_ratio_prefetch_y[k] =dcn_bw_max2(v->v_ratio_prefetch_y[k], v->max_num_swath_y[k] * v->swath_height_y[k] / (v->lines_to_request_prefetch_pixel_data - (v->v_init_pre_fill_y[k] - 3.0) / 2.0));
						पूर्ण
						अन्यथा अणु
							v->v_ratio_prefetch_y[k] = 999999.0;
						पूर्ण
					पूर्ण
				पूर्ण
				अन्यथा अणु
					v->v_ratio_prefetch_y[k] = 999999.0;
				पूर्ण
				v->v_ratio_prefetch_y[k] =dcn_bw_max2(v->v_ratio_prefetch_y[k], 1.0);
				अगर (v->lines_to_request_prefetch_pixel_data > 0.0) अणु
					v->v_ratio_prefetch_c[k] = v->prefetch_source_lines_c[k] / v->lines_to_request_prefetch_pixel_data;
					अगर ((v->swath_height_c[k] > 4.0)) अणु
						अगर (v->lines_to_request_prefetch_pixel_data > (v->v_init_pre_fill_c[k] - 3.0) / 2.0) अणु
							v->v_ratio_prefetch_c[k] =dcn_bw_max2(v->v_ratio_prefetch_c[k], v->max_num_swath_c[k] * v->swath_height_c[k] / (v->lines_to_request_prefetch_pixel_data - (v->v_init_pre_fill_c[k] - 3.0) / 2.0));
						पूर्ण
						अन्यथा अणु
							v->v_ratio_prefetch_c[k] = 999999.0;
						पूर्ण
					पूर्ण
				पूर्ण
				अन्यथा अणु
					v->v_ratio_prefetch_c[k] = 999999.0;
				पूर्ण
				v->v_ratio_prefetch_c[k] =dcn_bw_max2(v->v_ratio_prefetch_c[k], 1.0);
				अगर (v->lines_to_request_prefetch_pixel_data > 0.0) अणु
					v->required_prefetch_pix_data_bw = v->dpp_per_plane[k] * (v->prefetch_source_lines_y[k] / v->lines_to_request_prefetch_pixel_data *dcn_bw_उच्चमान2(v->byte_per_pixel_dety[k], 1.0) + v->prefetch_source_lines_c[k] / v->lines_to_request_prefetch_pixel_data *dcn_bw_उच्चमान2(v->byte_per_pixel_detc[k], 2.0) / 2.0) * v->swath_width_y[k] / (v->htotal[k] / v->pixel_घड़ी[k]);
				पूर्ण
				अन्यथा अणु
					v->required_prefetch_pix_data_bw = 999999.0;
				पूर्ण
				v->max_rd_bandwidth = v->max_rd_bandwidth +dcn_bw_max2(v->पढ़ो_bandwidth_plane_luma[k] + v->पढ़ो_bandwidth_plane_chroma[k], v->required_prefetch_pix_data_bw);
				अगर (v->immediate_flip_supported == dcn_bw_yes && (v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_8 && v->source_pixel_क्रमmat[k] != dcn_bw_yuv420_sub_10)) अणु
					v->max_rd_bandwidth = v->max_rd_bandwidth +dcn_bw_max2(v->meta_pte_bytes_frame[k] / (v->destination_lines_to_request_vm_inv_blank[k] * v->htotal[k] / v->pixel_घड़ी[k]), (v->meta_row_byte[k] + v->pixel_pte_bytes_per_row[k]) / (v->destination_lines_to_request_row_in_vblank[k] * v->htotal[k] / v->pixel_घड़ी[k]));
				पूर्ण
				अगर (v->v_ratio_prefetch_y[k] > 4.0 || v->v_ratio_prefetch_c[k] > 4.0) अणु
					v->v_ratio_prefetch_more_than4 = dcn_bw_yes;
				पूर्ण
				अगर (v->destination_lines_क्रम_prefetch[k] < 2.0) अणु
					v->destination_line_बार_क्रम_prefetch_less_than2 = dcn_bw_yes;
				पूर्ण
				अगर (v->max_vstartup_lines[k] > v->v_startup_lines) अणु
					अगर (v->required_prefetch_pix_data_bw > (v->पढ़ो_bandwidth_plane_luma[k] + v->पढ़ो_bandwidth_plane_chroma[k])) अणु
						v->planes_with_room_to_increase_vstartup_prefetch_bw_less_than_active_bw = dcn_bw_no;
					पूर्ण
					अगर (v->v_ratio_prefetch_y[k] > 4.0 || v->v_ratio_prefetch_c[k] > 4.0) अणु
						v->planes_with_room_to_increase_vstartup_vratio_prefetch_more_than4 = dcn_bw_yes;
					पूर्ण
					अगर (v->destination_lines_क्रम_prefetch[k] < 2.0) अणु
						v->planes_with_room_to_increase_vstartup_destination_line_बार_क्रम_prefetch_less_than2 = dcn_bw_yes;
					पूर्ण
				पूर्ण
			पूर्ण
			अगर (v->max_rd_bandwidth <= v->वापस_bw && v->v_ratio_prefetch_more_than4 == dcn_bw_no && v->destination_line_बार_क्रम_prefetch_less_than2 == dcn_bw_no) अणु
				v->prefetch_mode_supported = dcn_bw_yes;
			पूर्ण
			अन्यथा अणु
				v->prefetch_mode_supported = dcn_bw_no;
			पूर्ण
			v->v_startup_lines = v->v_startup_lines + 1.0;
		पूर्ण जबतक (!(v->prefetch_mode_supported == dcn_bw_yes || (v->planes_with_room_to_increase_vstartup_prefetch_bw_less_than_active_bw == dcn_bw_yes && v->planes_with_room_to_increase_vstartup_vratio_prefetch_more_than4 == dcn_bw_no && v->planes_with_room_to_increase_vstartup_destination_line_बार_क्रम_prefetch_less_than2 == dcn_bw_no)));
		v->next_prefetch_mode = v->next_prefetch_mode + 1.0;
	पूर्ण जबतक (!(v->prefetch_mode_supported == dcn_bw_yes || v->prefetch_mode == 2.0));
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->v_ratio_prefetch_y[k] <= 1.0) अणु
			v->display_pipe_line_delivery_समय_luma_prefetch[k] = v->swath_width_y[k] * v->dpp_per_plane[k] / v->h_ratio[k] / v->pixel_घड़ी[k];
		पूर्ण
		अन्यथा अणु
			v->display_pipe_line_delivery_समय_luma_prefetch[k] = v->swath_width_y[k] / v->pscl_throughput[k] / v->dppclk;
		पूर्ण
		अगर (v->byte_per_pixel_detc[k] == 0.0) अणु
			v->display_pipe_line_delivery_समय_chroma_prefetch[k] = 0.0;
		पूर्ण
		अन्यथा अणु
			अगर (v->v_ratio_prefetch_c[k] <= 1.0) अणु
				v->display_pipe_line_delivery_समय_chroma_prefetch[k] = v->swath_width_y[k] * v->dpp_per_plane[k] / v->h_ratio[k] / v->pixel_घड़ी[k];
			पूर्ण
			अन्यथा अणु
				v->display_pipe_line_delivery_समय_chroma_prefetch[k] = v->swath_width_y[k] / v->pscl_throughput[k] / v->dppclk;
			पूर्ण
		पूर्ण
	पूर्ण
	/*min ttuv_blank*/

	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->prefetch_mode == 0.0) अणु
			v->allow_dram_घड़ी_change_during_vblank[k] = dcn_bw_yes;
			v->allow_dram_self_refresh_during_vblank[k] = dcn_bw_yes;
			v->min_ttuv_blank[k] = v->t_calc +dcn_bw_max3(v->dram_घड़ी_change_watermark, v->stutter_enter_plus_निकास_watermark, v->urgent_watermark);
		पूर्ण
		अन्यथा अगर (v->prefetch_mode == 1.0) अणु
			v->allow_dram_घड़ी_change_during_vblank[k] = dcn_bw_no;
			v->allow_dram_self_refresh_during_vblank[k] = dcn_bw_yes;
			v->min_ttuv_blank[k] = v->t_calc +dcn_bw_max2(v->stutter_enter_plus_निकास_watermark, v->urgent_watermark);
		पूर्ण
		अन्यथा अणु
			v->allow_dram_घड़ी_change_during_vblank[k] = dcn_bw_no;
			v->allow_dram_self_refresh_during_vblank[k] = dcn_bw_no;
			v->min_ttuv_blank[k] = v->t_calc + v->urgent_watermark;
		पूर्ण
	पूर्ण
	/*nb p-state/dram घड़ी change support*/

	v->active_dp_ps = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->active_dp_ps = v->active_dp_ps + v->dpp_per_plane[k];
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		v->lb_latency_hiding_source_lines_y =dcn_bw_min2(v->max_line_buffer_lines,dcn_bw_न्यूनमान2(v->line_buffer_size / v->lb_bit_per_pixel[k] / (v->swath_width_y[k] /dcn_bw_max2(v->h_ratio[k], 1.0)), 1.0)) - (v->vtaps[k] - 1.0);
		v->lb_latency_hiding_source_lines_c =dcn_bw_min2(v->max_line_buffer_lines,dcn_bw_न्यूनमान2(v->line_buffer_size / v->lb_bit_per_pixel[k] / (v->swath_width_y[k] / 2.0 /dcn_bw_max2(v->h_ratio[k] / 2.0, 1.0)), 1.0)) - (v->vta_pschroma[k] - 1.0);
		v->effective_lb_latency_hiding_y = v->lb_latency_hiding_source_lines_y / v->v_ratio[k] * (v->htotal[k] / v->pixel_घड़ी[k]);
		v->effective_lb_latency_hiding_c = v->lb_latency_hiding_source_lines_c / (v->v_ratio[k] / 2.0) * (v->htotal[k] / v->pixel_घड़ी[k]);
		अगर (v->swath_width_y[k] > 2.0 * v->dpp_output_buffer_pixels) अणु
			v->dpp_output_buffer_lines_y = v->dpp_output_buffer_pixels / v->swath_width_y[k];
		पूर्ण
		अन्यथा अगर (v->swath_width_y[k] > v->dpp_output_buffer_pixels) अणु
			v->dpp_output_buffer_lines_y = 0.5;
		पूर्ण
		अन्यथा अणु
			v->dpp_output_buffer_lines_y = 1.0;
		पूर्ण
		अगर (v->swath_width_y[k] / 2.0 > 2.0 * v->dpp_output_buffer_pixels) अणु
			v->dpp_output_buffer_lines_c = v->dpp_output_buffer_pixels / (v->swath_width_y[k] / 2.0);
		पूर्ण
		अन्यथा अगर (v->swath_width_y[k] / 2.0 > v->dpp_output_buffer_pixels) अणु
			v->dpp_output_buffer_lines_c = 0.5;
		पूर्ण
		अन्यथा अणु
			v->dpp_output_buffer_lines_c = 1.0;
		पूर्ण
		v->dppopp_buffering_y = (v->htotal[k] / v->pixel_घड़ी[k]) * (v->dpp_output_buffer_lines_y + v->opp_output_buffer_lines);
		v->max_det_buffering_समय_y = v->full_det_buffering_समय_y[k] + (v->lines_in_dety[k] - v->lines_in_dety_rounded_करोwn_to_swath[k]) / v->swath_height_y[k] * (v->htotal[k] / v->pixel_घड़ी[k]);
		v->active_dram_घड़ी_change_latency_margin_y = v->dppopp_buffering_y + v->effective_lb_latency_hiding_y + v->max_det_buffering_समय_y - v->dram_घड़ी_change_watermark;
		अगर (v->active_dp_ps > 1.0) अणु
			v->active_dram_घड़ी_change_latency_margin_y = v->active_dram_घड़ी_change_latency_margin_y - (1.0 - 1.0 / (v->active_dp_ps - 1.0)) * v->swath_height_y[k] * (v->htotal[k] / v->pixel_घड़ी[k]);
		पूर्ण
		अगर (v->byte_per_pixel_detc[k] > 0.0) अणु
			v->dppopp_buffering_c = (v->htotal[k] / v->pixel_घड़ी[k]) * (v->dpp_output_buffer_lines_c + v->opp_output_buffer_lines);
			v->max_det_buffering_समय_c = v->full_det_buffering_समय_c[k] + (v->lines_in_detc[k] - v->lines_in_detc_rounded_करोwn_to_swath[k]) / v->swath_height_c[k] * (v->htotal[k] / v->pixel_घड़ी[k]);
			v->active_dram_घड़ी_change_latency_margin_c = v->dppopp_buffering_c + v->effective_lb_latency_hiding_c + v->max_det_buffering_समय_c - v->dram_घड़ी_change_watermark;
			अगर (v->active_dp_ps > 1.0) अणु
				v->active_dram_घड़ी_change_latency_margin_c = v->active_dram_घड़ी_change_latency_margin_c - (1.0 - 1.0 / (v->active_dp_ps - 1.0)) * v->swath_height_c[k] * (v->htotal[k] / v->pixel_घड़ी[k]);
			पूर्ण
			v->active_dram_घड़ी_change_latency_margin[k] =dcn_bw_min2(v->active_dram_घड़ी_change_latency_margin_y, v->active_dram_घड़ी_change_latency_margin_c);
		पूर्ण
		अन्यथा अणु
			v->active_dram_घड़ी_change_latency_margin[k] = v->active_dram_घड़ी_change_latency_margin_y;
		पूर्ण
		अगर (v->output_क्रमmat[k] == dcn_bw_444) अणु
			v->ग_लिखोback_dram_घड़ी_change_latency_margin = (v->ग_लिखोback_luma_buffer_size + v->ग_लिखोback_chroma_buffer_size) * 1024.0 / (v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k]) * 4.0) - v->ग_लिखोback_dram_घड़ी_change_watermark;
		पूर्ण
		अन्यथा अणु
			v->ग_लिखोback_dram_घड़ी_change_latency_margin =dcn_bw_min2(v->ग_लिखोback_luma_buffer_size, 2.0 * v->ग_लिखोback_chroma_buffer_size) * 1024.0 / (v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k])) - v->ग_लिखोback_dram_घड़ी_change_watermark;
		पूर्ण
		अगर (v->output[k] == dcn_bw_ग_लिखोback) अणु
			v->active_dram_घड़ी_change_latency_margin[k] =dcn_bw_min2(v->active_dram_घड़ी_change_latency_margin[k], v->ग_लिखोback_dram_घड़ी_change_latency_margin);
		पूर्ण
	पूर्ण
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->allow_dram_घड़ी_change_during_vblank[k] == dcn_bw_yes) अणु
			v->v_blank_dram_घड़ी_change_latency_margin[k] = (v->vtotal[k] - v->scaler_recout_height[k]) * (v->htotal[k] / v->pixel_घड़ी[k]) -dcn_bw_max2(v->dram_घड़ी_change_watermark, v->ग_लिखोback_dram_घड़ी_change_watermark);
		पूर्ण
		अन्यथा अणु
			v->v_blank_dram_घड़ी_change_latency_margin[k] = 0.0;
		पूर्ण
	पूर्ण
	v->min_active_dram_घड़ी_change_margin = 999999.0;
	v->v_blank_of_min_active_dram_घड़ी_change_margin = 999999.0;
	v->second_min_active_dram_घड़ी_change_margin = 999999.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->active_dram_घड़ी_change_latency_margin[k] < v->min_active_dram_घड़ी_change_margin) अणु
			v->second_min_active_dram_घड़ी_change_margin = v->min_active_dram_घड़ी_change_margin;
			v->min_active_dram_घड़ी_change_margin = v->active_dram_घड़ी_change_latency_margin[k];
			v->v_blank_of_min_active_dram_घड़ी_change_margin = v->v_blank_dram_घड़ी_change_latency_margin[k];
		पूर्ण
		अन्यथा अगर (v->active_dram_घड़ी_change_latency_margin[k] < v->second_min_active_dram_घड़ी_change_margin) अणु
			v->second_min_active_dram_घड़ी_change_margin = v->active_dram_घड़ी_change_latency_margin[k];
		पूर्ण
	पूर्ण
	v->min_vblank_dram_घड़ी_change_margin = 999999.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->min_vblank_dram_घड़ी_change_margin > v->v_blank_dram_घड़ी_change_latency_margin[k]) अणु
			v->min_vblank_dram_घड़ी_change_margin = v->v_blank_dram_घड़ी_change_latency_margin[k];
		पूर्ण
	पूर्ण
	अगर (v->synchronized_vblank == dcn_bw_yes || v->number_of_active_planes == 1) अणु
		v->dram_घड़ी_change_margin =dcn_bw_max2(v->min_active_dram_घड़ी_change_margin, v->min_vblank_dram_घड़ी_change_margin);
	पूर्ण
	अन्यथा अगर (v->v_blank_of_min_active_dram_घड़ी_change_margin > v->min_active_dram_घड़ी_change_margin) अणु
		v->dram_घड़ी_change_margin =dcn_bw_min2(v->second_min_active_dram_घड़ी_change_margin, v->v_blank_of_min_active_dram_घड़ी_change_margin);
	पूर्ण
	अन्यथा अणु
		v->dram_घड़ी_change_margin = v->min_active_dram_घड़ी_change_margin;
	पूर्ण
	अगर (v->min_active_dram_घड़ी_change_margin > 0.0) अणु
		v->dram_घड़ी_change_support = dcn_bw_supported_in_v_active;
	पूर्ण
	अन्यथा अगर (v->dram_घड़ी_change_margin > 0.0) अणु
		v->dram_घड़ी_change_support = dcn_bw_supported_in_v_blank;
	पूर्ण
	अन्यथा अणु
		v->dram_घड़ी_change_support = dcn_bw_not_supported;
	पूर्ण
	/*maximum bandwidth used*/

	v->wr_bandwidth = 0.0;
	क्रम (k = 0; k <= v->number_of_active_planes - 1; k++) अणु
		अगर (v->output[k] == dcn_bw_ग_लिखोback && v->output_क्रमmat[k] == dcn_bw_444) अणु
			v->wr_bandwidth = v->wr_bandwidth + v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k]) * 4.0;
		पूर्ण
		अन्यथा अगर (v->output[k] == dcn_bw_ग_लिखोback) अणु
			v->wr_bandwidth = v->wr_bandwidth + v->scaler_rec_out_width[k] / (v->htotal[k] / v->pixel_घड़ी[k]) * 1.5;
		पूर्ण
	पूर्ण
	v->max_used_bw = v->max_rd_bandwidth + v->wr_bandwidth;
पूर्ण
