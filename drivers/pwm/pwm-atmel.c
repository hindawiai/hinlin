<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Aपंचांगel Pulse Width Modulation Controller
 *
 * Copyright (C) 2013 Aपंचांगel Corporation
 *		 Bo Shen <voice.shen@aपंचांगel.com>
 *
 * Links to reference manuals क्रम the supported PWM chips can be found in
 * Documentation/arm/microchip.rst.
 *
 * Limitations:
 * - Periods start with the inactive level.
 * - Hardware has to be stopped in general to update settings.
 *
 * Software bugs/possible improvements:
 * - When aपंचांगel_pwm_apply() is called with state->enabled=false a change in
 *   state->polarity isn't honored.
 * - Instead of sleeping to रुको क्रम a completed period, the पूर्णांकerrupt
 *   functionality could be used.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

/* The following is global रेजिस्टरs क्रम PWM controller */
#घोषणा PWM_ENA			0x04
#घोषणा PWM_DIS			0x08
#घोषणा PWM_SR			0x0C
#घोषणा PWM_ISR			0x1C
/* Bit field in SR */
#घोषणा PWM_SR_ALL_CH_ON	0x0F

/* The following रेजिस्टर is PWM channel related रेजिस्टरs */
#घोषणा PWM_CH_REG_OFFSET	0x200
#घोषणा PWM_CH_REG_SIZE		0x20

#घोषणा PWM_CMR			0x0
/* Bit field in CMR */
#घोषणा PWM_CMR_CPOL		(1 << 9)
#घोषणा PWM_CMR_UPD_CDTY	(1 << 10)
#घोषणा PWM_CMR_CPRE_MSK	0xF

/* The following रेजिस्टरs क्रम PWM v1 */
#घोषणा PWMV1_CDTY		0x04
#घोषणा PWMV1_CPRD		0x08
#घोषणा PWMV1_CUPD		0x10

/* The following रेजिस्टरs क्रम PWM v2 */
#घोषणा PWMV2_CDTY		0x04
#घोषणा PWMV2_CDTYUPD		0x08
#घोषणा PWMV2_CPRD		0x0C
#घोषणा PWMV2_CPRDUPD		0x10

#घोषणा PWM_MAX_PRES		10

काष्ठा aपंचांगel_pwm_रेजिस्टरs अणु
	u8 period;
	u8 period_upd;
	u8 duty;
	u8 duty_upd;
पूर्ण;

काष्ठा aपंचांगel_pwm_config अणु
	u32 period_bits;
पूर्ण;

काष्ठा aपंचांगel_pwm_data अणु
	काष्ठा aपंचांगel_pwm_रेजिस्टरs regs;
	काष्ठा aपंचांगel_pwm_config cfg;
पूर्ण;

काष्ठा aपंचांगel_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	स्थिर काष्ठा aपंचांगel_pwm_data *data;

	अचिन्हित पूर्णांक updated_pwms;
	/* ISR is cleared when पढ़ो, ensure only one thपढ़ो करोes that */
	काष्ठा mutex isr_lock;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_pwm_chip *to_aपंचांगel_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा aपंचांगel_pwm_chip, chip);
पूर्ण

अटल अंतरभूत u32 aपंचांगel_pwm_पढ़ोl(काष्ठा aपंचांगel_pwm_chip *chip,
				  अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl_relaxed(chip->base + offset);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_pwm_ग_लिखोl(काष्ठा aपंचांगel_pwm_chip *chip,
				    अचिन्हित दीर्घ offset, अचिन्हित दीर्घ val)
अणु
	ग_लिखोl_relaxed(val, chip->base + offset);
पूर्ण

अटल अंतरभूत u32 aपंचांगel_pwm_ch_पढ़ोl(काष्ठा aपंचांगel_pwm_chip *chip,
				     अचिन्हित पूर्णांक ch, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ base = PWM_CH_REG_OFFSET + ch * PWM_CH_REG_SIZE;

	वापस aपंचांगel_pwm_पढ़ोl(chip, base + offset);
पूर्ण

अटल अंतरभूत व्योम aपंचांगel_pwm_ch_ग_लिखोl(काष्ठा aपंचांगel_pwm_chip *chip,
				       अचिन्हित पूर्णांक ch, अचिन्हित दीर्घ offset,
				       अचिन्हित दीर्घ val)
अणु
	अचिन्हित दीर्घ base = PWM_CH_REG_OFFSET + ch * PWM_CH_REG_SIZE;

	aपंचांगel_pwm_ग_लिखोl(chip, base + offset, val);
पूर्ण

अटल पूर्णांक aपंचांगel_pwm_calculate_cprd_and_pres(काष्ठा pwm_chip *chip,
					     अचिन्हित दीर्घ clkrate,
					     स्थिर काष्ठा pwm_state *state,
					     अचिन्हित दीर्घ *cprd, u32 *pres)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm = to_aपंचांगel_pwm_chip(chip);
	अचिन्हित दीर्घ दीर्घ cycles = state->period;
	पूर्णांक shअगरt;

	/* Calculate the period cycles and prescale value */
	cycles *= clkrate;
	करो_भाग(cycles, NSEC_PER_SEC);

	/*
	 * The रेजिस्टर क्रम the period length is cfg.period_bits bits wide.
	 * So क्रम each bit the number of घड़ी cycles is wider भागide the input
	 * घड़ी frequency by two using pres and shअगरt cprd accordingly.
	 */
	shअगरt = fls(cycles) - aपंचांगel_pwm->data->cfg.period_bits;

	अगर (shअगरt > PWM_MAX_PRES) अणु
		dev_err(chip->dev, "pres exceeds the maximum value\n");
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (shअगरt > 0) अणु
		*pres = shअगरt;
		cycles >>= *pres;
	पूर्ण अन्यथा अणु
		*pres = 0;
	पूर्ण

	*cprd = cycles;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_pwm_calculate_cdty(स्थिर काष्ठा pwm_state *state,
				     अचिन्हित दीर्घ clkrate, अचिन्हित दीर्घ cprd,
				     u32 pres, अचिन्हित दीर्घ *cdty)
अणु
	अचिन्हित दीर्घ दीर्घ cycles = state->duty_cycle;

	cycles *= clkrate;
	करो_भाग(cycles, NSEC_PER_SEC);
	cycles >>= pres;
	*cdty = cprd - cycles;
पूर्ण

अटल व्योम aपंचांगel_pwm_update_cdty(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				  अचिन्हित दीर्घ cdty)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm = to_aपंचांगel_pwm_chip(chip);
	u32 val;

	अगर (aपंचांगel_pwm->data->regs.duty_upd ==
	    aपंचांगel_pwm->data->regs.period_upd) अणु
		val = aपंचांगel_pwm_ch_पढ़ोl(aपंचांगel_pwm, pwm->hwpwm, PWM_CMR);
		val &= ~PWM_CMR_UPD_CDTY;
		aपंचांगel_pwm_ch_ग_लिखोl(aपंचांगel_pwm, pwm->hwpwm, PWM_CMR, val);
	पूर्ण

	aपंचांगel_pwm_ch_ग_लिखोl(aपंचांगel_pwm, pwm->hwpwm,
			    aपंचांगel_pwm->data->regs.duty_upd, cdty);
पूर्ण

अटल व्योम aपंचांगel_pwm_set_cprd_cdty(काष्ठा pwm_chip *chip,
				    काष्ठा pwm_device *pwm,
				    अचिन्हित दीर्घ cprd, अचिन्हित दीर्घ cdty)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm = to_aपंचांगel_pwm_chip(chip);

	aपंचांगel_pwm_ch_ग_लिखोl(aपंचांगel_pwm, pwm->hwpwm,
			    aपंचांगel_pwm->data->regs.duty, cdty);
	aपंचांगel_pwm_ch_ग_लिखोl(aपंचांगel_pwm, pwm->hwpwm,
			    aपंचांगel_pwm->data->regs.period, cprd);
पूर्ण

अटल व्योम aपंचांगel_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      bool disable_clk)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm = to_aपंचांगel_pwm_chip(chip);
	अचिन्हित दीर्घ समयout = jअगरfies + 2 * HZ;

	/*
	 * Wait क्रम at least a complete period to have passed beक्रमe disabling a
	 * channel to be sure that CDTY has been updated
	 */
	mutex_lock(&aपंचांगel_pwm->isr_lock);
	aपंचांगel_pwm->updated_pwms |= aपंचांगel_pwm_पढ़ोl(aपंचांगel_pwm, PWM_ISR);

	जबतक (!(aपंचांगel_pwm->updated_pwms & (1 << pwm->hwpwm)) &&
	       समय_beक्रमe(jअगरfies, समयout)) अणु
		usleep_range(10, 100);
		aपंचांगel_pwm->updated_pwms |= aपंचांगel_pwm_पढ़ोl(aपंचांगel_pwm, PWM_ISR);
	पूर्ण

	mutex_unlock(&aपंचांगel_pwm->isr_lock);
	aपंचांगel_pwm_ग_लिखोl(aपंचांगel_pwm, PWM_DIS, 1 << pwm->hwpwm);

	/*
	 * Wait क्रम the PWM channel disable operation to be effective beक्रमe
	 * stopping the घड़ी.
	 */
	समयout = jअगरfies + 2 * HZ;

	जबतक ((aपंचांगel_pwm_पढ़ोl(aपंचांगel_pwm, PWM_SR) & (1 << pwm->hwpwm)) &&
	       समय_beक्रमe(jअगरfies, समयout))
		usleep_range(10, 100);

	अगर (disable_clk)
		clk_disable(aपंचांगel_pwm->clk);
पूर्ण

अटल पूर्णांक aपंचांगel_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm = to_aपंचांगel_pwm_chip(chip);
	काष्ठा pwm_state cstate;
	अचिन्हित दीर्घ cprd, cdty;
	u32 pres, val;
	पूर्णांक ret;

	pwm_get_state(pwm, &cstate);

	अगर (state->enabled) अणु
		अचिन्हित दीर्घ clkrate = clk_get_rate(aपंचांगel_pwm->clk);

		अगर (cstate.enabled &&
		    cstate.polarity == state->polarity &&
		    cstate.period == state->period) अणु
			u32 cmr = aपंचांगel_pwm_ch_पढ़ोl(aपंचांगel_pwm, pwm->hwpwm, PWM_CMR);

			cprd = aपंचांगel_pwm_ch_पढ़ोl(aपंचांगel_pwm, pwm->hwpwm,
						  aपंचांगel_pwm->data->regs.period);
			pres = cmr & PWM_CMR_CPRE_MSK;

			aपंचांगel_pwm_calculate_cdty(state, clkrate, cprd, pres, &cdty);
			aपंचांगel_pwm_update_cdty(chip, pwm, cdty);
			वापस 0;
		पूर्ण

		ret = aपंचांगel_pwm_calculate_cprd_and_pres(chip, clkrate, state, &cprd,
							&pres);
		अगर (ret) अणु
			dev_err(chip->dev,
				"failed to calculate cprd and prescaler\n");
			वापस ret;
		पूर्ण

		aपंचांगel_pwm_calculate_cdty(state, clkrate, cprd, pres, &cdty);

		अगर (cstate.enabled) अणु
			aपंचांगel_pwm_disable(chip, pwm, false);
		पूर्ण अन्यथा अणु
			ret = clk_enable(aपंचांगel_pwm->clk);
			अगर (ret) अणु
				dev_err(chip->dev, "failed to enable clock\n");
				वापस ret;
			पूर्ण
		पूर्ण

		/* It is necessary to preserve CPOL, inside CMR */
		val = aपंचांगel_pwm_ch_पढ़ोl(aपंचांगel_pwm, pwm->hwpwm, PWM_CMR);
		val = (val & ~PWM_CMR_CPRE_MSK) | (pres & PWM_CMR_CPRE_MSK);
		अगर (state->polarity == PWM_POLARITY_NORMAL)
			val &= ~PWM_CMR_CPOL;
		अन्यथा
			val |= PWM_CMR_CPOL;
		aपंचांगel_pwm_ch_ग_लिखोl(aपंचांगel_pwm, pwm->hwpwm, PWM_CMR, val);
		aपंचांगel_pwm_set_cprd_cdty(chip, pwm, cprd, cdty);
		mutex_lock(&aपंचांगel_pwm->isr_lock);
		aपंचांगel_pwm->updated_pwms |= aपंचांगel_pwm_पढ़ोl(aपंचांगel_pwm, PWM_ISR);
		aपंचांगel_pwm->updated_pwms &= ~(1 << pwm->hwpwm);
		mutex_unlock(&aपंचांगel_pwm->isr_lock);
		aपंचांगel_pwm_ग_लिखोl(aपंचांगel_pwm, PWM_ENA, 1 << pwm->hwpwm);
	पूर्ण अन्यथा अगर (cstate.enabled) अणु
		aपंचांगel_pwm_disable(chip, pwm, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				काष्ठा pwm_state *state)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm = to_aपंचांगel_pwm_chip(chip);
	u32 sr, cmr;

	sr = aपंचांगel_pwm_पढ़ोl(aपंचांगel_pwm, PWM_SR);
	cmr = aपंचांगel_pwm_ch_पढ़ोl(aपंचांगel_pwm, pwm->hwpwm, PWM_CMR);

	अगर (sr & (1 << pwm->hwpwm)) अणु
		अचिन्हित दीर्घ rate = clk_get_rate(aपंचांगel_pwm->clk);
		u32 cdty, cprd, pres;
		u64 पंचांगp;

		pres = cmr & PWM_CMR_CPRE_MSK;

		cprd = aपंचांगel_pwm_ch_पढ़ोl(aपंचांगel_pwm, pwm->hwpwm,
					  aपंचांगel_pwm->data->regs.period);
		पंचांगp = (u64)cprd * NSEC_PER_SEC;
		पंचांगp <<= pres;
		state->period = DIV64_U64_ROUND_UP(पंचांगp, rate);

		cdty = aपंचांगel_pwm_ch_पढ़ोl(aपंचांगel_pwm, pwm->hwpwm,
					  aपंचांगel_pwm->data->regs.duty);
		पंचांगp = (u64)(cprd - cdty) * NSEC_PER_SEC;
		पंचांगp <<= pres;
		state->duty_cycle = DIV64_U64_ROUND_UP(पंचांगp, rate);

		state->enabled = true;
	पूर्ण अन्यथा अणु
		state->enabled = false;
	पूर्ण

	अगर (cmr & PWM_CMR_CPOL)
		state->polarity = PWM_POLARITY_INVERSED;
	अन्यथा
		state->polarity = PWM_POLARITY_NORMAL;
पूर्ण

अटल स्थिर काष्ठा pwm_ops aपंचांगel_pwm_ops = अणु
	.apply = aपंचांगel_pwm_apply,
	.get_state = aपंचांगel_pwm_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_pwm_data aपंचांगel_sam9rl_pwm_data = अणु
	.regs = अणु
		.period		= PWMV1_CPRD,
		.period_upd	= PWMV1_CUPD,
		.duty		= PWMV1_CDTY,
		.duty_upd	= PWMV1_CUPD,
	पूर्ण,
	.cfg = अणु
		/* 16 bits to keep period and duty. */
		.period_bits	= 16,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_pwm_data aपंचांगel_sama5_pwm_data = अणु
	.regs = अणु
		.period		= PWMV2_CPRD,
		.period_upd	= PWMV2_CPRDUPD,
		.duty		= PWMV2_CDTY,
		.duty_upd	= PWMV2_CDTYUPD,
	पूर्ण,
	.cfg = अणु
		/* 16 bits to keep period and duty. */
		.period_bits	= 16,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_pwm_data mchp_sam9x60_pwm_data = अणु
	.regs = अणु
		.period		= PWMV1_CPRD,
		.period_upd	= PWMV1_CUPD,
		.duty		= PWMV1_CDTY,
		.duty_upd	= PWMV1_CUPD,
	पूर्ण,
	.cfg = अणु
		/* 32 bits to keep period and duty. */
		.period_bits	= 32,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_pwm_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91sam9rl-pwm",
		.data = &aपंचांगel_sam9rl_pwm_data,
	पूर्ण, अणु
		.compatible = "atmel,sama5d3-pwm",
		.data = &aपंचांगel_sama5_pwm_data,
	पूर्ण, अणु
		.compatible = "atmel,sama5d2-pwm",
		.data = &aपंचांगel_sama5_pwm_data,
	पूर्ण, अणु
		.compatible = "microchip,sam9x60-pwm",
		.data = &mchp_sam9x60_pwm_data,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_pwm_dt_ids);

अटल पूर्णांक aपंचांगel_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm;
	पूर्णांक ret;

	aपंचांगel_pwm = devm_kzalloc(&pdev->dev, माप(*aपंचांगel_pwm), GFP_KERNEL);
	अगर (!aपंचांगel_pwm)
		वापस -ENOMEM;

	mutex_init(&aपंचांगel_pwm->isr_lock);
	aपंचांगel_pwm->data = of_device_get_match_data(&pdev->dev);
	aपंचांगel_pwm->updated_pwms = 0;

	aपंचांगel_pwm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(aपंचांगel_pwm->base))
		वापस PTR_ERR(aपंचांगel_pwm->base);

	aपंचांगel_pwm->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(aपंचांगel_pwm->clk))
		वापस PTR_ERR(aपंचांगel_pwm->clk);

	ret = clk_prepare(aपंचांगel_pwm->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to prepare PWM clock\n");
		वापस ret;
	पूर्ण

	aपंचांगel_pwm->chip.dev = &pdev->dev;
	aपंचांगel_pwm->chip.ops = &aपंचांगel_pwm_ops;
	aपंचांगel_pwm->chip.of_xlate = of_pwm_xlate_with_flags;
	aपंचांगel_pwm->chip.of_pwm_n_cells = 3;
	aपंचांगel_pwm->chip.npwm = 4;

	ret = pwmchip_add(&aपंचांगel_pwm->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add PWM chip %d\n", ret);
		जाओ unprepare_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, aपंचांगel_pwm);

	वापस ret;

unprepare_clk:
	clk_unprepare(aपंचांगel_pwm->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_pwm_chip *aपंचांगel_pwm = platक्रमm_get_drvdata(pdev);

	pwmchip_हटाओ(&aपंचांगel_pwm->chip);

	clk_unprepare(aपंचांगel_pwm->clk);
	mutex_destroy(&aपंचांगel_pwm->isr_lock);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_pwm_driver = अणु
	.driver = अणु
		.name = "atmel-pwm",
		.of_match_table = of_match_ptr(aपंचांगel_pwm_dt_ids),
	पूर्ण,
	.probe = aपंचांगel_pwm_probe,
	.हटाओ = aपंचांगel_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_pwm_driver);

MODULE_ALIAS("platform:atmel-pwm");
MODULE_AUTHOR("Bo Shen <voice.shen@atmel.com>");
MODULE_DESCRIPTION("Atmel PWM driver");
MODULE_LICENSE("GPL v2");
