<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// MCP16502 PMIC driver
//
// Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries
//
// Author: Andrei Stefanescu <andrei.stefanescu@microchip.com>
//
// Inspired from tps65086-regulator.c

#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/suspend.h>
#समावेश <linux/gpio/consumer.h>

#घोषणा VDD_LOW_SEL 0x0D
#घोषणा VDD_HIGH_SEL 0x3F

#घोषणा MCP16502_FLT		BIT(7)
#घोषणा MCP16502_DVSR		GENMASK(3, 2)
#घोषणा MCP16502_ENS		BIT(0)

/*
 * The PMIC has four sets of रेजिस्टरs corresponding to four घातer modes:
 * Perक्रमmance, Active, Low-घातer, Hibernate.
 *
 * Registers:
 * Each regulator has a रेजिस्टर क्रम each घातer mode. To access a रेजिस्टर
 * क्रम a specअगरic regulator and mode BASE_* and OFFSET_* need to be added.
 *
 * Operating modes:
 * In order क्रम the PMIC to transition to operating modes it has to be
 * controlled via GPIO lines called LPM and HPM.
 *
 * The रेजिस्टरs are fully configurable such that you can put all regulators in
 * a low-घातer state जबतक the PMIC is in Active mode. They are supposed to be
 * configured at startup and then simply transition to/from a global low-घातer
 * state by setting the GPIO lpm pin high/low.
 *
 * This driver keeps the PMIC in Active mode, Low-घातer state is set क्रम the
 * regulators by enabling/disabling operating mode (FPWM or Auto PFM).
 *
 * The PMIC's Low-घातer and Hibernate modes are used during standby/suspend.
 * To enter standby/suspend the PMIC will go to Low-घातer mode. From there, it
 * will transition to Hibernate when the PWRHLD line is set to low by the MPU.
 */

/*
 * This function is useful क्रम iterating over all regulators and accessing their
 * रेजिस्टरs in a generic way or accessing a regulator device by its id.
 */
#घोषणा MCP16502_REG_BASE(i, r) ((((i) + 1) << 4) + MCP16502_REG_##r)
#घोषणा MCP16502_STAT_BASE(i) ((i) + 5)

#घोषणा MCP16502_OPMODE_ACTIVE REGULATOR_MODE_NORMAL
#घोषणा MCP16502_OPMODE_LPM REGULATOR_MODE_IDLE
#घोषणा MCP16502_OPMODE_HIB REGULATOR_MODE_STANDBY

#घोषणा MCP16502_MODE_AUTO_PFM 0
#घोषणा MCP16502_MODE_FPWM BIT(6)

#घोषणा MCP16502_VSEL 0x3F
#घोषणा MCP16502_EN BIT(7)
#घोषणा MCP16502_MODE BIT(6)

#घोषणा MCP16502_MIN_REG 0x0
#घोषणा MCP16502_MAX_REG 0x65

/**
 * क्रमागत mcp16502_reg - MCP16502 regulators's रेजिस्टरs
 * @MCP16502_REG_A: active state रेजिस्टर
 * @MCP16502_REG_LPM: low घातer mode state रेजिस्टर
 * @MCP16502_REG_HIB: hibernate state रेजिस्टर
 * @MCP16502_REG_SEQ: startup sequence रेजिस्टर
 * @MCP16502_REG_CFG: configuration रेजिस्टर
 */
क्रमागत mcp16502_reg अणु
	MCP16502_REG_A,
	MCP16502_REG_LPM,
	MCP16502_REG_HIB,
	MCP16502_REG_HPM,
	MCP16502_REG_SEQ,
	MCP16502_REG_CFG,
पूर्ण;

/* Ramp delay (uV/us) क्रम buck1, lकरो1, lकरो2. */
अटल स्थिर पूर्णांक mcp16502_ramp_b1l12[] = अणु 6250, 3125, 2083, 1563 पूर्ण;

/* Ramp delay (uV/us) क्रम buck2, buck3, buck4. */
अटल स्थिर पूर्णांक mcp16502_ramp_b234[] = अणु 3125, 1563, 1042, 781 पूर्ण;

अटल अचिन्हित पूर्णांक mcp16502_of_map_mode(अचिन्हित पूर्णांक mode)
अणु
	अगर (mode == REGULATOR_MODE_NORMAL || mode == REGULATOR_MODE_IDLE)
		वापस mode;

	वापस REGULATOR_MODE_INVALID;
पूर्ण

#घोषणा MCP16502_REGULATOR(_name, _id, _ranges, _ops)			\
	[_id] = अणु							\
		.name			= _name,			\
		.regulators_node	= of_match_ptr("regulators"),	\
		.id			= _id,				\
		.ops			= &(_ops),			\
		.type			= REGULATOR_VOLTAGE,		\
		.owner			= THIS_MODULE,			\
		.n_voltages		= MCP16502_VSEL + 1,		\
		.linear_ranges		= _ranges,			\
		.linear_min_sel		= VDD_LOW_SEL,			\
		.n_linear_ranges	= ARRAY_SIZE(_ranges),		\
		.of_match		= of_match_ptr(_name),		\
		.of_map_mode		= mcp16502_of_map_mode,		\
		.vsel_reg		= (((_id) + 1) << 4),		\
		.vsel_mask		= MCP16502_VSEL,		\
		.enable_reg		= (((_id) + 1) << 4),		\
		.enable_mask		= MCP16502_EN,			\
	पूर्ण

क्रमागत अणु
	BUCK1 = 0,
	BUCK2,
	BUCK3,
	BUCK4,
	LDO1,
	LDO2,
	NUM_REGULATORS
पूर्ण;

/*
 * काष्ठा mcp16502 - PMIC representation
 * @lpm: LPM GPIO descriptor
 */
काष्ठा mcp16502 अणु
	काष्ठा gpio_desc *lpm;
पूर्ण;

/*
 * mcp16502_gpio_set_mode() - set the GPIO corresponding value
 *
 * Used to prepare transitioning पूर्णांकo hibernate or resuming from it.
 */
अटल व्योम mcp16502_gpio_set_mode(काष्ठा mcp16502 *mcp, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल MCP16502_OPMODE_ACTIVE:
		gpiod_set_value(mcp->lpm, 0);
		अवरोध;
	हाल MCP16502_OPMODE_LPM:
	हाल MCP16502_OPMODE_HIB:
		gpiod_set_value(mcp->lpm, 1);
		अवरोध;
	शेष:
		pr_err("%s: %d invalid\n", __func__, mode);
	पूर्ण
पूर्ण

/*
 * mcp16502_get_reg() - get the PMIC's state configuration रेजिस्टर क्रम opmode
 *
 * @rdev: the regulator whose रेजिस्टर we are searching
 * @opmode: the PMIC's operating mode ACTIVE, Low-घातer, Hibernate
 */
अटल पूर्णांक mcp16502_get_state_reg(काष्ठा regulator_dev *rdev, पूर्णांक opmode)
अणु
	चयन (opmode) अणु
	हाल MCP16502_OPMODE_ACTIVE:
		वापस MCP16502_REG_BASE(rdev_get_id(rdev), A);
	हाल MCP16502_OPMODE_LPM:
		वापस MCP16502_REG_BASE(rdev_get_id(rdev), LPM);
	हाल MCP16502_OPMODE_HIB:
		वापस MCP16502_REG_BASE(rdev_get_id(rdev), HIB);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * mcp16502_get_mode() - वापस the current operating mode of a regulator
 *
 * Note: all functions that are not part of entering/निकासing standby/suspend
 *	 use the Active mode रेजिस्टरs.
 *
 * Note: this is dअगरferent from the PMIC's operatig mode, it is the
 *	 MODE bit from the regulator's रेजिस्टर.
 */
अटल अचिन्हित पूर्णांक mcp16502_get_mode(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, reg;

	reg = mcp16502_get_state_reg(rdev, MCP16502_OPMODE_ACTIVE);
	अगर (reg < 0)
		वापस reg;

	ret = regmap_पढ़ो(rdev->regmap, reg, &val);
	अगर (ret)
		वापस ret;

	चयन (val & MCP16502_MODE) अणु
	हाल MCP16502_MODE_FPWM:
		वापस REGULATOR_MODE_NORMAL;
	हाल MCP16502_MODE_AUTO_PFM:
		वापस REGULATOR_MODE_IDLE;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

/*
 * _mcp16502_set_mode() - helper क्रम set_mode and set_suspend_mode
 *
 * @rdev: the regulator क्रम which we are setting the mode
 * @mode: the regulator's mode (the one from MODE bit)
 * @opmode: the PMIC's operating mode: Active/Low-घातer/Hibernate
 */
अटल पूर्णांक _mcp16502_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode,
			      अचिन्हित पूर्णांक op_mode)
अणु
	पूर्णांक val;
	पूर्णांक reg;

	reg = mcp16502_get_state_reg(rdev, op_mode);
	अगर (reg < 0)
		वापस reg;

	चयन (mode) अणु
	हाल REGULATOR_MODE_NORMAL:
		val = MCP16502_MODE_FPWM;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:
		val = MCP16502_MODE_AUTO_PFM;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg = regmap_update_bits(rdev->regmap, reg, MCP16502_MODE, val);
	वापस reg;
पूर्ण

/*
 * mcp16502_set_mode() - regulator_ops set_mode
 */
अटल पूर्णांक mcp16502_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	वापस _mcp16502_set_mode(rdev, mode, MCP16502_OPMODE_ACTIVE);
पूर्ण

/*
 * mcp16502_get_status() - regulator_ops get_status
 */
अटल पूर्णांक mcp16502_get_status(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(rdev->regmap, MCP16502_STAT_BASE(rdev_get_id(rdev)),
			  &val);
	अगर (ret)
		वापस ret;

	अगर (val & MCP16502_FLT)
		वापस REGULATOR_STATUS_ERROR;
	अन्यथा अगर (val & MCP16502_ENS)
		वापस REGULATOR_STATUS_ON;
	अन्यथा अगर (!(val & MCP16502_ENS))
		वापस REGULATOR_STATUS_OFF;

	वापस REGULATOR_STATUS_UNDEFINED;
पूर्ण

अटल पूर्णांक mcp16502_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
					 अचिन्हित पूर्णांक old_sel,
					 अचिन्हित पूर्णांक new_sel)
अणु
	अटल स्थिर u8 us_ramp[] = अणु 8, 16, 24, 32 पूर्ण;
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक uV_delta, val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, MCP16502_REG_BASE(id, CFG), &val);
	अगर (ret)
		वापस ret;

	val = (val & MCP16502_DVSR) >> 2;
	uV_delta = असल(new_sel * rdev->desc->linear_ranges->step -
		       old_sel * rdev->desc->linear_ranges->step);
	चयन (id) अणु
	हाल BUCK1:
	हाल LDO1:
	हाल LDO2:
		ret = DIV_ROUND_CLOSEST(uV_delta * us_ramp[val],
					mcp16502_ramp_b1l12[val]);
		अवरोध;

	हाल BUCK2:
	हाल BUCK3:
	हाल BUCK4:
		ret = DIV_ROUND_CLOSEST(uV_delta * us_ramp[val],
					mcp16502_ramp_b234[val]);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mcp16502_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	स्थिर पूर्णांक *ramp;
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक i, size;

	चयन (id) अणु
	हाल BUCK1:
	हाल LDO1:
	हाल LDO2:
		ramp = mcp16502_ramp_b1l12;
		size = ARRAY_SIZE(mcp16502_ramp_b1l12);
		अवरोध;

	हाल BUCK2:
	हाल BUCK3:
	हाल BUCK4:
		ramp = mcp16502_ramp_b234;
		size = ARRAY_SIZE(mcp16502_ramp_b234);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		अगर (ramp[i] == ramp_delay)
			अवरोध;
	पूर्ण
	अगर (i == size)
		वापस -EINVAL;

	वापस regmap_update_bits(rdev->regmap, MCP16502_REG_BASE(id, CFG),
				  MCP16502_DVSR, (i << 2));
पूर्ण

#अगर_घोषित CONFIG_SUSPEND
/*
 * mcp16502_suspend_get_target_reg() - get the reg of the target suspend PMIC
 *				       mode
 */
अटल पूर्णांक mcp16502_suspend_get_target_reg(काष्ठा regulator_dev *rdev)
अणु
	चयन (pm_suspend_target_state) अणु
	हाल PM_SUSPEND_STANDBY:
		वापस mcp16502_get_state_reg(rdev, MCP16502_OPMODE_LPM);
	हाल PM_SUSPEND_ON:
	हाल PM_SUSPEND_MEM:
		वापस mcp16502_get_state_reg(rdev, MCP16502_OPMODE_HIB);
	शेष:
		dev_err(&rdev->dev, "invalid suspend target: %d\n",
			pm_suspend_target_state);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * mcp16502_set_suspend_voltage() - regulator_ops set_suspend_voltage
 */
अटल पूर्णांक mcp16502_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uV)
अणु
	पूर्णांक sel = regulator_map_voltage_linear_range(rdev, uV, uV);
	पूर्णांक reg = mcp16502_suspend_get_target_reg(rdev);

	अगर (sel < 0)
		वापस sel;

	अगर (reg < 0)
		वापस reg;

	वापस regmap_update_bits(rdev->regmap, reg, MCP16502_VSEL, sel);
पूर्ण

/*
 * mcp16502_set_suspend_mode() - regulator_ops set_suspend_mode
 */
अटल पूर्णांक mcp16502_set_suspend_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	चयन (pm_suspend_target_state) अणु
	हाल PM_SUSPEND_STANDBY:
		वापस _mcp16502_set_mode(rdev, mode, MCP16502_OPMODE_LPM);
	हाल PM_SUSPEND_ON:
	हाल PM_SUSPEND_MEM:
		वापस _mcp16502_set_mode(rdev, mode, MCP16502_OPMODE_HIB);
	शेष:
		dev_err(&rdev->dev, "invalid suspend target: %d\n",
			pm_suspend_target_state);
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * mcp16502_set_suspend_enable() - regulator_ops set_suspend_enable
 */
अटल पूर्णांक mcp16502_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक reg = mcp16502_suspend_get_target_reg(rdev);

	अगर (reg < 0)
		वापस reg;

	वापस regmap_update_bits(rdev->regmap, reg, MCP16502_EN, MCP16502_EN);
पूर्ण

/*
 * mcp16502_set_suspend_disable() - regulator_ops set_suspend_disable
 */
अटल पूर्णांक mcp16502_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक reg = mcp16502_suspend_get_target_reg(rdev);

	अगर (reg < 0)
		वापस reg;

	वापस regmap_update_bits(rdev->regmap, reg, MCP16502_EN, 0);
पूर्ण
#पूर्ण_अगर /* CONFIG_SUSPEND */

अटल स्थिर काष्ठा regulator_ops mcp16502_buck_ops = अणु
	.list_voltage			= regulator_list_voltage_linear_range,
	.map_voltage			= regulator_map_voltage_linear_range,
	.get_voltage_sel		= regulator_get_voltage_sel_regmap,
	.set_voltage_sel		= regulator_set_voltage_sel_regmap,
	.enable				= regulator_enable_regmap,
	.disable			= regulator_disable_regmap,
	.is_enabled			= regulator_is_enabled_regmap,
	.get_status			= mcp16502_get_status,
	.set_voltage_समय_sel		= mcp16502_set_voltage_समय_sel,
	.set_ramp_delay			= mcp16502_set_ramp_delay,

	.set_mode			= mcp16502_set_mode,
	.get_mode			= mcp16502_get_mode,

#अगर_घोषित CONFIG_SUSPEND
	.set_suspend_voltage		= mcp16502_set_suspend_voltage,
	.set_suspend_mode		= mcp16502_set_suspend_mode,
	.set_suspend_enable		= mcp16502_set_suspend_enable,
	.set_suspend_disable		= mcp16502_set_suspend_disable,
#पूर्ण_अगर /* CONFIG_SUSPEND */
पूर्ण;

/*
 * LDOs cannot change operating modes.
 */
अटल स्थिर काष्ठा regulator_ops mcp16502_lकरो_ops = अणु
	.list_voltage			= regulator_list_voltage_linear_range,
	.map_voltage			= regulator_map_voltage_linear_range,
	.get_voltage_sel		= regulator_get_voltage_sel_regmap,
	.set_voltage_sel		= regulator_set_voltage_sel_regmap,
	.enable				= regulator_enable_regmap,
	.disable			= regulator_disable_regmap,
	.is_enabled			= regulator_is_enabled_regmap,
	.get_status			= mcp16502_get_status,
	.set_voltage_समय_sel		= mcp16502_set_voltage_समय_sel,
	.set_ramp_delay			= mcp16502_set_ramp_delay,

#अगर_घोषित CONFIG_SUSPEND
	.set_suspend_voltage		= mcp16502_set_suspend_voltage,
	.set_suspend_enable		= mcp16502_set_suspend_enable,
	.set_suspend_disable		= mcp16502_set_suspend_disable,
#पूर्ण_अगर /* CONFIG_SUSPEND */
पूर्ण;

अटल स्थिर काष्ठा of_device_id mcp16502_ids[] = अणु
	अणु .compatible = "microchip,mcp16502", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp16502_ids);

अटल स्थिर काष्ठा linear_range b1l12_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1200000, VDD_LOW_SEL, VDD_HIGH_SEL, 50000),
पूर्ण;

अटल स्थिर काष्ठा linear_range b234_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(600000, VDD_LOW_SEL, VDD_HIGH_SEL, 25000),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc mcp16502_desc[] = अणु
	/* MCP16502_REGULATOR(_name, _id, ranges, regulator_ops) */
	MCP16502_REGULATOR("VDD_IO", BUCK1, b1l12_ranges, mcp16502_buck_ops),
	MCP16502_REGULATOR("VDD_DDR", BUCK2, b234_ranges, mcp16502_buck_ops),
	MCP16502_REGULATOR("VDD_CORE", BUCK3, b234_ranges, mcp16502_buck_ops),
	MCP16502_REGULATOR("VDD_OTHER", BUCK4, b234_ranges, mcp16502_buck_ops),
	MCP16502_REGULATOR("LDO1", LDO1, b1l12_ranges, mcp16502_lकरो_ops),
	MCP16502_REGULATOR("LDO2", LDO2, b1l12_ranges, mcp16502_lकरो_ops)
पूर्ण;

अटल स्थिर काष्ठा regmap_range mcp16502_ranges[] = अणु
	regmap_reg_range(MCP16502_MIN_REG, MCP16502_MAX_REG)
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table mcp16502_yes_reg_table = अणु
	.yes_ranges = mcp16502_ranges,
	.n_yes_ranges = ARRAY_SIZE(mcp16502_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config mcp16502_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= MCP16502_MAX_REG,
	.cache_type	= REGCACHE_NONE,
	.rd_table	= &mcp16502_yes_reg_table,
	.wr_table	= &mcp16502_yes_reg_table,
पूर्ण;

अटल पूर्णांक mcp16502_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा regulator_dev *rdev;
	काष्ठा device *dev;
	काष्ठा mcp16502 *mcp;
	काष्ठा regmap *rmap;
	पूर्णांक i, ret;

	dev = &client->dev;
	config.dev = dev;

	mcp = devm_kzalloc(dev, माप(*mcp), GFP_KERNEL);
	अगर (!mcp)
		वापस -ENOMEM;

	rmap = devm_regmap_init_i2c(client, &mcp16502_regmap_config);
	अगर (IS_ERR(rmap)) अणु
		ret = PTR_ERR(rmap);
		dev_err(dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, mcp);
	config.regmap = rmap;
	config.driver_data = mcp;

	mcp->lpm = devm_gpiod_get_optional(dev, "lpm", GPIOD_OUT_LOW);
	अगर (IS_ERR(mcp->lpm)) अणु
		dev_err(dev, "failed to get lpm pin: %ld\n", PTR_ERR(mcp->lpm));
		वापस PTR_ERR(mcp->lpm);
	पूर्ण

	क्रम (i = 0; i < NUM_REGULATORS; i++) अणु
		rdev = devm_regulator_रेजिस्टर(dev, &mcp16502_desc[i], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(dev,
				"failed to register %s regulator %ld\n",
				mcp16502_desc[i].name, PTR_ERR(rdev));
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	mcp16502_gpio_set_mode(mcp, MCP16502_OPMODE_ACTIVE);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mcp16502_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mcp16502 *mcp = i2c_get_clientdata(client);

	mcp16502_gpio_set_mode(mcp, MCP16502_OPMODE_LPM);

	वापस 0;
पूर्ण

अटल पूर्णांक mcp16502_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा mcp16502 *mcp = i2c_get_clientdata(client);

	mcp16502_gpio_set_mode(mcp, MCP16502_OPMODE_ACTIVE);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल स्थिर काष्ठा dev_pm_ops mcp16502_pm_ops = अणु
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(mcp16502_suspend_noirq,
				      mcp16502_resume_noirq)
पूर्ण;
#पूर्ण_अगर
अटल स्थिर काष्ठा i2c_device_id mcp16502_i2c_id[] = अणु
	अणु "mcp16502", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mcp16502_i2c_id);

अटल काष्ठा i2c_driver mcp16502_drv = अणु
	.probe		= mcp16502_probe,
	.driver		= अणु
		.name	= "mcp16502-regulator",
		.of_match_table	= of_match_ptr(mcp16502_ids),
#अगर_घोषित CONFIG_PM
		.pm = &mcp16502_pm_ops,
#पूर्ण_अगर
	पूर्ण,
	.id_table	= mcp16502_i2c_id,
पूर्ण;

module_i2c_driver(mcp16502_drv);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MCP16502 PMIC driver");
MODULE_AUTHOR("Andrei Stefanescu andrei.stefanescu@microchip.com");
