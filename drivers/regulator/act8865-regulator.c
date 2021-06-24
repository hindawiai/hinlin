<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * act8865-regulator.c - Voltage regulation क्रम active-semi ACT88xx PMUs
 *
 * http://www.active-semi.com/products/घातer-management-units/act88xx/
 *
 * Copyright (C) 2013 Aपंचांगel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/act8865.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/regmap.h>
#समावेश <dt-bindings/regulator/active-semi,8865-regulator.h>

/*
 * ACT8600 Global Register Map.
 */
#घोषणा ACT8600_SYS_MODE	0x00
#घोषणा ACT8600_SYS_CTRL	0x01
#घोषणा ACT8600_DCDC1_VSET	0x10
#घोषणा ACT8600_DCDC1_CTRL	0x12
#घोषणा ACT8600_DCDC2_VSET	0x20
#घोषणा ACT8600_DCDC2_CTRL	0x22
#घोषणा ACT8600_DCDC3_VSET	0x30
#घोषणा ACT8600_DCDC3_CTRL	0x32
#घोषणा ACT8600_SUDCDC4_VSET	0x40
#घोषणा ACT8600_SUDCDC4_CTRL	0x41
#घोषणा ACT8600_LDO5_VSET	0x50
#घोषणा ACT8600_LDO5_CTRL	0x51
#घोषणा ACT8600_LDO6_VSET	0x60
#घोषणा ACT8600_LDO6_CTRL	0x61
#घोषणा ACT8600_LDO7_VSET	0x70
#घोषणा ACT8600_LDO7_CTRL	0x71
#घोषणा ACT8600_LDO8_VSET	0x80
#घोषणा ACT8600_LDO8_CTRL	0x81
#घोषणा ACT8600_LDO910_CTRL	0x91
#घोषणा ACT8600_APCH0		0xA1
#घोषणा ACT8600_APCH1		0xA8
#घोषणा ACT8600_APCH2		0xA9
#घोषणा ACT8600_APCH_STAT	0xAA
#घोषणा ACT8600_OTG0		0xB0
#घोषणा ACT8600_OTG1		0xB2

/*
 * ACT8846 Global Register Map.
 */
#घोषणा	ACT8846_SYS0		0x00
#घोषणा	ACT8846_SYS1		0x01
#घोषणा	ACT8846_REG1_VSET	0x10
#घोषणा	ACT8846_REG1_CTRL	0x12
#घोषणा	ACT8846_REG2_VSET0	0x20
#घोषणा	ACT8846_REG2_VSET1	0x21
#घोषणा	ACT8846_REG2_CTRL	0x22
#घोषणा	ACT8846_REG3_VSET0	0x30
#घोषणा	ACT8846_REG3_VSET1	0x31
#घोषणा	ACT8846_REG3_CTRL	0x32
#घोषणा	ACT8846_REG4_VSET0	0x40
#घोषणा	ACT8846_REG4_VSET1	0x41
#घोषणा	ACT8846_REG4_CTRL	0x42
#घोषणा	ACT8846_REG5_VSET	0x50
#घोषणा	ACT8846_REG5_CTRL	0x51
#घोषणा	ACT8846_REG6_VSET	0x58
#घोषणा	ACT8846_REG6_CTRL	0x59
#घोषणा	ACT8846_REG7_VSET	0x60
#घोषणा	ACT8846_REG7_CTRL	0x61
#घोषणा	ACT8846_REG8_VSET	0x68
#घोषणा	ACT8846_REG8_CTRL	0x69
#घोषणा	ACT8846_REG9_VSET	0x70
#घोषणा	ACT8846_REG9_CTRL	0x71
#घोषणा	ACT8846_REG10_VSET	0x80
#घोषणा	ACT8846_REG10_CTRL	0x81
#घोषणा	ACT8846_REG11_VSET	0x90
#घोषणा	ACT8846_REG11_CTRL	0x91
#घोषणा	ACT8846_REG12_VSET	0xa0
#घोषणा	ACT8846_REG12_CTRL	0xa1
#घोषणा	ACT8846_REG13_CTRL	0xb1
#घोषणा	ACT8846_GLB_OFF_CTRL	0xc3
#घोषणा	ACT8846_OFF_SYSMASK	0x18

/*
 * ACT8865 Global Register Map.
 */
#घोषणा	ACT8865_SYS_MODE	0x00
#घोषणा	ACT8865_SYS_CTRL	0x01
#घोषणा	ACT8865_SYS_UNLK_REGS	0x0b
#घोषणा	ACT8865_DCDC1_VSET1	0x20
#घोषणा	ACT8865_DCDC1_VSET2	0x21
#घोषणा	ACT8865_DCDC1_CTRL	0x22
#घोषणा	ACT8865_DCDC1_SUS	0x24
#घोषणा	ACT8865_DCDC2_VSET1	0x30
#घोषणा	ACT8865_DCDC2_VSET2	0x31
#घोषणा	ACT8865_DCDC2_CTRL	0x32
#घोषणा	ACT8865_DCDC2_SUS	0x34
#घोषणा	ACT8865_DCDC3_VSET1	0x40
#घोषणा	ACT8865_DCDC3_VSET2	0x41
#घोषणा	ACT8865_DCDC3_CTRL	0x42
#घोषणा	ACT8865_DCDC3_SUS	0x44
#घोषणा	ACT8865_LDO1_VSET	0x50
#घोषणा	ACT8865_LDO1_CTRL	0x51
#घोषणा	ACT8865_LDO1_SUS	0x52
#घोषणा	ACT8865_LDO2_VSET	0x54
#घोषणा	ACT8865_LDO2_CTRL	0x55
#घोषणा	ACT8865_LDO2_SUS	0x56
#घोषणा	ACT8865_LDO3_VSET	0x60
#घोषणा	ACT8865_LDO3_CTRL	0x61
#घोषणा	ACT8865_LDO3_SUS	0x62
#घोषणा	ACT8865_LDO4_VSET	0x64
#घोषणा	ACT8865_LDO4_CTRL	0x65
#घोषणा	ACT8865_LDO4_SUS	0x66
#घोषणा	ACT8865_MSTROFF		0x20

/*
 * Field Definitions.
 */
#घोषणा	ACT8865_ENA		0x80	/* ON - [7] */
#घोषणा	ACT8865_DIS		0x40	/* DIS - [6] */

#घोषणा	ACT8865_VSEL_MASK	0x3F	/* VSET - [5:0] */


#घोषणा ACT8600_LDO10_ENA		0x40	/* ON - [6] */
#घोषणा ACT8600_SUDCDC_VSEL_MASK	0xFF	/* SUDCDC VSET - [7:0] */

#घोषणा ACT8600_APCH_CHG_ACIN		BIT(7)
#घोषणा ACT8600_APCH_CHG_USB		BIT(6)
#घोषणा ACT8600_APCH_CSTATE0		BIT(5)
#घोषणा ACT8600_APCH_CSTATE1		BIT(4)

/*
 * ACT8865 voltage number
 */
#घोषणा	ACT8865_VOLTAGE_NUM	64
#घोषणा ACT8600_SUDCDC_VOLTAGE_NUM	256

काष्ठा act8865 अणु
	काष्ठा regmap *regmap;
	पूर्णांक off_reg;
	पूर्णांक off_mask;
पूर्ण;

अटल स्थिर काष्ठा regmap_range act8600_reg_ranges[] = अणु
	regmap_reg_range(0x00, 0x01),
	regmap_reg_range(0x10, 0x10),
	regmap_reg_range(0x12, 0x12),
	regmap_reg_range(0x20, 0x20),
	regmap_reg_range(0x22, 0x22),
	regmap_reg_range(0x30, 0x30),
	regmap_reg_range(0x32, 0x32),
	regmap_reg_range(0x40, 0x41),
	regmap_reg_range(0x50, 0x51),
	regmap_reg_range(0x60, 0x61),
	regmap_reg_range(0x70, 0x71),
	regmap_reg_range(0x80, 0x81),
	regmap_reg_range(0x91, 0x91),
	regmap_reg_range(0xA1, 0xA1),
	regmap_reg_range(0xA8, 0xAA),
	regmap_reg_range(0xB0, 0xB0),
	regmap_reg_range(0xB2, 0xB2),
	regmap_reg_range(0xC1, 0xC1),
पूर्ण;

अटल स्थिर काष्ठा regmap_range act8600_reg_ro_ranges[] = अणु
	regmap_reg_range(0xAA, 0xAA),
	regmap_reg_range(0xC1, 0xC1),
पूर्ण;

अटल स्थिर काष्ठा regmap_range act8600_reg_अस्थिर_ranges[] = अणु
	regmap_reg_range(0x00, 0x01),
	regmap_reg_range(0x12, 0x12),
	regmap_reg_range(0x22, 0x22),
	regmap_reg_range(0x32, 0x32),
	regmap_reg_range(0x41, 0x41),
	regmap_reg_range(0x51, 0x51),
	regmap_reg_range(0x61, 0x61),
	regmap_reg_range(0x71, 0x71),
	regmap_reg_range(0x81, 0x81),
	regmap_reg_range(0xA8, 0xA8),
	regmap_reg_range(0xAA, 0xAA),
	regmap_reg_range(0xB0, 0xB0),
	regmap_reg_range(0xC1, 0xC1),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table act8600_ग_लिखो_ranges_table = अणु
	.yes_ranges	= act8600_reg_ranges,
	.n_yes_ranges	= ARRAY_SIZE(act8600_reg_ranges),
	.no_ranges	= act8600_reg_ro_ranges,
	.n_no_ranges	= ARRAY_SIZE(act8600_reg_ro_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table act8600_पढ़ो_ranges_table = अणु
	.yes_ranges	= act8600_reg_ranges,
	.n_yes_ranges	= ARRAY_SIZE(act8600_reg_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table act8600_अस्थिर_ranges_table = अणु
	.yes_ranges	= act8600_reg_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(act8600_reg_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config act8600_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xFF,
	.wr_table = &act8600_ग_लिखो_ranges_table,
	.rd_table = &act8600_पढ़ो_ranges_table,
	.अस्थिर_table = &act8600_अस्थिर_ranges_table,
पूर्ण;

अटल स्थिर काष्ठा regmap_config act8865_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर काष्ठा linear_range act8865_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 23, 25000),
	REGULATOR_LINEAR_RANGE(1200000, 24, 47, 50000),
	REGULATOR_LINEAR_RANGE(2400000, 48, 63, 100000),
पूर्ण;

अटल स्थिर काष्ठा linear_range act8600_sudcdc_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(3000000, 0, 63, 0),
	REGULATOR_LINEAR_RANGE(3000000, 64, 159, 100000),
	REGULATOR_LINEAR_RANGE(12600000, 160, 191, 200000),
	REGULATOR_LINEAR_RANGE(19000000, 192, 247, 400000),
	REGULATOR_LINEAR_RANGE(41400000, 248, 255, 0),
पूर्ण;

अटल पूर्णांक act8865_set_suspend_state(काष्ठा regulator_dev *rdev, bool enable)
अणु
	काष्ठा regmap *regmap = rdev->regmap;
	पूर्णांक id = rdev->desc->id, reg, val;

	चयन (id) अणु
	हाल ACT8865_ID_DCDC1:
		reg = ACT8865_DCDC1_SUS;
		val = 0xa8;
		अवरोध;
	हाल ACT8865_ID_DCDC2:
		reg = ACT8865_DCDC2_SUS;
		val = 0xa8;
		अवरोध;
	हाल ACT8865_ID_DCDC3:
		reg = ACT8865_DCDC3_SUS;
		val = 0xa8;
		अवरोध;
	हाल ACT8865_ID_LDO1:
		reg = ACT8865_LDO1_SUS;
		val = 0xe8;
		अवरोध;
	हाल ACT8865_ID_LDO2:
		reg = ACT8865_LDO2_SUS;
		val = 0xe8;
		अवरोध;
	हाल ACT8865_ID_LDO3:
		reg = ACT8865_LDO3_SUS;
		val = 0xe8;
		अवरोध;
	हाल ACT8865_ID_LDO4:
		reg = ACT8865_LDO4_SUS;
		val = 0xe8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (enable)
		val |= BIT(4);

	/*
	 * Ask the PMIC to enable/disable this output when entering hibernate
	 * mode.
	 */
	वापस regmap_ग_लिखो(regmap, reg, val);
पूर्ण

अटल पूर्णांक act8865_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	वापस act8865_set_suspend_state(rdev, true);
पूर्ण

अटल पूर्णांक act8865_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	वापस act8865_set_suspend_state(rdev, false);
पूर्ण

अटल अचिन्हित पूर्णांक act8865_of_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल ACT8865_REGULATOR_MODE_FIXED:
		वापस REGULATOR_MODE_FAST;
	हाल ACT8865_REGULATOR_MODE_NORMAL:
		वापस REGULATOR_MODE_NORMAL;
	हाल ACT8865_REGULATOR_MODE_LOWPOWER:
		वापस REGULATOR_MODE_STANDBY;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल पूर्णांक act8865_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा regmap *regmap = rdev->regmap;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक reg, val = 0;

	चयन (id) अणु
	हाल ACT8865_ID_DCDC1:
		reg = ACT8865_DCDC1_CTRL;
		अवरोध;
	हाल ACT8865_ID_DCDC2:
		reg = ACT8865_DCDC2_CTRL;
		अवरोध;
	हाल ACT8865_ID_DCDC3:
		reg = ACT8865_DCDC3_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO1:
		reg = ACT8865_LDO1_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO2:
		reg = ACT8865_LDO2_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO3:
		reg = ACT8865_LDO3_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO4:
		reg = ACT8865_LDO4_CTRL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
	हाल REGULATOR_MODE_NORMAL:
		अगर (id <= ACT8865_ID_DCDC3)
			val = BIT(5);
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		अगर (id > ACT8865_ID_DCDC3)
			val = BIT(5);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(regmap, reg, BIT(5), val);
पूर्ण

अटल अचिन्हित पूर्णांक act8865_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा regmap *regmap = rdev->regmap;
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक reg, ret, val = 0;

	चयन (id) अणु
	हाल ACT8865_ID_DCDC1:
		reg = ACT8865_DCDC1_CTRL;
		अवरोध;
	हाल ACT8865_ID_DCDC2:
		reg = ACT8865_DCDC2_CTRL;
		अवरोध;
	हाल ACT8865_ID_DCDC3:
		reg = ACT8865_DCDC3_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO1:
		reg = ACT8865_LDO1_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO2:
		reg = ACT8865_LDO2_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO3:
		reg = ACT8865_LDO3_CTRL;
		अवरोध;
	हाल ACT8865_ID_LDO4:
		reg = ACT8865_LDO4_CTRL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(regmap, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (id <= ACT8865_ID_DCDC3 && (val & BIT(5)))
		वापस REGULATOR_MODE_FAST;
	अन्यथा अगर	(id > ACT8865_ID_DCDC3 && !(val & BIT(5)))
		वापस REGULATOR_MODE_NORMAL;
	अन्यथा
		वापस REGULATOR_MODE_STANDBY;
पूर्ण

अटल स्थिर काष्ठा regulator_ops act8865_ops = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= act8865_set_mode,
	.get_mode		= act8865_get_mode,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_suspend_enable	= act8865_set_suspend_enable,
	.set_suspend_disable	= act8865_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops act8865_lकरो_ops = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.set_mode		= act8865_set_mode,
	.get_mode		= act8865_get_mode,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_suspend_enable	= act8865_set_suspend_enable,
	.set_suspend_disable	= act8865_set_suspend_disable,
	.set_pull_करोwn		= regulator_set_pull_करोwn_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops act8865_fixed_lकरो_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
पूर्ण;

#घोषणा ACT88xx_REG_(_name, _family, _id, _vsel_reg, _supply, _ops)	\
	[_family##_ID_##_id] = अणु					\
		.name			= _name,			\
		.of_match		= of_match_ptr(_name),		\
		.of_map_mode		= act8865_of_map_mode,		\
		.regulators_node	= of_match_ptr("regulators"),	\
		.supply_name		= _supply,			\
		.id			= _family##_ID_##_id,		\
		.type			= REGULATOR_VOLTAGE,		\
		.ops			= _ops,				\
		.n_voltages		= ACT8865_VOLTAGE_NUM,		\
		.linear_ranges		= act8865_voltage_ranges,	\
		.n_linear_ranges	= ARRAY_SIZE(act8865_voltage_ranges), \
		.vsel_reg		= _family##_##_id##_##_vsel_reg, \
		.vsel_mask		= ACT8865_VSEL_MASK,		\
		.enable_reg		= _family##_##_id##_CTRL,	\
		.enable_mask		= ACT8865_ENA,			\
		.pull_करोwn_reg		= _family##_##_id##_CTRL,	\
		.pull_करोwn_mask		= ACT8865_DIS,			\
		.owner			= THIS_MODULE,			\
	पूर्ण

#घोषणा ACT88xx_REG(_name, _family, _id, _vsel_reg, _supply) \
	ACT88xx_REG_(_name, _family, _id, _vsel_reg, _supply, &act8865_ops)

#घोषणा ACT88xx_LDO(_name, _family, _id, _vsel_reg, _supply) \
	ACT88xx_REG_(_name, _family, _id, _vsel_reg, _supply, &act8865_lकरो_ops)

अटल स्थिर काष्ठा regulator_desc act8600_regulators[] = अणु
	ACT88xx_REG("DCDC1", ACT8600, DCDC1, VSET, "vp1"),
	ACT88xx_REG("DCDC2", ACT8600, DCDC2, VSET, "vp2"),
	ACT88xx_REG("DCDC3", ACT8600, DCDC3, VSET, "vp3"),
	अणु
		.name = "SUDCDC_REG4",
		.of_match = of_match_ptr("SUDCDC_REG4"),
		.regulators_node = of_match_ptr("regulators"),
		.id = ACT8600_ID_SUDCDC4,
		.ops = &act8865_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = ACT8600_SUDCDC_VOLTAGE_NUM,
		.linear_ranges = act8600_sudcdc_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(act8600_sudcdc_voltage_ranges),
		.vsel_reg = ACT8600_SUDCDC4_VSET,
		.vsel_mask = ACT8600_SUDCDC_VSEL_MASK,
		.enable_reg = ACT8600_SUDCDC4_CTRL,
		.enable_mask = ACT8865_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	ACT88xx_REG("LDO5", ACT8600, LDO5, VSET, "inl"),
	ACT88xx_REG("LDO6", ACT8600, LDO6, VSET, "inl"),
	ACT88xx_REG("LDO7", ACT8600, LDO7, VSET, "inl"),
	ACT88xx_REG("LDO8", ACT8600, LDO8, VSET, "inl"),
	अणु
		.name = "LDO_REG9",
		.of_match = of_match_ptr("LDO_REG9"),
		.regulators_node = of_match_ptr("regulators"),
		.id = ACT8600_ID_LDO9,
		.ops = &act8865_fixed_lकरो_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 1,
		.fixed_uV = 3300000,
		.enable_reg = ACT8600_LDO910_CTRL,
		.enable_mask = ACT8865_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "LDO_REG10",
		.of_match = of_match_ptr("LDO_REG10"),
		.regulators_node = of_match_ptr("regulators"),
		.id = ACT8600_ID_LDO10,
		.ops = &act8865_fixed_lकरो_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 1,
		.fixed_uV = 1200000,
		.enable_reg = ACT8600_LDO910_CTRL,
		.enable_mask = ACT8600_LDO10_ENA,
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc act8846_regulators[] = अणु
	ACT88xx_REG("REG1", ACT8846, REG1, VSET, "vp1"),
	ACT88xx_REG("REG2", ACT8846, REG2, VSET0, "vp2"),
	ACT88xx_REG("REG3", ACT8846, REG3, VSET0, "vp3"),
	ACT88xx_REG("REG4", ACT8846, REG4, VSET0, "vp4"),
	ACT88xx_REG("REG5", ACT8846, REG5, VSET, "inl1"),
	ACT88xx_REG("REG6", ACT8846, REG6, VSET, "inl1"),
	ACT88xx_REG("REG7", ACT8846, REG7, VSET, "inl1"),
	ACT88xx_REG("REG8", ACT8846, REG8, VSET, "inl2"),
	ACT88xx_REG("REG9", ACT8846, REG9, VSET, "inl2"),
	ACT88xx_REG("REG10", ACT8846, REG10, VSET, "inl3"),
	ACT88xx_REG("REG11", ACT8846, REG11, VSET, "inl3"),
	ACT88xx_REG("REG12", ACT8846, REG12, VSET, "inl3"),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc act8865_regulators[] = अणु
	ACT88xx_REG("DCDC_REG1", ACT8865, DCDC1, VSET1, "vp1"),
	ACT88xx_REG("DCDC_REG2", ACT8865, DCDC2, VSET1, "vp2"),
	ACT88xx_REG("DCDC_REG3", ACT8865, DCDC3, VSET1, "vp3"),
	ACT88xx_LDO("LDO_REG1", ACT8865, LDO1, VSET, "inl45"),
	ACT88xx_LDO("LDO_REG2", ACT8865, LDO2, VSET, "inl45"),
	ACT88xx_LDO("LDO_REG3", ACT8865, LDO3, VSET, "inl67"),
	ACT88xx_LDO("LDO_REG4", ACT8865, LDO4, VSET, "inl67"),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc act8865_alt_regulators[] = अणु
	ACT88xx_REG("DCDC_REG1", ACT8865, DCDC1, VSET2, "vp1"),
	ACT88xx_REG("DCDC_REG2", ACT8865, DCDC2, VSET2, "vp2"),
	ACT88xx_REG("DCDC_REG3", ACT8865, DCDC3, VSET2, "vp3"),
	ACT88xx_LDO("LDO_REG1", ACT8865, LDO1, VSET, "inl45"),
	ACT88xx_LDO("LDO_REG2", ACT8865, LDO2, VSET, "inl45"),
	ACT88xx_LDO("LDO_REG3", ACT8865, LDO3, VSET, "inl67"),
	ACT88xx_LDO("LDO_REG4", ACT8865, LDO4, VSET, "inl67"),
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id act8865_dt_ids[] = अणु
	अणु .compatible = "active-semi,act8600", .data = (व्योम *)ACT8600 पूर्ण,
	अणु .compatible = "active-semi,act8846", .data = (व्योम *)ACT8846 पूर्ण,
	अणु .compatible = "active-semi,act8865", .data = (व्योम *)ACT8865 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, act8865_dt_ids);
#पूर्ण_अगर

अटल काष्ठा act8865_regulator_data *act8865_get_regulator_data(
		पूर्णांक id, काष्ठा act8865_platक्रमm_data *pdata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < pdata->num_regulators; i++) अणु
		अगर (pdata->regulators[i].id == id)
			वापस &pdata->regulators[i];
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा i2c_client *act8865_i2c_client;
अटल व्योम act8865_घातer_off(व्योम)
अणु
	काष्ठा act8865 *act8865;

	act8865 = i2c_get_clientdata(act8865_i2c_client);
	regmap_ग_लिखो(act8865->regmap, act8865->off_reg, act8865->off_mask);
	जबतक (1);
पूर्ण

अटल पूर्णांक act8600_अक्षरger_get_status(काष्ठा regmap *map)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;
	u8 state0, state1;

	ret = regmap_पढ़ो(map, ACT8600_APCH_STAT, &val);
	अगर (ret < 0)
		वापस ret;

	state0 = val & ACT8600_APCH_CSTATE0;
	state1 = val & ACT8600_APCH_CSTATE1;

	अगर (state0 && !state1)
		वापस POWER_SUPPLY_STATUS_CHARGING;
	अगर (!state0 && state1)
		वापस POWER_SUPPLY_STATUS_NOT_CHARGING;
	अगर (!state0 && !state1)
		वापस POWER_SUPPLY_STATUS_DISCHARGING;

	वापस POWER_SUPPLY_STATUS_UNKNOWN;
पूर्ण

अटल पूर्णांक act8600_अक्षरger_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
	काष्ठा regmap *map = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = act8600_अक्षरger_get_status(map);
		अगर (ret < 0)
			वापस ret;

		val->पूर्णांकval = ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property act8600_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc act8600_अक्षरger_desc = अणु
	.name = "act8600-charger",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = act8600_अक्षरger_properties,
	.num_properties = ARRAY_SIZE(act8600_अक्षरger_properties),
	.get_property = act8600_अक्षरger_get_property,
पूर्ण;

अटल पूर्णांक act8600_अक्षरger_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply_config cfg = अणु
		.drv_data = regmap,
		.of_node = dev->of_node,
	पूर्ण;

	अक्षरger = devm_घातer_supply_रेजिस्टर(dev, &act8600_अक्षरger_desc, &cfg);

	वापस PTR_ERR_OR_ZERO(अक्षरger);
पूर्ण

अटल पूर्णांक act8865_pmic_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *i2c_id)
अणु
	स्थिर काष्ठा regulator_desc *regulators;
	काष्ठा act8865_platक्रमm_data *pdata = शून्य;
	काष्ठा device *dev = &client->dev;
	पूर्णांक i, ret, num_regulators;
	काष्ठा act8865 *act8865;
	स्थिर काष्ठा regmap_config *regmap_config;
	अचिन्हित दीर्घ type;
	पूर्णांक off_reg, off_mask;
	पूर्णांक voltage_select = 0;

	अगर (dev->of_node) अणु
		स्थिर काष्ठा of_device_id *id;

		id = of_match_device(of_match_ptr(act8865_dt_ids), dev);
		अगर (!id)
			वापस -ENODEV;

		type = (अचिन्हित दीर्घ) id->data;

		voltage_select = !!of_get_property(dev->of_node,
						   "active-semi,vsel-high",
						   शून्य);
	पूर्ण अन्यथा अणु
		type = i2c_id->driver_data;
		pdata = dev_get_platdata(dev);
	पूर्ण

	चयन (type) अणु
	हाल ACT8600:
		regulators = act8600_regulators;
		num_regulators = ARRAY_SIZE(act8600_regulators);
		regmap_config = &act8600_regmap_config;
		off_reg = -1;
		off_mask = -1;
		अवरोध;
	हाल ACT8846:
		regulators = act8846_regulators;
		num_regulators = ARRAY_SIZE(act8846_regulators);
		regmap_config = &act8865_regmap_config;
		off_reg = ACT8846_GLB_OFF_CTRL;
		off_mask = ACT8846_OFF_SYSMASK;
		अवरोध;
	हाल ACT8865:
		अगर (voltage_select) अणु
			regulators = act8865_alt_regulators;
			num_regulators = ARRAY_SIZE(act8865_alt_regulators);
		पूर्ण अन्यथा अणु
			regulators = act8865_regulators;
			num_regulators = ARRAY_SIZE(act8865_regulators);
		पूर्ण
		regmap_config = &act8865_regmap_config;
		off_reg = ACT8865_SYS_CTRL;
		off_mask = ACT8865_MSTROFF;
		अवरोध;
	शेष:
		dev_err(dev, "invalid device id %lu\n", type);
		वापस -EINVAL;
	पूर्ण

	act8865 = devm_kzalloc(dev, माप(काष्ठा act8865), GFP_KERNEL);
	अगर (!act8865)
		वापस -ENOMEM;

	act8865->regmap = devm_regmap_init_i2c(client, regmap_config);
	अगर (IS_ERR(act8865->regmap)) अणु
		ret = PTR_ERR(act8865->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (of_device_is_प्रणाली_घातer_controller(dev->of_node)) अणु
		अगर (!pm_घातer_off && (off_reg > 0)) अणु
			act8865_i2c_client = client;
			act8865->off_reg = off_reg;
			act8865->off_mask = off_mask;
			pm_घातer_off = act8865_घातer_off;
		पूर्ण अन्यथा अणु
			dev_err(dev, "Failed to set poweroff capability, already defined\n");
		पूर्ण
	पूर्ण

	/* Finally रेजिस्टर devices */
	क्रम (i = 0; i < num_regulators; i++) अणु
		स्थिर काष्ठा regulator_desc *desc = &regulators[i];
		काष्ठा regulator_config config = अणु पूर्ण;
		काष्ठा regulator_dev *rdev;

		config.dev = dev;
		config.driver_data = act8865;
		config.regmap = act8865->regmap;

		अगर (pdata) अणु
			काष्ठा act8865_regulator_data *rdata;

			rdata = act8865_get_regulator_data(desc->id, pdata);
			अगर (rdata) अणु
				config.init_data = rdata->init_data;
				config.of_node = rdata->of_node;
			पूर्ण
		पूर्ण

		rdev = devm_regulator_रेजिस्टर(dev, desc, &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev, "failed to register %s\n", desc->name);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	अगर (type == ACT8600) अणु
		ret = act8600_अक्षरger_probe(dev, act8865->regmap);
		अगर (ret < 0) अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to probe charger");
			वापस ret;
		पूर्ण
	पूर्ण

	i2c_set_clientdata(client, act8865);

	/* Unlock expert रेजिस्टरs क्रम ACT8865. */
	वापस type != ACT8865 ? 0 : regmap_ग_लिखो(act8865->regmap,
						  ACT8865_SYS_UNLK_REGS, 0xef);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id act8865_ids[] = अणु
	अणु .name = "act8600", .driver_data = ACT8600 पूर्ण,
	अणु .name = "act8846", .driver_data = ACT8846 पूर्ण,
	अणु .name = "act8865", .driver_data = ACT8865 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, act8865_ids);

अटल काष्ठा i2c_driver act8865_pmic_driver = अणु
	.driver	= अणु
		.name	= "act8865",
	पूर्ण,
	.probe		= act8865_pmic_probe,
	.id_table	= act8865_ids,
पूर्ण;

module_i2c_driver(act8865_pmic_driver);

MODULE_DESCRIPTION("active-semi act88xx voltage regulator driver");
MODULE_AUTHOR("Wenyou Yang <wenyou.yang@atmel.com>");
MODULE_LICENSE("GPL v2");
