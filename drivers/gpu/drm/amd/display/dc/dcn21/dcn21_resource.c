<शैली गुरु>
/*
* Copyright 2018 Advanced Micro Devices, Inc.
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

#समावेश "dcn21_init.h"

#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "dcn20/dcn20_resource.h"

#समावेश "clk_mgr.h"
#समावेश "dcn10/dcn10_hubp.h"
#समावेश "dcn10/dcn10_ipp.h"
#समावेश "dcn20/dcn20_hubbub.h"
#समावेश "dcn20/dcn20_mpc.h"
#समावेश "dcn20/dcn20_hubp.h"
#समावेश "dcn21_hubp.h"
#समावेश "irq/dcn21/irq_service_dcn21.h"
#समावेश "dcn20/dcn20_dpp.h"
#समावेश "dcn20/dcn20_optc.h"
#समावेश "dcn21/dcn21_hwseq.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dcn20/dcn20_opp.h"
#समावेश "dcn20/dcn20_dsc.h"
#समावेश "dcn21/dcn21_link_encoder.h"
#समावेश "dcn20/dcn20_stream_encoder.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "virtual/virtual_stream_encoder.h"
#समावेश "dml/display_mode_vba.h"
#समावेश "dcn20/dcn20_dccg.h"
#समावेश "dcn21/dcn21_dccg.h"
#समावेश "dcn21_hubbub.h"
#समावेश "dcn10/dcn10_resource.h"
#समावेश "dce/dce_panel_cntl.h"

#समावेश "dcn20/dcn20_dwb.h"
#समावेश "dcn20/dcn20_mmhubbub.h"
#समावेश "dpcs/dpcs_2_1_0_offset.h"
#समावेश "dpcs/dpcs_2_1_0_sh_mask.h"

#समावेश "renoir_ip_offset.h"
#समावेश "dcn/dcn_2_1_0_offset.h"
#समावेश "dcn/dcn_2_1_0_sh_mask.h"

#समावेश "nbio/nbio_7_0_offset.h"

#समावेश "mmhub/mmhub_2_0_0_offset.h"
#समावेश "mmhub/mmhub_2_0_0_sh_mask.h"

#समावेश "reg_helper.h"
#समावेश "dce/dce_abm.h"
#समावेश "dce/dce_dmcu.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_i2c.h"
#समावेश "dcn21_resource.h"
#समावेश "vm_helper.h"
#समावेश "dcn20/dcn20_vmid.h"
#समावेश "dce/dmub_psr.h"
#समावेश "dce/dmub_abm.h"

#घोषणा DC_LOGGER_INIT(logger)


काष्ठा _vcs_dpi_ip_params_st dcn2_1_ip = अणु
	.odm_capable = 1,
	.gpuvm_enable = 1,
	.hostvm_enable = 1,
	.gpuvm_max_page_table_levels = 1,
	.hostvm_max_page_table_levels = 4,
	.hostvm_cached_page_table_levels = 2,
	.num_dsc = 3,
	.rob_buffer_size_kbytes = 168,
	.det_buffer_size_kbytes = 164,
	.dpte_buffer_size_in_pte_reqs_luma = 44,
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
	.max_num_otg = 4,
	.max_num_dpp = 4,
	.max_num_wb = 1,
	.max_dchub_pscl_bw_pix_per_clk = 4,
	.max_pscl_lb_bw_pix_per_clk = 2,
	.max_lb_vscl_bw_pix_per_clk = 4,
	.max_vscl_hscl_bw_pix_per_clk = 4,
	.max_hscl_ratio = 4,
	.max_vscl_ratio = 4,
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

	.xfc_supported = false,
	.xfc_fill_bw_overhead_percent = 10.0,
	.xfc_fill_स्थिरant_bytes = 0,
	.ptoi_supported = 0,
	.number_of_cursors = 1,
पूर्ण;

काष्ठा _vcs_dpi_soc_bounding_box_st dcn2_1_soc = अणु
	.घड़ी_limits = अणु
			अणु
				.state = 0,
				.dcfclk_mhz = 400.0,
				.fabricclk_mhz = 400.0,
				.dispclk_mhz = 600.0,
				.dppclk_mhz = 400.00,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 1600.0,
			पूर्ण,
			अणु
				.state = 1,
				.dcfclk_mhz = 464.52,
				.fabricclk_mhz = 800.0,
				.dispclk_mhz = 654.55,
				.dppclk_mhz = 626.09,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 205.67,
				.dram_speed_mts = 1600.0,
			पूर्ण,
			अणु
				.state = 2,
				.dcfclk_mhz = 514.29,
				.fabricclk_mhz = 933.0,
				.dispclk_mhz = 757.89,
				.dppclk_mhz = 685.71,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 287.67,
				.dram_speed_mts = 1866.0,
			पूर्ण,
			अणु
				.state = 3,
				.dcfclk_mhz = 576.00,
				.fabricclk_mhz = 1067.0,
				.dispclk_mhz = 847.06,
				.dppclk_mhz = 757.89,
				.phyclk_mhz = 600.0,
				.socclk_mhz = 715.0,
				.dscclk_mhz = 318.334,
				.dram_speed_mts = 2134.0,
			पूर्ण,
			अणु
				.state = 4,
				.dcfclk_mhz = 626.09,
				.fabricclk_mhz = 1200.0,
				.dispclk_mhz = 900.00,
				.dppclk_mhz = 847.06,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 953.0,
				.dscclk_mhz = 489.0,
				.dram_speed_mts = 2400.0,
			पूर्ण,
			अणु
				.state = 5,
				.dcfclk_mhz = 685.71,
				.fabricclk_mhz = 1333.0,
				.dispclk_mhz = 1028.57,
				.dppclk_mhz = 960.00,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 278.0,
				.dscclk_mhz = 287.67,
				.dram_speed_mts = 2666.0,
			पूर्ण,
			अणु
				.state = 6,
				.dcfclk_mhz = 757.89,
				.fabricclk_mhz = 1467.0,
				.dispclk_mhz = 1107.69,
				.dppclk_mhz = 1028.57,
				.phyclk_mhz = 810.0,
				.socclk_mhz = 715.0,
				.dscclk_mhz = 318.334,
				.dram_speed_mts = 3200.0,
			पूर्ण,
			अणु
				.state = 7,
				.dcfclk_mhz = 847.06,
				.fabricclk_mhz = 1600.0,
				.dispclk_mhz = 1395.0,
				.dppclk_mhz = 1285.00,
				.phyclk_mhz = 1325.0,
				.socclk_mhz = 953.0,
				.dscclk_mhz = 489.0,
				.dram_speed_mts = 4266.0,
			पूर्ण,
			/*Extra state, no dispclk ramping*/
			अणु
				.state = 8,
				.dcfclk_mhz = 847.06,
				.fabricclk_mhz = 1600.0,
				.dispclk_mhz = 1395.0,
				.dppclk_mhz = 1285.0,
				.phyclk_mhz = 1325.0,
				.socclk_mhz = 953.0,
				.dscclk_mhz = 489.0,
				.dram_speed_mts = 4266.0,
			पूर्ण,

		पूर्ण,

	.sr_निकास_समय_us = 12.5,
	.sr_enter_plus_निकास_समय_us = 17.0,
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
	.max_avg_dram_bw_use_normal_percent = 100.0,
	.ग_लिखोback_latency_us = 12.0,
	.max_request_size_bytes = 256,
	.dram_channel_width_bytes = 4,
	.fabric_datapath_to_dcn_data_वापस_bytes = 32,
	.dcn_करोwnspपढ़ो_percent = 0.5,
	.करोwnspपढ़ो_percent = 0.38,
	.dram_page_खोलो_समय_ns = 50.0,
	.dram_rw_turnaround_समय_ns = 17.5,
	.dram_वापस_buffer_per_channel_bytes = 8192,
	.round_trip_ping_latency_dcfclk_cycles = 128,
	.urgent_out_of_order_वापस_per_channel_bytes = 4096,
	.channel_पूर्णांकerleave_bytes = 256,
	.num_banks = 8,
	.num_chans = 4,
	.vmm_page_size_bytes = 4096,
	.dram_घड़ी_change_latency_us = 23.84,
	.वापस_bus_width_bytes = 64,
	.dispclk_dppclk_vco_speed_mhz = 3600,
	.xfc_bus_transport_समय_us = 4,
	.xfc_xbuf_latency_tolerance_us = 4,
	.use_urgent_burst_bw = 1,
	.num_states = 8
पूर्ण;

#अगर_अघोषित MAX
#घोषणा MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#पूर्ण_अगर
#अगर_अघोषित MIN
#घोषणा MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#पूर्ण_अगर

/* begin *********************
 * macros to expend रेजिस्टर list macro defined in HW object header file */

/* DCN */
/* TODO awful hack. fixup dcn20_dwb.h */
#अघोषित BASE_INNER
#घोषणा BASE_INNER(seg) DMU_BASE__INST0_SEG ## seg

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
	NBIF0_BASE__INST0_SEG ## seg

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

#घोषणा clk_src_regs(index, pllid)\
[index] = अणु\
	CS_COMMON_REG_LIST_DCN2_1(index, pllid),\
पूर्ण

अटल स्थिर काष्ठा dce110_clk_src_regs clk_src_regs[] = अणु
	clk_src_regs(0, A),
	clk_src_regs(1, B),
	clk_src_regs(2, C),
	clk_src_regs(3, D),
	clk_src_regs(4, E),
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_shअगरt cs_shअगरt = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_mask cs_mask = अणु
		CS_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
पूर्ण;

अटल स्थिर काष्ठा bios_रेजिस्टरs bios_regs = अणु
		NBIO_SR(BIOS_SCRATCH_3),
		NBIO_SR(BIOS_SCRATCH_6)
पूर्ण;

अटल स्थिर काष्ठा dce_dmcu_रेजिस्टरs dmcu_regs = अणु
		DMCU_DCN20_REG_LIST()
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

अटल स्थिर काष्ठा dccg_रेजिस्टरs dccg_regs = अणु
		DCCG_COMMON_REG_LIST_DCN_BASE()
पूर्ण;

अटल स्थिर काष्ठा dccg_shअगरt dccg_shअगरt = अणु
		DCCG_MASK_SH_LIST_DCN2(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dccg_mask dccg_mask = अणु
		DCCG_MASK_SH_LIST_DCN2(_MASK)
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

#घोषणा tg_regs(id)\
[id] = अणुTG_COMMON_REG_LIST_DCN2_0(id)पूर्ण

अटल स्थिर काष्ठा dcn_optc_रेजिस्टरs tg_regs[] = अणु
	tg_regs(0),
	tg_regs(1),
	tg_regs(2),
	tg_regs(3)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_shअगरt tg_shअगरt = अणु
	TG_COMMON_MASK_SH_LIST_DCN2_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_mask tg_mask = अणु
	TG_COMMON_MASK_SH_LIST_DCN2_0(_MASK)
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

#घोषणा hubp_regs(id)\
[id] = अणु\
	HUBP_REG_LIST_DCN21(id)\
पूर्ण

अटल स्थिर काष्ठा dcn_hubp2_रेजिस्टरs hubp_regs[] = अणु
		hubp_regs(0),
		hubp_regs(1),
		hubp_regs(2),
		hubp_regs(3)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_shअगरt hubp_shअगरt = अणु
		HUBP_MASK_SH_LIST_DCN21(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubp2_mask hubp_mask = अणु
		HUBP_MASK_SH_LIST_DCN21(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_रेजिस्टरs hubbub_reg = अणु
		HUBBUB_REG_LIST_DCN21()
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_shअगरt hubbub_shअगरt = अणु
		HUBBUB_MASK_SH_LIST_DCN21(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_mask hubbub_mask = अणु
		HUBBUB_MASK_SH_LIST_DCN21(_MASK)
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

#घोषणा ipp_regs(id)\
[id] = अणु\
	IPP_REG_LIST_DCN20(id),\
पूर्ण

अटल स्थिर काष्ठा dcn10_ipp_रेजिस्टरs ipp_regs[] = अणु
	ipp_regs(0),
	ipp_regs(1),
	ipp_regs(2),
	ipp_regs(3),
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
पूर्ण;

अटल स्थिर काष्ठा dcn2_dpp_shअगरt tf_shअगरt = अणु
		TF_REG_LIST_SH_MASK_DCN20(__SHIFT),
		TF_DEBUG_REG_LIST_SH_DCN20
पूर्ण;

अटल स्थिर काष्ठा dcn2_dpp_mask tf_mask = अणु
		TF_REG_LIST_SH_MASK_DCN20(_MASK),
		TF_DEBUG_REG_LIST_MASK_DCN20
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
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt aux_shअगरt = अणु
	DCN_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
	DCN_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCN20(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCN20(_MASK)
पूर्ण;

अटल व्योम dcn21_pp_smu_destroy(काष्ठा pp_smu_funcs **pp_smu);

अटल पूर्णांक dcn21_populate_dml_pipes_from_context(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		bool fast_validate);

अटल काष्ठा input_pixel_processor *dcn21_ipp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn10_ipp *ipp =
		kzalloc(माप(काष्ठा dcn10_ipp), GFP_KERNEL);

	अगर (!ipp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn20_ipp_स्थिरruct(ipp, ctx, inst,
			&ipp_regs[inst], &ipp_shअगरt, &ipp_mask);
	वापस &ipp->base;
पूर्ण

अटल काष्ठा dpp *dcn21_dpp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn20_dpp *dpp =
		kzalloc(माप(काष्ठा dcn20_dpp), GFP_KERNEL);

	अगर (!dpp)
		वापस शून्य;

	अगर (dpp2_स्थिरruct(dpp, ctx, inst,
			&tf_regs[inst], &tf_shअगरt, &tf_mask))
		वापस &dpp->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(dpp);
	वापस शून्य;
पूर्ण

अटल काष्ठा dce_aux *dcn21_aux_engine_create(
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
		i2c_inst_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_shअगरt i2c_shअगरts = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_mask i2c_masks = अणु
		I2C_COMMON_MASK_SH_LIST_DCN2(_MASK)
पूर्ण;

काष्ठा dce_i2c_hw *dcn21_i2c_hw_create(
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

अटल स्थिर काष्ठा resource_caps res_cap_rn = अणु
		.num_timing_generator = 4,
		.num_opp = 4,
		.num_video_plane = 4,
		.num_audio = 4, // 4 audio endpoपूर्णांकs.  4 audio streams
		.num_stream_encoder = 5,
		.num_pll = 5,  // maybe 3 because the last two used क्रम USB-c
		.num_dwb = 1,
		.num_ddc = 5,
		.num_vmid = 16,
		.num_dsc = 3,
पूर्ण;

#अगर_घोषित DIAGS_BUILD
अटल स्थिर काष्ठा resource_caps res_cap_rn_FPGA_4pipe = अणु
		.num_timing_generator = 4,
		.num_opp = 4,
		.num_video_plane = 4,
		.num_audio = 7,
		.num_stream_encoder = 4,
		.num_pll = 4,
		.num_dwb = 1,
		.num_ddc = 4,
		.num_dsc = 0,
पूर्ण;

अटल स्थिर काष्ठा resource_caps res_cap_rn_FPGA_2pipe_dsc = अणु
		.num_timing_generator = 2,
		.num_opp = 2,
		.num_video_plane = 2,
		.num_audio = 7,
		.num_stream_encoder = 2,
		.num_pll = 4,
		.num_dwb = 1,
		.num_ddc = 4,
		.num_dsc = 2,
पूर्ण;
#पूर्ण_अगर

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
			.fp16 = 16000
	पूर्ण,

	.max_करोwnscale_factor = अणु
			.argb8888 = 250,
			.nv12 = 250,
			.fp16 = 250
	पूर्ण,
	64,
	64
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_drv = अणु
		.disable_dmcu = false,
		.क्रमce_abm_enable = false,
		.timing_trace = false,
		.घड़ी_प्रकारrace = true,
		.disable_pplib_घड़ी_request = true,
		.min_disp_clk_khz = 100000,
		.pipe_split_policy = MPC_SPLIT_AVOID_MULT_DISP,
		.क्रमce_single_disp_pipe_split = false,
		.disable_dcc = DCC_ENABLE,
		.vsr_support = true,
		.perक्रमmance_trace = false,
		.max_करोwnscale_src_width = 4096,
		.disable_pplib_wm_range = false,
		.scl_reset_length10 = true,
		.sanity_checks = true,
		.disable_48mhz_pwrdwn = false,
		.usbc_combo_phy_reset_wa = true,
		.dmub_command_table = true,
		.use_max_lb = true
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
		.disable_48mhz_pwrdwn = true,
		.disable_psr = true,
		.enable_tri_buf = true,
		.use_max_lb = true
पूर्ण;

क्रमागत dcn20_clk_src_array_id अणु
	DCN20_CLK_SRC_PLL0,
	DCN20_CLK_SRC_PLL1,
	DCN20_CLK_SRC_PLL2,
	DCN20_CLK_SRC_PLL3,
	DCN20_CLK_SRC_PLL4,
	DCN20_CLK_SRC_TOTAL_DCN21
पूर्ण;

अटल व्योम dcn21_resource_deकाष्ठा(काष्ठा dcn21_resource_pool *pool)
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

	अगर (pool->base.abm != शून्य) अणु
		अगर (pool->base.abm->ctx->dc->config.disable_dmcu)
			dmub_abm_destroy(&pool->base.abm);
		अन्यथा
			dce_abm_destroy(&pool->base.abm);
	पूर्ण

	अगर (pool->base.dmcu != शून्य)
		dce_dmcu_destroy(&pool->base.dmcu);

	अगर (pool->base.psr != शून्य)
		dmub_psr_destroy(&pool->base.psr);

	अगर (pool->base.dccg != शून्य)
		dcn_dccg_destroy(&pool->base.dccg);

	अगर (pool->base.pp_smu != शून्य)
		dcn21_pp_smu_destroy(&pool->base.pp_smu);
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

अटल व्योम patch_bounding_box(काष्ठा dc *dc, काष्ठा _vcs_dpi_soc_bounding_box_st *bb)
अणु
	पूर्णांक i;

	अगर (dc->bb_overrides.sr_निकास_समय_ns) अणु
		क्रम (i = 0; i < WM_SET_COUNT; i++) अणु
			  dc->clk_mgr->bw_params->wm_table.entries[i].sr_निकास_समय_us =
					  dc->bb_overrides.sr_निकास_समय_ns / 1000.0;
		पूर्ण
	पूर्ण

	अगर (dc->bb_overrides.sr_enter_plus_निकास_समय_ns) अणु
		क्रम (i = 0; i < WM_SET_COUNT; i++) अणु
			  dc->clk_mgr->bw_params->wm_table.entries[i].sr_enter_plus_निकास_समय_us =
					  dc->bb_overrides.sr_enter_plus_निकास_समय_ns / 1000.0;
		पूर्ण
	पूर्ण

	अगर (dc->bb_overrides.urgent_latency_ns) अणु
		bb->urgent_latency_us = dc->bb_overrides.urgent_latency_ns / 1000.0;
	पूर्ण

	अगर (dc->bb_overrides.dram_घड़ी_change_latency_ns) अणु
		क्रम (i = 0; i < WM_SET_COUNT; i++) अणु
			dc->clk_mgr->bw_params->wm_table.entries[i].pstate_latency_us =
				dc->bb_overrides.dram_घड़ी_change_latency_ns / 1000.0;
		पूर्ण
	पूर्ण
पूर्ण

व्योम dcn21_calculate_wm(
		काष्ठा dc *dc, काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		पूर्णांक *out_pipe_cnt,
		पूर्णांक *pipe_split_from,
		पूर्णांक vlevel_req,
		bool fast_validate)
अणु
	पूर्णांक pipe_cnt, i, pipe_idx;
	पूर्णांक vlevel, vlevel_max;
	काष्ठा wm_range_table_entry *table_entry;
	काष्ठा clk_bw_params *bw_params = dc->clk_mgr->bw_params;

	ASSERT(bw_params);

	patch_bounding_box(dc, &context->bw_ctx.dml.soc);

	क्रम (i = 0, pipe_idx = 0, pipe_cnt = 0; i < dc->res_pool->pipe_count; i++) अणु
			अगर (!context->res_ctx.pipe_ctx[i].stream)
				जारी;

			pipes[pipe_cnt].clks_cfg.refclk_mhz = dc->res_pool->ref_घड़ीs.dchub_ref_घड़ी_inKhz / 1000.0;
			pipes[pipe_cnt].clks_cfg.dispclk_mhz = context->bw_ctx.dml.vba.RequiredDISPCLK[vlevel_req][context->bw_ctx.dml.vba.maxMpcComb];

			अगर (pipe_split_from[i] < 0) अणु
				pipes[pipe_cnt].clks_cfg.dppclk_mhz =
						context->bw_ctx.dml.vba.RequiredDPPCLK[vlevel_req][context->bw_ctx.dml.vba.maxMpcComb][pipe_idx];
				अगर (context->bw_ctx.dml.vba.BlendingAndTiming[pipe_idx] == pipe_idx)
					pipes[pipe_cnt].pipe.dest.odm_combine =
							context->bw_ctx.dml.vba.ODMCombineEnablePerState[vlevel_req][pipe_idx];
				अन्यथा
					pipes[pipe_cnt].pipe.dest.odm_combine = 0;
				pipe_idx++;
			पूर्ण अन्यथा अणु
				pipes[pipe_cnt].clks_cfg.dppclk_mhz =
						context->bw_ctx.dml.vba.RequiredDPPCLK[vlevel_req][context->bw_ctx.dml.vba.maxMpcComb][pipe_split_from[i]];
				अगर (context->bw_ctx.dml.vba.BlendingAndTiming[pipe_split_from[i]] == pipe_split_from[i])
					pipes[pipe_cnt].pipe.dest.odm_combine =
							context->bw_ctx.dml.vba.ODMCombineEnablePerState[vlevel_req][pipe_split_from[i]];
				अन्यथा
					pipes[pipe_cnt].pipe.dest.odm_combine = 0;
			पूर्ण
			pipe_cnt++;
	पूर्ण

	अगर (pipe_cnt != pipe_idx) अणु
		अगर (dc->res_pool->funcs->populate_dml_pipes)
			pipe_cnt = dc->res_pool->funcs->populate_dml_pipes(dc,
				context, pipes, fast_validate);
		अन्यथा
			pipe_cnt = dcn21_populate_dml_pipes_from_context(dc,
				context, pipes, fast_validate);
	पूर्ण

	*out_pipe_cnt = pipe_cnt;

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
	vlevel = MIN(MAX(vlevel_req, 3), vlevel_max);
	calculate_wm_set_क्रम_vlevel(vlevel, table_entry, &context->bw_ctx.bw.dcn.watermarks.c,
						&context->bw_ctx.dml, pipes, pipe_cnt);
	/* WM Set B */
	table_entry = &bw_params->wm_table.entries[WM_B];
	vlevel = MIN(MAX(vlevel_req, 2), vlevel_max);
	calculate_wm_set_क्रम_vlevel(vlevel, table_entry, &context->bw_ctx.bw.dcn.watermarks.b,
						&context->bw_ctx.dml, pipes, pipe_cnt);

	/* WM Set A */
	table_entry = &bw_params->wm_table.entries[WM_A];
	vlevel = MIN(vlevel_req, vlevel_max);
	calculate_wm_set_क्रम_vlevel(vlevel, table_entry, &context->bw_ctx.bw.dcn.watermarks.a,
						&context->bw_ctx.dml, pipes, pipe_cnt);
पूर्ण


अटल bool dcn21_fast_validate_bw(
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
	/*
	 * DML favors voltage over p-state, but we're more पूर्णांकerested in
	 * supporting p-state over voltage. We can't support p-state in
	 * prefetch mode > 0 so try capping the prefetch mode to start.
	 */
	context->bw_ctx.dml.soc.allow_dram_self_refresh_or_dram_घड़ी_change_in_vblank =
				dm_allow_self_refresh_and_mclk_चयन;
	vlevel = dml_get_voltage_level(&context->bw_ctx.dml, pipes, pipe_cnt);

	अगर (vlevel > context->bw_ctx.dml.soc.num_states) अणु
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
		अगर (vlevel > context->bw_ctx.dml.soc.num_states)
			जाओ validate_fail;
	पूर्ण

	vlevel = dcn20_validate_apply_pipe_split_flags(dc, context, vlevel, split, शून्य);

	क्रम (i = 0, pipe_idx = 0; i < dc->res_pool->pipe_count; i++) अणु
		काष्ठा pipe_ctx *pipe = &context->res_ctx.pipe_ctx[i];
		काष्ठा pipe_ctx *mpo_pipe = pipe->bottom_pipe;
		काष्ठा vba_vars_st *vba = &context->bw_ctx.dml.vba;

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

अटल noअंतरभूत bool dcn21_validate_bandwidth_fp(काष्ठा dc *dc,
		काष्ठा dc_state *context, bool fast_validate)
अणु
	bool out = false;

	BW_VAL_TRACE_SETUP();

	पूर्णांक vlevel = 0;
	पूर्णांक pipe_split_from[MAX_PIPES];
	पूर्णांक pipe_cnt = 0;
	display_e2e_pipe_params_st *pipes = kzalloc(dc->res_pool->pipe_count * माप(display_e2e_pipe_params_st), GFP_ATOMIC);
	DC_LOGGER_INIT(dc->ctx->logger);

	BW_VAL_TRACE_COUNT();

	/*Unsafe due to current pipe merge and split logic*/
	ASSERT(context != dc->current_state);

	out = dcn21_fast_validate_bw(dc, context, pipes, &pipe_cnt, pipe_split_from, &vlevel, fast_validate);

	अगर (pipe_cnt == 0)
		जाओ validate_out;

	अगर (!out)
		जाओ validate_fail;

	BW_VAL_TRACE_END_VOLTAGE_LEVEL();

	अगर (fast_validate) अणु
		BW_VAL_TRACE_SKIP(fast);
		जाओ validate_out;
	पूर्ण

	dcn21_calculate_wm(dc, context, pipes, &pipe_cnt, pipe_split_from, vlevel, fast_validate);
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
 * Some of the functions further below use the FPU, so we need to wrap this
 * with DC_FP_START()/DC_FP_END(). Use the same approach as क्रम
 * dcn20_validate_bandwidth in dcn20_resource.c.
 */
bool dcn21_validate_bandwidth(काष्ठा dc *dc, काष्ठा dc_state *context,
		bool fast_validate)
अणु
	bool voltage_supported;
	DC_FP_START();
	voltage_supported = dcn21_validate_bandwidth_fp(dc, context, fast_validate);
	DC_FP_END();
	वापस voltage_supported;
पूर्ण

अटल व्योम dcn21_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dcn21_resource_pool *dcn21_pool = TO_DCN21_RES_POOL(*pool);

	dcn21_resource_deकाष्ठा(dcn21_pool);
	kमुक्त(dcn21_pool);
	*pool = शून्य;
पूर्ण

अटल काष्ठा घड़ी_source *dcn21_घड़ी_source_create(
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

	अगर (dcn20_clk_src_स्थिरruct(clk_src, ctx, bios, id,
			regs, &cs_shअगरt, &cs_mask)) अणु
		clk_src->base.dp_clk_src = dp_clk_src;
		वापस &clk_src->base;
	पूर्ण

	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

अटल काष्ठा hubp *dcn21_hubp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn21_hubp *hubp21 =
		kzalloc(माप(काष्ठा dcn21_hubp), GFP_KERNEL);

	अगर (!hubp21)
		वापस शून्य;

	अगर (hubp21_स्थिरruct(hubp21, ctx, inst,
			&hubp_regs[inst], &hubp_shअगरt, &hubp_mask))
		वापस &hubp21->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(hubp21);
	वापस शून्य;
पूर्ण

अटल काष्ठा hubbub *dcn21_hubbub_create(काष्ठा dc_context *ctx)
अणु
	पूर्णांक i;

	काष्ठा dcn20_hubbub *hubbub = kzalloc(माप(काष्ठा dcn20_hubbub),
					  GFP_KERNEL);

	अगर (!hubbub)
		वापस शून्य;

	hubbub21_स्थिरruct(hubbub, ctx,
			&hubbub_reg,
			&hubbub_shअगरt,
			&hubbub_mask);

	क्रम (i = 0; i < res_cap_rn.num_vmid; i++) अणु
		काष्ठा dcn20_vmid *vmid = &hubbub->vmid[i];

		vmid->ctx = ctx;

		vmid->regs = &vmid_regs[i];
		vmid->shअगरts = &vmid_shअगरts;
		vmid->masks = &vmid_masks;
	पूर्ण
	hubbub->num_vmid = res_cap_rn.num_vmid;

	वापस &hubbub->base;
पूर्ण

काष्ठा output_pixel_processor *dcn21_opp_create(
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

काष्ठा timing_generator *dcn21_timing_generator_create(
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t instance)
अणु
	काष्ठा optc *tgn10 =
		kzalloc(माप(काष्ठा optc), GFP_KERNEL);

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

काष्ठा mpc *dcn21_mpc_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn20_mpc *mpc20 = kzalloc(माप(काष्ठा dcn20_mpc),
					  GFP_KERNEL);

	अगर (!mpc20)
		वापस शून्य;

	dcn20_mpc_स्थिरruct(mpc20, ctx,
			&mpc_regs,
			&mpc_shअगरt,
			&mpc_mask,
			6);

	वापस &mpc20->base;
पूर्ण

अटल व्योम पढ़ो_dce_straps(
	काष्ठा dc_context *ctx,
	काष्ठा resource_straps *straps)
अणु
	generic_reg_get(ctx, mmDC_PINSTRAPS + BASE(mmDC_PINSTRAPS_BASE_IDX),
		FN(DC_PINSTRAPS, DC_PINSTRAPS_AUDIO), &straps->dc_pinstraps_audio);

पूर्ण


काष्ठा display_stream_compressor *dcn21_dsc_create(
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

अटल काष्ठा _vcs_dpi_voltage_scaling_st स्थिरruct_low_pstate_lvl(काष्ठा clk_limit_table *clk_table, अचिन्हित पूर्णांक high_voltage_lvl)
अणु
	काष्ठा _vcs_dpi_voltage_scaling_st low_pstate_lvl;
	पूर्णांक i;

	low_pstate_lvl.state = 1;
	low_pstate_lvl.dcfclk_mhz = clk_table->entries[0].dcfclk_mhz;
	low_pstate_lvl.fabricclk_mhz = clk_table->entries[0].fclk_mhz;
	low_pstate_lvl.socclk_mhz = clk_table->entries[0].socclk_mhz;
	low_pstate_lvl.dram_speed_mts = clk_table->entries[0].memclk_mhz * 2;

	low_pstate_lvl.dispclk_mhz = dcn2_1_soc.घड़ी_limits[high_voltage_lvl].dispclk_mhz;
	low_pstate_lvl.dppclk_mhz = dcn2_1_soc.घड़ी_limits[high_voltage_lvl].dppclk_mhz;
	low_pstate_lvl.dram_bw_per_chan_gbps = dcn2_1_soc.घड़ी_limits[high_voltage_lvl].dram_bw_per_chan_gbps;
	low_pstate_lvl.dscclk_mhz = dcn2_1_soc.घड़ी_limits[high_voltage_lvl].dscclk_mhz;
	low_pstate_lvl.dtbclk_mhz = dcn2_1_soc.घड़ी_limits[high_voltage_lvl].dtbclk_mhz;
	low_pstate_lvl.phyclk_d18_mhz = dcn2_1_soc.घड़ी_limits[high_voltage_lvl].phyclk_d18_mhz;
	low_pstate_lvl.phyclk_mhz = dcn2_1_soc.घड़ी_limits[high_voltage_lvl].phyclk_mhz;

	क्रम (i = clk_table->num_entries; i > 1; i--)
		clk_table->entries[i] = clk_table->entries[i-1];
	clk_table->entries[1] = clk_table->entries[0];
	clk_table->num_entries++;

	वापस low_pstate_lvl;
पूर्ण

अटल व्योम update_bw_bounding_box(काष्ठा dc *dc, काष्ठा clk_bw_params *bw_params)
अणु
	काष्ठा dcn21_resource_pool *pool = TO_DCN21_RES_POOL(dc->res_pool);
	काष्ठा clk_limit_table *clk_table = &bw_params->clk_table;
	काष्ठा _vcs_dpi_voltage_scaling_st घड़ी_limits[DC__VOLTAGE_STATES];
	अचिन्हित पूर्णांक i, बंदst_clk_lvl = 0, k = 0;
	पूर्णांक j;

	dcn2_1_ip.max_num_otg = pool->base.res_cap->num_timing_generator;
	dcn2_1_ip.max_num_dpp = pool->base.pipe_count;
	dcn2_1_soc.num_chans = bw_params->num_channels;

	ASSERT(clk_table->num_entries);
	/* Copy dcn2_1_soc.घड़ी_limits to घड़ी_limits to aव्योम copying over null states later */
	क्रम (i = 0; i < dcn2_1_soc.num_states + 1; i++) अणु
		घड़ी_limits[i] = dcn2_1_soc.घड़ी_limits[i];
	पूर्ण

	क्रम (i = 0; i < clk_table->num_entries; i++) अणु
		/* loop backwards*/
		क्रम (बंदst_clk_lvl = 0, j = dcn2_1_soc.num_states - 1; j >= 0; j--) अणु
			अगर ((अचिन्हित पूर्णांक) dcn2_1_soc.घड़ी_limits[j].dcfclk_mhz <= clk_table->entries[i].dcfclk_mhz) अणु
				बंदst_clk_lvl = j;
				अवरोध;
			पूर्ण
		पूर्ण

		/* clk_table[1] is reserved क्रम min DF PState.  skip here to fill in later. */
		अगर (i == 1)
			k++;

		घड़ी_limits[k].state = k;
		घड़ी_limits[k].dcfclk_mhz = clk_table->entries[i].dcfclk_mhz;
		घड़ी_limits[k].fabricclk_mhz = clk_table->entries[i].fclk_mhz;
		घड़ी_limits[k].socclk_mhz = clk_table->entries[i].socclk_mhz;
		घड़ी_limits[k].dram_speed_mts = clk_table->entries[i].memclk_mhz * 2;

		घड़ी_limits[k].dispclk_mhz = dcn2_1_soc.घड़ी_limits[बंदst_clk_lvl].dispclk_mhz;
		घड़ी_limits[k].dppclk_mhz = dcn2_1_soc.घड़ी_limits[बंदst_clk_lvl].dppclk_mhz;
		घड़ी_limits[k].dram_bw_per_chan_gbps = dcn2_1_soc.घड़ी_limits[बंदst_clk_lvl].dram_bw_per_chan_gbps;
		घड़ी_limits[k].dscclk_mhz = dcn2_1_soc.घड़ी_limits[बंदst_clk_lvl].dscclk_mhz;
		घड़ी_limits[k].dtbclk_mhz = dcn2_1_soc.घड़ी_limits[बंदst_clk_lvl].dtbclk_mhz;
		घड़ी_limits[k].phyclk_d18_mhz = dcn2_1_soc.घड़ी_limits[बंदst_clk_lvl].phyclk_d18_mhz;
		घड़ी_limits[k].phyclk_mhz = dcn2_1_soc.घड़ी_limits[बंदst_clk_lvl].phyclk_mhz;

		k++;
	पूर्ण
	क्रम (i = 0; i < clk_table->num_entries + 1; i++)
		dcn2_1_soc.घड़ी_limits[i] = घड़ी_limits[i];
	अगर (clk_table->num_entries) अणु
		dcn2_1_soc.num_states = clk_table->num_entries + 1;
		/* fill in min DF PState */
		dcn2_1_soc.घड़ी_limits[1] = स्थिरruct_low_pstate_lvl(clk_table, बंदst_clk_lvl);
		/* duplicate last level */
		dcn2_1_soc.घड़ी_limits[dcn2_1_soc.num_states] = dcn2_1_soc.घड़ी_limits[dcn2_1_soc.num_states - 1];
		dcn2_1_soc.घड़ी_limits[dcn2_1_soc.num_states].state = dcn2_1_soc.num_states;
	पूर्ण

	dml_init_instance(&dc->dml, &dcn2_1_soc, &dcn2_1_ip, DML_PROJECT_DCN21);
पूर्ण

अटल काष्ठा pp_smu_funcs *dcn21_pp_smu_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा pp_smu_funcs *pp_smu = kzalloc(माप(*pp_smu), GFP_KERNEL);

	अगर (!pp_smu)
		वापस pp_smu;

	dm_pp_get_funcs(ctx, pp_smu);

	अगर (pp_smu->ctx.ver != PP_SMU_VER_RN)
		pp_smu = स_रखो(pp_smu, 0, माप(काष्ठा pp_smu_funcs));


	वापस pp_smu;
पूर्ण

अटल व्योम dcn21_pp_smu_destroy(काष्ठा pp_smu_funcs **pp_smu)
अणु
	अगर (pp_smu && *pp_smu) अणु
		kमुक्त(*pp_smu);
		*pp_smu = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा audio *dcn21_create_audio(
		काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst,
			&audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

अटल काष्ठा dc_cap_funcs cap_funcs = अणु
	.get_dcc_compression_cap = dcn20_get_dcc_compression_cap
पूर्ण;

काष्ठा stream_encoder *dcn21_stream_encoder_create(
	क्रमागत engine_id eng_id,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn10_stream_encoder *enc1 =
		kzalloc(माप(काष्ठा dcn10_stream_encoder), GFP_KERNEL);

	अगर (!enc1)
		वापस शून्य;

	dcn20_stream_encoder_स्थिरruct(enc1, ctx, ctx->dc_bios, eng_id,
					&stream_enc_regs[eng_id],
					&se_shअगरt, &se_mask);

	वापस &enc1->base;
पूर्ण

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCN21_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCN21_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCN21_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा dce_hwseq *dcn21_hwseq_create(
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dce_hwseq *hws = kzalloc(माप(काष्ठा dce_hwseq), GFP_KERNEL);

	अगर (hws) अणु
		hws->ctx = ctx;
		hws->regs = &hwseq_reg;
		hws->shअगरts = &hwseq_shअगरt;
		hws->masks = &hwseq_mask;
		hws->wa.DEGVIDCN21 = true;
		hws->wa.disallow_self_refresh_during_multi_plane_transition = true;
	पूर्ण
	वापस hws;
पूर्ण

अटल स्थिर काष्ठा resource_create_funcs res_create_funcs = अणु
	.पढ़ो_dce_straps = पढ़ो_dce_straps,
	.create_audio = dcn21_create_audio,
	.create_stream_encoder = dcn21_stream_encoder_create,
	.create_hwseq = dcn21_hwseq_create,
पूर्ण;

अटल स्थिर काष्ठा resource_create_funcs res_create_maximus_funcs = अणु
	.पढ़ो_dce_straps = शून्य,
	.create_audio = शून्य,
	.create_stream_encoder = शून्य,
	.create_hwseq = dcn21_hwseq_create,
पूर्ण;

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
	LE_DCN2_REG_LIST(id), \
	UNIPHY_DCN2_REG_LIST(phyid), \
	DPCS_DCN21_REG_LIST(id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id) \
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs link_enc_regs[] = अणु
	link_regs(0, A),
	link_regs(1, B),
	link_regs(2, C),
	link_regs(3, D),
	link_regs(4, E),
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

#घोषणा aux_regs(id)\
[id] = अणु\
	DCN2_AUX_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_aux_रेजिस्टरs link_enc_aux_regs[] = अणु
		aux_regs(0),
		aux_regs(1),
		aux_regs(2),
		aux_regs(3),
		aux_regs(4)
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
		hpd_regs(4)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_shअगरt le_shअगरt = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN20(__SHIFT),\
	DPCS_DCN21_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_mask le_mask = अणु
	LINK_ENCODER_MASK_SH_LIST_DCN20(_MASK),\
	DPCS_DCN21_MASK_SH_LIST(_MASK)
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
	शेष:
		ASSERT(0);
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा link_encoder *dcn21_link_encoder_create(
	स्थिर काष्ठा encoder_init_data *enc_init_data)
अणु
	काष्ठा dcn21_link_encoder *enc21 =
		kzalloc(माप(काष्ठा dcn21_link_encoder), GFP_KERNEL);
	पूर्णांक link_regs_id;

	अगर (!enc21)
		वापस शून्य;

	link_regs_id =
		map_transmitter_id_to_phy_instance(enc_init_data->transmitter);

	dcn21_link_encoder_स्थिरruct(enc21,
				      enc_init_data,
				      &link_enc_feature,
				      &link_enc_regs[link_regs_id],
				      &link_enc_aux_regs[enc_init_data->channel - 1],
				      &link_enc_hpd_regs[enc_init_data->hpd_source],
				      &le_shअगरt,
				      &le_mask);

	वापस &enc21->enc10.base;
पूर्ण

अटल काष्ठा panel_cntl *dcn21_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
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

अटल पूर्णांक dcn21_populate_dml_pipes_from_context(
		काष्ठा dc *dc,
		काष्ठा dc_state *context,
		display_e2e_pipe_params_st *pipes,
		bool fast_validate)
अणु
	uपूर्णांक32_t pipe_cnt = dcn20_populate_dml_pipes_from_context(dc, context, pipes, fast_validate);
	पूर्णांक i;

	क्रम (i = 0; i < pipe_cnt; i++) अणु

		pipes[i].pipe.src.hostvm = dc->res_pool->hubbub->riommu_active;
		pipes[i].pipe.src.gpuvm = 1;
	पूर्ण

	वापस pipe_cnt;
पूर्ण

क्रमागत dc_status dcn21_patch_unknown_plane_state(काष्ठा dc_plane_state *plane_state)
अणु
	क्रमागत dc_status result = DC_OK;

	अगर (plane_state->ctx->dc->debug.disable_dcc == DCC_ENABLE) अणु
		plane_state->dcc.enable = 1;
		/* align to our worst हाल block width */
		plane_state->dcc.meta_pitch = ((plane_state->src_rect.width + 1023) / 1024) * 1024;
	पूर्ण
	result = dcn20_patch_unknown_plane_state(plane_state);
	वापस result;
पूर्ण

अटल स्थिर काष्ठा resource_funcs dcn21_res_pool_funcs = अणु
	.destroy = dcn21_destroy_resource_pool,
	.link_enc_create = dcn21_link_encoder_create,
	.panel_cntl_create = dcn21_panel_cntl_create,
	.validate_bandwidth = dcn21_validate_bandwidth,
	.populate_dml_pipes = dcn21_populate_dml_pipes_from_context,
	.add_stream_to_ctx = dcn20_add_stream_to_ctx,
	.add_dsc_to_stream_resource = dcn20_add_dsc_to_stream_resource,
	.हटाओ_stream_from_ctx = dcn20_हटाओ_stream_from_ctx,
	.acquire_idle_pipe_क्रम_layer = dcn20_acquire_idle_pipe_क्रम_layer,
	.populate_dml_ग_लिखोback_from_context = dcn20_populate_dml_ग_लिखोback_from_context,
	.patch_unknown_plane_state = dcn21_patch_unknown_plane_state,
	.set_mcअगर_arb_params = dcn20_set_mcअगर_arb_params,
	.find_first_मुक्त_match_stream_enc_क्रम_link = dcn10_find_first_मुक्त_match_stream_enc_क्रम_link,
	.update_bw_bounding_box = update_bw_bounding_box
पूर्ण;

अटल bool dcn21_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा dcn21_resource_pool *pool)
अणु
	पूर्णांक i, j;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा irq_service_init_data init_data;
	uपूर्णांक32_t pipe_fuses = पढ़ो_pipe_fuses(ctx);
	uपूर्णांक32_t num_pipes;

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap_rn;
#अगर_घोषित DIAGS_BUILD
	अगर (IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment))
		//pool->base.res_cap = &res_cap_nv10_FPGA_2pipe_dsc;
		pool->base.res_cap = &res_cap_rn_FPGA_4pipe;
#पूर्ण_अगर

	pool->base.funcs = &dcn21_res_pool_funcs;

	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;

	/* max pipe num क्रम ASIC beक्रमe check pipe fuses */
	pool->base.pipe_count = pool->base.res_cap->num_timing_generator;

	dc->caps.max_करोwnscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 5; /*1.4 w/a applied by शेष*/
	dc->caps.max_cursor_size = 256;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.dmdata_alloc_size = 2048;

	dc->caps.max_slave_planes = 1;
	dc->caps.max_slave_yuv_planes = 1;
	dc->caps.max_slave_rgb_planes = 1;
	dc->caps.post_blend_color_processing = true;
	dc->caps.क्रमce_dp_tps4_क्रम_cp2520 = true;
	dc->caps.extended_aux_समयout_support = true;
	dc->caps.dmcub_support = true;
	dc->caps.is_apu = true;

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
	// no OGAM ROM on DCN2
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

	अगर (dc->ctx->dce_environment == DCE_ENV_PRODUCTION_DRV)
		dc->debug = debug_शेषs_drv;
	अन्यथा अगर (dc->ctx->dce_environment == DCE_ENV_FPGA_MAXIMUS) अणु
		pool->base.pipe_count = 4;
		dc->debug = debug_शेषs_diags;
	पूर्ण अन्यथा
		dc->debug = debug_शेषs_diags;

	// Init the vm_helper
	अगर (dc->vm_helper)
		vm_helper_init(dc->vm_helper, 16);

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL0] =
			dcn21_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL0,
				&clk_src_regs[0], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL1] =
			dcn21_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL1,
				&clk_src_regs[1], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL2] =
			dcn21_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL2,
				&clk_src_regs[2], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL3] =
			dcn21_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL3,
				&clk_src_regs[3], false);
	pool->base.घड़ी_sources[DCN20_CLK_SRC_PLL4] =
			dcn21_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL4,
				&clk_src_regs[4], false);

	pool->base.clk_src_count = DCN20_CLK_SRC_TOTAL_DCN21;

	/* toकरो: not reuse phy_pll रेजिस्टरs */
	pool->base.dp_घड़ी_source =
			dcn21_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_ID_DP_DTO,
				&clk_src_regs[0], true);

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] == शून्य) अणु
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण
	पूर्ण

	pool->base.dccg = dccg21_create(ctx, &dccg_regs, &dccg_shअगरt, &dccg_mask);
	अगर (pool->base.dccg == शून्य) अणु
		dm_error("DC: failed to create dccg!\n");
		BREAK_TO_DEBUGGER();
		जाओ create_fail;
	पूर्ण

	अगर (!dc->config.disable_dmcu) अणु
		pool->base.dmcu = dcn21_dmcu_create(ctx,
				&dmcu_regs,
				&dmcu_shअगरt,
				&dmcu_mask);
		अगर (pool->base.dmcu == शून्य) अणु
			dm_error("DC: failed to create dmcu!\n");
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण

		dc->debug.dmub_command_table = false;
	पूर्ण

	अगर (dc->config.disable_dmcu) अणु
		pool->base.psr = dmub_psr_create(ctx);

		अगर (pool->base.psr == शून्य) अणु
			dm_error("DC: failed to create psr obj!\n");
			BREAK_TO_DEBUGGER();
			जाओ create_fail;
		पूर्ण
	पूर्ण

	अगर (dc->config.disable_dmcu)
		pool->base.abm = dmub_abm_create(ctx,
			&abm_regs,
			&abm_shअगरt,
			&abm_mask);
	अन्यथा
		pool->base.abm = dce_abm_create(ctx,
			&abm_regs,
			&abm_shअगरt,
			&abm_mask);

	pool->base.pp_smu = dcn21_pp_smu_create(ctx);

	num_pipes = dcn2_1_ip.max_num_dpp;

	क्रम (i = 0; i < dcn2_1_ip.max_num_dpp; i++)
		अगर (pipe_fuses & 1 << i)
			num_pipes--;
	dcn2_1_ip.max_num_dpp = num_pipes;
	dcn2_1_ip.max_num_otg = num_pipes;

	dml_init_instance(&dc->dml, &dcn2_1_soc, &dcn2_1_ip, DML_PROJECT_DCN21);

	init_data.ctx = dc->ctx;
	pool->base.irqs = dal_irq_service_dcn21_create(&init_data);
	अगर (!pool->base.irqs)
		जाओ create_fail;

	j = 0;
	/* mem input -> ipp -> dpp -> opp -> TG */
	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		/* अगर pipe is disabled, skip instance of HW pipe,
		 * i.e, skip ASIC रेजिस्टर instance
		 */
		अगर ((pipe_fuses & (1 << i)) != 0)
			जारी;

		pool->base.hubps[j] = dcn21_hubp_create(ctx, i);
		अगर (pool->base.hubps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.ipps[j] = dcn21_ipp_create(ctx, i);
		अगर (pool->base.ipps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.dpps[j] = dcn21_dpp_create(ctx, i);
		अगर (pool->base.dpps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create dpps!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.opps[j] = dcn21_opp_create(ctx, i);
		अगर (pool->base.opps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			जाओ create_fail;
		पूर्ण

		pool->base.timing_generators[j] = dcn21_timing_generator_create(
				ctx, i);
		अगर (pool->base.timing_generators[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ create_fail;
		पूर्ण
		j++;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dcn21_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dcn21_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create hw i2c!!\n");
			जाओ create_fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	pool->base.timing_generator_count = j;
	pool->base.pipe_count = j;
	pool->base.mpcc_count = j;

	pool->base.mpc = dcn21_mpc_create(ctx);
	अगर (pool->base.mpc == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mpc!\n");
		जाओ create_fail;
	पूर्ण

	pool->base.hubbub = dcn21_hubbub_create(ctx);
	अगर (pool->base.hubbub == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create hubbub!\n");
		जाओ create_fail;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_dsc; i++) अणु
		pool->base.dscs[i] = dcn21_dsc_create(ctx, i);
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

	dcn21_hw_sequencer_स्थिरruct(dc);

	dc->caps.max_planes =  pool->base.pipe_count;

	क्रम (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	dc->cap_funcs = cap_funcs;

	वापस true;

create_fail:

	dcn21_resource_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dcn21_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc)
अणु
	काष्ठा dcn21_resource_pool *pool =
		kzalloc(माप(काष्ठा dcn21_resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dcn21_resource_स्थिरruct(init_data->num_भव_links, dc, pool))
		वापस &pool->base;

	BREAK_TO_DEBUGGER();
	kमुक्त(pool);
	वापस शून्य;
पूर्ण
