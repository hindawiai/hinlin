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

#अगर_अघोषित __DAL_HW_TRANSLATE_H__
#घोषणा __DAL_HW_TRANSLATE_H__

काष्ठा hw_translate_funcs अणु
	bool (*offset_to_id)(
		uपूर्णांक32_t offset,
		uपूर्णांक32_t mask,
		क्रमागत gpio_id *id,
		uपूर्णांक32_t *en);
	bool (*id_to_offset)(
		क्रमागत gpio_id id,
		uपूर्णांक32_t en,
		काष्ठा gpio_pin_info *info);
पूर्ण;

काष्ठा hw_translate अणु
	स्थिर काष्ठा hw_translate_funcs *funcs;
पूर्ण;

bool dal_hw_translate_init(
	काष्ठा hw_translate *translate,
	क्रमागत dce_version dce_version,
	क्रमागत dce_environment dce_environment);

#पूर्ण_अगर
