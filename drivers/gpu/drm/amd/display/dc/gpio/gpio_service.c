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
#समावेश "hw_translate.h"
#समावेश "hw_factory.h"

/*
 * Header of this unit
 */

#समावेश "gpio_service.h"

/*
 * Post-requisites: headers required by this unit
 */

#समावेश "hw_gpio.h"

/*
 * @brief
 * Public API.
 */

काष्ठा gpio_service *dal_gpio_service_create(
	क्रमागत dce_version dce_version_major,
	क्रमागत dce_version dce_version_minor,
	काष्ठा dc_context *ctx)
अणु
	काष्ठा gpio_service *service;
	uपूर्णांक32_t index_of_id;

	service = kzalloc(माप(काष्ठा gpio_service), GFP_KERNEL);

	अगर (!service) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	अगर (!dal_hw_translate_init(&service->translate, dce_version_major,
			dce_version_minor)) अणु
		BREAK_TO_DEBUGGER();
		जाओ failure_1;
	पूर्ण

	अगर (!dal_hw_factory_init(&service->factory, dce_version_major,
			dce_version_minor)) अणु
		BREAK_TO_DEBUGGER();
		जाओ failure_1;
	पूर्ण

	/* allocate and initialize busyness storage */
	अणु
		index_of_id = 0;
		service->ctx = ctx;

		करो अणु
			uपूर्णांक32_t number_of_bits =
				service->factory.number_of_pins[index_of_id];
			uपूर्णांक32_t i = 0;

			अगर (number_of_bits)  अणु
				service->busyness[index_of_id] =
					kसुस्मृति(number_of_bits, माप(अक्षर),
						GFP_KERNEL);

				अगर (!service->busyness[index_of_id]) अणु
					BREAK_TO_DEBUGGER();
					जाओ failure_2;
				पूर्ण

				करो अणु
					service->busyness[index_of_id][i] = 0;
					++i;
				पूर्ण जबतक (i < number_of_bits);
			पूर्ण अन्यथा अणु
				service->busyness[index_of_id] = शून्य;
			पूर्ण

			++index_of_id;
		पूर्ण जबतक (index_of_id < GPIO_ID_COUNT);
	पूर्ण

	वापस service;

failure_2:
	जबतक (index_of_id) अणु
		--index_of_id;
		kमुक्त(service->busyness[index_of_id]);
	पूर्ण

failure_1:
	kमुक्त(service);

	वापस शून्य;
पूर्ण

काष्ठा gpio *dal_gpio_service_create_irq(
	काष्ठा gpio_service *service,
	uपूर्णांक32_t offset,
	uपूर्णांक32_t mask)
अणु
	क्रमागत gpio_id id;
	uपूर्णांक32_t en;

	अगर (!service->translate.funcs->offset_to_id(offset, mask, &id, &en)) अणु
		ASSERT_CRITICAL(false);
		वापस शून्य;
	पूर्ण

	वापस dal_gpio_create_irq(service, id, en);
पूर्ण

काष्ठा gpio *dal_gpio_service_create_generic_mux(
	काष्ठा gpio_service *service,
	uपूर्णांक32_t offset,
	uपूर्णांक32_t mask)
अणु
	क्रमागत gpio_id id;
	uपूर्णांक32_t en;
	काष्ठा gpio *generic;

	अगर (!service->translate.funcs->offset_to_id(offset, mask, &id, &en)) अणु
		ASSERT_CRITICAL(false);
		वापस शून्य;
	पूर्ण

	generic = dal_gpio_create(
		service, id, en, GPIO_PIN_OUTPUT_STATE_DEFAULT);

	वापस generic;
पूर्ण

व्योम dal_gpio_destroy_generic_mux(
	काष्ठा gpio **mux)
अणु
	अगर (!mux || !*mux) अणु
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	dal_gpio_destroy(mux);
	kमुक्त(*mux);

	*mux = शून्य;
पूर्ण

काष्ठा gpio_pin_info dal_gpio_get_generic_pin_info(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	काष्ठा gpio_pin_info pin;

	अगर (service->translate.funcs->id_to_offset) अणु
		service->translate.funcs->id_to_offset(id, en, &pin);
	पूर्ण अन्यथा अणु
		pin.mask = 0xFFFFFFFF;
		pin.offset = 0xFFFFFFFF;
	पूर्ण

	वापस pin;
पूर्ण

व्योम dal_gpio_service_destroy(
	काष्ठा gpio_service **ptr)
अणु
	अगर (!ptr || !*ptr) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	/* मुक्त business storage */
	अणु
		uपूर्णांक32_t index_of_id = 0;

		करो अणु
			kमुक्त((*ptr)->busyness[index_of_id]);

			++index_of_id;
		पूर्ण जबतक (index_of_id < GPIO_ID_COUNT);
	पूर्ण

	kमुक्त(*ptr);

	*ptr = शून्य;
पूर्ण

क्रमागत gpio_result dal_mux_setup_config(
	काष्ठा gpio *mux,
	काष्ठा gpio_generic_mux_config *config)
अणु
	काष्ठा gpio_config_data config_data;

	अगर (!config)
		वापस GPIO_RESULT_INVALID_DATA;

	config_data.config.generic_mux = *config;
	config_data.type = GPIO_CONFIG_TYPE_GENERIC_MUX;

	वापस dal_gpio_set_config(mux, &config_data);
पूर्ण

/*
 * @brief
 * Private API.
 */

अटल bool is_pin_busy(
	स्थिर काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	वापस service->busyness[id][en];
पूर्ण

अटल व्योम set_pin_busy(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	service->busyness[id][en] = true;
पूर्ण

अटल व्योम set_pin_मुक्त(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	service->busyness[id][en] = false;
पूर्ण

क्रमागत gpio_result dal_gpio_service_lock(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	अगर (!service->busyness[id]) अणु
		ASSERT_CRITICAL(false);
		वापस GPIO_RESULT_OPEN_FAILED;
	पूर्ण

	set_pin_busy(service, id, en);
	वापस GPIO_RESULT_OK;
पूर्ण

क्रमागत gpio_result dal_gpio_service_unlock(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	अगर (!service->busyness[id]) अणु
		ASSERT_CRITICAL(false);
		वापस GPIO_RESULT_OPEN_FAILED;
	पूर्ण

	set_pin_मुक्त(service, id, en);
	वापस GPIO_RESULT_OK;
पूर्ण

क्रमागत gpio_result dal_gpio_service_खोलो(
	काष्ठा gpio *gpio)
अणु
	काष्ठा gpio_service *service = gpio->service;
	क्रमागत gpio_id id = gpio->id;
	uपूर्णांक32_t en = gpio->en;
	क्रमागत gpio_mode mode = gpio->mode;

	काष्ठा hw_gpio_pin **pin = &gpio->pin;


	अगर (!service->busyness[id]) अणु
		ASSERT_CRITICAL(false);
		वापस GPIO_RESULT_OPEN_FAILED;
	पूर्ण

	अगर (is_pin_busy(service, id, en)) अणु
		ASSERT_CRITICAL(false);
		वापस GPIO_RESULT_DEVICE_BUSY;
	पूर्ण

	चयन (id) अणु
	हाल GPIO_ID_DDC_DATA:
		*pin = service->factory.funcs->get_ddc_pin(gpio);
		service->factory.funcs->define_ddc_रेजिस्टरs(*pin, en);
	अवरोध;
	हाल GPIO_ID_DDC_CLOCK:
		*pin = service->factory.funcs->get_ddc_pin(gpio);
		service->factory.funcs->define_ddc_रेजिस्टरs(*pin, en);
	अवरोध;
	हाल GPIO_ID_GENERIC:
		*pin = service->factory.funcs->get_generic_pin(gpio);
		service->factory.funcs->define_generic_रेजिस्टरs(*pin, en);
	अवरोध;
	हाल GPIO_ID_HPD:
		*pin = service->factory.funcs->get_hpd_pin(gpio);
		service->factory.funcs->define_hpd_रेजिस्टरs(*pin, en);
	अवरोध;

	//TODO: gsl and sync support? create_sync and create_gsl are शून्य
	हाल GPIO_ID_SYNC:
	हाल GPIO_ID_GSL:
	अवरोध;
	शेष:
		ASSERT_CRITICAL(false);
		वापस GPIO_RESULT_NON_SPECIFIC_ERROR;
	पूर्ण

	अगर (!*pin) अणु
		ASSERT_CRITICAL(false);
		वापस GPIO_RESULT_NON_SPECIFIC_ERROR;
	पूर्ण

	अगर (!(*pin)->funcs->खोलो(*pin, mode)) अणु
		ASSERT_CRITICAL(false);
		dal_gpio_service_बंद(service, pin);
		वापस GPIO_RESULT_OPEN_FAILED;
	पूर्ण

	set_pin_busy(service, id, en);
	वापस GPIO_RESULT_OK;
पूर्ण

व्योम dal_gpio_service_बंद(
	काष्ठा gpio_service *service,
	काष्ठा hw_gpio_pin **ptr)
अणु
	काष्ठा hw_gpio_pin *pin;

	अगर (!ptr) अणु
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	pin = *ptr;

	अगर (pin) अणु
		set_pin_मुक्त(service, pin->id, pin->en);

		pin->funcs->बंद(pin);

		*ptr = शून्य;
	पूर्ण
पूर्ण

क्रमागत dc_irq_source dal_irq_get_source(
	स्थिर काष्ठा gpio *irq)
अणु
	क्रमागत gpio_id id = dal_gpio_get_id(irq);

	चयन (id) अणु
	हाल GPIO_ID_HPD:
		वापस (क्रमागत dc_irq_source)(DC_IRQ_SOURCE_HPD1 +
			dal_gpio_get_क्रमागत(irq));
	हाल GPIO_ID_GPIO_PAD:
		वापस (क्रमागत dc_irq_source)(DC_IRQ_SOURCE_GPIOPAD0 +
			dal_gpio_get_क्रमागत(irq));
	शेष:
		वापस DC_IRQ_SOURCE_INVALID;
	पूर्ण
पूर्ण

क्रमागत dc_irq_source dal_irq_get_rx_source(
	स्थिर काष्ठा gpio *irq)
अणु
	क्रमागत gpio_id id = dal_gpio_get_id(irq);

	चयन (id) अणु
	हाल GPIO_ID_HPD:
		वापस (क्रमागत dc_irq_source)(DC_IRQ_SOURCE_HPD1RX +
			dal_gpio_get_क्रमागत(irq));
	शेष:
		वापस DC_IRQ_SOURCE_INVALID;
	पूर्ण
पूर्ण

क्रमागत gpio_result dal_irq_setup_hpd_filter(
	काष्ठा gpio *irq,
	काष्ठा gpio_hpd_config *config)
अणु
	काष्ठा gpio_config_data config_data;

	अगर (!config)
		वापस GPIO_RESULT_INVALID_DATA;

	config_data.type = GPIO_CONFIG_TYPE_HPD;
	config_data.config.hpd = *config;

	वापस dal_gpio_set_config(irq, &config_data);
पूर्ण

/*
 * @brief
 * Creation and deकाष्ठाion
 */

काष्ठा gpio *dal_gpio_create_irq(
	काष्ठा gpio_service *service,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	काष्ठा gpio *irq;

	चयन (id) अणु
	हाल GPIO_ID_HPD:
	हाल GPIO_ID_GPIO_PAD:
	अवरोध;
	शेष:
		id = GPIO_ID_HPD;
		ASSERT_CRITICAL(false);
		वापस शून्य;
	पूर्ण

	irq = dal_gpio_create(
		service, id, en, GPIO_PIN_OUTPUT_STATE_DEFAULT);

	अगर (irq)
		वापस irq;

	ASSERT_CRITICAL(false);
	वापस शून्य;
पूर्ण

व्योम dal_gpio_destroy_irq(
	काष्ठा gpio **irq)
अणु
	अगर (!irq || !*irq) अणु
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	dal_gpio_destroy(irq);
	kमुक्त(*irq);

	*irq = शून्य;
पूर्ण

काष्ठा ddc *dal_gpio_create_ddc(
	काष्ठा gpio_service *service,
	uपूर्णांक32_t offset,
	uपूर्णांक32_t mask,
	काष्ठा gpio_ddc_hw_info *info)
अणु
	क्रमागत gpio_id id;
	uपूर्णांक32_t en;
	काष्ठा ddc *ddc;

	अगर (!service->translate.funcs->offset_to_id(offset, mask, &id, &en))
		वापस शून्य;

	ddc = kzalloc(माप(काष्ठा ddc), GFP_KERNEL);

	अगर (!ddc) अणु
		BREAK_TO_DEBUGGER();
		वापस शून्य;
	पूर्ण

	ddc->pin_data = dal_gpio_create(
		service, GPIO_ID_DDC_DATA, en, GPIO_PIN_OUTPUT_STATE_DEFAULT);

	अगर (!ddc->pin_data) अणु
		BREAK_TO_DEBUGGER();
		जाओ failure_1;
	पूर्ण

	ddc->pin_घड़ी = dal_gpio_create(
		service, GPIO_ID_DDC_CLOCK, en, GPIO_PIN_OUTPUT_STATE_DEFAULT);

	अगर (!ddc->pin_घड़ी) अणु
		BREAK_TO_DEBUGGER();
		जाओ failure_2;
	पूर्ण

	ddc->hw_info = *info;

	ddc->ctx = service->ctx;

	वापस ddc;

failure_2:
	dal_gpio_destroy(&ddc->pin_data);

failure_1:
	kमुक्त(ddc);

	वापस शून्य;
पूर्ण

व्योम dal_gpio_destroy_ddc(
	काष्ठा ddc **ddc)
अणु
	अगर (!ddc || !*ddc) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	dal_ddc_बंद(*ddc);
	dal_gpio_destroy(&(*ddc)->pin_data);
	dal_gpio_destroy(&(*ddc)->pin_घड़ी);
	kमुक्त(*ddc);

	*ddc = शून्य;
पूर्ण

क्रमागत gpio_result dal_ddc_खोलो(
	काष्ठा ddc *ddc,
	क्रमागत gpio_mode mode,
	क्रमागत gpio_ddc_config_type config_type)
अणु
	क्रमागत gpio_result result;

	काष्ठा gpio_config_data config_data;
	काष्ठा hw_gpio *hw_data;
	काष्ठा hw_gpio *hw_घड़ी;

	result = dal_gpio_खोलो_ex(ddc->pin_data, mode);

	अगर (result != GPIO_RESULT_OK) अणु
		BREAK_TO_DEBUGGER();
		वापस result;
	पूर्ण

	result = dal_gpio_खोलो_ex(ddc->pin_घड़ी, mode);

	अगर (result != GPIO_RESULT_OK) अणु
		BREAK_TO_DEBUGGER();
		जाओ failure;
	पूर्ण

	/* DDC घड़ी and data pins should beदीर्घ
	 * to the same DDC block id,
	 * we use the data pin to set the pad mode. */

	अगर (mode == GPIO_MODE_INPUT)
		/* this is from detect_sink_type,
		 * we need extra delay there */
		config_data.type = GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE;
	अन्यथा
		config_data.type = GPIO_CONFIG_TYPE_DDC;

	config_data.config.ddc.type = config_type;

	hw_data = FROM_HW_GPIO_PIN(ddc->pin_data->pin);
	hw_घड़ी = FROM_HW_GPIO_PIN(ddc->pin_घड़ी->pin);

	config_data.config.ddc.data_en_bit_present = hw_data->store.en != 0;
	config_data.config.ddc.घड़ी_en_bit_present = hw_घड़ी->store.en != 0;

	result = dal_gpio_set_config(ddc->pin_data, &config_data);

	अगर (result == GPIO_RESULT_OK)
		वापस result;

	BREAK_TO_DEBUGGER();

	dal_gpio_बंद(ddc->pin_घड़ी);

failure:
	dal_gpio_बंद(ddc->pin_data);

	वापस result;
पूर्ण

क्रमागत gpio_result dal_ddc_change_mode(
	काष्ठा ddc *ddc,
	क्रमागत gpio_mode mode)
अणु
	क्रमागत gpio_result result;

	क्रमागत gpio_mode original_mode =
		dal_gpio_get_mode(ddc->pin_data);

	result = dal_gpio_change_mode(ddc->pin_data, mode);

	/* [anaumov] DAL2 code वापसs GPIO_RESULT_NON_SPECIFIC_ERROR
	 * in हाल of failures;
	 * set_mode() is so that, in हाल of failure,
	 * we must explicitly set original mode */

	अगर (result != GPIO_RESULT_OK)
		जाओ failure;

	result = dal_gpio_change_mode(ddc->pin_घड़ी, mode);

	अगर (result == GPIO_RESULT_OK)
		वापस result;

	dal_gpio_change_mode(ddc->pin_घड़ी, original_mode);

failure:
	dal_gpio_change_mode(ddc->pin_data, original_mode);

	वापस result;
पूर्ण

क्रमागत gpio_ddc_line dal_ddc_get_line(
	स्थिर काष्ठा ddc *ddc)
अणु
	वापस (क्रमागत gpio_ddc_line)dal_gpio_get_क्रमागत(ddc->pin_data);
पूर्ण

क्रमागत gpio_result dal_ddc_set_config(
	काष्ठा ddc *ddc,
	क्रमागत gpio_ddc_config_type config_type)
अणु
	काष्ठा gpio_config_data config_data;

	config_data.type = GPIO_CONFIG_TYPE_DDC;

	config_data.config.ddc.type = config_type;
	config_data.config.ddc.data_en_bit_present = false;
	config_data.config.ddc.घड़ी_en_bit_present = false;

	वापस dal_gpio_set_config(ddc->pin_data, &config_data);
पूर्ण

व्योम dal_ddc_बंद(
	काष्ठा ddc *ddc)
अणु
	dal_gpio_बंद(ddc->pin_घड़ी);
	dal_gpio_बंद(ddc->pin_data);
पूर्ण

