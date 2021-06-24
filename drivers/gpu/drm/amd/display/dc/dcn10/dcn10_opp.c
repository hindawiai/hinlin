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
#समावेश "dcn10_opp.h"
#समावेश "reg_helper.h"

#घोषणा REG(reg) \
	(oppn10->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	oppn10->opp_shअगरt->field_name, oppn10->opp_mask->field_name

#घोषणा CTX \
	oppn10->base.ctx


/************* FORMATTER ************/

/**
 *	set_truncation
 *	1) set truncation depth: 0 क्रम 18 bpp or 1 क्रम 24 bpp
 *	2) enable truncation
 *	3) HW हटाओ 12bit FMT support क्रम DCE11 घातer saving reason.
 */
अटल व्योम opp1_set_truncation(
		काष्ठा dcn10_opp *oppn10,
		स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_TRUNCATE_EN, params->flags.TRUNCATE_ENABLED,
		FMT_TRUNCATE_DEPTH, params->flags.TRUNCATE_DEPTH,
		FMT_TRUNCATE_MODE, params->flags.TRUNCATE_MODE);
पूर्ण

अटल व्योम opp1_set_spatial_dither(
	काष्ठा dcn10_opp *oppn10,
	स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	/*Disable spatial (अक्रमom) dithering*/
	REG_UPDATE_7(FMT_BIT_DEPTH_CONTROL,
			FMT_SPATIAL_DITHER_EN, 0,
			FMT_SPATIAL_DITHER_MODE, 0,
			FMT_SPATIAL_DITHER_DEPTH, 0,
			FMT_TEMPORAL_DITHER_EN, 0,
			FMT_HIGHPASS_RANDOM_ENABLE, 0,
			FMT_FRAME_RANDOM_ENABLE, 0,
			FMT_RGB_RANDOM_ENABLE, 0);


	/* only use FRAME_COUNTER_MAX अगर frameRanकरोm == 1*/
	अगर (params->flags.FRAME_RANDOM == 1) अणु
		अगर (params->flags.SPATIAL_DITHER_DEPTH == 0 || params->flags.SPATIAL_DITHER_DEPTH == 1) अणु
			REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 15,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 2);
		पूर्ण अन्यथा अगर (params->flags.SPATIAL_DITHER_DEPTH == 2) अणु
			REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 3,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 1);
		पूर्ण अन्यथा अणु
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		REG_UPDATE_2(FMT_CONTROL,
				FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 0,
				FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 0);
	पूर्ण

	/*Set seed क्रम अक्रमom values क्रम
	 * spatial dithering क्रम R,G,B channels*/

	REG_SET(FMT_DITHER_RAND_R_SEED, 0,
			FMT_RAND_R_SEED, params->r_seed_value);

	REG_SET(FMT_DITHER_RAND_G_SEED, 0,
			FMT_RAND_G_SEED, params->g_seed_value);

	REG_SET(FMT_DITHER_RAND_B_SEED, 0,
			FMT_RAND_B_SEED, params->b_seed_value);

	/* FMT_OFFSET_R_Cr  31:16 0x0 Setting the zero
	 * offset क्रम the R/Cr channel, lower 4LSB
	 * is क्रमced to zeros. Typically set to 0
	 * RGB and 0x80000 YCbCr.
	 */
	/* FMT_OFFSET_G_Y   31:16 0x0 Setting the zero
	 * offset क्रम the G/Y  channel, lower 4LSB is
	 * क्रमced to zeros. Typically set to 0 RGB
	 * and 0x80000 YCbCr.
	 */
	/* FMT_OFFSET_B_Cb  31:16 0x0 Setting the zero
	 * offset क्रम the B/Cb channel, lower 4LSB is
	 * क्रमced to zeros. Typically set to 0 RGB and
	 * 0x80000 YCbCr.
	 */

	REG_UPDATE_6(FMT_BIT_DEPTH_CONTROL,
			/*Enable spatial dithering*/
			FMT_SPATIAL_DITHER_EN, params->flags.SPATIAL_DITHER_ENABLED,
			/* Set spatial dithering mode
			 * (शेष is Seed patterrn AAAA...)
			 */
			FMT_SPATIAL_DITHER_MODE, params->flags.SPATIAL_DITHER_MODE,
			/*Set spatial dithering bit depth*/
			FMT_SPATIAL_DITHER_DEPTH, params->flags.SPATIAL_DITHER_DEPTH,
			/*Disable High pass filter*/
			FMT_HIGHPASS_RANDOM_ENABLE, params->flags.HIGHPASS_RANDOM,
			/*Reset only at startup*/
			FMT_FRAME_RANDOM_ENABLE, params->flags.FRAME_RANDOM,
			/*Set RGB data dithered with x^28+x^3+1*/
			FMT_RGB_RANDOM_ENABLE, params->flags.RGB_RANDOM);
पूर्ण

व्योम opp1_program_bit_depth_reduction(
	काष्ठा output_pixel_processor *opp,
	स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	काष्ठा dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	opp1_set_truncation(oppn10, params);
	opp1_set_spatial_dither(oppn10, params);
	/* TODO
	 * set_temporal_dither(oppn10, params);
	 */
पूर्ण

/**
 *	set_pixel_encoding
 *
 *	Set Pixel Encoding
 *		0: RGB 4:4:4 or YCbCr 4:4:4 or YOnly
 *		1: YCbCr 4:2:2
 */
अटल व्योम opp1_set_pixel_encoding(
	काष्ठा dcn10_opp *oppn10,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	चयन (params->pixel_encoding)	अणु

	हाल PIXEL_ENCODING_RGB:
	हाल PIXEL_ENCODING_YCBCR444:
		REG_UPDATE(FMT_CONTROL, FMT_PIXEL_ENCODING, 0);
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR422:
		REG_UPDATE_3(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 1,
				FMT_SUBSAMPLING_MODE, 2,
				FMT_CBCR_BIT_REDUCTION_BYPASS, 0);
		अवरोध;
	हाल PIXEL_ENCODING_YCBCR420:
		REG_UPDATE(FMT_CONTROL, FMT_PIXEL_ENCODING, 2);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 *	Set Clamping
 *	1) Set clamping क्रमmat based on bpc - 0 क्रम 6bpc (No clamping)
 *		1 क्रम 8 bpc
 *		2 क्रम 10 bpc
 *		3 क्रम 12 bpc
 *		7 क्रम programable
 *	2) Enable clamp अगर Limited range requested
 */
अटल व्योम opp1_set_clamping(
	काष्ठा dcn10_opp *oppn10,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	REG_UPDATE_2(FMT_CLAMP_CNTL,
			FMT_CLAMP_DATA_EN, 0,
			FMT_CLAMP_COLOR_FORMAT, 0);

	चयन (params->clamping_level) अणु
	हाल CLAMPING_FULL_RANGE:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 0);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_8BPC:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 1);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_10BPC:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 2);

		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_12BPC:
		REG_UPDATE_2(FMT_CLAMP_CNTL,
				FMT_CLAMP_DATA_EN, 1,
				FMT_CLAMP_COLOR_FORMAT, 3);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_PROGRAMMABLE:
		/* TODO */
	शेष:
		अवरोध;
	पूर्ण

पूर्ण

व्योम opp1_set_dyn_expansion(
	काष्ठा output_pixel_processor *opp,
	क्रमागत dc_color_space color_sp,
	क्रमागत dc_color_depth color_dpth,
	क्रमागत संकेत_type संकेत)
अणु
	काष्ठा dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
			FMT_DYNAMIC_EXP_EN, 0,
			FMT_DYNAMIC_EXP_MODE, 0);

	अगर (opp->dyn_expansion == DYN_EXPANSION_DISABLE)
		वापस;

	/*00 - 10-bit -> 12-bit dynamic expansion*/
	/*01 - 8-bit  -> 12-bit dynamic expansion*/
	अगर (संकेत == SIGNAL_TYPE_HDMI_TYPE_A ||
		संकेत == SIGNAL_TYPE_DISPLAY_PORT ||
		संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST ||
		संकेत == SIGNAL_TYPE_VIRTUAL) अणु
		चयन (color_dpth) अणु
		हाल COLOR_DEPTH_888:
			REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
				FMT_DYNAMIC_EXP_EN, 1,
				FMT_DYNAMIC_EXP_MODE, 1);
			अवरोध;
		हाल COLOR_DEPTH_101010:
			REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
				FMT_DYNAMIC_EXP_EN, 1,
				FMT_DYNAMIC_EXP_MODE, 0);
			अवरोध;
		हाल COLOR_DEPTH_121212:
			REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
				FMT_DYNAMIC_EXP_EN, 1,/*otherwise last two bits are zero*/
				FMT_DYNAMIC_EXP_MODE, 0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम opp1_program_clamping_and_pixel_encoding(
	काष्ठा output_pixel_processor *opp,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	काष्ठा dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	opp1_set_clamping(oppn10, params);
	opp1_set_pixel_encoding(oppn10, params);
पूर्ण

व्योम opp1_program_fmt(
	काष्ठा output_pixel_processor *opp,
	काष्ठा bit_depth_reduction_params *fmt_bit_depth,
	काष्ठा clamping_and_pixel_encoding_params *clamping)
अणु
	काष्ठा dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	अगर (clamping->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		REG_UPDATE(FMT_MAP420_MEMORY_CONTROL, FMT_MAP420MEM_PWR_FORCE, 0);

	/* dithering is affected by <CrtcSourceSelect>, hence should be
	 * programmed afterwards */
	opp1_program_bit_depth_reduction(
		opp,
		fmt_bit_depth);

	opp1_program_clamping_and_pixel_encoding(
		opp,
		clamping);

	वापस;
पूर्ण

व्योम opp1_program_stereo(
	काष्ठा output_pixel_processor *opp,
	bool enable,
	स्थिर काष्ठा dc_crtc_timing *timing)
अणु
	काष्ठा dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	uपूर्णांक32_t active_width = timing->h_addressable - timing->h_border_right - timing->h_border_right;
	uपूर्णांक32_t space1_size = timing->v_total - timing->v_addressable;
	/* TODO: confirm computation of space2_size */
	uपूर्णांक32_t space2_size = timing->v_total - timing->v_addressable;

	अगर (!enable) अणु
		active_width = 0;
		space1_size = 0;
		space2_size = 0;
	पूर्ण

	/* TODO: क्रम which हालs should FMT_STEREOSYNC_OVERRIDE be set? */
	REG_UPDATE(FMT_CONTROL, FMT_STEREOSYNC_OVERRIDE, 0);

	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_ACTIVE_WIDTH, active_width);

	/* Program OPPBUF_3D_VACT_SPACE1_SIZE and OPPBUF_VACT_SPACE2_SIZE रेजिस्टरs
	 * In 3D progressive frames, Vactive space happens only in between the 2 frames,
	 * so only need to program OPPBUF_3D_VACT_SPACE1_SIZE
	 * In 3D alternative frames, left and right frames, top and bottom field.
	 */
	अगर (timing->timing_3d_क्रमmat == TIMING_3D_FORMAT_FRAME_ALTERNATE)
		REG_UPDATE(OPPBUF_3D_PARAMETERS_0, OPPBUF_3D_VACT_SPACE2_SIZE, space2_size);
	अन्यथा
		REG_UPDATE(OPPBUF_3D_PARAMETERS_0, OPPBUF_3D_VACT_SPACE1_SIZE, space1_size);

	/* TODO: Is programming of OPPBUF_DUMMY_DATA_R/G/B needed? */
	/*
	REG_UPDATE(OPPBUF_3D_PARAMETERS_0,
			OPPBUF_DUMMY_DATA_R, data_r);
	REG_UPDATE(OPPBUF_3D_PARAMETERS_1,
			OPPBUF_DUMMY_DATA_G, data_g);
	REG_UPDATE(OPPBUF_3D_PARAMETERS_1,
			OPPBUF_DUMMY_DATA_B, _data_b);
	*/
पूर्ण

व्योम opp1_program_oppbuf(
	काष्ठा output_pixel_processor *opp,
	काष्ठा oppbuf_params *oppbuf)
अणु
	काष्ठा dcn10_opp *oppn10 = TO_DCN10_OPP(opp);

	/* Program the oppbuf active width to be the frame width from mpc */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_ACTIVE_WIDTH, oppbuf->active_width);

	/* Specअगरies the number of segments in multi-segment mode (DP-MSO operation)
	 * description  "In 1/2/4 segment mode, specअगरies the horizontal active width in pixels of the display panel.
	 * In 4 segment split left/right mode, specअगरies the horizontal 1/2 active width in pixels of the display panel.
	 * Used to determine segment boundaries in multi-segment mode. Used to determine the width of the vertical active space in 3D frame packed modes.
	 * OPPBUF_ACTIVE_WIDTH must be पूर्णांकeger भागisible by the total number of segments."
	 */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_DISPLAY_SEGMENTATION, oppbuf->mso_segmentation);

	/* description  "Specifies the number of overlap pixels (1-8 overlapping pixels supported), used in multi-segment mode (DP-MSO operation)" */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_OVERLAP_PIXEL_NUM, oppbuf->mso_overlap_pixel_num);

	/* description  "Specअगरies the number of बार a pixel is replicated (0-15 pixel replications supported).
	 * A value of 0 disables replication. The total number of बार a pixel is output is OPPBUF_PIXEL_REPETITION + 1."
	 */
	REG_UPDATE(OPPBUF_CONTROL, OPPBUF_PIXEL_REPETITION, oppbuf->pixel_repetition);

	/* Controls the number of padded pixels at the end of a segment */
	अगर (REG(OPPBUF_CONTROL1))
		REG_UPDATE(OPPBUF_CONTROL1, OPPBUF_NUM_SEGMENT_PADDED_PIXELS, oppbuf->num_segment_padded_pixels);
पूर्ण

व्योम opp1_pipe_घड़ी_control(काष्ठा output_pixel_processor *opp, bool enable)
अणु
	काष्ठा dcn10_opp *oppn10 = TO_DCN10_OPP(opp);
	uपूर्णांक32_t regval = enable ? 1 : 0;

	REG_UPDATE(OPP_PIPE_CONTROL, OPP_PIPE_CLOCK_EN, regval);
पूर्ण

/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

व्योम opp1_destroy(काष्ठा output_pixel_processor **opp)
अणु
	kमुक्त(TO_DCN10_OPP(*opp));
	*opp = शून्य;
पूर्ण

अटल स्थिर काष्ठा opp_funcs dcn10_opp_funcs = अणु
		.opp_set_dyn_expansion = opp1_set_dyn_expansion,
		.opp_program_fmt = opp1_program_fmt,
		.opp_program_bit_depth_reduction = opp1_program_bit_depth_reduction,
		.opp_program_stereo = opp1_program_stereo,
		.opp_pipe_घड़ी_control = opp1_pipe_घड़ी_control,
		.opp_set_disp_pattern_generator = शून्य,
		.opp_program_dpg_dimensions = शून्य,
		.dpg_is_blanked = शून्य,
		.opp_destroy = opp1_destroy
पूर्ण;

व्योम dcn10_opp_स्थिरruct(काष्ठा dcn10_opp *oppn10,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn10_opp_रेजिस्टरs *regs,
	स्थिर काष्ठा dcn10_opp_shअगरt *opp_shअगरt,
	स्थिर काष्ठा dcn10_opp_mask *opp_mask)
अणु

	oppn10->base.ctx = ctx;
	oppn10->base.inst = inst;
	oppn10->base.funcs = &dcn10_opp_funcs;

	oppn10->regs = regs;
	oppn10->opp_shअगरt = opp_shअगरt;
	oppn10->opp_mask = opp_mask;
पूर्ण
