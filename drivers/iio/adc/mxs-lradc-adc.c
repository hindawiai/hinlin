<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Freescale MXS LRADC ADC driver
 *
 * Copyright (c) 2012 DENX Software Engineering, GmbH.
 * Copyright (c) 2017 Ksenija Stanojevic <ksenija.stanojevic@gmail.com>
 *
 * Authors:
 *  Marek Vasut <marex@denx.de>
 *  Ksenija Stanojevic <ksenija.stanojevic@gmail.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/mxs-lradc.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/sysfs.h>

/*
 * Make this runसमय configurable अगर necessary. Currently, अगर the buffered mode
 * is enabled, the LRADC takes LRADC_DELAY_TIMER_LOOP samples of data beक्रमe
 * triggering IRQ. The sampling happens every (LRADC_DELAY_TIMER_PER / 2000)
 * seconds. The result is that the samples arrive every 500mS.
 */
#घोषणा LRADC_DELAY_TIMER_PER	200
#घोषणा LRADC_DELAY_TIMER_LOOP	5

#घोषणा VREF_MV_BASE 1850

अटल स्थिर अक्षर *mx23_lradc_adc_irq_names[] = अणु
	"mxs-lradc-channel0",
	"mxs-lradc-channel1",
	"mxs-lradc-channel2",
	"mxs-lradc-channel3",
	"mxs-lradc-channel4",
	"mxs-lradc-channel5",
पूर्ण;

अटल स्थिर अक्षर *mx28_lradc_adc_irq_names[] = अणु
	"mxs-lradc-thresh0",
	"mxs-lradc-thresh1",
	"mxs-lradc-channel0",
	"mxs-lradc-channel1",
	"mxs-lradc-channel2",
	"mxs-lradc-channel3",
	"mxs-lradc-channel4",
	"mxs-lradc-channel5",
	"mxs-lradc-button0",
	"mxs-lradc-button1",
पूर्ण;

अटल स्थिर u32 mxs_lradc_adc_vref_mv[][LRADC_MAX_TOTAL_CHANS] = अणु
	[IMX23_LRADC] = अणु
		VREF_MV_BASE,		/* CH0 */
		VREF_MV_BASE,		/* CH1 */
		VREF_MV_BASE,		/* CH2 */
		VREF_MV_BASE,		/* CH3 */
		VREF_MV_BASE,		/* CH4 */
		VREF_MV_BASE,		/* CH5 */
		VREF_MV_BASE * 2,	/* CH6 VDDIO */
		VREF_MV_BASE * 4,	/* CH7 VBATT */
		VREF_MV_BASE,		/* CH8 Temp sense 0 */
		VREF_MV_BASE,		/* CH9 Temp sense 1 */
		VREF_MV_BASE,		/* CH10 */
		VREF_MV_BASE,		/* CH11 */
		VREF_MV_BASE,		/* CH12 USB_DP */
		VREF_MV_BASE,		/* CH13 USB_DN */
		VREF_MV_BASE,		/* CH14 VBG */
		VREF_MV_BASE * 4,	/* CH15 VDD5V */
	पूर्ण,
	[IMX28_LRADC] = अणु
		VREF_MV_BASE,		/* CH0 */
		VREF_MV_BASE,		/* CH1 */
		VREF_MV_BASE,		/* CH2 */
		VREF_MV_BASE,		/* CH3 */
		VREF_MV_BASE,		/* CH4 */
		VREF_MV_BASE,		/* CH5 */
		VREF_MV_BASE,		/* CH6 */
		VREF_MV_BASE * 4,	/* CH7 VBATT */
		VREF_MV_BASE,		/* CH8 Temp sense 0 */
		VREF_MV_BASE,		/* CH9 Temp sense 1 */
		VREF_MV_BASE * 2,	/* CH10 VDDIO */
		VREF_MV_BASE,		/* CH11 VTH */
		VREF_MV_BASE * 2,	/* CH12 VDDA */
		VREF_MV_BASE,		/* CH13 VDDD */
		VREF_MV_BASE,		/* CH14 VBG */
		VREF_MV_BASE * 4,	/* CH15 VDD5V */
	पूर्ण,
पूर्ण;

क्रमागत mxs_lradc_भागbytwo अणु
	MXS_LRADC_DIV_DISABLED = 0,
	MXS_LRADC_DIV_ENABLED,
पूर्ण;

काष्ठा mxs_lradc_scale अणु
	अचिन्हित पूर्णांक		पूर्णांकeger;
	अचिन्हित पूर्णांक		nano;
पूर्ण;

काष्ठा mxs_lradc_adc अणु
	काष्ठा mxs_lradc	*lradc;
	काष्ठा device		*dev;

	व्योम __iomem		*base;
	u32			buffer[10];
	काष्ठा iio_trigger	*trig;
	काष्ठा completion	completion;
	spinlock_t		lock;

	स्थिर u32		*vref_mv;
	काष्ठा mxs_lradc_scale	scale_avail[LRADC_MAX_TOTAL_CHANS][2];
	अचिन्हित दीर्घ		is_भागided;
पूर्ण;


/* Raw I/O operations */
अटल पूर्णांक mxs_lradc_adc_पढ़ो_single(काष्ठा iio_dev *iio_dev, पूर्णांक chan,
				     पूर्णांक *val)
अणु
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio_dev);
	काष्ठा mxs_lradc *lradc = adc->lradc;
	पूर्णांक ret;

	/*
	 * See अगर there is no buffered operation in progress. If there is simply
	 * bail out. This can be improved to support both buffered and raw IO at
	 * the same समय, yet the code becomes horribly complicated. Thereक्रमe I
	 * applied KISS principle here.
	 */
	ret = iio_device_claim_direct_mode(iio_dev);
	अगर (ret)
		वापस ret;

	reinit_completion(&adc->completion);

	/*
	 * No buffered operation in progress, map the channel and trigger it.
	 * Virtual channel 0 is always used here as the others are always not
	 * used अगर करोing raw sampling.
	 */
	अगर (lradc->soc == IMX28_LRADC)
		ग_लिखोl(LRADC_CTRL1_LRADC_IRQ_EN(0),
		       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(0x1, adc->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);

	/* Enable / disable the भागider per requirement */
	अगर (test_bit(chan, &adc->is_भागided))
		ग_लिखोl(1 << LRADC_CTRL2_DIVIDE_BY_TWO_OFFSET,
		       adc->base + LRADC_CTRL2 + STMP_OFFSET_REG_SET);
	अन्यथा
		ग_लिखोl(1 << LRADC_CTRL2_DIVIDE_BY_TWO_OFFSET,
		       adc->base + LRADC_CTRL2 + STMP_OFFSET_REG_CLR);

	/* Clean the slot's previous content, then set new one. */
	ग_लिखोl(LRADC_CTRL4_LRADCSELECT_MASK(0),
	       adc->base + LRADC_CTRL4 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(chan, adc->base + LRADC_CTRL4 + STMP_OFFSET_REG_SET);

	ग_लिखोl(0, adc->base + LRADC_CH(0));

	/* Enable the IRQ and start sampling the channel. */
	ग_लिखोl(LRADC_CTRL1_LRADC_IRQ_EN(0),
	       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
	ग_लिखोl(BIT(0), adc->base + LRADC_CTRL0 + STMP_OFFSET_REG_SET);

	/* Wait क्रम completion on the channel, 1 second max. */
	ret = रुको_क्रम_completion_समाप्तable_समयout(&adc->completion, HZ);
	अगर (!ret)
		ret = -ETIMEDOUT;
	अगर (ret < 0)
		जाओ err;

	/* Read the data. */
	*val = पढ़ोl(adc->base + LRADC_CH(0)) & LRADC_CH_VALUE_MASK;
	ret = IIO_VAL_INT;

err:
	ग_लिखोl(LRADC_CTRL1_LRADC_IRQ_EN(0),
	       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	iio_device_release_direct_mode(iio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_lradc_adc_पढ़ो_temp(काष्ठा iio_dev *iio_dev, पूर्णांक *val)
अणु
	पूर्णांक ret, min, max;

	ret = mxs_lradc_adc_पढ़ो_single(iio_dev, 8, &min);
	अगर (ret != IIO_VAL_INT)
		वापस ret;

	ret = mxs_lradc_adc_पढ़ो_single(iio_dev, 9, &max);
	अगर (ret != IIO_VAL_INT)
		वापस ret;

	*val = max - min;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक mxs_lradc_adc_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type == IIO_TEMP)
			वापस mxs_lradc_adc_पढ़ो_temp(iio_dev, val);

		वापस mxs_lradc_adc_पढ़ो_single(iio_dev, chan->channel, val);

	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_TEMP) अणु
			/*
			 * From the datasheet, we have to multiply by 1.012 and
			 * भागide by 4
			 */
			*val = 0;
			*val2 = 253000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण

		*val = adc->vref_mv[chan->channel];
		*val2 = chan->scan_type.realbits -
			test_bit(chan->channel, &adc->is_भागided);
		वापस IIO_VAL_FRACTIONAL_LOG2;

	हाल IIO_CHAN_INFO_OFFSET:
		अगर (chan->type == IIO_TEMP) अणु
			/*
			 * The calculated value from the ADC is in Kelvin, we
			 * want Celsius क्रम hwmon so the offset is -273.15
			 * The offset is applied beक्रमe scaling so it is
			 * actually -213.15 * 4 / 1.012 = -1079.644268
			 */
			*val = -1079;
			*val2 = 644268;

			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण

		वापस -EINVAL;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mxs_lradc_adc_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   पूर्णांक val, पूर्णांक val2, दीर्घ m)
अणु
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio_dev);
	काष्ठा mxs_lradc_scale *scale_avail =
			adc->scale_avail[chan->channel];
	पूर्णांक ret;

	ret = iio_device_claim_direct_mode(iio_dev);
	अगर (ret)
		वापस ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		ret = -EINVAL;
		अगर (val == scale_avail[MXS_LRADC_DIV_DISABLED].पूर्णांकeger &&
		    val2 == scale_avail[MXS_LRADC_DIV_DISABLED].nano) अणु
			/* भागider by two disabled */
			clear_bit(chan->channel, &adc->is_भागided);
			ret = 0;
		पूर्ण अन्यथा अगर (val == scale_avail[MXS_LRADC_DIV_ENABLED].पूर्णांकeger &&
			   val2 == scale_avail[MXS_LRADC_DIV_ENABLED].nano) अणु
			/* भागider by two enabled */
			set_bit(chan->channel, &adc->is_भागided);
			ret = 0;
		पूर्ण

		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	iio_device_release_direct_mode(iio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mxs_lradc_adc_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *iio_dev,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   दीर्घ m)
अणु
	वापस IIO_VAL_INT_PLUS_न_अंकO;
पूर्ण

अटल sमाप_प्रकार mxs_lradc_adc_show_scale_avail(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा iio_dev *iio = dev_to_iio_dev(dev);
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);
	काष्ठा iio_dev_attr *iio_attr = to_iio_dev_attr(attr);
	पूर्णांक i, ch, len = 0;

	ch = iio_attr->address;
	क्रम (i = 0; i < ARRAY_SIZE(adc->scale_avail[ch]); i++)
		len += प्र_लिखो(buf + len, "%u.%09u ",
			       adc->scale_avail[ch][i].पूर्णांकeger,
			       adc->scale_avail[ch][i].nano);

	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

#घोषणा SHOW_SCALE_AVAILABLE_ATTR(ch)\
	IIO_DEVICE_ATTR(in_voltage##ch##_scale_available, 0444,\
			mxs_lradc_adc_show_scale_avail, शून्य, ch)

अटल SHOW_SCALE_AVAILABLE_ATTR(0);
अटल SHOW_SCALE_AVAILABLE_ATTR(1);
अटल SHOW_SCALE_AVAILABLE_ATTR(2);
अटल SHOW_SCALE_AVAILABLE_ATTR(3);
अटल SHOW_SCALE_AVAILABLE_ATTR(4);
अटल SHOW_SCALE_AVAILABLE_ATTR(5);
अटल SHOW_SCALE_AVAILABLE_ATTR(6);
अटल SHOW_SCALE_AVAILABLE_ATTR(7);
अटल SHOW_SCALE_AVAILABLE_ATTR(10);
अटल SHOW_SCALE_AVAILABLE_ATTR(11);
अटल SHOW_SCALE_AVAILABLE_ATTR(12);
अटल SHOW_SCALE_AVAILABLE_ATTR(13);
अटल SHOW_SCALE_AVAILABLE_ATTR(14);
अटल SHOW_SCALE_AVAILABLE_ATTR(15);

अटल काष्ठा attribute *mxs_lradc_adc_attributes[] = अणु
	&iio_dev_attr_in_voltage0_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage1_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage2_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage3_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage4_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage5_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage6_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage7_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage10_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage11_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage12_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage13_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage14_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage15_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mxs_lradc_adc_attribute_group = अणु
	.attrs = mxs_lradc_adc_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info mxs_lradc_adc_iio_info = अणु
	.पढ़ो_raw		= mxs_lradc_adc_पढ़ो_raw,
	.ग_लिखो_raw		= mxs_lradc_adc_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt	= mxs_lradc_adc_ग_लिखो_raw_get_fmt,
	.attrs			= &mxs_lradc_adc_attribute_group,
पूर्ण;

/* IRQ Handling */
अटल irqवापस_t mxs_lradc_adc_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा iio_dev *iio = data;
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);
	काष्ठा mxs_lradc *lradc = adc->lradc;
	अचिन्हित दीर्घ reg = पढ़ोl(adc->base + LRADC_CTRL1);
	अचिन्हित दीर्घ flags;

	अगर (!(reg & mxs_lradc_irq_mask(lradc)))
		वापस IRQ_NONE;

	अगर (iio_buffer_enabled(iio)) अणु
		अगर (reg & lradc->buffer_vchans) अणु
			spin_lock_irqsave(&adc->lock, flags);
			iio_trigger_poll(iio->trig);
			spin_unlock_irqrestore(&adc->lock, flags);
		पूर्ण
	पूर्ण अन्यथा अगर (reg & LRADC_CTRL1_LRADC_IRQ(0)) अणु
		complete(&adc->completion);
	पूर्ण

	ग_लिखोl(reg & mxs_lradc_irq_mask(lradc),
	       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	वापस IRQ_HANDLED;
पूर्ण


/* Trigger handling */
अटल irqवापस_t mxs_lradc_adc_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *iio = pf->indio_dev;
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);
	स्थिर u32 chan_value = LRADC_CH_ACCUMULATE |
		((LRADC_DELAY_TIMER_LOOP - 1) << LRADC_CH_NUM_SAMPLES_OFFSET);
	अचिन्हित पूर्णांक i, j = 0;

	क्रम_each_set_bit(i, iio->active_scan_mask, LRADC_MAX_TOTAL_CHANS) अणु
		adc->buffer[j] = पढ़ोl(adc->base + LRADC_CH(j));
		ग_लिखोl(chan_value, adc->base + LRADC_CH(j));
		adc->buffer[j] &= LRADC_CH_VALUE_MASK;
		adc->buffer[j] /= LRADC_DELAY_TIMER_LOOP;
		j++;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(iio, adc->buffer, pf->बारtamp);

	iio_trigger_notअगरy_करोne(iio->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxs_lradc_adc_configure_trigger(काष्ठा iio_trigger *trig, bool state)
अणु
	काष्ठा iio_dev *iio = iio_trigger_get_drvdata(trig);
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);
	स्थिर u32 st = state ? STMP_OFFSET_REG_SET : STMP_OFFSET_REG_CLR;

	ग_लिखोl(LRADC_DELAY_KICK, adc->base + (LRADC_DELAY(0) + st));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops mxs_lradc_adc_trigger_ops = अणु
	.set_trigger_state = &mxs_lradc_adc_configure_trigger,
पूर्ण;

अटल पूर्णांक mxs_lradc_adc_trigger_init(काष्ठा iio_dev *iio)
अणु
	पूर्णांक ret;
	काष्ठा iio_trigger *trig;
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);

	trig = devm_iio_trigger_alloc(&iio->dev, "%s-dev%i", iio->name,
				      iio->id);
	अगर (!trig)
		वापस -ENOMEM;

	trig->dev.parent = adc->dev;
	iio_trigger_set_drvdata(trig, iio);
	trig->ops = &mxs_lradc_adc_trigger_ops;

	ret = iio_trigger_रेजिस्टर(trig);
	अगर (ret)
		वापस ret;

	adc->trig = trig;

	वापस 0;
पूर्ण

अटल व्योम mxs_lradc_adc_trigger_हटाओ(काष्ठा iio_dev *iio)
अणु
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);

	iio_trigger_unरेजिस्टर(adc->trig);
पूर्ण

अटल पूर्णांक mxs_lradc_adc_buffer_preenable(काष्ठा iio_dev *iio)
अणु
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);
	काष्ठा mxs_lradc *lradc = adc->lradc;
	पूर्णांक chan, ofs = 0;
	अचिन्हित दीर्घ enable = 0;
	u32 ctrl4_set = 0;
	u32 ctrl4_clr = 0;
	u32 ctrl1_irq = 0;
	स्थिर u32 chan_value = LRADC_CH_ACCUMULATE |
		((LRADC_DELAY_TIMER_LOOP - 1) << LRADC_CH_NUM_SAMPLES_OFFSET);

	अगर (lradc->soc == IMX28_LRADC)
		ग_लिखोl(lradc->buffer_vchans << LRADC_CTRL1_LRADC_IRQ_EN_OFFSET,
		       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(lradc->buffer_vchans,
	       adc->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);

	क्रम_each_set_bit(chan, iio->active_scan_mask, LRADC_MAX_TOTAL_CHANS) अणु
		ctrl4_set |= chan << LRADC_CTRL4_LRADCSELECT_OFFSET(ofs);
		ctrl4_clr |= LRADC_CTRL4_LRADCSELECT_MASK(ofs);
		ctrl1_irq |= LRADC_CTRL1_LRADC_IRQ_EN(ofs);
		ग_लिखोl(chan_value, adc->base + LRADC_CH(ofs));
		biपंचांगap_set(&enable, ofs, 1);
		ofs++;
	पूर्ण

	ग_लिखोl(LRADC_DELAY_TRIGGER_LRADCS_MASK | LRADC_DELAY_KICK,
	       adc->base + LRADC_DELAY(0) + STMP_OFFSET_REG_CLR);
	ग_लिखोl(ctrl4_clr, adc->base + LRADC_CTRL4 + STMP_OFFSET_REG_CLR);
	ग_लिखोl(ctrl4_set, adc->base + LRADC_CTRL4 + STMP_OFFSET_REG_SET);
	ग_लिखोl(ctrl1_irq, adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_SET);
	ग_लिखोl(enable << LRADC_DELAY_TRIGGER_LRADCS_OFFSET,
	       adc->base + LRADC_DELAY(0) + STMP_OFFSET_REG_SET);

	वापस 0;
पूर्ण

अटल पूर्णांक mxs_lradc_adc_buffer_postdisable(काष्ठा iio_dev *iio)
अणु
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);
	काष्ठा mxs_lradc *lradc = adc->lradc;

	ग_लिखोl(LRADC_DELAY_TRIGGER_LRADCS_MASK | LRADC_DELAY_KICK,
	       adc->base + LRADC_DELAY(0) + STMP_OFFSET_REG_CLR);

	ग_लिखोl(lradc->buffer_vchans,
	       adc->base + LRADC_CTRL0 + STMP_OFFSET_REG_CLR);
	अगर (lradc->soc == IMX28_LRADC)
		ग_लिखोl(lradc->buffer_vchans << LRADC_CTRL1_LRADC_IRQ_EN_OFFSET,
		       adc->base + LRADC_CTRL1 + STMP_OFFSET_REG_CLR);

	वापस 0;
पूर्ण

अटल bool mxs_lradc_adc_validate_scan_mask(काष्ठा iio_dev *iio,
					     स्थिर अचिन्हित दीर्घ *mask)
अणु
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);
	काष्ठा mxs_lradc *lradc = adc->lradc;
	स्थिर पूर्णांक map_chans = biपंचांगap_weight(mask, LRADC_MAX_TOTAL_CHANS);
	पूर्णांक rsvd_chans = 0;
	अचिन्हित दीर्घ rsvd_mask = 0;

	अगर (lradc->use_touchbutton)
		rsvd_mask |= CHAN_MASK_TOUCHBUTTON;
	अगर (lradc->touchscreen_wire == MXS_LRADC_TOUCHSCREEN_4WIRE)
		rsvd_mask |= CHAN_MASK_TOUCHSCREEN_4WIRE;
	अगर (lradc->touchscreen_wire == MXS_LRADC_TOUCHSCREEN_5WIRE)
		rsvd_mask |= CHAN_MASK_TOUCHSCREEN_5WIRE;

	अगर (lradc->use_touchbutton)
		rsvd_chans++;
	अगर (lradc->touchscreen_wire)
		rsvd_chans += 2;

	/* Test क्रम attempts to map channels with special mode of operation. */
	अगर (biपंचांगap_पूर्णांकersects(mask, &rsvd_mask, LRADC_MAX_TOTAL_CHANS))
		वापस false;

	/* Test क्रम attempts to map more channels then available slots. */
	अगर (map_chans + rsvd_chans > LRADC_MAX_MAPPED_CHANS)
		वापस false;

	वापस true;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops mxs_lradc_adc_buffer_ops = अणु
	.preenable = &mxs_lradc_adc_buffer_preenable,
	.postdisable = &mxs_lradc_adc_buffer_postdisable,
	.validate_scan_mask = &mxs_lradc_adc_validate_scan_mask,
पूर्ण;

/* Driver initialization */
#घोषणा MXS_ADC_CHAN(idx, chan_type, name) अणु			\
	.type = (chan_type),					\
	.indexed = 1,						\
	.scan_index = (idx),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
			      BIT(IIO_CHAN_INFO_SCALE),		\
	.channel = (idx),					\
	.address = (idx),					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = LRADC_RESOLUTION,			\
		.storagebits = 32,				\
	पूर्ण,							\
	.datasheet_name = (name),				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mx23_lradc_chan_spec[] = अणु
	MXS_ADC_CHAN(0, IIO_VOLTAGE, "LRADC0"),
	MXS_ADC_CHAN(1, IIO_VOLTAGE, "LRADC1"),
	MXS_ADC_CHAN(2, IIO_VOLTAGE, "LRADC2"),
	MXS_ADC_CHAN(3, IIO_VOLTAGE, "LRADC3"),
	MXS_ADC_CHAN(4, IIO_VOLTAGE, "LRADC4"),
	MXS_ADC_CHAN(5, IIO_VOLTAGE, "LRADC5"),
	MXS_ADC_CHAN(6, IIO_VOLTAGE, "VDDIO"),
	MXS_ADC_CHAN(7, IIO_VOLTAGE, "VBATT"),
	/* Combined Temperature sensors */
	अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = 8,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.channel = 8,
		.scan_type = अणु.sign = 'u', .realbits = 18, .storagebits = 32,पूर्ण,
		.datasheet_name = "TEMP_DIE",
	पूर्ण,
	/* Hidden channel to keep indexes */
	अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = -1,
		.channel = 9,
	पूर्ण,
	MXS_ADC_CHAN(10, IIO_VOLTAGE, शून्य),
	MXS_ADC_CHAN(11, IIO_VOLTAGE, शून्य),
	MXS_ADC_CHAN(12, IIO_VOLTAGE, "USB_DP"),
	MXS_ADC_CHAN(13, IIO_VOLTAGE, "USB_DN"),
	MXS_ADC_CHAN(14, IIO_VOLTAGE, "VBG"),
	MXS_ADC_CHAN(15, IIO_VOLTAGE, "VDD5V"),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec mx28_lradc_chan_spec[] = अणु
	MXS_ADC_CHAN(0, IIO_VOLTAGE, "LRADC0"),
	MXS_ADC_CHAN(1, IIO_VOLTAGE, "LRADC1"),
	MXS_ADC_CHAN(2, IIO_VOLTAGE, "LRADC2"),
	MXS_ADC_CHAN(3, IIO_VOLTAGE, "LRADC3"),
	MXS_ADC_CHAN(4, IIO_VOLTAGE, "LRADC4"),
	MXS_ADC_CHAN(5, IIO_VOLTAGE, "LRADC5"),
	MXS_ADC_CHAN(6, IIO_VOLTAGE, "LRADC6"),
	MXS_ADC_CHAN(7, IIO_VOLTAGE, "VBATT"),
	/* Combined Temperature sensors */
	अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = 8,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_OFFSET) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.channel = 8,
		.scan_type = अणु.sign = 'u', .realbits = 18, .storagebits = 32,पूर्ण,
		.datasheet_name = "TEMP_DIE",
	पूर्ण,
	/* Hidden channel to keep indexes */
	अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.scan_index = -1,
		.channel = 9,
	पूर्ण,
	MXS_ADC_CHAN(10, IIO_VOLTAGE, "VDDIO"),
	MXS_ADC_CHAN(11, IIO_VOLTAGE, "VTH"),
	MXS_ADC_CHAN(12, IIO_VOLTAGE, "VDDA"),
	MXS_ADC_CHAN(13, IIO_VOLTAGE, "VDDD"),
	MXS_ADC_CHAN(14, IIO_VOLTAGE, "VBG"),
	MXS_ADC_CHAN(15, IIO_VOLTAGE, "VDD5V"),
पूर्ण;

अटल व्योम mxs_lradc_adc_hw_init(काष्ठा mxs_lradc_adc *adc)
अणु
	/* The ADC always uses DELAY CHANNEL 0. */
	स्थिर u32 adc_cfg =
		(1 << (LRADC_DELAY_TRIGGER_DELAYS_OFFSET + 0)) |
		(LRADC_DELAY_TIMER_PER << LRADC_DELAY_DELAY_OFFSET);

	/* Configure DELAY CHANNEL 0 क्रम generic ADC sampling. */
	ग_लिखोl(adc_cfg, adc->base + LRADC_DELAY(0));

	/*
	 * Start पूर्णांकernal temperature sensing by clearing bit
	 * HW_LRADC_CTRL2_TEMPSENSE_PWD. This bit can be left cleared
	 * after घातer up.
	 */
	ग_लिखोl(0, adc->base + LRADC_CTRL2);
पूर्ण

अटल व्योम mxs_lradc_adc_hw_stop(काष्ठा mxs_lradc_adc *adc)
अणु
	ग_लिखोl(0, adc->base + LRADC_DELAY(0));
पूर्ण

अटल पूर्णांक mxs_lradc_adc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mxs_lradc *lradc = dev_get_drvdata(dev->parent);
	काष्ठा mxs_lradc_adc *adc;
	काष्ठा iio_dev *iio;
	काष्ठा resource *iores;
	पूर्णांक ret, irq, virq, i, s, n;
	u64 scale_uv;
	स्थिर अक्षर **irq_name;

	/* Allocate the IIO device. */
	iio = devm_iio_device_alloc(dev, माप(*adc));
	अगर (!iio) अणु
		dev_err(dev, "Failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण

	adc = iio_priv(iio);
	adc->lradc = lradc;
	adc->dev = dev;

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!iores)
		वापस -EINVAL;

	adc->base = devm_ioremap(dev, iores->start, resource_size(iores));
	अगर (!adc->base)
		वापस -ENOMEM;

	init_completion(&adc->completion);
	spin_lock_init(&adc->lock);

	platक्रमm_set_drvdata(pdev, iio);

	iio->name = pdev->name;
	iio->dev.of_node = dev->parent->of_node;
	iio->info = &mxs_lradc_adc_iio_info;
	iio->modes = INDIO_सूचीECT_MODE;
	iio->masklength = LRADC_MAX_TOTAL_CHANS;

	अगर (lradc->soc == IMX23_LRADC) अणु
		iio->channels = mx23_lradc_chan_spec;
		iio->num_channels = ARRAY_SIZE(mx23_lradc_chan_spec);
		irq_name = mx23_lradc_adc_irq_names;
		n = ARRAY_SIZE(mx23_lradc_adc_irq_names);
	पूर्ण अन्यथा अणु
		iio->channels = mx28_lradc_chan_spec;
		iio->num_channels = ARRAY_SIZE(mx28_lradc_chan_spec);
		irq_name = mx28_lradc_adc_irq_names;
		n = ARRAY_SIZE(mx28_lradc_adc_irq_names);
	पूर्ण

	ret = sपंचांगp_reset_block(adc->base);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < n; i++) अणु
		irq = platक्रमm_get_irq_byname(pdev, irq_name[i]);
		अगर (irq < 0)
			वापस irq;

		virq = irq_of_parse_and_map(dev->parent->of_node, irq);

		ret = devm_request_irq(dev, virq, mxs_lradc_adc_handle_irq,
				       0, irq_name[i], iio);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mxs_lradc_adc_trigger_init(iio);
	अगर (ret)
		जाओ err_trig;

	ret = iio_triggered_buffer_setup(iio, &iio_pollfunc_store_समय,
					 &mxs_lradc_adc_trigger_handler,
					 &mxs_lradc_adc_buffer_ops);
	अगर (ret)
		वापस ret;

	adc->vref_mv = mxs_lradc_adc_vref_mv[lradc->soc];

	/* Populate available ADC input ranges */
	क्रम (i = 0; i < LRADC_MAX_TOTAL_CHANS; i++) अणु
		क्रम (s = 0; s < ARRAY_SIZE(adc->scale_avail[i]); s++) अणु
			/*
			 * [s=0] = optional भागider by two disabled (शेष)
			 * [s=1] = optional भागider by two enabled
			 *
			 * The scale is calculated by करोing:
			 *   Vref >> (realbits - s)
			 * which multiplies by two on the second component
			 * of the array.
			 */
			scale_uv = ((u64)adc->vref_mv[i] * 100000000) >>
				   (LRADC_RESOLUTION - s);
			adc->scale_avail[i][s].nano =
					करो_भाग(scale_uv, 100000000) * 10;
			adc->scale_avail[i][s].पूर्णांकeger = scale_uv;
		पूर्ण
	पूर्ण

	/* Configure the hardware. */
	mxs_lradc_adc_hw_init(adc);

	/* Register IIO device. */
	ret = iio_device_रेजिस्टर(iio);
	अगर (ret) अणु
		dev_err(dev, "Failed to register IIO device\n");
		जाओ err_dev;
	पूर्ण

	वापस 0;

err_dev:
	mxs_lradc_adc_hw_stop(adc);
	mxs_lradc_adc_trigger_हटाओ(iio);
err_trig:
	iio_triggered_buffer_cleanup(iio);
	वापस ret;
पूर्ण

अटल पूर्णांक mxs_lradc_adc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *iio = platक्रमm_get_drvdata(pdev);
	काष्ठा mxs_lradc_adc *adc = iio_priv(iio);

	iio_device_unरेजिस्टर(iio);
	mxs_lradc_adc_hw_stop(adc);
	mxs_lradc_adc_trigger_हटाओ(iio);
	iio_triggered_buffer_cleanup(iio);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_lradc_adc_driver = अणु
	.driver = अणु
		.name	= "mxs-lradc-adc",
	पूर्ण,
	.probe	= mxs_lradc_adc_probe,
	.हटाओ = mxs_lradc_adc_हटाओ,
पूर्ण;
module_platक्रमm_driver(mxs_lradc_adc_driver);

MODULE_AUTHOR("Marek Vasut <marex@denx.de>");
MODULE_DESCRIPTION("Freescale MXS LRADC driver general purpose ADC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:mxs-lradc-adc");
