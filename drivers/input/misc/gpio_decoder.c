<शैली गुरु>
/*
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * A generic driver to पढ़ो multiple gpio lines and translate the
 * encoded numeric value पूर्णांकo an input event.
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा gpio_decoder अणु
	काष्ठा gpio_descs *input_gpios;
	काष्ठा device *dev;
	u32 axis;
	u32 last_stable;
पूर्ण;

अटल पूर्णांक gpio_decoder_get_gpios_state(काष्ठा gpio_decoder *decoder)
अणु
	काष्ठा gpio_descs *gpios = decoder->input_gpios;
	अचिन्हित पूर्णांक ret = 0;
	पूर्णांक i, val;

	क्रम (i = 0; i < gpios->ndescs; i++) अणु
		val = gpiod_get_value_cansleep(gpios->desc[i]);
		अगर (val < 0) अणु
			dev_err(decoder->dev,
				"Error reading gpio %d: %d\n",
				desc_to_gpio(gpios->desc[i]), val);
			वापस val;
		पूर्ण

		val = !!val;
		ret = (ret << 1) | val;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम gpio_decoder_poll_gpios(काष्ठा input_dev *input)
अणु
	काष्ठा gpio_decoder *decoder = input_get_drvdata(input);
	पूर्णांक state;

	state = gpio_decoder_get_gpios_state(decoder);
	अगर (state >= 0 && state != decoder->last_stable) अणु
		input_report_असल(input, decoder->axis, state);
		input_sync(input);
		decoder->last_stable = state;
	पूर्ण
पूर्ण

अटल पूर्णांक gpio_decoder_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gpio_decoder *decoder;
	काष्ठा input_dev *input;
	u32  max;
	पूर्णांक err;

	decoder = devm_kzalloc(dev, माप(*decoder), GFP_KERNEL);
	अगर (!decoder)
		वापस -ENOMEM;

	decoder->dev = dev;
	device_property_पढ़ो_u32(dev, "linux,axis", &decoder->axis);

	decoder->input_gpios = devm_gpiod_get_array(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(decoder->input_gpios)) अणु
		dev_err(dev, "unable to acquire input gpios\n");
		वापस PTR_ERR(decoder->input_gpios);
	पूर्ण

	अगर (decoder->input_gpios->ndescs < 2) अणु
		dev_err(dev, "not enough gpios found\n");
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "decoder-max-value", &max))
		max = (1U << decoder->input_gpios->ndescs) - 1;

	input = devm_input_allocate_device(dev);
	अगर (!input)
		वापस -ENOMEM;

	input_set_drvdata(input, decoder);

	input->name = pdev->name;
	input->id.bustype = BUS_HOST;
	input_set_असल_params(input, decoder->axis, 0, max, 0, 0);

	err = input_setup_polling(input, gpio_decoder_poll_gpios);
	अगर (err) अणु
		dev_err(dev, "failed to set up polling\n");
		वापस err;
	पूर्ण

	err = input_रेजिस्टर_device(input);
	अगर (err) अणु
		dev_err(dev, "failed to register input device\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id gpio_decoder_of_match[] = अणु
	अणु .compatible = "gpio-decoder", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gpio_decoder_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver gpio_decoder_driver = अणु
	.probe		= gpio_decoder_probe,
	.driver		= अणु
		.name	= "gpio-decoder",
		.of_match_table = of_match_ptr(gpio_decoder_of_match),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(gpio_decoder_driver);

MODULE_DESCRIPTION("GPIO decoder input driver");
MODULE_AUTHOR("Vignesh R <vigneshr@ti.com>");
MODULE_LICENSE("GPL v2");
