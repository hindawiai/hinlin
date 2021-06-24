<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Intel Corporation.
 *
 * Limitations:
 * - The hardware supports fixed period & configures only 2-wire mode.
 * - Supports normal polarity. Does not support changing polarity.
 * - When PWM is disabled, output of PWM will become 0(inactive). It करोesn't
 *   keep track of running period.
 * - When duty cycle is changed, PWM output may be a mix of previous setting
 *   and new setting क्रम the first period. From second period, the output is
 *   based on new setting.
 * - It is a dedicated PWM fan controller. There are no other consumers क्रम
 *   this PWM controller.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#घोषणा LGM_PWM_FAN_CON0		0x0
#घोषणा LGM_PWM_FAN_EN_EN		BIT(0)
#घोषणा LGM_PWM_FAN_EN_DIS		0x0
#घोषणा LGM_PWM_FAN_EN_MSK		BIT(0)
#घोषणा LGM_PWM_FAN_MODE_2WIRE		0x0
#घोषणा LGM_PWM_FAN_MODE_MSK		BIT(1)
#घोषणा LGM_PWM_FAN_DC_MSK		GENMASK(23, 16)

#घोषणा LGM_PWM_FAN_CON1		0x4
#घोषणा LGM_PWM_FAN_MAX_RPM_MSK		GENMASK(15, 0)

#घोषणा LGM_PWM_MAX_RPM			(BIT(16) - 1)
#घोषणा LGM_PWM_DEFAULT_RPM		4000
#घोषणा LGM_PWM_MAX_DUTY_CYCLE		(BIT(8) - 1)

#घोषणा LGM_PWM_DC_BITS			8

#घोषणा LGM_PWM_PERIOD_2WIRE_NS		(40 * NSEC_PER_MSEC)

काष्ठा lgm_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा regmap *regmap;
	u32 period;
पूर्ण;

अटल अंतरभूत काष्ठा lgm_pwm_chip *to_lgm_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा lgm_pwm_chip, chip);
पूर्ण

अटल पूर्णांक lgm_pwm_enable(काष्ठा pwm_chip *chip, bool enable)
अणु
	काष्ठा lgm_pwm_chip *pc = to_lgm_pwm_chip(chip);
	काष्ठा regmap *regmap = pc->regmap;

	वापस regmap_update_bits(regmap, LGM_PWM_FAN_CON0, LGM_PWM_FAN_EN_MSK,
				  enable ? LGM_PWM_FAN_EN_EN : LGM_PWM_FAN_EN_DIS);
पूर्ण

अटल पूर्णांक lgm_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			 स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा lgm_pwm_chip *pc = to_lgm_pwm_chip(chip);
	u32 duty_cycle, val;
	पूर्णांक ret;

	/* The hardware only supports normal polarity and fixed period. */
	अगर (state->polarity != PWM_POLARITY_NORMAL || state->period < pc->period)
		वापस -EINVAL;

	अगर (!state->enabled)
		वापस lgm_pwm_enable(chip, 0);

	duty_cycle = min_t(u64, state->duty_cycle, pc->period);
	val = duty_cycle * LGM_PWM_MAX_DUTY_CYCLE / pc->period;

	ret = regmap_update_bits(pc->regmap, LGM_PWM_FAN_CON0, LGM_PWM_FAN_DC_MSK,
				 FIELD_PREP(LGM_PWM_FAN_DC_MSK, val));
	अगर (ret)
		वापस ret;

	वापस lgm_pwm_enable(chip, 1);
पूर्ण

अटल व्योम lgm_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      काष्ठा pwm_state *state)
अणु
	काष्ठा lgm_pwm_chip *pc = to_lgm_pwm_chip(chip);
	u32 duty, val;

	state->enabled = regmap_test_bits(pc->regmap, LGM_PWM_FAN_CON0,
					  LGM_PWM_FAN_EN_EN);
	state->polarity = PWM_POLARITY_NORMAL;
	state->period = pc->period; /* fixed period */

	regmap_पढ़ो(pc->regmap, LGM_PWM_FAN_CON0, &val);
	duty = FIELD_GET(LGM_PWM_FAN_DC_MSK, val);
	state->duty_cycle = DIV_ROUND_UP(duty * pc->period, LGM_PWM_MAX_DUTY_CYCLE);
पूर्ण

अटल स्थिर काष्ठा pwm_ops lgm_pwm_ops = अणु
	.get_state = lgm_pwm_get_state,
	.apply = lgm_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल व्योम lgm_pwm_init(काष्ठा lgm_pwm_chip *pc)
अणु
	काष्ठा regmap *regmap = pc->regmap;
	u32 con0_val;

	con0_val = FIELD_PREP(LGM_PWM_FAN_MODE_MSK, LGM_PWM_FAN_MODE_2WIRE);
	pc->period = LGM_PWM_PERIOD_2WIRE_NS;
	regmap_update_bits(regmap, LGM_PWM_FAN_CON1, LGM_PWM_FAN_MAX_RPM_MSK,
			   LGM_PWM_DEFAULT_RPM);
	regmap_update_bits(regmap, LGM_PWM_FAN_CON0, LGM_PWM_FAN_MODE_MSK,
			   con0_val);
पूर्ण

अटल स्थिर काष्ठा regmap_config lgm_pwm_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
पूर्ण;

अटल व्योम lgm_clk_release(व्योम *data)
अणु
	काष्ठा clk *clk = data;

	clk_disable_unprepare(clk);
पूर्ण

अटल पूर्णांक lgm_clk_enable(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, lgm_clk_release, clk);
पूर्ण

अटल व्योम lgm_reset_control_release(व्योम *data)
अणु
	काष्ठा reset_control *rst = data;

	reset_control_निश्चित(rst);
पूर्ण

अटल पूर्णांक lgm_reset_control_deनिश्चित(काष्ठा device *dev, काष्ठा reset_control *rst)
अणु
	पूर्णांक ret;

	ret = reset_control_deनिश्चित(rst);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, lgm_reset_control_release, rst);
पूर्ण

अटल पूर्णांक lgm_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा reset_control *rst;
	काष्ठा lgm_pwm_chip *pc;
	व्योम __iomem *io_base;
	काष्ठा clk *clk;
	पूर्णांक ret;

	pc = devm_kzalloc(dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, pc);

	io_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	pc->regmap = devm_regmap_init_mmio(dev, io_base, &lgm_pwm_regmap_config);
	अगर (IS_ERR(pc->regmap))
		वापस dev_err_probe(dev, PTR_ERR(pc->regmap),
				     "failed to init register map\n");

	clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(dev, PTR_ERR(clk), "failed to get clock\n");

	ret = lgm_clk_enable(dev, clk);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to enable clock\n");

	rst = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(rst))
		वापस dev_err_probe(dev, PTR_ERR(rst),
				     "failed to get reset control\n");

	ret = lgm_reset_control_deनिश्चित(dev, rst);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "cannot deassert reset control\n");

	pc->chip.dev = dev;
	pc->chip.ops = &lgm_pwm_ops;
	pc->chip.npwm = 1;

	lgm_pwm_init(pc);

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0)
		वापस dev_err_probe(dev, ret, "failed to add PWM chip\n");

	वापस 0;
पूर्ण

अटल पूर्णांक lgm_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lgm_pwm_chip *pc = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&pc->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id lgm_pwm_of_match[] = अणु
	अणु .compatible = "intel,lgm-pwm" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lgm_pwm_of_match);

अटल काष्ठा platक्रमm_driver lgm_pwm_driver = अणु
	.driver = अणु
		.name = "intel-pwm",
		.of_match_table = lgm_pwm_of_match,
	पूर्ण,
	.probe = lgm_pwm_probe,
	.हटाओ = lgm_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(lgm_pwm_driver);

MODULE_LICENSE("GPL v2");
