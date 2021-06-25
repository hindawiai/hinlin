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

/**
 * Bandwidth and Watermark calculations पूर्णांकerface.
 * (Refer to "DCEx_mode_support.xlsm" from Perक्रमce.)
 */
#अगर_अघोषित __DCN_CALCS_H__
#घोषणा __DCN_CALCS_H__

#समावेश "bw_fixed.h"
#समावेश "../dml/display_mode_lib.h"


काष्ठा dc;
काष्ठा dc_state;

/*******************************************************************************
 * DCN data काष्ठाures.
 ******************************************************************************/

#घोषणा number_of_planes   6
#घोषणा number_of_planes_minus_one   5
#घोषणा number_of_states   4
#घोषणा number_of_states_plus_one   5

#घोषणा ddr4_dram_width   64
#घोषणा ddr4_dram_factor_single_Channel   16
क्रमागत dcn_bw_defs अणु
	dcn_bw_v_min0p65,
	dcn_bw_v_mid0p72,
	dcn_bw_v_nom0p8,
	dcn_bw_v_max0p9,
	dcn_bw_v_max0p91,
	dcn_bw_no_support = 5,
	dcn_bw_yes,
	dcn_bw_hor,
	dcn_bw_vert,
	dcn_bw_override,
	dcn_bw_rgb_sub_64,
	dcn_bw_rgb_sub_32,
	dcn_bw_rgb_sub_16,
	dcn_bw_no,
	dcn_bw_sw_linear,
	dcn_bw_sw_4_kb_d,
	dcn_bw_sw_4_kb_d_x,
	dcn_bw_sw_64_kb_d,
	dcn_bw_sw_64_kb_d_t,
	dcn_bw_sw_64_kb_d_x,
	dcn_bw_sw_var_d,
	dcn_bw_sw_var_d_x,
	dcn_bw_yuv420_sub_8,
	dcn_bw_sw_4_kb_s,
	dcn_bw_sw_4_kb_s_x,
	dcn_bw_sw_64_kb_s,
	dcn_bw_sw_64_kb_s_t,
	dcn_bw_sw_64_kb_s_x,
	dcn_bw_ग_लिखोback,
	dcn_bw_444,
	dcn_bw_dp,
	dcn_bw_420,
	dcn_bw_hdmi,
	dcn_bw_sw_var_s,
	dcn_bw_sw_var_s_x,
	dcn_bw_yuv420_sub_10,
	dcn_bw_supported_in_v_active,
	dcn_bw_supported_in_v_blank,
	dcn_bw_not_supported,
	dcn_bw_na,
	dcn_bw_encoder_8bpc,
	dcn_bw_encoder_10bpc,
	dcn_bw_encoder_12bpc,
	dcn_bw_encoder_16bpc,
पूर्ण;

/*bounding box parameters*/
/*mode parameters*/
/*प्रणाली configuration*/
/* display configuration*/
काष्ठा dcn_bw_पूर्णांकernal_vars अणु
	भग्न voltage[number_of_states_plus_one + 1];
	भग्न max_dispclk[number_of_states_plus_one + 1];
	भग्न max_dppclk[number_of_states_plus_one + 1];
	भग्न dcfclk_per_state[number_of_states_plus_one + 1];
	भग्न phyclk_per_state[number_of_states_plus_one + 1];
	भग्न fabric_and_dram_bandwidth_per_state[number_of_states_plus_one + 1];
	भग्न sr_निकास_समय;
	भग्न sr_enter_plus_निकास_समय;
	भग्न dram_घड़ी_change_latency;
	भग्न urgent_latency;
	भग्न ग_लिखो_back_latency;
	भग्न percent_of_ideal_drambw_received_after_urg_latency;
	भग्न dcfclkv_max0p9;
	भग्न dcfclkv_nom0p8;
	भग्न dcfclkv_mid0p72;
	भग्न dcfclkv_min0p65;
	भग्न max_dispclk_vmax0p9;
	भग्न max_dppclk_vmax0p9;
	भग्न max_dispclk_vnom0p8;
	भग्न max_dppclk_vnom0p8;
	भग्न max_dispclk_vmid0p72;
	भग्न max_dppclk_vmid0p72;
	भग्न max_dispclk_vmin0p65;
	भग्न max_dppclk_vmin0p65;
	भग्न socclk;
	भग्न fabric_and_dram_bandwidth_vmax0p9;
	भग्न fabric_and_dram_bandwidth_vnom0p8;
	भग्न fabric_and_dram_bandwidth_vmid0p72;
	भग्न fabric_and_dram_bandwidth_vmin0p65;
	भग्न round_trip_ping_latency_cycles;
	भग्न urgent_out_of_order_वापस_per_channel;
	भग्न number_of_channels;
	भग्न vmm_page_size;
	भग्न वापस_bus_width;
	भग्न rob_buffer_size_in_kbyte;
	भग्न det_buffer_size_in_kbyte;
	भग्न dpp_output_buffer_pixels;
	भग्न opp_output_buffer_lines;
	भग्न pixel_chunk_size_in_kbyte;
	भग्न pte_chunk_size;
	भग्न meta_chunk_size;
	भग्न ग_लिखोback_chunk_size;
	क्रमागत dcn_bw_defs odm_capability;
	क्रमागत dcn_bw_defs dsc_capability;
	भग्न line_buffer_size;
	क्रमागत dcn_bw_defs is_line_buffer_bpp_fixed;
	भग्न line_buffer_fixed_bpp;
	भग्न max_line_buffer_lines;
	भग्न ग_लिखोback_luma_buffer_size;
	भग्न ग_लिखोback_chroma_buffer_size;
	भग्न max_num_dpp;
	भग्न max_num_ग_लिखोback;
	भग्न max_dchub_topscl_throughput;
	भग्न max_pscl_tolb_throughput;
	भग्न max_lb_tovscl_throughput;
	भग्न max_vscl_tohscl_throughput;
	भग्न max_hscl_ratio;
	भग्न max_vscl_ratio;
	भग्न max_hscl_taps;
	भग्न max_vscl_taps;
	भग्न under_scan_factor;
	भग्न phyclkv_max0p9;
	भग्न phyclkv_nom0p8;
	भग्न phyclkv_mid0p72;
	भग्न phyclkv_min0p65;
	भग्न pte_buffer_size_in_requests;
	भग्न dispclk_ramping_margin;
	भग्न करोwnspपढ़ोing;
	भग्न max_पूर्णांकer_dcn_tile_repeaters;
	क्रमागत dcn_bw_defs can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one;
	क्रमागत dcn_bw_defs bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed;
	पूर्णांक mode;
	भग्न viewport_width[number_of_planes_minus_one + 1];
	भग्न htotal[number_of_planes_minus_one + 1];
	भग्न vtotal[number_of_planes_minus_one + 1];
	भग्न v_sync_plus_back_porch[number_of_planes_minus_one + 1];
	भग्न vactive[number_of_planes_minus_one + 1];
	भग्न pixel_घड़ी[number_of_planes_minus_one + 1]; /*MHz*/
	भग्न viewport_height[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs dcc_enable[number_of_planes_minus_one + 1];
	भग्न dcc_rate[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs source_scan[number_of_planes_minus_one + 1];
	भग्न lb_bit_per_pixel[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs source_pixel_क्रमmat[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs source_surface_mode[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs output_क्रमmat[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs output_deep_color[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs output[number_of_planes_minus_one + 1];
	भग्न scaler_rec_out_width[number_of_planes_minus_one + 1];
	भग्न scaler_recout_height[number_of_planes_minus_one + 1];
	भग्न underscan_output[number_of_planes_minus_one + 1];
	भग्न पूर्णांकerlace_output[number_of_planes_minus_one + 1];
	भग्न override_hta_ps[number_of_planes_minus_one + 1];
	भग्न override_vta_ps[number_of_planes_minus_one + 1];
	भग्न override_hta_pschroma[number_of_planes_minus_one + 1];
	भग्न override_vta_pschroma[number_of_planes_minus_one + 1];
	भग्न urgent_latency_support_us[number_of_planes_minus_one + 1];
	भग्न h_ratio[number_of_planes_minus_one + 1];
	भग्न v_ratio[number_of_planes_minus_one + 1];
	भग्न htaps[number_of_planes_minus_one + 1];
	भग्न vtaps[number_of_planes_minus_one + 1];
	भग्न hta_pschroma[number_of_planes_minus_one + 1];
	भग्न vta_pschroma[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs pte_enable;
	क्रमागत dcn_bw_defs synchronized_vblank;
	क्रमागत dcn_bw_defs ta_pscalculation;
	पूर्णांक voltage_override_level;
	पूर्णांक number_of_active_planes;
	पूर्णांक voltage_level;
	क्रमागत dcn_bw_defs immediate_flip_supported;
	भग्न dcfclk;
	भग्न max_phyclk;
	भग्न fabric_and_dram_bandwidth;
	भग्न dpp_per_plane_per_ratio[1 + 1][number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs dispclk_dppclk_support_per_ratio[1 + 1];
	भग्न required_dispclk_per_ratio[1 + 1];
	क्रमागत dcn_bw_defs error_message[1 + 1];
	पूर्णांक dispclk_dppclk_ratio;
	भग्न dpp_per_plane[number_of_planes_minus_one + 1];
	भग्न det_buffer_size_y[number_of_planes_minus_one + 1];
	भग्न det_buffer_size_c[number_of_planes_minus_one + 1];
	भग्न swath_height_y[number_of_planes_minus_one + 1];
	भग्न swath_height_c[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs final_error_message;
	भग्न frequency;
	भग्न header_line;
	भग्न header;
	क्रमागत dcn_bw_defs voltage_override;
	क्रमागत dcn_bw_defs allow_dअगरferent_hratio_vratio;
	भग्न acceptable_quality_hta_ps;
	भग्न acceptable_quality_vta_ps;
	भग्न no_of_dpp[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न swath_width_yper_state[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न swath_height_yper_state[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न swath_height_cper_state[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न urgent_latency_support_us_per_state[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न v_ratio_pre_ywith_immediate_flip[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न v_ratio_pre_cwith_immediate_flip[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न required_prefetch_pixel_data_bw_with_immediate_flip[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न v_ratio_pre_ywithout_immediate_flip[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न v_ratio_pre_cwithout_immediate_flip[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	भग्न required_prefetch_pixel_data_bw_without_immediate_flip[number_of_states_plus_one + 1][1 + 1][number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs prefetch_supported_with_immediate_flip[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs prefetch_supported_without_immediate_flip[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs v_ratio_in_prefetch_supported_with_immediate_flip[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs v_ratio_in_prefetch_supported_without_immediate_flip[number_of_states_plus_one + 1][1 + 1];
	भग्न required_dispclk[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs dispclk_dppclk_support[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs total_available_pipes_support[number_of_states_plus_one + 1][1 + 1];
	भग्न total_number_of_active_dpp[number_of_states_plus_one + 1][1 + 1];
	भग्न total_number_of_dcc_active_dpp[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs urgent_latency_support[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs mode_support_with_immediate_flip[number_of_states_plus_one + 1][1 + 1];
	क्रमागत dcn_bw_defs mode_support_without_immediate_flip[number_of_states_plus_one + 1][1 + 1];
	भग्न वापस_bw_per_state[number_of_states_plus_one + 1];
	क्रमागत dcn_bw_defs dio_support[number_of_states_plus_one + 1];
	भग्न urgent_round_trip_and_out_of_order_latency_per_state[number_of_states_plus_one + 1];
	क्रमागत dcn_bw_defs rob_support[number_of_states_plus_one + 1];
	क्रमागत dcn_bw_defs bandwidth_support[number_of_states_plus_one + 1];
	भग्न prefetch_bw[number_of_planes_minus_one + 1];
	भग्न meta_pte_bytes_per_frame[number_of_planes_minus_one + 1];
	भग्न meta_row_bytes[number_of_planes_minus_one + 1];
	भग्न dpte_bytes_per_row[number_of_planes_minus_one + 1];
	भग्न prefetch_lines_y[number_of_planes_minus_one + 1];
	भग्न prefetch_lines_c[number_of_planes_minus_one + 1];
	भग्न max_num_sw_y[number_of_planes_minus_one + 1];
	भग्न max_num_sw_c[number_of_planes_minus_one + 1];
	भग्न line_बार_क्रम_prefetch[number_of_planes_minus_one + 1];
	भग्न lines_क्रम_meta_pte_with_immediate_flip[number_of_planes_minus_one + 1];
	भग्न lines_क्रम_meta_pte_without_immediate_flip[number_of_planes_minus_one + 1];
	भग्न lines_क्रम_meta_and_dpte_row_with_immediate_flip[number_of_planes_minus_one + 1];
	भग्न lines_क्रम_meta_and_dpte_row_without_immediate_flip[number_of_planes_minus_one + 1];
	भग्न min_dppclk_using_single_dpp[number_of_planes_minus_one + 1];
	भग्न swath_width_ysingle_dpp[number_of_planes_minus_one + 1];
	भग्न byte_per_pixel_in_dety[number_of_planes_minus_one + 1];
	भग्न byte_per_pixel_in_detc[number_of_planes_minus_one + 1];
	भग्न number_of_dpp_required_क्रम_det_and_lb_size[number_of_planes_minus_one + 1];
	भग्न required_phyclk[number_of_planes_minus_one + 1];
	भग्न पढ़ो256_block_height_y[number_of_planes_minus_one + 1];
	भग्न पढ़ो256_block_width_y[number_of_planes_minus_one + 1];
	भग्न पढ़ो256_block_height_c[number_of_planes_minus_one + 1];
	भग्न पढ़ो256_block_width_c[number_of_planes_minus_one + 1];
	भग्न max_swath_height_y[number_of_planes_minus_one + 1];
	भग्न max_swath_height_c[number_of_planes_minus_one + 1];
	भग्न min_swath_height_y[number_of_planes_minus_one + 1];
	भग्न min_swath_height_c[number_of_planes_minus_one + 1];
	भग्न पढ़ो_bandwidth[number_of_planes_minus_one + 1];
	भग्न ग_लिखो_bandwidth[number_of_planes_minus_one + 1];
	भग्न pscl_factor[number_of_planes_minus_one + 1];
	भग्न pscl_factor_chroma[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs scale_ratio_support;
	क्रमागत dcn_bw_defs source_क्रमmat_pixel_and_scan_support;
	भग्न total_पढ़ो_bandwidth_consumed_gbyte_per_second;
	भग्न total_ग_लिखो_bandwidth_consumed_gbyte_per_second;
	भग्न total_bandwidth_consumed_gbyte_per_second;
	क्रमागत dcn_bw_defs dcc_enabled_in_any_plane;
	भग्न वापस_bw_todcn_per_state;
	भग्न critical_poपूर्णांक;
	क्रमागत dcn_bw_defs ग_लिखोback_latency_support;
	भग्न required_output_bw;
	भग्न total_number_of_active_ग_लिखोback;
	क्रमागत dcn_bw_defs total_available_ग_लिखोback_support;
	भग्न maximum_swath_width;
	भग्न number_of_dpp_required_क्रम_det_size;
	भग्न number_of_dpp_required_क्रम_lb_size;
	भग्न min_dispclk_using_single_dpp;
	भग्न min_dispclk_using_dual_dpp;
	क्रमागत dcn_bw_defs viewport_size_support;
	भग्न swath_width_granularity_y;
	भग्न rounded_up_max_swath_size_bytes_y;
	भग्न swath_width_granularity_c;
	भग्न rounded_up_max_swath_size_bytes_c;
	भग्न lines_in_det_luma;
	भग्न lines_in_det_chroma;
	भग्न effective_lb_latency_hiding_source_lines_luma;
	भग्न effective_lb_latency_hiding_source_lines_chroma;
	भग्न effective_detlb_lines_luma;
	भग्न effective_detlb_lines_chroma;
	भग्न projected_dcfclk_deep_sleep;
	भग्न meta_req_height_y;
	भग्न meta_req_width_y;
	भग्न meta_surface_width_y;
	भग्न meta_surface_height_y;
	भग्न meta_pte_bytes_per_frame_y;
	भग्न meta_row_bytes_y;
	भग्न macro_tile_block_size_bytes_y;
	भग्न macro_tile_block_height_y;
	भग्न data_pte_req_height_y;
	भग्न data_pte_req_width_y;
	भग्न dpte_bytes_per_row_y;
	भग्न meta_req_height_c;
	भग्न meta_req_width_c;
	भग्न meta_surface_width_c;
	भग्न meta_surface_height_c;
	भग्न meta_pte_bytes_per_frame_c;
	भग्न meta_row_bytes_c;
	भग्न macro_tile_block_size_bytes_c;
	भग्न macro_tile_block_height_c;
	भग्न macro_tile_block_width_c;
	भग्न data_pte_req_height_c;
	भग्न data_pte_req_width_c;
	भग्न dpte_bytes_per_row_c;
	भग्न v_init_y;
	भग्न max_partial_sw_y;
	भग्न v_init_c;
	भग्न max_partial_sw_c;
	भग्न dst_x_after_scaler;
	भग्न dst_y_after_scaler;
	भग्न समय_calc;
	भग्न v_update_offset[number_of_planes_minus_one + 1][2];
	भग्न total_repeater_delay;
	भग्न v_update_width[number_of_planes_minus_one + 1][2];
	भग्न v_पढ़ोy_offset[number_of_planes_minus_one + 1][2];
	भग्न समय_setup;
	भग्न extra_latency;
	भग्न maximum_vstartup;
	भग्न bw_available_क्रम_immediate_flip;
	भग्न total_immediate_flip_bytes[number_of_planes_minus_one + 1];
	भग्न समय_क्रम_meta_pte_with_immediate_flip;
	भग्न समय_क्रम_meta_pte_without_immediate_flip;
	भग्न समय_क्रम_meta_and_dpte_row_with_immediate_flip;
	भग्न समय_क्रम_meta_and_dpte_row_without_immediate_flip;
	भग्न line_बार_to_request_prefetch_pixel_data_with_immediate_flip;
	भग्न line_बार_to_request_prefetch_pixel_data_without_immediate_flip;
	भग्न maximum_पढ़ो_bandwidth_with_prefetch_with_immediate_flip;
	भग्न maximum_पढ़ो_bandwidth_with_prefetch_without_immediate_flip;
	भग्न voltage_level_with_immediate_flip;
	भग्न voltage_level_without_immediate_flip;
	भग्न total_number_of_active_dpp_per_ratio[1 + 1];
	भग्न byte_per_pix_dety;
	भग्न byte_per_pix_detc;
	भग्न पढ़ो256_bytes_block_height_y;
	भग्न पढ़ो256_bytes_block_width_y;
	भग्न पढ़ो256_bytes_block_height_c;
	भग्न पढ़ो256_bytes_block_width_c;
	भग्न maximum_swath_height_y;
	भग्न maximum_swath_height_c;
	भग्न minimum_swath_height_y;
	भग्न minimum_swath_height_c;
	भग्न swath_width;
	भग्न prefetch_bandwidth[number_of_planes_minus_one + 1];
	भग्न v_init_pre_fill_y[number_of_planes_minus_one + 1];
	भग्न v_init_pre_fill_c[number_of_planes_minus_one + 1];
	भग्न max_num_swath_y[number_of_planes_minus_one + 1];
	भग्न max_num_swath_c[number_of_planes_minus_one + 1];
	भग्न prefill_y[number_of_planes_minus_one + 1];
	भग्न prefill_c[number_of_planes_minus_one + 1];
	भग्न v_startup[number_of_planes_minus_one + 1];
	क्रमागत dcn_bw_defs allow_dram_घड़ी_change_during_vblank[number_of_planes_minus_one + 1];
	भग्न allow_dram_self_refresh_during_vblank[number_of_planes_minus_one + 1];
	भग्न v_ratio_prefetch_y[number_of_planes_minus_one + 1];
	भग्न v_ratio_prefetch_c[number_of_planes_minus_one + 1];
	भग्न destination_lines_क्रम_prefetch[number_of_planes_minus_one + 1];
	भग्न destination_lines_to_request_vm_inv_blank[number_of_planes_minus_one + 1];
	भग्न destination_lines_to_request_row_in_vblank[number_of_planes_minus_one + 1];
	भग्न min_ttuv_blank[number_of_planes_minus_one + 1];
	भग्न byte_per_pixel_dety[number_of_planes_minus_one + 1];
	भग्न byte_per_pixel_detc[number_of_planes_minus_one + 1];
	भग्न swath_width_y[number_of_planes_minus_one + 1];
	भग्न lines_in_dety[number_of_planes_minus_one + 1];
	भग्न lines_in_dety_rounded_करोwn_to_swath[number_of_planes_minus_one + 1];
	भग्न lines_in_detc[number_of_planes_minus_one + 1];
	भग्न lines_in_detc_rounded_करोwn_to_swath[number_of_planes_minus_one + 1];
	भग्न full_det_buffering_समय_y[number_of_planes_minus_one + 1];
	भग्न full_det_buffering_समय_c[number_of_planes_minus_one + 1];
	भग्न active_dram_घड़ी_change_latency_margin[number_of_planes_minus_one + 1];
	भग्न v_blank_dram_घड़ी_change_latency_margin[number_of_planes_minus_one + 1];
	भग्न dcfclk_deep_sleep_per_plane[number_of_planes_minus_one + 1];
	भग्न पढ़ो_bandwidth_plane_luma[number_of_planes_minus_one + 1];
	भग्न पढ़ो_bandwidth_plane_chroma[number_of_planes_minus_one + 1];
	भग्न display_pipe_line_delivery_समय_luma[number_of_planes_minus_one + 1];
	भग्न display_pipe_line_delivery_समय_chroma[number_of_planes_minus_one + 1];
	भग्न display_pipe_line_delivery_समय_luma_prefetch[number_of_planes_minus_one + 1];
	भग्न display_pipe_line_delivery_समय_chroma_prefetch[number_of_planes_minus_one + 1];
	भग्न pixel_pte_bytes_per_row[number_of_planes_minus_one + 1];
	भग्न meta_pte_bytes_frame[number_of_planes_minus_one + 1];
	भग्न meta_row_byte[number_of_planes_minus_one + 1];
	भग्न prefetch_source_lines_y[number_of_planes_minus_one + 1];
	भग्न prefetch_source_lines_c[number_of_planes_minus_one + 1];
	भग्न pscl_throughput[number_of_planes_minus_one + 1];
	भग्न pscl_throughput_chroma[number_of_planes_minus_one + 1];
	भग्न output_bpphdmi[number_of_planes_minus_one + 1];
	भग्न output_bppdp4_lane_hbr[number_of_planes_minus_one + 1];
	भग्न output_bppdp4_lane_hbr2[number_of_planes_minus_one + 1];
	भग्न output_bppdp4_lane_hbr3[number_of_planes_minus_one + 1];
	भग्न max_vstartup_lines[number_of_planes_minus_one + 1];
	भग्न dispclk_with_ramping;
	भग्न dispclk_without_ramping;
	भग्न dppclk_using_single_dpp_luma;
	भग्न dppclk_using_single_dpp;
	भग्न dppclk_using_single_dpp_chroma;
	क्रमागत dcn_bw_defs odm_capable;
	भग्न dispclk;
	भग्न dppclk;
	भग्न वापस_bandwidth_to_dcn;
	क्रमागत dcn_bw_defs dcc_enabled_any_plane;
	भग्न वापस_bw;
	भग्न critical_compression;
	भग्न total_data_पढ़ो_bandwidth;
	भग्न total_active_dpp;
	भग्न total_dcc_active_dpp;
	भग्न urgent_round_trip_and_out_of_order_latency;
	भग्न last_pixel_of_line_extra_watermark;
	भग्न data_fabric_line_delivery_समय_luma;
	भग्न data_fabric_line_delivery_समय_chroma;
	भग्न urgent_extra_latency;
	भग्न urgent_watermark;
	भग्न ptemeta_urgent_watermark;
	भग्न dram_घड़ी_change_watermark;
	भग्न total_active_ग_लिखोback;
	भग्न ग_लिखोback_dram_घड़ी_change_watermark;
	भग्न min_full_det_buffering_समय;
	भग्न frame_समय_क्रम_min_full_det_buffering_समय;
	भग्न average_पढ़ो_bandwidth_gbyte_per_second;
	भग्न part_of_burst_that_fits_in_rob;
	भग्न stutter_burst_समय;
	भग्न stutter_efficiency_not_including_vblank;
	भग्न smallest_vblank;
	भग्न v_blank_समय;
	भग्न stutter_efficiency;
	भग्न dcf_clk_deep_sleep;
	भग्न stutter_निकास_watermark;
	भग्न stutter_enter_plus_निकास_watermark;
	भग्न effective_det_plus_lb_lines_luma;
	भग्न urgent_latency_support_us_luma;
	भग्न effective_det_plus_lb_lines_chroma;
	भग्न urgent_latency_support_us_chroma;
	भग्न min_urgent_latency_support_us;
	भग्न non_urgent_latency_tolerance;
	भग्न block_height256_bytes_y;
	भग्न block_height256_bytes_c;
	भग्न meta_request_width_y;
	भग्न meta_surf_width_y;
	भग्न meta_surf_height_y;
	भग्न meta_pte_bytes_frame_y;
	भग्न meta_row_byte_y;
	भग्न macro_tile_size_byte_y;
	भग्न macro_tile_height_y;
	भग्न pixel_pte_req_height_y;
	भग्न pixel_pte_req_width_y;
	भग्न pixel_pte_bytes_per_row_y;
	भग्न meta_request_width_c;
	भग्न meta_surf_width_c;
	भग्न meta_surf_height_c;
	भग्न meta_pte_bytes_frame_c;
	भग्न meta_row_byte_c;
	भग्न macro_tile_size_bytes_c;
	भग्न macro_tile_height_c;
	भग्न pixel_pte_req_height_c;
	भग्न pixel_pte_req_width_c;
	भग्न pixel_pte_bytes_per_row_c;
	भग्न max_partial_swath_y;
	भग्न max_partial_swath_c;
	भग्न t_calc;
	भग्न next_prefetch_mode;
	भग्न v_startup_lines;
	क्रमागत dcn_bw_defs planes_with_room_to_increase_vstartup_prefetch_bw_less_than_active_bw;
	क्रमागत dcn_bw_defs planes_with_room_to_increase_vstartup_vratio_prefetch_more_than4;
	क्रमागत dcn_bw_defs planes_with_room_to_increase_vstartup_destination_line_बार_क्रम_prefetch_less_than2;
	क्रमागत dcn_bw_defs v_ratio_prefetch_more_than4;
	क्रमागत dcn_bw_defs destination_line_बार_क्रम_prefetch_less_than2;
	भग्न prefetch_mode;
	भग्न dstx_after_scaler;
	भग्न dsty_after_scaler;
	भग्न v_update_offset_pix[number_of_planes_minus_one + 1];
	भग्न total_repeater_delay_समय;
	भग्न v_update_width_pix[number_of_planes_minus_one + 1];
	भग्न v_पढ़ोy_offset_pix[number_of_planes_minus_one + 1];
	भग्न t_setup;
	भग्न t_रुको;
	भग्न bandwidth_available_क्रम_immediate_flip;
	भग्न tot_immediate_flip_bytes;
	भग्न max_rd_bandwidth;
	भग्न समय_क्रम_fetching_meta_pte;
	भग्न समय_क्रम_fetching_row_in_vblank;
	भग्न lines_to_request_prefetch_pixel_data;
	भग्न required_prefetch_pix_data_bw;
	क्रमागत dcn_bw_defs prefetch_mode_supported;
	भग्न active_dp_ps;
	भग्न lb_latency_hiding_source_lines_y;
	भग्न lb_latency_hiding_source_lines_c;
	भग्न effective_lb_latency_hiding_y;
	भग्न effective_lb_latency_hiding_c;
	भग्न dpp_output_buffer_lines_y;
	भग्न dpp_output_buffer_lines_c;
	भग्न dppopp_buffering_y;
	भग्न max_det_buffering_समय_y;
	भग्न active_dram_घड़ी_change_latency_margin_y;
	भग्न dppopp_buffering_c;
	भग्न max_det_buffering_समय_c;
	भग्न active_dram_घड़ी_change_latency_margin_c;
	भग्न ग_लिखोback_dram_घड़ी_change_latency_margin;
	भग्न min_active_dram_घड़ी_change_margin;
	भग्न v_blank_of_min_active_dram_घड़ी_change_margin;
	भग्न second_min_active_dram_घड़ी_change_margin;
	भग्न min_vblank_dram_घड़ी_change_margin;
	भग्न dram_घड़ी_change_margin;
	भग्न dram_घड़ी_change_support;
	भग्न wr_bandwidth;
	भग्न max_used_bw;
पूर्ण;

काष्ठा dcn_soc_bounding_box अणु
	भग्न sr_निकास_समय; /*us*/
	भग्न sr_enter_plus_निकास_समय; /*us*/
	भग्न urgent_latency; /*us*/
	भग्न ग_लिखो_back_latency; /*us*/
	भग्न percent_of_ideal_drambw_received_after_urg_latency; /*%*/
	पूर्णांक max_request_size; /*bytes*/
	भग्न dcfclkv_max0p9; /*MHz*/
	भग्न dcfclkv_nom0p8; /*MHz*/
	भग्न dcfclkv_mid0p72; /*MHz*/
	भग्न dcfclkv_min0p65; /*MHz*/
	भग्न max_dispclk_vmax0p9; /*MHz*/
	भग्न max_dispclk_vmid0p72; /*MHz*/
	भग्न max_dispclk_vnom0p8; /*MHz*/
	भग्न max_dispclk_vmin0p65; /*MHz*/
	भग्न max_dppclk_vmax0p9; /*MHz*/
	भग्न max_dppclk_vnom0p8; /*MHz*/
	भग्न max_dppclk_vmid0p72; /*MHz*/
	भग्न max_dppclk_vmin0p65; /*MHz*/
	भग्न socclk; /*MHz*/
	भग्न fabric_and_dram_bandwidth_vmax0p9; /*GB/s*/
	भग्न fabric_and_dram_bandwidth_vnom0p8; /*GB/s*/
	भग्न fabric_and_dram_bandwidth_vmid0p72; /*GB/s*/
	भग्न fabric_and_dram_bandwidth_vmin0p65; /*GB/s*/
	भग्न phyclkv_max0p9; /*MHz*/
	भग्न phyclkv_nom0p8; /*MHz*/
	भग्न phyclkv_mid0p72; /*MHz*/
	भग्न phyclkv_min0p65; /*MHz*/
	भग्न करोwnspपढ़ोing; /*%*/
	पूर्णांक round_trip_ping_latency_cycles; /*DCFCLK Cycles*/
	पूर्णांक urgent_out_of_order_वापस_per_channel; /*bytes*/
	पूर्णांक number_of_channels;
	पूर्णांक vmm_page_size; /*bytes*/
	भग्न dram_घड़ी_change_latency; /*us*/
	पूर्णांक वापस_bus_width; /*bytes*/
	भग्न percent_disp_bw_limit; /*%*/
पूर्ण;
बाह्य स्थिर काष्ठा dcn_soc_bounding_box dcn10_soc_शेषs;

काष्ठा dcn_ip_params अणु
	भग्न rob_buffer_size_in_kbyte;
	भग्न det_buffer_size_in_kbyte;
	भग्न dpp_output_buffer_pixels;
	भग्न opp_output_buffer_lines;
	भग्न pixel_chunk_size_in_kbyte;
	क्रमागत dcn_bw_defs pte_enable;
	पूर्णांक pte_chunk_size; /*kbytes*/
	पूर्णांक meta_chunk_size; /*kbytes*/
	पूर्णांक ग_लिखोback_chunk_size; /*kbytes*/
	क्रमागत dcn_bw_defs odm_capability;
	क्रमागत dcn_bw_defs dsc_capability;
	पूर्णांक line_buffer_size; /*bit*/
	पूर्णांक max_line_buffer_lines;
	क्रमागत dcn_bw_defs is_line_buffer_bpp_fixed;
	पूर्णांक line_buffer_fixed_bpp;
	पूर्णांक ग_लिखोback_luma_buffer_size; /*kbytes*/
	पूर्णांक ग_लिखोback_chroma_buffer_size; /*kbytes*/
	पूर्णांक max_num_dpp;
	पूर्णांक max_num_ग_लिखोback;
	पूर्णांक max_dchub_topscl_throughput; /*pixels/dppclk*/
	पूर्णांक max_pscl_tolb_throughput; /*pixels/dppclk*/
	पूर्णांक max_lb_tovscl_throughput; /*pixels/dppclk*/
	पूर्णांक max_vscl_tohscl_throughput; /*pixels/dppclk*/
	भग्न max_hscl_ratio;
	भग्न max_vscl_ratio;
	पूर्णांक max_hscl_taps;
	पूर्णांक max_vscl_taps;
	पूर्णांक pte_buffer_size_in_requests;
	भग्न dispclk_ramping_margin; /*%*/
	भग्न under_scan_factor;
	पूर्णांक max_पूर्णांकer_dcn_tile_repeaters;
	क्रमागत dcn_bw_defs can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one;
	क्रमागत dcn_bw_defs bug_क्रमcing_luma_and_chroma_request_to_same_size_fixed;
	पूर्णांक dcfclk_cstate_latency;
पूर्ण;
बाह्य स्थिर काष्ठा dcn_ip_params dcn10_ip_शेषs;

bool dcn_validate_bandwidth(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		bool fast_validate);

अचिन्हित पूर्णांक dcn_find_dcfclk_suits_all(
	स्थिर काष्ठा dc *dc,
	काष्ठा dc_घड़ीs *घड़ीs);

व्योम dcn_bw_update_from_pplib(काष्ठा dc *dc);
व्योम dcn_bw_notअगरy_pplib_of_wm_ranges(काष्ठा dc *dc);
व्योम dcn_bw_sync_calcs_and_dml(काष्ठा dc *dc);

क्रमागत source_macro_tile_size swizzle_mode_to_macro_tile_size(क्रमागत swizzle_mode_values sw_mode);

#पूर्ण_अगर /* __DCN_CALCS_H__ */

