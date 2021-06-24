<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PWM driver क्रम Rockchip SoCs
 *
 * Copyright (C) 2014 Beniamino Galvani <b.galvani@gmail.com>
 * Copyright (C) 2014 ROCKCHIP, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/समय.स>

#घोषणा PWM_CTRL_TIMER_EN	(1 << 0)
#घोषणा PWM_CTRL_OUTPUT_EN	(1 << 3)

#घोषणा PWM_ENABLE		(1 << 0)
#घोषणा PWM_CONTINUOUS		(1 << 1)
#घोषणा PWM_DUTY_POSITIVE	(1 << 3)
#घोषणा PWM_DUTY_NEGATIVE	(0 << 3)
#घोषणा PWM_INACTIVE_NEGATIVE	(0 << 4)
#घोषणा PWM_INACTIVE_POSITIVE	(1 << 4)
#घोषणा PWM_POLARITY_MASK	(PWM_DUTY_POSITIVE | PWM_INACTIVE_POSITIVE)
#घोषणा PWM_OUTPUT_LEFT		(0 << 5)
#घोषणा PWM_LOCK_EN		(1 << 6)
#घोषणा PWM_LP_DISABLE		(0 << 8)

काष्ठा rockchip_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *clk;
	काष्ठा clk *pclk;
	स्थिर काष्ठा rockchip_pwm_data *data;
	व्योम __iomem *base;
पूर्ण;

काष्ठा rockchip_pwm_regs अणु
	अचिन्हित दीर्घ duty;
	अचिन्हित दीर्घ period;
	अचिन्हित दीर्घ cntr;
	अचिन्हित दीर्घ ctrl;
पूर्ण;

काष्ठा rockchip_pwm_data अणु
	काष्ठा rockchip_pwm_regs regs;
	अचिन्हित पूर्णांक prescaler;
	bool supports_polarity;
	bool supports_lock;
	u32 enable_conf;
पूर्ण;

अटल अंतरभूत काष्ठा rockchip_pwm_chip *to_rockchip_pwm_chip(काष्ठा pwm_chip *c)
अणु
	वापस container_of(c, काष्ठा rockchip_pwm_chip, chip);
पूर्ण

अटल व्योम rockchip_pwm_get_state(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm,
				   काष्ठा pwm_state *state)
अणु
	काष्ठा rockchip_pwm_chip *pc = to_rockchip_pwm_chip(chip);
	u32 enable_conf = pc->data->enable_conf;
	अचिन्हित दीर्घ clk_rate;
	u64 पंचांगp;
	u32 val;
	पूर्णांक ret;

	ret = clk_enable(pc->pclk);
	अगर (ret)
		वापस;

	ret = clk_enable(pc->clk);
	अगर (ret)
		वापस;

	clk_rate = clk_get_rate(pc->clk);

	पंचांगp = पढ़ोl_relaxed(pc->base + pc->data->regs.period);
	पंचांगp *= pc->data->prescaler * NSEC_PER_SEC;
	state->period = DIV_ROUND_CLOSEST_ULL(पंचांगp, clk_rate);

	पंचांगp = पढ़ोl_relaxed(pc->base + pc->data->regs.duty);
	पंचांगp *= pc->data->prescaler * NSEC_PER_SEC;
	state->duty_cycle =  DIV_ROUND_CLOSEST_ULL(पंचांगp, clk_rate);

	val = पढ़ोl_relaxed(pc->base + pc->data->regs.ctrl);
	state->enabled = (val & enable_conf) == enable_conf;

	अगर (pc->data->supports_polarity && !(val & PWM_DUTY_POSITIVE))
		state->polarity = PWM_POLARITY_INVERSED;
	अन्यथा
		state->polarity = PWM_POLARITY_NORMAL;

	clk_disable(pc->clk);
	clk_disable(pc->pclk);
पूर्ण

अटल व्योम rockchip_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा rockchip_pwm_chip *pc = to_rockchip_pwm_chip(chip);
	अचिन्हित दीर्घ period, duty;
	u64 clk_rate, भाग;
	u32 ctrl;

	clk_rate = clk_get_rate(pc->clk);

	/*
	 * Since period and duty cycle रेजिस्टरs have a width of 32
	 * bits, every possible input period can be obtained using the
	 * शेष prescaler value क्रम all practical घड़ी rate values.
	 */
	भाग = clk_rate * state->period;
	period = DIV_ROUND_CLOSEST_ULL(भाग,
				       pc->data->prescaler * NSEC_PER_SEC);

	भाग = clk_rate * state->duty_cycle;
	duty = DIV_ROUND_CLOSEST_ULL(भाग, pc->data->prescaler * NSEC_PER_SEC);

	/*
	 * Lock the period and duty of previous configuration, then
	 * change the duty and period, that would not be effective.
	 */
	ctrl = पढ़ोl_relaxed(pc->base + pc->data->regs.ctrl);
	अगर (pc->data->supports_lock) अणु
		ctrl |= PWM_LOCK_EN;
		ग_लिखोl_relaxed(ctrl, pc->base + pc->data->regs.ctrl);
	पूर्ण

	ग_लिखोl(period, pc->base + pc->data->regs.period);
	ग_लिखोl(duty, pc->base + pc->data->regs.duty);

	अगर (pc->data->supports_polarity) अणु
		ctrl &= ~PWM_POLARITY_MASK;
		अगर (state->polarity == PWM_POLARITY_INVERSED)
			ctrl |= PWM_DUTY_NEGATIVE | PWM_INACTIVE_POSITIVE;
		अन्यथा
			ctrl |= PWM_DUTY_POSITIVE | PWM_INACTIVE_NEGATIVE;
	पूर्ण

	/*
	 * Unlock and set polarity at the same समय,
	 * the configuration of duty, period and polarity
	 * would be effective together at next period.
	 */
	अगर (pc->data->supports_lock)
		ctrl &= ~PWM_LOCK_EN;

	ग_लिखोl(ctrl, pc->base + pc->data->regs.ctrl);
पूर्ण

अटल पूर्णांक rockchip_pwm_enable(काष्ठा pwm_chip *chip,
			       काष्ठा pwm_device *pwm,
			       bool enable)
अणु
	काष्ठा rockchip_pwm_chip *pc = to_rockchip_pwm_chip(chip);
	u32 enable_conf = pc->data->enable_conf;
	पूर्णांक ret;
	u32 val;

	अगर (enable) अणु
		ret = clk_enable(pc->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	val = पढ़ोl_relaxed(pc->base + pc->data->regs.ctrl);

	अगर (enable)
		val |= enable_conf;
	अन्यथा
		val &= ~enable_conf;

	ग_लिखोl_relaxed(val, pc->base + pc->data->regs.ctrl);

	अगर (!enable)
		clk_disable(pc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा rockchip_pwm_chip *pc = to_rockchip_pwm_chip(chip);
	काष्ठा pwm_state curstate;
	bool enabled;
	पूर्णांक ret = 0;

	ret = clk_enable(pc->pclk);
	अगर (ret)
		वापस ret;

	ret = clk_enable(pc->clk);
	अगर (ret)
		वापस ret;

	pwm_get_state(pwm, &curstate);
	enabled = curstate.enabled;

	अगर (state->polarity != curstate.polarity && enabled &&
	    !pc->data->supports_lock) अणु
		ret = rockchip_pwm_enable(chip, pwm, false);
		अगर (ret)
			जाओ out;
		enabled = false;
	पूर्ण

	rockchip_pwm_config(chip, pwm, state);
	अगर (state->enabled != enabled) अणु
		ret = rockchip_pwm_enable(chip, pwm, state->enabled);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	clk_disable(pc->clk);
	clk_disable(pc->pclk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops rockchip_pwm_ops = अणु
	.get_state = rockchip_pwm_get_state,
	.apply = rockchip_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pwm_data pwm_data_v1 = अणु
	.regs = अणु
		.duty = 0x04,
		.period = 0x08,
		.cntr = 0x00,
		.ctrl = 0x0c,
	पूर्ण,
	.prescaler = 2,
	.supports_polarity = false,
	.supports_lock = false,
	.enable_conf = PWM_CTRL_OUTPUT_EN | PWM_CTRL_TIMER_EN,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pwm_data pwm_data_v2 = अणु
	.regs = अणु
		.duty = 0x08,
		.period = 0x04,
		.cntr = 0x00,
		.ctrl = 0x0c,
	पूर्ण,
	.prescaler = 1,
	.supports_polarity = true,
	.supports_lock = false,
	.enable_conf = PWM_OUTPUT_LEFT | PWM_LP_DISABLE | PWM_ENABLE |
		       PWM_CONTINUOUS,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pwm_data pwm_data_vop = अणु
	.regs = अणु
		.duty = 0x08,
		.period = 0x04,
		.cntr = 0x0c,
		.ctrl = 0x00,
	पूर्ण,
	.prescaler = 1,
	.supports_polarity = true,
	.supports_lock = false,
	.enable_conf = PWM_OUTPUT_LEFT | PWM_LP_DISABLE | PWM_ENABLE |
		       PWM_CONTINUOUS,
पूर्ण;

अटल स्थिर काष्ठा rockchip_pwm_data pwm_data_v3 = अणु
	.regs = अणु
		.duty = 0x08,
		.period = 0x04,
		.cntr = 0x00,
		.ctrl = 0x0c,
	पूर्ण,
	.prescaler = 1,
	.supports_polarity = true,
	.supports_lock = true,
	.enable_conf = PWM_OUTPUT_LEFT | PWM_LP_DISABLE | PWM_ENABLE |
		       PWM_CONTINUOUS,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rockchip_pwm_dt_ids[] = अणु
	अणु .compatible = "rockchip,rk2928-pwm", .data = &pwm_data_v1पूर्ण,
	अणु .compatible = "rockchip,rk3288-pwm", .data = &pwm_data_v2पूर्ण,
	अणु .compatible = "rockchip,vop-pwm", .data = &pwm_data_vopपूर्ण,
	अणु .compatible = "rockchip,rk3328-pwm", .data = &pwm_data_v3पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rockchip_pwm_dt_ids);

अटल पूर्णांक rockchip_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *id;
	काष्ठा rockchip_pwm_chip *pc;
	u32 enable_conf, ctrl;
	bool enabled;
	पूर्णांक ret, count;

	id = of_match_device(rockchip_pwm_dt_ids, &pdev->dev);
	अगर (!id)
		वापस -EINVAL;

	pc = devm_kzalloc(&pdev->dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	pc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pc->base))
		वापस PTR_ERR(pc->base);

	pc->clk = devm_clk_get(&pdev->dev, "pwm");
	अगर (IS_ERR(pc->clk)) अणु
		pc->clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(pc->clk))
			वापस dev_err_probe(&pdev->dev, PTR_ERR(pc->clk),
					     "Can't get PWM clk\n");
	पूर्ण

	count = of_count_phandle_with_args(pdev->dev.of_node,
					   "clocks", "#clock-cells");
	अगर (count == 2)
		pc->pclk = devm_clk_get(&pdev->dev, "pclk");
	अन्यथा
		pc->pclk = pc->clk;

	अगर (IS_ERR(pc->pclk)) अणु
		ret = PTR_ERR(pc->pclk);
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "Can't get APB clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(pc->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't prepare enable PWM clk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(pc->pclk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Can't prepare enable APB clk: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pc);

	pc->data = id->data;
	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &rockchip_pwm_ops;
	pc->chip.npwm = 1;

	अगर (pc->data->supports_polarity) अणु
		pc->chip.of_xlate = of_pwm_xlate_with_flags;
		pc->chip.of_pwm_n_cells = 3;
	पूर्ण

	enable_conf = pc->data->enable_conf;
	ctrl = पढ़ोl_relaxed(pc->base + pc->data->regs.ctrl);
	enabled = (ctrl & enable_conf) == enable_conf;

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		जाओ err_pclk;
	पूर्ण

	/* Keep the PWM clk enabled अगर the PWM appears to be up and running. */
	अगर (!enabled)
		clk_disable(pc->clk);

	clk_disable(pc->pclk);

	वापस 0;

err_pclk:
	clk_disable_unprepare(pc->pclk);
err_clk:
	clk_disable_unprepare(pc->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rockchip_pwm_chip *pc = platक्रमm_get_drvdata(pdev);

	/*
	 * Disable the PWM clk beक्रमe unpreparing it अगर the PWM device is still
	 * running. This should only happen when the last PWM user left it
	 * enabled, or when nobody requested a PWM that was previously enabled
	 * by the bootloader.
	 *
	 * FIXME: Maybe the core should disable all PWM devices in
	 * pwmchip_हटाओ(). In this हाल we'd only have to call
	 * clk_unprepare() after pwmchip_हटाओ().
	 *
	 */
	अगर (pwm_is_enabled(pc->chip.pwms))
		clk_disable(pc->clk);

	clk_unprepare(pc->pclk);
	clk_unprepare(pc->clk);

	वापस pwmchip_हटाओ(&pc->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver rockchip_pwm_driver = अणु
	.driver = अणु
		.name = "rockchip-pwm",
		.of_match_table = rockchip_pwm_dt_ids,
	पूर्ण,
	.probe = rockchip_pwm_probe,
	.हटाओ = rockchip_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(rockchip_pwm_driver);

MODULE_AUTHOR("Beniamino Galvani <b.galvani@gmail.com>");
MODULE_DESCRIPTION("Rockchip SoC PWM driver");
MODULE_LICENSE("GPL v2");
