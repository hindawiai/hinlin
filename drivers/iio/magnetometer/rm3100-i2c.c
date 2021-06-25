<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम PNI RM3100 3-axis geomagnetic sensor on a i2c bus.
 *
 * Copyright (C) 2018 Song Qiang <songqiang1304521@gmail.com>
 *
 * i2c slave address: 0x20 + SA1 << 1 + SA0.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>

#समावेश "rm3100.h"

अटल स्थिर काष्ठा regmap_config rm3100_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.rd_table = &rm3100_पढ़ोable_table,
	.wr_table = &rm3100_writable_table,
	.अस्थिर_table = &rm3100_अस्थिर_table,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक rm3100_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &rm3100_regmap_config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस rm3100_common_probe(&client->dev, regmap, client->irq);
पूर्ण

अटल स्थिर काष्ठा of_device_id rm3100_dt_match[] = अणु
	अणु .compatible = "pni,rm3100", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rm3100_dt_match);

अटल काष्ठा i2c_driver rm3100_driver = अणु
	.driver = अणु
		.name = "rm3100-i2c",
		.of_match_table = rm3100_dt_match,
	पूर्ण,
	.probe_new = rm3100_probe,
पूर्ण;
module_i2c_driver(rm3100_driver);

MODULE_AUTHOR("Song Qiang <songqiang1304521@gmail.com>");
MODULE_DESCRIPTION("PNI RM3100 3-axis magnetometer i2c driver");
MODULE_LICENSE("GPL v2");
