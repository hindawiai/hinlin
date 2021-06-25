<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI driver क्रम hmc5983
 *
 * Copyright (C) Josef Gajdusek <atx@atx.name>
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>

#समावेश "hmc5843.h"

अटल स्थिर काष्ठा regmap_range hmc5843_पढ़ोable_ranges[] = अणु
		regmap_reg_range(0, HMC5843_ID_END),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table hmc5843_पढ़ोable_table = अणु
		.yes_ranges = hmc5843_पढ़ोable_ranges,
		.n_yes_ranges = ARRAY_SIZE(hmc5843_पढ़ोable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range hmc5843_writable_ranges[] = अणु
		regmap_reg_range(0, HMC5843_MODE_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table hmc5843_writable_table = अणु
		.yes_ranges = hmc5843_writable_ranges,
		.n_yes_ranges = ARRAY_SIZE(hmc5843_writable_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_range hmc5843_अस्थिर_ranges[] = अणु
		regmap_reg_range(HMC5843_DATA_OUT_MSB_REGS, HMC5843_STATUS_REG),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table hmc5843_अस्थिर_table = अणु
		.yes_ranges = hmc5843_अस्थिर_ranges,
		.n_yes_ranges = ARRAY_SIZE(hmc5843_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config hmc5843_spi_regmap_config = अणु
		.reg_bits = 8,
		.val_bits = 8,

		.rd_table = &hmc5843_पढ़ोable_table,
		.wr_table = &hmc5843_writable_table,
		.अस्थिर_table = &hmc5843_अस्थिर_table,

		/* Autoincrement address poपूर्णांकer */
		.पढ़ो_flag_mask = 0xc0,

		.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक hmc5843_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = 8000000;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	regmap = devm_regmap_init_spi(spi, &hmc5843_spi_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस hmc5843_common_probe(&spi->dev,
			regmap,
			id->driver_data, id->name);
पूर्ण

अटल पूर्णांक hmc5843_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस hmc5843_common_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id hmc5843_id[] = अणु
	अणु "hmc5983", HMC5983_ID पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, hmc5843_id);

अटल काष्ठा spi_driver hmc5843_driver = अणु
		.driver = अणु
				.name = "hmc5843",
				.pm = HMC5843_PM_OPS,
		पूर्ण,
		.id_table = hmc5843_id,
		.probe = hmc5843_spi_probe,
		.हटाओ = hmc5843_spi_हटाओ,
पूर्ण;

module_spi_driver(hmc5843_driver);

MODULE_AUTHOR("Josef Gajdusek <atx@atx.name>");
MODULE_DESCRIPTION("HMC5983 SPI driver");
MODULE_LICENSE("GPL");
