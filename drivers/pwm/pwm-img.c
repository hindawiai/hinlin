<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Imagination Technologies Pulse Width Modulator driver
 *
 * Copyright (c) 2014-2015, Imagination Technologies
 *
 * Based on drivers/pwm/pwm-tegra.c, Copyright (c) 2010, NVIDIA Corporation
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

/* PWM रेजिस्टरs */
#घोषणा PWM_CTRL_CFG				0x0000
#घोषणा PWM_CTRL_CFG_NO_SUB_DIV			0
#घोषणा PWM_CTRL_CFG_SUB_DIV0			1
#घोषणा PWM_CTRL_CFG_SUB_DIV1			2
#घोषणा PWM_CTRL_CFG_SUB_DIV0_DIV1		3
#घोषणा PWM_CTRL_CFG_DIV_SHIFT(ch)		((ch) * 2 + 4)
#घोषणा PWM_CTRL_CFG_DIV_MASK			0x3

#घोषणा PWM_CH_CFG(ch)				(0x4 + (ch) * 4)
#घोषणा PWM_CH_CFG_TMBASE_SHIFT			0
#घोषणा PWM_CH_CFG_DUTY_SHIFT			16

#घोषणा PERIP_PWM_PDM_CONTROL			0x0140
#घोषणा PERIP_PWM_PDM_CONTROL_CH_MASK		0x1
#घोषणा PERIP_PWM_PDM_CONTROL_CH_SHIFT(ch)	((ch) * 4)

#घोषणा IMG_PWM_PM_TIMEOUT			1000 /* ms */

/*
 * PWM period is specअगरied with a समयbase रेजिस्टर,
 * in number of step periods. The PWM duty cycle is also
 * specअगरied in step periods, in the [0, $समयbase] range.
 * In other words, the समयbase imposes the duty cycle
 * resolution. Thereक्रमe, let's स्थिरraपूर्णांक the समयbase to
 * a minimum value to allow a sane range of duty cycle values.
 * Imposing a minimum समयbase, will impose a maximum PWM frequency.
 *
 * The value chosen is completely arbitrary.
 */
#घोषणा MIN_TMBASE_STEPS			16

#घोषणा IMG_PWM_NPWM				4

काष्ठा img_pwm_soc_data अणु
	u32 max_समयbase;
पूर्ण;

काष्ठा img_pwm_chip अणु
	काष्ठा device	*dev;
	काष्ठा pwm_chip	chip;
	काष्ठा clk	*pwm_clk;
	काष्ठा clk	*sys_clk;
	व्योम __iomem	*base;
	काष्ठा regmap	*periph_regs;
	पूर्णांक		max_period_ns;
	पूर्णांक		min_period_ns;
	स्थिर काष्ठा img_pwm_soc_data   *data;
	u32		suspend_ctrl_cfg;
	u32		suspend_ch_cfg[IMG_PWM_NPWM];
पूर्ण;

अटल अंतरभूत काष्ठा img_pwm_chip *to_img_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा img_pwm_chip, chip);
पूर्ण

अटल अंतरभूत व्योम img_pwm_ग_लिखोl(काष्ठा img_pwm_chip *chip,
				  u32 reg, u32 val)
अणु
	ग_लिखोl(val, chip->base + reg);
पूर्ण

अटल अंतरभूत u32 img_pwm_पढ़ोl(काष्ठा img_pwm_chip *chip,
					 u32 reg)
अणु
	वापस पढ़ोl(chip->base + reg);
पूर्ण

अटल पूर्णांक img_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			  पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	u32 val, भाग, duty, समयbase;
	अचिन्हित दीर्घ mul, output_clk_hz, input_clk_hz;
	काष्ठा img_pwm_chip *pwm_chip = to_img_pwm_chip(chip);
	अचिन्हित पूर्णांक max_समयbase = pwm_chip->data->max_समयbase;
	पूर्णांक ret;

	अगर (period_ns < pwm_chip->min_period_ns ||
	    period_ns > pwm_chip->max_period_ns) अणु
		dev_err(chip->dev, "configured period not in range\n");
		वापस -दुस्फल;
	पूर्ण

	input_clk_hz = clk_get_rate(pwm_chip->pwm_clk);
	output_clk_hz = DIV_ROUND_UP(NSEC_PER_SEC, period_ns);

	mul = DIV_ROUND_UP(input_clk_hz, output_clk_hz);
	अगर (mul <= max_समयbase) अणु
		भाग = PWM_CTRL_CFG_NO_SUB_DIV;
		समयbase = DIV_ROUND_UP(mul, 1);
	पूर्ण अन्यथा अगर (mul <= max_समयbase * 8) अणु
		भाग = PWM_CTRL_CFG_SUB_DIV0;
		समयbase = DIV_ROUND_UP(mul, 8);
	पूर्ण अन्यथा अगर (mul <= max_समयbase * 64) अणु
		भाग = PWM_CTRL_CFG_SUB_DIV1;
		समयbase = DIV_ROUND_UP(mul, 64);
	पूर्ण अन्यथा अगर (mul <= max_समयbase * 512) अणु
		भाग = PWM_CTRL_CFG_SUB_DIV0_DIV1;
		समयbase = DIV_ROUND_UP(mul, 512);
	पूर्ण अन्यथा अणु
		dev_err(chip->dev,
			"failed to configure timebase steps/divider value\n");
		वापस -EINVAL;
	पूर्ण

	duty = DIV_ROUND_UP(समयbase * duty_ns, period_ns);

	ret = pm_runसमय_get_sync(chip->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(chip->dev);
		वापस ret;
	पूर्ण

	val = img_pwm_पढ़ोl(pwm_chip, PWM_CTRL_CFG);
	val &= ~(PWM_CTRL_CFG_DIV_MASK << PWM_CTRL_CFG_DIV_SHIFT(pwm->hwpwm));
	val |= (भाग & PWM_CTRL_CFG_DIV_MASK) <<
		PWM_CTRL_CFG_DIV_SHIFT(pwm->hwpwm);
	img_pwm_ग_लिखोl(pwm_chip, PWM_CTRL_CFG, val);

	val = (duty << PWM_CH_CFG_DUTY_SHIFT) |
	      (समयbase << PWM_CH_CFG_TMBASE_SHIFT);
	img_pwm_ग_लिखोl(pwm_chip, PWM_CH_CFG(pwm->hwpwm), val);

	pm_runसमय_mark_last_busy(chip->dev);
	pm_runसमय_put_स्वतःsuspend(chip->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक img_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	u32 val;
	काष्ठा img_pwm_chip *pwm_chip = to_img_pwm_chip(chip);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(chip->dev);
	अगर (ret < 0)
		वापस ret;

	val = img_pwm_पढ़ोl(pwm_chip, PWM_CTRL_CFG);
	val |= BIT(pwm->hwpwm);
	img_pwm_ग_लिखोl(pwm_chip, PWM_CTRL_CFG, val);

	regmap_update_bits(pwm_chip->periph_regs, PERIP_PWM_PDM_CONTROL,
			   PERIP_PWM_PDM_CONTROL_CH_MASK <<
			   PERIP_PWM_PDM_CONTROL_CH_SHIFT(pwm->hwpwm), 0);

	वापस 0;
पूर्ण

अटल व्योम img_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	u32 val;
	काष्ठा img_pwm_chip *pwm_chip = to_img_pwm_chip(chip);

	val = img_pwm_पढ़ोl(pwm_chip, PWM_CTRL_CFG);
	val &= ~BIT(pwm->hwpwm);
	img_pwm_ग_लिखोl(pwm_chip, PWM_CTRL_CFG, val);

	pm_runसमय_mark_last_busy(chip->dev);
	pm_runसमय_put_स्वतःsuspend(chip->dev);
पूर्ण

अटल स्थिर काष्ठा pwm_ops img_pwm_ops = अणु
	.config = img_pwm_config,
	.enable = img_pwm_enable,
	.disable = img_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा img_pwm_soc_data pistachio_pwm = अणु
	.max_समयbase = 255,
पूर्ण;

अटल स्थिर काष्ठा of_device_id img_pwm_of_match[] = अणु
	अणु
		.compatible = "img,pistachio-pwm",
		.data = &pistachio_pwm,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_pwm_of_match);

अटल पूर्णांक img_pwm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_pwm_chip *pwm_chip = dev_get_drvdata(dev);

	clk_disable_unprepare(pwm_chip->pwm_clk);
	clk_disable_unprepare(pwm_chip->sys_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक img_pwm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा img_pwm_chip *pwm_chip = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(pwm_chip->sys_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "could not prepare or enable sys clock\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(pwm_chip->pwm_clk);
	अगर (ret < 0) अणु
		dev_err(dev, "could not prepare or enable pwm clock\n");
		clk_disable_unprepare(pwm_chip->sys_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक img_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	u64 val;
	अचिन्हित दीर्घ clk_rate;
	काष्ठा img_pwm_chip *pwm;
	स्थिर काष्ठा of_device_id *of_dev_id;

	pwm = devm_kzalloc(&pdev->dev, माप(*pwm), GFP_KERNEL);
	अगर (!pwm)
		वापस -ENOMEM;

	pwm->dev = &pdev->dev;

	pwm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pwm->base))
		वापस PTR_ERR(pwm->base);

	of_dev_id = of_match_device(img_pwm_of_match, &pdev->dev);
	अगर (!of_dev_id)
		वापस -ENODEV;
	pwm->data = of_dev_id->data;

	pwm->periph_regs = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							   "img,cr-periph");
	अगर (IS_ERR(pwm->periph_regs))
		वापस PTR_ERR(pwm->periph_regs);

	pwm->sys_clk = devm_clk_get(&pdev->dev, "sys");
	अगर (IS_ERR(pwm->sys_clk)) अणु
		dev_err(&pdev->dev, "failed to get system clock\n");
		वापस PTR_ERR(pwm->sys_clk);
	पूर्ण

	pwm->pwm_clk = devm_clk_get(&pdev->dev, "pwm");
	अगर (IS_ERR(pwm->pwm_clk)) अणु
		dev_err(&pdev->dev, "failed to get pwm clock\n");
		वापस PTR_ERR(pwm->pwm_clk);
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwm);

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, IMG_PWM_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = img_pwm_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	clk_rate = clk_get_rate(pwm->pwm_clk);
	अगर (!clk_rate) अणु
		dev_err(&pdev->dev, "pwm clock has no frequency\n");
		ret = -EINVAL;
		जाओ err_suspend;
	पूर्ण

	/* The maximum input घड़ी भागider is 512 */
	val = (u64)NSEC_PER_SEC * 512 * pwm->data->max_समयbase;
	करो_भाग(val, clk_rate);
	pwm->max_period_ns = val;

	val = (u64)NSEC_PER_SEC * MIN_TMBASE_STEPS;
	करो_भाग(val, clk_rate);
	pwm->min_period_ns = val;

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &img_pwm_ops;
	pwm->chip.npwm = IMG_PWM_NPWM;

	ret = pwmchip_add(&pwm->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add failed: %d\n", ret);
		जाओ err_suspend;
	पूर्ण

	वापस 0;

err_suspend:
	अगर (!pm_runसमय_enabled(&pdev->dev))
		img_pwm_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक img_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_pwm_chip *pwm_chip = platक्रमm_get_drvdata(pdev);
	u32 val;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put(&pdev->dev);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < pwm_chip->chip.npwm; i++) अणु
		val = img_pwm_पढ़ोl(pwm_chip, PWM_CTRL_CFG);
		val &= ~BIT(i);
		img_pwm_ग_लिखोl(pwm_chip, PWM_CTRL_CFG, val);
	पूर्ण

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		img_pwm_runसमय_suspend(&pdev->dev);

	वापस pwmchip_हटाओ(&pwm_chip->chip);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक img_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा img_pwm_chip *pwm_chip = dev_get_drvdata(dev);
	पूर्णांक i, ret;

	अगर (pm_runसमय_status_suspended(dev)) अणु
		ret = img_pwm_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < pwm_chip->chip.npwm; i++)
		pwm_chip->suspend_ch_cfg[i] = img_pwm_पढ़ोl(pwm_chip,
							    PWM_CH_CFG(i));

	pwm_chip->suspend_ctrl_cfg = img_pwm_पढ़ोl(pwm_chip, PWM_CTRL_CFG);

	img_pwm_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक img_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा img_pwm_chip *pwm_chip = dev_get_drvdata(dev);
	पूर्णांक ret;
	पूर्णांक i;

	ret = img_pwm_runसमय_resume(dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < pwm_chip->chip.npwm; i++)
		img_pwm_ग_लिखोl(pwm_chip, PWM_CH_CFG(i),
			       pwm_chip->suspend_ch_cfg[i]);

	img_pwm_ग_लिखोl(pwm_chip, PWM_CTRL_CFG, pwm_chip->suspend_ctrl_cfg);

	क्रम (i = 0; i < pwm_chip->chip.npwm; i++)
		अगर (pwm_chip->suspend_ctrl_cfg & BIT(i))
			regmap_update_bits(pwm_chip->periph_regs,
					   PERIP_PWM_PDM_CONTROL,
					   PERIP_PWM_PDM_CONTROL_CH_MASK <<
					   PERIP_PWM_PDM_CONTROL_CH_SHIFT(i),
					   0);

	अगर (pm_runसमय_status_suspended(dev))
		img_pwm_runसमय_suspend(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा dev_pm_ops img_pwm_pm_ops = अणु
	SET_RUNTIME_PM_OPS(img_pwm_runसमय_suspend,
			   img_pwm_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(img_pwm_suspend, img_pwm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver img_pwm_driver = अणु
	.driver = अणु
		.name = "img-pwm",
		.pm = &img_pwm_pm_ops,
		.of_match_table = img_pwm_of_match,
	पूर्ण,
	.probe = img_pwm_probe,
	.हटाओ = img_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(img_pwm_driver);

MODULE_AUTHOR("Sai Masarapu <Sai.Masarapu@imgtec.com>");
MODULE_DESCRIPTION("Imagination Technologies PWM DAC driver");
MODULE_LICENSE("GPL v2");
