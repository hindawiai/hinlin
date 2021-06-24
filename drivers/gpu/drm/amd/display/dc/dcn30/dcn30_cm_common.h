<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#समावेश "dcn10/dcn10_cm_common.h"

#अगर_अघोषित __DAL_DCN30_CM_COMMON_H__
#घोषणा __DAL_DCN30_CM_COMMON_H__

#घोषणा TF_HELPER_REG_FIELD_LIST_DCN3(type) \
	TF_HELPER_REG_FIELD_LIST(type);\
	type field_region_start_base;\
	type field_offset

काष्ठा DCN3_xfer_func_shअगरt अणु
	TF_HELPER_REG_FIELD_LIST_DCN3(uपूर्णांक8_t);
पूर्ण;

काष्ठा DCN3_xfer_func_mask अणु
	TF_HELPER_REG_FIELD_LIST_DCN3(uपूर्णांक32_t);
पूर्ण;

काष्ठा dcn3_xfer_func_reg अणु
	काष्ठा DCN3_xfer_func_shअगरt shअगरts;
	काष्ठा DCN3_xfer_func_mask masks;

	TF_HELPER_REG_LIST;
	uपूर्णांक32_t offset_b;
	uपूर्णांक32_t offset_g;
	uपूर्णांक32_t offset_r;
	uपूर्णांक32_t start_base_cntl_b;
	uपूर्णांक32_t start_base_cntl_g;
	uपूर्णांक32_t start_base_cntl_r;
पूर्ण;

व्योम cm_helper_program_gamcor_xfer_func(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा pwl_params *params,
	स्थिर काष्ठा dcn3_xfer_func_reg *reg);

bool cm3_helper_translate_curve_to_hw_क्रमmat(
	स्थिर काष्ठा dc_transfer_func *output_tf,
	काष्ठा pwl_params *lut_params, bool fixpoपूर्णांक);

bool cm3_helper_translate_curve_to_degamma_hw_क्रमmat(
				स्थिर काष्ठा dc_transfer_func *output_tf,
				काष्ठा pwl_params *lut_params);

bool cm3_helper_convert_to_custom_भग्न(
		काष्ठा pwl_result_data *rgb_resulted,
		काष्ठा curve_poपूर्णांकs3 *corner_poपूर्णांकs,
		uपूर्णांक32_t hw_poपूर्णांकs_num,
		bool fixpoपूर्णांक);

bool is_rgb_equal(स्थिर काष्ठा pwl_result_data *rgb, uपूर्णांक32_t num);

#पूर्ण_अगर
