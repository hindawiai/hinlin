<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Regulator driver क्रम Rockchip RK805/RK808/RK818
 *
 * Copyright (c) 2014, Fuzhou Rockchip Electronics Co., Ltd
 *
 * Author: Chris Zhong <zyw@rock-chips.com>
 * Author: Zhang Qing <zhangqing@rock-chips.com>
 *
 * Copyright (C) 2016 PHYTEC Messtechnik GmbH
 *
 * Author: Wadim Egorov <w.egorov@phytec.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/mfd/rk808.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/of_regulator.h>
#समावेश <linux/gpio/consumer.h>

/* Field Definitions */
#घोषणा RK808_BUCK_VSEL_MASK	0x3f
#घोषणा RK808_BUCK4_VSEL_MASK	0xf
#घोषणा RK808_LDO_VSEL_MASK	0x1f

#घोषणा RK809_BUCK5_VSEL_MASK		0x7

#घोषणा RK817_LDO_VSEL_MASK		0x7f
#घोषणा RK817_BOOST_VSEL_MASK		0x7
#घोषणा RK817_BUCK_VSEL_MASK		0x7f

#घोषणा RK818_BUCK_VSEL_MASK		0x3f
#घोषणा RK818_BUCK4_VSEL_MASK		0x1f
#घोषणा RK818_LDO_VSEL_MASK		0x1f
#घोषणा RK818_LDO3_ON_VSEL_MASK		0xf
#घोषणा RK818_BOOST_ON_VSEL_MASK	0xe0

/* Ramp rate definitions क्रम buck1 / buck2 only */
#घोषणा RK808_RAMP_RATE_OFFSET		3
#घोषणा RK808_RAMP_RATE_MASK		(3 << RK808_RAMP_RATE_OFFSET)
#घोषणा RK808_RAMP_RATE_2MV_PER_US	(0 << RK808_RAMP_RATE_OFFSET)
#घोषणा RK808_RAMP_RATE_4MV_PER_US	(1 << RK808_RAMP_RATE_OFFSET)
#घोषणा RK808_RAMP_RATE_6MV_PER_US	(2 << RK808_RAMP_RATE_OFFSET)
#घोषणा RK808_RAMP_RATE_10MV_PER_US	(3 << RK808_RAMP_RATE_OFFSET)

#घोषणा RK808_DVS2_POL		BIT(2)
#घोषणा RK808_DVS1_POL		BIT(1)

/* Offset from XXX_ON_VSEL to XXX_SLP_VSEL */
#घोषणा RK808_SLP_REG_OFFSET 1

/* Offset from XXX_ON_VSEL to XXX_DVS_VSEL */
#घोषणा RK808_DVS_REG_OFFSET 2

/* Offset from XXX_EN_REG to SLEEP_SET_OFF_XXX */
#घोषणा RK808_SLP_SET_OFF_REG_OFFSET 2

/* max steps क्रम increase voltage of Buck1/2, equal 100mv*/
#घोषणा MAX_STEPS_ONE_TIME 8

#घोषणा ENABLE_MASK(id)			(BIT(id) | BIT(4 + (id)))
#घोषणा DISABLE_VAL(id)			(BIT(4 + (id)))

#घोषणा RK817_BOOST_DESC(_id, _match, _supply, _min, _max, _step, _vreg,\
	_vmask, _ereg, _emask, _enval, _disval, _eसमय, m_drop)		\
	अणु							\
		.name		= (_match),				\
		.supply_name	= (_supply),				\
		.of_match	= of_match_ptr(_match),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.type		= REGULATOR_VOLTAGE,			\
		.id		= (_id),				\
		.n_voltages	= (((_max) - (_min)) / (_step) + 1),	\
		.owner		= THIS_MODULE,				\
		.min_uV		= (_min) * 1000,			\
		.uV_step	= (_step) * 1000,			\
		.vsel_reg	= (_vreg),				\
		.vsel_mask	= (_vmask),				\
		.enable_reg	= (_ereg),				\
		.enable_mask	= (_emask),				\
		.enable_val     = (_enval),				\
		.disable_val     = (_disval),				\
		.enable_समय	= (_eसमय),				\
		.min_dropout_uV = (m_drop) * 1000,			\
		.ops		= &rk817_boost_ops,			\
	पूर्ण

#घोषणा RK8XX_DESC_COM(_id, _match, _supply, _min, _max, _step, _vreg,	\
	_vmask, _ereg, _emask, _enval, _disval, _eसमय, _ops)		\
	अणु								\
		.name		= (_match),				\
		.supply_name	= (_supply),				\
		.of_match	= of_match_ptr(_match),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.type		= REGULATOR_VOLTAGE,			\
		.id		= (_id),				\
		.n_voltages	= (((_max) - (_min)) / (_step) + 1),	\
		.owner		= THIS_MODULE,				\
		.min_uV		= (_min) * 1000,			\
		.uV_step	= (_step) * 1000,			\
		.vsel_reg	= (_vreg),				\
		.vsel_mask	= (_vmask),				\
		.enable_reg	= (_ereg),				\
		.enable_mask	= (_emask),				\
		.enable_val     = (_enval),				\
		.disable_val     = (_disval),				\
		.enable_समय	= (_eसमय),				\
		.ops		= _ops,			\
	पूर्ण

#घोषणा RK805_DESC(_id, _match, _supply, _min, _max, _step, _vreg,	\
	_vmask, _ereg, _emask, _eसमय)					\
	RK8XX_DESC_COM(_id, _match, _supply, _min, _max, _step, _vreg,	\
	_vmask, _ereg, _emask, 0, 0, _eसमय, &rk805_reg_ops)

#घोषणा RK8XX_DESC(_id, _match, _supply, _min, _max, _step, _vreg,	\
	_vmask, _ereg, _emask, _eसमय)					\
	RK8XX_DESC_COM(_id, _match, _supply, _min, _max, _step, _vreg,	\
	_vmask, _ereg, _emask, 0, 0, _eसमय, &rk808_reg_ops)

#घोषणा RK817_DESC(_id, _match, _supply, _min, _max, _step, _vreg,	\
	_vmask, _ereg, _emask, _disval, _eसमय)				\
	RK8XX_DESC_COM(_id, _match, _supply, _min, _max, _step, _vreg,	\
	_vmask, _ereg, _emask, _emask, _disval, _eसमय, &rk817_reg_ops)

#घोषणा RKXX_DESC_SWITCH_COM(_id, _match, _supply, _ereg, _emask,	\
	_enval, _disval, _ops)						\
	अणु								\
		.name		= (_match),				\
		.supply_name	= (_supply),				\
		.of_match	= of_match_ptr(_match),			\
		.regulators_node = of_match_ptr("regulators"),		\
		.type		= REGULATOR_VOLTAGE,			\
		.id		= (_id),				\
		.enable_reg	= (_ereg),				\
		.enable_mask	= (_emask),				\
		.enable_val     = (_enval),				\
		.disable_val     = (_disval),				\
		.owner		= THIS_MODULE,				\
		.ops		= _ops					\
	पूर्ण

#घोषणा RK817_DESC_SWITCH(_id, _match, _supply, _ereg, _emask,		\
	_disval)							\
	RKXX_DESC_SWITCH_COM(_id, _match, _supply, _ereg, _emask,	\
	_emask, _disval, &rk817_चयन_ops)

#घोषणा RK8XX_DESC_SWITCH(_id, _match, _supply, _ereg, _emask)		\
	RKXX_DESC_SWITCH_COM(_id, _match, _supply, _ereg, _emask,	\
	0, 0, &rk808_चयन_ops)

काष्ठा rk808_regulator_data अणु
	काष्ठा gpio_desc *dvs_gpio[2];
पूर्ण;

अटल स्थिर पूर्णांक rk808_buck_config_regs[] = अणु
	RK808_BUCK1_CONFIG_REG,
	RK808_BUCK2_CONFIG_REG,
	RK808_BUCK3_CONFIG_REG,
	RK808_BUCK4_CONFIG_REG,
पूर्ण;

अटल स्थिर काष्ठा linear_range rk808_lकरो3_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(800000, 0, 13, 100000),
	REGULATOR_LINEAR_RANGE(2500000, 15, 15, 0),
पूर्ण;

#घोषणा RK809_BUCK5_SEL_CNT		(8)

अटल स्थिर काष्ठा linear_range rk809_buck5_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(1500000, 0, 0, 0),
	REGULATOR_LINEAR_RANGE(1800000, 1, 3, 200000),
	REGULATOR_LINEAR_RANGE(2800000, 4, 5, 200000),
	REGULATOR_LINEAR_RANGE(3300000, 6, 7, 300000),
पूर्ण;

#घोषणा RK817_BUCK1_MIN0 500000
#घोषणा RK817_BUCK1_MAX0 1500000

#घोषणा RK817_BUCK1_MIN1 1600000
#घोषणा RK817_BUCK1_MAX1 2400000

#घोषणा RK817_BUCK3_MAX1 3400000

#घोषणा RK817_BUCK1_STP0 12500
#घोषणा RK817_BUCK1_STP1 100000

#घोषणा RK817_BUCK1_SEL0 ((RK817_BUCK1_MAX0 - RK817_BUCK1_MIN0) /\
						  RK817_BUCK1_STP0)
#घोषणा RK817_BUCK1_SEL1 ((RK817_BUCK1_MAX1 - RK817_BUCK1_MIN1) /\
						  RK817_BUCK1_STP1)

#घोषणा RK817_BUCK3_SEL1 ((RK817_BUCK3_MAX1 - RK817_BUCK1_MIN1) /\
						  RK817_BUCK1_STP1)

#घोषणा RK817_BUCK1_SEL_CNT (RK817_BUCK1_SEL0 + RK817_BUCK1_SEL1 + 1)
#घोषणा RK817_BUCK3_SEL_CNT (RK817_BUCK1_SEL0 + RK817_BUCK3_SEL1 + 1)

अटल स्थिर काष्ठा linear_range rk817_buck1_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(RK817_BUCK1_MIN0, 0,
			       RK817_BUCK1_SEL0, RK817_BUCK1_STP0),
	REGULATOR_LINEAR_RANGE(RK817_BUCK1_MIN1, RK817_BUCK1_SEL0 + 1,
			       RK817_BUCK1_SEL_CNT, RK817_BUCK1_STP1),
पूर्ण;

अटल स्थिर काष्ठा linear_range rk817_buck3_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(RK817_BUCK1_MIN0, 0,
			       RK817_BUCK1_SEL0, RK817_BUCK1_STP0),
	REGULATOR_LINEAR_RANGE(RK817_BUCK1_MIN1, RK817_BUCK1_SEL0 + 1,
			       RK817_BUCK3_SEL_CNT, RK817_BUCK1_STP1),
पूर्ण;

अटल पूर्णांक rk808_buck1_2_get_voltage_sel_regmap(काष्ठा regulator_dev *rdev)
अणु
	काष्ठा rk808_regulator_data *pdata = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा gpio_desc *gpio = pdata->dvs_gpio[id];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!gpio || gpiod_get_value(gpio) == 0)
		वापस regulator_get_voltage_sel_regmap(rdev);

	ret = regmap_पढ़ो(rdev->regmap,
			  rdev->desc->vsel_reg + RK808_DVS_REG_OFFSET,
			  &val);
	अगर (ret != 0)
		वापस ret;

	val &= rdev->desc->vsel_mask;
	val >>= ffs(rdev->desc->vsel_mask) - 1;

	वापस val;
पूर्ण

अटल पूर्णांक rk808_buck1_2_i2c_set_voltage_sel(काष्ठा regulator_dev *rdev,
					     अचिन्हित sel)
अणु
	पूर्णांक ret, delta_sel;
	अचिन्हित पूर्णांक old_sel, पंचांगp, val, mask = rdev->desc->vsel_mask;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_reg, &val);
	अगर (ret != 0)
		वापस ret;

	पंचांगp = val & ~mask;
	old_sel = val & mask;
	old_sel >>= ffs(mask) - 1;
	delta_sel = sel - old_sel;

	/*
	 * If directly modअगरy the रेजिस्टर to change the voltage, we will face
	 * the risk of overshoot. Put it पूर्णांकo a multi-step, can effectively
	 * aव्योम this problem, a step is 100mv here.
	 */
	जबतक (delta_sel > MAX_STEPS_ONE_TIME) अणु
		old_sel += MAX_STEPS_ONE_TIME;
		val = old_sel << (ffs(mask) - 1);
		val |= पंचांगp;

		/*
		 * i2c is 400kHz (2.5us per bit) and we must transmit _at least_
		 * 3 bytes (24 bits) plus start and stop so 26 bits.  So we've
		 * got more than 65 us between each voltage change and thus
		 * won't ramp faster than ~1500 uV / us.
		 */
		ret = regmap_ग_लिखो(rdev->regmap, rdev->desc->vsel_reg, val);
		delta_sel = sel - old_sel;
	पूर्ण

	sel <<= ffs(mask) - 1;
	val = पंचांगp | sel;
	ret = regmap_ग_लिखो(rdev->regmap, rdev->desc->vsel_reg, val);

	/*
	 * When we change the voltage रेजिस्टर directly, the ramp rate is about
	 * 100000uv/us, रुको 1us to make sure the target voltage to be stable,
	 * so we needn't रुको extra समय after that.
	 */
	udelay(1);

	वापस ret;
पूर्ण

अटल पूर्णांक rk808_buck1_2_set_voltage_sel(काष्ठा regulator_dev *rdev,
					 अचिन्हित sel)
अणु
	काष्ठा rk808_regulator_data *pdata = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा gpio_desc *gpio = pdata->dvs_gpio[id];
	अचिन्हित पूर्णांक reg = rdev->desc->vsel_reg;
	अचिन्हित old_sel;
	पूर्णांक ret, gpio_level;

	अगर (!gpio)
		वापस rk808_buck1_2_i2c_set_voltage_sel(rdev, sel);

	gpio_level = gpiod_get_value(gpio);
	अगर (gpio_level == 0) अणु
		reg += RK808_DVS_REG_OFFSET;
		ret = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_reg, &old_sel);
	पूर्ण अन्यथा अणु
		ret = regmap_पढ़ो(rdev->regmap,
				  reg + RK808_DVS_REG_OFFSET,
				  &old_sel);
	पूर्ण

	अगर (ret != 0)
		वापस ret;

	sel <<= ffs(rdev->desc->vsel_mask) - 1;
	sel |= old_sel & ~rdev->desc->vsel_mask;

	ret = regmap_ग_लिखो(rdev->regmap, reg, sel);
	अगर (ret)
		वापस ret;

	gpiod_set_value(gpio, !gpio_level);

	वापस ret;
पूर्ण

अटल पूर्णांक rk808_buck1_2_set_voltage_समय_sel(काष्ठा regulator_dev *rdev,
				       अचिन्हित पूर्णांक old_selector,
				       अचिन्हित पूर्णांक new_selector)
अणु
	काष्ठा rk808_regulator_data *pdata = rdev_get_drvdata(rdev);
	पूर्णांक id = rdev_get_id(rdev);
	काष्ठा gpio_desc *gpio = pdata->dvs_gpio[id];

	/* अगर there is no dvs1/2 pin, we करोn't need रुको extra समय here. */
	अगर (!gpio)
		वापस 0;

	वापस regulator_set_voltage_समय_sel(rdev, old_selector, new_selector);
पूर्ण

अटल पूर्णांक rk808_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	अचिन्हित पूर्णांक ramp_value = RK808_RAMP_RATE_10MV_PER_US;
	अचिन्हित पूर्णांक reg = rk808_buck_config_regs[rdev_get_id(rdev)];

	चयन (ramp_delay) अणु
	हाल 1 ... 2000:
		ramp_value = RK808_RAMP_RATE_2MV_PER_US;
		अवरोध;
	हाल 2001 ... 4000:
		ramp_value = RK808_RAMP_RATE_4MV_PER_US;
		अवरोध;
	हाल 4001 ... 6000:
		ramp_value = RK808_RAMP_RATE_6MV_PER_US;
		अवरोध;
	हाल 6001 ... 10000:
		अवरोध;
	शेष:
		pr_warn("%s ramp_delay: %d not supported, setting 10000\n",
			rdev->desc->name, ramp_delay);
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, reg,
				  RK808_RAMP_RATE_MASK, ramp_value);
पूर्ण

/*
 * RK817 RK809
 */
अटल पूर्णांक rk817_set_ramp_delay(काष्ठा regulator_dev *rdev, पूर्णांक ramp_delay)
अणु
	अचिन्हित पूर्णांक ramp_value = RK817_RAMP_RATE_25MV_PER_US;
	अचिन्हित पूर्णांक reg = RK817_BUCK_CONFIG_REG(rdev_get_id(rdev));

	चयन (ramp_delay) अणु
	हाल 0 ... 3000:
		ramp_value = RK817_RAMP_RATE_3MV_PER_US;
		अवरोध;
	हाल 3001 ... 6300:
		ramp_value = RK817_RAMP_RATE_6_3MV_PER_US;
		अवरोध;
	हाल 6301 ... 12500:
		ramp_value = RK817_RAMP_RATE_12_5MV_PER_US;
		अवरोध;
	हाल 12501 ... 25000:
		अवरोध;
	शेष:
		dev_warn(&rdev->dev,
			 "%s ramp_delay: %d not supported, setting 25000\n",
			 rdev->desc->name, ramp_delay);
	पूर्ण

	वापस regmap_update_bits(rdev->regmap, reg,
				  RK817_RAMP_RATE_MASK, ramp_value);
पूर्ण

अटल पूर्णांक rk808_set_suspend_voltage(काष्ठा regulator_dev *rdev, पूर्णांक uv)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक sel = regulator_map_voltage_linear(rdev, uv, uv);

	अगर (sel < 0)
		वापस -EINVAL;

	reg = rdev->desc->vsel_reg + RK808_SLP_REG_OFFSET;

	वापस regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->vsel_mask,
				  sel);
पूर्ण

अटल पूर्णांक rk808_set_suspend_voltage_range(काष्ठा regulator_dev *rdev, पूर्णांक uv)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक sel = regulator_map_voltage_linear_range(rdev, uv, uv);

	अगर (sel < 0)
		वापस -EINVAL;

	reg = rdev->desc->vsel_reg + RK808_SLP_REG_OFFSET;

	वापस regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->vsel_mask,
				  sel);
पूर्ण

अटल पूर्णांक rk805_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक reg;

	reg = rdev->desc->enable_reg + RK808_SLP_SET_OFF_REG_OFFSET;

	वापस regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->enable_mask,
				  rdev->desc->enable_mask);
पूर्ण

अटल पूर्णांक rk805_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक reg;

	reg = rdev->desc->enable_reg + RK808_SLP_SET_OFF_REG_OFFSET;

	वापस regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->enable_mask,
				  0);
पूर्ण

अटल पूर्णांक rk808_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक reg;

	reg = rdev->desc->enable_reg + RK808_SLP_SET_OFF_REG_OFFSET;

	वापस regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->enable_mask,
				  0);
पूर्ण

अटल पूर्णांक rk808_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक reg;

	reg = rdev->desc->enable_reg + RK808_SLP_SET_OFF_REG_OFFSET;

	वापस regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->enable_mask,
				  rdev->desc->enable_mask);
पूर्ण

अटल पूर्णांक rk817_set_suspend_enable_ctrl(काष्ठा regulator_dev *rdev,
					 अचिन्हित पूर्णांक en)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक id = rdev_get_id(rdev);
	अचिन्हित पूर्णांक id_slp, msk, val;

	अगर (id >= RK817_ID_DCDC1 && id <= RK817_ID_DCDC4)
		id_slp = id;
	अन्यथा अगर (id >= RK817_ID_LDO1 && id <= RK817_ID_LDO8)
		id_slp = 8 + (id - RK817_ID_LDO1);
	अन्यथा अगर (id >= RK817_ID_LDO9 && id <= RK809_ID_SW2)
		id_slp = 4 + (id - RK817_ID_LDO9);
	अन्यथा
		वापस -EINVAL;

	reg = RK817_POWER_SLP_EN_REG(id_slp / 8);

	msk = BIT(id_slp % 8);
	अगर (en)
		val = msk;
	अन्यथा
		val = 0;

	वापस regmap_update_bits(rdev->regmap, reg, msk, val);
पूर्ण

अटल पूर्णांक rk817_set_suspend_enable(काष्ठा regulator_dev *rdev)
अणु
	वापस rk817_set_suspend_enable_ctrl(rdev, 1);
पूर्ण

अटल पूर्णांक rk817_set_suspend_disable(काष्ठा regulator_dev *rdev)
अणु
	वापस rk817_set_suspend_enable_ctrl(rdev, 0);
पूर्ण

अटल पूर्णांक rk8xx_set_suspend_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	अचिन्हित पूर्णांक reg;

	reg = rdev->desc->vsel_reg + RK808_SLP_REG_OFFSET;

	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		वापस regmap_update_bits(rdev->regmap, reg,
					  PWM_MODE_MSK, FPWM_MODE);
	हाल REGULATOR_MODE_NORMAL:
		वापस regmap_update_bits(rdev->regmap, reg,
					  PWM_MODE_MSK, AUTO_PWM_MODE);
	शेष:
		dev_err(&rdev->dev, "do not support this mode\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rk8xx_set_mode(काष्ठा regulator_dev *rdev, अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल REGULATOR_MODE_FAST:
		वापस regmap_update_bits(rdev->regmap, rdev->desc->vsel_reg,
					  PWM_MODE_MSK, FPWM_MODE);
	हाल REGULATOR_MODE_NORMAL:
		वापस regmap_update_bits(rdev->regmap, rdev->desc->vsel_reg,
					  PWM_MODE_MSK, AUTO_PWM_MODE);
	शेष:
		dev_err(&rdev->dev, "do not support this mode\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक rk8xx_get_mode(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो(rdev->regmap, rdev->desc->vsel_reg, &val);
	अगर (err)
		वापस err;

	अगर (val & FPWM_MODE)
		वापस REGULATOR_MODE_FAST;
	अन्यथा
		वापस REGULATOR_MODE_NORMAL;
पूर्ण

अटल पूर्णांक rk8xx_is_enabled_wmsk_regmap(काष्ठा regulator_dev *rdev)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rdev->regmap, rdev->desc->enable_reg, &val);
	अगर (ret != 0)
		वापस ret;

	/* add ग_लिखो mask bit */
	val |= (rdev->desc->enable_mask & 0xf0);
	val &= rdev->desc->enable_mask;

	अगर (rdev->desc->enable_is_inverted) अणु
		अगर (rdev->desc->enable_val)
			वापस val != rdev->desc->enable_val;
		वापस (val == 0);
	पूर्ण
	अगर (rdev->desc->enable_val)
		वापस val == rdev->desc->enable_val;
	वापस val != 0;
पूर्ण

अटल अचिन्हित पूर्णांक rk8xx_regulator_of_map_mode(अचिन्हित पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल 1:
		वापस REGULATOR_MODE_FAST;
	हाल 2:
		वापस REGULATOR_MODE_NORMAL;
	शेष:
		वापस REGULATOR_MODE_INVALID;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regulator_ops rk805_reg_ops = अणु
	.list_voltage           = regulator_list_voltage_linear,
	.map_voltage            = regulator_map_voltage_linear,
	.get_voltage_sel        = regulator_get_voltage_sel_regmap,
	.set_voltage_sel        = regulator_set_voltage_sel_regmap,
	.enable                 = regulator_enable_regmap,
	.disable                = regulator_disable_regmap,
	.is_enabled             = regulator_is_enabled_regmap,
	.set_suspend_voltage    = rk808_set_suspend_voltage,
	.set_suspend_enable     = rk805_set_suspend_enable,
	.set_suspend_disable    = rk805_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk805_चयन_ops = अणु
	.enable                 = regulator_enable_regmap,
	.disable                = regulator_disable_regmap,
	.is_enabled             = regulator_is_enabled_regmap,
	.set_suspend_enable     = rk805_set_suspend_enable,
	.set_suspend_disable    = rk805_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk808_buck1_2_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= rk808_buck1_2_get_voltage_sel_regmap,
	.set_voltage_sel	= rk808_buck1_2_set_voltage_sel,
	.set_voltage_समय_sel	= rk808_buck1_2_set_voltage_समय_sel,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_ramp_delay		= rk808_set_ramp_delay,
	.set_suspend_voltage	= rk808_set_suspend_voltage,
	.set_suspend_enable	= rk808_set_suspend_enable,
	.set_suspend_disable	= rk808_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk808_reg_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_suspend_voltage	= rk808_set_suspend_voltage,
	.set_suspend_enable	= rk808_set_suspend_enable,
	.set_suspend_disable	= rk808_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk808_reg_ops_ranges = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_suspend_voltage	= rk808_set_suspend_voltage_range,
	.set_suspend_enable	= rk808_set_suspend_enable,
	.set_suspend_disable	= rk808_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk808_चयन_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= regulator_is_enabled_regmap,
	.set_suspend_enable	= rk808_set_suspend_enable,
	.set_suspend_disable	= rk808_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा linear_range rk805_buck_1_2_voltage_ranges[] = अणु
	REGULATOR_LINEAR_RANGE(712500, 0, 59, 12500),
	REGULATOR_LINEAR_RANGE(1800000, 60, 62, 200000),
	REGULATOR_LINEAR_RANGE(2300000, 63, 63, 0),
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk809_buck5_ops_range = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= rk8xx_is_enabled_wmsk_regmap,
	.set_suspend_voltage	= rk808_set_suspend_voltage_range,
	.set_suspend_enable	= rk817_set_suspend_enable,
	.set_suspend_disable	= rk817_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk817_reg_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= rk8xx_is_enabled_wmsk_regmap,
	.set_suspend_voltage	= rk808_set_suspend_voltage,
	.set_suspend_enable	= rk817_set_suspend_enable,
	.set_suspend_disable	= rk817_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk817_boost_ops = अणु
	.list_voltage		= regulator_list_voltage_linear,
	.map_voltage		= regulator_map_voltage_linear,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= rk8xx_is_enabled_wmsk_regmap,
	.set_suspend_enable	= rk817_set_suspend_enable,
	.set_suspend_disable	= rk817_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk817_buck_ops_range = अणु
	.list_voltage		= regulator_list_voltage_linear_range,
	.map_voltage		= regulator_map_voltage_linear_range,
	.get_voltage_sel	= regulator_get_voltage_sel_regmap,
	.set_voltage_sel	= regulator_set_voltage_sel_regmap,
	.set_voltage_समय_sel	= regulator_set_voltage_समय_sel,
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= rk8xx_is_enabled_wmsk_regmap,
	.set_mode		= rk8xx_set_mode,
	.get_mode		= rk8xx_get_mode,
	.set_suspend_mode	= rk8xx_set_suspend_mode,
	.set_ramp_delay		= rk817_set_ramp_delay,
	.set_suspend_voltage	= rk808_set_suspend_voltage_range,
	.set_suspend_enable	= rk817_set_suspend_enable,
	.set_suspend_disable	= rk817_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_ops rk817_चयन_ops = अणु
	.enable			= regulator_enable_regmap,
	.disable		= regulator_disable_regmap,
	.is_enabled		= rk8xx_is_enabled_wmsk_regmap,
	.set_suspend_enable	= rk817_set_suspend_enable,
	.set_suspend_disable	= rk817_set_suspend_disable,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rk805_reg[] = अणु
	अणु
		.name = "DCDC_REG1",
		.supply_name = "vcc1",
		.of_match = of_match_ptr("DCDC_REG1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK805_ID_DCDC1,
		.ops = &rk808_reg_ops_ranges,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 64,
		.linear_ranges = rk805_buck_1_2_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk805_buck_1_2_voltage_ranges),
		.vsel_reg = RK805_BUCK1_ON_VSEL_REG,
		.vsel_mask = RK818_BUCK_VSEL_MASK,
		.enable_reg = RK805_DCDC_EN_REG,
		.enable_mask = BIT(0),
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG2",
		.supply_name = "vcc2",
		.of_match = of_match_ptr("DCDC_REG2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK805_ID_DCDC2,
		.ops = &rk808_reg_ops_ranges,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 64,
		.linear_ranges = rk805_buck_1_2_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk805_buck_1_2_voltage_ranges),
		.vsel_reg = RK805_BUCK2_ON_VSEL_REG,
		.vsel_mask = RK818_BUCK_VSEL_MASK,
		.enable_reg = RK805_DCDC_EN_REG,
		.enable_mask = BIT(1),
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG3",
		.supply_name = "vcc3",
		.of_match = of_match_ptr("DCDC_REG3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK805_ID_DCDC3,
		.ops = &rk805_चयन_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 1,
		.enable_reg = RK805_DCDC_EN_REG,
		.enable_mask = BIT(2),
		.owner = THIS_MODULE,
	पूर्ण,

	RK805_DESC(RK805_ID_DCDC4, "DCDC_REG4", "vcc4", 800, 3400, 100,
		RK805_BUCK4_ON_VSEL_REG, RK818_BUCK4_VSEL_MASK,
		RK805_DCDC_EN_REG, BIT(3), 0),

	RK805_DESC(RK805_ID_LDO1, "LDO_REG1", "vcc5", 800, 3400, 100,
		RK805_LDO1_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK805_LDO_EN_REG,
		BIT(0), 400),
	RK805_DESC(RK805_ID_LDO2, "LDO_REG2", "vcc5", 800, 3400, 100,
		RK805_LDO2_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK805_LDO_EN_REG,
		BIT(1), 400),
	RK805_DESC(RK805_ID_LDO3, "LDO_REG3", "vcc6", 800, 3400, 100,
		RK805_LDO3_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK805_LDO_EN_REG,
		BIT(2), 400),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rk808_reg[] = अणु
	अणु
		.name = "DCDC_REG1",
		.supply_name = "vcc1",
		.of_match = of_match_ptr("DCDC_REG1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK808_ID_DCDC1,
		.ops = &rk808_buck1_2_ops,
		.type = REGULATOR_VOLTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_voltages = 64,
		.vsel_reg = RK808_BUCK1_ON_VSEL_REG,
		.vsel_mask = RK808_BUCK_VSEL_MASK,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(0),
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG2",
		.supply_name = "vcc2",
		.of_match = of_match_ptr("DCDC_REG2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK808_ID_DCDC2,
		.ops = &rk808_buck1_2_ops,
		.type = REGULATOR_VOLTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_voltages = 64,
		.vsel_reg = RK808_BUCK2_ON_VSEL_REG,
		.vsel_mask = RK808_BUCK_VSEL_MASK,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(1),
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG3",
		.supply_name = "vcc3",
		.of_match = of_match_ptr("DCDC_REG3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK808_ID_DCDC3,
		.ops = &rk808_चयन_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 1,
		.enable_reg = RK808_DCDC_EN_REG,
		.enable_mask = BIT(2),
		.owner = THIS_MODULE,
	पूर्ण,
	RK8XX_DESC(RK808_ID_DCDC4, "DCDC_REG4", "vcc4", 1800, 3300, 100,
		RK808_BUCK4_ON_VSEL_REG, RK808_BUCK4_VSEL_MASK,
		RK808_DCDC_EN_REG, BIT(3), 0),
	RK8XX_DESC(RK808_ID_LDO1, "LDO_REG1", "vcc6", 1800, 3400, 100,
		RK808_LDO1_ON_VSEL_REG, RK808_LDO_VSEL_MASK, RK808_LDO_EN_REG,
		BIT(0), 400),
	RK8XX_DESC(RK808_ID_LDO2, "LDO_REG2", "vcc6", 1800, 3400, 100,
		RK808_LDO2_ON_VSEL_REG, RK808_LDO_VSEL_MASK, RK808_LDO_EN_REG,
		BIT(1), 400),
	अणु
		.name = "LDO_REG3",
		.supply_name = "vcc7",
		.of_match = of_match_ptr("LDO_REG3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK808_ID_LDO3,
		.ops = &rk808_reg_ops_ranges,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 16,
		.linear_ranges = rk808_lकरो3_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_lकरो3_voltage_ranges),
		.vsel_reg = RK808_LDO3_ON_VSEL_REG,
		.vsel_mask = RK808_BUCK4_VSEL_MASK,
		.enable_reg = RK808_LDO_EN_REG,
		.enable_mask = BIT(2),
		.enable_समय = 400,
		.owner = THIS_MODULE,
	पूर्ण,
	RK8XX_DESC(RK808_ID_LDO4, "LDO_REG4", "vcc9", 1800, 3400, 100,
		RK808_LDO4_ON_VSEL_REG, RK808_LDO_VSEL_MASK, RK808_LDO_EN_REG,
		BIT(3), 400),
	RK8XX_DESC(RK808_ID_LDO5, "LDO_REG5", "vcc9", 1800, 3400, 100,
		RK808_LDO5_ON_VSEL_REG, RK808_LDO_VSEL_MASK, RK808_LDO_EN_REG,
		BIT(4), 400),
	RK8XX_DESC(RK808_ID_LDO6, "LDO_REG6", "vcc10", 800, 2500, 100,
		RK808_LDO6_ON_VSEL_REG, RK808_LDO_VSEL_MASK, RK808_LDO_EN_REG,
		BIT(5), 400),
	RK8XX_DESC(RK808_ID_LDO7, "LDO_REG7", "vcc7", 800, 2500, 100,
		RK808_LDO7_ON_VSEL_REG, RK808_LDO_VSEL_MASK, RK808_LDO_EN_REG,
		BIT(6), 400),
	RK8XX_DESC(RK808_ID_LDO8, "LDO_REG8", "vcc11", 1800, 3400, 100,
		RK808_LDO8_ON_VSEL_REG, RK808_LDO_VSEL_MASK, RK808_LDO_EN_REG,
		BIT(7), 400),
	RK8XX_DESC_SWITCH(RK808_ID_SWITCH1, "SWITCH_REG1", "vcc8",
		RK808_DCDC_EN_REG, BIT(5)),
	RK8XX_DESC_SWITCH(RK808_ID_SWITCH2, "SWITCH_REG2", "vcc12",
		RK808_DCDC_EN_REG, BIT(6)),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rk809_reg[] = अणु
	अणु
		.name = "DCDC_REG1",
		.supply_name = "vcc1",
		.of_match = of_match_ptr("DCDC_REG1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC1,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK1_SEL_CNT + 1,
		.linear_ranges = rk817_buck1_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck1_voltage_ranges),
		.vsel_reg = RK817_BUCK1_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC1),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC1),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC1),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG2",
		.supply_name = "vcc2",
		.of_match = of_match_ptr("DCDC_REG2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC2,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK1_SEL_CNT + 1,
		.linear_ranges = rk817_buck1_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck1_voltage_ranges),
		.vsel_reg = RK817_BUCK2_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC2),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC2),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC2),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG3",
		.supply_name = "vcc3",
		.of_match = of_match_ptr("DCDC_REG3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC3,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK1_SEL_CNT + 1,
		.linear_ranges = rk817_buck1_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck1_voltage_ranges),
		.vsel_reg = RK817_BUCK3_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC3),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC3),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC3),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG4",
		.supply_name = "vcc4",
		.of_match = of_match_ptr("DCDC_REG4"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC4,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK3_SEL_CNT + 1,
		.linear_ranges = rk817_buck3_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck3_voltage_ranges),
		.vsel_reg = RK817_BUCK4_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC4),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC4),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC4),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण,
	अणु
		.name = "DCDC_REG5",
		.supply_name = "vcc9",
		.of_match = of_match_ptr("DCDC_REG5"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK809_ID_DCDC5,
		.ops = &rk809_buck5_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK809_BUCK5_SEL_CNT,
		.linear_ranges = rk809_buck5_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk809_buck5_voltage_ranges),
		.vsel_reg = RK809_BUCK5_CONFIG(0),
		.vsel_mask = RK809_BUCK5_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(3),
		.enable_mask = ENABLE_MASK(1),
		.enable_val = ENABLE_MASK(1),
		.disable_val = DISABLE_VAL(1),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण,
	RK817_DESC(RK817_ID_LDO1, "LDO_REG1", "vcc5", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(0), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(0),
		   DISABLE_VAL(0), 400),
	RK817_DESC(RK817_ID_LDO2, "LDO_REG2", "vcc5", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(1), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(1),
		   DISABLE_VAL(1), 400),
	RK817_DESC(RK817_ID_LDO3, "LDO_REG3", "vcc5", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(2), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(2),
		   DISABLE_VAL(2), 400),
	RK817_DESC(RK817_ID_LDO4, "LDO_REG4", "vcc6", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(3), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(3),
		   DISABLE_VAL(3), 400),
	RK817_DESC(RK817_ID_LDO5, "LDO_REG5", "vcc6", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(4), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(0),
		   DISABLE_VAL(0), 400),
	RK817_DESC(RK817_ID_LDO6, "LDO_REG6", "vcc6", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(5), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(1),
		   DISABLE_VAL(1), 400),
	RK817_DESC(RK817_ID_LDO7, "LDO_REG7", "vcc7", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(6), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(2),
		   DISABLE_VAL(2), 400),
	RK817_DESC(RK817_ID_LDO8, "LDO_REG8", "vcc7", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(7), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(3),
		   DISABLE_VAL(3), 400),
	RK817_DESC(RK817_ID_LDO9, "LDO_REG9", "vcc7", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(8), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(3), ENABLE_MASK(0),
		   DISABLE_VAL(0), 400),
	RK817_DESC_SWITCH(RK809_ID_SW1, "SWITCH_REG1", "vcc9",
			  RK817_POWER_EN_REG(3), ENABLE_MASK(2),
			  DISABLE_VAL(2)),
	RK817_DESC_SWITCH(RK809_ID_SW2, "SWITCH_REG2", "vcc8",
			  RK817_POWER_EN_REG(3), ENABLE_MASK(3),
			  DISABLE_VAL(3)),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rk817_reg[] = अणु
	अणु
		.name = "DCDC_REG1",
		.supply_name = "vcc1",
		.of_match = of_match_ptr("DCDC_REG1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC1,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK1_SEL_CNT + 1,
		.linear_ranges = rk817_buck1_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck1_voltage_ranges),
		.vsel_reg = RK817_BUCK1_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC1),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC1),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC1),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG2",
		.supply_name = "vcc2",
		.of_match = of_match_ptr("DCDC_REG2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC2,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK1_SEL_CNT + 1,
		.linear_ranges = rk817_buck1_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck1_voltage_ranges),
		.vsel_reg = RK817_BUCK2_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC2),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC2),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC2),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG3",
		.supply_name = "vcc3",
		.of_match = of_match_ptr("DCDC_REG3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC3,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK1_SEL_CNT + 1,
		.linear_ranges = rk817_buck1_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck1_voltage_ranges),
		.vsel_reg = RK817_BUCK3_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC3),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC3),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC3),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG4",
		.supply_name = "vcc4",
		.of_match = of_match_ptr("DCDC_REG4"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK817_ID_DCDC4,
		.ops = &rk817_buck_ops_range,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = RK817_BUCK3_SEL_CNT + 1,
		.linear_ranges = rk817_buck3_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk817_buck3_voltage_ranges),
		.vsel_reg = RK817_BUCK4_ON_VSEL_REG,
		.vsel_mask = RK817_BUCK_VSEL_MASK,
		.enable_reg = RK817_POWER_EN_REG(0),
		.enable_mask = ENABLE_MASK(RK817_ID_DCDC4),
		.enable_val = ENABLE_MASK(RK817_ID_DCDC4),
		.disable_val = DISABLE_VAL(RK817_ID_DCDC4),
		.of_map_mode = rk8xx_regulator_of_map_mode,
		.owner = THIS_MODULE,
	पूर्ण,
	RK817_DESC(RK817_ID_LDO1, "LDO_REG1", "vcc5", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(0), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(0),
		   DISABLE_VAL(0), 400),
	RK817_DESC(RK817_ID_LDO2, "LDO_REG2", "vcc5", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(1), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(1),
		   DISABLE_VAL(1), 400),
	RK817_DESC(RK817_ID_LDO3, "LDO_REG3", "vcc5", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(2), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(2),
		   DISABLE_VAL(2), 400),
	RK817_DESC(RK817_ID_LDO4, "LDO_REG4", "vcc6", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(3), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(1), ENABLE_MASK(3),
		   DISABLE_VAL(3), 400),
	RK817_DESC(RK817_ID_LDO5, "LDO_REG5", "vcc6", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(4), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(0),
		   DISABLE_VAL(0), 400),
	RK817_DESC(RK817_ID_LDO6, "LDO_REG6", "vcc6", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(5), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(1),
		   DISABLE_VAL(1), 400),
	RK817_DESC(RK817_ID_LDO7, "LDO_REG7", "vcc7", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(6), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(2),
		   DISABLE_VAL(2), 400),
	RK817_DESC(RK817_ID_LDO8, "LDO_REG8", "vcc7", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(7), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(2), ENABLE_MASK(3),
		   DISABLE_VAL(3), 400),
	RK817_DESC(RK817_ID_LDO9, "LDO_REG9", "vcc7", 600, 3400, 25,
		   RK817_LDO_ON_VSEL_REG(8), RK817_LDO_VSEL_MASK,
		   RK817_POWER_EN_REG(3), ENABLE_MASK(0),
		   DISABLE_VAL(0), 400),
	RK817_BOOST_DESC(RK817_ID_BOOST, "BOOST", "vcc8", 4700, 5400, 100,
			 RK817_BOOST_OTG_CFG, RK817_BOOST_VSEL_MASK,
			 RK817_POWER_EN_REG(3), ENABLE_MASK(1), ENABLE_MASK(1),
		   DISABLE_VAL(1), 400, 3500 - 5400),
	RK817_DESC_SWITCH(RK817_ID_BOOST_OTG_SW, "OTG_SWITCH", "vcc9",
			  RK817_POWER_EN_REG(3), ENABLE_MASK(2),
			  DISABLE_VAL(2)),
पूर्ण;

अटल स्थिर काष्ठा regulator_desc rk818_reg[] = अणु
	अणु
		.name = "DCDC_REG1",
		.supply_name = "vcc1",
		.of_match = of_match_ptr("DCDC_REG1"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK818_ID_DCDC1,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_voltages = 64,
		.vsel_reg = RK818_BUCK1_ON_VSEL_REG,
		.vsel_mask = RK818_BUCK_VSEL_MASK,
		.enable_reg = RK818_DCDC_EN_REG,
		.enable_mask = BIT(0),
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG2",
		.supply_name = "vcc2",
		.of_match = of_match_ptr("DCDC_REG2"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK818_ID_DCDC2,
		.ops = &rk808_reg_ops,
		.type = REGULATOR_VOLTAGE,
		.min_uV = 712500,
		.uV_step = 12500,
		.n_voltages = 64,
		.vsel_reg = RK818_BUCK2_ON_VSEL_REG,
		.vsel_mask = RK818_BUCK_VSEL_MASK,
		.enable_reg = RK818_DCDC_EN_REG,
		.enable_mask = BIT(1),
		.owner = THIS_MODULE,
	पूर्ण, अणु
		.name = "DCDC_REG3",
		.supply_name = "vcc3",
		.of_match = of_match_ptr("DCDC_REG3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK818_ID_DCDC3,
		.ops = &rk808_चयन_ops,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 1,
		.enable_reg = RK818_DCDC_EN_REG,
		.enable_mask = BIT(2),
		.owner = THIS_MODULE,
	पूर्ण,
	RK8XX_DESC(RK818_ID_DCDC4, "DCDC_REG4", "vcc4", 1800, 3600, 100,
		RK818_BUCK4_ON_VSEL_REG, RK818_BUCK4_VSEL_MASK,
		RK818_DCDC_EN_REG, BIT(3), 0),
	RK8XX_DESC(RK818_ID_BOOST, "DCDC_BOOST", "boost", 4700, 5400, 100,
		RK818_BOOST_LDO9_ON_VSEL_REG, RK818_BOOST_ON_VSEL_MASK,
		RK818_DCDC_EN_REG, BIT(4), 0),
	RK8XX_DESC(RK818_ID_LDO1, "LDO_REG1", "vcc6", 1800, 3400, 100,
		RK818_LDO1_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK818_LDO_EN_REG,
		BIT(0), 400),
	RK8XX_DESC(RK818_ID_LDO2, "LDO_REG2", "vcc6", 1800, 3400, 100,
		RK818_LDO2_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK818_LDO_EN_REG,
		BIT(1), 400),
	अणु
		.name = "LDO_REG3",
		.supply_name = "vcc7",
		.of_match = of_match_ptr("LDO_REG3"),
		.regulators_node = of_match_ptr("regulators"),
		.id = RK818_ID_LDO3,
		.ops = &rk808_reg_ops_ranges,
		.type = REGULATOR_VOLTAGE,
		.n_voltages = 16,
		.linear_ranges = rk808_lकरो3_voltage_ranges,
		.n_linear_ranges = ARRAY_SIZE(rk808_lकरो3_voltage_ranges),
		.vsel_reg = RK818_LDO3_ON_VSEL_REG,
		.vsel_mask = RK818_LDO3_ON_VSEL_MASK,
		.enable_reg = RK818_LDO_EN_REG,
		.enable_mask = BIT(2),
		.enable_समय = 400,
		.owner = THIS_MODULE,
	पूर्ण,
	RK8XX_DESC(RK818_ID_LDO4, "LDO_REG4", "vcc8", 1800, 3400, 100,
		RK818_LDO4_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK818_LDO_EN_REG,
		BIT(3), 400),
	RK8XX_DESC(RK818_ID_LDO5, "LDO_REG5", "vcc7", 1800, 3400, 100,
		RK818_LDO5_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK818_LDO_EN_REG,
		BIT(4), 400),
	RK8XX_DESC(RK818_ID_LDO6, "LDO_REG6", "vcc8", 800, 2500, 100,
		RK818_LDO6_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK818_LDO_EN_REG,
		BIT(5), 400),
	RK8XX_DESC(RK818_ID_LDO7, "LDO_REG7", "vcc7", 800, 2500, 100,
		RK818_LDO7_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK818_LDO_EN_REG,
		BIT(6), 400),
	RK8XX_DESC(RK818_ID_LDO8, "LDO_REG8", "vcc8", 1800, 3400, 100,
		RK818_LDO8_ON_VSEL_REG, RK818_LDO_VSEL_MASK, RK818_LDO_EN_REG,
		BIT(7), 400),
	RK8XX_DESC(RK818_ID_LDO9, "LDO_REG9", "vcc9", 1800, 3400, 100,
		RK818_BOOST_LDO9_ON_VSEL_REG, RK818_LDO_VSEL_MASK,
		RK818_DCDC_EN_REG, BIT(5), 400),
	RK8XX_DESC_SWITCH(RK818_ID_SWITCH, "SWITCH_REG", "vcc9",
		RK818_DCDC_EN_REG, BIT(6)),
	RK8XX_DESC_SWITCH(RK818_ID_HDMI_SWITCH, "HDMI_SWITCH", "h_5v",
		RK818_H5V_EN_REG, BIT(0)),
	RK8XX_DESC_SWITCH(RK818_ID_OTG_SWITCH, "OTG_SWITCH", "usb",
		RK818_DCDC_EN_REG, BIT(7)),
पूर्ण;

अटल पूर्णांक rk808_regulator_dt_parse_pdata(काष्ठा device *dev,
				   काष्ठा device *client_dev,
				   काष्ठा regmap *map,
				   काष्ठा rk808_regulator_data *pdata)
अणु
	काष्ठा device_node *np;
	पूर्णांक पंचांगp, ret = 0, i;

	np = of_get_child_by_name(client_dev->of_node, "regulators");
	अगर (!np)
		वापस -ENXIO;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->dvs_gpio); i++) अणु
		pdata->dvs_gpio[i] =
			devm_gpiod_get_index_optional(client_dev, "dvs", i,
						      GPIOD_OUT_LOW);
		अगर (IS_ERR(pdata->dvs_gpio[i])) अणु
			ret = PTR_ERR(pdata->dvs_gpio[i]);
			dev_err(dev, "failed to get dvs%d gpio (%d)\n", i, ret);
			जाओ dt_parse_end;
		पूर्ण

		अगर (!pdata->dvs_gpio[i]) अणु
			dev_info(dev, "there is no dvs%d gpio\n", i);
			जारी;
		पूर्ण

		पंचांगp = i ? RK808_DVS2_POL : RK808_DVS1_POL;
		ret = regmap_update_bits(map, RK808_IO_POL_REG, पंचांगp,
				gpiod_is_active_low(pdata->dvs_gpio[i]) ?
				0 : पंचांगp);
	पूर्ण

dt_parse_end:
	of_node_put(np);
	वापस ret;
पूर्ण

अटल पूर्णांक rk808_regulator_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा i2c_client *client = rk808->i2c;
	काष्ठा regulator_config config = अणुपूर्ण;
	काष्ठा regulator_dev *rk808_rdev;
	काष्ठा rk808_regulator_data *pdata;
	स्थिर काष्ठा regulator_desc *regulators;
	पूर्णांक ret, i, nregulators;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	ret = rk808_regulator_dt_parse_pdata(&pdev->dev, &client->dev,
					     rk808->regmap, pdata);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, pdata);

	चयन (rk808->variant) अणु
	हाल RK805_ID:
		regulators = rk805_reg;
		nregulators = RK805_NUM_REGULATORS;
		अवरोध;
	हाल RK808_ID:
		regulators = rk808_reg;
		nregulators = RK808_NUM_REGULATORS;
		अवरोध;
	हाल RK809_ID:
		regulators = rk809_reg;
		nregulators = RK809_NUM_REGULATORS;
		अवरोध;
	हाल RK817_ID:
		regulators = rk817_reg;
		nregulators = RK817_NUM_REGULATORS;
		अवरोध;
	हाल RK818_ID:
		regulators = rk818_reg;
		nregulators = RK818_NUM_REGULATORS;
		अवरोध;
	शेष:
		dev_err(&client->dev, "unsupported RK8XX ID %lu\n",
			rk808->variant);
		वापस -EINVAL;
	पूर्ण

	config.dev = &client->dev;
	config.driver_data = pdata;
	config.regmap = rk808->regmap;

	/* Instantiate the regulators */
	क्रम (i = 0; i < nregulators; i++) अणु
		rk808_rdev = devm_regulator_रेजिस्टर(&pdev->dev,
						     &regulators[i], &config);
		अगर (IS_ERR(rk808_rdev)) अणु
			dev_err(&client->dev,
				"failed to register %d regulator\n", i);
			वापस PTR_ERR(rk808_rdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rk808_regulator_driver = अणु
	.probe = rk808_regulator_probe,
	.driver = अणु
		.name = "rk808-regulator"
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rk808_regulator_driver);

MODULE_DESCRIPTION("regulator driver for the RK805/RK808/RK818 series PMICs");
MODULE_AUTHOR("Tony xie <tony.xie@rock-chips.com>");
MODULE_AUTHOR("Chris Zhong <zyw@rock-chips.com>");
MODULE_AUTHOR("Zhang Qing <zhangqing@rock-chips.com>");
MODULE_AUTHOR("Wadim Egorov <w.egorov@phytec.de>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rk808-regulator");
