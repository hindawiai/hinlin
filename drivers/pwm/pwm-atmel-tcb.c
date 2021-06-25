<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Overkiz SAS 2012
 *
 * Author: Boris BREZILLON <b.brezillon@overkiz.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/घड़ीsource.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <soc/at91/aपंचांगel_tcb.h>

#घोषणा NPWM	2

#घोषणा ATMEL_TC_ACMR_MASK	(ATMEL_TC_ACPA | ATMEL_TC_ACPC |	\
				 ATMEL_TC_AEEVT | ATMEL_TC_ASWTRG)

#घोषणा ATMEL_TC_BCMR_MASK	(ATMEL_TC_BCPB | ATMEL_TC_BCPC |	\
				 ATMEL_TC_BEEVT | ATMEL_TC_BSWTRG)

काष्ठा aपंचांगel_tcb_pwm_device अणु
	क्रमागत pwm_polarity polarity;	/* PWM polarity */
	अचिन्हित भाग;			/* PWM घड़ी भागider */
	अचिन्हित duty;			/* PWM duty expressed in clk cycles */
	अचिन्हित period;		/* PWM period expressed in clk cycles */
पूर्ण;

काष्ठा aपंचांगel_tcb_channel अणु
	u32 enabled;
	u32 cmr;
	u32 ra;
	u32 rb;
	u32 rc;
पूर्ण;

काष्ठा aपंचांगel_tcb_pwm_chip अणु
	काष्ठा pwm_chip chip;
	spinlock_t lock;
	u8 channel;
	u8 width;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;
	काष्ठा clk *gclk;
	काष्ठा clk *slow_clk;
	काष्ठा aपंचांगel_tcb_pwm_device *pwms[NPWM];
	काष्ठा aपंचांगel_tcb_channel bkup;
पूर्ण;

स्थिर u8 aपंचांगel_tcb_भागisors[] = अणु 2, 8, 32, 128, 0, पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_tcb_pwm_chip *to_tcb_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा aपंचांगel_tcb_pwm_chip, chip);
पूर्ण

अटल पूर्णांक aपंचांगel_tcb_pwm_set_polarity(काष्ठा pwm_chip *chip,
				      काष्ठा pwm_device *pwm,
				      क्रमागत pwm_polarity polarity)
अणु
	काष्ठा aपंचांगel_tcb_pwm_device *tcbpwm = pwm_get_chip_data(pwm);

	tcbpwm->polarity = polarity;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tcb_pwm_request(काष्ठा pwm_chip *chip,
				 काष्ठा pwm_device *pwm)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwmc = to_tcb_chip(chip);
	काष्ठा aपंचांगel_tcb_pwm_device *tcbpwm;
	अचिन्हित cmr;
	पूर्णांक ret;

	tcbpwm = devm_kzalloc(chip->dev, माप(*tcbpwm), GFP_KERNEL);
	अगर (!tcbpwm)
		वापस -ENOMEM;

	ret = clk_prepare_enable(tcbpwmc->clk);
	अगर (ret) अणु
		devm_kमुक्त(chip->dev, tcbpwm);
		वापस ret;
	पूर्ण

	pwm_set_chip_data(pwm, tcbpwm);
	tcbpwm->polarity = PWM_POLARITY_NORMAL;
	tcbpwm->duty = 0;
	tcbpwm->period = 0;
	tcbpwm->भाग = 0;

	spin_lock(&tcbpwmc->lock);
	regmap_पढ़ो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, CMR), &cmr);
	/*
	 * Get init config from Timer Counter रेजिस्टरs अगर
	 * Timer Counter is alपढ़ोy configured as a PWM generator.
	 */
	अगर (cmr & ATMEL_TC_WAVE) अणु
		अगर (pwm->hwpwm == 0)
			regmap_पढ़ो(tcbpwmc->regmap,
				    ATMEL_TC_REG(tcbpwmc->channel, RA),
				    &tcbpwm->duty);
		अन्यथा
			regmap_पढ़ो(tcbpwmc->regmap,
				    ATMEL_TC_REG(tcbpwmc->channel, RB),
				    &tcbpwm->duty);

		tcbpwm->भाग = cmr & ATMEL_TC_TCCLKS;
		regmap_पढ़ो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, RC),
			    &tcbpwm->period);
		cmr &= (ATMEL_TC_TCCLKS | ATMEL_TC_ACMR_MASK |
			ATMEL_TC_BCMR_MASK);
	पूर्ण अन्यथा
		cmr = 0;

	cmr |= ATMEL_TC_WAVE | ATMEL_TC_WAVESEL_UP_AUTO | ATMEL_TC_EEVT_XC0;
	regmap_ग_लिखो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, CMR), cmr);
	spin_unlock(&tcbpwmc->lock);

	tcbpwmc->pwms[pwm->hwpwm] = tcbpwm;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_tcb_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwmc = to_tcb_chip(chip);
	काष्ठा aपंचांगel_tcb_pwm_device *tcbpwm = pwm_get_chip_data(pwm);

	clk_disable_unprepare(tcbpwmc->clk);
	tcbpwmc->pwms[pwm->hwpwm] = शून्य;
	devm_kमुक्त(chip->dev, tcbpwm);
पूर्ण

अटल व्योम aपंचांगel_tcb_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwmc = to_tcb_chip(chip);
	काष्ठा aपंचांगel_tcb_pwm_device *tcbpwm = pwm_get_chip_data(pwm);
	अचिन्हित cmr;
	क्रमागत pwm_polarity polarity = tcbpwm->polarity;

	/*
	 * If duty is 0 the समयr will be stopped and we have to
	 * configure the output correctly on software trigger:
	 *  - set output to high अगर PWM_POLARITY_INVERSED
	 *  - set output to low अगर PWM_POLARITY_NORMAL
	 *
	 * This is why we're reverting polarity in this हाल.
	 */
	अगर (tcbpwm->duty == 0)
		polarity = !polarity;

	spin_lock(&tcbpwmc->lock);
	regmap_पढ़ो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, CMR), &cmr);

	/* flush old setting and set the new one */
	अगर (pwm->hwpwm == 0) अणु
		cmr &= ~ATMEL_TC_ACMR_MASK;
		अगर (polarity == PWM_POLARITY_INVERSED)
			cmr |= ATMEL_TC_ASWTRG_CLEAR;
		अन्यथा
			cmr |= ATMEL_TC_ASWTRG_SET;
	पूर्ण अन्यथा अणु
		cmr &= ~ATMEL_TC_BCMR_MASK;
		अगर (polarity == PWM_POLARITY_INVERSED)
			cmr |= ATMEL_TC_BSWTRG_CLEAR;
		अन्यथा
			cmr |= ATMEL_TC_BSWTRG_SET;
	पूर्ण

	regmap_ग_लिखो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, CMR), cmr);

	/*
	 * Use software trigger to apply the new setting.
	 * If both PWM devices in this group are disabled we stop the घड़ी.
	 */
	अगर (!(cmr & (ATMEL_TC_ACPC | ATMEL_TC_BCPC))) अणु
		regmap_ग_लिखो(tcbpwmc->regmap,
			     ATMEL_TC_REG(tcbpwmc->channel, CCR),
			     ATMEL_TC_SWTRG | ATMEL_TC_CLKDIS);
		tcbpwmc->bkup.enabled = 1;
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(tcbpwmc->regmap,
			     ATMEL_TC_REG(tcbpwmc->channel, CCR),
			     ATMEL_TC_SWTRG);
		tcbpwmc->bkup.enabled = 0;
	पूर्ण

	spin_unlock(&tcbpwmc->lock);
पूर्ण

अटल पूर्णांक aपंचांगel_tcb_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwmc = to_tcb_chip(chip);
	काष्ठा aपंचांगel_tcb_pwm_device *tcbpwm = pwm_get_chip_data(pwm);
	u32 cmr;
	क्रमागत pwm_polarity polarity = tcbpwm->polarity;

	/*
	 * If duty is 0 the समयr will be stopped and we have to
	 * configure the output correctly on software trigger:
	 *  - set output to high अगर PWM_POLARITY_INVERSED
	 *  - set output to low अगर PWM_POLARITY_NORMAL
	 *
	 * This is why we're reverting polarity in this हाल.
	 */
	अगर (tcbpwm->duty == 0)
		polarity = !polarity;

	spin_lock(&tcbpwmc->lock);
	regmap_पढ़ो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, CMR), &cmr);

	/* flush old setting and set the new one */
	cmr &= ~ATMEL_TC_TCCLKS;

	अगर (pwm->hwpwm == 0) अणु
		cmr &= ~ATMEL_TC_ACMR_MASK;

		/* Set CMR flags according to given polarity */
		अगर (polarity == PWM_POLARITY_INVERSED)
			cmr |= ATMEL_TC_ASWTRG_CLEAR;
		अन्यथा
			cmr |= ATMEL_TC_ASWTRG_SET;
	पूर्ण अन्यथा अणु
		cmr &= ~ATMEL_TC_BCMR_MASK;
		अगर (polarity == PWM_POLARITY_INVERSED)
			cmr |= ATMEL_TC_BSWTRG_CLEAR;
		अन्यथा
			cmr |= ATMEL_TC_BSWTRG_SET;
	पूर्ण

	/*
	 * If duty is 0 or equal to period there's no need to रेजिस्टर
	 * a specअगरic action on RA/RB and RC compare.
	 * The output will be configured on software trigger and keep
	 * this config till next config call.
	 */
	अगर (tcbpwm->duty != tcbpwm->period && tcbpwm->duty > 0) अणु
		अगर (pwm->hwpwm == 0) अणु
			अगर (polarity == PWM_POLARITY_INVERSED)
				cmr |= ATMEL_TC_ACPA_SET | ATMEL_TC_ACPC_CLEAR;
			अन्यथा
				cmr |= ATMEL_TC_ACPA_CLEAR | ATMEL_TC_ACPC_SET;
		पूर्ण अन्यथा अणु
			अगर (polarity == PWM_POLARITY_INVERSED)
				cmr |= ATMEL_TC_BCPB_SET | ATMEL_TC_BCPC_CLEAR;
			अन्यथा
				cmr |= ATMEL_TC_BCPB_CLEAR | ATMEL_TC_BCPC_SET;
		पूर्ण
	पूर्ण

	cmr |= (tcbpwm->भाग & ATMEL_TC_TCCLKS);

	regmap_ग_लिखो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, CMR), cmr);

	अगर (pwm->hwpwm == 0)
		regmap_ग_लिखो(tcbpwmc->regmap,
			     ATMEL_TC_REG(tcbpwmc->channel, RA),
			     tcbpwm->duty);
	अन्यथा
		regmap_ग_लिखो(tcbpwmc->regmap,
			     ATMEL_TC_REG(tcbpwmc->channel, RB),
			     tcbpwm->duty);

	regmap_ग_लिखो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, RC),
		     tcbpwm->period);

	/* Use software trigger to apply the new setting */
	regmap_ग_लिखो(tcbpwmc->regmap, ATMEL_TC_REG(tcbpwmc->channel, CCR),
		     ATMEL_TC_SWTRG | ATMEL_TC_CLKEN);
	tcbpwmc->bkup.enabled = 1;
	spin_unlock(&tcbpwmc->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tcb_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwmc = to_tcb_chip(chip);
	काष्ठा aपंचांगel_tcb_pwm_device *tcbpwm = pwm_get_chip_data(pwm);
	काष्ठा aपंचांगel_tcb_pwm_device *atcbpwm = शून्य;
	पूर्णांक i = 0;
	पूर्णांक slowclk = 0;
	अचिन्हित period;
	अचिन्हित duty;
	अचिन्हित rate = clk_get_rate(tcbpwmc->clk);
	अचिन्हित दीर्घ दीर्घ min;
	अचिन्हित दीर्घ दीर्घ max;

	/*
	 * Find best clk भागisor:
	 * the smallest भागisor which can fulfill the period_ns requirements.
	 * If there is a gclk, the first भागisor is actuallly the gclk selector
	 */
	अगर (tcbpwmc->gclk)
		i = 1;
	क्रम (; i < ARRAY_SIZE(aपंचांगel_tcb_भागisors); ++i) अणु
		अगर (aपंचांगel_tcb_भागisors[i] == 0) अणु
			slowclk = i;
			जारी;
		पूर्ण
		min = भाग_u64((u64)NSEC_PER_SEC * aपंचांगel_tcb_भागisors[i], rate);
		max = min << tcbpwmc->width;
		अगर (max >= period_ns)
			अवरोध;
	पूर्ण

	/*
	 * If none of the भागisor are small enough to represent period_ns
	 * take slow घड़ी (32KHz).
	 */
	अगर (i == ARRAY_SIZE(aपंचांगel_tcb_भागisors)) अणु
		i = slowclk;
		rate = clk_get_rate(tcbpwmc->slow_clk);
		min = भाग_u64(NSEC_PER_SEC, rate);
		max = min << tcbpwmc->width;

		/* If period is too big वापस दुस्फल error */
		अगर (max < period_ns)
			वापस -दुस्फल;
	पूर्ण

	duty = भाग_u64(duty_ns, min);
	period = भाग_u64(period_ns, min);

	अगर (pwm->hwpwm == 0)
		atcbpwm = tcbpwmc->pwms[1];
	अन्यथा
		atcbpwm = tcbpwmc->pwms[0];

	/*
	 * PWM devices provided by the TCB driver are grouped by 2.
	 * PWM devices in a given group must be configured with the
	 * same period_ns.
	 *
	 * We're checking the period value of the second PWM device
	 * in this group beक्रमe applying the new config.
	 */
	अगर ((atcbpwm && atcbpwm->duty > 0 &&
			atcbpwm->duty != atcbpwm->period) &&
		(atcbpwm->भाग != i || atcbpwm->period != period)) अणु
		dev_err(chip->dev,
			"failed to configure period_ns: PWM group already configured with a different value\n");
		वापस -EINVAL;
	पूर्ण

	tcbpwm->period = period;
	tcbpwm->भाग = i;
	tcbpwm->duty = duty;

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tcb_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       स्थिर काष्ठा pwm_state *state)
अणु
	पूर्णांक duty_cycle, period;
	पूर्णांक ret;

	/* This function only sets a flag in driver data */
	aपंचांगel_tcb_pwm_set_polarity(chip, pwm, state->polarity);

	अगर (!state->enabled) अणु
		aपंचांगel_tcb_pwm_disable(chip, pwm);
		वापस 0;
	पूर्ण

	period = state->period < पूर्णांक_उच्च ? state->period : पूर्णांक_उच्च;
	duty_cycle = state->duty_cycle < पूर्णांक_उच्च ? state->duty_cycle : पूर्णांक_उच्च;

	ret = aपंचांगel_tcb_pwm_config(chip, pwm, duty_cycle, period);
	अगर (ret)
		वापस ret;

	वापस aपंचांगel_tcb_pwm_enable(chip, pwm);
पूर्ण

अटल स्थिर काष्ठा pwm_ops aपंचांगel_tcb_pwm_ops = अणु
	.request = aपंचांगel_tcb_pwm_request,
	.मुक्त = aपंचांगel_tcb_pwm_मुक्त,
	.apply = aपंचांगel_tcb_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा aपंचांगel_tcb_config tcb_rm9200_config = अणु
	.counter_width = 16,
पूर्ण;

अटल काष्ठा aपंचांगel_tcb_config tcb_sam9x5_config = अणु
	.counter_width = 32,
पूर्ण;

अटल काष्ठा aपंचांगel_tcb_config tcb_sama5d2_config = अणु
	.counter_width = 32,
	.has_gclk = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_tcb_of_match[] = अणु
	अणु .compatible = "atmel,at91rm9200-tcb", .data = &tcb_rm9200_config, पूर्ण,
	अणु .compatible = "atmel,at91sam9x5-tcb", .data = &tcb_sam9x5_config, पूर्ण,
	अणु .compatible = "atmel,sama5d2-tcb", .data = &tcb_sama5d2_config, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल पूर्णांक aपंचांगel_tcb_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwm;
	स्थिर काष्ठा aपंचांगel_tcb_config *config;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk, *gclk = शून्य;
	काष्ठा clk *slow_clk;
	अक्षर clk_name[] = "t0_clk";
	पूर्णांक err;
	पूर्णांक channel;

	err = of_property_पढ़ो_u32(np, "reg", &channel);
	अगर (err < 0) अणु
		dev_err(&pdev->dev,
			"failed to get Timer Counter Block channel from device tree (error: %d)\n",
			err);
		वापस err;
	पूर्ण

	regmap = syscon_node_to_regmap(np->parent);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	slow_clk = of_clk_get_by_name(np->parent, "slow_clk");
	अगर (IS_ERR(slow_clk))
		वापस PTR_ERR(slow_clk);

	clk_name[1] += channel;
	clk = of_clk_get_by_name(np->parent, clk_name);
	अगर (IS_ERR(clk))
		clk = of_clk_get_by_name(np->parent, "t0_clk");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	match = of_match_node(aपंचांगel_tcb_of_match, np->parent);
	config = match->data;

	अगर (config->has_gclk) अणु
		gclk = of_clk_get_by_name(np->parent, "gclk");
		अगर (IS_ERR(gclk))
			वापस PTR_ERR(gclk);
	पूर्ण

	tcbpwm = devm_kzalloc(&pdev->dev, माप(*tcbpwm), GFP_KERNEL);
	अगर (tcbpwm == शून्य) अणु
		err = -ENOMEM;
		जाओ err_slow_clk;
	पूर्ण

	tcbpwm->chip.dev = &pdev->dev;
	tcbpwm->chip.ops = &aपंचांगel_tcb_pwm_ops;
	tcbpwm->chip.of_xlate = of_pwm_xlate_with_flags;
	tcbpwm->chip.of_pwm_n_cells = 3;
	tcbpwm->chip.npwm = NPWM;
	tcbpwm->channel = channel;
	tcbpwm->regmap = regmap;
	tcbpwm->clk = clk;
	tcbpwm->gclk = gclk;
	tcbpwm->slow_clk = slow_clk;
	tcbpwm->width = config->counter_width;

	err = clk_prepare_enable(slow_clk);
	अगर (err)
		जाओ err_slow_clk;

	spin_lock_init(&tcbpwm->lock);

	err = pwmchip_add(&tcbpwm->chip);
	अगर (err < 0)
		जाओ err_disable_clk;

	platक्रमm_set_drvdata(pdev, tcbpwm);

	वापस 0;

err_disable_clk:
	clk_disable_unprepare(tcbpwm->slow_clk);

err_slow_clk:
	clk_put(slow_clk);

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_tcb_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwm = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = pwmchip_हटाओ(&tcbpwm->chip);
	अगर (err < 0)
		वापस err;

	clk_disable_unprepare(tcbpwm->slow_clk);
	clk_put(tcbpwm->slow_clk);
	clk_put(tcbpwm->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_tcb_pwm_dt_ids[] = अणु
	अणु .compatible = "atmel,tcb-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_tcb_pwm_dt_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aपंचांगel_tcb_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwm = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_tcb_channel *chan = &tcbpwm->bkup;
	अचिन्हित पूर्णांक channel = tcbpwm->channel;

	regmap_पढ़ो(tcbpwm->regmap, ATMEL_TC_REG(channel, CMR), &chan->cmr);
	regmap_पढ़ो(tcbpwm->regmap, ATMEL_TC_REG(channel, RA), &chan->ra);
	regmap_पढ़ो(tcbpwm->regmap, ATMEL_TC_REG(channel, RB), &chan->rb);
	regmap_पढ़ो(tcbpwm->regmap, ATMEL_TC_REG(channel, RC), &chan->rc);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_tcb_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_tcb_pwm_chip *tcbpwm = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_tcb_channel *chan = &tcbpwm->bkup;
	अचिन्हित पूर्णांक channel = tcbpwm->channel;

	regmap_ग_लिखो(tcbpwm->regmap, ATMEL_TC_REG(channel, CMR), chan->cmr);
	regmap_ग_लिखो(tcbpwm->regmap, ATMEL_TC_REG(channel, RA), chan->ra);
	regmap_ग_लिखो(tcbpwm->regmap, ATMEL_TC_REG(channel, RB), chan->rb);
	regmap_ग_लिखो(tcbpwm->regmap, ATMEL_TC_REG(channel, RC), chan->rc);

	अगर (chan->enabled)
		regmap_ग_लिखो(tcbpwm->regmap,
			     ATMEL_TC_CLKEN | ATMEL_TC_SWTRG,
			     ATMEL_TC_REG(channel, CCR));

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_tcb_pwm_pm_ops, aपंचांगel_tcb_pwm_suspend,
			 aपंचांगel_tcb_pwm_resume);

अटल काष्ठा platक्रमm_driver aपंचांगel_tcb_pwm_driver = अणु
	.driver = अणु
		.name = "atmel-tcb-pwm",
		.of_match_table = aपंचांगel_tcb_pwm_dt_ids,
		.pm = &aपंचांगel_tcb_pwm_pm_ops,
	पूर्ण,
	.probe = aपंचांगel_tcb_pwm_probe,
	.हटाओ = aपंचांगel_tcb_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_tcb_pwm_driver);

MODULE_AUTHOR("Boris BREZILLON <b.brezillon@overkiz.com>");
MODULE_DESCRIPTION("Atmel Timer Counter Pulse Width Modulation Driver");
MODULE_LICENSE("GPL v2");
