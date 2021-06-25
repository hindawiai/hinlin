<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2016 Broadcom
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/iio/iपन.स>

/* Below Register's are common to IPROC ADC and Touchscreen IP */
#घोषणा IPROC_REGCTL1			0x00
#घोषणा IPROC_REGCTL2			0x04
#घोषणा IPROC_INTERRUPT_THRES		0x08
#घोषणा IPROC_INTERRUPT_MASK		0x0c
#घोषणा IPROC_INTERRUPT_STATUS		0x10
#घोषणा IPROC_ANALOG_CONTROL		0x1c
#घोषणा IPROC_CONTROLLER_STATUS		0x14
#घोषणा IPROC_AUX_DATA			0x20
#घोषणा IPROC_SOFT_BYPASS_CONTROL	0x38
#घोषणा IPROC_SOFT_BYPASS_DATA		0x3C

/* IPROC ADC Channel रेजिस्टर offsets */
#घोषणा IPROC_ADC_CHANNEL_REGCTL1		0x800
#घोषणा IPROC_ADC_CHANNEL_REGCTL2		0x804
#घोषणा IPROC_ADC_CHANNEL_STATUS		0x808
#घोषणा IPROC_ADC_CHANNEL_INTERRUPT_STATUS	0x80c
#घोषणा IPROC_ADC_CHANNEL_INTERRUPT_MASK	0x810
#घोषणा IPROC_ADC_CHANNEL_DATA			0x814
#घोषणा IPROC_ADC_CHANNEL_OFFSET		0x20

/* Bit definitions क्रम IPROC_REGCTL2 */
#घोषणा IPROC_ADC_AUXIN_SCAN_ENA	BIT(0)
#घोषणा IPROC_ADC_PWR_LDO		BIT(5)
#घोषणा IPROC_ADC_PWR_ADC		BIT(4)
#घोषणा IPROC_ADC_PWR_BG		BIT(3)
#घोषणा IPROC_ADC_CONTROLLER_EN		BIT(17)

/* Bit definitions क्रम IPROC_INTERRUPT_MASK and IPROC_INTERRUPT_STATUS */
#घोषणा IPROC_ADC_AUXDATA_RDY_INTR	BIT(3)
#घोषणा IPROC_ADC_INTR			9
#घोषणा IPROC_ADC_INTR_MASK		(0xFF << IPROC_ADC_INTR)

/* Bit definitions क्रम IPROC_ANALOG_CONTROL */
#घोषणा IPROC_ADC_CHANNEL_SEL		11
#घोषणा IPROC_ADC_CHANNEL_SEL_MASK	(0x7 << IPROC_ADC_CHANNEL_SEL)

/* Bit definitions क्रम IPROC_ADC_CHANNEL_REGCTL1 */
#घोषणा IPROC_ADC_CHANNEL_ROUNDS	0x2
#घोषणा IPROC_ADC_CHANNEL_ROUNDS_MASK	(0x3F << IPROC_ADC_CHANNEL_ROUNDS)
#घोषणा IPROC_ADC_CHANNEL_MODE		0x1
#घोषणा IPROC_ADC_CHANNEL_MODE_MASK	(0x1 << IPROC_ADC_CHANNEL_MODE)
#घोषणा IPROC_ADC_CHANNEL_MODE_TDM	0x1
#घोषणा IPROC_ADC_CHANNEL_MODE_SNAPSHOT 0x0
#घोषणा IPROC_ADC_CHANNEL_ENABLE	0x0
#घोषणा IPROC_ADC_CHANNEL_ENABLE_MASK	0x1

/* Bit definitions क्रम IPROC_ADC_CHANNEL_REGCTL2 */
#घोषणा IPROC_ADC_CHANNEL_WATERMARK	0x0
#घोषणा IPROC_ADC_CHANNEL_WATERMARK_MASK \
		(0x3F << IPROC_ADC_CHANNEL_WATERMARK)

#घोषणा IPROC_ADC_WATER_MARK_LEVEL	0x1

/* Bit definitions क्रम IPROC_ADC_CHANNEL_STATUS */
#घोषणा IPROC_ADC_CHANNEL_DATA_LOST		0x0
#घोषणा IPROC_ADC_CHANNEL_DATA_LOST_MASK	\
		(0x0 << IPROC_ADC_CHANNEL_DATA_LOST)
#घोषणा IPROC_ADC_CHANNEL_VALID_ENTERIES	0x1
#घोषणा IPROC_ADC_CHANNEL_VALID_ENTERIES_MASK	\
		(0xFF << IPROC_ADC_CHANNEL_VALID_ENTERIES)
#घोषणा IPROC_ADC_CHANNEL_TOTAL_ENTERIES	0x9
#घोषणा IPROC_ADC_CHANNEL_TOTAL_ENTERIES_MASK	\
		(0xFF << IPROC_ADC_CHANNEL_TOTAL_ENTERIES)

/* Bit definitions क्रम IPROC_ADC_CHANNEL_INTERRUPT_MASK */
#घोषणा IPROC_ADC_CHANNEL_WTRMRK_INTR			0x0
#घोषणा IPROC_ADC_CHANNEL_WTRMRK_INTR_MASK		\
		(0x1 << IPROC_ADC_CHANNEL_WTRMRK_INTR)
#घोषणा IPROC_ADC_CHANNEL_FULL_INTR			0x1
#घोषणा IPROC_ADC_CHANNEL_FULL_INTR_MASK		\
		(0x1 << IPROC_ADC_IPROC_ADC_CHANNEL_FULL_INTR)
#घोषणा IPROC_ADC_CHANNEL_EMPTY_INTR			0x2
#घोषणा IPROC_ADC_CHANNEL_EMPTY_INTR_MASK		\
		(0x1 << IPROC_ADC_CHANNEL_EMPTY_INTR)

#घोषणा IPROC_ADC_WATER_MARK_INTR_ENABLE		0x1

/* Number of समय to retry a set of the पूर्णांकerrupt mask reg */
#घोषणा IPROC_ADC_INTMASK_RETRY_ATTEMPTS		10

#घोषणा IPROC_ADC_READ_TIMEOUT        (HZ*2)

#घोषणा iproc_adc_dbg_reg(dev, priv, reg) \
करो अणु \
	u32 val; \
	regmap_पढ़ो(priv->regmap, reg, &val); \
	dev_dbg(dev, "%20s= 0x%08x\n", #reg, val); \
पूर्ण जबतक (0)

काष्ठा iproc_adc_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा clk *adc_clk;
	काष्ठा mutex mutex;
	पूर्णांक  irqno;
	पूर्णांक chan_val;
	पूर्णांक chan_id;
	काष्ठा completion completion;
पूर्ण;

अटल व्योम iproc_adc_reg_dump(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा device *dev = &indio_dev->dev;
	काष्ठा iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	iproc_adc_dbg_reg(dev, adc_priv, IPROC_REGCTL1);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_REGCTL2);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_INTERRUPT_THRES);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_INTERRUPT_MASK);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_INTERRUPT_STATUS);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_CONTROLLER_STATUS);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_ANALOG_CONTROL);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_AUX_DATA);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_SOFT_BYPASS_CONTROL);
	iproc_adc_dbg_reg(dev, adc_priv, IPROC_SOFT_BYPASS_DATA);
पूर्ण

अटल irqवापस_t iproc_adc_पूर्णांकerrupt_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	u32 channel_पूर्णांकr_status;
	u32 पूर्णांकr_status;
	u32 पूर्णांकr_mask;
	काष्ठा iio_dev *indio_dev = data;
	काष्ठा iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	/*
	 * This पूर्णांकerrupt is shared with the touchscreen driver.
	 * Make sure this पूर्णांकerrupt is पूर्णांकended क्रम us.
	 * Handle only ADC channel specअगरic पूर्णांकerrupts.
	 */
	regmap_पढ़ो(adc_priv->regmap, IPROC_INTERRUPT_STATUS, &पूर्णांकr_status);
	regmap_पढ़ो(adc_priv->regmap, IPROC_INTERRUPT_MASK, &पूर्णांकr_mask);
	पूर्णांकr_status = पूर्णांकr_status & पूर्णांकr_mask;
	channel_पूर्णांकr_status = (पूर्णांकr_status & IPROC_ADC_INTR_MASK) >>
				IPROC_ADC_INTR;
	अगर (channel_पूर्णांकr_status)
		वापस IRQ_WAKE_THREAD;

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t iproc_adc_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *data)
अणु
	irqवापस_t retval = IRQ_NONE;
	काष्ठा iproc_adc_priv *adc_priv;
	काष्ठा iio_dev *indio_dev = data;
	अचिन्हित पूर्णांक valid_entries;
	u32 पूर्णांकr_status;
	u32 पूर्णांकr_channels;
	u32 channel_status;
	u32 ch_पूर्णांकr_status;

	adc_priv = iio_priv(indio_dev);

	regmap_पढ़ो(adc_priv->regmap, IPROC_INTERRUPT_STATUS, &पूर्णांकr_status);
	dev_dbg(&indio_dev->dev, "iproc_adc_interrupt_handler(),INTRPT_STS:%x\n",
			पूर्णांकr_status);

	पूर्णांकr_channels = (पूर्णांकr_status & IPROC_ADC_INTR_MASK) >> IPROC_ADC_INTR;
	अगर (पूर्णांकr_channels) अणु
		regmap_पढ़ो(adc_priv->regmap,
			    IPROC_ADC_CHANNEL_INTERRUPT_STATUS +
			    IPROC_ADC_CHANNEL_OFFSET * adc_priv->chan_id,
			    &ch_पूर्णांकr_status);

		अगर (ch_पूर्णांकr_status & IPROC_ADC_CHANNEL_WTRMRK_INTR_MASK) अणु
			regmap_पढ़ो(adc_priv->regmap,
					IPROC_ADC_CHANNEL_STATUS +
					IPROC_ADC_CHANNEL_OFFSET *
					adc_priv->chan_id,
					&channel_status);

			valid_entries = ((channel_status &
				IPROC_ADC_CHANNEL_VALID_ENTERIES_MASK) >>
				IPROC_ADC_CHANNEL_VALID_ENTERIES);
			अगर (valid_entries >= 1) अणु
				regmap_पढ़ो(adc_priv->regmap,
					IPROC_ADC_CHANNEL_DATA +
					IPROC_ADC_CHANNEL_OFFSET *
					adc_priv->chan_id,
					&adc_priv->chan_val);
				complete(&adc_priv->completion);
			पूर्ण अन्यथा अणु
				dev_err(&indio_dev->dev,
					"No data rcvd on channel %d\n",
					adc_priv->chan_id);
			पूर्ण
			regmap_ग_लिखो(adc_priv->regmap,
					IPROC_ADC_CHANNEL_INTERRUPT_MASK +
					IPROC_ADC_CHANNEL_OFFSET *
					adc_priv->chan_id,
					(ch_पूर्णांकr_status &
					~(IPROC_ADC_CHANNEL_WTRMRK_INTR_MASK)));
		पूर्ण
		regmap_ग_लिखो(adc_priv->regmap,
				IPROC_ADC_CHANNEL_INTERRUPT_STATUS +
				IPROC_ADC_CHANNEL_OFFSET * adc_priv->chan_id,
				ch_पूर्णांकr_status);
		regmap_ग_लिखो(adc_priv->regmap, IPROC_INTERRUPT_STATUS,
				पूर्णांकr_channels);
		retval = IRQ_HANDLED;
	पूर्ण

	वापस retval;
पूर्ण

अटल पूर्णांक iproc_adc_करो_पढ़ो(काष्ठा iio_dev *indio_dev,
			   पूर्णांक channel,
			   u16 *p_adc_data)
अणु
	पूर्णांक पढ़ो_len = 0;
	u32 val;
	u32 mask;
	u32 val_check;
	पूर्णांक failed_cnt = 0;
	काष्ठा iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	mutex_lock(&adc_priv->mutex);

	/*
	 * After a पढ़ो is complete the ADC पूर्णांकerrupts will be disabled so
	 * we can assume this section of code is safe from पूर्णांकerrupts.
	 */
	adc_priv->chan_val = -1;
	adc_priv->chan_id = channel;

	reinit_completion(&adc_priv->completion);
	/* Clear any pending पूर्णांकerrupt */
	regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_STATUS,
			IPROC_ADC_INTR_MASK | IPROC_ADC_AUXDATA_RDY_INTR,
			((0x0 << channel) << IPROC_ADC_INTR) |
			IPROC_ADC_AUXDATA_RDY_INTR);

	/* Configure channel क्रम snapshot mode and enable  */
	val = (BIT(IPROC_ADC_CHANNEL_ROUNDS) |
		(IPROC_ADC_CHANNEL_MODE_SNAPSHOT << IPROC_ADC_CHANNEL_MODE) |
		(0x1 << IPROC_ADC_CHANNEL_ENABLE));

	mask = IPROC_ADC_CHANNEL_ROUNDS_MASK | IPROC_ADC_CHANNEL_MODE_MASK |
		IPROC_ADC_CHANNEL_ENABLE_MASK;
	regmap_update_bits(adc_priv->regmap, (IPROC_ADC_CHANNEL_REGCTL1 +
				IPROC_ADC_CHANNEL_OFFSET * channel),
				mask, val);

	/* Set the Watermark क्रम a channel */
	regmap_update_bits(adc_priv->regmap, (IPROC_ADC_CHANNEL_REGCTL2 +
					IPROC_ADC_CHANNEL_OFFSET * channel),
					IPROC_ADC_CHANNEL_WATERMARK_MASK,
					0x1);

	/* Enable water mark पूर्णांकerrupt */
	regmap_update_bits(adc_priv->regmap, (IPROC_ADC_CHANNEL_INTERRUPT_MASK +
					IPROC_ADC_CHANNEL_OFFSET *
					channel),
					IPROC_ADC_CHANNEL_WTRMRK_INTR_MASK,
					IPROC_ADC_WATER_MARK_INTR_ENABLE);
	regmap_पढ़ो(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val);

	/* Enable ADC पूर्णांकerrupt क्रम a channel */
	val |= (BIT(channel) << IPROC_ADC_INTR);
	regmap_ग_लिखो(adc_priv->regmap, IPROC_INTERRUPT_MASK, val);

	/*
	 * There seems to be a very rare issue where writing to this रेजिस्टर
	 * करोes not take effect.  To work around the issue we will try multiple
	 * ग_लिखोs.  In total we will spend about 10*10 = 100 us attempting this.
	 * Testing has shown that this may loop a few समय, but we have never
	 * hit the full count.
	 */
	regmap_पढ़ो(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val_check);
	जबतक (val_check != val) अणु
		failed_cnt++;

		अगर (failed_cnt > IPROC_ADC_INTMASK_RETRY_ATTEMPTS)
			अवरोध;

		udelay(10);
		regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_MASK,
				IPROC_ADC_INTR_MASK,
				((0x1 << channel) <<
				IPROC_ADC_INTR));

		regmap_पढ़ो(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val_check);
	पूर्ण

	अगर (failed_cnt) अणु
		dev_dbg(&indio_dev->dev,
			"IntMask failed (%d times)", failed_cnt);
		अगर (failed_cnt > IPROC_ADC_INTMASK_RETRY_ATTEMPTS) अणु
			dev_err(&indio_dev->dev,
				"IntMask set failed. Read will likely fail.");
			पढ़ो_len = -EIO;
			जाओ adc_err;
		पूर्ण
	पूर्ण
	regmap_पढ़ो(adc_priv->regmap, IPROC_INTERRUPT_MASK, &val_check);

	अगर (रुको_क्रम_completion_समयout(&adc_priv->completion,
		IPROC_ADC_READ_TIMEOUT) > 0) अणु

		/* Only the lower 16 bits are relevant */
		*p_adc_data = adc_priv->chan_val & 0xFFFF;
		पढ़ो_len = माप(*p_adc_data);

	पूर्ण अन्यथा अणु
		/*
		 * We never got the पूर्णांकerrupt, something went wrong.
		 * Perhaps the पूर्णांकerrupt may still be coming, we करो not want
		 * that now.  Lets disable the ADC पूर्णांकerrupt, and clear the
		 * status to put it back in to normal state.
		 */
		पढ़ो_len = -ETIMEDOUT;
		जाओ adc_err;
	पूर्ण
	mutex_unlock(&adc_priv->mutex);

	वापस पढ़ो_len;

adc_err:
	regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_MASK,
			   IPROC_ADC_INTR_MASK,
			   ((0x0 << channel) << IPROC_ADC_INTR));

	regmap_update_bits(adc_priv->regmap, IPROC_INTERRUPT_STATUS,
			   IPROC_ADC_INTR_MASK,
			   ((0x0 << channel) << IPROC_ADC_INTR));

	dev_err(&indio_dev->dev, "Timed out waiting for ADC data!\n");
	iproc_adc_reg_dump(indio_dev);
	mutex_unlock(&adc_priv->mutex);

	वापस पढ़ो_len;
पूर्ण

अटल पूर्णांक iproc_adc_enable(काष्ठा iio_dev *indio_dev)
अणु
	u32 val;
	u32 channel_id;
	काष्ठा iproc_adc_priv *adc_priv = iio_priv(indio_dev);
	पूर्णांक ret;

	/* Set i_amux = 3b'000, select channel 0 */
	ret = regmap_update_bits(adc_priv->regmap, IPROC_ANALOG_CONTROL,
				IPROC_ADC_CHANNEL_SEL_MASK, 0);
	अगर (ret) अणु
		dev_err(&indio_dev->dev,
			"failed to write IPROC_ANALOG_CONTROL %d\n", ret);
		वापस ret;
	पूर्ण
	adc_priv->chan_val = -1;

	/*
	 * PWR up LDO, ADC, and Band Gap (0 to enable)
	 * Also enable ADC controller (set high)
	 */
	ret = regmap_पढ़ो(adc_priv->regmap, IPROC_REGCTL2, &val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev,
			"failed to read IPROC_REGCTL2 %d\n", ret);
		वापस ret;
	पूर्ण

	val &= ~(IPROC_ADC_PWR_LDO | IPROC_ADC_PWR_ADC | IPROC_ADC_PWR_BG);

	ret = regmap_ग_लिखो(adc_priv->regmap, IPROC_REGCTL2, val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev,
			"failed to write IPROC_REGCTL2 %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(adc_priv->regmap, IPROC_REGCTL2, &val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev,
			"failed to read IPROC_REGCTL2 %d\n", ret);
		वापस ret;
	पूर्ण

	val |= IPROC_ADC_CONTROLLER_EN;
	ret = regmap_ग_लिखो(adc_priv->regmap, IPROC_REGCTL2, val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev,
			"failed to write IPROC_REGCTL2 %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (channel_id = 0; channel_id < indio_dev->num_channels;
		channel_id++) अणु
		ret = regmap_ग_लिखो(adc_priv->regmap,
				IPROC_ADC_CHANNEL_INTERRUPT_MASK +
				IPROC_ADC_CHANNEL_OFFSET * channel_id, 0);
		अगर (ret) अणु
			dev_err(&indio_dev->dev,
			    "failed to write ADC_CHANNEL_INTERRUPT_MASK %d\n",
			    ret);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(adc_priv->regmap,
				IPROC_ADC_CHANNEL_INTERRUPT_STATUS +
				IPROC_ADC_CHANNEL_OFFSET * channel_id, 0);
		अगर (ret) अणु
			dev_err(&indio_dev->dev,
			    "failed to write ADC_CHANNEL_INTERRUPT_STATUS %d\n",
			    ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम iproc_adc_disable(काष्ठा iio_dev *indio_dev)
अणु
	u32 val;
	पूर्णांक ret;
	काष्ठा iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	ret = regmap_पढ़ो(adc_priv->regmap, IPROC_REGCTL2, &val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev,
			"failed to read IPROC_REGCTL2 %d\n", ret);
		वापस;
	पूर्ण

	val &= ~IPROC_ADC_CONTROLLER_EN;
	ret = regmap_ग_लिखो(adc_priv->regmap, IPROC_REGCTL2, val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev,
			"failed to write IPROC_REGCTL2 %d\n", ret);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक iproc_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val,
			  पूर्णांक *val2,
			  दीर्घ mask)
अणु
	u16 adc_data;
	पूर्णांक err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		err =  iproc_adc_करो_पढ़ो(indio_dev, chan->channel, &adc_data);
		अगर (err < 0)
			वापस err;
		*val = adc_data;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			*val = 1800;
			*val2 = 10;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info iproc_adc_iio_info = अणु
	.पढ़ो_raw = &iproc_adc_पढ़ो_raw,
पूर्ण;

#घोषणा IPROC_ADC_CHANNEL(_index, _id) अणु                \
	.type = IIO_VOLTAGE,                            \
	.indexed = 1,                                   \
	.channel = _index,                              \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),   \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.datasheet_name = _id,                          \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec iproc_adc_iio_channels[] = अणु
	IPROC_ADC_CHANNEL(0, "adc0"),
	IPROC_ADC_CHANNEL(1, "adc1"),
	IPROC_ADC_CHANNEL(2, "adc2"),
	IPROC_ADC_CHANNEL(3, "adc3"),
	IPROC_ADC_CHANNEL(4, "adc4"),
	IPROC_ADC_CHANNEL(5, "adc5"),
	IPROC_ADC_CHANNEL(6, "adc6"),
	IPROC_ADC_CHANNEL(7, "adc7"),
पूर्ण;

अटल पूर्णांक iproc_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_adc_priv *adc_priv;
	काष्ठा iio_dev *indio_dev = शून्य;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev,
					माप(*adc_priv));
	अगर (!indio_dev) अणु
		dev_err(&pdev->dev, "failed to allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	adc_priv = iio_priv(indio_dev);
	platक्रमm_set_drvdata(pdev, indio_dev);

	mutex_init(&adc_priv->mutex);

	init_completion(&adc_priv->completion);

	adc_priv->regmap = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
			   "adc-syscon");
	अगर (IS_ERR(adc_priv->regmap)) अणु
		dev_err(&pdev->dev, "failed to get handle for tsc syscon\n");
		ret = PTR_ERR(adc_priv->regmap);
		वापस ret;
	पूर्ण

	adc_priv->adc_clk = devm_clk_get(&pdev->dev, "tsc_clk");
	अगर (IS_ERR(adc_priv->adc_clk)) अणु
		dev_err(&pdev->dev,
			"failed getting clock tsc_clk\n");
		ret = PTR_ERR(adc_priv->adc_clk);
		वापस ret;
	पूर्ण

	adc_priv->irqno = platक्रमm_get_irq(pdev, 0);
	अगर (adc_priv->irqno <= 0)
		वापस -ENODEV;

	ret = regmap_update_bits(adc_priv->regmap, IPROC_REGCTL2,
				IPROC_ADC_AUXIN_SCAN_ENA, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to write IPROC_REGCTL2 %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, adc_priv->irqno,
				iproc_adc_पूर्णांकerrupt_handler,
				iproc_adc_पूर्णांकerrupt_thपढ़ो,
				IRQF_SHARED, "iproc-adc", indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request_irq error %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(adc_priv->adc_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"clk_prepare_enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iproc_adc_enable(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable adc %d\n", ret);
		जाओ err_adc_enable;
	पूर्ण

	indio_dev->name = "iproc-static-adc";
	indio_dev->info = &iproc_adc_iio_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = iproc_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(iproc_adc_iio_channels);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "iio_device_register failed:err %d\n", ret);
		जाओ err_clk;
	पूर्ण

	वापस 0;

err_clk:
	iproc_adc_disable(indio_dev);
err_adc_enable:
	clk_disable_unprepare(adc_priv->adc_clk);

	वापस ret;
पूर्ण

अटल पूर्णांक iproc_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा iproc_adc_priv *adc_priv = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iproc_adc_disable(indio_dev);
	clk_disable_unprepare(adc_priv->adc_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id iproc_adc_of_match[] = अणु
	अणु.compatible = "brcm,iproc-static-adc", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, iproc_adc_of_match);

अटल काष्ठा platक्रमm_driver iproc_adc_driver = अणु
	.probe  = iproc_adc_probe,
	.हटाओ	= iproc_adc_हटाओ,
	.driver	= अणु
		.name	= "iproc-static-adc",
		.of_match_table = iproc_adc_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(iproc_adc_driver);

MODULE_DESCRIPTION("Broadcom iProc ADC controller driver");
MODULE_AUTHOR("Raveendra Padasalagi <raveendra.padasalagi@broadcom.com>");
MODULE_LICENSE("GPL v2");
