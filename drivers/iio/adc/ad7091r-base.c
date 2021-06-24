<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7091RX Analog to Digital converter driver
 *
 * Copyright 2014-2019 Analog Devices Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश "ad7091r-base.h"

#घोषणा AD7091R_REG_RESULT  0
#घोषणा AD7091R_REG_CHANNEL 1
#घोषणा AD7091R_REG_CONF    2
#घोषणा AD7091R_REG_ALERT   3
#घोषणा AD7091R_REG_CH_LOW_LIMIT(ch) ((ch) * 3 + 4)
#घोषणा AD7091R_REG_CH_HIGH_LIMIT(ch) ((ch) * 3 + 5)
#घोषणा AD7091R_REG_CH_HYSTERESIS(ch) ((ch) * 3 + 6)

/* AD7091R_REG_RESULT */
#घोषणा AD7091R_REG_RESULT_CH_ID(x)	    (((x) >> 13) & 0x3)
#घोषणा AD7091R_REG_RESULT_CONV_RESULT(x)   ((x) & 0xfff)

/* AD7091R_REG_CONF */
#घोषणा AD7091R_REG_CONF_AUTO   BIT(8)
#घोषणा AD7091R_REG_CONF_CMD    BIT(10)

#घोषणा AD7091R_REG_CONF_MODE_MASK  \
	(AD7091R_REG_CONF_AUTO | AD7091R_REG_CONF_CMD)

क्रमागत ad7091r_mode अणु
	AD7091R_MODE_SAMPLE,
	AD7091R_MODE_COMMAND,
	AD7091R_MODE_AUTOCYCLE,
पूर्ण;

काष्ठा ad7091r_state अणु
	काष्ठा device *dev;
	काष्ठा regmap *map;
	काष्ठा regulator *vref;
	स्थिर काष्ठा ad7091r_chip_info *chip_info;
	क्रमागत ad7091r_mode mode;
	काष्ठा mutex lock; /*lock to prevent concurent पढ़ोs */
पूर्ण;

अटल पूर्णांक ad7091r_set_mode(काष्ठा ad7091r_state *st, क्रमागत ad7091r_mode mode)
अणु
	पूर्णांक ret, conf;

	चयन (mode) अणु
	हाल AD7091R_MODE_SAMPLE:
		conf = 0;
		अवरोध;
	हाल AD7091R_MODE_COMMAND:
		conf = AD7091R_REG_CONF_CMD;
		अवरोध;
	हाल AD7091R_MODE_AUTOCYCLE:
		conf = AD7091R_REG_CONF_AUTO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(st->map, AD7091R_REG_CONF,
				 AD7091R_REG_CONF_MODE_MASK, conf);
	अगर (ret)
		वापस ret;

	st->mode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7091r_set_channel(काष्ठा ad7091r_state *st, अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक dummy;
	पूर्णांक ret;

	/* AD7091R_REG_CHANNEL specअगरied which channels to be converted */
	ret = regmap_ग_लिखो(st->map, AD7091R_REG_CHANNEL,
			BIT(channel) | (BIT(channel) << 8));
	अगर (ret)
		वापस ret;

	/*
	 * There is a latency of one conversion beक्रमe the channel conversion
	 * sequence is updated
	 */
	वापस regmap_पढ़ो(st->map, AD7091R_REG_RESULT, &dummy);
पूर्ण

अटल पूर्णांक ad7091r_पढ़ो_one(काष्ठा iio_dev *iio_dev,
		अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक *पढ़ो_val)
अणु
	काष्ठा ad7091r_state *st = iio_priv(iio_dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = ad7091r_set_channel(st, channel);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(st->map, AD7091R_REG_RESULT, &val);
	अगर (ret)
		वापस ret;

	अगर (AD7091R_REG_RESULT_CH_ID(val) != channel)
		वापस -EIO;

	*पढ़ो_val = AD7091R_REG_RESULT_CONV_RESULT(val);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7091r_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा ad7091r_state *st = iio_priv(iio_dev);
	अचिन्हित पूर्णांक पढ़ो_val;
	पूर्णांक ret;

	mutex_lock(&st->lock);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (st->mode != AD7091R_MODE_COMMAND) अणु
			ret = -EBUSY;
			जाओ unlock;
		पूर्ण

		ret = ad7091r_पढ़ो_one(iio_dev, chan->channel, &पढ़ो_val);
		अगर (ret)
			जाओ unlock;

		*val = पढ़ो_val;
		ret = IIO_VAL_INT;
		अवरोध;

	हाल IIO_CHAN_INFO_SCALE:
		अगर (st->vref) अणु
			ret = regulator_get_voltage(st->vref);
			अगर (ret < 0)
				जाओ unlock;

			*val = ret / 1000;
		पूर्ण अन्यथा अणु
			*val = st->chip_info->vref_mV;
		पूर्ण

		*val2 = chan->scan_type.realbits;
		ret = IIO_VAL_FRACTIONAL_LOG2;
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7091r_info = अणु
	.पढ़ो_raw = ad7091r_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t ad7091r_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा ad7091r_state *st = (काष्ठा ad7091r_state *) निजी;
	काष्ठा iio_dev *iio_dev = dev_get_drvdata(st->dev);
	अचिन्हित पूर्णांक i, पढ़ो_val;
	पूर्णांक ret;
	s64 बारtamp = iio_get_समय_ns(iio_dev);

	ret = regmap_पढ़ो(st->map, AD7091R_REG_ALERT, &पढ़ो_val);
	अगर (ret)
		वापस IRQ_HANDLED;

	क्रम (i = 0; i < st->chip_info->num_channels; i++) अणु
		अगर (पढ़ो_val & BIT(i * 2))
			iio_push_event(iio_dev,
					IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, i,
						IIO_EV_TYPE_THRESH,
						IIO_EV_सूची_RISING), बारtamp);
		अगर (पढ़ो_val & BIT(i * 2 + 1))
			iio_push_event(iio_dev,
					IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE, i,
						IIO_EV_TYPE_THRESH,
						IIO_EV_सूची_FALLING), बारtamp);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ad7091r_हटाओ(व्योम *data)
अणु
	काष्ठा ad7091r_state *st = data;

	regulator_disable(st->vref);
पूर्ण

पूर्णांक ad7091r_probe(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर काष्ठा ad7091r_chip_info *chip_info,
		काष्ठा regmap *map, पूर्णांक irq)
अणु
	काष्ठा iio_dev *iio_dev;
	काष्ठा ad7091r_state *st;
	पूर्णांक ret;

	iio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!iio_dev)
		वापस -ENOMEM;

	st = iio_priv(iio_dev);
	st->dev = dev;
	st->chip_info = chip_info;
	st->map = map;

	iio_dev->name = name;
	iio_dev->info = &ad7091r_info;
	iio_dev->modes = INDIO_सूचीECT_MODE;

	iio_dev->num_channels = chip_info->num_channels;
	iio_dev->channels = chip_info->channels;

	अगर (irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य,
				ad7091r_event_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT, name, st);
		अगर (ret)
			वापस ret;
	पूर्ण

	st->vref = devm_regulator_get_optional(dev, "vref");
	अगर (IS_ERR(st->vref)) अणु
		अगर (PTR_ERR(st->vref) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		st->vref = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(st->vref);
		अगर (ret)
			वापस ret;
		ret = devm_add_action_or_reset(dev, ad7091r_हटाओ, st);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Use command mode by शेष to convert only desired channels*/
	ret = ad7091r_set_mode(st, AD7091R_MODE_COMMAND);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, iio_dev);
पूर्ण
EXPORT_SYMBOL_GPL(ad7091r_probe);

अटल bool ad7091r_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AD7091R_REG_RESULT:
	हाल AD7091R_REG_ALERT:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool ad7091r_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AD7091R_REG_RESULT:
	हाल AD7091R_REG_ALERT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config ad7091r_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.ग_लिखोable_reg = ad7091r_ग_लिखोable_reg,
	.अस्थिर_reg = ad7091r_अस्थिर_reg,
पूर्ण;
EXPORT_SYMBOL_GPL(ad7091r_regmap_config);

MODULE_AUTHOR("Beniamin Bia <beniamin.bia@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7091Rx multi-channel converters");
MODULE_LICENSE("GPL v2");
