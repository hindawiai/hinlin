<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DHT11/DHT22 bit banging GPIO driver
 *
 * Copyright (c) Harald Geyer <harald@ccbib.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/रुको.h>
#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/समयkeeping.h>

#समावेश <linux/iio/iपन.स>

#घोषणा DRIVER_NAME	"dht11"

#घोषणा DHT11_DATA_VALID_TIME	2000000000  /* 2s in ns */

#घोषणा DHT11_EDGES_PREAMBLE 2
#घोषणा DHT11_BITS_PER_READ 40
/*
 * Note that when पढ़ोing the sensor actually 84 edges are detected, but
 * since the last edge is not signअगरicant, we only store 83:
 */
#घोषणा DHT11_EDGES_PER_READ (2 * DHT11_BITS_PER_READ + \
			      DHT11_EDGES_PREAMBLE + 1)

/*
 * Data transmission timing:
 * Data bits are encoded as pulse length (high समय) on the data line.
 * 0-bit: 22-30uS -- typically 26uS (AM2302)
 * 1-bit: 68-75uS -- typically 70uS (AM2302)
 * The acutal timings also depend on the properties of the cable, with
 * दीर्घer cables typically making pulses लघुer.
 *
 * Our decoding depends on the समय resolution of the प्रणाली:
 * समयres > 34uS ... करोn't know what a 1-tick pulse is
 * 34uS > समयres > 30uS ... no problem (30kHz and 32kHz घड़ीs)
 * 30uS > समयres > 23uS ... करोn't know what a 2-tick pulse is
 * समयres < 23uS ... no problem
 *
 * Luckily घड़ीs in the 33-44kHz range are quite uncommon, so we can
 * support most प्रणालीs अगर the threshold क्रम decoding a pulse as 1-bit
 * is chosen carefully. If somebody really wants to support घड़ीs around
 * 40kHz, where this driver is most unreliable, there are two options.
 * a) select an implementation using busy loop polling on those प्रणालीs
 * b) use the checksum to करो some probabilistic decoding
 */
#घोषणा DHT11_START_TRANSMISSION_MIN	18000  /* us */
#घोषणा DHT11_START_TRANSMISSION_MAX	20000  /* us */
#घोषणा DHT11_MIN_TIMERES	34000  /* ns */
#घोषणा DHT11_THRESHOLD		49000  /* ns */
#घोषणा DHT11_AMBIG_LOW		23000  /* ns */
#घोषणा DHT11_AMBIG_HIGH	30000  /* ns */

काष्ठा dht11 अणु
	काष्ठा device			*dev;

	काष्ठा gpio_desc		*gpiod;
	पूर्णांक				irq;

	काष्ठा completion		completion;
	/* The iio sysfs पूर्णांकerface करोesn't prevent concurrent पढ़ोs: */
	काष्ठा mutex			lock;

	s64				बारtamp;
	पूर्णांक				temperature;
	पूर्णांक				humidity;

	/* num_edges: -1 means "no transmission in progress" */
	पूर्णांक				num_edges;
	काष्ठा अणुs64 ts; पूर्णांक value; पूर्ण	edges[DHT11_EDGES_PER_READ];
पूर्ण;

#अगर_घोषित CONFIG_DYNAMIC_DEBUG
/*
 * dht11_edges_prपूर्णांक: show the data as actually received by the
 *                    driver.
 */
अटल व्योम dht11_edges_prपूर्णांक(काष्ठा dht11 *dht11)
अणु
	पूर्णांक i;

	dev_dbg(dht11->dev, "%d edges detected:\n", dht11->num_edges);
	क्रम (i = 1; i < dht11->num_edges; ++i) अणु
		dev_dbg(dht11->dev, "%d: %lld ns %s\n", i,
			dht11->edges[i].ts - dht11->edges[i - 1].ts,
			dht11->edges[i - 1].value ? "high" : "low");
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_DYNAMIC_DEBUG */

अटल अचिन्हित अक्षर dht11_decode_byte(अक्षर *bits)
अणु
	अचिन्हित अक्षर ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 8; ++i) अणु
		ret <<= 1;
		अगर (bits[i])
			++ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dht11_decode(काष्ठा dht11 *dht11, पूर्णांक offset)
अणु
	पूर्णांक i, t;
	अक्षर bits[DHT11_BITS_PER_READ];
	अचिन्हित अक्षर temp_पूर्णांक, temp_dec, hum_पूर्णांक, hum_dec, checksum;

	क्रम (i = 0; i < DHT11_BITS_PER_READ; ++i) अणु
		t = dht11->edges[offset + 2 * i + 2].ts -
			dht11->edges[offset + 2 * i + 1].ts;
		अगर (!dht11->edges[offset + 2 * i + 1].value) अणु
			dev_dbg(dht11->dev,
				"lost synchronisation at edge %d\n",
				offset + 2 * i + 1);
			वापस -EIO;
		पूर्ण
		bits[i] = t > DHT11_THRESHOLD;
	पूर्ण

	hum_पूर्णांक = dht11_decode_byte(bits);
	hum_dec = dht11_decode_byte(&bits[8]);
	temp_पूर्णांक = dht11_decode_byte(&bits[16]);
	temp_dec = dht11_decode_byte(&bits[24]);
	checksum = dht11_decode_byte(&bits[32]);

	अगर (((hum_पूर्णांक + hum_dec + temp_पूर्णांक + temp_dec) & 0xff) != checksum) अणु
		dev_dbg(dht11->dev, "invalid checksum\n");
		वापस -EIO;
	पूर्ण

	dht11->बारtamp = kसमय_get_bootसमय_ns();
	अगर (hum_पूर्णांक < 4) अणु  /* DHT22: 100000 = (3*256+232)*100 */
		dht11->temperature = (((temp_पूर्णांक & 0x7f) << 8) + temp_dec) *
					((temp_पूर्णांक & 0x80) ? -100 : 100);
		dht11->humidity = ((hum_पूर्णांक << 8) + hum_dec) * 100;
	पूर्ण अन्यथा अगर (temp_dec == 0 && hum_dec == 0) अणु  /* DHT11 */
		dht11->temperature = temp_पूर्णांक * 1000;
		dht11->humidity = hum_पूर्णांक * 1000;
	पूर्ण अन्यथा अणु
		dev_err(dht11->dev,
			"Don't know how to decode data: %d %d %d %d\n",
			hum_पूर्णांक, hum_dec, temp_पूर्णांक, temp_dec);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * IRQ handler called on GPIO edges
 */
अटल irqवापस_t dht11_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *iio = data;
	काष्ठा dht11 *dht11 = iio_priv(iio);

	अगर (dht11->num_edges < DHT11_EDGES_PER_READ && dht11->num_edges >= 0) अणु
		dht11->edges[dht11->num_edges].ts = kसमय_get_bootसमय_ns();
		dht11->edges[dht11->num_edges++].value =
						gpiod_get_value(dht11->gpiod);

		अगर (dht11->num_edges >= DHT11_EDGES_PER_READ)
			complete(&dht11->completion);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dht11_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			  स्थिर काष्ठा iio_chan_spec *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा dht11 *dht11 = iio_priv(iio_dev);
	पूर्णांक ret, समयres, offset;

	mutex_lock(&dht11->lock);
	अगर (dht11->बारtamp + DHT11_DATA_VALID_TIME < kसमय_get_bootसमय_ns()) अणु
		समयres = kसमय_get_resolution_ns();
		dev_dbg(dht11->dev, "current timeresolution: %dns\n", समयres);
		अगर (समयres > DHT11_MIN_TIMERES) अणु
			dev_err(dht11->dev, "timeresolution %dns too low\n",
				समयres);
			/* In theory a better घड़ी could become available
			 * at some poपूर्णांक ... and there is no error code
			 * that really fits better.
			 */
			ret = -EAGAIN;
			जाओ err;
		पूर्ण
		अगर (समयres > DHT11_AMBIG_LOW && समयres < DHT11_AMBIG_HIGH)
			dev_warn(dht11->dev,
				 "timeresolution: %dns - decoding ambiguous\n",
				 समयres);

		reinit_completion(&dht11->completion);

		dht11->num_edges = 0;
		ret = gpiod_direction_output(dht11->gpiod, 0);
		अगर (ret)
			जाओ err;
		usleep_range(DHT11_START_TRANSMISSION_MIN,
			     DHT11_START_TRANSMISSION_MAX);
		ret = gpiod_direction_input(dht11->gpiod);
		अगर (ret)
			जाओ err;

		ret = request_irq(dht11->irq, dht11_handle_irq,
				  IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
				  iio_dev->name, iio_dev);
		अगर (ret)
			जाओ err;

		ret = रुको_क्रम_completion_समाप्तable_समयout(&dht11->completion,
							   HZ);

		मुक्त_irq(dht11->irq, iio_dev);

#अगर_घोषित CONFIG_DYNAMIC_DEBUG
		dht11_edges_prपूर्णांक(dht11);
#पूर्ण_अगर

		अगर (ret == 0 && dht11->num_edges < DHT11_EDGES_PER_READ - 1) अणु
			dev_err(dht11->dev, "Only %d signal edges detected\n",
				dht11->num_edges);
			ret = -ETIMEDOUT;
		पूर्ण
		अगर (ret < 0)
			जाओ err;

		offset = DHT11_EDGES_PREAMBLE +
				dht11->num_edges - DHT11_EDGES_PER_READ;
		क्रम (; offset >= 0; --offset) अणु
			ret = dht11_decode(dht11, offset);
			अगर (!ret)
				अवरोध;
		पूर्ण

		अगर (ret)
			जाओ err;
	पूर्ण

	ret = IIO_VAL_INT;
	अगर (chan->type == IIO_TEMP)
		*val = dht11->temperature;
	अन्यथा अगर (chan->type == IIO_HUMIDITYRELATIVE)
		*val = dht11->humidity;
	अन्यथा
		ret = -EINVAL;
err:
	dht11->num_edges = -1;
	mutex_unlock(&dht11->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info dht11_iio_info = अणु
	.पढ़ो_raw		= dht11_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec dht11_chan_spec[] = अणु
	अणु .type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED), पूर्ण,
	अणु .type = IIO_HUMIDITYRELATIVE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED), पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id dht11_dt_ids[] = अणु
	अणु .compatible = "dht11", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dht11_dt_ids);

अटल पूर्णांक dht11_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dht11 *dht11;
	काष्ठा iio_dev *iio;

	iio = devm_iio_device_alloc(dev, माप(*dht11));
	अगर (!iio) अणु
		dev_err(dev, "Failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण

	dht11 = iio_priv(iio);
	dht11->dev = dev;
	dht11->gpiod = devm_gpiod_get(dev, शून्य, GPIOD_IN);
	अगर (IS_ERR(dht11->gpiod))
		वापस PTR_ERR(dht11->gpiod);

	dht11->irq = gpiod_to_irq(dht11->gpiod);
	अगर (dht11->irq < 0) अणु
		dev_err(dev, "GPIO %d has no interrupt\n", desc_to_gpio(dht11->gpiod));
		वापस -EINVAL;
	पूर्ण

	dht11->बारtamp = kसमय_get_bootसमय_ns() - DHT11_DATA_VALID_TIME - 1;
	dht11->num_edges = -1;

	platक्रमm_set_drvdata(pdev, iio);

	init_completion(&dht11->completion);
	mutex_init(&dht11->lock);
	iio->name = pdev->name;
	iio->info = &dht11_iio_info;
	iio->modes = INDIO_सूचीECT_MODE;
	iio->channels = dht11_chan_spec;
	iio->num_channels = ARRAY_SIZE(dht11_chan_spec);

	वापस devm_iio_device_रेजिस्टर(dev, iio);
पूर्ण

अटल काष्ठा platक्रमm_driver dht11_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = dht11_dt_ids,
	पूर्ण,
	.probe  = dht11_probe,
पूर्ण;

module_platक्रमm_driver(dht11_driver);

MODULE_AUTHOR("Harald Geyer <harald@ccbib.org>");
MODULE_DESCRIPTION("DHT11 humidity/temperature sensor driver");
MODULE_LICENSE("GPL v2");
