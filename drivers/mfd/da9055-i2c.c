<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /* I2C access क्रम DA9055 PMICs.
 *
 * Copyright(c) 2012 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/mfd/da9055/core.h>

अटल पूर्णांक da9055_i2c_probe(काष्ठा i2c_client *i2c,
				      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da9055 *da9055;
	पूर्णांक ret;

	da9055 = devm_kzalloc(&i2c->dev, माप(काष्ठा da9055), GFP_KERNEL);
	अगर (!da9055)
		वापस -ENOMEM;

	da9055->regmap = devm_regmap_init_i2c(i2c, &da9055_regmap_config);
	अगर (IS_ERR(da9055->regmap)) अणु
		ret = PTR_ERR(da9055->regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	da9055->dev = &i2c->dev;
	da9055->chip_irq = i2c->irq;

	i2c_set_clientdata(i2c, da9055);

	वापस da9055_device_init(da9055);
पूर्ण

अटल पूर्णांक da9055_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा da9055 *da9055 = i2c_get_clientdata(i2c);

	da9055_device_निकास(da9055);

	वापस 0;
पूर्ण

/*
 * DO NOT change the device Ids. The naming is पूर्णांकentionally specअगरic as both
 * the PMIC and CODEC parts of this chip are instantiated separately as I2C
 * devices (both have configurable I2C addresses, and are to all पूर्णांकents and
 * purposes separate). As a result there are specअगरic DA9055 ids क्रम PMIC
 * and CODEC, which must be dअगरferent to operate together.
 */
अटल स्थिर काष्ठा i2c_device_id da9055_i2c_id[] = अणु
	अणु"da9055-pmic", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da9055_i2c_id);

अटल स्थिर काष्ठा of_device_id da9055_of_match[] = अणु
	अणु .compatible = "dlg,da9055-pmic", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा i2c_driver da9055_i2c_driver = अणु
	.probe = da9055_i2c_probe,
	.हटाओ = da9055_i2c_हटाओ,
	.id_table = da9055_i2c_id,
	.driver = अणु
		.name = "da9055-pmic",
		.of_match_table = da9055_of_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init da9055_i2c_init(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&da9055_i2c_driver);
	अगर (ret != 0) अणु
		pr_err("DA9055 I2C registration failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(da9055_i2c_init);

अटल व्योम __निकास da9055_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&da9055_i2c_driver);
पूर्ण
module_निकास(da9055_i2c_निकास);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("I2C driver for Dialog DA9055 PMIC");
MODULE_LICENSE("GPL");
