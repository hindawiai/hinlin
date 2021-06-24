<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * lm3533-als.c -- LM3533 Ambient Light Sensor driver
 *
 * Copyright (C) 2011-2012 Texas Instruments
 *
 * Author: Johan Hovold <jhovold@gmail.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/mfd/lm3533.h>


#घोषणा LM3533_ALS_RESISTOR_MIN			1
#घोषणा LM3533_ALS_RESISTOR_MAX			127
#घोषणा LM3533_ALS_CHANNEL_CURRENT_MAX		2
#घोषणा LM3533_ALS_THRESH_MAX			3
#घोषणा LM3533_ALS_ZONE_MAX			4

#घोषणा LM3533_REG_ALS_RESISTOR_SELECT		0x30
#घोषणा LM3533_REG_ALS_CONF			0x31
#घोषणा LM3533_REG_ALS_ZONE_INFO		0x34
#घोषणा LM3533_REG_ALS_READ_ADC_RAW		0x37
#घोषणा LM3533_REG_ALS_READ_ADC_AVERAGE		0x38
#घोषणा LM3533_REG_ALS_BOUNDARY_BASE		0x50
#घोषणा LM3533_REG_ALS_TARGET_BASE		0x60

#घोषणा LM3533_ALS_ENABLE_MASK			0x01
#घोषणा LM3533_ALS_INPUT_MODE_MASK		0x02
#घोषणा LM3533_ALS_INT_ENABLE_MASK		0x01

#घोषणा LM3533_ALS_ZONE_SHIFT			2
#घोषणा LM3533_ALS_ZONE_MASK			0x1c

#घोषणा LM3533_ALS_FLAG_INT_ENABLED		1


काष्ठा lm3533_als अणु
	काष्ठा lm3533 *lm3533;
	काष्ठा platक्रमm_device *pdev;

	अचिन्हित दीर्घ flags;
	पूर्णांक irq;

	atomic_t zone;
	काष्ठा mutex thresh_mutex;
पूर्ण;


अटल पूर्णांक lm3533_als_get_adc(काष्ठा iio_dev *indio_dev, bool average,
								पूर्णांक *adc)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 reg;
	u8 val;
	पूर्णांक ret;

	अगर (average)
		reg = LM3533_REG_ALS_READ_ADC_AVERAGE;
	अन्यथा
		reg = LM3533_REG_ALS_READ_ADC_RAW;

	ret = lm3533_पढ़ो(als->lm3533, reg, &val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "failed to read adc\n");
		वापस ret;
	पूर्ण

	*adc = val;

	वापस 0;
पूर्ण

अटल पूर्णांक _lm3533_als_get_zone(काष्ठा iio_dev *indio_dev, u8 *zone)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 val;
	पूर्णांक ret;

	ret = lm3533_पढ़ो(als->lm3533, LM3533_REG_ALS_ZONE_INFO, &val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "failed to read zone\n");
		वापस ret;
	पूर्ण

	val = (val & LM3533_ALS_ZONE_MASK) >> LM3533_ALS_ZONE_SHIFT;
	*zone = min_t(u8, val, LM3533_ALS_ZONE_MAX);

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_als_get_zone(काष्ठा iio_dev *indio_dev, u8 *zone)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (test_bit(LM3533_ALS_FLAG_INT_ENABLED, &als->flags)) अणु
		*zone = atomic_पढ़ो(&als->zone);
	पूर्ण अन्यथा अणु
		ret = _lm3533_als_get_zone(indio_dev, zone);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * channel	output channel 0..2
 * zone		zone 0..4
 */
अटल अंतरभूत u8 lm3533_als_get_target_reg(अचिन्हित channel, अचिन्हित zone)
अणु
	वापस LM3533_REG_ALS_TARGET_BASE + 5 * channel + zone;
पूर्ण

अटल पूर्णांक lm3533_als_get_target(काष्ठा iio_dev *indio_dev, अचिन्हित channel,
							अचिन्हित zone, u8 *val)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 reg;
	पूर्णांक ret;

	अगर (channel > LM3533_ALS_CHANNEL_CURRENT_MAX)
		वापस -EINVAL;

	अगर (zone > LM3533_ALS_ZONE_MAX)
		वापस -EINVAL;

	reg = lm3533_als_get_target_reg(channel, zone);
	ret = lm3533_पढ़ो(als->lm3533, reg, val);
	अगर (ret)
		dev_err(&indio_dev->dev, "failed to get target current\n");

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_als_set_target(काष्ठा iio_dev *indio_dev, अचिन्हित channel,
							अचिन्हित zone, u8 val)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 reg;
	पूर्णांक ret;

	अगर (channel > LM3533_ALS_CHANNEL_CURRENT_MAX)
		वापस -EINVAL;

	अगर (zone > LM3533_ALS_ZONE_MAX)
		वापस -EINVAL;

	reg = lm3533_als_get_target_reg(channel, zone);
	ret = lm3533_ग_लिखो(als->lm3533, reg, val);
	अगर (ret)
		dev_err(&indio_dev->dev, "failed to set target current\n");

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_als_get_current(काष्ठा iio_dev *indio_dev, अचिन्हित channel,
								पूर्णांक *val)
अणु
	u8 zone;
	u8 target;
	पूर्णांक ret;

	ret = lm3533_als_get_zone(indio_dev, &zone);
	अगर (ret)
		वापस ret;

	ret = lm3533_als_get_target(indio_dev, channel, zone, &target);
	अगर (ret)
		वापस ret;

	*val = target;

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_als_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = lm3533_als_get_adc(indio_dev, false, val);
			अवरोध;
		हाल IIO_CURRENT:
			ret = lm3533_als_get_current(indio_dev, chan->channel,
									val);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_AVERAGE_RAW:
		ret = lm3533_als_get_adc(indio_dev, true, val);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस IIO_VAL_INT;
पूर्ण

#घोषणा CHANNEL_CURRENT(_channel)					\
	अणु								\
		.type		= IIO_CURRENT,				\
		.channel	= _channel,				\
		.indexed	= true,					\
		.output		= true,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec lm3533_als_channels[] = अणु
	अणु
		.type		= IIO_LIGHT,
		.channel	= 0,
		.indexed	= true,
		.info_mask_separate = BIT(IIO_CHAN_INFO_AVERAGE_RAW) |
				   BIT(IIO_CHAN_INFO_RAW),
	पूर्ण,
	CHANNEL_CURRENT(0),
	CHANNEL_CURRENT(1),
	CHANNEL_CURRENT(2),
पूर्ण;

अटल irqवापस_t lm3533_als_isr(पूर्णांक irq, व्योम *dev_id)
अणु

	काष्ठा iio_dev *indio_dev = dev_id;
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 zone;
	पूर्णांक ret;

	/* Clear पूर्णांकerrupt by पढ़ोing the ALS zone रेजिस्टर. */
	ret = _lm3533_als_get_zone(indio_dev, &zone);
	अगर (ret)
		जाओ out;

	atomic_set(&als->zone, zone);

	iio_push_event(indio_dev,
		       IIO_UNMOD_EVENT_CODE(IIO_LIGHT,
					    0,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_सूची_EITHER),
		       iio_get_समय_ns(indio_dev));
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lm3533_als_set_पूर्णांक_mode(काष्ठा iio_dev *indio_dev, पूर्णांक enable)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 mask = LM3533_ALS_INT_ENABLE_MASK;
	u8 val;
	पूर्णांक ret;

	अगर (enable)
		val = mask;
	अन्यथा
		val = 0;

	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_ZONE_INFO, val, mask);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "failed to set int mode %d\n",
								enable);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_als_get_पूर्णांक_mode(काष्ठा iio_dev *indio_dev, पूर्णांक *enable)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 mask = LM3533_ALS_INT_ENABLE_MASK;
	u8 val;
	पूर्णांक ret;

	ret = lm3533_पढ़ो(als->lm3533, LM3533_REG_ALS_ZONE_INFO, &val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "failed to get int mode\n");
		वापस ret;
	पूर्ण

	*enable = !!(val & mask);

	वापस 0;
पूर्ण

अटल अंतरभूत u8 lm3533_als_get_threshold_reg(अचिन्हित nr, bool raising)
अणु
	u8 offset = !raising;

	वापस LM3533_REG_ALS_BOUNDARY_BASE + 2 * nr + offset;
पूर्ण

अटल पूर्णांक lm3533_als_get_threshold(काष्ठा iio_dev *indio_dev, अचिन्हित nr,
							bool raising, u8 *val)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 reg;
	पूर्णांक ret;

	अगर (nr > LM3533_ALS_THRESH_MAX)
		वापस -EINVAL;

	reg = lm3533_als_get_threshold_reg(nr, raising);
	ret = lm3533_पढ़ो(als->lm3533, reg, val);
	अगर (ret)
		dev_err(&indio_dev->dev, "failed to get threshold\n");

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_als_set_threshold(काष्ठा iio_dev *indio_dev, अचिन्हित nr,
							bool raising, u8 val)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 val2;
	u8 reg, reg2;
	पूर्णांक ret;

	अगर (nr > LM3533_ALS_THRESH_MAX)
		वापस -EINVAL;

	reg = lm3533_als_get_threshold_reg(nr, raising);
	reg2 = lm3533_als_get_threshold_reg(nr, !raising);

	mutex_lock(&als->thresh_mutex);
	ret = lm3533_पढ़ो(als->lm3533, reg2, &val2);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "failed to get threshold\n");
		जाओ out;
	पूर्ण
	/*
	 * This device करोes not allow negative hysteresis (in fact, it uses
	 * whichever value is smaller as the lower bound) so we need to make
	 * sure that thresh_falling <= thresh_raising.
	 */
	अगर ((raising && (val < val2)) || (!raising && (val > val2))) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = lm3533_ग_लिखो(als->lm3533, reg, val);
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "failed to set threshold\n");
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&als->thresh_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_als_get_hysteresis(काष्ठा iio_dev *indio_dev, अचिन्हित nr,
								u8 *val)
अणु
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	u8 falling;
	u8 raising;
	पूर्णांक ret;

	अगर (nr > LM3533_ALS_THRESH_MAX)
		वापस -EINVAL;

	mutex_lock(&als->thresh_mutex);
	ret = lm3533_als_get_threshold(indio_dev, nr, false, &falling);
	अगर (ret)
		जाओ out;
	ret = lm3533_als_get_threshold(indio_dev, nr, true, &raising);
	अगर (ret)
		जाओ out;

	*val = raising - falling;
out:
	mutex_unlock(&als->thresh_mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_thresh_either_en(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	पूर्णांक enable;
	पूर्णांक ret;

	अगर (als->irq) अणु
		ret = lm3533_als_get_पूर्णांक_mode(indio_dev, &enable);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		enable = 0;
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", enable);
पूर्ण

अटल sमाप_प्रकार store_thresh_either_en(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा lm3533_als *als = iio_priv(indio_dev);
	अचिन्हित दीर्घ enable;
	bool पूर्णांक_enabled;
	u8 zone;
	पूर्णांक ret;

	अगर (!als->irq)
		वापस -EBUSY;

	अगर (kम_से_अदीर्घ(buf, 0, &enable))
		वापस -EINVAL;

	पूर्णांक_enabled = test_bit(LM3533_ALS_FLAG_INT_ENABLED, &als->flags);

	अगर (enable && !पूर्णांक_enabled) अणु
		ret = lm3533_als_get_zone(indio_dev, &zone);
		अगर (ret)
			वापस ret;

		atomic_set(&als->zone, zone);

		set_bit(LM3533_ALS_FLAG_INT_ENABLED, &als->flags);
	पूर्ण

	ret = lm3533_als_set_पूर्णांक_mode(indio_dev, enable);
	अगर (ret) अणु
		अगर (!पूर्णांक_enabled)
			clear_bit(LM3533_ALS_FLAG_INT_ENABLED, &als->flags);

		वापस ret;
	पूर्ण

	अगर (!enable)
		clear_bit(LM3533_ALS_FLAG_INT_ENABLED, &als->flags);

	वापस len;
पूर्ण

अटल sमाप_प्रकार show_zone(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	u8 zone;
	पूर्णांक ret;

	ret = lm3533_als_get_zone(indio_dev, &zone);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", zone);
पूर्ण

क्रमागत lm3533_als_attribute_type अणु
	LM3533_ATTR_TYPE_HYSTERESIS,
	LM3533_ATTR_TYPE_TARGET,
	LM3533_ATTR_TYPE_THRESH_FALLING,
	LM3533_ATTR_TYPE_THRESH_RAISING,
पूर्ण;

काष्ठा lm3533_als_attribute अणु
	काष्ठा device_attribute dev_attr;
	क्रमागत lm3533_als_attribute_type type;
	u8 val1;
	u8 val2;
पूर्ण;

अटल अंतरभूत काष्ठा lm3533_als_attribute *
to_lm3533_als_attr(काष्ठा device_attribute *attr)
अणु
	वापस container_of(attr, काष्ठा lm3533_als_attribute, dev_attr);
पूर्ण

अटल sमाप_प्रकार show_als_attr(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा lm3533_als_attribute *als_attr = to_lm3533_als_attr(attr);
	u8 val;
	पूर्णांक ret;

	चयन (als_attr->type) अणु
	हाल LM3533_ATTR_TYPE_HYSTERESIS:
		ret = lm3533_als_get_hysteresis(indio_dev, als_attr->val1,
									&val);
		अवरोध;
	हाल LM3533_ATTR_TYPE_TARGET:
		ret = lm3533_als_get_target(indio_dev, als_attr->val1,
							als_attr->val2, &val);
		अवरोध;
	हाल LM3533_ATTR_TYPE_THRESH_FALLING:
		ret = lm3533_als_get_threshold(indio_dev, als_attr->val1,
								false, &val);
		अवरोध;
	हाल LM3533_ATTR_TYPE_THRESH_RAISING:
		ret = lm3533_als_get_threshold(indio_dev, als_attr->val1,
								true, &val);
		अवरोध;
	शेष:
		ret = -ENXIO;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", val);
पूर्ण

अटल sमाप_प्रकार store_als_attr(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा lm3533_als_attribute *als_attr = to_lm3533_als_attr(attr);
	u8 val;
	पूर्णांक ret;

	अगर (kstrtou8(buf, 0, &val))
		वापस -EINVAL;

	चयन (als_attr->type) अणु
	हाल LM3533_ATTR_TYPE_TARGET:
		ret = lm3533_als_set_target(indio_dev, als_attr->val1,
							als_attr->val2, val);
		अवरोध;
	हाल LM3533_ATTR_TYPE_THRESH_FALLING:
		ret = lm3533_als_set_threshold(indio_dev, als_attr->val1,
								false, val);
		अवरोध;
	हाल LM3533_ATTR_TYPE_THRESH_RAISING:
		ret = lm3533_als_set_threshold(indio_dev, als_attr->val1,
								true, val);
		अवरोध;
	शेष:
		ret = -ENXIO;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

#घोषणा ALS_ATTR(_name, _mode, _show, _store, _type, _val1, _val2)	\
	अणु .dev_attr	= __ATTR(_name, _mode, _show, _store),		\
	  .type		= _type,					\
	  .val1		= _val1,					\
	  .val2		= _val2 पूर्ण

#घोषणा LM3533_ALS_ATTR(_name, _mode, _show, _store, _type, _val1, _val2) \
	काष्ठा lm3533_als_attribute lm3533_als_attr_##_name =		  \
		ALS_ATTR(_name, _mode, _show, _store, _type, _val1, _val2)

#घोषणा ALS_TARGET_ATTR_RW(_channel, _zone)				\
	LM3533_ALS_ATTR(out_current##_channel##_current##_zone##_raw,	\
				S_IRUGO | S_IWUSR,			\
				show_als_attr, store_als_attr,		\
				LM3533_ATTR_TYPE_TARGET, _channel, _zone)
/*
 * ALS output current values (ALS mapper tarमाला_लो)
 *
 * out_current[0-2]_current[0-4]_raw		0-255
 */
अटल ALS_TARGET_ATTR_RW(0, 0);
अटल ALS_TARGET_ATTR_RW(0, 1);
अटल ALS_TARGET_ATTR_RW(0, 2);
अटल ALS_TARGET_ATTR_RW(0, 3);
अटल ALS_TARGET_ATTR_RW(0, 4);

अटल ALS_TARGET_ATTR_RW(1, 0);
अटल ALS_TARGET_ATTR_RW(1, 1);
अटल ALS_TARGET_ATTR_RW(1, 2);
अटल ALS_TARGET_ATTR_RW(1, 3);
अटल ALS_TARGET_ATTR_RW(1, 4);

अटल ALS_TARGET_ATTR_RW(2, 0);
अटल ALS_TARGET_ATTR_RW(2, 1);
अटल ALS_TARGET_ATTR_RW(2, 2);
अटल ALS_TARGET_ATTR_RW(2, 3);
अटल ALS_TARGET_ATTR_RW(2, 4);

#घोषणा ALS_THRESH_FALLING_ATTR_RW(_nr)					\
	LM3533_ALS_ATTR(in_illuminance0_thresh##_nr##_falling_value,	\
			S_IRUGO | S_IWUSR,				\
			show_als_attr, store_als_attr,		\
			LM3533_ATTR_TYPE_THRESH_FALLING, _nr, 0)

#घोषणा ALS_THRESH_RAISING_ATTR_RW(_nr)					\
	LM3533_ALS_ATTR(in_illuminance0_thresh##_nr##_raising_value,	\
			S_IRUGO | S_IWUSR,				\
			show_als_attr, store_als_attr,			\
			LM3533_ATTR_TYPE_THRESH_RAISING, _nr, 0)
/*
 * ALS Zone thresholds (boundaries)
 *
 * in_illuminance0_thresh[0-3]_falling_value	0-255
 * in_illuminance0_thresh[0-3]_raising_value	0-255
 */
अटल ALS_THRESH_FALLING_ATTR_RW(0);
अटल ALS_THRESH_FALLING_ATTR_RW(1);
अटल ALS_THRESH_FALLING_ATTR_RW(2);
अटल ALS_THRESH_FALLING_ATTR_RW(3);

अटल ALS_THRESH_RAISING_ATTR_RW(0);
अटल ALS_THRESH_RAISING_ATTR_RW(1);
अटल ALS_THRESH_RAISING_ATTR_RW(2);
अटल ALS_THRESH_RAISING_ATTR_RW(3);

#घोषणा ALS_HYSTERESIS_ATTR_RO(_nr)					\
	LM3533_ALS_ATTR(in_illuminance0_thresh##_nr##_hysteresis,	\
			S_IRUGO, show_als_attr, शून्य,			\
			LM3533_ATTR_TYPE_HYSTERESIS, _nr, 0)
/*
 * ALS Zone threshold hysteresis
 *
 * threshY_hysteresis = threshY_raising - threshY_falling
 *
 * in_illuminance0_thresh[0-3]_hysteresis	0-255
 * in_illuminance0_thresh[0-3]_hysteresis	0-255
 */
अटल ALS_HYSTERESIS_ATTR_RO(0);
अटल ALS_HYSTERESIS_ATTR_RO(1);
अटल ALS_HYSTERESIS_ATTR_RO(2);
अटल ALS_HYSTERESIS_ATTR_RO(3);

#घोषणा ILLUMIन_अंकCE_ATTR_RO(_name) \
	DEVICE_ATTR(in_illuminance0_##_name, S_IRUGO, show_##_name, शून्य)
#घोषणा ILLUMIन_अंकCE_ATTR_RW(_name) \
	DEVICE_ATTR(in_illuminance0_##_name, S_IRUGO | S_IWUSR, \
						show_##_name, store_##_name)
/*
 * ALS Zone threshold-event enable
 *
 * in_illuminance0_thresh_either_en		0,1
 */
अटल ILLUMIन_अंकCE_ATTR_RW(thresh_either_en);

/*
 * ALS Current Zone
 *
 * in_illuminance0_zone		0-4
 */
अटल ILLUMIन_अंकCE_ATTR_RO(zone);

अटल काष्ठा attribute *lm3533_als_event_attributes[] = अणु
	&dev_attr_in_illuminance0_thresh_either_en.attr,
	&lm3533_als_attr_in_illuminance0_thresh0_falling_value.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh0_hysteresis.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh0_raising_value.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh1_falling_value.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh1_hysteresis.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh1_raising_value.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh2_falling_value.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh2_hysteresis.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh2_raising_value.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh3_falling_value.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh3_hysteresis.dev_attr.attr,
	&lm3533_als_attr_in_illuminance0_thresh3_raising_value.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm3533_als_event_attribute_group = अणु
	.attrs = lm3533_als_event_attributes
पूर्ण;

अटल काष्ठा attribute *lm3533_als_attributes[] = अणु
	&dev_attr_in_illuminance0_zone.attr,
	&lm3533_als_attr_out_current0_current0_raw.dev_attr.attr,
	&lm3533_als_attr_out_current0_current1_raw.dev_attr.attr,
	&lm3533_als_attr_out_current0_current2_raw.dev_attr.attr,
	&lm3533_als_attr_out_current0_current3_raw.dev_attr.attr,
	&lm3533_als_attr_out_current0_current4_raw.dev_attr.attr,
	&lm3533_als_attr_out_current1_current0_raw.dev_attr.attr,
	&lm3533_als_attr_out_current1_current1_raw.dev_attr.attr,
	&lm3533_als_attr_out_current1_current2_raw.dev_attr.attr,
	&lm3533_als_attr_out_current1_current3_raw.dev_attr.attr,
	&lm3533_als_attr_out_current1_current4_raw.dev_attr.attr,
	&lm3533_als_attr_out_current2_current0_raw.dev_attr.attr,
	&lm3533_als_attr_out_current2_current1_raw.dev_attr.attr,
	&lm3533_als_attr_out_current2_current2_raw.dev_attr.attr,
	&lm3533_als_attr_out_current2_current3_raw.dev_attr.attr,
	&lm3533_als_attr_out_current2_current4_raw.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lm3533_als_attribute_group = अणु
	.attrs = lm3533_als_attributes
पूर्ण;

अटल पूर्णांक lm3533_als_set_input_mode(काष्ठा lm3533_als *als, bool pwm_mode)
अणु
	u8 mask = LM3533_ALS_INPUT_MODE_MASK;
	u8 val;
	पूर्णांक ret;

	अगर (pwm_mode)
		val = mask;	/* pwm input */
	अन्यथा
		val = 0;	/* analog input */

	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_CONF, val, mask);
	अगर (ret) अणु
		dev_err(&als->pdev->dev, "failed to set input mode %d\n",
								pwm_mode);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_als_set_resistor(काष्ठा lm3533_als *als, u8 val)
अणु
	पूर्णांक ret;

	अगर (val < LM3533_ALS_RESISTOR_MIN || val > LM3533_ALS_RESISTOR_MAX) अणु
		dev_err(&als->pdev->dev, "invalid resistor value\n");
		वापस -EINVAL;
	पूर्ण

	ret = lm3533_ग_लिखो(als->lm3533, LM3533_REG_ALS_RESISTOR_SELECT, val);
	अगर (ret) अणु
		dev_err(&als->pdev->dev, "failed to set resistor\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_als_setup(काष्ठा lm3533_als *als,
			    काष्ठा lm3533_als_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = lm3533_als_set_input_mode(als, pdata->pwm_mode);
	अगर (ret)
		वापस ret;

	/* ALS input is always high impedance in PWM-mode. */
	अगर (!pdata->pwm_mode) अणु
		ret = lm3533_als_set_resistor(als, pdata->r_select);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_als_setup_irq(काष्ठा lm3533_als *als, व्योम *dev)
अणु
	u8 mask = LM3533_ALS_INT_ENABLE_MASK;
	पूर्णांक ret;

	/* Make sure पूर्णांकerrupts are disabled. */
	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_ZONE_INFO, 0, mask);
	अगर (ret) अणु
		dev_err(&als->pdev->dev, "failed to disable interrupts\n");
		वापस ret;
	पूर्ण

	ret = request_thपढ़ोed_irq(als->irq, शून्य, lm3533_als_isr,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					dev_name(&als->pdev->dev), dev);
	अगर (ret) अणु
		dev_err(&als->pdev->dev, "failed to request irq %d\n",
								als->irq);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3533_als_enable(काष्ठा lm3533_als *als)
अणु
	u8 mask = LM3533_ALS_ENABLE_MASK;
	पूर्णांक ret;

	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_CONF, mask, mask);
	अगर (ret)
		dev_err(&als->pdev->dev, "failed to enable ALS\n");

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_als_disable(काष्ठा lm3533_als *als)
अणु
	u8 mask = LM3533_ALS_ENABLE_MASK;
	पूर्णांक ret;

	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_CONF, 0, mask);
	अगर (ret)
		dev_err(&als->pdev->dev, "failed to disable ALS\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info lm3533_als_info = अणु
	.attrs		= &lm3533_als_attribute_group,
	.event_attrs	= &lm3533_als_event_attribute_group,
	.पढ़ो_raw	= &lm3533_als_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक lm3533_als_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lm3533 *lm3533;
	काष्ठा lm3533_als_platक्रमm_data *pdata;
	काष्ठा lm3533_als *als;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	lm3533 = dev_get_drvdata(pdev->dev.parent);
	अगर (!lm3533)
		वापस -EINVAL;

	pdata = pdev->dev.platक्रमm_data;
	अगर (!pdata) अणु
		dev_err(&pdev->dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*als));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->info = &lm3533_als_info;
	indio_dev->channels = lm3533_als_channels;
	indio_dev->num_channels = ARRAY_SIZE(lm3533_als_channels);
	indio_dev->name = dev_name(&pdev->dev);
	iio_device_set_parent(indio_dev, pdev->dev.parent);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	als = iio_priv(indio_dev);
	als->lm3533 = lm3533;
	als->pdev = pdev;
	als->irq = lm3533->irq;
	atomic_set(&als->zone, 0);
	mutex_init(&als->thresh_mutex);

	platक्रमm_set_drvdata(pdev, indio_dev);

	अगर (als->irq) अणु
		ret = lm3533_als_setup_irq(als, indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = lm3533_als_setup(als, pdata);
	अगर (ret)
		जाओ err_मुक्त_irq;

	ret = lm3533_als_enable(als);
	अगर (ret)
		जाओ err_मुक्त_irq;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register ALS\n");
		जाओ err_disable;
	पूर्ण

	वापस 0;

err_disable:
	lm3533_als_disable(als);
err_मुक्त_irq:
	अगर (als->irq)
		मुक्त_irq(als->irq, indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक lm3533_als_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा lm3533_als *als = iio_priv(indio_dev);

	lm3533_als_set_पूर्णांक_mode(indio_dev, false);
	iio_device_unरेजिस्टर(indio_dev);
	lm3533_als_disable(als);
	अगर (als->irq)
		मुक्त_irq(als->irq, indio_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lm3533_als_driver = अणु
	.driver	= अणु
		.name	= "lm3533-als",
	पूर्ण,
	.probe		= lm3533_als_probe,
	.हटाओ		= lm3533_als_हटाओ,
पूर्ण;
module_platक्रमm_driver(lm3533_als_driver);

MODULE_AUTHOR("Johan Hovold <jhovold@gmail.com>");
MODULE_DESCRIPTION("LM3533 Ambient Light Sensor driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lm3533-als");
