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
#समावेश "hw_hpd.h"

#समावेश "reg_helper.h"
#समावेश "hpd_regs.h"

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	hpd->shअगरts->field_name, hpd->masks->field_name

#घोषणा CTX \
	hpd->base.base.ctx
#घोषणा REG(reg)\
	(hpd->regs->reg)

काष्ठा gpio;

अटल व्योम dal_hw_hpd_deकाष्ठा(
	काष्ठा hw_hpd *pin)
अणु
	dal_hw_gpio_deकाष्ठा(&pin->base);
पूर्ण

अटल व्योम dal_hw_hpd_destroy(
	काष्ठा hw_gpio_pin **ptr)
अणु
	काष्ठा hw_hpd *hpd = HW_HPD_FROM_BASE(*ptr);

	dal_hw_hpd_deकाष्ठा(hpd);

	kमुक्त(hpd);

	*ptr = शून्य;
पूर्ण

अटल क्रमागत gpio_result get_value(
	स्थिर काष्ठा hw_gpio_pin *ptr,
	uपूर्णांक32_t *value)
अणु
	काष्ठा hw_hpd *hpd = HW_HPD_FROM_BASE(ptr);
	uपूर्णांक32_t hpd_delayed = 0;

	/* in Interrupt mode we ask क्रम SENSE bit */

	अगर (ptr->mode == GPIO_MODE_INTERRUPT) अणु

		REG_GET(पूर्णांक_status,
			DC_HPD_SENSE_DELAYED, &hpd_delayed);

		*value = hpd_delayed;
		वापस GPIO_RESULT_OK;
	पूर्ण

	/* in any other modes, operate as normal GPIO */

	वापस dal_hw_gpio_get_value(ptr, value);
पूर्ण

अटल क्रमागत gpio_result set_config(
	काष्ठा hw_gpio_pin *ptr,
	स्थिर काष्ठा gpio_config_data *config_data)
अणु
	काष्ठा hw_hpd *hpd = HW_HPD_FROM_BASE(ptr);

	अगर (!config_data)
		वापस GPIO_RESULT_INVALID_DATA;

	REG_UPDATE_2(toggle_filt_cntl,
		DC_HPD_CONNECT_INT_DELAY, config_data->config.hpd.delay_on_connect / 10,
		DC_HPD_DISCONNECT_INT_DELAY, config_data->config.hpd.delay_on_disconnect / 10);

	वापस GPIO_RESULT_OK;
पूर्ण

अटल स्थिर काष्ठा hw_gpio_pin_funcs funcs = अणु
	.destroy = dal_hw_hpd_destroy,
	.खोलो = dal_hw_gpio_खोलो,
	.get_value = get_value,
	.set_value = dal_hw_gpio_set_value,
	.set_config = set_config,
	.change_mode = dal_hw_gpio_change_mode,
	.बंद = dal_hw_gpio_बंद,
पूर्ण;

अटल व्योम dal_hw_hpd_स्थिरruct(
	काष्ठा hw_hpd *pin,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	काष्ठा dc_context *ctx)
अणु
	dal_hw_gpio_स्थिरruct(&pin->base, id, en, ctx);
	pin->base.base.funcs = &funcs;
पूर्ण

व्योम dal_hw_hpd_init(
	काष्ठा hw_hpd **hw_hpd,
	काष्ठा dc_context *ctx,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	अगर ((en < GPIO_DDC_LINE_MIN) || (en > GPIO_DDC_LINE_MAX)) अणु
		ASSERT_CRITICAL(false);
		*hw_hpd = शून्य;
	पूर्ण

	*hw_hpd = kzalloc(माप(काष्ठा hw_hpd), GFP_KERNEL);
	अगर (!*hw_hpd) अणु
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	dal_hw_hpd_स्थिरruct(*hw_hpd, id, en, ctx);
पूर्ण

काष्ठा hw_gpio_pin *dal_hw_hpd_get_pin(काष्ठा gpio *gpio)
अणु
	काष्ठा hw_hpd *hw_hpd = dal_gpio_get_hpd(gpio);

	वापस &hw_hpd->base.base;
पूर्ण
