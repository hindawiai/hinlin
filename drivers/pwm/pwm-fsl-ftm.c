<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Freescale FlexTimer Module (FTM) PWM Driver
 *
 *  Copyright 2012-2013 Freescale Semiconductor, Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/fsl/fपंचांग.h>

#घोषणा FTM_SC_CLK(c)	(((c) + 1) << FTM_SC_CLK_MASK_SHIFT)

क्रमागत fsl_pwm_clk अणु
	FSL_PWM_CLK_SYS,
	FSL_PWM_CLK_FIX,
	FSL_PWM_CLK_EXT,
	FSL_PWM_CLK_CNTEN,
	FSL_PWM_CLK_MAX
पूर्ण;

काष्ठा fsl_fपंचांग_soc अणु
	bool has_enable_bits;
पूर्ण;

काष्ठा fsl_pwm_periodcfg अणु
	क्रमागत fsl_pwm_clk clk_select;
	अचिन्हित पूर्णांक clk_ps;
	अचिन्हित पूर्णांक mod_period;
पूर्ण;

काष्ठा fsl_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;

	/* This value is valid अगरf a pwm is running */
	काष्ठा fsl_pwm_periodcfg period;

	काष्ठा clk *ipg_clk;
	काष्ठा clk *clk[FSL_PWM_CLK_MAX];

	स्थिर काष्ठा fsl_fपंचांग_soc *soc;
पूर्ण;

अटल अंतरभूत काष्ठा fsl_pwm_chip *to_fsl_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा fsl_pwm_chip, chip);
पूर्ण

अटल व्योम fपंचांग_clear_ग_लिखो_protection(काष्ठा fsl_pwm_chip *fpc)
अणु
	u32 val;

	regmap_पढ़ो(fpc->regmap, FTM_FMS, &val);
	अगर (val & FTM_FMS_WPEN)
		regmap_update_bits(fpc->regmap, FTM_MODE, FTM_MODE_WPDIS,
				   FTM_MODE_WPDIS);
पूर्ण

अटल व्योम fपंचांग_set_ग_लिखो_protection(काष्ठा fsl_pwm_chip *fpc)
अणु
	regmap_update_bits(fpc->regmap, FTM_FMS, FTM_FMS_WPEN, FTM_FMS_WPEN);
पूर्ण

अटल bool fsl_pwm_periodcfg_are_equal(स्थिर काष्ठा fsl_pwm_periodcfg *a,
					स्थिर काष्ठा fsl_pwm_periodcfg *b)
अणु
	अगर (a->clk_select != b->clk_select)
		वापस false;
	अगर (a->clk_ps != b->clk_ps)
		वापस false;
	अगर (a->mod_period != b->mod_period)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक fsl_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	पूर्णांक ret;
	काष्ठा fsl_pwm_chip *fpc = to_fsl_chip(chip);

	ret = clk_prepare_enable(fpc->ipg_clk);
	अगर (!ret && fpc->soc->has_enable_bits) अणु
		mutex_lock(&fpc->lock);
		regmap_update_bits(fpc->regmap, FTM_SC, BIT(pwm->hwpwm + 16),
				   BIT(pwm->hwpwm + 16));
		mutex_unlock(&fpc->lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम fsl_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा fsl_pwm_chip *fpc = to_fsl_chip(chip);

	अगर (fpc->soc->has_enable_bits) अणु
		mutex_lock(&fpc->lock);
		regmap_update_bits(fpc->regmap, FTM_SC, BIT(pwm->hwpwm + 16),
				   0);
		mutex_unlock(&fpc->lock);
	पूर्ण

	clk_disable_unprepare(fpc->ipg_clk);
पूर्ण

अटल अचिन्हित पूर्णांक fsl_pwm_ticks_to_ns(काष्ठा fsl_pwm_chip *fpc,
					  अचिन्हित पूर्णांक ticks)
अणु
	अचिन्हित दीर्घ rate;
	अचिन्हित दीर्घ दीर्घ exval;

	rate = clk_get_rate(fpc->clk[fpc->period.clk_select]);
	exval = ticks;
	exval *= 1000000000UL;
	करो_भाग(exval, rate >> fpc->period.clk_ps);
	वापस exval;
पूर्ण

अटल bool fsl_pwm_calculate_period_clk(काष्ठा fsl_pwm_chip *fpc,
					 अचिन्हित पूर्णांक period_ns,
					 क्रमागत fsl_pwm_clk index,
					 काष्ठा fsl_pwm_periodcfg *periodcfg
					 )
अणु
	अचिन्हित दीर्घ दीर्घ c;
	अचिन्हित पूर्णांक ps;

	c = clk_get_rate(fpc->clk[index]);
	c = c * period_ns;
	करो_भाग(c, 1000000000UL);

	अगर (c == 0)
		वापस false;

	क्रम (ps = 0; ps < 8 ; ++ps, c >>= 1) अणु
		अगर (c <= 0x10000) अणु
			periodcfg->clk_select = index;
			periodcfg->clk_ps = ps;
			periodcfg->mod_period = c - 1;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल bool fsl_pwm_calculate_period(काष्ठा fsl_pwm_chip *fpc,
				     अचिन्हित पूर्णांक period_ns,
				     काष्ठा fsl_pwm_periodcfg *periodcfg)
अणु
	क्रमागत fsl_pwm_clk m0, m1;
	अचिन्हित दीर्घ fix_rate, ext_rate;
	bool ret;

	ret = fsl_pwm_calculate_period_clk(fpc, period_ns, FSL_PWM_CLK_SYS,
					   periodcfg);
	अगर (ret)
		वापस true;

	fix_rate = clk_get_rate(fpc->clk[FSL_PWM_CLK_FIX]);
	ext_rate = clk_get_rate(fpc->clk[FSL_PWM_CLK_EXT]);

	अगर (fix_rate > ext_rate) अणु
		m0 = FSL_PWM_CLK_FIX;
		m1 = FSL_PWM_CLK_EXT;
	पूर्ण अन्यथा अणु
		m0 = FSL_PWM_CLK_EXT;
		m1 = FSL_PWM_CLK_FIX;
	पूर्ण

	ret = fsl_pwm_calculate_period_clk(fpc, period_ns, m0, periodcfg);
	अगर (ret)
		वापस true;

	वापस fsl_pwm_calculate_period_clk(fpc, period_ns, m1, periodcfg);
पूर्ण

अटल अचिन्हित पूर्णांक fsl_pwm_calculate_duty(काष्ठा fsl_pwm_chip *fpc,
					   अचिन्हित पूर्णांक duty_ns)
अणु
	अचिन्हित दीर्घ दीर्घ duty;

	अचिन्हित पूर्णांक period = fpc->period.mod_period + 1;
	अचिन्हित पूर्णांक period_ns = fsl_pwm_ticks_to_ns(fpc, period);

	duty = (अचिन्हित दीर्घ दीर्घ)duty_ns * period;
	करो_भाग(duty, period_ns);

	वापस (अचिन्हित पूर्णांक)duty;
पूर्ण

अटल bool fsl_pwm_is_any_pwm_enabled(काष्ठा fsl_pwm_chip *fpc,
				       काष्ठा pwm_device *pwm)
अणु
	u32 val;

	regmap_पढ़ो(fpc->regmap, FTM_OUTMASK, &val);
	अगर (~val & 0xFF)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool fsl_pwm_is_other_pwm_enabled(काष्ठा fsl_pwm_chip *fpc,
					 काष्ठा pwm_device *pwm)
अणु
	u32 val;

	regmap_पढ़ो(fpc->regmap, FTM_OUTMASK, &val);
	अगर (~(val | BIT(pwm->hwpwm)) & 0xFF)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक fsl_pwm_apply_config(काष्ठा fsl_pwm_chip *fpc,
				काष्ठा pwm_device *pwm,
				स्थिर काष्ठा pwm_state *newstate)
अणु
	अचिन्हित पूर्णांक duty;
	u32 reg_polarity;

	काष्ठा fsl_pwm_periodcfg periodcfg;
	bool करो_ग_लिखो_period = false;

	अगर (!fsl_pwm_calculate_period(fpc, newstate->period, &periodcfg)) अणु
		dev_err(fpc->chip.dev, "failed to calculate new period\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!fsl_pwm_is_any_pwm_enabled(fpc, pwm))
		करो_ग_लिखो_period = true;
	/*
	 * The Freescale FTM controller supports only a single period क्रम
	 * all PWM channels, thereक्रमe verअगरy अगर the newly computed period
	 * is dअगरferent than the current period being used. In such हाल
	 * we allow to change the period only अगर no other pwm is running.
	 */
	अन्यथा अगर (!fsl_pwm_periodcfg_are_equal(&fpc->period, &periodcfg)) अणु
		अगर (fsl_pwm_is_other_pwm_enabled(fpc, pwm)) अणु
			dev_err(fpc->chip.dev,
				"Cannot change period for PWM %u, disable other PWMs first\n",
				pwm->hwpwm);
			वापस -EBUSY;
		पूर्ण
		अगर (fpc->period.clk_select != periodcfg.clk_select) अणु
			पूर्णांक ret;
			क्रमागत fsl_pwm_clk oldclk = fpc->period.clk_select;
			क्रमागत fsl_pwm_clk newclk = periodcfg.clk_select;

			ret = clk_prepare_enable(fpc->clk[newclk]);
			अगर (ret)
				वापस ret;
			clk_disable_unprepare(fpc->clk[oldclk]);
		पूर्ण
		करो_ग_लिखो_period = true;
	पूर्ण

	fपंचांग_clear_ग_लिखो_protection(fpc);

	अगर (करो_ग_लिखो_period) अणु
		regmap_update_bits(fpc->regmap, FTM_SC, FTM_SC_CLK_MASK,
				   FTM_SC_CLK(periodcfg.clk_select));
		regmap_update_bits(fpc->regmap, FTM_SC, FTM_SC_PS_MASK,
				   periodcfg.clk_ps);
		regmap_ग_लिखो(fpc->regmap, FTM_MOD, periodcfg.mod_period);

		fpc->period = periodcfg;
	पूर्ण

	duty = fsl_pwm_calculate_duty(fpc, newstate->duty_cycle);

	regmap_ग_लिखो(fpc->regmap, FTM_CSC(pwm->hwpwm),
		     FTM_CSC_MSB | FTM_CSC_ELSB);
	regmap_ग_लिखो(fpc->regmap, FTM_CV(pwm->hwpwm), duty);

	reg_polarity = 0;
	अगर (newstate->polarity == PWM_POLARITY_INVERSED)
		reg_polarity = BIT(pwm->hwpwm);

	regmap_update_bits(fpc->regmap, FTM_POL, BIT(pwm->hwpwm), reg_polarity);

	fपंचांग_set_ग_लिखो_protection(fpc);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			 स्थिर काष्ठा pwm_state *newstate)
अणु
	काष्ठा fsl_pwm_chip *fpc = to_fsl_chip(chip);
	काष्ठा pwm_state *oldstate = &pwm->state;
	पूर्णांक ret = 0;

	/*
	 * oldstate to newstate : action
	 *
	 * disabled to disabled : ignore
	 * enabled to disabled : disable
	 * enabled to enabled : update settings
	 * disabled to enabled : update settings + enable
	 */

	mutex_lock(&fpc->lock);

	अगर (!newstate->enabled) अणु
		अगर (oldstate->enabled) अणु
			regmap_update_bits(fpc->regmap, FTM_OUTMASK,
					   BIT(pwm->hwpwm), BIT(pwm->hwpwm));
			clk_disable_unprepare(fpc->clk[FSL_PWM_CLK_CNTEN]);
			clk_disable_unprepare(fpc->clk[fpc->period.clk_select]);
		पूर्ण

		जाओ end_mutex;
	पूर्ण

	ret = fsl_pwm_apply_config(fpc, pwm, newstate);
	अगर (ret)
		जाओ end_mutex;

	/* check अगर need to enable */
	अगर (!oldstate->enabled) अणु
		ret = clk_prepare_enable(fpc->clk[fpc->period.clk_select]);
		अगर (ret)
			जाओ end_mutex;

		ret = clk_prepare_enable(fpc->clk[FSL_PWM_CLK_CNTEN]);
		अगर (ret) अणु
			clk_disable_unprepare(fpc->clk[fpc->period.clk_select]);
			जाओ end_mutex;
		पूर्ण

		regmap_update_bits(fpc->regmap, FTM_OUTMASK, BIT(pwm->hwpwm),
				   0);
	पूर्ण

end_mutex:
	mutex_unlock(&fpc->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops fsl_pwm_ops = अणु
	.request = fsl_pwm_request,
	.मुक्त = fsl_pwm_मुक्त,
	.apply = fsl_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक fsl_pwm_init(काष्ठा fsl_pwm_chip *fpc)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(fpc->ipg_clk);
	अगर (ret)
		वापस ret;

	regmap_ग_लिखो(fpc->regmap, FTM_CNTIN, 0x00);
	regmap_ग_लिखो(fpc->regmap, FTM_OUTINIT, 0x00);
	regmap_ग_लिखो(fpc->regmap, FTM_OUTMASK, 0xFF);

	clk_disable_unprepare(fpc->ipg_clk);

	वापस 0;
पूर्ण

अटल bool fsl_pwm_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल FTM_FMS:
	हाल FTM_MODE:
	हाल FTM_CNT:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_pwm_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.max_रेजिस्टर = FTM_PWMLOAD,
	.अस्थिर_reg = fsl_pwm_अस्थिर_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक fsl_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_pwm_chip *fpc;
	व्योम __iomem *base;
	पूर्णांक ret;

	fpc = devm_kzalloc(&pdev->dev, माप(*fpc), GFP_KERNEL);
	अगर (!fpc)
		वापस -ENOMEM;

	mutex_init(&fpc->lock);

	fpc->soc = of_device_get_match_data(&pdev->dev);
	fpc->chip.dev = &pdev->dev;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	fpc->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "ftm_sys", base,
						&fsl_pwm_regmap_config);
	अगर (IS_ERR(fpc->regmap)) अणु
		dev_err(&pdev->dev, "regmap init failed\n");
		वापस PTR_ERR(fpc->regmap);
	पूर्ण

	fpc->clk[FSL_PWM_CLK_SYS] = devm_clk_get(&pdev->dev, "ftm_sys");
	अगर (IS_ERR(fpc->clk[FSL_PWM_CLK_SYS])) अणु
		dev_err(&pdev->dev, "failed to get \"ftm_sys\" clock\n");
		वापस PTR_ERR(fpc->clk[FSL_PWM_CLK_SYS]);
	पूर्ण

	fpc->clk[FSL_PWM_CLK_FIX] = devm_clk_get(fpc->chip.dev, "ftm_fix");
	अगर (IS_ERR(fpc->clk[FSL_PWM_CLK_FIX]))
		वापस PTR_ERR(fpc->clk[FSL_PWM_CLK_FIX]);

	fpc->clk[FSL_PWM_CLK_EXT] = devm_clk_get(fpc->chip.dev, "ftm_ext");
	अगर (IS_ERR(fpc->clk[FSL_PWM_CLK_EXT]))
		वापस PTR_ERR(fpc->clk[FSL_PWM_CLK_EXT]);

	fpc->clk[FSL_PWM_CLK_CNTEN] =
				devm_clk_get(fpc->chip.dev, "ftm_cnt_clk_en");
	अगर (IS_ERR(fpc->clk[FSL_PWM_CLK_CNTEN]))
		वापस PTR_ERR(fpc->clk[FSL_PWM_CLK_CNTEN]);

	/*
	 * ipg_clk is the पूर्णांकerface घड़ी क्रम the IP. If not provided, use the
	 * fपंचांग_sys घड़ी as the शेष.
	 */
	fpc->ipg_clk = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(fpc->ipg_clk))
		fpc->ipg_clk = fpc->clk[FSL_PWM_CLK_SYS];


	fpc->chip.ops = &fsl_pwm_ops;
	fpc->chip.of_xlate = of_pwm_xlate_with_flags;
	fpc->chip.of_pwm_n_cells = 3;
	fpc->chip.npwm = 8;

	ret = pwmchip_add(&fpc->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, fpc);

	वापस fsl_pwm_init(fpc);
पूर्ण

अटल पूर्णांक fsl_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_pwm_chip *fpc = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&fpc->chip);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fsl_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_pwm_chip *fpc = dev_get_drvdata(dev);
	पूर्णांक i;

	regcache_cache_only(fpc->regmap, true);
	regcache_mark_dirty(fpc->regmap);

	क्रम (i = 0; i < fpc->chip.npwm; i++) अणु
		काष्ठा pwm_device *pwm = &fpc->chip.pwms[i];

		अगर (!test_bit(PWMF_REQUESTED, &pwm->flags))
			जारी;

		clk_disable_unprepare(fpc->ipg_clk);

		अगर (!pwm_is_enabled(pwm))
			जारी;

		clk_disable_unprepare(fpc->clk[FSL_PWM_CLK_CNTEN]);
		clk_disable_unprepare(fpc->clk[fpc->period.clk_select]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_pwm_chip *fpc = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < fpc->chip.npwm; i++) अणु
		काष्ठा pwm_device *pwm = &fpc->chip.pwms[i];

		अगर (!test_bit(PWMF_REQUESTED, &pwm->flags))
			जारी;

		clk_prepare_enable(fpc->ipg_clk);

		अगर (!pwm_is_enabled(pwm))
			जारी;

		clk_prepare_enable(fpc->clk[fpc->period.clk_select]);
		clk_prepare_enable(fpc->clk[FSL_PWM_CLK_CNTEN]);
	पूर्ण

	/* restore all रेजिस्टरs from cache */
	regcache_cache_only(fpc->regmap, false);
	regcache_sync(fpc->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops fsl_pwm_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fsl_pwm_suspend, fsl_pwm_resume)
पूर्ण;

अटल स्थिर काष्ठा fsl_fपंचांग_soc vf610_fपंचांग_pwm = अणु
	.has_enable_bits = false,
पूर्ण;

अटल स्थिर काष्ठा fsl_fपंचांग_soc imx8qm_fपंचांग_pwm = अणु
	.has_enable_bits = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_pwm_dt_ids[] = अणु
	अणु .compatible = "fsl,vf610-ftm-pwm", .data = &vf610_fपंचांग_pwm पूर्ण,
	अणु .compatible = "fsl,imx8qm-ftm-pwm", .data = &imx8qm_fपंचांग_pwm पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_pwm_dt_ids);

अटल काष्ठा platक्रमm_driver fsl_pwm_driver = अणु
	.driver = अणु
		.name = "fsl-ftm-pwm",
		.of_match_table = fsl_pwm_dt_ids,
		.pm = &fsl_pwm_pm_ops,
	पूर्ण,
	.probe = fsl_pwm_probe,
	.हटाओ = fsl_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(fsl_pwm_driver);

MODULE_DESCRIPTION("Freescale FlexTimer Module PWM Driver");
MODULE_AUTHOR("Xiubo Li <Li.Xiubo@freescale.com>");
MODULE_ALIAS("platform:fsl-ftm-pwm");
MODULE_LICENSE("GPL");
