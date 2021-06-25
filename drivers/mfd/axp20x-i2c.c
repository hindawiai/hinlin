<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C driver क्रम the X-Powers' Power Management ICs
 *
 * AXP20x typically comprises an adaptive USB-Compatible PWM अक्षरger, BUCK DC-DC
 * converters, LDOs, multiple 12-bit ADCs of voltage, current and temperature
 * as well as configurable GPIOs.
 *
 * This driver supports the I2C variants.
 *
 * Copyright (C) 2014 Carlo Caione
 *
 * Author: Carlo Caione <carlo@caione.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

अटल पूर्णांक axp20x_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा axp20x_dev *axp20x;
	पूर्णांक ret;

	axp20x = devm_kzalloc(&i2c->dev, माप(*axp20x), GFP_KERNEL);
	अगर (!axp20x)
		वापस -ENOMEM;

	axp20x->dev = &i2c->dev;
	axp20x->irq = i2c->irq;
	dev_set_drvdata(axp20x->dev, axp20x);

	ret = axp20x_match_device(axp20x);
	अगर (ret)
		वापस ret;

	axp20x->regmap = devm_regmap_init_i2c(i2c, axp20x->regmap_cfg);
	अगर (IS_ERR(axp20x->regmap)) अणु
		ret = PTR_ERR(axp20x->regmap);
		dev_err(&i2c->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस axp20x_device_probe(axp20x);
पूर्ण

अटल पूर्णांक axp20x_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	काष्ठा axp20x_dev *axp20x = i2c_get_clientdata(i2c);

	axp20x_device_हटाओ(axp20x);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id axp20x_i2c_of_match[] = अणु
	अणु .compatible = "x-powers,axp152", .data = (व्योम *)AXP152_ID पूर्ण,
	अणु .compatible = "x-powers,axp202", .data = (व्योम *)AXP202_ID पूर्ण,
	अणु .compatible = "x-powers,axp209", .data = (व्योम *)AXP209_ID पूर्ण,
	अणु .compatible = "x-powers,axp221", .data = (व्योम *)AXP221_ID पूर्ण,
	अणु .compatible = "x-powers,axp223", .data = (व्योम *)AXP223_ID पूर्ण,
	अणु .compatible = "x-powers,axp803", .data = (व्योम *)AXP803_ID पूर्ण,
	अणु .compatible = "x-powers,axp806", .data = (व्योम *)AXP806_ID पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axp20x_i2c_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id axp20x_i2c_id[] = अणु
	अणु "axp152", 0 पूर्ण,
	अणु "axp202", 0 पूर्ण,
	अणु "axp209", 0 पूर्ण,
	अणु "axp221", 0 पूर्ण,
	अणु "axp223", 0 पूर्ण,
	अणु "axp803", 0 पूर्ण,
	अणु "axp806", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, axp20x_i2c_id);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id axp20x_i2c_acpi_match[] = अणु
	अणु
		.id = "INT33F4",
		.driver_data = AXP288_ID,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, axp20x_i2c_acpi_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver axp20x_i2c_driver = अणु
	.driver = अणु
		.name	= "axp20x-i2c",
		.of_match_table	= of_match_ptr(axp20x_i2c_of_match),
		.acpi_match_table = ACPI_PTR(axp20x_i2c_acpi_match),
	पूर्ण,
	.probe		= axp20x_i2c_probe,
	.हटाओ		= axp20x_i2c_हटाओ,
	.id_table	= axp20x_i2c_id,
पूर्ण;

module_i2c_driver(axp20x_i2c_driver);

MODULE_DESCRIPTION("PMIC MFD I2C driver for AXP20X");
MODULE_AUTHOR("Carlo Caione <carlo@caione.org>");
MODULE_LICENSE("GPL");
