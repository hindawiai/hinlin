<शैली गुरु>
/* Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DC_OPP_DCN10_H__
#घोषणा __DC_OPP_DCN10_H__

#समावेश "opp.h"

#घोषणा TO_DCN10_OPP(opp)\
	container_of(opp, काष्ठा dcn10_opp, base)

#घोषणा OPP_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा OPP_REG_LIST_DCN(id) \
	SRI(FMT_BIT_DEPTH_CONTROL, FMT, id), \
	SRI(FMT_CONTROL, FMT, id), \
	SRI(FMT_DITHER_RAND_R_SEED, FMT, id), \
	SRI(FMT_DITHER_RAND_G_SEED, FMT, id), \
	SRI(FMT_DITHER_RAND_B_SEED, FMT, id), \
	SRI(FMT_CLAMP_CNTL, FMT, id), \
	SRI(FMT_DYNAMIC_EXP_CNTL, FMT, id), \
	SRI(FMT_MAP420_MEMORY_CONTROL, FMT, id), \
	SRI(OPPBUF_CONTROL, OPPBUF, id),\
	SRI(OPPBUF_3D_PARAMETERS_0, OPPBUF, id), \
	SRI(OPPBUF_3D_PARAMETERS_1, OPPBUF, id), \
	SRI(OPP_PIPE_CONTROL, OPP_PIPE, id)

#घोषणा OPP_REG_LIST_DCN10(id) \
	OPP_REG_LIST_DCN(id)

#घोषणा OPP_COMMON_REG_VARIABLE_LIST \
	uपूर्णांक32_t FMT_BIT_DEPTH_CONTROL; \
	uपूर्णांक32_t FMT_CONTROL; \
	uपूर्णांक32_t FMT_DITHER_RAND_R_SEED; \
	uपूर्णांक32_t FMT_DITHER_RAND_G_SEED; \
	uपूर्णांक32_t FMT_DITHER_RAND_B_SEED; \
	uपूर्णांक32_t FMT_CLAMP_CNTL; \
	uपूर्णांक32_t FMT_DYNAMIC_EXP_CNTL; \
	uपूर्णांक32_t FMT_MAP420_MEMORY_CONTROL; \
	uपूर्णांक32_t OPPBUF_CONTROL; \
	uपूर्णांक32_t OPPBUF_CONTROL1; \
	uपूर्णांक32_t OPPBUF_3D_PARAMETERS_0; \
	uपूर्णांक32_t OPPBUF_3D_PARAMETERS_1; \
	uपूर्णांक32_t OPP_PIPE_CONTROL

#घोषणा OPP_MASK_SH_LIST_DCN(mask_sh) \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_TRUNCATE_EN, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_TRUNCATE_DEPTH, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_TRUNCATE_MODE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_SPATIAL_DITHER_EN, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_SPATIAL_DITHER_MODE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_SPATIAL_DITHER_DEPTH, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_TEMPORAL_DITHER_EN, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_HIGHPASS_RANDOM_ENABLE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_FRAME_RANDOM_ENABLE, mask_sh), \
	OPP_SF(FMT0_FMT_BIT_DEPTH_CONTROL, FMT_RGB_RANDOM_ENABLE, mask_sh), \
	OPP_SF(FMT0_FMT_CONTROL, FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, mask_sh), \
	OPP_SF(FMT0_FMT_CONTROL, FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, mask_sh), \
	OPP_SF(FMT0_FMT_CONTROL, FMT_PIXEL_ENCODING, mask_sh), \
	OPP_SF(FMT0_FMT_CONTROL, FMT_STEREOSYNC_OVERRIDE, mask_sh), \
	OPP_SF(FMT0_FMT_DITHER_RAND_R_SEED, FMT_RAND_R_SEED, mask_sh), \
	OPP_SF(FMT0_FMT_DITHER_RAND_G_SEED, FMT_RAND_G_SEED, mask_sh), \
	OPP_SF(FMT0_FMT_DITHER_RAND_B_SEED, FMT_RAND_B_SEED, mask_sh), \
	OPP_SF(FMT0_FMT_CLAMP_CNTL, FMT_CLAMP_DATA_EN, mask_sh), \
	OPP_SF(FMT0_FMT_CLAMP_CNTL, FMT_CLAMP_COLOR_FORMAT, mask_sh), \
	OPP_SF(FMT0_FMT_DYNAMIC_EXP_CNTL, FMT_DYNAMIC_EXP_EN, mask_sh), \
	OPP_SF(FMT0_FMT_DYNAMIC_EXP_CNTL, FMT_DYNAMIC_EXP_MODE, mask_sh), \
	OPP_SF(FMT0_FMT_MAP420_MEMORY_CONTROL, FMT_MAP420MEM_PWR_FORCE, mask_sh), \
	OPP_SF(OPPBUF0_OPPBUF_CONTROL, OPPBUF_ACTIVE_WIDTH, mask_sh),\
	OPP_SF(OPPBUF0_OPPBUF_CONTROL, OPPBUF_PIXEL_REPETITION, mask_sh),\
	OPP_SF(OPPBUF0_OPPBUF_3D_PARAMETERS_0, OPPBUF_3D_VACT_SPACE1_SIZE, mask_sh), \
	OPP_SF(OPPBUF0_OPPBUF_3D_PARAMETERS_0, OPPBUF_3D_VACT_SPACE2_SIZE, mask_sh), \
	OPP_SF(OPP_PIPE0_OPP_PIPE_CONTROL, OPP_PIPE_CLOCK_EN, mask_sh)

#घोषणा OPP_MASK_SH_LIST_DCN10(mask_sh) \
	OPP_MASK_SH_LIST_DCN(mask_sh), \
	OPP_SF(OPPBUF0_OPPBUF_CONTROL, OPPBUF_DISPLAY_SEGMENTATION, mask_sh),\
	OPP_SF(OPPBUF0_OPPBUF_CONTROL, OPPBUF_OVERLAP_PIXEL_NUM, mask_sh)

#घोषणा OPP_DCN10_REG_FIELD_LIST(type) \
	type FMT_TRUNCATE_EN; \
	type FMT_TRUNCATE_DEPTH; \
	type FMT_TRUNCATE_MODE; \
	type FMT_SPATIAL_DITHER_EN; \
	type FMT_SPATIAL_DITHER_MODE; \
	type FMT_SPATIAL_DITHER_DEPTH; \
	type FMT_TEMPORAL_DITHER_EN; \
	type FMT_HIGHPASS_RANDOM_ENABLE; \
	type FMT_FRAME_RANDOM_ENABLE; \
	type FMT_RGB_RANDOM_ENABLE; \
	type FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX; \
	type FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP; \
	type FMT_RAND_R_SEED; \
	type FMT_RAND_G_SEED; \
	type FMT_RAND_B_SEED; \
	type FMT_PIXEL_ENCODING; \
	type FMT_SUBSAMPLING_MODE; \
	type FMT_CBCR_BIT_REDUCTION_BYPASS; \
	type FMT_CLAMP_DATA_EN; \
	type FMT_CLAMP_COLOR_FORMAT; \
	type FMT_DYNAMIC_EXP_EN; \
	type FMT_DYNAMIC_EXP_MODE; \
	type FMT_MAP420MEM_PWR_FORCE; \
	type FMT_STEREOSYNC_OVERRIDE; \
	type OPPBUF_ACTIVE_WIDTH;\
	type OPPBUF_PIXEL_REPETITION;\
	type OPPBUF_DISPLAY_SEGMENTATION;\
	type OPPBUF_OVERLAP_PIXEL_NUM;\
	type OPPBUF_NUM_SEGMENT_PADDED_PIXELS; \
	type OPPBUF_3D_VACT_SPACE1_SIZE; \
	type OPPBUF_3D_VACT_SPACE2_SIZE; \
	type OPP_PIPE_CLOCK_EN

काष्ठा dcn10_opp_रेजिस्टरs अणु
	OPP_COMMON_REG_VARIABLE_LIST;
पूर्ण;

काष्ठा dcn10_opp_shअगरt अणु
	OPP_DCN10_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn10_opp_mask अणु
	OPP_DCN10_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn10_opp अणु
	काष्ठा output_pixel_processor base;

	स्थिर काष्ठा dcn10_opp_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn10_opp_shअगरt *opp_shअगरt;
	स्थिर काष्ठा dcn10_opp_mask *opp_mask;

	bool is_ग_लिखो_to_ram_a_safe;
पूर्ण;

व्योम dcn10_opp_स्थिरruct(काष्ठा dcn10_opp *oppn10,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn10_opp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_opp_shअगरt *opp_shअगरt,
	स्थिर काष्ठा dcn10_opp_mask *opp_mask);

व्योम opp1_set_dyn_expansion(
	काष्ठा output_pixel_processor *opp,
	क्रमागत dc_color_space color_sp,
	क्रमागत dc_color_depth color_dpth,
	क्रमागत संकेत_type संकेत);

व्योम opp1_program_fmt(
	काष्ठा output_pixel_processor *opp,
	काष्ठा bit_depth_reduction_params *fmt_bit_depth,
	काष्ठा clamping_and_pixel_encoding_params *clamping);

व्योम opp1_program_bit_depth_reduction(
	काष्ठा output_pixel_processor *opp,
	स्थिर काष्ठा bit_depth_reduction_params *params);

व्योम opp1_program_stereo(
	काष्ठा output_pixel_processor *opp,
	bool enable,
	स्थिर काष्ठा dc_crtc_timing *timing);

व्योम opp1_pipe_घड़ी_control(काष्ठा output_pixel_processor *opp, bool enable);

व्योम opp1_destroy(काष्ठा output_pixel_processor **opp);

#पूर्ण_अगर
