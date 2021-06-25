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
#समावेश "dce110/dce110_resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce110/dce110_timing_generator.h"
#समावेश "irq/dce110/irq_service_dce110.h"
#समावेश "dce110/dce110_timing_generator_v.h"
#समावेश "dce/dce_link_encoder.h"
#समावेश "dce/dce_stream_encoder.h"
#समावेश "dce/dce_mem_input.h"
#समावेश "dce110/dce110_mem_input_v.h"
#समावेश "dce/dce_ipp.h"
#समावेश "dce/dce_transform.h"
#समावेश "dce110/dce110_transform_v.h"
#समावेश "dce/dce_opp.h"
#समावेश "dce110/dce110_opp_v.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_abm.h"
#समावेश "dce/dce_dmcu.h"
#समावेश "dce/dce_i2c.h"
#समावेश "dce/dce_panel_cntl.h"

#घोषणा DC_LOGGER \
		dc->ctx->logger

#समावेश "dce110/dce110_compressor.h"

#समावेश "reg_helper.h"

#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"

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

#अगर_अघोषित DPHY_RX_FAST_TRAINING_CAPABLE
	#घोषणा DPHY_RX_FAST_TRAINING_CAPABLE 0x1
#पूर्ण_अगर

अटल स्थिर काष्ठा dce110_timing_generator_offsets dce110_tg_offsets[] = अणु
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

#घोषणा ipp_regs(id)\
[id] = अणु\
		IPP_DCE110_REG_LIST_DCE_BASE(id)\
पूर्ण

अटल स्थिर काष्ठा dce_ipp_रेजिस्टरs ipp_regs[] = अणु
		ipp_regs(0),
		ipp_regs(1),
		ipp_regs(2)
पूर्ण;

अटल स्थिर काष्ठा dce_ipp_shअगरt ipp_shअगरt = अणु
		IPP_DCE100_MASK_SH_LIST_DCE_COMMON_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_ipp_mask ipp_mask = अणु
		IPP_DCE100_MASK_SH_LIST_DCE_COMMON_BASE(_MASK)
पूर्ण;

#घोषणा transक्रमm_regs(id)\
[id] = अणु\
		XFM_COMMON_REG_LIST_DCE110(id)\
पूर्ण

अटल स्थिर काष्ठा dce_transक्रमm_रेजिस्टरs xfm_regs[] = अणु
		transक्रमm_regs(0),
		transक्रमm_regs(1),
		transक्रमm_regs(2)
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
	LE_DCE110_REG_LIST(id)\
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
	SE_COMMON_REG_LIST(id),\
	.TMDS_CNTL = 0,\
पूर्ण

अटल स्थिर काष्ठा dce110_stream_enc_रेजिस्टरs stream_enc_regs[] = अणु
	stream_enc_regs(0),
	stream_enc_regs(1),
	stream_enc_regs(2)
पूर्ण;

अटल स्थिर काष्ठा dce_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCE110(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCE110(_MASK)
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

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_shअगरt aux_shअगरt = अणु
	DCE_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
	DCE_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा opp_regs(id)\
[id] = अणु\
	OPP_DCE_110_REG_LIST(id),\
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
	OPP_COMMON_MASK_SH_LIST_DCE_110(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_opp_mask opp_mask = अणु
	OPP_COMMON_MASK_SH_LIST_DCE_110(_MASK)
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

/* AG TBD Needs to be reduced back to 3 pipes once dce10 hw sequencer implemented. */


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

अटल स्थिर काष्ठा bios_रेजिस्टरs bios_regs = अणु
	.BIOS_SCRATCH_3 = mmBIOS_SCRATCH_3,
	.BIOS_SCRATCH_6 = mmBIOS_SCRATCH_6
पूर्ण;

अटल स्थिर काष्ठा resource_caps carrizo_resource_cap = अणु
		.num_timing_generator = 3,
		.num_video_plane = 1,
		.num_audio = 3,
		.num_stream_encoder = 3,
		.num_pll = 2,
		.num_ddc = 3,
पूर्ण;

अटल स्थिर काष्ठा resource_caps stoney_resource_cap = अणु
		.num_timing_generator = 2,
		.num_video_plane = 1,
		.num_audio = 3,
		.num_stream_encoder = 3,
		.num_pll = 2,
		.num_ddc = 3,
पूर्ण;

अटल स्थिर काष्ठा dc_plane_cap plane_cap = अणु
		.type = DC_PLANE_TYPE_DCE_RGB,
		.blends_with_below = true,
		.blends_with_above = true,
		.per_pixel_alpha = 1,

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
		पूर्ण,
		64,
		64
पूर्ण;

अटल स्थिर काष्ठा dc_plane_cap underlay_plane_cap = अणु
		.type = DC_PLANE_TYPE_DCE_UNDERLAY,
		.blends_with_above = true,
		.per_pixel_alpha = 1,

		.pixel_क्रमmat_support = अणु
				.argb8888 = false,
				.nv12 = true,
				.fp16 = false
		पूर्ण,

		.max_upscale_factor = अणु
				.argb8888 = 1,
				.nv12 = 16000,
				.fp16 = 1
		पूर्ण,

		.max_करोwnscale_factor = अणु
				.argb8888 = 1,
				.nv12 = 250,
				.fp16 = 1
		पूर्ण,
		64,
		64
पूर्ण;

#घोषणा CTX  ctx
#घोषणा REG(reg) mm ## reg

#अगर_अघोषित mmCC_DC_HDMI_STRAPS
#घोषणा mmCC_DC_HDMI_STRAPS 0x4819
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

अटल काष्ठा timing_generator *dce110_timing_generator_create(
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

अटल काष्ठा stream_encoder *dce110_stream_encoder_create(
	क्रमागत engine_id eng_id,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dce110_stream_encoder *enc110 =
		kzalloc(माप(काष्ठा dce110_stream_encoder), GFP_KERNEL);

	अगर (!enc110)
		वापस शून्य;

	dce110_stream_encoder_स्थिरruct(enc110, ctx, ctx->dc_bios, eng_id,
					&stream_enc_regs[eng_id],
					&se_shअगरt, &se_mask);
	वापस &enc110->base;
पूर्ण

#घोषणा SRII(reg_name, block, id)\
	.reg_name[id] = mm ## block ## id ## _ ## reg_name

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_stoney_reg = अणु
		HWSEQ_ST_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_cz_reg = अणु
		HWSEQ_CZ_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCE11_MASK_SH_LIST(__SHIFT),
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCE11_MASK_SH_LIST(_MASK),
पूर्ण;

अटल काष्ठा dce_hwseq *dce110_hwseq_create(
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dce_hwseq *hws = kzalloc(माप(काष्ठा dce_hwseq), GFP_KERNEL);

	अगर (hws) अणु
		hws->ctx = ctx;
		hws->regs = ASIC_REV_IS_STONEY(ctx->asic_id.hw_पूर्णांकernal_rev) ?
				&hwseq_stoney_reg : &hwseq_cz_reg;
		hws->shअगरts = &hwseq_shअगरt;
		hws->masks = &hwseq_mask;
		hws->wa.blnd_crtc_trigger = true;
	पूर्ण
	वापस hws;
पूर्ण

अटल स्थिर काष्ठा resource_create_funcs res_create_funcs = अणु
	.पढ़ो_dce_straps = पढ़ो_dce_straps,
	.create_audio = create_audio,
	.create_stream_encoder = dce110_stream_encoder_create,
	.create_hwseq = dce110_hwseq_create,
पूर्ण;

#घोषणा mi_inst_regs(id) अणु \
	MI_DCE11_REG_LIST(id), \
	.MC_HUB_RDREQ_DMIF_LIMIT = mmMC_HUB_RDREQ_DMIF_LIMIT \
पूर्ण
अटल स्थिर काष्ठा dce_mem_input_रेजिस्टरs mi_regs[] = अणु
		mi_inst_regs(0),
		mi_inst_regs(1),
		mi_inst_regs(2),
पूर्ण;

अटल स्थिर काष्ठा dce_mem_input_shअगरt mi_shअगरts = अणु
		MI_DCE11_MASK_SH_LIST(__SHIFT),
		.ENABLE = MC_HUB_RDREQ_DMIF_LIMIT__ENABLE__SHIFT
पूर्ण;

अटल स्थिर काष्ठा dce_mem_input_mask mi_masks = अणु
		MI_DCE11_MASK_SH_LIST(_MASK),
		.ENABLE = MC_HUB_RDREQ_DMIF_LIMIT__ENABLE_MASK
पूर्ण;


अटल काष्ठा mem_input *dce110_mem_input_create(
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
	dce_mi->wa.single_head_rdreq_dmअगर_limit = 3;
	वापस &dce_mi->base;
पूर्ण

अटल व्योम dce110_transक्रमm_destroy(काष्ठा transक्रमm **xfm)
अणु
	kमुक्त(TO_DCE_TRANSFORM(*xfm));
	*xfm = शून्य;
पूर्ण

अटल काष्ठा transक्रमm *dce110_transक्रमm_create(
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

अटल काष्ठा input_pixel_processor *dce110_ipp_create(
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

अटल काष्ठा link_encoder *dce110_link_encoder_create(
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

अटल काष्ठा panel_cntl *dce110_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
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

अटल काष्ठा output_pixel_processor *dce110_opp_create(
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

अटल काष्ठा dce_aux *dce110_aux_engine_create(
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

अटल काष्ठा dce_i2c_hw *dce110_i2c_hw_create(
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
अटल काष्ठा घड़ी_source *dce110_घड़ी_source_create(
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

अटल व्योम dce110_घड़ी_source_destroy(काष्ठा घड़ी_source **clk_src)
अणु
	काष्ठा dce110_clk_src *dce110_clk_src;

	अगर (!clk_src)
		वापस;

	dce110_clk_src = TO_DCE110_CLK_SRC(*clk_src);

	kमुक्त(dce110_clk_src->dp_ss_params);
	kमुक्त(dce110_clk_src->hdmi_ss_params);
	kमुक्त(dce110_clk_src->dvi_ss_params);

	kमुक्त(dce110_clk_src);
	*clk_src = शून्य;
पूर्ण

अटल व्योम dce110_resource_deकाष्ठा(काष्ठा dce110_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		अगर (pool->base.opps[i] != शून्य)
			dce110_opp_destroy(&pool->base.opps[i]);

		अगर (pool->base.transक्रमms[i] != शून्य)
			dce110_transक्रमm_destroy(&pool->base.transक्रमms[i]);

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
		अगर (pool->base.घड़ी_sources[i] != शून्य) अणु
			dce110_घड़ी_source_destroy(&pool->base.घड़ी_sources[i]);
		पूर्ण
	पूर्ण

	अगर (pool->base.dp_घड़ी_source != शून्य)
		dce110_घड़ी_source_destroy(&pool->base.dp_घड़ी_source);

	क्रम (i = 0; i < pool->base.audio_count; i++)	अणु
		अगर (pool->base.audios[i] != शून्य) अणु
			dce_aud_destroy(&pool->base.audios[i]);
		पूर्ण
	पूर्ण

	अगर (pool->base.abm != शून्य)
		dce_abm_destroy(&pool->base.abm);

	अगर (pool->base.dmcu != शून्य)
		dce_dmcu_destroy(&pool->base.dmcu);

	अगर (pool->base.irqs != शून्य) अणु
		dal_irq_service_destroy(&pool->base.irqs);
	पूर्ण
पूर्ण


अटल व्योम get_pixel_घड़ी_parameters(
	स्थिर काष्ठा pipe_ctx *pipe_ctx,
	काष्ठा pixel_clk_params *pixel_clk_params)
अणु
	स्थिर काष्ठा dc_stream_state *stream = pipe_ctx->stream;

	/*TODO: is this halved क्रम YCbCr 420? in that हाल we might want to move
	 * the pixel घड़ी normalization क्रम hdmi up to here instead of करोing it
	 * in pll_adjust_pix_clk
	 */
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
	pixel_clk_params->flags.SUPPORT_YCBCR420 = (stream->timing.pixel_encoding ==
			PIXEL_ENCODING_YCBCR420);
	pixel_clk_params->pixel_encoding = stream->timing.pixel_encoding;
	अगर (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR422) अणु
		pixel_clk_params->color_depth = COLOR_DEPTH_888;
	पूर्ण
	अगर (stream->timing.pixel_encoding == PIXEL_ENCODING_YCBCR420) अणु
		pixel_clk_params->requested_pix_clk_100hz  = pixel_clk_params->requested_pix_clk_100hz / 2;
	पूर्ण
	अगर (stream->timing.timing_3d_क्रमmat == TIMING_3D_FORMAT_HW_FRAME_PACKING)
		pixel_clk_params->requested_pix_clk_100hz *= 2;

पूर्ण

व्योम dce110_resource_build_pipe_hw_param(काष्ठा pipe_ctx *pipe_ctx)
अणु
	get_pixel_घड़ी_parameters(pipe_ctx, &pipe_ctx->stream_res.pix_clk_params);
	pipe_ctx->घड़ी_source->funcs->get_pix_clk_भागiders(
		pipe_ctx->घड़ी_source,
		&pipe_ctx->stream_res.pix_clk_params,
		&pipe_ctx->pll_settings);
	resource_build_bit_depth_reduction_params(pipe_ctx->stream,
			&pipe_ctx->stream->bit_depth_params);
	pipe_ctx->stream->clamping.pixel_encoding = pipe_ctx->stream->timing.pixel_encoding;
पूर्ण

अटल bool is_surface_pixel_क्रमmat_supported(काष्ठा pipe_ctx *pipe_ctx, अचिन्हित पूर्णांक underlay_idx)
अणु
	अगर (pipe_ctx->pipe_idx != underlay_idx)
		वापस true;
	अगर (!pipe_ctx->plane_state)
		वापस false;
	अगर (pipe_ctx->plane_state->क्रमmat < SURFACE_PIXEL_FORMAT_VIDEO_BEGIN)
		वापस false;
	वापस true;
पूर्ण

अटल क्रमागत dc_status build_mapped_resource(
		स्थिर काष्ठा dc *dc,
		काष्ठा dc_state *context,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा pipe_ctx *pipe_ctx = resource_get_head_pipe_क्रम_stream(&context->res_ctx, stream);

	अगर (!pipe_ctx)
		वापस DC_ERROR_UNEXPECTED;

	अगर (!is_surface_pixel_क्रमmat_supported(pipe_ctx,
			dc->res_pool->underlay_pipe_index))
		वापस DC_SURFACE_PIXEL_FORMAT_UNSUPPORTED;

	dce110_resource_build_pipe_hw_param(pipe_ctx);

	/* TODO: validate audio ASIC caps, encoder */

	resource_build_info_frame(pipe_ctx);

	वापस DC_OK;
पूर्ण

अटल bool dce110_validate_bandwidth(
	काष्ठा dc *dc,
	काष्ठा dc_state *context,
	bool fast_validate)
अणु
	bool result = false;

	DC_LOG_BANDWIDTH_CALCS(
		"%s: start",
		__func__);

	अगर (bw_calcs(
			dc->ctx,
			dc->bw_dceip,
			dc->bw_vbios,
			context->res_ctx.pipe_ctx,
			dc->res_pool->pipe_count,
			&context->bw_ctx.bw.dce))
		result =  true;

	अगर (!result)
		DC_LOG_BANDWIDTH_VALIDATION("%s: %dx%d@%d Bandwidth validation failed!\n",
			__func__,
			context->streams[0]->timing.h_addressable,
			context->streams[0]->timing.v_addressable,
			context->streams[0]->timing.pix_clk_100hz / 10);

	अगर (स_भेद(&dc->current_state->bw_ctx.bw.dce,
			&context->bw_ctx.bw.dce, माप(context->bw_ctx.bw.dce))) अणु

		DC_LOG_BANDWIDTH_CALCS(
			"%s: finish,\n"
			"nbpMark_b: %d nbpMark_a: %d urgentMark_b: %d urgentMark_a: %d\n"
			"stutMark_b: %d stutMark_a: %d\n"
			"nbpMark_b: %d nbpMark_a: %d urgentMark_b: %d urgentMark_a: %d\n"
			"stutMark_b: %d stutMark_a: %d\n"
			"nbpMark_b: %d nbpMark_a: %d urgentMark_b: %d urgentMark_a: %d\n"
			"stutMark_b: %d stutMark_a: %d stutter_mode_enable: %d\n"
			"cstate: %d pstate: %d nbpstate: %d sync: %d dispclk: %d\n"
			"sclk: %d sclk_sleep: %d yclk: %d blackout_recovery_time_us: %d\n"
			,
			__func__,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[0].b_mark,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[0].a_mark,
			context->bw_ctx.bw.dce.urgent_wm_ns[0].b_mark,
			context->bw_ctx.bw.dce.urgent_wm_ns[0].a_mark,
			context->bw_ctx.bw.dce.stutter_निकास_wm_ns[0].b_mark,
			context->bw_ctx.bw.dce.stutter_निकास_wm_ns[0].a_mark,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[1].b_mark,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[1].a_mark,
			context->bw_ctx.bw.dce.urgent_wm_ns[1].b_mark,
			context->bw_ctx.bw.dce.urgent_wm_ns[1].a_mark,
			context->bw_ctx.bw.dce.stutter_निकास_wm_ns[1].b_mark,
			context->bw_ctx.bw.dce.stutter_निकास_wm_ns[1].a_mark,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[2].b_mark,
			context->bw_ctx.bw.dce.nbp_state_change_wm_ns[2].a_mark,
			context->bw_ctx.bw.dce.urgent_wm_ns[2].b_mark,
			context->bw_ctx.bw.dce.urgent_wm_ns[2].a_mark,
			context->bw_ctx.bw.dce.stutter_निकास_wm_ns[2].b_mark,
			context->bw_ctx.bw.dce.stutter_निकास_wm_ns[2].a_mark,
			context->bw_ctx.bw.dce.stutter_mode_enable,
			context->bw_ctx.bw.dce.cpuc_state_change_enable,
			context->bw_ctx.bw.dce.cpup_state_change_enable,
			context->bw_ctx.bw.dce.nbp_state_change_enable,
			context->bw_ctx.bw.dce.all_displays_in_sync,
			context->bw_ctx.bw.dce.dispclk_khz,
			context->bw_ctx.bw.dce.sclk_khz,
			context->bw_ctx.bw.dce.sclk_deep_sleep_khz,
			context->bw_ctx.bw.dce.yclk_khz,
			context->bw_ctx.bw.dce.blackout_recovery_समय_us);
	पूर्ण
	वापस result;
पूर्ण

अटल क्रमागत dc_status dce110_validate_plane(स्थिर काष्ठा dc_plane_state *plane_state,
					    काष्ठा dc_caps *caps)
अणु
	अगर (((plane_state->dst_rect.width * 2) < plane_state->src_rect.width) ||
	    ((plane_state->dst_rect.height * 2) < plane_state->src_rect.height))
		वापस DC_FAIL_SURFACE_VALIDATE;

	वापस DC_OK;
पूर्ण

अटल bool dce110_validate_surface_sets(
		काष्ठा dc_state *context)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < context->stream_count; i++) अणु
		अगर (context->stream_status[i].plane_count == 0)
			जारी;

		अगर (context->stream_status[i].plane_count > 2)
			वापस false;

		क्रम (j = 0; j < context->stream_status[i].plane_count; j++) अणु
			काष्ठा dc_plane_state *plane =
				context->stream_status[i].plane_states[j];

			/* underlay validation */
			अगर (plane->क्रमmat >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN) अणु

				अगर ((plane->src_rect.width > 1920 ||
					plane->src_rect.height > 1080))
					वापस false;

				/* we करोn't have the logic to support underlay
				 * only yet so block the use हाल where we get
				 * NV12 plane as top layer
				 */
				अगर (j == 0)
					वापस false;

				/* irrespective of plane क्रमmat,
				 * stream should be RGB encoded
				 */
				अगर (context->streams[i]->timing.pixel_encoding
						!= PIXEL_ENCODING_RGB)
					वापस false;

			पूर्ण

		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल क्रमागत dc_status dce110_validate_global(
		काष्ठा dc *dc,
		काष्ठा dc_state *context)
अणु
	अगर (!dce110_validate_surface_sets(context))
		वापस DC_FAIL_SURFACE_VALIDATE;

	वापस DC_OK;
पूर्ण

अटल क्रमागत dc_status dce110_add_stream_to_ctx(
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

अटल काष्ठा pipe_ctx *dce110_acquire_underlay(
		काष्ठा dc_state *context,
		स्थिर काष्ठा resource_pool *pool,
		काष्ठा dc_stream_state *stream)
अणु
	काष्ठा dc *dc = stream->ctx->dc;
	काष्ठा dce_hwseq *hws = dc->hwseq;
	काष्ठा resource_context *res_ctx = &context->res_ctx;
	अचिन्हित पूर्णांक underlay_idx = pool->underlay_pipe_index;
	काष्ठा pipe_ctx *pipe_ctx = &res_ctx->pipe_ctx[underlay_idx];

	अगर (res_ctx->pipe_ctx[underlay_idx].stream)
		वापस शून्य;

	pipe_ctx->stream_res.tg = pool->timing_generators[underlay_idx];
	pipe_ctx->plane_res.mi = pool->mis[underlay_idx];
	/*pipe_ctx->plane_res.ipp = res_ctx->pool->ipps[underlay_idx];*/
	pipe_ctx->plane_res.xfm = pool->transक्रमms[underlay_idx];
	pipe_ctx->stream_res.opp = pool->opps[underlay_idx];
	pipe_ctx->pipe_idx = underlay_idx;

	pipe_ctx->stream = stream;

	अगर (!dc->current_state->res_ctx.pipe_ctx[underlay_idx].stream) अणु
		काष्ठा tg_color black_color = अणु0पूर्ण;
		काष्ठा dc_bios *dcb = dc->ctx->dc_bios;

		hws->funcs.enable_display_घातer_gating(
				dc,
				pipe_ctx->stream_res.tg->inst,
				dcb, PIPE_GATING_CONTROL_DISABLE);

		/*
		 * This is क्रम घातering on underlay, so crtc करोes not
		 * need to be enabled
		 */

		pipe_ctx->stream_res.tg->funcs->program_timing(pipe_ctx->stream_res.tg,
				&stream->timing,
				0,
				0,
				0,
				0,
				pipe_ctx->stream->संकेत,
				false);

		pipe_ctx->stream_res.tg->funcs->enable_advanced_request(
				pipe_ctx->stream_res.tg,
				true,
				&stream->timing);

		pipe_ctx->plane_res.mi->funcs->allocate_mem_input(pipe_ctx->plane_res.mi,
				stream->timing.h_total,
				stream->timing.v_total,
				stream->timing.pix_clk_100hz / 10,
				context->stream_count);

		color_space_to_black_color(dc,
				COLOR_SPACE_YCBCR601, &black_color);
		pipe_ctx->stream_res.tg->funcs->set_blank_color(
				pipe_ctx->stream_res.tg,
				&black_color);
	पूर्ण

	वापस pipe_ctx;
पूर्ण

अटल व्योम dce110_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dce110_resource_pool *dce110_pool = TO_DCE110_RES_POOL(*pool);

	dce110_resource_deकाष्ठा(dce110_pool);
	kमुक्त(dce110_pool);
	*pool = शून्य;
पूर्ण

काष्ठा stream_encoder *dce110_find_first_मुक्त_match_stream_enc_क्रम_link(
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


अटल स्थिर काष्ठा resource_funcs dce110_res_pool_funcs = अणु
	.destroy = dce110_destroy_resource_pool,
	.link_enc_create = dce110_link_encoder_create,
	.panel_cntl_create = dce110_panel_cntl_create,
	.validate_bandwidth = dce110_validate_bandwidth,
	.validate_plane = dce110_validate_plane,
	.acquire_idle_pipe_क्रम_layer = dce110_acquire_underlay,
	.add_stream_to_ctx = dce110_add_stream_to_ctx,
	.validate_global = dce110_validate_global,
	.find_first_मुक्त_match_stream_enc_क्रम_link = dce110_find_first_मुक्त_match_stream_enc_क्रम_link
पूर्ण;

अटल bool underlay_create(काष्ठा dc_context *ctx, काष्ठा resource_pool *pool)
अणु
	काष्ठा dce110_timing_generator *dce110_tgv = kzalloc(माप(*dce110_tgv),
							     GFP_KERNEL);
	काष्ठा dce_transक्रमm *dce110_xfmv = kzalloc(माप(*dce110_xfmv),
						    GFP_KERNEL);
	काष्ठा dce_mem_input *dce110_miv = kzalloc(माप(*dce110_miv),
						   GFP_KERNEL);
	काष्ठा dce110_opp *dce110_oppv = kzalloc(माप(*dce110_oppv),
						 GFP_KERNEL);

	अगर (!dce110_tgv || !dce110_xfmv || !dce110_miv || !dce110_oppv) अणु
		kमुक्त(dce110_tgv);
		kमुक्त(dce110_xfmv);
		kमुक्त(dce110_miv);
		kमुक्त(dce110_oppv);
		वापस false;
	पूर्ण

	dce110_opp_v_स्थिरruct(dce110_oppv, ctx);

	dce110_timing_generator_v_स्थिरruct(dce110_tgv, ctx);
	dce110_mem_input_v_स्थिरruct(dce110_miv, ctx);
	dce110_transक्रमm_v_स्थिरruct(dce110_xfmv, ctx);

	pool->opps[pool->pipe_count] = &dce110_oppv->base;
	pool->timing_generators[pool->pipe_count] = &dce110_tgv->base;
	pool->mis[pool->pipe_count] = &dce110_miv->base;
	pool->transक्रमms[pool->pipe_count] = &dce110_xfmv->base;
	pool->pipe_count++;

	/* update the खुला caps to indicate an underlay is available */
	ctx->dc->caps.max_slave_planes = 1;
	ctx->dc->caps.max_slave_yuv_planes = 1;
	ctx->dc->caps.max_slave_rgb_planes = 0;

	वापस true;
पूर्ण

अटल व्योम bw_calcs_data_update_from_pplib(काष्ठा dc *dc)
अणु
	काष्ठा dm_pp_घड़ी_levels clks = अणु0पूर्ण;

	/*करो प्रणाली घड़ी*/
	dm_pp_get_घड़ी_levels_by_type(
			dc->ctx,
			DM_PP_CLOCK_TYPE_ENGINE_CLK,
			&clks);
	/* convert all the घड़ी fro kHz to fix poपूर्णांक mHz */
	dc->bw_vbios->high_sclk = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels-1], 1000);
	dc->bw_vbios->mid1_sclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels/8], 1000);
	dc->bw_vbios->mid2_sclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels*2/8], 1000);
	dc->bw_vbios->mid3_sclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels*3/8], 1000);
	dc->bw_vbios->mid4_sclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels*4/8], 1000);
	dc->bw_vbios->mid5_sclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels*5/8], 1000);
	dc->bw_vbios->mid6_sclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels*6/8], 1000);
	dc->bw_vbios->low_sclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[0], 1000);
	dc->sclk_lvls = clks;

	/*करो display घड़ी*/
	dm_pp_get_घड़ी_levels_by_type(
			dc->ctx,
			DM_PP_CLOCK_TYPE_DISPLAY_CLK,
			&clks);
	dc->bw_vbios->high_voltage_max_dispclk = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels-1], 1000);
	dc->bw_vbios->mid_voltage_max_dispclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[clks.num_levels>>1], 1000);
	dc->bw_vbios->low_voltage_max_dispclk  = bw_frc_to_fixed(
			clks.घड़ीs_in_khz[0], 1000);

	/*करो memory घड़ी*/
	dm_pp_get_घड़ी_levels_by_type(
			dc->ctx,
			DM_PP_CLOCK_TYPE_MEMORY_CLK,
			&clks);

	dc->bw_vbios->low_yclk = bw_frc_to_fixed(
		clks.घड़ीs_in_khz[0] * MEMORY_TYPE_MULTIPLIER_CZ, 1000);
	dc->bw_vbios->mid_yclk = bw_frc_to_fixed(
		clks.घड़ीs_in_khz[clks.num_levels>>1] * MEMORY_TYPE_MULTIPLIER_CZ,
		1000);
	dc->bw_vbios->high_yclk = bw_frc_to_fixed(
		clks.घड़ीs_in_khz[clks.num_levels-1] * MEMORY_TYPE_MULTIPLIER_CZ,
		1000);
पूर्ण

अटल स्थिर काष्ठा resource_caps *dce110_resource_cap(
	काष्ठा hw_asic_id *asic_id)
अणु
	अगर (ASIC_REV_IS_STONEY(asic_id->hw_पूर्णांकernal_rev))
		वापस &stoney_resource_cap;
	अन्यथा
		वापस &carrizo_resource_cap;
पूर्ण

अटल bool dce110_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा dce110_resource_pool *pool,
	काष्ठा hw_asic_id asic_id)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा dc_bios *bp;

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = dce110_resource_cap(&ctx->asic_id);
	pool->base.funcs = &dce110_res_pool_funcs;

	/*************************************************
	 *  Resource + asic cap harcoding                *
	 *************************************************/

	pool->base.pipe_count = pool->base.res_cap->num_timing_generator;
	pool->base.underlay_pipe_index = pool->base.pipe_count;
	pool->base.timing_generator_count = pool->base.res_cap->num_timing_generator;
	dc->caps.max_करोwnscale_ratio = 150;
	dc->caps.i2c_speed_in_khz = 40;
	dc->caps.i2c_speed_in_khz_hdcp = 40;
	dc->caps.max_cursor_size = 128;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.is_apu = true;
	dc->caps.extended_aux_समयout_support = false;

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	bp = ctx->dc_bios;

	अगर (bp->fw_info_valid && bp->fw_info.बाह्यal_घड़ी_source_frequency_क्रम_dp != 0) अणु
		pool->base.dp_घड़ी_source =
				dce110_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_EXTERNAL, शून्य, true);

		pool->base.घड़ी_sources[0] =
				dce110_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL0,
						&clk_src_regs[0], false);
		pool->base.घड़ी_sources[1] =
				dce110_घड़ी_source_create(ctx, bp, CLOCK_SOURCE_ID_PLL1,
						&clk_src_regs[1], false);

		pool->base.clk_src_count = 2;

		/* TODO: find out अगर CZ support 3 PLLs */
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

	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		pool->base.timing_generators[i] = dce110_timing_generator_create(
				ctx, i, &dce110_tg_offsets[i]);
		अगर (pool->base.timing_generators[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.mis[i] = dce110_mem_input_create(ctx, i);
		अगर (pool->base.mis[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.ipps[i] = dce110_ipp_create(ctx, i);
		अगर (pool->base.ipps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.transक्रमms[i] = dce110_transक्रमm_create(ctx, i);
		अगर (pool->base.transक्रमms[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create transform!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.opps[i] = dce110_opp_create(ctx, i);
		अगर (pool->base.opps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
			जाओ res_create_fail;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dce110_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ res_create_fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dce110_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create i2c engine!!\n");
			जाओ res_create_fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	अगर (dc->config.fbc_support)
		dc->fbc_compressor = dce110_compressor_create(ctx);

	अगर (!underlay_create(ctx, &pool->base))
		जाओ res_create_fail;

	अगर (!resource_स्थिरruct(num_भव_links, dc, &pool->base,
			&res_create_funcs))
		जाओ res_create_fail;

	/* Create hardware sequencer */
	dce110_hw_sequencer_स्थिरruct(dc);

	dc->caps.max_planes =  pool->base.pipe_count;

	क्रम (i = 0; i < pool->base.underlay_pipe_index; ++i)
		dc->caps.planes[i] = plane_cap;

	dc->caps.planes[pool->base.underlay_pipe_index] = underlay_plane_cap;

	bw_calcs_init(dc->bw_dceip, dc->bw_vbios, dc->ctx->asic_id);

	bw_calcs_data_update_from_pplib(dc);

	वापस true;

res_create_fail:
	dce110_resource_deकाष्ठा(pool);
	वापस false;
पूर्ण

काष्ठा resource_pool *dce110_create_resource_pool(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा hw_asic_id asic_id)
अणु
	काष्ठा dce110_resource_pool *pool =
		kzalloc(माप(काष्ठा dce110_resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dce110_resource_स्थिरruct(num_भव_links, dc, pool, asic_id))
		वापस &pool->base;

	kमुक्त(pool);
	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण
