<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2015 MediaTek Inc.
// Author: Henry Chen <henryc.chen@mediatek.com>

#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regulator/mt6311.h>
#समावेश <linux/slab.h>
#समावेश "mt6311-regulator.h"

अटल स्थिर काष्ठा regmap_config mt6311_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MT6311_FQMTR_CON4,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

/* Default limits measured in millivolts and milliamps */
#घोषणा MT6311_MIN_UV		600000
#घोषणा MT6311_MAX_UV		1393750
#घोषणा MT6311_STEP_UV		6250

अटल स्थिर काष्ठा regulator_ops mt6311_buck_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6311_lकरो_ops = अणु
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
पूर्ण;

#घोषणा MT6311_BUCK(_id) \
अणु\
	.name = #_id,\
	.ops = &mt6311_buck_ops,\
	.of_match = of_match_ptr(#_id),\
	.regulators_node = of_match_ptr("regulators"),\
	.type = REGULATOR_VOLTAGE,\
	.id = MT6311_ID_##_id,\
	.n_voltages = (MT6311_MAX_UV - MT6311_MIN_UV) / MT6311_STEP_UV + 1,\
	.min_uV = MT6311_MIN_UV,\
	.uV_step = MT6311_STEP_UV,\
	.owner = THIS_MODULE,\
	.enable_reg = MT6311_VDVFS11_CON9,\
	.enable_mask = MT6311_PMIC_VDVFS11_EN_MASK,\
	.vsel_reg = MT6311_VDVFS11_CON12,\
	.vsel_mask = MT6311_PMIC_VDVFS11_VOSEL_MASK,\
पूर्ण

#घोषणा MT6311_LDO(_id) \
अणु\
	.name = #_id,\
	.ops = &mt6311_lकरो_ops,\
	.of_match = of_match_ptr(#_id),\
	.regulators_node = of_match_ptr("regulators"),\
	.type = REGULATOR_VOLTAGE,\
	.id = MT6311_ID_##_id,\
	.owner = THIS_MODULE,\
	.enable_reg = MT6311_LDO_CON3,\
	.enable_mask = MT6311_PMIC_RG_VBIASN_EN_MASK,\
पूर्ण

अटल स्थिर काष्ठा regulator_desc mt6311_regulators[] = अणु
	MT6311_BUCK(VDVFS),
	MT6311_LDO(VBIASN),
पूर्ण;

/*
 * I2C driver पूर्णांकerface functions
 */
अटल पूर्णांक mt6311_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा regmap *regmap;
	पूर्णांक i, ret;
	अचिन्हित पूर्णांक data;

	regmap = devm_regmap_init_i2c(i2c, &mt6311_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(regmap, MT6311_SWCID, &data);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read DEVICE_ID reg: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (data) अणु
	हाल MT6311_E1_CID_CODE:
	हाल MT6311_E2_CID_CODE:
	हाल MT6311_E3_CID_CODE:
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "Unsupported device id = 0x%x.\n", data);
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < MT6311_MAX_REGULATORS; i++) अणु
		config.dev = &i2c->dev;
		config.regmap = regmap;

		rdev = devm_regulator_रेजिस्टर(&i2c->dev,
			&mt6311_regulators[i], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&i2c->dev,
				"Failed to register MT6311 regulator\n");
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id mt6311_i2c_id[] = अणु
	अणु"mt6311", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mt6311_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mt6311_dt_ids[] = अणु
	अणु .compatible = "mediatek,mt6311-regulator",
	  .data = &mt6311_i2c_id[0] पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6311_dt_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver mt6311_regulator_driver = अणु
	.driver = अणु
		.name = "mt6311",
		.of_match_table = of_match_ptr(mt6311_dt_ids),
	पूर्ण,
	.probe_new = mt6311_i2c_probe,
	.id_table = mt6311_i2c_id,
पूर्ण;

module_i2c_driver(mt6311_regulator_driver);

MODULE_AUTHOR("Henry Chen <henryc.chen@mediatek.com>");
MODULE_DESCRIPTION("Regulator device driver for Mediatek MT6311");
MODULE_LICENSE("GPL v2");
