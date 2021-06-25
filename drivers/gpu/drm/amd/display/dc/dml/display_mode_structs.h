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

#समावेश "dc_features.h"
#समावेश "display_mode_enums.h"

#अगर_अघोषित __DISPLAY_MODE_STRUCTS_H__
#घोषणा __DISPLAY_MODE_STRUCTS_H__

प्रकार काष्ठा _vcs_dpi_voltage_scaling_st voltage_scaling_st;
प्रकार काष्ठा _vcs_dpi_soc_bounding_box_st soc_bounding_box_st;
प्रकार काष्ठा _vcs_dpi_ip_params_st ip_params_st;
प्रकार काष्ठा _vcs_dpi_display_pipe_source_params_st display_pipe_source_params_st;
प्रकार काष्ठा _vcs_dpi_display_output_params_st display_output_params_st;
प्रकार काष्ठा _vcs_dpi_scaler_ratio_depth_st scaler_ratio_depth_st;
प्रकार काष्ठा _vcs_dpi_scaler_taps_st scaler_taps_st;
प्रकार काष्ठा _vcs_dpi_display_pipe_dest_params_st display_pipe_dest_params_st;
प्रकार काष्ठा _vcs_dpi_display_pipe_params_st display_pipe_params_st;
प्रकार काष्ठा _vcs_dpi_display_घड़ीs_and_cfg_st display_घड़ीs_and_cfg_st;
प्रकार काष्ठा _vcs_dpi_display_e2e_pipe_params_st display_e2e_pipe_params_st;
प्रकार काष्ठा _vcs_dpi_display_data_rq_misc_params_st display_data_rq_misc_params_st;
प्रकार काष्ठा _vcs_dpi_display_data_rq_sizing_params_st display_data_rq_sizing_params_st;
प्रकार काष्ठा _vcs_dpi_display_data_rq_dlg_params_st display_data_rq_dlg_params_st;
प्रकार काष्ठा _vcs_dpi_display_rq_dlg_params_st display_rq_dlg_params_st;
प्रकार काष्ठा _vcs_dpi_display_rq_sizing_params_st display_rq_sizing_params_st;
प्रकार काष्ठा _vcs_dpi_display_rq_misc_params_st display_rq_misc_params_st;
प्रकार काष्ठा _vcs_dpi_display_rq_params_st display_rq_params_st;
प्रकार काष्ठा _vcs_dpi_display_dlg_regs_st display_dlg_regs_st;
प्रकार काष्ठा _vcs_dpi_display_ttu_regs_st display_ttu_regs_st;
प्रकार काष्ठा _vcs_dpi_display_data_rq_regs_st display_data_rq_regs_st;
प्रकार काष्ठा _vcs_dpi_display_rq_regs_st display_rq_regs_st;
प्रकार काष्ठा _vcs_dpi_display_dlg_sys_params_st display_dlg_sys_params_st;
प्रकार काष्ठा _vcs_dpi_display_arb_params_st display_arb_params_st;

काष्ठा _vcs_dpi_voltage_scaling_st अणु
	पूर्णांक state;
	द्विगुन dscclk_mhz;
	द्विगुन dcfclk_mhz;
	द्विगुन socclk_mhz;
	द्विगुन phyclk_d18_mhz;
	द्विगुन dram_speed_mts;
	द्विगुन fabricclk_mhz;
	द्विगुन dispclk_mhz;
	द्विगुन dram_bw_per_chan_gbps;
	द्विगुन phyclk_mhz;
	द्विगुन dppclk_mhz;
	द्विगुन dtbclk_mhz;
पूर्ण;

काष्ठा _vcs_dpi_soc_bounding_box_st अणु
	काष्ठा _vcs_dpi_voltage_scaling_st घड़ी_limits[DC__VOLTAGE_STATES];
	अचिन्हित पूर्णांक num_states;
	द्विगुन sr_निकास_समय_us;
	द्विगुन sr_enter_plus_निकास_समय_us;
	द्विगुन urgent_latency_us;
	द्विगुन urgent_latency_pixel_data_only_us;
	द्विगुन urgent_latency_pixel_mixed_with_vm_data_us;
	द्विगुन urgent_latency_vm_data_only_us;
	द्विगुन ग_लिखोback_latency_us;
	द्विगुन ideal_dram_bw_after_urgent_percent;
	द्विगुन pct_ideal_dram_sdp_bw_after_urgent_pixel_only; // PercentOfIdealDRAMFabricAndSDPPortBWReceivedAfterUrgLatencyPixelDataOnly
	द्विगुन pct_ideal_dram_sdp_bw_after_urgent_pixel_and_vm;
	द्विगुन pct_ideal_dram_sdp_bw_after_urgent_vm_only;
	द्विगुन pct_ideal_sdp_bw_after_urgent;
	द्विगुन max_avg_sdp_bw_use_normal_percent;
	द्विगुन max_avg_dram_bw_use_normal_percent;
	अचिन्हित पूर्णांक max_request_size_bytes;
	द्विगुन करोwnspपढ़ो_percent;
	द्विगुन dram_page_खोलो_समय_ns;
	द्विगुन dram_rw_turnaround_समय_ns;
	द्विगुन dram_वापस_buffer_per_channel_bytes;
	द्विगुन dram_channel_width_bytes;
	द्विगुन fabric_datapath_to_dcn_data_वापस_bytes;
	द्विगुन dcn_करोwnspपढ़ो_percent;
	द्विगुन dispclk_dppclk_vco_speed_mhz;
	द्विगुन dfs_vco_period_ps;
	अचिन्हित पूर्णांक urgent_out_of_order_वापस_per_channel_pixel_only_bytes;
	अचिन्हित पूर्णांक urgent_out_of_order_वापस_per_channel_pixel_and_vm_bytes;
	अचिन्हित पूर्णांक urgent_out_of_order_वापस_per_channel_vm_only_bytes;
	अचिन्हित पूर्णांक round_trip_ping_latency_dcfclk_cycles;
	अचिन्हित पूर्णांक urgent_out_of_order_वापस_per_channel_bytes;
	अचिन्हित पूर्णांक channel_पूर्णांकerleave_bytes;
	अचिन्हित पूर्णांक num_banks;
	अचिन्हित पूर्णांक num_chans;
	अचिन्हित पूर्णांक vmm_page_size_bytes;
	अचिन्हित पूर्णांक hostvm_min_page_size_bytes;
	अचिन्हित पूर्णांक gpuvm_min_page_size_bytes;
	द्विगुन dram_घड़ी_change_latency_us;
	द्विगुन dummy_pstate_latency_us;
	द्विगुन ग_लिखोback_dram_घड़ी_change_latency_us;
	अचिन्हित पूर्णांक वापस_bus_width_bytes;
	अचिन्हित पूर्णांक voltage_override;
	द्विगुन xfc_bus_transport_समय_us;
	द्विगुन xfc_xbuf_latency_tolerance_us;
	पूर्णांक use_urgent_burst_bw;
	द्विगुन min_dcfclk;
	bool करो_urgent_latency_adjusपंचांगent;
	द्विगुन urgent_latency_adjusपंचांगent_fabric_घड़ी_component_us;
	द्विगुन urgent_latency_adjusपंचांगent_fabric_घड़ी_reference_mhz;
	bool disable_dram_घड़ी_change_vactive_support;
	bool allow_dram_घड़ी_one_display_vactive;
	क्रमागत self_refresh_affinity allow_dram_self_refresh_or_dram_घड़ी_change_in_vblank;
पूर्ण;

काष्ठा _vcs_dpi_ip_params_st अणु
	bool use_min_dcfclk;
	bool clamp_min_dcfclk;
	bool gpuvm_enable;
	bool hostvm_enable;
	bool dsc422_native_support;
	अचिन्हित पूर्णांक gpuvm_max_page_table_levels;
	अचिन्हित पूर्णांक hostvm_max_page_table_levels;
	अचिन्हित पूर्णांक hostvm_cached_page_table_levels;
	अचिन्हित पूर्णांक pte_group_size_bytes;
	अचिन्हित पूर्णांक max_पूर्णांकer_dcn_tile_repeaters;
	अचिन्हित पूर्णांक num_dsc;
	अचिन्हित पूर्णांक odm_capable;
	अचिन्हित पूर्णांक rob_buffer_size_kbytes;
	अचिन्हित पूर्णांक det_buffer_size_kbytes;
	अचिन्हित पूर्णांक dpte_buffer_size_in_pte_reqs_luma;
	अचिन्हित पूर्णांक dpte_buffer_size_in_pte_reqs_chroma;
	अचिन्हित पूर्णांक pde_proc_buffer_size_64k_reqs;
	अचिन्हित पूर्णांक dpp_output_buffer_pixels;
	अचिन्हित पूर्णांक opp_output_buffer_lines;
	अचिन्हित पूर्णांक pixel_chunk_size_kbytes;
	अचिन्हित अक्षर pte_enable;
	अचिन्हित पूर्णांक pte_chunk_size_kbytes;
	अचिन्हित पूर्णांक meta_chunk_size_kbytes;
	अचिन्हित पूर्णांक min_meta_chunk_size_bytes;
	अचिन्हित पूर्णांक ग_लिखोback_chunk_size_kbytes;
	अचिन्हित पूर्णांक line_buffer_size_bits;
	अचिन्हित पूर्णांक max_line_buffer_lines;
	अचिन्हित पूर्णांक ग_लिखोback_luma_buffer_size_kbytes;
	अचिन्हित पूर्णांक ग_लिखोback_chroma_buffer_size_kbytes;
	अचिन्हित पूर्णांक ग_लिखोback_chroma_line_buffer_width_pixels;

	अचिन्हित पूर्णांक ग_लिखोback_पूर्णांकerface_buffer_size_kbytes;
	अचिन्हित पूर्णांक ग_लिखोback_line_buffer_buffer_size;

	अचिन्हित पूर्णांक ग_लिखोback_10bpc420_supported;
	द्विगुन ग_लिखोback_max_hscl_ratio;
	द्विगुन ग_लिखोback_max_vscl_ratio;
	द्विगुन ग_लिखोback_min_hscl_ratio;
	द्विगुन ग_लिखोback_min_vscl_ratio;
	अचिन्हित पूर्णांक maximum_dsc_bits_per_component;
	अचिन्हित पूर्णांक ग_लिखोback_max_hscl_taps;
	अचिन्हित पूर्णांक ग_लिखोback_max_vscl_taps;
	अचिन्हित पूर्णांक ग_लिखोback_line_buffer_luma_buffer_size;
	अचिन्हित पूर्णांक ग_लिखोback_line_buffer_chroma_buffer_size;

	अचिन्हित पूर्णांक max_page_table_levels;
	अचिन्हित पूर्णांक max_num_dpp;
	अचिन्हित पूर्णांक max_num_otg;
	अचिन्हित पूर्णांक cursor_chunk_size;
	अचिन्हित पूर्णांक cursor_buffer_size;
	अचिन्हित पूर्णांक max_num_wb;
	अचिन्हित पूर्णांक max_dchub_pscl_bw_pix_per_clk;
	अचिन्हित पूर्णांक max_pscl_lb_bw_pix_per_clk;
	अचिन्हित पूर्णांक max_lb_vscl_bw_pix_per_clk;
	अचिन्हित पूर्णांक max_vscl_hscl_bw_pix_per_clk;
	द्विगुन max_hscl_ratio;
	द्विगुन max_vscl_ratio;
	अचिन्हित पूर्णांक hscl_mults;
	अचिन्हित पूर्णांक vscl_mults;
	अचिन्हित पूर्णांक max_hscl_taps;
	अचिन्हित पूर्णांक max_vscl_taps;
	अचिन्हित पूर्णांक xfc_supported;
	अचिन्हित पूर्णांक ptoi_supported;
	अचिन्हित पूर्णांक gfx7_compat_tiling_supported;

	bool odm_combine_4to1_supported;
	bool dynamic_metadata_vm_enabled;
	अचिन्हित पूर्णांक max_num_hdmi_frl_outमाला_दो;

	अचिन्हित पूर्णांक xfc_fill_स्थिरant_bytes;
	द्विगुन dispclk_ramp_margin_percent;
	द्विगुन xfc_fill_bw_overhead_percent;
	द्विगुन underscan_factor;
	अचिन्हित पूर्णांक min_vblank_lines;
	अचिन्हित पूर्णांक dppclk_delay_subtotal;
	अचिन्हित पूर्णांक dispclk_delay_subtotal;
	द्विगुन dcfclk_cstate_latency;
	अचिन्हित पूर्णांक dppclk_delay_scl;
	अचिन्हित पूर्णांक dppclk_delay_scl_lb_only;
	अचिन्हित पूर्णांक dppclk_delay_cnvc_क्रमmatter;
	अचिन्हित पूर्णांक dppclk_delay_cnvc_cursor;
	अचिन्हित पूर्णांक is_line_buffer_bpp_fixed;
	अचिन्हित पूर्णांक line_buffer_fixed_bpp;
	अचिन्हित पूर्णांक dcc_supported;

	अचिन्हित पूर्णांक IsLineBufferBppFixed;
	अचिन्हित पूर्णांक LineBufferFixedBpp;
	अचिन्हित पूर्णांक can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one;
	अचिन्हित पूर्णांक bug_क्रमcing_LC_req_same_size_fixed;
	अचिन्हित पूर्णांक number_of_cursors;
पूर्ण;

काष्ठा _vcs_dpi_display_xfc_params_st अणु
	द्विगुन xfc_tslv_vपढ़ोy_offset_us;
	द्विगुन xfc_tslv_vupdate_width_us;
	द्विगुन xfc_tslv_vupdate_offset_us;
	पूर्णांक xfc_slv_chunk_size_bytes;
पूर्ण;

काष्ठा _vcs_dpi_display_pipe_source_params_st अणु
	पूर्णांक source_क्रमmat;
	द्विगुन dcc_fraction_of_zs_req_luma;
	द्विगुन dcc_fraction_of_zs_req_chroma;
	अचिन्हित अक्षर dcc;
	अचिन्हित पूर्णांक dcc_rate;
	अचिन्हित पूर्णांक dcc_rate_chroma;
	अचिन्हित अक्षर dcc_use_global;
	अचिन्हित अक्षर vm;
	bool unbounded_req_mode;
	bool gpuvm;    // gpuvm enabled
	bool hostvm;    // hostvm enabled
	bool gpuvm_levels_क्रमce_en;
	अचिन्हित पूर्णांक gpuvm_levels_क्रमce;
	bool hostvm_levels_क्रमce_en;
	अचिन्हित पूर्णांक hostvm_levels_क्रमce;
	पूर्णांक source_scan;
	पूर्णांक sw_mode;
	पूर्णांक macro_tile_size;
	अचिन्हित पूर्णांक surface_width_y;
	अचिन्हित पूर्णांक surface_height_y;
	अचिन्हित पूर्णांक surface_width_c;
	अचिन्हित पूर्णांक surface_height_c;
	अचिन्हित पूर्णांक viewport_width;
	अचिन्हित पूर्णांक viewport_height;
	अचिन्हित पूर्णांक viewport_y_y;
	अचिन्हित पूर्णांक viewport_y_c;
	अचिन्हित पूर्णांक viewport_width_c;
	अचिन्हित पूर्णांक viewport_height_c;
	अचिन्हित पूर्णांक data_pitch;
	अचिन्हित पूर्णांक data_pitch_c;
	अचिन्हित पूर्णांक meta_pitch;
	अचिन्हित पूर्णांक meta_pitch_c;
	अचिन्हित पूर्णांक cur0_src_width;
	पूर्णांक cur0_bpp;
	अचिन्हित पूर्णांक cur1_src_width;
	पूर्णांक cur1_bpp;
	पूर्णांक num_cursors;
	अचिन्हित अक्षर is_hsplit;
	अचिन्हित अक्षर dynamic_metadata_enable;
	अचिन्हित पूर्णांक dynamic_metadata_lines_beक्रमe_active;
	अचिन्हित पूर्णांक dynamic_metadata_xmit_bytes;
	अचिन्हित पूर्णांक hsplit_grp;
	अचिन्हित अक्षर xfc_enable;
	अचिन्हित अक्षर xfc_slave;
	अचिन्हित अक्षर immediate_flip;
	काष्ठा _vcs_dpi_display_xfc_params_st xfc_params;
	//क्रम vstartuplines calculation मुक्तsync
	अचिन्हित अक्षर v_total_min;
	अचिन्हित अक्षर v_total_max;
पूर्ण;
काष्ठा ग_लिखोback_st अणु
	पूर्णांक wb_src_height;
	पूर्णांक wb_src_width;
	पूर्णांक wb_dst_width;
	पूर्णांक wb_dst_height;
	पूर्णांक wb_pixel_क्रमmat;
	पूर्णांक wb_htaps_luma;
	पूर्णांक wb_vtaps_luma;
	पूर्णांक wb_htaps_chroma;
	पूर्णांक wb_vtaps_chroma;
	द्विगुन wb_hratio;
	द्विगुन wb_vratio;
पूर्ण;

काष्ठा _vcs_dpi_display_output_params_st अणु
	पूर्णांक dp_lanes;
	द्विगुन output_bpp;
	अचिन्हित पूर्णांक dsc_input_bpc;
	पूर्णांक dsc_enable;
	पूर्णांक wb_enable;
	पूर्णांक num_active_wb;
	पूर्णांक output_type;
	पूर्णांक is_भव;
	पूर्णांक output_क्रमmat;
	पूर्णांक dsc_slices;
	पूर्णांक max_audio_sample_rate;
	काष्ठा ग_लिखोback_st wb;
पूर्ण;

काष्ठा _vcs_dpi_scaler_ratio_depth_st अणु
	द्विगुन hscl_ratio;
	द्विगुन vscl_ratio;
	द्विगुन hscl_ratio_c;
	द्विगुन vscl_ratio_c;
	द्विगुन vinit;
	द्विगुन vinit_c;
	द्विगुन vinit_bot;
	द्विगुन vinit_bot_c;
	पूर्णांक lb_depth;
	पूर्णांक scl_enable;
पूर्ण;

काष्ठा _vcs_dpi_scaler_taps_st अणु
	अचिन्हित पूर्णांक htaps;
	अचिन्हित पूर्णांक vtaps;
	अचिन्हित पूर्णांक htaps_c;
	अचिन्हित पूर्णांक vtaps_c;
पूर्ण;

काष्ठा _vcs_dpi_display_pipe_dest_params_st अणु
	अचिन्हित पूर्णांक recout_width;
	अचिन्हित पूर्णांक recout_height;
	अचिन्हित पूर्णांक full_recout_width;
	अचिन्हित पूर्णांक full_recout_height;
	अचिन्हित पूर्णांक hblank_start;
	अचिन्हित पूर्णांक hblank_end;
	अचिन्हित पूर्णांक vblank_start;
	अचिन्हित पूर्णांक vblank_end;
	अचिन्हित पूर्णांक htotal;
	अचिन्हित पूर्णांक vtotal;
	अचिन्हित पूर्णांक vfront_porch;
	अचिन्हित पूर्णांक vactive;
	अचिन्हित पूर्णांक hactive;
	अचिन्हित पूर्णांक vstartup_start;
	अचिन्हित पूर्णांक vupdate_offset;
	अचिन्हित पूर्णांक vupdate_width;
	अचिन्हित पूर्णांक vपढ़ोy_offset;
	अचिन्हित अक्षर पूर्णांकerlaced;
	द्विगुन pixel_rate_mhz;
	अचिन्हित अक्षर synchronized_vblank_all_planes;
	अचिन्हित अक्षर otg_inst;
	अचिन्हित पूर्णांक odm_combine;
	अचिन्हित अक्षर use_maximum_vstartup;
	अचिन्हित पूर्णांक vtotal_max;
	अचिन्हित पूर्णांक vtotal_min;
पूर्ण;

काष्ठा _vcs_dpi_display_pipe_params_st अणु
	display_pipe_source_params_st src;
	display_pipe_dest_params_st dest;
	scaler_ratio_depth_st scale_ratio_depth;
	scaler_taps_st scale_taps;
पूर्ण;

काष्ठा _vcs_dpi_display_घड़ीs_and_cfg_st अणु
	पूर्णांक voltage;
	द्विगुन dppclk_mhz;
	द्विगुन refclk_mhz;
	द्विगुन dispclk_mhz;
	द्विगुन dcfclk_mhz;
	द्विगुन socclk_mhz;
पूर्ण;

काष्ठा _vcs_dpi_display_e2e_pipe_params_st अणु
	display_pipe_params_st pipe;
	display_output_params_st करोut;
	display_घड़ीs_and_cfg_st clks_cfg;
पूर्ण;

काष्ठा _vcs_dpi_display_data_rq_misc_params_st अणु
	अचिन्हित पूर्णांक full_swath_bytes;
	अचिन्हित पूर्णांक stored_swath_bytes;
	अचिन्हित पूर्णांक blk256_height;
	अचिन्हित पूर्णांक blk256_width;
	अचिन्हित पूर्णांक req_height;
	अचिन्हित पूर्णांक req_width;
पूर्ण;

काष्ठा _vcs_dpi_display_data_rq_sizing_params_st अणु
	अचिन्हित पूर्णांक chunk_bytes;
	अचिन्हित पूर्णांक min_chunk_bytes;
	अचिन्हित पूर्णांक meta_chunk_bytes;
	अचिन्हित पूर्णांक min_meta_chunk_bytes;
	अचिन्हित पूर्णांक mpte_group_bytes;
	अचिन्हित पूर्णांक dpte_group_bytes;
पूर्ण;

काष्ठा _vcs_dpi_display_data_rq_dlg_params_st अणु
	अचिन्हित पूर्णांक swath_width_ub;
	अचिन्हित पूर्णांक swath_height;
	अचिन्हित पूर्णांक req_per_swath_ub;
	अचिन्हित पूर्णांक meta_pte_bytes_per_frame_ub;
	अचिन्हित पूर्णांक dpte_req_per_row_ub;
	अचिन्हित पूर्णांक dpte_groups_per_row_ub;
	अचिन्हित पूर्णांक dpte_row_height;
	अचिन्हित पूर्णांक dpte_bytes_per_row_ub;
	अचिन्हित पूर्णांक meta_chunks_per_row_ub;
	अचिन्हित पूर्णांक meta_req_per_row_ub;
	अचिन्हित पूर्णांक meta_row_height;
	अचिन्हित पूर्णांक meta_bytes_per_row_ub;
पूर्ण;

काष्ठा _vcs_dpi_display_rq_dlg_params_st अणु
	display_data_rq_dlg_params_st rq_l;
	display_data_rq_dlg_params_st rq_c;
पूर्ण;

काष्ठा _vcs_dpi_display_rq_sizing_params_st अणु
	display_data_rq_sizing_params_st rq_l;
	display_data_rq_sizing_params_st rq_c;
पूर्ण;

काष्ठा _vcs_dpi_display_rq_misc_params_st अणु
	display_data_rq_misc_params_st rq_l;
	display_data_rq_misc_params_st rq_c;
पूर्ण;

काष्ठा _vcs_dpi_display_rq_params_st अणु
	अचिन्हित अक्षर yuv420;
	अचिन्हित अक्षर yuv420_10bpc;
	अचिन्हित अक्षर rgbe_alpha;
	display_rq_misc_params_st misc;
	display_rq_sizing_params_st sizing;
	display_rq_dlg_params_st dlg;
पूर्ण;

काष्ठा _vcs_dpi_display_dlg_regs_st अणु
	अचिन्हित पूर्णांक refcyc_h_blank_end;
	अचिन्हित पूर्णांक dlg_vblank_end;
	अचिन्हित पूर्णांक min_dst_y_next_start;
	अचिन्हित पूर्णांक refcyc_per_htotal;
	अचिन्हित पूर्णांक refcyc_x_after_scaler;
	अचिन्हित पूर्णांक dst_y_after_scaler;
	अचिन्हित पूर्णांक dst_y_prefetch;
	अचिन्हित पूर्णांक dst_y_per_vm_vblank;
	अचिन्हित पूर्णांक dst_y_per_row_vblank;
	अचिन्हित पूर्णांक dst_y_per_vm_flip;
	अचिन्हित पूर्णांक dst_y_per_row_flip;
	अचिन्हित पूर्णांक ref_freq_to_pix_freq;
	अचिन्हित पूर्णांक vratio_prefetch;
	अचिन्हित पूर्णांक vratio_prefetch_c;
	अचिन्हित पूर्णांक refcyc_per_pte_group_vblank_l;
	अचिन्हित पूर्णांक refcyc_per_pte_group_vblank_c;
	अचिन्हित पूर्णांक refcyc_per_meta_chunk_vblank_l;
	अचिन्हित पूर्णांक refcyc_per_meta_chunk_vblank_c;
	अचिन्हित पूर्णांक refcyc_per_pte_group_flip_l;
	अचिन्हित पूर्णांक refcyc_per_pte_group_flip_c;
	अचिन्हित पूर्णांक refcyc_per_meta_chunk_flip_l;
	अचिन्हित पूर्णांक refcyc_per_meta_chunk_flip_c;
	अचिन्हित पूर्णांक dst_y_per_pte_row_nom_l;
	अचिन्हित पूर्णांक dst_y_per_pte_row_nom_c;
	अचिन्हित पूर्णांक refcyc_per_pte_group_nom_l;
	अचिन्हित पूर्णांक refcyc_per_pte_group_nom_c;
	अचिन्हित पूर्णांक dst_y_per_meta_row_nom_l;
	अचिन्हित पूर्णांक dst_y_per_meta_row_nom_c;
	अचिन्हित पूर्णांक refcyc_per_meta_chunk_nom_l;
	अचिन्हित पूर्णांक refcyc_per_meta_chunk_nom_c;
	अचिन्हित पूर्णांक refcyc_per_line_delivery_pre_l;
	अचिन्हित पूर्णांक refcyc_per_line_delivery_pre_c;
	अचिन्हित पूर्णांक refcyc_per_line_delivery_l;
	अचिन्हित पूर्णांक refcyc_per_line_delivery_c;
	अचिन्हित पूर्णांक chunk_hdl_adjust_cur0;
	अचिन्हित पूर्णांक chunk_hdl_adjust_cur1;
	अचिन्हित पूर्णांक vपढ़ोy_after_vcount0;
	अचिन्हित पूर्णांक dst_y_offset_cur0;
	अचिन्हित पूर्णांक dst_y_offset_cur1;
	अचिन्हित पूर्णांक xfc_reg_transfer_delay;
	अचिन्हित पूर्णांक xfc_reg_preअक्षरge_delay;
	अचिन्हित पूर्णांक xfc_reg_remote_surface_flip_latency;
	अचिन्हित पूर्णांक xfc_reg_prefetch_margin;
	अचिन्हित पूर्णांक dst_y_delta_drq_limit;
	अचिन्हित पूर्णांक refcyc_per_vm_group_vblank;
	अचिन्हित पूर्णांक refcyc_per_vm_group_flip;
	अचिन्हित पूर्णांक refcyc_per_vm_req_vblank;
	अचिन्हित पूर्णांक refcyc_per_vm_req_flip;
	अचिन्हित पूर्णांक refcyc_per_vm_dmdata;
	अचिन्हित पूर्णांक dmdata_dl_delta;
पूर्ण;

काष्ठा _vcs_dpi_display_ttu_regs_st अणु
	अचिन्हित पूर्णांक qos_level_low_wm;
	अचिन्हित पूर्णांक qos_level_high_wm;
	अचिन्हित पूर्णांक min_ttu_vblank;
	अचिन्हित पूर्णांक qos_level_flip;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_l;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_c;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_cur0;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_cur1;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_pre_l;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_pre_c;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_pre_cur0;
	अचिन्हित पूर्णांक refcyc_per_req_delivery_pre_cur1;
	अचिन्हित पूर्णांक qos_level_fixed_l;
	अचिन्हित पूर्णांक qos_level_fixed_c;
	अचिन्हित पूर्णांक qos_level_fixed_cur0;
	अचिन्हित पूर्णांक qos_level_fixed_cur1;
	अचिन्हित पूर्णांक qos_ramp_disable_l;
	अचिन्हित पूर्णांक qos_ramp_disable_c;
	अचिन्हित पूर्णांक qos_ramp_disable_cur0;
	अचिन्हित पूर्णांक qos_ramp_disable_cur1;
पूर्ण;

काष्ठा _vcs_dpi_display_data_rq_regs_st अणु
	अचिन्हित पूर्णांक chunk_size;
	अचिन्हित पूर्णांक min_chunk_size;
	अचिन्हित पूर्णांक meta_chunk_size;
	अचिन्हित पूर्णांक min_meta_chunk_size;
	अचिन्हित पूर्णांक dpte_group_size;
	अचिन्हित पूर्णांक mpte_group_size;
	अचिन्हित पूर्णांक swath_height;
	अचिन्हित पूर्णांक pte_row_height_linear;
पूर्ण;

काष्ठा _vcs_dpi_display_rq_regs_st अणु
	display_data_rq_regs_st rq_regs_l;
	display_data_rq_regs_st rq_regs_c;
	अचिन्हित पूर्णांक drq_expansion_mode;
	अचिन्हित पूर्णांक prq_expansion_mode;
	अचिन्हित पूर्णांक mrq_expansion_mode;
	अचिन्हित पूर्णांक crq_expansion_mode;
	अचिन्हित पूर्णांक plane1_base_address;
पूर्ण;

काष्ठा _vcs_dpi_display_dlg_sys_params_st अणु
	द्विगुन t_mclk_wm_us;
	द्विगुन t_urg_wm_us;
	द्विगुन t_sr_wm_us;
	द्विगुन t_extra_us;
	द्विगुन mem_trip_us;
	द्विगुन t_srx_delay_us;
	द्विगुन deepsleep_dcfclk_mhz;
	द्विगुन total_flip_bw;
	अचिन्हित पूर्णांक total_flip_bytes;
पूर्ण;

काष्ठा _vcs_dpi_display_arb_params_st अणु
	पूर्णांक max_req_outstanding;
	पूर्णांक min_req_outstanding;
	पूर्णांक sat_level_us;
पूर्ण;

#पूर्ण_अगर /*__DISPLAY_MODE_STRUCTS_H__*/
