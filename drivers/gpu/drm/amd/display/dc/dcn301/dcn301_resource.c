<शैली गुरु>
/*
 * Copyright 2019-2021 Advanced Micro Devices, Inc.
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

#समावेश "dcn301_init.h"

#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "dcn30/dcn30_resource.h"
#समावेश "dcn301_resource.h"

#समावेश "dcn20/dcn20_resource.h"

#समावेश "dcn10/dcn10_ipp.h"
#समावेश "dcn301/dcn301_hubbub.h"
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
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "clk_mgr.h"
#समावेश "virtual/virtual_stream_encoder.h"
#समावेश "dce110/dce110_resource.h"
#समावेश "dml/display_mode_vba.h"
#समावेश "dcn301/dcn301_dccg.h"
#समावेश "dcn10/dcn10_resource.h"
#समावेश "dcn30/dcn30_dio_stream_encoder.h"
#समावेश "dcn301/dcn301_dio_link_encoder.h"
#समावेश "dcn301_panel_cntl.h"

#समावेश "vangogh_ip_offset.h"

#समावेश "dcn30/dcn30_dwb.h"
#समावेश "dcn30/dcn30_mmhubbub.h"

#समावेश "dcn/dcn_3_0_1_offset.h"
#समावेश "dcn/dcn_3_0_1_sh_mask.h"

#समावेश "nbio/nbio_7_2_0_offset.h"

#समावेश "dcn/dpcs_3_0_0_offset.h"
#समावेश "dcn/dpcs_3_0_0_sh_mask.h"

#समावेश "reg_helper.h"
#समावेश "dce/dmub_abm.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_i2c.h"

#समावेश "dml/dcn30/display_mode_vba_30.h"
#समावेश "vm_helper.h"
#समावेश "dcn20/dcn20_vmid.h"
#समावेश "amdgpu_socbb.h"

#घोषणा TO_DCN301_RES_POOL(pool)\
	container_of(pool, काष्ठा dcn301_resource_pool, base)

#घोषणा DC_LOGGER_INIT(logger)

काष्ठा _vcs_dpi_ip_params_st dcn3_01_ip = अणु
	.odm_capable = 1,
	.gpuvm_enable = 1,
	.hostvm_enable = 1,
	.gpuvm_max_page_table_levels = 1,
	.hostvm_max_page_table_levels = 2,
	.hostvm_cached_page_table_levels = 0,
	.pte_group_size_bytes = 2048,
	.num_dsc = 3,
	.rob_buffer_size_kbytes = 184,
	.det_buffer_size_kbytes = 184,
	.dpte_buffer_size_in_pte_reqs_luma = 64,
	.dpte_buffer_size_in_pte_reqs_chroma = 32,
	.pde_proc_buffer_size_64k_reqs = 48,
	.dpp_output_buffer_pixels = 2560,
	.opp_output_buffer_lines = 1,
	.pixel_chunk_size_kbytes = 8,
	.meta_chunk_size_kbytes = 2,
	.ग_लिखोback_chunk_size_kbytes = 8,
	.line_buffer_size_bits = 789504,
	.is_line_buffer_bpp_fixed = 0,  // ?
	.line_buffer_fixed_bpp = 48,     // ?
	.dcc_supported = true,
	.ग_लिखोback_पूर्णांकerface_buffer_size_kbytes = 90,
	.ग_लिखोback_line_buffer_buffer_size = 656640,
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
	.max_num_otg = 4,
	.max_num_dpp = 4,
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
	.max_num_hdmi_frl_outमाला_दो = 0,
	.odm_combine_4to1_supported = true,

	.xfc_supported = false,
	.xfc_fill_bw_overhead_percent = 10.0,
	.xfc_fill_स्थिरant_bytes = 0,
	.gfx7_compat_tiling_supported = 0,
	.number_of_cursors = 1,
पूर्ण;

काष्ठा _vcs_dpi_soc_bounding_box_st dcn3_01_soc = अणु
	.घड़ी_limits = अणु
			अणु
				.state = 0,
				.dram_speed_mts = 2400.0,
				.fabricclk_mhz = 600,
				.socclk_mhz = 278.0,
				.dcfclk_mhz = 400.0,
				.dscclk_mhz = 206.0,
				.dppclk_mhz = 1015.0,
				.dispclk_mhz = 1015.0,
				.phyclk_mhz = 600.0,
			पूर्ण,
			अणु
				.state = 1,
				.dram_speed_mts = 2400.0,
				.fabricclk_mhz = 688,
				.socclk_mhz = 278.0,
				.dcfclk_mhz = 400.0,
				.dscclk_mhz = 206.0,
				.dppclk_mhz = 1015.0,
				.dispclk_mhz = 1015.0,
				.phyclk_mhz = 600.0,
			पूर्ण,
			अणु
				.state = 2,
				.dram_speed_mts = 4267.0,
				.fabricclk_mhz = 1067,
				.socclk_mhz = 278.0,
				.dcfclk_mhz = 608.0,
				.dscclk_mhz = 296.0,
				.dppclk_mhz = 1015.0,
				.dispclk_mhz = 1015.0,
				.phyclk_mhz = 810.0,
			पूर्ण,

			अणु
				.state = 3,
				.dram_speed_mts = 4267.0,
				.fabricclk_mhz = 1067,
				.socclk_mhz = 715.0,
				.dcfclk_mhz = 676.0,
				.dscclk_mhz = 338.0,
				.dppclk_mhz = 1015.0,
				.dispclk_mhz = 1015.0,
				.phyclk_mhz = 810.0,
			पूर्ण,

			अणु
				.state = 4,
				.dram_speed_mts = 4267.0,
				.fabricclk_mhz = 1067,
				.socclk_mhz = 953.0,
				.dcfclk_mhz = 810.0,
				.dscclk_mhz = 338.0,
				.dppclk_mhz = 1015.0,
				.dispclk_mhz = 1015.0,
				.phyclk_mhz = 810.0,
			पूर्ण,
		पूर्ण,

	.sr_निकास_समय_us = 9.0,
	.sr_enter_plus_निकास_समय_us = 11.0,
	.urgent_latency_us = 4.0,
	.urgent_latency_pixel_data_only_us = 4.0,
	.urgent_latency_pixel_mixed_with_vm_data_us = 4.0,
	.urgent_latency_vm_data_only_us = 4.0,
	.urgent_out_of_order_वापस_per_channel_pixel_only_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_pixel_and_vm_bytes = 4096,
	.urgent_out_of_order_वापस_per_channel_vm_only_bytes = 4096,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_only = 80.0,
	.pct_ideal_dram_sdp_bw_after_urgent_pixel_and_vm = 75.0,
	.pct_ideal_dram_sdp_bw_after_urgent_vm_only = 40.0,
	.max_avg_sdp_bw_use_normal_percent = 60.0,
	.max_avg_dram_bw_use_normal_percent = 60.0,
	.ग_लिखोback_latency_us = 12.0,
	.max_request_size_bytes = 256,
	.dram_channel_width_bytes = 4,
	.fabric_datapath_to_dcn_data_वापस_bytes = 32,
	.dcn_करोwnspपढ़ो_percent = 0.5,
	.करोwnspपढ़ो_percent = 0.38,
	.dram_page_खोलो_समय_ns = 50.0,
	.dram_rw_turnaround_समय_ns = 17.5,
	.dram_वापस_buffer_per_channel_bytes = 8192,
	.round_trip_ping_latency_dcfclk_cycles = 191,
	.urgent_out_of_order_वापस_per_channel_bytes = 4096,
	.channel_पूर्णांकerleave_bytes = 256,
	.num_banks = 8,
	.num_chans = 4,
	.gpuvm_min_page_size_bytes = 4096,
	.hostvm_min_page_size_bytes = 4096,
	.dram_घड़ी_change_latency_us = 23.84,
	.ग_लिखोback_dram_घड़ी_change_latency_us = 23.0,
	.वापस_bus_width_bytes = 64,
	.dispclk_dppclk_vco_speed_mhz = 3550,
	.xfc_bus_transport_समय_us = 20,      // ?
	.xfc_xbuf_latency_tolerance_us = 4,  // ?
	.use_urgent_burst_bw = 1,            // ?
	.num_states = 5,
	.करो_urgent_latency_adjusपंचांगent = false,
	.urgent_latency_adjusपंचांगent_fabric_घड़ी_component_us = 0,
	.urgent_latency_adjusपंचांगent_fabric_घड़ी_reference_mhz = 0,
पूर्ण;

क्रमागत dcn301_clk_src_array_id अणु
	DCN301_CLK_SRC_PLL0,
	DCN301_CLK_SRC_PLL1,
	DCN301_CLK_SRC_PLL2,
	DCN301_CLK_SRC_PLL3,
	DCN301_CLK_SRC_TOTAL
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

#घोषणा SRII2(reg_name_pre, reg_name_post, id)\
	.reg_name_pre ## _ ##  reg_name_post[id] = BASE(mm ## reg_name_pre \
			## id ## _ ## reg_name_post ## _BASE_IDX) + \
			mm ## reg_name_pre ## id ## _ ## reg_name_post

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
		.reg_name = NBIO_BASE(regBIF_BX0_ ## reg_name ## _BASE_IDX) + \
					regBIF_BX0_ ## reg_name

/* MMHUB */
#घोषणा MMHUB_BASE_INNER(seg) \
	MMHUB_BASE__INST0_SEG ## seg

#घोषणा MMHUB_BASE(seg) \
	MMHUB_BASE_INNER(seg)

#घोषणा MMHUB_SR(reg_name)\
		.reg_name = MMHUB_BASE(regMM ## reg_name ## _BASE_IDX) + \
					regMM ## reg_name

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
	CS_COMMON_REG_LIST_DCN3_01(index, pllid),\
पूर्ण

अटल स्थिर काष्ठा dce110_clk_src_regs clk_src_regs[] = अणु
	clk_src_regs(0, A),
	clk_src_regs(1, B),
	clk_src_regs(2, C),
	clk_src_regs(3, D)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_shअगरt cs_shअगरt = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_mask cs_mask = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
पूर्ण;

#घोषणा abm_regs(id)\
[id] = अणु\
		ABM_DCN301_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dce_abm_रेजिस्टरs abm_regs[] = अणु
		abm_regs(0),
		abm_regs(1),
		abm_regs(2),
		abm_regs(3),
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
पूर्ण;


#घोषणा link_regs(id, phyid)\
[id] = अणु\
	LE_DCN301_REG_LIST(id), \
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
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_shअगरt le_shअगरt = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN301(__SHIFT),\
	DPCS_DCN2_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_mask le_mask = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN301(_MASK),\
	DPCS_DCN2_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा panel_cntl_regs(id)\
[id] = अणु\
	DCN301_PANEL_CNTL_REG_LIST(id),\
पूर्ण

अटल स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs panel_cntl_regs[] = अणु
	panel_cntl_regs(0),
	panel_cntl_regs(1),
पूर्ण;

अटल स्थिर काष्ठा dcn301_panel_cntl_shअगरt panel_cntl_shअगरt = अणु
	DCN301_PANEL_CNTL_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn301_panel_cntl_mask panel_cntl_mask = अणु
	DCN301_PANEL_CNTL_MASK_SH_LIST(_MASK)
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
		MPC_OUT_MUX_REG_LIST_DCN3_0(0),
		MPC_OUT_MUX_REG_LIST_DCN3_0(1),
		MPC_OUT_MUX_REG_LIST_DCN3_0(2),
		MPC_OUT_MUX_REG_LIST_DCN3_0(3),
		MPC_RMU_GLOBAL_REG_LIST_DCN3AG,
		MPC_RMU_REG_LIST_DCN3AG(0),
		MPC_RMU_REG_LIST_DCN3AG(1),
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
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_shअगरt hubp_shअगरt = अणु
		HUBP_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_mask hubp_mask = अणु
		HUBP_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_रेजिस्टरs hubbub_reg = अणु
		HUBBUB_REG_LIST_DCN301(0)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_shअगरt hubbub_shअगरt = अणु
		HUBBUB_MASK_SH_LIST_DCN301(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_mask hubbub_mask = अणु
		HUBBUB_MASK_SH_LIST_DCN301(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dccg_रेजिस्टरs dccg_regs = अणु
		DCCG_REG_LIST_DCN301()
पूर्ण;

अटल स्थिर काष्ठा dccg_shअगरt dccg_shअगरt = अणु
		DCCG_MASK_SH_LIST_DCN301(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dccg_mask dccg_mask = अणु
		DCCG_MASK_SH_LIST_DCN301(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCN301_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCN301_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCN301_MASK_SH_LIST(_MASK)
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

अटल स्थिर काष्ठा resource_caps res_cap_dcn301 = अणु
	.num_timing_generator = 4,
	.num_opp = 4,
	.num_video_plane = 4,
	.num_audio = 4,
	.num_stream_encoder = 4,
	.num_pll = 4,
	.num_dwb = 1,
	.num_ddc = 4,
	.num_vmid = 16,
	.num_mpc_3dlut = 2,
	.num_dsc = 3,
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
	पूर्ण,
	64,
	64
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_drv = अणु
	.disable_dmcu = true,
	.क्रमce_abm_enable = false,
	.timing_trace = false,
	.घड़ी_प्रकारrace = true,
	.disable_dpp_घातer_gate = false,
	.disable_hubp_घातer_gate = false,
	.disable_घड़ी_gate = true,
	.disable_pplib_घड़ी_request = true,
	.disable_pplib_wm_range = true,
	.pipe_split_policy = MPC_SPLIT_AVOID_MULT_DISP,
	.क्रमce_single_disp_pipe_split = false,
	.disable_dcc = DCC_ENABLE,
	.vsr_support = true,
	.perक्रमmance_trace = false,
	.max_करोwnscale_src_width = 7680,/*upto 8K*/
	.scl_reset_length10 = true,
	.sanity_checks = false,
	.underflow_निश्चित_delay_us = 0xFFFFFFFF,
	.dwb_fi_phase = -1, // -1 = disable
	.dmub_command_table = true,
	.use_max_lb = false,
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_diags = अणु
	.disable_dmcu = true,
	.क्रमce_abm_enable = false,
	.timing_trace = true,
	.घड़ी_प्रकारrace = true,
	.disable_dpp_घातer_gate = false,
	.disable_hubp_घातer_gate = false,
	.disable_घड़ी_gate = true,
	.disable_pplib_घड़ी_request = true,
	.disable_pplib_wm_range = true,
	.disable_stutter = true,
	.scl_reset_length10 = true,
	.dwb_fi_phase = -1, // -1 = disable
	.dmub_command_table = true,
	.use_max_lb = false,
पूर्ण;

व्योम dcn301_dpp_destroy(काष्ठा dpp **dpp)
अणु
	kमुक्त(TO_DCN20_DPP(*dpp));
	*dpp = शून्य;
पूर्ण

काष्ठा dpp *dcn301_dpp_create(
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
काष्ठा output_pixel_processor *dcn301_opp_create(
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

काष्ठा dce_aux *dcn301_aux_engine_create(
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
#घोषणा i2c_inst_regs(id) अणु I2C_HW_ENGINE_COMMON_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dce_i2c_रेजिस्टरs i2c_hw_regs[] = अणु
		i2c_inst_regs(1),
		i2c_inst_regs(2),
		i2c_inst_regs(3),
		i2c_inst_regs(4),
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_shअगरt i2c_shअगरts = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_mask i2c_masks = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(_MASK)
पूर्ण;

काष्ठा dce_i2c_hw *dcn301_i2c_hw_create(
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
अटल काष्ठा mpc *dcn301_mpc_create(
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

काष्ठा hubbub *dcn301_hubbub_create(काष्ठा dc_context *ctx)
अणु
	पूर्णांक i;

	काष्ठा dcn20_hubbub *hubbub3 = kzalloc(माप(काष्ठा dcn20_hubbub),
					  GFP_KERNEL);

	अगर (!hubbub3)
		वापस शून्य;

	hubbub301_स्थिरruct(hubbub3, ctx,
			&hubbub_reg,
			&hubbub_shअगरt,
			&hubbub_mask);


	क्रम (i = 0; i < res_cap_dcn301.num_vmid; i++) अणु
		काष्ठा dcn20_vmid *vmid = &hubbub3->vmid[i];

		vmid->ctx = ctx;

		vmid->regs = &vmid_regs[i];
		vmid->shअगरts = &vmid_shअगरts;
		vmid->masks = &vmid_masks;
	पूर्ण

	 hubbub3->num_vmid = res_cap_dcn301.num_vmid;

	वापस &hubbub3->base;
पूर्ण

काष्ठा timing_generator *dcn301_timing_generator_create(
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

काष्ठा link_encoder *dcn301_link_encoder_create(
	स्थिर काष्ठा encoder_init_data *enc_init_data)
अणु
	काष्ठा dcn20_link_encoder *enc20 =
		kzalloc(माप(काष्ठा dcn20_link_encoder), GFP_KERNEL);

	अगर (!enc20)
		वापस शून्य;

	dcn301_link_encoder_स्थिरruct(enc20,
			enc_init_data,
			&link_enc_feature,
			&link_enc_regs[enc_init_data->transmitter],
			&link_enc_aux_regs[enc_init_data->channel - 1],
			&link_enc_hpd_regs[enc_init_data->hpd_source],
			&le_shअगरt,
			&le_mask);

	वापस &enc20->enc10.base;
पूर्ण

काष्ठा panel_cntl *dcn301_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
अणु
	काष्ठा dcn301_panel_cntl *panel_cntl =
		kzalloc(माप(काष्ठा dcn301_panel_cntl), GFP_KERNEL);

	अगर (!panel_cntl)
		वापस शून्य;

	dcn301_panel_cntl_स्थिरruct(panel_cntl,
			init_data,
			&panel_cntl_regs[init_data->inst],
			&panel_cntl_shअगरt,
			&panel_cntl_mask);

	वापस &panel_cntl->base;
पूर्ण


#घोषणा CTX ctx

#घोषणा REG(reg_name) \
	(DCN_BASE.instance[0].segment[mm ## reg_name ## _BASE_IDX] + mm ## reg_name)

अटल uपूर्णांक32_t पढ़ो_pipe_fuses(काष्ठा dc_context *ctx)
अणु
	uपूर्णांक32_t value = REG_READ(CC_DC_PIPE_DIS);
	/* RV1 support max 4 pipes */
	value = value & 0xf;
	वापस value;
पूर्ण


अटल व्योम पढ़ो_dce_straps(
	काष्ठा dc_context *ctx,
	काष्ठा resource_straps *straps)
अणु
	generic_reg_get(ctx, mmDC_PINSTRAPS + BASE(mmDC_PINSTRAPS_BASE_IDX),
		FN(DC_PINSTRAPS, DC_PINSTRAPS_AUDIO), &straps->dc_pinstraps_audio);

पूर्ण

अटल काष्ठा audio *dcn301_create_audio(
		काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst,
			&audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

अटल काष्ठा vpg *dcn301_vpg_create(
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

अटल काष्ठा afmt *dcn301_afmt_create(
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

काष्ठा stream_encoder *dcn301_stream_encoder_create(
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
	vpg = dcn301_vpg_create(ctx, vpg_inst);
	afmt = dcn301_afmt_create(ctx, afmt_inst);

	अगर (!enc1 || !vpg || !afmt)
		वापस शून्य;

	dcn30_dio_stream_encoder_स्थिरruct(enc1, ctx, ctx->dc_bios,
					eng_id, vpg, afmt,
					&stream_enc_regs[eng_id],
					&se_shअगरt, &se_mask);

	वापस &enc1->base;
पूर्ण

काष्ठा dce_hwseq *dcn301_hwseq_create(
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
	.create_audio = dcn301_create_audio,
	.create_stream_encoder = dcn301_stream_encoder_create,
	.create_hwseq = dcn301_hwseq_create,
पूर्ण;

अटल स्थिर काष्ठा resource_create_funcs res_create_maximus_funcs = अणु
	.पढ़ो_dce_straps = शून्य,
	.create_audio = शून्य,
	.create_stream_encoder = शून्य,
	.create_hwseq = dcn301_hwseq_create,
पूर्ण;

अटल व्योम dcn301_deकाष्ठा(काष्ठा dcn301_resource_pool *pool)
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
			dcn301_dpp_destroy(&pool->base.dpps[i]);

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

	क्रम (i = 0; i < pool->base.res_cap->num_timing_generator; i++) अणु
		अगर (pool->base.multiple_abms[i] != शून्य)
			dce_abm_destroy(&pool->base.multiple_abms[i]);
	पूर्ण

	अगर (pool->base.dccg != शून्य)
		dcn_dccg_destroy(&pool->base.dccg);
पूर्ण

काष्ठा hubp *dcn301_hubp_create(
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

bool dcn301_dwbc_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
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

bool dcn301_mmhubbub_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
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

अटल काष्ठा display_stream_compressor *dcn301_dsc_create(
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


अटल व्योम dcn301_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dcn301_resource_pool *dcn301_pool = TO_DCN301_RES_POOL(*pool);

	dcn301_deकाष्ठा(dcn301_pool);
	kमुक्त(dcn301_pool);
	*pool = शून्य;
पूर्ण

अटल काष्ठा घड़ी_source *dcn301_घड़ी_source_create(
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

	अगर (dcn301_clk_src_स्थिरruct(clk_src, ctx, bios, id,
			regs, &cs_shअगरt, &cs_mask)) अणु
		clk_src->base.dp_clk_src = dp_clk_src;
		वापस &clk_src->base;
	पूर्ण

	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

अटल काष्ठा dc_cap_funcs cap_funcs = अणु
	.get_dcc_compression_cap = dcn20_get_dcc_compression_cap
पूर्ण;

#घोषणा fixed16_to_द्विगुन(x) (((द्विगुन) x) / ((द्विगुन) (1 << 16)))
#घोषणा fixed16_to_द्विगुन_to_cpu(x) fixed16_to_द्विगुन(le32_to_cpu(x))

अटल bool is_soc_bounding_box_valid(काष्ठा dc *dc)
अणु
	uपूर्णांक32_t hw_पूर्णांकernal_rev = dc->ctx->asic_id.hw_पूर्णांकernal_rev;

	अगर (ASICREV_IS_VANGOGH(hw_पूर्णांकernal_rev))
		वापस true;

	वापस false;
पूर्ण

अटल bool init_soc_bounding_box(काष्ठा dc *dc,
				  काष्ठा dcn301_resource_pool *pool)
अणु
	काष्ठा _vcs_dpi_soc_bounding_box_st *loaded_bb = &dcn3_01_soc;
	काष्ठा _vcs_dpi_ip_params_st *loaded_ip = &dcn3_01_ip;

	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (!is_soc_bounding_box_valid(dc)) अणु
		DC_LOG_ERROR("%s: not valid soc bounding box/n", __func__);
		वापस false;
	पूर्ण

	loaded_ip->max_num_otg = pool->base.res_cap->num_timing_generator;
	loaded_ip->max_num_dpp = pool->base.pipe_count;
	dcn20_patch_bounding_box(dc, loaded_bb);

	अगर (dc->ctx->dc_bios->funcs->get_soc_bb_info) अणु
		काष्ठा bp_soc_bb_info bb_info = अणु0पूर्ण;

		अगर (dc->ctx->dc_bios->funcs->get_soc_bb_info(dc->ctx->dc_bios, &bb_info) == BP_RESULT_OK) अणु
			अगर (bb_info.dram_घड़ी_change_latency_100ns > 0)
				dcn3_01_soc.dram_घड़ी_change_latency_us = bb_info.dram_घड़ी_change_latency_100ns * 10;

			अगर (bb_info.dram_sr_enter_निकास_latency_100ns > 0)
				dcn3_01_soc.sr_enter_plus_निकास_समय_us = bb_info.dram_sr_enter_निकास_latency_100ns * 10;

			अगर (bb_info.dram_sr_निकास_latency_100ns > 0)
				dcn3_01_soc.sr_निकास_समय_us = bb_info.dram_sr_निकास_latency_100ns * 10;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम set_wm_ranges(
		काष्ठा pp_smu_funcs *pp_smu,
		काष्ठा _vcs_dpi_soc_bounding_box_st *loaded_bb)
अणु
	काष्ठा pp_smu_wm_range_sets ranges = अणु0पूर्ण;
	पूर्णांक i;

	ranges.num_पढ़ोer_wm_sets = 0;

	अगर (loaded_bb->num_states == 1) अणु
		ranges.पढ़ोer_wm_sets[0].wm_inst = 0;
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
	pp_smu->nv_funcs.set_wm_ranges(&pp_smu->nv_funcs.pp_smu, &ranges);
पूर्ण

अटल व्योम dcn301_update_bw_bounding_box(काष्ठा dc *dc, काष्ठा clk_bw_params *bw_params)
अणु
	काष्ठा dcn301_resource_pool *pool = TO_DCN301_RES_POOL(dc->res_pool);
	काष्ठा clk_limit_table *clk_table = &bw_params->clk_table;
	काष्ठा _vcs_dpi_voltage_scaling_st घड़ी_limits[DC__VOLTAGE_STATES];
	अचिन्हित पूर्णांक i, बंदst_clk_lvl;
	पूर्णांक j;

	// Default घड़ी levels are used क्रम diags, which may lead to overघड़ीing.
	अगर (!IS_DIAG_DC(dc->ctx->dce_environment)) अणु
		dcn3_01_ip.max_num_otg = pool->base.res_cap->num_timing_generator;
		dcn3_01_ip.max_num_dpp = pool->base.pipe_count;
		dcn3_01_soc.num_chans = bw_params->num_channels;

		ASSERT(clk_table->num_entries);
		क्रम (i = 0; i < clk_table->num_entries; i++) अणु
			/* loop backwards*/
			क्रम (बंदst_clk_lvl = 0, j = dcn3_01_soc.num_states - 1; j >= 0; j--) अणु
				अगर ((अचिन्हित पूर्णांक) dcn3_01_soc.घड़ी_limits[j].dcfclk_mhz <= clk_table->entries[i].dcfclk_mhz) अणु
					बंदst_clk_lvl = j;
					अवरोध;
				पूर्ण
			पूर्ण

			घड़ी_limits[i].state = i;
			घड़ी_limits[i].dcfclk_mhz = clk_table->entries[i].dcfclk_mhz;
			घड़ी_limits[i].fabricclk_mhz = clk_table->entries[i].fclk_mhz;
			घड़ी_limits[i].socclk_mhz = clk_table->entries[i].socclk_mhz;
			घड़ी_limits[i].dram_speed_mts = clk_table->entries[i].memclk_mhz * 2;

			घड़ी_limits[i].dispclk_mhz = dcn3_01_soc.घड़ी_limits[बंदst_clk_lvl].dispclk_mhz;
			घड़ी_limits[i].dppclk_mhz = dcn3_01_soc.घड़ी_limits[बंदst_clk_lvl].dppclk_mhz;
			घड़ी_limits[i].dram_bw_per_chan_gbps = dcn3_01_soc.घड़ी_limits[बंदst_clk_lvl].dram_bw_per_chan_gbps;
			घड़ी_limits[i].dscclk_mhz = dcn3_01_soc.घड़ी_limits[बंदst_clk_lvl].dscclk_mhz;
			घड़ी_limits[i].dtbclk_mhz = dcn3_01_soc.घड़ी_limits[बंदst_clk_lvl].dtbclk_mhz;
			घड़ी_limits[i].phyclk_d18_mhz = dcn3_01_soc.घड़ी_limits[बंदst_clk_lvl].phyclk_d18_mhz;
			घड़ी_limits[i].phyclk_mhz = dcn3_01_soc.घड़ी_limits[बंदst_clk_lvl].phyclk_mhz;
		पूर्ण
		क्रम (i = 0; i < clk_table->num_entries; i++)
			dcn3_01_soc.घड़ी_limits[i] = घड़ी_limits[i];
		अगर (clk_table->num_entries) अणु
			dcn3_01_soc.num_states = clk_table->num_entries;
			/* duplicate last level */
			dcn3_01_soc.घड़ी_limits[dcn3_01_soc.num_states] = dcn3_01_soc.घड़ी_limits[dcn3_01_soc.num_states - 1];
			dcn3_01_soc.घड़ी_limits[dcn3_01_soc.num_states].state = dcn3_01_soc.num_states;
		पूर्ण
	पूर्ण

	dcn3_01_soc.dispclk_dppclk_vco_speed_mhz = dc->clk_mgr->dentist_vco_freq_khz / 1000.0;
	dc->dml.soc.dispclk_dppclk_vco_speed_mhz = dc->clk_mgr->dentist_vco_freq_khz / 1000.0;

	dml_init_instance(&dc->dml, &dcn3_01_soc, &dcn3_01_ip, DML_PROJECT_DCN30);
पूर्ण

अटल व्योम calculate_wm_set_क्रम_vlevel(
		पूर्णांक vlevel,
		काष्ठा wm_range_table_entry *table_entry,
		काष्ठा dcn_watermarks *wm_set,
		काष्ठा display_mode_lib *dml,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt)
अणु
	द्विगुन dram_घड़ी_change_latency_cached = dml->soc.dram_घड़ी_change_latency_us;

	ASSERT(vlevel < dml->soc.num_states);
	/* only pipe 0 is पढ़ो क्रम voltage and dcf/soc घड़ीs */
	pipes[0].clks_cfg.voltage = vlevel;
	pipes[0].clks_cfg.dcfclk_mhz = dml->soc.घड़ी_limits[vlevel].dcfclk_mhz;
	pipes[0].clks_cfg.socclk_mhz = dml->soc.घड़ी_limits[vlevel].socclk_mhz;

	dml->soc.dram_घड़ी_change_latency_us = table_entry->pstate_latency_us;
	dml->soc.sr_निकास_समय_us = table_entry->sr_निकास_समय_us;
	dml->soc.sr_enter_plus_निकास_समय_us = table_entry->sr_enter_plus_निकास_समय_us;

	wm_set->urgent_ns = get_wm_urgent(dml, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.cstate_enter_plus_निकास_ns = get_wm_stutter_enter_निकास(dml, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.cstate_निकास_ns = get_wm_stutter_निकास(dml, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.pstate_change_ns = get_wm_dram_घड़ी_change(dml, pipes, pipe_cnt) * 1000;
	wm_set->pte_meta_urgent_ns = get_wm_memory_trip(dml, pipes, pipe_cnt) * 1000;
	wm_set->frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(dml, pipes, pipe_cnt) * 1000;
	wm_set->frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(dml, pipes, pipe_cnt) * 1000;
	wm_set->urgent_latency_ns = get_urgent_latency(dml, pipes, pipe_cnt) * 1000;
	dml->soc.dram_घड़ी_change_latency_us = dram_घड़ी_change_latency_cached;

पूर्ण

अटल व्योम dcn301_calculate_wm_and_dlg(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक pipe_cnt,
		पूर्णांक vlevel_req)
अणु
	पूर्णांक i, pipe_idx;
	पूर्णांक vlevel, vlevel_max;
	काष्ठा wm_range_table_entry *table_entry;
	काष्ठा clk_bw_params *bw_params = dc->clk_mgr->bw_params;

	ASSERT(bw_params);

	vlevel_max = bw_params->clk_table.num_entries - 1;

	/* WM Set D */
	table_entry = &bw_params->wm_table.entries[WM_D];
	अगर (table_entry->wm_type == WM_TYPE_RETRAINING)
		vlevel = 0;
	अन्यथा
		vlevel = vlevel_max;
	calculate_wm_set_क्रम_vlevel(vlevel, table_entry, &context->bw_ctx.bw.dcn.watermarks.d,
						&context->bw_ctx.dml, pipes, pipe_cnt);
	/* WM Set C */
	table_entry = &bw_params->wm_table.entries[WM_C];
	vlevel = min(max(vlevel_req, 2), vlevel_max);
	calculate_wm_set_क्रम_vlevel(vlevel, table_entry, &context->bw_ctx.bw.dcn.watermarks.c,
						&context->bw_ctx.dml, pipes, pipe_cnt);
	/* WM Set B */
	table_entry = &bw_params->wm_table.entries[WM_B];
	vlevel = min(max(vlevel_req, 1), vlevel_max);
	calculate_wm_set_क्रम_vlevel(vlevel, table_entry, &context->bw_ctx.bw.dcn.watermarks.b,
						&context->bw_ctx.dml, pipes, pipe_cnt);

	/* WM Set A */
	table_entry = &bw_params->wm_table.entries[WM_A];
	vlevel = min(vlevel_req, vlevel_max);
	calculate_wm_set_क्रम_vlevel(vlevel, table_entry, &context->bw_ctx.bw.dcn.watermarks.a,
						&context->bw_ctx.dml, pipes, pipe_cnt);

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
पूर्ण

अटल काष्ठा resource_funcs dcn301_res_pool_funcs = अणु
	.destroy = dcn301_destroy_resource_pool,
	.link_enc_create = dcn301_link_encoder_create,
	.panel_cntl_create = dcn301_panel_cntl_create,
	.validate_bandwidth = dcn30_validate_bandwidth,
	.calculate_wm_and_dlg = dcn301_calculate_wm_and_dlg,
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
	.update_bw_bounding_box = dcn301_update_bw_bounding_box
पूर्ण;

अटल bool dcn301_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा dcn301_resource_pool *pool)
अणु
	पूर्णांक i, j;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा irq_service_init_data init_data;
	uपूर्णांक32_t pipe_fuses = पढ़ो_pipe_fuses(ctx);
	uपूर्णांक32_t num_pipes = 0;

	DC_LOGGER_INIT(dc->ctx->logger);

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap_dcn301;

	pool->base.funcs = &dcn301_res_pool_funcs;

	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;
	pool->base.pipe_count = pool->base.res_cap->num_timing_generator;
	pool->base.mpcc_count = pool->base.res_cap->num_timing_generator;
	dc->caps.max_करोwnscale_ratio = 600;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 5; /*1.4 w/a enabled by शेष*/
	dc->caps.max_cursor_size = 256;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.dmdata_alloc_size = 2048;
	dc->caps.max_slave_planes = 1;
	dc->caps.max_slave_yuv_planes = 1;
	dc->caps.max_slave_rgb_planes = 1;
	dc->caps.is_apu = true;
	dc->caps.post_blend_color_processing = true;
	dc->caps.क्रमce_dp_tps4_क्रम_cp2520 = true;
	dc->caps.extended_aux_समयout_support = true;
#अगर_घोषित CONFIG_DRM_AMD_DC_DMUB
	dc->caps.dmcub_support = true;
#पूर्ण_अगर

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
	// no OGAM ROM on DCN301
	dc->caps.color.dpp.ogam_rom_caps.srgb = 0;
	dc->caps.color.dpp.ogam_rom_caps.bt2020 = 0;
	dc->caps.color.dpp.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.dpp.ogam_rom_caps.pq = 0;
	dc->caps.color.dpp.ogam_rom_caps.hlg = 0;
	dc->caps.color.dpp.ocsc = 0;

	dc->caps.color.mpc.gamut_remap = 1;
	dc->caps.color.mpc.num_3dluts = pool->base.res_cap->num_mpc_3dlut; //2
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
	pool->base.घड़ी_sources[DCN301_CLK_SRC_PLL0] =
			dcn301_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL0,
				&clk_src_regs[0], false);
	pool->base.घड़ी_sources[DCN301_CLK_SRC_PLL1] =
			dcn301_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL1,
				&clk_src_regs[1], false);
	pool->base.घड़ी_sources[DCN301_CLK_SRC_PLL2] =
			dcn301_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL2,
				&clk_src_regs[2], false);
	pool->base.घड़ी_sources[DCN301_CLK_SRC_PLL3] =
			dcn301_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL3,
				&clk_src_regs[3], false);

	pool->base.clk_src_count = DCN301_CLK_SRC_TOTAL;

	/* toकरो: not reuse phy_pll रेजिस्टरs */
	pool->base.dp_घड़ी_source =
			dcn301_घड़ी_source_create(ctx, ctx->dc_bios,
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
	pool->base.dccg = dccg301_create(ctx, &dccg_regs, &dccg_shअगरt, &dccg_mask);
	अगर (pool->base.dccg == शून्य) अणु
		dm_error("DC: failed to create dccg!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	init_soc_bounding_box(dc, pool);

	अगर (!dc->debug.disable_pplib_wm_range && pool->base.pp_smu->nv_funcs.set_wm_ranges)
		set_wm_ranges(pool->base.pp_smu, &dcn3_01_soc);

	num_pipes = dcn3_01_ip.max_num_dpp;

	क्रम (i = 0; i < dcn3_01_ip.max_num_dpp; i++)
		अगर (pipe_fuses & 1 << i)
			num_pipes--;
	dcn3_01_ip.max_num_dpp = num_pipes;
	dcn3_01_ip.max_num_otg = num_pipes;


	dml_init_instance(&dc->dml, &dcn3_01_soc, &dcn3_01_ip, DML_PROJECT_DCN30);

	/* IRQ */
	init_data.ctx = dc->ctx;
	pool->base.irqs = dal_irq_service_dcn30_create(&init_data);
	अगर (!pool->base.irqs)
		जाओ create_fail;

	/* HUBBUB */
	pool->base.hubbub = dcn301_hubbub_create(ctx);
	अगर (pool->base.hubbub == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create hubbub!\n");
		जाओ create_fail;
	पूर्ण

	j = 0;
	/* HUBPs, DPPs, OPPs and TGs */
	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु

		/* अगर pipe is disabled, skip instance of HW pipe,
		 * i.e, skip ASIC रेजिस्टर instance
		 */
		अगर ((pipe_fuses & (1 << i)) != 0) अणु
			DC_LOG_DEBUG("%s: fusing pipe %d\n", __func__, i);
			जारी;
		पूर्ण

		pool->base.hubps[j] = dcn301_hubp_create(ctx, i);
		अगर (pool->base.hubps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create hubps!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.dpps[j] = dcn301_dpp_create(ctx, i);
		अगर (pool->base.dpps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create dpps!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.opps[j] = dcn301_opp_create(ctx, i);
		अगर (pool->base.opps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.timing_generators[j] = dcn301_timing_generator_create(ctx, i);
		अगर (pool->base.timing_generators[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ create_fail;
		पूर्ण
		j++;
	पूर्ण
	pool->base.timing_generator_count = j;
	pool->base.pipe_count = j;
	pool->base.mpcc_count = j;

	/* ABM (or ABMs क्रम NV2x) */
	/* TODO: */
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
	pool->base.mpc = dcn301_mpc_create(ctx, pool->base.mpcc_count, pool->base.res_cap->num_mpc_3dlut);
	अगर (pool->base.mpc == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mpc!\n");
		जाओ create_fail;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_dsc; i++) अणु
		pool->base.dscs[i] = dcn301_dsc_create(ctx, i);
		अगर (pool->base.dscs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create display stream compressor %d!\n", i);
			जाओ create_fail;
		पूर्ण
	पूर्ण

	/* DWB and MMHUBBUB */
	अगर (!dcn301_dwbc_create(ctx, &pool->base)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create dwbc!\n");
		जाओ create_fail;
	पूर्ण

	अगर (!dcn301_mmhubbub_create(ctx, &pool->base)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mcif_wb!\n");
		जाओ create_fail;
	पूर्ण

	/* AUX and I2C */
	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dcn301_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dcn301_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create hw i2c!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	/* Audio, Stream Encoders including HPO and भव, MPC 3D LUTs */
	अगर (!resource_स्थिरruct(num_भव_links, dc, &pool->base,
			(!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment) ?
			&res_create_funcs : &res_create_maximus_funcs)))
			जाओ create_fail;

	/* HW Sequencer and Plane caps */
	dcn301_hw_sequencer_स्थिरruct(dc);

	dc->caps.max_planes =  pool->base.pipe_count;

	क्रम (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	dc->cap_funcs = cap_funcs;

	वापस true;

create_fail:

	dcn301_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dcn301_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc)
अणु
	काष्ठा dcn301_resource_pool *pool =
		kzalloc(माप(काष्ठा dcn301_resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dcn301_resource_स्थिरruct(init_data->num_भव_links, dc, pool))
		वापस &pool->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(pool);
	वापस शून्य;
पूर्ण
