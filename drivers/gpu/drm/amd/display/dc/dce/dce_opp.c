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
#समावेश "basics/conversion.h"

#समावेश "dce_opp.h"

#समावेश "reg_helper.h"

#घोषणा REG(reg)\
	(opp110->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	opp110->opp_shअगरt->field_name, opp110->opp_mask->field_name

#घोषणा CTX \
	opp110->base.ctx

क्रमागत अणु
	MAX_PWL_ENTRY = 128,
	MAX_REGIONS_NUMBER = 16
पूर्ण;

क्रमागत अणु
	MAX_LUT_ENTRY = 256,
	MAX_NUMBER_OF_ENTRIES = 256
पूर्ण;


क्रमागत अणु
	OUTPUT_CSC_MATRIX_SIZE = 12
पूर्ण;






















/*
 *****************************************************************************
 *  Function: regamma_config_regions_and_segments
 *
 *     build regamma curve by using predefined hw poपूर्णांकs
 *     uses पूर्णांकerface parameters ,like EDID coeff.
 *
 * @param   : parameters   पूर्णांकerface parameters
 *  @वापस व्योम
 *
 *  @note
 *
 *  @see
 *
 *****************************************************************************
 */



/*
 *	set_truncation
 *	1) set truncation depth: 0 क्रम 18 bpp or 1 क्रम 24 bpp
 *	2) enable truncation
 *	3) HW हटाओ 12bit FMT support क्रम DCE11 घातer saving reason.
 */
अटल व्योम set_truncation(
		काष्ठा dce110_opp *opp110,
		स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	/*Disable truncation*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
			FMT_TRUNCATE_EN, 0,
			FMT_TRUNCATE_DEPTH, 0,
			FMT_TRUNCATE_MODE, 0);


	अगर (params->pixel_encoding == PIXEL_ENCODING_YCBCR422) अणु
		/*  8bpc trunc on YCbCr422*/
		अगर (params->flags.TRUNCATE_DEPTH == 1)
			REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
					FMT_TRUNCATE_EN, 1,
					FMT_TRUNCATE_DEPTH, 1,
					FMT_TRUNCATE_MODE, 0);
		अन्यथा अगर (params->flags.TRUNCATE_DEPTH == 2)
			/*  10bpc trunc on YCbCr422*/
			REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
					FMT_TRUNCATE_EN, 1,
					FMT_TRUNCATE_DEPTH, 2,
					FMT_TRUNCATE_MODE, 0);
		वापस;
	पूर्ण
	/* on other क्रमmat-to करो */
	अगर (params->flags.TRUNCATE_ENABLED == 0)
		वापस;
	/*Set truncation depth and Enable truncation*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
				FMT_TRUNCATE_EN, 1,
				FMT_TRUNCATE_DEPTH,
				params->flags.TRUNCATE_DEPTH,
				FMT_TRUNCATE_MODE,
				params->flags.TRUNCATE_MODE);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
/*
 *	dce60_set_truncation
 *	1) set truncation depth: 0 क्रम 18 bpp or 1 क्रम 24 bpp
 *	2) enable truncation
 *	3) HW हटाओ 12bit FMT support क्रम DCE11 घातer saving reason.
 */
अटल व्योम dce60_set_truncation(
		काष्ठा dce110_opp *opp110,
		स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	/* DCE6 has no FMT_TRUNCATE_MODE bit in FMT_BIT_DEPTH_CONTROL reg */

	/*Disable truncation*/
	REG_UPDATE_2(FMT_BIT_DEPTH_CONTROL,
			FMT_TRUNCATE_EN, 0,
			FMT_TRUNCATE_DEPTH, 0);

	अगर (params->pixel_encoding == PIXEL_ENCODING_YCBCR422) अणु
		/*  8bpc trunc on YCbCr422*/
		अगर (params->flags.TRUNCATE_DEPTH == 1)
			REG_UPDATE_2(FMT_BIT_DEPTH_CONTROL,
					FMT_TRUNCATE_EN, 1,
					FMT_TRUNCATE_DEPTH, 1);
		अन्यथा अगर (params->flags.TRUNCATE_DEPTH == 2)
			/*  10bpc trunc on YCbCr422*/
			REG_UPDATE_2(FMT_BIT_DEPTH_CONTROL,
					FMT_TRUNCATE_EN, 1,
					FMT_TRUNCATE_DEPTH, 2);
		वापस;
	पूर्ण
	/* on other क्रमmat-to करो */
	अगर (params->flags.TRUNCATE_ENABLED == 0)
		वापस;
	/*Set truncation depth and Enable truncation*/
	REG_UPDATE_2(FMT_BIT_DEPTH_CONTROL,
				FMT_TRUNCATE_EN, 1,
				FMT_TRUNCATE_DEPTH,
				params->flags.TRUNCATE_DEPTH);
पूर्ण
#पूर्ण_अगर

/*
 *	set_spatial_dither
 *	1) set spatial dithering mode: pattern of seed
 *	2) set spatial dithering depth: 0 क्रम 18bpp or 1 क्रम 24bpp
 *	3) set अक्रमom seed
 *	4) set अक्रमom mode
 *		lfsr is reset every frame or not reset
 *		RGB dithering method
 *		0: RGB data are all dithered with x^28+x^3+1
 *		1: R data is dithered with x^28+x^3+1
 *		G data is dithered with x^28+X^9+1
 *		B data is dithered with x^28+x^13+1
 *		enable high pass filter or not
 *	5) enable spatical dithering
 */
अटल व्योम set_spatial_dither(
	काष्ठा dce110_opp *opp110,
	स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	/*Disable spatial (अक्रमom) dithering*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_SPATIAL_DITHER_EN, 0,
		FMT_SPATIAL_DITHER_DEPTH, 0,
		FMT_SPATIAL_DITHER_MODE, 0);

	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_HIGHPASS_RANDOM_ENABLE, 0,
		FMT_FRAME_RANDOM_ENABLE, 0,
		FMT_RGB_RANDOM_ENABLE, 0);

	REG_UPDATE(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_EN, 0);

	अगर (params->flags.SPATIAL_DITHER_ENABLED == 0)
		वापस;

	/* only use FRAME_COUNTER_MAX अगर frameRanकरोm == 1*/

	अगर (opp110->opp_mask->FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX &&
			opp110->opp_mask->FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP) अणु
		अगर (params->flags.FRAME_RANDOM == 1) अणु
			अगर (params->flags.SPATIAL_DITHER_DEPTH == 0 ||
			params->flags.SPATIAL_DITHER_DEPTH == 1) अणु
				REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 15,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 2);
			पूर्ण अन्यथा अगर (params->flags.SPATIAL_DITHER_DEPTH == 2) अणु
				REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 3,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 1);
			पूर्ण अन्यथा
				वापस;
		पूर्ण अन्यथा अणु
			REG_UPDATE_2(FMT_CONTROL,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_MAX, 0,
					FMT_SPATIAL_DITHER_FRAME_COUNTER_BIT_SWAP, 0);
		पूर्ण
	पूर्ण
	/* Set seed क्रम अक्रमom values क्रम
	 * spatial dithering क्रम R,G,B channels
	 */
	REG_UPDATE(FMT_DITHER_RAND_R_SEED,
			FMT_RAND_R_SEED, params->r_seed_value);

	REG_UPDATE(FMT_DITHER_RAND_G_SEED,
			FMT_RAND_G_SEED, params->g_seed_value);

	REG_UPDATE(FMT_DITHER_RAND_B_SEED,
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

	/* Disable High pass filter
	 * Reset only at startup
	 * Set RGB data dithered with x^28+x^3+1
	 */
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_HIGHPASS_RANDOM_ENABLE, params->flags.HIGHPASS_RANDOM,
		FMT_FRAME_RANDOM_ENABLE, params->flags.FRAME_RANDOM,
		FMT_RGB_RANDOM_ENABLE, params->flags.RGB_RANDOM);

	/* Set spatial dithering bit depth
	 * Set spatial dithering mode
	 * (शेष is Seed patterrn AAAA...)
	 * Enable spatial dithering
	 */
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_SPATIAL_DITHER_DEPTH, params->flags.SPATIAL_DITHER_DEPTH,
		FMT_SPATIAL_DITHER_MODE, params->flags.SPATIAL_DITHER_MODE,
		FMT_SPATIAL_DITHER_EN, 1);
पूर्ण

/*
 *	SetTemporalDither (Frame Modulation)
 *	1) set temporal dither depth
 *	2) select pattern: from hard-coded pattern or programmable pattern
 *	3) select optimized strips क्रम BGR or RGB LCD sub-pixel
 *	4) set s matrix
 *	5) set t matrix
 *	6) set grey level क्रम 0.25, 0.5, 0.75
 *	7) enable temporal dithering
 */

अटल व्योम set_temporal_dither(
	काष्ठा dce110_opp *opp110,
	स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	/*Disable temporal (frame modulation) dithering first*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_EN, 0,
		FMT_TEMPORAL_DITHER_RESET, 0,
		FMT_TEMPORAL_DITHER_OFFSET, 0);

	REG_UPDATE_2(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_DEPTH, 0,
		FMT_TEMPORAL_LEVEL, 0);

	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_25FRC_SEL, 0,
		FMT_50FRC_SEL, 0,
		FMT_75FRC_SEL, 0);

	/* no 10bpc dither on DCE11*/
	अगर (params->flags.FRAME_MODULATION_ENABLED == 0 ||
		params->flags.FRAME_MODULATION_DEPTH == 2)
		वापस;

	/* Set temporal dithering depth*/
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_DEPTH, params->flags.FRAME_MODULATION_DEPTH,
		FMT_TEMPORAL_DITHER_RESET, 0,
		FMT_TEMPORAL_DITHER_OFFSET, 0);

	/*Select legacy pattern based on FRC and Temporal level*/
	अगर (REG(FMT_TEMPORAL_DITHER_PATTERN_CONTROL)) अणु
		REG_WRITE(FMT_TEMPORAL_DITHER_PATTERN_CONTROL, 0);
		/*Set s matrix*/
		REG_WRITE(FMT_TEMPORAL_DITHER_PROGRAMMABLE_PATTERN_S_MATRIX, 0);
		/*Set t matrix*/
		REG_WRITE(FMT_TEMPORAL_DITHER_PROGRAMMABLE_PATTERN_T_MATRIX, 0);
	पूर्ण

	/*Select patterns क्रम 0.25, 0.5 and 0.75 grey level*/
	REG_UPDATE(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_LEVEL, params->flags.TEMPORAL_LEVEL);

	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_25FRC_SEL, params->flags.FRC25,
		FMT_50FRC_SEL, params->flags.FRC50,
		FMT_75FRC_SEL, params->flags.FRC75);

	/*Enable bit reduction by temporal (frame modulation) dithering*/
	REG_UPDATE(FMT_BIT_DEPTH_CONTROL,
		FMT_TEMPORAL_DITHER_EN, 1);
पूर्ण

/*
 *	Set Clamping
 *	1) Set clamping क्रमmat based on bpc - 0 क्रम 6bpc (No clamping)
 *		1 क्रम 8 bpc
 *		2 क्रम 10 bpc
 *		3 क्रम 12 bpc
 *		7 क्रम programable
 *	2) Enable clamp अगर Limited range requested
 */
व्योम dce110_opp_set_clamping(
	काष्ठा dce110_opp *opp110,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	REG_SET_2(FMT_CLAMP_CNTL, 0,
		FMT_CLAMP_DATA_EN, 0,
		FMT_CLAMP_COLOR_FORMAT, 0);

	चयन (params->clamping_level) अणु
	हाल CLAMPING_FULL_RANGE:
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_8BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 1);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_10BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 2);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_12BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 3);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_PROGRAMMABLE:
		/*Set clamp control*/
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 7);

		/*set the शेषs*/
		REG_SET_2(FMT_CLAMP_COMPONENT_R, 0,
			FMT_CLAMP_LOWER_R, 0x10,
			FMT_CLAMP_UPPER_R, 0xFEF);

		REG_SET_2(FMT_CLAMP_COMPONENT_G, 0,
			FMT_CLAMP_LOWER_G, 0x10,
			FMT_CLAMP_UPPER_G, 0xFEF);

		REG_SET_2(FMT_CLAMP_COMPONENT_B, 0,
			FMT_CLAMP_LOWER_B, 0x10,
			FMT_CLAMP_UPPER_B, 0xFEF);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
/*
 *	Set Clamping क्रम DCE6 parts
 *	1) Set clamping क्रमmat based on bpc - 0 क्रम 6bpc (No clamping)
 *		1 क्रम 8 bpc
 *		2 क्रम 10 bpc
 *		3 क्रम 12 bpc
 *		7 क्रम programable
 *	2) Enable clamp अगर Limited range requested
 */
अटल व्योम dce60_opp_set_clamping(
	काष्ठा dce110_opp *opp110,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	REG_SET_2(FMT_CLAMP_CNTL, 0,
		FMT_CLAMP_DATA_EN, 0,
		FMT_CLAMP_COLOR_FORMAT, 0);

	चयन (params->clamping_level) अणु
	हाल CLAMPING_FULL_RANGE:
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_8BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 1);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_10BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 2);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_12BPC:
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 3);
		अवरोध;
	हाल CLAMPING_LIMITED_RANGE_PROGRAMMABLE:
		/*Set clamp control*/
		REG_SET_2(FMT_CLAMP_CNTL, 0,
			FMT_CLAMP_DATA_EN, 1,
			FMT_CLAMP_COLOR_FORMAT, 7);

		/* DCE6 करोes have FMT_CLAMP_COMPONENT_अणुR,G,Bपूर्ण रेजिस्टरs */

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 *	set_pixel_encoding
 *
 *	Set Pixel Encoding
 *		0: RGB 4:4:4 or YCbCr 4:4:4 or YOnly
 *		1: YCbCr 4:2:2
 */
अटल व्योम set_pixel_encoding(
	काष्ठा dce110_opp *opp110,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	अगर (opp110->opp_mask->FMT_CBCR_BIT_REDUCTION_BYPASS)
		REG_UPDATE_3(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 0,
				FMT_SUBSAMPLING_MODE, 0,
				FMT_CBCR_BIT_REDUCTION_BYPASS, 0);
	अन्यथा
		REG_UPDATE_2(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 0,
				FMT_SUBSAMPLING_MODE, 0);

	अगर (params->pixel_encoding == PIXEL_ENCODING_YCBCR422) अणु
		REG_UPDATE_2(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 1,
				FMT_SUBSAMPLING_ORDER, 0);
	पूर्ण
	अगर (params->pixel_encoding == PIXEL_ENCODING_YCBCR420) अणु
		REG_UPDATE_3(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 2,
				FMT_SUBSAMPLING_MODE, 2,
				FMT_CBCR_BIT_REDUCTION_BYPASS, 1);
	पूर्ण

पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
/*
 *	dce60_set_pixel_encoding
 *	DCE6 has no FMT_SUBSAMPLING_अणुMODE,ORDERपूर्ण bits in FMT_CONTROL reg
 *	Set Pixel Encoding
 *		0: RGB 4:4:4 or YCbCr 4:4:4 or YOnly
 *		1: YCbCr 4:2:2
 */
अटल व्योम dce60_set_pixel_encoding(
	काष्ठा dce110_opp *opp110,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	अगर (opp110->opp_mask->FMT_CBCR_BIT_REDUCTION_BYPASS)
		REG_UPDATE_2(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 0,
				FMT_CBCR_BIT_REDUCTION_BYPASS, 0);
	अन्यथा
		REG_UPDATE(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 0);

	अगर (params->pixel_encoding == PIXEL_ENCODING_YCBCR422) अणु
		REG_UPDATE(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 1);
	पूर्ण
	अगर (params->pixel_encoding == PIXEL_ENCODING_YCBCR420) अणु
		REG_UPDATE_2(FMT_CONTROL,
				FMT_PIXEL_ENCODING, 2,
				FMT_CBCR_BIT_REDUCTION_BYPASS, 1);
	पूर्ण

पूर्ण
#पूर्ण_अगर

व्योम dce110_opp_program_bit_depth_reduction(
	काष्ठा output_pixel_processor *opp,
	स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	काष्ठा dce110_opp *opp110 = TO_DCE110_OPP(opp);

	set_truncation(opp110, params);
	set_spatial_dither(opp110, params);
	set_temporal_dither(opp110, params);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_opp_program_bit_depth_reduction(
	काष्ठा output_pixel_processor *opp,
	स्थिर काष्ठा bit_depth_reduction_params *params)
अणु
	काष्ठा dce110_opp *opp110 = TO_DCE110_OPP(opp);

	dce60_set_truncation(opp110, params);
	set_spatial_dither(opp110, params);
	set_temporal_dither(opp110, params);
पूर्ण
#पूर्ण_अगर

व्योम dce110_opp_program_clamping_and_pixel_encoding(
	काष्ठा output_pixel_processor *opp,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	काष्ठा dce110_opp *opp110 = TO_DCE110_OPP(opp);

	dce110_opp_set_clamping(opp110, params);
	set_pixel_encoding(opp110, params);
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_opp_program_clamping_and_pixel_encoding(
	काष्ठा output_pixel_processor *opp,
	स्थिर काष्ठा clamping_and_pixel_encoding_params *params)
अणु
	काष्ठा dce110_opp *opp110 = TO_DCE110_OPP(opp);

	dce60_opp_set_clamping(opp110, params);
	dce60_set_pixel_encoding(opp110, params);
पूर्ण
#पूर्ण_अगर


अटल व्योम program_क्रमmatter_420_memory(काष्ठा output_pixel_processor *opp)
अणु
	काष्ठा dce110_opp *opp110 = TO_DCE110_OPP(opp);
	uपूर्णांक32_t fmt_mem_cntl_value;

	/* Program source select*/
	/* Use HW शेष source select क्रम FMT_MEMORYx_CONTROL */
	/* Use that value क्रम FMT_SRC_SELECT as well*/
	REG_GET(CONTROL,
			FMT420_MEM0_SOURCE_SEL, &fmt_mem_cntl_value);

	REG_UPDATE(FMT_CONTROL,
			FMT_SRC_SELECT, fmt_mem_cntl_value);

	/* Turn on the memory */
	REG_UPDATE(CONTROL,
			FMT420_MEM0_PWR_FORCE, 0);
पूर्ण

व्योम dce110_opp_set_dyn_expansion(
	काष्ठा output_pixel_processor *opp,
	क्रमागत dc_color_space color_sp,
	क्रमागत dc_color_depth color_dpth,
	क्रमागत संकेत_type संकेत)
अणु
	काष्ठा dce110_opp *opp110 = TO_DCE110_OPP(opp);

	REG_UPDATE_2(FMT_DYNAMIC_EXP_CNTL,
			FMT_DYNAMIC_EXP_EN, 0,
			FMT_DYNAMIC_EXP_MODE, 0);

	/*00 - 10-bit -> 12-bit dynamic expansion*/
	/*01 - 8-bit  -> 12-bit dynamic expansion*/
	अगर (संकेत == SIGNAL_TYPE_HDMI_TYPE_A ||
		संकेत == SIGNAL_TYPE_DISPLAY_PORT ||
		संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
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
			REG_UPDATE_2(
				FMT_DYNAMIC_EXP_CNTL,
				FMT_DYNAMIC_EXP_EN, 1,/*otherwise last two bits are zero*/
				FMT_DYNAMIC_EXP_MODE, 0);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम program_क्रमmatter_reset_dig_resync_fअगरo(काष्ठा output_pixel_processor *opp)
अणु
	काष्ठा dce110_opp *opp110 = TO_DCE110_OPP(opp);

	/* clear previous phase lock status*/
	REG_UPDATE(FMT_CONTROL,
			FMT_420_PIXEL_PHASE_LOCKED_CLEAR, 1);

	/* poll until FMT_420_PIXEL_PHASE_LOCKED become 1*/
	REG_WAIT(FMT_CONTROL, FMT_420_PIXEL_PHASE_LOCKED, 1, 10, 10);

पूर्ण

व्योम dce110_opp_program_fmt(
	काष्ठा output_pixel_processor *opp,
	काष्ठा bit_depth_reduction_params *fmt_bit_depth,
	काष्ठा clamping_and_pixel_encoding_params *clamping)
अणु
	/* dithering is affected by <CrtcSourceSelect>, hence should be
	 * programmed afterwards */

	अगर (clamping->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		program_क्रमmatter_420_memory(opp);

	dce110_opp_program_bit_depth_reduction(
		opp,
		fmt_bit_depth);

	dce110_opp_program_clamping_and_pixel_encoding(
		opp,
		clamping);

	अगर (clamping->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		program_क्रमmatter_reset_dig_resync_fअगरo(opp);

	वापस;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल व्योम dce60_opp_program_fmt(
	काष्ठा output_pixel_processor *opp,
	काष्ठा bit_depth_reduction_params *fmt_bit_depth,
	काष्ठा clamping_and_pixel_encoding_params *clamping)
अणु
	/* dithering is affected by <CrtcSourceSelect>, hence should be
	 * programmed afterwards */

	अगर (clamping->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		program_क्रमmatter_420_memory(opp);

	dce60_opp_program_bit_depth_reduction(
		opp,
		fmt_bit_depth);

	dce60_opp_program_clamping_and_pixel_encoding(
		opp,
		clamping);

	अगर (clamping->pixel_encoding == PIXEL_ENCODING_YCBCR420)
		program_क्रमmatter_reset_dig_resync_fअगरo(opp);

	वापस;
पूर्ण
#पूर्ण_अगर



/*****************************************/
/* Conकाष्ठाor, Deकाष्ठाor               */
/*****************************************/

अटल स्थिर काष्ठा opp_funcs funcs = अणु
	.opp_set_dyn_expansion = dce110_opp_set_dyn_expansion,
	.opp_destroy = dce110_opp_destroy,
	.opp_program_fmt = dce110_opp_program_fmt,
	.opp_program_bit_depth_reduction = dce110_opp_program_bit_depth_reduction
पूर्ण;

#अगर defined(CONFIG_DRM_AMD_DC_SI)
अटल स्थिर काष्ठा opp_funcs dce60_opp_funcs = अणु
	.opp_set_dyn_expansion = dce110_opp_set_dyn_expansion,
	.opp_destroy = dce110_opp_destroy,
	.opp_program_fmt = dce60_opp_program_fmt,
	.opp_program_bit_depth_reduction = dce60_opp_program_bit_depth_reduction
पूर्ण;
#पूर्ण_अगर

व्योम dce110_opp_स्थिरruct(काष्ठा dce110_opp *opp110,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dce_opp_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_opp_shअगरt *opp_shअगरt,
	स्थिर काष्ठा dce_opp_mask *opp_mask)
अणु
	opp110->base.funcs = &funcs;

	opp110->base.ctx = ctx;

	opp110->base.inst = inst;

	opp110->regs = regs;
	opp110->opp_shअगरt = opp_shअगरt;
	opp110->opp_mask = opp_mask;
पूर्ण

#अगर defined(CONFIG_DRM_AMD_DC_SI)
व्योम dce60_opp_स्थिरruct(काष्ठा dce110_opp *opp110,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dce_opp_रेजिस्टरs *regs,
	स्थिर काष्ठा dce_opp_shअगरt *opp_shअगरt,
	स्थिर काष्ठा dce_opp_mask *opp_mask)
अणु
	opp110->base.funcs = &dce60_opp_funcs;

	opp110->base.ctx = ctx;

	opp110->base.inst = inst;

	opp110->regs = regs;
	opp110->opp_shअगरt = opp_shअगरt;
	opp110->opp_mask = opp_mask;
पूर्ण
#पूर्ण_अगर

व्योम dce110_opp_destroy(काष्ठा output_pixel_processor **opp)
अणु
	अगर (*opp)
		kमुक्त(FROM_DCE11_OPP(*opp));
	*opp = शून्य;
पूर्ण

