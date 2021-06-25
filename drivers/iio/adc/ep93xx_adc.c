<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम ADC module on the Cirrus Logic EP93xx series of SoCs
 *
 * Copyright (C) 2015 Alexander Sverdlin
 *
 * The driver uses polling to get the conversion status. According to EP93xx
 * datasheets, पढ़ोing ADCResult रेजिस्टर starts the conversion, but user is also
 * responsible क्रम ensuring that delay between adjacent conversion triggers is
 * दीर्घ enough so that maximum allowed conversion rate is not exceeded. This
 * basically renders IRQ mode unusable.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पन.स>
#समावेश <linux/irqflags.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * This code could benefit from real HR Timers, but jअगरfy granularity would
 * lower ADC conversion rate करोwn to CONFIG_HZ, so we fallback to busy रुको
 * in such हाल.
 *
 * HR Timers-based version loads CPU only up to 10% during back to back ADC
 * conversion, जबतक busy रुको-based version consumes whole CPU घातer.
 */
#अगर_घोषित CONFIG_HIGH_RES_TIMERS
#घोषणा ep93xx_adc_delay(usmin, usmax) usleep_range(usmin, usmax)
#अन्यथा
#घोषणा ep93xx_adc_delay(usmin, usmax) udelay(usmin)
#पूर्ण_अगर

#घोषणा EP93XX_ADC_RESULT	0x08
#घोषणा   EP93XX_ADC_SDR	BIT(31)
#घोषणा EP93XX_ADC_SWITCH	0x18
#घोषणा EP93XX_ADC_SW_LOCK	0x20

काष्ठा ep93xx_adc_priv अणु
	काष्ठा clk *clk;
	व्योम __iomem *base;
	पूर्णांक lastch;
	काष्ठा mutex lock;
पूर्ण;

#घोषणा EP93XX_ADC_CH(index, dname, swcfg) अणु			\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = index,					\
	.address = swcfg,					\
	.datasheet_name = dname,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SCALE) |	\
				   BIT(IIO_CHAN_INFO_OFFSET),	\
पूर्ण

/*
 * Numbering scheme क्रम channels 0..4 is defined in EP9301 and EP9302 datasheets.
 * EP9307, EP9312 and EP9312 have 3 channels more (total 8), but the numbering is
 * not defined. So the last three are numbered अक्रमomly, let's say.
 */
अटल स्थिर काष्ठा iio_chan_spec ep93xx_adc_channels[8] = अणु
	EP93XX_ADC_CH(0, "YM",	0x608),
	EP93XX_ADC_CH(1, "SXP",	0x680),
	EP93XX_ADC_CH(2, "SXM",	0x640),
	EP93XX_ADC_CH(3, "SYP",	0x620),
	EP93XX_ADC_CH(4, "SYM",	0x610),
	EP93XX_ADC_CH(5, "XP",	0x601),
	EP93XX_ADC_CH(6, "XM",	0x602),
	EP93XX_ADC_CH(7, "YP",	0x604),
पूर्ण;

अटल पूर्णांक ep93xx_पढ़ो_raw(काष्ठा iio_dev *iiodev,
			   काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value,
			   पूर्णांक *shअगरt, दीर्घ mask)
अणु
	काष्ठा ep93xx_adc_priv *priv = iio_priv(iiodev);
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&priv->lock);
		अगर (priv->lastch != channel->channel) अणु
			priv->lastch = channel->channel;
			/*
			 * Switch रेजिस्टर is software-locked, unlocking must be
			 * immediately followed by ग_लिखो
			 */
			local_irq_disable();
			ग_लिखोl_relaxed(0xAA, priv->base + EP93XX_ADC_SW_LOCK);
			ग_लिखोl_relaxed(channel->address,
				       priv->base + EP93XX_ADC_SWITCH);
			local_irq_enable();
			/*
			 * Settling delay depends on module घड़ी and could be
			 * 2ms or 500us
			 */
			ep93xx_adc_delay(2000, 2000);
		पूर्ण
		/* Start the conversion, eventually discarding old result */
		पढ़ोl_relaxed(priv->base + EP93XX_ADC_RESULT);
		/* Ensure maximum conversion rate is not exceeded */
		ep93xx_adc_delay(DIV_ROUND_UP(1000000, 925),
				 DIV_ROUND_UP(1000000, 925));
		/* At this poपूर्णांक conversion must be completed, but anyway... */
		ret = IIO_VAL_INT;
		समयout = jअगरfies + msecs_to_jअगरfies(1) + 1;
		जबतक (1) अणु
			u32 t;

			t = पढ़ोl_relaxed(priv->base + EP93XX_ADC_RESULT);
			अगर (t & EP93XX_ADC_SDR) अणु
				*value = sign_extend32(t, 15);
				अवरोध;
			पूर्ण

			अगर (समय_after(jअगरfies, समयout)) अणु
				dev_err(&iiodev->dev, "Conversion timeout\n");
				ret = -ETIMEDOUT;
				अवरोध;
			पूर्ण

			cpu_relax();
		पूर्ण
		mutex_unlock(&priv->lock);
		वापस ret;

	हाल IIO_CHAN_INFO_OFFSET:
		/* According to datasheet, range is -25000..25000 */
		*value = 25000;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		/* Typical supply voltage is 3.3v */
		*value = (1ULL << 32) * 3300 / 50000;
		*shअगरt = 32;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ep93xx_adc_info = अणु
	.पढ़ो_raw = ep93xx_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ep93xx_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *iiodev;
	काष्ठा ep93xx_adc_priv *priv;
	काष्ठा clk *pclk;
	काष्ठा resource *res;

	iiodev = devm_iio_device_alloc(&pdev->dev, माप(*priv));
	अगर (!iiodev)
		वापस -ENOMEM;
	priv = iio_priv(iiodev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(priv->base)) अणु
		dev_err(&pdev->dev, "Cannot map memory resource\n");
		वापस PTR_ERR(priv->base);
	पूर्ण

	iiodev->name = dev_name(&pdev->dev);
	iiodev->modes = INDIO_सूचीECT_MODE;
	iiodev->info = &ep93xx_adc_info;
	iiodev->num_channels = ARRAY_SIZE(ep93xx_adc_channels);
	iiodev->channels = ep93xx_adc_channels;

	priv->lastch = -1;
	mutex_init(&priv->lock);

	platक्रमm_set_drvdata(pdev, iiodev);

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "Cannot obtain clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	pclk = clk_get_parent(priv->clk);
	अगर (!pclk) अणु
		dev_warn(&pdev->dev, "Cannot obtain parent clock\n");
	पूर्ण अन्यथा अणु
		/*
		 * This is actually a place क्रम improvement:
		 * EP93xx ADC supports two घड़ी भागisors -- 4 and 16,
		 * resulting in conversion rates 3750 and 925 samples per second
		 * with 500us or 2ms settling समय respectively.
		 * One might find this पूर्णांकeresting enough to be configurable.
		 */
		ret = clk_set_rate(priv->clk, clk_get_rate(pclk) / 16);
		अगर (ret)
			dev_warn(&pdev->dev, "Cannot set clock rate\n");
		/*
		 * We can tolerate rate setting failure because the module should
		 * work in any हाल.
		 */
	पूर्ण

	ret = clk_enable(priv->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable clock\n");
		वापस ret;
	पूर्ण

	ret = iio_device_रेजिस्टर(iiodev);
	अगर (ret)
		clk_disable(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक ep93xx_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *iiodev = platक्रमm_get_drvdata(pdev);
	काष्ठा ep93xx_adc_priv *priv = iio_priv(iiodev);

	iio_device_unरेजिस्टर(iiodev);
	clk_disable(priv->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_adc_driver = अणु
	.driver = अणु
		.name = "ep93xx-adc",
	पूर्ण,
	.probe = ep93xx_adc_probe,
	.हटाओ = ep93xx_adc_हटाओ,
पूर्ण;
module_platक्रमm_driver(ep93xx_adc_driver);

MODULE_AUTHOR("Alexander Sverdlin <alexander.sverdlin@gmail.com>");
MODULE_DESCRIPTION("Cirrus Logic EP93XX ADC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ep93xx-adc");
