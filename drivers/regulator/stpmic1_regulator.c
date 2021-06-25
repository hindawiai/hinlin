<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) STMicroelectronics 2018
// Author: Pascal Paillet <p.paillet@st.com> क्रम STMicroelectronics.

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/stpmic1.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>

#समावेश <dt-bindings/mfd/st,stpmic1.h>

/**
 * काष्ठा stpmic1 regulator description: this काष्ठाure is used as driver data
 * @desc: regulator framework description
 * @mask_reset_reg: mask reset रेजिस्टर address
 * @mask_reset_mask: mask rank and mask reset रेजिस्टर mask
 * @icc_reg: icc रेजिस्टर address
 * @icc_mask: icc रेजिस्टर mask
 */
काष्ठा stpmic1_regulator_cfg अणु
	काष्ठा regulator_desc desc;
	u8 mask_reset_reg;
	u8 mask_reset_mask;
	u8 icc_reg;
	u8 icc_mask;
पूर्ण;

अटल पूर्णांक stpmic1_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode);
अटल अचिन्हित पूर्णांक stpmic1_get_mode(काष्ठा regulator_dev *rdev);
अटल पूर्णांक stpmic1_set_icc(काष्ठा regulator_dev *rdev);
अटल अचिन्हित पूर्णांक stpmic1_map_mode(अचिन्हित पूर्णांक mode);

क्रमागत अणु
	STPMIC1_BUCK1 = 0,
	STPMIC1_BUCK2 = 1,
	STPMIC1_BUCK3 = 2,
	STPMIC1_BUCK4 = 3,
	STPMIC1_LDO1 = 4,
	STPMIC1_LDO2 = 5,
	STPMIC1_LDO3 = 6,
	STPMIC1_LDO4 = 7,
	STPMIC1_LDO5 = 8,
	STPMIC1_LDO6 = 9,
	STPMIC1_VREF_DDR = 10,
	STPMIC1_BOOST = 11,
	STPMIC1_VBUS_OTG = 12,
	STPMIC1_SW_OUT = 13,
पूर्ण;

/* Enable समय worst हाल is 5000mV/(2250uV/uS) */
#घोषणा PMIC_ENABLE_TIME_US 2200
/* Ramp delay worst हाल is (2250uV/uS) */
#घोषणा PMIC_RAMP_DELAY 2200

अटल स्थिर काष्ठा linear_range buck1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(725000, 0, 4, 0),
	REGULATOR_LINEAR_RANGE(725000, 5, 36, 25000),
	REGULATOR_LINEAR_RANGE(1500000, 37, 63, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck2_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1000000, 0, 17, 0),
	REGULATOR_LINEAR_RANGE(1050000, 18, 19, 0),
	REGULATOR_LINEAR_RANGE(1100000, 20, 21, 0),
	REGULATOR_LINEAR_RANGE(1150000, 22, 23, 0),
	REGULATOR_LINEAR_RANGE(1200000, 24, 25, 0),
	REGULATOR_LINEAR_RANGE(1250000, 26, 27, 0),
	REGULATOR_LINEAR_RANGE(1300000, 28, 29, 0),
	REGULATOR_LINEAR_RANGE(1350000, 30, 31, 0),
	REGULATOR_LINEAR_RANGE(1400000, 32, 33, 0),
	REGULATOR_LINEAR_RANGE(1450000, 34, 35, 0),
	REGULATOR_LINEAR_RANGE(1500000, 36, 63, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck3_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1000000, 0, 19, 0),
	REGULATOR_LINEAR_RANGE(1100000, 20, 23, 0),
	REGULATOR_LINEAR_RANGE(1200000, 24, 27, 0),
	REGULATOR_LINEAR_RANGE(1300000, 28, 31, 0),
	REGULATOR_LINEAR_RANGE(1400000, 32, 35, 0),
	REGULATOR_LINEAR_RANGE(1500000, 36, 55, 100000),
	REGULATOR_LINEAR_RANGE(3400000, 56, 63, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range buck4_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 27, 25000),
	REGULATOR_LINEAR_RANGE(1300000, 28, 29, 0),
	REGULATOR_LINEAR_RANGE(1350000, 30, 31, 0),
	REGULATOR_LINEAR_RANGE(1400000, 32, 33, 0),
	REGULATOR_LINEAR_RANGE(1450000, 34, 35, 0),
	REGULATOR_LINEAR_RANGE(1500000, 36, 60, 100000),
	REGULATOR_LINEAR_RANGE(3900000, 61, 63, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1700000, 0, 7, 0),
	REGULATOR_LINEAR_RANGE(1700000, 8, 24, 100000),
	REGULATOR_LINEAR_RANGE(3300000, 25, 31, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो2_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1700000, 0, 7, 0),
	REGULATOR_LINEAR_RANGE(1700000, 8, 24, 100000),
	REGULATOR_LINEAR_RANGE(3300000, 25, 30, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो3_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1700000, 0, 7, 0),
	REGULATOR_LINEAR_RANGE(1700000, 8, 24, 100000),
	REGULATOR_LINEAR_RANGE(3300000, 25, 30, 0),
	/* with index 31 LDO3 is in DDR mode */
	REGULATOR_LINEAR_RANGE(500000, 31, 31, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो5_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1700000, 0, 7, 0),
	REGULATOR_LINEAR_RANGE(1700000, 8, 30, 100000),
	REGULATOR_LINEAR_RANGE(3900000, 31, 31, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range lकरो6_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(900000, 0, 24, 100000),
	REGULATOR_LINEAR_RANGE(3300000, 25, 31, 0),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stpmic1_lकरो_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_over_current_protection = stpmic1_set_icc,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stpmic1_lकरो3_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_iterate,
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_bypass = regulator_get_bypass_regmap,
	.set_bypass = regulator_set_bypass_regmap,
	.set_over_current_protection = stpmic1_set_icc,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stpmic1_lकरो4_fixed_regul_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.set_over_current_protection = stpmic1_set_icc,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stpmic1_buck_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.set_pull_करोwn = regulator_set_pull_करोwn_regmap,
	.set_mode = stpmic1_set_mode,
	.get_mode = stpmic1_get_mode,
	.set_over_current_protection = stpmic1_set_icc,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stpmic1_vref_ddr_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stpmic1_boost_regul_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.set_over_current_protection = stpmic1_set_icc,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops stpmic1_चयन_regul_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.set_over_current_protection = stpmic1_set_icc,
	.set_active_disअक्षरge = regulator_set_active_disअक्षरge_regmap,
पूर्ण;

#घोषणा REG_LDO(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_voltages = 32, \
	.ops = &stpmic1_lकरो_ops, \
	.linear_ranges = base ## _ranges, \
	.n_linear_ranges = ARRAY_SIZE(base ## _ranges), \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.vsel_reg = ids##_ACTIVE_CR, \
	.vsel_mask = LDO_VOLTAGE_MASK, \
	.enable_reg = ids##_ACTIVE_CR, \
	.enable_mask = LDO_ENABLE_MASK, \
	.enable_val = 1, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.ramp_delay = PMIC_RAMP_DELAY, \
	.supply_name = #base, \
पूर्ण

#घोषणा REG_LDO3(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_voltages = 32, \
	.ops = &stpmic1_lकरो3_ops, \
	.linear_ranges = lकरो3_ranges, \
	.n_linear_ranges = ARRAY_SIZE(lकरो3_ranges), \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.vsel_reg = LDO3_ACTIVE_CR, \
	.vsel_mask = LDO_VOLTAGE_MASK, \
	.enable_reg = LDO3_ACTIVE_CR, \
	.enable_mask = LDO_ENABLE_MASK, \
	.enable_val = 1, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.ramp_delay = PMIC_RAMP_DELAY, \
	.bypass_reg = LDO3_ACTIVE_CR, \
	.bypass_mask = LDO_BYPASS_MASK, \
	.bypass_val_on = LDO_BYPASS_MASK, \
	.bypass_val_off = 0, \
	.supply_name = #base, \
पूर्ण

#घोषणा REG_LDO4(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_voltages = 1, \
	.ops = &stpmic1_lकरो4_fixed_regul_ops, \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.min_uV = 3300000, \
	.fixed_uV = 3300000, \
	.enable_reg = LDO4_ACTIVE_CR, \
	.enable_mask = LDO_ENABLE_MASK, \
	.enable_val = 1, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.ramp_delay = PMIC_RAMP_DELAY, \
	.supply_name = #base, \
पूर्ण

#घोषणा REG_BUCK(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.ops = &stpmic1_buck_ops, \
	.n_voltages = 64, \
	.linear_ranges = base ## _ranges, \
	.n_linear_ranges = ARRAY_SIZE(base ## _ranges), \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.vsel_reg = ids##_ACTIVE_CR, \
	.vsel_mask = BUCK_VOLTAGE_MASK, \
	.enable_reg = ids##_ACTIVE_CR, \
	.enable_mask = BUCK_ENABLE_MASK, \
	.enable_val = 1, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.ramp_delay = PMIC_RAMP_DELAY, \
	.of_map_mode = stpmic1_map_mode, \
	.pull_करोwn_reg = ids##_PULL_DOWN_REG, \
	.pull_करोwn_mask = ids##_PULL_DOWN_MASK, \
	.supply_name = #base, \
पूर्ण

#घोषणा REG_VREF_DDR(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_voltages = 1, \
	.ops = &stpmic1_vref_ddr_ops, \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.min_uV = 500000, \
	.fixed_uV = 500000, \
	.enable_reg = VREF_DDR_ACTIVE_CR, \
	.enable_mask = BUCK_ENABLE_MASK, \
	.enable_val = 1, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.supply_name = #base, \
पूर्ण

#घोषणा REG_BOOST(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_voltages = 1, \
	.ops = &stpmic1_boost_regul_ops, \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.min_uV = 0, \
	.fixed_uV = 5000000, \
	.enable_reg = BST_SW_CR, \
	.enable_mask = BOOST_ENABLED, \
	.enable_val = BOOST_ENABLED, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.supply_name = #base, \
पूर्ण

#घोषणा REG_VBUS_OTG(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_voltages = 1, \
	.ops = &stpmic1_चयन_regul_ops, \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.min_uV = 0, \
	.fixed_uV = 5000000, \
	.enable_reg = BST_SW_CR, \
	.enable_mask = USBSW_OTG_SWITCH_ENABLED, \
	.enable_val = USBSW_OTG_SWITCH_ENABLED, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.supply_name = #base, \
	.active_disअक्षरge_reg = BST_SW_CR, \
	.active_disअक्षरge_mask = VBUS_OTG_DISCHARGE, \
	.active_disअक्षरge_on = VBUS_OTG_DISCHARGE, \
पूर्ण

#घोषणा REG_SW_OUT(ids, base) अणु \
	.name = #ids, \
	.id = STPMIC1_##ids, \
	.n_voltages = 1, \
	.ops = &stpmic1_चयन_regul_ops, \
	.type = REGULATOR_VOLTAGE, \
	.owner = THIS_MODULE, \
	.min_uV = 0, \
	.fixed_uV = 5000000, \
	.enable_reg = BST_SW_CR, \
	.enable_mask = SWIN_SWOUT_ENABLED, \
	.enable_val = SWIN_SWOUT_ENABLED, \
	.disable_val = 0, \
	.enable_समय = PMIC_ENABLE_TIME_US, \
	.supply_name = #base, \
	.active_disअक्षरge_reg = BST_SW_CR, \
	.active_disअक्षरge_mask = SW_OUT_DISCHARGE, \
	.active_disअक्षरge_on = SW_OUT_DISCHARGE, \
पूर्ण

अटल स्थिर काष्ठा stpmic1_regulator_cfg stpmic1_regulator_cfgs[] = अणु
	[STPMIC1_BUCK1] = अणु
		.desc = REG_BUCK(BUCK1, buck1),
		.icc_reg = BUCKS_ICCTO_CR,
		.icc_mask = BIT(0),
		.mask_reset_reg = BUCKS_MASK_RESET_CR,
		.mask_reset_mask = BIT(0),
	पूर्ण,
	[STPMIC1_BUCK2] = अणु
		.desc = REG_BUCK(BUCK2, buck2),
		.icc_reg = BUCKS_ICCTO_CR,
		.icc_mask = BIT(1),
		.mask_reset_reg = BUCKS_MASK_RESET_CR,
		.mask_reset_mask = BIT(1),
	पूर्ण,
	[STPMIC1_BUCK3] = अणु
		.desc = REG_BUCK(BUCK3, buck3),
		.icc_reg = BUCKS_ICCTO_CR,
		.icc_mask = BIT(2),
		.mask_reset_reg = BUCKS_MASK_RESET_CR,
		.mask_reset_mask = BIT(2),
	पूर्ण,
	[STPMIC1_BUCK4] = अणु
		.desc = REG_BUCK(BUCK4, buck4),
		.icc_reg = BUCKS_ICCTO_CR,
		.icc_mask = BIT(3),
		.mask_reset_reg = BUCKS_MASK_RESET_CR,
		.mask_reset_mask = BIT(3),
	पूर्ण,
	[STPMIC1_LDO1] = अणु
		.desc = REG_LDO(LDO1, lकरो1),
		.icc_reg = LDOS_ICCTO_CR,
		.icc_mask = BIT(0),
		.mask_reset_reg = LDOS_MASK_RESET_CR,
		.mask_reset_mask = BIT(0),
	पूर्ण,
	[STPMIC1_LDO2] = अणु
		.desc = REG_LDO(LDO2, lकरो2),
		.icc_reg = LDOS_ICCTO_CR,
		.icc_mask = BIT(1),
		.mask_reset_reg = LDOS_MASK_RESET_CR,
		.mask_reset_mask = BIT(1),
	पूर्ण,
	[STPMIC1_LDO3] = अणु
		.desc = REG_LDO3(LDO3, lकरो3),
		.icc_reg = LDOS_ICCTO_CR,
		.icc_mask = BIT(2),
		.mask_reset_reg = LDOS_MASK_RESET_CR,
		.mask_reset_mask = BIT(2),
	पूर्ण,
	[STPMIC1_LDO4] = अणु
		.desc = REG_LDO4(LDO4, lकरो4),
		.icc_reg = LDOS_ICCTO_CR,
		.icc_mask = BIT(3),
		.mask_reset_reg = LDOS_MASK_RESET_CR,
		.mask_reset_mask = BIT(3),
	पूर्ण,
	[STPMIC1_LDO5] = अणु
		.desc = REG_LDO(LDO5, lकरो5),
		.icc_reg = LDOS_ICCTO_CR,
		.icc_mask = BIT(4),
		.mask_reset_reg = LDOS_MASK_RESET_CR,
		.mask_reset_mask = BIT(4),
	पूर्ण,
	[STPMIC1_LDO6] = अणु
		.desc = REG_LDO(LDO6, lकरो6),
		.icc_reg = LDOS_ICCTO_CR,
		.icc_mask = BIT(5),
		.mask_reset_reg = LDOS_MASK_RESET_CR,
		.mask_reset_mask = BIT(5),
	पूर्ण,
	[STPMIC1_VREF_DDR] = अणु
		.desc = REG_VREF_DDR(VREF_DDR, vref_ddr),
		.mask_reset_reg = LDOS_MASK_RESET_CR,
		.mask_reset_mask = BIT(6),
	पूर्ण,
	[STPMIC1_BOOST] = अणु
		.desc = REG_BOOST(BOOST, boost),
		.icc_reg = BUCKS_ICCTO_CR,
		.icc_mask = BIT(6),
	पूर्ण,
	[STPMIC1_VBUS_OTG] = अणु
		.desc = REG_VBUS_OTG(VBUS_OTG, pwr_sw1),
		.icc_reg = BUCKS_ICCTO_CR,
		.icc_mask = BIT(4),
	पूर्ण,
	[STPMIC1_SW_OUT] = अणु
		.desc = REG_SW_OUT(SW_OUT, pwr_sw2),
		.icc_reg = BUCKS_ICCTO_CR,
		.icc_mask = BIT(5),
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक stpmic1_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल STPMIC1_BUCK_MODE_NORMAL:
		वापस REGULATOR_MODE_NORMAL;
	हाल STPMIC1_BUCK_MODE_LP:
		वापस REGULATOR_MODE_STANDBY;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक stpmic1_get_mode(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक value;
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);

	regmap_पढ़ो(regmap, rdev->desc->enable_reg, &value);

	अगर (value & STPMIC1_BUCK_MODE_LP)
		वापस REGULATOR_MODE_STANDBY;

	वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक stpmic1_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक value;
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		value = STPMIC1_BUCK_MODE_NORMAL;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		value = STPMIC1_BUCK_MODE_LP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(regmap, rdev->desc->enable_reg,
				  STPMIC1_BUCK_MODE_LP, value);
पूर्ण

अटल पूर्णांक stpmic1_set_icc(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा stpmic1_regulator_cfg *cfg = rdev_get_drvdata(rdev);
	काष्ठा regmap *regmap = rdev_get_regmap(rdev);

	/* enable चयन off in हाल of over current */
	वापस regmap_update_bits(regmap, cfg->icc_reg, cfg->icc_mask,
				  cfg->icc_mask);
पूर्ण

अटल irqवापस_t stpmic1_curlim_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा regulator_dev *rdev = (काष्ठा regulator_dev *)data;

	/* Send an overcurrent notअगरication */
	regulator_notअगरier_call_chain(rdev,
				      REGULATOR_EVENT_OVER_CURRENT,
				      शून्य);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा MATCH(_name, _id) \
	[STPMIC1_##_id] = अणु \
		.name = #_name, \
		.desc = &stpmic1_regulator_cfgs[STPMIC1_##_id].desc, \
	पूर्ण

अटल काष्ठा of_regulator_match stpmic1_matches[] = अणु
	MATCH(buck1, BUCK1),
	MATCH(buck2, BUCK2),
	MATCH(buck3, BUCK3),
	MATCH(buck4, BUCK4),
	MATCH(lकरो1, LDO1),
	MATCH(lकरो2, LDO2),
	MATCH(lकरो3, LDO3),
	MATCH(lकरो4, LDO4),
	MATCH(lकरो5, LDO5),
	MATCH(lकरो6, LDO6),
	MATCH(vref_ddr, VREF_DDR),
	MATCH(boost, BOOST),
	MATCH(pwr_sw1, VBUS_OTG),
	MATCH(pwr_sw2, SW_OUT),
पूर्ण;

अटल पूर्णांक stpmic1_regulator_रेजिस्टर(काष्ठा platक्रमm_device *pdev, पूर्णांक id,
				      काष्ठा of_regulator_match *match,
				      स्थिर काष्ठा stpmic1_regulator_cfg *cfg)
अणु
	काष्ठा stpmic1 *pmic_dev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणुपूर्ण;
	पूर्णांक ret = 0;
	पूर्णांक irq;

	config.dev = &pdev->dev;
	config.init_data = match->init_data;
	config.of_node = match->of_node;
	config.regmap = pmic_dev->regmap;
	config.driver_data = (व्योम *)cfg;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &cfg->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "failed to register %s regulator\n",
			cfg->desc.name);
		वापस PTR_ERR(rdev);
	पूर्ण

	/* set mask reset */
	अगर (of_get_property(config.of_node, "st,mask-reset", शून्य) &&
	    cfg->mask_reset_reg != 0) अणु
		ret = regmap_update_bits(pmic_dev->regmap,
					 cfg->mask_reset_reg,
					 cfg->mask_reset_mask,
					 cfg->mask_reset_mask);
		अगर (ret) अणु
			dev_err(&pdev->dev, "set mask reset failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* setup an irq handler क्रम over-current detection */
	irq = of_irq_get(config.of_node, 0);
	अगर (irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&pdev->dev,
						irq, शून्य,
						stpmic1_curlim_irq_handler,
						IRQF_ONESHOT | IRQF_SHARED,
						pdev->name, rdev);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Request IRQ failed\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक stpmic1_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, ret;

	ret = of_regulator_match(&pdev->dev, pdev->dev.of_node, stpmic1_matches,
				 ARRAY_SIZE(stpmic1_matches));
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"Error in PMIC regulator device tree node");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(stpmic1_regulator_cfgs); i++) अणु
		ret = stpmic1_regulator_रेजिस्टर(pdev, i, &stpmic1_matches[i],
						 &stpmic1_regulator_cfgs[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	dev_dbg(&pdev->dev, "stpmic1_regulator driver probed\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_pmic_regulator_match[] = अणु
	अणु .compatible = "st,stpmic1-regulators" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_pmic_regulator_match);

अटल काष्ठा platक्रमm_driver stpmic1_regulator_driver = अणु
	.driver = अणु
		.name = "stpmic1-regulator",
		.of_match_table = of_match_ptr(of_pmic_regulator_match),
	पूर्ण,
	.probe = stpmic1_regulator_probe,
पूर्ण;

module_platक्रमm_driver(stpmic1_regulator_driver);

MODULE_DESCRIPTION("STPMIC1 PMIC voltage regulator driver");
MODULE_AUTHOR("Pascal Paillet <p.paillet@st.com>");
MODULE_LICENSE("GPL v2");
