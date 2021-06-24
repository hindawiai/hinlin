<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2016 MediaTek Inc.
// Author: Chen Zhong <chen.zhong@mediatek.com>

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/mfd/mt6323/रेजिस्टरs.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/mt6323-regulator.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा MT6323_LDO_MODE_NORMAL	0
#घोषणा MT6323_LDO_MODE_LP	1

/*
 * MT6323 regulators' inक्रमmation
 *
 * @desc: standard fields of regulator description.
 * @qi: Mask क्रम query enable संकेत status of regulators
 * @vselon_reg: Register sections क्रम hardware control mode of bucks
 * @vselctrl_reg: Register क्रम controlling the buck control mode.
 * @vselctrl_mask: Mask क्रम query buck's voltage control mode.
 */
काष्ठा mt6323_regulator_info अणु
	काष्ठा regulator_desc desc;
	u32 qi;
	u32 vselon_reg;
	u32 vselctrl_reg;
	u32 vselctrl_mask;
	u32 modeset_reg;
	u32 modeset_mask;
पूर्ण;

#घोषणा MT6323_BUCK(match, vreg, min, max, step, volt_ranges, enreg,	\
		vosel, vosel_mask, voselon, vosel_ctrl)			\
[MT6323_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6323_volt_range_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6323_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = (max - min)/step + 1,			\
		.linear_ranges = volt_ranges,				\
		.n_linear_ranges = ARRAY_SIZE(volt_ranges),		\
		.vsel_reg = vosel,					\
		.vsel_mask = vosel_mask,				\
		.enable_reg = enreg,					\
		.enable_mask = BIT(0),					\
	पूर्ण,								\
	.qi = BIT(13),							\
	.vselon_reg = voselon,						\
	.vselctrl_reg = vosel_ctrl,					\
	.vselctrl_mask = BIT(1),					\
पूर्ण

#घोषणा MT6323_LDO(match, vreg, lकरो_volt_table, enreg, enbit, vosel,	\
		vosel_mask, _modeset_reg, _modeset_mask)		\
[MT6323_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6323_volt_table_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6323_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = ARRAY_SIZE(lकरो_volt_table),		\
		.volt_table = lकरो_volt_table,				\
		.vsel_reg = vosel,					\
		.vsel_mask = vosel_mask,				\
		.enable_reg = enreg,					\
		.enable_mask = BIT(enbit),				\
	पूर्ण,								\
	.qi = BIT(15),							\
	.modeset_reg = _modeset_reg,					\
	.modeset_mask = _modeset_mask,					\
पूर्ण

#घोषणा MT6323_REG_FIXED(match, vreg, enreg, enbit, volt,		\
		_modeset_reg, _modeset_mask)				\
[MT6323_ID_##vreg] = अणु							\
	.desc = अणु							\
		.name = #vreg,						\
		.of_match = of_match_ptr(match),			\
		.ops = &mt6323_volt_fixed_ops,				\
		.type = REGULATOR_VOLTAGE,				\
		.id = MT6323_ID_##vreg,					\
		.owner = THIS_MODULE,					\
		.n_voltages = 1,					\
		.enable_reg = enreg,					\
		.enable_mask = BIT(enbit),				\
		.min_uV = volt,						\
	पूर्ण,								\
	.qi = BIT(15),							\
	.modeset_reg = _modeset_reg,					\
	.modeset_mask = _modeset_mask,					\
पूर्ण

अटल स्थिर काष्ठा linear_range buck_volt_range1[] = अणु
	REGULATOR_LINEAR_RANGE(700000, 0, 0x7f, 6250),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range2[] = अणु
	REGULATOR_LINEAR_RANGE(1400000, 0, 0x7f, 12500),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range3[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0, 0x3f, 50000),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table1[] = अणु
	3300000, 3400000, 3500000, 3600000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table2[] = अणु
	1500000, 1800000, 2500000, 2800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table3[] = अणु
	1800000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table4[] = अणु
	3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table5[] = अणु
	1200000, 1300000, 1500000, 1800000, 2000000, 2800000, 3000000, 3300000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table6[] = अणु
	1200000, 1300000, 1500000, 1800000, 2500000, 2800000, 3000000, 2000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table7[] = अणु
	1200000, 1300000, 1500000, 1800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table8[] = अणु
	1800000, 3000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table9[] = अणु
	1200000, 1350000, 1500000, 1800000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक lकरो_volt_table10[] = अणु
	1200000, 1300000, 1500000, 1800000,
पूर्ण;

अटल पूर्णांक mt6323_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	u32 regval;
	काष्ठा mt6323_regulator_info *info = rdev_get_drvdata(rdev);

	ret = regmap_पढ़ो(rdev->regmap, info->desc.enable_reg, &regval);
	अगर (ret != 0) अणु
		dev_err(&rdev->dev, "Failed to get enable reg: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस (regval & info->qi) ? REGULATOR_STATUS_ON : REGULATOR_STATUS_OFF;
पूर्ण

अटल पूर्णांक mt6323_lकरो_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक ret, val = 0;
	काष्ठा mt6323_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (!info->modeset_mask) अणु
		dev_err(&rdev->dev, "regulator %s doesn't support set_mode\n",
			info->desc.name);
		वापस -EINVAL;
	पूर्ण

	चयन (mode) अणु
	हाल REGULATOR_MODE_STANDBY:
		val = MT6323_LDO_MODE_LP;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = MT6323_LDO_MODE_NORMAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val <<= ffs(info->modeset_mask) - 1;

	ret = regmap_update_bits(rdev->regmap, info->modeset_reg,
				  info->modeset_mask, val);

	वापस ret;
पूर्ण

अटल अचिन्हित पूर्णांक mt6323_lकरो_get_mode(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;
	काष्ठा mt6323_regulator_info *info = rdev_get_drvdata(rdev);

	अगर (!info->modeset_mask) अणु
		dev_err(&rdev->dev, "regulator %s doesn't support get_mode\n",
			info->desc.name);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(rdev->regmap, info->modeset_reg, &val);
	अगर (ret < 0)
		वापस ret;

	val &= info->modeset_mask;
	val >>= ffs(info->modeset_mask) - 1;

	अगर (val & 0x1)
		mode = REGULATOR_MODE_STANDBY;
	अन्यथा
		mode = REGULATOR_MODE_NORMAL;

	वापस mode;
पूर्ण

अटल स्थिर काष्ठा regulator_ops mt6323_volt_range_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6323_get_status,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6323_volt_table_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6323_get_status,
	.set_mode = mt6323_lकरो_set_mode,
	.get_mode = mt6323_lकरो_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6323_volt_fixed_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6323_get_status,
	.set_mode = mt6323_lकरो_set_mode,
	.get_mode = mt6323_lकरो_get_mode,
पूर्ण;

/* The array is indexed by id(MT6323_ID_XXX) */
अटल काष्ठा mt6323_regulator_info mt6323_regulators[] = अणु
	MT6323_BUCK("buck_vproc", VPROC, 700000, 1493750, 6250,
		buck_volt_range1, MT6323_VPROC_CON7, MT6323_VPROC_CON9, 0x7f,
		MT6323_VPROC_CON10, MT6323_VPROC_CON5),
	MT6323_BUCK("buck_vsys", VSYS, 1400000, 2987500, 12500,
		buck_volt_range2, MT6323_VSYS_CON7, MT6323_VSYS_CON9, 0x7f,
		MT6323_VSYS_CON10, MT6323_VSYS_CON5),
	MT6323_BUCK("buck_vpa", VPA, 500000, 3650000, 50000,
		buck_volt_range3, MT6323_VPA_CON7, MT6323_VPA_CON9,
		0x3f, MT6323_VPA_CON10, MT6323_VPA_CON5),
	MT6323_REG_FIXED("ldo_vtcxo", VTCXO, MT6323_ANALDO_CON1, 10, 2800000,
		MT6323_ANALDO_CON1, 0x2),
	MT6323_REG_FIXED("ldo_vcn28", VCN28, MT6323_ANALDO_CON19, 12, 2800000,
		MT6323_ANALDO_CON20, 0x2),
	MT6323_LDO("ldo_vcn33_bt", VCN33_BT, lकरो_volt_table1,
		MT6323_ANALDO_CON16, 7, MT6323_ANALDO_CON16, 0xC,
		MT6323_ANALDO_CON21, 0x2),
	MT6323_LDO("ldo_vcn33_wifi", VCN33_WIFI, lकरो_volt_table1,
		MT6323_ANALDO_CON17, 12, MT6323_ANALDO_CON16, 0xC,
		MT6323_ANALDO_CON21, 0x2),
	MT6323_REG_FIXED("ldo_va", VA, MT6323_ANALDO_CON2, 14, 2800000,
		MT6323_ANALDO_CON2, 0x2),
	MT6323_LDO("ldo_vcama", VCAMA, lकरो_volt_table2,
		MT6323_ANALDO_CON4, 15, MT6323_ANALDO_CON10, 0x60, -1, 0),
	MT6323_REG_FIXED("ldo_vio28", VIO28, MT6323_DIGLDO_CON0, 14, 2800000,
		MT6323_DIGLDO_CON0, 0x2),
	MT6323_REG_FIXED("ldo_vusb", VUSB, MT6323_DIGLDO_CON2, 14, 3300000,
		MT6323_DIGLDO_CON2, 0x2),
	MT6323_LDO("ldo_vmc", VMC, lकरो_volt_table3,
		MT6323_DIGLDO_CON3, 12, MT6323_DIGLDO_CON24, 0x10,
		MT6323_DIGLDO_CON3, 0x2),
	MT6323_LDO("ldo_vmch", VMCH, lकरो_volt_table4,
		MT6323_DIGLDO_CON5, 14, MT6323_DIGLDO_CON26, 0x80,
		MT6323_DIGLDO_CON5, 0x2),
	MT6323_LDO("ldo_vemc3v3", VEMC3V3, lकरो_volt_table4,
		MT6323_DIGLDO_CON6, 14, MT6323_DIGLDO_CON27, 0x80,
		MT6323_DIGLDO_CON6, 0x2),
	MT6323_LDO("ldo_vgp1", VGP1, lकरो_volt_table5,
		MT6323_DIGLDO_CON7, 15, MT6323_DIGLDO_CON28, 0xE0,
		MT6323_DIGLDO_CON7, 0x2),
	MT6323_LDO("ldo_vgp2", VGP2, lकरो_volt_table6,
		MT6323_DIGLDO_CON8, 15, MT6323_DIGLDO_CON29, 0xE0,
		MT6323_DIGLDO_CON8, 0x2),
	MT6323_LDO("ldo_vgp3", VGP3, lकरो_volt_table7,
		MT6323_DIGLDO_CON9, 15, MT6323_DIGLDO_CON30, 0x60,
		MT6323_DIGLDO_CON9, 0x2),
	MT6323_REG_FIXED("ldo_vcn18", VCN18, MT6323_DIGLDO_CON11, 14, 1800000,
		MT6323_DIGLDO_CON11, 0x2),
	MT6323_LDO("ldo_vsim1", VSIM1, lकरो_volt_table8,
		MT6323_DIGLDO_CON13, 15, MT6323_DIGLDO_CON34, 0x20,
		MT6323_DIGLDO_CON13, 0x2),
	MT6323_LDO("ldo_vsim2", VSIM2, lकरो_volt_table8,
		MT6323_DIGLDO_CON14, 15, MT6323_DIGLDO_CON35, 0x20,
		MT6323_DIGLDO_CON14, 0x2),
	MT6323_REG_FIXED("ldo_vrtc", VRTC, MT6323_DIGLDO_CON15, 8, 2800000,
		-1, 0),
	MT6323_LDO("ldo_vcamaf", VCAMAF, lकरो_volt_table5,
		MT6323_DIGLDO_CON31, 15, MT6323_DIGLDO_CON32, 0xE0,
		MT6323_DIGLDO_CON31, 0x2),
	MT6323_LDO("ldo_vibr", VIBR, lकरो_volt_table5,
		MT6323_DIGLDO_CON39, 15, MT6323_DIGLDO_CON40, 0xE0,
		MT6323_DIGLDO_CON39, 0x2),
	MT6323_REG_FIXED("ldo_vrf18", VRF18, MT6323_DIGLDO_CON45, 15, 1825000,
		MT6323_DIGLDO_CON45, 0x2),
	MT6323_LDO("ldo_vm", VM, lकरो_volt_table9,
		MT6323_DIGLDO_CON47, 14, MT6323_DIGLDO_CON48, 0x30,
		MT6323_DIGLDO_CON47, 0x2),
	MT6323_REG_FIXED("ldo_vio18", VIO18, MT6323_DIGLDO_CON49, 14, 1800000,
		MT6323_DIGLDO_CON49, 0x2),
	MT6323_LDO("ldo_vcamd", VCAMD, lकरो_volt_table10,
		MT6323_DIGLDO_CON51, 14, MT6323_DIGLDO_CON52, 0x60,
		MT6323_DIGLDO_CON51, 0x2),
	MT6323_REG_FIXED("ldo_vcamio", VCAMIO, MT6323_DIGLDO_CON53, 14, 1800000,
		MT6323_DIGLDO_CON53, 0x2),
पूर्ण;

अटल पूर्णांक mt6323_set_buck_vosel_reg(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6397_chip *mt6323 = dev_get_drvdata(pdev->dev.parent);
	पूर्णांक i;
	u32 regval;

	क्रम (i = 0; i < MT6323_MAX_REGULATOR; i++) अणु
		अगर (mt6323_regulators[i].vselctrl_reg) अणु
			अगर (regmap_पढ़ो(mt6323->regmap,
				mt6323_regulators[i].vselctrl_reg,
				&regval) < 0) अणु
				dev_err(&pdev->dev,
					"Failed to read buck ctrl\n");
				वापस -EIO;
			पूर्ण

			अगर (regval & mt6323_regulators[i].vselctrl_mask) अणु
				mt6323_regulators[i].desc.vsel_reg =
				mt6323_regulators[i].vselon_reg;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt6323_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6397_chip *mt6323 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;
	u32 reg_value;

	/* Query buck controller to select activated voltage रेजिस्टर part */
	अगर (mt6323_set_buck_vosel_reg(pdev))
		वापस -EIO;

	/* Read PMIC chip revision to update स्थिरraपूर्णांकs and voltage table */
	अगर (regmap_पढ़ो(mt6323->regmap, MT6323_CID, &reg_value) < 0) अणु
		dev_err(&pdev->dev, "Failed to read Chip ID\n");
		वापस -EIO;
	पूर्ण
	dev_info(&pdev->dev, "Chip ID = 0x%x\n", reg_value);

	क्रम (i = 0; i < MT6323_MAX_REGULATOR; i++) अणु
		config.dev = &pdev->dev;
		config.driver_data = &mt6323_regulators[i];
		config.regmap = mt6323->regmap;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
				&mt6323_regulators[i].desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register %s\n",
				mt6323_regulators[i].desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mt6323_platक्रमm_ids[] = अणु
	अणु"mt6323-regulator", 0पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mt6323_platक्रमm_ids);

अटल काष्ठा platक्रमm_driver mt6323_regulator_driver = अणु
	.driver = अणु
		.name = "mt6323-regulator",
	पूर्ण,
	.probe = mt6323_regulator_probe,
	.id_table = mt6323_platक्रमm_ids,
पूर्ण;

module_platक्रमm_driver(mt6323_regulator_driver);

MODULE_AUTHOR("Chen Zhong <chen.zhong@mediatek.com>");
MODULE_DESCRIPTION("Regulator Driver for MediaTek MT6323 PMIC");
MODULE_LICENSE("GPL v2");
