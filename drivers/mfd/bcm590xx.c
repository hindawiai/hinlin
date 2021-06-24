<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom BCM590xx PMU
 *
 * Copyright 2014 Linaro Limited
 * Author: Matt Porter <mporter@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/bcm590xx.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल स्थिर काष्ठा mfd_cell bcm590xx_devs[] = अणु
	अणु
		.name = "bcm590xx-vregs",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bcm590xx_regmap_config_pri = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= BCM590XX_MAX_REGISTER_PRI,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bcm590xx_regmap_config_sec = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= BCM590XX_MAX_REGISTER_SEC,
	.cache_type	= REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक bcm590xx_i2c_probe(काष्ठा i2c_client *i2c_pri,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा bcm590xx *bcm590xx;
	पूर्णांक ret;

	bcm590xx = devm_kzalloc(&i2c_pri->dev, माप(*bcm590xx), GFP_KERNEL);
	अगर (!bcm590xx)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c_pri, bcm590xx);
	bcm590xx->dev = &i2c_pri->dev;
	bcm590xx->i2c_pri = i2c_pri;

	bcm590xx->regmap_pri = devm_regmap_init_i2c(i2c_pri,
						 &bcm590xx_regmap_config_pri);
	अगर (IS_ERR(bcm590xx->regmap_pri)) अणु
		ret = PTR_ERR(bcm590xx->regmap_pri);
		dev_err(&i2c_pri->dev, "primary regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Secondary I2C slave address is the base address with A(2) निश्चितed */
	bcm590xx->i2c_sec = i2c_new_dummy_device(i2c_pri->adapter,
					  i2c_pri->addr | BIT(2));
	अगर (IS_ERR(bcm590xx->i2c_sec)) अणु
		dev_err(&i2c_pri->dev, "failed to add secondary I2C device\n");
		वापस PTR_ERR(bcm590xx->i2c_sec);
	पूर्ण
	i2c_set_clientdata(bcm590xx->i2c_sec, bcm590xx);

	bcm590xx->regmap_sec = devm_regmap_init_i2c(bcm590xx->i2c_sec,
						&bcm590xx_regmap_config_sec);
	अगर (IS_ERR(bcm590xx->regmap_sec)) अणु
		ret = PTR_ERR(bcm590xx->regmap_sec);
		dev_err(&bcm590xx->i2c_sec->dev,
			"secondary regmap init failed: %d\n", ret);
		जाओ err;
	पूर्ण

	ret = devm_mfd_add_devices(&i2c_pri->dev, -1, bcm590xx_devs,
				   ARRAY_SIZE(bcm590xx_devs), शून्य, 0, शून्य);
	अगर (ret < 0) अणु
		dev_err(&i2c_pri->dev, "failed to add sub-devices: %d\n", ret);
		जाओ err;
	पूर्ण

	वापस 0;

err:
	i2c_unरेजिस्टर_device(bcm590xx->i2c_sec);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm590xx_of_match[] = अणु
	अणु .compatible = "brcm,bcm59056" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm590xx_of_match);

अटल स्थिर काष्ठा i2c_device_id bcm590xx_i2c_id[] = अणु
	अणु "bcm59056" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bcm590xx_i2c_id);

अटल काष्ठा i2c_driver bcm590xx_i2c_driver = अणु
	.driver = अणु
		   .name = "bcm590xx",
		   .of_match_table = bcm590xx_of_match,
	पूर्ण,
	.probe = bcm590xx_i2c_probe,
	.id_table = bcm590xx_i2c_id,
पूर्ण;
module_i2c_driver(bcm590xx_i2c_driver);

MODULE_AUTHOR("Matt Porter <mporter@linaro.org>");
MODULE_DESCRIPTION("BCM590xx multi-function driver");
MODULE_LICENSE("GPL v2");
