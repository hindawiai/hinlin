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

#अगर_अघोषित __DAL_GPIO_INTERFACE_H__
#घोषणा __DAL_GPIO_INTERFACE_H__

#समावेश "gpio_types.h"
#समावेश "grph_object_defs.h"

काष्ठा gpio;

/* Open the handle क्रम future use */
क्रमागत gpio_result dal_gpio_खोलो(
	काष्ठा gpio *gpio,
	क्रमागत gpio_mode mode);

क्रमागत gpio_result dal_gpio_खोलो_ex(
	काष्ठा gpio *gpio,
	क्रमागत gpio_mode mode);

/* Get high or low from the pin */
क्रमागत gpio_result dal_gpio_get_value(
	स्थिर काष्ठा gpio *gpio,
	uपूर्णांक32_t *value);

/* Set pin high or low */
क्रमागत gpio_result dal_gpio_set_value(
	स्थिर काष्ठा gpio *gpio,
	uपूर्णांक32_t value);

/* Get current mode */
क्रमागत gpio_mode dal_gpio_get_mode(
	स्थिर काष्ठा gpio *gpio);

/* Change mode of the handle */
क्रमागत gpio_result dal_gpio_change_mode(
	काष्ठा gpio *gpio,
	क्रमागत gpio_mode mode);

/* Lock Pin */
क्रमागत gpio_result dal_gpio_lock_pin(
	काष्ठा gpio *gpio);

/* Unlock Pin */
क्रमागत gpio_result dal_gpio_unlock_pin(
	काष्ठा gpio *gpio);

/* Get the GPIO id */
क्रमागत gpio_id dal_gpio_get_id(
	स्थिर काष्ठा gpio *gpio);

/* Get the GPIO क्रमागत */
uपूर्णांक32_t dal_gpio_get_क्रमागत(
	स्थिर काष्ठा gpio *gpio);

/* Set the GPIO pin configuration */
क्रमागत gpio_result dal_gpio_set_config(
	काष्ठा gpio *gpio,
	स्थिर काष्ठा gpio_config_data *config_data);

/* Obtain GPIO pin info */
क्रमागत gpio_result dal_gpio_get_pin_info(
	स्थिर काष्ठा gpio *gpio,
	काष्ठा gpio_pin_info *pin_info);

/* Obtain GPIO sync source */
क्रमागत sync_source dal_gpio_get_sync_source(
	स्थिर काष्ठा gpio *gpio);

/* Obtain GPIO pin output state (active low or active high) */
क्रमागत gpio_pin_output_state dal_gpio_get_output_state(
	स्थिर काष्ठा gpio *gpio);

काष्ठा hw_ddc *dal_gpio_get_ddc(काष्ठा gpio *gpio);

काष्ठा hw_hpd *dal_gpio_get_hpd(काष्ठा gpio *gpio);

काष्ठा hw_generic *dal_gpio_get_generic(काष्ठा gpio *gpio);

/* Close the handle */
व्योम dal_gpio_बंद(
	काष्ठा gpio *gpio);




#पूर्ण_अगर
