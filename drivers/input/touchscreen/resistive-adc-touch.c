<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ADC generic resistive touchscreen (GRTS)
 * This is a generic input driver that connects to an ADC
 * given the channels in device tree, and reports events to the input
 * subप्रणाली.
 *
 * Copyright (C) 2017,2018 Microchip Technology,
 * Author: Eugen Hristev <eugen.hristev@microchip.com>
 *
 */
#समावेश <linux/input.h>
#समावेश <linux/input/touchscreen.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRIVER_NAME					"resistive-adc-touch"
#घोषणा GRTS_DEFAULT_PRESSURE_MIN			50000
#घोषणा GRTS_MAX_POS_MASK				GENMASK(11, 0)

/**
 * काष्ठा grts_state - generic resistive touch screen inक्रमmation काष्ठा
 * @pressure_min:	number representing the minimum क्रम the pressure
 * @pressure:		are we getting pressure info or not
 * @iio_chans:		list of channels acquired
 * @iio_cb:		iio_callback buffer क्रम the data
 * @input:		the input device काष्ठाure that we रेजिस्टर
 * @prop:		touchscreen properties काष्ठा
 */
काष्ठा grts_state अणु
	u32				pressure_min;
	bool				pressure;
	काष्ठा iio_channel		*iio_chans;
	काष्ठा iio_cb_buffer		*iio_cb;
	काष्ठा input_dev		*input;
	काष्ठा touchscreen_properties	prop;
पूर्ण;

अटल पूर्णांक grts_cb(स्थिर व्योम *data, व्योम *निजी)
अणु
	स्थिर u16 *touch_info = data;
	काष्ठा grts_state *st = निजी;
	अचिन्हित पूर्णांक x, y, press = 0x0;

	/* channel data coming in buffer in the order below */
	x = touch_info[0];
	y = touch_info[1];
	अगर (st->pressure)
		press = touch_info[2];

	अगर ((!x && !y) || (st->pressure && (press < st->pressure_min))) अणु
		/* report end of touch */
		input_report_key(st->input, BTN_TOUCH, 0);
		input_sync(st->input);
		वापस 0;
	पूर्ण

	/* report proper touch to subप्रणाली*/
	touchscreen_report_pos(st->input, &st->prop, x, y, false);
	अगर (st->pressure)
		input_report_असल(st->input, ABS_PRESSURE, press);
	input_report_key(st->input, BTN_TOUCH, 1);
	input_sync(st->input);

	वापस 0;
पूर्ण

अटल पूर्णांक grts_खोलो(काष्ठा input_dev *dev)
अणु
	पूर्णांक error;
	काष्ठा grts_state *st = input_get_drvdata(dev);

	error = iio_channel_start_all_cb(st->iio_cb);
	अगर (error) अणु
		dev_err(dev->dev.parent, "failed to start callback buffer.\n");
		वापस error;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम grts_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा grts_state *st = input_get_drvdata(dev);

	iio_channel_stop_all_cb(st->iio_cb);
पूर्ण

अटल व्योम grts_disable(व्योम *data)
अणु
	iio_channel_release_all_cb(data);
पूर्ण

अटल पूर्णांक grts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा grts_state *st;
	काष्ठा input_dev *input;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा iio_channel *chan;
	पूर्णांक error;

	st = devm_kzalloc(dev, माप(काष्ठा grts_state), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	/* get the channels from IIO device */
	st->iio_chans = devm_iio_channel_get_all(dev);
	अगर (IS_ERR(st->iio_chans)) अणु
		error = PTR_ERR(st->iio_chans);
		अगर (error != -EPROBE_DEFER)
			dev_err(dev, "can't get iio channels.\n");
		वापस error;
	पूर्ण

	chan = &st->iio_chans[0];
	st->pressure = false;
	जबतक (chan && chan->indio_dev) अणु
		अगर (!म_भेद(chan->channel->datasheet_name, "pressure"))
			st->pressure = true;
		chan++;
	पूर्ण

	अगर (st->pressure) अणु
		error = device_property_पढ़ो_u32(dev,
						 "touchscreen-min-pressure",
						 &st->pressure_min);
		अगर (error) अणु
			dev_dbg(dev, "can't get touchscreen-min-pressure property.\n");
			st->pressure_min = GRTS_DEFAULT_PRESSURE_MIN;
		पूर्ण
	पूर्ण

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "failed to allocate input device.\n");
		वापस -ENOMEM;
	पूर्ण

	input->name = DRIVER_NAME;
	input->id.bustype = BUS_HOST;
	input->खोलो = grts_खोलो;
	input->बंद = grts_बंद;

	input_set_असल_params(input, ABS_X, 0, GRTS_MAX_POS_MASK - 1, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, GRTS_MAX_POS_MASK - 1, 0, 0);
	अगर (st->pressure)
		input_set_असल_params(input, ABS_PRESSURE, st->pressure_min,
				     0xffff, 0, 0);

	input_set_capability(input, EV_KEY, BTN_TOUCH);

	/* parse optional device tree properties */
	touchscreen_parse_properties(input, false, &st->prop);

	st->input = input;
	input_set_drvdata(input, st);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "failed to register input device.");
		वापस error;
	पूर्ण

	st->iio_cb = iio_channel_get_all_cb(dev, grts_cb, st);
	अगर (IS_ERR(st->iio_cb)) अणु
		dev_err(dev, "failed to allocate callback buffer.\n");
		वापस PTR_ERR(st->iio_cb);
	पूर्ण

	error = devm_add_action_or_reset(dev, grts_disable, st->iio_cb);
	अगर (error) अणु
		dev_err(dev, "failed to add disable action.\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id grts_of_match[] = अणु
	अणु
		.compatible = "resistive-adc-touch",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, grts_of_match);

अटल काष्ठा platक्रमm_driver grts_driver = अणु
	.probe = grts_probe,
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = of_match_ptr(grts_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(grts_driver);

MODULE_AUTHOR("Eugen Hristev <eugen.hristev@microchip.com>");
MODULE_DESCRIPTION("Generic ADC Resistive Touch Driver");
MODULE_LICENSE("GPL v2");
