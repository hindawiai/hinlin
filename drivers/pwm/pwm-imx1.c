<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * simple driver क्रम PWM (Pulse Width Modulator) controller
 *
 * Derived from pxa PWM driver by eric miao <eric.miao@marvell.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा MX1_PWMC			0x00   /* PWM Control Register */
#घोषणा MX1_PWMS			0x04   /* PWM Sample Register */
#घोषणा MX1_PWMP			0x08   /* PWM Period Register */

#घोषणा MX1_PWMC_EN			BIT(4)

काष्ठा pwm_imx1_chip अणु
	काष्ठा clk *clk_ipg;
	काष्ठा clk *clk_per;
	व्योम __iomem *mmio_base;
	काष्ठा pwm_chip chip;
पूर्ण;

#घोषणा to_pwm_imx1_chip(chip)	container_of(chip, काष्ठा pwm_imx1_chip, chip)

अटल पूर्णांक pwm_imx1_clk_prepare_enable(काष्ठा pwm_chip *chip)
अणु
	काष्ठा pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	पूर्णांक ret;

	ret = clk_prepare_enable(imx->clk_ipg);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(imx->clk_per);
	अगर (ret) अणु
		clk_disable_unprepare(imx->clk_ipg);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pwm_imx1_clk_disable_unprepare(काष्ठा pwm_chip *chip)
अणु
	काष्ठा pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);

	clk_disable_unprepare(imx->clk_per);
	clk_disable_unprepare(imx->clk_ipg);
पूर्ण

अटल पूर्णांक pwm_imx1_config(काष्ठा pwm_chip *chip,
			   काष्ठा pwm_device *pwm, पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 max, p;

	/*
	 * The PWM subप्रणाली allows क्रम exact frequencies. However,
	 * I cannot connect a scope on my device to the PWM line and
	 * thus cannot provide the program the PWM controller
	 * exactly. Instead, I'm relying on the fact that the
	 * Bootloader (u-boot or WinCE+haret) has programmed the PWM
	 * function group alपढ़ोy. So I'll just modअगरy the PWM sample
	 * रेजिस्टर to follow the ratio of duty_ns vs. period_ns
	 * accordingly.
	 *
	 * This is good enough क्रम programming the brightness of
	 * the LCD backlight.
	 *
	 * The real implementation would भागide PERCLK[0] first by
	 * both the prescaler (/1 .. /128) and then by CLKSEL
	 * (/2 .. /16).
	 */
	max = पढ़ोl(imx->mmio_base + MX1_PWMP);
	p = max * duty_ns / period_ns;

	ग_लिखोl(max - p, imx->mmio_base + MX1_PWMS);

	वापस 0;
पूर्ण

अटल पूर्णांक pwm_imx1_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 value;
	पूर्णांक ret;

	ret = pwm_imx1_clk_prepare_enable(chip);
	अगर (ret < 0)
		वापस ret;

	value = पढ़ोl(imx->mmio_base + MX1_PWMC);
	value |= MX1_PWMC_EN;
	ग_लिखोl(value, imx->mmio_base + MX1_PWMC);

	वापस 0;
पूर्ण

अटल व्योम pwm_imx1_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_imx1_chip *imx = to_pwm_imx1_chip(chip);
	u32 value;

	value = पढ़ोl(imx->mmio_base + MX1_PWMC);
	value &= ~MX1_PWMC_EN;
	ग_लिखोl(value, imx->mmio_base + MX1_PWMC);

	pwm_imx1_clk_disable_unprepare(chip);
पूर्ण

अटल स्थिर काष्ठा pwm_ops pwm_imx1_ops = अणु
	.enable = pwm_imx1_enable,
	.disable = pwm_imx1_disable,
	.config = pwm_imx1_config,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pwm_imx1_dt_ids[] = अणु
	अणु .compatible = "fsl,imx1-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_imx1_dt_ids);

अटल पूर्णांक pwm_imx1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_imx1_chip *imx;

	imx = devm_kzalloc(&pdev->dev, माप(*imx), GFP_KERNEL);
	अगर (!imx)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, imx);

	imx->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(imx->clk_ipg))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(imx->clk_ipg),
				     "getting ipg clock failed\n");

	imx->clk_per = devm_clk_get(&pdev->dev, "per");
	अगर (IS_ERR(imx->clk_per))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(imx->clk_per),
				     "failed to get peripheral clock\n");

	imx->chip.ops = &pwm_imx1_ops;
	imx->chip.dev = &pdev->dev;
	imx->chip.npwm = 1;

	imx->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(imx->mmio_base))
		वापस PTR_ERR(imx->mmio_base);

	वापस pwmchip_add(&imx->chip);
पूर्ण

अटल पूर्णांक pwm_imx1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_imx1_chip *imx = platक्रमm_get_drvdata(pdev);

	pwm_imx1_clk_disable_unprepare(&imx->chip);

	वापस pwmchip_हटाओ(&imx->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver pwm_imx1_driver = अणु
	.driver = अणु
		.name = "pwm-imx1",
		.of_match_table = pwm_imx1_dt_ids,
	पूर्ण,
	.probe = pwm_imx1_probe,
	.हटाओ = pwm_imx1_हटाओ,
पूर्ण;
module_platक्रमm_driver(pwm_imx1_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
