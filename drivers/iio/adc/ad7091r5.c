<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7091R5 Analog to Digital converter driver
 *
 * Copyright 2014-2019 Analog Devices Inc.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "ad7091r-base.h"

अटल स्थिर काष्ठा iio_event_spec ad7091r5_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_HYSTERESIS),
	पूर्ण,
पूर्ण;

#घोषणा AD7091R_CHANNEL(idx, bits, ev, num_ev) अणु \
	.type = IIO_VOLTAGE, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.indexed = 1, \
	.channel = idx, \
	.event_spec = ev, \
	.num_event_specs = num_ev, \
	.scan_type.storagebits = 16, \
	.scan_type.realbits = bits, \
पूर्ण
अटल स्थिर काष्ठा iio_chan_spec ad7091r5_channels_irq[] = अणु
	AD7091R_CHANNEL(0, 12, ad7091r5_events, ARRAY_SIZE(ad7091r5_events)),
	AD7091R_CHANNEL(1, 12, ad7091r5_events, ARRAY_SIZE(ad7091r5_events)),
	AD7091R_CHANNEL(2, 12, ad7091r5_events, ARRAY_SIZE(ad7091r5_events)),
	AD7091R_CHANNEL(3, 12, ad7091r5_events, ARRAY_SIZE(ad7091r5_events)),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7091r5_channels_noirq[] = अणु
	AD7091R_CHANNEL(0, 12, शून्य, 0),
	AD7091R_CHANNEL(1, 12, शून्य, 0),
	AD7091R_CHANNEL(2, 12, शून्य, 0),
	AD7091R_CHANNEL(3, 12, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा ad7091r_chip_info ad7091r5_chip_info_irq = अणु
	.channels = ad7091r5_channels_irq,
	.num_channels = ARRAY_SIZE(ad7091r5_channels_irq),
	.vref_mV = 2500,
पूर्ण;

अटल स्थिर काष्ठा ad7091r_chip_info ad7091r5_chip_info_noirq = अणु
	.channels = ad7091r5_channels_noirq,
	.num_channels = ARRAY_SIZE(ad7091r5_channels_noirq),
	.vref_mV = 2500,
पूर्ण;

अटल पूर्णांक ad7091r5_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा ad7091r_chip_info *chip_info;
	काष्ठा regmap *map = devm_regmap_init_i2c(i2c, &ad7091r_regmap_config);

	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	अगर (i2c->irq)
		chip_info = &ad7091r5_chip_info_irq;
	अन्यथा
		chip_info = &ad7091r5_chip_info_noirq;

	वापस ad7091r_probe(&i2c->dev, id->name, chip_info, map, i2c->irq);
पूर्ण

अटल स्थिर काष्ठा of_device_id ad7091r5_dt_ids[] = अणु
	अणु .compatible = "adi,ad7091r5" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7091r5_dt_ids);

अटल स्थिर काष्ठा i2c_device_id ad7091r5_i2c_ids[] = अणु
	अणु"ad7091r5", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad7091r5_i2c_ids);

अटल काष्ठा i2c_driver ad7091r5_driver = अणु
	.driver = अणु
		.name = "ad7091r5",
		.of_match_table = ad7091r5_dt_ids,
	पूर्ण,
	.probe = ad7091r5_i2c_probe,
	.id_table = ad7091r5_i2c_ids,
पूर्ण;
module_i2c_driver(ad7091r5_driver);

MODULE_AUTHOR("Beniamin Bia <beniamin.bia@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7091R5 multi-channel ADC driver");
MODULE_LICENSE("GPL v2");
