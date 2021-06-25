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

#अगर_अघोषित __DAL_TRANSFORM_H__
#घोषणा __DAL_TRANSFORM_H__

#समावेश "hw_shared.h"
#समावेश "dc_hw_types.h"
#समावेश "fixed31_32.h"

#घोषणा CSC_TEMPERATURE_MATRIX_SIZE 12

काष्ठा bit_depth_reduction_params;

काष्ठा transक्रमm अणु
	स्थिर काष्ठा transक्रमm_funcs *funcs;
	काष्ठा dc_context *ctx;
	पूर्णांक inst;
	काष्ठा dpp_caps *caps;
	काष्ठा pwl_params regamma_params;
पूर्ण;

/* Colorimetry */
क्रमागत colorimetry अणु
	COLORIMETRY_NO_DATA = 0,
	COLORIMETRY_ITU601 = 1,
	COLORIMETRY_ITU709 = 2,
	COLORIMETRY_EXTENDED = 3
पूर्ण;

क्रमागत colorimetry_ext अणु
	COLORIMETRYEX_XVYCC601 = 0,
	COLORIMETRYEX_XVYCC709 = 1,
	COLORIMETRYEX_SYCC601 = 2,
	COLORIMETRYEX_ADOBEYCC601 = 3,
	COLORIMETRYEX_ADOBERGB = 4,
	COLORIMETRYEX_BT2020YCC = 5,
	COLORIMETRYEX_BT2020RGBYCBCR = 6,
	COLORIMETRYEX_RESERVED = 7
पूर्ण;

क्रमागत active_क्रमmat_info अणु
	ACTIVE_FORMAT_NO_DATA = 0,
	ACTIVE_FORMAT_VALID = 1
पूर्ण;

/* Active क्रमmat aspect ratio */
क्रमागत active_क्रमmat_aspect_ratio अणु
	ACTIVE_FORMAT_ASPECT_RATIO_SAME_AS_PICTURE = 8,
	ACTIVE_FORMAT_ASPECT_RATIO_4_3 = 9,
	ACTIVE_FORMAT_ASPECT_RATIO_16_9 = 0XA,
	ACTIVE_FORMAT_ASPECT_RATIO_14_9 = 0XB
पूर्ण;

क्रमागत bar_info अणु
	BAR_INFO_NOT_VALID = 0,
	BAR_INFO_VERTICAL_VALID = 1,
	BAR_INFO_HORIZONTAL_VALID = 2,
	BAR_INFO_BOTH_VALID = 3
पूर्ण;

क्रमागत picture_scaling अणु
	PICTURE_SCALING_UNIFORM = 0,
	PICTURE_SCALING_HORIZONTAL = 1,
	PICTURE_SCALING_VERTICAL = 2,
	PICTURE_SCALING_BOTH = 3
पूर्ण;

/* RGB quantization range */
क्रमागत rgb_quantization_range अणु
	RGB_QUANTIZATION_DEFAULT_RANGE = 0,
	RGB_QUANTIZATION_LIMITED_RANGE = 1,
	RGB_QUANTIZATION_FULL_RANGE = 2,
	RGB_QUANTIZATION_RESERVED = 3
पूर्ण;

/* YYC quantization range */
क्रमागत yyc_quantization_range अणु
	YYC_QUANTIZATION_LIMITED_RANGE = 0,
	YYC_QUANTIZATION_FULL_RANGE = 1,
	YYC_QUANTIZATION_RESERVED2 = 2,
	YYC_QUANTIZATION_RESERVED3 = 3
पूर्ण;

क्रमागत graphics_gamut_adjust_type अणु
	GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS = 0,
	GRAPHICS_GAMUT_ADJUST_TYPE_HW, /* without adjusपंचांगents */
	GRAPHICS_GAMUT_ADJUST_TYPE_SW /* use adjusपंचांगents */
पूर्ण;

क्रमागत lb_memory_config अणु
	/* Enable all 3 pieces of memory */
	LB_MEMORY_CONFIG_0 = 0,

	/* Enable only the first piece of memory */
	LB_MEMORY_CONFIG_1 = 1,

	/* Enable only the second piece of memory */
	LB_MEMORY_CONFIG_2 = 2,

	/* Only applicable in 4:2:0 mode, enable all 3 pieces of memory and the
	 * last piece of chroma memory used क्रम the luma storage
	 */
	LB_MEMORY_CONFIG_3 = 3
पूर्ण;

काष्ठा xfm_grph_csc_adjusपंचांगent अणु
	काष्ठा fixed31_32 temperature_matrix[CSC_TEMPERATURE_MATRIX_SIZE];
	क्रमागत graphics_gamut_adjust_type gamut_adjust_type;
पूर्ण;

काष्ठा overscan_info अणु
	पूर्णांक left;
	पूर्णांक right;
	पूर्णांक top;
	पूर्णांक bottom;
पूर्ण;

काष्ठा scaling_ratios अणु
	काष्ठा fixed31_32 horz;
	काष्ठा fixed31_32 vert;
	काष्ठा fixed31_32 horz_c;
	काष्ठा fixed31_32 vert_c;
पूर्ण;

काष्ठा sharpness_adj अणु
	पूर्णांक horz;
	पूर्णांक vert;
पूर्ण;

काष्ठा line_buffer_params अणु
	bool alpha_en;
	bool pixel_expan_mode;
	bool पूर्णांकerleave_en;
	पूर्णांक dynamic_pixel_depth;
	क्रमागत lb_pixel_depth depth;
पूर्ण;

काष्ठा scl_inits अणु
	काष्ठा fixed31_32 h;
	काष्ठा fixed31_32 h_c;
	काष्ठा fixed31_32 v;
	काष्ठा fixed31_32 v_bot;
	काष्ठा fixed31_32 v_c;
	काष्ठा fixed31_32 v_c_bot;
पूर्ण;

काष्ठा scaler_data अणु
	पूर्णांक h_active;
	पूर्णांक v_active;
	काष्ठा scaling_taps taps;
	काष्ठा rect viewport;
	काष्ठा rect viewport_c;
	काष्ठा rect viewport_unadjusted;
	काष्ठा rect viewport_c_unadjusted;
	काष्ठा rect recout;
	काष्ठा scaling_ratios ratios;
	काष्ठा scl_inits inits;
	काष्ठा sharpness_adj sharpness;
	क्रमागत pixel_क्रमmat क्रमmat;
	काष्ठा line_buffer_params lb_params;
पूर्ण;

काष्ठा transक्रमm_funcs अणु
	व्योम (*transक्रमm_reset)(काष्ठा transक्रमm *xfm);

	व्योम (*transक्रमm_set_scaler)(काष्ठा transक्रमm *xfm,
			स्थिर काष्ठा scaler_data *scl_data);

	व्योम (*transक्रमm_set_pixel_storage_depth)(
			काष्ठा transक्रमm *xfm,
			क्रमागत lb_pixel_depth depth,
			स्थिर काष्ठा bit_depth_reduction_params *bit_depth_params);

	bool (*transक्रमm_get_optimal_number_of_taps)(
			काष्ठा transक्रमm *xfm,
			काष्ठा scaler_data *scl_data,
			स्थिर काष्ठा scaling_taps *in_taps);

	व्योम (*transक्रमm_set_gamut_remap)(
			काष्ठा transक्रमm *xfm,
			स्थिर काष्ठा xfm_grph_csc_adjusपंचांगent *adjust);

	व्योम (*opp_set_csc_शेष)(
		काष्ठा transक्रमm *xfm,
		स्थिर काष्ठा शेष_adjusपंचांगent *शेष_adjust);

	व्योम (*opp_set_csc_adjusपंचांगent)(
		काष्ठा transक्रमm *xfm,
		स्थिर काष्ठा out_csc_color_matrix *tbl_entry);

	व्योम (*opp_घातer_on_regamma_lut)(
		काष्ठा transक्रमm *xfm,
		bool घातer_on);

	व्योम (*opp_program_regamma_lut)(
			काष्ठा transक्रमm *xfm,
			स्थिर काष्ठा pwl_result_data *rgb,
			uपूर्णांक32_t num);

	व्योम (*opp_configure_regamma_lut)(
			काष्ठा transक्रमm *xfm,
			bool is_ram_a);

	व्योम (*opp_program_regamma_lutb_settings)(
			काष्ठा transक्रमm *xfm,
			स्थिर काष्ठा pwl_params *params);

	व्योम (*opp_program_regamma_luta_settings)(
			काष्ठा transक्रमm *xfm,
			स्थिर काष्ठा pwl_params *params);

	व्योम (*opp_program_regamma_pwl)(
		काष्ठा transक्रमm *xfm, स्थिर काष्ठा pwl_params *params);

	व्योम (*opp_set_regamma_mode)(
			काष्ठा transक्रमm *xfm_base,
			क्रमागत opp_regamma mode);

	व्योम (*ipp_set_degamma)(
			काष्ठा transक्रमm *xfm_base,
			क्रमागत ipp_degamma_mode mode);

	व्योम (*ipp_program_input_lut)(
			काष्ठा transक्रमm *xfm_base,
			स्थिर काष्ठा dc_gamma *gamma);

	व्योम (*ipp_program_degamma_pwl)(काष्ठा transक्रमm *xfm_base,
									 स्थिर काष्ठा pwl_params *params);

	व्योम (*ipp_setup)(
			काष्ठा transक्रमm *xfm_base,
			क्रमागत surface_pixel_क्रमmat क्रमmat,
			क्रमागत expansion_mode mode,
			काष्ठा dc_csc_transक्रमm input_csc_color_matrix,
			क्रमागत dc_color_space input_color_space);

	व्योम (*ipp_full_bypass)(काष्ठा transक्रमm *xfm_base);

	व्योम (*set_cursor_attributes)(
			काष्ठा transक्रमm *xfm_base,
			स्थिर काष्ठा dc_cursor_attributes *attr);

पूर्ण;

स्थिर uपूर्णांक16_t *get_filter_2tap_16p(व्योम);
स्थिर uपूर्णांक16_t *get_filter_2tap_64p(व्योम);
स्थिर uपूर्णांक16_t *get_filter_3tap_16p(काष्ठा fixed31_32 ratio);
स्थिर uपूर्णांक16_t *get_filter_3tap_64p(काष्ठा fixed31_32 ratio);
स्थिर uपूर्णांक16_t *get_filter_4tap_16p(काष्ठा fixed31_32 ratio);
स्थिर uपूर्णांक16_t *get_filter_4tap_64p(काष्ठा fixed31_32 ratio);
स्थिर uपूर्णांक16_t *get_filter_5tap_64p(काष्ठा fixed31_32 ratio);
स्थिर uपूर्णांक16_t *get_filter_6tap_64p(काष्ठा fixed31_32 ratio);
स्थिर uपूर्णांक16_t *get_filter_7tap_64p(काष्ठा fixed31_32 ratio);
स्थिर uपूर्णांक16_t *get_filter_8tap_64p(काष्ठा fixed31_32 ratio);


/* Defines the pixel processing capability of the DSCL */
क्रमागत dscl_data_processing_क्रमmat अणु
	DSCL_DATA_PRCESSING_FIXED_FORMAT,	/* The DSCL processes pixel data in fixed क्रमmat */
	DSCL_DATA_PRCESSING_FLOAT_FORMAT,	/* The DSCL processes pixel data in भग्न क्रमmat */
पूर्ण;

/*
 * The DPP capabilities काष्ठाure contains क्रमागतerations to specअगरy the
 * HW processing features and an associated function poपूर्णांकers to
 * provide the function पूर्णांकerface that can be overloaded क्रम implementations
 * based on dअगरferent capabilities
 */
काष्ठा dpp_caps अणु
	/* DSCL processing pixel data in fixed or भग्न क्रमmat */
	क्रमागत dscl_data_processing_क्रमmat dscl_data_proc_क्रमmat;

	/* Calculates the number of partitions in the line buffer.
	 * The implementation of this function is overloaded क्रम
	 * dअगरferent versions of DSCL LB.
	 */
	व्योम (*dscl_calc_lb_num_partitions)(
			स्थिर काष्ठा scaler_data *scl_data,
			क्रमागत lb_memory_config lb_config,
			पूर्णांक *num_part_y,
			पूर्णांक *num_part_c);
पूर्ण;


#पूर्ण_अगर
