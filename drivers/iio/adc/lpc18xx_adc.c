<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO ADC driver क्रम NXP LPC18xx ADC
 *
 * Copyright (C) 2016 Joachim Eastwood <manabian@gmail.com>
 *
 * UNSUPPORTED hardware features:
 *  - Hardware triggers
 *  - Burst mode
 *  - Interrupts
 *  - DMA
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

/* LPC18XX ADC रेजिस्टरs and bits */
#घोषणा LPC18XX_ADC_CR			0x000
#घोषणा  LPC18XX_ADC_CR_CLKDIV_SHIFT	8
#घोषणा  LPC18XX_ADC_CR_PDN		BIT(21)
#घोषणा  LPC18XX_ADC_CR_START_NOW	(0x1 << 24)
#घोषणा LPC18XX_ADC_GDR			0x004

/* Data रेजिस्टर bits */
#घोषणा LPC18XX_ADC_SAMPLE_SHIFT	6
#घोषणा LPC18XX_ADC_SAMPLE_MASK		0x3ff
#घोषणा LPC18XX_ADC_CONV_DONE		BIT(31)

/* Clock should be 4.5 MHz or less */
#घोषणा LPC18XX_ADC_CLK_TARGET		4500000

काष्ठा lpc18xx_adc अणु
	काष्ठा regulator *vref;
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा mutex lock;
	काष्ठा clk *clk;
	u32 cr_reg;
पूर्ण;

#घोषणा LPC18XX_ADC_CHAN(_idx) अणु				\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = _idx,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec lpc18xx_adc_iio_channels[] = अणु
	LPC18XX_ADC_CHAN(0),
	LPC18XX_ADC_CHAN(1),
	LPC18XX_ADC_CHAN(2),
	LPC18XX_ADC_CHAN(3),
	LPC18XX_ADC_CHAN(4),
	LPC18XX_ADC_CHAN(5),
	LPC18XX_ADC_CHAN(6),
	LPC18XX_ADC_CHAN(7),
पूर्ण;

अटल पूर्णांक lpc18xx_adc_पढ़ो_chan(काष्ठा lpc18xx_adc *adc, अचिन्हित पूर्णांक ch)
अणु
	पूर्णांक ret;
	u32 reg;

	reg = adc->cr_reg | BIT(ch) | LPC18XX_ADC_CR_START_NOW;
	ग_लिखोl(reg, adc->base + LPC18XX_ADC_CR);

	ret = पढ़ोl_poll_समयout(adc->base + LPC18XX_ADC_GDR, reg,
				 reg & LPC18XX_ADC_CONV_DONE, 3, 9);
	अगर (ret) अणु
		dev_warn(adc->dev, "adc read timed out\n");
		वापस ret;
	पूर्ण

	वापस (reg >> LPC18XX_ADC_SAMPLE_SHIFT) & LPC18XX_ADC_SAMPLE_MASK;
पूर्ण

अटल पूर्णांक lpc18xx_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा lpc18xx_adc *adc = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		*val = lpc18xx_adc_पढ़ो_chan(adc, chan->channel);
		mutex_unlock(&adc->lock);
		अगर (*val < 0)
			वापस *val;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = regulator_get_voltage(adc->vref) / 1000;
		*val2 = 10;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info lpc18xx_adc_info = अणु
	.पढ़ो_raw = lpc18xx_adc_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक lpc18xx_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा lpc18xx_adc *adc;
	अचिन्हित पूर्णांक clkभाग;
	अचिन्हित दीर्घ rate;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);
	adc = iio_priv(indio_dev);
	adc->dev = &pdev->dev;
	mutex_init(&adc->lock);

	adc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adc->base))
		वापस PTR_ERR(adc->base);

	adc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(adc->clk)) अणु
		dev_err(&pdev->dev, "error getting clock\n");
		वापस PTR_ERR(adc->clk);
	पूर्ण

	rate = clk_get_rate(adc->clk);
	clkभाग = DIV_ROUND_UP(rate, LPC18XX_ADC_CLK_TARGET);

	adc->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(adc->vref)) अणु
		dev_err(&pdev->dev, "error getting regulator\n");
		वापस PTR_ERR(adc->vref);
	पूर्ण

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &lpc18xx_adc_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = lpc18xx_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(lpc18xx_adc_iio_channels);

	ret = regulator_enable(adc->vref);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable regulator\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(adc->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable clock\n");
		जाओ dis_reg;
	पूर्ण

	adc->cr_reg = (clkभाग << LPC18XX_ADC_CR_CLKDIV_SHIFT) |
			LPC18XX_ADC_CR_PDN;
	ग_लिखोl(adc->cr_reg, adc->base + LPC18XX_ADC_CR);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to register device\n");
		जाओ dis_clk;
	पूर्ण

	वापस 0;

dis_clk:
	ग_लिखोl(0, adc->base + LPC18XX_ADC_CR);
	clk_disable_unprepare(adc->clk);
dis_reg:
	regulator_disable(adc->vref);
	वापस ret;
पूर्ण

अटल पूर्णांक lpc18xx_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा lpc18xx_adc *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	ग_लिखोl(0, adc->base + LPC18XX_ADC_CR);
	clk_disable_unprepare(adc->clk);
	regulator_disable(adc->vref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_adc_match[] = अणु
	अणु .compatible = "nxp,lpc1850-adc" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_adc_match);

अटल काष्ठा platक्रमm_driver lpc18xx_adc_driver = अणु
	.probe	= lpc18xx_adc_probe,
	.हटाओ	= lpc18xx_adc_हटाओ,
	.driver	= अणु
		.name = "lpc18xx-adc",
		.of_match_table = lpc18xx_adc_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc18xx_adc_driver);

MODULE_DESCRIPTION("LPC18xx ADC driver");
MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_LICENSE("GPL v2");
