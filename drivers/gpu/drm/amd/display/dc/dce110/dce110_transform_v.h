<शैली गुरु>
/* Copyright 2012-15 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_TRANSFORM_V_DCE110_H__
#घोषणा __DAL_TRANSFORM_V_DCE110_H__

#समावेश "../dce/dce_transform.h"

#घोषणा LB_TOTAL_NUMBER_OF_ENTRIES 1712
#घोषणा LB_BITS_PER_ENTRY 144

bool dce110_transक्रमm_v_स्थिरruct(
	काष्ठा dce_transक्रमm *xfm110,
	काष्ठा dc_context *ctx);

व्योम dce110_opp_v_set_csc_शेष(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा शेष_adjusपंचांगent *शेष_adjust);

व्योम dce110_opp_v_set_csc_adjusपंचांगent(
		काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा out_csc_color_matrix *tbl_entry);


व्योम dce110_opp_program_regamma_pwl_v(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा pwl_params *params);

व्योम dce110_opp_घातer_on_regamma_lut_v(
	काष्ठा transक्रमm *xfm,
	bool घातer_on);

व्योम dce110_opp_set_regamma_mode_v(
	काष्ठा transक्रमm *xfm,
	क्रमागत opp_regamma mode);

#पूर्ण_अगर
