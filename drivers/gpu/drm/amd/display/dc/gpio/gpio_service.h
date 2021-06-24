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

#अगर_अघोषित __DAL_GPIO_SERVICE_H__
#घोषणा __DAL_GPIO_SERVICE_H__

काष्ठा hw_translate;
काष्ठा hw_factory;

काष्ठा gpio_service अणु
	काष्ठा dc_context *ctx;
	काष्ठा hw_translate translate;
	काष्ठा hw_factory factory;
	/*
	 * @brief
	 * Business storage.
	 * one byte For each member of 'enum gpio_id'
	 */
	अक्षर *busyness[GPIO_ID_COUNT];
पूर्ण;

क्रमागत gpio_result dal_gpio_service_खोलो(
	काष्ठा gpio *gpio);

व्योम dal_gpio_service_बंद(
	काष्ठा gpio_service *service,
	काष्ठा hw_gpio_pin **ptr);

क्रमागत gpio_result dal_gpio_service_lock(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en);

क्रमागत gpio_result dal_gpio_service_unlock(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en);

#पूर्ण_अगर
