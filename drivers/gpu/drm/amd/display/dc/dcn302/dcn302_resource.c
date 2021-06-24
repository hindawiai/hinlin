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

#समावेश "dcn302_init.h"
#समावेश "dcn302_resource.h"
#समावेश "dcn302_dccg.h"
#समावेश "irq/dcn302/irq_service_dcn302.h"

#समावेश "dcn30/dcn30_dio_link_encoder.h"
#समावेश "dcn30/dcn30_dio_stream_encoder.h"
#समावेश "dcn30/dcn30_dwb.h"
#समावेश "dcn30/dcn30_dpp.h"
#समावेश "dcn30/dcn30_hubbub.h"
#समावेश "dcn30/dcn30_hubp.h"
#समावेश "dcn30/dcn30_mmhubbub.h"
#समावेश "dcn30/dcn30_mpc.h"
#समावेश "dcn30/dcn30_opp.h"
#समावेश "dcn30/dcn30_optc.h"
#समावेश "dcn30/dcn30_resource.h"

#समावेश "dcn20/dcn20_dsc.h"
#समावेश "dcn20/dcn20_resource.h"

#समावेश "dcn10/dcn10_resource.h"

#समावेश "dce/dce_abm.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "dce/dce_i2c_hw.h"
#समावेश "dce/dce_panel_cntl.h"
#समावेश "dce/dmub_abm.h"
#समावेश "dce/dmub_psr.h"
#समावेश "clk_mgr.h"

#समावेश "hw_sequencer_private.h"
#समावेश "reg_helper.h"
#समावेश "resource.h"
#समावेश "vm_helper.h"

#समावेश "dimgrey_cavefish_ip_offset.h"
#समावेश "dcn/dcn_3_0_2_offset.h"
#समावेश "dcn/dcn_3_0_2_sh_mask.h"
#समावेश "dcn/dpcs_3_0_0_offset.h"
#समावेश "dcn/dpcs_3_0_0_sh_mask.h"
#समावेश "nbio/nbio_7_4_offset.h"
#समावेश "amdgpu_socbb.h"

#घोषणा DC_LOGGER_INIT(logger)

काष्ठा _vcs_dpi_ip_params_st dcn3_02_ip = अणु
		.use_min_dcfclk = 0,
		.clamp_min_dcfclk = 0,
		.odm_capable = 1,
		.gpuvm_enable = 1,
		.hostvm_enable = 0,
		.gpuvm_max_page_table_levels = 4,
		.hostvm_max_page_table_levels = 4,
		.hostvm_cached_page_table_levels = 0,
		.pte_group_size_bytes = 2048,
		.num_dsc = 5,
		.rob_buffer_size_kbytes = 184,
		.det_buffer_size_kbytes = 184,
		.dpte_buffer_size_in_pte_reqs_luma = 64,
		.dpte_buffer_size_in_pte_reqs_chroma = 34,
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
		.max_num_otg = 5,
		.max_num_dpp = 5,
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
		.max_num_hdmi_frl_outमाला_दो = 1,
		.odm_combine_4to1_supported = true,

		.xfc_supported = false,
		.xfc_fill_bw_overhead_percent = 10.0,
		.xfc_fill_स्थिरant_bytes = 0,
		.gfx7_compat_tiling_supported = 0,
		.number_of_cursors = 1,
पूर्ण;

काष्ठा _vcs_dpi_soc_bounding_box_st dcn3_02_soc = अणु
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
		.round_trip_ping_latency_dcfclk_cycles = 156,
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

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_drv = अणु
		.disable_dmcu = true,
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
		.use_max_lb = true
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_diags = अणु
		.disable_dmcu = true,
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
		.enable_tri_buf = true,
		.disable_psr = true,
		.use_max_lb = true
पूर्ण;

क्रमागत dcn302_clk_src_array_id अणु
	DCN302_CLK_SRC_PLL0,
	DCN302_CLK_SRC_PLL1,
	DCN302_CLK_SRC_PLL2,
	DCN302_CLK_SRC_PLL3,
	DCN302_CLK_SRC_PLL4,
	DCN302_CLK_SRC_TOTAL
पूर्ण;

अटल स्थिर काष्ठा resource_caps res_cap_dcn302 = अणु
		.num_timing_generator = 5,
		.num_opp = 5,
		.num_video_plane = 5,
		.num_audio = 5,
		.num_stream_encoder = 5,
		.num_dwb = 1,
		.num_ddc = 5,
		.num_vmid = 16,
		.num_mpc_3dlut = 2,
		.num_dsc = 5,
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
		16,
		16
पूर्ण;

/* NBIO */
#घोषणा NBIO_BASE_INNER(seg) \
		NBIO_BASE__INST0_SEG ## seg

#घोषणा NBIO_BASE(seg) \
		NBIO_BASE_INNER(seg)

#घोषणा NBIO_SR(reg_name)\
		.reg_name = NBIO_BASE(mm ## reg_name ## _BASE_IDX) + \
		mm ## reg_name

/* DCN */
#अघोषित BASE_INNER
#घोषणा BASE_INNER(seg) DCN_BASE__INST0_SEG ## seg

#घोषणा BASE(seg) BASE_INNER(seg)

#घोषणा SR(reg_name)\
		.reg_name = BASE(mm ## reg_name ## _BASE_IDX) + mm ## reg_name

#घोषणा SF(reg_name, field_name, post_fix)\
		.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा SRI(reg_name, block, id)\
		.reg_name = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + mm ## block ## id ## _ ## reg_name

#घोषणा SRI2(reg_name, block, id)\
		.reg_name = BASE(mm ## reg_name ## _BASE_IDX) + mm ## reg_name

#घोषणा SRII(reg_name, block, id)\
		.reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
		mm ## block ## id ## _ ## reg_name

#घोषणा DCCG_SRII(reg_name, block, id)\
		.block ## _ ## reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
		mm ## block ## id ## _ ## reg_name

#घोषणा VUPDATE_SRII(reg_name, block, id)\
		.reg_name[id] = BASE(mm ## reg_name ## _ ## block ## id ## _BASE_IDX) + \
		mm ## reg_name ## _ ## block ## id

#घोषणा SRII_DWB(reg_name, temp_name, block, id)\
		.reg_name[id] = BASE(mm ## block ## id ## _ ## temp_name ## _BASE_IDX) + \
		mm ## block ## id ## _ ## temp_name

#घोषणा SRII_MPC_RMU(reg_name, block, id)\
		.RMU##_##reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
		mm ## block ## id ## _ ## reg_name

अटल स्थिर काष्ठा dcn_hubbub_रेजिस्टरs hubbub_reg = अणु
		HUBBUB_REG_LIST_DCN30(0)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_shअगरt hubbub_shअगरt = अणु
		HUBBUB_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_mask hubbub_mask = अणु
		HUBBUB_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

#घोषणा vmid_regs(id)\
		[id] = अणु DCN20_VMID_REG_LIST(id) पूर्ण

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

अटल काष्ठा hubbub *dcn302_hubbub_create(काष्ठा dc_context *ctx)
अणु
	पूर्णांक i;

	काष्ठा dcn20_hubbub *hubbub3 = kzalloc(माप(काष्ठा dcn20_hubbub), GFP_KERNEL);

	अगर (!hubbub3)
		वापस शून्य;

	hubbub3_स्थिरruct(hubbub3, ctx, &hubbub_reg, &hubbub_shअगरt, &hubbub_mask);

	क्रम (i = 0; i < res_cap_dcn302.num_vmid; i++) अणु
		काष्ठा dcn20_vmid *vmid = &hubbub3->vmid[i];

		vmid->ctx = ctx;

		vmid->regs = &vmid_regs[i];
		vmid->shअगरts = &vmid_shअगरts;
		vmid->masks = &vmid_masks;
	पूर्ण

	वापस &hubbub3->base;
पूर्ण

#घोषणा vpg_regs(id)\
		[id] = अणु VPG_DCN3_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dcn30_vpg_रेजिस्टरs vpg_regs[] = अणु
		vpg_regs(0),
		vpg_regs(1),
		vpg_regs(2),
		vpg_regs(3),
		vpg_regs(4),
		vpg_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dcn30_vpg_shअगरt vpg_shअगरt = अणु
		DCN3_VPG_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_vpg_mask vpg_mask = अणु
		DCN3_VPG_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा vpg *dcn302_vpg_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn30_vpg *vpg3 = kzalloc(माप(काष्ठा dcn30_vpg), GFP_KERNEL);

	अगर (!vpg3)
		वापस शून्य;

	vpg3_स्थिरruct(vpg3, ctx, inst, &vpg_regs[inst], &vpg_shअगरt, &vpg_mask);

	वापस &vpg3->base;
पूर्ण

#घोषणा afmt_regs(id)\
		[id] = अणु AFMT_DCN3_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dcn30_afmt_रेजिस्टरs afmt_regs[] = अणु
		afmt_regs(0),
		afmt_regs(1),
		afmt_regs(2),
		afmt_regs(3),
		afmt_regs(4),
		afmt_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dcn30_afmt_shअगरt afmt_shअगरt = अणु
		DCN3_AFMT_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_afmt_mask afmt_mask = अणु
		DCN3_AFMT_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा afmt *dcn302_afmt_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn30_afmt *afmt3 = kzalloc(माप(काष्ठा dcn30_afmt), GFP_KERNEL);

	अगर (!afmt3)
		वापस शून्य;

	afmt3_स्थिरruct(afmt3, ctx, inst, &afmt_regs[inst], &afmt_shअगरt, &afmt_mask);

	वापस &afmt3->base;
पूर्ण

#घोषणा audio_regs(id)\
		[id] = अणु AUD_COMMON_REG_LIST(id) पूर्ण

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

अटल काष्ठा audio *dcn302_create_audio(काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst, &audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

#घोषणा stream_enc_regs(id)\
		[id] = अणु SE_DCN3_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs stream_enc_regs[] = अणु
		stream_enc_regs(0),
		stream_enc_regs(1),
		stream_enc_regs(2),
		stream_enc_regs(3),
		stream_enc_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल काष्ठा stream_encoder *dcn302_stream_encoder_create(क्रमागत engine_id eng_id, काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn10_stream_encoder *enc1;
	काष्ठा vpg *vpg;
	काष्ठा afmt *afmt;
	पूर्णांक vpg_inst;
	पूर्णांक afmt_inst;

	/* Mapping of VPG, AFMT, DME रेजिस्टर blocks to DIO block instance */
	अगर (eng_id <= ENGINE_ID_DIGE) अणु
		vpg_inst = eng_id;
		afmt_inst = eng_id;
	पूर्ण अन्यथा
		वापस शून्य;

	enc1 = kzalloc(माप(काष्ठा dcn10_stream_encoder), GFP_KERNEL);
	vpg = dcn302_vpg_create(ctx, vpg_inst);
	afmt = dcn302_afmt_create(ctx, afmt_inst);

	अगर (!enc1 || !vpg || !afmt)
		वापस शून्य;

	dcn30_dio_stream_encoder_स्थिरruct(enc1, ctx, ctx->dc_bios, eng_id, vpg, afmt, &stream_enc_regs[eng_id],
			&se_shअगरt, &se_mask);

	वापस &enc1->base;
पूर्ण

#घोषणा clk_src_regs(index, pllid)\
		[index] = अणु CS_COMMON_REG_LIST_DCN3_02(index, pllid) पूर्ण

अटल स्थिर काष्ठा dce110_clk_src_regs clk_src_regs[] = अणु
		clk_src_regs(0, A),
		clk_src_regs(1, B),
		clk_src_regs(2, C),
		clk_src_regs(3, D),
		clk_src_regs(4, E)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_shअगरt cs_shअगरt = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_mask cs_mask = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
पूर्ण;

अटल काष्ठा घड़ी_source *dcn302_घड़ी_source_create(काष्ठा dc_context *ctx, काष्ठा dc_bios *bios,
		क्रमागत घड़ी_source_id id, स्थिर काष्ठा dce110_clk_src_regs *regs, bool dp_clk_src)
अणु
	काष्ठा dce110_clk_src *clk_src = kzalloc(माप(काष्ठा dce110_clk_src), GFP_KERNEL);

	अगर (!clk_src)
		वापस शून्य;

	अगर (dcn3_clk_src_स्थिरruct(clk_src, ctx, bios, id, regs, &cs_shअगरt, &cs_mask)) अणु
		clk_src->base.dp_clk_src = dp_clk_src;
		वापस &clk_src->base;
	पूर्ण

	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCN302_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCN302_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCN302_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा dce_hwseq *dcn302_hwseq_create(काष्ठा dc_context *ctx)
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

#घोषणा hubp_regs(id)\
		[id] = अणु HUBP_REG_LIST_DCN30(id) पूर्ण

अटल स्थिर काष्ठा dcn_hubp2_रेजिस्टरs hubp_regs[] = अणु
		hubp_regs(0),
		hubp_regs(1),
		hubp_regs(2),
		hubp_regs(3),
		hubp_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_shअगरt hubp_shअगरt = अणु
		HUBP_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_mask hubp_mask = अणु
		HUBP_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल काष्ठा hubp *dcn302_hubp_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_hubp *hubp2 = kzalloc(माप(काष्ठा dcn20_hubp), GFP_KERNEL);

	अगर (!hubp2)
		वापस शून्य;

	अगर (hubp3_स्थिरruct(hubp2, ctx, inst, &hubp_regs[inst], &hubp_shअगरt, &hubp_mask))
		वापस &hubp2->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(hubp2);
	वापस शून्य;
पूर्ण

#घोषणा dpp_regs(id)\
		[id] = अणु DPP_REG_LIST_DCN30(id) पूर्ण

अटल स्थिर काष्ठा dcn3_dpp_रेजिस्टरs dpp_regs[] = अणु
		dpp_regs(0),
		dpp_regs(1),
		dpp_regs(2),
		dpp_regs(3),
		dpp_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dcn3_dpp_shअगरt tf_shअगरt = अणु
		DPP_REG_LIST_SH_MASK_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn3_dpp_mask tf_mask = अणु
		DPP_REG_LIST_SH_MASK_DCN30(_MASK)
पूर्ण;

अटल काष्ठा dpp *dcn302_dpp_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn3_dpp *dpp = kzalloc(माप(काष्ठा dcn3_dpp), GFP_KERNEL);

	अगर (!dpp)
		वापस शून्य;

	अगर (dpp3_स्थिरruct(dpp, ctx, inst, &dpp_regs[inst], &tf_shअगरt, &tf_mask))
		वापस &dpp->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(dpp);
	वापस शून्य;
पूर्ण

#घोषणा opp_regs(id)\
		[id] = अणु OPP_REG_LIST_DCN30(id) पूर्ण

अटल स्थिर काष्ठा dcn20_opp_रेजिस्टरs opp_regs[] = अणु
		opp_regs(0),
		opp_regs(1),
		opp_regs(2),
		opp_regs(3),
		opp_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dcn20_opp_shअगरt opp_shअगरt = अणु
		OPP_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn20_opp_mask opp_mask = अणु
		OPP_MASK_SH_LIST_DCN20(_MASK)
पूर्ण;

अटल काष्ठा output_pixel_processor *dcn302_opp_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_opp *opp = kzalloc(माप(काष्ठा dcn20_opp), GFP_KERNEL);

	अगर (!opp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn20_opp_स्थिरruct(opp, ctx, inst, &opp_regs[inst], &opp_shअगरt, &opp_mask);
	वापस &opp->base;
पूर्ण

#घोषणा optc_regs(id)\
		[id] = अणु OPTC_COMMON_REG_LIST_DCN3_0(id) पूर्ण

अटल स्थिर काष्ठा dcn_optc_रेजिस्टरs optc_regs[] = अणु
		optc_regs(0),
		optc_regs(1),
		optc_regs(2),
		optc_regs(3),
		optc_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_shअगरt optc_shअगरt = अणु
		OPTC_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_mask optc_mask = अणु
		OPTC_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल काष्ठा timing_generator *dcn302_timing_generator_create(काष्ठा dc_context *ctx, uपूर्णांक32_t instance)
अणु
	काष्ठा optc *tgn10 = kzalloc(माप(काष्ठा optc), GFP_KERNEL);

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

अटल स्थिर काष्ठा dcn30_mpc_रेजिस्टरs mpc_regs = अणु
		MPC_REG_LIST_DCN3_0(0),
		MPC_REG_LIST_DCN3_0(1),
		MPC_REG_LIST_DCN3_0(2),
		MPC_REG_LIST_DCN3_0(3),
		MPC_REG_LIST_DCN3_0(4),
		MPC_OUT_MUX_REG_LIST_DCN3_0(0),
		MPC_OUT_MUX_REG_LIST_DCN3_0(1),
		MPC_OUT_MUX_REG_LIST_DCN3_0(2),
		MPC_OUT_MUX_REG_LIST_DCN3_0(3),
		MPC_OUT_MUX_REG_LIST_DCN3_0(4),
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

अटल काष्ठा mpc *dcn302_mpc_create(काष्ठा dc_context *ctx, पूर्णांक num_mpcc, पूर्णांक num_rmu)
अणु
	काष्ठा dcn30_mpc *mpc30 = kzalloc(माप(काष्ठा dcn30_mpc), GFP_KERNEL);

	अगर (!mpc30)
		वापस शून्य;

	dcn30_mpc_स्थिरruct(mpc30, ctx, &mpc_regs, &mpc_shअगरt, &mpc_mask, num_mpcc, num_rmu);

	वापस &mpc30->base;
पूर्ण

#घोषणा dsc_regsDCN20(id)\
[id] = अणु DSC_REG_LIST_DCN20(id) पूर्ण

अटल स्थिर काष्ठा dcn20_dsc_रेजिस्टरs dsc_regs[] = अणु
		dsc_regsDCN20(0),
		dsc_regsDCN20(1),
		dsc_regsDCN20(2),
		dsc_regsDCN20(3),
		dsc_regsDCN20(4)
पूर्ण;

अटल स्थिर काष्ठा dcn20_dsc_shअगरt dsc_shअगरt = अणु
		DSC_REG_LIST_SH_MASK_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn20_dsc_mask dsc_mask = अणु
		DSC_REG_LIST_SH_MASK_DCN20(_MASK)
पूर्ण;

अटल काष्ठा display_stream_compressor *dcn302_dsc_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_dsc *dsc = kzalloc(माप(काष्ठा dcn20_dsc), GFP_KERNEL);

	अगर (!dsc) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dsc2_स्थिरruct(dsc, ctx, inst, &dsc_regs[inst], &dsc_shअगरt, &dsc_mask);
	वापस &dsc->base;
पूर्ण

#घोषणा dwbc_regs_dcn3(id)\
[id] = अणु DWBC_COMMON_REG_LIST_DCN30(id) पूर्ण

अटल स्थिर काष्ठा dcn30_dwbc_रेजिस्टरs dwbc30_regs[] = अणु
		dwbc_regs_dcn3(0)
पूर्ण;

अटल स्थिर काष्ठा dcn30_dwbc_shअगरt dwbc30_shअगरt = अणु
		DWBC_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_dwbc_mask dwbc30_mask = अणु
		DWBC_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल bool dcn302_dwbc_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	uपूर्णांक32_t pipe_count = pool->res_cap->num_dwb;

	क्रम (i = 0; i < pipe_count; i++) अणु
		काष्ठा dcn30_dwbc *dwbc30 = kzalloc(माप(काष्ठा dcn30_dwbc), GFP_KERNEL);

		अगर (!dwbc30) अणु
			dm_error("DC: failed to create dwbc30!\n");
			वापस false;
		पूर्ण

		dcn30_dwbc_स्थिरruct(dwbc30, ctx, &dwbc30_regs[i], &dwbc30_shअगरt, &dwbc30_mask, i);

		pool->dwbc[i] = &dwbc30->base;
	पूर्ण
	वापस true;
पूर्ण

#घोषणा mcअगर_wb_regs_dcn3(id)\
[id] = अणु MCIF_WB_COMMON_REG_LIST_DCN30(id) पूर्ण

अटल स्थिर काष्ठा dcn30_mmhubbub_रेजिस्टरs mcअगर_wb30_regs[] = अणु
		mcअगर_wb_regs_dcn3(0)
पूर्ण;

अटल स्थिर काष्ठा dcn30_mmhubbub_shअगरt mcअगर_wb30_shअगरt = अणु
		MCIF_WB_COMMON_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn30_mmhubbub_mask mcअगर_wb30_mask = अणु
		MCIF_WB_COMMON_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल bool dcn302_mmhubbub_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	uपूर्णांक32_t pipe_count = pool->res_cap->num_dwb;

	क्रम (i = 0; i < pipe_count; i++) अणु
		काष्ठा dcn30_mmhubbub *mcअगर_wb30 = kzalloc(माप(काष्ठा dcn30_mmhubbub), GFP_KERNEL);

		अगर (!mcअगर_wb30) अणु
			dm_error("DC: failed to create mcif_wb30!\n");
			वापस false;
		पूर्ण

		dcn30_mmhubbub_स्थिरruct(mcअगर_wb30, ctx, &mcअगर_wb30_regs[i], &mcअगर_wb30_shअगरt, &mcअगर_wb30_mask, i);

		pool->mcअगर_wb[i] = &mcअगर_wb30->base;
	पूर्ण
	वापस true;
पूर्ण

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
		aux_engine_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt aux_shअगरt = अणु
		DCN_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
		DCN_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा dce_aux *dcn302_aux_engine_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा aux_engine_dce110 *aux_engine = kzalloc(माप(काष्ठा aux_engine_dce110), GFP_KERNEL);

	अगर (!aux_engine)
		वापस शून्य;

	dce110_aux_engine_स्थिरruct(aux_engine, ctx, inst, SW_AUX_TIMEOUT_PERIOD_MULTIPLIER * AUX_TIMEOUT_PERIOD,
			&aux_engine_regs[inst], &aux_mask, &aux_shअगरt, ctx->dc->caps.extended_aux_समयout_support);

	वापस &aux_engine->base;
पूर्ण

#घोषणा i2c_inst_regs(id) अणु I2C_HW_ENGINE_COMMON_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dce_i2c_रेजिस्टरs i2c_hw_regs[] = अणु
		i2c_inst_regs(1),
		i2c_inst_regs(2),
		i2c_inst_regs(3),
		i2c_inst_regs(4),
		i2c_inst_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_shअगरt i2c_shअगरts = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_mask i2c_masks = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(_MASK)
पूर्ण;

अटल काष्ठा dce_i2c_hw *dcn302_i2c_hw_create(काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dce_i2c_hw *dce_i2c_hw = kzalloc(माप(काष्ठा dce_i2c_hw), GFP_KERNEL);

	अगर (!dce_i2c_hw)
		वापस शून्य;

	dcn2_i2c_hw_स्थिरruct(dce_i2c_hw, ctx, inst, &i2c_hw_regs[inst], &i2c_shअगरts, &i2c_masks);

	वापस dce_i2c_hw;
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

#घोषणा link_regs(id, phyid)\
		[id] = अणु\
				LE_DCN3_REG_LIST(id), \
				UNIPHY_DCN2_REG_LIST(phyid), \
				DPCS_DCN2_REG_LIST(id), \
				SRI(DP_DPHY_INTERNAL_CTRL, DP, id) \
		पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs link_enc_regs[] = अणु
		link_regs(0, A),
		link_regs(1, B),
		link_regs(2, C),
		link_regs(3, D),
		link_regs(4, E)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_shअगरt le_shअगरt = अणु
		LINK_ENCODER_MASK_SH_LIST_DCN30(__SHIFT),
		DPCS_DCN2_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_mask le_mask = अणु
		LINK_ENCODER_MASK_SH_LIST_DCN30(_MASK),
		DPCS_DCN2_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा aux_regs(id)\
		[id] = अणु DCN2_AUX_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_aux_रेजिस्टरs link_enc_aux_regs[] = अणु
		aux_regs(0),
		aux_regs(1),
		aux_regs(2),
		aux_regs(3),
		aux_regs(4)
पूर्ण;

#घोषणा hpd_regs(id)\
		[id] = अणु HPD_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_hpd_रेजिस्टरs link_enc_hpd_regs[] = अणु
		hpd_regs(0),
		hpd_regs(1),
		hpd_regs(2),
		hpd_regs(3),
		hpd_regs(4)
पूर्ण;

अटल काष्ठा link_encoder *dcn302_link_encoder_create(स्थिर काष्ठा encoder_init_data *enc_init_data)
अणु
	काष्ठा dcn20_link_encoder *enc20 = kzalloc(माप(काष्ठा dcn20_link_encoder), GFP_KERNEL);

	अगर (!enc20)
		वापस शून्य;

	dcn30_link_encoder_स्थिरruct(enc20, enc_init_data, &link_enc_feature,
			&link_enc_regs[enc_init_data->transmitter], &link_enc_aux_regs[enc_init_data->channel - 1],
			&link_enc_hpd_regs[enc_init_data->hpd_source], &le_shअगरt, &le_mask);

	वापस &enc20->enc10.base;
पूर्ण

अटल स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs panel_cntl_regs[] = अणु
		अणु DCN_PANEL_CNTL_REG_LIST() पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_shअगरt panel_cntl_shअगरt = अणु
		DCE_PANEL_CNTL_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_mask panel_cntl_mask = अणु
		DCE_PANEL_CNTL_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा panel_cntl *dcn302_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
अणु
	काष्ठा dce_panel_cntl *panel_cntl = kzalloc(माप(काष्ठा dce_panel_cntl), GFP_KERNEL);

	अगर (!panel_cntl)
		वापस शून्य;

	dce_panel_cntl_स्थिरruct(panel_cntl, init_data, &panel_cntl_regs[init_data->inst],
			&panel_cntl_shअगरt, &panel_cntl_mask);

	वापस &panel_cntl->base;
पूर्ण

अटल व्योम पढ़ो_dce_straps(काष्ठा dc_context *ctx, काष्ठा resource_straps *straps)
अणु
	generic_reg_get(ctx, mmDC_PINSTRAPS + BASE(mmDC_PINSTRAPS_BASE_IDX),
			FN(DC_PINSTRAPS, DC_PINSTRAPS_AUDIO), &straps->dc_pinstraps_audio);
पूर्ण

अटल स्थिर काष्ठा resource_create_funcs res_create_funcs = अणु
		.पढ़ो_dce_straps = पढ़ो_dce_straps,
		.create_audio = dcn302_create_audio,
		.create_stream_encoder = dcn302_stream_encoder_create,
		.create_hwseq = dcn302_hwseq_create,
पूर्ण;

अटल स्थिर काष्ठा resource_create_funcs res_create_maximus_funcs = अणु
		.पढ़ो_dce_straps = शून्य,
		.create_audio = शून्य,
		.create_stream_encoder = शून्य,
		.create_hwseq = dcn302_hwseq_create,
पूर्ण;

अटल bool is_soc_bounding_box_valid(काष्ठा dc *dc)
अणु
	uपूर्णांक32_t hw_पूर्णांकernal_rev = dc->ctx->asic_id.hw_पूर्णांकernal_rev;

	अगर (ASICREV_IS_DIMGREY_CAVEFISH_P(hw_पूर्णांकernal_rev))
		वापस true;

	वापस false;
पूर्ण

अटल bool init_soc_bounding_box(काष्ठा dc *dc,  काष्ठा resource_pool *pool)
अणु
	काष्ठा _vcs_dpi_soc_bounding_box_st *loaded_bb = &dcn3_02_soc;
	काष्ठा _vcs_dpi_ip_params_st *loaded_ip = &dcn3_02_ip;

	DC_LOGGER_INIT(dc->ctx->logger);

	अगर (!is_soc_bounding_box_valid(dc)) अणु
		DC_LOG_ERROR("%s: not valid soc bounding box/n", __func__);
		वापस false;
	पूर्ण

	loaded_ip->max_num_otg = pool->pipe_count;
	loaded_ip->max_num_dpp = pool->pipe_count;
	loaded_ip->clamp_min_dcfclk = dc->config.clamp_min_dcfclk;
	dcn20_patch_bounding_box(dc, loaded_bb);
	वापस true;
पूर्ण

अटल व्योम dcn302_resource_deकाष्ठा(काष्ठा resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pool->stream_enc_count; i++) अणु
		अगर (pool->stream_enc[i] != शून्य) अणु
			अगर (pool->stream_enc[i]->vpg != शून्य) अणु
				kमुक्त(DCN30_VPG_FROM_VPG(pool->stream_enc[i]->vpg));
				pool->stream_enc[i]->vpg = शून्य;
			पूर्ण
			अगर (pool->stream_enc[i]->afmt != शून्य) अणु
				kमुक्त(DCN30_AFMT_FROM_AFMT(pool->stream_enc[i]->afmt));
				pool->stream_enc[i]->afmt = शून्य;
			पूर्ण
			kमुक्त(DCN10STRENC_FROM_STRENC(pool->stream_enc[i]));
			pool->stream_enc[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_dsc; i++) अणु
		अगर (pool->dscs[i] != शून्य)
			dcn20_dsc_destroy(&pool->dscs[i]);
	पूर्ण

	अगर (pool->mpc != शून्य) अणु
		kमुक्त(TO_DCN20_MPC(pool->mpc));
		pool->mpc = शून्य;
	पूर्ण

	अगर (pool->hubbub != शून्य) अणु
		kमुक्त(pool->hubbub);
		pool->hubbub = शून्य;
	पूर्ण

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		अगर (pool->dpps[i] != शून्य) अणु
			kमुक्त(TO_DCN20_DPP(pool->dpps[i]));
			pool->dpps[i] = शून्य;
		पूर्ण

		अगर (pool->hubps[i] != शून्य) अणु
			kमुक्त(TO_DCN20_HUBP(pool->hubps[i]));
			pool->hubps[i] = शून्य;
		पूर्ण

		अगर (pool->irqs != शून्य)
			dal_irq_service_destroy(&pool->irqs);
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_ddc; i++) अणु
		अगर (pool->engines[i] != शून्य)
			dce110_engine_destroy(&pool->engines[i]);
		अगर (pool->hw_i2cs[i] != शून्य) अणु
			kमुक्त(pool->hw_i2cs[i]);
			pool->hw_i2cs[i] = शून्य;
		पूर्ण
		अगर (pool->sw_i2cs[i] != शून्य) अणु
			kमुक्त(pool->sw_i2cs[i]);
			pool->sw_i2cs[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_opp; i++) अणु
		अगर (pool->opps[i] != शून्य)
			pool->opps[i]->funcs->opp_destroy(&pool->opps[i]);
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_timing_generator; i++) अणु
		अगर (pool->timing_generators[i] != शून्य)	अणु
			kमुक्त(DCN10TG_FROM_TG(pool->timing_generators[i]));
			pool->timing_generators[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_dwb; i++) अणु
		अगर (pool->dwbc[i] != शून्य) अणु
			kमुक्त(TO_DCN30_DWBC(pool->dwbc[i]));
			pool->dwbc[i] = शून्य;
		पूर्ण
		अगर (pool->mcअगर_wb[i] != शून्य) अणु
			kमुक्त(TO_DCN30_MMHUBBUB(pool->mcअगर_wb[i]));
			pool->mcअगर_wb[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->audio_count; i++) अणु
		अगर (pool->audios[i])
			dce_aud_destroy(&pool->audios[i]);
	पूर्ण

	क्रम (i = 0; i < pool->clk_src_count; i++) अणु
		अगर (pool->घड़ी_sources[i] != शून्य)
			dcn20_घड़ी_source_destroy(&pool->घड़ी_sources[i]);
	पूर्ण

	अगर (pool->dp_घड़ी_source != शून्य)
		dcn20_घड़ी_source_destroy(&pool->dp_घड़ी_source);

	क्रम (i = 0; i < pool->res_cap->num_mpc_3dlut; i++) अणु
		अगर (pool->mpc_lut[i] != शून्य) अणु
			dc_3dlut_func_release(pool->mpc_lut[i]);
			pool->mpc_lut[i] = शून्य;
		पूर्ण
		अगर (pool->mpc_shaper[i] != शून्य) अणु
			dc_transfer_func_release(pool->mpc_shaper[i]);
			pool->mpc_shaper[i] = शून्य;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		अगर (pool->multiple_abms[i] != शून्य)
			dce_abm_destroy(&pool->multiple_abms[i]);
	पूर्ण

	अगर (pool->psr != शून्य)
		dmub_psr_destroy(&pool->psr);

	अगर (pool->dccg != शून्य)
		dcn_dccg_destroy(&pool->dccg);
पूर्ण

अटल व्योम dcn302_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	dcn302_resource_deकाष्ठा(*pool);
	kमुक्त(*pool);
	*pool = शून्य;
पूर्ण

अटल व्योम dcn302_get_optimal_dcfclk_fclk_क्रम_uclk(अचिन्हित पूर्णांक uclk_mts,
		अचिन्हित पूर्णांक *optimal_dcfclk,
		अचिन्हित पूर्णांक *optimal_fclk)
अणु
	द्विगुन bw_from_dram, bw_from_dram1, bw_from_dram2;

	bw_from_dram1 = uclk_mts * dcn3_02_soc.num_chans *
		dcn3_02_soc.dram_channel_width_bytes * (dcn3_02_soc.max_avg_dram_bw_use_normal_percent / 100);
	bw_from_dram2 = uclk_mts * dcn3_02_soc.num_chans *
		dcn3_02_soc.dram_channel_width_bytes * (dcn3_02_soc.max_avg_sdp_bw_use_normal_percent / 100);

	bw_from_dram = (bw_from_dram1 < bw_from_dram2) ? bw_from_dram1 : bw_from_dram2;

	अगर (optimal_fclk)
		*optimal_fclk = bw_from_dram /
		(dcn3_02_soc.fabric_datapath_to_dcn_data_वापस_bytes * (dcn3_02_soc.max_avg_sdp_bw_use_normal_percent / 100));

	अगर (optimal_dcfclk)
		*optimal_dcfclk =  bw_from_dram /
		(dcn3_02_soc.वापस_bus_width_bytes * (dcn3_02_soc.max_avg_sdp_bw_use_normal_percent / 100));
पूर्ण

व्योम dcn302_update_bw_bounding_box(काष्ठा dc *dc, काष्ठा clk_bw_params *bw_params)
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
		dcn3_02_soc.num_chans = dc->ctx->dc_bios->vram_info.num_chans;

	अगर (dc->ctx->dc_bios->vram_info.dram_channel_width_bytes)
		dcn3_02_soc.dram_channel_width_bytes = dc->ctx->dc_bios->vram_info.dram_channel_width_bytes;

	dcn3_02_soc.dispclk_dppclk_vco_speed_mhz = dc->clk_mgr->dentist_vco_freq_khz / 1000.0;
	dc->dml.soc.dispclk_dppclk_vco_speed_mhz = dc->clk_mgr->dentist_vco_freq_khz / 1000.0;

	अगर (bw_params->clk_table.entries[0].memclk_mhz) अणु
		पूर्णांक max_dcfclk_mhz = 0, max_dispclk_mhz = 0, max_dppclk_mhz = 0, max_phyclk_mhz = 0;

		क्रम (i = 0; i < MAX_NUM_DPM_LVL; i++) अणु
			अगर (bw_params->clk_table.entries[i].dcfclk_mhz > max_dcfclk_mhz)
				max_dcfclk_mhz = bw_params->clk_table.entries[i].dcfclk_mhz;
			अगर (bw_params->clk_table.entries[i].dispclk_mhz > max_dispclk_mhz)
				max_dispclk_mhz = bw_params->clk_table.entries[i].dispclk_mhz;
			अगर (bw_params->clk_table.entries[i].dppclk_mhz > max_dppclk_mhz)
				max_dppclk_mhz = bw_params->clk_table.entries[i].dppclk_mhz;
			अगर (bw_params->clk_table.entries[i].phyclk_mhz > max_phyclk_mhz)
				max_phyclk_mhz = bw_params->clk_table.entries[i].phyclk_mhz;
		पूर्ण
		अगर (!max_dcfclk_mhz)
			max_dcfclk_mhz = dcn3_02_soc.घड़ी_limits[0].dcfclk_mhz;
		अगर (!max_dispclk_mhz)
			max_dispclk_mhz = dcn3_02_soc.घड़ी_limits[0].dispclk_mhz;
		अगर (!max_dppclk_mhz)
			max_dppclk_mhz = dcn3_02_soc.घड़ी_limits[0].dppclk_mhz;
		अगर (!max_phyclk_mhz)
			max_phyclk_mhz = dcn3_02_soc.घड़ी_limits[0].phyclk_mhz;

		अगर (max_dcfclk_mhz > dcfclk_sta_tarमाला_लो[num_dcfclk_sta_tarमाला_लो-1]) अणु
			/* If max DCFCLK is greater than the max DCFCLK STA target, insert पूर्णांकo the DCFCLK STA target array */
			dcfclk_sta_tarमाला_लो[num_dcfclk_sta_tarमाला_लो] = max_dcfclk_mhz;
			num_dcfclk_sta_tarमाला_लो++;
		पूर्ण अन्यथा अगर (max_dcfclk_mhz < dcfclk_sta_tarमाला_लो[num_dcfclk_sta_tarमाला_लो-1]) अणु
			/* If max DCFCLK is less than the max DCFCLK STA target, cap values and हटाओ duplicates */
			क्रम (i = 0; i < num_dcfclk_sta_tarमाला_लो; i++) अणु
				अगर (dcfclk_sta_tarमाला_लो[i] > max_dcfclk_mhz) अणु
					dcfclk_sta_tarमाला_लो[i] = max_dcfclk_mhz;
					अवरोध;
				पूर्ण
			पूर्ण
			/* Update size of array since we "removed" duplicates */
			num_dcfclk_sta_tarमाला_लो = i + 1;
		पूर्ण

		num_uclk_states = bw_params->clk_table.num_entries;

		/* Calculate optimal dcfclk क्रम each uclk */
		क्रम (i = 0; i < num_uclk_states; i++) अणु
			dcn302_get_optimal_dcfclk_fclk_क्रम_uclk(bw_params->clk_table.entries[i].memclk_mhz * 16,
					&optimal_dcfclk_क्रम_uclk[i], शून्य);
			अगर (optimal_dcfclk_क्रम_uclk[i] < bw_params->clk_table.entries[0].dcfclk_mhz) अणु
				optimal_dcfclk_क्रम_uclk[i] = bw_params->clk_table.entries[0].dcfclk_mhz;
			पूर्ण
		पूर्ण

		/* Calculate optimal uclk क्रम each dcfclk sta target */
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
		/* create the final dcfclk and uclk table */
		जबतक (i < num_dcfclk_sta_tarमाला_लो && j < num_uclk_states && num_states < DC__VOLTAGE_STATES) अणु
			अगर (dcfclk_sta_tarमाला_लो[i] < optimal_dcfclk_क्रम_uclk[j] && i < num_dcfclk_sta_tarमाला_लो) अणु
				dcfclk_mhz[num_states] = dcfclk_sta_tarमाला_लो[i];
				dram_speed_mts[num_states++] = optimal_uclk_क्रम_dcfclk_sta_tarमाला_लो[i++];
			पूर्ण अन्यथा अणु
				अगर (j < num_uclk_states && optimal_dcfclk_क्रम_uclk[j] <= max_dcfclk_mhz) अणु
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
				optimal_dcfclk_क्रम_uclk[j] <= max_dcfclk_mhz) अणु
			dcfclk_mhz[num_states] = optimal_dcfclk_क्रम_uclk[j];
			dram_speed_mts[num_states++] = bw_params->clk_table.entries[j++].memclk_mhz * 16;
		पूर्ण

		dcn3_02_soc.num_states = num_states;
		क्रम (i = 0; i < dcn3_02_soc.num_states; i++) अणु
			dcn3_02_soc.घड़ी_limits[i].state = i;
			dcn3_02_soc.घड़ी_limits[i].dcfclk_mhz = dcfclk_mhz[i];
			dcn3_02_soc.घड़ी_limits[i].fabricclk_mhz = dcfclk_mhz[i];
			dcn3_02_soc.घड़ी_limits[i].dram_speed_mts = dram_speed_mts[i];

			/* Fill all states with max values of all other घड़ीs */
			dcn3_02_soc.घड़ी_limits[i].dispclk_mhz = max_dispclk_mhz;
			dcn3_02_soc.घड़ी_limits[i].dppclk_mhz  = max_dppclk_mhz;
			dcn3_02_soc.घड़ी_limits[i].phyclk_mhz  = max_phyclk_mhz;
			dcn3_02_soc.घड़ी_limits[i].dtbclk_mhz = dcn3_02_soc.घड़ी_limits[0].dtbclk_mhz;
			/* These घड़ीs cannot come from bw_params, always fill from dcn3_02_soc[1] */
			/* FCLK, PHYCLK_D18, SOCCLK, DSCCLK */
			dcn3_02_soc.घड़ी_limits[i].phyclk_d18_mhz = dcn3_02_soc.घड़ी_limits[0].phyclk_d18_mhz;
			dcn3_02_soc.घड़ी_limits[i].socclk_mhz = dcn3_02_soc.घड़ी_limits[0].socclk_mhz;
			dcn3_02_soc.घड़ी_limits[i].dscclk_mhz = dcn3_02_soc.घड़ी_limits[0].dscclk_mhz;
		पूर्ण
		/* re-init DML with updated bb */
		dml_init_instance(&dc->dml, &dcn3_02_soc, &dcn3_02_ip, DML_PROJECT_DCN30);
		अगर (dc->current_state)
			dml_init_instance(&dc->current_state->bw_ctx.dml, &dcn3_02_soc, &dcn3_02_ip, DML_PROJECT_DCN30);
	पूर्ण
पूर्ण

अटल काष्ठा resource_funcs dcn302_res_pool_funcs = अणु
		.destroy = dcn302_destroy_resource_pool,
		.link_enc_create = dcn302_link_encoder_create,
		.panel_cntl_create = dcn302_panel_cntl_create,
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
		.update_bw_bounding_box = dcn302_update_bw_bounding_box,
		.patch_unknown_plane_state = dcn20_patch_unknown_plane_state,
पूर्ण;

अटल काष्ठा dc_cap_funcs cap_funcs = अणु
		.get_dcc_compression_cap = dcn20_get_dcc_compression_cap
पूर्ण;

अटल स्थिर काष्ठा bios_रेजिस्टरs bios_regs = अणु
		NBIO_SR(BIOS_SCRATCH_3),
		NBIO_SR(BIOS_SCRATCH_6)
पूर्ण;

अटल स्थिर काष्ठा dccg_रेजिस्टरs dccg_regs = अणु
		DCCG_REG_LIST_DCN3_02()
पूर्ण;

अटल स्थिर काष्ठा dccg_shअगरt dccg_shअगरt = अणु
		DCCG_MASK_SH_LIST_DCN3_02(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dccg_mask dccg_mask = अणु
		DCCG_MASK_SH_LIST_DCN3_02(_MASK)
पूर्ण;

#घोषणा abm_regs(id)\
		[id] = अणु ABM_DCN301_REG_LIST(id) पूर्ण

अटल स्थिर काष्ठा dce_abm_रेजिस्टरs abm_regs[] = अणु
		abm_regs(0),
		abm_regs(1),
		abm_regs(2),
		abm_regs(3),
		abm_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_shअगरt abm_shअगरt = अणु
		ABM_MASK_SH_LIST_DCN30(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_mask abm_mask = अणु
		ABM_MASK_SH_LIST_DCN30(_MASK)
पूर्ण;

अटल bool dcn302_resource_स्थिरruct(
		uपूर्णांक8_t num_भव_links,
		काष्ठा dc *dc,
		काष्ठा resource_pool *pool)
अणु
	पूर्णांक i;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा irq_service_init_data init_data;

	ctx->dc_bios->regs = &bios_regs;

	pool->res_cap = &res_cap_dcn302;

	pool->funcs = &dcn302_res_pool_funcs;

	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->underlay_pipe_index = NO_UNDERLAY_PIPE;
	pool->pipe_count = pool->res_cap->num_timing_generator;
	pool->mpcc_count = pool->res_cap->num_timing_generator;
	dc->caps.max_करोwnscale_ratio = 600;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 5; /*1.4 w/a applied by derfault*/
	dc->caps.max_cursor_size = 256;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.dmdata_alloc_size = 2048;
	dc->caps.mall_size_per_mem_channel = 4;
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
	dc->caps.color.mpc.num_3dluts = pool->res_cap->num_mpc_3dlut; //3
	dc->caps.color.mpc.ogam_ram = 1;
	dc->caps.color.mpc.ogam_rom_caps.srgb = 0;
	dc->caps.color.mpc.ogam_rom_caps.bt2020 = 0;
	dc->caps.color.mpc.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.mpc.ogam_rom_caps.pq = 0;
	dc->caps.color.mpc.ogam_rom_caps.hlg = 0;
	dc->caps.color.mpc.ocsc = 1;

	अगर (dc->ctx->dce_environment == DCE_ENV_PRODUCTION_DRV)
		dc->debug = debug_शेषs_drv;
	अन्यथा
		dc->debug = debug_शेषs_diags;

	// Init the vm_helper
	अगर (dc->vm_helper)
		vm_helper_init(dc->vm_helper, 16);

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	/* Clock Sources क्रम Pixel Clock*/
	pool->घड़ी_sources[DCN302_CLK_SRC_PLL0] =
			dcn302_घड़ी_source_create(ctx, ctx->dc_bios,
					CLOCK_SOURCE_COMBO_PHY_PLL0,
					&clk_src_regs[0], false);
	pool->घड़ी_sources[DCN302_CLK_SRC_PLL1] =
			dcn302_घड़ी_source_create(ctx, ctx->dc_bios,
					CLOCK_SOURCE_COMBO_PHY_PLL1,
					&clk_src_regs[1], false);
	pool->घड़ी_sources[DCN302_CLK_SRC_PLL2] =
			dcn302_घड़ी_source_create(ctx, ctx->dc_bios,
					CLOCK_SOURCE_COMBO_PHY_PLL2,
					&clk_src_regs[2], false);
	pool->घड़ी_sources[DCN302_CLK_SRC_PLL3] =
			dcn302_घड़ी_source_create(ctx, ctx->dc_bios,
					CLOCK_SOURCE_COMBO_PHY_PLL3,
					&clk_src_regs[3], false);
	pool->घड़ी_sources[DCN302_CLK_SRC_PLL4] =
			dcn302_घड़ी_source_create(ctx, ctx->dc_bios,
					CLOCK_SOURCE_COMBO_PHY_PLL4,
					&clk_src_regs[4], false);

	pool->clk_src_count = DCN302_CLK_SRC_TOTAL;

	/* toकरो: not reuse phy_pll रेजिस्टरs */
	pool->dp_घड़ी_source =
			dcn302_घड़ी_source_create(ctx, ctx->dc_bios,
					CLOCK_SOURCE_ID_DP_DTO,
					&clk_src_regs[0], true);

	क्रम (i = 0; i < pool->clk_src_count; i++) अणु
		अगर (pool->घड़ी_sources[i] == शून्य) अणु
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण
	पूर्ण

	/* DCCG */
	pool->dccg = dccg30_create(ctx, &dccg_regs, &dccg_shअगरt, &dccg_mask);
	अगर (pool->dccg == शून्य) अणु
		dm_error("DC: failed to create dccg!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	/* PP Lib and SMU पूर्णांकerfaces */
	init_soc_bounding_box(dc, pool);

	/* DML */
	dml_init_instance(&dc->dml, &dcn3_02_soc, &dcn3_02_ip, DML_PROJECT_DCN30);

	/* IRQ */
	init_data.ctx = dc->ctx;
	pool->irqs = dal_irq_service_dcn302_create(&init_data);
	अगर (!pool->irqs)
		जाओ create_fail;

	/* HUBBUB */
	pool->hubbub = dcn302_hubbub_create(ctx);
	अगर (pool->hubbub == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create hubbub!\n");
		जाओ create_fail;
	पूर्ण

	/* HUBPs, DPPs, OPPs and TGs */
	क्रम (i = 0; i < pool->pipe_count; i++) अणु
		pool->hubps[i] = dcn302_hubp_create(ctx, i);
		अगर (pool->hubps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create hubps!\n");
			जाओ create_fail;
		पूर्ण

		pool->dpps[i] = dcn302_dpp_create(ctx, i);
		अगर (pool->dpps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create dpps!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_opp; i++) अणु
		pool->opps[i] = dcn302_opp_create(ctx, i);
		अगर (pool->opps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create output pixel processor!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_timing_generator; i++) अणु
		pool->timing_generators[i] = dcn302_timing_generator_create(ctx, i);
		अगर (pool->timing_generators[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ create_fail;
		पूर्ण
	पूर्ण
	pool->timing_generator_count = i;

	/* PSR */
	pool->psr = dmub_psr_create(ctx);
	अगर (pool->psr == शून्य) अणु
		dm_error("DC: failed to create psr!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	/* ABMs */
	क्रम (i = 0; i < pool->res_cap->num_timing_generator; i++) अणु
		pool->multiple_abms[i] = dmub_abm_create(ctx, &abm_regs[i], &abm_shअगरt, &abm_mask);
		अगर (pool->multiple_abms[i] == शून्य) अणु
			dm_error("DC: failed to create abm for pipe %d!\n", i);
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण
	पूर्ण

	/* MPC and DSC */
	pool->mpc = dcn302_mpc_create(ctx, pool->mpcc_count, pool->res_cap->num_mpc_3dlut);
	अगर (pool->mpc == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mpc!\n");
		जाओ create_fail;
	पूर्ण

	क्रम (i = 0; i < pool->res_cap->num_dsc; i++) अणु
		pool->dscs[i] = dcn302_dsc_create(ctx, i);
		अगर (pool->dscs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create display stream compressor %d!\n", i);
			जाओ create_fail;
		पूर्ण
	पूर्ण

	/* DWB and MMHUBBUB */
	अगर (!dcn302_dwbc_create(ctx, pool)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create dwbc!\n");
		जाओ create_fail;
	पूर्ण

	अगर (!dcn302_mmhubbub_create(ctx, pool)) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mcif_wb!\n");
		जाओ create_fail;
	पूर्ण

	/* AUX and I2C */
	क्रम (i = 0; i < pool->res_cap->num_ddc; i++) अणु
		pool->engines[i] = dcn302_aux_engine_create(ctx, i);
		अगर (pool->engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC:failed to create aux engine!!\n");
			जाओ create_fail;
		पूर्ण
		pool->hw_i2cs[i] = dcn302_i2c_hw_create(ctx, i);
		अगर (pool->hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC:failed to create hw i2c!!\n");
			जाओ create_fail;
		पूर्ण
		pool->sw_i2cs[i] = शून्य;
	पूर्ण

	/* Audio, Stream Encoders including HPO and भव, MPC 3D LUTs */
	अगर (!resource_स्थिरruct(num_भव_links, dc, pool,
			(!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment) ?
					&res_create_funcs : &res_create_maximus_funcs)))
		जाओ create_fail;

	/* HW Sequencer and Plane caps */
	dcn302_hw_sequencer_स्थिरruct(dc);

	dc->caps.max_planes =  pool->pipe_count;

	क्रम (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	dc->cap_funcs = cap_funcs;

	वापस true;

create_fail:

	dcn302_resource_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dcn302_create_resource_pool(स्थिर काष्ठा dc_init_data *init_data, काष्ठा dc *dc)
अणु
	काष्ठा resource_pool *pool = kzalloc(माप(काष्ठा resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dcn302_resource_स्थिरruct(init_data->num_भव_links, dc, pool))
		वापस pool;

	BREAK_TO_DEBUGGER();
	kमुक्त(pool);
	वापस शून्य;
पूर्ण
