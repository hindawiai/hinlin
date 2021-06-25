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

#अगर_अघोषित __DAL_GPIO_SERVICE_INTERFACE_H__
#घोषणा __DAL_GPIO_SERVICE_INTERFACE_H__

#समावेश "gpio_types.h"
#समावेश "gpio_interface.h"
#समावेश "hw/gpio.h"

काष्ठा gpio_service;

काष्ठा gpio *dal_gpio_create(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	क्रमागत gpio_pin_output_state output_state);

व्योम dal_gpio_destroy(
	काष्ठा gpio **ptr);

काष्ठा gpio_service *dal_gpio_service_create(
	क्रमागत dce_version dce_version_major,
	क्रमागत dce_version dce_version_minor,
	काष्ठा dc_context *ctx);

काष्ठा gpio *dal_gpio_service_create_irq(
	काष्ठा gpio_service *service,
	uपूर्णांक32_t offset,
	uपूर्णांक32_t mask);

काष्ठा gpio *dal_gpio_service_create_generic_mux(
	काष्ठा gpio_service *service,
	uपूर्णांक32_t offset,
	uपूर्णांक32_t mask);

व्योम dal_gpio_destroy_generic_mux(
	काष्ठा gpio **mux);

क्रमागत gpio_result dal_mux_setup_config(
	काष्ठा gpio *mux,
	काष्ठा gpio_generic_mux_config *config);

काष्ठा gpio_pin_info dal_gpio_get_generic_pin_info(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en);

काष्ठा ddc *dal_gpio_create_ddc(
	काष्ठा gpio_service *service,
	uपूर्णांक32_t offset,
	uपूर्णांक32_t mask,
	काष्ठा gpio_ddc_hw_info *info);

व्योम dal_gpio_destroy_ddc(
	काष्ठा ddc **ddc);

व्योम dal_gpio_service_destroy(
	काष्ठा gpio_service **ptr);

क्रमागत dc_irq_source dal_irq_get_source(
	स्थिर काष्ठा gpio *irq);

क्रमागत dc_irq_source dal_irq_get_rx_source(
	स्थिर काष्ठा gpio *irq);

क्रमागत gpio_result dal_irq_setup_hpd_filter(
	काष्ठा gpio *irq,
	काष्ठा gpio_hpd_config *config);

काष्ठा gpio *dal_gpio_create_irq(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en);

व्योम dal_gpio_destroy_irq(
	काष्ठा gpio **ptr);


क्रमागत gpio_result dal_ddc_खोलो(
	काष्ठा ddc *ddc,
	क्रमागत gpio_mode mode,
	क्रमागत gpio_ddc_config_type config_type);

क्रमागत gpio_result dal_ddc_change_mode(
	काष्ठा ddc *ddc,
	क्रमागत gpio_mode mode);

क्रमागत gpio_ddc_line dal_ddc_get_line(
	स्थिर काष्ठा ddc *ddc);

क्रमागत gpio_result dal_ddc_set_config(
	काष्ठा ddc *ddc,
	क्रमागत gpio_ddc_config_type config_type);

व्योम dal_ddc_बंद(
	काष्ठा ddc *ddc);

#पूर्ण_अगर
