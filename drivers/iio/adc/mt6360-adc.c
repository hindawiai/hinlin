<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/bits.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा MT6360_REG_PMUCHGCTRL3	0x313
#घोषणा MT6360_REG_PMUADCCFG	0x356
#घोषणा MT6360_REG_PMUADCIDLET	0x358
#घोषणा MT6360_REG_PMUADCRPT1	0x35A

/* PMUCHGCTRL3 0x313 */
#घोषणा MT6360_AICR_MASK	GENMASK(7, 2)
#घोषणा MT6360_AICR_SHFT	2
#घोषणा MT6360_AICR_400MA	0x6
/* PMUADCCFG 0x356 */
#घोषणा MT6360_ADCEN_MASK	BIT(15)
/* PMUADCRPT1 0x35A */
#घोषणा MT6360_PREFERCH_MASK	GENMASK(7, 4)
#घोषणा MT6360_PREFERCH_SHFT	4
#घोषणा MT6360_RPTCH_MASK	GENMASK(3, 0)
#घोषणा MT6360_NO_PREFER	15

/* Time in ms */
#घोषणा ADC_WAIT_TIME_MS	25
#घोषणा ADC_CONV_TIMEOUT_MS	100
#घोषणा ADC_LOOP_TIME_US	2000

क्रमागत अणु
	MT6360_CHAN_USBID = 0,
	MT6360_CHAN_VBUSDIV5,
	MT6360_CHAN_VBUSDIV2,
	MT6360_CHAN_VSYS,
	MT6360_CHAN_VBAT,
	MT6360_CHAN_IBUS,
	MT6360_CHAN_IBAT,
	MT6360_CHAN_CHG_VDDP,
	MT6360_CHAN_TEMP_JC,
	MT6360_CHAN_VREF_TS,
	MT6360_CHAN_TS,
	MT6360_CHAN_MAX
पूर्ण;

काष्ठा mt6360_adc_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	/* Due to only one set of ADC control, this lock is used to prevent the race condition */
	काष्ठा mutex adc_lock;
	kसमय_प्रकार last_off_बारtamps[MT6360_CHAN_MAX];
पूर्ण;

अटल पूर्णांक mt6360_adc_पढ़ो_channel(काष्ठा mt6360_adc_data *mad, पूर्णांक channel, पूर्णांक *val)
अणु
	__be16 adc_enable;
	u8 rpt[3];
	kसमय_प्रकार predict_end_t, समयout;
	अचिन्हित पूर्णांक pre_रुको_समय;
	पूर्णांक ret;

	mutex_lock(&mad->adc_lock);

	/* Select the preferred ADC channel */
	ret = regmap_update_bits(mad->regmap, MT6360_REG_PMUADCRPT1, MT6360_PREFERCH_MASK,
				 channel << MT6360_PREFERCH_SHFT);
	अगर (ret)
		जाओ out_adc_lock;

	adc_enable = cpu_to_be16(MT6360_ADCEN_MASK | BIT(channel));
	ret = regmap_raw_ग_लिखो(mad->regmap, MT6360_REG_PMUADCCFG, &adc_enable, माप(adc_enable));
	अगर (ret)
		जाओ out_adc_lock;

	predict_end_t = kसमय_add_ms(mad->last_off_बारtamps[channel], 2 * ADC_WAIT_TIME_MS);

	अगर (kसमय_after(kसमय_get(), predict_end_t))
		pre_रुको_समय = ADC_WAIT_TIME_MS;
	अन्यथा
		pre_रुको_समय = 3 * ADC_WAIT_TIME_MS;

	अगर (msleep_पूर्णांकerruptible(pre_रुको_समय)) अणु
		ret = -ERESTARTSYS;
		जाओ out_adc_conv;
	पूर्ण

	समयout = kसमय_add_ms(kसमय_get(), ADC_CONV_TIMEOUT_MS);
	जबतक (true) अणु
		ret = regmap_raw_पढ़ो(mad->regmap, MT6360_REG_PMUADCRPT1, rpt, माप(rpt));
		अगर (ret)
			जाओ out_adc_conv;

		/*
		 * There are two functions, ZCV and TypeC OTP, running ADC VBAT and TS in
		 * background, and ADC samples are taken on a fixed frequency no matter पढ़ो the
		 * previous one or not.
		 * To aव्योम conflict, We set minimum समय threshold after enable ADC and
		 * check report channel is the same.
		 * The worst हाल is run the same ADC twice and background function is also running,
		 * ADC conversion sequence is desire channel beक्रमe start ADC, background ADC,
		 * desire channel after start ADC.
		 * So the minimum correct data is three बार of typical conversion समय.
		 */
		अगर ((rpt[0] & MT6360_RPTCH_MASK) == channel)
			अवरोध;

		अगर (kसमय_compare(kसमय_get(), समयout) > 0) अणु
			ret = -ETIMEDOUT;
			जाओ out_adc_conv;
		पूर्ण

		usleep_range(ADC_LOOP_TIME_US / 2, ADC_LOOP_TIME_US);
	पूर्ण

	*val = rpt[1] << 8 | rpt[2];
	ret = IIO_VAL_INT;

out_adc_conv:
	/* Only keep ADC enable */
	adc_enable = cpu_to_be16(MT6360_ADCEN_MASK);
	regmap_raw_ग_लिखो(mad->regmap, MT6360_REG_PMUADCCFG, &adc_enable, माप(adc_enable));
	mad->last_off_बारtamps[channel] = kसमय_get();
	/* Config prefer channel to NO_PREFER */
	regmap_update_bits(mad->regmap, MT6360_REG_PMUADCRPT1, MT6360_PREFERCH_MASK,
			   MT6360_NO_PREFER << MT6360_PREFERCH_SHFT);
out_adc_lock:
	mutex_unlock(&mad->adc_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mt6360_adc_पढ़ो_scale(काष्ठा mt6360_adc_data *mad, पूर्णांक channel, पूर्णांक *val, पूर्णांक *val2)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	चयन (channel) अणु
	हाल MT6360_CHAN_USBID:
	हाल MT6360_CHAN_VSYS:
	हाल MT6360_CHAN_VBAT:
	हाल MT6360_CHAN_CHG_VDDP:
	हाल MT6360_CHAN_VREF_TS:
	हाल MT6360_CHAN_TS:
		*val = 1250;
		वापस IIO_VAL_INT;
	हाल MT6360_CHAN_VBUSDIV5:
		*val = 6250;
		वापस IIO_VAL_INT;
	हाल MT6360_CHAN_VBUSDIV2:
	हाल MT6360_CHAN_IBUS:
	हाल MT6360_CHAN_IBAT:
		*val = 2500;

		अगर (channel == MT6360_CHAN_IBUS) अणु
			/* IBUS will be affected by input current limit क्रम the dअगरferent Ron */
			/* Check whether the config is <400mA or not */
			ret = regmap_पढ़ो(mad->regmap, MT6360_REG_PMUCHGCTRL3, &regval);
			अगर (ret)
				वापस ret;

			regval = (regval & MT6360_AICR_MASK) >> MT6360_AICR_SHFT;
			अगर (regval < MT6360_AICR_400MA)
				*val = 1900;
		पूर्ण

		वापस IIO_VAL_INT;
	हाल MT6360_CHAN_TEMP_JC:
		*val = 105;
		*val2 = 100;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mt6360_adc_पढ़ो_offset(काष्ठा mt6360_adc_data *mad, पूर्णांक channel, पूर्णांक *val)
अणु
	*val = (channel == MT6360_CHAN_TEMP_JC) ? -80 : 0;
	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक mt6360_adc_पढ़ो_raw(काष्ठा iio_dev *iio_dev, स्थिर काष्ठा iio_chan_spec *chan,
			       पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mt6360_adc_data *mad = iio_priv(iio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस mt6360_adc_पढ़ो_channel(mad, chan->channel, val);
	हाल IIO_CHAN_INFO_SCALE:
		वापस mt6360_adc_पढ़ो_scale(mad, chan->channel, val, val2);
	हाल IIO_CHAN_INFO_OFFSET:
		वापस mt6360_adc_पढ़ो_offset(mad, chan->channel, val);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *mt6360_channel_labels[MT6360_CHAN_MAX] = अणु
	"usbid", "vbusdiv5", "vbusdiv2", "vsys", "vbat", "ibus", "ibat", "chg_vddp",
	"temp_jc", "vref_ts", "ts",
पूर्ण;

अटल पूर्णांक mt6360_adc_पढ़ो_label(काष्ठा iio_dev *iio_dev, स्थिर काष्ठा iio_chan_spec *chan,
				 अक्षर *label)
अणु
	वापस snम_लिखो(label, PAGE_SIZE, "%s\n", mt6360_channel_labels[chan->channel]);
पूर्ण

अटल स्थिर काष्ठा iio_info mt6360_adc_iio_info = अणु
	.पढ़ो_raw = mt6360_adc_पढ़ो_raw,
	.पढ़ो_label = mt6360_adc_पढ़ो_label,
पूर्ण;

#घोषणा MT6360_ADC_CHAN(_idx, _type) अणु				\
	.type = _type,						\
	.channel = MT6360_CHAN_##_idx,				\
	.scan_index = MT6360_CHAN_##_idx,			\
	.datasheet_name = #_idx,				\
	.scan_type =  अणु						\
		.sign = 'u',					\
		.realbits = 16,					\
		.storagebits = 16,				\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
	.indexed = 1,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
				BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_OFFSET),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mt6360_adc_channels[] = अणु
	MT6360_ADC_CHAN(USBID, IIO_VOLTAGE),
	MT6360_ADC_CHAN(VBUSDIV5, IIO_VOLTAGE),
	MT6360_ADC_CHAN(VBUSDIV2, IIO_VOLTAGE),
	MT6360_ADC_CHAN(VSYS, IIO_VOLTAGE),
	MT6360_ADC_CHAN(VBAT, IIO_VOLTAGE),
	MT6360_ADC_CHAN(IBUS, IIO_CURRENT),
	MT6360_ADC_CHAN(IBAT, IIO_CURRENT),
	MT6360_ADC_CHAN(CHG_VDDP, IIO_VOLTAGE),
	MT6360_ADC_CHAN(TEMP_JC, IIO_TEMP),
	MT6360_ADC_CHAN(VREF_TS, IIO_VOLTAGE),
	MT6360_ADC_CHAN(TS, IIO_VOLTAGE),
	IIO_CHAN_SOFT_TIMESTAMP(MT6360_CHAN_MAX),
पूर्ण;

अटल irqवापस_t mt6360_adc_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mt6360_adc_data *mad = iio_priv(indio_dev);
	काष्ठा अणु
		u16 values[MT6360_CHAN_MAX];
		पूर्णांक64_t बारtamp;
	पूर्ण data __aligned(8);
	पूर्णांक i = 0, bit, val, ret;

	स_रखो(&data, 0, माप(data));
	क्रम_each_set_bit(bit, indio_dev->active_scan_mask, indio_dev->masklength) अणु
		ret = mt6360_adc_पढ़ो_channel(mad, bit, &val);
		अगर (ret < 0) अणु
			dev_warn(&indio_dev->dev, "Failed to get channel %d conversion val\n", bit);
			जाओ out;
		पूर्ण

		data.values[i++] = val;
	पूर्ण
	iio_push_to_buffers_with_बारtamp(indio_dev, &data, iio_get_समय_ns(indio_dev));
out:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत पूर्णांक mt6360_adc_reset(काष्ठा mt6360_adc_data *info)
अणु
	__be16 adc_enable;
	kसमय_प्रकार all_off_समय;
	पूर्णांक i, ret;

	/* Clear ADC idle रुको समय to 0 */
	ret = regmap_ग_लिखो(info->regmap, MT6360_REG_PMUADCIDLET, 0);
	अगर (ret)
		वापस ret;

	/* Only keep ADC enable, but keep all channels off */
	adc_enable = cpu_to_be16(MT6360_ADCEN_MASK);
	ret = regmap_raw_ग_लिखो(info->regmap, MT6360_REG_PMUADCCFG, &adc_enable, माप(adc_enable));
	अगर (ret)
		वापस ret;

	/* Reset all channel off समय to the current one */
	all_off_समय = kसमय_get();
	क्रम (i = 0; i < MT6360_CHAN_MAX; i++)
		info->last_off_बारtamps[i] = all_off_समय;

	वापस 0;
पूर्ण

अटल पूर्णांक mt6360_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6360_adc_data *mad;
	काष्ठा regmap *regmap;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap) अणु
		dev_err(&pdev->dev, "Failed to get parent regmap\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*mad));
	अगर (!indio_dev)
		वापस -ENOMEM;

	mad = iio_priv(indio_dev);
	mad->dev = &pdev->dev;
	mad->regmap = regmap;
	mutex_init(&mad->adc_lock);

	ret = mt6360_adc_reset(mad);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to reset adc\n");
		वापस ret;
	पूर्ण

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &mt6360_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mt6360_adc_channels;
	indio_dev->num_channels = ARRAY_SIZE(mt6360_adc_channels);

	ret = devm_iio_triggered_buffer_setup(&pdev->dev, indio_dev, शून्य,
					      mt6360_adc_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to allocate iio trigger buffer\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&pdev->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused mt6360_adc_of_id[] = अणु
	अणु .compatible = "mediatek,mt6360-adc", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6360_adc_of_id);

अटल काष्ठा platक्रमm_driver mt6360_adc_driver = अणु
	.driver = अणु
		.name = "mt6360-adc",
		.of_match_table = mt6360_adc_of_id,
	पूर्ण,
	.probe = mt6360_adc_probe,
पूर्ण;
module_platक्रमm_driver(mt6360_adc_driver);

MODULE_AUTHOR("Gene Chen <gene_chen@richtek.com>");
MODULE_DESCRIPTION("MT6360 ADC Driver");
MODULE_LICENSE("GPL v2");
