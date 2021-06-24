<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Intel Corporation. All rights reserved.
 *
 * Author: Shobhit Kumar <shobhit.kumar@पूर्णांकel.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>
#समावेश <linux/pwm.h>

#घोषणा PWM0_CLK_DIV		0x4B
#घोषणा  PWM_OUTPUT_ENABLE	BIT(7)
#घोषणा  PWM_DIV_CLK_0		0x00 /* DIVIDECLK = BASECLK */
#घोषणा  PWM_DIV_CLK_100	0x63 /* DIVIDECLK = BASECLK/100 */
#घोषणा  PWM_DIV_CLK_128	0x7F /* DIVIDECLK = BASECLK/128 */

#घोषणा PWM0_DUTY_CYCLE		0x4E
#घोषणा BACKLIGHT_EN		0x51

#घोषणा PWM_MAX_LEVEL		0xFF

#घोषणा PWM_BASE_CLK_MHZ	6	/* 6 MHz */
#घोषणा PWM_MAX_PERIOD_NS	5461334	/* 183 Hz */

/**
 * काष्ठा crystalcove_pwm - Crystal Cove PWM controller
 * @chip: the असलtract pwm_chip काष्ठाure.
 * @regmap: the regmap from the parent device.
 */
काष्ठा crystalcove_pwm अणु
	काष्ठा pwm_chip chip;
	काष्ठा regmap *regmap;
पूर्ण;

अटल अंतरभूत काष्ठा crystalcove_pwm *to_crc_pwm(काष्ठा pwm_chip *pc)
अणु
	वापस container_of(pc, काष्ठा crystalcove_pwm, chip);
पूर्ण

अटल पूर्णांक crc_pwm_calc_clk_भाग(पूर्णांक period_ns)
अणु
	पूर्णांक clk_भाग;

	clk_भाग = PWM_BASE_CLK_MHZ * period_ns / (256 * NSEC_PER_USEC);
	/* clk_भाग 1 - 128, maps to रेजिस्टर values 0-127 */
	अगर (clk_भाग > 0)
		clk_भाग--;

	वापस clk_भाग;
पूर्ण

अटल पूर्णांक crc_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			 स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा crystalcove_pwm *crc_pwm = to_crc_pwm(chip);
	काष्ठा device *dev = crc_pwm->chip.dev;
	पूर्णांक err;

	अगर (state->period > PWM_MAX_PERIOD_NS) अणु
		dev_err(dev, "un-supported period_ns\n");
		वापस -EINVAL;
	पूर्ण

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	अगर (pwm_is_enabled(pwm) && !state->enabled) अणु
		err = regmap_ग_लिखो(crc_pwm->regmap, BACKLIGHT_EN, 0);
		अगर (err) अणु
			dev_err(dev, "Error writing BACKLIGHT_EN %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (pwm_get_duty_cycle(pwm) != state->duty_cycle ||
	    pwm_get_period(pwm) != state->period) अणु
		u64 level = state->duty_cycle * PWM_MAX_LEVEL;

		करो_भाग(level, state->period);

		err = regmap_ग_लिखो(crc_pwm->regmap, PWM0_DUTY_CYCLE, level);
		अगर (err) अणु
			dev_err(dev, "Error writing PWM0_DUTY_CYCLE %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (pwm_is_enabled(pwm) && state->enabled &&
	    pwm_get_period(pwm) != state->period) अणु
		/* changing the clk भागisor, clear PWM_OUTPUT_ENABLE first */
		err = regmap_ग_लिखो(crc_pwm->regmap, PWM0_CLK_DIV, 0);
		अगर (err) अणु
			dev_err(dev, "Error writing PWM0_CLK_DIV %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (pwm_get_period(pwm) != state->period ||
	    pwm_is_enabled(pwm) != state->enabled) अणु
		पूर्णांक clk_भाग = crc_pwm_calc_clk_भाग(state->period);
		पूर्णांक pwm_output_enable = state->enabled ? PWM_OUTPUT_ENABLE : 0;

		err = regmap_ग_लिखो(crc_pwm->regmap, PWM0_CLK_DIV,
				   clk_भाग | pwm_output_enable);
		अगर (err) अणु
			dev_err(dev, "Error writing PWM0_CLK_DIV %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (!pwm_is_enabled(pwm) && state->enabled) अणु
		err = regmap_ग_लिखो(crc_pwm->regmap, BACKLIGHT_EN, 1);
		अगर (err) अणु
			dev_err(dev, "Error writing BACKLIGHT_EN %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम crc_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      काष्ठा pwm_state *state)
अणु
	काष्ठा crystalcove_pwm *crc_pwm = to_crc_pwm(chip);
	काष्ठा device *dev = crc_pwm->chip.dev;
	अचिन्हित पूर्णांक clk_भाग, clk_भाग_reg, duty_cycle_reg;
	पूर्णांक error;

	error = regmap_पढ़ो(crc_pwm->regmap, PWM0_CLK_DIV, &clk_भाग_reg);
	अगर (error) अणु
		dev_err(dev, "Error reading PWM0_CLK_DIV %d\n", error);
		वापस;
	पूर्ण

	error = regmap_पढ़ो(crc_pwm->regmap, PWM0_DUTY_CYCLE, &duty_cycle_reg);
	अगर (error) अणु
		dev_err(dev, "Error reading PWM0_DUTY_CYCLE %d\n", error);
		वापस;
	पूर्ण

	clk_भाग = (clk_भाग_reg & ~PWM_OUTPUT_ENABLE) + 1;

	state->period =
		DIV_ROUND_UP(clk_भाग * NSEC_PER_USEC * 256, PWM_BASE_CLK_MHZ);
	state->duty_cycle =
		DIV_ROUND_UP_ULL(duty_cycle_reg * state->period, PWM_MAX_LEVEL);
	state->polarity = PWM_POLARITY_NORMAL;
	state->enabled = !!(clk_भाग_reg & PWM_OUTPUT_ENABLE);
पूर्ण

अटल स्थिर काष्ठा pwm_ops crc_pwm_ops = अणु
	.apply = crc_pwm_apply,
	.get_state = crc_pwm_get_state,
पूर्ण;

अटल पूर्णांक crystalcove_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा crystalcove_pwm *pwm;
	काष्ठा device *dev = pdev->dev.parent;
	काष्ठा पूर्णांकel_soc_pmic *pmic = dev_get_drvdata(dev);

	pwm = devm_kzalloc(&pdev->dev, माप(*pwm), GFP_KERNEL);
	अगर (!pwm)
		वापस -ENOMEM;

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &crc_pwm_ops;
	pwm->chip.npwm = 1;

	/* get the PMIC regmap */
	pwm->regmap = pmic->regmap;

	platक्रमm_set_drvdata(pdev, pwm);

	वापस pwmchip_add(&pwm->chip);
पूर्ण

अटल पूर्णांक crystalcove_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा crystalcove_pwm *pwm = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&pwm->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver crystalcove_pwm_driver = अणु
	.probe = crystalcove_pwm_probe,
	.हटाओ = crystalcove_pwm_हटाओ,
	.driver = अणु
		.name = "crystal_cove_pwm",
	पूर्ण,
पूर्ण;

builtin_platक्रमm_driver(crystalcove_pwm_driver);
