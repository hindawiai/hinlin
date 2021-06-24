<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO DAC driver क्रम NXP LPC18xx DAC
 *
 * Copyright (C) 2016 Joachim Eastwood <manabian@gmail.com>
 *
 * UNSUPPORTED hardware features:
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

/* LPC18XX DAC रेजिस्टरs and bits */
#घोषणा LPC18XX_DAC_CR			0x000
#घोषणा  LPC18XX_DAC_CR_VALUE_SHIFT	6
#घोषणा  LPC18XX_DAC_CR_VALUE_MASK	0x3ff
#घोषणा  LPC18XX_DAC_CR_BIAS		BIT(16)
#घोषणा LPC18XX_DAC_CTRL		0x004
#घोषणा  LPC18XX_DAC_CTRL_DMA_ENA	BIT(3)

काष्ठा lpc18xx_dac अणु
	काष्ठा regulator *vref;
	व्योम __iomem *base;
	काष्ठा mutex lock;
	काष्ठा clk *clk;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec lpc18xx_dac_iio_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.output = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक lpc18xx_dac_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा lpc18xx_dac *dac = iio_priv(indio_dev);
	u32 reg;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		reg = पढ़ोl(dac->base + LPC18XX_DAC_CR);
		*val = reg >> LPC18XX_DAC_CR_VALUE_SHIFT;
		*val &= LPC18XX_DAC_CR_VALUE_MASK;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = regulator_get_voltage(dac->vref) / 1000;
		*val2 = 10;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक lpc18xx_dac_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा lpc18xx_dac *dac = iio_priv(indio_dev);
	u32 reg;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val < 0 || val > LPC18XX_DAC_CR_VALUE_MASK)
			वापस -EINVAL;

		reg = LPC18XX_DAC_CR_BIAS;
		reg |= val << LPC18XX_DAC_CR_VALUE_SHIFT;

		mutex_lock(&dac->lock);
		ग_लिखोl(reg, dac->base + LPC18XX_DAC_CR);
		ग_लिखोl(LPC18XX_DAC_CTRL_DMA_ENA, dac->base + LPC18XX_DAC_CTRL);
		mutex_unlock(&dac->lock);

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info lpc18xx_dac_info = अणु
	.पढ़ो_raw = lpc18xx_dac_पढ़ो_raw,
	.ग_लिखो_raw = lpc18xx_dac_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक lpc18xx_dac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा lpc18xx_dac *dac;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*dac));
	अगर (!indio_dev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, indio_dev);
	dac = iio_priv(indio_dev);
	mutex_init(&dac->lock);

	dac->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dac->base))
		वापस PTR_ERR(dac->base);

	dac->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dac->clk)) अणु
		dev_err(&pdev->dev, "error getting clock\n");
		वापस PTR_ERR(dac->clk);
	पूर्ण

	dac->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(dac->vref)) अणु
		dev_err(&pdev->dev, "error getting regulator\n");
		वापस PTR_ERR(dac->vref);
	पूर्ण

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &lpc18xx_dac_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = lpc18xx_dac_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(lpc18xx_dac_iio_channels);

	ret = regulator_enable(dac->vref);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable regulator\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(dac->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to enable clock\n");
		जाओ dis_reg;
	पूर्ण

	ग_लिखोl(0, dac->base + LPC18XX_DAC_CTRL);
	ग_लिखोl(0, dac->base + LPC18XX_DAC_CR);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to register device\n");
		जाओ dis_clk;
	पूर्ण

	वापस 0;

dis_clk:
	clk_disable_unprepare(dac->clk);
dis_reg:
	regulator_disable(dac->vref);
	वापस ret;
पूर्ण

अटल पूर्णांक lpc18xx_dac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा lpc18xx_dac *dac = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	ग_लिखोl(0, dac->base + LPC18XX_DAC_CTRL);
	clk_disable_unprepare(dac->clk);
	regulator_disable(dac->vref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc18xx_dac_match[] = अणु
	अणु .compatible = "nxp,lpc1850-dac" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc18xx_dac_match);

अटल काष्ठा platक्रमm_driver lpc18xx_dac_driver = अणु
	.probe	= lpc18xx_dac_probe,
	.हटाओ	= lpc18xx_dac_हटाओ,
	.driver	= अणु
		.name = "lpc18xx-dac",
		.of_match_table = lpc18xx_dac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lpc18xx_dac_driver);

MODULE_DESCRIPTION("LPC18xx DAC driver");
MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_LICENSE("GPL v2");
