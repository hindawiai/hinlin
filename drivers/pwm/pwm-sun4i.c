<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Allwinner sun4i Pulse Width Modulation Controller
 *
 * Copyright (C) 2014 Alexandre Belloni <alexandre.belloni@मुक्त-electrons.com>
 *
 * Limitations:
 * - When outputing the source घड़ी directly, the PWM logic will be bypassed
 *   and the currently running period is not guaranteed to be completed
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समय.स>

#घोषणा PWM_CTRL_REG		0x0

#घोषणा PWM_CH_PRD_BASE		0x4
#घोषणा PWM_CH_PRD_OFFSET	0x4
#घोषणा PWM_CH_PRD(ch)		(PWM_CH_PRD_BASE + PWM_CH_PRD_OFFSET * (ch))

#घोषणा PWMCH_OFFSET		15
#घोषणा PWM_PRESCAL_MASK	GENMASK(3, 0)
#घोषणा PWM_PRESCAL_OFF		0
#घोषणा PWM_EN			BIT(4)
#घोषणा PWM_ACT_STATE		BIT(5)
#घोषणा PWM_CLK_GATING		BIT(6)
#घोषणा PWM_MODE		BIT(7)
#घोषणा PWM_PULSE		BIT(8)
#घोषणा PWM_BYPASS		BIT(9)

#घोषणा PWM_RDY_BASE		28
#घोषणा PWM_RDY_OFFSET		1
#घोषणा PWM_RDY(ch)		BIT(PWM_RDY_BASE + PWM_RDY_OFFSET * (ch))

#घोषणा PWM_PRD(prd)		(((prd) - 1) << 16)
#घोषणा PWM_PRD_MASK		GENMASK(15, 0)

#घोषणा PWM_DTY_MASK		GENMASK(15, 0)

#घोषणा PWM_REG_PRD(reg)	((((reg) >> 16) & PWM_PRD_MASK) + 1)
#घोषणा PWM_REG_DTY(reg)	((reg) & PWM_DTY_MASK)
#घोषणा PWM_REG_PRESCAL(reg, chan)	(((reg) >> ((chan) * PWMCH_OFFSET)) & PWM_PRESCAL_MASK)

#घोषणा BIT_CH(bit, chan)	((bit) << ((chan) * PWMCH_OFFSET))

अटल स्थिर u32 prescaler_table[] = अणु
	120,
	180,
	240,
	360,
	480,
	0,
	0,
	0,
	12000,
	24000,
	36000,
	48000,
	72000,
	0,
	0,
	0, /* Actually 1 but tested separately */
पूर्ण;

काष्ठा sun4i_pwm_data अणु
	bool has_prescaler_bypass;
	bool has_direct_mod_clk_output;
	अचिन्हित पूर्णांक npwm;
पूर्ण;

काष्ठा sun4i_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *bus_clk;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	व्योम __iomem *base;
	spinlock_t ctrl_lock;
	स्थिर काष्ठा sun4i_pwm_data *data;
	अचिन्हित दीर्घ next_period[2];
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_pwm_chip *to_sun4i_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा sun4i_pwm_chip, chip);
पूर्ण

अटल अंतरभूत u32 sun4i_pwm_पढ़ोl(काष्ठा sun4i_pwm_chip *chip,
				  अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl(chip->base + offset);
पूर्ण

अटल अंतरभूत व्योम sun4i_pwm_ग_लिखोl(काष्ठा sun4i_pwm_chip *chip,
				    u32 val, अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl(val, chip->base + offset);
पूर्ण

अटल व्योम sun4i_pwm_get_state(काष्ठा pwm_chip *chip,
				काष्ठा pwm_device *pwm,
				काष्ठा pwm_state *state)
अणु
	काष्ठा sun4i_pwm_chip *sun4i_pwm = to_sun4i_pwm_chip(chip);
	u64 clk_rate, पंचांगp;
	u32 val;
	अचिन्हित पूर्णांक prescaler;

	clk_rate = clk_get_rate(sun4i_pwm->clk);

	val = sun4i_pwm_पढ़ोl(sun4i_pwm, PWM_CTRL_REG);

	/*
	 * PWM chapter in H6 manual has a diagram which explains that अगर bypass
	 * bit is set, no other setting has any meaning. Even more, experiment
	 * proved that also enable bit is ignored in this हाल.
	 */
	अगर ((val & BIT_CH(PWM_BYPASS, pwm->hwpwm)) &&
	    sun4i_pwm->data->has_direct_mod_clk_output) अणु
		state->period = DIV_ROUND_UP_ULL(NSEC_PER_SEC, clk_rate);
		state->duty_cycle = DIV_ROUND_UP_ULL(state->period, 2);
		state->polarity = PWM_POLARITY_NORMAL;
		state->enabled = true;
		वापस;
	पूर्ण

	अगर ((PWM_REG_PRESCAL(val, pwm->hwpwm) == PWM_PRESCAL_MASK) &&
	    sun4i_pwm->data->has_prescaler_bypass)
		prescaler = 1;
	अन्यथा
		prescaler = prescaler_table[PWM_REG_PRESCAL(val, pwm->hwpwm)];

	अगर (prescaler == 0)
		वापस;

	अगर (val & BIT_CH(PWM_ACT_STATE, pwm->hwpwm))
		state->polarity = PWM_POLARITY_NORMAL;
	अन्यथा
		state->polarity = PWM_POLARITY_INVERSED;

	अगर ((val & BIT_CH(PWM_CLK_GATING | PWM_EN, pwm->hwpwm)) ==
	    BIT_CH(PWM_CLK_GATING | PWM_EN, pwm->hwpwm))
		state->enabled = true;
	अन्यथा
		state->enabled = false;

	val = sun4i_pwm_पढ़ोl(sun4i_pwm, PWM_CH_PRD(pwm->hwpwm));

	पंचांगp = (u64)prescaler * NSEC_PER_SEC * PWM_REG_DTY(val);
	state->duty_cycle = DIV_ROUND_CLOSEST_ULL(पंचांगp, clk_rate);

	पंचांगp = (u64)prescaler * NSEC_PER_SEC * PWM_REG_PRD(val);
	state->period = DIV_ROUND_CLOSEST_ULL(पंचांगp, clk_rate);
पूर्ण

अटल पूर्णांक sun4i_pwm_calculate(काष्ठा sun4i_pwm_chip *sun4i_pwm,
			       स्थिर काष्ठा pwm_state *state,
			       u32 *dty, u32 *prd, अचिन्हित पूर्णांक *prsclr,
			       bool *bypass)
अणु
	u64 clk_rate, भाग = 0;
	अचिन्हित पूर्णांक prescaler = 0;

	clk_rate = clk_get_rate(sun4i_pwm->clk);

	*bypass = sun4i_pwm->data->has_direct_mod_clk_output &&
		  state->enabled &&
		  (state->period * clk_rate >= NSEC_PER_SEC) &&
		  (state->period * clk_rate < 2 * NSEC_PER_SEC) &&
		  (state->duty_cycle * clk_rate * 2 >= NSEC_PER_SEC);

	/* Skip calculation of other parameters अगर we bypass them */
	अगर (*bypass)
		वापस 0;

	अगर (sun4i_pwm->data->has_prescaler_bypass) अणु
		/* First, test without any prescaler when available */
		prescaler = PWM_PRESCAL_MASK;
		/*
		 * When not using any prescaler, the घड़ी period in nanoseconds
		 * is not an पूर्णांकeger so round it half up instead of
		 * truncating to get less surprising values.
		 */
		भाग = clk_rate * state->period + NSEC_PER_SEC / 2;
		करो_भाग(भाग, NSEC_PER_SEC);
		अगर (भाग - 1 > PWM_PRD_MASK)
			prescaler = 0;
	पूर्ण

	अगर (prescaler == 0) अणु
		/* Go up from the first भागider */
		क्रम (prescaler = 0; prescaler < PWM_PRESCAL_MASK; prescaler++) अणु
			अचिन्हित पूर्णांक pval = prescaler_table[prescaler];

			अगर (!pval)
				जारी;

			भाग = clk_rate;
			करो_भाग(भाग, pval);
			भाग = भाग * state->period;
			करो_भाग(भाग, NSEC_PER_SEC);
			अगर (भाग - 1 <= PWM_PRD_MASK)
				अवरोध;
		पूर्ण

		अगर (भाग - 1 > PWM_PRD_MASK)
			वापस -EINVAL;
	पूर्ण

	*prd = भाग;
	भाग *= state->duty_cycle;
	करो_भाग(भाग, state->period);
	*dty = भाग;
	*prsclr = prescaler;

	वापस 0;
पूर्ण

अटल पूर्णांक sun4i_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा sun4i_pwm_chip *sun4i_pwm = to_sun4i_pwm_chip(chip);
	काष्ठा pwm_state cstate;
	u32 ctrl, duty = 0, period = 0, val;
	पूर्णांक ret;
	अचिन्हित पूर्णांक delay_us, prescaler = 0;
	अचिन्हित दीर्घ now;
	bool bypass;

	pwm_get_state(pwm, &cstate);

	अगर (!cstate.enabled) अणु
		ret = clk_prepare_enable(sun4i_pwm->clk);
		अगर (ret) अणु
			dev_err(chip->dev, "failed to enable PWM clock\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = sun4i_pwm_calculate(sun4i_pwm, state, &duty, &period, &prescaler,
				  &bypass);
	अगर (ret) अणु
		dev_err(chip->dev, "period exceeds the maximum value\n");
		अगर (!cstate.enabled)
			clk_disable_unprepare(sun4i_pwm->clk);
		वापस ret;
	पूर्ण

	spin_lock(&sun4i_pwm->ctrl_lock);
	ctrl = sun4i_pwm_पढ़ोl(sun4i_pwm, PWM_CTRL_REG);

	अगर (sun4i_pwm->data->has_direct_mod_clk_output) अणु
		अगर (bypass) अणु
			ctrl |= BIT_CH(PWM_BYPASS, pwm->hwpwm);
			/* We can skip other parameter */
			sun4i_pwm_ग_लिखोl(sun4i_pwm, ctrl, PWM_CTRL_REG);
			spin_unlock(&sun4i_pwm->ctrl_lock);
			वापस 0;
		पूर्ण

		ctrl &= ~BIT_CH(PWM_BYPASS, pwm->hwpwm);
	पूर्ण

	अगर (PWM_REG_PRESCAL(ctrl, pwm->hwpwm) != prescaler) अणु
		/* Prescaler changed, the घड़ी has to be gated */
		ctrl &= ~BIT_CH(PWM_CLK_GATING, pwm->hwpwm);
		sun4i_pwm_ग_लिखोl(sun4i_pwm, ctrl, PWM_CTRL_REG);

		ctrl &= ~BIT_CH(PWM_PRESCAL_MASK, pwm->hwpwm);
		ctrl |= BIT_CH(prescaler, pwm->hwpwm);
	पूर्ण

	val = (duty & PWM_DTY_MASK) | PWM_PRD(period);
	sun4i_pwm_ग_लिखोl(sun4i_pwm, val, PWM_CH_PRD(pwm->hwpwm));
	sun4i_pwm->next_period[pwm->hwpwm] = jअगरfies +
		nsecs_to_jअगरfies(cstate.period + 1000);

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		ctrl &= ~BIT_CH(PWM_ACT_STATE, pwm->hwpwm);
	अन्यथा
		ctrl |= BIT_CH(PWM_ACT_STATE, pwm->hwpwm);

	ctrl |= BIT_CH(PWM_CLK_GATING, pwm->hwpwm);

	अगर (state->enabled)
		ctrl |= BIT_CH(PWM_EN, pwm->hwpwm);

	sun4i_pwm_ग_लिखोl(sun4i_pwm, ctrl, PWM_CTRL_REG);

	spin_unlock(&sun4i_pwm->ctrl_lock);

	अगर (state->enabled)
		वापस 0;

	/* We need a full period to elapse beक्रमe disabling the channel. */
	now = jअगरfies;
	अगर (समय_beक्रमe(now, sun4i_pwm->next_period[pwm->hwpwm])) अणु
		delay_us = jअगरfies_to_usecs(sun4i_pwm->next_period[pwm->hwpwm] -
					   now);
		अगर ((delay_us / 500) > MAX_UDELAY_MS)
			msleep(delay_us / 1000 + 1);
		अन्यथा
			usleep_range(delay_us, delay_us * 2);
	पूर्ण

	spin_lock(&sun4i_pwm->ctrl_lock);
	ctrl = sun4i_pwm_पढ़ोl(sun4i_pwm, PWM_CTRL_REG);
	ctrl &= ~BIT_CH(PWM_CLK_GATING, pwm->hwpwm);
	ctrl &= ~BIT_CH(PWM_EN, pwm->hwpwm);
	sun4i_pwm_ग_लिखोl(sun4i_pwm, ctrl, PWM_CTRL_REG);
	spin_unlock(&sun4i_pwm->ctrl_lock);

	clk_disable_unprepare(sun4i_pwm->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops sun4i_pwm_ops = अणु
	.apply = sun4i_pwm_apply,
	.get_state = sun4i_pwm_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा sun4i_pwm_data sun4i_pwm_dual_nobypass = अणु
	.has_prescaler_bypass = false,
	.npwm = 2,
पूर्ण;

अटल स्थिर काष्ठा sun4i_pwm_data sun4i_pwm_dual_bypass = अणु
	.has_prescaler_bypass = true,
	.npwm = 2,
पूर्ण;

अटल स्थिर काष्ठा sun4i_pwm_data sun4i_pwm_single_bypass = अणु
	.has_prescaler_bypass = true,
	.npwm = 1,
पूर्ण;

अटल स्थिर काष्ठा sun4i_pwm_data sun50i_a64_pwm_data = अणु
	.has_prescaler_bypass = true,
	.has_direct_mod_clk_output = true,
	.npwm = 1,
पूर्ण;

अटल स्थिर काष्ठा sun4i_pwm_data sun50i_h6_pwm_data = अणु
	.has_prescaler_bypass = true,
	.has_direct_mod_clk_output = true,
	.npwm = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun4i_pwm_dt_ids[] = अणु
	अणु
		.compatible = "allwinner,sun4i-a10-pwm",
		.data = &sun4i_pwm_dual_nobypass,
	पूर्ण, अणु
		.compatible = "allwinner,sun5i-a10s-pwm",
		.data = &sun4i_pwm_dual_bypass,
	पूर्ण, अणु
		.compatible = "allwinner,sun5i-a13-pwm",
		.data = &sun4i_pwm_single_bypass,
	पूर्ण, अणु
		.compatible = "allwinner,sun7i-a20-pwm",
		.data = &sun4i_pwm_dual_bypass,
	पूर्ण, अणु
		.compatible = "allwinner,sun8i-h3-pwm",
		.data = &sun4i_pwm_single_bypass,
	पूर्ण, अणु
		.compatible = "allwinner,sun50i-a64-pwm",
		.data = &sun50i_a64_pwm_data,
	पूर्ण, अणु
		.compatible = "allwinner,sun50i-h6-pwm",
		.data = &sun50i_h6_pwm_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_pwm_dt_ids);

अटल पूर्णांक sun4i_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_pwm_chip *pwm;
	पूर्णांक ret;

	pwm = devm_kzalloc(&pdev->dev, माप(*pwm), GFP_KERNEL);
	अगर (!pwm)
		वापस -ENOMEM;

	pwm->data = of_device_get_match_data(&pdev->dev);
	अगर (!pwm->data)
		वापस -ENODEV;

	pwm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pwm->base))
		वापस PTR_ERR(pwm->base);

	/*
	 * All hardware variants need a source घड़ी that is भागided and
	 * then feeds the counter that defines the output wave क्रमm. In the
	 * device tree this घड़ी is either unnamed or called "mod".
	 * Some variants (e.g. H6) need another घड़ी to access the
	 * hardware रेजिस्टरs; this is called "bus".
	 * So we request "mod" first (and ignore the corner हाल that a
	 * parent provides a "mod" घड़ी जबतक the right one would be the
	 * unnamed one of the PWM device) and अगर this is not found we fall
	 * back to the first घड़ी of the PWM.
	 */
	pwm->clk = devm_clk_get_optional(&pdev->dev, "mod");
	अगर (IS_ERR(pwm->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(pwm->clk),
				     "get mod clock failed\n");

	अगर (!pwm->clk) अणु
		pwm->clk = devm_clk_get(&pdev->dev, शून्य);
		अगर (IS_ERR(pwm->clk))
			वापस dev_err_probe(&pdev->dev, PTR_ERR(pwm->clk),
					     "get unnamed clock failed\n");
	पूर्ण

	pwm->bus_clk = devm_clk_get_optional(&pdev->dev, "bus");
	अगर (IS_ERR(pwm->bus_clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(pwm->bus_clk),
				     "get bus clock failed\n");

	pwm->rst = devm_reset_control_get_optional_shared(&pdev->dev, शून्य);
	अगर (IS_ERR(pwm->rst))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(pwm->rst),
				     "get reset failed\n");

	/* Deनिश्चित reset */
	ret = reset_control_deनिश्चित(pwm->rst);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot deassert reset control: %pe\n",
			ERR_PTR(ret));
		वापस ret;
	पूर्ण

	/*
	 * We're keeping the bus घड़ी on क्रम the sake of simplicity.
	 * Actually it only needs to be on क्रम hardware रेजिस्टर accesses.
	 */
	ret = clk_prepare_enable(pwm->bus_clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "cannot prepare and enable bus_clk %pe\n",
			ERR_PTR(ret));
		जाओ err_bus;
	पूर्ण

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &sun4i_pwm_ops;
	pwm->chip.npwm = pwm->data->npwm;
	pwm->chip.of_xlate = of_pwm_xlate_with_flags;
	pwm->chip.of_pwm_n_cells = 3;

	spin_lock_init(&pwm->ctrl_lock);

	ret = pwmchip_add(&pwm->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);
		जाओ err_pwm_add;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwm);

	वापस 0;

err_pwm_add:
	clk_disable_unprepare(pwm->bus_clk);
err_bus:
	reset_control_निश्चित(pwm->rst);

	वापस ret;
पूर्ण

अटल पूर्णांक sun4i_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun4i_pwm_chip *pwm = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&pwm->chip);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(pwm->bus_clk);
	reset_control_निश्चित(pwm->rst);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sun4i_pwm_driver = अणु
	.driver = अणु
		.name = "sun4i-pwm",
		.of_match_table = sun4i_pwm_dt_ids,
	पूर्ण,
	.probe = sun4i_pwm_probe,
	.हटाओ = sun4i_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(sun4i_pwm_driver);

MODULE_ALIAS("platform:sun4i-pwm");
MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner sun4i PWM driver");
MODULE_LICENSE("GPL v2");
