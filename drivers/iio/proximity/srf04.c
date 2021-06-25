<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SRF04: ultrasonic sensor क्रम distance measuring by using GPIOs
 *
 * Copyright (c) 2017 Andreas Klinger <ak@it-klinger.de>
 *
 * For details about the device see:
 * https://www.robot-electronics.co.uk/hपंचांग/srf04tech.hपंचांग
 *
 * the measurement cycle as timing diagram looks like:
 *
 *          +---+
 * GPIO     |   |
 * trig:  --+   +------------------------------------------------------
 *          ^   ^
 *          |<->|
 *         udelay(trigger_pulse_us)
 *
 * ultra           +-+ +-+ +-+
 * sonic           | | | | | |
 * burst: ---------+ +-+ +-+ +-----------------------------------------
 *                           .
 * ultra                     .              +-+ +-+ +-+
 * sonic                     .              | | | | | |
 * echo:  ----------------------------------+ +-+ +-+ +----------------
 *                           .                        .
 *                           +------------------------+
 * GPIO                      |                        |
 * echo:  -------------------+                        +---------------
 *                           ^                        ^
 *                           पूर्णांकerrupt                पूर्णांकerrupt
 *                           (ts_rising)              (ts_falling)
 *                           |<---------------------->|
 *                              pulse समय measured
 *                              --> one round trip of ultra sonic waves
 */
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

काष्ठा srf04_cfg अणु
	अचिन्हित दीर्घ trigger_pulse_us;
पूर्ण;

काष्ठा srf04_data अणु
	काष्ठा device		*dev;
	काष्ठा gpio_desc	*gpiod_trig;
	काष्ठा gpio_desc	*gpiod_echo;
	काष्ठा gpio_desc	*gpiod_घातer;
	काष्ठा mutex		lock;
	पूर्णांक			irqnr;
	kसमय_प्रकार			ts_rising;
	kसमय_प्रकार			ts_falling;
	काष्ठा completion	rising;
	काष्ठा completion	falling;
	स्थिर काष्ठा srf04_cfg	*cfg;
	पूर्णांक			startup_समय_ms;
पूर्ण;

अटल स्थिर काष्ठा srf04_cfg srf04_cfg = अणु
	.trigger_pulse_us = 10,
पूर्ण;

अटल स्थिर काष्ठा srf04_cfg mb_lv_cfg = अणु
	.trigger_pulse_us = 20,
पूर्ण;

अटल irqवापस_t srf04_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iio_dev *indio_dev = dev_id;
	काष्ठा srf04_data *data = iio_priv(indio_dev);
	kसमय_प्रकार now = kसमय_get();

	अगर (gpiod_get_value(data->gpiod_echo)) अणु
		data->ts_rising = now;
		complete(&data->rising);
	पूर्ण अन्यथा अणु
		data->ts_falling = now;
		complete(&data->falling);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक srf04_पढ़ो(काष्ठा srf04_data *data)
अणु
	पूर्णांक ret;
	kसमय_प्रकार kसमय_dt;
	u64 dt_ns;
	u32 समय_ns, distance_mm;

	अगर (data->gpiod_घातer)
		pm_runसमय_get_sync(data->dev);

	/*
	 * just one पढ़ो-echo-cycle can take place at a समय
	 * ==> lock against concurrent पढ़ोing calls
	 */
	mutex_lock(&data->lock);

	reinit_completion(&data->rising);
	reinit_completion(&data->falling);

	gpiod_set_value(data->gpiod_trig, 1);
	udelay(data->cfg->trigger_pulse_us);
	gpiod_set_value(data->gpiod_trig, 0);

	अगर (data->gpiod_घातer) अणु
		pm_runसमय_mark_last_busy(data->dev);
		pm_runसमय_put_स्वतःsuspend(data->dev);
	पूर्ण

	/* it should not take more than 20 ms until echo is rising */
	ret = रुको_क्रम_completion_समाप्तable_समयout(&data->rising, HZ/50);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		mutex_unlock(&data->lock);
		वापस -ETIMEDOUT;
	पूर्ण

	/* it cannot take more than 50 ms until echo is falling */
	ret = रुको_क्रम_completion_समाप्तable_समयout(&data->falling, HZ/20);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण अन्यथा अगर (ret == 0) अणु
		mutex_unlock(&data->lock);
		वापस -ETIMEDOUT;
	पूर्ण

	kसमय_dt = kसमय_sub(data->ts_falling, data->ts_rising);

	mutex_unlock(&data->lock);

	dt_ns = kसमय_प्रकारo_ns(kसमय_dt);
	/*
	 * measuring more than 6,45 meters is beyond the capabilities of
	 * the supported sensors
	 * ==> filter out invalid results क्रम not measuring echos of
	 *     another us sensor
	 *
	 * क्रमmula:
	 *         distance     6,45 * 2 m
	 * समय = ---------- = ------------ = 40438871 ns
	 *          speed         319 m/s
	 *
	 * using a minimum speed at -20 तओC of 319 m/s
	 */
	अगर (dt_ns > 40438871)
		वापस -EIO;

	समय_ns = dt_ns;

	/*
	 * the speed as function of the temperature is approximately:
	 *
	 * speed = 331,5 + 0,6 * Temp
	 *   with Temp in तओC
	 *   and speed in m/s
	 *
	 * use 343,5 m/s as ultrasonic speed at 20 तओC here in असलence of the
	 * temperature
	 *
	 * thereक्रमe:
	 *             समय     343,5     समय * 106
	 * distance = ------ * ------- = ------------
	 *             10^6         2         617176
	 *   with समय in ns
	 *   and distance in mm (one way)
	 *
	 * because we limit to 6,45 meters the multiplication with 106 just
	 * fits पूर्णांकo 32 bit
	 */
	distance_mm = समय_ns * 106 / 617176;

	वापस distance_mm;
पूर्ण

अटल पूर्णांक srf04_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा srf04_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (channel->type != IIO_DISTANCE)
		वापस -EINVAL;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = srf04_पढ़ो(data);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * theoretical maximum resolution is 3 mm
		 * 1 LSB is 1 mm
		 */
		*val = 0;
		*val2 = 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info srf04_iio_info = अणु
	.पढ़ो_raw		= srf04_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec srf04_chan_spec[] = अणु
	अणु
		.type = IIO_DISTANCE,
		.info_mask_separate =
				BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_srf04_match[] = अणु
	अणु .compatible = "devantech,srf04", .data = &srf04_cfgपूर्ण,
	अणु .compatible = "maxbotix,mb1000", .data = &mb_lv_cfgपूर्ण,
	अणु .compatible = "maxbotix,mb1010", .data = &mb_lv_cfgपूर्ण,
	अणु .compatible = "maxbotix,mb1020", .data = &mb_lv_cfgपूर्ण,
	अणु .compatible = "maxbotix,mb1030", .data = &mb_lv_cfgपूर्ण,
	अणु .compatible = "maxbotix,mb1040", .data = &mb_lv_cfgपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_srf04_match);

अटल पूर्णांक srf04_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा srf04_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(काष्ठा srf04_data));
	अगर (!indio_dev) अणु
		dev_err(dev, "failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->dev = dev;
	data->cfg = of_match_device(of_srf04_match, dev)->data;

	mutex_init(&data->lock);
	init_completion(&data->rising);
	init_completion(&data->falling);

	data->gpiod_trig = devm_gpiod_get(dev, "trig", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->gpiod_trig)) अणु
		dev_err(dev, "failed to get trig-gpios: err=%ld\n",
					PTR_ERR(data->gpiod_trig));
		वापस PTR_ERR(data->gpiod_trig);
	पूर्ण

	data->gpiod_echo = devm_gpiod_get(dev, "echo", GPIOD_IN);
	अगर (IS_ERR(data->gpiod_echo)) अणु
		dev_err(dev, "failed to get echo-gpios: err=%ld\n",
					PTR_ERR(data->gpiod_echo));
		वापस PTR_ERR(data->gpiod_echo);
	पूर्ण

	data->gpiod_घातer = devm_gpiod_get_optional(dev, "power",
								GPIOD_OUT_LOW);
	अगर (IS_ERR(data->gpiod_घातer)) अणु
		dev_err(dev, "failed to get power-gpios: err=%ld\n",
						PTR_ERR(data->gpiod_घातer));
		वापस PTR_ERR(data->gpiod_घातer);
	पूर्ण
	अगर (data->gpiod_घातer) अणु

		अगर (of_property_पढ़ो_u32(dev->of_node, "startup-time-ms",
						&data->startup_समय_ms))
			data->startup_समय_ms = 100;
		dev_dbg(dev, "using power gpio: startup-time-ms=%d\n",
							data->startup_समय_ms);
	पूर्ण

	अगर (gpiod_cansleep(data->gpiod_echo)) अणु
		dev_err(data->dev, "cansleep-GPIOs not supported\n");
		वापस -ENODEV;
	पूर्ण

	data->irqnr = gpiod_to_irq(data->gpiod_echo);
	अगर (data->irqnr < 0) अणु
		dev_err(data->dev, "gpiod_to_irq: %d\n", data->irqnr);
		वापस data->irqnr;
	पूर्ण

	ret = devm_request_irq(dev, data->irqnr, srf04_handle_irq,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			pdev->name, indio_dev);
	अगर (ret < 0) अणु
		dev_err(data->dev, "request_irq: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = "srf04";
	indio_dev->info = &srf04_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = srf04_chan_spec;
	indio_dev->num_channels = ARRAY_SIZE(srf04_chan_spec);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(data->dev, "iio_device_register: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (data->gpiod_घातer) अणु
		pm_runसमय_set_स्वतःsuspend_delay(data->dev, 1000);
		pm_runसमय_use_स्वतःsuspend(data->dev);

		ret = pm_runसमय_set_active(data->dev);
		अगर (ret) अणु
			dev_err(data->dev, "pm_runtime_set_active: %d\n", ret);
			iio_device_unरेजिस्टर(indio_dev);
		पूर्ण

		pm_runसमय_enable(data->dev);
		pm_runसमय_idle(data->dev);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक srf04_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा srf04_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (data->gpiod_घातer) अणु
		pm_runसमय_disable(data->dev);
		pm_runसमय_set_suspended(data->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused srf04_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = container_of(dev,
						काष्ठा platक्रमm_device, dev);
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा srf04_data *data = iio_priv(indio_dev);

	gpiod_set_value(data->gpiod_घातer, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused srf04_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = container_of(dev,
						काष्ठा platक्रमm_device, dev);
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा srf04_data *data = iio_priv(indio_dev);

	gpiod_set_value(data->gpiod_घातer, 1);
	msleep(data->startup_समय_ms);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops srf04_pm_ops = अणु
	SET_RUNTIME_PM_OPS(srf04_pm_runसमय_suspend,
				srf04_pm_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver srf04_driver = अणु
	.probe		= srf04_probe,
	.हटाओ		= srf04_हटाओ,
	.driver		= अणु
		.name		= "srf04-gpio",
		.of_match_table	= of_srf04_match,
		.pm		= &srf04_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(srf04_driver);

MODULE_AUTHOR("Andreas Klinger <ak@it-klinger.de>");
MODULE_DESCRIPTION("SRF04 ultrasonic sensor for distance measuring using GPIOs");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:srf04");
