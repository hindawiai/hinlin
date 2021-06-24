<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Spपढ़ोtrum Communications Inc.

#समावेश <linux/hwspinlock.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* PMIC global रेजिस्टरs definition */
#घोषणा SC27XX_MODULE_EN		0xc08
#घोषणा SC27XX_MODULE_ADC_EN		BIT(5)
#घोषणा SC27XX_ARM_CLK_EN		0xc10
#घोषणा SC27XX_CLK_ADC_EN		BIT(5)
#घोषणा SC27XX_CLK_ADC_CLK_EN		BIT(6)

/* ADC controller रेजिस्टरs definition */
#घोषणा SC27XX_ADC_CTL			0x0
#घोषणा SC27XX_ADC_CH_CFG		0x4
#घोषणा SC27XX_ADC_DATA			0x4c
#घोषणा SC27XX_ADC_INT_EN		0x50
#घोषणा SC27XX_ADC_INT_CLR		0x54
#घोषणा SC27XX_ADC_INT_STS		0x58
#घोषणा SC27XX_ADC_INT_RAW		0x5c

/* Bits and mask definition क्रम SC27XX_ADC_CTL रेजिस्टर */
#घोषणा SC27XX_ADC_EN			BIT(0)
#घोषणा SC27XX_ADC_CHN_RUN		BIT(1)
#घोषणा SC27XX_ADC_12BIT_MODE		BIT(2)
#घोषणा SC27XX_ADC_RUN_NUM_MASK		GENMASK(7, 4)
#घोषणा SC27XX_ADC_RUN_NUM_SHIFT	4

/* Bits and mask definition क्रम SC27XX_ADC_CH_CFG रेजिस्टर */
#घोषणा SC27XX_ADC_CHN_ID_MASK		GENMASK(4, 0)
#घोषणा SC27XX_ADC_SCALE_MASK		GENMASK(10, 8)
#घोषणा SC27XX_ADC_SCALE_SHIFT		8

/* Bits definitions क्रम SC27XX_ADC_INT_EN रेजिस्टरs */
#घोषणा SC27XX_ADC_IRQ_EN		BIT(0)

/* Bits definitions क्रम SC27XX_ADC_INT_CLR रेजिस्टरs */
#घोषणा SC27XX_ADC_IRQ_CLR		BIT(0)

/* Bits definitions क्रम SC27XX_ADC_INT_RAW रेजिस्टरs */
#घोषणा SC27XX_ADC_IRQ_RAW		BIT(0)

/* Mask definition क्रम SC27XX_ADC_DATA रेजिस्टर */
#घोषणा SC27XX_ADC_DATA_MASK		GENMASK(11, 0)

/* Timeout (ms) क्रम the trylock of hardware spinlocks */
#घोषणा SC27XX_ADC_HWLOCK_TIMEOUT	5000

/* Timeout (us) क्रम ADC data conversion according to ADC datasheet */
#घोषणा SC27XX_ADC_RDY_TIMEOUT		1000000
#घोषणा SC27XX_ADC_POLL_RAW_STATUS	500

/* Maximum ADC channel number */
#घोषणा SC27XX_ADC_CHANNEL_MAX		32

/* ADC voltage ratio definition */
#घोषणा SC27XX_VOLT_RATIO(n, d)		\
	(((n) << SC27XX_RATIO_NUMERATOR_OFFSET) | (d))
#घोषणा SC27XX_RATIO_NUMERATOR_OFFSET	16
#घोषणा SC27XX_RATIO_DENOMINATOR_MASK	GENMASK(15, 0)

काष्ठा sc27xx_adc_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	/*
	 * One hardware spinlock to synchronize between the multiple
	 * subप्रणालीs which will access the unique ADC controller.
	 */
	काष्ठा hwspinlock *hwlock;
	पूर्णांक channel_scale[SC27XX_ADC_CHANNEL_MAX];
	u32 base;
	पूर्णांक irq;
पूर्ण;

काष्ठा sc27xx_adc_linear_graph अणु
	पूर्णांक volt0;
	पूर्णांक adc0;
	पूर्णांक volt1;
	पूर्णांक adc1;
पूर्ण;

/*
 * According to the datasheet, we can convert one ADC value to one voltage value
 * through 2 poपूर्णांकs in the linear graph. If the voltage is less than 1.2v, we
 * should use the small-scale graph, and अगर more than 1.2v, we should use the
 * big-scale graph.
 */
अटल काष्ठा sc27xx_adc_linear_graph big_scale_graph = अणु
	4200, 3310,
	3600, 2832,
पूर्ण;

अटल काष्ठा sc27xx_adc_linear_graph small_scale_graph = अणु
	1000, 3413,
	100, 341,
पूर्ण;

अटल स्थिर काष्ठा sc27xx_adc_linear_graph big_scale_graph_calib = अणु
	4200, 856,
	3600, 733,
पूर्ण;

अटल स्थिर काष्ठा sc27xx_adc_linear_graph small_scale_graph_calib = अणु
	1000, 833,
	100, 80,
पूर्ण;

अटल पूर्णांक sc27xx_adc_get_calib_data(u32 calib_data, पूर्णांक calib_adc)
अणु
	वापस ((calib_data & 0xff) + calib_adc - 128) * 4;
पूर्ण

अटल पूर्णांक sc27xx_adc_scale_calibration(काष्ठा sc27xx_adc_data *data,
					bool big_scale)
अणु
	स्थिर काष्ठा sc27xx_adc_linear_graph *calib_graph;
	काष्ठा sc27xx_adc_linear_graph *graph;
	काष्ठा nvmem_cell *cell;
	स्थिर अक्षर *cell_name;
	u32 calib_data = 0;
	व्योम *buf;
	माप_प्रकार len;

	अगर (big_scale) अणु
		calib_graph = &big_scale_graph_calib;
		graph = &big_scale_graph;
		cell_name = "big_scale_calib";
	पूर्ण अन्यथा अणु
		calib_graph = &small_scale_graph_calib;
		graph = &small_scale_graph;
		cell_name = "small_scale_calib";
	पूर्ण

	cell = nvmem_cell_get(data->dev, cell_name);
	अगर (IS_ERR(cell))
		वापस PTR_ERR(cell);

	buf = nvmem_cell_पढ़ो(cell, &len);
	nvmem_cell_put(cell);

	अगर (IS_ERR(buf))
		वापस PTR_ERR(buf);

	स_नकल(&calib_data, buf, min(len, माप(u32)));

	/* Only need to calibrate the adc values in the linear graph. */
	graph->adc0 = sc27xx_adc_get_calib_data(calib_data, calib_graph->adc0);
	graph->adc1 = sc27xx_adc_get_calib_data(calib_data >> 8,
						calib_graph->adc1);

	kमुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_adc_get_ratio(पूर्णांक channel, पूर्णांक scale)
अणु
	चयन (channel) अणु
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
		वापस scale ? SC27XX_VOLT_RATIO(400, 1025) :
			SC27XX_VOLT_RATIO(1, 1);
	हाल 5:
		वापस SC27XX_VOLT_RATIO(7, 29);
	हाल 6:
		वापस SC27XX_VOLT_RATIO(375, 9000);
	हाल 7:
	हाल 8:
		वापस scale ? SC27XX_VOLT_RATIO(100, 125) :
			SC27XX_VOLT_RATIO(1, 1);
	हाल 19:
		वापस SC27XX_VOLT_RATIO(1, 3);
	शेष:
		वापस SC27XX_VOLT_RATIO(1, 1);
	पूर्ण
	वापस SC27XX_VOLT_RATIO(1, 1);
पूर्ण

अटल पूर्णांक sc27xx_adc_पढ़ो(काष्ठा sc27xx_adc_data *data, पूर्णांक channel,
			   पूर्णांक scale, पूर्णांक *val)
अणु
	पूर्णांक ret;
	u32 पंचांगp, value, status;

	ret = hwspin_lock_समयout_raw(data->hwlock, SC27XX_ADC_HWLOCK_TIMEOUT);
	अगर (ret) अणु
		dev_err(data->dev, "timeout to get the hwspinlock\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
				 SC27XX_ADC_EN, SC27XX_ADC_EN);
	अगर (ret)
		जाओ unlock_adc;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_INT_CLR,
				 SC27XX_ADC_IRQ_CLR, SC27XX_ADC_IRQ_CLR);
	अगर (ret)
		जाओ disable_adc;

	/* Configure the channel id and scale */
	पंचांगp = (scale << SC27XX_ADC_SCALE_SHIFT) & SC27XX_ADC_SCALE_MASK;
	पंचांगp |= channel & SC27XX_ADC_CHN_ID_MASK;
	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CH_CFG,
				 SC27XX_ADC_CHN_ID_MASK | SC27XX_ADC_SCALE_MASK,
				 पंचांगp);
	अगर (ret)
		जाओ disable_adc;

	/* Select 12bit conversion mode, and only sample 1 समय */
	पंचांगp = SC27XX_ADC_12BIT_MODE;
	पंचांगp |= (0 << SC27XX_ADC_RUN_NUM_SHIFT) & SC27XX_ADC_RUN_NUM_MASK;
	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
				 SC27XX_ADC_RUN_NUM_MASK | SC27XX_ADC_12BIT_MODE,
				 पंचांगp);
	अगर (ret)
		जाओ disable_adc;

	ret = regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
				 SC27XX_ADC_CHN_RUN, SC27XX_ADC_CHN_RUN);
	अगर (ret)
		जाओ disable_adc;

	ret = regmap_पढ़ो_poll_समयout(data->regmap,
				       data->base + SC27XX_ADC_INT_RAW,
				       status, (status & SC27XX_ADC_IRQ_RAW),
				       SC27XX_ADC_POLL_RAW_STATUS,
				       SC27XX_ADC_RDY_TIMEOUT);
	अगर (ret) अणु
		dev_err(data->dev, "read adc timeout, status = 0x%x\n", status);
		जाओ disable_adc;
	पूर्ण

	ret = regmap_पढ़ो(data->regmap, data->base + SC27XX_ADC_DATA, &value);
	अगर (ret)
		जाओ disable_adc;

	value &= SC27XX_ADC_DATA_MASK;

disable_adc:
	regmap_update_bits(data->regmap, data->base + SC27XX_ADC_CTL,
			   SC27XX_ADC_EN, 0);
unlock_adc:
	hwspin_unlock_raw(data->hwlock);

	अगर (!ret)
		*val = value;

	वापस ret;
पूर्ण

अटल व्योम sc27xx_adc_volt_ratio(काष्ठा sc27xx_adc_data *data,
				  पूर्णांक channel, पूर्णांक scale,
				  u32 *भाग_numerator, u32 *भाग_denominator)
अणु
	u32 ratio = sc27xx_adc_get_ratio(channel, scale);

	*भाग_numerator = ratio >> SC27XX_RATIO_NUMERATOR_OFFSET;
	*भाग_denominator = ratio & SC27XX_RATIO_DENOMINATOR_MASK;
पूर्ण

अटल पूर्णांक sc27xx_adc_to_volt(काष्ठा sc27xx_adc_linear_graph *graph,
			      पूर्णांक raw_adc)
अणु
	पूर्णांक पंचांगp;

	पंचांगp = (graph->volt0 - graph->volt1) * (raw_adc - graph->adc1);
	पंचांगp /= (graph->adc0 - graph->adc1);
	पंचांगp += graph->volt1;

	वापस पंचांगp < 0 ? 0 : पंचांगp;
पूर्ण

अटल पूर्णांक sc27xx_adc_convert_volt(काष्ठा sc27xx_adc_data *data, पूर्णांक channel,
				   पूर्णांक scale, पूर्णांक raw_adc)
अणु
	u32 numerator, denominator;
	u32 volt;

	/*
	 * Convert ADC values to voltage values according to the linear graph,
	 * and channel 5 and channel 1 has been calibrated, so we can just
	 * वापस the voltage values calculated by the linear graph. But other
	 * channels need be calculated to the real voltage values with the
	 * voltage ratio.
	 */
	चयन (channel) अणु
	हाल 5:
		वापस sc27xx_adc_to_volt(&big_scale_graph, raw_adc);

	हाल 1:
		वापस sc27xx_adc_to_volt(&small_scale_graph, raw_adc);

	शेष:
		volt = sc27xx_adc_to_volt(&small_scale_graph, raw_adc);
		अवरोध;
	पूर्ण

	sc27xx_adc_volt_ratio(data, channel, scale, &numerator, &denominator);

	वापस DIV_ROUND_CLOSEST(volt * denominator, numerator);
पूर्ण

अटल पूर्णांक sc27xx_adc_पढ़ो_processed(काष्ठा sc27xx_adc_data *data,
				     पूर्णांक channel, पूर्णांक scale, पूर्णांक *val)
अणु
	पूर्णांक ret, raw_adc;

	ret = sc27xx_adc_पढ़ो(data, channel, scale, &raw_adc);
	अगर (ret)
		वापस ret;

	*val = sc27xx_adc_convert_volt(data, channel, scale, raw_adc);
	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा sc27xx_adc_data *data = iio_priv(indio_dev);
	पूर्णांक scale = data->channel_scale[chan->channel];
	पूर्णांक ret, पंचांगp;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		ret = sc27xx_adc_पढ़ो(data, chan->channel, scale, &पंचांगp);
		mutex_unlock(&indio_dev->mlock);

		अगर (ret)
			वापस ret;

		*val = पंचांगp;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_PROCESSED:
		mutex_lock(&indio_dev->mlock);
		ret = sc27xx_adc_पढ़ो_processed(data, chan->channel, scale,
						&पंचांगp);
		mutex_unlock(&indio_dev->mlock);

		अगर (ret)
			वापस ret;

		*val = पंचांगp;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = scale;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sc27xx_adc_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा sc27xx_adc_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		data->channel_scale[chan->channel] = val;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info sc27xx_info = अणु
	.पढ़ो_raw = &sc27xx_adc_पढ़ो_raw,
	.ग_लिखो_raw = &sc27xx_adc_ग_लिखो_raw,
पूर्ण;

#घोषणा SC27XX_ADC_CHANNEL(index, mask) अणु			\
	.type = IIO_VOLTAGE,					\
	.channel = index,					\
	.info_mask_separate = mask | BIT(IIO_CHAN_INFO_SCALE),	\
	.datasheet_name = "CH##index",				\
	.indexed = 1,						\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec sc27xx_channels[] = अणु
	SC27XX_ADC_CHANNEL(0, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(1, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(2, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(3, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(4, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(5, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(6, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(7, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(8, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(9, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(10, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(11, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(12, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(13, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(14, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(15, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(16, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(17, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(18, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(19, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(20, BIT(IIO_CHAN_INFO_RAW)),
	SC27XX_ADC_CHANNEL(21, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(22, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(23, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(24, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(25, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(26, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(27, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(28, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(29, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(30, BIT(IIO_CHAN_INFO_PROCESSED)),
	SC27XX_ADC_CHANNEL(31, BIT(IIO_CHAN_INFO_PROCESSED)),
पूर्ण;

अटल पूर्णांक sc27xx_adc_enable(काष्ठा sc27xx_adc_data *data)
अणु
	पूर्णांक ret;

	ret = regmap_update_bits(data->regmap, SC27XX_MODULE_EN,
				 SC27XX_MODULE_ADC_EN, SC27XX_MODULE_ADC_EN);
	अगर (ret)
		वापस ret;

	/* Enable ADC work घड़ी and controller घड़ी */
	ret = regmap_update_bits(data->regmap, SC27XX_ARM_CLK_EN,
				 SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN,
				 SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN);
	अगर (ret)
		जाओ disable_adc;

	/* ADC channel scales' calibration from nvmem device */
	ret = sc27xx_adc_scale_calibration(data, true);
	अगर (ret)
		जाओ disable_clk;

	ret = sc27xx_adc_scale_calibration(data, false);
	अगर (ret)
		जाओ disable_clk;

	वापस 0;

disable_clk:
	regmap_update_bits(data->regmap, SC27XX_ARM_CLK_EN,
			   SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN, 0);
disable_adc:
	regmap_update_bits(data->regmap, SC27XX_MODULE_EN,
			   SC27XX_MODULE_ADC_EN, 0);

	वापस ret;
पूर्ण

अटल व्योम sc27xx_adc_disable(व्योम *_data)
अणु
	काष्ठा sc27xx_adc_data *data = _data;

	/* Disable ADC work घड़ी and controller घड़ी */
	regmap_update_bits(data->regmap, SC27XX_ARM_CLK_EN,
			   SC27XX_CLK_ADC_EN | SC27XX_CLK_ADC_CLK_EN, 0);

	regmap_update_bits(data->regmap, SC27XX_MODULE_EN,
			   SC27XX_MODULE_ADC_EN, 0);
पूर्ण

अटल पूर्णांक sc27xx_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा sc27xx_adc_data *sc27xx_data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*sc27xx_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	sc27xx_data = iio_priv(indio_dev);

	sc27xx_data->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!sc27xx_data->regmap) अणु
		dev_err(dev, "failed to get ADC regmap\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "reg", &sc27xx_data->base);
	अगर (ret) अणु
		dev_err(dev, "failed to get ADC base address\n");
		वापस ret;
	पूर्ण

	sc27xx_data->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sc27xx_data->irq < 0)
		वापस sc27xx_data->irq;

	ret = of_hwspin_lock_get_id(np, 0);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get hwspinlock id\n");
		वापस ret;
	पूर्ण

	sc27xx_data->hwlock = devm_hwspin_lock_request_specअगरic(dev, ret);
	अगर (!sc27xx_data->hwlock) अणु
		dev_err(dev, "failed to request hwspinlock\n");
		वापस -ENXIO;
	पूर्ण

	sc27xx_data->dev = dev;

	ret = sc27xx_adc_enable(sc27xx_data);
	अगर (ret) अणु
		dev_err(dev, "failed to enable ADC module\n");
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, sc27xx_adc_disable, sc27xx_data);
	अगर (ret) अणु
		dev_err(dev, "failed to add ADC disable action\n");
		वापस ret;
	पूर्ण

	indio_dev->name = dev_name(dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &sc27xx_info;
	indio_dev->channels = sc27xx_channels;
	indio_dev->num_channels = ARRAY_SIZE(sc27xx_channels);
	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret)
		dev_err(dev, "could not register iio (ADC)");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id sc27xx_adc_of_match[] = अणु
	अणु .compatible = "sprd,sc2731-adc", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver sc27xx_adc_driver = अणु
	.probe = sc27xx_adc_probe,
	.driver = अणु
		.name = "sc27xx-adc",
		.of_match_table = sc27xx_adc_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sc27xx_adc_driver);

MODULE_AUTHOR("Freeman Liu <freeman.liu@spreadtrum.com>");
MODULE_DESCRIPTION("Spreadtrum SC27XX ADC Driver");
MODULE_LICENSE("GPL v2");
