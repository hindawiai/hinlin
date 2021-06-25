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

/*
 * Pre-requisites: headers required by header of this unit
 */

#समावेश <linux/slab.h>

#समावेश "dm_services.h"

#समावेश "include/gpio_interface.h"
#समावेश "include/gpio_service_interface.h"
#समावेश "hw_gpio.h"
#समावेश "hw_translate.h"
#समावेश "hw_factory.h"
#समावेश "gpio_service.h"

/*
 * Post-requisites: headers required by this unit
 */

/*
 * This unit
 */

/*
 * @brief
 * Public API
 */

क्रमागत gpio_result dal_gpio_खोलो(
	काष्ठा gpio *gpio,
	क्रमागत gpio_mode mode)
अणु
	वापस dal_gpio_खोलो_ex(gpio, mode);
पूर्ण

क्रमागत gpio_result dal_gpio_खोलो_ex(
	काष्ठा gpio *gpio,
	क्रमागत gpio_mode mode)
अणु
	अगर (gpio->pin) अणु
		BREAK_TO_DEBUGGER();
		वापस GPIO_RESULT_ALREADY_OPENED;
	पूर्ण

	// No action अगर allocation failed during gpio स्थिरruct
	अगर (!gpio->hw_container.ddc) अणु
		BREAK_TO_DEBUGGER();
		वापस GPIO_RESULT_NON_SPECIFIC_ERROR;
	पूर्ण
	gpio->mode = mode;

	वापस dal_gpio_service_खोलो(gpio);
पूर्ण

क्रमागत gpio_result dal_gpio_get_value(
	स्थिर काष्ठा gpio *gpio,
	uपूर्णांक32_t *value)
अणु
	अगर (!gpio->pin) अणु
		BREAK_TO_DEBUGGER();
		वापस GPIO_RESULT_शून्य_HANDLE;
	पूर्ण

	वापस gpio->pin->funcs->get_value(gpio->pin, value);
पूर्ण

क्रमागत gpio_result dal_gpio_set_value(
	स्थिर काष्ठा gpio *gpio,
	uपूर्णांक32_t value)
अणु
	अगर (!gpio->pin) अणु
		BREAK_TO_DEBUGGER();
		वापस GPIO_RESULT_शून्य_HANDLE;
	पूर्ण

	वापस gpio->pin->funcs->set_value(gpio->pin, value);
पूर्ण

क्रमागत gpio_mode dal_gpio_get_mode(
	स्थिर काष्ठा gpio *gpio)
अणु
	वापस gpio->mode;
पूर्ण

क्रमागत gpio_result dal_gpio_lock_pin(
	काष्ठा gpio *gpio)
अणु
	वापस dal_gpio_service_lock(gpio->service, gpio->id, gpio->en);
पूर्ण

क्रमागत gpio_result dal_gpio_unlock_pin(
	काष्ठा gpio *gpio)
अणु
	वापस dal_gpio_service_unlock(gpio->service, gpio->id, gpio->en);
पूर्ण

क्रमागत gpio_result dal_gpio_change_mode(
	काष्ठा gpio *gpio,
	क्रमागत gpio_mode mode)
अणु
	अगर (!gpio->pin) अणु
		BREAK_TO_DEBUGGER();
		वापस GPIO_RESULT_शून्य_HANDLE;
	पूर्ण

	वापस gpio->pin->funcs->change_mode(gpio->pin, mode);
पूर्ण

क्रमागत gpio_id dal_gpio_get_id(
	स्थिर काष्ठा gpio *gpio)
अणु
	वापस gpio->id;
पूर्ण

uपूर्णांक32_t dal_gpio_get_क्रमागत(
	स्थिर काष्ठा gpio *gpio)
अणु
	वापस gpio->en;
पूर्ण

क्रमागत gpio_result dal_gpio_set_config(
	काष्ठा gpio *gpio,
	स्थिर काष्ठा gpio_config_data *config_data)
अणु
	अगर (!gpio->pin) अणु
		BREAK_TO_DEBUGGER();
		वापस GPIO_RESULT_शून्य_HANDLE;
	पूर्ण

	वापस gpio->pin->funcs->set_config(gpio->pin, config_data);
पूर्ण

क्रमागत gpio_result dal_gpio_get_pin_info(
	स्थिर काष्ठा gpio *gpio,
	काष्ठा gpio_pin_info *pin_info)
अणु
	वापस gpio->service->translate.funcs->id_to_offset(
		gpio->id, gpio->en, pin_info) ?
		GPIO_RESULT_OK : GPIO_RESULT_INVALID_DATA;
पूर्ण

क्रमागत sync_source dal_gpio_get_sync_source(
	स्थिर काष्ठा gpio *gpio)
अणु
	चयन (gpio->id) अणु
	हाल GPIO_ID_GENERIC:
		चयन (gpio->en) अणु
		हाल GPIO_GENERIC_A:
			वापस SYNC_SOURCE_IO_GENERIC_A;
		हाल GPIO_GENERIC_B:
			वापस SYNC_SOURCE_IO_GENERIC_B;
		हाल GPIO_GENERIC_C:
			वापस SYNC_SOURCE_IO_GENERIC_C;
		हाल GPIO_GENERIC_D:
			वापस SYNC_SOURCE_IO_GENERIC_D;
		हाल GPIO_GENERIC_E:
			वापस SYNC_SOURCE_IO_GENERIC_E;
		हाल GPIO_GENERIC_F:
			वापस SYNC_SOURCE_IO_GENERIC_F;
		शेष:
			वापस SYNC_SOURCE_NONE;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_SYNC:
		चयन (gpio->en) अणु
		हाल GPIO_SYNC_HSYNC_A:
			वापस SYNC_SOURCE_IO_HSYNC_A;
		हाल GPIO_SYNC_VSYNC_A:
			वापस SYNC_SOURCE_IO_VSYNC_A;
		हाल GPIO_SYNC_HSYNC_B:
			वापस SYNC_SOURCE_IO_HSYNC_B;
		हाल GPIO_SYNC_VSYNC_B:
			वापस SYNC_SOURCE_IO_VSYNC_B;
		शेष:
			वापस SYNC_SOURCE_NONE;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_HPD:
		चयन (gpio->en) अणु
		हाल GPIO_HPD_1:
			वापस SYNC_SOURCE_IO_HPD1;
		हाल GPIO_HPD_2:
			वापस SYNC_SOURCE_IO_HPD2;
		शेष:
			वापस SYNC_SOURCE_NONE;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_GSL:
		चयन (gpio->en) अणु
		हाल GPIO_GSL_GENLOCK_CLOCK:
			वापस SYNC_SOURCE_GSL_IO_GENLOCK_CLOCK;
		हाल GPIO_GSL_GENLOCK_VSYNC:
			वापस SYNC_SOURCE_GSL_IO_GENLOCK_VSYNC;
		हाल GPIO_GSL_SWAPLOCK_A:
			वापस SYNC_SOURCE_GSL_IO_SWAPLOCK_A;
		हाल GPIO_GSL_SWAPLOCK_B:
			वापस SYNC_SOURCE_GSL_IO_SWAPLOCK_B;
		शेष:
			वापस SYNC_SOURCE_NONE;
		पूर्ण
	अवरोध;
	शेष:
		वापस SYNC_SOURCE_NONE;
	पूर्ण
पूर्ण

क्रमागत gpio_pin_output_state dal_gpio_get_output_state(
	स्थिर काष्ठा gpio *gpio)
अणु
	वापस gpio->output_state;
पूर्ण

काष्ठा hw_ddc *dal_gpio_get_ddc(काष्ठा gpio *gpio)
अणु
	वापस gpio->hw_container.ddc;
पूर्ण

काष्ठा hw_hpd *dal_gpio_get_hpd(काष्ठा gpio *gpio)
अणु
	वापस gpio->hw_container.hpd;
पूर्ण

काष्ठा hw_generic *dal_gpio_get_generic(काष्ठा gpio *gpio)
अणु
	वापस gpio->hw_container.generic;
पूर्ण

व्योम dal_gpio_बंद(
	काष्ठा gpio *gpio)
अणु
	अगर (!gpio)
		वापस;

	dal_gpio_service_बंद(gpio->service, &gpio->pin);

	gpio->mode = GPIO_MODE_UNKNOWN;
पूर्ण

/*
 * @brief
 * Creation and deकाष्ठाion
 */

काष्ठा gpio *dal_gpio_create(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	क्रमागत gpio_pin_output_state output_state)
अणु
	काष्ठा gpio *gpio = kzalloc(माप(काष्ठा gpio), GFP_KERNEL);

	अगर (!gpio) अणु
		ASSERT_CRITICAL(false);
		वापस शून्य;
	पूर्ण

	gpio->service = service;
	gpio->pin = शून्य;
	gpio->id = id;
	gpio->en = en;
	gpio->mode = GPIO_MODE_UNKNOWN;
	gpio->output_state = output_state;

	//initialize hw_container जोड़ based on id
	चयन (gpio->id) अणु
	हाल GPIO_ID_DDC_DATA:
		gpio->service->factory.funcs->init_ddc_data(&gpio->hw_container.ddc, service->ctx, id, en);
		अवरोध;
	हाल GPIO_ID_DDC_CLOCK:
		gpio->service->factory.funcs->init_ddc_data(&gpio->hw_container.ddc, service->ctx, id, en);
		अवरोध;
	हाल GPIO_ID_GENERIC:
		gpio->service->factory.funcs->init_generic(&gpio->hw_container.generic, service->ctx, id, en);
		अवरोध;
	हाल GPIO_ID_HPD:
		gpio->service->factory.funcs->init_hpd(&gpio->hw_container.hpd, service->ctx, id, en);
		अवरोध;
	// TODO: currently gpio क्रम sync and gsl करोes not get created, might need it later
	हाल GPIO_ID_SYNC:
		अवरोध;
	हाल GPIO_ID_GSL:
		अवरोध;
	शेष:
		ASSERT_CRITICAL(false);
		gpio->pin = शून्य;
	पूर्ण

	वापस gpio;
पूर्ण

व्योम dal_gpio_destroy(
	काष्ठा gpio **gpio)
अणु
	अगर (!gpio || !*gpio) अणु
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	चयन ((*gpio)->id) अणु
	हाल GPIO_ID_DDC_DATA:
		kमुक्त((*gpio)->hw_container.ddc);
		(*gpio)->hw_container.ddc = शून्य;
		अवरोध;
	हाल GPIO_ID_DDC_CLOCK:
		//TODO: might want to change it to init_ddc_घड़ी
		kमुक्त((*gpio)->hw_container.ddc);
		(*gpio)->hw_container.ddc = शून्य;
		अवरोध;
	हाल GPIO_ID_GENERIC:
		kमुक्त((*gpio)->hw_container.generic);
		(*gpio)->hw_container.generic = शून्य;
		अवरोध;
	हाल GPIO_ID_HPD:
		kमुक्त((*gpio)->hw_container.hpd);
		(*gpio)->hw_container.hpd = शून्य;
		अवरोध;
	// TODO: currently gpio क्रम sync and gsl करोes not get created, might need it later
	हाल GPIO_ID_SYNC:
		अवरोध;
	हाल GPIO_ID_GSL:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	kमुक्त(*gpio);

	*gpio = शून्य;
पूर्ण
