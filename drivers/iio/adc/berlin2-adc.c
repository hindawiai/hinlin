<शैली गुरु>
/*
 * Marvell Berlin2 ADC driver
 *
 * Copyright (C) 2015 Marvell Technology Group Ltd.
 *
 * Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/machine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sched.h>
#समावेश <linux/रुको.h>

#घोषणा BERLIN2_SM_CTRL				0x14
#घोषणा  BERLIN2_SM_CTRL_SM_SOC_INT		BIT(1)
#घोषणा  BERLIN2_SM_CTRL_SOC_SM_INT		BIT(2)
#घोषणा  BERLIN2_SM_CTRL_ADC_SEL(x)		((x) << 5)	/* 0-15 */
#घोषणा  BERLIN2_SM_CTRL_ADC_SEL_MASK		GENMASK(8, 5)
#घोषणा  BERLIN2_SM_CTRL_ADC_POWER		BIT(9)
#घोषणा  BERLIN2_SM_CTRL_ADC_CLKSEL_DIV2	(0x0 << 10)
#घोषणा  BERLIN2_SM_CTRL_ADC_CLKSEL_DIV3	(0x1 << 10)
#घोषणा  BERLIN2_SM_CTRL_ADC_CLKSEL_DIV4	(0x2 << 10)
#घोषणा  BERLIN2_SM_CTRL_ADC_CLKSEL_DIV8	(0x3 << 10)
#घोषणा  BERLIN2_SM_CTRL_ADC_CLKSEL_MASK	GENMASK(11, 10)
#घोषणा  BERLIN2_SM_CTRL_ADC_START		BIT(12)
#घोषणा  BERLIN2_SM_CTRL_ADC_RESET		BIT(13)
#घोषणा  BERLIN2_SM_CTRL_ADC_BANDGAP_RDY	BIT(14)
#घोषणा  BERLIN2_SM_CTRL_ADC_CONT_SINGLE	(0x0 << 15)
#घोषणा  BERLIN2_SM_CTRL_ADC_CONT_CONTINUOUS	(0x1 << 15)
#घोषणा  BERLIN2_SM_CTRL_ADC_BUFFER_EN		BIT(16)
#घोषणा  BERLIN2_SM_CTRL_ADC_VREF_EXT		(0x0 << 17)
#घोषणा  BERLIN2_SM_CTRL_ADC_VREF_INT		(0x1 << 17)
#घोषणा  BERLIN2_SM_CTRL_ADC_ROTATE		BIT(19)
#घोषणा  BERLIN2_SM_CTRL_TSEN_EN		BIT(20)
#घोषणा  BERLIN2_SM_CTRL_TSEN_CLK_SEL_125	(0x0 << 21)	/* 1.25 MHz */
#घोषणा  BERLIN2_SM_CTRL_TSEN_CLK_SEL_250	(0x1 << 21)	/* 2.5 MHz */
#घोषणा  BERLIN2_SM_CTRL_TSEN_MODE_0_125	(0x0 << 22)	/* 0-125 C */
#घोषणा  BERLIN2_SM_CTRL_TSEN_MODE_10_50	(0x1 << 22)	/* 10-50 C */
#घोषणा  BERLIN2_SM_CTRL_TSEN_RESET		BIT(29)
#घोषणा BERLIN2_SM_ADC_DATA			0x20
#घोषणा  BERLIN2_SM_ADC_MASK			GENMASK(9, 0)
#घोषणा BERLIN2_SM_ADC_STATUS			0x1c
#घोषणा  BERLIN2_SM_ADC_STATUS_DATA_RDY(x)	BIT(x)		/* 0-15 */
#घोषणा  BERLIN2_SM_ADC_STATUS_DATA_RDY_MASK	GENMASK(15, 0)
#घोषणा  BERLIN2_SM_ADC_STATUS_INT_EN(x)	(BIT(x) << 16)	/* 0-15 */
#घोषणा  BERLIN2_SM_ADC_STATUS_INT_EN_MASK	GENMASK(31, 16)
#घोषणा BERLIN2_SM_TSEN_STATUS			0x24
#घोषणा  BERLIN2_SM_TSEN_STATUS_DATA_RDY	BIT(0)
#घोषणा  BERLIN2_SM_TSEN_STATUS_INT_EN		BIT(1)
#घोषणा BERLIN2_SM_TSEN_DATA			0x28
#घोषणा  BERLIN2_SM_TSEN_MASK			GENMASK(9, 0)
#घोषणा BERLIN2_SM_TSEN_CTRL			0x74
#घोषणा  BERLIN2_SM_TSEN_CTRL_START		BIT(8)
#घोषणा  BERLIN2_SM_TSEN_CTRL_SETTLING_4	(0x0 << 21)	/* 4 us */
#घोषणा  BERLIN2_SM_TSEN_CTRL_SETTLING_12	(0x1 << 21)	/* 12 us */
#घोषणा  BERLIN2_SM_TSEN_CTRL_SETTLING_MASK	BIT(21)
#घोषणा  BERLIN2_SM_TSEN_CTRL_TRIM(x)		((x) << 22)
#घोषणा  BERLIN2_SM_TSEN_CTRL_TRIM_MASK		GENMASK(25, 22)

काष्ठा berlin2_adc_priv अणु
	काष्ठा regmap		*regmap;
	काष्ठा mutex		lock;
	रुको_queue_head_t	wq;
	bool			data_available;
	पूर्णांक			data;
पूर्ण;

#घोषणा BERLIN2_ADC_CHANNEL(n, t)					\
	अणु								\
		.channel		= n,				\
		.datasheet_name		= "channel"#n,			\
		.type			= t,				\
		.indexed		= 1,				\
		.info_mask_separate	= BIT(IIO_CHAN_INFO_RAW),	\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec berlin2_adc_channels[] = अणु
	BERLIN2_ADC_CHANNEL(0, IIO_VOLTAGE),	/* बाह्यal input */
	BERLIN2_ADC_CHANNEL(1, IIO_VOLTAGE),	/* बाह्यal input */
	BERLIN2_ADC_CHANNEL(2, IIO_VOLTAGE),	/* बाह्यal input */
	BERLIN2_ADC_CHANNEL(3, IIO_VOLTAGE),	/* बाह्यal input */
	BERLIN2_ADC_CHANNEL(4, IIO_VOLTAGE),	/* reserved */
	BERLIN2_ADC_CHANNEL(5, IIO_VOLTAGE),	/* reserved */
	अणु					/* temperature sensor */
		.channel		= 6,
		.datasheet_name		= "channel6",
		.type			= IIO_TEMP,
		.indexed		= 0,
		.info_mask_separate	= BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
	BERLIN2_ADC_CHANNEL(7, IIO_VOLTAGE),	/* reserved */
	IIO_CHAN_SOFT_TIMESTAMP(8),		/* बारtamp */
पूर्ण;

अटल पूर्णांक berlin2_adc_पढ़ो(काष्ठा iio_dev *indio_dev, पूर्णांक channel)
अणु
	काष्ठा berlin2_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक data, ret;

	mutex_lock(&priv->lock);

	/* Enable the पूर्णांकerrupts */
	regmap_ग_लिखो(priv->regmap, BERLIN2_SM_ADC_STATUS,
		     BERLIN2_SM_ADC_STATUS_INT_EN(channel));

	/* Configure the ADC */
	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_ADC_RESET |
			   BERLIN2_SM_CTRL_ADC_SEL_MASK |
			   BERLIN2_SM_CTRL_ADC_START,
			   BERLIN2_SM_CTRL_ADC_SEL(channel) |
			   BERLIN2_SM_CTRL_ADC_START);

	ret = रुको_event_पूर्णांकerruptible_समयout(priv->wq, priv->data_available,
					       msecs_to_jअगरfies(1000));

	/* Disable the पूर्णांकerrupts */
	regmap_update_bits(priv->regmap, BERLIN2_SM_ADC_STATUS,
			   BERLIN2_SM_ADC_STATUS_INT_EN(channel), 0);

	अगर (ret == 0)
		ret = -ETIMEDOUT;
	अगर (ret < 0) अणु
		mutex_unlock(&priv->lock);
		वापस ret;
	पूर्ण

	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_ADC_START, 0);

	data = priv->data;
	priv->data_available = false;

	mutex_unlock(&priv->lock);

	वापस data;
पूर्ण

अटल पूर्णांक berlin2_adc_tsen_पढ़ो(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा berlin2_adc_priv *priv = iio_priv(indio_dev);
	पूर्णांक data, ret;

	mutex_lock(&priv->lock);

	/* Enable पूर्णांकerrupts */
	regmap_ग_लिखो(priv->regmap, BERLIN2_SM_TSEN_STATUS,
		     BERLIN2_SM_TSEN_STATUS_INT_EN);

	/* Configure the ADC */
	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_TSEN_RESET |
			   BERLIN2_SM_CTRL_ADC_ROTATE,
			   BERLIN2_SM_CTRL_ADC_ROTATE);

	/* Configure the temperature sensor */
	regmap_update_bits(priv->regmap, BERLIN2_SM_TSEN_CTRL,
			   BERLIN2_SM_TSEN_CTRL_TRIM_MASK |
			   BERLIN2_SM_TSEN_CTRL_SETTLING_MASK |
			   BERLIN2_SM_TSEN_CTRL_START,
			   BERLIN2_SM_TSEN_CTRL_TRIM(3) |
			   BERLIN2_SM_TSEN_CTRL_SETTLING_12 |
			   BERLIN2_SM_TSEN_CTRL_START);

	ret = रुको_event_पूर्णांकerruptible_समयout(priv->wq, priv->data_available,
					       msecs_to_jअगरfies(1000));

	/* Disable पूर्णांकerrupts */
	regmap_update_bits(priv->regmap, BERLIN2_SM_TSEN_STATUS,
			   BERLIN2_SM_TSEN_STATUS_INT_EN, 0);

	अगर (ret == 0)
		ret = -ETIMEDOUT;
	अगर (ret < 0) अणु
		mutex_unlock(&priv->lock);
		वापस ret;
	पूर्ण

	regmap_update_bits(priv->regmap, BERLIN2_SM_TSEN_CTRL,
			   BERLIN2_SM_TSEN_CTRL_START, 0);

	data = priv->data;
	priv->data_available = false;

	mutex_unlock(&priv->lock);

	वापस data;
पूर्ण

अटल पूर्णांक berlin2_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
				पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक temp;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type != IIO_VOLTAGE)
			वापस -EINVAL;

		*val = berlin2_adc_पढ़ो(indio_dev, chan->channel);
		अगर (*val < 0)
			वापस *val;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_PROCESSED:
		अगर (chan->type != IIO_TEMP)
			वापस -EINVAL;

		temp = berlin2_adc_tsen_पढ़ो(indio_dev);
		अगर (temp < 0)
			वापस temp;

		अगर (temp > 2047)
			temp -= 4096;

		/* Convert to milli Celsius */
		*val = ((temp * 100000) / 264 - 270000);
		वापस IIO_VAL_INT;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t berlin2_adc_irq(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा berlin2_adc_priv *priv = iio_priv(निजी);
	अचिन्हित val;

	regmap_पढ़ो(priv->regmap, BERLIN2_SM_ADC_STATUS, &val);
	अगर (val & BERLIN2_SM_ADC_STATUS_DATA_RDY_MASK) अणु
		regmap_पढ़ो(priv->regmap, BERLIN2_SM_ADC_DATA, &priv->data);
		priv->data &= BERLIN2_SM_ADC_MASK;

		val &= ~BERLIN2_SM_ADC_STATUS_DATA_RDY_MASK;
		regmap_ग_लिखो(priv->regmap, BERLIN2_SM_ADC_STATUS, val);

		priv->data_available = true;
		wake_up_पूर्णांकerruptible(&priv->wq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t berlin2_adc_tsen_irq(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा berlin2_adc_priv *priv = iio_priv(निजी);
	अचिन्हित val;

	regmap_पढ़ो(priv->regmap, BERLIN2_SM_TSEN_STATUS, &val);
	अगर (val & BERLIN2_SM_TSEN_STATUS_DATA_RDY) अणु
		regmap_पढ़ो(priv->regmap, BERLIN2_SM_TSEN_DATA, &priv->data);
		priv->data &= BERLIN2_SM_TSEN_MASK;

		val &= ~BERLIN2_SM_TSEN_STATUS_DATA_RDY;
		regmap_ग_लिखो(priv->regmap, BERLIN2_SM_TSEN_STATUS, val);

		priv->data_available = true;
		wake_up_पूर्णांकerruptible(&priv->wq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_info berlin2_adc_info = अणु
	.पढ़ो_raw	= berlin2_adc_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक berlin2_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा berlin2_adc_priv *priv;
	काष्ठा device_node *parent_np = of_get_parent(pdev->dev.of_node);
	पूर्णांक irq, tsen_irq;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*priv));
	अगर (!indio_dev)
		वापस -ENOMEM;

	priv = iio_priv(indio_dev);
	platक्रमm_set_drvdata(pdev, indio_dev);

	priv->regmap = syscon_node_to_regmap(parent_np);
	of_node_put(parent_np);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	irq = platक्रमm_get_irq_byname(pdev, "adc");
	अगर (irq < 0)
		वापस irq;

	tsen_irq = platक्रमm_get_irq_byname(pdev, "tsen");
	अगर (tsen_irq < 0)
		वापस tsen_irq;

	ret = devm_request_irq(&pdev->dev, irq, berlin2_adc_irq, 0,
			       pdev->dev.driver->name, indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_request_irq(&pdev->dev, tsen_irq, berlin2_adc_tsen_irq,
			       0, pdev->dev.driver->name, indio_dev);
	अगर (ret)
		वापस ret;

	init_रुकोqueue_head(&priv->wq);
	mutex_init(&priv->lock);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &berlin2_adc_info;

	indio_dev->channels = berlin2_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(berlin2_adc_channels);

	/* Power up the ADC */
	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_ADC_POWER,
			   BERLIN2_SM_CTRL_ADC_POWER);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		/* Power करोwn the ADC */
		regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
				   BERLIN2_SM_CTRL_ADC_POWER, 0);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक berlin2_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा berlin2_adc_priv *priv = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	/* Power करोwn the ADC */
	regmap_update_bits(priv->regmap, BERLIN2_SM_CTRL,
			   BERLIN2_SM_CTRL_ADC_POWER, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id berlin2_adc_match[] = अणु
	अणु .compatible = "marvell,berlin2-adc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, berlin2_adc_match);

अटल काष्ठा platक्रमm_driver berlin2_adc_driver = अणु
	.driver	= अणु
		.name		= "berlin2-adc",
		.of_match_table	= berlin2_adc_match,
	पूर्ण,
	.probe	= berlin2_adc_probe,
	.हटाओ	= berlin2_adc_हटाओ,
पूर्ण;
module_platक्रमm_driver(berlin2_adc_driver);

MODULE_AUTHOR("Antoine Tenart <antoine.tenart@free-electrons.com>");
MODULE_DESCRIPTION("Marvell Berlin2 ADC driver");
MODULE_LICENSE("GPL v2");
