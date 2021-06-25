<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * EHRPWM PWM driver
 *
 * Copyright (C) 2012 Texas Instruments, Inc. - https://www.ti.com/
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of_device.h>

/* EHRPWM रेजिस्टरs and bits definitions */

/* Time base module रेजिस्टरs */
#घोषणा TBCTL			0x00
#घोषणा TBPRD			0x0A

#घोषणा TBCTL_PRDLD_MASK	BIT(3)
#घोषणा TBCTL_PRDLD_SHDW	0
#घोषणा TBCTL_PRDLD_IMDT	BIT(3)
#घोषणा TBCTL_CLKDIV_MASK	(BIT(12) | BIT(11) | BIT(10) | BIT(9) | \
				BIT(8) | BIT(7))
#घोषणा TBCTL_CTRMODE_MASK	(BIT(1) | BIT(0))
#घोषणा TBCTL_CTRMODE_UP	0
#घोषणा TBCTL_CTRMODE_DOWN	BIT(0)
#घोषणा TBCTL_CTRMODE_UPDOWN	BIT(1)
#घोषणा TBCTL_CTRMODE_FREEZE	(BIT(1) | BIT(0))

#घोषणा TBCTL_HSPCLKDIV_SHIFT	7
#घोषणा TBCTL_CLKDIV_SHIFT	10

#घोषणा CLKDIV_MAX		7
#घोषणा HSPCLKDIV_MAX		7
#घोषणा PERIOD_MAX		0xFFFF

/* compare module रेजिस्टरs */
#घोषणा CMPA			0x12
#घोषणा CMPB			0x14

/* Action qualअगरier module रेजिस्टरs */
#घोषणा AQCTLA			0x16
#घोषणा AQCTLB			0x18
#घोषणा AQSFRC			0x1A
#घोषणा AQCSFRC			0x1C

#घोषणा AQCTL_CBU_MASK		(BIT(9) | BIT(8))
#घोषणा AQCTL_CBU_FRCLOW	BIT(8)
#घोषणा AQCTL_CBU_FRCHIGH	BIT(9)
#घोषणा AQCTL_CBU_FRCTOGGLE	(BIT(9) | BIT(8))
#घोषणा AQCTL_CAU_MASK		(BIT(5) | BIT(4))
#घोषणा AQCTL_CAU_FRCLOW	BIT(4)
#घोषणा AQCTL_CAU_FRCHIGH	BIT(5)
#घोषणा AQCTL_CAU_FRCTOGGLE	(BIT(5) | BIT(4))
#घोषणा AQCTL_PRD_MASK		(BIT(3) | BIT(2))
#घोषणा AQCTL_PRD_FRCLOW	BIT(2)
#घोषणा AQCTL_PRD_FRCHIGH	BIT(3)
#घोषणा AQCTL_PRD_FRCTOGGLE	(BIT(3) | BIT(2))
#घोषणा AQCTL_ZRO_MASK		(BIT(1) | BIT(0))
#घोषणा AQCTL_ZRO_FRCLOW	BIT(0)
#घोषणा AQCTL_ZRO_FRCHIGH	BIT(1)
#घोषणा AQCTL_ZRO_FRCTOGGLE	(BIT(1) | BIT(0))

#घोषणा AQCTL_CHANA_POLNORMAL	(AQCTL_CAU_FRCLOW | AQCTL_PRD_FRCHIGH | \
				AQCTL_ZRO_FRCHIGH)
#घोषणा AQCTL_CHANA_POLINVERSED	(AQCTL_CAU_FRCHIGH | AQCTL_PRD_FRCLOW | \
				AQCTL_ZRO_FRCLOW)
#घोषणा AQCTL_CHANB_POLNORMAL	(AQCTL_CBU_FRCLOW | AQCTL_PRD_FRCHIGH | \
				AQCTL_ZRO_FRCHIGH)
#घोषणा AQCTL_CHANB_POLINVERSED	(AQCTL_CBU_FRCHIGH | AQCTL_PRD_FRCLOW | \
				AQCTL_ZRO_FRCLOW)

#घोषणा AQSFRC_RLDCSF_MASK	(BIT(7) | BIT(6))
#घोषणा AQSFRC_RLDCSF_ZRO	0
#घोषणा AQSFRC_RLDCSF_PRD	BIT(6)
#घोषणा AQSFRC_RLDCSF_ZROPRD	BIT(7)
#घोषणा AQSFRC_RLDCSF_IMDT	(BIT(7) | BIT(6))

#घोषणा AQCSFRC_CSFB_MASK	(BIT(3) | BIT(2))
#घोषणा AQCSFRC_CSFB_FRCDIS	0
#घोषणा AQCSFRC_CSFB_FRCLOW	BIT(2)
#घोषणा AQCSFRC_CSFB_FRCHIGH	BIT(3)
#घोषणा AQCSFRC_CSFB_DISSWFRC	(BIT(3) | BIT(2))
#घोषणा AQCSFRC_CSFA_MASK	(BIT(1) | BIT(0))
#घोषणा AQCSFRC_CSFA_FRCDIS	0
#घोषणा AQCSFRC_CSFA_FRCLOW	BIT(0)
#घोषणा AQCSFRC_CSFA_FRCHIGH	BIT(1)
#घोषणा AQCSFRC_CSFA_DISSWFRC	(BIT(1) | BIT(0))

#घोषणा NUM_PWM_CHANNEL		2	/* EHRPWM channels */

काष्ठा ehrpwm_context अणु
	u16 tbctl;
	u16 tbprd;
	u16 cmpa;
	u16 cmpb;
	u16 aqctla;
	u16 aqctlb;
	u16 aqsfrc;
	u16 aqcsfrc;
पूर्ण;

काष्ठा ehrpwm_pwm_chip अणु
	काष्ठा pwm_chip chip;
	अचिन्हित दीर्घ clk_rate;
	व्योम __iomem *mmio_base;
	अचिन्हित दीर्घ period_cycles[NUM_PWM_CHANNEL];
	क्रमागत pwm_polarity polarity[NUM_PWM_CHANNEL];
	काष्ठा clk *tbclk;
	काष्ठा ehrpwm_context ctx;
पूर्ण;

अटल अंतरभूत काष्ठा ehrpwm_pwm_chip *to_ehrpwm_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा ehrpwm_pwm_chip, chip);
पूर्ण

अटल अंतरभूत u16 ehrpwm_पढ़ो(व्योम __iomem *base, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोw(base + offset);
पूर्ण

अटल अंतरभूत व्योम ehrpwm_ग_लिखो(व्योम __iomem *base, अचिन्हित पूर्णांक offset,
				u16 value)
अणु
	ग_लिखोw(value, base + offset);
पूर्ण

अटल व्योम ehrpwm_modअगरy(व्योम __iomem *base, अचिन्हित पूर्णांक offset, u16 mask,
			  u16 value)
अणु
	अचिन्हित लघु val;

	val = पढ़ोw(base + offset);
	val &= ~mask;
	val |= value & mask;
	ग_लिखोw(val, base + offset);
पूर्ण

/**
 * set_prescale_भाग -	Set up the prescaler भागider function
 * @rqst_prescaler:	prescaler value min
 * @prescale_भाग:	prescaler value set
 * @tb_clk_भाग:		Time Base Control prescaler bits
 */
अटल पूर्णांक set_prescale_भाग(अचिन्हित दीर्घ rqst_prescaler, u16 *prescale_भाग,
			    u16 *tb_clk_भाग)
अणु
	अचिन्हित पूर्णांक clkभाग, hspclkभाग;

	क्रम (clkभाग = 0; clkभाग <= CLKDIV_MAX; clkभाग++) अणु
		क्रम (hspclkभाग = 0; hspclkभाग <= HSPCLKDIV_MAX; hspclkभाग++) अणु
			/*
			 * calculations क्रम prescaler value :
			 * prescale_भाग = HSPCLKDIVIDER * CLKDIVIDER.
			 * HSPCLKDIVIDER =  2 ** hspclkभाग
			 * CLKDIVIDER = (1),		अगर clkभाग == 0 *OR*
			 *		(2 * clkभाग),	अगर clkभाग != 0
			 *
			 * Configure prescale_भाग value such that period
			 * रेजिस्टर value is less than 65535.
			 */

			*prescale_भाग = (1 << clkभाग) *
					(hspclkभाग ? (hspclkभाग * 2) : 1);
			अगर (*prescale_भाग > rqst_prescaler) अणु
				*tb_clk_भाग = (clkभाग << TBCTL_CLKDIV_SHIFT) |
					(hspclkभाग << TBCTL_HSPCLKDIV_SHIFT);
				वापस 0;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम configure_polarity(काष्ठा ehrpwm_pwm_chip *pc, पूर्णांक chan)
अणु
	u16 aqctl_val, aqctl_mask;
	अचिन्हित पूर्णांक aqctl_reg;

	/*
	 * Configure PWM output to HIGH/LOW level on counter
	 * reaches compare रेजिस्टर value and LOW/HIGH level
	 * on counter value reaches period रेजिस्टर value and
	 * zero value on counter
	 */
	अगर (chan == 1) अणु
		aqctl_reg = AQCTLB;
		aqctl_mask = AQCTL_CBU_MASK;

		अगर (pc->polarity[chan] == PWM_POLARITY_INVERSED)
			aqctl_val = AQCTL_CHANB_POLINVERSED;
		अन्यथा
			aqctl_val = AQCTL_CHANB_POLNORMAL;
	पूर्ण अन्यथा अणु
		aqctl_reg = AQCTLA;
		aqctl_mask = AQCTL_CAU_MASK;

		अगर (pc->polarity[chan] == PWM_POLARITY_INVERSED)
			aqctl_val = AQCTL_CHANA_POLINVERSED;
		अन्यथा
			aqctl_val = AQCTL_CHANA_POLNORMAL;
	पूर्ण

	aqctl_mask |= AQCTL_PRD_MASK | AQCTL_ZRO_MASK;
	ehrpwm_modअगरy(pc->mmio_base, aqctl_reg, aqctl_mask, aqctl_val);
पूर्ण

/*
 * period_ns = 10^9 * (ps_भागval * period_cycles) / PWM_CLK_RATE
 * duty_ns   = 10^9 * (ps_भागval * duty_cycles) / PWM_CLK_RATE
 */
अटल पूर्णांक ehrpwm_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);
	u32 period_cycles, duty_cycles;
	u16 ps_भागval, tb_भागval;
	अचिन्हित पूर्णांक i, cmp_reg;
	अचिन्हित दीर्घ दीर्घ c;

	अगर (period_ns > NSEC_PER_SEC)
		वापस -दुस्फल;

	c = pc->clk_rate;
	c = c * period_ns;
	करो_भाग(c, NSEC_PER_SEC);
	period_cycles = (अचिन्हित दीर्घ)c;

	अगर (period_cycles < 1) अणु
		period_cycles = 1;
		duty_cycles = 1;
	पूर्ण अन्यथा अणु
		c = pc->clk_rate;
		c = c * duty_ns;
		करो_भाग(c, NSEC_PER_SEC);
		duty_cycles = (अचिन्हित दीर्घ)c;
	पूर्ण

	/*
	 * Period values should be same क्रम multiple PWM channels as IP uses
	 * same period रेजिस्टर क्रम multiple channels.
	 */
	क्रम (i = 0; i < NUM_PWM_CHANNEL; i++) अणु
		अगर (pc->period_cycles[i] &&
				(pc->period_cycles[i] != period_cycles)) अणु
			/*
			 * Allow channel to reconfigure period अगर no other
			 * channels being configured.
			 */
			अगर (i == pwm->hwpwm)
				जारी;

			dev_err(chip->dev,
				"period value conflicts with channel %u\n",
				i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pc->period_cycles[pwm->hwpwm] = period_cycles;

	/* Configure घड़ी prescaler to support Low frequency PWM wave */
	अगर (set_prescale_भाग(period_cycles/PERIOD_MAX, &ps_भागval,
			     &tb_भागval)) अणु
		dev_err(chip->dev, "Unsupported values\n");
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_get_sync(chip->dev);

	/* Update घड़ी prescaler values */
	ehrpwm_modअगरy(pc->mmio_base, TBCTL, TBCTL_CLKDIV_MASK, tb_भागval);

	/* Update period & duty cycle with presacler भागision */
	period_cycles = period_cycles / ps_भागval;
	duty_cycles = duty_cycles / ps_भागval;

	/* Configure shaकरोw loading on Period रेजिस्टर */
	ehrpwm_modअगरy(pc->mmio_base, TBCTL, TBCTL_PRDLD_MASK, TBCTL_PRDLD_SHDW);

	ehrpwm_ग_लिखो(pc->mmio_base, TBPRD, period_cycles);

	/* Configure ehrpwm counter क्रम up-count mode */
	ehrpwm_modअगरy(pc->mmio_base, TBCTL, TBCTL_CTRMODE_MASK,
		      TBCTL_CTRMODE_UP);

	अगर (pwm->hwpwm == 1)
		/* Channel 1 configured with compare B रेजिस्टर */
		cmp_reg = CMPB;
	अन्यथा
		/* Channel 0 configured with compare A रेजिस्टर */
		cmp_reg = CMPA;

	ehrpwm_ग_लिखो(pc->mmio_base, cmp_reg, duty_cycles);

	pm_runसमय_put_sync(chip->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ehrpwm_pwm_set_polarity(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm,
				   क्रमागत pwm_polarity polarity)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);

	/* Configuration of polarity in hardware delayed, करो at enable */
	pc->polarity[pwm->hwpwm] = polarity;

	वापस 0;
पूर्ण

अटल पूर्णांक ehrpwm_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);
	u16 aqcsfrc_val, aqcsfrc_mask;
	पूर्णांक ret;

	/* Leave घड़ी enabled on enabling PWM */
	pm_runसमय_get_sync(chip->dev);

	/* Disabling Action Qualअगरier on PWM output */
	अगर (pwm->hwpwm) अणु
		aqcsfrc_val = AQCSFRC_CSFB_FRCDIS;
		aqcsfrc_mask = AQCSFRC_CSFB_MASK;
	पूर्ण अन्यथा अणु
		aqcsfrc_val = AQCSFRC_CSFA_FRCDIS;
		aqcsfrc_mask = AQCSFRC_CSFA_MASK;
	पूर्ण

	/* Changes to shaकरोw mode */
	ehrpwm_modअगरy(pc->mmio_base, AQSFRC, AQSFRC_RLDCSF_MASK,
		      AQSFRC_RLDCSF_ZRO);

	ehrpwm_modअगरy(pc->mmio_base, AQCSFRC, aqcsfrc_mask, aqcsfrc_val);

	/* Channels polarity can be configured from action qualअगरier module */
	configure_polarity(pc, pwm->hwpwm);

	/* Enable TBCLK */
	ret = clk_enable(pc->tbclk);
	अगर (ret) अणु
		dev_err(chip->dev, "Failed to enable TBCLK for %s: %d\n",
			dev_name(pc->chip.dev), ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ehrpwm_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);
	u16 aqcsfrc_val, aqcsfrc_mask;

	/* Action Qualअगरier माला_दो PWM output low क्रमcefully */
	अगर (pwm->hwpwm) अणु
		aqcsfrc_val = AQCSFRC_CSFB_FRCLOW;
		aqcsfrc_mask = AQCSFRC_CSFB_MASK;
	पूर्ण अन्यथा अणु
		aqcsfrc_val = AQCSFRC_CSFA_FRCLOW;
		aqcsfrc_mask = AQCSFRC_CSFA_MASK;
	पूर्ण

	/* Update shaकरोw रेजिस्टर first beक्रमe modअगरying active रेजिस्टर */
	ehrpwm_modअगरy(pc->mmio_base, AQSFRC, AQSFRC_RLDCSF_MASK,
		      AQSFRC_RLDCSF_ZRO);
	ehrpwm_modअगरy(pc->mmio_base, AQCSFRC, aqcsfrc_mask, aqcsfrc_val);
	/*
	 * Changes to immediate action on Action Qualअगरier. This माला_दो
	 * Action Qualअगरier control on PWM output from next TBCLK
	 */
	ehrpwm_modअगरy(pc->mmio_base, AQSFRC, AQSFRC_RLDCSF_MASK,
		      AQSFRC_RLDCSF_IMDT);

	ehrpwm_modअगरy(pc->mmio_base, AQCSFRC, aqcsfrc_mask, aqcsfrc_val);

	/* Disabling TBCLK on PWM disable */
	clk_disable(pc->tbclk);

	/* Disable घड़ी on PWM disable */
	pm_runसमय_put_sync(chip->dev);
पूर्ण

अटल व्योम ehrpwm_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = to_ehrpwm_pwm_chip(chip);

	अगर (pwm_is_enabled(pwm)) अणु
		dev_warn(chip->dev, "Removing PWM device without disabling\n");
		pm_runसमय_put_sync(chip->dev);
	पूर्ण

	/* set period value to zero on मुक्त */
	pc->period_cycles[pwm->hwpwm] = 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops ehrpwm_pwm_ops = अणु
	.मुक्त = ehrpwm_pwm_मुक्त,
	.config = ehrpwm_pwm_config,
	.set_polarity = ehrpwm_pwm_set_polarity,
	.enable = ehrpwm_pwm_enable,
	.disable = ehrpwm_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ehrpwm_of_match[] = अणु
	अणु .compatible = "ti,am3352-ehrpwm" पूर्ण,
	अणु .compatible = "ti,am33xx-ehrpwm" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ehrpwm_of_match);

अटल पूर्णांक ehrpwm_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ehrpwm_pwm_chip *pc;
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

	अगर (IS_ERR(clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(clk), "Failed to get fck\n");

	pc->clk_rate = clk_get_rate(clk);
	अगर (!pc->clk_rate) अणु
		dev_err(&pdev->dev, "failed to get clock rate\n");
		वापस -EINVAL;
	पूर्ण

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &ehrpwm_pwm_ops;
	pc->chip.of_xlate = of_pwm_xlate_with_flags;
	pc->chip.of_pwm_n_cells = 3;
	pc->chip.npwm = NUM_PWM_CHANNEL;

	pc->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pc->mmio_base))
		वापस PTR_ERR(pc->mmio_base);

	/* Acquire tbclk क्रम Time Base EHRPWM submodule */
	pc->tbclk = devm_clk_get(&pdev->dev, "tbclk");
	अगर (IS_ERR(pc->tbclk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(pc->tbclk), "Failed to get tbclk\n");

	ret = clk_prepare(pc->tbclk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "clk_prepare() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pwmchip_add(&pc->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		जाओ err_clk_unprepare;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pc);
	pm_runसमय_enable(&pdev->dev);

	वापस 0;

err_clk_unprepare:
	clk_unprepare(pc->tbclk);

	वापस ret;
पूर्ण

अटल पूर्णांक ehrpwm_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = platक्रमm_get_drvdata(pdev);

	clk_unprepare(pc->tbclk);

	pm_runसमय_disable(&pdev->dev);

	वापस pwmchip_हटाओ(&pc->chip);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल व्योम ehrpwm_pwm_save_context(काष्ठा ehrpwm_pwm_chip *pc)
अणु
	pm_runसमय_get_sync(pc->chip.dev);

	pc->ctx.tbctl = ehrpwm_पढ़ो(pc->mmio_base, TBCTL);
	pc->ctx.tbprd = ehrpwm_पढ़ो(pc->mmio_base, TBPRD);
	pc->ctx.cmpa = ehrpwm_पढ़ो(pc->mmio_base, CMPA);
	pc->ctx.cmpb = ehrpwm_पढ़ो(pc->mmio_base, CMPB);
	pc->ctx.aqctla = ehrpwm_पढ़ो(pc->mmio_base, AQCTLA);
	pc->ctx.aqctlb = ehrpwm_पढ़ो(pc->mmio_base, AQCTLB);
	pc->ctx.aqsfrc = ehrpwm_पढ़ो(pc->mmio_base, AQSFRC);
	pc->ctx.aqcsfrc = ehrpwm_पढ़ो(pc->mmio_base, AQCSFRC);

	pm_runसमय_put_sync(pc->chip.dev);
पूर्ण

अटल व्योम ehrpwm_pwm_restore_context(काष्ठा ehrpwm_pwm_chip *pc)
अणु
	ehrpwm_ग_लिखो(pc->mmio_base, TBPRD, pc->ctx.tbprd);
	ehrpwm_ग_लिखो(pc->mmio_base, CMPA, pc->ctx.cmpa);
	ehrpwm_ग_लिखो(pc->mmio_base, CMPB, pc->ctx.cmpb);
	ehrpwm_ग_लिखो(pc->mmio_base, AQCTLA, pc->ctx.aqctla);
	ehrpwm_ग_लिखो(pc->mmio_base, AQCTLB, pc->ctx.aqctlb);
	ehrpwm_ग_लिखो(pc->mmio_base, AQSFRC, pc->ctx.aqsfrc);
	ehrpwm_ग_लिखो(pc->mmio_base, AQCSFRC, pc->ctx.aqcsfrc);
	ehrpwm_ग_लिखो(pc->mmio_base, TBCTL, pc->ctx.tbctl);
पूर्ण

अटल पूर्णांक ehrpwm_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	ehrpwm_pwm_save_context(pc);

	क्रम (i = 0; i < pc->chip.npwm; i++) अणु
		काष्ठा pwm_device *pwm = &pc->chip.pwms[i];

		अगर (!pwm_is_enabled(pwm))
			जारी;

		/* Disable explicitly अगर PWM is running */
		pm_runसमय_put_sync(dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ehrpwm_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा ehrpwm_pwm_chip *pc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pc->chip.npwm; i++) अणु
		काष्ठा pwm_device *pwm = &pc->chip.pwms[i];

		अगर (!pwm_is_enabled(pwm))
			जारी;

		/* Enable explicitly अगर PWM was running */
		pm_runसमय_get_sync(dev);
	पूर्ण

	ehrpwm_pwm_restore_context(pc);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ehrpwm_pwm_pm_ops, ehrpwm_pwm_suspend,
			 ehrpwm_pwm_resume);

अटल काष्ठा platक्रमm_driver ehrpwm_pwm_driver = अणु
	.driver = अणु
		.name = "ehrpwm",
		.of_match_table = ehrpwm_of_match,
		.pm = &ehrpwm_pwm_pm_ops,
	पूर्ण,
	.probe = ehrpwm_pwm_probe,
	.हटाओ = ehrpwm_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(ehrpwm_pwm_driver);

MODULE_DESCRIPTION("EHRPWM PWM driver");
MODULE_AUTHOR("Texas Instruments");
MODULE_LICENSE("GPL");
