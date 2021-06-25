<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 BayLibre SAS
// Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
//
// Regulator driver क्रम MAXIM 77650/77651 अक्षरger/घातer-supply.

#समावेश <linux/of.h>
#समावेश <linux/mfd/max77650.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>

#घोषणा MAX77650_REGULATOR_EN_CTRL_MASK		GENMASK(3, 0)
#घोषणा MAX77650_REGULATOR_EN_CTRL_BITS(_reg) \
		((_reg) & MAX77650_REGULATOR_EN_CTRL_MASK)
#घोषणा MAX77650_REGULATOR_ENABLED		GENMASK(2, 1)
#घोषणा MAX77650_REGULATOR_DISABLED		BIT(2)

#घोषणा MAX77650_REGULATOR_V_LDO_MASK		GENMASK(6, 0)
#घोषणा MAX77650_REGULATOR_V_SBB_MASK		GENMASK(5, 0)
#घोषणा MAX77651_REGULATOR_V_SBB1_MASK		GENMASK(5, 2)
#घोषणा MAX77651_REGULATOR_V_SBB1_RANGE_MASK	GENMASK(1, 0)

#घोषणा MAX77650_REGULATOR_AD_MASK		BIT(3)
#घोषणा MAX77650_REGULATOR_AD_DISABLED		0x00
#घोषणा MAX77650_REGULATOR_AD_ENABLED		BIT(3)

#घोषणा MAX77650_REGULATOR_CURR_LIM_MASK	GENMASK(7, 6)

क्रमागत अणु
	MAX77650_REGULATOR_ID_LDO = 0,
	MAX77650_REGULATOR_ID_SBB0,
	MAX77650_REGULATOR_ID_SBB1,
	MAX77650_REGULATOR_ID_SBB2,
	MAX77650_REGULATOR_NUM_REGULATORS,
पूर्ण;

काष्ठा max77650_regulator_desc अणु
	काष्ठा regulator_desc desc;
	अचिन्हित पूर्णांक regA;
	अचिन्हित पूर्णांक regB;
पूर्ण;

अटल काष्ठा max77650_regulator_desc max77651_SBB1_desc;

अटल स्थिर अचिन्हित पूर्णांक max77651_sbb1_volt_range_sel[] = अणु
	0x0, 0x1, 0x2, 0x3
पूर्ण;

अटल स्थिर काष्ठा linear_range max77651_sbb1_volt_ranges[] = अणु
	/* range index 0 */
	REGULATOR_LINEAR_RANGE(2400000, 0x00, 0x0f, 50000),
	/* range index 1 */
	REGULATOR_LINEAR_RANGE(3200000, 0x00, 0x0f, 50000),
	/* range index 2 */
	REGULATOR_LINEAR_RANGE(4000000, 0x00, 0x0f, 50000),
	/* range index 3 */
	REGULATOR_LINEAR_RANGE(4800000, 0x00, 0x09, 50000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक max77650_current_limit_table[] = अणु
	1000000, 866000, 707000, 500000,
पूर्ण;

अटल पूर्णांक max77650_regulator_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77650_regulator_desc *rdesc;
	काष्ठा regmap *map;
	पूर्णांक val, rv, en;

	rdesc = rdev_get_drvdata(rdev);
	map = rdev_get_regmap(rdev);

	rv = regmap_पढ़ो(map, rdesc->regB, &val);
	अगर (rv)
		वापस rv;

	en = MAX77650_REGULATOR_EN_CTRL_BITS(val);

	वापस en != MAX77650_REGULATOR_DISABLED;
पूर्ण

अटल पूर्णांक max77650_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77650_regulator_desc *rdesc;
	काष्ठा regmap *map;

	rdesc = rdev_get_drvdata(rdev);
	map = rdev_get_regmap(rdev);

	वापस regmap_update_bits(map, rdesc->regB,
				  MAX77650_REGULATOR_EN_CTRL_MASK,
				  MAX77650_REGULATOR_ENABLED);
पूर्ण

अटल पूर्णांक max77650_regulator_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77650_regulator_desc *rdesc;
	काष्ठा regmap *map;

	rdesc = rdev_get_drvdata(rdev);
	map = rdev_get_regmap(rdev);

	वापस regmap_update_bits(map, rdesc->regB,
				  MAX77650_REGULATOR_EN_CTRL_MASK,
				  MAX77650_REGULATOR_DISABLED);
पूर्ण

अटल स्थिर काष्ठा regulator_ops max77650_regulator_LDO_ops = अणु
	.is_enabled		= max77650_regulator_is_enabled,
	.enable			= max77650_regulator_enable,
	.disable		= max77650_regulator_disable,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77650_regulator_SBB_ops = अणु
	.is_enabled		= max77650_regulator_is_enabled,
	.enable			= max77650_regulator_enable,
	.disable		= max77650_regulator_disable,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.get_current_limit	= regulator_get_current_limit_regmap,
	.set_current_limit	= regulator_set_current_limit_regmap,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
पूर्ण;

/* Special हाल क्रम max77651 SBB1 - pickable linear-range voltage mapping. */
अटल स्थिर काष्ठा regulator_ops max77651_SBB1_regulator_ops = अणु
	.is_enabled		= max77650_regulator_is_enabled,
	.enable			= max77650_regulator_enable,
	.disable		= max77650_regulator_disable,
	.list_voltage		= regulator_list_voltage_pickable_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_pickable_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_pickable_regmap,
	.get_current_limit	= regulator_get_current_limit_regmap,
	.set_current_limit	= regulator_set_current_limit_regmap,
	.set_active_disअक्षरge	= regulator_set_active_disअक्षरge_regmap,
पूर्ण;

अटल काष्ठा max77650_regulator_desc max77650_LDO_desc = अणु
	.desc = अणु
		.name			= "ldo",
		.of_match		= of_match_ptr("ldo"),
		.regulators_node	= of_match_ptr("regulators"),
		.supply_name		= "in-ldo",
		.id			= MAX77650_REGULATOR_ID_LDO,
		.ops			= &max77650_regulator_LDO_ops,
		.min_uV			= 1350000,
		.uV_step		= 12500,
		.n_voltages		= 128,
		.vsel_step		= 1,
		.vsel_mask		= MAX77650_REGULATOR_V_LDO_MASK,
		.vsel_reg		= MAX77650_REG_CNFG_LDO_A,
		.active_disअक्षरge_off	= MAX77650_REGULATOR_AD_DISABLED,
		.active_disअक्षरge_on	= MAX77650_REGULATOR_AD_ENABLED,
		.active_disअक्षरge_mask	= MAX77650_REGULATOR_AD_MASK,
		.active_disअक्षरge_reg	= MAX77650_REG_CNFG_LDO_B,
		.enable_समय		= 100,
		.type			= REGULATOR_VOLTAGE,
		.owner			= THIS_MODULE,
	पूर्ण,
	.regA		= MAX77650_REG_CNFG_LDO_A,
	.regB		= MAX77650_REG_CNFG_LDO_B,
पूर्ण;

अटल काष्ठा max77650_regulator_desc max77650_SBB0_desc = अणु
	.desc = अणु
		.name			= "sbb0",
		.of_match		= of_match_ptr("sbb0"),
		.regulators_node	= of_match_ptr("regulators"),
		.supply_name		= "in-sbb0",
		.id			= MAX77650_REGULATOR_ID_SBB0,
		.ops			= &max77650_regulator_SBB_ops,
		.min_uV			= 800000,
		.uV_step		= 25000,
		.n_voltages		= 64,
		.vsel_step		= 1,
		.vsel_mask		= MAX77650_REGULATOR_V_SBB_MASK,
		.vsel_reg		= MAX77650_REG_CNFG_SBB0_A,
		.active_disअक्षरge_off	= MAX77650_REGULATOR_AD_DISABLED,
		.active_disअक्षरge_on	= MAX77650_REGULATOR_AD_ENABLED,
		.active_disअक्षरge_mask	= MAX77650_REGULATOR_AD_MASK,
		.active_disअक्षरge_reg	= MAX77650_REG_CNFG_SBB0_B,
		.enable_समय		= 100,
		.type			= REGULATOR_VOLTAGE,
		.owner			= THIS_MODULE,
		.csel_reg		= MAX77650_REG_CNFG_SBB0_A,
		.csel_mask		= MAX77650_REGULATOR_CURR_LIM_MASK,
		.curr_table		= max77650_current_limit_table,
		.n_current_limits = ARRAY_SIZE(max77650_current_limit_table),
	पूर्ण,
	.regA		= MAX77650_REG_CNFG_SBB0_A,
	.regB		= MAX77650_REG_CNFG_SBB0_B,
पूर्ण;

अटल काष्ठा max77650_regulator_desc max77650_SBB1_desc = अणु
	.desc = अणु
		.name			= "sbb1",
		.of_match		= of_match_ptr("sbb1"),
		.regulators_node	= of_match_ptr("regulators"),
		.supply_name		= "in-sbb1",
		.id			= MAX77650_REGULATOR_ID_SBB1,
		.ops			= &max77650_regulator_SBB_ops,
		.min_uV			= 800000,
		.uV_step		= 12500,
		.n_voltages		= 64,
		.vsel_step		= 1,
		.vsel_mask		= MAX77650_REGULATOR_V_SBB_MASK,
		.vsel_reg		= MAX77650_REG_CNFG_SBB1_A,
		.active_disअक्षरge_off	= MAX77650_REGULATOR_AD_DISABLED,
		.active_disअक्षरge_on	= MAX77650_REGULATOR_AD_ENABLED,
		.active_disअक्षरge_mask	= MAX77650_REGULATOR_AD_MASK,
		.active_disअक्षरge_reg	= MAX77650_REG_CNFG_SBB1_B,
		.enable_समय		= 100,
		.type			= REGULATOR_VOLTAGE,
		.owner			= THIS_MODULE,
		.csel_reg		= MAX77650_REG_CNFG_SBB1_A,
		.csel_mask		= MAX77650_REGULATOR_CURR_LIM_MASK,
		.curr_table		= max77650_current_limit_table,
		.n_current_limits = ARRAY_SIZE(max77650_current_limit_table),
	पूर्ण,
	.regA		= MAX77650_REG_CNFG_SBB1_A,
	.regB		= MAX77650_REG_CNFG_SBB1_B,
पूर्ण;

अटल काष्ठा max77650_regulator_desc max77651_SBB1_desc = अणु
	.desc = अणु
		.name			= "sbb1",
		.of_match		= of_match_ptr("sbb1"),
		.regulators_node	= of_match_ptr("regulators"),
		.supply_name		= "in-sbb1",
		.id			= MAX77650_REGULATOR_ID_SBB1,
		.ops			= &max77651_SBB1_regulator_ops,
		.linear_range_selectors	= max77651_sbb1_volt_range_sel,
		.linear_ranges		= max77651_sbb1_volt_ranges,
		.n_linear_ranges	= ARRAY_SIZE(max77651_sbb1_volt_ranges),
		.n_voltages		= 58,
		.vsel_step		= 1,
		.vsel_range_mask	= MAX77651_REGULATOR_V_SBB1_RANGE_MASK,
		.vsel_range_reg		= MAX77650_REG_CNFG_SBB1_A,
		.vsel_mask		= MAX77651_REGULATOR_V_SBB1_MASK,
		.vsel_reg		= MAX77650_REG_CNFG_SBB1_A,
		.active_disअक्षरge_off	= MAX77650_REGULATOR_AD_DISABLED,
		.active_disअक्षरge_on	= MAX77650_REGULATOR_AD_ENABLED,
		.active_disअक्षरge_mask	= MAX77650_REGULATOR_AD_MASK,
		.active_disअक्षरge_reg	= MAX77650_REG_CNFG_SBB1_B,
		.enable_समय		= 100,
		.type			= REGULATOR_VOLTAGE,
		.owner			= THIS_MODULE,
		.csel_reg		= MAX77650_REG_CNFG_SBB1_A,
		.csel_mask		= MAX77650_REGULATOR_CURR_LIM_MASK,
		.curr_table		= max77650_current_limit_table,
		.n_current_limits = ARRAY_SIZE(max77650_current_limit_table),
	पूर्ण,
	.regA		= MAX77650_REG_CNFG_SBB1_A,
	.regB		= MAX77650_REG_CNFG_SBB1_B,
पूर्ण;

अटल काष्ठा max77650_regulator_desc max77650_SBB2_desc = अणु
	.desc = अणु
		.name			= "sbb2",
		.of_match		= of_match_ptr("sbb2"),
		.regulators_node	= of_match_ptr("regulators"),
		.supply_name		= "in-sbb0",
		.id			= MAX77650_REGULATOR_ID_SBB2,
		.ops			= &max77650_regulator_SBB_ops,
		.min_uV			= 800000,
		.uV_step		= 50000,
		.n_voltages		= 64,
		.vsel_step		= 1,
		.vsel_mask		= MAX77650_REGULATOR_V_SBB_MASK,
		.vsel_reg		= MAX77650_REG_CNFG_SBB2_A,
		.active_disअक्षरge_off	= MAX77650_REGULATOR_AD_DISABLED,
		.active_disअक्षरge_on	= MAX77650_REGULATOR_AD_ENABLED,
		.active_disअक्षरge_mask	= MAX77650_REGULATOR_AD_MASK,
		.active_disअक्षरge_reg	= MAX77650_REG_CNFG_SBB2_B,
		.enable_समय		= 100,
		.type			= REGULATOR_VOLTAGE,
		.owner			= THIS_MODULE,
		.csel_reg		= MAX77650_REG_CNFG_SBB2_A,
		.csel_mask		= MAX77650_REGULATOR_CURR_LIM_MASK,
		.curr_table		= max77650_current_limit_table,
		.n_current_limits = ARRAY_SIZE(max77650_current_limit_table),
	पूर्ण,
	.regA		= MAX77650_REG_CNFG_SBB2_A,
	.regB		= MAX77650_REG_CNFG_SBB2_B,
पूर्ण;

अटल काष्ठा max77650_regulator_desc max77651_SBB2_desc = अणु
	.desc = अणु
		.name			= "sbb2",
		.of_match		= of_match_ptr("sbb2"),
		.regulators_node	= of_match_ptr("regulators"),
		.supply_name		= "in-sbb0",
		.id			= MAX77650_REGULATOR_ID_SBB2,
		.ops			= &max77650_regulator_SBB_ops,
		.min_uV			= 2400000,
		.uV_step		= 50000,
		.n_voltages		= 64,
		.vsel_step		= 1,
		.vsel_mask		= MAX77650_REGULATOR_V_SBB_MASK,
		.vsel_reg		= MAX77650_REG_CNFG_SBB2_A,
		.active_disअक्षरge_off	= MAX77650_REGULATOR_AD_DISABLED,
		.active_disअक्षरge_on	= MAX77650_REGULATOR_AD_ENABLED,
		.active_disअक्षरge_mask	= MAX77650_REGULATOR_AD_MASK,
		.active_disअक्षरge_reg	= MAX77650_REG_CNFG_SBB2_B,
		.enable_समय		= 100,
		.type			= REGULATOR_VOLTAGE,
		.owner			= THIS_MODULE,
		.csel_reg		= MAX77650_REG_CNFG_SBB2_A,
		.csel_mask		= MAX77650_REGULATOR_CURR_LIM_MASK,
		.curr_table		= max77650_current_limit_table,
		.n_current_limits = ARRAY_SIZE(max77650_current_limit_table),
	पूर्ण,
	.regA		= MAX77650_REG_CNFG_SBB2_A,
	.regB		= MAX77650_REG_CNFG_SBB2_B,
पूर्ण;

अटल पूर्णांक max77650_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77650_regulator_desc **rdescs;
	काष्ठा max77650_regulator_desc *rdesc;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा device *dev, *parent;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *map;
	अचिन्हित पूर्णांक val;
	पूर्णांक i, rv;

	dev = &pdev->dev;
	parent = dev->parent;

	अगर (!dev->of_node)
		dev->of_node = parent->of_node;

	rdescs = devm_kसुस्मृति(dev, MAX77650_REGULATOR_NUM_REGULATORS,
			      माप(*rdescs), GFP_KERNEL);
	अगर (!rdescs)
		वापस -ENOMEM;

	map = dev_get_regmap(parent, शून्य);
	अगर (!map)
		वापस -ENODEV;

	rv = regmap_पढ़ो(map, MAX77650_REG_CID, &val);
	अगर (rv)
		वापस rv;

	rdescs[MAX77650_REGULATOR_ID_LDO] = &max77650_LDO_desc;
	rdescs[MAX77650_REGULATOR_ID_SBB0] = &max77650_SBB0_desc;

	चयन (MAX77650_CID_BITS(val)) अणु
	हाल MAX77650_CID_77650A:
	हाल MAX77650_CID_77650C:
		rdescs[MAX77650_REGULATOR_ID_SBB1] = &max77650_SBB1_desc;
		rdescs[MAX77650_REGULATOR_ID_SBB2] = &max77650_SBB2_desc;
		अवरोध;
	हाल MAX77650_CID_77651A:
	हाल MAX77650_CID_77651B:
		rdescs[MAX77650_REGULATOR_ID_SBB1] = &max77651_SBB1_desc;
		rdescs[MAX77650_REGULATOR_ID_SBB2] = &max77651_SBB2_desc;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	config.dev = parent;

	क्रम (i = 0; i < MAX77650_REGULATOR_NUM_REGULATORS; i++) अणु
		rdesc = rdescs[i];
		config.driver_data = rdesc;

		rdev = devm_regulator_रेजिस्टर(dev, &rdesc->desc, &config);
		अगर (IS_ERR(rdev))
			वापस PTR_ERR(rdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max77650_regulator_of_match[] = अणु
	अणु .compatible = "maxim,max77650-regulator" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max77650_regulator_of_match);

अटल काष्ठा platक्रमm_driver max77650_regulator_driver = अणु
	.driver = अणु
		.name = "max77650-regulator",
		.of_match_table = max77650_regulator_of_match,
	पूर्ण,
	.probe = max77650_regulator_probe,
पूर्ण;
module_platक्रमm_driver(max77650_regulator_driver);

MODULE_DESCRIPTION("MAXIM 77650/77651 regulator driver");
MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:max77650-regulator");
