<शैली गुरु>
/*
* Copyright 2012-15 Advanced Micro Devices, Inc.cls
*
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


#समावेश "stream_encoder.h"
#समावेश "resource.h"
#समावेश "include/irq_service_interface.h"
#समावेश "dce120_resource.h"

#समावेश "dce112/dce112_resource.h"

#समावेश "dce110/dce110_resource.h"
#समावेश "../virtual/virtual_stream_encoder.h"
#समावेश "dce120_timing_generator.h"
#समावेश "irq/dce120/irq_service_dce120.h"
#समावेश "dce/dce_opp.h"
#समावेश "dce/dce_clock_source.h"
#समावेश "dce/dce_ipp.h"
#समावेश "dce/dce_mem_input.h"
#समावेश "dce/dce_panel_cntl.h"

#समावेश "dce110/dce110_hw_sequencer.h"
#समावेश "dce120/dce120_hw_sequencer.h"
#समावेश "dce/dce_transform.h"
#समावेश "clk_mgr.h"
#समावेश "dce/dce_audio.h"
#समावेश "dce/dce_link_encoder.h"
#समावेश "dce/dce_stream_encoder.h"
#समावेश "dce/dce_hwseq.h"
#समावेश "dce/dce_abm.h"
#समावेश "dce/dce_dmcu.h"
#समावेश "dce/dce_aux.h"
#समावेश "dce/dce_i2c.h"

#समावेश "dce/dce_12_0_offset.h"
#समावेश "dce/dce_12_0_sh_mask.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"
#समावेश "nbio/nbio_6_1_offset.h"
#समावेश "mmhub/mmhub_1_0_offset.h"
#समावेश "mmhub/mmhub_1_0_sh_mask.h"
#समावेश "reg_helper.h"

#समावेश "dce100/dce100_resource.h"

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

क्रमागत dce120_clk_src_array_id अणु
	DCE120_CLK_SRC_PLL0,
	DCE120_CLK_SRC_PLL1,
	DCE120_CLK_SRC_PLL2,
	DCE120_CLK_SRC_PLL3,
	DCE120_CLK_SRC_PLL4,
	DCE120_CLK_SRC_PLL5,

	DCE120_CLK_SRC_TOTAL
पूर्ण;

अटल स्थिर काष्ठा dce110_timing_generator_offsets dce120_tg_offsets[] = अणु
	अणु
		.crtc = (mmCRTC0_CRTC_CONTROL - mmCRTC0_CRTC_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC1_CRTC_CONTROL - mmCRTC0_CRTC_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC2_CRTC_CONTROL - mmCRTC0_CRTC_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC3_CRTC_CONTROL - mmCRTC0_CRTC_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC4_CRTC_CONTROL - mmCRTC0_CRTC_CONTROL),
	पूर्ण,
	अणु
		.crtc = (mmCRTC5_CRTC_CONTROL - mmCRTC0_CRTC_CONTROL),
	पूर्ण
पूर्ण;

/* begin *********************
 * macros to expend रेजिस्टर list macro defined in HW object header file */

#घोषणा BASE_INNER(seg) \
	DCE_BASE__INST0_SEG ## seg

#घोषणा NBIO_BASE_INNER(seg) \
	NBIF_BASE__INST0_SEG ## seg

#घोषणा NBIO_BASE(seg) \
	NBIO_BASE_INNER(seg)

/* compile समय expand base address. */
#घोषणा BASE(seg) \
	BASE_INNER(seg)

#घोषणा SR(reg_name)\
		.reg_name = BASE(mm ## reg_name ## _BASE_IDX) +  \
					mm ## reg_name

#घोषणा SRI(reg_name, block, id)\
	.reg_name = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

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
		ipp_regs(2),
		ipp_regs(3),
		ipp_regs(4),
		ipp_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dce_ipp_shअगरt ipp_shअगरt = अणु
		IPP_DCE120_MASK_SH_LIST_SOC_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_ipp_mask ipp_mask = अणु
		IPP_DCE120_MASK_SH_LIST_SOC_BASE(_MASK)
पूर्ण;

#घोषणा transक्रमm_regs(id)\
[id] = अणु\
		XFM_COMMON_REG_LIST_DCE110(id)\
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
		XFM_COMMON_MASK_SH_LIST_SOC_BASE(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_transक्रमm_mask xfm_mask = अणु
		XFM_COMMON_MASK_SH_LIST_SOC_BASE(_MASK)
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
	LE_DCE120_REG_LIST(id), \
	SRI(DP_DPHY_INTERNAL_CTRL, DP, id) \
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
	stream_enc_regs(2),
	stream_enc_regs(3),
	stream_enc_regs(4),
	stream_enc_regs(5)
पूर्ण;

अटल स्थिर काष्ठा dce_stream_encoder_shअगरt se_shअगरt = अणु
		SE_COMMON_MASK_SH_LIST_DCE120(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_stream_encoder_mask se_mask = अणु
		SE_COMMON_MASK_SH_LIST_DCE120(_MASK)
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
	DCE12_AUX_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_aux_रेजिस्टरs_mask aux_mask = अणु
	DCE12_AUX_MASK_SH_LIST(_MASK)
पूर्ण;

#घोषणा opp_regs(id)\
[id] = अणु\
	OPP_DCE_120_REG_LIST(id),\
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
	OPP_COMMON_MASK_SH_LIST_DCE_120(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_opp_mask opp_mask = अणु
	OPP_COMMON_MASK_SH_LIST_DCE_120(_MASK)
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
	audio_regs(5)
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

#घोषणा clk_src_regs(index, id)\
[index] = अणु\
	CS_COMMON_REG_LIST_DCE_112(id),\
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
		CS_COMMON_MASK_SH_LIST_DCE_112(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce110_clk_src_mask cs_mask = अणु
		CS_COMMON_MASK_SH_LIST_DCE_112(_MASK)
पूर्ण;

अटल काष्ठा output_pixel_processor *dce120_opp_create(
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
अटल काष्ठा dce_aux *dce120_aux_engine_create(
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

अटल काष्ठा dce_i2c_hw *dce120_i2c_hw_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_i2c_hw *dce_i2c_hw =
		kzalloc(माप(काष्ठा dce_i2c_hw), GFP_KERNEL);

	अगर (!dce_i2c_hw)
		वापस शून्य;

	dce112_i2c_hw_स्थिरruct(dce_i2c_hw, ctx, inst,
				    &i2c_hw_regs[inst], &i2c_shअगरts, &i2c_masks);

	वापस dce_i2c_hw;
पूर्ण
अटल स्थिर काष्ठा bios_रेजिस्टरs bios_regs = अणु
	.BIOS_SCRATCH_3 = mmBIOS_SCRATCH_3 + NBIO_BASE(mmBIOS_SCRATCH_3_BASE_IDX),
	.BIOS_SCRATCH_6 = mmBIOS_SCRATCH_6 + NBIO_BASE(mmBIOS_SCRATCH_6_BASE_IDX)
पूर्ण;

अटल स्थिर काष्ठा resource_caps res_cap = अणु
		.num_timing_generator = 6,
		.num_audio = 7,
		.num_stream_encoder = 6,
		.num_pll = 6,
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

अटल स्थिर काष्ठा dc_debug_options debug_शेषs = अणु
		.disable_घड़ी_gate = true,
पूर्ण;

अटल काष्ठा घड़ी_source *dce120_घड़ी_source_create(
	काष्ठा dc_context *ctx,
	काष्ठा dc_bios *bios,
	क्रमागत घड़ी_source_id id,
	स्थिर काष्ठा dce110_clk_src_regs *regs,
	bool dp_clk_src)
अणु
	काष्ठा dce110_clk_src *clk_src =
		kzalloc(माप(*clk_src), GFP_KERNEL);

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

अटल व्योम dce120_घड़ी_source_destroy(काष्ठा घड़ी_source **clk_src)
अणु
	kमुक्त(TO_DCE110_CLK_SRC(*clk_src));
	*clk_src = शून्य;
पूर्ण


अटल bool dce120_hw_sequencer_create(काष्ठा dc *dc)
अणु
	/* All रेजिस्टरs used by dce11.2 match those in dce11 in offset and
	 * काष्ठाure
	 */
	dce120_hw_sequencer_स्थिरruct(dc);

	/*TODO	Move to separate file and Override what is needed */

	वापस true;
पूर्ण

अटल काष्ठा timing_generator *dce120_timing_generator_create(
		काष्ठा dc_context *ctx,
		uपूर्णांक32_t instance,
		स्थिर काष्ठा dce110_timing_generator_offsets *offsets)
अणु
	काष्ठा dce110_timing_generator *tg110 =
		kzalloc(माप(काष्ठा dce110_timing_generator), GFP_KERNEL);

	अगर (!tg110)
		वापस शून्य;

	dce120_timing_generator_स्थिरruct(tg110, ctx, instance, offsets);
	वापस &tg110->base;
पूर्ण

अटल व्योम dce120_transक्रमm_destroy(काष्ठा transक्रमm **xfm)
अणु
	kमुक्त(TO_DCE_TRANSFORM(*xfm));
	*xfm = शून्य;
पूर्ण

अटल व्योम dce120_resource_deकाष्ठा(काष्ठा dce110_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		अगर (pool->base.opps[i] != शून्य)
			dce110_opp_destroy(&pool->base.opps[i]);

		अगर (pool->base.transक्रमms[i] != शून्य)
			dce120_transक्रमm_destroy(&pool->base.transक्रमms[i]);

		अगर (pool->base.ipps[i] != शून्य)
			dce_ipp_destroy(&pool->base.ipps[i]);

		अगर (pool->base.mis[i] != शून्य) अणु
			kमुक्त(TO_DCE_MEM_INPUT(pool->base.mis[i]));
			pool->base.mis[i] = शून्य;
		पूर्ण

		अगर (pool->base.irqs != शून्य) अणु
			dal_irq_service_destroy(&pool->base.irqs);
		पूर्ण

		अगर (pool->base.timing_generators[i] != शून्य) अणु
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

	क्रम (i = 0; i < pool->base.audio_count; i++) अणु
		अगर (pool->base.audios[i])
			dce_aud_destroy(&pool->base.audios[i]);
	पूर्ण

	क्रम (i = 0; i < pool->base.stream_enc_count; i++) अणु
		अगर (pool->base.stream_enc[i] != शून्य)
			kमुक्त(DCE110STRENC_FROM_STRENC(pool->base.stream_enc[i]));
	पूर्ण

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] != शून्य)
			dce120_घड़ी_source_destroy(
				&pool->base.घड़ी_sources[i]);
	पूर्ण

	अगर (pool->base.dp_घड़ी_source != शून्य)
		dce120_घड़ी_source_destroy(&pool->base.dp_घड़ी_source);

	अगर (pool->base.abm != शून्य)
		dce_abm_destroy(&pool->base.abm);

	अगर (pool->base.dmcu != शून्य)
		dce_dmcu_destroy(&pool->base.dmcu);
पूर्ण

अटल व्योम पढ़ो_dce_straps(
	काष्ठा dc_context *ctx,
	काष्ठा resource_straps *straps)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg_soc15(ctx, mmCC_DC_MISC_STRAPS, 0);

	straps->audio_stream_number = get_reg_field_value(reg_val,
							  CC_DC_MISC_STRAPS,
							  AUDIO_STREAM_NUMBER);
	straps->hdmi_disable = get_reg_field_value(reg_val,
						   CC_DC_MISC_STRAPS,
						   HDMI_DISABLE);

	reg_val = dm_पढ़ो_reg_soc15(ctx, mmDC_PINSTRAPS, 0);
	straps->dc_pinstraps_audio = get_reg_field_value(reg_val,
							 DC_PINSTRAPS,
							 DC_PINSTRAPS_AUDIO);
पूर्ण

अटल काष्ठा audio *create_audio(
		काष्ठा dc_context *ctx, अचिन्हित पूर्णांक inst)
अणु
	वापस dce_audio_create(ctx, inst,
			&audio_regs[inst], &audio_shअगरt, &audio_mask);
पूर्ण

अटल स्थिर काष्ठा encoder_feature_support link_enc_feature = अणु
		.max_hdmi_deep_color = COLOR_DEPTH_121212,
		.max_hdmi_pixel_घड़ी = 600000,
		.hdmi_ycbcr420_supported = true,
		.dp_ycbcr420_supported = false,
		.flags.bits.IS_HBR2_CAPABLE = true,
		.flags.bits.IS_HBR3_CAPABLE = true,
		.flags.bits.IS_TPS3_CAPABLE = true,
		.flags.bits.IS_TPS4_CAPABLE = true,
पूर्ण;

अटल काष्ठा link_encoder *dce120_link_encoder_create(
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

अटल काष्ठा panel_cntl *dce120_panel_cntl_create(स्थिर काष्ठा panel_cntl_init_data *init_data)
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

अटल काष्ठा input_pixel_processor *dce120_ipp_create(
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

अटल काष्ठा stream_encoder *dce120_stream_encoder_create(
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
	.reg_name[id] = BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
					mm ## block ## id ## _ ## reg_name

अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs hwseq_reg = अणु
		HWSEQ_DCE120_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt hwseq_shअगरt = अणु
		HWSEQ_DCE12_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask hwseq_mask = अणु
		HWSEQ_DCE12_MASK_SH_LIST(_MASK)
पूर्ण;

/* HWSEQ regs क्रम VG20 */
अटल स्थिर काष्ठा dce_hwseq_रेजिस्टरs dce121_hwseq_reg = अणु
		HWSEQ_VG20_REG_LIST()
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_shअगरt dce121_hwseq_shअगरt = अणु
		HWSEQ_VG20_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_hwseq_mask dce121_hwseq_mask = अणु
		HWSEQ_VG20_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा dce_hwseq *dce120_hwseq_create(
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

अटल काष्ठा dce_hwseq *dce121_hwseq_create(
	काष्ठा dc_context *ctx)
अणु
	काष्ठा dce_hwseq *hws = kzalloc(माप(काष्ठा dce_hwseq), GFP_KERNEL);

	अगर (hws) अणु
		hws->ctx = ctx;
		hws->regs = &dce121_hwseq_reg;
		hws->shअगरts = &dce121_hwseq_shअगरt;
		hws->masks = &dce121_hwseq_mask;
	पूर्ण
	वापस hws;
पूर्ण

अटल स्थिर काष्ठा resource_create_funcs res_create_funcs = अणु
	.पढ़ो_dce_straps = पढ़ो_dce_straps,
	.create_audio = create_audio,
	.create_stream_encoder = dce120_stream_encoder_create,
	.create_hwseq = dce120_hwseq_create,
पूर्ण;

अटल स्थिर काष्ठा resource_create_funcs dce121_res_create_funcs = अणु
	.पढ़ो_dce_straps = पढ़ो_dce_straps,
	.create_audio = create_audio,
	.create_stream_encoder = dce120_stream_encoder_create,
	.create_hwseq = dce121_hwseq_create,
पूर्ण;


#घोषणा mi_inst_regs(id) अणु MI_DCE12_REG_LIST(id) पूर्ण
अटल स्थिर काष्ठा dce_mem_input_रेजिस्टरs mi_regs[] = अणु
		mi_inst_regs(0),
		mi_inst_regs(1),
		mi_inst_regs(2),
		mi_inst_regs(3),
		mi_inst_regs(4),
		mi_inst_regs(5),
पूर्ण;

अटल स्थिर काष्ठा dce_mem_input_shअगरt mi_shअगरts = अणु
		MI_DCE12_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा dce_mem_input_mask mi_masks = अणु
		MI_DCE12_MASK_SH_LIST(_MASK)
पूर्ण;

अटल काष्ठा mem_input *dce120_mem_input_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_mem_input *dce_mi = kzalloc(माप(काष्ठा dce_mem_input),
					       GFP_KERNEL);

	अगर (!dce_mi) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	dce120_mem_input_स्थिरruct(dce_mi, ctx, inst, &mi_regs[inst], &mi_shअगरts, &mi_masks);
	वापस &dce_mi->base;
पूर्ण

अटल काष्ठा transक्रमm *dce120_transक्रमm_create(
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst)
अणु
	काष्ठा dce_transक्रमm *transक्रमm =
		kzalloc(माप(काष्ठा dce_transक्रमm), GFP_KERNEL);

	अगर (!transक्रमm)
		वापस शून्य;

	dce_transक्रमm_स्थिरruct(transक्रमm, ctx, inst,
				&xfm_regs[inst], &xfm_shअगरt, &xfm_mask);
	transक्रमm->lb_memory_size = 0x1404; /*5124*/
	वापस &transक्रमm->base;
पूर्ण

अटल व्योम dce120_destroy_resource_pool(काष्ठा resource_pool **pool)
अणु
	काष्ठा dce110_resource_pool *dce110_pool = TO_DCE110_RES_POOL(*pool);

	dce120_resource_deकाष्ठा(dce110_pool);
	kमुक्त(dce110_pool);
	*pool = शून्य;
पूर्ण

अटल स्थिर काष्ठा resource_funcs dce120_res_pool_funcs = अणु
	.destroy = dce120_destroy_resource_pool,
	.link_enc_create = dce120_link_encoder_create,
	.panel_cntl_create = dce120_panel_cntl_create,
	.validate_bandwidth = dce112_validate_bandwidth,
	.validate_plane = dce100_validate_plane,
	.add_stream_to_ctx = dce112_add_stream_to_ctx,
	.find_first_मुक्त_match_stream_enc_क्रम_link = dce110_find_first_मुक्त_match_stream_enc_क्रम_link
पूर्ण;

अटल व्योम bw_calcs_data_update_from_pplib(काष्ठा dc *dc)
अणु
	काष्ठा dm_pp_घड़ी_levels_with_latency eng_clks = अणु0पूर्ण;
	काष्ठा dm_pp_घड़ी_levels_with_latency mem_clks = अणु0पूर्ण;
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges clk_ranges = अणु0पूर्ण;
	पूर्णांक i;
	अचिन्हित पूर्णांक clk;
	अचिन्हित पूर्णांक latency;
	/*original logic in dal3*/
	पूर्णांक memory_type_multiplier = MEMORY_TYPE_MULTIPLIER_CZ;

	/*करो प्रणाली घड़ी*/
	अगर (!dm_pp_get_घड़ी_levels_by_type_with_latency(
				dc->ctx,
				DM_PP_CLOCK_TYPE_ENGINE_CLK,
				&eng_clks) || eng_clks.num_levels == 0) अणु

		eng_clks.num_levels = 8;
		clk = 300000;

		क्रम (i = 0; i < eng_clks.num_levels; i++) अणु
			eng_clks.data[i].घड़ीs_in_khz = clk;
			clk += 100000;
		पूर्ण
	पूर्ण

	/* convert all the घड़ी fro kHz to fix poपूर्णांक mHz  TODO: wloop data */
	dc->bw_vbios->high_sclk = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels-1].घड़ीs_in_khz, 1000);
	dc->bw_vbios->mid1_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels/8].घड़ीs_in_khz, 1000);
	dc->bw_vbios->mid2_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*2/8].घड़ीs_in_khz, 1000);
	dc->bw_vbios->mid3_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*3/8].घड़ीs_in_khz, 1000);
	dc->bw_vbios->mid4_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*4/8].घड़ीs_in_khz, 1000);
	dc->bw_vbios->mid5_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*5/8].घड़ीs_in_khz, 1000);
	dc->bw_vbios->mid6_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*6/8].घड़ीs_in_khz, 1000);
	dc->bw_vbios->low_sclk  = bw_frc_to_fixed(
			eng_clks.data[0].घड़ीs_in_khz, 1000);

	/*करो memory घड़ी*/
	अगर (!dm_pp_get_घड़ी_levels_by_type_with_latency(
			dc->ctx,
			DM_PP_CLOCK_TYPE_MEMORY_CLK,
			&mem_clks) || mem_clks.num_levels == 0) अणु

		mem_clks.num_levels = 3;
		clk = 250000;
		latency = 45;

		क्रम (i = 0; i < eng_clks.num_levels; i++) अणु
			mem_clks.data[i].घड़ीs_in_khz = clk;
			mem_clks.data[i].latency_in_us = latency;
			clk += 500000;
			latency -= 5;
		पूर्ण

	पूर्ण

	/* we करोn't need to call PPLIB क्रम validation घड़ी since they
	 * also give us the highest sclk and highest mclk (UMA घड़ी).
	 * ALSO always convert UMA घड़ी (from PPLIB)  to YCLK (HW क्रमmula):
	 * YCLK = UMACLK*m_memoryTypeMultiplier
	 */
	अगर (dc->bw_vbios->memory_type == bw_def_hbm)
		memory_type_multiplier = MEMORY_TYPE_HBM;

	dc->bw_vbios->low_yclk = bw_frc_to_fixed(
		mem_clks.data[0].घड़ीs_in_khz * memory_type_multiplier, 1000);
	dc->bw_vbios->mid_yclk = bw_frc_to_fixed(
		mem_clks.data[mem_clks.num_levels>>1].घड़ीs_in_khz * memory_type_multiplier,
		1000);
	dc->bw_vbios->high_yclk = bw_frc_to_fixed(
		mem_clks.data[mem_clks.num_levels-1].घड़ीs_in_khz * memory_type_multiplier,
		1000);

	/* Now notअगरy PPLib/SMU about which Watermarks sets they should select
	 * depending on DPM state they are in. And update BW MGR GFX Engine and
	 * Memory घड़ी member variables क्रम Watermarks calculations क्रम each
	 * Watermark Set
	 */
	clk_ranges.num_wm_sets = 4;
	clk_ranges.wm_clk_ranges[0].wm_set_id = WM_SET_A;
	clk_ranges.wm_clk_ranges[0].wm_min_eng_clk_in_khz =
			eng_clks.data[0].घड़ीs_in_khz;
	clk_ranges.wm_clk_ranges[0].wm_max_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].घड़ीs_in_khz - 1;
	clk_ranges.wm_clk_ranges[0].wm_min_mem_clk_in_khz =
			mem_clks.data[0].घड़ीs_in_khz;
	clk_ranges.wm_clk_ranges[0].wm_max_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].घड़ीs_in_khz - 1;

	clk_ranges.wm_clk_ranges[1].wm_set_id = WM_SET_B;
	clk_ranges.wm_clk_ranges[1].wm_min_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].घड़ीs_in_khz;
	/* 5 GHz instead of data[7].घड़ीInKHz to cover Overdrive */
	clk_ranges.wm_clk_ranges[1].wm_max_eng_clk_in_khz = 5000000;
	clk_ranges.wm_clk_ranges[1].wm_min_mem_clk_in_khz =
			mem_clks.data[0].घड़ीs_in_khz;
	clk_ranges.wm_clk_ranges[1].wm_max_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].घड़ीs_in_khz - 1;

	clk_ranges.wm_clk_ranges[2].wm_set_id = WM_SET_C;
	clk_ranges.wm_clk_ranges[2].wm_min_eng_clk_in_khz =
			eng_clks.data[0].घड़ीs_in_khz;
	clk_ranges.wm_clk_ranges[2].wm_max_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].घड़ीs_in_khz - 1;
	clk_ranges.wm_clk_ranges[2].wm_min_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].घड़ीs_in_khz;
	/* 5 GHz instead of data[2].घड़ीInKHz to cover Overdrive */
	clk_ranges.wm_clk_ranges[2].wm_max_mem_clk_in_khz = 5000000;

	clk_ranges.wm_clk_ranges[3].wm_set_id = WM_SET_D;
	clk_ranges.wm_clk_ranges[3].wm_min_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].घड़ीs_in_khz;
	/* 5 GHz instead of data[7].घड़ीInKHz to cover Overdrive */
	clk_ranges.wm_clk_ranges[3].wm_max_eng_clk_in_khz = 5000000;
	clk_ranges.wm_clk_ranges[3].wm_min_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].घड़ीs_in_khz;
	/* 5 GHz instead of data[2].घड़ीInKHz to cover Overdrive */
	clk_ranges.wm_clk_ranges[3].wm_max_mem_clk_in_khz = 5000000;

	/* Notअगरy PP Lib/SMU which Watermarks to use क्रम which घड़ी ranges */
	dm_pp_notअगरy_wm_घड़ी_changes(dc->ctx, &clk_ranges);
पूर्ण

अटल uपूर्णांक32_t पढ़ो_pipe_fuses(काष्ठा dc_context *ctx)
अणु
	uपूर्णांक32_t value = dm_पढ़ो_reg_soc15(ctx, mmCC_DC_PIPE_DIS, 0);
	/* VG20 support max 6 pipes */
	value = value & 0x3f;
	वापस value;
पूर्ण

अटल bool dce120_resource_स्थिरruct(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc,
	काष्ठा dce110_resource_pool *pool)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक j;
	काष्ठा dc_context *ctx = dc->ctx;
	काष्ठा irq_service_init_data irq_init_data;
	अटल स्थिर काष्ठा resource_create_funcs *res_funcs;
	bool is_vg20 = ASICREV_IS_VEGA20_P(ctx->asic_id.hw_पूर्णांकernal_rev);
	uपूर्णांक32_t pipe_fuses;

	ctx->dc_bios->regs = &bios_regs;

	pool->base.res_cap = &res_cap;
	pool->base.funcs = &dce120_res_pool_funcs;

	/* TODO: Fill more data from GreenlandAsicCapability.cpp */
	pool->base.pipe_count = res_cap.num_timing_generator;
	pool->base.timing_generator_count = pool->base.res_cap->num_timing_generator;
	pool->base.underlay_pipe_index = NO_UNDERLAY_PIPE;

	dc->caps.max_करोwnscale_ratio = 200;
	dc->caps.i2c_speed_in_khz = 100;
	dc->caps.i2c_speed_in_khz_hdcp = 100; /*1.4 w/a not applied by शेष*/
	dc->caps.max_cursor_size = 128;
	dc->caps.min_horizontal_blanking_period = 80;
	dc->caps.dual_link_dvi = true;
	dc->caps.psp_setup_panel_mode = true;
	dc->caps.extended_aux_समयout_support = false;
	dc->debug = debug_शेषs;

	/*************************************************
	 *  Create resources                             *
	 *************************************************/

	pool->base.घड़ी_sources[DCE120_CLK_SRC_PLL0] =
			dce120_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL0,
				&clk_src_regs[0], false);
	pool->base.घड़ी_sources[DCE120_CLK_SRC_PLL1] =
			dce120_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL1,
				&clk_src_regs[1], false);
	pool->base.घड़ी_sources[DCE120_CLK_SRC_PLL2] =
			dce120_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL2,
				&clk_src_regs[2], false);
	pool->base.घड़ी_sources[DCE120_CLK_SRC_PLL3] =
			dce120_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL3,
				&clk_src_regs[3], false);
	pool->base.घड़ी_sources[DCE120_CLK_SRC_PLL4] =
			dce120_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL4,
				&clk_src_regs[4], false);
	pool->base.घड़ी_sources[DCE120_CLK_SRC_PLL5] =
			dce120_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_COMBO_PHY_PLL5,
				&clk_src_regs[5], false);
	pool->base.clk_src_count = DCE120_CLK_SRC_TOTAL;

	pool->base.dp_घड़ी_source =
			dce120_घड़ी_source_create(ctx, ctx->dc_bios,
				CLOCK_SOURCE_ID_DP_DTO,
				&clk_src_regs[0], true);

	क्रम (i = 0; i < pool->base.clk_src_count; i++) अणु
		अगर (pool->base.घड़ी_sources[i] == शून्य) अणु
			dm_error("DC: failed to create clock sources!\n");
			BREAK_TO_DEBUGGER();
			जाओ clk_src_create_fail;
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


	irq_init_data.ctx = dc->ctx;
	pool->base.irqs = dal_irq_service_dce120_create(&irq_init_data);
	अगर (!pool->base.irqs)
		जाओ irqs_create_fail;

	/* VG20: Pipe harvesting enabled, retrieve valid pipe fuses */
	अगर (is_vg20)
		pipe_fuses = पढ़ो_pipe_fuses(ctx);

	/* index to valid pipe resource */
	j = 0;
	क्रम (i = 0; i < pool->base.pipe_count; i++) अणु
		अगर (is_vg20) अणु
			अगर ((pipe_fuses & (1 << i)) != 0) अणु
				dm_error("DC: skip invalid pipe %d!\n", i);
				जारी;
			पूर्ण
		पूर्ण

		pool->base.timing_generators[j] =
				dce120_timing_generator_create(
					ctx,
					i,
					&dce120_tg_offsets[i]);
		अगर (pool->base.timing_generators[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error("DC: failed to create tg!\n");
			जाओ controller_create_fail;
		पूर्ण

		pool->base.mis[j] = dce120_mem_input_create(ctx, i);

		अगर (pool->base.mis[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create memory input!\n");
			जाओ controller_create_fail;
		पूर्ण

		pool->base.ipps[j] = dce120_ipp_create(ctx, i);
		अगर (pool->base.ipps[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create input pixel processor!\n");
			जाओ controller_create_fail;
		पूर्ण

		pool->base.transक्रमms[j] = dce120_transक्रमm_create(ctx, i);
		अगर (pool->base.transक्रमms[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create transform!\n");
			जाओ res_create_fail;
		पूर्ण

		pool->base.opps[j] = dce120_opp_create(
			ctx,
			i);
		अगर (pool->base.opps[j] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC: failed to create output pixel processor!\n");
		पूर्ण

		/* check next valid pipe */
		j++;
	पूर्ण

	क्रम (i = 0; i < pool->base.res_cap->num_ddc; i++) अणु
		pool->base.engines[i] = dce120_aux_engine_create(ctx, i);
		अगर (pool->base.engines[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create aux engine!!\n");
			जाओ res_create_fail;
		पूर्ण
		pool->base.hw_i2cs[i] = dce120_i2c_hw_create(ctx, i);
		अगर (pool->base.hw_i2cs[i] == शून्य) अणु
			BREAK_TO_DEBUGGER();
			dm_error(
				"DC:failed to create i2c engine!!\n");
			जाओ res_create_fail;
		पूर्ण
		pool->base.sw_i2cs[i] = शून्य;
	पूर्ण

	/* valid pipe num */
	pool->base.pipe_count = j;
	pool->base.timing_generator_count = j;

	अगर (is_vg20)
		res_funcs = &dce121_res_create_funcs;
	अन्यथा
		res_funcs = &res_create_funcs;

	अगर (!resource_स्थिरruct(num_भव_links, dc, &pool->base, res_funcs))
		जाओ res_create_fail;

	/* Create hardware sequencer */
	अगर (!dce120_hw_sequencer_create(dc))
		जाओ controller_create_fail;

	dc->caps.max_planes =  pool->base.pipe_count;

	क्रम (i = 0; i < dc->caps.max_planes; ++i)
		dc->caps.planes[i] = plane_cap;

	bw_calcs_init(dc->bw_dceip, dc->bw_vbios, dc->ctx->asic_id);

	bw_calcs_data_update_from_pplib(dc);

	वापस true;

irqs_create_fail:
controller_create_fail:
clk_src_create_fail:
res_create_fail:

	dce120_resource_deकाष्ठा(pool);

	वापस false;
पूर्ण

काष्ठा resource_pool *dce120_create_resource_pool(
	uपूर्णांक8_t num_भव_links,
	काष्ठा dc *dc)
अणु
	काष्ठा dce110_resource_pool *pool =
		kzalloc(माप(काष्ठा dce110_resource_pool), GFP_KERNEL);

	अगर (!pool)
		वापस शून्य;

	अगर (dce120_resource_स्थिरruct(num_भव_links, dc, pool))
		वापस &pool->base;

	kमुक्त(pool);
	BREAK_TO_DEBUGGER();
	वापस शून्य;
पूर्ण
