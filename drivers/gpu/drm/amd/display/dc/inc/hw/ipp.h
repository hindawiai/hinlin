<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_IPP_H__
#घोषणा __DAL_IPP_H__

#समावेश "hw_shared.h"
#समावेश "dc_hw_types.h"

#घोषणा MAXTRIX_COEFFICIENTS_NUMBER 12
#घोषणा MAXTRIX_COEFFICIENTS_WRAP_NUMBER (MAXTRIX_COEFFICIENTS_NUMBER + 4)
#घोषणा MAX_OVL_MATRIX_COUNT 12

/* IPP RELATED */
काष्ठा input_pixel_processor अणु
	काष्ठा  dc_context *ctx;
	अचिन्हित पूर्णांक inst;
	स्थिर काष्ठा ipp_funcs *funcs;
पूर्ण;

क्रमागत ipp_prescale_mode अणु
	IPP_PRESCALE_MODE_BYPASS,
	IPP_PRESCALE_MODE_FIXED_SIGNED,
	IPP_PRESCALE_MODE_FLOAT_SIGNED,
	IPP_PRESCALE_MODE_FIXED_UNSIGNED,
	IPP_PRESCALE_MODE_FLOAT_UNSIGNED
पूर्ण;

काष्ठा ipp_prescale_params अणु
	क्रमागत ipp_prescale_mode mode;
	uपूर्णांक16_t bias;
	uपूर्णांक16_t scale;
पूर्ण;



क्रमागत ovl_color_space अणु
	OVL_COLOR_SPACE_UNKNOWN = 0,
	OVL_COLOR_SPACE_RGB,
	OVL_COLOR_SPACE_YUV601,
	OVL_COLOR_SPACE_YUV709
पूर्ण;


काष्ठा ipp_funcs अणु

	/*** cursor ***/
	व्योम (*ipp_cursor_set_position)(
		काष्ठा input_pixel_processor *ipp,
		स्थिर काष्ठा dc_cursor_position *position,
		स्थिर काष्ठा dc_cursor_mi_param *param);

	व्योम (*ipp_cursor_set_attributes)(
		काष्ठा input_pixel_processor *ipp,
		स्थिर काष्ठा dc_cursor_attributes *attributes);

	/*** setup input pixel processing ***/

	/* put the entire pixel processor to bypass */
	व्योम (*ipp_full_bypass)(
			काष्ठा input_pixel_processor *ipp);

	/* setup ipp to expand/convert input to pixel processor पूर्णांकernal क्रमmat */
	व्योम (*ipp_setup)(
		काष्ठा input_pixel_processor *ipp,
		क्रमागत surface_pixel_क्रमmat क्रमmat,
		क्रमागत expansion_mode mode,
		काष्ठा dc_csc_transक्रमm input_csc_color_matrix,
		क्रमागत dc_color_space input_color_space);

	/* DCE function to setup IPP.  TODO: see अगर we can consolidate to setup */
	व्योम (*ipp_program_prescale)(
			काष्ठा input_pixel_processor *ipp,
			काष्ठा ipp_prescale_params *params);

	व्योम (*ipp_program_input_lut)(
			काष्ठा input_pixel_processor *ipp,
			स्थिर काष्ठा dc_gamma *gamma);

	/*** DEGAMMA RELATED ***/
	व्योम (*ipp_set_degamma)(
		काष्ठा input_pixel_processor *ipp,
		क्रमागत ipp_degamma_mode mode);

	व्योम (*ipp_program_degamma_pwl)(
		काष्ठा input_pixel_processor *ipp,
		स्थिर काष्ठा pwl_params *params);

	व्योम (*ipp_destroy)(काष्ठा input_pixel_processor **ipp);
पूर्ण;

#पूर्ण_अगर /* __DAL_IPP_H__ */
