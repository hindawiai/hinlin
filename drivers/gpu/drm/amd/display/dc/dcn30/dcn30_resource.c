<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "dc.h"

#समावेश "dcn30_init.h"

#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "dcn20/dcn20_resource.h"

#समावेश "dcn30_resource.h"

#समावेश "dcn10/dcn10_ipp.h"
#समावेश "dcn30/dcn30_hubbub.h"
#समावेश "dcn30/dcn30_mpc.h"
#समावेश "dcn30/dcn30_hubp.h"
#समावेश "irq/dcn30/irq_service_dcn30.h"
#समावेश "dcn30/dcn30_dpp.h"
#समावेश "dcn30/dcn30_optc.h"
#समावेश "dcn20/dcn20_hwseq.h"
#समावेश "dcn30/dcn30_hwseq.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dcn30/dcn30_opp.h"
#समावेश "dcn20/dcn20_dsc.h"
#समावेश "dcn30/dcn30_vpg.h"
#समावेश "dcn30/dcn30_afmt.h"
#समावेश "dcn30/dcn30_dio_stream_encoder.h"
#समावेश "dcn30/dcn30_dio_link_encoder.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "clk_mgr.h"
#समावेश "virtual/virtual_stream_encoder.h"
#समावेश "dce110/dce110_resource.h"
#समावेश "dml/display_mode_vba.h"
#समावेश "dcn30/dcn30_dccg.h"
#समावेश "dcn10/dcn10_resource.h"
#समावेश "dc_link_ddc.h"
#समावेश "dce/dce_panel_cntl.h"

#समावेश "dcn30/dcn30_dwb.h"
#समावेश "dcn30/dcn30_mmhubbub.h"

#समावेश "sienna_cichlid_ip_offset.h"
#समावेश "dcn/dcn_3_0_0_offset.h"
#समावेश "dcn/dcn_3_0_0_sh_mask.h"

#समावेश "nbio/nbio_7_4_offset.h"

#समावेश "dcn/dpcs_3_0_0_offset.h"
#समावेश "dcn/dpcs_3_0_0_sh_mask.h"

#समावेश "mmhub/mmhub_2_0_0_offset.h"
#समावेश "mmhub/mmhub_2_0_0_sh_mask.h"

#समावेश "reg_helper.h"
#समावेश "dce/dmub_abm.h"
#समावेश "dce/dmub_psr.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_i2c.h"

#समावेश "dml/dcn30/display_mode_vba_30.h"
#समावेश "vm_helper.h"
#समावेश "dcn20/dcn20_vmid.h"
#समावेश "amdgpu_socbb.h"

#घोषणा DC_LOGGER_INIT(logger)

काष्ठा _vcs_dpi_ip_params_st dcn3_0_ip = अणु
	.use_min_dcfclk = 1,
	.clamp_min_dcfclk = 0,
	.odm_capable = 1,
	.gpuvm_enable = 0,
	.hostvm_enable = 0,
	.gpuvm_max_page_table_levels = 4,
	.hostvm_max_page_table_levels = 4,
	.hostvm_cached_page_table_levels = 0,
	.pte_group_size_bytes = 2048,
	.num_dsc = 6,
	.rob_buffer_size_kbytes = 184,
	.det_buffer_size_kbytes = 184,
	.dpte_buffer_size_in_pte_reqs_luma = 84,
	.pde_proc_buffer_size_64k_reqs = 48,
	.dpp_output_buffer_pixels = 2560,
	.opp_output_buffer_lines = 1,
	.pixel_chunk_size_kbytes = 8,
	.pte_enable = 1,
	.max_page_table_levels = 2,
	.pte_chunk_size_kbytes = 2,  // ?
	.meta_chunk_size_kbytes = 2,
	.ग_लिखोback_chunk_size_kbytes = 8,
	.line_buffer_size_bits = 789504,
	.is_line_buffer_bpp_fixed = 0,  // ?
	.line_buffer_fixed_bpp = 0,     // ?
	.dcc_supported = true,
	.ग_लिखोback_पूर्णांकerface_buffer_size_kbytes = 90,
	.ग_लिखोback_line_buffer_buffer_size = 0,
	.max_line_buffer_lines = 12,
	.ग_लिखोback_luma_buffer_size_kbytes = 12,  // ग_लिखोback_line_buffer_buffer_size = 656640
	.ग_लिखोback_chroma_buffer_size_kbytes = 8,
	.ग_लिखोback_chroma_line_buffer_width_pixels = 4,
	.ग_लिखोback_max_hscl_ratio = 1,
	.ग_लिखोback_max_vscl_ratio = 1,
	.ग_लिखोback_min_hscl_ratio = 1,
	.ग_लिखोback_min_vscl_ratio = 1,
	.ग_लिखोback_max_hscl_taps = 1,
	.ग_लिखोback_max_vscl_taps = 1,
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
	.max_hscl_ratio = 6,
	.max_vscl_ratio = 6,
	.hscl_mults = 4,
	.vscl_mults = 4,
	.max_hscl_taps = 8,
	.max_vscl_taps = 8,
	.dispclk_ramp_margin_percent = 1,
	.underscan_factor = 1.11,
	.min_vblank_lines = 32,
	.dppclk_delay_subtotal = 46,
	.dynamic_metadata_vm_enabled = true,
	.dppclk_delay_scl_lb_only = 16,
	.dppclk_delay_scl = 50,
	.dppclk_delay_cnvc_क्रमmatter = 27,
	.dppclk_delay_cnvc_cursor = 6,
	.dispclk_delay_subtotal = 119,
	.dcfclk_cstate_latency = 5.2, // SRExitTime
	.max_पूर्णांकer_dcn_tile_repeaters = 8,
	.odm_combine_4to1_supported = true,

	.xfc_supported = false,
	.xfc_fill_bw_overhead_percent = 10.0,
	.xfc_fill_स्थिरant_bytes = 0,
	.gfx7_compat_tiling_supported = 0,
	.number_of_cursors = 1,
पूर्ण;

काष्ठा _vcs_dpi_soc_bounding_box_st dcn3_0_soc = अणु
	.घड़ी_limits = अणु
			अणु
				.state = 0,
				.dispclk_mhz = 562.0,
				.dppclk_mhz = 300.0,
				.phyclk_mhz = 300.0,
				.phyclk_d18_mhz = 667.0,
				.dscclk_mhz = 405.6,
			पूर्ण,
		पूर्ण,
	.min_dcfclk = 500.0, /* TODO: set this to actual min DCFCLK */
	.num_states = 1,
	.sr_निकास_समय_us = 15.5,
	.sr_enter_plus_निकास_समय_us = 20,
	.urgent_latency_us = 4.0,
	.urgent_latency_pixel_data_only_us = 4.0,
	.urgent_latency_pixel_mixed_with_vm_data_us = 4.0,
	.urgent_latency_vm_data_only_us = 4.0,
	.urgent_out_of_order_वापस_per_channel_pixel_only_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_pixel_and_vm_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_vm_only_bytes = 4096,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_only = 80.0,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_and_vm = 60.0,
	.pct_ideal_dram_sdp_bw_after_urgent_vm_only = 40.0,
	.max_avg_sdp_bw_use_normal_percent = 60.0,
	.max_avg_dram_bw_use_normal_percent = 40.0,
	.ग_लिखोback_latency_us = 12.0,
	.max_request_size_bytes = 256,
	.fabric_datapath_to_dcn_data_वापस_bytes = 64,
	.dcn_करोwnspपढ़ो_percent = 0.5,
	.करोwnspपढ़ो_percent = 0.38,
	.dram_page_खोलो_समय_ns = 50.0,
	.dram_rw_turnaround_समय_ns = 17.5,
	.dram_वापस_buffer_per_channel_bytes = 8192,
	.round_trip_ping_latency_dcfclk_cycles = 191,
	.urgent_out_of_order_वापस_per_channel_bytes = 4096,
	.channel_पूर्णांकerleave_bytes = 256,
	.num_banks = 8,
	.gpuvm_min_page_size_bytes = 4096,
	.hostvm_min_page_size_bytes = 4096,
	.dram_घड़ी_change_latency_us = 404,
	.dummy_pstate_latency_us = 5,
	.ग_लिखोback_dram_घड़ी_change_latency_us = 23.0,
	.वापस_bus_width_bytes = 64,
	.dispclk_dppclk_vco_speed_mhz = 3650,
	.xfc_bus_transport_समय_us = 20,      // ?
	.xfc_xbuf_latency_tolerance_us = 4,  // ?
	.use_urgent_burst_bw = 1,            // ?
	.करो_urgent_latency_adjusपंचांगent = true,
	.urgent_latency_adjusपंचांगent_fabric_घड़ी_component_us = 1.0,
	.urgent_latency_adjusपंचांगent_fabric_घड़ी_reference_mhz = 1000,
पूर्ण;

क्रमागत dcn30_clk_src_array_id अणु
	DCN30_CLK_SRC_PLL0,
	DCN30_CLK_SRC_PLL1,
	DCN30_CLK_SRC_PLL2,
	DCN30_CLK_SRC_PLL3,
	DCN30_CLK_SRC_PLL4,
	DCN30_CLK_SRC_PLL5,
	DCN30_CLK_SRC_TOTAL
पूर्ण;

/* begin *********************
 * macros to expend रेजिस्टर list macro defined in HW object header file
 */

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

#घोषणा SRI2(reg_name, block, id)\
	.reg_name = BASE(mm ## reg_name ## _BASE_IDX) + \
					mm ## reg_name

#घोषणा SRIR(var_name, reg_name, block, id)\
	.var_name = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा SRII(reg_name, block, id)\
	.reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा SRII_MPC_RMU(reg_name, block, id)\
	.RMU##_##reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा SRII_DWB(reg_name, temp_name, block, id)\
	.reg_name[id] = BASE(mm ## block ## id ## _ ## temp_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## temp_name

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

/* CLOCK */
#घोषणा CLK_BASE_INNER(seg) \
	CLK_BASE__INST0_SEG ## seg

#घोषणा CLK_BASE(seg) \
	CLK_BASE_INNER(seg)

#घोषणा CLK_SRI(reg_name, block, inst)\
	.reg_name = CLK_BASE(mm ## block ## _ ## inst ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## _ ## inst ## _ ## reg_name


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

#घोषणा abm_regs(id)\
[id] = अणु\
		ABM_DCN30_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dce_abm_रेजिस्टरs abm_regs[] = अणु
		abm_regs(0),
		abm_regs(1),
		abm_regs(2),
		abm_regs(3),
		abm_regs(4),
		abm_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dce_abm_shअगरt abm_shअगरt = अणु
		ABM_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_mask abm_mask = अणु
		ABM_MASK_SH_LIST_DCN30(_MASK)
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
	audio_regs(6)
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

#घोषणा vpg_regs(id)\
[id] = अणु\
	VPG_DCN3_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn30_vpg_रेजिस्टरs vpg_regs[] = अणु
	vpg_regs(0),
	vpg_regs(1),
	vpg_regs(2),
	vpg_regs(3),
	vpg_regs(4),
	vpg_regs(5),
	vpg_regs(6),
पूर्ण;

अटल स्थिर काष्ठा dcn30_vpg_shअगरt vpg_shअगरt = अणु
	DCN3_VPG_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_vpg_mask vpg_mask = अणु
	DCN3_VPG_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा afmt_regs(id)\
[id] = अणु\
	AFMT_DCN3_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn30_afmt_रेजिस्टरs afmt_regs[] = अणु
	afmt_regs(0),
	afmt_regs(1),
	afmt_regs(2),
	afmt_regs(3),
	afmt_regs(4),
	afmt_regs(5),
	afmt_regs(6),
पूर्ण;

अटल स्थिर काष्ठा dcn30_afmt_shअगरt afmt_shअगरt = अणु
	DCN3_AFMT_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_afmt_mask afmt_mask = अणु
	DCN3_AFMT_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा stream_enc_regs(id)\
[id] = अणु\
	SE_DCN3_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs stream_enc_regs[] = अणु
	stream_enc_regs(0),
	stream_enc_regs(1),
	stream_enc_regs(2),
	stream_enc_regs(3),
	stream_enc_regs(4),
	stream_enc_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCN30(_MASK)
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
	LE_DCN3_REG_LIST(id), \
	UNIPHY_DCN2_REG_LIST(phyid), \
	DPCS_DCN2_REG_LIST(id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id) \
पूर्ण

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt aux_shअगरt = अणु
	DCN_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
	DCN_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs link_enc_regs[] = अणु
	link_regs(0, A),
	link_regs(1, B),
	link_regs(2, C),
	link_regs(3, D),
	link_regs(4, E),
	link_regs(5, F)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_shअगरt le_shअगरt = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN30(__SHIFT),\
	DPCS_DCN2_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_mask le_mask = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN30(_MASK),\
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

#घोषणा dpp_regs(id)\
[id] = अणु\
	DPP_REG_LIST_DCN30(id),\
पूर्ण

अटल स्थिर काष्ठा dcn3_dpp_रेजिस्टरs dpp_regs[] = अणु
	dpp_regs(0),
	dpp_regs(1),
	dpp_regs(2),
	dpp_regs(3),
	dpp_regs(4),
	dpp_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dcn3_dpp_shअगरt tf_shअगरt = अणु
		DPP_REG_LIST_SH_MASK_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn3_dpp_mask tf_mask = अणु
		DPP_REG_LIST_SH_MASK_DCN30(_MASK)
पूर्ण;

#घोषणा opp_regs(id)\
[id] = अणु\
	OPP_REG_LIST_DCN30(id),\
पूर्ण

अटल स्थिर काष्ठा dcn20_opp_रेजिस्टरs opp_regs[] = अणु
	opp_regs(0),
	opp_regs(1),
	opp_regs(2),
	opp_regs(3),
	opp_regs(4),
	opp_regs(5)
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

#घोषणा dwbc_regs_dcn3(id)\
[id] = अणु\
	DWBC_COMMON_REG_LIST_DCN30(id),\
पूर्ण

अटल स्थिर काष्ठा dcn30_dwbc_रेजिस्टरs dwbc30_regs[] = अणु
	dwbc_regs_dcn3(0),
पूर्ण;

अटल स्थिर काष्ठा dcn30_dwbc_shअगरt dwbc30_shअगरt = अणु
	DWBC_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_dwbc_mask dwbc30_mask = अणु
	DWBC_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

#घोषणा mcअगर_wb_regs_dcn3(id)\
[id] = अणु\
	MCIF_WB_COMMON_REG_LIST_DCN30(id),\
पूर्ण

अटल स्थिर काष्ठा dcn30_mmhubbub_रेजिस्टरs mcअगर_wb30_regs[] = अणु
	mcअगर_wb_regs_dcn3(0)
पूर्ण;

अटल स्थिर काष्ठा dcn30_mmhubbub_shअगरt mcअगर_wb30_shअगरt = अणु
	MCIF_WB_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_mmhubbub_mask mcअगर_wb30_mask = अणु
	MCIF_WB_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

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

अटल स्थिर काष्ठा dcn30_mpc_रेजिस्टरs mpc_regs = अणु
		MPC_REG_LIST_DCN3_0(0),
		MPC_REG_LIST_DCN3_0(1),
		MPC_REG_LIST_DCN3_0(2),
		MPC_REG_LIST_DCN3_0(3),
		MPC_REG_LIST_DCN3_0(4),
		MPC_REG_LIST_DCN3_0(5),
		MPC_OUT_MUX_REG_LIST_DCN3_0(0),
		MPC_OUT_MUX_REG_LIST_DCN3_0(1),
		MPC_OUT_MUX_REG_LIST_DCN3_0(2),
		MPC_OUT_MUX_REG_LIST_DCN3_0(3),
		MPC_OUT_MUX_REG_LIST_DCN3_0(4),
		MPC_OUT_MUX_REG_LIST_DCN3_0(5),
		MPC_RMU_GLOBAL_REG_LIST_DCN3AG,
		MPC_RMU_REG_LIST_DCN3AG(0),
		MPC_RMU_REG_LIST_DCN3AG(1),
		MPC_RMU_REG_LIST_DCN3AG(2),
		MPC_DWB_MUX_REG_LIST_DCN3_0(0),
पूर्ण;

अटल स्थिर काष्ठा dcn30_mpc_shअगरt mpc_shअगरt = अणु
	MPC_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_mpc_mask mpc_mask = अणु
	MPC_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

#घोषणा optc_regs(id)\
[id] = अणुOPTC_COMMON_REG_LIST_DCN3_0(id)पूर्ण


अटल स्थिर काष्ठा dcn_optc_रेजिस्टरs optc_regs[] = अणु
	optc_regs(0),
	optc_regs(1),
	optc_regs(2),
	optc_regs(3),
	optc_regs(4),
	optc_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_shअगरt optc_shअगरt = अणु
	OPTC_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_mask optc_mask = अणु
	OPTC_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

#घोषणा hubp_regs(id)\
[id] = अणु\
	HUBP_REG_LIST_DCN30(id)\
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
		HUBP_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_mask hubp_mask = अणु
		HUBP_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_रेजिस्टरs hubbub_reg = अणु
		HUBBUB_REG_LIST_DCN30(0)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_shअगरt hubbub_shअगरt = अणु
		HUBBUB_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_mask hubbub_mask = अणु
		HUBBUB_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dccg_रेजिस्टरs dccg_regs = अणु
		DCCG_REG_LIST_DCN30()
पूर्ण;

अटल स्थिर काष्ठा dccg_shअगरt dccg_shअगरt = अणु
		DCCG_MASK_SH_LIST_DCN3(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dccg_mask dccg_mask = अणु
		DCCG_MASK_SH_LIST_DCN3(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCN30_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCN30_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCN30_MASK_SH_LIST(_MASK)
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

अटल स्थिर काष्ठा resource_caps res_cap_dcn3 = अणु
	.num_timing_generator = 6,
	.num_opp = 6,
	.num_video_plane = 6,
	.num_audio = 6,
	.num_stream_encoder = 6,
	.num_pll = 6,
	.num_dwb = 1,
	.num_ddc = 6,
	.num_vmid = 16,
	.num_mpc_3dlut = 3,
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
			.p010 = false,
			.ayuv = false,
	पूर्ण,

	.max_upscale_factor = अणु
			.argb8888 = 16000,
			.nv12 = 16000,
			.fp16 = 16000
	पूर्ण,

	/* 6:1 करोwnscaling ratio: 1000/6 = 166.666 */
	.max_करोwnscale_factor = अणु
			.argb8888 = 167,
			.nv12 = 167,
			.fp16 = 167
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_drv = अणु
	.disable_dmcu = true, //No DMCU on DCN30
	.क्रमce_abm_enable = false,
	.timing_trace = false,
	.घड़ी_प्रकारrace = true,
	.disable_pplib_घड़ी_request = true,
	.pipe_split_policy = MPC_SPLIT_DYNAMIC,
	.क्रमce_single_disp_pipe_split = false,
	.disable_dcc = DCC_ENABLE,
	.vsr_support = true,
	.perक्रमmance_trace = false,
	.max_करोwnscale_src_width = 7680,/*upto 8K*/
	.disable_pplib_wm_range = false,
	.scl_reset_length10 = true,
	.sanity_checks = false,
	.underflow_निश्चित_delay_us = 0xFFFFFFFF,
	.dwb_fi_phase = -1, // -1 = disable,
	.dmub_command_table = true,
	.disable_psr = false,
	.use_max_lb = true
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_diags = अणु
	.disable_dmcu = true, //No dmcu on DCN30
	.क्रमce_abm_enable = false,
	.timing_trace = true,
	.घड़ी_प्रकारrace = true,
	.disable_dpp_घातer_gate = true,
	.disable_hubp_घातer_gate = true,
	.disable_घड़ी_gate = true,
	.disable_pplib_घड़ी_request = true,
	.disable_pplib_wm_range = true,
	.disable_stutter = false,
	.scl_reset_length10 = true,
	.dwb_fi_phase = -1, // -1 = disable
	.dmub_command_table = true,
	.disable_psr = true,
	.enable_tri_buf = true,
	.use_max_lb = true
पूर्ण;

व्योम dcn30_dpp_destroy(काष्ठा dpp **dpp)
अणु
	kमुक्त(TO_DCN20_DPP(*dpp));
	*dpp = शून्य;
पूर्ण

अटल काष्ठा dpp *dcn30_dpp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn3_dpp *dpp =
		kzalloc(माप(काष्ठा dcn3_dpp), GFP_KERNEL);

	अगर (!dpp)
		वापस शून्य;

	अगर (dpp3_स्थिरruct(dpp, ctx, inst,
			&dpp_regs[inst], &tf_shअगरt, &tf_mask))
		वापस &dpp->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(dpp);
	वापस शून्य;
पूर्ण

अटल काष्ठा output_pixel_processor *dcn30_opp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_opp *opp =
		kzalloc(माप(काष्ठा dcn20_opp), GFP_KERNEL);

	अगर (!opp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn20_opp_स्थिरruct(opp, ctx, inst,
			&opp_regs[inst], &opp_shअगरt, &opp_mask);
	वापस &opp->base;
पूर्ण

अटल काष्ठा dce_aux *dcn30_aux_engine_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा aux_engine_dce110 *aux_engine =
		kzalloc(माप(काष्ठा aux_engine_dce110), GFP_KERNEL);

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

#घोषणा i2c_inst_regs(id) अणु I2C_HW_ENGINE_COMMON_REG_LIST_DCN30(id) पूर्ण

अटल स्थिर काष्ठा dce_i2c_रेजिस्टरs i2c_hw_regs[] = अणु
		i2c_inst_regs(1),
		i2c_inst_regs(2),
		i2c_inst_regs(3),
		i2c_inst_regs(4),
		i2c_inst_regs(5),
		i2c_inst_regs(6),
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_shअगरt i2c_shअगरts = अणु
		I2C_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_mask i2c_masks = अणु
		I2C_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल काष्ठा dce_i2c_hw *dcn30_i2c_hw_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_i2c_hw *dce_i2c_hw =
		kzalloc(माप(काष्ठा dce_i2c_hw), GFP_KERNEL);

	अगर (!dce_i2c_hw)
		वापस शून्य;

	dcn2_i2c_hw_स्थिरruct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_regs[inst], &i2c_shअगरts, &i2c_masks);

	वापस dce_i2c_hw;
पूर्ण

अटल काष्ठा mpc *dcn30_mpc_create(
		काष्ठा dc_context *ctx,
		पूर्णांक num_mpcc,
		पूर्णांक num_rmu)
अणु
	काष्ठा dcn30_mpc *mpc30 = kzalloc(माप(काष्ठा dcn30_mpc),
					  GFP_KERNEL);

	अगर (!mpc30)
		वापस शून्य;

	dcn30_mpc_स्थिरruct(mpc30, ctx,
			&mpc_regs,
			&mpc_shअगरt,
			&mpc_mask,
			num_mpcc,
			num_rmu);

	वापस &mpc30->base;
पूर्ण

काष्ठा hubbub *dcn30_hubbub_create(काष्ठा dc_context *ctx)
अणु
	पूर्णांक i;

	काष्ठा dcn20_hubbub *hubbub3 = kzalloc(माप(काष्ठा dcn20_hubbub),
					  GFP_KERNEL);

	अगर (!hubbub3)
		वापस शून्य;

	hubbub3_स्थिरruct(hubbub3, ctx,
			&hubbub_reg,
			&hubbub_shअगरt,
			&hubbub_mask);


	क्रम (i = 0; i < res_cap_dcn3.num_vmid; i++) अणु
		काष्ठा dcn20_vmid *vmid = &hubbub3->vmid[i];

		vmid->ctx = ctx;

		vmid->regs = &vmid_regs[i];
		vmid->shअगरts = &vmid_shअगरts;
		vmid->masks = &vmid_masks;
	पूर्ण

	वापस &hubbub3->base;
पूर्ण

अटल काष्ठा timing_generator *dcn30_timing_generator_create(
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t instance)
अणु
	काष्ठा optc *tgn10 =
		kzalloc(माप(काष्ठा optc), GFP_KERNEL);

	अगर (!tgn10)
		वापस शून्य;

	tgn10->base.inst = instance;
	tgn10->base.ctx = ctx;

	tgn10->tg_regs = &optc_regs[instance];
	tgn10->tg_shअगरt = &optc_shअगरt;
	tgn10->tg_mask = &optc_mask;

	dcn30_timing_generator_init(tgn10);

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

अटल काष्ठा link_encoder *dcn30_link_encoder_create(
	स्थिर काष्ठा encoder_init_data *enc_init_data)
अणु
	काष्ठा dcn20_link_encoder *enc20 =
		kzalloc(माप(काष्ठा dcn20_link_encoder), GFP_KERNEL);

	अगर (!enc20)
		वापस शून्य;

	dcn30_link_encoder_स्थिरruct(enc20,
			enc_init_data,
			&link_enc_feature,
			&link_enc_regs[enc_init_data->transmitter],
			&link_enc_aux_regs[enc_init_data->channel - 1],
			&link_enc_hpd_regs[enc_init_data->hpd_source],
			&le_shअगरt,
			&le_mask);

	वापस &enc20->enc10.base;
पूर्ण

अटल काष्ठा panel_cntl *dcn30_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
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

अटल व्योम पढ़ो_dce_straps(
	काष्ठा dc_context *ctx,
	काष्ठा resource_straps *straps)
अणु
	generic_reg_get(ctx, mmDC_PINSTRAPS + BASE(mmDC_PINSTRAPS_BASE_IDX),
		FN(DC_PINSTRAPS, DC_PINSTRAPS_AUDIO), &straps->dc_pinstraps_audio);

पूर्ण

अटल काष्ठा audio *dcn30_create_audio(
		काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst,
			&audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

अटल काष्ठा vpg *dcn30_vpg_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn30_vpg *vpg3 = kzalloc(माप(काष्ठा dcn30_vpg), GFP_KERNEL);

	अगर (!vpg3)
		वापस शून्य;

	vpg3_स्थिरruct(vpg3, ctx, inst,
			&vpg_regs[inst],
			&vpg_shअगरt,
			&vpg_mask);

	वापस &vpg3->base;
पूर्ण

अटल काष्ठा afmt *dcn30_afmt_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn30_afmt *afmt3 = kzalloc(माप(काष्ठा dcn30_afmt), GFP_KERNEL);

	अगर (!afmt3)
		वापस शून्य;

	afmt3_स्थिरruct(afmt3, ctx, inst,
			&afmt_regs[inst],
			&afmt_shअगरt,
			&afmt_mask);

	वापस &afmt3->base;
पूर्ण

काष्ठा stream_encoder *dcn30_stream_encoder_create(
	क्रमागत engine_id eng_id,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn10_stream_encoder *enc1;
	काष्ठा vpg *vpg;
	काष्ठा afmt *afmt;
	पूर्णांक vpg_inst;
	पूर्णांक afmt_inst;

	/* Mapping of VPG, AFMT, DME रेजिस्टर blocks to DIO block instance */
	अगर (eng_id <= ENGINE_ID_DIGF) अणु
		vpg_inst = eng_id;
		afmt_inst = eng_id;
	पूर्ण अन्यथा
		वापस शून्य;

	enc1 = kzalloc(माप(काष्ठा dcn10_stream_encoder), GFP_KERNEL);
	vpg = dcn30_vpg_create(ctx, vpg_inst);
	afmt = dcn30_afmt_create(ctx, afmt_inst);

	अगर (!enc1 || !vpg || !afmt)
		वापस शून्य;

	dcn30_dio_stream_encoder_स्थिरruct(enc1, ctx, ctx->dc_bios,
					eng_id, vpg, afmt,
					&stream_enc_regs[eng_id],
					&se_shअगरt, &se_mask);

	वापस &enc1->base;
पूर्ण

काष्ठा dce_hwseq *dcn30_hwseq_create(
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
	.create_audio = dcn30_create_audio,
	.create_stream_encoder = dcn30_stream_encoder_create,
	.create_hwseq = dcn30_hwseq_create,
पूर्ण;

अटल स्थिर काष्ठा resource_create_funcs res_create_maximus_funcs = अणु
	.पढ़ो_dce_straps = शून्य,
	.create_audio = शून्य,
	.create_stream_encoder = शून्य,
	.create_hwseq = dcn30_hwseq_create,
पूर्ण;

अटल व्योम dcn30_resource_deकाष्ठा(काष्ठा dcn30_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pool->base.stream_enc_count; i++) अणु
		अगर (pool->base.stream_enc[i] != शून्य) अणु
			अगर (pool->base.stream_enc[i]->vpg != शून्य) अणु
				kमुक्त(DCN30_VPG_FROM_VPG(pool->base.stream_enc[i]->vpg));
				pool->base.stream_enc[i]->vpg = शून्य;
			पूर्ण
			अगर (pool->base.stream_enc[i]->afmt != शून्य) अणु
				kमुक्त(DCN30_AFMT_FROM_AFMT(pool->base.stream_enc[i]->afmt));
				pool->base.stream_enc[i]->afmt = शून्य;
			पूर्ण
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
			dcn30_dpp_destroy(&pool->base.dpps[i]);

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
			kमुक्त(TO_DCN30_DWBC(pool->base.dwbc[i]));
			pool->base.dwbc[i] = शून्य;
		पूर्ण
		अगर (pool->base.mcअगर_wb[i] != शून्य) अणु
			kमुक्त(TO_DCN30_MMHUBBUB(pool->base.mcअगर_wb[i]));
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

	क्रम (i = 0; i < pool->base.res_cap->num_mpc_3dlut; i++) अणु
		अगर (pool->base.mpc_lut[i] != शून्य) अणु
			dc_3dlut_func_release(pool->base.mpc_lut[i]);
			pool->base.mpc_lut[i] = शून्य;
		पूर्ण
		अगर (pool->base.mpc_shaper[i] != शून्य) अणु
			dc_transfer_func_release(pool->base.mpc_shaper[i]);
			pool->base.mpc_shaper[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (pool->base.dp_घड़ी_source != शून्य) अणु
		dcn20_घड़ी_source_destroy(&pool->base.dp_घड़ी_source);
		pool->base.dp_घड़ी_source = शून्य;
	पूर्ण

	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		अगर (pool->base.multiple_abms[i] != शून्य)
			dce_abm_destroy(&pool->base.multiple_abms[i]);
	पूर्ण

	अगर (pool->base.psr != शून्य)
		dmub_psr_destroy(&pool->base.psr);

	अगर (pool->base.dccg != शून्य)
		dcn_dccg_destroy(&pool->base.dccg);

	अगर (pool->base.oem_device != शून्य)
		dal_ddc_service_destroy(&pool->base.oem_device);
पूर्ण

अटल काष्ठा hubp *dcn30_hubp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_hubp *hubp2 =
		kzalloc(माप(काष्ठा dcn20_hubp), GFP_KERNEL);

	अगर (!hubp2)
		वापस शून्य;

	अगर (hubp3_स्थिरruct(hubp2, ctx, inst,
			&hubp_regs[inst], &hubp_shअगरt, &hubp_mask))
		वापस &hubp2->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(hubp2);
	वापस शून्य;
पूर्ण

अटल bool dcn30_dwbc_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	uपूर्णांक32_t pipe_count = pool->res_cap->num_dwb;

	क्रम (i = 0; i < pipe_count; i++) अणु
		काष्ठा dcn30_dwbc *dwbc30 = kzalloc(माप(काष्ठा dcn30_dwbc),
						    GFP_KERNEL);

		अगर (!dwbc30) अणु
			dm_error("DC: failed to create dwbc30!\n");
			वापस false;
		पूर्ण

		dcn30_dwbc_स्थिरruct(dwbc30, ctx,
				&dwbc30_regs[i],
				&dwbc30_shअगरt,
				&dwbc30_mask,
				i);

		pool->dwbc[i] = &dwbc30->base;
	पूर्ण
	वापस true;
पूर्ण

अटल bool dcn30_mmhubbub_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	uपूर्णांक32_t pipe_count = pool->res_cap->num_dwb;

	क्रम (i = 0; i < pipe_count; i++) अणु
		काष्ठा dcn30_mmhubbub *mcअगर_wb30 = kzalloc(माप(काष्ठा dcn30_mmhubbub),
						    GFP_KERNEL);

		अगर (!mcअगर_wb30) अणु
			dm_error("DC: failed to create mcif_wb30!\n");
			वापस false;
		पूर्ण

		dcn30_mmhubbub_स्थिरruct(mcअगर_wb30, ctx,
				&mcअगर_wb30_regs[i],
				&mcअगर_wb30_shअगरt,
				&mcअगर_wb30_mask,
				i);

		pool->mcअगर_wb[i] = &mcअगर_wb30->base;
	पूर्ण
	वापस true;
पूर्ण

अटल काष्ठा display_stream_compressor *dcn30_dsc_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_dsc *dsc =
		kzalloc(माप(काष्ठा dcn20_dsc), GFP_KERNEL);

	अगर (!dsc) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dsc2_स्थिरruct(dsc, ctx, inst, &dsc_regs[inst], &dsc_shअगरt, &dsc_mask);
	वापस &dsc->base;
पूर्ण

क्रमागत dc_status dcn30_add_stream_to_ctx(काष्ठा dc *dc, काष्ठा dc_state *new_ctx, काष्ठा dc_stream_state *dc_stream)
अणु

	वापस dcn20_add_stream_to_ctx(dc, new_ctx, dc_stream);
पूर्ण

अटल व्योम dcn30_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dcn30_resource_pool *dcn30_pool = TO_DCN30_RES_POOL(*pool);

	dcn30_resource_deकाष्ठा(dcn30_pool);
	kमुक्त(dcn30_pool);
	*pool = शून्य;
पूर्ण

अटल काष्ठा घड़ी_source *dcn30_घड़ी_source_create(
		काष्ठा dc_context *ctx,
		काष्ठा dc_bios *bios,
		क्रमागत घड़ी_source_id id,
		स्थिर काष्ठा dce110_clk_src_regs *regs,
		bool dp_clk_src)
अणु
	काष्ठा dce110_clk_src *clk_src =
		kzalloc(माप(काष्ठा dce110_clk_src), GFP_KERNEL);

	अगर (!clk_src)
		वापस शून्य;

	अगर (dcn3_clk_src_स्थिरruct(clk_src, ctx, bios, id,
			regs, &cs_shअगरt, &cs_mask)) अणु
		clk_src->base.dp_clk_src = dp_clk_src;
		वापस &clk_src->base;
	पूर्ण

	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

पूर्णांक dcn30_populate_dml_pipes_from_context(
	काष्ठा dc *dc, काष्ठा dc_state *context,
	display_e2e_pipe_params_st *pipes,
	bool fast_validate)
अणु
	पूर्णांक i, pipe_cnt;
	काष्ठा resource_context *res_ctx = &context->res_ctx;

	dcn20_populate_dml_pipes_from_context(dc, context, pipes, fast_validate);

	क्रम (i = 0, pipe_cnt = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (!res_ctx->pipe_ctx[i].stream)
			जारी;

		pipes[pipe_cnt++].pipe.scale_ratio_depth.lb_depth =
			dm_lb_16;
	पूर्ण

	वापस pipe_cnt;
पूर्ण

व्योम dcn30_populate_dml_ग_लिखोback_from_context(
	काष्ठा dc *dc, काष्ठा resource_context *res_ctx, display_e2e_pipe_params_st *pipes)
अणु
	पूर्णांक pipe_cnt, i, j;
	द्विगुन max_calc_ग_लिखोback_dispclk;
	द्विगुन ग_लिखोback_dispclk;
	काष्ठा ग_लिखोback_st करोut_wb;

	क्रम (i = 0, pipe_cnt = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा dc_stream_state *stream = res_ctx->pipe_ctx[i].stream;

		अगर (!stream)
			जारी;
		max_calc_ग_लिखोback_dispclk = 0;

		/* Set ग_लिखोback inक्रमmation */
		pipes[pipe_cnt].करोut.wb_enable = 0;
		pipes[pipe_cnt].करोut.num_active_wb = 0;
		क्रम (j = 0; j < stream->num_wb_info; j++) अणु
			काष्ठा dc_ग_लिखोback_info *wb_info = &stream->ग_लिखोback_info[j];

			अगर (wb_info->wb_enabled && wb_info->ग_लिखोback_source_plane &&
					(wb_info->ग_लिखोback_source_plane == res_ctx->pipe_ctx[i].plane_state)) अणु
				pipes[pipe_cnt].करोut.wb_enable = 1;
				pipes[pipe_cnt].करोut.num_active_wb++;
				करोut_wb.wb_src_height = wb_info->dwb_params.cnv_params.crop_en ?
					wb_info->dwb_params.cnv_params.crop_height :
					wb_info->dwb_params.cnv_params.src_height;
				करोut_wb.wb_src_width = wb_info->dwb_params.cnv_params.crop_en ?
					wb_info->dwb_params.cnv_params.crop_width :
					wb_info->dwb_params.cnv_params.src_width;
				करोut_wb.wb_dst_width = wb_info->dwb_params.dest_width;
				करोut_wb.wb_dst_height = wb_info->dwb_params.dest_height;

				/* For IP that करोesn't support WB scaling, set h/v taps to 1 to aव्योम DML validation failure */
				अगर (dc->dml.ip.ग_लिखोback_max_hscl_taps > 1) अणु
					करोut_wb.wb_htaps_luma = wb_info->dwb_params.scaler_taps.h_taps;
					करोut_wb.wb_vtaps_luma = wb_info->dwb_params.scaler_taps.v_taps;
				पूर्ण अन्यथा अणु
					करोut_wb.wb_htaps_luma = 1;
					करोut_wb.wb_vtaps_luma = 1;
				पूर्ण
				करोut_wb.wb_htaps_chroma = 0;
				करोut_wb.wb_vtaps_chroma = 0;
				करोut_wb.wb_hratio = wb_info->dwb_params.cnv_params.crop_en ?
					(द्विगुन)wb_info->dwb_params.cnv_params.crop_width /
						(द्विगुन)wb_info->dwb_params.dest_width :
					(द्विगुन)wb_info->dwb_params.cnv_params.src_width /
						(द्विगुन)wb_info->dwb_params.dest_width;
				करोut_wb.wb_vratio = wb_info->dwb_params.cnv_params.crop_en ?
					(द्विगुन)wb_info->dwb_params.cnv_params.crop_height /
						(द्विगुन)wb_info->dwb_params.dest_height :
					(द्विगुन)wb_info->dwb_params.cnv_params.src_height /
						(द्विगुन)wb_info->dwb_params.dest_height;
				अगर (wb_info->dwb_params.cnv_params.fc_out_क्रमmat == DWB_OUT_FORMAT_64BPP_ARGB ||
					wb_info->dwb_params.cnv_params.fc_out_क्रमmat == DWB_OUT_FORMAT_64BPP_RGBA)
					करोut_wb.wb_pixel_क्रमmat = dm_444_64;
				अन्यथा
					करोut_wb.wb_pixel_क्रमmat = dm_444_32;

				/* Workaround क्रम हालs where multiple ग_लिखोbacks are connected to same plane
				 * In which हाल, need to compute worst हाल and set the associated ग_लिखोback parameters
				 * This workaround is necessary due to DML computation assuming only 1 set of ग_लिखोback
				 * parameters per pipe
				 */
				ग_लिखोback_dispclk = dml30_CalculateWriteBackDISPCLK(
						करोut_wb.wb_pixel_क्रमmat,
						pipes[pipe_cnt].pipe.dest.pixel_rate_mhz,
						करोut_wb.wb_hratio,
						करोut_wb.wb_vratio,
						करोut_wb.wb_htaps_luma,
						करोut_wb.wb_vtaps_luma,
						करोut_wb.wb_src_width,
						करोut_wb.wb_dst_width,
						pipes[pipe_cnt].pipe.dest.htotal,
						dc->current_state->bw_ctx.dml.ip.ग_लिखोback_line_buffer_buffer_size);

				अगर (ग_लिखोback_dispclk > max_calc_ग_लिखोback_dispclk) अणु
					max_calc_ग_लिखोback_dispclk = ग_लिखोback_dispclk;
					pipes[pipe_cnt].करोut.wb = करोut_wb;
				पूर्ण
			पूर्ण
		पूर्ण

		pipe_cnt++;
	पूर्ण

पूर्ण

अचिन्हित पूर्णांक dcn30_calc_max_scaled_समय(
		अचिन्हित पूर्णांक समय_per_pixel,
		क्रमागत mmhubbub_wbअगर_mode mode,
		अचिन्हित पूर्णांक urgent_watermark)
अणु
	अचिन्हित पूर्णांक समय_per_byte = 0;
	अचिन्हित पूर्णांक total_मुक्त_entry = 0xb40;
	अचिन्हित पूर्णांक buf_lh_capability;
	अचिन्हित पूर्णांक max_scaled_समय;

	अगर (mode == PACKED_444) /* packed mode 32 bpp */
		समय_per_byte = समय_per_pixel/4;
	अन्यथा अगर (mode == PACKED_444_FP16) /* packed mode 64 bpp */
		समय_per_byte = समय_per_pixel/8;

	अगर (समय_per_byte == 0)
		समय_per_byte = 1;

	buf_lh_capability = (total_मुक्त_entry*समय_per_byte*32) >> 6; /* समय_per_byte is in u6.6*/
	max_scaled_समय   = buf_lh_capability - urgent_watermark;
	वापस max_scaled_समय;
पूर्ण

व्योम dcn30_set_mcअगर_arb_params(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt)
अणु
	क्रमागत mmhubbub_wbअगर_mode wbअगर_mode;
	काष्ठा display_mode_lib *dml = &context->bw_ctx.dml;
	काष्ठा mcअगर_arb_params *wb_arb_params;
	पूर्णांक i, j, k, dwb_pipe;

	/* Writeback MCIF_WB arbitration parameters */
	dwb_pipe = 0;
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु

		अगर (!context->res_ctx.pipe_ctx[i].stream)
			जारी;

		क्रम (j = 0; j < MAX_DWB_PIPES; j++) अणु
			काष्ठा dc_ग_लिखोback_info *ग_लिखोback_info = &context->res_ctx.pipe_ctx[i].stream->ग_लिखोback_info[j];

			अगर (ग_लिखोback_info->wb_enabled == false)
				जारी;

			//wb_arb_params = &context->res_ctx.pipe_ctx[i].stream->ग_लिखोback_info[j].mcअगर_arb_params;
			wb_arb_params = &context->bw_ctx.bw.dcn.bw_ग_लिखोback.mcअगर_wb_arb[dwb_pipe];

			अगर (ग_लिखोback_info->dwb_params.cnv_params.fc_out_क्रमmat == DWB_OUT_FORMAT_64BPP_ARGB ||
				ग_लिखोback_info->dwb_params.cnv_params.fc_out_क्रमmat == DWB_OUT_FORMAT_64BPP_RGBA)
				wbअगर_mode = PACKED_444_FP16;
			अन्यथा
				wbअगर_mode = PACKED_444;

			क्रम (k = 0; k < माप(wb_arb_params->cli_watermark)/माप(wb_arb_params->cli_watermark[0]); k++) अणु
				wb_arb_params->cli_watermark[k] = get_wm_ग_लिखोback_urgent(dml, pipes, pipe_cnt) * 1000;
				wb_arb_params->pstate_watermark[k] = get_wm_ग_लिखोback_dram_घड़ी_change(dml, pipes, pipe_cnt) * 1000;
			पूर्ण
			wb_arb_params->समय_per_pixel = (1000000 << 6) / context->res_ctx.pipe_ctx[i].stream->phy_pix_clk; /* समय_per_pixel should be in u6.6 क्रमmat */
			wb_arb_params->slice_lines = 32;
			wb_arb_params->arbitration_slice = 2; /* irrelevant since there is no YUV output */
			wb_arb_params->max_scaled_समय = dcn30_calc_max_scaled_समय(wb_arb_params->समय_per_pixel,
					wbअगर_mode,
					wb_arb_params->cli_watermark[0]); /* assume 4 watermark sets have the same value */
			wb_arb_params->dram_speed_change_duration = dml->vba.WritebackAllowDRAMClockChangeEndPosition[j] * pipes[0].clks_cfg.refclk_mhz; /* num_घड़ी_cycles = us * MHz */

			dwb_pipe++;

			अगर (dwb_pipe >= MAX_DWB_PIPES)
				वापस;
		पूर्ण
		अगर (dwb_pipe >= MAX_DWB_PIPES)
			वापस;
	पूर्ण

पूर्ण

अटल काष्ठा dc_cap_funcs cap_funcs = अणु
	.get_dcc_compression_cap = dcn20_get_dcc_compression_cap
पूर्ण;

bool dcn30_acquire_post_bldn_3dlut(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		पूर्णांक mpcc_id,
		काष्ठा dc_3dlut **lut,
		काष्ठा dc_transfer_func **shaper)
अणु
	पूर्णांक i;
	bool ret = false;
	जोड़ dc_3dlut_state *state;

	ASSERT(*lut == शून्य && *shaper == शून्य);
	*lut = शून्य;
	*shaper = शून्य;

	क्रम (i = 0; i < pool->res_cap->num_mpc_3dlut; i++) अणु
		अगर (!res_ctx->is_mpc_3dlut_acquired[i]) अणु
			*lut = pool->mpc_lut[i];
			*shaper = pool->mpc_shaper[i];
			state = &pool->mpc_lut[i]->state;
			res_ctx->is_mpc_3dlut_acquired[i] = true;
			state->bits.rmu_idx_valid = 1;
			state->bits.rmu_mux_num = i;
			अगर (state->bits.rmu_mux_num == 0)
				state->bits.mpc_rmu0_mux = mpcc_id;
			अन्यथा अगर (state->bits.rmu_mux_num == 1)
				state->bits.mpc_rmu1_mux = mpcc_id;
			अन्यथा अगर (state->bits.rmu_mux_num == 2)
				state->bits.mpc_rmu2_mux = mpcc_id;
			ret = true;
			अवरोध;
			पूर्ण
		पूर्ण
	वापस ret;
पूर्ण

bool dcn30_release_post_bldn_3dlut(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_3dlut **lut,
		काष्ठा dc_transfer_func **shaper)
अणु
	पूर्णांक i;
	bool ret = false;

	क्रम (i = 0; i < pool->res_cap->num_mpc_3dlut; i++) अणु
		अगर (pool->mpc_lut[i] == *lut && pool->mpc_shaper[i] == *shaper) अणु
			res_ctx->is_mpc_3dlut_acquired[i] = false;
			pool->mpc_lut[i]->state.raw = 0;
			*lut = शून्य;
			*shaper = शून्य;
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा fixed16_to_द्विगुन(x) (((द्विगुन) x) / ((द्विगुन) (1 << 16)))
#घोषणा fixed16_to_द्विगुन_to_cpu(x) fixed16_to_द्विगुन(le32_to_cpu(x))

अटल bool is_soc_bounding_box_valid(काष्ठा dc *dc)
अणु
	uपूर्णांक32_t hw_पूर्णांकernal_rev = dc->ctx->asic_id.hw_पूर्णांकernal_rev;

	अगर (ASICREV_IS_SIENNA_CICHLID_P(hw_पूर्णांकernal_rev))
		वापस true;

	वापस false;
पूर्ण

अटल bool init_soc_bounding_box(काष्ठा dc *dc,
				  काष्ठा dcn30_resource_pool *pool)
अणु
	काष्ठा _vcs_dpi_soc_bounding_box_st *loaded_bb = &dcn3_0_soc;
	काष्ठा _vcs_dpi_ip_params_st *loaded_ip = &dcn3_0_ip;

	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (!is_soc_bounding_box_valid(dc)) अणु
		DC_LOG_ERROR("%s: not valid soc bounding box/n", __func__);
		वापस false;
	पूर्ण

	loaded_ip->max_num_otg = pool->base.res_cap->num_timing_generator;
	loaded_ip->max_num_dpp = pool->base.pipe_count;
	loaded_ip->clamp_min_dcfclk = dc->config.clamp_min_dcfclk;
	dcn20_patch_bounding_box(dc, loaded_bb);

	अगर (dc->ctx->dc_bios->funcs->get_soc_bb_info) अणु
		काष्ठा bp_soc_bb_info bb_info = अणु0पूर्ण;

		अगर (dc->ctx->dc_bios->funcs->get_soc_bb_info(dc->ctx->dc_bios, &bb_info) == BP_RESULT_OK) अणु
			अगर (bb_info.dram_घड़ी_change_latency_100ns > 0)
				dcn3_0_soc.dram_घड़ी_change_latency_us = bb_info.dram_घड़ी_change_latency_100ns * 10;

			अगर (bb_info.dram_sr_enter_निकास_latency_100ns > 0)
				dcn3_0_soc.sr_enter_plus_निकास_समय_us = bb_info.dram_sr_enter_निकास_latency_100ns * 10;

			अगर (bb_info.dram_sr_निकास_latency_100ns > 0)
				dcn3_0_soc.sr_निकास_समय_us = bb_info.dram_sr_निकास_latency_100ns * 10;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल bool dcn30_split_stream_क्रम_mpc_or_odm(
		स्थिर काष्ठा dc *dc,
		काष्ठा resource_context *res_ctx,
		काष्ठा pipe_ctx *pri_pipe,
		काष्ठा pipe_ctx *sec_pipe,
		bool odm)
अणु
	पूर्णांक pipe_idx = sec_pipe->pipe_idx;
	स्थिर काष्ठा resource_pool *pool = dc->res_pool;

	*sec_pipe = *pri_pipe;

	sec_pipe->pipe_idx = pipe_idx;
	sec_pipe->plane_res.mi = pool->mis[pipe_idx];
	sec_pipe->plane_res.hubp = pool->hubps[pipe_idx];
	sec_pipe->plane_res.ipp = pool->ipps[pipe_idx];
	sec_pipe->plane_res.xfm = pool->transक्रमms[pipe_idx];
	sec_pipe->plane_res.dpp = pool->dpps[pipe_idx];
	sec_pipe->plane_res.mpcc_inst = pool->dpps[pipe_idx]->inst;
	sec_pipe->stream_res.dsc = शून्य;
	अगर (odm) अणु
		अगर (pri_pipe->next_odm_pipe) अणु
			ASSERT(pri_pipe->next_odm_pipe != sec_pipe);
			sec_pipe->next_odm_pipe = pri_pipe->next_odm_pipe;
			sec_pipe->next_odm_pipe->prev_odm_pipe = sec_pipe;
		पूर्ण
		अगर (pri_pipe->top_pipe && pri_pipe->top_pipe->next_odm_pipe) अणु
			pri_pipe->top_pipe->next_odm_pipe->bottom_pipe = sec_pipe;
			sec_pipe->top_pipe = pri_pipe->top_pipe->next_odm_pipe;
		पूर्ण
		अगर (pri_pipe->bottom_pipe && pri_pipe->bottom_pipe->next_odm_pipe) अणु
			pri_pipe->bottom_pipe->next_odm_pipe->top_pipe = sec_pipe;
			sec_pipe->bottom_pipe = pri_pipe->bottom_pipe->next_odm_pipe;
		पूर्ण
		pri_pipe->next_odm_pipe = sec_pipe;
		sec_pipe->prev_odm_pipe = pri_pipe;
		ASSERT(sec_pipe->top_pipe == शून्य);

		अगर (!sec_pipe->top_pipe)
			sec_pipe->stream_res.opp = pool->opps[pipe_idx];
		अन्यथा
			sec_pipe->stream_res.opp = sec_pipe->top_pipe->stream_res.opp;
		अगर (sec_pipe->stream->timing.flags.DSC == 1) अणु
			dcn20_acquire_dsc(dc, res_ctx, &sec_pipe->stream_res.dsc, pipe_idx);
			ASSERT(sec_pipe->stream_res.dsc);
			अगर (sec_pipe->stream_res.dsc == शून्य)
				वापस false;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (pri_pipe->bottom_pipe) अणु
			ASSERT(pri_pipe->bottom_pipe != sec_pipe);
			sec_pipe->bottom_pipe = pri_pipe->bottom_pipe;
			sec_pipe->bottom_pipe->top_pipe = sec_pipe;
		पूर्ण
		pri_pipe->bottom_pipe = sec_pipe;
		sec_pipe->top_pipe = pri_pipe;

		ASSERT(pri_pipe->plane_state);
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा pipe_ctx *dcn30_find_split_pipe(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		पूर्णांक old_index)
अणु
	काष्ठा pipe_ctx *pipe = शून्य;
	पूर्णांक i;

	अगर (old_index >= 0 && context->res_ctx.pipe_ctx[old_index].stream == शून्य) अणु
		pipe = &context->res_ctx.pipe_ctx[old_index];
		pipe->pipe_idx = old_index;
	पूर्ण

	अगर (!pipe)
		क्रम (i = dc->res_pool->pipe_count - 1; i >= 0; i--) अणु
			अगर (dc->current_state->res_ctx.pipe_ctx[i].top_pipe == शून्य
					&& dc->current_state->res_ctx.pipe_ctx[i].prev_odm_pipe == शून्य) अणु
				अगर (context->res_ctx.pipe_ctx[i].stream == शून्य) अणु
					pipe = &context->res_ctx.pipe_ctx[i];
					pipe->pipe_idx = i;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

	/*
	 * May need to fix pipes getting tossed from 1 opp to another on flip
	 * Add क्रम debugging transient underflow during topology updates:
	 * ASSERT(pipe);
	 */
	अगर (!pipe)
		क्रम (i = dc->res_pool->pipe_count - 1; i >= 0; i--) अणु
			अगर (context->res_ctx.pipe_ctx[i].stream == शून्य) अणु
				pipe = &context->res_ctx.pipe_ctx[i];
				pipe->pipe_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण

	वापस pipe;
पूर्ण

अटल noअंतरभूत bool dcn30_पूर्णांकernal_validate_bw(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक *pipe_cnt_out,
		पूर्णांक *vlevel_out,
		bool fast_validate)
अणु
	bool out = false;
	bool repopulate_pipes = false;
	पूर्णांक split[MAX_PIPES] = अणु 0 पूर्ण;
	bool merge[MAX_PIPES] = अणु false पूर्ण;
	bool newly_split[MAX_PIPES] = अणु false पूर्ण;
	पूर्णांक pipe_cnt, i, pipe_idx, vlevel;
	काष्ठा vba_vars_st *vba = &context->bw_ctx.dml.vba;

	ASSERT(pipes);
	अगर (!pipes)
		वापस false;

	dc->res_pool->funcs->update_soc_क्रम_wm_a(dc, context);
	pipe_cnt = dc->res_pool->funcs->populate_dml_pipes(dc, context, pipes, fast_validate);

	DC_FP_START();
	अगर (!pipe_cnt) अणु
		out = true;
		जाओ validate_out;
	पूर्ण

	dml_log_pipe_params(&context->bw_ctx.dml, pipes, pipe_cnt);

	अगर (!fast_validate) अणु
		/*
		 * DML favors voltage over p-state, but we're more पूर्णांकerested in
		 * supporting p-state over voltage. We can't support p-state in
		 * prefetch mode > 0 so try capping the prefetch mode to start.
		 */
		context->bw_ctx.dml.soc.allow_dram_self_refresh_or_dram_घड़ी_change_in_vblank =
			dm_allow_self_refresh_and_mclk_चयन;
		vlevel = dml_get_voltage_level(&context->bw_ctx.dml, pipes, pipe_cnt);
		/* This may adjust vlevel and maxMpcComb */
		अगर (vlevel < context->bw_ctx.dml.soc.num_states)
			vlevel = dcn20_validate_apply_pipe_split_flags(dc, context, vlevel, split, merge);
	पूर्ण
	अगर (fast_validate || vlevel == context->bw_ctx.dml.soc.num_states ||
			vba->DRAMClockChangeSupport[vlevel][vba->maxMpcComb] == dm_dram_घड़ी_change_unsupported) अणु
		/*
		 * If mode is unsupported or there's still no p-state support then
		 * fall back to favoring voltage.
		 *
		 * We करोn't actually support prefetch mode 2, so require that we
		 * at least support prefetch mode 1.
		 */
		context->bw_ctx.dml.soc.allow_dram_self_refresh_or_dram_घड़ी_change_in_vblank =
			dm_allow_self_refresh;

		vlevel = dml_get_voltage_level(&context->bw_ctx.dml, pipes, pipe_cnt);
		अगर (vlevel < context->bw_ctx.dml.soc.num_states) अणु
			स_रखो(split, 0, माप(split));
			स_रखो(merge, 0, माप(merge));
			vlevel = dcn20_validate_apply_pipe_split_flags(dc, context, vlevel, split, merge);
		पूर्ण
	पूर्ण

	dml_log_mode_support_params(&context->bw_ctx.dml);

	अगर (vlevel == context->bw_ctx.dml.soc.num_states)
		जाओ validate_fail;

	क्रम (i = 0, pipe_idx = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *mpo_pipe = pipe->bottom_pipe;

		अगर (!pipe->stream)
			जारी;

		/* We only support full screen mpo with ODM */
		अगर (vba->ODMCombineEnabled[vba->pipe_plane[pipe_idx]] != dm_odm_combine_mode_disabled
				&& pipe->plane_state && mpo_pipe
				&& स_भेद(&mpo_pipe->plane_res.scl_data.recout,
						&pipe->plane_res.scl_data.recout,
						माप(काष्ठा rect)) != 0) अणु
			ASSERT(mpo_pipe->plane_state != pipe->plane_state);
			जाओ validate_fail;
		पूर्ण
		pipe_idx++;
	पूर्ण

	/* merge pipes अगर necessary */
	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		/*skip pipes that करोn't need merging*/
		अगर (!merge[i])
			जारी;

		/* अगर ODM merge we ignore mpc tree, mpo pipes will have their own flags */
		अगर (pipe->prev_odm_pipe) अणु
			/*split off odm pipe*/
			pipe->prev_odm_pipe->next_odm_pipe = pipe->next_odm_pipe;
			अगर (pipe->next_odm_pipe)
				pipe->next_odm_pipe->prev_odm_pipe = pipe->prev_odm_pipe;

			pipe->bottom_pipe = शून्य;
			pipe->next_odm_pipe = शून्य;
			pipe->plane_state = शून्य;
			pipe->stream = शून्य;
			pipe->top_pipe = शून्य;
			pipe->prev_odm_pipe = शून्य;
			अगर (pipe->stream_res.dsc)
				dcn20_release_dsc(&context->res_ctx, dc->res_pool, &pipe->stream_res.dsc);
			स_रखो(&pipe->plane_res, 0, माप(pipe->plane_res));
			स_रखो(&pipe->stream_res, 0, माप(pipe->stream_res));
			repopulate_pipes = true;
		पूर्ण अन्यथा अगर (pipe->top_pipe && pipe->top_pipe->plane_state == pipe->plane_state) अणु
			काष्ठा pipe_ctx *top_pipe = pipe->top_pipe;
			काष्ठा pipe_ctx *bottom_pipe = pipe->bottom_pipe;

			top_pipe->bottom_pipe = bottom_pipe;
			अगर (bottom_pipe)
				bottom_pipe->top_pipe = top_pipe;

			pipe->top_pipe = शून्य;
			pipe->bottom_pipe = शून्य;
			pipe->plane_state = शून्य;
			pipe->stream = शून्य;
			स_रखो(&pipe->plane_res, 0, माप(pipe->plane_res));
			स_रखो(&pipe->stream_res, 0, माप(pipe->stream_res));
			repopulate_pipes = true;
		पूर्ण अन्यथा
			ASSERT(0); /* Should never try to merge master pipe */

	पूर्ण

	क्रम (i = 0, pipe_idx = -1; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *old_pipe = &dc->current_state->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *hsplit_pipe = शून्य;
		bool odm;
		पूर्णांक old_index = -1;

		अगर (!pipe->stream || newly_split[i])
			जारी;

		pipe_idx++;
		odm = vba->ODMCombineEnabled[vba->pipe_plane[pipe_idx]] != dm_odm_combine_mode_disabled;

		अगर (!pipe->plane_state && !odm)
			जारी;

		अगर (split[i]) अणु
			अगर (odm) अणु
				अगर (split[i] == 4 && old_pipe->next_odm_pipe && old_pipe->next_odm_pipe->next_odm_pipe)
					old_index = old_pipe->next_odm_pipe->next_odm_pipe->pipe_idx;
				अन्यथा अगर (old_pipe->next_odm_pipe)
					old_index = old_pipe->next_odm_pipe->pipe_idx;
			पूर्ण अन्यथा अणु
				अगर (split[i] == 4 && old_pipe->bottom_pipe && old_pipe->bottom_pipe->bottom_pipe &&
						old_pipe->bottom_pipe->bottom_pipe->plane_state == old_pipe->plane_state)
					old_index = old_pipe->bottom_pipe->bottom_pipe->pipe_idx;
				अन्यथा अगर (old_pipe->bottom_pipe &&
						old_pipe->bottom_pipe->plane_state == old_pipe->plane_state)
					old_index = old_pipe->bottom_pipe->pipe_idx;
			पूर्ण
			hsplit_pipe = dcn30_find_split_pipe(dc, context, old_index);
			ASSERT(hsplit_pipe);
			अगर (!hsplit_pipe)
				जाओ validate_fail;

			अगर (!dcn30_split_stream_क्रम_mpc_or_odm(
					dc, &context->res_ctx,
					pipe, hsplit_pipe, odm))
				जाओ validate_fail;

			newly_split[hsplit_pipe->pipe_idx] = true;
			repopulate_pipes = true;
		पूर्ण
		अगर (split[i] == 4) अणु
			काष्ठा pipe_ctx *pipe_4to1;

			अगर (odm && old_pipe->next_odm_pipe)
				old_index = old_pipe->next_odm_pipe->pipe_idx;
			अन्यथा अगर (!odm && old_pipe->bottom_pipe &&
						old_pipe->bottom_pipe->plane_state == old_pipe->plane_state)
				old_index = old_pipe->bottom_pipe->pipe_idx;
			अन्यथा
				old_index = -1;
			pipe_4to1 = dcn30_find_split_pipe(dc, context, old_index);
			ASSERT(pipe_4to1);
			अगर (!pipe_4to1)
				जाओ validate_fail;
			अगर (!dcn30_split_stream_क्रम_mpc_or_odm(
					dc, &context->res_ctx,
					pipe, pipe_4to1, odm))
				जाओ validate_fail;
			newly_split[pipe_4to1->pipe_idx] = true;

			अगर (odm && old_pipe->next_odm_pipe && old_pipe->next_odm_pipe->next_odm_pipe
					&& old_pipe->next_odm_pipe->next_odm_pipe->next_odm_pipe)
				old_index = old_pipe->next_odm_pipe->next_odm_pipe->next_odm_pipe->pipe_idx;
			अन्यथा अगर (!odm && old_pipe->bottom_pipe && old_pipe->bottom_pipe->bottom_pipe &&
					old_pipe->bottom_pipe->bottom_pipe->bottom_pipe &&
					old_pipe->bottom_pipe->bottom_pipe->bottom_pipe->plane_state == old_pipe->plane_state)
				old_index = old_pipe->bottom_pipe->bottom_pipe->bottom_pipe->pipe_idx;
			अन्यथा
				old_index = -1;
			pipe_4to1 = dcn30_find_split_pipe(dc, context, old_index);
			ASSERT(pipe_4to1);
			अगर (!pipe_4to1)
				जाओ validate_fail;
			अगर (!dcn30_split_stream_क्रम_mpc_or_odm(
					dc, &context->res_ctx,
					hsplit_pipe, pipe_4to1, odm))
				जाओ validate_fail;
			newly_split[pipe_4to1->pipe_idx] = true;
		पूर्ण
		अगर (odm)
			dcn20_build_mapped_resource(dc, context, pipe->stream);
	पूर्ण

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];

		अगर (pipe->plane_state) अणु
			अगर (!resource_build_scaling_params(pipe))
				जाओ validate_fail;
		पूर्ण
	पूर्ण

	/* Actual dsc count per stream dsc validation*/
	अगर (!dcn20_validate_dsc(dc, context)) अणु
		vba->ValidationStatus[vba->soc.num_states] = DML_FAIL_DSC_VALIDATION_FAILURE;
		जाओ validate_fail;
	पूर्ण

	अगर (repopulate_pipes)
		pipe_cnt = dc->res_pool->funcs->populate_dml_pipes(dc, context, pipes, fast_validate);
	*vlevel_out = vlevel;
	*pipe_cnt_out = pipe_cnt;

	out = true;
	जाओ validate_out;

validate_fail:
	out = false;

validate_out:
	DC_FP_END();
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
अटल noअंतरभूत व्योम dcn30_calculate_wm_and_dlg_fp(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt,
		पूर्णांक vlevel)
अणु
	पूर्णांक i, pipe_idx;
	द्विगुन dcfclk = context->bw_ctx.dml.vba.DCFCLKState[vlevel][context->bw_ctx.dml.vba.maxMpcComb];
	bool pstate_en = context->bw_ctx.dml.vba.DRAMClockChangeSupport[vlevel][context->bw_ctx.dml.vba.maxMpcComb] !=
			dm_dram_घड़ी_change_unsupported;

	अगर (context->bw_ctx.dml.soc.min_dcfclk > dcfclk)
		dcfclk = context->bw_ctx.dml.soc.min_dcfclk;

	pipes[0].clks_cfg.voltage = vlevel;
	pipes[0].clks_cfg.dcfclk_mhz = dcfclk;
	pipes[0].clks_cfg.socclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[vlevel].socclk_mhz;

	/* Set B:
	 * DCFCLK: 1GHz or min required above 1GHz
	 * FCLK/UCLK: Max
	 */
	अगर (dc->clk_mgr->bw_params->wm_table.nv_entries[WM_B].valid) अणु
		अगर (vlevel == 0) अणु
			pipes[0].clks_cfg.voltage = 1;
			pipes[0].clks_cfg.dcfclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[0].dcfclk_mhz;
		पूर्ण
		context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_B].dml_input.pstate_latency_us;
		context->bw_ctx.dml.soc.sr_enter_plus_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_B].dml_input.sr_enter_plus_निकास_समय_us;
		context->bw_ctx.dml.soc.sr_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_B].dml_input.sr_निकास_समय_us;
	पूर्ण
	context->bw_ctx.bw.dcn.watermarks.b.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.b.urgent_latency_ns = get_urgent_latency(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;

	pipes[0].clks_cfg.voltage = vlevel;
	pipes[0].clks_cfg.dcfclk_mhz = dcfclk;

	/* Set D:
	 * DCFCLK: Min Required
	 * FCLK(proportional to UCLK): 1GHz or Max
	 * MALL stutter, sr_enter_निकास = 4, sr_निकास = 2us
	 */
	/*
	अगर (dc->clk_mgr->bw_params->wm_table.nv_entries[WM_D].valid) अणु
		context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_D].dml_input.pstate_latency_us;
		context->bw_ctx.dml.soc.sr_enter_plus_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_D].dml_input.sr_enter_plus_निकास_समय_us;
		context->bw_ctx.dml.soc.sr_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_D].dml_input.sr_निकास_समय_us;
	पूर्ण
	context->bw_ctx.bw.dcn.watermarks.d.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.d.urgent_latency_ns = get_urgent_latency(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	*/

	/* Set C:
	 * DCFCLK: Min Required
	 * FCLK(proportional to UCLK): 1GHz or Max
	 * pstate latency overridden to 5us
	 */
	अगर (dc->clk_mgr->bw_params->wm_table.nv_entries[WM_C].valid) अणु
		अचिन्हित पूर्णांक min_dram_speed_mts = context->bw_ctx.dml.vba.DRAMSpeed;
		अचिन्हित पूर्णांक min_dram_speed_mts_margin = 160;

		अगर (context->bw_ctx.dml.vba.DRAMClockChangeSupport[vlevel][context->bw_ctx.dml.vba.maxMpcComb] == dm_dram_घड़ी_change_unsupported)
			min_dram_speed_mts = dc->clk_mgr->bw_params->clk_table.entries[dc->clk_mgr->bw_params->clk_table.num_entries - 1].memclk_mhz * 16;

		/* find largest table entry that is lower than dram speed, but lower than DPM0 still uses DPM0 */
		क्रम (i = 3; i > 0; i--)
			अगर (min_dram_speed_mts + min_dram_speed_mts_margin > dc->clk_mgr->bw_params->dummy_pstate_table[i].dram_speed_mts)
				अवरोध;

		context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us = dc->clk_mgr->bw_params->dummy_pstate_table[i].dummy_pstate_latency_us;
		context->bw_ctx.dml.soc.sr_enter_plus_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_C].dml_input.sr_enter_plus_निकास_समय_us;
		context->bw_ctx.dml.soc.sr_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_C].dml_input.sr_निकास_समय_us;
	पूर्ण
	context->bw_ctx.bw.dcn.watermarks.c.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	context->bw_ctx.bw.dcn.watermarks.c.urgent_latency_ns = get_urgent_latency(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;

	अगर (!pstate_en) अणु
		/* The only dअगरference between A and C is p-state latency, अगर p-state is not supported we want to
		 * calculate DLG based on dummy p-state latency, and max out the set A p-state watermark
		 */
		context->bw_ctx.bw.dcn.watermarks.a = context->bw_ctx.bw.dcn.watermarks.c;
		context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.pstate_change_ns = 0;
	पूर्ण अन्यथा अणु
		/* Set A:
		 * DCFCLK: Min Required
		 * FCLK(proportional to UCLK): 1GHz or Max
		 *
		 * Set A calculated last so that following calculations are based on Set A
		 */
		dc->res_pool->funcs->update_soc_क्रम_wm_a(dc, context);
		context->bw_ctx.bw.dcn.watermarks.a.urgent_ns = get_wm_urgent(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.pte_meta_urgent_ns = get_wm_memory_trip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
		context->bw_ctx.bw.dcn.watermarks.a.urgent_latency_ns = get_urgent_latency(&context->bw_ctx.dml, pipes, pipe_cnt) * 1000;
	पूर्ण

	context->perf_params.stutter_period_us = context->bw_ctx.dml.vba.StutterPeriod;

	/* Make set D = set A until set D is enabled */
	context->bw_ctx.bw.dcn.watermarks.d = context->bw_ctx.bw.dcn.watermarks.a;

	क्रम (i = 0, pipe_idx = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (!context->res_ctx.pipe_ctx[i].stream)
			जारी;

		pipes[pipe_idx].clks_cfg.dispclk_mhz = get_dispclk_calculated(&context->bw_ctx.dml, pipes, pipe_cnt);
		pipes[pipe_idx].clks_cfg.dppclk_mhz = get_dppclk_calculated(&context->bw_ctx.dml, pipes, pipe_cnt, pipe_idx);

		अगर (dc->config.क्रमced_घड़ीs) अणु
			pipes[pipe_idx].clks_cfg.dispclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[0].dispclk_mhz;
			pipes[pipe_idx].clks_cfg.dppclk_mhz = context->bw_ctx.dml.soc.घड़ी_limits[0].dppclk_mhz;
		पूर्ण
		अगर (dc->debug.min_disp_clk_khz > pipes[pipe_idx].clks_cfg.dispclk_mhz * 1000)
			pipes[pipe_idx].clks_cfg.dispclk_mhz = dc->debug.min_disp_clk_khz / 1000.0;
		अगर (dc->debug.min_dpp_clk_khz > pipes[pipe_idx].clks_cfg.dppclk_mhz * 1000)
			pipes[pipe_idx].clks_cfg.dppclk_mhz = dc->debug.min_dpp_clk_khz / 1000.0;

		pipe_idx++;
	पूर्ण

	dcn20_calculate_dlg_params(dc, context, pipes, pipe_cnt, vlevel);

	अगर (!pstate_en)
		/* Restore full p-state latency */
		context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us =
				dc->clk_mgr->bw_params->wm_table.nv_entries[WM_A].dml_input.pstate_latency_us;
पूर्ण

व्योम dcn30_update_soc_क्रम_wm_a(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	अगर (dc->clk_mgr->bw_params->wm_table.nv_entries[WM_A].valid) अणु
		context->bw_ctx.dml.soc.dram_घड़ी_change_latency_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_A].dml_input.pstate_latency_us;
		context->bw_ctx.dml.soc.sr_enter_plus_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_A].dml_input.sr_enter_plus_निकास_समय_us;
		context->bw_ctx.dml.soc.sr_निकास_समय_us = dc->clk_mgr->bw_params->wm_table.nv_entries[WM_A].dml_input.sr_निकास_समय_us;
	पूर्ण
पूर्ण

व्योम dcn30_calculate_wm_and_dlg(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt,
		पूर्णांक vlevel)
अणु
	DC_FP_START();
	dcn30_calculate_wm_and_dlg_fp(dc, context, pipes, pipe_cnt, vlevel);
	DC_FP_END();
पूर्ण

bool dcn30_validate_bandwidth(काष्ठा dc *dc,
		काष्ठा dc_state *context,
		bool fast_validate)
अणु
	bool out = false;

	BW_VAL_TRACE_SETUP();

	पूर्णांक vlevel = 0;
	पूर्णांक pipe_cnt = 0;
	display_e2e_pipe_params_st *pipes = kzalloc(dc->res_pool->pipe_count * माप(display_e2e_pipe_params_st), GFP_KERNEL);
	DC_LOGGER_INIT(dc->ctx->logger);

	BW_VAL_TRACE_COUNT();

	out = dcn30_पूर्णांकernal_validate_bw(dc, context, pipes, &pipe_cnt, &vlevel, fast_validate);

	अगर (pipe_cnt == 0)
		जाओ validate_out;

	अगर (!out)
		जाओ validate_fail;

	BW_VAL_TRACE_END_VOLTAGE_LEVEL();

	अगर (fast_validate) अणु
		BW_VAL_TRACE_SKIP(fast);
		जाओ validate_out;
	पूर्ण

	dc->res_pool->funcs->calculate_wm_and_dlg(dc, context, pipes, pipe_cnt, vlevel);

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
अटल noअंतरभूत व्योम dcn30_get_optimal_dcfclk_fclk_क्रम_uclk(अचिन्हित पूर्णांक uclk_mts,
		अचिन्हित पूर्णांक *optimal_dcfclk,
		अचिन्हित पूर्णांक *optimal_fclk)
अणु
       द्विगुन bw_from_dram, bw_from_dram1, bw_from_dram2;

       bw_from_dram1 = uclk_mts * dcn3_0_soc.num_chans *
		dcn3_0_soc.dram_channel_width_bytes * (dcn3_0_soc.max_avg_dram_bw_use_normal_percent / 100);
       bw_from_dram2 = uclk_mts * dcn3_0_soc.num_chans *
		dcn3_0_soc.dram_channel_width_bytes * (dcn3_0_soc.max_avg_sdp_bw_use_normal_percent / 100);

       bw_from_dram = (bw_from_dram1 < bw_from_dram2) ? bw_from_dram1 : bw_from_dram2;

       अगर (optimal_fclk)
               *optimal_fclk = bw_from_dram /
               (dcn3_0_soc.fabric_datapath_to_dcn_data_वापस_bytes * (dcn3_0_soc.max_avg_sdp_bw_use_normal_percent / 100));

       अगर (optimal_dcfclk)
               *optimal_dcfclk =  bw_from_dram /
               (dcn3_0_soc.वापस_bus_width_bytes * (dcn3_0_soc.max_avg_sdp_bw_use_normal_percent / 100));
पूर्ण

व्योम dcn30_update_bw_bounding_box(काष्ठा dc *dc, काष्ठा clk_bw_params *bw_params)
अणु
	अचिन्हित पूर्णांक i, j;
	अचिन्हित पूर्णांक num_states = 0;

	अचिन्हित पूर्णांक dcfclk_mhz[DC__VOLTAGE_STATES] = अणु0पूर्ण;
	अचिन्हित पूर्णांक dram_speed_mts[DC__VOLTAGE_STATES] = अणु0पूर्ण;
	अचिन्हित पूर्णांक optimal_uclk_क्रम_dcfclk_sta_tarमाला_लो[DC__VOLTAGE_STATES] = अणु0पूर्ण;
	अचिन्हित पूर्णांक optimal_dcfclk_क्रम_uclk[DC__VOLTAGE_STATES] = अणु0पूर्ण;

	अचिन्हित पूर्णांक dcfclk_sta_tarमाला_लो[DC__VOLTAGE_STATES] = अणु694, 875, 1000, 1200पूर्ण;
	अचिन्हित पूर्णांक num_dcfclk_sta_tarमाला_लो = 4;
	अचिन्हित पूर्णांक num_uclk_states;

	अगर (dc->ctx->dc_bios->vram_info.num_chans)
		dcn3_0_soc.num_chans = dc->ctx->dc_bios->vram_info.num_chans;

	अगर (dc->ctx->dc_bios->vram_info.dram_channel_width_bytes)
		dcn3_0_soc.dram_channel_width_bytes = dc->ctx->dc_bios->vram_info.dram_channel_width_bytes;

	dcn3_0_soc.dispclk_dppclk_vco_speed_mhz = dc->clk_mgr->dentist_vco_freq_khz / 1000.0;
	dc->dml.soc.dispclk_dppclk_vco_speed_mhz = dc->clk_mgr->dentist_vco_freq_khz / 1000.0;

	अगर (bw_params->clk_table.entries[0].memclk_mhz) अणु

		अगर (bw_params->clk_table.entries[1].dcfclk_mhz > dcfclk_sta_tarमाला_लो[num_dcfclk_sta_tarमाला_लो-1]) अणु
			// If max DCFCLK is greater than the max DCFCLK STA target, insert पूर्णांकo the DCFCLK STA target array
			dcfclk_sta_tarमाला_लो[num_dcfclk_sta_tarमाला_लो] = bw_params->clk_table.entries[1].dcfclk_mhz;
			num_dcfclk_sta_tarमाला_लो++;
		पूर्ण अन्यथा अगर (bw_params->clk_table.entries[1].dcfclk_mhz < dcfclk_sta_tarमाला_लो[num_dcfclk_sta_tarमाला_लो-1]) अणु
			// If max DCFCLK is less than the max DCFCLK STA target, cap values and हटाओ duplicates
			क्रम (i = 0; i < num_dcfclk_sta_tarमाला_लो; i++) अणु
				अगर (dcfclk_sta_tarमाला_लो[i] > bw_params->clk_table.entries[1].dcfclk_mhz) अणु
					dcfclk_sta_tarमाला_लो[i] = bw_params->clk_table.entries[1].dcfclk_mhz;
					अवरोध;
				पूर्ण
			पूर्ण
			// Update size of array since we "removed" duplicates
			num_dcfclk_sta_tarमाला_लो = i + 1;
		पूर्ण

		num_uclk_states = bw_params->clk_table.num_entries;

		// Calculate optimal dcfclk क्रम each uclk
		क्रम (i = 0; i < num_uclk_states; i++) अणु
			DC_FP_START();
			dcn30_get_optimal_dcfclk_fclk_क्रम_uclk(bw_params->clk_table.entries[i].memclk_mhz * 16,
					&optimal_dcfclk_क्रम_uclk[i], शून्य);
			DC_FP_END();
			अगर (optimal_dcfclk_क्रम_uclk[i] < bw_params->clk_table.entries[0].dcfclk_mhz) अणु
				optimal_dcfclk_क्रम_uclk[i] = bw_params->clk_table.entries[0].dcfclk_mhz;
			पूर्ण
		पूर्ण

		// Calculate optimal uclk क्रम each dcfclk sta target
		क्रम (i = 0; i < num_dcfclk_sta_tarमाला_लो; i++) अणु
			क्रम (j = 0; j < num_uclk_states; j++) अणु
				अगर (dcfclk_sta_tarमाला_लो[i] < optimal_dcfclk_क्रम_uclk[j]) अणु
					optimal_uclk_क्रम_dcfclk_sta_tarमाला_लो[i] =
							bw_params->clk_table.entries[j].memclk_mhz * 16;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		i = 0;
		j = 0;
		// create the final dcfclk and uclk table
		जबतक (i < num_dcfclk_sta_tarमाला_लो && j < num_uclk_states && num_states < DC__VOLTAGE_STATES) अणु
			अगर (dcfclk_sta_tarमाला_लो[i] < optimal_dcfclk_क्रम_uclk[j] && i < num_dcfclk_sta_tarमाला_लो) अणु
				dcfclk_mhz[num_states] = dcfclk_sta_tarमाला_लो[i];
				dram_speed_mts[num_states++] = optimal_uclk_क्रम_dcfclk_sta_tarमाला_लो[i++];
			पूर्ण अन्यथा अणु
				अगर (j < num_uclk_states && optimal_dcfclk_क्रम_uclk[j] <= bw_params->clk_table.entries[1].dcfclk_mhz) अणु
					dcfclk_mhz[num_states] = optimal_dcfclk_क्रम_uclk[j];
					dram_speed_mts[num_states++] = bw_params->clk_table.entries[j++].memclk_mhz * 16;
				पूर्ण अन्यथा अणु
					j = num_uclk_states;
				पूर्ण
			पूर्ण
		पूर्ण

		जबतक (i < num_dcfclk_sta_tarमाला_लो && num_states < DC__VOLTAGE_STATES) अणु
			dcfclk_mhz[num_states] = dcfclk_sta_tarमाला_लो[i];
			dram_speed_mts[num_states++] = optimal_uclk_क्रम_dcfclk_sta_tarमाला_लो[i++];
		पूर्ण

		जबतक (j < num_uclk_states && num_states < DC__VOLTAGE_STATES &&
				optimal_dcfclk_क्रम_uclk[j] <= bw_params->clk_table.entries[1].dcfclk_mhz) अणु
			dcfclk_mhz[num_states] = optimal_dcfclk_क्रम_uclk[j];
			dram_speed_mts[num_states++] = bw_params->clk_table.entries[j++].memclk_mhz * 16;
		पूर्ण

		क्रम (i = 0; i < dcn3_0_soc.num_states; i++) अणु
			dcn3_0_soc.घड़ी_limits[i].state = i;
			dcn3_0_soc.घड़ी_limits[i].dcfclk_mhz = dcfclk_mhz[i];
			dcn3_0_soc.घड़ी_limits[i].fabricclk_mhz = dcfclk_mhz[i];
			dcn3_0_soc.घड़ी_limits[i].dram_speed_mts = dram_speed_mts[i];

			/* Fill all states with max values of all other घड़ीs */
			dcn3_0_soc.घड़ी_limits[i].dispclk_mhz = bw_params->clk_table.entries[1].dispclk_mhz;
			dcn3_0_soc.घड़ी_limits[i].dppclk_mhz  = bw_params->clk_table.entries[1].dppclk_mhz;
			dcn3_0_soc.घड़ी_limits[i].phyclk_mhz  = bw_params->clk_table.entries[1].phyclk_mhz;
			dcn3_0_soc.घड़ी_limits[i].dtbclk_mhz = dcn3_0_soc.घड़ी_limits[0].dtbclk_mhz;
			/* These घड़ीs cannot come from bw_params, always fill from dcn3_0_soc[1] */
			/* FCLK, PHYCLK_D18, SOCCLK, DSCCLK */
			dcn3_0_soc.घड़ी_limits[i].phyclk_d18_mhz = dcn3_0_soc.घड़ी_limits[0].phyclk_d18_mhz;
			dcn3_0_soc.घड़ी_limits[i].socclk_mhz = dcn3_0_soc.घड़ी_limits[0].socclk_mhz;
			dcn3_0_soc.घड़ी_limits[i].dscclk_mhz = dcn3_0_soc.घड़ी_limits[0].dscclk_mhz;
		पूर्ण
		/* re-init DML with updated bb */
		dml_init_instance(&dc->dml, &dcn3_0_soc, &dcn3_0_ip, DML_PROJECT_DCN30);
		अगर (dc->current_state)
			dml_init_instance(&dc->current_state->bw_ctx.dml, &dcn3_0_soc, &dcn3_0_ip, DML_PROJECT_DCN30);
	पूर्ण

	/* re-init DML with updated bb */
	dml_init_instance(&dc->dml, &dcn3_0_soc, &dcn3_0_ip, DML_PROJECT_DCN30);
	अगर (dc->current_state)
		dml_init_instance(&dc->current_state->bw_ctx.dml, &dcn3_0_soc, &dcn3_0_ip, DML_PROJECT_DCN30);
पूर्ण

अटल स्थिर काष्ठा resource_funcs dcn30_res_pool_funcs = अणु
	.destroy = dcn30_destroy_resource_pool,
	.link_enc_create = dcn30_link_encoder_create,
	.panel_cntl_create = dcn30_panel_cntl_create,
	.validate_bandwidth = dcn30_validate_bandwidth,
	.calculate_wm_and_dlg = dcn30_calculate_wm_and_dlg,
	.update_soc_क्रम_wm_a = dcn30_update_soc_क्रम_wm_a,
	.populate_dml_pipes = dcn30_populate_dml_pipes_from_context,
	.acquire_idle_pipe_क्रम_layer = dcn20_acquire_idle_pipe_क्रम_layer,
	.add_stream_to_ctx = dcn30_add_stream_to_ctx,
	.add_dsc_to_stream_resource = dcn20_add_dsc_to_stream_resource,
	.हटाओ_stream_from_ctx = dcn20_हटाओ_stream_from_ctx,
	.populate_dml_ग_लिखोback_from_context = dcn30_populate_dml_ग_लिखोback_from_context,
	.set_mcअगर_arb_params = dcn30_set_mcअगर_arb_params,
	.find_first_मुक्त_match_stream_enc_क्रम_link = dcn10_find_first_मुक्त_match_stream_enc_क्रम_link,
	.acquire_post_bldn_3dlut = dcn30_acquire_post_bldn_3dlut,
	.release_post_bldn_3dlut = dcn30_release_post_bldn_3dlut,
	.update_bw_bounding_box = dcn30_update_bw_bounding_box,
	.patch_unknown_plane_state = dcn20_patch_unknown_plane_state,
पूर्ण;

#घोषणा CTX ctx

#घोषणा REG(reg_name) \
	(DCN_BASE.instance[0].segment[mm ## reg_name ## _BASE_IDX] + mm ## reg_name)

अटल uपूर्णांक32_t पढ़ो_pipe_fuses(काष्ठा dc_context *ctx)
अणु
	uपूर्णांक32_t value = REG_READ(CC_DC_PIPE_DIS);
	/* Support क्रम max 6 pipes */
	value = value & 0x3f;
	वापस value;
पूर्ण

अटल bool dcn30_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा dcn30_resource_pool *pool)
अणु
	पूर्णांक i;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा irq_service_init_data init_data;
	काष्ठा ddc_service_init_data ddc_init_data;
	uपूर्णांक32_t pipe_fuses = पढ़ो_pipe_fuses(ctx);
	uपूर्णांक32_t num_pipes = 0;

	अगर (!(pipe_fuses == 0 || pipe_fuses == 0x3e)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: Unexpected fuse recipe for navi2x !\n");
		/* fault to single pipe */
		pipe_fuses = 0x3e;
	पूर्ण

	DC_FP_START();

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap_dcn3;

	pool->base.funcs = &dcn30_res_pool_funcs;

	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;
	pool->base.pipe_count = pool->base.res_cap->num_timing_generator;
	pool->base.mpcc_count = pool->base.res_cap->num_timing_generator;
	dc->caps.max_करोwnscale_ratio = 600;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100; /*1.4 w/a not applied by शेष*/
	dc->caps.max_cursor_size = 256;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.dmdata_alloc_size = 2048;
	dc->caps.mall_size_per_mem_channel = 8;
	/* total size = mall per channel * num channels * 1024 * 1024 */
	dc->caps.mall_माप_प्रकारotal = dc->caps.mall_size_per_mem_channel * dc->ctx->dc_bios->vram_info.num_chans * 1048576;
	dc->caps.cursor_cache_size = dc->caps.max_cursor_size * dc->caps.max_cursor_size * 8;

	dc->caps.max_slave_planes = 1;
	dc->caps.max_slave_yuv_planes = 1;
	dc->caps.max_slave_rgb_planes = 1;
	dc->caps.post_blend_color_processing = true;
	dc->caps.क्रमce_dp_tps4_क्रम_cp2520 = true;
	dc->caps.extended_aux_समयout_support = true;
	dc->caps.dmcub_support = true;

	/* Color pipeline capabilities */
	dc->caps.color.dpp.dcn_arch = 1;
	dc->caps.color.dpp.input_lut_shared = 0;
	dc->caps.color.dpp.icsc = 1;
	dc->caps.color.dpp.dgam_ram = 0; // must use gamma_corr
	dc->caps.color.dpp.dgam_rom_caps.srgb = 1;
	dc->caps.color.dpp.dgam_rom_caps.bt2020 = 1;
	dc->caps.color.dpp.dgam_rom_caps.gamma2_2 = 1;
	dc->caps.color.dpp.dgam_rom_caps.pq = 1;
	dc->caps.color.dpp.dgam_rom_caps.hlg = 1;
	dc->caps.color.dpp.post_csc = 1;
	dc->caps.color.dpp.gamma_corr = 1;
	dc->caps.color.dpp.dgam_rom_क्रम_yuv = 0;

	dc->caps.color.dpp.hw_3d_lut = 1;
	dc->caps.color.dpp.ogam_ram = 1;
	// no OGAM ROM on DCN3
	dc->caps.color.dpp.ogam_rom_caps.srgb = 0;
	dc->caps.color.dpp.ogam_rom_caps.bt2020 = 0;
	dc->caps.color.dpp.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.dpp.ogam_rom_caps.pq = 0;
	dc->caps.color.dpp.ogam_rom_caps.hlg = 0;
	dc->caps.color.dpp.ocsc = 0;

	dc->caps.color.mpc.gamut_remap = 1;
	dc->caps.color.mpc.num_3dluts = pool->base.res_cap->num_mpc_3dlut; //3
	dc->caps.color.mpc.ogam_ram = 1;
	dc->caps.color.mpc.ogam_rom_caps.srgb = 0;
	dc->caps.color.mpc.ogam_rom_caps.bt2020 = 0;
	dc->caps.color.mpc.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.mpc.ogam_rom_caps.pq = 0;
	dc->caps.color.mpc.ogam_rom_caps.hlg = 0;
	dc->caps.color.mpc.ocsc = 1;

	अगर (dc->ctx->dce_environment == DCE_ENV_PRODUCTION_DRV)
		dc->debug = debug_शेषs_drv;
	अन्यथा अगर (dc->ctx->dce_environment == DCE_ENV_FPGA_MAXIMUS) अणु
		dc->debug = debug_शेषs_diags;
	पूर्ण अन्यथा
		dc->debug = debug_शेषs_diags;
	// Init the vm_helper
	अगर (dc->vm_helper)
		vm_helper_init(dc->vm_helper, 16);

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	/* Clock Sources क्रम Pixel Clock*/
	pool->base.घड़ी_sources[DCN30_CLK_SRC_PLL0] =
			dcn30_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL0,
				&clk_src_regs[0], false);
	pool->base.घड़ी_sources[DCN30_CLK_SRC_PLL1] =
			dcn30_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL1,
				&clk_src_regs[1], false);
	pool->base.घड़ी_sources[DCN30_CLK_SRC_PLL2] =
			dcn30_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL2,
				&clk_src_regs[2], false);
	pool->base.घड़ी_sources[DCN30_CLK_SRC_PLL3] =
			dcn30_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL3,
				&clk_src_regs[3], false);
	pool->base.घड़ी_sources[DCN30_CLK_SRC_PLL4] =
			dcn30_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL4,
				&clk_src_regs[4], false);
	pool->base.घड़ी_sources[DCN30_CLK_SRC_PLL5] =
			dcn30_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL5,
				&clk_src_regs[5], false);

	pool->base.clk_src_count = DCN30_CLK_SRC_TOTAL;

	/* toकरो: not reuse phy_pll रेजिस्टरs */
	pool->base.dp_घड़ी_source =
			dcn30_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_ID_DP_DTO,
				&clk_src_regs[0], true);

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] == शून्य) अणु
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण
	पूर्ण

	/* DCCG */
	pool->base.dccg = dccg30_create(ctx, &dccg_regs, &dccg_shअगरt, &dccg_mask);
	अगर (pool->base.dccg == शून्य) अणु
		dm_error("DC: failed to create dccg!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	/* PP Lib and SMU पूर्णांकerfaces */
	init_soc_bounding_box(dc, pool);

	num_pipes = dcn3_0_ip.max_num_dpp;

	क्रम (i = 0; i < dcn3_0_ip.max_num_dpp; i++)
		अगर (pipe_fuses & 1 << i)
			num_pipes--;

	dcn3_0_ip.max_num_dpp = num_pipes;
	dcn3_0_ip.max_num_otg = num_pipes;

	dml_init_instance(&dc->dml, &dcn3_0_soc, &dcn3_0_ip, DML_PROJECT_DCN30);

	/* IRQ */
	init_data.ctx = dc->ctx;
	pool->base.irqs = dal_irq_service_dcn30_create(&init_data);
	अगर (!pool->base.irqs)
		जाओ create_fail;

	/* HUBBUB */
	pool->base.hubbub = dcn30_hubbub_create(ctx);
	अगर (pool->base.hubbub == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create hubbub!\n");
		जाओ create_fail;
	पूर्ण

	/* HUBPs, DPPs, OPPs and TGs */
	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		pool->base.hubps[i] = dcn30_hubp_create(ctx, i);
		अगर (pool->base.hubps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create hubps!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.dpps[i] = dcn30_dpp_create(ctx, i);
		अगर (pool->base.dpps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create dpps!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_opp; i++) अणु
		pool->base.opps[i] = dcn30_opp_create(ctx, i);
		अगर (pool->base.opps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_timing_generator; i++) अणु
		pool->base.timing_generators[i] = dcn30_timing_generator_create(
				ctx, i);
		अगर (pool->base.timing_generators[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण
	pool->base.timing_generator_count = i;
	/* PSR */
	pool->base.psr = dmub_psr_create(ctx);

	अगर (pool->base.psr == शून्य) अणु
		dm_error("DC: failed to create PSR obj!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	/* ABM */
	क्रम (i = 0; i < pool->base.res_cap->num_timing_generator; i++) अणु
		pool->base.multiple_abms[i] = dmub_abm_create(ctx,
				&abm_regs[i],
				&abm_shअगरt,
				&abm_mask);
		अगर (pool->base.multiple_abms[i] == शून्य) अणु
			dm_error("DC: failed to create abm for pipe %d!\n", i);
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण
	पूर्ण
	/* MPC and DSC */
	pool->base.mpc = dcn30_mpc_create(ctx, pool->base.mpcc_count, pool->base.res_cap->num_mpc_3dlut);
	अगर (pool->base.mpc == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mpc!\n");
		जाओ create_fail;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_dsc; i++) अणु
		pool->base.dscs[i] = dcn30_dsc_create(ctx, i);
		अगर (pool->base.dscs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create display stream compressor %d!\n", i);
			जाओ create_fail;
		पूर्ण
	पूर्ण

	/* DWB and MMHUBBUB */
	अगर (!dcn30_dwbc_create(ctx, &pool->base)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create dwbc!\n");
		जाओ create_fail;
	पूर्ण

	अगर (!dcn30_mmhubbub_create(ctx, &pool->base)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mcif_wb!\n");
		जाओ create_fail;
	पूर्ण

	/* AUX and I2C */
	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dcn30_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dcn30_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create hw i2c!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	/* Audio, Stream Encoders including DIG and भव, MPC 3D LUTs */
	अगर (!resource_स्थिरruct(num_भव_links, dc, &pool->base,
			(!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment) ?
			&res_create_funcs : &res_create_maximus_funcs)))
		जाओ create_fail;

	/* HW Sequencer and Plane caps */
	dcn30_hw_sequencer_स्थिरruct(dc);

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
	dcn30_resource_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dcn30_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc)
अणु
	काष्ठा dcn30_resource_pool *pool =
		kzalloc(माप(काष्ठा dcn30_resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dcn30_resource_स्थिरruct(init_data->num_भव_links, dc, pool))
		वापस &pool->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(pool);
	वापस शून्य;
पूर्ण
