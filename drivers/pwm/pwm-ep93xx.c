<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PWM framework driver क्रम Cirrus Logic EP93xx
 *
 * Copyright (c) 2009        Matthieu Crapet <mcrapet@gmail.com>
 * Copyright (c) 2009, 2013  H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * EP9301/02 have only one channel:
 *   platक्रमm device ep93xx-pwm.1 - PWMOUT1 (EGPIO14)
 *
 * EP9307 has only one channel:
 *   platक्रमm device ep93xx-pwm.0 - PWMOUT
 *
 * EP9312/15 have two channels:
 *   platक्रमm device ep93xx-pwm.0 - PWMOUT
 *   platक्रमm device ep93xx-pwm.1 - PWMOUT1 (EGPIO14)
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/pwm.h>

#समावेश <यंत्र/भाग64.h>

#समावेश <linux/soc/cirrus/ep93xx.h>	/* क्रम ep93xx_pwm_अणुacquire,releaseपूर्ण_gpio() */

#घोषणा EP93XX_PWMx_TERM_COUNT	0x00
#घोषणा EP93XX_PWMx_DUTY_CYCLE	0x04
#घोषणा EP93XX_PWMx_ENABLE	0x08
#घोषणा EP93XX_PWMx_INVERT	0x0c

काष्ठा ep93xx_pwm अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा pwm_chip chip;
पूर्ण;

अटल अंतरभूत काष्ठा ep93xx_pwm *to_ep93xx_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा ep93xx_pwm, chip);
पूर्ण

अटल पूर्णांक ep93xx_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(chip->dev);

	वापस ep93xx_pwm_acquire_gpio(pdev);
पूर्ण

अटल व्योम ep93xx_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(chip->dev);

	ep93xx_pwm_release_gpio(pdev);
पूर्ण

अटल पूर्णांक ep93xx_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा ep93xx_pwm *ep93xx_pwm = to_ep93xx_pwm(chip);
	व्योम __iomem *base = ep93xx_pwm->base;
	अचिन्हित दीर्घ दीर्घ c;
	अचिन्हित दीर्घ period_cycles;
	अचिन्हित दीर्घ duty_cycles;
	अचिन्हित दीर्घ term;
	पूर्णांक ret = 0;

	/*
	 * The घड़ी needs to be enabled to access the PWM रेजिस्टरs.
	 * Configuration can be changed at any समय.
	 */
	अगर (!pwm_is_enabled(pwm)) अणु
		ret = clk_enable(ep93xx_pwm->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	c = clk_get_rate(ep93xx_pwm->clk);
	c *= period_ns;
	करो_भाग(c, 1000000000);
	period_cycles = c;

	c = period_cycles;
	c *= duty_ns;
	करो_भाग(c, period_ns);
	duty_cycles = c;

	अगर (period_cycles < 0x10000 && duty_cycles < 0x10000) अणु
		term = पढ़ोw(base + EP93XX_PWMx_TERM_COUNT);

		/* Order is important अगर PWM is running */
		अगर (period_cycles > term) अणु
			ग_लिखोw(period_cycles, base + EP93XX_PWMx_TERM_COUNT);
			ग_लिखोw(duty_cycles, base + EP93XX_PWMx_DUTY_CYCLE);
		पूर्ण अन्यथा अणु
			ग_लिखोw(duty_cycles, base + EP93XX_PWMx_DUTY_CYCLE);
			ग_लिखोw(period_cycles, base + EP93XX_PWMx_TERM_COUNT);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	अगर (!pwm_is_enabled(pwm))
		clk_disable(ep93xx_pwm->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक ep93xx_pwm_polarity(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       क्रमागत pwm_polarity polarity)
अणु
	काष्ठा ep93xx_pwm *ep93xx_pwm = to_ep93xx_pwm(chip);
	पूर्णांक ret;

	/*
	 * The घड़ी needs to be enabled to access the PWM रेजिस्टरs.
	 * Polarity can only be changed when the PWM is disabled.
	 */
	ret = clk_enable(ep93xx_pwm->clk);
	अगर (ret)
		वापस ret;

	अगर (polarity == PWM_POLARITY_INVERSED)
		ग_लिखोw(0x1, ep93xx_pwm->base + EP93XX_PWMx_INVERT);
	अन्यथा
		ग_लिखोw(0x0, ep93xx_pwm->base + EP93XX_PWMx_INVERT);

	clk_disable(ep93xx_pwm->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा ep93xx_pwm *ep93xx_pwm = to_ep93xx_pwm(chip);
	पूर्णांक ret;

	ret = clk_enable(ep93xx_pwm->clk);
	अगर (ret)
		वापस ret;

	ग_लिखोw(0x1, ep93xx_pwm->base + EP93XX_PWMx_ENABLE);

	वापस 0;
पूर्ण

अटल व्योम ep93xx_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा ep93xx_pwm *ep93xx_pwm = to_ep93xx_pwm(chip);

	ग_लिखोw(0x0, ep93xx_pwm->base + EP93XX_PWMx_ENABLE);
	clk_disable(ep93xx_pwm->clk);
पूर्ण

अटल स्थिर काष्ठा pwm_ops ep93xx_pwm_ops = अणु
	.request = ep93xx_pwm_request,
	.मुक्त = ep93xx_pwm_मुक्त,
	.config = ep93xx_pwm_config,
	.set_polarity = ep93xx_pwm_polarity,
	.enable = ep93xx_pwm_enable,
	.disable = ep93xx_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक ep93xx_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_pwm *ep93xx_pwm;
	पूर्णांक ret;

	ep93xx_pwm = devm_kzalloc(&pdev->dev, माप(*ep93xx_pwm), GFP_KERNEL);
	अगर (!ep93xx_pwm)
		वापस -ENOMEM;

	ep93xx_pwm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ep93xx_pwm->base))
		वापस PTR_ERR(ep93xx_pwm->base);

	ep93xx_pwm->clk = devm_clk_get(&pdev->dev, "pwm_clk");
	अगर (IS_ERR(ep93xx_pwm->clk))
		वापस PTR_ERR(ep93xx_pwm->clk);

	ep93xx_pwm->chip.dev = &pdev->dev;
	ep93xx_pwm->chip.ops = &ep93xx_pwm_ops;
	ep93xx_pwm->chip.npwm = 1;

	ret = pwmchip_add(&ep93xx_pwm->chip);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, ep93xx_pwm);
	वापस 0;
पूर्ण

अटल पूर्णांक ep93xx_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ep93xx_pwm *ep93xx_pwm = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&ep93xx_pwm->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver ep93xx_pwm_driver = अणु
	.driver = अणु
		.name = "ep93xx-pwm",
	पूर्ण,
	.probe = ep93xx_pwm_probe,
	.हटाओ = ep93xx_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(ep93xx_pwm_driver);

MODULE_DESCRIPTION("Cirrus Logic EP93xx PWM driver");
MODULE_AUTHOR("Matthieu Crapet <mcrapet@gmail.com>");
MODULE_AUTHOR("H Hartley Sweeten <hsweeten@visionengravers.com>");
MODULE_ALIAS("platform:ep93xx-pwm");
MODULE_LICENSE("GPL");
