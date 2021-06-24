<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Regulator support क्रम WM8400
//
// Copyright 2008 Wolfson Microelectronics PLC.
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/mfd/wm8400-निजी.h>

अटल स्थिर काष्ठा linear_range wm8400_lकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0, 14, 50000),
	REGULATOR_LINEAR_RANGE(1700000, 15, 31, 100000),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops wm8400_lकरो_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.map_voltage = regulator_map_voltage_linear_range,
पूर्ण;

अटल अचिन्हित पूर्णांक wm8400_dcdc_get_mode(काष्ठा regulator_dev *dev)
अणु
	काष्ठा regmap *rmap = rdev_get_regmap(dev);
	पूर्णांक offset = (rdev_get_id(dev) - WM8400_DCDC1) * 2;
	u16 data[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rmap, WM8400_DCDC1_CONTROL_1 + offset, data, 2);
	अगर (ret != 0)
		वापस 0;

	/* Datasheet: hibernate */
	अगर (data[0] & WM8400_DC1_SLEEP)
		वापस REGULATOR_MODE_STANDBY;

	/* Datasheet: standby */
	अगर (!(data[0] & WM8400_DC1_ACTIVE))
		वापस REGULATOR_MODE_IDLE;

	/* Datasheet: active with or without क्रमce PWM */
	अगर (data[1] & WM8400_DC1_FRC_PWM)
		वापस REGULATOR_MODE_FAST;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक wm8400_dcdc_set_mode(काष्ठा regulator_dev *dev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा regmap *rmap = rdev_get_regmap(dev);
	पूर्णांक offset = (rdev_get_id(dev) - WM8400_DCDC1) * 2;
	पूर्णांक ret;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		/* Datasheet: active with क्रमce PWM */
		ret = regmap_update_bits(rmap, WM8400_DCDC1_CONTROL_2 + offset,
				      WM8400_DC1_FRC_PWM, WM8400_DC1_FRC_PWM);
		अगर (ret != 0)
			वापस ret;

		वापस regmap_update_bits(rmap, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP,
				       WM8400_DC1_ACTIVE);

	हाल REGULATOR_MODE_NORMAL:
		/* Datasheet: active */
		ret = regmap_update_bits(rmap, WM8400_DCDC1_CONTROL_2 + offset,
				      WM8400_DC1_FRC_PWM, 0);
		अगर (ret != 0)
			वापस ret;

		वापस regmap_update_bits(rmap, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP,
				       WM8400_DC1_ACTIVE);

	हाल REGULATOR_MODE_IDLE:
		/* Datasheet: standby */
		वापस regmap_update_bits(rmap, WM8400_DCDC1_CONTROL_1 + offset,
				       WM8400_DC1_ACTIVE | WM8400_DC1_SLEEP, 0);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक wm8400_dcdc_get_optimum_mode(काष्ठा regulator_dev *dev,
						 पूर्णांक input_uV, पूर्णांक output_uV,
						 पूर्णांक load_uA)
अणु
	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops wm8400_dcdc_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_mode = wm8400_dcdc_get_mode,
	.set_mode = wm8400_dcdc_set_mode,
	.get_optimum_mode = wm8400_dcdc_get_optimum_mode,
पूर्ण;

अटल काष्ठा regulator_desc regulators[] = अणु
	अणु
		.name = "LDO1",
		.id = WM8400_LDO1,
		.ops = &wm8400_lकरो_ops,
		.enable_reg = WM8400_LDO1_CONTROL,
		.enable_mask = WM8400_LDO1_ENA,
		.n_voltages = WM8400_LDO1_VSEL_MASK + 1,
		.linear_ranges = wm8400_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8400_lकरो_ranges),
		.vsel_reg = WM8400_LDO1_CONTROL,
		.vsel_mask = WM8400_LDO1_VSEL_MASK,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO2",
		.id = WM8400_LDO2,
		.ops = &wm8400_lकरो_ops,
		.enable_reg = WM8400_LDO2_CONTROL,
		.enable_mask = WM8400_LDO2_ENA,
		.n_voltages = WM8400_LDO2_VSEL_MASK + 1,
		.linear_ranges = wm8400_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8400_lकरो_ranges),
		.type = REGULATOR_VOLTAGE,
		.vsel_reg = WM8400_LDO2_CONTROL,
		.vsel_mask = WM8400_LDO2_VSEL_MASK,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO3",
		.id = WM8400_LDO3,
		.ops = &wm8400_lकरो_ops,
		.enable_reg = WM8400_LDO3_CONTROL,
		.enable_mask = WM8400_LDO3_ENA,
		.n_voltages = WM8400_LDO3_VSEL_MASK + 1,
		.linear_ranges = wm8400_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8400_lकरो_ranges),
		.vsel_reg = WM8400_LDO3_CONTROL,
		.vsel_mask = WM8400_LDO3_VSEL_MASK,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO4",
		.id = WM8400_LDO4,
		.ops = &wm8400_lकरो_ops,
		.enable_reg = WM8400_LDO4_CONTROL,
		.enable_mask = WM8400_LDO4_ENA,
		.n_voltages = WM8400_LDO4_VSEL_MASK + 1,
		.linear_ranges = wm8400_lकरो_ranges,
		.n_linear_ranges = ARRAY_SIZE(wm8400_lकरो_ranges),
		.vsel_reg = WM8400_LDO4_CONTROL,
		.vsel_mask = WM8400_LDO4_VSEL_MASK,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC1",
		.id = WM8400_DCDC1,
		.ops = &wm8400_dcdc_ops,
		.enable_reg = WM8400_DCDC1_CONTROL_1,
		.enable_mask = WM8400_DC1_ENA_MASK,
		.n_voltages = WM8400_DC1_VSEL_MASK + 1,
		.vsel_reg = WM8400_DCDC1_CONTROL_1,
		.vsel_mask = WM8400_DC1_VSEL_MASK,
		.min_uV = 850000,
		.uV_step = 25000,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC2",
		.id = WM8400_DCDC2,
		.ops = &wm8400_dcdc_ops,
		.enable_reg = WM8400_DCDC2_CONTROL_1,
		.enable_mask = WM8400_DC2_ENA_MASK,
		.n_voltages = WM8400_DC2_VSEL_MASK + 1,
		.vsel_reg = WM8400_DCDC2_CONTROL_1,
		.vsel_mask = WM8400_DC2_VSEL_MASK,
		.min_uV = 850000,
		.uV_step = 25000,
		.type = REGULATOR_VOLTAGE,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm8400_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8400 *wm8400 = container_of(pdev, काष्ठा wm8400, regulators[pdev->id]);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;

	config.dev = &pdev->dev;
	config.init_data = dev_get_platdata(&pdev->dev);
	config.driver_data = wm8400;
	config.regmap = wm8400->regmap;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &regulators[pdev->id],
				       &config);
	अगर (IS_ERR(rdev))
		वापस PTR_ERR(rdev);

	platक्रमm_set_drvdata(pdev, rdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8400_regulator_driver = अणु
	.driver = अणु
		.name = "wm8400-regulator",
	पूर्ण,
	.probe = wm8400_regulator_probe,
पूर्ण;

/**
 * wm8400_रेजिस्टर_regulator - enable software control of a WM8400 regulator
 *
 * This function enables software control of a WM8400 regulator via
 * the regulator API.  It is पूर्णांकended to be called from the
 * platक्रमm_init() callback of the WM8400 MFD driver.
 *
 * @dev:      The WM8400 device to operate on.
 * @reg:      The regulator to control.
 * @initdata: Regulator initdata क्रम the regulator.
 */
पूर्णांक wm8400_रेजिस्टर_regulator(काष्ठा device *dev, पूर्णांक reg,
			      काष्ठा regulator_init_data *initdata)
अणु
	काष्ठा wm8400 *wm8400 = dev_get_drvdata(dev);

	अगर (wm8400->regulators[reg].name)
		वापस -EBUSY;

	initdata->driver_data = wm8400;

	wm8400->regulators[reg].name = "wm8400-regulator";
	wm8400->regulators[reg].id = reg;
	wm8400->regulators[reg].dev.parent = dev;
	wm8400->regulators[reg].dev.platक्रमm_data = initdata;

	वापस platक्रमm_device_रेजिस्टर(&wm8400->regulators[reg]);
पूर्ण
EXPORT_SYMBOL_GPL(wm8400_रेजिस्टर_regulator);

अटल पूर्णांक __init wm8400_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&wm8400_regulator_driver);
पूर्ण
subsys_initcall(wm8400_regulator_init);

अटल व्योम __निकास wm8400_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wm8400_regulator_driver);
पूर्ण
module_निकास(wm8400_regulator_निकास);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("WM8400 regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8400-regulator");
