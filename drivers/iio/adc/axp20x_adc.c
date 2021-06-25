<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ADC driver क्रम AXP20X and AXP22X PMICs
 *
 * Copyright (c) 2016 Free Electrons NextThing Co.
 *	Quentin Schulz <quentin.schulz@मुक्त-electrons.com>
 */

#समावेश <linux/completion.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/machine.h>
#समावेश <linux/mfd/axp20x.h>

#घोषणा AXP20X_ADC_EN1_MASK			GENMASK(7, 0)

#घोषणा AXP20X_ADC_EN2_MASK			(GENMASK(3, 2) | BIT(7))
#घोषणा AXP22X_ADC_EN1_MASK			(GENMASK(7, 5) | BIT(0))

#घोषणा AXP20X_GPIO10_IN_RANGE_GPIO0		BIT(0)
#घोषणा AXP20X_GPIO10_IN_RANGE_GPIO1		BIT(1)
#घोषणा AXP20X_GPIO10_IN_RANGE_GPIO0_VAL(x)	((x) & BIT(0))
#घोषणा AXP20X_GPIO10_IN_RANGE_GPIO1_VAL(x)	(((x) & BIT(0)) << 1)

#घोषणा AXP20X_ADC_RATE_MASK			GENMASK(7, 6)
#घोषणा AXP813_V_I_ADC_RATE_MASK		GENMASK(5, 4)
#घोषणा AXP813_ADC_RATE_MASK			(AXP20X_ADC_RATE_MASK | AXP813_V_I_ADC_RATE_MASK)
#घोषणा AXP20X_ADC_RATE_HZ(x)			((ilog2((x) / 25) << 6) & AXP20X_ADC_RATE_MASK)
#घोषणा AXP22X_ADC_RATE_HZ(x)			((ilog2((x) / 100) << 6) & AXP20X_ADC_RATE_MASK)
#घोषणा AXP813_TS_GPIO0_ADC_RATE_HZ(x)		AXP20X_ADC_RATE_HZ(x)
#घोषणा AXP813_V_I_ADC_RATE_HZ(x)		((ilog2((x) / 100) << 4) & AXP813_V_I_ADC_RATE_MASK)
#घोषणा AXP813_ADC_RATE_HZ(x)			(AXP20X_ADC_RATE_HZ(x) | AXP813_V_I_ADC_RATE_HZ(x))

#घोषणा AXP20X_ADC_CHANNEL(_channel, _name, _type, _reg)	\
	अणु							\
		.type = _type,					\
		.indexed = 1,					\
		.channel = _channel,				\
		.address = _reg,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
				      BIT(IIO_CHAN_INFO_SCALE),	\
		.datasheet_name = _name,			\
	पूर्ण

#घोषणा AXP20X_ADC_CHANNEL_OFFSET(_channel, _name, _type, _reg) \
	अणु							\
		.type = _type,					\
		.indexed = 1,					\
		.channel = _channel,				\
		.address = _reg,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |	\
				      BIT(IIO_CHAN_INFO_SCALE) |\
				      BIT(IIO_CHAN_INFO_OFFSET),\
		.datasheet_name = _name,			\
	पूर्ण

काष्ठा axp_data;

काष्ठा axp20x_adc_iio अणु
	काष्ठा regmap		*regmap;
	स्थिर काष्ठा axp_data	*data;
पूर्ण;

क्रमागत axp20x_adc_channel_v अणु
	AXP20X_ACIN_V = 0,
	AXP20X_VBUS_V,
	AXP20X_TS_IN,
	AXP20X_GPIO0_V,
	AXP20X_GPIO1_V,
	AXP20X_IPSOUT_V,
	AXP20X_BATT_V,
पूर्ण;

क्रमागत axp20x_adc_channel_i अणु
	AXP20X_ACIN_I = 0,
	AXP20X_VBUS_I,
	AXP20X_BATT_CHRG_I,
	AXP20X_BATT_DISCHRG_I,
पूर्ण;

क्रमागत axp22x_adc_channel_v अणु
	AXP22X_TS_IN = 0,
	AXP22X_BATT_V,
पूर्ण;

क्रमागत axp22x_adc_channel_i अणु
	AXP22X_BATT_CHRG_I = 1,
	AXP22X_BATT_DISCHRG_I,
पूर्ण;

क्रमागत axp813_adc_channel_v अणु
	AXP813_TS_IN = 0,
	AXP813_GPIO0_V,
	AXP813_BATT_V,
पूर्ण;

अटल काष्ठा iio_map axp20x_maps[] = अणु
	अणु
		.consumer_dev_name = "axp20x-usb-power-supply",
		.consumer_channel = "vbus_v",
		.adc_channel_label = "vbus_v",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-usb-power-supply",
		.consumer_channel = "vbus_i",
		.adc_channel_label = "vbus_i",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-ac-power-supply",
		.consumer_channel = "acin_v",
		.adc_channel_label = "acin_v",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-ac-power-supply",
		.consumer_channel = "acin_i",
		.adc_channel_label = "acin_i",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-battery-power-supply",
		.consumer_channel = "batt_v",
		.adc_channel_label = "batt_v",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-battery-power-supply",
		.consumer_channel = "batt_chrg_i",
		.adc_channel_label = "batt_chrg_i",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-battery-power-supply",
		.consumer_channel = "batt_dischrg_i",
		.adc_channel_label = "batt_dischrg_i",
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;

अटल काष्ठा iio_map axp22x_maps[] = अणु
	अणु
		.consumer_dev_name = "axp20x-battery-power-supply",
		.consumer_channel = "batt_v",
		.adc_channel_label = "batt_v",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-battery-power-supply",
		.consumer_channel = "batt_chrg_i",
		.adc_channel_label = "batt_chrg_i",
	पूर्ण, अणु
		.consumer_dev_name = "axp20x-battery-power-supply",
		.consumer_channel = "batt_dischrg_i",
		.adc_channel_label = "batt_dischrg_i",
	पूर्ण, अणु /* sentinel */ पूर्ण
पूर्ण;

/*
 * Channels are mapped by physical प्रणाली. Their channels share the same index.
 * i.e. acin_i is in_current0_raw and acin_v is in_voltage0_raw.
 * The only exception is क्रम the battery. batt_v will be in_voltage6_raw and
 * अक्षरge current in_current6_raw and disअक्षरge current will be in_current7_raw.
 */
अटल स्थिर काष्ठा iio_chan_spec axp20x_adc_channels[] = अणु
	AXP20X_ADC_CHANNEL(AXP20X_ACIN_V, "acin_v", IIO_VOLTAGE,
			   AXP20X_ACIN_V_ADC_H),
	AXP20X_ADC_CHANNEL(AXP20X_ACIN_I, "acin_i", IIO_CURRENT,
			   AXP20X_ACIN_I_ADC_H),
	AXP20X_ADC_CHANNEL(AXP20X_VBUS_V, "vbus_v", IIO_VOLTAGE,
			   AXP20X_VBUS_V_ADC_H),
	AXP20X_ADC_CHANNEL(AXP20X_VBUS_I, "vbus_i", IIO_CURRENT,
			   AXP20X_VBUS_I_ADC_H),
	अणु
		.type = IIO_TEMP,
		.address = AXP20X_TEMP_ADC_H,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "pmic_temp",
	पूर्ण,
	AXP20X_ADC_CHANNEL_OFFSET(AXP20X_GPIO0_V, "gpio0_v", IIO_VOLTAGE,
				  AXP20X_GPIO0_V_ADC_H),
	AXP20X_ADC_CHANNEL_OFFSET(AXP20X_GPIO1_V, "gpio1_v", IIO_VOLTAGE,
				  AXP20X_GPIO1_V_ADC_H),
	AXP20X_ADC_CHANNEL(AXP20X_IPSOUT_V, "ipsout_v", IIO_VOLTAGE,
			   AXP20X_IPSOUT_V_HIGH_H),
	AXP20X_ADC_CHANNEL(AXP20X_BATT_V, "batt_v", IIO_VOLTAGE,
			   AXP20X_BATT_V_H),
	AXP20X_ADC_CHANNEL(AXP20X_BATT_CHRG_I, "batt_chrg_i", IIO_CURRENT,
			   AXP20X_BATT_CHRG_I_H),
	AXP20X_ADC_CHANNEL(AXP20X_BATT_DISCHRG_I, "batt_dischrg_i", IIO_CURRENT,
			   AXP20X_BATT_DISCHRG_I_H),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec axp22x_adc_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.address = AXP22X_PMIC_TEMP_H,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "pmic_temp",
	पूर्ण,
	AXP20X_ADC_CHANNEL(AXP22X_BATT_V, "batt_v", IIO_VOLTAGE,
			   AXP20X_BATT_V_H),
	AXP20X_ADC_CHANNEL(AXP22X_BATT_CHRG_I, "batt_chrg_i", IIO_CURRENT,
			   AXP20X_BATT_CHRG_I_H),
	AXP20X_ADC_CHANNEL(AXP22X_BATT_DISCHRG_I, "batt_dischrg_i", IIO_CURRENT,
			   AXP20X_BATT_DISCHRG_I_H),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec axp813_adc_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.address = AXP22X_PMIC_TEMP_H,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.datasheet_name = "pmic_temp",
	पूर्ण,
	AXP20X_ADC_CHANNEL(AXP813_GPIO0_V, "gpio0_v", IIO_VOLTAGE,
			   AXP288_GP_ADC_H),
	AXP20X_ADC_CHANNEL(AXP813_BATT_V, "batt_v", IIO_VOLTAGE,
			   AXP20X_BATT_V_H),
	AXP20X_ADC_CHANNEL(AXP22X_BATT_CHRG_I, "batt_chrg_i", IIO_CURRENT,
			   AXP20X_BATT_CHRG_I_H),
	AXP20X_ADC_CHANNEL(AXP22X_BATT_DISCHRG_I, "batt_dischrg_i", IIO_CURRENT,
			   AXP20X_BATT_DISCHRG_I_H),
पूर्ण;

अटल पूर्णांक axp20x_adc_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	काष्ठा axp20x_adc_iio *info = iio_priv(indio_dev);
	पूर्णांक size = 12;

	/*
	 * N.B.:  Unlike the Chinese datasheets tell, the अक्षरging current is
	 * stored on 12 bits, not 13 bits. Only disअक्षरging current is on 13
	 * bits.
	 */
	अगर (chan->type == IIO_CURRENT && chan->channel == AXP20X_BATT_DISCHRG_I)
		size = 13;
	अन्यथा
		size = 12;

	*val = axp20x_पढ़ो_variable_width(info->regmap, chan->address, size);
	अगर (*val < 0)
		वापस *val;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक axp22x_adc_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	काष्ठा axp20x_adc_iio *info = iio_priv(indio_dev);
	पूर्णांक size;

	/*
	 * N.B.: Unlike the Chinese datasheets tell, the अक्षरging current is
	 * stored on 12 bits, not 13 bits. Only disअक्षरging current is on 13
	 * bits.
	 */
	अगर (chan->type == IIO_CURRENT && chan->channel == AXP22X_BATT_DISCHRG_I)
		size = 13;
	अन्यथा
		size = 12;

	*val = axp20x_पढ़ो_variable_width(info->regmap, chan->address, size);
	अगर (*val < 0)
		वापस *val;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक axp813_adc_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	काष्ठा axp20x_adc_iio *info = iio_priv(indio_dev);

	*val = axp20x_पढ़ो_variable_width(info->regmap, chan->address, 12);
	अगर (*val < 0)
		वापस *val;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक axp20x_adc_scale_voltage(पूर्णांक channel, पूर्णांक *val, पूर्णांक *val2)
अणु
	चयन (channel) अणु
	हाल AXP20X_ACIN_V:
	हाल AXP20X_VBUS_V:
		*val = 1;
		*val2 = 700000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल AXP20X_GPIO0_V:
	हाल AXP20X_GPIO1_V:
		*val = 0;
		*val2 = 500000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल AXP20X_BATT_V:
		*val = 1;
		*val2 = 100000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल AXP20X_IPSOUT_V:
		*val = 1;
		*val2 = 400000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp813_adc_scale_voltage(पूर्णांक channel, पूर्णांक *val, पूर्णांक *val2)
अणु
	चयन (channel) अणु
	हाल AXP813_GPIO0_V:
		*val = 0;
		*val2 = 800000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल AXP813_BATT_V:
		*val = 1;
		*val2 = 100000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp20x_adc_scale_current(पूर्णांक channel, पूर्णांक *val, पूर्णांक *val2)
अणु
	चयन (channel) अणु
	हाल AXP20X_ACIN_I:
		*val = 0;
		*val2 = 625000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल AXP20X_VBUS_I:
		*val = 0;
		*val2 = 375000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल AXP20X_BATT_DISCHRG_I:
	हाल AXP20X_BATT_CHRG_I:
		*val = 0;
		*val2 = 500000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp20x_adc_scale(काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2)
अणु
	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		वापस axp20x_adc_scale_voltage(chan->channel, val, val2);

	हाल IIO_CURRENT:
		वापस axp20x_adc_scale_current(chan->channel, val, val2);

	हाल IIO_TEMP:
		*val = 100;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp22x_adc_scale(काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2)
अणु
	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		अगर (chan->channel != AXP22X_BATT_V)
			वापस -EINVAL;

		*val = 1;
		*val2 = 100000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CURRENT:
		*val = 0;
		*val2 = 500000;
		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_TEMP:
		*val = 100;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp813_adc_scale(काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2)
अणु
	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		वापस axp813_adc_scale_voltage(chan->channel, val, val2);

	हाल IIO_CURRENT:
		*val = 1;
		वापस IIO_VAL_INT;

	हाल IIO_TEMP:
		*val = 100;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp20x_adc_offset_voltage(काष्ठा iio_dev *indio_dev, पूर्णांक channel,
				     पूर्णांक *val)
अणु
	काष्ठा axp20x_adc_iio *info = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, AXP20X_GPIO10_IN_RANGE, val);
	अगर (ret < 0)
		वापस ret;

	चयन (channel) अणु
	हाल AXP20X_GPIO0_V:
		*val &= AXP20X_GPIO10_IN_RANGE_GPIO0;
		अवरोध;

	हाल AXP20X_GPIO1_V:
		*val &= AXP20X_GPIO10_IN_RANGE_GPIO1;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	*val = *val ? 700000 : 0;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक axp20x_adc_offset(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		वापस axp20x_adc_offset_voltage(indio_dev, chan->channel, val);

	हाल IIO_TEMP:
		*val = -1447;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp20x_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OFFSET:
		वापस axp20x_adc_offset(indio_dev, chan, val);

	हाल IIO_CHAN_INFO_SCALE:
		वापस axp20x_adc_scale(chan, val, val2);

	हाल IIO_CHAN_INFO_RAW:
		वापस axp20x_adc_raw(indio_dev, chan, val);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp22x_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -2677;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		वापस axp22x_adc_scale(chan, val, val2);

	हाल IIO_CHAN_INFO_RAW:
		वापस axp22x_adc_raw(indio_dev, chan, val);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp813_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -2667;
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		वापस axp813_adc_scale(chan, val, val2);

	हाल IIO_CHAN_INFO_RAW:
		वापस axp813_adc_raw(indio_dev, chan, val);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक axp20x_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा axp20x_adc_iio *info = iio_priv(indio_dev);
	अचिन्हित पूर्णांक reg, regval;

	/*
	 * The AXP20X PMIC allows the user to choose between 0V and 0.7V offsets
	 * क्रम (independently) GPIO0 and GPIO1 when in ADC mode.
	 */
	अगर (mask != IIO_CHAN_INFO_OFFSET)
		वापस -EINVAL;

	अगर (val != 0 && val != 700000)
		वापस -EINVAL;

	val = val ? 1 : 0;

	चयन (chan->channel) अणु
	हाल AXP20X_GPIO0_V:
		reg = AXP20X_GPIO10_IN_RANGE_GPIO0;
		regval = AXP20X_GPIO10_IN_RANGE_GPIO0_VAL(val);
		अवरोध;

	हाल AXP20X_GPIO1_V:
		reg = AXP20X_GPIO10_IN_RANGE_GPIO1;
		regval = AXP20X_GPIO10_IN_RANGE_GPIO1_VAL(val);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(info->regmap, AXP20X_GPIO10_IN_RANGE, reg,
				  regval);
पूर्ण

अटल स्थिर काष्ठा iio_info axp20x_adc_iio_info = अणु
	.पढ़ो_raw = axp20x_पढ़ो_raw,
	.ग_लिखो_raw = axp20x_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_info axp22x_adc_iio_info = अणु
	.पढ़ो_raw = axp22x_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_info axp813_adc_iio_info = अणु
	.पढ़ो_raw = axp813_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक axp20x_adc_rate(काष्ठा axp20x_adc_iio *info, पूर्णांक rate)
अणु
	वापस regmap_update_bits(info->regmap, AXP20X_ADC_RATE,
				  AXP20X_ADC_RATE_MASK,
				  AXP20X_ADC_RATE_HZ(rate));
पूर्ण

अटल पूर्णांक axp22x_adc_rate(काष्ठा axp20x_adc_iio *info, पूर्णांक rate)
अणु
	वापस regmap_update_bits(info->regmap, AXP20X_ADC_RATE,
				  AXP20X_ADC_RATE_MASK,
				  AXP22X_ADC_RATE_HZ(rate));
पूर्ण

अटल पूर्णांक axp813_adc_rate(काष्ठा axp20x_adc_iio *info, पूर्णांक rate)
अणु
	वापस regmap_update_bits(info->regmap, AXP813_ADC_RATE,
				 AXP813_ADC_RATE_MASK,
				 AXP813_ADC_RATE_HZ(rate));
पूर्ण

काष्ठा axp_data अणु
	स्थिर काष्ठा iio_info		*iio_info;
	पूर्णांक				num_channels;
	काष्ठा iio_chan_spec स्थिर	*channels;
	अचिन्हित दीर्घ			adc_en1_mask;
	पूर्णांक				(*adc_rate)(काष्ठा axp20x_adc_iio *info,
						    पूर्णांक rate);
	bool				adc_en2;
	काष्ठा iio_map			*maps;
पूर्ण;

अटल स्थिर काष्ठा axp_data axp20x_data = अणु
	.iio_info = &axp20x_adc_iio_info,
	.num_channels = ARRAY_SIZE(axp20x_adc_channels),
	.channels = axp20x_adc_channels,
	.adc_en1_mask = AXP20X_ADC_EN1_MASK,
	.adc_rate = axp20x_adc_rate,
	.adc_en2 = true,
	.maps = axp20x_maps,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp22x_data = अणु
	.iio_info = &axp22x_adc_iio_info,
	.num_channels = ARRAY_SIZE(axp22x_adc_channels),
	.channels = axp22x_adc_channels,
	.adc_en1_mask = AXP22X_ADC_EN1_MASK,
	.adc_rate = axp22x_adc_rate,
	.adc_en2 = false,
	.maps = axp22x_maps,
पूर्ण;

अटल स्थिर काष्ठा axp_data axp813_data = अणु
	.iio_info = &axp813_adc_iio_info,
	.num_channels = ARRAY_SIZE(axp813_adc_channels),
	.channels = axp813_adc_channels,
	.adc_en1_mask = AXP22X_ADC_EN1_MASK,
	.adc_rate = axp813_adc_rate,
	.adc_en2 = false,
	.maps = axp22x_maps,
पूर्ण;

अटल स्थिर काष्ठा of_device_id axp20x_adc_of_match[] = अणु
	अणु .compatible = "x-powers,axp209-adc", .data = (व्योम *)&axp20x_data, पूर्ण,
	अणु .compatible = "x-powers,axp221-adc", .data = (व्योम *)&axp22x_data, पूर्ण,
	अणु .compatible = "x-powers,axp813-adc", .data = (व्योम *)&axp813_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, axp20x_adc_of_match);

अटल स्थिर काष्ठा platक्रमm_device_id axp20x_adc_id_match[] = अणु
	अणु .name = "axp20x-adc", .driver_data = (kernel_uदीर्घ_t)&axp20x_data, पूर्ण,
	अणु .name = "axp22x-adc", .driver_data = (kernel_uदीर्घ_t)&axp22x_data, पूर्ण,
	अणु .name = "axp813-adc", .driver_data = (kernel_uदीर्घ_t)&axp813_data, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, axp20x_adc_id_match);

अटल पूर्णांक axp20x_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axp20x_adc_iio *info;
	काष्ठा iio_dev *indio_dev;
	काष्ठा axp20x_dev *axp20x_dev;
	पूर्णांक ret;

	axp20x_dev = dev_get_drvdata(pdev->dev.parent);

	indio_dev = devm_iio_device_alloc(&pdev->dev, माप(*info));
	अगर (!indio_dev)
		वापस -ENOMEM;

	info = iio_priv(indio_dev);
	platक्रमm_set_drvdata(pdev, indio_dev);

	info->regmap = axp20x_dev->regmap;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (!dev_fwnode(&pdev->dev)) अणु
		स्थिर काष्ठा platक्रमm_device_id *id;

		id = platक्रमm_get_device_id(pdev);
		info->data = (स्थिर काष्ठा axp_data *)id->driver_data;
	पूर्ण अन्यथा अणु
		काष्ठा device *dev = &pdev->dev;

		info->data = device_get_match_data(dev);
	पूर्ण

	indio_dev->name = platक्रमm_get_device_id(pdev)->name;
	indio_dev->info = info->data->iio_info;
	indio_dev->num_channels = info->data->num_channels;
	indio_dev->channels = info->data->channels;

	/* Enable the ADCs on IP */
	regmap_ग_लिखो(info->regmap, AXP20X_ADC_EN1, info->data->adc_en1_mask);

	अगर (info->data->adc_en2)
		/* Enable GPIO0/1 and पूर्णांकernal temperature ADCs */
		regmap_update_bits(info->regmap, AXP20X_ADC_EN2,
				   AXP20X_ADC_EN2_MASK, AXP20X_ADC_EN2_MASK);

	/* Configure ADCs rate */
	info->data->adc_rate(info, 100);

	ret = iio_map_array_रेजिस्टर(indio_dev, info->data->maps);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register IIO maps: %d\n", ret);
		जाओ fail_map;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not register the device\n");
		जाओ fail_रेजिस्टर;
	पूर्ण

	वापस 0;

fail_रेजिस्टर:
	iio_map_array_unरेजिस्टर(indio_dev);

fail_map:
	regmap_ग_लिखो(info->regmap, AXP20X_ADC_EN1, 0);

	अगर (info->data->adc_en2)
		regmap_ग_लिखो(info->regmap, AXP20X_ADC_EN2, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक axp20x_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iio_dev *indio_dev = platक्रमm_get_drvdata(pdev);
	काष्ठा axp20x_adc_iio *info = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_map_array_unरेजिस्टर(indio_dev);

	regmap_ग_लिखो(info->regmap, AXP20X_ADC_EN1, 0);

	अगर (info->data->adc_en2)
		regmap_ग_लिखो(info->regmap, AXP20X_ADC_EN2, 0);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver axp20x_adc_driver = अणु
	.driver = अणु
		.name = "axp20x-adc",
		.of_match_table = axp20x_adc_of_match,
	पूर्ण,
	.id_table = axp20x_adc_id_match,
	.probe = axp20x_probe,
	.हटाओ = axp20x_हटाओ,
पूर्ण;

module_platक्रमm_driver(axp20x_adc_driver);

MODULE_DESCRIPTION("ADC driver for AXP20X and AXP22X PMICs");
MODULE_AUTHOR("Quentin Schulz <quentin.schulz@free-electrons.com>");
MODULE_LICENSE("GPL");
