<शैली गुरु>
/*
 * Copyright 2015-2017 Advanced Micro Devices, Inc.
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
#अगर_अघोषित __DCE_CALCS_H__
#घोषणा __DCE_CALCS_H__

#समावेश "bw_fixed.h"

काष्ठा pipe_ctx;
काष्ठा dc;
काष्ठा dc_state;
काष्ठा dce_bw_output;

क्रमागत bw_calcs_version अणु
	BW_CALCS_VERSION_INVALID,
	BW_CALCS_VERSION_CARRIZO,
	BW_CALCS_VERSION_POLARIS10,
	BW_CALCS_VERSION_POLARIS11,
	BW_CALCS_VERSION_POLARIS12,
	BW_CALCS_VERSION_VEGAM,
	BW_CALCS_VERSION_STONEY,
	BW_CALCS_VERSION_VEGA10
पूर्ण;

/*******************************************************************************
 * There are three types of input पूर्णांकo Calculations:
 * 1. per-DCE अटल values - these are "hardcoded" properties of the DCEIP
 * 2. board-level values - these are generally coming from VBIOS parser
 * 3. mode/configuration values - depending Mode, Scaling number of Displays etc.
 ******************************************************************************/

क्रमागत bw_defines अणु
	//Common
	bw_def_no = 0,
	bw_def_none = 0,
	bw_def_yes = 1,
	bw_def_ok = 1,
	bw_def_high = 2,
	bw_def_mid = 1,
	bw_def_low = 0,

	//Internal
	bw_defs_start = 255,
	bw_def_underlay422,
	bw_def_underlay420_luma,
	bw_def_underlay420_chroma,
	bw_def_underlay444,
	bw_def_graphics,
	bw_def_display_ग_लिखो_back420_luma,
	bw_def_display_ग_लिखो_back420_chroma,
	bw_def_portrait,
	bw_def_hsr_mtn_4,
	bw_def_hsr_mtn_h_taps,
	bw_def_उच्चमानing__h_taps_भाग_4___meq_hsr,
	bw_def_invalid_linear_or_stereo_mode,
	bw_def_invalid_rotation_or_bpp_or_stereo,
	bw_def_vsr_mtn_v_taps,
	bw_def_vsr_mtn_4,
	bw_def_स्वतः,
	bw_def_manual,
	bw_def_exceeded_allowed_maximum_sclk,
	bw_def_exceeded_allowed_page_बंद_खोलो,
	bw_def_exceeded_allowed_outstanding_pte_req_queue_size,
	bw_def_exceeded_allowed_maximum_bw,
	bw_def_landscape,

	//Panning and bezel
	bw_def_any_lines,

	//Underlay mode
	bw_def_underlay_only,
	bw_def_blended,
	bw_def_blend,

	//Stereo mode
	bw_def_mono,
	bw_def_side_by_side,
	bw_def_top_bottom,

	//Underlay surface type
	bw_def_420,
	bw_def_422,
	bw_def_444,

	//Tiling mode
	bw_def_linear,
	bw_def_tiled,
	bw_def_array_linear_general,
	bw_def_array_linear_aligned,
	bw_def_rotated_micro_tiling,
	bw_def_display_micro_tiling,

	//Memory type
	bw_def_gddr5,
	bw_def_hbm,

	//Voltage
	bw_def_high_no_nbp_state_change,
	bw_def_0_72,
	bw_def_0_8,
	bw_def_0_9,

	bw_def_notok = -1,
	bw_def_na = -1
पूर्ण;

काष्ठा bw_calcs_dceip अणु
	क्रमागत bw_calcs_version version;
	uपूर्णांक32_t percent_of_ideal_port_bw_received_after_urgent_latency;
	uपूर्णांक32_t max_average_percent_of_ideal_port_bw_display_can_use_in_normal_प्रणाली_operation;
	uपूर्णांक32_t max_average_percent_of_ideal_drambw_display_can_use_in_normal_प्रणाली_operation;
	bool large_cursor;
	uपूर्णांक32_t cursor_max_outstanding_group_num;
	bool dmअगर_pipe_en_fbc_chunk_tracker;
	काष्ठा bw_fixed dmअगर_request_buffer_size;
	uपूर्णांक32_t lines_पूर्णांकerleaved_पूर्णांकo_lb;
	uपूर्णांक32_t low_घातer_tiling_mode;
	uपूर्णांक32_t chunk_width;
	uपूर्णांक32_t number_of_graphics_pipes;
	uपूर्णांक32_t number_of_underlay_pipes;
	bool display_ग_लिखो_back_supported;
	bool argb_compression_support;
	काष्ठा bw_fixed underlay_vscaler_efficiency6_bit_per_component;
	काष्ठा bw_fixed underlay_vscaler_efficiency8_bit_per_component;
	काष्ठा bw_fixed underlay_vscaler_efficiency10_bit_per_component;
	काष्ठा bw_fixed underlay_vscaler_efficiency12_bit_per_component;
	काष्ठा bw_fixed graphics_vscaler_efficiency6_bit_per_component;
	काष्ठा bw_fixed graphics_vscaler_efficiency8_bit_per_component;
	काष्ठा bw_fixed graphics_vscaler_efficiency10_bit_per_component;
	काष्ठा bw_fixed graphics_vscaler_efficiency12_bit_per_component;
	काष्ठा bw_fixed alpha_vscaler_efficiency;
	uपूर्णांक32_t max_dmअगर_buffer_allocated;
	uपूर्णांक32_t graphics_dmअगर_size;
	uपूर्णांक32_t underlay_luma_dmअगर_size;
	uपूर्णांक32_t underlay_chroma_dmअगर_size;
	bool pre_करोwnscaler_enabled;
	bool underlay_करोwnscale_prefetch_enabled;
	काष्ठा bw_fixed lb_ग_लिखो_pixels_per_dispclk;
	काष्ठा bw_fixed lb_size_per_component444;
	bool graphics_lb_noकरोwnscaling_multi_line_prefetching;
	काष्ठा bw_fixed stutter_and_dram_घड़ी_state_change_gated_beक्रमe_cursor;
	काष्ठा bw_fixed underlay420_luma_lb_size_per_component;
	काष्ठा bw_fixed underlay420_chroma_lb_size_per_component;
	काष्ठा bw_fixed underlay422_lb_size_per_component;
	काष्ठा bw_fixed cursor_chunk_width;
	काष्ठा bw_fixed cursor_dcp_buffer_lines;
	काष्ठा bw_fixed underlay_maximum_width_efficient_क्रम_tiling;
	काष्ठा bw_fixed underlay_maximum_height_efficient_क्रम_tiling;
	काष्ठा bw_fixed peak_pte_request_to_eviction_ratio_limiting_multiple_displays_or_single_rotated_display;
	काष्ठा bw_fixed peak_pte_request_to_eviction_ratio_limiting_single_display_no_rotation;
	काष्ठा bw_fixed minimum_outstanding_pte_request_limit;
	काष्ठा bw_fixed maximum_total_outstanding_pte_requests_allowed_by_saw;
	bool limit_excessive_outstanding_dmअगर_requests;
	काष्ठा bw_fixed linear_mode_line_request_alternation_slice;
	uपूर्णांक32_t scatter_gather_lines_of_pte_prefetching_in_linear_mode;
	uपूर्णांक32_t display_ग_लिखो_back420_luma_mcअगरwr_buffer_size;
	uपूर्णांक32_t display_ग_लिखो_back420_chroma_mcअगरwr_buffer_size;
	काष्ठा bw_fixed request_efficiency;
	काष्ठा bw_fixed dispclk_per_request;
	काष्ठा bw_fixed dispclk_ramping_factor;
	काष्ठा bw_fixed display_pipe_throughput_factor;
	uपूर्णांक32_t scatter_gather_pte_request_rows_in_tiling_mode;
	काष्ठा bw_fixed mcअगरwr_all_surfaces_burst_समय;
पूर्ण;

काष्ठा bw_calcs_vbios अणु
	क्रमागत bw_defines memory_type;
	uपूर्णांक32_t dram_channel_width_in_bits;
	uपूर्णांक32_t number_of_dram_channels;
	uपूर्णांक32_t number_of_dram_banks;
	काष्ठा bw_fixed low_yclk; /*m_hz*/
	काष्ठा bw_fixed mid_yclk; /*m_hz*/
	काष्ठा bw_fixed high_yclk; /*m_hz*/
	काष्ठा bw_fixed low_sclk; /*m_hz*/
	काष्ठा bw_fixed mid1_sclk; /*m_hz*/
	काष्ठा bw_fixed mid2_sclk; /*m_hz*/
	काष्ठा bw_fixed mid3_sclk; /*m_hz*/
	काष्ठा bw_fixed mid4_sclk; /*m_hz*/
	काष्ठा bw_fixed mid5_sclk; /*m_hz*/
	काष्ठा bw_fixed mid6_sclk; /*m_hz*/
	काष्ठा bw_fixed high_sclk; /*m_hz*/
	काष्ठा bw_fixed low_voltage_max_dispclk; /*m_hz*/
	काष्ठा bw_fixed mid_voltage_max_dispclk; /*m_hz*/
	काष्ठा bw_fixed high_voltage_max_dispclk; /*m_hz*/
	काष्ठा bw_fixed low_voltage_max_phyclk;
	काष्ठा bw_fixed mid_voltage_max_phyclk;
	काष्ठा bw_fixed high_voltage_max_phyclk;
	काष्ठा bw_fixed data_वापस_bus_width;
	काष्ठा bw_fixed trc;
	काष्ठा bw_fixed dmअगरmc_urgent_latency;
	काष्ठा bw_fixed stutter_self_refresh_निकास_latency;
	काष्ठा bw_fixed stutter_self_refresh_entry_latency;
	काष्ठा bw_fixed nbp_state_change_latency;
	काष्ठा bw_fixed mcअगरwrmc_urgent_latency;
	bool scatter_gather_enable;
	काष्ठा bw_fixed करोwn_spपढ़ो_percentage;
	uपूर्णांक32_t cursor_width;
	uपूर्णांक32_t average_compression_rate;
	uपूर्णांक32_t number_of_request_slots_gmc_reserves_क्रम_dmअगर_per_channel;
	काष्ठा bw_fixed blackout_duration;
	काष्ठा bw_fixed maximum_blackout_recovery_समय;
पूर्ण;

/*******************************************************************************
 * Temporary data काष्ठाure(s).
 ******************************************************************************/
#घोषणा maximum_number_of_surfaces 12
/*Units : MHz, us */

काष्ठा bw_calcs_data अणु
	/* data क्रम all displays */
	bool display_synchronization_enabled;
	uपूर्णांक32_t number_of_displays;
	क्रमागत bw_defines underlay_surface_type;
	क्रमागत bw_defines panning_and_bezel_adjusपंचांगent;
	क्रमागत bw_defines graphics_tiling_mode;
	uपूर्णांक32_t graphics_lb_bpc;
	uपूर्णांक32_t underlay_lb_bpc;
	क्रमागत bw_defines underlay_tiling_mode;
	क्रमागत bw_defines d0_underlay_mode;
	bool d1_display_ग_लिखो_back_dwb_enable;
	क्रमागत bw_defines d1_underlay_mode;

	bool increase_voltage_to_support_mclk_चयन;
	bool cpup_state_change_enable;
	bool cpuc_state_change_enable;
	bool nbp_state_change_enable;
	bool stutter_mode_enable;
	uपूर्णांक32_t y_clk_level;
	uपूर्णांक32_t sclk_level;
	uपूर्णांक32_t number_of_underlay_surfaces;
	uपूर्णांक32_t number_of_dram_wrchannels;
	uपूर्णांक32_t chunk_request_delay;
	uपूर्णांक32_t number_of_dram_channels;
	क्रमागत bw_defines underlay_micro_tile_mode;
	क्रमागत bw_defines graphics_micro_tile_mode;
	काष्ठा bw_fixed max_phyclk;
	काष्ठा bw_fixed dram_efficiency;
	काष्ठा bw_fixed src_width_after_surface_type;
	काष्ठा bw_fixed src_height_after_surface_type;
	काष्ठा bw_fixed hsr_after_surface_type;
	काष्ठा bw_fixed vsr_after_surface_type;
	काष्ठा bw_fixed src_width_after_rotation;
	काष्ठा bw_fixed src_height_after_rotation;
	काष्ठा bw_fixed hsr_after_rotation;
	काष्ठा bw_fixed vsr_after_rotation;
	काष्ठा bw_fixed source_height_pixels;
	काष्ठा bw_fixed hsr_after_stereo;
	काष्ठा bw_fixed vsr_after_stereo;
	काष्ठा bw_fixed source_width_in_lb;
	काष्ठा bw_fixed lb_line_pitch;
	काष्ठा bw_fixed underlay_maximum_source_efficient_क्रम_tiling;
	काष्ठा bw_fixed num_lines_at_frame_start;
	काष्ठा bw_fixed min_dmअगर_size_in_समय;
	काष्ठा bw_fixed min_mcअगरwr_size_in_समय;
	काष्ठा bw_fixed total_requests_क्रम_dmअगर_size;
	काष्ठा bw_fixed peak_pte_request_to_eviction_ratio_limiting;
	काष्ठा bw_fixed useful_pte_per_pte_request;
	काष्ठा bw_fixed scatter_gather_pte_request_rows;
	काष्ठा bw_fixed scatter_gather_row_height;
	काष्ठा bw_fixed scatter_gather_pte_requests_in_vblank;
	काष्ठा bw_fixed inefficient_linear_pitch_in_bytes;
	काष्ठा bw_fixed cursor_total_data;
	काष्ठा bw_fixed cursor_total_request_groups;
	काष्ठा bw_fixed scatter_gather_total_pte_requests;
	काष्ठा bw_fixed scatter_gather_total_pte_request_groups;
	काष्ठा bw_fixed tile_width_in_pixels;
	काष्ठा bw_fixed dmअगर_total_number_of_data_request_page_बंद_खोलो;
	काष्ठा bw_fixed mcअगरwr_total_number_of_data_request_page_बंद_खोलो;
	काष्ठा bw_fixed bytes_per_page_बंद_खोलो;
	काष्ठा bw_fixed mcअगरwr_total_page_बंद_खोलो_समय;
	काष्ठा bw_fixed total_requests_क्रम_adjusted_dmअगर_size;
	काष्ठा bw_fixed total_dmअगरmc_urgent_trips;
	काष्ठा bw_fixed total_dmअगरmc_urgent_latency;
	काष्ठा bw_fixed total_display_पढ़ोs_required_data;
	काष्ठा bw_fixed total_display_पढ़ोs_required_dram_access_data;
	काष्ठा bw_fixed total_display_ग_लिखोs_required_data;
	काष्ठा bw_fixed total_display_ग_लिखोs_required_dram_access_data;
	काष्ठा bw_fixed display_पढ़ोs_required_data;
	काष्ठा bw_fixed display_पढ़ोs_required_dram_access_data;
	काष्ठा bw_fixed dmअगर_total_page_बंद_खोलो_समय;
	काष्ठा bw_fixed min_cursor_memory_पूर्णांकerface_buffer_size_in_समय;
	काष्ठा bw_fixed min_पढ़ो_buffer_size_in_समय;
	काष्ठा bw_fixed display_पढ़ोs_समय_क्रम_data_transfer;
	काष्ठा bw_fixed display_ग_लिखोs_समय_क्रम_data_transfer;
	काष्ठा bw_fixed dmअगर_required_dram_bandwidth;
	काष्ठा bw_fixed mcअगरwr_required_dram_bandwidth;
	काष्ठा bw_fixed required_dmअगरmc_urgent_latency_क्रम_page_बंद_खोलो;
	काष्ठा bw_fixed required_mcअगरmcwr_urgent_latency;
	काष्ठा bw_fixed required_dram_bandwidth_gbyte_per_second;
	काष्ठा bw_fixed dram_bandwidth;
	काष्ठा bw_fixed dmअगर_required_sclk;
	काष्ठा bw_fixed mcअगरwr_required_sclk;
	काष्ठा bw_fixed required_sclk;
	काष्ठा bw_fixed करोwnspपढ़ो_factor;
	काष्ठा bw_fixed v_scaler_efficiency;
	काष्ठा bw_fixed scaler_limits_factor;
	काष्ठा bw_fixed display_pipe_pixel_throughput;
	काष्ठा bw_fixed total_dispclk_required_with_ramping;
	काष्ठा bw_fixed total_dispclk_required_without_ramping;
	काष्ठा bw_fixed total_पढ़ो_request_bandwidth;
	काष्ठा bw_fixed total_ग_लिखो_request_bandwidth;
	काष्ठा bw_fixed dispclk_required_क्रम_total_पढ़ो_request_bandwidth;
	काष्ठा bw_fixed total_dispclk_required_with_ramping_with_request_bandwidth;
	काष्ठा bw_fixed total_dispclk_required_without_ramping_with_request_bandwidth;
	काष्ठा bw_fixed dispclk;
	काष्ठा bw_fixed blackout_recovery_समय;
	काष्ठा bw_fixed min_pixels_per_data_fअगरo_entry;
	काष्ठा bw_fixed sclk_deep_sleep;
	काष्ठा bw_fixed chunk_request_समय;
	काष्ठा bw_fixed cursor_request_समय;
	काष्ठा bw_fixed line_source_pixels_transfer_समय;
	काष्ठा bw_fixed dmअगरdram_access_efficiency;
	काष्ठा bw_fixed mcअगरwrdram_access_efficiency;
	काष्ठा bw_fixed total_average_bandwidth_no_compression;
	काष्ठा bw_fixed total_average_bandwidth;
	काष्ठा bw_fixed total_stutter_cycle_duration;
	काष्ठा bw_fixed stutter_burst_समय;
	काष्ठा bw_fixed समय_in_self_refresh;
	काष्ठा bw_fixed stutter_efficiency;
	काष्ठा bw_fixed worst_number_of_trips_to_memory;
	काष्ठा bw_fixed immediate_flip_समय;
	काष्ठा bw_fixed latency_क्रम_non_dmअगर_clients;
	काष्ठा bw_fixed latency_क्रम_non_mcअगरwr_clients;
	काष्ठा bw_fixed dmअगरmc_urgent_latency_supported_in_high_sclk_and_yclk;
	काष्ठा bw_fixed nbp_state_dram_speed_change_margin;
	काष्ठा bw_fixed display_पढ़ोs_समय_क्रम_data_transfer_and_urgent_latency;
	काष्ठा bw_fixed dram_speed_change_margin;
	काष्ठा bw_fixed min_vblank_dram_speed_change_margin;
	काष्ठा bw_fixed min_stutter_refresh_duration;
	uपूर्णांक32_t total_stutter_dmअगर_buffer_size;
	uपूर्णांक32_t total_bytes_requested;
	uपूर्णांक32_t min_stutter_dmअगर_buffer_size;
	uपूर्णांक32_t num_stutter_bursts;
	काष्ठा bw_fixed v_blank_nbp_state_dram_speed_change_latency_supported;
	काष्ठा bw_fixed nbp_state_dram_speed_change_latency_supported;
	bool fbc_en[maximum_number_of_surfaces];
	bool lpt_en[maximum_number_of_surfaces];
	bool displays_match_flag[maximum_number_of_surfaces];
	bool use_alpha[maximum_number_of_surfaces];
	bool orthogonal_rotation[maximum_number_of_surfaces];
	bool enable[maximum_number_of_surfaces];
	bool access_one_channel_only[maximum_number_of_surfaces];
	bool scatter_gather_enable_क्रम_pipe[maximum_number_of_surfaces];
	bool पूर्णांकerlace_mode[maximum_number_of_surfaces];
	bool display_pstate_change_enable[maximum_number_of_surfaces];
	bool line_buffer_prefetch[maximum_number_of_surfaces];
	uपूर्णांक32_t bytes_per_pixel[maximum_number_of_surfaces];
	uपूर्णांक32_t max_chunks_non_fbc_mode[maximum_number_of_surfaces];
	uपूर्णांक32_t lb_bpc[maximum_number_of_surfaces];
	uपूर्णांक32_t output_bpphdmi[maximum_number_of_surfaces];
	uपूर्णांक32_t output_bppdp4_lane_hbr[maximum_number_of_surfaces];
	uपूर्णांक32_t output_bppdp4_lane_hbr2[maximum_number_of_surfaces];
	uपूर्णांक32_t output_bppdp4_lane_hbr3[maximum_number_of_surfaces];
	क्रमागत bw_defines stereo_mode[maximum_number_of_surfaces];
	काष्ठा bw_fixed dmअगर_buffer_transfer_समय[maximum_number_of_surfaces];
	काष्ठा bw_fixed displays_with_same_mode[maximum_number_of_surfaces];
	काष्ठा bw_fixed stutter_dmअगर_buffer_size[maximum_number_of_surfaces];
	काष्ठा bw_fixed stutter_refresh_duration[maximum_number_of_surfaces];
	काष्ठा bw_fixed stutter_निकास_watermark[maximum_number_of_surfaces];
	काष्ठा bw_fixed stutter_entry_watermark[maximum_number_of_surfaces];
	काष्ठा bw_fixed h_total[maximum_number_of_surfaces];
	काष्ठा bw_fixed v_total[maximum_number_of_surfaces];
	काष्ठा bw_fixed pixel_rate[maximum_number_of_surfaces];
	काष्ठा bw_fixed src_width[maximum_number_of_surfaces];
	काष्ठा bw_fixed pitch_in_pixels[maximum_number_of_surfaces];
	काष्ठा bw_fixed pitch_in_pixels_after_surface_type[maximum_number_of_surfaces];
	काष्ठा bw_fixed src_height[maximum_number_of_surfaces];
	काष्ठा bw_fixed scale_ratio[maximum_number_of_surfaces];
	काष्ठा bw_fixed h_taps[maximum_number_of_surfaces];
	काष्ठा bw_fixed v_taps[maximum_number_of_surfaces];
	काष्ठा bw_fixed h_scale_ratio[maximum_number_of_surfaces];
	काष्ठा bw_fixed v_scale_ratio[maximum_number_of_surfaces];
	काष्ठा bw_fixed rotation_angle[maximum_number_of_surfaces];
	काष्ठा bw_fixed compression_rate[maximum_number_of_surfaces];
	काष्ठा bw_fixed hsr[maximum_number_of_surfaces];
	काष्ठा bw_fixed vsr[maximum_number_of_surfaces];
	काष्ठा bw_fixed source_width_rounded_up_to_chunks[maximum_number_of_surfaces];
	काष्ठा bw_fixed source_width_pixels[maximum_number_of_surfaces];
	काष्ठा bw_fixed source_height_rounded_up_to_chunks[maximum_number_of_surfaces];
	काष्ठा bw_fixed display_bandwidth[maximum_number_of_surfaces];
	काष्ठा bw_fixed request_bandwidth[maximum_number_of_surfaces];
	काष्ठा bw_fixed bytes_per_request[maximum_number_of_surfaces];
	काष्ठा bw_fixed useful_bytes_per_request[maximum_number_of_surfaces];
	काष्ठा bw_fixed lines_पूर्णांकerleaved_in_mem_access[maximum_number_of_surfaces];
	काष्ठा bw_fixed latency_hiding_lines[maximum_number_of_surfaces];
	काष्ठा bw_fixed lb_partitions[maximum_number_of_surfaces];
	काष्ठा bw_fixed lb_partitions_max[maximum_number_of_surfaces];
	काष्ठा bw_fixed dispclk_required_with_ramping[maximum_number_of_surfaces];
	काष्ठा bw_fixed dispclk_required_without_ramping[maximum_number_of_surfaces];
	काष्ठा bw_fixed data_buffer_size[maximum_number_of_surfaces];
	काष्ठा bw_fixed outstanding_chunk_request_limit[maximum_number_of_surfaces];
	काष्ठा bw_fixed urgent_watermark[maximum_number_of_surfaces];
	काष्ठा bw_fixed nbp_state_change_watermark[maximum_number_of_surfaces];
	काष्ठा bw_fixed v_filter_init[maximum_number_of_surfaces];
	काष्ठा bw_fixed stutter_cycle_duration[maximum_number_of_surfaces];
	काष्ठा bw_fixed average_bandwidth[maximum_number_of_surfaces];
	काष्ठा bw_fixed average_bandwidth_no_compression[maximum_number_of_surfaces];
	काष्ठा bw_fixed scatter_gather_pte_request_limit[maximum_number_of_surfaces];
	काष्ठा bw_fixed lb_size_per_component[maximum_number_of_surfaces];
	काष्ठा bw_fixed memory_chunk_size_in_bytes[maximum_number_of_surfaces];
	काष्ठा bw_fixed pipe_chunk_size_in_bytes[maximum_number_of_surfaces];
	काष्ठा bw_fixed number_of_trips_to_memory_क्रम_getting_apte_row[maximum_number_of_surfaces];
	काष्ठा bw_fixed adjusted_data_buffer_size[maximum_number_of_surfaces];
	काष्ठा bw_fixed adjusted_data_buffer_size_in_memory[maximum_number_of_surfaces];
	काष्ठा bw_fixed pixels_per_data_fअगरo_entry[maximum_number_of_surfaces];
	काष्ठा bw_fixed scatter_gather_pte_requests_in_row[maximum_number_of_surfaces];
	काष्ठा bw_fixed pte_request_per_chunk[maximum_number_of_surfaces];
	काष्ठा bw_fixed scatter_gather_page_width[maximum_number_of_surfaces];
	काष्ठा bw_fixed scatter_gather_page_height[maximum_number_of_surfaces];
	काष्ठा bw_fixed lb_lines_in_per_line_out_in_beginning_of_frame[maximum_number_of_surfaces];
	काष्ठा bw_fixed lb_lines_in_per_line_out_in_middle_of_frame[maximum_number_of_surfaces];
	काष्ठा bw_fixed cursor_width_pixels[maximum_number_of_surfaces];
	काष्ठा bw_fixed minimum_latency_hiding[maximum_number_of_surfaces];
	काष्ठा bw_fixed maximum_latency_hiding[maximum_number_of_surfaces];
	काष्ठा bw_fixed minimum_latency_hiding_with_cursor[maximum_number_of_surfaces];
	काष्ठा bw_fixed maximum_latency_hiding_with_cursor[maximum_number_of_surfaces];
	काष्ठा bw_fixed src_pixels_क्रम_first_output_pixel[maximum_number_of_surfaces];
	काष्ठा bw_fixed src_pixels_क्रम_last_output_pixel[maximum_number_of_surfaces];
	काष्ठा bw_fixed src_data_क्रम_first_output_pixel[maximum_number_of_surfaces];
	काष्ठा bw_fixed src_data_क्रम_last_output_pixel[maximum_number_of_surfaces];
	काष्ठा bw_fixed active_समय[maximum_number_of_surfaces];
	काष्ठा bw_fixed horizontal_blank_and_chunk_granularity_factor[maximum_number_of_surfaces];
	काष्ठा bw_fixed cursor_latency_hiding[maximum_number_of_surfaces];
	काष्ठा bw_fixed v_blank_dram_speed_change_margin[maximum_number_of_surfaces];
	uपूर्णांक32_t num_displays_with_margin[3][8];
	काष्ठा bw_fixed dmअगर_burst_समय[3][8];
	काष्ठा bw_fixed mcअगरwr_burst_समय[3][8];
	काष्ठा bw_fixed line_source_transfer_समय[maximum_number_of_surfaces][3][8];
	काष्ठा bw_fixed dram_speed_change_line_source_transfer_समय[maximum_number_of_surfaces][3][8];
	काष्ठा bw_fixed min_dram_speed_change_margin[3][8];
	काष्ठा bw_fixed dispclk_required_क्रम_dram_speed_change[3][8];
	काष्ठा bw_fixed dispclk_required_क्रम_dram_speed_change_pipe[3][8];
	काष्ठा bw_fixed blackout_duration_margin[3][8];
	काष्ठा bw_fixed dispclk_required_क्रम_blackout_duration[3][8];
	काष्ठा bw_fixed dispclk_required_क्रम_blackout_recovery[3][8];
	काष्ठा bw_fixed dmअगर_required_sclk_क्रम_urgent_latency[6];
पूर्ण;

/**
 * Initialize काष्ठाures with data which will NOT change at runसमय.
 */
व्योम bw_calcs_init(
	काष्ठा bw_calcs_dceip *bw_dceip,
	काष्ठा bw_calcs_vbios *bw_vbios,
	काष्ठा hw_asic_id asic_id);

/**
 * Return:
 *	true -	Display(s) configuration supported.
 *		In this हाल 'calcs_output' contains data क्रम HW programming
 *	false - Display(s) configuration not supported (not enough bandwidth).
 */
bool bw_calcs(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा bw_calcs_dceip *dceip,
	स्थिर काष्ठा bw_calcs_vbios *vbios,
	स्थिर काष्ठा pipe_ctx *pipe,
	पूर्णांक pipe_count,
	काष्ठा dce_bw_output *calcs_output);

#पूर्ण_अगर /* __BANDWIDTH_CALCS_H__ */

