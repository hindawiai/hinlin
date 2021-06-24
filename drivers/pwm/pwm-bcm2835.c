<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2014 Bart Tanghe <bart.tanghe@thomयंत्रore.be>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

#घोषणा PWM_CONTROL		0x000
#घोषणा PWM_CONTROL_SHIFT(x)	((x) * 8)
#घोषणा PWM_CONTROL_MASK	0xff
#घोषणा PWM_MODE		0x80		/* set समयr in PWM mode */
#घोषणा PWM_ENABLE		(1 << 0)
#घोषणा PWM_POLARITY		(1 << 4)

#घोषणा PERIOD(x)		(((x) * 0x10) + 0x10)
#घोषणा DUTY(x)			(((x) * 0x10) + 0x14)

#घोषणा PERIOD_MIN		0x2

काष्ठा bcm2835_pwm अणु
	काष्ठा pwm_chip chip;
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा bcm2835_pwm *to_bcm2835_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा bcm2835_pwm, chip);
पूर्ण

अटल पूर्णांक bcm2835_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा bcm2835_pwm *pc = to_bcm2835_pwm(chip);
	u32 value;

	value = पढ़ोl(pc->base + PWM_CONTROL);
	value &= ~(PWM_CONTROL_MASK << PWM_CONTROL_SHIFT(pwm->hwpwm));
	value |= (PWM_MODE << PWM_CONTROL_SHIFT(pwm->hwpwm));
	ग_लिखोl(value, pc->base + PWM_CONTROL);

	वापस 0;
पूर्ण

अटल व्योम bcm2835_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा bcm2835_pwm *pc = to_bcm2835_pwm(chip);
	u32 value;

	value = पढ़ोl(pc->base + PWM_CONTROL);
	value &= ~(PWM_CONTROL_MASK << PWM_CONTROL_SHIFT(pwm->hwpwm));
	ग_लिखोl(value, pc->base + PWM_CONTROL);
पूर्ण

अटल पूर्णांक bcm2835_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     स्थिर काष्ठा pwm_state *state)
अणु

	काष्ठा bcm2835_pwm *pc = to_bcm2835_pwm(chip);
	अचिन्हित दीर्घ rate = clk_get_rate(pc->clk);
	अचिन्हित दीर्घ दीर्घ period_cycles;
	u64 max_period;

	u32 val;

	अगर (!rate) अणु
		dev_err(pc->dev, "failed to get clock rate\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * period_cycles must be a 32 bit value, so period * rate / NSEC_PER_SEC
	 * must be <= U32_MAX. As U32_MAX * NSEC_PER_SEC < U64_MAX the
	 * multiplication period * rate करोesn't overflow.
	 * To calculate the maximal possible period that guarantees the
	 * above inequality:
	 *
	 *     round(period * rate / NSEC_PER_SEC) <= U32_MAX
	 * <=> period * rate / NSEC_PER_SEC < U32_MAX + 0.5
	 * <=> period * rate < (U32_MAX + 0.5) * NSEC_PER_SEC
	 * <=> period < ((U32_MAX + 0.5) * NSEC_PER_SEC) / rate
	 * <=> period < ((U32_MAX * NSEC_PER_SEC + NSEC_PER_SEC/2) / rate
	 * <=> period <= उच्चमान((U32_MAX * NSEC_PER_SEC + NSEC_PER_SEC/2) / rate) - 1
	 */
	max_period = DIV_ROUND_UP_ULL((u64)U32_MAX * NSEC_PER_SEC + NSEC_PER_SEC / 2, rate) - 1;

	अगर (state->period > max_period)
		वापस -EINVAL;

	/* set period */
	period_cycles = DIV_ROUND_CLOSEST_ULL(state->period * rate, NSEC_PER_SEC);

	/* करोn't accept a period that is too small */
	अगर (period_cycles < PERIOD_MIN)
		वापस -EINVAL;

	ग_लिखोl(period_cycles, pc->base + PERIOD(pwm->hwpwm));

	/* set duty cycle */
	val = DIV_ROUND_CLOSEST_ULL(state->duty_cycle * rate, NSEC_PER_SEC);
	ग_लिखोl(val, pc->base + DUTY(pwm->hwpwm));

	/* set polarity */
	val = पढ़ोl(pc->base + PWM_CONTROL);

	अगर (state->polarity == PWM_POLARITY_NORMAL)
		val &= ~(PWM_POLARITY << PWM_CONTROL_SHIFT(pwm->hwpwm));
	अन्यथा
		val |= PWM_POLARITY << PWM_CONTROL_SHIFT(pwm->hwpwm);

	/* enable/disable */
	अगर (state->enabled)
		val |= PWM_ENABLE << PWM_CONTROL_SHIFT(pwm->hwpwm);
	अन्यथा
		val &= ~(PWM_ENABLE << PWM_CONTROL_SHIFT(pwm->hwpwm));

	ग_लिखोl(val, pc->base + PWM_CONTROL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops bcm2835_pwm_ops = अणु
	.request = bcm2835_pwm_request,
	.मुक्त = bcm2835_pwm_मुक्त,
	.apply = bcm2835_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक bcm2835_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_pwm *pc;
	पूर्णांक ret;

	pc = devm_kzalloc(&pdev->dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	pc->dev = &pdev->dev;

	pc->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pc->base))
		वापस PTR_ERR(pc->base);

	pc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pc->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(pc->clk),
				     "clock not found\n");

	ret = clk_prepare_enable(pc->clk);
	अगर (ret)
		वापस ret;

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &bcm2835_pwm_ops;
	pc->chip.npwm = 2;
	pc->chip.of_xlate = of_pwm_xlate_with_flags;
	pc->chip.of_pwm_n_cells = 3;

	platक्रमm_set_drvdata(pdev, pc);

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0)
		जाओ add_fail;

	वापस 0;

add_fail:
	clk_disable_unprepare(pc->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm2835_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm2835_pwm *pc = platक्रमm_get_drvdata(pdev);

	pwmchip_हटाओ(&pc->chip);

	clk_disable_unprepare(pc->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm2835_pwm_of_match[] = अणु
	अणु .compatible = "brcm,bcm2835-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm2835_pwm_of_match);

अटल काष्ठा platक्रमm_driver bcm2835_pwm_driver = अणु
	.driver = अणु
		.name = "bcm2835-pwm",
		.of_match_table = bcm2835_pwm_of_match,
	पूर्ण,
	.probe = bcm2835_pwm_probe,
	.हटाओ = bcm2835_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(bcm2835_pwm_driver);

MODULE_AUTHOR("Bart Tanghe <bart.tanghe@thomasmore.be>");
MODULE_DESCRIPTION("Broadcom BCM2835 PWM driver");
MODULE_LICENSE("GPL v2");
