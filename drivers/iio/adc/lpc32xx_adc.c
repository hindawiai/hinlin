<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  lpc32xx_adc.c - Support क्रम ADC in LPC32XX
 *
 *  3-channel, 10-bit ADC
 *
 *  Copyright (C) 2011, 2012 Roland Stigge <stigge@antcom.de>
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

/*
 * LPC32XX रेजिस्टरs definitions
 */
#घोषणा LPC32XXAD_SELECT(x)	((x) + 0x04)
#घोषणा LPC32XXAD_CTRL(x)	((x) + 0x08)
#घोषणा LPC32XXAD_VALUE(x)	((x) + 0x48)

/* Bit definitions क्रम LPC32XXAD_SELECT: */
/* स्थिरant, always ग_लिखो this value! */
#घोषणा LPC32XXAD_REFm         0x00000200
/* स्थिरant, always ग_लिखो this value! */
#घोषणा LPC32XXAD_REFp		0x00000080
 /* multiple of this is the channel number: 0, 1, 2 */
#घोषणा LPC32XXAD_IN		0x00000010
/* स्थिरant, always ग_लिखो this value! */
#घोषणा LPC32XXAD_INTERNAL	0x00000004

/* Bit definitions क्रम LPC32XXAD_CTRL: */
#घोषणा LPC32XXAD_STROBE	0x00000002
#घोषणा LPC32XXAD_PDN_CTRL	0x00000004

/* Bit definitions क्रम LPC32XXAD_VALUE: */
#घोषणा LPC32XXAD_VALUE_MASK	0x000003FF

#घोषणा LPC32XXAD_NAME "lpc32xx-adc"

काष्ठा lpc32xx_adc_state अणु
	व्योम __iomem *adc_base;
	काष्ठा clk *clk;
	काष्ठा completion completion;
	काष्ठा regulator *vref;

	u32 value;
पूर्ण;

अटल पूर्णांक lpc32xx_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val,
			    पूर्णांक *val2,
			    दीर्घ mask)
अणु
	काष्ठा lpc32xx_adc_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		ret = clk_prepare_enable(st->clk);
		अगर (ret) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस ret;
		पूर्ण
		/* Measurement setup */
		__raw_ग_लिखोl(LPC32XXAD_INTERNAL | (chan->address) |
			     LPC32XXAD_REFp | LPC32XXAD_REFm,
			     LPC32XXAD_SELECT(st->adc_base));
		/* Trigger conversion */
		__raw_ग_लिखोl(LPC32XXAD_PDN_CTRL | LPC32XXAD_STROBE,
			     LPC32XXAD_CTRL(st->adc_base));
		रुको_क्रम_completion(&st->completion); /* set by ISR */
		clk_disable_unprepare(st->clk);
		*val = st->value;
		mutex_unlock(&indio_dev->mlock);

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = regulator_get_voltage(st->vref) / 1000;
		*val2 =  10;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info lpc32xx_adc_iio_info = अणु
	.पढ़ो_raw = &lpc32xx_पढ़ो_raw,
पूर्ण;

#घोषणा LPC32XX_ADC_CHANNEL_BASE(_index)		\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.channel = _index,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.address = LPC32XXAD_IN * _index,		\
	.scan_index = _index,

#घोषणा LPC32XX_ADC_CHANNEL(_index) अणु		\
	LPC32XX_ADC_CHANNEL_BASE(_index)	\
पूर्ण

#घोषणा LPC32XX_ADC_SCALE_CHANNEL(_index) अणु			\
	LPC32XX_ADC_CHANNEL_BASE(_index)			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE)	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec lpc32xx_adc_iio_channels[] = अणु
	LPC32XX_ADC_CHANNEL(0),
	LPC32XX_ADC_CHANNEL(1),
	LPC32XX_ADC_CHANNEL(2),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec lpc32xx_adc_iio_scale_channels[] = अणु
	LPC32XX_ADC_SCALE_CHANNEL(0),
	LPC32XX_ADC_SCALE_CHANNEL(1),
	LPC32XX_ADC_SCALE_CHANNEL(2),
पूर्ण;

अटल irqवापस_t lpc32xx_adc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा lpc32xx_adc_state *st = dev_id;

	/* Read value and clear irq */
	st->value = __raw_पढ़ोl(LPC32XXAD_VALUE(st->adc_base)) &
		LPC32XXAD_VALUE_MASK;
	complete(&st->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lpc32xx_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_adc_state *st = शून्य;
	काष्ठा resource *res;
	पूर्णांक retval = -ENODEV;
	काष्ठा iio_dev *iodev = शून्य;
	पूर्णांक irq;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to get platform I/O memory\n");
		वापस -ENXIO;
	पूर्ण

	iodev = devm_iio_device_alloc(&pdev->dev, माप(*st));
	अगर (!iodev)
		वापस -ENOMEM;

	st = iio_priv(iodev);

	st->adc_base = devm_ioremap(&pdev->dev, res->start,
				    resource_size(res));
	अगर (!st->adc_base) अणु
		dev_err(&pdev->dev, "failed mapping memory\n");
		वापस -EBUSY;
	पूर्ण

	st->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(st->clk)) अणु
		dev_err(&pdev->dev, "failed getting clock\n");
		वापस PTR_ERR(st->clk);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -ENXIO;

	retval = devm_request_irq(&pdev->dev, irq, lpc32xx_adc_isr, 0,
				  LPC32XXAD_NAME, st);
	अगर (retval < 0) अणु
		dev_err(&pdev->dev, "failed requesting interrupt\n");
		वापस retval;
	पूर्ण

	st->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(st->vref)) अणु
		iodev->channels = lpc32xx_adc_iio_channels;
		dev_info(&pdev->dev,
			 "Missing vref regulator: No scaling available\n");
	पूर्ण अन्यथा अणु
		iodev->channels = lpc32xx_adc_iio_scale_channels;
	पूर्ण

	platक्रमm_set_drvdata(pdev, iodev);

	init_completion(&st->completion);

	iodev->name = LPC32XXAD_NAME;
	iodev->info = &lpc32xx_adc_iio_info;
	iodev->modes = INDIO_सूचीECT_MODE;
	iodev->num_channels = ARRAY_SIZE(lpc32xx_adc_iio_channels);

	retval = devm_iio_device_रेजिस्टर(&pdev->dev, iodev);
	अगर (retval)
		वापस retval;

	dev_info(&pdev->dev, "LPC32XX ADC driver loaded, IRQ %d\n", irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc32xx_adc_match[] = अणु
	अणु .compatible = "nxp,lpc3220-adc" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_adc_match);

अटल काष्ठा platक्रमm_driver lpc32xx_adc_driver = अणु
	.probe		= lpc32xx_adc_probe,
	.driver		= अणु
		.name	= LPC32XXAD_NAME,
		.of_match_table = lpc32xx_adc_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(lpc32xx_adc_driver);

MODULE_AUTHOR("Roland Stigge <stigge@antcom.de>");
MODULE_DESCRIPTION("LPC32XX ADC driver");
MODULE_LICENSE("GPL");
