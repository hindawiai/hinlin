<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom BCM7038 PWM driver
 * Author: Florian Fainelli
 *
 * Copyright (C) 2015 Broadcom Corporation
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/clk.h>
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/spinlock.h>

#घोषणा PWM_CTRL		0x00
#घोषणा  CTRL_START		BIT(0)
#घोषणा  CTRL_OEB		BIT(1)
#घोषणा  CTRL_FORCE_HIGH	BIT(2)
#घोषणा  CTRL_OPENDRAIN		BIT(3)
#घोषणा  CTRL_CHAN_OFFS		4

#घोषणा PWM_CTRL2		0x04
#घोषणा  CTRL2_OUT_SELECT	BIT(0)

#घोषणा PWM_CH_SIZE		0x8

#घोषणा PWM_CWORD_MSB(ch)	(0x08 + ((ch) * PWM_CH_SIZE))
#घोषणा PWM_CWORD_LSB(ch)	(0x0c + ((ch) * PWM_CH_SIZE))

/* Number of bits क्रम the CWORD value */
#घोषणा CWORD_BIT_SIZE		16

/*
 * Maximum control word value allowed when variable-frequency PWM is used as a
 * घड़ी क्रम the स्थिरant-frequency PMW.
 */
#घोषणा CONST_VAR_F_MAX		32768
#घोषणा CONST_VAR_F_MIN		1

#घोषणा PWM_ON(ch)		(0x18 + ((ch) * PWM_CH_SIZE))
#घोषणा  PWM_ON_MIN		1
#घोषणा PWM_PERIOD(ch)		(0x1c + ((ch) * PWM_CH_SIZE))
#घोषणा  PWM_PERIOD_MIN		0

#घोषणा PWM_ON_PERIOD_MAX	0xff

काष्ठा brcmstb_pwm अणु
	व्योम __iomem *base;
	spinlock_t lock;
	काष्ठा clk *clk;
	काष्ठा pwm_chip chip;
पूर्ण;

अटल अंतरभूत u32 brcmstb_pwm_पढ़ोl(काष्ठा brcmstb_pwm *p,
				    अचिन्हित पूर्णांक offset)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		वापस __raw_पढ़ोl(p->base + offset);
	अन्यथा
		वापस पढ़ोl_relaxed(p->base + offset);
पूर्ण

अटल अंतरभूत व्योम brcmstb_pwm_ग_लिखोl(काष्ठा brcmstb_pwm *p, u32 value,
				      अचिन्हित पूर्णांक offset)
अणु
	अगर (IS_ENABLED(CONFIG_MIPS) && IS_ENABLED(CONFIG_CPU_BIG_ENDIAN))
		__raw_ग_लिखोl(value, p->base + offset);
	अन्यथा
		ग_लिखोl_relaxed(value, p->base + offset);
पूर्ण

अटल अंतरभूत काष्ठा brcmstb_pwm *to_brcmstb_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा brcmstb_pwm, chip);
पूर्ण

/*
 * Fv is derived from the variable frequency output. The variable frequency
 * output is configured using this क्रमmula:
 *
 * W = cword, अगर cword < 2 ^ 15 अन्यथा 16-bit 2's complement of cword
 *
 * Fv = W x 2 ^ -16 x 27Mhz (reference घड़ी)
 *
 * The period is: (period + 1) / Fv and "on" समय is on / (period + 1)
 *
 * The PWM core framework specअगरies that the "duty_ns" parameter is in fact the
 * "on" समय, so this translates directly पूर्णांकo our HW programming here.
 */
अटल पूर्णांक brcmstb_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा brcmstb_pwm *p = to_brcmstb_pwm(chip);
	अचिन्हित दीर्घ pc, dc, cword = CONST_VAR_F_MAX;
	अचिन्हित पूर्णांक channel = pwm->hwpwm;
	u32 value;

	/*
	 * If asking क्रम a duty_ns equal to period_ns, we need to substract
	 * the period value by 1 to make it लघुer than the "on" समय and
	 * produce a flat 100% duty cycle संकेत, and max out the "on" समय
	 */
	अगर (duty_ns == period_ns) अणु
		dc = PWM_ON_PERIOD_MAX;
		pc = PWM_ON_PERIOD_MAX - 1;
		जाओ करोne;
	पूर्ण

	जबतक (1) अणु
		u64 rate, पंचांगp;

		/*
		 * Calculate the base rate from base frequency and current
		 * cword
		 */
		rate = (u64)clk_get_rate(p->clk) * (u64)cword;
		करो_भाग(rate, 1 << CWORD_BIT_SIZE);

		पंचांगp = period_ns * rate;
		करो_भाग(पंचांगp, NSEC_PER_SEC);
		pc = पंचांगp;

		पंचांगp = (duty_ns + 1) * rate;
		करो_भाग(पंचांगp, NSEC_PER_SEC);
		dc = पंचांगp;

		/*
		 * We can be called with separate duty and period updates,
		 * so करो not reject dc == 0 right away
		 */
		अगर (pc == PWM_PERIOD_MIN || (dc < PWM_ON_MIN && duty_ns))
			वापस -EINVAL;

		/* We converged on a calculation */
		अगर (pc <= PWM_ON_PERIOD_MAX && dc <= PWM_ON_PERIOD_MAX)
			अवरोध;

		/*
		 * The cword needs to be a घातer of 2 क्रम the variable
		 * frequency generator to output a 50% duty cycle variable
		 * frequency which is used as input घड़ी to the fixed
		 * frequency generator.
		 */
		cword >>= 1;

		/*
		 * Desired periods are too large, we करो not have a भागider
		 * क्रम them
		 */
		अगर (cword < CONST_VAR_F_MIN)
			वापस -EINVAL;
	पूर्ण

करोne:
	/*
	 * Configure the defined "cword" value to have the variable frequency
	 * generator output a base frequency क्रम the स्थिरant frequency
	 * generator to derive from.
	 */
	spin_lock(&p->lock);
	brcmstb_pwm_ग_लिखोl(p, cword >> 8, PWM_CWORD_MSB(channel));
	brcmstb_pwm_ग_लिखोl(p, cword & 0xff, PWM_CWORD_LSB(channel));

	/* Select स्थिरant frequency संकेत output */
	value = brcmstb_pwm_पढ़ोl(p, PWM_CTRL2);
	value |= CTRL2_OUT_SELECT << (channel * CTRL_CHAN_OFFS);
	brcmstb_pwm_ग_लिखोl(p, value, PWM_CTRL2);

	/* Configure on and period value */
	brcmstb_pwm_ग_लिखोl(p, pc, PWM_PERIOD(channel));
	brcmstb_pwm_ग_लिखोl(p, dc, PWM_ON(channel));
	spin_unlock(&p->lock);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम brcmstb_pwm_enable_set(काष्ठा brcmstb_pwm *p,
					  अचिन्हित पूर्णांक channel, bool enable)
अणु
	अचिन्हित पूर्णांक shअगरt = channel * CTRL_CHAN_OFFS;
	u32 value;

	spin_lock(&p->lock);
	value = brcmstb_pwm_पढ़ोl(p, PWM_CTRL);

	अगर (enable) अणु
		value &= ~(CTRL_OEB << shअगरt);
		value |= (CTRL_START | CTRL_OPENDRAIN) << shअगरt;
	पूर्ण अन्यथा अणु
		value &= ~((CTRL_START | CTRL_OPENDRAIN) << shअगरt);
		value |= CTRL_OEB << shअगरt;
	पूर्ण

	brcmstb_pwm_ग_लिखोl(p, value, PWM_CTRL);
	spin_unlock(&p->lock);
पूर्ण

अटल पूर्णांक brcmstb_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा brcmstb_pwm *p = to_brcmstb_pwm(chip);

	brcmstb_pwm_enable_set(p, pwm->hwpwm, true);

	वापस 0;
पूर्ण

अटल व्योम brcmstb_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा brcmstb_pwm *p = to_brcmstb_pwm(chip);

	brcmstb_pwm_enable_set(p, pwm->hwpwm, false);
पूर्ण

अटल स्थिर काष्ठा pwm_ops brcmstb_pwm_ops = अणु
	.config = brcmstb_pwm_config,
	.enable = brcmstb_pwm_enable,
	.disable = brcmstb_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id brcmstb_pwm_of_match[] = अणु
	अणु .compatible = "brcm,bcm7038-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, brcmstb_pwm_of_match);

अटल पूर्णांक brcmstb_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmstb_pwm *p;
	पूर्णांक ret;

	p = devm_kzalloc(&pdev->dev, माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	spin_lock_init(&p->lock);

	p->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(p->clk)) अणु
		dev_err(&pdev->dev, "failed to obtain clock\n");
		वापस PTR_ERR(p->clk);
	पूर्ण

	ret = clk_prepare_enable(p->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, p);

	p->chip.dev = &pdev->dev;
	p->chip.ops = &brcmstb_pwm_ops;
	p->chip.npwm = 2;

	p->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(p->base)) अणु
		ret = PTR_ERR(p->base);
		जाओ out_clk;
	पूर्ण

	ret = pwmchip_add(&p->chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);
		जाओ out_clk;
	पूर्ण

	वापस 0;

out_clk:
	clk_disable_unprepare(p->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक brcmstb_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmstb_pwm *p = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&p->chip);
	clk_disable_unprepare(p->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक brcmstb_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_pwm *p = dev_get_drvdata(dev);

	clk_disable(p->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_pwm *p = dev_get_drvdata(dev);

	clk_enable(p->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(brcmstb_pwm_pm_ops, brcmstb_pwm_suspend,
			 brcmstb_pwm_resume);

अटल काष्ठा platक्रमm_driver brcmstb_pwm_driver = अणु
	.probe = brcmstb_pwm_probe,
	.हटाओ = brcmstb_pwm_हटाओ,
	.driver = अणु
		.name = "pwm-brcmstb",
		.of_match_table = brcmstb_pwm_of_match,
		.pm = &brcmstb_pwm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(brcmstb_pwm_driver);

MODULE_AUTHOR("Florian Fainelli <f.fainelli@gmail.com>");
MODULE_DESCRIPTION("Broadcom STB PWM driver");
MODULE_ALIAS("platform:pwm-brcmstb");
MODULE_LICENSE("GPL");
