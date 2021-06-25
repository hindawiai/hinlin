<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sl28cpld PWM driver
 *
 * Copyright (c) 2020 Michael Walle <michael@walle.cc>
 *
 * There is no खुला datasheet available क्रम this PWM core. But it is easy
 * enough to be briefly explained. It consists of one 8-bit counter. The PWM
 * supports four distinct frequencies by selecting when to reset the counter.
 * With the prescaler setting you can select which bit of the counter is used
 * to reset it. This implies that the higher the frequency the less reमुख्यing
 * bits are available क्रम the actual counter.
 *
 * Let cnt[7:0] be the counter, घड़ीed at 32kHz:
 * +-----------+--------+--------------+-----------+---------------+
 * | prescaler |  reset | counter bits | frequency | period length |
 * +-----------+--------+--------------+-----------+---------------+
 * |         0 | cnt[7] |     cnt[6:0] |    250 Hz |    4000000 ns |
 * |         1 | cnt[6] |     cnt[5:0] |    500 Hz |    2000000 ns |
 * |         2 | cnt[5] |     cnt[4:0] |     1 kHz |    1000000 ns |
 * |         3 | cnt[4] |     cnt[3:0] |     2 kHz |     500000 ns |
 * +-----------+--------+--------------+-----------+---------------+
 *
 * Limitations:
 * - The hardware cannot generate a 100% duty cycle अगर the prescaler is 0.
 * - The hardware cannot atomically set the prescaler and the counter value,
 *   which might lead to glitches and inconsistent states अगर a ग_लिखो fails.
 * - The counter is not reset अगर you चयन the prescaler which leads
 *   to glitches, too.
 * - The duty cycle will चयन immediately and not after a complete cycle.
 * - Depending on the actual implementation, disabling the PWM might have
 *   side effects. For example, अगर the output pin is shared with a GPIO pin
 *   it will स्वतःmatically चयन back to GPIO mode.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>

/*
 * PWM समयr block रेजिस्टरs.
 */
#घोषणा SL28CPLD_PWM_CTRL			0x00
#घोषणा   SL28CPLD_PWM_CTRL_ENABLE		BIT(7)
#घोषणा   SL28CPLD_PWM_CTRL_PRESCALER_MASK	GENMASK(1, 0)
#घोषणा SL28CPLD_PWM_CYCLE			0x01
#घोषणा   SL28CPLD_PWM_CYCLE_MAX		GENMASK(6, 0)

#घोषणा SL28CPLD_PWM_CLK			32000 /* 32 kHz */
#घोषणा SL28CPLD_PWM_MAX_DUTY_CYCLE(prescaler)	(1 << (7 - (prescaler)))
#घोषणा SL28CPLD_PWM_PERIOD(prescaler) \
	(NSEC_PER_SEC / SL28CPLD_PWM_CLK * SL28CPLD_PWM_MAX_DUTY_CYCLE(prescaler))

/*
 * We calculate the duty cycle like this:
 *   duty_cycle_ns = pwm_cycle_reg * max_period_ns / max_duty_cycle
 *
 * With
 *   max_period_ns = 1 << (7 - prescaler) / SL28CPLD_PWM_CLK * NSEC_PER_SEC
 *   max_duty_cycle = 1 << (7 - prescaler)
 * this then simplअगरies to:
 *   duty_cycle_ns = pwm_cycle_reg / SL28CPLD_PWM_CLK * NSEC_PER_SEC
 *                 = NSEC_PER_SEC / SL28CPLD_PWM_CLK * pwm_cycle_reg
 *
 * NSEC_PER_SEC is a multiple of SL28CPLD_PWM_CLK, thereक्रमe we're not losing
 * precision by करोing the भागison first.
 */
#घोषणा SL28CPLD_PWM_TO_DUTY_CYCLE(reg) \
	(NSEC_PER_SEC / SL28CPLD_PWM_CLK * (reg))
#घोषणा SL28CPLD_PWM_FROM_DUTY_CYCLE(duty_cycle) \
	(DIV_ROUND_DOWN_ULL((duty_cycle), NSEC_PER_SEC / SL28CPLD_PWM_CLK))

#घोषणा sl28cpld_pwm_पढ़ो(priv, reg, val) \
	regmap_पढ़ो((priv)->regmap, (priv)->offset + (reg), (val))
#घोषणा sl28cpld_pwm_ग_लिखो(priv, reg, val) \
	regmap_ग_लिखो((priv)->regmap, (priv)->offset + (reg), (val))

काष्ठा sl28cpld_pwm अणु
	काष्ठा pwm_chip pwm_chip;
	काष्ठा regmap *regmap;
	u32 offset;
पूर्ण;
#घोषणा sl28cpld_pwm_from_chip(_chip) \
	container_of(_chip, काष्ठा sl28cpld_pwm, pwm_chip)

अटल व्योम sl28cpld_pwm_get_state(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm,
				   काष्ठा pwm_state *state)
अणु
	काष्ठा sl28cpld_pwm *priv = sl28cpld_pwm_from_chip(chip);
	अचिन्हित पूर्णांक reg;
	पूर्णांक prescaler;

	sl28cpld_pwm_पढ़ो(priv, SL28CPLD_PWM_CTRL, &reg);

	state->enabled = reg & SL28CPLD_PWM_CTRL_ENABLE;

	prescaler = FIELD_GET(SL28CPLD_PWM_CTRL_PRESCALER_MASK, reg);
	state->period = SL28CPLD_PWM_PERIOD(prescaler);

	sl28cpld_pwm_पढ़ो(priv, SL28CPLD_PWM_CYCLE, &reg);
	state->duty_cycle = SL28CPLD_PWM_TO_DUTY_CYCLE(reg);
	state->polarity = PWM_POLARITY_NORMAL;

	/*
	 * Sanitize values क्रम the PWM core. Depending on the prescaler it
	 * might happen that we calculate a duty_cycle greater than the actual
	 * period. This might happen अगर someone (e.g. the bootloader) sets an
	 * invalid combination of values. The behavior of the hardware is
	 * undefined in this हाल. But we need to report sane values back to
	 * the PWM core.
	 */
	state->duty_cycle = min(state->duty_cycle, state->period);
पूर्ण

अटल पूर्णांक sl28cpld_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			      स्थिर काष्ठा pwm_state *state)
अणु
	काष्ठा sl28cpld_pwm *priv = sl28cpld_pwm_from_chip(chip);
	अचिन्हित पूर्णांक cycle, prescaler;
	bool ग_लिखो_duty_cycle_first;
	पूर्णांक ret;
	u8 ctrl;

	/* Polarity inversion is not supported */
	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	/*
	 * Calculate the prescaler. Pick the biggest period that isn't
	 * bigger than the requested period.
	 */
	prescaler = DIV_ROUND_UP_ULL(SL28CPLD_PWM_PERIOD(0), state->period);
	prescaler = order_base_2(prescaler);

	अगर (prescaler > field_max(SL28CPLD_PWM_CTRL_PRESCALER_MASK))
		वापस -दुस्फल;

	ctrl = FIELD_PREP(SL28CPLD_PWM_CTRL_PRESCALER_MASK, prescaler);
	अगर (state->enabled)
		ctrl |= SL28CPLD_PWM_CTRL_ENABLE;

	cycle = SL28CPLD_PWM_FROM_DUTY_CYCLE(state->duty_cycle);
	cycle = min_t(अचिन्हित पूर्णांक, cycle, SL28CPLD_PWM_MAX_DUTY_CYCLE(prescaler));

	/*
	 * Work around the hardware limitation. See also above. Trap 100% duty
	 * cycle अगर the prescaler is 0. Set prescaler to 1 instead. We करोn't
	 * care about the frequency because its "all-one" in either हाल.
	 *
	 * We करोn't need to check the actual prescaler setting, because only
	 * अगर the prescaler is 0 we can have this particular value.
	 */
	अगर (cycle == SL28CPLD_PWM_MAX_DUTY_CYCLE(0)) अणु
		ctrl &= ~SL28CPLD_PWM_CTRL_PRESCALER_MASK;
		ctrl |= FIELD_PREP(SL28CPLD_PWM_CTRL_PRESCALER_MASK, 1);
		cycle = SL28CPLD_PWM_MAX_DUTY_CYCLE(1);
	पूर्ण

	/*
	 * To aव्योम glitches when we चयन the prescaler, we have to make sure
	 * we have a valid duty cycle क्रम the new mode.
	 *
	 * Take the current prescaler (or the current period length) पूर्णांकo
	 * account to decide whether we have to ग_लिखो the duty cycle or the new
	 * prescaler first. If the period length is decreasing we have to
	 * ग_लिखो the duty cycle first.
	 */
	ग_लिखो_duty_cycle_first = pwm->state.period > state->period;

	अगर (ग_लिखो_duty_cycle_first) अणु
		ret = sl28cpld_pwm_ग_लिखो(priv, SL28CPLD_PWM_CYCLE, cycle);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = sl28cpld_pwm_ग_लिखो(priv, SL28CPLD_PWM_CTRL, ctrl);
	अगर (ret)
		वापस ret;

	अगर (!ग_लिखो_duty_cycle_first) अणु
		ret = sl28cpld_pwm_ग_लिखो(priv, SL28CPLD_PWM_CYCLE, cycle);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops sl28cpld_pwm_ops = अणु
	.apply = sl28cpld_pwm_apply,
	.get_state = sl28cpld_pwm_get_state,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक sl28cpld_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sl28cpld_pwm *priv;
	काष्ठा pwm_chip *chip;
	पूर्णांक ret;

	अगर (!pdev->dev.parent) अणु
		dev_err(&pdev->dev, "no parent device\n");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!priv->regmap) अणु
		dev_err(&pdev->dev, "could not get parent regmap\n");
		वापस -ENODEV;
	पूर्ण

	ret = device_property_पढ़ो_u32(&pdev->dev, "reg", &priv->offset);
	अगर (ret) अणु
		dev_err(&pdev->dev, "no 'reg' property found (%pe)\n",
			ERR_PTR(ret));
		वापस -EINVAL;
	पूर्ण

	/* Initialize the pwm_chip काष्ठाure */
	chip = &priv->pwm_chip;
	chip->dev = &pdev->dev;
	chip->ops = &sl28cpld_pwm_ops;
	chip->npwm = 1;

	platक्रमm_set_drvdata(pdev, priv);

	ret = pwmchip_add(&priv->pwm_chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to add PWM chip (%pe)",
			ERR_PTR(ret));
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sl28cpld_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sl28cpld_pwm *priv = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&priv->pwm_chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id sl28cpld_pwm_of_match[] = अणु
	अणु .compatible = "kontron,sl28cpld-pwm" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sl28cpld_pwm_of_match);

अटल काष्ठा platक्रमm_driver sl28cpld_pwm_driver = अणु
	.probe = sl28cpld_pwm_probe,
	.हटाओ	= sl28cpld_pwm_हटाओ,
	.driver = अणु
		.name = "sl28cpld-pwm",
		.of_match_table = sl28cpld_pwm_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sl28cpld_pwm_driver);

MODULE_DESCRIPTION("sl28cpld PWM Driver");
MODULE_AUTHOR("Michael Walle <michael@walle.cc>");
MODULE_LICENSE("GPL");
