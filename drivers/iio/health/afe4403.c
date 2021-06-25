<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AFE4403 Heart Rate Monitors and Low-Cost Pulse Oximeters
 *
 * Copyright (C) 2015-2016 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "afe440x.h"

#घोषणा AFE4403_DRIVER_NAME		"afe4403"

/* AFE4403 Registers */
#घोषणा AFE4403_TIAGAIN			0x20
#घोषणा AFE4403_TIA_AMB_GAIN		0x21

क्रमागत afe4403_fields अणु
	/* Gains */
	F_RF_LED1, F_CF_LED1,
	F_RF_LED, F_CF_LED,

	/* LED Current */
	F_ILED1, F_ILED2,

	/* sentinel */
	F_MAX_FIELDS
पूर्ण;

अटल स्थिर काष्ठा reg_field afe4403_reg_fields[] = अणु
	/* Gains */
	[F_RF_LED1]	= REG_FIELD(AFE4403_TIAGAIN, 0, 2),
	[F_CF_LED1]	= REG_FIELD(AFE4403_TIAGAIN, 3, 7),
	[F_RF_LED]	= REG_FIELD(AFE4403_TIA_AMB_GAIN, 0, 2),
	[F_CF_LED]	= REG_FIELD(AFE4403_TIA_AMB_GAIN, 3, 7),
	/* LED Current */
	[F_ILED1]	= REG_FIELD(AFE440X_LEDCNTRL, 0, 7),
	[F_ILED2]	= REG_FIELD(AFE440X_LEDCNTRL, 8, 15),
पूर्ण;

/**
 * काष्ठा afe4403_data - AFE4403 device instance data
 * @dev: Device काष्ठाure
 * @spi: SPI device handle
 * @regmap: Register map of the device
 * @fields: Register fields of the device
 * @regulator: Poपूर्णांकer to the regulator क्रम the IC
 * @trig: IIO trigger क्रम this device
 * @irq: ADC_RDY line पूर्णांकerrupt number
 * @buffer: Used to स्थिरruct data layout to push पूर्णांकo IIO buffer.
 */
काष्ठा afe4403_data अणु
	काष्ठा device *dev;
	काष्ठा spi_device *spi;
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *fields[F_MAX_FIELDS];
	काष्ठा regulator *regulator;
	काष्ठा iio_trigger *trig;
	पूर्णांक irq;
	/* Ensure suitable alignment क्रम बारtamp */
	s32 buffer[8] __aligned(8);
पूर्ण;

क्रमागत afe4403_chan_id अणु
	LED2 = 1,
	ALED2,
	LED1,
	ALED1,
	LED2_ALED2,
	LED1_ALED1,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक afe4403_channel_values[] = अणु
	[LED2] = AFE440X_LED2VAL,
	[ALED2] = AFE440X_ALED2VAL,
	[LED1] = AFE440X_LED1VAL,
	[ALED1] = AFE440X_ALED1VAL,
	[LED2_ALED2] = AFE440X_LED2_ALED2VAL,
	[LED1_ALED1] = AFE440X_LED1_ALED1VAL,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक afe4403_channel_leds[] = अणु
	[LED2] = F_ILED2,
	[LED1] = F_ILED1,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec afe4403_channels[] = अणु
	/* ADC values */
	AFE440X_INTENSITY_CHAN(LED2, 0),
	AFE440X_INTENSITY_CHAN(ALED2, 0),
	AFE440X_INTENSITY_CHAN(LED1, 0),
	AFE440X_INTENSITY_CHAN(ALED1, 0),
	AFE440X_INTENSITY_CHAN(LED2_ALED2, 0),
	AFE440X_INTENSITY_CHAN(LED1_ALED1, 0),
	/* LED current */
	AFE440X_CURRENT_CHAN(LED2),
	AFE440X_CURRENT_CHAN(LED1),
पूर्ण;

अटल स्थिर काष्ठा afe440x_val_table afe4403_res_table[] = अणु
	अणु 500000 पूर्ण, अणु 250000 पूर्ण, अणु 100000 पूर्ण, अणु 50000 पूर्ण,
	अणु 25000 पूर्ण, अणु 10000 पूर्ण, अणु 1000000 पूर्ण, अणु 0 पूर्ण,
पूर्ण;
AFE440X_TABLE_ATTR(in_पूर्णांकensity_resistance_available, afe4403_res_table);

अटल स्थिर काष्ठा afe440x_val_table afe4403_cap_table[] = अणु
	अणु 0, 5000 पूर्ण, अणु 0, 10000 पूर्ण, अणु 0, 20000 पूर्ण, अणु 0, 25000 पूर्ण,
	अणु 0, 30000 पूर्ण, अणु 0, 35000 पूर्ण, अणु 0, 45000 पूर्ण, अणु 0, 50000 पूर्ण,
	अणु 0, 55000 पूर्ण, अणु 0, 60000 पूर्ण, अणु 0, 70000 पूर्ण, अणु 0, 75000 पूर्ण,
	अणु 0, 80000 पूर्ण, अणु 0, 85000 पूर्ण, अणु 0, 95000 पूर्ण, अणु 0, 100000 पूर्ण,
	अणु 0, 155000 पूर्ण, अणु 0, 160000 पूर्ण, अणु 0, 170000 पूर्ण, अणु 0, 175000 पूर्ण,
	अणु 0, 180000 पूर्ण, अणु 0, 185000 पूर्ण, अणु 0, 195000 पूर्ण, अणु 0, 200000 पूर्ण,
	अणु 0, 205000 पूर्ण, अणु 0, 210000 पूर्ण, अणु 0, 220000 पूर्ण, अणु 0, 225000 पूर्ण,
	अणु 0, 230000 पूर्ण, अणु 0, 235000 पूर्ण, अणु 0, 245000 पूर्ण, अणु 0, 250000 पूर्ण,
पूर्ण;
AFE440X_TABLE_ATTR(in_पूर्णांकensity_capacitance_available, afe4403_cap_table);

अटल sमाप_प्रकार afe440x_show_रेजिस्टर(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
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
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
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

अटल AFE440X_ATTR(in_पूर्णांकensity1_resistance, F_RF_LED, afe4403_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity1_capacitance, F_CF_LED, afe4403_cap_table);

अटल AFE440X_ATTR(in_पूर्णांकensity2_resistance, F_RF_LED, afe4403_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity2_capacitance, F_CF_LED, afe4403_cap_table);

अटल AFE440X_ATTR(in_पूर्णांकensity3_resistance, F_RF_LED1, afe4403_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity3_capacitance, F_CF_LED1, afe4403_cap_table);

अटल AFE440X_ATTR(in_पूर्णांकensity4_resistance, F_RF_LED1, afe4403_res_table);
अटल AFE440X_ATTR(in_पूर्णांकensity4_capacitance, F_CF_LED1, afe4403_cap_table);

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

अटल पूर्णांक afe4403_पढ़ो(काष्ठा afe4403_data *afe, अचिन्हित पूर्णांक reg, u32 *val)
अणु
	u8 tx[4] = अणुAFE440X_CONTROL0, 0x0, 0x0, AFE440X_CONTROL0_READपूर्ण;
	u8 rx[3];
	पूर्णांक ret;

	/* Enable पढ़ोing from the device */
	ret = spi_ग_लिखो_then_पढ़ो(afe->spi, tx, 4, शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = spi_ग_लिखो_then_पढ़ो(afe->spi, &reg, 1, rx, माप(rx));
	अगर (ret)
		वापस ret;

	*val = get_unaligned_be24(&rx[0]);

	/* Disable पढ़ोing from the device */
	tx[3] = AFE440X_CONTROL0_WRITE;
	ret = spi_ग_लिखो_then_पढ़ो(afe->spi, tx, 4, शून्य, 0);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक afe4403_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
	अचिन्हित पूर्णांक reg = afe4403_channel_values[chan->address];
	अचिन्हित पूर्णांक field = afe4403_channel_leds[chan->address];
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_INTENSITY:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_RAW:
			ret = afe4403_पढ़ो(afe, reg, val);
			अगर (ret)
				वापस ret;
			वापस IIO_VAL_INT;
		पूर्ण
		अवरोध;
	हाल IIO_CURRENT:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_RAW:
			ret = regmap_field_पढ़ो(afe->fields[field], val);
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

अटल पूर्णांक afe4403_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
	अचिन्हित पूर्णांक field = afe4403_channel_leds[chan->address];

	चयन (chan->type) अणु
	हाल IIO_CURRENT:
		चयन (mask) अणु
		हाल IIO_CHAN_INFO_RAW:
			वापस regmap_field_ग_लिखो(afe->fields[field], val);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info afe4403_iio_info = अणु
	.attrs = &afe440x_attribute_group,
	.पढ़ो_raw = afe4403_पढ़ो_raw,
	.ग_लिखो_raw = afe4403_ग_लिखो_raw,
पूर्ण;

अटल irqवापस_t afe4403_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
	पूर्णांक ret, bit, i = 0;
	u8 tx[4] = अणुAFE440X_CONTROL0, 0x0, 0x0, AFE440X_CONTROL0_READपूर्ण;
	u8 rx[3];

	/* Enable पढ़ोing from the device */
	ret = spi_ग_लिखो_then_पढ़ो(afe->spi, tx, 4, शून्य, 0);
	अगर (ret)
		जाओ err;

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = spi_ग_लिखो_then_पढ़ो(afe->spi,
					  &afe4403_channel_values[bit], 1,
					  rx, माप(rx));
		अगर (ret)
			जाओ err;

		afe->buffer[i++] = get_unaligned_be24(&rx[0]);
	पूर्ण

	/* Disable पढ़ोing from the device */
	tx[3] = AFE440X_CONTROL0_WRITE;
	ret = spi_ग_लिखो_then_पढ़ो(afe->spi, tx, 4, शून्य, 0);
	अगर (ret)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, afe->buffer,
					   pf->बारtamp);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops afe4403_trigger_ops = अणु
पूर्ण;

#घोषणा AFE4403_TIMING_PAIRS			\
	अणु AFE440X_LED2STC,	0x000050 पूर्ण,	\
	अणु AFE440X_LED2ENDC,	0x0003e7 पूर्ण,	\
	अणु AFE440X_LED1LEDSTC,	0x0007d0 पूर्ण,	\
	अणु AFE440X_LED1LEDENDC,	0x000bb7 पूर्ण,	\
	अणु AFE440X_ALED2STC,	0x000438 पूर्ण,	\
	अणु AFE440X_ALED2ENDC,	0x0007cf पूर्ण,	\
	अणु AFE440X_LED1STC,	0x000820 पूर्ण,	\
	अणु AFE440X_LED1ENDC,	0x000bb7 पूर्ण,	\
	अणु AFE440X_LED2LEDSTC,	0x000000 पूर्ण,	\
	अणु AFE440X_LED2LEDENDC,	0x0003e7 पूर्ण,	\
	अणु AFE440X_ALED1STC,	0x000c08 पूर्ण,	\
	अणु AFE440X_ALED1ENDC,	0x000f9f पूर्ण,	\
	अणु AFE440X_LED2CONVST,	0x0003ef पूर्ण,	\
	अणु AFE440X_LED2CONVEND,	0x0007cf पूर्ण,	\
	अणु AFE440X_ALED2CONVST,	0x0007d7 पूर्ण,	\
	अणु AFE440X_ALED2CONVEND,	0x000bb7 पूर्ण,	\
	अणु AFE440X_LED1CONVST,	0x000bbf पूर्ण,	\
	अणु AFE440X_LED1CONVEND,	0x009c3f पूर्ण,	\
	अणु AFE440X_ALED1CONVST,	0x000fa7 पूर्ण,	\
	अणु AFE440X_ALED1CONVEND,	0x001387 पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT0,	0x0003e8 पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT0,	0x0003eb पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT1,	0x0007d0 पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT1,	0x0007d3 पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT2,	0x000bb8 पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT2,	0x000bbb पूर्ण,	\
	अणु AFE440X_ADCRSTSTCT3,	0x000fa0 पूर्ण,	\
	अणु AFE440X_ADCRSTENDCT3,	0x000fa3 पूर्ण,	\
	अणु AFE440X_PRPCOUNT,	0x009c3f पूर्ण,	\
	अणु AFE440X_PDNCYCLESTC,	0x001518 पूर्ण,	\
	अणु AFE440X_PDNCYCLEENDC,	0x00991f पूर्ण

अटल स्थिर काष्ठा reg_sequence afe4403_reg_sequences[] = अणु
	AFE4403_TIMING_PAIRS,
	अणु AFE440X_CONTROL1, AFE440X_CONTROL1_TIMEREN पूर्ण,
	अणु AFE4403_TIAGAIN, AFE440X_TIAGAIN_ENSEPGAIN पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_range afe4403_yes_ranges[] = अणु
	regmap_reg_range(AFE440X_LED2VAL, AFE440X_LED1_ALED1VAL),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table afe4403_अस्थिर_table = अणु
	.yes_ranges = afe4403_yes_ranges,
	.n_yes_ranges = ARRAY_SIZE(afe4403_yes_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config afe4403_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 24,

	.max_रेजिस्टर = AFE440X_PDNCYCLEENDC,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_table = &afe4403_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा of_device_id afe4403_of_match[] = अणु
	अणु .compatible = "ti,afe4403", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, afe4403_of_match);

अटल पूर्णांक __maybe_unused afe4403_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(to_spi_device(dev));
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
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

अटल पूर्णांक __maybe_unused afe4403_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(to_spi_device(dev));
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
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

अटल SIMPLE_DEV_PM_OPS(afe4403_pm_ops, afe4403_suspend, afe4403_resume);

अटल पूर्णांक afe4403_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा afe4403_data *afe;
	पूर्णांक i, ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*afe));
	अगर (!indio_dev)
		वापस -ENOMEM;

	afe = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	afe->dev = &spi->dev;
	afe->spi = spi;
	afe->irq = spi->irq;

	afe->regmap = devm_regmap_init_spi(spi, &afe4403_regmap_config);
	अगर (IS_ERR(afe->regmap)) अणु
		dev_err(afe->dev, "Unable to allocate register map\n");
		वापस PTR_ERR(afe->regmap);
	पूर्ण

	क्रम (i = 0; i < F_MAX_FIELDS; i++) अणु
		afe->fields[i] = devm_regmap_field_alloc(afe->dev, afe->regmap,
							 afe4403_reg_fields[i]);
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
		जाओ err_disable_reg;
	पूर्ण

	ret = regmap_multi_reg_ग_लिखो(afe->regmap, afe4403_reg_sequences,
				     ARRAY_SIZE(afe4403_reg_sequences));
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to set register defaults\n");
		जाओ err_disable_reg;
	पूर्ण

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = afe4403_channels;
	indio_dev->num_channels = ARRAY_SIZE(afe4403_channels);
	indio_dev->name = AFE4403_DRIVER_NAME;
	indio_dev->info = &afe4403_iio_info;

	अगर (afe->irq > 0) अणु
		afe->trig = devm_iio_trigger_alloc(afe->dev,
						   "%s-dev%d",
						   indio_dev->name,
						   indio_dev->id);
		अगर (!afe->trig) अणु
			dev_err(afe->dev, "Unable to allocate IIO trigger\n");
			ret = -ENOMEM;
			जाओ err_disable_reg;
		पूर्ण

		iio_trigger_set_drvdata(afe->trig, indio_dev);

		afe->trig->ops = &afe4403_trigger_ops;

		ret = iio_trigger_रेजिस्टर(afe->trig);
		अगर (ret) अणु
			dev_err(afe->dev, "Unable to register IIO trigger\n");
			जाओ err_disable_reg;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(afe->dev, afe->irq,
						iio_trigger_generic_data_rdy_poll,
						शून्य, IRQF_ONESHOT,
						AFE4403_DRIVER_NAME,
						afe->trig);
		अगर (ret) अणु
			dev_err(afe->dev, "Unable to request IRQ\n");
			जाओ err_trig;
		पूर्ण
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, &iio_pollfunc_store_समय,
					 afe4403_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to setup buffer\n");
		जाओ err_trig;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(afe->dev, "Unable to register IIO device\n");
		जाओ err_buff;
	पूर्ण

	वापस 0;

err_buff:
	iio_triggered_buffer_cleanup(indio_dev);
err_trig:
	अगर (afe->irq > 0)
		iio_trigger_unरेजिस्टर(afe->trig);
err_disable_reg:
	regulator_disable(afe->regulator);

	वापस ret;
पूर्ण

अटल पूर्णांक afe4403_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा afe4403_data *afe = iio_priv(indio_dev);
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

अटल स्थिर काष्ठा spi_device_id afe4403_ids[] = अणु
	अणु "afe4403", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, afe4403_ids);

अटल काष्ठा spi_driver afe4403_spi_driver = अणु
	.driver = अणु
		.name = AFE4403_DRIVER_NAME,
		.of_match_table = afe4403_of_match,
		.pm = &afe4403_pm_ops,
	पूर्ण,
	.probe = afe4403_probe,
	.हटाओ = afe4403_हटाओ,
	.id_table = afe4403_ids,
पूर्ण;
module_spi_driver(afe4403_spi_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TI AFE4403 Heart Rate Monitor and Pulse Oximeter AFE");
MODULE_LICENSE("GPL v2");
