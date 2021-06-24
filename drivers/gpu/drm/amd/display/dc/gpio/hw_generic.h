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

#अगर_अघोषित __DAL_HW_generic_H__
#घोषणा __DAL_HW_generic_H__

#समावेश "generic_regs.h"
#समावेश "hw_gpio.h"

काष्ठा hw_generic अणु
	काष्ठा hw_gpio base;
	स्थिर काष्ठा generic_रेजिस्टरs *regs;
	स्थिर काष्ठा generic_sh_mask *shअगरts;
	स्थिर काष्ठा generic_sh_mask *masks;
पूर्ण;

#घोषणा HW_GENERIC_FROM_BASE(hw_gpio) \
	container_of((HW_GPIO_FROM_BASE(hw_gpio)), काष्ठा hw_generic, base)

व्योम dal_hw_generic_init(
	काष्ठा hw_generic **hw_generic,
	काष्ठा dc_context *ctx,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en);

काष्ठा hw_gpio_pin *dal_hw_generic_get_pin(काष्ठा gpio *gpio);

#पूर्ण_अगर
