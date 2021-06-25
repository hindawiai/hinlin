<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MFD driver क्रम Active-semi ACT8945a PMIC
 *
 * Copyright (C) 2015 Aपंचांगel Corporation.
 *
 * Author: Wenyou Yang <wenyou.yang@aपंचांगel.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

अटल स्थिर काष्ठा mfd_cell act8945a_devs[] = अणु
	अणु
		.name = "act8945a-regulator",
	पूर्ण,
	अणु
		.name = "act8945a-charger",
		.of_compatible = "active-semi,act8945a-charger",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config act8945a_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक act8945a_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &act8945a_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(i2c, regmap);

	ret = devm_mfd_add_devices(&i2c->dev, PLATFORM_DEVID_NONE,
				   act8945a_devs, ARRAY_SIZE(act8945a_devs),
				   शून्य, 0, शून्य);
	अगर (ret) अणु
		dev_err(&i2c->dev, "Failed to add sub devices\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id act8945a_i2c_id[] = अणु
	अणु "act8945a", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, act8945a_i2c_id);

अटल स्थिर काष्ठा of_device_id act8945a_of_match[] = अणु
	अणु .compatible = "active-semi,act8945a", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, act8945a_of_match);

अटल काष्ठा i2c_driver act8945a_i2c_driver = अणु
	.driver = अणु
		   .name = "act8945a",
		   .of_match_table = of_match_ptr(act8945a_of_match),
	पूर्ण,
	.probe = act8945a_i2c_probe,
	.id_table = act8945a_i2c_id,
पूर्ण;

अटल पूर्णांक __init act8945a_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&act8945a_i2c_driver);
पूर्ण
subsys_initcall(act8945a_i2c_init);

अटल व्योम __निकास act8945a_i2c_निकास(व्योम)
अणु
	i2c_del_driver(&act8945a_i2c_driver);
पूर्ण
module_निकास(act8945a_i2c_निकास);

MODULE_DESCRIPTION("ACT8945A PMIC multi-function driver");
MODULE_AUTHOR("Wenyou Yang <wenyou.yang@atmel.com>");
MODULE_LICENSE("GPL");
