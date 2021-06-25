<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Free Electrons
 * Copyright (C) 2014 Aपंचांगel
 *
 * Author: Boris BREZILLON <boris.brezillon@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/aपंचांगel-hlcdc.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>

#घोषणा ATMEL_HLCDC_PWMCVAL_MASK	GENMASK(15, 8)
#घोषणा ATMEL_HLCDC_PWMCVAL(x)		(((x) << 8) & ATMEL_HLCDC_PWMCVAL_MASK)
#घोषणा ATMEL_HLCDC_PWMPOL		BIT(4)
#घोषणा ATMEL_HLCDC_PWMPS_MASK		GENMASK(2, 0)
#घोषणा ATMEL_HLCDC_PWMPS_MAX		0x6
#घोषणा ATMEL_HLCDC_PWMPS(x)		((x) & ATMEL_HLCDC_PWMPS_MASK)

काष्ठा aपंचांगel_hlcdc_pwm_errata अणु
	bool slow_clk_erratum;
	bool भाग1_clk_erratum;
पूर्ण;

काष्ठा aपंचांगel_hlcdc_pwm अणु
	काष्ठा pwm_chip chip;
	काष्ठा aपंचांगel_hlcdc *hlcdc;
	काष्ठा clk *cur_clk;
	स्थिर काष्ठा aपंचांगel_hlcdc_pwm_errata *errata;
पूर्ण;

अटल अंतरभूत काष्ठा aपंचांगel_hlcdc_pwm *to_aपंचांगel_hlcdc_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा aपंचांगel_hlcdc_pwm, chip);
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_pwm_apply(काष्ठा pwm_chip *c, काष्ठा pwm_device *pwm,
				 स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा aपंचांगel_hlcdc_pwm *chip = to_aपंचांगel_hlcdc_pwm(c);
	काष्ठा aपंचांगel_hlcdc *hlcdc = chip->hlcdc;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	अगर (state->enabled) अणु
		काष्ठा clk *new_clk = hlcdc->slow_clk;
		u64 pwmcval = state->duty_cycle * 256;
		अचिन्हित दीर्घ clk_freq;
		u64 clk_period_ns;
		u32 pwmcfg;
		पूर्णांक pres;

		अगर (!chip->errata || !chip->errata->slow_clk_erratum) अणु
			clk_freq = clk_get_rate(new_clk);
			अगर (!clk_freq)
				वापस -EINVAL;

			clk_period_ns = (u64)NSEC_PER_SEC * 256;
			करो_भाग(clk_period_ns, clk_freq);
		पूर्ण

		/* Errata: cannot use slow clk on some IP revisions */
		अगर ((chip->errata && chip->errata->slow_clk_erratum) ||
		    clk_period_ns > state->period) अणु
			new_clk = hlcdc->sys_clk;
			clk_freq = clk_get_rate(new_clk);
			अगर (!clk_freq)
				वापस -EINVAL;

			clk_period_ns = (u64)NSEC_PER_SEC * 256;
			करो_भाग(clk_period_ns, clk_freq);
		पूर्ण

		क्रम (pres = 0; pres <= ATMEL_HLCDC_PWMPS_MAX; pres++) अणु
		/* Errata: cannot भागide by 1 on some IP revisions */
			अगर (!pres && chip->errata &&
			    chip->errata->भाग1_clk_erratum)
				जारी;

			अगर ((clk_period_ns << pres) >= state->period)
				अवरोध;
		पूर्ण

		अगर (pres > ATMEL_HLCDC_PWMPS_MAX)
			वापस -EINVAL;

		pwmcfg = ATMEL_HLCDC_PWMPS(pres);

		अगर (new_clk != chip->cur_clk) अणु
			u32 gencfg = 0;
			पूर्णांक ret;

			ret = clk_prepare_enable(new_clk);
			अगर (ret)
				वापस ret;

			clk_disable_unprepare(chip->cur_clk);
			chip->cur_clk = new_clk;

			अगर (new_clk == hlcdc->sys_clk)
				gencfg = ATMEL_HLCDC_CLKPWMSEL;

			ret = regmap_update_bits(hlcdc->regmap,
						 ATMEL_HLCDC_CFG(0),
						 ATMEL_HLCDC_CLKPWMSEL,
						 gencfg);
			अगर (ret)
				वापस ret;
		पूर्ण

		करो_भाग(pwmcval, state->period);

		/*
		 * The PWM duty cycle is configurable from 0/256 to 255/256 of
		 * the period cycle. Hence we can't set a duty cycle occupying
		 * the whole period cycle अगर we're asked to.
		 * Set it to 255 अगर pwmcval is greater than 256.
		 */
		अगर (pwmcval > 255)
			pwmcval = 255;

		pwmcfg |= ATMEL_HLCDC_PWMCVAL(pwmcval);

		अगर (state->polarity == PWM_POLARITY_NORMAL)
			pwmcfg |= ATMEL_HLCDC_PWMPOL;

		ret = regmap_update_bits(hlcdc->regmap, ATMEL_HLCDC_CFG(6),
					 ATMEL_HLCDC_PWMCVAL_MASK |
					 ATMEL_HLCDC_PWMPS_MASK |
					 ATMEL_HLCDC_PWMPOL,
					 pwmcfg);
		अगर (ret)
			वापस ret;

		ret = regmap_ग_लिखो(hlcdc->regmap, ATMEL_HLCDC_EN,
				   ATMEL_HLCDC_PWM);
		अगर (ret)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(hlcdc->regmap, ATMEL_HLCDC_SR,
					       status,
					       status & ATMEL_HLCDC_PWM,
					       10, 0);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(hlcdc->regmap, ATMEL_HLCDC_DIS,
				   ATMEL_HLCDC_PWM);
		अगर (ret)
			वापस ret;

		ret = regmap_पढ़ो_poll_समयout(hlcdc->regmap, ATMEL_HLCDC_SR,
					       status,
					       !(status & ATMEL_HLCDC_PWM),
					       10, 0);
		अगर (ret)
			वापस ret;

		clk_disable_unprepare(chip->cur_clk);
		chip->cur_clk = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops aपंचांगel_hlcdc_pwm_ops = अणु
	.apply = aपंचांगel_hlcdc_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_pwm_errata aपंचांगel_hlcdc_pwm_at91sam9x5_errata = अणु
	.slow_clk_erratum = true,
पूर्ण;

अटल स्थिर काष्ठा aपंचांगel_hlcdc_pwm_errata aपंचांगel_hlcdc_pwm_sama5d3_errata = अणु
	.भाग1_clk_erratum = true,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aपंचांगel_hlcdc_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_pwm *chip = dev_get_drvdata(dev);

	/* Keep the periph घड़ी enabled अगर the PWM is still running. */
	अगर (pwm_is_enabled(&chip->chip.pwms[0]))
		clk_disable_unprepare(chip->hlcdc->periph_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा aपंचांगel_hlcdc_pwm *chip = dev_get_drvdata(dev);
	काष्ठा pwm_state state;
	पूर्णांक ret;

	pwm_get_state(&chip->chip.pwms[0], &state);

	/* Re-enable the periph घड़ी it was stopped during suspend. */
	अगर (!state.enabled) अणु
		ret = clk_prepare_enable(chip->hlcdc->periph_clk);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस aपंचांगel_hlcdc_pwm_apply(&chip->chip, &chip->chip.pwms[0], &state);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(aपंचांगel_hlcdc_pwm_pm_ops,
			 aपंचांगel_hlcdc_pwm_suspend, aपंचांगel_hlcdc_pwm_resume);

अटल स्थिर काष्ठा of_device_id aपंचांगel_hlcdc_dt_ids[] = अणु
	अणु
		.compatible = "atmel,at91sam9n12-hlcdc",
		/* 9n12 has same errata as 9x5 HLCDC PWM */
		.data = &aपंचांगel_hlcdc_pwm_at91sam9x5_errata,
	पूर्ण,
	अणु
		.compatible = "atmel,at91sam9x5-hlcdc",
		.data = &aपंचांगel_hlcdc_pwm_at91sam9x5_errata,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d2-hlcdc",
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d3-hlcdc",
		.data = &aपंचांगel_hlcdc_pwm_sama5d3_errata,
	पूर्ण,
	अणु
		.compatible = "atmel,sama5d4-hlcdc",
		.data = &aपंचांगel_hlcdc_pwm_sama5d3_errata,
	पूर्ण,
	अणु	.compatible = "microchip,sam9x60-hlcdc", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_hlcdc_dt_ids);

अटल पूर्णांक aपंचांगel_hlcdc_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aपंचांगel_hlcdc_pwm *chip;
	काष्ठा aपंचांगel_hlcdc *hlcdc;
	पूर्णांक ret;

	hlcdc = dev_get_drvdata(dev->parent);

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	ret = clk_prepare_enable(hlcdc->periph_clk);
	अगर (ret)
		वापस ret;

	match = of_match_node(aपंचांगel_hlcdc_dt_ids, dev->parent->of_node);
	अगर (match)
		chip->errata = match->data;

	chip->hlcdc = hlcdc;
	chip->chip.ops = &aपंचांगel_hlcdc_pwm_ops;
	chip->chip.dev = dev;
	chip->chip.npwm = 1;
	chip->chip.of_xlate = of_pwm_xlate_with_flags;
	chip->chip.of_pwm_n_cells = 3;

	ret = pwmchip_add(&chip->chip);
	अगर (ret) अणु
		clk_disable_unprepare(hlcdc->periph_clk);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, chip);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_hlcdc_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा aपंचांगel_hlcdc_pwm *chip = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&chip->chip);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(chip->hlcdc->periph_clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id aपंचांगel_hlcdc_pwm_dt_ids[] = अणु
	अणु .compatible = "atmel,hlcdc-pwm" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver aपंचांगel_hlcdc_pwm_driver = अणु
	.driver = अणु
		.name = "atmel-hlcdc-pwm",
		.of_match_table = aपंचांगel_hlcdc_pwm_dt_ids,
		.pm = &aपंचांगel_hlcdc_pwm_pm_ops,
	पूर्ण,
	.probe = aपंचांगel_hlcdc_pwm_probe,
	.हटाओ = aपंचांगel_hlcdc_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_hlcdc_pwm_driver);

MODULE_ALIAS("platform:atmel-hlcdc-pwm");
MODULE_AUTHOR("Boris Brezillon <boris.brezillon@free-electrons.com>");
MODULE_DESCRIPTION("Atmel HLCDC PWM driver");
MODULE_LICENSE("GPL v2");
