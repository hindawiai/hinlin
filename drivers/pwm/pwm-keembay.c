<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel Keem Bay PWM driver
 *
 * Copyright (C) 2020 Intel Corporation
 * Authors: Lai Poey Seng <poey.seng.lai@पूर्णांकel.com>
 *          Vineetha G. Jaya Kumaran <vineetha.g.jaya.kumaran@पूर्णांकel.com>
 *
 * Limitations:
 * - Upon disabling a channel, the currently running
 *   period will not be completed. However, upon
 *   reconfiguration of the duty cycle/period, the
 *   currently running period will be completed first.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>

#घोषणा KMB_TOTAL_PWM_CHANNELS		6
#घोषणा KMB_PWM_COUNT_MAX		U16_MAX
#घोषणा KMB_PWM_EN_BIT			BIT(31)

/* Mask */
#घोषणा KMB_PWM_HIGH_MASK		GENMASK(31, 16)
#घोषणा KMB_PWM_LOW_MASK		GENMASK(15, 0)
#घोषणा KMB_PWM_LEADIN_MASK		GENMASK(30, 0)

/* PWM Register offset */
#घोषणा KMB_PWM_LEADIN_OFFSET(ch)	(0x00 + 4 * (ch))
#घोषणा KMB_PWM_HIGHLOW_OFFSET(ch)	(0x20 + 4 * (ch))

काष्ठा keembay_pwm अणु
	काष्ठा pwm_chip chip;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत काष्ठा keembay_pwm *to_keembay_pwm_dev(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा keembay_pwm, chip);
पूर्ण

अटल व्योम keembay_clk_unprepare(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक keembay_clk_enable(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(clk);
	अगर (ret)
		वापस ret;

	वापस devm_add_action_or_reset(dev, keembay_clk_unprepare, clk);
पूर्ण

/*
 * With gcc 10, CONFIG_CC_OPTIMIZE_FOR_SIZE and only "inline" instead of
 * "__always_inline" this fails to compile because the compiler करोesn't notice
 * क्रम all valid masks (e.g. KMB_PWM_LEADIN_MASK) that they are ok.
 */
अटल __always_अंतरभूत व्योम keembay_pwm_update_bits(काष्ठा keembay_pwm *priv, u32 mask,
					   u32 val, u32 offset)
अणु
	u32 buff = पढ़ोl(priv->base + offset);

	buff = u32_replace_bits(buff, val, mask);
	ग_लिखोl(buff, priv->base + offset);
पूर्ण

अटल व्योम keembay_pwm_enable(काष्ठा keembay_pwm *priv, पूर्णांक ch)
अणु
	keembay_pwm_update_bits(priv, KMB_PWM_EN_BIT, 1,
				KMB_PWM_LEADIN_OFFSET(ch));
पूर्ण

अटल व्योम keembay_pwm_disable(काष्ठा keembay_pwm *priv, पूर्णांक ch)
अणु
	keembay_pwm_update_bits(priv, KMB_PWM_EN_BIT, 0,
				KMB_PWM_LEADIN_OFFSET(ch));
पूर्ण

अटल व्योम keembay_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				  काष्ठा pwm_state *state)
अणु
	काष्ठा keembay_pwm *priv = to_keembay_pwm_dev(chip);
	अचिन्हित दीर्घ दीर्घ high, low;
	अचिन्हित दीर्घ clk_rate;
	u32 highlow;

	clk_rate = clk_get_rate(priv->clk);

	/* Read channel enabled status */
	highlow = पढ़ोl(priv->base + KMB_PWM_LEADIN_OFFSET(pwm->hwpwm));
	अगर (highlow & KMB_PWM_EN_BIT)
		state->enabled = true;
	अन्यथा
		state->enabled = false;

	/* Read period and duty cycle */
	highlow = पढ़ोl(priv->base + KMB_PWM_HIGHLOW_OFFSET(pwm->hwpwm));
	low = FIELD_GET(KMB_PWM_LOW_MASK, highlow) * NSEC_PER_SEC;
	high = FIELD_GET(KMB_PWM_HIGH_MASK, highlow) * NSEC_PER_SEC;
	state->duty_cycle = DIV_ROUND_UP_ULL(high, clk_rate);
	state->period = DIV_ROUND_UP_ULL(high + low, clk_rate);
	state->polarity = PWM_POLARITY_NORMAL;
पूर्ण

अटल पूर्णांक keembay_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा keembay_pwm *priv = to_keembay_pwm_dev(chip);
	काष्ठा pwm_state current_state;
	अचिन्हित दीर्घ दीर्घ भाग;
	अचिन्हित दीर्घ clk_rate;
	u32 pwm_count = 0;
	u16 high, low;

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	/*
	 * Configure the pwm repeat count as infinite at (15:0) and leadin
	 * low समय as 0 at (30:16), which is in terms of घड़ी cycles.
	 */
	keembay_pwm_update_bits(priv, KMB_PWM_LEADIN_MASK, 0,
				KMB_PWM_LEADIN_OFFSET(pwm->hwpwm));

	keembay_pwm_get_state(chip, pwm, &current_state);

	अगर (!state->enabled) अणु
		अगर (current_state.enabled)
			keembay_pwm_disable(priv, pwm->hwpwm);
		वापस 0;
	पूर्ण

	/*
	 * The upper 16 bits and lower 16 bits of the KMB_PWM_HIGHLOW_OFFSET
	 * रेजिस्टर contain the high समय and low समय of waveक्रमm accordingly.
	 * All the values are in terms of घड़ी cycles.
	 */

	clk_rate = clk_get_rate(priv->clk);
	भाग = clk_rate * state->duty_cycle;
	भाग = DIV_ROUND_DOWN_ULL(भाग, NSEC_PER_SEC);
	अगर (भाग > KMB_PWM_COUNT_MAX)
		वापस -दुस्फल;

	high = भाग;
	भाग = clk_rate * state->period;
	भाग = DIV_ROUND_DOWN_ULL(भाग, NSEC_PER_SEC);
	भाग = भाग - high;
	अगर (भाग > KMB_PWM_COUNT_MAX)
		वापस -दुस्फल;

	low = भाग;

	pwm_count = FIELD_PREP(KMB_PWM_HIGH_MASK, high) |
		    FIELD_PREP(KMB_PWM_LOW_MASK, low);

	ग_लिखोl(pwm_count, priv->base + KMB_PWM_HIGHLOW_OFFSET(pwm->hwpwm));

	अगर (state->enabled && !current_state.enabled)
		keembay_pwm_enable(priv, pwm->hwpwm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops keembay_pwm_ops = अणु
	.owner = THIS_MODULE,
	.apply = keembay_pwm_apply,
	.get_state = keembay_pwm_get_state,
पूर्ण;

अटल पूर्णांक keembay_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा keembay_pwm *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस dev_err_probe(dev, PTR_ERR(priv->clk), "Failed to get clock\n");

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	ret = keembay_clk_enable(dev, priv->clk);
	अगर (ret)
		वापस ret;

	priv->chip.dev = dev;
	priv->chip.ops = &keembay_pwm_ops;
	priv->chip.npwm = KMB_TOTAL_PWM_CHANNELS;

	ret = pwmchip_add(&priv->chip);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "Failed to add PWM chip\n");

	platक्रमm_set_drvdata(pdev, priv);

	वापस 0;
पूर्ण

अटल पूर्णांक keembay_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा keembay_pwm *priv = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&priv->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id keembay_pwm_of_match[] = अणु
	अणु .compatible = "intel,keembay-pwm" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, keembay_pwm_of_match);

अटल काष्ठा platक्रमm_driver keembay_pwm_driver = अणु
	.probe	= keembay_pwm_probe,
	.हटाओ	= keembay_pwm_हटाओ,
	.driver	= अणु
		.name = "pwm-keembay",
		.of_match_table = keembay_pwm_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(keembay_pwm_driver);

MODULE_ALIAS("platform:pwm-keembay");
MODULE_DESCRIPTION("Intel Keem Bay PWM driver");
MODULE_LICENSE("GPL v2");
