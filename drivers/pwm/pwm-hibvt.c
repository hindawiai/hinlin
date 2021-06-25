<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PWM Controller Driver क्रम HiSilicon BVT SoCs
 *
 * Copyright (c) 2016 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/reset.h>

#घोषणा PWM_CFG0_ADDR(x)    (((x) * 0x20) + 0x0)
#घोषणा PWM_CFG1_ADDR(x)    (((x) * 0x20) + 0x4)
#घोषणा PWM_CFG2_ADDR(x)    (((x) * 0x20) + 0x8)
#घोषणा PWM_CTRL_ADDR(x)    (((x) * 0x20) + 0xC)

#घोषणा PWM_ENABLE_SHIFT    0
#घोषणा PWM_ENABLE_MASK     BIT(0)

#घोषणा PWM_POLARITY_SHIFT  1
#घोषणा PWM_POLARITY_MASK   BIT(1)

#घोषणा PWM_KEEP_SHIFT      2
#घोषणा PWM_KEEP_MASK       BIT(2)

#घोषणा PWM_PERIOD_MASK     GENMASK(31, 0)
#घोषणा PWM_DUTY_MASK       GENMASK(31, 0)

काष्ठा hibvt_pwm_chip अणु
	काष्ठा pwm_chip	chip;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	काष्ठा reset_control *rstc;
	स्थिर काष्ठा hibvt_pwm_soc *soc;
पूर्ण;

काष्ठा hibvt_pwm_soc अणु
	u32 num_pwms;
	bool quirk_क्रमce_enable;
पूर्ण;

अटल स्थिर काष्ठा hibvt_pwm_soc hi3516cv300_soc_info = अणु
	.num_pwms = 4,
पूर्ण;

अटल स्थिर काष्ठा hibvt_pwm_soc hi3519v100_soc_info = अणु
	.num_pwms = 8,
पूर्ण;

अटल स्थिर काष्ठा hibvt_pwm_soc hi3559v100_shub_soc_info = अणु
	.num_pwms = 8,
	.quirk_क्रमce_enable = true,
पूर्ण;

अटल स्थिर काष्ठा hibvt_pwm_soc hi3559v100_soc_info = अणु
	.num_pwms = 2,
	.quirk_क्रमce_enable = true,
पूर्ण;

अटल अंतरभूत काष्ठा hibvt_pwm_chip *to_hibvt_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा hibvt_pwm_chip, chip);
पूर्ण

अटल व्योम hibvt_pwm_set_bits(व्योम __iomem *base, u32 offset,
					u32 mask, u32 data)
अणु
	व्योम __iomem *address = base + offset;
	u32 value;

	value = पढ़ोl(address);
	value &= ~mask;
	value |= (data & mask);
	ग_लिखोl(value, address);
पूर्ण

अटल व्योम hibvt_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTRL_ADDR(pwm->hwpwm),
			PWM_ENABLE_MASK, 0x1);
पूर्ण

अटल व्योम hibvt_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTRL_ADDR(pwm->hwpwm),
			PWM_ENABLE_MASK, 0x0);
पूर्ण

अटल व्योम hibvt_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
					पूर्णांक duty_cycle_ns, पूर्णांक period_ns)
अणु
	काष्ठा hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);
	u32 freq, period, duty;

	freq = भाग_u64(clk_get_rate(hi_pwm_chip->clk), 1000000);

	period = भाग_u64(freq * period_ns, 1000);
	duty = भाग_u64(period * duty_cycle_ns, period_ns);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CFG0_ADDR(pwm->hwpwm),
			PWM_PERIOD_MASK, period);

	hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CFG1_ADDR(pwm->hwpwm),
			PWM_DUTY_MASK, duty);
पूर्ण

अटल व्योम hibvt_pwm_set_polarity(काष्ठा pwm_chip *chip,
					काष्ठा pwm_device *pwm,
					क्रमागत pwm_polarity polarity)
अणु
	काष्ठा hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	अगर (polarity == PWM_POLARITY_INVERSED)
		hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTRL_ADDR(pwm->hwpwm),
				PWM_POLARITY_MASK, (0x1 << PWM_POLARITY_SHIFT));
	अन्यथा
		hibvt_pwm_set_bits(hi_pwm_chip->base, PWM_CTRL_ADDR(pwm->hwpwm),
				PWM_POLARITY_MASK, (0x0 << PWM_POLARITY_SHIFT));
पूर्ण

अटल व्योम hibvt_pwm_get_state(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				काष्ठा pwm_state *state)
अणु
	काष्ठा hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);
	व्योम __iomem *base;
	u32 freq, value;

	freq = भाग_u64(clk_get_rate(hi_pwm_chip->clk), 1000000);
	base = hi_pwm_chip->base;

	value = पढ़ोl(base + PWM_CFG0_ADDR(pwm->hwpwm));
	state->period = भाग_u64(value * 1000, freq);

	value = पढ़ोl(base + PWM_CFG1_ADDR(pwm->hwpwm));
	state->duty_cycle = भाग_u64(value * 1000, freq);

	value = पढ़ोl(base + PWM_CTRL_ADDR(pwm->hwpwm));
	state->enabled = (PWM_ENABLE_MASK & value);
पूर्ण

अटल पूर्णांक hibvt_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			   स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा hibvt_pwm_chip *hi_pwm_chip = to_hibvt_pwm_chip(chip);

	अगर (state->polarity != pwm->state.polarity)
		hibvt_pwm_set_polarity(chip, pwm, state->polarity);

	अगर (state->period != pwm->state.period ||
	    state->duty_cycle != pwm->state.duty_cycle) अणु
		hibvt_pwm_config(chip, pwm, state->duty_cycle, state->period);

		/*
		 * Some implementations require the PWM to be enabled twice
		 * each समय the duty cycle is refreshed.
		 */
		अगर (hi_pwm_chip->soc->quirk_क्रमce_enable && state->enabled)
			hibvt_pwm_enable(chip, pwm);
	पूर्ण

	अगर (state->enabled != pwm->state.enabled) अणु
		अगर (state->enabled)
			hibvt_pwm_enable(chip, pwm);
		अन्यथा
			hibvt_pwm_disable(chip, pwm);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops hibvt_pwm_ops = अणु
	.get_state = hibvt_pwm_get_state,
	.apply = hibvt_pwm_apply,

	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक hibvt_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा hibvt_pwm_soc *soc =
				of_device_get_match_data(&pdev->dev);
	काष्ठा hibvt_pwm_chip *pwm_chip;
	पूर्णांक ret, i;

	pwm_chip = devm_kzalloc(&pdev->dev, माप(*pwm_chip), GFP_KERNEL);
	अगर (pwm_chip == शून्य)
		वापस -ENOMEM;

	pwm_chip->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pwm_chip->clk)) अणु
		dev_err(&pdev->dev, "getting clock failed with %ld\n",
				PTR_ERR(pwm_chip->clk));
		वापस PTR_ERR(pwm_chip->clk);
	पूर्ण

	pwm_chip->chip.ops = &hibvt_pwm_ops;
	pwm_chip->chip.dev = &pdev->dev;
	pwm_chip->chip.npwm = soc->num_pwms;
	pwm_chip->chip.of_xlate = of_pwm_xlate_with_flags;
	pwm_chip->chip.of_pwm_n_cells = 3;
	pwm_chip->soc = soc;

	pwm_chip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pwm_chip->base))
		वापस PTR_ERR(pwm_chip->base);

	ret = clk_prepare_enable(pwm_chip->clk);
	अगर (ret < 0)
		वापस ret;

	pwm_chip->rstc = devm_reset_control_get_exclusive(&pdev->dev, शून्य);
	अगर (IS_ERR(pwm_chip->rstc)) अणु
		clk_disable_unprepare(pwm_chip->clk);
		वापस PTR_ERR(pwm_chip->rstc);
	पूर्ण

	reset_control_निश्चित(pwm_chip->rstc);
	msleep(30);
	reset_control_deनिश्चित(pwm_chip->rstc);

	ret = pwmchip_add(&pwm_chip->chip);
	अगर (ret < 0) अणु
		clk_disable_unprepare(pwm_chip->clk);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < pwm_chip->chip.npwm; i++) अणु
		hibvt_pwm_set_bits(pwm_chip->base, PWM_CTRL_ADDR(i),
				PWM_KEEP_MASK, (0x1 << PWM_KEEP_SHIFT));
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwm_chip);

	वापस 0;
पूर्ण

अटल पूर्णांक hibvt_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hibvt_pwm_chip *pwm_chip;

	pwm_chip = platक्रमm_get_drvdata(pdev);

	reset_control_निश्चित(pwm_chip->rstc);
	msleep(30);
	reset_control_deनिश्चित(pwm_chip->rstc);

	clk_disable_unprepare(pwm_chip->clk);

	वापस pwmchip_हटाओ(&pwm_chip->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id hibvt_pwm_of_match[] = अणु
	अणु .compatible = "hisilicon,hi3516cv300-pwm",
	  .data = &hi3516cv300_soc_info पूर्ण,
	अणु .compatible = "hisilicon,hi3519v100-pwm",
	  .data = &hi3519v100_soc_info पूर्ण,
	अणु .compatible = "hisilicon,hi3559v100-shub-pwm",
	  .data = &hi3559v100_shub_soc_info पूर्ण,
	अणु .compatible = "hisilicon,hi3559v100-pwm",
	  .data = &hi3559v100_soc_info पूर्ण,
	अणु  पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hibvt_pwm_of_match);

अटल काष्ठा platक्रमm_driver hibvt_pwm_driver = अणु
	.driver = अणु
		.name = "hibvt-pwm",
		.of_match_table = hibvt_pwm_of_match,
	पूर्ण,
	.probe = hibvt_pwm_probe,
	.हटाओ	= hibvt_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(hibvt_pwm_driver);

MODULE_AUTHOR("Jian Yuan");
MODULE_DESCRIPTION("HiSilicon BVT SoCs PWM driver");
MODULE_LICENSE("GPL");
