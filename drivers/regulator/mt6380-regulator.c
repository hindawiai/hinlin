<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2017 MediaTek Inc.
// Author: Chenglin Xu <chenglin.xu@mediatek.com>

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/mt6380-regulator.h>
#समावेश <linux/regulator/of_regulator.h>

/* PMIC Registers */
#घोषणा MT6380_ALDO_CON_0                         0x0000
#घोषणा MT6380_BTLDO_CON_0                        0x0004
#घोषणा MT6380_COMP_CON_0                         0x0008
#घोषणा MT6380_CPUBUCK_CON_0                      0x000C
#घोषणा MT6380_CPUBUCK_CON_1                      0x0010
#घोषणा MT6380_CPUBUCK_CON_2                      0x0014
#घोषणा MT6380_DDRLDO_CON_0                       0x0018
#घोषणा MT6380_MLDO_CON_0                         0x001C
#घोषणा MT6380_PALDO_CON_0                        0x0020
#घोषणा MT6380_PHYLDO_CON_0                       0x0024
#घोषणा MT6380_SIDO_CON_0                         0x0028
#घोषणा MT6380_SIDO_CON_1                         0x002C
#घोषणा MT6380_SIDO_CON_2                         0x0030
#घोषणा MT6380_SLDO_CON_0                         0x0034
#घोषणा MT6380_TLDO_CON_0                         0x0038
#घोषणा MT6380_STARTUP_CON_0                      0x003C
#घोषणा MT6380_STARTUP_CON_1                      0x0040
#घोषणा MT6380_SMPS_TOP_CON_0                     0x0044
#घोषणा MT6380_SMPS_TOP_CON_1                     0x0048
#घोषणा MT6380_ANA_CTRL_0                         0x0050
#घोषणा MT6380_ANA_CTRL_1                         0x0054
#घोषणा MT6380_ANA_CTRL_2                         0x0058
#घोषणा MT6380_ANA_CTRL_3                         0x005C
#घोषणा MT6380_ANA_CTRL_4                         0x0060
#घोषणा MT6380_SPK_CON9                           0x0064
#घोषणा MT6380_SPK_CON11                          0x0068
#घोषणा MT6380_SPK_CON12                          0x006A
#घोषणा MT6380_CLK_CTRL                           0x0070
#घोषणा MT6380_PINMUX_CTRL                        0x0074
#घोषणा MT6380_IO_CTRL                            0x0078
#घोषणा MT6380_SLP_MODE_CTRL_0                    0x007C
#घोषणा MT6380_SLP_MODE_CTRL_1                    0x0080
#घोषणा MT6380_SLP_MODE_CTRL_2                    0x0084
#घोषणा MT6380_SLP_MODE_CTRL_3                    0x0088
#घोषणा MT6380_SLP_MODE_CTRL_4                    0x008C
#घोषणा MT6380_SLP_MODE_CTRL_5                    0x0090
#घोषणा MT6380_SLP_MODE_CTRL_6                    0x0094
#घोषणा MT6380_SLP_MODE_CTRL_7                    0x0098
#घोषणा MT6380_SLP_MODE_CTRL_8                    0x009C
#घोषणा MT6380_FCAL_CTRL_0                        0x00A0
#घोषणा MT6380_FCAL_CTRL_1                        0x00A4
#घोषणा MT6380_LDO_CTRL_0                         0x00A8
#घोषणा MT6380_LDO_CTRL_1                         0x00AC
#घोषणा MT6380_LDO_CTRL_2                         0x00B0
#घोषणा MT6380_LDO_CTRL_3                         0x00B4
#घोषणा MT6380_LDO_CTRL_4                         0x00B8
#घोषणा MT6380_DEBUG_CTRL_0                       0x00BC
#घोषणा MT6380_EFU_CTRL_0                         0x0200
#घोषणा MT6380_EFU_CTRL_1                         0x0201
#घोषणा MT6380_EFU_CTRL_2                         0x0202
#घोषणा MT6380_EFU_CTRL_3                         0x0203
#घोषणा MT6380_EFU_CTRL_4                         0x0204
#घोषणा MT6380_EFU_CTRL_5                         0x0205
#घोषणा MT6380_EFU_CTRL_6                         0x0206
#घोषणा MT6380_EFU_CTRL_7                         0x0207
#घोषणा MT6380_EFU_CTRL_8                         0x0208

#घोषणा MT6380_REGULATOR_MODE_AUTO	0
#घोषणा MT6380_REGULATOR_MODE_FORCE_PWM	1

/*
 * mt6380 regulators' inक्रमmation
 *
 * @desc: standard fields of regulator description
 * @vselon_reg: Register sections क्रम hardware control mode of bucks
 * @modeset_reg: Register क्रम controlling the buck/LDO control mode
 * @modeset_mask: Mask क्रम controlling the buck/LDO control mode
 */
काष्ठा mt6380_regulator_info अणु
	काष्ठा regulator_desc desc;
	u32 vselon_reg;
	u32 modeset_reg;
	u32 modeset_mask;
पूर्ण;

#घोषणा MT6380_BUCK(match, vreg, min, max, step, volt_ranges, enreg,	\
		    vosel, vosel_mask, enbit, voselon, _modeset_reg,	\
		    _modeset_mask)					\
[MT6380_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6380_volt_range_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6380_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = ((max) - (min)) / (step) + 1,		\
		.linear_ranges = volt_ranges,				\
		.n_linear_ranges = ARRAY_SIZE(volt_ranges),		\
		.vsel_reg = vosel,					\
		.vsel_mask = vosel_mask,				\
		.enable_reg = enreg,					\
		.enable_mask = BIT(enbit),				\
	पूर्ण,								\
	.vselon_reg = voselon,						\
	.modeset_reg = _modeset_reg,					\
	.modeset_mask = _modeset_mask,					\
पूर्ण

#घोषणा MT6380_LDO(match, vreg, lकरो_volt_table, enreg, enbit, vosel,	\
		   vosel_mask, _modeset_reg, _modeset_mask)		\
[MT6380_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6380_volt_table_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6380_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = ARRAY_SIZE(lकरो_volt_table),		\
		.volt_table = lकरो_volt_table,				\
		.vsel_reg = vosel,					\
		.vsel_mask = vosel_mask,				\
		.enable_reg = enreg,					\
		.enable_mask = BIT(enbit),				\
	पूर्ण,								\
	.modeset_reg = _modeset_reg,					\
	.modeset_mask = _modeset_mask,					\
पूर्ण

#घोषणा MT6380_REG_FIXED(match, vreg, enreg, enbit, volt,		\
			 _modeset_reg, _modeset_mask)			\
[MT6380_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6380_volt_fixed_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6380_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = 1,					\
		.enable_reg = enreg,					\
		.enable_mask = BIT(enbit),				\
		.min_uV = volt,						\
	पूर्ण,								\
	.modeset_reg = _modeset_reg,					\
	.modeset_mask = _modeset_mask,					\
पूर्ण

अटल स्थिर काष्ठा linear_range buck_volt_range1[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 0xfe, 6250),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range2[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 0xfe, 6250),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range3[] = अणु
	REGULATOR_LINEAR_RANGE(1200000, 0, 0x3c, 25000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table1[] = अणु
	1400000, 1350000, 1300000, 1250000, 1200000, 1150000, 1100000, 1050000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table2[] = अणु
	2200000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table3[] = अणु
	1240000, 1390000, 1540000, 1840000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table4[] = अणु
	2200000, 3300000,
पूर्ण;

अटल पूर्णांक mt6380_regulator_set_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret, val = 0;
	काष्ठा mt6380_regulator_info *info = rdev_get_drvdata(rdev);

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = MT6380_REGULATOR_MODE_AUTO;
		अवरोध;
	हाल REGULATOR_MODE_FAST:
		val = MT6380_REGULATOR_MODE_FORCE_PWM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val <<= ffs(info->modeset_mask) - 1;

	ret = regmap_update_bits(rdev->regmap, info->modeset_reg,
				 info->modeset_mask, val);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक mt6380_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;
	काष्ठा mt6380_regulator_info *info = rdev_get_drvdata(rdev);

	ret = regmap_पढ़ो(rdev->regmap, info->modeset_reg, &val);
	अगर (ret < 0)
		वापस ret;

	val &= info->modeset_mask;
	val >>= ffs(info->modeset_mask) - 1;

	चयन (val) अणु
	हाल MT6380_REGULATOR_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		अवरोध;
	हाल MT6380_REGULATOR_MODE_FORCE_PWM:
		mode = REGULATOR_MODE_FAST;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mt6380_volt_range_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = mt6380_regulator_set_mode,
	.get_mode = mt6380_regulator_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6380_volt_table_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = mt6380_regulator_set_mode,
	.get_mode = mt6380_regulator_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6380_volt_fixed_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.set_mode = mt6380_regulator_set_mode,
	.get_mode = mt6380_regulator_get_mode,
पूर्ण;

/* The array is indexed by id(MT6380_ID_XXX) */
अटल काष्ठा mt6380_regulator_info mt6380_regulators[] = अणु
	MT6380_BUCK("buck-vcore1", VCPU, 600000, 1393750, 6250,
		    buck_volt_range1, MT6380_ANA_CTRL_3, MT6380_ANA_CTRL_1,
		    0xfe, 3, MT6380_ANA_CTRL_1,
		    MT6380_CPUBUCK_CON_0, 0x8000000),
	MT6380_BUCK("buck-vcore", VCORE, 600000, 1393750, 6250,
		    buck_volt_range2, MT6380_ANA_CTRL_3, MT6380_ANA_CTRL_2,
		    0xfe, 2, MT6380_ANA_CTRL_2, MT6380_SIDO_CON_0, 0x1000000),
	MT6380_BUCK("buck-vrf", VRF, 1200000, 1575000, 25000,
		    buck_volt_range3, MT6380_ANA_CTRL_3, MT6380_SIDO_CON_0,
		    0x78, 1, MT6380_SIDO_CON_0, MT6380_SIDO_CON_0, 0x8000),
	MT6380_LDO("ldo-vm", VMLDO, lकरो_volt_table1, MT6380_LDO_CTRL_0,
		   1, MT6380_MLDO_CON_0, 0xE000, MT6380_ANA_CTRL_1, 0x4000000),
	MT6380_LDO("ldo-va", VALDO, lकरो_volt_table2, MT6380_LDO_CTRL_0,
		   2, MT6380_ALDO_CON_0, 0x400, MT6380_ALDO_CON_0, 0x20),
	MT6380_REG_FIXED("ldo-vphy", VPHYLDO, MT6380_LDO_CTRL_0, 7, 1800000,
			 MT6380_PHYLDO_CON_0, 0x80),
	MT6380_LDO("ldo-vddr", VDDRLDO, lकरो_volt_table3, MT6380_LDO_CTRL_0,
		   8, MT6380_DDRLDO_CON_0, 0x3000, MT6380_DDRLDO_CON_0, 0x80),
	MT6380_LDO("ldo-vt", VTLDO, lकरो_volt_table4, MT6380_LDO_CTRL_0, 3,
		   MT6380_TLDO_CON_0, 0x400, MT6380_TLDO_CON_0, 0x20),
पूर्ण;

अटल पूर्णांक mt6380_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap *regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	क्रम (i = 0; i < MT6380_MAX_REGULATOR; i++) अणु
		config.dev = &pdev->dev;
		config.driver_data = &mt6380_regulators[i];
		config.regmap = regmap;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
					       &mt6380_regulators[i].desc,
				&config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register %s\n",
				mt6380_regulators[i].desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mt6380_platक्रमm_ids[] = अणु
	अणु"mt6380-regulator", 0पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mt6380_platक्रमm_ids);

अटल स्थिर काष्ठा of_device_id mt6380_of_match[] = अणु
	अणु .compatible = "mediatek,mt6380-regulator", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6380_of_match);

अटल काष्ठा platक्रमm_driver mt6380_regulator_driver = अणु
	.driver = अणु
		.name = "mt6380-regulator",
		.of_match_table = of_match_ptr(mt6380_of_match),
	पूर्ण,
	.probe = mt6380_regulator_probe,
	.id_table = mt6380_platक्रमm_ids,
पूर्ण;

module_platक्रमm_driver(mt6380_regulator_driver);

MODULE_AUTHOR("Chenglin Xu <chenglin.xu@mediatek.com>");
MODULE_DESCRIPTION("Regulator Driver for MediaTek MT6380 PMIC");
MODULE_LICENSE("GPL v2");
