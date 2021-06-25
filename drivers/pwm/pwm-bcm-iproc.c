<शैली गुरु>
/*
 * Copyright (C) 2016 Broadcom
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

#घोषणा IPROC_PWM_CTRL_OFFSET			0x00
#घोषणा IPROC_PWM_CTRL_TYPE_SHIFT(ch)		(15 + (ch))
#घोषणा IPROC_PWM_CTRL_POLARITY_SHIFT(ch)	(8 + (ch))
#घोषणा IPROC_PWM_CTRL_EN_SHIFT(ch)		(ch)

#घोषणा IPROC_PWM_PERIOD_OFFSET(ch)		(0x04 + ((ch) << 3))
#घोषणा IPROC_PWM_PERIOD_MIN			0x02
#घोषणा IPROC_PWM_PERIOD_MAX			0xffff

#घोषणा IPROC_PWM_DUTY_CYCLE_OFFSET(ch)		(0x08 + ((ch) << 3))
#घोषणा IPROC_PWM_DUTY_CYCLE_MIN		0x00
#घोषणा IPROC_PWM_DUTY_CYCLE_MAX		0xffff

#घोषणा IPROC_PWM_PRESCALE_OFFSET		0x24
#घोषणा IPROC_PWM_PRESCALE_BITS			0x06
#घोषणा IPROC_PWM_PRESCALE_SHIFT(ch)		((3 - (ch)) * \
						 IPROC_PWM_PRESCALE_BITS)
#घोषणा IPROC_PWM_PRESCALE_MASK(ch)		(IPROC_PWM_PRESCALE_MAX << \
						 IPROC_PWM_PRESCALE_SHIFT(ch))
#घोषणा IPROC_PWM_PRESCALE_MIN			0x00
#घोषणा IPROC_PWM_PRESCALE_MAX			0x3f

काष्ठा iproc_pwmc अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा iproc_pwmc *to_iproc_pwmc(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा iproc_pwmc, chip);
पूर्ण

अटल व्योम iproc_pwmc_enable(काष्ठा iproc_pwmc *ip, अचिन्हित पूर्णांक channel)
अणु
	u32 value;

	value = पढ़ोl(ip->base + IPROC_PWM_CTRL_OFFSET);
	value |= 1 << IPROC_PWM_CTRL_EN_SHIFT(channel);
	ग_लिखोl(value, ip->base + IPROC_PWM_CTRL_OFFSET);

	/* must be a 400 ns delay between clearing and setting enable bit */
	ndelay(400);
पूर्ण

अटल व्योम iproc_pwmc_disable(काष्ठा iproc_pwmc *ip, अचिन्हित पूर्णांक channel)
अणु
	u32 value;

	value = पढ़ोl(ip->base + IPROC_PWM_CTRL_OFFSET);
	value &= ~(1 << IPROC_PWM_CTRL_EN_SHIFT(channel));
	ग_लिखोl(value, ip->base + IPROC_PWM_CTRL_OFFSET);

	/* must be a 400 ns delay between clearing and setting enable bit */
	ndelay(400);
पूर्ण

अटल व्योम iproc_pwmc_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				 काष्ठा pwm_state *state)
अणु
	काष्ठा iproc_pwmc *ip = to_iproc_pwmc(chip);
	u64 पंचांगp, multi, rate;
	u32 value, prescale;

	value = पढ़ोl(ip->base + IPROC_PWM_CTRL_OFFSET);

	अगर (value & BIT(IPROC_PWM_CTRL_EN_SHIFT(pwm->hwpwm)))
		state->enabled = true;
	अन्यथा
		state->enabled = false;

	अगर (value & BIT(IPROC_PWM_CTRL_POLARITY_SHIFT(pwm->hwpwm)))
		state->polarity = PWM_POLARITY_NORMAL;
	अन्यथा
		state->polarity = PWM_POLARITY_INVERSED;

	rate = clk_get_rate(ip->clk);
	अगर (rate == 0) अणु
		state->period = 0;
		state->duty_cycle = 0;
		वापस;
	पूर्ण

	value = पढ़ोl(ip->base + IPROC_PWM_PRESCALE_OFFSET);
	prescale = value >> IPROC_PWM_PRESCALE_SHIFT(pwm->hwpwm);
	prescale &= IPROC_PWM_PRESCALE_MAX;

	multi = NSEC_PER_SEC * (prescale + 1);

	value = पढ़ोl(ip->base + IPROC_PWM_PERIOD_OFFSET(pwm->hwpwm));
	पंचांगp = (value & IPROC_PWM_PERIOD_MAX) * multi;
	state->period = भाग64_u64(पंचांगp, rate);

	value = पढ़ोl(ip->base + IPROC_PWM_DUTY_CYCLE_OFFSET(pwm->hwpwm));
	पंचांगp = (value & IPROC_PWM_PERIOD_MAX) * multi;
	state->duty_cycle = भाग64_u64(पंचांगp, rate);
पूर्ण

अटल पूर्णांक iproc_pwmc_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			    स्थिर काष्ठा pwm_state *state)
अणु
	अचिन्हित दीर्घ prescale = IPROC_PWM_PRESCALE_MIN;
	काष्ठा iproc_pwmc *ip = to_iproc_pwmc(chip);
	u32 value, period, duty;
	u64 rate;

	rate = clk_get_rate(ip->clk);

	/*
	 * Find period count, duty count and prescale to suit duty_cycle and
	 * period. This is करोne according to क्रमmulas described below:
	 *
	 * period_ns = 10^9 * (PRESCALE + 1) * PC / PWM_CLK_RATE
	 * duty_ns = 10^9 * (PRESCALE + 1) * DC / PWM_CLK_RATE
	 *
	 * PC = (PWM_CLK_RATE * period_ns) / (10^9 * (PRESCALE + 1))
	 * DC = (PWM_CLK_RATE * duty_ns) / (10^9 * (PRESCALE + 1))
	 */
	जबतक (1) अणु
		u64 value, भाग;

		भाग = NSEC_PER_SEC * (prescale + 1);
		value = rate * state->period;
		period = भाग64_u64(value, भाग);
		value = rate * state->duty_cycle;
		duty = भाग64_u64(value, भाग);

		अगर (period < IPROC_PWM_PERIOD_MIN)
			वापस -EINVAL;

		अगर (period <= IPROC_PWM_PERIOD_MAX &&
		     duty <= IPROC_PWM_DUTY_CYCLE_MAX)
			अवरोध;

		/* Otherwise, increase prescale and recalculate counts */
		अगर (++prescale > IPROC_PWM_PRESCALE_MAX)
			वापस -EINVAL;
	पूर्ण

	iproc_pwmc_disable(ip, pwm->hwpwm);

	/* Set prescale */
	value = पढ़ोl(ip->base + IPROC_PWM_PRESCALE_OFFSET);
	value &= ~IPROC_PWM_PRESCALE_MASK(pwm->hwpwm);
	value |= prescale << IPROC_PWM_PRESCALE_SHIFT(pwm->hwpwm);
	ग_लिखोl(value, ip->base + IPROC_PWM_PRESCALE_OFFSET);

	/* set period and duty cycle */
	ग_लिखोl(period, ip->base + IPROC_PWM_PERIOD_OFFSET(pwm->hwpwm));
	ग_लिखोl(duty, ip->base + IPROC_PWM_DUTY_CYCLE_OFFSET(pwm->hwpwm));

	/* set polarity */
	value = पढ़ोl(ip->base + IPROC_PWM_CTRL_OFFSET);

	अगर (state->polarity == PWM_POLARITY_NORMAL)
		value |= 1 << IPROC_PWM_CTRL_POLARITY_SHIFT(pwm->hwpwm);
	अन्यथा
		value &= ~(1 << IPROC_PWM_CTRL_POLARITY_SHIFT(pwm->hwpwm));

	ग_लिखोl(value, ip->base + IPROC_PWM_CTRL_OFFSET);

	अगर (state->enabled)
		iproc_pwmc_enable(ip, pwm->hwpwm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops iproc_pwm_ops = अणु
	.apply = iproc_pwmc_apply,
	.get_state = iproc_pwmc_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक iproc_pwmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_pwmc *ip;
	अचिन्हित पूर्णांक i;
	u32 value;
	पूर्णांक ret;

	ip = devm_kzalloc(&pdev->dev, माप(*ip), GFP_KERNEL);
	अगर (!ip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ip);

	ip->chip.dev = &pdev->dev;
	ip->chip.ops = &iproc_pwm_ops;
	ip->chip.npwm = 4;
	ip->chip.of_xlate = of_pwm_xlate_with_flags;
	ip->chip.of_pwm_n_cells = 3;

	ip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ip->base))
		वापस PTR_ERR(ip->base);

	ip->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(ip->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock: %ld\n",
			PTR_ERR(ip->clk));
		वापस PTR_ERR(ip->clk);
	पूर्ण

	ret = clk_prepare_enable(ip->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set full drive and normal polarity क्रम all channels */
	value = पढ़ोl(ip->base + IPROC_PWM_CTRL_OFFSET);

	क्रम (i = 0; i < ip->chip.npwm; i++) अणु
		value &= ~(1 << IPROC_PWM_CTRL_TYPE_SHIFT(i));
		value |= 1 << IPROC_PWM_CTRL_POLARITY_SHIFT(i);
	पूर्ण

	ग_लिखोl(value, ip->base + IPROC_PWM_CTRL_OFFSET);

	ret = pwmchip_add(&ip->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);
		clk_disable_unprepare(ip->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक iproc_pwmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा iproc_pwmc *ip = platक्रमm_get_drvdata(pdev);

	pwmchip_हटाओ(&ip->chip);

	clk_disable_unprepare(ip->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_iproc_pwmc_dt[] = अणु
	अणु .compatible = "brcm,iproc-pwm" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_iproc_pwmc_dt);

अटल काष्ठा platक्रमm_driver iproc_pwmc_driver = अणु
	.driver = अणु
		.name = "bcm-iproc-pwm",
		.of_match_table = bcm_iproc_pwmc_dt,
	पूर्ण,
	.probe = iproc_pwmc_probe,
	.हटाओ = iproc_pwmc_हटाओ,
पूर्ण;
module_platक्रमm_driver(iproc_pwmc_driver);

MODULE_AUTHOR("Yendapally Reddy Dhananjaya Reddy <yendapally.reddy@broadcom.com>");
MODULE_DESCRIPTION("Broadcom iProc PWM driver");
MODULE_LICENSE("GPL v2");
