<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2019 Nuvoton Technology corporation.

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/पन.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/reset.h>

काष्ठा npcm_adc अणु
	bool पूर्णांक_status;
	u32 adc_sample_hz;
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *adc_clk;
	रुको_queue_head_t wq;
	काष्ठा regulator *vref;
	काष्ठा reset_control *reset;
	/*
	 * Lock to protect the device state during a potential concurrent
	 * पढ़ो access from userspace. Reading a raw value requires a sequence
	 * of रेजिस्टर ग_लिखोs, then a रुको क्रम a event and finally a रेजिस्टर
	 * पढ़ो, during which userspace could issue another पढ़ो request.
	 * This lock protects a पढ़ो access from ocurring beक्रमe another one
	 * has finished.
	 */
	काष्ठा mutex lock;
पूर्ण;

/* ADC रेजिस्टरs */
#घोषणा NPCM_ADCCON	 0x00
#घोषणा NPCM_ADCDATA	 0x04

/* ADCCON Register Bits */
#घोषणा NPCM_ADCCON_ADC_INT_EN		BIT(21)
#घोषणा NPCM_ADCCON_REFSEL		BIT(19)
#घोषणा NPCM_ADCCON_ADC_INT_ST		BIT(18)
#घोषणा NPCM_ADCCON_ADC_EN		BIT(17)
#घोषणा NPCM_ADCCON_ADC_RST		BIT(16)
#घोषणा NPCM_ADCCON_ADC_CONV		BIT(13)

#घोषणा NPCM_ADCCON_CH_MASK		GENMASK(27, 24)
#घोषणा NPCM_ADCCON_CH(x)		((x) << 24)
#घोषणा NPCM_ADCCON_DIV_SHIFT		1
#घोषणा NPCM_ADCCON_DIV_MASK		GENMASK(8, 1)
#घोषणा NPCM_ADC_DATA_MASK(x)		((x) & GENMASK(9, 0))

#घोषणा NPCM_ADC_ENABLE		(NPCM_ADCCON_ADC_EN | NPCM_ADCCON_ADC_INT_EN)

/* ADC General Definition */
#घोषणा NPCM_RESOLUTION_BITS		10
#घोषणा NPCM_INT_VREF_MV		2000

#घोषणा NPCM_ADC_CHAN(ch) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = ch,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec npcm_adc_iio_channels[] = अणु
	NPCM_ADC_CHAN(0),
	NPCM_ADC_CHAN(1),
	NPCM_ADC_CHAN(2),
	NPCM_ADC_CHAN(3),
	NPCM_ADC_CHAN(4),
	NPCM_ADC_CHAN(5),
	NPCM_ADC_CHAN(6),
	NPCM_ADC_CHAN(7),
पूर्ण;

अटल irqवापस_t npcm_adc_isr(पूर्णांक irq, व्योम *data)
अणु
	u32 regtemp;
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा npcm_adc *info = iio_priv(indio_dev);

	regtemp = ioपढ़ो32(info->regs + NPCM_ADCCON);
	अगर (regtemp & NPCM_ADCCON_ADC_INT_ST) अणु
		ioग_लिखो32(regtemp, info->regs + NPCM_ADCCON);
		wake_up_पूर्णांकerruptible(&info->wq);
		info->पूर्णांक_status = true;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक npcm_adc_पढ़ो(काष्ठा npcm_adc *info, पूर्णांक *val, u8 channel)
अणु
	पूर्णांक ret;
	u32 regtemp;

	/* Select ADC channel */
	regtemp = ioपढ़ो32(info->regs + NPCM_ADCCON);
	regtemp &= ~NPCM_ADCCON_CH_MASK;
	info->पूर्णांक_status = false;
	ioग_लिखो32(regtemp | NPCM_ADCCON_CH(channel) |
		  NPCM_ADCCON_ADC_CONV, info->regs + NPCM_ADCCON);

	ret = रुको_event_पूर्णांकerruptible_समयout(info->wq, info->पूर्णांक_status,
					       msecs_to_jअगरfies(10));
	अगर (ret == 0) अणु
		regtemp = ioपढ़ो32(info->regs + NPCM_ADCCON);
		अगर (regtemp & NPCM_ADCCON_ADC_CONV) अणु
			/* अगर conversion failed - reset ADC module */
			reset_control_निश्चित(info->reset);
			msleep(100);
			reset_control_deनिश्चित(info->reset);
			msleep(100);

			/* Enable ADC and start conversion module */
			ioग_लिखो32(NPCM_ADC_ENABLE | NPCM_ADCCON_ADC_CONV,
				  info->regs + NPCM_ADCCON);
			dev_err(info->dev, "RESET ADC Complete\n");
		पूर्ण
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (ret < 0)
		वापस ret;

	*val = NPCM_ADC_DATA_MASK(ioपढ़ो32(info->regs + NPCM_ADCDATA));

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	पूर्णांक vref_uv;
	काष्ठा npcm_adc *info = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&info->lock);
		ret = npcm_adc_पढ़ो(info, val, chan->channel);
		mutex_unlock(&info->lock);
		अगर (ret) अणु
			dev_err(info->dev, "NPCM ADC read failed\n");
			वापस ret;
		पूर्ण
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (!IS_ERR(info->vref)) अणु
			vref_uv = regulator_get_voltage(info->vref);
			*val = vref_uv / 1000;
		पूर्ण अन्यथा अणु
			*val = NPCM_INT_VREF_MV;
		पूर्ण
		*val2 = NPCM_RESOLUTION_BITS;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = info->adc_sample_hz;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info npcm_adc_iio_info = अणु
	.पढ़ो_raw = &npcm_adc_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा of_device_id npcm_adc_match[] = अणु
	अणु .compatible = "nuvoton,npcm750-adc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, npcm_adc_match);

अटल पूर्णांक npcm_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	पूर्णांक irq;
	u32 भाग;
	u32 reg_con;
	काष्ठा npcm_adc *info;
	काष्ठा iio_dev *indio_dev;
	काष्ठा device *dev = &pdev->dev;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*info));
	अगर (!indio_dev)
		वापस -ENOMEM;
	info = iio_priv(indio_dev);

	mutex_init(&info->lock);

	info->dev = &pdev->dev;

	info->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);

	info->reset = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(info->reset))
		वापस PTR_ERR(info->reset);

	info->adc_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(info->adc_clk)) अणु
		dev_warn(&pdev->dev, "ADC clock failed: can't read clk\n");
		वापस PTR_ERR(info->adc_clk);
	पूर्ण

	/* calculate ADC घड़ी sample rate */
	reg_con = ioपढ़ो32(info->regs + NPCM_ADCCON);
	भाग = reg_con & NPCM_ADCCON_DIV_MASK;
	भाग = भाग >> NPCM_ADCCON_DIV_SHIFT;
	info->adc_sample_hz = clk_get_rate(info->adc_clk) / ((भाग + 1) * 2);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		ret = -EINVAL;
		जाओ err_disable_clk;
	पूर्ण

	ret = devm_request_irq(&pdev->dev, irq, npcm_adc_isr, 0,
			       "NPCM_ADC", indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed requesting interrupt\n");
		जाओ err_disable_clk;
	पूर्ण

	reg_con = ioपढ़ो32(info->regs + NPCM_ADCCON);
	info->vref = devm_regulator_get_optional(&pdev->dev, "vref");
	अगर (!IS_ERR(info->vref)) अणु
		ret = regulator_enable(info->vref);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Can't enable ADC reference voltage\n");
			जाओ err_disable_clk;
		पूर्ण

		ioग_लिखो32(reg_con & ~NPCM_ADCCON_REFSEL,
			  info->regs + NPCM_ADCCON);
	पूर्ण अन्यथा अणु
		/*
		 * Any error which is not ENODEV indicates the regulator
		 * has been specअगरied and so is a failure हाल.
		 */
		अगर (PTR_ERR(info->vref) != -ENODEV) अणु
			ret = PTR_ERR(info->vref);
			जाओ err_disable_clk;
		पूर्ण

		/* Use पूर्णांकernal reference */
		ioग_लिखो32(reg_con | NPCM_ADCCON_REFSEL,
			  info->regs + NPCM_ADCCON);
	पूर्ण

	init_रुकोqueue_head(&info->wq);

	reg_con = ioपढ़ो32(info->regs + NPCM_ADCCON);
	reg_con |= NPCM_ADC_ENABLE;

	/* Enable the ADC Module */
	ioग_लिखो32(reg_con, info->regs + NPCM_ADCCON);

	/* Start ADC conversion */
	ioग_लिखो32(reg_con | NPCM_ADCCON_ADC_CONV, info->regs + NPCM_ADCCON);

	platक्रमm_set_drvdata(pdev, indio_dev);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &npcm_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = npcm_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(npcm_adc_iio_channels);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't register the device.\n");
		जाओ err_iio_रेजिस्टर;
	पूर्ण

	pr_info("NPCM ADC driver probed\n");

	वापस 0;

err_iio_रेजिस्टर:
	ioग_लिखो32(reg_con & ~NPCM_ADCCON_ADC_EN, info->regs + NPCM_ADCCON);
	अगर (!IS_ERR(info->vref))
		regulator_disable(info->vref);
err_disable_clk:
	clk_disable_unprepare(info->adc_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक npcm_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा npcm_adc *info = iio_priv(indio_dev);
	u32 regtemp;

	iio_device_unरेजिस्टर(indio_dev);

	regtemp = ioपढ़ो32(info->regs + NPCM_ADCCON);
	ioग_लिखो32(regtemp & ~NPCM_ADCCON_ADC_EN, info->regs + NPCM_ADCCON);
	अगर (!IS_ERR(info->vref))
		regulator_disable(info->vref);
	clk_disable_unprepare(info->adc_clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver npcm_adc_driver = अणु
	.probe		= npcm_adc_probe,
	.हटाओ		= npcm_adc_हटाओ,
	.driver		= अणु
		.name	= "npcm_adc",
		.of_match_table = npcm_adc_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(npcm_adc_driver);

MODULE_DESCRIPTION("Nuvoton NPCM ADC Driver");
MODULE_AUTHOR("Tomer Maimon <tomer.maimon@nuvoton.com>");
MODULE_LICENSE("GPL v2");
