<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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

#समावेश "link_encoder.h"
#समावेश "stream_encoder.h"

#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "../virtual/virtual_stream_encoder.h"
#समावेश "dce110/dce110_resource.h"
#समावेश "dce110/dce110_timing_generator.h"
#समावेश "irq/dce110/irq_service_dce110.h"
#समावेश "dce/dce_link_encoder.h"
#समावेश "dce/dce_stream_encoder.h"
#समावेश "dce/dce_mem_input.h"
#समावेश "dce/dce_ipp.h"
#समावेश "dce/dce_transform.h"
#समावेश "dce/dce_opp.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "dce100/dce100_hw_sequencer.h"
#समावेश "dce/dce_panel_cntl.h"

#समावेश "reg_helper.h"

#समावेश "dce/dce_10_0_d.h"
#समावेश "dce/dce_10_0_sh_mask.h"

#समावेश "dce/dce_dmcu.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_abm.h"
#समावेश "dce/dce_i2c.h"

#समावेश "dce100_resource.h"

#अगर_अघोषित mmMC_HUB_RDREQ_DMIF_LIMIT
#समावेश "gmc/gmc_8_2_d.h"
#समावेश "gmc/gmc_8_2_sh_mask.h"
#पूर्ण_अगर

#अगर_अघोषित mmDP_DPHY_INTERNAL_CTRL
	#घोषणा mmDP_DPHY_INTERNAL_CTRL 0x4aa7
	#घोषणा mmDP0_DP_DPHY_INTERNAL_CTRL 0x4aa7
	#घोषणा mmDP1_DP_DPHY_INTERNAL_CTRL 0x4ba7
	#घोषणा mmDP2_DP_DPHY_INTERNAL_CTRL 0x4ca7
	#घोषणा mmDP3_DP_DPHY_INTERNAL_CTRL 0x4da7
	#घोषणा mmDP4_DP_DPHY_INTERNAL_CTRL 0x4ea7
	#घोषणा mmDP5_DP_DPHY_INTERNAL_CTRL 0x4fa7
	#घोषणा mmDP6_DP_DPHY_INTERNAL_CTRL 0x54a7
	#घोषणा mmDP7_DP_DPHY_INTERNAL_CTRL 0x56a7
	#घोषणा mmDP8_DP_DPHY_INTERNAL_CTRL 0x57a7
#पूर्ण_अगर

#अगर_अघोषित mmBIOS_SCRATCH_2
	#घोषणा mmBIOS_SCRATCH_2 0x05CB
	#घोषणा mmBIOS_SCRATCH_3 0x05CC
	#घोषणा mmBIOS_SCRATCH_6 0x05CF
#पूर्ण_अगर

#अगर_अघोषित mmDP_DPHY_BS_SR_SWAP_CNTL
	#घोषणा mmDP_DPHY_BS_SR_SWAP_CNTL                       0x4ADC
	#घोषणा mmDP0_DP_DPHY_BS_SR_SWAP_CNTL                   0x4ADC
	#घोषणा mmDP1_DP_DPHY_BS_SR_SWAP_CNTL                   0x4BDC
	#घोषणा mmDP2_DP_DPHY_BS_SR_SWAP_CNTL                   0x4CDC
	#घोषणा mmDP3_DP_DPHY_BS_SR_SWAP_CNTL                   0x4DDC
	#घोषणा mmDP4_DP_DPHY_BS_SR_SWAP_CNTL                   0x4EDC
	#घोषणा mmDP5_DP_DPHY_BS_SR_SWAP_CNTL                   0x4FDC
	#घोषणा mmDP6_DP_DPHY_BS_SR_SWAP_CNTL                   0x54DC
#पूर्ण_अगर

#अगर_अघोषित mmDP_DPHY_FAST_TRAINING
	#घोषणा mmDP_DPHY_FAST_TRAINING                         0x4ABC
	#घोषणा mmDP0_DP_DPHY_FAST_TRAINING                     0x4ABC
	#घोषणा mmDP1_DP_DPHY_FAST_TRAINING                     0x4BBC
	#घोषणा mmDP2_DP_DPHY_FAST_TRAINING                     0x4CBC
	#घोषणा mmDP3_DP_DPHY_FAST_TRAINING                     0x4DBC
	#घोषणा mmDP4_DP_DPHY_FAST_TRAINING                     0x4EBC
	#घोषणा mmDP5_DP_DPHY_FAST_TRAINING                     0x4FBC
	#घोषणा mmDP6_DP_DPHY_FAST_TRAINING                     0x54BC
#पूर्ण_अगर

अटल स्थिर काष्ठा dce110_timing_generator_offsets dce100_tg_offsets[] = अणु
	अणु
		.crtc = (mmCRTC0_CRTC_CONTROL - mmCRTC_CONTROL),
		.dcp =  (mmDCP0_GRPH_CONTROL - mmGRPH_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC1_CRTC_CONTROL - mmCRTC_CONTROL),
		.dcp = (mmDCP1_GRPH_CONTROL - mmGRPH_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC2_CRTC_CONTROL - mmCRTC_CONTROL),
		.dcp = (mmDCP2_GRPH_CONTROL - mmGRPH_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC3_CRTC_CONTROL - mmCRTC_CONTROL),
		.dcp =  (mmDCP3_GRPH_CONTROL - mmGRPH_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC4_CRTC_CONTROL - mmCRTC_CONTROL),
		.dcp = (mmDCP4_GRPH_CONTROL - mmGRPH_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC5_CRTC_CONTROL - mmCRTC_CONTROL),
		.dcp = (mmDCP5_GRPH_CONTROL - mmGRPH_CONTROL),
	पूर्ण
पूर्ण;

/* set रेजिस्टर offset */
#घोषणा SR(reg_name)\
	.reg_name = mm ## reg_name

/* set रेजिस्टर offset with instance */
#घोषणा SRI(reg_name, block, id)\
	.reg_name = mm ## block ## id ## _ ## reg_name

#घोषणा ipp_regs(id)\
[id] = अणु\
		IPP_DCE100_REG_LIST_DCE_BASE(id)\
पूर्ण

अटल स्थिर काष्ठा dce_ipp_रेजिस्टरs ipp_regs[] = अणु
		ipp_regs(0),
		ipp_regs(1),
		ipp_regs(2),
		ipp_regs(3),
		ipp_regs(4),
		ipp_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dce_ipp_shअगरt ipp_shअगरt = अणु
		IPP_DCE100_MASK_SH_LIST_DCE_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_ipp_mask ipp_mask = अणु
		IPP_DCE100_MASK_SH_LIST_DCE_COMMON_BASE(_MASK)
पूर्ण;

#घोषणा transक्रमm_regs(id)\
[id] = अणु\
		XFM_COMMON_REG_LIST_DCE100(id)\
पूर्ण

अटल स्थिर काष्ठा dce_transक्रमm_रेजिस्टरs xfm_regs[] = अणु
		transक्रमm_regs(0),
		transक्रमm_regs(1),
		transक्रमm_regs(2),
		transक्रमm_regs(3),
		transक्रमm_regs(4),
		transक्रमm_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dce_transक्रमm_shअगरt xfm_shअगरt = अणु
		XFM_COMMON_MASK_SH_LIST_DCE110(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_transक्रमm_mask xfm_mask = अणु
		XFM_COMMON_MASK_SH_LIST_DCE110(_MASK)
पूर्ण;

#घोषणा aux_regs(id)\
[id] = अणु\
	AUX_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dce110_link_enc_aux_रेजिस्टरs link_enc_aux_regs[] = अणु
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

अटल स्थिर काष्ठा dce110_link_enc_hpd_रेजिस्टरs link_enc_hpd_regs[] = अणु
		hpd_regs(0),
		hpd_regs(1),
		hpd_regs(2),
		hpd_regs(3),
		hpd_regs(4),
		hpd_regs(5)
पूर्ण;

#घोषणा link_regs(id)\
[id] = अणु\
	LE_DCE100_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा dce110_link_enc_रेजिस्टरs link_enc_regs[] = अणु
	link_regs(0),
	link_regs(1),
	link_regs(2),
	link_regs(3),
	link_regs(4),
	link_regs(5),
	link_regs(6),
पूर्ण;

#घोषणा stream_enc_regs(id)\
[id] = अणु\
	SE_COMMON_REG_LIST_DCE_BASE(id),\
	.AFMT_CNTL = 0,\
पूर्ण

अटल स्थिर काष्ठा dce110_stream_enc_रेजिस्टरs stream_enc_regs[] = अणु
	stream_enc_regs(0),
	stream_enc_regs(1),
	stream_enc_regs(2),
	stream_enc_regs(3),
	stream_enc_regs(4),
	stream_enc_regs(5),
	stream_enc_regs(6)
पूर्ण;

अटल स्थिर काष्ठा dce_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCE80_100(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCE80_100(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_रेजिस्टरs panel_cntl_regs[] = अणु
	अणु DCE_PANEL_CNTL_REG_LIST() पूर्ण
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_shअगरt panel_cntl_shअगरt = अणु
	DCE_PANEL_CNTL_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_panel_cntl_mask panel_cntl_mask = अणु
	DCE_PANEL_CNTL_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा opp_regs(id)\
[id] = अणु\
	OPP_DCE_100_REG_LIST(id),\
पूर्ण

अटल स्थिर काष्ठा dce_opp_रेजिस्टरs opp_regs[] = अणु
	opp_regs(0),
	opp_regs(1),
	opp_regs(2),
	opp_regs(3),
	opp_regs(4),
	opp_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dce_opp_shअगरt opp_shअगरt = अणु
	OPP_COMMON_MASK_SH_LIST_DCE_100(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_opp_mask opp_mask = अणु
	OPP_COMMON_MASK_SH_LIST_DCE_100(_MASK)
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

अटल स्थिर काष्ठा dce_audio_shअगरt audio_shअगरt = अणु
		AUD_COMMON_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_audio_mask audio_mask = अणु
		AUD_COMMON_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा clk_src_regs(id)\
[id] = अणु\
	CS_COMMON_REG_LIST_DCE_100_110(id),\
पूर्ण

अटल स्थिर काष्ठा dce110_clk_src_regs clk_src_regs[] = अणु
	clk_src_regs(0),
	clk_src_regs(1),
	clk_src_regs(2)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_shअगरt cs_shअगरt = अणु
		CS_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_mask cs_mask = अणु
		CS_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_dmcu_रेजिस्टरs dmcu_regs = अणु
		DMCU_DCE110_COMMON_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_dmcu_shअगरt dmcu_shअगरt = अणु
		DMCU_MASK_SH_LIST_DCE110(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_dmcu_mask dmcu_mask = अणु
		DMCU_MASK_SH_LIST_DCE110(_MASK)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_रेजिस्टरs abm_regs = अणु
		ABM_DCE110_COMMON_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_abm_shअगरt abm_shअगरt = अणु
		ABM_MASK_SH_LIST_DCE110(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_abm_mask abm_mask = अणु
		ABM_MASK_SH_LIST_DCE110(_MASK)
पूर्ण;

#घोषणा DCFE_MEM_PWR_CTRL_REG_BASE 0x1b03

अटल स्थिर काष्ठा bios_रेजिस्टरs bios_regs = अणु
	.BIOS_SCRATCH_3 = mmBIOS_SCRATCH_3,
	.BIOS_SCRATCH_6 = mmBIOS_SCRATCH_6
पूर्ण;

अटल स्थिर काष्ठा resource_caps res_cap = अणु
	.num_timing_generator = 6,
	.num_audio = 6,
	.num_stream_encoder = 6,
	.num_pll = 3,
	.num_ddc = 6,
पूर्ण;

अटल स्थिर काष्ठा dc_plane_cap plane_cap = अणु
	.type = DC_PLANE_TYPE_DCE_RGB,

	.pixel_क्रमmat_support = अणु
			.argb8888 = true,
			.nv12 = false,
			.fp16 = true
	पूर्ण,

	.max_upscale_factor = अणु
			.argb8888 = 16000,
			.nv12 = 1,
			.fp16 = 1
	पूर्ण,

	.max_करोwnscale_factor = अणु
			.argb8888 = 250,
			.nv12 = 1,
			.fp16 = 1
	पूर्ण
पूर्ण;

#घोषणा CTX  ctx
#घोषणा REG(reg) mm ## reg

#अगर_अघोषित mmCC_DC_HDMI_STRAPS
#घोषणा mmCC_DC_HDMI_STRAPS 0x1918
#घोषणा CC_DC_HDMI_STRAPS__HDMI_DISABLE_MASK 0x40
#घोषणा CC_DC_HDMI_STRAPS__HDMI_DISABLE__SHIFT 0x6
#घोषणा CC_DC_HDMI_STRAPS__AUDIO_STREAM_NUMBER_MASK 0x700
#घोषणा CC_DC_HDMI_STRAPS__AUDIO_STREAM_NUMBER__SHIFT 0x8
#पूर्ण_अगर

अटल पूर्णांक map_transmitter_id_to_phy_instance(
	क्रमागत transmitter transmitter)
अणु
	चयन (transmitter) अणु
	हाल TRANSMITTER_UNIPHY_A:
		वापस 0;
	हाल TRANSMITTER_UNIPHY_B:
		वापस 1;
	हाल TRANSMITTER_UNIPHY_C:
		वापस 2;
	हाल TRANSMITTER_UNIPHY_D:
		वापस 3;
	हाल TRANSMITTER_UNIPHY_E:
		वापस 4;
	हाल TRANSMITTER_UNIPHY_F:
		वापस 5;
	हाल TRANSMITTER_UNIPHY_G:
		वापस 6;
	शेष:
		ASSERT(0);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_dce_straps(
	काष्ठा dc_context *ctx,
	काष्ठा resource_straps *straps)
अणु
	REG_GET_2(CC_DC_HDMI_STRAPS,
			HDMI_DISABLE, &straps->hdmi_disable,
			AUDIO_STREAM_NUMBER, &straps->audio_stream_number);

	REG_GET(DC_PINSTRAPS, DC_PINSTRAPS_AUDIO, &straps->dc_pinstraps_audio);
पूर्ण

अटल काष्ठा audio *create_audio(
		काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst,
			&audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

अटल काष्ठा timing_generator *dce100_timing_generator_create(
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t instance,
		स्थिर काष्ठा dce110_timing_generator_offsets *offsets)
अणु
	काष्ठा dce110_timing_generator *tg110 =
		kzalloc(माप(काष्ठा dce110_timing_generator), GFP_KERNEL);

	अगर (!tg110)
		वापस शून्य;

	dce110_timing_generator_स्थिरruct(tg110, ctx, instance, offsets);
	वापस &tg110->base;
पूर्ण

अटल काष्ठा stream_encoder *dce100_stream_encoder_create(
	क्रमागत engine_id eng_id,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dce110_stream_encoder *enc110 =
		kzalloc(माप(काष्ठा dce110_stream_encoder), GFP_KERNEL);

	अगर (!enc110)
		वापस शून्य;

	dce110_stream_encoder_स्थिरruct(enc110, ctx, ctx->dc_bios, eng_id,
					&stream_enc_regs[eng_id], &se_shअगरt, &se_mask);
	वापस &enc110->base;
पूर्ण

#घोषणा SRII(reg_name, block, id)\
	.reg_name[id] = mm ## block ## id ## _ ## reg_name

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCE10_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCE10_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCE10_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा dce_hwseq *dce100_hwseq_create(
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
	.create_audio = create_audio,
	.create_stream_encoder = dce100_stream_encoder_create,
	.create_hwseq = dce100_hwseq_create,
पूर्ण;

#घोषणा mi_inst_regs(id) अणु \
	MI_DCE8_REG_LIST(id), \
	.MC_HUB_RDREQ_DMIF_LIMIT = mmMC_HUB_RDREQ_DMIF_LIMIT \
पूर्ण
अटल स्थिर काष्ठा dce_mem_input_रेजिस्टरs mi_regs[] = अणु
		mi_inst_regs(0),
		mi_inst_regs(1),
		mi_inst_regs(2),
		mi_inst_regs(3),
		mi_inst_regs(4),
		mi_inst_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dce_mem_input_shअगरt mi_shअगरts = अणु
		MI_DCE8_MASK_SH_LIST(__SHIFT),
		.ENABLE = MC_HUB_RDREQ_DMIF_LIMIT__ENABLE__SHIFT
पूर्ण;

अटल स्थिर काष्ठा dce_mem_input_mask mi_masks = अणु
		MI_DCE8_MASK_SH_LIST(_MASK),
		.ENABLE = MC_HUB_RDREQ_DMIF_LIMIT__ENABLE_MASK
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt aux_shअगरt = अणु
	DCE10_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
	DCE10_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा mem_input *dce100_mem_input_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_mem_input *dce_mi = kzalloc(माप(काष्ठा dce_mem_input),
					       GFP_KERNEL);

	अगर (!dce_mi) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dce_mem_input_स्थिरruct(dce_mi, ctx, inst, &mi_regs[inst], &mi_shअगरts, &mi_masks);
	dce_mi->wa.single_head_rdreq_dmअगर_limit = 2;
	वापस &dce_mi->base;
पूर्ण

अटल व्योम dce100_transक्रमm_destroy(काष्ठा transक्रमm **xfm)
अणु
	kमुक्त(TO_DCE_TRANSFORM(*xfm));
	*xfm = शून्य;
पूर्ण

अटल काष्ठा transक्रमm *dce100_transक्रमm_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_transक्रमm *transक्रमm =
		kzalloc(माप(काष्ठा dce_transक्रमm), GFP_KERNEL);

	अगर (!transक्रमm)
		वापस शून्य;

	dce_transक्रमm_स्थिरruct(transक्रमm, ctx, inst,
				&xfm_regs[inst], &xfm_shअगरt, &xfm_mask);
	वापस &transक्रमm->base;
पूर्ण

अटल काष्ठा input_pixel_processor *dce100_ipp_create(
	काष्ठा dc_context *ctx, uपूर्णांक32_t inst)
अणु
	काष्ठा dce_ipp *ipp = kzalloc(माप(काष्ठा dce_ipp), GFP_KERNEL);

	अगर (!ipp) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dce_ipp_स्थिरruct(ipp, ctx, inst,
			&ipp_regs[inst], &ipp_shअगरt, &ipp_mask);
	वापस &ipp->base;
पूर्ण

अटल स्थिर काष्ठा encoder_feature_support link_enc_feature = अणु
		.max_hdmi_deep_color = COLOR_DEPTH_121212,
		.max_hdmi_pixel_घड़ी = 300000,
		.flags.bits.IS_HBR2_CAPABLE = true,
		.flags.bits.IS_TPS3_CAPABLE = true
पूर्ण;

अटल काष्ठा link_encoder *dce100_link_encoder_create(
	स्थिर काष्ठा encoder_init_data *enc_init_data)
अणु
	काष्ठा dce110_link_encoder *enc110 =
		kzalloc(माप(काष्ठा dce110_link_encoder), GFP_KERNEL);
	पूर्णांक link_regs_id;

	अगर (!enc110)
		वापस शून्य;

	link_regs_id =
		map_transmitter_id_to_phy_instance(enc_init_data->transmitter);

	dce110_link_encoder_स्थिरruct(enc110,
				      enc_init_data,
				      &link_enc_feature,
				      &link_enc_regs[link_regs_id],
				      &link_enc_aux_regs[enc_init_data->channel - 1],
				      &link_enc_hpd_regs[enc_init_data->hpd_source]);
	वापस &enc110->base;
पूर्ण

अटल काष्ठा panel_cntl *dce100_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
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

अटल काष्ठा output_pixel_processor *dce100_opp_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce110_opp *opp =
		kzalloc(माप(काष्ठा dce110_opp), GFP_KERNEL);

	अगर (!opp)
		वापस शून्य;

	dce110_opp_स्थिरruct(opp,
			     ctx, inst, &opp_regs[inst], &opp_shअगरt, &opp_mask);
	वापस &opp->base;
पूर्ण

अटल काष्ठा dce_aux *dce100_aux_engine_create(
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
		I2C_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_i2c_mask i2c_masks = अणु
		I2C_COMMON_MASK_SH_LIST_DCE_COMMON_BASE(_MASK)
पूर्ण;

अटल काष्ठा dce_i2c_hw *dce100_i2c_hw_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_i2c_hw *dce_i2c_hw =
		kzalloc(माप(काष्ठा dce_i2c_hw), GFP_KERNEL);

	अगर (!dce_i2c_hw)
		वापस शून्य;

	dce100_i2c_hw_स्थिरruct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_regs[inst], &i2c_shअगरts, &i2c_masks);

	वापस dce_i2c_hw;
पूर्ण
अटल काष्ठा घड़ी_source *dce100_घड़ी_source_create(
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

	अगर (dce110_clk_src_स्थिरruct(clk_src, ctx, bios, id,
			regs, &cs_shअगरt, &cs_mask)) अणु
		clk_src->base.dp_clk_src = dp_clk_src;
		वापस &clk_src->base;
	पूर्ण

	kमुक्त(clk_src);
	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

अटल व्योम dce100_घड़ी_source_destroy(काष्ठा घड़ी_source **clk_src)
अणु
	kमुक्त(TO_DCE110_CLK_SRC(*clk_src));
	*clk_src = शून्य;
पूर्ण

अटल व्योम dce100_resource_deकाष्ठा(काष्ठा dce110_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		अगर (pool->base.opps[i] != शून्य)
			dce110_opp_destroy(&pool->base.opps[i]);

		अगर (pool->base.transक्रमms[i] != शून्य)
			dce100_transक्रमm_destroy(&pool->base.transक्रमms[i]);

		अगर (pool->base.ipps[i] != शून्य)
			dce_ipp_destroy(&pool->base.ipps[i]);

		अगर (pool->base.mis[i] != शून्य) अणु
			kमुक्त(TO_DCE_MEM_INPUT(pool->base.mis[i]));
			pool->base.mis[i] = शून्य;
		पूर्ण

		अगर (pool->base.timing_generators[i] != शून्य)	अणु
			kमुक्त(DCE110TG_FROM_TG(pool->base.timing_generators[i]));
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

	क्रम (i = 0; i < pool->base.stream_enc_count; i++) अणु
		अगर (pool->base.stream_enc[i] != शून्य)
			kमुक्त(DCE110STRENC_FROM_STRENC(pool->base.stream_enc[i]));
	पूर्ण

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] != शून्य)
			dce100_घड़ी_source_destroy(&pool->base.घड़ी_sources[i]);
	पूर्ण

	अगर (pool->base.dp_घड़ी_source != शून्य)
		dce100_घड़ी_source_destroy(&pool->base.dp_घड़ी_source);

	क्रम (i = 0; i < pool->base.audio_count; i++)	अणु
		अगर (pool->base.audios[i] != शून्य)
			dce_aud_destroy(&pool->base.audios[i]);
	पूर्ण

	अगर (pool->base.abm != शून्य)
				dce_abm_destroy(&pool->base.abm);

	अगर (pool->base.dmcu != शून्य)
			dce_dmcu_destroy(&pool->base.dmcu);

	अगर (pool->base.irqs != शून्य)
		dal_irq_service_destroy(&pool->base.irqs);
पूर्ण

अटल क्रमागत dc_status build_mapped_resource(
		स्थिर काष्ठा dc  *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा pipe_ctx *pipe_ctx = resource_get_head_pipe_क्रम_stream(&context->res_ctx, stream);

	अगर (!pipe_ctx)
		वापस DC_ERROR_UNEXPECTED;

	dce110_resource_build_pipe_hw_param(pipe_ctx);

	resource_build_info_frame(pipe_ctx);

	वापस DC_OK;
पूर्ण

अटल bool dce100_validate_bandwidth(
	काष्ठा dc  *dc,
	काष्ठा dc_state *context,
	bool fast_validate)
अणु
	पूर्णांक i;
	bool at_least_one_pipe = false;

	क्रम (i = 0; i < dc->res_pool->pipe_count; i++) अणु
		अगर (context->res_ctx.pipe_ctx[i].stream)
			at_least_one_pipe = true;
	पूर्ण

	अगर (at_least_one_pipe) अणु
		/* TODO implement when needed but क्रम now hardcode max value*/
		context->bw_ctx.bw.dce.dispclk_khz = 681000;
		context->bw_ctx.bw.dce.yclk_khz = 250000 * MEMORY_TYPE_MULTIPLIER_CZ;
	पूर्ण अन्यथा अणु
		context->bw_ctx.bw.dce.dispclk_khz = 0;
		context->bw_ctx.bw.dce.yclk_khz = 0;
	पूर्ण

	वापस true;
पूर्ण

अटल bool dce100_validate_surface_sets(
		काष्ठा dc_state *context)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < context->stream_count; i++) अणु
		अगर (context->stream_status[i].plane_count == 0)
			जारी;

		अगर (context->stream_status[i].plane_count > 1)
			वापस false;

		अगर (context->stream_status[i].plane_states[0]->क्रमmat
				>= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल क्रमागत dc_status dce100_validate_global(
		काष्ठा dc  *dc,
		काष्ठा dc_state *context)
अणु
	अगर (!dce100_validate_surface_sets(context))
		वापस DC_FAIL_SURFACE_VALIDATE;

	वापस DC_OK;
पूर्ण

क्रमागत dc_status dce100_add_stream_to_ctx(
		काष्ठा dc *dc,
		काष्ठा dc_state *new_ctx,
		काष्ठा dc_stream_state *dc_stream)
अणु
	क्रमागत dc_status result = DC_ERROR_UNEXPECTED;

	result = resource_map_pool_resources(dc, new_ctx, dc_stream);

	अगर (result == DC_OK)
		result = resource_map_घड़ी_resources(dc, new_ctx, dc_stream);

	अगर (result == DC_OK)
		result = build_mapped_resource(dc, new_ctx, dc_stream);

	वापस result;
पूर्ण

अटल व्योम dce100_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dce110_resource_pool *dce110_pool = TO_DCE110_RES_POOL(*pool);

	dce100_resource_deकाष्ठा(dce110_pool);
	kमुक्त(dce110_pool);
	*pool = शून्य;
पूर्ण

क्रमागत dc_status dce100_validate_plane(स्थिर काष्ठा dc_plane_state *plane_state, काष्ठा dc_caps *caps)
अणु

	अगर (plane_state->क्रमmat < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		वापस DC_OK;

	वापस DC_FAIL_SURFACE_VALIDATE;
पूर्ण

काष्ठा stream_encoder *dce100_find_first_मुक्त_match_stream_enc_क्रम_link(
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
	 * below can happen in हालs when stream encoder is acquired:
	 * 1) क्रम second MST display in chain, so preferred engine alपढ़ोy
	 * acquired;
	 * 2) क्रम another link, which preferred engine alपढ़ोy acquired by any
	 * MST configuration.
	 *
	 * If संकेत is of DP type and preferred engine not found, वापस last available
	 *
	 * TODO - This is just a patch up and a generic solution is
	 * required क्रम non DP connectors.
	 */

	अगर (j >= 0 && link->connector_संकेत == SIGNAL_TYPE_DISPLAY_PORT)
		वापस pool->stream_enc[j];

	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा resource_funcs dce100_res_pool_funcs = अणु
	.destroy = dce100_destroy_resource_pool,
	.link_enc_create = dce100_link_encoder_create,
	.panel_cntl_create = dce100_panel_cntl_create,
	.validate_bandwidth = dce100_validate_bandwidth,
	.validate_plane = dce100_validate_plane,
	.add_stream_to_ctx = dce100_add_stream_to_ctx,
	.validate_global = dce100_validate_global,
	.find_first_मुक्त_match_stream_enc_क्रम_link = dce100_find_first_मुक्त_match_stream_enc_क्रम_link
पूर्ण;

अटल bool dce100_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc  *dc,
	काष्ठा dce110_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा dc_bios *bp;

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap;
	pool->base.funcs = &dce100_res_pool_funcs;
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;

	bp = ctx->dc_bios;

	अगर (bp->fw_info_valid && bp->fw_info.बाह्यal_घड़ी_source_frequency_क्रम_dp != 0) अणु
		pool->base.dp_घड़ी_source =
				dce100_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_EXTERNAL, शून्य, true);

		pool->base.घड़ी_sources[0] =
				dce100_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL0, &clk_src_regs[0], false);
		pool->base.घड़ी_sources[1] =
				dce100_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL1, &clk_src_regs[1], false);
		pool->base.घड़ी_sources[2] =
				dce100_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL2, &clk_src_regs[2], false);
		pool->base.clk_src_count = 3;

	पूर्ण अन्यथा अणु
		pool->base.dp_घड़ी_source =
				dce100_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL0, &clk_src_regs[0], true);

		pool->base.घड़ी_sources[0] =
				dce100_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL1, &clk_src_regs[1], false);
		pool->base.घड़ी_sources[1] =
				dce100_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL2, &clk_src_regs[2], false);
		pool->base.clk_src_count = 2;
	पूर्ण

	अगर (pool->base.dp_घड़ी_source == शून्य) अणु
		dm_error("DC: failed to create dp clock source!\n");
		BREAK_TO_DEBUGGER();
		जाओ res_create_fail;
	पूर्ण

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] == शून्य) अणु
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			जाओ res_create_fail;
		पूर्ण
	पूर्ण

	pool->base.dmcu = dce_dmcu_create(ctx,
			&dmcu_regs,
			&dmcu_shअगरt,
			&dmcu_mask);
	अगर (pool->base.dmcu == शून्य) अणु
		dm_error("DC: failed to create dmcu!\n");
		BREAK_TO_DEBUGGER();
		जाओ res_create_fail;
	पूर्ण

	pool->base.abm = dce_abm_create(ctx,
				&abm_regs,
				&abm_shअगरt,
				&abm_mask);
	अगर (pool->base.abm == शून्य) अणु
		dm_error("DC: failed to create abm!\n");
		BREAK_TO_DEBUGGER();
		जाओ res_create_fail;
	पूर्ण

	अणु
		काष्ठा irq_service_init_data init_data;
		init_data.ctx = dc->ctx;
		pool->base.irqs = dal_irq_service_dce110_create(&init_data);
		अगर (!pool->base.irqs)
			जाओ res_create_fail;
	पूर्ण

	/*************************************************
	*  Resource + asic cap harcoding                *
	*************************************************/
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;
	pool->base.pipe_count = res_cap.num_timing_generator;
	pool->base.timing_generator_count = pool->base.res_cap->num_timing_generator;
	dc->caps.max_करोwnscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 40;
	dc->caps.i2c_speed_in_khz = 40;
	dc->caps.max_cursor_size = 128;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.dual_link_dvi = true;
	dc->caps.disable_dp_clk_share = true;
	dc->caps.extended_aux_समयout_support = false;

	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		pool->base.timing_generators[i] =
			dce100_timing_generator_create(
				ctx,
				i,
				&dce100_tg_offsets[i]);
		अगर (pool->base.timing_generators[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.mis[i] = dce100_mem_input_create(ctx, i);
		अगर (pool->base.mis[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.ipps[i] = dce100_ipp_create(ctx, i);
		अगर (pool->base.ipps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.transक्रमms[i] = dce100_transक्रमm_create(ctx, i);
		अगर (pool->base.transक्रमms[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create transform!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.opps[i] = dce100_opp_create(ctx, i);
		अगर (pool->base.opps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			जाओ res_create_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dce100_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ res_create_fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dce100_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create i2c engine!!\n");
			जाओ res_create_fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	dc->caps.max_planes =  pool->base.pipe_count;

	क्रम (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	अगर (!resource_स्थिरruct(num_भव_links, dc, &pool->base,
			&res_create_funcs))
		जाओ res_create_fail;

	/* Create hardware sequencer */
	dce100_hw_sequencer_स्थिरruct(dc);
	वापस true;

res_create_fail:
	dce100_resource_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dce100_create_resource_pool(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc  *dc)
अणु
	काष्ठा dce110_resource_pool *pool =
		kzalloc(माप(काष्ठा dce110_resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dce100_resource_स्थिरruct(num_भव_links, dc, pool))
		वापस &pool->base;

	kमुक्त(pool);
	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण

