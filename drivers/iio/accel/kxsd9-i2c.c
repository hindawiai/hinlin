<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>

#समावेश "kxsd9.h"

अटल पूर्णांक kxsd9_i2c_probe(काष्ठा i2c_client *i2c,
			   स्थिर काष्ठा i2c_device_id *id)
अणु
	अटल स्थिर काष्ठा regmap_config config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x0e,
	पूर्ण;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&i2c->dev, "Failed to register i2c regmap: %pe\n",
			regmap);
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस kxsd9_common_probe(&i2c->dev,
				  regmap,
				  i2c->name);
पूर्ण

अटल पूर्णांक kxsd9_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस kxsd9_common_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id kxsd9_of_match[] = अणु
	अणु .compatible = "kionix,kxsd9", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, kxsd9_of_match);

अटल स्थिर काष्ठा i2c_device_id kxsd9_i2c_id[] = अणु
	अणु"kxsd9", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, kxsd9_i2c_id);

अटल काष्ठा i2c_driver kxsd9_i2c_driver = अणु
	.driver = अणु
		.name	= "kxsd9",
		.of_match_table = kxsd9_of_match,
		.pm = &kxsd9_dev_pm_ops,
	पूर्ण,
	.probe		= kxsd9_i2c_probe,
	.हटाओ		= kxsd9_i2c_हटाओ,
	.id_table	= kxsd9_i2c_id,
पूर्ण;
module_i2c_driver(kxsd9_i2c_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("KXSD9 accelerometer I2C interface");
