<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Voltage regulator support क्रम AMS AS3722 PMIC
 *
 * Copyright (C) 2013 ams
 *
 * Author: Florian Lobmaier <florian.lobmaier@ams.com>
 * Author: Laxman Dewangan <ldewangan@nvidia.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mfd/as3722.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/slab.h>

/* Regulator IDs */
क्रमागत as3722_regulators_id अणु
	AS3722_REGULATOR_ID_SD0,
	AS3722_REGULATOR_ID_SD1,
	AS3722_REGULATOR_ID_SD2,
	AS3722_REGULATOR_ID_SD3,
	AS3722_REGULATOR_ID_SD4,
	AS3722_REGULATOR_ID_SD5,
	AS3722_REGULATOR_ID_SD6,
	AS3722_REGULATOR_ID_LDO0,
	AS3722_REGULATOR_ID_LDO1,
	AS3722_REGULATOR_ID_LDO2,
	AS3722_REGULATOR_ID_LDO3,
	AS3722_REGULATOR_ID_LDO4,
	AS3722_REGULATOR_ID_LDO5,
	AS3722_REGULATOR_ID_LDO6,
	AS3722_REGULATOR_ID_LDO7,
	AS3722_REGULATOR_ID_LDO9,
	AS3722_REGULATOR_ID_LDO10,
	AS3722_REGULATOR_ID_LDO11,
	AS3722_REGULATOR_ID_MAX,
पूर्ण;

काष्ठा as3722_रेजिस्टर_mapping अणु
	u8 regulator_id;
	स्थिर अक्षर *name;
	स्थिर अक्षर *sname;
	u8 vsel_reg;
	u8 vsel_mask;
	पूर्णांक n_voltages;
	u32 enable_reg;
	u8 enable_mask;
	u32 control_reg;
	u8 mode_mask;
	u32 sleep_ctrl_reg;
	u8 sleep_ctrl_mask;
पूर्ण;

काष्ठा as3722_regulator_config_data अणु
	काष्ठा regulator_init_data *reg_init;
	bool enable_tracking;
	पूर्णांक ext_control;
पूर्ण;

काष्ठा as3722_regulators अणु
	काष्ठा device *dev;
	काष्ठा as3722 *as3722;
	काष्ठा regulator_desc desc[AS3722_REGULATOR_ID_MAX];
	काष्ठा as3722_regulator_config_data
			reg_config_data[AS3722_REGULATOR_ID_MAX];
पूर्ण;

अटल स्थिर काष्ठा as3722_रेजिस्टर_mapping as3722_reg_lookup[] = अणु
	अणु
		.regulator_id = AS3722_REGULATOR_ID_SD0,
		.name = "as3722-sd0",
		.vsel_reg = AS3722_SD0_VOLTAGE_REG,
		.vsel_mask = AS3722_SD_VSEL_MASK,
		.enable_reg = AS3722_SD_CONTROL_REG,
		.enable_mask = AS3722_SDn_CTRL(0),
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL1_REG,
		.sleep_ctrl_mask = AS3722_SD0_EXT_ENABLE_MASK,
		.control_reg = AS3722_SD0_CONTROL_REG,
		.mode_mask = AS3722_SD0_MODE_FAST,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_SD1,
		.name = "as3722-sd1",
		.vsel_reg = AS3722_SD1_VOLTAGE_REG,
		.vsel_mask = AS3722_SD_VSEL_MASK,
		.enable_reg = AS3722_SD_CONTROL_REG,
		.enable_mask = AS3722_SDn_CTRL(1),
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL1_REG,
		.sleep_ctrl_mask = AS3722_SD1_EXT_ENABLE_MASK,
		.control_reg = AS3722_SD1_CONTROL_REG,
		.mode_mask = AS3722_SD1_MODE_FAST,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_SD2,
		.name = "as3722-sd2",
		.sname = "vsup-sd2",
		.vsel_reg = AS3722_SD2_VOLTAGE_REG,
		.vsel_mask = AS3722_SD_VSEL_MASK,
		.enable_reg = AS3722_SD_CONTROL_REG,
		.enable_mask = AS3722_SDn_CTRL(2),
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL1_REG,
		.sleep_ctrl_mask = AS3722_SD2_EXT_ENABLE_MASK,
		.control_reg = AS3722_SD23_CONTROL_REG,
		.mode_mask = AS3722_SD2_MODE_FAST,
		.n_voltages = AS3722_SD2_VSEL_MAX + 1,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_SD3,
		.name = "as3722-sd3",
		.sname = "vsup-sd3",
		.vsel_reg = AS3722_SD3_VOLTAGE_REG,
		.vsel_mask = AS3722_SD_VSEL_MASK,
		.enable_reg = AS3722_SD_CONTROL_REG,
		.enable_mask = AS3722_SDn_CTRL(3),
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL1_REG,
		.sleep_ctrl_mask = AS3722_SD3_EXT_ENABLE_MASK,
		.control_reg = AS3722_SD23_CONTROL_REG,
		.mode_mask = AS3722_SD3_MODE_FAST,
		.n_voltages = AS3722_SD2_VSEL_MAX + 1,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_SD4,
		.name = "as3722-sd4",
		.sname = "vsup-sd4",
		.vsel_reg = AS3722_SD4_VOLTAGE_REG,
		.vsel_mask = AS3722_SD_VSEL_MASK,
		.enable_reg = AS3722_SD_CONTROL_REG,
		.enable_mask = AS3722_SDn_CTRL(4),
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL2_REG,
		.sleep_ctrl_mask = AS3722_SD4_EXT_ENABLE_MASK,
		.control_reg = AS3722_SD4_CONTROL_REG,
		.mode_mask = AS3722_SD4_MODE_FAST,
		.n_voltages = AS3722_SD2_VSEL_MAX + 1,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_SD5,
		.name = "as3722-sd5",
		.sname = "vsup-sd5",
		.vsel_reg = AS3722_SD5_VOLTAGE_REG,
		.vsel_mask = AS3722_SD_VSEL_MASK,
		.enable_reg = AS3722_SD_CONTROL_REG,
		.enable_mask = AS3722_SDn_CTRL(5),
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL2_REG,
		.sleep_ctrl_mask = AS3722_SD5_EXT_ENABLE_MASK,
		.control_reg = AS3722_SD5_CONTROL_REG,
		.mode_mask = AS3722_SD5_MODE_FAST,
		.n_voltages = AS3722_SD2_VSEL_MAX + 1,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_SD6,
		.name = "as3722-sd6",
		.vsel_reg = AS3722_SD6_VOLTAGE_REG,
		.vsel_mask = AS3722_SD_VSEL_MASK,
		.enable_reg = AS3722_SD_CONTROL_REG,
		.enable_mask = AS3722_SDn_CTRL(6),
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL2_REG,
		.sleep_ctrl_mask = AS3722_SD6_EXT_ENABLE_MASK,
		.control_reg = AS3722_SD6_CONTROL_REG,
		.mode_mask = AS3722_SD6_MODE_FAST,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO0,
		.name = "as3722-ldo0",
		.sname = "vin-ldo0",
		.vsel_reg = AS3722_LDO0_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO0_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO0_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL3_REG,
		.sleep_ctrl_mask = AS3722_LDO0_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO0_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO1,
		.name = "as3722-ldo1",
		.sname = "vin-ldo1-6",
		.vsel_reg = AS3722_LDO1_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO1_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL3_REG,
		.sleep_ctrl_mask = AS3722_LDO1_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO2,
		.name = "as3722-ldo2",
		.sname = "vin-ldo2-5-7",
		.vsel_reg = AS3722_LDO2_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO2_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL3_REG,
		.sleep_ctrl_mask = AS3722_LDO2_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO3,
		.name = "as3722-ldo3",
		.sname = "vin-ldo3-4",
		.vsel_reg = AS3722_LDO3_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO3_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO3_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL3_REG,
		.sleep_ctrl_mask = AS3722_LDO3_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO3_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO4,
		.name = "as3722-ldo4",
		.sname = "vin-ldo3-4",
		.vsel_reg = AS3722_LDO4_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO4_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL4_REG,
		.sleep_ctrl_mask = AS3722_LDO4_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO5,
		.name = "as3722-ldo5",
		.sname = "vin-ldo2-5-7",
		.vsel_reg = AS3722_LDO5_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO5_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL4_REG,
		.sleep_ctrl_mask = AS3722_LDO5_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO6,
		.name = "as3722-ldo6",
		.sname = "vin-ldo1-6",
		.vsel_reg = AS3722_LDO6_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO6_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL4_REG,
		.sleep_ctrl_mask = AS3722_LDO6_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO7,
		.name = "as3722-ldo7",
		.sname = "vin-ldo2-5-7",
		.vsel_reg = AS3722_LDO7_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL0_REG,
		.enable_mask = AS3722_LDO7_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL4_REG,
		.sleep_ctrl_mask = AS3722_LDO7_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO9,
		.name = "as3722-ldo9",
		.sname = "vin-ldo9-10",
		.vsel_reg = AS3722_LDO9_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL1_REG,
		.enable_mask = AS3722_LDO9_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL5_REG,
		.sleep_ctrl_mask = AS3722_LDO9_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO10,
		.name = "as3722-ldo10",
		.sname = "vin-ldo9-10",
		.vsel_reg = AS3722_LDO10_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL1_REG,
		.enable_mask = AS3722_LDO10_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL5_REG,
		.sleep_ctrl_mask = AS3722_LDO10_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
	अणु
		.regulator_id = AS3722_REGULATOR_ID_LDO11,
		.name = "as3722-ldo11",
		.sname = "vin-ldo11",
		.vsel_reg = AS3722_LDO11_VOLTAGE_REG,
		.vsel_mask = AS3722_LDO_VSEL_MASK,
		.enable_reg = AS3722_LDOCONTROL1_REG,
		.enable_mask = AS3722_LDO11_CTRL,
		.sleep_ctrl_reg = AS3722_ENABLE_CTRL5_REG,
		.sleep_ctrl_mask = AS3722_LDO11_EXT_ENABLE_MASK,
		.n_voltages = AS3722_LDO_NUM_VOLT,
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक as3722_lकरो_current[] = अणु 150000, 300000 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक as3722_sd016_current[] = अणु
	2500000, 3000000, 3500000
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_lकरो0_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_lकरो0_extcntrl_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
पूर्ण;

अटल पूर्णांक as3722_lकरो3_set_tracking_mode(काष्ठा as3722_regulators *as3722_reg,
		पूर्णांक id, u8 mode)
अणु
	काष्ठा as3722 *as3722 = as3722_reg->as3722;

	चयन (mode) अणु
	हाल AS3722_LDO3_MODE_PMOS:
	हाल AS3722_LDO3_MODE_PMOS_TRACKING:
	हाल AS3722_LDO3_MODE_NMOS:
	हाल AS3722_LDO3_MODE_SWITCH:
		वापस as3722_update_bits(as3722,
			as3722_reg_lookup[id].vsel_reg,
			AS3722_LDO3_MODE_MASK, mode);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक as3722_lकरो3_get_current_limit(काष्ठा regulator_dev *rdev)
अणु
	वापस 150000;
पूर्ण

अटल स्थिर काष्ठा regulator_ops as3722_lकरो3_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_current_limit = as3722_lकरो3_get_current_limit,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_lकरो3_extcntrl_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_current_limit = as3722_lकरो3_get_current_limit,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_lकरो6_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_bypass = regulator_get_bypass_regmap,
	.set_bypass = regulator_set_bypass_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_lकरो6_extcntrl_ops = अणु
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_bypass = regulator_get_bypass_regmap,
	.set_bypass = regulator_set_bypass_regmap,
पूर्ण;

अटल स्थिर काष्ठा linear_range as3722_lकरो_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x00, 0x00, 0),
	REGULATOR_LINEAR_RANGE(825000, 0x01, 0x24, 25000),
	REGULATOR_LINEAR_RANGE(1725000, 0x40, 0x7F, 25000),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_lकरो_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_lकरो_extcntrl_ops = अणु
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
पूर्ण;

अटल अचिन्हित पूर्णांक as3722_sd_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा as3722_regulators *as3722_regs = rdev_get_drvdata(rdev);
	काष्ठा as3722 *as3722 = as3722_regs->as3722;
	पूर्णांक id = rdev_get_id(rdev);
	u32 val;
	पूर्णांक ret;

	अगर (!as3722_reg_lookup[id].control_reg)
		वापस -ENOTSUPP;

	ret = as3722_पढ़ो(as3722, as3722_reg_lookup[id].control_reg, &val);
	अगर (ret < 0) अणु
		dev_err(as3722_regs->dev, "Reg 0x%02x read failed: %d\n",
			as3722_reg_lookup[id].control_reg, ret);
		वापस ret;
	पूर्ण

	अगर (val & as3722_reg_lookup[id].mode_mask)
		वापस REGULATOR_MODE_FAST;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक as3722_sd_set_mode(काष्ठा regulator_dev *rdev,
		अचिन्हित पूर्णांक mode)
अणु
	काष्ठा as3722_regulators *as3722_regs = rdev_get_drvdata(rdev);
	काष्ठा as3722 *as3722 = as3722_regs->as3722;
	u8 id = rdev_get_id(rdev);
	u8 val = 0;
	पूर्णांक ret;

	अगर (!as3722_reg_lookup[id].control_reg)
		वापस -दुस्फल;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		val = as3722_reg_lookup[id].mode_mask;
		fallthrough;
	हाल REGULATOR_MODE_NORMAL:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = as3722_update_bits(as3722, as3722_reg_lookup[id].control_reg,
			as3722_reg_lookup[id].mode_mask, val);
	अगर (ret < 0) अणु
		dev_err(as3722_regs->dev, "Reg 0x%02x update failed: %d\n",
			as3722_reg_lookup[id].control_reg, ret);
		वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool as3722_sd0_is_low_voltage(काष्ठा as3722_regulators *as3722_regs)
अणु
	पूर्णांक err;
	अचिन्हित val;

	err = as3722_पढ़ो(as3722_regs->as3722, AS3722_FUSE7_REG, &val);
	अगर (err < 0) अणु
		dev_err(as3722_regs->dev, "Reg 0x%02x read failed: %d\n",
			AS3722_FUSE7_REG, err);
		वापस false;
	पूर्ण
	अगर (val & AS3722_FUSE7_SD0_LOW_VOLTAGE)
		वापस true;
	वापस false;
पूर्ण

अटल स्थिर काष्ठा linear_range as3722_sd2345_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x00, 0x00, 0),
	REGULATOR_LINEAR_RANGE(612500, 0x01, 0x40, 12500),
	REGULATOR_LINEAR_RANGE(1425000, 0x41, 0x70, 25000),
	REGULATOR_LINEAR_RANGE(2650000, 0x71, 0x7F, 50000),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_sd016_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_sd016_extcntrl_ops = अणु
	.list_voltage = regulator_list_voltage_linear,
	.map_voltage = regulator_map_voltage_linear,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_current_limit = regulator_get_current_limit_regmap,
	.set_current_limit = regulator_set_current_limit_regmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_sd2345_ops = अणु
	.is_enabled = regulator_is_enabled_regmap,
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops as3722_sd2345_extcntrl_ops = अणु
	.list_voltage = regulator_list_voltage_linear_range,
	.map_voltage = regulator_map_voltage_linear_range,
	.set_voltage_sel = regulator_set_voltage_sel_regmap,
	.get_voltage_sel = regulator_get_voltage_sel_regmap,
	.get_mode = as3722_sd_get_mode,
	.set_mode = as3722_sd_set_mode,
पूर्ण;

अटल पूर्णांक as3722_extreg_init(काष्ठा as3722_regulators *as3722_regs, पूर्णांक id,
		पूर्णांक ext_pwr_ctrl)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	अगर ((ext_pwr_ctrl < AS3722_EXT_CONTROL_ENABLE1) ||
		(ext_pwr_ctrl > AS3722_EXT_CONTROL_ENABLE3))
		वापस -EINVAL;

	val =  ext_pwr_ctrl << (ffs(as3722_reg_lookup[id].sleep_ctrl_mask) - 1);
	ret = as3722_update_bits(as3722_regs->as3722,
			as3722_reg_lookup[id].sleep_ctrl_reg,
			as3722_reg_lookup[id].sleep_ctrl_mask, val);
	अगर (ret < 0)
		dev_err(as3722_regs->dev, "Reg 0x%02x update failed: %d\n",
			as3722_reg_lookup[id].sleep_ctrl_reg, ret);
	वापस ret;
पूर्ण

अटल काष्ठा of_regulator_match as3722_regulator_matches[] = अणु
	अणु .name = "sd0", पूर्ण,
	अणु .name = "sd1", पूर्ण,
	अणु .name = "sd2", पूर्ण,
	अणु .name = "sd3", पूर्ण,
	अणु .name = "sd4", पूर्ण,
	अणु .name = "sd5", पूर्ण,
	अणु .name = "sd6", पूर्ण,
	अणु .name = "ldo0", पूर्ण,
	अणु .name = "ldo1", पूर्ण,
	अणु .name = "ldo2", पूर्ण,
	अणु .name = "ldo3", पूर्ण,
	अणु .name = "ldo4", पूर्ण,
	अणु .name = "ldo5", पूर्ण,
	अणु .name = "ldo6", पूर्ण,
	अणु .name = "ldo7", पूर्ण,
	अणु .name = "ldo9", पूर्ण,
	अणु .name = "ldo10", पूर्ण,
	अणु .name = "ldo11", पूर्ण,
पूर्ण;

अटल पूर्णांक as3722_get_regulator_dt_data(काष्ठा platक्रमm_device *pdev,
		काष्ठा as3722_regulators *as3722_regs)
अणु
	काष्ठा device_node *np;
	काष्ठा as3722_regulator_config_data *reg_config;
	u32 prop;
	पूर्णांक id;
	पूर्णांक ret;

	np = of_get_child_by_name(pdev->dev.parent->of_node, "regulators");
	अगर (!np) अणु
		dev_err(&pdev->dev, "Device is not having regulators node\n");
		वापस -ENODEV;
	पूर्ण
	pdev->dev.of_node = np;

	ret = of_regulator_match(&pdev->dev, np, as3722_regulator_matches,
			ARRAY_SIZE(as3722_regulator_matches));
	of_node_put(np);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Parsing of regulator node failed: %d\n",
			ret);
		वापस ret;
	पूर्ण

	क्रम (id = 0; id < ARRAY_SIZE(as3722_regulator_matches); ++id) अणु
		काष्ठा device_node *reg_node;

		reg_config = &as3722_regs->reg_config_data[id];
		reg_config->reg_init = as3722_regulator_matches[id].init_data;
		reg_node = as3722_regulator_matches[id].of_node;

		अगर (!reg_config->reg_init || !reg_node)
			जारी;

		ret = of_property_पढ़ो_u32(reg_node, "ams,ext-control", &prop);
		अगर (!ret) अणु
			अगर (prop < 3)
				reg_config->ext_control = prop;
			अन्यथा
				dev_warn(&pdev->dev,
					"ext-control have invalid option: %u\n",
					prop);
		पूर्ण
		reg_config->enable_tracking =
			of_property_पढ़ो_bool(reg_node, "ams,enable-tracking");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक as3722_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा as3722 *as3722 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा as3722_regulators *as3722_regs;
	काष्ठा as3722_regulator_config_data *reg_config;
	काष्ठा regulator_dev *rdev;
	काष्ठा regulator_config config = अणु पूर्ण;
	स्थिर काष्ठा regulator_ops *ops;
	पूर्णांक id;
	पूर्णांक ret;

	as3722_regs = devm_kzalloc(&pdev->dev, माप(*as3722_regs),
				GFP_KERNEL);
	अगर (!as3722_regs)
		वापस -ENOMEM;

	as3722_regs->dev = &pdev->dev;
	as3722_regs->as3722 = as3722;
	platक्रमm_set_drvdata(pdev, as3722_regs);

	ret = as3722_get_regulator_dt_data(pdev, as3722_regs);
	अगर (ret < 0)
		वापस ret;

	config.dev = &pdev->dev;
	config.driver_data = as3722_regs;
	config.regmap = as3722->regmap;

	क्रम (id = 0; id < AS3722_REGULATOR_ID_MAX; id++) अणु
		काष्ठा regulator_desc *desc;

		desc = &as3722_regs->desc[id];
		reg_config = &as3722_regs->reg_config_data[id];

		desc->name = as3722_reg_lookup[id].name;
		desc->supply_name = as3722_reg_lookup[id].sname;
		desc->id = as3722_reg_lookup[id].regulator_id;
		desc->n_voltages = as3722_reg_lookup[id].n_voltages;
		desc->type = REGULATOR_VOLTAGE;
		desc->owner = THIS_MODULE;
		desc->enable_reg = as3722_reg_lookup[id].enable_reg;
		desc->enable_mask = as3722_reg_lookup[id].enable_mask;
		desc->vsel_reg = as3722_reg_lookup[id].vsel_reg;
		desc->vsel_mask = as3722_reg_lookup[id].vsel_mask;
		चयन (id) अणु
		हाल AS3722_REGULATOR_ID_LDO0:
			अगर (reg_config->ext_control)
				ops = &as3722_lकरो0_extcntrl_ops;
			अन्यथा
				ops = &as3722_lकरो0_ops;
			desc->min_uV = 825000;
			desc->uV_step = 25000;
			desc->linear_min_sel = 1;
			desc->enable_समय = 500;
			desc->curr_table = as3722_lकरो_current;
			desc->n_current_limits = ARRAY_SIZE(as3722_lकरो_current);
			desc->csel_reg = as3722_reg_lookup[id].vsel_reg;
			desc->csel_mask = AS3722_LDO_ILIMIT_MASK;
			अवरोध;
		हाल AS3722_REGULATOR_ID_LDO3:
			अगर (reg_config->ext_control)
				ops = &as3722_lकरो3_extcntrl_ops;
			अन्यथा
				ops = &as3722_lकरो3_ops;
			desc->min_uV = 620000;
			desc->uV_step = 20000;
			desc->linear_min_sel = 1;
			desc->enable_समय = 500;
			अगर (reg_config->enable_tracking) अणु
				ret = as3722_lकरो3_set_tracking_mode(as3722_regs,
					id, AS3722_LDO3_MODE_PMOS_TRACKING);
				अगर (ret < 0) अणु
					dev_err(&pdev->dev,
						"LDO3 tracking failed: %d\n",
						ret);
					वापस ret;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल AS3722_REGULATOR_ID_LDO6:
			अगर (reg_config->ext_control)
				ops = &as3722_lकरो6_extcntrl_ops;
			अन्यथा
				ops = &as3722_lकरो6_ops;
			desc->enable_समय = 500;
			desc->bypass_reg = AS3722_LDO6_VOLTAGE_REG;
			desc->bypass_mask = AS3722_LDO_VSEL_MASK;
			desc->bypass_val_on = AS3722_LDO6_VSEL_BYPASS;
			desc->bypass_val_off = AS3722_LDO6_VSEL_BYPASS;
			desc->linear_ranges = as3722_lकरो_ranges;
			desc->n_linear_ranges = ARRAY_SIZE(as3722_lकरो_ranges);
			desc->curr_table = as3722_lकरो_current;
			desc->n_current_limits = ARRAY_SIZE(as3722_lकरो_current);
			desc->csel_reg = as3722_reg_lookup[id].vsel_reg;
			desc->csel_mask = AS3722_LDO_ILIMIT_MASK;
			अवरोध;
		हाल AS3722_REGULATOR_ID_SD0:
		हाल AS3722_REGULATOR_ID_SD1:
		हाल AS3722_REGULATOR_ID_SD6:
			अगर (reg_config->ext_control)
				ops = &as3722_sd016_extcntrl_ops;
			अन्यथा
				ops = &as3722_sd016_ops;
			अगर (id == AS3722_REGULATOR_ID_SD0 &&
			    as3722_sd0_is_low_voltage(as3722_regs)) अणु
				as3722_regs->desc[id].n_voltages =
					AS3722_SD0_VSEL_LOW_VOL_MAX + 1;
				as3722_regs->desc[id].min_uV = 410000;
			पूर्ण अन्यथा अणु
				as3722_regs->desc[id].n_voltages =
					AS3722_SD0_VSEL_MAX + 1;
				as3722_regs->desc[id].min_uV = 610000;
			पूर्ण
			desc->uV_step = 10000;
			desc->linear_min_sel = 1;
			desc->enable_समय = 600;
			desc->curr_table = as3722_sd016_current;
			desc->n_current_limits =
				ARRAY_SIZE(as3722_sd016_current);
			अगर (id == AS3722_REGULATOR_ID_SD0) अणु
				desc->csel_reg = AS3722_OVCURRENT_REG;
				desc->csel_mask =
					AS3722_OVCURRENT_SD0_TRIP_MASK;
			पूर्ण अन्यथा अगर (id == AS3722_REGULATOR_ID_SD1) अणु
				desc->csel_reg = AS3722_OVCURRENT_REG;
				desc->csel_mask =
					AS3722_OVCURRENT_SD1_TRIP_MASK;
			पूर्ण अन्यथा अगर (id == AS3722_REGULATOR_ID_SD6) अणु
				desc->csel_reg = AS3722_OVCURRENT_DEB_REG;
				desc->csel_mask =
					AS3722_OVCURRENT_SD6_TRIP_MASK;
			पूर्ण
			अवरोध;
		हाल AS3722_REGULATOR_ID_SD2:
		हाल AS3722_REGULATOR_ID_SD3:
		हाल AS3722_REGULATOR_ID_SD4:
		हाल AS3722_REGULATOR_ID_SD5:
			अगर (reg_config->ext_control)
				ops = &as3722_sd2345_extcntrl_ops;
			अन्यथा
				ops = &as3722_sd2345_ops;
			desc->linear_ranges = as3722_sd2345_ranges;
			desc->n_linear_ranges =
					ARRAY_SIZE(as3722_sd2345_ranges);
			अवरोध;
		शेष:
			अगर (reg_config->ext_control)
				ops = &as3722_lकरो_extcntrl_ops;
			अन्यथा
				ops = &as3722_lकरो_ops;
			desc->enable_समय = 500;
			desc->linear_ranges = as3722_lकरो_ranges;
			desc->n_linear_ranges = ARRAY_SIZE(as3722_lकरो_ranges);
			desc->curr_table = as3722_lकरो_current;
			desc->n_current_limits = ARRAY_SIZE(as3722_lकरो_current);
			desc->csel_reg = as3722_reg_lookup[id].vsel_reg;
			desc->csel_mask = AS3722_LDO_ILIMIT_MASK;
			अवरोध;
		पूर्ण
		desc->ops = ops;
		config.init_data = reg_config->reg_init;
		config.of_node = as3722_regulator_matches[id].of_node;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(&pdev->dev, "regulator %d register failed %d\n",
				id, ret);
			वापस ret;
		पूर्ण

		अगर (reg_config->ext_control) अणु
			ret = regulator_enable_regmap(rdev);
			अगर (ret < 0) अणु
				dev_err(&pdev->dev,
					"Regulator %d enable failed: %d\n",
					id, ret);
				वापस ret;
			पूर्ण
			ret = as3722_extreg_init(as3722_regs, id,
					reg_config->ext_control);
			अगर (ret < 0) अणु
				dev_err(&pdev->dev,
					"AS3722 ext control failed: %d", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_as3722_regulator_match[] = अणु
	अणु .compatible = "ams,as3722-regulator", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_as3722_regulator_match);

अटल काष्ठा platक्रमm_driver as3722_regulator_driver = अणु
	.driver = अणु
		.name = "as3722-regulator",
		.of_match_table = of_as3722_regulator_match,
	पूर्ण,
	.probe = as3722_regulator_probe,
पूर्ण;

module_platक्रमm_driver(as3722_regulator_driver);

MODULE_ALIAS("platform:as3722-regulator");
MODULE_DESCRIPTION("AS3722 regulator driver");
MODULE_AUTHOR("Florian Lobmaier <florian.lobmaier@ams.com>");
MODULE_AUTHOR("Laxman Dewangan <ldewangan@nvidia.com>");
MODULE_LICENSE("GPL");
