<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * tps65910.c  --  TI tps65910
 *
 * Copyright 2010 Texas Instruments Inc.
 *
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 * Author: Jorge Eduarकरो Candelaria <jedu@slimlogic.co.uk>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/mfd/tps65910.h>
#समावेश <linux/regulator/of_regulator.h>

#घोषणा TPS65910_SUPPLY_STATE_ENABLED	0x1
#घोषणा EXT_SLEEP_CONTROL (TPS65910_SLEEP_CONTROL_EXT_INPUT_EN1 |	\
			TPS65910_SLEEP_CONTROL_EXT_INPUT_EN2 |		\
			TPS65910_SLEEP_CONTROL_EXT_INPUT_EN3 |		\
			TPS65911_SLEEP_CONTROL_EXT_INPUT_SLEEP)

/* supported VIO voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VIO_VSEL_table[] = अणु
	1500000, 1800000, 2500000, 3300000,
पूर्ण;

/* VSEL tables क्रम TPS65910 specअगरic LDOs and dcdc's */

/* supported VRTC voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VRTC_VSEL_table[] = अणु
	1800000,
पूर्ण;

/* supported VDD3 voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VDD3_VSEL_table[] = अणु
	5000000,
पूर्ण;

/* supported VDIG1 voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VDIG1_VSEL_table[] = अणु
	1200000, 1500000, 1800000, 2700000,
पूर्ण;

/* supported VDIG2 voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VDIG2_VSEL_table[] = अणु
	1000000, 1100000, 1200000, 1800000,
पूर्ण;

/* supported VPLL voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VPLL_VSEL_table[] = अणु
	1000000, 1100000, 1800000, 2500000,
पूर्ण;

/* supported VDAC voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VDAC_VSEL_table[] = अणु
	1800000, 2600000, 2800000, 2850000,
पूर्ण;

/* supported VAUX1 voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VAUX1_VSEL_table[] = अणु
	1800000, 2500000, 2800000, 2850000,
पूर्ण;

/* supported VAUX2 voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VAUX2_VSEL_table[] = अणु
	1800000, 2800000, 2900000, 3300000,
पूर्ण;

/* supported VAUX33 voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VAUX33_VSEL_table[] = अणु
	1800000, 2000000, 2800000, 3300000,
पूर्ण;

/* supported VMMC voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VMMC_VSEL_table[] = अणु
	1800000, 2800000, 3000000, 3300000,
पूर्ण;

/* supported BBCH voltages in microvolts */
अटल स्थिर अचिन्हित पूर्णांक VBB_VSEL_table[] = अणु
	3000000, 2520000, 3150000, 5000000,
पूर्ण;

काष्ठा tps_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *vin_name;
	u8 n_voltages;
	स्थिर अचिन्हित पूर्णांक *voltage_table;
	पूर्णांक enable_समय_us;
पूर्ण;

अटल काष्ठा tps_info tps65910_regs[] = अणु
	अणु
		.name = "vrtc",
		.vin_name = "vcc7",
		.n_voltages = ARRAY_SIZE(VRTC_VSEL_table),
		.voltage_table = VRTC_VSEL_table,
		.enable_समय_us = 2200,
	पूर्ण,
	अणु
		.name = "vio",
		.vin_name = "vccio",
		.n_voltages = ARRAY_SIZE(VIO_VSEL_table),
		.voltage_table = VIO_VSEL_table,
		.enable_समय_us = 350,
	पूर्ण,
	अणु
		.name = "vdd1",
		.vin_name = "vcc1",
		.enable_समय_us = 350,
	पूर्ण,
	अणु
		.name = "vdd2",
		.vin_name = "vcc2",
		.enable_समय_us = 350,
	पूर्ण,
	अणु
		.name = "vdd3",
		.n_voltages = ARRAY_SIZE(VDD3_VSEL_table),
		.voltage_table = VDD3_VSEL_table,
		.enable_समय_us = 200,
	पूर्ण,
	अणु
		.name = "vdig1",
		.vin_name = "vcc6",
		.n_voltages = ARRAY_SIZE(VDIG1_VSEL_table),
		.voltage_table = VDIG1_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vdig2",
		.vin_name = "vcc6",
		.n_voltages = ARRAY_SIZE(VDIG2_VSEL_table),
		.voltage_table = VDIG2_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vpll",
		.vin_name = "vcc5",
		.n_voltages = ARRAY_SIZE(VPLL_VSEL_table),
		.voltage_table = VPLL_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vdac",
		.vin_name = "vcc5",
		.n_voltages = ARRAY_SIZE(VDAC_VSEL_table),
		.voltage_table = VDAC_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vaux1",
		.vin_name = "vcc4",
		.n_voltages = ARRAY_SIZE(VAUX1_VSEL_table),
		.voltage_table = VAUX1_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vaux2",
		.vin_name = "vcc4",
		.n_voltages = ARRAY_SIZE(VAUX2_VSEL_table),
		.voltage_table = VAUX2_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vaux33",
		.vin_name = "vcc3",
		.n_voltages = ARRAY_SIZE(VAUX33_VSEL_table),
		.voltage_table = VAUX33_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vmmc",
		.vin_name = "vcc3",
		.n_voltages = ARRAY_SIZE(VMMC_VSEL_table),
		.voltage_table = VMMC_VSEL_table,
		.enable_समय_us = 100,
	पूर्ण,
	अणु
		.name = "vbb",
		.vin_name = "vcc7",
		.n_voltages = ARRAY_SIZE(VBB_VSEL_table),
		.voltage_table = VBB_VSEL_table,
	पूर्ण,
पूर्ण;

अटल काष्ठा tps_info tps65911_regs[] = अणु
	अणु
		.name = "vrtc",
		.vin_name = "vcc7",
		.enable_समय_us = 2200,
	पूर्ण,
	अणु
		.name = "vio",
		.vin_name = "vccio",
		.n_voltages = ARRAY_SIZE(VIO_VSEL_table),
		.voltage_table = VIO_VSEL_table,
		.enable_समय_us = 350,
	पूर्ण,
	अणु
		.name = "vdd1",
		.vin_name = "vcc1",
		.n_voltages = 0x4C,
		.enable_समय_us = 350,
	पूर्ण,
	अणु
		.name = "vdd2",
		.vin_name = "vcc2",
		.n_voltages = 0x4C,
		.enable_समय_us = 350,
	पूर्ण,
	अणु
		.name = "vddctrl",
		.n_voltages = 0x44,
		.enable_समय_us = 900,
	पूर्ण,
	अणु
		.name = "ldo1",
		.vin_name = "vcc6",
		.n_voltages = 0x33,
		.enable_समय_us = 420,
	पूर्ण,
	अणु
		.name = "ldo2",
		.vin_name = "vcc6",
		.n_voltages = 0x33,
		.enable_समय_us = 420,
	पूर्ण,
	अणु
		.name = "ldo3",
		.vin_name = "vcc5",
		.n_voltages = 0x1A,
		.enable_समय_us = 230,
	पूर्ण,
	अणु
		.name = "ldo4",
		.vin_name = "vcc5",
		.n_voltages = 0x33,
		.enable_समय_us = 230,
	पूर्ण,
	अणु
		.name = "ldo5",
		.vin_name = "vcc4",
		.n_voltages = 0x1A,
		.enable_समय_us = 230,
	पूर्ण,
	अणु
		.name = "ldo6",
		.vin_name = "vcc3",
		.n_voltages = 0x1A,
		.enable_समय_us = 230,
	पूर्ण,
	अणु
		.name = "ldo7",
		.vin_name = "vcc3",
		.n_voltages = 0x1A,
		.enable_समय_us = 230,
	पूर्ण,
	अणु
		.name = "ldo8",
		.vin_name = "vcc3",
		.n_voltages = 0x1A,
		.enable_समय_us = 230,
	पूर्ण,
पूर्ण;

#घोषणा EXT_CONTROL_REG_BITS(id, regs_offs, bits) (((regs_offs) << 8) | (bits))
अटल अचिन्हित पूर्णांक tps65910_ext_sleep_control[] = अणु
	0,
	EXT_CONTROL_REG_BITS(VIO,    1, 0),
	EXT_CONTROL_REG_BITS(VDD1,   1, 1),
	EXT_CONTROL_REG_BITS(VDD2,   1, 2),
	EXT_CONTROL_REG_BITS(VDD3,   1, 3),
	EXT_CONTROL_REG_BITS(VDIG1,  0, 1),
	EXT_CONTROL_REG_BITS(VDIG2,  0, 2),
	EXT_CONTROL_REG_BITS(VPLL,   0, 6),
	EXT_CONTROL_REG_BITS(VDAC,   0, 7),
	EXT_CONTROL_REG_BITS(VAUX1,  0, 3),
	EXT_CONTROL_REG_BITS(VAUX2,  0, 4),
	EXT_CONTROL_REG_BITS(VAUX33, 0, 5),
	EXT_CONTROL_REG_BITS(VMMC,   0, 0),
पूर्ण;

अटल अचिन्हित पूर्णांक tps65911_ext_sleep_control[] = अणु
	0,
	EXT_CONTROL_REG_BITS(VIO,     1, 0),
	EXT_CONTROL_REG_BITS(VDD1,    1, 1),
	EXT_CONTROL_REG_BITS(VDD2,    1, 2),
	EXT_CONTROL_REG_BITS(VDDCTRL, 1, 3),
	EXT_CONTROL_REG_BITS(LDO1,    0, 1),
	EXT_CONTROL_REG_BITS(LDO2,    0, 2),
	EXT_CONTROL_REG_BITS(LDO3,    0, 7),
	EXT_CONTROL_REG_BITS(LDO4,    0, 6),
	EXT_CONTROL_REG_BITS(LDO5,    0, 3),
	EXT_CONTROL_REG_BITS(LDO6,    0, 0),
	EXT_CONTROL_REG_BITS(LDO7,    0, 5),
	EXT_CONTROL_REG_BITS(LDO8,    0, 4),
पूर्ण;

काष्ठा tps65910_reg अणु
	काष्ठा regulator_desc *desc;
	काष्ठा tps65910 *mfd;
	काष्ठा regulator_dev **rdev;
	काष्ठा tps_info **info;
	पूर्णांक num_regulators;
	पूर्णांक mode;
	पूर्णांक  (*get_ctrl_reg)(पूर्णांक);
	अचिन्हित पूर्णांक *ext_sleep_control;
	अचिन्हित पूर्णांक board_ext_control[TPS65910_NUM_REGS];
पूर्ण;

अटल पूर्णांक tps65910_get_ctrl_रेजिस्टर(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल TPS65910_REG_VRTC:
		वापस TPS65910_VRTC;
	हाल TPS65910_REG_VIO:
		वापस TPS65910_VIO;
	हाल TPS65910_REG_VDD1:
		वापस TPS65910_VDD1;
	हाल TPS65910_REG_VDD2:
		वापस TPS65910_VDD2;
	हाल TPS65910_REG_VDD3:
		वापस TPS65910_VDD3;
	हाल TPS65910_REG_VDIG1:
		वापस TPS65910_VDIG1;
	हाल TPS65910_REG_VDIG2:
		वापस TPS65910_VDIG2;
	हाल TPS65910_REG_VPLL:
		वापस TPS65910_VPLL;
	हाल TPS65910_REG_VDAC:
		वापस TPS65910_VDAC;
	हाल TPS65910_REG_VAUX1:
		वापस TPS65910_VAUX1;
	हाल TPS65910_REG_VAUX2:
		वापस TPS65910_VAUX2;
	हाल TPS65910_REG_VAUX33:
		वापस TPS65910_VAUX33;
	हाल TPS65910_REG_VMMC:
		वापस TPS65910_VMMC;
	हाल TPS65910_REG_VBB:
		वापस TPS65910_BBCH;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tps65911_get_ctrl_रेजिस्टर(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल TPS65910_REG_VRTC:
		वापस TPS65910_VRTC;
	हाल TPS65910_REG_VIO:
		वापस TPS65910_VIO;
	हाल TPS65910_REG_VDD1:
		वापस TPS65910_VDD1;
	हाल TPS65910_REG_VDD2:
		वापस TPS65910_VDD2;
	हाल TPS65911_REG_VDDCTRL:
		वापस TPS65911_VDDCTRL;
	हाल TPS65911_REG_LDO1:
		वापस TPS65911_LDO1;
	हाल TPS65911_REG_LDO2:
		वापस TPS65911_LDO2;
	हाल TPS65911_REG_LDO3:
		वापस TPS65911_LDO3;
	हाल TPS65911_REG_LDO4:
		वापस TPS65911_LDO4;
	हाल TPS65911_REG_LDO5:
		वापस TPS65911_LDO5;
	हाल TPS65911_REG_LDO6:
		वापस TPS65911_LDO6;
	हाल TPS65911_REG_LDO7:
		वापस TPS65911_LDO7;
	हाल TPS65911_REG_LDO8:
		वापस TPS65911_LDO8;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक tps65910_set_mode(काष्ठा regulator_dev *dev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा tps65910_reg *pmic = rdev_get_drvdata(dev);
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक reg, id = rdev_get_id(dev);

	reg = pmic->get_ctrl_reg(id);
	अगर (reg < 0)
		वापस reg;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		वापस regmap_update_bits(regmap, reg,
					  LDO_ST_MODE_BIT | LDO_ST_ON_BIT,
					  LDO_ST_ON_BIT);
	हाल REGULATOR_MODE_IDLE:
		वापस regmap_set_bits(regmap, reg,
				       LDO_ST_ON_BIT | LDO_ST_MODE_BIT);
	हाल REGULATOR_MODE_STANDBY:
		वापस regmap_clear_bits(regmap, reg, LDO_ST_ON_BIT);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक tps65910_get_mode(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65910_reg *pmic = rdev_get_drvdata(dev);
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक ret, reg, value, id = rdev_get_id(dev);

	reg = pmic->get_ctrl_reg(id);
	अगर (reg < 0)
		वापस reg;

	ret = regmap_पढ़ो(regmap, reg, &value);
	अगर (ret < 0)
		वापस ret;

	अगर (!(value & LDO_ST_ON_BIT))
		वापस REGULATOR_MODE_STANDBY;
	अन्यथा अगर (value & LDO_ST_MODE_BIT)
		वापस REGULATOR_MODE_IDLE;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक tps65910_get_voltage_dcdc_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक ret, id = rdev_get_id(dev);
	पूर्णांक opvsel = 0, srvsel = 0, vselmax = 0, mult = 0, sr = 0;

	चयन (id) अणु
	हाल TPS65910_REG_VDD1:
		ret = regmap_पढ़ो(regmap, TPS65910_VDD1_OP, &opvsel);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, TPS65910_VDD1, &mult);
		अगर (ret < 0)
			वापस ret;
		mult = (mult & VDD1_VGAIN_SEL_MASK) >> VDD1_VGAIN_SEL_SHIFT;
		ret = regmap_पढ़ो(regmap, TPS65910_VDD1_SR, &srvsel);
		अगर (ret < 0)
			वापस ret;
		sr = opvsel & VDD1_OP_CMD_MASK;
		opvsel &= VDD1_OP_SEL_MASK;
		srvsel &= VDD1_SR_SEL_MASK;
		vselmax = 75;
		अवरोध;
	हाल TPS65910_REG_VDD2:
		ret = regmap_पढ़ो(regmap, TPS65910_VDD2_OP, &opvsel);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, TPS65910_VDD2, &mult);
		अगर (ret < 0)
			वापस ret;
		mult = (mult & VDD2_VGAIN_SEL_MASK) >> VDD2_VGAIN_SEL_SHIFT;
		ret = regmap_पढ़ो(regmap, TPS65910_VDD2_SR, &srvsel);
		अगर (ret < 0)
			वापस ret;
		sr = opvsel & VDD2_OP_CMD_MASK;
		opvsel &= VDD2_OP_SEL_MASK;
		srvsel &= VDD2_SR_SEL_MASK;
		vselmax = 75;
		अवरोध;
	हाल TPS65911_REG_VDDCTRL:
		ret = regmap_पढ़ो(regmap, TPS65911_VDDCTRL_OP, &opvsel);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(regmap, TPS65911_VDDCTRL_SR, &srvsel);
		अगर (ret < 0)
			वापस ret;
		sr = opvsel & VDDCTRL_OP_CMD_MASK;
		opvsel &= VDDCTRL_OP_SEL_MASK;
		srvsel &= VDDCTRL_SR_SEL_MASK;
		vselmax = 64;
		अवरोध;
	पूर्ण

	/* multiplier 0 == 1 but 2,3 normal */
	अगर (!mult)
		mult = 1;

	अगर (sr) अणु
		/* normalise to valid range */
		अगर (srvsel < 3)
			srvsel = 3;
		अगर (srvsel > vselmax)
			srvsel = vselmax;
		वापस srvsel - 3;
	पूर्ण अन्यथा अणु

		/* normalise to valid range*/
		अगर (opvsel < 3)
			opvsel = 3;
		अगर (opvsel > vselmax)
			opvsel = vselmax;
		वापस opvsel - 3;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tps65910_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65910_reg *pmic = rdev_get_drvdata(dev);
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक ret, reg, value, id = rdev_get_id(dev);

	reg = pmic->get_ctrl_reg(id);
	अगर (reg < 0)
		वापस reg;

	ret = regmap_पढ़ो(regmap, reg, &value);
	अगर (ret < 0)
		वापस ret;

	चयन (id) अणु
	हाल TPS65910_REG_VIO:
	हाल TPS65910_REG_VDIG1:
	हाल TPS65910_REG_VDIG2:
	हाल TPS65910_REG_VPLL:
	हाल TPS65910_REG_VDAC:
	हाल TPS65910_REG_VAUX1:
	हाल TPS65910_REG_VAUX2:
	हाल TPS65910_REG_VAUX33:
	हाल TPS65910_REG_VMMC:
		value &= LDO_SEL_MASK;
		value >>= LDO_SEL_SHIFT;
		अवरोध;
	हाल TPS65910_REG_VBB:
		value &= BBCH_BBSEL_MASK;
		value >>= BBCH_BBSEL_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक tps65910_get_voltage_vdd3(काष्ठा regulator_dev *dev)
अणु
	वापस dev->desc->volt_table[0];
पूर्ण

अटल पूर्णांक tps65911_get_voltage_sel(काष्ठा regulator_dev *dev)
अणु
	काष्ठा tps65910_reg *pmic = rdev_get_drvdata(dev);
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक ret, id = rdev_get_id(dev);
	अचिन्हित पूर्णांक value, reg;

	reg = pmic->get_ctrl_reg(id);

	ret = regmap_पढ़ो(regmap, reg, &value);
	अगर (ret < 0)
		वापस ret;

	चयन (id) अणु
	हाल TPS65911_REG_LDO1:
	हाल TPS65911_REG_LDO2:
	हाल TPS65911_REG_LDO4:
		value &= LDO1_SEL_MASK;
		value >>= LDO_SEL_SHIFT;
		अवरोध;
	हाल TPS65911_REG_LDO3:
	हाल TPS65911_REG_LDO5:
	हाल TPS65911_REG_LDO6:
	हाल TPS65911_REG_LDO7:
	हाल TPS65911_REG_LDO8:
		value &= LDO3_SEL_MASK;
		value >>= LDO_SEL_SHIFT;
		अवरोध;
	हाल TPS65910_REG_VIO:
		value &= LDO_SEL_MASK;
		value >>= LDO_SEL_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस value;
पूर्ण

अटल पूर्णांक tps65910_set_voltage_dcdc_sel(काष्ठा regulator_dev *dev,
					 अचिन्हित selector)
अणु
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक id = rdev_get_id(dev), vsel;
	पूर्णांक dcdc_mult = 0;

	चयन (id) अणु
	हाल TPS65910_REG_VDD1:
		dcdc_mult = (selector / VDD1_2_NUM_VOLT_FINE) + 1;
		अगर (dcdc_mult == 1)
			dcdc_mult--;
		vsel = (selector % VDD1_2_NUM_VOLT_FINE) + 3;

		regmap_update_bits(regmap, TPS65910_VDD1, VDD1_VGAIN_SEL_MASK,
				   dcdc_mult << VDD1_VGAIN_SEL_SHIFT);
		regmap_ग_लिखो(regmap, TPS65910_VDD1_OP, vsel);
		अवरोध;
	हाल TPS65910_REG_VDD2:
		dcdc_mult = (selector / VDD1_2_NUM_VOLT_FINE) + 1;
		अगर (dcdc_mult == 1)
			dcdc_mult--;
		vsel = (selector % VDD1_2_NUM_VOLT_FINE) + 3;

		regmap_update_bits(regmap, TPS65910_VDD2, VDD1_VGAIN_SEL_MASK,
				   dcdc_mult << VDD2_VGAIN_SEL_SHIFT);
		regmap_ग_लिखो(regmap, TPS65910_VDD2_OP, vsel);
		अवरोध;
	हाल TPS65911_REG_VDDCTRL:
		vsel = selector + 3;
		regmap_ग_लिखो(regmap, TPS65911_VDDCTRL_OP, vsel);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65910_set_voltage_sel(काष्ठा regulator_dev *dev,
				    अचिन्हित selector)
अणु
	काष्ठा tps65910_reg *pmic = rdev_get_drvdata(dev);
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक reg, id = rdev_get_id(dev);

	reg = pmic->get_ctrl_reg(id);
	अगर (reg < 0)
		वापस reg;

	चयन (id) अणु
	हाल TPS65910_REG_VIO:
	हाल TPS65910_REG_VDIG1:
	हाल TPS65910_REG_VDIG2:
	हाल TPS65910_REG_VPLL:
	हाल TPS65910_REG_VDAC:
	हाल TPS65910_REG_VAUX1:
	हाल TPS65910_REG_VAUX2:
	हाल TPS65910_REG_VAUX33:
	हाल TPS65910_REG_VMMC:
		वापस regmap_update_bits(regmap, reg, LDO_SEL_MASK,
					  selector << LDO_SEL_SHIFT);
	हाल TPS65910_REG_VBB:
		वापस regmap_update_bits(regmap, reg, BBCH_BBSEL_MASK,
					  selector << BBCH_BBSEL_SHIFT);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक tps65911_set_voltage_sel(काष्ठा regulator_dev *dev,
				    अचिन्हित selector)
अणु
	काष्ठा tps65910_reg *pmic = rdev_get_drvdata(dev);
	काष्ठा regmap *regmap = rdev_get_regmap(dev);
	पूर्णांक reg, id = rdev_get_id(dev);

	reg = pmic->get_ctrl_reg(id);
	अगर (reg < 0)
		वापस reg;

	चयन (id) अणु
	हाल TPS65911_REG_LDO1:
	हाल TPS65911_REG_LDO2:
	हाल TPS65911_REG_LDO4:
		वापस regmap_update_bits(regmap, reg, LDO1_SEL_MASK,
					  selector << LDO_SEL_SHIFT);
	हाल TPS65911_REG_LDO3:
	हाल TPS65911_REG_LDO5:
	हाल TPS65911_REG_LDO6:
	हाल TPS65911_REG_LDO7:
	हाल TPS65911_REG_LDO8:
		वापस regmap_update_bits(regmap, reg, LDO3_SEL_MASK,
					  selector << LDO_SEL_SHIFT);
	हाल TPS65910_REG_VIO:
		वापस regmap_update_bits(regmap, reg, LDO_SEL_MASK,
					  selector << LDO_SEL_SHIFT);
	हाल TPS65910_REG_VBB:
		वापस regmap_update_bits(regmap, reg, BBCH_BBSEL_MASK,
					  selector << BBCH_BBSEL_SHIFT);
	पूर्ण

	वापस -EINVAL;
पूर्ण


अटल पूर्णांक tps65910_list_voltage_dcdc(काष्ठा regulator_dev *dev,
					अचिन्हित selector)
अणु
	पूर्णांक volt, mult = 1, id = rdev_get_id(dev);

	चयन (id) अणु
	हाल TPS65910_REG_VDD1:
	हाल TPS65910_REG_VDD2:
		mult = (selector / VDD1_2_NUM_VOLT_FINE) + 1;
		volt = VDD1_2_MIN_VOLT +
			(selector % VDD1_2_NUM_VOLT_FINE) * VDD1_2_OFFSET;
		अवरोध;
	हाल TPS65911_REG_VDDCTRL:
		volt = VDDCTRL_MIN_VOLT + (selector * VDDCTRL_OFFSET);
		अवरोध;
	शेष:
		BUG();
		वापस -EINVAL;
	पूर्ण

	वापस  volt * 100 * mult;
पूर्ण

अटल पूर्णांक tps65911_list_voltage(काष्ठा regulator_dev *dev, अचिन्हित selector)
अणु
	काष्ठा tps65910_reg *pmic = rdev_get_drvdata(dev);
	पूर्णांक step_mv = 0, id = rdev_get_id(dev);

	चयन (id) अणु
	हाल TPS65911_REG_LDO1:
	हाल TPS65911_REG_LDO2:
	हाल TPS65911_REG_LDO4:
		/* The first 5 values of the selector correspond to 1V */
		अगर (selector < 5)
			selector = 0;
		अन्यथा
			selector -= 4;

		step_mv = 50;
		अवरोध;
	हाल TPS65911_REG_LDO3:
	हाल TPS65911_REG_LDO5:
	हाल TPS65911_REG_LDO6:
	हाल TPS65911_REG_LDO7:
	हाल TPS65911_REG_LDO8:
		/* The first 3 values of the selector correspond to 1V */
		अगर (selector < 3)
			selector = 0;
		अन्यथा
			selector -= 2;

		step_mv = 100;
		अवरोध;
	हाल TPS65910_REG_VIO:
		वापस pmic->info[id]->voltage_table[selector];
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस (LDO_MIN_VOLT + selector * step_mv) * 1000;
पूर्ण

/* Regulator ops (except VRTC) */
अटल स्थिर काष्ठा regulator_ops tps65910_ops_dcdc = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= tps65910_set_mode,
	.get_mode		= tps65910_get_mode,
	.get_voltage_sel	= tps65910_get_voltage_dcdc_sel,
	.set_voltage_sel	= tps65910_set_voltage_dcdc_sel,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.list_voltage		= tps65910_list_voltage_dcdc,
	.map_voltage		= regulator_map_voltage_ascend,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65910_ops_vdd3 = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= tps65910_set_mode,
	.get_mode		= tps65910_get_mode,
	.get_voltage		= tps65910_get_voltage_vdd3,
	.list_voltage		= regulator_list_voltage_table,
	.map_voltage		= regulator_map_voltage_ascend,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65910_ops_vbb = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= tps65910_set_mode,
	.get_mode		= tps65910_get_mode,
	.get_voltage_sel	= tps65910_get_voltage_sel,
	.set_voltage_sel	= tps65910_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_table,
	.map_voltage		= regulator_map_voltage_iterate,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65910_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= tps65910_set_mode,
	.get_mode		= tps65910_get_mode,
	.get_voltage_sel	= tps65910_get_voltage_sel,
	.set_voltage_sel	= tps65910_set_voltage_sel,
	.list_voltage		= regulator_list_voltage_table,
	.map_voltage		= regulator_map_voltage_ascend,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65911_ops = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= tps65910_set_mode,
	.get_mode		= tps65910_get_mode,
	.get_voltage_sel	= tps65911_get_voltage_sel,
	.set_voltage_sel	= tps65911_set_voltage_sel,
	.list_voltage		= tps65911_list_voltage,
	.map_voltage		= regulator_map_voltage_ascend,
पूर्ण;

अटल पूर्णांक tps65910_set_ext_sleep_config(काष्ठा tps65910_reg *pmic,
		पूर्णांक id, पूर्णांक ext_sleep_config)
अणु
	काष्ठा tps65910 *mfd = pmic->mfd;
	u8 regoffs = (pmic->ext_sleep_control[id] >> 8) & 0xFF;
	u8 bit_pos = (1 << pmic->ext_sleep_control[id] & 0xFF);
	पूर्णांक ret;

	/*
	 * Regulator can not be control from multiple बाह्यal input EN1, EN2
	 * and EN3 together.
	 */
	अगर (ext_sleep_config & EXT_SLEEP_CONTROL) अणु
		पूर्णांक en_count;
		en_count = ((ext_sleep_config &
				TPS65910_SLEEP_CONTROL_EXT_INPUT_EN1) != 0);
		en_count += ((ext_sleep_config &
				TPS65910_SLEEP_CONTROL_EXT_INPUT_EN2) != 0);
		en_count += ((ext_sleep_config &
				TPS65910_SLEEP_CONTROL_EXT_INPUT_EN3) != 0);
		en_count += ((ext_sleep_config &
				TPS65911_SLEEP_CONTROL_EXT_INPUT_SLEEP) != 0);
		अगर (en_count > 1) अणु
			dev_err(mfd->dev,
				"External sleep control flag is not proper\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pmic->board_ext_control[id] = ext_sleep_config;

	/* External EN1 control */
	अगर (ext_sleep_config & TPS65910_SLEEP_CONTROL_EXT_INPUT_EN1)
		ret = regmap_set_bits(mfd->regmap,
				TPS65910_EN1_LDO_ASS + regoffs, bit_pos);
	अन्यथा
		ret = regmap_clear_bits(mfd->regmap,
				TPS65910_EN1_LDO_ASS + regoffs, bit_pos);
	अगर (ret < 0) अणु
		dev_err(mfd->dev,
			"Error in configuring external control EN1\n");
		वापस ret;
	पूर्ण

	/* External EN2 control */
	अगर (ext_sleep_config & TPS65910_SLEEP_CONTROL_EXT_INPUT_EN2)
		ret = regmap_set_bits(mfd->regmap,
				TPS65910_EN2_LDO_ASS + regoffs, bit_pos);
	अन्यथा
		ret = regmap_clear_bits(mfd->regmap,
				TPS65910_EN2_LDO_ASS + regoffs, bit_pos);
	अगर (ret < 0) अणु
		dev_err(mfd->dev,
			"Error in configuring external control EN2\n");
		वापस ret;
	पूर्ण

	/* External EN3 control क्रम TPS65910 LDO only */
	अगर ((tps65910_chip_id(mfd) == TPS65910) &&
			(id >= TPS65910_REG_VDIG1)) अणु
		अगर (ext_sleep_config & TPS65910_SLEEP_CONTROL_EXT_INPUT_EN3)
			ret = regmap_set_bits(mfd->regmap,
				TPS65910_EN3_LDO_ASS + regoffs, bit_pos);
		अन्यथा
			ret = regmap_clear_bits(mfd->regmap,
				TPS65910_EN3_LDO_ASS + regoffs, bit_pos);
		अगर (ret < 0) अणु
			dev_err(mfd->dev,
				"Error in configuring external control EN3\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* Return अगर no बाह्यal control is selected */
	अगर (!(ext_sleep_config & EXT_SLEEP_CONTROL)) अणु
		/* Clear all sleep controls */
		ret = regmap_clear_bits(mfd->regmap,
			TPS65910_SLEEP_KEEP_LDO_ON + regoffs, bit_pos);
		अगर (!ret)
			ret = regmap_clear_bits(mfd->regmap,
				TPS65910_SLEEP_SET_LDO_OFF + regoffs, bit_pos);
		अगर (ret < 0)
			dev_err(mfd->dev,
				"Error in configuring SLEEP register\n");
		वापस ret;
	पूर्ण

	/*
	 * For regulator that has separate operational and sleep रेजिस्टर make
	 * sure that operational is used and clear sleep रेजिस्टर to turn
	 * regulator off when बाह्यal control is inactive
	 */
	अगर ((id == TPS65910_REG_VDD1) ||
		(id == TPS65910_REG_VDD2) ||
			((id == TPS65911_REG_VDDCTRL) &&
				(tps65910_chip_id(mfd) == TPS65911))) अणु
		पूर्णांक op_reg_add = pmic->get_ctrl_reg(id) + 1;
		पूर्णांक sr_reg_add = pmic->get_ctrl_reg(id) + 2;
		पूर्णांक opvsel, srvsel;

		ret = regmap_पढ़ो(mfd->regmap, op_reg_add, &opvsel);
		अगर (ret < 0)
			वापस ret;
		ret = regmap_पढ़ो(mfd->regmap, sr_reg_add, &srvsel);
		अगर (ret < 0)
			वापस ret;

		अगर (opvsel & VDD1_OP_CMD_MASK) अणु
			u8 reg_val = srvsel & VDD1_OP_SEL_MASK;

			ret = regmap_ग_लिखो(mfd->regmap, op_reg_add, reg_val);
			अगर (ret < 0) अणु
				dev_err(mfd->dev,
					"Error in configuring op register\n");
				वापस ret;
			पूर्ण
		पूर्ण
		ret = regmap_ग_लिखो(mfd->regmap, sr_reg_add, 0);
		अगर (ret < 0) अणु
			dev_err(mfd->dev, "Error in setting sr register\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = regmap_clear_bits(mfd->regmap,
			TPS65910_SLEEP_KEEP_LDO_ON + regoffs, bit_pos);
	अगर (!ret) अणु
		अगर (ext_sleep_config & TPS65911_SLEEP_CONTROL_EXT_INPUT_SLEEP)
			ret = regmap_set_bits(mfd->regmap,
				TPS65910_SLEEP_SET_LDO_OFF + regoffs, bit_pos);
		अन्यथा
			ret = regmap_clear_bits(mfd->regmap,
				TPS65910_SLEEP_SET_LDO_OFF + regoffs, bit_pos);
	पूर्ण
	अगर (ret < 0)
		dev_err(mfd->dev,
			"Error in configuring SLEEP register\n");

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF

अटल काष्ठा of_regulator_match tps65910_matches[] = अणु
	अणु .name = "vrtc",	.driver_data = (व्योम *) &tps65910_regs[0] पूर्ण,
	अणु .name = "vio",	.driver_data = (व्योम *) &tps65910_regs[1] पूर्ण,
	अणु .name = "vdd1",	.driver_data = (व्योम *) &tps65910_regs[2] पूर्ण,
	अणु .name = "vdd2",	.driver_data = (व्योम *) &tps65910_regs[3] पूर्ण,
	अणु .name = "vdd3",	.driver_data = (व्योम *) &tps65910_regs[4] पूर्ण,
	अणु .name = "vdig1",	.driver_data = (व्योम *) &tps65910_regs[5] पूर्ण,
	अणु .name = "vdig2",	.driver_data = (व्योम *) &tps65910_regs[6] पूर्ण,
	अणु .name = "vpll",	.driver_data = (व्योम *) &tps65910_regs[7] पूर्ण,
	अणु .name = "vdac",	.driver_data = (व्योम *) &tps65910_regs[8] पूर्ण,
	अणु .name = "vaux1",	.driver_data = (व्योम *) &tps65910_regs[9] पूर्ण,
	अणु .name = "vaux2",	.driver_data = (व्योम *) &tps65910_regs[10] पूर्ण,
	अणु .name = "vaux33",	.driver_data = (व्योम *) &tps65910_regs[11] पूर्ण,
	अणु .name = "vmmc",	.driver_data = (व्योम *) &tps65910_regs[12] पूर्ण,
	अणु .name = "vbb",	.driver_data = (व्योम *) &tps65910_regs[13] पूर्ण,
पूर्ण;

अटल काष्ठा of_regulator_match tps65911_matches[] = अणु
	अणु .name = "vrtc",	.driver_data = (व्योम *) &tps65911_regs[0] पूर्ण,
	अणु .name = "vio",	.driver_data = (व्योम *) &tps65911_regs[1] पूर्ण,
	अणु .name = "vdd1",	.driver_data = (व्योम *) &tps65911_regs[2] पूर्ण,
	अणु .name = "vdd2",	.driver_data = (व्योम *) &tps65911_regs[3] पूर्ण,
	अणु .name = "vddctrl",	.driver_data = (व्योम *) &tps65911_regs[4] पूर्ण,
	अणु .name = "ldo1",	.driver_data = (व्योम *) &tps65911_regs[5] पूर्ण,
	अणु .name = "ldo2",	.driver_data = (व्योम *) &tps65911_regs[6] पूर्ण,
	अणु .name = "ldo3",	.driver_data = (व्योम *) &tps65911_regs[7] पूर्ण,
	अणु .name = "ldo4",	.driver_data = (व्योम *) &tps65911_regs[8] पूर्ण,
	अणु .name = "ldo5",	.driver_data = (व्योम *) &tps65911_regs[9] पूर्ण,
	अणु .name = "ldo6",	.driver_data = (व्योम *) &tps65911_regs[10] पूर्ण,
	अणु .name = "ldo7",	.driver_data = (व्योम *) &tps65911_regs[11] पूर्ण,
	अणु .name = "ldo8",	.driver_data = (व्योम *) &tps65911_regs[12] पूर्ण,
पूर्ण;

अटल काष्ठा tps65910_board *tps65910_parse_dt_reg_data(
		काष्ठा platक्रमm_device *pdev,
		काष्ठा of_regulator_match **tps65910_reg_matches)
अणु
	काष्ठा tps65910_board *pmic_plat_data;
	काष्ठा tps65910 *tps65910 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा device_node *np, *regulators;
	काष्ठा of_regulator_match *matches;
	अचिन्हित पूर्णांक prop;
	पूर्णांक idx = 0, ret, count;

	pmic_plat_data = devm_kzalloc(&pdev->dev, माप(*pmic_plat_data),
					GFP_KERNEL);
	अगर (!pmic_plat_data)
		वापस शून्य;

	np = pdev->dev.parent->of_node;
	regulators = of_get_child_by_name(np, "regulators");
	अगर (!regulators) अणु
		dev_err(&pdev->dev, "regulator node not found\n");
		वापस शून्य;
	पूर्ण

	चयन (tps65910_chip_id(tps65910)) अणु
	हाल TPS65910:
		count = ARRAY_SIZE(tps65910_matches);
		matches = tps65910_matches;
		अवरोध;
	हाल TPS65911:
		count = ARRAY_SIZE(tps65911_matches);
		matches = tps65911_matches;
		अवरोध;
	शेष:
		of_node_put(regulators);
		dev_err(&pdev->dev, "Invalid tps chip version\n");
		वापस शून्य;
	पूर्ण

	ret = of_regulator_match(&pdev->dev, regulators, matches, count);
	of_node_put(regulators);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Error parsing regulator init data: %d\n",
			ret);
		वापस शून्य;
	पूर्ण

	*tps65910_reg_matches = matches;

	क्रम (idx = 0; idx < count; idx++) अणु
		अगर (!matches[idx].of_node)
			जारी;

		pmic_plat_data->tps65910_pmic_init_data[idx] =
							matches[idx].init_data;

		ret = of_property_पढ़ो_u32(matches[idx].of_node,
				"ti,regulator-ext-sleep-control", &prop);
		अगर (!ret)
			pmic_plat_data->regulator_ext_sleep_control[idx] = prop;

	पूर्ण

	वापस pmic_plat_data;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा tps65910_board *tps65910_parse_dt_reg_data(
			काष्ठा platक्रमm_device *pdev,
			काष्ठा of_regulator_match **tps65910_reg_matches)
अणु
	*tps65910_reg_matches = शून्य;
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक tps65910_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65910 *tps65910 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा tps_info *info;
	काष्ठा regulator_dev *rdev;
	काष्ठा tps65910_reg *pmic;
	काष्ठा tps65910_board *pmic_plat_data;
	काष्ठा of_regulator_match *tps65910_reg_matches = शून्य;
	पूर्णांक i, err;

	pmic_plat_data = dev_get_platdata(tps65910->dev);
	अगर (!pmic_plat_data && tps65910->dev->of_node)
		pmic_plat_data = tps65910_parse_dt_reg_data(pdev,
						&tps65910_reg_matches);

	अगर (!pmic_plat_data) अणु
		dev_err(&pdev->dev, "Platform data not found\n");
		वापस -EINVAL;
	पूर्ण

	pmic = devm_kzalloc(&pdev->dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	pmic->mfd = tps65910;
	platक्रमm_set_drvdata(pdev, pmic);

	/* Give control of all रेजिस्टर to control port */
	err = regmap_set_bits(pmic->mfd->regmap, TPS65910_DEVCTRL,
				DEVCTRL_SR_CTL_I2C_SEL_MASK);
	अगर (err < 0)
		वापस err;

	चयन (tps65910_chip_id(tps65910)) अणु
	हाल TPS65910:
		BUILD_BUG_ON(TPS65910_NUM_REGS < ARRAY_SIZE(tps65910_regs));
		pmic->get_ctrl_reg = &tps65910_get_ctrl_रेजिस्टर;
		pmic->num_regulators = ARRAY_SIZE(tps65910_regs);
		pmic->ext_sleep_control = tps65910_ext_sleep_control;
		info = tps65910_regs;
		/* Work around silicon erratum SWCZ010: output programmed
		 * voltage level can go higher than expected or crash
		 * Workaround: use no synchronization of DCDC घड़ीs
		 */
		regmap_clear_bits(pmic->mfd->regmap, TPS65910_DCDCCTRL,
					DCDCCTRL_DCDCCKSYNC_MASK);
		अवरोध;
	हाल TPS65911:
		BUILD_BUG_ON(TPS65910_NUM_REGS < ARRAY_SIZE(tps65911_regs));
		pmic->get_ctrl_reg = &tps65911_get_ctrl_रेजिस्टर;
		pmic->num_regulators = ARRAY_SIZE(tps65911_regs);
		pmic->ext_sleep_control = tps65911_ext_sleep_control;
		info = tps65911_regs;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Invalid tps chip version\n");
		वापस -ENODEV;
	पूर्ण

	pmic->desc = devm_kसुस्मृति(&pdev->dev,
				  pmic->num_regulators,
				  माप(काष्ठा regulator_desc),
				  GFP_KERNEL);
	अगर (!pmic->desc)
		वापस -ENOMEM;

	pmic->info = devm_kसुस्मृति(&pdev->dev,
				  pmic->num_regulators,
				  माप(काष्ठा tps_info *),
				  GFP_KERNEL);
	अगर (!pmic->info)
		वापस -ENOMEM;

	pmic->rdev = devm_kसुस्मृति(&pdev->dev,
				  pmic->num_regulators,
				  माप(काष्ठा regulator_dev *),
				  GFP_KERNEL);
	अगर (!pmic->rdev)
		वापस -ENOMEM;

	क्रम (i = 0; i < pmic->num_regulators; i++, info++) अणु
		/* Register the regulators */
		pmic->info[i] = info;

		pmic->desc[i].name = info->name;
		pmic->desc[i].supply_name = info->vin_name;
		pmic->desc[i].id = i;
		pmic->desc[i].n_voltages = info->n_voltages;
		pmic->desc[i].enable_समय = info->enable_समय_us;

		अगर (i == TPS65910_REG_VDD1 || i == TPS65910_REG_VDD2) अणु
			pmic->desc[i].ops = &tps65910_ops_dcdc;
			pmic->desc[i].n_voltages = VDD1_2_NUM_VOLT_FINE *
							VDD1_2_NUM_VOLT_COARSE;
			pmic->desc[i].ramp_delay = 12500;
		पूर्ण अन्यथा अगर (i == TPS65910_REG_VDD3) अणु
			अगर (tps65910_chip_id(tps65910) == TPS65910) अणु
				pmic->desc[i].ops = &tps65910_ops_vdd3;
				pmic->desc[i].volt_table = info->voltage_table;
			पूर्ण अन्यथा अणु
				pmic->desc[i].ops = &tps65910_ops_dcdc;
				pmic->desc[i].ramp_delay = 5000;
			पूर्ण
		पूर्ण अन्यथा अगर (i == TPS65910_REG_VBB &&
				tps65910_chip_id(tps65910) == TPS65910) अणु
			pmic->desc[i].ops = &tps65910_ops_vbb;
			pmic->desc[i].volt_table = info->voltage_table;
		पूर्ण अन्यथा अणु
			अगर (tps65910_chip_id(tps65910) == TPS65910) अणु
				pmic->desc[i].ops = &tps65910_ops;
				pmic->desc[i].volt_table = info->voltage_table;
			पूर्ण अन्यथा अणु
				pmic->desc[i].ops = &tps65911_ops;
			पूर्ण
		पूर्ण

		err = tps65910_set_ext_sleep_config(pmic, i,
				pmic_plat_data->regulator_ext_sleep_control[i]);
		/*
		 * Failing on regulator क्रम configuring बाह्यally control
		 * is not a serious issue, just throw warning.
		 */
		अगर (err < 0)
			dev_warn(tps65910->dev,
				"Failed to initialise ext control config\n");

		pmic->desc[i].type = REGULATOR_VOLTAGE;
		pmic->desc[i].owner = THIS_MODULE;
		pmic->desc[i].enable_reg = pmic->get_ctrl_reg(i);
		pmic->desc[i].enable_mask = TPS65910_SUPPLY_STATE_ENABLED;

		config.dev = tps65910->dev;
		config.init_data = pmic_plat_data->tps65910_pmic_init_data[i];
		config.driver_data = pmic;
		config.regmap = tps65910->regmap;

		अगर (tps65910_reg_matches)
			config.of_node = tps65910_reg_matches[i].of_node;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev, &pmic->desc[i],
					       &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(tps65910->dev,
				"failed to register %s regulator\n",
				pdev->name);
			वापस PTR_ERR(rdev);
		पूर्ण

		/* Save regulator क्रम cleanup */
		pmic->rdev[i] = rdev;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम tps65910_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tps65910_reg *pmic = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	/*
	 * Beक्रमe bootloader jumps to kernel, it makes sure that required
	 * बाह्यal control संकेतs are in desired state so that given rails
	 * can be configure accordingly.
	 * If rails are configured to be controlled from बाह्यal control
	 * then beक्रमe shutting करोwn/rebooting the प्रणाली, the बाह्यal
	 * control configuration need to be हटाओ from the rails so that
	 * its output will be available as per रेजिस्टर programming even
	 * अगर बाह्यal controls are हटाओd. This is require when the POR
	 * value of the control संकेतs are not in active state and beक्रमe
	 * bootloader initializes it, the प्रणाली requires the rail output
	 * to be active क्रम booting.
	 */
	क्रम (i = 0; i < pmic->num_regulators; i++) अणु
		पूर्णांक err;
		अगर (!pmic->rdev[i])
			जारी;

		err = tps65910_set_ext_sleep_config(pmic, i, 0);
		अगर (err < 0)
			dev_err(&pdev->dev,
				"Error in clearing external control\n");
	पूर्ण
पूर्ण

अटल काष्ठा platक्रमm_driver tps65910_driver = अणु
	.driver = अणु
		.name = "tps65910-pmic",
	पूर्ण,
	.probe = tps65910_probe,
	.shutकरोwn = tps65910_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init tps65910_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&tps65910_driver);
पूर्ण
subsys_initcall(tps65910_init);

अटल व्योम __निकास tps65910_cleanup(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&tps65910_driver);
पूर्ण
module_निकास(tps65910_cleanup);

MODULE_AUTHOR("Graeme Gregory <gg@slimlogic.co.uk>");
MODULE_DESCRIPTION("TPS65910/TPS65911 voltage regulator driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:tps65910-pmic");
