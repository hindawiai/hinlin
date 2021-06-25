<शैली गुरु>
/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
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

#अगर_अघोषित __DAL_GPIO_H__
#घोषणा __DAL_GPIO_H__

#समावेश "gpio_types.h"


जोड़ gpio_hw_container अणु
	काष्ठा hw_ddc *ddc;
	काष्ठा hw_generic *generic;
	काष्ठा hw_hpd *hpd;
पूर्ण;

काष्ठा gpio अणु
	काष्ठा gpio_service *service;
	काष्ठा hw_gpio_pin *pin;
	क्रमागत gpio_id id;
	uपूर्णांक32_t en;

	जोड़ gpio_hw_container hw_container;
	क्रमागत gpio_mode mode;

	/* when GPIO comes from VBIOS, it has defined output state */
	क्रमागत gpio_pin_output_state output_state;
पूर्ण;

#अगर 0
काष्ठा gpio_funcs अणु

	काष्ठा hw_gpio_pin *(*create_ddc_data)(
		काष्ठा dc_context *ctx,
		क्रमागत gpio_id id,
		uपूर्णांक32_t en);
	काष्ठा hw_gpio_pin *(*create_ddc_घड़ी)(
		काष्ठा dc_context *ctx,
		क्रमागत gpio_id id,
		uपूर्णांक32_t en);
	काष्ठा hw_gpio_pin *(*create_generic)(
		काष्ठा dc_context *ctx,
		क्रमागत gpio_id id,
		uपूर्णांक32_t en);
	काष्ठा hw_gpio_pin *(*create_hpd)(
		काष्ठा dc_context *ctx,
		क्रमागत gpio_id id,
		uपूर्णांक32_t en);
	काष्ठा hw_gpio_pin *(*create_gpio_pad)(
		काष्ठा dc_context *ctx,
		क्रमागत gpio_id id,
		uपूर्णांक32_t en);
	काष्ठा hw_gpio_pin *(*create_sync)(
		काष्ठा dc_context *ctx,
		क्रमागत gpio_id id,
		uपूर्णांक32_t en);
	काष्ठा hw_gpio_pin *(*create_gsl)(
		काष्ठा dc_context *ctx,
		क्रमागत gpio_id id,
		uपूर्णांक32_t en);

	/* HW translation */
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
#पूर्ण_अगर

#पूर्ण_अगर  /* __DAL_GPIO__ */
