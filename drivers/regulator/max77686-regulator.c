<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max77686.c - Regulator driver क्रम the Maxim 77686
//
// Copyright (C) 2012 Samsung Electronics
// Chiwoong Byun <woong.byun@samsung.com>
// Jonghwa Lee <jonghwa3.lee@samsung.com>
//
// This driver is based on max8997.c

#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/max77686.h>
#समावेश <linux/mfd/max77686-निजी.h>

#घोषणा MAX77686_LDO_MINUV	800000
#घोषणा MAX77686_LDO_UVSTEP	50000
#घोषणा MAX77686_LDO_LOW_MINUV	800000
#घोषणा MAX77686_LDO_LOW_UVSTEP	25000
#घोषणा MAX77686_BUCK_MINUV	750000
#घोषणा MAX77686_BUCK_UVSTEP	50000
#घोषणा MAX77686_BUCK_ENABLE_TIME	40		/* us */
#घोषणा MAX77686_DVS_ENABLE_TIME	22		/* us */
#घोषणा MAX77686_RAMP_DELAY	100000			/* uV/us */
#घोषणा MAX77686_DVS_RAMP_DELAY	27500			/* uV/us */
#घोषणा MAX77686_DVS_MINUV	600000
#घोषणा MAX77686_DVS_UVSTEP	12500

/*
 * Value क्रम configuring buck[89] and LDOअणु20,21,22पूर्ण as GPIO control.
 * It is the same as 'off' क्रम other regulators.
 */
#घोषणा MAX77686_GPIO_CONTROL		0x0
/*
 * Values used क्रम configuring LDOs and bucks.
 * Forcing low घातer mode: LDO1, 3-5, 9, 13, 17-26
 */
#घोषणा MAX77686_LDO_LOWPOWER		0x1
/*
 * On/off controlled by PWRREQ:
 *  - LDO2, 6-8, 10-12, 14-16
 *  - buck[1234]
 */
#घोषणा MAX77686_OFF_PWRREQ		0x1
/* Low घातer mode controlled by PWRREQ: All LDOs */
#घोषणा MAX77686_LDO_LOWPOWER_PWRREQ	0x2
/* Forcing low घातer mode: buck[234] */
#घोषणा MAX77686_BUCK_LOWPOWER		0x2
#घोषणा MAX77686_NORMAL			0x3

#घोषणा MAX77686_OPMODE_SHIFT	6
#घोषणा MAX77686_OPMODE_BUCK234_SHIFT	4
#घोषणा MAX77686_OPMODE_MASK	0x3

#घोषणा MAX77686_VSEL_MASK	0x3F
#घोषणा MAX77686_DVS_VSEL_MASK	0xFF

#घोषणा MAX77686_RAMP_RATE_MASK	0xC0

#घोषणा MAX77686_REGULATORS	MAX77686_REG_MAX
#घोषणा MAX77686_LDOS		26

क्रमागत max77686_ramp_rate अणु
	RAMP_RATE_13P75MV,
	RAMP_RATE_27P5MV,
	RAMP_RATE_55MV,
	RAMP_RATE_NO_CTRL,	/* 100mV/us */
पूर्ण;

काष्ठा max77686_data अणु
	काष्ठा device *dev;
	DECLARE_BITMAP(gpio_enabled, MAX77686_REGULATORS);

	/* Array indexed by regulator id */
	अचिन्हित पूर्णांक opmode[MAX77686_REGULATORS];
पूर्ण;

अटल अचिन्हित पूर्णांक max77686_get_opmode_shअगरt(पूर्णांक id)
अणु
	चयन (id) अणु
	हाल MAX77686_BUCK1:
	हाल MAX77686_BUCK5 ... MAX77686_BUCK9:
		वापस 0;
	हाल MAX77686_BUCK2 ... MAX77686_BUCK4:
		वापस MAX77686_OPMODE_BUCK234_SHIFT;
	शेष:
		/* all LDOs */
		वापस MAX77686_OPMODE_SHIFT;
	पूर्ण
पूर्ण

/*
 * When regulator is configured क्रम GPIO control then it
 * replaces "normal" mode. Any change from low घातer mode to normal
 * should actually change to GPIO control.
 * Map normal mode to proper value क्रम such regulators.
 */
अटल अचिन्हित पूर्णांक max77686_map_normal_mode(काष्ठा max77686_data *max77686,
					     पूर्णांक id)
अणु
	चयन (id) अणु
	हाल MAX77686_BUCK8:
	हाल MAX77686_BUCK9:
	हाल MAX77686_LDO20 ... MAX77686_LDO22:
		अगर (test_bit(id, max77686->gpio_enabled))
			वापस MAX77686_GPIO_CONTROL;
	पूर्ण

	वापस MAX77686_NORMAL;
पूर्ण

/* Some BUCKs and LDOs supports Normal[ON/OFF] mode during suspend */
अटल पूर्णांक max77686_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val, shअगरt;
	काष्ठा max77686_data *max77686 = rdev_get_drvdata(rdev);
	पूर्णांक ret, id = rdev_get_id(rdev);

	shअगरt = max77686_get_opmode_shअगरt(id);
	val = MAX77686_OFF_PWRREQ;

	ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				 rdev->desc->enable_mask, val << shअगरt);
	अगर (ret)
		वापस ret;

	max77686->opmode[id] = val;
	वापस 0;
पूर्ण

/* Some LDOs supports [LPM/Normal]ON mode during suspend state */
अटल पूर्णांक max77686_set_suspend_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	काष्ठा max77686_data *max77686 = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, id = rdev_get_id(rdev);

	/* BUCK[5-9] करोesn't support this feature */
	अगर (id >= MAX77686_BUCK5)
		वापस 0;

	चयन (mode) अणु
	हाल REGULATOR_MODE_IDLE:			/* ON in LP Mode */
		val = MAX77686_LDO_LOWPOWER_PWRREQ;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:			/* ON in Normal Mode */
		val = max77686_map_normal_mode(max77686, id);
		अवरोध;
	शेष:
		pr_warn("%s: regulator_suspend_mode : 0x%x not supported\n",
			rdev->desc->name, mode);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask,
				  val << MAX77686_OPMODE_SHIFT);
	अगर (ret)
		वापस ret;

	max77686->opmode[id] = val;
	वापस 0;
पूर्ण

/* Some LDOs supports LPM-ON/OFF/Normal-ON mode during suspend state */
अटल पूर्णांक max77686_lकरो_set_suspend_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा max77686_data *max77686 = rdev_get_drvdata(rdev);
	पूर्णांक ret, id = rdev_get_id(rdev);

	चयन (mode) अणु
	हाल REGULATOR_MODE_STANDBY:			/* चयन off */
		val = MAX77686_OFF_PWRREQ;
		अवरोध;
	हाल REGULATOR_MODE_IDLE:			/* ON in LP Mode */
		val = MAX77686_LDO_LOWPOWER_PWRREQ;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:			/* ON in Normal Mode */
		val = max77686_map_normal_mode(max77686, id);
		अवरोध;
	शेष:
		pr_warn("%s: regulator_suspend_mode : 0x%x not supported\n",
			rdev->desc->name, mode);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				 rdev->desc->enable_mask,
				 val << MAX77686_OPMODE_SHIFT);
	अगर (ret)
		वापस ret;

	max77686->opmode[id] = val;
	वापस 0;
पूर्ण

अटल पूर्णांक max77686_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77686_data *max77686 = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक shअगरt;
	पूर्णांक id = rdev_get_id(rdev);

	shअगरt = max77686_get_opmode_shअगरt(id);

	अगर (max77686->opmode[id] == MAX77686_OFF_PWRREQ)
		max77686->opmode[id] = max77686_map_normal_mode(max77686, id);

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask,
				  max77686->opmode[id] << shअगरt);
पूर्ण

अटल पूर्णांक max77686_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	अचिन्हित पूर्णांक ramp_value = RAMP_RATE_NO_CTRL;

	चयन (ramp_delay) अणु
	हाल 1 ... 13750:
		ramp_value = RAMP_RATE_13P75MV;
		अवरोध;
	हाल 13751 ... 27500:
		ramp_value = RAMP_RATE_27P5MV;
		अवरोध;
	हाल 27501 ... 55000:
		ramp_value = RAMP_RATE_55MV;
		अवरोध;
	हाल 55001 ... 100000:
		अवरोध;
	शेष:
		pr_warn("%s: ramp_delay: %d not supported, setting 100000\n",
			rdev->desc->name, ramp_delay);
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  MAX77686_RAMP_RATE_MASK, ramp_value << 6);
पूर्ण

अटल पूर्णांक max77686_of_parse_cb(काष्ठा device_node *np,
		स्थिर काष्ठा regulator_desc *desc,
		काष्ठा regulator_config *config)
अणु
	काष्ठा max77686_data *max77686 = config->driver_data;
	पूर्णांक ret;

	चयन (desc->id) अणु
	हाल MAX77686_BUCK8:
	हाल MAX77686_BUCK9:
	हाल MAX77686_LDO20 ... MAX77686_LDO22:
		config->ena_gpiod = fwnode_gpiod_get_index(
				of_fwnode_handle(np),
				"maxim,ena",
				0,
				GPIOD_OUT_HIGH | GPIOD_FLAGS_BIT_NONEXCLUSIVE,
				"max77686-regulator");
		अगर (IS_ERR(config->ena_gpiod))
			config->ena_gpiod = शून्य;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (config->ena_gpiod) अणु
		set_bit(desc->id, max77686->gpio_enabled);

		ret = regmap_update_bits(config->regmap, desc->enable_reg,
					 desc->enable_mask,
					 MAX77686_GPIO_CONTROL);
		अगर (ret) अणु
			gpiod_put(config->ena_gpiod);
			config->ena_gpiod = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regulator_ops max77686_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77686_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_mode	= max77686_set_suspend_mode,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77686_lकरो_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77686_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_mode	= max77686_lकरो_set_suspend_mode,
	.set_suspend_disable	= max77686_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77686_buck1_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77686_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_disable	= max77686_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops max77686_buck_dvs_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77686_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= max77686_set_ramp_delay,
	.set_suspend_disable	= max77686_set_suspend_disable,
पूर्ण;

#घोषणा regulator_desc_lकरो(num)		अणु				\
	.name		= "LDO"#num,					\
	.of_match	= of_match_ptr("LDO"#num),			\
	.regulators_node	= of_match_ptr("voltage-regulators"),	\
	.of_parse_cb	= max77686_of_parse_cb,				\
	.id		= MAX77686_LDO##num,				\
	.ops		= &max77686_ops,				\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= MAX77686_LDO_MINUV,				\
	.uV_step	= MAX77686_LDO_UVSTEP,				\
	.ramp_delay	= MAX77686_RAMP_DELAY,				\
	.n_voltages	= MAX77686_VSEL_MASK + 1,			\
	.vsel_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.vsel_mask	= MAX77686_VSEL_MASK,				\
	.enable_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.enable_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
पूर्ण
#घोषणा regulator_desc_lpm_lकरो(num)	अणु				\
	.name		= "LDO"#num,					\
	.of_match	= of_match_ptr("LDO"#num),			\
	.regulators_node	= of_match_ptr("voltage-regulators"),	\
	.id		= MAX77686_LDO##num,				\
	.ops		= &max77686_lकरो_ops,				\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= MAX77686_LDO_MINUV,				\
	.uV_step	= MAX77686_LDO_UVSTEP,				\
	.ramp_delay	= MAX77686_RAMP_DELAY,				\
	.n_voltages	= MAX77686_VSEL_MASK + 1,			\
	.vsel_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.vsel_mask	= MAX77686_VSEL_MASK,				\
	.enable_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.enable_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
पूर्ण
#घोषणा regulator_desc_lकरो_low(num)		अणु			\
	.name		= "LDO"#num,					\
	.of_match	= of_match_ptr("LDO"#num),			\
	.regulators_node	= of_match_ptr("voltage-regulators"),	\
	.id		= MAX77686_LDO##num,				\
	.ops		= &max77686_lकरो_ops,				\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= MAX77686_LDO_LOW_MINUV,			\
	.uV_step	= MAX77686_LDO_LOW_UVSTEP,			\
	.ramp_delay	= MAX77686_RAMP_DELAY,				\
	.n_voltages	= MAX77686_VSEL_MASK + 1,			\
	.vsel_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.vsel_mask	= MAX77686_VSEL_MASK,				\
	.enable_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.enable_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
पूर्ण
#घोषणा regulator_desc_lकरो1_low(num)		अणु			\
	.name		= "LDO"#num,					\
	.of_match	= of_match_ptr("LDO"#num),			\
	.regulators_node	= of_match_ptr("voltage-regulators"),	\
	.id		= MAX77686_LDO##num,				\
	.ops		= &max77686_ops,				\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= MAX77686_LDO_LOW_MINUV,			\
	.uV_step	= MAX77686_LDO_LOW_UVSTEP,			\
	.ramp_delay	= MAX77686_RAMP_DELAY,				\
	.n_voltages	= MAX77686_VSEL_MASK + 1,			\
	.vsel_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.vsel_mask	= MAX77686_VSEL_MASK,				\
	.enable_reg	= MAX77686_REG_LDO1CTRL1 + num - 1,		\
	.enable_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_SHIFT,			\
पूर्ण
#घोषणा regulator_desc_buck(num)		अणु			\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptr("BUCK"#num),			\
	.regulators_node	= of_match_ptr("voltage-regulators"),	\
	.of_parse_cb	= max77686_of_parse_cb,				\
	.id		= MAX77686_BUCK##num,				\
	.ops		= &max77686_ops,				\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= MAX77686_BUCK_MINUV,				\
	.uV_step	= MAX77686_BUCK_UVSTEP,				\
	.ramp_delay	= MAX77686_RAMP_DELAY,				\
	.enable_समय	= MAX77686_BUCK_ENABLE_TIME,			\
	.n_voltages	= MAX77686_VSEL_MASK + 1,			\
	.vsel_reg	= MAX77686_REG_BUCK5OUT + (num - 5) * 2,	\
	.vsel_mask	= MAX77686_VSEL_MASK,				\
	.enable_reg	= MAX77686_REG_BUCK5CTRL + (num - 5) * 2,	\
	.enable_mask	= MAX77686_OPMODE_MASK,				\
पूर्ण
#घोषणा regulator_desc_buck1(num)		अणु			\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptr("BUCK"#num),			\
	.regulators_node	= of_match_ptr("voltage-regulators"),	\
	.id		= MAX77686_BUCK##num,				\
	.ops		= &max77686_buck1_ops,				\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= MAX77686_BUCK_MINUV,				\
	.uV_step	= MAX77686_BUCK_UVSTEP,				\
	.ramp_delay	= MAX77686_RAMP_DELAY,				\
	.enable_समय	= MAX77686_BUCK_ENABLE_TIME,			\
	.n_voltages	= MAX77686_VSEL_MASK + 1,			\
	.vsel_reg	= MAX77686_REG_BUCK1OUT,			\
	.vsel_mask	= MAX77686_VSEL_MASK,				\
	.enable_reg	= MAX77686_REG_BUCK1CTRL,			\
	.enable_mask	= MAX77686_OPMODE_MASK,				\
पूर्ण
#घोषणा regulator_desc_buck_dvs(num)		अणु			\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptr("BUCK"#num),			\
	.regulators_node	= of_match_ptr("voltage-regulators"),	\
	.id		= MAX77686_BUCK##num,				\
	.ops		= &max77686_buck_dvs_ops,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= MAX77686_DVS_MINUV,				\
	.uV_step	= MAX77686_DVS_UVSTEP,				\
	.ramp_delay	= MAX77686_DVS_RAMP_DELAY,			\
	.enable_समय	= MAX77686_DVS_ENABLE_TIME,			\
	.n_voltages	= MAX77686_DVS_VSEL_MASK + 1,			\
	.vsel_reg	= MAX77686_REG_BUCK2DVS1 + (num - 2) * 10,	\
	.vsel_mask	= MAX77686_DVS_VSEL_MASK,			\
	.enable_reg	= MAX77686_REG_BUCK2CTRL1 + (num - 2) * 10,	\
	.enable_mask	= MAX77686_OPMODE_MASK				\
			<< MAX77686_OPMODE_BUCK234_SHIFT,		\
पूर्ण

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	regulator_desc_lकरो1_low(1),
	regulator_desc_lकरो_low(2),
	regulator_desc_lकरो(3),
	regulator_desc_lकरो(4),
	regulator_desc_lकरो(5),
	regulator_desc_lकरो_low(6),
	regulator_desc_lकरो_low(7),
	regulator_desc_lकरो_low(8),
	regulator_desc_lकरो(9),
	regulator_desc_lpm_lकरो(10),
	regulator_desc_lpm_lकरो(11),
	regulator_desc_lpm_lकरो(12),
	regulator_desc_lकरो(13),
	regulator_desc_lpm_lकरो(14),
	regulator_desc_lकरो_low(15),
	regulator_desc_lpm_lकरो(16),
	regulator_desc_lकरो(17),
	regulator_desc_lकरो(18),
	regulator_desc_lकरो(19),
	regulator_desc_lकरो(20),
	regulator_desc_lकरो(21),
	regulator_desc_lकरो(22),
	regulator_desc_lकरो(23),
	regulator_desc_lकरो(24),
	regulator_desc_lकरो(25),
	regulator_desc_lकरो(26),
	regulator_desc_buck1(1),
	regulator_desc_buck_dvs(2),
	regulator_desc_buck_dvs(3),
	regulator_desc_buck_dvs(4),
	regulator_desc_buck(5),
	regulator_desc_buck(6),
	regulator_desc_buck(7),
	regulator_desc_buck(8),
	regulator_desc_buck(9),
पूर्ण;

अटल पूर्णांक max77686_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77686_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77686_data *max77686;
	पूर्णांक i;
	काष्ठा regulator_config config = अणु पूर्ण;

	dev_dbg(&pdev->dev, "%s\n", __func__);

	max77686 = devm_kzalloc(&pdev->dev, माप(काष्ठा max77686_data),
				GFP_KERNEL);
	अगर (!max77686)
		वापस -ENOMEM;

	max77686->dev = &pdev->dev;
	config.dev = iodev->dev;
	config.regmap = iodev->regmap;
	config.driver_data = max77686;
	platक्रमm_set_drvdata(pdev, max77686);

	क्रम (i = 0; i < MAX77686_REGULATORS; i++) अणु
		काष्ठा regulator_dev *rdev;
		पूर्णांक id = regulators[i].id;

		max77686->opmode[id] = MAX77686_NORMAL;
		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
						&regulators[i], &config);
		अगर (IS_ERR(rdev)) अणु
			पूर्णांक ret = PTR_ERR(rdev);
			dev_err(&pdev->dev,
				"regulator init failed for %d: %d\n", i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77686_pmic_id[] = अणु
	अणु"max77686-pmic", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77686_pmic_id);

अटल काष्ठा platक्रमm_driver max77686_pmic_driver = अणु
	.driver = अणु
		.name = "max77686-pmic",
	पूर्ण,
	.probe = max77686_pmic_probe,
	.id_table = max77686_pmic_id,
पूर्ण;

module_platक्रमm_driver(max77686_pmic_driver);

MODULE_DESCRIPTION("MAXIM 77686 Regulator Driver");
MODULE_AUTHOR("Chiwoong Byun <woong.byun@samsung.com>");
MODULE_LICENSE("GPL");
