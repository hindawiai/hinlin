<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Toshiba Visconti pulse-width-modulation controller driver
 *
 * Copyright (c) 2020 - 2021 TOSHIBA CORPORATION
 * Copyright (c) 2020 - 2021 Toshiba Electronic Devices & Storage Corporation
 *
 * Authors: Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>
 *
 * Limitations:
 * - The fixed input घड़ी is running at 1 MHz and is भागided by either 1,
 *   2, 4 or 8.
 * - When the settings of the PWM are modअगरied, the new values are shaकरोwed
 *   in hardware until the PIPGM_PCSR रेजिस्टर is written and the currently
 *   running period is completed. This way the hardware चयनes atomically
 *   from the old setting to the new.
 * - Disabling the hardware completes the currently running period and keeps
 *   the output at low level at all बार.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

#घोषणा PIPGM_PCSR(ch) (0x400 + 4 * (ch))
#घोषणा PIPGM_PDUT(ch) (0x420 + 4 * (ch))
#घोषणा PIPGM_PWMC(ch) (0x440 + 4 * (ch))

#घोषणा PIPGM_PWMC_PWMACT		BIT(5)
#घोषणा PIPGM_PWMC_CLK_MASK		GENMASK(1, 0)
#घोषणा PIPGM_PWMC_POLARITY_MASK	GENMASK(5, 5)

काष्ठा visconti_pwm_chip अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत काष्ठा visconti_pwm_chip *visconti_pwm_from_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा visconti_pwm_chip, chip);
पूर्ण

अटल पूर्णांक visconti_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा visconti_pwm_chip *priv = visconti_pwm_from_chip(chip);
	u32 period, duty_cycle, pwmc0;

	अगर (!state->enabled) अणु
		ग_लिखोl(0, priv->base + PIPGM_PCSR(pwm->hwpwm));
		वापस 0;
	पूर्ण

	/*
	 * The biggest period the hardware can provide is
	 *	(0xffff << 3) * 1000 ns
	 * This value fits easily in an u32, so simplअगरy the maths by
	 * capping the values to 32 bit पूर्णांकegers.
	 */
	अगर (state->period > (0xffff << 3) * 1000)
		period = (0xffff << 3) * 1000;
	अन्यथा
		period = state->period;

	अगर (state->duty_cycle > period)
		duty_cycle = period;
	अन्यथा
		duty_cycle = state->duty_cycle;

	/*
	 * The input घड़ी runs fixed at 1 MHz, so we have only
	 * microsecond resolution and so can भागide by
	 * NSEC_PER_SEC / CLKFREQ = 1000 without losing precision.
	 */
	period /= 1000;
	duty_cycle /= 1000;

	अगर (!period)
		वापस -दुस्फल;

	/*
	 * PWMC controls a भागider that भागides the input clk by a
	 * घातer of two between 1 and 8. As a smaller भागider yields
	 * higher precision, pick the smallest possible one.
	 */
	अगर (period > 0xffff) अणु
		pwmc0 = ilog2(period >> 16);
		अगर (WARN_ON(pwmc0 > 3))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		pwmc0 = 0;
	पूर्ण

	period >>= pwmc0;
	duty_cycle >>= pwmc0;

	अगर (state->polarity == PWM_POLARITY_INVERSED)
		pwmc0 |= PIPGM_PWMC_PWMACT;
	ग_लिखोl(pwmc0, priv->base + PIPGM_PWMC(pwm->hwpwm));
	ग_लिखोl(duty_cycle, priv->base + PIPGM_PDUT(pwm->hwpwm));
	ग_लिखोl(period, priv->base + PIPGM_PCSR(pwm->hwpwm));

	वापस 0;
पूर्ण

अटल व्योम visconti_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				   काष्ठा pwm_state *state)
अणु
	काष्ठा visconti_pwm_chip *priv = visconti_pwm_from_chip(chip);
	u32 period, duty, pwmc0, pwmc0_clk;

	period = पढ़ोl(priv->base + PIPGM_PCSR(pwm->hwpwm));
	duty = पढ़ोl(priv->base + PIPGM_PDUT(pwm->hwpwm));
	pwmc0 = पढ़ोl(priv->base + PIPGM_PWMC(pwm->hwpwm));
	pwmc0_clk = pwmc0 & PIPGM_PWMC_CLK_MASK;

	state->period = (period << pwmc0_clk) * NSEC_PER_USEC;
	state->duty_cycle = (duty << pwmc0_clk) * NSEC_PER_USEC;
	अगर (pwmc0 & PIPGM_PWMC_POLARITY_MASK)
		state->polarity = PWM_POLARITY_INVERSED;
	अन्यथा
		state->polarity = PWM_POLARITY_NORMAL;

	state->enabled = true;
पूर्ण

अटल स्थिर काष्ठा pwm_ops visconti_pwm_ops = अणु
	.apply = visconti_pwm_apply,
	.get_state = visconti_pwm_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक visconti_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा visconti_pwm_chip *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	platक्रमm_set_drvdata(pdev, priv);

	priv->chip.dev = dev;
	priv->chip.ops = &visconti_pwm_ops;
	priv->chip.npwm = 4;

	ret = pwmchip_add(&priv->chip);
	अगर (ret < 0)
		वापस dev_err_probe(&pdev->dev, ret, "Cannot register visconti PWM\n");

	वापस 0;
पूर्ण

अटल पूर्णांक visconti_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा visconti_pwm_chip *priv = platक्रमm_get_drvdata(pdev);

	pwmchip_हटाओ(&priv->chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id visconti_pwm_of_match[] = अणु
	अणु .compatible = "toshiba,visconti-pwm", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, visconti_pwm_of_match);

अटल काष्ठा platक्रमm_driver visconti_pwm_driver = अणु
	.driver = अणु
		.name = "pwm-visconti",
		.of_match_table = visconti_pwm_of_match,
	पूर्ण,
	.probe = visconti_pwm_probe,
	.हटाओ = visconti_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(visconti_pwm_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Nobuhiro Iwamatsu <nobuhiro1.iwamatsu@toshiba.co.jp>");
MODULE_ALIAS("platform:pwm-visconti");
