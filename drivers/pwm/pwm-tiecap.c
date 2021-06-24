<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ECAP PWM driver
 *
 * Copyright (C) 2012 Texas Instruments, Inc. - https://www.ti.com/
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pwm.h>
#समावेश <linux/of_device.h>

/* ECAP रेजिस्टरs and bits definitions */
#घोषणा CAP1			0x08
#घोषणा CAP2			0x0C
#घोषणा CAP3			0x10
#घोषणा CAP4			0x14
#घोषणा ECCTL2			0x2A
#घोषणा ECCTL2_APWM_POL_LOW	BIT(10)
#घोषणा ECCTL2_APWM_MODE	BIT(9)
#घोषणा ECCTL2_SYNC_SEL_DISA	(BIT(7) | BIT(6))
#घोषणा ECCTL2_TSCTR_FREERUN	BIT(4)

काष्ठा ecap_context अणु
	u32 cap3;
	u32 cap4;
	u16 ecctl2;
पूर्ण;

काष्ठा ecap_pwm_chip अणु
	काष्ठा pwm_chip chip;
	अचिन्हित पूर्णांक clk_rate;
	व्योम __iomem *mmio_base;
	काष्ठा ecap_context ctx;
पूर्ण;

अटल अंतरभूत काष्ठा ecap_pwm_chip *to_ecap_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा ecap_pwm_chip, chip);
पूर्ण

/*
 * period_ns = 10^9 * period_cycles / PWM_CLK_RATE
 * duty_ns   = 10^9 * duty_cycles / PWM_CLK_RATE
 */
अटल पूर्णांक ecap_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
		पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u32 period_cycles, duty_cycles;
	अचिन्हित दीर्घ दीर्घ c;
	u16 value;

	अगर (period_ns > NSEC_PER_SEC)
		वापस -दुस्फल;

	c = pc->clk_rate;
	c = c * period_ns;
	करो_भाग(c, NSEC_PER_SEC);
	period_cycles = (u32)c;

	अगर (period_cycles < 1) अणु
		period_cycles = 1;
		duty_cycles = 1;
	पूर्ण अन्यथा अणु
		c = pc->clk_rate;
		c = c * duty_ns;
		करो_भाग(c, NSEC_PER_SEC);
		duty_cycles = (u32)c;
	पूर्ण

	pm_runसमय_get_sync(pc->chip.dev);

	value = पढ़ोw(pc->mmio_base + ECCTL2);

	/* Configure APWM mode & disable sync option */
	value |= ECCTL2_APWM_MODE | ECCTL2_SYNC_SEL_DISA;

	ग_लिखोw(value, pc->mmio_base + ECCTL2);

	अगर (!pwm_is_enabled(pwm)) अणु
		/* Update active रेजिस्टरs अगर not running */
		ग_लिखोl(duty_cycles, pc->mmio_base + CAP2);
		ग_लिखोl(period_cycles, pc->mmio_base + CAP1);
	पूर्ण अन्यथा अणु
		/*
		 * Update shaकरोw रेजिस्टरs to configure period and
		 * compare values. This helps current PWM period to
		 * complete on reconfiguring
		 */
		ग_लिखोl(duty_cycles, pc->mmio_base + CAP4);
		ग_लिखोl(period_cycles, pc->mmio_base + CAP3);
	पूर्ण

	अगर (!pwm_is_enabled(pwm)) अणु
		value = पढ़ोw(pc->mmio_base + ECCTL2);
		/* Disable APWM mode to put APWM output Low */
		value &= ~ECCTL2_APWM_MODE;
		ग_लिखोw(value, pc->mmio_base + ECCTL2);
	पूर्ण

	pm_runसमय_put_sync(pc->chip.dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ecap_pwm_set_polarity(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				 क्रमागत pwm_polarity polarity)
अणु
	काष्ठा ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 value;

	pm_runसमय_get_sync(pc->chip.dev);

	value = पढ़ोw(pc->mmio_base + ECCTL2);

	अगर (polarity == PWM_POLARITY_INVERSED)
		/* Duty cycle defines LOW period of PWM */
		value |= ECCTL2_APWM_POL_LOW;
	अन्यथा
		/* Duty cycle defines HIGH period of PWM */
		value &= ~ECCTL2_APWM_POL_LOW;

	ग_लिखोw(value, pc->mmio_base + ECCTL2);

	pm_runसमय_put_sync(pc->chip.dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ecap_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 value;

	/* Leave घड़ी enabled on enabling PWM */
	pm_runसमय_get_sync(pc->chip.dev);

	/*
	 * Enable 'Free run Time stamp counter mode' to start counter
	 * and  'APWM mode' to enable APWM output
	 */
	value = पढ़ोw(pc->mmio_base + ECCTL2);
	value |= ECCTL2_TSCTR_FREERUN | ECCTL2_APWM_MODE;
	ग_लिखोw(value, pc->mmio_base + ECCTL2);

	वापस 0;
पूर्ण

अटल व्योम ecap_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा ecap_pwm_chip *pc = to_ecap_pwm_chip(chip);
	u16 value;

	/*
	 * Disable 'Free run Time stamp counter mode' to stop counter
	 * and 'APWM mode' to put APWM output to low
	 */
	value = पढ़ोw(pc->mmio_base + ECCTL2);
	value &= ~(ECCTL2_TSCTR_FREERUN | ECCTL2_APWM_MODE);
	ग_लिखोw(value, pc->mmio_base + ECCTL2);

	/* Disable घड़ी on PWM disable */
	pm_runसमय_put_sync(pc->chip.dev);
पूर्ण

अटल व्योम ecap_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	अगर (pwm_is_enabled(pwm)) अणु
		dev_warn(chip->dev, "Removing PWM device without disabling\n");
		pm_runसमय_put_sync(chip->dev);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pwm_ops ecap_pwm_ops = अणु
	.मुक्त = ecap_pwm_मुक्त,
	.config = ecap_pwm_config,
	.set_polarity = ecap_pwm_set_polarity,
	.enable = ecap_pwm_enable,
	.disable = ecap_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ecap_of_match[] = अणु
	अणु .compatible	= "ti,am3352-ecap" पूर्ण,
	अणु .compatible	= "ti,am33xx-ecap" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ecap_of_match);

अटल पूर्णांक ecap_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ecap_pwm_chip *pc;
	काष्ठा clk *clk;
	पूर्णांक ret;

	pc = devm_kzalloc(&pdev->dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	clk = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(clk)) अणु
		अगर (of_device_is_compatible(np, "ti,am33xx-ecap")) अणु
			dev_warn(&pdev->dev, "Binding is obsolete.\n");
			clk = devm_clk_get(pdev->dev.parent, "fck");
		पूर्ण
	पूर्ण

	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	pc->clk_rate = clk_get_rate(clk);
	अगर (!pc->clk_rate) अणु
		dev_err(&pdev->dev, "failed to get clock rate\n");
		वापस -EINVAL;
	पूर्ण

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &ecap_pwm_ops;
	pc->chip.of_xlate = of_pwm_xlate_with_flags;
	pc->chip.of_pwm_n_cells = 3;
	pc->chip.npwm = 1;

	pc->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pc->mmio_base))
		वापस PTR_ERR(pc->mmio_base);

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pc);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ecap_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ecap_pwm_chip *pc = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);

	वापस pwmchip_हटाओ(&pc->chip);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम ecap_pwm_save_context(काष्ठा ecap_pwm_chip *pc)
अणु
	pm_runसमय_get_sync(pc->chip.dev);
	pc->ctx.ecctl2 = पढ़ोw(pc->mmio_base + ECCTL2);
	pc->ctx.cap4 = पढ़ोl(pc->mmio_base + CAP4);
	pc->ctx.cap3 = पढ़ोl(pc->mmio_base + CAP3);
	pm_runसमय_put_sync(pc->chip.dev);
पूर्ण

अटल व्योम ecap_pwm_restore_context(काष्ठा ecap_pwm_chip *pc)
अणु
	ग_लिखोl(pc->ctx.cap3, pc->mmio_base + CAP3);
	ग_लिखोl(pc->ctx.cap4, pc->mmio_base + CAP4);
	ग_लिखोw(pc->ctx.ecctl2, pc->mmio_base + ECCTL2);
पूर्ण

अटल पूर्णांक ecap_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ecap_pwm_chip *pc = dev_get_drvdata(dev);
	काष्ठा pwm_device *pwm = pc->chip.pwms;

	ecap_pwm_save_context(pc);

	/* Disable explicitly अगर PWM is running */
	अगर (pwm_is_enabled(pwm))
		pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ecap_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा ecap_pwm_chip *pc = dev_get_drvdata(dev);
	काष्ठा pwm_device *pwm = pc->chip.pwms;

	/* Enable explicitly अगर PWM was running */
	अगर (pwm_is_enabled(pwm))
		pm_runसमय_get_sync(dev);

	ecap_pwm_restore_context(pc);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ecap_pwm_pm_ops, ecap_pwm_suspend, ecap_pwm_resume);

अटल काष्ठा platक्रमm_driver ecap_pwm_driver = अणु
	.driver = अणु
		.name = "ecap",
		.of_match_table = ecap_of_match,
		.pm = &ecap_pwm_pm_ops,
	पूर्ण,
	.probe = ecap_pwm_probe,
	.हटाओ = ecap_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(ecap_pwm_driver);

MODULE_DESCRIPTION("ECAP PWM driver");
MODULE_AUTHOR("Texas Instruments");
MODULE_LICENSE("GPL");
