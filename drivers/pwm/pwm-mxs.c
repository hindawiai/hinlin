<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांगp_device.h>

#घोषणा SET	0x4
#घोषणा CLR	0x8
#घोषणा TOG	0xc

#घोषणा PWM_CTRL		0x0
#घोषणा PWM_ACTIVE0		0x10
#घोषणा PWM_PERIOD0		0x20
#घोषणा  PERIOD_PERIOD(p)	((p) & 0xffff)
#घोषणा  PERIOD_PERIOD_MAX	0x10000
#घोषणा  PERIOD_ACTIVE_HIGH	(3 << 16)
#घोषणा  PERIOD_ACTIVE_LOW	(2 << 16)
#घोषणा  PERIOD_INACTIVE_HIGH	(3 << 18)
#घोषणा  PERIOD_INACTIVE_LOW	(2 << 18)
#घोषणा  PERIOD_POLARITY_NORMAL	(PERIOD_ACTIVE_HIGH | PERIOD_INACTIVE_LOW)
#घोषणा  PERIOD_POLARITY_INVERSE	(PERIOD_ACTIVE_LOW | PERIOD_INACTIVE_HIGH)
#घोषणा  PERIOD_CDIV(भाग)	(((भाग) & 0x7) << 20)
#घोषणा  PERIOD_CDIV_MAX	8

अटल स्थिर u8 cभाग_shअगरt[PERIOD_CDIV_MAX] = अणु
	0, 1, 2, 3, 4, 6, 8, 10
पूर्ण;

काष्ठा mxs_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *clk;
	व्योम __iomem *base;
पूर्ण;

#घोषणा to_mxs_pwm_chip(_chip) container_of(_chip, काष्ठा mxs_pwm_chip, chip)

अटल पूर्णांक mxs_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			 स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा mxs_pwm_chip *mxs = to_mxs_pwm_chip(chip);
	पूर्णांक ret, भाग = 0;
	अचिन्हित पूर्णांक period_cycles, duty_cycles;
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ दीर्घ c;
	अचिन्हित पूर्णांक pol_bits;

	/*
	 * If the PWM channel is disabled, make sure to turn on the
	 * घड़ी beक्रमe calling clk_get_rate() and writing to the
	 * रेजिस्टरs. Otherwise, just keep it enabled.
	 */
	अगर (!pwm_is_enabled(pwm)) अणु
		ret = clk_prepare_enable(mxs->clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!state->enabled && pwm_is_enabled(pwm))
		ग_लिखोl(1 << pwm->hwpwm, mxs->base + PWM_CTRL + CLR);

	rate = clk_get_rate(mxs->clk);
	जबतक (1) अणु
		c = rate >> cभाग_shअगरt[भाग];
		c = c * state->period;
		करो_भाग(c, 1000000000);
		अगर (c < PERIOD_PERIOD_MAX)
			अवरोध;
		भाग++;
		अगर (भाग >= PERIOD_CDIV_MAX)
			वापस -EINVAL;
	पूर्ण

	period_cycles = c;
	c *= state->duty_cycle;
	करो_भाग(c, state->period);
	duty_cycles = c;

	/*
	 * The data sheet the says रेजिस्टरs must be written to in
	 * this order (ACTIVEn, then PERIODn). Also, the new settings
	 * only take effect at the beginning of a new period, aव्योमing
	 * glitches.
	 */

	pol_bits = state->polarity == PWM_POLARITY_NORMAL ?
		PERIOD_POLARITY_NORMAL : PERIOD_POLARITY_INVERSE;
	ग_लिखोl(duty_cycles << 16,
	       mxs->base + PWM_ACTIVE0 + pwm->hwpwm * 0x20);
	ग_लिखोl(PERIOD_PERIOD(period_cycles) | pol_bits | PERIOD_CDIV(भाग),
	       mxs->base + PWM_PERIOD0 + pwm->hwpwm * 0x20);

	अगर (state->enabled) अणु
		अगर (!pwm_is_enabled(pwm)) अणु
			/*
			 * The घड़ी was enabled above. Just enable
			 * the channel in the control रेजिस्टर.
			 */
			ग_लिखोl(1 << pwm->hwpwm, mxs->base + PWM_CTRL + SET);
		पूर्ण
	पूर्ण अन्यथा अणु
		clk_disable_unprepare(mxs->clk);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops mxs_pwm_ops = अणु
	.apply = mxs_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक mxs_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mxs_pwm_chip *mxs;
	पूर्णांक ret;

	mxs = devm_kzalloc(&pdev->dev, माप(*mxs), GFP_KERNEL);
	अगर (!mxs)
		वापस -ENOMEM;

	mxs->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mxs->base))
		वापस PTR_ERR(mxs->base);

	mxs->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mxs->clk))
		वापस PTR_ERR(mxs->clk);

	mxs->chip.dev = &pdev->dev;
	mxs->chip.ops = &mxs_pwm_ops;
	mxs->chip.of_xlate = of_pwm_xlate_with_flags;
	mxs->chip.of_pwm_n_cells = 3;

	ret = of_property_पढ़ो_u32(np, "fsl,pwm-number", &mxs->chip.npwm);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to get pwm number: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pwmchip_add(&mxs->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add pwm chip %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mxs);

	ret = sपंचांगp_reset_block(mxs->base);
	अगर (ret)
		जाओ pwm_हटाओ;

	वापस 0;

pwm_हटाओ:
	pwmchip_हटाओ(&mxs->chip);
	वापस ret;
पूर्ण

अटल पूर्णांक mxs_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mxs_pwm_chip *mxs = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&mxs->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id mxs_pwm_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_pwm_dt_ids);

अटल काष्ठा platक्रमm_driver mxs_pwm_driver = अणु
	.driver = अणु
		.name = "mxs-pwm",
		.of_match_table = mxs_pwm_dt_ids,
	पूर्ण,
	.probe = mxs_pwm_probe,
	.हटाओ = mxs_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(mxs_pwm_driver);

MODULE_ALIAS("platform:mxs-pwm");
MODULE_AUTHOR("Shawn Guo <shawn.guo@linaro.org>");
MODULE_DESCRIPTION("Freescale MXS PWM Driver");
MODULE_LICENSE("GPL v2");
