<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RSB driver क्रम the X-Powers' Power Management ICs
 *
 * AXP20x typically comprises an adaptive USB-Compatible PWM अक्षरger, BUCK DC-DC
 * converters, LDOs, multiple 12-bit ADCs of voltage, current and temperature
 * as well as configurable GPIOs.
 *
 * This driver supports the RSB variants.
 *
 * Copyright (C) 2015 Chen-Yu Tsai
 *
 * Author: Chen-Yu Tsai <wens@csie.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/axp20x.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunxi-rsb.h>

अटल पूर्णांक axp20x_rsb_probe(काष्ठा sunxi_rsb_device *rdev)
अणु
	काष्ठा axp20x_dev *axp20x;
	पूर्णांक ret;

	axp20x = devm_kzalloc(&rdev->dev, माप(*axp20x), GFP_KERNEL);
	अगर (!axp20x)
		वापस -ENOMEM;

	axp20x->dev = &rdev->dev;
	axp20x->irq = rdev->irq;
	dev_set_drvdata(&rdev->dev, axp20x);

	ret = axp20x_match_device(axp20x);
	अगर (ret)
		वापस ret;

	axp20x->regmap = devm_regmap_init_sunxi_rsb(rdev, axp20x->regmap_cfg);
	अगर (IS_ERR(axp20x->regmap)) अणु
		ret = PTR_ERR(axp20x->regmap);
		dev_err(&rdev->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस axp20x_device_probe(axp20x);
पूर्ण

अटल व्योम axp20x_rsb_हटाओ(काष्ठा sunxi_rsb_device *rdev)
अणु
	काष्ठा axp20x_dev *axp20x = sunxi_rsb_device_get_drvdata(rdev);

	axp20x_device_हटाओ(axp20x);
पूर्ण

अटल स्थिर काष्ठा of_device_id axp20x_rsb_of_match[] = अणु
	अणु .compatible = "x-powers,axp223", .data = (व्योम *)AXP223_ID पूर्ण,
	अणु .compatible = "x-powers,axp803", .data = (व्योम *)AXP803_ID पूर्ण,
	अणु .compatible = "x-powers,axp806", .data = (व्योम *)AXP806_ID पूर्ण,
	अणु .compatible = "x-powers,axp809", .data = (व्योम *)AXP809_ID पूर्ण,
	अणु .compatible = "x-powers,axp813", .data = (व्योम *)AXP813_ID पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, axp20x_rsb_of_match);

अटल काष्ठा sunxi_rsb_driver axp20x_rsb_driver = अणु
	.driver = अणु
		.name	= "axp20x-rsb",
		.of_match_table	= of_match_ptr(axp20x_rsb_of_match),
	पूर्ण,
	.probe	= axp20x_rsb_probe,
	.हटाओ	= axp20x_rsb_हटाओ,
पूर्ण;
module_sunxi_rsb_driver(axp20x_rsb_driver);

MODULE_DESCRIPTION("PMIC MFD sunXi RSB driver for AXP20X");
MODULE_AUTHOR("Chen-Yu Tsai <wens@csie.org>");
MODULE_LICENSE("GPL v2");
