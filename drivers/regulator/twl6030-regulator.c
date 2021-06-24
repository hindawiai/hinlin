<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Split TWL6030 logic from twl-regulator.c:
 * Copyright (C) 2008 David Brownell
 *
 * Copyright (C) 2016 Nicolae Rosia <nicolae.rosia@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/twl.h>
#समावेश <linux/delay.h>

काष्ठा twlreg_info अणु
	/* start of regulator's PM_RECEIVER control रेजिस्टर bank */
	u8			base;

	/* twl resource ID, क्रम resource control state machine */
	u8			id;

	u8			flags;

	/* used by regulator core */
	काष्ठा regulator_desc	desc;

	/* chip specअगरic features */
	अचिन्हित दीर्घ		features;

	/* data passed from board क्रम बाह्यal get/set voltage */
	व्योम			*data;
पूर्ण;


/* LDO control रेजिस्टरs ... offset is from the base of its रेजिस्टर bank.
 * The first three रेजिस्टरs of all घातer resource banks help hardware to
 * manage the various resource groups.
 */
/* Common offset in TWL4030/6030 */
#घोषणा VREG_GRP		0
/* TWL6030 रेजिस्टर offsets */
#घोषणा VREG_TRANS		1
#घोषणा VREG_STATE		2
#घोषणा VREG_VOLTAGE		3
#घोषणा VREG_VOLTAGE_SMPS	4
/* TWL6030 Misc रेजिस्टर offsets */
#घोषणा VREG_BC_ALL		1
#घोषणा VREG_BC_REF		2
#घोषणा VREG_BC_PROC		3
#घोषणा VREG_BC_CLK_RST		4

/* TWL6030 LDO रेजिस्टर values क्रम VREG_VOLTAGE */
#घोषणा TWL6030_VREG_VOLTAGE_WR_S   BIT(7)

/* TWL6030 LDO रेजिस्टर values क्रम CFG_STATE */
#घोषणा TWL6030_CFG_STATE_OFF	0x00
#घोषणा TWL6030_CFG_STATE_ON	0x01
#घोषणा TWL6030_CFG_STATE_OFF2	0x02
#घोषणा TWL6030_CFG_STATE_SLEEP	0x03
#घोषणा TWL6030_CFG_STATE_GRP_SHIFT	5
#घोषणा TWL6030_CFG_STATE_APP_SHIFT	2
#घोषणा TWL6030_CFG_STATE_APP_MASK	(0x03 << TWL6030_CFG_STATE_APP_SHIFT)
#घोषणा TWL6030_CFG_STATE_APP(v)	(((v) & TWL6030_CFG_STATE_APP_MASK) >>\
						TWL6030_CFG_STATE_APP_SHIFT)

/* Flags क्रम SMPS Voltage पढ़ोing and LDO पढ़ोing*/
#घोषणा SMPS_OFFSET_EN		BIT(0)
#घोषणा SMPS_EXTENDED_EN	BIT(1)
#घोषणा TWL_6030_WARM_RESET	BIT(3)

/* twl6032 SMPS EPROM values */
#घोषणा TWL6030_SMPS_OFFSET		0xB0
#घोषणा TWL6030_SMPS_MULT		0xB3
#घोषणा SMPS_MULTOFFSET_SMPS4	BIT(0)
#घोषणा SMPS_MULTOFFSET_VIO	BIT(1)
#घोषणा SMPS_MULTOFFSET_SMPS3	BIT(6)

अटल अंतरभूत पूर्णांक
twlreg_पढ़ो(काष्ठा twlreg_info *info, अचिन्हित slave_subgp, अचिन्हित offset)
अणु
	u8 value;
	पूर्णांक status;

	status = twl_i2c_पढ़ो_u8(slave_subgp,
			&value, info->base + offset);
	वापस (status < 0) ? status : value;
पूर्ण

अटल अंतरभूत पूर्णांक
twlreg_ग_लिखो(काष्ठा twlreg_info *info, अचिन्हित slave_subgp, अचिन्हित offset,
						 u8 value)
अणु
	वापस twl_i2c_ग_लिखो_u8(slave_subgp,
			value, info->base + offset);
पूर्ण

/* generic घातer resource operations, which work on all regulators */
अटल पूर्णांक twlreg_grp(काष्ठा regulator_dev *rdev)
अणु
	वापस twlreg_पढ़ो(rdev_get_drvdata(rdev), TWL_MODULE_PM_RECEIVER,
								 VREG_GRP);
पूर्ण

/*
 * Enable/disable regulators by joining/leaving the P1 (processor) group.
 * We assume nobody अन्यथा is updating the DEV_GRP रेजिस्टरs.
 */
/* definition क्रम 6030 family */
#घोषणा P3_GRP_6030	BIT(2)		/* secondary processor, modem, etc */
#घोषणा P2_GRP_6030	BIT(1)		/* "peripherals" */
#घोषणा P1_GRP_6030	BIT(0)		/* CPU/Linux */

अटल पूर्णांक twl6030reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक			grp = 0, val;

	अगर (!(twl_class_is_6030() && (info->features & TWL6032_SUBCLASS))) अणु
		grp = twlreg_grp(rdev);
		अगर (grp < 0)
			वापस grp;
		grp &= P1_GRP_6030;
	पूर्ण अन्यथा अणु
		grp = 1;
	पूर्ण

	val = twlreg_पढ़ो(info, TWL_MODULE_PM_RECEIVER, VREG_STATE);
	val = TWL6030_CFG_STATE_APP(val);

	वापस grp && (val == TWL6030_CFG_STATE_ON);
पूर्ण

#घोषणा PB_I2C_BUSY	BIT(0)
#घोषणा PB_I2C_BWEN	BIT(1)


अटल पूर्णांक twl6030reg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक			grp = 0;
	पूर्णांक			ret;

	अगर (!(twl_class_is_6030() && (info->features & TWL6032_SUBCLASS)))
		grp = twlreg_grp(rdev);
	अगर (grp < 0)
		वापस grp;

	ret = twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_STATE,
			grp << TWL6030_CFG_STATE_GRP_SHIFT |
			TWL6030_CFG_STATE_ON);
	वापस ret;
पूर्ण

अटल पूर्णांक twl6030reg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक			grp = 0;
	पूर्णांक			ret;

	अगर (!(twl_class_is_6030() && (info->features & TWL6032_SUBCLASS)))
		grp = P1_GRP_6030 | P2_GRP_6030 | P3_GRP_6030;

	/* For 6030, set the off state क्रम all grps enabled */
	ret = twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_STATE,
			(grp) << TWL6030_CFG_STATE_GRP_SHIFT |
			TWL6030_CFG_STATE_OFF);

	वापस ret;
पूर्ण

अटल पूर्णांक twl6030reg_get_status(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक			val;

	val = twlreg_grp(rdev);
	अगर (val < 0)
		वापस val;

	val = twlreg_पढ़ो(info, TWL_MODULE_PM_RECEIVER, VREG_STATE);

	चयन (TWL6030_CFG_STATE_APP(val)) अणु
	हाल TWL6030_CFG_STATE_ON:
		वापस REGULATOR_STATUS_NORMAL;

	हाल TWL6030_CFG_STATE_SLEEP:
		वापस REGULATOR_STATUS_STANDBY;

	हाल TWL6030_CFG_STATE_OFF:
	हाल TWL6030_CFG_STATE_OFF2:
	शेष:
		अवरोध;
	पूर्ण

	वापस REGULATOR_STATUS_OFF;
पूर्ण

अटल पूर्णांक twl6030reg_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित mode)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक grp = 0;
	पूर्णांक val;

	अगर (!(twl_class_is_6030() && (info->features & TWL6032_SUBCLASS)))
		grp = twlreg_grp(rdev);

	अगर (grp < 0)
		वापस grp;

	/* Compose the state रेजिस्टर settings */
	val = grp << TWL6030_CFG_STATE_GRP_SHIFT;
	/* We can only set the mode through state machine commands... */
	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val |= TWL6030_CFG_STATE_ON;
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		val |= TWL6030_CFG_STATE_SLEEP;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_STATE, val);
पूर्ण

अटल पूर्णांक twl6030coresmps_set_voltage(काष्ठा regulator_dev *rdev, पूर्णांक min_uV,
	पूर्णांक max_uV, अचिन्हित *selector)
अणु
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक twl6030coresmps_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	वापस -ENODEV;
पूर्ण

अटल स्थिर काष्ठा regulator_ops twl6030coresmps_ops = अणु
	.set_voltage	= twl6030coresmps_set_voltage,
	.get_voltage	= twl6030coresmps_get_voltage,
पूर्ण;

अटल पूर्णांक
twl6030lकरो_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित selector)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);

	अगर (info->flags & TWL_6030_WARM_RESET)
		selector |= TWL6030_VREG_VOLTAGE_WR_S;

	वापस twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE,
			    selector);
पूर्ण

अटल पूर्णांक twl6030lकरो_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक vsel = twlreg_पढ़ो(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE);

	अगर (info->flags & TWL_6030_WARM_RESET)
		vsel &= ~TWL6030_VREG_VOLTAGE_WR_S;

	वापस vsel;
पूर्ण

अटल स्थिर काष्ठा regulator_ops twl6030lकरो_ops = अणु
	.list_voltage	= regulator_list_voltage_linear_range,

	.set_voltage_sel = twl6030lकरो_set_voltage_sel,
	.get_voltage_sel = twl6030lकरो_get_voltage_sel,

	.enable		= twl6030reg_enable,
	.disable	= twl6030reg_disable,
	.is_enabled	= twl6030reg_is_enabled,

	.set_mode	= twl6030reg_set_mode,

	.get_status	= twl6030reg_get_status,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops twl6030fixed_ops = अणु
	.list_voltage	= regulator_list_voltage_linear,

	.enable		= twl6030reg_enable,
	.disable	= twl6030reg_disable,
	.is_enabled	= twl6030reg_is_enabled,

	.set_mode	= twl6030reg_set_mode,

	.get_status	= twl6030reg_get_status,
पूर्ण;

/*
 * SMPS status and control
 */

अटल पूर्णांक twl6030smps_list_voltage(काष्ठा regulator_dev *rdev, अचिन्हित index)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);

	पूर्णांक voltage = 0;

	चयन (info->flags) अणु
	हाल SMPS_OFFSET_EN:
		voltage = 100000;
		fallthrough;
	हाल 0:
		चयन (index) अणु
		हाल 0:
			voltage = 0;
			अवरोध;
		हाल 58:
			voltage = 1350 * 1000;
			अवरोध;
		हाल 59:
			voltage = 1500 * 1000;
			अवरोध;
		हाल 60:
			voltage = 1800 * 1000;
			अवरोध;
		हाल 61:
			voltage = 1900 * 1000;
			अवरोध;
		हाल 62:
			voltage = 2100 * 1000;
			अवरोध;
		शेष:
			voltage += (600000 + (12500 * (index - 1)));
		पूर्ण
		अवरोध;
	हाल SMPS_EXTENDED_EN:
		चयन (index) अणु
		हाल 0:
			voltage = 0;
			अवरोध;
		हाल 58:
			voltage = 2084 * 1000;
			अवरोध;
		हाल 59:
			voltage = 2315 * 1000;
			अवरोध;
		हाल 60:
			voltage = 2778 * 1000;
			अवरोध;
		हाल 61:
			voltage = 2932 * 1000;
			अवरोध;
		हाल 62:
			voltage = 3241 * 1000;
			अवरोध;
		शेष:
			voltage = (1852000 + (38600 * (index - 1)));
		पूर्ण
		अवरोध;
	हाल SMPS_OFFSET_EN | SMPS_EXTENDED_EN:
		चयन (index) अणु
		हाल 0:
			voltage = 0;
			अवरोध;
		हाल 58:
			voltage = 4167 * 1000;
			अवरोध;
		हाल 59:
			voltage = 2315 * 1000;
			अवरोध;
		हाल 60:
			voltage = 2778 * 1000;
			अवरोध;
		हाल 61:
			voltage = 2932 * 1000;
			अवरोध;
		हाल 62:
			voltage = 3241 * 1000;
			अवरोध;
		शेष:
			voltage = (2161000 + (38600 * (index - 1)));
		पूर्ण
		अवरोध;
	पूर्ण

	वापस voltage;
पूर्ण

अटल पूर्णांक twl6030smps_map_voltage(काष्ठा regulator_dev *rdev, पूर्णांक min_uV,
				   पूर्णांक max_uV)
अणु
	काष्ठा twlreg_info *info = rdev_get_drvdata(rdev);
	पूर्णांक vsel = 0;

	चयन (info->flags) अणु
	हाल 0:
		अगर (min_uV == 0)
			vsel = 0;
		अन्यथा अगर ((min_uV >= 600000) && (min_uV <= 1300000)) अणु
			vsel = DIV_ROUND_UP(min_uV - 600000, 12500);
			vsel++;
		पूर्ण
		/* Values 1..57 क्रम vsel are linear and can be calculated
		 * values 58..62 are non linear.
		 */
		अन्यथा अगर ((min_uV > 1900000) && (min_uV <= 2100000))
			vsel = 62;
		अन्यथा अगर ((min_uV > 1800000) && (min_uV <= 1900000))
			vsel = 61;
		अन्यथा अगर ((min_uV > 1500000) && (min_uV <= 1800000))
			vsel = 60;
		अन्यथा अगर ((min_uV > 1350000) && (min_uV <= 1500000))
			vsel = 59;
		अन्यथा अगर ((min_uV > 1300000) && (min_uV <= 1350000))
			vsel = 58;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल SMPS_OFFSET_EN:
		अगर (min_uV == 0)
			vsel = 0;
		अन्यथा अगर ((min_uV >= 700000) && (min_uV <= 1420000)) अणु
			vsel = DIV_ROUND_UP(min_uV - 700000, 12500);
			vsel++;
		पूर्ण
		/* Values 1..57 क्रम vsel are linear and can be calculated
		 * values 58..62 are non linear.
		 */
		अन्यथा अगर ((min_uV > 1900000) && (min_uV <= 2100000))
			vsel = 62;
		अन्यथा अगर ((min_uV > 1800000) && (min_uV <= 1900000))
			vsel = 61;
		अन्यथा अगर ((min_uV > 1500000) && (min_uV <= 1800000))
			vsel = 60;
		अन्यथा अगर ((min_uV > 1350000) && (min_uV <= 1500000))
			vsel = 59;
		अन्यथा
			वापस -EINVAL;
		अवरोध;
	हाल SMPS_EXTENDED_EN:
		अगर (min_uV == 0) अणु
			vsel = 0;
		पूर्ण अन्यथा अगर ((min_uV >= 1852000) && (max_uV <= 4013600)) अणु
			vsel = DIV_ROUND_UP(min_uV - 1852000, 38600);
			vsel++;
		पूर्ण
		अवरोध;
	हाल SMPS_OFFSET_EN|SMPS_EXTENDED_EN:
		अगर (min_uV == 0) अणु
			vsel = 0;
		पूर्ण अन्यथा अगर ((min_uV >= 2161000) && (min_uV <= 4321000)) अणु
			vsel = DIV_ROUND_UP(min_uV - 2161000, 38600);
			vsel++;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस vsel;
पूर्ण

अटल पूर्णांक twl6030smps_set_voltage_sel(काष्ठा regulator_dev *rdev,
				       अचिन्हित पूर्णांक selector)
अणु
	काष्ठा twlreg_info *info = rdev_get_drvdata(rdev);

	वापस twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE_SMPS,
			    selector);
पूर्ण

अटल पूर्णांक twl6030smps_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);

	वापस twlreg_पढ़ो(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE_SMPS);
पूर्ण

अटल स्थिर काष्ठा regulator_ops twlsmps_ops = अणु
	.list_voltage		= twl6030smps_list_voltage,
	.map_voltage		= twl6030smps_map_voltage,

	.set_voltage_sel	= twl6030smps_set_voltage_sel,
	.get_voltage_sel	= twl6030smps_get_voltage_sel,

	.enable			= twl6030reg_enable,
	.disable		= twl6030reg_disable,
	.is_enabled		= twl6030reg_is_enabled,

	.set_mode		= twl6030reg_set_mode,

	.get_status		= twl6030reg_get_status,
पूर्ण;

/*----------------------------------------------------------------------*/
अटल स्थिर काष्ठा linear_range twl6030lकरो_linear_range[] = अणु
	REGULATOR_LINEAR_RANGE(0, 0, 0, 0),
	REGULATOR_LINEAR_RANGE(1000000, 1, 24, 100000),
	REGULATOR_LINEAR_RANGE(2750000, 31, 31, 0),
पूर्ण;

#घोषणा TWL6030_ADJUSTABLE_SMPS(label) \
अटल स्थिर काष्ठा twlreg_info TWL6030_INFO_##label = अणु \
	.desc = अणु \
		.name = #label, \
		.id = TWL6030_REG_##label, \
		.ops = &twl6030coresmps_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		पूर्ण, \
	पूर्ण

#घोषणा TWL6030_ADJUSTABLE_LDO(label, offset) \
अटल स्थिर काष्ठा twlreg_info TWL6030_INFO_##label = अणु \
	.base = offset, \
	.desc = अणु \
		.name = #label, \
		.id = TWL6030_REG_##label, \
		.n_voltages = 32, \
		.linear_ranges = twl6030lकरो_linear_range, \
		.n_linear_ranges = ARRAY_SIZE(twl6030lकरो_linear_range), \
		.ops = &twl6030lकरो_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		पूर्ण, \
	पूर्ण

#घोषणा TWL6032_ADJUSTABLE_LDO(label, offset) \
अटल स्थिर काष्ठा twlreg_info TWL6032_INFO_##label = अणु \
	.base = offset, \
	.desc = अणु \
		.name = #label, \
		.id = TWL6032_REG_##label, \
		.n_voltages = 32, \
		.linear_ranges = twl6030lकरो_linear_range, \
		.n_linear_ranges = ARRAY_SIZE(twl6030lकरो_linear_range), \
		.ops = &twl6030lकरो_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		पूर्ण, \
	पूर्ण

#घोषणा TWL6030_FIXED_LDO(label, offset, mVolts, turnon_delay) \
अटल स्थिर काष्ठा twlreg_info TWLFIXED_INFO_##label = अणु \
	.base = offset, \
	.id = 0, \
	.desc = अणु \
		.name = #label, \
		.id = TWL6030##_REG_##label, \
		.n_voltages = 1, \
		.ops = &twl6030fixed_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.min_uV = mVolts * 1000, \
		.enable_समय = turnon_delay, \
		.of_map_mode = शून्य, \
		पूर्ण, \
	पूर्ण

#घोषणा TWL6032_ADJUSTABLE_SMPS(label, offset) \
अटल स्थिर काष्ठा twlreg_info TWLSMPS_INFO_##label = अणु \
	.base = offset, \
	.desc = अणु \
		.name = #label, \
		.id = TWL6032_REG_##label, \
		.n_voltages = 63, \
		.ops = &twlsmps_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		पूर्ण, \
	पूर्ण

/* VUSBCP is managed *only* by the USB subchip */
/* 6030 REG with base as PMC Slave Misc : 0x0030 */
/* Turnon-delay and remap configuration values क्रम 6030 are not
   verअगरied since the specअगरication is not खुला */
TWL6030_ADJUSTABLE_SMPS(VDD1);
TWL6030_ADJUSTABLE_SMPS(VDD2);
TWL6030_ADJUSTABLE_SMPS(VDD3);
TWL6030_ADJUSTABLE_LDO(VAUX1_6030, 0x54);
TWL6030_ADJUSTABLE_LDO(VAUX2_6030, 0x58);
TWL6030_ADJUSTABLE_LDO(VAUX3_6030, 0x5c);
TWL6030_ADJUSTABLE_LDO(VMMC, 0x68);
TWL6030_ADJUSTABLE_LDO(VPP, 0x6c);
TWL6030_ADJUSTABLE_LDO(VUSIM, 0x74);
/* 6025 are नामd compared to 6030 versions */
TWL6032_ADJUSTABLE_LDO(LDO2, 0x54);
TWL6032_ADJUSTABLE_LDO(LDO4, 0x58);
TWL6032_ADJUSTABLE_LDO(LDO3, 0x5c);
TWL6032_ADJUSTABLE_LDO(LDO5, 0x68);
TWL6032_ADJUSTABLE_LDO(LDO1, 0x6c);
TWL6032_ADJUSTABLE_LDO(LDO7, 0x74);
TWL6032_ADJUSTABLE_LDO(LDO6, 0x60);
TWL6032_ADJUSTABLE_LDO(LDOLN, 0x64);
TWL6032_ADJUSTABLE_LDO(LDOUSB, 0x70);
TWL6030_FIXED_LDO(VANA, 0x50, 2100, 0);
TWL6030_FIXED_LDO(VCXIO, 0x60, 1800, 0);
TWL6030_FIXED_LDO(VDAC, 0x64, 1800, 0);
TWL6030_FIXED_LDO(VUSB, 0x70, 3300, 0);
TWL6030_FIXED_LDO(V1V8, 0x16, 1800, 0);
TWL6030_FIXED_LDO(V2V1, 0x1c, 2100, 0);
TWL6032_ADJUSTABLE_SMPS(SMPS3, 0x34);
TWL6032_ADJUSTABLE_SMPS(SMPS4, 0x10);
TWL6032_ADJUSTABLE_SMPS(VIO, 0x16);

अटल u8 twl_get_smps_offset(व्योम)
अणु
	u8 value;

	twl_i2c_पढ़ो_u8(TWL_MODULE_PM_RECEIVER, &value,
			TWL6030_SMPS_OFFSET);
	वापस value;
पूर्ण

अटल u8 twl_get_smps_mult(व्योम)
अणु
	u8 value;

	twl_i2c_पढ़ो_u8(TWL_MODULE_PM_RECEIVER, &value,
			TWL6030_SMPS_MULT);
	वापस value;
पूर्ण

#घोषणा TWL_OF_MATCH(comp, family, label) \
	अणु \
		.compatible = comp, \
		.data = &family##_INFO_##label, \
	पूर्ण

#घोषणा TWL6030_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWL6030, label)
#घोषणा TWL6032_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWL6032, label)
#घोषणा TWLFIXED_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWLFIXED, label)
#घोषणा TWLSMPS_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWLSMPS, label)

अटल स्थिर काष्ठा of_device_id twl_of_match[] = अणु
	TWL6030_OF_MATCH("ti,twl6030-vdd1", VDD1),
	TWL6030_OF_MATCH("ti,twl6030-vdd2", VDD2),
	TWL6030_OF_MATCH("ti,twl6030-vdd3", VDD3),
	TWL6030_OF_MATCH("ti,twl6030-vaux1", VAUX1_6030),
	TWL6030_OF_MATCH("ti,twl6030-vaux2", VAUX2_6030),
	TWL6030_OF_MATCH("ti,twl6030-vaux3", VAUX3_6030),
	TWL6030_OF_MATCH("ti,twl6030-vmmc", VMMC),
	TWL6030_OF_MATCH("ti,twl6030-vpp", VPP),
	TWL6030_OF_MATCH("ti,twl6030-vusim", VUSIM),
	TWL6032_OF_MATCH("ti,twl6032-ldo2", LDO2),
	TWL6032_OF_MATCH("ti,twl6032-ldo4", LDO4),
	TWL6032_OF_MATCH("ti,twl6032-ldo3", LDO3),
	TWL6032_OF_MATCH("ti,twl6032-ldo5", LDO5),
	TWL6032_OF_MATCH("ti,twl6032-ldo1", LDO1),
	TWL6032_OF_MATCH("ti,twl6032-ldo7", LDO7),
	TWL6032_OF_MATCH("ti,twl6032-ldo6", LDO6),
	TWL6032_OF_MATCH("ti,twl6032-ldoln", LDOLN),
	TWL6032_OF_MATCH("ti,twl6032-ldousb", LDOUSB),
	TWLFIXED_OF_MATCH("ti,twl6030-vana", VANA),
	TWLFIXED_OF_MATCH("ti,twl6030-vcxio", VCXIO),
	TWLFIXED_OF_MATCH("ti,twl6030-vdac", VDAC),
	TWLFIXED_OF_MATCH("ti,twl6030-vusb", VUSB),
	TWLFIXED_OF_MATCH("ti,twl6030-v1v8", V1V8),
	TWLFIXED_OF_MATCH("ti,twl6030-v2v1", V2V1),
	TWLSMPS_OF_MATCH("ti,twl6032-smps3", SMPS3),
	TWLSMPS_OF_MATCH("ti,twl6032-smps4", SMPS4),
	TWLSMPS_OF_MATCH("ti,twl6032-vio", VIO),
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_of_match);

अटल पूर्णांक twlreg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक id;
	काष्ठा twlreg_info		*info;
	स्थिर काष्ठा twlreg_info	*ढाँचा;
	काष्ठा regulator_init_data	*initdata;
	काष्ठा regulation_स्थिरraपूर्णांकs	*c;
	काष्ठा regulator_dev		*rdev;
	काष्ठा regulator_config		config = अणु पूर्ण;
	काष्ठा device_node		*np = pdev->dev.of_node;

	ढाँचा = of_device_get_match_data(&pdev->dev);
	अगर (!ढाँचा)
		वापस -ENODEV;

	id = ढाँचा->desc.id;
	initdata = of_get_regulator_init_data(&pdev->dev, np, &ढाँचा->desc);
	अगर (!initdata)
		वापस -EINVAL;

	info = devm_kmemdup(&pdev->dev, ढाँचा, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	/* Constrain board-specअगरic capabilities according to what
	 * this driver and the chip itself can actually करो.
	 */
	c = &initdata->स्थिरraपूर्णांकs;
	c->valid_modes_mask &= REGULATOR_MODE_NORMAL | REGULATOR_MODE_STANDBY;
	c->valid_ops_mask &= REGULATOR_CHANGE_VOLTAGE
				| REGULATOR_CHANGE_MODE
				| REGULATOR_CHANGE_STATUS;

	चयन (id) अणु
	हाल TWL6032_REG_SMPS3:
		अगर (twl_get_smps_mult() & SMPS_MULTOFFSET_SMPS3)
			info->flags |= SMPS_EXTENDED_EN;
		अगर (twl_get_smps_offset() & SMPS_MULTOFFSET_SMPS3)
			info->flags |= SMPS_OFFSET_EN;
		अवरोध;
	हाल TWL6032_REG_SMPS4:
		अगर (twl_get_smps_mult() & SMPS_MULTOFFSET_SMPS4)
			info->flags |= SMPS_EXTENDED_EN;
		अगर (twl_get_smps_offset() & SMPS_MULTOFFSET_SMPS4)
			info->flags |= SMPS_OFFSET_EN;
		अवरोध;
	हाल TWL6032_REG_VIO:
		अगर (twl_get_smps_mult() & SMPS_MULTOFFSET_VIO)
			info->flags |= SMPS_EXTENDED_EN;
		अगर (twl_get_smps_offset() & SMPS_MULTOFFSET_VIO)
			info->flags |= SMPS_OFFSET_EN;
		अवरोध;
	पूर्ण

	अगर (of_get_property(np, "ti,retain-on-reset", शून्य))
		info->flags |= TWL_6030_WARM_RESET;

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.driver_data = info;
	config.of_node = np;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &info->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "can't register %s, %ld\n",
				info->desc.name, PTR_ERR(rdev));
		वापस PTR_ERR(rdev);
	पूर्ण
	platक्रमm_set_drvdata(pdev, rdev);

	/* NOTE:  many regulators support लघु-circuit IRQs (presentable
	 * as REGULATOR_OVER_CURRENT notअगरications?) configured via:
	 *  - SC_CONFIG
	 *  - SC_DETECT1 (vपूर्णांकana2, vmmc1/2, vaux1/2/3/4)
	 *  - SC_DETECT2 (vusb, vdac, vio, vdd1/2, vpll2)
	 *  - IT_CONFIG
	 */

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:twl6030_reg");

अटल काष्ठा platक्रमm_driver twlreg_driver = अणु
	.probe		= twlreg_probe,
	/* NOTE: लघु name, to work around driver model truncation of
	 * "twl_regulator.12" (and मित्रs) to "twl_regulator.1".
	 */
	.driver  = अणु
		.name  = "twl6030_reg",
		.of_match_table = of_match_ptr(twl_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init twlreg_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&twlreg_driver);
पूर्ण
subsys_initcall(twlreg_init);

अटल व्योम __निकास twlreg_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&twlreg_driver);
पूर्ण
module_निकास(twlreg_निकास)

MODULE_DESCRIPTION("TWL6030 regulator driver");
MODULE_LICENSE("GPL");
