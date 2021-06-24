<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The Netronix embedded controller is a microcontroller found in some
 * e-book पढ़ोers deचिन्हित by the original design manufacturer Netronix, Inc.
 * It contains RTC, battery monitoring, प्रणाली घातer management, and PWM
 * functionality.
 *
 * This driver implements PWM output.
 *
 * Copyright 2020 Jonathan Neuschथअfer <j.neuschaefer@gmx.net>
 *
 * Limitations:
 * - The get_state callback is not implemented, because the current state of
 *   the PWM output can't be पढ़ो back from the hardware.
 * - The hardware can only generate normal polarity output.
 * - The period and duty cycle can't be changed together in one atomic action.
 */

#समावेश <linux/mfd/ntxec.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

काष्ठा ntxec_pwm अणु
	काष्ठा device *dev;
	काष्ठा ntxec *ec;
	काष्ठा pwm_chip chip;
पूर्ण;

अटल काष्ठा ntxec_pwm *ntxec_pwm_from_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा ntxec_pwm, chip);
पूर्ण

#घोषणा NTXEC_REG_AUTO_OFF_HI	0xa1
#घोषणा NTXEC_REG_AUTO_OFF_LO	0xa2
#घोषणा NTXEC_REG_ENABLE	0xa3
#घोषणा NTXEC_REG_PERIOD_LOW	0xa4
#घोषणा NTXEC_REG_PERIOD_HIGH	0xa5
#घोषणा NTXEC_REG_DUTY_LOW	0xa6
#घोषणा NTXEC_REG_DUTY_HIGH	0xa7

/*
 * The समय base used in the EC is 8MHz, or 125ns. Period and duty cycle are
 * measured in this unit.
 */
#घोषणा TIME_BASE_NS 125

/*
 * The maximum input value (in nanoseconds) is determined by the समय base and
 * the range of the hardware रेजिस्टरs that hold the converted value.
 * It fits पूर्णांकo 32 bits, so we can करो our calculations in 32 bits as well.
 */
#घोषणा MAX_PERIOD_NS (TIME_BASE_NS * 0xffff)

अटल पूर्णांक ntxec_pwm_set_raw_period_and_duty_cycle(काष्ठा pwm_chip *chip,
						   पूर्णांक period, पूर्णांक duty)
अणु
	काष्ठा ntxec_pwm *priv = ntxec_pwm_from_chip(chip);

	/*
	 * Changes to the period and duty cycle take effect as soon as the
	 * corresponding low byte is written, so the hardware may be configured
	 * to an inconsistent state after the period is written and beक्रमe the
	 * duty cycle is fully written. If, in such a हाल, the old duty cycle
	 * is दीर्घer than the new period, the EC may output 100% क्रम a moment.
	 *
	 * To minimize the समय between the changes to period and duty cycle
	 * taking effect, the ग_लिखोs are पूर्णांकerleaved.
	 */

	काष्ठा reg_sequence regs[] = अणु
		अणु NTXEC_REG_PERIOD_HIGH, ntxec_reg8(period >> 8) पूर्ण,
		अणु NTXEC_REG_DUTY_HIGH, ntxec_reg8(duty >> 8) पूर्ण,
		अणु NTXEC_REG_PERIOD_LOW, ntxec_reg8(period) पूर्ण,
		अणु NTXEC_REG_DUTY_LOW, ntxec_reg8(duty) पूर्ण,
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(priv->ec->regmap, regs, ARRAY_SIZE(regs));
पूर्ण

अटल पूर्णांक ntxec_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm_dev,
			   स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा ntxec_pwm *priv = ntxec_pwm_from_chip(chip);
	अचिन्हित पूर्णांक period, duty;
	पूर्णांक res;

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	period = min_t(u64, state->period, MAX_PERIOD_NS);
	duty   = min_t(u64, state->duty_cycle, period);

	period /= TIME_BASE_NS;
	duty   /= TIME_BASE_NS;

	/*
	 * Writing a duty cycle of zero माला_दो the device पूर्णांकo a state where
	 * writing a higher duty cycle करोesn't result in the brightness that it
	 * usually results in. This can be fixed by cycling the ENABLE रेजिस्टर.
	 *
	 * As a workaround, ग_लिखो ENABLE=0 when the duty cycle is zero.
	 * The हाल that something has previously set the duty cycle to zero
	 * but ENABLE=1, is not handled.
	 */
	अगर (state->enabled && duty != 0) अणु
		res = ntxec_pwm_set_raw_period_and_duty_cycle(chip, period, duty);
		अगर (res)
			वापस res;

		res = regmap_ग_लिखो(priv->ec->regmap, NTXEC_REG_ENABLE, ntxec_reg8(1));
		अगर (res)
			वापस res;

		/* Disable the स्वतः-off समयr */
		res = regmap_ग_लिखो(priv->ec->regmap, NTXEC_REG_AUTO_OFF_HI, ntxec_reg8(0xff));
		अगर (res)
			वापस res;

		वापस regmap_ग_लिखो(priv->ec->regmap, NTXEC_REG_AUTO_OFF_LO, ntxec_reg8(0xff));
	पूर्ण अन्यथा अणु
		वापस regmap_ग_लिखो(priv->ec->regmap, NTXEC_REG_ENABLE, ntxec_reg8(0));
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा pwm_ops ntxec_pwm_ops = अणु
	.owner = THIS_MODULE,
	.apply = ntxec_pwm_apply,
	/*
	 * No .get_state callback, because the current state cannot be पढ़ो
	 * back from the hardware.
	 */
पूर्ण;

अटल पूर्णांक ntxec_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ntxec *ec = dev_get_drvdata(pdev->dev.parent);
	काष्ठा ntxec_pwm *priv;
	काष्ठा pwm_chip *chip;

	pdev->dev.of_node = pdev->dev.parent->of_node;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->ec = ec;
	priv->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, priv);

	chip = &priv->chip;
	chip->dev = &pdev->dev;
	chip->ops = &ntxec_pwm_ops;
	chip->base = -1;
	chip->npwm = 1;

	वापस pwmchip_add(chip);
पूर्ण

अटल पूर्णांक ntxec_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ntxec_pwm *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा pwm_chip *chip = &priv->chip;

	वापस pwmchip_हटाओ(chip);
पूर्ण

अटल काष्ठा platक्रमm_driver ntxec_pwm_driver = अणु
	.driver = अणु
		.name = "ntxec-pwm",
	पूर्ण,
	.probe = ntxec_pwm_probe,
	.हटाओ = ntxec_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(ntxec_pwm_driver);

MODULE_AUTHOR("Jonathan Neuschथअfer <j.neuschaefer@gmx.net>");
MODULE_DESCRIPTION("PWM driver for Netronix EC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ntxec-pwm");
