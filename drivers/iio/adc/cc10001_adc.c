<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015 Imagination Technologies Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

/* Registers */
#घोषणा CC10001_ADC_CONFIG		0x00
#घोषणा CC10001_ADC_START_CONV		BIT(4)
#घोषणा CC10001_ADC_MODE_SINGLE_CONV	BIT(5)

#घोषणा CC10001_ADC_DDATA_OUT		0x04
#घोषणा CC10001_ADC_EOC			0x08
#घोषणा CC10001_ADC_EOC_SET		BIT(0)

#घोषणा CC10001_ADC_CHSEL_SAMPLED	0x0c
#घोषणा CC10001_ADC_POWER_DOWN		0x10
#घोषणा CC10001_ADC_POWER_DOWN_SET	BIT(0)

#घोषणा CC10001_ADC_DEBUG		0x14
#घोषणा CC10001_ADC_DATA_COUNT		0x20

#घोषणा CC10001_ADC_DATA_MASK		GENMASK(9, 0)
#घोषणा CC10001_ADC_NUM_CHANNELS	8
#घोषणा CC10001_ADC_CH_MASK		GENMASK(2, 0)

#घोषणा CC10001_INVALID_SAMPLED		0xffff
#घोषणा CC10001_MAX_POLL_COUNT		20

/*
 * As per device specअगरication, रुको six घड़ी cycles after घातer-up to
 * activate START. Since adding two more घड़ी cycles delay करोes not
 * impact the perक्रमmance too much, we are adding two additional cycles delay
 * पूर्णांकentionally here.
 */
#घोषणा	CC10001_WAIT_CYCLES		8

काष्ठा cc10001_adc_device अणु
	व्योम __iomem *reg_base;
	काष्ठा clk *adc_clk;
	काष्ठा regulator *reg;
	u16 *buf;

	bool shared;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक start_delay_ns;
	अचिन्हित पूर्णांक eoc_delay_ns;
पूर्ण;

अटल अंतरभूत व्योम cc10001_adc_ग_लिखो_reg(काष्ठा cc10001_adc_device *adc_dev,
					 u32 reg, u32 val)
अणु
	ग_लिखोl(val, adc_dev->reg_base + reg);
पूर्ण

अटल अंतरभूत u32 cc10001_adc_पढ़ो_reg(काष्ठा cc10001_adc_device *adc_dev,
				       u32 reg)
अणु
	वापस पढ़ोl(adc_dev->reg_base + reg);
पूर्ण

अटल व्योम cc10001_adc_घातer_up(काष्ठा cc10001_adc_device *adc_dev)
अणु
	cc10001_adc_ग_लिखो_reg(adc_dev, CC10001_ADC_POWER_DOWN, 0);
	ndelay(adc_dev->start_delay_ns);
पूर्ण

अटल व्योम cc10001_adc_घातer_करोwn(काष्ठा cc10001_adc_device *adc_dev)
अणु
	cc10001_adc_ग_लिखो_reg(adc_dev, CC10001_ADC_POWER_DOWN,
			      CC10001_ADC_POWER_DOWN_SET);
पूर्ण

अटल व्योम cc10001_adc_start(काष्ठा cc10001_adc_device *adc_dev,
			      अचिन्हित पूर्णांक channel)
अणु
	u32 val;

	/* Channel selection and mode of operation */
	val = (channel & CC10001_ADC_CH_MASK) | CC10001_ADC_MODE_SINGLE_CONV;
	cc10001_adc_ग_लिखो_reg(adc_dev, CC10001_ADC_CONFIG, val);

	udelay(1);
	val = cc10001_adc_पढ़ो_reg(adc_dev, CC10001_ADC_CONFIG);
	val = val | CC10001_ADC_START_CONV;
	cc10001_adc_ग_लिखो_reg(adc_dev, CC10001_ADC_CONFIG, val);
पूर्ण

अटल u16 cc10001_adc_poll_करोne(काष्ठा iio_dev *indio_dev,
				 अचिन्हित पूर्णांक channel,
				 अचिन्हित पूर्णांक delay)
अणु
	काष्ठा cc10001_adc_device *adc_dev = iio_priv(indio_dev);
	अचिन्हित पूर्णांक poll_count = 0;

	जबतक (!(cc10001_adc_पढ़ो_reg(adc_dev, CC10001_ADC_EOC) &
			CC10001_ADC_EOC_SET)) अणु

		ndelay(delay);
		अगर (poll_count++ == CC10001_MAX_POLL_COUNT)
			वापस CC10001_INVALID_SAMPLED;
	पूर्ण

	poll_count = 0;
	जबतक ((cc10001_adc_पढ़ो_reg(adc_dev, CC10001_ADC_CHSEL_SAMPLED) &
			CC10001_ADC_CH_MASK) != channel) अणु

		ndelay(delay);
		अगर (poll_count++ == CC10001_MAX_POLL_COUNT)
			वापस CC10001_INVALID_SAMPLED;
	पूर्ण

	/* Read the 10 bit output रेजिस्टर */
	वापस cc10001_adc_पढ़ो_reg(adc_dev, CC10001_ADC_DDATA_OUT) &
			       CC10001_ADC_DATA_MASK;
पूर्ण

अटल irqवापस_t cc10001_adc_trigger_h(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा cc10001_adc_device *adc_dev;
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक delay_ns;
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक scan_idx;
	bool sample_invalid;
	u16 *data;
	पूर्णांक i;

	indio_dev = pf->indio_dev;
	adc_dev = iio_priv(indio_dev);
	data = adc_dev->buf;

	mutex_lock(&adc_dev->lock);

	अगर (!adc_dev->shared)
		cc10001_adc_घातer_up(adc_dev);

	/* Calculate delay step क्रम eoc and sampled data */
	delay_ns = adc_dev->eoc_delay_ns / CC10001_MAX_POLL_COUNT;

	i = 0;
	sample_invalid = false;
	क्रम_each_set_bit(scan_idx, indio_dev->active_scan_mask,
				  indio_dev->masklength) अणु

		channel = indio_dev->channels[scan_idx].channel;
		cc10001_adc_start(adc_dev, channel);

		data[i] = cc10001_adc_poll_करोne(indio_dev, channel, delay_ns);
		अगर (data[i] == CC10001_INVALID_SAMPLED) अणु
			dev_warn(&indio_dev->dev,
				 "invalid sample on channel %d\n", channel);
			sample_invalid = true;
			जाओ करोne;
		पूर्ण
		i++;
	पूर्ण

करोne:
	अगर (!adc_dev->shared)
		cc10001_adc_घातer_करोwn(adc_dev);

	mutex_unlock(&adc_dev->lock);

	अगर (!sample_invalid)
		iio_push_to_buffers_with_बारtamp(indio_dev, data,
						   iio_get_समय_ns(indio_dev));
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल u16 cc10001_adc_पढ़ो_raw_voltage(काष्ठा iio_dev *indio_dev,
					काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा cc10001_adc_device *adc_dev = iio_priv(indio_dev);
	अचिन्हित पूर्णांक delay_ns;
	u16 val;

	अगर (!adc_dev->shared)
		cc10001_adc_घातer_up(adc_dev);

	/* Calculate delay step क्रम eoc and sampled data */
	delay_ns = adc_dev->eoc_delay_ns / CC10001_MAX_POLL_COUNT;

	cc10001_adc_start(adc_dev, chan->channel);

	val = cc10001_adc_poll_करोne(indio_dev, chan->channel, delay_ns);

	अगर (!adc_dev->shared)
		cc10001_adc_घातer_करोwn(adc_dev);

	वापस val;
पूर्ण

अटल पूर्णांक cc10001_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan,
				 पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा cc10001_adc_device *adc_dev = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (iio_buffer_enabled(indio_dev))
			वापस -EBUSY;
		mutex_lock(&adc_dev->lock);
		*val = cc10001_adc_पढ़ो_raw_voltage(indio_dev, chan);
		mutex_unlock(&adc_dev->lock);

		अगर (*val == CC10001_INVALID_SAMPLED)
			वापस -EIO;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(adc_dev->reg);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक cc10001_update_scan_mode(काष्ठा iio_dev *indio_dev,
				    स्थिर अचिन्हित दीर्घ *scan_mask)
अणु
	काष्ठा cc10001_adc_device *adc_dev = iio_priv(indio_dev);

	kमुक्त(adc_dev->buf);
	adc_dev->buf = kदो_स्मृति(indio_dev->scan_bytes, GFP_KERNEL);
	अगर (!adc_dev->buf)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info cc10001_adc_info = अणु
	.पढ़ो_raw = &cc10001_adc_पढ़ो_raw,
	.update_scan_mode = &cc10001_update_scan_mode,
पूर्ण;

अटल पूर्णांक cc10001_adc_channel_init(काष्ठा iio_dev *indio_dev,
				    अचिन्हित दीर्घ channel_map)
अणु
	काष्ठा iio_chan_spec *chan_array, *बारtamp;
	अचिन्हित पूर्णांक bit, idx = 0;

	indio_dev->num_channels = biपंचांगap_weight(&channel_map,
						CC10001_ADC_NUM_CHANNELS) + 1;

	chan_array = devm_kसुस्मृति(&indio_dev->dev, indio_dev->num_channels,
				  माप(काष्ठा iio_chan_spec),
				  GFP_KERNEL);
	अगर (!chan_array)
		वापस -ENOMEM;

	क्रम_each_set_bit(bit, &channel_map, CC10001_ADC_NUM_CHANNELS) अणु
		काष्ठा iio_chan_spec *chan = &chan_array[idx];

		chan->type = IIO_VOLTAGE;
		chan->indexed = 1;
		chan->channel = bit;
		chan->scan_index = idx;
		chan->scan_type.sign = 'u';
		chan->scan_type.realbits = 10;
		chan->scan_type.storagebits = 16;
		chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
		chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
		idx++;
	पूर्ण

	बारtamp = &chan_array[idx];
	बारtamp->type = IIO_TIMESTAMP;
	बारtamp->channel = -1;
	बारtamp->scan_index = idx;
	बारtamp->scan_type.sign = 's';
	बारtamp->scan_type.realbits = 64;
	बारtamp->scan_type.storagebits = 64;

	indio_dev->channels = chan_array;

	वापस 0;
पूर्ण

अटल पूर्णांक cc10001_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा cc10001_adc_device *adc_dev;
	अचिन्हित दीर्घ adc_clk_rate;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित दीर्घ channel_map;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*adc_dev));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	adc_dev = iio_priv(indio_dev);

	channel_map = GENMASK(CC10001_ADC_NUM_CHANNELS - 1, 0);
	अगर (!of_property_पढ़ो_u32(node, "adc-reserved-channels", &ret)) अणु
		adc_dev->shared = true;
		channel_map &= ~ret;
	पूर्ण

	adc_dev->reg = devm_regulator_get(&pdev->dev, "vref");
	अगर (IS_ERR(adc_dev->reg))
		वापस PTR_ERR(adc_dev->reg);

	ret = regulator_enable(adc_dev->reg);
	अगर (ret)
		वापस ret;

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->info = &cc10001_adc_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	adc_dev->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(adc_dev->reg_base)) अणु
		ret = PTR_ERR(adc_dev->reg_base);
		जाओ err_disable_reg;
	पूर्ण

	adc_dev->adc_clk = devm_clk_get(&pdev->dev, "adc");
	अगर (IS_ERR(adc_dev->adc_clk)) अणु
		dev_err(&pdev->dev, "failed to get the clock\n");
		ret = PTR_ERR(adc_dev->adc_clk);
		जाओ err_disable_reg;
	पूर्ण

	ret = clk_prepare_enable(adc_dev->adc_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable the clock\n");
		जाओ err_disable_reg;
	पूर्ण

	adc_clk_rate = clk_get_rate(adc_dev->adc_clk);
	अगर (!adc_clk_rate) अणु
		ret = -EINVAL;
		dev_err(&pdev->dev, "null clock rate!\n");
		जाओ err_disable_clk;
	पूर्ण

	adc_dev->eoc_delay_ns = NSEC_PER_SEC / adc_clk_rate;
	adc_dev->start_delay_ns = adc_dev->eoc_delay_ns * CC10001_WAIT_CYCLES;

	/*
	 * There is only one रेजिस्टर to घातer-up/घातer-करोwn the AUX ADC.
	 * If the ADC is shared among multiple CPUs, always घातer it up here.
	 * If the ADC is used only by the MIPS, घातer-up/घातer-करोwn at runसमय.
	 */
	अगर (adc_dev->shared)
		cc10001_adc_घातer_up(adc_dev);

	/* Setup the ADC channels available on the device */
	ret = cc10001_adc_channel_init(indio_dev, channel_map);
	अगर (ret < 0)
		जाओ err_disable_clk;

	mutex_init(&adc_dev->lock);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 &cc10001_adc_trigger_h, शून्य);
	अगर (ret < 0)
		जाओ err_disable_clk;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ err_cleanup_buffer;

	platक्रमm_set_drvdata(pdev, indio_dev);

	वापस 0;

err_cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
err_disable_clk:
	clk_disable_unprepare(adc_dev->adc_clk);
err_disable_reg:
	regulator_disable(adc_dev->reg);
	वापस ret;
पूर्ण

अटल पूर्णांक cc10001_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा cc10001_adc_device *adc_dev = iio_priv(indio_dev);

	cc10001_adc_घातer_करोwn(adc_dev);
	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	clk_disable_unprepare(adc_dev->adc_clk);
	regulator_disable(adc_dev->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cc10001_adc_dt_ids[] = अणु
	अणु .compatible = "cosmic,10001-adc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cc10001_adc_dt_ids);

अटल काष्ठा platक्रमm_driver cc10001_adc_driver = अणु
	.driver = अणु
		.name   = "cc10001-adc",
		.of_match_table = cc10001_adc_dt_ids,
	पूर्ण,
	.probe	= cc10001_adc_probe,
	.हटाओ	= cc10001_adc_हटाओ,
पूर्ण;
module_platक्रमm_driver(cc10001_adc_driver);

MODULE_AUTHOR("Phani Movva <Phani.Movva@imgtec.com>");
MODULE_DESCRIPTION("Cosmic Circuits ADC driver");
MODULE_LICENSE("GPL v2");
