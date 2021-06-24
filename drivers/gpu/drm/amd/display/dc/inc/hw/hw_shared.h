<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_HW_SHARED_H__
#घोषणा __DAL_HW_SHARED_H__

#समावेश "os_types.h"
#समावेश "fixed31_32.h"
#समावेश "dc_hw_types.h"

/******************************************************************************
 * Data types shared between dअगरferent Virtual HW blocks
 ******************************************************************************/

#घोषणा MAX_AUDIOS 7
#घोषणा MAX_PIPES 6
#घोषणा MAX_DIG_LINK_ENCODERS 7
#घोषणा MAX_DWB_PIPES	1

काष्ठा gamma_curve अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t segments_num;
पूर्ण;

काष्ठा curve_poपूर्णांकs अणु
	काष्ठा fixed31_32 x;
	काष्ठा fixed31_32 y;
	काष्ठा fixed31_32 offset;
	काष्ठा fixed31_32 slope;

	uपूर्णांक32_t custom_भग्न_x;
	uपूर्णांक32_t custom_भग्न_y;
	uपूर्णांक32_t custom_भग्न_offset;
	uपूर्णांक32_t custom_भग्न_slope;
पूर्ण;

काष्ठा curve_poपूर्णांकs3 अणु
	काष्ठा curve_poपूर्णांकs red;
	काष्ठा curve_poपूर्णांकs green;
	काष्ठा curve_poपूर्णांकs blue;
पूर्ण;

काष्ठा pwl_result_data अणु
	काष्ठा fixed31_32 red;
	काष्ठा fixed31_32 green;
	काष्ठा fixed31_32 blue;

	काष्ठा fixed31_32 delta_red;
	काष्ठा fixed31_32 delta_green;
	काष्ठा fixed31_32 delta_blue;

	uपूर्णांक32_t red_reg;
	uपूर्णांक32_t green_reg;
	uपूर्णांक32_t blue_reg;

	uपूर्णांक32_t delta_red_reg;
	uपूर्णांक32_t delta_green_reg;
	uपूर्णांक32_t delta_blue_reg;
पूर्ण;

काष्ठा dc_rgb अणु
	uपूर्णांक32_t red;
	uपूर्णांक32_t green;
	uपूर्णांक32_t blue;
पूर्ण;

काष्ठा tetrahedral_17x17x17 अणु
	काष्ठा dc_rgb lut0[1229];
	काष्ठा dc_rgb lut1[1228];
	काष्ठा dc_rgb lut2[1228];
	काष्ठा dc_rgb lut3[1228];
पूर्ण;
काष्ठा tetrahedral_9x9x9 अणु
	काष्ठा dc_rgb lut0[183];
	काष्ठा dc_rgb lut1[182];
	काष्ठा dc_rgb lut2[182];
	काष्ठा dc_rgb lut3[182];
पूर्ण;

काष्ठा tetrahedral_params अणु
	जोड़ अणु
		काष्ठा tetrahedral_17x17x17 tetrahedral_17;
		काष्ठा tetrahedral_9x9x9 tetrahedral_9;
	पूर्ण;
	bool use_tetrahedral_9;
	bool use_12bits;

पूर्ण;

/* arr_curve_poपूर्णांकs - regamma regions/segments specअगरication
 * arr_poपूर्णांकs - beginning and end poपूर्णांक specअगरied separately (only one on DCE)
 * corner_poपूर्णांकs - beginning and end poपूर्णांक क्रम all 3 colors (DCN)
 * rgb_resulted - final curve
 */
काष्ठा pwl_params अणु
	काष्ठा gamma_curve arr_curve_poपूर्णांकs[34];
	जोड़ अणु
		काष्ठा curve_poपूर्णांकs arr_poपूर्णांकs[2];
		काष्ठा curve_poपूर्णांकs3 corner_poपूर्णांकs[2];
	पूर्ण;
	काष्ठा pwl_result_data rgb_resulted[256 + 3];
	uपूर्णांक32_t hw_poपूर्णांकs_num;
पूर्ण;

/* move to dpp
 * जबतक we are moving functionality out of opp to dpp to align
 * HW programming to HW IP, we define these काष्ठा in hw_shared
 * so we can still compile जबतक refactoring
 */

क्रमागत lb_pixel_depth अणु
	/* करो not change the values because it is used as bit vector */
	LB_PIXEL_DEPTH_18BPP = 1,
	LB_PIXEL_DEPTH_24BPP = 2,
	LB_PIXEL_DEPTH_30BPP = 4,
	LB_PIXEL_DEPTH_36BPP = 8
पूर्ण;

क्रमागत graphics_csc_adjust_type अणु
	GRAPHICS_CSC_ADJUST_TYPE_BYPASS = 0,
	GRAPHICS_CSC_ADJUST_TYPE_HW, /* without adjusपंचांगents */
	GRAPHICS_CSC_ADJUST_TYPE_SW  /*use adjusपंचांगents */
पूर्ण;

क्रमागत ipp_degamma_mode अणु
	IPP_DEGAMMA_MODE_BYPASS,
	IPP_DEGAMMA_MODE_HW_sRGB,
	IPP_DEGAMMA_MODE_HW_xvYCC,
	IPP_DEGAMMA_MODE_USER_PWL
पूर्ण;

क्रमागत gamcor_mode अणु
	GAMCOR_MODE_BYPASS,
	GAMCOR_MODE_RESERVED_1,
	GAMCOR_MODE_USER_PWL,
	GAMCOR_MODE_RESERVED_3
पूर्ण;

क्रमागत ipp_output_क्रमmat अणु
	IPP_OUTPUT_FORMAT_12_BIT_FIX,
	IPP_OUTPUT_FORMAT_16_BIT_BYPASS,
	IPP_OUTPUT_FORMAT_FLOAT
पूर्ण;

क्रमागत expansion_mode अणु
	EXPANSION_MODE_DYNAMIC,
	EXPANSION_MODE_ZERO
पूर्ण;

काष्ठा शेष_adjusपंचांगent अणु
	क्रमागत lb_pixel_depth lb_color_depth;
	क्रमागत dc_color_space out_color_space;
	क्रमागत dc_color_space in_color_space;
	क्रमागत dc_color_depth color_depth;
	क्रमागत pixel_क्रमmat surface_pixel_क्रमmat;
	क्रमागत graphics_csc_adjust_type csc_adjust_type;
	bool क्रमce_hw_शेष;
पूर्ण;


काष्ठा out_csc_color_matrix अणु
	क्रमागत dc_color_space color_space;
	uपूर्णांक16_t regval[12];
पूर्ण;

क्रमागत gamut_remap_select अणु
	GAMUT_REMAP_BYPASS = 0,
	GAMUT_REMAP_COEFF,
	GAMUT_REMAP_COMA_COEFF,
	GAMUT_REMAP_COMB_COEFF
पूर्ण;

क्रमागत opp_regamma अणु
	OPP_REGAMMA_BYPASS = 0,
	OPP_REGAMMA_SRGB,
	OPP_REGAMMA_XVYCC,
	OPP_REGAMMA_USER
पूर्ण;

क्रमागत optc_dsc_mode अणु
	OPTC_DSC_DISABLED = 0,
	OPTC_DSC_ENABLED_444 = 1, /* 'RGB 444' or 'Simple YCbCr 4:2:2' (4:2:2 upsampled to 4:4:4) */
	OPTC_DSC_ENABLED_NATIVE_SUBSAMPLED = 2 /* Native 4:2:2 or 4:2:0 */
पूर्ण;

काष्ठा dc_bias_and_scale अणु
	uपूर्णांक16_t scale_red;
	uपूर्णांक16_t bias_red;
	uपूर्णांक16_t scale_green;
	uपूर्णांक16_t bias_green;
	uपूर्णांक16_t scale_blue;
	uपूर्णांक16_t bias_blue;
पूर्ण;

क्रमागत test_pattern_dyn_range अणु
	TEST_PATTERN_DYN_RANGE_VESA = 0,
	TEST_PATTERN_DYN_RANGE_CEA
पूर्ण;

क्रमागत test_pattern_mode अणु
	TEST_PATTERN_MODE_COLORSQUARES_RGB = 0,
	TEST_PATTERN_MODE_COLORSQUARES_YCBCR601,
	TEST_PATTERN_MODE_COLORSQUARES_YCBCR709,
	TEST_PATTERN_MODE_VERTICALBARS,
	TEST_PATTERN_MODE_HORIZONTALBARS,
	TEST_PATTERN_MODE_SINGLERAMP_RGB,
	TEST_PATTERN_MODE_DUALRAMP_RGB,
	TEST_PATTERN_MODE_XR_BIAS_RGB
पूर्ण;

क्रमागत test_pattern_color_क्रमmat अणु
	TEST_PATTERN_COLOR_FORMAT_BPC_6 = 0,
	TEST_PATTERN_COLOR_FORMAT_BPC_8,
	TEST_PATTERN_COLOR_FORMAT_BPC_10,
	TEST_PATTERN_COLOR_FORMAT_BPC_12
पूर्ण;

क्रमागत controller_dp_test_pattern अणु
	CONTROLLER_DP_TEST_PATTERN_D102 = 0,
	CONTROLLER_DP_TEST_PATTERN_SYMBOLERROR,
	CONTROLLER_DP_TEST_PATTERN_PRBS7,
	CONTROLLER_DP_TEST_PATTERN_COLORSQUARES,
	CONTROLLER_DP_TEST_PATTERN_VERTICALBARS,
	CONTROLLER_DP_TEST_PATTERN_HORIZONTALBARS,
	CONTROLLER_DP_TEST_PATTERN_COLORRAMP,
	CONTROLLER_DP_TEST_PATTERN_VIDEOMODE,
	CONTROLLER_DP_TEST_PATTERN_RESERVED_8,
	CONTROLLER_DP_TEST_PATTERN_RESERVED_9,
	CONTROLLER_DP_TEST_PATTERN_RESERVED_A,
	CONTROLLER_DP_TEST_PATTERN_COLORSQUARES_CEA,
	CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR
पूर्ण;

क्रमागत controller_dp_color_space अणु
	CONTROLLER_DP_COLOR_SPACE_RGB,
	CONTROLLER_DP_COLOR_SPACE_YCBCR601,
	CONTROLLER_DP_COLOR_SPACE_YCBCR709,
	CONTROLLER_DP_COLOR_SPACE_UDEFINED
पूर्ण;

क्रमागत dc_lut_mode अणु
	LUT_BYPASS,
	LUT_RAM_A,
	LUT_RAM_B
पूर्ण;

/**
 * speakersToChannels
 *
 * @brief
 *  translate speakers to channels
 *
 *  FL  - Front Left
 *  FR  - Front Right
 *  RL  - Rear Left
 *  RR  - Rear Right
 *  RC  - Rear Center
 *  FC  - Front Center
 *  FLC - Front Left Center
 *  FRC - Front Right Center
 *  RLC - Rear Left Center
 *  RRC - Rear Right Center
 *  LFE - Low Freq Effect
 *
 *               FC
 *          FLC      FRC
 *    FL                    FR
 *
 *                    LFE
 *              ()
 *
 *
 *    RL                    RR
 *          RLC      RRC
 *               RC
 *
 *             ch  8   7   6   5   4   3   2   1
 * 0b00000011      -   -   -   -   -   -   FR  FL
 * 0b00000111      -   -   -   -   -   LFE FR  FL
 * 0b00001011      -   -   -   -   FC  -   FR  FL
 * 0b00001111      -   -   -   -   FC  LFE FR  FL
 * 0b00010011      -   -   -   RC  -   -   FR  FL
 * 0b00010111      -   -   -   RC  -   LFE FR  FL
 * 0b00011011      -   -   -   RC  FC  -   FR  FL
 * 0b00011111      -   -   -   RC  FC  LFE FR  FL
 * 0b00110011      -   -   RR  RL  -   -   FR  FL
 * 0b00110111      -   -   RR  RL  -   LFE FR  FL
 * 0b00111011      -   -   RR  RL  FC  -   FR  FL
 * 0b00111111      -   -   RR  RL  FC  LFE FR  FL
 * 0b01110011      -   RC  RR  RL  -   -   FR  FL
 * 0b01110111      -   RC  RR  RL  -   LFE FR  FL
 * 0b01111011      -   RC  RR  RL  FC  -   FR  FL
 * 0b01111111      -   RC  RR  RL  FC  LFE FR  FL
 * 0b11110011      RRC RLC RR  RL  -   -   FR  FL
 * 0b11110111      RRC RLC RR  RL  -   LFE FR  FL
 * 0b11111011      RRC RLC RR  RL  FC  -   FR  FL
 * 0b11111111      RRC RLC RR  RL  FC  LFE FR  FL
 * 0b11000011      FRC FLC -   -   -   -   FR  FL
 * 0b11000111      FRC FLC -   -   -   LFE FR  FL
 * 0b11001011      FRC FLC -   -   FC  -   FR  FL
 * 0b11001111      FRC FLC -   -   FC  LFE FR  FL
 * 0b11010011      FRC FLC -   RC  -   -   FR  FL
 * 0b11010111      FRC FLC -   RC  -   LFE FR  FL
 * 0b11011011      FRC FLC -   RC  FC  -   FR  FL
 * 0b11011111      FRC FLC -   RC  FC  LFE FR  FL
 * 0b11110011      FRC FLC RR  RL  -   -   FR  FL
 * 0b11110111      FRC FLC RR  RL  -   LFE FR  FL
 * 0b11111011      FRC FLC RR  RL  FC  -   FR  FL
 * 0b11111111      FRC FLC RR  RL  FC  LFE FR  FL
 *
 * @param
 *  speakers - speaker inक्रमmation as it comes from CEA audio block
 */
/* translate speakers to channels */

जोड़ audio_cea_channels अणु
	uपूर्णांक8_t all;
	काष्ठा audio_cea_channels_bits अणु
		uपूर्णांक32_t FL:1;
		uपूर्णांक32_t FR:1;
		uपूर्णांक32_t LFE:1;
		uपूर्णांक32_t FC:1;
		uपूर्णांक32_t RL_RC:1;
		uपूर्णांक32_t RR:1;
		uपूर्णांक32_t RC_RLC_FLC:1;
		uपूर्णांक32_t RRC_FRC:1;
	पूर्ण channels;
पूर्ण;

#पूर्ण_अगर /* __DAL_HW_SHARED_H__ */
