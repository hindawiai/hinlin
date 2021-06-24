<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Simple MFD - I2C
 *
 * This driver creates a single रेजिस्टर map with the पूर्णांकention क्रम it to be
 * shared by all sub-devices.  Children can use their parent's device काष्ठाure
 * (dev.parent) in order to reference it.
 *
 * Once the रेजिस्टर map has been successfully initialised, any sub-devices
 * represented by child nodes in Device Tree will be subsequently रेजिस्टरed.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा regmap_config simple_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक simple_mfd_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	स्थिर काष्ठा regmap_config *config;
	काष्ठा regmap *regmap;

	config = device_get_match_data(&i2c->dev);
	अगर (!config)
		config = &simple_regmap_config;

	regmap = devm_regmap_init_i2c(i2c, config);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस devm_of_platक्रमm_populate(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id simple_mfd_i2c_of_match[] = अणु
	अणु .compatible = "kontron,sl28cpld" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, simple_mfd_i2c_of_match);

अटल काष्ठा i2c_driver simple_mfd_i2c_driver = अणु
	.probe_new = simple_mfd_i2c_probe,
	.driver = अणु
		.name = "simple-mfd-i2c",
		.of_match_table = simple_mfd_i2c_of_match,
	पूर्ण,
पूर्ण;
module_i2c_driver(simple_mfd_i2c_driver);

MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_DESCRIPTION("Simple MFD - I2C driver");
MODULE_LICENSE("GPL v2");
