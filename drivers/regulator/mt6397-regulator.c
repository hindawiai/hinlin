<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2014 MediaTek Inc.
// Author: Flora Fu <flora.fu@mediatek.com>

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/mfd/mt6397/रेजिस्टरs.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/mt6397-regulator.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <dt-bindings/regulator/mediatek,mt6397-regulator.h>

/*
 * MT6397 regulators' inक्रमmation
 *
 * @desc: standard fields of regulator description.
 * @qi: Mask क्रम query enable संकेत status of regulators
 * @vselon_reg: Register sections क्रम hardware control mode of bucks
 * @vselctrl_reg: Register क्रम controlling the buck control mode.
 * @vselctrl_mask: Mask क्रम query buck's voltage control mode.
 */
काष्ठा mt6397_regulator_info अणु
	काष्ठा regulator_desc desc;
	u32 qi;
	u32 vselon_reg;
	u32 vselctrl_reg;
	u32 vselctrl_mask;
	u32 modeset_reg;
	u32 modeset_mask;
	u32 modeset_shअगरt;
पूर्ण;

#घोषणा MT6397_BUCK(match, vreg, min, max, step, volt_ranges, enreg,	\
		vosel, vosel_mask, voselon, vosel_ctrl, _modeset_reg,	\
		_modeset_shअगरt)					\
[MT6397_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6397_volt_range_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6397_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = (max - min)/step + 1,			\
		.linear_ranges = volt_ranges,				\
		.n_linear_ranges = ARRAY_SIZE(volt_ranges),		\
		.vsel_reg = vosel,					\
		.vsel_mask = vosel_mask,				\
		.enable_reg = enreg,					\
		.enable_mask = BIT(0),					\
		.of_map_mode = mt6397_map_mode,				\
	पूर्ण,								\
	.qi = BIT(13),							\
	.vselon_reg = voselon,						\
	.vselctrl_reg = vosel_ctrl,					\
	.vselctrl_mask = BIT(1),					\
	.modeset_reg = _modeset_reg,					\
	.modeset_mask = BIT(_modeset_shअगरt),				\
	.modeset_shअगरt = _modeset_shअगरt					\
पूर्ण

#घोषणा MT6397_LDO(match, vreg, lकरो_volt_table, enreg, enbit, vosel,	\
		vosel_mask)						\
[MT6397_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6397_volt_table_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6397_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = ARRAY_SIZE(lकरो_volt_table),		\
		.volt_table = lकरो_volt_table,				\
		.vsel_reg = vosel,					\
		.vsel_mask = vosel_mask,				\
		.enable_reg = enreg,					\
		.enable_mask = BIT(enbit),				\
	पूर्ण,								\
	.qi = BIT(15),							\
पूर्ण

#घोषणा MT6397_REG_FIXED(match, vreg, enreg, enbit, volt)		\
[MT6397_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6397_volt_fixed_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6397_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = 1,					\
		.enable_reg = enreg,					\
		.enable_mask = BIT(enbit),				\
		.min_uV = volt,						\
	पूर्ण,								\
	.qi = BIT(15),							\
पूर्ण

अटल स्थिर काष्ठा linear_range buck_volt_range1[] = अणु
	REGULATOR_LINEAR_RANGE(700000, 0, 0x7f, 6250),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range2[] = अणु
	REGULATOR_LINEAR_RANGE(800000, 0, 0x7f, 6250),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range3[] = अणु
	REGULATOR_LINEAR_RANGE(1500000, 0, 0x1f, 20000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table1[] = अणु
	1500000, 1800000, 2500000, 2800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table2[] = अणु
	1800000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table3[] = अणु
	3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table4[] = अणु
	1220000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table5[] = अणु
	1200000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table5_v2[] = अणु
	1200000, 1000000, 1500000, 1800000, 2500000, 2800000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table6[] = अणु
	1200000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 2000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table7[] = अणु
	1300000, 1500000, 1800000, 2000000, 2500000, 2800000, 3000000, 3300000,
पूर्ण;

अटल अचिन्हित पूर्णांक mt6397_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल MT6397_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_NORMAL;
	हाल MT6397_BUCK_MODE_FORCE_PWM:
		वापस REGULATOR_MODE_FAST;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक mt6397_regulator_set_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	काष्ठा mt6397_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret, val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = MT6397_BUCK_MODE_FORCE_PWM;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = MT6397_BUCK_MODE_AUTO;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err_mode;
	पूर्ण

	dev_dbg(&rdev->dev, "mt6397 buck set_mode %#x, %#x, %#x, %#x\n",
		info->modeset_reg, info->modeset_mask,
		info->modeset_shअगरt, val);

	val <<= info->modeset_shअगरt;
	ret = regmap_update_bits(rdev->regmap, info->modeset_reg,
				 info->modeset_mask, val);
err_mode:
	अगर (ret != 0) अणु
		dev_err(&rdev->dev,
			"Failed to set mt6397 buck mode: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक mt6397_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mt6397_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret, regval;

	ret = regmap_पढ़ो(rdev->regmap, info->modeset_reg, &regval);
	अगर (ret != 0) अणु
		dev_err(&rdev->dev,
			"Failed to get mt6397 buck mode: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन ((regval & info->modeset_mask) >> info->modeset_shअगरt) अणु
	हाल MT6397_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_NORMAL;
	हाल MT6397_BUCK_MODE_FORCE_PWM:
		वापस REGULATOR_MODE_FAST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mt6397_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	u32 regval;
	काष्ठा mt6397_regulator_info *info = rdev_get_drvdata(rdev);

	ret = regmap_पढ़ो(rdev->regmap, info->desc.enable_reg, &regval);
	अगर (ret != 0) अणु
		dev_err(&rdev->dev, "Failed to get enable reg: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस (regval & info->qi) ? REGULATOR_STATUS_ON : REGULATOR_STATUS_OFF;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mt6397_volt_range_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6397_get_status,
	.set_mode = mt6397_regulator_set_mode,
	.get_mode = mt6397_regulator_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6397_volt_table_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6397_get_status,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6397_volt_fixed_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6397_get_status,
पूर्ण;

/* The array is indexed by id(MT6397_ID_XXX) */
अटल काष्ठा mt6397_regulator_info mt6397_regulators[] = अणु
	MT6397_BUCK("buck_vpca15", VPCA15, 700000, 1493750, 6250,
		buck_volt_range1, MT6397_VCA15_CON7, MT6397_VCA15_CON9, 0x7f,
		MT6397_VCA15_CON10, MT6397_VCA15_CON5, MT6397_VCA15_CON2, 11),
	MT6397_BUCK("buck_vpca7", VPCA7, 700000, 1493750, 6250,
		buck_volt_range1, MT6397_VPCA7_CON7, MT6397_VPCA7_CON9, 0x7f,
		MT6397_VPCA7_CON10, MT6397_VPCA7_CON5, MT6397_VPCA7_CON2, 8),
	MT6397_BUCK("buck_vsramca15", VSRAMCA15, 700000, 1493750, 6250,
		buck_volt_range1, MT6397_VSRMCA15_CON7, MT6397_VSRMCA15_CON9,
		0x7f, MT6397_VSRMCA15_CON10, MT6397_VSRMCA15_CON5,
		MT6397_VSRMCA15_CON2, 8),
	MT6397_BUCK("buck_vsramca7", VSRAMCA7, 700000, 1493750, 6250,
		buck_volt_range1, MT6397_VSRMCA7_CON7, MT6397_VSRMCA7_CON9,
		0x7f, MT6397_VSRMCA7_CON10, MT6397_VSRMCA7_CON5,
		MT6397_VSRMCA7_CON2, 8),
	MT6397_BUCK("buck_vcore", VCORE, 700000, 1493750, 6250,
		buck_volt_range1, MT6397_VCORE_CON7, MT6397_VCORE_CON9, 0x7f,
		MT6397_VCORE_CON10, MT6397_VCORE_CON5, MT6397_VCORE_CON2, 8),
	MT6397_BUCK("buck_vgpu", VGPU, 700000, 1493750, 6250, buck_volt_range1,
		MT6397_VGPU_CON7, MT6397_VGPU_CON9, 0x7f,
		MT6397_VGPU_CON10, MT6397_VGPU_CON5, MT6397_VGPU_CON2, 8),
	MT6397_BUCK("buck_vdrm", VDRM, 800000, 1593750, 6250, buck_volt_range2,
		MT6397_VDRM_CON7, MT6397_VDRM_CON9, 0x7f,
		MT6397_VDRM_CON10, MT6397_VDRM_CON5, MT6397_VDRM_CON2, 8),
	MT6397_BUCK("buck_vio18", VIO18, 1500000, 2120000, 20000,
		buck_volt_range3, MT6397_VIO18_CON7, MT6397_VIO18_CON9, 0x1f,
		MT6397_VIO18_CON10, MT6397_VIO18_CON5, MT6397_VIO18_CON2, 8),
	MT6397_REG_FIXED("ldo_vtcxo", VTCXO, MT6397_ANALDO_CON0, 10, 2800000),
	MT6397_REG_FIXED("ldo_va28", VA28, MT6397_ANALDO_CON1, 14, 2800000),
	MT6397_LDO("ldo_vcama", VCAMA, lकरो_volt_table1,
		MT6397_ANALDO_CON2, 15, MT6397_ANALDO_CON6, 0xC0),
	MT6397_REG_FIXED("ldo_vio28", VIO28, MT6397_DIGLDO_CON0, 14, 2800000),
	MT6397_REG_FIXED("ldo_vusb", VUSB, MT6397_DIGLDO_CON1, 14, 3300000),
	MT6397_LDO("ldo_vmc", VMC, lकरो_volt_table2,
		MT6397_DIGLDO_CON2, 12, MT6397_DIGLDO_CON29, 0x10),
	MT6397_LDO("ldo_vmch", VMCH, lकरो_volt_table3,
		MT6397_DIGLDO_CON3, 14, MT6397_DIGLDO_CON17, 0x80),
	MT6397_LDO("ldo_vemc3v3", VEMC3V3, lकरो_volt_table3,
		MT6397_DIGLDO_CON4, 14, MT6397_DIGLDO_CON18, 0x10),
	MT6397_LDO("ldo_vgp1", VGP1, lकरो_volt_table4,
		MT6397_DIGLDO_CON5, 15, MT6397_DIGLDO_CON19, 0xE0),
	MT6397_LDO("ldo_vgp2", VGP2, lकरो_volt_table5,
		MT6397_DIGLDO_CON6, 15, MT6397_DIGLDO_CON20, 0xE0),
	MT6397_LDO("ldo_vgp3", VGP3, lकरो_volt_table5,
		MT6397_DIGLDO_CON7, 15, MT6397_DIGLDO_CON21, 0xE0),
	MT6397_LDO("ldo_vgp4", VGP4, lकरो_volt_table5,
		MT6397_DIGLDO_CON8, 15, MT6397_DIGLDO_CON22, 0xE0),
	MT6397_LDO("ldo_vgp5", VGP5, lकरो_volt_table6,
		MT6397_DIGLDO_CON9, 15, MT6397_DIGLDO_CON23, 0xE0),
	MT6397_LDO("ldo_vgp6", VGP6, lकरो_volt_table5,
		MT6397_DIGLDO_CON10, 15, MT6397_DIGLDO_CON33, 0xE0),
	MT6397_LDO("ldo_vibr", VIBR, lकरो_volt_table7,
		MT6397_DIGLDO_CON24, 15, MT6397_DIGLDO_CON25, 0xE00),
पूर्ण;

अटल पूर्णांक mt6397_set_buck_vosel_reg(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < MT6397_MAX_REGULATOR; i++) अणु
		अगर (mt6397_regulators[i].vselctrl_reg) अणु
			अगर (regmap_पढ़ो(mt6397->regmap,
				mt6397_regulators[i].vselctrl_reg,
				&regval) < 0) अणु
				dev_err(&pdev->dev,
					"Failed to read buck ctrl\n");
				वापस -EIO;
			पूर्ण

			अगर (regval & mt6397_regulators[i].vselctrl_mask) अणु
				mt6397_regulators[i].desc.vsel_reg =
				mt6397_regulators[i].vselon_reg;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt6397_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;
	u32 reg_value, version;

	/* Query buck controller to select activated voltage रेजिस्टर part */
	अगर (mt6397_set_buck_vosel_reg(pdev))
		वापस -EIO;

	/* Read PMIC chip revision to update स्थिरraपूर्णांकs and voltage table */
	अगर (regmap_पढ़ो(mt6397->regmap, MT6397_CID, &reg_value) < 0) अणु
		dev_err(&pdev->dev, "Failed to read Chip ID\n");
		वापस -EIO;
	पूर्ण
	dev_info(&pdev->dev, "Chip ID = 0x%x\n", reg_value);

	version = (reg_value & 0xFF);
	चयन (version) अणु
	हाल MT6397_REGULATOR_ID91:
		mt6397_regulators[MT6397_ID_VGP2].desc.volt_table =
		lकरो_volt_table5_v2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < MT6397_MAX_REGULATOR; i++) अणु
		config.dev = &pdev->dev;
		config.driver_data = &mt6397_regulators[i];
		config.regmap = mt6397->regmap;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
				&mt6397_regulators[i].desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register %s\n",
				mt6397_regulators[i].desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mt6397_platक्रमm_ids[] = अणु
	अणु"mt6397-regulator", 0पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mt6397_platक्रमm_ids);

अटल स्थिर काष्ठा of_device_id mt6397_of_match[] = अणु
	अणु .compatible = "mediatek,mt6397-regulator", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6397_of_match);

अटल काष्ठा platक्रमm_driver mt6397_regulator_driver = अणु
	.driver = अणु
		.name = "mt6397-regulator",
		.of_match_table = of_match_ptr(mt6397_of_match),
	पूर्ण,
	.probe = mt6397_regulator_probe,
	.id_table = mt6397_platक्रमm_ids,
पूर्ण;

module_platक्रमm_driver(mt6397_regulator_driver);

MODULE_AUTHOR("Flora Fu <flora.fu@mediatek.com>");
MODULE_DESCRIPTION("Regulator Driver for MediaTek MT6397 PMIC");
MODULE_LICENSE("GPL");
