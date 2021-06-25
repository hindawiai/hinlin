<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Murata ZPA2326 I2C pressure and temperature sensor driver
 *
 * Copyright (c) 2016 Parrot S.A.
 *
 * Author: Gregor Boirie <gregor.boirie@parrot.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश "zpa2326.h"

/*
 * पढ़ो_flag_mask:
 *   - address bit 7 must be set to request a रेजिस्टर पढ़ो operation
 */
अटल स्थिर काष्ठा regmap_config zpa2326_regmap_i2c_config = अणु
	.reg_bits       = 8,
	.val_bits       = 8,
	.ग_लिखोable_reg  = zpa2326_isreg_ग_लिखोable,
	.पढ़ोable_reg   = zpa2326_isreg_पढ़ोable,
	.precious_reg   = zpa2326_isreg_precious,
	.max_रेजिस्टर   = ZPA2326_TEMP_OUT_H_REG,
	.पढ़ो_flag_mask = BIT(7),
	.cache_type     = REGCACHE_NONE,
पूर्ण;

अटल अचिन्हित पूर्णांक zpa2326_i2c_hwid(स्थिर काष्ठा i2c_client *client)
अणु
#घोषणा ZPA2326_SA0(_addr)          (_addr & BIT(0))
#घोषणा ZPA2326_DEVICE_ID_SA0_SHIFT (1)

	/* Identअगरication रेजिस्टर bit 1 mirrors device address bit 0. */
	वापस (ZPA2326_DEVICE_ID |
		(ZPA2326_SA0(client->addr) << ZPA2326_DEVICE_ID_SA0_SHIFT));
पूर्ण

अटल पूर्णांक zpa2326_probe_i2c(काष्ठा i2c_client          *client,
			     स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(client, &zpa2326_regmap_i2c_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "failed to init registers map");
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस zpa2326_probe(&client->dev, i2c_id->name, client->irq,
			     zpa2326_i2c_hwid(client), regmap);
पूर्ण

अटल पूर्णांक zpa2326_हटाओ_i2c(काष्ठा i2c_client *client)
अणु
	zpa2326_हटाओ(&client->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id zpa2326_i2c_ids[] = अणु
	अणु "zpa2326", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, zpa2326_i2c_ids);

अटल स्थिर काष्ठा of_device_id zpa2326_i2c_matches[] = अणु
	अणु .compatible = "murata,zpa2326" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zpa2326_i2c_matches);

अटल काष्ठा i2c_driver zpa2326_i2c_driver = अणु
	.driver = अणु
		.name           = "zpa2326-i2c",
		.of_match_table = zpa2326_i2c_matches,
		.pm             = ZPA2326_PM_OPS,
	पूर्ण,
	.probe    = zpa2326_probe_i2c,
	.हटाओ   = zpa2326_हटाओ_i2c,
	.id_table = zpa2326_i2c_ids,
पूर्ण;
module_i2c_driver(zpa2326_i2c_driver);

MODULE_AUTHOR("Gregor Boirie <gregor.boirie@parrot.com>");
MODULE_DESCRIPTION("I2C driver for Murata ZPA2326 pressure sensor");
MODULE_LICENSE("GPL v2");
