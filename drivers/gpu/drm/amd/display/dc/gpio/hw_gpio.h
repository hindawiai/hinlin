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

#अगर_अघोषित __DAL_HW_GPIO_H__
#घोषणा __DAL_HW_GPIO_H__

#समावेश "gpio_regs.h"

#घोषणा FROM_HW_GPIO_PIN(ptr) \
	container_of((ptr), काष्ठा hw_gpio, base)

काष्ठा addr_mask अणु
	uपूर्णांक32_t addr;
	uपूर्णांक32_t mask;
पूर्ण;

काष्ठा hw_gpio_pin अणु
	स्थिर काष्ठा hw_gpio_pin_funcs *funcs;
	क्रमागत gpio_id id;
	uपूर्णांक32_t en;
	क्रमागत gpio_mode mode;
	bool खोलोed;
	काष्ठा dc_context *ctx;
पूर्ण;

काष्ठा hw_gpio_pin_funcs अणु
	व्योम (*destroy)(
		काष्ठा hw_gpio_pin **ptr);
	bool (*खोलो)(
		काष्ठा hw_gpio_pin *pin,
		क्रमागत gpio_mode mode);
	क्रमागत gpio_result (*get_value)(
		स्थिर काष्ठा hw_gpio_pin *pin,
		uपूर्णांक32_t *value);
	क्रमागत gpio_result (*set_value)(
		स्थिर काष्ठा hw_gpio_pin *pin,
		uपूर्णांक32_t value);
	क्रमागत gpio_result (*set_config)(
		काष्ठा hw_gpio_pin *pin,
		स्थिर काष्ठा gpio_config_data *config_data);
	क्रमागत gpio_result (*change_mode)(
		काष्ठा hw_gpio_pin *pin,
		क्रमागत gpio_mode mode);
	व्योम (*बंद)(
		काष्ठा hw_gpio_pin *pin);
पूर्ण;


काष्ठा hw_gpio;

/* Register indices are represented by member variables
 * and are to be filled in by स्थिरructors of derived classes.
 * These members permit the use of common code
 * क्रम programming रेजिस्टरs, where the sequence is the same
 * but रेजिस्टर sets are dअगरferent.
 * Some GPIOs have HW mux which allows to choose
 * what is the source of the संकेत in HW mode */

काष्ठा hw_gpio_pin_reg अणु
	काष्ठा addr_mask DC_GPIO_DATA_MASK;
	काष्ठा addr_mask DC_GPIO_DATA_A;
	काष्ठा addr_mask DC_GPIO_DATA_EN;
	काष्ठा addr_mask DC_GPIO_DATA_Y;
पूर्ण;

काष्ठा hw_gpio_mux_reg अणु
	काष्ठा addr_mask GPIO_MUX_CONTROL;
	काष्ठा addr_mask GPIO_MUX_STEREO_SEL;
पूर्ण;

काष्ठा hw_gpio अणु
	काष्ठा hw_gpio_pin base;

	/* variables to save रेजिस्टर value */
	काष्ठा अणु
		uपूर्णांक32_t mask;
		uपूर्णांक32_t a;
		uपूर्णांक32_t en;
		uपूर्णांक32_t mux;
	पूर्ण store;

	/* GPIO MUX support */
	bool mux_supported;
	स्थिर काष्ठा gpio_रेजिस्टरs *regs;
पूर्ण;

#घोषणा HW_GPIO_FROM_BASE(hw_gpio_pin) \
	container_of((hw_gpio_pin), काष्ठा hw_gpio, base)

व्योम dal_hw_gpio_स्थिरruct(
	काष्ठा hw_gpio *pin,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	काष्ठा dc_context *ctx);

bool dal_hw_gpio_खोलो(
	काष्ठा hw_gpio_pin *pin,
	क्रमागत gpio_mode mode);

क्रमागत gpio_result dal_hw_gpio_get_value(
	स्थिर काष्ठा hw_gpio_pin *pin,
	uपूर्णांक32_t *value);

क्रमागत gpio_result dal_hw_gpio_config_mode(
	काष्ठा hw_gpio *pin,
	क्रमागत gpio_mode mode);

व्योम dal_hw_gpio_deकाष्ठा(
	काष्ठा hw_gpio *pin);

क्रमागत gpio_result dal_hw_gpio_set_value(
	स्थिर काष्ठा hw_gpio_pin *ptr,
	uपूर्णांक32_t value);

क्रमागत gpio_result dal_hw_gpio_change_mode(
	काष्ठा hw_gpio_pin *ptr,
	क्रमागत gpio_mode mode);

व्योम dal_hw_gpio_बंद(
	काष्ठा hw_gpio_pin *ptr);

#पूर्ण_अगर
