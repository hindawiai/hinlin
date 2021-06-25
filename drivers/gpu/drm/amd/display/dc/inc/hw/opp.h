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

#अगर_अघोषित __DAL_OPP_H__
#घोषणा __DAL_OPP_H__

#समावेश "hw_shared.h"
#समावेश "dc_hw_types.h"
#समावेश "transform.h"
#समावेश "mpc.h"

काष्ठा fixed31_32;

/* TODO: Need cleanup */
क्रमागत clamping_range अणु
	CLAMPING_FULL_RANGE = 0,	   /* No Clamping */
	CLAMPING_LIMITED_RANGE_8BPC,   /* 8  bpc: Clamping 1  to FE */
	CLAMPING_LIMITED_RANGE_10BPC, /* 10 bpc: Clamping 4  to 3FB */
	CLAMPING_LIMITED_RANGE_12BPC, /* 12 bpc: Clamping 10 to FEF */
	/* Use programmable clampping value on FMT_CLAMP_COMPONENT_R/G/B. */
	CLAMPING_LIMITED_RANGE_PROGRAMMABLE
पूर्ण;

काष्ठा clamping_and_pixel_encoding_params अणु
	क्रमागत dc_pixel_encoding pixel_encoding; /* Pixel Encoding */
	क्रमागत clamping_range clamping_level; /* Clamping identअगरier */
	क्रमागत dc_color_depth c_depth; /* Deep color use. */
पूर्ण;

काष्ठा bit_depth_reduction_params अणु
	काष्ठा अणु
		/* truncate/round */
		/* trunc/round enabled*/
		uपूर्णांक32_t TRUNCATE_ENABLED:1;
		/* 2 bits: 0=6 bpc, 1=8 bpc, 2 = 10bpc*/
		uपूर्णांक32_t TRUNCATE_DEPTH:2;
		/* truncate or round*/
		uपूर्णांक32_t TRUNCATE_MODE:1;

		/* spatial dither */
		/* Spatial Bit Depth Reduction enabled*/
		uपूर्णांक32_t SPATIAL_DITHER_ENABLED:1;
		/* 2 bits: 0=6 bpc, 1 = 8 bpc, 2 = 10bpc*/
		uपूर्णांक32_t SPATIAL_DITHER_DEPTH:2;
		/* 0-3 to select patterns*/
		uपूर्णांक32_t SPATIAL_DITHER_MODE:2;
		/* Enable RGB अक्रमom dithering*/
		uपूर्णांक32_t RGB_RANDOM:1;
		/* Enable Frame अक्रमom dithering*/
		uपूर्णांक32_t FRAME_RANDOM:1;
		/* Enable HighPass अक्रमom dithering*/
		uपूर्णांक32_t HIGHPASS_RANDOM:1;

		/* temporal dither*/
		 /* frame modulation enabled*/
		uपूर्णांक32_t FRAME_MODULATION_ENABLED:1;
		/* same as क्रम trunc/spatial*/
		uपूर्णांक32_t FRAME_MODULATION_DEPTH:2;
		/* 2/4 gray levels*/
		uपूर्णांक32_t TEMPORAL_LEVEL:1;
		uपूर्णांक32_t FRC25:2;
		uपूर्णांक32_t FRC50:2;
		uपूर्णांक32_t FRC75:2;
	पूर्ण flags;

	uपूर्णांक32_t r_seed_value;
	uपूर्णांक32_t b_seed_value;
	uपूर्णांक32_t g_seed_value;
	क्रमागत dc_pixel_encoding pixel_encoding;
पूर्ण;

क्रमागत wide_gamut_regamma_mode अणु
	/*  0x0  - BITS2:0 Bypass */
	WIDE_GAMUT_REGAMMA_MODE_GRAPHICS_BYPASS,
	/*  0x1  - Fixed curve sRGB 2.4 */
	WIDE_GAMUT_REGAMMA_MODE_GRAPHICS_SRGB24,
	/*  0x2  - Fixed curve xvYCC 2.22 */
	WIDE_GAMUT_REGAMMA_MODE_GRAPHICS_XYYCC22,
	/*  0x3  - Programmable control A */
	WIDE_GAMUT_REGAMMA_MODE_GRAPHICS_MATRIX_A,
	/*  0x4  - Programmable control B */
	WIDE_GAMUT_REGAMMA_MODE_GRAPHICS_MATRIX_B,
	/*  0x0  - BITS6:4 Bypass */
	WIDE_GAMUT_REGAMMA_MODE_OVL_BYPASS,
	/*  0x1  - Fixed curve sRGB 2.4 */
	WIDE_GAMUT_REGAMMA_MODE_OVL_SRGB24,
	/*  0x2  - Fixed curve xvYCC 2.22 */
	WIDE_GAMUT_REGAMMA_MODE_OVL_XYYCC22,
	/*  0x3  - Programmable control A */
	WIDE_GAMUT_REGAMMA_MODE_OVL_MATRIX_A,
	/*  0x4  - Programmable control B */
	WIDE_GAMUT_REGAMMA_MODE_OVL_MATRIX_B
पूर्ण;

काष्ठा gamma_pixel अणु
	काष्ठा fixed31_32 r;
	काष्ठा fixed31_32 g;
	काष्ठा fixed31_32 b;
पूर्ण;

क्रमागत channel_name अणु
	CHANNEL_NAME_RED,
	CHANNEL_NAME_GREEN,
	CHANNEL_NAME_BLUE
पूर्ण;

काष्ठा custom_भग्न_क्रमmat अणु
	uपूर्णांक32_t mantissa_bits;
	uपूर्णांक32_t exponenta_bits;
	bool sign;
पूर्ण;

काष्ठा custom_भग्न_value अणु
	uपूर्णांक32_t mantissa;
	uपूर्णांक32_t exponenta;
	uपूर्णांक32_t value;
	bool negative;
पूर्ण;

काष्ठा hw_x_poपूर्णांक अणु
	uपूर्णांक32_t custom_भग्न_x;
	काष्ठा fixed31_32 x;
	काष्ठा fixed31_32 regamma_y_red;
	काष्ठा fixed31_32 regamma_y_green;
	काष्ठा fixed31_32 regamma_y_blue;

पूर्ण;

काष्ठा pwl_भग्न_data_ex अणु
	काष्ठा fixed31_32 r;
	काष्ठा fixed31_32 g;
	काष्ठा fixed31_32 b;
	काष्ठा fixed31_32 delta_r;
	काष्ठा fixed31_32 delta_g;
	काष्ठा fixed31_32 delta_b;
पूर्ण;

क्रमागत hw_poपूर्णांक_position अणु
	/* hw poपूर्णांक sits between left and right sw poपूर्णांकs */
	HW_POINT_POSITION_MIDDLE,
	/* hw poपूर्णांक lays left from left (smaller) sw poपूर्णांक */
	HW_POINT_POSITION_LEFT,
	/* hw poपूर्णांक lays stays from right (bigger) sw poपूर्णांक */
	HW_POINT_POSITION_RIGHT
पूर्ण;

काष्ठा gamma_poपूर्णांक अणु
	पूर्णांक32_t left_index;
	पूर्णांक32_t right_index;
	क्रमागत hw_poपूर्णांक_position pos;
	काष्ठा fixed31_32 coeff;
पूर्ण;

काष्ठा pixel_gamma_poपूर्णांक अणु
	काष्ठा gamma_poपूर्णांक r;
	काष्ठा gamma_poपूर्णांक g;
	काष्ठा gamma_poपूर्णांक b;
पूर्ण;

काष्ठा gamma_coefficients अणु
	काष्ठा fixed31_32 a0[3];
	काष्ठा fixed31_32 a1[3];
	काष्ठा fixed31_32 a2[3];
	काष्ठा fixed31_32 a3[3];
	काष्ठा fixed31_32 user_gamma[3];
	काष्ठा fixed31_32 user_contrast;
	काष्ठा fixed31_32 user_brightness;
पूर्ण;

काष्ठा pwl_भग्न_data अणु
	काष्ठा fixed31_32 r;
	काष्ठा fixed31_32 g;
	काष्ठा fixed31_32 b;
पूर्ण;

काष्ठा mpc_tree_cfg अणु
	पूर्णांक num_pipes;
	पूर्णांक dpp[MAX_PIPES];
	पूर्णांक mpcc[MAX_PIPES];
पूर्ण;

काष्ठा output_pixel_processor अणु
	काष्ठा dc_context *ctx;
	uपूर्णांक32_t inst;
	काष्ठा pwl_params regamma_params;
	काष्ठा mpc_tree mpc_tree_params;
	bool mpcc_disconnect_pending[MAX_PIPES];
	स्थिर काष्ठा opp_funcs *funcs;
	uपूर्णांक32_t dyn_expansion;
पूर्ण;

क्रमागत fmt_stereo_action अणु
	FMT_STEREO_ACTION_ENABLE = 0,
	FMT_STEREO_ACTION_DISABLE,
	FMT_STEREO_ACTION_UPDATE_POLARITY
पूर्ण;

काष्ठा opp_grph_csc_adjusपंचांगent अणु
	//क्रमागत grph_color_adjust_option color_adjust_option;
	क्रमागत dc_color_space c_space;
	क्रमागत dc_color_depth color_depth; /* clean up to uपूर्णांक32_t */
	क्रमागत graphics_csc_adjust_type   csc_adjust_type;
	पूर्णांक32_t adjust_भागider;
	पूर्णांक32_t grph_cont;
	पूर्णांक32_t grph_sat;
	पूर्णांक32_t grph_bright;
	पूर्णांक32_t grph_hue;
पूर्ण;

/* Underlay related types */

काष्ठा hw_adjusपंचांगent_range अणु
	पूर्णांक32_t hw_शेष;
	पूर्णांक32_t min;
	पूर्णांक32_t max;
	पूर्णांक32_t step;
	uपूर्णांक32_t भागider; /* (actually HW range is min/भागider; भागider !=0) */
पूर्ण;

क्रमागत ovl_csc_adjust_item अणु
	OVERLAY_BRIGHTNESS = 0,
	OVERLAY_GAMMA,
	OVERLAY_CONTRAST,
	OVERLAY_SATURATION,
	OVERLAY_HUE,
	OVERLAY_ALPHA,
	OVERLAY_ALPHA_PER_PIX,
	OVERLAY_COLOR_TEMPERATURE
पूर्ण;

क्रमागत oppbuf_display_segmentation अणु
	OPPBUF_DISPLAY_SEGMENTATION_1_SEGMENT = 0,
	OPPBUF_DISPLAY_SEGMENTATION_2_SEGMENT = 1,
	OPPBUF_DISPLAY_SEGMENTATION_4_SEGMENT = 2,
	OPPBUF_DISPLAY_SEGMENTATION_4_SEGMENT_SPLIT_LEFT = 3,
	OPPBUF_DISPLAY_SEGMENTATION_4_SEGMENT_SPLIT_RIGHT = 4
पूर्ण;

काष्ठा oppbuf_params अणु
	uपूर्णांक32_t active_width;
	क्रमागत oppbuf_display_segmentation mso_segmentation;
	uपूर्णांक32_t mso_overlap_pixel_num;
	uपूर्णांक32_t pixel_repetition;
	uपूर्णांक32_t num_segment_padded_pixels;
पूर्ण;

काष्ठा opp_funcs अणु


	/* FORMATTER RELATED */

	व्योम (*opp_program_fmt)(
			काष्ठा output_pixel_processor *opp,
			काष्ठा bit_depth_reduction_params *fmt_bit_depth,
			काष्ठा clamping_and_pixel_encoding_params *clamping);

	व्योम (*opp_set_dyn_expansion)(
		काष्ठा output_pixel_processor *opp,
		क्रमागत dc_color_space color_sp,
		क्रमागत dc_color_depth color_dpth,
		क्रमागत संकेत_type संकेत);

	व्योम (*opp_program_bit_depth_reduction)(
		काष्ठा output_pixel_processor *opp,
		स्थिर काष्ठा bit_depth_reduction_params *params);

	/* underlay related */
	व्योम (*opp_get_underlay_adjusपंचांगent_range)(
			काष्ठा output_pixel_processor *opp,
			क्रमागत ovl_csc_adjust_item overlay_adjust_item,
			काष्ठा hw_adjusपंचांगent_range *range);

	व्योम (*opp_destroy)(काष्ठा output_pixel_processor **opp);

	व्योम (*opp_program_stereo)(
		काष्ठा output_pixel_processor *opp,
		bool enable,
		स्थिर काष्ठा dc_crtc_timing *timing);

	व्योम (*opp_pipe_घड़ी_control)(
			काष्ठा output_pixel_processor *opp,
			bool enable);

	व्योम (*opp_set_disp_pattern_generator)(
			काष्ठा output_pixel_processor *opp,
			क्रमागत controller_dp_test_pattern test_pattern,
			क्रमागत controller_dp_color_space color_space,
			क्रमागत dc_color_depth color_depth,
			स्थिर काष्ठा tg_color *solid_color,
			पूर्णांक width,
			पूर्णांक height,
			पूर्णांक offset);

	व्योम (*opp_program_dpg_dimensions)(
				काष्ठा output_pixel_processor *opp,
				पूर्णांक width,
				पूर्णांक height);

	bool (*dpg_is_blanked)(
			काष्ठा output_pixel_processor *opp);

	व्योम (*opp_dpg_set_blank_color)(
			काष्ठा output_pixel_processor *opp,
			स्थिर काष्ठा tg_color *color);

	व्योम (*opp_program_left_edge_extra_pixel)(
			काष्ठा output_pixel_processor *opp,
			bool count);

पूर्ण;

#पूर्ण_अगर
