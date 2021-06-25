<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ST SPEAr ADC driver
 *
 * Copyright 2012 Stefan Roese <sr@denx.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/completion.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/* SPEAR रेजिस्टरs definitions */
#घोषणा SPEAR600_ADC_SCAN_RATE_LO(x)	((x) & 0xFFFF)
#घोषणा SPEAR600_ADC_SCAN_RATE_HI(x)	(((x) >> 0x10) & 0xFFFF)
#घोषणा SPEAR_ADC_CLK_LOW(x)		(((x) & 0xf) << 0)
#घोषणा SPEAR_ADC_CLK_HIGH(x)		(((x) & 0xf) << 4)

/* Bit definitions क्रम SPEAR_ADC_STATUS */
#घोषणा SPEAR_ADC_STATUS_START_CONVERSION	BIT(0)
#घोषणा SPEAR_ADC_STATUS_CHANNEL_NUM(x)		((x) << 1)
#घोषणा SPEAR_ADC_STATUS_ADC_ENABLE		BIT(4)
#घोषणा SPEAR_ADC_STATUS_AVG_SAMPLE(x)		((x) << 5)
#घोषणा SPEAR_ADC_STATUS_VREF_INTERNAL		BIT(9)

#घोषणा SPEAR_ADC_DATA_MASK		0x03ff
#घोषणा SPEAR_ADC_DATA_BITS		10

#घोषणा SPEAR_ADC_MOD_NAME "spear-adc"

#घोषणा SPEAR_ADC_CHANNEL_NUM		8

#घोषणा SPEAR_ADC_CLK_MIN			2500000
#घोषणा SPEAR_ADC_CLK_MAX			20000000

काष्ठा adc_regs_spear3xx अणु
	u32 status;
	u32 average;
	u32 scan_rate;
	u32 clk;	/* Not avail क्रम 1340 & 1310 */
	u32 ch_ctrl[SPEAR_ADC_CHANNEL_NUM];
	u32 ch_data[SPEAR_ADC_CHANNEL_NUM];
पूर्ण;

काष्ठा chan_data अणु
	u32 lsb;
	u32 msb;
पूर्ण;

काष्ठा adc_regs_spear6xx अणु
	u32 status;
	u32 pad[2];
	u32 clk;
	u32 ch_ctrl[SPEAR_ADC_CHANNEL_NUM];
	काष्ठा chan_data ch_data[SPEAR_ADC_CHANNEL_NUM];
	u32 scan_rate_lo;
	u32 scan_rate_hi;
	काष्ठा chan_data average;
पूर्ण;

काष्ठा spear_adc_state अणु
	काष्ठा device_node *np;
	काष्ठा adc_regs_spear3xx __iomem *adc_base_spear3xx;
	काष्ठा adc_regs_spear6xx __iomem *adc_base_spear6xx;
	काष्ठा clk *clk;
	काष्ठा completion completion;
	/*
	 * Lock to protect the device state during a potential concurrent
	 * पढ़ो access from userspace. Reading a raw value requires a sequence
	 * of रेजिस्टर ग_लिखोs, then a रुको क्रम a completion callback,
	 * and finally a रेजिस्टर पढ़ो, during which userspace could issue
	 * another पढ़ो request. This lock protects a पढ़ो access from
	 * ocurring beक्रमe another one has finished.
	 */
	काष्ठा mutex lock;
	u32 current_clk;
	u32 sampling_freq;
	u32 avg_samples;
	u32 vref_बाह्यal;
	u32 value;
पूर्ण;

/*
 * Functions to access some SPEAr ADC रेजिस्टर. Abstracted पूर्णांकo
 * अटल अंतरभूत functions, because of dअगरferent रेजिस्टर offsets
 * on dअगरferent SoC variants (SPEAr300 vs SPEAr600 etc).
 */
अटल व्योम spear_adc_set_status(काष्ठा spear_adc_state *st, u32 val)
अणु
	__raw_ग_लिखोl(val, &st->adc_base_spear6xx->status);
पूर्ण

अटल व्योम spear_adc_set_clk(काष्ठा spear_adc_state *st, u32 val)
अणु
	u32 clk_high, clk_low, count;
	u32 apb_clk = clk_get_rate(st->clk);

	count = DIV_ROUND_UP(apb_clk, val);
	clk_low = count / 2;
	clk_high = count - clk_low;
	st->current_clk = apb_clk / count;

	__raw_ग_लिखोl(SPEAR_ADC_CLK_LOW(clk_low) | SPEAR_ADC_CLK_HIGH(clk_high),
		     &st->adc_base_spear6xx->clk);
पूर्ण

अटल व्योम spear_adc_set_ctrl(काष्ठा spear_adc_state *st, पूर्णांक n,
			       u32 val)
अणु
	__raw_ग_लिखोl(val, &st->adc_base_spear6xx->ch_ctrl[n]);
पूर्ण

अटल u32 spear_adc_get_average(काष्ठा spear_adc_state *st)
अणु
	अगर (of_device_is_compatible(st->np, "st,spear600-adc")) अणु
		वापस __raw_पढ़ोl(&st->adc_base_spear6xx->average.msb) &
			SPEAR_ADC_DATA_MASK;
	पूर्ण अन्यथा अणु
		वापस __raw_पढ़ोl(&st->adc_base_spear3xx->average) &
			SPEAR_ADC_DATA_MASK;
	पूर्ण
पूर्ण

अटल व्योम spear_adc_set_scanrate(काष्ठा spear_adc_state *st, u32 rate)
अणु
	अगर (of_device_is_compatible(st->np, "st,spear600-adc")) अणु
		__raw_ग_लिखोl(SPEAR600_ADC_SCAN_RATE_LO(rate),
			     &st->adc_base_spear6xx->scan_rate_lo);
		__raw_ग_लिखोl(SPEAR600_ADC_SCAN_RATE_HI(rate),
			     &st->adc_base_spear6xx->scan_rate_hi);
	पूर्ण अन्यथा अणु
		__raw_ग_लिखोl(rate, &st->adc_base_spear3xx->scan_rate);
	पूर्ण
पूर्ण

अटल पूर्णांक spear_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val,
			      पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा spear_adc_state *st = iio_priv(indio_dev);
	u32 status;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);

		status = SPEAR_ADC_STATUS_CHANNEL_NUM(chan->channel) |
			SPEAR_ADC_STATUS_AVG_SAMPLE(st->avg_samples) |
			SPEAR_ADC_STATUS_START_CONVERSION |
			SPEAR_ADC_STATUS_ADC_ENABLE;
		अगर (st->vref_बाह्यal == 0)
			status |= SPEAR_ADC_STATUS_VREF_INTERNAL;

		spear_adc_set_status(st, status);
		रुको_क्रम_completion(&st->completion); /* set by ISR */
		*val = st->value;

		mutex_unlock(&st->lock);

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_बाह्यal;
		*val2 = SPEAR_ADC_DATA_BITS;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->current_clk;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक spear_adc_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा spear_adc_state *st = iio_priv(indio_dev);
	पूर्णांक ret = 0;

	अगर (mask != IIO_CHAN_INFO_SAMP_FREQ)
		वापस -EINVAL;

	mutex_lock(&st->lock);

	अगर ((val < SPEAR_ADC_CLK_MIN) ||
	    (val > SPEAR_ADC_CLK_MAX) ||
	    (val2 != 0)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	spear_adc_set_clk(st, val);

out:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

#घोषणा SPEAR_ADC_CHAN(idx) अणु				\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),\
	.channel = idx,					\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec spear_adc_iio_channels[] = अणु
	SPEAR_ADC_CHAN(0),
	SPEAR_ADC_CHAN(1),
	SPEAR_ADC_CHAN(2),
	SPEAR_ADC_CHAN(3),
	SPEAR_ADC_CHAN(4),
	SPEAR_ADC_CHAN(5),
	SPEAR_ADC_CHAN(6),
	SPEAR_ADC_CHAN(7),
पूर्ण;

अटल irqवापस_t spear_adc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spear_adc_state *st = dev_id;

	/* Read value to clear IRQ */
	st->value = spear_adc_get_average(st);
	complete(&st->completion);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक spear_adc_configure(काष्ठा spear_adc_state *st)
अणु
	पूर्णांक i;

	/* Reset ADC core */
	spear_adc_set_status(st, 0);
	__raw_ग_लिखोl(0, &st->adc_base_spear6xx->clk);
	क्रम (i = 0; i < 8; i++)
		spear_adc_set_ctrl(st, i, 0);
	spear_adc_set_scanrate(st, 0);

	spear_adc_set_clk(st, st->sampling_freq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info spear_adc_info = अणु
	.पढ़ो_raw = &spear_adc_पढ़ो_raw,
	.ग_लिखो_raw = &spear_adc_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक spear_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spear_adc_state *st;
	काष्ठा iio_dev *indio_dev = शून्य;
	पूर्णांक ret = -ENODEV;
	पूर्णांक irq;

	indio_dev = devm_iio_device_alloc(dev, माप(काष्ठा spear_adc_state));
	अगर (!indio_dev) अणु
		dev_err(dev, "failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	st = iio_priv(indio_dev);

	mutex_init(&st->lock);

	st->np = np;

	/*
	 * SPEAr600 has a dअगरferent रेजिस्टर layout than other SPEAr SoC's
	 * (e.g. SPEAr3xx). Let's provide two रेजिस्टर base addresses
	 * to support multi-arch kernels.
	 */
	st->adc_base_spear6xx = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(st->adc_base_spear6xx))
		वापस PTR_ERR(st->adc_base_spear6xx);

	st->adc_base_spear3xx =
		(काष्ठा adc_regs_spear3xx __iomem *)st->adc_base_spear6xx;

	st->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(st->clk)) अणु
		dev_err(dev, "failed getting clock\n");
		वापस PTR_ERR(st->clk);
	पूर्ण

	ret = clk_prepare_enable(st->clk);
	अगर (ret) अणु
		dev_err(dev, "failed enabling clock\n");
		वापस ret;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		ret = -EINVAL;
		जाओ errout2;
	पूर्ण

	ret = devm_request_irq(dev, irq, spear_adc_isr, 0, SPEAR_ADC_MOD_NAME,
			       st);
	अगर (ret < 0) अणु
		dev_err(dev, "failed requesting interrupt\n");
		जाओ errout2;
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "sampling-frequency",
				 &st->sampling_freq)) अणु
		dev_err(dev, "sampling-frequency missing in DT\n");
		ret = -EINVAL;
		जाओ errout2;
	पूर्ण

	/*
	 * Optional avg_samples शेषs to 0, resulting in single data
	 * conversion
	 */
	of_property_पढ़ो_u32(np, "average-samples", &st->avg_samples);

	/*
	 * Optional vref_बाह्यal शेषs to 0, resulting in पूर्णांकernal vref
	 * selection
	 */
	of_property_पढ़ो_u32(np, "vref-external", &st->vref_बाह्यal);

	spear_adc_configure(st);

	platक्रमm_set_drvdata(pdev, indio_dev);

	init_completion(&st->completion);

	indio_dev->name = SPEAR_ADC_MOD_NAME;
	indio_dev->info = &spear_adc_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = spear_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(spear_adc_iio_channels);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ errout2;

	dev_info(dev, "SPEAR ADC driver loaded, IRQ %d\n", irq);

	वापस 0;

errout2:
	clk_disable_unprepare(st->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक spear_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा spear_adc_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	clk_disable_unprepare(st->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spear_adc_dt_ids[] = अणु
	अणु .compatible = "st,spear600-adc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, spear_adc_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver spear_adc_driver = अणु
	.probe		= spear_adc_probe,
	.हटाओ		= spear_adc_हटाओ,
	.driver		= अणु
		.name	= SPEAR_ADC_MOD_NAME,
		.of_match_table = of_match_ptr(spear_adc_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(spear_adc_driver);

MODULE_AUTHOR("Stefan Roese <sr@denx.de>");
MODULE_DESCRIPTION("SPEAr ADC driver");
MODULE_LICENSE("GPL");
