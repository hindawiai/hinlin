<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2010, Lars-Peter Clausen <lars@metafoo.de>
 *  JZ4740 platक्रमm PWM support
 *
 * Limitations:
 * - The .apply callback करोesn't complete the currently running period beक्रमe
 *   reconfiguring the hardware.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/ingenic-tcu.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>

काष्ठा soc_info अणु
	अचिन्हित पूर्णांक num_pwms;
पूर्ण;

काष्ठा jz4740_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा regmap *map;
पूर्ण;

अटल अंतरभूत काष्ठा jz4740_pwm_chip *to_jz4740(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा jz4740_pwm_chip, chip);
पूर्ण

अटल bool jz4740_pwm_can_use_chn(काष्ठा jz4740_pwm_chip *jz,
				   अचिन्हित पूर्णांक channel)
अणु
	/* Enable all TCU channels क्रम PWM use by शेष except channels 0/1 */
	u32 pwm_channels_mask = GENMASK(jz->chip.npwm - 1, 2);

	device_property_पढ़ो_u32(jz->chip.dev->parent,
				 "ingenic,pwm-channels-mask",
				 &pwm_channels_mask);

	वापस !!(pwm_channels_mask & BIT(channel));
पूर्ण

अटल पूर्णांक jz4740_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा jz4740_pwm_chip *jz = to_jz4740(chip);
	काष्ठा clk *clk;
	अक्षर name[16];
	पूर्णांक err;

	अगर (!jz4740_pwm_can_use_chn(jz, pwm->hwpwm))
		वापस -EBUSY;

	snम_लिखो(name, माप(name), "timer%u", pwm->hwpwm);

	clk = clk_get(chip->dev, name);
	अगर (IS_ERR(clk))
		वापस dev_err_probe(chip->dev, PTR_ERR(clk),
				     "Failed to get clock\n");

	err = clk_prepare_enable(clk);
	अगर (err < 0) अणु
		clk_put(clk);
		वापस err;
	पूर्ण

	pwm_set_chip_data(pwm, clk);

	वापस 0;
पूर्ण

अटल व्योम jz4740_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा clk *clk = pwm_get_chip_data(pwm);

	clk_disable_unprepare(clk);
	clk_put(clk);
पूर्ण

अटल पूर्णांक jz4740_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा jz4740_pwm_chip *jz = to_jz4740(chip);

	/* Enable PWM output */
	regmap_update_bits(jz->map, TCU_REG_TCSRc(pwm->hwpwm),
			   TCU_TCSR_PWM_EN, TCU_TCSR_PWM_EN);

	/* Start counter */
	regmap_ग_लिखो(jz->map, TCU_REG_TESR, BIT(pwm->hwpwm));

	वापस 0;
पूर्ण

अटल व्योम jz4740_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा jz4740_pwm_chip *jz = to_jz4740(chip);

	/*
	 * Set duty > period. This trick allows the TCU channels in TCU2 mode to
	 * properly वापस to their init level.
	 */
	regmap_ग_लिखो(jz->map, TCU_REG_TDHRc(pwm->hwpwm), 0xffff);
	regmap_ग_लिखो(jz->map, TCU_REG_TDFRc(pwm->hwpwm), 0x0);

	/*
	 * Disable PWM output.
	 * In TCU2 mode (channel 1/2 on JZ4750+), this must be करोne beक्रमe the
	 * counter is stopped, जबतक in TCU1 mode the order करोes not matter.
	 */
	regmap_update_bits(jz->map, TCU_REG_TCSRc(pwm->hwpwm),
			   TCU_TCSR_PWM_EN, 0);

	/* Stop counter */
	regmap_ग_लिखो(jz->map, TCU_REG_TECR, BIT(pwm->hwpwm));
पूर्ण

अटल पूर्णांक jz4740_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			    स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा jz4740_pwm_chip *jz4740 = to_jz4740(pwm->chip);
	अचिन्हित दीर्घ दीर्घ पंचांगp = 0xffffull * NSEC_PER_SEC;
	काष्ठा clk *clk = pwm_get_chip_data(pwm);
	अचिन्हित दीर्घ period, duty;
	दीर्घ rate;
	पूर्णांक err;

	/*
	 * Limit the घड़ी to a maximum rate that still gives us a period value
	 * which fits in 16 bits.
	 */
	करो_भाग(पंचांगp, state->period);

	/*
	 * /!\ IMPORTANT NOTE:
	 * -------------------
	 * This code relies on the fact that clk_round_rate() will always round
	 * करोwn, which is not a valid assumption given by the clk API, but only
	 * happens to be true with the clk drivers used क्रम Ingenic SoCs.
	 *
	 * Right now, there is no alternative as the clk API करोes not have a
	 * round-करोwn function (and won't have one क्रम a जबतक), but अगर it ever
	 * comes to light, a round-करोwn function should be used instead.
	 */
	rate = clk_round_rate(clk, पंचांगp);
	अगर (rate < 0) अणु
		dev_err(chip->dev, "Unable to round rate: %ld", rate);
		वापस rate;
	पूर्ण

	/* Calculate period value */
	पंचांगp = (अचिन्हित दीर्घ दीर्घ)rate * state->period;
	करो_भाग(पंचांगp, NSEC_PER_SEC);
	period = पंचांगp;

	/* Calculate duty value */
	पंचांगp = (अचिन्हित दीर्घ दीर्घ)rate * state->duty_cycle;
	करो_भाग(पंचांगp, NSEC_PER_SEC);
	duty = पंचांगp;

	अगर (duty >= period)
		duty = period - 1;

	jz4740_pwm_disable(chip, pwm);

	err = clk_set_rate(clk, rate);
	अगर (err) अणु
		dev_err(chip->dev, "Unable to set rate: %d", err);
		वापस err;
	पूर्ण

	/* Reset counter to 0 */
	regmap_ग_लिखो(jz4740->map, TCU_REG_TCNTc(pwm->hwpwm), 0);

	/* Set duty */
	regmap_ग_लिखो(jz4740->map, TCU_REG_TDHRc(pwm->hwpwm), duty);

	/* Set period */
	regmap_ग_लिखो(jz4740->map, TCU_REG_TDFRc(pwm->hwpwm), period);

	/* Set abrupt shutकरोwn */
	regmap_update_bits(jz4740->map, TCU_REG_TCSRc(pwm->hwpwm),
			   TCU_TCSR_PWM_SD, TCU_TCSR_PWM_SD);

	/*
	 * Set polarity.
	 *
	 * The PWM starts in inactive state until the पूर्णांकernal समयr reaches the
	 * duty value, then becomes active until the समयr reaches the period
	 * value. In theory, we should then use (period - duty) as the real duty
	 * value, as a high duty value would otherwise result in the PWM pin
	 * being inactive most of the समय.
	 *
	 * Here, we करोn't करो that, and instead invert the polarity of the PWM
	 * when it is active. This trick makes the PWM start with its active
	 * state instead of its inactive state.
	 */
	अगर ((state->polarity == PWM_POLARITY_NORMAL) ^ state->enabled)
		regmap_update_bits(jz4740->map, TCU_REG_TCSRc(pwm->hwpwm),
				   TCU_TCSR_PWM_INITL_HIGH, 0);
	अन्यथा
		regmap_update_bits(jz4740->map, TCU_REG_TCSRc(pwm->hwpwm),
				   TCU_TCSR_PWM_INITL_HIGH,
				   TCU_TCSR_PWM_INITL_HIGH);

	अगर (state->enabled)
		jz4740_pwm_enable(chip, pwm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops jz4740_pwm_ops = अणु
	.request = jz4740_pwm_request,
	.मुक्त = jz4740_pwm_मुक्त,
	.apply = jz4740_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक jz4740_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा jz4740_pwm_chip *jz4740;
	स्थिर काष्ठा soc_info *info;

	info = device_get_match_data(dev);
	अगर (!info)
		वापस -EINVAL;

	jz4740 = devm_kzalloc(dev, माप(*jz4740), GFP_KERNEL);
	अगर (!jz4740)
		वापस -ENOMEM;

	jz4740->map = device_node_to_regmap(dev->parent->of_node);
	अगर (IS_ERR(jz4740->map)) अणु
		dev_err(dev, "regmap not found: %ld\n", PTR_ERR(jz4740->map));
		वापस PTR_ERR(jz4740->map);
	पूर्ण

	jz4740->chip.dev = dev;
	jz4740->chip.ops = &jz4740_pwm_ops;
	jz4740->chip.npwm = info->num_pwms;
	jz4740->chip.of_xlate = of_pwm_xlate_with_flags;
	jz4740->chip.of_pwm_n_cells = 3;

	platक्रमm_set_drvdata(pdev, jz4740);

	वापस pwmchip_add(&jz4740->chip);
पूर्ण

अटल पूर्णांक jz4740_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jz4740_pwm_chip *jz4740 = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&jz4740->chip);
पूर्ण

अटल स्थिर काष्ठा soc_info __maybe_unused jz4740_soc_info = अणु
	.num_pwms = 8,
पूर्ण;

अटल स्थिर काष्ठा soc_info __maybe_unused jz4725b_soc_info = अणु
	.num_pwms = 6,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id jz4740_pwm_dt_ids[] = अणु
	अणु .compatible = "ingenic,jz4740-pwm", .data = &jz4740_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4725b-pwm", .data = &jz4725b_soc_info पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_pwm_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver jz4740_pwm_driver = अणु
	.driver = अणु
		.name = "jz4740-pwm",
		.of_match_table = of_match_ptr(jz4740_pwm_dt_ids),
	पूर्ण,
	.probe = jz4740_pwm_probe,
	.हटाओ = jz4740_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(jz4740_pwm_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Ingenic JZ4740 PWM driver");
MODULE_ALIAS("platform:jz4740-pwm");
MODULE_LICENSE("GPL");
