<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ADC driver क्रम sunxi platक्रमms' (A10, A13 and A31) GPADC
 *
 * Copyright (c) 2016 Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 *
 * The Allwinner SoCs all have an ADC that can also act as a touchscreen
 * controller and a thermal sensor.
 * The thermal sensor works only when the ADC acts as a touchscreen controller
 * and is configured to throw an पूर्णांकerrupt every fixed periods of समय (let say
 * every X seconds).
 * One would be tempted to disable the IP on the hardware side rather than
 * disabling पूर्णांकerrupts to save some घातer but that resets the पूर्णांकernal घड़ी of
 * the IP, resulting in having to रुको X seconds every समय we want to पढ़ो the
 * value of the thermal sensor.
 * This is also the reason of using स्वतःsuspend in pm_runसमय. If there was no
 * स्वतःsuspend, the thermal sensor would need X seconds after every
 * pm_runसमय_get_sync to get a value from the ADC. The स्वतःsuspend allows the
 * thermal sensor to be requested again in a certain समय span beक्रमe it माला_लो
 * shutकरोwn क्रम not being used.
 */

#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/machine.h>
#समावेश <linux/mfd/sun4i-gpadc.h>

अटल अचिन्हित पूर्णांक sun4i_gpadc_chan_select(अचिन्हित पूर्णांक chan)
अणु
	वापस SUN4I_GPADC_CTRL1_ADC_CHAN_SELECT(chan);
पूर्ण

अटल अचिन्हित पूर्णांक sun6i_gpadc_chan_select(अचिन्हित पूर्णांक chan)
अणु
	वापस SUN6I_GPADC_CTRL1_ADC_CHAN_SELECT(chan);
पूर्ण

काष्ठा gpadc_data अणु
	पूर्णांक		temp_offset;
	पूर्णांक		temp_scale;
	अचिन्हित पूर्णांक	tp_mode_en;
	अचिन्हित पूर्णांक	tp_adc_select;
	अचिन्हित पूर्णांक	(*adc_chan_select)(अचिन्हित पूर्णांक chan);
	अचिन्हित पूर्णांक	adc_chan_mask;
पूर्ण;

अटल स्थिर काष्ठा gpadc_data sun4i_gpadc_data = अणु
	.temp_offset = -1932,
	.temp_scale = 133,
	.tp_mode_en = SUN4I_GPADC_CTRL1_TP_MODE_EN,
	.tp_adc_select = SUN4I_GPADC_CTRL1_TP_ADC_SELECT,
	.adc_chan_select = &sun4i_gpadc_chan_select,
	.adc_chan_mask = SUN4I_GPADC_CTRL1_ADC_CHAN_MASK,
पूर्ण;

अटल स्थिर काष्ठा gpadc_data sun5i_gpadc_data = अणु
	.temp_offset = -1447,
	.temp_scale = 100,
	.tp_mode_en = SUN4I_GPADC_CTRL1_TP_MODE_EN,
	.tp_adc_select = SUN4I_GPADC_CTRL1_TP_ADC_SELECT,
	.adc_chan_select = &sun4i_gpadc_chan_select,
	.adc_chan_mask = SUN4I_GPADC_CTRL1_ADC_CHAN_MASK,
पूर्ण;

अटल स्थिर काष्ठा gpadc_data sun6i_gpadc_data = अणु
	.temp_offset = -1623,
	.temp_scale = 167,
	.tp_mode_en = SUN6I_GPADC_CTRL1_TP_MODE_EN,
	.tp_adc_select = SUN6I_GPADC_CTRL1_TP_ADC_SELECT,
	.adc_chan_select = &sun6i_gpadc_chan_select,
	.adc_chan_mask = SUN6I_GPADC_CTRL1_ADC_CHAN_MASK,
पूर्ण;

अटल स्थिर काष्ठा gpadc_data sun8i_a33_gpadc_data = अणु
	.temp_offset = -1662,
	.temp_scale = 162,
	.tp_mode_en = SUN8I_GPADC_CTRL1_CHOP_TEMP_EN,
पूर्ण;

काष्ठा sun4i_gpadc_iio अणु
	काष्ठा iio_dev			*indio_dev;
	काष्ठा completion		completion;
	पूर्णांक				temp_data;
	u32				adc_data;
	काष्ठा regmap			*regmap;
	अचिन्हित पूर्णांक			fअगरo_data_irq;
	atomic_t			ignore_fअगरo_data_irq;
	अचिन्हित पूर्णांक			temp_data_irq;
	atomic_t			ignore_temp_data_irq;
	स्थिर काष्ठा gpadc_data		*data;
	bool				no_irq;
	/* prevents concurrent पढ़ोs of temperature and ADC */
	काष्ठा mutex			mutex;
	काष्ठा thermal_zone_device	*tzd;
	काष्ठा device			*sensor_device;
पूर्ण;

#घोषणा SUN4I_GPADC_ADC_CHANNEL(_channel, _name) अणु		\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = _channel,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.datasheet_name = _name,				\
पूर्ण

अटल काष्ठा iio_map sun4i_gpadc_hwmon_maps[] = अणु
	अणु
		.adc_channel_label = "temp_adc",
		.consumer_dev_name = "iio_hwmon.0",
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sun4i_gpadc_channels[] = अणु
	SUN4I_GPADC_ADC_CHANNEL(0, "adc_chan0"),
	SUN4I_GPADC_ADC_CHANNEL(1, "adc_chan1"),
	SUN4I_GPADC_ADC_CHANNEL(2, "adc_chan2"),
	SUN4I_GPADC_ADC_CHANNEL(3, "adc_chan3"),
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "temp_adc",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sun4i_gpadc_channels_no_temp[] = अणु
	SUN4I_GPADC_ADC_CHANNEL(0, "adc_chan0"),
	SUN4I_GPADC_ADC_CHANNEL(1, "adc_chan1"),
	SUN4I_GPADC_ADC_CHANNEL(2, "adc_chan2"),
	SUN4I_GPADC_ADC_CHANNEL(3, "adc_chan3"),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sun8i_a33_gpadc_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "temp_adc",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_gpadc_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.fast_io = true,
पूर्ण;

अटल पूर्णांक sun4i_prepare_क्रम_irq(काष्ठा iio_dev *indio_dev, पूर्णांक channel,
				 अचिन्हित पूर्णांक irq)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 reg;

	pm_runसमय_get_sync(indio_dev->dev.parent);

	reinit_completion(&info->completion);

	ret = regmap_ग_लिखो(info->regmap, SUN4I_GPADC_INT_FIFOC,
			   SUN4I_GPADC_INT_FIFOC_TP_FIFO_TRIG_LEVEL(1) |
			   SUN4I_GPADC_INT_FIFOC_TP_FIFO_FLUSH);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(info->regmap, SUN4I_GPADC_CTRL1, &reg);
	अगर (ret)
		वापस ret;

	अगर (irq == info->fअगरo_data_irq) अणु
		ret = regmap_ग_लिखो(info->regmap, SUN4I_GPADC_CTRL1,
				   info->data->tp_mode_en |
				   info->data->tp_adc_select |
				   info->data->adc_chan_select(channel));
		/*
		 * When the IP changes channel, it needs a bit of समय to get
		 * correct values.
		 */
		अगर ((reg & info->data->adc_chan_mask) !=
			 info->data->adc_chan_select(channel))
			mdelay(10);

	पूर्ण अन्यथा अणु
		/*
		 * The temperature sensor वापसs valid data only when the ADC
		 * operates in touchscreen mode.
		 */
		ret = regmap_ग_लिखो(info->regmap, SUN4I_GPADC_CTRL1,
				   info->data->tp_mode_en);
	पूर्ण

	अगर (ret)
		वापस ret;

	/*
	 * When the IP changes mode between ADC or touchscreen, it
	 * needs a bit of समय to get correct values.
	 */
	अगर ((reg & info->data->tp_adc_select) != info->data->tp_adc_select)
		mdelay(100);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_gpadc_पढ़ो(काष्ठा iio_dev *indio_dev, पूर्णांक channel, पूर्णांक *val,
			    अचिन्हित पूर्णांक irq)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&info->mutex);

	ret = sun4i_prepare_क्रम_irq(indio_dev, channel, irq);
	अगर (ret)
		जाओ err;

	enable_irq(irq);

	/*
	 * The temperature sensor throws an पूर्णांकerruption periodically (currently
	 * set at periods of ~0.6s in sun4i_gpadc_runसमय_resume). A 1s delay
	 * makes sure an पूर्णांकerruption occurs in normal conditions. If it करोesn't
	 * occur, then there is a समयout.
	 */
	अगर (!रुको_क्रम_completion_समयout(&info->completion,
					 msecs_to_jअगरfies(1000))) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	अगर (irq == info->fअगरo_data_irq)
		*val = info->adc_data;
	अन्यथा
		*val = info->temp_data;

	ret = 0;
	pm_runसमय_mark_last_busy(indio_dev->dev.parent);

err:
	pm_runसमय_put_स्वतःsuspend(indio_dev->dev.parent);
	disable_irq(irq);
	mutex_unlock(&info->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_gpadc_adc_पढ़ो(काष्ठा iio_dev *indio_dev, पूर्णांक channel,
				पूर्णांक *val)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);

	वापस sun4i_gpadc_पढ़ो(indio_dev, channel, val, info->fअगरo_data_irq);
पूर्ण

अटल पूर्णांक sun4i_gpadc_temp_पढ़ो(काष्ठा iio_dev *indio_dev, पूर्णांक *val)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);

	अगर (info->no_irq) अणु
		pm_runसमय_get_sync(indio_dev->dev.parent);

		regmap_पढ़ो(info->regmap, SUN4I_GPADC_TEMP_DATA, val);

		pm_runसमय_mark_last_busy(indio_dev->dev.parent);
		pm_runसमय_put_स्वतःsuspend(indio_dev->dev.parent);

		वापस 0;
	पूर्ण

	वापस sun4i_gpadc_पढ़ो(indio_dev, 0, val, info->temp_data_irq);
पूर्ण

अटल पूर्णांक sun4i_gpadc_temp_offset(काष्ठा iio_dev *indio_dev, पूर्णांक *val)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);

	*val = info->data->temp_offset;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_gpadc_temp_scale(काष्ठा iio_dev *indio_dev, पूर्णांक *val)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);

	*val = info->data->temp_scale;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_gpadc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
				पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OFFSET:
		ret = sun4i_gpadc_temp_offset(indio_dev, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type == IIO_VOLTAGE)
			ret = sun4i_gpadc_adc_पढ़ो(indio_dev, chan->channel,
						   val);
		अन्यथा
			ret = sun4i_gpadc_temp_पढ़ो(indio_dev, val);

		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_VOLTAGE) अणु
			/* 3000mV / 4096 * raw */
			*val = 0;
			*val2 = 732421875;
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		पूर्ण

		ret = sun4i_gpadc_temp_scale(indio_dev, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info sun4i_gpadc_iio_info = अणु
	.पढ़ो_raw = sun4i_gpadc_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t sun4i_gpadc_temp_data_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_gpadc_iio *info = dev_id;

	अगर (atomic_पढ़ो(&info->ignore_temp_data_irq))
		जाओ out;

	अगर (!regmap_पढ़ो(info->regmap, SUN4I_GPADC_TEMP_DATA, &info->temp_data))
		complete(&info->completion);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sun4i_gpadc_fअगरo_data_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun4i_gpadc_iio *info = dev_id;

	अगर (atomic_पढ़ो(&info->ignore_fअगरo_data_irq))
		जाओ out;

	अगर (!regmap_पढ़ो(info->regmap, SUN4I_GPADC_DATA, &info->adc_data))
		complete(&info->completion);

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sun4i_gpadc_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(dev_get_drvdata(dev));

	/* Disable the ADC on IP */
	regmap_ग_लिखो(info->regmap, SUN4I_GPADC_CTRL1, 0);
	/* Disable temperature sensor on IP */
	regmap_ग_लिखो(info->regmap, SUN4I_GPADC_TPR, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_gpadc_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(dev_get_drvdata(dev));

	/* clkin = 6MHz */
	regmap_ग_लिखो(info->regmap, SUN4I_GPADC_CTRL0,
		     SUN4I_GPADC_CTRL0_ADC_CLK_DIVIDER(2) |
		     SUN4I_GPADC_CTRL0_FS_DIV(7) |
		     SUN4I_GPADC_CTRL0_T_ACQ(63));
	regmap_ग_लिखो(info->regmap, SUN4I_GPADC_CTRL1, info->data->tp_mode_en);
	regmap_ग_लिखो(info->regmap, SUN4I_GPADC_CTRL3,
		     SUN4I_GPADC_CTRL3_FILTER_EN |
		     SUN4I_GPADC_CTRL3_FILTER_TYPE(1));
	/* period = SUN4I_GPADC_TPR_TEMP_PERIOD * 256 * 16 / clkin; ~0.6s */
	regmap_ग_लिखो(info->regmap, SUN4I_GPADC_TPR,
		     SUN4I_GPADC_TPR_TEMP_ENABLE |
		     SUN4I_GPADC_TPR_TEMP_PERIOD(800));

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_gpadc_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा sun4i_gpadc_iio *info = data;
	पूर्णांक val, scale, offset;

	अगर (sun4i_gpadc_temp_पढ़ो(info->indio_dev, &val))
		वापस -ETIMEDOUT;

	sun4i_gpadc_temp_scale(info->indio_dev, &scale);
	sun4i_gpadc_temp_offset(info->indio_dev, &offset);

	*temp = (val + offset) * scale;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops sun4i_ts_tz_ops = अणु
	.get_temp = &sun4i_gpadc_get_temp,
पूर्ण;

अटल स्थिर काष्ठा dev_pm_ops sun4i_gpadc_pm_ops = अणु
	.runसमय_suspend = &sun4i_gpadc_runसमय_suspend,
	.runसमय_resume = &sun4i_gpadc_runसमय_resume,
पूर्ण;

अटल पूर्णांक sun4i_irq_init(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
			  irq_handler_t handler, स्थिर अक्षर *devname,
			  अचिन्हित पूर्णांक *irq, atomic_t *atomic)
अणु
	पूर्णांक ret;
	काष्ठा sun4i_gpadc_dev *mfd_dev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sun4i_gpadc_iio *info = iio_priv(dev_get_drvdata(&pdev->dev));

	/*
	 * Once the पूर्णांकerrupt is activated, the IP continuously perक्रमms
	 * conversions thus throws पूर्णांकerrupts. The पूर्णांकerrupt is activated right
	 * after being requested but we want to control when these पूर्णांकerrupts
	 * occur thus we disable it right after being requested. However, an
	 * पूर्णांकerrupt might occur between these two inकाष्ठाions and we have to
	 * make sure that करोes not happen, by using atomic flags. We set the
	 * flag beक्रमe requesting the पूर्णांकerrupt and unset it right after
	 * disabling the पूर्णांकerrupt. When an पूर्णांकerrupt occurs between these two
	 * inकाष्ठाions, पढ़ोing the atomic flag will tell us to ignore the
	 * पूर्णांकerrupt.
	 */
	atomic_set(atomic, 1);

	ret = platक्रमm_get_irq_byname(pdev, name);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_irq_get_virq(mfd_dev->regmap_irqc, ret);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get virq for irq %s\n", name);
		वापस ret;
	पूर्ण

	*irq = ret;
	ret = devm_request_any_context_irq(&pdev->dev, *irq, handler,
					   IRQF_NO_AUTOEN,
					   devname, info);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not request %s interrupt: %d\n",
			name, ret);
		वापस ret;
	पूर्ण

	atomic_set(atomic, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_gpadc_of_id[] = अणु
	अणु
		.compatible = "allwinner,sun8i-a33-ths",
		.data = &sun8i_a33_gpadc_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक sun4i_gpadc_probe_dt(काष्ठा platक्रमm_device *pdev,
				काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);
	व्योम __iomem *base;
	पूर्णांक ret;

	info->data = of_device_get_match_data(&pdev->dev);
	अगर (!info->data)
		वापस -ENODEV;

	info->no_irq = true;
	indio_dev->num_channels = ARRAY_SIZE(sun8i_a33_gpadc_channels);
	indio_dev->channels = sun8i_a33_gpadc_channels;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	info->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					     &sun4i_gpadc_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		ret = PTR_ERR(info->regmap);
		dev_err(&pdev->dev, "failed to init regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_THERMAL_OF))
		info->sensor_device = &pdev->dev;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_gpadc_probe_mfd(काष्ठा platक्रमm_device *pdev,
				 काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);
	काष्ठा sun4i_gpadc_dev *sun4i_gpadc_dev =
		dev_get_drvdata(pdev->dev.parent);
	पूर्णांक ret;

	info->no_irq = false;
	info->regmap = sun4i_gpadc_dev->regmap;

	indio_dev->num_channels = ARRAY_SIZE(sun4i_gpadc_channels);
	indio_dev->channels = sun4i_gpadc_channels;

	info->data = (काष्ठा gpadc_data *)platक्रमm_get_device_id(pdev)->driver_data;

	/*
	 * Since the controller needs to be in touchscreen mode क्रम its thermal
	 * sensor to operate properly, and that चयनing between the two modes
	 * needs a delay, always रेजिस्टरing in the thermal framework will
	 * signअगरicantly slow करोwn the conversion rate of the ADCs.
	 *
	 * Thereक्रमe, instead of depending on THERMAL_OF in Kconfig, we only
	 * रेजिस्टर the sensor अगर that option is enabled, eventually leaving
	 * that choice to the user.
	 */

	अगर (IS_ENABLED(CONFIG_THERMAL_OF)) अणु
		/*
		 * This driver is a child of an MFD which has a node in the DT
		 * but not its children, because of DT backward compatibility
		 * क्रम A10, A13 and A31 SoCs. Thereक्रमe, the resulting devices
		 * of this driver करो not have an of_node variable.
		 * However, its parent (the MFD driver) has an of_node variable
		 * and since devm_thermal_zone_of_sensor_रेजिस्टर uses its first
		 * argument to match the phandle defined in the node of the
		 * thermal driver with the of_node of the device passed as first
		 * argument and the third argument to call ops from
		 * thermal_zone_of_device_ops, the solution is to use the parent
		 * device as first argument to match the phandle with its
		 * of_node, and the device from this driver as third argument to
		 * वापस the temperature.
		 */
		info->sensor_device = pdev->dev.parent;
	पूर्ण अन्यथा अणु
		indio_dev->num_channels =
			ARRAY_SIZE(sun4i_gpadc_channels_no_temp);
		indio_dev->channels = sun4i_gpadc_channels_no_temp;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_THERMAL_OF)) अणु
		ret = sun4i_irq_init(pdev, "TEMP_DATA_PENDING",
				     sun4i_gpadc_temp_data_irq_handler,
				     "temp_data", &info->temp_data_irq,
				     &info->ignore_temp_data_irq);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = sun4i_irq_init(pdev, "FIFO_DATA_PENDING",
			     sun4i_gpadc_fअगरo_data_irq_handler, "fifo_data",
			     &info->fअगरo_data_irq, &info->ignore_fअगरo_data_irq);
	अगर (ret < 0)
		वापस ret;

	अगर (IS_ENABLED(CONFIG_THERMAL_OF)) अणु
		ret = iio_map_array_रेजिस्टर(indio_dev, sun4i_gpadc_hwmon_maps);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev,
				"failed to register iio map array\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_gpadc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_gpadc_iio *info;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*info));
	अगर (!indio_dev)
		वापस -ENOMEM;

	info = iio_priv(indio_dev);
	platक्रमm_set_drvdata(pdev, indio_dev);

	mutex_init(&info->mutex);
	info->indio_dev = indio_dev;
	init_completion(&info->completion);
	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &sun4i_gpadc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (pdev->dev.of_node)
		ret = sun4i_gpadc_probe_dt(pdev, indio_dev);
	अन्यथा
		ret = sun4i_gpadc_probe_mfd(pdev, indio_dev);

	अगर (ret)
		वापस ret;

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev,
					 SUN4I_GPADC_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	अगर (IS_ENABLED(CONFIG_THERMAL_OF)) अणु
		info->tzd = thermal_zone_of_sensor_रेजिस्टर(info->sensor_device,
							    0, info,
							    &sun4i_ts_tz_ops);
		/*
		 * Do not fail driver probing when failing to रेजिस्टर in
		 * thermal because no thermal DT node is found.
		 */
		अगर (IS_ERR(info->tzd) && PTR_ERR(info->tzd) != -ENODEV) अणु
			dev_err(&pdev->dev,
				"could not register thermal sensor: %ld\n",
				PTR_ERR(info->tzd));
			वापस PTR_ERR(info->tzd);
		पूर्ण
	पूर्ण

	ret = devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not register the device\n");
		जाओ err_map;
	पूर्ण

	वापस 0;

err_map:
	अगर (!info->no_irq && IS_ENABLED(CONFIG_THERMAL_OF))
		iio_map_array_unरेजिस्टर(indio_dev);

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_gpadc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा sun4i_gpadc_iio *info = iio_priv(indio_dev);

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	अगर (!IS_ENABLED(CONFIG_THERMAL_OF))
		वापस 0;

	thermal_zone_of_sensor_unरेजिस्टर(info->sensor_device, info->tzd);

	अगर (!info->no_irq)
		iio_map_array_unरेजिस्टर(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id sun4i_gpadc_id[] = अणु
	अणु "sun4i-a10-gpadc-iio", (kernel_uदीर्घ_t)&sun4i_gpadc_data पूर्ण,
	अणु "sun5i-a13-gpadc-iio", (kernel_uदीर्घ_t)&sun5i_gpadc_data पूर्ण,
	अणु "sun6i-a31-gpadc-iio", (kernel_uदीर्घ_t)&sun6i_gpadc_data पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, sun4i_gpadc_id);

अटल काष्ठा platक्रमm_driver sun4i_gpadc_driver = अणु
	.driver = अणु
		.name = "sun4i-gpadc-iio",
		.of_match_table = sun4i_gpadc_of_id,
		.pm = &sun4i_gpadc_pm_ops,
	पूर्ण,
	.id_table = sun4i_gpadc_id,
	.probe = sun4i_gpadc_probe,
	.हटाओ = sun4i_gpadc_हटाओ,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_gpadc_of_id);

module_platक्रमm_driver(sun4i_gpadc_driver);

MODULE_DESCRIPTION("ADC driver for sunxi platforms");
MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_LICENSE("GPL v2");
