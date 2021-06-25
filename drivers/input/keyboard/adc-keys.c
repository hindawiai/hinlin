<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Input driver क्रम resistor ladder connected on ADC
 *
 * Copyright (c) 2016 Alexandre Belloni
 */

#समावेश <linux/err.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

काष्ठा adc_keys_button अणु
	u32 voltage;
	u32 keycode;
पूर्ण;

काष्ठा adc_keys_state अणु
	काष्ठा iio_channel *channel;
	u32 num_keys;
	u32 last_key;
	u32 keyup_voltage;
	स्थिर काष्ठा adc_keys_button *map;
पूर्ण;

अटल व्योम adc_keys_poll(काष्ठा input_dev *input)
अणु
	काष्ठा adc_keys_state *st = input_get_drvdata(input);
	पूर्णांक i, value, ret;
	u32 dअगरf, बंदst = 0xffffffff;
	पूर्णांक keycode = 0;

	ret = iio_पढ़ो_channel_processed(st->channel, &value);
	अगर (unlikely(ret < 0)) अणु
		/* Forcibly release key अगर any was pressed */
		value = st->keyup_voltage;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < st->num_keys; i++) अणु
			dअगरf = असल(st->map[i].voltage - value);
			अगर (dअगरf < बंदst) अणु
				बंदst = dअगरf;
				keycode = st->map[i].keycode;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (असल(st->keyup_voltage - value) < बंदst)
		keycode = 0;

	अगर (st->last_key && st->last_key != keycode)
		input_report_key(input, st->last_key, 0);

	अगर (keycode)
		input_report_key(input, keycode, 1);

	input_sync(input);
	st->last_key = keycode;
पूर्ण

अटल पूर्णांक adc_keys_load_keymap(काष्ठा device *dev, काष्ठा adc_keys_state *st)
अणु
	काष्ठा adc_keys_button *map;
	काष्ठा fwnode_handle *child;
	पूर्णांक i;

	st->num_keys = device_get_child_node_count(dev);
	अगर (st->num_keys == 0) अणु
		dev_err(dev, "keymap is missing\n");
		वापस -EINVAL;
	पूर्ण

	map = devm_kदो_स्मृति_array(dev, st->num_keys, माप(*map), GFP_KERNEL);
	अगर (!map)
		वापस -ENOMEM;

	i = 0;
	device_क्रम_each_child_node(dev, child) अणु
		अगर (fwnode_property_पढ़ो_u32(child, "press-threshold-microvolt",
					     &map[i].voltage)) अणु
			dev_err(dev, "Key with invalid or missing voltage\n");
			fwnode_handle_put(child);
			वापस -EINVAL;
		पूर्ण
		map[i].voltage /= 1000;

		अगर (fwnode_property_पढ़ो_u32(child, "linux,code",
					     &map[i].keycode)) अणु
			dev_err(dev, "Key with invalid or missing linux,code\n");
			fwnode_handle_put(child);
			वापस -EINVAL;
		पूर्ण

		i++;
	पूर्ण

	st->map = map;
	वापस 0;
पूर्ण

अटल पूर्णांक adc_keys_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा adc_keys_state *st;
	काष्ठा input_dev *input;
	क्रमागत iio_chan_type type;
	पूर्णांक i, value;
	पूर्णांक error;

	st = devm_kzalloc(dev, माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	st->channel = devm_iio_channel_get(dev, "buttons");
	अगर (IS_ERR(st->channel))
		वापस PTR_ERR(st->channel);

	अगर (!st->channel->indio_dev)
		वापस -ENXIO;

	error = iio_get_channel_type(st->channel, &type);
	अगर (error < 0)
		वापस error;

	अगर (type != IIO_VOLTAGE) अणु
		dev_err(dev, "Incompatible channel type %d\n", type);
		वापस -EINVAL;
	पूर्ण

	अगर (device_property_पढ़ो_u32(dev, "keyup-threshold-microvolt",
				     &st->keyup_voltage)) अणु
		dev_err(dev, "Invalid or missing keyup voltage\n");
		वापस -EINVAL;
	पूर्ण
	st->keyup_voltage /= 1000;

	error = adc_keys_load_keymap(dev, st);
	अगर (error)
		वापस error;

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(input, st);

	input->name = pdev->name;
	input->phys = "adc-keys/input0";

	input->id.bustype = BUS_HOST;
	input->id.venकरोr = 0x0001;
	input->id.product = 0x0001;
	input->id.version = 0x0100;

	__set_bit(EV_KEY, input->evbit);
	क्रम (i = 0; i < st->num_keys; i++)
		__set_bit(st->map[i].keycode, input->keybit);

	अगर (device_property_पढ़ो_bool(dev, "autorepeat"))
		__set_bit(EV_REP, input->evbit);


	error = input_setup_polling(input, adc_keys_poll);
	अगर (error) अणु
		dev_err(dev, "Unable to set up polling: %d\n", error);
		वापस error;
	पूर्ण

	अगर (!device_property_पढ़ो_u32(dev, "poll-interval", &value))
		input_set_poll_पूर्णांकerval(input, value);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "Unable to register input device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id adc_keys_of_match[] = अणु
	अणु .compatible = "adc-keys", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc_keys_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver __refdata adc_keys_driver = अणु
	.driver = अणु
		.name = "adc_keys",
		.of_match_table = of_match_ptr(adc_keys_of_match),
	पूर्ण,
	.probe = adc_keys_probe,
पूर्ण;
module_platक्रमm_driver(adc_keys_driver);

MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@free-electrons.com>");
MODULE_DESCRIPTION("Input driver for resistor ladder connected on ADC");
MODULE_LICENSE("GPL v2");
