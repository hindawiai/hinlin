<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Car PWM Timer driver
 *
 * Copyright (C) 2015 Renesas Electronics Corporation
 *
 * Limitations:
 * - The hardware cannot generate a 0% duty cycle.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/math64.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा RCAR_PWM_MAX_DIVISION	24
#घोषणा RCAR_PWM_MAX_CYCLE	1023

#घोषणा RCAR_PWMCR		0x00
#घोषणा  RCAR_PWMCR_CC0_MASK	0x000f0000
#घोषणा  RCAR_PWMCR_CC0_SHIFT	16
#घोषणा  RCAR_PWMCR_CCMD	BIT(15)
#घोषणा  RCAR_PWMCR_SYNC	BIT(11)
#घोषणा  RCAR_PWMCR_SS0		BIT(4)
#घोषणा  RCAR_PWMCR_EN0		BIT(0)

#घोषणा RCAR_PWMCNT		0x04
#घोषणा  RCAR_PWMCNT_CYC0_MASK	0x03ff0000
#घोषणा  RCAR_PWMCNT_CYC0_SHIFT	16
#घोषणा  RCAR_PWMCNT_PH0_MASK	0x000003ff
#घोषणा  RCAR_PWMCNT_PH0_SHIFT	0

काष्ठा rcar_pwm_chip अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

अटल अंतरभूत काष्ठा rcar_pwm_chip *to_rcar_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा rcar_pwm_chip, chip);
पूर्ण

अटल व्योम rcar_pwm_ग_लिखो(काष्ठा rcar_pwm_chip *rp, u32 data,
			   अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(data, rp->base + offset);
पूर्ण

अटल u32 rcar_pwm_पढ़ो(काष्ठा rcar_pwm_chip *rp, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(rp->base + offset);
पूर्ण

अटल व्योम rcar_pwm_update(काष्ठा rcar_pwm_chip *rp, u32 mask, u32 data,
			    अचिन्हित पूर्णांक offset)
अणु
	u32 value;

	value = rcar_pwm_पढ़ो(rp, offset);
	value &= ~mask;
	value |= data & mask;
	rcar_pwm_ग_लिखो(rp, value, offset);
पूर्ण

अटल पूर्णांक rcar_pwm_get_घड़ी_भागision(काष्ठा rcar_pwm_chip *rp, पूर्णांक period_ns)
अणु
	अचिन्हित दीर्घ clk_rate = clk_get_rate(rp->clk);
	u64 भाग, पंचांगp;

	अगर (clk_rate == 0)
		वापस -EINVAL;

	भाग = (u64)NSEC_PER_SEC * RCAR_PWM_MAX_CYCLE;
	पंचांगp = (u64)period_ns * clk_rate + भाग - 1;
	पंचांगp = भाग64_u64(पंचांगp, भाग);
	भाग = ilog2(पंचांगp - 1) + 1;

	वापस (भाग <= RCAR_PWM_MAX_DIVISION) ? भाग : -दुस्फल;
पूर्ण

अटल व्योम rcar_pwm_set_घड़ी_control(काष्ठा rcar_pwm_chip *rp,
				       अचिन्हित पूर्णांक भाग)
अणु
	u32 value;

	value = rcar_pwm_पढ़ो(rp, RCAR_PWMCR);
	value &= ~(RCAR_PWMCR_CCMD | RCAR_PWMCR_CC0_MASK);

	अगर (भाग & 1)
		value |= RCAR_PWMCR_CCMD;

	भाग >>= 1;

	value |= भाग << RCAR_PWMCR_CC0_SHIFT;
	rcar_pwm_ग_लिखो(rp, value, RCAR_PWMCR);
पूर्ण

अटल पूर्णांक rcar_pwm_set_counter(काष्ठा rcar_pwm_chip *rp, पूर्णांक भाग, पूर्णांक duty_ns,
				पूर्णांक period_ns)
अणु
	अचिन्हित दीर्घ दीर्घ one_cycle, पंचांगp;	/* 0.01 nanoseconds */
	अचिन्हित दीर्घ clk_rate = clk_get_rate(rp->clk);
	u32 cyc, ph;

	one_cycle = (अचिन्हित दीर्घ दीर्घ)NSEC_PER_SEC * 100ULL * (1 << भाग);
	करो_भाग(one_cycle, clk_rate);

	पंचांगp = period_ns * 100ULL;
	करो_भाग(पंचांगp, one_cycle);
	cyc = (पंचांगp << RCAR_PWMCNT_CYC0_SHIFT) & RCAR_PWMCNT_CYC0_MASK;

	पंचांगp = duty_ns * 100ULL;
	करो_भाग(पंचांगp, one_cycle);
	ph = पंचांगp & RCAR_PWMCNT_PH0_MASK;

	/* Aव्योम prohibited setting */
	अगर (cyc == 0 || ph == 0)
		वापस -EINVAL;

	rcar_pwm_ग_लिखो(rp, cyc | ph, RCAR_PWMCNT);

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	वापस pm_runसमय_get_sync(chip->dev);
पूर्ण

अटल व्योम rcar_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	pm_runसमय_put(chip->dev);
पूर्ण

अटल पूर्णांक rcar_pwm_enable(काष्ठा rcar_pwm_chip *rp)
अणु
	u32 value;

	/* Don't enable the PWM device अगर CYC0 or PH0 is 0 */
	value = rcar_pwm_पढ़ो(rp, RCAR_PWMCNT);
	अगर ((value & RCAR_PWMCNT_CYC0_MASK) == 0 ||
	    (value & RCAR_PWMCNT_PH0_MASK) == 0)
		वापस -EINVAL;

	rcar_pwm_update(rp, RCAR_PWMCR_EN0, RCAR_PWMCR_EN0, RCAR_PWMCR);

	वापस 0;
पूर्ण

अटल व्योम rcar_pwm_disable(काष्ठा rcar_pwm_chip *rp)
अणु
	rcar_pwm_update(rp, RCAR_PWMCR_EN0, 0, RCAR_PWMCR);
पूर्ण

अटल पूर्णांक rcar_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			  स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा rcar_pwm_chip *rp = to_rcar_pwm_chip(chip);
	पूर्णांक भाग, ret;

	/* This HW/driver only supports normal polarity */
	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	अगर (!state->enabled) अणु
		rcar_pwm_disable(rp);
		वापस 0;
	पूर्ण

	भाग = rcar_pwm_get_घड़ी_भागision(rp, state->period);
	अगर (भाग < 0)
		वापस भाग;

	rcar_pwm_update(rp, RCAR_PWMCR_SYNC, RCAR_PWMCR_SYNC, RCAR_PWMCR);

	ret = rcar_pwm_set_counter(rp, भाग, state->duty_cycle, state->period);
	अगर (!ret)
		rcar_pwm_set_घड़ी_control(rp, भाग);

	/* The SYNC should be set to 0 even अगर rcar_pwm_set_counter failed */
	rcar_pwm_update(rp, RCAR_PWMCR_SYNC, 0, RCAR_PWMCR);

	अगर (!ret)
		ret = rcar_pwm_enable(rp);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops rcar_pwm_ops = अणु
	.request = rcar_pwm_request,
	.मुक्त = rcar_pwm_मुक्त,
	.apply = rcar_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक rcar_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_pwm_chip *rcar_pwm;
	पूर्णांक ret;

	rcar_pwm = devm_kzalloc(&pdev->dev, माप(*rcar_pwm), GFP_KERNEL);
	अगर (rcar_pwm == शून्य)
		वापस -ENOMEM;

	rcar_pwm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rcar_pwm->base))
		वापस PTR_ERR(rcar_pwm->base);

	rcar_pwm->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rcar_pwm->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(rcar_pwm->clk);
	पूर्ण

	platक्रमm_set_drvdata(pdev, rcar_pwm);

	rcar_pwm->chip.dev = &pdev->dev;
	rcar_pwm->chip.ops = &rcar_pwm_ops;
	rcar_pwm->chip.npwm = 1;

	pm_runसमय_enable(&pdev->dev);

	ret = pwmchip_add(&rcar_pwm->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register PWM chip: %d\n", ret);
		pm_runसमय_disable(&pdev->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rcar_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rcar_pwm_chip *rcar_pwm = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&rcar_pwm->chip);

	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id rcar_pwm_of_table[] = अणु
	अणु .compatible = "renesas,pwm-rcar", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rcar_pwm_of_table);

अटल काष्ठा platक्रमm_driver rcar_pwm_driver = अणु
	.probe = rcar_pwm_probe,
	.हटाओ = rcar_pwm_हटाओ,
	.driver = अणु
		.name = "pwm-rcar",
		.of_match_table = of_match_ptr(rcar_pwm_of_table),
	पूर्ण
पूर्ण;
module_platक्रमm_driver(rcar_pwm_driver);

MODULE_AUTHOR("Yoshihiro Shimoda <yoshihiro.shimoda.uh@renesas.com>");
MODULE_DESCRIPTION("Renesas PWM Timer Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:pwm-rcar");
