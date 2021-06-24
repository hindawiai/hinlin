<शैली गुरु>
/*
 * ST Microelectronics SPEAr Pulse Width Modulator driver
 *
 * Copyright (C) 2012 ST Microelectronics
 * Shiraz Hashim <shiraz.linux.kernel@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#घोषणा NUM_PWM		4

/* PWM रेजिस्टरs and bits definitions */
#घोषणा PWMCR			0x00	/* Control Register */
#घोषणा PWMCR_PWM_ENABLE	0x1
#घोषणा PWMCR_PRESCALE_SHIFT	2
#घोषणा PWMCR_MIN_PRESCALE	0x00
#घोषणा PWMCR_MAX_PRESCALE	0x3FFF

#घोषणा PWMDCR			0x04	/* Duty Cycle Register */
#घोषणा PWMDCR_MIN_DUTY		0x0001
#घोषणा PWMDCR_MAX_DUTY		0xFFFF

#घोषणा PWMPCR			0x08	/* Period Register */
#घोषणा PWMPCR_MIN_PERIOD	0x0001
#घोषणा PWMPCR_MAX_PERIOD	0xFFFF

/* Following only available on 13xx SoCs */
#घोषणा PWMMCR			0x3C	/* Master Control Register */
#घोषणा PWMMCR_PWM_ENABLE	0x1

/**
 * काष्ठा spear_pwm_chip - काष्ठा representing pwm chip
 *
 * @mmio_base: base address of pwm chip
 * @clk: poपूर्णांकer to clk काष्ठाure of pwm chip
 * @chip: linux pwm chip representation
 */
काष्ठा spear_pwm_chip अणु
	व्योम __iomem *mmio_base;
	काष्ठा clk *clk;
	काष्ठा pwm_chip chip;
पूर्ण;

अटल अंतरभूत काष्ठा spear_pwm_chip *to_spear_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा spear_pwm_chip, chip);
पूर्ण

अटल अंतरभूत u32 spear_pwm_पढ़ोl(काष्ठा spear_pwm_chip *chip, अचिन्हित पूर्णांक num,
				  अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl_relaxed(chip->mmio_base + (num << 4) + offset);
पूर्ण

अटल अंतरभूत व्योम spear_pwm_ग_लिखोl(काष्ठा spear_pwm_chip *chip,
				    अचिन्हित पूर्णांक num, अचिन्हित दीर्घ offset,
				    अचिन्हित दीर्घ val)
अणु
	ग_लिखोl_relaxed(val, chip->mmio_base + (num << 4) + offset);
पूर्ण

अटल पूर्णांक spear_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			    पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा spear_pwm_chip *pc = to_spear_pwm_chip(chip);
	u64 val, भाग, clk_rate;
	अचिन्हित दीर्घ prescale = PWMCR_MIN_PRESCALE, pv, dc;
	पूर्णांक ret;

	/*
	 * Find pv, dc and prescale to suit duty_ns and period_ns. This is करोne
	 * according to क्रमmulas described below:
	 *
	 * period_ns = 10^9 * (PRESCALE + 1) * PV / PWM_CLK_RATE
	 * duty_ns = 10^9 * (PRESCALE + 1) * DC / PWM_CLK_RATE
	 *
	 * PV = (PWM_CLK_RATE * period_ns) / (10^9 * (PRESCALE + 1))
	 * DC = (PWM_CLK_RATE * duty_ns) / (10^9 * (PRESCALE + 1))
	 */
	clk_rate = clk_get_rate(pc->clk);
	जबतक (1) अणु
		भाग = 1000000000;
		भाग *= 1 + prescale;
		val = clk_rate * period_ns;
		pv = भाग64_u64(val, भाग);
		val = clk_rate * duty_ns;
		dc = भाग64_u64(val, भाग);

		/* अगर duty_ns and period_ns are not achievable then वापस */
		अगर (pv < PWMPCR_MIN_PERIOD || dc < PWMDCR_MIN_DUTY)
			वापस -EINVAL;

		/*
		 * अगर pv and dc have crossed their upper limit, then increase
		 * prescale and recalculate pv and dc.
		 */
		अगर (pv > PWMPCR_MAX_PERIOD || dc > PWMDCR_MAX_DUTY) अणु
			अगर (++prescale > PWMCR_MAX_PRESCALE)
				वापस -EINVAL;
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	/*
	 * NOTE: the घड़ी to PWM has to be enabled first beक्रमe writing to the
	 * रेजिस्टरs.
	 */
	ret = clk_enable(pc->clk);
	अगर (ret)
		वापस ret;

	spear_pwm_ग_लिखोl(pc, pwm->hwpwm, PWMCR,
			prescale << PWMCR_PRESCALE_SHIFT);
	spear_pwm_ग_लिखोl(pc, pwm->hwpwm, PWMDCR, dc);
	spear_pwm_ग_लिखोl(pc, pwm->hwpwm, PWMPCR, pv);
	clk_disable(pc->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक spear_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा spear_pwm_chip *pc = to_spear_pwm_chip(chip);
	पूर्णांक rc = 0;
	u32 val;

	rc = clk_enable(pc->clk);
	अगर (rc)
		वापस rc;

	val = spear_pwm_पढ़ोl(pc, pwm->hwpwm, PWMCR);
	val |= PWMCR_PWM_ENABLE;
	spear_pwm_ग_लिखोl(pc, pwm->hwpwm, PWMCR, val);

	वापस 0;
पूर्ण

अटल व्योम spear_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा spear_pwm_chip *pc = to_spear_pwm_chip(chip);
	u32 val;

	val = spear_pwm_पढ़ोl(pc, pwm->hwpwm, PWMCR);
	val &= ~PWMCR_PWM_ENABLE;
	spear_pwm_ग_लिखोl(pc, pwm->hwpwm, PWMCR, val);

	clk_disable(pc->clk);
पूर्ण

अटल स्थिर काष्ठा pwm_ops spear_pwm_ops = अणु
	.config = spear_pwm_config,
	.enable = spear_pwm_enable,
	.disable = spear_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक spear_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spear_pwm_chip *pc;
	पूर्णांक ret;
	u32 val;

	pc = devm_kzalloc(&pdev->dev, माप(*pc), GFP_KERNEL);
	अगर (!pc)
		वापस -ENOMEM;

	pc->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pc->mmio_base))
		वापस PTR_ERR(pc->mmio_base);

	pc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pc->clk))
		वापस PTR_ERR(pc->clk);

	platक्रमm_set_drvdata(pdev, pc);

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &spear_pwm_ops;
	pc->chip.npwm = NUM_PWM;

	ret = clk_prepare(pc->clk);
	अगर (ret)
		वापस ret;

	अगर (of_device_is_compatible(np, "st,spear1340-pwm")) अणु
		ret = clk_enable(pc->clk);
		अगर (ret) अणु
			clk_unprepare(pc->clk);
			वापस ret;
		पूर्ण
		/*
		 * Following enables PWM chip, channels would still be
		 * enabled inभागidually through their control रेजिस्टर
		 */
		val = पढ़ोl_relaxed(pc->mmio_base + PWMMCR);
		val |= PWMMCR_PWM_ENABLE;
		ग_लिखोl_relaxed(val, pc->mmio_base + PWMMCR);

		clk_disable(pc->clk);
	पूर्ण

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0) अणु
		clk_unprepare(pc->clk);
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक spear_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spear_pwm_chip *pc = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < NUM_PWM; i++)
		pwm_disable(&pc->chip.pwms[i]);

	/* clk was prepared in probe, hence unprepare it here */
	clk_unprepare(pc->clk);
	वापस pwmchip_हटाओ(&pc->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id spear_pwm_of_match[] = अणु
	अणु .compatible = "st,spear320-pwm" पूर्ण,
	अणु .compatible = "st,spear1340-pwm" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, spear_pwm_of_match);

अटल काष्ठा platक्रमm_driver spear_pwm_driver = अणु
	.driver = अणु
		.name = "spear-pwm",
		.of_match_table = spear_pwm_of_match,
	पूर्ण,
	.probe = spear_pwm_probe,
	.हटाओ = spear_pwm_हटाओ,
पूर्ण;

module_platक्रमm_driver(spear_pwm_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shiraz Hashim <shiraz.linux.kernel@gmail.com>");
MODULE_AUTHOR("Viresh Kumar <viresh.kumar@linaro.com>");
MODULE_ALIAS("platform:spear-pwm");
