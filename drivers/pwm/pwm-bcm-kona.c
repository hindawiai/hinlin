<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
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
#समावेश <linux/ioport.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

/*
 * The Kona PWM has some unusual अक्षरacteristics.  Here are the मुख्य poपूर्णांकs.
 *
 * 1) There is no disable bit and the hardware करोcs advise programming a zero
 *    duty to achieve output equivalent to that of a normal disable operation.
 *
 * 2) Changes to prescale, duty, period, and polarity करो not take effect until
 *    a subsequent rising edge of the trigger bit.
 *
 * 3) If the smooth bit and trigger bit are both low, the output is a स्थिरant
 *    high संकेत.  Otherwise, the earlier waveक्रमm जारीs to be output.
 *
 * 4) If the smooth bit is set on the rising edge of the trigger bit, output
 *    will transition to the new settings on a period boundary (which could be
 *    seconds away).  If the smooth bit is clear, new settings will be applied
 *    as soon as possible (the hardware always has a 400ns delay).
 *
 * 5) When the बाह्यal घड़ी that feeds the PWM is disabled, output is pegged
 *    high or low depending on its state at that exact instant.
 */

#घोषणा PWM_CONTROL_OFFSET			0x00000000
#घोषणा PWM_CONTROL_SMOOTH_SHIFT(chan)		(24 + (chan))
#घोषणा PWM_CONTROL_TYPE_SHIFT(chan)		(16 + (chan))
#घोषणा PWM_CONTROL_POLARITY_SHIFT(chan)	(8 + (chan))
#घोषणा PWM_CONTROL_TRIGGER_SHIFT(chan)		(chan)

#घोषणा PRESCALE_OFFSET				0x00000004
#घोषणा PRESCALE_SHIFT(chan)			((chan) << 2)
#घोषणा PRESCALE_MASK(chan)			(0x7 << PRESCALE_SHIFT(chan))
#घोषणा PRESCALE_MIN				0x00000000
#घोषणा PRESCALE_MAX				0x00000007

#घोषणा PERIOD_COUNT_OFFSET(chan)		(0x00000008 + ((chan) << 3))
#घोषणा PERIOD_COUNT_MIN			0x00000002
#घोषणा PERIOD_COUNT_MAX			0x00ffffff

#घोषणा DUTY_CYCLE_HIGH_OFFSET(chan)		(0x0000000c + ((chan) << 3))
#घोषणा DUTY_CYCLE_HIGH_MIN			0x00000000
#घोषणा DUTY_CYCLE_HIGH_MAX			0x00ffffff

काष्ठा kona_pwmc अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा kona_pwmc *to_kona_pwmc(काष्ठा pwm_chip *_chip)
अणु
	वापस container_of(_chip, काष्ठा kona_pwmc, chip);
पूर्ण

/*
 * Clear trigger bit but set smooth bit to मुख्यtain old output.
 */
अटल व्योम kona_pwmc_prepare_क्रम_settings(काष्ठा kona_pwmc *kp,
	अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित पूर्णांक value = पढ़ोl(kp->base + PWM_CONTROL_OFFSET);

	value |= 1 << PWM_CONTROL_SMOOTH_SHIFT(chan);
	value &= ~(1 << PWM_CONTROL_TRIGGER_SHIFT(chan));
	ग_लिखोl(value, kp->base + PWM_CONTROL_OFFSET);

	/*
	 * There must be a min 400ns delay between clearing trigger and setting
	 * it. Failing to करो this may result in no PWM संकेत.
	 */
	ndelay(400);
पूर्ण

अटल व्योम kona_pwmc_apply_settings(काष्ठा kona_pwmc *kp, अचिन्हित पूर्णांक chan)
अणु
	अचिन्हित पूर्णांक value = पढ़ोl(kp->base + PWM_CONTROL_OFFSET);

	/* Set trigger bit and clear smooth bit to apply new settings */
	value &= ~(1 << PWM_CONTROL_SMOOTH_SHIFT(chan));
	value |= 1 << PWM_CONTROL_TRIGGER_SHIFT(chan);
	ग_लिखोl(value, kp->base + PWM_CONTROL_OFFSET);

	/* Trigger bit must be held high क्रम at least 400 ns. */
	ndelay(400);
पूर्ण

अटल पूर्णांक kona_pwmc_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			    पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा kona_pwmc *kp = to_kona_pwmc(chip);
	u64 val, भाग, rate;
	अचिन्हित दीर्घ prescale = PRESCALE_MIN, pc, dc;
	अचिन्हित पूर्णांक value, chan = pwm->hwpwm;

	/*
	 * Find period count, duty count and prescale to suit duty_ns and
	 * period_ns. This is करोne according to क्रमmulas described below:
	 *
	 * period_ns = 10^9 * (PRESCALE + 1) * PC / PWM_CLK_RATE
	 * duty_ns = 10^9 * (PRESCALE + 1) * DC / PWM_CLK_RATE
	 *
	 * PC = (PWM_CLK_RATE * period_ns) / (10^9 * (PRESCALE + 1))
	 * DC = (PWM_CLK_RATE * duty_ns) / (10^9 * (PRESCALE + 1))
	 */

	rate = clk_get_rate(kp->clk);

	जबतक (1) अणु
		भाग = 1000000000;
		भाग *= 1 + prescale;
		val = rate * period_ns;
		pc = भाग64_u64(val, भाग);
		val = rate * duty_ns;
		dc = भाग64_u64(val, भाग);

		/* If duty_ns or period_ns are not achievable then वापस */
		अगर (pc < PERIOD_COUNT_MIN)
			वापस -EINVAL;

		/* If pc and dc are in bounds, the calculation is करोne */
		अगर (pc <= PERIOD_COUNT_MAX && dc <= DUTY_CYCLE_HIGH_MAX)
			अवरोध;

		/* Otherwise, increase prescale and recalculate pc and dc */
		अगर (++prescale > PRESCALE_MAX)
			वापस -EINVAL;
	पूर्ण

	/*
	 * Don't apply settings अगर disabled. The period and duty cycle are
	 * always calculated above to ensure the new values are
	 * validated immediately instead of on enable.
	 */
	अगर (pwm_is_enabled(pwm)) अणु
		kona_pwmc_prepare_क्रम_settings(kp, chan);

		value = पढ़ोl(kp->base + PRESCALE_OFFSET);
		value &= ~PRESCALE_MASK(chan);
		value |= prescale << PRESCALE_SHIFT(chan);
		ग_लिखोl(value, kp->base + PRESCALE_OFFSET);

		ग_लिखोl(pc, kp->base + PERIOD_COUNT_OFFSET(chan));

		ग_लिखोl(dc, kp->base + DUTY_CYCLE_HIGH_OFFSET(chan));

		kona_pwmc_apply_settings(kp, chan);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kona_pwmc_set_polarity(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				  क्रमागत pwm_polarity polarity)
अणु
	काष्ठा kona_pwmc *kp = to_kona_pwmc(chip);
	अचिन्हित पूर्णांक chan = pwm->hwpwm;
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	ret = clk_prepare_enable(kp->clk);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	kona_pwmc_prepare_क्रम_settings(kp, chan);

	value = पढ़ोl(kp->base + PWM_CONTROL_OFFSET);

	अगर (polarity == PWM_POLARITY_NORMAL)
		value |= 1 << PWM_CONTROL_POLARITY_SHIFT(chan);
	अन्यथा
		value &= ~(1 << PWM_CONTROL_POLARITY_SHIFT(chan));

	ग_लिखोl(value, kp->base + PWM_CONTROL_OFFSET);

	kona_pwmc_apply_settings(kp, chan);

	clk_disable_unprepare(kp->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक kona_pwmc_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा kona_pwmc *kp = to_kona_pwmc(chip);
	पूर्णांक ret;

	ret = clk_prepare_enable(kp->clk);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = kona_pwmc_config(chip, pwm, pwm_get_duty_cycle(pwm),
			       pwm_get_period(pwm));
	अगर (ret < 0) अणु
		clk_disable_unprepare(kp->clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम kona_pwmc_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा kona_pwmc *kp = to_kona_pwmc(chip);
	अचिन्हित पूर्णांक chan = pwm->hwpwm;
	अचिन्हित पूर्णांक value;

	kona_pwmc_prepare_क्रम_settings(kp, chan);

	/* Simulate a disable by configuring क्रम zero duty */
	ग_लिखोl(0, kp->base + DUTY_CYCLE_HIGH_OFFSET(chan));
	ग_लिखोl(0, kp->base + PERIOD_COUNT_OFFSET(chan));

	/* Set prescale to 0 क्रम this channel */
	value = पढ़ोl(kp->base + PRESCALE_OFFSET);
	value &= ~PRESCALE_MASK(chan);
	ग_लिखोl(value, kp->base + PRESCALE_OFFSET);

	kona_pwmc_apply_settings(kp, chan);

	clk_disable_unprepare(kp->clk);
पूर्ण

अटल स्थिर काष्ठा pwm_ops kona_pwm_ops = अणु
	.config = kona_pwmc_config,
	.set_polarity = kona_pwmc_set_polarity,
	.enable = kona_pwmc_enable,
	.disable = kona_pwmc_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक kona_pwmc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kona_pwmc *kp;
	अचिन्हित पूर्णांक chan;
	अचिन्हित पूर्णांक value = 0;
	पूर्णांक ret = 0;

	kp = devm_kzalloc(&pdev->dev, माप(*kp), GFP_KERNEL);
	अगर (kp == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, kp);

	kp->chip.dev = &pdev->dev;
	kp->chip.ops = &kona_pwm_ops;
	kp->chip.npwm = 6;
	kp->chip.of_xlate = of_pwm_xlate_with_flags;
	kp->chip.of_pwm_n_cells = 3;

	kp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(kp->base))
		वापस PTR_ERR(kp->base);

	kp->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(kp->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock: %ld\n",
			PTR_ERR(kp->clk));
		वापस PTR_ERR(kp->clk);
	पूर्ण

	ret = clk_prepare_enable(kp->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set push/pull क्रम all channels */
	क्रम (chan = 0; chan < kp->chip.npwm; chan++)
		value |= (1 << PWM_CONTROL_TYPE_SHIFT(chan));

	ग_लिखोl(value, kp->base + PWM_CONTROL_OFFSET);

	clk_disable_unprepare(kp->clk);

	ret = pwmchip_add(&kp->chip);
	अगर (ret < 0)
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक kona_pwmc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kona_pwmc *kp = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&kp->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_kona_pwmc_dt[] = अणु
	अणु .compatible = "brcm,kona-pwm" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_kona_pwmc_dt);

अटल काष्ठा platक्रमm_driver kona_pwmc_driver = अणु
	.driver = अणु
		.name = "bcm-kona-pwm",
		.of_match_table = bcm_kona_pwmc_dt,
	पूर्ण,
	.probe = kona_pwmc_probe,
	.हटाओ = kona_pwmc_हटाओ,
पूर्ण;
module_platक्रमm_driver(kona_pwmc_driver);

MODULE_AUTHOR("Broadcom Corporation <bcm-kernel-feedback-list@broadcom.com>");
MODULE_AUTHOR("Tim Kryger <tkryger@broadcom.com>");
MODULE_DESCRIPTION("Broadcom Kona PWM driver");
MODULE_LICENSE("GPL v2");
