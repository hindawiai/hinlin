<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  STMicroelectronics STMPE811 IIO ADC Driver
 *
 *  4 channel, 10/12-bit ADC
 *
 *  Copyright (C) 2013-2018 Toradex AG <stefan.agner@toradex.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/sपंचांगpe.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>

#घोषणा STMPE_REG_INT_STA		0x0B
#घोषणा STMPE_REG_ADC_INT_EN		0x0E
#घोषणा STMPE_REG_ADC_INT_STA		0x0F

#घोषणा STMPE_REG_ADC_CTRL1		0x20
#घोषणा STMPE_REG_ADC_CTRL2		0x21
#घोषणा STMPE_REG_ADC_CAPT		0x22
#घोषणा STMPE_REG_ADC_DATA_CH(channel)	(0x30 + 2 * (channel))

#घोषणा STMPE_REG_TEMP_CTRL		0x60
#घोषणा STMPE_TEMP_CTRL_ENABLE		BIT(0)
#घोषणा STMPE_TEMP_CTRL_ACQ		BIT(1)
#घोषणा STMPE_TEMP_CTRL_THRES_EN	BIT(3)
#घोषणा STMPE_START_ONE_TEMP_CONV	(STMPE_TEMP_CTRL_ENABLE | \
					STMPE_TEMP_CTRL_ACQ | \
					STMPE_TEMP_CTRL_THRES_EN)
#घोषणा STMPE_REG_TEMP_DATA		0x61
#घोषणा STMPE_REG_TEMP_TH		0x63
#घोषणा STMPE_ADC_LAST_NR		7
#घोषणा STMPE_TEMP_CHANNEL		(STMPE_ADC_LAST_NR + 1)

#घोषणा STMPE_ADC_CH(channel)		((1 << (channel)) & 0xff)

#घोषणा STMPE_ADC_TIMEOUT		msecs_to_jअगरfies(1000)

काष्ठा sपंचांगpe_adc अणु
	काष्ठा sपंचांगpe *sपंचांगpe;
	काष्ठा clk *clk;
	काष्ठा device *dev;
	काष्ठा mutex lock;

	/* We are allocating plus one क्रम the temperature channel */
	काष्ठा iio_chan_spec sपंचांगpe_adc_iio_channels[STMPE_ADC_LAST_NR + 2];

	काष्ठा completion completion;

	u8 channel;
	u32 value;
पूर्ण;

अटल पूर्णांक sपंचांगpe_पढ़ो_voltage(काष्ठा sपंचांगpe_adc *info,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	दीर्घ ret;

	mutex_lock(&info->lock);

	reinit_completion(&info->completion);

	info->channel = (u8)chan->channel;

	अगर (info->channel > STMPE_ADC_LAST_NR) अणु
		mutex_unlock(&info->lock);
		वापस -EINVAL;
	पूर्ण

	sपंचांगpe_reg_ग_लिखो(info->sपंचांगpe, STMPE_REG_ADC_CAPT,
			STMPE_ADC_CH(info->channel));

	ret = रुको_क्रम_completion_समयout(&info->completion, STMPE_ADC_TIMEOUT);

	अगर (ret <= 0) अणु
		sपंचांगpe_reg_ग_लिखो(info->sपंचांगpe, STMPE_REG_ADC_INT_STA,
				STMPE_ADC_CH(info->channel));
		mutex_unlock(&info->lock);
		वापस -ETIMEDOUT;
	पूर्ण

	*val = info->value;

	mutex_unlock(&info->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_पढ़ो_temp(काष्ठा sपंचांगpe_adc *info,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	दीर्घ ret;

	mutex_lock(&info->lock);

	reinit_completion(&info->completion);

	info->channel = (u8)chan->channel;

	अगर (info->channel != STMPE_TEMP_CHANNEL) अणु
		mutex_unlock(&info->lock);
		वापस -EINVAL;
	पूर्ण

	sपंचांगpe_reg_ग_लिखो(info->sपंचांगpe, STMPE_REG_TEMP_CTRL,
			STMPE_START_ONE_TEMP_CONV);

	ret = रुको_क्रम_completion_समयout(&info->completion, STMPE_ADC_TIMEOUT);

	अगर (ret <= 0) अणु
		mutex_unlock(&info->lock);
		वापस -ETIMEDOUT;
	पूर्ण

	/*
	 * असलolute temp = +V3.3 * value /7.51 [K]
	 * scale to [milli तओC]
	 */
	*val = ((449960l * info->value) / 1024l) - 273150;

	mutex_unlock(&info->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val,
			  पूर्णांक *val2,
			  दीर्घ mask)
अणु
	काष्ठा sपंचांगpe_adc *info = iio_priv(indio_dev);
	दीर्घ ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:

		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			ret = sपंचांगpe_पढ़ो_voltage(info, chan, val);
			अवरोध;

		हाल IIO_TEMP:
			ret = sपंचांगpe_पढ़ो_temp(info, chan, val);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		अगर (ret < 0)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = 3300;
		*val2 = info->sपंचांगpe->mod_12b ? 12 : 10;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t sपंचांगpe_adc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sपंचांगpe_adc *info = (काष्ठा sपंचांगpe_adc *)dev_id;
	__be16 data;

	अगर (info->channel <= STMPE_ADC_LAST_NR) अणु
		पूर्णांक पूर्णांक_sta;

		पूर्णांक_sta = sपंचांगpe_reg_पढ़ो(info->sपंचांगpe, STMPE_REG_ADC_INT_STA);

		/* Is the पूर्णांकerrupt relevant */
		अगर (!(पूर्णांक_sta & STMPE_ADC_CH(info->channel)))
			वापस IRQ_NONE;

		/* Read value */
		sपंचांगpe_block_पढ़ो(info->sपंचांगpe,
			STMPE_REG_ADC_DATA_CH(info->channel), 2, (u8 *) &data);

		sपंचांगpe_reg_ग_लिखो(info->sपंचांगpe, STMPE_REG_ADC_INT_STA, पूर्णांक_sta);
	पूर्ण अन्यथा अगर (info->channel == STMPE_TEMP_CHANNEL) अणु
		/* Read value */
		sपंचांगpe_block_पढ़ो(info->sपंचांगpe, STMPE_REG_TEMP_DATA, 2,
				(u8 *) &data);
	पूर्ण अन्यथा अणु
		वापस IRQ_NONE;
	पूर्ण

	info->value = (u32) be16_to_cpu(data);
	complete(&info->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_info sपंचांगpe_adc_iio_info = अणु
	.पढ़ो_raw = &sपंचांगpe_पढ़ो_raw,
पूर्ण;

अटल व्योम sपंचांगpe_adc_voltage_chan(काष्ठा iio_chan_spec *ics, पूर्णांक chan)
अणु
	ics->type = IIO_VOLTAGE;
	ics->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	ics->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
	ics->indexed = 1;
	ics->channel = chan;
पूर्ण

अटल व्योम sपंचांगpe_adc_temp_chan(काष्ठा iio_chan_spec *ics, पूर्णांक chan)
अणु
	ics->type = IIO_TEMP;
	ics->info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED);
	ics->indexed = 1;
	ics->channel = chan;
पूर्ण

अटल पूर्णांक sपंचांगpe_adc_init_hw(काष्ठा sपंचांगpe_adc *adc)
अणु
	पूर्णांक ret;
	काष्ठा sपंचांगpe *sपंचांगpe = adc->sपंचांगpe;

	ret = sपंचांगpe_enable(sपंचांगpe, STMPE_BLOCK_ADC);
	अगर (ret) अणु
		dev_err(sपंचांगpe->dev, "Could not enable clock for ADC\n");
		वापस ret;
	पूर्ण

	ret = sपंचांगpe811_adc_common_init(sपंचांगpe);
	अगर (ret) अणु
		sपंचांगpe_disable(sपंचांगpe, STMPE_BLOCK_ADC);
		वापस ret;
	पूर्ण

	/* use temp irq क्रम each conversion completion */
	sपंचांगpe_reg_ग_लिखो(sपंचांगpe, STMPE_REG_TEMP_TH, 0);
	sपंचांगpe_reg_ग_लिखो(sपंचांगpe, STMPE_REG_TEMP_TH + 1, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांगpe_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा sपंचांगpe_adc *info;
	काष्ठा device_node *np;
	u32 norequest_mask = 0;
	पूर्णांक irq_temp, irq_adc;
	पूर्णांक num_chan = 0;
	पूर्णांक i = 0;
	पूर्णांक ret;

	irq_adc = platक्रमm_get_irq_byname(pdev, "STMPE_ADC");
	अगर (irq_adc < 0)
		वापस irq_adc;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(काष्ठा sपंचांगpe_adc));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	info = iio_priv(indio_dev);
	mutex_init(&info->lock);

	init_completion(&info->completion);
	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq_adc, शून्य,
					sपंचांगpe_adc_isr, IRQF_ONESHOT,
					"stmpe-adc", info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed requesting irq, irq = %d\n",
				irq_adc);
		वापस ret;
	पूर्ण

	irq_temp = platक्रमm_get_irq_byname(pdev, "STMPE_TEMP_SENS");
	अगर (irq_temp >= 0) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq_temp, शून्य,
						sपंचांगpe_adc_isr, IRQF_ONESHOT,
						"stmpe-adc", info);
		अगर (ret < 0)
			dev_warn(&pdev->dev, "failed requesting irq for"
				 " temp sensor, irq = %d\n", irq_temp);
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name		= dev_name(&pdev->dev);
	indio_dev->info		= &sपंचांगpe_adc_iio_info;
	indio_dev->modes	= INDIO_सूचीECT_MODE;

	info->sपंचांगpe = dev_get_drvdata(pdev->dev.parent);

	np = pdev->dev.of_node;

	अगर (!np)
		dev_err(&pdev->dev, "no device tree node found\n");

	of_property_पढ़ो_u32(np, "st,norequest-mask", &norequest_mask);

	क्रम_each_clear_bit(i, (अचिन्हित दीर्घ *) &norequest_mask,
			   (STMPE_ADC_LAST_NR + 1)) अणु
		sपंचांगpe_adc_voltage_chan(&info->sपंचांगpe_adc_iio_channels[num_chan], i);
		num_chan++;
	पूर्ण
	sपंचांगpe_adc_temp_chan(&info->sपंचांगpe_adc_iio_channels[num_chan], i);
	num_chan++;
	indio_dev->channels = info->sपंचांगpe_adc_iio_channels;
	indio_dev->num_channels = num_chan;

	ret = sपंचांगpe_adc_init_hw(info);
	अगर (ret)
		वापस ret;

	sपंचांगpe_reg_ग_लिखो(info->sपंचांगpe, STMPE_REG_ADC_INT_EN,
			~(norequest_mask & 0xFF));

	sपंचांगpe_reg_ग_लिखो(info->sपंचांगpe, STMPE_REG_ADC_INT_STA,
			~(norequest_mask & 0xFF));

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांगpe_adc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा sपंचांगpe_adc *info = iio_priv(indio_dev);

	sपंचांगpe_adc_init_hw(info);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांगpe_adc_pm_ops, शून्य, sपंचांगpe_adc_resume);

अटल काष्ठा platक्रमm_driver sपंचांगpe_adc_driver = अणु
	.probe		= sपंचांगpe_adc_probe,
	.driver		= अणु
		.name	= "stmpe-adc",
		.pm	= &sपंचांगpe_adc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांगpe_adc_driver);

अटल स्थिर काष्ठा of_device_id sपंचांगpe_adc_ids[] = अणु
	अणु .compatible = "st,stmpe-adc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांगpe_adc_ids);

MODULE_AUTHOR("Stefan Agner <stefan.agner@toradex.com>");
MODULE_DESCRIPTION("STMPEXXX ADC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:stmpe-adc");
