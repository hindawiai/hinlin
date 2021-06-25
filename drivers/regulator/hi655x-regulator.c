<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Device driver क्रम regulators in Hi655x IC
//
// Copyright (c) 2016 HiSilicon Ltd.
//
// Authors:
// Chen Feng <puck.chen@hisilicon.com>
// Fei  Wang <w.f@huawei.com>

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/hi655x-pmic.h>

काष्ठा hi655x_regulator अणु
	अचिन्हित पूर्णांक disable_reg;
	अचिन्हित पूर्णांक status_reg;
	काष्ठा regulator_desc rdesc;
पूर्ण;

/* LDO7 & LDO10 */
अटल स्थिर अचिन्हित पूर्णांक lकरो7_voltages[] = अणु
	1800000, 1850000, 2850000, 2900000,
	3000000, 3100000, 3200000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो19_voltages[] = अणु
	1800000, 1850000, 1900000, 1750000,
	2800000, 2850000, 2900000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो22_voltages[] = अणु
	 900000, 1000000, 1050000, 1100000,
	1150000, 1175000, 1185000, 1200000,
पूर्ण;

क्रमागत hi655x_regulator_id अणु
	HI655X_LDO0,
	HI655X_LDO1,
	HI655X_LDO2,
	HI655X_LDO3,
	HI655X_LDO4,
	HI655X_LDO5,
	HI655X_LDO6,
	HI655X_LDO7,
	HI655X_LDO8,
	HI655X_LDO9,
	HI655X_LDO10,
	HI655X_LDO11,
	HI655X_LDO12,
	HI655X_LDO13,
	HI655X_LDO14,
	HI655X_LDO15,
	HI655X_LDO16,
	HI655X_LDO17,
	HI655X_LDO18,
	HI655X_LDO19,
	HI655X_LDO20,
	HI655X_LDO21,
	HI655X_LDO22,
पूर्ण;

अटल पूर्णांक hi655x_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक value = 0;
	काष्ठा hi655x_regulator *regulator = rdev_get_drvdata(rdev);

	regmap_पढ़ो(rdev->regmap, regulator->status_reg, &value);
	वापस (value & rdev->desc->enable_mask);
पूर्ण

अटल पूर्णांक hi655x_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा hi655x_regulator *regulator = rdev_get_drvdata(rdev);

	वापस regmap_ग_लिखो(rdev->regmap, regulator->disable_reg,
			    rdev->desc->enable_mask);
पूर्ण

अटल स्थिर काष्ठा regulator_ops hi655x_regulator_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = hi655x_disable,
	.is_enabled = hi655x_is_enabled,
	.list_voltage = regulator_list_voltage_table,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops hi655x_lकरो_linear_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = hi655x_disable,
	.is_enabled = hi655x_is_enabled,
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
पूर्ण;

#घोषणा HI655X_LDO(_ID, vreg, vmask, ereg, dreg,                 \
		   sreg, cmask, vtable) अणु                        \
	.rdesc = अणु                                               \
		.name            = #_ID,                         \
		.of_match        = of_match_ptr(#_ID),           \
		.ops             = &hi655x_regulator_ops,        \
		.regulators_node = of_match_ptr("regulators"),   \
		.type            = REGULATOR_VOLTAGE,            \
		.id              = HI655X_##_ID,                 \
		.owner           = THIS_MODULE,                  \
		.n_voltages      = ARRAY_SIZE(vtable),           \
		.volt_table      = vtable,                       \
		.vsel_reg        = HI655X_BUS_ADDR(vreg),        \
		.vsel_mask       = vmask,                        \
		.enable_reg      = HI655X_BUS_ADDR(ereg),        \
		.enable_mask     = BIT(cmask),                   \
	पूर्ण,                                                       \
	.disable_reg = HI655X_BUS_ADDR(dreg),                    \
	.status_reg = HI655X_BUS_ADDR(sreg),                     \
पूर्ण

#घोषणा HI655X_LDO_LINEAR(_ID, vreg, vmask, ereg, dreg,          \
			  sreg, cmask, minv, nvolt, vstep) अणु     \
	.rdesc = अणु                                               \
		.name            = #_ID,                         \
		.of_match        = of_match_ptr(#_ID),           \
		.ops             = &hi655x_lकरो_linear_ops,       \
		.regulators_node = of_match_ptr("regulators"),   \
		.type            = REGULATOR_VOLTAGE,            \
		.id              = HI655X_##_ID,                 \
		.owner           = THIS_MODULE,                  \
		.min_uV          = minv,                         \
		.n_voltages      = nvolt,                        \
		.uV_step         = vstep,                        \
		.vsel_reg        = HI655X_BUS_ADDR(vreg),        \
		.vsel_mask       = vmask,                        \
		.enable_reg      = HI655X_BUS_ADDR(ereg),        \
		.enable_mask     = BIT(cmask),                   \
	पूर्ण,                                                       \
	.disable_reg = HI655X_BUS_ADDR(dreg),                    \
	.status_reg = HI655X_BUS_ADDR(sreg),                     \
पूर्ण

अटल स्थिर काष्ठा hi655x_regulator regulators[] = अणु
	HI655X_LDO_LINEAR(LDO2, 0x72, 0x07, 0x29, 0x2a, 0x2b, 0x01,
			  2500000, 8, 100000),
	HI655X_LDO(LDO7, 0x78, 0x07, 0x29, 0x2a, 0x2b, 0x06, lकरो7_voltages),
	HI655X_LDO(LDO10, 0x78, 0x07, 0x29, 0x2a, 0x2b, 0x01, lकरो7_voltages),
	HI655X_LDO_LINEAR(LDO13, 0x7e, 0x07, 0x2c, 0x2d, 0x2e, 0x04,
			  1600000, 8, 50000),
	HI655X_LDO_LINEAR(LDO14, 0x7f, 0x07, 0x2c, 0x2d, 0x2e, 0x05,
			  2500000, 8, 100000),
	HI655X_LDO_LINEAR(LDO15, 0x80, 0x07, 0x2c, 0x2d, 0x2e, 0x06,
			  1600000, 8, 50000),
	HI655X_LDO_LINEAR(LDO17, 0x82, 0x07, 0x2f, 0x30, 0x31, 0x00,
			  2500000, 8, 100000),
	HI655X_LDO(LDO19, 0x84, 0x07, 0x2f, 0x30, 0x31, 0x02, lकरो19_voltages),
	HI655X_LDO_LINEAR(LDO21, 0x86, 0x07, 0x2f, 0x30, 0x31, 0x04,
			  1650000, 8, 50000),
	HI655X_LDO(LDO22, 0x87, 0x07, 0x2f, 0x30, 0x31, 0x05, lकरो22_voltages),
पूर्ण;

अटल पूर्णांक hi655x_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा hi655x_regulator *regulator;
	काष्ठा hi655x_pmic *pmic;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;

	pmic = dev_get_drvdata(pdev->dev.parent);
	अगर (!pmic) अणु
		dev_err(&pdev->dev, "no pmic in the regulator parent node\n");
		वापस -ENODEV;
	पूर्ण

	regulator = devm_kzalloc(&pdev->dev, माप(*regulator), GFP_KERNEL);
	अगर (!regulator)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, regulator);

	config.dev = pdev->dev.parent;
	config.regmap = pmic->regmap;
	config.driver_data = regulator;
	क्रम (i = 0; i < ARRAY_SIZE(regulators); i++) अणु
		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
					       &regulators[i].rdesc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				regulator->rdesc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id hi655x_regulator_table[] = अणु
	अणु .name = "hi655x-regulator" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, hi655x_regulator_table);

अटल काष्ठा platक्रमm_driver hi655x_regulator_driver = अणु
	.id_table = hi655x_regulator_table,
	.driver = अणु
		.name	= "hi655x-regulator",
	पूर्ण,
	.probe	= hi655x_regulator_probe,
पूर्ण;
module_platक्रमm_driver(hi655x_regulator_driver);

MODULE_AUTHOR("Chen Feng <puck.chen@hisilicon.com>");
MODULE_DESCRIPTION("Hisilicon Hi655x regulator driver");
MODULE_LICENSE("GPL v2");
