<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AS3711 PMIC regulator driver, using DCDC Step Down and LDO supplies
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 * Author: Guennadi Liakhovetski, <g.liakhovetski@gmx.de>
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/as3711.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/*
 * The regulator API supports 4 modes of operataion: FAST, NORMAL, IDLE and
 * STANDBY. We map them in the following way to AS3711 SD1-4 DCDC modes:
 * FAST:	sdX_fast=1
 * NORMAL:	low_noise=1
 * IDLE:	low_noise=0
 */

अटल पूर्णांक as3711_set_mode_sd(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक fast_bit = rdev->desc->enable_mask,
		low_noise_bit = fast_bit << 4;
	u8 val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = fast_bit | low_noise_bit;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = low_noise_bit;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, AS3711_SD_CONTROL_1,
				  low_noise_bit | fast_bit, val);
पूर्ण

अटल अचिन्हित पूर्णांक as3711_get_mode_sd(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक fast_bit = rdev->desc->enable_mask,
		low_noise_bit = fast_bit << 4, mask = fast_bit | low_noise_bit;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret = regmap_पढ़ो(rdev->regmap, AS3711_SD_CONTROL_1, &val);

	अगर (ret < 0)
		वापस ret;

	अगर ((val & mask) == mask)
		वापस REGULATOR_MODE_FAST;

	अगर ((val & mask) == low_noise_bit)
		वापस REGULATOR_MODE_NORMAL;

	अगर (!(val & mask))
		वापस REGULATOR_MODE_IDLE;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा regulator_ops as3711_sd_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_mode		= as3711_get_mode_sd,
	.set_mode		= as3711_set_mode_sd,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3711_alकरो_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3711_dlकरो_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
पूर्ण;

अटल स्थिर काष्ठा linear_range as3711_sd_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(612500, 0x1, 0x40, 12500),
	REGULATOR_LINEAR_RANGE(1425000, 0x41, 0x70, 25000),
	REGULATOR_LINEAR_RANGE(2650000, 0x71, 0x7f, 50000),
पूर्ण;

अटल स्थिर काष्ठा linear_range as3711_alकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1200000, 0, 0xf, 50000),
	REGULATOR_LINEAR_RANGE(1800000, 0x10, 0x1f, 100000),
पूर्ण;

अटल स्थिर काष्ठा linear_range as3711_dlकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0, 0x10, 50000),
	REGULATOR_LINEAR_RANGE(1750000, 0x20, 0x3f, 50000),
पूर्ण;

#घोषणा AS3711_REG(_id, _en_reg, _en_bit, _vmask, _sfx)			   \
	[AS3711_REGULATOR_ ## _id] = अणु					   \
		.name = "as3711-regulator-" # _id,			   \
		.id = AS3711_REGULATOR_ ## _id,				   \
		.n_voltages = (_vmask + 1),				   \
		.ops = &as3711_ ## _sfx ## _ops,			   \
		.type = REGULATOR_VOLTAGE,				   \
		.owner = THIS_MODULE,					   \
		.vsel_reg = AS3711_ ## _id ## _VOLTAGE,			   \
		.vsel_mask = _vmask,					   \
		.enable_reg = AS3711_ ## _en_reg,			   \
		.enable_mask = BIT(_en_bit),				   \
		.linear_ranges = as3711_ ## _sfx ## _ranges,		   \
		.n_linear_ranges = ARRAY_SIZE(as3711_ ## _sfx ## _ranges), \
पूर्ण

अटल स्थिर काष्ठा regulator_desc as3711_reg_desc[] = अणु
	AS3711_REG(SD_1, SD_CONTROL, 0, 0x7f, sd),
	AS3711_REG(SD_2, SD_CONTROL, 1, 0x7f, sd),
	AS3711_REG(SD_3, SD_CONTROL, 2, 0x7f, sd),
	AS3711_REG(SD_4, SD_CONTROL, 3, 0x7f, sd),
	AS3711_REG(LDO_1, LDO_1_VOLTAGE, 7, 0x1f, alकरो),
	AS3711_REG(LDO_2, LDO_2_VOLTAGE, 7, 0x1f, alकरो),
	AS3711_REG(LDO_3, LDO_3_VOLTAGE, 7, 0x3f, dlकरो),
	AS3711_REG(LDO_4, LDO_4_VOLTAGE, 7, 0x3f, dlकरो),
	AS3711_REG(LDO_5, LDO_5_VOLTAGE, 7, 0x3f, dlकरो),
	AS3711_REG(LDO_6, LDO_6_VOLTAGE, 7, 0x3f, dlकरो),
	AS3711_REG(LDO_7, LDO_7_VOLTAGE, 7, 0x3f, dlकरो),
	AS3711_REG(LDO_8, LDO_8_VOLTAGE, 7, 0x3f, dlकरो),
	/* StepUp output voltage depends on supplying regulator */
पूर्ण;

#घोषणा AS3711_REGULATOR_NUM ARRAY_SIZE(as3711_reg_desc)

अटल काष्ठा of_regulator_match
as3711_regulator_matches[AS3711_REGULATOR_NUM] = अणु
	[AS3711_REGULATOR_SD_1] = अणु .name = "sd1" पूर्ण,
	[AS3711_REGULATOR_SD_2] = अणु .name = "sd2" पूर्ण,
	[AS3711_REGULATOR_SD_3] = अणु .name = "sd3" पूर्ण,
	[AS3711_REGULATOR_SD_4] = अणु .name = "sd4" पूर्ण,
	[AS3711_REGULATOR_LDO_1] = अणु .name = "ldo1" पूर्ण,
	[AS3711_REGULATOR_LDO_2] = अणु .name = "ldo2" पूर्ण,
	[AS3711_REGULATOR_LDO_3] = अणु .name = "ldo3" पूर्ण,
	[AS3711_REGULATOR_LDO_4] = अणु .name = "ldo4" पूर्ण,
	[AS3711_REGULATOR_LDO_5] = अणु .name = "ldo5" पूर्ण,
	[AS3711_REGULATOR_LDO_6] = अणु .name = "ldo6" पूर्ण,
	[AS3711_REGULATOR_LDO_7] = अणु .name = "ldo7" पूर्ण,
	[AS3711_REGULATOR_LDO_8] = अणु .name = "ldo8" पूर्ण,
पूर्ण;

अटल पूर्णांक as3711_regulator_parse_dt(काष्ठा device *dev,
				काष्ठा device_node **of_node, स्थिर पूर्णांक count)
अणु
	काष्ठा as3711_regulator_pdata *pdata = dev_get_platdata(dev);
	काष्ठा device_node *regulators =
		of_get_child_by_name(dev->parent->of_node, "regulators");
	काष्ठा of_regulator_match *match;
	पूर्णांक ret, i;

	अगर (!regulators) अणु
		dev_err(dev, "regulator node not found\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_regulator_match(dev->parent, regulators,
				 as3711_regulator_matches, count);
	of_node_put(regulators);
	अगर (ret < 0) अणु
		dev_err(dev, "Error parsing regulator init data: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0, match = as3711_regulator_matches; i < count; i++, match++)
		अगर (match->of_node) अणु
			pdata->init_data[i] = match->init_data;
			of_node[i] = match->of_node;
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक as3711_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा as3711_regulator_pdata *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा as3711 *as3711 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु.dev = &pdev->dev,पूर्ण;
	काष्ठा device_node *of_node[AS3711_REGULATOR_NUM] = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक ret;
	पूर्णांक id;

	अगर (!pdata) अणु
		dev_err(&pdev->dev, "No platform data...\n");
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->dev.parent->of_node) अणु
		ret = as3711_regulator_parse_dt(&pdev->dev, of_node, AS3711_REGULATOR_NUM);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "DT parsing failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (id = 0; id < AS3711_REGULATOR_NUM; id++) अणु
		config.init_data = pdata->init_data[id];
		config.regmap = as3711->regmap;
		config.of_node = of_node[id];

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &as3711_reg_desc[id],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "Failed to register regulator %s\n",
				as3711_reg_desc[id].name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver as3711_regulator_driver = अणु
	.driver	= अणु
		.name	= "as3711-regulator",
	पूर्ण,
	.probe		= as3711_regulator_probe,
पूर्ण;

अटल पूर्णांक __init as3711_regulator_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&as3711_regulator_driver);
पूर्ण
subsys_initcall(as3711_regulator_init);

अटल व्योम __निकास as3711_regulator_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&as3711_regulator_driver);
पूर्ण
module_निकास(as3711_regulator_निकास);

MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_DESCRIPTION("AS3711 regulator driver");
MODULE_ALIAS("platform:as3711-regulator");
MODULE_LICENSE("GPL v2");
