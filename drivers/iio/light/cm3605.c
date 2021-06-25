<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * CM3605 Ambient Light and Proximity Sensor
 *
 * Copyright (C) 2016 Linaro Ltd.
 * Author: Linus Walleij <linus.walleij@linaro.org>
 *
 * This hardware was found in the very first Nexus One handset from Google/HTC
 * and an early endavour पूर्णांकo mobile light and proximity sensors.
 */

#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/consumer.h> /* To get our ADC channel */
#समावेश <linux/iio/types.h> /* To deal with our ADC channel */
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/math64.h>
#समावेश <linux/pm.h>

#घोषणा CM3605_PROX_CHANNEL 0
#घोषणा CM3605_ALS_CHANNEL 1
#घोषणा CM3605_AOUT_TYP_MAX_MV 1550
/* It should not go above 1.650V according to the data sheet */
#घोषणा CM3605_AOUT_MAX_MV 1650

/**
 * काष्ठा cm3605 - CM3605 state
 * @dev: poपूर्णांकer to parent device
 * @vdd: regulator controlling VDD
 * @aset: sleep enable GPIO, high = sleep
 * @aout: IIO ADC channel to convert the AOUT संकेत
 * @als_max: maximum LUX detection (depends on RSET)
 * @dir: proximity direction: start as FALLING
 * @led: trigger क्रम the infrared LED used by the proximity sensor
 */
काष्ठा cm3605 अणु
	काष्ठा device *dev;
	काष्ठा regulator *vdd;
	काष्ठा gpio_desc *aset;
	काष्ठा iio_channel *aout;
	s32 als_max;
	क्रमागत iio_event_direction dir;
	काष्ठा led_trigger *led;
पूर्ण;

अटल irqवापस_t cm3605_prox_irq(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा iio_dev *indio_dev = d;
	काष्ठा cm3605 *cm3605 = iio_priv(indio_dev);
	u64 ev;

	ev = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, CM3605_PROX_CHANNEL,
				  IIO_EV_TYPE_THRESH, cm3605->dir);
	iio_push_event(indio_dev, ev, iio_get_समय_ns(indio_dev));

	/* Invert the edge क्रम each event */
	अगर (cm3605->dir == IIO_EV_सूची_RISING)
		cm3605->dir = IIO_EV_सूची_FALLING;
	अन्यथा
		cm3605->dir = IIO_EV_सूची_RISING;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक cm3605_get_lux(काष्ठा cm3605 *cm3605)
अणु
	पूर्णांक ret, res;
	s64 lux;

	ret = iio_पढ़ो_channel_processed(cm3605->aout, &res);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(cm3605->dev, "read %d mV from ADC\n", res);

	/*
	 * AOUT has an offset of ~30mV then linear at dark
	 * then goes from 2.54 up to 650 LUX yielding 1.55V
	 * (1550 mV) so scale the वापसed value to this पूर्णांकerval
	 * using simple linear पूर्णांकerpolation.
	 */
	अगर (res < 30)
		वापस 0;
	अगर (res > CM3605_AOUT_MAX_MV)
		dev_err(cm3605->dev, "device out of range\n");

	/* Remove bias */
	lux = res - 30;

	/* Linear पूर्णांकerpolation between 0 and ALS typ max */
	lux *= cm3605->als_max;
	lux = भाग64_s64(lux, CM3605_AOUT_TYP_MAX_MV);

	वापस lux;
पूर्ण

अटल पूर्णांक cm3605_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cm3605 *cm3605 = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = cm3605_get_lux(cm3605);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info cm3605_info = अणु
	.पढ़ो_raw = cm3605_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec cm3605_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec cm3605_channels[] = अणु
	अणु
		.type = IIO_PROXIMITY,
		.event_spec = cm3605_events,
		.num_event_specs = ARRAY_SIZE(cm3605_events),
	पूर्ण,
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.channel = CM3605_ALS_CHANNEL,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cm3605_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cm3605 *cm3605;
	काष्ठा iio_dev *indio_dev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	क्रमागत iio_chan_type ch_type;
	u32 rset;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*cm3605));
	अगर (!indio_dev)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, indio_dev);

	cm3605 = iio_priv(indio_dev);
	cm3605->dev = dev;
	cm3605->dir = IIO_EV_सूची_FALLING;

	ret = of_property_पढ़ो_u32(np, "capella,aset-resistance-ohms", &rset);
	अगर (ret) अणु
		dev_info(dev, "no RSET specified, assuming 100K\n");
		rset = 100000;
	पूर्ण
	चयन (rset) अणु
	हाल 50000:
		cm3605->als_max = 650;
		अवरोध;
	हाल 100000:
		cm3605->als_max = 300;
		अवरोध;
	हाल 300000:
		cm3605->als_max = 100;
		अवरोध;
	हाल 600000:
		cm3605->als_max = 50;
		अवरोध;
	शेष:
		dev_info(dev, "non-standard resistance\n");
		वापस -EINVAL;
	पूर्ण

	cm3605->aout = devm_iio_channel_get(dev, "aout");
	अगर (IS_ERR(cm3605->aout)) अणु
		अगर (PTR_ERR(cm3605->aout) == -ENODEV) अणु
			dev_err(dev, "no ADC, deferring...\n");
			वापस -EPROBE_DEFER;
		पूर्ण
		dev_err(dev, "failed to get AOUT ADC channel\n");
		वापस PTR_ERR(cm3605->aout);
	पूर्ण
	ret = iio_get_channel_type(cm3605->aout, &ch_type);
	अगर (ret < 0)
		वापस ret;
	अगर (ch_type != IIO_VOLTAGE) अणु
		dev_err(dev, "wrong type of IIO channel specified for AOUT\n");
		वापस -EINVAL;
	पूर्ण

	cm3605->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(cm3605->vdd)) अणु
		dev_err(dev, "failed to get VDD regulator\n");
		वापस PTR_ERR(cm3605->vdd);
	पूर्ण
	ret = regulator_enable(cm3605->vdd);
	अगर (ret) अणु
		dev_err(dev, "failed to enable VDD regulator\n");
		वापस ret;
	पूर्ण

	cm3605->aset = devm_gpiod_get(dev, "aset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(cm3605->aset)) अणु
		dev_err(dev, "no ASET GPIO\n");
		ret = PTR_ERR(cm3605->aset);
		जाओ out_disable_vdd;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, platक्रमm_get_irq(pdev, 0),
			cm3605_prox_irq, शून्य, 0, "cm3605", indio_dev);
	अगर (ret) अणु
		dev_err(dev, "unable to request IRQ\n");
		जाओ out_disable_aset;
	पूर्ण

	/* Just name the trigger the same as the driver */
	led_trigger_रेजिस्टर_simple("cm3605", &cm3605->led);
	led_trigger_event(cm3605->led, LED_FULL);

	indio_dev->info = &cm3605_info;
	indio_dev->name = "cm3605";
	indio_dev->channels = cm3605_channels;
	indio_dev->num_channels = ARRAY_SIZE(cm3605_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ out_हटाओ_trigger;
	dev_info(dev, "Capella Microsystems CM3605 enabled range 0..%d LUX\n",
		 cm3605->als_max);

	वापस 0;

out_हटाओ_trigger:
	led_trigger_event(cm3605->led, LED_OFF);
	led_trigger_unरेजिस्टर_simple(cm3605->led);
out_disable_aset:
	gpiod_set_value_cansleep(cm3605->aset, 0);
out_disable_vdd:
	regulator_disable(cm3605->vdd);
	वापस ret;
पूर्ण

अटल पूर्णांक cm3605_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा cm3605 *cm3605 = iio_priv(indio_dev);

	led_trigger_event(cm3605->led, LED_OFF);
	led_trigger_unरेजिस्टर_simple(cm3605->led);
	gpiod_set_value_cansleep(cm3605->aset, 0);
	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(cm3605->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cm3605_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा cm3605 *cm3605 = iio_priv(indio_dev);

	led_trigger_event(cm3605->led, LED_OFF);
	regulator_disable(cm3605->vdd);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cm3605_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा cm3605 *cm3605 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(cm3605->vdd);
	अगर (ret)
		dev_err(dev, "failed to enable regulator in resume path\n");
	led_trigger_event(cm3605->led, LED_FULL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cm3605_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cm3605_pm_suspend,
				cm3605_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cm3605_of_match[] = अणु
	अणु.compatible = "capella,cm3605"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cm3605_of_match);

अटल काष्ठा platक्रमm_driver cm3605_driver = अणु
	.driver = अणु
		.name = "cm3605",
		.of_match_table = cm3605_of_match,
		.pm = &cm3605_dev_pm_ops,
	पूर्ण,
	.probe = cm3605_probe,
	.हटाओ = cm3605_हटाओ,
पूर्ण;
module_platक्रमm_driver(cm3605_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("CM3605 ambient light and proximity sensor driver");
MODULE_LICENSE("GPL");
