<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AFE4404 Heart Rate Monitors and Low-Cost Pulse Oximeters
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#समावेश "afe440x.h"

#घोषणा AFE4404_DRIVER_NAME		"afe4404"

/* AFE4404 रेजिस्टरs */
#घोषणा AFE4404_TIA_GAIN_SEP		0x20
#घोषणा AFE4404_TIA_GAIN		0x21
#घोषणा AFE4404_PROG_TG_STC		0x34
#घोषणा AFE4404_PROG_TG_ENDC		0x35
#घोषणा AFE4404_LED3LEDSTC		0x36
#घोषणा AFE4404_LED3LEDENDC		0x37
#घोषणा AFE4404_CLKDIV_PRF		0x39
#घोषणा AFE4404_OFFDAC			0x3a
#घोषणा AFE4404_DEC			0x3d
#घोषणा AFE4404_AVG_LED2_ALED2VAL	0x3f
#घोषणा AFE4404_AVG_LED1_ALED1VAL	0x40

/* AFE4404 CONTROL2 रेजिस्टर fields */
#घोषणा AFE440X_CONTROL2_OSC_ENABLE	BIT(9)

क्रमागत afe4404_fields अणु
	/* Gains */
	F_TIA_GAIN_SEP, F_TIA_CF_SEP,
	F_TIA_GAIN, TIA_CF,

	/* LED Current */
	F_ILED1, F_ILED2, F_ILED3,

	/* Offset DAC */
	F_OFFDAC_AMB2, F_OFFDAC_LED1, F_OFFDAC_AMB1, F_OFFDAC_LED2,

	/* sentinel */
	F_MAX_FIELDS
पूर्ण;

अटल स्थिर काष्ठा reg_field afe4404_reg_fields[] = अणु
	/* Gains */
	[F_TIA_GAIN_SEP]	= REG_FIELD(AFE4404_TIA_GAIN_SEP, 0, 2),
	[F_TIA_CF_SEP]		= REG_FIELD(AFE4404_TIA_GAIN_SEP, 3, 5),
	[F_TIA_GAIN]		= REG_FIELD(AFE4404_TIA_GAIN, 0, 2),
	[TIA_CF]		= REG_FIELD(AFE4404_TIA_GAIN, 3, 5),
	/* LED Current */
	[F_ILED1]		= REG_FIELD(AFE440X_LEDCNTRL, 0, 5),
	[F_ILED2]		= REG_FIELD(AFE440X_LEDCNTRL, 6, 11),
	[F_ILED3]		= REG_FIELD(AFE440X_LEDCNTRL, 12, 17),
	/* Offset DAC */
	[F_OFFDAC_AMB2]		= REG_FIELD(AFE4404_OFFDAC, 0, 4),
	[F_OFFDAC_LED1]		= REG_FIELD(AFE4404_OFFDAC, 5, 9),
	[F_OFFDAC_AMB1]		= REG_FIELD(AFE4404_OFFDAC, 10, 14),
	[F_OFFDAC_LED2]		= REG_FIELD(AFE4404_OFFDAC, 15, 19),
पूर्ण;

/**
 * काष्ठा afe4404_data - AFE4404 device instance data
 * @dev: Device काष्ठाure
 * @regmap: Register map of the device
 * @fields: Register fields of the device
 * @regulator: Poपूर्णांकer to the regulator क्रम the IC
 * @trig: IIO trigger क्रम this device
 * @irq: ADC_RDY line पूर्णांकerrupt number
 * @buffer: Used to स्थिरruct a scan to push to the iio buffer.
 */
काष्ठा afe4404_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *fields[F_MAX_FIELDS];
	काष्ठा regulator *regulator;
	काष्ठा iio_trigger *trig;
	पूर्णांक irq;
	s32 buffer[10] __aligned(8);
पूर्ण;

क्रमागत afe4404_chan_id अणु
	LED2 = 1,
	ALED2,
	LED1,
	ALED1,
	LED2_ALED2,
	LED1_ALED1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक afe4404_channel_values[] = अणु
	[LED2] = AFE440X_LED2VAL,
	[ALED2] = AFE440X_ALED2VAL,
	[LED1] = AFE440X_LED1VAL,
	[ALED1] = AFE440X_ALED1VAL,
	[LED2_ALED2] = AFE440X_LED2_ALED2VAL,
	[LED1_ALED1] = AFE440X_LED1_ALED1VAL,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक afe4404_channel_leds[] = अणु
	[LED2] = F_ILED2,
	[ALED2] = F_ILED3,
	[LED1] = F_ILED1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक afe4404_channel_offdacs[] = अणु
	[LED2] = F_OFFDAC_LED2,
	[ALED2] = F_OFFDAC_AMB2,
	[LED1] = F_OFFDAC_LED1,
	[ALED1] = F_OFFDAC_AMB1,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec afe4404_channels[] = अणु
	/* ADC values */
	AFE440X_INTENSITY_CHAN(LED2, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(ALED2, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(LED1, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(ALED1, BIT(IIO_CHAN_INFO_OFFSET)),
	AFE440X_INTENSITY_CHAN(LED2_ALED2, 0),
	AFE440X_INTENSITY_CHAN(LED1_ALED1, 0),
	/* LED current */
	AFE440X_CURRENT_CHAN(LED2),
	AFE440X_CURRENT_CHAN(ALED2),
	AFE440X_CURRENT_CHAN(LED1),
पूर्ण;

अटल स्थिर काष्ठा afe440x_val_table afe4404_res_table[] = अणु
	अणु .पूर्णांकeger = 500000, .fract = 0 पूर्ण,
	अणु .पूर्णांकeger = 250000, .fract = 0 पूर्ण,
	अणु .पूर्णांकeger = 100000, .fract = 0 पूर्ण,
	अणु .पूर्णांकeger = 50000, .fract = 0 पूर्ण,
	अणु .पूर्णांकeger = 25000, .fract = 0 पूर्ण,
	अणु .पूर्णांकeger = 10000, .fract = 0 पूर्ण,
	अणु .पूर्णांकeger = 1000000, .fract = 0 पूर्ण,
	अणु .पूर्णांकeger = 2000000, .fract = 0 पूर्ण,
पूर्ण;
AFE440X_TABLE_ATTR(in_पूर्णांकensity_resistance_available, afe4404_res_table);

अटल स्थिर काष्ठा afe440x_val_table afe4404_cap_table[] = अणु
	अणु .पूर्णांकeger = 0, .fract = 5000 पूर्ण,
	अणु .पूर्णांकeger = 0, .fract = 2500 पूर्ण,
	अणु .पूर्णांकeger = 0, .fract = 10000 पूर्ण,
	अणु .पूर्णांकeger = 0, .fract = 7500 पूर्ण,
	अणु .पूर्णांकeger = 0, .fract = 20000 पूर्ण,
	अणु .पूर्णांकeger = 0, .fract = 17500 पूर्ण,
	अणु .पूर्णांकeger = 0, .fract = 25000 पूर्ण,
	अणु .पूर्णांकeger = 0, .fract = 22500 पूर्ण,
पूर्ण;
AFE440X_TABLE_ATTR(in_पूर्णांकensity_capacitance_available, afe4404_cap_table);

अटल sमाप_प्रकार afe440x_show_रेजिस्टर(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	काष्ठा afe440x_attr *afe440x_attr = to_afe440x_attr(attr);
	अचिन्हित पूर्णांक reg_val;
	पूर्णांक vals[2];
	पूर्णांक ret;

	ret = regmap_field_पढ़ो(afe->fields[afe440x_attr->field], &reg_val);
	अगर (ret)
		वापस ret;

	अगर (reg_val >= afe440x_attr->table_size)
		वापस -EINVAL;

	vals[0] = afe440x_attr->val_table[reg_val].पूर्णांकeger;
	vals[1] = afe440x_attr->val_table[reg_val].fract;

	वापस iio_क्रमmat_value(buf, IIO_VAL_INT_PLUS_MICRO, 2, vals);
पूर्ण

अटल sमाप_प्रकार afe440x_store_रेजिस्टर(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	काष्ठा afe440x_attr *afe440x_attr = to_afe440x_attr(attr);
	पूर्णांक val, पूर्णांकeger, fract, ret;

	ret = iio_str_to_fixpoपूर्णांक(buf, 100000, &पूर्णांकeger, &fract);
	अगर (ret)
		वापस ret;

	क्रम (val = 0; val < afe440x_attr->table_size; val++)
		अगर (afe440x_attr->val_table[val].पूर्णांकeger == पूर्णांकeger &&
		    afe440x_attr->val_table[val].fract == fract)
			अवरोध;
	अगर (val == afe440x_attr->table_size)
		वापस -EINVAL;

	ret = regmap_field_ग_लिखो(afe->fields[afe440x_attr->field], val);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल AFE440X_ATTR(in_पूर्णांकensity1_resistance, F_TIA_GAIN_SEP, afe4404_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity1_capacitance, F_TIA_CF_SEP, afe4404_cap_table);

अटल AFE440X_ATTR(in_पूर्णांकensity2_resistance, F_TIA_GAIN_SEP, afe4404_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity2_capacitance, F_TIA_CF_SEP, afe4404_cap_table);

अटल AFE440X_ATTR(in_पूर्णांकensity3_resistance, F_TIA_GAIN, afe4404_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity3_capacitance, TIA_CF, afe4404_cap_table);

अटल AFE440X_ATTR(in_पूर्णांकensity4_resistance, F_TIA_GAIN, afe4404_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity4_capacitance, TIA_CF, afe4404_cap_table);

अटल काष्ठा attribute *afe440x_attributes[] = अणु
	&dev_attr_in_पूर्णांकensity_resistance_available.attr,
	&dev_attr_in_पूर्णांकensity_capacitance_available.attr,
	&afe440x_attr_in_पूर्णांकensity1_resistance.dev_attr.attr,
	&afe440x_attr_in_पूर्णांकensity1_capacitance.dev_attr.attr,
	&afe440x_attr_in_पूर्णांकensity2_resistance.dev_attr.attr,
	&afe440x_attr_in_पूर्णांकensity2_capacitance.dev_attr.attr,
	&afe440x_attr_in_पूर्णांकensity3_resistance.dev_attr.attr,
	&afe440x_attr_in_पूर्णांकensity3_capacitance.dev_attr.attr,
	&afe440x_attr_in_पूर्णांकensity4_resistance.dev_attr.attr,
	&afe440x_attr_in_पूर्णांकensity4_capacitance.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group afe440x_attribute_group = अणु
	.attrs = afe440x_attributes
पूर्ण;

अटल पूर्णांक afe4404_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	अचिन्हित पूर्णांक value_reg = afe4404_channel_values[chan->address];
	अचिन्हित पूर्णांक led_field = afe4404_channel_leds[chan->address];
	अचिन्हित पूर्णांक offdac_field = afe4404_channel_offdacs[chan->address];
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_RAW:
			ret = regmap_पढ़ो(afe->regmap, value_reg, val);
			अगर (ret)
				वापस ret;
			वापस IIO_VAL_INT;
		हाल IIO_CHAN_INFO_OFFSET:
			ret = regmap_field_पढ़ो(afe->fields[offdac_field], val);
			अगर (ret)
				वापस ret;
			वापस IIO_VAL_INT;
		पूर्ण
		अवरोध;
	हाल IIO_CURRENT:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_RAW:
			ret = regmap_field_पढ़ो(afe->fields[led_field], val);
			अगर (ret)
				वापस ret;
			वापस IIO_VAL_INT;
		हाल IIO_CHAN_INFO_SCALE:
			*val = 0;
			*val2 = 800000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक afe4404_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	अचिन्हित पूर्णांक led_field = afe4404_channel_leds[chan->address];
	अचिन्हित पूर्णांक offdac_field = afe4404_channel_offdacs[chan->address];

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_OFFSET:
			वापस regmap_field_ग_लिखो(afe->fields[offdac_field], val);
		पूर्ण
		अवरोध;
	हाल IIO_CURRENT:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_RAW:
			वापस regmap_field_ग_लिखो(afe->fields[led_field], val);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info afe4404_iio_info = अणु
	.attrs = &afe440x_attribute_group,
	.पढ़ो_raw = afe4404_पढ़ो_raw,
	.ग_लिखो_raw = afe4404_ग_लिखो_raw,
पूर्ण;

अटल irqवापस_t afe4404_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	पूर्णांक ret, bit, i = 0;

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = regmap_पढ़ो(afe->regmap, afe4404_channel_values[bit],
				  &afe->buffer[i++]);
		अगर (ret)
			जाओ err;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, afe->buffer,
					   pf->बारtamp);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops afe4404_trigger_ops = अणु
पूर्ण;

/* Default timings from data-sheet */
#घोषणा AFE4404_TIMING_PAIRS			\
	अणु AFE440X_PRPCOUNT,	39999	पूर्ण,	\
	अणु AFE440X_LED2LEDSTC,	0	पूर्ण,	\
	अणु AFE440X_LED2LEDENDC,	398	पूर्ण,	\
	अणु AFE440X_LED2STC,	80	पूर्ण,	\
	अणु AFE440X_LED2ENDC,	398	पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT0,	5600	पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT0,	5606	पूर्ण,	\
	अणु AFE440X_LED2CONVST,	5607	पूर्ण,	\
	अणु AFE440X_LED2CONVEND,	6066	पूर्ण,	\
	अणु AFE4404_LED3LEDSTC,	400	पूर्ण,	\
	अणु AFE4404_LED3LEDENDC,	798	पूर्ण,	\
	अणु AFE440X_ALED2STC,	480	पूर्ण,	\
	अणु AFE440X_ALED2ENDC,	798	पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT1,	6068	पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT1,	6074	पूर्ण,	\
	अणु AFE440X_ALED2CONVST,	6075	पूर्ण,	\
	अणु AFE440X_ALED2CONVEND,	6534	पूर्ण,	\
	अणु AFE440X_LED1LEDSTC,	800	पूर्ण,	\
	अणु AFE440X_LED1LEDENDC,	1198	पूर्ण,	\
	अणु AFE440X_LED1STC,	880	पूर्ण,	\
	अणु AFE440X_LED1ENDC,	1198	पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT2,	6536	पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT2,	6542	पूर्ण,	\
	अणु AFE440X_LED1CONVST,	6543	पूर्ण,	\
	अणु AFE440X_LED1CONVEND,	7003	पूर्ण,	\
	अणु AFE440X_ALED1STC,	1280	पूर्ण,	\
	अणु AFE440X_ALED1ENDC,	1598	पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT3,	7005	पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT3,	7011	पूर्ण,	\
	अणु AFE440X_ALED1CONVST,	7012	पूर्ण,	\
	अणु AFE440X_ALED1CONVEND,	7471	पूर्ण,	\
	अणु AFE440X_PDNCYCLESTC,	7671	पूर्ण,	\
	अणु AFE440X_PDNCYCLEENDC,	39199	पूर्ण

अटल स्थिर काष्ठा reg_sequence afe4404_reg_sequences[] = अणु
	AFE4404_TIMING_PAIRS,
	अणु AFE440X_CONTROL1, AFE440X_CONTROL1_TIMEREN पूर्ण,
	अणु AFE4404_TIA_GAIN_SEP, AFE440X_TIAGAIN_ENSEPGAIN पूर्ण,
	अणु AFE440X_CONTROL2, AFE440X_CONTROL2_OSC_ENABLE	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range afe4404_yes_ranges[] = अणु
	regmap_reg_range(AFE440X_LED2VAL, AFE440X_LED1_ALED1VAL),
	regmap_reg_range(AFE4404_AVG_LED2_ALED2VAL, AFE4404_AVG_LED1_ALED1VAL),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table afe4404_अस्थिर_table = अणु
	.yes_ranges = afe4404_yes_ranges,
	.n_yes_ranges = ARRAY_SIZE(afe4404_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config afe4404_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 24,

	.max_रेजिस्टर = AFE4404_AVG_LED1_ALED1VAL,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_table = &afe4404_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा of_device_id afe4404_of_match[] = अणु
	अणु .compatible = "ti,afe4404", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, afe4404_of_match);

अटल पूर्णांक __maybe_unused afe4404_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regmap_update_bits(afe->regmap, AFE440X_CONTROL2,
				 AFE440X_CONTROL2_PDN_AFE,
				 AFE440X_CONTROL2_PDN_AFE);
	अगर (ret)
		वापस ret;

	ret = regulator_disable(afe->regulator);
	अगर (ret) अणु
		dev_err(dev, "Unable to disable regulator\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused afe4404_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regulator_enable(afe->regulator);
	अगर (ret) अणु
		dev_err(dev, "Unable to enable regulator\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(afe->regmap, AFE440X_CONTROL2,
				 AFE440X_CONTROL2_PDN_AFE, 0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(afe4404_pm_ops, afe4404_suspend, afe4404_resume);

अटल पूर्णांक afe4404_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा afe4404_data *afe;
	पूर्णांक i, ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*afe));
	अगर (!indio_dev)
		वापस -ENOMEM;

	afe = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);

	afe->dev = &client->dev;
	afe->irq = client->irq;

	afe->regmap = devm_regmap_init_i2c(client, &afe4404_regmap_config);
	अगर (IS_ERR(afe->regmap)) अणु
		dev_err(afe->dev, "Unable to allocate register map\n");
		वापस PTR_ERR(afe->regmap);
	पूर्ण

	क्रम (i = 0; i < F_MAX_FIELDS; i++) अणु
		afe->fields[i] = devm_regmap_field_alloc(afe->dev, afe->regmap,
							 afe4404_reg_fields[i]);
		अगर (IS_ERR(afe->fields[i])) अणु
			dev_err(afe->dev, "Unable to allocate regmap fields\n");
			वापस PTR_ERR(afe->fields[i]);
		पूर्ण
	पूर्ण

	afe->regulator = devm_regulator_get(afe->dev, "tx_sup");
	अगर (IS_ERR(afe->regulator)) अणु
		dev_err(afe->dev, "Unable to get regulator\n");
		वापस PTR_ERR(afe->regulator);
	पूर्ण
	ret = regulator_enable(afe->regulator);
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to enable regulator\n");
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(afe->regmap, AFE440X_CONTROL0,
			   AFE440X_CONTROL0_SW_RESET);
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to reset device\n");
		जाओ disable_reg;
	पूर्ण

	ret = regmap_multi_reg_ग_लिखो(afe->regmap, afe4404_reg_sequences,
				     ARRAY_SIZE(afe4404_reg_sequences));
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to set register defaults\n");
		जाओ disable_reg;
	पूर्ण

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = afe4404_channels;
	indio_dev->num_channels = ARRAY_SIZE(afe4404_channels);
	indio_dev->name = AFE4404_DRIVER_NAME;
	indio_dev->info = &afe4404_iio_info;

	अगर (afe->irq > 0) अणु
		afe->trig = devm_iio_trigger_alloc(afe->dev,
						   "%s-dev%d",
						   indio_dev->name,
						   indio_dev->id);
		अगर (!afe->trig) अणु
			dev_err(afe->dev, "Unable to allocate IIO trigger\n");
			ret = -ENOMEM;
			जाओ disable_reg;
		पूर्ण

		iio_trigger_set_drvdata(afe->trig, indio_dev);

		afe->trig->ops = &afe4404_trigger_ops;

		ret = iio_trigger_रेजिस्टर(afe->trig);
		अगर (ret) अणु
			dev_err(afe->dev, "Unable to register IIO trigger\n");
			जाओ disable_reg;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(afe->dev, afe->irq,
						iio_trigger_generic_data_rdy_poll,
						शून्य, IRQF_ONESHOT,
						AFE4404_DRIVER_NAME,
						afe->trig);
		अगर (ret) अणु
			dev_err(afe->dev, "Unable to request IRQ\n");
			जाओ disable_reg;
		पूर्ण
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
					 afe4404_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to setup buffer\n");
		जाओ unरेजिस्टर_trigger;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to register IIO device\n");
		जाओ unरेजिस्टर_triggered_buffer;
	पूर्ण

	वापस 0;

unरेजिस्टर_triggered_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
unरेजिस्टर_trigger:
	अगर (afe->irq > 0)
		iio_trigger_unरेजिस्टर(afe->trig);
disable_reg:
	regulator_disable(afe->regulator);

	वापस ret;
पूर्ण

अटल पूर्णांक afe4404_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा afe4404_data *afe = iio_priv(indio_dev);
	पूर्णांक ret;

	iio_device_unरेजिस्टर(indio_dev);

	iio_triggered_buffer_cleanup(indio_dev);

	अगर (afe->irq > 0)
		iio_trigger_unरेजिस्टर(afe->trig);

	ret = regulator_disable(afe->regulator);
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to disable regulator\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id afe4404_ids[] = अणु
	अणु "afe4404", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, afe4404_ids);

अटल काष्ठा i2c_driver afe4404_i2c_driver = अणु
	.driver = अणु
		.name = AFE4404_DRIVER_NAME,
		.of_match_table = afe4404_of_match,
		.pm = &afe4404_pm_ops,
	पूर्ण,
	.probe = afe4404_probe,
	.हटाओ = afe4404_हटाओ,
	.id_table = afe4404_ids,
पूर्ण;
module_i2c_driver(afe4404_i2c_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TI AFE4404 Heart Rate Monitor and Pulse Oximeter AFE");
MODULE_LICENSE("GPL v2");
