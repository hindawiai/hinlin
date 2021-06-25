<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// max77802.c - Regulator driver क्रम the Maxim 77802
//
// Copyright (C) 2013-2014 Google, Inc
// Simon Glass <sjg@chromium.org>
//
// Copyright (C) 2012 Samsung Electronics
// Chiwoong Byun <woong.byun@samsung.com>
// Jonghwa Lee <jonghwa3.lee@samsung.com>
//
// This driver is based on max8997.c

#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/max77686.h>
#समावेश <linux/mfd/max77686-निजी.h>
#समावेश <dt-bindings/regulator/maxim,max77802.h>

/* Default ramp delay in हाल it is not manually set */
#घोषणा MAX77802_RAMP_DELAY		100000		/* uV/us */

#घोषणा MAX77802_OPMODE_SHIFT_LDO	6
#घोषणा MAX77802_OPMODE_BUCK234_SHIFT	4
#घोषणा MAX77802_OPMODE_MASK		0x3

#घोषणा MAX77802_VSEL_MASK		0x3F
#घोषणा MAX77802_DVS_VSEL_MASK		0xFF

#घोषणा MAX77802_RAMP_RATE_MASK_2BIT	0xC0
#घोषणा MAX77802_RAMP_RATE_SHIFT_2BIT	6
#घोषणा MAX77802_RAMP_RATE_MASK_4BIT	0xF0
#घोषणा MAX77802_RAMP_RATE_SHIFT_4BIT	4

#घोषणा MAX77802_STATUS_OFF		0x0
#घोषणा MAX77802_OFF_PWRREQ		0x1
#घोषणा MAX77802_LP_PWRREQ		0x2

/* MAX77802 has two रेजिस्टर क्रमmats: 2-bit and 4-bit */
अटल स्थिर अचिन्हित पूर्णांक ramp_table_77802_2bit[] = अणु
	12500,
	25000,
	50000,
	100000,
पूर्ण;

अटल अचिन्हित पूर्णांक ramp_table_77802_4bit[] = अणु
	1000,	2000,	3030,	4000,
	5000,	5880,	7140,	8330,
	9090,	10000,	11110,	12500,
	16670,	25000,	50000,	100000,
पूर्ण;

काष्ठा max77802_regulator_prv अणु
	/* Array indexed by regulator id */
	अचिन्हित पूर्णांक opmode[MAX77802_REG_MAX];
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक max77802_map_mode(अचिन्हित पूर्णांक mode)
अणु
	वापस mode == MAX77802_OPMODE_NORMAL ?
		REGULATOR_MODE_NORMAL : REGULATOR_MODE_STANDBY;
पूर्ण

अटल पूर्णांक max77802_get_opmode_shअगरt(पूर्णांक id)
अणु
	अगर (id == MAX77802_BUCK1 || (id >= MAX77802_BUCK5 &&
				     id <= MAX77802_BUCK10))
		वापस 0;

	अगर (id >= MAX77802_BUCK2 && id <= MAX77802_BUCK4)
		वापस MAX77802_OPMODE_BUCK234_SHIFT;

	अगर (id >= MAX77802_LDO1 && id <= MAX77802_LDO35)
		वापस MAX77802_OPMODE_SHIFT_LDO;

	वापस -EINVAL;
पूर्ण

/**
 * max77802_set_suspend_disable - Disable the regulator during प्रणाली suspend
 * @rdev: regulator to mark as disabled
 *
 * All regulators expect LDO 1, 3, 20 and 21 support OFF by PWRREQ.
 * Configure the regulator so the PMIC will turn it OFF during प्रणाली suspend.
 */
अटल पूर्णांक max77802_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val = MAX77802_OFF_PWRREQ;
	काष्ठा max77802_regulator_prv *max77802 = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक shअगरt = max77802_get_opmode_shअगरt(id);

	max77802->opmode[id] = val;
	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, val << shअगरt);
पूर्ण

/*
 * Some LDOs support Low Power Mode जबतक the प्रणाली is running.
 *
 * LDOs 1, 3, 20, 21.
 */
अटल पूर्णांक max77802_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा max77802_regulator_prv *max77802 = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक shअगरt = max77802_get_opmode_shअगरt(id);

	चयन (mode) अणु
	हाल REGULATOR_MODE_STANDBY:
		val = MAX77802_OPMODE_LP;	/* ON in Low Power Mode */
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		val = MAX77802_OPMODE_NORMAL;	/* ON in Normal Mode */
		अवरोध;
	शेष:
		dev_warn(&rdev->dev, "%s: regulator mode: 0x%x not supported\n",
			 rdev->desc->name, mode);
		वापस -EINVAL;
	पूर्ण

	max77802->opmode[id] = val;
	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, val << shअगरt);
पूर्ण

अटल अचिन्हित max77802_get_mode(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77802_regulator_prv *max77802 = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);

	वापस max77802_map_mode(max77802->opmode[id]);
पूर्ण

/**
 * max77802_set_suspend_mode - set regulator opmode when the प्रणाली is suspended
 * @rdev: regulator to change mode
 * @mode: operating mode to be set
 *
 * Will set the operating mode क्रम the regulators during प्रणाली suspend.
 * This function is valid क्रम the three dअगरferent enable control logics:
 *
 * Enable Control Logic1 by PWRREQ (BUCK 2-4 and LDOs 2, 4-19, 22-35)
 * Enable Control Logic2 by PWRREQ (LDOs 1, 20, 21)
 * Enable Control Logic3 by PWRREQ (LDO 3)
 *
 * If setting the regulator mode fails, the function only warns but करोes
 * not वापस an error code to aव्योम the regulator core to stop setting
 * the operating mode क्रम the reमुख्यing regulators.
 */
अटल पूर्णांक max77802_set_suspend_mode(काष्ठा regulator_dev *rdev,
				     अचिन्हित पूर्णांक mode)
अणु
	काष्ठा max77802_regulator_prv *max77802 = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;
	पूर्णांक shअगरt = max77802_get_opmode_shअगरt(id);

	/*
	 * If the regulator has been disabled क्रम suspend
	 * then is invalid to try setting a suspend mode.
	 */
	अगर (max77802->opmode[id] == MAX77802_OFF_PWRREQ) अणु
		dev_warn(&rdev->dev, "%s: is disabled, mode: 0x%x not set\n",
			 rdev->desc->name, mode);
		वापस 0;
	पूर्ण

	चयन (mode) अणु
	हाल REGULATOR_MODE_STANDBY:
		/*
		 * If the regulator opmode is normal then enable
		 * ON in Low Power Mode by PWRREQ. If the mode is
		 * alपढ़ोy Low Power then no action is required.
		 */
		अगर (max77802->opmode[id] == MAX77802_OPMODE_NORMAL)
			val = MAX77802_LP_PWRREQ;
		अन्यथा
			वापस 0;
		अवरोध;
	हाल REGULATOR_MODE_NORMAL:
		/*
		 * If the regulator operating mode is Low Power then
		 * normal is not a valid opmode in suspend. If the
		 * mode is alपढ़ोy normal then no action is required.
		 */
		अगर (max77802->opmode[id] == MAX77802_OPMODE_LP)
			dev_warn(&rdev->dev, "%s: in Low Power: 0x%x invalid\n",
				 rdev->desc->name, mode);
		वापस 0;
	शेष:
		dev_warn(&rdev->dev, "%s: regulator mode: 0x%x not supported\n",
			 rdev->desc->name, mode);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, val << shअगरt);
पूर्ण

अटल पूर्णांक max77802_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा max77802_regulator_prv *max77802 = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	पूर्णांक shअगरt = max77802_get_opmode_shअगरt(id);

	अगर (max77802->opmode[id] == MAX77802_OFF_PWRREQ)
		max77802->opmode[id] = MAX77802_OPMODE_NORMAL;

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask,
				  max77802->opmode[id] << shअगरt);
पूर्ण

अटल पूर्णांक max77802_find_ramp_value(काष्ठा regulator_dev *rdev,
				    स्थिर अचिन्हित पूर्णांक limits[], पूर्णांक size,
				    अचिन्हित पूर्णांक ramp_delay)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		अगर (ramp_delay <= limits[i])
			वापस i;
	पूर्ण

	/* Use maximum value क्रम no ramp control */
	dev_warn(&rdev->dev, "%s: ramp_delay: %d not supported, setting 100000\n",
		 rdev->desc->name, ramp_delay);
	वापस size - 1;
पूर्ण

/* Used क्रम BUCKs 2-4 */
अटल पूर्णांक max77802_set_ramp_delay_2bit(काष्ठा regulator_dev *rdev,
					पूर्णांक ramp_delay)
अणु
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक ramp_value;

	अगर (id > MAX77802_BUCK4) अणु
		dev_warn(&rdev->dev,
			 "%s: regulator: ramp delay not supported\n",
			 rdev->desc->name);
		वापस -EINVAL;
	पूर्ण
	ramp_value = max77802_find_ramp_value(rdev, ramp_table_77802_2bit,
				ARRAY_SIZE(ramp_table_77802_2bit), ramp_delay);

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  MAX77802_RAMP_RATE_MASK_2BIT,
				  ramp_value << MAX77802_RAMP_RATE_SHIFT_2BIT);
पूर्ण

/* For BUCK1, 6 */
अटल पूर्णांक max77802_set_ramp_delay_4bit(काष्ठा regulator_dev *rdev,
					    पूर्णांक ramp_delay)
अणु
	अचिन्हित पूर्णांक ramp_value;

	ramp_value = max77802_find_ramp_value(rdev, ramp_table_77802_4bit,
				ARRAY_SIZE(ramp_table_77802_4bit), ramp_delay);

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  MAX77802_RAMP_RATE_MASK_4BIT,
				  ramp_value << MAX77802_RAMP_RATE_SHIFT_4BIT);
पूर्ण

/*
 * LDOs 2, 4-19, 22-35
 */
अटल स्थिर काष्ठा regulator_ops max77802_lकरो_ops_logic1 = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77802_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_disable	= max77802_set_suspend_disable,
	.set_suspend_mode	= max77802_set_suspend_mode,
पूर्ण;

/*
 * LDOs 1, 20, 21, 3
 */
अटल स्थिर काष्ठा regulator_ops max77802_lकरो_ops_logic2 = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77802_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_mode		= max77802_set_mode,
	.get_mode		= max77802_get_mode,
	.set_suspend_mode	= max77802_set_suspend_mode,
पूर्ण;

/* BUCKS 1, 6 */
अटल स्थिर काष्ठा regulator_ops max77802_buck_16_dvs_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77802_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= max77802_set_ramp_delay_4bit,
	.set_suspend_disable	= max77802_set_suspend_disable,
पूर्ण;

/* BUCKs 2-4 */
अटल स्थिर काष्ठा regulator_ops max77802_buck_234_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77802_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= max77802_set_ramp_delay_2bit,
	.set_suspend_disable	= max77802_set_suspend_disable,
	.set_suspend_mode	= max77802_set_suspend_mode,
पूर्ण;

/* BUCKs 5, 7-10 */
अटल स्थिर काष्ठा regulator_ops max77802_buck_dvs_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= max77802_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_ramp_delay		= max77802_set_ramp_delay_2bit,
	.set_suspend_disable	= max77802_set_suspend_disable,
पूर्ण;

/* LDOs 3-7, 9-14, 18-26, 28, 29, 32-34 */
#घोषणा regulator_77802_desc_p_lकरो(num, supply, log)	अणु		\
	.name		= "LDO"#num,					\
	.of_match	= of_match_ptr("LDO"#num),			\
	.regulators_node	= of_match_ptr("regulators"),		\
	.id		= MAX77802_LDO##num,				\
	.supply_name	= "inl"#supply,					\
	.ops		= &max77802_lकरो_ops_logic##log,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= 800000,					\
	.uV_step	= 50000,					\
	.ramp_delay	= MAX77802_RAMP_DELAY,				\
	.n_voltages	= 1 << 6,					\
	.vsel_reg	= MAX77802_REG_LDO1CTRL1 + num - 1,		\
	.vsel_mask	= MAX77802_VSEL_MASK,				\
	.enable_reg	= MAX77802_REG_LDO1CTRL1 + num - 1,		\
	.enable_mask	= MAX77802_OPMODE_MASK << MAX77802_OPMODE_SHIFT_LDO, \
	.of_map_mode	= max77802_map_mode,				\
पूर्ण

/* LDOs 1, 2, 8, 15, 17, 27, 30, 35 */
#घोषणा regulator_77802_desc_n_lकरो(num, supply, log)   अणु		\
	.name		= "LDO"#num,					\
	.of_match	= of_match_ptr("LDO"#num),			\
	.regulators_node	= of_match_ptr("regulators"),		\
	.id		= MAX77802_LDO##num,				\
	.supply_name	= "inl"#supply,					\
	.ops		= &max77802_lकरो_ops_logic##log,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= 800000,					\
	.uV_step	= 25000,					\
	.ramp_delay	= MAX77802_RAMP_DELAY,				\
	.n_voltages	= 1 << 6,					\
	.vsel_reg	= MAX77802_REG_LDO1CTRL1 + num - 1,		\
	.vsel_mask	= MAX77802_VSEL_MASK,				\
	.enable_reg	= MAX77802_REG_LDO1CTRL1 + num - 1,		\
	.enable_mask	= MAX77802_OPMODE_MASK << MAX77802_OPMODE_SHIFT_LDO, \
	.of_map_mode	= max77802_map_mode,				\
पूर्ण

/* BUCKs 1, 6 */
#घोषणा regulator_77802_desc_16_buck(num)	अणु		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptr("BUCK"#num),			\
	.regulators_node	= of_match_ptr("regulators"),		\
	.id		= MAX77802_BUCK##num,				\
	.supply_name	= "inb"#num,					\
	.ops		= &max77802_buck_16_dvs_ops,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= 612500,					\
	.uV_step	= 6250,						\
	.ramp_delay	= MAX77802_RAMP_DELAY,				\
	.n_voltages	= 1 << 8,					\
	.vsel_reg	= MAX77802_REG_BUCK ## num ## DVS1,		\
	.vsel_mask	= MAX77802_DVS_VSEL_MASK,			\
	.enable_reg	= MAX77802_REG_BUCK ## num ## CTRL,		\
	.enable_mask	= MAX77802_OPMODE_MASK,				\
	.of_map_mode	= max77802_map_mode,				\
पूर्ण

/* BUCKS 2-4 */
#घोषणा regulator_77802_desc_234_buck(num)	अणु		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptr("BUCK"#num),			\
	.regulators_node	= of_match_ptr("regulators"),		\
	.id		= MAX77802_BUCK##num,				\
	.supply_name	= "inb"#num,					\
	.ops		= &max77802_buck_234_ops,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= 600000,					\
	.uV_step	= 6250,						\
	.ramp_delay	= MAX77802_RAMP_DELAY,				\
	.n_voltages	= 0x91,						\
	.vsel_reg	= MAX77802_REG_BUCK ## num ## DVS1,		\
	.vsel_mask	= MAX77802_DVS_VSEL_MASK,			\
	.enable_reg	= MAX77802_REG_BUCK ## num ## CTRL1,		\
	.enable_mask	= MAX77802_OPMODE_MASK <<			\
				MAX77802_OPMODE_BUCK234_SHIFT,		\
	.of_map_mode	= max77802_map_mode,				\
पूर्ण

/* BUCK 5 */
#घोषणा regulator_77802_desc_buck5(num)		अणु		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptr("BUCK"#num),			\
	.regulators_node	= of_match_ptr("regulators"),		\
	.id		= MAX77802_BUCK##num,				\
	.supply_name	= "inb"#num,					\
	.ops		= &max77802_buck_dvs_ops,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= 750000,					\
	.uV_step	= 50000,					\
	.ramp_delay	= MAX77802_RAMP_DELAY,				\
	.n_voltages	= 1 << 6,					\
	.vsel_reg	= MAX77802_REG_BUCK5OUT,			\
	.vsel_mask	= MAX77802_VSEL_MASK,				\
	.enable_reg	= MAX77802_REG_BUCK5CTRL,			\
	.enable_mask	= MAX77802_OPMODE_MASK,				\
	.of_map_mode	= max77802_map_mode,				\
पूर्ण

/* BUCKs 7-10 */
#घोषणा regulator_77802_desc_buck7_10(num)	अणु		\
	.name		= "BUCK"#num,					\
	.of_match	= of_match_ptr("BUCK"#num),			\
	.regulators_node	= of_match_ptr("regulators"),		\
	.id		= MAX77802_BUCK##num,				\
	.supply_name	= "inb"#num,					\
	.ops		= &max77802_buck_dvs_ops,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.min_uV		= 750000,					\
	.uV_step	= 50000,					\
	.ramp_delay	= MAX77802_RAMP_DELAY,				\
	.n_voltages	= 1 << 6,					\
	.vsel_reg	= MAX77802_REG_BUCK7OUT + (num - 7) * 3,	\
	.vsel_mask	= MAX77802_VSEL_MASK,				\
	.enable_reg	= MAX77802_REG_BUCK7CTRL + (num - 7) * 3,	\
	.enable_mask	= MAX77802_OPMODE_MASK,				\
	.of_map_mode	= max77802_map_mode,				\
पूर्ण

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	regulator_77802_desc_16_buck(1),
	regulator_77802_desc_234_buck(2),
	regulator_77802_desc_234_buck(3),
	regulator_77802_desc_234_buck(4),
	regulator_77802_desc_buck5(5),
	regulator_77802_desc_16_buck(6),
	regulator_77802_desc_buck7_10(7),
	regulator_77802_desc_buck7_10(8),
	regulator_77802_desc_buck7_10(9),
	regulator_77802_desc_buck7_10(10),
	regulator_77802_desc_n_lकरो(1, 10, 2),
	regulator_77802_desc_n_lकरो(2, 10, 1),
	regulator_77802_desc_p_lकरो(3, 3, 2),
	regulator_77802_desc_p_lकरो(4, 6, 1),
	regulator_77802_desc_p_lकरो(5, 3, 1),
	regulator_77802_desc_p_lकरो(6, 3, 1),
	regulator_77802_desc_p_lकरो(7, 3, 1),
	regulator_77802_desc_n_lकरो(8, 1, 1),
	regulator_77802_desc_p_lकरो(9, 5, 1),
	regulator_77802_desc_p_lकरो(10, 4, 1),
	regulator_77802_desc_p_lकरो(11, 4, 1),
	regulator_77802_desc_p_lकरो(12, 9, 1),
	regulator_77802_desc_p_lकरो(13, 4, 1),
	regulator_77802_desc_p_lकरो(14, 4, 1),
	regulator_77802_desc_n_lकरो(15, 1, 1),
	regulator_77802_desc_n_lकरो(17, 2, 1),
	regulator_77802_desc_p_lकरो(18, 7, 1),
	regulator_77802_desc_p_lकरो(19, 5, 1),
	regulator_77802_desc_p_lकरो(20, 7, 2),
	regulator_77802_desc_p_lकरो(21, 6, 2),
	regulator_77802_desc_p_lकरो(23, 9, 1),
	regulator_77802_desc_p_lकरो(24, 6, 1),
	regulator_77802_desc_p_lकरो(25, 9, 1),
	regulator_77802_desc_p_lकरो(26, 9, 1),
	regulator_77802_desc_n_lकरो(27, 2, 1),
	regulator_77802_desc_p_lकरो(28, 7, 1),
	regulator_77802_desc_p_lकरो(29, 7, 1),
	regulator_77802_desc_n_lकरो(30, 2, 1),
	regulator_77802_desc_p_lकरो(32, 9, 1),
	regulator_77802_desc_p_lकरो(33, 6, 1),
	regulator_77802_desc_p_lकरो(34, 9, 1),
	regulator_77802_desc_n_lकरो(35, 2, 1),
पूर्ण;

अटल पूर्णांक max77802_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max77686_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा max77802_regulator_prv *max77802;
	पूर्णांक i, val;
	काष्ठा regulator_config config = अणु पूर्ण;

	max77802 = devm_kzalloc(&pdev->dev,
				माप(काष्ठा max77802_regulator_prv),
				GFP_KERNEL);
	अगर (!max77802)
		वापस -ENOMEM;

	config.dev = iodev->dev;
	config.regmap = iodev->regmap;
	config.driver_data = max77802;
	platक्रमm_set_drvdata(pdev, max77802);

	क्रम (i = 0; i < MAX77802_REG_MAX; i++) अणु
		काष्ठा regulator_dev *rdev;
		पूर्णांक id = regulators[i].id;
		पूर्णांक shअगरt = max77802_get_opmode_shअगरt(id);
		पूर्णांक ret;

		ret = regmap_पढ़ो(iodev->regmap, regulators[i].enable_reg, &val);
		अगर (ret < 0) अणु
			dev_warn(&pdev->dev,
				"cannot read current mode for %d\n", i);
			val = MAX77802_OPMODE_NORMAL;
		पूर्ण अन्यथा अणु
			val = val >> shअगरt & MAX77802_OPMODE_MASK;
		पूर्ण

		/*
		 * If the regulator is disabled and the प्रणाली warm rebooted,
		 * the hardware reports OFF as the regulator operating mode.
		 * Default to operating mode NORMAL in that हाल.
		 */
		अगर (val == MAX77802_STATUS_OFF)
			max77802->opmode[id] = MAX77802_OPMODE_NORMAL;
		अन्यथा
			max77802->opmode[id] = val;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
					       &regulators[i], &config);
		अगर (IS_ERR(rdev)) अणु
			ret = PTR_ERR(rdev);
			dev_err(&pdev->dev,
				"regulator init failed for %d: %d\n", i, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max77802_pmic_id[] = अणु
	अणु"max77802-pmic", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max77802_pmic_id);

अटल काष्ठा platक्रमm_driver max77802_pmic_driver = अणु
	.driver = अणु
		.name = "max77802-pmic",
	पूर्ण,
	.probe = max77802_pmic_probe,
	.id_table = max77802_pmic_id,
पूर्ण;

module_platक्रमm_driver(max77802_pmic_driver);

MODULE_DESCRIPTION("MAXIM 77802 Regulator Driver");
MODULE_AUTHOR("Simon Glass <sjg@chromium.org>");
MODULE_LICENSE("GPL");
