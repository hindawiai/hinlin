<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2013 Samsung Electronics Co., Ltd
//		http://www.samsung.com

#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/mfd/samsung/core.h>
#समावेश <linux/mfd/samsung/s2mpa01.h>

काष्ठा s2mpa01_info अणु
	पूर्णांक ramp_delay24;
	पूर्णांक ramp_delay3;
	पूर्णांक ramp_delay5;
	पूर्णांक ramp_delay16;
	पूर्णांक ramp_delay7;
	पूर्णांक ramp_delay8910;
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

अटल पूर्णांक s2mpa01_regulator_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
				   अचिन्हित पूर्णांक old_selector,
				   अचिन्हित पूर्णांक new_selector)
अणु
	काष्ठा s2mpa01_info *s2mpa01 = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक ramp_delay = 0;
	पूर्णांक old_volt, new_volt;

	चयन (rdev_get_id(rdev)) अणु
	हाल S2MPA01_BUCK2:
	हाल S2MPA01_BUCK4:
		ramp_delay = s2mpa01->ramp_delay24;
		अवरोध;
	हाल S2MPA01_BUCK3:
		ramp_delay = s2mpa01->ramp_delay3;
		अवरोध;
	हाल S2MPA01_BUCK5:
		ramp_delay = s2mpa01->ramp_delay5;
		अवरोध;
	हाल S2MPA01_BUCK1:
	हाल S2MPA01_BUCK6:
		ramp_delay = s2mpa01->ramp_delay16;
		अवरोध;
	हाल S2MPA01_BUCK7:
		ramp_delay = s2mpa01->ramp_delay7;
		अवरोध;
	हाल S2MPA01_BUCK8:
	हाल S2MPA01_BUCK9:
	हाल S2MPA01_BUCK10:
		ramp_delay = s2mpa01->ramp_delay8910;
		अवरोध;
	पूर्ण

	अगर (ramp_delay == 0)
		ramp_delay = rdev->desc->ramp_delay;

	old_volt = rdev->desc->min_uV + (rdev->desc->uV_step * old_selector);
	new_volt = rdev->desc->min_uV + (rdev->desc->uV_step * new_selector);

	वापस DIV_ROUND_UP(असल(new_volt - old_volt), ramp_delay);
पूर्ण

अटल पूर्णांक s2mpa01_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	काष्ठा s2mpa01_info *s2mpa01 = rdev_get_drvdata(rdev);
	अचिन्हित पूर्णांक ramp_val, ramp_shअगरt, ramp_reg = S2MPA01_REG_RAMP2;
	अचिन्हित पूर्णांक ramp_enable = 1, enable_shअगरt = 0;
	पूर्णांक ret;

	चयन (rdev_get_id(rdev)) अणु
	हाल S2MPA01_BUCK1:
		enable_shअगरt = S2MPA01_BUCK1_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		अगर (ramp_delay > s2mpa01->ramp_delay16)
			s2mpa01->ramp_delay16 = ramp_delay;
		अन्यथा
			ramp_delay = s2mpa01->ramp_delay16;

		ramp_shअगरt = S2MPA01_BUCK16_RAMP_SHIFT;
		अवरोध;
	हाल S2MPA01_BUCK2:
		enable_shअगरt = S2MPA01_BUCK2_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		अगर (ramp_delay > s2mpa01->ramp_delay24)
			s2mpa01->ramp_delay24 = ramp_delay;
		अन्यथा
			ramp_delay = s2mpa01->ramp_delay24;

		ramp_shअगरt = S2MPA01_BUCK24_RAMP_SHIFT;
		ramp_reg = S2MPA01_REG_RAMP1;
		अवरोध;
	हाल S2MPA01_BUCK3:
		enable_shअगरt = S2MPA01_BUCK3_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		s2mpa01->ramp_delay3 = ramp_delay;
		ramp_shअगरt = S2MPA01_BUCK3_RAMP_SHIFT;
		ramp_reg = S2MPA01_REG_RAMP1;
		अवरोध;
	हाल S2MPA01_BUCK4:
		enable_shअगरt = S2MPA01_BUCK4_RAMP_EN_SHIFT;
		अगर (!ramp_delay) अणु
			ramp_enable = 0;
			अवरोध;
		पूर्ण

		अगर (ramp_delay > s2mpa01->ramp_delay24)
			s2mpa01->ramp_delay24 = ramp_delay;
		अन्यथा
			ramp_delay = s2mpa01->ramp_delay24;

		ramp_shअगरt = S2MPA01_BUCK24_RAMP_SHIFT;
		ramp_reg = S2MPA01_REG_RAMP1;
		अवरोध;
	हाल S2MPA01_BUCK5:
		s2mpa01->ramp_delay5 = ramp_delay;
		ramp_shअगरt = S2MPA01_BUCK5_RAMP_SHIFT;
		अवरोध;
	हाल S2MPA01_BUCK6:
		अगर (ramp_delay > s2mpa01->ramp_delay16)
			s2mpa01->ramp_delay16 = ramp_delay;
		अन्यथा
			ramp_delay = s2mpa01->ramp_delay16;

		ramp_shअगरt = S2MPA01_BUCK16_RAMP_SHIFT;
		अवरोध;
	हाल S2MPA01_BUCK7:
		s2mpa01->ramp_delay7 = ramp_delay;
		ramp_shअगरt = S2MPA01_BUCK7_RAMP_SHIFT;
		अवरोध;
	हाल S2MPA01_BUCK8:
	हाल S2MPA01_BUCK9:
	हाल S2MPA01_BUCK10:
		अगर (ramp_delay > s2mpa01->ramp_delay8910)
			s2mpa01->ramp_delay8910 = ramp_delay;
		अन्यथा
			ramp_delay = s2mpa01->ramp_delay8910;

		ramp_shअगरt = S2MPA01_BUCK8910_RAMP_SHIFT;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (!ramp_enable)
		जाओ ramp_disable;

	/* Ramp delay can be enabled/disabled only क्रम buck[1234] */
	अगर (rdev_get_id(rdev) >= S2MPA01_BUCK1 &&
			rdev_get_id(rdev) <= S2MPA01_BUCK4) अणु
		ret = regmap_update_bits(rdev->regmap, S2MPA01_REG_RAMP1,
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
	वापस regmap_update_bits(rdev->regmap, S2MPA01_REG_RAMP1,
				  1 << enable_shअगरt, 0);
पूर्ण

अटल स्थिर काष्ठा regulator_ops s2mpa01_lकरो_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops s2mpa01_buck_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.is_enabled		= regulator_is_enabled_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= s2mpa01_regulator_set_voltage_समय_sel,
	.set_ramp_delay		= s2mpa01_set_ramp_delay,
पूर्ण;

#घोषणा regulator_desc_lकरो(num, step) अणु			\
	.name		= "LDO"#num,			\
	.of_match	= of_match_ptr("LDO"#num),	\
	.regulators_node = of_match_ptr("regulators"),	\
	.id		= S2MPA01_LDO##num,		\
	.ops		= &s2mpa01_lकरो_ops,		\
	.type		= REGULATOR_VOLTAGE,		\
	.owner		= THIS_MODULE,			\
	.min_uV		= MIN_800_MV,			\
	.uV_step	= step,				\
	.n_voltages	= S2MPA01_LDO_N_VOLTAGES,	\
	.vsel_reg	= S2MPA01_REG_L1CTRL + num - 1,	\
	.vsel_mask	= S2MPA01_LDO_VSEL_MASK,	\
	.enable_reg	= S2MPA01_REG_L1CTRL + num - 1,	\
	.enable_mask	= S2MPA01_ENABLE_MASK		\
पूर्ण

#घोषणा regulator_desc_buck1_4(num)	अणु			\
	.name		= "BUCK"#num,				\
	.of_match	= of_match_ptr("BUCK"#num),		\
	.regulators_node = of_match_ptr("regulators"),		\
	.id		= S2MPA01_BUCK##num,			\
	.ops		= &s2mpa01_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= MIN_600_MV,				\
	.uV_step	= STEP_6_25_MV,				\
	.n_voltages	= S2MPA01_BUCK_N_VOLTAGES,		\
	.ramp_delay	= S2MPA01_RAMP_DELAY,			\
	.vsel_reg	= S2MPA01_REG_B1CTRL2 + (num - 1) * 2,	\
	.vsel_mask	= S2MPA01_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPA01_REG_B1CTRL1 + (num - 1) * 2,	\
	.enable_mask	= S2MPA01_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_buck5	अणु				\
	.name		= "BUCK5",				\
	.of_match	= of_match_ptr("BUCK5"),		\
	.regulators_node = of_match_ptr("regulators"),		\
	.id		= S2MPA01_BUCK5,			\
	.ops		= &s2mpa01_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= MIN_800_MV,				\
	.uV_step	= STEP_6_25_MV,				\
	.n_voltages	= S2MPA01_BUCK_N_VOLTAGES,		\
	.ramp_delay	= S2MPA01_RAMP_DELAY,			\
	.vsel_reg	= S2MPA01_REG_B5CTRL2,			\
	.vsel_mask	= S2MPA01_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPA01_REG_B5CTRL1,			\
	.enable_mask	= S2MPA01_ENABLE_MASK			\
पूर्ण

#घोषणा regulator_desc_buck6_10(num, min, step) अणु			\
	.name		= "BUCK"#num,				\
	.of_match	= of_match_ptr("BUCK"#num),		\
	.regulators_node = of_match_ptr("regulators"),		\
	.id		= S2MPA01_BUCK##num,			\
	.ops		= &s2mpa01_buck_ops,			\
	.type		= REGULATOR_VOLTAGE,			\
	.owner		= THIS_MODULE,				\
	.min_uV		= min,					\
	.uV_step	= step,					\
	.n_voltages	= S2MPA01_BUCK_N_VOLTAGES,		\
	.ramp_delay	= S2MPA01_RAMP_DELAY,			\
	.vsel_reg	= S2MPA01_REG_B6CTRL2 + (num - 6) * 2,	\
	.vsel_mask	= S2MPA01_BUCK_VSEL_MASK,		\
	.enable_reg	= S2MPA01_REG_B6CTRL1 + (num - 6) * 2,	\
	.enable_mask	= S2MPA01_ENABLE_MASK			\
पूर्ण

अटल स्थिर काष्ठा regulator_desc regulators[] = अणु
	regulator_desc_lकरो(1, STEP_25_MV),
	regulator_desc_lकरो(2, STEP_50_MV),
	regulator_desc_lकरो(3, STEP_50_MV),
	regulator_desc_lकरो(4, STEP_50_MV),
	regulator_desc_lकरो(5, STEP_25_MV),
	regulator_desc_lकरो(6, STEP_25_MV),
	regulator_desc_lकरो(7, STEP_50_MV),
	regulator_desc_lकरो(8, STEP_50_MV),
	regulator_desc_lकरो(9, STEP_50_MV),
	regulator_desc_lकरो(10, STEP_50_MV),
	regulator_desc_lकरो(11, STEP_50_MV),
	regulator_desc_lकरो(12, STEP_50_MV),
	regulator_desc_lकरो(13, STEP_50_MV),
	regulator_desc_lकरो(14, STEP_50_MV),
	regulator_desc_lकरो(15, STEP_50_MV),
	regulator_desc_lकरो(16, STEP_50_MV),
	regulator_desc_lकरो(17, STEP_50_MV),
	regulator_desc_lकरो(18, STEP_50_MV),
	regulator_desc_lकरो(19, STEP_50_MV),
	regulator_desc_lकरो(20, STEP_50_MV),
	regulator_desc_lकरो(21, STEP_50_MV),
	regulator_desc_lकरो(22, STEP_50_MV),
	regulator_desc_lकरो(23, STEP_50_MV),
	regulator_desc_lकरो(24, STEP_50_MV),
	regulator_desc_lकरो(25, STEP_50_MV),
	regulator_desc_lकरो(26, STEP_25_MV),
	regulator_desc_buck1_4(1),
	regulator_desc_buck1_4(2),
	regulator_desc_buck1_4(3),
	regulator_desc_buck1_4(4),
	regulator_desc_buck5,
	regulator_desc_buck6_10(6, MIN_600_MV, STEP_6_25_MV),
	regulator_desc_buck6_10(7, MIN_600_MV, STEP_6_25_MV),
	regulator_desc_buck6_10(8, MIN_800_MV, STEP_12_5_MV),
	regulator_desc_buck6_10(9, MIN_1500_MV, STEP_12_5_MV),
	regulator_desc_buck6_10(10, MIN_1000_MV, STEP_12_5_MV),
पूर्ण;

अटल पूर्णांक s2mpa01_pmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा regulator_config config = अणु पूर्ण;
	काष्ठा s2mpa01_info *s2mpa01;
	पूर्णांक i;

	s2mpa01 = devm_kzalloc(&pdev->dev, माप(*s2mpa01), GFP_KERNEL);
	अगर (!s2mpa01)
		वापस -ENOMEM;

	config.dev = iodev->dev;
	config.regmap = iodev->regmap_pmic;
	config.driver_data = s2mpa01;

	क्रम (i = 0; i < S2MPA01_REGULATOR_MAX; i++) अणु
		काष्ठा regulator_dev *rdev;

		rdev = devm_regulator_रेजिस्टर(&pdev->dev,
						&regulators[i], &config);
		अगर (IS_ERR(rdev)) अणु
			dev_err(&pdev->dev, "regulator init failed for %d\n",
				i);
			वापस PTR_ERR(rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id s2mpa01_pmic_id[] = अणु
	अणु "s2mpa01-pmic", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, s2mpa01_pmic_id);

अटल काष्ठा platक्रमm_driver s2mpa01_pmic_driver = अणु
	.driver = अणु
		.name = "s2mpa01-pmic",
	पूर्ण,
	.probe = s2mpa01_pmic_probe,
	.id_table = s2mpa01_pmic_id,
पूर्ण;

module_platक्रमm_driver(s2mpa01_pmic_driver);

/* Module inक्रमmation */
MODULE_AUTHOR("Sangbeom Kim <sbkim73@samsung.com>");
MODULE_AUTHOR("Sachin Kamat <sachin.kamat@samsung.com>");
MODULE_DESCRIPTION("Samsung S2MPA01 Regulator Driver");
MODULE_LICENSE("GPL");
