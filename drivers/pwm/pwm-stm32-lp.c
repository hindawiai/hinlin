<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * STM32 Low-Power Timer PWM driver
 *
 * Copyright (C) STMicroelectronics 2017
 *
 * Author: Gerald Baeza <gerald.baeza@st.com>
 *
 * Inspired by Gerald Baeza's pwm-sपंचांग32 driver
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/mfd/sपंचांग32-lpसमयr.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

काष्ठा sपंचांग32_pwm_lp अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
पूर्ण;

अटल अंतरभूत काष्ठा sपंचांग32_pwm_lp *to_sपंचांग32_pwm_lp(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा sपंचांग32_pwm_lp, chip);
पूर्ण

/* STM32 Low-Power Timer is preceded by a configurable घातer-of-2 prescaler */
#घोषणा STM32_LPTIM_MAX_PRESCALER	128

अटल पूर्णांक sपंचांग32_pwm_lp_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा sपंचांग32_pwm_lp *priv = to_sपंचांग32_pwm_lp(chip);
	अचिन्हित दीर्घ दीर्घ prd, भाग, dty;
	काष्ठा pwm_state cstate;
	u32 val, mask, cfgr, presc = 0;
	bool reenable;
	पूर्णांक ret;

	pwm_get_state(pwm, &cstate);
	reenable = !cstate.enabled;

	अगर (!state->enabled) अणु
		अगर (cstate.enabled) अणु
			/* Disable LP समयr */
			ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CR, 0);
			अगर (ret)
				वापस ret;
			/* disable घड़ी to PWM counter */
			clk_disable(priv->clk);
		पूर्ण
		वापस 0;
	पूर्ण

	/* Calculate the period and prescaler value */
	भाग = (अचिन्हित दीर्घ दीर्घ)clk_get_rate(priv->clk) * state->period;
	करो_भाग(भाग, NSEC_PER_SEC);
	अगर (!भाग) अणु
		/* Clock is too slow to achieve requested period. */
		dev_dbg(priv->chip.dev, "Can't reach %llu ns\n", state->period);
		वापस -EINVAL;
	पूर्ण

	prd = भाग;
	जबतक (भाग > STM32_LPTIM_MAX_ARR) अणु
		presc++;
		अगर ((1 << presc) > STM32_LPTIM_MAX_PRESCALER) अणु
			dev_err(priv->chip.dev, "max prescaler exceeded\n");
			वापस -EINVAL;
		पूर्ण
		भाग = prd >> presc;
	पूर्ण
	prd = भाग;

	/* Calculate the duty cycle */
	dty = prd * state->duty_cycle;
	करो_भाग(dty, state->period);

	अगर (!cstate.enabled) अणु
		/* enable घड़ी to drive PWM counter */
		ret = clk_enable(priv->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(priv->regmap, STM32_LPTIM_CFGR, &cfgr);
	अगर (ret)
		जाओ err;

	अगर ((FIELD_GET(STM32_LPTIM_PRESC, cfgr) != presc) ||
	    (FIELD_GET(STM32_LPTIM_WAVPOL, cfgr) != state->polarity)) अणु
		val = FIELD_PREP(STM32_LPTIM_PRESC, presc);
		val |= FIELD_PREP(STM32_LPTIM_WAVPOL, state->polarity);
		mask = STM32_LPTIM_PRESC | STM32_LPTIM_WAVPOL;

		/* Must disable LP समयr to modअगरy CFGR */
		reenable = true;
		ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CR, 0);
		अगर (ret)
			जाओ err;

		ret = regmap_update_bits(priv->regmap, STM32_LPTIM_CFGR, mask,
					 val);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (reenable) अणु
		/* Must (re)enable LP समयr to modअगरy CMP & ARR */
		ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CR,
				   STM32_LPTIM_ENABLE);
		अगर (ret)
			जाओ err;
	पूर्ण

	ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_ARR, prd - 1);
	अगर (ret)
		जाओ err;

	ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CMP, prd - (1 + dty));
	अगर (ret)
		जाओ err;

	/* ensure CMP & ARR रेजिस्टरs are properly written */
	ret = regmap_पढ़ो_poll_समयout(priv->regmap, STM32_LPTIM_ISR, val,
				       (val & STM32_LPTIM_CMPOK_ARROK),
				       100, 1000);
	अगर (ret) अणु
		dev_err(priv->chip.dev, "ARR/CMP registers write issue\n");
		जाओ err;
	पूर्ण
	ret = regmap_ग_लिखो(priv->regmap, STM32_LPTIM_ICR,
			   STM32_LPTIM_CMPOKCF_ARROKCF);
	अगर (ret)
		जाओ err;

	अगर (reenable) अणु
		/* Start LP समयr in continuous mode */
		ret = regmap_update_bits(priv->regmap, STM32_LPTIM_CR,
					 STM32_LPTIM_CNTSTRT,
					 STM32_LPTIM_CNTSTRT);
		अगर (ret) अणु
			regmap_ग_लिखो(priv->regmap, STM32_LPTIM_CR, 0);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	अगर (!cstate.enabled)
		clk_disable(priv->clk);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_pwm_lp_get_state(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm,
				   काष्ठा pwm_state *state)
अणु
	काष्ठा sपंचांग32_pwm_lp *priv = to_sपंचांग32_pwm_lp(chip);
	अचिन्हित दीर्घ rate = clk_get_rate(priv->clk);
	u32 val, presc, prd;
	u64 पंचांगp;

	regmap_पढ़ो(priv->regmap, STM32_LPTIM_CR, &val);
	state->enabled = !!FIELD_GET(STM32_LPTIM_ENABLE, val);
	/* Keep PWM counter घड़ी refcount in sync with PWM initial state */
	अगर (state->enabled)
		clk_enable(priv->clk);

	regmap_पढ़ो(priv->regmap, STM32_LPTIM_CFGR, &val);
	presc = FIELD_GET(STM32_LPTIM_PRESC, val);
	state->polarity = FIELD_GET(STM32_LPTIM_WAVPOL, val);

	regmap_पढ़ो(priv->regmap, STM32_LPTIM_ARR, &prd);
	पंचांगp = prd + 1;
	पंचांगp = (पंचांगp << presc) * NSEC_PER_SEC;
	state->period = DIV_ROUND_CLOSEST_ULL(पंचांगp, rate);

	regmap_पढ़ो(priv->regmap, STM32_LPTIM_CMP, &val);
	पंचांगp = prd - val;
	पंचांगp = (पंचांगp << presc) * NSEC_PER_SEC;
	state->duty_cycle = DIV_ROUND_CLOSEST_ULL(पंचांगp, rate);
पूर्ण

अटल स्थिर काष्ठा pwm_ops sपंचांग32_pwm_lp_ops = अणु
	.owner = THIS_MODULE,
	.apply = sपंचांग32_pwm_lp_apply,
	.get_state = sपंचांग32_pwm_lp_get_state,
पूर्ण;

अटल पूर्णांक sपंचांग32_pwm_lp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_lpसमयr *ddata = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sपंचांग32_pwm_lp *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->chip.dev = &pdev->dev;
	priv->chip.ops = &sपंचांग32_pwm_lp_ops;
	priv->chip.npwm = 1;
	priv->chip.of_xlate = of_pwm_xlate_with_flags;
	priv->chip.of_pwm_n_cells = 3;

	ret = pwmchip_add(&priv->chip);
	अगर (ret < 0)
		वापस ret;

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_pwm_lp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_pwm_lp *priv = platक्रमm_get_drvdata(pdev);

	pwm_disable(&priv->chip.pwms[0]);

	वापस pwmchip_हटाओ(&priv->chip);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_pwm_lp_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_pwm_lp *priv = dev_get_drvdata(dev);
	काष्ठा pwm_state state;

	pwm_get_state(&priv->chip.pwms[0], &state);
	अगर (state.enabled) अणु
		dev_err(dev, "The consumer didn't stop us (%s)\n",
			priv->chip.pwms[0].label);
		वापस -EBUSY;
	पूर्ण

	वापस pinctrl_pm_select_sleep_state(dev);
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_pwm_lp_resume(काष्ठा device *dev)
अणु
	वापस pinctrl_pm_select_शेष_state(dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_pwm_lp_pm_ops, sपंचांग32_pwm_lp_suspend,
			 sपंचांग32_pwm_lp_resume);

अटल स्थिर काष्ठा of_device_id sपंचांग32_pwm_lp_of_match[] = अणु
	अणु .compatible = "st,stm32-pwm-lp", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_pwm_lp_of_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_pwm_lp_driver = अणु
	.probe	= sपंचांग32_pwm_lp_probe,
	.हटाओ	= sपंचांग32_pwm_lp_हटाओ,
	.driver	= अणु
		.name = "stm32-pwm-lp",
		.of_match_table = of_match_ptr(sपंचांग32_pwm_lp_of_match),
		.pm = &sपंचांग32_pwm_lp_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_pwm_lp_driver);

MODULE_ALIAS("platform:stm32-pwm-lp");
MODULE_DESCRIPTION("STMicroelectronics STM32 PWM LP driver");
MODULE_LICENSE("GPL v2");
