<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2019 MediaTek Inc.

#समावेश <linux/mfd/mt6358/रेजिस्टरs.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/mt6358-regulator.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा MT6358_BUCK_MODE_AUTO	0
#घोषणा MT6358_BUCK_MODE_FORCE_PWM	1

/*
 * MT6358 regulators' inक्रमmation
 *
 * @desc: standard fields of regulator description.
 * @qi: Mask क्रम query enable संकेत status of regulators
 */
काष्ठा mt6358_regulator_info अणु
	काष्ठा regulator_desc desc;
	u32 status_reg;
	u32 qi;
	स्थिर u32 *index_table;
	अचिन्हित पूर्णांक n_table;
	u32 vsel_shअगरt;
	u32 da_vsel_reg;
	u32 da_vsel_mask;
	u32 da_vsel_shअगरt;
	u32 modeset_reg;
	u32 modeset_mask;
	u32 modeset_shअगरt;
पूर्ण;

#घोषणा MT6358_BUCK(match, vreg, min, max, step,		\
	volt_ranges, vosel_mask, _da_vsel_reg, _da_vsel_mask,	\
	_da_vsel_shअगरt, _modeset_reg, _modeset_shअगरt)		\
[MT6358_ID_##vreg] = अणु	\
	.desc = अणु	\
		.name = #vreg,	\
		.of_match = of_match_ptr(match),	\
		.ops = &mt6358_volt_range_ops,	\
		.type = REGULATOR_VOLTAGE,	\
		.id = MT6358_ID_##vreg,		\
		.owner = THIS_MODULE,		\
		.n_voltages = ((max) - (min)) / (step) + 1,	\
		.linear_ranges = volt_ranges,		\
		.n_linear_ranges = ARRAY_SIZE(volt_ranges),	\
		.vsel_reg = MT6358_BUCK_##vreg##_ELR0,	\
		.vsel_mask = vosel_mask,	\
		.enable_reg = MT6358_BUCK_##vreg##_CON0,	\
		.enable_mask = BIT(0),	\
		.of_map_mode = mt6358_map_mode,	\
	पूर्ण,	\
	.status_reg = MT6358_BUCK_##vreg##_DBG1,	\
	.qi = BIT(0),	\
	.da_vsel_reg = _da_vsel_reg,	\
	.da_vsel_mask = _da_vsel_mask,	\
	.da_vsel_shअगरt = _da_vsel_shअगरt,	\
	.modeset_reg = _modeset_reg,	\
	.modeset_mask = BIT(_modeset_shअगरt),	\
	.modeset_shअगरt = _modeset_shअगरt	\
पूर्ण

#घोषणा MT6358_LDO(match, vreg, lकरो_volt_table,	\
	lकरो_index_table, enreg, enbit, vosel,	\
	vosel_mask, vosel_shअगरt)	\
[MT6358_ID_##vreg] = अणु	\
	.desc = अणु	\
		.name = #vreg,	\
		.of_match = of_match_ptr(match),	\
		.ops = &mt6358_volt_table_ops,	\
		.type = REGULATOR_VOLTAGE,	\
		.id = MT6358_ID_##vreg,	\
		.owner = THIS_MODULE,	\
		.n_voltages = ARRAY_SIZE(lकरो_volt_table),	\
		.volt_table = lकरो_volt_table,	\
		.vsel_reg = vosel,	\
		.vsel_mask = vosel_mask,	\
		.enable_reg = enreg,	\
		.enable_mask = BIT(enbit),	\
	पूर्ण,	\
	.status_reg = MT6358_LDO_##vreg##_CON1,	\
	.qi = BIT(15),	\
	.index_table = lकरो_index_table,	\
	.n_table = ARRAY_SIZE(lकरो_index_table),	\
	.vsel_shअगरt = vosel_shअगरt,	\
पूर्ण

#घोषणा MT6358_LDO1(match, vreg, min, max, step,	\
	volt_ranges, _da_vsel_reg, _da_vsel_mask,	\
	_da_vsel_shअगरt, vosel, vosel_mask)	\
[MT6358_ID_##vreg] = अणु	\
	.desc = अणु	\
		.name = #vreg,	\
		.of_match = of_match_ptr(match),	\
		.ops = &mt6358_volt_range_ops,	\
		.type = REGULATOR_VOLTAGE,	\
		.id = MT6358_ID_##vreg,	\
		.owner = THIS_MODULE,	\
		.n_voltages = ((max) - (min)) / (step) + 1,	\
		.linear_ranges = volt_ranges,	\
		.n_linear_ranges = ARRAY_SIZE(volt_ranges),	\
		.vsel_reg = vosel,	\
		.vsel_mask = vosel_mask,	\
		.enable_reg = MT6358_LDO_##vreg##_CON0,	\
		.enable_mask = BIT(0),	\
	पूर्ण,	\
	.da_vsel_reg = _da_vsel_reg,	\
	.da_vsel_mask = _da_vsel_mask,	\
	.da_vsel_shअगरt = _da_vsel_shअगरt,	\
	.status_reg = MT6358_LDO_##vreg##_DBG1,	\
	.qi = BIT(0),	\
पूर्ण

#घोषणा MT6358_REG_FIXED(match, vreg,	\
	enreg, enbit, volt)	\
[MT6358_ID_##vreg] = अणु	\
	.desc = अणु	\
		.name = #vreg,	\
		.of_match = of_match_ptr(match),	\
		.ops = &mt6358_volt_fixed_ops,	\
		.type = REGULATOR_VOLTAGE,	\
		.id = MT6358_ID_##vreg,	\
		.owner = THIS_MODULE,	\
		.n_voltages = 1,	\
		.enable_reg = enreg,	\
		.enable_mask = BIT(enbit),	\
		.min_uV = volt,	\
	पूर्ण,	\
	.status_reg = MT6358_LDO_##vreg##_CON1,	\
	.qi = BIT(15),							\
पूर्ण

अटल स्थिर काष्ठा linear_range buck_volt_range1[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0, 0x7f, 6250),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range2[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0, 0x7f, 12500),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range3[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0, 0x3f, 50000),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck_volt_range4[] = अणु
	REGULATOR_LINEAR_RANGE(1000000, 0, 0x7f, 12500),
पूर्ण;

अटल स्थिर u32 vdram2_voltages[] = अणु
	600000, 1800000,
पूर्ण;

अटल स्थिर u32 vsim_voltages[] = अणु
	1700000, 1800000, 2700000, 3000000, 3100000,
पूर्ण;

अटल स्थिर u32 vibr_voltages[] = अणु
	1200000, 1300000, 1500000, 1800000,
	2000000, 2800000, 3000000, 3300000,
पूर्ण;

अटल स्थिर u32 vusb_voltages[] = अणु
	3000000, 3100000,
पूर्ण;

अटल स्थिर u32 vcamd_voltages[] = अणु
	900000, 1000000, 1100000, 1200000,
	1300000, 1500000, 1800000,
पूर्ण;

अटल स्थिर u32 vefuse_voltages[] = अणु
	1700000, 1800000, 1900000,
पूर्ण;

अटल स्थिर u32 vmch_vemc_voltages[] = अणु
	2900000, 3000000, 3300000,
पूर्ण;

अटल स्थिर u32 vcama_voltages[] = अणु
	1800000, 2500000, 2700000,
	2800000, 2900000, 3000000,
पूर्ण;

अटल स्थिर u32 vcn33_bt_wअगरi_voltages[] = अणु
	3300000, 3400000, 3500000,
पूर्ण;

अटल स्थिर u32 vmc_voltages[] = अणु
	1800000, 2900000, 3000000, 3300000,
पूर्ण;

अटल स्थिर u32 vlकरो28_voltages[] = अणु
	2800000, 3000000,
पूर्ण;

अटल स्थिर u32 vdram2_idx[] = अणु
	0, 12,
पूर्ण;

अटल स्थिर u32 vsim_idx[] = अणु
	3, 4, 8, 11, 12,
पूर्ण;

अटल स्थिर u32 vibr_idx[] = अणु
	0, 1, 2, 4, 5, 9, 11, 13,
पूर्ण;

अटल स्थिर u32 vusb_idx[] = अणु
	3, 4,
पूर्ण;

अटल स्थिर u32 vcamd_idx[] = अणु
	3, 4, 5, 6, 7, 9, 12,
पूर्ण;

अटल स्थिर u32 vefuse_idx[] = अणु
	11, 12, 13,
पूर्ण;

अटल स्थिर u32 vmch_vemc_idx[] = अणु
	2, 3, 5,
पूर्ण;

अटल स्थिर u32 vcama_idx[] = अणु
	0, 7, 9, 10, 11, 12,
पूर्ण;

अटल स्थिर u32 vcn33_bt_wअगरi_idx[] = अणु
	1, 2, 3,
पूर्ण;

अटल स्थिर u32 vmc_idx[] = अणु
	4, 10, 11, 13,
पूर्ण;

अटल स्थिर u32 vlकरो28_idx[] = अणु
	1, 3,
पूर्ण;

अटल अचिन्हित पूर्णांक mt6358_map_mode(अचिन्हित पूर्णांक mode)
अणु
	वापस mode == MT6358_BUCK_MODE_AUTO ?
		REGULATOR_MODE_NORMAL : REGULATOR_MODE_FAST;
पूर्ण

अटल पूर्णांक mt6358_set_voltage_sel(काष्ठा regulator_dev *rdev,
				  अचिन्हित पूर्णांक selector)
अणु
	पूर्णांक idx, ret;
	स्थिर u32 *pvol;
	काष्ठा mt6358_regulator_info *info = rdev_get_drvdata(rdev);

	pvol = info->index_table;

	idx = pvol[selector];
	ret = regmap_update_bits(rdev->regmap, info->desc.vsel_reg,
				 info->desc.vsel_mask,
				 idx << info->vsel_shअगरt);

	वापस ret;
पूर्ण

अटल पूर्णांक mt6358_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक idx, ret;
	u32 selector;
	काष्ठा mt6358_regulator_info *info = rdev_get_drvdata(rdev);
	स्थिर u32 *pvol;

	ret = regmap_पढ़ो(rdev->regmap, info->desc.vsel_reg, &selector);
	अगर (ret != 0) अणु
		dev_info(&rdev->dev,
			 "Failed to get mt6358 %s vsel reg: %d\n",
			 info->desc.name, ret);
		वापस ret;
	पूर्ण

	selector = (selector & info->desc.vsel_mask) >> info->vsel_shअगरt;
	pvol = info->index_table;
	क्रम (idx = 0; idx < info->desc.n_voltages; idx++) अणु
		अगर (pvol[idx] == selector)
			वापस idx;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mt6358_get_buck_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret, regval;
	काष्ठा mt6358_regulator_info *info = rdev_get_drvdata(rdev);

	ret = regmap_पढ़ो(rdev->regmap, info->da_vsel_reg, &regval);
	अगर (ret != 0) अणु
		dev_err(&rdev->dev,
			"Failed to get mt6358 Buck %s vsel reg: %d\n",
			info->desc.name, ret);
		वापस ret;
	पूर्ण

	ret = (regval >> info->da_vsel_shअगरt) & info->da_vsel_mask;

	वापस ret;
पूर्ण

अटल पूर्णांक mt6358_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	u32 regval;
	काष्ठा mt6358_regulator_info *info = rdev_get_drvdata(rdev);

	ret = regmap_पढ़ो(rdev->regmap, info->status_reg, &regval);
	अगर (ret != 0) अणु
		dev_info(&rdev->dev, "Failed to get enable reg: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस (regval & info->qi) ? REGULATOR_STATUS_ON : REGULATOR_STATUS_OFF;
पूर्ण

अटल पूर्णांक mt6358_regulator_set_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	काष्ठा mt6358_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक val;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = MT6358_BUCK_MODE_FORCE_PWM;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = MT6358_BUCK_MODE_AUTO;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&rdev->dev, "mt6358 buck set_mode %#x, %#x, %#x, %#x\n",
		info->modeset_reg, info->modeset_mask,
		info->modeset_shअगरt, val);

	val <<= info->modeset_shअगरt;

	वापस regmap_update_bits(rdev->regmap, info->modeset_reg,
				  info->modeset_mask, val);
पूर्ण

अटल अचिन्हित पूर्णांक mt6358_regulator_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा mt6358_regulator_info *info = rdev_get_drvdata(rdev);
	पूर्णांक ret, regval;

	ret = regmap_पढ़ो(rdev->regmap, info->modeset_reg, &regval);
	अगर (ret != 0) अणु
		dev_err(&rdev->dev,
			"Failed to get mt6358 buck mode: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन ((regval & info->modeset_mask) >> info->modeset_shअगरt) अणु
	हाल MT6358_BUCK_MODE_AUTO:
		वापस REGULATOR_MODE_NORMAL;
	हाल MT6358_BUCK_MODE_FORCE_PWM:
		वापस REGULATOR_MODE_FAST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regulator_ops mt6358_volt_range_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = mt6358_get_buck_voltage_sel,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6358_get_status,
	.set_mode = mt6358_regulator_set_mode,
	.get_mode = mt6358_regulator_get_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6358_volt_table_ops = अणु
	.list_voltage = regulator_list_voltage_table,
	.map_voltage = regulator_map_voltage_iterate,
	.set_voltage_sel = mt6358_set_voltage_sel,
	.get_voltage_sel = mt6358_get_voltage_sel,
	.set_voltage_समय_sel = regulator_set_voltage_समय_sel,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6358_get_status,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops mt6358_volt_fixed_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_status = mt6358_get_status,
पूर्ण;

/* The array is indexed by id(MT6358_ID_XXX) */
अटल काष्ठा mt6358_regulator_info mt6358_regulators[] = अणु
	MT6358_BUCK("buck_vdram1", VDRAM1, 500000, 2087500, 12500,
		    buck_volt_range2, 0x7f, MT6358_BUCK_VDRAM1_DBG0, 0x7f,
		    0, MT6358_VDRAM1_ANA_CON0, 8),
	MT6358_BUCK("buck_vcore", VCORE, 500000, 1293750, 6250,
		    buck_volt_range1, 0x7f, MT6358_BUCK_VCORE_DBG0, 0x7f,
		    0, MT6358_VCORE_VGPU_ANA_CON0, 1),
	MT6358_BUCK("buck_vpa", VPA, 500000, 3650000, 50000,
		    buck_volt_range3, 0x3f, MT6358_BUCK_VPA_DBG0, 0x3f, 0,
		    MT6358_VPA_ANA_CON0, 3),
	MT6358_BUCK("buck_vproc11", VPROC11, 500000, 1293750, 6250,
		    buck_volt_range1, 0x7f, MT6358_BUCK_VPROC11_DBG0, 0x7f,
		    0, MT6358_VPROC_ANA_CON0, 1),
	MT6358_BUCK("buck_vproc12", VPROC12, 500000, 1293750, 6250,
		    buck_volt_range1, 0x7f, MT6358_BUCK_VPROC12_DBG0, 0x7f,
		    0, MT6358_VPROC_ANA_CON0, 2),
	MT6358_BUCK("buck_vgpu", VGPU, 500000, 1293750, 6250,
		    buck_volt_range1, 0x7f, MT6358_BUCK_VGPU_ELR0, 0x7f, 0,
		    MT6358_VCORE_VGPU_ANA_CON0, 2),
	MT6358_BUCK("buck_vs2", VS2, 500000, 2087500, 12500,
		    buck_volt_range2, 0x7f, MT6358_BUCK_VS2_DBG0, 0x7f, 0,
		    MT6358_VS2_ANA_CON0, 8),
	MT6358_BUCK("buck_vmodem", VMODEM, 500000, 1293750, 6250,
		    buck_volt_range1, 0x7f, MT6358_BUCK_VMODEM_DBG0, 0x7f,
		    0, MT6358_VMODEM_ANA_CON0, 8),
	MT6358_BUCK("buck_vs1", VS1, 1000000, 2587500, 12500,
		    buck_volt_range4, 0x7f, MT6358_BUCK_VS1_DBG0, 0x7f, 0,
		    MT6358_VS1_ANA_CON0, 8),
	MT6358_REG_FIXED("ldo_vrf12", VRF12,
			 MT6358_LDO_VRF12_CON0, 0, 1200000),
	MT6358_REG_FIXED("ldo_vio18", VIO18,
			 MT6358_LDO_VIO18_CON0, 0, 1800000),
	MT6358_REG_FIXED("ldo_vcamio", VCAMIO,
			 MT6358_LDO_VCAMIO_CON0, 0, 1800000),
	MT6358_REG_FIXED("ldo_vcn18", VCN18, MT6358_LDO_VCN18_CON0, 0, 1800000),
	MT6358_REG_FIXED("ldo_vfe28", VFE28, MT6358_LDO_VFE28_CON0, 0, 2800000),
	MT6358_REG_FIXED("ldo_vcn28", VCN28, MT6358_LDO_VCN28_CON0, 0, 2800000),
	MT6358_REG_FIXED("ldo_vxo22", VXO22, MT6358_LDO_VXO22_CON0, 0, 2200000),
	MT6358_REG_FIXED("ldo_vaux18", VAUX18,
			 MT6358_LDO_VAUX18_CON0, 0, 1800000),
	MT6358_REG_FIXED("ldo_vbif28", VBIF28,
			 MT6358_LDO_VBIF28_CON0, 0, 2800000),
	MT6358_REG_FIXED("ldo_vio28", VIO28, MT6358_LDO_VIO28_CON0, 0, 2800000),
	MT6358_REG_FIXED("ldo_va12", VA12, MT6358_LDO_VA12_CON0, 0, 1200000),
	MT6358_REG_FIXED("ldo_vrf18", VRF18, MT6358_LDO_VRF18_CON0, 0, 1800000),
	MT6358_REG_FIXED("ldo_vaud28", VAUD28,
			 MT6358_LDO_VAUD28_CON0, 0, 2800000),
	MT6358_LDO("ldo_vdram2", VDRAM2, vdram2_voltages, vdram2_idx,
		   MT6358_LDO_VDRAM2_CON0, 0, MT6358_LDO_VDRAM2_ELR0, 0x10, 0),
	MT6358_LDO("ldo_vsim1", VSIM1, vsim_voltages, vsim_idx,
		   MT6358_LDO_VSIM1_CON0, 0, MT6358_VSIM1_ANA_CON0, 0xf00, 8),
	MT6358_LDO("ldo_vibr", VIBR, vibr_voltages, vibr_idx,
		   MT6358_LDO_VIBR_CON0, 0, MT6358_VIBR_ANA_CON0, 0xf00, 8),
	MT6358_LDO("ldo_vusb", VUSB, vusb_voltages, vusb_idx,
		   MT6358_LDO_VUSB_CON0_0, 0, MT6358_VUSB_ANA_CON0, 0x700, 8),
	MT6358_LDO("ldo_vcamd", VCAMD, vcamd_voltages, vcamd_idx,
		   MT6358_LDO_VCAMD_CON0, 0, MT6358_VCAMD_ANA_CON0, 0xf00, 8),
	MT6358_LDO("ldo_vefuse", VEFUSE, vefuse_voltages, vefuse_idx,
		   MT6358_LDO_VEFUSE_CON0, 0, MT6358_VEFUSE_ANA_CON0, 0xf00, 8),
	MT6358_LDO("ldo_vmch", VMCH, vmch_vemc_voltages, vmch_vemc_idx,
		   MT6358_LDO_VMCH_CON0, 0, MT6358_VMCH_ANA_CON0, 0x700, 8),
	MT6358_LDO("ldo_vcama1", VCAMA1, vcama_voltages, vcama_idx,
		   MT6358_LDO_VCAMA1_CON0, 0, MT6358_VCAMA1_ANA_CON0, 0xf00, 8),
	MT6358_LDO("ldo_vemc", VEMC, vmch_vemc_voltages, vmch_vemc_idx,
		   MT6358_LDO_VEMC_CON0, 0, MT6358_VEMC_ANA_CON0, 0x700, 8),
	MT6358_LDO("ldo_vcn33_bt", VCN33_BT, vcn33_bt_wअगरi_voltages,
		   vcn33_bt_wअगरi_idx, MT6358_LDO_VCN33_CON0_0,
		   0, MT6358_VCN33_ANA_CON0, 0x300, 8),
	MT6358_LDO("ldo_vcn33_wifi", VCN33_WIFI, vcn33_bt_wअगरi_voltages,
		   vcn33_bt_wअगरi_idx, MT6358_LDO_VCN33_CON0_1,
		   0, MT6358_VCN33_ANA_CON0, 0x300, 8),
	MT6358_LDO("ldo_vcama2", VCAMA2, vcama_voltages, vcama_idx,
		   MT6358_LDO_VCAMA2_CON0, 0, MT6358_VCAMA2_ANA_CON0, 0xf00, 8),
	MT6358_LDO("ldo_vmc", VMC, vmc_voltages, vmc_idx,
		   MT6358_LDO_VMC_CON0, 0, MT6358_VMC_ANA_CON0, 0xf00, 8),
	MT6358_LDO("ldo_vldo28", VLDO28, vlकरो28_voltages, vlकरो28_idx,
		   MT6358_LDO_VLDO28_CON0_0, 0,
		   MT6358_VLDO28_ANA_CON0, 0x300, 8),
	MT6358_LDO("ldo_vsim2", VSIM2, vsim_voltages, vsim_idx,
		   MT6358_LDO_VSIM2_CON0, 0, MT6358_VSIM2_ANA_CON0, 0xf00, 8),
	MT6358_LDO1("ldo_vsram_proc11", VSRAM_PROC11, 500000, 1293750, 6250,
		    buck_volt_range1, MT6358_LDO_VSRAM_PROC11_DBG0, 0x7f, 8,
		    MT6358_LDO_VSRAM_CON0, 0x7f),
	MT6358_LDO1("ldo_vsram_others", VSRAM_OTHERS, 500000, 1293750, 6250,
		    buck_volt_range1, MT6358_LDO_VSRAM_OTHERS_DBG0, 0x7f, 8,
		    MT6358_LDO_VSRAM_CON2, 0x7f),
	MT6358_LDO1("ldo_vsram_gpu", VSRAM_GPU, 500000, 1293750, 6250,
		    buck_volt_range1, MT6358_LDO_VSRAM_GPU_DBG0, 0x7f, 8,
		    MT6358_LDO_VSRAM_CON3, 0x7f),
	MT6358_LDO1("ldo_vsram_proc12", VSRAM_PROC12, 500000, 1293750, 6250,
		    buck_volt_range1, MT6358_LDO_VSRAM_PROC12_DBG0, 0x7f, 8,
		    MT6358_LDO_VSRAM_CON1, 0x7f),
पूर्ण;

अटल पूर्णांक mt6358_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6397_chip *mt6397 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_dev *rdev;
	पूर्णांक i;

	क्रम (i = 0; i < MT6358_MAX_REGULATOR; i++) अणु
		config.dev = &pdev->dev;
		config.driver_data = &mt6358_regulators[i];
		config.regmap = mt6397->regmap;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
					       &mt6358_regulators[i].desc,
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "failed to register %s\n",
				mt6358_regulators[i].desc.name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mt6358_platक्रमm_ids[] = अणु
	अणु"mt6358-regulator", 0पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, mt6358_platक्रमm_ids);

अटल काष्ठा platक्रमm_driver mt6358_regulator_driver = अणु
	.driver = अणु
		.name = "mt6358-regulator",
	पूर्ण,
	.probe = mt6358_regulator_probe,
	.id_table = mt6358_platक्रमm_ids,
पूर्ण;

module_platक्रमm_driver(mt6358_regulator_driver);

MODULE_AUTHOR("Hsin-Hsiung Wang <hsin-hsiung.wang@mediatek.com>");
MODULE_DESCRIPTION("Regulator Driver for MediaTek MT6358 PMIC");
MODULE_LICENSE("GPL");
