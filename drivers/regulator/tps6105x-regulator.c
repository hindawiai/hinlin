<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम TPS61050/61052 boost converters, typically used क्रम white LEDs
 * or audio amplअगरiers.
 *
 * Copyright (C) 2011 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/tps6105x.h>

अटल स्थिर अचिन्हित पूर्णांक tps6105x_voltages[] = अणु
	4500000,
	5000000,
	5250000,
	5000000, /* There is an additional 5V */
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps6105x_regulator_ops = अणु
	.enable		= regulator_enable_regmap,
	.disable	= regulator_disable_regmap,
	.is_enabled	= regulator_is_enabled_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.list_voltage	= regulator_list_voltage_table,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc tps6105x_regulator_desc = अणु
	.name		= "tps6105x-boost",
	.of_match	= of_match_ptr("regulator"),
	.ops		= &tps6105x_regulator_ops,
	.type		= REGULATOR_VOLTAGE,
	.id		= 0,
	.owner		= THIS_MODULE,
	.n_voltages	= ARRAY_SIZE(tps6105x_voltages),
	.volt_table	= tps6105x_voltages,
	.vsel_reg	= TPS6105X_REG_0,
	.vsel_mask	= TPS6105X_REG0_VOLTAGE_MASK,
	.enable_reg	= TPS6105X_REG_0,
	.enable_mask	= TPS6105X_REG0_MODE_MASK,
	.enable_val	= TPS6105X_REG0_MODE_VOLTAGE <<
			  TPS6105X_REG0_MODE_SHIFT,
पूर्ण;

/*
 * Registers the chip as a voltage regulator
 */
अटल पूर्णांक tps6105x_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps6105x *tps6105x = dev_get_platdata(&pdev->dev);
	काष्ठा tps6105x_platक्रमm_data *pdata = tps6105x->pdata;
	काष्ठा regulator_config config = अणु पूर्ण;
	पूर्णांक ret;

	/* This instance is not set क्रम regulator mode so bail out */
	अगर (pdata->mode != TPS6105X_MODE_VOLTAGE) अणु
		dev_info(&pdev->dev,
			"chip not in voltage mode mode, exit probe\n");
		वापस 0;
	पूर्ण

	config.dev = &tps6105x->client->dev;
	config.init_data = pdata->regulator_data;
	config.driver_data = tps6105x;
	config.of_node = pdev->dev.parent->of_node;
	config.regmap = tps6105x->regmap;

	/* Register regulator with framework */
	tps6105x->regulator = devm_regulator_रेजिस्टर(&pdev->dev,
						      &tps6105x_regulator_desc,
						      &config);
	अगर (IS_ERR(tps6105x->regulator)) अणु
		ret = PTR_ERR(tps6105x->regulator);
		dev_err(&tps6105x->client->dev,
			"failed to register regulator\n");
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, tps6105x);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver tps6105x_regulator_driver = अणु
	.driver = अणु
		.name  = "tps6105x-regulator",
	पूर्ण,
	.probe = tps6105x_regulator_probe,
पूर्ण;

अटल __init पूर्णांक tps6105x_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps6105x_regulator_driver);
पूर्ण
subsys_initcall(tps6105x_regulator_init);

अटल __निकास व्योम tps6105x_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps6105x_regulator_driver);
पूर्ण
module_निकास(tps6105x_regulator_निकास);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("TPS6105x regulator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tps6105x-regulator");
