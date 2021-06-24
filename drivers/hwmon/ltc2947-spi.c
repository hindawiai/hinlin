<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices LTC2947 high precision घातer and energy monitor over SPI
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "ltc2947.h"

अटल स्थिर काष्ठा regmap_config ltc2947_regmap_config = अणु
	.reg_bits = 16,
	.val_bits = 8,
	.पढ़ो_flag_mask = BIT(0),
पूर्ण;

अटल पूर्णांक ltc2947_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap *map;

	map = devm_regmap_init_spi(spi, &ltc2947_regmap_config);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	वापस ltc2947_core_probe(map, spi_get_device_id(spi)->name);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ltc2947_id[] = अणु
	अणु"ltc2947", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ltc2947_id);

अटल काष्ठा spi_driver ltc2947_driver = अणु
	.driver = अणु
		.name = "ltc2947",
		.of_match_table = ltc2947_of_match,
		.pm = &ltc2947_pm_ops,
	पूर्ण,
	.probe = ltc2947_probe,
	.id_table = ltc2947_id,
पूर्ण;
module_spi_driver(ltc2947_driver);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("LTC2947 SPI power and energy monitor driver");
MODULE_LICENSE("GPL");
