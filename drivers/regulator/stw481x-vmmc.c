<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम STw4810/STw4811 VMMC regulator.
 *
 * Copyright (C) 2013 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/stw481x.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>

अटल स्थिर अचिन्हित पूर्णांक stw481x_vmmc_voltages[] = अणु
	1800000,
	1800000,
	2850000,
	3000000,
	1850000,
	2600000,
	2700000,
	3300000,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stw481x_vmmc_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.enable      = regulator_enable_regmap,
	.disable     = regulator_disable_regmap,
	.is_enabled  = regulator_is_enabled_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc vmmc_regulator = अणु
	.name = "VMMC",
	.id   = 0,
	.ops  = &stw481x_vmmc_ops,
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
	.n_voltages = ARRAY_SIZE(stw481x_vmmc_voltages),
	.volt_table = stw481x_vmmc_voltages,
	.enable_समय = 200, /* FIXME: look this up */
	.enable_reg = STW_CONF1,
	.enable_mask = STW_CONF1_PDN_VMMC | STW_CONF1_MMC_LS_STATUS,
	.enable_val = STW_CONF1_PDN_VMMC,
	.vsel_reg = STW_CONF1,
	.vsel_mask = STW_CONF1_VMMC_MASK,
पूर्ण;

अटल पूर्णांक stw481x_vmmc_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा stw481x *stw481x = dev_get_platdata(&pdev->dev);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;

	/* First disable the बाह्यal VMMC अगर it's active */
	ret = regmap_update_bits(stw481x->map, STW_CONF2,
				 STW_CONF2_VMMC_EXT, 0);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not disable external VMMC\n");
		वापस ret;
	पूर्ण

	/* Register VMMC regulator */
	config.dev = &pdev->dev;
	config.driver_data = stw481x;
	config.regmap = stw481x->map;
	config.of_node = pdev->dev.of_node;
	config.init_data = of_get_regulator_init_data(&pdev->dev,
						      pdev->dev.of_node,
						      &vmmc_regulator);

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &vmmc_regulator, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev,
			"error initializing STw481x VMMC regulator\n");
		वापस PTR_ERR(rdev);
	पूर्ण

	dev_info(&pdev->dev, "initialized STw481x VMMC regulator\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id stw481x_vmmc_match[] = अणु
	अणु .compatible = "st,stw481x-vmmc", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver stw481x_vmmc_regulator_driver = अणु
	.driver = अणु
		.name  = "stw481x-vmmc-regulator",
		.of_match_table = stw481x_vmmc_match,
	पूर्ण,
	.probe = stw481x_vmmc_regulator_probe,
पूर्ण;

module_platक्रमm_driver(stw481x_vmmc_regulator_driver);
