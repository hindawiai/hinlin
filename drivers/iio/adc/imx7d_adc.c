<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale i.MX7D ADC driver
 *
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/sysfs.h>

/* ADC रेजिस्टर */
#घोषणा IMX7D_REG_ADC_CH_A_CFG1			0x00
#घोषणा IMX7D_REG_ADC_CH_A_CFG2			0x10
#घोषणा IMX7D_REG_ADC_CH_B_CFG1			0x20
#घोषणा IMX7D_REG_ADC_CH_B_CFG2			0x30
#घोषणा IMX7D_REG_ADC_CH_C_CFG1			0x40
#घोषणा IMX7D_REG_ADC_CH_C_CFG2			0x50
#घोषणा IMX7D_REG_ADC_CH_D_CFG1			0x60
#घोषणा IMX7D_REG_ADC_CH_D_CFG2			0x70
#घोषणा IMX7D_REG_ADC_CH_SW_CFG			0x80
#घोषणा IMX7D_REG_ADC_TIMER_UNIT		0x90
#घोषणा IMX7D_REG_ADC_DMA_FIFO			0xa0
#घोषणा IMX7D_REG_ADC_FIFO_STATUS		0xb0
#घोषणा IMX7D_REG_ADC_INT_SIG_EN		0xc0
#घोषणा IMX7D_REG_ADC_INT_EN			0xd0
#घोषणा IMX7D_REG_ADC_INT_STATUS		0xe0
#घोषणा IMX7D_REG_ADC_CHA_B_CNV_RSLT		0xf0
#घोषणा IMX7D_REG_ADC_CHC_D_CNV_RSLT		0x100
#घोषणा IMX7D_REG_ADC_CH_SW_CNV_RSLT		0x110
#घोषणा IMX7D_REG_ADC_DMA_FIFO_DAT		0x120
#घोषणा IMX7D_REG_ADC_ADC_CFG			0x130

#घोषणा IMX7D_REG_ADC_CHANNEL_CFG2_BASE		0x10
#घोषणा IMX7D_EACH_CHANNEL_REG_OFFSET		0x20

#घोषणा IMX7D_REG_ADC_CH_CFG1_CHANNEL_EN			(0x1 << 31)
#घोषणा IMX7D_REG_ADC_CH_CFG1_CHANNEL_SINGLE			BIT(30)
#घोषणा IMX7D_REG_ADC_CH_CFG1_CHANNEL_AVG_EN			BIT(29)
#घोषणा IMX7D_REG_ADC_CH_CFG1_CHANNEL_SEL(x)			((x) << 24)

#घोषणा IMX7D_REG_ADC_CH_CFG2_AVG_NUM_4				(0x0 << 12)
#घोषणा IMX7D_REG_ADC_CH_CFG2_AVG_NUM_8				(0x1 << 12)
#घोषणा IMX7D_REG_ADC_CH_CFG2_AVG_NUM_16			(0x2 << 12)
#घोषणा IMX7D_REG_ADC_CH_CFG2_AVG_NUM_32			(0x3 << 12)

#घोषणा IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_4			(0x0 << 29)
#घोषणा IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_8			(0x1 << 29)
#घोषणा IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_16			(0x2 << 29)
#घोषणा IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_32			(0x3 << 29)
#घोषणा IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_64			(0x4 << 29)
#घोषणा IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_128			(0x5 << 29)

#घोषणा IMX7D_REG_ADC_ADC_CFG_ADC_CLK_DOWN			BIT(31)
#घोषणा IMX7D_REG_ADC_ADC_CFG_ADC_POWER_DOWN			BIT(1)
#घोषणा IMX7D_REG_ADC_ADC_CFG_ADC_EN				BIT(0)

#घोषणा IMX7D_REG_ADC_INT_CHA_COV_INT_EN			BIT(8)
#घोषणा IMX7D_REG_ADC_INT_CHB_COV_INT_EN			BIT(9)
#घोषणा IMX7D_REG_ADC_INT_CHC_COV_INT_EN			BIT(10)
#घोषणा IMX7D_REG_ADC_INT_CHD_COV_INT_EN			BIT(11)
#घोषणा IMX7D_REG_ADC_INT_CHANNEL_INT_EN \
	(IMX7D_REG_ADC_INT_CHA_COV_INT_EN | \
	 IMX7D_REG_ADC_INT_CHB_COV_INT_EN | \
	 IMX7D_REG_ADC_INT_CHC_COV_INT_EN | \
	 IMX7D_REG_ADC_INT_CHD_COV_INT_EN)
#घोषणा IMX7D_REG_ADC_INT_STATUS_CHANNEL_INT_STATUS		0xf00
#घोषणा IMX7D_REG_ADC_INT_STATUS_CHANNEL_CONV_TIME_OUT		0xf0000

#घोषणा IMX7D_ADC_TIMEOUT		msecs_to_jअगरfies(100)
#घोषणा IMX7D_ADC_INPUT_CLK		24000000

क्रमागत imx7d_adc_clk_pre_भाग अणु
	IMX7D_ADC_ANALOG_CLK_PRE_DIV_4,
	IMX7D_ADC_ANALOG_CLK_PRE_DIV_8,
	IMX7D_ADC_ANALOG_CLK_PRE_DIV_16,
	IMX7D_ADC_ANALOG_CLK_PRE_DIV_32,
	IMX7D_ADC_ANALOG_CLK_PRE_DIV_64,
	IMX7D_ADC_ANALOG_CLK_PRE_DIV_128,
पूर्ण;

क्रमागत imx7d_adc_average_num अणु
	IMX7D_ADC_AVERAGE_NUM_4,
	IMX7D_ADC_AVERAGE_NUM_8,
	IMX7D_ADC_AVERAGE_NUM_16,
	IMX7D_ADC_AVERAGE_NUM_32,
पूर्ण;

काष्ठा imx7d_adc_feature अणु
	क्रमागत imx7d_adc_clk_pre_भाग clk_pre_भाग;
	क्रमागत imx7d_adc_average_num avg_num;

	u32 core_समय_unit;	/* impact the sample rate */
पूर्ण;

काष्ठा imx7d_adc अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	काष्ठा clk *clk;

	u32 vref_uv;
	u32 value;
	u32 channel;
	u32 pre_भाग_num;

	काष्ठा regulator *vref;
	काष्ठा imx7d_adc_feature adc_feature;

	काष्ठा completion completion;
पूर्ण;

काष्ठा imx7d_adc_analogue_core_clk अणु
	u32 pre_भाग;
	u32 reg_config;
पूर्ण;

#घोषणा IMX7D_ADC_ANALOGUE_CLK_CONFIG(_pre_भाग, _reg_conf) अणु	\
	.pre_भाग = (_pre_भाग),					\
	.reg_config = (_reg_conf),				\
पूर्ण

अटल स्थिर काष्ठा imx7d_adc_analogue_core_clk imx7d_adc_analogue_clk[] = अणु
	IMX7D_ADC_ANALOGUE_CLK_CONFIG(4, IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_4),
	IMX7D_ADC_ANALOGUE_CLK_CONFIG(8, IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_8),
	IMX7D_ADC_ANALOGUE_CLK_CONFIG(16, IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_16),
	IMX7D_ADC_ANALOGUE_CLK_CONFIG(32, IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_32),
	IMX7D_ADC_ANALOGUE_CLK_CONFIG(64, IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_64),
	IMX7D_ADC_ANALOGUE_CLK_CONFIG(128, IMX7D_REG_ADC_TIMER_UNIT_PRE_DIV_128),
पूर्ण;

#घोषणा IMX7D_ADC_CHAN(_idx) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = (_idx),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
				BIT(IIO_CHAN_INFO_SAMP_FREQ),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec imx7d_adc_iio_channels[] = अणु
	IMX7D_ADC_CHAN(0),
	IMX7D_ADC_CHAN(1),
	IMX7D_ADC_CHAN(2),
	IMX7D_ADC_CHAN(3),
	IMX7D_ADC_CHAN(4),
	IMX7D_ADC_CHAN(5),
	IMX7D_ADC_CHAN(6),
	IMX7D_ADC_CHAN(7),
	IMX7D_ADC_CHAN(8),
	IMX7D_ADC_CHAN(9),
	IMX7D_ADC_CHAN(10),
	IMX7D_ADC_CHAN(11),
	IMX7D_ADC_CHAN(12),
	IMX7D_ADC_CHAN(13),
	IMX7D_ADC_CHAN(14),
	IMX7D_ADC_CHAN(15),
पूर्ण;

अटल स्थिर u32 imx7d_adc_average_num[] = अणु
	IMX7D_REG_ADC_CH_CFG2_AVG_NUM_4,
	IMX7D_REG_ADC_CH_CFG2_AVG_NUM_8,
	IMX7D_REG_ADC_CH_CFG2_AVG_NUM_16,
	IMX7D_REG_ADC_CH_CFG2_AVG_NUM_32,
पूर्ण;

अटल व्योम imx7d_adc_feature_config(काष्ठा imx7d_adc *info)
अणु
	info->adc_feature.clk_pre_भाग = IMX7D_ADC_ANALOG_CLK_PRE_DIV_4;
	info->adc_feature.avg_num = IMX7D_ADC_AVERAGE_NUM_32;
	info->adc_feature.core_समय_unit = 1;
पूर्ण

अटल व्योम imx7d_adc_sample_rate_set(काष्ठा imx7d_adc *info)
अणु
	काष्ठा imx7d_adc_feature *adc_feature = &info->adc_feature;
	काष्ठा imx7d_adc_analogue_core_clk adc_analogure_clk;
	u32 i;
	u32 पंचांगp_cfg1;
	u32 sample_rate = 0;

	/*
	 * Beक्रमe sample set, disable channel A,B,C,D. Here we
	 * clear the bit 31 of रेजिस्टर REG_ADC_CH_A\B\C\D_CFG1.
	 */
	क्रम (i = 0; i < 4; i++) अणु
		पंचांगp_cfg1 =
			पढ़ोl(info->regs + i * IMX7D_EACH_CHANNEL_REG_OFFSET);
		पंचांगp_cfg1 &= ~IMX7D_REG_ADC_CH_CFG1_CHANNEL_EN;
		ग_लिखोl(पंचांगp_cfg1,
		       info->regs + i * IMX7D_EACH_CHANNEL_REG_OFFSET);
	पूर्ण

	adc_analogure_clk = imx7d_adc_analogue_clk[adc_feature->clk_pre_भाग];
	sample_rate |= adc_analogure_clk.reg_config;
	info->pre_भाग_num = adc_analogure_clk.pre_भाग;

	sample_rate |= adc_feature->core_समय_unit;
	ग_लिखोl(sample_rate, info->regs + IMX7D_REG_ADC_TIMER_UNIT);
पूर्ण

अटल व्योम imx7d_adc_hw_init(काष्ठा imx7d_adc *info)
अणु
	u32 cfg;

	/* घातer up and enable adc analogue core */
	cfg = पढ़ोl(info->regs + IMX7D_REG_ADC_ADC_CFG);
	cfg &= ~(IMX7D_REG_ADC_ADC_CFG_ADC_CLK_DOWN |
		 IMX7D_REG_ADC_ADC_CFG_ADC_POWER_DOWN);
	cfg |= IMX7D_REG_ADC_ADC_CFG_ADC_EN;
	ग_लिखोl(cfg, info->regs + IMX7D_REG_ADC_ADC_CFG);

	/* enable channel A,B,C,D पूर्णांकerrupt */
	ग_लिखोl(IMX7D_REG_ADC_INT_CHANNEL_INT_EN,
	       info->regs + IMX7D_REG_ADC_INT_SIG_EN);
	ग_लिखोl(IMX7D_REG_ADC_INT_CHANNEL_INT_EN,
	       info->regs + IMX7D_REG_ADC_INT_EN);

	imx7d_adc_sample_rate_set(info);
पूर्ण

अटल व्योम imx7d_adc_channel_set(काष्ठा imx7d_adc *info)
अणु
	u32 cfg1 = 0;
	u32 cfg2;
	u32 channel;

	channel = info->channel;

	/* the channel choose single conversion, and enable average mode */
	cfg1 |= (IMX7D_REG_ADC_CH_CFG1_CHANNEL_EN |
		 IMX7D_REG_ADC_CH_CFG1_CHANNEL_SINGLE |
		 IMX7D_REG_ADC_CH_CFG1_CHANNEL_AVG_EN);

	/*
	 * physical channel 0 chose logical channel A
	 * physical channel 1 chose logical channel B
	 * physical channel 2 chose logical channel C
	 * physical channel 3 chose logical channel D
	 */
	cfg1 |= IMX7D_REG_ADC_CH_CFG1_CHANNEL_SEL(channel);

	/*
	 * पढ़ो रेजिस्टर REG_ADC_CH_A\B\C\D_CFG2, according to the
	 * channel chosen
	 */
	cfg2 = पढ़ोl(info->regs + IMX7D_EACH_CHANNEL_REG_OFFSET * channel +
		     IMX7D_REG_ADC_CHANNEL_CFG2_BASE);

	cfg2 |= imx7d_adc_average_num[info->adc_feature.avg_num];

	/*
	 * ग_लिखो the रेजिस्टर REG_ADC_CH_A\B\C\D_CFG2, according to
	 * the channel chosen
	 */
	ग_लिखोl(cfg2, info->regs + IMX7D_EACH_CHANNEL_REG_OFFSET * channel +
	       IMX7D_REG_ADC_CHANNEL_CFG2_BASE);
	ग_लिखोl(cfg1, info->regs + IMX7D_EACH_CHANNEL_REG_OFFSET * channel);
पूर्ण

अटल u32 imx7d_adc_get_sample_rate(काष्ठा imx7d_adc *info)
अणु
	u32 analogue_core_clk;
	u32 core_समय_unit = info->adc_feature.core_समय_unit;
	u32 पंचांगp;

	analogue_core_clk = IMX7D_ADC_INPUT_CLK / info->pre_भाग_num;
	पंचांगp = (core_समय_unit + 1) * 6;

	वापस analogue_core_clk / पंचांगp;
पूर्ण

अटल पूर्णांक imx7d_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val,
			पूर्णांक *val2,
			दीर्घ mask)
अणु
	काष्ठा imx7d_adc *info = iio_priv(indio_dev);

	u32 channel;
	दीर्घ ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&indio_dev->mlock);
		reinit_completion(&info->completion);

		channel = chan->channel & 0x03;
		info->channel = channel;
		imx7d_adc_channel_set(info);

		ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout
				(&info->completion, IMX7D_ADC_TIMEOUT);
		अगर (ret == 0) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (ret < 0) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस ret;
		पूर्ण

		*val = info->value;
		mutex_unlock(&indio_dev->mlock);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		info->vref_uv = regulator_get_voltage(info->vref);
		*val = info->vref_uv / 1000;
		*val2 = 12;
		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = imx7d_adc_get_sample_rate(info);
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक imx7d_adc_पढ़ो_data(काष्ठा imx7d_adc *info)
अणु
	u32 channel;
	u32 value;

	channel = info->channel & 0x03;

	/*
	 * channel A and B conversion result share one रेजिस्टर,
	 * bit[27~16] is the channel B conversion result,
	 * bit[11~0] is the channel A conversion result.
	 * channel C and D is the same.
	 */
	अगर (channel < 2)
		value = पढ़ोl(info->regs + IMX7D_REG_ADC_CHA_B_CNV_RSLT);
	अन्यथा
		value = पढ़ोl(info->regs + IMX7D_REG_ADC_CHC_D_CNV_RSLT);
	अगर (channel & 0x1)	/* channel B or D */
		value = (value >> 16) & 0xFFF;
	अन्यथा			/* channel A or C */
		value &= 0xFFF;

	वापस value;
पूर्ण

अटल irqवापस_t imx7d_adc_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imx7d_adc *info = dev_id;
	पूर्णांक status;

	status = पढ़ोl(info->regs + IMX7D_REG_ADC_INT_STATUS);
	अगर (status & IMX7D_REG_ADC_INT_STATUS_CHANNEL_INT_STATUS) अणु
		info->value = imx7d_adc_पढ़ो_data(info);
		complete(&info->completion);

		/*
		 * The रेजिस्टर IMX7D_REG_ADC_INT_STATUS can't clear
		 * itself after पढ़ो operation, need software to ग_लिखो
		 * 0 to the related bit. Here we clear the channel A/B/C/D
		 * conversion finished flag.
		 */
		status &= ~IMX7D_REG_ADC_INT_STATUS_CHANNEL_INT_STATUS;
		ग_लिखोl(status, info->regs + IMX7D_REG_ADC_INT_STATUS);
	पूर्ण

	/*
	 * If the channel A/B/C/D conversion समयout, report it and clear these
	 * समयout flags.
	 */
	अगर (status & IMX7D_REG_ADC_INT_STATUS_CHANNEL_CONV_TIME_OUT) अणु
		dev_err(info->dev,
			"ADC got conversion time out interrupt: 0x%08x\n",
			status);
		status &= ~IMX7D_REG_ADC_INT_STATUS_CHANNEL_CONV_TIME_OUT;
		ग_लिखोl(status, info->regs + IMX7D_REG_ADC_INT_STATUS);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक imx7d_adc_reg_access(काष्ठा iio_dev *indio_dev,
			अचिन्हित reg, अचिन्हित ग_लिखोval,
			अचिन्हित *पढ़ोval)
अणु
	काष्ठा imx7d_adc *info = iio_priv(indio_dev);

	अगर (!पढ़ोval || reg % 4 || reg > IMX7D_REG_ADC_ADC_CFG)
		वापस -EINVAL;

	*पढ़ोval = पढ़ोl(info->regs + reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info imx7d_adc_iio_info = अणु
	.पढ़ो_raw = &imx7d_adc_पढ़ो_raw,
	.debugfs_reg_access = &imx7d_adc_reg_access,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx7d_adc_match[] = अणु
	अणु .compatible = "fsl,imx7d-adc", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx7d_adc_match);

अटल व्योम imx7d_adc_घातer_करोwn(काष्ठा imx7d_adc *info)
अणु
	u32 adc_cfg;

	adc_cfg = पढ़ोl(info->regs + IMX7D_REG_ADC_ADC_CFG);
	adc_cfg |= IMX7D_REG_ADC_ADC_CFG_ADC_CLK_DOWN |
		   IMX7D_REG_ADC_ADC_CFG_ADC_POWER_DOWN;
	adc_cfg &= ~IMX7D_REG_ADC_ADC_CFG_ADC_EN;
	ग_लिखोl(adc_cfg, info->regs + IMX7D_REG_ADC_ADC_CFG);
पूर्ण

अटल पूर्णांक imx7d_adc_enable(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा imx7d_adc *info = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(info->vref);
	अगर (ret) अणु
		dev_err(info->dev,
			"Can't enable adc reference top voltage, err = %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(info->clk);
	अगर (ret) अणु
		dev_err(info->dev,
			"Could not prepare or enable clock.\n");
		regulator_disable(info->vref);
		वापस ret;
	पूर्ण

	imx7d_adc_hw_init(info);

	वापस 0;
पूर्ण

अटल पूर्णांक imx7d_adc_disable(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा imx7d_adc *info = iio_priv(indio_dev);

	imx7d_adc_घातer_करोwn(info);

	clk_disable_unprepare(info->clk);
	regulator_disable(info->vref);

	वापस 0;
पूर्ण

अटल व्योम __imx7d_adc_disable(व्योम *data)
अणु
	imx7d_adc_disable(data);
पूर्ण

अटल पूर्णांक imx7d_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx7d_adc *info;
	काष्ठा iio_dev *indio_dev;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*info));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "Failed allocating iio device\n");
		वापस -ENOMEM;
	पूर्ण

	info = iio_priv(indio_dev);
	info->dev = dev;

	info->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(info->regs))
		वापस PTR_ERR(info->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	info->clk = devm_clk_get(dev, "adc");
	अगर (IS_ERR(info->clk)) अणु
		ret = PTR_ERR(info->clk);
		dev_err(dev, "Failed getting clock, err = %d\n", ret);
		वापस ret;
	पूर्ण

	info->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(info->vref)) अणु
		ret = PTR_ERR(info->vref);
		dev_err(dev,
			"Failed getting reference voltage, err = %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, indio_dev);

	init_completion(&info->completion);

	indio_dev->name = dev_name(dev);
	indio_dev->info = &imx7d_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = imx7d_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(imx7d_adc_iio_channels);

	ret = devm_request_irq(dev, irq, imx7d_adc_isr, 0, dev_name(dev), info);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed requesting irq, irq = %d\n", irq);
		वापस ret;
	पूर्ण

	imx7d_adc_feature_config(info);

	ret = imx7d_adc_enable(&indio_dev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, __imx7d_adc_disable,
				       &indio_dev->dev);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(dev, indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't register the device.\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx7d_adc_pm_ops, imx7d_adc_disable, imx7d_adc_enable);

अटल काष्ठा platक्रमm_driver imx7d_adc_driver = अणु
	.probe		= imx7d_adc_probe,
	.driver		= अणु
		.name	= "imx7d_adc",
		.of_match_table = imx7d_adc_match,
		.pm	= &imx7d_adc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(imx7d_adc_driver);

MODULE_AUTHOR("Haibo Chen <haibo.chen@freescale.com>");
MODULE_DESCRIPTION("Freescale IMX7D ADC driver");
MODULE_LICENSE("GPL v2");
