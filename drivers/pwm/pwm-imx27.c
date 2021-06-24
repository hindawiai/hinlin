<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * simple driver क्रम PWM (Pulse Width Modulator) controller
 *
 * Derived from pxa PWM driver by eric miao <eric.miao@marvell.com>
 *
 * Limitations:
 * - When disabled the output is driven to 0 independent of the configured
 *   polarity.
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
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा MX3_PWMCR			0x00    /* PWM Control Register */
#घोषणा MX3_PWMSR			0x04    /* PWM Status Register */
#घोषणा MX3_PWMSAR			0x0C    /* PWM Sample Register */
#घोषणा MX3_PWMPR			0x10    /* PWM Period Register */

#घोषणा MX3_PWMCR_FWM			GENMASK(27, 26)
#घोषणा MX3_PWMCR_STOPEN		BIT(25)
#घोषणा MX3_PWMCR_DOZEN			BIT(24)
#घोषणा MX3_PWMCR_WAITEN		BIT(23)
#घोषणा MX3_PWMCR_DBGEN			BIT(22)
#घोषणा MX3_PWMCR_BCTR			BIT(21)
#घोषणा MX3_PWMCR_HCTR			BIT(20)

#घोषणा MX3_PWMCR_POUTC			GENMASK(19, 18)
#घोषणा MX3_PWMCR_POUTC_NORMAL		0
#घोषणा MX3_PWMCR_POUTC_INVERTED	1
#घोषणा MX3_PWMCR_POUTC_OFF		2

#घोषणा MX3_PWMCR_CLKSRC		GENMASK(17, 16)
#घोषणा MX3_PWMCR_CLKSRC_OFF		0
#घोषणा MX3_PWMCR_CLKSRC_IPG		1
#घोषणा MX3_PWMCR_CLKSRC_IPG_HIGH	2
#घोषणा MX3_PWMCR_CLKSRC_IPG_32K	3

#घोषणा MX3_PWMCR_PRESCALER		GENMASK(15, 4)

#घोषणा MX3_PWMCR_SWR			BIT(3)

#घोषणा MX3_PWMCR_REPEAT		GENMASK(2, 1)
#घोषणा MX3_PWMCR_REPEAT_1X		0
#घोषणा MX3_PWMCR_REPEAT_2X		1
#घोषणा MX3_PWMCR_REPEAT_4X		2
#घोषणा MX3_PWMCR_REPEAT_8X		3

#घोषणा MX3_PWMCR_EN			BIT(0)

#घोषणा MX3_PWMSR_FWE			BIT(6)
#घोषणा MX3_PWMSR_CMP			BIT(5)
#घोषणा MX3_PWMSR_ROV			BIT(4)
#घोषणा MX3_PWMSR_FE			BIT(3)

#घोषणा MX3_PWMSR_FIFOAV		GENMASK(2, 0)
#घोषणा MX3_PWMSR_FIFOAV_EMPTY		0
#घोषणा MX3_PWMSR_FIFOAV_1WORD		1
#घोषणा MX3_PWMSR_FIFOAV_2WORDS		2
#घोषणा MX3_PWMSR_FIFOAV_3WORDS		3
#घोषणा MX3_PWMSR_FIFOAV_4WORDS		4

#घोषणा MX3_PWMCR_PRESCALER_SET(x)	FIELD_PREP(MX3_PWMCR_PRESCALER, (x) - 1)
#घोषणा MX3_PWMCR_PRESCALER_GET(x)	(FIELD_GET(MX3_PWMCR_PRESCALER, \
						   (x)) + 1)

#घोषणा MX3_PWM_SWR_LOOP		5

/* PWMPR रेजिस्टर value of 0xffff has the same effect as 0xfffe */
#घोषणा MX3_PWMPR_MAX			0xfffe

काष्ठा pwm_imx27_chip अणु
	काष्ठा clk	*clk_ipg;
	काष्ठा clk	*clk_per;
	व्योम __iomem	*mmio_base;
	काष्ठा pwm_chip	chip;

	/*
	 * The driver cannot पढ़ो the current duty cycle from the hardware अगर
	 * the hardware is disabled. Cache the last programmed duty cycle
	 * value to वापस in that हाल.
	 */
	अचिन्हित पूर्णांक duty_cycle;
पूर्ण;

#घोषणा to_pwm_imx27_chip(chip)	container_of(chip, काष्ठा pwm_imx27_chip, chip)

अटल पूर्णांक pwm_imx27_clk_prepare_enable(काष्ठा pwm_imx27_chip *imx)
अणु
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

अटल व्योम pwm_imx27_clk_disable_unprepare(काष्ठा pwm_imx27_chip *imx)
अणु
	clk_disable_unprepare(imx->clk_per);
	clk_disable_unprepare(imx->clk_ipg);
पूर्ण

अटल व्योम pwm_imx27_get_state(काष्ठा pwm_chip *chip,
				काष्ठा pwm_device *pwm, काष्ठा pwm_state *state)
अणु
	काष्ठा pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	u32 period, prescaler, pwm_clk, val;
	u64 पंचांगp;
	पूर्णांक ret;

	ret = pwm_imx27_clk_prepare_enable(imx);
	अगर (ret < 0)
		वापस;

	val = पढ़ोl(imx->mmio_base + MX3_PWMCR);

	अगर (val & MX3_PWMCR_EN)
		state->enabled = true;
	अन्यथा
		state->enabled = false;

	चयन (FIELD_GET(MX3_PWMCR_POUTC, val)) अणु
	हाल MX3_PWMCR_POUTC_NORMAL:
		state->polarity = PWM_POLARITY_NORMAL;
		अवरोध;
	हाल MX3_PWMCR_POUTC_INVERTED:
		state->polarity = PWM_POLARITY_INVERSED;
		अवरोध;
	शेष:
		dev_warn(chip->dev, "can't set polarity, output disconnected");
	पूर्ण

	prescaler = MX3_PWMCR_PRESCALER_GET(val);
	pwm_clk = clk_get_rate(imx->clk_per);
	val = पढ़ोl(imx->mmio_base + MX3_PWMPR);
	period = val >= MX3_PWMPR_MAX ? MX3_PWMPR_MAX : val;

	/* PWMOUT (Hz) = PWMCLK / (PWMPR + 2) */
	पंचांगp = NSEC_PER_SEC * (u64)(period + 2) * prescaler;
	state->period = DIV_ROUND_UP_ULL(पंचांगp, pwm_clk);

	/*
	 * PWMSAR can be पढ़ो only अगर PWM is enabled. If the PWM is disabled,
	 * use the cached value.
	 */
	अगर (state->enabled)
		val = पढ़ोl(imx->mmio_base + MX3_PWMSAR);
	अन्यथा
		val = imx->duty_cycle;

	पंचांगp = NSEC_PER_SEC * (u64)(val) * prescaler;
	state->duty_cycle = DIV_ROUND_UP_ULL(पंचांगp, pwm_clk);

	pwm_imx27_clk_disable_unprepare(imx);
पूर्ण

अटल व्योम pwm_imx27_sw_reset(काष्ठा pwm_chip *chip)
अणु
	काष्ठा pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	काष्ठा device *dev = chip->dev;
	पूर्णांक रुको_count = 0;
	u32 cr;

	ग_लिखोl(MX3_PWMCR_SWR, imx->mmio_base + MX3_PWMCR);
	करो अणु
		usleep_range(200, 1000);
		cr = पढ़ोl(imx->mmio_base + MX3_PWMCR);
	पूर्ण जबतक ((cr & MX3_PWMCR_SWR) &&
		 (रुको_count++ < MX3_PWM_SWR_LOOP));

	अगर (cr & MX3_PWMCR_SWR)
		dev_warn(dev, "software reset timeout\n");
पूर्ण

अटल व्योम pwm_imx27_रुको_fअगरo_slot(काष्ठा pwm_chip *chip,
				     काष्ठा pwm_device *pwm)
अणु
	काष्ठा pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	काष्ठा device *dev = chip->dev;
	अचिन्हित पूर्णांक period_ms;
	पूर्णांक fअगरoav;
	u32 sr;

	sr = पढ़ोl(imx->mmio_base + MX3_PWMSR);
	fअगरoav = FIELD_GET(MX3_PWMSR_FIFOAV, sr);
	अगर (fअगरoav == MX3_PWMSR_FIFOAV_4WORDS) अणु
		period_ms = DIV_ROUND_UP_ULL(pwm_get_period(pwm),
					 NSEC_PER_MSEC);
		msleep(period_ms);

		sr = पढ़ोl(imx->mmio_base + MX3_PWMSR);
		अगर (fअगरoav == FIELD_GET(MX3_PWMSR_FIFOAV, sr))
			dev_warn(dev, "there is no free FIFO slot\n");
	पूर्ण
पूर्ण

अटल पूर्णांक pwm_imx27_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   स्थिर काष्ठा pwm_state *state)
अणु
	अचिन्हित दीर्घ period_cycles, duty_cycles, prescale;
	काष्ठा pwm_imx27_chip *imx = to_pwm_imx27_chip(chip);
	काष्ठा pwm_state cstate;
	अचिन्हित दीर्घ दीर्घ c;
	अचिन्हित दीर्घ दीर्घ clkrate;
	पूर्णांक ret;
	u32 cr;

	pwm_get_state(pwm, &cstate);

	clkrate = clk_get_rate(imx->clk_per);
	c = clkrate * state->period;

	करो_भाग(c, NSEC_PER_SEC);
	period_cycles = c;

	prescale = period_cycles / 0x10000 + 1;

	period_cycles /= prescale;
	c = clkrate * state->duty_cycle;
	करो_भाग(c, NSEC_PER_SEC);
	duty_cycles = c;
	duty_cycles /= prescale;

	/*
	 * according to imx pwm RM, the real period value should be PERIOD
	 * value in PWMPR plus 2.
	 */
	अगर (period_cycles > 2)
		period_cycles -= 2;
	अन्यथा
		period_cycles = 0;

	/*
	 * Wait क्रम a मुक्त FIFO slot अगर the PWM is alपढ़ोy enabled, and flush
	 * the FIFO अगर the PWM was disabled and is about to be enabled.
	 */
	अगर (cstate.enabled) अणु
		pwm_imx27_रुको_fअगरo_slot(chip, pwm);
	पूर्ण अन्यथा अणु
		ret = pwm_imx27_clk_prepare_enable(imx);
		अगर (ret)
			वापस ret;

		pwm_imx27_sw_reset(chip);
	पूर्ण

	ग_लिखोl(duty_cycles, imx->mmio_base + MX3_PWMSAR);
	ग_लिखोl(period_cycles, imx->mmio_base + MX3_PWMPR);

	/*
	 * Store the duty cycle क्रम future reference in हालs where the
	 * MX3_PWMSAR रेजिस्टर can't be पढ़ो (i.e. when the PWM is disabled).
	 */
	imx->duty_cycle = duty_cycles;

	cr = MX3_PWMCR_PRESCALER_SET(prescale) |
	     MX3_PWMCR_STOPEN | MX3_PWMCR_DOZEN | MX3_PWMCR_WAITEN |
	     FIELD_PREP(MX3_PWMCR_CLKSRC, MX3_PWMCR_CLKSRC_IPG_HIGH) |
	     MX3_PWMCR_DBGEN;

	अगर (state->polarity == PWM_POLARITY_INVERSED)
		cr |= FIELD_PREP(MX3_PWMCR_POUTC,
				MX3_PWMCR_POUTC_INVERTED);

	अगर (state->enabled)
		cr |= MX3_PWMCR_EN;

	ग_लिखोl(cr, imx->mmio_base + MX3_PWMCR);

	अगर (!state->enabled)
		pwm_imx27_clk_disable_unprepare(imx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops pwm_imx27_ops = अणु
	.apply = pwm_imx27_apply,
	.get_state = pwm_imx27_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id pwm_imx27_dt_ids[] = अणु
	अणु .compatible = "fsl,imx27-pwm", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_imx27_dt_ids);

अटल पूर्णांक pwm_imx27_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_imx27_chip *imx;
	पूर्णांक ret;
	u32 pwmcr;

	imx = devm_kzalloc(&pdev->dev, माप(*imx), GFP_KERNEL);
	अगर (imx == शून्य)
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

	imx->chip.ops = &pwm_imx27_ops;
	imx->chip.dev = &pdev->dev;
	imx->chip.npwm = 1;

	imx->chip.of_xlate = of_pwm_xlate_with_flags;
	imx->chip.of_pwm_n_cells = 3;

	imx->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(imx->mmio_base))
		वापस PTR_ERR(imx->mmio_base);

	ret = pwm_imx27_clk_prepare_enable(imx);
	अगर (ret)
		वापस ret;

	/* keep clks on अगर pwm is running */
	pwmcr = पढ़ोl(imx->mmio_base + MX3_PWMCR);
	अगर (!(pwmcr & MX3_PWMCR_EN))
		pwm_imx27_clk_disable_unprepare(imx);

	वापस pwmchip_add(&imx->chip);
पूर्ण

अटल पूर्णांक pwm_imx27_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pwm_imx27_chip *imx;

	imx = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&imx->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver imx_pwm_driver = अणु
	.driver = अणु
		.name = "pwm-imx27",
		.of_match_table = pwm_imx27_dt_ids,
	पूर्ण,
	.probe = pwm_imx27_probe,
	.हटाओ = pwm_imx27_हटाओ,
पूर्ण;
module_platक्रमm_driver(imx_pwm_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
