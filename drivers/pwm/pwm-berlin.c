<शैली गुरु>
/*
 * Marvell Berlin PWM driver
 *
 * Copyright (C) 2015 Marvell Technology Group Ltd.
 *
 * Author: Antoine Tenart <antoine.tenart@मुक्त-electrons.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा BERLIN_PWM_EN			0x0
#घोषणा  BERLIN_PWM_ENABLE		BIT(0)
#घोषणा BERLIN_PWM_CONTROL		0x4
/*
 * The prescaler claims to support 8 dअगरferent moduli, configured using the
 * low three bits of PWM_CONTROL. (Sequentially, they are 1, 4, 8, 16, 64,
 * 256, 1024, and 4096.)  However, the moduli from 4 to 1024 appear to be
 * implemented by पूर्णांकernally shअगरting TCNT left without adding additional
 * bits. So, the max TCNT that actually works क्रम a modulus of 4 is 0x3fff;
 * क्रम 8, 0x1fff; and so on. This means that those moduli are entirely
 * useless, as we could just करो the shअगरt ourselves. The 4096 modulus is
 * implemented with a real prescaler, so we करो use that, but we treat it
 * as a flag instead of pretending the modulus is actually configurable.
 */
#घोषणा  BERLIN_PWM_PRESCALE_4096	0x7
#घोषणा  BERLIN_PWM_INVERT_POLARITY	BIT(3)
#घोषणा BERLIN_PWM_DUTY			0x8
#घोषणा BERLIN_PWM_TCNT			0xc
#घोषणा  BERLIN_PWM_MAX_TCNT		65535

काष्ठा berlin_pwm_channel अणु
	u32 enable;
	u32 ctrl;
	u32 duty;
	u32 tcnt;
पूर्ण;

काष्ठा berlin_pwm_chip अणु
	काष्ठा pwm_chip chip;
	काष्ठा clk *clk;
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत काष्ठा berlin_pwm_chip *to_berlin_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा berlin_pwm_chip, chip);
पूर्ण

अटल अंतरभूत u32 berlin_pwm_पढ़ोl(काष्ठा berlin_pwm_chip *chip,
				   अचिन्हित पूर्णांक channel, अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोl_relaxed(chip->base + channel * 0x10 + offset);
पूर्ण

अटल अंतरभूत व्योम berlin_pwm_ग_लिखोl(काष्ठा berlin_pwm_chip *chip,
				     अचिन्हित पूर्णांक channel, u32 value,
				     अचिन्हित दीर्घ offset)
अणु
	ग_लिखोl_relaxed(value, chip->base + channel * 0x10 + offset);
पूर्ण

अटल पूर्णांक berlin_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा berlin_pwm_channel *channel;

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel)
		वापस -ENOMEM;

	वापस pwm_set_chip_data(pwm, channel);
पूर्ण

अटल व्योम berlin_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा berlin_pwm_channel *channel = pwm_get_chip_data(pwm);

	kमुक्त(channel);
पूर्ण

अटल पूर्णांक berlin_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm_dev,
			     पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा berlin_pwm_chip *pwm = to_berlin_pwm_chip(chip);
	bool prescale_4096 = false;
	u32 value, duty, period;
	u64 cycles;

	cycles = clk_get_rate(pwm->clk);
	cycles *= period_ns;
	करो_भाग(cycles, NSEC_PER_SEC);

	अगर (cycles > BERLIN_PWM_MAX_TCNT) अणु
		prescale_4096 = true;
		cycles >>= 12; // Prescaled by 4096

		अगर (cycles > BERLIN_PWM_MAX_TCNT)
			वापस -दुस्फल;
	पूर्ण

	period = cycles;
	cycles *= duty_ns;
	करो_भाग(cycles, period_ns);
	duty = cycles;

	value = berlin_pwm_पढ़ोl(pwm, pwm_dev->hwpwm, BERLIN_PWM_CONTROL);
	अगर (prescale_4096)
		value |= BERLIN_PWM_PRESCALE_4096;
	अन्यथा
		value &= ~BERLIN_PWM_PRESCALE_4096;
	berlin_pwm_ग_लिखोl(pwm, pwm_dev->hwpwm, value, BERLIN_PWM_CONTROL);

	berlin_pwm_ग_लिखोl(pwm, pwm_dev->hwpwm, duty, BERLIN_PWM_DUTY);
	berlin_pwm_ग_लिखोl(pwm, pwm_dev->hwpwm, period, BERLIN_PWM_TCNT);

	वापस 0;
पूर्ण

अटल पूर्णांक berlin_pwm_set_polarity(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm_dev,
				   क्रमागत pwm_polarity polarity)
अणु
	काष्ठा berlin_pwm_chip *pwm = to_berlin_pwm_chip(chip);
	u32 value;

	value = berlin_pwm_पढ़ोl(pwm, pwm_dev->hwpwm, BERLIN_PWM_CONTROL);

	अगर (polarity == PWM_POLARITY_NORMAL)
		value &= ~BERLIN_PWM_INVERT_POLARITY;
	अन्यथा
		value |= BERLIN_PWM_INVERT_POLARITY;

	berlin_pwm_ग_लिखोl(pwm, pwm_dev->hwpwm, value, BERLIN_PWM_CONTROL);

	वापस 0;
पूर्ण

अटल पूर्णांक berlin_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm_dev)
अणु
	काष्ठा berlin_pwm_chip *pwm = to_berlin_pwm_chip(chip);
	u32 value;

	value = berlin_pwm_पढ़ोl(pwm, pwm_dev->hwpwm, BERLIN_PWM_EN);
	value |= BERLIN_PWM_ENABLE;
	berlin_pwm_ग_लिखोl(pwm, pwm_dev->hwpwm, value, BERLIN_PWM_EN);

	वापस 0;
पूर्ण

अटल व्योम berlin_pwm_disable(काष्ठा pwm_chip *chip,
			       काष्ठा pwm_device *pwm_dev)
अणु
	काष्ठा berlin_pwm_chip *pwm = to_berlin_pwm_chip(chip);
	u32 value;

	value = berlin_pwm_पढ़ोl(pwm, pwm_dev->hwpwm, BERLIN_PWM_EN);
	value &= ~BERLIN_PWM_ENABLE;
	berlin_pwm_ग_लिखोl(pwm, pwm_dev->hwpwm, value, BERLIN_PWM_EN);
पूर्ण

अटल स्थिर काष्ठा pwm_ops berlin_pwm_ops = अणु
	.request = berlin_pwm_request,
	.मुक्त = berlin_pwm_मुक्त,
	.config = berlin_pwm_config,
	.set_polarity = berlin_pwm_set_polarity,
	.enable = berlin_pwm_enable,
	.disable = berlin_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id berlin_pwm_match[] = अणु
	अणु .compatible = "marvell,berlin-pwm" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, berlin_pwm_match);

अटल पूर्णांक berlin_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा berlin_pwm_chip *pwm;
	पूर्णांक ret;

	pwm = devm_kzalloc(&pdev->dev, माप(*pwm), GFP_KERNEL);
	अगर (!pwm)
		वापस -ENOMEM;

	pwm->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pwm->base))
		वापस PTR_ERR(pwm->base);

	pwm->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pwm->clk))
		वापस PTR_ERR(pwm->clk);

	ret = clk_prepare_enable(pwm->clk);
	अगर (ret)
		वापस ret;

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &berlin_pwm_ops;
	pwm->chip.npwm = 4;
	pwm->chip.of_xlate = of_pwm_xlate_with_flags;
	pwm->chip.of_pwm_n_cells = 3;

	ret = pwmchip_add(&pwm->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);
		clk_disable_unprepare(pwm->clk);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwm);

	वापस 0;
पूर्ण

अटल पूर्णांक berlin_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा berlin_pwm_chip *pwm = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&pwm->chip);
	clk_disable_unprepare(pwm->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक berlin_pwm_suspend(काष्ठा device *dev)
अणु
	काष्ठा berlin_pwm_chip *pwm = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < pwm->chip.npwm; i++) अणु
		काष्ठा berlin_pwm_channel *channel;

		channel = pwm_get_chip_data(&pwm->chip.pwms[i]);
		अगर (!channel)
			जारी;

		channel->enable = berlin_pwm_पढ़ोl(pwm, i, BERLIN_PWM_ENABLE);
		channel->ctrl = berlin_pwm_पढ़ोl(pwm, i, BERLIN_PWM_CONTROL);
		channel->duty = berlin_pwm_पढ़ोl(pwm, i, BERLIN_PWM_DUTY);
		channel->tcnt = berlin_pwm_पढ़ोl(pwm, i, BERLIN_PWM_TCNT);
	पूर्ण

	clk_disable_unprepare(pwm->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक berlin_pwm_resume(काष्ठा device *dev)
अणु
	काष्ठा berlin_pwm_chip *pwm = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = clk_prepare_enable(pwm->clk);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < pwm->chip.npwm; i++) अणु
		काष्ठा berlin_pwm_channel *channel;

		channel = pwm_get_chip_data(&pwm->chip.pwms[i]);
		अगर (!channel)
			जारी;

		berlin_pwm_ग_लिखोl(pwm, i, channel->ctrl, BERLIN_PWM_CONTROL);
		berlin_pwm_ग_लिखोl(pwm, i, channel->duty, BERLIN_PWM_DUTY);
		berlin_pwm_ग_लिखोl(pwm, i, channel->tcnt, BERLIN_PWM_TCNT);
		berlin_pwm_ग_लिखोl(pwm, i, channel->enable, BERLIN_PWM_ENABLE);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(berlin_pwm_pm_ops, berlin_pwm_suspend,
			 berlin_pwm_resume);

अटल काष्ठा platक्रमm_driver berlin_pwm_driver = अणु
	.probe = berlin_pwm_probe,
	.हटाओ = berlin_pwm_हटाओ,
	.driver = अणु
		.name = "berlin-pwm",
		.of_match_table = berlin_pwm_match,
		.pm = &berlin_pwm_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(berlin_pwm_driver);

MODULE_AUTHOR("Antoine Tenart <antoine.tenart@free-electrons.com>");
MODULE_DESCRIPTION("Marvell Berlin PWM driver");
MODULE_LICENSE("GPL v2");
