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

#अगर_अघोषित __DAL_CONVERSION_H__
#घोषणा __DAL_CONVERSION_H__

#समावेश "include/fixed31_32.h"

uपूर्णांक16_t fixed_poपूर्णांक_to_पूर्णांक_frac(
	काष्ठा fixed31_32 arg,
	uपूर्णांक8_t पूर्णांकeger_bits,
	uपूर्णांक8_t fractional_bits);

व्योम convert_भग्न_matrix(
	uपूर्णांक16_t *matrix,
	काष्ठा fixed31_32 *flt,
	uपूर्णांक32_t buffer_size);

अटल अंतरभूत अचिन्हित पूर्णांक log_2(अचिन्हित पूर्णांक num)
अणु
	वापस ilog2(num);
पूर्ण

#पूर्ण_अगर
