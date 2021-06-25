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

#समावेश "dm_services.h"
#समावेश "dcn20_opp.h"
#समावेश "reg_helper.h"

#घोषणा REG(reg) \
	(oppn20->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	oppn20->opp_shअगरt->field_name, oppn20->opp_mask->field_name

#घोषणा CTX \
	oppn20->base.ctx


व्योम opp2_set_disp_pattern_generator(
		काष्ठा output_pixel_processor *opp,
		क्रमागत controller_dp_test_pattern test_pattern,
		क्रमागत controller_dp_color_space color_space,
		क्रमागत dc_color_depth color_depth,
		स्थिर काष्ठा tg_color *solid_color,
		पूर्णांक width,
		पूर्णांक height,
		पूर्णांक offset)
अणु
	काष्ठा dcn20_opp *oppn20 = TO_DCN20_OPP(opp);
	क्रमागत test_pattern_color_क्रमmat bit_depth;
	क्रमागत test_pattern_dyn_range dyn_range;
	क्रमागत test_pattern_mode mode;

	/* color ramp generator mixes 16-bits color */
	uपूर्णांक32_t src_bpc = 16;
	/* requested bpc */
	uपूर्णांक32_t dst_bpc;
	uपूर्णांक32_t index;
	/* RGB values of the color bars.
	 * Produce two RGB colors: RGB0 - white (all Fs)
	 * and RGB1 - black (all 0s)
	 * (three RGB components क्रम two colors)
	 */
	uपूर्णांक16_t src_color[6] = अणु0xFFFF, 0xFFFF, 0xFFFF, 0x0000,
						0x0000, 0x0000पूर्ण;
	/* dest color (converted to the specअगरied color क्रमmat) */
	uपूर्णांक16_t dst_color[6];
	uपूर्णांक32_t inc_base;

	/* translate to bit depth */
	चयन (color_depth) अणु
	हाल COLOR_DEPTH_666:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_6;
	अवरोध;
	हाल COLOR_DEPTH_888:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_8;
	अवरोध;
	हाल COLOR_DEPTH_101010:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_10;
	अवरोध;
	हाल COLOR_DEPTH_121212:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_12;
	अवरोध;
	शेष:
		bit_depth = TEST_PATTERN_COLOR_FORMAT_BPC_8;
	अवरोध;
	पूर्ण

	/* set DPG dimentions */
	REG_SET_2(DPG_DIMENSIONS, 0,
		DPG_ACTIVE_WIDTH, width,
		DPG_ACTIVE_HEIGHT, height);

	/* set DPG offset */
	REG_SET_2(DPG_OFFSET_SEGMENT, 0,
		DPG_X_OFFSET, offset,
		DPG_SEGMENT_WIDTH, 0);

	चयन (test_pattern) अणु
	हाल CONTROLLER_DP_TEST_PATTERN_COLORSQUARES:
	हाल CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA:
	अणु
		dyn_range = (test_pattern ==
				CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA ?
				TEST_PATTERN_DYN_RANGE_CEA :
				TEST_PATTERN_DYN_RANGE_VESA);

		चयन (color_space) अणु
		हाल CONTROLLER_DP_COLOR_SPACE_YCBCR601:
			mode = TEST_PATTERN_MODE_COLORSQUARES_YCBCR601;
		अवरोध;
		हाल CONTROLLER_DP_COLOR_SPACE_YCBCR709:
			mode = TEST_PATTERN_MODE_COLORSQUARES_YCBCR709;
		अवरोध;
		हाल CONTROLLER_DP_COLOR_SPACE_RGB:
		शेष:
			mode = TEST_PATTERN_MODE_COLORSQUARES_RGB;
		अवरोध;
		पूर्ण

		REG_UPDATE_6(DPG_CONTROL,
			DPG_EN, 1,
			DPG_MODE, mode,
			DPG_DYNAMIC_RANGE, dyn_range,
			DPG_BIT_DEPTH, bit_depth,
			DPG_VRES, 6,
			DPG_HRES, 6);
	पूर्ण
	अवरोध;

	हाल CONTROLLER_DP_TEST_PATTERN_VERTICALBARS:
	हाल CONTROLLER_DP_TEST_PATTERN_HORIZONTALBARS:
	अणु
		mode = (test_pattern ==
			CONTROLLER_DP_TEST_PATTERN_VERTICALBARS ?
			TEST_PATTERN_MODE_VERTICALBARS :
			TEST_PATTERN_MODE_HORIZONTALBARS);

		चयन (bit_depth) अणु
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_6:
			dst_bpc = 6;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
			dst_bpc = 8;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
			dst_bpc = 10;
		अवरोध;
		शेष:
			dst_bpc = 8;
		अवरोध;
		पूर्ण

		/* adjust color to the required colorFormat */
		क्रम (index = 0; index < 6; index++) अणु
			/* dst = 2^dstBpc * src / 2^srcBpc = src >>
			 * (srcBpc - dstBpc);
			 */
			dst_color[index] =
				src_color[index] >> (src_bpc - dst_bpc);
		/* DPG_COLOUR रेजिस्टरs are 16-bit MSB aligned value with bits 3:0 hardwired to ZERO.
		 * XXXXXXXXXX000000 क्रम 10 bit,
		 * XXXXXXXX00000000 क्रम 8 bit,
		 * XXXXXX0000000000 क्रम 6 bits
		 */
			dst_color[index] <<= (16 - dst_bpc);
		पूर्ण

		REG_SET_2(DPG_COLOUR_R_CR, 0,
				DPG_COLOUR1_R_CR, dst_color[0],
				DPG_COLOUR0_R_CR, dst_color[3]);
		REG_SET_2(DPG_COLOUR_G_Y, 0,
				DPG_COLOUR1_G_Y, dst_color[1],
				DPG_COLOUR0_G_Y, dst_color[4]);
		REG_SET_2(DPG_COLOUR_B_CB, 0,
				DPG_COLOUR1_B_CB, dst_color[2],
				DPG_COLOUR0_B_CB, dst_color[5]);

		/* enable test pattern */
		REG_UPDATE_6(DPG_CONTROL,
			DPG_EN, 1,
			DPG_MODE, mode,
			DPG_DYNAMIC_RANGE, 0,
			DPG_BIT_DEPTH, bit_depth,
			DPG_VRES, 0,
			DPG_HRES, 0);
	पूर्ण
	अवरोध;

	हाल CONTROLLER_DP_TEST_PATTERN_COLORRAMP:
	अणु
		mode = (bit_depth ==
			TEST_PATTERN_COLOR_FORMAT_BPC_10 ?
			TEST_PATTERN_MODE_DUALRAMP_RGB :
			TEST_PATTERN_MODE_SINGLERAMP_RGB);

		चयन (bit_depth) अणु
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_6:
			dst_bpc = 6;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
			dst_bpc = 8;
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
			dst_bpc = 10;
		अवरोध;
		शेष:
			dst_bpc = 8;
		अवरोध;
		पूर्ण

		/* increment क्रम the first ramp क्रम one color gradation
		 * 1 gradation क्रम 6-bit color is 2^10
		 * gradations in 16-bit color
		 */
		inc_base = (src_bpc - dst_bpc);

		चयन (bit_depth) अणु
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_6:
		अणु
			REG_SET_3(DPG_RAMP_CONTROL, 0,
				DPG_RAMP0_OFFSET, 0,
				DPG_INC0, inc_base,
				DPG_INC1, 0);
			REG_UPDATE_2(DPG_CONTROL,
				DPG_VRES, 6,
				DPG_HRES, 6);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_8:
		अणु
			REG_SET_3(DPG_RAMP_CONTROL, 0,
				DPG_RAMP0_OFFSET, 0,
				DPG_INC0, inc_base,
				DPG_INC1, 0);
			REG_UPDATE_2(DPG_CONTROL,
				DPG_VRES, 6,
				DPG_HRES, 8);
		पूर्ण
		अवरोध;
		हाल TEST_PATTERN_COLOR_FORMAT_BPC_10:
		अणु
			REG_SET_3(DPG_RAMP_CONTROL, 0,
				DPG_RAMP0_OFFSET, 384 << 6,
				DPG_INC0, inc_base,
				DPG_INC1, inc_base + 2);
			REG_UPDATE_2(DPG_CONTROL,
				DPG_VRES, 5,
				DPG_HRES, 8);
		पूर्ण
		अवरोध;
		शेष:
		अवरोध;
		पूर्ण

		/* enable test pattern */
		REG_UPDATE_4(DPG_CONTROL,
			DPG_EN, 1,
			DPG_MODE, mode,
			DPG_DYNAMIC_RANGE, 0,
			DPG_BIT_DEPTH, bit_depth);
	पूर्ण
	अवरोध;
	हाल CONTROLLER_DP_TEST_PATTERN_VIDEOMODE:
	अणु
		REG_WRITE(DPG_CONTROL, 0);
		REG_WRITE(DPG_COLOUR_R_CR, 0);
		REG_WRITE(DPG_COLOUR_G_Y, 0);
		REG_WRITE(DPG_COLOUR_B_CB, 0);
		REG_WRITE(DPG_RAMP_CONTROL, 0);
	पूर्ण
	अवरोध;
	हाल CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR:
	अणु
		opp2_dpg_set_blank_color(opp, solid_color);
		REG_UPDATE_2(DPG_CONTROL,
				DPG_EN, 1,
				DPG_MODE, TEST_PATTERN_MODE_HORIZONTALBARS);

		REG_SET_2(DPG_DIMENSIONS, 0,
				DPG_ACTIVE_WIDTH, width,
				DPG_ACTIVE_HEIGHT, height);
	पूर्ण
	अवरोध;
	शेष:
		अवरोध;

	पूर्ण
पूर्ण

व्योम opp2_program_dpg_dimensions(
		काष्ठा output_pixel_processor *opp,
		पूर्णांक width, पूर्णांक height)
अणु
	काष्ठा dcn20_opp *oppn20 = TO_DCN20_OPP(opp);

	REG_SET_2(DPG_DIMENSIONS, 0,
		DPG_ACTIVE_WIDTH, width,
		DPG_ACTIVE_HEIGHT, height);
पूर्ण

व्योम opp2_dpg_set_blank_color(
		काष्ठा output_pixel_processor *opp,
		स्थिर काष्ठा tg_color *color)
अणु
	काष्ठा dcn20_opp *oppn20 = TO_DCN20_OPP(opp);

	/* 16-bit MSB aligned value. Bits 3:0 of this field are hardwired to ZERO */
	ASSERT(color);
	REG_SET_2(DPG_COLOUR_B_CB, 0,
			DPG_COLOUR1_B_CB, color->color_b_cb << 6,
			DPG_COLOUR0_B_CB, color->color_b_cb << 6);
	REG_SET_2(DPG_COLOUR_G_Y, 0,
			DPG_COLOUR1_G_Y, color->color_g_y << 6,
			DPG_COLOUR0_G_Y, color->color_g_y << 6);
	REG_SET_2(DPG_COLOUR_R_CR, 0,
			DPG_COLOUR1_R_CR, color->color_r_cr << 6,
			DPG_COLOUR0_R_CR, color->color_r_cr << 6);
पूर्ण

bool opp2_dpg_is_blanked(काष्ठा output_pixel_processor *opp)
अणु
	काष्ठा dcn20_opp *oppn20 = TO_DCN20_OPP(opp);
	uपूर्णांक32_t dpg_en, dpg_mode;
	uपूर्णांक32_t द्विगुन_buffer_pending;

	REG_GET_2(DPG_CONTROL,
			DPG_EN, &dpg_en,
			DPG_MODE, &dpg_mode);

	REG_GET(DPG_STATUS,
			DPG_DOUBLE_BUFFER_PENDING, &द्विगुन_buffer_pending);

	वापस (dpg_en == 1) &&
		(द्विगुन_buffer_pending == 0);
पूर्ण

व्योम opp2_program_left_edge_extra_pixel (
		काष्ठा output_pixel_processor *opp,
		bool count)
अणु
	काष्ठा dcn20_opp *oppn20 = TO_DCN20_OPP(opp);

	/* Specअगरies the number of extra left edge pixels that are supplied to
	 * the 422 horizontal chroma sub-sample filter.
	 * Note that when left edge pixel is not "0", fmt pixel encoding can be in either 420 or 422 mode
	 * */
	REG_UPDATE(FMT_422_CONTROL, FMT_LEFT_EDGE_EXTRA_PIXEL_COUNT, count);
पूर्ण

/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

अटल काष्ठा opp_funcs dcn20_opp_funcs = अणु
		.opp_set_dyn_expansion = opp1_set_dyn_expansion,
		.opp_program_fmt = opp1_program_fmt,
		.opp_program_bit_depth_reduction = opp1_program_bit_depth_reduction,
		.opp_program_stereo = opp1_program_stereo,
		.opp_pipe_घड़ी_control = opp1_pipe_घड़ी_control,
		.opp_set_disp_pattern_generator = opp2_set_disp_pattern_generator,
		.opp_program_dpg_dimensions = opp2_program_dpg_dimensions,
		.dpg_is_blanked = opp2_dpg_is_blanked,
		.opp_dpg_set_blank_color = opp2_dpg_set_blank_color,
		.opp_destroy = opp1_destroy,
		.opp_program_left_edge_extra_pixel = opp2_program_left_edge_extra_pixel,
पूर्ण;

व्योम dcn20_opp_स्थिरruct(काष्ठा dcn20_opp *oppn20,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn20_opp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn20_opp_shअगरt *opp_shअगरt,
	स्थिर काष्ठा dcn20_opp_mask *opp_mask)
अणु
	oppn20->base.ctx = ctx;
	oppn20->base.inst = inst;
	oppn20->base.funcs = &dcn20_opp_funcs;

	oppn20->regs = regs;
	oppn20->opp_shअगरt = opp_shअगरt;
	oppn20->opp_mask = opp_mask;
पूर्ण

