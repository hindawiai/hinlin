<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2012 Alexandre Pereira da Silva <aletes.xgr@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

काष्ठा lpc32xx_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *clk;
	व्योम __iomem *base;
पूर्ण;

#घोषणा PWM_ENABLE	BIT(31)
#घोषणा PWM_PIN_LEVEL	BIT(30)

#घोषणा to_lpc32xx_pwm_chip(_chip) \
	container_of(_chip, काष्ठा lpc32xx_pwm_chip, chip)

अटल पूर्णांक lpc32xx_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा lpc32xx_pwm_chip *lpc32xx = to_lpc32xx_pwm_chip(chip);
	अचिन्हित दीर्घ दीर्घ c;
	पूर्णांक period_cycles, duty_cycles;
	u32 val;
	c = clk_get_rate(lpc32xx->clk);

	/* The highest acceptable भागisor is 256, which is represented by 0 */
	period_cycles = भाग64_u64(c * period_ns,
			       (अचिन्हित दीर्घ दीर्घ)NSEC_PER_SEC * 256);
	अगर (!period_cycles || period_cycles > 256)
		वापस -दुस्फल;
	अगर (period_cycles == 256)
		period_cycles = 0;

	/* Compute 256 x #duty/period value and care क्रम corner हालs */
	duty_cycles = भाग64_u64((अचिन्हित दीर्घ दीर्घ)(period_ns - duty_ns) * 256,
				period_ns);
	अगर (!duty_cycles)
		duty_cycles = 1;
	अगर (duty_cycles > 255)
		duty_cycles = 255;

	val = पढ़ोl(lpc32xx->base + (pwm->hwpwm << 2));
	val &= ~0xFFFF;
	val |= (period_cycles << 8) | duty_cycles;
	ग_लिखोl(val, lpc32xx->base + (pwm->hwpwm << 2));

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lpc32xx_pwm_chip *lpc32xx = to_lpc32xx_pwm_chip(chip);
	u32 val;
	पूर्णांक ret;

	ret = clk_prepare_enable(lpc32xx->clk);
	अगर (ret)
		वापस ret;

	val = पढ़ोl(lpc32xx->base + (pwm->hwpwm << 2));
	val |= PWM_ENABLE;
	ग_लिखोl(val, lpc32xx->base + (pwm->hwpwm << 2));

	वापस 0;
पूर्ण

अटल व्योम lpc32xx_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lpc32xx_pwm_chip *lpc32xx = to_lpc32xx_pwm_chip(chip);
	u32 val;

	val = पढ़ोl(lpc32xx->base + (pwm->hwpwm << 2));
	val &= ~PWM_ENABLE;
	ग_लिखोl(val, lpc32xx->base + (pwm->hwpwm << 2));

	clk_disable_unprepare(lpc32xx->clk);
पूर्ण

अटल स्थिर काष्ठा pwm_ops lpc32xx_pwm_ops = अणु
	.config = lpc32xx_pwm_config,
	.enable = lpc32xx_pwm_enable,
	.disable = lpc32xx_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक lpc32xx_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_pwm_chip *lpc32xx;
	पूर्णांक ret;
	u32 val;

	lpc32xx = devm_kzalloc(&pdev->dev, माप(*lpc32xx), GFP_KERNEL);
	अगर (!lpc32xx)
		वापस -ENOMEM;

	lpc32xx->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(lpc32xx->base))
		वापस PTR_ERR(lpc32xx->base);

	lpc32xx->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(lpc32xx->clk))
		वापस PTR_ERR(lpc32xx->clk);

	lpc32xx->chip.dev = &pdev->dev;
	lpc32xx->chip.ops = &lpc32xx_pwm_ops;
	lpc32xx->chip.npwm = 1;

	ret = pwmchip_add(&lpc32xx->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add PWM chip, error %d\n", ret);
		वापस ret;
	पूर्ण

	/* When PWM is disable, configure the output to the शेष value */
	val = पढ़ोl(lpc32xx->base + (lpc32xx->chip.pwms[0].hwpwm << 2));
	val &= ~PWM_PIN_LEVEL;
	ग_लिखोl(val, lpc32xx->base + (lpc32xx->chip.pwms[0].hwpwm << 2));

	platक्रमm_set_drvdata(pdev, lpc32xx);

	वापस 0;
पूर्ण

अटल पूर्णांक lpc32xx_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lpc32xx_pwm_chip *lpc32xx = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&lpc32xx->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id lpc32xx_pwm_dt_ids[] = अणु
	अणु .compatible = "nxp,lpc3220-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lpc32xx_pwm_dt_ids);

अटल काष्ठा platक्रमm_driver lpc32xx_pwm_driver = अणु
	.driver = अणु
		.name = "lpc32xx-pwm",
		.of_match_table = lpc32xx_pwm_dt_ids,
	पूर्ण,
	.probe = lpc32xx_pwm_probe,
	.हटाओ = lpc32xx_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(lpc32xx_pwm_driver);

MODULE_ALIAS("platform:lpc32xx-pwm");
MODULE_AUTHOR("Alexandre Pereira da Silva <aletes.xgr@gmail.com>");
MODULE_DESCRIPTION("LPC32XX PWM Driver");
MODULE_LICENSE("GPL v2");
