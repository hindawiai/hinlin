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
#अगर_अघोषित LUTS_1D_H
#घोषणा LUTS_1D_H

#समावेश "hw_shared.h"

काष्ठा poपूर्णांक_config अणु
	uपूर्णांक32_t custom_भग्न_x;
	uपूर्णांक32_t custom_भग्न_y;
	uपूर्णांक32_t custom_भग्न_slope;
पूर्ण;

काष्ठा lut_poपूर्णांक अणु
	uपूर्णांक32_t red;
	uपूर्णांक32_t green;
	uपूर्णांक32_t blue;
	uपूर्णांक32_t delta_red;
	uपूर्णांक32_t delta_green;
	uपूर्णांक32_t delta_blue;
पूर्ण;

काष्ठा pwl_1dlut_parameter अणु
	काष्ठा gamma_curve	arr_curve_poपूर्णांकs[34];
	काष्ठा poपूर्णांक_config	arr_poपूर्णांकs[2];
	काष्ठा lut_poपूर्णांक rgb_resulted[256];
	uपूर्णांक32_t hw_poपूर्णांकs_num;
पूर्ण;
#पूर्ण_अगर // LUTS_1D_H
