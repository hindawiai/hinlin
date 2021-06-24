<शैली गुरु>
/*
* Copyright 2016 Advanced Micro Devices, Inc.
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

#समावेश "dcn10_init.h"

#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "dcn10_resource.h"
#समावेश "dcn10_ipp.h"
#समावेश "dcn10_mpc.h"
#समावेश "irq/dcn10/irq_service_dcn10.h"
#समावेश "dcn10_dpp.h"
#समावेश "dcn10_optc.h"
#समावेश "dcn10_hw_sequencer.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dcn10_opp.h"
#समावेश "dcn10_link_encoder.h"
#समावेश "dcn10_stream_encoder.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "virtual/virtual_stream_encoder.h"
#समावेश "dce110/dce110_resource.h"
#समावेश "dce112/dce112_resource.h"
#समावेश "dcn10_hubp.h"
#समावेश "dcn10_hubbub.h"
#समावेश "dce/dce_panel_cntl.h"

#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"

#समावेश "dcn/dcn_1_0_offset.h"
#समावेश "dcn/dcn_1_0_sh_mask.h"

#समावेश "nbio/nbio_7_0_offset.h"

#समावेश "mmhub/mmhub_9_1_offset.h"
#समावेश "mmhub/mmhub_9_1_sh_mask.h"

#समावेश "reg_helper.h"
#समावेश "dce/dce_abm.h"
#समावेश "dce/dce_dmcu.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_i2c.h"

स्थिर काष्ठा _vcs_dpi_ip_params_st dcn1_0_ip = अणु
	.rob_buffer_size_kbytes = 64,
	.det_buffer_size_kbytes = 164,
	.dpte_buffer_size_in_pte_reqs_luma = 42,
	.dpp_output_buffer_pixels = 2560,
	.opp_output_buffer_lines = 1,
	.pixel_chunk_size_kbytes = 8,
	.pte_enable = 1,
	.pte_chunk_size_kbytes = 2,
	.meta_chunk_size_kbytes = 2,
	.ग_लिखोback_chunk_size_kbytes = 2,
	.line_buffer_size_bits = 589824,
	.max_line_buffer_lines = 12,
	.IsLineBufferBppFixed = 0,
	.LineBufferFixedBpp = -1,
	.ग_लिखोback_luma_buffer_size_kbytes = 12,
	.ग_लिखोback_chroma_buffer_size_kbytes = 8,
	.max_num_dpp = 4,
	.max_num_wb = 2,
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
	.min_vblank_lines = 14,
	.dppclk_delay_subtotal = 90,
	.dispclk_delay_subtotal = 42,
	.dcfclk_cstate_latency = 10,
	.max_पूर्णांकer_dcn_tile_repeaters = 8,
	.can_vstartup_lines_exceed_vsync_plus_back_porch_lines_minus_one = 0,
	.bug_क्रमcing_LC_req_same_size_fixed = 0,
पूर्ण;

स्थिर काष्ठा _vcs_dpi_soc_bounding_box_st dcn1_0_soc = अणु
	.sr_निकास_समय_us = 9.0,
	.sr_enter_plus_निकास_समय_us = 11.0,
	.urgent_latency_us = 4.0,
	.ग_लिखोback_latency_us = 12.0,
	.ideal_dram_bw_after_urgent_percent = 80.0,
	.max_request_size_bytes = 256,
	.करोwnspपढ़ो_percent = 0.5,
	.dram_page_खोलो_समय_ns = 50.0,
	.dram_rw_turnaround_समय_ns = 17.5,
	.dram_वापस_buffer_per_channel_bytes = 8192,
	.round_trip_ping_latency_dcfclk_cycles = 128,
	.urgent_out_of_order_वापस_per_channel_bytes = 256,
	.channel_पूर्णांकerleave_bytes = 256,
	.num_banks = 8,
	.num_chans = 2,
	.vmm_page_size_bytes = 4096,
	.dram_घड़ी_change_latency_us = 17.0,
	.ग_लिखोback_dram_घड़ी_change_latency_us = 23.0,
	.वापस_bus_width_bytes = 64,
पूर्ण;

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


क्रमागत dcn10_clk_src_array_id अणु
	DCN10_CLK_SRC_PLL0,
	DCN10_CLK_SRC_PLL1,
	DCN10_CLK_SRC_PLL2,
	DCN10_CLK_SRC_PLL3,
	DCN10_CLK_SRC_TOTAL,
	DCN101_CLK_SRC_TOTAL = DCN10_CLK_SRC_PLL3
पूर्ण;

/* begin *********************
 * macros to expend रेजिस्टर list macro defined in HW object header file */

/* DCN */
#घोषणा BASE_INNER(seg) \
	DCE_BASE__INST0_SEG ## seg

#घोषणा BASE(seg) \
	BASE_INNER(seg)

#घोषणा SR(reg_name)\
		.reg_name = BASE(mm ## reg_name ## _BASE_IDX) +  \
					mm ## reg_name

#घोषणा SRI(reg_name, block, id)\
	.reg_name = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name


#घोषणा SRII(reg_name, block, id)\
	.reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

#घोषणा VUPDATE_SRII(reg_name, block, id)\
	.reg_name[id] = BASE(mm ## reg_name ## 0 ## _ ## block ## id ## _BASE_IDX) + \
					mm ## reg_name ## 0 ## _ ## block ## id

/* set field/रेजिस्टर/bitfield name */
#घोषणा SFRB(field_name, reg_name, bitfield, post_fix)\
	.field_name = reg_name ## __ ## bitfield ## post_fix

/* NBIO */
#घोषणा NBIO_BASE_INNER(seg) \
	NBIF_BASE__INST0_SEG ## seg

#घोषणा NBIO_BASE(seg) \
	NBIO_BASE_INNER(seg)

#घोषणा NBIO_SR(reg_name)\
		.reg_name = NBIO_BASE(mm ## reg_name ## _BASE_IDX) +  \
					mm ## reg_name

/* MMHUB */
#घोषणा MMHUB_BASE_INNER(seg) \
	MMHUB_BASE__INST0_SEG ## seg

#घोषणा MMHUB_BASE(seg) \
	MMHUB_BASE_INNER(seg)

#घोषणा MMHUB_SR(reg_name)\
		.reg_name = MMHUB_BASE(mm ## reg_name ## _BASE_IDX) +  \
					mm ## reg_name

/* macros to expend रेजिस्टर list macro defined in HW object header file
 * end *********************/


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
		ABM_DCN10_REG_LIST(0)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_shअगरt abm_shअगरt = अणु
		ABM_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_mask abm_mask = अणु
		ABM_MASK_SH_LIST_DCN10(_MASK)
पूर्ण;

#घोषणा stream_enc_regs(id)\
[id] = अणु\
	SE_DCN_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_stream_enc_रेजिस्टरs stream_enc_regs[] = अणु
	stream_enc_regs(0),
	stream_enc_regs(1),
	stream_enc_regs(2),
	stream_enc_regs(3),
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCN10(_MASK)
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

#घोषणा aux_regs(id)\
[id] = अणु\
	AUX_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_aux_रेजिस्टरs link_enc_aux_regs[] = अणु
		aux_regs(0),
		aux_regs(1),
		aux_regs(2),
		aux_regs(3)
पूर्ण;

#घोषणा hpd_regs(id)\
[id] = अणु\
	HPD_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_hpd_रेजिस्टरs link_enc_hpd_regs[] = अणु
		hpd_regs(0),
		hpd_regs(1),
		hpd_regs(2),
		hpd_regs(3)
पूर्ण;

#घोषणा link_regs(id)\
[id] = अणु\
	LE_DCN10_REG_LIST(id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id) \
पूर्ण

अटल स्थिर काष्ठा dcn10_link_enc_रेजिस्टरs link_enc_regs[] = अणु
	link_regs(0),
	link_regs(1),
	link_regs(2),
	link_regs(3)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_shअगरt le_shअगरt = अणु
		LINK_ENCODER_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_link_enc_mask le_mask = अणु
		LINK_ENCODER_MASK_SH_LIST_DCN10(_MASK)
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

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt aux_shअगरt = अणु
	DCN10_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
	DCN10_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा ipp_regs(id)\
[id] = अणु\
	IPP_REG_LIST_DCN10(id),\
पूर्ण

अटल स्थिर काष्ठा dcn10_ipp_रेजिस्टरs ipp_regs[] = अणु
	ipp_regs(0),
	ipp_regs(1),
	ipp_regs(2),
	ipp_regs(3),
पूर्ण;

अटल स्थिर काष्ठा dcn10_ipp_shअगरt ipp_shअगरt = अणु
		IPP_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_ipp_mask ipp_mask = अणु
		IPP_MASK_SH_LIST_DCN10(_MASK),
पूर्ण;

#घोषणा opp_regs(id)\
[id] = अणु\
	OPP_REG_LIST_DCN10(id),\
पूर्ण

अटल स्थिर काष्ठा dcn10_opp_रेजिस्टरs opp_regs[] = अणु
	opp_regs(0),
	opp_regs(1),
	opp_regs(2),
	opp_regs(3),
पूर्ण;

अटल स्थिर काष्ठा dcn10_opp_shअगरt opp_shअगरt = अणु
		OPP_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn10_opp_mask opp_mask = अणु
		OPP_MASK_SH_LIST_DCN10(_MASK),
पूर्ण;

#घोषणा aux_engine_regs(id)\
[id] = अणु\
	AUX_COMMON_REG_LIST(id), \
	.AUX_RESET_MASK = 0 \
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
	TF_REG_LIST_DCN10(id),\
पूर्ण

अटल स्थिर काष्ठा dcn_dpp_रेजिस्टरs tf_regs[] = अणु
	tf_regs(0),
	tf_regs(1),
	tf_regs(2),
	tf_regs(3),
पूर्ण;

अटल स्थिर काष्ठा dcn_dpp_shअगरt tf_shअगरt = अणु
	TF_REG_LIST_SH_MASK_DCN10(__SHIFT),
	TF_DEBUG_REG_LIST_SH_DCN10

पूर्ण;

अटल स्थिर काष्ठा dcn_dpp_mask tf_mask = अणु
	TF_REG_LIST_SH_MASK_DCN10(_MASK),
	TF_DEBUG_REG_LIST_MASK_DCN10
पूर्ण;

अटल स्थिर काष्ठा dcn_mpc_रेजिस्टरs mpc_regs = अणु
		MPC_COMMON_REG_LIST_DCN1_0(0),
		MPC_COMMON_REG_LIST_DCN1_0(1),
		MPC_COMMON_REG_LIST_DCN1_0(2),
		MPC_COMMON_REG_LIST_DCN1_0(3),
		MPC_OUT_MUX_COMMON_REG_LIST_DCN1_0(0),
		MPC_OUT_MUX_COMMON_REG_LIST_DCN1_0(1),
		MPC_OUT_MUX_COMMON_REG_LIST_DCN1_0(2),
		MPC_OUT_MUX_COMMON_REG_LIST_DCN1_0(3)
पूर्ण;

अटल स्थिर काष्ठा dcn_mpc_shअगरt mpc_shअगरt = अणु
	MPC_COMMON_MASK_SH_LIST_DCN1_0(__SHIFT),\
	SFRB(CUR_VUPDATE_LOCK_SET, CUR0_VUPDATE_LOCK_SET0, CUR0_VUPDATE_LOCK_SET, __SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_mpc_mask mpc_mask = अणु
	MPC_COMMON_MASK_SH_LIST_DCN1_0(_MASK),\
	SFRB(CUR_VUPDATE_LOCK_SET, CUR0_VUPDATE_LOCK_SET0, CUR0_VUPDATE_LOCK_SET, _MASK)
पूर्ण;

#घोषणा tg_regs(id)\
[id] = अणुTG_COMMON_REG_LIST_DCN1_0(id)पूर्ण

अटल स्थिर काष्ठा dcn_optc_रेजिस्टरs tg_regs[] = अणु
	tg_regs(0),
	tg_regs(1),
	tg_regs(2),
	tg_regs(3),
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_shअगरt tg_shअगरt = अणु
	TG_COMMON_MASK_SH_LIST_DCN1_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_optc_mask tg_mask = अणु
	TG_COMMON_MASK_SH_LIST_DCN1_0(_MASK)
पूर्ण;

अटल स्थिर काष्ठा bios_रेजिस्टरs bios_regs = अणु
		NBIO_SR(BIOS_SCRATCH_3),
		NBIO_SR(BIOS_SCRATCH_6)
पूर्ण;

#घोषणा hubp_regs(id)\
[id] = अणु\
	HUBP_REG_LIST_DCN10(id)\
पूर्ण

अटल स्थिर काष्ठा dcn_mi_रेजिस्टरs hubp_regs[] = अणु
	hubp_regs(0),
	hubp_regs(1),
	hubp_regs(2),
	hubp_regs(3),
पूर्ण;

अटल स्थिर काष्ठा dcn_mi_shअगरt hubp_shअगरt = अणु
		HUBP_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_mi_mask hubp_mask = अणु
		HUBP_MASK_SH_LIST_DCN10(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_रेजिस्टरs hubbub_reg = अणु
		HUBBUB_REG_LIST_DCN10(0)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_shअगरt hubbub_shअगरt = अणु
		HUBBUB_MASK_SH_LIST_DCN10(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dcn_hubbub_mask hubbub_mask = अणु
		HUBBUB_MASK_SH_LIST_DCN10(_MASK)
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
	शेष:
		ASSERT(0);
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा clk_src_regs(index, pllid)\
[index] = अणु\
	CS_COMMON_REG_LIST_DCN1_0(index, pllid),\
पूर्ण

अटल स्थिर काष्ठा dce110_clk_src_regs clk_src_regs[] = अणु
	clk_src_regs(0, A),
	clk_src_regs(1, B),
	clk_src_regs(2, C),
	clk_src_regs(3, D)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_shअगरt cs_shअगरt = अणु
		CS_COMMON_MASK_SH_LIST_DCN1_0(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_mask cs_mask = अणु
		CS_COMMON_MASK_SH_LIST_DCN1_0(_MASK)
पूर्ण;

अटल स्थिर काष्ठा resource_caps res_cap = अणु
		.num_timing_generator = 4,
		.num_opp = 4,
		.num_video_plane = 4,
		.num_audio = 4,
		.num_stream_encoder = 4,
		.num_pll = 4,
		.num_ddc = 4,
पूर्ण;

अटल स्थिर काष्ठा resource_caps rv2_res_cap = अणु
		.num_timing_generator = 3,
		.num_opp = 3,
		.num_video_plane = 3,
		.num_audio = 3,
		.num_stream_encoder = 3,
		.num_pll = 3,
		.num_ddc = 4,
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
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_drv = अणु
		.sanity_checks = true,
		.disable_dmcu = false,
		.क्रमce_abm_enable = false,
		.timing_trace = false,
		.घड़ी_प्रकारrace = true,

		/* raven smu करोnes't allow 0 disp clk,
		 * smu min disp clk limit is 50Mhz
		 * keep min disp clk 100Mhz aव्योम smu hang
		 */
		.min_disp_clk_khz = 100000,

		.disable_pplib_घड़ी_request = false,
		.disable_pplib_wm_range = false,
		.pplib_wm_report_mode = WM_REPORT_DEFAULT,
		.pipe_split_policy = MPC_SPLIT_AVOID,
		.क्रमce_single_disp_pipe_split = false,
		.disable_dcc = DCC_ENABLE,
		.voltage_align_fclk = true,
		.disable_stereo_support = true,
		.vsr_support = true,
		.perक्रमmance_trace = false,
		.az_endpoपूर्णांक_mute_only = true,
		.recovery_enabled = false, /*enable this by शेष after testing.*/
		.max_करोwnscale_src_width = 3840,
		.underflow_निश्चित_delay_us = 0xFFFFFFFF,
पूर्ण;

अटल स्थिर काष्ठा dc_debug_options debug_शेषs_diags = अणु
		.disable_dmcu = false,
		.क्रमce_abm_enable = false,
		.timing_trace = true,
		.घड़ी_प्रकारrace = true,
		.disable_stutter = true,
		.disable_pplib_घड़ी_request = true,
		.disable_pplib_wm_range = true,
		.underflow_निश्चित_delay_us = 0xFFFFFFFF,
पूर्ण;

अटल व्योम dcn10_dpp_destroy(काष्ठा dpp **dpp)
अणु
	kमुक्त(TO_DCN10_DPP(*dpp));
	*dpp = शून्य;
पूर्ण

अटल काष्ठा dpp *dcn10_dpp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn10_dpp *dpp =
		kzalloc(माप(काष्ठा dcn10_dpp), GFP_KERNEL);

	अगर (!dpp)
		वापस शून्य;

	dpp1_स्थिरruct(dpp, ctx, inst,
		       &tf_regs[inst], &tf_shअगरt, &tf_mask);
	वापस &dpp->base;
पूर्ण

अटल काष्ठा input_pixel_processor *dcn10_ipp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn10_ipp *ipp =
		kzalloc(माप(काष्ठा dcn10_ipp), GFP_KERNEL);

	अगर (!ipp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn10_ipp_स्थिरruct(ipp, ctx, inst,
			&ipp_regs[inst], &ipp_shअगरt, &ipp_mask);
	वापस &ipp->base;
पूर्ण


अटल काष्ठा output_pixel_processor *dcn10_opp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dcn10_opp *opp =
		kzalloc(माप(काष्ठा dcn10_opp), GFP_KERNEL);

	अगर (!opp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dcn10_opp_स्थिरruct(opp, ctx, inst,
			&opp_regs[inst], &opp_shअगरt, &opp_mask);
	वापस &opp->base;
पूर्ण

काष्ठा dce_aux *dcn10_aux_engine_create(
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
		i2c_inst_regs(6),
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_shअगरt i2c_shअगरts = अणु
		I2C_COMMON_MASK_SH_LIST_DCE110(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_mask i2c_masks = अणु
		I2C_COMMON_MASK_SH_LIST_DCE110(_MASK)
पूर्ण;

काष्ठा dce_i2c_hw *dcn10_i2c_hw_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_i2c_hw *dce_i2c_hw =
		kzalloc(माप(काष्ठा dce_i2c_hw), GFP_KERNEL);

	अगर (!dce_i2c_hw)
		वापस शून्य;

	dcn1_i2c_hw_स्थिरruct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_regs[inst], &i2c_shअगरts, &i2c_masks);

	वापस dce_i2c_hw;
पूर्ण
अटल काष्ठा mpc *dcn10_mpc_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn10_mpc *mpc10 = kzalloc(माप(काष्ठा dcn10_mpc),
					  GFP_KERNEL);

	अगर (!mpc10)
		वापस शून्य;

	dcn10_mpc_स्थिरruct(mpc10, ctx,
			&mpc_regs,
			&mpc_shअगरt,
			&mpc_mask,
			4);

	वापस &mpc10->base;
पूर्ण

अटल काष्ठा hubbub *dcn10_hubbub_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn10_hubbub *dcn10_hubbub = kzalloc(माप(काष्ठा dcn10_hubbub),
					  GFP_KERNEL);

	अगर (!dcn10_hubbub)
		वापस शून्य;

	hubbub1_स्थिरruct(&dcn10_hubbub->base, ctx,
			&hubbub_reg,
			&hubbub_shअगरt,
			&hubbub_mask);

	वापस &dcn10_hubbub->base;
पूर्ण

अटल काष्ठा timing_generator *dcn10_timing_generator_create(
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

	dcn10_timing_generator_init(tgn10);

	वापस &tgn10->base;
पूर्ण

अटल स्थिर काष्ठा encoder_feature_support link_enc_feature = अणु
		.max_hdmi_deep_color = COLOR_DEPTH_121212,
		.max_hdmi_pixel_घड़ी = 600000,
		.hdmi_ycbcr420_supported = true,
		.dp_ycbcr420_supported = true,
		.flags.bits.IS_HBR2_CAPABLE = true,
		.flags.bits.IS_HBR3_CAPABLE = true,
		.flags.bits.IS_TPS3_CAPABLE = true,
		.flags.bits.IS_TPS4_CAPABLE = true
पूर्ण;

काष्ठा link_encoder *dcn10_link_encoder_create(
	स्थिर काष्ठा encoder_init_data *enc_init_data)
अणु
	काष्ठा dcn10_link_encoder *enc10 =
		kzalloc(माप(काष्ठा dcn10_link_encoder), GFP_KERNEL);
	पूर्णांक link_regs_id;

	अगर (!enc10)
		वापस शून्य;

	link_regs_id =
		map_transmitter_id_to_phy_instance(enc_init_data->transmitter);

	dcn10_link_encoder_स्थिरruct(enc10,
				      enc_init_data,
				      &link_enc_feature,
				      &link_enc_regs[link_regs_id],
				      &link_enc_aux_regs[enc_init_data->channel - 1],
				      &link_enc_hpd_regs[enc_init_data->hpd_source],
				      &le_shअगरt,
				      &le_mask);

	वापस &enc10->base;
पूर्ण

अटल काष्ठा panel_cntl *dcn10_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
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

काष्ठा घड़ी_source *dcn10_घड़ी_source_create(
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

	अगर (dce112_clk_src_स्थिरruct(clk_src, ctx, bios, id,
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

अटल काष्ठा audio *create_audio(
		काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst,
			&audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

अटल काष्ठा stream_encoder *dcn10_stream_encoder_create(
	क्रमागत engine_id eng_id,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dcn10_stream_encoder *enc1 =
		kzalloc(माप(काष्ठा dcn10_stream_encoder), GFP_KERNEL);

	अगर (!enc1)
		वापस शून्य;

	dcn10_stream_encoder_स्थिरruct(enc1, ctx, ctx->dc_bios, eng_id,
					&stream_enc_regs[eng_id],
					&se_shअगरt, &se_mask);
	वापस &enc1->base;
पूर्ण

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCN1_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCN1_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCN1_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा dce_hwseq *dcn10_hwseq_create(
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dce_hwseq *hws = kzalloc(माप(काष्ठा dce_hwseq), GFP_KERNEL);

	अगर (hws) अणु
		hws->ctx = ctx;
		hws->regs = &hwseq_reg;
		hws->shअगरts = &hwseq_shअगरt;
		hws->masks = &hwseq_mask;
		hws->wa.DEGVIDCN10_253 = true;
		hws->wa.false_optc_underflow = true;
		hws->wa.DEGVIDCN10_254 = true;
	पूर्ण
	वापस hws;
पूर्ण

अटल स्थिर काष्ठा resource_create_funcs res_create_funcs = अणु
	.पढ़ो_dce_straps = पढ़ो_dce_straps,
	.create_audio = create_audio,
	.create_stream_encoder = dcn10_stream_encoder_create,
	.create_hwseq = dcn10_hwseq_create,
पूर्ण;

अटल स्थिर काष्ठा resource_create_funcs res_create_maximus_funcs = अणु
	.पढ़ो_dce_straps = शून्य,
	.create_audio = शून्य,
	.create_stream_encoder = शून्य,
	.create_hwseq = dcn10_hwseq_create,
पूर्ण;

व्योम dcn10_घड़ी_source_destroy(काष्ठा घड़ी_source **clk_src)
अणु
	kमुक्त(TO_DCE110_CLK_SRC(*clk_src));
	*clk_src = शून्य;
पूर्ण

अटल काष्ठा pp_smu_funcs *dcn10_pp_smu_create(काष्ठा dc_context *ctx)
अणु
	काष्ठा pp_smu_funcs *pp_smu = kzalloc(माप(*pp_smu), GFP_KERNEL);

	अगर (!pp_smu)
		वापस pp_smu;

	dm_pp_get_funcs(ctx, pp_smu);
	वापस pp_smu;
पूर्ण

अटल व्योम dcn10_resource_deकाष्ठा(काष्ठा dcn10_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pool->base.stream_enc_count; i++) अणु
		अगर (pool->base.stream_enc[i] != शून्य) अणु
			kमुक्त(DCN10STRENC_FROM_STRENC(pool->base.stream_enc[i]));
			pool->base.stream_enc[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (pool->base.mpc != शून्य) अणु
		kमुक्त(TO_DCN10_MPC(pool->base.mpc));
		pool->base.mpc = शून्य;
	पूर्ण

	अगर (pool->base.hubbub != शून्य) अणु
		kमुक्त(pool->base.hubbub);
		pool->base.hubbub = शून्य;
	पूर्ण

	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		अगर (pool->base.opps[i] != शून्य)
			pool->base.opps[i]->funcs->opp_destroy(&pool->base.opps[i]);

		अगर (pool->base.dpps[i] != शून्य)
			dcn10_dpp_destroy(&pool->base.dpps[i]);

		अगर (pool->base.ipps[i] != शून्य)
			pool->base.ipps[i]->funcs->ipp_destroy(&pool->base.ipps[i]);

		अगर (pool->base.hubps[i] != शून्य) अणु
			kमुक्त(TO_DCN10_HUBP(pool->base.hubps[i]));
			pool->base.hubps[i] = शून्य;
		पूर्ण

		अगर (pool->base.irqs != शून्य) अणु
			dal_irq_service_destroy(&pool->base.irqs);
		पूर्ण

		अगर (pool->base.timing_generators[i] != शून्य)	अणु
			kमुक्त(DCN10TG_FROM_TG(pool->base.timing_generators[i]));
			pool->base.timing_generators[i] = शून्य;
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

	क्रम (i = 0; i < pool->base.audio_count; i++) अणु
		अगर (pool->base.audios[i])
			dce_aud_destroy(&pool->base.audios[i]);
	पूर्ण

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] != शून्य) अणु
			dcn10_घड़ी_source_destroy(&pool->base.घड़ी_sources[i]);
			pool->base.घड़ी_sources[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (pool->base.dp_घड़ी_source != शून्य) अणु
		dcn10_घड़ी_source_destroy(&pool->base.dp_घड़ी_source);
		pool->base.dp_घड़ी_source = शून्य;
	पूर्ण

	अगर (pool->base.abm != शून्य)
		dce_abm_destroy(&pool->base.abm);

	अगर (pool->base.dmcu != शून्य)
		dce_dmcu_destroy(&pool->base.dmcu);

	kमुक्त(pool->base.pp_smu);
पूर्ण

अटल काष्ठा hubp *dcn10_hubp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dcn10_hubp *hubp1 =
		kzalloc(माप(काष्ठा dcn10_hubp), GFP_KERNEL);

	अगर (!hubp1)
		वापस शून्य;

	dcn10_hubp_स्थिरruct(hubp1, ctx, inst,
			     &hubp_regs[inst], &hubp_shअगरt, &hubp_mask);
	वापस &hubp1->base;
पूर्ण

अटल व्योम get_pixel_घड़ी_parameters(
	स्थिर काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा pixel_clk_params *pixel_clk_params)
अणु
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;
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

	अगर (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420)
		pixel_clk_params->requested_pix_clk_100hz  /= 2;
	अगर (stream->timing.timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
		pixel_clk_params->requested_pix_clk_100hz *= 2;

पूर्ण

अटल व्योम build_clamping_params(काष्ठा dc_stream_state *stream)
अणु
	stream->clamping.clamping_level = CLAMPING_FULL_RANGE;
	stream->clamping.c_depth = stream->timing.display_color_depth;
	stream->clamping.pixel_encoding = stream->timing.pixel_encoding;
पूर्ण

अटल व्योम build_pipe_hw_param(काष्ठा pipe_ctx *pipe_ctx)
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
पूर्ण

अटल क्रमागत dc_status build_mapped_resource(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा pipe_ctx *pipe_ctx = resource_get_head_pipe_क्रम_stream(&context->res_ctx, stream);

	अगर (!pipe_ctx)
		वापस DC_ERROR_UNEXPECTED;

	build_pipe_hw_param(pipe_ctx);
	वापस DC_OK;
पूर्ण

क्रमागत dc_status dcn10_add_stream_to_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *dc_stream)
अणु
	क्रमागत dc_status result = DC_ERROR_UNEXPECTED;

	result = resource_map_pool_resources(dc, new_ctx, dc_stream);

	अगर (result == DC_OK)
		result = resource_map_phy_घड़ी_resources(dc, new_ctx, dc_stream);


	अगर (result == DC_OK)
		result = build_mapped_resource(dc, new_ctx, dc_stream);

	वापस result;
पूर्ण

अटल काष्ठा pipe_ctx *dcn10_acquire_idle_pipe_क्रम_layer(
		काष्ठा dc_state *context,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा resource_context *res_ctx = &context->res_ctx;
	काष्ठा pipe_ctx *head_pipe = resource_get_head_pipe_क्रम_stream(res_ctx, stream);
	काष्ठा pipe_ctx *idle_pipe = find_idle_secondary_pipe(res_ctx, pool, head_pipe);

	अगर (!head_pipe) अणु
		ASSERT(0);
		वापस शून्य;
	पूर्ण

	अगर (!idle_pipe)
		वापस शून्य;

	idle_pipe->stream = head_pipe->stream;
	idle_pipe->stream_res.tg = head_pipe->stream_res.tg;
	idle_pipe->stream_res.abm = head_pipe->stream_res.abm;
	idle_pipe->stream_res.opp = head_pipe->stream_res.opp;

	idle_pipe->plane_res.hubp = pool->hubps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.ipp = pool->ipps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.dpp = pool->dpps[idle_pipe->pipe_idx];
	idle_pipe->plane_res.mpcc_inst = pool->dpps[idle_pipe->pipe_idx]->inst;

	वापस idle_pipe;
पूर्ण

अटल bool dcn10_get_dcc_compression_cap(स्थिर काष्ठा dc *dc,
		स्थिर काष्ठा dc_dcc_surface_param *input,
		काष्ठा dc_surface_dcc_cap *output)
अणु
	वापस dc->res_pool->hubbub->funcs->get_dcc_compression_cap(
			dc->res_pool->hubbub,
			input,
			output);
पूर्ण

अटल व्योम dcn10_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dcn10_resource_pool *dcn10_pool = TO_DCN10_RES_POOL(*pool);

	dcn10_resource_deकाष्ठा(dcn10_pool);
	kमुक्त(dcn10_pool);
	*pool = शून्य;
पूर्ण

अटल क्रमागत dc_status dcn10_validate_plane(स्थिर काष्ठा dc_plane_state *plane_state, काष्ठा dc_caps *caps)
अणु
	अगर (plane_state->क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN
			&& caps->max_video_width != 0
			&& plane_state->src_rect.width > caps->max_video_width)
		वापस DC_FAIL_SURFACE_VALIDATE;

	वापस DC_OK;
पूर्ण

अटल क्रमागत dc_status dcn10_validate_global(काष्ठा dc *dc, काष्ठा dc_state *context)
अणु
	पूर्णांक i, j;
	bool video_करोwn_scaled = false;
	bool video_large = false;
	bool desktop_large = false;
	bool dcc_disabled = false;
	bool mpo_enabled = false;

	क्रम (i = 0; i < context->stream_count; i++) अणु
		अगर (context->stream_status[i].plane_count == 0)
			जारी;

		अगर (context->stream_status[i].plane_count > 2)
			वापस DC_FAIL_UNSUPPORTED_1;

		अगर (context->stream_status[i].plane_count > 1)
			mpo_enabled = true;

		क्रम (j = 0; j < context->stream_status[i].plane_count; j++) अणु
			काष्ठा dc_plane_state *plane =
				context->stream_status[i].plane_states[j];


			अगर (plane->क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) अणु

				अगर (plane->src_rect.width > plane->dst_rect.width ||
						plane->src_rect.height > plane->dst_rect.height)
					video_करोwn_scaled = true;

				अगर (plane->src_rect.width >= 3840)
					video_large = true;

			पूर्ण अन्यथा अणु
				अगर (plane->src_rect.width >= 3840)
					desktop_large = true;
				अगर (!plane->dcc.enable)
					dcc_disabled = true;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Disable MPO in multi-display configurations. */
	अगर (context->stream_count > 1 && mpo_enabled)
		वापस DC_FAIL_UNSUPPORTED_1;

	/*
	 * Workaround: On DCN10 there is UMC issue that causes underflow when
	 * playing 4k video on 4k desktop with video करोwnscaled and single channel
	 * memory
	 */
	अगर (video_large && desktop_large && video_करोwn_scaled && dcc_disabled &&
			dc->dcn_soc->number_of_channels == 1)
		वापस DC_FAIL_SURFACE_VALIDATE;

	वापस DC_OK;
पूर्ण

अटल क्रमागत dc_status dcn10_patch_unknown_plane_state(काष्ठा dc_plane_state *plane_state)
अणु
	क्रमागत dc_status result = DC_OK;

	क्रमागत surface_pixel_क्रमmat surf_pix_क्रमmat = plane_state->क्रमmat;
	अचिन्हित पूर्णांक bpp = resource_pixel_क्रमmat_to_bpp(surf_pix_क्रमmat);

	क्रमागत swizzle_mode_values swizzle = DC_SW_LINEAR;

	अगर (bpp == 64)
		swizzle = DC_SW_64KB_D;
	अन्यथा
		swizzle = DC_SW_64KB_S;

	plane_state->tiling_info.gfx9.swizzle = swizzle;
	वापस result;
पूर्ण

काष्ठा stream_encoder *dcn10_find_first_मुक्त_match_stream_enc_क्रम_link(
		काष्ठा resource_context *res_ctx,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream)
अणु
	पूर्णांक i;
	पूर्णांक j = -1;
	काष्ठा dc_link *link = stream->link;

	क्रम (i = 0; i < pool->stream_enc_count; i++) अणु
		अगर (!res_ctx->is_stream_enc_acquired[i] &&
				pool->stream_enc[i]) अणु
			/* Store first available क्रम MST second display
			 * in daisy chain use हाल
			 */
			j = i;
			अगर (pool->stream_enc[i]->id ==
					link->link_enc->preferred_engine)
				वापस pool->stream_enc[i];
		पूर्ण
	पूर्ण

	/*
	 * For CZ and later, we can allow DIG FE and BE to dअगरfer क्रम all display types
	 */

	अगर (j >= 0)
		वापस pool->stream_enc[j];

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dc_cap_funcs cap_funcs = अणु
	.get_dcc_compression_cap = dcn10_get_dcc_compression_cap
पूर्ण;

अटल स्थिर काष्ठा resource_funcs dcn10_res_pool_funcs = अणु
	.destroy = dcn10_destroy_resource_pool,
	.link_enc_create = dcn10_link_encoder_create,
	.panel_cntl_create = dcn10_panel_cntl_create,
	.validate_bandwidth = dcn_validate_bandwidth,
	.acquire_idle_pipe_क्रम_layer = dcn10_acquire_idle_pipe_क्रम_layer,
	.validate_plane = dcn10_validate_plane,
	.validate_global = dcn10_validate_global,
	.add_stream_to_ctx = dcn10_add_stream_to_ctx,
	.patch_unknown_plane_state = dcn10_patch_unknown_plane_state,
	.find_first_मुक्त_match_stream_enc_क्रम_link = dcn10_find_first_मुक्त_match_stream_enc_क्रम_link
पूर्ण;

अटल uपूर्णांक32_t पढ़ो_pipe_fuses(काष्ठा dc_context *ctx)
अणु
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(ctx, mmCC_DC_PIPE_DIS, 0);
	/* RV1 support max 4 pipes */
	value = value & 0xf;
	वापस value;
पूर्ण

/*
 * Some architectures करोn't support soft-भग्न (e.g. aarch64), on those
 * this function has to be called with hardभग्न enabled, make sure not
 * to अंतरभूत it so whatever fp stuff is करोne stays inside
 */
अटल noअंतरभूत व्योम dcn10_resource_स्थिरruct_fp(
	काष्ठा dc *dc)
अणु
	अगर (dc->ctx->dce_version == DCN_VERSION_1_01) अणु
		काष्ठा dcn_soc_bounding_box *dcn_soc = dc->dcn_soc;
		काष्ठा dcn_ip_params *dcn_ip = dc->dcn_ip;
		काष्ठा display_mode_lib *dml = &dc->dml;

		dml->ip.max_num_dpp = 3;
		/* TODO how to handle 23.84? */
		dcn_soc->dram_घड़ी_change_latency = 23;
		dcn_ip->max_num_dpp = 3;
	पूर्ण
	अगर (ASICREV_IS_RV1_F0(dc->ctx->asic_id.hw_पूर्णांकernal_rev)) अणु
		dc->dcn_soc->urgent_latency = 3;
		dc->debug.disable_dmcu = true;
		dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9 = 41.60f;
	पूर्ण


	dc->dcn_soc->number_of_channels = dc->ctx->asic_id.vram_width / ddr4_dram_width;
	ASSERT(dc->dcn_soc->number_of_channels < 3);
	अगर (dc->dcn_soc->number_of_channels == 0)/*old sbios bug*/
		dc->dcn_soc->number_of_channels = 2;

	अगर (dc->dcn_soc->number_of_channels == 1) अणु
		dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9 = 19.2f;
		dc->dcn_soc->fabric_and_dram_bandwidth_vnom0p8 = 17.066f;
		dc->dcn_soc->fabric_and_dram_bandwidth_vmid0p72 = 14.933f;
		dc->dcn_soc->fabric_and_dram_bandwidth_vmin0p65 = 12.8f;
		अगर (ASICREV_IS_RV1_F0(dc->ctx->asic_id.hw_पूर्णांकernal_rev)) अणु
			dc->dcn_soc->fabric_and_dram_bandwidth_vmax0p9 = 20.80f;
		पूर्ण
	पूर्ण
पूर्ण

अटल bool dcn10_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा dcn10_resource_pool *pool)
अणु
	पूर्णांक i;
	पूर्णांक j;
	काष्ठा dc_context *ctx = dc->ctx;
	uपूर्णांक32_t pipe_fuses = पढ़ो_pipe_fuses(ctx);

	ctx->dc_bios->regs = &bios_regs;

	अगर (ctx->dce_version == DCN_VERSION_1_01)
		pool->base.res_cap = &rv2_res_cap;
	अन्यथा
		pool->base.res_cap = &res_cap;
	pool->base.funcs = &dcn10_res_pool_funcs;

	/*
	 * TODO fill in from actual raven resource when we create
	 * more than भव encoder
	 */

	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;

	/* max pipe num क्रम ASIC beक्रमe check pipe fuses */
	pool->base.pipe_count = pool->base.res_cap->num_timing_generator;

	अगर (dc->ctx->dce_version == DCN_VERSION_1_01)
		pool->base.pipe_count = 3;
	dc->caps.max_video_width = 3840;
	dc->caps.max_करोwnscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100; /*1.4 w/a not applied by शेष*/
	dc->caps.max_cursor_size = 256;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.max_slave_planes = 1;
	dc->caps.max_slave_yuv_planes = 1;
	dc->caps.max_slave_rgb_planes = 0;
	dc->caps.is_apu = true;
	dc->caps.post_blend_color_processing = false;
	dc->caps.extended_aux_समयout_support = false;

	/* Raven DP PHY HBR2 eye diagram pattern is not stable. Use TP4 */
	dc->caps.क्रमce_dp_tps4_क्रम_cp2520 = true;

	/* Color pipeline capabilities */
	dc->caps.color.dpp.dcn_arch = 1;
	dc->caps.color.dpp.input_lut_shared = 1;
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

	dc->caps.color.dpp.hw_3d_lut = 0;
	dc->caps.color.dpp.ogam_ram = 1; // RGAM on DCN1
	dc->caps.color.dpp.ogam_rom_caps.srgb = 1;
	dc->caps.color.dpp.ogam_rom_caps.bt2020 = 1;
	dc->caps.color.dpp.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.dpp.ogam_rom_caps.pq = 0;
	dc->caps.color.dpp.ogam_rom_caps.hlg = 0;
	dc->caps.color.dpp.ocsc = 1;

	/* no post-blend color operations */
	dc->caps.color.mpc.gamut_remap = 0;
	dc->caps.color.mpc.num_3dluts = 0;
	dc->caps.color.mpc.shared_3d_lut = 0;
	dc->caps.color.mpc.ogam_ram = 0;
	dc->caps.color.mpc.ogam_rom_caps.srgb = 0;
	dc->caps.color.mpc.ogam_rom_caps.bt2020 = 0;
	dc->caps.color.mpc.ogam_rom_caps.gamma2_2 = 0;
	dc->caps.color.mpc.ogam_rom_caps.pq = 0;
	dc->caps.color.mpc.ogam_rom_caps.hlg = 0;
	dc->caps.color.mpc.ocsc = 0;

	अगर (dc->ctx->dce_environment == DCE_ENV_PRODUCTION_DRV)
		dc->debug = debug_शेषs_drv;
	अन्यथा
		dc->debug = debug_शेषs_diags;

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	pool->base.घड़ी_sources[DCN10_CLK_SRC_PLL0] =
			dcn10_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL0,
				&clk_src_regs[0], false);
	pool->base.घड़ी_sources[DCN10_CLK_SRC_PLL1] =
			dcn10_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL1,
				&clk_src_regs[1], false);
	pool->base.घड़ी_sources[DCN10_CLK_SRC_PLL2] =
			dcn10_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL2,
				&clk_src_regs[2], false);

	अगर (dc->ctx->dce_version == DCN_VERSION_1_0) अणु
		pool->base.घड़ी_sources[DCN10_CLK_SRC_PLL3] =
				dcn10_घड़ी_source_create(ctx, ctx->dc_bios,
					CLOCK_SOURCE_COMBO_PHY_PLL3,
					&clk_src_regs[3], false);
	पूर्ण

	pool->base.clk_src_count = DCN10_CLK_SRC_TOTAL;

	अगर (dc->ctx->dce_version == DCN_VERSION_1_01)
		pool->base.clk_src_count = DCN101_CLK_SRC_TOTAL;

	pool->base.dp_घड़ी_source =
			dcn10_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_ID_DP_DTO,
				/* toकरो: not reuse phy_pll रेजिस्टरs */
				&clk_src_regs[0], true);

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] == शून्य) अणु
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			जाओ fail;
		पूर्ण
	पूर्ण

	pool->base.dmcu = dcn10_dmcu_create(ctx,
			&dmcu_regs,
			&dmcu_shअगरt,
			&dmcu_mask);
	अगर (pool->base.dmcu == शून्य) अणु
		dm_error("DC: failed to create dmcu!\n");
		BREAK_TO_DEBUGGER();
		जाओ fail;
	पूर्ण

	pool->base.abm = dce_abm_create(ctx,
			&abm_regs,
			&abm_shअगरt,
			&abm_mask);
	अगर (pool->base.abm == शून्य) अणु
		dm_error("DC: failed to create abm!\n");
		BREAK_TO_DEBUGGER();
		जाओ fail;
	पूर्ण

	dml_init_instance(&dc->dml, &dcn1_0_soc, &dcn1_0_ip, DML_PROJECT_RAVEN1);
	स_नकल(dc->dcn_ip, &dcn10_ip_शेषs, माप(dcn10_ip_शेषs));
	स_नकल(dc->dcn_soc, &dcn10_soc_शेषs, माप(dcn10_soc_शेषs));

	/* Other architectures we build क्रम build this with soft-भग्न */
	dcn10_resource_स्थिरruct_fp(dc);

	pool->base.pp_smu = dcn10_pp_smu_create(ctx);

	/*
	 * Right now SMU/PPLIB and DAL all have the AZ D3 क्रमce PME notअगरication *
	 * implemented. So AZ D3 should work.For issue 197007.                   *
	 */
	अगर (pool->base.pp_smu != शून्य
			&& pool->base.pp_smu->rv_funcs.set_pme_wa_enable != शून्य)
		dc->debug.az_endpoपूर्णांक_mute_only = false;

	अगर (!dc->debug.disable_pplib_घड़ी_request)
		dcn_bw_update_from_pplib(dc);
	dcn_bw_sync_calcs_and_dml(dc);
	अगर (!dc->debug.disable_pplib_wm_range) अणु
		dc->res_pool = &pool->base;
		dcn_bw_notअगरy_pplib_of_wm_ranges(dc);
	पूर्ण

	अणु
		काष्ठा irq_service_init_data init_data;
		init_data.ctx = dc->ctx;
		pool->base.irqs = dal_irq_service_dcn10_create(&init_data);
		अगर (!pool->base.irqs)
			जाओ fail;
	पूर्ण

	/* index to valid pipe resource  */
	j = 0;
	/* mem input -> ipp -> dpp -> opp -> TG */
	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		/* अगर pipe is disabled, skip instance of HW pipe,
		 * i.e, skip ASIC रेजिस्टर instance
		 */
		अगर ((pipe_fuses & (1 << i)) != 0)
			जारी;

		pool->base.hubps[j] = dcn10_hubp_create(ctx, i);
		अगर (pool->base.hubps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			जाओ fail;
		पूर्ण

		pool->base.ipps[j] = dcn10_ipp_create(ctx, i);
		अगर (pool->base.ipps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			जाओ fail;
		पूर्ण

		pool->base.dpps[j] = dcn10_dpp_create(ctx, i);
		अगर (pool->base.dpps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create dpp!\n");
			जाओ fail;
		पूर्ण

		pool->base.opps[j] = dcn10_opp_create(ctx, i);
		अगर (pool->base.opps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			जाओ fail;
		पूर्ण

		pool->base.timing_generators[j] = dcn10_timing_generator_create(
				ctx, i);
		अगर (pool->base.timing_generators[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ fail;
		पूर्ण
		/* check next valid pipe */
		j++;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dcn10_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dcn10_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create hw i2c!!\n");
			जाओ fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	/* valid pipe num */
	pool->base.pipe_count = j;
	pool->base.timing_generator_count = j;

	/* within dml lib, it is hard code to 4. If ASIC pipe is fused,
	 * the value may be changed
	 */
	dc->dml.ip.max_num_dpp = pool->base.pipe_count;
	dc->dcn_ip->max_num_dpp = pool->base.pipe_count;

	pool->base.mpc = dcn10_mpc_create(ctx);
	अगर (pool->base.mpc == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create mpc!\n");
		जाओ fail;
	पूर्ण

	pool->base.hubbub = dcn10_hubbub_create(ctx);
	अगर (pool->base.hubbub == शून्य) अणु
		BREAK_TO_DEBUGGER();
		dm_error("DC: failed to create hubbub!\n");
		जाओ fail;
	पूर्ण

	अगर (!resource_स्थिरruct(num_भव_links, dc, &pool->base,
			(!IS_FPGA_MAXIMUS_DC(dc->ctx->dce_environment) ?
			&res_create_funcs : &res_create_maximus_funcs)))
			जाओ fail;

	dcn10_hw_sequencer_स्थिरruct(dc);
	dc->caps.max_planes =  pool->base.pipe_count;

	क्रम (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	dc->cap_funcs = cap_funcs;

	वापस true;

fail:

	dcn10_resource_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dcn10_create_resource_pool(
		स्थिर काष्ठा dc_init_data *init_data,
		काष्ठा dc *dc)
अणु
	काष्ठा dcn10_resource_pool *pool =
		kzalloc(माप(काष्ठा dcn10_resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dcn10_resource_स्थिरruct(init_data->num_भव_links, dc, pool))
		वापस &pool->base;

	kमुक्त(pool);
	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण
