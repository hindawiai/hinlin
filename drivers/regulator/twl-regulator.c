<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * twl-regulator.c -- support regulators in twl4030/twl6030 family chips
 *
 * Copyright (C) 2008 David Brownell
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

/*
 * The TWL4030/TW5030/TPS659x0 family chips include घातer management, a
 * USB OTG transceiver, an RTC, ADC, PWM, and lots more.  Some versions
 * include an audio codec, battery अक्षरger, and more voltage regulators.
 * These chips are often used in OMAP-based प्रणालीs.
 *
 * This driver implements software-based resource control क्रम various
 * voltage regulators.  This is usually augmented with state machine
 * based control.
 */

काष्ठा twlreg_info अणु
	/* start of regulator's PM_RECEIVER control रेजिस्टर bank */
	u8			base;

	/* twl resource ID, क्रम resource control state machine */
	u8			id;

	/* voltage in mV = table[VSEL]; table_len must be a घातer-of-two */
	u8			table_len;
	स्थिर u16		*table;

	/* State REMAP शेष configuration */
	u8			remap;

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
/* TWL4030 रेजिस्टर offsets */
#घोषणा VREG_TYPE		1
#घोषणा VREG_REMAP		2
#घोषणा VREG_DEDICATED		3	/* LDO control */
#घोषणा VREG_VOLTAGE_SMPS_4030	9
/* TWL6030 रेजिस्टर offsets */
#घोषणा VREG_TRANS		1
#घोषणा VREG_STATE		2
#घोषणा VREG_VOLTAGE		3
#घोषणा VREG_VOLTAGE_SMPS	4

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

/*----------------------------------------------------------------------*/

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
/* definition क्रम 4030 family */
#घोषणा P3_GRP_4030	BIT(7)		/* "peripherals" */
#घोषणा P2_GRP_4030	BIT(6)		/* secondary processor, modem, etc */
#घोषणा P1_GRP_4030	BIT(5)		/* CPU/Linux */
/* definition क्रम 6030 family */
#घोषणा P3_GRP_6030	BIT(2)		/* secondary processor, modem, etc */
#घोषणा P2_GRP_6030	BIT(1)		/* "peripherals" */
#घोषणा P1_GRP_6030	BIT(0)		/* CPU/Linux */

अटल पूर्णांक twl4030reg_is_enabled(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक	state = twlreg_grp(rdev);

	अगर (state < 0)
		वापस state;

	वापस state & P1_GRP_4030;
पूर्ण

#घोषणा PB_I2C_BUSY	BIT(0)
#घोषणा PB_I2C_BWEN	BIT(1)

/* Wait until buffer empty/पढ़ोy to send a word on घातer bus. */
अटल पूर्णांक twl4030_रुको_pb_पढ़ोy(व्योम)
अणु

	पूर्णांक	ret;
	पूर्णांक	समयout = 10;
	u8	val;

	करो अणु
		ret = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &val,
				      TWL4030_PM_MASTER_PB_CFG);
		अगर (ret < 0)
			वापस ret;

		अगर (!(val & PB_I2C_BUSY))
			वापस 0;

		mdelay(1);
		समयout--;
	पूर्ण जबतक (समयout);

	वापस -ETIMEDOUT;
पूर्ण

/* Send a word over the घातerbus */
अटल पूर्णांक twl4030_send_pb_msg(अचिन्हित msg)
अणु
	u8	val;
	पूर्णांक	ret;

	/* save घातerbus configuration */
	ret = twl_i2c_पढ़ो_u8(TWL_MODULE_PM_MASTER, &val,
			      TWL4030_PM_MASTER_PB_CFG);
	अगर (ret < 0)
		वापस ret;

	/* Enable i2c access to घातerbus */
	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, val | PB_I2C_BWEN,
			       TWL4030_PM_MASTER_PB_CFG);
	अगर (ret < 0)
		वापस ret;

	ret = twl4030_रुको_pb_पढ़ोy();
	अगर (ret < 0)
		वापस ret;

	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, msg >> 8,
			       TWL4030_PM_MASTER_PB_WORD_MSB);
	अगर (ret < 0)
		वापस ret;

	ret = twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, msg & 0xff,
			       TWL4030_PM_MASTER_PB_WORD_LSB);
	अगर (ret < 0)
		वापस ret;

	ret = twl4030_रुको_pb_पढ़ोy();
	अगर (ret < 0)
		वापस ret;

	/* Restore घातerbus configuration */
	वापस twl_i2c_ग_लिखो_u8(TWL_MODULE_PM_MASTER, val,
				TWL4030_PM_MASTER_PB_CFG);
पूर्ण

अटल पूर्णांक twl4030reg_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक			grp;
	पूर्णांक			ret;

	grp = twlreg_grp(rdev);
	अगर (grp < 0)
		वापस grp;

	grp |= P1_GRP_4030;

	ret = twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_GRP, grp);

	वापस ret;
पूर्ण

अटल पूर्णांक twl4030reg_disable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक			grp;
	पूर्णांक			ret;

	grp = twlreg_grp(rdev);
	अगर (grp < 0)
		वापस grp;

	grp &= ~(P1_GRP_4030 | P2_GRP_4030 | P3_GRP_4030);

	ret = twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_GRP, grp);

	वापस ret;
पूर्ण

अटल पूर्णांक twl4030reg_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक	state = twlreg_grp(rdev);

	अगर (state < 0)
		वापस state;
	state &= 0x0f;

	/* assume state != WARM_RESET; we'd not be running...  */
	अगर (!state)
		वापस REGULATOR_STATUS_OFF;
	वापस (state & BIT(3))
		? REGULATOR_STATUS_NORMAL
		: REGULATOR_STATUS_STANDBY;
पूर्ण

अटल पूर्णांक twl4030reg_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित mode)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	अचिन्हित		message;

	/* We can only set the mode through state machine commands... */
	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		message = MSG_SINGULAR(DEV_GRP_P1, info->id, RES_STATE_ACTIVE);
		अवरोध;
	हाल REGULATOR_MODE_STANDBY:
		message = MSG_SINGULAR(DEV_GRP_P1, info->id, RES_STATE_SLEEP);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस twl4030_send_pb_msg(message);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक twl4030reg_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल RES_STATE_ACTIVE:
		वापस REGULATOR_MODE_NORMAL;
	हाल RES_STATE_SLEEP:
		वापस REGULATOR_MODE_STANDBY;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * Support क्रम adjustable-voltage LDOs uses a four bit (or less) voltage
 * select field in its control रेजिस्टर.   We use tables indexed by VSEL
 * to record voltages in milliVolts.  (Accuracy is about three percent.)
 *
 * Note that VSEL values क्रम VAUX2 changed in twl5030 and newer silicon;
 * currently handled by listing two slightly dअगरferent VAUX2 regulators,
 * only one of which will be configured.
 *
 * VSEL values करोcumented as "TI cannot support these values" are flagged
 * in these tables as UNSUP() values; we normally won't assign them.
 *
 * VAUX3 at 3V is incorrectly listed in some TI manuals as unsupported.
 * TI are revising the twl5030/tps659x0 specs to support that 3.0V setting.
 */
#घोषणा UNSUP_MASK	0x8000

#घोषणा UNSUP(x)	(UNSUP_MASK | (x))
#घोषणा IS_UNSUP(info, x)			\
	((UNSUP_MASK & (x)) &&			\
	 !((info)->features & TWL4030_ALLOW_UNSUPPORTED))
#घोषणा LDO_MV(x)	(~UNSUP_MASK & (x))


अटल स्थिर u16 VAUX1_VSEL_table[] = अणु
	UNSUP(1500), UNSUP(1800), 2500, 2800,
	3000, 3000, 3000, 3000,
पूर्ण;
अटल स्थिर u16 VAUX2_4030_VSEL_table[] = अणु
	UNSUP(1000), UNSUP(1000), UNSUP(1200), 1300,
	1500, 1800, UNSUP(1850), 2500,
	UNSUP(2600), 2800, UNSUP(2850), UNSUP(3000),
	UNSUP(3150), UNSUP(3150), UNSUP(3150), UNSUP(3150),
पूर्ण;
अटल स्थिर u16 VAUX2_VSEL_table[] = अणु
	1700, 1700, 1900, 1300,
	1500, 1800, 2000, 2500,
	2100, 2800, 2200, 2300,
	2400, 2400, 2400, 2400,
पूर्ण;
अटल स्थिर u16 VAUX3_VSEL_table[] = अणु
	1500, 1800, 2500, 2800,
	3000, 3000, 3000, 3000,
पूर्ण;
अटल स्थिर u16 VAUX4_VSEL_table[] = अणु
	700, 1000, 1200, UNSUP(1300),
	1500, 1800, UNSUP(1850), 2500,
	UNSUP(2600), 2800, UNSUP(2850), UNSUP(3000),
	UNSUP(3150), UNSUP(3150), UNSUP(3150), UNSUP(3150),
पूर्ण;
अटल स्थिर u16 VMMC1_VSEL_table[] = अणु
	1850, 2850, 3000, 3150,
पूर्ण;
अटल स्थिर u16 VMMC2_VSEL_table[] = अणु
	UNSUP(1000), UNSUP(1000), UNSUP(1200), UNSUP(1300),
	UNSUP(1500), UNSUP(1800), 1850, UNSUP(2500),
	2600, 2800, 2850, 3000,
	3150, 3150, 3150, 3150,
पूर्ण;
अटल स्थिर u16 VPLL1_VSEL_table[] = अणु
	1000, 1200, 1300, 1800,
	UNSUP(2800), UNSUP(3000), UNSUP(3000), UNSUP(3000),
पूर्ण;
अटल स्थिर u16 VPLL2_VSEL_table[] = अणु
	700, 1000, 1200, 1300,
	UNSUP(1500), 1800, UNSUP(1850), UNSUP(2500),
	UNSUP(2600), UNSUP(2800), UNSUP(2850), UNSUP(3000),
	UNSUP(3150), UNSUP(3150), UNSUP(3150), UNSUP(3150),
पूर्ण;
अटल स्थिर u16 VSIM_VSEL_table[] = अणु
	UNSUP(1000), UNSUP(1200), UNSUP(1300), 1800,
	2800, 3000, 3000, 3000,
पूर्ण;
अटल स्थिर u16 VDAC_VSEL_table[] = अणु
	1200, 1300, 1800, 1800,
पूर्ण;
अटल स्थिर u16 VIO_VSEL_table[] = अणु
	1800, 1850,
पूर्ण;
अटल स्थिर u16 VINTANA2_VSEL_table[] = अणु
	2500, 2750,
पूर्ण;

/* 600mV to 1450mV in 12.5 mV steps */
अटल स्थिर काष्ठा linear_range VDD1_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 68, 12500)
पूर्ण;

/* 600mV to 1450mV in 12.5 mV steps, everything above = 1500mV */
अटल स्थिर काष्ठा linear_range VDD2_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, 0, 68, 12500),
	REGULATOR_LINEAR_RANGE(1500000, 69, 69, 12500)
पूर्ण;

अटल पूर्णांक twl4030lकरो_list_voltage(काष्ठा regulator_dev *rdev, अचिन्हित index)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक			mV = info->table[index];

	वापस IS_UNSUP(info, mV) ? 0 : (LDO_MV(mV) * 1000);
पूर्ण

अटल पूर्णांक
twl4030lकरो_set_voltage_sel(काष्ठा regulator_dev *rdev, अचिन्हित selector)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);

	वापस twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE,
			    selector);
पूर्ण

अटल पूर्णांक twl4030lकरो_get_voltage_sel(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info	*info = rdev_get_drvdata(rdev);
	पूर्णांक vsel = twlreg_पढ़ो(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE);

	अगर (vsel < 0)
		वापस vsel;

	vsel &= info->table_len - 1;
	वापस vsel;
पूर्ण

अटल स्थिर काष्ठा regulator_ops twl4030lकरो_ops = अणु
	.list_voltage	= twl4030lकरो_list_voltage,

	.set_voltage_sel = twl4030lकरो_set_voltage_sel,
	.get_voltage_sel = twl4030lकरो_get_voltage_sel,

	.enable		= twl4030reg_enable,
	.disable	= twl4030reg_disable,
	.is_enabled	= twl4030reg_is_enabled,

	.set_mode	= twl4030reg_set_mode,

	.get_status	= twl4030reg_get_status,
पूर्ण;

अटल पूर्णांक
twl4030smps_set_voltage(काष्ठा regulator_dev *rdev, पूर्णांक min_uV, पूर्णांक max_uV,
			अचिन्हित *selector)
अणु
	काष्ठा twlreg_info *info = rdev_get_drvdata(rdev);
	पूर्णांक vsel = DIV_ROUND_UP(min_uV - 600000, 12500);

	twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE_SMPS_4030, vsel);

	वापस 0;
पूर्ण

अटल पूर्णांक twl4030smps_get_voltage(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा twlreg_info *info = rdev_get_drvdata(rdev);
	पूर्णांक vsel;

	vsel = twlreg_पढ़ो(info, TWL_MODULE_PM_RECEIVER,
		VREG_VOLTAGE_SMPS_4030);

	वापस vsel * 12500 + 600000;
पूर्ण

अटल स्थिर काष्ठा regulator_ops twl4030smps_ops = अणु
	.list_voltage   = regulator_list_voltage_linear_range,

	.set_voltage	= twl4030smps_set_voltage,
	.get_voltage	= twl4030smps_get_voltage,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल स्थिर काष्ठा regulator_ops twl4030fixed_ops = अणु
	.list_voltage	= regulator_list_voltage_linear,

	.enable		= twl4030reg_enable,
	.disable	= twl4030reg_disable,
	.is_enabled	= twl4030reg_is_enabled,

	.set_mode	= twl4030reg_set_mode,

	.get_status	= twl4030reg_get_status,
पूर्ण;

/*----------------------------------------------------------------------*/

#घोषणा TWL4030_ADJUSTABLE_LDO(label, offset, num, turnon_delay, remap_conf) \
अटल स्थिर काष्ठा twlreg_info TWL4030_INFO_##label = अणु \
	.base = offset, \
	.id = num, \
	.table_len = ARRAY_SIZE(label##_VSEL_table), \
	.table = label##_VSEL_table, \
	.remap = remap_conf, \
	.desc = अणु \
		.name = #label, \
		.id = TWL4030_REG_##label, \
		.n_voltages = ARRAY_SIZE(label##_VSEL_table), \
		.ops = &twl4030lकरो_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.enable_समय = turnon_delay, \
		.of_map_mode = twl4030reg_map_mode, \
		पूर्ण, \
	पूर्ण

#घोषणा TWL4030_ADJUSTABLE_SMPS(label, offset, num, turnon_delay, remap_conf, \
		n_volt) \
अटल स्थिर काष्ठा twlreg_info TWL4030_INFO_##label = अणु \
	.base = offset, \
	.id = num, \
	.remap = remap_conf, \
	.desc = अणु \
		.name = #label, \
		.id = TWL4030_REG_##label, \
		.ops = &twl4030smps_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.enable_समय = turnon_delay, \
		.of_map_mode = twl4030reg_map_mode, \
		.n_voltages = n_volt, \
		.n_linear_ranges = ARRAY_SIZE(label ## _ranges), \
		.linear_ranges = label ## _ranges, \
		पूर्ण, \
	पूर्ण

#घोषणा TWL4030_FIXED_LDO(label, offset, mVolts, num, turnon_delay, \
			remap_conf) \
अटल स्थिर काष्ठा twlreg_info TWLFIXED_INFO_##label = अणु \
	.base = offset, \
	.id = num, \
	.remap = remap_conf, \
	.desc = अणु \
		.name = #label, \
		.id = TWL4030##_REG_##label, \
		.n_voltages = 1, \
		.ops = &twl4030fixed_ops, \
		.type = REGULATOR_VOLTAGE, \
		.owner = THIS_MODULE, \
		.min_uV = mVolts * 1000, \
		.enable_समय = turnon_delay, \
		.of_map_mode = twl4030reg_map_mode, \
		पूर्ण, \
	पूर्ण

/*
 * We list regulators here अगर प्रणालीs need some level of
 * software control over them after boot.
 */
TWL4030_ADJUSTABLE_LDO(VAUX1, 0x17, 1, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VAUX2_4030, 0x1b, 2, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VAUX2, 0x1b, 2, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VAUX3, 0x1f, 3, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VAUX4, 0x23, 4, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VMMC1, 0x27, 5, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VMMC2, 0x2b, 6, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VPLL1, 0x2f, 7, 100, 0x00);
TWL4030_ADJUSTABLE_LDO(VPLL2, 0x33, 8, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VSIM, 0x37, 9, 100, 0x00);
TWL4030_ADJUSTABLE_LDO(VDAC, 0x3b, 10, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VINTANA2, 0x43, 12, 100, 0x08);
TWL4030_ADJUSTABLE_LDO(VIO, 0x4b, 14, 1000, 0x08);
TWL4030_ADJUSTABLE_SMPS(VDD1, 0x55, 15, 1000, 0x08, 68);
TWL4030_ADJUSTABLE_SMPS(VDD2, 0x63, 16, 1000, 0x08, 69);
/* VUSBCP is managed *only* by the USB subchip */
TWL4030_FIXED_LDO(VINTANA1, 0x3f, 1500, 11, 100, 0x08);
TWL4030_FIXED_LDO(VINTDIG, 0x47, 1500, 13, 100, 0x08);
TWL4030_FIXED_LDO(VUSB1V5, 0x71, 1500, 17, 100, 0x08);
TWL4030_FIXED_LDO(VUSB1V8, 0x74, 1800, 18, 100, 0x08);
TWL4030_FIXED_LDO(VUSB3V1, 0x77, 3100, 19, 150, 0x08);

#घोषणा TWL_OF_MATCH(comp, family, label) \
	अणु \
		.compatible = comp, \
		.data = &family##_INFO_##label, \
	पूर्ण

#घोषणा TWL4030_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWL4030, label)
#घोषणा TWL6030_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWL6030, label)
#घोषणा TWL6032_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWL6032, label)
#घोषणा TWLFIXED_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWLFIXED, label)
#घोषणा TWLSMPS_OF_MATCH(comp, label) TWL_OF_MATCH(comp, TWLSMPS, label)

अटल स्थिर काष्ठा of_device_id twl_of_match[] = अणु
	TWL4030_OF_MATCH("ti,twl4030-vaux1", VAUX1),
	TWL4030_OF_MATCH("ti,twl4030-vaux2", VAUX2_4030),
	TWL4030_OF_MATCH("ti,twl5030-vaux2", VAUX2),
	TWL4030_OF_MATCH("ti,twl4030-vaux3", VAUX3),
	TWL4030_OF_MATCH("ti,twl4030-vaux4", VAUX4),
	TWL4030_OF_MATCH("ti,twl4030-vmmc1", VMMC1),
	TWL4030_OF_MATCH("ti,twl4030-vmmc2", VMMC2),
	TWL4030_OF_MATCH("ti,twl4030-vpll1", VPLL1),
	TWL4030_OF_MATCH("ti,twl4030-vpll2", VPLL2),
	TWL4030_OF_MATCH("ti,twl4030-vsim", VSIM),
	TWL4030_OF_MATCH("ti,twl4030-vdac", VDAC),
	TWL4030_OF_MATCH("ti,twl4030-vintana2", VINTANA2),
	TWL4030_OF_MATCH("ti,twl4030-vio", VIO),
	TWL4030_OF_MATCH("ti,twl4030-vdd1", VDD1),
	TWL4030_OF_MATCH("ti,twl4030-vdd2", VDD2),
	TWLFIXED_OF_MATCH("ti,twl4030-vintana1", VINTANA1),
	TWLFIXED_OF_MATCH("ti,twl4030-vintdig", VINTDIG),
	TWLFIXED_OF_MATCH("ti,twl4030-vusb1v5", VUSB1V5),
	TWLFIXED_OF_MATCH("ti,twl4030-vusb1v8", VUSB1V8),
	TWLFIXED_OF_MATCH("ti,twl4030-vusb3v1", VUSB3V1),
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

	ढाँचा = of_device_get_match_data(&pdev->dev);
	अगर (!ढाँचा)
		वापस -ENODEV;

	id = ढाँचा->desc.id;
	initdata = of_get_regulator_init_data(&pdev->dev, pdev->dev.of_node,
						&ढाँचा->desc);
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
	हाल TWL4030_REG_VIO:
	हाल TWL4030_REG_VDD1:
	हाल TWL4030_REG_VDD2:
	हाल TWL4030_REG_VPLL1:
	हाल TWL4030_REG_VINTANA1:
	हाल TWL4030_REG_VINTANA2:
	हाल TWL4030_REG_VINTDIG:
		c->always_on = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.driver_data = info;
	config.of_node = pdev->dev.of_node;

	rdev = devm_regulator_रेजिस्टर(&pdev->dev, &info->desc, &config);
	अगर (IS_ERR(rdev)) अणु
		dev_err(&pdev->dev, "can't register %s, %ld\n",
				info->desc.name, PTR_ERR(rdev));
		वापस PTR_ERR(rdev);
	पूर्ण
	platक्रमm_set_drvdata(pdev, rdev);

	twlreg_ग_लिखो(info, TWL_MODULE_PM_RECEIVER, VREG_REMAP, info->remap);

	/* NOTE:  many regulators support लघु-circuit IRQs (presentable
	 * as REGULATOR_OVER_CURRENT notअगरications?) configured via:
	 *  - SC_CONFIG
	 *  - SC_DETECT1 (vपूर्णांकana2, vmmc1/2, vaux1/2/3/4)
	 *  - SC_DETECT2 (vusb, vdac, vio, vdd1/2, vpll2)
	 *  - IT_CONFIG
	 */

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:twl4030_reg");

अटल काष्ठा platक्रमm_driver twlreg_driver = अणु
	.probe		= twlreg_probe,
	/* NOTE: लघु name, to work around driver model truncation of
	 * "twl_regulator.12" (and मित्रs) to "twl_regulator.1".
	 */
	.driver  = अणु
		.name  = "twl4030_reg",
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

MODULE_DESCRIPTION("TWL4030 regulator driver");
MODULE_LICENSE("GPL");
