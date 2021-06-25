<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017-2018 SiFive
 * For SiFive's PWM IP block करोcumentation please refer Chapter 14 of
 * Reference Manual : https://अटल.dev.sअगरive.com/FU540-C000-v1.0.pdf
 *
 * Limitations:
 * - When changing both duty cycle and period, we cannot prevent in
 *   software that the output might produce a period with mixed
 *   settings (new period length and old duty cycle).
 * - The hardware cannot generate a 100% duty cycle.
 * - The hardware generates only inverted output.
 */
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitfield.h>

/* Register offsets */
#घोषणा PWM_SIFIVE_PWMCFG		0x0
#घोषणा PWM_SIFIVE_PWMCOUNT		0x8
#घोषणा PWM_SIFIVE_PWMS			0x10
#घोषणा PWM_SIFIVE_PWMCMP0		0x20

/* PWMCFG fields */
#घोषणा PWM_SIFIVE_PWMCFG_SCALE		GENMASK(3, 0)
#घोषणा PWM_SIFIVE_PWMCFG_STICKY	BIT(8)
#घोषणा PWM_SIFIVE_PWMCFG_ZERO_CMP	BIT(9)
#घोषणा PWM_SIFIVE_PWMCFG_DEGLITCH	BIT(10)
#घोषणा PWM_SIFIVE_PWMCFG_EN_ALWAYS	BIT(12)
#घोषणा PWM_SIFIVE_PWMCFG_EN_ONCE	BIT(13)
#घोषणा PWM_SIFIVE_PWMCFG_CENTER	BIT(16)
#घोषणा PWM_SIFIVE_PWMCFG_GANG		BIT(24)
#घोषणा PWM_SIFIVE_PWMCFG_IP		BIT(28)

/* PWM_SIFIVE_SIZE_PWMCMP is used to calculate offset क्रम pwmcmpX रेजिस्टरs */
#घोषणा PWM_SIFIVE_SIZE_PWMCMP		4
#घोषणा PWM_SIFIVE_CMPWIDTH		16
#घोषणा PWM_SIFIVE_DEFAULT_PERIOD	10000000

काष्ठा pwm_sअगरive_ddata अणु
	काष्ठा pwm_chip	chip;
	काष्ठा mutex lock; /* lock to protect user_count */
	काष्ठा notअगरier_block notअगरier;
	काष्ठा clk *clk;
	व्योम __iomem *regs;
	अचिन्हित पूर्णांक real_period;
	अचिन्हित पूर्णांक approx_period;
	पूर्णांक user_count;
पूर्ण;

अटल अंतरभूत
काष्ठा pwm_sअगरive_ddata *pwm_sअगरive_chip_to_ddata(काष्ठा pwm_chip *c)
अणु
	वापस container_of(c, काष्ठा pwm_sअगरive_ddata, chip);
पूर्ण

अटल पूर्णांक pwm_sअगरive_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_sअगरive_ddata *ddata = pwm_sअगरive_chip_to_ddata(chip);

	mutex_lock(&ddata->lock);
	ddata->user_count++;
	mutex_unlock(&ddata->lock);

	वापस 0;
पूर्ण

अटल व्योम pwm_sअगरive_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_sअगरive_ddata *ddata = pwm_sअगरive_chip_to_ddata(chip);

	mutex_lock(&ddata->lock);
	ddata->user_count--;
	mutex_unlock(&ddata->lock);
पूर्ण

अटल व्योम pwm_sअगरive_update_घड़ी(काष्ठा pwm_sअगरive_ddata *ddata,
				    अचिन्हित दीर्घ rate)
अणु
	अचिन्हित दीर्घ दीर्घ num;
	अचिन्हित दीर्घ scale_घात;
	पूर्णांक scale;
	u32 val;
	/*
	 * The PWM unit is used with pwmzerocmp=0, so the only way to modअगरy the
	 * period length is using pwmscale which provides the number of bits the
	 * counter is shअगरted beक्रमe being feed to the comparators. A period
	 * lasts (1 << (PWM_SIFIVE_CMPWIDTH + pwmscale)) घड़ी ticks.
	 * (1 << (PWM_SIFIVE_CMPWIDTH + scale)) * 10^9/rate = period
	 */
	scale_घात = भाग64_ul(ddata->approx_period * (u64)rate, NSEC_PER_SEC);
	scale = clamp(ilog2(scale_घात) - PWM_SIFIVE_CMPWIDTH, 0, 0xf);

	val = PWM_SIFIVE_PWMCFG_EN_ALWAYS |
	      FIELD_PREP(PWM_SIFIVE_PWMCFG_SCALE, scale);
	ग_लिखोl(val, ddata->regs + PWM_SIFIVE_PWMCFG);

	/* As scale <= 15 the shअगरt operation cannot overflow. */
	num = (अचिन्हित दीर्घ दीर्घ)NSEC_PER_SEC << (PWM_SIFIVE_CMPWIDTH + scale);
	ddata->real_period = भाग64_ul(num, rate);
	dev_dbg(ddata->chip.dev,
		"New real_period = %u ns\n", ddata->real_period);
पूर्ण

अटल व्योम pwm_sअगरive_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				 काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_sअगरive_ddata *ddata = pwm_sअगरive_chip_to_ddata(chip);
	u32 duty, val;

	duty = पढ़ोl(ddata->regs + PWM_SIFIVE_PWMCMP0 +
		     pwm->hwpwm * PWM_SIFIVE_SIZE_PWMCMP);

	state->enabled = duty > 0;

	val = पढ़ोl(ddata->regs + PWM_SIFIVE_PWMCFG);
	अगर (!(val & PWM_SIFIVE_PWMCFG_EN_ALWAYS))
		state->enabled = false;

	state->period = ddata->real_period;
	state->duty_cycle =
		(u64)duty * ddata->real_period >> PWM_SIFIVE_CMPWIDTH;
	state->polarity = PWM_POLARITY_INVERSED;
पूर्ण

अटल पूर्णांक pwm_sअगरive_enable(काष्ठा pwm_chip *chip, bool enable)
अणु
	काष्ठा pwm_sअगरive_ddata *ddata = pwm_sअगरive_chip_to_ddata(chip);
	पूर्णांक ret;

	अगर (enable) अणु
		ret = clk_enable(ddata->clk);
		अगर (ret) अणु
			dev_err(ddata->chip.dev, "Enable clk failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!enable)
		clk_disable(ddata->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_sअगरive_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			    स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_sअगरive_ddata *ddata = pwm_sअगरive_chip_to_ddata(chip);
	काष्ठा pwm_state cur_state;
	अचिन्हित पूर्णांक duty_cycle;
	अचिन्हित दीर्घ दीर्घ num;
	bool enabled;
	पूर्णांक ret = 0;
	u32 frac;

	अगर (state->polarity != PWM_POLARITY_INVERSED)
		वापस -EINVAL;

	ret = clk_enable(ddata->clk);
	अगर (ret) अणु
		dev_err(ddata->chip.dev, "Enable clk failed\n");
		वापस ret;
	पूर्ण

	mutex_lock(&ddata->lock);
	cur_state = pwm->state;
	enabled = cur_state.enabled;

	duty_cycle = state->duty_cycle;
	अगर (!state->enabled)
		duty_cycle = 0;

	/*
	 * The problem of output producing mixed setting as mentioned at top,
	 * occurs here. To minimize the winकरोw क्रम this problem, we are
	 * calculating the रेजिस्टर values first and then writing them
	 * consecutively
	 */
	num = (u64)duty_cycle * (1U << PWM_SIFIVE_CMPWIDTH);
	frac = DIV64_U64_ROUND_CLOSEST(num, state->period);
	/* The hardware cannot generate a 100% duty cycle */
	frac = min(frac, (1U << PWM_SIFIVE_CMPWIDTH) - 1);

	अगर (state->period != ddata->approx_period) अणु
		अगर (ddata->user_count != 1) अणु
			ret = -EBUSY;
			जाओ निकास;
		पूर्ण
		ddata->approx_period = state->period;
		pwm_sअगरive_update_घड़ी(ddata, clk_get_rate(ddata->clk));
	पूर्ण

	ग_लिखोl(frac, ddata->regs + PWM_SIFIVE_PWMCMP0 +
	       pwm->hwpwm * PWM_SIFIVE_SIZE_PWMCMP);

	अगर (state->enabled != enabled)
		pwm_sअगरive_enable(chip, state->enabled);

निकास:
	clk_disable(ddata->clk);
	mutex_unlock(&ddata->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops pwm_sअगरive_ops = अणु
	.request = pwm_sअगरive_request,
	.मुक्त = pwm_sअगरive_मुक्त,
	.get_state = pwm_sअगरive_get_state,
	.apply = pwm_sअगरive_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक pwm_sअगरive_घड़ी_notअगरier(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा pwm_sअगरive_ddata *ddata =
		container_of(nb, काष्ठा pwm_sअगरive_ddata, notअगरier);

	अगर (event == POST_RATE_CHANGE)
		pwm_sअगरive_update_घड़ी(ddata, ndata->new_rate);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक pwm_sअगरive_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा pwm_sअगरive_ddata *ddata;
	काष्ठा pwm_chip *chip;
	पूर्णांक ret;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	mutex_init(&ddata->lock);
	chip = &ddata->chip;
	chip->dev = dev;
	chip->ops = &pwm_sअगरive_ops;
	chip->of_xlate = of_pwm_xlate_with_flags;
	chip->of_pwm_n_cells = 3;
	chip->npwm = 4;

	ddata->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ddata->regs))
		वापस PTR_ERR(ddata->regs);

	ddata->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ddata->clk))
		वापस dev_err_probe(dev, PTR_ERR(ddata->clk),
				     "Unable to find controller clock\n");

	ret = clk_prepare_enable(ddata->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable clock for pwm: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Watch क्रम changes to underlying घड़ी frequency */
	ddata->notअगरier.notअगरier_call = pwm_sअगरive_घड़ी_notअगरier;
	ret = clk_notअगरier_रेजिस्टर(ddata->clk, &ddata->notअगरier);
	अगर (ret) अणु
		dev_err(dev, "failed to register clock notifier: %d\n", ret);
		जाओ disable_clk;
	पूर्ण

	ret = pwmchip_add(chip);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot register PWM: %d\n", ret);
		जाओ unरेजिस्टर_clk;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ddata);
	dev_dbg(dev, "SiFive PWM chip registered %d PWMs\n", chip->npwm);

	वापस 0;

unरेजिस्टर_clk:
	clk_notअगरier_unरेजिस्टर(ddata->clk, &ddata->notअगरier);
disable_clk:
	clk_disable_unprepare(ddata->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक pwm_sअगरive_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा pwm_sअगरive_ddata *ddata = platक्रमm_get_drvdata(dev);
	bool is_enabled = false;
	काष्ठा pwm_device *pwm;
	पूर्णांक ret, ch;

	क्रम (ch = 0; ch < ddata->chip.npwm; ch++) अणु
		pwm = &ddata->chip.pwms[ch];
		अगर (pwm->state.enabled) अणु
			is_enabled = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (is_enabled)
		clk_disable(ddata->clk);

	clk_disable_unprepare(ddata->clk);
	ret = pwmchip_हटाओ(&ddata->chip);
	clk_notअगरier_unरेजिस्टर(ddata->clk, &ddata->notअगरier);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id pwm_sअगरive_of_match[] = अणु
	अणु .compatible = "sifive,pwm0" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_sअगरive_of_match);

अटल काष्ठा platक्रमm_driver pwm_sअगरive_driver = अणु
	.probe = pwm_sअगरive_probe,
	.हटाओ = pwm_sअगरive_हटाओ,
	.driver = अणु
		.name = "pwm-sifive",
		.of_match_table = pwm_sअगरive_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pwm_sअगरive_driver);

MODULE_DESCRIPTION("SiFive PWM driver");
MODULE_LICENSE("GPL v2");
