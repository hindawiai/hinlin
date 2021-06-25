<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices LTC2947 high precision घातer and energy monitor over I2C
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "ltc2947.h"

अटल स्थिर काष्ठा regmap_config ltc2947_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक ltc2947_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regmap *map;

	map = devm_regmap_init_i2c(i2c, &ltc2947_regmap_config);
	अगर (IS_ERR(map))
		वापस PTR_ERR(map);

	वापस ltc2947_core_probe(map, i2c->name);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc2947_id[] = अणु
	अणु"ltc2947", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc2947_id);

अटल काष्ठा i2c_driver ltc2947_driver = अणु
	.driver = अणु
		.name = "ltc2947",
		.of_match_table = ltc2947_of_match,
		.pm = &ltc2947_pm_ops,
	पूर्ण,
	.probe_new = ltc2947_probe,
	.id_table = ltc2947_id,
पूर्ण;
module_i2c_driver(ltc2947_driver);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("LTC2947 I2C power and energy monitor driver");
MODULE_LICENSE("GPL");
