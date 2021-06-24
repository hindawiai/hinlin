<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Murata ZPA2326 SPI pressure and temperature sensor driver
 *
 * Copyright (c) 2016 Parrot S.A.
 *
 * Author: Gregor Boirie <gregor.boirie@parrot.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश "zpa2326.h"

/*
 * पढ़ो_flag_mask:
 *   - address bit 7 must be set to request a रेजिस्टर पढ़ो operation
 *   - address bit 6 must be set to request रेजिस्टर address स्वतः increment
 */
अटल स्थिर काष्ठा regmap_config zpa2326_regmap_spi_config = अणु
	.reg_bits       = 8,
	.val_bits       = 8,
	.ग_लिखोable_reg  = zpa2326_isreg_ग_लिखोable,
	.पढ़ोable_reg   = zpa2326_isreg_पढ़ोable,
	.precious_reg   = zpa2326_isreg_precious,
	.max_रेजिस्टर   = ZPA2326_TEMP_OUT_H_REG,
	.पढ़ो_flag_mask = BIT(7) | BIT(6),
	.cache_type     = REGCACHE_NONE,
पूर्ण;

अटल पूर्णांक zpa2326_probe_spi(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *regmap;
	पूर्णांक            err;

	regmap = devm_regmap_init_spi(spi, &zpa2326_regmap_spi_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "failed to init registers map");
		वापस PTR_ERR(regmap);
	पूर्ण

	/*
	 * Enक्रमce SPI slave settings to prevent from DT misconfiguration.
	 *
	 * Clock is idle high. Sampling happens on trailing edge, i.e., rising
	 * edge. Maximum bus frequency is 1 MHz. Registers are 8 bits wide.
	 */
	spi->mode = SPI_MODE_3;
	spi->max_speed_hz = min(spi->max_speed_hz, 1000000U);
	spi->bits_per_word = 8;
	err = spi_setup(spi);
	अगर (err < 0)
		वापस err;

	वापस zpa2326_probe(&spi->dev, spi_get_device_id(spi)->name,
			     spi->irq, ZPA2326_DEVICE_ID, regmap);
पूर्ण

अटल पूर्णांक zpa2326_हटाओ_spi(काष्ठा spi_device *spi)
अणु
	zpa2326_हटाओ(&spi->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id zpa2326_spi_ids[] = अणु
	अणु "zpa2326", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, zpa2326_spi_ids);

अटल स्थिर काष्ठा of_device_id zpa2326_spi_matches[] = अणु
	अणु .compatible = "murata,zpa2326" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zpa2326_spi_matches);

अटल काष्ठा spi_driver zpa2326_spi_driver = अणु
	.driver = अणु
		.name           = "zpa2326-spi",
		.of_match_table = zpa2326_spi_matches,
		.pm             = ZPA2326_PM_OPS,
	पूर्ण,
	.probe    = zpa2326_probe_spi,
	.हटाओ   = zpa2326_हटाओ_spi,
	.id_table = zpa2326_spi_ids,
पूर्ण;
module_spi_driver(zpa2326_spi_driver);

MODULE_AUTHOR("Gregor Boirie <gregor.boirie@parrot.com>");
MODULE_DESCRIPTION("SPI driver for Murata ZPA2326 pressure sensor");
MODULE_LICENSE("GPL v2");
