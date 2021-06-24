<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम PNI RM3100 3-axis geomagnetic sensor on a spi bus.
 *
 * Copyright (C) 2018 Song Qiang <songqiang1304521@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश "rm3100.h"

अटल स्थिर काष्ठा regmap_config rm3100_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.rd_table = &rm3100_पढ़ोable_table,
	.wr_table = &rm3100_writable_table,
	.अस्थिर_table = &rm3100_अस्थिर_table,

	.पढ़ो_flag_mask = 0x80,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक rm3100_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	/* Actually this device supports both mode 0 and mode 3. */
	spi->mode = SPI_MODE_0;
	/* Data rates cannot exceed 1Mbits. */
	spi->max_speed_hz = 1000000;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	regmap = devm_regmap_init_spi(spi, &rm3100_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस rm3100_common_probe(&spi->dev, regmap, spi->irq);
पूर्ण

अटल स्थिर काष्ठा of_device_id rm3100_dt_match[] = अणु
	अणु .compatible = "pni,rm3100", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rm3100_dt_match);

अटल काष्ठा spi_driver rm3100_driver = अणु
	.driver = अणु
		.name = "rm3100-spi",
		.of_match_table = rm3100_dt_match,
	पूर्ण,
	.probe = rm3100_probe,
पूर्ण;
module_spi_driver(rm3100_driver);

MODULE_AUTHOR("Song Qiang <songqiang1304521@gmail.com>");
MODULE_DESCRIPTION("PNI RM3100 3-axis magnetometer spi driver");
MODULE_LICENSE("GPL v2");
