<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PING: ultrasonic sensor क्रम distance measuring by using only one GPIOs
 *
 * Copyright (c) 2019 Andreas Klinger <ak@it-klinger.de>
 *
 * For details about the devices see:
 * http://parallax.com/sites/शेष/files/करोwnloads/28041-LaserPING-2m-Rangefinder-Guide.pdf
 * http://parallax.com/sites/शेष/files/करोwnloads/28015-PING-Documentation-v1.6.pdf
 *
 * the measurement cycle as timing diagram looks like:
 *
 * GPIO      ___              ________________________
 * ping:  __/   \____________/                        \________________
 *          ^   ^            ^                        ^
 *          |<->|            पूर्णांकerrupt                पूर्णांकerrupt
 *         udelay(5)         (ts_rising)              (ts_falling)
 *                           |<---------------------->|
 *                           .  pulse समय measured   .
 *                           .  --> one round trip of ultra sonic waves
 * ultra                     .                        .
 * sonic            _   _   _.                        .
 * burst: _________/ \_/ \_/ \_________________________________________
 *                                                    .
 * ultra                                              .
 * sonic                                     _   _   _.
 * echo:  __________________________________/ \_/ \_/ \________________
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
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

काष्ठा ping_cfg अणु
	अचिन्हित दीर्घ	trigger_pulse_us;	/* length of trigger pulse */
	पूर्णांक		laserping_error;	/* support error code in */
						/*   pulse width of laser */
						/*   ping sensors */
	s64		समयout_ns;		/* समयout in ns */
पूर्ण;

काष्ठा ping_data अणु
	काष्ठा device		*dev;
	काष्ठा gpio_desc	*gpiod_ping;
	काष्ठा mutex		lock;
	पूर्णांक			irqnr;
	kसमय_प्रकार			ts_rising;
	kसमय_प्रकार			ts_falling;
	काष्ठा completion	rising;
	काष्ठा completion	falling;
	स्थिर काष्ठा ping_cfg	*cfg;
पूर्ण;

अटल स्थिर काष्ठा ping_cfg pa_ping_cfg = अणु
	.trigger_pulse_us	= 5,
	.laserping_error	= 0,
	.समयout_ns		= 18500000,	/* 3 meters */
पूर्ण;

अटल स्थिर काष्ठा ping_cfg pa_laser_ping_cfg = अणु
	.trigger_pulse_us	= 5,
	.laserping_error	= 1,
	.समयout_ns		= 15500000,	/* 2 meters plus error codes */
पूर्ण;

अटल irqवापस_t ping_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा iio_dev *indio_dev = dev_id;
	काष्ठा ping_data *data = iio_priv(indio_dev);
	kसमय_प्रकार now = kसमय_get();

	अगर (gpiod_get_value(data->gpiod_ping)) अणु
		data->ts_rising = now;
		complete(&data->rising);
	पूर्ण अन्यथा अणु
		data->ts_falling = now;
		complete(&data->falling);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ping_पढ़ो(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ping_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	kसमय_प्रकार kसमय_dt;
	s64 dt_ns;
	u32 समय_ns, distance_mm;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(data->dev);

	/*
	 * just one पढ़ो-echo-cycle can take place at a समय
	 * ==> lock against concurrent पढ़ोing calls
	 */
	mutex_lock(&data->lock);

	reinit_completion(&data->rising);
	reinit_completion(&data->falling);

	gpiod_set_value(data->gpiod_ping, 1);
	udelay(data->cfg->trigger_pulse_us);
	gpiod_set_value(data->gpiod_ping, 0);

	ret = gpiod_direction_input(data->gpiod_ping);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	data->irqnr = gpiod_to_irq(data->gpiod_ping);
	अगर (data->irqnr < 0) अणु
		dev_err(data->dev, "gpiod_to_irq: %d\n", data->irqnr);
		mutex_unlock(&data->lock);
		वापस data->irqnr;
	पूर्ण

	ret = request_irq(data->irqnr, ping_handle_irq,
				IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
							pdev->name, indio_dev);
	अगर (ret < 0) अणु
		dev_err(data->dev, "request_irq: %d\n", ret);
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	/* it should not take more than 20 ms until echo is rising */
	ret = रुको_क्रम_completion_समाप्तable_समयout(&data->rising, HZ/50);
	अगर (ret < 0)
		जाओ err_reset_direction;
	अन्यथा अगर (ret == 0) अणु
		ret = -ETIMEDOUT;
		जाओ err_reset_direction;
	पूर्ण

	/* it cannot take more than 50 ms until echo is falling */
	ret = रुको_क्रम_completion_समाप्तable_समयout(&data->falling, HZ/20);
	अगर (ret < 0)
		जाओ err_reset_direction;
	अन्यथा अगर (ret == 0) अणु
		ret = -ETIMEDOUT;
		जाओ err_reset_direction;
	पूर्ण

	kसमय_dt = kसमय_sub(data->ts_falling, data->ts_rising);

	मुक्त_irq(data->irqnr, indio_dev);

	ret = gpiod_direction_output(data->gpiod_ping, GPIOD_OUT_LOW);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	mutex_unlock(&data->lock);

	dt_ns = kसमय_प्रकारo_ns(kसमय_dt);
	अगर (dt_ns > data->cfg->समयout_ns) अणु
		dev_dbg(data->dev, "distance out of range: dt=%lldns\n",
								dt_ns);
		वापस -EIO;
	पूर्ण

	समय_ns = dt_ns;

	/*
	 * पढ़ो error code of laser ping sensor and give users chance to
	 * figure out error by using dynamic debuggging
	 */
	अगर (data->cfg->laserping_error) अणु
		अगर ((समय_ns > 12500000) && (समय_ns <= 13500000)) अणु
			dev_dbg(data->dev, "target too close or to far\n");
			वापस -EIO;
		पूर्ण
		अगर ((समय_ns > 13500000) && (समय_ns <= 14500000)) अणु
			dev_dbg(data->dev, "internal sensor error\n");
			वापस -EIO;
		पूर्ण
		अगर ((समय_ns > 14500000) && (समय_ns <= 15500000)) अणु
			dev_dbg(data->dev, "internal sensor timeout\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

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
	 *             समय     343,5     समय * 232
	 * distance = ------ * ------- = ------------
	 *             10^6         2        1350800
	 *   with समय in ns
	 *   and distance in mm (one way)
	 *
	 * because we limit to 3 meters the multiplication with 232 just
	 * fits पूर्णांकo 32 bit
	 */
	distance_mm = समय_ns * 232 / 1350800;

	वापस distance_mm;

err_reset_direction:
	मुक्त_irq(data->irqnr, indio_dev);
	mutex_unlock(&data->lock);

	अगर (gpiod_direction_output(data->gpiod_ping, GPIOD_OUT_LOW))
		dev_dbg(data->dev, "error in gpiod_direction_output\n");
	वापस ret;
पूर्ण

अटल पूर्णांक ping_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ info)
अणु
	पूर्णांक ret;

	अगर (channel->type != IIO_DISTANCE)
		वापस -EINVAL;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ping_पढ़ो(indio_dev);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/*
		 * maximum resolution in datasheet is 1 mm
		 * 1 LSB is 1 mm
		 */
		*val = 0;
		*val2 = 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info ping_iio_info = अणु
	.पढ़ो_raw		= ping_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ping_chan_spec[] = अणु
	अणु
		.type = IIO_DISTANCE,
		.info_mask_separate =
				BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id of_ping_match[] = अणु
	अणु .compatible = "parallax,ping", .data = &pa_ping_cfgपूर्ण,
	अणु .compatible = "parallax,laserping", .data = &pa_laser_ping_cfgपूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_ping_match);

अटल पूर्णांक ping_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ping_data *data;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, माप(काष्ठा ping_data));
	अगर (!indio_dev) अणु
		dev_err(dev, "failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->dev = dev;
	data->cfg = of_device_get_match_data(dev);

	mutex_init(&data->lock);
	init_completion(&data->rising);
	init_completion(&data->falling);

	data->gpiod_ping = devm_gpiod_get(dev, "ping", GPIOD_OUT_LOW);
	अगर (IS_ERR(data->gpiod_ping)) अणु
		dev_err(dev, "failed to get ping-gpios: err=%ld\n",
						PTR_ERR(data->gpiod_ping));
		वापस PTR_ERR(data->gpiod_ping);
	पूर्ण

	अगर (gpiod_cansleep(data->gpiod_ping)) अणु
		dev_err(data->dev, "cansleep-GPIOs not supported\n");
		वापस -ENODEV;
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = "ping";
	indio_dev->info = &ping_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ping_chan_spec;
	indio_dev->num_channels = ARRAY_SIZE(ping_chan_spec);

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver ping_driver = अणु
	.probe		= ping_probe,
	.driver		= अणु
		.name		= "ping-gpio",
		.of_match_table	= of_ping_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ping_driver);

MODULE_AUTHOR("Andreas Klinger <ak@it-klinger.de>");
MODULE_DESCRIPTION("PING sensors for distance measuring using one GPIOs");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ping");
