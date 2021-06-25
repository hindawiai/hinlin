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

#समावेश "dm_services.h"
#समावेश "include/gpio_types.h"
#समावेश "hw_gpio.h"

#समावेश "reg_helper.h"
#समावेश "gpio_regs.h"

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	gpio->regs->field_name ## _shअगरt, gpio->regs->field_name ## _mask

#घोषणा CTX \
	gpio->base.ctx
#घोषणा REG(reg)\
	(gpio->regs->reg)

अटल व्योम store_रेजिस्टरs(
	काष्ठा hw_gpio *gpio)
अणु
	REG_GET(MASK_reg, MASK, &gpio->store.mask);
	REG_GET(A_reg, A, &gpio->store.a);
	REG_GET(EN_reg, EN, &gpio->store.en);
	/* TODO store GPIO_MUX_CONTROL अगर we ever use it */
पूर्ण

अटल व्योम restore_रेजिस्टरs(
	काष्ठा hw_gpio *gpio)
अणु
	REG_UPDATE(MASK_reg, MASK, gpio->store.mask);
	REG_UPDATE(A_reg, A, gpio->store.a);
	REG_UPDATE(EN_reg, EN, gpio->store.en);
	/* TODO restore GPIO_MUX_CONTROL अगर we ever use it */
पूर्ण

bool dal_hw_gpio_खोलो(
	काष्ठा hw_gpio_pin *ptr,
	क्रमागत gpio_mode mode)
अणु
	काष्ठा hw_gpio *pin = FROM_HW_GPIO_PIN(ptr);

	store_रेजिस्टरs(pin);

	ptr->खोलोed = (dal_hw_gpio_config_mode(pin, mode) == GPIO_RESULT_OK);

	वापस ptr->खोलोed;
पूर्ण

क्रमागत gpio_result dal_hw_gpio_get_value(
	स्थिर काष्ठा hw_gpio_pin *ptr,
	uपूर्णांक32_t *value)
अणु
	स्थिर काष्ठा hw_gpio *gpio = FROM_HW_GPIO_PIN(ptr);

	क्रमागत gpio_result result = GPIO_RESULT_OK;

	चयन (ptr->mode) अणु
	हाल GPIO_MODE_INPUT:
	हाल GPIO_MODE_OUTPUT:
	हाल GPIO_MODE_HARDWARE:
	हाल GPIO_MODE_FAST_OUTPUT:
		REG_GET(Y_reg, Y, value);
		अवरोध;
	शेष:
		result = GPIO_RESULT_NON_SPECIFIC_ERROR;
	पूर्ण

	वापस result;
पूर्ण

क्रमागत gpio_result dal_hw_gpio_set_value(
	स्थिर काष्ठा hw_gpio_pin *ptr,
	uपूर्णांक32_t value)
अणु
	काष्ठा hw_gpio *gpio = FROM_HW_GPIO_PIN(ptr);

	/* This is the खुला पूर्णांकerface
	 * where the input comes from client, not shअगरted yet
	 * (because client करोes not know the shअगरts). */

	चयन (ptr->mode) अणु
	हाल GPIO_MODE_OUTPUT:
		REG_UPDATE(A_reg, A, value);
		वापस GPIO_RESULT_OK;
	हाल GPIO_MODE_FAST_OUTPUT:
		/* We use (EN) to faster चयन (used in DDC GPIO).
		 * So (A) is grounded, output is driven by (EN = 0)
		 * to pull the line करोwn (output == 0) and (EN=1)
		 * then output is tri-state */
		REG_UPDATE(EN_reg, EN, ~value);
		वापस GPIO_RESULT_OK;
	शेष:
		वापस GPIO_RESULT_NON_SPECIFIC_ERROR;
	पूर्ण
पूर्ण

क्रमागत gpio_result dal_hw_gpio_change_mode(
	काष्ठा hw_gpio_pin *ptr,
	क्रमागत gpio_mode mode)
अणु
	काष्ठा hw_gpio *pin = FROM_HW_GPIO_PIN(ptr);

	वापस dal_hw_gpio_config_mode(pin, mode);
पूर्ण

व्योम dal_hw_gpio_बंद(
	काष्ठा hw_gpio_pin *ptr)
अणु
	काष्ठा hw_gpio *pin = FROM_HW_GPIO_PIN(ptr);

	restore_रेजिस्टरs(pin);

	ptr->mode = GPIO_MODE_UNKNOWN;
	ptr->खोलोed = false;
पूर्ण

क्रमागत gpio_result dal_hw_gpio_config_mode(
	काष्ठा hw_gpio *gpio,
	क्रमागत gpio_mode mode)
अणु
	gpio->base.mode = mode;

	चयन (mode) अणु
	हाल GPIO_MODE_INPUT:
		/* turn off output enable, act as input pin;
		 * program the pin as GPIO, mask out संकेत driven by HW */
		REG_UPDATE(EN_reg, EN, 0);
		REG_UPDATE(MASK_reg, MASK, 1);
		वापस GPIO_RESULT_OK;
	हाल GPIO_MODE_OUTPUT:
		/* turn on output enable, act as output pin;
		 * program the pin as GPIO, mask out संकेत driven by HW */
		REG_UPDATE(A_reg, A, 0);
		REG_UPDATE(MASK_reg, MASK, 1);
		वापस GPIO_RESULT_OK;
	हाल GPIO_MODE_FAST_OUTPUT:
		/* grounding the A रेजिस्टर then use the EN रेजिस्टर bit
		 * will have faster effect on the rise समय */
		REG_UPDATE(A_reg, A, 0);
		REG_UPDATE(MASK_reg, MASK, 1);
		वापस GPIO_RESULT_OK;
	हाल GPIO_MODE_HARDWARE:
		/* program the pin as tri-state, pin is driven by HW */
		REG_UPDATE(MASK_reg, MASK, 0);
		वापस GPIO_RESULT_OK;
	हाल GPIO_MODE_INTERRUPT:
		/* Interrupt mode supported only by HPD (IrqGpio) pins. */
		REG_UPDATE(MASK_reg, MASK, 0);
		वापस GPIO_RESULT_OK;
	शेष:
		वापस GPIO_RESULT_NON_SPECIFIC_ERROR;
	पूर्ण
पूर्ण

व्योम dal_hw_gpio_स्थिरruct(
	काष्ठा hw_gpio *pin,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	काष्ठा dc_context *ctx)
अणु
	pin->base.ctx = ctx;
	pin->base.id = id;
	pin->base.en = en;
	pin->base.mode = GPIO_MODE_UNKNOWN;
	pin->base.खोलोed = false;

	pin->store.mask = 0;
	pin->store.a = 0;
	pin->store.en = 0;
	pin->store.mux = 0;

	pin->mux_supported = false;
पूर्ण

व्योम dal_hw_gpio_deकाष्ठा(
	काष्ठा hw_gpio *pin)
अणु
	ASSERT(!pin->base.खोलोed);
पूर्ण
