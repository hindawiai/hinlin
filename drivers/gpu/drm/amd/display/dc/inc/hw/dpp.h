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


#अगर_अघोषित __DAL_DPP_H__
#घोषणा __DAL_DPP_H__

#समावेश "transform.h"

काष्ठा dpp अणु
	स्थिर काष्ठा dpp_funcs *funcs;
	काष्ठा dc_context *ctx;
	पूर्णांक inst;
	काष्ठा dpp_caps *caps;
	काष्ठा pwl_params regamma_params;
	काष्ठा pwl_params degamma_params;
	काष्ठा dpp_cursor_attributes cur_attr;

	काष्ठा pwl_params shaper_params;
	bool cm_bypass_mode;
पूर्ण;

काष्ठा dpp_input_csc_matrix अणु
	क्रमागत dc_color_space color_space;
	uपूर्णांक16_t regval[12];
पूर्ण;

अटल स्थिर काष्ठा dpp_input_csc_matrix __maybe_unused dpp_input_csc_matrix[] = अणु
	अणुCOLOR_SPACE_SRGB,
		अणु0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0पूर्ण पूर्ण,
	अणुCOLOR_SPACE_SRGB_LIMITED,
		अणु0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0पूर्ण पूर्ण,
	अणुCOLOR_SPACE_YCBCR601,
		अणु0x2cdd, 0x2000, 0, 0xe991, 0xe926, 0x2000, 0xf4fd, 0x10ef,
						0, 0x2000, 0x38b4, 0xe3a6पूर्ण पूर्ण,
	अणुCOLOR_SPACE_YCBCR601_LIMITED,
		अणु0x3353, 0x2568, 0, 0xe400, 0xe5dc, 0x2568, 0xf367, 0x1108,
						0, 0x2568, 0x40de, 0xdd3aपूर्ण पूर्ण,
	अणुCOLOR_SPACE_YCBCR709,
		अणु0x3265, 0x2000, 0, 0xe6ce, 0xf105, 0x2000, 0xfa01, 0xa7d, 0,
						0x2000, 0x3b61, 0xe24fपूर्ण पूर्ण,

	अणुCOLOR_SPACE_YCBCR709_LIMITED,
		अणु0x39a6, 0x2568, 0, 0xe0d6, 0xeedd, 0x2568, 0xf925, 0x9a8, 0,
						0x2568, 0x43ee, 0xdbb2पूर्ण पूर्ण
पूर्ण;

काष्ठा dpp_grph_csc_adjusपंचांगent अणु
	काष्ठा fixed31_32 temperature_matrix[CSC_TEMPERATURE_MATRIX_SIZE];
	क्रमागत graphics_gamut_adjust_type gamut_adjust_type;
पूर्ण;

काष्ठा cnv_color_keyer_params अणु
	पूर्णांक color_keyer_en;
	पूर्णांक color_keyer_mode;
	पूर्णांक color_keyer_alpha_low;
	पूर्णांक color_keyer_alpha_high;
	पूर्णांक color_keyer_red_low;
	पूर्णांक color_keyer_red_high;
	पूर्णांक color_keyer_green_low;
	पूर्णांक color_keyer_green_high;
	पूर्णांक color_keyer_blue_low;
	पूर्णांक color_keyer_blue_high;
पूर्ण;

/* new क्रम dcn2: set the 8bit alpha values based on the 2 bit alpha
 *ALPHA_2BIT_LUT. ALPHA_2BIT_LUT0   शेष: 0b00000000
 *ALPHA_2BIT_LUT. ALPHA_2BIT_LUT1   शेष: 0b01010101
 *ALPHA_2BIT_LUT. ALPHA_2BIT_LUT2   शेष: 0b10101010
 *ALPHA_2BIT_LUT. ALPHA_2BIT_LUT3   शेष: 0b11111111
 */
काष्ठा cnv_alpha_2bit_lut अणु
	पूर्णांक lut0;
	पूर्णांक lut1;
	पूर्णांक lut2;
	पूर्णांक lut3;
पूर्ण;

काष्ठा dcn_dpp_state अणु
	uपूर्णांक32_t is_enabled;
	uपूर्णांक32_t igam_lut_mode;
	uपूर्णांक32_t igam_input_क्रमmat;
	uपूर्णांक32_t dgam_lut_mode;
	uपूर्णांक32_t rgam_lut_mode;
	uपूर्णांक32_t gamut_remap_mode;
	uपूर्णांक32_t gamut_remap_c11_c12;
	uपूर्णांक32_t gamut_remap_c13_c14;
	uपूर्णांक32_t gamut_remap_c21_c22;
	uपूर्णांक32_t gamut_remap_c23_c24;
	uपूर्णांक32_t gamut_remap_c31_c32;
	uपूर्णांक32_t gamut_remap_c33_c34;
पूर्ण;

काष्ठा CM_bias_params अणु
	uपूर्णांक32_t cm_bias_cr_r;
	uपूर्णांक32_t cm_bias_y_g;
	uपूर्णांक32_t cm_bias_cb_b;
	uपूर्णांक32_t cm_bias_क्रमmat;
पूर्ण;

काष्ठा dpp_funcs अणु
	bool (*dpp_program_gamcor_lut)(
		काष्ठा dpp *dpp_base, स्थिर काष्ठा pwl_params *params);

	व्योम (*dpp_set_pre_degam)(काष्ठा dpp *dpp_base,
			क्रमागत dc_transfer_func_predefined tr);

	व्योम (*dpp_program_cm_dealpha)(काष्ठा dpp *dpp_base,
		uपूर्णांक32_t enable, uपूर्णांक32_t additive_blending);

	व्योम (*dpp_program_cm_bias)(
		काष्ठा dpp *dpp_base,
		काष्ठा CM_bias_params *bias_params);

	व्योम (*dpp_पढ़ो_state)(काष्ठा dpp *dpp, काष्ठा dcn_dpp_state *s);

	व्योम (*dpp_reset)(काष्ठा dpp *dpp);

	व्योम (*dpp_set_scaler)(काष्ठा dpp *dpp,
			स्थिर काष्ठा scaler_data *scl_data);

	व्योम (*dpp_set_pixel_storage_depth)(
			काष्ठा dpp *dpp,
			क्रमागत lb_pixel_depth depth,
			स्थिर काष्ठा bit_depth_reduction_params *bit_depth_params);

	bool (*dpp_get_optimal_number_of_taps)(
			काष्ठा dpp *dpp,
			काष्ठा scaler_data *scl_data,
			स्थिर काष्ठा scaling_taps *in_taps);

	व्योम (*dpp_set_gamut_remap)(
			काष्ठा dpp *dpp,
			स्थिर काष्ठा dpp_grph_csc_adjusपंचांगent *adjust);

	व्योम (*dpp_set_csc_शेष)(
		काष्ठा dpp *dpp,
		क्रमागत dc_color_space colorspace);

	व्योम (*dpp_set_csc_adjusपंचांगent)(
		काष्ठा dpp *dpp,
		स्थिर uपूर्णांक16_t *regval);

	व्योम (*dpp_घातer_on_regamma_lut)(
		काष्ठा dpp *dpp,
		bool घातer_on);

	व्योम (*dpp_program_regamma_lut)(
			काष्ठा dpp *dpp,
			स्थिर काष्ठा pwl_result_data *rgb,
			uपूर्णांक32_t num);

	व्योम (*dpp_configure_regamma_lut)(
			काष्ठा dpp *dpp,
			bool is_ram_a);

	व्योम (*dpp_program_regamma_lutb_settings)(
			काष्ठा dpp *dpp,
			स्थिर काष्ठा pwl_params *params);

	व्योम (*dpp_program_regamma_luta_settings)(
			काष्ठा dpp *dpp,
			स्थिर काष्ठा pwl_params *params);

	व्योम (*dpp_program_regamma_pwl)(
		काष्ठा dpp *dpp,
		स्थिर काष्ठा pwl_params *params,
		क्रमागत opp_regamma mode);

	व्योम (*dpp_program_bias_and_scale)(
			काष्ठा dpp *dpp,
			काष्ठा dc_bias_and_scale *params);

	व्योम (*dpp_set_degamma)(
			काष्ठा dpp *dpp_base,
			क्रमागत ipp_degamma_mode mode);

	व्योम (*dpp_program_input_lut)(
			काष्ठा dpp *dpp_base,
			स्थिर काष्ठा dc_gamma *gamma);

	व्योम (*dpp_program_degamma_pwl)(काष्ठा dpp *dpp_base,
									 स्थिर काष्ठा pwl_params *params);

	व्योम (*dpp_setup)(
			काष्ठा dpp *dpp_base,
			क्रमागत surface_pixel_क्रमmat क्रमmat,
			क्रमागत expansion_mode mode,
			काष्ठा dc_csc_transक्रमm input_csc_color_matrix,
			क्रमागत dc_color_space input_color_space,
			काष्ठा cnv_alpha_2bit_lut *alpha_2bit_lut);

	व्योम (*dpp_full_bypass)(काष्ठा dpp *dpp_base);

	व्योम (*set_cursor_attributes)(
			काष्ठा dpp *dpp_base,
			काष्ठा dc_cursor_attributes *cursor_attributes);

	व्योम (*set_cursor_position)(
			काष्ठा dpp *dpp_base,
			स्थिर काष्ठा dc_cursor_position *pos,
			स्थिर काष्ठा dc_cursor_mi_param *param,
			uपूर्णांक32_t width,
			uपूर्णांक32_t height
			);

	व्योम (*dpp_set_hdr_multiplier)(
			काष्ठा dpp *dpp_base,
			uपूर्णांक32_t multiplier);

	व्योम (*set_optional_cursor_attributes)(
			काष्ठा dpp *dpp_base,
			काष्ठा dpp_cursor_attributes *attr);

	व्योम (*dpp_dppclk_control)(
			काष्ठा dpp *dpp_base,
			bool dppclk_भाग,
			bool enable);

	bool (*dpp_program_blnd_lut)(
			काष्ठा dpp *dpp,
			स्थिर काष्ठा pwl_params *params);
	bool (*dpp_program_shaper_lut)(
			काष्ठा dpp *dpp,
			स्थिर काष्ठा pwl_params *params);
	bool (*dpp_program_3dlut)(
			काष्ठा dpp *dpp,
			काष्ठा tetrahedral_params *params);
	व्योम (*dpp_cnv_set_alpha_keyer)(
			काष्ठा dpp *dpp_base,
			काष्ठा cnv_color_keyer_params *color_keyer);
पूर्ण;



#पूर्ण_अगर
