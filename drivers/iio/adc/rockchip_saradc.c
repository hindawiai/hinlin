<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Rockchip Successive Approximation Register (SAR) A/D Converter
 * Copyright (C) 2014 ROCKCHIP, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/reset.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा SARADC_DATA			0x00

#घोषणा SARADC_STAS			0x04
#घोषणा SARADC_STAS_BUSY		BIT(0)

#घोषणा SARADC_CTRL			0x08
#घोषणा SARADC_CTRL_IRQ_STATUS		BIT(6)
#घोषणा SARADC_CTRL_IRQ_ENABLE		BIT(5)
#घोषणा SARADC_CTRL_POWER_CTRL		BIT(3)
#घोषणा SARADC_CTRL_CHN_MASK		0x7

#घोषणा SARADC_DLY_PU_SOC		0x0c
#घोषणा SARADC_DLY_PU_SOC_MASK		0x3f

#घोषणा SARADC_TIMEOUT			msecs_to_jअगरfies(100)
#घोषणा SARADC_MAX_CHANNELS		6

काष्ठा rockchip_saradc_data अणु
	स्थिर काष्ठा iio_chan_spec	*channels;
	पूर्णांक				num_channels;
	अचिन्हित दीर्घ			clk_rate;
पूर्ण;

काष्ठा rockchip_saradc अणु
	व्योम __iomem		*regs;
	काष्ठा clk		*pclk;
	काष्ठा clk		*clk;
	काष्ठा completion	completion;
	काष्ठा regulator	*vref;
	काष्ठा reset_control	*reset;
	स्थिर काष्ठा rockchip_saradc_data *data;
	u16			last_val;
	स्थिर काष्ठा iio_chan_spec *last_chan;
पूर्ण;

अटल व्योम rockchip_saradc_घातer_करोwn(काष्ठा rockchip_saradc *info)
अणु
	/* Clear irq & घातer करोwn adc */
	ग_लिखोl_relaxed(0, info->regs + SARADC_CTRL);
पूर्ण

अटल पूर्णांक rockchip_saradc_conversion(काष्ठा rockchip_saradc *info,
				   काष्ठा iio_chan_spec स्थिर *chan)
अणु
	reinit_completion(&info->completion);

	/* 8 घड़ी periods as delay between घातer up and start cmd */
	ग_लिखोl_relaxed(8, info->regs + SARADC_DLY_PU_SOC);

	info->last_chan = chan;

	/* Select the channel to be used and trigger conversion */
	ग_लिखोl(SARADC_CTRL_POWER_CTRL
			| (chan->channel & SARADC_CTRL_CHN_MASK)
			| SARADC_CTRL_IRQ_ENABLE,
		   info->regs + SARADC_CTRL);

	अगर (!रुको_क्रम_completion_समयout(&info->completion, SARADC_TIMEOUT))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_saradc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा rockchip_saradc *info = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);

		ret = rockchip_saradc_conversion(info, chan);
		अगर (ret) अणु
			rockchip_saradc_घातer_करोwn(info);
			mutex_unlock(&indio_dev->mlock);
			वापस ret;
		पूर्ण

		*val = info->last_val;
		mutex_unlock(&indio_dev->mlock);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(info->vref);
		अगर (ret < 0) अणु
			dev_err(&indio_dev->dev, "failed to get voltage\n");
			वापस ret;
		पूर्ण

		*val = ret / 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल irqवापस_t rockchip_saradc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rockchip_saradc *info = dev_id;

	/* Read value */
	info->last_val = पढ़ोl_relaxed(info->regs + SARADC_DATA);
	info->last_val &= GENMASK(info->last_chan->scan_type.realbits - 1, 0);

	rockchip_saradc_घातer_करोwn(info);

	complete(&info->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_info rockchip_saradc_iio_info = अणु
	.पढ़ो_raw = rockchip_saradc_पढ़ो_raw,
पूर्ण;

#घोषणा SARADC_CHANNEL(_index, _id, _res) अणु			\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = _index,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.datasheet_name = _id,					\
	.scan_index = _index,					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = _res,				\
		.storagebits = 16,				\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec rockchip_saradc_iio_channels[] = अणु
	SARADC_CHANNEL(0, "adc0", 10),
	SARADC_CHANNEL(1, "adc1", 10),
	SARADC_CHANNEL(2, "adc2", 10),
पूर्ण;

अटल स्थिर काष्ठा rockchip_saradc_data saradc_data = अणु
	.channels = rockchip_saradc_iio_channels,
	.num_channels = ARRAY_SIZE(rockchip_saradc_iio_channels),
	.clk_rate = 1000000,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec rockchip_rk3066_tsadc_iio_channels[] = अणु
	SARADC_CHANNEL(0, "adc0", 12),
	SARADC_CHANNEL(1, "adc1", 12),
पूर्ण;

अटल स्थिर काष्ठा rockchip_saradc_data rk3066_tsadc_data = अणु
	.channels = rockchip_rk3066_tsadc_iio_channels,
	.num_channels = ARRAY_SIZE(rockchip_rk3066_tsadc_iio_channels),
	.clk_rate = 50000,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec rockchip_rk3399_saradc_iio_channels[] = अणु
	SARADC_CHANNEL(0, "adc0", 10),
	SARADC_CHANNEL(1, "adc1", 10),
	SARADC_CHANNEL(2, "adc2", 10),
	SARADC_CHANNEL(3, "adc3", 10),
	SARADC_CHANNEL(4, "adc4", 10),
	SARADC_CHANNEL(5, "adc5", 10),
पूर्ण;

अटल स्थिर काष्ठा rockchip_saradc_data rk3399_saradc_data = अणु
	.channels = rockchip_rk3399_saradc_iio_channels,
	.num_channels = ARRAY_SIZE(rockchip_rk3399_saradc_iio_channels),
	.clk_rate = 1000000,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_saradc_match[] = अणु
	अणु
		.compatible = "rockchip,saradc",
		.data = &saradc_data,
	पूर्ण, अणु
		.compatible = "rockchip,rk3066-tsadc",
		.data = &rk3066_tsadc_data,
	पूर्ण, अणु
		.compatible = "rockchip,rk3399-saradc",
		.data = &rk3399_saradc_data,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_saradc_match);

/*
 * Reset SARADC Controller.
 */
अटल व्योम rockchip_saradc_reset_controller(काष्ठा reset_control *reset)
अणु
	reset_control_निश्चित(reset);
	usleep_range(10, 20);
	reset_control_deनिश्चित(reset);
पूर्ण

अटल व्योम rockchip_saradc_clk_disable(व्योम *data)
अणु
	काष्ठा rockchip_saradc *info = data;

	clk_disable_unprepare(info->clk);
पूर्ण

अटल व्योम rockchip_saradc_pclk_disable(व्योम *data)
अणु
	काष्ठा rockchip_saradc *info = data;

	clk_disable_unprepare(info->pclk);
पूर्ण

अटल व्योम rockchip_saradc_regulator_disable(व्योम *data)
अणु
	काष्ठा rockchip_saradc *info = data;

	regulator_disable(info->vref);
पूर्ण

अटल irqवापस_t rockchip_saradc_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *i_dev = pf->indio_dev;
	काष्ठा rockchip_saradc *info = iio_priv(i_dev);
	/*
	 * @values: each channel takes an u16 value
	 * @बारtamp: will be 8-byte aligned स्वतःmatically
	 */
	काष्ठा अणु
		u16 values[SARADC_MAX_CHANNELS];
		पूर्णांक64_t बारtamp;
	पूर्ण data;
	पूर्णांक ret;
	पूर्णांक i, j = 0;

	mutex_lock(&i_dev->mlock);

	क्रम_each_set_bit(i, i_dev->active_scan_mask, i_dev->masklength) अणु
		स्थिर काष्ठा iio_chan_spec *chan = &i_dev->channels[i];

		ret = rockchip_saradc_conversion(info, chan);
		अगर (ret) अणु
			rockchip_saradc_घातer_करोwn(info);
			जाओ out;
		पूर्ण

		data.values[j] = info->last_val;
		j++;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(i_dev, &data, iio_get_समय_ns(i_dev));
out:
	mutex_unlock(&i_dev->mlock);

	iio_trigger_notअगरy_करोne(i_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rockchip_saradc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_saradc *info = शून्य;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा iio_dev *indio_dev = शून्य;
	काष्ठा resource	*mem;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;
	पूर्णांक irq;

	अगर (!np)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*info));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण
	info = iio_priv(indio_dev);

	match = of_match_device(rockchip_saradc_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "failed to match device\n");
		वापस -ENODEV;
	पूर्ण

	info->data = match->data;

	/* Sanity check क्रम possible later IP variants with more channels */
	अगर (info->data->num_channels > SARADC_MAX_CHANNELS) अणु
		dev_err(&pdev->dev, "max channels exceeded");
		वापस -EINVAL;
	पूर्ण

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	info->regs = devm_ioremap_resource(&pdev->dev, mem);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);

	/*
	 * The reset should be an optional property, as it should work
	 * with old devicetrees as well
	 */
	info->reset = devm_reset_control_get_exclusive(&pdev->dev,
						       "saradc-apb");
	अगर (IS_ERR(info->reset)) अणु
		ret = PTR_ERR(info->reset);
		अगर (ret != -ENOENT)
			वापस ret;

		dev_dbg(&pdev->dev, "no reset control found\n");
		info->reset = शून्य;
	पूर्ण

	init_completion(&info->completion);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, rockchip_saradc_isr,
			       0, dev_name(&pdev->dev), info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed requesting irq %d\n", irq);
		वापस ret;
	पूर्ण

	info->pclk = devm_clk_get(&pdev->dev, "apb_pclk");
	अगर (IS_ERR(info->pclk)) अणु
		dev_err(&pdev->dev, "failed to get pclk\n");
		वापस PTR_ERR(info->pclk);
	पूर्ण

	info->clk = devm_clk_get(&pdev->dev, "saradc");
	अगर (IS_ERR(info->clk)) अणु
		dev_err(&pdev->dev, "failed to get adc clock\n");
		वापस PTR_ERR(info->clk);
	पूर्ण

	info->vref = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(info->vref)) अणु
		dev_err(&pdev->dev, "failed to get regulator, %ld\n",
			PTR_ERR(info->vref));
		वापस PTR_ERR(info->vref);
	पूर्ण

	अगर (info->reset)
		rockchip_saradc_reset_controller(info->reset);

	/*
	 * Use a शेष value क्रम the converter घड़ी.
	 * This may become user-configurable in the future.
	 */
	ret = clk_set_rate(info->clk, info->data->clk_rate);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to set adc clk rate, %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_enable(info->vref);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable vref regulator\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(&pdev->dev,
				       rockchip_saradc_regulator_disable, info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register devm action, %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(info->pclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable pclk\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(&pdev->dev,
				       rockchip_saradc_pclk_disable, info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register devm action, %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(info->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable converter clock\n");
		वापस ret;
	पूर्ण
	ret = devm_add_action_or_reset(&pdev->dev,
				       rockchip_saradc_clk_disable, info);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register devm action, %d\n",
			ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &rockchip_saradc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	indio_dev->channels = info->data->channels;
	indio_dev->num_channels = info->data->num_channels;
	ret = devm_iio_triggered_buffer_setup(&indio_dev->dev, indio_dev, शून्य,
					      rockchip_saradc_trigger_handler,
					      शून्य);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक rockchip_saradc_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा rockchip_saradc *info = iio_priv(indio_dev);

	clk_disable_unprepare(info->clk);
	clk_disable_unprepare(info->pclk);
	regulator_disable(info->vref);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_saradc_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा rockchip_saradc *info = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(info->vref);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(info->pclk);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(info->clk);
	अगर (ret)
		clk_disable_unprepare(info->pclk);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(rockchip_saradc_pm_ops,
			 rockchip_saradc_suspend, rockchip_saradc_resume);

अटल काष्ठा platक्रमm_driver rockchip_saradc_driver = अणु
	.probe		= rockchip_saradc_probe,
	.driver		= अणु
		.name	= "rockchip-saradc",
		.of_match_table = rockchip_saradc_match,
		.pm	= &rockchip_saradc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_saradc_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_DESCRIPTION("Rockchip SARADC driver");
MODULE_LICENSE("GPL v2");
