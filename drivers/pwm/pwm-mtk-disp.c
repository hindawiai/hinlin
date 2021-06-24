<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MediaTek display pulse-width-modulation controller driver.
 * Copyright (c) 2015 MediaTek Inc.
 * Author: YH Huang <yh.huang@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा DISP_PWM_EN		0x00

#घोषणा PWM_CLKDIV_SHIFT	16
#घोषणा PWM_CLKDIV_MAX		0x3ff
#घोषणा PWM_CLKDIV_MASK		(PWM_CLKDIV_MAX << PWM_CLKDIV_SHIFT)

#घोषणा PWM_PERIOD_BIT_WIDTH	12
#घोषणा PWM_PERIOD_MASK		((1 << PWM_PERIOD_BIT_WIDTH) - 1)

#घोषणा PWM_HIGH_WIDTH_SHIFT	16
#घोषणा PWM_HIGH_WIDTH_MASK	(0x1fff << PWM_HIGH_WIDTH_SHIFT)

काष्ठा mtk_pwm_data अणु
	u32 enable_mask;
	अचिन्हित पूर्णांक con0;
	u32 con0_sel;
	अचिन्हित पूर्णांक con1;

	bool has_commit;
	अचिन्हित पूर्णांक commit;
	अचिन्हित पूर्णांक commit_mask;

	अचिन्हित पूर्णांक bls_debug;
	u32 bls_debug_mask;
पूर्ण;

काष्ठा mtk_disp_pwm अणु
	काष्ठा pwm_chip chip;
	स्थिर काष्ठा mtk_pwm_data *data;
	काष्ठा clk *clk_मुख्य;
	काष्ठा clk *clk_mm;
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_disp_pwm *to_mtk_disp_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा mtk_disp_pwm, chip);
पूर्ण

अटल व्योम mtk_disp_pwm_update_bits(काष्ठा mtk_disp_pwm *mdp, u32 offset,
				     u32 mask, u32 data)
अणु
	व्योम __iomem *address = mdp->base + offset;
	u32 value;

	value = पढ़ोl(address);
	value &= ~mask;
	value |= data;
	ग_लिखोl(value, address);
पूर्ण

अटल पूर्णांक mtk_disp_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा mtk_disp_pwm *mdp = to_mtk_disp_pwm(chip);
	u32 clk_भाग, period, high_width, value;
	u64 भाग, rate;
	पूर्णांक err;

	/*
	 * Find period, high_width and clk_भाग to suit duty_ns and period_ns.
	 * Calculate proper भाग value to keep period value in the bound.
	 *
	 * period_ns = 10^9 * (clk_भाग + 1) * (period + 1) / PWM_CLK_RATE
	 * duty_ns = 10^9 * (clk_भाग + 1) * high_width / PWM_CLK_RATE
	 *
	 * period = (PWM_CLK_RATE * period_ns) / (10^9 * (clk_भाग + 1)) - 1
	 * high_width = (PWM_CLK_RATE * duty_ns) / (10^9 * (clk_भाग + 1))
	 */
	rate = clk_get_rate(mdp->clk_मुख्य);
	clk_भाग = भाग_u64(rate * period_ns, NSEC_PER_SEC) >>
			  PWM_PERIOD_BIT_WIDTH;
	अगर (clk_भाग > PWM_CLKDIV_MAX)
		वापस -EINVAL;

	भाग = NSEC_PER_SEC * (clk_भाग + 1);
	period = भाग64_u64(rate * period_ns, भाग);
	अगर (period > 0)
		period--;

	high_width = भाग64_u64(rate * duty_ns, भाग);
	value = period | (high_width << PWM_HIGH_WIDTH_SHIFT);

	err = clk_enable(mdp->clk_मुख्य);
	अगर (err < 0)
		वापस err;

	err = clk_enable(mdp->clk_mm);
	अगर (err < 0) अणु
		clk_disable(mdp->clk_मुख्य);
		वापस err;
	पूर्ण

	mtk_disp_pwm_update_bits(mdp, mdp->data->con0,
				 PWM_CLKDIV_MASK,
				 clk_भाग << PWM_CLKDIV_SHIFT);
	mtk_disp_pwm_update_bits(mdp, mdp->data->con1,
				 PWM_PERIOD_MASK | PWM_HIGH_WIDTH_MASK,
				 value);

	अगर (mdp->data->has_commit) अणु
		mtk_disp_pwm_update_bits(mdp, mdp->data->commit,
					 mdp->data->commit_mask,
					 mdp->data->commit_mask);
		mtk_disp_pwm_update_bits(mdp, mdp->data->commit,
					 mdp->data->commit_mask,
					 0x0);
	पूर्ण

	clk_disable(mdp->clk_mm);
	clk_disable(mdp->clk_मुख्य);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_disp_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा mtk_disp_pwm *mdp = to_mtk_disp_pwm(chip);
	पूर्णांक err;

	err = clk_enable(mdp->clk_मुख्य);
	अगर (err < 0)
		वापस err;

	err = clk_enable(mdp->clk_mm);
	अगर (err < 0) अणु
		clk_disable(mdp->clk_मुख्य);
		वापस err;
	पूर्ण

	mtk_disp_pwm_update_bits(mdp, DISP_PWM_EN, mdp->data->enable_mask,
				 mdp->data->enable_mask);

	वापस 0;
पूर्ण

अटल व्योम mtk_disp_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा mtk_disp_pwm *mdp = to_mtk_disp_pwm(chip);

	mtk_disp_pwm_update_bits(mdp, DISP_PWM_EN, mdp->data->enable_mask,
				 0x0);

	clk_disable(mdp->clk_mm);
	clk_disable(mdp->clk_मुख्य);
पूर्ण

अटल स्थिर काष्ठा pwm_ops mtk_disp_pwm_ops = अणु
	.config = mtk_disp_pwm_config,
	.enable = mtk_disp_pwm_enable,
	.disable = mtk_disp_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक mtk_disp_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_disp_pwm *mdp;
	पूर्णांक ret;

	mdp = devm_kzalloc(&pdev->dev, माप(*mdp), GFP_KERNEL);
	अगर (!mdp)
		वापस -ENOMEM;

	mdp->data = of_device_get_match_data(&pdev->dev);

	mdp->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdp->base))
		वापस PTR_ERR(mdp->base);

	mdp->clk_मुख्य = devm_clk_get(&pdev->dev, "main");
	अगर (IS_ERR(mdp->clk_मुख्य))
		वापस PTR_ERR(mdp->clk_मुख्य);

	mdp->clk_mm = devm_clk_get(&pdev->dev, "mm");
	अगर (IS_ERR(mdp->clk_mm))
		वापस PTR_ERR(mdp->clk_mm);

	ret = clk_prepare(mdp->clk_मुख्य);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare(mdp->clk_mm);
	अगर (ret < 0)
		जाओ disable_clk_मुख्य;

	mdp->chip.dev = &pdev->dev;
	mdp->chip.ops = &mtk_disp_pwm_ops;
	mdp->chip.npwm = 1;

	ret = pwmchip_add(&mdp->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		जाओ disable_clk_mm;
	पूर्ण

	platक्रमm_set_drvdata(pdev, mdp);

	/*
	 * For MT2701, disable द्विगुन buffer beक्रमe writing रेजिस्टर
	 * and select manual mode and use PWM_PERIOD/PWM_HIGH_WIDTH.
	 */
	अगर (!mdp->data->has_commit) अणु
		mtk_disp_pwm_update_bits(mdp, mdp->data->bls_debug,
					 mdp->data->bls_debug_mask,
					 mdp->data->bls_debug_mask);
		mtk_disp_pwm_update_bits(mdp, mdp->data->con0,
					 mdp->data->con0_sel,
					 mdp->data->con0_sel);
	पूर्ण

	वापस 0;

disable_clk_mm:
	clk_unprepare(mdp->clk_mm);
disable_clk_मुख्य:
	clk_unprepare(mdp->clk_मुख्य);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_disp_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_disp_pwm *mdp = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&mdp->chip);
	clk_unprepare(mdp->clk_mm);
	clk_unprepare(mdp->clk_मुख्य);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा mtk_pwm_data mt2701_pwm_data = अणु
	.enable_mask = BIT(16),
	.con0 = 0xa8,
	.con0_sel = 0x2,
	.con1 = 0xac,
	.has_commit = false,
	.bls_debug = 0xb0,
	.bls_debug_mask = 0x3,
पूर्ण;

अटल स्थिर काष्ठा mtk_pwm_data mt8173_pwm_data = अणु
	.enable_mask = BIT(0),
	.con0 = 0x10,
	.con0_sel = 0x0,
	.con1 = 0x14,
	.has_commit = true,
	.commit = 0x8,
	.commit_mask = 0x1,
पूर्ण;

अटल स्थिर काष्ठा mtk_pwm_data mt8183_pwm_data = अणु
	.enable_mask = BIT(0),
	.con0 = 0x18,
	.con0_sel = 0x0,
	.con1 = 0x1c,
	.has_commit = false,
	.bls_debug = 0x80,
	.bls_debug_mask = 0x3,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mtk_disp_pwm_of_match[] = अणु
	अणु .compatible = "mediatek,mt2701-disp-pwm", .data = &mt2701_pwm_dataपूर्ण,
	अणु .compatible = "mediatek,mt6595-disp-pwm", .data = &mt8173_pwm_dataपूर्ण,
	अणु .compatible = "mediatek,mt8173-disp-pwm", .data = &mt8173_pwm_dataपूर्ण,
	अणु .compatible = "mediatek,mt8183-disp-pwm", .data = &mt8183_pwm_dataपूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_disp_pwm_of_match);

अटल काष्ठा platक्रमm_driver mtk_disp_pwm_driver = अणु
	.driver = अणु
		.name = "mediatek-disp-pwm",
		.of_match_table = mtk_disp_pwm_of_match,
	पूर्ण,
	.probe = mtk_disp_pwm_probe,
	.हटाओ = mtk_disp_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(mtk_disp_pwm_driver);

MODULE_AUTHOR("YH Huang <yh.huang@mediatek.com>");
MODULE_DESCRIPTION("MediaTek SoC display PWM driver");
MODULE_LICENSE("GPL v2");
