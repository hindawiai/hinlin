<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Regulator part of Palmas PMIC Chips
 *
 * Copyright 2011-2013 Texas Instruments Inc.
 *
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 * Author: Ian Lartey <ian@slimlogic.co.uk>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regulator/of_regulator.h>

अटल स्थिर काष्ठा linear_range smps_low_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x0, 0x0, 0),
	REGULATOR_LINEAR_RANGE(500000, 0x1, 0x6, 0),
	REGULATOR_LINEAR_RANGE(510000, 0x7, 0x79, 10000),
	REGULATOR_LINEAR_RANGE(1650000, 0x7A, 0x7f, 0),
पूर्ण;

अटल स्थिर काष्ठा linear_range smps_high_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0x0, 0x0, 0),
	REGULATOR_LINEAR_RANGE(1000000, 0x1, 0x6, 0),
	REGULATOR_LINEAR_RANGE(1020000, 0x7, 0x79, 20000),
	REGULATOR_LINEAR_RANGE(3300000, 0x7A, 0x7f, 0),
पूर्ण;

अटल काष्ठा palmas_regs_info palmas_generic_regs_info[] = अणु
	अणु
		.name		= "SMPS12",
		.sname		= "smps1-in",
		.vsel_addr	= PALMAS_SMPS12_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS12_CTRL,
		.tstep_addr	= PALMAS_SMPS12_TSTEP,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS12,
	पूर्ण,
	अणु
		.name		= "SMPS123",
		.sname		= "smps1-in",
		.vsel_addr	= PALMAS_SMPS12_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS12_CTRL,
		.tstep_addr	= PALMAS_SMPS12_TSTEP,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS12,
	पूर्ण,
	अणु
		.name		= "SMPS3",
		.sname		= "smps3-in",
		.vsel_addr	= PALMAS_SMPS3_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS3_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS3,
	पूर्ण,
	अणु
		.name		= "SMPS45",
		.sname		= "smps4-in",
		.vsel_addr	= PALMAS_SMPS45_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS45_CTRL,
		.tstep_addr	= PALMAS_SMPS45_TSTEP,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS45,
	पूर्ण,
	अणु
		.name		= "SMPS457",
		.sname		= "smps4-in",
		.vsel_addr	= PALMAS_SMPS45_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS45_CTRL,
		.tstep_addr	= PALMAS_SMPS45_TSTEP,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS45,
	पूर्ण,
	अणु
		.name		= "SMPS6",
		.sname		= "smps6-in",
		.vsel_addr	= PALMAS_SMPS6_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS6_CTRL,
		.tstep_addr	= PALMAS_SMPS6_TSTEP,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS6,
	पूर्ण,
	अणु
		.name		= "SMPS7",
		.sname		= "smps7-in",
		.vsel_addr	= PALMAS_SMPS7_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS7_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS7,
	पूर्ण,
	अणु
		.name		= "SMPS8",
		.sname		= "smps8-in",
		.vsel_addr	= PALMAS_SMPS8_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS8_CTRL,
		.tstep_addr	= PALMAS_SMPS8_TSTEP,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS8,
	पूर्ण,
	अणु
		.name		= "SMPS9",
		.sname		= "smps9-in",
		.vsel_addr	= PALMAS_SMPS9_VOLTAGE,
		.ctrl_addr	= PALMAS_SMPS9_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS9,
	पूर्ण,
	अणु
		.name		= "SMPS10_OUT2",
		.sname		= "smps10-in",
		.ctrl_addr	= PALMAS_SMPS10_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS10,
	पूर्ण,
	अणु
		.name		= "SMPS10_OUT1",
		.sname		= "smps10-out2",
		.ctrl_addr	= PALMAS_SMPS10_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SMPS10,
	पूर्ण,
	अणु
		.name		= "LDO1",
		.sname		= "ldo1-in",
		.vsel_addr	= PALMAS_LDO1_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO1_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO1,
	पूर्ण,
	अणु
		.name		= "LDO2",
		.sname		= "ldo2-in",
		.vsel_addr	= PALMAS_LDO2_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO2_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO2,
	पूर्ण,
	अणु
		.name		= "LDO3",
		.sname		= "ldo3-in",
		.vsel_addr	= PALMAS_LDO3_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO3_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO3,
	पूर्ण,
	अणु
		.name		= "LDO4",
		.sname		= "ldo4-in",
		.vsel_addr	= PALMAS_LDO4_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO4_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO4,
	पूर्ण,
	अणु
		.name		= "LDO5",
		.sname		= "ldo5-in",
		.vsel_addr	= PALMAS_LDO5_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO5_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO5,
	पूर्ण,
	अणु
		.name		= "LDO6",
		.sname		= "ldo6-in",
		.vsel_addr	= PALMAS_LDO6_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO6_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO6,
	पूर्ण,
	अणु
		.name		= "LDO7",
		.sname		= "ldo7-in",
		.vsel_addr	= PALMAS_LDO7_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO7_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO7,
	पूर्ण,
	अणु
		.name		= "LDO8",
		.sname		= "ldo8-in",
		.vsel_addr	= PALMAS_LDO8_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO8_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO8,
	पूर्ण,
	अणु
		.name		= "LDO9",
		.sname		= "ldo9-in",
		.vsel_addr	= PALMAS_LDO9_VOLTAGE,
		.ctrl_addr	= PALMAS_LDO9_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDO9,
	पूर्ण,
	अणु
		.name		= "LDOLN",
		.sname		= "ldoln-in",
		.vsel_addr	= PALMAS_LDOLN_VOLTAGE,
		.ctrl_addr	= PALMAS_LDOLN_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDOLN,
	पूर्ण,
	अणु
		.name		= "LDOUSB",
		.sname		= "ldousb-in",
		.vsel_addr	= PALMAS_LDOUSB_VOLTAGE,
		.ctrl_addr	= PALMAS_LDOUSB_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_LDOUSB,
	पूर्ण,
	अणु
		.name		= "REGEN1",
		.ctrl_addr	= PALMAS_REGEN1_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_REGEN1,
	पूर्ण,
	अणु
		.name		= "REGEN2",
		.ctrl_addr	= PALMAS_REGEN2_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_REGEN2,
	पूर्ण,
	अणु
		.name		= "REGEN3",
		.ctrl_addr	= PALMAS_REGEN3_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_REGEN3,
	पूर्ण,
	अणु
		.name		= "SYSEN1",
		.ctrl_addr	= PALMAS_SYSEN1_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SYSEN1,
	पूर्ण,
	अणु
		.name		= "SYSEN2",
		.ctrl_addr	= PALMAS_SYSEN2_CTRL,
		.sleep_id	= PALMAS_EXTERNAL_REQSTR_ID_SYSEN2,
	पूर्ण,
पूर्ण;

अटल काष्ठा palmas_regs_info tps65917_regs_info[] = अणु
	अणु
		.name		= "SMPS1",
		.sname		= "smps1-in",
		.vsel_addr	= TPS65917_SMPS1_VOLTAGE,
		.ctrl_addr	= TPS65917_SMPS1_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_SMPS1,
	पूर्ण,
	अणु
		.name		= "SMPS2",
		.sname		= "smps2-in",
		.vsel_addr	= TPS65917_SMPS2_VOLTAGE,
		.ctrl_addr	= TPS65917_SMPS2_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_SMPS2,
	पूर्ण,
	अणु
		.name		= "SMPS3",
		.sname		= "smps3-in",
		.vsel_addr	= TPS65917_SMPS3_VOLTAGE,
		.ctrl_addr	= TPS65917_SMPS3_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_SMPS3,
	पूर्ण,
	अणु
		.name		= "SMPS4",
		.sname		= "smps4-in",
		.vsel_addr	= TPS65917_SMPS4_VOLTAGE,
		.ctrl_addr	= TPS65917_SMPS4_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_SMPS4,
	पूर्ण,
	अणु
		.name		= "SMPS5",
		.sname		= "smps5-in",
		.vsel_addr	= TPS65917_SMPS5_VOLTAGE,
		.ctrl_addr	= TPS65917_SMPS5_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_SMPS5,
	पूर्ण,
	अणु
		.name		= "SMPS12",
		.sname		= "smps1-in",
		.vsel_addr	= TPS65917_SMPS1_VOLTAGE,
		.ctrl_addr	= TPS65917_SMPS1_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_SMPS12,
	पूर्ण,
	अणु
		.name		= "LDO1",
		.sname		= "ldo1-in",
		.vsel_addr	= TPS65917_LDO1_VOLTAGE,
		.ctrl_addr	= TPS65917_LDO1_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_LDO1,
	पूर्ण,
	अणु
		.name		= "LDO2",
		.sname		= "ldo2-in",
		.vsel_addr	= TPS65917_LDO2_VOLTAGE,
		.ctrl_addr	= TPS65917_LDO2_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_LDO2,
	पूर्ण,
	अणु
		.name		= "LDO3",
		.sname		= "ldo3-in",
		.vsel_addr	= TPS65917_LDO3_VOLTAGE,
		.ctrl_addr	= TPS65917_LDO3_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_LDO3,
	पूर्ण,
	अणु
		.name		= "LDO4",
		.sname		= "ldo4-in",
		.vsel_addr	= TPS65917_LDO4_VOLTAGE,
		.ctrl_addr	= TPS65917_LDO4_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_LDO4,
	पूर्ण,
	अणु
		.name		= "LDO5",
		.sname		= "ldo5-in",
		.vsel_addr	= TPS65917_LDO5_VOLTAGE,
		.ctrl_addr	= TPS65917_LDO5_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_LDO5,
	पूर्ण,
	अणु
		.name		= "REGEN1",
		.ctrl_addr	= TPS65917_REGEN1_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_REGEN1,
	पूर्ण,
	अणु
		.name		= "REGEN2",
		.ctrl_addr	= TPS65917_REGEN2_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_REGEN2,
	पूर्ण,
	अणु
		.name		= "REGEN3",
		.ctrl_addr	= TPS65917_REGEN3_CTRL,
		.sleep_id	= TPS65917_EXTERNAL_REQSTR_ID_REGEN3,
	पूर्ण,
पूर्ण;

#घोषणा EXTERNAL_REQUESTOR(_id, _offset, _pos)		\
	[PALMAS_EXTERNAL_REQSTR_ID_##_id] = अणु		\
		.id = PALMAS_EXTERNAL_REQSTR_ID_##_id,	\
		.reg_offset = _offset,			\
		.bit_pos = _pos,			\
	पूर्ण

अटल काष्ठा palmas_sleep_requestor_info palma_sleep_req_info[] = अणु
	EXTERNAL_REQUESTOR(REGEN1, 0, 0),
	EXTERNAL_REQUESTOR(REGEN2, 0, 1),
	EXTERNAL_REQUESTOR(SYSEN1, 0, 2),
	EXTERNAL_REQUESTOR(SYSEN2, 0, 3),
	EXTERNAL_REQUESTOR(CLK32KG, 0, 4),
	EXTERNAL_REQUESTOR(CLK32KGAUDIO, 0, 5),
	EXTERNAL_REQUESTOR(REGEN3, 0, 6),
	EXTERNAL_REQUESTOR(SMPS12, 1, 0),
	EXTERNAL_REQUESTOR(SMPS3, 1, 1),
	EXTERNAL_REQUESTOR(SMPS45, 1, 2),
	EXTERNAL_REQUESTOR(SMPS6, 1, 3),
	EXTERNAL_REQUESTOR(SMPS7, 1, 4),
	EXTERNAL_REQUESTOR(SMPS8, 1, 5),
	EXTERNAL_REQUESTOR(SMPS9, 1, 6),
	EXTERNAL_REQUESTOR(SMPS10, 1, 7),
	EXTERNAL_REQUESTOR(LDO1, 2, 0),
	EXTERNAL_REQUESTOR(LDO2, 2, 1),
	EXTERNAL_REQUESTOR(LDO3, 2, 2),
	EXTERNAL_REQUESTOR(LDO4, 2, 3),
	EXTERNAL_REQUESTOR(LDO5, 2, 4),
	EXTERNAL_REQUESTOR(LDO6, 2, 5),
	EXTERNAL_REQUESTOR(LDO7, 2, 6),
	EXTERNAL_REQUESTOR(LDO8, 2, 7),
	EXTERNAL_REQUESTOR(LDO9, 3, 0),
	EXTERNAL_REQUESTOR(LDOLN, 3, 1),
	EXTERNAL_REQUESTOR(LDOUSB, 3, 2),
पूर्ण;

#घोषणा EXTERNAL_REQUESTOR_TPS65917(_id, _offset, _pos)		\
	[TPS65917_EXTERNAL_REQSTR_ID_##_id] = अणु		\
		.id = TPS65917_EXTERNAL_REQSTR_ID_##_id,	\
		.reg_offset = _offset,			\
		.bit_pos = _pos,			\
	पूर्ण

अटल काष्ठा palmas_sleep_requestor_info tps65917_sleep_req_info[] = अणु
	EXTERNAL_REQUESTOR_TPS65917(REGEN1, 0, 0),
	EXTERNAL_REQUESTOR_TPS65917(REGEN2, 0, 1),
	EXTERNAL_REQUESTOR_TPS65917(REGEN3, 0, 6),
	EXTERNAL_REQUESTOR_TPS65917(SMPS1, 1, 0),
	EXTERNAL_REQUESTOR_TPS65917(SMPS2, 1, 1),
	EXTERNAL_REQUESTOR_TPS65917(SMPS3, 1, 2),
	EXTERNAL_REQUESTOR_TPS65917(SMPS4, 1, 3),
	EXTERNAL_REQUESTOR_TPS65917(SMPS5, 1, 4),
	EXTERNAL_REQUESTOR_TPS65917(SMPS12, 1, 5),
	EXTERNAL_REQUESTOR_TPS65917(LDO1, 2, 0),
	EXTERNAL_REQUESTOR_TPS65917(LDO2, 2, 1),
	EXTERNAL_REQUESTOR_TPS65917(LDO3, 2, 2),
	EXTERNAL_REQUESTOR_TPS65917(LDO4, 2, 3),
	EXTERNAL_REQUESTOR_TPS65917(LDO5, 2, 4),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक palmas_smps_ramp_delay[4] = अणु0, 10000, 5000, 2500पूर्ण;

#घोषणा SMPS_CTRL_MODE_OFF		0x00
#घोषणा SMPS_CTRL_MODE_ON		0x01
#घोषणा SMPS_CTRL_MODE_ECO		0x02
#घोषणा SMPS_CTRL_MODE_PWM		0x03

#घोषणा PALMAS_SMPS_NUM_VOLTAGES	122
#घोषणा PALMAS_SMPS10_NUM_VOLTAGES	2
#घोषणा PALMAS_LDO_NUM_VOLTAGES		50

#घोषणा SMPS10_VSEL			(1<<3)
#घोषणा SMPS10_BOOST_EN			(1<<2)
#घोषणा SMPS10_BYPASS_EN		(1<<1)
#घोषणा SMPS10_SWITCH_EN		(1<<0)

#घोषणा REGULATOR_SLAVE			0

अटल पूर्णांक palmas_smps_पढ़ो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक *dest)
अणु
	अचिन्हित पूर्णांक addr;

	addr = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE, reg);

	वापस regmap_पढ़ो(palmas->regmap[REGULATOR_SLAVE], addr, dest);
पूर्ण

अटल पूर्णांक palmas_smps_ग_लिखो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक addr;

	addr = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE, reg);

	वापस regmap_ग_लिखो(palmas->regmap[REGULATOR_SLAVE], addr, value);
पूर्ण

अटल पूर्णांक palmas_lकरो_पढ़ो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक *dest)
अणु
	अचिन्हित पूर्णांक addr;

	addr = PALMAS_BASE_TO_REG(PALMAS_LDO_BASE, reg);

	वापस regmap_पढ़ो(palmas->regmap[REGULATOR_SLAVE], addr, dest);
पूर्ण

अटल पूर्णांक palmas_lकरो_ग_लिखो(काष्ठा palmas *palmas, अचिन्हित पूर्णांक reg,
		अचिन्हित पूर्णांक value)
अणु
	अचिन्हित पूर्णांक addr;

	addr = PALMAS_BASE_TO_REG(PALMAS_LDO_BASE, reg);

	वापस regmap_ग_लिखो(palmas->regmap[REGULATOR_SLAVE], addr, value);
पूर्ण

अटल पूर्णांक palmas_set_mode_smps(काष्ठा regulator_dev *dev, अचिन्हित पूर्णांक mode)
अणु
	पूर्णांक id = rdev_get_id(dev);
	पूर्णांक ret;
	काष्ठा palmas_pmic *pmic = rdev_get_drvdata(dev);
	काष्ठा palmas_pmic_driver_data *ddata = pmic->palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];
	अचिन्हित पूर्णांक reg;
	bool rail_enable = true;

	ret = palmas_smps_पढ़ो(pmic->palmas, rinfo->ctrl_addr, &reg);
	अगर (ret)
		वापस ret;

	reg &= ~PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;

	अगर (reg == SMPS_CTRL_MODE_OFF)
		rail_enable = false;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		reg |= SMPS_CTRL_MODE_ON;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		reg |= SMPS_CTRL_MODE_ECO;
		अवरोध;
	हाल REGULATOR_MODE_FAST:
		reg |= SMPS_CTRL_MODE_PWM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	pmic->current_reg_mode[id] = reg & PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;
	अगर (rail_enable)
		palmas_smps_ग_लिखो(pmic->palmas, rinfo->ctrl_addr, reg);

	/* Switch the enable value to ensure this is used क्रम enable */
	pmic->desc[id].enable_val = pmic->current_reg_mode[id];

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक palmas_get_mode_smps(काष्ठा regulator_dev *dev)
अणु
	काष्ठा palmas_pmic *pmic = rdev_get_drvdata(dev);
	पूर्णांक id = rdev_get_id(dev);
	अचिन्हित पूर्णांक reg;

	reg = pmic->current_reg_mode[id] & PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;

	चयन (reg) अणु
	हाल SMPS_CTRL_MODE_ON:
		वापस REGULATOR_MODE_NORMAL;
	हाल SMPS_CTRL_MODE_ECO:
		वापस REGULATOR_MODE_IDLE;
	हाल SMPS_CTRL_MODE_PWM:
		वापस REGULATOR_MODE_FAST;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक palmas_smps_set_ramp_delay(काष्ठा regulator_dev *rdev,
		 पूर्णांक ramp_delay)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा palmas_pmic *pmic = rdev_get_drvdata(rdev);
	काष्ठा palmas_pmic_driver_data *ddata = pmic->palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];
	अचिन्हित पूर्णांक reg = 0;
	पूर्णांक ret;

	/* SMPS3 and SMPS7 करो not have tstep_addr setting */
	चयन (id) अणु
	हाल PALMAS_REG_SMPS3:
	हाल PALMAS_REG_SMPS7:
		वापस 0;
	पूर्ण

	अगर (ramp_delay <= 0)
		reg = 0;
	अन्यथा अगर (ramp_delay <= 2500)
		reg = 3;
	अन्यथा अगर (ramp_delay <= 5000)
		reg = 2;
	अन्यथा
		reg = 1;

	ret = palmas_smps_ग_लिखो(pmic->palmas, rinfo->tstep_addr, reg);
	अगर (ret < 0) अणु
		dev_err(pmic->palmas->dev, "TSTEP write failed: %d\n", ret);
		वापस ret;
	पूर्ण

	pmic->ramp_delay[id] = palmas_smps_ramp_delay[reg];
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regulator_ops palmas_ops_smps = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= palmas_set_mode_smps,
	.get_mode		= palmas_get_mode_smps,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= palmas_smps_set_ramp_delay,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops palmas_ops_ext_control_smps = अणु
	.set_mode		= palmas_set_mode_smps,
	.get_mode		= palmas_get_mode_smps,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= palmas_smps_set_ramp_delay,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops palmas_ops_smps10 = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.set_bypass		= regulator_set_bypass_regmap,
	.get_bypass		= regulator_get_bypass_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65917_ops_smps = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= palmas_set_mode_smps,
	.get_mode		= palmas_get_mode_smps,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65917_ops_ext_control_smps = अणु
	.set_mode		= palmas_set_mode_smps,
	.get_mode		= palmas_get_mode_smps,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
पूर्ण;

अटल पूर्णांक palmas_is_enabled_lकरो(काष्ठा regulator_dev *dev)
अणु
	पूर्णांक id = rdev_get_id(dev);
	काष्ठा palmas_pmic *pmic = rdev_get_drvdata(dev);
	काष्ठा palmas_pmic_driver_data *ddata = pmic->palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];
	अचिन्हित पूर्णांक reg;

	palmas_lकरो_पढ़ो(pmic->palmas, rinfo->ctrl_addr, &reg);

	reg &= PALMAS_LDO1_CTRL_STATUS;

	वापस !!(reg);
पूर्ण

अटल स्थिर काष्ठा regulator_ops palmas_ops_lकरो = अणु
	.is_enabled		= palmas_is_enabled_lकरो,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops palmas_ops_lकरो9 = अणु
	.is_enabled		= palmas_is_enabled_lकरो,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.set_bypass		= regulator_set_bypass_regmap,
	.get_bypass		= regulator_get_bypass_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops palmas_ops_ext_control_lकरो = अणु
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops palmas_ops_extreg = अणु
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops palmas_ops_ext_control_extreg = अणु
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65917_ops_lकरो = अणु
	.is_enabled		= palmas_is_enabled_lकरो,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops tps65917_ops_lकरो_1_2 = अणु
	.is_enabled		= palmas_is_enabled_lकरो,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_bypass		= regulator_set_bypass_regmap,
	.get_bypass		= regulator_get_bypass_regmap,
पूर्ण;

अटल पूर्णांक palmas_regulator_config_बाह्यal(काष्ठा palmas *palmas, पूर्णांक id,
		काष्ठा palmas_reg_init *reg_init)
अणु
	काष्ठा palmas_pmic_driver_data *ddata = palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];
	पूर्णांक ret;

	ret = palmas_ext_control_req_config(palmas, rinfo->sleep_id,
					    reg_init->roof_न्यूनमान, true);
	अगर (ret < 0)
		dev_err(palmas->dev,
			"Ext control config for regulator %d failed %d\n",
			id, ret);
	वापस ret;
पूर्ण

/*
 * setup the hardware based sleep configuration of the SMPS/LDO regulators
 * from the platक्रमm data. This is dअगरferent to the software based control
 * supported by the regulator framework as it is controlled by toggling
 * pins on the PMIC such as PREQ, SYSEN, ...
 */
अटल पूर्णांक palmas_smps_init(काष्ठा palmas *palmas, पूर्णांक id,
		काष्ठा palmas_reg_init *reg_init)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	काष्ठा palmas_pmic_driver_data *ddata = palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];
	अचिन्हित पूर्णांक addr = rinfo->ctrl_addr;

	ret = palmas_smps_पढ़ो(palmas, addr, &reg);
	अगर (ret)
		वापस ret;

	चयन (id) अणु
	हाल PALMAS_REG_SMPS10_OUT1:
	हाल PALMAS_REG_SMPS10_OUT2:
		reg &= ~PALMAS_SMPS10_CTRL_MODE_SLEEP_MASK;
		अगर (reg_init->mode_sleep)
			reg |= reg_init->mode_sleep <<
					PALMAS_SMPS10_CTRL_MODE_SLEEP_SHIFT;
		अवरोध;
	शेष:
		अगर (reg_init->warm_reset)
			reg |= PALMAS_SMPS12_CTRL_WR_S;
		अन्यथा
			reg &= ~PALMAS_SMPS12_CTRL_WR_S;

		अगर (reg_init->roof_न्यूनमान)
			reg |= PALMAS_SMPS12_CTRL_ROOF_FLOOR_EN;
		अन्यथा
			reg &= ~PALMAS_SMPS12_CTRL_ROOF_FLOOR_EN;

		reg &= ~PALMAS_SMPS12_CTRL_MODE_SLEEP_MASK;
		अगर (reg_init->mode_sleep)
			reg |= reg_init->mode_sleep <<
					PALMAS_SMPS12_CTRL_MODE_SLEEP_SHIFT;
	पूर्ण

	ret = palmas_smps_ग_लिखो(palmas, addr, reg);
	अगर (ret)
		वापस ret;

	अगर (rinfo->vsel_addr && reg_init->vsel) अणु

		reg = reg_init->vsel;

		ret = palmas_smps_ग_लिखो(palmas, rinfo->vsel_addr, reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (reg_init->roof_न्यूनमान && (id != PALMAS_REG_SMPS10_OUT1) &&
			(id != PALMAS_REG_SMPS10_OUT2)) अणु
		/* Enable बाह्यally controlled regulator */
		ret = palmas_smps_पढ़ो(palmas, addr, &reg);
		अगर (ret < 0)
			वापस ret;

		अगर (!(reg & PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK)) अणु
			reg |= SMPS_CTRL_MODE_ON;
			ret = palmas_smps_ग_लिखो(palmas, addr, reg);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		वापस palmas_regulator_config_बाह्यal(palmas, id, reg_init);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक palmas_lकरो_init(काष्ठा palmas *palmas, पूर्णांक id,
		काष्ठा palmas_reg_init *reg_init)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret;
	काष्ठा palmas_pmic_driver_data *ddata = palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];

	addr = rinfo->ctrl_addr;

	ret = palmas_lकरो_पढ़ो(palmas, addr, &reg);
	अगर (ret)
		वापस ret;

	अगर (reg_init->warm_reset)
		reg |= PALMAS_LDO1_CTRL_WR_S;
	अन्यथा
		reg &= ~PALMAS_LDO1_CTRL_WR_S;

	अगर (reg_init->mode_sleep)
		reg |= PALMAS_LDO1_CTRL_MODE_SLEEP;
	अन्यथा
		reg &= ~PALMAS_LDO1_CTRL_MODE_SLEEP;

	ret = palmas_lकरो_ग_लिखो(palmas, addr, reg);
	अगर (ret)
		वापस ret;

	अगर (reg_init->roof_न्यूनमान) अणु
		/* Enable बाह्यally controlled regulator */
		ret = palmas_update_bits(palmas, PALMAS_LDO_BASE,
				addr, PALMAS_LDO1_CTRL_MODE_ACTIVE,
				PALMAS_LDO1_CTRL_MODE_ACTIVE);
		अगर (ret < 0) अणु
			dev_err(palmas->dev,
				"LDO Register 0x%02x update failed %d\n",
				addr, ret);
			वापस ret;
		पूर्ण
		वापस palmas_regulator_config_बाह्यal(palmas, id, reg_init);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक palmas_extreg_init(काष्ठा palmas *palmas, पूर्णांक id,
		काष्ठा palmas_reg_init *reg_init)
अणु
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val = 0;
	काष्ठा palmas_pmic_driver_data *ddata = palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];

	addr = rinfo->ctrl_addr;

	अगर (reg_init->mode_sleep)
		val = PALMAS_REGEN1_CTRL_MODE_SLEEP;

	ret = palmas_update_bits(palmas, PALMAS_RESOURCE_BASE,
			addr, PALMAS_REGEN1_CTRL_MODE_SLEEP, val);
	अगर (ret < 0) अणु
		dev_err(palmas->dev, "Resource reg 0x%02x update failed %d\n",
			addr, ret);
		वापस ret;
	पूर्ण

	अगर (reg_init->roof_न्यूनमान) अणु
		/* Enable बाह्यally controlled regulator */
		ret = palmas_update_bits(palmas, PALMAS_RESOURCE_BASE,
				addr, PALMAS_REGEN1_CTRL_MODE_ACTIVE,
				PALMAS_REGEN1_CTRL_MODE_ACTIVE);
		अगर (ret < 0) अणु
			dev_err(palmas->dev,
				"Resource Register 0x%02x update failed %d\n",
				addr, ret);
			वापस ret;
		पूर्ण
		वापस palmas_regulator_config_बाह्यal(palmas, id, reg_init);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम palmas_enable_lकरो8_track(काष्ठा palmas *palmas)
अणु
	अचिन्हित पूर्णांक reg;
	अचिन्हित पूर्णांक addr;
	पूर्णांक ret;
	काष्ठा palmas_pmic_driver_data *ddata = palmas->pmic_ddata;
	काष्ठा palmas_regs_info *rinfo;

	rinfo = &ddata->palmas_regs_info[PALMAS_REG_LDO8];
	addr = rinfo->ctrl_addr;

	ret = palmas_lकरो_पढ़ो(palmas, addr, &reg);
	अगर (ret) अणु
		dev_err(palmas->dev, "Error in reading ldo8 control reg\n");
		वापस;
	पूर्ण

	reg |= PALMAS_LDO8_CTRL_LDO_TRACKING_EN;
	ret = palmas_lकरो_ग_लिखो(palmas, addr, reg);
	अगर (ret < 0) अणु
		dev_err(palmas->dev, "Error in enabling tracking mode\n");
		वापस;
	पूर्ण
	/*
	 * When SMPS45 is set to off and LDO8 tracking is enabled, the LDO8
	 * output is defined by the LDO8_VOLTAGE.VSEL रेजिस्टर भागided by two,
	 * and can be set from 0.45 to 1.65 V.
	 */
	addr = rinfo->vsel_addr;
	ret = palmas_lकरो_पढ़ो(palmas, addr, &reg);
	अगर (ret) अणु
		dev_err(palmas->dev, "Error in reading ldo8 voltage reg\n");
		वापस;
	पूर्ण

	reg = (reg << 1) & PALMAS_LDO8_VOLTAGE_VSEL_MASK;
	ret = palmas_lकरो_ग_लिखो(palmas, addr, reg);
	अगर (ret < 0)
		dev_err(palmas->dev, "Error in setting ldo8 voltage reg\n");

	वापस;
पूर्ण

अटल पूर्णांक palmas_lकरो_registration(काष्ठा palmas_pmic *pmic,
				   काष्ठा palmas_pmic_driver_data *ddata,
				   काष्ठा palmas_pmic_platक्रमm_data *pdata,
				   स्थिर अक्षर *pdev_name,
				   काष्ठा regulator_config config)
अणु
	पूर्णांक id, ret;
	काष्ठा regulator_dev *rdev;
	काष्ठा palmas_reg_init *reg_init;
	काष्ठा palmas_regs_info *rinfo;
	काष्ठा regulator_desc *desc;

	क्रम (id = ddata->lकरो_begin; id < ddata->max_reg; id++) अणु
		अगर (pdata && pdata->reg_init[id])
			reg_init = pdata->reg_init[id];
		अन्यथा
			reg_init = शून्य;

		rinfo = &ddata->palmas_regs_info[id];
		/* Miss out regulators which are not available due
		 * to alternate functions.
		 */

		/* Register the regulators */
		desc = &pmic->desc[id];
		desc->name = rinfo->name;
		desc->id = id;
		desc->type = REGULATOR_VOLTAGE;
		desc->owner = THIS_MODULE;

		अगर (id < PALMAS_REG_REGEN1) अणु
			desc->n_voltages = PALMAS_LDO_NUM_VOLTAGES;
			अगर (reg_init && reg_init->roof_न्यूनमान)
				desc->ops = &palmas_ops_ext_control_lकरो;
			अन्यथा
				desc->ops = &palmas_ops_lकरो;
			desc->min_uV = 900000;
			desc->uV_step = 50000;
			desc->linear_min_sel = 1;
			desc->enable_समय = 500;
			desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_LDO_BASE,
							    rinfo->vsel_addr);
			desc->vsel_mask = PALMAS_LDO1_VOLTAGE_VSEL_MASK;
			desc->enable_reg = PALMAS_BASE_TO_REG(PALMAS_LDO_BASE,
							      rinfo->ctrl_addr);
			desc->enable_mask = PALMAS_LDO1_CTRL_MODE_ACTIVE;

			/* Check अगर LDO8 is in tracking mode or not */
			अगर (pdata && (id == PALMAS_REG_LDO8) &&
			    pdata->enable_lकरो8_tracking) अणु
				palmas_enable_lकरो8_track(pmic->palmas);
				desc->min_uV = 450000;
				desc->uV_step = 25000;
			पूर्ण

			/* LOD6 in vibrator mode will have enable समय 2000us */
			अगर (pdata && pdata->lकरो6_vibrator &&
			    (id == PALMAS_REG_LDO6))
				desc->enable_समय = 2000;

			अगर (id == PALMAS_REG_LDO9) अणु
				desc->ops = &palmas_ops_lकरो9;
				desc->bypass_reg = desc->enable_reg;
				desc->bypass_val_on =
						PALMAS_LDO9_CTRL_LDO_BYPASS_EN;
				desc->bypass_mask =
						PALMAS_LDO9_CTRL_LDO_BYPASS_EN;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!ddata->has_regen3 && id == PALMAS_REG_REGEN3)
				जारी;

			desc->n_voltages = 1;
			अगर (reg_init && reg_init->roof_न्यूनमान)
				desc->ops = &palmas_ops_ext_control_extreg;
			अन्यथा
				desc->ops = &palmas_ops_extreg;
			desc->enable_reg =
					PALMAS_BASE_TO_REG(PALMAS_RESOURCE_BASE,
							   rinfo->ctrl_addr);
			desc->enable_mask = PALMAS_REGEN1_CTRL_MODE_ACTIVE;
		पूर्ण

		अगर (pdata)
			config.init_data = pdata->reg_data[id];
		अन्यथा
			config.init_data = शून्य;

		desc->supply_name = rinfo->sname;
		config.of_node = ddata->palmas_matches[id].of_node;

		rdev = devm_regulator_रेजिस्टर(pmic->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(pmic->dev,
				"failed to register %s regulator\n",
				pdev_name);
			वापस PTR_ERR(rdev);
		पूर्ण

		/* Initialise sleep/init values from platक्रमm data */
		अगर (pdata) अणु
			reg_init = pdata->reg_init[id];
			अगर (reg_init) अणु
				अगर (id <= ddata->lकरो_end)
					ret = palmas_lकरो_init(pmic->palmas, id,
							      reg_init);
				अन्यथा
					ret = palmas_extreg_init(pmic->palmas,
								 id, reg_init);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65917_lकरो_registration(काष्ठा palmas_pmic *pmic,
				     काष्ठा palmas_pmic_driver_data *ddata,
				     काष्ठा palmas_pmic_platक्रमm_data *pdata,
				     स्थिर अक्षर *pdev_name,
				     काष्ठा regulator_config config)
अणु
	पूर्णांक id, ret;
	काष्ठा regulator_dev *rdev;
	काष्ठा palmas_reg_init *reg_init;
	काष्ठा palmas_regs_info *rinfo;
	काष्ठा regulator_desc *desc;

	क्रम (id = ddata->lकरो_begin; id < ddata->max_reg; id++) अणु
		अगर (pdata && pdata->reg_init[id])
			reg_init = pdata->reg_init[id];
		अन्यथा
			reg_init = शून्य;

		/* Miss out regulators which are not available due
		 * to alternate functions.
		 */
		rinfo = &ddata->palmas_regs_info[id];

		/* Register the regulators */
		desc = &pmic->desc[id];
		desc->name = rinfo->name;
		desc->id = id;
		desc->type = REGULATOR_VOLTAGE;
		desc->owner = THIS_MODULE;

		अगर (id < TPS65917_REG_REGEN1) अणु
			desc->n_voltages = PALMAS_LDO_NUM_VOLTAGES;
			अगर (reg_init && reg_init->roof_न्यूनमान)
				desc->ops = &palmas_ops_ext_control_lकरो;
			अन्यथा
				desc->ops = &tps65917_ops_lकरो;
			desc->min_uV = 900000;
			desc->uV_step = 50000;
			desc->linear_min_sel = 1;
			desc->enable_समय = 500;
			desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_LDO_BASE,
							    rinfo->vsel_addr);
			desc->vsel_mask = PALMAS_LDO1_VOLTAGE_VSEL_MASK;
			desc->enable_reg = PALMAS_BASE_TO_REG(PALMAS_LDO_BASE,
							      rinfo->ctrl_addr);
			desc->enable_mask = PALMAS_LDO1_CTRL_MODE_ACTIVE;
			/*
			 * To be confirmed. Discussion on going with PMIC Team.
			 * It is of the order of ~60mV/uS.
			 */
			desc->ramp_delay = 2500;
			अगर (id == TPS65917_REG_LDO1 ||
			    id == TPS65917_REG_LDO2) अणु
				desc->ops = &tps65917_ops_lकरो_1_2;
				desc->bypass_reg = desc->enable_reg;
				desc->bypass_val_on =
						TPS65917_LDO1_CTRL_BYPASS_EN;
				desc->bypass_mask =
						TPS65917_LDO1_CTRL_BYPASS_EN;
			पूर्ण
		पूर्ण अन्यथा अणु
			desc->n_voltages = 1;
			अगर (reg_init && reg_init->roof_न्यूनमान)
				desc->ops = &palmas_ops_ext_control_extreg;
			अन्यथा
				desc->ops = &palmas_ops_extreg;
			desc->enable_reg =
					PALMAS_BASE_TO_REG(PALMAS_RESOURCE_BASE,
							   rinfo->ctrl_addr);
			desc->enable_mask = PALMAS_REGEN1_CTRL_MODE_ACTIVE;
		पूर्ण

		अगर (pdata)
			config.init_data = pdata->reg_data[id];
		अन्यथा
			config.init_data = शून्य;

		desc->supply_name = rinfo->sname;
		config.of_node = ddata->palmas_matches[id].of_node;

		rdev = devm_regulator_रेजिस्टर(pmic->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(pmic->dev,
				"failed to register %s regulator\n",
				pdev_name);
			वापस PTR_ERR(rdev);
		पूर्ण

		/* Initialise sleep/init values from platक्रमm data */
		अगर (pdata) अणु
			reg_init = pdata->reg_init[id];
			अगर (reg_init) अणु
				अगर (id < TPS65917_REG_REGEN1)
					ret = palmas_lकरो_init(pmic->palmas,
							      id, reg_init);
				अन्यथा
					ret = palmas_extreg_init(pmic->palmas,
								 id, reg_init);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक palmas_smps_registration(काष्ठा palmas_pmic *pmic,
				    काष्ठा palmas_pmic_driver_data *ddata,
				    काष्ठा palmas_pmic_platक्रमm_data *pdata,
				    स्थिर अक्षर *pdev_name,
				    काष्ठा regulator_config config)
अणु
	पूर्णांक id, ret;
	अचिन्हित पूर्णांक addr, reg;
	काष्ठा regulator_dev *rdev;
	काष्ठा palmas_reg_init *reg_init;
	काष्ठा palmas_regs_info *rinfo;
	काष्ठा regulator_desc *desc;

	क्रम (id = ddata->smps_start; id <= ddata->smps_end; id++) अणु
		bool ramp_delay_support = false;

		/*
		 * Miss out regulators which are not available due
		 * to slaving configurations.
		 */
		चयन (id) अणु
		हाल PALMAS_REG_SMPS12:
		हाल PALMAS_REG_SMPS3:
			अगर (pmic->smps123)
				जारी;
			अगर (id == PALMAS_REG_SMPS12)
				ramp_delay_support = true;
			अवरोध;
		हाल PALMAS_REG_SMPS123:
			अगर (!pmic->smps123)
				जारी;
			ramp_delay_support = true;
			अवरोध;
		हाल PALMAS_REG_SMPS45:
		हाल PALMAS_REG_SMPS7:
			अगर (pmic->smps457)
				जारी;
			अगर (id == PALMAS_REG_SMPS45)
				ramp_delay_support = true;
			अवरोध;
		हाल PALMAS_REG_SMPS457:
			अगर (!pmic->smps457)
				जारी;
			ramp_delay_support = true;
			अवरोध;
		हाल PALMAS_REG_SMPS10_OUT1:
		हाल PALMAS_REG_SMPS10_OUT2:
			अगर (!PALMAS_PMIC_HAS(pmic->palmas, SMPS10_BOOST))
				जारी;
		पूर्ण
		rinfo = &ddata->palmas_regs_info[id];
		desc = &pmic->desc[id];

		अगर ((id == PALMAS_REG_SMPS6) || (id == PALMAS_REG_SMPS8))
			ramp_delay_support = true;

		अगर (ramp_delay_support) अणु
			addr = rinfo->tstep_addr;
			ret = palmas_smps_पढ़ो(pmic->palmas, addr, &reg);
			अगर (ret < 0) अणु
				dev_err(pmic->dev,
					"reading TSTEP reg failed: %d\n", ret);
				वापस ret;
			पूर्ण
			desc->ramp_delay = palmas_smps_ramp_delay[reg & 0x3];
			pmic->ramp_delay[id] = desc->ramp_delay;
		पूर्ण

		/* Initialise sleep/init values from platक्रमm data */
		अगर (pdata && pdata->reg_init[id]) अणु
			reg_init = pdata->reg_init[id];
			ret = palmas_smps_init(pmic->palmas, id, reg_init);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			reg_init = शून्य;
		पूर्ण

		/* Register the regulators */
		desc->name = rinfo->name;
		desc->id = id;

		चयन (id) अणु
		हाल PALMAS_REG_SMPS10_OUT1:
		हाल PALMAS_REG_SMPS10_OUT2:
			desc->n_voltages = PALMAS_SMPS10_NUM_VOLTAGES;
			desc->ops = &palmas_ops_smps10;
			desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    PALMAS_SMPS10_CTRL);
			desc->vsel_mask = SMPS10_VSEL;
			desc->enable_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    PALMAS_SMPS10_CTRL);
			अगर (id == PALMAS_REG_SMPS10_OUT1)
				desc->enable_mask = SMPS10_SWITCH_EN;
			अन्यथा
				desc->enable_mask = SMPS10_BOOST_EN;
			desc->bypass_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    PALMAS_SMPS10_CTRL);
			desc->bypass_val_on = SMPS10_BYPASS_EN;
			desc->bypass_mask = SMPS10_BYPASS_EN;
			desc->min_uV = 3750000;
			desc->uV_step = 1250000;
			अवरोध;
		शेष:
			/*
			 * Read and store the RANGE bit क्रम later use
			 * This must be करोne beक्रमe regulator is probed,
			 * otherwise we error in probe with unsupportable
			 * ranges. Read the current smps mode क्रम later use.
			 */
			addr = rinfo->vsel_addr;
			desc->n_linear_ranges = 3;

			ret = palmas_smps_पढ़ो(pmic->palmas, addr, &reg);
			अगर (ret)
				वापस ret;
			अगर (reg & PALMAS_SMPS12_VOLTAGE_RANGE)
				pmic->range[id] = 1;
			अगर (pmic->range[id])
				desc->linear_ranges = smps_high_ranges;
			अन्यथा
				desc->linear_ranges = smps_low_ranges;

			अगर (reg_init && reg_init->roof_न्यूनमान)
				desc->ops = &palmas_ops_ext_control_smps;
			अन्यथा
				desc->ops = &palmas_ops_smps;
			desc->n_voltages = PALMAS_SMPS_NUM_VOLTAGES;
			desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							    rinfo->vsel_addr);
			desc->vsel_mask = PALMAS_SMPS12_VOLTAGE_VSEL_MASK;

			/* Read the smps mode क्रम later use. */
			addr = rinfo->ctrl_addr;
			ret = palmas_smps_पढ़ो(pmic->palmas, addr, &reg);
			अगर (ret)
				वापस ret;
			pmic->current_reg_mode[id] = reg &
					PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;

			desc->enable_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
							      rinfo->ctrl_addr);
			desc->enable_mask = PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;
			/* set_mode overrides this value */
			desc->enable_val = SMPS_CTRL_MODE_ON;
		पूर्ण

		desc->type = REGULATOR_VOLTAGE;
		desc->owner = THIS_MODULE;

		अगर (pdata)
			config.init_data = pdata->reg_data[id];
		अन्यथा
			config.init_data = शून्य;

		desc->supply_name = rinfo->sname;
		config.of_node = ddata->palmas_matches[id].of_node;

		rdev = devm_regulator_रेजिस्टर(pmic->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(pmic->dev,
				"failed to register %s regulator\n",
				pdev_name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps65917_smps_registration(काष्ठा palmas_pmic *pmic,
				      काष्ठा palmas_pmic_driver_data *ddata,
				      काष्ठा palmas_pmic_platक्रमm_data *pdata,
				      स्थिर अक्षर *pdev_name,
				      काष्ठा regulator_config config)
अणु
	पूर्णांक id, ret;
	अचिन्हित पूर्णांक addr, reg;
	काष्ठा regulator_dev *rdev;
	काष्ठा palmas_reg_init *reg_init;
	काष्ठा palmas_regs_info *rinfo;
	काष्ठा regulator_desc *desc;

	क्रम (id = ddata->smps_start; id <= ddata->smps_end; id++) अणु
		/*
		 * Miss out regulators which are not available due
		 * to slaving configurations.
		 */
		desc = &pmic->desc[id];
		desc->n_linear_ranges = 3;
		अगर ((id == TPS65917_REG_SMPS2 || id == TPS65917_REG_SMPS1) &&
		    pmic->smps12)
			जारी;

		/* Initialise sleep/init values from platक्रमm data */
		अगर (pdata && pdata->reg_init[id]) अणु
			reg_init = pdata->reg_init[id];
			ret = palmas_smps_init(pmic->palmas, id, reg_init);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			reg_init = शून्य;
		पूर्ण
		rinfo = &ddata->palmas_regs_info[id];

		/* Register the regulators */
		desc->name = rinfo->name;
		desc->id = id;

		/*
		 * Read and store the RANGE bit क्रम later use
		 * This must be करोne beक्रमe regulator is probed,
		 * otherwise we error in probe with unsupportable
		 * ranges. Read the current smps mode क्रम later use.
		 */
		addr = rinfo->vsel_addr;

		ret = palmas_smps_पढ़ो(pmic->palmas, addr, &reg);
		अगर (ret)
			वापस ret;
		अगर (reg & TPS65917_SMPS1_VOLTAGE_RANGE)
			pmic->range[id] = 1;

		अगर (pmic->range[id])
			desc->linear_ranges = smps_high_ranges;
		अन्यथा
			desc->linear_ranges = smps_low_ranges;

		अगर (reg_init && reg_init->roof_न्यूनमान)
			desc->ops = &tps65917_ops_ext_control_smps;
		अन्यथा
			desc->ops = &tps65917_ops_smps;
		desc->n_voltages = PALMAS_SMPS_NUM_VOLTAGES;
		desc->vsel_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
						    rinfo->vsel_addr);
		desc->vsel_mask = PALMAS_SMPS12_VOLTAGE_VSEL_MASK;
		desc->ramp_delay = 2500;

		/* Read the smps mode क्रम later use. */
		addr = rinfo->ctrl_addr;
		ret = palmas_smps_पढ़ो(pmic->palmas, addr, &reg);
		अगर (ret)
			वापस ret;
		pmic->current_reg_mode[id] = reg &
				PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;
		desc->enable_reg = PALMAS_BASE_TO_REG(PALMAS_SMPS_BASE,
						      rinfo->ctrl_addr);
		desc->enable_mask = PALMAS_SMPS12_CTRL_MODE_ACTIVE_MASK;
		/* set_mode overrides this value */
		desc->enable_val = SMPS_CTRL_MODE_ON;

		desc->type = REGULATOR_VOLTAGE;
		desc->owner = THIS_MODULE;

		अगर (pdata)
			config.init_data = pdata->reg_data[id];
		अन्यथा
			config.init_data = शून्य;

		desc->supply_name = rinfo->sname;
		config.of_node = ddata->palmas_matches[id].of_node;

		rdev = devm_regulator_रेजिस्टर(pmic->dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(pmic->dev,
				"failed to register %s regulator\n",
				pdev_name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा of_regulator_match palmas_matches[] = अणु
	अणु .name = "smps12", पूर्ण,
	अणु .name = "smps123", पूर्ण,
	अणु .name = "smps3", पूर्ण,
	अणु .name = "smps45", पूर्ण,
	अणु .name = "smps457", पूर्ण,
	अणु .name = "smps6", पूर्ण,
	अणु .name = "smps7", पूर्ण,
	अणु .name = "smps8", पूर्ण,
	अणु .name = "smps9", पूर्ण,
	अणु .name = "smps10_out2", पूर्ण,
	अणु .name = "smps10_out1", पूर्ण,
	अणु .name = "ldo1", पूर्ण,
	अणु .name = "ldo2", पूर्ण,
	अणु .name = "ldo3", पूर्ण,
	अणु .name = "ldo4", पूर्ण,
	अणु .name = "ldo5", पूर्ण,
	अणु .name = "ldo6", पूर्ण,
	अणु .name = "ldo7", पूर्ण,
	अणु .name = "ldo8", पूर्ण,
	अणु .name = "ldo9", पूर्ण,
	अणु .name = "ldoln", पूर्ण,
	अणु .name = "ldousb", पूर्ण,
	अणु .name = "regen1", पूर्ण,
	अणु .name = "regen2", पूर्ण,
	अणु .name = "regen3", पूर्ण,
	अणु .name = "sysen1", पूर्ण,
	अणु .name = "sysen2", पूर्ण,
पूर्ण;

अटल काष्ठा of_regulator_match tps65917_matches[] = अणु
	अणु .name = "smps1", पूर्ण,
	अणु .name = "smps2", पूर्ण,
	अणु .name = "smps3", पूर्ण,
	अणु .name = "smps4", पूर्ण,
	अणु .name = "smps5", पूर्ण,
	अणु .name = "smps12",पूर्ण,
	अणु .name = "ldo1", पूर्ण,
	अणु .name = "ldo2", पूर्ण,
	अणु .name = "ldo3", पूर्ण,
	अणु .name = "ldo4", पूर्ण,
	अणु .name = "ldo5", पूर्ण,
	अणु .name = "regen1", पूर्ण,
	अणु .name = "regen2", पूर्ण,
	अणु .name = "regen3", पूर्ण,
	अणु .name = "sysen1", पूर्ण,
	अणु .name = "sysen2", पूर्ण,
पूर्ण;

अटल काष्ठा palmas_pmic_driver_data palmas_ddata = अणु
	.smps_start = PALMAS_REG_SMPS12,
	.smps_end = PALMAS_REG_SMPS10_OUT1,
	.lकरो_begin = PALMAS_REG_LDO1,
	.lकरो_end = PALMAS_REG_LDOUSB,
	.max_reg = PALMAS_NUM_REGS,
	.has_regen3 = true,
	.palmas_regs_info = palmas_generic_regs_info,
	.palmas_matches = palmas_matches,
	.sleep_req_info = palma_sleep_req_info,
	.smps_रेजिस्टर = palmas_smps_registration,
	.lकरो_रेजिस्टर = palmas_lकरो_registration,
पूर्ण;

अटल काष्ठा palmas_pmic_driver_data tps65917_ddata = अणु
	.smps_start = TPS65917_REG_SMPS1,
	.smps_end = TPS65917_REG_SMPS12,
	.lकरो_begin = TPS65917_REG_LDO1,
	.lकरो_end = TPS65917_REG_LDO5,
	.max_reg = TPS65917_NUM_REGS,
	.has_regen3 = true,
	.palmas_regs_info = tps65917_regs_info,
	.palmas_matches = tps65917_matches,
	.sleep_req_info = tps65917_sleep_req_info,
	.smps_रेजिस्टर = tps65917_smps_registration,
	.lकरो_रेजिस्टर = tps65917_lकरो_registration,
पूर्ण;

अटल पूर्णांक palmas_dt_to_pdata(काष्ठा device *dev,
			      काष्ठा device_node *node,
			      काष्ठा palmas_pmic_platक्रमm_data *pdata,
			      काष्ठा palmas_pmic_driver_data *ddata)
अणु
	काष्ठा device_node *regulators;
	u32 prop;
	पूर्णांक idx, ret;

	regulators = of_get_child_by_name(node, "regulators");
	अगर (!regulators) अणु
		dev_info(dev, "regulator node not found\n");
		वापस 0;
	पूर्ण

	ret = of_regulator_match(dev, regulators, ddata->palmas_matches,
				 ddata->max_reg);
	of_node_put(regulators);
	अगर (ret < 0) अणु
		dev_err(dev, "Error parsing regulator init data: %d\n", ret);
		वापस 0;
	पूर्ण

	क्रम (idx = 0; idx < ddata->max_reg; idx++) अणु
		काष्ठा of_regulator_match *match;
		काष्ठा palmas_reg_init *rinit;
		काष्ठा device_node *np;

		match = &ddata->palmas_matches[idx];
		np = match->of_node;

		अगर (!match->init_data || !np)
			जारी;

		rinit = devm_kzalloc(dev, माप(*rinit), GFP_KERNEL);
		अगर (!rinit)
			वापस -ENOMEM;

		pdata->reg_data[idx] = match->init_data;
		pdata->reg_init[idx] = rinit;

		rinit->warm_reset = of_property_पढ़ो_bool(np, "ti,warm-reset");
		ret = of_property_पढ़ो_u32(np, "ti,roof-floor", &prop);
		/* EINVAL: Property not found */
		अगर (ret != -EINVAL) अणु
			पूर्णांक econtrol;

			/* use शेष value, when no value is specअगरied */
			econtrol = PALMAS_EXT_CONTROL_NSLEEP;
			अगर (!ret) अणु
				चयन (prop) अणु
				हाल 1:
					econtrol = PALMAS_EXT_CONTROL_ENABLE1;
					अवरोध;
				हाल 2:
					econtrol = PALMAS_EXT_CONTROL_ENABLE2;
					अवरोध;
				हाल 3:
					econtrol = PALMAS_EXT_CONTROL_NSLEEP;
					अवरोध;
				शेष:
					WARN_ON(1);
					dev_warn(dev,
						 "%s: Invalid roof-floor option: %u\n",
						 match->name, prop);
					अवरोध;
				पूर्ण
			पूर्ण
			rinit->roof_न्यूनमान = econtrol;
		पूर्ण

		ret = of_property_पढ़ो_u32(np, "ti,mode-sleep", &prop);
		अगर (!ret)
			rinit->mode_sleep = prop;

		ret = of_property_पढ़ो_bool(np, "ti,smps-range");
		अगर (ret)
			rinit->vsel = PALMAS_SMPS12_VOLTAGE_RANGE;

		अगर (idx == PALMAS_REG_LDO8)
			pdata->enable_lकरो8_tracking = of_property_पढ़ो_bool(
						np, "ti,enable-ldo8-tracking");
	पूर्ण

	pdata->lकरो6_vibrator = of_property_पढ़ो_bool(node, "ti,ldo6-vibrator");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_palmas_match_tbl[] = अणु
	अणु
		.compatible = "ti,palmas-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	अणु
		.compatible = "ti,twl6035-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	अणु
		.compatible = "ti,twl6036-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	अणु
		.compatible = "ti,twl6037-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	अणु
		.compatible = "ti,tps65913-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	अणु
		.compatible = "ti,tps65914-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	अणु
		.compatible = "ti,tps80036-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	अणु
		.compatible = "ti,tps659038-pmic",
		.data = &palmas_ddata,
	पूर्ण,
	 अणु
		.compatible = "ti,tps65917-pmic",
		.data = &tps65917_ddata,
	पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;

अटल पूर्णांक palmas_regulators_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	काष्ठा palmas_pmic_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा palmas_pmic_driver_data *driver_data;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा palmas_pmic *pmic;
	स्थिर अक्षर *pdev_name;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक reg;

	match = of_match_device(of_match_ptr(of_palmas_match_tbl), &pdev->dev);

	अगर (!match)
		वापस -ENODATA;

	driver_data = (काष्ठा palmas_pmic_driver_data *)match->data;
	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pmic = devm_kzalloc(&pdev->dev, माप(*pmic), GFP_KERNEL);
	अगर (!pmic)
		वापस -ENOMEM;

	अगर (of_device_is_compatible(node, "ti,tps659038-pmic")) अणु
		palmas_generic_regs_info[PALMAS_REG_REGEN2].ctrl_addr =
							TPS659038_REGEN2_CTRL;
		palmas_ddata.has_regen3 = false;
	पूर्ण

	pmic->dev = &pdev->dev;
	pmic->palmas = palmas;
	palmas->pmic = pmic;
	platक्रमm_set_drvdata(pdev, pmic);
	pmic->palmas->pmic_ddata = driver_data;

	ret = palmas_dt_to_pdata(&pdev->dev, node, pdata, driver_data);
	अगर (ret)
		वापस ret;

	ret = palmas_smps_पढ़ो(palmas, PALMAS_SMPS_CTRL, &reg);
	अगर (ret)
		वापस ret;

	अगर (reg & PALMAS_SMPS_CTRL_SMPS12_SMPS123_EN) अणु
		pmic->smps123 = 1;
		pmic->smps12 = 1;
	पूर्ण

	अगर (reg & PALMAS_SMPS_CTRL_SMPS45_SMPS457_EN)
		pmic->smps457 = 1;

	config.regmap = palmas->regmap[REGULATOR_SLAVE];
	config.dev = &pdev->dev;
	config.driver_data = pmic;
	pdev_name = pdev->name;

	ret = driver_data->smps_रेजिस्टर(pmic, driver_data, pdata, pdev_name,
					 config);
	अगर (ret)
		वापस ret;

	ret = driver_data->lकरो_रेजिस्टर(pmic, driver_data, pdata, pdev_name,
					config);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver palmas_driver = अणु
	.driver = अणु
		.name = "palmas-pmic",
		.of_match_table = of_palmas_match_tbl,
	पूर्ण,
	.probe = palmas_regulators_probe,
पूर्ण;

अटल पूर्णांक __init palmas_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&palmas_driver);
पूर्ण
subsys_initcall(palmas_init);

अटल व्योम __निकास palmas_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&palmas_driver);
पूर्ण
module_निकास(palmas_निकास);

MODULE_AUTHOR("Graeme Gregory <gg@slimlogic.co.uk>");
MODULE_DESCRIPTION("Palmas voltage regulator driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:palmas-pmic");
MODULE_DEVICE_TABLE(of, of_palmas_match_tbl);
