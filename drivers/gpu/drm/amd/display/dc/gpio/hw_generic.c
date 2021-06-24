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

#समावेश <linux/slab.h>

#समावेश "dm_services.h"

#समावेश "include/gpio_interface.h"
#समावेश "include/gpio_types.h"
#समावेश "hw_gpio.h"
#समावेश "hw_generic.h"

#समावेश "reg_helper.h"
#समावेश "generic_regs.h"

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	generic->shअगरts->field_name, generic->masks->field_name

#घोषणा CTX \
	generic->base.base.ctx
#घोषणा REG(reg)\
	(generic->regs->reg)

काष्ठा gpio;

अटल व्योम dal_hw_generic_deकाष्ठा(
	काष्ठा hw_generic *pin)
अणु
	dal_hw_gpio_deकाष्ठा(&pin->base);
पूर्ण

अटल व्योम dal_hw_generic_destroy(
	काष्ठा hw_gpio_pin **ptr)
अणु
	काष्ठा hw_generic *generic = HW_GENERIC_FROM_BASE(*ptr);

	dal_hw_generic_deकाष्ठा(generic);

	kमुक्त(generic);

	*ptr = शून्य;
पूर्ण

अटल क्रमागत gpio_result set_config(
	काष्ठा hw_gpio_pin *ptr,
	स्थिर काष्ठा gpio_config_data *config_data)
अणु
	काष्ठा hw_generic *generic = HW_GENERIC_FROM_BASE(ptr);

	अगर (!config_data)
		वापस GPIO_RESULT_INVALID_DATA;

	REG_UPDATE_2(mux,
		GENERIC_EN, config_data->config.generic_mux.enable_output_from_mux,
		GENERIC_SEL, config_data->config.generic_mux.mux_select);

	वापस GPIO_RESULT_OK;
पूर्ण

अटल स्थिर काष्ठा hw_gpio_pin_funcs funcs = अणु
	.destroy = dal_hw_generic_destroy,
	.खोलो = dal_hw_gpio_खोलो,
	.get_value = dal_hw_gpio_get_value,
	.set_value = dal_hw_gpio_set_value,
	.set_config = set_config,
	.change_mode = dal_hw_gpio_change_mode,
	.बंद = dal_hw_gpio_बंद,
पूर्ण;

अटल व्योम dal_hw_generic_स्थिरruct(
	काष्ठा hw_generic *pin,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	काष्ठा dc_context *ctx)
अणु
	dal_hw_gpio_स्थिरruct(&pin->base, id, en, ctx);
	pin->base.base.funcs = &funcs;
पूर्ण

व्योम dal_hw_generic_init(
	काष्ठा hw_generic **hw_generic,
	काष्ठा dc_context *ctx,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	अगर ((en < GPIO_DDC_LINE_MIN) || (en > GPIO_DDC_LINE_MAX)) अणु
		ASSERT_CRITICAL(false);
		*hw_generic = शून्य;
	पूर्ण

	*hw_generic = kzalloc(माप(काष्ठा hw_generic), GFP_KERNEL);
	अगर (!*hw_generic) अणु
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	dal_hw_generic_स्थिरruct(*hw_generic, id, en, ctx);
पूर्ण


काष्ठा hw_gpio_pin *dal_hw_generic_get_pin(काष्ठा gpio *gpio)
अणु
	काष्ठा hw_generic *hw_generic = dal_gpio_get_generic(gpio);

	वापस &hw_generic->base.base;
पूर्ण
