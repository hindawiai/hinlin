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

#अगर_अघोषित __DC_OPP_DCN20_H__
#घोषणा __DC_OPP_DCN20_H__

#समावेश "dcn10/dcn10_opp.h"

#घोषणा TO_DCN20_OPP(opp)\
	container_of(opp, काष्ठा dcn20_opp, base)

#घोषणा OPP_SF(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा OPP_DPG_REG_LIST(id) \
	SRI(DPG_CONTROL, DPG, id), \
	SRI(DPG_DIMENSIONS, DPG, id), \
	SRI(DPG_OFFSET_SEGMENT, DPG, id), \
	SRI(DPG_COLOUR_B_CB, DPG, id), \
	SRI(DPG_COLOUR_G_Y, DPG, id), \
	SRI(DPG_COLOUR_R_CR, DPG, id), \
	SRI(DPG_RAMP_CONTROL, DPG, id), \
	SRI(DPG_STATUS, DPG, id)

#घोषणा OPP_REG_LIST_DCN20(id) \
	OPP_REG_LIST_DCN10(id), \
	OPP_DPG_REG_LIST(id), \
	SRI(FMT_422_CONTROL, FMT, id), \
	SRI(OPPBUF_CONTROL1, OPPBUF, id)

#घोषणा OPP_REG_VARIABLE_LIST_DCN2_0 \
	OPP_COMMON_REG_VARIABLE_LIST; \
	uपूर्णांक32_t FMT_422_CONTROL; \
	uपूर्णांक32_t DPG_CONTROL; \
	uपूर्णांक32_t DPG_DIMENSIONS; \
	uपूर्णांक32_t DPG_OFFSET_SEGMENT; \
	uपूर्णांक32_t DPG_COLOUR_B_CB; \
	uपूर्णांक32_t DPG_COLOUR_G_Y; \
	uपूर्णांक32_t DPG_COLOUR_R_CR; \
	uपूर्णांक32_t DPG_RAMP_CONTROL; \
	uपूर्णांक32_t DPG_STATUS

#घोषणा OPP_DPG_MASK_SH_LIST(mask_sh) \
	OPP_SF(DPG0_DPG_CONTROL, DPG_EN, mask_sh), \
	OPP_SF(DPG0_DPG_CONTROL, DPG_MODE, mask_sh), \
	OPP_SF(DPG0_DPG_CONTROL, DPG_DYNAMIC_RANGE, mask_sh), \
	OPP_SF(DPG0_DPG_CONTROL, DPG_BIT_DEPTH, mask_sh), \
	OPP_SF(DPG0_DPG_CONTROL, DPG_VRES, mask_sh), \
	OPP_SF(DPG0_DPG_CONTROL, DPG_HRES, mask_sh), \
	OPP_SF(DPG0_DPG_DIMENSIONS, DPG_ACTIVE_WIDTH, mask_sh), \
	OPP_SF(DPG0_DPG_DIMENSIONS, DPG_ACTIVE_HEIGHT, mask_sh), \
	OPP_SF(DPG0_DPG_OFFSET_SEGMENT, DPG_X_OFFSET, mask_sh), \
	OPP_SF(DPG0_DPG_OFFSET_SEGMENT, DPG_SEGMENT_WIDTH, mask_sh), \
	OPP_SF(DPG0_DPG_COLOUR_R_CR, DPG_COLOUR0_R_CR, mask_sh), \
	OPP_SF(DPG0_DPG_COLOUR_R_CR, DPG_COLOUR1_R_CR, mask_sh), \
	OPP_SF(DPG0_DPG_COLOUR_B_CB, DPG_COLOUR0_B_CB, mask_sh), \
	OPP_SF(DPG0_DPG_COLOUR_B_CB, DPG_COLOUR1_B_CB, mask_sh), \
	OPP_SF(DPG0_DPG_COLOUR_G_Y, DPG_COLOUR0_G_Y, mask_sh), \
	OPP_SF(DPG0_DPG_COLOUR_G_Y, DPG_COLOUR1_G_Y, mask_sh), \
	OPP_SF(DPG0_DPG_RAMP_CONTROL, DPG_RAMP0_OFFSET, mask_sh), \
	OPP_SF(DPG0_DPG_RAMP_CONTROL, DPG_INC0, mask_sh), \
	OPP_SF(DPG0_DPG_RAMP_CONTROL, DPG_INC1, mask_sh), \
	OPP_SF(DPG0_DPG_STATUS, DPG_DOUBLE_BUFFER_PENDING, mask_sh)

#घोषणा OPP_MASK_SH_LIST_DCN20(mask_sh) \
	OPP_MASK_SH_LIST_DCN(mask_sh), \
	OPP_DPG_MASK_SH_LIST(mask_sh), \
	OPP_SF(OPPBUF0_OPPBUF_CONTROL, OPPBUF_DISPLAY_SEGMENTATION, mask_sh),\
	OPP_SF(OPPBUF0_OPPBUF_CONTROL, OPPBUF_OVERLAP_PIXEL_NUM, mask_sh), \
	OPP_SF(FMT0_FMT_422_CONTROL, FMT_LEFT_EDGE_EXTRA_PIXEL_COUNT, mask_sh)

#घोषणा OPP_DCN20_REG_FIELD_LIST(type) \
	OPP_DCN10_REG_FIELD_LIST(type); \
	type FMT_LEFT_EDGE_EXTRA_PIXEL_COUNT; \
	type DPG_EN; \
	type DPG_MODE; \
	type DPG_DYNAMIC_RANGE; \
	type DPG_BIT_DEPTH; \
	type DPG_VRES; \
	type DPG_HRES; \
	type DPG_ACTIVE_WIDTH; \
	type DPG_ACTIVE_HEIGHT; \
	type DPG_X_OFFSET; \
	type DPG_SEGMENT_WIDTH; \
	type DPG_COLOUR0_R_CR; \
	type DPG_COLOUR1_R_CR; \
	type DPG_COLOUR0_B_CB; \
	type DPG_COLOUR1_B_CB; \
	type DPG_COLOUR0_G_Y; \
	type DPG_COLOUR1_G_Y; \
	type DPG_RAMP0_OFFSET; \
	type DPG_INC0; \
	type DPG_INC1; \
	type DPG_DOUBLE_BUFFER_PENDING

काष्ठा dcn20_opp_रेजिस्टरs अणु
	OPP_REG_VARIABLE_LIST_DCN2_0;
पूर्ण;

काष्ठा dcn20_opp_shअगरt अणु
	OPP_DCN20_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा dcn20_opp_mask अणु
	OPP_DCN20_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn20_opp अणु
	काष्ठा output_pixel_processor base;

	स्थिर काष्ठा dcn20_opp_रेजिस्टरs *regs;
	स्थिर काष्ठा dcn20_opp_shअगरt *opp_shअगरt;
	स्थिर काष्ठा dcn20_opp_mask *opp_mask;

	bool is_ग_लिखो_to_ram_a_safe;
पूर्ण;

व्योम dcn20_opp_स्थिरruct(काष्ठा dcn20_opp *oppn20,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn20_opp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn20_opp_shअगरt *opp_shअगरt,
	स्थिर काष्ठा dcn20_opp_mask *opp_mask);

व्योम opp2_set_disp_pattern_generator(
	काष्ठा output_pixel_processor *opp,
	क्रमागत controller_dp_test_pattern test_pattern,
	क्रमागत controller_dp_color_space color_space,
	क्रमागत dc_color_depth color_depth,
	स्थिर काष्ठा tg_color *solid_color,
	पूर्णांक width,
	पूर्णांक height,
	पूर्णांक offset);

व्योम opp2_program_dpg_dimensions(
		काष्ठा output_pixel_processor *opp,
		पूर्णांक width, पूर्णांक height);

bool opp2_dpg_is_blanked(काष्ठा output_pixel_processor *opp);

व्योम opp2_dpg_set_blank_color(
		काष्ठा output_pixel_processor *opp,
		स्थिर काष्ठा tg_color *color);

व्योम opp2_program_left_edge_extra_pixel (
		काष्ठा output_pixel_processor *opp,
		bool count);

#पूर्ण_अगर
