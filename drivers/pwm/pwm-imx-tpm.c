<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018-2019 NXP.
 *
 * Limitations:
 * - The TPM counter and period counter are shared between
 *   multiple channels, so all channels should use same period
 *   settings.
 * - Changes to polarity cannot be latched at the समय of the
 *   next period start.
 * - Changing period and duty cycle together isn't atomic,
 *   with the wrong timing it might happen that a period is
 *   produced with old duty cycle but new period settings.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा PWM_IMX_TPM_PARAM	0x4
#घोषणा PWM_IMX_TPM_GLOBAL	0x8
#घोषणा PWM_IMX_TPM_SC		0x10
#घोषणा PWM_IMX_TPM_CNT		0x14
#घोषणा PWM_IMX_TPM_MOD		0x18
#घोषणा PWM_IMX_TPM_CnSC(n)	(0x20 + (n) * 0x8)
#घोषणा PWM_IMX_TPM_CnV(n)	(0x24 + (n) * 0x8)

#घोषणा PWM_IMX_TPM_PARAM_CHAN			GENMASK(7, 0)

#घोषणा PWM_IMX_TPM_SC_PS			GENMASK(2, 0)
#घोषणा PWM_IMX_TPM_SC_CMOD			GENMASK(4, 3)
#घोषणा PWM_IMX_TPM_SC_CMOD_INC_EVERY_CLK	FIELD_PREP(PWM_IMX_TPM_SC_CMOD, 1)
#घोषणा PWM_IMX_TPM_SC_CPWMS			BIT(5)

#घोषणा PWM_IMX_TPM_CnSC_CHF	BIT(7)
#घोषणा PWM_IMX_TPM_CnSC_MSB	BIT(5)
#घोषणा PWM_IMX_TPM_CnSC_MSA	BIT(4)

/*
 * The reference manual describes this field as two separate bits. The
 * semantic of the two bits isn't orthogonal though, so they are treated
 * together as a 2-bit field here.
 */
#घोषणा PWM_IMX_TPM_CnSC_ELS	GENMASK(3, 2)
#घोषणा PWM_IMX_TPM_CnSC_ELS_INVERSED	FIELD_PREP(PWM_IMX_TPM_CnSC_ELS, 1)
#घोषणा PWM_IMX_TPM_CnSC_ELS_NORMAL	FIELD_PREP(PWM_IMX_TPM_CnSC_ELS, 2)


#घोषणा PWM_IMX_TPM_MOD_WIDTH	16
#घोषणा PWM_IMX_TPM_MOD_MOD	GENMASK(PWM_IMX_TPM_MOD_WIDTH - 1, 0)

काष्ठा imx_tpm_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	काष्ठा mutex lock;
	u32 user_count;
	u32 enable_count;
	u32 real_period;
पूर्ण;

काष्ठा imx_tpm_pwm_param अणु
	u8 prescale;
	u32 mod;
	u32 val;
पूर्ण;

अटल अंतरभूत काष्ठा imx_tpm_pwm_chip *
to_imx_tpm_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा imx_tpm_pwm_chip, chip);
पूर्ण

/*
 * This function determines क्रम a given pwm_state *state that a consumer
 * might request the pwm_state *real_state that eventually is implemented
 * by the hardware and the necessary रेजिस्टर values (in *p) to achieve
 * this.
 */
अटल पूर्णांक pwm_imx_tpm_round_state(काष्ठा pwm_chip *chip,
				   काष्ठा imx_tpm_pwm_param *p,
				   काष्ठा pwm_state *real_state,
				   स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	u32 rate, prescale, period_count, घड़ी_unit;
	u64 पंचांगp;

	rate = clk_get_rate(tpm->clk);
	पंचांगp = (u64)state->period * rate;
	घड़ी_unit = DIV_ROUND_CLOSEST_ULL(पंचांगp, NSEC_PER_SEC);
	अगर (घड़ी_unit <= PWM_IMX_TPM_MOD_MOD)
		prescale = 0;
	अन्यथा
		prescale = ilog2(घड़ी_unit) + 1 - PWM_IMX_TPM_MOD_WIDTH;

	अगर ((!FIELD_FIT(PWM_IMX_TPM_SC_PS, prescale)))
		वापस -दुस्फल;
	p->prescale = prescale;

	period_count = (घड़ी_unit + ((1 << prescale) >> 1)) >> prescale;
	p->mod = period_count;

	/* calculate real period HW can support */
	पंचांगp = (u64)period_count << prescale;
	पंचांगp *= NSEC_PER_SEC;
	real_state->period = DIV_ROUND_CLOSEST_ULL(पंचांगp, rate);

	/*
	 * अगर eventually the PWM output is inactive, either
	 * duty cycle is 0 or status is disabled, need to
	 * make sure the output pin is inactive.
	 */
	अगर (!state->enabled)
		real_state->duty_cycle = 0;
	अन्यथा
		real_state->duty_cycle = state->duty_cycle;

	पंचांगp = (u64)p->mod * real_state->duty_cycle;
	p->val = DIV64_U64_ROUND_CLOSEST(पंचांगp, real_state->period);

	real_state->polarity = state->polarity;
	real_state->enabled = state->enabled;

	वापस 0;
पूर्ण

अटल व्योम pwm_imx_tpm_get_state(काष्ठा pwm_chip *chip,
				  काष्ठा pwm_device *pwm,
				  काष्ठा pwm_state *state)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	u32 rate, val, prescale;
	u64 पंचांगp;

	/* get period */
	state->period = tpm->real_period;

	/* get duty cycle */
	rate = clk_get_rate(tpm->clk);
	val = पढ़ोl(tpm->base + PWM_IMX_TPM_SC);
	prescale = FIELD_GET(PWM_IMX_TPM_SC_PS, val);
	पंचांगp = पढ़ोl(tpm->base + PWM_IMX_TPM_CnV(pwm->hwpwm));
	पंचांगp = (पंचांगp << prescale) * NSEC_PER_SEC;
	state->duty_cycle = DIV_ROUND_CLOSEST_ULL(पंचांगp, rate);

	/* get polarity */
	val = पढ़ोl(tpm->base + PWM_IMX_TPM_CnSC(pwm->hwpwm));
	अगर ((val & PWM_IMX_TPM_CnSC_ELS) == PWM_IMX_TPM_CnSC_ELS_INVERSED)
		state->polarity = PWM_POLARITY_INVERSED;
	अन्यथा
		/*
		 * Assume reserved values (2b00 and 2b11) to yield
		 * normal polarity.
		 */
		state->polarity = PWM_POLARITY_NORMAL;

	/* get channel status */
	state->enabled = FIELD_GET(PWM_IMX_TPM_CnSC_ELS, val) ? true : false;
पूर्ण

/* this function is supposed to be called with mutex hold */
अटल पूर्णांक pwm_imx_tpm_apply_hw(काष्ठा pwm_chip *chip,
				काष्ठा imx_tpm_pwm_param *p,
				काष्ठा pwm_state *state,
				काष्ठा pwm_device *pwm)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	bool period_update = false;
	bool duty_update = false;
	u32 val, cmod, cur_prescale;
	अचिन्हित दीर्घ समयout;
	काष्ठा pwm_state c;

	अगर (state->period != tpm->real_period) अणु
		/*
		 * TPM counter is shared by multiple channels, so
		 * prescale and period can NOT be modअगरied when
		 * there are multiple channels in use with dअगरferent
		 * period settings.
		 */
		अगर (tpm->user_count > 1)
			वापस -EBUSY;

		val = पढ़ोl(tpm->base + PWM_IMX_TPM_SC);
		cmod = FIELD_GET(PWM_IMX_TPM_SC_CMOD, val);
		cur_prescale = FIELD_GET(PWM_IMX_TPM_SC_PS, val);
		अगर (cmod && cur_prescale != p->prescale)
			वापस -EBUSY;

		/* set TPM counter prescale */
		val &= ~PWM_IMX_TPM_SC_PS;
		val |= FIELD_PREP(PWM_IMX_TPM_SC_PS, p->prescale);
		ग_लिखोl(val, tpm->base + PWM_IMX_TPM_SC);

		/*
		 * set period count:
		 * अगर the PWM is disabled (CMOD[1:0] = 2b00), then MOD रेजिस्टर
		 * is updated when MOD रेजिस्टर is written.
		 *
		 * अगर the PWM is enabled (CMOD[1:0] ै	  2b00), the period length
		 * is latched पूर्णांकo hardware when the next period starts.
		 */
		ग_लिखोl(p->mod, tpm->base + PWM_IMX_TPM_MOD);
		tpm->real_period = state->period;
		period_update = true;
	पूर्ण

	pwm_imx_tpm_get_state(chip, pwm, &c);

	/* polarity is NOT allowed to be changed अगर PWM is active */
	अगर (c.enabled && c.polarity != state->polarity)
		वापस -EBUSY;

	अगर (state->duty_cycle != c.duty_cycle) अणु
		/*
		 * set channel value:
		 * अगर the PWM is disabled (CMOD[1:0] = 2b00), then CnV रेजिस्टर
		 * is updated when CnV रेजिस्टर is written.
		 *
		 * अगर the PWM is enabled (CMOD[1:0] ै	  2b00), the duty length
		 * is latched पूर्णांकo hardware when the next period starts.
		 */
		ग_लिखोl(p->val, tpm->base + PWM_IMX_TPM_CnV(pwm->hwpwm));
		duty_update = true;
	पूर्ण

	/* make sure MOD & CnV रेजिस्टरs are updated */
	अगर (period_update || duty_update) अणु
		समयout = jअगरfies + msecs_to_jअगरfies(tpm->real_period /
						     NSEC_PER_MSEC + 1);
		जबतक (पढ़ोl(tpm->base + PWM_IMX_TPM_MOD) != p->mod
		       || पढ़ोl(tpm->base + PWM_IMX_TPM_CnV(pwm->hwpwm))
		       != p->val) अणु
			अगर (समय_after(jअगरfies, समयout))
				वापस -ETIME;
			cpu_relax();
		पूर्ण
	पूर्ण

	/*
	 * polarity settings will enabled/disable output status
	 * immediately, so अगर the channel is disabled, need to
	 * make sure MSA/MSB/ELS are set to 0 which means channel
	 * disabled.
	 */
	val = पढ़ोl(tpm->base + PWM_IMX_TPM_CnSC(pwm->hwpwm));
	val &= ~(PWM_IMX_TPM_CnSC_ELS | PWM_IMX_TPM_CnSC_MSA |
		 PWM_IMX_TPM_CnSC_MSB);
	अगर (state->enabled) अणु
		/*
		 * set polarity (क्रम edge-aligned PWM modes)
		 *
		 * ELS[1:0] = 2b10 yields normal polarity behaviour,
		 * ELS[1:0] = 2b01 yields inversed polarity.
		 * The other values are reserved.
		 */
		val |= PWM_IMX_TPM_CnSC_MSB;
		val |= (state->polarity == PWM_POLARITY_NORMAL) ?
			PWM_IMX_TPM_CnSC_ELS_NORMAL :
			PWM_IMX_TPM_CnSC_ELS_INVERSED;
	पूर्ण
	ग_लिखोl(val, tpm->base + PWM_IMX_TPM_CnSC(pwm->hwpwm));

	/* control the counter status */
	अगर (state->enabled != c.enabled) अणु
		val = पढ़ोl(tpm->base + PWM_IMX_TPM_SC);
		अगर (state->enabled) अणु
			अगर (++tpm->enable_count == 1)
				val |= PWM_IMX_TPM_SC_CMOD_INC_EVERY_CLK;
		पूर्ण अन्यथा अणु
			अगर (--tpm->enable_count == 0)
				val &= ~PWM_IMX_TPM_SC_CMOD;
		पूर्ण
		ग_लिखोl(val, tpm->base + PWM_IMX_TPM_SC);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_imx_tpm_apply(काष्ठा pwm_chip *chip,
			     काष्ठा pwm_device *pwm,
			     स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);
	काष्ठा imx_tpm_pwm_param param;
	काष्ठा pwm_state real_state;
	पूर्णांक ret;

	ret = pwm_imx_tpm_round_state(chip, &param, &real_state, state);
	अगर (ret)
		वापस ret;

	mutex_lock(&tpm->lock);
	ret = pwm_imx_tpm_apply_hw(chip, &param, &real_state, pwm);
	mutex_unlock(&tpm->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pwm_imx_tpm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);

	mutex_lock(&tpm->lock);
	tpm->user_count++;
	mutex_unlock(&tpm->lock);

	वापस 0;
पूर्ण

अटल व्योम pwm_imx_tpm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = to_imx_tpm_pwm_chip(chip);

	mutex_lock(&tpm->lock);
	tpm->user_count--;
	mutex_unlock(&tpm->lock);
पूर्ण

अटल स्थिर काष्ठा pwm_ops imx_tpm_pwm_ops = अणु
	.request = pwm_imx_tpm_request,
	.मुक्त = pwm_imx_tpm_मुक्त,
	.get_state = pwm_imx_tpm_get_state,
	.apply = pwm_imx_tpm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pwm_imx_tpm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm;
	पूर्णांक ret;
	u32 val;

	tpm = devm_kzalloc(&pdev->dev, माप(*tpm), GFP_KERNEL);
	अगर (!tpm)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, tpm);

	tpm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tpm->base))
		वापस PTR_ERR(tpm->base);

	tpm->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(tpm->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(tpm->clk),
				     "failed to get PWM clock\n");

	ret = clk_prepare_enable(tpm->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"failed to prepare or enable clock: %d\n", ret);
		वापस ret;
	पूर्ण

	tpm->chip.dev = &pdev->dev;
	tpm->chip.ops = &imx_tpm_pwm_ops;
	tpm->chip.of_xlate = of_pwm_xlate_with_flags;
	tpm->chip.of_pwm_n_cells = 3;

	/* get number of channels */
	val = पढ़ोl(tpm->base + PWM_IMX_TPM_PARAM);
	tpm->chip.npwm = FIELD_GET(PWM_IMX_TPM_PARAM_CHAN, val);

	mutex_init(&tpm->lock);

	ret = pwmchip_add(&tpm->chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);
		clk_disable_unprepare(tpm->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pwm_imx_tpm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret = pwmchip_हटाओ(&tpm->chip);

	clk_disable_unprepare(tpm->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_imx_tpm_suspend(काष्ठा device *dev)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = dev_get_drvdata(dev);

	अगर (tpm->enable_count > 0)
		वापस -EBUSY;

	clk_disable_unprepare(tpm->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pwm_imx_tpm_resume(काष्ठा device *dev)
अणु
	काष्ठा imx_tpm_pwm_chip *tpm = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	ret = clk_prepare_enable(tpm->clk);
	अगर (ret)
		dev_err(dev, "failed to prepare or enable clock: %d\n", ret);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(imx_tpm_pwm_pm,
			 pwm_imx_tpm_suspend, pwm_imx_tpm_resume);

अटल स्थिर काष्ठा of_device_id imx_tpm_pwm_dt_ids[] = अणु
	अणु .compatible = "fsl,imx7ulp-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_tpm_pwm_dt_ids);

अटल काष्ठा platक्रमm_driver imx_tpm_pwm_driver = अणु
	.driver = अणु
		.name = "imx7ulp-tpm-pwm",
		.of_match_table = imx_tpm_pwm_dt_ids,
		.pm = &imx_tpm_pwm_pm,
	पूर्ण,
	.probe	= pwm_imx_tpm_probe,
	.हटाओ = pwm_imx_tpm_हटाओ,
पूर्ण;
module_platक्रमm_driver(imx_tpm_pwm_driver);

MODULE_AUTHOR("Anson Huang <Anson.Huang@nxp.com>");
MODULE_DESCRIPTION("i.MX TPM PWM Driver");
MODULE_LICENSE("GPL v2");
