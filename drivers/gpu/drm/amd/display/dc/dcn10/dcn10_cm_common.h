<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_DCN10_CM_COMMON_H__
#घोषणा __DAL_DCN10_CM_COMMON_H__

#घोषणा TF_HELPER_REG_FIELD_LIST(type) \
	type exp_region0_lut_offset; \
	type exp_region0_num_segments; \
	type exp_region1_lut_offset; \
	type exp_region1_num_segments;\
	type field_region_end;\
	type field_region_end_slope;\
	type field_region_end_base;\
	type exp_region_start;\
	type exp_resion_start_segment;\
	type field_region_linear_slope

#घोषणा TF_HELPER_REG_LIST \
	uपूर्णांक32_t start_cntl_b; \
	uपूर्णांक32_t start_cntl_g; \
	uपूर्णांक32_t start_cntl_r; \
	uपूर्णांक32_t start_slope_cntl_b; \
	uपूर्णांक32_t start_slope_cntl_g; \
	uपूर्णांक32_t start_slope_cntl_r; \
	uपूर्णांक32_t start_end_cntl1_b; \
	uपूर्णांक32_t start_end_cntl2_b; \
	uपूर्णांक32_t start_end_cntl1_g; \
	uपूर्णांक32_t start_end_cntl2_g; \
	uपूर्णांक32_t start_end_cntl1_r; \
	uपूर्णांक32_t start_end_cntl2_r; \
	uपूर्णांक32_t region_start; \
	uपूर्णांक32_t region_end

#घोषणा TF_CM_REG_FIELD_LIST(type) \
	type csc_c11; \
	type csc_c12

काष्ठा xfer_func_shअगरt अणु
	TF_HELPER_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा xfer_func_mask अणु
	TF_HELPER_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा xfer_func_reg अणु
	काष्ठा xfer_func_shअगरt shअगरts;
	काष्ठा xfer_func_mask masks;

	TF_HELPER_REG_LIST;
पूर्ण;

काष्ठा cm_color_matrix_shअगरt अणु
	TF_CM_REG_FIELD_LIST(uपूर्णांक8_t);
पूर्ण;

काष्ठा cm_color_matrix_mask अणु
	TF_CM_REG_FIELD_LIST(uपूर्णांक32_t);
पूर्ण;

काष्ठा color_matrices_regअणु
	काष्ठा cm_color_matrix_shअगरt shअगरts;
	काष्ठा cm_color_matrix_mask masks;

	uपूर्णांक32_t csc_c11_c12;
	uपूर्णांक32_t csc_c33_c34;
पूर्ण;

व्योम cm_helper_program_color_matrices(
		काष्ठा dc_context *ctx,
		स्थिर uपूर्णांक16_t *regval,
		स्थिर काष्ठा color_matrices_reg *reg);

व्योम cm_helper_program_xfer_func(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा pwl_params *params,
		स्थिर काष्ठा xfer_func_reg *reg);

bool cm_helper_convert_to_custom_भग्न(
		काष्ठा pwl_result_data *rgb_resulted,
		काष्ठा curve_poपूर्णांकs3 *corner_poपूर्णांकs,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		bool fixpoपूर्णांक);

bool cm_helper_translate_curve_to_hw_क्रमmat(
		स्थिर काष्ठा dc_transfer_func *output_tf,
		काष्ठा pwl_params *lut_params, bool fixpoपूर्णांक);

bool cm_helper_translate_curve_to_degamma_hw_क्रमmat(
				स्थिर काष्ठा dc_transfer_func *output_tf,
				काष्ठा pwl_params *lut_params);


#पूर्ण_अगर
