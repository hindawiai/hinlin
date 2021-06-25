<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5592R Digital <-> Analog converters driver
 *
 * Copyright 2014-2016 Analog Devices Inc.
 * Author: Paul Cercueil <paul.cercueil@analog.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/property.h>

#समावेश <dt-bindings/iio/adi,ad5592r.h>

#समावेश "ad5592r-base.h"

अटल पूर्णांक ad5592r_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ad5592r_state *st = gpiochip_get_data(chip);
	पूर्णांक ret = 0;
	u8 val;

	mutex_lock(&st->gpio_lock);

	अगर (st->gpio_out & BIT(offset))
		val = st->gpio_val;
	अन्यथा
		ret = st->ops->gpio_पढ़ो(st, &val);

	mutex_unlock(&st->gpio_lock);

	अगर (ret < 0)
		वापस ret;

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम ad5592r_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा ad5592r_state *st = gpiochip_get_data(chip);

	mutex_lock(&st->gpio_lock);

	अगर (value)
		st->gpio_val |= BIT(offset);
	अन्यथा
		st->gpio_val &= ~BIT(offset);

	st->ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_SET, st->gpio_val);

	mutex_unlock(&st->gpio_lock);
पूर्ण

अटल पूर्णांक ad5592r_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ad5592r_state *st = gpiochip_get_data(chip);
	पूर्णांक ret;

	mutex_lock(&st->gpio_lock);

	st->gpio_out &= ~BIT(offset);
	st->gpio_in |= BIT(offset);

	ret = st->ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_OUT_EN, st->gpio_out);
	अगर (ret < 0)
		जाओ err_unlock;

	ret = st->ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_IN_EN, st->gpio_in);

err_unlock:
	mutex_unlock(&st->gpio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5592r_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा ad5592r_state *st = gpiochip_get_data(chip);
	पूर्णांक ret;

	mutex_lock(&st->gpio_lock);

	अगर (value)
		st->gpio_val |= BIT(offset);
	अन्यथा
		st->gpio_val &= ~BIT(offset);

	st->gpio_in &= ~BIT(offset);
	st->gpio_out |= BIT(offset);

	ret = st->ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_SET, st->gpio_val);
	अगर (ret < 0)
		जाओ err_unlock;

	ret = st->ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_OUT_EN, st->gpio_out);
	अगर (ret < 0)
		जाओ err_unlock;

	ret = st->ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_IN_EN, st->gpio_in);

err_unlock:
	mutex_unlock(&st->gpio_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5592r_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा ad5592r_state *st = gpiochip_get_data(chip);

	अगर (!(st->gpio_map & BIT(offset))) अणु
		dev_err(st->dev, "GPIO %d is reserved by alternate function\n",
			offset);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad5592r_gpio_init(काष्ठा ad5592r_state *st)
अणु
	अगर (!st->gpio_map)
		वापस 0;

	st->gpiochip.label = dev_name(st->dev);
	st->gpiochip.base = -1;
	st->gpiochip.ngpio = 8;
	st->gpiochip.parent = st->dev;
	st->gpiochip.can_sleep = true;
	st->gpiochip.direction_input = ad5592r_gpio_direction_input;
	st->gpiochip.direction_output = ad5592r_gpio_direction_output;
	st->gpiochip.get = ad5592r_gpio_get;
	st->gpiochip.set = ad5592r_gpio_set;
	st->gpiochip.request = ad5592r_gpio_request;
	st->gpiochip.owner = THIS_MODULE;

	mutex_init(&st->gpio_lock);

	वापस gpiochip_add_data(&st->gpiochip, st);
पूर्ण

अटल व्योम ad5592r_gpio_cleanup(काष्ठा ad5592r_state *st)
अणु
	अगर (st->gpio_map)
		gpiochip_हटाओ(&st->gpiochip);
पूर्ण

अटल पूर्णांक ad5592r_reset(काष्ठा ad5592r_state *st)
अणु
	काष्ठा gpio_desc *gpio;

	gpio = devm_gpiod_get_optional(st->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	अगर (gpio) अणु
		udelay(1);
		gpiod_set_value(gpio, 1);
	पूर्ण अन्यथा अणु
		mutex_lock(&st->lock);
		/* Writing this magic value resets the device */
		st->ops->reg_ग_लिखो(st, AD5592R_REG_RESET, 0xdac);
		mutex_unlock(&st->lock);
	पूर्ण

	udelay(250);

	वापस 0;
पूर्ण

अटल पूर्णांक ad5592r_get_vref(काष्ठा ad5592r_state *st)
अणु
	पूर्णांक ret;

	अगर (st->reg) अणु
		ret = regulator_get_voltage(st->reg);
		अगर (ret < 0)
			वापस ret;

		वापस ret / 1000;
	पूर्ण अन्यथा अणु
		वापस 2500;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5592r_set_channel_modes(काष्ठा ad5592r_state *st)
अणु
	स्थिर काष्ठा ad5592r_rw_ops *ops = st->ops;
	पूर्णांक ret;
	अचिन्हित i;
	u8 pullकरोwn = 0, tristate = 0, dac = 0, adc = 0;
	u16 पढ़ो_back;

	क्रम (i = 0; i < st->num_channels; i++) अणु
		चयन (st->channel_modes[i]) अणु
		हाल CH_MODE_DAC:
			dac |= BIT(i);
			अवरोध;

		हाल CH_MODE_ADC:
			adc |= BIT(i);
			अवरोध;

		हाल CH_MODE_DAC_AND_ADC:
			dac |= BIT(i);
			adc |= BIT(i);
			अवरोध;

		हाल CH_MODE_GPIO:
			st->gpio_map |= BIT(i);
			st->gpio_in |= BIT(i); /* Default to input */
			अवरोध;

		हाल CH_MODE_UNUSED:
		शेष:
			चयन (st->channel_ofख_स्थितिe[i]) अणु
			हाल CH_OFFSTATE_OUT_TRISTATE:
				tristate |= BIT(i);
				अवरोध;

			हाल CH_OFFSTATE_OUT_LOW:
				st->gpio_out |= BIT(i);
				अवरोध;

			हाल CH_OFFSTATE_OUT_HIGH:
				st->gpio_out |= BIT(i);
				st->gpio_val |= BIT(i);
				अवरोध;

			हाल CH_OFFSTATE_PULLDOWN:
			शेष:
				pullकरोwn |= BIT(i);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_lock(&st->lock);

	/* Pull करोwn unused pins to GND */
	ret = ops->reg_ग_लिखो(st, AD5592R_REG_PULLDOWN, pullकरोwn);
	अगर (ret)
		जाओ err_unlock;

	ret = ops->reg_ग_लिखो(st, AD5592R_REG_TRISTATE, tristate);
	अगर (ret)
		जाओ err_unlock;

	/* Configure pins that we use */
	ret = ops->reg_ग_लिखो(st, AD5592R_REG_DAC_EN, dac);
	अगर (ret)
		जाओ err_unlock;

	ret = ops->reg_ग_लिखो(st, AD5592R_REG_ADC_EN, adc);
	अगर (ret)
		जाओ err_unlock;

	ret = ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_SET, st->gpio_val);
	अगर (ret)
		जाओ err_unlock;

	ret = ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_OUT_EN, st->gpio_out);
	अगर (ret)
		जाओ err_unlock;

	ret = ops->reg_ग_लिखो(st, AD5592R_REG_GPIO_IN_EN, st->gpio_in);
	अगर (ret)
		जाओ err_unlock;

	/* Verअगरy that we can पढ़ो back at least one रेजिस्टर */
	ret = ops->reg_पढ़ो(st, AD5592R_REG_ADC_EN, &पढ़ो_back);
	अगर (!ret && (पढ़ो_back & 0xff) != adc)
		ret = -EIO;

err_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5592r_reset_channel_modes(काष्ठा ad5592r_state *st)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(st->channel_modes); i++)
		st->channel_modes[i] = CH_MODE_UNUSED;

	वापस ad5592r_set_channel_modes(st);
पूर्ण

अटल पूर्णांक ad5592r_ग_लिखो_raw(काष्ठा iio_dev *iio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ad5592r_state *st = iio_priv(iio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:

		अगर (val >= (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		अगर (!chan->output)
			वापस -EINVAL;

		mutex_lock(&st->lock);
		ret = st->ops->ग_लिखो_dac(st, chan->channel, val);
		अगर (!ret)
			st->cached_dac[chan->channel] = val;
		mutex_unlock(&st->lock);
		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_VOLTAGE) अणु
			bool gain;

			अगर (val == st->scale_avail[0][0] &&
				val2 == st->scale_avail[0][1])
				gain = false;
			अन्यथा अगर (val == st->scale_avail[1][0] &&
				 val2 == st->scale_avail[1][1])
				gain = true;
			अन्यथा
				वापस -EINVAL;

			mutex_lock(&st->lock);

			ret = st->ops->reg_पढ़ो(st, AD5592R_REG_CTRL,
						&st->cached_gp_ctrl);
			अगर (ret < 0) अणु
				mutex_unlock(&st->lock);
				वापस ret;
			पूर्ण

			अगर (chan->output) अणु
				अगर (gain)
					st->cached_gp_ctrl |=
						AD5592R_REG_CTRL_DAC_RANGE;
				अन्यथा
					st->cached_gp_ctrl &=
						~AD5592R_REG_CTRL_DAC_RANGE;
			पूर्ण अन्यथा अणु
				अगर (gain)
					st->cached_gp_ctrl |=
						AD5592R_REG_CTRL_ADC_RANGE;
				अन्यथा
					st->cached_gp_ctrl &=
						~AD5592R_REG_CTRL_ADC_RANGE;
			पूर्ण

			ret = st->ops->reg_ग_लिखो(st, AD5592R_REG_CTRL,
						 st->cached_gp_ctrl);
			mutex_unlock(&st->lock);

			वापस ret;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad5592r_पढ़ो_raw(काष्ठा iio_dev *iio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	काष्ठा ad5592r_state *st = iio_priv(iio_dev);
	u16 पढ़ो_val;
	पूर्णांक ret, mult;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (!chan->output) अणु
			mutex_lock(&st->lock);
			ret = st->ops->पढ़ो_adc(st, chan->channel, &पढ़ो_val);
			mutex_unlock(&st->lock);
			अगर (ret)
				वापस ret;

			अगर ((पढ़ो_val >> 12 & 0x7) != (chan->channel & 0x7)) अणु
				dev_err(st->dev, "Error while reading channel %u\n",
						chan->channel);
				वापस -EIO;
			पूर्ण

			पढ़ो_val &= GENMASK(11, 0);

		पूर्ण अन्यथा अणु
			mutex_lock(&st->lock);
			पढ़ो_val = st->cached_dac[chan->channel];
			mutex_unlock(&st->lock);
		पूर्ण

		dev_dbg(st->dev, "Channel %u read: 0x%04hX\n",
				chan->channel, पढ़ो_val);

		*val = (पूर्णांक) पढ़ो_val;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = ad5592r_get_vref(st);

		अगर (chan->type == IIO_TEMP) अणु
			s64 पंचांगp = *val * (3767897513LL / 25LL);
			*val = भाग_s64_rem(पंचांगp, 1000000000LL, val2);

			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण

		mutex_lock(&st->lock);

		अगर (chan->output)
			mult = !!(st->cached_gp_ctrl &
				AD5592R_REG_CTRL_DAC_RANGE);
		अन्यथा
			mult = !!(st->cached_gp_ctrl &
				AD5592R_REG_CTRL_ADC_RANGE);

		mutex_unlock(&st->lock);

		*val *= ++mult;

		*val2 = chan->scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		ret = ad5592r_get_vref(st);

		mutex_lock(&st->lock);

		अगर (st->cached_gp_ctrl & AD5592R_REG_CTRL_ADC_RANGE)
			*val = (-34365 * 25) / ret;
		अन्यथा
			*val = (-75365 * 25) / ret;

		mutex_unlock(&st->lock);

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5592r_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				 काष्ठा iio_chan_spec स्थिर *chan, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस IIO_VAL_INT_PLUS_न_अंकO;

	शेष:
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5592r_info = अणु
	.पढ़ो_raw = ad5592r_पढ़ो_raw,
	.ग_लिखो_raw = ad5592r_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = ad5592r_ग_लिखो_raw_get_fmt,
पूर्ण;

अटल sमाप_प्रकार ad5592r_show_scale_available(काष्ठा iio_dev *iio_dev,
					   uपूर्णांकptr_t निजी,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   अक्षर *buf)
अणु
	काष्ठा ad5592r_state *st = iio_priv(iio_dev);

	वापस प्र_लिखो(buf, "%d.%09u %d.%09u\n",
		st->scale_avail[0][0], st->scale_avail[0][1],
		st->scale_avail[1][0], st->scale_avail[1][1]);
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5592r_ext_info[] = अणु
	अणु
	 .name = "scale_available",
	 .पढ़ो = ad5592r_show_scale_available,
	 .shared = IIO_SHARED_BY_TYPE,
	 पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम ad5592r_setup_channel(काष्ठा iio_dev *iio_dev,
		काष्ठा iio_chan_spec *chan, bool output, अचिन्हित id)
अणु
	chan->type = IIO_VOLTAGE;
	chan->indexed = 1;
	chan->output = output;
	chan->channel = id;
	chan->info_mask_separate = BIT(IIO_CHAN_INFO_RAW);
	chan->info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE);
	chan->scan_type.sign = 'u';
	chan->scan_type.realbits = 12;
	chan->scan_type.storagebits = 16;
	chan->ext_info = ad5592r_ext_info;
पूर्ण

अटल पूर्णांक ad5592r_alloc_channels(काष्ठा iio_dev *iio_dev)
अणु
	काष्ठा ad5592r_state *st = iio_priv(iio_dev);
	अचिन्हित i, curr_channel = 0,
		 num_channels = st->num_channels;
	काष्ठा iio_chan_spec *channels;
	काष्ठा fwnode_handle *child;
	u32 reg, पंचांगp;
	पूर्णांक ret;

	device_क्रम_each_child_node(st->dev, child) अणु
		ret = fwnode_property_पढ़ो_u32(child, "reg", &reg);
		अगर (ret || reg >= ARRAY_SIZE(st->channel_modes))
			जारी;

		ret = fwnode_property_पढ़ो_u32(child, "adi,mode", &पंचांगp);
		अगर (!ret)
			st->channel_modes[reg] = पंचांगp;

		fwnode_property_पढ़ो_u32(child, "adi,off-state", &पंचांगp);
		अगर (!ret)
			st->channel_ofख_स्थितिe[reg] = पंचांगp;
	पूर्ण

	channels = devm_kसुस्मृति(st->dev,
			1 + 2 * num_channels, माप(*channels),
			GFP_KERNEL);
	अगर (!channels)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_channels; i++) अणु
		चयन (st->channel_modes[i]) अणु
		हाल CH_MODE_DAC:
			ad5592r_setup_channel(iio_dev, &channels[curr_channel],
					true, i);
			curr_channel++;
			अवरोध;

		हाल CH_MODE_ADC:
			ad5592r_setup_channel(iio_dev, &channels[curr_channel],
					false, i);
			curr_channel++;
			अवरोध;

		हाल CH_MODE_DAC_AND_ADC:
			ad5592r_setup_channel(iio_dev, &channels[curr_channel],
					true, i);
			curr_channel++;
			ad5592r_setup_channel(iio_dev, &channels[curr_channel],
					false, i);
			curr_channel++;
			अवरोध;

		शेष:
			जारी;
		पूर्ण
	पूर्ण

	channels[curr_channel].type = IIO_TEMP;
	channels[curr_channel].channel = 8;
	channels[curr_channel].info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				   BIT(IIO_CHAN_INFO_SCALE) |
				   BIT(IIO_CHAN_INFO_OFFSET);
	curr_channel++;

	iio_dev->num_channels = curr_channel;
	iio_dev->channels = channels;

	वापस 0;
पूर्ण

अटल व्योम ad5592r_init_scales(काष्ठा ad5592r_state *st, पूर्णांक vref_mV)
अणु
	s64 पंचांगp = (s64)vref_mV * 1000000000LL >> 12;

	st->scale_avail[0][0] =
		भाग_s64_rem(पंचांगp, 1000000000LL, &st->scale_avail[0][1]);
	st->scale_avail[1][0] =
		भाग_s64_rem(पंचांगp * 2, 1000000000LL, &st->scale_avail[1][1]);
पूर्ण

पूर्णांक ad5592r_probe(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर काष्ठा ad5592r_rw_ops *ops)
अणु
	काष्ठा iio_dev *iio_dev;
	काष्ठा ad5592r_state *st;
	पूर्णांक ret;

	iio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!iio_dev)
		वापस -ENOMEM;

	st = iio_priv(iio_dev);
	st->dev = dev;
	st->ops = ops;
	st->num_channels = 8;
	dev_set_drvdata(dev, iio_dev);

	st->reg = devm_regulator_get_optional(dev, "vref");
	अगर (IS_ERR(st->reg)) अणु
		अगर ((PTR_ERR(st->reg) != -ENODEV) && dev->of_node)
			वापस PTR_ERR(st->reg);

		st->reg = शून्य;
	पूर्ण अन्यथा अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	iio_dev->name = name;
	iio_dev->info = &ad5592r_info;
	iio_dev->modes = INDIO_सूचीECT_MODE;

	mutex_init(&st->lock);

	ad5592r_init_scales(st, ad5592r_get_vref(st));

	ret = ad5592r_reset(st);
	अगर (ret)
		जाओ error_disable_reg;

	ret = ops->reg_ग_लिखो(st, AD5592R_REG_PD,
		     (st->reg == शून्य) ? AD5592R_REG_PD_EN_REF : 0);
	अगर (ret)
		जाओ error_disable_reg;

	ret = ad5592r_alloc_channels(iio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	ret = ad5592r_set_channel_modes(st);
	अगर (ret)
		जाओ error_reset_ch_modes;

	ret = iio_device_रेजिस्टर(iio_dev);
	अगर (ret)
		जाओ error_reset_ch_modes;

	ret = ad5592r_gpio_init(st);
	अगर (ret)
		जाओ error_dev_unरेजिस्टर;

	वापस 0;

error_dev_unरेजिस्टर:
	iio_device_unरेजिस्टर(iio_dev);

error_reset_ch_modes:
	ad5592r_reset_channel_modes(st);

error_disable_reg:
	अगर (st->reg)
		regulator_disable(st->reg);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ad5592r_probe);

पूर्णांक ad5592r_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *iio_dev = dev_get_drvdata(dev);
	काष्ठा ad5592r_state *st = iio_priv(iio_dev);

	iio_device_unरेजिस्टर(iio_dev);
	ad5592r_reset_channel_modes(st);
	ad5592r_gpio_cleanup(st);

	अगर (st->reg)
		regulator_disable(st->reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ad5592r_हटाओ);

MODULE_AUTHOR("Paul Cercueil <paul.cercueil@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5592R multi-channel converters");
MODULE_LICENSE("GPL v2");
