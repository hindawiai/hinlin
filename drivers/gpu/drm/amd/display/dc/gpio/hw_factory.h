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

#अगर_अघोषित __DAL_HW_FACTORY_H__
#घोषणा __DAL_HW_FACTORY_H__

काष्ठा hw_gpio_pin;
काष्ठा hw_hpd;
काष्ठा hw_ddc;
काष्ठा hw_generic;
काष्ठा gpio;

काष्ठा hw_factory अणु
	uपूर्णांक32_t number_of_pins[GPIO_ID_COUNT];

	स्थिर काष्ठा hw_factory_funcs अणु
		व्योम (*init_ddc_data)(
				काष्ठा hw_ddc **hw_ddc,
				काष्ठा dc_context *ctx,
				क्रमागत gpio_id id,
				uपूर्णांक32_t en);
		व्योम (*init_generic)(
				काष्ठा hw_generic **hw_generic,
				काष्ठा dc_context *ctx,
				क्रमागत gpio_id id,
				uपूर्णांक32_t en);
		व्योम (*init_hpd)(
				काष्ठा hw_hpd **hw_hpd,
				काष्ठा dc_context *ctx,
				क्रमागत gpio_id id,
				uपूर्णांक32_t en);
		काष्ठा hw_gpio_pin *(*get_hpd_pin)(
				काष्ठा gpio *gpio);
		काष्ठा hw_gpio_pin *(*get_ddc_pin)(
				काष्ठा gpio *gpio);
		काष्ठा hw_gpio_pin *(*get_generic_pin)(
				काष्ठा gpio *gpio);
		व्योम (*define_hpd_रेजिस्टरs)(
				काष्ठा hw_gpio_pin *pin,
				uपूर्णांक32_t en);
		व्योम (*define_ddc_रेजिस्टरs)(
				काष्ठा hw_gpio_pin *pin,
				uपूर्णांक32_t en);
		व्योम (*define_generic_रेजिस्टरs)(
				काष्ठा hw_gpio_pin *pin,
				uपूर्णांक32_t en);
	पूर्ण *funcs;
पूर्ण;

bool dal_hw_factory_init(
	काष्ठा hw_factory *factory,
	क्रमागत dce_version dce_version,
	क्रमागत dce_environment dce_environment);

#पूर्ण_अगर
