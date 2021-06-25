<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2012-2014 Samsung Electronics Co., Ltd
//              http://www.samsung.com

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/samsung/core.h>
#समावेश <linux/mfd/samsung/s2mps11.h>
#समावेश <linux/mfd/samsung/s2mps13.h>
#समावेश <linux/mfd/samsung/s2mps14.h>
#समावेश <linux/mfd/samsung/s2mps15.h>
#समावेश <linux/mfd/samsung/s2mpu02.h>

/* The highest number of possible regulators क्रम supported devices. */
#घोषणा S2MPS_REGULATOR_MAX		S2MPS13_REGULATOR_MAX
काष्ठा s2mps11_info अणु
	पूर्णांक ramp_delay2;
	पूर्णांक ramp_delay34;
	पूर्णांक ramp_delay5;
	पूर्णांक ramp_delay16;
	पूर्णांक ramp_delay7810;
	पूर्णांक ramp_delay9;

	क्रमागत sec_device_type dev_type;

	/*
	 * One bit क्रम each S2MPS11/S2MPS13/S2MPS14/S2MPU02 regulator whether
	 * the suspend mode was enabled.
	 */
	DECLARE_BITMAP(suspend_state, S2MPS_REGULATOR_MAX);

	/*
	 * Array (size: number of regulators) with GPIO-s क्रम बाह्यal
	 * sleep control.
	 */
	काष्ठा gpio_desc **ext_control_gpiod;
पूर्ण;

अटल पूर्णांक get_ramp_delay(पूर्णांक ramp_delay)
अणु
	अचिन्हित अक्षर cnt = 0;

	ramp_delay /= 6250;

	जबतक (true) अणु
		ramp_delay = ramp_delay >> 1;
		अगर (ramp_delay == 0)
			अवरोध;
		cnt++;
	पूर्ण

	अगर (cnt > 3)
		cnt = 3;

	वापस cnt;
पूर्ण

अटल पूर्णांक s2mps11_regulator_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
				   अचिन्हित पूर्णांक old_selector,
				   अचिन्हित पूर्णांक new_selector)
अणु
	काष्ठा s2mps11_info *s2mps11 = rdev_get_drvdata(rdev);
	पूर्णांक rdev_id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक ramp_delay = 0;
	पूर्णांक old_volt, new_volt;

	चयन (rdev_id) अणु
	हाल S2MPS11_BUCK2:
		ramp_delay = s2mps11->ramp_delay2;
		अवरोध;
	हाल S2MPS11_BUCK3:
	हाल S2MPS11_BUCK4:
		ramp_delay = s2mps11->ramp_delay34;
		अवरोध;
	हाल S2MPS11_BUCK5:
		ramp_delay = s2mps11->ramp_delay5;
		अवरोध;
	हाल S2MPS11_BUCK6:
	हाल S2MPS11_BUCK1:
		ramp_delay = s2mps11->ramp_delay16;
		अवरोध;
	हाल S2MPS11_BUCK7:
	हाल S2MPS11_BUCK8:
	हाल S2MPS11_BUCK10:
		ramp_delay = s2mps11->ramp_delay7810;
		अवरोध;
	हाल S2MPS11_BUCK9:
		ramp_delay = s2mps11->ramp_delay9;
	पूर्ण

	अगर (ramp_delay == 0)
		ramp_delay = rdev->desc->ramp_delay;

	old_volt = rdev->desc->min_uV + (rdev->desc->uV_step * old_selector);
	new_volt = rdev->desc->min_uV + (rdev->desc->uV_step * new_selector);

	वापस DIV_ROUND_UP(असल(new_volt - old_volt), ramp_delay);
पूर्ण

अटल पूर्णांक s2mps11_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	काष्ठा s2mps11_info *s2mps11 = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक ramp_val, ramp_shअगरt, ramp_reg = S2MPS11_REG_RAMP_BUCK;
	अचिन्हित पूर्णांक ramp_enable = 1, enable_shअगरt = 0;
	पूर्णांक rdev_id = rdev_get_id(rdev);
	पूर्णांक ret;

	चयन (rdev_id) अणु
	हाल S2MPS11_BUCK1:
		अगर (ramp_delay > s2mps11->ramp_delay16)
			s2mps11->ramp_delay16 = ramp_delay;
		अन्यथा
			ramp_delay = s2mps11->ramp_delay16;

		ramp_shअगरt = S2MPS11_BUCK16_RAMP_SHIFT;
		अवरोध;
	हाल S2MPS11_BUCK2:
		enable_shअगरt = S2MPS11_BUCK2_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		s2mps11->ramp_delay2 = ramp_delay;
		ramp_shअगरt = S2MPS11_BUCK2_RAMP_SHIFT;
		ramp_reg = S2MPS11_REG_RAMP;
		अवरोध;
	हाल S2MPS11_BUCK3:
		enable_shअगरt = S2MPS11_BUCK3_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		अगर (ramp_delay > s2mps11->ramp_delay34)
			s2mps11->ramp_delay34 = ramp_delay;
		अन्यथा
			ramp_delay = s2mps11->ramp_delay34;

		ramp_shअगरt = S2MPS11_BUCK34_RAMP_SHIFT;
		ramp_reg = S2MPS11_REG_RAMP;
		अवरोध;
	हाल S2MPS11_BUCK4:
		enable_shअगरt = S2MPS11_BUCK4_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		अगर (ramp_delay > s2mps11->ramp_delay34)
			s2mps11->ramp_delay34 = ramp_delay;
		अन्यथा
			ramp_delay = s2mps11->ramp_delay34;

		ramp_shअगरt = S2MPS11_BUCK34_RAMP_SHIFT;
		ramp_reg = S2MPS11_REG_RAMP;
		अवरोध;
	हाल S2MPS11_BUCK5:
		s2mps11->ramp_delay5 = ramp_delay;
		ramp_shअगरt = S2MPS11_BUCK5_RAMP_SHIFT;
		अवरोध;
	हाल S2MPS11_BUCK6:
		enable_shअगरt = S2MPS11_BUCK6_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		अगर (ramp_delay > s2mps11->ramp_delay16)
			s2mps11->ramp_delay16 = ramp_delay;
		अन्यथा
			ramp_delay = s2mps11->ramp_delay16;

		ramp_shअगरt = S2MPS11_BUCK16_RAMP_SHIFT;
		अवरोध;
	हाल S2MPS11_BUCK7:
	हाल S2MPS11_BUCK8:
	हाल S2MPS11_BUCK10:
		अगर (ramp_delay > s2mps11->ramp_delay7810)
			s2mps11->ramp_delay7810 = ramp_delay;
		अन्यथा
			ramp_delay = s2mps11->ramp_delay7810;

		ramp_shअगरt = S2MPS11_BUCK7810_RAMP_SHIFT;
		अवरोध;
	हाल S2MPS11_BUCK9:
		s2mps11->ramp_delay9 = ramp_delay;
		ramp_shअगरt = S2MPS11_BUCK9_RAMP_SHIFT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (!ramp_enable)
		जाओ ramp_disable;

	/* Ramp delay can be enabled/disabled only क्रम buck[2346] */
	अगर ((rdev_id >= S2MPS11_BUCK2 && rdev_id <= S2MPS11_BUCK4) ||
	    rdev_id == S2MPS11_BUCK6)  अणु
		ret = regmap_update_bits(rdev->regmap, S2MPS11_REG_RAMP,
					 1 << enable_shअगरt, 1 << enable_shअगरt);
		अगर (ret) अणु
			dev_err(&rdev->dev, "failed to enable ramp rate\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ramp_val = get_ramp_delay(ramp_delay);

	वापस regmap_update_bits(rdev->regmap, ramp_reg, 0x3 << ramp_shअगरt,
				  ramp_val << ramp_shअगरt);

ramp_disable:
	वापस regmap_update_bits(rdev->regmap, S2MPS11_REG_RAMP,
				  1 << enable_shअगरt, 0);
पूर्ण

अटल पूर्णांक s2mps11_regulator_enable(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा s2mps11_info *s2mps11 = rdev_get_drvdata(rdev);
	पूर्णांक rdev_id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक val;

	चयन (s2mps11->dev_type) अणु
	हाल S2MPS11X:
		अगर (test_bit(rdev_id, s2mps11->suspend_state))
			val = S2MPS14_ENABLE_SUSPEND;
		अन्यथा
			val = rdev->desc->enable_mask;
		अवरोध;
	हाल S2MPS13X:
	हाल S2MPS14X:
		अगर (test_bit(rdev_id, s2mps11->suspend_state))
			val = S2MPS14_ENABLE_SUSPEND;
		अन्यथा अगर (s2mps11->ext_control_gpiod[rdev_id])
			val = S2MPS14_ENABLE_EXT_CONTROL;
		अन्यथा
			val = rdev->desc->enable_mask;
		अवरोध;
	हाल S2MPU02:
		अगर (test_bit(rdev_id, s2mps11->suspend_state))
			val = S2MPU02_ENABLE_SUSPEND;
		अन्यथा
			val = rdev->desc->enable_mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			rdev->desc->enable_mask, val);
पूर्ण

अटल पूर्णांक s2mps11_regulator_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val, state;
	काष्ठा s2mps11_info *s2mps11 = rdev_get_drvdata(rdev);
	पूर्णांक rdev_id = rdev_get_id(rdev);

	/* Below LDO should be always on or करोes not support suspend mode. */
	चयन (s2mps11->dev_type) अणु
	हाल S2MPS11X:
		चयन (rdev_id) अणु
		हाल S2MPS11_LDO2:
		हाल S2MPS11_LDO36:
		हाल S2MPS11_LDO37:
		हाल S2MPS11_LDO38:
			वापस 0;
		शेष:
			state = S2MPS14_ENABLE_SUSPEND;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल S2MPS13X:
	हाल S2MPS14X:
		चयन (rdev_id) अणु
		हाल S2MPS14_LDO3:
			वापस 0;
		शेष:
			state = S2MPS14_ENABLE_SUSPEND;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल S2MPU02:
		चयन (rdev_id) अणु
		हाल S2MPU02_LDO13:
		हाल S2MPU02_LDO14:
		हाल S2MPU02_LDO15:
		हाल S2MPU02_LDO17:
		हाल S2MPU02_BUCK7:
			state = S2MPU02_DISABLE_SUSPEND;
			अवरोध;
		शेष:
			state = S2MPU02_ENABLE_SUSPEND;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &val);
	अगर (ret < 0)
		वापस ret;

	set_bit(rdev_id, s2mps11->suspend_state);
	/*
	 * Don't enable suspend mode अगर regulator is alपढ़ोy disabled because
	 * this would effectively क्रम a लघु समय turn on the regulator after
	 * resuming.
	 * However we still want to toggle the suspend_state bit क्रम regulator
	 * in हाल अगर it got enabled beक्रमe suspending the प्रणाली.
	 */
	अगर (!(val & rdev->desc->enable_mask))
		वापस 0;

	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
				  rdev->desc->enable_mask, state);
पूर्ण

अटल स्थिर काष्ठा regulator_ops s2mps11_lकरो_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= s2mps11_regulator_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_disable	= s2mps11_regulator_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s2mps11_buck_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= s2mps11_regulator_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= s2mps11_regulator_set_voltage_समय_sel,
	.set_ramp_delay		= s2mps11_set_ramp_delay,
	.set_suspend_disable	= s2mps11_regulator_set_suspend_disable,
पूर्ण;

#घोषणा regulator_desc_s2mps11_lकरो(num, step) अणु		\
	.name		= "LDO"#num,			\
	.id		= S2MPS11_LDO##num,		\
	.ops		= &s2mps11_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.ramp_delay	= RAMP_DELAY_12_MVUS,		\
	.min_uV		= MIN_800_MV,			\
	.uV_step	= step,				\
	.n_voltages	= S2MPS11_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPS11_REG_L1CTRL + num - 1,	\
	.vsel_mask	= S2MPS11_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPS11_REG_L1CTRL + num - 1,	\
	.enable_mask	= S2MPS11_ENABLE_MASK		\
पूर्ण

#घोषणा regulator_desc_s2mps11_buck1_4(num) अणु			\
	.name		= "BUCK"#num,				\
	.id		= S2MPS11_BUCK##num,			\
	.ops		= &s2mps11_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= MIN_650_MV,				\
	.uV_step	= STEP_6_25_MV,				\
	.linear_min_sel	= 8,					\
	.n_voltages	= S2MPS11_BUCK12346_N_VOLTAGES,		\
	.ramp_delay	= S2MPS11_RAMP_DELAY,			\
	.vsel_reg	= S2MPS11_REG_B1CTRL2 + (num - 1) * 2,	\
	.vsel_mask	= S2MPS11_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPS11_REG_B1CTRL1 + (num - 1) * 2,	\
	.enable_mask	= S2MPS11_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_s2mps11_buck5 अणु				\
	.name		= "BUCK5",				\
	.id		= S2MPS11_BUCK5,			\
	.ops		= &s2mps11_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= MIN_650_MV,				\
	.uV_step	= STEP_6_25_MV,				\
	.linear_min_sel	= 8,					\
	.n_voltages	= S2MPS11_BUCK5_N_VOLTAGES,		\
	.ramp_delay	= S2MPS11_RAMP_DELAY,			\
	.vsel_reg	= S2MPS11_REG_B5CTRL2,			\
	.vsel_mask	= S2MPS11_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPS11_REG_B5CTRL1,			\
	.enable_mask	= S2MPS11_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_s2mps11_buck67810(num, min, step, min_sel, voltages) अणु	\
	.name		= "BUCK"#num,				\
	.id		= S2MPS11_BUCK##num,			\
	.ops		= &s2mps11_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.linear_min_sel	= min_sel,				\
	.n_voltages	= voltages,				\
	.ramp_delay	= S2MPS11_RAMP_DELAY,			\
	.vsel_reg	= S2MPS11_REG_B6CTRL2 + (num - 6) * 2,	\
	.vsel_mask	= S2MPS11_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPS11_REG_B6CTRL1 + (num - 6) * 2,	\
	.enable_mask	= S2MPS11_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_s2mps11_buck9 अणु				\
	.name		= "BUCK9",				\
	.id		= S2MPS11_BUCK9,			\
	.ops		= &s2mps11_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= MIN_3000_MV,				\
	.uV_step	= STEP_25_MV,				\
	.n_voltages	= S2MPS11_BUCK9_N_VOLTAGES,		\
	.ramp_delay	= S2MPS11_RAMP_DELAY,			\
	.vsel_reg	= S2MPS11_REG_B9CTRL2,			\
	.vsel_mask	= S2MPS11_BUCK9_VSEL_MASK,		\
	.enable_reg	= S2MPS11_REG_B9CTRL1,			\
	.enable_mask	= S2MPS11_ENABLE_MASK			\
पूर्ण

अटल स्थिर काष्ठा regulator_desc s2mps11_regulators[] = अणु
	regulator_desc_s2mps11_lकरो(1, STEP_25_MV),
	regulator_desc_s2mps11_lकरो(2, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(3, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(4, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(5, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(6, STEP_25_MV),
	regulator_desc_s2mps11_lकरो(7, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(8, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(9, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(10, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(11, STEP_25_MV),
	regulator_desc_s2mps11_lकरो(12, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(13, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(14, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(15, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(16, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(17, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(18, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(19, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(20, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(21, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(22, STEP_25_MV),
	regulator_desc_s2mps11_lकरो(23, STEP_25_MV),
	regulator_desc_s2mps11_lकरो(24, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(25, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(26, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(27, STEP_25_MV),
	regulator_desc_s2mps11_lकरो(28, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(29, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(30, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(31, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(32, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(33, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(34, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(35, STEP_25_MV),
	regulator_desc_s2mps11_lकरो(36, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(37, STEP_50_MV),
	regulator_desc_s2mps11_lकरो(38, STEP_50_MV),
	regulator_desc_s2mps11_buck1_4(1),
	regulator_desc_s2mps11_buck1_4(2),
	regulator_desc_s2mps11_buck1_4(3),
	regulator_desc_s2mps11_buck1_4(4),
	regulator_desc_s2mps11_buck5,
	regulator_desc_s2mps11_buck67810(6, MIN_650_MV, STEP_6_25_MV, 8,
					 S2MPS11_BUCK12346_N_VOLTAGES),
	regulator_desc_s2mps11_buck67810(7, MIN_750_MV, STEP_12_5_MV, 0,
					 S2MPS11_BUCK7810_N_VOLTAGES),
	regulator_desc_s2mps11_buck67810(8, MIN_750_MV, STEP_12_5_MV, 0,
					 S2MPS11_BUCK7810_N_VOLTAGES),
	regulator_desc_s2mps11_buck9,
	regulator_desc_s2mps11_buck67810(10, MIN_750_MV, STEP_12_5_MV, 0,
					 S2MPS11_BUCK7810_N_VOLTAGES),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s2mps14_reg_ops;

#घोषणा regulator_desc_s2mps13_lकरो(num, min, step, min_sel) अणु	\
	.name		= "LDO"#num,				\
	.id		= S2MPS13_LDO##num,			\
	.ops		= &s2mps14_reg_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.linear_min_sel	= min_sel,				\
	.n_voltages	= S2MPS14_LDO_N_VOLTAGES,		\
	.vsel_reg	= S2MPS13_REG_L1CTRL + num - 1,		\
	.vsel_mask	= S2MPS14_LDO_VSEL_MASK,		\
	.enable_reg	= S2MPS13_REG_L1CTRL + num - 1,		\
	.enable_mask	= S2MPS14_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_s2mps13_buck(num, min, step, min_sel) अणु	\
	.name		= "BUCK"#num,				\
	.id		= S2MPS13_BUCK##num,			\
	.ops		= &s2mps14_reg_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.linear_min_sel	= min_sel,				\
	.n_voltages	= S2MPS14_BUCK_N_VOLTAGES,		\
	.ramp_delay	= S2MPS13_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPS13_REG_B1OUT + (num - 1) * 2,	\
	.vsel_mask	= S2MPS14_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPS13_REG_B1CTRL + (num - 1) * 2,	\
	.enable_mask	= S2MPS14_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_s2mps13_buck7(num, min, step, min_sel) अणु	\
	.name		= "BUCK"#num,				\
	.id		= S2MPS13_BUCK##num,			\
	.ops		= &s2mps14_reg_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.linear_min_sel	= min_sel,				\
	.n_voltages	= S2MPS14_BUCK_N_VOLTAGES,		\
	.ramp_delay	= S2MPS13_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPS13_REG_B1OUT + (num) * 2 - 1,	\
	.vsel_mask	= S2MPS14_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPS13_REG_B1CTRL + (num - 1) * 2,	\
	.enable_mask	= S2MPS14_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_s2mps13_buck8_10(num, min, step, min_sel) अणु	\
	.name		= "BUCK"#num,				\
	.id		= S2MPS13_BUCK##num,			\
	.ops		= &s2mps14_reg_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.linear_min_sel	= min_sel,				\
	.n_voltages	= S2MPS14_BUCK_N_VOLTAGES,		\
	.ramp_delay	= S2MPS13_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPS13_REG_B1OUT + (num) * 2 - 1,	\
	.vsel_mask	= S2MPS14_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPS13_REG_B1CTRL + (num) * 2 - 1,	\
	.enable_mask	= S2MPS14_ENABLE_MASK			\
पूर्ण

अटल स्थिर काष्ठा regulator_desc s2mps13_regulators[] = अणु
	regulator_desc_s2mps13_lकरो(1,  MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(2,  MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(3,  MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(4,  MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(5,  MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(6,  MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(7,  MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(8,  MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(9,  MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(10, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(11, MIN_800_MV,  STEP_25_MV,   0x10),
	regulator_desc_s2mps13_lकरो(12, MIN_800_MV,  STEP_25_MV,   0x10),
	regulator_desc_s2mps13_lकरो(13, MIN_800_MV,  STEP_25_MV,   0x10),
	regulator_desc_s2mps13_lकरो(14, MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(15, MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(16, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(17, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(18, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(19, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(20, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(21, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(22, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(23, MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(24, MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(25, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(26, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(27, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(28, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(29, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(30, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(31, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(32, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(33, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(34, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(35, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(36, MIN_800_MV,  STEP_12_5_MV, 0x00),
	regulator_desc_s2mps13_lकरो(37, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(38, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_lकरो(39, MIN_1000_MV, STEP_25_MV,   0x08),
	regulator_desc_s2mps13_lकरो(40, MIN_1400_MV, STEP_50_MV,   0x0C),
	regulator_desc_s2mps13_buck(1,  MIN_500_MV,  STEP_6_25_MV, 0x10),
	regulator_desc_s2mps13_buck(2,  MIN_500_MV,  STEP_6_25_MV, 0x10),
	regulator_desc_s2mps13_buck(3,  MIN_500_MV,  STEP_6_25_MV, 0x10),
	regulator_desc_s2mps13_buck(4,  MIN_500_MV,  STEP_6_25_MV, 0x10),
	regulator_desc_s2mps13_buck(5,  MIN_500_MV,  STEP_6_25_MV, 0x10),
	regulator_desc_s2mps13_buck(6,  MIN_500_MV,  STEP_6_25_MV, 0x10),
	regulator_desc_s2mps13_buck7(7,  MIN_500_MV,  STEP_6_25_MV, 0x10),
	regulator_desc_s2mps13_buck8_10(8,  MIN_1000_MV, STEP_12_5_MV, 0x20),
	regulator_desc_s2mps13_buck8_10(9,  MIN_1000_MV, STEP_12_5_MV, 0x20),
	regulator_desc_s2mps13_buck8_10(10, MIN_500_MV,  STEP_6_25_MV, 0x10),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s2mps14_reg_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= s2mps11_regulator_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_disable	= s2mps11_regulator_set_suspend_disable,
पूर्ण;

#घोषणा regulator_desc_s2mps14_lकरो(num, min, step) अणु	\
	.name		= "LDO"#num,			\
	.id		= S2MPS14_LDO##num,		\
	.ops		= &s2mps14_reg_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.min_uV		= min,				\
	.uV_step	= step,				\
	.n_voltages	= S2MPS14_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPS14_REG_L1CTRL + num - 1,	\
	.vsel_mask	= S2MPS14_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPS14_REG_L1CTRL + num - 1,	\
	.enable_mask	= S2MPS14_ENABLE_MASK		\
पूर्ण

#घोषणा regulator_desc_s2mps14_buck(num, min, step, min_sel) अणु	\
	.name		= "BUCK"#num,				\
	.id		= S2MPS14_BUCK##num,			\
	.ops		= &s2mps14_reg_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.n_voltages	= S2MPS14_BUCK_N_VOLTAGES,		\
	.linear_min_sel = min_sel,				\
	.ramp_delay	= S2MPS14_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPS14_REG_B1CTRL2 + (num - 1) * 2,	\
	.vsel_mask	= S2MPS14_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPS14_REG_B1CTRL1 + (num - 1) * 2,	\
	.enable_mask	= S2MPS14_ENABLE_MASK			\
पूर्ण

अटल स्थिर काष्ठा regulator_desc s2mps14_regulators[] = अणु
	regulator_desc_s2mps14_lकरो(1, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_s2mps14_lकरो(2, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_s2mps14_lकरो(3, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(4, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(5, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_s2mps14_lकरो(6, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_s2mps14_lकरो(7, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(8, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(9, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_s2mps14_lकरो(10, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_s2mps14_lकरो(11, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(12, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(13, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(14, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(15, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(16, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(17, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(18, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(19, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(20, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(21, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(22, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_s2mps14_lकरो(23, MIN_800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(24, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_lकरो(25, MIN_1800_MV, STEP_25_MV),
	regulator_desc_s2mps14_buck(1, MIN_600_MV, STEP_6_25_MV,
				    S2MPS14_BUCK1235_START_SEL),
	regulator_desc_s2mps14_buck(2, MIN_600_MV, STEP_6_25_MV,
				    S2MPS14_BUCK1235_START_SEL),
	regulator_desc_s2mps14_buck(3, MIN_600_MV, STEP_6_25_MV,
				    S2MPS14_BUCK1235_START_SEL),
	regulator_desc_s2mps14_buck(4, MIN_1400_MV, STEP_12_5_MV,
				    S2MPS14_BUCK4_START_SEL),
	regulator_desc_s2mps14_buck(5, MIN_600_MV, STEP_6_25_MV,
				    S2MPS14_BUCK1235_START_SEL),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s2mps15_reg_lकरो_ops = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s2mps15_reg_buck_ops = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
पूर्ण;

#घोषणा regulator_desc_s2mps15_lकरो(num, range) अणु	\
	.name		= "LDO"#num,			\
	.id		= S2MPS15_LDO##num,		\
	.ops		= &s2mps15_reg_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.linear_ranges	= range,			\
	.n_linear_ranges = ARRAY_SIZE(range),		\
	.n_voltages	= S2MPS15_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPS15_REG_L1CTRL + num - 1,	\
	.vsel_mask	= S2MPS15_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPS15_REG_L1CTRL + num - 1,	\
	.enable_mask	= S2MPS15_ENABLE_MASK		\
पूर्ण

#घोषणा regulator_desc_s2mps15_buck(num, range) अणु			\
	.name		= "BUCK"#num,					\
	.id		= S2MPS15_BUCK##num,				\
	.ops		= &s2mps15_reg_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,				\
	.owner		= THIS_MODULE,					\
	.linear_ranges	= range,					\
	.n_linear_ranges = ARRAY_SIZE(range),				\
	.ramp_delay	= 12500,					\
	.n_voltages	= S2MPS15_BUCK_N_VOLTAGES,			\
	.vsel_reg	= S2MPS15_REG_B1CTRL2 + ((num - 1) * 2),	\
	.vsel_mask	= S2MPS15_BUCK_VSEL_MASK,			\
	.enable_reg	= S2MPS15_REG_B1CTRL1 + ((num - 1) * 2),	\
	.enable_mask	= S2MPS15_ENABLE_MASK				\
पूर्ण

/* voltage range क्रम s2mps15 LDO 3, 5, 15, 16, 18, 20, 23 and 27 */
अटल स्थिर काष्ठा linear_range s2mps15_lकरो_voltage_ranges1[] = अणु
	REGULATOR_LINEAR_RANGE(1000000, 0xc, 0x38, 25000),
पूर्ण;

/* voltage range क्रम s2mps15 LDO 2, 6, 14, 17, 19, 21, 24 and 25 */
अटल स्थिर काष्ठा linear_range s2mps15_lकरो_voltage_ranges2[] = अणु
	REGULATOR_LINEAR_RANGE(1800000, 0x0, 0x3f, 25000),
पूर्ण;

/* voltage range क्रम s2mps15 LDO 4, 11, 12, 13, 22 and 26 */
अटल स्थिर काष्ठा linear_range s2mps15_lकरो_voltage_ranges3[] = अणु
	REGULATOR_LINEAR_RANGE(700000, 0x0, 0x34, 12500),
पूर्ण;

/* voltage range क्रम s2mps15 LDO 7, 8, 9 and 10 */
अटल स्थिर काष्ठा linear_range s2mps15_lकरो_voltage_ranges4[] = अणु
	REGULATOR_LINEAR_RANGE(700000, 0x10, 0x20, 25000),
पूर्ण;

/* voltage range क्रम s2mps15 LDO 1 */
अटल स्थिर काष्ठा linear_range s2mps15_lकरो_voltage_ranges5[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0x0, 0x20, 12500),
पूर्ण;

/* voltage range क्रम s2mps15 BUCK 1, 2, 3, 4, 5, 6 and 7 */
अटल स्थिर काष्ठा linear_range s2mps15_buck_voltage_ranges1[] = अणु
	REGULATOR_LINEAR_RANGE(500000, 0x20, 0xc0, 6250),
पूर्ण;

/* voltage range क्रम s2mps15 BUCK 8, 9 and 10 */
अटल स्थिर काष्ठा linear_range s2mps15_buck_voltage_ranges2[] = अणु
	REGULATOR_LINEAR_RANGE(1000000, 0x20, 0x78, 12500),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc s2mps15_regulators[] = अणु
	regulator_desc_s2mps15_lकरो(1, s2mps15_lकरो_voltage_ranges5),
	regulator_desc_s2mps15_lकरो(2, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(3, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_lकरो(4, s2mps15_lकरो_voltage_ranges3),
	regulator_desc_s2mps15_lकरो(5, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_lकरो(6, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(7, s2mps15_lकरो_voltage_ranges4),
	regulator_desc_s2mps15_lकरो(8, s2mps15_lकरो_voltage_ranges4),
	regulator_desc_s2mps15_lकरो(9, s2mps15_lकरो_voltage_ranges4),
	regulator_desc_s2mps15_lकरो(10, s2mps15_lकरो_voltage_ranges4),
	regulator_desc_s2mps15_lकरो(11, s2mps15_lकरो_voltage_ranges3),
	regulator_desc_s2mps15_lकरो(12, s2mps15_lकरो_voltage_ranges3),
	regulator_desc_s2mps15_lकरो(13, s2mps15_lकरो_voltage_ranges3),
	regulator_desc_s2mps15_lकरो(14, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(15, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_lकरो(16, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_lकरो(17, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(18, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_lकरो(19, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(20, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_lकरो(21, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(22, s2mps15_lकरो_voltage_ranges3),
	regulator_desc_s2mps15_lकरो(23, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_lकरो(24, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(25, s2mps15_lकरो_voltage_ranges2),
	regulator_desc_s2mps15_lकरो(26, s2mps15_lकरो_voltage_ranges3),
	regulator_desc_s2mps15_lकरो(27, s2mps15_lकरो_voltage_ranges1),
	regulator_desc_s2mps15_buck(1, s2mps15_buck_voltage_ranges1),
	regulator_desc_s2mps15_buck(2, s2mps15_buck_voltage_ranges1),
	regulator_desc_s2mps15_buck(3, s2mps15_buck_voltage_ranges1),
	regulator_desc_s2mps15_buck(4, s2mps15_buck_voltage_ranges1),
	regulator_desc_s2mps15_buck(5, s2mps15_buck_voltage_ranges1),
	regulator_desc_s2mps15_buck(6, s2mps15_buck_voltage_ranges1),
	regulator_desc_s2mps15_buck(7, s2mps15_buck_voltage_ranges1),
	regulator_desc_s2mps15_buck(8, s2mps15_buck_voltage_ranges2),
	regulator_desc_s2mps15_buck(9, s2mps15_buck_voltage_ranges2),
	regulator_desc_s2mps15_buck(10, s2mps15_buck_voltage_ranges2),
पूर्ण;

अटल पूर्णांक s2mps14_pmic_enable_ext_control(काष्ठा s2mps11_info *s2mps11,
		काष्ठा regulator_dev *rdev)
अणु
	वापस regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			rdev->desc->enable_mask, S2MPS14_ENABLE_EXT_CONTROL);
पूर्ण

अटल व्योम s2mps14_pmic_dt_parse_ext_control_gpio(काष्ठा platक्रमm_device *pdev,
		काष्ठा of_regulator_match *rdata, काष्ठा s2mps11_info *s2mps11)
अणु
	काष्ठा gpio_desc **gpio = s2mps11->ext_control_gpiod;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक valid_regulators[3] = अणु S2MPS14_LDO10, S2MPS14_LDO11,
		S2MPS14_LDO12 पूर्ण;

	क्रम (i = 0; i < ARRAY_SIZE(valid_regulators); i++) अणु
		अचिन्हित पूर्णांक reg = valid_regulators[i];

		अगर (!rdata[reg].init_data || !rdata[reg].of_node)
			जारी;

		gpio[reg] = devm_fwnode_gpiod_get(&pdev->dev,
				of_fwnode_handle(rdata[reg].of_node),
				"samsung,ext-control",
				GPIOD_OUT_HIGH | GPIOD_FLAGS_BIT_NONEXCLUSIVE,
				"s2mps11-regulator");
		अगर (PTR_ERR(gpio[reg]) == -ENOENT)
			gpio[reg] = शून्य;
		अन्यथा अगर (IS_ERR(gpio[reg])) अणु
			dev_err(&pdev->dev, "Failed to get control GPIO for %d/%s\n",
				reg, rdata[reg].name);
			gpio[reg] = शून्य;
			जारी;
		पूर्ण
		अगर (gpio[reg])
			dev_dbg(&pdev->dev, "Using GPIO for ext-control over %d/%s\n",
				reg, rdata[reg].name);
	पूर्ण
पूर्ण

अटल पूर्णांक s2mps11_pmic_dt_parse(काष्ठा platक्रमm_device *pdev,
		काष्ठा of_regulator_match *rdata, काष्ठा s2mps11_info *s2mps11,
		अचिन्हित पूर्णांक rdev_num)
अणु
	काष्ठा device_node *reg_np;

	reg_np = of_get_child_by_name(pdev->dev.parent->of_node, "regulators");
	अगर (!reg_np) अणु
		dev_err(&pdev->dev, "could not find regulators sub-node\n");
		वापस -EINVAL;
	पूर्ण

	of_regulator_match(&pdev->dev, reg_np, rdata, rdev_num);
	अगर (s2mps11->dev_type == S2MPS14X)
		s2mps14_pmic_dt_parse_ext_control_gpio(pdev, rdata, s2mps11);

	of_node_put(reg_np);

	वापस 0;
पूर्ण

अटल पूर्णांक s2mpu02_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	अचिन्हित पूर्णांक ramp_val, ramp_shअगरt, ramp_reg;
	पूर्णांक rdev_id = rdev_get_id(rdev);

	चयन (rdev_id) अणु
	हाल S2MPU02_BUCK1:
		ramp_shअगरt = S2MPU02_BUCK1_RAMP_SHIFT;
		अवरोध;
	हाल S2MPU02_BUCK2:
		ramp_shअगरt = S2MPU02_BUCK2_RAMP_SHIFT;
		अवरोध;
	हाल S2MPU02_BUCK3:
		ramp_shअगरt = S2MPU02_BUCK3_RAMP_SHIFT;
		अवरोध;
	हाल S2MPU02_BUCK4:
		ramp_shअगरt = S2MPU02_BUCK4_RAMP_SHIFT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण
	ramp_reg = S2MPU02_REG_RAMP1;
	ramp_val = get_ramp_delay(ramp_delay);

	वापस regmap_update_bits(rdev->regmap, ramp_reg,
				  S2MPU02_BUCK1234_RAMP_MASK << ramp_shअगरt,
				  ramp_val << ramp_shअगरt);
पूर्ण

अटल स्थिर काष्ठा regulator_ops s2mpu02_lकरो_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= s2mps11_regulator_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_disable	= s2mps11_regulator_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s2mpu02_buck_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= s2mps11_regulator_enable,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.set_suspend_disable	= s2mps11_regulator_set_suspend_disable,
	.set_ramp_delay		= s2mpu02_set_ramp_delay,
पूर्ण;

#घोषणा regulator_desc_s2mpu02_lकरो1(num) अणु		\
	.name		= "LDO"#num,			\
	.id		= S2MPU02_LDO##num,		\
	.ops		= &s2mpu02_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.min_uV		= S2MPU02_LDO_MIN_900MV,	\
	.uV_step	= S2MPU02_LDO_STEP_12_5MV,	\
	.linear_min_sel	= S2MPU02_LDO_GROUP1_START_SEL,	\
	.n_voltages	= S2MPU02_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPU02_REG_L1CTRL,		\
	.vsel_mask	= S2MPU02_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPU02_REG_L1CTRL,		\
	.enable_mask	= S2MPU02_ENABLE_MASK		\
पूर्ण
#घोषणा regulator_desc_s2mpu02_lकरो2(num) अणु		\
	.name		= "LDO"#num,			\
	.id		= S2MPU02_LDO##num,		\
	.ops		= &s2mpu02_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.min_uV		= S2MPU02_LDO_MIN_1050MV,	\
	.uV_step	= S2MPU02_LDO_STEP_25MV,	\
	.linear_min_sel	= S2MPU02_LDO_GROUP2_START_SEL,	\
	.n_voltages	= S2MPU02_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPU02_REG_L2CTRL1,		\
	.vsel_mask	= S2MPU02_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPU02_REG_L2CTRL1,		\
	.enable_mask	= S2MPU02_ENABLE_MASK		\
पूर्ण
#घोषणा regulator_desc_s2mpu02_lकरो3(num) अणु		\
	.name		= "LDO"#num,			\
	.id		= S2MPU02_LDO##num,		\
	.ops		= &s2mpu02_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.min_uV		= S2MPU02_LDO_MIN_900MV,	\
	.uV_step	= S2MPU02_LDO_STEP_12_5MV,	\
	.linear_min_sel	= S2MPU02_LDO_GROUP1_START_SEL,	\
	.n_voltages	= S2MPU02_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPU02_REG_L3CTRL + num - 3,	\
	.vsel_mask	= S2MPU02_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPU02_REG_L3CTRL + num - 3,	\
	.enable_mask	= S2MPU02_ENABLE_MASK		\
पूर्ण
#घोषणा regulator_desc_s2mpu02_lकरो4(num) अणु		\
	.name		= "LDO"#num,			\
	.id		= S2MPU02_LDO##num,		\
	.ops		= &s2mpu02_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.min_uV		= S2MPU02_LDO_MIN_1050MV,	\
	.uV_step	= S2MPU02_LDO_STEP_25MV,	\
	.linear_min_sel	= S2MPU02_LDO_GROUP2_START_SEL,	\
	.n_voltages	= S2MPU02_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPU02_REG_L3CTRL + num - 3,	\
	.vsel_mask	= S2MPU02_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPU02_REG_L3CTRL + num - 3,	\
	.enable_mask	= S2MPU02_ENABLE_MASK		\
पूर्ण
#घोषणा regulator_desc_s2mpu02_lकरो5(num) अणु		\
	.name		= "LDO"#num,			\
	.id		= S2MPU02_LDO##num,		\
	.ops		= &s2mpu02_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.min_uV		= S2MPU02_LDO_MIN_1600MV,	\
	.uV_step	= S2MPU02_LDO_STEP_50MV,	\
	.linear_min_sel	= S2MPU02_LDO_GROUP3_START_SEL,	\
	.n_voltages	= S2MPU02_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPU02_REG_L3CTRL + num - 3,	\
	.vsel_mask	= S2MPU02_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPU02_REG_L3CTRL + num - 3,	\
	.enable_mask	= S2MPU02_ENABLE_MASK		\
पूर्ण

#घोषणा regulator_desc_s2mpu02_buck1234(num) अणु			\
	.name		= "BUCK"#num,				\
	.id		= S2MPU02_BUCK##num,			\
	.ops		= &s2mpu02_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= S2MPU02_BUCK1234_MIN_600MV,		\
	.uV_step	= S2MPU02_BUCK1234_STEP_6_25MV,		\
	.n_voltages	= S2MPU02_BUCK_N_VOLTAGES,		\
	.linear_min_sel = S2MPU02_BUCK1234_START_SEL,		\
	.ramp_delay	= S2MPU02_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPU02_REG_B1CTRL2 + (num - 1) * 2,	\
	.vsel_mask	= S2MPU02_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPU02_REG_B1CTRL1 + (num - 1) * 2,	\
	.enable_mask	= S2MPU02_ENABLE_MASK			\
पूर्ण
#घोषणा regulator_desc_s2mpu02_buck5(num) अणु			\
	.name		= "BUCK"#num,				\
	.id		= S2MPU02_BUCK##num,			\
	.ops		= &s2mpu02_lकरो_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= S2MPU02_BUCK5_MIN_1081_25MV,		\
	.uV_step	= S2MPU02_BUCK5_STEP_6_25MV,		\
	.n_voltages	= S2MPU02_BUCK_N_VOLTAGES,		\
	.linear_min_sel = S2MPU02_BUCK5_START_SEL,		\
	.ramp_delay	= S2MPU02_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPU02_REG_B5CTRL2,			\
	.vsel_mask	= S2MPU02_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPU02_REG_B5CTRL1,			\
	.enable_mask	= S2MPU02_ENABLE_MASK			\
पूर्ण
#घोषणा regulator_desc_s2mpu02_buck6(num) अणु			\
	.name		= "BUCK"#num,				\
	.id		= S2MPU02_BUCK##num,			\
	.ops		= &s2mpu02_lकरो_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= S2MPU02_BUCK6_MIN_1700MV,		\
	.uV_step	= S2MPU02_BUCK6_STEP_2_50MV,		\
	.n_voltages	= S2MPU02_BUCK_N_VOLTAGES,		\
	.linear_min_sel = S2MPU02_BUCK6_START_SEL,		\
	.ramp_delay	= S2MPU02_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPU02_REG_B6CTRL2,			\
	.vsel_mask	= S2MPU02_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPU02_REG_B6CTRL1,			\
	.enable_mask	= S2MPU02_ENABLE_MASK			\
पूर्ण
#घोषणा regulator_desc_s2mpu02_buck7(num) अणु			\
	.name		= "BUCK"#num,				\
	.id		= S2MPU02_BUCK##num,			\
	.ops		= &s2mpu02_lकरो_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= S2MPU02_BUCK7_MIN_900MV,		\
	.uV_step	= S2MPU02_BUCK7_STEP_6_25MV,		\
	.n_voltages	= S2MPU02_BUCK_N_VOLTAGES,		\
	.linear_min_sel = S2MPU02_BUCK7_START_SEL,		\
	.ramp_delay	= S2MPU02_BUCK_RAMP_DELAY,		\
	.vsel_reg	= S2MPU02_REG_B7CTRL2,			\
	.vsel_mask	= S2MPU02_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPU02_REG_B7CTRL1,			\
	.enable_mask	= S2MPU02_ENABLE_MASK			\
पूर्ण

अटल स्थिर काष्ठा regulator_desc s2mpu02_regulators[] = अणु
	regulator_desc_s2mpu02_lकरो1(1),
	regulator_desc_s2mpu02_lकरो2(2),
	regulator_desc_s2mpu02_lकरो4(3),
	regulator_desc_s2mpu02_lकरो5(4),
	regulator_desc_s2mpu02_lकरो4(5),
	regulator_desc_s2mpu02_lकरो3(6),
	regulator_desc_s2mpu02_lकरो3(7),
	regulator_desc_s2mpu02_lकरो4(8),
	regulator_desc_s2mpu02_lकरो5(9),
	regulator_desc_s2mpu02_lकरो3(10),
	regulator_desc_s2mpu02_lकरो4(11),
	regulator_desc_s2mpu02_lकरो5(12),
	regulator_desc_s2mpu02_lकरो5(13),
	regulator_desc_s2mpu02_lकरो5(14),
	regulator_desc_s2mpu02_lकरो5(15),
	regulator_desc_s2mpu02_lकरो5(16),
	regulator_desc_s2mpu02_lकरो4(17),
	regulator_desc_s2mpu02_lकरो5(18),
	regulator_desc_s2mpu02_lकरो3(19),
	regulator_desc_s2mpu02_lकरो4(20),
	regulator_desc_s2mpu02_lकरो5(21),
	regulator_desc_s2mpu02_lकरो5(22),
	regulator_desc_s2mpu02_lकरो5(23),
	regulator_desc_s2mpu02_lकरो4(24),
	regulator_desc_s2mpu02_lकरो5(25),
	regulator_desc_s2mpu02_lकरो4(26),
	regulator_desc_s2mpu02_lकरो5(27),
	regulator_desc_s2mpu02_lकरो5(28),
	regulator_desc_s2mpu02_buck1234(1),
	regulator_desc_s2mpu02_buck1234(2),
	regulator_desc_s2mpu02_buck1234(3),
	regulator_desc_s2mpu02_buck1234(4),
	regulator_desc_s2mpu02_buck5(5),
	regulator_desc_s2mpu02_buck6(6),
	regulator_desc_s2mpu02_buck7(7),
पूर्ण;

अटल पूर्णांक s2mps11_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा of_regulator_match *rdata = शून्य;
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा s2mps11_info *s2mps11;
	अचिन्हित पूर्णांक rdev_num = 0;
	पूर्णांक i, ret = 0;
	स्थिर काष्ठा regulator_desc *regulators;

	s2mps11 = devm_kzalloc(&pdev->dev, माप(काष्ठा s2mps11_info),
				GFP_KERNEL);
	अगर (!s2mps11)
		वापस -ENOMEM;

	s2mps11->dev_type = platक्रमm_get_device_id(pdev)->driver_data;
	चयन (s2mps11->dev_type) अणु
	हाल S2MPS11X:
		rdev_num = ARRAY_SIZE(s2mps11_regulators);
		regulators = s2mps11_regulators;
		BUILD_BUG_ON(S2MPS_REGULATOR_MAX < ARRAY_SIZE(s2mps11_regulators));
		अवरोध;
	हाल S2MPS13X:
		rdev_num = ARRAY_SIZE(s2mps13_regulators);
		regulators = s2mps13_regulators;
		BUILD_BUG_ON(S2MPS_REGULATOR_MAX < ARRAY_SIZE(s2mps13_regulators));
		अवरोध;
	हाल S2MPS14X:
		rdev_num = ARRAY_SIZE(s2mps14_regulators);
		regulators = s2mps14_regulators;
		BUILD_BUG_ON(S2MPS_REGULATOR_MAX < ARRAY_SIZE(s2mps14_regulators));
		अवरोध;
	हाल S2MPS15X:
		rdev_num = ARRAY_SIZE(s2mps15_regulators);
		regulators = s2mps15_regulators;
		BUILD_BUG_ON(S2MPS_REGULATOR_MAX < ARRAY_SIZE(s2mps15_regulators));
		अवरोध;
	हाल S2MPU02:
		rdev_num = ARRAY_SIZE(s2mpu02_regulators);
		regulators = s2mpu02_regulators;
		BUILD_BUG_ON(S2MPS_REGULATOR_MAX < ARRAY_SIZE(s2mpu02_regulators));
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Invalid device type: %u\n",
				    s2mps11->dev_type);
		वापस -EINVAL;
	पूर्ण

	s2mps11->ext_control_gpiod = devm_kसुस्मृति(&pdev->dev, rdev_num,
			       माप(*s2mps11->ext_control_gpiod), GFP_KERNEL);
	अगर (!s2mps11->ext_control_gpiod)
		वापस -ENOMEM;

	rdata = kसुस्मृति(rdev_num, माप(*rdata), GFP_KERNEL);
	अगर (!rdata)
		वापस -ENOMEM;

	क्रम (i = 0; i < rdev_num; i++)
		rdata[i].name = regulators[i].name;

	ret = s2mps11_pmic_dt_parse(pdev, rdata, s2mps11, rdev_num);
	अगर (ret)
		जाओ out;

	platक्रमm_set_drvdata(pdev, s2mps11);

	config.dev = &pdev->dev;
	config.regmap = iodev->regmap_pmic;
	config.driver_data = s2mps11;
	क्रम (i = 0; i < rdev_num; i++) अणु
		काष्ठा regulator_dev *regulator;

		config.init_data = rdata[i].init_data;
		config.of_node = rdata[i].of_node;
		config.ena_gpiod = s2mps11->ext_control_gpiod[i];
		/*
		 * Hand the GPIO descriptor management over to the regulator
		 * core, हटाओ it from devres management.
		 */
		अगर (config.ena_gpiod)
			devm_gpiod_unhinge(&pdev->dev, config.ena_gpiod);
		regulator = devm_regulator_रेजिस्टर(&pdev->dev,
						&regulators[i], &config);
		अगर (IS_ERR(regulator)) अणु
			ret = PTR_ERR(regulator);
			dev_err(&pdev->dev, "regulator init failed for %d\n",
				i);
			जाओ out;
		पूर्ण

		अगर (config.ena_gpiod) अणु
			ret = s2mps14_pmic_enable_ext_control(s2mps11,
					regulator);
			अगर (ret < 0) अणु
				dev_err(&pdev->dev,
						"failed to enable GPIO control over %s: %d\n",
						regulator->desc->name, ret);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	kमुक्त(rdata);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id s2mps11_pmic_id[] = अणु
	अणु "s2mps11-regulator", S2MPS11Xपूर्ण,
	अणु "s2mps13-regulator", S2MPS13Xपूर्ण,
	अणु "s2mps14-regulator", S2MPS14Xपूर्ण,
	अणु "s2mps15-regulator", S2MPS15Xपूर्ण,
	अणु "s2mpu02-regulator", S2MPU02पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s2mps11_pmic_id);

अटल काष्ठा platक्रमm_driver s2mps11_pmic_driver = अणु
	.driver = अणु
		.name = "s2mps11-pmic",
	पूर्ण,
	.probe = s2mps11_pmic_probe,
	.id_table = s2mps11_pmic_id,
पूर्ण;

module_platक्रमm_driver(s2mps11_pmic_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Sangbeom Kim <sbkim73@samsung.com>");
MODULE_DESCRIPTION("Samsung S2MPS11/S2MPS14/S2MPS15/S2MPU02 Regulator Driver");
MODULE_LICENSE("GPL");
