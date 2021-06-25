<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Toradex Colibri VF50 Touchscreen driver
 *
 * Copyright 2015 Toradex AG
 *
 * Originally authored by Stefan Agner क्रम 3.0 kernel
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/consumer.h>
#समावेश <linux/iio/types.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा DRIVER_NAME			"colibri-vf50-ts"

#घोषणा VF_ADC_MAX			((1 << 12) - 1)

#घोषणा COLI_TOUCH_MIN_DELAY_US		1000
#घोषणा COLI_TOUCH_MAX_DELAY_US		2000
#घोषणा COLI_PULLUP_MIN_DELAY_US	10000
#घोषणा COLI_PULLUP_MAX_DELAY_US	11000
#घोषणा COLI_TOUCH_NO_OF_AVGS		5
#घोषणा COLI_TOUCH_REQ_ADC_CHAN		4

काष्ठा vf50_touch_device अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा input_dev *ts_input;
	काष्ठा iio_channel *channels;
	काष्ठा gpio_desc *gpio_xp;
	काष्ठा gpio_desc *gpio_xm;
	काष्ठा gpio_desc *gpio_yp;
	काष्ठा gpio_desc *gpio_ym;
	पूर्णांक pen_irq;
	पूर्णांक min_pressure;
	bool stop_touchscreen;
पूर्ण;

/*
 * Enables given plates and measures touch parameters using ADC
 */
अटल पूर्णांक adc_ts_measure(काष्ठा iio_channel *channel,
			  काष्ठा gpio_desc *plate_p, काष्ठा gpio_desc *plate_m)
अणु
	पूर्णांक i, value = 0, val = 0;
	पूर्णांक error;

	gpiod_set_value(plate_p, 1);
	gpiod_set_value(plate_m, 1);

	usleep_range(COLI_TOUCH_MIN_DELAY_US, COLI_TOUCH_MAX_DELAY_US);

	क्रम (i = 0; i < COLI_TOUCH_NO_OF_AVGS; i++) अणु
		error = iio_पढ़ो_channel_raw(channel, &val);
		अगर (error < 0) अणु
			value = error;
			जाओ error_iio_पढ़ो;
		पूर्ण

		value += val;
	पूर्ण

	value /= COLI_TOUCH_NO_OF_AVGS;

error_iio_पढ़ो:
	gpiod_set_value(plate_p, 0);
	gpiod_set_value(plate_m, 0);

	वापस value;
पूर्ण

/*
 * Enable touch detection using falling edge detection on XM
 */
अटल व्योम vf50_ts_enable_touch_detection(काष्ठा vf50_touch_device *vf50_ts)
अणु
	/* Enable plate YM (needs to be strong GND, high active) */
	gpiod_set_value(vf50_ts->gpio_ym, 1);

	/*
	 * Let the platक्रमm mux to idle state in order to enable
	 * Pull-Up on GPIO
	 */
	pinctrl_pm_select_idle_state(&vf50_ts->pdev->dev);

	/* Wait क्रम the pull-up to be stable on high */
	usleep_range(COLI_PULLUP_MIN_DELAY_US, COLI_PULLUP_MAX_DELAY_US);
पूर्ण

/*
 * ADC touch screen sampling bottom half irq handler
 */
अटल irqवापस_t vf50_ts_irq_bh(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा vf50_touch_device *vf50_ts = निजी;
	काष्ठा device *dev = &vf50_ts->pdev->dev;
	पूर्णांक val_x, val_y, val_z1, val_z2, val_p = 0;
	bool discard_val_on_start = true;

	/* Disable the touch detection plates */
	gpiod_set_value(vf50_ts->gpio_ym, 0);

	/* Let the platक्रमm mux to शेष state in order to mux as ADC */
	pinctrl_pm_select_शेष_state(dev);

	जबतक (!vf50_ts->stop_touchscreen) अणु
		/* X-Direction */
		val_x = adc_ts_measure(&vf50_ts->channels[0],
				vf50_ts->gpio_xp, vf50_ts->gpio_xm);
		अगर (val_x < 0)
			अवरोध;

		/* Y-Direction */
		val_y = adc_ts_measure(&vf50_ts->channels[1],
				vf50_ts->gpio_yp, vf50_ts->gpio_ym);
		अगर (val_y < 0)
			अवरोध;

		/*
		 * Touch pressure
		 * Measure on XP/YM
		 */
		val_z1 = adc_ts_measure(&vf50_ts->channels[2],
				vf50_ts->gpio_yp, vf50_ts->gpio_xm);
		अगर (val_z1 < 0)
			अवरोध;
		val_z2 = adc_ts_measure(&vf50_ts->channels[3],
				vf50_ts->gpio_yp, vf50_ts->gpio_xm);
		अगर (val_z2 < 0)
			अवरोध;

		/* Validate संकेत (aव्योम calculation using noise) */
		अगर (val_z1 > 64 && val_x > 64) अणु
			/*
			 * Calculate resistance between the plates
			 * lower resistance means higher pressure
			 */
			पूर्णांक r_x = (1000 * val_x) / VF_ADC_MAX;

			val_p = (r_x * val_z2) / val_z1 - r_x;

		पूर्ण अन्यथा अणु
			val_p = 2000;
		पूर्ण

		val_p = 2000 - val_p;
		dev_dbg(dev,
			"Measured values: x: %d, y: %d, z1: %d, z2: %d, p: %d\n",
			val_x, val_y, val_z1, val_z2, val_p);

		/*
		 * If touch pressure is too low, stop measuring and reenable
		 * touch detection
		 */
		अगर (val_p < vf50_ts->min_pressure || val_p > 2000)
			अवरोध;

		/*
		 * The pressure may not be enough क्रम the first x and the
		 * second y measurement, but, the pressure is ok when the
		 * driver is करोing the third and fourth measurement. To
		 * take care of this, we drop the first measurement always.
		 */
		अगर (discard_val_on_start) अणु
			discard_val_on_start = false;
		पूर्ण अन्यथा अणु
			/*
			 * Report touch position and sleep क्रम
			 * the next measurement.
			 */
			input_report_असल(vf50_ts->ts_input,
					ABS_X, VF_ADC_MAX - val_x);
			input_report_असल(vf50_ts->ts_input,
					ABS_Y, VF_ADC_MAX - val_y);
			input_report_असल(vf50_ts->ts_input,
					ABS_PRESSURE, val_p);
			input_report_key(vf50_ts->ts_input, BTN_TOUCH, 1);
			input_sync(vf50_ts->ts_input);
		पूर्ण

		usleep_range(COLI_PULLUP_MIN_DELAY_US,
			     COLI_PULLUP_MAX_DELAY_US);
	पूर्ण

	/* Report no more touch, re-enable touch detection */
	input_report_असल(vf50_ts->ts_input, ABS_PRESSURE, 0);
	input_report_key(vf50_ts->ts_input, BTN_TOUCH, 0);
	input_sync(vf50_ts->ts_input);

	vf50_ts_enable_touch_detection(vf50_ts);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vf50_ts_खोलो(काष्ठा input_dev *dev_input)
अणु
	काष्ठा vf50_touch_device *touchdev = input_get_drvdata(dev_input);
	काष्ठा device *dev = &touchdev->pdev->dev;

	dev_dbg(dev, "Input device %s opened, starting touch detection\n",
		dev_input->name);

	touchdev->stop_touchscreen = false;

	/* Mux detection beक्रमe request IRQ, रुको क्रम pull-up to settle */
	vf50_ts_enable_touch_detection(touchdev);

	वापस 0;
पूर्ण

अटल व्योम vf50_ts_बंद(काष्ठा input_dev *dev_input)
अणु
	काष्ठा vf50_touch_device *touchdev = input_get_drvdata(dev_input);
	काष्ठा device *dev = &touchdev->pdev->dev;

	touchdev->stop_touchscreen = true;

	/* Make sure IRQ is not running past बंद */
	mb();
	synchronize_irq(touchdev->pen_irq);

	gpiod_set_value(touchdev->gpio_ym, 0);
	pinctrl_pm_select_शेष_state(dev);

	dev_dbg(dev, "Input device %s closed, disable touch detection\n",
		dev_input->name);
पूर्ण

अटल पूर्णांक vf50_ts_get_gpiod(काष्ठा device *dev, काष्ठा gpio_desc **gpio_d,
			     स्थिर अक्षर *con_id, क्रमागत gpiod_flags flags)
अणु
	पूर्णांक error;

	*gpio_d = devm_gpiod_get(dev, con_id, flags);
	अगर (IS_ERR(*gpio_d)) अणु
		error = PTR_ERR(*gpio_d);
		dev_err(dev, "Could not get gpio_%s %d\n", con_id, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vf50_ts_channel_release(व्योम *data)
अणु
	काष्ठा iio_channel *channels = data;

	iio_channel_release_all(channels);
पूर्ण

अटल पूर्णांक vf50_ts_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा input_dev *input;
	काष्ठा iio_channel *channels;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा vf50_touch_device *touchdev;
	पूर्णांक num_adc_channels;
	पूर्णांक error;

	channels = iio_channel_get_all(dev);
	अगर (IS_ERR(channels))
		वापस PTR_ERR(channels);

	error = devm_add_action(dev, vf50_ts_channel_release, channels);
	अगर (error) अणु
		iio_channel_release_all(channels);
		dev_err(dev, "Failed to register iio channel release action");
		वापस error;
	पूर्ण

	num_adc_channels = 0;
	जबतक (channels[num_adc_channels].indio_dev)
		num_adc_channels++;

	अगर (num_adc_channels != COLI_TOUCH_REQ_ADC_CHAN) अणु
		dev_err(dev, "Inadequate ADC channels specified\n");
		वापस -EINVAL;
	पूर्ण

	touchdev = devm_kzalloc(dev, माप(*touchdev), GFP_KERNEL);
	अगर (!touchdev)
		वापस -ENOMEM;

	touchdev->pdev = pdev;
	touchdev->channels = channels;

	error = of_property_पढ़ो_u32(dev->of_node, "vf50-ts-min-pressure",
				 &touchdev->min_pressure);
	अगर (error)
		वापस error;

	input = devm_input_allocate_device(dev);
	अगर (!input) अणु
		dev_err(dev, "Failed to allocate TS input device\n");
		वापस -ENOMEM;
	पूर्ण

	input->name = DRIVER_NAME;
	input->id.bustype = BUS_HOST;
	input->dev.parent = dev;
	input->खोलो = vf50_ts_खोलो;
	input->बंद = vf50_ts_बंद;

	input_set_capability(input, EV_KEY, BTN_TOUCH);
	input_set_असल_params(input, ABS_X, 0, VF_ADC_MAX, 0, 0);
	input_set_असल_params(input, ABS_Y, 0, VF_ADC_MAX, 0, 0);
	input_set_असल_params(input, ABS_PRESSURE, 0, VF_ADC_MAX, 0, 0);

	touchdev->ts_input = input;
	input_set_drvdata(input, touchdev);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(dev, "Failed to register input device\n");
		वापस error;
	पूर्ण

	error = vf50_ts_get_gpiod(dev, &touchdev->gpio_xp, "xp", GPIOD_OUT_LOW);
	अगर (error)
		वापस error;

	error = vf50_ts_get_gpiod(dev, &touchdev->gpio_xm,
				"xm", GPIOD_OUT_LOW);
	अगर (error)
		वापस error;

	error = vf50_ts_get_gpiod(dev, &touchdev->gpio_yp, "yp", GPIOD_OUT_LOW);
	अगर (error)
		वापस error;

	error = vf50_ts_get_gpiod(dev, &touchdev->gpio_ym, "ym", GPIOD_OUT_LOW);
	अगर (error)
		वापस error;

	touchdev->pen_irq = platक्रमm_get_irq(pdev, 0);
	अगर (touchdev->pen_irq < 0)
		वापस touchdev->pen_irq;

	error = devm_request_thपढ़ोed_irq(dev, touchdev->pen_irq,
					  शून्य, vf50_ts_irq_bh, IRQF_ONESHOT,
					  "vf50 touch", touchdev);
	अगर (error) अणु
		dev_err(dev, "Failed to request IRQ %d: %d\n",
			touchdev->pen_irq, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id vf50_touch_of_match[] = अणु
	अणु .compatible = "toradex,vf50-touchscreen", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vf50_touch_of_match);

अटल काष्ठा platक्रमm_driver vf50_touch_driver = अणु
	.driver = अणु
		.name = "toradex,vf50_touchctrl",
		.of_match_table = vf50_touch_of_match,
	पूर्ण,
	.probe = vf50_ts_probe,
पूर्ण;
module_platक्रमm_driver(vf50_touch_driver);

MODULE_AUTHOR("Sanchayan Maity");
MODULE_DESCRIPTION("Colibri VF50 Touchscreen driver");
MODULE_LICENSE("GPL");
