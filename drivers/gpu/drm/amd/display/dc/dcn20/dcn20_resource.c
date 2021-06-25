<शैली गुरु>
/*
* Copyright 2016 Advanced Micro Devices, Inc.
 * Copyright 2019 Raptor Engineering, LLC
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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"
#समावेश "dc.h"

#समावेश "dcn20_init.h"

#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "dcn20/dcn20_resource.h"

#समावेश "dcn10/dcn10_hubp.h"
#समावेश "dcn10/dcn10_ipp.h"
#समावेश "dcn20_hubbub.h"
#समावेश "dcn20_mpc.h"
#समावेश "dcn20_hubp.h"
#समावेश "irq/dcn20/irq_service_dcn20.h"
#समावेश "dcn20_dpp.h"
#समावेश "dcn20_optc.h"
#समावेश "dcn20_hwseq.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dcn10/dcn10_resource.h"
#समावेश "dcn20_opp.h"

#समावेश "dcn20_dsc.h"

#समावेश "dcn20_link_encoder.h"
#समावेश "dcn20_stream_encoder.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "virtual/virtual_stream_encoder.h"
#समावेश "dce110/dce110_resource.h"
#समावेश "dml/display_mode_vba.h"
#समावेश "dcn20_dccg.h"
#समावेश "dcn20_vmid.h"
#समावेश "dc_link_ddc.h"
#समावेश "dce/dce_panel_cntl.h"

#समावेश "navi10_ip_offset.h"

#समावेश "dcn/dcn_2_0_0_offset.h"
#समावेश "dcn/dcn_2_0_0_sh_mask.h"
#समावेश "dpcs/dpcs_2_0_0_offset.h"
#समावेश "dpcs/dpcs_2_0_0_sh_mask.h"

#समावेश "nbio/nbio_2_3_offset.h"

#समावेश "dcn20/dcn20_dwb.h"
#समावेश "dcn20/dcn20_mmhubbub.h"

#समावेश "mmhub/mmhub_2_0_0_offset.h"
#समावेश "mmhub/mmhub_2_0_0_sh_mask.h"

#समावेश "reg_helper.h"
#समावेश "dce/dce_abm.h"
#समावेश "dce/dce_dmcu.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_i2c.h"
#समावेश "vm_helper.h"

#समावेश "amdgpu_socbb.h"

#घोषणा DC_LOGGER_INIT(logger)

काष्ठा _vcs_dpi_ip_params_st dcn2_0_ip = अणु
	.odm_capable = 1,
	.gpuvm_enable = 0,
	.hostvm_enable = 0,
	.gpuvm_max_page_table_levels = 4,
	.hostvm_max_page_table_levels = 4,
	.hostvm_cached_page_table_levels = 0,
	.pte_group_size_bytes = 2048,
	.num_dsc = 6,
	.rob_buffer_size_kbytes = 168,
	.det_buffer_size_kbytes = 164,
	.dpte_buffer_size_in_pte_reqs_luma = 84,
	.pde_proc_buffer_size_64k_reqs = 48,
	.dpp_output_buffer_pixels = 2560,
	.opp_output_buffer_lines = 1,
	.pixel_chunk_size_kbytes = 8,
	.pte_chunk_size_kbytes = 2,
	.meta_chunk_size_kbytes = 2,
	.ग_लिखोback_chunk_size_kbytes = 2,
	.line_buffer_size_bits = 789504,
	.is_line_buffer_bpp_fixed = 0,
	.line_buffer_fixed_bpp = 0,
	.dcc_supported = true,
	.max_line_buffer_lines = 12,
	.ग_लिखोback_luma_buffer_size_kbytes = 12,
	.ग_लिखोback_chroma_buffer_size_kbytes = 8,
	.ग_लिखोback_chroma_line_buffer_width_pixels = 4,
	.ग_लिखोback_max_hscl_ratio = 1,
	.ग_लिखोback_max_vscl_ratio = 1,
	.ग_लिखोback_min_hscl_ratio = 1,
	.ग_लिखोback_min_vscl_ratio = 1,
	.ग_लिखोback_max_hscl_taps = 12,
	.ग_लिखोback_max_vscl_taps = 12,
	.ग_लिखोback_line_buffer_luma_buffer_size = 0,
	.ग_लिखोback_line_buffer_chroma_buffer_size = 14643,
	.cursor_buffer_size = 8,
	.cursor_chunk_size = 2,
	.max_num_otg = 6,
	.max_num_dpp = 6,
	.max_num_wb = 1,
	.max_dchub_pscl_bw_pix_per_clk = 4,
	.max_pscl_lb_bw_pix_per_clk = 2,
	.max_lb_vscl_bw_pix_per_clk = 4,
	.max_vscl_hscl_bw_pix_per_clk = 4,
	.max_hscl_ratio = 8,
	.max_vscl_ratio = 8,
	.hscl_mults = 4,
	.vscl_mults = 4,
	.max_hscl_taps = 8,
	.max_vscl_taps = 8,
	.dispclk_ramp_margin_percent = 1,
	.underscan_factor = 1.10,
	.min_vblank_lines = 32, //
	.dppclk_delay_subtotal = 77, //
	.dppclk_delay_scl_lb_only = 16,
	.dppclk_delay_scl = 50,
	.dppclk_delay_cnvc_क्रमmatter = 8,
	.dppclk_delay_cnvc_cursor = 6,
	.dispclk_delay_subtotal = 87, //
	.dcfclk_cstate_latency = 10, // SRExitTime
	.max_पूर्णांकer_dcn_tile_repeaters = 8,
	.xfc_supported = true,
	.xfc_fill_bw_overhead_percent = 10.0,
	.xfc_fill_स्थिरant_bytes = 0,
	.number_of_cursors = 1,
पूर्ण;

अटल काष्ठा _vcs_dpi_ip_params_st dcn2_0_nv14_ip = अणु
	.odm_capable = 1,
	.gpuvm_enable = 0,
	.hostvm_enable = 0,
	.gpuvm_max_page_table_levels = 4,
	.hostvm_max_page_table_levels = 4,
	.hostvm_cached_page_table_levels = 0,
	.num_dsc = 5,
	.rob_buffer_size_kbytes = 168,
	.det_buffer_size_kbytes = 164,
	.dpte_buffer_size_in_pte_reqs_luma = 84,
	.dpte_buffer_size_in_pte_reqs_chroma = 42,//toकरो
	.dpp_output_buffer_pixels = 2560,
	.opp_output_buffer_lines = 1,
	.pixel_chunk_size_kbytes = 8,
	.pte_enable = 1,
	.max_page_table_levels = 4,
	.pte_chunk_size_kbytes = 2,
	.meta_chunk_size_kbytes = 2,
	.ग_लिखोback_chunk_size_kbytes = 2,
	.line_buffer_size_bits = 789504,
	.is_line_buffer_bpp_fixed = 0,
	.line_buffer_fixed_bpp = 0,
	.dcc_supported = true,
	.max_line_buffer_lines = 12,
	.ग_लिखोback_luma_buffer_size_kbytes = 12,
	.ग_लिखोback_chroma_buffer_size_kbytes = 8,
	.ग_लिखोback_chroma_line_buffer_width_pixels = 4,
	.ग_लिखोback_max_hscl_ratio = 1,
	.ग_लिखोback_max_vscl_ratio = 1,
	.ग_लिखोback_min_hscl_ratio = 1,
	.ग_लिखोback_min_vscl_ratio = 1,
	.ग_लिखोback_max_hscl_taps = 12,
	.ग_लिखोback_max_vscl_taps = 12,
	.ग_लिखोback_line_buffer_luma_buffer_size = 0,
	.ग_लिखोback_line_buffer_chroma_buffer_size = 14643,
	.cursor_buffer_size = 8,
	.cursor_chunk_size = 2,
	.max_num_otg = 5,
	.max_num_dpp = 5,
	.max_num_wb = 1,
	.max_dchub_pscl_bw_pix_per_clk = 4,
	.max_pscl_lb_bw_pix_per_clk = 2,
	.max_lb_vscl_bw_pix_per_clk = 4,
	.max_vscl_hscl_bw_pix_per_clk = 4,
	.max_hscl_ratio = 8,
	.max_vscl_ratio = 8,
	.hscl_mults = 4,
	.vscl_mults = 4,
	.max_hscl_taps = 8,
	.max_vscl_taps = 8,
	.dispclk_ramp_margin_percent = 1,
	.underscan_factor = 1.10,
	.min_vblank_lines = 32, //
	.dppclk_delay_subtotal = 77, //
	.dppclk_delay_scl_lb_only = 16,
	.dppclk_delay_scl = 50,
	.dppclk_delay_cnvc_क्रमmatter = 8,
	.dppclk_delay_cnvc_cursor = 6,
	.dispclk_delay_subtotal = 87, //
	.dcfclk_cstate_latency = 10, // SRExitTime
	.max_पूर्णांकer_dcn_tile_repeaters = 8,
	.xfc_supported = true,
	.xfc_fill_bw_overhead_percent = 10.0,
	.xfc_fill_स्थिरant_bytes = 0,
	.ptoi_supported = 0,
	.number_of_cursors = 1,
पूर्ण;

अटल काष्ठा _vcs_dpi_soc_bounding_box_st dcn2_0_soc = अणु
	/* Defaults that get patched on driver load from firmware. */
	.घड़ी_limits = अणु
			अणु
				.state = 0,
				.dcfclk_mhz = 560.0,
				.fabricclk_mhz = 560.0,
				.dispclk_mhz = 513.0,
				.dppclk_mhz = 513.0,
				.phyclk_mhz = 540.0,
				.socclk_mhz = 560.0,
				.dscclk_mhz = 171.0,
				.dram_speed_mts = 8960.0,
			पूर्ण,
			अणु
				.state = 1,
				.dcfclk_mhz = 694.0,
				.fabricclk_mhz = 694.0,
				.dispclk_mhz = 642.0,
				.dppclk_mhz = 642.0,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 694.0,
				.dscclk_mhz = 214.0,
				.dram_speed_mts = 11104.0,
			पूर्ण,
			अणु
				.state = 2,
				.dcfclk_mhz = 875.0,
				.fabricclk_mhz = 875.0,
				.dispclk_mhz = 734.0,
				.dppclk_mhz = 734.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 875.0,
				.dscclk_mhz = 245.0,
				.dram_speed_mts = 14000.0,
			पूर्ण,
			अणु
				.state = 3,
				.dcfclk_mhz = 1000.0,
				.fabricclk_mhz = 1000.0,
				.dispclk_mhz = 1100.0,
				.dppclk_mhz = 1100.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 1000.0,
				.dscclk_mhz = 367.0,
				.dram_speed_mts = 16000.0,
			पूर्ण,
			अणु
				.state = 4,
				.dcfclk_mhz = 1200.0,
				.fabricclk_mhz = 1200.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 1200.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 16000.0,
			पूर्ण,
			/*Extra state, no dispclk ramping*/
			अणु
				.state = 5,
				.dcfclk_mhz = 1200.0,
				.fabricclk_mhz = 1200.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 1200.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 16000.0,
			पूर्ण,
		पूर्ण,
	.num_states = 5,
	.sr_निकास_समय_us = 8.6,
	.sr_enter_plus_निकास_समय_us = 10.9,
	.urgent_latency_us = 4.0,
	.urgent_latency_pixel_data_only_us = 4.0,
	.urgent_latency_pixel_mixed_with_vm_data_us = 4.0,
	.urgent_latency_vm_data_only_us = 4.0,
	.urgent_out_of_order_वापस_per_channel_pixel_only_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_pixel_and_vm_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_vm_only_bytes = 4096,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_only = 40.0,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_and_vm = 40.0,
	.pct_ideal_dram_sdp_bw_after_urgent_vm_only = 40.0,
	.max_avg_sdp_bw_use_normal_percent = 40.0,
	.max_avg_dram_bw_use_normal_percent = 40.0,
	.ग_लिखोback_latency_us = 12.0,
	.ideal_dram_bw_after_urgent_percent = 40.0,
	.max_request_size_bytes = 256,
	.dram_channel_width_bytes = 2,
	.fabric_datapath_to_dcn_data_वापस_bytes = 64,
	.dcn_करोwnspपढ़ो_percent = 0.5,
	.करोwnspपढ़ो_percent = 0.38,
	.dram_page_खोलो_समय_ns = 50.0,
	.dram_rw_turnaround_समय_ns = 17.5,
	.dram_वापस_buffer_per_channel_bytes = 8192,
	.round_trip_ping_latency_dcfclk_cycles = 131,
	.urgent_out_of_order_वापस_per_channel_bytes = 256,
	.channel_पूर्णांकerleave_bytes = 256,
	.num_banks = 8,
	.num_chans = 16,
	.vmm_page_size_bytes = 4096,
	.dram_घड़ी_change_latency_us = 404.0,
	.dummy_pstate_latency_us = 5.0,
	.ग_लिखोback_dram_घड़ी_change_latency_us = 23.0,
	.वापस_bus_width_bytes = 64,
	.dispclk_dppclk_vco_speed_mhz = 3850,
	.xfc_bus_transport_समय_us = 20,
	.xfc_xbuf_latency_tolerance_us = 4,
	.use_urgent_burst_bw = 0
पूर्ण;

अटल काष्ठा _vcs_dpi_soc_bounding_box_st dcn2_0_nv14_soc = अणु
	.घड़ी_limits = अणु
			अणु
				.state = 0,
				.dcfclk_mhz = 560.0,
				.fabricclk_mhz = 560.0,
				.dispclk_mhz = 513.0,
				.dppclk_mhz = 513.0,
				.phyclk_mhz = 540.0,
				.socclk_mhz = 560.0,
				.dscclk_mhz = 171.0,
				.dram_speed_mts = 8960.0,
			पूर्ण,
			अणु
				.state = 1,
				.dcfclk_mhz = 694.0,
				.fabricclk_mhz = 694.0,
				.dispclk_mhz = 642.0,
				.dppclk_mhz = 642.0,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 694.0,
				.dscclk_mhz = 214.0,
				.dram_speed_mts = 11104.0,
			पूर्ण,
			अणु
				.state = 2,
				.dcfclk_mhz = 875.0,
				.fabricclk_mhz = 875.0,
				.dispclk_mhz = 734.0,
				.dppclk_mhz = 734.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 875.0,
				.dscclk_mhz = 245.0,
				.dram_speed_mts = 14000.0,
			पूर्ण,
			अणु
				.state = 3,
				.dcfclk_mhz = 1000.0,
				.fabricclk_mhz = 1000.0,
				.dispclk_mhz = 1100.0,
				.dppclk_mhz = 1100.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 1000.0,
				.dscclk_mhz = 367.0,
				.dram_speed_mts = 16000.0,
			पूर्ण,
			अणु
				.state = 4,
				.dcfclk_mhz = 1200.0,
				.fabricclk_mhz = 1200.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 1200.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 16000.0,
			पूर्ण,
			/*Extra state, no dispclk ramping*/
			अणु
				.state = 5,
				.dcfclk_mhz = 1200.0,
				.fabricclk_mhz = 1200.0,
				.dispclk_mhz = 1284.0,
				.dppclk_mhz = 1284.0,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 1200.0,
				.dscclk_mhz = 428.0,
				.dram_speed_mts = 16000.0,
			पूर्ण,
		पूर्ण,
	.num_states = 5,
	.sr_निकास_समय_us = 11.6,
	.sr_enter_plus_निकास_समय_us = 13.9,
	.urgent_latency_us = 4.0,
	.urgent_latency_pixel_data_only_us = 4.0,
	.urgent_latency_pixel_mixed_with_vm_data_us = 4.0,
	.urgent_latency_vm_data_only_us = 4.0,
	.urgent_out_of_order_वापस_per_channel_pixel_only_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_pixel_and_vm_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_vm_only_bytes = 4096,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_only = 40.0,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_and_vm = 40.0,
	.pct_ideal_dram_sdp_bw_after_urgent_vm_only = 40.0,
	.max_avg_sdp_bw_use_normal_percent = 40.0,
	.max_avg_dram_bw_use_normal_percent = 40.0,
	.ग_लिखोback_latency_us = 12.0,
	.ideal_dram_bw_after_urgent_percent = 40.0,
	.max_request_size_bytes = 256,
	.dram_channel_width_bytes = 2,
	.fabric_datapath_to_dcn_data_वापस_bytes = 64,
	.dcn_करोwnspपढ़ो_percent = 0.5,
	.करोwnspपढ़ो_percent = 0.38,
	.dram_page_खोलो_समय_ns = 50.0,
	.dram_rw_turnaround_समय_ns = 17.5,
	.dram_वापस_buffer_per_channel_bytes = 8192,
	.round_trip_ping_latency_dcfclk_cycles = 131,
	.urgent_out_of_order_वापस_per_channel_bytes = 256,
	.channel_पूर्णांकerleave_bytes = 256,
	.num_banks = 8,
	.num_chans = 8,
	.vmm_page_size_bytes = 4096,
	.dram_घड़ी_change_latency_us = 404.0,
	.dummy_pstate_latency_us = 5.0,
	.ग_लिखोback_dram_घड़ी_change_latency_us = 23.0,
	.वापस_bus_width_bytes = 64,
	.dispclk_dppclk_vco_speed_mhz = 3850,
	.xfc_bus_transport_समय_us = 20,
	.xfc_xbuf_latency_tolerance_us = 4,
	.use_urgent_burst_bw = 0
पूर्ण;

अटल काष्ठा _vcs_dpi_soc_bounding_box_st dcn2_0_nv12_soc = अणु 0 पूर्ण;

#अगर_अघोषित mmDP0_DP_DPHY_INTERNAL_CTRL
	#घोषणा mmDP0_DP_DPHY_INTERNAL_CTRL		0x210f
	#घोषणा mmDP0_DP_DPHY_INTERNAL_CTRL_BASE_IDX	2
	#घोषणा mmDP1_DP_DPHY_INTERNAL_CTRL		0x220f
	#घोषणा mmDP1_DP_DPHY_INTERNAL_CTRL_BASE_IDX	2
	#घोषणा mmDP2_DP_DPHY_INTERNAL_CTRL		0x230f
	#घोषणा mmDP2_DP_DPHY_INTERNAL_CTRL_BASE_IDX	2
	#घोषणा mmDP3_DP_DPHY_INTERNAL_CTRL		0x240f
	#घोषणा mmDP3_DP_DPHY_INTERNAL_CTRL_BASE_IDX	2
	#घोषणा mmDP4_DP_DPHY_INTERNAL_CTRL		0x250f
	#घोषणा mmDP4_DP_DPHY_INTERNAL_CTRL_BASE_IDX	2
	#घोषणा mmDP5_DP_DPHY_INTERNAL_CTRL		0x260f
	#घोषणा mmDP5_DP_DPHY_INTERNAL_CTRL_BASE_IDX	2
	#घोषणा mmDP6_DP_DPHY_INTERNAL_CTRL		0x270f
	#घोषणा mmDP6_DP_DPHY_INTERNAL_CTRL_BASE_IDX	2
#पूर्ण_अगर


क्रमागत dcn20_clk_src_array_id अणु
	DCN20_CLK_SRC_PLL0,
	DCN20_CLK_SRC_PLL1,
	DCN20_CLK_SRC_PLL2,
	DCN20_CLK_SRC_PLL3,
	DCN20_CLK_SRC_PLL4,
	DCN20_CLK_SRC_PLL5,
	DCN20_CLK_SRC_TOTAL
पूर्ण;

/* begin *********************
 * macros to expend रेजिस्टर list macro defined in HW object header file */

/* DCN */
/* TODO awful hack. fixup dcn20_dwb.h */
#अघोषित BASE_INNER
#घोषणा BASE_INNER(seg) DCN_BASE__INST0_SEG ## seg

#घोषणा BASE(seg) BASE_INNER(seg)

#घोषणा SR(reg_name)\
		.reg_name = BASE(mm ## reg_name ## _BASE_IDX) +  \
					mm ## reg_name

#घोषणा SRI(reg_name, block, id)\
	.reg_name = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा SRIR(var_name, reg_name, block, id)\
	.var_name = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा SRII(reg_name, block, id)\
	.reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा DCCG_SRII(reg_name, block, id)\
	.block ## _ ## reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा VUPDATE_SRII(reg_name, block, id)\
	.reg_name[id] = BASE(mm ## reg_name ## _ ## block ## id ## _BASE_IDX) + \
					mm ## reg_name ## _ ## block ## id

/* NBIO */
#घोषणा NBIO_BASE_INNER(seg) \
	NBIO_BASE__INST0_SEG ## seg

#घोषणा NBIO_BASE(seg) \
	NBIO_BASE_INNER(seg)

#घोषणा NBIO_SR(reg_name)\
		.reg_name = NBIO_BASE(mm ## reg_name ## _BASE_IDX) + \
					mm ## reg_name

/* MMHUB */
#घोषणा MMHUB_BASE_INNER(seg) \
	MMHUB_BASE__INST0_SEG ## seg

#घोषणा MMHUB_BASE(seg) \
	MMHUB_BASE_INNER(seg)

#घोषणा MMHUB_SR(reg_name)\
		.reg_name = MMHUB_BASE(mmMM ## reg_name ## _BASE_IDX) + \
					mmMM ## reg_name

अटल स्थिर काष्ठा bios_रेजिस्टरs bios_regs = अणु
		NBIO_SR(BIOS_SCRATCH_3),
		NBIO_SR(BIOS_SCRATCH_6)
पूर्ण;

#घोषणा clk_src_regs(index, pllid)\
[index] = अणु\
	CS_COMMON_REG_LIST_DCN2_0(index, pllid),\
पूर्ण

अटल स्थिर काष्ठा dce110_clk_src_regs clk_src_regs[] = अणु
	clk_src_regs(0, A),
	clk_src_regs(1, B),
	clk_src_regs(2, C),
	clk_src_regs(3, D),
	clk_src_regs(4, E),
	clk_src_regs(5, F)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_shअगरt cs_shअगरt = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_mask cs_mask = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_dmcu_रेजिस्टरs dmcu_regs = अणु
		DMCU_DCN10_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_dmcu_shअगरt dmcu_shअगरt = अणु
		DMCU_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_dmcu_mask dmcu_mask = अणु
		DMCU_MASK_SH_LIST_DCN10(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_रेजिस्टरs abm_regs = अणु
		ABM_DCN20_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_abm_shअगरt abm_shअगरt = अणु
		ABM_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_mask abm_mask = अणु
		ABM_MASK_SH_LIST_DCN20(_MASK)
पूर्ण;

#घोषणा audio_regs(id)\
[id] = अणु\
		AUD_COMMON_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dce_audio_रेजिस्टरs audio_regs[] = अणु
	audio_regs(0),
	audio_regs(1),
	audio_regs(2),
	audio_regs(3),
	audio_regs(4),
	audio_regs(5),
	audio_regs(6),
पूर्ण;

#घोषणा DCE120_AUD_COMMON_MASK_SH_LIST(mask_sh)\
		SF(AZF0ENDPOINT0_AZALIA_F0_CODEC_ENDPOINT_INDEX, AZALIA_ENDPOINT_REG_INDEX, mask_sh),\
		SF(AZF0ENDPOINT0_AZALIA_F0_CODEC_ENDPOINT_DATA, AZALIA_ENDPOINT_REG_DATA, mask_sh),\
		AUD_COMMON_MASK_SH_LIST_BASE(mask_sh)

अटल स्थिर काष्ठा dce_audio_shअगरt audio_shअगरt = अणु
		DCE120_AUD_COMMON_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_audio_mask audio_mask = अणु
		DCE120_AUD_COMMON_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा stream_enc_regs(id)\
[id] = अणु\
	SE_DCN2_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs stream_enc_regs[] = अणु
	stream_enc_regs(0),
	stream_enc_regs(1),
	stream_enc_regs(2),
	stream_enc_regs(3),
	stream_enc_regs(4),
	stream_enc_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCN20(_MASK)
पूर्ण;


#घोषणा aux_regs(id)\
[id] = अणु\
	DCN2_AUX_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_aux_रेजिस्टरs link_enc_aux_regs[] = अणु
		aux_regs(0),
		aux_regs(1),
		aux_regs(2),
		aux_regs(3),
		aux_regs(4),
		aux_regs(5)
पूर्ण;

#घोषणा hpd_regs(id)\
[id] = अणु\
	HPD_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_hpd_रेजिस्टरs link_enc_hpd_regs[] = अणु
		hpd_regs(0),
		hpd_regs(1),
		hpd_regs(2),
		hpd_regs(3),
		hpd_regs(4),
		hpd_regs(5)
पूर्ण;

#घोषणा link_regs(id, phyid)\
[id] = अणु\
	LE_DCN10_REG_LIST(id), \
	UNIPHY_DCN2_REG_LIST(phyid), \
	DPCS_DCN2_REG_LIST(id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id) \
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs link_enc_regs[] = अणु
	link_regs(0, A),
	link_regs(1, B),
	link_regs(2, C),
	link_regs(3, D),
	link_regs(4, E),
	link_regs(5, F)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_shअगरt le_shअगरt = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN20(__SHIFT),\
	DPCS_DCN2_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_mask le_mask = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN20(_MASK),\
	DPCS_DCN2_MASK_SH_LIST(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs panel_cntl_regs[] = अणु
	अणु DCN_PANEL_CNTL_REG_LIST() पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_shअगरt panel_cntl_shअगरt = अणु
	DCE_PANEL_CNTL_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_mask panel_cntl_mask = अणु
	DCE_PANEL_CNTL_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा ipp_regs(id)\
[id] = अणु\
	IPP_REG_LIST_DCN20(id),\
पूर्ण

अटल स्थिर काष्ठा dcn10_ipp_रेजिस्टरs ipp_regs[] = अणु
	ipp_regs(0),
	ipp_regs(1),
	ipp_regs(2),
	ipp_regs(3),
	ipp_regs(4),
	ipp_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dcn10_ipp_shअगरt ipp_shअगरt = अणु
		IPP_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_ipp_mask ipp_mask = अणु
		IPP_MASK_SH_LIST_DCN20(_MASK),
पूर्ण;

#घोषणा opp_regs(id)\
[id] = अणु\
	OPP_REG_LIST_DCN20(id),\
पूर्ण

अटल स्थिर काष्ठा dcn20_opp_रेजिस्टरs opp_regs[] = अणु
	opp_regs(0),
	opp_regs(1),
	opp_regs(2),
	opp_regs(3),
	opp_regs(4),
	opp_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dcn20_opp_shअगरt opp_shअगरt = अणु
		OPP_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn20_opp_mask opp_mask = अणु
		OPP_MASK_SH_LIST_DCN20(_MASK)
पूर्ण;

#घोषणा aux_engine_regs(id)\
[id] = अणु\
	AUX_COMMON_REG_LIST0(id), \
	.AUXN_IMPCAL = 0, \
	.AUXP_IMPCAL = 0, \
	.AUX_RESET_MASK = DP_AUX0_AUX_CONTROL__AUX_RESET_MASK, \
पूर्ण

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs aux_engine_regs[] = अणु
		aux_engine_regs(0),
		aux_engine_regs(1),
		aux_engine_regs(2),
		aux_engine_regs(3),
		aux_engine_regs(4),
		aux_engine_regs(5)
पूर्ण;

#घोषणा tf_regs(id)\
[id] = अणु\
	TF_REG_LIST_DCN20(id),\
	TF_REG_LIST_DCN20_COMMON_APPEND(id),\
पूर्ण

अटल स्थिर काष्ठा dcn2_dpp_रेजिस्टरs tf_regs[] = अणु
	tf_regs(0),
	tf_regs(1),
	tf_regs(2),
	tf_regs(3),
	tf_regs(4),
	tf_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dcn2_dpp_shअगरt tf_shअगरt = अणु
		TF_REG_LIST_SH_MASK_DCN20(__SHIFT),
		TF_DEBUG_REG_LIST_SH_DCN20
पूर्ण;

अटल स्थिर काष्ठा dcn2_dpp_mask tf_mask = अणु
		TF_REG_LIST_SH_MASK_DCN20(_MASK),
		TF_DEBUG_REG_LIST_MASK_DCN20
पूर्ण;

#घोषणा dwbc_regs_dcn2(id)\
[id] = अणु\
	DWBC_COMMON_REG_LIST_DCN2_0(id),\
		पूर्ण

अटल स्थिर काष्ठा dcn20_dwbc_रेजिस्टरs dwbc20_regs[] = अणु
	dwbc_regs_dcn2(0),
पूर्ण;

अटल स्थिर काष्ठा dcn20_dwbc_shअगरt dwbc20_shअगरt = अणु
	DWBC_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn20_dwbc_mask dwbc20_mask = अणु
	DWBC_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
पूर्ण;

#घोषणा mcअगर_wb_regs_dcn2(id)\
[id] = अणु\
	MCIF_WB_COMMON_REG_LIST_DCN2_0(id),\
		पूर्ण

अटल स्थिर काष्ठा dcn20_mmhubbub_रेजिस्टरs mcअगर_wb20_regs[] = अणु
	mcअगर_wb_regs_dcn2(0),
पूर्ण;

अटल स्थिर काष्ठा dcn20_mmhubbub_shअगरt mcअगर_wb20_shअगरt = अणु
	MCIF_WB_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn20_mmhubbub_mask mcअगर_wb20_mask = अणु
	MCIF_WB_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn20_mpc_रेजिस्टरs mpc_regs = अणु
		MPC_REG_LIST_DCN2_0(0),
		MPC_REG_LIST_DCN2_0(1),
		MPC_REG_LIST_DCN2_0(2),
		MPC_REG_LIST_DCN2_0(3),
		MPC_REG_LIST_DCN2_0(4),
		MPC_REG_LIST_DCN2_0(5),
		MPC_OUT_MUX_REG_LIST_DCN2_0(0),
		MPC_OUT_MUX_REG_LIST_DCN2_0(1),
		MPC_OUT_MUX_REG_LIST_DCN2_0(2),
		MPC_OUT_MUX_REG_LIST_DCN2_0(3),
		MPC_OUT_MUX_REG_LIST_DCN2_0(4),
		MPC_OUT_MUX_REG_LIST_DCN2_0(5),
		MPC_DBG_REG_LIST_DCN2_0()
पूर्ण;

अटल स्थिर काष्ठा dcn20_mpc_shअगरt mpc_shअगरt = अणु
	MPC_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT),
	MPC_DEBUG_REG_LIST_SH_DCN20
पूर्ण;

अटल स्थिर काष्ठा dcn20_mpc_mask mpc_mask = अणु
	MPC_COMMON_MASK_SH_LIST_DCN2_0(_MASK),
	MPC_DEBUG_REG_LIST_MASK_DCN20
पूर्ण;

#घोषणा tg_regs(id)\
[id] = अणुTG_COMMON_REG_LIST_DCN2_0(id)पूर्ण


अटल स्थिर काष्ठा dcn_optc_रेजिस्टरs tg_regs[] = अणु
	tg_regs(0),
	tg_regs(1),
	tg_regs(2),
	tg_regs(3),
	tg_regs(4),
	tg_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_shअगरt tg_shअगरt = अणु
	TG_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_mask tg_mask = अणु
	TG_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
पूर्ण;

#घोषणा hubp_regs(id)\
[id] = अणु\
	HUBP_REG_LIST_DCN20(id)\
पूर्ण

अटल स्थिर काष्ठा dcn_hubp2_रेजिस्टरs hubp_regs[] = अणु
		hubp_regs(0),
		hubp_regs(1),
		hubp_regs(2),
		hubp_regs(3),
		hubp_regs(4),
		hubp_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_shअगरt hubp_shअगरt = अणु
		HUBP_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_mask hubp_mask = अणु
		HUBP_MASK_SH_LIST_DCN20(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_रेजिस्टरs hubbub_reg = अणु
		HUBBUB_REG_LIST_DCN20(0)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_shअगरt hubbub_shअगरt = अणु
		HUBBUB_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_mask hubbub_mask = अणु
		HUBBUB_MASK_SH_LIST_DCN20(_MASK)
पूर्ण;

#घोषणा vmid_regs(id)\
[id] = अणु\
		DCN20_VMID_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn_vmid_रेजिस्टरs vmid_regs[] = अणु
	vmid_regs(0),
	vmid_regs(1),
	vmid_regs(2),
	vmid_regs(3),
	vmid_regs(4),
	vmid_regs(5),
	vmid_regs(6),
	vmid_regs(7),
	vmid_regs(8),
	vmid_regs(9),
	vmid_regs(10),
	vmid_regs(11),
	vmid_regs(12),
	vmid_regs(13),
	vmid_regs(14),
	vmid_regs(15)
पूर्ण;

अटल स्थिर काष्ठा dcn20_vmid_shअगरt vmid_shअगरts = अणु
		DCN20_VMID_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn20_vmid_mask vmid_masks = अणु
		DCN20_VMID_MASK_SH_LIST(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt aux_shअगरt = अणु
		DCN_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
		DCN_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

अटल पूर्णांक map_transmitter_id_to_phy_instance(
	क्रमागत transmitter transmitter)
अणु
	चयन (transmitter) अणु
	हाल TRANSMITTER_UNIPHY_A:
		वापस 0;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_B:
		वापस 1;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_C:
		वापस 2;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_D:
		वापस 3;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_E:
		वापस 4;
	अवरोध;
	हाल TRANSMITTER_UNIPHY_F:
		वापस 5;
	अवरोध;
	शेष:
		ASSERT(0);
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा dsc_regsDCN20(id)\
[id] = अणु\
	DSC_REG_LIST_DCN20(id)\
पूर्ण

अटल स्थिर काष्ठा dcn20_dsc_रेजिस्टरs dsc_regs[] = अणु
	dsc_regsDCN20(0),
	dsc_regsDCN20(1),
	dsc_regsDCN20(2),
	dsc_regsDCN20(3),
	dsc_regsDCN20(4),
	dsc_regsDCN20(5)
पूर्ण;

अटल स्थिर काष्ठा dcn20_dsc_shअगरt dsc_shअगरt = अणु
	DSC_REG_LIST_SH_MASK_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn20_dsc_mask dsc_mask = अणु
	DSC_REG_LIST_SH_MASK_DCN20(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dccg_रेजिस्टरs dccg_regs = अणु
		DCCG_REG_LIST_DCN2()
पूर्ण;

अटल स्थिर काष्ठा dccg_shअगरt dccg_shअगरt = अणु
		DCCG_MASK_SH_LIST_DCN2(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dccg_mask dccg_mask = अणु
		DCCG_MASK_SH_LIST_DCN2(_MASK)
पूर्ण;

अटल स्थिर काष्ठा resource_caps res_cap_nv10 = अणु
		.num_timing_generator = 6,
		.num_opp = 6,
		.num_video_plane = 6,
		.num_audio = 7,
		.num_stream_encoder = 6,
		.num_pll = 6,
		.num_dwb = 1,
		.num_ddc = 6,
		.num_vmid = 16,
		.num_dsc = 6,
पूर्ण;

अटल स्थिर काष्ठा dc_plane_cap plane_cap = अणु
	.type = DC_PLANE_TYPE_DCN_UNIVERSAL,
	.blends_with_above = true,
	.blends_with_below = true,
	.per_pixel_alpha = true,

	.pixel_क्रमmat_support = अणु
			.argb8888 = true,
			.nv12 = true,
			.fp16 = true,
			.p010 = true
	पूर्ण,

	.max_upscale_factor = अणु
			.argb8888 = 16000,
			.nv12 = 16000,
			.fp16 = 1
	पूर्ण,

	.max_करोwnscale_factor = अणु
			.argb8888 = 250,
			.nv12 = 250,
			.fp16 = 1
	पूर्ण,
	16,
	16
पूर्ण;
अटल स्थिर काष्ठा resource_caps res_cap_nv14 = अणु
		.num_timing_generator = 5,
		.num_opp = 5,
		.num_video_plane = 5,
		.num_audio = 6,
		.num_stream_encoder = 5,
		.num_pll = 5,
		.num_dwb = 1,
		.num_ddc = 5,
		.num_vmid = 16,
		.num_dsc = 5,
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_drv = अणु
		.disable_dmcu = false,
		.क्रमce_abm_enable = false,
		.timing_trace = false,
		.घड़ी_प्रकारrace = true,
		.disable_pplib_घड़ी_request = true,
		.pipe_split_policy = MPC_SPLIT_DYNAMIC,
		.क्रमce_single_disp_pipe_split = false,
		.disable_dcc = DCC_ENABLE,
		.vsr_support = true,
		.perक्रमmance_trace = false,
		.max_करोwnscale_src_width = 5120,/*upto 5K*/
		.disable_pplib_wm_range = false,
		.scl_reset_length10 = true,
		.sanity_checks = false,
		.underflow_निश्चित_delay_us = 0xFFFFFFFF,
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_diags = अणु
		.disable_dmcu = false,
		.क्रमce_abm_enable = false,
		.timing_trace = true,
		.घड़ी_प्रकारrace = true,
		.disable_dpp_घातer_gate = true,
		.disable_hubp_घातer_gate = true,
		.disable_घड़ी_gate = true,
		.disable_pplib_घड़ी_request = true,
		.disable_pplib_wm_range = true,
		.disable_stutter = true,
		.scl_reset_length10 = true,
		.underflow_निश्चित_delay_us = 0xFFFFFFFF,
		.enable_tri_buf = true,
पूर्ण;

व्योम dcn20_dpp_destroy(काष्ठा dpp **dpp)
अणु
	kमुक्त(TO_DCN20_DPP(*dpp));
	*dpp = शून्य;
पूर्ण

काष्ठा dpp *dcn20_dpp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_dpp *dpp =
		kzalloc(माप(काष्ठा dcn20_dpp), GFP_ATOMIC);

	अगर (!dpp)
		वापस शून्य;

	अगर (dpp2_स्थिरruct(dpp, ctx, inst,
			&tf_regs[inst], &tf_shअगरt, &tf_mask))
		वापस &dpp->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(dpp);
	वापस शून्य;
पूर्ण

काष्ठा input_pixel_processor *dcn20_ipp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn10_ipp *ipp =
		kzalloc(माप(काष्ठा dcn10_ipp), GFP_ATOMIC);

	अगर (!ipp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn20_ipp_स्थिरruct(ipp, ctx, inst,
			&ipp_regs[inst], &ipp_shअगरt, &ipp_mask);
	वापस &ipp->base;
पूर्ण


काष्ठा output_pixel_processor *dcn20_opp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_opp *opp =
		kzalloc(माप(काष्ठा dcn20_opp), GFP_ATOMIC);

	अगर (!opp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn20_opp_स्थिरruct(opp, ctx, inst,
			&opp_regs[inst], &opp_shअगरt, &opp_mask);
	वापस &opp->base;
पूर्ण

काष्ठा dce_aux *dcn20_aux_engine_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा aux_engine_dce110 *aux_engine =
		kzalloc(माप(काष्ठा aux_engine_dce110), GFP_ATOMIC);

	अगर (!aux_engine)
		वापस शून्य;

	dce110_aux_engine_स्थिरruct(aux_engine, ctx, inst,
				    SW_AUX_TIMEOUT_PERIOD_MULTIPLIER * AUX_TIMEOUT_PERIOD,
				    &aux_engine_regs[inst],
					&aux_mask,
					&aux_shअगरt,
					ctx->dc->caps.extended_aux_समयout_support);

	वापस &aux_engine->base;
पूर्ण
#घोषणा i2c_inst_regs(id) अणु I2C_HW_ENGINE_COMMON_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dce_i2c_रेजिस्टरs i2c_hw_regs[] = अणु
		i2c_inst_regs(1),
		i2c_inst_regs(2),
		i2c_inst_regs(3),
		i2c_inst_regs(4),
		i2c_inst_regs(5),
		i2c_inst_regs(6),
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_shअगरt i2c_shअगरts = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_mask i2c_masks = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(_MASK)
पूर्ण;

काष्ठा dce_i2c_hw *dcn20_i2c_hw_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_i2c_hw *dce_i2c_hw =
		kzalloc(माप(काष्ठा dce_i2c_hw), GFP_ATOMIC);

	अगर (!dce_i2c_hw)
		वापस शून्य;

	dcn2_i2c_hw_स्थिरruct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_regs[inst], &i2c_shअगरts, &i2c_masks);

	वापस dce_i2c_hw;
पूर्ण
काष्ठा mpc *dcn20_mpc_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn20_mpc *mpc20 = kzalloc(माप(काष्ठा dcn20_mpc),
					  GFP_ATOMIC);

	अगर (!mpc20)
		वापस शून्य;

	dcn20_mpc_स्थिरruct(mpc20, ctx,
			&mpc_regs,
			&mpc_shअगरt,
			&mpc_mask,
			6);

	वापस &mpc20->base;
पूर्ण

काष्ठा hubbub *dcn20_hubbub_create(काष्ठा dc_context *ctx)
अणु
	पूर्णांक i;
	काष्ठा dcn20_hubbub *hubbub = kzalloc(माप(काष्ठा dcn20_hubbub),
					  GFP_ATOMIC);

	अगर (!hubbub)
		वापस शून्य;

	hubbub2_स्थिरruct(hubbub, ctx,
			&hubbub_reg,
			&hubbub_shअगरt,
			&hubbub_mask);

	क्रम (i = 0; i < res_cap_nv10.num_vmid; i++) अणु
		काष्ठा dcn20_vmid *vmid = &hubbub->vmid[i];

		vmid->ctx = ctx;

		vmid->regs = &vmid_regs[i];
		vmid->shअगरts = &vmid_shअगरts;
		vmid->masks = &vmid_masks;
	पूर्ण

	वापस &hubbub->base;
पूर्ण

काष्ठा timing_generator *dcn20_timing_generator_create(
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t instance)
अणु
	काष्ठा optc *tgn10 =
		kzalloc(माप(काष्ठा optc), GFP_ATOMIC);

	अगर (!tgn10)
		वापस शून्य;

	tgn10->base.inst = instance;
	tgn10->base.ctx = ctx;

	tgn10->tg_regs = &tg_regs[instance];
	tgn10->tg_shअगरt = &tg_shअगरt;
	tgn10->tg_mask = &tg_mask;

	dcn20_timing_generator_init(tgn10);

	वापस &tgn10->base;
पूर्ण

अटल स्थिर काष्ठा encoder_feature_support link_enc_feature = अणु
		.max_hdmi_deep_color = COLOR_DEPTH_121212,
		.max_hdmi_pixel_घड़ी = 600000,
		.hdmi_ycbcr420_supported = true,
		.dp_ycbcr420_supported = true,
		.fec_supported = true,
		.flags.bits.IS_HBR2_CAPABLE = true,
		.flags.bits.IS_HBR3_CAPABLE = true,
		.flags.bits.IS_TPS3_CAPABLE = true,
		.flags.bits.IS_TPS4_CAPABLE = true
पूर्ण;

काष्ठा link_encoder *dcn20_link_encoder_create(
	स्थिर काष्ठा encoder_init_data *enc_init_data)
अणु
	काष्ठा dcn20_link_encoder *enc20 =
		kzalloc(माप(काष्ठा dcn20_link_encoder), GFP_KERNEL);
	पूर्णांक link_regs_id;

	अगर (!enc20)
		वापस शून्य;

	link_regs_id =
		map_transmitter_id_to_phy_instance(enc_init_data->transmitter);

	dcn20_link_encoder_स्थिरruct(enc20,
				      enc_init_data,
				      &link_enc_feature,
				      &link_enc_regs[link_regs_id],
				      &link_enc_aux_regs[enc_init_data->channel - 1],
				      &link_enc_hpd_regs[enc_init_data->hpd_source],
				      &le_shअगरt,
				      &le_mask);

	वापस &enc20->enc10.base;
पूर्ण

अटल काष्ठा panel_cntl *dcn20_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
अणु
	काष्ठा dce_panel_cntl *panel_cntl =
		kzalloc(माप(काष्ठा dce_panel_cntl), GFP_KERNEL);

	अगर (!panel_cntl)
		वापस शून्य;

	dce_panel_cntl_स्थिरruct(panel_cntl,
			init_data,
			&panel_cntl_regs[init_data->inst],
			&panel_cntl_shअगरt,
			&panel_cntl_mask);

	वापस &panel_cntl->base;
पूर्ण

अटल काष्ठा घड़ी_source *dcn20_घड़ी_source_create(
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	bool dp_clk_src)
अणु
	काष्ठा dce110_clk_src *clk_src =
		kzalloc(माप(काष्ठा dce110_clk_src), GFP_ATOMIC);

	अगर (!clk_src)
		वापस शून्य;

	अगर (dcn20_clk_src_स्थिरruct(clk_src, ctx, bios, id,
			regs, &cs_shअगरt, &cs_mask)) अणु
		clk_src->base.dp_clk_src = dp_clk_src;
		वापस &clk_src->base;
	पूर्ण

	kमुक्त(clk_src);
	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

अटल व्योम पढ़ो_dce_straps(
	काष्ठा dc_context *ctx,
	काष्ठा resource_straps *straps)
अणु
	generic_reg_get(ctx, mmDC_PINSTRAPS + BASE(mmDC_PINSTRAPS_BASE_IDX),
		FN(DC_PINSTRAPS, DC_PINSTRAPS_AUDIO), &straps->dc_pinstraps_audio);
पूर्ण

अटल काष्ठा audio *dcn20_create_audio(
		काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst,
			&audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

काष्ठा stream_encoder *dcn20_stream_encoder_create(
	क्रमागत engine_id eng_id,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn10_stream_encoder *enc1 =
		kzalloc(माप(काष्ठा dcn10_stream_encoder), GFP_KERNEL);

	अगर (!enc1)
		वापस शून्य;

	अगर (ASICREV_IS_NAVI14_M(ctx->asic_id.hw_पूर्णांकernal_rev)) अणु
		अगर (eng_id >= ENGINE_ID_DIGD)
			eng_id++;
	पूर्ण

	dcn20_stream_encoder_स्थिरruct(enc1, ctx, ctx->dc_bios, eng_id,
					&stream_enc_regs[eng_id],
					&se_shअगरt, &se_mask);

	वापस &enc1->base;
पूर्ण

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCN2_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCN2_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCN2_MASK_SH_LIST(_MASK)
पूर्ण;

काष्ठा dce_hwseq *dcn20_hwseq_create(
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dce_hwseq *hws = kzalloc(माप(काष्ठा dce_hwseq), GFP_KERNEL);

	अगर (hws) अणु
		hws->ctx = ctx;
		hws->regs = &hwseq_reg;
		hws->shअगरts = &hwseq_shअगरt;
		hws->masks = &hwseq_mask;
	पूर्ण
	वापस hws;
पूर्ण

अटल स्थिर काष्ठा resource_create_funcs res_create_funcs = अणु
	.पढ़ो_dce_straps = पढ़ो_dce_straps,
	.create_audio = dcn20_create_audio,
	.create_stream_encoder = dcn20_stream_encoder_create,
	.create_hwseq = dcn20_hwseq_create,
पूर्ण;

अटल स्थिर काष्ठा resource_create_funcs res_create_maximus_funcs = अणु
	.पढ़ो_dce_straps = शून्य,
	.create_audio = शून्य,
	.create_stream_encoder = शून्य,
	.create_hwseq = dcn20_hwseq_create,
पूर्ण;

अटल व्योम dcn20_pp_smu_destroy(काष्ठा pp_smu_funcs **pp_smu);

व्योम dcn20_घड़ी_source_destroy(काष्ठा घड़ी_source **clk_src)
अणु
	kमुक्त(TO_DCE110_CLK_SRC(*clk_src));
	*clk_src = शून्य;
पूर्ण


काष्ठा display_stream_compressor *dcn20_dsc_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_dsc *dsc =
		kzalloc(माप(काष्ठा dcn20_dsc), GFP_ATOMIC);

	अगर (!dsc) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dsc2_स्थिरruct(dsc, ctx, inst, &dsc_regs[inst], &dsc_shअगरt, &dsc_mask);
	वापस &dsc->base;
पूर्ण

व्योम dcn20_dsc_destroy(काष्ठा display_stream_compressor **dsc)
अणु
	kमुक्त(container_of(*dsc, काष्ठा dcn20_dsc, base));
	*dsc = शून्य;
पूर्ण


अटल व्योम dcn20_resource_deकाष्ठा(काष्ठा dcn20_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pool->base.stream_enc_count; i++) अणु
		अगर (pool->base.stream_enc[i] != शून्य) अणु
			kमुक्त(DCN10STRENC_FROM_STRENC(pool->base.stream_enc[i]));
			pool->base.stream_enc[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_dsc; i++) अणु
		अगर (pool->base.dscs[i] != शून्य)
			dcn20_dsc_destroy(&pool->base.dscs[i]);
	पूर्ण

	अगर (pool->base.mpc != शून्य) अणु
		kमुक्त(TO_DCN20_MPC(pool->base.mpc));
		pool->base.mpc = शून्य;
	पूर्ण
	अगर (pool->base.hubbub != शून्य) अणु
		kमुक्त(pool->base.hubbub);
		pool->base.hubbub = शून्य;
	पूर्ण
	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		अगर (pool->base.dpps[i] != शून्य)
			dcn20_dpp_destroy(&pool->base.dpps[i]);

		अगर (pool->base.ipps[i] != शून्य)
			pool->base.ipps[i]->funcs->ipp_destroy(&pool->base.ipps[i]);

		अगर (pool->base.hubps[i] != शून्य) अणु
			kमुक्त(TO_DCN20_HUBP(pool->base.hubps[i]));
			pool->base.hubps[i] = शून्य;
		पूर्ण

		अगर (pool->base.irqs != शून्य) अणु
			dal_irq_service_destroy(&pool->base.irqs);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		अगर (pool->base.engines[i] != शून्य)
			dce110_engine_destroy(&pool->base.engines[i]);
		अगर (pool->base.hw_i2cs[i] != शून्य) अणु
			kमुक्त(pool->base.hw_i2cs[i]);
			pool->base.hw_i2cs[i] = शून्य;
		पूर्ण
		अगर (pool->base.sw_i2cs[i] != शून्य) अणु
			kमुक्त(pool->base.sw_i2cs[i]);
			pool->base.sw_i2cs[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_opp; i++) अणु
		अगर (pool->base.opps[i] != शून्य)
			pool->base.opps[i]->funcs->opp_destroy(&pool->base.opps[i]);
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_timing_generator; i++) अणु
		अगर (pool->base.timing_generators[i] != शून्य)	अणु
			kमुक्त(DCN10TG_FROM_TG(pool->base.timing_generators[i]));
			pool->base.timing_generators[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_dwb; i++) अणु
		अगर (pool->base.dwbc[i] != शून्य) अणु
			kमुक्त(TO_DCN20_DWBC(pool->base.dwbc[i]));
			pool->base.dwbc[i] = शून्य;
		पूर्ण
		अगर (pool->base.mcअगर_wb[i] != शून्य) अणु
			kमुक्त(TO_DCN20_MMHUBBUB(pool->base.mcअगर_wb[i]));
			pool->base.mcअगर_wb[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.audio_count; i++) अणु
		अगर (pool->base.audios[i])
			dce_aud_destroy(&pool->base.audios[i]);
	पूर्ण

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] != शून्य) अणु
			dcn20_घड़ी_source_destroy(&pool->base.घड़ी_sources[i]);
			pool->base.घड़ी_sources[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (pool->base.dp_घड़ी_source != शून्य) अणु
		dcn20_घड़ी_source_destroy(&pool->base.dp_घड़ी_source);
		pool->base.dp_घड़ी_source = शून्य;
	पूर्ण


	अगर (pool->base.abm != शून्य)
		dce_abm_destroy(&pool->base.abm);

	अगर (pool->base.dmcu != शून्य)
		dce_dmcu_destroy(&pool->base.dmcu);

	अगर (pool->base.dccg != शून्य)
		dcn_dccg_destroy(&pool->base.dccg);

	अगर (pool->base.pp_smu != शून्य)
		dcn20_pp_smu_destroy(&pool->base.pp_smu);

	अगर (pool->base.oem_device != शून्य)
		dal_ddc_service_destroy(&pool->base.oem_device);
पूर्ण

काष्ठा hubp *dcn20_hubp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_hubp *hubp2 =
		kzalloc(माप(काष्ठा dcn20_hubp), GFP_ATOMIC);

	अगर (!hubp2)
		वापस शून्य;

	अगर (hubp2_स्थिरruct(hubp2, ctx, inst,
			&hubp_regs[inst], &hubp_shअगरt, &hubp_mask))
		वापस &hubp2->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(hubp2);
	वापस शून्य;
पूर्ण

अटल व्योम get_pixel_घड़ी_parameters(
	काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा pixel_clk_params *pixel_clk_params)
अणु
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;
	काष्ठा pipe_ctx *odm_pipe;
	पूर्णांक opp_cnt = 1;

	क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		opp_cnt++;

	pixel_clk_params->requested_pix_clk_100hz = stream->timing.pix_clk_100hz;
	pixel_clk_params->encoder_object_id = stream->link->link_enc->id;
	pixel_clk_params->संकेत_type = pipe_ctx->stream->संकेत;
	pixel_clk_params->controller_id = pipe_ctx->stream_res.tg->inst + 1;
	/* TODO: un-hardcode*/
	pixel_clk_params->requested_sym_clk = LINK_RATE_LOW *
		LINK_RATE_REF_FREQ_IN_KHZ;
	pixel_clk_params->flags.ENABLE_SS = 0;
	pixel_clk_params->color_depth =
		stream->timing.display_color_depth;
	pixel_clk_params->flags.DISPLAY_BLANKED = 1;
	pixel_clk_params->pixel_encoding = stream->timing.pixel_encoding;

	अगर (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR422)
		pixel_clk_params->color_depth = COLOR_DEPTH_888;

	अगर (opp_cnt == 4)
		pixel_clk_params->requested_pix_clk_100hz /= 4;
	अन्यथा अगर (optc2_is_two_pixels_per_contaपूर्णांकer(&stream->timing) || opp_cnt == 2)
		pixel_clk_params->requested_pix_clk_100hz /= 2;

	अगर (stream->timing.timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
		pixel_clk_params->requested_pix_clk_100hz *= 2;

पूर्ण

अटल व्योम build_clamping_params(काष्ठा dc_stream_state *stream)
अणु
	stream->clamping.clamping_level = CLAMPING_FULL_RANGE;
	stream->clamping.c_depth = stream->timing.display_color_depth;
	stream->clamping.pixel_encoding = stream->timing.pixel_encoding;
पूर्ण

अटल क्रमागत dc_status build_pipe_hw_param(काष्ठा pipe_ctx *pipe_ctx)
अणु

	get_pixel_घड़ी_parameters(pipe_ctx, &pipe_ctx->stream_res.pix_clk_params);

	pipe_ctx->घड़ी_source->funcs->get_pix_clk_भागiders(
		pipe_ctx->घड़ी_source,
		&pipe_ctx->stream_res.pix_clk_params,
		&pipe_ctx->pll_settings);

	pipe_ctx->stream->clamping.pixel_encoding = pipe_ctx->stream->timing.pixel_encoding;

	resource_build_bit_depth_reduction_params(pipe_ctx->stream,
					&pipe_ctx->stream->bit_depth_params);
	build_clamping_params(pipe_ctx->stream);

	वापस DC_OK;
पूर्ण

क्रमागत dc_status dcn20_build_mapped_resource(स्थिर काष्ठा dc *dc, काष्ठा dc_state *context, काष्ठा dc_stream_state *stream)
अणु
	क्रमागत dc_status status = DC_OK;
	काष्ठा pipe_ctx *pipe_ctx = resource_get_head_pipe_क्रम_stream(&context->res_ctx, stream);

	अगर (!pipe_ctx)
		वापस DC_ERROR_UNEXPECTED;


	status = build_pipe_hw_param(pipe_ctx);

	वापस status;
पूर्ण


व्योम dcn20_acquire_dsc(स्थिर काष्ठा dc *dc,
			काष्ठा resource_context *res_ctx,
			काष्ठा display_stream_compressor **dsc,
			पूर्णांक pipe_idx)
अणु
	पूर्णांक i;
	स्थिर काष्ठा resource_pool *pool = dc->res_pool;
	काष्ठा display_stream_compressor *dsc_old = dc->current_state->res_ctx.pipe_ctx[pipe_idx].stream_res.dsc;

	ASSERT(*dsc == शून्य); /* If this ASSERT fails, dsc was not released properly */
	*dsc = शून्य;

	/* Always करो 1-to-1 mapping when number of DSCs is same as number of pipes */
	अगर (pool->res_cap->num_dsc == pool->res_cap->num_opp) अणु
		*dsc = pool->dscs[pipe_idx];
		res_ctx->is_dsc_acquired[pipe_idx] = true;
		वापस;
	पूर्ण

	/* Return old DSC to aव्योम the need क्रम re-programming */
	अगर (dsc_old && !res_ctx->is_dsc_acquired[dsc_old->inst]) अणु
		*dsc = dsc_old;
		res_ctx->is_dsc_acquired[dsc_old->inst] = true;
		वापस ;
	पूर्ण

	/* Find first मुक्त DSC */
	क्रम (i = 0; i < pool->res_cap->num_dsc; i++)
		अगर (!res_ctx->is_dsc_acquired[i]) अणु
			*dsc = pool->dscs[i];
			res_ctx->is_dsc_acquired[i] = true;
			अवरोध;
		पूर्ण
पूर्ण

व्योम dcn20_release_dsc(काष्ठा resource_context *res_ctx,
			स्थिर काष्ठा resource_pool *pool,
			काष्ठा display_stream_compressor **dsc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pool->res_cap->num_dsc; i++)
		अगर (pool->dscs[i] == *dsc) अणु
			res_ctx->is_dsc_acquired[i] = false;
			*dsc = शून्य;
			अवरोध;
		पूर्ण
पूर्ण



क्रमागत dc_status dcn20_add_dsc_to_stream_resource(काष्ठा dc *dc,
		काष्ठा dc_state *dc_ctx,
		काष्ठा dc_stream_state *dc_stream)
अणु
	क्रमागत dc_status result = DC_OK;
	पूर्णांक i;

	/* Get a DSC अगर required and available */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &dc_ctx->res_ctx.pipe_ctx[i];

		अगर (pipe_ctx->stream != dc_stream)
			जारी;

		अगर (pipe_ctx->stream_res.dsc)
			जारी;

		dcn20_acquire_dsc(dc, &dc_ctx->res_ctx, &pipe_ctx->stream_res.dsc, i);

		/* The number of DSCs can be less than the number of pipes */
		अगर (!pipe_ctx->stream_res.dsc) अणु
			result = DC_NO_DSC_RESOURCE;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस result;
पूर्ण


अटल क्रमागत dc_status हटाओ_dsc_from_stream_resource(काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *dc_stream)
अणु
	काष्ठा pipe_ctx *pipe_ctx = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_PIPES; i++) अणु
		अगर (new_ctx->res_ctx.pipe_ctx[i].stream == dc_stream && !new_ctx->res_ctx.pipe_ctx[i].top_pipe) अणु
			pipe_ctx = &new_ctx->res_ctx.pipe_ctx[i];

			अगर (pipe_ctx->stream_res.dsc)
				dcn20_release_dsc(&new_ctx->res_ctx, dc->res_pool, &pipe_ctx->stream_res.dsc);
		पूर्ण
	पूर्ण

	अगर (!pipe_ctx)
		वापस DC_ERROR_UNEXPECTED;
	अन्यथा
		वापस DC_OK;
पूर्ण


क्रमागत dc_status dcn20_add_stream_to_ctx(काष्ठा dc *dc, काष्ठा dc_state *new_ctx, काष्ठा dc_stream_state *dc_stream)
अणु
	क्रमागत dc_status result = DC_ERROR_UNEXPECTED;

	result = resource_map_pool_resources(dc, new_ctx, dc_stream);

	अगर (result == DC_OK)
		result = resource_map_phy_घड़ी_resources(dc, new_ctx, dc_stream);

	/* Get a DSC अगर required and available */
	अगर (result == DC_OK && dc_stream->timing.flags.DSC)
		result = dcn20_add_dsc_to_stream_resource(dc, new_ctx, dc_stream);

	अगर (result == DC_OK)
		result = dcn20_build_mapped_resource(dc, new_ctx, dc_stream);

	वापस result;
पूर्ण


क्रमागत dc_status dcn20_हटाओ_stream_from_ctx(काष्ठा dc *dc, काष्ठा dc_state *new_ctx, काष्ठा dc_stream_state *dc_stream)
अणु
	क्रमागत dc_status result = DC_OK;

	result = हटाओ_dsc_from_stream_resource(dc, new_ctx, dc_stream);

	वापस result;
पूर्ण


अटल व्योम swizzle_to_dml_params(
		क्रमागत swizzle_mode_values swizzle,
		अचिन्हित पूर्णांक *sw_mode)
अणु
	चयन (swizzle) अणु
	हाल DC_SW_LINEAR:
		*sw_mode = dm_sw_linear;
		अवरोध;
	हाल DC_SW_4KB_S:
		*sw_mode = dm_sw_4kb_s;
		अवरोध;
	हाल DC_SW_4KB_S_X:
		*sw_mode = dm_sw_4kb_s_x;
		अवरोध;
	हाल DC_SW_4KB_D:
		*sw_mode = dm_sw_4kb_d;
		अवरोध;
	हाल DC_SW_4KB_D_X:
		*sw_mode = dm_sw_4kb_d_x;
		अवरोध;
	हाल DC_SW_64KB_S:
		*sw_mode = dm_sw_64kb_s;
		अवरोध;
	हाल DC_SW_64KB_S_X:
		*sw_mode = dm_sw_64kb_s_x;
		अवरोध;
	हाल DC_SW_64KB_S_T:
		*sw_mode = dm_sw_64kb_s_t;
		अवरोध;
	हाल DC_SW_64KB_D:
		*sw_mode = dm_sw_64kb_d;
		अवरोध;
	हाल DC_SW_64KB_D_X:
		*sw_mode = dm_sw_64kb_d_x;
		अवरोध;
	हाल DC_SW_64KB_D_T:
		*sw_mode = dm_sw_64kb_d_t;
		अवरोध;
	हाल DC_SW_64KB_R_X:
		*sw_mode = dm_sw_64kb_r_x;
		अवरोध;
	हाल DC_SW_VAR_S:
		*sw_mode = dm_sw_var_s;
		अवरोध;
	हाल DC_SW_VAR_S_X:
		*sw_mode = dm_sw_var_s_x;
		अवरोध;
	हाल DC_SW_VAR_D:
		*sw_mode = dm_sw_var_d;
		अवरोध;
	हाल DC_SW_VAR_D_X:
		*sw_mode = dm_sw_var_d_x;
		अवरोध;

	शेष:
		ASSERT(0); /* Not supported */
		अवरोध;
	पूर्ण
पूर्ण

bool dcn20_split_stream_क्रम_odm(
		स्थिर काष्ठा dc *dc,
		काष्ठा resource_context *res_ctx,
		काष्ठा pipe_ctx *prev_odm_pipe,
		काष्ठा pipe_ctx *next_odm_pipe)
अणु
	पूर्णांक pipe_idx = next_odm_pipe->pipe_idx;
	स्थिर काष्ठा resource_pool *pool = dc->res_pool;

	*next_odm_pipe = *prev_odm_pipe;

	next_odm_pipe->pipe_idx = pipe_idx;
	next_odm_pipe->plane_res.mi = pool->mis[next_odm_pipe->pipe_idx];
	next_odm_pipe->plane_res.hubp = pool->hubps[next_odm_pipe->pipe_idx];
	next_odm_pipe->plane_res.ipp = pool->ipps[next_odm_pipe->pipe_idx];
	next_odm_pipe->plane_res.xfm = pool->transक्रमms[next_odm_pipe->pipe_idx];
	next_odm_pipe->plane_res.dpp = pool->dpps[next_odm_pipe->pipe_idx];
	next_odm_pipe->plane_res.mpcc_inst = pool->dpps[next_odm_pipe->pipe_idx]->inst;
	next_odm_pipe->stream_res.dsc = शून्य;
	अगर (prev_odm_pipe->next_odm_pipe && prev_odm_pipe->next_odm_pipe != next_odm_pipe) अणु
		next_odm_pipe->next_odm_pipe = prev_odm_pipe->next_odm_pipe;
		next_odm_pipe->next_odm_pipe->prev_odm_pipe = next_odm_pipe;
	पूर्ण
	अगर (prev_odm_pipe->top_pipe && prev_odm_pipe->top_pipe->next_odm_pipe) अणु
		prev_odm_pipe->top_pipe->next_odm_pipe->bottom_pipe = next_odm_pipe;
		next_odm_pipe->top_pipe = prev_odm_pipe->top_pipe->next_odm_pipe;
	पूर्ण
	अगर (prev_odm_pipe->bottom_pipe && prev_odm_pipe->bottom_pipe->next_odm_pipe) अणु
		prev_odm_pipe->bottom_pipe->next_odm_pipe->top_pipe = next_odm_pipe;
		next_odm_pipe->bottom_pipe = prev_odm_pipe->bottom_pipe->next_odm_pipe;
	पूर्ण
	prev_odm_pipe->next_odm_pipe = next_odm_pipe;
	next_odm_pipe->prev_odm_pipe = prev_odm_pipe;

	अगर (prev_odm_pipe->plane_state) अणु
		काष्ठा scaler_data *sd = &prev_odm_pipe->plane_res.scl_data;
		पूर्णांक new_width;

		/* HACTIVE halved क्रम odm combine */
		sd->h_active /= 2;
		/* Calculate new vp and recout क्रम left pipe */
		/* Need at least 16 pixels width per side */
		अगर (sd->recout.x + 16 >= sd->h_active)
			वापस false;
		new_width = sd->h_active - sd->recout.x;
		sd->viewport.width -= dc_fixpt_न्यूनमान(dc_fixpt_mul_पूर्णांक(
				sd->ratios.horz, sd->recout.width - new_width));
		sd->viewport_c.width -= dc_fixpt_न्यूनमान(dc_fixpt_mul_पूर्णांक(
				sd->ratios.horz_c, sd->recout.width - new_width));
		sd->recout.width = new_width;

		/* Calculate new vp and recout क्रम right pipe */
		sd = &next_odm_pipe->plane_res.scl_data;
		/* HACTIVE halved क्रम odm combine */
		sd->h_active /= 2;
		/* Need at least 16 pixels width per side */
		अगर (new_width <= 16)
			वापस false;
		new_width = sd->recout.width + sd->recout.x - sd->h_active;
		sd->viewport.width -= dc_fixpt_न्यूनमान(dc_fixpt_mul_पूर्णांक(
				sd->ratios.horz, sd->recout.width - new_width));
		sd->viewport_c.width -= dc_fixpt_न्यूनमान(dc_fixpt_mul_पूर्णांक(
				sd->ratios.horz_c, sd->recout.width - new_width));
		sd->recout.width = new_width;
		sd->viewport.x += dc_fixpt_न्यूनमान(dc_fixpt_mul_पूर्णांक(
				sd->ratios.horz, sd->h_active - sd->recout.x));
		sd->viewport_c.x += dc_fixpt_न्यूनमान(dc_fixpt_mul_पूर्णांक(
				sd->ratios.horz_c, sd->h_active - sd->recout.x));
		sd->recout.x = 0;
	पूर्ण
	अगर (!next_odm_pipe->top_pipe)
		next_odm_pipe->stream_res.opp = pool->opps[next_odm_pipe->pipe_idx];
	अन्यथा
		next_odm_pipe->stream_res.opp = next_odm_pipe->top_pipe->stream_res.opp;
	अगर (next_odm_pipe->stream->timing.flags.DSC == 1 && !next_odm_pipe->top_pipe) अणु
		dcn20_acquire_dsc(dc, res_ctx, &next_odm_pipe->stream_res.dsc, next_odm_pipe->pipe_idx);
		ASSERT(next_odm_pipe->stream_res.dsc);
		अगर (next_odm_pipe->stream_res.dsc == शून्य)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम dcn20_split_stream_क्रम_mpc(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा pipe_ctx *primary_pipe,
		काष्ठा pipe_ctx *secondary_pipe)
अणु
	पूर्णांक pipe_idx = secondary_pipe->pipe_idx;
	काष्ठा pipe_ctx *sec_bot_pipe = secondary_pipe->bottom_pipe;

	*secondary_pipe = *primary_pipe;
	secondary_pipe->bottom_pipe = sec_bot_pipe;

	secondary_pipe->pipe_idx = pipe_idx;
	secondary_pipe->plane_res.mi = pool->mis[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.hubp = pool->hubps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.ipp = pool->ipps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.xfm = pool->transक्रमms[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.dpp = pool->dpps[secondary_pipe->pipe_idx];
	secondary_pipe->plane_res.mpcc_inst = pool->dpps[secondary_pipe->pipe_idx]->inst;
	secondary_pipe->stream_res.dsc = शून्य;
	अगर (primary_pipe->bottom_pipe && primary_pipe->bottom_pipe != secondary_pipe) अणु
		ASSERT(!secondary_pipe->bottom_pipe);
		secondary_pipe->bottom_pipe = primary_pipe->bottom_pipe;
		secondary_pipe->bottom_pipe->top_pipe = secondary_pipe;
	पूर्ण
	primary_pipe->bottom_pipe = secondary_pipe;
	secondary_pipe->top_pipe = primary_pipe;

	ASSERT(primary_pipe->plane_state);
पूर्ण

व्योम dcn20_populate_dml_ग_लिखोback_from_context(
		काष्ठा dc *dc, काष्ठा resource_context *res_ctx, display_e2e_pipe_params_st *pipes)
अणु
	पूर्णांक pipe_cnt, i;

	क्रम (i = 0, pipe_cnt = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा dc_ग_लिखोback_info *wb_info = &res_ctx->pipe_ctx[i].stream->ग_लिखोback_info[0];

		अगर (!res_ctx->pipe_ctx[i].stream)
			जारी;

		/* Set ग_लिखोback inक्रमmation */
		pipes[pipe_cnt].करोut.wb_enable = (wb_info->wb_enabled == true) ? 1 : 0;
		pipes[pipe_cnt].करोut.num_active_wb++;
		pipes[pipe_cnt].करोut.wb.wb_src_height = wb_info->dwb_params.cnv_params.crop_height;
		pipes[pipe_cnt].करोut.wb.wb_src_width = wb_info->dwb_params.cnv_params.crop_width;
		pipes[pipe_cnt].करोut.wb.wb_dst_width = wb_info->dwb_params.dest_width;
		pipes[pipe_cnt].करोut.wb.wb_dst_height = wb_info->dwb_params.dest_height;
		pipes[pipe_cnt].करोut.wb.wb_htaps_luma = 1;
		pipes[pipe_cnt].करोut.wb.wb_vtaps_luma = 1;
		pipes[pipe_cnt].करोut.wb.wb_htaps_chroma = wb_info->dwb_params.scaler_taps.h_taps_c;
		pipes[pipe_cnt].करोut.wb.wb_vtaps_chroma = wb_info->dwb_params.scaler_taps.v_taps_c;
		pipes[pipe_cnt].करोut.wb.wb_hratio = 1.0;
		pipes[pipe_cnt].करोut.wb.wb_vratio = 1.0;
		अगर (wb_info->dwb_params.out_क्रमmat == dwb_scaler_mode_yuv420) अणु
			अगर (wb_info->dwb_params.output_depth == DWB_OUTPUT_PIXEL_DEPTH_8BPC)
				pipes[pipe_cnt].करोut.wb.wb_pixel_क्रमmat = dm_420_8;
			अन्यथा
				pipes[pipe_cnt].करोut.wb.wb_pixel_क्रमmat = dm_420_10;
		पूर्ण अन्यथा
			pipes[pipe_cnt].करोut.wb.wb_pixel_क्रमmat = dm_444_32;

		pipe_cnt++;
	पूर्ण

पूर्ण

पूर्णांक dcn20_populate_dml_pipes_from_context(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		bool fast_validate)
अणु
	पूर्णांक pipe_cnt, i;
	bool synchronized_vblank = true;
	काष्ठा resource_context *res_ctx = &context->res_ctx;

	क्रम (i = 0, pipe_cnt = -1; i < dc->res_pool->pipe_count; i++) अणु
		अगर (!res_ctx->pipe_ctx[i].stream)
			जारी;

		अगर (pipe_cnt < 0) अणु
			pipe_cnt = i;
			जारी;
		पूर्ण

		अगर (res_ctx->pipe_ctx[pipe_cnt].stream == res_ctx->pipe_ctx[i].stream)
			जारी;

		अगर (dc->debug.disable_timing_sync ||
			(!resource_are_streams_timing_synchronizable(
				res_ctx->pipe_ctx[pipe_cnt].stream,
				res_ctx->pipe_ctx[i].stream) &&
			!resource_are_vblanks_synchronizable(
				res_ctx->pipe_ctx[pipe_cnt].stream,
				res_ctx->pipe_ctx[i].stream))) अणु
			synchronized_vblank = false;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (i = 0, pipe_cnt = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा dc_crtc_timing *timing = &res_ctx->pipe_ctx[i].stream->timing;
		अचिन्हित पूर्णांक v_total;
		अचिन्हित पूर्णांक front_porch;
		पूर्णांक output_bpc;
		काष्ठा audio_check aud_check = अणु0पूर्ण;

		अगर (!res_ctx->pipe_ctx[i].stream)
			जारी;

		v_total = timing->v_total;
		front_porch = timing->v_front_porch;

		/* toकरो:
		pipes[pipe_cnt].pipe.src.dynamic_metadata_enable = 0;
		pipes[pipe_cnt].pipe.src.dcc = 0;
		pipes[pipe_cnt].pipe.src.vm = 0;*/

		pipes[pipe_cnt].clks_cfg.refclk_mhz = dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000.0;

		pipes[pipe_cnt].करोut.dsc_enable = res_ctx->pipe_ctx[i].stream->timing.flags.DSC;
		/* toकरो: rotation?*/
		pipes[pipe_cnt].करोut.dsc_slices = res_ctx->pipe_ctx[i].stream->timing.dsc_cfg.num_slices_h;
		अगर (res_ctx->pipe_ctx[i].stream->use_dynamic_meta) अणु
			pipes[pipe_cnt].pipe.src.dynamic_metadata_enable = true;
			/* 1/2 vblank */
			pipes[pipe_cnt].pipe.src.dynamic_metadata_lines_beक्रमe_active =
				(v_total - timing->v_addressable
					- timing->v_border_top - timing->v_border_bottom) / 2;
			/* 36 bytes dp, 32 hdmi */
			pipes[pipe_cnt].pipe.src.dynamic_metadata_xmit_bytes =
				dc_is_dp_संकेत(res_ctx->pipe_ctx[i].stream->संकेत) ? 36 : 32;
		पूर्ण
		pipes[pipe_cnt].pipe.src.dcc = false;
		pipes[pipe_cnt].pipe.src.dcc_rate = 1;
		pipes[pipe_cnt].pipe.dest.synchronized_vblank_all_planes = synchronized_vblank;
		pipes[pipe_cnt].pipe.dest.hblank_start = timing->h_total - timing->h_front_porch;
		pipes[pipe_cnt].pipe.dest.hblank_end = pipes[pipe_cnt].pipe.dest.hblank_start
				- timing->h_addressable
				- timing->h_border_left
				- timing->h_border_right;
		pipes[pipe_cnt].pipe.dest.vblank_start = v_total - front_porch;
		pipes[pipe_cnt].pipe.dest.vblank_end = pipes[pipe_cnt].pipe.dest.vblank_start
				- timing->v_addressable
				- timing->v_border_top
				- timing->v_border_bottom;
		pipes[pipe_cnt].pipe.dest.htotal = timing->h_total;
		pipes[pipe_cnt].pipe.dest.vtotal = v_total;
		pipes[pipe_cnt].pipe.dest.hactive = timing->h_addressable;
		pipes[pipe_cnt].pipe.dest.vactive = timing->v_addressable;
		pipes[pipe_cnt].pipe.dest.पूर्णांकerlaced = timing->flags.INTERLACE;
		pipes[pipe_cnt].pipe.dest.pixel_rate_mhz = timing->pix_clk_100hz/10000.0;
		अगर (timing->timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
			pipes[pipe_cnt].pipe.dest.pixel_rate_mhz *= 2;
		pipes[pipe_cnt].pipe.dest.otg_inst = res_ctx->pipe_ctx[i].stream_res.tg->inst;
		pipes[pipe_cnt].करोut.dp_lanes = 4;
		pipes[pipe_cnt].करोut.is_भव = 0;
		pipes[pipe_cnt].pipe.dest.vtotal_min = res_ctx->pipe_ctx[i].stream->adjust.v_total_min;
		pipes[pipe_cnt].pipe.dest.vtotal_max = res_ctx->pipe_ctx[i].stream->adjust.v_total_max;
		चयन (get_num_odm_splits(&res_ctx->pipe_ctx[i])) अणु
		हाल 1:
			pipes[pipe_cnt].pipe.dest.odm_combine = dm_odm_combine_mode_2to1;
			अवरोध;
		हाल 3:
			pipes[pipe_cnt].pipe.dest.odm_combine = dm_odm_combine_mode_4to1;
			अवरोध;
		शेष:
			pipes[pipe_cnt].pipe.dest.odm_combine = dm_odm_combine_mode_disabled;
		पूर्ण
		pipes[pipe_cnt].pipe.src.hsplit_grp = res_ctx->pipe_ctx[i].pipe_idx;
		अगर (res_ctx->pipe_ctx[i].top_pipe && res_ctx->pipe_ctx[i].top_pipe->plane_state
				== res_ctx->pipe_ctx[i].plane_state) अणु
			काष्ठा pipe_ctx *first_pipe = res_ctx->pipe_ctx[i].top_pipe;
			पूर्णांक split_idx = 0;

			जबतक (first_pipe->top_pipe && first_pipe->top_pipe->plane_state
					== res_ctx->pipe_ctx[i].plane_state) अणु
				first_pipe = first_pipe->top_pipe;
				split_idx++;
			पूर्ण
			/* Treat 4to1 mpc combine as an mpo of 2 2-to-1 combines */
			अगर (split_idx == 0)
				pipes[pipe_cnt].pipe.src.hsplit_grp = first_pipe->pipe_idx;
			अन्यथा अगर (split_idx == 1)
				pipes[pipe_cnt].pipe.src.hsplit_grp = res_ctx->pipe_ctx[i].pipe_idx;
			अन्यथा अगर (split_idx == 2)
				pipes[pipe_cnt].pipe.src.hsplit_grp = res_ctx->pipe_ctx[i].top_pipe->pipe_idx;
		पूर्ण अन्यथा अगर (res_ctx->pipe_ctx[i].prev_odm_pipe) अणु
			काष्ठा pipe_ctx *first_pipe = res_ctx->pipe_ctx[i].prev_odm_pipe;

			जबतक (first_pipe->prev_odm_pipe)
				first_pipe = first_pipe->prev_odm_pipe;
			pipes[pipe_cnt].pipe.src.hsplit_grp = first_pipe->pipe_idx;
		पूर्ण

		चयन (res_ctx->pipe_ctx[i].stream->संकेत) अणु
		हाल SIGNAL_TYPE_DISPLAY_PORT_MST:
		हाल SIGNAL_TYPE_DISPLAY_PORT:
			pipes[pipe_cnt].करोut.output_type = dm_dp;
			अवरोध;
		हाल SIGNAL_TYPE_EDP:
			pipes[pipe_cnt].करोut.output_type = dm_edp;
			अवरोध;
		हाल SIGNAL_TYPE_HDMI_TYPE_A:
		हाल SIGNAL_TYPE_DVI_SINGLE_LINK:
		हाल SIGNAL_TYPE_DVI_DUAL_LINK:
			pipes[pipe_cnt].करोut.output_type = dm_hdmi;
			अवरोध;
		शेष:
			/* In हाल there is no संकेत, set dp with 4 lanes to allow max config */
			pipes[pipe_cnt].करोut.is_भव = 1;
			pipes[pipe_cnt].करोut.output_type = dm_dp;
			pipes[pipe_cnt].करोut.dp_lanes = 4;
		पूर्ण

		चयन (res_ctx->pipe_ctx[i].stream->timing.display_color_depth) अणु
		हाल COLOR_DEPTH_666:
			output_bpc = 6;
			अवरोध;
		हाल COLOR_DEPTH_888:
			output_bpc = 8;
			अवरोध;
		हाल COLOR_DEPTH_101010:
			output_bpc = 10;
			अवरोध;
		हाल COLOR_DEPTH_121212:
			output_bpc = 12;
			अवरोध;
		हाल COLOR_DEPTH_141414:
			output_bpc = 14;
			अवरोध;
		हाल COLOR_DEPTH_161616:
			output_bpc = 16;
			अवरोध;
		हाल COLOR_DEPTH_999:
			output_bpc = 9;
			अवरोध;
		हाल COLOR_DEPTH_111111:
			output_bpc = 11;
			अवरोध;
		शेष:
			output_bpc = 8;
			अवरोध;
		पूर्ण

		चयन (res_ctx->pipe_ctx[i].stream->timing.pixel_encoding) अणु
		हाल PIXEL_ENCODING_RGB:
		हाल PIXEL_ENCODING_YCBCR444:
			pipes[pipe_cnt].करोut.output_क्रमmat = dm_444;
			pipes[pipe_cnt].करोut.output_bpp = output_bpc * 3;
			अवरोध;
		हाल PIXEL_ENCODING_YCBCR420:
			pipes[pipe_cnt].करोut.output_क्रमmat = dm_420;
			pipes[pipe_cnt].करोut.output_bpp = (output_bpc * 3.0) / 2;
			अवरोध;
		हाल PIXEL_ENCODING_YCBCR422:
			अगर (res_ctx->pipe_ctx[i].stream->timing.flags.DSC &&
			    !res_ctx->pipe_ctx[i].stream->timing.dsc_cfg.ycbcr422_simple)
				pipes[pipe_cnt].करोut.output_क्रमmat = dm_n422;
			अन्यथा
				pipes[pipe_cnt].करोut.output_क्रमmat = dm_s422;
			pipes[pipe_cnt].करोut.output_bpp = output_bpc * 2;
			अवरोध;
		शेष:
			pipes[pipe_cnt].करोut.output_क्रमmat = dm_444;
			pipes[pipe_cnt].करोut.output_bpp = output_bpc * 3;
		पूर्ण

		अगर (res_ctx->pipe_ctx[i].stream->timing.flags.DSC)
			pipes[pipe_cnt].करोut.output_bpp = res_ctx->pipe_ctx[i].stream->timing.dsc_cfg.bits_per_pixel / 16.0;

		/* toकरो: शेष max क्रम now, until there is logic reflecting this in dc*/
		pipes[pipe_cnt].करोut.dsc_input_bpc = 12;
		/*fill up the audio sample rate (unit in kHz)*/
		get_audio_check(&res_ctx->pipe_ctx[i].stream->audio_info, &aud_check);
		pipes[pipe_cnt].करोut.max_audio_sample_rate = aud_check.max_audiosample_rate / 1000;
		/*
		 * For graphic plane, cursor number is 1, nv12 is 0
		 * bw calculations due to cursor on/off
		 */
		अगर (res_ctx->pipe_ctx[i].plane_state &&
				res_ctx->pipe_ctx[i].plane_state->address.type == PLN_ADDR_TYPE_VIDEO_PROGRESSIVE)
			pipes[pipe_cnt].pipe.src.num_cursors = 0;
		अन्यथा
			pipes[pipe_cnt].pipe.src.num_cursors = dc->dml.ip.number_of_cursors;

		pipes[pipe_cnt].pipe.src.cur0_src_width = 256;
		pipes[pipe_cnt].pipe.src.cur0_bpp = dm_cur_32bit;

		अगर (!res_ctx->pipe_ctx[i].plane_state) अणु
			pipes[pipe_cnt].pipe.src.is_hsplit = pipes[pipe_cnt].pipe.dest.odm_combine != dm_odm_combine_mode_disabled;
			pipes[pipe_cnt].pipe.src.source_scan = dm_horz;
			pipes[pipe_cnt].pipe.src.sw_mode = dm_sw_4kb_s;
			pipes[pipe_cnt].pipe.src.macro_tile_size = dm_64k_tile;
			pipes[pipe_cnt].pipe.src.viewport_width = timing->h_addressable;
			अगर (pipes[pipe_cnt].pipe.src.viewport_width > 1920)
				pipes[pipe_cnt].pipe.src.viewport_width = 1920;
			pipes[pipe_cnt].pipe.src.viewport_height = timing->v_addressable;
			अगर (pipes[pipe_cnt].pipe.src.viewport_height > 1080)
				pipes[pipe_cnt].pipe.src.viewport_height = 1080;
			pipes[pipe_cnt].pipe.src.surface_height_y = pipes[pipe_cnt].pipe.src.viewport_height;
			pipes[pipe_cnt].pipe.src.surface_width_y = pipes[pipe_cnt].pipe.src.viewport_width;
			pipes[pipe_cnt].pipe.src.surface_height_c = pipes[pipe_cnt].pipe.src.viewport_height;
			pipes[pipe_cnt].pipe.src.surface_width_c = pipes[pipe_cnt].pipe.src.viewport_width;
			pipes[pipe_cnt].pipe.src.data_pitch = ((pipes[pipe_cnt].pipe.src.viewport_width + 255) / 256) * 256;
			pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_444_32;
			pipes[pipe_cnt].pipe.dest.recout_width = pipes[pipe_cnt].pipe.src.viewport_width; /*vp_width/hratio*/
			pipes[pipe_cnt].pipe.dest.recout_height = pipes[pipe_cnt].pipe.src.viewport_height; /*vp_height/vratio*/
			pipes[pipe_cnt].pipe.dest.full_recout_width = pipes[pipe_cnt].pipe.dest.recout_width;  /*when is_hsplit != 1*/
			pipes[pipe_cnt].pipe.dest.full_recout_height = pipes[pipe_cnt].pipe.dest.recout_height; /*when is_hsplit != 1*/
			pipes[pipe_cnt].pipe.scale_ratio_depth.lb_depth = dm_lb_16;
			pipes[pipe_cnt].pipe.scale_ratio_depth.hscl_ratio = 1.0;
			pipes[pipe_cnt].pipe.scale_ratio_depth.vscl_ratio = 1.0;
			pipes[pipe_cnt].pipe.scale_ratio_depth.scl_enable = 0; /*Lb only or Full scl*/
			pipes[pipe_cnt].pipe.scale_taps.htaps = 1;
			pipes[pipe_cnt].pipe.scale_taps.vtaps = 1;
			pipes[pipe_cnt].pipe.dest.vtotal_min = v_total;
			pipes[pipe_cnt].pipe.dest.vtotal_max = v_total;

			अगर (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_2to1) अणु
				pipes[pipe_cnt].pipe.src.viewport_width /= 2;
				pipes[pipe_cnt].pipe.dest.recout_width /= 2;
			पूर्ण अन्यथा अगर (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_4to1) अणु
				pipes[pipe_cnt].pipe.src.viewport_width /= 4;
				pipes[pipe_cnt].pipe.dest.recout_width /= 4;
			पूर्ण
		पूर्ण अन्यथा अणु
			काष्ठा dc_plane_state *pln = res_ctx->pipe_ctx[i].plane_state;
			काष्ठा scaler_data *scl = &res_ctx->pipe_ctx[i].plane_res.scl_data;

			pipes[pipe_cnt].pipe.src.immediate_flip = pln->flip_immediate;
			pipes[pipe_cnt].pipe.src.is_hsplit = (res_ctx->pipe_ctx[i].bottom_pipe && res_ctx->pipe_ctx[i].bottom_pipe->plane_state == pln)
					|| (res_ctx->pipe_ctx[i].top_pipe && res_ctx->pipe_ctx[i].top_pipe->plane_state == pln)
					|| pipes[pipe_cnt].pipe.dest.odm_combine != dm_odm_combine_mode_disabled;

			/* stereo is not split */
			अगर (pln->stereo_क्रमmat == PLANE_STEREO_FORMAT_SIDE_BY_SIDE ||
			    pln->stereo_क्रमmat == PLANE_STEREO_FORMAT_TOP_AND_BOTTOM) अणु
				pipes[pipe_cnt].pipe.src.is_hsplit = false;
				pipes[pipe_cnt].pipe.src.hsplit_grp = res_ctx->pipe_ctx[i].pipe_idx;
			पूर्ण

			pipes[pipe_cnt].pipe.src.source_scan = pln->rotation == ROTATION_ANGLE_90
					|| pln->rotation == ROTATION_ANGLE_270 ? dm_vert : dm_horz;
			pipes[pipe_cnt].pipe.src.viewport_y_y = scl->viewport_unadjusted.y;
			pipes[pipe_cnt].pipe.src.viewport_y_c = scl->viewport_c_unadjusted.y;
			pipes[pipe_cnt].pipe.src.viewport_width = scl->viewport_unadjusted.width;
			pipes[pipe_cnt].pipe.src.viewport_width_c = scl->viewport_c_unadjusted.width;
			pipes[pipe_cnt].pipe.src.viewport_height = scl->viewport_unadjusted.height;
			pipes[pipe_cnt].pipe.src.viewport_height_c = scl->viewport_c_unadjusted.height;
			pipes[pipe_cnt].pipe.src.surface_width_y = pln->plane_size.surface_size.width;
			pipes[pipe_cnt].pipe.src.surface_height_y = pln->plane_size.surface_size.height;
			pipes[pipe_cnt].pipe.src.surface_width_c = pln->plane_size.chroma_size.width;
			pipes[pipe_cnt].pipe.src.surface_height_c = pln->plane_size.chroma_size.height;
			अगर (pln->क्रमmat == SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA
					|| pln->क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) अणु
				pipes[pipe_cnt].pipe.src.data_pitch = pln->plane_size.surface_pitch;
				pipes[pipe_cnt].pipe.src.data_pitch_c = pln->plane_size.chroma_pitch;
				pipes[pipe_cnt].pipe.src.meta_pitch = pln->dcc.meta_pitch;
				pipes[pipe_cnt].pipe.src.meta_pitch_c = pln->dcc.meta_pitch_c;
			पूर्ण अन्यथा अणु
				pipes[pipe_cnt].pipe.src.data_pitch = pln->plane_size.surface_pitch;
				pipes[pipe_cnt].pipe.src.meta_pitch = pln->dcc.meta_pitch;
			पूर्ण
			pipes[pipe_cnt].pipe.src.dcc = pln->dcc.enable;
			pipes[pipe_cnt].pipe.dest.recout_width = scl->recout.width;
			pipes[pipe_cnt].pipe.dest.recout_height = scl->recout.height;
			pipes[pipe_cnt].pipe.dest.full_recout_height = scl->recout.height;
			pipes[pipe_cnt].pipe.dest.full_recout_width = scl->recout.width;
			अगर (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_2to1)
				pipes[pipe_cnt].pipe.dest.full_recout_width *= 2;
			अन्यथा अगर (pipes[pipe_cnt].pipe.dest.odm_combine == dm_odm_combine_mode_4to1)
				pipes[pipe_cnt].pipe.dest.full_recout_width *= 4;
			अन्यथा अणु
				काष्ठा pipe_ctx *split_pipe = res_ctx->pipe_ctx[i].bottom_pipe;

				जबतक (split_pipe && split_pipe->plane_state == pln) अणु
					pipes[pipe_cnt].pipe.dest.full_recout_width += split_pipe->plane_res.scl_data.recout.width;
					split_pipe = split_pipe->bottom_pipe;
				पूर्ण
				split_pipe = res_ctx->pipe_ctx[i].top_pipe;
				जबतक (split_pipe && split_pipe->plane_state == pln) अणु
					pipes[pipe_cnt].pipe.dest.full_recout_width += split_pipe->plane_res.scl_data.recout.width;
					split_pipe = split_pipe->top_pipe;
				पूर्ण
			पूर्ण

			pipes[pipe_cnt].pipe.scale_ratio_depth.lb_depth = dm_lb_16;
			pipes[pipe_cnt].pipe.scale_ratio_depth.hscl_ratio = (द्विगुन) scl->ratios.horz.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.hscl_ratio_c = (द्विगुन) scl->ratios.horz_c.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.vscl_ratio = (द्विगुन) scl->ratios.vert.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.vscl_ratio_c = (द्विगुन) scl->ratios.vert_c.value / (1ULL<<32);
			pipes[pipe_cnt].pipe.scale_ratio_depth.scl_enable =
					scl->ratios.vert.value != dc_fixpt_one.value
					|| scl->ratios.horz.value != dc_fixpt_one.value
					|| scl->ratios.vert_c.value != dc_fixpt_one.value
					|| scl->ratios.horz_c.value != dc_fixpt_one.value /*Lb only or Full scl*/
					|| dc->debug.always_scale; /*support always scale*/
			pipes[pipe_cnt].pipe.scale_taps.htaps = scl->taps.h_taps;
			pipes[pipe_cnt].pipe.scale_taps.htaps_c = scl->taps.h_taps_c;
			pipes[pipe_cnt].pipe.scale_taps.vtaps = scl->taps.v_taps;
			pipes[pipe_cnt].pipe.scale_taps.vtaps_c = scl->taps.v_taps_c;

			pipes[pipe_cnt].pipe.src.macro_tile_size =
					swizzle_mode_to_macro_tile_size(pln->tiling_info.gfx9.swizzle);
			swizzle_to_dml_params(pln->tiling_info.gfx9.swizzle,
					&pipes[pipe_cnt].pipe.src.sw_mode);

			चयन (pln->क्रमmat) अणु
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
				pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_420_8;
				अवरोध;
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
			हाल SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
				pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_420_10;
				अवरोध;
			हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
			हाल SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
				pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_444_64;
				अवरोध;
			हाल SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
			हाल SURFACE_PIXEL_FORMAT_GRPH_RGB565:
				pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_444_16;
				अवरोध;
			हाल SURFACE_PIXEL_FORMAT_GRPH_PALETA_256_COLORS:
				pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_444_8;
				अवरोध;
			हाल SURFACE_PIXEL_FORMAT_GRPH_RGBE_ALPHA:
				pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_rgbe_alpha;
				अवरोध;
			शेष:
				pipes[pipe_cnt].pipe.src.source_क्रमmat = dm_444_32;
				अवरोध;
			पूर्ण
		पूर्ण

		pipe_cnt++;
	पूर्ण

	/* populate ग_लिखोback inक्रमmation */
	dc->res_pool->funcs->populate_dml_ग_लिखोback_from_context(dc, res_ctx, pipes);

	वापस pipe_cnt;
पूर्ण

अचिन्हित पूर्णांक dcn20_calc_max_scaled_समय(
		अचिन्हित पूर्णांक समय_per_pixel,
		क्रमागत mmhubbub_wbअगर_mode mode,
		अचिन्हित पूर्णांक urgent_watermark)
अणु
	अचिन्हित पूर्णांक समय_per_byte = 0;
	अचिन्हित पूर्णांक total_y_मुक्त_entry = 0x200; /* two memory piece क्रम luma */
	अचिन्हित पूर्णांक total_c_मुक्त_entry = 0x140; /* two memory piece क्रम chroma */
	अचिन्हित पूर्णांक small_मुक्त_entry, max_मुक्त_entry;
	अचिन्हित पूर्णांक buf_lh_capability;
	अचिन्हित पूर्णांक max_scaled_समय;

	अगर (mode == PACKED_444) /* packed mode */
		समय_per_byte = समय_per_pixel/4;
	अन्यथा अगर (mode == PLANAR_420_8BPC)
		समय_per_byte  = समय_per_pixel;
	अन्यथा अगर (mode == PLANAR_420_10BPC) /* p010 */
		समय_per_byte  = समय_per_pixel * 819/1024;

	अगर (समय_per_byte == 0)
		समय_per_byte = 1;

	small_मुक्त_entry  = (total_y_मुक्त_entry > total_c_मुक्त_entry) ? total_c_मुक्त_entry : total_y_मुक्त_entry;
	max_मुक्त_entry    = (mode == PACKED_444) ? total_y_मुक्त_entry + total_c_मुक्त_entry : small_मुक्त_entry;
	buf_lh_capability = max_मुक्त_entry*समय_per_byte*32/16; /* there is 4bit fraction */
	max_scaled_समय   = buf_lh_capability - urgent_watermark;
	वापस max_scaled_समय;
पूर्ण

व्योम dcn20_set_mcअगर_arb_params(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt)
अणु
	क्रमागत mmhubbub_wbअगर_mode wbअगर_mode;
	काष्ठा mcअगर_arb_params *wb_arb_params;
	पूर्णांक i, j, k, dwb_pipe;

	/* Writeback MCIF_WB arbitration parameters */
	dwb_pipe = 0;
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु

		अगर (!context->res_ctx.pipe_ctx[i].stream)
			जारी;

		क्रम (j = 0; j < MAX_DWB_PIPES; j++) अणु
			अगर (context->res_ctx.pipe_ctx[i].stream->ग_लिखोback_info[j].wb_enabled == false)
				जारी;

			//wb_arb_params = &context->res_ctx.pipe_ctx[i].stream->ग_लिखोback_info[j].mcअगर_arb_params;
			wb_arb_params = &context->bw_ctx.bw.dcn.bw_ग_लिखोback.mcअगर_wb_arb[dwb_pipe];

			अगर (context->res_ctx.pipe_ctx[i].stream->ग_लिखोback_info[j].dwb_params.out_क्रमmat == dwb_scaler_mode_yuv420) अणु
				अगर (context->res_ctx.pipe_ctx[i].stream->ग_लिखोback_info[j].dwb_params.output_depth == DWB_OUTPUT_PIXEL_DEPTH_8BPC)
					wbअगर_mode = PLANAR_420_8BPC;
				अन्यथा
					wbअगर_mode = PLANAR_420_10BPC;
			पूर्ण अन्यथा
				wbअगर_mode = PACKED_444;

			क्रम (k = 0; k < माप(wb_arb_params->cli_watermark)/माप(wb_arb_params->cli_watermark[0]); k++) अणु
				wb_arb_params->cli_watermark[k] = get_wm_ग_लिखोback_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
				wb_arb_params->pstate_watermark[k] = get_wm_ग_लिखोback_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
			पूर्ण
			wb_arb_params->समय_per_pixel = 16.0 / context->res_ctx.pipe_ctx[i].stream->phy_pix_clk; /* 4 bit fraction, ms */
			wb_arb_params->slice_lines = 32;
			wb_arb_params->arbitration_slice = 2;
			wb_arb_params->max_scaled_समय = dcn20_calc_max_scaled_समय(wb_arb_params->समय_per_pixel,
				wbअगर_mode,
				wb_arb_params->cli_watermark[0]); /* assume 4 watermark sets have the same value */

			dwb_pipe++;

			अगर (dwb_pipe >= MAX_DWB_PIPES)
				वापस;
		पूर्ण
		अगर (dwb_pipe >= MAX_DWB_PIPES)
			वापस;
	पूर्ण
पूर्ण

bool dcn20_validate_dsc(काष्ठा dc *dc, काष्ठा dc_state *new_ctx)
अणु
	पूर्णांक i;

	/* Validate DSC config, dsc count validation is alपढ़ोy करोne */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe_ctx = &new_ctx->res_ctx.pipe_ctx[i];
		काष्ठा dc_stream_state *stream = pipe_ctx->stream;
		काष्ठा dsc_config dsc_cfg;
		काष्ठा pipe_ctx *odm_pipe;
		पूर्णांक opp_cnt = 1;

		क्रम (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
			opp_cnt++;

		/* Only need to validate top pipe */
		अगर (pipe_ctx->top_pipe || pipe_ctx->prev_odm_pipe || !stream || !stream->timing.flags.DSC)
			जारी;

		dsc_cfg.pic_width = (stream->timing.h_addressable + stream->timing.h_border_left
				+ stream->timing.h_border_right) / opp_cnt;
		dsc_cfg.pic_height = stream->timing.v_addressable + stream->timing.v_border_top
				+ stream->timing.v_border_bottom;
		dsc_cfg.pixel_encoding = stream->timing.pixel_encoding;
		dsc_cfg.color_depth = stream->timing.display_color_depth;
		dsc_cfg.is_odm = pipe_ctx->next_odm_pipe ? true : false;
		dsc_cfg.dc_dsc_cfg = stream->timing.dsc_cfg;
		dsc_cfg.dc_dsc_cfg.num_slices_h /= opp_cnt;

		अगर (!pipe_ctx->stream_res.dsc->funcs->dsc_validate_stream(pipe_ctx->stream_res.dsc, &dsc_cfg))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

काष्ठा pipe_ctx *dcn20_find_secondary_pipe(काष्ठा dc *dc,
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		स्थिर काष्ठा pipe_ctx *primary_pipe)
अणु
	काष्ठा pipe_ctx *secondary_pipe = शून्य;

	अगर (dc && primary_pipe) अणु
		पूर्णांक j;
		पूर्णांक preferred_pipe_idx = 0;

		/* first check the prev dc state:
		 * अगर this primary pipe has a bottom pipe in prev. state
		 * and अगर the bottom pipe is still available (which it should be),
		 * pick that pipe as secondary
		 * Same logic applies क्रम ODM pipes
		 */
		अगर (dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].bottom_pipe) अणु
			preferred_pipe_idx = dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].bottom_pipe->pipe_idx;
			अगर (res_ctx->pipe_ctx[preferred_pipe_idx].stream == शून्य) अणु
				secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
				secondary_pipe->pipe_idx = preferred_pipe_idx;
			पूर्ण
		पूर्ण
		अगर (secondary_pipe == शून्य &&
				dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].next_odm_pipe) अणु
			preferred_pipe_idx = dc->current_state->res_ctx.pipe_ctx[primary_pipe->pipe_idx].next_odm_pipe->pipe_idx;
			अगर (res_ctx->pipe_ctx[preferred_pipe_idx].stream == शून्य) अणु
				secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
				secondary_pipe->pipe_idx = preferred_pipe_idx;
			पूर्ण
		पूर्ण

		/*
		 * अगर this primary pipe करोes not have a bottom pipe in prev. state
		 * start backward and find a pipe that did not used to be a bottom pipe in
		 * prev. dc state. This way we make sure we keep the same assignment as
		 * last state and will not have to reprogram every pipe
		 */
		अगर (secondary_pipe == शून्य) अणु
			क्रम (j = dc->res_pool->pipe_count - 1; j >= 0; j--) अणु
				अगर (dc->current_state->res_ctx.pipe_ctx[j].top_pipe == शून्य
						&& dc->current_state->res_ctx.pipe_ctx[j].prev_odm_pipe == शून्य) अणु
					preferred_pipe_idx = j;

					अगर (res_ctx->pipe_ctx[preferred_pipe_idx].stream == शून्य) अणु
						secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
						secondary_pipe->pipe_idx = preferred_pipe_idx;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
		/*
		 * We should never hit this निश्चित unless assignments are shuffled around
		 * अगर this happens we will prob. hit a vsync tdr
		 */
		ASSERT(secondary_pipe);
		/*
		 * search backwards क्रम the second pipe to keep pipe
		 * assignment more consistent
		 */
		अगर (secondary_pipe == शून्य) अणु
			क्रम (j = dc->res_pool->pipe_count - 1; j >= 0; j--) अणु
				preferred_pipe_idx = j;

				अगर (res_ctx->pipe_ctx[preferred_pipe_idx].stream == शून्य) अणु
					secondary_pipe = &res_ctx->pipe_ctx[preferred_pipe_idx];
					secondary_pipe->pipe_idx = preferred_pipe_idx;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस secondary_pipe;
पूर्ण

व्योम dcn20_merge_pipes_क्रम_validate(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	/* merge previously split odm pipes since mode support needs to make the decision */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *odm_pipe = pipe->next_odm_pipe;

		अगर (pipe->prev_odm_pipe)
			जारी;

		pipe->next_odm_pipe = शून्य;
		जबतक (odm_pipe) अणु
			काष्ठा pipe_ctx *next_odm_pipe = odm_pipe->next_odm_pipe;

			odm_pipe->plane_state = शून्य;
			odm_pipe->stream = शून्य;
			odm_pipe->top_pipe = शून्य;
			odm_pipe->bottom_pipe = शून्य;
			odm_pipe->prev_odm_pipe = शून्य;
			odm_pipe->next_odm_pipe = शून्य;
			अगर (odm_pipe->stream_res.dsc)
				dcn20_release_dsc(&context->res_ctx, dc->res_pool, &odm_pipe->stream_res.dsc);
			/* Clear plane_res and stream_res */
			स_रखो(&odm_pipe->plane_res, 0, माप(odm_pipe->plane_res));
			स_रखो(&odm_pipe->stream_res, 0, माप(odm_pipe->stream_res));
			odm_pipe = next_odm_pipe;
		पूर्ण
		अगर (pipe->plane_state)
			resource_build_scaling_params(pipe);
	पूर्ण

	/* merge previously mpc split pipes since mode support needs to make the decision */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *hsplit_pipe = pipe->bottom_pipe;

		अगर (!hsplit_pipe || hsplit_pipe->plane_state != pipe->plane_state)
			जारी;

		pipe->bottom_pipe = hsplit_pipe->bottom_pipe;
		अगर (hsplit_pipe->bottom_pipe)
			hsplit_pipe->bottom_pipe->top_pipe = pipe;
		hsplit_pipe->plane_state = शून्य;
		hsplit_pipe->stream = शून्य;
		hsplit_pipe->top_pipe = शून्य;
		hsplit_pipe->bottom_pipe = शून्य;

		/* Clear plane_res and stream_res */
		स_रखो(&hsplit_pipe->plane_res, 0, माप(hsplit_pipe->plane_res));
		स_रखो(&hsplit_pipe->stream_res, 0, माप(hsplit_pipe->stream_res));
		अगर (pipe->plane_state)
			resource_build_scaling_params(pipe);
	पूर्ण
पूर्ण

पूर्णांक dcn20_validate_apply_pipe_split_flags(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		पूर्णांक vlevel,
		पूर्णांक *split,
		bool *merge)
अणु
	पूर्णांक i, pipe_idx, vlevel_split;
	पूर्णांक plane_count = 0;
	bool क्रमce_split = false;
	bool aव्योम_split = dc->debug.pipe_split_policy == MPC_SPLIT_AVOID;
	काष्ठा vba_vars_st *v = &context->bw_ctx.dml.vba;
	पूर्णांक max_mpc_comb = v->maxMpcComb;

	अगर (context->stream_count > 1) अणु
		अगर (dc->debug.pipe_split_policy == MPC_SPLIT_AVOID_MULT_DISP)
			aव्योम_split = true;
	पूर्ण अन्यथा अगर (dc->debug.क्रमce_single_disp_pipe_split)
			क्रमce_split = true;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		/**
		 * Workaround क्रम aव्योमing pipe-split in हालs where we'd split
		 * planes that are too small, resulting in splits that aren't
		 * valid क्रम the scaler.
		 */
		अगर (pipe->plane_state &&
		    (pipe->plane_state->dst_rect.width <= 16 ||
		     pipe->plane_state->dst_rect.height <= 16 ||
		     pipe->plane_state->src_rect.width <= 16 ||
		     pipe->plane_state->src_rect.height <= 16))
			aव्योम_split = true;

		/* TODO: fix dc bugs and हटाओ this split threshold thing */
		अगर (pipe->stream && !pipe->prev_odm_pipe &&
				(!pipe->top_pipe || pipe->top_pipe->plane_state != pipe->plane_state))
			++plane_count;
	पूर्ण
	अगर (plane_count > dc->res_pool->pipe_count / 2)
		aव्योम_split = true;

	/* W/A: Mode timing with borders may not work well with pipe split, aव्योम क्रम this corner हाल */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा dc_crtc_timing timing;

		अगर (!pipe->stream)
			जारी;
		अन्यथा अणु
			timing = pipe->stream->timing;
			अगर (timing.h_border_left + timing.h_border_right
					+ timing.v_border_top + timing.v_border_bottom > 0) अणु
				aव्योम_split = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Aव्योम split loop looks क्रम lowest voltage level that allows most unsplit pipes possible */
	अगर (aव्योम_split) अणु
		क्रम (i = 0, pipe_idx = 0; i < dc->res_pool->pipe_count; i++) अणु
			अगर (!context->res_ctx.pipe_ctx[i].stream)
				जारी;

			क्रम (vlevel_split = vlevel; vlevel <= context->bw_ctx.dml.soc.num_states; vlevel++)
				अगर (v->NoOfDPP[vlevel][0][pipe_idx] == 1 &&
						v->ModeSupport[vlevel][0])
					अवरोध;
			/* Impossible to not split this pipe */
			अगर (vlevel > context->bw_ctx.dml.soc.num_states)
				vlevel = vlevel_split;
			अन्यथा
				max_mpc_comb = 0;
			pipe_idx++;
		पूर्ण
		v->maxMpcComb = max_mpc_comb;
	पूर्ण

	/* Split loop sets which pipe should be split based on dml outमाला_दो and dc flags */
	क्रम (i = 0, pipe_idx = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		पूर्णांक pipe_plane = v->pipe_plane[pipe_idx];
		bool split4mpc = context->stream_count == 1 && plane_count == 1
				&& dc->config.enable_4to1MPC && dc->res_pool->pipe_count >= 4;

		अगर (!context->res_ctx.pipe_ctx[i].stream)
			जारी;

		अगर (split4mpc || v->NoOfDPP[vlevel][max_mpc_comb][pipe_plane] == 4)
			split[i] = 4;
		अन्यथा अगर (क्रमce_split || v->NoOfDPP[vlevel][max_mpc_comb][pipe_plane] == 2)
				split[i] = 2;

		अगर ((pipe->stream->view_क्रमmat ==
				VIEW_3D_FORMAT_SIDE_BY_SIDE ||
				pipe->stream->view_क्रमmat ==
				VIEW_3D_FORMAT_TOP_AND_BOTTOM) &&
				(pipe->stream->timing.timing_3d_क्रमmat ==
				TIMING_3D_FORMAT_TOP_AND_BOTTOM ||
				 pipe->stream->timing.timing_3d_क्रमmat ==
				TIMING_3D_FORMAT_SIDE_BY_SIDE))
			split[i] = 2;
		अगर (dc->debug.क्रमce_odm_combine & (1 << pipe->stream_res.tg->inst)) अणु
			split[i] = 2;
			v->ODMCombineEnablePerState[vlevel][pipe_plane] = dm_odm_combine_mode_2to1;
		पूर्ण
		अगर (dc->debug.क्रमce_odm_combine_4to1 & (1 << pipe->stream_res.tg->inst)) अणु
			split[i] = 4;
			v->ODMCombineEnablePerState[vlevel][pipe_plane] = dm_odm_combine_mode_4to1;
		पूर्ण
		/*420 क्रमmat workaround*/
		अगर (pipe->stream->timing.h_addressable > 7680 &&
				pipe->stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420) अणु
			split[i] = 4;
		पूर्ण
		v->ODMCombineEnabled[pipe_plane] =
			v->ODMCombineEnablePerState[vlevel][pipe_plane];

		अगर (v->ODMCombineEnabled[pipe_plane] == dm_odm_combine_mode_disabled) अणु
			अगर (get_num_mpc_splits(pipe) == 1) अणु
				/*If need split क्रम mpc but 2 way split alपढ़ोy*/
				अगर (split[i] == 4)
					split[i] = 2; /* 2 -> 4 MPC */
				अन्यथा अगर (split[i] == 2)
					split[i] = 0; /* 2 -> 2 MPC */
				अन्यथा अगर (pipe->top_pipe && pipe->top_pipe->plane_state == pipe->plane_state)
					merge[i] = true; /* 2 -> 1 MPC */
			पूर्ण अन्यथा अगर (get_num_mpc_splits(pipe) == 3) अणु
				/*If need split क्रम mpc but 4 way split alपढ़ोy*/
				अगर (split[i] == 2 && ((pipe->top_pipe && !pipe->top_pipe->top_pipe)
						|| !pipe->bottom_pipe)) अणु
					merge[i] = true; /* 4 -> 2 MPC */
				पूर्ण अन्यथा अगर (split[i] == 0 && pipe->top_pipe &&
						pipe->top_pipe->plane_state == pipe->plane_state)
					merge[i] = true; /* 4 -> 1 MPC */
				split[i] = 0;
			पूर्ण अन्यथा अगर (get_num_odm_splits(pipe)) अणु
				/* ODM -> MPC transition */
				ASSERT(0); /* NOT expected yet */
				अगर (pipe->prev_odm_pipe) अणु
					split[i] = 0;
					merge[i] = true;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (get_num_odm_splits(pipe) == 1) अणु
				/*If need split क्रम odm but 2 way split alपढ़ोy*/
				अगर (split[i] == 4)
					split[i] = 2; /* 2 -> 4 ODM */
				अन्यथा अगर (split[i] == 2)
					split[i] = 0; /* 2 -> 2 ODM */
				अन्यथा अगर (pipe->prev_odm_pipe) अणु
					ASSERT(0); /* NOT expected yet */
					merge[i] = true; /* निकास ODM */
				पूर्ण
			पूर्ण अन्यथा अगर (get_num_odm_splits(pipe) == 3) अणु
				/*If need split क्रम odm but 4 way split alपढ़ोy*/
				अगर (split[i] == 2 && ((pipe->prev_odm_pipe && !pipe->prev_odm_pipe->prev_odm_pipe)
						|| !pipe->next_odm_pipe)) अणु
					ASSERT(0); /* NOT expected yet */
					merge[i] = true; /* 4 -> 2 ODM */
				पूर्ण अन्यथा अगर (split[i] == 0 && pipe->prev_odm_pipe) अणु
					ASSERT(0); /* NOT expected yet */
					merge[i] = true; /* निकास ODM */
				पूर्ण
				split[i] = 0;
			पूर्ण अन्यथा अगर (get_num_mpc_splits(pipe)) अणु
				/* MPC -> ODM transition */
				ASSERT(0); /* NOT expected yet */
				अगर (pipe->top_pipe && pipe->top_pipe->plane_state == pipe->plane_state) अणु
					split[i] = 0;
					merge[i] = true;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Adjust dppclk when split is क्रमced, करो not bother with dispclk */
		अगर (split[i] != 0 && v->NoOfDPP[vlevel][max_mpc_comb][pipe_idx] == 1)
			v->RequiredDPPCLK[vlevel][max_mpc_comb][pipe_idx] /= 2;
		pipe_idx++;
	पूर्ण

	वापस vlevel;
पूर्ण

bool dcn20_fast_validate_bw(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक *pipe_cnt_out,
		पूर्णांक *pipe_split_from,
		पूर्णांक *vlevel_out,
		bool fast_validate)
अणु
	bool out = false;
	पूर्णांक split[MAX_PIPES] = अणु 0 पूर्ण;
	पूर्णांक pipe_cnt, i, pipe_idx, vlevel;

	ASSERT(pipes);
	अगर (!pipes)
		वापस false;

	dcn20_merge_pipes_क्रम_validate(dc, context);

	pipe_cnt = dc->res_pool->funcs->populate_dml_pipes(dc, context, pipes, fast_validate);

	*pipe_cnt_out = pipe_cnt;

	अगर (!pipe_cnt) अणु
		out = true;
		जाओ validate_out;
	पूर्ण

	vlevel = dml_get_voltage_level(&context->bw_ctx.dml, pipes, pipe_cnt);

	अगर (vlevel > context->bw_ctx.dml.soc.num_states)
		जाओ validate_fail;

	vlevel = dcn20_validate_apply_pipe_split_flags(dc, context, vlevel, split, शून्य);

	/*initialize pipe_just_split_from to invalid idx*/
	क्रम (i = 0; i < MAX_PIPES; i++)
		pipe_split_from[i] = -1;

	क्रम (i = 0, pipe_idx = -1; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *hsplit_pipe = pipe->bottom_pipe;

		अगर (!pipe->stream || pipe_split_from[i] >= 0)
			जारी;

		pipe_idx++;

		अगर (!pipe->top_pipe && !pipe->plane_state && context->bw_ctx.dml.vba.ODMCombineEnabled[pipe_idx]) अणु
			hsplit_pipe = dcn20_find_secondary_pipe(dc, &context->res_ctx, dc->res_pool, pipe);
			ASSERT(hsplit_pipe);
			अगर (!dcn20_split_stream_क्रम_odm(
					dc, &context->res_ctx,
					pipe, hsplit_pipe))
				जाओ validate_fail;
			pipe_split_from[hsplit_pipe->pipe_idx] = pipe_idx;
			dcn20_build_mapped_resource(dc, context, pipe->stream);
		पूर्ण

		अगर (!pipe->plane_state)
			जारी;
		/* Skip 2nd half of alपढ़ोy split pipe */
		अगर (pipe->top_pipe && pipe->plane_state == pipe->top_pipe->plane_state)
			जारी;

		/* We करो not support mpo + odm at the moment */
		अगर (hsplit_pipe && hsplit_pipe->plane_state != pipe->plane_state
				&& context->bw_ctx.dml.vba.ODMCombineEnabled[pipe_idx])
			जाओ validate_fail;

		अगर (split[i] == 2) अणु
			अगर (!hsplit_pipe || hsplit_pipe->plane_state != pipe->plane_state) अणु
				/* pipe not split previously needs split */
				hsplit_pipe = dcn20_find_secondary_pipe(dc, &context->res_ctx, dc->res_pool, pipe);
				ASSERT(hsplit_pipe);
				अगर (!hsplit_pipe) अणु
					context->bw_ctx.dml.vba.RequiredDPPCLK[vlevel][context->bw_ctx.dml.vba.maxMpcComb][pipe_idx] *= 2;
					जारी;
				पूर्ण
				अगर (context->bw_ctx.dml.vba.ODMCombineEnabled[pipe_idx]) अणु
					अगर (!dcn20_split_stream_क्रम_odm(
							dc, &context->res_ctx,
							pipe, hsplit_pipe))
						जाओ validate_fail;
					dcn20_build_mapped_resource(dc, context, pipe->stream);
				पूर्ण अन्यथा अणु
					dcn20_split_stream_क्रम_mpc(
							&context->res_ctx, dc->res_pool,
							pipe, hsplit_pipe);
					resource_build_scaling_params(pipe);
					resource_build_scaling_params(hsplit_pipe);
				पूर्ण
				pipe_split_from[hsplit_pipe->pipe_idx] = pipe_idx;
			पूर्ण
		पूर्ण अन्यथा अगर (hsplit_pipe && hsplit_pipe->plane_state == pipe->plane_state) अणु
			/* merge should alपढ़ोy have been करोne */
			ASSERT(0);
		पूर्ण
	पूर्ण
	/* Actual dsc count per stream dsc validation*/
	अगर (!dcn20_validate_dsc(dc, context)) अणु
		context->bw_ctx.dml.vba.ValidationStatus[context->bw_ctx.dml.vba.soc.num_states] =
				DML_FAIL_DSC_VALIDATION_FAILURE;
		जाओ validate_fail;
	पूर्ण

	*vlevel_out = vlevel;

	out = true;
	जाओ validate_out;

validate_fail:
	out = false;

validate_out:
	वापस out;
पूर्ण

अटल व्योम dcn20_calculate_wm(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक *out_pipe_cnt,
		पूर्णांक *pipe_split_from,
		पूर्णांक vlevel,
		bool fast_validate)
अणु
	पूर्णांक pipe_cnt, i, pipe_idx;

	क्रम (i = 0, pipe_idx = 0, pipe_cnt = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (!context->res_ctx.pipe_ctx[i].stream)
			जारी;

		pipes[pipe_cnt].clks_cfg.refclk_mhz = dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000.0;
		pipes[pipe_cnt].clks_cfg.dispclk_mhz = context->bw_ctx.dml.vba.RequiredDISPCLK[vlevel][context->bw_ctx.dml.vba.maxMpcComb];

		अगर (pipe_split_from[i] < 0) अणु
			pipes[pipe_cnt].clks_cfg.dppclk_mhz =
					context->bw_ctx.dml.vba.RequiredDPPCLK[vlevel][context->bw_ctx.dml.vba.maxMpcComb][pipe_idx];
			अगर (context->bw_ctx.dml.vba.BlendingAndTiming[pipe_idx] == pipe_idx)
				pipes[pipe_cnt].pipe.dest.odm_combine =
						context->bw_ctx.dml.vba.ODMCombineEnabled[pipe_idx];
			अन्यथा
				pipes[pipe_cnt].pipe.dest.odm_combine = 0;
			pipe_idx++;
		पूर्ण अन्यथा अणु
			pipes[pipe_cnt].clks_cfg.dppclk_mhz =
					context->bw_ctx.dml.vba.RequiredDPPCLK[vlevel][context->bw_ctx.dml.vba.maxMpcComb][pipe_split_from[i]];
			अगर (context->bw_ctx.dml.vba.BlendingAndTiming[pipe_split_from[i]] == pipe_split_from[i])
				pipes[pipe_cnt].pipe.dest.odm_combine =
						context->bw_ctx.dml.vba.ODMCombineEnabled[pipe_split_from[i]];
			अन्यथा
				pipes[pipe_cnt].pipe.dest.odm_combine = 0;
		पूर्ण

		अगर (dc->config.क्रमced_घड़ीs) अणु
			pipes[pipe_cnt].clks_cfg.dispclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[0].dispclk_mhz;
			pipes[pipe_cnt].clks_cfg.dppclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[0].dppclk_mhz;
		पूर्ण
		अगर (dc->debug.min_disp_clk_khz > pipes[pipe_cnt].clks_cfg.dispclk_mhz * 1000)
			pipes[pipe_cnt].clks_cfg.dispclk_mhz = dc->debug.min_disp_clk_khz / 1000.0;
		अगर (dc->debug.min_dpp_clk_khz > pipes[pipe_cnt].clks_cfg.dppclk_mhz * 1000)
			pipes[pipe_cnt].clks_cfg.dppclk_mhz = dc->debug.min_dpp_clk_khz / 1000.0;

		pipe_cnt++;
	पूर्ण

	अगर (pipe_cnt != pipe_idx) अणु
		अगर (dc->res_pool->funcs->populate_dml_pipes)
			pipe_cnt = dc->res_pool->funcs->populate_dml_pipes(dc,
				context, pipes, fast_validate);
		अन्यथा
			pipe_cnt = dcn20_populate_dml_pipes_from_context(dc,
				context, pipes, fast_validate);
	पूर्ण

	*out_pipe_cnt = pipe_cnt;

	pipes[0].clks_cfg.voltage = vlevel;
	pipes[0].clks_cfg.dcfclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[vlevel].dcfclk_mhz;
	pipes[0].clks_cfg.socclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[vlevel].socclk_mhz;

	/* only pipe 0 is पढ़ो क्रम voltage and dcf/soc घड़ीs */
	अगर (vlevel < 1) अणु
		pipes[0].clks_cfg.voltage = 1;
		pipes[0].clks_cfg.dcfclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[1].dcfclk_mhz;
		pipes[0].clks_cfg.socclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[1].socclk_mhz;
	पूर्ण
	context->bw_ctx.bw.dcn.watermarks.b.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.urgent_latency_ns = get_urgent_latency(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;

	अगर (vlevel < 2) अणु
		pipes[0].clks_cfg.voltage = 2;
		pipes[0].clks_cfg.dcfclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[2].dcfclk_mhz;
		pipes[0].clks_cfg.socclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[2].socclk_mhz;
	पूर्ण
	context->bw_ctx.bw.dcn.watermarks.c.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;

	अगर (vlevel < 3) अणु
		pipes[0].clks_cfg.voltage = 3;
		pipes[0].clks_cfg.dcfclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[2].dcfclk_mhz;
		pipes[0].clks_cfg.socclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[2].socclk_mhz;
	पूर्ण
	context->bw_ctx.bw.dcn.watermarks.d.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;

	pipes[0].clks_cfg.voltage = vlevel;
	pipes[0].clks_cfg.dcfclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[vlevel].dcfclk_mhz;
	pipes[0].clks_cfg.socclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[vlevel].socclk_mhz;
	context->bw_ctx.bw.dcn.watermarks.a.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.a.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
पूर्ण

व्योम dcn20_calculate_dlg_params(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt,
		पूर्णांक vlevel)
अणु
	पूर्णांक i, pipe_idx;

	/* Writeback MCIF_WB arbitration parameters */
	dc->res_pool->funcs->set_mcअगर_arb_params(dc, context, pipes, pipe_cnt);

	context->bw_ctx.bw.dcn.clk.dispclk_khz = context->bw_ctx.dml.vba.DISPCLK * 1000;
	context->bw_ctx.bw.dcn.clk.dcfclk_khz = context->bw_ctx.dml.vba.DCFCLK * 1000;
	context->bw_ctx.bw.dcn.clk.socclk_khz = context->bw_ctx.dml.vba.SOCCLK * 1000;
	context->bw_ctx.bw.dcn.clk.dramclk_khz = context->bw_ctx.dml.vba.DRAMSpeed * 1000 / 16;
	context->bw_ctx.bw.dcn.clk.dcfclk_deep_sleep_khz = context->bw_ctx.dml.vba.DCFCLKDeepSleep * 1000;
	context->bw_ctx.bw.dcn.clk.fclk_khz = context->bw_ctx.dml.vba.FabricClock * 1000;
	context->bw_ctx.bw.dcn.clk.p_state_change_support =
		context->bw_ctx.dml.vba.DRAMClockChangeSupport[vlevel][context->bw_ctx.dml.vba.maxMpcComb]
							!= dm_dram_घड़ी_change_unsupported;
	context->bw_ctx.bw.dcn.clk.dppclk_khz = 0;

	अगर (context->bw_ctx.bw.dcn.clk.dispclk_khz < dc->debug.min_disp_clk_khz)
		context->bw_ctx.bw.dcn.clk.dispclk_khz = dc->debug.min_disp_clk_khz;

	क्रम (i = 0, pipe_idx = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (!context->res_ctx.pipe_ctx[i].stream)
			जारी;
		pipes[pipe_idx].pipe.dest.vstartup_start = get_vstartup(&context->bw_ctx.dml, pipes, pipe_cnt, pipe_idx);
		pipes[pipe_idx].pipe.dest.vupdate_offset = get_vupdate_offset(&context->bw_ctx.dml, pipes, pipe_cnt, pipe_idx);
		pipes[pipe_idx].pipe.dest.vupdate_width = get_vupdate_width(&context->bw_ctx.dml, pipes, pipe_cnt, pipe_idx);
		pipes[pipe_idx].pipe.dest.vपढ़ोy_offset = get_vपढ़ोy_offset(&context->bw_ctx.dml, pipes, pipe_cnt, pipe_idx);
		अगर (context->bw_ctx.bw.dcn.clk.dppclk_khz < pipes[pipe_idx].clks_cfg.dppclk_mhz * 1000)
			context->bw_ctx.bw.dcn.clk.dppclk_khz = pipes[pipe_idx].clks_cfg.dppclk_mhz * 1000;
		context->res_ctx.pipe_ctx[i].plane_res.bw.dppclk_khz =
						pipes[pipe_idx].clks_cfg.dppclk_mhz * 1000;
		context->res_ctx.pipe_ctx[i].pipe_dlg_param = pipes[pipe_idx].pipe.dest;
		pipe_idx++;
	पूर्ण
	/*save a original dppघड़ी copy*/
	context->bw_ctx.bw.dcn.clk.bw_dppclk_khz = context->bw_ctx.bw.dcn.clk.dppclk_khz;
	context->bw_ctx.bw.dcn.clk.bw_dispclk_khz = context->bw_ctx.bw.dcn.clk.dispclk_khz;
	context->bw_ctx.bw.dcn.clk.max_supported_dppclk_khz = context->bw_ctx.dml.soc.घड़ी_limits[vlevel].dppclk_mhz * 1000;
	context->bw_ctx.bw.dcn.clk.max_supported_dispclk_khz = context->bw_ctx.dml.soc.घड़ी_limits[vlevel].dispclk_mhz * 1000;

	क्रम (i = 0, pipe_idx = 0; i < dc->res_pool->pipe_count; i++) अणु
		bool cstate_en = context->bw_ctx.dml.vba.PrefetchMode[vlevel][context->bw_ctx.dml.vba.maxMpcComb] != 2;

		अगर (!context->res_ctx.pipe_ctx[i].stream)
			जारी;

		context->bw_ctx.dml.funcs.rq_dlg_get_dlg_reg(&context->bw_ctx.dml,
				&context->res_ctx.pipe_ctx[i].dlg_regs,
				&context->res_ctx.pipe_ctx[i].ttu_regs,
				pipes,
				pipe_cnt,
				pipe_idx,
				cstate_en,
				context->bw_ctx.bw.dcn.clk.p_state_change_support,
				false, false, true);

		context->bw_ctx.dml.funcs.rq_dlg_get_rq_reg(&context->bw_ctx.dml,
				&context->res_ctx.pipe_ctx[i].rq_regs,
				pipes[pipe_idx].pipe);
		pipe_idx++;
	पूर्ण
पूर्ण

अटल bool dcn20_validate_bandwidth_पूर्णांकernal(काष्ठा dc *dc, काष्ठा dc_state *context,
		bool fast_validate)
अणु
	bool out = false;

	BW_VAL_TRACE_SETUP();

	पूर्णांक vlevel = 0;
	पूर्णांक pipe_split_from[MAX_PIPES];
	पूर्णांक pipe_cnt = 0;
	display_e2e_pipe_params_st *pipes = kzalloc(dc->res_pool->pipe_count * माप(display_e2e_pipe_params_st), GFP_ATOMIC);
	DC_LOGGER_INIT(dc->ctx->logger);

	BW_VAL_TRACE_COUNT();

	out = dcn20_fast_validate_bw(dc, context, pipes, &pipe_cnt, pipe_split_from, &vlevel, fast_validate);

	अगर (pipe_cnt == 0)
		जाओ validate_out;

	अगर (!out)
		जाओ validate_fail;

	BW_VAL_TRACE_END_VOLTAGE_LEVEL();

	अगर (fast_validate) अणु
		BW_VAL_TRACE_SKIP(fast);
		जाओ validate_out;
	पूर्ण

	dcn20_calculate_wm(dc, context, pipes, &pipe_cnt, pipe_split_from, vlevel, fast_validate);
	dcn20_calculate_dlg_params(dc, context, pipes, pipe_cnt, vlevel);

	BW_VAL_TRACE_END_WATERMARKS();

	जाओ validate_out;

validate_fail:
	DC_LOG_WARNING("Mode Validation Warning: %s failed validation.\n",
		dml_get_status_message(context->bw_ctx.dml.vba.ValidationStatus[context->bw_ctx.dml.vba.soc.num_states]));

	BW_VAL_TRACE_SKIP(fail);
	out = false;

validate_out:
	kमुक्त(pipes);

	BW_VAL_TRACE_FINISH();

	वापस out;
पूर्ण

/*
 * This must be noअंतरभूत to ensure anything that deals with FP रेजिस्टरs
 * is contained within this call; previously our compiling with hard-भग्न
 * would result in fp inकाष्ठाions being emitted outside of the boundaries
 * of the DC_FP_START/END macros, which makes sense as the compiler has no
 * idea about what is wrapped and what is not
 *
 * This is largely just a workaround to aव्योम अवरोधage पूर्णांकroduced with 5.6,
 * ideally all fp-using code should be moved पूर्णांकo its own file, only that
 * should be compiled with hard-भग्न, and all code exported from there
 * should be strictly wrapped with DC_FP_START/END
 */
अटल noअंतरभूत bool dcn20_validate_bandwidth_fp(काष्ठा dc *dc,
		काष्ठा dc_state *context, bool fast_validate)
अणु
	bool voltage_supported = false;
	bool full_pstate_supported = false;
	bool dummy_pstate_supported = false;
	द्विगुन p_state_latency_us;

	p_state_latency_us = context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us;
	context->bw_ctx.dml.soc.disable_dram_घड़ी_change_vactive_support =
		dc->debug.disable_dram_घड़ी_change_vactive_support;
	context->bw_ctx.dml.soc.allow_dram_घड़ी_one_display_vactive =
		dc->debug.enable_dram_घड़ी_change_one_display_vactive;

	/*Unsafe due to current pipe merge and split logic*/
	ASSERT(context != dc->current_state);

	अगर (fast_validate) अणु
		वापस dcn20_validate_bandwidth_पूर्णांकernal(dc, context, true);
	पूर्ण

	// Best हाल, we support full UCLK चयन latency
	voltage_supported = dcn20_validate_bandwidth_पूर्णांकernal(dc, context, false);
	full_pstate_supported = context->bw_ctx.bw.dcn.clk.p_state_change_support;

	अगर (context->bw_ctx.dml.soc.dummy_pstate_latency_us == 0 ||
		(voltage_supported && full_pstate_supported)) अणु
		context->bw_ctx.bw.dcn.clk.p_state_change_support = full_pstate_supported;
		जाओ restore_dml_state;
	पूर्ण

	// Fallback: Try to only support G6 temperature पढ़ो latency
	context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us = context->bw_ctx.dml.soc.dummy_pstate_latency_us;

	voltage_supported = dcn20_validate_bandwidth_पूर्णांकernal(dc, context, false);
	dummy_pstate_supported = context->bw_ctx.bw.dcn.clk.p_state_change_support;

	अगर (voltage_supported && (dummy_pstate_supported || !(context->stream_count))) अणु
		context->bw_ctx.bw.dcn.clk.p_state_change_support = false;
		जाओ restore_dml_state;
	पूर्ण

	// ERROR: fallback is supposed to always work.
	ASSERT(false);

restore_dml_state:
	context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us = p_state_latency_us;
	वापस voltage_supported;
पूर्ण

bool dcn20_validate_bandwidth(काष्ठा dc *dc, काष्ठा dc_state *context,
		bool fast_validate)
अणु
	bool voltage_supported;
	DC_FP_START();
	voltage_supported = dcn20_validate_bandwidth_fp(dc, context, fast_validate);
	DC_FP_END();
	वापस voltage_supported;
पूर्ण

काष्ठा pipe_ctx *dcn20_acquire_idle_pipe_क्रम_layer(
		काष्ठा dc_state *state,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा resource_context *res_ctx = &state->res_ctx;
	काष्ठा pipe_ctx *head_pipe = resource_get_head_pipe_क्रम_stream(res_ctx, stream);
	काष्ठा pipe_ctx *idle_pipe = find_idle_secondary_pipe(res_ctx, pool, head_pipe);

	अगर (!head_pipe)
		ASSERT(0);

	अगर (!idle_pipe)
		वापस शून्य;

	idle_pipe->stream = head_pipe->stream;
	idle_pipe->stream_res.tg = head_pipe->stream_res.tg;
	idle_pipe->stream_res.opp = head_pipe->stream_res.opp;

	idle_pipe->plane_res.hubp = pool->hubps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.ipp = pool->ipps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.dpp = pool->dpps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.mpcc_inst = pool->dpps[idle_pipe->pipe_idx]->inst;

	वापस idle_pipe;
पूर्ण

bool dcn20_get_dcc_compression_cap(स्थिर काष्ठा dc *dc,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output)
अणु
	वापस dc->res_pool->hubbub->funcs->get_dcc_compression_cap(
			dc->res_pool->hubbub,
			input,
			output);
पूर्ण

अटल व्योम dcn20_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dcn20_resource_pool *dcn20_pool = TO_DCN20_RES_POOL(*pool);

	dcn20_resource_deकाष्ठा(dcn20_pool);
	kमुक्त(dcn20_pool);
	*pool = शून्य;
पूर्ण


अटल काष्ठा dc_cap_funcs cap_funcs = अणु
	.get_dcc_compression_cap = dcn20_get_dcc_compression_cap
पूर्ण;


क्रमागत dc_status dcn20_patch_unknown_plane_state(काष्ठा dc_plane_state *plane_state)
अणु
	क्रमागत surface_pixel_क्रमmat surf_pix_क्रमmat = plane_state->क्रमmat;
	अचिन्हित पूर्णांक bpp = resource_pixel_क्रमmat_to_bpp(surf_pix_क्रमmat);

	क्रमागत swizzle_mode_values swizzle = DC_SW_LINEAR;

	अगर (bpp == 64)
		swizzle = DC_SW_64KB_D;
	अन्यथा
		swizzle = DC_SW_64KB_S;

	plane_state->tiling_info.gfx9.swizzle = swizzle;
	वापस DC_OK;
पूर्ण

अटल स्थिर काष्ठा resource_funcs dcn20_res_pool_funcs = अणु
	.destroy = dcn20_destroy_resource_pool,
	.link_enc_create = dcn20_link_encoder_create,
	.panel_cntl_create = dcn20_panel_cntl_create,
	.validate_bandwidth = dcn20_validate_bandwidth,
	.acquire_idle_pipe_क्रम_layer = dcn20_acquire_idle_pipe_क्रम_layer,
	.add_stream_to_ctx = dcn20_add_stream_to_ctx,
	.add_dsc_to_stream_resource = dcn20_add_dsc_to_stream_resource,
	.हटाओ_stream_from_ctx = dcn20_हटाओ_stream_from_ctx,
	.populate_dml_ग_लिखोback_from_context = dcn20_populate_dml_ग_लिखोback_from_context,
	.patch_unknown_plane_state = dcn20_patch_unknown_plane_state,
	.set_mcअगर_arb_params = dcn20_set_mcअगर_arb_params,
	.populate_dml_pipes = dcn20_populate_dml_pipes_from_context,
	.find_first_मुक्त_match_stream_enc_क्रम_link = dcn10_find_first_मुक्त_match_stream_enc_क्रम_link
पूर्ण;

bool dcn20_dwbc_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	uपूर्णांक32_t pipe_count = pool->res_cap->num_dwb;

	क्रम (i = 0; i < pipe_count; i++) अणु
		काष्ठा dcn20_dwbc *dwbc20 = kzalloc(माप(काष्ठा dcn20_dwbc),
						    GFP_KERNEL);

		अगर (!dwbc20) अणु
			dm_error("DC: failed to create dwbc20!\n");
			वापस false;
		पूर्ण
		dcn20_dwbc_स्थिरruct(dwbc20, ctx,
				&dwbc20_regs[i],
				&dwbc20_shअगरt,
				&dwbc20_mask,
				i);
		pool->dwbc[i] = &dwbc20->base;
	पूर्ण
	वापस true;
पूर्ण

bool dcn20_mmhubbub_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	uपूर्णांक32_t pipe_count = pool->res_cap->num_dwb;

	ASSERT(pipe_count > 0);

	क्रम (i = 0; i < pipe_count; i++) अणु
		काष्ठा dcn20_mmhubbub *mcअगर_wb20 = kzalloc(माप(काष्ठा dcn20_mmhubbub),
						    GFP_KERNEL);

		अगर (!mcअगर_wb20) अणु
			dm_error("DC: failed to create mcif_wb20!\n");
			वापस false;
		पूर्ण

		dcn20_mmhubbub_स्थिरruct(mcअगर_wb20, ctx,
				&mcअगर_wb20_regs[i],
				&mcअगर_wb20_shअगरt,
				&mcअगर_wb20_mask,
				i);

		pool->mcअगर_wb[i] = &mcअगर_wb20->base;
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा pp_smu_funcs *dcn20_pp_smu_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा pp_smu_funcs *pp_smu = kzalloc(माप(*pp_smu), GFP_ATOMIC);

	अगर (!pp_smu)
		वापस pp_smu;

	dm_pp_get_funcs(ctx, pp_smu);

	अगर (pp_smu->ctx.ver != PP_SMU_VER_NV)
		pp_smu = स_रखो(pp_smu, 0, माप(काष्ठा pp_smu_funcs));

	वापस pp_smu;
पूर्ण

अटल व्योम dcn20_pp_smu_destroy(काष्ठा pp_smu_funcs **pp_smu)
अणु
	अगर (pp_smu && *pp_smu) अणु
		kमुक्त(*pp_smu);
		*pp_smu = शून्य;
	पूर्ण
पूर्ण

व्योम dcn20_cap_soc_घड़ीs(
		काष्ठा _vcs_dpi_soc_bounding_box_st *bb,
		काष्ठा pp_smu_nv_घड़ी_प्रकारable max_घड़ीs)
अणु
	पूर्णांक i;

	// First pass - cap all घड़ीs higher than the reported max
	क्रम (i = 0; i < bb->num_states; i++) अणु
		अगर ((bb->घड़ी_limits[i].dcfclk_mhz > (max_घड़ीs.dcfClockInKhz / 1000))
				&& max_घड़ीs.dcfClockInKhz != 0)
			bb->घड़ी_limits[i].dcfclk_mhz = (max_घड़ीs.dcfClockInKhz / 1000);

		अगर ((bb->घड़ी_limits[i].dram_speed_mts > (max_घड़ीs.uClockInKhz / 1000) * 16)
						&& max_घड़ीs.uClockInKhz != 0)
			bb->घड़ी_limits[i].dram_speed_mts = (max_घड़ीs.uClockInKhz / 1000) * 16;

		अगर ((bb->घड़ी_limits[i].fabricclk_mhz > (max_घड़ीs.fabricClockInKhz / 1000))
						&& max_घड़ीs.fabricClockInKhz != 0)
			bb->घड़ी_limits[i].fabricclk_mhz = (max_घड़ीs.fabricClockInKhz / 1000);

		अगर ((bb->घड़ी_limits[i].dispclk_mhz > (max_घड़ीs.displayClockInKhz / 1000))
						&& max_घड़ीs.displayClockInKhz != 0)
			bb->घड़ी_limits[i].dispclk_mhz = (max_घड़ीs.displayClockInKhz / 1000);

		अगर ((bb->घड़ी_limits[i].dppclk_mhz > (max_घड़ीs.dppClockInKhz / 1000))
						&& max_घड़ीs.dppClockInKhz != 0)
			bb->घड़ी_limits[i].dppclk_mhz = (max_घड़ीs.dppClockInKhz / 1000);

		अगर ((bb->घड़ी_limits[i].phyclk_mhz > (max_घड़ीs.phyClockInKhz / 1000))
						&& max_घड़ीs.phyClockInKhz != 0)
			bb->घड़ी_limits[i].phyclk_mhz = (max_घड़ीs.phyClockInKhz / 1000);

		अगर ((bb->घड़ी_limits[i].socclk_mhz > (max_घड़ीs.socClockInKhz / 1000))
						&& max_घड़ीs.socClockInKhz != 0)
			bb->घड़ी_limits[i].socclk_mhz = (max_घड़ीs.socClockInKhz / 1000);

		अगर ((bb->घड़ी_limits[i].dscclk_mhz > (max_घड़ीs.dscClockInKhz / 1000))
						&& max_घड़ीs.dscClockInKhz != 0)
			bb->घड़ी_limits[i].dscclk_mhz = (max_घड़ीs.dscClockInKhz / 1000);
	पूर्ण

	// Second pass - हटाओ all duplicate घड़ी states
	क्रम (i = bb->num_states - 1; i > 1; i--) अणु
		bool duplicate = true;

		अगर (bb->घड़ी_limits[i-1].dcfclk_mhz != bb->घड़ी_limits[i].dcfclk_mhz)
			duplicate = false;
		अगर (bb->घड़ी_limits[i-1].dispclk_mhz != bb->घड़ी_limits[i].dispclk_mhz)
			duplicate = false;
		अगर (bb->घड़ी_limits[i-1].dppclk_mhz != bb->घड़ी_limits[i].dppclk_mhz)
			duplicate = false;
		अगर (bb->घड़ी_limits[i-1].dram_speed_mts != bb->घड़ी_limits[i].dram_speed_mts)
			duplicate = false;
		अगर (bb->घड़ी_limits[i-1].dscclk_mhz != bb->घड़ी_limits[i].dscclk_mhz)
			duplicate = false;
		अगर (bb->घड़ी_limits[i-1].fabricclk_mhz != bb->घड़ी_limits[i].fabricclk_mhz)
			duplicate = false;
		अगर (bb->घड़ी_limits[i-1].phyclk_mhz != bb->घड़ी_limits[i].phyclk_mhz)
			duplicate = false;
		अगर (bb->घड़ी_limits[i-1].socclk_mhz != bb->घड़ी_limits[i].socclk_mhz)
			duplicate = false;

		अगर (duplicate)
			bb->num_states--;
	पूर्ण
पूर्ण

व्योम dcn20_update_bounding_box(काष्ठा dc *dc, काष्ठा _vcs_dpi_soc_bounding_box_st *bb,
		काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs, अचिन्हित पूर्णांक *uclk_states, अचिन्हित पूर्णांक num_states)
अणु
	काष्ठा _vcs_dpi_voltage_scaling_st calculated_states[DC__VOLTAGE_STATES];
	पूर्णांक i;
	पूर्णांक num_calculated_states = 0;
	पूर्णांक min_dcfclk = 0;

	अगर (num_states == 0)
		वापस;

	स_रखो(calculated_states, 0, माप(calculated_states));

	अगर (dc->bb_overrides.min_dcfclk_mhz > 0)
		min_dcfclk = dc->bb_overrides.min_dcfclk_mhz;
	अन्यथा अणु
		अगर (ASICREV_IS_NAVI12_P(dc->ctx->asic_id.hw_पूर्णांकernal_rev))
			min_dcfclk = 310;
		अन्यथा
			// Accounting क्रम SOC/DCF relationship, we can go as high as
			// 506Mhz in Vmin.
			min_dcfclk = 506;
	पूर्ण

	क्रम (i = 0; i < num_states; i++) अणु
		पूर्णांक min_fclk_required_by_uclk;
		calculated_states[i].state = i;
		calculated_states[i].dram_speed_mts = uclk_states[i] * 16 / 1000;

		// FCLK:UCLK ratio is 1.08
		min_fclk_required_by_uclk = भाग_u64(((अचिन्हित दीर्घ दीर्घ)uclk_states[i]) * 1080,
			1000000);

		calculated_states[i].fabricclk_mhz = (min_fclk_required_by_uclk < min_dcfclk) ?
				min_dcfclk : min_fclk_required_by_uclk;

		calculated_states[i].socclk_mhz = (calculated_states[i].fabricclk_mhz > max_घड़ीs->socClockInKhz / 1000) ?
				max_घड़ीs->socClockInKhz / 1000 : calculated_states[i].fabricclk_mhz;

		calculated_states[i].dcfclk_mhz = (calculated_states[i].fabricclk_mhz > max_घड़ीs->dcfClockInKhz / 1000) ?
				max_घड़ीs->dcfClockInKhz / 1000 : calculated_states[i].fabricclk_mhz;

		calculated_states[i].dispclk_mhz = max_घड़ीs->displayClockInKhz / 1000;
		calculated_states[i].dppclk_mhz = max_घड़ीs->displayClockInKhz / 1000;
		calculated_states[i].dscclk_mhz = max_घड़ीs->displayClockInKhz / (1000 * 3);

		calculated_states[i].phyclk_mhz = max_घड़ीs->phyClockInKhz / 1000;

		num_calculated_states++;
	पूर्ण

	calculated_states[num_calculated_states - 1].socclk_mhz = max_घड़ीs->socClockInKhz / 1000;
	calculated_states[num_calculated_states - 1].fabricclk_mhz = max_घड़ीs->socClockInKhz / 1000;
	calculated_states[num_calculated_states - 1].dcfclk_mhz = max_घड़ीs->dcfClockInKhz / 1000;

	स_नकल(bb->घड़ी_limits, calculated_states, माप(bb->घड़ी_limits));
	bb->num_states = num_calculated_states;

	// Duplicate the last state, DML always an extra state identical to max state to work
	स_नकल(&bb->घड़ी_limits[num_calculated_states], &bb->घड़ी_limits[num_calculated_states - 1], माप(काष्ठा _vcs_dpi_voltage_scaling_st));
	bb->घड़ी_limits[num_calculated_states].state = bb->num_states;
पूर्ण

व्योम dcn20_patch_bounding_box(काष्ठा dc *dc, काष्ठा _vcs_dpi_soc_bounding_box_st *bb)
अणु
	अगर ((पूर्णांक)(bb->sr_निकास_समय_us * 1000) != dc->bb_overrides.sr_निकास_समय_ns
			&& dc->bb_overrides.sr_निकास_समय_ns) अणु
		bb->sr_निकास_समय_us = dc->bb_overrides.sr_निकास_समय_ns / 1000.0;
	पूर्ण

	अगर ((पूर्णांक)(bb->sr_enter_plus_निकास_समय_us * 1000)
				!= dc->bb_overrides.sr_enter_plus_निकास_समय_ns
			&& dc->bb_overrides.sr_enter_plus_निकास_समय_ns) अणु
		bb->sr_enter_plus_निकास_समय_us =
				dc->bb_overrides.sr_enter_plus_निकास_समय_ns / 1000.0;
	पूर्ण

	अगर ((पूर्णांक)(bb->urgent_latency_us * 1000) != dc->bb_overrides.urgent_latency_ns
			&& dc->bb_overrides.urgent_latency_ns) अणु
		bb->urgent_latency_us = dc->bb_overrides.urgent_latency_ns / 1000.0;
	पूर्ण

	अगर ((पूर्णांक)(bb->dram_घड़ी_change_latency_us * 1000)
				!= dc->bb_overrides.dram_घड़ी_change_latency_ns
			&& dc->bb_overrides.dram_घड़ी_change_latency_ns) अणु
		bb->dram_घड़ी_change_latency_us =
				dc->bb_overrides.dram_घड़ी_change_latency_ns / 1000.0;
	पूर्ण

	अगर ((पूर्णांक)(bb->dummy_pstate_latency_us * 1000)
				!= dc->bb_overrides.dummy_घड़ी_change_latency_ns
			&& dc->bb_overrides.dummy_घड़ी_change_latency_ns) अणु
		bb->dummy_pstate_latency_us =
				dc->bb_overrides.dummy_घड़ी_change_latency_ns / 1000.0;
	पूर्ण
पूर्ण

अटल काष्ठा _vcs_dpi_soc_bounding_box_st *get_asic_rev_soc_bb(
	uपूर्णांक32_t hw_पूर्णांकernal_rev)
अणु
	अगर (ASICREV_IS_NAVI14_M(hw_पूर्णांकernal_rev))
		वापस &dcn2_0_nv14_soc;

	अगर (ASICREV_IS_NAVI12_P(hw_पूर्णांकernal_rev))
		वापस &dcn2_0_nv12_soc;

	वापस &dcn2_0_soc;
पूर्ण

अटल काष्ठा _vcs_dpi_ip_params_st *get_asic_rev_ip_params(
	uपूर्णांक32_t hw_पूर्णांकernal_rev)
अणु
	/* NV14 */
	अगर (ASICREV_IS_NAVI14_M(hw_पूर्णांकernal_rev))
		वापस &dcn2_0_nv14_ip;

	/* NV12 and NV10 */
	वापस &dcn2_0_ip;
पूर्ण

अटल क्रमागत dml_project get_dml_project_version(uपूर्णांक32_t hw_पूर्णांकernal_rev)
अणु
	वापस DML_PROJECT_NAVI10v2;
पूर्ण

#घोषणा fixed16_to_द्विगुन(x) (((द्विगुन) x) / ((द्विगुन) (1 << 16)))
#घोषणा fixed16_to_द्विगुन_to_cpu(x) fixed16_to_द्विगुन(le32_to_cpu(x))

अटल bool init_soc_bounding_box(काष्ठा dc *dc,
				  काष्ठा dcn20_resource_pool *pool)
अणु
	काष्ठा _vcs_dpi_soc_bounding_box_st *loaded_bb =
			get_asic_rev_soc_bb(dc->ctx->asic_id.hw_पूर्णांकernal_rev);
	काष्ठा _vcs_dpi_ip_params_st *loaded_ip =
			get_asic_rev_ip_params(dc->ctx->asic_id.hw_पूर्णांकernal_rev);

	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (pool->base.pp_smu) अणु
		काष्ठा pp_smu_nv_घड़ी_प्रकारable max_घड़ीs = अणु0पूर्ण;
		अचिन्हित पूर्णांक uclk_states[8] = अणु0पूर्ण;
		अचिन्हित पूर्णांक num_states = 0;
		क्रमागत pp_smu_status status;
		bool घड़ी_limits_available = false;
		bool uclk_states_available = false;

		अगर (pool->base.pp_smu->nv_funcs.get_uclk_dpm_states) अणु
			status = (pool->base.pp_smu->nv_funcs.get_uclk_dpm_states)
				(&pool->base.pp_smu->nv_funcs.pp_smu, uclk_states, &num_states);

			uclk_states_available = (status == PP_SMU_RESULT_OK);
		पूर्ण

		अगर (pool->base.pp_smu->nv_funcs.get_maximum_sustainable_घड़ीs) अणु
			status = (*pool->base.pp_smu->nv_funcs.get_maximum_sustainable_घड़ीs)
					(&pool->base.pp_smu->nv_funcs.pp_smu, &max_घड़ीs);
			/* SMU cannot set DCF घड़ी to anything equal to or higher than SOC घड़ी
			 */
			अगर (max_घड़ीs.dcfClockInKhz >= max_घड़ीs.socClockInKhz)
				max_घड़ीs.dcfClockInKhz = max_घड़ीs.socClockInKhz - 1000;
			घड़ी_limits_available = (status == PP_SMU_RESULT_OK);
		पूर्ण

		अगर (घड़ी_limits_available && uclk_states_available && num_states)
			dcn20_update_bounding_box(dc, loaded_bb, &max_घड़ीs, uclk_states, num_states);
		अन्यथा अगर (घड़ी_limits_available)
			dcn20_cap_soc_घड़ीs(loaded_bb, max_घड़ीs);
	पूर्ण

	loaded_ip->max_num_otg = pool->base.res_cap->num_timing_generator;
	loaded_ip->max_num_dpp = pool->base.pipe_count;
	dcn20_patch_bounding_box(dc, loaded_bb);

	वापस true;
पूर्ण

अटल bool dcn20_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा dcn20_resource_pool *pool)
अणु
	पूर्णांक i;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा irq_service_init_data init_data;
	काष्ठा ddc_service_init_data ddc_init_data;
	काष्ठा _vcs_dpi_soc_bounding_box_st *loaded_bb =
			get_asic_rev_soc_bb(ctx->asic_id.hw_पूर्णांकernal_rev);
	काष्ठा _vcs_dpi_ip_params_st *loaded_ip =
			get_asic_rev_ip_params(ctx->asic_id.hw_पूर्णांकernal_rev);
	क्रमागत dml_project dml_project_version =
			get_dml_project_version(ctx->asic_id.hw_पूर्णांकernal_rev);

	DC_FP_START();

	ctx->dc_bios->regs = &bios_regs;
	pool->base.funcs = &dcn20_res_pool_funcs;

	अगर (ASICREV_IS_NAVI14_M(ctx->asic_id.hw_पूर्णांकernal_rev)) अणु
		pool->base.res_cap = &res_cap_nv14;
		pool->base.pipe_count = 5;
		pool->base.mpcc_count = 5;
	पूर्ण अन्यथा अणु
		pool->base.res_cap = &res_cap_nv10;
		pool->base.pipe_count = 6;
		pool->base.mpcc_count = 6;
	पूर्ण
	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;

	dc->caps.max_करोwnscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100; /*1.4 w/a not applied by शेष*/
	dc->caps.max_cursor_size = 256;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.dmdata_alloc_size = 2048;

	dc->caps.max_slave_planes = 1;
	dc->caps.max_slave_yuv_planes = 1;
	dc->caps.max_slave_rgb_planes = 1;
	dc->caps.post_blend_color_processing = true;
	dc->caps.क्रमce_dp_tps4_क्रम_cp2520 = true;
	dc->caps.extended_aux_समयout_support = true;

	/* Color pipeline capabilities */
	dc->caps.color.dpp.dcn_arch = 1;
	dc->caps.color.dpp.input_lut_shared = 0;
	dc->caps.color.dpp.icsc = 1;
	dc->caps.color.dpp.dgam_ram = 1;
	dc->caps.color.dpp.dgam_rom_caps.srgb = 1;
	dc->caps.color.dpp.dgam_rom_caps.bt2020 = 1;
	dc->caps.color.dpp.dgam_rom_caps.gamma2_2 = 0;
	dc->caps.color.dpp.dgam_rom_caps.pq = 0;
	dc->caps.color.dpp.dgam_rom_caps.hlg = 0;
	dc->caps.color.dpp.post_csc = 0;
	dc->caps.color.dpp.gamma_corr = 0;
	dc->caps.color.dpp.dgam_rom_क्रम_yuv = 1;

	dc->caps.color.dpp.hw_3d_lut = 1;
	dc->caps.color.dpp.ogam_ram = 1;
	// no OGAM ROM on DCN2, only MPC ROM
	dc->caps.color.dpp.ogam_rom_caps.srgb = 0;
	dc->caps.color.dpp.ogam_rom_caps.bt2020 = 0;
	dc->caps.color.dpp.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.dpp.ogam_rom_caps.pq = 0;
	dc->caps.color.dpp.ogam_rom_caps.hlg = 0;
	dc->caps.color.dpp.ocsc = 0;

	dc->caps.color.mpc.gamut_remap = 0;
	dc->caps.color.mpc.num_3dluts = 0;
	dc->caps.color.mpc.shared_3d_lut = 0;
	dc->caps.color.mpc.ogam_ram = 1;
	dc->caps.color.mpc.ogam_rom_caps.srgb = 0;
	dc->caps.color.mpc.ogam_rom_caps.bt2020 = 0;
	dc->caps.color.mpc.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.mpc.ogam_rom_caps.pq = 0;
	dc->caps.color.mpc.ogam_rom_caps.hlg = 0;
	dc->caps.color.mpc.ocsc = 1;

	अगर (dc->ctx->dce_environment == DCE_ENV_PRODUCTION_DRV) अणु
		dc->debug = debug_शेषs_drv;
	पूर्ण अन्यथा अगर (dc->ctx->dce_environment == DCE_ENV_FPGA_MAXIMUS) अणु
		pool->base.pipe_count = 4;
		pool->base.mpcc_count = pool->base.pipe_count;
		dc->debug = debug_शेषs_diags;
	पूर्ण अन्यथा अणु
		dc->debug = debug_शेषs_diags;
	पूर्ण
	//dcn2.0x
	dc->work_arounds.dedcn20_305_wa = true;

	// Init the vm_helper
	अगर (dc->vm_helper)
		vm_helper_init(dc->vm_helper, 16);

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL0] =
			dcn20_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL0,
				&clk_src_regs[0], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL1] =
			dcn20_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL1,
				&clk_src_regs[1], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL2] =
			dcn20_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL2,
				&clk_src_regs[2], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL3] =
			dcn20_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL3,
				&clk_src_regs[3], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL4] =
			dcn20_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL4,
				&clk_src_regs[4], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL5] =
			dcn20_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL5,
				&clk_src_regs[5], false);
	pool->base.clk_src_count = DCN20_CLK_SRC_TOTAL;
	/* toकरो: not reuse phy_pll रेजिस्टरs */
	pool->base.dp_घड़ी_source =
			dcn20_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_ID_DP_DTO,
				&clk_src_regs[0], true);

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] == शून्य) अणु
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण
	पूर्ण

	pool->base.dccg = dccg2_create(ctx, &dccg_regs, &dccg_shअगरt, &dccg_mask);
	अगर (pool->base.dccg == शून्य) अणु
		dm_error("DC: failed to create dccg!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	pool->base.dmcu = dcn20_dmcu_create(ctx,
			&dmcu_regs,
			&dmcu_shअगरt,
			&dmcu_mask);
	अगर (pool->base.dmcu == शून्य) अणु
		dm_error("DC: failed to create dmcu!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	pool->base.abm = dce_abm_create(ctx,
			&abm_regs,
			&abm_shअगरt,
			&abm_mask);
	अगर (pool->base.abm == शून्य) अणु
		dm_error("DC: failed to create abm!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	pool->base.pp_smu = dcn20_pp_smu_create(ctx);


	अगर (!init_soc_bounding_box(dc, pool)) अणु
		dm_error("DC: failed to initialize soc bounding box!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	dml_init_instance(&dc->dml, loaded_bb, loaded_ip, dml_project_version);

	अगर (!dc->debug.disable_pplib_wm_range) अणु
		काष्ठा pp_smu_wm_range_sets ranges = अणु0पूर्ण;
		पूर्णांक i = 0;

		ranges.num_पढ़ोer_wm_sets = 0;

		अगर (loaded_bb->num_states == 1) अणु
			ranges.पढ़ोer_wm_sets[0].wm_inst = i;
			ranges.पढ़ोer_wm_sets[0].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
			ranges.पढ़ोer_wm_sets[0].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
			ranges.पढ़ोer_wm_sets[0].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
			ranges.पढ़ोer_wm_sets[0].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

			ranges.num_पढ़ोer_wm_sets = 1;
		पूर्ण अन्यथा अगर (loaded_bb->num_states > 1) अणु
			क्रम (i = 0; i < 4 && i < loaded_bb->num_states; i++) अणु
				ranges.पढ़ोer_wm_sets[i].wm_inst = i;
				ranges.पढ़ोer_wm_sets[i].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
				ranges.पढ़ोer_wm_sets[i].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
				ranges.पढ़ोer_wm_sets[i].min_fill_clk_mhz = (i > 0) ? (loaded_bb->घड़ी_limits[i - 1].dram_speed_mts / 16) + 1 : 0;
				ranges.पढ़ोer_wm_sets[i].max_fill_clk_mhz = loaded_bb->घड़ी_limits[i].dram_speed_mts / 16;

				ranges.num_पढ़ोer_wm_sets = i + 1;
			पूर्ण

			ranges.पढ़ोer_wm_sets[0].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
			ranges.पढ़ोer_wm_sets[ranges.num_पढ़ोer_wm_sets - 1].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
		पूर्ण

		ranges.num_ग_लिखोr_wm_sets = 1;

		ranges.ग_लिखोr_wm_sets[0].wm_inst = 0;
		ranges.ग_लिखोr_wm_sets[0].min_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
		ranges.ग_लिखोr_wm_sets[0].max_fill_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;
		ranges.ग_लिखोr_wm_sets[0].min_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MIN;
		ranges.ग_लिखोr_wm_sets[0].max_drain_clk_mhz = PP_SMU_WM_SET_RANGE_CLK_UNCONSTRAINED_MAX;

		/* Notअगरy PP Lib/SMU which Watermarks to use क्रम which घड़ी ranges */
		अगर (pool->base.pp_smu->nv_funcs.set_wm_ranges)
			pool->base.pp_smu->nv_funcs.set_wm_ranges(&pool->base.pp_smu->nv_funcs.pp_smu, &ranges);
	पूर्ण

	init_data.ctx = dc->ctx;
	pool->base.irqs = dal_irq_service_dcn20_create(&init_data);
	अगर (!pool->base.irqs)
		जाओ create_fail;

	/* mem input -> ipp -> dpp -> opp -> TG */
	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		pool->base.hubps[i] = dcn20_hubp_create(ctx, i);
		अगर (pool->base.hubps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.ipps[i] = dcn20_ipp_create(ctx, i);
		अगर (pool->base.ipps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.dpps[i] = dcn20_dpp_create(ctx, i);
		अगर (pool->base.dpps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create dpps!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dcn20_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dcn20_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create hw i2c!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_opp; i++) अणु
		pool->base.opps[i] = dcn20_opp_create(ctx, i);
		अगर (pool->base.opps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_timing_generator; i++) अणु
		pool->base.timing_generators[i] = dcn20_timing_generator_create(
				ctx, i);
		अगर (pool->base.timing_generators[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण

	pool->base.timing_generator_count = i;

	pool->base.mpc = dcn20_mpc_create(ctx);
	अगर (pool->base.mpc == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mpc!\n");
		जाओ create_fail;
	पूर्ण

	pool->base.hubbub = dcn20_hubbub_create(ctx);
	अगर (pool->base.hubbub == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create hubbub!\n");
		जाओ create_fail;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_dsc; i++) अणु
		pool->base.dscs[i] = dcn20_dsc_create(ctx, i);
		अगर (pool->base.dscs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create display stream compressor %d!\n", i);
			जाओ create_fail;
		पूर्ण
	पूर्ण

	अगर (!dcn20_dwbc_create(ctx, &pool->base)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create dwbc!\n");
		जाओ create_fail;
	पूर्ण
	अगर (!dcn20_mmhubbub_create(ctx, &pool->base)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mcif_wb!\n");
		जाओ create_fail;
	पूर्ण

	अगर (!resource_स्थिरruct(num_भव_links, dc, &pool->base,
			(!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment) ?
			&res_create_funcs : &res_create_maximus_funcs)))
			जाओ create_fail;

	dcn20_hw_sequencer_स्थिरruct(dc);

	// IF NV12, set PG function poपूर्णांकer to शून्य. It's not that
	// PG isn't supported for NV12, it's that we don't want to
	// program the रेजिस्टरs because that will cause more घातer
	// to be consumed. We could have created dcn20_init_hw to get
	// the same effect by checking ASIC rev, but there was a
	// request at some poपूर्णांक to not check ASIC rev on hw sequencer.
	अगर (ASICREV_IS_NAVI12_P(dc->ctx->asic_id.hw_पूर्णांकernal_rev)) अणु
		dc->hwseq->funcs.enable_घातer_gating_plane = शून्य;
		dc->debug.disable_dpp_घातer_gate = true;
		dc->debug.disable_hubp_घातer_gate = true;
	पूर्ण


	dc->caps.max_planes =  pool->base.pipe_count;

	क्रम (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	dc->cap_funcs = cap_funcs;

	अगर (dc->ctx->dc_bios->fw_info.oem_i2c_present) अणु
		ddc_init_data.ctx = dc->ctx;
		ddc_init_data.link = शून्य;
		ddc_init_data.id.id = dc->ctx->dc_bios->fw_info.oem_i2c_obj_id;
		ddc_init_data.id.क्रमागत_id = 0;
		ddc_init_data.id.type = OBJECT_TYPE_GENERIC;
		pool->base.oem_device = dal_ddc_service_create(&ddc_init_data);
	पूर्ण अन्यथा अणु
		pool->base.oem_device = शून्य;
	पूर्ण

	DC_FP_END();
	वापस true;

create_fail:

	DC_FP_END();
	dcn20_resource_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dcn20_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc)
अणु
	काष्ठा dcn20_resource_pool *pool =
		kzalloc(माप(काष्ठा dcn20_resource_pool), GFP_ATOMIC);

	अगर (!pool)
		वापस शून्य;

	अगर (dcn20_resource_स्थिरruct(init_data->num_भव_links, dc, pool))
		वापस &pool->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(pool);
	वापस शून्य;
पूर्ण
