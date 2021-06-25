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

#अगर_अघोषित COLOR_MOD_COLOR_GAMMA_H_
#घोषणा COLOR_MOD_COLOR_GAMMA_H_

#समावेश "color_table.h"

काष्ठा dc_transfer_func;
काष्ठा dc_gamma;
काष्ठा dc_transfer_func_distributed_poपूर्णांकs;
काष्ठा dc_rgb_fixed;
काष्ठा dc_color_caps;
क्रमागत dc_transfer_func_predefined;

/* For SetRegamma ADL पूर्णांकerface support
 * Must match escape type
 */
जोड़ regamma_flags अणु
	अचिन्हित पूर्णांक raw;
	काष्ठा अणु
		अचिन्हित पूर्णांक gammaRampArray       :1;    // RegammaRamp is in use
		अचिन्हित पूर्णांक gammaFromEdid        :1;    //gamma from edid is in use
		अचिन्हित पूर्णांक gammaFromEdidEx      :1;    //gamma from edid is in use , but only क्रम Display Id 1.2
		अचिन्हित पूर्णांक gammaFromUser        :1;    //user custom gamma is used
		अचिन्हित पूर्णांक coeffFromUser        :1;    //coeff. A0-A3 from user is in use
		अचिन्हित पूर्णांक coeffFromEdid        :1;    //coeff. A0-A3 from edid is in use
		अचिन्हित पूर्णांक applyDegamma         :1;    //flag क्रम additional degamma correction in driver
		अचिन्हित पूर्णांक gammaPredefinedSRGB  :1;    //flag क्रम SRGB gamma
		अचिन्हित पूर्णांक gammaPredefinedPQ    :1;    //flag क्रम PQ gamma
		अचिन्हित पूर्णांक gammaPredefinedPQ2084Interim :1;    //flag क्रम PQ gamma, lower max nits
		अचिन्हित पूर्णांक gammaPredefined36    :1;    //flag क्रम 3.6 gamma
		अचिन्हित पूर्णांक gammaPredefinedReset :1;    //flag to वापस to previous gamma
	पूर्ण bits;
पूर्ण;

काष्ठा regamma_ramp अणु
	अचिन्हित लघु gamma[256*3];  // gamma ramp packed  in same way as OS winकरोws ,r , g & b
पूर्ण;

काष्ठा regamma_coeff अणु
	पूर्णांक    gamma[3];
	पूर्णांक    A0[3];
	पूर्णांक    A1[3];
	पूर्णांक    A2[3];
	पूर्णांक    A3[3];
पूर्ण;

काष्ठा regamma_lut अणु
	जोड़ regamma_flags flags;
	जोड़ अणु
		काष्ठा regamma_ramp ramp;
		काष्ठा regamma_coeff coeff;
	पूर्ण;
पूर्ण;

काष्ठा hdr_पंचांग_params अणु
	अचिन्हित पूर्णांक sdr_white_level;
	अचिन्हित पूर्णांक min_content; // luminance in 1/10000 nits
	अचिन्हित पूर्णांक max_content; // luminance in nits
	अचिन्हित पूर्णांक min_display; // luminance in 1/10000 nits
	अचिन्हित पूर्णांक max_display; // luminance in nits
	अचिन्हित पूर्णांक skip_पंचांग; // skip पंचांग
पूर्ण;

काष्ठा calculate_buffer अणु
	पूर्णांक buffer_index;
	काष्ठा fixed31_32 buffer[NUM_PTS_IN_REGION];
	काष्ठा fixed31_32 gamma_of_2;
पूर्ण;

काष्ठा translate_from_linear_space_args अणु
	काष्ठा fixed31_32 arg;
	काष्ठा fixed31_32 a0;
	काष्ठा fixed31_32 a1;
	काष्ठा fixed31_32 a2;
	काष्ठा fixed31_32 a3;
	काष्ठा fixed31_32 gamma;
	काष्ठा calculate_buffer *cal_buffer;
पूर्ण;

व्योम setup_x_poपूर्णांकs_distribution(व्योम);
व्योम log_x_poपूर्णांकs_distribution(काष्ठा dal_logger *logger);
व्योम precompute_pq(व्योम);
व्योम precompute_de_pq(व्योम);

bool mod_color_calculate_regamma_params(काष्ठा dc_transfer_func *output_tf,
		स्थिर काष्ठा dc_gamma *ramp, bool mapUserRamp, bool canRomBeUsed,
		स्थिर काष्ठा hdr_पंचांग_params *fs_params,
		काष्ठा calculate_buffer *cal_buffer);

bool mod_color_calculate_degamma_params(काष्ठा dc_color_caps *dc_caps,
		काष्ठा dc_transfer_func *output_tf,
		स्थिर काष्ठा dc_gamma *ramp, bool mapUserRamp);

bool mod_color_calculate_degamma_curve(क्रमागत dc_transfer_func_predefined trans,
				काष्ठा dc_transfer_func_distributed_poपूर्णांकs *poपूर्णांकs);

bool calculate_user_regamma_coeff(काष्ठा dc_transfer_func *output_tf,
		स्थिर काष्ठा regamma_lut *regamma,
		काष्ठा calculate_buffer *cal_buffer,
		स्थिर काष्ठा dc_gamma *ramp);

bool calculate_user_regamma_ramp(काष्ठा dc_transfer_func *output_tf,
		स्थिर काष्ठा regamma_lut *regamma,
		काष्ठा calculate_buffer *cal_buffer,
		स्थिर काष्ठा dc_gamma *ramp);


#पूर्ण_अगर /* COLOR_MOD_COLOR_GAMMA_H_ */
